"""Read-only original-artifact checker; run explicitly for each new terminal CI."""
from pathlib import Path
from hashlib import sha256
import argparse,json

HERE=Path(__file__).resolve().parent
ROOT=HERE.parents[4]
RUNS=ROOT/'competitions/floatlib/candidates/f01-mul-log2-proof1/ci-runs'
ap=argparse.ArgumentParser()
ap.add_argument('runs',nargs='+',type=int)
args=ap.parse_args()
results=[]
for run in args.runs:
    folder=RUNS/str(run)
    index_path=folder/'original-artifact-hashes.json'
    index_raw=index_path.read_bytes()
    index=json.loads(index_raw)
    stage=(folder/index['directory']).resolve()
    assert stage.is_relative_to(folder.resolve())
    count=size=0
    for name,expected in index['files'].items():
        path=(stage/name).resolve()
        assert path.is_relative_to(stage)
        raw=path.read_bytes()
        assert len(raw)==expected['bytes'] and sha256(raw).hexdigest()==expected['sha256'],str(path)
        count+=1;size+=len(raw)
    suite=stage/'diagnostics/f01-d7-public-suite/public-suite'
    verdicts=[]
    for path in sorted(suite.glob('*-verdict.json')):
        raw=path.read_bytes();v=json.loads(raw)
        name=path.name.removesuffix('-verdict.json')
        inp=suite/'inputs'/name/'Kernel.lean'
        diag=suite/'diagnostics'/name
        helper=diag/'helper-audit.json'
        h=json.loads(helper.read_bytes())if helper.is_file()else None
        verdicts.append(dict(name=name,kernel_sha256=sha256(inp.read_bytes()).hexdigest()if inp.is_file()else None,
                             stage=v.get('stage'),passed=v.get('passed'),reason=v.get('reason'),
                             verdict_sha256=sha256(raw).hexdigest(),
                             kernel_replay=h.get('kernel_replay')if h else None,
                             helper_accepted=h.get('accepted')if h else None,
                             roots_count=len(h.get('names',[]))if h else None,
                             full_performance_gate=v.get('stage')=='score'and v.get('passed')is True))
    results.append(dict(run=run,artifact_id=index['artifact']['id'],artifact_head=index['artifact']['workflow_run']['head_sha'],
                        index_sha256=sha256(index_raw).hexdigest(),original_files_verified=count,bytes_verified=size,
                        verdicts=verdicts))
record=dict(status='VERIFIED_AVAILABLE_ORIGINAL_FILES_EXACT_BYTES',runs=results,
            total_files=sum(r['original_files_verified']for r in results),
            scope='File-byte integrity and exact source/verdict/audit binding only. Stage labels distinguish statement/replay/helper audit from full performance gate; no admission or reward claim.')
(HERE/('astra-originals-verified-'+ '-'.join(map(str,args.runs))+'.json')).write_text(json.dumps(record,indent=2)+'\n',encoding='utf-8')
print(json.dumps(record,indent=2))
