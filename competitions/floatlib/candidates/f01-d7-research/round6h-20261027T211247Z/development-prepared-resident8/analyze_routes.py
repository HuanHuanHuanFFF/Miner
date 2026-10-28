"""Read-only old public controls x exact622d static router. No new kernels/CI."""
from pathlib import Path
import hashlib
import json
import re

HERE = Path(__file__).resolve().parent
ROOT = next(p for p in HERE.parents if (p / 'competitions/floatlib/pins.json').is_file())
PRIOR = HERE.parent / ('ci-runs/40602369221/download-ce1e0ed55a6c4efe9bb9847d082e65d1/'
    'diagnostics/f01-d7-public-suite/public-suite/diagnostics/f01-r22-dev-resident8-cost1/runtime-cost')
sha = lambda b: hashlib.sha256(b).hexdigest()


def route(c):
    m, n, p = c['m'], c['n'], c['p']
    if 2 <= p <= 8 and n > 1 and m >= 4:
        return 'R15PackedB2'
    if m >= 4 and n > 1 and 0 < p <= 2:
        return 'R14ThinBCache'
    if (n <= 4 and p > 2) or p <= 8:
        return 'DirectContinuous'
    if n <= 4 or p <= 2:
        return 'DirectSmall'
    return 'RowStreamPacked10'


def resident16_eligible(c):
    return c['n'] > 1 and c['m'] >= 4 and c['p'] >= 4


def main():
    bindings = {}
    def read(p):
        raw = p.read_bytes()
        bindings[str(p.relative_to(ROOT)).replace('\\', '/')] = sha(raw)
        return json.loads(raw)
    base = ROOT / 'competitions/floatlib/candidates/f01-r15-dev-packed-b2-1/Kernel.lean'
    base_raw = base.read_bytes()
    assert sha(base_raw) == '622d8394a7127e93dcaf992c62c6dfcff7208d212738409a5e34525dfafd1a58'
    bindings[str(base.relative_to(ROOT)).replace('\\', '/')] = sha(base_raw)
    rows, case_rows = [], []
    for seed in (2220001, 2220003):
        plan = read(PRIOR / f'plan-{seed}.json')
        for order in (0, 3, 4, 7):
            actual = read(PRIOR / f'{seed}-{order}-control-rows.json')
            assert set(actual) == {c['name'] for c in plan['cases']}
            whole = sum(actual[c['name']]['best_ns'] for c in plan['cases'] if c['timed'])
            cases = [c for c in plan['cases'] if c['timed'] and c['kernel'] == 'bmm']
            bt = sum(actual[c['name']]['best_ns'] for c in cases)
            paths = {}
            for c in cases:
                k = route(c)
                r = paths.setdefault(k, {'cases': 0, 'ns': 0, 'outside_resident16_ns': 0,
                    'outside_resident16_cases': 0, 'logical_output_count': 0, 'logical_native_MACs': 0})
                t = actual[c['name']]['best_ns']
                r['cases'] += 1
                r['ns'] += t
                r['logical_output_count'] += c['batch'] * c['m'] * c['p']
                r['logical_native_MACs'] += c['batch'] * c['m'] * c['p'] * c['n']
                if not resident16_eligible(c):
                    r['outside_resident16_ns'] += t
                    r['outside_resident16_cases'] += 1
            for r in paths.values():
                r['fraction_whole'] = r['ns'] / whole
                r['fraction_BMM'] = r['ns'] / bt
                r['outside_resident16_fraction_whole'] = r['outside_resident16_ns'] / whole
            uncovered = [dict(name=c['name'], shape=[c['batch'], c['m'], c['n'], c['p']],
                route=route(c), best_ns=actual[c['name']]['best_ns'],
                logical_outputs=c['batch'] * c['m'] * c['p'],
                logical_MACs=c['batch'] * c['m'] * c['p'] * c['n'],
                row_base_divisions_in_current_direct_or_thin=c['batch'] * c['m']
                    if route(c) in ('DirectContinuous', 'R14ThinBCache') else None,
                specRate=c['specRate'], subPct=c['subPct'], center=c['center'], spread=c['spread'])
                for c in cases if not resident16_eligible(c)]
            uncovered.sort(key=lambda r: r['best_ns'], reverse=True)
            rows.append({'seed': seed, 'order': order, 'whole_ns': whole, 'BMM_ns': bt, 'routes': paths,
                         'top_uncovered': uncovered[:8]})
            if order == 0:
                case_rows.extend(dict(seed=seed, **r) for r in uncovered)
    report = {'status': 'STATIC_ROUTER_PUBLIC_CONTROL_PARTITION', 'rows': rows,
        'all_uncovered_cases_first_control_each_seed': case_rows, 'input_bindings': bindings,
        'limits': ['Mutually exclusive static routes after outerUnderflowZero; actual value-guard bypass UNKNOWN.',
            'Whole-case times include all prep, codec, output, replay and destruction.',
            'Operation and division counts are source-level logical counts, not measured CPU time.',
            'These discovery plans are already seen; private suite distribution and time fractions UNKNOWN.']}
    (HERE / 'route-partition.json').write_text(json.dumps(report, indent=2) + '\n', encoding='utf-8')
    print(json.dumps([{'seed': r['seed'], 'order': r['order'], 'routes': r['routes']} for r in rows]))


if __name__ == '__main__':
    main()
