from pathlib import Path
import datetime,hashlib,json,re

here=Path(__file__).resolve().parent
root=here.parents[3]
base=root/'competitions/floatlib/candidates/f01-d2-final-finite/Kernel.lean'
parent_sha='86312a3759286cb207f946af9db95546777fdb16f1bd147f7892c0f9e1d79217'
assert hashlib.sha256(base.read_bytes()).hexdigest()==parent_sha
source=base.read_text(encoding='utf8')
start=source.index('def bmm (batch m n p : Nat)')
end=source.rindex('end Submission')
original=re.sub(r'\bbmm\b','originalBmm',source[start:end])
original=original.replace('theorem bmm_spec :','theorem originalBmm_spec :')
fragment=(here/'checked-floatarray-fragment.lean').read_text(encoding='utf8')
source=source[:start]+original+'\n'+fragment+'\nend Submission\n'
out=root/'competitions/floatlib/candidates/f01-r2-checked-floatarray'
out.mkdir(exist_ok=True)
assert not (out/'Kernel.lean').exists(), 'Preserve frozen candidate; use a new name.'
(out/'Kernel.lean').write_text(source,encoding='utf8',newline='\n')
data=(out/'Kernel.lean').read_bytes()
manifest={'candidate':out.name,'candidate_file':'Kernel.lean','candidate_sha256':hashlib.sha256(data).hexdigest(),'candidate_bytes':len(data),'parent':base.parent.name,'parent_sha256':parent_sha,'validation_mode':'statement-only','proof_status':'NOT_RUN: check-and-prepare FloatArray read invariant plus backward finite dot proof','mechanism':'Validate numeric Float32-to-Float-to-Float32 raw roundtrip once per input, then store contiguous FloatArray doubles and narrow via inline cast on every read. No semantic theorem assumed about the opaque casts. Retain final finite dot fallback and original bmm for a failed preparation check. All checks/conversion/allocation are in the timed call.','extra_gate_question':'Audit exact accepted theorem dependencies for allowed axioms; read compiled C to exclude hot FloatArray.data materialization and external bit conversion.','created_at_utc':datetime.datetime.now(datetime.timezone.utc).isoformat(),'formal_submission':'NOT_SUBMITTED'}
(out/'manifest.json').write_text(json.dumps(manifest,indent=2)+'\n',encoding='utf8')
print(json.dumps(manifest,indent=2))
