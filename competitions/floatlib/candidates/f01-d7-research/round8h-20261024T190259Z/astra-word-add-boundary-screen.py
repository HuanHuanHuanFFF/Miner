"""Bounded falsification of add-domain identities; not Lean/native execution."""
from pathlib import Path
from itertools import product
from hashlib import sha256
from datetime import datetime, timezone
from time import monotonic
import json

start = monotonic()
budget_seconds, max_cases = 2.0, 3000
values = [2**23, 2**23 + 1, 2**23 + 127, 2**23 + 128,
          2**24 - 129, 2**24 - 2, 2**24 - 1]
cases = []
for gap, same, hi, lo in product(range(8), [False, True], values, values):
    if not (same or gap >= 2):
        continue
    for elo in [1, 254 - gap]:
        assert monotonic() - start <= budget_seconds
        assert len(cases) < max_cases
        ehi = elo + gap
        left = hi << gap
        n = left + lo if same else left - lo
        base = (23 if same else 22) + gap
        h = n.bit_length() - 1
        assert 2**24 <= n <= 2164260735 < 2**32
        assert 2**base <= n < 2**(base + 2)
        assert h == base + (n >> (base + 1))
        assert 24 <= h <= min(31, gap + 24)
        t = h - 23
        q, rem = divmod(n, 2**t)
        nearest = q + int(2*rem > 2**t or (2*rem == 2**t and q % 2 == 1))
        biased = (n + 2**(t-1) - 1 + ((n >> t) & 1)) >> t
        assert nearest == biased
        assert 2**23 <= nearest <= 2**24
        c = nearest >> 24
        assert c == int(nearest == 2**24)
        mantissa = 2**23 if c else nearest
        assert nearest % 2**23 == mantissa - 2**23
        e = h + elo - 23 + c
        assert 2 <= e <= 256
        word_guard = ((e - 1) % 2**32) <= 253
        field_guard = 1 <= (e % 256) <= 254
        assert word_guard == field_guard == (e <= 254)
        cases.append(dict(gap=gap, same=same, hi=hi, lo=lo, elo=elo,
                          n=n, h=h, t=t, carry=c, exponent=e))

negative = [
    dict(premise_removed='opposite gap>=2', gap=1, hi=2**23, lo=2**24-1,
         n=(2**23 << 1)-(2**24-1), effect='n=1 has log2=0; small-shift domain fails'),
    dict(premise_removed='nonzero opposite gap=0 excluded', gap=0,
         hi=2**23, lo=2**23, n=0, effect='complete cancellation'),
    dict(premise_removed='gap<=7', gap=8, hi=2**24-1, lo=2**24-1,
         n=((2**24-1)<<8)+(2**24-1), effect='UInt32 addition wraps'),
    dict(premise_removed='E<=256 before exponent-field check', exponent=257,
         exponent_field=1, field_guard_accepts=True,
         actual_runtime2_word_guard_accepts=False,
         effect='illustrative masked-field alias; not an actual runtime2 bug')]
receipt = dict(timestamp_utc=datetime.now(timezone.utc).isoformat(),
               script_sha256=sha256(Path(__file__).read_bytes()).hexdigest(),
               budget_seconds=budget_seconds, max_cases=max_cases,
               elapsed_seconds=monotonic()-start, count=len(cases),
               result='NO_COUNTEREXAMPLE_IN_SELECTED_BOUNDARY_CASES',
               source_scope='Pure Python integer identities, not pinned Lean/native candidate execution or performance',
               extremes={k:dict(min=min(c[k] for c in cases), max=max(c[k] for c in cases))
                         for k in ['n', 'h', 't', 'carry', 'exponent']},
               carry_cases=sum(c['carry'] for c in cases),
               overflow_rejected_cases=sum(c['exponent'] >= 255 for c in cases),
               negative=negative, cases=cases)
out = Path(__file__).with_suffix('.json')
out.write_text(json.dumps(receipt, indent=2, ensure_ascii=False)+'\n', encoding='utf-8')
print(json.dumps({k:v for k,v in receipt.items() if k!='cases'}, indent=2, ensure_ascii=False))
