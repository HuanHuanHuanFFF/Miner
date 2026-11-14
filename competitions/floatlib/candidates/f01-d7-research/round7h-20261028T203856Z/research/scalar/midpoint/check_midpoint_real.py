"""Eight fixed word/real boundary witnesses for the new decode transport.

This checks exact binary64 bit denotations, not native execution or Lean.
The already retained broad midpoint sampling is not rerun.
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

def sha(path):
    return hashlib.sha256(path.read_bytes()).hexdigest()

def p2(k):
    return F(1 << k) if k >= 0 else F(1, 1 << -k)

def decode64(word):
    e, f = (word >> 52) & 2047, word & ((1 << 52) - 1)
    assert word >> 63 == 0 and 0 < e < 2047
    return ((1 << 52) + f) * p2(e - 1075)

def main():
    fixed = [(1, 0), (1, 1), (1, 8388607), (2, 0), (127, 0),
             (127, 1), (254, 0), (254, 8388607)]
    witnesses = []
    for e, f in fixed:
        center = ((e + 896) << 52) + (f << 29)
        upper = center + 0x10000000
        lower = center - (0x20000000 if e == 1 and f == 0 else 0x10000000)
        expected_low = (F(8388608 + f) - (F(1, 4) if f == 0 and e > 1 else F(1, 2))) * p2(e - 150)
        expected_high = (F(8388608 + f) + F(1, 2)) * p2(e - 150)
        assert decode64(lower) == expected_low and decode64(upper) == expected_high
        witnesses.append({'e': e, 'f': f, 'lower_word': f'0x{lower:016x}', 'upper_word': f'0x{upper:016x}',
                          'lower_exact': str(expected_low), 'upper_exact': str(expected_high),
                          'lower_branch': 'minnormal' if e == 1 and f == 0 else 'power' if f == 0 else 'inner'})
    source = HERE / 'MidpointReal.lean.inc'
    source_bytes = source.read_bytes()
    assert not re.search(rb'\b(sorry|admit|axiom|unsafe|extern|native_decide)\b', source_bytes)
    dependencies = [
        (ROUND / 'research/controller/MidpointWords.lean.inc', 'f5dbbdaf457823ba26857f5804184583e47e64d540629b45a1c7319ea554bd12'),
        (ROUND / 'research/representation/WidenNormal3.lean.inc', '9a1e894c10c9e8bcc160133d1d2aab084c358a24a04a5f78e11361ae0be8a517'),
        (HERE / 'NormalCell.lean.inc', '43958f8bb657966dcf05b328dc7bd38ac8ddb1f81a228cfcf7eee8636dddebd4')
    ]
    for path, expected in dependencies:
        assert sha(path) == expected
    result = {
        'observed_at_utc': datetime.now(timezone.utc).isoformat(),
        'round_start_utc': '2026-10-28T20:38:56Z', 'round_deadline_utc': '2026-10-29T03:38:56Z',
        'component': {'path': str(source.relative_to(ROOT)).replace('\\', '/'), 'bytes': len(source_bytes), 'sha256': sha(source)},
        'roots': ['Submission.R24MidpointReal.upper_real', 'Submission.R24MidpointReal.lower_real'],
        'dependencies': [{'path': str(p.relative_to(ROOT)).replace('\\', '/'), 'bytes': p.stat().st_size, 'sha256': h} for p, h in dependencies],
        'declaration_dependencies': ['R24MidpointWords.upper_decode', 'R24MidpointWords.lower_inner_decode',
                                     'R24MidpointWords.lower_power_decode', 'R24MidpointWords.lower_minNormal_decode',
                                     'R24RepresentationWiden.native_ofBits_of_decode',
                                     'R24NormalCell.lowerMagnitude', 'R24NormalCell.upperMagnitude',
                                     'Model.toReal_eq', 'Dyadic.toReal_mk_false', 'Model.bpow_add'],
        'status': 'SOURCE_COMPLETE_TERMS_AND_8_FIXED_WORD_MODELS_PENDING_TYPING',
        'fixed_cases': len(fixed), 'equalities_checked': 2 * len(fixed), 'witnesses': witnesses,
        'exact_source_scope': 'For UInt64 e/f with 0<e.toNat<255 and f.toNat<2^23, real semantics of actual Float.ofBits midpoint words equal the positive NormalCell endpoints. Includes maxfinite upper endpoint.',
        'explicit_remaining': ['Raw32 q extraction/conversion into the UInt64 e/f arguments',
                               'Actual negative native-word endpoint reflection/swap',
                               'Caller strict comparison and full source-to-cell composition',
                               'Acceptance of all dependent source artifacts'],
        'not_claimed': ['Model.toReal equality as native-bit injectivity', 'Native runtime execution', 'Speed or hit rate', 'Any new target implementation'],
        'verification': {'Lean': 'NOT_RUN', 'replay': 'NOT_RUN', 'axioms': 'NOT_RUN', 'performance': 'NOT_RUN'},
        'script_sha256': sha(Path(__file__)), 'token_usage': 'UNKNOWN', 'cached_input_tokens': 'UNKNOWN', 'CI_owner': 'D only'
    }
    (HERE / 'midpoint-real-source-receipt.json').write_text(json.dumps(result, indent=2) + '\n', encoding='utf-8')
    print(json.dumps({'component': result['component'], 'roots': result['roots'], 'cases': len(fixed), 'equalities': 2 * len(fixed)}))

if __name__ == '__main__':
    main()
