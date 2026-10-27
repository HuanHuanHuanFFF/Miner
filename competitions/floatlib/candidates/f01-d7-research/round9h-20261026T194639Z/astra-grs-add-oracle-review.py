"""Check the model oracle independently by exact binary search of IEEE word order."""
from pathlib import Path
from hashlib import sha256
import importlib.util
import json
import random

HERE = Path(__file__).resolve().parent
p = HERE / 'astra-grs-add-model.py'
spec = importlib.util.spec_from_file_location('grs_model', p)
model = importlib.util.module_from_spec(spec)
spec.loader.exec_module(model)

def units(bits):
    e, f = bits >> 23, bits & 0x7fffff
    return f if e == 0 else (0x800000 | f) << (e - 1)

def independently_round_sum(u, v):
    n = (-1 if u >> 31 else 1) * units(u & 0x7fffffff)
    n += (-1 if v >> 31 else 1) * units(v & 0x7fffffff)
    if n == 0:
        return 0
    sign, n = (n < 0) << 31, abs(n)
    max_finite = 0x7f7fffff
    if n >= units(max_finite) + (1 << 252):
        return sign | 0x7f800000
    if n >= units(max_finite):
        return sign | max_finite
    lo, hi = 0, max_finite
    while lo + 1 < hi:
        mid = (lo + hi) // 2
        if units(mid) <= n:
            lo = mid
        else:
            hi = mid
    midpoint_twice = units(lo) + units(hi)
    choose_hi = 2*n > midpoint_twice or (2*n == midpoint_twice and lo & 1)
    return sign | (hi if choose_hi else lo)

rng = random.Random(19272332)
cases = [(0x3f800000,0xbf800000),(0x00800000,0x80800001),
         (0x7f7fffff,0x7f7fffff),(0xff7fffff,0xff7fffff),
         (0x3f800000,0x33000000),(0x3f800001,0x33000000),
         (0x00800000,0x00800000),(0x01000000,0x80800001)]
for _ in range(2048):
    cases.append(tuple((rng.randrange(2)<<31) | (rng.randrange(1,255)<<23) |
                       rng.randrange(1<<23) for _ in range(2)))
failures = []
accepted = 0
for u,v in cases:
    reference = independently_round_sum(u,v)
    original = model.exact_add_normal(u,v)
    proposal = model.proposal(u,v)
    if original != reference or (proposal is not None and proposal != reference):
        failures.append({'u':hex(u),'v':hex(v),'binary_search':hex(reference),
                         'original_oracle':hex(original),'proposal':proposal})
        break
    accepted += proposal is not None
out = {'state':'BOUNDED_INDEPENDENT_ORACLE_REVIEW', 'cases':len(cases),
       'accepted_proposal_cases':accepted,'failures':failures,'seed':19272332,
       'reference':'Signed integer units2^-149; binary search all positive finite IEEE words; exact nearest-distance/ties-even plus overflow threshold. No reuse of RNE quotient helper.',
       'model_sha256':sha256(p.read_bytes()).hexdigest(),
       'review_sha256':sha256(Path(__file__).read_bytes()).hexdigest(),
       'scope':'Supports correctness of the finite checker on these cases, not all-input proposal correctness, Lean, target lowering or performance.'}
(HERE/'astra-grs-add-oracle-review.json').write_text(json.dumps(out,indent=2)+'\n')
print(json.dumps(out,indent=2))
if failures:
    raise SystemExit(1)
