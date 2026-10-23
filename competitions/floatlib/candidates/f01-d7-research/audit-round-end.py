"""Audit saved R7 evidence; completion requires the actual ten-hour deadline."""
import argparse
from datetime import datetime, timezone
import hashlib
import json
from pathlib import Path
import re
import subprocess

ROOT = Path(__file__).resolve().parents[4]
HERE = Path(__file__).resolve().parent
START = datetime.fromisoformat('2026-10-22T18:22:17+00:00')
DEADLINE = datetime.fromisoformat('2026-10-23T04:22:17+00:00')
parser = argparse.ArgumentParser(description=__doc__)
parser.add_argument('--preflight', action='store_true')
parser.add_argument('--output', required=True, type=Path)
args = parser.parse_args()
now = datetime.now(timezone.utc)
if not args.preflight:
    assert now >= DEADLINE, 'The ten-hour window has not finished'
output = args.output.resolve()
assert output.is_relative_to(HERE.resolve()) and not output.exists()

def read(path):
    return json.loads(path.read_bytes())

def identity(path):
    raw = path.read_bytes()
    return {'path': path.relative_to(ROOT).as_posix(), 'sha256': hashlib.sha256(raw).hexdigest(), 'bytes': len(raw)}

def verify(path, expected):
    actual = identity(path)
    assert actual['sha256'] == expected['sha256'], path
    assert actual['bytes'] == expected['bytes'], path
    return actual

freeze_path = HERE / 'source-freeze.json'
freeze = read(freeze_path)
for row in freeze['sources'] + freeze['supporting_files']:
    verify(ROOT / row['path'], row)
    if 'manifest' in row:
        verify(ROOT / row['manifest']['path'], row['manifest'])
index = read(HERE / 'math-reserve-index.json')
for path, row in index['evidence_registry'].items():
    verify(ROOT / path, row)

costs = read(HERE / 'validation-cost-ledger.json')
ci = []
for row in costs['runs']:
    path = ROOT / row['raw_ci_record']
    raw = identity(path)
    assert raw['sha256'] == row['raw_sha256'], path
    meta = read(path)
    assert meta['status'] == 'completed' and meta['headSha'] == row['source_commit'], path
    ci.append({'run': row['run'], 'status': meta['status'], 'conclusion': meta['conclusion'], 'record': raw})
maintenance = ROOT / '.local-maintenance/r7-20261023'
snapshots = sorted(p for p in maintenance.glob('ci-readonly-*.json') if re.fullmatch(r'ci-readonly-\d{8}T\d{6}Z.json', p.name))
assert snapshots
snapshot = snapshots[-1]
observed = datetime.strptime(snapshot.stem.removeprefix('ci-readonly-'), '%Y%m%dT%H%M%SZ').replace(tzinfo=timezone.utc)
active = [r for r in read(snapshot) if r['status'] != 'completed']
assert not active, active
if not args.preflight:
    assert 0 <= (now-observed).total_seconds() <= 900, 'Refresh the read-only CI snapshot before closing'

official_pointer = read(HERE / 'current-official-snapshot.json')
official = HERE / official_pointer['directory']
for row in read(official / 'receipts.json')['responses'].values():
    if 'file' in row:
        verify(official / row['file'], row)
champion = read(official / 'champion-detail.raw')
assert champion['id'] == official_pointer['champion']
state = read(ROOT / 'competitions/floatlib/coordination/development-status.json')
retained = ROOT / state['kernel']
assert identity(retained)['sha256'] == state['kernel_sha256']
test_root = HERE / 'source-budget-test-evidence'
test_receipt = read(test_root / 'receipt.json')
assert test_receipt['exit_code'] == 0
assert identity(HERE / 'source-budget.py')['sha256'] == test_receipt['script_sha256']
assert identity(HERE / 'test-source-budget.py')['sha256'] == test_receipt['tests_sha256']
for name, row in test_receipt['raw_output'].items():
    verify(test_root / name, row)

result = {
    'audited_at_utc': now.isoformat(),
    'window_start_utc': START.isoformat(), 'window_deadline_utc': DEADLINE.isoformat(),
    'elapsed_wall_seconds': (now-START).total_seconds(),
    'audit_kind': 'PREDEADLINE_EVIDENCE_CHECK_ONLY' if args.preflight else 'POSTDEADLINE_EVIDENCE_CHECK',
    'window_complete': now >= DEADLINE and not args.preflight,
    'head_at_audit': subprocess.check_output(['git', 'rev-parse', 'HEAD'], cwd=ROOT, text=True).strip(),
    'frozen_candidate_sources': len(freeze['sources']), 'frozen_supporting_files': len(freeze['supporting_files']),
    'frozen_source_bytes_unchanged': True, 'math_registry_files_rehashed': len(index['evidence_registry']),
    'started_ci_terminal_records': ci, 'latest_readonly_ci_snapshot': identity(snapshot),
    'ci_observed_at_utc': observed.isoformat(), 'ci_active_at_snapshot': active,
    'official_champion': champion['id'], 'official_observed_at_utc': official_pointer['queried_at_utc'],
    'official_raw_receipts': identity(official / 'receipts.json'),
    'retained_kernel': identity(retained), 'retained_full_gate_runs': state['performance']['full_gate_runs'],
    'new_runtime_integrations': 'NOT_RUN_UNLESS_A_SEPARATE_EXACT_ORIGINAL_GATE_RECEIPT_EXISTS',
    'champion_replacement_goal': state['acceptance_target_status'],
    'public_push_state': state['collaboration']['publication']['state'],
    'source_budget_regression_receipt': identity(test_root / 'receipt.json'),
    'boundary': 'This audit rehashes saved evidence only; it runs no Lean, CI or performance experiment. Wall time includes research, preparation, review, recovery and blocked waiting; elapsed time is not productive coding time or champion attainment.',
}
with output.open('x', encoding='utf8') as stream:
    stream.write(json.dumps(result, ensure_ascii=False, indent=2)+'\n')
print(json.dumps({'audit_kind': result['audit_kind'], 'window_complete': result['window_complete'],
                  'elapsed_wall_seconds': result['elapsed_wall_seconds'], 'candidate_sources': result['frozen_candidate_sources'],
                  'math_files': result['math_registry_files_rehashed'], 'terminal_ci': len(ci), 'output': str(output)}, ensure_ascii=False))
