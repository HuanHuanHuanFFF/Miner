"""Audit collected R20 raw artifacts, exact candidates and actual runner time."""
from datetime import datetime, timezone
from pathlib import Path
import argparse
import hashlib
import json

ROOT = Path(__file__).resolve().parents[1]
E = ROOT / 'evidence/round20'


def read(path):
    return json.loads(path.read_bytes())


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--output', type=Path, required=True)
    args = parser.parse_args()
    artifacts, jobs, missing, count, size = [], {}, [], 0, 0
    for dispatch_path in sorted(E.glob('dispatch-*.json')):
        dispatch = read(dispatch_path)
        rid = str(dispatch['run']['databaseId'])
        folders = list((E / rid / dispatch['batch']).glob('*/raw-artifact-files.json'))
        if not folders:
            missing.append(rid)
        for inv_path in folders:
            folder, inv = inv_path.parent, read(inv_path)
            ci = read(folder / 'ci-run.json')
            assert str(ci['databaseId']) == rid and ci['headSha'] == dispatch['git_sha']
            assert ci['status'] == 'completed'
            for name, expected in inv['files'].items():
                file = (folder / name).resolve()
                assert file.is_relative_to(folder.resolve())
                raw = file.read_bytes()
                assert len(raw) == expected['bytes'] and hashlib.sha256(raw).hexdigest() == expected['sha256']
                count += 1
                size += len(raw)
            artifacts.append({'run_id': rid, 'batch': dispatch['batch'], 'path': folder.relative_to(ROOT).as_posix(), 'files': len(inv['files'])})
            seconds = 0
            for job in ci['jobs']:
                if job.get('startedAt') and job.get('completedAt') and job['conclusion'] != 'skipped':
                    seconds += (datetime.fromisoformat(job['completedAt'].replace('Z', '+00:00')) - datetime.fromisoformat(job['startedAt'].replace('Z', '+00:00'))).total_seconds()
            state_path = folder / 'state.json'
            pairs = len(read(state_path)['metrics']) if state_path.exists() else 0
            jobs[rid] = {'batch': dispatch['batch'], 'conclusion': ci['conclusion'], 'runner_seconds': seconds, 'original_paired_processes': pairs, 'source_commit': ci['headSha']}
    candidates = []
    for path in sorted((ROOT / 'candidates').glob('r20-*')):
        manifest = read(path / 'manifest.json')
        pair = {name: hashlib.sha256((path / name).read_bytes()).hexdigest() for name in ('parse.rs', 'Parse.lean')}
        assert pair == manifest['hashes']
        certificate = read(path / 'VERIFICATION.json') if (path / 'VERIFICATION.json').exists() else None
        if certificate:
            assert certificate['files'] == pair
        candidates.append({'candidate': path.name, 'files': pair, 'exact_public_gate': certificate['status'] if certificate else 'NOT_VERIFIED', 'formal_submission_sent': manifest['formal_submission_sent']})
    report = {'checked_at_utc': datetime.now(timezone.utc).isoformat(), 'status': 'VERIFIED_COLLECTED_BYTES',
        'jobs': jobs, 'uncollected_run_ids': missing, 'artifacts': artifacts, 'raw_file_count': count, 'raw_bytes': size,
        'runner_seconds': sum(j['runner_seconds'] for j in jobs.values()),
        'original_paired_processes': sum(j['original_paired_processes'] for j in jobs.values()),
        'candidates': candidates, 'money_cost': 'UNKNOWN', 'reset_cards_used': 0,
        'scope': 'Counted original-protocol paired processes include controls and are not independent samples. Runner seconds sum concurrent jobs, not wall time or billed cost. No formal submission.'}
    args.output.write_bytes((json.dumps(report, indent=2) + '\n').encode())
    print(json.dumps({k: report[k] for k in ('status', 'uncollected_run_ids', 'raw_file_count', 'raw_bytes', 'runner_seconds', 'original_paired_processes')}))


if __name__ == '__main__':
    main()
