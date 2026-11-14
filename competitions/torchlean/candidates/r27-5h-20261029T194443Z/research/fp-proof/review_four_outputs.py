from pathlib import Path
import json,hashlib
from datetime import datetime,timezone
H=Path(__file__).parent;P=H/'follow-on/SharedLeftFourFloat.lean';b=P.read_bytes();r=dict(at_utc=datetime.now(timezone.utc).isoformat(),state='PARENT_FOUR_OUTPUT_FOLLOW_ON_READ_AND_PREFERRED_AFTER_COST',path=P.relative_to(Path.cwd()).as_posix(),bytes=len(b),sha256=hashlib.sha256(b).hexdigest(),roots=['R27SharedLeftFourFloat.interleave_eq'],scope='Fourcolumns/sharedleft exactscalarsequence; noFloat reassociation orcommutativity assumption',proof='NOT_RUN',native='NOT_RUN',queued=False)
(H/'follow-on/shared-left-four-receipt.json').write_text(json.dumps(r,indent=2)+'\n',encoding='utf-8')
p=H/'follow-on/four-chain-v2-receipt.json';d=json.loads(p.read_bytes());d['priority_update']='Secondary; prefer parent4output exactscalarEq afterinitialnativecost/ASM. No largeproof orCI forperdotreassociation now.';p.write_text(json.dumps(d,indent=2)+'\n',encoding='utf-8')
print(json.dumps(r,indent=2))
