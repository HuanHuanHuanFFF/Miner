"""Import two exact, already reviewed R handoffs without changing their runtime."""
from pathlib import Path
from datetime import datetime, timezone
import hashlib
import json

HERE = Path(__file__).resolve().parent
ROOT = HERE.parents[4]
sha = lambda raw: hashlib.sha256(raw).hexdigest()
save = lambda path, value: path.write_bytes((json.dumps(value, ensure_ascii=False, indent=2) + '\n').encode())
base = HERE / 'development-helper-audit-v7.py'
audit = HERE / 'development-helper-audit-v8.py'
old = base.read_bytes()
new = old.replace(b'R19BiasBase|BranchlessRNESeed', b'R19BiasBase|R19JamVariableProbe|BranchlessRNESeed')
assert old != new and new.count(b'R19JamVariableProbe') == 1
if audit.exists():
    assert audit.read_bytes() == new
else:
    audit.write_bytes(new)

jam = HERE / 'astra-workers/matrix-structure/grs-jam-math/low-state-repair1'
jam_meta = json.loads((jam / 'manifest.json').read_bytes())
dual_parent = ROOT / 'competitions/floatlib/candidates/f01-r19-dev-dual-temporal-a4-4'
dual_meta = json.loads((dual_parent / 'manifest.json').read_bytes())
entries = [
    ('f01-r19-dev-jam-variable-math1', jam / 'Probe-jam-variable-repair1.lean',
     'b3724bc5cb19a85fdae25187d8700bb43233ab4098a9c0a92b97a36d0eaac496', 233592,
     jam_meta['roots'], audit, 'f01-r15-dev-packed-b2-1',
     'Peer statement PASS only; obtain original two-module replay and all 15 allowed-only roots. Public runtime remains exact B2.'),
    ('f01-r19-dev-dual-temporal-a4-5', HERE / 'astra-workers/matrix-structure/dual-temporal-frontier/proof5/Kernel-dual-temporal-a4-proof5.lean',
     'c36bc2502904bf946d442de1a4646e09689f016643f09ab0b6788f9bdd375250', 241509,
     dual_meta['explicit_helper_audit'], HERE / 'development-helper-audit-v5.py', dual_parent.name,
     'Close the three actual CI12 tail goals with rfl only; runtime, domains and all 18 theorem statements retained.'),
]
rows = []
for name, source, expected, size, roots, helper, parent, mechanism in entries:
    raw = source.read_bytes()
    assert sha(raw) == expected and len(raw) == size <= 256000 and b'\r' not in raw
    parent_dir = ROOT / 'competitions/floatlib/candidates' / parent
    target = ROOT / 'competitions/floatlib/candidates' / name
    target.mkdir(exist_ok=False)
    (target / 'Kernel.lean').write_bytes(raw)
    manifest = dict(candidate=name, candidate_file='Kernel.lean', candidate_sha256=expected, candidate_bytes=size,
        created_at_utc=datetime.now(timezone.utc).isoformat(), parent=parent,
        parent_sha256=sha((parent_dir / 'Kernel.lean').read_bytes()), mechanism=mechanism,
        validation_mode='statement-only', proof_status='NOT_RUN_IN_D_STANDARD_REPLAY', performance='NOT_RUN',
        explicit_helper_audit=roots, helper_audit_expected_count=len(roots), helper_audit_source_sha256=expected,
        helper_audit_required_endpoints=['Submission.bmm_spec', roots[-1]],
        helper_audit_module=helper.name, helper_audit_module_sha256=sha(helper.read_bytes()),
        source_producer_path=source.relative_to(ROOT).as_posix(), source_producer_sha256=expected,
        formal_submission='NOT_SUBMITTED')
    save(target / 'manifest.json', manifest)
    rows.append(dict(candidate=name, sha256=expected, bytes=size, roots=len(roots), mechanism=mechanism))
save(HERE / 'development-batch15-import.json', dict(at_utc=datetime.now(timezone.utc).isoformat(), rows=rows,
    audit_change='v8 adds only namespace R19JamVariableProbe; original replay and allowed axioms unchanged'))
print(json.dumps(rows))
