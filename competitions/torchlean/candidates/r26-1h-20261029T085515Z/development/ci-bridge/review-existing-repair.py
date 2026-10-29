"""Verify the frozen queue-repair delta, not candidate correctness or performance."""
from pathlib import Path
import datetime, hashlib, json, subprocess

ROOT = next(p for p in Path(__file__).resolve().parents if (p / 'AGENTS.md').is_file())
ROUND = Path(__file__).resolve().parents[2]
PREFIX = ROUND.relative_to(ROOT).as_posix()
OLD = 'edd41c939a772d634dc118a9201dc1946351369d'
NEW = '12e6d73f5775a753d8a82d4c2f731900a74c0043'
sha = lambda b: hashlib.sha256(b).hexdigest()

def blob(commit, path):
    return subprocess.check_output(['git', 'show', commit + ':' + path], cwd=ROOT)

dispatch_path = ROUND / 'evidence/dispatch-20261029T095022Z/dispatch.json'
dispatch = json.loads(dispatch_path.read_bytes())
assert dispatch['source_commit'] == NEW and dispatch['run']['databaseId'] == 40852769757
for path, digest in dispatch['frozen_files'].items():
    assert sha(blob(NEW, path)) == digest, path
old_plan = json.loads(blob(OLD, PREFIX + '/ci-plan.json'))
new_plan = json.loads(blob(NEW, PREFIX + '/ci-plan.json'))
mutable = {'start_cutoff_utc', 'sample_role', 'parent_run', 'queue_repair_reason'}
assert {k:v for k,v in old_plan.items() if k not in mutable} == {k:v for k,v in new_plan.items() if k not in mutable}
assert old_plan['round_deadline_utc'] == new_plan['round_deadline_utc'] == '2026-10-29T09:55:15Z'
runner_path = PREFIX + '/development/ci-bridge/runner.py'
old_runner = blob(OLD, runner_path)
old_line = b" assert datetime.datetime.now(datetime.timezone.utc)<datetime.datetime.fromisoformat(plan['start_cutoff_utc'])\n"
new_line = old_line.rstrip(b'\n') + b", 'QUEUE_ACQUIRED_AFTER_EXISTING_EXPERIMENT_START_LIMIT'\n"
assert old_runner.count(old_line) == 1
assert old_runner.replace(old_line, new_line) == blob(NEW, runner_path)
prior = ROUND / 'verification/preflight-delta2.json'
review = {
    'round':'R26',
    'review_kind':'ROOT_FROZEN_DELTA_REVIEW_BEFORE_RESULT_NOT_INDEPENDENT',
    'reviewed_utc':datetime.datetime.now(datetime.timezone.utc).isoformat(),
    'status':'EXACT_FROZEN_DELTA_PASS_RUNTIME_PENDING',
    'prior_independent_review':{'path':prior.relative_to(ROOT).as_posix(), 'sha256':sha(prior.read_bytes())},
    'actual_dispatch':{
        'run_id':40852769757, 'source_commit':NEW,
        'created_at_utc':dispatch['run']['createdAt'],
        'plan_sha256':dispatch['frozen_files'][PREFIX + '/ci-plan.json'],
        'runner_sha256':dispatch['frozen_files'][runner_path],
    },
    'frozen_sources':{
        'workflow_sha256':dispatch['frozen_files']['.github/workflows/deflate-baseline.yml'],
        'ci_prepare_sha256':dispatch['frozen_files']['competitions/torchlean/scripts/ci-prepare.sh'],
        'candidate':new_plan['candidates'][0], 'reference':new_plan['reference'],
        'proof_diagnostics':new_plan['proof_diagnostics'],
    },
    'plan_cutoff_utc':new_plan['start_cutoff_utc'],
    'delta':'Same source, reference, inputs, target, flags, proof boundaries and overall deadline. Only existing-experiment queue cutoff/metadata and assertion text changed.',
    'cutoff_boundary':'Dispatched after09:38 new-route cutoff, before09:55:15 common end, as repair of the09:37 already-launched frozen experiment; not a new route or extension.',
    'claims':'No runtime or native proof claim. This late delta review is by Root, not a new independent review.',
}
out = ROUND / 'verification/preflight-batch3-root.json'
assert not out.exists(), 'Do not overwrite a review receipt'
out.write_text(json.dumps(review, indent=2) + '\n', encoding='utf-8')
print(json.dumps({'path':str(out), 'status':review['status']}))
