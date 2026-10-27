from pathlib import Path
from datetime import datetime, timezone
import hashlib,json
ROOT=Path(__file__).resolve().parents[4];HERE=Path(__file__).resolve().parent
base=ROOT/'competitions/floatlib/candidates/f01-d6-notnan-probe/Kernel.lean'
b=base.read_bytes();assert hashlib.sha256(b).hexdigest()=='dfef26d57326c442fbfef79dc6368a23703271f70ac015a65e851bac7f3968f9'
out=b+b'\n'+(HERE/'nonnan-native-block.lean').read_bytes()
d=ROOT/'competitions/floatlib/candidates/f01-r7-nonnan-bridge-probe';d.mkdir(exist_ok=True)
(d/'Kernel.lean').write_bytes(out)
m={'candidate':d.name,'candidate_file':'Kernel.lean','candidate_sha256':hashlib.sha256(out).hexdigest(),'candidate_bytes':len(out),'parent':'f01-d6-notnan-probe','parent_sha256':hashlib.sha256(b).hexdigest(),'validated_runtime_ancestor':'f01-d5-stream-pack 8eb63a2f','created_at_utc':datetime.now(timezone.utc).isoformat(),'proof_status':'NOT_RUN','validation_mode':'statement-only','mechanism':'Complete binary32 native add/mul model bridge for non-NaN inputs, including infinity and invalid operations producing canonical NaN. Reuse accepted finite bridge, explicit infinity cases and actual Model/Configured/ExecFloat interfaces. Existing runtime entry points unchanged.','expected_gain':'UNKNOWN; this probe closes the operation-spec gap required to expand terminal-finite guards to terminal-non-NaN in sum/BMM. No performance claim until actual integration and public-suite gate.','formal_submission':'NOT_SUBMITTED'}
(d/'manifest.json').write_text(json.dumps(m,indent=2)+'\n');print(json.dumps(m,indent=2))
