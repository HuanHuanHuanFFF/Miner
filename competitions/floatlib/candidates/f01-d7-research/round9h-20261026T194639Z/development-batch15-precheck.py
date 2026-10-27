"""Byte-level intake checks; this is not Lean or runtime validation."""
from pathlib import Path
from datetime import datetime, timezone
import hashlib
import json

HERE = Path(__file__).resolve().parent
ROOT = HERE.parents[4]
CANDIDATES = ROOT / 'competitions/floatlib/candidates'
sha = lambda data: hashlib.sha256(data).hexdigest()
b2 = (CANDIDATES / 'f01-r15-dev-packed-b2-1/Kernel.lean').read_bytes()
jam = (CANDIDATES / 'f01-r19-dev-jam-variable-math1/Kernel.lean').read_bytes()
assert jam.startswith(b2), 'Mathematical append must retain the complete B2 prefix'
old = (CANDIDATES / 'f01-r19-dev-dual-temporal-a4-4/Kernel.lean').read_bytes()
new = (CANDIDATES / 'f01-r19-dev-dual-temporal-a4-5/Kernel.lean').read_bytes()
assert new.count(b' <;> rfl') - old.count(b' <;> rfl') == 3
assert new.replace(b'] <;> rfl\n', b']\n') == old.replace(b'] <;> rfl\n', b']\n')
v7 = (HERE / 'development-helper-audit-v7.py').read_bytes()
v8 = (HERE / 'development-helper-audit-v8.py').read_bytes()
assert v8.replace(b'|R19JamVariableProbe', b'') == v7
rows = []
for name in ('f01-r19-dev-jam-variable-math1', 'f01-r19-dev-dual-temporal-a4-5'):
    folder = CANDIDATES / name
    raw = (folder / 'Kernel.lean').read_bytes()
    meta = json.loads((folder / 'manifest.json').read_bytes())
    assert sha(raw) == meta['candidate_sha256'] and len(raw) == meta['candidate_bytes']
    assert len(meta['explicit_helper_audit']) == meta['helper_audit_expected_count']
    assert sha((HERE / meta['helper_audit_module']).read_bytes()) == meta['helper_audit_module_sha256']
    rows.append(dict(candidate=name, sha256=sha(raw), bytes=len(raw), roots=meta['helper_audit_expected_count']))
result = dict(at_utc=datetime.now(timezone.utc).isoformat(), status='PASS_BYTE_LEVEL_ONLY', rows=rows,
    checks=['jam complete B2 prefix identical', 'dual inverse exactly removes three rfl tactic tails',
            'v8 inverse exactly removes one namespace permission', 'candidate, helper and root counts bound'],
    Lean='NOT_RUN', performance='NOT_RUN', allowed_axioms='UNCHANGED')
(HERE / 'development-batch15-precheck.json').write_bytes((json.dumps(result, indent=2) + '\n').encode())
print(json.dumps(result))
