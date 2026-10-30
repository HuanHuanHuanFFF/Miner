"""Summarize complete R28 evidence without changing original bytes or scorer."""
from pathlib import Path
import datetime
import hashlib
import json

ROUND = Path(__file__).resolve().parent.parent
ROOT = next(p for p in ROUND.parents if (p / 'AGENTS.md').is_file())
RUNS = [41099255272, 41103226283, 41107618451, 41113231015, 41117223550, 41119180001]


def j(path):
    return json.loads(path.read_bytes())


def main():
    rows = []
    proofs = {}
    pairs = 0
    for run in RUNS:
        folder = ROUND / 'evidence' / str(run)
        manifest = j(folder / 'original-artifact-hashes.json')
        artifact = folder / manifest['directory']
        summary = j(artifact / 'summary.json')
        audit_path = folder / 'root-fixed-audit.json'
        audit = j(audit_path)
        assert audit['outer_hashes']['status'] == audit['inner_hashes']['status'] == 'PASS'
        results = []
        for result in audit['results']:
            count = sum(x['paired_rows'] for x in result.get('counts', []))
            pairs += count
            score = result.get('score_vs_calibration_internal', {})
            results.append({
                'candidate': result['candidate'],
                'sha256': result.get('candidate_sha256', 'UNKNOWN'),
                'paired_rows': count,
                'time_over_current_champion_estimate': result.get('candidate_time_over_current_champion_estimate', 'UNKNOWN'),
                'proof': result.get('candidate_proof', 'UNKNOWN'),
                'guard_passed': score.get('guard_passed', 'UNKNOWN'),
                'outcome': score.get('outcome', 'UNKNOWN'),
                'status': result['status'],
            })
        for gate in summary.get('full_gates', []):
            if gate['exit_code'] == 0 and gate['verdict']['passed'] and gate['verdict']['stage'] == 'axioms':
                proofs[gate['source_sha256']] = {'run': run, 'name': gate['name'], 'seconds': gate['verdict']['seconds']}
        rows.append({
            'run': run, 'source_commit': summary['source_commit'],
            'started_at_utc': summary['started_at_utc'], 'finished_at_utc': summary['finished_at_utc'],
            'elapsed_seconds': summary['elapsed_seconds'], 'complete': summary['complete'],
            'error': summary.get('error'), 'platform_status': audit['ci_metadata_status'],
            'platform_conclusion': audit['ci_conclusion'],
            'audit_path': audit_path.relative_to(ROOT).as_posix(),
            'audit_sha256': hashlib.sha256(audit_path.read_bytes()).hexdigest(),
            'results': results,
        })
    binding = j(ROUND / 'evidence/41119180001/exact-source-proof-confirmation-binding.json')
    result = {
        'at_utc': datetime.datetime.now(datetime.timezone.utc).isoformat(),
        'round': 'R28', 'research_start_utc': '2026-10-30T17:15:58Z',
        'research_cutoff_utc': '2026-10-30T20:15:58Z', 'research_budget_seconds': 10800,
        'research_window_complete': datetime.datetime.now(datetime.timezone.utc) >= datetime.datetime(2026, 10, 30, 20, 15, 58, tzinfo=datetime.timezone.utc),
        'goal': 'Any current TorchLean board champion', 'goal_achieved': False,
        'new_exact_sources_passing_original_all12': proofs,
        'native_paired_rows': pairs, 'ns_values': pairs * 2, 'checksum_pairs': pairs,
        'profile_counts': 'Separate instrumented controls, not added to scored candidate rows',
        'CI_elapsed_seconds': sum(x['elapsed_seconds'] for x in rows),
        'runs': rows, 'norm26_proof_confirmation': binding['proof'],
        'resources': {'tokens': 'UNKNOWN', 'cached_input_tokens': 'UNKNOWN', 'local_heavy_build': False, 'max_actual_CI_inflight': 1},
        'formal_submission': False, 'funds_or_signing': False,
        'comparison': 'Current champion=1.00x, ratios INFERRED; direct current private source and ARM timing unavailable',
    }
    target = ROUND / 'ROUND-RESULTS.json'
    target.write_text(json.dumps(result, ensure_ascii=False, indent=2) + '\n', encoding='utf-8', newline='\n')
    print(json.dumps({'receipt': str(target.relative_to(ROOT)), 'CI': len(rows), 'paired_rows': pairs, 'new_fullgate_sources': len(proofs), 'window_complete': result['research_window_complete']}))


if __name__ == '__main__':
    main()
