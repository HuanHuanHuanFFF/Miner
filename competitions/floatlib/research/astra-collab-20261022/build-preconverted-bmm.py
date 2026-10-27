from pathlib import Path
import hashlib, json, datetime, argparse

p = argparse.ArgumentParser()
p.add_argument('--parent', default='f01-d2-final-finite')
p.add_argument('--expected-parent-sha', default='86312a3759286cb207f946af9db95546777fdb16f1bd147f7892c0f9e1d79217')
p.add_argument('--candidate', default='f01-r2-preconverted-bmm')
a = p.parse_args()
assert a.parent.startswith('f01-d2-') and '/' not in a.parent and '\\' not in a.parent
assert a.candidate.startswith('f01-r2-') and '/' not in a.candidate and '\\' not in a.candidate
here = Path(__file__).resolve().parent
root = here.parents[3]
base = root/'competitions/floatlib/candidates'/a.parent/'Kernel.lean'
data = base.read_bytes()
assert hashlib.sha256(data).hexdigest() == a.expected_parent_sha
source = data.decode('utf8')
fragment = (here/'preconverted-bmm-fragment.lean').read_text(encoding='utf8')
marker = 'theorem index_address (a b c d : Nat)'
assert source.count(marker) == 1
source = source.replace(marker, fragment+'\n'+marker)
start = source.index('def bmm (batch m n p : Nat)')
end = source.index('theorem bmm_spec', start)
source = source[:start]+'''def bmm (batch m n p : Nat) (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p)) : Vector Binary32 (batch * m * p) :=
  let AF := Preconverted.floats A.toArray
  let BF := Preconverted.floats B.toArray
  Vector.ofFn fun q =>
    let (b, i, j) := bmmDecodeC m p q.val
    Preconverted.dot n ((b * m + i) * n) (b * n * p + j) p
      A.toArray B.toArray AF BF

'''+source[end:]
assert source.count('rw [NativeFinal.dot_eq]') == 1
source = source.replace('rw [NativeFinal.dot_eq]', 'rw [Preconverted.dot_map_eq, NativeFinal.dot_eq]')
out = root/'competitions/floatlib/candidates'/a.candidate
out.mkdir(exist_ok=True)
assert not (out/'Kernel.lean').exists(), 'Preserve frozen candidate; use a new name.'
(out/'Kernel.lean').write_text(source,encoding='utf8',newline='\n')
result = (out/'Kernel.lean').read_bytes()
manifest = {'candidate':a.candidate,'candidate_file':'Kernel.lean','candidate_sha256':hashlib.sha256(result).hexdigest(),'candidate_bytes':len(result),'parent':a.parent,'parent_sha256':a.expected_parent_sha,'proof_status':'NOT_RUN: conditional on parent final-finite proof and new map/default induction','mechanism':'Map A/B to Array Float32 once per bmm call; reuse exact ordered native dot loop and final finite fallback. Scalar wrappers and sum unchanged. All mapping/boxing is in timed call.','validation_mode':'statement-only','created_at_utc':datetime.datetime.now(datetime.timezone.utc).isoformat(),'formal_submission':'NOT_SUBMITTED'}
(out/'manifest.json').write_text(json.dumps(manifest,indent=2)+'\n',encoding='utf8')
print(json.dumps(manifest,indent=2))
