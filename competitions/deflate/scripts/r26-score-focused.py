"""Small R26 joint scenarios and fixed-time quality slices; all hypothetical."""
from pathlib import Path
from datetime import datetime, timezone
import csv
import importlib
import json
import math

M = importlib.import_module('r26-score-map')
ROOT = M.ROOT
OUT = ROOT / 'evidence/round26/score-verification'


def main():
    replay = M.Replay(ROOT / 'evidence/round26/official-start-live', ROOT / 'evidence/round26/official-rules-start-live')
    fast_points = [(.429, 36.35), (.429, 36.2), (.429, 36.0), (.432, 36.2),
                   (.432, 36.0), (.436, 36.0), (.444, 35.75)]
    compression_points = [(4.5, 34.091422617511455), (4, 34.091422617511455),
                          (3.5, 34.091422617511455), (3, 34.091422617511455),
                          (5.5, 34.09), (5.85, 34.089), (5, 34.089), (4.5, 34.09)]
    joints = []
    for ax, ay in fast_points:
        for bx, by in compression_points:
            case = replay.describe([('A', ax, ay), ('B', bx, by)])
            single_a = replay.describe([('A', ax, ay)])['points']['A']['share_pct']
            single_b = replay.describe([('B', bx, by)])['points']['B']['share_pct']
            shares = {n: p['share_pct'] for n, p in case['points'].items()}
            joints.append({'A_x': ax, 'A_y_pct': ay, 'B_x': bx, 'B_y_pct': by,
                           'A_single_pct': single_a, 'B_single_pct': single_b,
                           'A_joint_pct': shares['A'], 'B_joint_pct': shares['B'],
                           'joint_total_pct': sum(shares.values()),
                           'A5_B10_joint': shares['A'] >= 5 and shares['B'] >= 10,
                           'A10_B5_joint': shares['A'] >= 10 and shares['B'] >= 5,
                           'A_joint_change_pp': shares['A'] - single_a,
                           'B_joint_change_pp': shares['B'] - single_b,
                           'full_terms': case})
    columns = [k for k in joints[0] if k != 'full_terms']
    with (OUT / 'joint-scenarios-29785.csv').open('w', encoding='utf-8', newline='') as handle:
        writer = csv.DictWriter(handle, fieldnames=columns)
        writer.writeheader()
        writer.writerows({k: row[k] for k in columns} for row in joints)
    fixed = []
    for name, anchor_id, lo, hi, step in [('fast', '595', 35.5, 36.6, .0005),
                                         ('compression', '628', 34.08, 34.093, .000002),
                                         ('middle', '361', 34.1, 34.22, .0001)]:
        x = replay.byid[anchor_id]['metrics']['balanced_time_ratio']
        anchor_y = replay.byid[anchor_id]['metrics']['mean_file_compression_pct']
        line = []
        for i in range(round((hi - lo) / step) + 1):
            y = lo + i * step
            term = replay.score([(name, x, y)]).get(name, {})
            line.append({'y_pct': y, 'share_pct': term.get('share_pct', 0),
                         'predecessor': term.get('predecessor'), 'successor': term.get('successor')})
        segments = {}
        for target in [5, 10]:
            runs, current = [], []
            for row in line:
                if row['share_pct'] >= target:
                    current.append(row)
                elif current:
                    runs.append(current)
                    current = []
            if current:
                runs.append(current)
            segments[str(target)] = [{'sampled_y_low': r[0]['y_pct'], 'sampled_y_high': r[-1]['y_pct'],
                                     'width_quality_pp': r[-1]['y_pct'] - r[0]['y_pct'],
                                     'least_sample_quality_reduction_pp': anchor_y - r[-1]['y_pct'],
                                     'min_sample_share_pct': min(s['share_pct'] for s in r),
                                     'max_sample_share_pct': max(s['share_pct'] for s in r)} for r in runs]
        boundaries = []
        for n, t, q in replay.base:
            if lo <= q <= hi:
                values = []
                for side, y in [('better', math.nextafter(q, 0)), ('equal', q), ('worse', math.nextafter(q, math.inf))]:
                    term = replay.score([(name, x, y)]).get(name, {})
                    values.append({'side': side, 'y_pct': y, 'share_pct': term.get('share_pct', 0),
                                   'predecessor': term.get('predecessor'), 'successor': term.get('successor')})
                if max(v['share_pct'] for v in values) - min(v['share_pct'] for v in values) > 1e-6:
                    boundaries.append({'official_id': n, 'x': t, 'y_pct': q, 'one_sided': values})
        fixed.append({'route': name, 'anchor_id': anchor_id, 'fixed_x': x, 'anchor_y_pct': anchor_y,
                      'y_domain': [lo, hi], 'y_step': step, 'target_segments': segments,
                      'peak_sample': max(line, key=lambda p: p['share_pct']), 'quality_topology_boundaries': boundaries})
    result = {'status': 'VERIFIED_HYPOTHETICAL_JOINT_AND_QUALITY_MAP_NOT_MEASUREMENT',
              'checked_utc': datetime.now(timezone.utc).isoformat(), 'snapshot': replay.context,
              'fixed_time_quality_maps': fixed, 'joint_scenarios': joints,
              'hypothetical_identity_cases': {
                  'distinct_eligible_hotkeys': 'The joint geometric values are payable conditionally on new admission, registration, no bounty cap, and no older surviving frontier entry on each hotkey.',
                  'same_fresh_hotkey_A_then_B': 'When both survive only A Pareto allocation is payable; B allocation burns. Geometry is still normalized including B.',
                  'same_fresh_hotkey_B_then_A': 'When both survive only B Pareto allocation is payable; A allocation burns. Geometry is still normalized including A.'},
              'limits': ['These coordinates are explanatory hypotheses, not measurements, candidate implementations, pressure tests, or stable payout guarantees.',
                         'All grid intervals are sampled extents. Topology jump sides are computed at adjacent representable floats.',
                         'Different candidate regions can still increase or decrease each other through global/local terms and common normalization.']}
    M.dump(OUT / 'focused-map-29785.json', result)
    print(json.dumps({'quality_maps': [{k: r[k] for k in ['route', 'fixed_x', 'target_segments', 'peak_sample']} for r in fixed],
                      'joint_cases': len(joints), 'A5_B10_count': sum(r['A5_B10_joint'] for r in joints),
                      'A10_B5_count': sum(r['A10_B5_joint'] for r in joints)}, indent=2))


if __name__ == '__main__':
    main()
