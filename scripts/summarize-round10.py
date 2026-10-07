"""Recompute Round 10 evidence, grouping proof variants by identical Rust bytes."""
from pathlib import Path
import argparse
import hashlib
import json
import statistics
from round3 import load_scorer

ROOT = Path(__file__).resolve().parents[1]


def sha(path):
    return hashlib.sha256(path.read_bytes()).hexdigest()


def main():
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument('receipts', type=Path, nargs='+')
    ap.add_argument('--snapshot', type=Path, required=True)
    ap.add_argument('--output', type=Path, default=ROOT / 'evidence/round10/final-summary.json')
    args = ap.parse_args()
    pages = json.loads(args.snapshot.read_text())
    assert len({p['context']['snapshot_id'] for p in pages}) == 1
    competition_path = args.snapshot.parent / 'competition.json'
    competition = json.loads(competition_path.read_text())
    assert competition['current_snapshot_id'] == pages[0]['context']['snapshot_id']
    policy = competition['policy']
    assert policy['scoring_method'] == 'local-global-improvement-space-log'
    rows = [r for p in pages for r in p['items']]
    assert len({r['id'] for r in rows}) == len(rows)
    formal = next(r['metrics'] for r in rows if r['id'] == '361')
    front = [r for r in rows if (r.get('score') or {}).get('on_frontier')]
    sc = load_scorer(ROOT / 'sources/conjectures-optimisation-deflate/validator/scoring/pareto.py')
    bounds = sc.Boundaries(float(policy['max_balanced_time_ratio']), float(policy['max_mean_file_compression_pct']))
    points = [sc.Point(r['id'], r['metrics']['balanced_time_ratio'], r['metrics']['mean_file_compression_pct']) for r in front]
    weights = sc.local_global_improvement_space_log_weights(sc.pareto_front(points), bounds)
    replay_error = max(abs(weights[r['id']] - r['score']['pareto_weight']) for r in front)
    assert replay_error < 1e-10

    def geometry(x, y):
        dominating = [p.name for p in points if p.time_s <= x and p.ratio_pct <= y]
        eligible = 0 < x <= bounds.time_s and 0 < y <= bounds.ratio_pct and not dominating
        w = sc.local_global_improvement_space_log_weights(sc.pareto_front(points + [sc.Point('hypothetical', x, y)]), bounds)
        return {'time_ratio': x, 'compressed_pct': y, 'on_geometric_frontier': eligible,
                'conditional_share_pct': w.get('hypothetical', 0) * 100 if eligible else 0,
                'dominating_ids': dominating,
                'size_gap_pp': max(0, y - min((p.ratio_pct for p in points if p.time_s <= x), default=bounds.ratio_pct))}

    groups, runs, checks, shadows = {}, [], [], []
    deterministic_records = {}
    for folder in args.receipts:
        state = json.loads((folder / 'state.json').read_text())
        ci = json.loads((folder / 'ci-run.json').read_text())
        assert ci['status'] == 'completed', 'Final result requires a completed CI receipt'
        raw_manifest = json.loads((folder / 'raw-artifact-files.json').read_text())
        assert all((folder / name).stat().st_size == record['bytes'] and sha(folder / name) == record['sha256']
                   for name, record in raw_manifest['files'].items()), 'Original artifact file bytes changed'
        assert str(ci['databaseId']) == state['run_id'] and ci['headSha'] == state['git_sha']
        entries = {e['name']: e for e in state['spec']['entries']}
        by = {}
        environment = None
        for metric in state['metrics']:
            name, block = metric['candidate'], metric['round']
            entry = entries[name]
            records = [json.loads(line) for line in (folder / f'round{block}-{name}.jsonl').read_text().splitlines()]
            meta, files = records[0], [r for r in records if r['kind'] == 'file']
            assert meta['corpus'] == 'corpus-stage1' and len(files) == 28
            observed_environment = {k: meta[k] for k in ('os', 'arch', 'rustc_version', 'cpu_model', 'cpu_governor', 'warmup_rounds', 'measured_rounds', 'benchmark_provenance')}
            if environment is None:
                environment = observed_environment
            assert environment == observed_environment
            assert meta['warmup_rounds'] == 1 and meta['measured_rounds'] == 11
            assert sum(f['raw_bytes'] for f in files) == 15930000
            assert meta['methods'][name]['source_sha256'] == entry['hashes']['parse.rs'] == metric['source_sha256']
            ratios = []
            for f in files:
                identity = (metric['source_sha256'], f['file'])
                record_identity = (f['sha256'], f['methods'][name]['tokens_sha256'], f['methods'][name]['output_sha256'], f['methods'][name]['output_bytes'])
                assert deterministic_records.setdefault(identity, record_identity) == record_identity
                times = {}
                for method in (name, 'incumbent'):
                    record = f['methods'][method]
                    reps = [r for r in record['reps'] if r['phase'] == 'measured']
                    assert record['deterministic'] and not record['errors'] and len(reps) == 11
                    assert all(r['total_s'] > 0 for r in reps)
                    times[method] = statistics.median(r['total_s'] for r in reps)
                ratios.append(times[name] / times['incumbent'])
            assert abs(statistics.mean(ratios) - metric['time']) < 1e-12
            assert abs(statistics.mean(100 * f['methods'][name]['output_bytes'] / f['raw_bytes'] for f in files) - metric['size_pct']) < 1e-12
            assert (name, block) not in by
            by[name, block] = metric
        runs.append({'run_id': state['run_id'], 'batch': state['batch'], 'source_commit': ci['headSha'],
                     'conclusion': ci['conclusion'], 'url': ci['url'], 'public_paired_processes': len(by), 'measurement_failures': state['failures'], 'environment': environment})
        for entry in entries.values():
            name = entry['name']
            blocks = sorted(b for n, b in by if n == name)
            if not blocks:
                continue
            if name == 'mid-shadow':
                shadows.append({'run_id': state['run_id'], 'relative_time_changes_pct': [100 * (by[name, b]['time'] / by['public361', b]['time'] - 1) for b in blocks]})
            if entry.get('control') or not name.startswith('r10-'):
                continue
            assert all(sha(ROOT / entry['path'] / f) == h for f, h in entry['hashes'].items())
            assert len(blocks) >= 2
            source = entry['hashes']['parse.rs']
            size, base_size = by[name, blocks[0]]['size_pct'], by['public361', blocks[0]]['size_pct']
            assert all(by[name, b]['size_pct'] == size and by['public361', b]['size_pct'] == base_size for b in blocks)
            group = groups.setdefault(source, {'candidate': name.removesuffix('-proof'), 'source_sha256': source,
                        'public_size_pct': size, 'public_size_change_pp': size - base_size, 'runs': [], 'gates': []})
            assert group['public_size_pct'] == size
            group['runs'].append({'run_id': state['run_id'], 'candidate_name': name, 'proof_sha256': entry['hashes']['Parse.lean'], 'blocks': blocks,
                                  'public_time': statistics.mean(by[name, b]['time'] for b in blocks),
                                  'relative_times': [by[name, b]['time'] / by['public361', b]['time'] for b in blocks],
                                  'relative_to_parent_times': [by[name, b]['time'] / by['r9-block-scalar', b]['time'] for b in blocks],
                                  'parent_size_pct': by['r9-block-scalar', blocks[0]]['size_pct'],
                                  'projected_size_pct': formal['mean_file_compression_pct'] * size / base_size})
            if name in state['gates']:
                for f, h in entry['hashes'].items():
                    assert sha(folder / ('input-' + name) / f) == h
                group['gates'].append({'run_id': state['run_id'], 'candidate': name, 'files': entry['hashes'], 'accepted': state['gates'][name].get('accepted', False)})
        eq = folder / 'equivalence-research.json'
        if eq.exists():
            checks.extend({'run_id': state['run_id'], **c} for c in json.loads(eq.read_text()).get('cases', []))
    candidates = []
    for g in groups.values():
        rr = g['runs']
        assert len({r['run_id'] for r in rr}) == len(rr), 'Do not count the same runner twice'
        relative = statistics.mean(statistics.mean(r['relative_times']) for r in rr)
        x = formal['balanced_time_ratio'] * relative
        y = rr[0]['projected_size_pct']
        assert all(abs(r['projected_size_pct'] - y) < 1e-12 for r in rr)
        stress_x = formal['balanced_time_ratio'] * max(t for r in rr for t in r['relative_times']) * 1.02
        g.update(independent_jobs=len(rr), public_blocks=sum(len(r['blocks']) for r in rr),
                 public_time=statistics.mean(r['public_time'] for r in rr), relative_time_change_pct=100 * (relative - 1),
                 relative_time_change_pct_vs_parent=100 * (statistics.mean(statistics.mean(r['relative_to_parent_times']) for r in rr) - 1),
                 public_size_change_pp_vs_parent=g['public_size_pct'] - rr[0]['parent_size_pct'],
                 same_family_projection=geometry(x, y), conservative_projection=geometry(stress_x, max(y + 0.01, g['public_size_pct'] * 1.008)),
                 has_verified_source_proof_pair=any(v['accepted'] for v in g['gates']),
                 verified_source_proof_pairs=[v for v in g['gates'] if v['accepted']])
        candidates.append(g)
    candidates.sort(key=lambda g: (-g['conservative_projection']['conditional_share_pct'], -g['same_family_projection']['conditional_share_pct'], g['public_size_pct'], g['same_family_projection']['time_ratio']))
    result = {'status': 'COMPLETED_CI_RECEIPTS_RECOMPUTED', 'snapshot': pages[0]['context'], 'scorer_replay_max_error': replay_error,
              'official_policy': policy, 'competition_capture_sha256': sha(competition_path),
              'formal_anchor': {'submission_id': '361', 'metrics': formal}, 'completed_ci_runs': runs, 'candidate_count': len(candidates),
              'public_paired_processes': sum(r['public_paired_processes'] for r in runs), 'same_byte_shadows': shadows,
              'finite_equivalence_checks': checks, 'candidates': candidates, 'new_formal_submissions': 0, 'new_chain_transactions': 0,
              'limits': ['Public metrics are VERIFIED; formal transfers and conditional geometric shares are INFERRED.',
                         'Proof status belongs to the exact source/proof pair recorded in gates, not every proof variant.',
                         'Adverse scenario: worst observed paired relative time plus 2%; size max(family+0.01pp, public*1.008). This is not a confidence interval.',
                         'Private corpus, online admission and rewards for these candidates are UNKNOWN.']}
    args.output.write_text(json.dumps(result, indent=2) + '\n')
    print(json.dumps({'runs': len(runs), 'candidates': len(candidates), 'paired_processes': result['public_paired_processes'],
                      'results': [{k: g[k] for k in ('candidate', 'public_time', 'public_size_pct', 'relative_time_change_pct_vs_parent', 'public_size_change_pp_vs_parent', 'same_family_projection', 'conservative_projection', 'verified_source_proof_pairs')} for g in candidates]}))


if __name__ == '__main__':
    main()
