#!/usr/bin/env python3
"""Additional R28 local affine parameter checks; not a benchmark.

The Row values below have mathematically consistent mean metadata, but are not
claimed to arise from complete stable input rows. This isolates the guarded
signed numerator and cell checker. No Lean execution or native timing occurs.

Usage from the delivered folder:
    python3 pressure_extra.py --model r28_exact_model.py --json pressure_extra_results.json
"""
from __future__ import annotations

import argparse
from fractions import Fraction
import importlib.util
import json
from pathlib import Path
import random
import sys


def run(model_path: Path, seed: int = 610302, cases: int = 12000) -> dict:
    spec = importlib.util.spec_from_file_location("r28_review_target", model_path)
    if spec is None or spec.loader is None:
        raise RuntimeError(f"Cannot import model: {model_path}")
    m = importlib.util.module_from_spec(spec)
    sys.modules[spec.name] = m
    spec.loader.exec_module(m)
    r = random.Random(seed)
    counts: dict[str, int] = {}
    accepted = maxbits = 0
    for _ in range(cases):
        n = r.randrange(1, 4096)
        b0 = r.randrange(0, 254)
        total = r.randrange(-(1 << 60) + 1, 1 << 60)
        iw = r.randrange(b0, min(b0 + 24, 253) + 1)
        w = ((iw + 1) << 23) | r.getrandbits(23) | (m.SIGN if r.getrandbits(1) else 0)
        g = (r.randrange(0, 255) << 23) | r.getrandbits(23) | (m.SIGN if r.getrandbits(1) else 0)
        b = (r.randrange(0, 255) << 23) | r.getrandbits(23) | (m.SIGN if r.getrandbits(1) else 0)
        if r.randrange(10) == 0:
            w = m.SIGN if r.getrandbits(1) else 0
        if r.randrange(10) == 0:
            g = m.SIGN if r.getrandbits(1) else 0
        if r.randrange(10) == 0:
            b = m.SIGN if r.getrandbits(1) else 0
        dw = (r.randrange(1, 255) << 23) | r.getrandbits(23)
        row = m.Row(n, b0, total, dw,
                    Fraction(total, n) * m.pow2(b0 - 149), Fraction(0))
        data, reason = m.construct(row, w, g, b)
        counts[reason] = counts.get(reason, 0) + 1
        if data:
            _, p, _, _ = data
            maxbits = max(maxbits, m.join(p).bit_length())
            v = ((m.finite_value(w) - row.mean) * m.finite_value(g)
                 / m.finite_value(dw) + m.finite_value(b))
            truth = m.round32(v)
            for q in [truth, truth ^ 1, truth ^ m.SIGN, r.getrandbits(32)]:
                if m.limb_cell(*data, q):
                    assert q == truth
                    accepted += 1
    return {
        "status": "FINITE_MODEL_PASS",
        "seed": seed,
        "scope": "Synthetic consistent local affine metadata; not asserted as complete stable rows.",
        "cases": cases,
        "counts": counts,
        "cell_accepts": accepted,
        "max_constructed_p_bits": maxbits,
        "false_accepts": 0,
        "lean_status": "NOT_COMPILED",
        "native_timing_status": "NOT_RUN",
    }


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--model", type=Path,
                        default=Path(__file__).with_name("r28_exact_model.py"))
    parser.add_argument("--seed", type=int, default=610302)
    parser.add_argument("--cases", type=int, default=12000)
    parser.add_argument("--json", type=Path)
    args = parser.parse_args()
    result = run(args.model, args.seed, args.cases)
    encoded = json.dumps(result, ensure_ascii=False, indent=2) + "\n"
    if args.json:
        args.json.write_text(encoded, encoding="utf-8")
    print(encoded, end="")
