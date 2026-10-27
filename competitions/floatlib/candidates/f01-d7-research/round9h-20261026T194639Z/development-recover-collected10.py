from pathlib import Path
import hashlib
import importlib.util
import json

here = Path(__file__).resolve().parent
root = here.parents[4]
run = 40425497337
base = root / 'competitions/floatlib/candidates/f01-mul-log2-proof1/ci-runs' / str(run)
ci = json.loads((base / 'ci-run.json').read_bytes())
assert ci['status'] == 'completed' and ci['headSha'] == 'e0cee8772259a3823cafbe575d8a82f064b7d236'
index = json.loads((base / 'original-artifact-hashes.json').read_bytes())
stage = base / index['directory']
assert set(index['files']) == {p.relative_to(stage).as_posix() for p in stage.rglob('*') if p.is_file()}
for name, info in index['files'].items():
    path = stage / name
    assert path.stat().st_size == info['bytes'] and hashlib.sha256(path.read_bytes()).hexdigest() == info['sha256']
spec = importlib.util.spec_from_file_location('r19_recover_ci_log', here / 'development-ci.py')
module = importlib.util.module_from_spec(spec); spec.loader.exec_module(module)
log = base / 'ci.log'
assert not log.exists()
raw = module.gh(['run', 'view', str(run), '--repo', module.REPO, '--log'], module.env()).encode('utf-8')
with log.open('xb') as stream:
    stream.write(raw)
summary = json.loads((stage / 'diagnostics/f01-d7-public-suite/public-suite/summary.json').read_bytes())
assert summary['source_commit'] == ci['headSha']
result = {'run': run, 'state': ci['status'], 'conclusion': ci['conclusion'], 'source_commit': ci['headSha'],
          'evidence': base.relative_to(root).as_posix(), 'artifact_files': len(index['files']),
          'nested_complete': summary['complete'],
          'results': [{k: row.get(k) for k in ('candidate', 'kernel_sha256', 'exit_code', 'full_gate', 'stage', 'reason', 'verdict')} for row in summary['results']],
          'recovery': 'Artifact already downloaded/hashed; only missing original workflow log recovered. Initial collector failure log preserved; no redownload/overwrite of original artifact.'}
(here / f'development-terminal-{run}.json').write_bytes((json.dumps(result, ensure_ascii=False, indent=2) + '\n').encode())
print(json.dumps(result, ensure_ascii=False))
