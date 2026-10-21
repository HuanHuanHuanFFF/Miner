"""Read a collected H16 receipt and compare every experiment with its matched base.

Official axes are recomputed by collect-round4.py first. This report adds H16
relative changes, same-byte controls and finite-equivalence/diagnostic status;
it does not infer proof, admission, or rewards from a green screening workflow.
"""
from __future__ import annotations
import argparse
import hashlib
import json
from pathlib import Path
import statistics

ROOT = Path(__file__).resolve().parents[1]


def analyze(folder):
    state = json.loads((folder / "state.json").read_text())
    baseline = state["spec"].get("comparison_baseline", "h16-base")
    entries = {e["name"]: e for e in state["spec"]["entries"]}
    metrics = {(m["candidate"], m["round"]): m for m in state["metrics"]}
    assert baseline in entries
    eq_path = folder / "equivalence-research.json"
    finite = json.loads(eq_path.read_text()) if eq_path.exists() else {}
    finite_by_name = {r["candidate"]: r for r in finite.get("cases", [])}
    result = []
    for name, entry in entries.items():
        if entry.get("control") and name != "h16-shadow":
            continue
        assert hashlib.sha256((ROOT / entry["path"] / "parse.rs").read_bytes()).hexdigest() == entry["hashes"]["parse.rs"]
        blocks = sorted(b for (n, b) in metrics if n == name and (baseline, b) in metrics)
        if not blocks:
            result.append({"candidate": name, "status": "NO_PAIRED_MEASUREMENT"})
            continue
        changes = [100 * (metrics[name, b]["time"] / metrics[baseline, b]["time"] - 1) for b in blocks]
        def files(method):
            raw = map(json.loads, (folder / f"round{blocks[0]}-{method}.jsonl").read_text().splitlines())
            return {r["file"]: r for r in raw if r["kind"] == "file"}
        before, after = files(baseline), files(name)
        assert before.keys() == after.keys() and len(before) == 28
        differences = []
        for filename, row in after.items():
            ref = before[filename]
            assert ref["sha256"] == row["sha256"]
            a, b = row["methods"][name], ref["methods"][baseline]
            if any(a[k] != b[k] for k in ("tokens_sha256", "output_sha256", "output_bytes")):
                differences.append({"file": filename, "output_byte_delta": a["output_bytes"] - b["output_bytes"], "tokens_equal": a["tokens_sha256"] == b["tokens_sha256"]})
        result.append({"candidate": name, "source_sha256": entry["hashes"]["parse.rs"], "blocks": blocks,
                       "paired_time_change_pct": changes, "mean_time_change_pct": statistics.mean(changes),
                       "public_time_axis": statistics.mean(metrics[name,b]["time"] for b in blocks),
                       "public_size_pct": metrics[name,blocks[0]]["size_pct"],
                       "size_change_pp": metrics[name,blocks[0]]["size_pct"] - metrics[baseline,blocks[0]]["size_pct"],
                       "public_token_and_output_equal": not differences, "changed_files": differences,
                       "finite_equivalence": finite_by_name.get(name), "gate": state.get("gates",{}).get(name)})
    diagnostic = folder / "interleaved/summary.json"
    aux = json.loads(diagnostic.read_text()) if diagnostic.exists() else {}
    if aux.get("status") == "AUXILIARY_DIAGNOSTIC_OK":
        assert aux["relative_baseline"] == baseline
    phases = [{"phase": p["phase"], "status": p.get("status"),
               "changes": [{"candidate": r["method"], "change_pct": r["same_denominator_axis_change_pct_vs_baseline"]}
                           for r in p.get("summary",[]) if r["method"] not in ("incumbent", baseline)]}
              for p in aux.get("phases",[])]
    return {"scope": "Public H16 relative measurements; finite equality and auxiliary timing are not proof or admission",
            "run_id": state["run_id"], "batch": state["batch"], "git_sha": state["git_sha"], "phase": state["phase"],
            "baseline": baseline, "failures": state["failures"], "candidates": result,
            "finite_check_status": {k: finite[k] for k in ("status", "returncode", "scope") if k in finite},
            "auxiliary_status": aux.get("status", "NOT_AVAILABLE"), "auxiliary_phases": phases}


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("receipt", type=Path)
    args = parser.parse_args()
    print(json.dumps(analyze(args.receipt), indent=2, ensure_ascii=False, allow_nan=False))
