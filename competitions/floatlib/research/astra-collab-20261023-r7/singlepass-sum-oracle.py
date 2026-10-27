"""Finite original-word checks and source-condition counts, never hardware timings."""
from pathlib import Path
from datetime import datetime,timezone
import importlib.util,json,hashlib,random,time
H=Path(__file__).resolve().parent;ROOT=H.parents[3]
sp=importlib.util.spec_from_file_location('opportunity',H/'public-nonfinite-opportunity.py');P=importlib.util.module_from_spec(sp);sp.loader.exec_module(P);O=P.O
def classify(u):
 a=u&0x7fffffff
 if 0x0bffffff <= ((a-1)&0xffffffff):
  if a<0x7f800000:return 'table'
  if a==0x7f800000:return 'infinity'
  return 'nan'
 return 'low'
def run(xs,seed=0):
 acc=O.canon(seed);counts=dict(table=0,low=0,infinity=0,nan=0,suffix_words=0,native_adds=0,repair_adds=0)
 poisoned=False
 for u in xs:
  if poisoned:
   counts['suffix_words']+=1
   if O.snan(u):acc=u|0x400000
   continue
  branch=classify(u);counts[branch]+=1
  if branch=='nan':
   assert O.nan(u);acc=O.add(acc,u);assert O.nan(acc) and not O.snan(acc)
   counts['repair_adds']+=1;poisoned=True
  else:
   assert not O.nan(u);acc=O.native_model(O.add,acc,u);counts['native_adds']+=1
 return acc,counts
edge=[0,0x80000000,1,0x80000001,0x007fffff,0x00800000,0x0bffffff,0x0c000000,0x0c000001,0x3f800000,0xbf800000,0x7f7fffff,0xff7fffff,0x7f800000,0xff800000,0x7f800001,0xff800011,0x7fc00000,0xffc12345,0xffffffff]
r=random.Random(2026102323);traces=[]
for seed in edge:
 for x in edge:
  for y in edge:
   xs=[x,y];got,_=run(xs,seed);want=O.add(O.add(O.canon(seed),x),y);assert got==want;traces.append((seed,x,y,got))
for n in [0,1,2,3,8,31,32,33,128,1024]:
 for _ in range(120):
  xs=[r.choice(edge) if r.randrange(4)==0 else r.getrandbits(32) for i in range(n)]
  seed=r.getrandbits(32);got,_=run(xs,seed);want=O.canon(seed)
  for x in xs:want=O.add(want,x)
  assert got==want;traces.append((seed,n,got))
for u in edge+[r.getrandbits(32) for _ in range(100000)]:assert (classify(u)=='nan')==O.nan(u)
base=ROOT/'competitions/floatlib/candidates/f01-mul-log2-proof1/ci-runs/39840672791/download-81e3479e9e2b47249bf76c8d44eb2e62/diagnostics/f01-d7-public-suite/public-suite'
planpath=base/'public-drawn-plan.json';plan=json.loads(planpath.read_text());ap=ROOT/'competitions/floatlib/candidates/f01-d7-research/nonnan-input-nan-output-807.json';anchors={x['name']:x for x in json.loads(ap.read_text())['cases']};rows=[];start=time.monotonic()
for c in plan['cases']:
 if c['kernel']!='sum':continue
 n=c['length'];row=dict(name=c['name'],timed=c['timed'],outputs=c['batch'],source_words=n*c['batch'],checksum32=0,table=0,low=0,infinity=0,nan=0,suffix_words=0,native_adds=0,repair_adds=0);trace=hashlib.sha256()
 for b in range(c['batch']):
  xs=[P.element(c,b*n+k,0,n) for k in range(n)];q,counts=run(xs)
  for k,v in counts.items():row[k]+=v
  row['checksum32']=((row['checksum32']^q)*16777619)&0xffffffff;trace.update(q.to_bytes(4,'little'))
 anchor=anchors[c['name']];assert row['checksum32']==anchor['checksum32'];assert trace.hexdigest()==anchor['output_words_le_sha256']
 row['output_sha256']=trace.hexdigest();row['D_word_sha_and_actual_checksum_anchor_match']=True;rows.append(row)
 print(json.dumps({k:row[k] for k in ['name','native_adds','repair_adds','suffix_words']}),flush=True)
keys=['outputs','source_words','table','low','infinity','nan','suffix_words','native_adds','repair_adds'];totals={str(t):{k:sum(x[k] for x in rows if x['timed']==t) for k in keys} for t in [True,False]}
out=dict(completed_at_utc=datetime.now(timezone.utc).isoformat(),finite_trace_count=len(traces),finite_trace_sha256=hashlib.sha256(json.dumps(traces).encode()).hexdigest(),raw_branch_checks=100020,analysis_seconds=time.monotonic()-start,source_sha256=hashlib.sha256(Path(__file__).read_bytes()).hexdigest(),plan_sha256=hashlib.sha256(planpath.read_bytes()).hexdigest(),anchor_sha256=hashlib.sha256(ap.read_bytes()).hexdigest(),totals=totals,cases=rows,scope='Integer source model/public discovery807 only. Shared oracle/generator and actual checksums give finite anchors, not independent proof/hardware equivalence or time estimates. Table/low branch values modeled using known equivalent decoder; actual fusedLeanC/loop remains uncompiled. Native seeds are canonicalized; arbitrary rawNaN seed equality is not claimed.')
(H/'singlepass-sum-oracle.json').write_text(json.dumps(out,indent=2)+'\n');print(json.dumps(totals,indent=2))
