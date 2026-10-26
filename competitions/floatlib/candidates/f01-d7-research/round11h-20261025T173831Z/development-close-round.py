"""Close R18 only after its full210 minutes and every started CI is collected."""
from datetime import datetime, timezone
from pathlib import Path
import argparse
import hashlib
import json

HERE = Path(__file__).resolve().parent
ROOT = HERE.parents[4]
D7 = HERE.parent
COMMON = ROOT / 'competitions/floatlib/candidates/f01-mul-log2-proof1/ci-runs'
read = lambda p: json.loads(p.read_bytes())
sha = lambda p: hashlib.sha256(p.read_bytes()).hexdigest()
save = lambda p, x: p.write_bytes((json.dumps(x, ensure_ascii=False, indent=2) + '\n').encode())


def main():
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument('--close', action='store_true')
    args = ap.parse_args()
    state_path = ROOT / 'competitions/floatlib/coordination/development-status.json'
    state = read(state_path)
    rr = state['research_round']
    assert rr['id'] == 'R18-3h30-20261026T081528Z'
    assert not rr['active_ci'] and not state['active_jobs']
    assert len(rr['started_ci']) == len(set(rr['started_ci']))
    assert set(rr['started_ci']) == set(rr['completed_ci']) and rr['started_ci']
    assert sha(ROOT / state['kernel']) == state['kernel_sha256'] == '622d8394a7127e93dcaf992c62c6dfcff7208d212738409a5e34525dfafd1a58'
    model = read(D7 / 'champion-time-estimate.json')
    pointer = read(D7 / 'current-official-snapshot.json')
    view = read(D7 / 'multiplier-comparison.json')
    assert model['champion_submission'] == pointer['champion'] == view['champion']['submission']
    assert view['champion_time_estimate']['evidence_sha256'] == sha(D7 / 'champion-time-estimate.json')
    jobs = []
    for run in rr['completed_ci']:
        folder = COMMON / str(run)
        meta = read(folder / 'ci-run.json')
        index = read(folder / 'original-artifact-hashes.json')
        assert meta['status'] == 'completed'
        for relative, item in index['files'].items():
            original = folder / index['directory'] / relative
            assert original.stat().st_size == item['bytes'] and sha(original) == item['sha256']
        terminal = read(HERE / f'development-terminal-{run}.json')
        assert terminal['source_commit'] == meta['headSha'] and terminal['state'] == 'completed'
        jobs.append({'run': run, 'conclusion': meta['conclusion'], 'source_commit': meta['headSha'],
            'artifact_files': len(index['files']), 'artifact_index_sha256': sha(folder / 'original-artifact-hashes.json'),
            'terminal_receipt': (HERE / f'development-terminal-{run}.json').relative_to(ROOT).as_posix()})
    outcomes = []
    for path in sorted(HERE.glob('result-1826*.json')):
        result = read(path)
        if result.get('full_gate_both'):
            outcomes.append({k: result[k] for k in ('candidate', 'sha256', 'run', 'seed', 'relative_normalized_ratio', 'gain_p05', 'per_operation_normalized', 'local_discovery_screen_passed')})
    assert not list(HERE.glob('cohort*.json')), 'A new confirmation cohort requires its own final accounting'
    proof = read(HERE / 'development-proof-batch-40296747927.json')
    now = datetime.now(timezone.utc)
    start = datetime.fromisoformat(rr['start_utc'].replace('Z', '+00:00'))
    deadline = datetime.fromisoformat(rr['deadline_utc'].replace('Z', '+00:00'))
    assert (deadline - start).total_seconds() == 210 * 60
    report = {'round': rr['id'], 'start_utc': rr['start_utc'], 'deadline_utc': rr['deadline_utc'],
        'checked_at_utc': now.isoformat(), 'budget_status': 'COMPLETED_210_MINUTES' if args.close else 'FINAL_REVIEW_ACTIVE_UNTIL_DEADLINE',
        'ci': jobs, 'all_started_ci_terminal_and_collected': True,
        'original_artifact_files': sum(j['artifact_files'] for j in jobs),
        'retained_candidate': state['candidate'], 'retained_sha256': state['kernel_sha256'],
        'adoption_performed': False, 'timed_outcomes': outcomes, 'confirmation_groups_generated': False,
        'champion': pointer['champion'], 'champion_goal': 'UNACHIEVED', 'formal_submission': 'NOT_SUBMITTED',
        'current_model_sha256': sha(D7 / 'champion-time-estimate.json'),
        'official_receipt': (D7 / pointer['directory'] / 'receipts.json').relative_to(ROOT).as_posix(),
        'verified_interface_batch': (HERE / 'development-proof-batch-40296747927.json').relative_to(ROOT).as_posix(),
        'verified_interface_batch_sha256': sha(HERE / 'development-proof-batch-40296747927.json'),
        'interface_scope': 'Explicit helper audit and entire module replay for U32/U64 interfaces and lowering diagnostic; not a separate performance claim',
        'latest_add_terminal': (HERE / 'development-terminal-40313517927.json').relative_to(ROOT).as_posix(),
        'deepseek': 'NOT_PARTICIPATING', 'local_lean': 'NOT_RUN', 'private_or_paid_runner': False}
    assert proof, 'Proof feedback must remain available'
    if args.close:
        assert now >= deadline, 'Do not end the authorized window early'
        report.update(ended_at_utc=now.isoformat(), elapsed_minutes=(now - start).total_seconds() / 60)
        rr.update(state='COMPLETED_WINDOW', window_status='COMPLETED_210_MINUTES', ended_at_utc=now.isoformat(),
            current_phase='All started CI terminal and original evidence collected; B2 retained, no new champion or adoption')
        state.update(state='R18_WINDOW_COMPLETED_RETAIN_B2_ALL_CI_COLLECTED', updated_at_utc=now.isoformat())
        state['collaboration']['state'] = 'COMPLETED_WINDOW'
        save(state_path, state)
    save(HERE / 'development-round-results.json', report)
    print(json.dumps({'budget_status': report['budget_status'], 'ci': len(jobs),
        'original_artifact_files': report['original_artifact_files'], 'adoption': False, 'champion': pointer['champion']}))


if __name__ == '__main__':
    main()
