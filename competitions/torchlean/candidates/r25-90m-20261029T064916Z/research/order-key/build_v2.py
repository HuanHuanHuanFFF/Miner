"""Static proof-script correction; original v1 artifacts stay byte-identical."""
from pathlib import Path
from datetime import datetime,timezone
import hashlib,json
HERE=Path(__file__).resolve().parent
ROOT=next(p for p in HERE.parents if (p/"AGENTS.md").is_file())
OUT=HERE/"v2"
OUT.mkdir(exist_ok=True)
sha=lambda b:hashlib.sha256(b).hexdigest()
key=(HERE/"OrderKey.lean.inc").read_text(encoding="utf-8")
checker=(HERE/"ActualChecker.lean.inc").read_text(encoding="utf-8")
old="""  have hmask : 9218868437227405312 / 4503599627370496 = (2 ^ 11 - 1 : Nat) := by decide
  rw [hmask, Nat.and_two_pow_sub_one_eq_mod] at hd"""
new="""  change (w.toNat &&& 9218868437227405312) / 4503599627370496 =
    (w.toNat / 4503599627370496) &&& (2 ^ 11 - 1) at hd
  rw [Nat.and_two_pow_sub_one_eq_mod] at hd"""
assert old in key
key=key.replace(old,new)
old="""  cases hsx : negative x <;> cases hsy : negative y <;>
    simp only [hsx, hsy, Bool.false_eq_true, Bool.true_eq_true, ite_false, ite_true] at h ⊢ <;>
    omega"""
new="""  cases hsx : negative x <;> cases hsy : negative y <;>
    simp [hsx, hsy] at h ⊢ <;> omega"""
assert old in key
key=key.replace(old,new)
old="""  rw [base, UInt64.toNat_or, hE, hF]
  rw [Nat.or_comm]
  have hsmall"""
new="""  rw [base, UInt64.toNat_or, hE, hF]
  have hsmall"""
assert old in checker
checker=checker.replace(old,new)
runtime=(HERE/"ActualRuntime.lean.inc").read_text(encoding="utf-8")
identity=(HERE/"RuntimeIdentity.lean.inc").read_text(encoding="utf-8")
original=ROOT/"competitions/floatlib/candidates/f01-d7-research/round7h-20261028T203856Z/source-snapshot/torchlean/kernels/exact/incumbent/Kernel.lean"
combined=key+"\n"+checker+"\n"+runtime+"\n"+identity
outputs={
 "OrderKey.lean.inc":key,
 "ActualChecker.lean.inc":checker,
 "OrderKeyContractOnly.lean":"import ContractExact\n"+key,
 "OrderKeyCoreContractOnly.lean":"import ContractExact\n"+key.split("noncomputable def magnitudeReal",1)[0]+"\nend Submission.R25OrderKey\n",
 "ActualCheckerContractOnly.lean":"import ContractExact\n"+combined,
 "Kernel.lean":original.read_text(encoding="utf-8")+"\n"+combined,
}
for name,content in outputs.items():
    (OUT/name).write_text(content,encoding="utf-8",newline="\n")
roots=json.loads((HERE/"manifest.json").read_text(encoding="utf-8"))["explicit_axiom_roots"]+json.loads((HERE/"checker-manifest.json").read_text(encoding="utf-8"))["explicit_axiom_roots"]
receipt=dict(at_utc=datetime.now(timezone.utc).isoformat(),revision="v2",proof_status="NOT_RUN",
  changes=[
    "expMask_nat: norm_num may already fold MASK/B; replace stale rw by explicit changed target before mask lemma.",
    "orderKey_lt_cases: ordinary simp removes reflexive Boolean equalities before omega.",
    "base_nat: remove reversed OR order; Nat.two_pow_add_eq_or_of_lt already places high part first."
  ],
  runtime_change="NONE",nonzero_condition="UNCHANGED",imports=["ContractExact"],
  files=[dict(path=(OUT/n).relative_to(ROOT).as_posix(),bytes=(OUT/n).stat().st_size,
              sha256=sha((OUT/n).read_bytes())) for n in outputs],
  explicit_axiom_roots=roots,allowed_axioms=["propext","Classical.choice","Quot.sound"],
  actual_CI="NOT_RUN",local_Lean=False,CI_owner="Droot",tokens="UNKNOWN",
  original_v1_preserved=dict(key_sha256=sha((HERE/"OrderKey.lean").read_bytes()),
                            checker_sha256=sha((HERE/"ActualChecker.lean.inc").read_bytes())),
  model_receipt="../small-model.json",model_rerun=False,
  remaining="Actual pinned Lean elaboration, axiom/replay; midpoint real cell bridge and complete producer/checker combination.")
(OUT/"manifest.json").write_text(json.dumps(receipt,indent=2)+"\n",encoding="utf-8")
print(json.dumps(receipt,indent=2))

