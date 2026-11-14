"""Read only prior discovery controls; structural scope, never forecast a speed."""
from pathlib import Path
import hashlib
import json

HERE = Path(__file__).resolve().parent
ROOT = next(p for p in HERE.parents if (p / 'competitions/floatlib/pins.json').is_file())
PRIOR = HERE.parent / ('ci-runs/40602369221/download-ce1e0ed55a6c4efe9bb9847d082e65d1/'
    'diagnostics/f01-d7-public-suite/public-suite/diagnostics/f01-r22-dev-resident8-cost1/runtime-cost')
sha = lambda b: hashlib.sha256(b).hexdigest()


def load(path, bindings):
    raw = path.read_bytes()
    bindings[str(path.relative_to(ROOT)).replace('\\', '/')] = sha(raw)
    return json.loads(raw)


def main():
    inputs = {}
    result = load(PRIOR / 'result.json', inputs)
    assert result['complete'] and result['measurement_complete']
    assert result['source_sha256'] == '24c60123b76214c4da31d2765fca0010985c0289dad77e8bc18b2de507625e34'
    rows = []
    structural = []
    for seed in (2220001, 2220003):
        plan = load(PRIOR / f'plan-{seed}.json', inputs)
        cases = plan['cases']
        assert len(cases) == 156 and sum(c['timed'] for c in cases) == 152
        bmm = [c for c in cases if c['timed'] and c['kernel'] == 'bmm']
        eligible = [c for c in bmm if c['n'] > 1 and c['m'] >= 4 and c['p'] >= 4]
        narrow = [c for c in eligible if c['p'] <= 8]
        for c in eligible:
            p, n, m, b = c['p'], c['n'], c['m'], c['batch']
            g2, g4, h = (p + 1) // 2, (p + 3) // 4, m // 4
            structural.append({'seed': seed, 'name': c['name'], 'shape': [b, m, n, p],
                'retained_control_route': 'B2' if p <= 8 else 'bmmBeforeUnderflowZero',
                'A_panel_records_per_call': b * h * n,
                'R16_B2_records_per_call': b * g2 * n,
                'new_B4_records_per_call': b * g4 * n,
                'R16_fullblock_loop_iterations': b * h * g2 * n,
                'new_fullblock_loop_iterations': b * h * g4 * n,
                'R16_fullblock_padded_MACs': b * h * g2 * n * 8,
                'new_fullblock_padded_MACs': b * h * g4 * n * 16,
                'extra_phantom_MACs_vs_R16': b * h * n * (16 * g4 - 8 * g2),
                'tail_rows_per_batch': m % 4})
        for order in (0, 3, 4, 7):
            actual = load(PRIOR / f'{seed}-{order}-control-rows.json', inputs)
            assert set(actual) == {c['name'] for c in cases}
            assert all(actual[c['name']]['timed'] == c['timed'] for c in cases)
            whole = sum(actual[c['name']]['best_ns'] for c in cases if c['timed'])
            bt = sum(actual[c['name']]['best_ns'] for c in bmm)
            et = sum(actual[c['name']]['best_ns'] for c in eligible)
            nt = sum(actual[c['name']]['best_ns'] for c in narrow)
            rows.append({'seed': seed, 'order': order, 'whole_ns': whole,
                'BMM_ns': bt, 'eligible_case_ns': et, 'eligible_narrow_case_ns': nt,
                'BMM_fraction_whole': bt / whole,
                'eligible_case_fraction_whole_upper_touch': et / whole,
                'eligible_narrow_case_fraction_whole_upper_touch': nt / whole,
                'hypothetical_half_total_eligible_case_time_fraction_whole': et / whole / 2,
                'eligible_cases': len(eligible), 'eligible_narrow_cases': len(narrow)})
    report = {'scope': 'Prior seen discovery controls only. No threshold, seed or new implementation selection.',
        'input_source_sha256': result['source_sha256'], 'rows': rows,
        'structural_case_ledger': structural, 'input_bindings': inputs,
        'limitations': ['Eligible case cost includes untouched guard/prep/output/tails/replay.',
            'Outer UnderflowZero may bypass the new core; eligible times are only loose touch bounds.',
            'Hypothetical half-time is an arithmetic scenario, not a recoverable-work or speed estimate.',
            'R16 ledger compares prepared4x2, while retained wide control can use F10/other layouts.',
            'Actual dynamic hot-loop fraction, peak memory, allocation/RC time and whole gain are UNKNOWN.']}
    (HERE / 'resident16-exposure.json').write_text(json.dumps(report, indent=2) + '\n', encoding='utf-8')
    print(json.dumps({'rows': rows, 'structural_cases': len(structural)}))


if __name__ == '__main__':
    main()
