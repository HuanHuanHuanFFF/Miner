"""Compose exact full-gate parents; the resulting source still needs its own full gate."""
from pathlib import Path
import argparse,hashlib,json,re
ROOT=Path.cwd();CAND=ROOT/'competitions/floatlib/candidates';OWN=Path(__file__).resolve().parent
ap=argparse.ArgumentParser();ap.add_argument('--scalar',required=True);ap.add_argument('--matrix',required=True);ap.add_argument('--name',required=True);a=ap.parse_args()
assert re.fullmatch(r'f01-d4-final-[a-z0-9-]+',a.name)
records=json.loads((OWN/'summary.json').read_bytes())['records']
parents={}
for role,name in [('scalar',a.scalar),('matrix',a.matrix)]:
    assert re.fullmatch(r'f01-[a-z0-9-]+',name)
    p=CAND/name/'Kernel.lean';data=p.read_bytes();digest=hashlib.sha256(data).hexdigest()
    assert any(r['kernel_sha256']==digest and r['full_gate'] and r['passed'] for r in records),(role,name,'not full-gate accepted')
    parents[role]=dict(candidate=name,kernel_sha256=digest,kernel_bytes=len(data),source=data.decode())
scalar=parents['scalar']['source'];matrix=parents['matrix']['source']
marker='namespace FinalFinite\n';assert scalar.count(marker)==matrix.count(marker)==1
prefix=scalar[:scalar.index(marker)];suffix=matrix[matrix.index(marker):]
assert prefix.count('namespace R2W01b\n')==1
start=suffix.index('namespace R2W01b\n');end=suffix.index('namespace Submission.NativeDecodeSum\n')
suffix=suffix[:start]+suffix[end:]
word_start=scalar.index('namespace Submission.NativeDecodeSumWord\n');word_end=scalar.index('end Submission.NativeDecodeSumWord',word_start)+len('end Submission.NativeDecodeSumWord')
word=scalar[word_start:word_end]+'\n\n'
sum_marker='namespace Submission\n\nopen FloatLib.Floats Competition\n\ndef sum'
assert suffix.count(sum_marker)==1
pos=suffix.index(sum_marker);suffix=suffix[:pos]+word+suffix[pos:]
old='let result := NativeDecodeSum.loop x 0 (Float32.ofBits 0)';assert suffix.count(old)==1
suffix=suffix.replace(old,'let result := NativeDecodeSumWord.run x',1)
old='rw [NativeDecodeSum.loop_eq]';assert suffix.count(old)==1
suffix=suffix.replace(old,'rw [NativeDecodeSumWord.run_eq, NativeDecodeSum.loop_eq]',1)
data=(prefix+suffix).encode();assert data.startswith(b'import ContractTensor\n') and len(data)<=256000
out=CAND/a.name;out.mkdir();(out/'Kernel.lean').write_bytes(data)
for p in parents.values():p.pop('source')
manifest=dict(candidate=a.name,candidate_file='Kernel.lean',candidate_sha256=hashlib.sha256(data).hexdigest(),candidate_bytes=len(data),parents=parents,validation_mode='full-gate',proof_status='NOT_RUN',mechanism='Exact combination of full-gate accepted scalar add/mul/word-sum prefix and selected matrix organization. This integrated source requires its own full gate and independent frozen confirmation.',formal_submission='NOT_SUBMITTED')
(out/'manifest.json').write_bytes((json.dumps(manifest,indent=2)+'\n').encode());print(json.dumps(manifest))
