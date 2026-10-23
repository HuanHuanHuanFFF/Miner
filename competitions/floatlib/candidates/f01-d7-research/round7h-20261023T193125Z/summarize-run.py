from pathlib import Path
import argparse, datetime, hashlib, importlib.util, json, random, statistics

ap=argparse.ArgumentParser()
ap.add_argument('--run', type=int, required=True)
ap.add_argument('--candidate', required=True)
ap.add_argument('--baseline', default='f01-r8-combined-result-guard')
a=ap.parse_args()
root=Path(__file__).resolve().parents[5]
out=Path(__file__).resolve().parent
d7=out.parent
sp=importlib.util.spec_from_file_location('guard',d7/'adoption-guard.py')
g=importlib.util.module_from_spec(sp); sp.loader.exec_module(g)
baseline=a.baseline
p=g.load_run(root,d7,a.run,(a.candidate,baseline))
result={'at_utc':datetime.datetime.now(datetime.timezone.utc).isoformat(),
        'run':a.run,'seed':p['seed'],'candidate':a.candidate,
        'sha256':p['kernel_hashes'][a.candidate], 'baseline':baseline,
        'baseline_sha256':p['kernel_hashes'][baseline], 'sample_role':p['plan'].get('sample_role'),
        'codegen_present':p['codegen_present'], 'evidence':p['evidence'],
        'selection_policy':g.SELECTION_POLICY,
        'full_gate_both':all(v.get('passed') is True and v.get('stage')=='score' and len(v.get('rounds',[]))==25 for v in p['verdicts'].values()),
        'results':{n:{k:v.get(k) for k in ('passed','stage','reason','ratio')} for n,v in p['verdicts'].items()}}
if result['full_gate_both']:
    relative=p['verdicts'][a.candidate]['ratio']/p['verdicts'][baseline]['ratio']
    values=[[sub/inc for inc,sub in p['verdicts'][n]['rounds']] for n in (a.candidate,baseline)]
    rng=random.Random(90423); gains=[]
    for _ in range(2000):
        medians=[statistics.median(v[rng.randrange(25)] for _ in range(25)) for v in values]
        gains.append(1-medians[0]/medians[1])
    gains.sort(); k=.05*1999; lo=int(k)
    p05=gains[lo]+(gains[lo+1]-gains[lo])*(k-lo)
    by_op={}
    cells={}
    for cell in p['cell_work']:
        cv=p['verdicts'][a.candidate]['classes'][cell]
        bv=p['verdicts'][baseline]['classes'][cell]
        cells[cell]=(cv['submission_ns']/cv['incumbent_ns'])/(bv['submission_ns']/bv['incumbent_ns'])
    for op in ('add','mul','sum','bmm'):
        sums={n:{kind:sum(v['classes'][c][kind+'_ns']*work for c,work in p['cell_work'].items() if c.startswith(op+':')) for kind in ('submission','incumbent')} for n,v in p['verdicts'].items()}
        by_op[op]=(sums[a.candidate]['submission']/sums[a.candidate]['incumbent'])/(sums[baseline]['submission']/sums[baseline]['incumbent'])
    result.update(relative_normalized_ratio=relative,gain_p05=p05,
        local_discovery_screen_passed=relative<=.97 and p05>0,
        per_operation_normalized=by_op,per_cell_normalized=cells,
        normalized_scope='Candidate/reference versus baseline/reference; workload-weighted per operation, same actual CI execution. Not a direct paired candidate/baseline gate.')
path=out/f'result-{p["seed"]}-{a.candidate}-vs-{baseline}.json'
path.write_text(json.dumps(result,ensure_ascii=False,indent=2)+'\n',encoding='utf-8')
print(json.dumps({k:v for k,v in result.items() if k not in ('evidence','per_cell_normalized','selection_policy')}))
