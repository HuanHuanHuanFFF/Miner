"""Controlled combination: address-hoisted tensor + previously full-gate verified mul."""
from pathlib import Path
import hashlib,json
OWN=Path(__file__).resolve().parent;CAND=OWN.parent
tensor=(CAND/'f01-index-hoist-proof1/Kernel.lean').read_text(encoding='utf-8')
mul=(CAND/'f01-rebuilt-mul-proof1/Kernel.lean').read_text(encoding='utf-8')
start=mul.index('namespace RebuiltMul\n');end=mul.index('end RebuiltMul',start)+len('end RebuiltMul')
block=mul[start:end]+'\n'
source=tensor.replace('end FastMul\n','end FastMul\n'+block,1)
source=source.replace('def mul (x y : Binary32) : Binary32 := FastMul.mul x y','def mul (x y : Binary32) : Binary32 := RebuiltMul.mul x y').replace(':= FastMul.mul_spec\n',':= RebuiltMul.mul_spec\n')
(OWN/'Kernel.lean').write_bytes(source.encode())
(OWN/'manifest.json').write_bytes((json.dumps({'candidate':OWN.name,'kernel_sha256':hashlib.sha256(source.encode()).hexdigest(),'kernel_bytes':len(source.encode()),'components':['f01-index-hoist-proof1','f01-rebuilt-mul-proof1'],'mechanism':'Controlled combination: invariant bmm address bases and fixed-width normalized product pipeline','proof_status':'NOT_RUN_COMBINED','validation_mode':'full-gate','benchmark':'NOT_RUN; do not add component gains'},indent=2)+'\n').encode())
print(OWN.name,hashlib.sha256(source.encode()).hexdigest(),len(source.encode()))
