from pathlib import Path
import json,hashlib
from datetime import datetime,timezone
H=Path(__file__).parent;P=H/'follow-on/FourChainContractOnly.lean';s=(H/'numerics-v1/Sum3ContractOnly.lean').read_text(encoding='utf-8')+'\n'+(H/'follow-on/FourChain.lean.inc').read_text(encoding='utf-8-sig');P.write_text(s,encoding='utf-8',newline='\n');b=P.read_bytes()
r=dict(at_utc=datetime.now(timezone.utc).isoformat(),state='FOLLOW_ON_SOURCE_NOT_QUEUED',path=P.as_posix(),bytes=len(b),sha256=hashlib.sha256(b).hexdigest(),roots=['Submission.R27FourChain.merge_grid','Submission.R27FourChain.four_sums_enclosure'],difference='Four actual native Float folds plus3native merges; reuse SUM3 count-grid anderror proof, retain originalradius for3<=L<=30. No new gamma analysis.',remaining=['Exact array lane partition/producer connection','Actual native4chain runtime and fullcall cost','Full12 source-specific gate'],proof='NOT_RUN',performance='UNKNOWN',primary_priority='Lazyprepare native discriminator and currentchecker/producer smallproof feedback remain first')
(H/'follow-on/four-chain-receipt.json').write_text(json.dumps(r,indent=2)+'\n',encoding='utf-8');print(json.dumps(r,indent=2))
