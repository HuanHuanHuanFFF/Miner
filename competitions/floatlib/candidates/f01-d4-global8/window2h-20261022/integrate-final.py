"""Compose exact full-gate parents; the resulting source still needs its own full gate."""
from pathlib import Path
import argparse,hashlib,json,re
ROOT=Path.cwd();CAND=ROOT/'competitions/floatlib/candidates';OWN=Path(__file__).resolve().parent
ap=argparse.ArgumentParser();ap.add_argument('--scalar',required=True);ap.add_argument('--matrix',required=True);ap.add_argument('--name',required=True);ap.add_argument('--inline-coordinates',action='store_true');a=ap.parse_args()
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
index_namespace='Packed8Index' if 'namespace Packed8Index\n' in suffix else 'Packed10Index'
assert ('namespace '+index_namespace+'\n') in suffix
word=word.replace('Packed8Index.',index_namespace+'.')
sum_marker='namespace Submission\n\nopen FloatLib.Floats Competition\n\ndef sum'
assert suffix.count(sum_marker)==1
pos=suffix.index(sum_marker);suffix=suffix[:pos]+word+suffix[pos:]
old='let result := NativeDecodeSum.loop x 0 (Float32.ofBits 0)';assert suffix.count(old)==1
suffix=suffix.replace(old,'let result := NativeDecodeSumWord.run x',1)
old='rw [NativeDecodeSum.loop_eq]';assert suffix.count(old)==1
suffix=suffix.replace(old,'rw [NativeDecodeSumWord.run_eq, NativeDecodeSum.loop_eq]',1)
source=prefix+suffix
if a.inline_coordinates:
    decode_parent=CAND/'f01-d4-decode-inline10/Kernel.lean'
    decode_bytes=decode_parent.read_bytes();decode_hash=hashlib.sha256(decode_bytes).hexdigest()
    assert any(r['kernel_sha256']==decode_hash and r['full_gate'] and r['passed'] for r in records)
    parents['coordinate_decode']=dict(candidate='f01-d4-decode-inline10',kernel_sha256=decode_hash,kernel_bytes=len(decode_bytes))
    # The unchanged total coordinate formula is exposed to erase temporary pairs.
    # The pure definition is identical even for zero dimensions.
    helper='''namespace Submission.OutputDecode

@[inline] def decode (m p q : Nat) : Nat \u00d7 Nat \u00d7 Nat :=
  let rowSize := m * p
  let b := if rowSize = 0 then 0 else q / rowSize
  let r := if rowSize = 0 then 0 else q % rowSize
  let i := if p = 0 then 0 else r / p
  let j := if p = 0 then 0 else r % p
  (b, i, j)

theorem decode_eq (m p q : Nat) : decode m p q = Competition.bmmDecodeC m p q := by
  rfl

end Submission.OutputDecode

'''
    old='let d := bmmDecodeC m p q.val';assert source.count(old)>0
    source=source.replace(old,'let d := Submission.OutputDecode.decode m p q.val')
    source=source.replace('import ContractTensor\n','import ContractTensor\n\n'+helper,1)
data=source.encode();assert data.startswith(b'import ContractTensor\n') and len(data)<=256000
out=CAND/a.name;out.mkdir();(out/'Kernel.lean').write_bytes(data)
for p in parents.values():p.pop('source',None)
manifest=dict(candidate=a.name,candidate_file='Kernel.lean',candidate_sha256=hashlib.sha256(data).hexdigest(),candidate_bytes=len(data),parents=parents,inline_coordinates=a.inline_coordinates,word_sum_index_lemmas_from=index_namespace,validation_mode='full-gate',proof_status='NOT_RUN',mechanism='Exact combination of full-gate accepted scalar add/mul/word-sum prefix and selected matrix organization. This integrated source requires its own full gate and independent frozen confirmation.',formal_submission='NOT_SUBMITTED')
(out/'manifest.json').write_bytes((json.dumps(manifest,indent=2)+'\n').encode());print(json.dumps(manifest))
