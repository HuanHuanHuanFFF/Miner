"""Read one peer discovery only; do not inspect its frozen confirmation inputs."""
from pathlib import Path
from hashlib import sha256
import json,random,statistics

HERE=Path(__file__).resolve().parent
ROOT=HERE.parents[4]
PEER=Path('D:/CodingProject/Bitget-DeepSeek')
folder=PEER/'competitions/floatlib/research/deepseek-20261025/ci-runs/40397668271'
index_path=folder/'original-artifact-hashes.json'
index=json.loads(index_path.read_bytes())
stage=(folder/index['directory']).resolve()
assert stage.is_relative_to(folder.resolve())
for name,info in index['files'].items():
    path=(stage/name).resolve();assert path.is_relative_to(stage)
    raw=path.read_bytes()
    assert len(raw)==info['bytes']and sha256(raw).hexdigest()==info['sha256'],name
suite=stage/'diagnostics/f01-d7-public-suite/public-suite'
base='f01-r15-dev-packed-b2-1';candidate='f01-deepseek-multh0'
raw=(suite/'inputs'/candidate/'Kernel.lean').read_bytes()
assert sha256(raw).hexdigest()=='14a6ae2f9afd31cd584b5087fe24e001663d16222856515c9a4c4e10c1322ea5'
parent=(ROOT/'competitions/floatlib/candidates'/base/'Kernel.lean').read_bytes()
assert sha256(parent).hexdigest()=='622d8394a7127e93dcaf992c62c6dfcff7208d212738409a5e34525dfafd1a58'
old=b'if ex + ey < (128 : UInt32) then LowScale.mul x y else nativeMul x y'
new=b'if ex + ey < (0 : UInt32) then LowScale.mul x y else nativeMul x y'
assert parent.count(old)==1 and parent.replace(old,new)==raw
vs={p.name.removesuffix('-verdict.json'):json.loads(p.read_bytes())for p in suite.glob('*-verdict.json')}
b=vs[base];v=vs[candidate]
assert all(x['passed']is True and x['stage']=='score'and len(x['rounds'])==25 for x in vs.values())
assert v['seed']==b['seed']==1826011 and v['suite']==b['suite']
assert v['verifier_fingerprint']==v['verifier_fingerprint_end']==b['verifier_fingerprint']==b['verifier_fingerprint_end']
assert v['reference_complete']and b['reference_complete']and not v['incumbent_failed']and not b['incumbent_failed']
cr=[s/i for i,s in v['rounds']];br=[s/i for i,s in b['rounds']]
rng=random.Random(90423);gains=[]
for _ in range(2000):
    gains.append(1-statistics.median(cr[rng.randrange(25)]for _ in range(25))/statistics.median(br[rng.randrange(25)]for _ in range(25)))
gains.sort();k=.05*(len(gains)-1);lo=int(k)
p05=gains[lo]+(gains[lo+1]-gains[lo])*(k-lo)
request=json.loads((suite/'requested-plan.json').read_bytes())
out=dict(status='VERIFIED_PEER_DISCOVERY_ONLY',run=40397668271,source_head=index['artifact']['workflow_run']['head_sha'],
         candidate_sha256=sha256(raw).hexdigest(),source_change='Exactly one selected public mul threshold128->0; other source bytes identical',
         original_files_verified=len(index['files']),index_sha256=sha256(index_path.read_bytes()).hexdigest(),
         gate_status='4 original full gates pass,25 paired rounds each; candidate/B2 verifier and suite identical',
         whole_vs_B2=v['ratio']/b['ratio'],gain_p05=p05,
         bootstrap='Local independent cross-gate,2000 replicates,Random90423,candidate thenbaseline,linear(n-1)*0.05; not official admission',
         pre_frozen_selection_policy=request.get('selection_policy'),sample_role=request.get('sample_role'),
         confirmation='NOT_INSPECTED_BY_THIS_RESEARCH_CHECK',adoption='NOT_DECIDED',
         performance_cause='UNKNOWN; deleting the dispatch is verified, the denormal-CPU explanation is a peer inference, not isolated by this check',
         excluded_claims=['official champion admission','future hardware performance','stable gain from a single discovery'])
(HERE/'astra-peer-discovery-40397668271.json').write_text(json.dumps(out,indent=2)+'\n',encoding='utf-8')
print(json.dumps(out,indent=2))
