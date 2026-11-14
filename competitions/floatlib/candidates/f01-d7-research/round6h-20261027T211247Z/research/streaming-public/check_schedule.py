"""Finite symbolic-address check; deliberately not a Float32 or Lean proof."""
from itertools import product
from pathlib import Path
from datetime import datetime, timezone
import json

OUT = Path(__file__).resolve().parent

def reference(batch, m, n, p):
    return [tuple(((b*m+i)*n+k, b*n*p+k*p+j) for k in range(n))
            for b in range(batch) for i in range(m) for j in range(p)]

def paired(batch, m, n, p):
    out = []
    for b in range(batch):
        for g in range(m//2):
            i = 2*g
            lanes = [[[] for _ in range(p)] for _ in range(2)]
            for k in range(n):
                for j in range(p):
                    for lane in range(2):
                        lanes[lane][j].append(((b*m+i+lane)*n+k, b*n*p+k*p+j))
            for lane in lanes:
                out.extend(tuple(xs) for xs in lane)
        if m % 2:
            out.extend(tuple(((b*m+m-1)*n+k, b*n*p+k*p+j) for k in range(n)) for j in range(p))
    return out

def exact_cost_caller(batch, m, n, p):
    out = []
    for b in range(batch):
        for g in range(m//2):
            base0=(b*m+2*g)*n
            base1=(b*m+2*g+1)*n
            baseB=b*n*p
            for base in (base0,base1):
                out.extend(tuple((base+k,baseB+j+k*p) for k in range(n)) for j in range(p))
        # This is D's actual (m % 2) * p loop and Nat-saturated A address.
        out.extend(tuple((max(b*m+m-1,0)*n+k,b*n*p+j+k*p) for k in range(n))
                   for j in range((m%2)*p))
    return out

def main():
    count = 0
    for shape in product(range(5), range(10), range(8), range(10)):
        expected, actual = reference(*shape), paired(*shape)
        assert actual == expected, shape
        assert exact_cost_caller(*shape) == expected, shape
        assert len(actual) == shape[0]*shape[1]*shape[3]
        count += 1
    shape = (2,3,2,3)
    expected = reference(*shape)
    # Mutant shares the B batch of an even global row with its next row.
    b,m,n,p = shape
    mutated = [tuple((r*n+k, (2*(r//2)//m)*n*p+k*p+j) for k in range(n))
               for r in range(b*m) for j in range(p)]
    diffs = [i for i,(a,z) in enumerate(zip(expected, mutated)) if a != z]
    assert diffs == [9,10,11]
    result = {
        'at_utc': datetime.now(timezone.utc).isoformat(),
        'scope': 'Finite symbolic address and operation-order equality only; no floating-point value emulation, no Lean execution, no performance claim.',
        'shape_ranges_inclusive': {'batch':[0,4], 'm':[0,9], 'n':[0,7], 'p':[0,9]},
        'checked_shapes': count, 'mismatches': 0,
        'exact_D_cost_caller_checked_shapes':count,
        'exact_D_cost_caller_mismatches':0,
        'original_odd_batch_counterexample': {'shape':shape, 'new_driver_pass':True},
        'global_pair_mutant_rejected_at_outputs': diffs,
        'per_output_k_order': 'Ascending 0 .. n-1 preserved symbolically',
        'initial_accumulator_and_finish': 'Not modeled; exact R21 pair component reused and raw NaN replay retained in source.'
    }
    (OUT / 'schedule-check.json').write_text(json.dumps(result, indent=2)+'\n', encoding='utf-8')
    print(json.dumps(result))

if __name__ == '__main__':
    main()
