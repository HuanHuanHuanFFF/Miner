"""Source-bound integer classification only; no Lean or Float32 execution."""
from pathlib import Path
from datetime import datetime,timezone
import hashlib,json,re
HERE=Path(__file__).resolve().parent
ROOT=next(p for p in HERE.parents if (p/'competitions/floatlib/pins.json').is_file())
sha=lambda b:hashlib.sha256(b).hexdigest()
def rec(p):
 b=p.read_bytes();return dict(path=str(p.relative_to(ROOT)),bytes=len(b),sha256=sha(b))
primary=json.loads((HERE/'primary/source-index.json').read_bytes())
for z in primary['files']:
 b=(HERE/'primary'/z['name']).read_bytes()
 assert len(b)==z['bytes'] and sha(b)==z['sha256']
 assert hashlib.sha1(b'blob '+str(len(b)).encode()+b'\0'+b).hexdigest()==z['git_blob_sha1']
catalog=(HERE/'primary/Format-Catalog.lean').read_text()
section=catalog[catalog.index('def binary32'):catalog.index('def binary64')]
assert 'expWidth := 8' in section and 'fracWidth := 23' in section
qnan=(((1<<8)-1)<<23) | (1<<(23-1));assert qnan==0x7fc00000
fracs=[0,1,0x3fffff,0x400000,0x400001,0x7fffff]
cases=[];killed=set()
for sign in [0,1]:
 for e in range(256):
  for f in fracs:
   u=(sign<<31)|(e<<23)|f
   expected=qnan if e==255 and f!=0 else u
   actual=u if (u&0x7fffffff)<=0x7f800000 else qnan
   assert actual==expected
   if (u if (u&0x7fffffff)<0x7f800000 else qnan)!=expected:killed.add('strict_less_rejects_infinity')
   if (u if u<=0x7f800000 else qnan)!=expected:killed.add('omit_absolute_mask')
   if (u if e!=255 or f==0 else u|0x400000)!=expected:killed.add('quiet_only_preserves_payload_or_sign')
   cases.append(u)
assert len(cases)==3072 and len(killed)==3
base=ROOT/'competitions/floatlib/candidates/f01-r15-dev-packed-b2-1/Kernel.lean'
bridge=HERE.parents[1]/'floatarray-bridge-review/NativeTarget.lean.inc'
assert sha(base.read_bytes())=='622d8394a7127e93dcaf992c62c6dfcff7208d212738409a5e34525dfafd1a58'
assert sha(bridge.read_bytes())=='fb7d71540db5b0fee7ae9a9b73440b10224713ebd646c4cd812d145c4dfbc1b1'
proof=HERE/'ExpectedNativeWord.lean.inc';roots=re.findall(r'(?m)^theorem (\w+)',proof.read_text())
frozen={n:rec(HERE.parent/'floatarray-storage'/n) for n in ['Runtime.lean.inc','Kernel-probe.lean','CheckedPrefix.lean.inc']}
assert [z['sha256'] for z in frozen.values()]==[
'f5a6cbc6a89ccccd1e08cb861ce483d447d9b8dc30feed21ef24a2f30e5cacf8',
'303a239716b2521a72093453f7d363553055bc2702f481a09837a6ed53724da1',
'91ac9aa73ad8ae2a29bed7d08a901da27af45c1324d6854aa56ef6eacd4a6b93']
out=dict(created_at_utc=datetime.now(timezone.utc).isoformat(),phase_start_utc='2026-10-28T01:50:33Z',
 phase_limit_utc='2026-10-28T02:10:33Z',common_deadline_utc='2026-10-28T03:12:47Z',
 source=rec(proof),roots=['Submission.R22ExpectedNativeWord.'+n for n in roots],
 dependencies=[rec(base),rec(bridge)],canonical_word=hex(qnan),integer_cases=len(cases),
 mutations_killed=sorted(killed),frozen_floatarray_sources=frozen,formal='NOT_RUN',CI=False,
 runtime_integrated=False,native_cost='UNKNOWN',
 scope='3 mathematical interfaces. Constant derived from pinned format source and old canonicalNaN bridge. Finite checks cover integer classification only; not Lean/Float32/cast validation.')
(HERE/'manifest.json').write_text(json.dumps(out,ensure_ascii=False,indent=2)+'\n',encoding='utf-8')
print(json.dumps({k:out[k] for k in ['created_at_utc','source','roots','integer_cases','formal']},ensure_ascii=False))
