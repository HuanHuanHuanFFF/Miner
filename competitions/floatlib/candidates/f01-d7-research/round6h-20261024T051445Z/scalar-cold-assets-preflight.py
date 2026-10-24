"""Read-only source-capacity/proof-seam study; writes no Kernel or candidate."""
from pathlib import Path
import hashlib
import json

HERE = Path(__file__).resolve().parent
CANDIDATES = HERE.parents[1]


def sha(raw):
    return hashlib.sha256(raw).hexdigest()


def block(raw, start, end):
    assert raw.count(start) == raw.count(end) == 1
    lo = raw.index(start)
    hi = raw.index(end, lo) + len(end)
    return lo, hi, raw[lo:hi]


def main():
    base = (CANDIDATES / 'f01-d11-bmm-combined-classifier/Kernel.lean').read_bytes()
    old = (CANDIDATES / 'f01-d7-scalar-nan-select/Kernel.lean').read_bytes()
    assert sha(base) == '6c2d394dd34e8854d0d44d5d6605c194ecb27c152a1768d236481fc03fa4277d'
    assert sha(old) == '4a30c99f8230aae6d1b0cd238d1a6b1c9ac0aac0c448ca67d3005d3a6d00d528'
    tlo, thi, tuned = block(base, b'namespace TunedAdd\n', b'end TunedAdd\n')
    _, _, nan = block(old, b'namespace DWordNaN\n', b'end DWordNaN\n')
    _, _, scalar = block(old, b'namespace ScalarNaN\n', b'end ScalarNaN\n')
    assert tuned.count(b'TunedAdd.') == 0
    outside = base[:tlo] + base[thi:]
    assert outside.count(b'TunedAdd.') == 2
    assert outside.count(b'else TunedAdd.add x y') == 1
    assert outside.count(b'exact TunedAdd.add_spec x y') == 1
    assert outside.count(b'else FastMul.mul x y') == 1
    assert outside.count(b'exact FastMul.mul_spec x y') == 2  # LowScale fallback plus nativeMul.
    scalar = scalar.replace(b'TunedAdd.add x y', b'ExecFloat.add x y').replace(
        b'TunedAdd.add_spec x y', b'ExecFloat.Proof.add_eq_spec x y')
    # Projection remains in memory. This has not been written as a candidate.
    projected = outside.replace(b'else TunedAdd.add x y', b'else ScalarNaN.add x y').replace(
        b'exact TunedAdd.add_spec x y', b'exact ScalarNaN.add_spec x y')
    native_lo = projected.index(b'@[inline] def nativeMul (x y : Binary32)')
    native_hi = projected.index(b'@[inline] def mul (x y : Binary32)', native_lo)
    native = projected[native_lo:native_hi]
    assert native.count(b'else FastMul.mul x y') == native.count(b'exact FastMul.mul_spec x y') == 1
    native = native.replace(b'else FastMul.mul x y', b'else ScalarNaN.mul x y').replace(
        b'exact FastMul.mul_spec x y', b'exact ScalarNaN.mul_spec x y')
    projected = projected[:native_lo] + native + projected[native_hi:]
    anchor = b'end R7Native\n'
    assert projected.count(anchor) == 1
    projected = projected.replace(anchor, anchor + b'\n' + nan + b'\n' + scalar + b'\n')
    assert len(projected) < 256000
    report = {'state': 'STATIC_SOURCE_PROJECTION_ONLY', 'base_sha256': sha(base), 'old_asset_sha256': sha(old),
              'runtime_candidate_written': False, 'new_mechanism': False,
              'mechanism': 'Conditional reuse of existing4a30 rawChoose/selected_add/selected_mul only after current native-result NaN guard; default add fallback becomes official ExecFloat.add to reclaim TunedAdd capacity.',
              'tuned_add': {'byte_interval': [tlo, thi], 'bytes': len(tuned), 'sha256': sha(tuned),
                            'external_qualified_references': 2},
              'reused_DWordNaN': {'bytes': len(nan), 'sha256': sha(nan)},
              'adapted_ScalarNaN': {'bytes': len(scalar), 'sha256': sha(scalar)},
              'in_memory_projection': {'bytes': len(projected), 'headroom': 256000-len(projected), 'sha256': sha(projected)},
              'proof_dependencies_in_current_source': ['FastMul.ofBits', 'NativeBridge.toModelExecMul', 'R7Native.toModelExecAdd'],
              'new_obligations': ['Exact current namespace/wiring elaboration and unchanged4a30 proof acceptance',
                                  'Original full statement/kernel replay/axiom/checksum/performance gate for complete source'],
              'no_new_false_domain_assumption': 'rawChoose=some provides its own selected-word premise. None retains certified generic fallback. No native-result-NaN to exp255 bridge is assumed.',
              'capacity_edit_control': 'R11 official-add-fallback exact full gate passed but whole1.00328806/p05negative; capacity saving is not a speed gain.',
              'actual_Lean': 'NOT_RUN', 'full_gate': 'NOT_RUN', 'performance_gain': 'UNKNOWN',
              'decision': 'WAIT_ACTUAL_MAINFULL: do not write runtime candidate until current caller feedback supports this investment.'}
    for dependency in report['proof_dependencies_in_current_source']:
        assert dependency.encode() in base
    out = HERE / 'scalar-cold-assets-preflight.json'
    out.write_text(json.dumps(report, indent=2) + '\n', encoding='utf-8')
    print(json.dumps(report, indent=2))


if __name__ == '__main__':
    main()
