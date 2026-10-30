#!/usr/bin/env python3
"""Original exact integer model; no FP arithmetic, upstream inputs, or timings.
Run: python3 integer_model.py --output results.json
The model is not an implemented/compiled native kernel.
"""
import argparse
from fractions import Fraction
import hashlib
import itertools
import json
from pathlib import Path
import random

B = 1 << 20
MASK64 = (1 << 64) - 1

def p2(e):
    return Fraction(1 << e) if e >= 0 else Fraction(1, 1 << -e)

def fields(w):
    return w >> 31, (w >> 23) & 255, w & 0x7fffff

def finite(w):
    return fields(w)[1] != 255

def parts(w):
    sign, e, f = fields(w)
    assert e != 255
    return sign, (f if e == 0 else (1 << 23) + f), max(0, e - 1)

def units149(w):
    s, m, i = parts(w)
    return (-m if s else m) << i

def relu_word(w):
    s, e, f = fields(w)
    return 0 if s and not (e == 255 and f != 0) else w

def rshift_even(m, shift):
    if shift <= 0:
        return m << -shift
    q, r = divmod(m, 1 << shift)
    h = 1 << (shift - 1)
    return q + int(r > h or (r == h and q & 1))

def rn32_units298(total, neg_zero=False):
    if total == 0:
        return 0x80000000 if neg_zero else 0
    sign = 0x80000000 if total < 0 else 0
    a = abs(total)
    lead = a.bit_length() - 1
    exponent = lead - 298
    if exponent < -126:
        m = rshift_even(a, 149)
        assert m <= (1 << 23)
        return sign | m
    m = rshift_even(a, lead - 23)
    if m == (1 << 24):
        m >>= 1
        exponent += 1
    if exponent > 127:
        return sign | 0x7f800000
    return sign | ((exponent + 127) << 23) | (m - (1 << 23))

def exact_linear(x, w, bias):
    total = sum(units149(a) * units149(b) for a, b in zip(x, w))
    total += units149(bias) << 149
    nz = (units149(bias) == 0 and (bias >> 31) == 1)
    nz = nz and all((units149(a) == 0 or units149(b) == 0)
                    and bool((a ^ b) >> 31) for a, b in zip(x, w))
    return total, rn32_units298(total, nz)

def packed3(a, b, base=B):
    assert len(a) == len(b) == 3
    A = a[0] + a[1] * base + a[2] * base * base
    C = b[2] + b[1] * base + b[0] * base * base
    # For B=2^20 this is ((A*C mod 2^64)>>40)&(B-1).
    return ((A * C) & MASK64) // (base * base) % base

def quantize(words, unsigned=False):
    assert all(map(finite, words))
    if unsigned and any(parts(v)[0] and parts(v)[1] for v in words):
        return None
    peak = max((parts(v)[2] for v in words), default=0)
    shift_base = peak + (16 if unsigned else 17)
    q, rem, raw_sign = [], [], []
    for v in words:
        sign, m, idx = parts(v)
        shift = shift_base - idx
        assert shift >= (16 if unsigned else 17)
        mag = 0 if shift >= 24 else m >> shift
        residual = bool(m) if shift >= 24 else (m != (mag << shift))
        qi = -mag if sign else mag
        assert 0 <= qi <= 255 if unsigned else -127 <= qi <= 127
        q.append(qi); rem.append(residual); raw_sign.append(sign)
    return {'peak': peak, 'shift': shift_base, 'q': q, 'rem': rem,
            'sign': raw_sign, 'sum_abs': sum(map(abs, q)), 'sum_q': sum(q),
            'qmax': max(map(abs, q), default=0), 'any_rem': any(rem),
            'positive_q_sum': sum(qi for qi, s in zip(q, raw_sign) if s == 0),
            'positive_rem_count': sum(r and s == 0 for r, s in zip(rem, raw_sign))}

def bias_interval(word, product_shift):
    # Product lattice is 2^(product_shift-298), bias is m*2^(idx-149).
    sign, m, idx = parts(word)
    if m == 0:
        return (0, 0)
    t = idx + 149 - product_shift
    if t >= 0:
        if m.bit_length() + t > 60:
            return None  # real guard; no overflowing native shift
        q, rem = m << t, False
    else:
        d = -t
        q = 0 if d >= 24 else m >> d
        rem = bool(m) if d >= 24 else m != (q << d)
    return (-q - int(rem), -q) if sign else (q, q + int(rem))

def packed_quantized_dot(qa, qb, unsigned_left):
    k = len(qa)
    N = 3 * ((k + 2) // 3)
    aa = list(qa) + [0] * (N - k)
    bb = list(qb) + [0] * (N - k)
    u = aa if unsigned_left else [a + 128 for a in aa]
    v = [b + 128 for b in bb]
    D = sum(packed3(u[i:i+3], v[i:i+3]) for i in range(0, N, 3))
    assert D <= 65025 * N < (1 << 63)
    if unsigned_left:
        Q = D - 128 * sum(qa)
    else:
        Q = D - 128 * sum(u) - 128 * sum(v) + 16384 * N
    assert Q == sum(a*b for a, b in zip(qa, qb))
    return Q, D, N

def certificate_probe(x, w, bias, relu=True, unsigned_left=True):
    """Executable proposed guards/bound; never evaluates the exact dot oracle.

    This Python implementation prepares each pair independently. A profitable
    native implementation MUST reuse row/column prep; no timing claim is made.
    """
    n = len(x)
    if not relu or n != len(w) or n > (1 << 30):
        return {'status': 'GUARD_MISS'}
    if any(type(v) is not int or not 0 <= v < (1 << 32) for v in x+w+[bias]):
        return {'status': 'GUARD_MISS'}
    if not all(map(finite, x + w + [bias])):
        return {'status': 'GUARD_MISS'}
    a = quantize(x, unsigned_left)
    if a is None:
        return {'status': 'GUARD_MISS'}
    b = quantize(w, False)
    shift = a['shift'] + b['shift']
    beta = bias_interval(bias, shift)
    if beta is None:
        return {'status': 'BIAS_RANGE_MISS'}
    Q, D, N = packed_quantized_dot(a['q'], b['q'], unsigned_left)
    if unsigned_left:
        K = b['positive_rem_count']
        E = min(a['sum_q'], a['qmax'] * K)
        if a['any_rem']:
            E += b['positive_q_sum'] + K
        upper = Q + E + beta[1]
        lower = Q - (a['sum_abs'] + b['sum_abs'] + n) + beta[0]
    else:
        E = a['sum_abs'] + b['sum_abs'] + n
        upper, lower = Q + E + beta[1], Q - E + beta[0]
    assert abs(Q) < (1 << 47) and E < (1 << 40)
    assert abs(upper) < (1 << 61) and abs(lower) < (1 << 61)
    return {'status': 'CERTIFIED_NEGATIVE' if upper < 0 else 'BOUND_MISS',
            'Q': Q, 'E_upper': E, 'bias_interval': beta, 'upper': upper,
            'lower': lower, 'product_shift': shift,
            'packed_multiplies': N // 3, 'N_padded': N,
            'nonzero_activation_count': sum(parts(v)[1] != 0 for v in x)}

def certified_or_fallback(x, w, bias, fallback, relu=True, unsigned_left=True):
    """Total routing skeleton; caller supplies original correct fallback.

    No speculative zero for nonfinite, shape, scale, or precision misses.
    This is NOT a linked YaV implementation and makes no scheduler claim.
    """
    r = certificate_probe(x, w, bias, relu, unsigned_left)
    return 0 if r['status'] == 'CERTIFIED_NEGATIVE' else fallback()

def certify(x, w, bias, relu=True, unsigned_left=True):
    """Validation wrapper only: exact integer oracle checks a finished probe."""
    r = certificate_probe(x, w, bias, relu, unsigned_left)
    if r['status'] not in ('CERTIFIED_NEGATIVE', 'BOUND_MISS'):
        return r
    shift, lower, upper = r['product_shift'], r['lower'], r['upper']
    total, output = exact_linear(x, w, bias)
    scaled = Fraction(total, 1 << shift)
    assert lower <= scaled <= upper
    hit = upper < 0  # deliberately strict first implementation
    if hit:
        assert total < 0 and relu_word(output) == 0
    r.update(scaled_exact_sum=str(scaled), true_negative=total < 0,
             activation_word=f'0x{relu_word(output):08x}')
    return r

def main():
    ap = argparse.ArgumentParser(); ap.add_argument('--output', default='results.json')
    args = ap.parse_args()
    rng = random.Random(0x523237)
    pack_checks = 0
    for v in itertools.product([0, 1, 128, 255], repeat=6):
        a, b = v[:3], v[3:]
        assert packed3(a, b) == sum(x*y for x, y in zip(a, b))
        pack_checks += 1
    for _ in range(10000):
        a = [rng.randrange(256) for _ in range(3)]
        b = [rng.randrange(256) for _ in range(3)]
        assert packed3(a, b) == sum(x*y for x, y in zip(a, b))
        pack_checks += 1
    assert packed3([591]*3, [591]*3) == 3*591*591
    assert packed3([592]*3, [592]*3) == 2816 != 3*592*592
    act_cases = {w: relu_word(w) for w in [0, 0x80000000, 0x80000001,
                    0xbf800000, 0xff800000, 0x7f800000, 0xffc00001, 0x7fc00001]}
    assert act_cases[0x80000000] == act_cases[0x80000001] == act_cases[0xff800000] == 0
    assert act_cases[0xffc00001] == 0xffc00001
    boundaries = [
        ('negative_underflow', [1], [0x80000001], 0),
        ('negative_overflow', [0x7f7fffff], [0xff7fffff], 0),
        ('negative_zero_bias', [0], [0x3f800000], 0x80000000),
        ('all_negative_zeros', [0x80000000], [0x3f800000], 0x80000000),
        ('positive_bias_reverses_dot', [0x3f800000], [0xbf800000], 0x40000000),
        ('subnormal_finite', [0x007fffff], [0x807fffff], 0),
        ('infinite_weight', [0], [0x7f800000], 0),
        ('nan_bias', [0x3f800000], [0xbf800000], 0xffc00001),
        ('empty_bias_only', [], [], 0xbf800000),
    ]
    boundary_out = []
    for name, x, w, bias in boundaries:
        r = certify(x, w, bias)
        item = {'name':name, 'x':[f'0x{v:08x}' for v in x],
                'w':[f'0x{v:08x}' for v in w], 'bias':f'0x{bias:08x}', 'certificate':r}
        if all(map(finite, x+w+[bias])):
            total, out = exact_linear(x,w,bias)
            item['rounded_dot_word']=f'0x{out:08x}'
            item['activated_word']=f'0x{relu_word(out):08x}'
        boundary_out.append(item)
    # Padding bug: centered s8/s8 must correct with padded count N, not k.
    qa = qb = [64]
    Q,D,N = packed_quantized_dot(qa,qb,False)
    u = [192,128,128]
    wrong = D -128*sum(u)-128*sum(u)+16384*1
    assert Q == 4096 and wrong == -28672
    assert wrong+(64+64+1)<0
    # Ignoring a positive bias would certify the wrong activation.
    no_bias = certify([0x3f800000], [0xbf800000], 0)
    with_bias = certify([0x3f800000], [0xbf800000], 0x40000000)
    assert no_bias['status']=='CERTIFIED_NEGATIVE' and not with_bias['true_negative']
    # A hit never calls fallback; every miss calls it once, including nonfinite.
    calls = []
    def fallback_marker():
        calls.append(True)
        return 0x7fc12345
    assert certified_or_fallback([0x3f800000], [0xbf800000], 0,
                                 fallback_marker) == 0 and not calls
    for x, w, bias, relu in [([0], [0x7f800000], 0, True),
                            ([0x3f800000], [0xbf800000], 0, False),
                            ([0xbf800000], [0x3f800000], 0, True),
                            ([0x3f800000], [], 0, True),
                            ([0x3f800000], [0xbf800000], 0x40000000, True)]:
        before = len(calls)
        assert certified_or_fallback(x,w,bias,fallback_marker,relu) == 0x7fc12345
        assert len(calls) == before + 1
    # Metadata-only upper error: random finite inputs including subnormals.
    random_checks = 0
    for _ in range(500):
        n = rng.randrange(1,65)
        x = [(rng.randrange(255)<<23)|rng.randrange(1<<23) for _ in range(n)]
        w = [(rng.randrange(2)<<31)|(rng.randrange(255)<<23)|rng.randrange(1<<23) for _ in range(n)]
        bias = (rng.randrange(2)<<31)|(rng.randrange(255)<<23)|rng.randrange(1<<23)
        certify(x,w,bias, unsigned_left=True)
        xs = [v | (rng.randrange(2)<<31) for v in x]
        certify(xs,w,bias, unsigned_left=False)
        random_checks += 2
    # Controlled synthetic families, never a workload-accuracy estimate.
    rows=[]
    for family in ['negative_aligned','positive_aligned','balanced_pairs',
                   'wide_small_negative_tail','sparse_one_active','seeded_mixed']:
        n=96; cases=[]
        for trial in range(32):
            x=[0x3f800000|rng.randrange(1<<23) for _ in range(n)]
            w=[0x3f800000|rng.randrange(1<<23) for _ in range(n)]
            if family=='negative_aligned': w=[v|0x80000000 for v in w]
            elif family=='balanced_pairs':
                x=[0x3f800000]*n
                w=[0x3f800000 if i%2==0 else 0xbf800001 for i in range(n)]
            elif family=='wide_small_negative_tail':
                x=[0x3f800000]*n
                w=[0x3f800000,0xbf800000]+[0xa5000000]*(n-2)
            elif family=='sparse_one_active':
                x=[0]*(n-1)+[0x3f800001];w=[v|0x80000000 for v in w]
            elif family=='seeded_mixed':
                w=[v | (rng.randrange(2)<<31) for v in w]
            cases.append(certify(x,w,0))
        hits=sum(c['status']=='CERTIFIED_NEGATIVE' for c in cases)
        groups=sum(all(c['status']=='CERTIFIED_NEGATIVE' for c in cases[i:i+4])
                   for i in range(0,32,4))
        rows.append({'family':family,'cases':32,'k':n,
                     'true_negative':sum(c.get('true_negative',False) for c in cases),
                     'certificate_hits':hits,'all_hit_groups_of4':groups,
                     'groups_of4':8,'packed_multiplies_per_output':32,
                     'nonzero_x_per_output':cases[0]['nonzero_activation_count'],
                     'first_case':cases[0]})
    out={'status':'PASS_EXACT_INTEGER_MODEL','seed':'0x523237',
         'packing_checks':pack_checks,'random_finite_certificate_checks':random_checks,
         'native_status':'NOT_RUN','lean_status':'NOT_COMPILED',
         'fallback_routing_checks':6,
         'no_frozen_inputs':True,'uses_host_float':False,
         'scope':'Synthetic coverage is not representative workload accuracy.',
         'activation_cases':{f'0x{k:08x}':f'0x{v:08x}' for k,v in act_cases.items()},
         'boundary_cases':boundary_out,
         'padding_counterexample':{'raw_x':'0x3f800000','raw_w':'0x3f800000',
              'k':1,'N':N,'D':D,'correct_Q':Q,'wrong_Q_using_k':wrong,
              'wrong_upper_with_symmetric_error':wrong+129,'true_activation':'0x3f800000'},
         'too_small_base_counterexample':{'base':1<<17,'digits':[255]*6,
              'extracted':packed3([255]*3,[255]*3,1<<17),'correct_dot':3*255*255},
         'max_uniform_digit_range':{'max_valid_digit':591,
              'first_invalid_digit':592, 'extracted_at_592':2816,
              'correct_dot_at_592':3*592*592},
         'synthetic_families':rows,
         'script_sha256':hashlib.sha256(Path(__file__).read_bytes()).hexdigest()}
    Path(args.output).write_text(json.dumps(out,ensure_ascii=False,indent=2)+'\n')
    print(json.dumps({'status':out['status'],'packing_checks':pack_checks,
          'random_checks':random_checks,'families':[{k:r[k] for k in ['family','true_negative',
           'certificate_hits','all_hit_groups_of4']} for r in rows]},ensure_ascii=False))

if __name__=='__main__': main()
