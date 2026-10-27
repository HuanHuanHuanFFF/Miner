"""Build one exact B2 classifier diagnostic; no Lean/compiler/Git execution."""
from pathlib import Path
import hashlib, json, re, datetime, random

HERE = Path(__file__).resolve().parent
ROOT = next(p for p in HERE.parents if (p / "DEVELOPMENT.md").exists())
BASE = ROOT / "competitions/floatlib/candidates/f01-r15-dev-packed-b2-1/Kernel.lean"
EXPECTED = "622d8394a7127e93dcaf992c62c6dfcff7208d212738409a5e34525dfafd1a58"
sha = lambda b: hashlib.sha256(b).hexdigest()
base = BASE.read_bytes()
assert sha(base) == EXPECTED
src = base.decode("utf-8")
old = """@[inline] def fastOK (u : UInt32) : Bool :=
  let a := magnitude u
  decide (0x0bffffff ≤ a - 1) && decide (a < 0x7f800000)"""
new = """@[inline] def fastOK (u : UInt32) : Bool :=
  let a := magnitude u
  decide (0x0bffffff ≤ a - 1) == decide (a < 0x7f800000)"""
assert src.count(old) == 1
src = src.replace(old, new)
bridge = """
/- R19 runtime classifier: the two rejection domains are disjoint.
   All arithmetic, table reads, native codecs and fallbacks are unchanged. -/
theorem r19_low_reject_finite (a : UInt32)
    (h : ¬ ((0x0bffffff : UInt32) ≤ a - 1)) :
    a < (0x7f800000 : UInt32) := by
  by_cases hz : a = 0
  · subst a
    exact False.elim (h (by decide))
  · have hpos : 0 < a := UInt32.pos_iff_ne_zero.mpr hz
    have hone : (1 : UInt32) ≤ a := by
      change 1 ≤ a.toNat
      change 0 < a.toNat at hpos
      omega
    have hnat : ¬ 201326591 ≤ (a - 1).toNat := h
    rw [UInt32.toNat_sub_of_le a 1 hone] at hnat
    change a.toNat < 2139095040
    change ¬ 201326591 ≤ a.toNat - 1 at hnat
    omega

theorem r19_eager_gate_eq (a : UInt32) :
    (decide (0x0bffffff ≤ a - 1) == decide (a < 0x7f800000)) =
      (decide (0x0bffffff ≤ a - 1) && decide (a < 0x7f800000)) := by
  by_cases hl : (0x0bffffff : UInt32) ≤ a - 1
  · by_cases hh : a < (0x7f800000 : UInt32) <;> simp [hl, hh]
  · have hh := r19_low_reject_finite a hl
    simp [hl, hh]

theorem r19_fastOK_eq_old (u : UInt32) :
    fastOK u = (decide (0x0bffffff ≤ magnitude u - 1) &&
      decide (magnitude u < 0x7f800000)) := by
  exact r19_eager_gate_eq (magnitude u)

"""
marker = "theorem fastOK_iff (u : UInt32) :"
assert src.count(marker) == 1
src = src.replace(marker, bridge + marker)
old_proof = "  exact wrap_gate_iff (magnitude u)"
assert src.count(old_proof) == 1
src = src.replace(old_proof, "  rw [r19_fastOK_eq_old]\n" + old_proof)
candidate = src.encode("utf-8")
assert len(candidate) <= 256000
out = HERE / "Kernel-eager-classifier.lean"
out.write_bytes(candidate)
(HERE / "Classifier-bridge.lean.inc").write_text(bridge, encoding="utf-8", newline="\n")
undo = src.replace(bridge, "").replace(new, old).replace("  rw [r19_fastOK_eq_old]\n"+old_proof, old_proof)
assert undo.encode("utf-8") == base

# Bounded independent guard truth table, including values not obtainable as magnitude.
critical = {0,1,2,0x0bfffffe,0x0bffffff,0x0c000000,0x0c000001,
            0x7f7ffffe,0x7f7fffff,0x7f800000,0x7f800001,0x7fffffff,
            0x80000000,0xfffffffe,0xffffffff}
rng = random.Random(20261027)
values = list(critical) + [rng.getrandbits(32) for _ in range(100000)]
for a in values:
    lo = 0x0bffffff <= ((a-1) & 0xffffffff)
    hi = a < 0x7f800000
    assert (lo == hi) == (lo and hi), a

manifest = {
    "created_utc": datetime.datetime.now(datetime.timezone.utc).isoformat(),
    "state": "COMPLETE_SOURCE_PROOF_ATTEMPT_NOT_RUN",
    "baseline": {"path": str(BASE), "sha256": sha(base), "bytes":len(base)},
    "candidate": {"path": str(out), "sha256": sha(candidate), "bytes":len(candidate)},
    "mechanism": "Eager Bool.beq replaces short-circuit Bool.and for exactly the same full fastOK domain; disjoint rejects prove equality.",
    "scope": "Actual selected scalar add/nativeMul and their fallback uses of convert. SUM manual classification and BMM layout/dispatch remain byte-identical.",
    "edits": ["one runtime && to ==", "three bridge lemmas", "one fastOK_iff rewrite"],
    "inverse_splice_restores_exact_baseline": True,
    "model": {"samples":len(values), "mismatches":0, "scope":"guard Boolean identity only; not Lean or float validation"},
    "lean": "NOT_RUN", "full_gate": "NOT_RUN", "timing": "NOT_RUN",
    "codegen": "UNKNOWN: Clang may already compile old conjunction eagerly; candidate must show a real selected-path difference before timing.",
    "early_stop": "If selected MainFull ADD/MUL accepted paths are identical, park without full timing. If branch removed, D decides one complete discovery with all preparation/codec/fallback costs.",
    "not_claimed": ["10 percent whole gain", "compiler branch removal", "new numerical method", "formal admission"],
    "resources": {"local_compiler_runs":0,"ci_runs":0,"tokens":"UNKNOWN","cached_input_tokens":"UNKNOWN"}
}
(HERE / "classifier-manifest.json").write_text(json.dumps(manifest,indent=2)+"\n",encoding="utf-8")
print(json.dumps({"bytes":len(candidate),"sha256":sha(candidate),"samples":len(values),"inverse_splice":True}))
