"""Expose unchanged row-major decode logic at the output projection site."""
from pathlib import Path
import hashlib,json
ROOT=Path(__file__).resolve().parents[1];OUT=Path(__file__).resolve().parent
raw=(ROOT/'f01-d4-packed10/Kernel.lean').read_bytes();assert hashlib.sha256(raw).hexdigest()=='21d446f4cbdebc955dbed6b49990ba201d224b7776aa30c60b2710537d9f71d0'
s=raw.decode()
contract=ROOT.parents[0]/'research/astra-collab-20261022/web/R2-W01c/original-extracted/FloatLib_R2-W01c/public_sources/official/lean/contract/ContractTensor.lean'
data=contract.read_bytes();text=data.decode();a=text.index('def bmmDecodeC ');b=text.index('/-- The bmm slot',a);definition=text[a:b].replace('def bmmDecodeC','@[inline] def inlineDecodeC',1)
extra=definition+'''theorem inlineDecodeC_eq (m p q : Nat) :
    inlineDecodeC m p q = bmmDecodeC m p q := by
  rfl

'''
a=s.index('def outputFromTiles (');b=s.index('theorem outputFromTiles_eq',a);block=s[a:b];assert block.count('let d := bmmDecodeC m p q.val')==1
block=block.replace('let d := bmmDecodeC m p q.val','let d := inlineDecodeC m p q.val',1)
s=s[:a]+extra+block+s[b:];data=s.encode();(OUT/'Kernel.lean').write_bytes(data)
m=dict(candidate=OUT.name,candidate_file='Kernel.lean',candidate_sha256=hashlib.sha256(data).hexdigest(),candidate_bytes=len(data),parent='f01-d4-packed10',validation_mode='full-gate',proof_status='NOT_RUN',mechanism='Exact original coordinate-decode body marked inline at output projection. Removes the opaque per-output tuple-return boundary if compiler cancels the pair constructors; arithmetic, guards and every proof unchanged except a new rfl helper.',copied_contract_sha256=hashlib.sha256(contract.read_bytes()).hexdigest(),performance='NOT_RUN')
(OUT/'manifest.json').write_bytes((json.dumps(m,indent=2)+'\n').encode());print(m)
