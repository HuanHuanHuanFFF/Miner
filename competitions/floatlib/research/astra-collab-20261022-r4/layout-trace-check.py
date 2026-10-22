"""Finite address/order diagnostic, not Lean or floating-point acceptance."""
from pathlib import Path
import hashlib
import itertools
import json

HERE = Path(__file__).resolve().parent
ROOT = HERE.parents[3]
kernel = ROOT / 'competitions/floatlib/candidates/f01-r4-tile2x4/Kernel.lean'
assert hashlib.sha256(kernel.read_bytes()).hexdigest() == '7de60fa52c445fa31aad8a0b9e4143933e0c0b26cdebf07d12805c3fa72a5476'

def selected_trace(batch, m, n, p, b, i, j):
    row_group, row_lane = divmod(i, 2)
    col_group, col_lane = divmod(j, 4)
    base0 = (b*m + 2*row_group)*n
    base1 = base0+n
    selected_base = base0 if row_lane == 0 else base1
    selected_column = 4*col_group+col_lane
    return tuple((selected_base+k, (b*n+k)*p+selected_column) for k in range(n))

trace_hash = hashlib.sha256()
shapes = outputs = pairs = odd_rows = 0
for batch, m, n, p in itertools.product(range(4), range(6), range(7), range(11)):
    shapes += 1
    for b, i, j in itertools.product(range(batch), range(m), range(p)):
        actual = selected_trace(batch, m, n, p, b, i, j)
        expected = tuple(((b*m+i)*n+k, (b*n+k)*p+j) for k in range(n))
        assert actual == expected
        assert i//2 < (m+1)//2 and j//4 < (p+3)//4
        assert all(0 <= a < batch*m*n and 0 <= bb < batch*n*p for a, bb in actual)
        trace_hash.update(repr((batch,m,n,p,b,i,j,actual)).encode())
        outputs += 1
        pairs += len(actual)
        odd_rows += int(m % 2 == 1 and i == m-1)

boundary_cases = 0
for bits in (32,64):
    limit = 1 << bits
    for n, base0, size in itertools.product((0,1,2,3,limit-1,limit,limit+1),
                                          (0,1,limit-2,limit-1,limit,limit+1),
                                          (0,1,2,limit-1,limit,limit+3)):
        base1 = base0+n
        admit = (n < limit and base0 < limit and base1 < limit and
                 base0+max(n-1,0) < size and base1+max(n-1,0) < size and size < limit)
        if admit and n:
            for k in {0,n//2,n-1}:
                assert (base0+k) % limit == base0+k < size
                assert (base1+k) % limit == base1+k < size
                assert (k+1) % limit == k+1
        boundary_cases += 1

# Flattening row pairs across batches incorrectly reuses batch0's right operand.
counterexample = {'shape':[2,1,1,1], 'A':[1,1], 'B':[2,3],
                  'correct_output':[2,3], 'wrong_cross_batch_pair_output':[2,2]}
result = {'status':'PASS_FINITE_ADDRESS_ORDER_DIAGNOSTIC', 'shapes':shapes,
          'valid_outputs':outputs, 'ordered_address_pairs':pairs,
          'odd_final_row_outputs':odd_rows, 'machine_boundary_cases':boundary_cases,
          'trace_sha256':trace_hash.hexdigest(), 'counterexample':counterexample,
          'candidate_sha256':hashlib.sha256(kernel.read_bytes()).hexdigest(),
          'limits':['No Float32 arithmetic executed; no NaN payload validation',
                    'Only finite dimensions and sampled machine-boundary indices',
                    'Not a proof of the universal Lean obligation or a performance result']}
(HERE/'layout-trace-check.json').write_text(json.dumps(result,indent=2)+'\n',encoding='utf-8')
print(json.dumps(result,indent=2))
