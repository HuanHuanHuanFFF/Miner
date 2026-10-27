"""Bounded source-derived check of the new gap>=1/high-N UInt32 runtime, not Lean."""
from pathlib import Path
from datetime import datetime,timezone
import hashlib,json,random,runpy,subprocess,sys,time
H=Path(__file__).resolve().parent
SHA='2f998811caa348ad7c0e66026b0d049c6ce0720549dd12622345777d24a1e13e'
def worker():
 t=time.perf_counter();g=runpy.run_path(str(H/'add-u32-screen.py'))
 ex,m,sg,bits=g['exp'],g['mant'],g['sign'],g['bits'];U=(1<<32)-1
 assert hashlib.sha256((H/'Kernel-add-native-high-draft1.lean').read_bytes()).hexdigest()==SHA
 pairs=[];ms=(0,1,0x3fffff,0x400000,0x7ffffe,0x7fffff)
 for a in (1,23,24,126,127,150,246,253,254):
  for d in (0,1,2,7,8):
   if a+d>254:continue
   for x in ms:
    for y in ms:
     for s in range(4):pairs.append((((a+d)<<23)|x|((s&1)<<31),(a<<23)|y|((s>>1)<<31)))
 rng=random.Random(202610251053)
 for _ in range(2048):
  a=rng.randrange(1,255);b=max(1,min(254,a+rng.randrange(-8,9)))
  pairs.append((a<<23|rng.getrandbits(23)|rng.getrandbits(1)<<31,b<<23|rng.getrandbits(23)|rng.getrandbits(1)<<31))
 assert len(pairs)<=9000
 errors=[];accepted=0;gap1=0;zero_fallback=0
 for u,v in pairs:
  assert time.perf_counter()-t<4.5
  hi,lo=(v,u) if ex(u)<ex(v) else (u,v);d=ex(hi)-ex(lo)
  same=sg(u)==sg(v);got=None
  if 1<=ex(u)<=254 and 1<=ex(v)<=254 and d<=7 and (same or d>=1):
   left=(m(hi)<<d)&U;right=m(lo)
   n=(left+right if same else left-right)&U
   if n>=8388608:
    mid=bits(float(n));e=(ex(mid)+ex(lo)-150)&U
    if ((e-1)&U)<=253:got=(0x80000000 if sg(hi) else 0)|((e&255)<<23)|(mid&0x7fffff)
  a,N,s=g['raw_alignment'](u,v);ref=g['round_exact'](s,N,a-150)
  expected=g['proposed'](u,v) if N>=8388608 else None
  if got!=expected:errors.append(['domain_or_value',hex(u),hex(v),got,expected])
  if got is not None:
   accepted+=1;gap1+=int(not same and d==1)
   if got!=ref:errors.append(['reference',hex(u),hex(v),got,ref])
  zero_fallback+=int(N==0 and got is None)
 out={'created_utc':datetime.now(timezone.utc).isoformat(),'source_sha256':SHA,'state':'FINITE_SOURCE_MODEL_ONLY',
  'cases':len(pairs),'accepted':accepted,'opposite_gap1_accepted':gap1,'zero_fallback':zero_fallback,'errors':errors,
  'elapsed_seconds':time.perf_counter()-t,'limits':{'cases':9000,'internal_seconds':4.5,'external_timeout_seconds':5},
  'scope':'New unsigned sorted runtime versus original exact-N high-only domain and integer reference. No active CI data, no native Lean runtime, proof or benchmark.'}
 print(json.dumps(out,indent=2));return bool(errors)
if __name__=='__main__':
 if '--worker' in sys.argv:sys.exit(worker())
 t=time.perf_counter();p=subprocess.run([sys.executable,str(Path(__file__)),'--worker'],capture_output=True,text=True,timeout=5)
 (H/'high-entry-model.stdout.txt').write_text(p.stdout,encoding='utf-8');(H/'high-entry-model.stderr.txt').write_text(p.stderr,encoding='utf-8')
 assert p.returncode==0,p.stderr or p.stdout
 r=json.loads(p.stdout);r['controller_seconds']=time.perf_counter()-t;r['worker_exit_code']=p.returncode
 (H/'high-entry-model.json').write_text(json.dumps(r,indent=2)+'\n',encoding='utf-8');print(json.dumps(r,indent=2))
