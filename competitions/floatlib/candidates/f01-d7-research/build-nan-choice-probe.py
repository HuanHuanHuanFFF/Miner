"""Build an append-only bridge probe; the exact retained runtime is unchanged."""
from pathlib import Path
import hashlib,json

root=Path(__file__).resolve().parents[1];parent=root/'f01-d7-direct-nonnan'
a=(parent/'Kernel.lean').read_bytes()
assert hashlib.sha256(a).hexdigest()=='60f74aa4af01a9b35ece66a7c310e6b05b5b84b9b7121a4cccd12a0a9c987e15'
block=(root/'f01-d7-research/nan-choice-block.lean').read_bytes()
out=root/'f01-d7-nan-choice-probe';out.mkdir(exist_ok=True);raw=a+b'\n\n'+block
assert raw[:len(a)]==a and len(raw)<256000
(out/'Kernel.lean').write_bytes(raw)
m={'candidate':out.name,'candidate_file':'Kernel.lean','candidate_sha256':hashlib.sha256(raw).hexdigest(),'candidate_bytes':len(raw),'validation_mode':'statement-only','proof_status':'NOT_RUN','parent':parent.name,'parent_sha256':hashlib.sha256(a).hexdigest(),'mechanism':'Statement-only exact raw UInt32 signaling-first NaN selection and quiet-bit proof, including Model.Spec and actual ExecFloat carrier add/mul bridges on selected words. Original four runtime kernels remain exact60f. No canonicalized NaN shortcut.','source_attribution':'FloatLib Team MIT fixed0d918 Model/Carrier.lean and ExecFloat/Backends/Word/Narrow/Packing.lean. New glue proof by D.','block_sha256':hashlib.sha256(block).hexdigest(),'formal_submission':'NOT_SUBMITTED'}
(out/'manifest.json').write_text(json.dumps(m,indent=2)+'\n',encoding='utf8')
print(json.dumps({'candidate':out.name,'sha256':m['candidate_sha256'],'bytes':len(raw)}))
