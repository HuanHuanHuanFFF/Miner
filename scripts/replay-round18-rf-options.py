"""Check whether restoring known RF quality is promising before another cloud run."""
from pathlib import Path
import argparse
import hashlib
import itertools
import json
import statistics as st
from round10_payability import load_flat_rows, load_official_scorer, validate_policy_for_replay

ROOT = Path(__file__).resolve().parents[1]
NAME = 'r18-586-selective-rf'


def read(path):
    return json.loads(path.read_bytes())


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--capture', type=Path, required=True)
    parser.add_argument('--analysis', type=Path, required=True)
    parser.add_argument('--output', type=Path, required=True)
    args = parser.parse_args()
    assert not args.output.exists()
    comp, context, rows = load_flat_rows(args.capture)
    scorer = load_official_scorer()
    validate_policy_for_replay(comp['policy'], rows, scorer)
    bounds = scorer.Boundaries(comp['policy']['max_balanced_time_ratio'],
                               comp['policy']['max_mean_file_compression_pct'])
    formal = next(row['metrics'] for row in rows if row['id'] == '586')
    frontier = [scorer.Point(r['id'], r['metrics']['balanced_time_ratio'],
                            r['metrics']['mean_file_compression_pct'])
                for r in rows if (r.get('score') or {}).get('on_frontier')]
    analysis = read(args.analysis)
    assert analysis['snapshot']['snapshot_id'] == context['snapshot_id']
    candidate = next(c for c in analysis['candidates'] if c['candidate'] == NAME)
    expected = {(o['run_id'], o['block'], o['calibration']): o['single_pool_share_pct']
                for o in candidate['observations']}
    audit = {}
    blocks = []
    changed = None
    for run in analysis['runs']:
        folder = ROOT / 'evidence/round18' / run['run_id'] / run['batch'] / 'gate'
        inventory = read(folder / 'raw-artifact-files.json')
        state = read(folder / 'state.json')
        entries = {e['name']: e for e in state['spec']['entries']}
        metrics = {(m['candidate'], m['round']): m for m in state['metrics']}
        for block in range(1, 5):
            programs = {}
            for name in (NAME, 'public586', 'public586-shadow'):
                path = folder / f'round{block}-{name}.jsonl'
                data = path.read_bytes()
                assert hashlib.sha256(data).hexdigest() == inventory['files'][path.name]['sha256']
                audit[path.relative_to(ROOT).as_posix()] = hashlib.sha256(data).hexdigest()
                lines = [json.loads(line) for line in data.splitlines()]
                assert lines[0]['methods'][name]['source_sha256'] == entries[name]['hashes']['parse.rs']
                files = {}
                for row in lines:
                    if row['kind'] != 'file':
                        continue
                    medians = {}
                    for method in (name, 'incumbent'):
                        method_row = row['methods'][method]
                        assert method_row['deterministic'] and not method_row['errors']
                        reps = [r['total_s'] for r in method_row['reps'] if r['phase'] == 'measured']
                        assert len(reps) == 11
                        medians[method] = st.median(reps)
                    files[row['file']] = {
                        'input_sha256': row['sha256'],
                        'time': medians[name] / medians['incumbent'],
                        'size_pct': 100 * row['methods'][name]['output_bytes'] / row['raw_bytes'],
                        'bytes': row['methods'][name]['output_bytes'],
                    }
                assert len(files) == 28
                assert abs(st.mean(f['time'] for f in files.values()) - metrics[name, block]['time']) < 1e-12
                programs[name] = files
            assert set(programs[NAME]) == set(programs['public586'])
            for filename in programs[NAME]:
                assert len({p[filename]['input_sha256'] for p in programs.values()}) == 1
            delta = sorted(filename for filename in programs[NAME]
                           if programs[NAME][filename]['bytes'] > programs['public586'][filename]['bytes'])
            if changed is None:
                changed = delta
            assert delta == changed
            blocks.append({'run_id': run['run_id'], 'block': block, 'programs': programs})
    assert len(blocks) == 8 and len(changed) == 7

    def share(x, y):
        if any(p.time_s <= x and p.ratio_pct <= y for p in frontier):
            return 0.0
        points = scorer.pareto_front(frontier + [scorer.Point('__mixture__', x, y)])
        return 100 * scorer.local_global_improvement_space_log_weights(points, bounds).get('__mixture__', 0)

    options = []
    for flags in itertools.product((False, True), repeat=len(changed)):
        selected = {name for name, flag in zip(changed, flags) if flag}
        observed = []
        for block in blocks:
            programs = block['programs']
            mixed = {filename: programs['public586' if filename in selected else NAME][filename]
                     for filename in programs[NAME]}
            public_x = st.mean(f['time'] for f in mixed.values())
            public_y = st.mean(f['size_pct'] for f in mixed.values())
            for calibration, anchor in (('primary', 'public586'), ('shadow', 'public586-shadow')):
                anchor_x = st.mean(f['time'] for f in programs[anchor].values())
                anchor_y = st.mean(f['size_pct'] for f in programs[anchor].values())
                x = formal['balanced_time_ratio'] * public_x / anchor_x
                y = formal['mean_file_compression_pct'] * public_y / anchor_y
                value = share(x, y)
                if not selected:
                    assert abs(value - expected[block['run_id'], block['block'], calibration]) < 1e-10
                observed.append({'run_id': block['run_id'], 'block': block['block'],
                                 'calibration': calibration, 'projected_time': x,
                                 'projected_size_pct': y, 'conditional_pool_pct': value})
        values = [o['conditional_pool_pct'] for o in observed]
        options.append({'restored_original_rf_files': sorted(selected),
                        'control_variant_median_pct': st.median(values),
                        'range_pct': [min(values), max(values)],
                        'at_least_5_count': sum(v >= 5 for v in values),
                        'at_least_15_count': sum(v >= 15 for v in values),
                        'observations': observed})
    options.sort(key=lambda o: o['control_variant_median_pct'], reverse=True)
    result = {
        'status': 'INFERRED_FIXED_FILE_MIXTURE_OPPORTUNITY_NOT_IMPLEMENTED',
        'snapshot': context,
        'analysis_sha256': hashlib.sha256(args.analysis.read_bytes()).hexdigest(),
        'candidate': NAME, 'optional_files': changed, 'option_count': len(options),
        'blocks': 8, 'runners': 2,
        'best_control_variant_median_option': options[0],
        'any_option_any_control_variant_at_least_5': any(o['at_least_5_count'] for o in options),
        'options': options, 'raw_input_audit': audit,
        'limits': [
            'Only seven existing RF-versus-base output improvements are mixed. This does not cover new matches, costs or engines.',
            'One fixed file-selection set is applied to every measured block; no per-block winner selection.',
            'Free per-file selection is not a runnable content classifier, benchmark score or proof that arbitrary routing cannot work.',
            'Each component keeps its original paired incumbent denominator. Compiler interactions and routing overhead are unknown.',
            'Primary and shadow variants are paired sensitivity views, not sixteen independent samples or success probabilities.',
            'No candidate changes or new cloud runs are justified solely by this illustrative mixture calculation.',
        ],
    }
    args.output.write_bytes((json.dumps(result, indent=2) + '\n').encode())
    print(json.dumps({'snapshot': context, 'option_count': len(options),
                      'any_option_any_control_variant_at_least_5': result['any_option_any_control_variant_at_least_5'],
                      'best': {k: v for k, v in options[0].items() if k != 'observations'}}, indent=2))


if __name__ == '__main__':
    main()
