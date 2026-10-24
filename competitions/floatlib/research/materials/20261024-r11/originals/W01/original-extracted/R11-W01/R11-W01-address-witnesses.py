#!/usr/bin/env python3
"""Exact integer address constructions only: not Lean/FloatLib acceptance."""
import json

cases = []
for bits in [32, 64]:
    U = 2**bits
    batch, m, p = 1, 5, 2
    n = (U-1)//5
    guard = (p == 2 and 4 <= batch*m and 0 < n and n < U
             and batch*m*n < U and batch*n*p < U and batch*m*p < U)
    assert guard and 7*n >= U
    cases.append({
        "kind": "unneeded_all_tail_offsets_machine_bound_counterexample",
        "USize_bits_model": bits, "U": U, "batch": batch, "m": m, "n": n, "p": p,
        "A_length": batch*m*n, "B_length": batch*n*p,
        "output_length": batch*m*p, "dispatch_guard": guard,
        "phantom_row": 7, "A_base": 7*n, "A_base_ge_U": 7*n >= U,
        "note": "Exact integer construction only; not a runtime allocation or FloatLib execution."
    })
batch, m, n, p = 2, 3, 1, 2
rows = []
for g in range((batch*m+3)//4):
    rs = []
    for lane_r in range(4):
        r = 4*g+lane_r
        rs.append({
            "local_row": lane_r, "global_row": r, "emitted": r < batch*m,
            "A_base": r*n, "B_base": r//m*n*p
        })
    rows.append({
        "group": g, "rows": rs,
        "shared_B_guard": len({x["B_base"] for x in rs}) == 1
    })
cases.append({
    "kind": "cross_batch_and_tail", "shape": [batch,m,n,p], "groups": rows,
    "A_exact_integers": [1]*6, "B_exact_integers": [1,2,4,8],
    "correct_row3": [4,8], "wrong_always_shared_row3": [1,2],
    "note": "Index/one-product arithmetic witness; no claimed Lean or FloatLib execution."
})
print(json.dumps({
    "status": "EXACT_INTEGER_CONSTRUCTION", "acceptance": False, "cases": cases
}, indent=2))
