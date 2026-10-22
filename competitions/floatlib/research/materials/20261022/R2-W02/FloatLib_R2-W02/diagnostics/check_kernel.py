#!/usr/bin/env python3
"""Read-only policy preflight. Does NOT execute gate.py or certify Lean proofs.

Usage: python3 check_kernel.py /path/to/fixed/competition /path/to/Kernel.lean
The regular expression and allowed attributes are read as data from the pinned
gate AST. No upstream executable code is imported or evaluated.
"""
import ast
import hashlib
import json
import re
import sys
from pathlib import Path


def main():
    repo, path = (Path(x).resolve() for x in sys.argv[1:3])
    gate_bytes = (repo / "gate.py").read_bytes()
    expected = "2d2e97dcbe7e4a131a5655c915e63ffc05c3c34c3f6977534bf4bfd337434ff8"
    actual = hashlib.sha256(gate_bytes).hexdigest()
    if actual != expected:
        raise SystemExit("STOP: gate.py does not match the inspected fixed source")
    manifest_path = Path(__file__).resolve().parents[1] / "sources/required_workspace_hashes.json"
    protected = json.loads(manifest_path.read_text())["files"]
    for relative, expected_hash in protected.items():
        protected_path = repo / relative
        if not protected_path.is_file() or hashlib.sha256(protected_path.read_bytes()).hexdigest() != expected_hash:
            raise SystemExit("STOP: protected workspace file differs: " + relative)
    tree = ast.parse(gate_bytes.decode())
    values = {}
    for node in tree.body:
        if not isinstance(node, ast.Assign):
            continue
        names = [t.id for t in node.targets if isinstance(t, ast.Name)]
        if "BANNED" in names:
            if not isinstance(node.value, ast.Call):
                raise SystemExit("Unexpected BANNED definition")
            values["BANNED"] = re.compile(ast.literal_eval(node.value.args[0]))
        for name in ("ATTRIBUTES", "OPTIONS", "_MAX_BYTES"):
            if name in names:
                values[name] = ast.literal_eval(node.value)
    data = path.read_bytes()
    text = data.decode("utf-8")
    errors = []
    if len(data) > values["_MAX_BYTES"]:
        errors.append("file exceeds fixed byte limit")
    for i, line in enumerate(text.splitlines(), 1):
        if re.search(r"\bimport\b", line) and line.strip() != "import ContractTensor":
            errors.append(f"disallowed import line {i}")
    match = values["BANNED"].search(text)
    if match:
        errors.append(f"fixed policy rejects token {match.group(0)!r}")
    if "set_option" in text:
        errors.append("this narrow preflight accepts no set_option directives")
    for group in re.findall(r"@\[([^\]]*)\]", text):
        for attr in group.split(","):
            name = attr.split()[-1] if attr.split() else ""
            if name not in values["ATTRIBUTES"]:
                errors.append(f"unlisted attribute {name!r}")
    result = {
        "status": "STATIC_PREFLIGHT_PASSED" if not errors else "STATIC_PREFLIGHT_FAILED",
        "gate_sha256": actual,
        "protected_workspace_files_checked": len(protected),
        "kernel_sha256": hashlib.sha256(data).hexdigest(),
        "kernel_bytes": len(data),
        "errors": errors,
        "bmm_spec_declared": bool(re.search(r"\btheorem\s+bmm_spec\b", text)),
        "elaboration": "NOT_CHECKED_BY_THIS_SCRIPT",
        "full_gate": "NOT_CHECKED_BY_THIS_SCRIPT",
        "scope": "lexical candidate preflight only; missing bmm_spec is expected for this codegen candidate",
    }
    print(json.dumps(result, indent=2))
    return bool(errors)


if __name__ == "__main__":
    sys.exit(main())
