"""Paper all-normal domain screen; same old strata, no new runtime or correctness tests."""
from pathlib import Path
from datetime import datetime, timezone
import importlib.util, json, hashlib, time
D = Path(__file__).resolve().parent
spec = importlib.util.spec_from_file_location('gen', D/'same_exponent_add.py')
M = importlib.util.module_from_spec(spec); spec.loader.exec_module(M)
KEYS = ['all_normal', 'same_sign', 'opposite', 'opposite_d01', 'opposite_d2_25', 'opposite_far26', 'opposite_exact_cancel']
start = time.monotonic(); runs = []
for run in [40168687803, 40169957447, 40171180249]:
    base = M.R/f'competitions/floatlib/candidates/f01-mul-log2-proof1/ci-runs/{run}'
    index = json.loads((base/'original-artifact-hashes.json').read_bytes())
    pre = 'diagnostics/f01-d7-public-suite/public-suite/'
    plan, ph = M.load_checked(base,index,pre+'public-drawn-plan.json')
    verdict, vh = M.load_checked(base,index,pre+'f01-r15-dev-packed-b2-1-verdict.json')
    work, wh = M.load_checked(base,index,pre+'public-cell-work.json')
    costs = {k:v['submission_ns']*work[k] for k,v in verdict['classes'].items()}
    total = sum(costs.values()); groups = {}
    for case in plan['cases']:
        if case['kernel'] != 'add' or not case['timed']: continue
        cell = ':'.join(case['name'].split(':')[:2])
        g = groups.setdefault(cell, {'samples': 0, **{k:0 for k in KEYS}})
        for j in range(256):
            low, high = j*case['work']//256, (j+1)*case['work']//256
            i = low+M.E['word'](case['seed'],j,63)%(high-low)
            u = M.E['element'](case,i,0,31); v = M.partner(case,i,u)
            eu, ev = (u>>23)&255, (v>>23)&255
            normal = 1<=eu<=254 and 1<=ev<=254
            same = normal and (u^v)<0x80000000
            opp = normal and not same; gap = abs(eu-ev)
            hits = [normal, same, opp, opp and gap<=1, opp and 2<=gap<=25,
                    opp and gap>=26, opp and (u&0x7fffffff)==(v&0x7fffffff)]
            g['samples'] += 1
            for k,h in zip(KEYS,hits): g[k] += h
    for cell,g in groups.items():
        g['whole_cell_share'] = costs[cell]/total
        g['equal_cost_proxies'] = {k:g['whole_cell_share']*g[k]/g['samples'] for k in KEYS}
    runs.append({'run':run,'plan_sha256':ph,'verdict_sha256':vh,'work_sha256':wh,
                 'groups':groups,'proxy_NOT_upper_bound_or_speed':{
                    k:sum(g['equal_cost_proxies'][k] for g in groups.values()) for k in KEYS}})
out = {'at_utc':datetime.now(timezone.utc).isoformat(),
       'script_sha256':hashlib.sha256(Path(__file__).read_bytes()).hexdigest(),
       'scope':'Same256 deterministic strata per timed ADD case, already exposed three old R15 draws. Pure domain classification; no new runtime, random correctness sample, measured speed, bound, or probability.',
       'runs':runs,'elapsed_seconds':time.monotonic()-start,'candidate':'NONE'}
(D/'allnormal-word-domain.json').write_text(json.dumps(out,indent=2)+'\n')
print(json.dumps({'runs':[{'run':r['run'],**r['proxy_NOT_upper_bound_or_speed']} for r in runs],
                 'elapsed_seconds':out['elapsed_seconds']}))
