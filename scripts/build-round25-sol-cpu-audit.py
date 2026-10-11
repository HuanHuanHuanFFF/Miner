"""Read-only numeric decomposition and static route audit of end4 screen A."""
from pathlib import Path
import argparse
import hashlib
import json
import statistics

ROOT = Path(__file__).resolve().parents[1]
RUN = ROOT / "evidence/round25/38124524718/screen-a/gate"
OUTPUT = ROOT / "evidence/round25/sol/end4-cpu-audit-a.json"
NAME = "r25-astra-end4"
PC_CHAIN_ROUTES = {0, 1, 10, 2, 4, 5, 12, 14, 15, 17, 18, 19, 20, 9}
FIXED = {800000: 5, 150000: 6, 900000: 7, 1300000: 11, 1100000: 12,
         1500000: 14, 1400000: 17, 700000: 19, 40000: 21, 28000: 22,
         12000: 23, 450000: 24}
FORMATS = {250000: {25, 27, 8}, 300000: {16, 3}, 350000: {20, 26},
           400000: {15, 4}, 500000: {2, 10, 0}, 600000: {13, 18},
           1000000: {1, 9}}


def digest(data):
    return hashlib.sha256(data).hexdigest()


def load(block, name):
    path = RUN / f"round{block}-{name}.jsonl"
    raw = path.read_bytes()
    data = [json.loads(line) for line in raw.splitlines() if line.strip()]
    meta = next(row for row in data if row.get("kind") == "meta")
    rows = {row["file"]: row for row in data if row.get("kind") == "file"}
    assert len(rows) == 28 and meta["measured_rounds"] == 11
    return rows, {"path": path.relative_to(ROOT).as_posix(), "sha256": digest(raw), "meta": meta}


def samples(method, key):
    values = [row[key] for row in method["reps"] if row["phase"] == "measured"]
    assert len(values) == 11
    return values


def med(values):
    return statistics.median(values)


def calculate():
    blocks = []
    inputs = []
    for block in (1, 2):
        parent_rows, parent_receipt = load(block, "combo")
        candidate_rows, candidate_receipt = load(block, NAME)
        inputs.extend([parent_receipt, candidate_receipt])
        groups = {}
        rows = []
        for file, old_row in parent_rows.items():
            new_row = candidate_rows[file]
            assert old_row["sha256"] == new_row["sha256"]
            assert old_row["raw_bytes"] == new_row["raw_bytes"]
            old = old_row["methods"]["combo"]
            new = new_row["methods"][NAME]
            oi = old_row["methods"]["incumbent"]
            ni = new_row["methods"]["incumbent"]
            assert oi["output_sha256"] == ni["output_sha256"]
            for value in (old, new, oi, ni):
                assert value["deterministic"] and not value["errors"]
            possible = {FIXED[old_row["raw_bytes"]]} if old_row["raw_bytes"] in FIXED else FORMATS.get(old_row["raw_bytes"], {28})
            same_tokens = old["tokens_sha256"] == new["tokens_sha256"]
            same_bytes = old["output_sha256"] == new["output_sha256"]
            if not possible & PC_CHAIN_ROUTES:
                group = "VERIFIED_STATIC_UNTOUCHED_ROUTE"
                assert same_tokens and same_bytes
            elif possible <= PC_CHAIN_ROUTES:
                group = "VERIFIED_STATIC_PC_CHAIN_ROUTE"
            elif not same_tokens or not same_bytes:
                group = "VERIFIED_TOKEN_DELTA_PROVES_PC_CHAIN_ROUTE"
            else:
                group = "UNKNOWN_MIXED_ROUTE_WITH_UNCHANGED_OUTPUT"
            op, oe = samples(old, "time_s"), samples(old, "encode_s")
            np, ne = samples(new, "time_s"), samples(new, "encode_s")
            old_inc = med(samples(oi, "total_s"))
            new_inc = med(samples(ni, "total_s"))
            # Counterfactual sample recompositions are diagnostics only. Pair
            # equal repetition indices across runs; never present as new timing.
            r00 = med([a + b for a, b in zip(op, oe)]) / old_inc
            r10 = med([a + b for a, b in zip(np, oe)]) / old_inc
            r01 = med([a + b for a, b in zip(op, ne)]) / old_inc
            r11_fixed = med([a + b for a, b in zip(np, ne)]) / old_inc
            r11 = med(samples(new, "total_s")) / new_inc
            assert abs(r00 - med(samples(old, "total_s")) / old_inc) < 1e-12
            assert abs(r11_fixed - med(samples(new, "total_s")) / old_inc) < 1e-12
            parser = ((r10 - r00) + (r11_fixed - r01)) / 2
            encoder = ((r01 - r00) + (r11_fixed - r10)) / 2
            denominator = r11 - r11_fixed
            total = r11 - r00
            assert abs(parser + encoder + denominator - total) < 1e-12
            row = {
                "file": file, "raw_bytes": old_row["raw_bytes"],
                "possible_original_route_ids": sorted(possible), "group": group,
                "same_tokens": same_tokens, "same_encoded_bytes": same_bytes,
                "candidate_parse_change_pct": (med(np) / med(op) - 1) * 100,
                "candidate_encode_change_pct": (med(ne) / med(oe) - 1) * 100,
                "candidate_total_change_pct": (med(samples(new, "total_s")) / med(samples(old, "total_s")) - 1) * 100,
                "incumbent_total_change_pct": (new_inc / old_inc - 1) * 100,
                "observed_public_axis_parent": r00,
                "observed_public_axis_candidate": r11,
                "equal_file_axis_delta": total / 28,
                "diagnostic_parser_shapley_delta": parser / 28,
                "diagnostic_encoder_shapley_delta": encoder / 28,
                "diagnostic_incumbent_denominator_delta": denominator / 28,
            }
            rows.append(row)
            g = groups.setdefault(group, {"files": [], "equal_file_axis_delta": 0,
                "diagnostic_parser_shapley_delta": 0, "diagnostic_encoder_shapley_delta": 0,
                "diagnostic_incumbent_denominator_delta": 0})
            g["files"].append(file)
            for key in ("equal_file_axis_delta", "diagnostic_parser_shapley_delta", "diagnostic_encoder_shapley_delta", "diagnostic_incumbent_denominator_delta"):
                g[key] += row[key]
        parent_axis = sum(row["observed_public_axis_parent"] for row in rows) / 28
        candidate_axis = sum(row["observed_public_axis_candidate"] for row in rows) / 28
        assert abs(sum(g["equal_file_axis_delta"] for g in groups.values()) - (candidate_axis - parent_axis)) < 1e-12
        blocks.append({"block": block, "parent_public_axis": parent_axis,
            "candidate_public_axis": candidate_axis,
            "observed_public_time_change_pct": (candidate_axis / parent_axis - 1) * 100,
            "groups": groups, "rows": rows})
    return {"status": "VERIFIED_RAW_TIMING_ARITHMETIC_AND_STATIC_ROUTE_SCOPE_NOT_CAUSAL_PROFILE",
        "run": "38124524718", "candidate": NAME, "candidate_rust_sha256": "03ec0aa4e617d622755e85324a9d4fbc77ef74e6572485b3170e2790681ed8e6",
        "input_receipts": inputs, "blocks": blocks,
        "diagnostic_method": "Four sample recompositions for candidate parser/encoder with old incumbent held fixed, equal repetition-index pairing across old/new processes. Two-player Shapley split of nonadditive median interaction; then actual incumbent-denominator difference. The components sum exactly to observed equal-file axis delta but are numeric attribution, not causal measurements, adjusted scores or a performance claim.",
        "route_method": "All possible format_id branches from exact original input length plus static bulk_parse map. If no possible route invokes pc_run1c, mark untouched. A token delta in a mixed route proves that the changed PC chain path executed. Unchanged output alone does not prove nonexecution.",
        "limits": ["One discovery runner and two original protocol blocks only", "Same output does not guarantee same compiler code/address/layout or timer environment", "No current assembly or insertion-frequency counters retained", "No hypothetical speed saving or score computed"]}


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("--check", action="store_true")
    args = parser.parse_args()
    result = calculate()
    data = (json.dumps(result, indent=2, ensure_ascii=False) + "\n").encode()
    if args.check:
        assert OUTPUT.read_bytes() == data
    else:
        assert not OUTPUT.exists(), OUTPUT
        OUTPUT.write_bytes(data)
    print(json.dumps({"status": result["status"], "file": OUTPUT.relative_to(ROOT).as_posix(),
        "blocks": [{"block": b["block"], "time_change_pct": b["observed_public_time_change_pct"],
            "groups": [{"group": k, "files": len(g["files"]), "axis_delta": g["equal_file_axis_delta"],
                "parser_delta": g["diagnostic_parser_shapley_delta"], "encoder_delta": g["diagnostic_encoder_shapley_delta"],
                "incumbent_delta": g["diagnostic_incumbent_denominator_delta"]} for k, g in b["groups"].items()]} for b in result["blocks"]]}))


if __name__ == "__main__":
    main()
