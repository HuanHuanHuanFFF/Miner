"""Checked affine word operation and exact fallback; old B2 public endpoints."""
from pathlib import Path
import hashlib
import json
import re

HERE = Path(__file__).resolve().parent
ROOT = next(p for p in HERE.parents if (p / 'competitions/floatlib/pins.json').is_file())
BASE = ROOT / 'competitions/floatlib/candidates/f01-r15-dev-packed-b2-1/Kernel.lean'
HELPER = ROOT / 'competitions/floatlib/candidates/f01-d7-research/round9h-20261026T194639Z/development-helper-audit-v8.py'
CAND = ROOT / 'competitions/floatlib/candidates/f01-r24-dev-broad-affine-scaled1'
sha = lambda p: hashlib.sha256(p.read_bytes()).hexdigest()


def main():
    assert sha(BASE) == '622d8394a7127e93dcaf992c62c6dfcff7208d212738409a5e34525dfafd1a58'
    assert sha(HELPER) == '5b58eece211bd9cdaa270fc82bef624a5974c7d056732e19f54547c0fe6ef975'
    parent = HERE / 'CellPrimitive-v2.lean.inc'
    assert sha(parent) == '78bef6ff5b493648c3be18faf0b194380fbf7c7585591b15b7c587caec7d1819'
    frozen = parent.read_bytes()
    chunks, selections = [], []
    for start, end in [('theorem quotient_strict_midpoint', 'theorem quotient_even_closed_midpoint'),
                       ('theorem normal_ratio_nat_bounds', 'theorem normal_ratio_log23')]:
        a = frozen.index(start.encode())
        b = frozen.index(end.encode(), a)
        chunk = frozen[a:b]
        chunks.append(chunk)
        selections.append({'start_declaration': start, 'start_byte': a, 'end_byte_exclusive': b,
                           'sha256': hashlib.sha256(chunk).hexdigest(), 'bytes': len(chunk)})
    dependency = (b'namespace Submission.R24CellPrimitive\n'
                  b'open FloatLib.Floats FloatLib.Floats.Formats.BinaryInterchange\n\n' +
                  b'\n'.join(chunks) + b'end Submission.R24CellPrimitive\n')
    dep = HERE / 'CellStrictDependencies.lean.inc'
    dep.write_bytes(dependency)
    parts = [dep] + [HERE / n for n in ('ScaledCell.lean.inc', 'ScaledWord128.lean.inc', 'AffineScaledWord128.lean.inc')]
    assert sha(parts[1]) == 'ccd159940f6d07bcd2f5187021a6da0c49eae0df2147d70c8ed9ec511d4e49bb'
    assert sha(parts[2]) == '4a44009121362742d1e4aae9a4f189055a225dc076a9f2c80f5766c84ecf6c19'
    raw = BASE.read_bytes()
    for p in parts:
        fragment = p.read_bytes()
        assert not re.search(rb'\b(?:sorry|admit|native_decide|axiom|unsafe)\b', fragment)
        assert not re.search(rb'^\s*import\b', fragment, re.M)
        raw += b'\n' + fragment
    assert len(raw) < 256000 and b'ContractExact' not in raw
    names = ['Submission.' + n + '_spec' for n in ('add', 'mul', 'sum', 'bmm')]
    names += ['Submission.R24CellPrimitive.' + n for n in ('quotient_strict_midpoint', 'normal_ratio_nat_bounds')]
    names += ['Submission.R24ScaledCell.' + n for n in ('normalize_strict', 'native32_scaled_strict')]
    names += ['Submission.R24ScaledWord128.' + n for n in ('midpointWords_exact', 'compare_lt', 'compare_gt', 'check_sound')]
    names += ['Submission.R24AffineScaledWord128.' + n for n in (
        'multiply_sound', 'combine_sound', 'affine_word_coefficient', 'coefficient_sign_abs',
        'scaledCheck_nonzero', 'attempt_sound', 'roundWithFallback_eq_reference')]
    CAND.mkdir(exist_ok=True)
    (CAND / 'Kernel.lean').write_bytes(raw)
    source = sha(CAND / 'Kernel.lean')
    manifest = {
        'candidate': CAND.name, 'candidate_file': 'Kernel.lean', 'candidate_sha256': source,
        'candidate_bytes': len(raw), 'validation_mode': 'statement-only', 'diagnostic_only': True,
        'diagnostic_timeout_seconds': 600, 'proof_status': 'NOT_RUN_COMPLETE_GENERIC_WORD_OPERATION_WITH_REAL_FALLBACK',
        'performance': 'NO_NEW_PERFORMANCE_CLAIM', 'formal_submission': 'NOT_SUBMITTED',
        'official_submission_inherited': False,
        'helper_audit_module': HELPER.name,
        'helper_audit_module_path': HELPER.relative_to(ROOT / 'competitions/floatlib/candidates').as_posix(),
        'helper_audit_module_sha256': sha(HELPER), 'explicit_helper_audit': names,
        'helper_audit_required_endpoints': names, 'helper_audit_expected_count': len(names),
        'helper_audit_source_sha256': source, 'diagnostic_evaluations': [],
        'runtime_prefix': {'path': BASE.relative_to(ROOT).as_posix(), 'sha256': sha(BASE),
                           'bytes': BASE.stat().st_size, 'byte_identical': True},
        'components': [{'path': p.relative_to(ROOT).as_posix(), 'sha256': sha(p), 'bytes': p.stat().st_size} for p in parts],
        'exact_dependency_extraction': {'parent_path': parent.relative_to(ROOT).as_posix(),
                                        'parent_sha256': sha(parent), 'selections': selections},
        'scope': 'Old ContractTensor only, exact B2 public callbacks. Complete generic operation computes signed(A*G+B) in checked words, certifies arbitrary mantissa/exponent against raw scaled value, and builds actual wide Nat NativeBinary32 reference only on rejection. Gain24/A104 fast guards, signed carry, zero/tie/boundary/exponent/failure fallback all retained. No new target Kernel or native guess accuracy premise; no runtime speed claim.',
    }
    (CAND / 'manifest.json').write_text(json.dumps(manifest, indent=2) + '\n', encoding='utf-8')
    print(json.dumps({'candidate': CAND.name, 'sha256': source, 'bytes': len(raw),
                      'roots': len(names), 'manifest_sha256': sha(CAND / 'manifest.json')}, indent=2))


if __name__ == '__main__':
    main()
