from pathlib import Path
import hashlib,json
from datetime import datetime,timezone
H=Path('competitions/torchlean/candidates/r26-1h-20261029T085515Z/research/key')
plan=json.loads((H/'probe-plan.json').read_text(encoding='utf-8'))
tail='''\nnamespace Submission\ndef kernels : ExactRuntime.Kernels := ExactRuntime.specKernels\ntheorem correct : ExactRuntime.Obligation kernels := rfl\nend Submission\n'''
rows=[]
for entry in plan['probes'][:3]:
 src=Path(entry['path']);d=H/'carriers'/entry['name'];d.mkdir(parents=True,exist_ok=True)
 p=d/'Kernel.lean';p.write_text(src.read_text(encoding='utf-8')+tail,encoding='utf-8',newline='\n')
 b=p.read_bytes();rows.append(dict(name=entry['name'],path=p.as_posix(),bytes=len(b),sha256=hashlib.sha256(b).hexdigest(),helper_roots=entry['helper_roots'],source_sha256=entry['sha256'],runtime='ExactRuntime.specKernels; helper proof carrier only',measurement='NOT_REQUESTED'))
(H/'carrier-plan.json').write_text(json.dumps(dict(at_utc=datetime.now(timezone.utc).isoformat(),candidates=rows,formal_submission=False,proof='NOT_RUN',purpose='Optional tiny original-gate carrier if D lacks direct diagnostic compile; no native prototype Correct is claimed'),indent=2)+'\n',encoding='utf-8');print(json.dumps(rows,indent=2))
