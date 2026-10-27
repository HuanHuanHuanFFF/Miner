from pathlib import Path
from datetime import datetime, timezone
import hashlib
import json

here = Path(__file__).resolve().parent
root = here.parents[4]
sha = lambda data: hashlib.sha256(data).hexdigest()
save = lambda p, value: p.write_bytes((json.dumps(value, ensure_ascii=False, indent=2) + '\n').encode())
base = here / 'development-helper-audit-v5.py'
entries = [
    ('f01-r19-dev-dual-temporal-a4-4', here / 'astra-workers/matrix-structure/dual-temporal-frontier/proof4/Kernel-dual-temporal-a4-proof4.lean',
     'b92dac573897e6dc5c72eef9d5eebac778eeefde1f9ca262657dfacaa368c4ca', 'f01-r19-dev-dual-temporal-a4-2',
     'Apply actual successful first-branch explicit eq_def instance to the remaining loop proof branches; runtime/domain/theorem statements unchanged, traces removed'),
    ('f01-r19-dev-grs-add-runtime2', here / 'astra-workers/runtime-representation/grs-add-type-repair1/Kernel-grs-add-runtime-repair1.lean',
     '77377f8b373988545c557aa6f5cd5edfd82ec772bb643a404a15e26e02d627af', 'f01-r19-dev-grs-add-runtime1',
     'Only explicit UInt32 signmask annotation fixes actual HAnd UInt32 Nat error; runtime algorithm/fallback/publicB2 unchanged'),
]
rows = []
for name, source, expected, parent, mechanism in entries:
    raw = source.read_bytes()
    assert sha(raw) == expected and len(raw) <= 256000 and b'\r' not in raw
    parent_path = root / 'competitions/floatlib/candidates' / parent
    old = json.loads((parent_path / 'manifest.json').read_bytes())
    roots = old['explicit_helper_audit']
    folder = root / 'competitions/floatlib/candidates' / name
    folder.mkdir(exist_ok=False)
    (folder / 'Kernel.lean').write_bytes(raw)
    manifest = {'candidate': name, 'candidate_file': 'Kernel.lean', 'candidate_sha256': expected, 'candidate_bytes': len(raw),
        'created_at_utc': datetime.now(timezone.utc).isoformat(), 'parent': parent, 'parent_sha256': sha((parent_path / 'Kernel.lean').read_bytes()),
        'mechanism': mechanism, 'validation_mode': 'statement-only', 'proof_status': 'NOT_RUN', 'performance': 'NOT_RUN',
        'explicit_helper_audit': roots, 'helper_audit_expected_count': len(roots), 'helper_audit_source_sha256': expected,
        'helper_audit_required_endpoints': ['Submission.bmm_spec', roots[-1]],
        'helper_audit_module': base.name, 'helper_audit_module_sha256': sha(base.read_bytes()),
        'source_producer_path': source.relative_to(root).as_posix(), 'source_producer_sha256': expected, 'formal_submission': 'NOT_SUBMITTED'}
    save(folder / 'manifest.json', manifest)
    rows.append({'candidate': name, 'sha256': expected, 'bytes': len(raw), 'roots': len(roots)})
for name, status in (
    ('f01-r19-dev-direct-bias-public1', 'STATEMENT_SIGNAL_MINUS15_EMPTY_OUTPUT_CAUSE_UNKNOWN'),
    ('f01-r19-dev-dual-equation-diagnostic1', 'FIRST_BRANCH_EXPLICIT_EQUATIONS_SUCCEED_FOUR_OTHER_BRANCHES_EXPECTED_RED'),
    ('f01-r19-dev-grs-add-runtime1', 'STATEMENT_HAND_UINT32_NAT_SIGNMASK_ERROR'),
):
    path = root / 'competitions/floatlib/candidates' / name / 'manifest.json'
    value = json.loads(path.read_bytes())
    value.update(proof_status=status, statement_run=40428306094, performance='NOT_RUN')
    save(path, value)
save(here / 'development-batch12-import.json', {'at_utc': datetime.now(timezone.utc).isoformat(), 'rows': rows,
    'scope': 'Exact proof/type-only repairs based on actual CI11. No runtime/guard change, no source performance qualification.'})
print(json.dumps(rows))
