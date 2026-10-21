"""Audit B7 inclusive phases without counting nested containers as separate work."""
from pathlib import Path
import argparse
import hashlib
import json

ROOT = Path(__file__).resolve().parents[1]
EXPECTED = {
    'public628': '784e02703c98a32f85753cae4f3b62aea3f505d91088869f327e0ad646629c14',
    'r26-b-628-shared-cache-fix1': '582c3ea7236dfaa93a801a265713e3c96175d6978d895e62a9bea024fbdd39ac',
    'r26-b-628-cache-hint': '1d55b3acf2db9c737b4af84a234b96d33748089dc0bb80300314192fde0581cd',
}
ALIASES = {
    'parse': ['parse'],
    'base': ['SFbase', 'r26_b_SFbase'],
    'shape': ['SFshape', 'r26_b_SFshape'],
    'prev': ['SFprev'],
    'small': ['SFsmallmatches', 'r26_b_small_cached', 'r26_b_SFsmallmatches_hint'],
    'more': ['SFmorematches', 'r26_b_more_cached', 'r26_b_SFmorematches_hint'],
    'solve': ['SFsolve'],
    'suffix_seed': ['SFseed'],
    'prefix_trials': ['SFprefix'],
    'refine': ['refine'],
    'classifier_inclusive': ['Z469'],
}
SHAPE_CHILDREN = ['prev', 'small', 'more', 'solve', 'suffix_seed', 'prefix_trials']


def sha(raw):
    return hashlib.sha256(raw).hexdigest()


def sum_phases(rows):
    total = {key: sum(row['phases_ns'][key] for row in rows) for key in ALIASES}
    total['shape_other'] = total['shape'] - sum(total[key] for key in SHAPE_CHILDREN)
    total['parse_other'] = total['parse'] - total['base'] - total['shape'] - total['refine']
    return {
        'files': len(rows),
        'phase_seconds': {key: value / 1e9 for key, value in total.items()},
        'percent_of_observed_parse': {
            key: 100 * value / total['parse'] if total['parse'] else None
            for key, value in total.items()
        },
    }


def analyze(receipt_path, standard_path):
    raw = receipt_path.read_bytes()
    receipt = json.loads(raw)
    standard_raw = standard_path.read_bytes()
    standard = json.loads(standard_raw)
    baseline = standard['analyses'][0]['rows']
    cache_files = {row['file'] for row in baseline if not row['identical_token_and_output']}
    input_hashes = {row['file']: row['input_sha256'] for row in baseline}
    assert len(cache_files) == 7 and len(input_hashes) == 28
    entries = receipt['entries']
    assert set(entries) == set(EXPECTED)
    output = {}
    for name, expected in EXPECTED.items():
        entry = entries[name]
        assert entry['source_hashes']['parse.rs'] == expected
        assert {row['file']: row['input_sha256'] for row in entry['rows']} == input_hashes
        rows = []
        for row in entry['rows']:
            functions = row['functions']
            phases = {}
            for phase, aliases in ALIASES.items():
                active = [fn for fn in aliases if functions.get(fn, {}).get('calls', 0)]
                # On the real single-file path the original and cloned implementations
                # are alternatives. Refuse to sum them if a future receipt mixes paths.
                assert len(active) <= 1, (name, row['file'], phase, active)
                phases[phase] = sum(functions.get(fn, {}).get('inclusive_ns', 0) for fn in aliases)
            rows.append({
                'file': row['file'], 'input_sha256': row['input_sha256'],
                'actual_b3_changed_output': row['file'] in cache_files,
                'phases_ns': phases, 'original_function_counters': functions,
            })
        output[name] = {
            'source_hashes': entry['source_hashes'],
            'all': sum_phases(rows),
            'seven_active_cache_files': sum_phases([row for row in rows if row['actual_b3_changed_output']]),
            'other_twenty_one_files': sum_phases([row for row in rows if not row['actual_b3_changed_output']]),
            'rows': rows,
        }
    original_rows = {row['file']: row for row in output['public628']['rows']}
    priority_models = []
    for block in standard['analyses']:
        if block['candidate'] != 'r26-b-628-shared-cache-fix1':
            continue
        model = {key: 0.0 for key in ['base_all', 'shape_all', 'refine_all',
                                     'cache_prev', 'cache_collectors', 'cache_solve', 'cache_shape_all']}
        for row in block['rows']:
            profiled = original_rows[row['file']]
            phases = profiled['phases_ns']
            weight = row['parent']['parse_s'] / row['parent_incumbent']['total_s'] / 28 / block['parent_axis'] * 100
            scale = weight / phases['parse']
            for phase in ['base', 'shape', 'refine']:
                model[phase + '_all'] += scale * phases[phase]
            if profiled['actual_b3_changed_output']:
                model['cache_prev'] += scale * phases['prev']
                model['cache_collectors'] += scale * (phases['small'] + phases['more'])
                model['cache_solve'] += scale * (phases['solve'] + phases['suffix_seed'] + phases['prefix_trials'])
                model['cache_shape_all'] += scale * phases['shape']
        priority_models.append({'block': block['block'], 'parent_axis': block['parent_axis'],
                                'relative_parent_axis_percent_proxy': model})
    return {
        'status': 'VERIFIED_SAME_RECEIPT_COARSE_PHASE_ACCOUNTING_ONLY',
        'run_id': receipt['run_id'], 'git_sha': receipt['git_sha'],
        'receipt': str(receipt_path.relative_to(ROOT)).replace('\\', '/'),
        'receipt_sha256': sha(raw),
        'standard_decomposition': str(standard_path.relative_to(ROOT)).replace('\\', '/'),
        'standard_decomposition_sha256': sha(standard_raw),
        'entries': output,
        'phase_fraction_priority_models': priority_models,
        'phase_fraction_priority_model_status': 'INFERRED_PRIORITY_ONLY: transfer observed inclusive phase fractions into actual B3 original parser / paired incumbent weights. This is an ideal-elimination planning proxy, not a valid upper bound, causal estimate, expected performance or actual speedup.',
        'method': 'Alternative original/clone phase calls are checked per file. Shape children exclude the nested heavy container; parse children exclude nested seed and classifier containers. Residuals retain wrapper, cost, patch, copy and allocation work.',
        'limits': [
            'Observer clocks and changed wrapper layouts are diagnostic. Cross-variant observed seconds are not original paired benchmark gains, a causal attribution or a recoverable speedup bound.',
            'Seven active-cache files are selected from actual B3 changed token/output; the other21 include non-SF and uncached-SF routes. This partition does not identify allocation or classifier causation.',
            'Inclusive classifier and original function counters are recorded separately and cannot be added to disjoint phase children.',
            'No exact proof, full gate, private admission, current score or reward conclusion.',
        ],
    }


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument('receipt', type=Path)
    parser.add_argument('--standard', type=Path, default=ROOT / 'evidence/round26/route-b/b3fix1-cost-decomposition.json')
    parser.add_argument('--output', type=Path, default=ROOT / 'evidence/round26/route-b/b7-phase-accounting.json')
    args = parser.parse_args()
    result = analyze(args.receipt.resolve(), args.standard.resolve())
    args.output.write_bytes((json.dumps(result, indent=2) + '\n').encode())
    print(json.dumps({name: entry['all'] for name, entry in result['entries'].items()}, indent=2))


if __name__ == '__main__':
    main()
