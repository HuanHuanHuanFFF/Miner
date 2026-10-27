from pathlib import Path
import hashlib, json, datetime

here = Path(__file__).resolve().parent
root = here.parents[3]
base = root/'competitions/floatlib/candidates/f01-d2-final-finite/Kernel.lean'
parent_sha = '86312a3759286cb207f946af9db95546777fdb16f1bd147f7892c0f9e1d79217'
assert hashlib.sha256(base.read_bytes()).hexdigest() == parent_sha
source = base.read_text(encoding='utf8')
start = source.index('def sum {n : Nat}', source.index('end NativeFinal'))
end = source.index('theorem index_address', start)
fragment = (here/'native-fold-sum-fragment.lean').read_text(encoding='utf8')
source = source[:start]+fragment+'\n'+source[end:]
out = root/'competitions/floatlib/candidates/f01-r2-native-fold-sum'
out.mkdir(exist_ok=True)
assert not (out/'Kernel.lean').exists(), 'Preserve frozen candidate; use a new name.'
(out/'Kernel.lean').write_text(source,encoding='utf8',newline='\n')
data = (out/'Kernel.lean').read_bytes()
manifest = {'candidate':out.name,'candidate_file':'Kernel.lean','candidate_sha256':hashlib.sha256(data).hexdigest(),'candidate_bytes':len(data),'parent':base.parent.name,'parent_sha256':parent_sha,'validation_mode':'statement-only','proof_status':'NOT_RUN: backward list fold proof plus Vector.foldl_toList bridge','mechanism':'Use standard Vector.foldl of inline native Float32 step with one final finite guard; retain exact software fallback. Intended to use specialized machine-size standard array fold. Scalar operations and bmm unchanged.','created_at_utc':datetime.datetime.now(datetime.timezone.utc).isoformat(),'formal_submission':'NOT_SUBMITTED'}
(out/'manifest.json').write_text(json.dumps(manifest,indent=2)+'\n',encoding='utf8')
print(json.dumps(manifest,indent=2))
