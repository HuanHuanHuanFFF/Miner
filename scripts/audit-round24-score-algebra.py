"""Independently expand the captured scoring algebra and check every final main/joint point."""
from pathlib import Path
from datetime import datetime, timezone
import argparse, csv, hashlib, json, math
from round10_payability import load_flat_rows

ROOT = Path(__file__).resolve().parents[1]


def expanded(points):
    ordered = sorted(points, key=lambda r: (r[1], r[2]))
    frontier, best = [], math.inf
    for row in ordered:
        if row[2] < best:
            frontier.append(row)
            best = row[2]
    assert len(frontier) > 1
    dt = [math.log1p(max(0, frontier[min(i + 1, len(frontier) - 1)][1] - p[1]) / p[1]) for i, p in enumerate(frontier)]
    dq = [math.log1p(max(0, frontier[max(i - 1, 0)][2] - p[2]) / p[2]) for i, p in enumerate(frontier)]
    total_t, total_q = sum(dt), sum(dq)
    assert total_t > 0 and total_q > 0

    def corner(left, right, middle):
        nt = (middle[1] - left[1]) / (right[1] - left[1]) if right[1] > left[1] else 0.0
        nq = (middle[2] - right[2]) / (left[2] - right[2]) if left[2] > right[2] else 0.0
        # At documented coefficients max2/min0, both branches simplify to2-nt-nq.
        return 2 - nt - nq

    terms = []
    for i, p in enumerate(frontier):
        local = 1.0 if i in [0, len(frontier) - 1] else corner(frontier[i-1], frontier[i+1], p)
        glob = corner(frontier[0], frontier[-1], p)
        improvement = 0.5 * (dt[i] / total_t + dq[i] / total_q)
        terms.append({'name': p[0], 'local': local, 'global': glob, 'incremental_time_budget_fraction': dt[i] / total_t, 'incremental_quality_budget_fraction': dq[i] / total_q, 'improvement_factor': improvement, 'unnormalized_product': local * glob * improvement, 'predecessor': frontier[i-1][0] if i else None, 'successor': frontier[i+1][0] if i+1 < len(frontier) else None})
    denominator = sum(r['unnormalized_product'] for r in terms)
    for r in terms:
        r['normalization_denominator'] = denominator
        r['share_pct'] = 100 * r['unnormalized_product'] / denominator
    return {r['name']: r for r in terms}


def main():
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument('--capture', required=True, type=Path)
    ap.add_argument('--confirmation', required=True, type=Path)
    ap.add_argument('--output', required=True, type=Path)
    a = ap.parse_args()
    assert not a.output.exists()
    comp, ctx, rows = load_flat_rows(a.capture)
    assert comp['policy']['method'] == 'local-global-improvement-space-log' and comp['policy']['pareto_share'] == 1 and comp['policy']['improvement_share'] == 0
    formal = [r for r in rows if (r.get('score') or {}).get('on_frontier')]
    base = [(str(r['id']), r['metrics']['balanced_time_ratio'], r['metrics']['mean_file_compression_pct']) for r in formal]
    before = expanded(base)
    baseline_error = max(abs(before[str(r['id'])]['share_pct'] - 100 * r['score']['pareto_weight']) for r in formal)
    assert baseline_error < 1e-10
    with (a.confirmation / 'main-blocks.csv').open(encoding='utf-8-sig', newline='') as f:
        mains = list(csv.DictReader(f))
    with (a.confirmation / 'joint-blocks.csv').open(encoding='utf-8-sig', newline='') as f:
        joints = list(csv.DictReader(f))
    indexed = {(r['run_id'], r['block'], r['anchor'], r['label']): r for r in mains}

    def insert(rs):
        eligible = []
        for r in rs:
            x, y = float(r['projected_time']), float(r['projected_size_pct'])
            if 0 < x <= comp['policy']['max_balanced_time_ratio'] and 0 < y <= comp['policy']['max_mean_file_compression_pct'] and not any(t <= x and q <= y for _, t, q in base):
                eligible.append((r['candidate'], x, y))
        return expanded(base + eligible)

    single_errors, joint_errors, effects = [], [], []
    for r in mains:
        w = insert([r])
        single_errors.append(abs(w.get(r['candidate'], {}).get('share_pct', 0) - float(r['single_pool_share_pct'])))
    for r in joints:
        aa, bb = [indexed[r['run_id'], r['block'], r['anchor'], label] for label in ['A', 'B']]
        w = insert([aa, bb])
        for label, row in [('A', aa), ('B', bb)]:
            share = w.get(row['candidate'], {}).get('share_pct', 0)
            joint_errors.append(abs(share - float(r[label + '_joint_pct'])))
        single_b = insert([bb])
        b = bb['candidate']
        effects.append({'run_id': r['run_id'], 'block': r['block'], 'anchor': r['anchor'], 'B_single': single_b.get(b), 'B_joint': w.get(b), 'B_change_pp': w.get(b, {}).get('share_pct', 0) - single_b.get(b, {}).get('share_pct', 0)})
    assert len(mains) == 54 and len(joints) == 27 and max(single_errors + joint_errors) < 1e-10
    result = {'status': 'VERIFIED_INDEPENDENT_EXPANDED_SCORING_ALGEBRA', 'checked_utc': datetime.now(timezone.utc).isoformat(), 'snapshot': ctx, 'baseline_frontier_points': len(base), 'main_conditional_points': len(mains), 'joint_cases': len(joints), 'max_baseline_api_error_pp': baseline_error, 'max_single_error_pp': max(single_errors), 'max_joint_error_pp': max(joint_errors), 'joint_B_increase_cases': sum(r['B_change_pp'] > 1e-10 for r in effects), 'joint_B_decrease_cases': sum(r['B_change_pp'] < -1e-10 for r in effects), 'B_single_vs_joint_algebra': effects, 'inputs': {str(p): hashlib.sha256(p.read_bytes()).hexdigest() for p in [a.confirmation / 'main-blocks.csv', a.confirmation / 'joint-blocks.csv']}, 'method': 'Independent Pareto sweep; corner=2-nt-nq; local*global*equallyweighted incremental log-axis budget; normalize product once. The intermediate local-global normalization cancels algebraically. No officialscorer implementation imported.', 'limits': ['This confirms captured scoring arithmetic and role-aligned joint selection only; calibration, admission, eligibility and private performance remainconditional.', '54singleviews and27jointviews reuse9mainblocks per candidate, not81independentmeasurements.', 'Rivals can increase or decrease a point share through local coefficient and common normalization changes; independent shares cannotbeadded.']}
    a.output.write_bytes((json.dumps(result, indent=2) + '\n').encode())
    print(json.dumps({k: result[k] for k in ['status', 'baseline_frontier_points', 'main_conditional_points', 'joint_cases', 'max_baseline_api_error_pp', 'max_single_error_pp', 'max_joint_error_pp', 'joint_B_increase_cases', 'joint_B_decrease_cases']}, indent=2))


if __name__ == '__main__':
    main()
