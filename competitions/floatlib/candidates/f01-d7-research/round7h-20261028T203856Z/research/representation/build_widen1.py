"""Package a portable old-contract helper; no Lean, CI or benchmark is run."""
from pathlib import Path
from datetime import datetime, timezone
import hashlib, json, ast

HERE = Path(__file__).resolve().parent
ROOT = next(p for p in HERE.parents if (p / 'AGENTS.md').is_file())
CANDIDATES = ROOT / 'competitions/floatlib/candidates'
sha = lambda b: hashlib.sha256(b).hexdigest()
base = CANDIDATES / 'f01-r15-dev-packed-b2-1/Kernel.lean'
raw = base.read_bytes()
assert sha(raw) == '622d8394a7127e93dcaf992c62c6dfcff7208d212738409a5e34525dfafd1a58'
fragment_path = HERE / 'WidenNormal.lean.inc'
fragment = fragment_path.read_bytes()
blob = raw + b'\n' + fragment
assert len(blob) <= 256000
assert blob[:len(raw)] == raw
assert fragment.count(b'import ') == 0
for forbidden in (b'sorry', b'axiom ', b'unsafe ', b'implemented_by', b'@[extern', b'native_decide'):
    assert forbidden not in fragment, forbidden
out = CANDIDATES / 'f01-r24-research-representation-widen1'
out.mkdir(exist_ok=True)
(out / 'Kernel.lean').write_bytes(blob)
helper = 'f01-d7-research/round9h-20261026T194639Z/development-helper-audit-v8.py'
helper_path = CANDIDATES / helper
roots = ['Submission.R24RepresentationWiden.' + n for n in
         ['normal_decode', 'native_model', 'native_finite', 'actual_native_value', 'signed_zero_bits']]
manifest = dict(candidate=out.name, candidate_file='Kernel.lean', candidate_sha256=sha(blob),
    candidate_bytes=len(blob), created_at_utc=datetime.now(timezone.utc).isoformat(),
    validation_mode='statement-only', diagnostic_only=True, diagnostic_timeout_seconds=180,
    proof_status='NOT_RUN', performance='NOT_RUN', formal_submission='NOT_SUBMITTED',
    official_submission_inherited=False, helper_audit_module='development-helper-audit-v8.py',
    helper_audit_module_path=helper, helper_audit_module_sha256=sha(helper_path.read_bytes()),
    explicit_helper_audit=roots, helper_audit_required_endpoints=roots,
    helper_audit_expected_count=len(roots), helper_audit_source_sha256=sha(blob),
    diagnostic_evaluations=[], runtime_base_sha256=sha(raw), runtime_base_prefix_bytes=len(raw),
    byte_identical_base_prefix_verified=True, fragment_sha256=sha(fragment), fragment_bytes=len(fragment),
    components=[dict(path=fragment_path.relative_to(ROOT).as_posix(), sha256=sha(fragment), bytes=len(fragment))],
    public_endpoints='All four B2 public endpoints and proofs are unchanged byte-for-byte in the complete prefix.',
    scope='Portable ContractTensor/B2 helper only: actual Float.ofBits binary64 native model/real-value and finite bridge for binary32 normals or signed zero. Nonzero subnormals and exponent-255 words are excluded.',
    semantic_endpoint='Model.toReal (Binary.toModel (Binary.ofFloat (value u))) = Model.toReal (Model.ofUInt32 u), under Domain u',
    fallback_note='value alone is not a full-finite decoder; a future caller must check Domain and retain its original path on misses.',
    local_Lean=False, CI_owner='D', source_of_authorization='Parent R24 portable mathematics helper task; no ContractExact implementation or benchmark')
(out / 'manifest.json').write_text(json.dumps(manifest, indent=2) + '\n', encoding='utf-8')
receipt = dict(manifest=manifest, builder_sha256=sha(Path(__file__).read_bytes()),
    checked_at_utc=datetime.now(timezone.utc).isoformat(),
    static_checks=['base exact SHA', 'full byte-identical prefix', '256000 byte cap',
                   'no new import', 'no added forbidden proof/source construct', 'v8 relative path/hash',
                   'statement-only timeout exactly180'],
    Lean_status='NOT_RUN', numeric_oracle='NOT_RUN_NO_DUPLICATE_RANDOM_BATCH',
    scope_boundary='No field theorem alone is claimed as a value theorem; actual_native_value composes into the actual native64 model.')
(HERE / 'widen1-source-receipt.json').write_text(json.dumps(receipt, indent=2) + '\n', encoding='utf-8')
ast.parse(Path(__file__).read_text(encoding='utf-8'))
print(json.dumps({'candidate':out.name,'sha256':sha(blob),'bytes':len(blob),
                  'fragment_sha256':sha(fragment),'fragment_bytes':len(fragment),'roots':roots,
                  'diagnostic_timeout_seconds':180,'proof_status':'NOT_RUN'}))
