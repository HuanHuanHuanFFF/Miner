"""Lightweight local artifact audit. No Lean, native code, CI, Git writes or network."""
from pathlib import Path
from datetime import datetime, timezone
import ast
import collections
import hashlib
import json
import re

HERE = Path(__file__).resolve().parent
ROOT = next(p for p in HERE.parents if (p/"AGENTS.md").is_file())


def sha(path):
    return hashlib.sha256(path.read_bytes()).hexdigest()


def main():
    checked = datetime.now(timezone.utc).isoformat()
    failures = []
    old_inputs = {
        "predecessor-HANDOFF.md":"020a629501aa4c649635e0d99321b0b38a9c4fc79196bd6b1d876f6ea703e64c",
        "predecessor-status.json":"95f3e2ee11c7471d2d690f5a061a7794c232d3b8f840d6d6b2ec1e9a5051ba37",
    }
    for name, expected in old_inputs.items():
        if sha(HERE/name) != expected:
            failures.append("predecessorbytes:"+name)
    private = ROOT/"competitions/torchlean/candidates/r27-5h-20261029T194443Z/competition-state/source-private/submission23-Kernel.lean"
    if sha(private) != "1010c0744f0506974c64601e8ce7335bea56d0cb21b655543d390794df0665fe":
        failures.append("public23sourcehash")
    python_files = list(HERE.glob("*.py"))
    for path in python_files:
        ast.parse(path.read_text(encoding="utf-8-sig"), filename=path.name)
    lean_files = [*HERE.glob("*.lean"), *HERE.glob("*.lean.inc")]
    roots = {}
    for path in lean_files:
        text = path.read_text(encoding="utf-8-sig")
        plain = re.sub(r"/-.*?-/", "", text, flags=re.S)
        plain = re.sub(r"--[^\n]*", "", plain)
        banned = re.findall(r"\b(?:sorry|admit|axiom|unsafe|native_decide)\b", plain)
        if banned:
            failures.append(path.name+":"+str(banned))
        imports = re.findall(r"(?m)^import\s+(.+)$", plain)
        if any(i != "ContractExact" for i in imports):
            failures.append(path.name+":import")
        roots[path.name] = re.findall(r"(?m)^(?:private )?theorem\s+(\w+)", plain)
    for path in HERE.glob("*.json"):
        json.loads(path.read_text(encoding="utf-8-sig"))
    model = json.loads((HERE/"aligned60-model.json").read_bytes())
    if model["script_sha256"] != sha(HERE/"check_aligned60.py"):
        failures.append("aligned60modelscript")
    if model["runtime_draft_sha256"] != sha(HERE/"Aligned60Carrier.lean.inc"):
        failures.append("aligned60runtimedraft")
    witness = json.loads((HERE/"prepare-scope-counterexample.json").read_bytes())
    if not witness["metadata"]["exact_Yah_model"]:
        failures.append("nonexactYah")
    if witness["script_sha256"] != sha(HERE/"check_prepare_scope.py"):
        failures.append("preparecounterexamplescript")
    if witness["actual_YaV_row_guard"]["wide_cache_actually_built"]:
        failures.append("retractedpreparationclaimresurrected")
    census = json.loads((HERE/"oldseen-prepare-census.json").read_bytes())
    if census["script_sha256"] != sha(HERE/"census_oldseen_prepare.py"):
        failures.append("censusscript")
    if len(census["cells"]) != 36 or not all(c["checksum_match"] for c in census["cells"]):
        failures.append("oldseenchecksums")
    groups = collections.Counter()
    bad = []
    total_dense_macs = 0
    for c in census["cells"]:
        for s in c["stages"]:
            total_dense_macs += s["shape"][0]*s["shape"][1]*s["shape"][2]
            if not s["global_QPS"]:
                continue
            for r in s["rows"]:
                if not r.get("prepared", False):
                    continue
                bucket = "le7" if r["span"] <= 7 else "8to15" if r["span"] <= 15 else "gt15"
                groups[(r["mode"],bucket,"rows")] += 1
                groups[(r["mode"],bucket,"slots")] += r["prepared_slots"]
                if r["aligned60_bound_fail_terms"]:
                    bad.append({"root":c["root"],"cell":c["cell"],"stage":s["stage"],"span":r["span"],"terms":r["aligned60_bound_fail_terms"]})
                    if r["span"] <= 15:
                        failures.append("aligned60counterexamplewithinclaimedrowdomain")
    owned = [{"file":str(p.relative_to(HERE)),"bytes":p.stat().st_size,"sha256":sha(p)} for p in sorted(HERE.rglob("*")) if p.is_file() and p.name != "SOURCE-AND-VALIDATION-RECEIPT.json"]
    result = {
        "state":"LOCAL_ARTIFACT_AUDIT_PASS" if not failures else "LOCAL_ARTIFACT_AUDIT_FAIL",
        "checked_at_utc":checked,
        "failures":failures,
        "python_AST_files":len(python_files),
        "new_Lean_roots_NOT_COMPILED":roots,
        "predecessor_copies_byte_hash_match":not any(s.startswith("predecessorbytes:") for s in failures),
        "oldseen_census":{"cells":36,"checksums_match":36,"counts":census["total_counts"],"all_dense_linear_MACs":total_dense_macs,"groups":{"/".join(k):v for k,v in groups.items()},"actual_prepared_transport60_range_failures":bad,"model_includes_existing_YaV_perrow_guard":True},
        "retracted_claims":["Earlierunusedwide/bigNatactualpreparationclaimmissedexistingYaVline869guard.","768rows/2wide/73noeligibleand14rangefailsareINVALIDactualpreparecounts;currentcorrectedcounts682/0/0.","UnusedCacheElisionProofisredundantinterfaceonly,notnewruntimeworkelimination."],
        "source_budget":{"parent_prefreeze_public23_alias_bytes":248185,"finiteprefix_fullhelper_bytes":(HERE/"FinitePrefixTransportContractOnly.lean").stat().st_size,"fullcodec_plus_both_controls_bytes":(HERE/"Aligned60Carrier.lean.inc").stat().st_size,"naive_sum":248185+(HERE/"FinitePrefixTransportContractOnly.lean").stat().st_size+(HERE/"Aligned60Carrier.lean.inc").stat().st_size,"cap":256000,"qualification":"Notanactualassembledcandidate. Productioncanomitcontrols/duplicatewrappers; originalQPcodec/fullcorrectproofstillmissing. Do notassumefit."},
        "root_check_observed":{"command":"python scripts/project.py check","observed_checked_by_utc":"2026-10-30T00:32:04Z","exit_code":0,"status":"PASS","tracks":["deflate","floatlib","torchlean"],"root_links":98,"manual_workflows":11,"scope":"Localmetadata/link/hash/syntaxcheck;notLeanorCI"},
        "resources":{"recovery_first_clock_utc":"2026-10-30T00:08:40Z","deadline_utc":"2026-10-30T00:44:43Z","new_CI_runs":0,"local_Lean_runs":0,"local_native_runs":0,"new_agents":0,"direct_messages":0,"actual_tokens":"UNKNOWN","cached_input_tokens":"UNKNOWN","CPU":"UNKNOWN","census_formula_wall_seconds":census["elapsed_seconds"]},
        "files":owned
    }
    (HERE/"SOURCE-AND-VALIDATION-RECEIPT.json").write_text(json.dumps(result,indent=2)+"\n",encoding="utf-8")
    print(json.dumps({"state":result["state"],"failures":failures,"files":len(owned),"python_AST_files":len(python_files),"census_cells":36,"source_budget":result["source_budget"]}))
    return bool(failures)


if __name__=="__main__":
    raise SystemExit(main())

