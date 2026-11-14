"""Closed-arithmetic witnesses for unsafe band-guard simplifications."""
from pathlib import Path
from datetime import datetime, timezone
import hashlib
import json

HERE = Path(__file__).resolve().parent
M64 = (1 << 64)-1
M128 = (1 << 128)-1


def signed(value, bits):
    value &= (1 << bits)-1
    return value if value < 1 << (bits-1) else value-(1 << bits)


def main():
    mant = (1 << 24)-1
    factor_a = mant << 3
    factor_b = mant << 7
    product = factor_a * factor_b
    block = 64 * product
    assert factor_a < 1 << 27 and factor_b < 1 << 31
    assert 1 << 63 < block < 1 << 64
    assert signed(block, 64) != block
    # These packed finite words give literal Yc spans3 and7. Fraction1 on
    # the low endpoints avoids the conservative exponent decrement at powers2.
    local = {
        'n': 65, 'first_64_x': (124 << 23) | 0x7fffff,
        'last_x': (121 << 23) | 1,
        'first_64_w': (127 << 23) | 0x7fffff,
        'last_w': (120 << 23) | 1,
        'x_span': 3, 'weight_span': 7,
        'factor_a': factor_a, 'factor_b': factor_b,
        'term': product, 'block64_exact_sum': block,
        'signed_low64': signed(block, 64),
        'current_guard': 'Rejects weight span7; remains safe.',
        'invalid_change': 'Allowing span7 while retaining64 terms can overflow the signed block.'}
    n = (1 << 20)-1
    high_terms = n-1
    high_product = mant*mant*(1 << 60)
    low_product = ((1 << 23)+1)**2
    total = high_terms*high_product+low_product
    local_product = (mant << 2)*(mant << 6)
    assert 64*local_product < 1 << 63
    assert total > 1 << 127 and total < 1 << 128
    outer = {
        'n': n, 'high_terms': high_terms,
        'repeated_high_x': (175 << 23) | 0x7fffff,
        'single_low_x': (121 << 23) | 1,
        'repeated_high_w': (127 << 23) | 0x7fffff,
        'single_low_w': (121 << 23) | 1,
        'x_span': 54, 'weight_span': 6,
        'terminal_range_without_bias': 60,
        'block64_local_mass': 64*local_product,
        'global_exact_body': total, 'signed_128_interpretation': signed(total,128),
        'current_guard': 'Rejects terminal range60 before preparation; remains safe.',
        'invalid_change': 'The per-block bound alone does not keep the complete shifted body in signed128.',
        'execution': 'Closed repeated-term arithmetic only. No million-element allocation or native loop.'}
    result = {'at_utc': datetime.now(timezone.utc).isoformat(),
              'state': 'EXPLICIT_ALGEBRAIC_COUNTEREXAMPLES_TO_GUARD_WIDENING_NOT_TO_CURRENT_CANDIDATE',
              'local_block': local, 'global_body': outer,
              'note': 'Range58 remains the selected sufficient rule. This does not claim range59 is impossible under the actual strict n bound; no such widening was implemented or proved.',
              'source_hashes': {p.name: hashlib.sha256(p.read_bytes()).hexdigest() for p in
                               (Path(__file__), HERE/'BandNative.lean.inc')}}
    (HERE/'guard-widening-witness.json').write_text(json.dumps(result, indent=2), encoding='utf8')
    print(json.dumps({'block64_sum': block, 'signed64': signed(block,64),
                      'global_body_bits': total.bit_length(), 'global_signed128_negative': signed(total,128)<0}))


if __name__ == '__main__':
    main()
