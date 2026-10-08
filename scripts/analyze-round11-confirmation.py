"""Recheck two explicitly named frozen R11 gap-groups runs against pipeline and shadow."""
from pathlib import Path
import argparse
import json
import statistics
import subprocess
import sys
import tempfile

ROOT = Path(__file__).resolve().parents[1]
DISCOVERY_RUNS = {"37729066378"}
EXCLUDED_BATCHES = {"groups-e", "confirm-f", "confirm-g"}
METHODS = {
    "r11-gap-groups": ("6ef07be874052d23fbe3cdca8de7e311e82a306338a93f70389fe35006e99992",
                       "e0ded4248a894e8c53bc1ce644c7c3f5c6681fe3c06eaab597caf10a5bf472db"),
    "r10-finder-pipeline-proof": ("b74ae5fd9575101b6b34b9f2718d8835adca770c6765c30b33bb895878ba1adf",
                                  "e0ded4248a894e8c53bc1ce644c7c3f5c6681fe3c06eaab597caf10a5bf472db"),
    "pipeline-shadow": ("b74ae5fd9575101b6b34b9f2718d8835adca770c6765c30b33bb895878ba1adf",
                        "e0ded4248a894e8c53bc1ce644c7c3f5c6681fe3c06eaab597caf10a5bf472db"),
}
CANDIDATE, PARENT, SHADOW = "r11-gap-groups", "r10-finder-pipeline-proof", "pipeline-shadow"


def load(path):
    return json.loads(path.read_bytes())


def need(ok, message):
    if not ok:
        raise ValueError(message)


def inspect_run(folder, expected_id, expected_batch):
    folder = folder.resolve()
    need(folder.is_dir() and folder.name == "gate", f"not a final gate directory: {folder}")
    state, ci = load(folder / "state.json"), load(folder / "ci-run.json")
    rid = str(state["run_id"])
    need(rid == expected_id and rid not in DISCOVERY_RUNS,
         f"refusing run {rid}; it is not the explicitly designated new confirmation")
    need(state["batch"] == expected_batch and expected_batch not in EXCLUDED_BATCHES and
         state["phase"] == "gate", f"wrong batch/phase for {rid}")
    need(str(ci["databaseId"]) == rid and ci["status"] == "completed" and ci["conclusion"] == "success",
         f"CI run {rid} is mismatched, incomplete, or unsuccessful")
    need(ci["headSha"] == state["git_sha"], f"run {rid} head SHA does not match its state")
    need(state.get("failures") == [], f"state.failures is not empty in run {rid}")
    entries = {e["name"]: e for e in state["spec"]["entries"]}
    for name, (rust, lean) in METHODS.items():
        need(name in entries and entries[name]["hashes"] == {"parse.rs": rust, "Parse.lean": lean},
             f"unexpected source/proof pair for {name} in {rid}")
    need(not entries[CANDIDATE].get("control") and entries[PARENT].get("control") and entries[SHADOW].get("control"),
         f"candidate/control labels are wrong in {rid}")
    need(entries[CANDIDATE].get("anchor") == "public361" and
         entries[CANDIDATE].get("comparison_baseline") == PARENT and
         entries[CANDIDATE].get("expected_equivalent_to") == PARENT,
         f"candidate comparison contract changed in {rid}")
    eq = load(folder / "equivalence-research.json")
    eq_rows = [row for row in eq.get("cases", []) if row.get("candidate") == CANDIDATE]
    need(eq.get("returncode") == 0 and len(eq_rows) == 1 and
         eq_rows[0].get("reference") == PARENT and eq_rows[0].get("cases") == 444 and
         eq_rows[0].get("different_or_failed") == 0,
         f"run {rid} did not pass the declared 444-case finite equivalence check")
    names = [e["name"] for e in state["spec"]["entries"]]
    need(names.index(PARENT) < names.index(SHADOW) < names.index(CANDIDATE),
         f"block-1 method order changed in {rid}")
    metrics = state["metrics"]
    keys = [(m["candidate"], m["round"]) for m in metrics]
    need(len(keys) == len(set(keys)), f"duplicate method/block in {rid}")
    for name in (CANDIDATE, PARENT, SHADOW):
        need(sorted(m["round"] for m in metrics if m["candidate"] == name) == [1, 2],
             f"{rid} must have exactly blocks 1 and 2 for {name}")
    for block, ordered in ((1, (PARENT, SHADOW, CANDIDATE)), (2, (CANDIDATE, SHADOW, PARENT))):
        sequence = [m["candidate"] for m in metrics if m["round"] == block]
        need([sequence.index(n) for n in ordered] == sorted(sequence.index(n) for n in ordered),
             f"block {block} order is not counterbalanced in {rid}")
        stamps = []
        for name in ordered:
            raw = [json.loads(s) for s in (folder / f"round{block}-{name}.jsonl").read_text().splitlines()]
            meta, files = raw[0], [r for r in raw if r.get("kind") == "file"]
            need(meta["corpus"] == "corpus-stage1" and len(files) == 28 and
                 sum(r["raw_bytes"] for r in files) == 15_930_000,
                 f"{rid} block {block} is not the complete 28-file corpus")
            need(meta["warmup_rounds"] == 1 and meta["measured_rounds"] == 11 and
                 meta["methods"][name]["source_sha256"] == METHODS[name][0],
                 f"bad reps/source hash for {rid} block {block} {name}")
            stamps.append(float(meta["started_at_unix"]))
        need(stamps == sorted(stamps) and len(set(stamps)) == 3,
             f"raw start times do not confirm block {block} order in {rid}")
    finite = {"scope": eq.get("scope"), "returncode": eq["returncode"],
              "candidate": CANDIDATE, "reference": PARENT,
              "cases": eq_rows[0]["cases"], "different_or_failed": eq_rows[0]["different_or_failed"],
              "full_gate": False}
    return folder, state, ci, finite


def output_equality(folder, run_id, block, left, right):
    def files(name):
        raw = [json.loads(s) for s in (folder / f"round{block}-{name}.jsonl").read_text().splitlines()]
        return {r["file"]: r for r in raw if r.get("kind") == "file"}
    a, b = files(left), files(right)
    need(set(a) == set(b) and len(a) == 28, f"file list mismatch in {run_id} block {block}")
    changed = []
    for filename in a:
        x, y = a[filename], b[filename]
        need(x["sha256"] == y["sha256"], f"input hash mismatch for {filename}")
        x, y = x["methods"][left], y["methods"][right]
        if any(x[k] != y[k] for k in ("output_bytes", "output_sha256", "tokens_sha256")):
            changed.append(filename)
    return {"equal": not changed, "changed_files": changed, "files": len(a)}


def main():
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument("receipts", nargs=2, type=Path, metavar="FINAL_GATE_DIR")
    ap.add_argument("--expected-run", action="append", required=True, metavar="BATCH=RUN_ID",
                    help="exactly twice and in receipt-path order; explicitly designates the two new runs")
    ap.add_argument("--capture", type=Path, default=ROOT / "evidence/round11/official-final")
    ap.add_argument("--output", type=Path, required=True, help="write the JSON report as UTF-8 bytes")
    args = ap.parse_args()
    try:
        expected = []
        for value in args.expected_run:
            batch, sep, rid = value.partition("=")
            need(bool(sep and batch.startswith("confirm-") and rid.isdecimal()),
                 f"invalid --expected-run {value!r}; expected confirm-name=CI_RUN_ID")
            need(batch not in EXCLUDED_BATCHES and rid not in DISCOVERY_RUNS,
                 f"selection run {value!r} cannot count as confirmation")
            expected.append((batch, rid))
        need(len(expected) == 2 and len({b for b, _ in expected}) == 2 and
             len({r for _, r in expected}) == 2, "provide exactly two distinct --expected-run batch=id values")
        checked = [inspect_run(path, rid, batch)
                   for path, (batch, rid) in zip(args.receipts, expected, strict=True)]
        by_id = {str(state["run_id"]): (folder, state, ci, finite) for folder, state, ci, finite in checked}
        expected_ids = {rid for _, rid in expected}
        need(set(by_id) == expected_ids, f"receipts do not match explicit run IDs {sorted(expected_ids)}")
        commits = {state["git_sha"] for _, state, _, _ in checked}
        need(len(commits) == 1, "the two confirmation runs must use the same frozen commit")
        ordered_paths = [by_id[rid][0] for rid in sorted(expected_ids)]
        with tempfile.TemporaryDirectory(prefix="r11-confirm-") as tmp:
            output = Path(tmp) / "summary.json"
            cmd = [sys.executable, str(ROOT / "scripts/analyze-round11.py"),
                   *(str(p) for p in ordered_paths), "--capture", str(args.capture.resolve()),
                   "--output", str(output), "--final"]
            proc = subprocess.run(cmd, cwd=ROOT, capture_output=True, text=True, check=False)
            need(proc.returncode == 0, "analyze-round11 rejected receipts: " + proc.stderr[-2000:])
            summary = load(output)

        capture_dir = args.capture.resolve()
        capture_receipt = load(capture_dir / "receipt.json")
        competition = load(capture_dir / "competition.json")
        snapshot_id = str(capture_receipt["snapshot_id"])
        capture_context = capture_receipt["competition_context"]
        need(str(competition["current_snapshot_id"]) == snapshot_id and
             str(competition["context"]["snapshot_id"]) == snapshot_id and
             str(summary["snapshot"]["snapshot_id"]) == snapshot_id and
             summary["snapshot"].get("freshness") == capture_context.get("freshness"),
             "capture receipt, competition context, scorer snapshot, or freshness fields differ")
        need(summary["status"] == "COMPLETED_FINAL_ARTIFACTS_RECOMPUTED",
             "analysis-round11 did not recompute completed final artifacts")
        groups = [g for g in summary["candidates"] if g["source_sha256"] == METHODS[CANDIDATE][0]]
        need(len(groups) == 1, "expected one source group for gap-groups")
        group = groups[0]
        need(group["candidate"] == CANDIDATE and group["independent_runs"] == 2 and group["blocks"] == 4,
             "analysis must aggregate only the two new runs and four measured blocks")
        run_rows = {str(r["run_id"]): r for r in group["runs"]}
        shadows = {str(r["run_id"]): r for r in summary["pipeline_shadows"]}
        need(set(run_rows) == expected_ids and set(shadows) == expected_ids,
             "candidate or pipeline-shadow evidence included an unexpected/missing run")
        need(all(r["proof_sha256"] == METHODS[CANDIDATE][1] for r in run_rows.values()),
             "Rust source was grouped across different Lean proofs")

        per_run = []
        batch_by_id = {rid: batch for batch, rid in expected}
        for rid in sorted(expected_ids):
            folder, state, ci, finite = by_id[rid]
            candidate = run_rows[rid]
            shadow = shadows[rid]
            need(candidate["blocks"] == [1, 2] and shadow["blocks"] == [1, 2],
                 f"missing block for run {rid}")
            blocks = []
            for i, block in enumerate((1, 2)):
                c_over_p = candidate["relative_to_parent"][i]
                s_over_p = 1 + shadow["changes_pct"][i] / 100
                c_over_s = c_over_p / s_over_p
                blocks.append({
                    "block": block,
                    "candidate_vs_pipeline": {"ratio": c_over_p, "change_pct": 100 * (c_over_p - 1)},
                    "candidate_vs_pipeline_shadow": {"ratio": c_over_s, "change_pct": 100 * (c_over_s - 1)},
                    "pipeline_shadow_vs_pipeline": {"ratio": s_over_p, "change_pct": shadow["changes_pct"][i]},
                    "candidate_matches_pipeline": output_equality(folder, rid, block, CANDIDATE, PARENT),
                    "shadow_matches_pipeline": output_equality(folder, rid, block, SHADOW, PARENT),
                })
            per_run.append({
                "run_id": rid, "batch": batch_by_id[rid], "commit": ci["headSha"],
                "ci_status": ci["status"], "ci_conclusion": ci["conclusion"], "blocks": blocks,
                "state_failures": state["failures"], "finite_equivalence": finite,
                "mean_block_change_pct": {
                    key: statistics.mean(b[key]["change_pct"] for b in blocks)
                    for key in ("candidate_vs_pipeline", "candidate_vs_pipeline_shadow", "pipeline_shadow_vs_pipeline")
                },
                "full_gate_accepted": group["full_gate_accepted"],
            })
        means = [r["mean_block_change_pct"] for r in per_run]
        faster = all(r["candidate_vs_pipeline"] < 0 and r["candidate_vs_pipeline_shadow"] < 0 for r in means)
        output_equal = all(b["candidate_matches_pipeline"]["equal"] for r in per_run for b in r["blocks"])
        shadow_equal = all(b["shadow_matches_pipeline"]["equal"] for r in per_run for b in r["blocks"])
        point = group["same_family"]["candidate"]
        if not shadow_equal:
            signal = "CONTROL_OUTPUT_MISMATCH_RECHECK_REQUIRED"
        elif point["on_updated_geometric_frontier"] and faster and output_equal:
            signal = "PROJECTED_FRONTIER_WITH_FASTER_RUN_MEANS"
        elif point["on_updated_geometric_frontier"] and not output_equal:
            signal = "FRONTIER_PROJECTION_WITH_OUTPUT_DIFFERENCE_REQUIRES_EXACT_GATE_REVIEW"
        elif faster and not output_equal:
            signal = "FASTER_DIRECTION_ONLY_OUTPUT_EQUALITY_NOT_MET"
        elif faster:
            signal = "FASTER_DIRECTION_BUT_STILL_DOMINATED"
        elif point["on_updated_geometric_frontier"]:
            signal = "FRONTIER_PROJECTION_WITH_MIXED_TIMING_DIRECTION"
        else:
            signal = "MIXED_OR_NO_CONSISTENT_FASTER_SIGNAL"
        result = {
            "status": "TWO_RUN_DIRECTIONAL_RECHECK",
            "frozen_commit": next(iter(commits)),
            "runs": per_run,
            "equal_run_mean_change_pct": {
                key: statistics.mean(r["mean_block_change_pct"][key] for r in per_run)
                for key in ("candidate_vs_pipeline", "candidate_vs_pipeline_shadow", "pipeline_shadow_vs_pipeline")
            },
            "candidate_output_matches_pipeline_all_blocks": output_equal,
            "pipeline_shadow_output_matches_pipeline_all_blocks": shadow_equal,
            "candidate_signal": signal,
            "official_capture": {
                "snapshot_id": snapshot_id,
                "computed_at": capture_context["computed_at"],
                "freshness": capture_context["freshness"],
                "freshness_reason": capture_context.get("freshness_reason"),
                "weights_snapshot_id": capture_receipt.get("weights_context", {}).get("snapshot_id"),
                "weights_same_snapshot": capture_receipt.get("weights_same_snapshot"),
            },
            "candidate_projection": point,
            "full_gate_accepted": group["full_gate_accepted"],
            "selection_receipts_excluded": True,
            "limits": [
                "Two-run directional evidence only; no confidence interval or statistical significance claim.",
                "Pipeline-shadow is an observed control drift, not a correction factor or candidate.",
                "Finite public output equality and projected geometry do not replace an accepted exact-pair full gate.",
            ],
        }
        payload = (json.dumps(result, ensure_ascii=False, indent=2, allow_nan=False) + "\n").encode("utf-8")
        args.output.parent.mkdir(parents=True, exist_ok=True)
        args.output.write_bytes(payload)
        print(json.dumps({"status": result["status"], "output": str(args.output.resolve()),
                          "candidate_signal": signal, "snapshot_id": snapshot_id}, ensure_ascii=False))
        return 0
    except Exception as exc:
        print(json.dumps({"status": "REJECTED_INPUT_OR_INCOMPLETE_RECEIPT", "reason": str(exc)}, indent=2))
        return 2


if __name__ == "__main__":
    raise SystemExit(main())
