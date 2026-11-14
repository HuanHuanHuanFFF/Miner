"""Invoke pinned upstream's pure intake/policy functions without Lean or a build.

Only the original policy declarations are compiled from their saved AST; no gate
implementation is edited, monkeypatched, or substituted in the actual CI gate.
"""
from pathlib import Path
import ast
import argparse
import hashlib
import json
import re
import types

HERE = Path(__file__).resolve().parent
SOURCE = HERE / "policy-source"
EXPECTED = {"sandbox.py": "13c4f7b71e678a27d024613e5198e0d75667de4e",
            "duplicates.py": "3e8eb21d1a50cce44090e29a816e3b55c0ad3fd9"}


def blob_sha(data: bytes) -> str:
    return hashlib.sha1(b"blob " + str(len(data)).encode() + b"\0" + data).hexdigest()


def main() -> None:
    parser = argparse.ArgumentParser()
    parser.add_argument("--plan", type=Path)
    args = parser.parse_args()
    sources = {}
    for name, expected in EXPECTED.items():
        raw = (SOURCE / name).read_bytes()
        assert blob_sha(raw) == expected, (name, blob_sha(raw), expected)
        sources[name] = {"git_blob": expected, "bytes": len(raw), "sha256": hashlib.sha256(raw).hexdigest()}
    duplicate_ns = {}
    exec(compile((SOURCE / "duplicates.py").read_text(encoding="utf-8"), "pinned-duplicates.py", "exec"), duplicate_ns)
    tree = ast.parse((SOURCE / "sandbox.py").read_text(encoding="utf-8"))
    names = {"_MAX_BYTES", "OPTIONS", "ATTRIBUTES", "BANNED", "GLOBAL"}
    funcs = {"intake", "policy", "global_declarations", "options"}
    selected = [node for node in tree.body if
                (isinstance(node, ast.Assign) and any(isinstance(t, ast.Name) and t.id in names for t in node.targets))
                or (isinstance(node, ast.FunctionDef) and node.name in funcs)]
    ns = {"Path": Path, "Verdict": object, "re": re, "normalized": duplicate_ns["normalized"]}
    exec(compile(ast.Module(body=selected, type_ignores=[]), "pinned-policy-functions.py", "exec"), ns)
    rows = []
    kernels = [(p.parent.name, p, None) for p in sorted(HERE.glob("*/Kernel.lean"))]
    if args.plan:
        plan = json.loads(args.plan.read_bytes())
        kernels += [("planned:" + e["name"], HERE.parents[5] / e["path"], e["sha256"]) for e in plan["candidates"]]
    for label, kernel, declared_sha in kernels:
        raw = kernel.read_bytes()
        intake = ns["intake"](kernel, None)
        policy = ns["policy"](kernel, None) if intake is None else None
        actual_sha = hashlib.sha256(raw).hexdigest()
        rows.append({"variant": label, "sha256": actual_sha,
                     "declared_sha_match": actual_sha == declared_sha if declared_sha else None,
                     "bytes": len(raw), "intake": intake, "policy": policy,
                     "passed_intake_policy_only": intake is None and policy is None})
    result = {"official_commit": "accb82b6e2adeda1b41a57a260d68fb3879c427e",
              "source_blobs_match": True, "sources": sources, "results": rows,
              "statement_kernel_axioms": "NOT_RUN", "native": "NOT_RUN"}
    output = "policy-check-planned.json" if args.plan else "policy-check.json"
    (HERE / output).write_text(json.dumps(result, indent=2) + "\n", encoding="utf-8")
    print(json.dumps(result, indent=2))


if __name__ == "__main__":
    main()
