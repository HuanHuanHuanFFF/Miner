"""Replay bounded coordinate requirements around frozen final observations."""
from pathlib import Path
import argparse
import hashlib
import json
import math
import statistics
from round10_payability import load_flat_rows, load_official_scorer, validate_policy_for_replay

ROOT = Path(__file__).resolve().parents[1]


def sha(path):
    return hashlib.sha256(path.read_bytes()).hexdigest()


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--analysis', type=Path, required=True)
    parser.add_argument('--capture', type=Path, required=True)
    parser.add_argument('--output', type=Path, required=True)
    args = parser.parse_args()
    assert not args.output.exists()
    analysis = json.loads(args.analysis.read_bytes())
    competition, context, rows = load_flat_rows(args.capture)
    assert analysis['snapshot']['snapshot_id'] == context['snapshot_id']
    scorer = load_official_scorer()
    policy = competition['policy']
    validation = validate_policy_for_replay(policy, rows, scorer)
    assert policy['pareto_share'] == 1 and policy['improvement_share'] == 0
    bounds = scorer.Boundaries(policy['max_balanced_time_ratio'],
                               policy['max_mean_file_compression_pct'])
    frontier = [scorer.Point(r['id'], r['metrics']['balanced_time_ratio'],
                            r['metrics']['mean_file_compression_pct'])
                for r in rows if (r.get('score') or {}).get('on_frontier')]

    def score(x, y):
        if not (0 < x <= bounds.time_s and 0 < y <= bounds.ratio_pct):
            return 0.0
        if any(p.time_s <= x and p.ratio_pct <= y for p in frontier):
            return 0.0
        points = scorer.pareto_front(frontier + [scorer.Point('__candidate__', x, y)])
        weights = scorer.local_global_improvement_space_log_weights(points, bounds)
        return 100 * weights.get('__candidate__', 0)

    results = []
    for candidate in analysis['candidates']:
        observations = candidate['observations']
        xs = [o['projected_time'] for o in observations]
        x0 = statistics.median(xs)
        y0 = observations[0]['projected_size_pct']
        assert all(o['projected_size_pct'] == y0 for o in observations)
        # A finite one-dimensional search, including both sides of every known
        # frontier discontinuity. This is geometry, not a candidate experiment.
        time_grid = {x0 * (0.5 + i / 10000) for i in range(10001)}
        time_grid.update(p.time_s * (1 + direction * 1e-10)
                         for p in frontier for direction in (-1, 1)
                         if 0.5 * x0 < p.time_s < 1.5 * x0)
        time_grid.update(xs)
        # Resolve the very narrow speed-end window directly between its
        # published neighbors, instead of relying only on a broad grid.
        relevant = sorted({0.95 * x0, 1.05 * x0} |
                          {p.time_s for p in frontier if 0.95 * x0 < p.time_s < 1.05 * x0})
        for left, right in zip(relevant, relevant[1:]):
            time_grid.update(left + (right - left) * i / 1000 for i in range(1001))
        size_grid = {y0 - 0.1 * i / 10000 for i in range(10001)}
        size_grid.update(p.ratio_pct * (1 + direction * 1e-10)
                         for p in frontier for direction in (-1, 1)
                         if y0 - 0.1 < p.ratio_pct < y0)
        time_values = [(x, score(x, y0)) for x in sorted(time_grid)]
        size_values = [(y, score(x0, y)) for y in sorted(size_grid)]
        targets = {}
        for goal in (5, 15):
            passing_time = [(x, value) for x, value in time_values if value >= goal]
            passing_size = [(y, value) for y, value in size_values if value >= goal]
            closest_time = min(passing_time, key=lambda item: abs(math.log(item[0] / x0))) if passing_time else None
            closest_size = min(passing_size, key=lambda item: abs(item[0] - y0)) if passing_size else None
            segments = []
            segment = []
            for x, value in time_values:
                if value >= goal:
                    segment.append((x, value))
                elif segment:
                    segments.append(segment)
                    segment = []
            if segment:
                segments.append(segment)
            targets[str(goal)] = {
                'closest_sample_time': None if closest_time is None else {
                    'time': closest_time[0], 'time_change_pct': 100 * (closest_time[0] / x0 - 1),
                    'share_pct': closest_time[1]},
                'closest_sample_size': None if closest_size is None else {
                    'size_pct': closest_size[0], 'size_delta_pp': closest_size[0] - y0,
                    'share_pct': closest_size[1]},
                'sampled_passing_time_segments': [
                    {'time_range': [segment[0][0], segment[-1][0]],
                     'width_pct_of_reference_time': 100 * (segment[-1][0] - segment[0][0]) / x0,
                     'sample_count': len(segment),
                     'share_range_pct': [min(p[1] for p in segment), max(p[1] for p in segment)]}
                    for segment in segments],
            }
        results.append({
            'candidate': candidate['candidate'], 'rust_sha256': candidate['rust_sha256'],
            'reference_time_median_of_observed_control_variants': x0,
            'reference_size_pct': y0,
            'observed_projected_time_range': [min(xs), max(xs)],
            'observed_time_span_pct_of_reference': 100 * (max(xs) - min(xs)) / x0,
            'observation_control_variants': len(xs),
            'observed_runner_count': len({o['run_id'] for o in observations}),
            'observed_block_count': len({(o['run_id'], o['block']) for o in observations}),
            'reference_time_is_a_descriptive_center_not_expected_score': True,
            'time_grid_range': [min(time_grid), max(time_grid)],
            'size_grid_range': [min(size_grid), max(size_grid)],
            'targets': targets,
            'time_samples': time_values,
            'size_samples': size_values,
        })
    result = {
        'status': 'INFERRED_BOUNDED_COORDINATE_REQUIREMENTS_NOT_MEASURED_IMPROVEMENTS',
        'snapshot': context, 'policy_validation': validation,
        'analysis_sha256': sha(args.analysis),
        'capture_receipt_sha256': sha(args.capture / 'receipt.json'),
        'candidates': results,
        'limits': [
            'Each axis is varied separately. Time and quality changes have no demonstrated implementation.',
            'Finite samples are not an exhaustive feasibility theorem or formal success probability.',
            'Primary/shadow views are not independent runs. Actual block and runner counts are reported per candidate.',
            'Observed time span is reported directly; no arbitrary pressure margin or private-corpus bound is substituted.',
            'Discontinuities are sampled on both sides. A faster candidate can receive less share when it removes a neighbor.',
            'No source/proof changes, new measurements, formal submission or ownership check are performed.',
        ],
    }
    args.output.write_bytes((json.dumps(result, indent=2) + '\n').encode())
    print(json.dumps([{k: v for k, v in row.items() if k not in ('time_samples', 'size_samples')}
                      for row in results], indent=2))


if __name__ == '__main__':
    main()
