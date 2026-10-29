"""Portable old ContractTensor helper only; no build/Git/CI operations."""
from pathlib import Path
import hashlib
import json
import re

HERE = Path(__file__).resolve().parent
ROOT = next(p for p in HERE.parents if (p / 'competitions/floatlib/pins.json').is_file())
BASE = ROOT / 'competitions/floatlib/candidates/f01-r15-dev-packed-b2-1/Kernel.lean'
CELL = HERE / 'CellPrimitive-v2.lean.inc'
GAP = HERE / 'WordGap128.lean.inc'
CAND = ROOT / 'competitions/floatlib/candidates/f01-r24-dev-broad-word-gap1281'
HELPER = ROOT / 'competitions/floatlib/candidates/f01-d7-research/round9h-20261026T194639Z/development-helper-audit-v8.py'
sha = lambda p: hashlib.sha256(p.read_bytes()).hexdigest()


def main():
    assert sha(BASE) == '622d8394a7127e93dcaf992c62c6dfcff7208d212738409a5e34525dfafd1a58'
    assert sha(CELL) == '78bef6ff5b493648c3be18faf0b194380fbf7c7585591b15b7c587caec7d1819'
    assert sha(HELPER) == '5b58eece211bd9cdaa270fc82bef624a5974c7d056732e19f54547c0fe6ef975'
    raw = BASE.read_bytes() + b'\n' + CELL.read_bytes() + b'\n' + GAP.read_bytes()
    assert len(raw) < 256000
    for fragment in (CELL, GAP):
        assert not re.search(rb'\b(?:sorry|admit|native_decide|axiom|unsafe)\b', fragment.read_bytes())
        assert not re.search(rb'^\s*import\b', fragment.read_bytes(), re.M)
    names = ['Submission.' + n + '_spec' for n in ('add', 'mul', 'sum', 'bmm')]
    names += ['Submission.R24CellPrimitive.' + n for n in (
        'quotient_strict_midpoint', 'quotient_even_closed_midpoint', 'strictCell_sound',
        'normal_ratio_nat_bounds', 'normal_ratio_log23', 'native32_strict_cell',
        'normalStrictCell_sound')]
    names += ['Submission.R24WordGap128.' + n for n in (
        'gap_toNat_cases', 'check_midpoint_bounds', 'check_sound', 'normalCheck_sound')]
    CAND.mkdir(exist_ok=True)
    (CAND / 'Kernel.lean').write_bytes(raw)
    source = sha(CAND / 'Kernel.lean')
    manifest = {
        'candidate': CAND.name, 'candidate_file': 'Kernel.lean',
        'candidate_sha256': source, 'candidate_bytes': len(raw),
        'validation_mode': 'statement-only', 'diagnostic_only': True,
        'diagnostic_timeout_seconds': 600,
        'proof_status': 'NOT_RUN_FIXED_WORD_GUARD_TO_REAL_RNE_AND_NORMAL_NATIVE32',
        'performance': 'NO_NEW_PERFORMANCE_CLAIM', 'formal_submission': 'NOT_SUBMITTED',
        'official_submission_inherited': False,
        'helper_audit_module': HELPER.name,
        'helper_audit_module_path': HELPER.relative_to(ROOT / 'competitions/floatlib/candidates').as_posix(),
        'helper_audit_module_sha256': sha(HELPER),
        'explicit_helper_audit': names, 'helper_audit_required_endpoints': names,
        'helper_audit_expected_count': len(names), 'helper_audit_source_sha256': source,
        'diagnostic_evaluations': [],
        'runtime_prefix': {'path': BASE.relative_to(ROOT).as_posix(),
                           'sha256': sha(BASE), 'bytes': BASE.stat().st_size, 'byte_identical': True},
        'components': [{'path': p.relative_to(ROOT).as_posix(), 'sha256': sha(p),
                        'bytes': p.stat().st_size} for p in (CELL, GAP)],
        'scope': 'Old ContractTensor/B2 only. Unchanged four public callbacks. Arbitrary rounded guess certified by an exact 64x64-to-128 product and ordered difference; native-word guards conclude actual Nat RNE and actual normal-interior NativeBinary32.roundRatScaled/mkBits. No floating guess accuracy premise, new-track implementation or cost claim.',
    }
    (CAND / 'manifest.json').write_text(json.dumps(manifest, indent=2) + '\n', encoding='utf-8')
    print(json.dumps({'candidate': CAND.name, 'sha256': source, 'bytes': len(raw),
                      'roots': len(names), 'manifest_sha256': sha(CAND / 'manifest.json')}, indent=2))


if __name__ == '__main__':
    main()
