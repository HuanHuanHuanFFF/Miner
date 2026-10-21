"""Recompute Round 10 record route contributions and same-run diagnostics.

This is a finite public-corpus measurement audit. It uses each method's own
paired-incumbent per-file median total time before comparing normalized axes.
It does not estimate private-corpus behavior or construct confidence bounds.
"""
from __future__ import annotations

import argparse
from collections import defaultdict
import hashlib
import json
from pathlib import Path
import statistics

ROOT = Path(__file__).resolve().parents[1]
DEFAULT_ROUTE_JSON = ROOT / "evidence/round10/37679261323/explore-a/gate/forward-diagnostics/forward.json"
DEFAULT_RECEIPTS = [
    ROOT / "evidence/round10/37684506856/struct-b/gate",
    ROOT / "evidence/round10/37688325585/row-c/gate",
    ROOT / "evidence/round10/37695105461/cpu-g/gate",
    ROOT / "evidence/round10/37695964878/restore-h/gate",
    ROOT / "evidence/round10/37698560245/pack-i/gate",
]


def sha_bytes(data: bytes) -> str:
    return hashlib.sha256(data).hexdigest()


def sha_file(path: Path) -> str:
    return sha_bytes(path.read_bytes())


def load_jsonl(path: Path):
    raw = path.read_bytes()
    manifest_path = path.parent / "raw-artifact-files.json"
    if manifest_path.exists():
        manifest = json.loads(manifest_path.read_text(encoding="utf-8"))
        record = manifest["files"].get(path.name)
        assert record is not None, f"raw file absent from receipt manifest: {path}"
        assert record["bytes"] == len(raw) and record["sha256"] == sha_bytes(raw), f"raw receipt hash mismatch: {path}"
    rows = [json.loads(line) for line in raw.decode("utf-8").splitlines() if line.strip()]
    assert rows and rows[0]["kind"] == "meta", f"missing metadata row: {path}"
    files = [row for row in rows[1:] if row.get("kind") == "file"]
    assert len(files) == 28, f"expected 28 file rows in {path}, got {len(files)}"
    by_sha = {row["sha256"]: row for row in files}
    assert len(by_sha) == 28, f"duplicate input SHA in {path}"
    return {"path": str(path), "sha256": sha_bytes(raw), "meta": rows[0], "files": by_sha}


def median_total(method_row):
    assert method_row["deterministic"] and not method_row["errors"]
    reps = [r for r in method_row["reps"] if r["phase"] == "measured"]
    assert len(reps) == 11 and all(r["total_s"] > 0 for r in reps)
    return statistics.median(r["total_s"] for r in reps)


def output_identity(method_row):
    return (method_row["tokens"], method_row["tokens_sha256"],
            method_row["output_bytes"], method_row["output_sha256"])


def load_route_hashes(path: Path):
    raw = path.read_bytes()
    report = json.loads(raw)
    corpus = report["corpus"]
    routes = {}
    for record in report["seed_records"]:
        if record.get("synthetic"):
            continue
        i = record["case"]
        assert 0 <= i < len(corpus)
        item = corpus[i]
        assert item["bytes"] == record["bytes"]
        digest = item["sha256"]
        assert digest not in routes, f"duplicate public D input SHA in route map: {digest}"
        routes[digest] = {"case": i, "row": record["row"], "bytes": item["bytes"]}
    assert len(routes) == 18, f"expected 18 public D routes from forward diagnostics, found {len(routes)}"
    return routes, {"path": str(path), "sha256": sha_bytes(raw), "run_id": report["run_id"],
                    "candidate_sha256": report["candidate_sha256"], "reference_sha256": report["reference_sha256"],
                    "public_d_route_count": len(routes)}


def read_method(folder: Path, block: int, name: str):
    path = folder / f"round{block}-{name}.jsonl"
    loaded = load_jsonl(path)
    assert name in loaded["meta"]["methods"], f"{name} missing from method metadata in {path}"
    return loaded


def compare_block(folder: Path, block: int, challenger: str, reference: str,
                  route_hashes: dict[str, dict], run_id: str):
    challenger_data = read_method(folder, block, challenger)
    reference_data = read_method(folder, block, reference)
    ch_meta, ref_meta = challenger_data["meta"], reference_data["meta"]
    assert ch_meta["corpus"] == ref_meta["corpus"] == "corpus-stage1"
    assert ch_meta["methods"]["incumbent"]["source_sha256"] == ref_meta["methods"]["incumbent"]["source_sha256"]
    ch_source = ch_meta["methods"][challenger]["source_sha256"]
    ref_source = ref_meta["methods"][reference]["source_sha256"]

    details = []
    for digest in sorted(challenger_data["files"]):
        cf = challenger_data["files"][digest]
        rf = reference_data["files"].get(digest)
        assert rf is not None, f"input SHA unmatched between {challenger} and {reference}: {digest}"
        assert cf["raw_bytes"] == rf["raw_bytes"] and cf["corpus"] == rf["corpus"]
        ch_method = cf["methods"][challenger]
        ref_method = rf["methods"][reference]
        assert output_identity(ch_method) == output_identity(ref_method), (
            f"token/output identity mismatch: {run_id} block {block} {challenger} vs {reference} {digest}")
        ch_inc = cf["methods"]["incumbent"]
        ref_inc = rf["methods"]["incumbent"]
        ch_axis = median_total(ch_method) / median_total(ch_inc)
        ref_axis = median_total(ref_method) / median_total(ref_inc)
        group = "D" if digest in route_hashes else "non_D"
        details.append({"input_sha256": digest, "bytes": cf["raw_bytes"], "group": group,
                        "challenger_axis": ch_axis, "reference_axis": ref_axis,
                        "contribution_pp": None,
                        "tokens": ch_method["tokens"], "tokens_sha256": ch_method["tokens_sha256"],
                        "output_bytes": ch_method["output_bytes"], "output_sha256": ch_method["output_sha256"]})
    assert len(details) == 28
    assert sum(1 for x in details if x["group"] == "D") == 18
    ref_axis = statistics.mean(x["reference_axis"] for x in details)
    ch_axis = statistics.mean(x["challenger_axis"] for x in details)
    for x in details:
        x["contribution_pp"] = 100 * (x["challenger_axis"] - x["reference_axis"]) / (28 * ref_axis)
    group_sums = {group: sum(x["contribution_pp"] for x in details if x["group"] == group)
                  for group in ("D", "non_D")}
    effect = 100 * (ch_axis / ref_axis - 1)
    assert abs(sum(group_sums.values()) - effect) < 1e-9
    return {
        "run_id": run_id, "block": block,
        "challenger": {"name": challenger, "source_sha256": ch_source,
                       "raw_jsonl_sha256": challenger_data["sha256"]},
        "reference": {"name": reference, "source_sha256": ref_source,
                      "raw_jsonl_sha256": reference_data["sha256"]},
        "paired_incumbent_source_sha256": ch_meta["methods"]["incumbent"]["source_sha256"],
        "input_files": len(details), "matched_input_sha_count": len({x["input_sha256"] for x in details}),
        "tokens_and_output_equal_all_files": True,
        "challenger_overall_axis": ch_axis, "reference_overall_axis": ref_axis,
        "overall_relative_change_pct": effect,
        "group_contribution_pp": group_sums,
        "group_contribution_sum_matches_overall_pp": sum(group_sums.values()),
        "per_file": details,
    }


def get_entries(state):
    return {e["name"]: e for e in state["spec"]["entries"]}


def selected_names(entries, prefix):
    return sorted(name for name in entries if name == prefix or name.startswith(prefix + "-"))


def summarize_runner(blocks):
    assert blocks
    return {"blocks": len(blocks),
            "overall_relative_change_pct": statistics.mean(b["overall_relative_change_pct"] for b in blocks),
            "group_contribution_pp": {g: statistics.mean(b["group_contribution_pp"][g] for b in blocks)
                                       for g in ("D", "non_D")}}


def add_main_comparisons(receipts, route_hashes, candidate_prefix, parent_name):
    by_source = defaultdict(list)
    receipt_details = []
    for folder in receipts:
        state = json.loads((folder / "state.json").read_text(encoding="utf-8"))
        entries = get_entries(state)
        names = selected_names(entries, candidate_prefix)
        assert names, f"no candidate matching {candidate_prefix!r} in {folder}"
        by_metric = defaultdict(list)
        for metric in state["metrics"]:
            by_metric[metric["candidate"]].append(metric["round"])
        assert parent_name in by_metric, f"parent {parent_name} absent in {folder}"
        for name in names:
            entry = entries[name]
            source = entry["hashes"]["parse.rs"]
            blocks = sorted(set(by_metric[name]) & set(by_metric[parent_name]))
            assert blocks, f"no same-block paired measurements for {name} in {folder}"
            runner_blocks = [compare_block(folder, b, name, parent_name, route_hashes, str(state["run_id"]))
                             for b in blocks]
            for block_result in runner_blocks:
                cm = next(m for m in state["metrics"] if m["candidate"] == name and m["round"] == block_result["block"])
                pm = next(m for m in state["metrics"] if m["candidate"] == parent_name and m["round"] == block_result["block"])
                assert cm["source_sha256"] == source == block_result["challenger"]["source_sha256"]
                assert pm["source_sha256"] == block_result["reference"]["source_sha256"]
                assert abs(cm["time"] - block_result["challenger_overall_axis"]) < 1e-12
                assert abs(pm["time"] - block_result["reference_overall_axis"]) < 1e-12
            run_summary = summarize_runner(runner_blocks)
            by_source[source].append({"run_id": str(state["run_id"]), "batch": state.get("batch"),
                                      "candidate_names": [name], "proof_sha256": entry["hashes"].get("Parse.lean"),
                                      "runner_summary": run_summary, "blocks": runner_blocks})
            receipt_details.append({"run_id": str(state["run_id"]), "folder": str(folder),
                                    "candidate": name, "source_sha256": source,
                                    "blocks": blocks, "environment": state.get("metrics", [{}])[0].get("environment")})
    results = []
    for source, runs in sorted(by_source.items()):
        # A repeated runner or proof alias must not silently receive extra weight.
        assert len({r["run_id"] for r in runs}) == len(runs), f"duplicate Rust source/run pair for {source}"
        means = [r["runner_summary"] for r in runs]
        results.append({"source_sha256": source, "candidate_names": sorted({n for r in runs for n in r["candidate_names"]}),
                        "independent_runners": len(runs), "runs": runs,
                        "runner_equal_mean_overall_relative_change_pct": statistics.mean(x["overall_relative_change_pct"] for x in means),
                        "runner_equal_mean_group_contribution_pp": {
                            g: statistics.mean(x["group_contribution_pp"][g] for x in means) for g in ("D", "non_D")},
                        "runner_mean_range_pct": {
                            "overall_min": min(x["overall_relative_change_pct"] for x in means),
                            "overall_max": max(x["overall_relative_change_pct"] for x in means),
                            "D_min": min(x["group_contribution_pp"]["D"] for x in means),
                            "D_max": max(x["group_contribution_pp"]["D"] for x in means),
                            "non_D_min": min(x["group_contribution_pp"]["non_D"] for x in means),
                            "non_D_max": max(x["group_contribution_pp"]["non_D"] for x in means)}})
    return results, receipt_details


def find_prefix_method_blocks(folder, state, prefix):
    entries = get_entries(state)
    names = selected_names(entries, prefix)
    metrics = defaultdict(set)
    for m in state["metrics"]:
        metrics[m["candidate"]].add(m["round"])
    out = []
    for name in names:
        for block in sorted(metrics[name]):
            if (folder / f"round{block}-{name}.jsonl").exists():
                out.append((name, block, entries[name]))
    return out


def add_optional_comparison(folder, route_hashes, challenger_prefix, reference_prefix):
    state = json.loads((folder / "state.json").read_text(encoding="utf-8"))
    ch = find_prefix_method_blocks(folder, state, challenger_prefix)
    ref = find_prefix_method_blocks(folder, state, reference_prefix)
    ref_by_block = {b: (n, e) for n, b, e in ref}
    blocks = []
    for name, block, entry in ch:
        if block in ref_by_block:
            ref_name, ref_entry = ref_by_block[block]
            result = compare_block(folder, block, name, ref_name, route_hashes, str(state["run_id"]))
            candidate_metric = next(m for m in state["metrics"] if m["candidate"] == name and m["round"] == block)
            reference_metric = next(m for m in state["metrics"] if m["candidate"] == ref_name and m["round"] == block)
            assert candidate_metric["source_sha256"] == entry["hashes"]["parse.rs"] == result["challenger"]["source_sha256"]
            assert reference_metric["source_sha256"] == ref_entry["hashes"]["parse.rs"] == result["reference"]["source_sha256"]
            assert abs(candidate_metric["time"] - result["challenger_overall_axis"]) < 1e-12
            assert abs(reference_metric["time"] - result["reference_overall_axis"]) < 1e-12
            result["challenger"]["selected_prefix"] = challenger_prefix
            result["reference"]["selected_prefix"] = reference_prefix
            result["reference"]["source_sha256"] = ref_entry["hashes"]["parse.rs"]
            result["challenger"]["source_sha256"] = entry["hashes"]["parse.rs"]
            blocks.append(result)
    if not blocks:
        return None
    return {"run_id": str(state["run_id"]), "batch": state.get("batch"),
            "challenger_prefix": challenger_prefix, "reference_prefix": reference_prefix,
            "source_sha256": {"challenger": blocks[0]["challenger"]["source_sha256"],
                              "reference": blocks[0]["reference"]["source_sha256"]},
            "runner_summary": summarize_runner(blocks), "blocks": blocks}


def clone_comparisons(receipts, route_hashes, clone_name, reference_name):
    results = []
    for folder in receipts:
        state = json.loads((folder / "state.json").read_text(encoding="utf-8"))
        metric_map = defaultdict(set)
        for m in state["metrics"]:
            metric_map[m["candidate"]].add(m["round"])
        blocks = sorted(metric_map[clone_name] & metric_map[reference_name])
        for block in blocks:
            results.append(compare_block(folder, block, clone_name, reference_name,
                                         route_hashes, str(state["run_id"])) )
    return results


def main():
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument("receipts", nargs="*", type=Path, default=DEFAULT_RECEIPTS,
                    help="gate receipt directories; defaults to the five completed record/scalar runs")
    ap.add_argument("--route-json", type=Path, default=DEFAULT_ROUTE_JSON)
    ap.add_argument("--candidate-prefix", default="r10-record-nonempty",
                    help="candidate entry name or prefix; same-Rust proof variants are grouped by parse.rs SHA")
    ap.add_argument("--parent", default="r9-block-scalar")
    ap.add_argument("--pipeline-run", type=Path, default=ROOT / "evidence/round10/37695964878/restore-h/gate")
    ap.add_argument("--pipeline-prefix", default="r10-finder-pipeline")
    ap.add_argument("--pipeline-reference-prefix", default="r10-record-nonempty")
    ap.add_argument("--additional-pipeline-run", type=Path, action="append", default=[],
                    help="additional screen/gate folder for a same-block pipeline-vs-record diagnostic")
    ap.add_argument("--clone-name", default="mid-shadow")
    ap.add_argument("--clone-reference", default="public361")
    ap.add_argument("--json", type=Path, default=ROOT / "evidence/round10/stability-before-confirm.json")
    ap.add_argument("--markdown", type=Path, default=ROOT / "evidence/round10/stability-before-confirm.md")
    args = ap.parse_args()
    receipts = [p.resolve() for p in args.receipts]
    assert receipts and all((p / "state.json").exists() for p in receipts)
    route_hashes, route_meta = load_route_hashes(args.route_json.resolve())
    main_results, receipt_details = add_main_comparisons(receipts, route_hashes,
                                                         args.candidate_prefix, args.parent)
    assert main_results
    pipeline = add_optional_comparison(args.pipeline_run.resolve(), route_hashes,
                                       args.pipeline_prefix, args.pipeline_reference_prefix)
    additional_screens = []
    for screen_folder in args.additional_pipeline_run:
        screen_folder = screen_folder.resolve()
        comparison = add_optional_comparison(screen_folder, route_hashes,
                                             args.pipeline_prefix, args.pipeline_reference_prefix)
        assert comparison, f"no same-block pipeline/reference comparison in {screen_folder}"
        state = json.loads((screen_folder / "state.json").read_text(encoding="utf-8"))
        ci_path = screen_folder / "ci-run.json"
        ci = json.loads(ci_path.read_text(encoding="utf-8")) if ci_path.exists() else {}
        screen_clones = clone_comparisons([screen_folder], route_hashes,
                                          args.clone_name, args.clone_reference)
        screen_clone_effects = [b["overall_relative_change_pct"] for b in screen_clones]
        comparison["receipt_folder"] = str(screen_folder)
        comparison["state_phase"] = state.get("phase")
        comparison["ci_status"] = ci.get("status", "UNKNOWN")
        comparison["ci_conclusion"] = ci.get("conclusion", "")
        gate_names = selected_names(get_entries(state), args.pipeline_prefix)
        gate_verdicts = {name: {"accepted": bool(state["gates"][name].get("accepted")),
                                 "files": get_entries(state)[name]["hashes"]}
                         for name in gate_names if name in state.get("gates", {})}
        comparison["ci_completed"] = ci.get("status") == "completed" and bool(ci.get("conclusion"))
        comparison["gate_verdicts"] = gate_verdicts
        comparison["gate_completed"] = comparison["ci_completed"] and bool(gate_verdicts)
        comparison["gate_accepted"] = any(v["accepted"] for v in gate_verdicts.values()) if gate_verdicts else None
        comparison["same_run_clone_diagnostic"] = {
            "comparison": f"{args.clone_name} / {args.clone_reference}",
            "block_effect_pct": screen_clone_effects,
            "maximum_absolute_block_effect_pct": max((abs(x) for x in screen_clone_effects), default=0.0),
            "pipeline_abs_effect_exceeds_clone_max": abs(comparison["runner_summary"]["overall_relative_change_pct"])
                > max((abs(x) for x in screen_clone_effects), default=0.0)}
        additional_screens.append(comparison)
    clones = clone_comparisons(receipts, route_hashes, args.clone_name, args.clone_reference)
    record_mean = main_results[0]["runner_equal_mean_overall_relative_change_pct"]
    clone_effects = [c["overall_relative_change_pct"] for c in clones]
    clone_max_abs = max((abs(x) for x in clone_effects), default=0.0)
    pipeline_clones = [c["overall_relative_change_pct"] for c in clones
                       if pipeline and c["run_id"] == pipeline["run_id"]]
    pipeline_clone_max_abs = max((abs(x) for x in pipeline_clones), default=0.0)
    result = {
        "status": "VERIFIED_PUBLIC_RECEIPTS_RECOMPUTED",
        "route_map": route_meta,
        "measurement_definition": {
            "file_axis": "median(measured total_s for method) / median(measured total_s for that JSONL's paired incumbent), per file",
            "overall_axis": "arithmetic mean of 28 per-file axes within each block",
            "per_file_group_contribution_pp": "100 * (challenger_file_axis - reference_file_axis) / (28 * same-block overall reference_axis)",
            "weighting": "average the two blocks equally within each runner, then average runners equally",
            "D_classification": "18 public input SHA values from non-synthetic seed_records in forward.json; matched to every receipt by input SHA-256",
            "limits": ["public stage1 paired measurements only", "unmodified-route contributions are not pure noise",
                       "observed clone differences are diagnostics, not confidence intervals", "no private-corpus or leaderboard prediction"]},
        "record_vs_scalar": {"candidate_prefix": args.candidate_prefix, "reference": args.parent,
                             "results_by_candidate_source_sha256": main_results,
                             "receipt_paths": receipt_details},
        "pipeline_vs_record_restore_h": pipeline,
        "pipeline_vs_record_additional_screens": additional_screens,
        "same_run_mid_shadow_vs_public361_clone_diagnostic": {
            "comparison": f"{args.clone_name} / {args.clone_reference}",
            "blocks": clones,
            "block_effect_range_pct": {"min": min(clone_effects), "max": max(clone_effects)} if clone_effects else None,
            "maximum_absolute_block_effect_pct": clone_max_abs,
            "record_runner_equal_mean_effect_pct": record_mean,
            "abs_record_mean_exceeds_max_abs_clone_block_effect": abs(record_mean) > clone_max_abs,
            "pipeline_restore_h_effect_pct": (pipeline["runner_summary"]["overall_relative_change_pct"] if pipeline else None),
            "pipeline_restore_h_clone_max_abs_block_effect_pct": pipeline_clone_max_abs,
            "abs_pipeline_restore_h_effect_exceeds_same_run_clone": (
                abs(pipeline["runner_summary"]["overall_relative_change_pct"]) > pipeline_clone_max_abs
                if pipeline and pipeline_clones else None),
            "comparison_scope": "descriptive only; clone timing movement does not define statistical significance"},
        "input_output_identity": {"all_comparisons_require_identical_input_sha_tokens_sha_output_bytes_and_output_sha": True,
                                  "validated_for_every_reported_file": True},
    }
    args.json.parent.mkdir(parents=True, exist_ok=True)
    args.markdown.parent.mkdir(parents=True, exist_ok=True)
    args.json.write_bytes((json.dumps(result, indent=2) + "\n").encode("utf-8"))
    args.markdown.write_bytes(render_markdown(result).encode("utf-8"))
    print(json.dumps({"status": result["status"], "json": str(args.json), "markdown": str(args.markdown),
                      "candidate_sources": len(main_results),
                      "record_runner_mean_pct": record_mean,
                      "record_group_contribution_pp": main_results[0]["runner_equal_mean_group_contribution_pp"],
                      "clone_block_abs_max_pct": clone_max_abs,
                      "clone_abs_exceeded_by_record_mean": result["same_run_mid_shadow_vs_public361_clone_diagnostic"]["abs_record_mean_exceeds_max_abs_clone_block_effect"]}, indent=2))


def render_markdown(result):
    line = []
    route = result["route_map"]
    route_path = Path(route["path"])
    try:
        route_label = route_path.resolve().relative_to(ROOT.resolve()).as_posix()
    except ValueError:
        route_label = route_path.as_posix()
    line.extend(["# Round 10 stability and route-contribution audit", "",
                 f"Status: **{result['status']}**. D routes: {route['public_d_route_count']} input SHAs from `{route_label}` (SHA-256 `{route['sha256']}`); all receipt rows were classified by input SHA.", "",
                 "Per-file axis is each method's measured-total median divided by that file's paired-incumbent measured-total median. Each block averages the 28 axes. Contributions use `100 × (challenger file axis − reference file axis) / (28 × block reference axis)`; D and non-D contributions sum to the overall relative change. Blocks are equal within a runner, and runners are equal in the final mean.", "",
                 "## Record versus scalar", ""])
    for group in result["record_vs_scalar"]["results_by_candidate_source_sha256"]:
        line.append(f"Rust SHA `{group['source_sha256']}`; runs={group['independent_runners']}; runner-equal overall change **{group['runner_equal_mean_overall_relative_change_pct']:+.6f}%**; D contribution **{group['runner_equal_mean_group_contribution_pp']['D']:+.6f} pp**, non-D contribution **{group['runner_equal_mean_group_contribution_pp']['non_D']:+.6f} pp**.")
        line.append("")
        line.append("| run | block | change | D contribution | non-D contribution |")
        line.append("|---|---:|---:|---:|---:|")
        for run in group["runs"]:
            for b in run["blocks"]:
                line.append(f"| {run['run_id']} | {b['block']} | {b['overall_relative_change_pct']:+.6f}% | {b['group_contribution_pp']['D']:+.6f} pp | {b['group_contribution_pp']['non_D']:+.6f} pp |")
        line.append("")
    pipe = result["pipeline_vs_record_restore_h"]
    if pipe:
        s = pipe["runner_summary"]
        line.extend(["## Pipeline versus record in restore-h", "",
                     f"Same-run, same-block output identity held for every file. Pipeline versus record changed the normalized overall axis by **{s['overall_relative_change_pct']:+.6f}%**; D contribution {s['group_contribution_pp']['D']:+.6f} pp and non-D contribution {s['group_contribution_pp']['non_D']:+.6f} pp.", "",
                     "| block | change | D contribution | non-D contribution |", "|---:|---:|---:|---:|"])
        for b in pipe["blocks"]:
            line.append(f"| {b['block']} | {b['overall_relative_change_pct']:+.6f}% | {b['group_contribution_pp']['D']:+.6f} pp | {b['group_contribution_pp']['non_D']:+.6f} pp |")
        line.append("")
    clone = result["same_run_mid_shadow_vs_public361_clone_diagnostic"]
    line.extend(["## Same-run clone diagnostic", "",
                 f"`mid-shadow / public361` block-level movement ranged from **{clone['block_effect_range_pct']['min']:+.6f}%** to **{clone['block_effect_range_pct']['max']:+.6f}%** (maximum absolute {clone['maximum_absolute_block_effect_pct']:.6f}%). The record runner-equal mean is {clone['record_runner_equal_mean_effect_pct']:+.6f}%; absolute record mean exceeds the largest observed clone block movement: **{clone['abs_record_mean_exceeds_max_abs_clone_block_effect']}**.",
                 f"For pipeline versus record in restore-h, the change was {clone['pipeline_restore_h_effect_pct']:+.6f}% against a same-run clone maximum absolute block movement of {clone['pipeline_restore_h_clone_max_abs_block_effect_pct']:.6f}%; it exceeded that movement: **{clone['abs_pipeline_restore_h_effect_exceeds_same_run_clone']}**.", "",
                 "This is a finite public stage1 comparison. Untouched-route contribution is measured contribution, not an assumed noise term. Clone movement is descriptive and does not establish a confidence interval or predict private/leaderboard performance.", "",
                 "The JSON file retains per-file axes, contribution values, input SHA, token SHA, output byte count/SHA, per-block equality checks, source hashes, and raw JSONL hashes.", ""])
    for extra in result.get("pipeline_vs_record_additional_screens", []):
        s = extra["runner_summary"]
        line.extend([f"## Additional receipt: {extra['run_id']} ({extra['state_phase']})", "",
                     f"Pipeline versus record: {s['overall_relative_change_pct']:+.6f}% overall, D {s['group_contribution_pp']['D']:+.6f} pp, non-D {s['group_contribution_pp']['non_D']:+.6f} pp. Its same-run clone movement was {extra['same_run_clone_diagnostic']['block_effect_pct']}; maximum absolute movement {extra['same_run_clone_diagnostic']['maximum_absolute_block_effect_pct']:.6f}%, so the pipeline effect exceeded it: **{extra['same_run_clone_diagnostic']['pipeline_abs_effect_exceeds_clone_max']}**. CI status is `{extra['ci_status']}` with conclusion `{extra['ci_conclusion'] or 'UNKNOWN'}`; completed full gate: **{extra['gate_completed']}**; accepted exact pair: **{extra['gate_accepted'] if extra['gate_accepted'] is not None else 'NOT_RUN_IN_RECEIPT'}**. Performance and proof verdicts are separate.", ""])
    return "\n".join(line)


if __name__ == "__main__":
    main()
