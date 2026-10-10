"""Audit a same-run public cost matrix and fixed file-mixture opportunities.

Mixtures are diagnostic models, not implemented classifiers or candidate scores.
Both family calibrations are retained; neither is promoted to a private guarantee.
"""
from pathlib import Path
import argparse
import hashlib
import itertools
import json
import statistics as st
from round10_payability import load_flat_rows, load_official_scorer, validate_policy_for_replay

ROOT = Path(__file__).resolve().parents[1]
METHODS = ['r18-586-selective-rf', 'public586', 'public591', 'base591']


def read(p):
    return json.loads(p.read_bytes())


def main():
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument('folder', type=Path)
    ap.add_argument('--capture', type=Path, required=True)
    ap.add_argument('--output', type=Path, required=True)
    args = ap.parse_args()
    args.folder = args.folder.resolve()
    assert not args.output.exists()
    state, inv, ci = (read(args.folder / name) for name in ('state.json', 'raw-artifact-files.json', 'ci-run.json'))
    assert ci['status'] == 'completed' and ci['conclusion'] == 'success'
    assert ci['headSha'] == state['git_sha']
    comp, context, rows = load_flat_rows(args.capture)
    sc = load_official_scorer()
    validate_policy_for_replay(comp['policy'], rows, sc)
    fm = {r['id']: r['metrics'] for r in rows}
    front = [sc.Point(r['id'], r['metrics']['balanced_time_ratio'], r['metrics']['mean_file_compression_pct'])
             for r in rows if (r.get('score') or {}).get('on_frontier')]
    bounds = sc.Boundaries(comp['policy']['max_balanced_time_ratio'], comp['policy']['max_mean_file_compression_pct'])
    entries = {e['name']: e for e in state['spec']['entries']}
    blocks, audit = [], {}
    for b in range(1, state['spec']['screen_blocks'] + 1):
        programs = {}
        for name in METHODS + ['public586-shadow', 'public591-shadow']:
            path = args.folder / f'round{b}-{name}.jsonl'
            raw = path.read_bytes()
            digest = hashlib.sha256(raw).hexdigest()
            assert digest == inv['files'][path.name]['sha256']
            audit[path.relative_to(ROOT).as_posix()] = digest
            data = [json.loads(line) for line in raw.splitlines()]
            meta, files = data[0], {}
            assert meta['measured_rounds'] == 11 and meta['warmup_rounds'] == 1
            assert meta['methods'][name]['source_sha256'] == entries[name]['hashes']['parse.rs']
            for row in data:
                if row['kind'] != 'file':
                    continue
                medians = {}
                for method in (name, 'incumbent'):
                    m = row['methods'][method]
                    assert m['deterministic'] and not m['errors']
                    values = [v['total_s'] for v in m['reps'] if v['phase'] == 'measured']
                    assert len(values) == 11
                    medians[method] = st.median(values)
                files[row['file']] = {
                    'input_sha256': row['sha256'],
                    'time': medians[name] / medians['incumbent'],
                    'candidate_total_s': medians[name],
                    'incumbent_total_s': medians['incumbent'],
                    'bytes': row['methods'][name]['output_bytes'],
                    'size_pct': 100 * row['methods'][name]['output_bytes'] / row['raw_bytes'],
                }
            assert len(files) == 28
            programs[name] = files
        blocks.append({'block': b, 'programs': programs})
    filenames = sorted(blocks[0]['programs'][METHODS[0]])
    centers = {}
    for file in filenames:
        assert len({b['programs'][m][file]['input_sha256'] for b in blocks for m in METHODS}) == 1
        centers[file] = {}
        for method in METHODS:
            observed = [b['programs'][method][file] for b in blocks]
            assert len({o['bytes'] for o in observed}) == 1
            centers[file][method] = {'time': st.mean(o['time'] for o in observed),
                                    'size_pct': observed[0]['size_pct'], 'bytes': observed[0]['bytes']}
    breaks = set()
    for file in filenames:
        for a, b in itertools.combinations(METHODS, 2):
            aa, bb = centers[file][a], centers[file][b]
            dy = aa['size_pct'] - bb['size_pct']
            if dy:
                value = (bb['time'] - aa['time']) / dy
                if value > 0:
                    breaks.add(value)
    thresholds = sorted(breaks)
    probes = [0] + [(a + b) / 2 for a, b in zip([0] + thresholds, thresholds)]
    probes += [thresholds[-1] * 2] if thresholds else [1]
    selections = {tuple(min(METHODS, key=lambda m: centers[f][m]['time'] + lam * centers[f][m]['size_pct'])
                        for f in filenames) for lam in probes}
    selections.update(tuple(m for _ in filenames) for m in METHODS)

    def share(x, y):
        if not (0 < x <= bounds.time_s and 0 < y <= bounds.ratio_pct):
            return 0.0
        if any(p.time_s <= x and p.ratio_pct <= y for p in front):
            return 0.0
        f = sc.pareto_front(front + [sc.Point('__mix__', x, y)])
        return 100 * comp['policy']['pareto_share'] * sc.local_global_improvement_space_log_weights(f, bounds).get('__mix__', 0)

    options = []
    for selected in sorted(selections):
        observations = []
        for block in blocks:
            programs = block['programs']
            x = st.mean(programs[m][f]['time'] for f, m in zip(filenames, selected))
            y = st.mean(programs[m][f]['size_pct'] for f, m in zip(filenames, selected))
            for family in ('586', '591'):
                for label in ('primary', 'shadow'):
                    anchor = 'public' + family + ('-shadow' if label == 'shadow' else '')
                    ax = st.mean(v['time'] for v in programs[anchor].values())
                    ay = st.mean(v['size_pct'] for v in programs[anchor].values())
                    px, py = fm[family]['balanced_time_ratio'] * x / ax, fm[family]['mean_file_compression_pct'] * y / ay
                    observations.append({'block': block['block'], 'family': family, 'calibration': label,
                                         'public_time': x, 'public_size_pct': y,
                                         'projected_time': px, 'projected_size_pct': py,
                                         'conditional_share_pct': share(px, py)})
        summaries = {}
        for family in ('586', '591'):
            values = [o['conditional_share_pct'] for o in observations if o['family'] == family]
            summaries[family] = {'median_pct': st.median(values), 'range_pct': [min(values), max(values)],
                                 'zeros': values.count(0), 'at_least_5': sum(v >= 5 for v in values),
                                 'at_least_15': sum(v >= 15 for v in values)}
        options.append({'selection': dict(zip(filenames, selected)), 'family_summaries': summaries,
                        'observations': observations})
    options.sort(key=lambda o: o['family_summaries']['586']['median_pct'], reverse=True)
    result = {'status': 'INFERRED_FREE_FILE_MIXTURE_DIAGNOSTIC_NOT_CANDIDATE_SCORE', 'snapshot': context,
              'run_id': state['run_id'], 'runner_count': 1, 'blocks': len(blocks), 'raw_audit': audit,
              'same_run_per_file_matrix': centers, 'option_count': len(options), 'options': options,
              'limits': [
                  'File selection is fixed across blocks, generated from supported linear cost tradeoffs; not all possible nonconvex mixtures were searched.',
                  'Selections use public filenames only as a diagnostic; no runnable/private-generalizing classifier or zero-overhead implementation is assumed.',
                  '586 and591 family calibrations are competing transfer assumptions, not confidence bounds; both must be reported.',
                  'Same-source shadows are sensitivity views, not independent runners or success probabilities.',
                  'Standalone component timings retain their paired incumbent denominators. Compiler, shared-stage and routing effects require an actual experiment.',
              ]}
    args.output.write_bytes((json.dumps(result, indent=2) + '\n').encode())
    print(json.dumps({'snapshot': context, 'options': len(options), 'top': options[0],
                      'best_591_family': max(options, key=lambda o: o['family_summaries']['591']['median_pct'])}, indent=2))


if __name__ == '__main__':
    main()
