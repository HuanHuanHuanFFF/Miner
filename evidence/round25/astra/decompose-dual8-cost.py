"""Describe the existing same-run paired ratios; no new benchmark or causal correction."""
from pathlib import Path
import hashlib
import json

ROOT = Path(__file__).resolve().parents[3]
OUT = Path(__file__).resolve().parent
GATE = ROOT / "evidence/round25/38126014186/screen-c/gate"


def read(name, block):
    path = GATE / f"round{block}-{name}.jsonl"
    data = [json.loads(x) for x in path.read_text().splitlines() if x.strip()]
    meta = next(x for x in data if x["kind"] == "meta")
    rows = {x["file"]: x for x in data if x["kind"] == "file"}
    assert len(rows) == 28
    return {"path": path.relative_to(ROOT).as_posix(), "sha256": hashlib.sha256(path.read_bytes()).hexdigest(),
            "methods": meta["methods"], "rows": rows}


def median_rep(method):
    values = sorted((r for r in method["reps"] if r["phase"] == "measured"), key=lambda r: r["total_s"])
    assert len(values) == 11
    m = values[5]
    assert abs(m["time_s"] + m["encode_s"] - m["total_s"]) < 1e-10
    return {"parse_s": m["time_s"], "encode_s": m["encode_s"], "total_s": m["total_s"],
            "order_index": m["order_index"]}


def main():
    changed = {x["file"] for x in next(x for x in json.load(open(ROOT / "evidence/round25/feedback-c-native.json"))["summary"]
                                      if x["candidate"] == "r25-astra-dual8")["changed_files"]}
    analyses = []
    for block in (1, 2):
        parent = read("combo", block)
        for name in ("r25-astra-dual8", "r25-astra-dual8-shadow"):
            candidate = read(name, block)
            rows = []
            for file, pr in parent["rows"].items():
                cr = candidate["rows"][file]
                assert (pr["raw_bytes"], pr["sha256"]) == (cr["raw_bytes"], cr["sha256"])
                p, pi = [median_rep(pr["methods"][key]) for key in ("combo", "incumbent")]
                c, ci = [median_rep(cr["methods"][key]) for key in (name, "incumbent")]
                dp, dc = pi["total_s"], ci["total_s"]
                weight = 0.5 * (1 / dc + 1 / dp)
                parse = (c["parse_s"] - p["parse_s"]) * weight
                encode = (c["encode_s"] - p["encode_s"]) * weight
                denominator = 0.5 * (c["total_s"] + p["total_s"]) * (1 / dc - 1 / dp)
                paxis, caxis = p["total_s"] / dp, c["total_s"] / dc
                assert abs(parse + encode + denominator - (caxis - paxis)) < 1e-10
                rows.append({"file": file, "changed_output": file in changed, "input_sha256": pr["sha256"],
                             "parent": p, "candidate": c, "parent_incumbent": pi, "candidate_incumbent": ci,
                             "parent_axis": paxis, "candidate_axis": caxis,
                             "parse_axis_delta": parse / 28, "encode_axis_delta": encode / 28,
                             "paired_denominator_axis_delta": denominator / 28})
            pa = sum(r["parent_axis"] for r in rows) / 28
            ca = sum(r["candidate_axis"] for r in rows) / 28
            totals = {k: sum(r[k] for r in rows) for k in
                      ("parse_axis_delta", "encode_axis_delta", "paired_denominator_axis_delta")}
            fractions = {k.replace("axis_delta", "relative_pct_contribution"): v / pa * 100 for k, v in totals.items()}
            groups = {}
            for flag in (True, False):
                selected = [r for r in rows if r["changed_output"] == flag]
                groups["changed12" if flag else "unchanged16"] = {"files": len(selected), **{
                    k.replace("axis_delta", "relative_pct_contribution"): sum(r[k] for r in selected) / pa * 100 for k in totals}}
            analyses.append({"block": block, "candidate": name, "parent_axis": pa, "candidate_axis": ca,
                             "relative_total_change_pct": (ca / pa - 1) * 100, **fractions,
                             "groups": groups, "parent_receipt": {k: v for k, v in parent.items() if k != "rows"},
                             "candidate_receipt": {k: v for k, v in candidate.items() if k != "rows"},
                             "rows": rows})
    result = {"status": "VERIFIED_DESCRIPTIVE_SAME_RUN_RAW_COMPONENT_DECOMPOSITION", "run": "38126014186",
              "method": "For each original file/method choose its actual measured total-median rep and retain that rep's parse+encode. Symmetric two-order algebra separates numerator parse, numerator encode and independently paired incumbent denominator contributions. Sum is exactly the original axis difference.",
              "limits": "Descriptive accounting only, not a modified official score, causal attribution, confidence interval or recoverable speedup. Same-run candidate/parent executions are distinct paired processes; output-identical files can still differ in timing.",
              "analyses": analyses}
    (OUT / "dual8-existing-cost-decomposition.json").write_bytes((json.dumps(result, indent=2) + "\n").encode())
    print(json.dumps([{k: v for k, v in a.items() if k not in ("rows", "parent_receipt", "candidate_receipt")}
                      for a in analyses], indent=2))


if __name__ == "__main__":
    main()
