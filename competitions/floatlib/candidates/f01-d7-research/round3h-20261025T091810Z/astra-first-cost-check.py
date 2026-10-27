"""Independent arithmetic/identity review of completed discovery, not a new experiment."""
from pathlib import Path
import argparse, hashlib, json, random, statistics
from datetime import datetime, timezone

HERE = Path(__file__).resolve().parent
ROOT = next(p for p in HERE.parents if (p / 'AGENTS.md').is_file())
parser = argparse.ArgumentParser()
parser.add_argument('--run', type=int, default=40183711165)
parser.add_argument('--seed', type=int, default=1626003)
args = parser.parse_args()
RUN = ROOT / f'competitions/floatlib/candidates/f01-mul-log2-proof1/ci-runs/{args.run}'
STAGE = next(RUN.glob('download-*/diagnostics/f01-d7-public-suite/public-suite'))
work = json.loads((STAGE / 'public-cell-work.json').read_bytes())
summary = json.loads((STAGE / 'summary.json').read_bytes())
assert summary['complete']
sha = lambda data: hashlib.sha256(data).hexdigest()
checks = []
for rp in sorted(HERE.glob(f'result-{args.seed}-*-vs-f01-r15-dev-packed-b2-1.json')):
    result = json.loads(rp.read_bytes())
    assert result['sample_role'] == 'DISCOVERY' and result['run'] == args.run
    verdicts = []
    for name, digest in ((result['candidate'], result['sha256']), (result['baseline'], result['baseline_sha256'])):
        assert sha((STAGE / 'inputs' / name / 'Kernel.lean').read_bytes()) == digest
        raw = (STAGE / (name + '-verdict.json')).read_bytes()
        assert sha(raw) == result['evidence']['verdict_sha256'][name]
        v = json.loads(raw)
        assert v['passed'] and v['mode'] == 'gate' and v['stage'] == 'score'
        assert v['seed'] == args.seed and len(v['rounds']) == 25
        assert v['reference_complete'] and not v['incumbent_failed']
        assert v['verifier_fingerprint'] == v['verifier_fingerprint_end']
        verdicts.append(v)
    a, b = verdicts
    assert a['verifier_fingerprint'] == b['verifier_fingerprint']
    def ratio(v, operation=None):
        keys = [key for key in work if operation is None or key.split(':')[0] == operation]
        return sum(v['classes'][key]['submission_ns'] * work[key] for key in keys) / sum(v['classes'][key]['incumbent_ns'] * work[key] for key in keys)
    headline = ratio(a) / ratio(b)
    assert abs(headline - result['relative_normalized_ratio']) < 1e-12
    operations = {op: ratio(a, op) / ratio(b, op) for op in ('add', 'mul', 'sum', 'bmm')}
    assert all(abs(value - result['per_operation_normalized'][op]) < 1e-12 for op, value in operations.items())
    values = [[sub / ref for ref, sub in v['rounds']] for v in verdicts]
    policy = result['selection_policy']; rng = random.Random(policy['bootstrap_seed'])
    gains = []
    for _ in range(policy['bootstrap_samples']):
        medians = [statistics.median(row[rng.randrange(len(row))] for _ in row) for row in values]
        gains.append(1 - medians[0] / medians[1])
    gains.sort(); q = (len(gains) - 1) * .05; lo = int(q)
    p05 = gains[lo] * (1 - (q - lo)) + gains[lo + 1] * (q - lo)
    assert abs(p05 - result['gain_p05']) < 1e-12
    passed = headline <= policy['headline_normalized_ratio_max'] and p05 > policy['gain_p05_min_exclusive']
    assert passed == result['local_discovery_screen_passed']
    checks.append(dict(candidate=result['candidate'], sha256=result['sha256'], both_full_gate=True,
                       headline=headline, gain_p05=p05, operations=operations, qualifies=passed,
                       development_result_sha256=sha(rp.read_bytes())))
assert checks
report = dict(at_utc=datetime.now(timezone.utc).isoformat(), run=args.run,
              state='INDEPENDENT_HASH_AND_ARITHMETIC_CHECK_PASS', checks=checks,
              limitation='Completed discovery only; no confirmation or adoption, no timing rerun or causal attribution.')
output = 'astra-first-cost-check.json' if args.run == 40183711165 else f'astra-cost-check-{args.run}.json'
HERE.joinpath(output).write_text(json.dumps(report, ensure_ascii=False, indent=2) + '\n', encoding='utf-8')
print(json.dumps(report, ensure_ascii=False))
