"""NaN-column/direct-replay opportunity on the completed exposed first-D plan."""
from pathlib import Path
from datetime import datetime,timezone
import ast,hashlib,json,time
H=Path(__file__).resolve().parent
R=next(p for p in H.parents if (p/'competitions/floatlib/pins.json').is_file())
start=time.monotonic();sha=lambda p:hashlib.sha256(p.read_bytes()).hexdigest()
generator=R/'competitions/floatlib/candidates/f01-d7-research/round3h-20261024T112622Z/profile-analyze.py'
t=ast.parse(generator.read_text());fs=[x for x in t.body if isinstance(x,ast.FunctionDef) and x.name in ('word','element')]
env={'MASK64':(1<<64)-1};exec(compile(ast.Module(body=fs,type_ignores=[]),str(generator),'exec'),env)
element=env['element']
home=R/'competitions/floatlib/candidates/f01-mul-log2-proof1/ci-runs/40398675395/download-42cfe8ce05b24bf6bd145777f10a1729/diagnostics/f01-d7-public-suite/public-suite'
planpath=home/'public-drawn-plan.json';plan=json.loads(planpath.read_bytes())
work=json.loads((home/'public-cell-work.json').read_bytes());v=json.loads((home/'f01-r15-dev-packed-b2-1-verdict.json').read_bytes())
costs={c:work[c]*v['classes'][c]['submission_ns'] for c in work};whole=sum(costs.values())
rows=[]
for c in plan['cases']:
 if c['kernel']!='bmm' or not c['timed']:continue
 b,m,n,p=(c[k] for k in ('batch','m','n','p'))
 possible=c['mag']==2 or (c['specRate']>0 and ((c['specMask']&31)==0 or bool(c['specMask']&2)))
 row={'name':c['name'],'shape':[b,m,n,p],'full_B_words':b*n*p,'flag_slots':b*p,'first_B_checks':b*p,'source_possible_rawNaN':possible,'poison_columns':0,'first_B_NaN_columns':0,'scan_words_to_first_NaN':0,'native_MAC_terms_selected_by_column':0,'selected_output_count':0,'all_columns_poison_batch_count':0,'unchanged_pack_group_all_poison_valid_outputs':0,'replay_steps_upper_before_first_B_NaN':0}
 if not possible:row['scan_words_to_first_NaN']=b*n*p
 else:
  for batch in range(b):
   first=[]
   for j in range(p):
    hit=None
    for k in range(n):
     raw=element(c,(batch*n+k)*p+j,1,p);row['scan_words_to_first_NaN']+=1
     if raw&0x7fffffff>0x7f800000:hit=k;break
    first.append(hit)
    if hit is not None:
     row['poison_columns']+=1;row['selected_output_count']+=m;row['native_MAC_terms_selected_by_column']+=m*n
     row['first_B_NaN_columns']+=int(hit==0);row['replay_steps_upper_before_first_B_NaN']+=m*(hit+1)
   row['all_columns_poison_batch_count']+=int(p>0 and all(x is not None for x in first))
   # Keep retained paired/wide groups whole; do not pretend a poisoned lane alone removes the shared numeric loop.
   width=2 if 2<=p<=8 and n>1 and m>=4 else (10 if p>8 and n>4 else 1)
   for g in range((p+width-1)//width):
    group=first[width*g:min(width*(g+1),p)]
    if group and all(x is not None for x in group):row['unchanged_pack_group_all_poison_valid_outputs']+=m*len(group)
   assert time.monotonic()-start<9
 rows.append(row)
affected={':'.join(x['name'].split(':')[:2]) for x in rows if x['poison_columns']}
totals={k:sum(x[k] for x in rows) for k in ('full_B_words','flag_slots','first_B_checks','poison_columns','first_B_NaN_columns','scan_words_to_first_NaN','native_MAC_terms_selected_by_column','selected_output_count','all_columns_poison_batch_count','unchanged_pack_group_all_poison_valid_outputs','replay_steps_upper_before_first_B_NaN')}
totals['first_B_NaN_outputs']=sum(x['first_B_NaN_columns']*x['shape'][1] for x in rows)
totals['first_B_NaN_native_MAC_terms']=sum(x['first_B_NaN_columns']*x['shape'][1]*x['shape'][2] for x in rows)
out={'at_utc':datetime.now(timezone.utc).isoformat(),'seed':1927003,'plan_sha256':sha(planpath),'generator_translation_sha256':sha(generator),'totals':totals,'cases':rows,'touched_cells':sorted(affected),'complete_touched_cell_whole_time_upper':sum(costs[x] for x in affected)/whole,'proof_reuse':'R7NaNReplay.replayEarly_eq already all-input; choosing it via any flag requires no semantic soundness premise, only preserving actual addresses and output order. Poison flag is a performance policy.','scope':'Literal exposed-plan input model, not real BMM/NaN replay execution or time. First-NaN position only bounds unchanged raw replay from above; earlier invalid can stop earlier. Count of selected native MACs is not saved cycles. Shared B2/F10 groups require all valid lanes poison before the unchanged native group can be omitted.','elapsed_seconds':time.monotonic()-start}
(H/'nan-column-screen.json').write_text(json.dumps(out,indent=2)+'\n')
print(json.dumps({k:out[k] for k in ('seed','totals','touched_cells','complete_touched_cell_whole_time_upper','elapsed_seconds')}))
print(json.dumps([x for x in rows if x['poison_columns']],indent=2))
