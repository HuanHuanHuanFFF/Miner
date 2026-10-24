"""Adopt only freshly reread three-group evidence; no Git, CI or formal submission."""
import argparse
from copy import deepcopy
from datetime import datetime, timezone
import hashlib
import importlib.util
import json
import math
import os
from pathlib import Path
import statistics
import sys
import uuid

HERE = Path(__file__).resolve().parent
ROOT = HERE.parents[4]
REL = HERE.relative_to(ROOT)
BASELINE = "df5c61a0ca24a8ef18c0c42d83bdd23466872d3fe8f39dd912e9c347b27fb172"
OPS = ("add", "mul", "sum", "bmm")


def require(ok, message):
    if not ok:
        raise ValueError(message)


def sha(raw):
    return hashlib.sha256(raw).hexdigest()


def encoded(value):
    return (json.dumps(value, ensure_ascii=False, indent=2) + "\n").encode()


def read(path):
    return json.loads(Path(path).read_bytes())


def module(name, path):
    old = sys.dont_write_bytecode
    sys.dont_write_bytecode = True
    try:
        spec = importlib.util.spec_from_file_location(name, path)
        result = importlib.util.module_from_spec(spec)
        spec.loader.exec_module(result)
        return result
    finally:
        sys.dont_write_bytecode = old


def diagnostic(value):
    if isinstance(value, dict):
        return value.get("diagnostic_only") is True or any(diagnostic(v) for v in value.values())
    return isinstance(value, list) and any(diagnostic(v) for v in value)


class Transaction:
    """Content-CAS writes and rollback; never replace a concurrently changed file."""
    def __init__(self, paths):
        self.before = {Path(p).resolve(): Path(p).read_bytes() if Path(p).exists() else None for p in paths}
        self.owned = {}

    def unchanged(self):
        for path, before in self.before.items():
            current = path.read_bytes() if path.exists() else None
            require(current == self.owned.get(path, before), "Concurrent external change: " + str(path))

    def write(self, path, raw):
        path = Path(path).resolve()
        require(path in self.before, "Unowned output path: " + str(path))
        expected = self.owned.get(path, self.before[path])
        require((path.read_bytes() if path.exists() else None) == expected, "Concurrent external change: " + str(path))
        temporary = path.with_name(path.name + ".adopt-" + uuid.uuid4().hex + ".tmp")
        try:
            with temporary.open("xb") as stream:
                stream.write(raw)
            require((path.read_bytes() if path.exists() else None) == expected, "Concurrent external change before replacement")
            os.replace(temporary, path)
            self.owned[path] = raw
        finally:
            if temporary.exists():
                temporary.unlink()

    def rollback(self):
        results = []
        for path, owned in reversed(list(self.owned.items())):
            current = path.read_bytes() if path.exists() else None
            if current != owned:
                results.append({"path": str(path), "status": "EXTERNAL_CHANGE_PRESERVED"})
                continue
            before = self.before[path]
            try:
                if before is None:
                    path.unlink()
                else:
                    temporary = path.with_name(path.name + ".rollback-" + uuid.uuid4().hex + ".tmp")
                    try:
                        with temporary.open("xb") as stream:
                            stream.write(before)
                        require(path.read_bytes() == owned, "External change during rollback")
                        os.replace(temporary, path)
                    finally:
                        if temporary.exists():
                            temporary.unlink()
                results.append({"path": str(path), "status": "RESTORED"})
            except Exception as exc:
                results.append({"path": str(path), "status": "ROLLBACK_FAILED_OR_CONFLICT", "reason": str(exc)})
        return results


def scoring_pairs(records, candidate_pairs, estimator, root):
    """Authenticate retainedDF separately from the immutable estimator's 41 control."""
    result = []
    fields = ("run", "seed", "suite_sha256", "official_commit", "runner_execution",
              "drawn_plan_sha256", "provenance_sha256", "incumbent_sha256",
              "reference_champion_sha256", "verifier_fingerprint", "cell_work")
    for candidate, _ in candidate_pairs:
        matches = [r for r in records if r.get("full_gate") is True and
                   r.get("run") == candidate["run"] and r.get("kernel_sha256") == BASELINE and
                   r.get("candidate") == "f01-d12-scalar-combined" and
                   (root / r["verdict"]).parent == (root / candidate["verdict"]).parent]
        require(len(matches) == 1, "No unique same-runner retainedDF score baseline")
        baseline = estimator.checked_record(matches[0], root=root)
        require(all(candidate.get(field) == baseline.get(field) for field in fields),
                "RetainedDF score baseline execution differs from candidate")
        require(candidate.get("runner_execution") is not None,
                "Missing authenticated runner execution for score baseline")
        result.append((candidate, baseline))
    return result


def prepare_views(view, state, freeze, selection, rows, pairs, runs, root, now):
    """Pure narrow updates: copy existing objects, preserve policy/resources/CI."""
    require(state["kernel_sha256"] == view["kernel_sha256"] == BASELINE, "Retained source/state is no longer6c")
    require(selection.get("accepted") is True and selection.get("group_count") == 3 and
            not selection.get("failures") and not diagnostic(selection), "Three original groups not accepted")
    require(set(selection["groups"]) == {"D", "A", "B"}, "Missing independent group")
    candidate = freeze["candidate"]
    require(candidate["sha256"] != BASELINE and not diagnostic(freeze) and not any(diagnostic(r) for r in rows), "Diagnostic or baseline source rejected")
    require(len({r["run"] for r in rows}) == len(rows) and set(runs.values()) <= {r["run"] for r in rows}, "Missing/duplicate retained full-gate row")
    require(all(r["full_gate"] is True and r["kernel_sha256"] == candidate["sha256"] and
                r["suite_sha256"] == freeze["suite_sha256"] for r in rows), "Wrong full-gate source/suite")
    for role in ("D", "A", "B"):
        group = selection["groups"][role]
        require(group["run"] == runs[role] and group["seed"] == freeze["groups"][role]["seed"] and
                group["relative_normalized_ratio"] <= freeze["selection_policy"]["headline_normalized_ratio_max"] and
                group["gain_p05"] > freeze["selection_policy"]["gain_p05_min_exclusive"], "Independent group fails original policy")
    v, s = deepcopy(view), deepcopy(state)
    # Adoption selects the new retained package. An old research overlay must
    # not hide it or compare its stale source/model against the new estimate.
    v.pop('dashboard_research_candidate', None)
    s['current_multiplier_view'].pop('displayed_research_candidate', None)
    # A newly accepted source gets a new model. Never carry the previous
    # source's display freeze into the new source; the old receipt stays intact.
    v.pop('retained_numeric_model_freeze', None)
    s['current_multiplier_view'].pop('retained_numeric_model_freeze', None)
    independent = [runs[r] for r in ("D", "A", "B")]
    all_runs = [r["run"] for r in rows]
    by_run = {r["run"]: r for r in rows}
    independent_rows = [by_run[r] for r in independent]
    relative = [selection["groups"][r]["relative_normalized_ratio"] for r in ("D", "A", "B")]
    previous = {"candidate": view["candidate"], "kernel_sha256": BASELINE, "whole_normalized_ratios": relative,
                "scope": "Three frozen independent groups against retainedDF"}
    op_relative = {}
    for c, b in pairs:
        for row in (c,b):
            totals={op:sum(cell['submission_ns']*row['cell_work'][key] for key,cell in row['classes'].items() if key.startswith(op+':')) for op in OPS}
            references={op:sum(cell['incumbent_ns']*row['cell_work'][key] for key,cell in row['classes'].items() if key.startswith(op+':')) for op in OPS}
            require(all(math.isclose(totals[op],row['operation_total_ns'][op],rel_tol=1e-12) and
                        math.isclose(references[op],row['operation_reference_total_ns'][op],rel_tol=1e-12) for op in OPS),"Index operation totals differ from authenticated cells")
            require(math.isclose(sum(totals.values())/sum(references.values()),row['ratio'],rel_tol=1e-10),"Index headline differs from authenticated cells")
            require(all(math.isclose(totals[op]/sum(totals.values())*100,row['time_share_percent'][op],rel_tol=1e-12) for op in OPS),"Index shares differ from authenticated cells")
        op_relative[c["run"]] = {op: (c["operation_total_ns"][op] / c["operation_reference_total_ns"][op]) /
                                      (b["operation_total_ns"][op] / b["operation_reference_total_ns"][op]) for op in OPS}
        if c['run'] in independent:
            role=next(role for role in ("D","A","B") if runs[role]==c['run'])
            require(math.isclose(c['ratio']/b['ratio'],selection['groups'][role]['relative_normalized_ratio'],rel_tol=1e-10),"Index candidate/baseline differs from fresh guard")
    previous["bmm_normalized_ratios"] = [op_relative[r]["bmm"] for r in independent]
    ratios = [{op: r["operation_total_ns"][op] / r["operation_reference_total_ns"][op] for op in OPS} for r in rows]
    public = {"whole_range": [min(1/r["ratio"] for r in rows), max(1/r["ratio"] for r in rows)],
              "operations": {op: {"speedup_range": [min(1/r[op] for r in ratios), max(1/r[op] for r in ratios)],
                                    "time_share_median_percent": statistics.median(r["time_share_percent"][op] for r in rows)} for op in OPS}}
    selection = deepcopy(selection)
    selection.update(adoption_performed=True, independent_adoption_runs=independent)
    v.update(as_of_utc=now, candidate=candidate["name"], kernel_sha256=candidate["sha256"], full_gate_runs=all_runs,
             independent_adoption_runs=independent, local_selection_guard=selection, public_speedup=public,
             previous_package=previous, display_sample_scope="Every exact-source full public gate, including additional slower samples; independent adoption is separately D/A/B")
    # All direct-comparison fields concern the previous candidate, not the new one.
    v["champion"]["candidate_over_champion_time"] = "UNKNOWN"
    v["champion"]["candidate_over_champion_time_by_operation"] = {op: "UNKNOWN" for op in OPS}
    source = root / "competitions/floatlib/candidates" / candidate["name"] / "Kernel.lean"
    s.update(updated_at_utc=now, candidate=source.parent.relative_to(root).as_posix(), kernel=source.relative_to(root).as_posix(),
             kernel_sha256=candidate["sha256"], kernel_bytes=source.stat().st_size,
             manifest=source.with_name("manifest.json").relative_to(root).as_posix(),
             proof_status="PASS_FULL_CURRENT_PUBLIC_SUITE_THREE_FROZEN_INPUT_GROUPS", independent_adoption_runs=independent,
             local_selection_guard=selection, previous_package=previous,
             selection_scope="Retained after three frozen exact-source original full-gate groups; direct champion admission remains UNKNOWN")
    s["performance"] = {"protocol": "Original current public-v2 complete gates; three independent frozen adoption groups",
        "full_gate_runs": all_runs, "independent_adoption_runs": independent,
        "independent_samples": [selection["groups"][r] for r in ("D", "A", "B")],
        "independent_seeds": [r["seed"] for r in independent_rows],
        "independent_ratio_vs_shipped": [r["ratio"] for r in independent_rows],
        "seeds": [r["seed"] for r in rows], "ratio_vs_shipped": [r["ratio"] for r in rows],
        "kernels_vs_shipped": ratios,
        "independent_kernels_vs_shipped": [{op:r["operation_total_ns"][op]/r["operation_reference_total_ns"][op] for op in OPS} for r in independent_rows],
        "local_selection_guard": selection, "previous_package": previous,
        "all_source_samples": [{"run":r["run"],"seed":r["seed"],"ratio":r["ratio"],"verdict":r["verdict"],"verdict_sha256":r["verdict_sha256"],
                                "sample_role":r.get('sample_role','UNKNOWN_HISTORICAL_ROLE'),
                                "execution_has_observer":r.get('execution_has_observer','UNKNOWN_HISTORICAL_OBSERVER'),
                                "codegen_capture_state":r.get('codegen',{}).get('state','NOT_REQUESTED' if r.get('execution_has_observer') is False else 'UNKNOWN')} for r in rows],
        "evidence": view["public_results"]}
    s["current_multiplier_view"].update(candidate=candidate["name"], candidate_time_over_current_champion="UNKNOWN",
        all_retained_source_public_gate_runs=all_runs, independent_adoption_runs=independent,
        candidate_current_public_suite_speedup_range=public["whole_range"])
    s["current_champion_comparison"].update(candidate=candidate["name"], direct_paired_ratio="UNKNOWN")
    return v, s


def adopt(freeze_path, expected_sha, runs, root=ROOT, verifier=None, estimator=None, renderer=None):
    """Runtime entry. Tests inject original-I/O adapters; real CLI rereads raw gates."""
    root = Path(root).resolve()
    own = root / "competitions/floatlib/candidates/f01-d7-research"
    here = root / REL
    attempt = here / ("adoption-attempt-" + datetime.now(timezone.utc).strftime("%Y%m%dT%H%M%SZ") + "-" + uuid.uuid4().hex[:8])
    attempt.mkdir()
    paths = {"view":own/"multiplier-comparison.json", "state":root/"competitions/floatlib/coordination/development-status.json",
             "model":own/"champion-time-estimate.json", "dashboard":root/"dashboard.md"}
    tx = Transaction(paths.values())
    receipt = {"accepted":False,"adoption_performed":False,"status":"PREFLIGHT_REJECTED","failures":[],"rollback":[]}
    try:
        require(__debug__, "Optimized Python refused")
        verifier = verifier or module("r13_fresh_verifier",here/"verify-three-groups.py")
        estimator = estimator or module("r13_frozen_estimator",root/"competitions/floatlib/scripts/estimate_champion_time.py")
        renderer = renderer or module("r13_renderer",root/"competitions/floatlib/scripts/render_dashboard.py")
        freeze = read(freeze_path)
        require(not diagnostic(freeze) and len(set(runs.values()))==3 and set(runs)=={"D","A","B"}, "Diagnostic or duplicate/missing cohort rejected")
        guard = verifier.import_guard()
        def frozen():
            verifier.verify_freeze(freeze,expected_sha,freeze_path,guard,root=root)
            for path in (here/"adopt-three-confirmed.py",root/"competitions/floatlib/scripts/estimate_champion_time.py",root/"competitions/floatlib/scripts/render_dashboard.py",Path(estimator.DEFAULT_ANCHOR)):
                key=path.relative_to(root).as_posix()
                require(key in freeze["files"] and sha(path.read_bytes())==freeze["files"][key]["sha256"], "Missing/changed adoption estimator anchor freeze: "+key)
        frozen()
        model_binding=freeze.get('retained_model',{})
        require(model_binding.get('source_sha256')==BASELINE and
                model_binding.get('model_path')==paths['model'].relative_to(root).as_posix() and
                sha(paths['model'].read_bytes())==model_binding.get('sha256'),
                'Retained numeric model changed before adoption')
        for role in runs:
            if "run" in freeze["groups"][role]:
                require(runs[role]==freeze["groups"][role]["run"],"Run differs from frozen role")
        view,state = read(paths["view"]),read(paths["state"])
        require(state["kernel_sha256"]==view["kernel_sha256"]==BASELINE and sha((root/state["kernel"]).read_bytes())==BASELINE,"Current state/source no longerDF")
        inputs=(root/view["public_results"],own/"current-official-snapshot.json",Path(estimator.DEFAULT_ANCHOR),
                root/"competitions/floatlib/candidates"/freeze["candidate"]["name"]/"Kernel.lean")
        input_hashes={path:sha(path.read_bytes()) for path in inputs}
        def unchanged_inputs():
            require(all(sha(path.read_bytes())==value for path,value in input_hashes.items()),"Source/index/official snapshot changed during adoption")
        selection=verifier.verify_three_groups(freeze,runs,guard,root=root,own=own)
        receipt["fresh_three_group_verification"]=selection
        require(selection.get("accepted") is True and selection.get("group_count")==3 and not selection.get("failures") and not diagnostic(selection),"Fresh original three-group guard rejected")
        frozen()
        # Existing main's dry run authenticates original official receipts/anchor.
        official=estimator.main(["--dry-run","--anchor",str(estimator.DEFAULT_ANCHOR)])
        require(official["champion_digest"]==view["champion"]["digest"] and official["champion_submission"]==view["champion"]["submission"],"Current champion/view changed")
        records=read(root/view["public_results"])["records"]
        rows=[r for r in records if r["kernel_sha256"]==freeze["candidate"]["sha256"] and r.get("full_gate")]
        require(rows and not any(diagnostic(r) for r in rows),"No non-diagnostic full source rows")
        all_runs=[r["run"] for r in rows]
        pairs=estimator.select_pairs(records,all_runs,freeze["candidate"]["sha256"],read(estimator.DEFAULT_ANCHOR),root=root)
        predicted=estimator.estimate_from_anchor(read(estimator.DEFAULT_ANCHOR),freeze["candidate"]["sha256"],official["champion_digest"],official["champion_suite"],pairs)
        receipt["estimate_preflight"]={k:predicted[k] for k in ("operations","whole","kernel_sha256")}
        score_pairs=scoring_pairs(records,pairs,estimator,root)
        new_view,new_state=prepare_views(view,state,freeze,selection,rows,score_pairs,runs,root,datetime.now(timezone.utc).isoformat())
        frozen(); unchanged_inputs(); tx.unchanged()
        require(sha((root/state["kernel"]).read_bytes())==BASELINE,"Retained source changed before commit")
        for path,raw in tx.before.items():
            if raw is not None:
                with (attempt/(path.name+".before")).open("xb") as backup: backup.write(raw)
        tx.write(paths["view"],encoded(new_view)); tx.write(paths["state"],encoded(new_state))
        original_save=estimator.save
        try:
            estimator.save=lambda path,value: tx.write(path,encoded(value))
            estimator.main(["--anchor",str(estimator.DEFAULT_ANCHOR)])
        finally:
            estimator.save=original_save
        # Estimator touches policy timestamps; preserve the exact pre-adoption UI policy.
        v,s=read(paths["view"]),read(paths["state"])
        require(v["champion"]["digest"]==view["champion"]["digest"] and v["champion"]["submission"]==view["champion"]["submission"],"Estimator changed champion identity")
        v["dashboard_policy"]=deepcopy(view["dashboard_policy"])
        s["current_multiplier_view"]["dashboard_policy"]=deepcopy(state["current_multiplier_view"]["dashboard_policy"])
        changed_keys={"updated_at_utc","candidate","kernel","kernel_sha256","kernel_bytes","manifest","proof_status",
                      "independent_adoption_runs","local_selection_guard","previous_package","selection_scope","performance",
                      "current_multiplier_view","current_champion_comparison"}
        require(all(s.get(key)==value for key,value in state.items() if key not in changed_keys),
                "Unexpected mutation of resources/authorization/research/CI or unrelated state")
        tx.write(paths["view"],encoded(v)); tx.write(paths["state"],encoded(s))
        original_write_text=Path.write_text
        def tracked_write_text(path,text,encoding=None,errors=None,newline=None):
            require(Path(path).resolve()==paths["dashboard"].resolve(),"Unexpected renderer output")
            tx.write(path,text.encode(encoding or "utf-8",errors or "strict")); return len(text)
        try:
            Path.write_text=tracked_write_text
            renderer.main()
        finally:
            Path.write_text=original_write_text
        frozen(); unchanged_inputs(); tx.unchanged()
        receipt.update(accepted=True,adoption_performed=True,status="THREE_GROUP_ADOPTED",all_source_full_gate_runs=all_runs,independent_adoption_runs=[runs[r] for r in ("D","A","B")])
    except Exception as exc:
        receipt["failures"].append({"type":type(exc).__name__,"reason":str(exc)})
        receipt["rollback"]=tx.rollback()
        receipt["status"]="WRITE_FAILED_ROLLBACK_RECORDED" if tx.owned else "PREFLIGHT_REJECTED"
    receipt.update(as_of_utc=datetime.now(timezone.utc).isoformat(),freeze=str(freeze_path),expected_freeze_sha256=expected_sha,
                   before_sha256={str(p):sha(b) if b is not None else None for p,b in tx.before.items()},
                   after_sha256={str(p):sha(p.read_bytes()) if p.exists() else None for p in tx.before})
    receipt_path=attempt/"receipt.json"
    try:
        with receipt_path.open("xb") as output: output.write(encoded(receipt))
    except Exception as exc:
        receipt.update(accepted=False,adoption_performed=False,status="AUDIT_WRITE_FAILED_ROLLBACK_RECORDED")
        receipt["failures"].append({"type":type(exc).__name__,"reason":"Audit receipt write failed: "+str(exc)})
        receipt["rollback"]=tx.rollback()
        receipt["after_sha256"]={str(p):sha(p.read_bytes()) if p.exists() else None for p in tx.before}
        receipt_path=attempt/"receipt-audit-failure.json"
        with receipt_path.open("xb") as output: output.write(encoded(receipt))
    return receipt,receipt_path


def main(argv=None):
    parser=argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--freeze",type=Path,required=True);parser.add_argument("--freeze-sha256",required=True)
    parser.add_argument("--discovery",type=int,required=True);parser.add_argument("--confirmation-a",type=int,required=True);parser.add_argument("--confirmation-b",type=int,required=True)
    args=parser.parse_args(argv)
    result,path=adopt(args.freeze,args.freeze_sha256,{"D":args.discovery,"A":args.confirmation_a,"B":args.confirmation_b})
    print(json.dumps({"accepted":result["accepted"],"status":result["status"],"receipt":str(path)}))
    return 0 if result["accepted"] else 2


if __name__=="__main__":
    sys.exit(main())
