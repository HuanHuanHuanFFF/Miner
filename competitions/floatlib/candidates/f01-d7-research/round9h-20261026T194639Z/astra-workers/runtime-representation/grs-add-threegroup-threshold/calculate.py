"""Same fixed256/case sample scheme; old exposed runs only; cost proxy, not timing."""
from pathlib import Path
from collections import defaultdict
from types import SimpleNamespace
import ast,datetime,hashlib,importlib.util,json,statistics
HERE=Path(__file__).resolve().parent
ROOT=next(p for p in HERE.parents if (p/'DEVELOPMENT.md').exists())
ROUND=HERE.parent.parent.parent
RUNS=(40168687803,40169957447,40171180249)
H=lambda b:hashlib.sha256(b).hexdigest()

def bind(p,expected=None):
 b=p.read_bytes();h=H(b)
 if expected:assert h==expected,(str(p),h)
 return {'path':str(p.relative_to(ROOT)).replace('\\','/'),'bytes':len(b),'sha256':h}

def main():
 oldmodel=HERE.parent/'grs-add-cost-frontier/model-and-exposure.json';previous=json.loads(oldmodel.read_text())
 modelp=HERE.parent/'grs-add-cost-frontier/check_runtime_model.py';rootp=ROUND/'astra-grs-add-model.py'
 genp=ROUND.parent/'round8h-20261024T190259Z/astra-public-input-domain.py'
 bindings=[bind(oldmodel),bind(modelp),bind(rootp,previous['root_model_sha256']),bind(genp,previous['exposure']['generator_translation_sha256'])]
 # Load only definitions: avoid old scripts' main work, writes, or unrelated plan reads.
 rnens={};tree=ast.parse(rootp.read_text());rnedef=next(n for n in tree.body if isinstance(n,ast.FunctionDef) and n.name=='rne')
 exec(compile(ast.Module(body=[rnedef],type_ignores=[]),str(rootp),'exec'),rnens)
 ns={'M':(1<<32)-1,'B':1<<23,'q':SimpleNamespace(rne=rnens['rne'])}
 tree=ast.parse(modelp.read_text());defs=[n for n in tree.body if isinstance(n,ast.FunctionDef) and n.name in ('numeric_bits','typed','old_r16_hit')]
 exec(compile(ast.Module(body=defs,type_ignores=[]),str(modelp),'exec'),ns)
 gt=ast.parse(genp.read_text());gns={'U32':(1<<32)-1,'U64':(1<<64)-1}
 exec(compile(ast.Module(body=[n for n in gt.body if isinstance(n,ast.FunctionDef)],type_ignores=[]),str(genp),'exec'),gns)
 results=[]
 for run in RUNS:
  runp=ROOT/'competitions/floatlib/candidates/f01-mul-log2-proof1/ci-runs'/str(run)
  receipt=json.loads((runp/'original-artifact-hashes.json').read_text());download=runp/receipt['directory'];suite=download/'diagnostics/f01-d7-public-suite/public-suite'
  paths=[suite/'public-drawn-plan.json',suite/'public-cell-work.json',suite/'f01-r15-dev-packed-b2-1-verdict.json',suite/'inputs/f01-r15-dev-packed-b2-1/Kernel.lean',suite/'provenance.json']
  rows=[]
  for p in paths:
   key=str(p.relative_to(download)).replace('\\','/');row=receipt['files'][key];rows.append(bind(p,row['sha256']))
  assert rows[3]['sha256']=='622d8394a7127e93dcaf992c62c6dfcff7208d212738409a5e34525dfafd1a58'
  plan=json.loads(paths[0].read_text());work=json.loads(paths[1].read_text());verdict=json.loads(paths[2].read_text())
  assert verdict['passed'] and verdict['stage']=='score' and len(verdict['rounds'])==25
  assert verdict['verifier_fingerprint']==verdict['verifier_fingerprint_end']
  assert set(work)==set(verdict['classes']) and len(work)==26
  counts=defaultdict(lambda:defaultdict(float));cases=[]
  for c in plan['cases']:
   if c['kernel']!='add' or not c['timed']:continue
   n=min(256,c['work']);cell=':'.join(c['name'].split(':')[:2]);cr=dict(sampled=n,normal=0,new_hit=0,postE_hit_nonzero=0,new_zero=0,normal_postE_miss=0,old_r16_hit=0,new_only=0,old_only=0)
   for z in range(n):
    lo,hi=z*c['work']//n,(z+1)*c['work']//n;i=lo+gns['word'](c['seed'],z,63)%(hi-lo)
    u=gns['element'](c,i,0,31);v=gns['partner'](c,i,u)
    normal=1<=((u>>23)&255)<=254 and 1<=((v>>23)&255)<=254
    value=ns['typed'](u,v);nh=value is not None;oh=ns['old_r16_hit'](u,v)
    for k,val in [('normal',normal),('new_hit',nh),('postE_hit_nonzero',nh and value!=0),('new_zero',value==0),('normal_postE_miss',normal and not nh),('old_r16_hit',oh),('new_only',nh and not oh),('old_only',oh and not nh)]:cr[k]+=int(val)
   cases.append({'case':c['name'],'work':c['work'],**cr})
   for k,v in cr.items():counts[cell][k]+=v
   counts[cell]['work']+=c['work']
   for k in ('normal','new_hit','postE_hit_nonzero','new_zero','normal_postE_miss','old_r16_hit','new_only','old_only'):
    counts[cell][k+'_work_proxy']+=c['work']*cr[k]/n
  if run==RUNS[0]:
   for new,old in zip(cases,previous['exposure']['cases']):
    assert all(new[k]==old[k] for k in ('case','work','sampled','new_hit','old_r16_hit','new_only','new_zero','old_only'))
  totalcost=sum(work[k]*verdict['classes'][k]['submission_ns'] for k in work)
  addcost=0;newcost=0;oldcost=0;misswork=0
  for cell,c in counts.items():
   assert c['work']==work[cell]
   c['B2_cell_ns_per_work']=verdict['classes'][cell]['submission_ns'];cost=work[cell]*c['B2_cell_ns_per_work'];addcost+=cost
   c['B2_cell_cost_proxy_ns']=cost;c['B2_whole_cost_share_proxy']=cost/totalcost
   for k in ('normal','new_hit','postE_hit_nonzero','new_zero','normal_postE_miss','old_r16_hit','new_only','old_only'):
    c[k+'_work_rate']=c[k+'_work_proxy']/work[cell]
   c['new_eligible_whole_cost_proxy']=cost*c['new_hit_work_rate']/totalcost
   c['old_eligible_whole_cost_proxy']=cost*c['old_r16_hit_work_rate']/totalcost
   newcost+=cost*c['new_hit_work_rate'];oldcost+=cost*c['old_r16_hit_work_rate'];misswork+=work[cell]*(1-c['new_hit_work_rate'])
  totals={k:int(sum(c[k] for c in counts.values())) for k in ('sampled','normal','new_hit','postE_hit_nonzero','new_zero','normal_postE_miss','old_r16_hit','new_only','old_only')}
  fnew=newcost/totalcost;fold=oldcost/totalcost
  results.append({'run':run,'seed':verdict['seed'],'provenance':json.loads(paths[4].read_text()),'bindings':rows,'counts':totals,'cells':dict(counts),'cases':cases,
    'B2_total_cost_proxy_ns':totalcost,'ADD_share_proxy':addcost/totalcost,'new_eligible_whole_cost_proxy':fnew,'old_eligible_whole_cost_proxy':fold,
    'new_eligible_reduction_for_10pct_zero_miss_overhead':.1/fnew,'old_eligible_reduction_for_10pct_zero_miss_overhead':.1/fold,
    'new_eligible_speedup_for_10pct_zero_miss_overhead':1/(1-.1/fnew),
    'whole_penalty_per_1ns_added_miss_guard_proxy':misswork/totalcost,
    'cost_scope':'sum of B2 class median ns/work times original cell work; not median whole gate time; eligible/miss assumed equal old cost within each cell'})
 result={'utc':datetime.datetime.now(datetime.timezone.utc).isoformat(),'status':'HISTORICAL_EQUAL_COST_EXPOSURE_PROXY_NOT_PERFORMANCE','bindings':bindings,'runs':results,
   'method':'Exact same256 stratified points per timedADD case as prior first-group study. Per-cell hit rates weighted by each original case work. No sample expansion, future inputs or Lean execution.',
   'caveats':['Python generator translation has not been independently aligned against Lean execution.','Sample frequencies are not timings, probabilities or strict benefit upper bounds.','Old eligible and miss cost distributions within each cell may differ.','New miss guard cost UNKNOWN; required reduction=(0.10+whole miss penalty)/eligible whole cost proxy.','Real new eligible-path cost must include its guard, alignment, call and fallback preparation costs.'],
   'candidate_written':False,'Lean':'NOT_RUN','CI_dispatch':0}
 (HERE/'results.json').write_text(json.dumps(result,indent=2)+'\n',encoding='utf-8',newline='\n')
 print(json.dumps([{'run':r['run'],**r['counts'],'ADDshare':r['ADD_share_proxy'],'Fnew':r['new_eligible_whole_cost_proxy'],'Fold':r['old_eligible_whole_cost_proxy'],'required_drop':r['new_eligible_reduction_for_10pct_zero_miss_overhead'],'speedup':r['new_eligible_speedup_for_10pct_zero_miss_overhead']} for r in results],indent=2))

if __name__=='__main__':main()
