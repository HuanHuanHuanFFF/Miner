from pathlib import Path
from hashlib import sha256
from datetime import datetime, timezone
import json

here = Path(__file__).resolve().parent
repo = next(p for p in here.parents if (p / 'AGENTS.md').is_file())
now = datetime.now(timezone.utc)
roots = ['fastOK_notNaN', 'native_add_spec_of_fastOK', 'native_mul_spec_of_fastOK', 'pairOK_normal']
files = ['FastOKNativeBridges.lean.inc', 'PairDomain.lean.inc', 'REVIEW.md', 'boundary-witnesses.json', 'check_boundaries.py']
items = {}
for name in files:
    data = (here / name).read_bytes()
    items[name] = {'sha256': sha256(data).hexdigest(), 'bytes': len(data)}
witnesses = json.loads((here / 'boundary-witnesses.json').read_text())
assert witnesses['cases'] == 50 and witnesses['mismatches'] == 0
manifest = {
    'checked_utc': now.isoformat(),
    'first_tool_utc': '2026-10-28T00:38:36Z',
    'bound_utc': '2026-10-28T00:58:36Z',
    'common_deadline_utc': '2026-10-28T03:12:47Z',
    'state': 'INDEPENDENT_SEMANTIC_REVIEW_READY_PROOF_SNIPPETS_NOT_RUN',
    'roots': ['Submission.R22NativeColdReview.' + r for r in roots],
    'files': items,
    'runtime_and_old_source_bindings': witnesses['source_bindings'],
    'scope': 'Original hit-domain semantics, signed zeros, low-normal/subnormal/Inf/NaN misses and source-result-test removal only within hit arms',
    'source_edits': 'Only this research directory; D runtime/candidate unchanged',
    'Lean': 'NOT_RUN', 'CI': 'NOT_RUN', 'native_execution': 'NOT_RUN',
    'new_public_ADD_MUL_specs': 'NOT_ASSEMBLED_OR_VERIFIED',
    'performance': 'UNKNOWN',
    'next': 'D actual selected caller/complete cost first; assist exact first typing error when supplied'
}
(here / 'manifest.json').write_text(json.dumps(manifest, ensure_ascii=False, indent=2) + '\n', encoding='utf-8')
(here / 'status.json').write_text(json.dumps({k: manifest[k] for k in
    ['checked_utc', 'first_tool_utc', 'bound_utc', 'common_deadline_utc', 'state', 'Lean', 'CI', 'performance', 'next']}, ensure_ascii=False, indent=2) + '\n', encoding='utf-8')
print(json.dumps({'ready_utc': now.isoformat(), 'proof_files': {k: v for k, v in items.items() if k.endswith('.inc')}, 'roots': len(roots)}, ensure_ascii=False))
