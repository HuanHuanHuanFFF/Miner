#!/usr/bin/env python3
"""Independent acceptance audit of B10 standard Mixer NativeAdd evidence."""
from __future__ import annotations

import datetime
import hashlib
import importlib.util
import json
import math
from pathlib import Path
import re
import shlex
import subprocess
import sys

sys.dont_write_bytecode = True
HERE = Path(__file__).resolve().parent
ROUND = HERE.parent
ROOT = ROUND.parents[3]
STATE = ROUND / "competition-state"
RUN_DIR = ROUND / "evidence/40977309820"
PLAN_PATH = ROUND / "ci-plan-batch10.json"
RESULTS_PATH = ROUND / "CI-RESULTS-BATCH10.json"
OUT_PATH = HERE / "audit-native-run-40977309820.json"


def read(path: Path):
    raw = path.read_bytes()
    return json.loads(raw.decode("utf-8-sig")), raw, hashlib.sha256(raw).hexdigest()


def sha(path: Path) -> str:
    return hashlib.sha256(path.read_bytes()).hexdigest()


def load_module(path: Path, name: str):
    spec = importlib.util.spec_from_file_location(name, path)
    if spec is None or spec.loader is None:
        raise ValueError(f"cannot load {path}")
    module = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(module)
    return module


def normalize(args: list[str]) -> list[str]:
    return [
        re.sub(
            r"(?<=/)(?:benchExact|r27Native)(?=\.|$)", "<BIN>",
            re.sub(r"(?<=/)(?:MainExact|R27NativeMain)(?=\.)", "<MAIN>", x),
        )
        for x in args
    ]


def main() -> int:
    failures: list[str] = []
    plan, plan_bytes, plan_sha = read(PLAN_PATH)
    ci, _, ci_sha = read(RUN_DIR / "ci-run.json")
    root_audit, _, root_audit_sha = read(RUN_DIR / "root-native-audit.json")
    original_manifest, _, original_manifest_sha = read(RUN_DIR / "original-artifact-hashes.json")
    artifact_dir = RUN_DIR / original_manifest["directory"]
    summary, _, summary_sha = read(artifact_dir / "summary.json")
    artifact_plan, artifact_plan_bytes, artifact_plan_sha = read(artifact_dir / "plan.json")
    file_manifest, _, inner_manifest_sha = read(artifact_dir / "file-hashes.json")
    ci_results_present = RESULTS_PATH.is_file()
    ci_results, _, ci_results_sha = read(RESULTS_PATH) if ci_results_present else ({}, b"", None)

    r26_path = ROOT / "competitions/torchlean/candidates/r26-1h-20261029T085515Z/verification/analyze-native-only.py"
    r26 = load_module(r26_path, "r27_b10_pinned_r26_auditor")
    mod, modules, pins = r26.r25_tools()
    outer = r26.audit_tree(artifact_dir, original_manifest.get("files", {}))
    inner = r26.audit_tree(artifact_dir, file_manifest, excluded=("file-hashes.json",))
    if outer.get("status") != "PASS":
        failures.append("outer_artifact_hashes")
    if inner.get("status") != "PASS":
        failures.append("inner_runner_hashes")

    dispatch_path, dispatch = r26.find_dispatch(RUN_DIR.parent, "40977309820")
    frozen = dispatch.get("frozen_files", {})
    owned_hashes = []
    for rel in plan.get("owned_sources", []):
        p = ROOT / rel
        current_digest = sha(p) if p.is_file() else None
        try:
            commit_blob = subprocess.run(["git", "show", f"{ci['headSha']}:{rel}"], cwd=ROOT, capture_output=True, check=True).stdout
            commit_digest = hashlib.sha256(commit_blob).hexdigest()
        except (subprocess.CalledProcessError, FileNotFoundError):
            commit_digest = None
        matched = commit_digest is not None and commit_digest == frozen.get(rel)
        owned_hashes.append({"path": rel, "current_sha256": current_digest, "run_commit_sha256": commit_digest, "dispatch_sha256": frozen.get(rel), "pass": matched})
        if not matched:
            failures.append("owned_dispatch_hash:" + rel)
    candidate = plan["candidates"][0]
    canonical_plan_rel = "competitions/torchlean/candidates/r27-5h-20261029T194443Z/ci-plan.json"
    try:
        canonical_plan_blob = subprocess.run(["git", "show", f"{ci['headSha']}:{canonical_plan_rel}"], cwd=ROOT, capture_output=True, check=True).stdout
        canonical_plan_commit_sha = hashlib.sha256(canonical_plan_blob).hexdigest()
    except (subprocess.CalledProcessError, FileNotFoundError):
        canonical_plan_commit_sha = None
    canonical_plan_workspace_sha = sha(ROUND / "ci-plan.json")
    dispatch_checks = {
        "run_identity_matches": dispatch.get("state") == "RUN_IDENTIFIED" and str((dispatch.get("run") or {}).get("databaseId")) == str(ci.get("databaseId")) == "40977309820" and dispatch.get("source_commit") == ci.get("headSha"),
        "public_repository_and_allow_private_false": dispatch.get("repository_public") is True and str(dispatch.get("request", {}).get("inputs", {}).get("allow_private", "")).lower() == "false",
        "frozen_plan_matches": plan_sha == artifact_plan_sha == canonical_plan_commit_sha == frozen.get(canonical_plan_rel),
        "candidate_patch_frozen": frozen.get(candidate["patch_script"]) == candidate.get("patch_script_sha256"),
        "all_owned_sources_frozen": all(x.get("pass") for x in owned_hashes),
        "official_head_matches": plan.get("official_commit") == artifact_plan.get("official_commit") == "27fb1d19c712ead50ad34b4ad0d4ba597161e616",
        "root_seed_matches_plan": str(dispatch.get("request", {}).get("inputs", {}).get("seed")) == str(plan.get("dispatch_seed")),
    }
    if not all(dispatch_checks.values()):
        failures.extend("dispatch:" + k for k, ok in dispatch_checks.items() if not ok)

    source23_path = STATE / "source-private/submission23-Kernel.lean"
    source27_path = STATE / "source-private/submission27-Kernel.lean"
    source23 = source23_path.read_bytes()
    source27 = source27_path.read_bytes()
    source23_sha = hashlib.sha256(source23).hexdigest()
    source27_sha = hashlib.sha256(source27).hexdigest()
    public_receipts, _, public_receipts_sha = read(STATE / "public-source-and-report-receipts.json")
    current_receipts, _, current_receipts_sha = read(STATE / "normalized-champion-update-2150-receipts.json")
    receipt23 = next((x for x in current_receipts if x.get("url") == "https://conjectures.io/v1/competitions/torchlean/submissions/23/source"), None)
    receipt27 = next((x for x in public_receipts if x.get("url") == "https://conjectures.io/v1/competitions/torchlean/submissions/27/source"), None)
    source_checks = {
        "public23_matches_candidate_fetch": bool(receipt23 and receipt23.get("status") == 200 and receipt23.get("sha256") == source23_sha == candidate["fetch"]["sha256"] and receipt23.get("bytes") == len(source23)),
        "public27_matches_reference_and_extra_fetch": bool(receipt27 and receipt27.get("status") == 200 and receipt27.get("sha256") == source27_sha == plan["reference"]["sha256"] == candidate["extra_fetches"][0]["sha256"] and receipt27.get("bytes") == len(source27)),
    }
    if not all(source_checks.values()):
        failures.extend("source:" + k for k, ok in source_checks.items() if not ok)

    patch = load_module(ROOT / candidate["patch_script"], "r27_b10_acceptance_patch")
    generated = patch.transform(source23, 23, candidate["variant"], donor_raw=source27)
    generated_sha = hashlib.sha256(generated).hexdigest()
    if generated_sha != candidate["sha256"] or len(generated) != candidate["bytes"]:
        failures.append("candidate_transform_hash")

    recipe_dependencies = {
        candidate["patch_script"]: candidate.get("patch_script_sha256"),
        "competitions/torchlean/candidates/r27-5h-20261029T194443Z/development/ci-bridge/batch10/graft_native_add_portfolio10.py": "6d4f12349641bbb6587d844414cf1a5209c7f874a7ca4a1f1a51f2aec2123943",
        "competitions/torchlean/candidates/r27-5h-20261029T194443Z/development/ci-bridge/batch10/portfolio10_components/build_gemm27_on_public23.py": "a920b7ab2545ad4e7eb4f009b29c5a78da2ae0fa9f41415c9546e0f679049736",
        "competitions/torchlean/candidates/r27-5h-20261029T194443Z/development/ci-bridge/batch10/portfolio10_components/build_gemm27_on_public23_v2.py": "01b5405cfb0410396902d7f54c95b48a18789c2d696e31207f09fdee9f8b7c23",
        "competitions/torchlean/candidates/r27-5h-20261029T194443Z/development/ci-bridge/batch10/portfolio10_components/compact_public23.py": "4c3dd79284f6701d3b128687f9f973f47d9236f8d9db502d398e2eb4d131e129",
    }
    dependency_checks = {rel: sha(ROOT / rel) == expected for rel, expected in recipe_dependencies.items()}
    if not all(dependency_checks.values()):
        failures.append("candidate_recipe_dependency_hash")

    main_rel = "competitions/torchlean/candidates/r27-5h-20261029T194443Z/development/ci-bridge/runner.py"
    runner_hash = frozen.get(main_rel)
    try:
        runner_blob = subprocess.run(["git", "show", f"{ci['headSha']}:{main_rel}"], cwd=ROOT, capture_output=True, check=True).stdout
        runner_blob_sha = hashlib.sha256(runner_blob).hexdigest()
        runner_text = runner_blob.decode("utf-8")
    except (subprocess.CalledProcessError, FileNotFoundError):
        runner_blob_sha, runner_text = None, ""
    summary_main = summary.get("owned_main_equals_original_sha256")
    main_receipt = {"sha256": summary_main, "root_audit_sha256": root_audit.get("MainExact_sha256"), "runner_sha256": runner_blob_sha, "runner_dispatch_sha256": runner_hash, "runner_blob_matches_dispatch": runner_blob_sha == runner_hash, "copy_assertion_present": "mainfile.write_bytes(mainbytes)" in runner_text and "assert mainfile.read_bytes()==mainbytes" in runner_text}
    if summary_main != root_audit.get("MainExact_sha256") or runner_blob_sha != runner_hash or not main_receipt["copy_assertion_present"]:
        failures.append("MainExact_copy_receipt")

    gate_rows = summary.get("full_gates", [])
    gate = next((x for x in gate_rows if x.get("name") == candidate["name"]), {})
    verdict = gate.get("verdict", {})
    gate_checks = {
        "full_gate_planned": candidate.get("full_gate") is True and candidate.get("declares_correct") is True,
        "gate_source_matches_candidate": gate.get("source_sha256") == candidate["sha256"],
        "gate_passed_at_axioms": gate.get("exit_code") == 0 and verdict.get("passed") is True and verdict.get("stage") == "axioms",
        "verifier_fingerprint_stable": verdict.get("verifier_fingerprint") == verdict.get("verifier_fingerprint_end"),
        "gate_not_exhausted": verdict.get("exhausted") is False,
    }
    if not all(gate_checks.values()):
        failures.extend("full_gate:" + k for k, ok in gate_checks.items() if not ok)

    config = modules["config"].Config.load(artifact_dir / "overall-config.toml")
    board = config.plan("mixer")
    expected_cells = list(board["cells"])
    expected_timing = config.timing | board["timing"] | config.environments["local"]["timing"]
    expected_seeds = [int(x) for x in plan.get("seeds", [])]
    source_results = {x.get("name"): x for x in summary.get("results", []) if isinstance(x, dict)}
    measured = []
    pairs = []
    cpus = []
    candidate_dir = artifact_dir / candidate["name"]
    saved_flags = read(candidate_dir / "flags.json")[0]
    flags = {}
    for kind in ("compile", "link", "response"):
        a, b = candidate_dir / f"original-{kind}.raw", candidate_dir / f"owned-{kind}.raw"
        old = shlex.split(a.read_text(encoding="utf-8")) if kind == "response" else r26.trace_args(a)
        new = shlex.split(b.read_text(encoding="utf-8")) if kind == "response" else r26.trace_args(b)
        record = saved_flags.get(kind, {})
        passed = normalize(old) == normalize(new) and record.get("original_args") == old and record.get("owned_args") == new and record.get("equal_only_root_mapping") is True
        flags[kind] = {"equal_after_target_mapping": passed, "original_arg_count": len(old), "owned_arg_count": len(new)}
        if not passed:
            failures.append("native_flags:" + kind)

    for seed in expected_seeds:
        request, _, request_sha = read(artifact_dir / f"{candidate['name']}-{seed}-request.json")
        raw_result, _, measurement_sha = read(artifact_dir / f"{candidate['name']}-{seed}-measurement.json")
        result = raw_result.get("result")
        if not isinstance(result, dict):
            failures.append("measurement_missing:" + str(seed))
            continue
        expected_request = {"environment":"local","identity":config.environments["local"]["identity"],"seed":seed,"candidate_hash":candidate["sha256"],"reference_hash":plan["reference"]["sha256"],"cells":expected_cells,"timing":expected_timing,"benchmark_identity":board["benchmark_identity"],"workloads":modules["multiseed"].workloads(seed)}
        request_checks = {k: request.get(k) == v for k,v in expected_request.items()}
        try:
            modules["config"].MeasurementRequest.parse(request)
            request_checks["parse"] = True
        except Exception:
            request_checks["parse"] = False
        checked = mod.measurement_check(request, raw_result, board["cells"], modules)
        r26.raw_rounds(artifact_dir, candidate["name"], seed, request, result)
        paired = sum(len(r.get("cells",{})) for r in result.get("rounds",[]))
        ns_values = 2*paired
        checksums = sum(x.get("reference_checksum")==x.get("candidate_checksum") for r in result.get("rounds",[]) for x in r.get("cells",{}).values())
        provenance = result.get("provenance",{})
        candidate_binary = source_results.get(candidate["name"],{}).get("binary_sha256")
        reference_binary = source_results.get("calibration",{}).get("binary_sha256")
        provenance_checks = {"identity":provenance.get("identity")==request.get("identity"),"candidate_binary":provenance.get("candidate_binary")==candidate_binary,"reference_binary":provenance.get("reference_binary")==reference_binary}
        if not all(request_checks.values()):
            failures.extend(f"request:{seed}:{k}" for k,v in request_checks.items() if not v)
        if checked.get("status")!="PASS" or len(result.get("rounds",[]))!=11 or paired!=396 or ns_values!=792 or checksums!=396 or checked.get("checksum_mismatches")!=0:
            failures.append("standard_measurement:"+str(seed))
        if not all(provenance_checks.values()):
            failures.extend(f"provenance:{seed}:{k}" for k,v in provenance_checks.items() if not v)
        cpus.append({k:provenance.get(k) for k in ("identity","machine","architecture","cpu_affinity")})
        measured.append({"seed":seed,"request_sha256":request_sha,"measurement_sha256":measurement_sha,"paired_rows":paired,"nanosecond_values":ns_values,"checksum_pairs":checksums,"checksum_mismatches":checked.get("checksum_mismatches"),"rounds":len(result.get("rounds",[])),"cells_per_round":[len(r.get("cells",{})) for r in result.get("rounds",[])],"reference_first_sequence":[r.get("reference_first") for r in result.get("rounds",[])],"request_checks":request_checks,"pinned_measurement_check":checked,"provenance":{**provenance,"checks":provenance_checks}})
        pairs.append((request,result))
    same_cpu = len(cpus)==2 and all(cpus[0].get(k)==cpus[1].get(k) for k in ("identity","machine","architecture","cpu_affinity"))
    if not same_cpu:
        failures.append("same_cpu")
    local_plan=dict(board);local_plan["strata"]=[{"environment":q["environment"],"identity":q["identity"],"seed":q["seed"],"weight":1/len(pairs),"timing":q["timing"]} for q,_ in pairs]
    scorer=modules["scoring"].assess(local_plan,pairs) if len(pairs)==2 else None
    score=scorer.get("score") if scorer else None

    # The official #36/#27 report is an old-policy edge; use it only as INFERRED.
    current_record=read(HERE/"champion-only-record.json")[0]
    mixer_record=next((x for x in current_record.get("boards",[]) if x.get("board")=="mixer"),{})
    chain=read(HERE/"official-report-chain.json")[0]
    mixer_chain=next((x for x in chain.get("boards",[]) if x.get("board")=="mixer"),{})
    current36_over_public27=float(mixer_chain.get("current_ratio_to_reference_reported"))
    estimate=score/current36_over_public27 if score else None
    results_candidate=next((x for x in root_audit.get("results",[]) if x.get("candidate")==candidate["name"]),{})
    root_score=results_candidate.get("score_vs_calibration_internal",{}).get("score")
    root_estimate=results_candidate.get("candidate_time_over_current_champion_estimate")
    score_checks={"pinned_score":score,"root_score":root_score,"score_matches":bool(score is not None and math.isclose(float(score),float(root_score or -1),rel_tol=1e-12,abs_tol=1e-15)),"guard_passed":scorer.get("guard_passed") if scorer else None,"root_guard_passed":results_candidate.get("score_vs_calibration_internal",{}).get("guard_passed"),"guard_matches":bool(scorer and scorer.get("guard_passed")==results_candidate.get("score_vs_calibration_internal",{}).get("guard_passed")),"current36_over_public27_old_report":current36_over_public27,"candidate_over_current36_estimate":estimate,"root_estimate":root_estimate,"estimate_matches":bool(estimate is not None and math.isclose(float(estimate),float(root_estimate or -1),rel_tol=1e-12,abs_tol=1e-15)),"classification":"INFERRED_CROSS_BENCHMARK_VERSION_ENVIRONMENTS_AND_SEEDS","strict_converter_status":"UNKNOWN_OLD_REPORT_CONFIG_AND_LOCAL_RUN_CONTRACT"}
    if not score_checks["score_matches"] or not score_checks["guard_matches"] or not score_checks["estimate_matches"]:
        failures.append("score_reconstruction")

    mixer_binding=read(HERE/"audit-mixer-current-binding-230552.json")[0]
    mixer_chain=next((x for x in read(HERE/"official-report-chain.json")[0].get("boards",[]) if x.get("board")=="mixer"),{})
    current36_ratio=float(mixer_chain.get("current_ratio_to_reference_reported"))
    current36_checks={
        "latest_publication_binding_passed":mixer_binding.get("checks",{}).get("response_publication_matches_latest_board_snapshot") is True,
        "current_submission_matches_plan":plan.get("champion",{}).get("submission")==36 and mixer_binding.get("saved_champion_response",{}).get("current_row",{}).get("submission")==36,
        "current_source_unavailable":mixer_binding.get("saved_champion_response",{}).get("current_row",{}).get("source_available") is False,
        "plan_calibration_ratio_matches_official_chain":math.isclose(float(plan.get("champion",{}).get("current_champion_over_calibration",-1)),current36_ratio,rel_tol=1e-12,abs_tol=1e-15),
        "live_report_config_mismatch":mixer_binding.get("checks",{}).get("response_config_matches_live_board_config") is False,
        "candidate_over_current36_estimate":estimate,
        "classification":"INFERRED_CROSS_REPORT_CONFIG_ENVIRONMENTS_AND_SEEDS",
        "strict_converter_status":"UNKNOWN_OLD_REPORT_CONFIG_AND_LOCAL_RUN_CONTRACT",
    }
    if not all(current36_checks[k] for k in ("latest_publication_binding_passed","current_submission_matches_plan","current_source_unavailable","plan_calibration_ratio_matches_official_chain","live_report_config_mismatch")):
        failures.append("current36_binding_or_calibration_edge")

    run_record, _, _ = read(RUN_DIR/"ci-run.json")
    result_file_present=(ROUND/"CI-RESULTS-BATCH9.json").is_file()
    output={"round":"R27","captured_at_utc":datetime.datetime.now(datetime.timezone.utc).isoformat(),"scope":"INDEPENDENT_B10_ACCEPTANCE_AUDIT_WITH_PINNED_R25_SCORER; ACCEPTANCE_ONLY_NOT_TUNING","run":{"id":run_record.get("databaseId"),"source_commit":run_record.get("headSha"),"conclusion":run_record.get("conclusion")},"plan":{"sha256":plan_sha,"artifact_plan_sha256":artifact_plan_sha,"run_commit_canonical_plan_sha256":canonical_plan_commit_sha,"current_workspace_canonical_plan_sha256":canonical_plan_workspace_sha,"official_commit":plan.get("official_commit")},"dispatch":{"path":dispatch_path.relative_to(ROOT).as_posix(),"checks":dispatch_checks,"owned_hashes":owned_hashes,"recipe_dependency_checks":dependency_checks},"artifact_integrity":{"outer":outer,"inner":inner},"source_receipts":{"public23":receipt23,"public27":receipt27,"checks":source_checks},"candidate":{"sha256":candidate["sha256"],"proof_state":summary.get("results",[{}])[-1].get("proof_state"),"full_gate":gate,"gate_checks":gate_checks,"MainExact":main_receipt,"native_flags":flags,"seeds":measured,"same_cpu":same_cpu,"score_and_inferred_current36":score_checks,"current36_binding":current36_checks},"root_audit_sha256":root_audit_sha,"summary_sha256":summary_sha,"results_file_present":result_file_present,"acceptance_barrier":"New B10 inputs/results audited for acceptance only; not used for tuning.","failures":failures,"status":"PASS_B10_GATE_AND_NATIVE_ACCEPTANCE_AUDITED_NO_PROMOTION" if not failures else "AUDIT_FAILED"}
    OUT_PATH.write_text(json.dumps(output,indent=2,ensure_ascii=False)+"\n",encoding="utf-8")
    print(json.dumps({"status":output["status"],"full_gate":gate_checks,"measurements":len(measured),"score":score_checks,"current36_binding":current36_checks,"failures":failures},ensure_ascii=False))
    return 0 if not failures else 1


if __name__ == "__main__":
    raise SystemExit(main())
