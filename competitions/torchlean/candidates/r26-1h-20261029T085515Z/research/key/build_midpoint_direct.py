from pathlib import Path
import hashlib,json
from datetime import datetime,timezone
H=Path('competitions/torchlean/candidates/r26-1h-20261029T085515Z/research/key')
fs=['MidpointFields.lean.inc','MidpointRealDirect.lean.inc','MidpointSignedDirect.lean.inc']
text=(H/'ActualCheckerContractOnly.lean').read_text(encoding='utf-8')
for n in fs:text+='\n'+(H/'follow-on'/n).read_text(encoding='utf-8-sig')
p=H/'follow-on/MidpointDirectContractOnly.lean';p.write_text(text,encoding='utf-8',newline='\n')
rec=dict(at_utc=datetime.now(timezone.utc).isoformat(),source=p.as_posix(),bytes=p.stat().st_size,sha256=hashlib.sha256(p.read_bytes()).hexdigest(),fragments=[dict(path=n,sha256=hashlib.sha256((H/'follow-on'/n).read_bytes()).hexdigest()) for n in fs],roots=['Submission.R25Checker.mag32_fields','Submission.R25Checker.minnormal_fields','Submission.R25Checker.above_decode_fields','Submission.R25Checker.below_decode_fields_inner','Submission.R25Checker.below_decode_fields_power','Submission.R25Checker.below_decode_fields_minnormal','Submission.R25Checker.unsigned_midpoint_values','Submission.R25Checker.signed_midpoint_values','Submission.R25Checker.eWord_eq_native','Submission.R25Checker.fWord_eq_native'],proof='NOT_RUN',purpose='Bypass old R24 Widen/NativeSignOr/MidpointWords closure; direct raw_value to actual q midpoint cells',CI_request='NONE; independent follow-on while primary probes wait',local_Lean=False)
(H/'follow-on/midpoint-direct-receipt.json').write_text(json.dumps(rec,indent=2)+'\n',encoding='utf-8');print(json.dumps(rec,indent=2))
