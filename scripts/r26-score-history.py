"""Reaudit historical raw original timings and replay them on R26 snapshot 29785.

Roles are retained. Repeated analyses/calibrations/control aliases add no samples.
"""
from pathlib import Path
from datetime import datetime, timezone
from collections import defaultdict
import contextlib
import importlib
import json
import statistics
import sys

M = importlib.import_module('r26-score-map')
ROOT = M.ROOT
OUT = ROOT / 'evidence/round26/score-verification'


def distribution(observations):
    values = [o['new_share_pct'] for o in observations]
    return {'views': len(values), 'runner_count': len({o['run_id'] for o in observations}),
            'minimum_pct': min(values), 'median_pct': statistics.median(values),
            'maximum_pct': max(values), 'zero_count': sum(v == 0 for v in values),
            'at_least_5_count': sum(v >= 5 for v in values),
            'at_least_10_count': sum(v >= 10 for v in values)}


def main():
    replay = M.Replay(ROOT / 'evidence/round26/official-start-live', ROOT / 'evidence/round26/official-rules-start-live')
    import round10_payability
    round10_payability.SCORER_PATH = ROOT / 'evidence/round26/official-rules-start-live/validator--scoring--pareto.py'
    analyzer = importlib.import_module('analyze-round18')
    sources = [('r25', ROOT / 'evidence/round25/analysis-all-29702.json'),
               ('r24-confirmation', ROOT / 'evidence/round24/analysis-confirmation-29652.json'),
               ('parent-context', ROOT / 'evidence/round25/parent-context-29702.json')]
    summaries, all_measurements, all_raw = [], {}, {}
    for name, path in sources:
        registry = json.loads(path.read_bytes())
        folders = []
        for run in registry['runs']:
            matches = list((ROOT / 'evidence').glob('round*/' + run['run_id'] + '/' + run['batch'] + '/gate/state.json'))
            assert len(matches) == 1, (name, run['run_id'], matches)
            folders.append(matches[0].parent)
        result_path = OUT / ('historical-' + name + '-raw-replay-29785.json')
        argv = sys.argv[:]
        sys.argv = ['analyze-round18', *map(str, folders), '--capture', str(replay.capture), '--output', str(result_path)]
        try:
            with (OUT / ('historical-' + name + '-raw-replay-29785.log')).open('w', encoding='utf-8') as handle:
                with contextlib.redirect_stdout(handle):
                    analyzer.main()
        finally:
            sys.argv = argv
        current = json.loads(result_path.read_bytes())
        assert current['snapshot'] == replay.context
        observed, errors = [], []
        for candidate in current['candidates']:
            for o in candidate['observations']:
                key = (candidate['rust_sha256'], o['run_id'], o['block'], o['entry_name'], o['calibration'])
                assert key not in all_measurements or all_measurements[key] == (o['projected_time'], o['projected_size_pct'])
                all_measurements[key] = (o['projected_time'], o['projected_size_pct'])
                value = replay.score([(candidate['candidate'], o['projected_time'], o['projected_size_pct'])]).get(candidate['candidate'], {}).get('share_pct', 0)
                errors.append(abs(value - o['single_pool_share_pct']))
                observed.append({'candidate': candidate['candidate'], 'rust_sha256': candidate['rust_sha256'],
                                 **{k: o[k] for k in ('run_id', 'block', 'role', 'entry_role', 'entry_name',
                                                    'calibration', 'projected_time', 'projected_size_pct')},
                                 'new_share_pct': value})
        for rawpath, evidence in current['raw_input_audit'].items():
            assert rawpath not in all_raw or all_raw[rawpath] == evidence
            all_raw[rawpath] = evidence
        grouped = defaultdict(list)
        for o in observed:
            grouped[o['candidate'], o['role'], o['entry_role'], o['calibration']].append(o)
        group_summaries = [{'candidate': key[0], 'role': key[1], 'entry_role': key[2],
                            'calibration': key[3], **distribution(rows)} for key, rows in grouped.items()]
        # Validate every role-aligned joint case independently as well.
        indexed = {(o['candidate'], o['run_id'], o['block'], o['calibration'], o['entry_name']): o for o in observed}
        joint_errors = []
        for pair in current['joint']:
            for row in pair['matched_observations']:
                points = []
                for candidate, entry in row['selected_entries'].items():
                    o = indexed[candidate, row['run_id'], row['block'], row['calibration'], entry['name']]
                    assert o['entry_role'] == entry['role']
                    points.append((candidate, o['projected_time'], o['projected_size_pct']))
                score = replay.score(points)
                for candidate in pair['candidates']:
                    joint_errors.append(abs(score.get(candidate, {}).get('share_pct', 0) - row['simultaneous_geometric_pct'][candidate]))
        assert max(errors + joint_errors) < 1e-10
        summary = {'era': name, 'source_registry': str(path.relative_to(ROOT)),
                   'source_registry_sha256': M.digest(path), 'raw_replay_file': result_path.relative_to(ROOT).as_posix(),
                   'run_ids': [r['run_id'] for r in current['runs']],
                   'raw_paired_processes_in_this_view': current['paired_processes'],
                   'coordinate_views': len(observed), 'joint_cases': len(joint_errors) // 2,
                   'max_single_independent_error_pp': max(errors),
                   'max_joint_independent_error_pp': max(joint_errors),
                   'role_summaries': group_summaries, 'observations': observed}
        summaries.append(summary)
        print(json.dumps({'era': name, 'views': len(observed), 'groups': group_summaries}), flush=True)
    unique_physical = {(sha, run, block, entry) for sha, run, block, entry, cal in all_measurements}
    result = {'status': 'VERIFIED_HISTORICAL_RAW_REAUDIT_AND_INDEPENDENT_CURRENT_SCORING_REPLAY',
              'checked_utc': datetime.now(timezone.utc).isoformat(), 'snapshot': replay.context,
              'historical_sets': summaries, 'deduplicated_coordinate_views': len(all_measurements),
              'deduplicated_observed_candidate_or_control_measurements': len(unique_physical),
              'deduplicated_raw_paired_process_files': len(all_raw),
              'raw_file_audit_sha256': M.digest(OUT / 'historical-r25-raw-replay-29785.json'),
              'limits': ['All timing is historical; this creates no new independent runner measurement.',
                         'R25 parent-context repeats the same R25 jobs; counts are deduplicated globally and era reports must not be added.',
                         'Calibration views and same-source control aliases do not increase independent candidate sample count.',
                         'R24/R23 frozen confirmations were independent at their original freeze; reuse to choose R26 variants is historical selection evidence.',
                         'Formal coordinate transfer, future admission/registration/cap/payment remain conditional.']}
    M.dump(OUT / 'historical-replay-summary-29785.json', result)


if __name__ == '__main__':
    main()
