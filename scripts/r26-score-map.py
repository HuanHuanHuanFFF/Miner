"""Independent captured-frontier replay and hypothetical R26 coordinate planning.

No measurements, API requests, CI, submission, or wallet operations are performed.
All coordinate maps are conditional on admission and independent eligible hotkeys.
"""
from pathlib import Path
from datetime import datetime, timezone
import argparse
import csv
import hashlib
import importlib
import json
import math
from collections import Counter, defaultdict

ROOT = Path(__file__).resolve().parents[1]
expanded = importlib.import_module('audit-round24-score-algebra').expanded


def digest(path):
    return hashlib.sha256(path.read_bytes()).hexdigest()


def dump(path, value):
    path.write_text(json.dumps(value, ensure_ascii=False, indent=2) + '\n', encoding='utf-8')


def front(points):
    ordered, result, best = sorted(points, key=lambda p: (p[1], p[2])), [], math.inf
    for point in ordered:
        if point[2] < best:
            result.append(point)
            best = point[2]
    return result


class Replay:
    def __init__(self, capture, rules):
        self.capture, self.rules = capture, rules
        self.receipt = json.loads((capture / 'receipt.json').read_bytes())
        self.competition = json.loads((capture / 'competition.json').read_bytes())
        self.pages = json.loads((capture / 'pareto-pages.json').read_bytes())
        self.rows = [r for p in self.pages for r in p['items']]
        self.context = self.competition['context']
        self.policy = self.competition['policy']
        self.byid = {str(r['id']): r for r in self.rows}
        assert len(self.byid) == len(self.rows)
        assert all(p['context'] == self.context for p in self.pages)
        assert self.policy['method'] == 'local-global-improvement-space-log'
        assert self.policy['pareto_share'] == 1 and self.policy['improvement_share'] == 0
        self.valid = [r for r in self.rows if (r.get('admission') or {}).get('admitted') is True
                      and (r.get('bounds') or {}).get('eligible') is True]
        self.all_points = [(str(r['id']), r['metrics']['balanced_time_ratio'],
                            r['metrics']['mean_file_compression_pct']) for r in self.valid]
        self.base = front(self.all_points)
        self.initial = expanded(self.all_points)
        self.official_ids = {str(r['id']) for r in self.rows if (r.get('score') or {}).get('on_frontier')}
        assert {p[0] for p in self.base} == self.official_ids

    def score(self, additions):
        accepted = [p for p in additions if 0 < p[1] <= self.policy['max_balanced_time_ratio']
                    and 0 < p[2] <= self.policy['max_mean_file_compression_pct']
                    and not any(t <= p[1] and q <= p[2] for _, t, q in self.base)]
        return expanded(self.base + accepted)

    def describe(self, additions):
        terms = self.score(additions)
        answer = {'points': {}, 'conditional_total_pct': 0}
        for name, x, y in additions:
            term = terms.get(name)
            row = {'x': x, 'y_pct': y, 'share_pct': term['share_pct'] if term else 0,
                   'on_frontier': term is not None, 'terms': term,
                   'dominator_ids': [n for n, t, q in self.base if t <= x and q <= y],
                   'removed_existing_ids': [n for n, t, q in self.base if x <= t and y <= q]}
            answer['points'][name] = row
            answer['conditional_total_pct'] += row['share_pct']
        return answer


def audit(replay):
    capture, rules = replay.capture, replay.rules
    hashes = []
    for item in replay.receipt['raw_response_files']:
        path = capture / item['file']
        observed = digest(path)
        assert observed == item['sha256'] and path.stat().st_size == item['bytes']
        hashes.append({'file': item['file'], 'sha256': observed, 'bytes': path.stat().st_size})
    for file, item in replay.receipt['derived_files'].items():
        assert digest(capture / file) == item['sha256']
    rr = json.loads((rules / 'receipt.json').read_bytes())
    for item in rr['files']:
        assert digest(rules / item['file']) == item['sha256']
    # Independent expanded algebra has no dependency on the captured pure scorer.
    errors = {str(r['id']): abs(replay.initial.get(str(r['id']), {}).get('share_pct', 0)
                                  - 100 * (r.get('score') or {}).get('pareto_weight', 0))
              for r in replay.rows}
    assert max(errors.values()) < 1e-10
    from round3 import load_scorer
    scorer = load_scorer(rules / 'validator--scoring--pareto.py')
    official = scorer.local_global_improvement_space_log_weights(
        scorer.pareto_front([scorer.Point(*p) for p in replay.all_points]),
        scorer.Boundaries(replay.policy['max_balanced_time_ratio'], replay.policy['max_mean_file_compression_pct']))
    official_error = max(abs(100 * official.get(n, 0) - replay.initial.get(n, {}).get('share_pct', 0))
                         for n in replay.byid)
    assert official_error < 1e-10
    # Reproduce payout disposition from API evidence. Geometry is normalized once;
    # zeroed/ineligible allocations are burned and never reallocated.
    oldest = {}
    for row in sorted(replay.rows, key=lambda r: (r['submitted_at'], int(r['id']))):
        if str(row['id']) in replay.official_ids and row.get('hotkey') is not None:
            oldest.setdefault(row['hotkey'], str(row['id']))
    payable_by_key = defaultdict(float)
    payment_errors, disposition = [], []
    for row in replay.rows:
        score = row.get('score') or {}
        geometric = replay.initial.get(str(row['id']), {}).get('share_pct', 0) / 100
        eligible = bool(score.get('payment_eligible'))
        if geometric and eligible:
            assert row['kind'] == 'miner' and oldest[row['hotkey']] == str(row['id'])
            assert score.get('unpaid_reason') is None and not score.get('bounty_capped')
        predicted = geometric if eligible else 0
        payment_errors.append(abs(predicted - score.get('payable_weight', 0)))
        if predicted:
            payable_by_key[row['hotkey']] += predicted
        disposition.append({'id': row['id'], 'geometric_pct': 100 * geometric,
                            'payment_eligible': eligible, 'unpaid_reason': score.get('unpaid_reason'),
                            'recomputed_payable_pct': 100 * predicted})
    weights = json.loads((capture / 'weights-current.json').read_bytes())
    assert weights['context'] == replay.context
    keys = set(payable_by_key) | set(weights['weights'])
    key_error = max(abs(payable_by_key.get(k, 0) - weights['weights'].get(k, 0)) for k in keys)
    assert max(payment_errors) < 1e-12 and key_error < 1e-12
    result = {'status': 'VERIFIED_INDEPENDENT_ENTIRE_FRONTIER_AND_API_PAYOUT_REPLAY',
              'checked_utc': datetime.now(timezone.utc).isoformat(), 'context': replay.context,
              'input_rows': len(replay.rows), 'admitted_bounded_rows': len(replay.valid),
              'reconstructed_frontier': len(replay.base), 'frontier_ids_match': True,
              'raw_and_derived_hashes_match': True, 'raw_files': hashes,
              'max_independent_api_error_pp': max(errors.values()),
              'max_independent_official_scorer_error_pp': official_error,
              'max_api_payable_error_fraction': max(payment_errors),
              'max_weights_by_hotkey_error_fraction': key_error,
              'sum_geometric_fraction': sum(v['share_pct'] for v in replay.initial.values()) / 100,
              'sum_payable_fraction': sum(payable_by_key.values()),
              'api_payable_competition_weight': weights['payable_competition_weight'],
              'api_unpaid_competition_weight': weights['unpaid_competition_weight'],
              'api_chain_accepted': weights['chain_accepted'],
              'frontier': [{'id': n, 'x': t, 'y_pct': q, **replay.initial[n]} for n, t, q in replay.base],
              'payment_disposition': disposition,
              'source_hashes': {'algebra': digest(ROOT / 'scripts/audit-round24-score-algebra.py'),
                                'pareto': digest(rules / 'validator--scoring--pareto.py'),
                                'combine': digest(rules / 'validator--scoring--combine.py')},
              'limits': ['API payout eligibility is observed; registration and cap decisions are not independently recomputed from chain.',
                         'Captured public scorer replay matches this recorded pass; exact live deployment bytes and finalized payment are UNKNOWN.',
                         'Freshness remains API unknown. This audit performs no current refresh.']}
    return result


def scan(replay, name, anchor_id, ys, lo, hi, step, output):
    anchor = replay.byid[anchor_id]['metrics']
    records, summaries = [], []
    for y in ys:
        line = []
        for i in range(round((hi - lo) / step) + 1):
            x = lo + i * step
            terms = replay.score([(name, x, y)])
            term = terms.get(name, {})
            row = {'route': name, 'x': x, 'y_pct': y, 'share_pct': term.get('share_pct', 0),
                   'predecessor': term.get('predecessor'), 'successor': term.get('successor'),
                   'on_frontier': bool(term), 'time_change_from_anchor_pct': 100 * (x / anchor['balanced_time_ratio'] - 1),
                   'quality_change_from_anchor_pp': y - anchor['mean_file_compression_pct']}
            line.append(row)
            records.append(row)
        targets = {}
        for target in [5, 10]:
            segments, current = [], []
            for row in line:
                if row['share_pct'] >= target:
                    current.append(row)
                elif current:
                    segments.append(current)
                    current = []
            if current:
                segments.append(current)
            targets[str(target)] = [{'sampled_x_low': seg[0]['x'], 'sampled_x_high': seg[-1]['x'],
                                    'sampled_width_x': seg[-1]['x'] - seg[0]['x'],
                                    'width_relative_to_anchor_pct': 100 * (seg[-1]['x'] - seg[0]['x']) / anchor['balanced_time_ratio'],
                                    'min_sample_share_pct': min(p['share_pct'] for p in seg),
                                    'max_sample_share_pct': max(p['share_pct'] for p in seg),
                                    'neighbor_regimes': [list(k) for k in dict.fromkeys((p['predecessor'], p['successor']) for p in seg)]}
                                   for seg in segments]
        reversals = []
        for faster, slower in zip(line, line[1:]):
            if faster['share_pct'] + 1e-7 < slower['share_pct']:
                reversals.append({'faster_x': faster['x'], 'slower_x': slower['x'],
                                  'faster_share_pct': faster['share_pct'], 'slower_share_pct': slower['share_pct'],
                                  'faster_neighbors': [faster['predecessor'], faster['successor']],
                                  'slower_neighbors': [slower['predecessor'], slower['successor']]})
        # Preserve topological one-sided boundaries at machine-adjacent coordinates.
        transitions = []
        for n, t, q in replay.base:
            if lo <= t <= hi:
                at = []
                for side, x in [('left', math.nextafter(t, 0)), ('equal', t), ('right', math.nextafter(t, math.inf))]:
                    terms = replay.score([(name, x, y)]).get(name, {})
                    at.append({'side': side, 'x': x, 'share_pct': terms.get('share_pct', 0),
                               'predecessor': terms.get('predecessor'), 'successor': terms.get('successor')})
                if max(p['share_pct'] for p in at) - min(p['share_pct'] for p in at) > 1e-6:
                    transitions.append({'official_id': n, 'official_x': t, 'official_y_pct': q,
                                        'candidate_y_pct': y, 'one_sided': at})
        summaries.append({'y_pct': y, 'quality_change_from_anchor_pp': y - anchor['mean_file_compression_pct'],
                          'target_segments': targets, 'peak_sample': max(line, key=lambda p: p['share_pct']),
                          'nonmonotone_adjacent_pairs_count': len(reversals),
                          'largest_nonmonotone_pair': max(reversals, key=lambda p: p['slower_share_pct'] - p['faster_share_pct']) if reversals else None,
                          'discontinuous_topology_boundaries': transitions})
    with output.open('w', encoding='utf-8', newline='') as handle:
        writer = csv.DictWriter(handle, fieldnames=list(records[0]))
        writer.writeheader()
        writer.writerows(records)
    return {'route': name, 'anchor_id': anchor_id, 'anchor_x': anchor['balanced_time_ratio'],
            'anchor_y_pct': anchor['mean_file_compression_pct'], 'x_domain': [lo, hi], 'x_step': step,
            'coordinate_views': len(records), 'quality_slices': summaries,
            'scope': 'Hypothetical grid, not measured variants, probability, stability evidence, or continuous guarantees.'}


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--capture', type=Path, default=ROOT / 'evidence/round26/official-start-live')
    parser.add_argument('--rules', type=Path, default=ROOT / 'evidence/round26/official-rules-start-live')
    parser.add_argument('--output', type=Path, default=ROOT / 'evidence/round26/score-verification')
    args = parser.parse_args()
    args.output.mkdir(parents=True, exist_ok=True)
    replay = Replay(args.capture, args.rules)
    audit_result = audit(replay)
    dump(args.output / 'frontier-api-audit-29785.json', audit_result)
    print(json.dumps({k: audit_result[k] for k in ['status', 'input_rows', 'admitted_bounded_rows', 'reconstructed_frontier', 'max_independent_api_error_pp', 'max_weights_by_hotkey_error_fraction']}), flush=True)
    routes = [scan(replay, 'fast', '595', [36.57814279549815, 36.52, 36.45, 36.35, 36.2, 36.0, 35.75, 35.5],
                   .39, .49, .00005, args.output / 'fast-grid-29785.csv'),
              scan(replay, 'compression', '628', [34.091422617511455, 34.09118, 34.09, 34.0874, 34.085, 34.08, 34.06],
                   2, 7, .005, args.output / 'compression-grid-29785.csv'),
              scan(replay, 'middle', '361', [34.19, 34.18, 34.17, 34.16, 34.14, 34.12, 34.1],
                   .8, 2.3, .002, args.output / 'middle-grid-29785.csv')]
    result = {'status': 'VERIFIED_HYPOTHETICAL_COORDINATE_MAP_NOT_MEASUREMENT',
              'checked_utc': datetime.now(timezone.utc).isoformat(), 'snapshot': replay.context,
              'routes': routes,
              'normalization': 'Entire admitted bounded geometric frontier is scored and normalized once. Payment exclusions burn allocated weight without renormalizing.',
              'limits': ['Each y slice and x grid is hypothetical. Intervals are sampled extents, not certified continuous bounds.',
                         'Observed runner and same-source deviations must be replayed from measurements; these grids impose no noise model.',
                         'Prospective shares assume admitted, uncapped, registered independent hotkeys; two candidates sharing one hotkey cannot both receive Pareto allocations.',
                         'Coordinates must be transferred using their actual matched original-protocol anchors; direct public coordinates are not formal coordinates.']}
    dump(args.output / 'coordinate-map-29785.json', result)
    print(json.dumps({'status': result['status'], 'routes': [{k: r[k] for k in ['route', 'coordinate_views']} for r in routes]}), flush=True)


if __name__ == '__main__':
    main()
