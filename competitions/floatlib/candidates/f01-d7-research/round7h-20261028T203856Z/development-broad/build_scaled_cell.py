"""Old ContractTensor scoped mathematical certificate; no build, CI or Git."""
from pathlib import Path
import hashlib
import json
import re

HERE = Path(__file__).resolve().parent
ROOT = next(p for p in HERE.parents if (p / 'competitions/floatlib/pins.json').is_file())
BASE = ROOT / 'competitions/floatlib/candidates/f01-r15-dev-packed-b2-1/Kernel.lean'
HELPER = ROOT / 'competitions/floatlib/candidates/f01-d7-research/round9h-20261026T194639Z/development-helper-audit-v8.py'
CAND = ROOT / 'competitions/floatlib/candidates/f01-r24-dev-broad-scaled-cell1'
PARTS = [HERE / p for p in ('CellPrimitive-v2.lean.inc', 'ScaledCell.lean.inc', 'ScaledWord128.lean.inc')]
sha = lambda p: hashlib.sha256(p.read_bytes()).hexdigest()


def main():
    assert sha(BASE) == '622d8394a7127e93dcaf992c62c6dfcff7208d212738409a5e34525dfafd1a58'
    assert sha(PARTS[0]) == '78bef6ff5b493648c3be18faf0b194380fbf7c7585591b15b7c587caec7d1819'
    assert sha(HELPER) == '5b58eece211bd9cdaa270fc82bef624a5974c7d056732e19f54547c0fe6ef975'
    raw = BASE.read_bytes()
    for p in PARTS:
        fragment = p.read_bytes()
        assert not re.search(rb'\b(?:sorry|admit|native_decide|axiom|unsafe)\b', fragment)
        assert not re.search(rb'^\s*import\b', fragment, re.M)
        raw += b'\n' + fragment
    assert len(raw) < 256000 and b'ContractExact' not in raw
    names = ['Submission.' + n + '_spec' for n in ('add', 'mul', 'sum', 'bmm')]
    names += ['Submission.R24CellPrimitive.' + n for n in (
        'quotient_strict_midpoint', 'quotient_even_closed_midpoint', 'strictCell_sound',
        'normal_ratio_nat_bounds', 'normal_ratio_log23', 'native32_strict_cell', 'normalStrictCell_sound')]
    names += ['Submission.R24ScaledCell.' + n for n in ('normalize_strict', 'native32_scaled_strict')]
    names += ['Submission.R24ScaledWord128.' + n for n in
              ('midpointWords_exact', 'compare_lt', 'compare_gt', 'check_sound')]
    CAND.mkdir(exist_ok=True)
    (CAND / 'Kernel.lean').write_bytes(raw)
    source = sha(CAND / 'Kernel.lean')
    manifest = {
        'candidate': CAND.name, 'candidate_file': 'Kernel.lean', 'candidate_sha256': source,
        'candidate_bytes': len(raw), 'validation_mode': 'statement-only', 'diagnostic_only': True,
        'diagnostic_timeout_seconds': 600, 'proof_status': 'NOT_RUN_RAW_SCALED_CELL_TO_ACTUAL_NATIVE32',
        'performance': 'NO_NEW_PERFORMANCE_CLAIM', 'formal_submission': 'NOT_SUBMITTED',
        'official_submission_inherited': False,
        'helper_audit_module': HELPER.name,
        'helper_audit_module_path': HELPER.relative_to(ROOT / 'competitions/floatlib/candidates').as_posix(),
        'helper_audit_module_sha256': sha(HELPER),
        'explicit_helper_audit': names, 'helper_audit_required_endpoints': names,
        'helper_audit_expected_count': len(names), 'helper_audit_source_sha256': source,
        'diagnostic_evaluations': [],
        'runtime_prefix': {'path': BASE.relative_to(ROOT).as_posix(), 'sha256': sha(BASE),
                           'bytes': BASE.stat().st_size, 'byte_identical': True},
        'components': [{'path': p.relative_to(ROOT).as_posix(), 'sha256': sha(p),
                        'bytes': p.stat().st_size} for p in PARTS],
        'scope': 'Generic old ContractTensor/B2 only. Four public callbacks byte identical. Concrete raw128 numerator/word38 denominator checker keeps source and candidate exponents separate and concludes actual NativeBinary32.roundRatScaled/mkBits. Logical normalization only occurs in proof; narrow public comparator Nat fallback is guarded out. No new target Kernel, arbitrary native equation, abstract hcell or runtime speed claim.',
    }
    (CAND / 'manifest.json').write_text(json.dumps(manifest, indent=2) + '\n', encoding='utf-8')
    print(json.dumps({'candidate': CAND.name, 'sha256': source, 'bytes': len(raw),
                      'roots': len(names), 'manifest_sha256': sha(CAND / 'manifest.json')}, indent=2))


if __name__ == '__main__':
    main()
