"""Prepare an UNCOMPILED full Lean draft for E1, preserving the timing pair."""
from pathlib import Path
import datetime
import hashlib
import json
import re

ROOT = Path(__file__).resolve().parents[1]
OLD = ROOT / "candidates/r26-e-658-short-same"
NEW = ROOT / "candidates/r26-e-658-short-same-proof1"
OUT = ROOT / "evidence/round26/extension90m/route-e"

HELPER = r'''/- E1 proof draft, UNCOMPILED. The direct short branch includes len8.
   It uses the same word8_prefix theorem as the original masked tail. -/
theorem e1_mask_match {input : Slice Std.U8} {a b len : Std.Usize}
    {x y z w : Std.U64} {sh : Std.U32}
    (hd : len.val ≤ 8)
    (hx : x.val = word8 input a.val) (hy : y.val = word8 input b.val)
    (hz : z.val = (x ^^^ y).val) (hw : w.val = z.val >>> sh.val)
    (hw0 : w.val = 0) (hsh : sh.val = 64 - 8 * len.val) :
    Matches input a.val b.val len.val := by
  have h0 : (x.val ^^^ y.val) >>> sh.val = 0 := by
    rw [← UScalar.val_xor, ← hz, ← hw, hw0]
  rw [Nat.shiftRight_xor_distrib] at h0
  have heq := nat_xor_eq_zero h0
  apply word8_prefix input a.val b.val len.val hd
  rw [← hx, ← hy, ← hsh]
  simpa only [Nat.shiftRight_eq_div_pow] using heq

'''

BODY = r''' := by
  rw [slot.u118_same]
  have hmax : s.length ≤ Std.Usize.max := Std.Slice.length_ineq s
  step*
  all_goals first
    | (intro hr; exfalso; scalar_tac)
    | (intro hr
       apply e1_mask_match (input := s) (a := a) (b := b) (len := len)
       all_goals first | assumption | scalar_tac)
    | (apply Std.WP.spec_bind (same_loop0_spec s a b len 0#usize 1#usize
         ha hb hlen (by simp) (LZ77.Matches.zero s a.val b.val))
       rintro ⟨k, ok⟩ ⟨hk, hm, hok⟩
       simp only at hk hm hok
       step*
       intro _
       exact Matches.mask hm (by assumption) (by assumption) (by assumption)
         (by assumption) (by assumption) (by assumption) (by assumption)
         (by scalar_tac) (by scalar_tac) (by scalar_tac))
'''


def sha(raw):
    return hashlib.sha256(raw).hexdigest()


def dump(path, obj):
    path.write_bytes((json.dumps(obj, indent=2, ensure_ascii=False)+"\n").encode())


def main():
    assert not NEW.exists(), NEW
    rust = (OLD / "parse.rs").read_bytes()
    original = (OLD / "Parse.lean").read_bytes()
    text = original.decode()
    start = text.index("@[local step]\ntheorem same_spec", text.index("namespace U118_MAIN"))
    end = text.index("\ntheorem lz32_le", start)
    theorem = text[start:end]
    old_body = " := C12553! slot.u118_same"
    assert theorem.count(old_body) == 1
    theorem = theorem.replace(old_body, BODY.rstrip())
    lean = (text[:start] + HELPER + theorem + text[end:]).encode()
    assert len(lean) <= 524288
    assert not re.search(rb"(?m)^\s*(axiom\s|.*\b(sorry|admit)\b)", lean)
    NEW.mkdir()
    (NEW / "parse.rs").write_bytes(rust)
    (NEW / "Parse.lean").write_bytes(lean)
    metadata = json.loads((OLD / "manifest.json").read_bytes())
    metadata.update({"candidate": NEW.name,
        "hashes": {"parse.rs": sha(rust), "Parse.lean": sha(lean)},
        "implementation_parent": OLD.relative_to(ROOT).as_posix(),
        "proof_status": "UNCOMPILED_ORIGINAL_GATE_NOT_RUN",
        "proof_adaptation": "Add inclusive len<=8 word-prefix helper; same_spec branches fast result vs unchanged loop0+masked-tail proof. Generated variable/interface matching remains untested.",
        "proof_origin": {"path": "references/round26-public-658/Parse.lean", "sha256": sha(original)},
        "prepared_utc": datetime.datetime.now(datetime.timezone.utc).isoformat()})
    dump(NEW / "manifest.json", metadata)
    dump(OUT / "e1-proof1-entry.json", {"name": NEW.name,
        "path": NEW.relative_to(ROOT).as_posix(), "hashes": metadata["hashes"],
        "rust_bytes": len(rust), "lean_bytes": len(lean),
        "lean_spare_bytes": 524288-len(lean), "status": metadata["proof_status"],
        "control": False, "anchor": "public658", "comparison_baseline": "public658"})
    (OUT / "E1-helper-UNCOMPILED.lean").write_bytes((HELPER+BODY).encode())
    print(json.dumps(metadata["hashes"], indent=2))


if __name__ == "__main__":
    main()
