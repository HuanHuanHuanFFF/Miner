"""Read exact recovered first-D artifacts; no Git, network, CI or source mutation."""
from pathlib import Path
from datetime import datetime,timezone
import hashlib,json,math,random,statistics,time
H=Path(__file__).resolve().parent
R=next(p for p in H.parents if (p/'competitions/floatlib/pins.json').is_file())
start=time.monotonic();sha=lambda b:hashlib.sha256(b).hexdigest()
home=R/'competitions/floatlib/candidates/f01-mul-log2-proof1/ci-runs/40398675395/download-42cfe8ce05b24bf6bd145777f10a1729/diagnostics/f01-d7-public-suite/public-suite'
summary=json.loads((home/'summary.json').read_bytes())
assert summary['seed']==1927003 and summary['rounds']==25
assert summary['source_commit']=='505520ce3a0b7075fd73c6d6ec1d8698ba42a399'
assert summary['official_commit']=='4b7e83841cc0c32c6529f533923c73d33b5ecf97'
work=json.loads((home/'public-cell-work.json').read_bytes())
names=['f01-r19-dev-temporal-b2-1','f01-r15-dev-packed-b2-1']
expected=['c70cf9479ca48b4690990ebbd0b3781139cbeb94e46b28bbe61563e3eeaced1c','622d8394a7127e93dcaf992c62c6dfcff7208d212738409a5e34525dfafd1a58']
verdicts={};evidence=[]
for name,digest in zip(names,expected):
 entry=next(x for x in summary['results'] if x['candidate']==name)
 assert entry['kernel_sha256']==digest and entry['full_gate'] and entry['exit_code']==0
 source=home/'inputs'/name/'Kernel.lean';assert sha(source.read_bytes())==digest
 vp=home/(name+'-verdict.json');assert sha(vp.read_bytes())==entry['verdict_sha256']
 v=json.loads(vp.read_bytes());verdicts[name]=v
 assert v['passed'] is True and v['stage']=='score' and len(v['rounds'])==25
 assert not v.get('diagnostic_only',False)
 assert set(work)==set(v['classes'])
 assert all(math.isfinite(x) and x>0 for row in v['rounds'] for x in row)
 for p in (source,vp):evidence.append({'path':str(p.relative_to(R)),'sha256':sha(p.read_bytes()),'bytes':p.stat().st_size})
for p in (home/'summary.json',home/'public-cell-work.json',home/'public-drawn-plan.json'):
 evidence.append({'path':str(p.relative_to(R)),'sha256':sha(p.read_bytes()),'bytes':p.stat().st_size})
environment_path=home.parents[2]/'environment.json'
environment=json.loads(environment_path.read_bytes())
evidence.append({'path':str(environment_path.relative_to(R)),'sha256':sha(environment_path.read_bytes()),'bytes':environment_path.stat().st_size})
gate_log=home/(names[0]+'-gate.log')
assert 'pairs=500000 rounds=25 cpu=0' in gate_log.read_text()
evidence.append({'path':str(gate_log.relative_to(R)),'sha256':sha(gate_log.read_bytes()),'bytes':gate_log.stat().st_size})
cv,bv=(verdicts[n] for n in names)
whole=cv['ratio']/bv['ratio']
ratios=[[sub/inc for inc,sub in verdicts[n]['rounds']] for n in names]
rng=random.Random(90423);gains=[]
for _ in range(2000):
 med=[statistics.median(values[rng.randrange(25)] for _ in range(25)) for values in ratios]
 gains.append(1-med[0]/med[1])
gains.sort();x=.05*1999;i=int(x);p05=gains[i]+(gains[i+1]-gains[i])*(x-i)
ops={};cells={}
for op in ('add','mul','sum','bmm'):
 totals={n:{kind:sum(v['classes'][cell][kind+'_ns']*weight for cell,weight in work.items() if cell.startswith(op+':')) for kind in ('submission','incumbent')} for n,v in verdicts.items()}
 a,b=(totals[n] for n in names)
 ops[op]={'normalized_ratio':(a['submission']/a['incumbent'])/(b['submission']/b['incumbent']),'candidate_submission_total_ns':a['submission'],'baseline_submission_total_ns':b['submission'],'candidate_reference_total_ns':a['incumbent'],'baseline_reference_total_ns':b['incumbent']}
for cell in work:
 c,b=cv['classes'][cell],bv['classes'][cell]
 cells[cell]={'normalized_ratio':(c['submission_ns']/c['incumbent_ns'])/(b['submission_ns']/b['incumbent_ns']),'candidate_submission_ns':c['submission_ns'],'baseline_submission_ns':b['submission_ns'],'weight':work[cell]}
report={'at_utc':datetime.now(timezone.utc).isoformat(),'run':40398675395,'seed':1927003,'sample_role':'DISCOVERY','candidate':names[0],'candidate_sha256':expected[0],'baseline':names[1],'baseline_sha256':expected[1],'source_commit':summary['source_commit'],'original_public_full_gate_both':True,'paired_rounds_each':25,'relative_normalized_whole_ratio':whole,'whole_gain':1-whole,'gain_p05':p05,'bootstrap_samples':2000,'bootstrap_seed':90423,'discovery_pass':whole<=.97 and p05>0,'per_operation':ops,'per_cell':cells,'evidence':evidence,'scope':'Same actual CI source artifacts. Normalization is candidate/reference divided by B2/reference, not directly paired candidate/B2. No Git commit-tree audit performed here; D/root owns full execution binding.','decision':'NO_ADOPTION_OR_CONFIRMATION_FOR_C70C_FIRST_D; preserve exact correctness and measured local evidence, no seed reset','elapsed_seconds':time.monotonic()-start}
report['environment']={'lean':environment['lean'],'systemd_caps':environment['systemd_caps'],'official_source_diff':environment['official_source_diff'],'bench_logical_cpu':0,'cpu_model':'UNKNOWN_NOT_RECORDED_IN_READ_ARTIFACTS','candidate_gate_seconds':cv['seconds'],'baseline_gate_seconds':bv['seconds'],'scope':'Gate duration includes proof/build/check/score; it is CI resource use, not the kernel speed ratio.'}
(H/'first-discovery-review.json').write_text(json.dumps(report,indent=2)+'\n')
print(json.dumps({k:report[k] for k in ('run','seed','candidate_sha256','original_public_full_gate_both','paired_rounds_each','relative_normalized_whole_ratio','gain_p05','discovery_pass','per_operation','elapsed_seconds')}))
