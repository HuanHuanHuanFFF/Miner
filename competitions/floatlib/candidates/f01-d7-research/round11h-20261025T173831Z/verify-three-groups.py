"""R14 receipt-only validation of one discovery and two frozen confirmations."""
import argparse
from copy import deepcopy
from datetime import datetime, timezone
import hashlib
import importlib.util
import json
from pathlib import Path
import re
import sys

HERE = Path(__file__).resolve().parent
OWN = HERE.parent
ROOT = HERE.parents[4]
BASELINE_SHA = "622d8394a7127e93dcaf992c62c6dfcff7208d212738409a5e34525dfafd1a58"
CONTROL_NAME = "f01-r8-combined-result-guard"
CONTROL_SHA = "41bce4856c4c921dd67b6115928df16e5e8ed08a55b71f1296d28b77cf9ce9a7"
ROLES = ("D", "A", "B")
SHAPE_FIELDS = ("name", "kernel", "timed", "length", "batch", "m", "n", "p", "work")


def require(condition, message):
    if not condition:
        raise ValueError(message)


def digest(path):
    return hashlib.sha256(Path(path).read_bytes()).hexdigest()


def read(path):
    return json.loads(Path(path).read_bytes())


def canonical_sha(value):
    return hashlib.sha256(json.dumps(value, sort_keys=True, separators=(",", ":"), allow_nan=False).encode()).hexdigest()


def import_guard():
    spec = importlib.util.spec_from_file_location("r18_unchanged_adoption_guard", HERE / "adoption-guard.py")
    guard = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(guard)
    return guard


def import_binding():
    spec = importlib.util.spec_from_file_location('r18_execution_binding', HERE / 'execution-binding.py')
    binding = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(binding)
    return binding


def retained_model_identity(root=ROOT):
    own=Path(root)/'competitions/floatlib/candidates/f01-d7-research'
    here=own/'round11h-20261025T173831Z'
    receipt=here/'retained-estimate-freeze.json'
    prior=read(receipt);plan=read(here/'round-plan.json')
    require(prior['source_sha256']==BASELINE_SHA and prior['model_sha256']==plan['model_sha256'], 'Retained B2 model identity differs')
    require(digest(Path(root)/prior['frozen_snapshot'])==prior['model_sha256'], 'Retained model snapshot changed')
    original=Path(root)/prior['original_adoption']
    require(digest(original)==prior['original_adoption_sha256'] and read(original)['adoption_performed'] is True, 'Prior B2 adoption receipt differs')
    return {'source_sha256':BASELINE_SHA,'model_path':prior['model_path'],'sha256':prior['model_sha256'],
            'receipt_path':receipt.relative_to(root).as_posix(),'receipt_sha256':digest(receipt)}


def verify_freeze(freeze, expected_sha256, freeze_path, guard, root=ROOT):
    """External freeze digest is mandatory; a self-recomputed digest is insufficient."""
    require(digest(freeze_path) == expected_sha256, "Frozen cohort bytes differ from external SHA-256")
    require(freeze.get("schema_version") == 1 and freeze.get("required_groups") == 3,
            "Exactly three predeclared groups required")
    require(freeze.get("holdouts_unseen_before_freeze") is True and bool(freeze.get("frozen_at_utc")),
            "Missing pre-observation freeze declaration")
    timestamp = datetime.fromisoformat(freeze["frozen_at_utc"].replace("Z", "+00:00"))
    require(timestamp.tzinfo is not None and timestamp.utcoffset().total_seconds() == 0, "Freeze time must declare UTC")
    require(freeze["baseline"]["sha256"] == BASELINE_SHA and
            freeze["baseline"]["name"] == "f01-r15-dev-packed-b2-1", "Baseline must be exact retained41")
    require(freeze["candidate"]["sha256"] != BASELINE_SHA, "Candidate is the baseline")
    require(freeze.get('estimator_control') == {'name':CONTROL_NAME,'sha256':CONTROL_SHA},
            'Missing/wrong frozen estimator control41')
    require(freeze.get('retained_model')==retained_model_identity(root), 'Missing/changed retained model identity')
    require(re.fullmatch(r"[0-9a-f]{64}", freeze["candidate"]["sha256"]) is not None, "Invalid candidate digest")
    require(set(freeze["groups"]) == set(ROLES), "Missing/extra frozen role")
    require(len({freeze["groups"][r]["seed"] for r in ROLES}) == 3, "Frozen seeds are not distinct")
    require(all(type(freeze["groups"][r]["seed"]) is int and freeze["groups"][r]["seed"] > 0 for r in ROLES), "Invalid frozen seed")
    require(type(freeze["groups"]["D"].get("run")) is int, "Discovery run must be frozen")
    orders = freeze.get('candidate_orders', {})
    require(set(orders) == set(ROLES), 'Missing frozen measurement orders')
    require(all(len(order) == len(set(order)) and set(order) == set(orders['D']) for order in orders.values()),
            'Duplicate or different sources in frozen orders')
    require({freeze['candidate']['name'], freeze['baseline']['name']} <= set(orders['D']),
            'Missing primary sources in frozen orders')
    require(CONTROL_NAME in orders['D'], 'Missing estimator control in frozen orders')
    require(freeze["selection_policy"] == guard.SELECTION_POLICY and
            all(type(freeze["selection_policy"][k]) is type(v) for k, v in guard.SELECTION_POLICY.items()),
            "Frozen policy differs from unchanged guard")
    require(freeze["suite_sha256"] == guard.SUITE_SHA and freeze["generator_sha256"] == guard.GENERATOR_SHA,
            "Frozen suite/generator differs from unchanged guard")
    require(set(freeze["reference"]) == {"incumbent_sha256", "champion_sha256"} and
            all(isinstance(v, str) and re.fullmatch(r"[0-9a-f]{64}", v) for v in freeze["reference"].values()), "Missing frozen reference identities")
    binding = import_binding()
    binding.verify_freeze(freeze)
    required = binding.required_local_paths(root, HERE) + [root / n for n in binding.EXECUTION_FILES]
    files = freeze["files"]
    for path in required:
        key = path.relative_to(root).as_posix()
        require(key in files, "Missing frozen helper/rule: " + key)
    for relative, info in files.items():
        path = guard.inside(root, relative)
        require(digest(path) == info["sha256"], "Frozen file changed: " + relative)
    for role in ("candidate", "baseline"):
        entry = freeze[role]
        require(re.fullmatch(r"[A-Za-z0-9][A-Za-z0-9_.-]*", entry["name"]) is not None, "Invalid source name")
        path = root / "competitions/floatlib/candidates" / entry["name"] / "Kernel.lean"
        require(digest(path) == entry["sha256"], "Frozen source changed: " + role)
    plan = read(HERE / "selection-policy.json")
    require(plan["additional_inputs"]["groups_total_target"] == 3 and
            plan["selection_policy"] == freeze["selection_policy"] and
            plan["baseline"]["sha256"] == BASELINE_SHA, "Round rules differ from cohort")


def shape_evidence(drawn_plan):
    cases = drawn_plan["cases"]
    require(cases and len({c["name"] for c in cases}) == len(cases), "Empty/duplicate drawn cases")
    cases = sorted(cases, key=lambda c: c["name"])
    shapes = [{k: c[k] for k in SHAPE_FIELDS} for c in cases]
    generation = [{k: v for k, v in c.items() if k not in SHAPE_FIELDS} for c in cases]
    return {"shape_vector": shapes, "shape_sha256": canonical_sha(shapes),
            "generation_vector": generation, "generation_sha256": canonical_sha(generation),
            "cases": len(cases), "timed_cases": sum(c["timed"] for c in cases)}


def compare_inputs(left, right):
    a, b = left["shape_vector"], right["shape_vector"]
    require([x["name"] for x in a] == [x["name"] for x in b], "Different drawn case coverage")
    shape_changed = [x["name"] for x, y in zip(a, b) if x != y]
    generation_changed = [x["name"] for x, u, v in zip(a, left["generation_vector"], right["generation_vector"]) if u != v]
    require(shape_changed or generation_changed, "Distinct JSON hashes do not demonstrate different actual cases")
    return {"shape_work_changed_cases": len(shape_changed), "shape_work_changed_case_names": shape_changed,
            "bmm_shape_work_changed_cases": sum(x.startswith("bmm:") for x in shape_changed),
            "generation_changed_cases": len(generation_changed), "generation_changed_case_names": generation_changed,
            "diversity_kind": "SHAPE_WORK_AND_GENERATION" if shape_changed and generation_changed else
                              "SHAPE_WORK_ONLY" if shape_changed else "VALUE_GENERATION_ONLY",
            "scope": "Actual case fields; distinct group seed or JSON hash alone is not evidence of new shapes"}


def load_shapes(root, guard, packet):
    rp = root / "competitions/floatlib/candidates/f01-mul-log2-proof1/ci-runs" / str(packet["run_id"])
    index = read(rp / "original-artifact-hashes.json")
    artifact = guard.inside(rp, index["directory"])
    relative = "diagnostics/f01-d7-public-suite/public-suite/public-drawn-plan.json"
    path = guard.inside(artifact, relative)
    info = index["files"][relative]
    require(path.stat().st_size == info["bytes"] and digest(path) == info["sha256"] == packet["evidence"]["drawn_plan_sha256"],
            "Drawn plan differs from authenticated raw packet/index")
    result = shape_evidence(read(path))
    result.update(path=path.relative_to(root).as_posix(), raw_sha256=digest(path))
    return result


def validate_cohort(freeze, packets, shapes, pair_receipts):
    """Pure global checks, in addition to both unchanged two-group guards."""
    require(set(packets) == set(shapes) == set(ROLES), "All three groups must exist")
    for field in ("run_id", "job_id", "seed"):
        require(len({packets[r][field] for r in ROLES}) == 3, "Three distinct " + field + " values required")
    hashes = [packets[r]["evidence"].get("drawn_plan_sha256") for r in ROLES]
    require(all(isinstance(h, str) and len(h) == 64 for h in hashes) and len(set(hashes)) == 3,
            "Three nonempty distinct drawn-plan SHA-256 values required")
    require(set(pair_receipts) == {"D+A", "D+B"}, "Both original guard receipts required")
    candidate, baseline = freeze["candidate"], freeze["baseline"]
    reference = freeze["reference"]
    for role in ROLES:
        packet = packets[role]
        group = freeze["groups"][role]
        require(packet["seed"] == group["seed"], "Group differs from frozen seed: " + role)
        require([r['candidate'] for r in packet['plan']['candidates']] == freeze['candidate_orders'][role],
                "Measurement order differs from frozen role: " + role)
        if role != 'D':
            require(packet['plan'].get('sample_role') == 'FROZEN_INDEPENDENT_CONFIRMATION' and
                    packet['plan'].get('cohort', {}).get('role') == role,
                    "Confirmation role is not frozen: " + role)
            require(packet['plan']['cohort'].get('sha256') == hashlib.sha256(
                    (json.dumps(freeze, ensure_ascii=False, indent=2)+'\n').encode()).hexdigest(),
                    'Confirmation cohort digest differs: '+role)
        for frozen_key, actual_key in (("run", "run_id"), ("job", "job_id")):
            if frozen_key in group:
                require(packet[actual_key] == group[frozen_key], "Group differs from frozen " + frozen_key)
        evidence = packet["evidence"]
        require(evidence["suite_sha256"] == freeze["suite_sha256"] and
                evidence["generator_sha256"] == freeze["generator_sha256"], "Cohort suite/generator mismatch")
        require(shapes[role]["raw_sha256"] == evidence["drawn_plan_sha256"], "Shape evidence not bound to raw input")
        for entry in (candidate, baseline):
            name = entry["name"]
            require(packet["kernel_hashes"][name] == entry["sha256"], "Cohort source mismatch")
            verdict = packet["verdicts"][name]
            require(all(verdict[k] == reference[k] for k in reference), "Cohort reference mismatch")
        require(packet['kernel_hashes'].get(CONTROL_NAME)==CONTROL_SHA,'Estimator control source changed')
        control=packet['verdicts'].get(CONTROL_NAME,{})
        require(control.get('passed') is True and control.get('stage')=='score' and
                control.get('mode')=='gate' and len(control.get('rounds',[]))==25 and
                all(control.get(k)==value for k,value in reference.items()),
                'Estimator control is not a complete matching original gate')
        if role != "D":
            confirmations = [x for x in packet["plan"].get("confirmation_candidates", []) if x["candidate"] == candidate["name"]]
            require(len(confirmations) == 1 and confirmations[0]["sha256"] == candidate["sha256"] and
                    confirmations[0]["prior_discovery_run"] == packets["D"]["run_id"], "Confirmation does not link same frozen discovery/source")
    per_group = {}
    for label, confirmation_role in (("D+A", "A"), ("D+B", "B")):
        receipt = pair_receipts[label]
        require(receipt.get("accepted") is True and receipt["selection_policy"] == freeze["selection_policy"], "Original pair guard not accepted")
        require(receipt["identity"] == {"candidate": candidate["name"], "candidate_sha256": candidate["sha256"],
                                       "baseline": baseline["name"], "baseline_sha256": baseline["sha256"]}, "Pair guard source mismatch")
        require(len(receipt["samples"]) == 2, "Pair guard sample count changed")
        for role, sample in zip(("D", confirmation_role), receipt["samples"]):
            p = packets[role]
            require((sample["run"], sample["job"], sample["seed"]) == (p["run_id"], p["job_id"], p["seed"]), "Pair receipt group identity mismatch")
            require(sample["relative_normalized_ratio"] <= freeze["selection_policy"]["headline_normalized_ratio_max"] and
                    sample["gain_p05"] > freeze["selection_policy"]["gain_p05_min_exclusive"], "One group fails unchanged threshold")
            if role in per_group:
                require(per_group[role] == sample, "Discovery differs across two pair receipts")
            per_group[role] = deepcopy(sample)
    comparisons = {a + "+" + b: compare_inputs(shapes[a], shapes[b]) for a, b in (("D", "A"), ("D", "B"), ("A", "B"))}
    return {"groups": per_group, "input_comparisons": comparisons,
            "group_count": 3, "counting": "Discovery is shared by both pair calls and counted once"}


def verify_three_groups(freeze, runs, guard, root=ROOT, own=OWN, shape_loader=load_shapes):
    """Return every failure as receipt data; never adopt or mutate state."""
    receipt = {"accepted": False, "status": "NOT_THREE_GROUP_CONFIRMED", "group_count": 0,
               "pairs": {}, "groups": {}, "failures": [], "adoption_performed": False,
               "method": "LOCAL_INDEPENDENT_CROSS_GATE_BOOTSTRAP",
               "random_stream": "Each verify_adoption resets Random(90423); D then confirmation. D is shared, not a fourth group. No joint confidence or official admission claim."}
    packets = {}
    candidate, baseline = freeze["candidate"]["name"], freeze["baseline"]["name"]
    for label, role in (("D+A", "A"), ("D+B", "B")):
        try:
            result, pair = guard.verify_adoption(root, own, candidate, runs["D"], runs[role], baseline)
            receipt["pairs"][label] = result
            for item, item_role in zip(pair, ("D", role)):
                if item_role in packets:
                    require(packets[item_role] == item, "Discovery raw packet changed between guard calls")
                packets[item_role] = item
        except Exception as exc:
            receipt["failures"].append({"stage": label, "type": type(exc).__name__, "reason": str(exc)})
    # A failed threshold must still retain that group's authenticated raw identity,
    # ratio and input provenance, rather than disappearing from a successful pair.
    for role in ROLES:
        if role not in packets:
            try:
                packets[role] = guard.load_run(root, own, runs[role], (candidate, baseline))
            except Exception as exc:
                receipt["failures"].append({"stage": "raw:" + role, "run": runs.get(role), "type": type(exc).__name__, "reason": str(exc)})
    shapes = {}
    for role, packet in packets.items():
        try:
            expanded=guard.load_run(root,own,runs[role],(candidate,baseline,CONTROL_NAME))
            require(expanded['run_id']==packet['run_id'] and expanded['job_id']==packet['job_id'] and
                    expanded['plan']==packet['plan'] and
                    all(expanded['verdicts'][name]==packet['verdicts'][name] and
                        expanded['kernel_hashes'][name]==packet['kernel_hashes'][name]
                        for name in (candidate,baseline)), 'Control reread changed primary packet')
            packets[role]=packet=expanded
        except Exception as exc:
            receipt['failures'].append({'stage':'estimator-control:'+role,'type':type(exc).__name__,'reason':str(exc)})
        receipt["groups"][role] = {"run": packet["run_id"], "job": packet["job_id"], "seed": packet["seed"],
                                  "evidence": packet["evidence"], "gain_p05": "UNKNOWN_IF_GUARD_REJECTED"}
        try:
            receipt['groups'][role]['execution_binding'] = import_binding().verify_run(freeze, packet, guard, root)
        except Exception as exc:
            receipt['failures'].append({'stage': 'execution:' + role, 'type': type(exc).__name__, 'reason': str(exc)})
        try:
            receipt["groups"][role]["relative_normalized_ratio"] = packet["verdicts"][candidate]["ratio"] / packet["verdicts"][baseline]["ratio"]
            shapes[role] = shape_loader(root, guard, packet)
            receipt["groups"][role]["inputs"] = shapes[role]
        except Exception as exc:
            receipt["failures"].append({"stage": "inputs:" + role, "type": type(exc).__name__, "reason": str(exc)})
    receipt["group_count"] = len(packets)
    receipt["declared_groups"] = {r: {"run": runs.get(r), "frozen_seed": freeze["groups"][r]["seed"]} for r in ROLES}
    receipt["group_count_scope"] = "Authenticated observed groups, including rejected groups; acceptance requires all three"
    # Preserve known statistics and input comparisons even if the other pair fails.
    for label, confirmation in (("D+A", "A"), ("D+B", "B")):
        if label in receipt["pairs"]:
            for role, sample in zip(("D", confirmation), receipt["pairs"][label]["samples"]):
                if role in receipt["groups"]:
                    receipt["groups"][role].update(sample)
    receipt["input_comparisons"] = {}
    for left, right in (("D", "A"), ("D", "B"), ("A", "B")):
        if left in shapes and right in shapes:
            try:
                receipt["input_comparisons"][left + "+" + right] = compare_inputs(shapes[left], shapes[right])
            except Exception as exc:
                receipt["failures"].append({"stage": "diversity:" + left + "+" + right,
                                            "type": type(exc).__name__, "reason": str(exc)})
    try:
        result = validate_cohort(freeze, packets, shapes, receipt["pairs"])
        for role, stats in result["groups"].items():
            receipt["groups"][role].update(stats)
        receipt.update(input_comparisons=result["input_comparisons"], group_count=3, counting=result["counting"])
        if not receipt["failures"]:
            receipt.update(accepted=True, status="THREE_GROUP_CONFIRMED_RECEIPT_ONLY")
    except Exception as exc:
        receipt["failures"].append({"stage": "global", "type": type(exc).__name__, "reason": str(exc)})
    return receipt


def main(argv=None):
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--freeze", type=Path, required=True)
    parser.add_argument("--freeze-sha256", required=True)
    parser.add_argument("--discovery", type=int, required=True)
    parser.add_argument("--confirmation-a", type=int, required=True)
    parser.add_argument("--confirmation-b", type=int, required=True)
    parser.add_argument("--output", type=Path, required=True)
    args = parser.parse_args(argv)
    receipt = {"accepted": False, "status": "FREEZE_REJECTED", "failures": [], "adoption_performed": False}
    try:
        require(__debug__, "Optimized Python refused")
        guard = import_guard()
        freeze = read(args.freeze)
        verify_freeze(freeze, args.freeze_sha256, args.freeze, guard)
        runs = {"D": args.discovery, "A": args.confirmation_a, "B": args.confirmation_b}
        require(len(set(runs.values())) == 3, "Three distinct input run IDs required")
        for role in ROLES:
            if "run" in freeze["groups"][role]:
                require(runs[role] == freeze["groups"][role]["run"], "CLI run differs from frozen role: " + role)
        receipt = verify_three_groups(freeze, runs, guard)
        # Recheck after original-artifact reads so helper/source/freeze drift cannot
        # leave an accepted receipt bound only to an earlier filesystem state.
        verify_freeze(freeze, args.freeze_sha256, args.freeze, guard)
    except Exception as exc:
        receipt.update(accepted=False, status="FREEZE_REJECTED")
        receipt["failures"].append({"stage": "freeze", "type": type(exc).__name__, "reason": str(exc)})
    receipt.update(as_of_utc=datetime.now(timezone.utc).isoformat(), freeze=str(args.freeze),
                   expected_freeze_sha256=args.freeze_sha256, actual_freeze_sha256=digest(args.freeze) if args.freeze.exists() else "UNKNOWN",
                   verifier_sha256=digest(Path(__file__).resolve()))
    # Receipts are append-only by filename; accidental overwrite must not hide a failure.
    with args.output.open("x", encoding="utf-8") as output:
        output.write(json.dumps(receipt, ensure_ascii=False, indent=2) + "\n")
    print(json.dumps({"accepted": receipt["accepted"], "status": receipt["status"], "receipt": str(args.output), "receipt_sha256": digest(args.output)}))
    return 0 if receipt["accepted"] else 2


if __name__ == "__main__":
    sys.exit(main())
