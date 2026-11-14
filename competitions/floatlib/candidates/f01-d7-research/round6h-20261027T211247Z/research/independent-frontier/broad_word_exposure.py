"""Frozen broad-word guard exposure on three old plans; no correctness expansion."""
from pathlib import Path
from datetime import datetime,timezone
import importlib.util,json,hashlib,time
D=Path(__file__).resolve().parent
spec=importlib.util.spec_from_file_location('gen',D/'same_exponent_add.py');M=importlib.util.module_from_spec(spec);spec.loader.exec_module(M)
runtime=D/'Runtime-broad-word-add.lean.inc';assert hashlib.sha256(runtime.read_bytes()).hexdigest()=='5655df5c8a8fbfbf40101bba782788d4a59ee716a95ab8e2bd58bff05e715bf9'
st=time.monotonic();runs=[]
for run in [40168687803,40169957447,40171180249]:
 base=M.R/f'competitions/floatlib/candidates/f01-mul-log2-proof1/ci-runs/{run}';idx=json.loads((base/'original-artifact-hashes.json').read_bytes());pre='diagnostics/f01-d7-public-suite/public-suite/'
 plan,ph=M.load_checked(base,idx,pre+'public-drawn-plan.json');verdict,vh=M.load_checked(base,idx,pre+'f01-r15-dev-packed-b2-1-verdict.json');work,wh=M.load_checked(base,idx,pre+'public-cell-work.json');costs={k:v['submission_ns']*work[k] for k,v in verdict['classes'].items()};total=sum(costs.values());groups={}
 for c in plan['cases']:
  if c['kernel']!='add' or not c['timed']:continue
  cell=':'.join(c['name'].split(':')[:2]);g=groups.setdefault(cell,{'samples':0,'normal_same_sign':0,'far_direct':0,'GRS_core':0})
  for j in range(256):
   lo,hi=j*c['work']//256,(j+1)*c['work']//256;i=lo+M.E['word'](c['seed'],j,63)%(hi-lo)
   u=M.E['element'](c,i,0,31);v=M.partner(c,i,u);eu,ev=(u>>23)&255,(v>>23)&255;hit=(u^v)<0x80000000 and 1<=eu<=254 and 1<=ev<=254
   g['samples']+=1;g['normal_same_sign']+=hit;g['far_direct']+=hit and abs(eu-ev)>=25;g['GRS_core']+=hit and abs(eu-ev)<=24
 for cell,g in groups.items():
  g['cell_share_whole']=costs[cell]/total
  for k in ['normal_same_sign','far_direct','GRS_core']:g[k+'_equal_cost_proxy']=g['cell_share_whole']*g[k]/g['samples']
 runs.append({'run':run,'plan_sha256':ph,'verdict_sha256':vh,'work_sha256':wh,'groups':groups,'proxy_NOT_upper_bound_or_speed':{k:sum(g[k+'_equal_cost_proxy'] for g in groups.values()) for k in ['normal_same_sign','far_direct','GRS_core']}})
out={'at_utc':datetime.now(timezone.utc).isoformat(),'runtime_sha256':hashlib.sha256(runtime.read_bytes()).hexdigest(),'state':'FROZEN_GUARD_SOURCE_TRANSCRIPTION_ONLY','runs':runs,'elapsed_seconds':time.monotonic()-st,'script_sha256':hashlib.sha256(Path(__file__).read_bytes()).hexdigest(),'scope':'256 deterministic strata per timed ADD case, three already exposed R15 draws. Cell-weighted hit proxy assumes uniform within-cell cost and is NOT a measured saved time, upper bound, speed estimate or future probability. Guard/source unchanged after reading results.'}
(D/'broad-word-exposure.json').write_text(json.dumps(out,indent=2)+'\n',encoding='utf8',newline='\n');print(json.dumps({'runs':[{'run':r['run'],**r['proxy_NOT_upper_bound_or_speed']} for r in runs],'elapsed_seconds':out['elapsed_seconds']}))
