"""Run the exact upstream intake/policy functions without importing its runner.

This is a static preflight only. It cannot establish Lean acceptance or speed.
"""
from __future__ import annotations

import argparse
import ast
from datetime import datetime, timezone
import hashlib
import importlib.util
import json
from pathlib import Path
import re
from types import SimpleNamespace

ROOT = Path(__file__).resolve().parents[4]


def digest(data: bytes) -> str:
    return hashlib.sha256(data).hexdigest()


def extract_policy(source: bytes, expected_sha256: str):
    assert digest(source) == expected_sha256, "Upstream gate bytes differ from the recorded response"
    module = ast.parse(source.decode("utf-8"))
    constants = {"_MAX_BYTES", "OPTIONS", "ATTRIBUTES", "BANNED"}
    functions = {"intake", "options", "policy"}
    selected = []
    found = set()
    for node in module.body:
        if isinstance(node, ast.Assign):
            names = {target.id for target in node.targets if isinstance(target, ast.Name)}
            if names & constants:
                assert names <= constants
                selected.append(node)
                found |= names
        elif isinstance(node, ast.FunctionDef) and node.name in functions:
            selected.append(node)
            found.add(node.name)
    assert found == constants | functions, found
    # Defer annotations so the unrelated runner's Verdict class is not imported.
    future = ast.ImportFrom(module="__future__", names=[ast.alias(name="annotations")], level=0)
    extracted = ast.fix_missing_locations(ast.Module(body=[future] + selected, type_ignores=[]))
    namespace = {"Path": Path, "re": re,
                 "SLOTS": {"full": SimpleNamespace(contract="ContractTensor")}}
    exec(compile(extracted, "<exact-upstream-policy-functions>", "exec"), namespace)
    return namespace


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--plan", required=True, type=Path)
    parser.add_argument("--gate-source", required=True, type=Path)
    parser.add_argument("--gate-receipt", required=True, type=Path)
    parser.add_argument("--output", required=True, type=Path)
    args = parser.parse_args()
    plan_bytes = args.plan.read_bytes()
    plan = json.loads(plan_bytes)
    receipt = json.loads(args.gate_receipt.read_bytes())
    assert receipt["status"] == 200
    assert f'/{plan["official_commit"]}/gate.py' in receipt["url"]
    source = args.gate_source.read_bytes()
    assert len(source) == receipt["bytes"]
    policy = extract_policy(source, receipt["sha256"])
    validator_path = ROOT / "competitions/floatlib/candidates/f01-mul-log2-proof1/ci.py"
    spec = importlib.util.spec_from_file_location("static_plan_validator", validator_path)
    validator = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(validator)
    entries = validator.validate_suite_plan(plan, plan["seed"])
    candidates = []
    for row in entries:
        directory = ROOT / "competitions/floatlib/candidates" / row["candidate"]
        path = directory / "Kernel.lean"
        data = path.read_bytes()
        assert digest(data) == row["sha256"], row["candidate"]
        manifest = json.loads((directory / "manifest.json").read_bytes())
        assert manifest["candidate_sha256"] == row["sha256"], row["candidate"]
        assert manifest["candidate_bytes"] == len(data), row["candidate"]
        intake = policy["intake"](path, SimpleNamespace(slot="full"))
        reason = intake or policy["policy"](path, SimpleNamespace(slot="full"))
        candidates.append({"candidate": row["candidate"], "sha256": digest(data),
                           "bytes": len(data), "mode": row.get("validation_mode", "full-gate"),
                           "static_policy": "PASS" if reason is None else "FAIL", "reason": reason,
                           "lean_and_full_gate": "NOT_RUN_BY_THIS_PREFLIGHT"})
    report = {"checked_at_utc": datetime.now(timezone.utc).isoformat(),
              "status": "PASS" if all(r["static_policy"] == "PASS" for r in candidates) else "FAIL",
              "scope": "Exact unmodified current upstream intake/options/policy functions only",
              "official_commit": plan["official_commit"], "upstream_gate": receipt,
              "plan_sha256": digest(plan_bytes), "seed": plan["seed"], "candidates": candidates,
              "publication_authorization": "NOT_ESTABLISHED_BY_THIS_PREFLIGHT"}
    args.output.write_text(json.dumps(report, ensure_ascii=False, indent=2) + "\n", encoding="utf-8")
    print(json.dumps({"status": report["status"], "candidates": len(candidates),
                      "output": str(args.output)}, ensure_ascii=False))
    if report["status"] != "PASS":
        raise SystemExit(1)


if __name__ == "__main__":
    main()
