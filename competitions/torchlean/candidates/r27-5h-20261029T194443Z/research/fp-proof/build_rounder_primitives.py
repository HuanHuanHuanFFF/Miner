from pathlib import Path
import hashlib,json
from datetime import datetime,timezone
H=Path(__file__).parent;ROOT=Path.cwd();R=ROOT/'competitions/floatlib/candidates/f01-d7-research/round7h-20261028T203856Z'
paths=[R/'development-broad/CellPrimitive-v2.lean.inc',R/'development-scalar/quotient-boundary/RescaleNative32.lean.inc',R/'research/scalar/midpoint/DyadicAgreement.lean.inc']
s='import ContractExact\n\n'+'\n\n'.join(p.read_text(encoding='utf-8-sig') for p in paths)
(H/'rounder-v1').mkdir(exist_ok=True);p=H/'rounder-v1/RounderPrimitivesContractOnly.lean';p.write_text(s,encoding='utf-8',newline='\n');b=p.read_bytes()
r=dict(at_utc=datetime.now(timezone.utc).isoformat(),state='PREPARED_NOT_QUEUED_AFTER_REAL_CHECKER_PRIORITY',path=p.relative_to(ROOT).as_posix(),bytes=len(b),sha256=hashlib.sha256(b).hexdigest(),helper_roots=['Submission.R24CellPrimitive.quotient_strict_midpoint','Submission.R24CellPrimitive.quotient_even_closed_midpoint','Submission.R24CellPrimitive.native32_strict_cell','Submission.R24RescaleNative32.roundRatScaled_rescale','Submission.R24DyadicAgreement.roundDyadic_eq_roundRatScaled'],inputs=[dict(path=x.relative_to(ROOT).as_posix(),sha256=hashlib.sha256(x.read_bytes()).hexdigest()) for x in paths],scope='Independent base cell/scale/dyadic rational primitives; no actual midpoint integration, normal-power cases or producer proof claimed. Avoid waiting until final closure to expose unrelated primitive type errors.',proof='NOT_RUN',local_Lean=False,formal_submission=False)
(H/'rounder-v1/receipt.json').write_text(json.dumps(r,indent=2)+'\n',encoding='utf-8')
p=H/'CI-REQUEST-003.json';d=json.loads(p.read_bytes());d['optional_rounder_primitive']=r;p.write_text(json.dumps(d,ensure_ascii=False,indent=2)+'\n',encoding='utf-8')
print(json.dumps(r,indent=2))
