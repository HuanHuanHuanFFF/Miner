"""Refresh only authenticated same-champion metadata; numeric model bytes frozen."""
from datetime import datetime, timezone
from pathlib import Path
import argparse
import hashlib
import importlib.util
import json

HERE = Path(__file__).resolve().parent
ROOT = HERE.parents[4]
D7 = HERE.parent
read = lambda p: json.loads(p.read_bytes())
sha = lambda p: hashlib.sha256(p.read_bytes()).hexdigest()
encoded = lambda x: (json.dumps(x, ensure_ascii=False, indent=2) + '\n').encode()
ap = argparse.ArgumentParser()
ap.add_argument('--snapshot', required=True)
args = ap.parse_args()
snapshot = D7 / args.snapshot
assert snapshot.resolve().parent == D7.resolve() and snapshot.name.startswith('official-')
receipt = read(snapshot / 'receipts.json')
assert receipt['status'] == 'VERIFIED_SNAPSHOT' and receipt['compatible_frozen_protocol']
for item in receipt['responses'].values():
    raw = snapshot / item['file']
    assert raw.stat().st_size == item['bytes'] and sha(raw) == item['sha256']
detail = read(snapshot / 'champion-detail.raw')
report = read(snapshot / 'champion-report.raw')['report']
report = json.loads(report) if isinstance(report, str) else report
champion = next(c for c in read(snapshot / 'champions.raw') if c['current'])
competition = read(snapshot / 'competition.raw')
model_path = D7 / 'champion-time-estimate.json'
original_model = model_path.read_bytes()
model = json.loads(original_model)
assert model['champion_submission'] == detail['id'] == champion['submission'] == receipt['champion'] == int(report['submission'])
assert model['champion_digest'] == detail['digest'] and model['champion_suite'] == report['suite'], 'Champion changed: reviewed transition required'
assert detail['state'] == 'accepted' and detail['verification_current'] and report['passed'] and detail['classes'] == report['classes']
spec = importlib.util.spec_from_file_location('r19_metadata_tx', HERE / 'adopt-three-confirmed.py')
adopter = importlib.util.module_from_spec(spec)
spec.loader.exec_module(adopter)
view_path = D7 / 'multiplier-comparison.json'
pointer_path = D7 / 'current-official-snapshot.json'
state_path = ROOT / 'competitions/floatlib/coordination/development-status.json'
tx = adopter.Transaction([view_path, pointer_path, state_path])
view, pointer, state = (json.loads(tx.before[p.resolve()]) for p in (view_path, pointer_path, state_path))
assert state['kernel_sha256'] == view['kernel_sha256'] == model['kernel_sha256']
view['champion'].update(receipts=(snapshot / 'receipts.json').relative_to(ROOT).as_posix(),
    checked_at_utc=receipt['queried_at_utc'], snapshot=competition['current_snapshot_id'],
    official_cumulative_speedup_vs_shipped=champion['speedup_vs_shipped'], official_speedup_basis=champion['speedup_basis'])
pointer.update(directory=snapshot.name, queried_at_utc=receipt['queried_at_utc'], champion=detail['id'],
    official_commit=receipt['official_commit'], policy_snapshot=competition['current_snapshot_id'])
state['current_champion_comparison'].update(submission=detail['id'], source_digest=detail['digest'],
    policy_snapshot=competition['current_snapshot_id'], queried_at_utc=receipt['queried_at_utc'])
state['current_multiplier_view'].update(official_champion=detail['id'], snapshot=competition['current_snapshot_id'])
state['updated_at_utc'] = datetime.now(timezone.utc).isoformat()
try:
    assert model_path.read_bytes() == original_model
    for path, value in ((view_path, view), (pointer_path, pointer), (state_path, state)):
        tx.write(path, encoded(value))
    tx.unchanged()
    assert model_path.read_bytes() == original_model
except BaseException:
    tx.rollback()
    raise
record = {'at_utc': state['updated_at_utc'], 'snapshot': snapshot.name, 'receipt_sha256': sha(snapshot / 'receipts.json'),
    'champion': detail['id'], 'numeric_model_sha256_unchanged': sha(model_path), 'scope': 'Same-source/same-champion official metadata only'}
stamp = datetime.now(timezone.utc).strftime('%Y%m%dT%H%M%S%fZ')
with (HERE / ('development-official-metadata-' + stamp + '.json')).open('xb') as stream:
    stream.write(encoded(record))
print(json.dumps(record))
