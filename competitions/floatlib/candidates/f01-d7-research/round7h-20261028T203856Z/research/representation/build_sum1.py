"""Package the actual Native64 fold helper. Does not invoke Lean, CI or timing."""
from pathlib import Path
from datetime import datetime, timezone
import ast
import hashlib
import json
import re

HERE = Path(__file__).resolve().parent
ROOT = next(p for p in HERE.parents if (p / 'AGENTS.md').is_file())
CANDIDATES = ROOT / 'competitions/floatlib/candidates'
sha = lambda b: hashlib.sha256(b).hexdigest()
base = CANDIDATES / 'f01-r15-dev-packed-b2-1/Kernel.lean'
raw = base.read_bytes()
assert sha(raw) == '622d8394a7127e93dcaf992c62c6dfcff7208d212738409a5e34525dfafd1a58'
paths = [HERE / 'NativeSumEnclosure.lean.inc', HERE.parent / 'controller/StrictEnclosure.lean.inc']
fragments = [p.read_bytes() for p in paths]
blob = raw + b'\n' + b'\n'.join(fragments)
assert len(blob) <= 256000
assert blob[:len(raw)] == raw
for fragment in fragments:
    assert b'import ' not in fragment
    assert re.search(rb'(?m)^\s*(?:axiom|unsafe)\b', fragment) is None
    for forbidden in (b'sorry', b'implemented_by', b'@[extern', b'native_decide'):
        assert forbidden not in fragment, forbidden
out = CANDIDATES / 'f01-r24-research-representation-sum1'
out.mkdir(exist_ok=True)
(out / 'Kernel.lean').write_bytes(blob)
helper = 'f01-d7-research/round9h-20261026T194639Z/development-helper-audit-v8.py'
roots = ['Submission.R24RepresentationSum.' + n for n in
         ['native_add_finite_real', 'round_grid', 'round_error_power', 'loop_invariant',
          'sum_enclosure', 'actual_sum_enclosure']]
roots += ['Submission.R24StrictEnclosure.' + n for n in
          ['strict_lower_pullback', 'strict_upper_pullback', 'strict_enclosure_of_rounded_bounds']]
manifest = dict(candidate=out.name, candidate_file='Kernel.lean', candidate_sha256=sha(blob),
    candidate_bytes=len(blob), created_at_utc=datetime.now(timezone.utc).isoformat(),
    validation_mode='statement-only', diagnostic_only=True, diagnostic_timeout_seconds=180,
    proof_status='NOT_RUN', performance='NOT_RUN', formal_submission='NOT_SUBMITTED',
    official_submission_inherited=False, helper_audit_module='development-helper-audit-v8.py',
    helper_audit_module_path=helper, helper_audit_module_sha256=sha((CANDIDATES / helper).read_bytes()),
    explicit_helper_audit=roots, helper_audit_required_endpoints=roots,
    helper_audit_expected_count=len(roots), helper_audit_source_sha256=sha(blob),
    diagnostic_evaluations=[], runtime_base_sha256=sha(raw), runtime_base_prefix_bytes=len(raw),
    byte_identical_base_prefix_verified=True,
    components=[dict(path=p.relative_to(ROOT).as_posix(), sha256=sha(b), bytes=len(b))
                for p, b in zip(paths, fragments)],
    public_endpoints='All four B2 public endpoints and proofs are unchanged byte-for-byte in the complete prefix.',
    scope='Portable ContractTensor/B2 mathematics helper: actual binary64 Float.add List fold, finite prefix and RNE error bound; three unchanged controller strict-pullback helpers share the audit.',
    semantic_endpoint='For -250<=k<=256, L<=30, length<=2^L, finite |x|<2^k: actual Float.add fold from +0 remains finite and differs from exact real sum by <=2^(k+2L-53).',
    limitations=['NOT_RUN', 'No ContractExact kernel or benchmark', 'No widening or multiplication dependency',
                 'No raw32 midpoint construction or final word-cell theorem', 'No performance/adoption claim'],
    local_Lean=False, CI_owner='D',
    window_start_utc='2026-10-28T20:38:56Z', shared_deadline_utc='2026-10-29T03:38:56Z',
    actual_phase_first_utc='2026-10-28T22:57:09Z',
    source_of_authorization='Parent R24 portable mathematics helper task; old public endpoints remain unchanged')
(out / 'manifest.json').write_text(json.dumps(manifest, indent=2) + '\n', encoding='utf-8')
receipt = dict(manifest=manifest, builder_sha256=sha(Path(__file__).read_bytes()),
    checked_at_utc=datetime.now(timezone.utc).isoformat(),
    static_checks=['B2 exact SHA and complete byte-identical prefix', '256000 byte cap',
                   'No new import or added forbidden proof/source construct',
                   'v8 candidates-relative path/hash; components root-relative paths/hashes',
                   'statement-only timeout exactly180', 'original R24 start/deadline'],
    Lean_status='NOT_RUN', execution_cost='UNKNOWN', tokens='UNKNOWN', cached_input_tokens='UNKNOWN',
    capacity_gap='No local Lean/native compilation allowed; D owns remote verification; no nested agents',
    preserved_preflight_failure='First builder scan matched the word axiom inside the unchanged controller explanatory comment; declaration-aware scan repaired, no Lean source mutation for this issue.')
(HERE / 'sum1-source-receipt.json').write_text(json.dumps(receipt, indent=2) + '\n', encoding='utf-8')
ast.parse(Path(__file__).read_text(encoding='utf-8'))
print(json.dumps(dict(candidate=out.name, sha256=sha(blob), bytes=len(blob),
    components=manifest['components'], roots=roots, proof_status='NOT_RUN')))
