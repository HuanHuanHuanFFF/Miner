"""Small evidence index; never changes source selection or the frozen model."""
from pathlib import Path
from datetime import datetime, timezone
import hashlib
import json

here = Path(__file__).resolve().parent
root = here.parents[4]
read = lambda p: json.loads(p.read_bytes())
sha = lambda p: hashlib.sha256(p.read_bytes()).hexdigest()
state = read(root / 'competitions/floatlib/coordination/development-status.json')
rr = state['research_round']
assert rr['id'] == 'R19-20261026T194639Z'
runs = []
wall_seconds = 0
for run in rr['started_ci']:
    job_path = here / f'development-ci-job-{run}.json'
    job = read(job_path)
    item = {k: job[k] for k in ('run', 'source_commit', 'state', 'inputs')}
    item['job_receipt'] = {'path': job_path.relative_to(root).as_posix(), 'sha256': sha(job_path)}
    plan = here / f'plan-{job["inputs"]["seed"]}.json'
    item['plan'] = {'path': plan.relative_to(root).as_posix(), 'sha256': sha(plan)}
    item['sample_role'] = read(plan)['sample_role']
    item['candidate_names'] = [row['candidate'] for row in read(plan)['candidates']]
    if run in rr['completed_ci']:
        base = root / 'competitions/floatlib/candidates/f01-mul-log2-proof1/ci-runs' / str(run)
        meta = read(base / 'ci-run.json')
        assert meta['status'] == 'completed' and meta['headSha'] == job['source_commit']
        item['conclusion'] = meta['conclusion']
        item['evidence_index'] = {'path': (base / 'original-artifact-hashes.json').relative_to(root).as_posix(), 'sha256': sha(base / 'original-artifact-hashes.json')}
        item['artifact_files'] = len(read(base / 'original-artifact-hashes.json')['files'])
        jobs = meta['jobs']
        assert len(jobs) == 1
        start = datetime.fromisoformat(jobs[0]['startedAt'].replace('Z', '+00:00'))
        end = datetime.fromisoformat(jobs[0]['completedAt'].replace('Z', '+00:00'))
        item['whole_job_wall_seconds'] = (end - start).total_seconds()
        wall_seconds += item['whole_job_wall_seconds']
    else:
        item['whole_job_wall_seconds'] = 'UNKNOWN_ACTIVE'
    runs.append(item)

routes = []
for folder in sorted((root / 'competitions/floatlib/candidates').glob('f01-r19-dev-*')):
    manifest_path = folder / 'manifest.json'
    if not manifest_path.is_file():
        continue
    manifest = read(manifest_path)
    assert sha(folder / 'Kernel.lean') == manifest['candidate_sha256']
    relevant = [item['run'] for item in runs if folder.name in item['candidate_names']]
    route = {
        'candidate': folder.name, 'sha256': manifest['candidate_sha256'], 'bytes': manifest['candidate_bytes'],
        'manifest': manifest_path.relative_to(root).as_posix(), 'manifest_sha256': sha(manifest_path),
        'proof_status': manifest.get('proof_status', 'UNKNOWN'), 'performance': manifest.get('performance', 'UNKNOWN'),
        'CI_runs': relevant, 'individual_CI_wall_seconds': 'UNKNOWN_SHARED_BATCH',
        'actual_research_seconds': 'UNKNOWN', 'available_tokens': 'UNKNOWN', 'used_tokens': 'UNKNOWN', 'cached_input_tokens': 'UNKNOWN',
    }
    if 'first_discovery' in manifest:
        route['first_discovery'] = manifest['first_discovery']
    for result_path in sorted(here.glob('result-*-'+folder.name+'-vs-f01-r15-dev-packed-b2-1.json')):
        result = read(result_path)
        route.setdefault('original_cost_results', []).append({
            'path': result_path.relative_to(root).as_posix(), 'sha256': sha(result_path),
            **{key: result[key] for key in ('run', 'seed', 'full_gate_both', 'relative_normalized_ratio', 'gain_p05', 'local_discovery_screen_passed', 'per_operation_normalized') if key in result},
        })
    routes.append(route)

model = here.parent / 'champion-time-estimate.json'
assert sha(model) == 'ab3be355546023e1e8c88a98830018cf3a72f5b238de6b86dd7c0603b296bfda'
value = {
    'as_of_utc': datetime.now(timezone.utc).isoformat(), 'round': rr['id'],
    'scope': 'Derived compact evidence/resource index, not the authoritative current state or an adoption result',
    'window': {'start_utc': rr['start_utc'], 'deadline_utc': rr['deadline_utc'], 'budget_minutes': 540},
    'CI_whole_job_wall_seconds_completed': wall_seconds, 'CI_wall_scope': 'One actual hosted job per run, counted once across shared routes; excludes current active run and peer jobs. Not local CPU time.',
    'local_Lean_compiles': 0, 'formal_submission': 'NOT_SUBMITTED', 'retained_source_sha256': state['kernel_sha256'],
    'retained_numeric_model_sha256': sha(model), 'runs': runs, 'routes': routes,
    'decisions': rr.get('allocation_decisions', []),
}
path = here / 'development-experiment-ledger.json'
path.write_bytes((json.dumps(value, ensure_ascii=False, indent=2) + '\n').encode())
print(json.dumps({'path': path.relative_to(root).as_posix(), 'runs': len(runs), 'completed': len(rr['completed_ci']), 'routes': len(routes), 'completed_CI_job_wall_minutes': wall_seconds / 60, 'retained_model_unchanged': True}))
