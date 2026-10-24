"""Describe already exposed complete controls from a cancelled outer CI; no adoption."""
from pathlib import Path
import importlib.util,json
OUT=Path(__file__).resolve().parent;ROOT=OUT.parents[4];D7=OUT.parent
s=importlib.util.spec_from_file_location('r14_share_guard',OUT/'adoption-guard.py');g=importlib.util.module_from_spec(s);s.loader.exec_module(g)
p=g.load_run(ROOT,D7,40124283357,('f01-d12-scalar-combined','f01-r8-combined-result-guard'))
v=p['verdicts']['f01-d12-scalar-combined'];work=p['cell_work']
times={c:values['submission_ns']*work[c] for c,values in v['classes'].items()};total=sum(times.values())
ops={op:sum(ns for c,ns in times.items() if c.startswith(op+':')) for op in ('add','mul','sum','bmm')}
report={'scope':'Exposed seed1425001 workload diagnostic only. Individual DF and41 original full25 gates passed, outer CI cancelled at fixed45min. Not adoption or a new holdout.',
        'run':40124283357,'job_conclusion':p['job_conclusion'],'source_commit':p['evidence']['source_commit'],'kernel_sha256':p['kernel_hashes']['f01-d12-scalar-combined'],
        'seed':p['seed'],'operation_shares':{op:ns/total for op,ns in ops.items()},'cell_shares':{c:ns/total for c,ns in times.items()},
        'category_whole_share_upper_bounds':{'scalar_specials_all_cost':sum(times[c] for c in ('add:specials','mul:specials'))/total,'bmm_specials_all_cost':times['bmm:specials']/total,'mul_subnormal_all_cost':times['mul:subnormal']/total},
        'limits':'Shares are complete per-cell minimum-cost contributions for this public input draw. Category totals are only broad ceilings, not NaN or removable-stage costs; ordinary overhead and actual data eligibility still need measurement.'}
(OUT/'development-d1-cost-shares.json').write_bytes((json.dumps(report,ensure_ascii=False,indent=2)+'\n').encode());print(json.dumps({k:v for k,v in report.items() if k!='cell_shares'}))
