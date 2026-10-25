"""Freeze a labeled same-input control repeat; never a new selection sample."""
from pathlib import Path
from datetime import datetime, timezone
import hashlib
import json
import os

HERE = Path(__file__).resolve().parent
ROOT = HERE.parents[4]
sha = lambda p: hashlib.sha256(p.read_bytes()).hexdigest()
state_path = ROOT / 'competitions/floatlib/coordination/development-status.json'
state_raw = state_path.read_bytes()
state = json.loads(state_raw)
assert state['research_round']['id'] == 'R16-20261025T091810Z'
assert state['research_round']['active_ci'] == []
original = HERE / 'plan-1626007.json'
old_hash = sha(original)
old = json.loads(original.read_bytes())
assert old['seed'] == 1626007
names = ('f01-r8-combined-result-guard', 'f01-r15-dev-packed-b2-1', 'f01-r16-dev-native-add-high3')
expected = ('41bce4856c4c921dd67b6115928df16e5e8ed08a55b71f1296d28b77cf9ce9a7',
            '622d8394a7127e93dcaf992c62c6dfcff7208d212738409a5e34525dfafd1a58',
            'f7f4702f9191061bb70a274610c9b735967ce4460ca2ef6ae121b9264fad18dd')
rows = []
files = {}
for name, digest in zip(names, expected):
    folder = ROOT / 'competitions/floatlib/candidates' / name
    kernel, manifest = folder / 'Kernel.lean', folder / 'manifest.json'
    assert sha(kernel) == digest
    for p in (kernel, manifest):
        files[p.relative_to(ROOT).as_posix()] = dict(sha256=sha(p), bytes=p.stat().st_size)
    row = dict(candidate=name, sha256=digest, capture_codegen=False)
    if name == names[-1]:
        row['validation_mode'] = 'statement-only'
    else:
        assert next(r['sha256'] for r in old['candidates'] if r['candidate'] == name) == digest
    rows.append(row)
plan = dict(old)
plan.update(candidates=rows, sample_role='ADDITIONAL_INPUT_DIAGNOSTIC',
            purpose='Repeat exact completed1626007 inputs and unchanged41/B2 controls in reversed order on a fresh runner; final f7f row is static statement/C diagnostic only. No source selection, seed reset, new independent input or adoption claim.',
            same_input_as_run=40187127847, source_selection_allowed=False,
            mixed_modes_explicit=True)
destination = HERE / 'plan-1626007-control-repeat.json'
freeze = HERE / 'freeze-1626007-control-repeat.json'
assert not destination.exists() and not freeze.exists()
live = ROOT / 'competitions/floatlib/candidates/f01-d7-public-suite/suite-plan.json'
previous_live = sha(live)
encoded = lambda obj: (json.dumps(obj, ensure_ascii=False, indent=2)+'\n').encode()
destination.write_bytes(encoded(plan))
for p in (original, Path(__file__).resolve(), HERE / 'development-ci.py'):
    files[p.relative_to(ROOT).as_posix()] = dict(sha256=sha(p), bytes=p.stat().st_size)
freeze.write_bytes(encoded(dict(recorded_at_utc=datetime.now(timezone.utc).isoformat(),
                               request_sha256=sha(destination), previous_live_plan_sha256=previous_live,
                               role='ADDITIONAL_INPUT_DIAGNOSTIC', same_input_as_run=40187127847,
                               original_request_sha256_unchanged=old_hash, files=files)))
assert sha(original) == old_hash
live.write_bytes(destination.read_bytes())
state['research_round'].setdefault('prepared_requests', []).append(dict(seed=1626007,
    role='ADDITIONAL_INPUT_DIAGNOSTIC', plan=destination.relative_to(ROOT).as_posix(),
    sha256=sha(destination), candidates=rows, same_input_as_run=40187127847))
state['updated_at_utc'] = datetime.now(timezone.utc).isoformat()
temp = state_path.with_name('development-status-control-repeat.tmp')
assert not temp.exists() and state_path.read_bytes() == state_raw
temp.write_bytes(encoded(state))
os.replace(temp, state_path)
print(json.dumps(dict(plan=destination.relative_to(ROOT).as_posix(), seed=1626007,
                     request_sha256=sha(destination), original_request_sha256_unchanged=old_hash)))
