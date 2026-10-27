"""Conditional route event coverage from exact completed B2 plans, never timing by shape."""
from pathlib import Path
from datetime import datetime, timezone
import hashlib
import json
from collections import defaultdict

HERE = Path(__file__).resolve().parent
ROOT = next(p for p in HERE.parents if (p / 'competitions/floatlib/pins.json').is_file())
audit = json.loads((HERE/'source-cost-audit.json').read_text(encoding='utf-8'))
sha = lambda p: hashlib.sha256(p.read_bytes()).hexdigest()

def route(c):
    if c['batch']*c['m']*c['p'] == 0:
        return 'empty'
    m,n,p = (c[k] for k in ('m','n','p'))
    if 2 <= p <= 8 and n > 1 and m >= 4:
        return 'B2_raw_A_Nat'
    if m >= 4 and n > 1 and 0 < p <= 2:
        return 'B1_raw_A_Nat'
    if (n <= 4 and p > 2) or p <= 8:
        return 'Direct_raw_AB_Nat'
    if n <= 4 or p <= 2:
        return 'DirectSmall_raw_AB_Nat'
    if n == 0:
        return 'reference_n0'
    return 'F10_prepared_A_USize'

groups = []
for old in audit['completed_groups']:
    paths = {k:ROOT/r['path'] for k,r in old['evidence'].items()}
    for k,p in paths.items():
        assert sha(p) == old['evidence'][k]['sha256']
    plan,work,verdict = (json.loads(paths[k].read_text()) for k in ('plan','work','verdict'))
    cost = {k:work[k]*v['submission_ns'] for k,v in verdict['classes'].items()}
    whole = sum(cost.values())
    buckets = defaultdict(list)
    for c in plan['cases']:
        if c['kernel']=='bmm' and c['timed']:
            buckets[route(c)].append(c)
    rows=[]
    for key,cases in sorted(buckets.items()):
        cells={':'.join(c['name'].split(':')[:2]) for c in cases}
        dot_groups = sum(c['batch']*c['m']*((c['p']+1)//2 if key=='B2_raw_A_Nat' else c['p']) for c in cases)
        ksteps = sum(c['batch']*c['m']*((c['p']+1)//2 if key=='B2_raw_A_Nat' else c['p'])*c['n'] for c in cases)
        hist=defaultdict(lambda:dict(output_groups=0,k_steps=0,shapes=0))
        for c in cases:
            n=c['n']; bucket='n1' if n==1 else 'n2to4' if n<=4 else 'n5to16' if n<=16 else 'n17plus'
            g=c['batch']*c['m']*((c['p']+1)//2 if key=='B2_raw_A_Nat' else c['p'])
            hist[bucket]['output_groups']+=g
            hist[bucket]['k_steps']+=g*n
            hist[bucket]['shapes']+=1
        rows.append(dict(route=key,shape_count=len(cases),touched_classes=sorted(cells),
                         touched_class_whole_upper=sum(cost[k] for k in cells)/whole,
                         actual_time_lower=0, conditional_output_groups=dot_groups,
                         conditional_k_steps=ksteps,
                         conditional_mean_n_per_group=ksteps/dot_groups if dot_groups else None,
                         conditional_n_histogram=dict(hist),
                         shapes=[dict(name=c['name'],shape={k:c[k] for k in ('batch','m','n','p')}) for c in cases]))
    raw_routes=[r for r in rows if r['route'] in ('B2_raw_A_Nat','B1_raw_A_Nat','Direct_raw_AB_Nat','DirectSmall_raw_AB_Nat')]
    raw_cells=set().union(*(set(r['touched_classes']) for r in raw_routes))
    groups.append(dict(run=old['run'],seed=old['seed'],routes=rows,
                       raw_index_union_class_whole_upper=sum(cost[k] for k in raw_cells)/whole,
                       raw_index_actual_time_lower=0))
record=dict(at_utc=datetime.now(timezone.utc).isoformat(),state='CONDITIONAL_SOURCE_ROUTES_COMPLETED_INPUTS',groups=groups,
            scope='Exact 622d shape guards after an UNKNOWN underflow-zero miss. No value generation, stage timing, or route-time attribution.',
            limits=['Touched class bounds overlap; never sum them',
                    'k-step/output counts include all loops of the selected source route, not dynamic underflow entries',
                    'F10 counts are scalar-output-normalized workload only; its actual kernel is 10-wide and already has USize indexing',
                    'Class time must not be distributed by shape counts, MAC counts, or conditional output counts'])
(HERE/'route-coverage.json').write_text(json.dumps(record,ensure_ascii=False,indent=2)+'\n',encoding='utf-8')
print(json.dumps([dict(run=g['run'],routes=[{k:r[k] for k in ('route','shape_count','conditional_mean_n_per_group','touched_class_whole_upper')} for r in g['routes']]) for g in groups],indent=2))
