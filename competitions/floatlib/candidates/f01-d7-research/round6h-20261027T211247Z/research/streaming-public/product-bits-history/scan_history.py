"""R9-R20 top-level source scan only; excludes current confirmation sources."""
from pathlib import Path
from datetime import datetime,timezone
import re,json,hashlib
HERE=Path(__file__).resolve().parent
ROOT=next(p for p in HERE.parents if (p/'competitions/floatlib/pins.json').is_file())
base=ROOT/'competitions/floatlib/candidates';files=[];hits=[];all_bits=[]
for p in sorted(base.glob('*/Kernel.lean')):
 name=p.parent.name;m=re.match(r'f01-r(\d+)-',name)
 if not m or not 9<=int(m.group(1))<=20:continue
 raw=p.read_bytes();s=raw.decode('utf-8-sig');lines=s.splitlines()
 files.append(dict(path=str(p.relative_to(ROOT)),bytes=len(raw),sha256=hashlib.sha256(raw).hexdigest()))
 starts=[i for i,l in enumerate(lines) if re.match(r'^(?:@\[[^\]]+\]\s*)?(?:private\s+)?(?:def|abbrev|theorem|structure|namespace|end)\b',l)]
 for a,b in zip(starts,starts[1:]+[len(lines)]):
  if not re.match(r'^(?:@\[[^\]]+\]\s*)?(?:private\s+)?def\b',lines[a]):continue
  body='\n'.join(lines[a:b]);shape=dict(candidate=name,line=a+1,definition=lines[a],body_sha256=hashlib.sha256(body.encode()).hexdigest())
  if 'toFloat32' in body and ('toBits' in body or 'ofFloat32' in body):
   all_bits.append(shape)
   if 'UInt64' in body or '.toUInt64' in body:hits.append(shape)
report=dict(at_utc=datetime.now(timezone.utc).isoformat(),phase_start_utc='2026-10-28T02:46:45Z',phase_limit_utc='2026-10-28T02:56:45Z',
 kernels=len(files),files=files,direct_same_def_UInt64_native_bits_hits=hits,all_native_bits_def_summaries=all_bits,
 scope='Bounded literal same-def scan only; not whole-history absence, not codegen/timing. No R21/R22 or confirmation source scanned.',
 outcome='No exact measured complete caller located; different historical negative mechanisms retained. No new candidate/CI.')
(HERE/'manifest.json').write_text(json.dumps(report,ensure_ascii=False,indent=2)+'\n',encoding='utf-8')
print(json.dumps({k:report[k] for k in ['at_utc','kernels','direct_same_def_UInt64_native_bits_hits','outcome']}))
