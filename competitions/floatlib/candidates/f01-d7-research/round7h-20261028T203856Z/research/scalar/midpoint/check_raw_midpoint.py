"""Fixed actual-word field/sign/swap checks against independent neighbors.

No native execution, Lean, compiler, performance test, or old sample sweep.
The overflow neighbor used for the maximum finite cell is the virtual 2^128.
"""
from pathlib import Path
from fractions import Fraction as F
from datetime import datetime, timezone
import hashlib
import json
import re

HERE = Path(__file__).resolve().parent
ROOT = Path(__file__).resolve().parents[8]
ROUND = HERE.parents[2]

def sha(p):
    return hashlib.sha256(p.read_bytes()).hexdigest()

def p2(e):
    return F(1 << e) if e >= 0 else F(1, 1 << -e)

def value32(m):
    e, f = m >> 23, m & 0x7fffff
    assert m <= 0x7f800000
    return (f if e == 0 else (1 << 23) + f) * p2(-149 if e == 0 else e - 150)

def value64(w):
    s, e, f = w >> 63, (w >> 52) & 2047, w & ((1 << 52) - 1)
    assert e < 2047
    return (-1 if s else 1) * (f if e == 0 else (1 << 52) + f) * p2(-1074 if e == 0 else e - 1075)

def actual_views(q):
    magnitude = q & 0x7fffffff
    e = (magnitude >> 23) & 255
    f = magnitude & 0x7fffff
    base = ((e + 896) << 52) | (f << 29)
    below = base - (0x20000000 if magnitude == 0x00800000 else 0x10000000)
    above = base + 0x10000000
    negative = (q & 0x80000000) != 0
    lower = (above | 0x8000000000000000) if negative else below
    upper = (below | 0x8000000000000000) if negative else above
    return magnitude, e, f, base, lower, upper

def main():
    cases = []
    for e in [1, 2, 127, 254]:
        for f in [0, 1, 8388607]:
            for sign in [0, 1]:
                q = (sign << 31) | (e << 23) | f
                m, got_e, got_f, base, lower, upper = actual_views(q)
                assert got_e == (q >> 23) & 255 and got_f == q & 0x7fffff
                assert (m == 0x00800000) == (e == 1 and f == 0)
                assert base == ((e + 896) << 52) + (f << 29)
                center = value32(m)
                ref_lower = (value32(m - 1) + center) / 2
                ref_upper = (center + value32(m + 1)) / 2
                if sign:
                    ref_lower, ref_upper = -ref_upper, -ref_lower
                assert value64(lower) == ref_lower and value64(upper) == ref_upper
                assert value64(lower) < value64(upper)
                cases.append({'raw32': f'0x{q:08x}', 'lower_word': f'0x{lower:016x}',
                              'upper_word': f'0x{upper:016x}', 'e': e, 'f': f, 'negative': bool(sign)})
    excluded_fields = [0, 1, 0x7f800000, 0x7f800001, 0x7fffffff]
    for m in excluded_fields:
        for sign in [0, 1]:
            q = m | (sign << 31)
            mag, e, f, base, _, _ = actual_views(q)
            assert e == (q >> 23) & 255 and f == q & 0x7fffff
            assert (mag == 0x00800000) == (e == 1 and f == 0)
            assert base == ((e + 896) << 52) + (f << 29)
    runtime = ROUND / 'development-scalar/PortableF64Dot.lean.inc'
    source_text = runtime.read_text(encoding='utf-8')
    required = [
        'let magnitude := guess &&& 0x7fffffff',
        'let base := ((e.toUInt64 + 896) <<< 52) ||| ((magnitude &&& 0x7fffff).toUInt64 <<< 29)',
        'let lowerDelta : UInt64 := if magnitude == 0x00800000 then 0x20000000 else 0x10000000',
        'let negative := guess &&& 0x80000000 != 0',
        'let lower := if negative then above ||| 0x8000000000000000 else below',
        'let upper := if negative then below ||| 0x8000000000000000 else above'
    ]
    assert all(line in source_text for line in required)
    components = [HERE / 'NativeSignOr.lean.inc', HERE / 'RawMidpoint.lean.inc']
    dependencies = [
        ROUND / 'research/controller/MidpointWords.lean.inc',
        ROUND / 'research/representation/WidenNormal4.lean.inc',
        HERE / 'MidpointReal.lean.inc', HERE / 'NormalCell.lean.inc'
    ]
    def entry(p):
        return {'path': str(p.relative_to(ROOT)).replace('\\', '/'), 'bytes': p.stat().st_size, 'sha256': sha(p)}
    for p in components:
        assert not re.search(rb'\b(sorry|admit|axiom|unsafe|extern|native_decide)\b', p.read_bytes())
        assert not re.search(rb'^set_option\b|^import\b', p.read_bytes(), re.M)
    out = {
        'observed_at_utc': datetime.now(timezone.utc).isoformat(),
        'round_start_utc': '2026-10-28T20:38:56Z', 'round_deadline_utc': '2026-10-29T03:38:56Z',
        'components': [entry(p) for p in components],
        'roots': ['Submission.R24RawMidpoint.signed_endpoint_reals',
                  'Submission.R24RawMidpoint.roundRatScaled_of_endpoint_bounds'],
        'supporting_word_equality': 'Submission.R24NativeSignOr.raw_eq_neg',
        'dependencies': [entry(p) for p in dependencies],
        'runtime_source_readonly': entry(runtime), 'runtime_expression_strings_checked': required,
        'normal_words': len(cases), 'exact_endpoint_equalities': 2 * len(cases),
        'out_of_domain_words_field_adapter_only': 2 * len(excluded_fields),
        'witnesses': cases,
        'status': 'COMPLETE_PROOF_SOURCE_AND_FIXED_WORD_MODELS_PENDING_TYPING',
        'scope': 'Actual native sign-OR word model equality, finite native value negation, magnitude fields, UInt64 OR/add base equality, minimum-normal predicate, sign swap, and a thin existing NormalCell rational-rounder composition.',
        'remaining': ['Public typing/replay/AX of every exact source dependency',
                      'Runtime orderKey comparison boolean to endpoint real inequalities',
                      'Native radius and exact-sum enclosure composition',
                      'Any full checker correctness, measurement, or target adoption'],
        'verification': {'Lean': 'NOT_RUN', 'replay': 'NOT_RUN', 'axioms': 'NOT_RUN', 'performance': 'NOT_RUN'},
        'script_sha256': sha(Path(__file__)), 'token_usage': 'UNKNOWN', 'cached_input_tokens': 'UNKNOWN', 'CI_owner': 'D only'
    }
    (HERE / 'raw-midpoint-source-receipt.json').write_text(json.dumps(out, indent=2) + '\n', encoding='utf-8')
    print(json.dumps({'components': out['components'], 'normal_words': len(cases), 'endpoint_equalities': 2 * len(cases), 'roots': out['roots']}))

if __name__ == '__main__':
    main()
