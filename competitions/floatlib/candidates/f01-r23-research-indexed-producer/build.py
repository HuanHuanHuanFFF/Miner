from pathlib import Path
import hashlib, json
from datetime import datetime, timezone

ROOT = Path(__file__).resolve().parents[4]
HERE = Path(__file__).resolve().parent
BASE = ROOT / 'competitions/floatlib/candidates/f01-r22-dev-indexed8-cost1/Kernel.lean'
AUDIT = ROOT / 'competitions/floatlib/candidates/f01-d7-research/round9h-20261026T194639Z/development-helper-audit-v8.py'
sha = lambda b: hashlib.sha256(b).hexdigest()
base = BASE.read_bytes()
assert sha(base) == '8e27baf70ce7e3f10b669cc9f59d66d5fffaa17ee3dc6df934f3229139a5b0dd'
fragment = (HERE / 'Producer.lean.inc').read_bytes()
raw = base + fragment
assert len(raw) <= 256000
assert sha(AUDIT.read_bytes()) == '5b58eece211bd9cdaa270fc82bef624a5974c7d056732e19f54547c0fe6ef975'
(HERE / 'Kernel.lean').write_bytes(raw)
roots = ['Submission.R23IndexedProducer.' + x for x in
         ['point_pair', 'packRow_prefix', 'packB_prefix', 'packB_get', 'packB_read']]
manifest = dict(candidate=HERE.name, candidate_file='Kernel.lean', candidate_sha256=sha(raw),
    candidate_bytes=len(raw), created_at_utc=datetime.now(timezone.utc).isoformat(),
    validation_mode='statement-only', diagnostic_only=True, diagnostic_timeout_seconds=600,
    proof_status='NOT_RUN_ACTUAL_PACKB_PRODUCER_READER_BRIDGE', performance='NO_NEW_PERFORMANCE_CLAIM',
    formal_submission='NOT_SUBMITTED', official_submission_inherited=False,
    helper_audit_module='development-helper-audit-v8.py',
    helper_audit_module_path=AUDIT.relative_to(ROOT / 'competitions/floatlib/candidates').as_posix(),
    helper_audit_module_sha256=sha(AUDIT.read_bytes()), explicit_helper_audit=roots,
    helper_audit_required_endpoints=roots, helper_audit_expected_count=len(roots),
    helper_audit_source_sha256=sha(raw), diagnostic_evaluations=[],
    runtime_prefix=dict(path=BASE.relative_to(ROOT).as_posix(), sha256=sha(base), bytes=len(base), byte_identical=True),
    producer_fragment_sha256=sha(fragment),
    scope='Exact indexed8 cost1 runtime prefix, actual packRow/packB content invariant, selected valid lanes and explicit odd-padding branch. Public four remain B2. No public indexed8 BMM closure or adoption.')
(HERE / 'manifest.json').write_text(json.dumps(manifest, indent=2) + '\n', encoding='utf-8')
print(json.dumps(dict(kernel_sha256=sha(raw), bytes=len(raw), roots=roots)))
