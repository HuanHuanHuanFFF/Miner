"""Bounded R16 architecture analysis. Reads completed R15 evidence only."""
from pathlib import Path
import hashlib, json, time
from datetime import datetime, timezone

HERE = Path(__file__).resolve().parent
ROOT = next(p for p in HERE.parents if (p/'competitions/floatlib/pins.json').is_file())
BASE = ROOT/'competitions/floatlib/candidates/f01-r15-dev-packed-b2-1/Kernel.lean'
assert hashlib.sha256(BASE.read_bytes()).hexdigest() == '622d8394a7127e93dcaf992c62c6dfcff7208d212738409a5e34525dfafd1a58'
start=time.monotonic()
def sha(p): return hashlib.sha256(p.read_bytes()).hexdigest()
groups=[]
for run in (40168687803,40169957447,40171180249):
    runroot=ROOT/f'competitions/floatlib/candidates/f01-mul-log2-proof1/ci-runs/{run}'
    paths=list(runroot.glob('download-*/diagnostics/f01-d7-public-suite/public-suite'))
    assert len(paths)==1
    folder=paths[0]
    files={k:folder/v for k,v in dict(plan='public-drawn-plan.json',work='public-cell-work.json',verdict='f01-r15-dev-packed-b2-1-verdict.json').items()}
    plan,work,verdict=(json.loads(files[k].read_text()) for k in ('plan','work','verdict'))
    assert verdict['passed'] and len(verdict['rounds'])==25
    cost={k:verdict['classes'][k]['submission_ns']*v for k,v in work.items()}
    total=sum(cost.values()); bc=sum(v for k,v in cost.items() if k.startswith('bmm:'))
    selected=[]; selected_cells=set(); existing_cells=set()
    for c in plan['cases']:
        if c['kernel']!='bmm' or not c['timed']: continue
        b,m,n,p=(c[x] for x in ('batch','m','n','p'))
        cell=':'.join(c['name'].split(':')[:2])
        if m<4 or n<=1 or p<2: continue
        selected_cells.add(cell)
        if p<=8:existing_cells.add(cell)
        g=(p+1)//2; h=m//4; tail=m%4
        selected.append(dict(name=c['name'],shape={x:c[x] for x in ('batch','m','n','p')},
          is_existing_B2_domain=p<=8,
          full_block_rows=b*4*h,tail_rows=b*tail,
          B2_source_model=dict(A_conversions=b*m*g*n,B_record_reads=b*m*g*n,k_iterations=b*m*g*n,F2_results=b*m*g),
          A4B2_source_model=dict(A_conversions=b*(4*h+tail*g)*n,A4_records=b*h*n,B_record_reads=b*(h+tail)*g*n,k_iterations=b*(h+tail)*g*n,F8_results=b*h*g,F2_tail_results=b*tail*g,temporary_tile_slots=b*h*g),
          unchanged=dict(B_conversions=b*2*g*n,B2_records=b*g*n,valid_finish_calls=b*m*p,MAC_pairs_including_odd_column=b*m*2*g*n)))
    groups.append(dict(run=run,seed=verdict['seed'],evidence={k:dict(path=str(p.relative_to(ROOT)),sha256=sha(p)) for k,p in files.items()},
      BMM_whole_share=bc/total,whole_reduction_if_all_BMM_2x=bc/total/2,
      touched_cell_upper_bound_whole=sum(cost[k] for k in selected_cells)/total,
      existing_B2_touched_cell_upper_bound_whole=sum(cost[k] for k in existing_cells)/total,
      selected_shape_count=len(selected),selected=selected,
      selected_case_time='UNKNOWN; class-level time cannot be allocated by MAC counts or shape counts'))
checks=0
for batch in range(3):
 for m in range(10):
  for n in range(6):
   for p in range(10):
    outputs=[]
    for b in range(batch):
     for h in range(m//4):
      tiles={}
      for g in range((p+1)//2):
       for r in range(4):
        for l in range(2):
         row=b*m+4*h+r
         tiles[g,r,l]=[(row*n+k,b*n*p+2*g+l+k*p) for k in range(n)]
      for r in range(4):
       for j in range(p):
        row=b*m+4*h+r
        assert tiles[j//2,r,j%2]==[(row*n+k,b*n*p+j+k*p) for k in range(n)]
        outputs.append((row,j));checks+=1
     for r in range(4*(m//4),m):
      outputs.extend((b*m+r,j) for j in range(p))
    assert outputs==[(r,j) for r in range(batch*m) for j in range(p)]
    assert time.monotonic()-start<4.5
record=dict(at_utc=datetime.now(timezone.utc).isoformat(),status='FINITE_ADDRESS_TRACE_AND_COMPLETED_R15_COST_ONLY',
 baseline_sha256=sha(BASE),baseline_bytes=BASE.stat().st_size,groups=groups,finite_output_traces=checks,
 trace_domain=dict(batch='0..2',m='0..9',n='0..5',p='0..9'),
 elapsed_seconds=time.monotonic()-start,limitations=['No new timings or compiled code','No floating-point equality established by finite traces','B2 source-model comparison for p>8 is counterfactual: current baseline actually selects Packed10/other paths','Class touched upper bounds include untargeted shapes, preparation, replay, output; not attainable gain'])
(HERE/'analysis.json').write_text(json.dumps(record,indent=2)+'\n')
print(json.dumps(dict(traces=checks,seconds=record['elapsed_seconds'],groups=[{k:g[k] for k in ('run','BMM_whole_share','whole_reduction_if_all_BMM_2x','selected_shape_count','touched_cell_upper_bound_whole')} for g in groups])))
