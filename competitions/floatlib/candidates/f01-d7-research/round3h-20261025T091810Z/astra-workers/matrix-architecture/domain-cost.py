"""Conditioned allocation requests and rigorous class-time bounds, completed data only."""
from pathlib import Path
import json,time,hashlib
from datetime import datetime,timezone
H=Path(__file__).resolve().parent
R=next(p for p in H.parents if (p/'competitions/floatlib/pins.json').is_file())
start=time.monotonic()
def sha(p):return hashlib.sha256(p.read_bytes()).hexdigest()
def domain(c):
 b,m,n,p=(c[x] for x in ('batch','m','n','p'))
 if not(b and m>=4 and n>1 and p>=2):return 'miss'
 if p==2:return 'p2'
 if p<=8:return 'p3to8'
 if n<=4:return 'wide_short_n'
 return 'wide_long_n'
def requests(c):
 b,m,n,p=(c[x] for x in ('batch','m','n','p'));g=(p+1)//2;h=m//4;t=m%4
 return dict(A4_panel_bytes=b*h*(32*n+24),F8_tiles_bytes=b*h*(48*g+24),
  old_B2_fullrow_F2_bytes=b*h*64*g,
  delta_vs_B2_fullrows_bytes=b*h*(32*n+48-16*g),
  A4_record_count=b*h*n,panel_array_count=b*h,F8_record_count=b*h*g,tile_array_count=b*h,
  old_A_conversion_count=b*m*g*n,new_A_conversion_count=b*(4*h+t*g)*n,
  unchanged_B2_pack_major_bytes=b*g*(24*n+24)+24+8*b*g,
  G=g,H=h,T=t,
  new_peak_panel_and_tiles_upper_bytes=32*n+24+48*g+24,
  new_peak_scope='one panel plus one complete tile vector; excludes input,globalB,output,closures,allocator')
old=json.loads((H/'analysis.json').read_text());out=[]
for group in old['groups']:
 files={k:R/v['path'] for k,v in group['evidence'].items()}
 for k,f in files.items():assert sha(f)==group['evidence'][k]['sha256']
 plan,work,v=(json.loads(files[k].read_text()) for k in ('plan','work','verdict'))
 costs={k:work[k]*r['submission_ns'] for k,r in v['classes'].items()};whole=sum(costs.values())
 cases=[c for c in plan['cases'] if c['timed'] and c['kernel']=='bmm']
 domains=[]
 for name in ('p2','p3to8','wide_short_n','wide_long_n','miss'):
  rows=[c for c in cases if domain(c)==name]
  cells={':'.join(c['name'].split(':')[:2]) for c in rows}
  pure={cell for cell in cells if all(domain(c)==name for c in cases if ':'.join(c['name'].split(':')[:2])==cell)}
  detail=[dict(name=c['name'],shape={k:c[k] for k in ('batch','m','n','p','work')},request_model=requests(c)) for c in rows if name!='miss']
  sums={k:sum(d['request_model'][k] for d in detail) for k in ('A4_panel_bytes','F8_tiles_bytes','old_B2_fullrow_F2_bytes','delta_vs_B2_fullrows_bytes','A4_record_count','panel_array_count','F8_record_count','tile_array_count','old_A_conversion_count','new_A_conversion_count')}
  domains.append(dict(domain=name,cases=len(rows),cells=sorted(cells),
    shape_whole_time_lower=sum(costs[k] for k in pure)/whole,
    shape_whole_time_upper=sum(costs[k] for k in cells)/whole,
    optimized_subwork_time_lower=0,
    optimized_subwork_time_upper=sum(costs[k] for k in cells)/whole,
    conditional_request_totals=sums,detail=detail,
    comparison_is_actual_B2_source=name in ('p2','p3to8')))
 out.append(dict(run=group['run'],seed=group['seed'],domains=domains))
profile=R/'competitions/floatlib/candidates/f01-d7-research/round3h-20261024T112622Z/profile-whole-multi-analysis-40099316795.json'
pd=json.loads(profile.read_text());old_bounds=[]
for seed in pd['seeds']:
 cases=[c for c in seed['cases'] if c['timed']]
 whole=sum(c['whole_process_mean_ns'] for c in cases)
 rows=[]
 for name in ('p2','p3to8','wide_short_n','wide_long_n'):
  selected=[c for c in cases if c['kernel']=='bmm' and domain(c['shape'])==name]
  rows.append(dict(domain=name,case_count=len(selected),
   old_DF_target_whole_call_share=sum(c['whole_process_mean_ns'] for c in selected)/whole,
   old_DF_known_underflow_share=sum(c['whole_process_mean_ns'] for c in selected if 'Zero' in c['route']['route'] or 'underflow' in c['route']['route'].lower())/whole,
   cases=[dict(name=c['name'],shape=c['shape'],route=c['route']['route'],whole_ns=c['whole_process_mean_ns']) for c in selected]))
 old_bounds.append(dict(seed=seed['seed'],rows=rows))
assert time.monotonic()-start<4.5
record=dict(at_utc=datetime.now(timezone.utc).isoformat(),status='CONDITIONAL_REQUEST_MODEL_AND_OLD_TIME_BOUNDS',
 current_B2_groups=out,old_DF_profile=dict(path=str(profile.relative_to(R)),sha256=sha(profile),groups=old_bounds),
 assumptions=['New A4/F8 layout still awaits actual C','64-bit8B header,24B array header,8B aligned constructors and exact-capacity arrays','All selected shape guards miss underflow-zero; raw actual value classification not recomputed','No conditional request amount is measured physical allocation or time','B2 event comparison is actual current path only p2..8','Class-time upper bounds overlap and must not be summed','Old DF profile numbers do not transfer to current622d'],elapsed_seconds=time.monotonic()-start)
(H/'domain-cost.json').write_text(json.dumps(record,indent=2)+'\n')
print(json.dumps(dict(seconds=record['elapsed_seconds'],groups=[dict(run=g['run'],domains=[dict(domain=d['domain'],cases=d['cases'],lower=d['shape_whole_time_lower'],upper=d['shape_whole_time_upper'],delta=d['conditional_request_totals']['delta_vs_B2_fullrows_bytes']) for d in g['domains']]) for g in out],old_DF=[dict(seed=g['seed'],bounds=[{k:d[k] for k in ('domain','case_count','old_DF_target_whole_call_share')} for d in g['rows']]) for g in old_bounds])))
