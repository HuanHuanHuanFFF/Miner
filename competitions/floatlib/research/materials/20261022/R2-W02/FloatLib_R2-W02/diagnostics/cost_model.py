#!/usr/bin/env python3
"""Source-level operation counts, not timing or observed allocations."""
import argparse
import json


def counts(batch, m, n, p):
    out = batch * m * p
    if out == 0 or n == 0:
        return {"output_elements": out, "input_conversions": 0,
                "native_MAC": 0, "early_return": True}
    g = (p + 3) // 4
    packets = batch * g * n
    tiles = batch * m * g
    steps = tiles * n
    return {
        "early_return": False, "output_elements": out,
        "blocks_per_row": g, "valid_MAC": out * n,
        "native_MAC": 4 * steps,
        "input_A_conversions": batch * m * n,
        "input_B_conversions": batch * n * p,
        "B_padding_fields": batch * n * (4 * g - p),
        "explicit_B_packet_constructions": packets,
        "explicit_terminal_packet_constructions": tiles,
        "A_hot_reads": steps, "B_packet_hot_reads": steps,
        "B_scalar_hot_reads": 4 * steps,
        "packing_div_mod_expressions": 4 * packets,
        "packing_column_tests": 4 * packets,
        "output_column_tests": 4 * tiles,
        "valid_terminal_finite_tests": out,
        "native_output_conversions_upper_bound": out,
        "exact_fallback_dot_range": [0, out],
        "conditional_software_MAC_upper_bound": out * n,
        "note": "Fallback list/index cost, COW, closures, RC, array construction and destruction are additional. Counts are before compiler optimization.",
    }


if __name__ == "__main__":
    p = argparse.ArgumentParser()
    for name, default in (("batch", 2), ("m", 50), ("n", 100), ("p", 50)):
        p.add_argument("--" + name, type=int, default=default)
    a = p.parse_args()
    if min(a.batch, a.m, a.n, a.p) < 0:
        p.error("dimensions are Nat")
    print(json.dumps(counts(a.batch, a.m, a.n, a.p), indent=2))
