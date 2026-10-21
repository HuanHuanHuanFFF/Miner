"""Retain prior hash32 measurements even when its old comparison parent is absent."""
from pathlib import Path
import argparse, hashlib, json, statistics
from round3 import load_scorer
from round10_payability import load_flat_rows, validate_policy_for_replay

ROOT = Path(__file__).resolve().parents[1]

def read(p): return json.loads(p.read_bytes())
def digest(p): return hashlib.sha256(p.read_bytes()).hexdigest()

def main():
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument('--capture', type=Path, required=True)
    ap.add_argument('--output', type=Path, required=True)
    args = ap.parse_args()
    competition, context, rows = load_flat_rows(args.capture)
    scorer = load_scorer(ROOT / 'sources/conjectures-optimisation-deflate/validator/scoring/pareto.py')
    policy = validate_policy_for_replay(competition['policy'], rows, scorer)
    points = [scorer.Point(r['id'], r['metrics']['balanced_time_ratio'], r['metrics']['mean_file_compression_pct']) for r in rows if (r.get('score') or {}).get('on_frontier')]
    formal = next(r['metrics'] for r in rows if r['id'] == '514')
    candidate = ROOT / 'candidates/r14-514-hash32'
    pair = {f: digest(candidate / f) for f in ('parse.rs', 'Parse.lean')}
    runs = []

    def share(x, y):
        return scorer.local_global_improvement_space_log_weights(scorer.pareto_front(points + [scorer.Point('__continuing_hash32__', x, y)])).get('__continuing_hash32__', 0.0)

    for round_name in ('round14', 'round15'):
        for path in sorted((ROOT / 'evidence' / round_name).glob('*/*/gate/state.json')):
            state = read(path)
            matches = [e for e in state['spec']['entries'] if e['hashes']['parse.rs'] == pair['parse.rs']]
            if not matches: continue
            ci = read(path.parent / 'ci-run.json')
            if ci['status'] != 'completed': continue
            assert str(ci['databaseId']) == state['run_id'] and ci['headSha'] == state['git_sha']
            inv = read(path.parent / 'raw-artifact-files.json')['files']
            assert digest(path) == inv['state.json']['sha256']
            entry = matches[0]; name = entry['name']
            assert entry['hashes'] == pair
            anchor = next(e['name'] for e in state['spec']['entries'] if e.get('formal_id') == '514')
            metrics = {(m['candidate'], m['round']): m for m in state['metrics']}
            blocks = sorted(b for n,b in metrics if n == name)
            if not blocks: continue
            # Recompute both paired axes from actual repetitions, not state alone.
            for n in (name, anchor):
                for b in blocks:
                    p = path.parent / f'round{b}-{n}.jsonl'
                    assert digest(p) == inv[p.name]['sha256']
                    records = [json.loads(line) for line in p.read_text().splitlines()]
                    files = [r for r in records if r['kind'] == 'file']
                    assert len(files) == 28 and records[0]['measured_rounds'] == 11
                    axes = []
                    for f in files:
                        times = []
                        for method in (n, 'incumbent'):
                            reps = [r['total_s'] for r in f['methods'][method]['reps'] if r['phase'] == 'measured']
                            assert len(reps) == 11 and all(v > 0 for v in reps)
                            times.append(statistics.median(reps))
                        axes.append(times[0] / times[1])
                    assert abs(statistics.mean(axes) - metrics[n,b]['time']) < 1e-12
                    size = statistics.mean(100 * f['methods'][n]['output_bytes'] / f['raw_bytes'] for f in files)
                    assert abs(size - metrics[n,b]['size_pct']) < 1e-12
            relative = [metrics[name,b]['time'] / metrics[anchor,b]['time'] for b in blocks]
            y = formal['mean_file_compression_pct'] * metrics[name,blocks[0]]['size_pct'] / metrics[anchor,blocks[0]]['size_pct']
            xs = [formal['balanced_time_ratio'] * v for v in relative]
            runs.append({'run_id': state['run_id'], 'receipt': path.parent.relative_to(ROOT).as_posix(), 'role': 'control' if entry.get('control') else 'candidate', 'block_relative_to514': relative, 'block_pool_fractions': [share(x,y) for x in xs], 'center_pool_fraction': share(statistics.mean(xs),y), 'projected_size_pct': y})
    assert runs and len(runs) == len({r['run_id'] for r in runs})
    y = runs[0]['projected_size_pct']; assert all(abs(r['projected_size_pct']-y) < 1e-12 for r in runs)
    x = formal['balanced_time_ratio'] * statistics.mean(statistics.mean(r['block_relative_to514']) for r in runs)
    result = {'status': 'RAW_PAIRED_AXES_RECOMPUTED_CONDITIONAL_PROJECTION_ONLY', 'snapshot': context, 'policy_validation': policy, 'source_pair': pair, 'runs': runs, 'equal_runner_mean_coordinate': {'x': x, 'y': y, 'pool_percent': 100*share(x,y)}, 'blocks_at_least1percent': sum(v >= .01 for r in runs for v in r['block_pool_fractions']), 'blocks': sum(len(r['block_relative_to514']) for r in runs), 'limits': 'All collected final R14/R15 observations of this exact source, including control roles. No abs15 comparison is invented where absent. A mean in the narrow533-539 interval does not establish stable1percent; block counts are not success probabilities. No promotion, private admission or new reward is implied.'}
    args.output.write_bytes((json.dumps(result, indent=2) + '\n').encode())
    print(json.dumps({'runners': len(runs), 'mean': result['equal_runner_mean_coordinate'], 'passing_blocks': result['blocks_at_least1percent'], 'blocks': result['blocks']}))

if __name__ == '__main__': main()
