"""Repair actual batch4 goals with B's explicit cancellation Nat proof.

No runtime change. The alternate proof is uncompiled until fresh public CI.
"""
from pathlib import Path
import hashlib
import json
HERE=Path(__file__).resolve().parent
BASE=HERE.parents[1]

def build():
    original=(HERE/'ReciprocalUInt64ContractOnly-v3.lean').read_text(encoding='utf-8')
    assert hashlib.sha256(original.encode()).hexdigest()=='032dd2d40779f88b49cc28a23d5dc2bf4f1b9f371b0b7c071f5b36fe482ae97f'
    alternate=(BASE/'research/word-proof/ReciprocalNatCore.lean').read_text(encoding='utf-8')
    alternate=alternate.removeprefix('import ContractExact\n')
    alternate=alternate.replace('namespace Submission.R27Reciprocal','namespace R27ReciprocalProof')
    alternate=alternate.replace('end Submission.R27Reciprocal','end R27ReciprocalProof')
    alternate=alternate.replace('reciprocal_bounds','reciprocal_estimate_bounds')
    wrapper='''
theorem reciprocal_divrem (base numerator divisor : Nat)
    (base_pos : 0 < base) (numerator_bound : numerator < base)
    (divisor_pos : 0 < divisor) :
    let reciprocal := (base - 1) / divisor
    let estimate := numerator * reciprocal / base
    let remainder := numerator - estimate * divisor
    (if divisor \u2264 remainder then (estimate + 1, remainder - divisor)
     else (estimate, remainder)) = (numerator / divisor, numerator % divisor) :=
  corrected_exact base numerator divisor base_pos numerator_bound divisor_pos
'''
    alternate=alternate.replace('end R27ReciprocalProof',wrapper+'\nend R27ReciprocalProof')
    old_end=original.index('end R27ReciprocalProof')+len('end R27ReciprocalProof')
    result='import ContractExact\n'+alternate+original[old_end:]
    before='      rw [mulHigh_toNat, prepare_toNat]\n'
    assert result.count(before)==1
    result=result.replace(before,before+'      norm_num\n',1)
    before='    dsimp only at lower upper\n'
    assert result.count(before)==1
    result=result.replace(before,'',1)
    return result.encode()

if __name__=='__main__':
    result=build(); out=HERE/'ReciprocalUInt64ContractOnly-v4.lean'; out.write_bytes(result)
    receipt={'source':'ReciprocalUInt64ContractOnly-v4.lean','sha256':hashlib.sha256(result).hexdigest(),
      'bytes':len(result),'status':'ACTUAL_BATCH4_PROOF_REPAIR_NOT_COMPILED',
      'batch4_log_sha256':'39474b428e9c2aebcf6da91e14e51f182970fda7b7d6c26552588eed2f7c5aee',
      'changes':['Use explicit multiplication cancellation from B alternate Nat root',
                 'Normalize numeric base in word estimate_value',
                 'Remove diagnosed no-progress dsimp at lower/upper'],
      'runtime':'Original v3 primitive definitions unchanged; no new correctness claim',
      'independent_proof_source':'research/word-proof/ReciprocalNatCore.lean'}
    (HERE/'reciprocal-v4-repair-receipt.json').write_text(json.dumps(receipt,indent=2)+'\n',encoding='utf-8')
    print(json.dumps(receipt))
