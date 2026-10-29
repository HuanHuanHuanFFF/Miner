"""Package one portable native Float.lt proof root. No Lean/CI/Git/network."""
from pathlib import Path
from datetime import datetime, timezone
import hashlib
import json

D = Path(__file__).resolve().parent
R = next(p for p in D.parents if (p / 'AGENTS.md').exists())
BASE = R / 'competitions/floatlib/candidates/f01-r15-dev-packed-b2-1/Kernel.lean'
HELPER = R / 'competitions/floatlib/candidates/f01-d7-research/round9h-20261026T194639Z/development-helper-audit-v8.py'
BASE_SHA = '622d8394a7127e93dcaf992c62c6dfcff7208d212738409a5e34525dfafd1a58'
HELPER_SHA = '5b58eece211bd9cdaa270fc82bef624a5974c7d056732e19f54547c0fe6ef975'
ROOTS = ['Submission.R24NativeCompare.native_lt_iff_real']
sha = lambda b: hashlib.sha256(b).hexdigest()


def main():
    base = BASE.read_bytes()
    component = D / 'NativeCompare.lean.inc'
    fragment = component.read_bytes()
    assert sha(base) == BASE_SHA and sha(HELPER.read_bytes()) == HELPER_SHA
    source = base + b'\n' + fragment
    assert len(source) <= 256000 and source[:len(base)] == base
    assert b'\r' not in fragment and source.count(b'import ContractTensor') == 1
    assert b'import ContractExact' not in source
    for forbidden in [b'sorry', b'axiom ', b'unsafe ', b'implemented_by', b'@[extern', b'native_decide']:
        assert forbidden not in fragment
    (D / 'Kernel.lean').write_bytes(source)
    digest = sha(source)
    manifest = {
        'candidate': D.name, 'candidate_file': 'Kernel.lean', 'candidate_sha256': digest,
        'candidate_bytes': len(source), 'created_at_utc': datetime.now(timezone.utc).isoformat(),
        'validation_mode': 'statement-only', 'diagnostic_only': True,
        'diagnostic_timeout_seconds': 180,
        'proof_status': 'NOT_RUN_ACTUAL_NATIVE64_STRICT_ORDER_BRIDGE',
        'performance': 'NOT_RUN_NO_CHANGED_PUBLIC_ENDPOINTS',
        'formal_submission': 'NOT_SUBMITTED', 'official_submission_inherited': False,
        'helper_audit_module': HELPER.name,
        'helper_audit_module_path': 'f01-d7-research/round9h-20261026T194639Z/development-helper-audit-v8.py',
        'helper_audit_module_sha256': HELPER_SHA, 'explicit_helper_audit': ROOTS,
        'helper_audit_required_endpoints': ROOTS, 'helper_audit_expected_count': 1,
        'helper_audit_source_sha256': digest, 'diagnostic_evaluations': [],
        'components': [{'path': component.relative_to(R).as_posix(), 'sha256': sha(fragment), 'bytes': len(fragment)}],
        'runtime_prefix': {'path': BASE.relative_to(R).as_posix(), 'sha256': BASE_SHA,
                           'bytes': len(base), 'byte_identical': True},
        'scope': 'One actual Float.lt=true iff strict real order root, for finite native binary64 inputs. Includes both signed zeros and finite subnormals. Old B2 public endpoints unchanged.',
        'proof_route': 'Native unpack comparison is lexicographic only on numerical canonical forms. Model.cexp_toDyadic? supplies exact decoded exponents; cexp_mono_abs with fltMonotoneExp proves the unequal-exponent order. Same-exponent mantissas, signs and zero cases finish the actual native Boolean bridge.',
        'missing': ['New source not compiled, replayed or axiom-audited',
                    'No combined midpoint/error checker implementation',
                    'No native caller/ASM/timing or whole-model speed claim'],
        'runtime_policy': 'No runtime Model.compare/totalOrder/ExecFloat.compare/raw-key algorithm is introduced. No new extern/unsafe/axiom or opaque cast correctness premise.',
        'window_start_utc': '2026-10-28T20:38:56Z',
        'shared_deadline_utc': '2026-10-29T03:38:56Z', 'CI_owner': 'D', 'local_Lean': False,
    }
    (D / 'manifest.json').write_text(json.dumps(manifest, ensure_ascii=False, indent=2) + '\n', encoding='utf-8')
    print(json.dumps({'candidate': D.name, 'kernel_sha256': digest, 'kernel_bytes': len(source),
                      'fragment_sha256': sha(fragment), 'fragment_bytes': len(fragment), 'roots': ROOTS}))


if __name__ == '__main__':
    main()
