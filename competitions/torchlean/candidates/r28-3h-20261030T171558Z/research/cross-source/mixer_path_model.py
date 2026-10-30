"""Exact integer finite replay of old seen Mixer inputs, not native timing/proof.

Replays the actual public36 span guard and prepared signed128 arithmetic.
Output checksums are independently matched to the saved old native cohort.
Also measures guard26 *coverage*, never labels that count a speedup.
"""
from pathlib import Path
import collections
from datetime import datetime, timezone
import hashlib
import importlib.util
import json
import sys
import time

sys.dont_write_bytecode = True
HERE = Path(__file__).resolve().parent
ROOT = next(p for p in HERE.parents if (p / "AGENTS.md").is_file())
OLD = ROOT / "competitions/torchlean/candidates/r27-5h-20261029T194443Z/research/fp-proof/census"
spec = importlib.util.spec_from_file_location("old_seen_replay", OLD / "fp_replay-frozen.py")
r = importlib.util.module_from_spec(spec)
spec.loader.exec_module(r)
m = r.m
MASK64 = (1 << 64) - 1
MASK128 = (1 << 128) - 1


def metadata(words):
    lo, hi = 511, 0
    for word in words:
        mag = word & 0x7FFFFFFF
        lo = min(lo, ((mag - 1) & 0xFFFFFFFF) >> 23)
        hi = max(hi, mag >> 23)
    return max(0, lo - 1), max(0, hi - 1), hi


def prepared_value(word, minimum):
    sign, mantissa, index = m.fields(word)
    return sign * (mantissa << (index - minimum)) if mantissa else 0


def trace_dot(x, w, bias, meta_x, meta_w):
    mx, hx, ex = meta_x
    mw, hw, ew = meta_w
    sb, mb, ib = m.fields(bias)
    lo0 = mx + mw
    lo = min(lo0, 126 + ib) if mb else lo0
    hi = max(hx + hw, 126 + ib) if mb else hx + hw
    if ex == 255 or ew == 255 or ((bias >> 23) & 255) == 255 or hi < lo or hi - lo > 15:
        return "fallback_span", None
    d = mx + mw - lo
    acc = 0
    expected_sum = 0
    for a, b in zip(x, w):
        av = prepared_value(a, mx)
        bv = prepared_value(b, mw)
        exact = (av * bv) << d
        assert -(1 << 63) <= exact < (1 << 63)
        p = exact & MASK64
        high, low = acc >> 64, acc & MASK64
        low2 = (low + p) & MASK64
        high2 = (high - (p >> 63) + (low2 < low)) & MASK64
        acc = (high2 << 64) | low2
        expected_sum += exact
        assert acc == expected_sum & MASK128
    signed = acc - (1 << 128) if acc >> 127 else acc
    assert signed == expected_sum
    total = signed + (sb * mb << (149 + ib - lo) if mb else 0)
    output = m.round_ratio(total, 1, lo - 298)
    return "prepared_zero_shift" if d == 0 else "prepared_nonzero_shift", output


class Census:
    def __init__(self):
        self.stages = []
        self.norms = []

    def matrix(self, left, right, relu, stage):
        lm, rm = list(map(metadata, left)), list(map(metadata, right))
        counts = collections.Counter()
        out = []
        for a, ma in zip(left, lm):
            for b, mb in zip(right, rm):
                total = sum(m.key(x) * m.key(y) for x, y in zip(a, b))
                result = 0 if relu and total <= 0 else m.round_ratio(total, 1, -298)
                kind, got = trace_dot(a, b, 0, ma, mb)
                if got is not None:
                    assert got == result or (got & 0x7FFFFFFF == result & 0x7FFFFFFF == 0)
                counts[kind] += 1
                out.append(result)
        self.stages.append({"stage": stage, "rows": len(left), "k": len(left[0]), "outputs": len(right),
                            "macs": len(left)*len(right)*len(left[0]), "dot_paths": counts})
        return out

    def linear(self, x, rows, k, out, w, b, relu, stage):
        left = [x[i*k:(i+1)*k] for i in range(rows)]
        right = [w[j*k:(j+1)*k] for j in range(out)]
        lm, rm = list(map(metadata, left)), list(map(metadata, right))
        counts = collections.Counter()
        result = []
        fast_by_row = []
        for a, ma in zip(left, lm):
            fast_by_row.append([])
            for j, (v, mv) in enumerate(zip(right, rm)):
                total = sum(m.key(u)*m.key(z) for u, z in zip(a, v)) + (m.key(b[j]) << 149)
                expected = 0 if relu and total <= 0 else m.round_ratio(total, 1, -298)
                kind, got = trace_dot(a, v, b[j], ma, mv)
                if got is not None:
                    assert (0 if relu and got >> 31 else got) == expected
                counts[kind] += 1
                fast_by_row[-1].append(got is not None)
                result.append(expected)
        pairs = collections.Counter()
        for i in range(0, rows - 1, 2):
            for j, v in enumerate(right):
                if fast_by_row[i][j] and fast_by_row[i+1][j]:
                    pairs["eligible_pair_dots"] += 1
                    pairs["eligible_pair_terms"] += k
                    pairs["weight_zero_pair_terms"] += sum((word & 0x7FFFFFFF) == 0 for word in v)
        self.stages.append({"stage": stage, "rows": rows, "k": k, "outputs": out, "macs": rows*k*out,
                            "dot_paths": counts, "old_outer_prepared": rows >= 2,
                            "candidate_outer_prepared": rows >= 2 or (rows == 1 and k >= 64),
                            "prepare_items": (rows + out)*k, "paired_md2": pairs})
        return result


def main():
    started = datetime.now(timezone.utc).isoformat()
    begun = time.monotonic()
    cells = []
    root_seed = 26102901
    req_path = r.E / f"fp-word-conv6-{root_seed}-request.json"
    measurement_path = r.E / f"fp-word-conv6-{root_seed}-measurement.json"
    req = json.loads(req_path.read_bytes())
    measured = json.loads(measurement_path.read_bytes())["result"]
    original_norm = m.norm
    active = None

    def norm_capture(x, rows, n, g, b=None, census=None):
        stats = {"rows": 0, "stats_fast_nlt256": 0, "row_lengths": collections.Counter(),
                 "ks_distribution": collections.Counter(), **{f"cap{k}": collections.Counter() for k in (8, 26, 28)}}
        output = original_norm(x, rows, n, g, b, census=stats)
        active.norms.append({"n": n, "rows": rows, "stats": stats})
        return output

    m.norm = norm_capture
    for workload in req["workloads"]:
        for kind in ("normal", "wide", "sparse"):
            assert time.monotonic() - begun < 60, "bounded local finite-model budget"
            active = Census()
            output = r.run_cell("mixer", workload["seed"], workload["profile"], kind, active)
            cell = f"{workload['id']}|mixer:b1:{kind}"
            expected = measured["rounds"][0]["cells"][cell]["candidate_checksum"]
            actual = r.fnv(output)
            assert actual == expected, (cell, actual, expected)
            cells.append({"cell": cell, "seed": workload["seed"], "profile": workload["profile"],
                          "kind": kind, "checksum": actual, "old_native_checksum": expected,
                          "stages": active.stages, "normalization": active.norms})
    totals = collections.Counter()
    for cell in cells:
        for stage in cell["stages"]:
            totals["all_dot_macs"] += stage["macs"]
            for key, count in stage.get("paired_md2", {}).items():
                totals["md2_" + key] += count
            for path, count in stage["dot_paths"].items():
                totals[path + "_macs"] += count*stage["k"]
                if stage["stage"] == "classifier":
                    totals["classifier_" + path + "_macs"] += count*stage["k"]
            if stage["stage"] == "classifier":
                totals["classifier_macs"] += stage["macs"]
                totals["classifier_prepare_items"] += stage["prepare_items"]
        for norm in cell["normalization"]:
            for cap in (8, 26):
                totals[f"norm_cap{cap}_inner_fast"] += norm["stats"][f"cap{cap}"]["inner_fast"]
            totals["norm_outputs"] += norm["rows"]*norm["n"]
    result = {
        "state": "OLD_SEEN_EXACT_INTEGER_FINITE_MODEL_OUTPUTS_MATCH_OLD_NATIVE",
        "start_utc": started, "end_utc": datetime.now(timezone.utc).isoformat(),
        "elapsed_seconds": time.monotonic() - begun, "root_seed": root_seed,
        "cells": cells, "totals": totals,
        "source_sha256": hashlib.sha256(Path(__file__).read_bytes()).hexdigest(),
        "old_formula_sha256": hashlib.sha256(r.UTIL.read_bytes()).hexdigest(),
        "old_request_sha256": hashlib.sha256(req_path.read_bytes()).hexdigest(),
        "old_measurement_sha256": hashlib.sha256(measurement_path.read_bytes()).hexdigest(),
        "limits": ["Not actual Lean branch instrumentation or a proof", "MAC shares are not elapsed-time shares", "Batch1 old seen cohort only", "guard26 counts omit later rrsG/native-rounding fallbacks", "No new source gate or native performance is inferred"],
    }
    (HERE / "mixer-path-model.json").write_text(json.dumps(result, indent=2) + "\n", encoding="utf-8")
    print(json.dumps({"cells": len(cells), "elapsed_seconds": result["elapsed_seconds"], "totals": totals}, indent=2))


if __name__ == "__main__":
    main()
