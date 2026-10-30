"""Exact finite arithmetic discriminator, not a Lean/runtime performance claim.

Self-authored R27 source. No retired-submission implementation is copied.
Run with --quick for fixtures and small complete-call proxy timings.
Python bigint costs are only diagnostic; Lean's GMP/runtime must be measured.
"""
from __future__ import annotations

import argparse
import hashlib
import json
import platform
import random
import statistics
import time
from datetime import datetime, timezone
from pathlib import Path


def dot_reference(a: list[int], w: list[list[int]]) -> list[int]:
    return [sum(x * y for x, y in zip(a, row)) for row in w]


def pack_signed(values: list[int], width: int) -> int:
    """Horner evaluation; negative digits are legal, no per-digit clipping."""
    out = 0
    for x in reversed(values):
        out = (out << width) + x
    return out


def pack_signed_dc(values: list[int], width: int) -> int:
    """Balanced concatenation: avoids repeated copying of the whole prefix."""
    def go(lo: int, hi: int) -> int:
        if hi - lo <= 8:
            return pack_signed(values[lo:hi], width)
        mid = (lo + hi) // 2
        return go(lo, mid) + (go(mid, hi) << ((mid - lo) * width))
    return go(0, len(values))


def parameters(a: list[list[int]], w: list[list[int]]) -> tuple[int, int]:
    ma = max((abs(v) for row in a for v in row), default=0)
    mw = max((abs(v) for row in w for v in row), default=0)
    bound = len(w[0]) * ma * mw if w else 0
    # Strict bound: |coefficient| < B/2 even for equality at the worst case.
    width = max(2, bound.bit_length() + 1)
    return width, 1 << (width - 1)


def unpack_centered(value: int, width: int, count: int) -> list[int]:
    # Add a HALF digit in every slot. All resulting digits lie in [0, B).
    half = 1 << (width - 1)
    mask = (1 << width) - 1
    offset = ((1 << (width * count)) - 1) // mask * half if count else 0
    raw = value + offset
    if raw < 0:
        raise AssertionError("invalid digit bound: packed shifted value is negative")
    out = []
    for _ in range(count):
        out.append((raw & mask) - half)
        raw >>= width
    if raw:
        raise AssertionError("invalid digit bound: carry crossed the highest digit")
    return out


def packed_outputs(a: list[list[int]], w: list[list[int]], tile: int = 0,
                   dc: bool = False) -> list[list[int]]:
    """Include parameter scan, packing, multiply/add, bias mask and extraction.

    w stores output rows. Each input coordinate gets one packed output vector;
    each input row requires k bigint-by-scalar multiplications, not k*m Lean MACs.
    """
    if not a or not w:
        return [[] for _ in a]
    n = len(w)
    k = len(a[0])
    width, _ = parameters(a, w)
    tile = tile or n
    result = [[] for _ in a]
    pack = pack_signed_dc if dc else pack_signed
    for start in range(0, n, tile):
        end = min(start + tile, n)
        cache = [pack([w[j][i] for j in range(start, end)], width) for i in range(k)]
        for r, row in enumerate(a):
            total = sum(x * y for x, y in zip(row, cache))
            result[r].extend(unpack_centered(total, width, end - start))
    return result


def kronecker_outputs(a: list[list[int]], w: list[list[int]], tile: int = 0) -> list[list[int]]:
    """Cross-coordinate convolution control; all padding/offset work is included."""
    if not a or not w:
        return [[] for _ in a]
    k, n = len(a[0]), len(w)
    ma = max(abs(v) for row in a for v in row)
    mw = max(abs(v) for row in w for v in row)
    width = max(1, (k * (2 * ma) * (2 * mw)).bit_length())
    mask = (1 << width) - 1
    stride = 2 * k - 1
    tile = tile or n
    result = [[] for _ in a]
    packed_a = [pack_signed_dc([v + ma for v in row], width) for row in a]
    sa = [sum(row) for row in a]
    for start in range(0, n, tile):
        end = min(start + tile, n)
        bands = []
        for j in range(start, end):
            bands.extend(v + mw for v in reversed(w[j]))
            if j + 1 < end:
                bands.extend([0] * (k - 1))
        pw = pack_signed_dc(bands, width)
        sw = [sum(w[j]) for j in range(start, end)]
        for r, pa in enumerate(packed_a):
            prod = pa * pw
            result[r].extend(((prod >> ((j * stride + k - 1) * width)) & mask)
                             - mw * sa[r] - ma * sw[j] - k * ma * mw
                             for j in range(end - start))
    return result


def run_fixtures() -> dict:
    rng = random.Random(0xC2701)
    count = 0
    shapes = [(1, 1, 1), (1, 2, 3), (2, 3, 2), (3, 7, 9), (8, 17, 31)]
    modes = ["random", "max", "min", "alternating", "zero", "cancellation"]
    for rows, k, n in shapes:
        for bits in [1, 7, 24, 31, 61, 149, 277]:
            bound = (1 << bits) - 1
            for mode in modes:
                a = [[rng.randrange(-bound, bound + 1) for _ in range(k)] for _ in range(rows)]
                w = [[rng.randrange(-bound, bound + 1) for _ in range(k)] for _ in range(n)]
                if mode == "max":
                    a, w = [[bound] * k for _ in range(rows)], [[bound] * k for _ in range(n)]
                elif mode == "min":
                    a, w = [[-bound] * k for _ in range(rows)], [[bound] * k for _ in range(n)]
                elif mode == "alternating":
                    a = [[bound * (-1) ** i for i in range(k)] for _ in range(rows)]
                elif mode == "zero":
                    a = [[0] * k for _ in range(rows)]
                elif mode == "cancellation":
                    a = [[1] * k for _ in range(rows)]
                    w = [[bound * (-1) ** i if i + 1 < k or k % 2 == 0 else 0
                          for i in range(k)] for _ in range(n)]
                expected = [dot_reference(row, w) for row in a]
                for tile in [1, 4, 16, 0]:
                    assert packed_outputs(a, w, tile) == expected, (rows, k, n, bits, mode, tile)
                    assert packed_outputs(a, w, tile, True) == expected
                    assert kronecker_outputs(a, w, tile) == expected
                    count += 3
    # A too-small digit width makes carry/borrow corruption observable.
    bad = None
    try:
        wrong = unpack_centered(pack_signed([8, -8], 4), 4, 2)
        if wrong != [8, -8]:
            bad = {"width": 4, "coefficients": [8, -8], "decoded": wrong}
    except AssertionError as e:
        bad = {"width": 4, "coefficients": [8, -8], "rejection": str(e)}
    assert bad is not None
    return {"checks": count, "finite_domain_only": True, "strict_bound_negative_control": bad}


def timing(fn, rounds: int = 3) -> dict:
    values = []
    check = None
    for _ in range(rounds):
        start = time.perf_counter_ns()
        out = fn()
        values.append(time.perf_counter_ns() - start)
        check = hashlib.sha256(repr(out).encode()).hexdigest()
    return {"ns": values, "median_ns": statistics.median(values), "output_sha256": check}


def benchmark(quick: bool) -> list[dict]:
    rng = random.Random(0xC2702)
    shapes = [(1, 64, 64), (8, 64, 64), (1, 192, 96), (8, 192, 96), (16, 96, 192)]
    widths = [24, 31] if quick else [8, 24, 31, 48, 277]
    results = []
    for rows, k, n in shapes:
        for bits in widths:
            bound = (1 << bits) - 1
            a = [[rng.randrange(-bound, bound + 1) for _ in range(k)] for _ in range(rows)]
            w = [[rng.randrange(-bound, bound + 1) for _ in range(k)] for _ in range(n)]
            entries = {"scalar_python": timing(lambda: [dot_reference(row, w) for row in a])}
            for tile in [4, 16, 64, 0]:
                entries[f"balanced_{tile or 'all'}"] = timing(lambda: packed_outputs(a, w, tile))
            entries["balanced_dc_all"] = timing(lambda: packed_outputs(a, w, 0, True))
            if bits <= 31:
                entries["kronecker_16"] = timing(lambda: kronecker_outputs(a, w, 16))
            checksums = {v["output_sha256"] for v in entries.values()}
            assert len(checksums) == 1
            width, _ = parameters(a, w)
            results.append({"shape": [rows, k, n], "factor_bits": bits, "digit_bits": width,
                            "packed_weight_bytes_lower_bound": (k * n * width + 7) // 8,
                            "methods": entries})
    return results


def main() -> None:
    p = argparse.ArgumentParser()
    p.add_argument("--quick", action="store_true")
    p.add_argument("--output", type=Path, default=Path(__file__).with_name("packed-model-result.json"))
    args = p.parse_args()
    start = datetime.now(timezone.utc).isoformat()
    data = {"status": "FINITE_MODEL_AND_PYTHON_COST_PROXY_ONLY", "start_utc": start,
            "python": platform.python_version(), "platform": platform.platform(),
            "source_sha256": hashlib.sha256(Path(__file__).read_bytes()).hexdigest(),
            "scope_exclusions": ["not Lean native cost", "not full 12 gate", "not current champion comparison",
                                 "no float decoding, bias alignment, output rounding, exceptional fallback yet"],
            "fixtures": run_fixtures(), "benchmarks": benchmark(args.quick)}
    data["end_utc"] = datetime.now(timezone.utc).isoformat()
    args.output.write_text(json.dumps(data, indent=2), encoding="utf-8")
    print(json.dumps({"output": str(args.output), "fixtures": data["fixtures"],
                      "benchmarks": len(data["benchmarks"])}))


if __name__ == "__main__":
    main()
