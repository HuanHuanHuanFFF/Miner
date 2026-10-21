"""Optimistic public-file switching envelope over measured programs, not a candidate.

Normalize each paired block by that block's aggregate public361 axis. This makes
each whole-program point reproduce the R10 same-family projection exactly. Then
allow an impossible free oracle to select a program independently for every file.
This is a diagnostic of the tested set, never an implementable routing rule or a
private-corpus guarantee. Positive envelope points do not authorize file routing.
"""
from pathlib import Path
import argparse
import hashlib
import json
import statistics
import sys

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / 'scripts'))
from round10_payability import analyze_payability, load_flat_rows, load_official_scorer


def load(path):
    return json.loads(path.read_bytes())


def main():
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument('receipts', type=Path, nargs='+')
    ap.add_argument('--capture', type=Path, required=True)
    ap.add_argument('--output', type=Path, required=True)
    args = ap.parse_args()
    competition, context, official = load_flat_rows(args.capture)
    formal = next(r['metrics'] for r in official if str(r['id']) == '361')
    fx, fy = formal['balanced_time_ratio'], formal['mean_file_compression_pct']
    scorer = load_official_scorer()
    groups, hashes, sources = {}, {}, {}
    for folder in args.receipts:
        state, ci = load(folder / 'state.json'), load(folder / 'ci-run.json')
        assert ci['status'] == 'completed'
        entries = {e['name']: e for e in state['spec']['entries']}
        metrics = {(m['candidate'], m['round']): m for m in state['metrics']}
        sources[str(folder / 'state.json')] = hashlib.sha256((folder / 'state.json').read_bytes()).hexdigest()
        for name, entry in entries.items():
            if name not in ('public361', 'r9-block-scalar') and not name.startswith('r10-'):
                continue
            key = entry['hashes']['parse.rs']
            group = groups.setdefault(key, {'name': name.removesuffix('-proof'), 'source_sha256': key, 'jobs': {}})
            assert state['run_id'] not in group['jobs'], 'same Rust appears twice in a run'
            blocks = []
            for n, b in metrics:
                if n != name:
                    continue
                anchor = metrics['public361', b]
                rows = [json.loads(l) for l in (folder / f'round{b}-{name}.jsonl').read_text().splitlines()]
                files = {}
                for r in rows:
                    if r['kind'] != 'file':
                        continue
                    assert hashes.setdefault(r['file'], r['sha256']) == r['sha256']
                    def med(method):
                        data = r['methods'][method]
                        assert data['deterministic'] and not data['errors']
                        reps = [v for v in data['reps'] if v['phase'] == 'measured']
                        assert len(reps) == 11
                        return statistics.median(v['total_s'] for v in reps)
                    files[r['file']] = {
                        'x': fx * med(name) / med('incumbent') / anchor['time'],
                        'y': fy * (100 * r['methods'][name]['output_bytes'] / r['raw_bytes']) / anchor['size_pct'],
                    }
                assert len(files) == 28
                assert abs(statistics.mean(f['x'] for f in files.values()) - fx * metrics[name, b]['time'] / anchor['time']) < 1e-12
                blocks.append(files)
            assert len(blocks) >= 2
            group['jobs'][state['run_id']] = {file: {
                dim: statistics.mean(b[file][dim] for b in blocks) for dim in ('x', 'y')
            } for file in hashes}
    files = sorted(hashes)
    choices = {file: [] for file in files}
    programs = []
    for g in groups.values():
        point = {file: {dim: statistics.mean(job[file][dim] for job in g['jobs'].values()) for dim in ('x', 'y')} for file in files}
        programs.append({'name': g['name'], 'source_sha256': g['source_sha256'], 'jobs': len(g['jobs']),
                         'x': statistics.mean(v['x'] for v in point.values()), 'y': statistics.mean(v['y'] for v in point.values())})
        for file, p in point.items():
            choices[file].append({'name': g['name'], **p})
    # Every switch in min(x + lambda*y) occurs at a pairwise equality. All
    # positive intersections are included, even if dominated: cheap and exact.
    slopes = {0.0}
    for opts in choices.values():
        for i, a in enumerate(opts):
            for b in opts[i+1:]:
                if a['y'] != b['y']:
                    slope = (b['x'] - a['x']) / (a['y'] - b['y'])
                    if slope > 0:
                        slopes.add(slope)
    cuts = sorted(slopes)
    probes = [0.0] + [(a + b)/2 for a, b in zip(cuts, cuts[1:])] + [cuts[-1]*2 + 1]
    envelope, seen = [], set()
    for slope in probes:
        selected = {f: min(choices[f], key=lambda p: (p['x'] + slope*p['y'], p['y'], p['name'])) for f in files}
        key = tuple(selected[f]['name'] for f in files)
        if key in seen:
            continue
        seen.add(key)
        x = statistics.mean(p['x'] for p in selected.values())
        y = statistics.mean(p['y'] for p in selected.values())
        payout = analyze_payability(official, x, y, '453', scorer,
            pareto_share=competition['policy']['pareto_share'], improvement_share=competition['policy']['improvement_share'])
        envelope.append({'x': x, 'y': y, 'lambda': slope,
            'geometric_share_pct': payout['candidate']['geometric_share_pct_of_competition_pareto_pool'],
            'same_hotkey_new_point_share_pct': payout['same_hotkey_payability_if_admission_registration_and_bounty_remain_eligible']['candidate_additional_share_pct'],
            'file_choices': selected})
    best = max(envelope, key=lambda p: p['geometric_share_pct'])
    result = {'status': 'INFERRED_OPTIMISTIC_PUBLIC_FILE_ORACLE', 'snapshot': context,
        'scope': 'Free independent per-file program choice among the measured set. Not an implemented parser, real timing, generalizable route, formal result, or private-corpus bound. Vertices of a convex relaxation are diagnostics; no claim about all interpolated points.',
        'normalization': 'Within each paired block divide each candidate per-file axis contribution by the same-block aggregate public361 axis, multiply by formal361. Average blocks within jobs, then jobs equally. Whole-program averages match the declared family projection.',
        'selection_bias': 'Minima are selected using these same public measurements; noise, overhead, feature prediction and unknown inputs make this deliberately optimistic.',
        'programs': programs, 'file_sha256': hashes, 'evidence_sha256': sources,
        'envelope_vertices': envelope, 'best_vertex_by_geometric_share': best}
    args.output.write_bytes((json.dumps(result, indent=2) + '\n').encode())
    print(json.dumps({'programs': len(programs), 'envelope_vertices': len(envelope), 'best': {k:v for k,v in best.items() if k != 'file_choices'},
        'choices': {name: sum(p['name'] == name for p in best['file_choices'].values()) for name in sorted({p['name'] for p in best['file_choices'].values()})}}))


if __name__ == '__main__':
    main()
