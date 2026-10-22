#!/usr/bin/env python3
"""Read-only provenance and lexical checks. This does not run or certify Lean."""
import ast
import hashlib
import json
import re
import sys
from pathlib import Path


def sha(data):
    return hashlib.sha256(data).hexdigest()


def main():
    package = Path(__file__).resolve().parents[1]
    provenance = json.loads((package / "sources/provenance.json").read_text())
    rules = json.loads((package / "sources/policy_snapshot.json").read_text())
    parent = (package / "parent/Kernel.lean").read_bytes()
    candidate = (package / "Kernel.lean").read_bytes()
    text = candidate.decode("utf-8")
    errors = []
    if len(parent) != 58079 or sha(parent) != "86312a3759286cb207f946af9db95546777fdb16f1bd147f7892c0f9e1d79217":
        errors.append("parent differs from the user-specified public bytes")
    boundary = provenance["preserved_prefix_bytes"]
    if candidate[:boundary] != parent[:boundary]:
        errors.append("protected parent prefix changed")
    pieces = [(package / name).read_bytes() for name in provenance["source_fragments"]]
    rebuilt = parent[:boundary] + b"\n\n".join(pieces) + b"\n\nend Submission\n"
    if rebuilt != candidate:
        errors.append("assembled file differs from its four source fragments")
    if sha(candidate) != provenance["candidate_sha256"]:
        errors.append("candidate differs from recorded SHA256")
    if len(candidate) > rules["_MAX_BYTES"]:
        errors.append("candidate exceeds the fixed byte limit")
    imports = [(i, line) for i, line in enumerate(text.splitlines(), 1) if re.search(r"\bimport\b", line)]
    if imports != [(1, "import ContractTensor")]:
        errors.append("unexpected import text, including comments")
    banned = list(re.finditer(rules["BANNED"], text))
    for match in banned:
        errors.append(f"banned text {match.group()!r} at line {text.count(chr(10), 0, match.start()) + 1}")
    for group in re.findall(r"@\[([^\]]*)\]", text):
        for attr in group.split(","):
            name = attr.split()[-1] if attr.split() else ""
            if name not in rules["ATTRIBUTES"]:
                errors.append("unlisted attribute " + name)
    # This candidate adds no option directives; the inherited parent has none.
    if re.search(r"\bset_option\b", text):
        errors.append("unexpected option directive")
    protected_files = 0
    if len(sys.argv) == 2:
        official = Path(sys.argv[1]).resolve()
        hashes = json.loads((package / "sources/required_workspace_hashes.json").read_text())["files"]
        for name, expected in hashes.items():
            path = official / name
            if not path.is_file() or sha(path.read_bytes()) != expected:
                errors.append("fixed workspace input differs: " + name)
            protected_files += 1
        gate = (official / "gate.py").read_bytes()
        for node in ast.parse(gate.decode()).body:
            if isinstance(node, ast.Assign) and any(isinstance(t, ast.Name) and t.id == "BANNED" for t in node.targets):
                if ast.literal_eval(node.value.args[0]) != rules["BANNED"]:
                    errors.append("policy snapshot does not match the fixed gate")
        if sha(gate) != rules["gate_sha256"]:
            errors.append("gate hash differs")
    elif len(sys.argv) != 1:
        raise SystemExit("Usage: python3 diagnostics/verify_source.py [fixed-official-repository]")
    result = {
        "status": "PASSED_SOURCE_AND_LEXICAL_PREFLIGHT" if not errors else "FAILED",
        "parent_bytes": len(parent), "parent_sha256": sha(parent),
        "preserved_prefix_bytes": boundary,
        "preserved_prefix_sha256": sha(parent[:boundary]),
        "preserved_prefix_identical": candidate[:boundary] == parent[:boundary],
        "candidate_bytes": len(candidate), "candidate_lines": len(text.splitlines()),
        "candidate_sha256": sha(candidate), "candidate_reconstructed_exactly": rebuilt == candidate,
        "fixed_workspace_files_checked": protected_files,
        "banned_matches_including_comments": len(banned), "errors": errors,
        "lean_elaboration": "NOT_RUN", "kernel_check": "NOT_RUN", "full_gate": "NOT_RUN",
        "scope": "Byte preservation and text policy only; not evidence of proof acceptance or runtime behavior.",
    }
    print(json.dumps(result, indent=2))
    return bool(errors)


if __name__ == "__main__":
    sys.exit(main())
