from pathlib import Path
import json,hashlib
from datetime import datetime,timezone
H=Path(__file__).parent;ROOT=Path.cwd()
old=(ROOT/'competitions/torchlean/candidates/r26-1h-20261029T085515Z/research/key/follow-on/CheckerConsequences.lean.inc').read_text(encoding='utf-8-sig')
cut=old[:old.index('/-- Strict containment follows')]+ '\nend Submission.R26CheckerConsequences\n'
extra='''
namespace Submission.R27GuardedEndpoints
open FloatLib.Floats FloatLib.Floats.Formats.BinaryInterchange
open Submission.R25OrderKey Submission.R25Checker

theorem actual_accepted_exact_nonzero (s r : Float) (q : UInt32) (S : Real)
    (hr : r.isFinite = true)
    (herr : |nativeValue s - S| ≤ nativeValue r)
    (hacc : Submission.R24PortableF64.certify s r s.toBits q = true) : S ≠ 0 := by
  have ha : certify s r s.toBits q = true := by
    simpa only [certify_eq_runtime] using hacc
  obtain ⟨he0, he255, _⟩ := accepted_components s r s.toBits q ha
  obtain ⟨hlf, huf, hlnz, hunz⟩ := midpoint_finite_nonzero q he0 he255
  have hs := Submission.R26CheckerConsequences.midpoint_signs q he0 he255
  have hp := (magnitudeReal_pos_iff (magnitude (lowerWord q))).mpr hlnz
  have hn := (magnitudeReal_pos_iff (magnitude (upperWord q))).mpr hunz
  have hc := actual_acceptance_contains_exact_of_error s r q S hr herr hacc
  rw [raw_value _ hlf, raw_value _ huf, hs.1, hs.2] at hc
  cases hsign : negative32 q <;>
    simp only [hsign, Bool.false_eq_true, ite_false, ite_true] at hc <;>
    intro hz <;> subst S <;> linarith

theorem actual_accepted_total_nonzero (s r : Float) (q : UInt32) (T e : Int)
    (hr : r.isFinite = true)
    (herr : |nativeValue s - (T : Real) * (2 : Real) ^ e| ≤ nativeValue r)
    (hacc : Submission.R24PortableF64.certify s r s.toBits q = true) : T ≠ 0 := by
  have hn := actual_accepted_exact_nonzero s r q ((T : Real) * (2 : Real) ^ e) hr herr hacc
  intro hz
  apply hn
  simp only [hz, Int.cast_zero, zero_mul]

end Submission.R27GuardedEndpoints
'''
s=(H/'boundary-v1/GuardedBoundaryContractOnly.lean').read_text(encoding='utf-8')+'\n'+cut+'\n'+extra
p=H/'boundary-v1/GuardedNonzeroContractOnly.lean';p.write_text(s,encoding='utf-8',newline='\n');b=p.read_bytes()
r=dict(at_utc=datetime.now(timezone.utc).isoformat(),state='PREPARED_NEXT_AFTER_CORE',path=p.relative_to(ROOT).as_posix(),bytes=len(b),sha256=hashlib.sha256(b).hexdigest(),helper_roots=['Submission.R25OrderKey.orderKey_lt_real','Submission.R25Checker.actual_acceptance_bounds','Submission.R27GuardedEndpoints.accepted_endpoint_equations','Submission.R27GuardedEndpoints.actual_acceptance_contains_exact_of_error','Submission.R27GuardedEndpoints.actual_accepted_exact_nonzero','Submission.R27GuardedEndpoints.actual_accepted_total_nonzero'],remaining_producer=['actual radius finite','actual forward error in terms of native radius value'],remaining_rounder='strict raw binary32 cell -> NativeBinary32.roundDyadic/official finishWord',proof='NOT_RUN',formal_submission=False)
(H/'boundary-v1/nonzero-receipt.json').write_text(json.dumps(r,ensure_ascii=False,indent=2)+'\n',encoding='utf-8')
print(json.dumps(r,ensure_ascii=False,indent=2))
