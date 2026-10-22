"""Repair the exact statement507 error: select the multiplication core namespace explicitly."""
from pathlib import Path
import hashlib,json
ROOT=Path(__file__).resolve().parents[1];OUT=Path(__file__).resolve().parent
raw=(ROOT/'f01-d4-balanced-package/Kernel.lean').read_bytes()
assert hashlib.sha256(raw).hexdigest()=='df3d6369dc668b63b7c9cae42e7ac330cdc7dad1960926632c3ae2d633324d6c'
s=raw.decode();base=(ROOT/'f01-d3-final-package/Kernel.lean').read_text()
a=base.index('@[inline] def core (xBits yBits : UInt32)',base.index('namespace FastMul\n'));b=base.index('/-- One operand is a NaN',a);correct=base[a:b].replace('  roundP sign','  roundSelect sign')
assert 'xMantissa * yMantissa' in correct and 'if xScale' not in correct
a=s.index('@[inline] def core (xBits yBits : UInt32)',s.index('namespace LowScale\n'));b=s.index('theorem core_eq (a b : UInt32)',a);s=s[:a]+correct+'\n'+s[b:]
data=s.encode();(OUT/'Kernel.lean').write_bytes(data)
m=dict(candidate=OUT.name,candidate_file='Kernel.lean',candidate_sha256=hashlib.sha256(data).hexdigest(),candidate_bytes=len(data),validation_mode='full-gate',proof_status='NOT_RUN',parent='f01-d4-balanced-package',repair='Explicit FastMul namespace for core extraction; retains original507failedsource andreceipt.',mechanism='Decodedadd, USize ordered sum, cheap subnormal software multiply, original8lane bmm.')
(OUT/'manifest.json').write_bytes((json.dumps(m,indent=2)+'\n').encode());print(m)
# The conservative package has no LowScale runtime dependency; drop the unused block.
raw=(ROOT/'f01-d4-add-sum-word/Kernel.lean').read_bytes();assert hashlib.sha256(raw).hexdigest()=='5d4dc76ef5b6403537510ceb6a82637e2b31be9bd891ce753477615cfaf17a46'
s=raw.decode();a=s.index('namespace LowScale\n');b=s.index('end LowScale',a)+len('end LowScale');s=s[:a]+s[b:];data=s.encode();out=ROOT/'f01-d4-add-sum-word-proof1';out.mkdir(exist_ok=True);(out/'Kernel.lean').write_bytes(data);m.update(candidate=out.name,candidate_sha256=hashlib.sha256(data).hexdigest(),candidate_bytes=len(data),parent='f01-d4-add-sum-word',repair='Remove unused broken LowScale block; original exported native mul unchanged.',mechanism='Numeric decoder only for add and USize ordered sum; originalnative mul/8lanebmm.');(out/'manifest.json').write_bytes((json.dumps(m,indent=2)+'\n').encode());print(m)
