"""Freeze the one requested proof probe; do not alter current execution bindings."""
from pathlib import Path
from datetime import datetime, timezone
import hashlib
import json
import re

here = Path(__file__).resolve().parent
root = here.parents[4]
origin = here / 'astra-workers/exact-arithmetic/bias-frontier'
producer = json.loads((origin / 'probe-manifest.json').read_bytes())
source = origin / producer['file']
raw = source.read_bytes()
digest = lambda data: hashlib.sha256(data).hexdigest()
assert digest(raw) == producer['sha256'] == '1180c82c69ded5619978a2673f47ce9ed6d94a80930099429fc0b7cd5b0044bd'
assert len(raw) == producer['bytes'] == 235339
baseline = root / 'competitions/floatlib/candidates/f01-r15-dev-packed-b2-1/Kernel.lean'
assert digest(baseline.read_bytes()) == '622d8394a7127e93dcaf992c62c6dfcff7208d212738409a5e34525dfafd1a58'
assert raw.startswith(baseline.read_bytes())
roots = producer['roots']
assert len(roots) == len(set(roots)) == producer['roots_count'] == 14
assert roots == re.findall(r'^#print axioms (\S+)', (origin / 'HelperAudit-direct-bias.lean.inc').read_text('utf-8'), re.M)
old_helper = here / 'development-helper-audit-v4.py'
helper = here / 'development-helper-audit-v5.py'
old = old_helper.read_bytes()
assert old.count(b'|R19Base)') == 1
new = old.replace(b'|R19Base)', b'|R19Base|BranchlessRNESeed|R19PostBias)')
assert not helper.exists()
helper.write_bytes(new)
name = 'f01-r19-dev-direct-bias-probe1'
target = root / 'competitions/floatlib/candidates' / name
target.mkdir(exist_ok=False)
(target / 'Kernel.lean').write_bytes(raw)
manifest = {
    'candidate': name, 'candidate_file': 'Kernel.lean', 'candidate_sha256': digest(raw), 'candidate_bytes': len(raw),
    'created_at_utc': datetime.now(timezone.utc).isoformat(), 'parent': 'f01-r15-dev-packed-b2-1',
    'parent_sha256': digest(baseline.read_bytes()), 'validation_mode': 'statement-only', 'proof_status': 'NOT_RUN',
    'performance': 'NOT_RUN_PUBLIC_ENTRIES_STILL_B2',
    'mechanism': 'One fixed23/24 integer ties-to-even bias proof probe and complete guarded diagnostic caller; current public add/mul/sum/bmm remain exact B2',
    'explicit_helper_audit': roots, 'helper_audit_expected_count': len(roots), 'helper_audit_source_sha256': digest(raw),
    'helper_audit_required_endpoints': ['Submission.bmm_spec', 'BranchlessRNESeed.grouped_eq_existing_rse', 'R19PostBias.normalized_quotient'],
    'helper_audit_module': helper.name, 'helper_audit_module_sha256': digest(new),
    'source_producer_path': source.relative_to(root).as_posix(), 'source_producer_sha256': digest(raw),
    'execution_status': 'HOLD_UNTIL_CURRENT_DISCOVERY_DECISION_AND_DIAGNOSTIC_V5_BINDING',
    'history': 'Old branchless seed compilation SIGTERM cause remains UNKNOWN; original generic/flag RSE performance negatives retained. This is not a new performance discovery or accepted public MUL proof.',
    'formal_submission': 'NOT_SUBMITTED',
}
save = lambda p, value: p.write_bytes((json.dumps(value, ensure_ascii=False, indent=2) + '\n').encode())
save(target / 'manifest.json', manifest)
save(here / 'development-direct-bias-import.json', {
    'at_utc': manifest['created_at_utc'], 'candidate': name, 'sha256': digest(raw), 'bytes': len(raw),
    'helper': helper.relative_to(root).as_posix(), 'helper_sha256': digest(new),
    'change': 'Only exact additional helper namespaces accepted by a new version; original v4/current CI execution files unchanged',
    'original_producer_manifest_sha256': digest((origin / 'probe-manifest.json').read_bytes()),
    'original_helper_list_sha256': digest((origin / 'HelperAudit-direct-bias.lean.inc').read_bytes()),
    'public_entries_unchanged': True, 'not_a_performance_candidate': True,
})
print(json.dumps({'candidate': name, 'sha256': digest(raw), 'bytes': len(raw), 'roots': len(roots), 'dispatch': 'HOLD'}))
