"""Independent rehash/recalculation of exact compactScales first full discovery."""
from pathlib import Path
from collections import defaultdict
import hashlib,json,random,statistics,datetime
HERE=Path(__file__).resolve().parent
ROOT=next(p for p in HERE.parents if (p/'DEVELOPMENT.md').exists())
R=ROOT/'competitions/floatlib/candidates/f01-mul-log2-proof1/ci-runs/40417039536'
sha=lambda p:hashlib.sha256(p.read_bytes()).hexdigest()
idx=json.loads((R/'original-artifact-hashes.json').read_text());art=(R/idx['directory']).resolve()
ci=json.loads((R/'ci-run.json').read_text());listing=json.loads((R/'artifacts.json').read_text())
assert ci['databaseId']==40417039536 and ci['status']=='completed' and ci['conclusion']=='success'
assert ci['headSha']==idx['artifact']['workflow_run']['head_sha']=='b75a8d645e87ff5abea4b7ba336f7c9bd357527d'
assert idx['artifact'] in listing['artifacts']
verified=[]
for rel,meta in idx['files'].items():
    p=(art/rel).resolve();assert p.is_relative_to(art)
    assert p.stat().st_size==meta['bytes'] and sha(p)==meta['sha256'],rel
    verified.append({'file':rel,**meta})
s=art/'diagnostics/f01-d7-public-suite/public-suite'
plan=json.loads((s/'requested-plan.json').read_text());summary=json.loads((s/'summary.json').read_text())
assert plan['sample_role']=='DISCOVERY' and summary['complete'] and summary['rounds']==25 and summary['pairs']==500000
assert summary['source_commit']==ci['headSha'] and summary['requested_plan_sha256']==sha(s/'requested-plan.json')
assert summary['official_commit']=='4b7e83841cc0c32c6529f533923c73d33b5ecf97'
assert not any(e.get('capture_codegen') for e in plan['candidates'])
assert not plan['profile_parent'] and not plan['profile_current']
assert (s/'official-source-clean.log').read_bytes()==b''
work=json.loads((s/'public-cell-work.json').read_text())
cases=json.loads((s/'public-drawn-plan.json').read_text())['cases']
assert len(cases)==156 and sum(c['timed'] for c in cases)==152 and len(work)==26
names=['f01-r19-dev-compact-scales1','f01-r15-dev-packed-b2-1','f01-r8-combined-result-guard']
expected=['9c4e9505702231fdb93f47f8d767ba0b2b0c2ad7ec48d8894b5a53ba87657645','622d8394a7127e93dcaf992c62c6dfcff7208d212738409a5e34525dfafd1a58','41bce4856c4c921dd67b6115928df16e5e8ed08a55b71f1296d28b77cf9ce9a7']
vs={};identities=[]
for n,h in zip(names,expected):
    inp=s/'inputs'/n/'Kernel.lean';assert sha(inp)==h
    vp=s/(n+'-verdict.json');v=json.loads(vp.read_text());row=next(x for x in summary['results'] if x['candidate']==n)
    assert sha(vp)==row['verdict_sha256'] and row['kernel_sha256']==h
    assert v['passed'] and v['stage']=='score' and v['mode']=='gate' and len(v['rounds'])==25 and v['seed']==1927008
    assert v['verifier_fingerprint']==v['verifier_fingerprint_end']=='dbfba2ce838eefbfcfc3f8f66c24feff9a57a9dca85374ae44ca8ed1b49d0479'
    assert v['suite']['sha256']=='a16494e97c6a073bfd8accf72480c34534c87808092c56074fdcfa42cd34868a'
    sub=sum(v['classes'][c]['submission_ns']*w for c,w in work.items());ref=sum(v['classes'][c]['incumbent_ns']*w for c,w in work.items())
    assert abs(sub/ref-v['ratio'])<1e-12
    vs[n]=v;identities.append({'candidate':n,'source_sha256':h,'verdict_sha256':sha(vp),'full_gate':True,'whole_submission_ns':sub,'whole_reference_ns':ref})
c,b=names[:2];relative=vs[c]['ratio']/vs[b]['ratio']
values=[[sub/inc for inc,sub in vs[n]['rounds']] for n in [c,b]]
rng=random.Random(90423);gains=[]
for _ in range(2000):
    med=[statistics.median([x[rng.randrange(25)] for _ in range(25)]) for x in values]
    gains.append(1-med[0]/med[1])
gains.sort();p=.05*1999;lo=int(p);p05=gains[lo]+(gains[lo+1]-gains[lo])*(p-lo)
ops={};cell={}
for op in ['add','mul','sum','bmm']:
    sums={n:{kind:sum(vs[n]['classes'][k][kind+'_ns']*w for k,w in work.items() if k.startswith(op+':')) for kind in ['submission','incumbent']} for n in [c,b]}
    ops[op]=(sums[c]['submission']/sums[c]['incumbent'])/(sums[b]['submission']/sums[b]['incumbent'])
for k in work:cell[k]=vs[c]['classes'][k]['ratio']/vs[b]['classes'][k]['ratio']
dresult=ROOT/'competitions/floatlib/candidates/f01-d7-research/round9h-20261026T194639Z/result-1927008-f01-r19-dev-compact-scales1-vs-f01-r15-dev-packed-b2-1.json'
d=json.loads(dresult.read_text());assert abs(relative-d['relative_normalized_ratio'])<1e-14 and abs(p05-d['gain_p05'])<1e-14
assert all(abs(ops[k]-d['per_operation_normalized'][k])<1e-14 for k in ops)
out={'utc':datetime.datetime.now(datetime.timezone.utc).isoformat(),'status':'VERIFIED_FIRST_FULL_D_NEGATIVE_RETAIN_B2',
 'run':40417039536,'seed':1927008,'source_commit':ci['headSha'],'verified_original_files':len(verified),'files':verified,
 'artifact_index_sha256':sha(R/'original-artifact-hashes.json'),'D_comparison_sha256':sha(dresult),
 'identities':identities,'relative_normalized_ratio':relative,'gain_p05':p05,'per_operation_normalized':ops,'per_cell_normalized':cell,
 'observer':False,'sample_role':'DISCOVERY','policy_pass':relative<=.97 and p05>0,
 'bootstrap':'Independent candidate/reference and baseline/reference gates;2000 seeded90423 draws of25 roundratios, medians,linear p05; not direct candidate/B2 pairs.',
 'codegen_binding':'Same exact9c4e was previously inspected in actual MainFull diagnostic404108. This fullD has no observer or captured timedELF; runtime mechanism is supported, specific slowdown attribution remains UNKNOWN.',
 'causal_limit':'Added flag/narrowing and code layout are plausible costs, not separately measured causes. SUM/BMM movements also warn against assigning the entire headline delta to the changed scalar loads.',
 'decision':'PARK_EXACT_9C4E_NO_AB_NO_SEED_REVIVAL; keep formal interface and primary evidence. No variant emitted by this stage.',
 'root_git_tree_verification':'D comparison records source-tree verification; this worker independently rehashes artifact inputs/metadata, without Git operations.',
 'new_CI':False,'new_candidate':False}
(HERE/'audit.json').write_text(json.dumps(out,indent=2)+'\n',encoding='utf-8')
print(json.dumps({k:out[k] for k in ['status','verified_original_files','relative_normalized_ratio','gain_p05','per_operation_normalized','decision']}))
