"""Preserve the first handoff bytes and version explicit-type proof cleanups."""
from pathlib import Path
from hashlib import sha256
import json
from datetime import datetime, timezone

base = Path(__file__).resolve().parent
changes = [
    ('astra-small-shift-bias1.lean', 'astra-small-shift-bias2.lean',
     b'have h := Nat.pow_le_pow_right (a := 2) (by decide)',
     b'have h : 2 ^ (t.toNat - 1) \xe2\x89\xa4 2 ^ 7 := Nat.pow_le_pow_right (by decide)',
     'cc00612794e473d1e404606df2b502cda0321f0c6ac086bfb542dfed8dd03b66'),
    ('astra-word-add-alignment1.lean', 'astra-word-add-alignment2.lean',
     b'have h := Nat.pow_le_pow_right (a := 2) (by decide) hgap',
     b'have h : 2 ^ 2 \xe2\x89\xa4 2 ^ gap := Nat.pow_le_pow_right (by decide) hgap',
     '3628f637670621b049cfb3935e3e782ea2aa8403193f461a060082cb3a7ff5ca')]
for old_name, new_name, old_line, new_line, frozen_sha in changes:
    old = base / old_name
    b = old.read_bytes()
    if new_line in b:
        newer, original = b, b.replace(new_line, old_line)
    else:
        assert b.count(old_line) == 1
        original, newer = b, b.replace(old_line, new_line)
    assert sha256(original).hexdigest() == frozen_sha
    old.write_bytes(original)
    new = base / new_name
    if new.exists():
        assert new.read_bytes() == newer
    else:
        new.write_bytes(newer)

names = ['astra-word-add-alignment2.lean', 'astra-small-shift-bias2.lean',
         'astra-word-add-bounds1.lean', 'astra-word-add-rounding1.lean',
         'astra-biased-rne2.lean']
files = []
for name in names:
    b = (base / name).read_bytes()
    files.append(dict(path=name, bytes=len(b), sha256=sha256(b).hexdigest()))
receipt = dict(timestamp_utc=datetime.now(timezone.utc).isoformat(),
               status='DRAFT_NOT_COMPILED', files=files,
               original_first_handoff_preserved=True,
               revision='Prefer explicit type of Nat.pow_le_pow_right result to named implicit a; theorem statements unchanged.',
               dependencies='alignment2 + bounds1; existing R14NatNormal + FastMul.log2_shift for rounding1; smallShiftBias2 independent.',
               authorization='No candidate, CI, index or push action.')
(base / 'astra-word-add-fragments2.json').write_text(
    json.dumps(receipt, indent=2, ensure_ascii=False) + '\n', encoding='utf-8')
status_path = base / 'astra-status.json'
status = json.loads(status_path.read_text(encoding='utf-8'))
status['updated_at_utc'] = receipt['timestamp_utc']
status['state'] = 'R14_WORD_ADD_ALIGNMENT_BOUNDS_SMALL_SHIFT_DRAFTS_READY'
status['next_action'] = 'Deliver bounds/log2/carry/fraction supplements to D; inspect exact integration at natural checkpoint; all new fragments NOT_COMPILED.'
for name in names + ['astra-word-add-fragments2.json', 'astra-word-add-fragments-intake.json']:
    rel = (base / name).relative_to(base.parents[5]).as_posix() if False else str(base / name)
    if name not in status['artifacts']:
        status['artifacts'].append(name)
status['new_mathematical_task']['status'] = 'ALIGNMENT_SMALL_SHIFT_BOUNDS_LOG2_CARRY_FRACTION_DRAFTS_READY_NOT_COMPILED'
status['new_mathematical_task']['receipt'] = 'astra-word-add-fragments2.json'
tmp = base / 'astra-status.json.tmp'
tmp.write_text(json.dumps(status, indent=2, ensure_ascii=False) + '\n', encoding='utf-8')
tmp.replace(status_path)
print(json.dumps(receipt, indent=2, ensure_ascii=False))
