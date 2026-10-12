"""Finite exact-packed reselect checks, including whole-domain shortcut counterexample."""
from pathlib import Path
import hashlib
import json
import random

ROOT = Path(__file__).resolve().parents[1]
MASK = (1<<32)-1


def key(cost, lc, distance_price, bias, length):
    return (((cost+lc+distance_price+bias)&MASK)<<9)&MASK | length


def slot(x):
    if x < 4:
        return x
    k = x.bit_length()-1
    return 2*k+((x>>(k-1))&1)


def main():
    rng = random.Random(2613)
    edges = [0,1,511,512,(1<<23)-1,1<<23,(1<<23)+1,(1<<31)-1,1<<31,MASK-1,MASK]
    cases = 0
    for _ in range(100000):
        cost, lc, bias = (rng.choice(edges) if rng.randrange(2) else rng.randrange(1<<32) for _ in range(3))
        old = rng.randrange(1<<32)
        new = rng.randrange(old+1)
        length = rng.randrange(3,259)
        delta = ((old-new)<<9)&MASK
        original = key(cost, lc, old, bias, length)
        assert (original-delta)&MASK == key(cost, lc, new, bias, length)
        cases += 1
    domains = 0
    for _ in range(10000):
        lo = rng.randrange(3,259)
        hi = min(258, lo+rng.randrange(40))
        cut = rng.randrange(lo-1, hi+1)
        old = rng.randrange(2049)
        new = rng.randrange(old+1)
        bias = rng.randrange(1<<32)
        costs = [rng.randrange(1<<32) for _ in range(hi-lo+1)]
        prices = [rng.randrange(1<<32) for _ in costs]
        original = [key(c,p,old,bias,l) for l,c,p in zip(range(lo,hi+1),costs,prices)]
        expected = [key(c,p,new,bias,l) for l,c,p in zip(range(lo,hi+1),costs,prices) if l<=cut]
        old_min = min(original)
        alt_min = min(((v-((old-new)<<9))&MASK for l,v in zip(range(lo,hi+1),original) if l<=cut), default=MASK)
        assert old_min == min(original) and alt_min == min(expected, default=MASK)
        domains += 1
    code_checks = 0
    for x in range(32768):
        for length in (3,258):
            for fixed in (False, True):
                packed = x | ((length-3)<<15) | (slot(x)<<23) | ((1<<31) if fixed else 0)
                assert ((packed>>23)%32) == slot(x)
                code_checks += 1
    old = [key(MASK,0,1,0,3), key(0,0,1,0,4)]
    new = [key(MASK,0,0,0,3), key(0,0,0,0,4)]
    assert (min(old)-512)&MASK != min(new)
    result = {'status': 'VERIFIED_FINITE_POINTWISE_PACKED_SUBTRACTION_AND_DOMAIN_MIN',
              'pointwise_cases': cases, 'domain_cases': domains, 'encoded_distance_code_cases': code_checks,
              'whole_domain_shortcut_counterexample': {'original_keys':old, 'new_keys':new,
                    'incorrect_subtract_from_original_min': (min(old)-512)&MASK,
                    'correct_new_min':min(new)},
              'exact_algebra': 'For length<512, v=((cost+lc+oldD+bias)<<9)|length; v-wrapping((oldD-newD)<<9) equals the term with newD mod2^32. It must be applied per term, not after original interval argmin.',
              'limits': ['Finite model of exact arithmetic; not native equivalence, universal formal lemma or gate.',
                         'Retain original term minimum, normal-only coverage intersection, and original final packed tie priority.',
                         'Encoded code consistency justifies carrying current-pass price along unchanged max-record XL/XD; all-input proof still pending.'],
              'script_sha256': hashlib.sha256(Path(__file__).read_bytes()).hexdigest()}
    path = ROOT/'evidence/round26/route-b/overlap-packed-model.json'
    path.write_bytes((json.dumps(result,indent=2)+'\n').encode())
    print(json.dumps(result))


if __name__=='__main__':
    main()
