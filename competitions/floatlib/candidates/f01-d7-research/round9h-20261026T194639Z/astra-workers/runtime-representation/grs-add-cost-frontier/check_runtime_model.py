"""UInt32 implementation-boundary check and old-discovery exposure; not Lean or timing."""
from pathlib import Path
import hashlib,json,importlib.util,random,time,datetime
from collections import defaultdict
HERE=Path(__file__).resolve().parent
ROOT=next(p for p in HERE.parents if (p/'DEVELOPMENT.md').exists())
ROUND=HERE.parents[2]
sha=lambda p:hashlib.sha256(p.read_bytes()).hexdigest()
def imp(name,p):
 s=importlib.util.spec_from_file_location(name,p);m=importlib.util.module_from_spec(s);s.loader.exec_module(m);return m
model_path=ROUND/'astra-grs-add-model.py';q=imp('root_grs',model_path)
gen_path=ROOT/'competitions/floatlib/candidates/f01-d7-research/round8h-20261024T190259Z/astra-public-input-domain.py';g=imp('public_gen',gen_path)
M=(1<<32)-1;B=1<<23
def numeric_bits(n):
 assert 0<n<1<<32
 h=n.bit_length()-1;r=q.rne(n,h-23)
 if r==2*B:r>>=1;h+=1
 return ((h+127)<<23)|(r-B)
def typed(u,v):
 eu,ev=(u>>23)&255,(v>>23)&255
 if ((eu-1)&M)>253 or ((ev-1)&M)>253:return None
 swap=(u&0x7fffffff)<(v&0x7fffffff)
 hi,lo,eh,el=(v,u,ev,eu) if swap else (u,v,eu,ev)
 a=((hi&0x7fffff)|B)<<3;b=((lo&0x7fffff)|B)<<3;d=(eh-el)&M
 assert b>0 and d<=253
 if d<32:j=(b>>(d%32))|int((b&(((1<<(d%32))-1)&M))!=0)
 else:j=1
 t=((a+j) if ((u^v)&0x80000000)==0 else (a-j))&M
 assert t<1<<28
 if not t:return 0
 mid=numeric_bits(t);e=((mid>>23)+eh-153)&M
 if ((e-1)&M)>253:return None
 return (hi&0x80000000)|((e<<23)&M)|(mid&0x7fffff)
def old_r16_hit(u,v):
 eu,ev=(u>>23)&255,(v>>23)&255
 if not (1<=eu<=254 and 1<=ev<=254):return False
 hi,lo,eh,el=(v,u,ev,eu) if eu<ev else (u,v,eu,ev)
 d=eh-el;same=((u^v)&0x80000000)==0
 if d>7 or not(same or d>=1):return False
 ma=(hi&0x7fffff)|B;mb=(lo&0x7fffff)|B
 n=((ma<<d)+mb if same else (ma<<d)-mb)&M
 if n<B:return False
 mid=numeric_bits(n);e=((mid>>23)+el-150)&M
 return ((e-1)&M)<=253
start=time.perf_counter();pairs=[]
for e in [1,2,3,4,24,127,254]:
 for d in [0,1,3,4,25,26,27,31,32,33,253]:
  if e-d<1:continue
  for f in [0,1,2,3,0x3fffff,0x400000,0x7ffffe,0x7fffff]:
   for h in [0,1,2,3,0x3fffff,0x400000,0x7ffffe,0x7fffff]:
    for sign in range(4):pairs.append(((sign&1)<<31|e<<23|f,(sign>>1)<<31|(e-d)<<23|h))
rng=random.Random(19272330);pairs += [(rng.getrandbits(32),rng.getrandbits(32)) for _ in range(20000)]
small_pairs=[(0x0c800000,0x8c7fffff),(0x8c7fffff,0x0c800000),(0x8c800000,0x0c7fffff),(0x0c7fffff,0x8c800000)]
pairs+=small_pairs
for u,v in pairs:
 assert time.perf_counter()-start<5
 assert typed(u,v)==q.proposal(u,v),(hex(u),hex(v))
plan=ROOT/'competitions/floatlib/candidates/f01-mul-log2-proof1/ci-runs/40168687803/download-13caf4644cf1467e8717d9474d417b8a/diagnostics/f01-d7-public-suite/public-suite/public-drawn-plan.json'
groups=defaultdict(lambda:{'sampled':0,'new_hit':0,'old_r16_hit':0,'new_only':0,'new_zero':0,'old_only':0});rows=[]
for c in json.loads(plan.read_text())['cases']:
 if c['kernel']!='add' or not c['timed']:continue
 n=min(256,c['work']);counts={k:0 for k in groups['unused']};counts['sampled']=n
 for z in range(n):
  assert time.perf_counter()-start<5
  lo,hi=z*c['work']//n,(z+1)*c['work']//n;i=lo+g.word(c['seed'],z,63)%(hi-lo)
  u=g.element(c,i,0,31);v=g.partner(c,i,u);value=typed(u,v);nh=value is not None;oh=old_r16_hit(u,v)
  counts['new_hit']+=nh;counts['old_r16_hit']+=oh;counts['new_only']+=nh and not oh;counts['new_zero']+=value==0;counts['old_only']+=oh and not nh
 name=':'.join(c['name'].split(':')[:2])
 for k,v in counts.items():groups[name][k]+=v
 rows.append({'case':c['name'],'work':c['work'],**counts})
groups.pop('unused')
out={'utc':datetime.datetime.now(datetime.timezone.utc).isoformat(),'state':'BOUNDED_TYPED_MODEL_AND_OLD_EXPOSED_DRAW_ONLY','runtime_fragment_sha256':sha(HERE/'Runtime-grs32-add.lean.inc'),
 'root_model_sha256':sha(model_path),'typed_pairs_checked':len(pairs),'typed_disagreements':0,'elapsed_seconds':time.perf_counter()-start,
 'exposure':{'source_run':40168687803,'plan_sha256':sha(plan),'generator_translation_sha256':sha(gen_path),'cases':rows,'groups':dict(groups)},
 'scope':'Checks exact UInt32 wrap/shift control against root integer proposal; original RNE correctness still depends on root proof. Exposure is256 stratified samples per completed old ADD case, not time or new holdout. Original same-sign GRS bench and R16 negatives remain.',
 'small_T_witnesses':[{'u':hex(u),'v':hex(v),'T':4,'numeric_bits':hex(numeric_bits(4)),'postE':1,'typed':hex(typed(u,v)),'oracle':hex(q.exact_add_normal(u,v))} for u,v in small_pairs],
 'lean':'NOT_RUN','codegen':'NOT_RUN','full_gate':'NOT_RUN','performance':'UNKNOWN','candidate_kernel_created':False}
(HERE/'model-and-exposure.json').write_text(json.dumps(out,indent=2)+'\n',encoding='utf-8')
print(json.dumps({'typed_pairs':len(pairs),'elapsed_seconds':out['elapsed_seconds'],'groups':dict(groups)}))
