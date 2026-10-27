"""Read original frozen-cohort artifacts; never changes candidates or selection.

Independent arithmetic check of the frozen formula. One Random(90423) stream
is consumed in D/A/B order, candidate then DF, 2000 paired-round resamples.
This is an audit of observed inputs, not a prediction of future success.
"""
from pathlib import Path
from datetime import datetime, timezone
import hashlib
import json
import random
import statistics
import subprocess
import time

HERE = Path(__file__).resolve().parent
ROOT = next(p for p in HERE.parents if (p / 'AGENTS.md').is_file())
START = time.perf_counter()
COHORT_SHA = 'e934782573a07d2cb8607a3325d18eca33ba3b15cbcc9ceacabe2d4989f78018'
RUNS = {'D': 40168687803, 'A': 40169957447, 'B': 40171180249}
blob = (HERE / 'cohort-freeze.json').read_bytes()
assert hashlib.sha256(blob).hexdigest() == COHORT_SHA
co = json.loads(blob)
assert co['diagnostic_only'] is False and co['required_groups'] == 3
assert co['selection_policy']['headline_normalized_ratio_max'] == .97
assert co['selection_policy']['gain_p05_min_exclusive'] == 0
policy = co['selection_policy']
rng = random.Random(policy['bootstrap_seed'])
observations = []
fingerprint = None
contracts = None
for label, run in RUNS.items():
    statefile = HERE / f'development-ci-job-{run}.json'
    if not statefile.is_file() or json.loads(statefile.read_bytes())['state'] != 'TERMINAL_COLLECTED':
        break
    job = json.loads(statefile.read_bytes())
    runroot = ROOT / f'competitions/floatlib/candidates/f01-mul-log2-proof1/ci-runs/{run}'
    name = co['candidate']['name']
    vf = next(runroot.glob(f'download-*/diagnostics/f01-d7-public-suite/public-suite/{name}-verdict.json'))
    stage = vf.parent
    summary = json.loads((stage / 'summary.json').read_bytes())
    assert summary['complete']
    assert [x['candidate'] for x in summary['results']] == co['candidate_orders'][label]
    assert summary['suite_sha256'] == co['suite_sha256']
    assert summary['official_generator_sha256'] == co['generator_sha256']
    if contracts is None:
        contracts = summary['same_contracts_sha256']
    assert contracts == summary['same_contracts_sha256']
    work = json.loads((stage / 'public-cell-work.json').read_bytes())
    verdicts = {}
    for role in ('candidate', 'baseline', 'estimator_control'):
        spec = co[role]
        raw = (stage / 'inputs' / spec['name'] / 'Kernel.lean').read_bytes()
        assert hashlib.sha256(raw).hexdigest() == spec['sha256']
        v = json.loads((stage / (spec['name'] + '-verdict.json')).read_bytes())
        assert v['passed'] and v['mode'] == 'gate' and v['stage'] == 'score'
        assert v['seed'] == co['groups'][label]['seed'] and len(v['rounds']) == 25
        assert v['reference_complete'] and not v['incumbent_failed']
        assert v['incumbent_sha256'] == co['reference']['incumbent_sha256']
        assert v['champion_sha256'] == co['reference']['champion_sha256']
        if fingerprint is None:
            fingerprint = v['verifier_fingerprint']
        assert fingerprint == v['verifier_fingerprint'] == v['verifier_fingerprint_end']
        assert set(v['classes']) == set(work)
        verdicts[role] = v
    def headline(v):
        sub = sum(x['submission_ns'] * work[k] for k, x in v['classes'].items())
        ref = sum(x['incumbent_ns'] * work[k] for k, x in v['classes'].items())
        assert abs(sub / ref - v['ratio']) < 1e-10
        return sub / ref
    ratio = headline(verdicts['candidate']) / headline(verdicts['baseline'])
    pairratios = [[sub / ref for ref, sub in verdicts[role]['rounds']]
                  for role in ('candidate', 'baseline')]
    gains = []
    for _ in range(policy['bootstrap_samples']):
        medians = [statistics.median(values[rng.randrange(25)] for _ in range(25))
                   for values in pairratios]
        gains.append(1 - medians[0] / medians[1])
    gains.sort()
    q = (len(gains) - 1) * .05
    lo = int(q)
    p05 = gains[lo] * (1 - (q - lo)) + gains[lo + 1] * (q - lo)
    observations.append({'group': label, 'run': run, 'source_commit': job['source_commit'],
                         'seed': co['groups'][label]['seed'], 'all3_full_gates': True,
                         'rounds': 25, 'actual_order': co['candidate_orders'][label],
                         'headline_independent': ratio, 'p05_one_stream_independent': p05,
                         'meets_original_thresholds': ratio <= .97 and p05 > 0})

assert observations
last_commit = observations[-1]['source_commit']
frozen_files = []
for section in ('files', 'execution_files'):
    for rel, info in co[section].items():
        file = (ROOT / rel).resolve()
        assert file.is_relative_to(ROOT)
        actual = hashlib.sha256(file.read_bytes()).hexdigest()
        if actual == info['sha256']:
            checked_at = 'current_working_bytes'
        else:
            # Legitimate post-confirmation metadata updates must not rewrite the
            # historical observation: inspect the final checked run's Git bytes.
            git = subprocess.run(['git', 'show', last_commit + ':' + rel], cwd=ROOT,
                                 check=True, capture_output=True, timeout=2)
            assert hashlib.sha256(git.stdout).hexdigest() == info['sha256'], rel
            checked_at = 'run_source_commit; current bytes changed after cohort'
        frozen_files.append({'path': rel, 'match': True, 'source': checked_at})

out = {'checked_utc': datetime.now(timezone.utc).isoformat(), 'cohort_sha256': COHORT_SHA,
       'candidate_sha256': co['candidate']['sha256'], 'baseline_sha256': co['baseline']['sha256'],
       'completed_groups': observations, 'frozen_files': frozen_files,
       'complete_three_groups': len(observations) == 3,
       'all_completed_groups_qualify': all(x['meets_original_thresholds'] for x in observations),
       'verifier_fingerprint': fingerprint, 'contract_hashes': contracts,
       'bootstrap': 'One frozen-seed stream, D/A/B, candidate then baseline; linear p05',
       'scope': 'Independent original-artifact arithmetic audit. No new timing, reseed, model calibration, adoption, publication or formal submission.',
       'elapsed_seconds': time.perf_counter() - START,
       'script_sha256': hashlib.sha256(Path(__file__).read_bytes()).hexdigest()}
target = HERE / ('astra-cohort-independent-' + '-'.join(x['group'] for x in observations) + '.json')
if target.exists():
    raise RuntimeError('Preserve existing audit receipt: choose a new observation filename explicitly')
target.write_text(json.dumps(out, indent=2) + '\n', encoding='utf-8')
print(json.dumps({'receipt': str(target), 'groups': observations,
                  'complete': out['complete_three_groups'], 'elapsed': out['elapsed_seconds']}))
