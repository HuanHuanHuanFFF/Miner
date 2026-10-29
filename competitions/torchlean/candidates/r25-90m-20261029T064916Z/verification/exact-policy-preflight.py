"""Run the pinned upstream UTF-8 intake and source-policy functions without Lean."""
from __future__ import annotations

import ast
import hashlib
import json
import re
from pathlib import Path

HERE = Path(__file__).resolve().parent
ROUND = HERE.parent
REPO = ROUND.parents[3]
VARIANT_ROOT = ROUND / "development" / "contract-port"
POLICY_SOURCE = VARIANT_ROOT / "policy-source"
EXPECTED_BLOBS = {
    "sandbox.py": "13c4f7b71e678a27d024613e5198e0d75667de4e",
    "duplicates.py": "3e8eb21d1a50cce44090e29a816e3b55c0ad3fd9",
}
PINNED_COMMIT = "accb82b6e2adeda1b41a57a260d68fb3879c427e"


def sha256(data: bytes) -> str:
    return hashlib.sha256(data).hexdigest()


def git_blob_sha(data: bytes) -> str:
    header = b"blob " + str(len(data)).encode("ascii") + b"\0"
    return hashlib.sha1(header + data).hexdigest()


class Utf8Path:
    """Path adapter matching the upstream Linux UTF-8 file reads on this Windows host."""

    def __init__(self, path: Path):
        self.path = path

    def is_file(self):
        return self.path.is_file()

    def stat(self):
        return self.path.stat()

    def read_bytes(self):
        return self.path.read_bytes()

    def read_text(self):
        return self.path.read_bytes().decode("utf-8")

    def __str__(self):
        return str(self.path)


def names_in_target(target) -> set[str]:
    if isinstance(target, ast.Name):
        return {target.id}
    if isinstance(target, (ast.Tuple, ast.List)):
        return set().union(*(names_in_target(item) for item in target.elts))
    return set()


def load_official_policy():
    source_bytes = {}
    for name, expected in EXPECTED_BLOBS.items():
        data = (POLICY_SOURCE / name).read_bytes()
        actual = git_blob_sha(data)
        if actual != expected:
            raise ValueError(f"pinned source mismatch: {name} blob {actual}, expected {expected}")
        source_bytes[name] = data

    duplicate_ns = {"__name__": "pinned_duplicates"}
    exec(compile(source_bytes["duplicates.py"].decode("utf-8"), "pinned-duplicates.py", "exec"), duplicate_ns)

    tree = ast.parse(source_bytes["sandbox.py"].decode("utf-8"), filename="pinned-sandbox.py")
    wanted_constants = {"_MAX_BYTES", "OPTIONS", "ATTRIBUTES", "BANNED", "GLOBAL"}
    wanted_functions = {"intake", "policy", "options", "global_declarations"}
    selected = []
    found_constants: set[str] = set()
    found_functions: set[str] = set()
    for node in tree.body:
        if isinstance(node, ast.Assign):
            names = set().union(*(names_in_target(t) for t in node.targets))
            if names & wanted_constants:
                selected.append(node)
                found_constants |= names & wanted_constants
        elif isinstance(node, (ast.FunctionDef, ast.AsyncFunctionDef)) and node.name in wanted_functions:
            selected.append(node)
            found_functions.add(node.name)
    if found_constants != wanted_constants or found_functions != wanted_functions:
        raise ValueError(
            "pinned policy AST incomplete: "
            f"constants={sorted(found_constants)}, functions={sorted(found_functions)}"
        )

    ns = {
        "__builtins__": __builtins__,
        "Path": Path,
        "Verdict": object,
        "re": re,
        "normalized": duplicate_ns["normalized"],
    }
    module = ast.fix_missing_locations(ast.Module(body=selected, type_ignores=[]))
    exec(compile(module, "pinned-policy-functions.py", "exec"), ns)
    return ns, {
        name: {"git_blob_sha": EXPECTED_BLOBS[name], "bytes": len(source_bytes[name]), "sha256": sha256(source_bytes[name])}
        for name in EXPECTED_BLOBS
    }


def repo_path(value: str) -> Path:
    candidate = (REPO / value.replace("\\", "/")).resolve()
    candidate.relative_to(REPO)
    return candidate


def inspect_one(ns, row: dict) -> dict:
    path = repo_path(row["path"])
    if not path.is_file():
        return {**row, "actual_sha256": None, "actual_bytes": None, "identity": "MISSING", "intake": None, "policy": None}
    data = path.read_bytes()
    actual_sha = sha256(data)
    actual_bytes = len(data)
    identity_ok = actual_sha == row["expected_sha256"] and actual_bytes == row["expected_bytes"]
    result = {
        **row,
        "actual_sha256": actual_sha,
        "actual_bytes": actual_bytes,
        "identity": "MATCH" if identity_ok else "MISMATCH",
        "intake": None,
        "policy": None,
        "policy_preflight_only": True,
    }
    if not identity_ok:
        return result
    source = Utf8Path(path)
    result["intake"] = ns["intake"](source, None)
    if result["intake"] is None:
        result["policy"] = ns["policy"](source, None)
    result["passed_intake_policy_only"] = result["intake"] is None and result["policy"] is None
    return result


def main() -> int:
    plan = json.loads((ROUND / "ci-plan.json").read_text(encoding="utf-8"))
    frozen_by_name = {row["name"]: row for row in plan["candidates"]}
    pairs = [
        ("adaptive", "decode-cache-adaptive-policy1-source-receipt.json"),
        ("patch-norm", "patch-norm-cache-policy1-source-receipt.json"),
    ]
    entries = []
    for frozen_name, receipt_name in pairs:
        frozen = frozen_by_name[frozen_name]
        receipt_path = VARIANT_ROOT / receipt_name
        receipt = json.loads(receipt_path.read_text(encoding="utf-8"))
        policy1 = receipt["candidate"]
        entries.extend(
            [
                {
                    "pair": frozen_name,
                    "variant": "frozen",
                    "path": frozen["path"],
                    "expected_sha256": frozen["sha256"],
                    "expected_bytes": frozen["bytes"],
                    "expected_policy": "REJECT_GLOBAL_INSTANCE",
                },
                {
                    "pair": frozen_name,
                    "variant": "policy1",
                    "path": policy1["path"],
                    "expected_sha256": policy1["sha256"],
                    "expected_bytes": policy1["bytes"],
                    "expected_policy": "PASS_INTAKE_POLICY",
                    "source_receipt": receipt_name,
                },
            ]
        )

    ns, policy_sources = load_official_policy()
    results = [inspect_one(ns, row) for row in entries]
    for row in results:
        rejection = row.get("policy") or ""
        row["observed_policy"] = "REJECT_GLOBAL_INSTANCE" if "instance without `local`" in rejection else (
            "PASS_INTAKE_POLICY" if row.get("passed_intake_policy_only") else "OTHER_REJECTION"
        )
        row["expectation_met"] = (
            row["observed_policy"] == row["expected_policy"] and row.get("identity") == "MATCH"
        )

    local_maintenance = REPO / ".local-maintenance" / "torchlean-original" / "validator" / "sandbox.py"
    local_maintenance_record = None
    if local_maintenance.is_file():
        data = local_maintenance.read_bytes()
        local_maintenance_record = {
            "path": str(local_maintenance.relative_to(REPO)).replace("\\", "/"),
            "git_blob_sha": git_blob_sha(data),
            "matches_pinned_official": git_blob_sha(data) == EXPECTED_BLOBS["sandbox.py"],
            "used_for_policy_execution": False,
        }

    succeeded = all(row["expectation_met"] for row in results)
    output = {
        "round": "R25",
        "official_commit": PINNED_COMMIT,
        "source": "R25 development/contract-port/policy-source; exact official Git blobs",
        "policy_source_integrity": policy_sources,
        "local_maintenance_copy": local_maintenance_record,
        "results": results,
        "statement_kernel_axioms": "NOT_RUN",
        "native_measurement": "NOT_RUN",
        "status": "PASS_POLICY_DIFFERENTIAL" if succeeded else "FAIL_OR_IDENTITY_MISMATCH",
        "claim_boundary": "Pure pinned intake/policy preflight only; no Lean elaboration, proof, kernel replay, axiom audit or benchmark was run.",
    }
    target = HERE / "exact-policy-preflight.json"
    target.write_text(json.dumps(output, indent=2, ensure_ascii=False) + "\n", encoding="utf-8")
    print(json.dumps(output, indent=2, ensure_ascii=False))
    return 0 if succeeded else 1


if __name__ == "__main__":
    raise SystemExit(main())
