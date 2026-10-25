"""Collect original evidence and print a small terminal summary, never full raw logs."""
from pathlib import Path
import argparse,json,subprocess,sys
OUT=Path(__file__).resolve().parent;ROOT=OUT.parents[4]
ap=argparse.ArgumentParser();ap.add_argument('--run',type=int,required=True);a=ap.parse_args()
log=OUT/f'development-collect-{a.run}.log'
with log.open('xb') as f:
    p=subprocess.run([sys.executable,'-B',str(OUT/'development-ci.py'),'collect','--run',str(a.run)],cwd=ROOT,stdout=f,stderr=subprocess.STDOUT)
assert p.returncode==0, f'Collector failed; inspect {log} before retry'
base=ROOT/'competitions/floatlib/candidates/f01-mul-log2-proof1/ci-runs'/str(a.run);ci=json.loads((base/'ci-run.json').read_bytes())
result={'run':a.run,'state':ci['status'],'conclusion':ci['conclusion'],'source_commit':ci['headSha'],'evidence':base.relative_to(ROOT).as_posix()}
index_path=base/'original-artifact-hashes.json'
if index_path.exists():
    index=json.loads(index_path.read_bytes());stage=base/index['directory'];nested=stage/'diagnostics/f01-d7-public-suite/public-suite/summary.json'
    result['artifact_files']=len(index['files'])
    if nested.exists():
        d=json.loads(nested.read_bytes());result.update(nested_complete=d.get('complete'),results=[{k:r.get(k) for k in ['candidate','kernel_sha256','exit_code','full_gate','compile_pass','ratio','verdict']} for r in d.get('results',[])])
    else:result['nested_complete']=False
else:result['artifact_status']='MISSING'
(OUT/f'development-terminal-{a.run}.json').write_bytes((json.dumps(result,ensure_ascii=False,indent=2)+'\n').encode());print(json.dumps(result,ensure_ascii=False))
