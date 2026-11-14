"""Conservative interval partitions of already-seen discovery plans; no sampling/timing."""
from pathlib import Path
from collections import Counter
import hashlib
import json

HERE = Path(__file__).resolve().parent
ROUND = HERE.parent
ROOT = next(p for p in HERE.parents if (p / 'AGENTS.md').is_file())
SHA = lambda p: hashlib.sha256(p.read_bytes()).hexdigest()


def clamp(e):
    return max(1, min(254, e))


def classify(c):
    # These conservatively remain UNKNOWN even when a special/zero path might be narrower.
    if c['mag'] == 2:
        return {'domain': 'UNKNOWN_RAW32', 'reason': 'Raw uniform32 words can be normal, zero, subnormal or special.'}
    if c['specRate'] or c['zeroPct'] or c['subPct']:
        return {'domain': 'UNKNOWN_MIXED_CONSTRUCTORS',
                'reason': 'Special/zero/subnormal constructor enabled; do not substitute an ordinary-only interval.'}
    lo = c['center'] - (min(32, c['spread']) if c['mag'] == 1 else c['spread'])
    hi = c['center'] if c['mag'] == 1 else c['center'] + c['spread']
    shift = c['scaleShift'] if c['scaleBlock'] else 0
    lo, hi = clamp(lo - shift), clamp(hi + shift)
    relation = c['relation']
    if relation == 6:
        slo, shi = lo + clamp(lo - c['relParam']), hi + clamp(hi - c['relParam'])
    elif relation == 5:
        slo, shi = lo + min(lo, 127), hi + max(hi, 127)
    else:
        # relations1/2/3/7 preserve exponent; relation4 is an ordinary fixed second
        # value in this same safe interval; relation0 has independent ordinary values.
        slo, shi = 2 * lo, 2 * hi
    domain = 'GUARANTEED_ACCEPT' if 128 <= slo and shi <= 380 else (
        'GUARANTEED_MISS' if shi < 128 or slo > 380 else 'POSSIBLE_BOTH')
    return {'domain': domain, 'first_exponent_interval': [lo, hi], 'sum_exponent_interval': [slo, shi],
            'bound_kind': 'Conservative interval over all positions, no sampled frequency or time estimate.'}


def main():
    bench = ROOT / 'competitions/floatlib/research/astra-collab-20261023-r7/upstream/BenchSuite.lean'
    assert SHA(bench) == '2f1672738e07851fdb24ed968c248fc2e6d8a3e677c27763ebd489ada9425a9f'
    results = []
    for seed in (2220001, 2220003):
        matches = list((ROUND / 'ci-runs/40590900980').rglob(f'plan-{seed}.json'))
        assert len(matches) == 1
        plan_path = matches[0]
        plan = json.loads(plan_path.read_bytes())
        assert len(plan['cases']) == 156
        cases = [{'name': c['name'], 'work': c['work'], 'timed': c['timed'], 'parameters': c,
                  **classify(c)} for c in plan['cases'] if c['kernel'] == 'mul']
        counts = Counter(c['domain'] for c in cases if c['timed'])
        work = {k: sum(c['work'] for c in cases if c['timed'] and c['domain'] == k) for k in counts}
        results.append({'seed': seed, 'plan_path': str(plan_path), 'plan_sha256': SHA(plan_path),
                        'all_mul_cases': len(cases), 'timed_mul_cases': sum(c['timed'] for c in cases),
                        'timed_case_counts': dict(counts), 'timed_work_counts': work, 'cases': cases})
    out = {'BenchSuite_path': str(bench), 'BenchSuite_sha256': SHA(bench),
           'scope': 'Static domain partition for already-seen discovery2220001/3 only. Pair/work/case counts are not CPU time shares, speed bounds, probabilities, or hidden-suite coverage.',
           'purpose': 'Annotate future same-binary complete measurements; retain all categories and all slow cases. UNKNOWN constructor cases require actual input tracing before any hit-rate statement.',
           'plans': results}
    (HERE / 'guard-domain-partition.json').write_text(json.dumps(out, ensure_ascii=False, indent=2) + '\n', encoding='utf-8')
    print(json.dumps([{k: p[k] for k in ('seed', 'timed_mul_cases', 'timed_case_counts', 'timed_work_counts')} for p in results]))


if __name__ == '__main__':
    main()
