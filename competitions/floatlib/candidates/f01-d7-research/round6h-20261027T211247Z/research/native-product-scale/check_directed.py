"""Small exact-source-model discriminator for the newUInt64 frontend; no native/Lean run."""
from pathlib import Path
from datetime import datetime,timezone
import importlib.util,hashlib,json
HERE=Path(__file__).resolve().parent
ROOT=next(p for p in HERE.parents if (p/'AGENTS.md').exists())
ORACLE=ROOT/'competitions/floatlib/research/astra-collab-20261023-r7/nonfinite-oracle.py'
sp=importlib.util.spec_from_file_location('r22_exact_word_model',ORACLE);O=importlib.util.module_from_spec(sp);sp.loader.exec_module(O)
MASK=(1<<32)-1
def scale_bits(j):
    e=j&255;s=(j&256)<<23
    return s|((e-23)<<23) if 24<=e<=254 else s
def guard(u,v):
    eu=(u>>23)&255;ev=(v>>23)&255;s=eu+ev
    return ((eu-1)&MASK)<=253 and ((ev-1)&MASK)<=253 and ((s-174)&MASK)<=206
def proposed(u,v):
    s=((u>>23)&255)+((v>>23)&255)
    a=(u&0x7fffff)|0x800000;b=(v&0x7fffff)|0x800000
    p=a*b;first=O.rounded(p,0)
    w=(((s-150)&MASK)<<23)&MASK|((u^v)&0x80000000)
    scale=scale_bits(w>>23)
    return O.mul(first,scale),first,scale,p
mantissas=[(8388608,8388608),(8388608,8388609),(8388609,16777214),(16777215,16777215),
           (8390656,8390656),(8390656,8394752),(12584960,12587008),(12589056,12595200)]
count=0;trace=hashlib.sha256();named=[]
for s in (174,175,254,255,300,379,380):
 for eu in sorted({max(1,s-254),s//2,min(254,s-1)}):
  ev=s-eu
  if not(1<=eu<=254 and 1<=ev<=254):continue
  for a,b in mantissas:
   for su,sv in ((0,0),(0,1),(1,0),(1,1)):
    u=(su<<31)|(eu<<23)|(a-8388608);v=(sv<<31)|(ev<<23)|(b-8388608)
    assert guard(u,v)
    got,first,scale,p=proposed(u,v);want=O.mul(u,v)
    assert got==want,(s,eu,a,b,su,sv,hex(got),hex(want))
    assert 0<O.exp(got)<255 and 0<O.exp(scale)<255
    count+=1;trace.update(b''.join(x.to_bytes(4,'little') for x in (u,v,first,scale,got)))
    if su==sv==0 and eu==s//2 and s in (174,380) and (a,b) in mantissas[:4]:
      named.append({'S':s,'a':a,'b':b,'P':p,'first_bits':f'{first:08x}','scale_bits':f'{scale:08x}','output_bits':f'{got:08x}'})
for e in range(256):assert (((e-1)&MASK)<=253)==(1<=e<=254)
for s in range(511):assert (((s-174)&MASK)<=206)==(174<=s<=380)
u=86<<23;v=87<<23
bad,first,scale,p=proposed(u,v)
assert not guard(u,v) and bad!=O.mul(u,v) and scale==0
out={'checked_utc':datetime.now(timezone.utc).isoformat(),'state':'DIRECTED_FIXED_DOMAIN_WORD_MODEL_PASS',
 'runtime_sha256':hashlib.sha256((HERE/'Runtime.lean.inc').read_bytes()).hexdigest(),
 'oracle_sha256':hashlib.sha256(ORACLE.read_bytes()).hexdigest(),'cases':count,
 'fixed_guard_class_checks':767,'trace_sha256':trace.hexdigest(),'boundary_rows':named,
 'S173_existing_table_counterexample':{'u':f'{u:08x}','v':f'{v:08x}','correct':f'{O.mul(u,v):08x}','forced_core':f'{bad:08x}','scale':f'{scale:08x}','actual_guard_rejects':True},
 'scope':'Selectedexactinteger/sourceword cases only; actualUInt64cast semantics separately have old6589proof support. No newLean/hardware/performance/fullMUL proof. Bounds fixed mathematically, not threshold search.'}
(HERE/'directed-check.json').write_text(json.dumps(out,indent=2)+'\n',encoding='utf-8')
print(json.dumps(out,indent=2))
