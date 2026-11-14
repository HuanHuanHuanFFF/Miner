from pathlib import Path
import hashlib,json
from datetime import datetime,timezone
H=Path('competitions/torchlean/candidates/r26-1h-20261029T085515Z/research/key')
K=Path('competitions/torchlean/candidates/r26-1h-20261029T085515Z/development/native/fp1/Kernel.lean')
source=K.read_text(encoding='utf-8');start=source.index('@[inline] def finite64 (word : UInt64)');end=source.index('def sumRemaining',start);block=source[start:end]
old=Path('competitions/torchlean/candidates/r25-90m-20261029T064916Z/research/order-key/ActualRuntime.lean.inc').read_text(encoding='utf-8')
oldblock=old[old.index('@[inline] def finite64'):old.index('\n\nend Submission.R24PortableF64')].strip();assert oldblock==block.strip()
identity=Path('competitions/torchlean/candidates/r25-90m-20261029T064916Z/research/order-key/RuntimeIdentity.lean.inc').read_text(encoding='utf-8')
contents=(H/'ActualCheckerContractOnly.lean').read_text(encoding='utf-8')+'\nnamespace Submission.R24PortableF64\n'+block+'\nend Submission.R24PortableF64\n'+identity
p=H/'follow-on/RuntimeIdentityContractOnly.lean';p.write_text(contents,encoding='utf-8',newline='\n');b=p.read_bytes()
rec=dict(at_utc=datetime.now(timezone.utc).isoformat(),path=p.as_posix(),bytes=len(b),sha256=hashlib.sha256(b).hexdigest(),actual_development_kernel_path=K.as_posix(),actual_development_kernel_sha256=hashlib.sha256(K.read_bytes()).hexdigest(),actual_definition_block_sha256=hashlib.sha256(block.encode()).hexdigest(),R25_runtime_block_text_identical=True,roots=['Submission.R25Checker.finite64_eq_runtime','Submission.R25Checker.orderKey_eq_runtime','Submission.R25Checker.certify_eq_runtime','Submission.R25Checker.actual_acceptance_bounds'],proof='NOT_RUN',axioms='NOT_RUN',native='NOT_RUN',local_Lean=False)
(H/'follow-on/runtime-identity-receipt.json').write_text(json.dumps(rec,indent=2)+'\n',encoding='utf-8');print(json.dumps(rec,indent=2))
