"""Build the old-B2 native-mul proof probe; no Lean, CI, Git or network action."""
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
ROOTS = [
    'Submission.R24NativeMul.native_mul_toModel',
    'Submission.R24NativeMul.native_mul_finite_roundAt',
    'Submission.R24NativeMul.native_mul_exact_from_raw32_values',
]
sha = lambda b: hashlib.sha256(b).hexdigest()


def main():
    base = BASE.read_bytes()
    fragment_path = D / 'NativeMul.lean.inc'
    fragment = fragment_path.read_bytes()
    assert sha(base) == BASE_SHA
    assert sha(HELPER.read_bytes()) == HELPER_SHA
    assert b'\r' not in fragment
    source = base + b'\n' + fragment
    assert len(source) <= 256000
    assert source[:len(base)] == base
    assert source.count(b'import ContractTensor') == 1
    assert b'import ContractExact' not in source
    for forbidden in [b'sorry', b'axiom ', b'unsafe ', b'implemented_by', b'@[extern', b'native_decide']:
        assert forbidden not in fragment
    (D / 'Kernel.lean').write_bytes(source)
    digest = sha(source)
    manifest = {
        'candidate': D.name, 'candidate_file': 'Kernel.lean',
        'candidate_sha256': digest, 'candidate_bytes': len(source),
        'created_at_utc': datetime.now(timezone.utc).isoformat(),
        'validation_mode': 'statement-only', 'diagnostic_only': True,
        'diagnostic_timeout_seconds': 180,
        'proof_status': 'NOT_RUN_NATIVE64_MODEL_FINITE_REAL_EXACT_BRIDGE',
        'performance': 'NOT_RUN_NO_CHANGED_PUBLIC_ENDPOINTS',
        'formal_submission': 'NOT_SUBMITTED', 'official_submission_inherited': False,
        'helper_audit_module': HELPER.name,
        'helper_audit_module_path': 'f01-d7-research/round9h-20261026T194639Z/development-helper-audit-v8.py',
        'helper_audit_module_sha256': HELPER_SHA,
        'explicit_helper_audit': ROOTS, 'helper_audit_required_endpoints': ROOTS,
        'helper_audit_expected_count': len(ROOTS), 'helper_audit_source_sha256': digest,
        'diagnostic_evaluations': [],
        'runtime_prefix': {'path': BASE.relative_to(R).as_posix(), 'sha256': BASE_SHA,
                           'bytes': len(base), 'byte_identical': True},
        'components': [{'path': fragment_path.relative_to(R).as_posix(),
                        'sha256': sha(fragment), 'bytes': len(fragment)}],
        'scope': 'Portable old ContractTensor/B2 helper. Actual native Float64 MUL to generic Model.mul, then proven output finiteness/roundAt under an input-value bound, then exact multiplication of native values corresponding to finite raw binary32 words. All four B2 public endpoints remain byte-identical.',
        'reused_semantic_interface': 'R2W01c.NativeBridge.modelMulFinite in unchanged retained B2 prefix is polymorphic in FloatFormat and includes signed-zero cases. Only the original existing Float32 wrapper was width-specific.',
        'exact_root_premises': 'Native x,y finite; raw32 a,b finite; Model real values of native x,y equal the exact raw32 values. No output-finiteness, product-exactness, rounding-cell, or opaque-cast correctness premise.',
        'missing': ['New helper not compiled or axiom-audited yet',
                    'No definition or proof of raw32-to-Float widening is included; compose only with a separately verified finite/value bridge',
                    'No bound for an accumulated Float64 fold',
                    'No new-track kernel, benchmark, whole-model gain or formal submission'],
        'shared_deadline_utc': '2026-10-29T03:38:56Z', 'CI_owner': 'D',
        'local_Lean': False,
    }
    (D / 'manifest.json').write_text(json.dumps(manifest, ensure_ascii=False, indent=2) + '\n', encoding='utf8')
    print(json.dumps({'candidate': D.name, 'sha256': digest, 'bytes': len(source),
                      'fragment_sha256': sha(fragment), 'roots': ROOTS}))


if __name__ == '__main__':
    main()
