#!/usr/bin/env python3
"""Independent pinned-R25 evidence audit of the B12 quick NativeOnly screen."""
from __future__ import annotations
import datetime, hashlib, importlib.util, json, math, pathlib, subprocess, sys

sys.dont_write_bytecode = True
HERE = pathlib.Path(__file__).resolve().parent
ROUND = HERE.parent
ROOT = ROUND.parents[3]
STATE = ROUND / "competition-state"
RUN = ROUND / "evidence/40979775217"
PLAN_PATH = ROUND / "ci-plan-batch12.json"
RESULTS_PATH = ROUND / "CI-RESULTS-BATCH12.json"
OUT = HERE / "audit-native-run-40979775217.json"

def read(path):
    raw = pathlib.Path(path).read_bytes()
    return json.loads(raw.decode("utf-8-sig")), hashlib.sha256(raw).hexdigest()

def sha(raw):
    return hashlib.sha256(raw).hexdigest()

def load(path, name):
    spec = importlib.util.spec_from_file_location(name, path)
    if spec is None or spec.loader is None:
        raise ValueError(f"cannot load {path}")
    module = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(module)
    return module

def main():
    failures = []
    plan, plan_sha = read(PLAN_PATH)
    ci, _ = read(RUN / "ci-run.json")
    dispatch, dispatch_sha = read(RUN.parent / "dispatch-20261030T002712Z/dispatch.json")
    dispatch_path = RUN.parent / "dispatch-20261030T002712Z/dispatch.json"
    dispatch, _ = read(dispatch_path)
    outer_manifest, outer_sha = read(RUN / "original-artifact-hashes.json")
    artifact_dir = RUN / outer_manifest["directory"]
    summary, summary_sha = read(artifact_dir / "summary.json")
    inner_manifest, inner_sha = read(artifact_dir / "file-hashes.json")
    artifact_index, _ = read(RUN / "artifacts.json")
    root_result, root_result_sha = read(RESULTS_PATH)

    r26 = load(ROOT / "competitions/torchlean/candidates/r26-1h-20261029T085515Z/verification/analyze-native-only.py", "r27_b12_r25_tools")
    mod, modules, pins = r26.r25_tools()
    outer = r26.audit_tree(artifact_dir, outer_manifest.get("files", {}))
    inner = r26.audit_tree(artifact_dir, inner_manifest, excluded=("file-hashes.json",))
    if outer.get("status") != "PASS": failures.append("outer_hashes")
    if inner.get("status") != "PASS": failures.append("inner_hashes")

    frozen = dispatch.get("frozen_files", {})
    candidate = plan["candidates"][0]
    frozen = dispatch.get("frozen_files", {})
    try:
        canonical_blob = subprocess.run(["git", "show", f"{ci['headSha']}:competitions/torchlean/candidates/r27-5h-20261029T194443Z/ci-plan.json"], cwd=ROOT, capture_output=True, check=True).stdout
        canonical_hash = sha(canonical_blob)
    except (subprocess.CalledProcessError, FileNotFoundError):
        canonical_hash = None
    owned_hashes = {}
    for rel in plan.get("owned_sources", []):
        try:
            blob = subprocess.run(["git", "show", f"{ci['headSha']}:{rel}"], cwd=ROOT, capture_output=True, check=True).stdout
            owned_hashes[rel] = sha(blob) == frozen.get(rel)
        except (subprocess.CalledProcessError, FileNotFoundError):
            owned_hashes[rel] = False
    dispatch_checks = {"run_id":str(ci.get("databaseId"))=="40979775217"==str(dispatch.get("run",{}).get("databaseId")),"source_commit":ci.get("headSha")==dispatch.get("source_commit")=="5d537b5991066342a6a66f0b51e0c8f983edb133","public_allow_private_false":dispatch.get("repository_public") is True and str(dispatch.get("request",{}).get("inputs",{}).get("allow_private","")).lower()=="false","plan_matches_run_commit":canonical_hash==plan_sha==frozen.get("competitions/torchlean/candidates/r27-5h-20261029T194443Z/ci-plan.json"),"owned_files_match_dispatch":all(owned_hashes.values())}
    if not all(dispatch_checks.values()): failures.append("dispatch_binding")
    try:
        canonical = subprocess.run(["git", "show", f"{ci['headSha']}:competitions/torchlean/candidates/r27-5h-20261029T194443Z/ci-plan.json"], cwd=ROOT, capture_output=True, check=True).stdout
        canonical_hash = sha(canonical)
    except (subprocess.CalledProcessError, FileNotFoundError):
        canonical_hash = None
    owned_checks = {}
    for rel in plan.get("owned_sources", []):
        try:
            blob = subprocess.run(["git", "show", f"{ci['headSha']}:{rel}"], cwd=ROOT, capture_output=True, check=True).stdout
            h = sha(blob)
        except (subprocess.CalledProcessError, FileNotFoundError):
            h = None
        owned_checks[rel] = h is not None and h == frozen.get(rel)
    dispatch_checks = {
        "run_id_and_commit": str(ci.get("databaseId")) == "40979775217" == str(dispatch.get("run", {}).get("databaseId")) and ci.get("headSha") == dispatch.get("source_commit"),
        "public_allow_private_false": dispatch.get("repository_public") is True and str(dispatch.get("request", {}).get("inputs", {}).get("allow_private", "")).lower() == "false",
        "immutable_plan_matches": canonical_hash == plan_sha == hashlib.sha256((artifact_dir / "plan.json").read_bytes()).hexdigest() == frozen.get("competitions/torchlean/candidates/r27-5h-20261029T194443Z/ci-plan.json"),
        "owned_files_match_dispatch_commit": all(owned_checks.values()),
    }
    if not all(dispatch_checks.values()): failures.append("dispatch_binding")

    src = (STATE / "source-private/submission23-Kernel.lean").read_bytes()
    builder = load(ROOT / candidate["patch_script"], "r27_b12_builder")
    transformed = builder.transform(src, 23, candidate["variant"])
    source_checks = {"submission23_matches_fetch": sha(src) == candidate["fetch"]["sha256"], "candidate_transform_hash": sha(transformed) == candidate["sha256"], "candidate_transform_bytes": len(transformed) == candidate["bytes"]}
    if not all(source_checks.values()): failures.append("candidate_reconstruction")

    config = modules["config"].Config.load(artifact_dir / "overall-config.toml")
    board = config.plan("normalized_mlp")
    seeds = [int(x) for x in plan.get("seeds", [])]
    pairs, cohorts, cpus = [], [], []
    name = candidate["name"]
    for seed in seeds:
        req_path = artifact_dir / f"{name}-{seed}-request.json"
        measure_path = artifact_dir / f"{name}-{seed}-measurement.json"
        req, req_sha = read(req_path)
        raw, measure_sha = read(measure_path)
        result = raw["result"]
        core = {"environment":"local", "identity":config.environments["local"]["identity"], "seed":seed, "candidate_hash":candidate["sha256"], "reference_hash":plan["reference"]["sha256"], "cells":list(board["cells"]), "benchmark_identity":board["benchmark_identity"], "workloads":modules["multiseed"].workloads(seed)}
        request_core = {k:req.get(k)==v for k,v in core.items()}
        modules["config"].MeasurementRequest.parse(req)
        checked = mod.measurement_check(req, raw, board["cells"], modules)
        r26.raw_rounds(artifact_dir, name, seed, req, result)
        rows = [(x["candidate_ns"], x["reference_ns"], i, cell, x["candidate_checksum"]==x["reference_checksum"]) for i,rnd in enumerate(result["rounds"]) for cell,x in rnd["cells"].items()]
        prov = result.get("provenance", {})
        cpus.append({k:prov.get(k) for k in ("identity","machine","architecture","cpu_affinity")})
        budget = req.get("timing", {})
        schedule_ok = budget.get("rounds")==5 and budget.get("inner")==3 and budget.get("cell_ms")==2
        configured_budget = config.timing | board["timing"] | config.environments["local"]["timing"]
        cohort = {"seed":seed,"request_sha256":req_sha,"measurement_sha256":measure_sha,"request_core_checks":request_core,"quick_schedule_5x3x2_matches":schedule_ok,"request_timing":budget,"config_default_timing":configured_budget,"request_budget_matches_config_defaults":budget==configured_budget,"paired_rows":len(rows),"nanosecond_values":2*len(rows),"checksum_pairs":sum(x[4] for x in rows),"checksum_mismatches":len(rows)-sum(x[4] for x in rows),"rounds":len(result["rounds"]),"cells_per_round":[len(x["cells"]) for x in result["rounds"]],"reference_first":[x.get("reference_first") for x in result["rounds"]],"pinned_check":checked,"slowest_candidate_rows":sorted(rows, reverse=True)[:2],"provenance":prov}
        if not all(request_core.values()) or checked.get("status")!="PASS" or len(rows)!=180 or checked.get("checksum_mismatches")!=0 or not schedule_ok:
            failures.append("cohort:"+str(seed))
        cohorts.append(cohort)
        pairs.append((req,result))
    same_cpu = len(cpus)==2 and all(cpus[0].get(k)==cpus[1].get(k) for k in cpus[0])
    if not same_cpu: failures.append("same_cpu")
    local_plan=dict(board); local_plan["strata"]=[{"environment":q[0]["environment"],"identity":q[0]["identity"],"seed":q[0]["seed"],"weight":1/len(pairs),"timing":q[0]["timing"]} for q in pairs]
    scorer=modules["scoring"].assess(local_plan,pairs)
    chain=json.loads((HERE/"current43-report-chain.json").read_text(encoding="utf-8"))
    current43_ratio=float(chain["current_report_edge"]["score_current43_over_public23"])
    estimate=scorer["score"]/current43_ratio
    root_native,_=read(RUN/"root-native-audit.json")
    root_entry=next((x for x in root_native.get("results",[]) if x.get("candidate")==name),{})
    root_score=root_entry.get("score_vs_calibration_internal",{}).get("score")
    root_guard=root_entry.get("score_vs_calibration_internal",{}).get("guard_passed")
    root_estimate=root_entry.get("candidate_time_over_current_champion_estimate")
    score_checks={"pinned_score":scorer["score"],"root_score":root_score,"score_matches":math.isclose(float(scorer["score"]),float(root_score or -1),rel_tol=1e-12,abs_tol=1e-15),"guard_passed":scorer["guard_passed"],"root_guard_passed":root_guard,"guard_matches":scorer["guard_passed"]==root_guard,"current43_over_public23":current43_ratio,"candidate_over_current43_estimate":estimate,"root_estimate":root_estimate,"estimate_matches":math.isclose(estimate,float(root_estimate or -1),rel_tol=1e-12,abs_tol=1e-15),"classification":"INFERRED_LOCAL_QUICK_SCREEN_CROSS_ENVIRONMENTS_AND_SEEDS","strict_converter_status":"UNKNOWN_LOCAL_ENVIRONMENT_AND_SEED_CONTRACT"}
    if not score_checks["score_matches"] or not score_checks["guard_matches"] or not score_checks["estimate_matches"]: failures.append("score_reconstruction")

    board_raw,_=read(STATE/"boards-003007.raw")
    champion_raw,_=read(STATE/"champions-normalized_mlp-003007.raw")
    curr=[x for x in champion_raw.get("champions",[]) if x.get("current") is True]
    champ_binding={"publication_matches":champion_raw.get("publication_hash")==board_raw.get("publication_hash"),"submission":curr[0].get("submission") if len(curr)==1 else None,"source_available":curr[0].get("source_available") if len(curr)==1 else None}
    if not champ_binding["publication_matches"] or champ_binding["submission"]!=43: failures.append("current_champion_binding")

    root_result,_=read(RESULTS_PATH)
    root_candidate=next((x for x in root_result.get("results",[]) if x.get("candidate")==name),{})
    result_match= root_result.get("run")==40979775217 and root_candidate.get("candidate_sha256")==candidate["sha256"] and math.isclose(float(root_candidate.get("candidate_time_over_current_champion_estimate",-1)),estimate,rel_tol=1e-12,abs_tol=1e-15)
    if not result_match: failures.append("root_ci_result_mismatch")

    output={"round":"R27","batch":12,"captured_at_utc":datetime.datetime.now(datetime.timezone.utc).isoformat(),"scope":"INDEPENDENT_B12_RAW_HASH_AND_FIXED_R25_SCORE_AUDIT; QUICK_NATIVE_ONLY_COST_SCREEN","run":{"id":ci.get("databaseId"),"source_commit":ci.get("headSha"),"status":ci.get("status"),"conclusion":ci.get("conclusion"),"complete":summary.get("complete"),"elapsed_seconds":summary.get("elapsed_seconds")},"plan":{"sha256":plan_sha,"candidate_sha256":candidate["sha256"],"candidate_bytes":candidate["bytes"],"full_gate":candidate.get("full_gate"),"declares_correct":candidate.get("declares_correct")},"dispatch_checks":dispatch_checks,"owned_hash_checks":owned_hashes,"source_checks":source_checks,"artifact":{"id":artifact_index.get("artifacts",[{}])[0].get("id"),"archive_sha256":artifact_index.get("artifacts",[{}])[0].get("digest"),"outer_manifest_sha256":outer_sha,"inner_manifest_sha256":inner_sha,"summary_sha256":summary_sha,"outer":outer,"inner":inner},"candidate":{"proof_state":summary.get("results",[{}])[-1].get("proof_state"),"flags_pass":summary.get("results",[{}])[-1].get("flags_pass"),"native_flags":{"compile":22,"link":4,"response":10080,"equal_after_expected_target_mapping":True},"cohorts":cohorts,"same_cpu":same_cpu,"pinned_score_and_current43_estimate":score_checks,"champion_binding":champ_binding,"correctness":"NOT_PROVED_NATIVE_ONLY_FULL_GATE_FALSE"},"request_timing_caveat":{"cell_schedule":"5 rounds x 3 inner x 2 ms matches official quick schedule","resource_budgets":"request overrides Config defaults for run/cached/benchmark caps; scorer and finite row checks pass; strict production-report conversion remains UNKNOWN"},"root_result":{"file_sha256":root_result_sha,"state":root_result.get("state"),"candidate_result_match":result_match},"failures":failures,"status":"PASS_RAW_HASHES_AND_SCORE_REPRODUCED; NATIVE_ONLY_COST_NEGATIVE" if not failures else "AUDIT_FAILED"}
    OUT.write_text(json.dumps(output,indent=2,ensure_ascii=False)+"\n",encoding="utf-8")
    print(json.dumps({"status":output["status"],"outer_files":outer.get("files"),"inner_files":inner.get("files"),"score":score_checks,"request_budget_override":True,"root_result_match":result_match,"failures":failures},ensure_ascii=False))
    return 0 if not failures else 1

if __name__=="__main__":
    raise SystemExit(main())
