from pathlib import Path
from datetime import datetime, timezone
import ast
import hashlib
import json

here = Path(__file__).resolve().parent
root = here.parents[4]
sha = lambda raw: hashlib.sha256(raw).hexdigest()
save = lambda p, value: p.write_bytes((json.dumps(value, ensure_ascii=False, indent=2) + '\n').encode())
worker = here / 'development-workers/structural-cost/dc-decode-frontier'
receipt = json.loads((worker / 'draft-receipt.json').read_bytes())
source = worker / 'Kernel-dc-rawpair.draft.lean'
raw = source.read_bytes()
assert sha(raw) == receipt['draft_sha256'] == '8134696db068ceb0c969c7c896199e9c019a7cd375bfe34ab2712eb8d2464365'
assert len(raw) == 235299 and receipt['exact_inverse_to_parent'] and b'\r' not in raw
roots = receipt['proof_roots']; assert len(roots) == len(set(roots)) == 14
helper = here / 'development-helper-audit-v5.py'
name = 'f01-r19-dev-dc-rawpair1'
folder = root / 'competitions/floatlib/candidates' / name
folder.mkdir(exist_ok=False)
(folder / 'Kernel.lean').write_bytes(raw)
manifest = {'candidate': name, 'candidate_file': 'Kernel.lean', 'candidate_sha256': sha(raw), 'candidate_bytes': len(raw),
    'created_at_utc': datetime.now(timezone.utc).isoformat(), 'validation_mode': 'statement-only', 'proof_status': 'NOT_RUN',
    'performance': 'NOT_RUN', 'parent': 'f01-r15-dev-packed-b2-1', 'parent_sha256': receipt['parent_sha256'],
    'mechanism': 'No-preparation DC raw two-output loop shares each A conversion; two original B conversions, ordered chains, original odd scalar tail and exact replay remain; other3 public ops/outer routing unchanged',
    'history': 'R9 both-R2 converter full negative retained; this does not retry that mechanism or alter B2 m/p predicates. Narrow target affects5.98%whole in one seen plan; not a10% guarantee.',
    'explicit_helper_audit': roots, 'helper_audit_expected_count': len(roots), 'helper_audit_source_sha256': sha(raw),
    'helper_audit_required_endpoints': ['Submission.bmm_spec', 'Submission.R19DCRawPair.core_eq_direct'],
    'helper_audit_module': helper.name, 'helper_audit_module_sha256': sha(helper.read_bytes()),
    'source_producer_path': source.relative_to(root).as_posix(), 'source_producer_sha256': sha(raw), 'formal_submission': 'NOT_SUBMITTED'}
save(folder / 'manifest.json', manifest)
diag = root / 'competitions/floatlib/candidates/f01-word-tensors/ci-diagnostics.py'
old = diag.read_bytes();before = b"or 'R19DualTemporal' in name)"
assert old.count(before) == 1
new = old.replace(before, b"or 'R19DualTemporal' in name or 'R19DCRawPair' in name)")
tree = ast.parse(new)
embedded = [n.value.value for n in ast.walk(tree) if isinstance(n, ast.Assign) and any(isinstance(t, ast.Name) and t.id=='code' for t in n.targets)]
assert len(embedded)==1
ast.parse(embedded[0]);diag.write_bytes(new)
save(here / 'development-rawpair-import.json', {'at_utc': manifest['created_at_utc'], 'candidate': name, 'sha256': sha(raw),
    'bytes': len(raw), 'roots': len(roots), 'old_diagnostic_sha256': sha(old), 'new_diagnostic_sha256': sha(new),
    'scope': 'One bounded statement/actual selected-loop cost discriminator, not a first scoredD or adoption. No official gate/flags/resources changed.'})
print(json.dumps({'candidate': name, 'sha256': sha(raw), 'bytes': len(raw), 'roots': len(roots)}))
