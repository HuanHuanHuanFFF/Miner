"""Directed outer-guard/zero tests for the finite band model, no Lean build."""
from pathlib import Path
from datetime import datetime, timezone
import hashlib
import importlib.util
import json
import sys

sys.dont_write_bytecode = True
HERE = Path(__file__).resolve().parent
C = HERE.parent / 'board-frontier'


def load(path, name):
    spec = importlib.util.spec_from_file_location(name, path)
    m = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(m)
    return m


f = load(C / 'norm_frontier.py', 'r27_band_guard_formula')
word = load(HERE / 'band_full_model_census_v3.py', 'r27_band_guard_words')


def prepared(words):
    fields = [f.fields(w) for w in words]
    nz = [(i, s, m, e) for i, (s, m, e) in enumerate(fields) if m]
    low = min((e for _, _, _, e in nz), default=0)
    high = max((e for _, _, _, e in nz), default=low)
    return nz, low, high


def candidate(xs, ws, bias, shipped):
    n = len(xs)
    if len(ws) != n or n > 1 << 20 or any(((w >> 23) & 255) == 255 for w in xs+ws+[bias]):
        return shipped(), 'outer_shape_or_finite_fallback'
    xn, xl, xh = prepared(xs)
    wn, wl, wh = prepared(ws)
    sb, mb, ib = f.fields(bias)
    base = min(xl+wl, ib+126) if mb else xl+wl
    high = max(xh+wh, ib+126) if mb else xh+wh
    if wh-wl > 6 or high-base > 58:
        return shipped(), 'outer_range_fallback'
    wf = [0] * n
    for i, s, m, e in wn:
        wf[i] = s * (m << (e-wl))
    groups = {}
    for i, s, m, e in xn:
        groups.setdefault((e-xl)//4, []).append((i, s*(m << ((e-xl)%4))))
    lo, hi = 0, 0
    for band, entries in groups.items():
        gl, gh = 0, 0
        for begin in range(0, len(entries), 64):
            products = [a*wf[i] for i, a in entries[begin:begin+64]]
            assert sum(map(abs, products)) < 1 << 63
            q = sum(products) & word.MASK64
            gl, gh = word.merge64(gl, gh, q)
        sl, sh = word.shift128(gl, gh, 4*band)
        lo, hi = word.add128(lo, hi, sl, sh)
    body = word.signed128(lo, hi)
    shift = ib+149-base
    assert mb == 0 or shift >= 23
    total = (body << (xl+wl-base)) + sb*(mb << max(0, shift))
    assert -(1 << 127) <= total < 1 << 127
    if total == 0:
        return shipped(), 'exact_zero_fallback'
    return f.round_ratio(total, 1, base-298), 'single_round'


def main():
    cases = [
        ('one_minus_one_plus_minsubnormal', [0x3f800000, 0xbf800000], [0x3f800000]*2, 1, 1, 'outer_range_fallback'),
        ('negative_zero_callback', [0x80000000], [0x3f800000], 0x80000000, 0x80000000, 'exact_zero_fallback'),
        ('nonzero_cancellation_callback', [0x3f800000, 0xbf800000], [0x3f800000]*2, 0, 0, 'exact_zero_fallback'),
        ('YL_bias_rebase_23bit_boundary', [0x3f800000], [0x3f800000], 0x3a800000, 0x3f802000, 'single_round'),
        ('two_minsubnormals', [1], [0x3f800000], 1, 2, 'single_round'),
        ('nonfinite_callback_identity', [0x7f800000], [0x3f800000], 0, 0x7fc00011, 'outer_shape_or_finite_fallback'),
        ('weight_span7_fallback', [0x3f800000]*2, [(120<<23)|1, (127<<23)|1], 0, None, 'outer_range_fallback'),
        ('wide_span58_edge', [(100<<23)|1, (158<<23)|1], [0x3f800000]*2, 0, None, 'single_round'),
        ('wide_span59_fallback', [(100<<23)|1, (159<<23)|1], [0x3f800000]*2, 0, None, 'outer_range_fallback')
    ]
    rows = []
    for name, xs, ws, bias, expected, branch in cases:
        if expected is None:
            total = sum(f.key(a)*f.key(b) for a, b in zip(xs, ws)) + (f.key(bias) << 149)
            expected = f.round_ratio(total, 1, -298)
        calls = []
        def shipped():
            calls.append(True)
            return expected
        actual, observed = candidate(xs, ws, bias, shipped)
        assert actual == expected and observed == branch
        assert len(calls) == int(branch != 'single_round')
        rows.append({'name': name, 'actual_word': actual, 'expected_word': expected,
                     'branch': observed, 'original_callback_calls': len(calls)})
    # This counterexample is to a proposed simplification, not the guarded model.
    broken_clipped_bias = f.round_ratio(1, 1, -46)
    assert broken_clipped_bias == 679477248 and broken_clipped_bias != 1
    assert (1 << 20)+1 > 1 << 20
    # A zero shift needs its own arm: machine shifts mask 64 to zero.
    lo, hi = 3, 5
    actual = word.shift128(lo, hi, 0)
    broken = (lo, (hi | lo))
    assert actual == (3, 5) and broken != actual
    result = {'at_utc': datetime.now(timezone.utc).isoformat(),
              'state': 'DIRECTED_FINITE_OUTER_GUARD_AND_CALLBACK_TESTS', 'cases': rows,
              'negative_controls': {'bias_shift_clipped_to_zero': broken_clipped_bias,
                                    'missing_zero_shift_arm': {'correct': actual, 'incorrect': broken}},
              'bounds': {'reject_n_above': 1048576, 'max_weight_span': 6, 'max_terminal_range': 58},
              'limitations': ['Negative-zero and nonfinite expected values are supplied callback identities; this checks preservation, not a proof of FloatLib special-value semantics.',
                              'No Lean/native execution; the general partition, guards and endpoint proof remain outstanding.'],
              'source_hashes': {p.name: hashlib.sha256(p.read_bytes()).hexdigest() for p in
                               (Path(__file__), HERE/'band_full_model_census_v3.py', C/'norm_frontier.py')}}
    (HERE/'band-guard-counterexamples.json').write_text(json.dumps(result, indent=2), encoding='utf8')
    print(json.dumps({'cases': len(rows), 'negative_controls': result['negative_controls']}))


if __name__ == '__main__':
    main()
