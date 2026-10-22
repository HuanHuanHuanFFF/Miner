#!/usr/bin/env python3
"""Independent symbolic input-address and operation-order diagnosis.

Float32 values and arithmetic are uninterpreted expression nodes. This checks
the new nested-cache schedule, not IEEE numerics, NaN payloads or Lean proofs.
"""
import json
import platform
import sys


ZERO = ("positive-zero",)


def raw_read(tag, size, index):
    return ("convert", (tag, index)) if index < size else ZERO


def step(acc, a, b):
    return ("add32", acc, ("mul32", a, b))


def reference(batch, m, n, p):
    output = []
    for q in range(batch * m * p):
        b, rem = divmod(q, m * p)
        i, j = divmod(rem, p)
        acc = ZERO
        for k in range(n):
            acc = step(acc, raw_read("A", batch * m * n, (b * m + i) * n + k),
                       raw_read("B", batch * n * p, (b * n + k) * p + j))
        output.append(acc)
    return output


def packed(batch, m, n, p):
    if batch * m * p == 0 or n == 0:
        return [ZERO] * (batch * m * p), 0
    groups = (p + 3) // 4
    native_a = [raw_read("A", batch * m * n, index) for index in range(batch * m * n)]
    packed_b = [
        [
            [tuple(raw_read("B", batch * n * p, (b * n + k) * p + 4 * g + lane)
                   if 4 * g + lane < p else ZERO for lane in range(4))
             for k in range(n)]
            for g in range(groups)
        ] for b in range(batch)
    ]
    tiles = []
    calls = 0
    for b in range(batch):
        rows = []
        for i in range(m):
            row = []
            for g in range(groups):
                state = [ZERO] * 4
                for k in range(n):
                    a = native_a[(b * m + i) * n + k]
                    packet = packed_b[b][g][k]
                    state = [step(state[lane], a, packet[lane]) for lane in range(4)]
                row.append(tuple(state))
                calls += 1
            rows.append(row)
        tiles.append(rows)
    output = []
    for q in range(batch * m * p):
        b, rem = divmod(q, m * p)
        i, j = divmod(rem, p)
        output.append(tiles[b][i][j // 4][j % 4])
    assert calls == batch * m * groups
    return output, calls


def main():
    shapes = outputs = calls = 0
    for batch in range(4):
        for m in range(5):
            for n in range(8):
                for p in range(10):
                    expected = reference(batch, m, n, p)
                    actual, count = packed(batch, m, n, p)
                    assert actual == expected, (batch, m, n, p)
                    shapes += 1
                    outputs += len(expected)
                    calls += count
    total_read_cases = 0
    for size in range(8):
        native = [raw_read("A", size, i) for i in range(size)]
        for i in range(12):
            assert (native[i] if i < size else ZERO) == raw_read("A", size, i)
            total_read_cases += 1
    b, m, n, p = 2, 50, 100, 50
    g = (p + 3) // 4
    counts = {
        "shape": [b, m, n, p], "groups": g,
        "input_conversions": b * m * n + b * n * p,
        "b_packet_records": b * g * n, "tile_result_records": b * m * g,
        "b_logical_array_containers": 1 + b + b * g,
        "tile_logical_array_containers": 1 + b + b * m,
        "all_logical_result_array_containers": 4 + 2 * b + b * g + b * m,
        "nested_child_reference_slots": 2 * b + b * g + b * m,
        "ordered_four_lane_iterations": b * m * g * n,
        "native_multiplications": 4 * b * m * g * n,
        "native_additions": 4 * b * m * g * n,
        "output_selections_and_finite_checks": b * m * p,
        "logical_tile_cache_gets": 3 * b * m * p,
    }
    result = {
        "status": "PASSED_SYMBOLIC_SCHEDULING_MODEL_ONLY",
        "shape_range": "batch=0..3,m=0..4,n=0..7,p=0..9",
        "shapes": shapes, "compared_output_expression_trees": outputs,
        "dot4_calls_in_model": calls, "total_read_default_cases": total_read_cases,
        "default_counts": counts,
        "python": sys.version, "platform": platform.platform(),
        "lean_elaboration": "NOT_RUN", "floating_point_execution": "NOT_RUN",
        "NaN_payload_validation": "NOT_RUN", "timing": "NOT_RUN",
        "scope": "Source-level symbolic model; does not execute the Lean candidate or establish all-input numerical correctness.",
    }
    print(json.dumps(result, indent=2))


if __name__ == "__main__":
    main()
