from pathlib import Path
import argparse,json,hashlib,subprocess
OUT=Path(__file__).resolve().parent;ROOT=OUT.parents[4]
ap=argparse.ArgumentParser();ap.add_argument('--run',type=int,required=True);a=ap.parse_args()
base=ROOT/'competitions/floatlib/candidates/f01-mul-log2-proof1/ci-runs'/str(a.run);ci=json.loads((base/'ci-run.json').read_bytes());index=json.loads((base/'original-artifact-hashes.json').read_bytes());stage=base/index['directory'];nested=stage/'diagnostics/f01-d7-public-suite/public-suite';summary=json.loads((nested/'summary.json').read_bytes())
assert summary['complete'] and summary['source_commit']==ci['headSha']
for relative,info in index['files'].items():
    p=stage/relative;assert p.stat().st_size==info['bytes'] and hashlib.sha256(p.read_bytes()).hexdigest()==info['sha256']
rows=[]
for r in summary['results']:
    name=r['candidate'];raw=subprocess.check_output(['git','show',ci['headSha']+':competitions/floatlib/candidates/'+name+'/Kernel.lean'],cwd=ROOT);assert hashlib.sha256(raw).hexdigest()==r['kernel_sha256']
    verdict_path=nested/r['verdict'];v=json.loads(verdict_path.read_bytes());assert v['mode']=='diagnostic-statement-only'
    item={'run':a.run,'candidate':name,'kernel_sha256':r['kernel_sha256'],'source_commit':ci['headSha'],'statement_pass':v['passed'],'stage':v['stage'],'reason':v['reason'],'verdict':verdict_path.relative_to(ROOT).as_posix(),'verdict_sha256':hashlib.sha256(verdict_path.read_bytes()).hexdigest(),'full_gate':False,'kernel_replay_and_helper_axiom_audit':'NOT_RUN'}
    full=nested/'diagnostics'/name/'full-build-output.txt'
    if full.exists():
        lines=full.read_text(encoding='utf-8',errors='replace').splitlines();errors=[]
        for i,line in enumerate(lines):
            if 'error:' in line:errors.append('\n'.join(lines[i:i+5]))
        item.update(compiler_output=full.relative_to(ROOT).as_posix(),compiler_output_sha256=hashlib.sha256(full.read_bytes()).hexdigest(),compiler_errors=errors)
    (OUT/f'development-proof-{name}-{a.run}.json').write_bytes((json.dumps(item,ensure_ascii=False,indent=2)+'\n').encode());rows.append(item)
result={'run':a.run,'source_commit':ci['headSha'],'rows':rows,'original_artifact_files_verified':len(index['files']),'scope':'Exact original diagnostic statement/bench-build results, not full gate, kernel replay, extra theorem axiom audit or performance.'}
(OUT/f'development-proof-batch-{a.run}.json').write_bytes((json.dumps(result,ensure_ascii=False,indent=2)+'\n').encode())
print(json.dumps(result,ensure_ascii=False))
