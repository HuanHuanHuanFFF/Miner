"""Trim frozen uniform-H candidates to their Rust and Lean dependency core.

Default: generate only r4-parse-h8d32-core. Other parent recipes are available
through explicit --only for later authorized use. No Rust/Lean/CI execution.
All reachable function bodies, used constants and retained proof blocks are
copied verbatim. The official obligation, axiom policy and time limits are not
part of this generator and are not changed.
"""
from __future__ import annotations

import argparse
import hashlib
import json
import re
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
PROOF_SHA = "f14e3c7b8a5c89d84dcffdb5ffc43e4963a043538c42dd39e228cd351145ffaf"
RECIPES = {
    "r4-parse-h8d32-core": ("r4-parse-plan-h8-deep32", "a7115baa44afa81dc761cb7435872db264e6dea6a3013acec3fb9d768e81f83c"),
    "r4-parse-h4d32-wide-core": ("r4-parse-plan-h4-deep32-wide", "3787e8f8f5fc9fa9674e21462b0600c9f3fdc86c175f40d673f0c3c3cf25a6e3"),
    "r4-parse-h4d32-noslot-core": ("r4-parse-plan-h4-deep32-noslot", "3a6aa5f4514a02526fbe1043b29e4e75aeea2e32eebf35a0984328c516f584d3"),
}


def sha(data: bytes) -> str:
    return hashlib.sha256(data).hexdigest()


def mask_noncode(source: str) -> str:
    # Preserve offsets and line endings for byte-exact declaration copying.
    pattern = r'//[^\n]*|/\*.*?\*/|"(?:\\.|[^"\\])*"'
    return re.sub(pattern, lambda m: "".join("\n" if c == "\n" else " " for c in m[0]), source, flags=re.S)


def rust_declarations(source: str) -> tuple[dict, dict]:
    plain = mask_noncode(source)
    functions = {}
    for match in re.finditer(r"(?m)^(?:#\[[^\n]*\]\s*\n)*pub fn (\w+)\b[^{}]*\{", plain):
        pos, depth = match.end(), 1
        while depth:
            assert pos < len(plain), match[1]
            depth += (plain[pos] == "{") - (plain[pos] == "}")
            pos += 1
        functions[match[1]] = {"start": match.start(), "end": pos,
            "text": source[match.start():pos], "body": plain[match.end():pos - 1]}
    assert len(functions) == len(re.findall(r"\bfn\s+\w+\s*[<(]", plain)), "unsupported function declaration"
    assert not re.search(r"\bfn\s*\(", plain), "function-pointer audit required"
    constants = {}
    for match in re.finditer(r"(?m)^pub const (\w+)\s*:", plain):
        eq = plain.index("=", match.end())
        end = plain.index(";", eq) + 1
        constants[match[1]] = {"start": match.start(), "end": end,
            "text": source[match.start():end], "body": plain[eq + 1:end - 1]}
    return functions, constants


def reachable(functions: dict) -> set[str]:
    pending, active = ["parse"], set()
    while pending:
        name = pending.pop()
        if name in active:
            continue
        active.add(name)
        calls = set(re.findall(r"\b(\w+)\s*(?=\(|::<)", functions[name]["body"]))
        pending.extend((calls & functions.keys()) - active)
    return active


def trim_proof(proof: str) -> tuple[str, dict]:
    header = proof[:proof.index("namespace EA\n")]
    shared_start = proof.index("\nset_option hygiene false in\nlocal notation \"T9!\"", proof.index("\nend EA")) + 1
    shared_end = proof.index("namespace ED\n", shared_start)
    shared = proof[shared_start:shared_end]
    eh_start = proof.index("namespace EH\n")
    eh_end = proof.index("\nend EH", eh_start) + len("\nend EH")
    eh = proof[eh_start:eh_end]
    entry_start = proof.rindex("theorem parse_spec (input : Slice Std.U8)")
    entry_end = proof.index("\nend Submission", entry_start)
    entry = proof[entry_start:entry_end]
    assert "exact EH.parse_mode_spec input out 0#usize hlen" in entry
    used_macros = set(re.findall(r"\bT\d+!", eh))
    eh_macros = set(re.findall(r'local notation "(T\d+!)"', eh))
    shared_macros = set(re.findall(r'local notation "(T\d+!)"', shared))
    assert used_macros - eh_macros == shared_macros == {"T9!", "T10!"}
    assert not re.search(r"\b(?:EA|ED)\.|\b(?:route_spec|parse_c[012])\b", eh)
    result = header + shared + eh + "\n\n" + entry + "\nend Submission\n"
    assert not re.search(r"\b(?:sorry|admit|axiom)\b", result), "untrusted proof escape"
    blocks = {}
    for label, text in (("submission_header", header), ("shared_T9_T10", shared), ("EH_namespace", eh), ("parse_spec", entry)):
        at = proof.index(text)
        blocks[label] = {"original_line_start": proof[:at].count("\n") + 1,
            "original_line_end": proof[:at + len(text)].count("\n") + 1,
            "sha256": sha(text.encode()), "bytes": len(text.encode())}
    return result, {"retained_blocks": blocks, "shared_macros": sorted(shared_macros),
        "slot_references": sorted(set(re.findall(r"\bslot\.(\w+)", eh + entry)))}


def generate(parent_name: str, source_sha: str) -> tuple[dict[str, bytes], dict]:
    parent = ROOT / "candidates" / parent_name
    source_bytes, proof_bytes = (parent / "parse.rs").read_bytes(), (parent / "Parse.lean").read_bytes()
    assert sha(source_bytes) == source_sha, "parent source drift"
    assert sha(proof_bytes) == PROOF_SHA, "parent proof drift"
    source, proof = source_bytes.decode(), proof_bytes.decode()
    assert "\r\n" not in source and "\r\n" not in proof, "unexpected parent newline change"
    functions, constants = rust_declarations(source)
    active = reachable(functions)
    assert len(active) == 148 and all(n == "parse" or n.startswith("h_") for n in active)
    assert functions["parse"]["body"].strip() == "h_parse_mode(input, out, 0)"
    lean, proof_audit = trim_proof(proof)
    proof_owners = {}
    proof_constants = set()
    for ref in proof_audit["slot_references"]:
        if ref in constants:
            proof_constants.add(ref)
        else:
            owners = sorted((n for n in functions if ref == n or ref.startswith(n + "_loop")), key=len, reverse=True)
            assert owners and owners[0] in active, f"uncovered extracted reference: {ref}"
            proof_owners[ref] = owners[0]
    assert set(proof_owners.values()) == active, "proof does not cover every retained Rust function"
    pending_constants = set(proof_constants)
    for name in active:
        pending_constants |= set(re.findall(r"\b\w+\b", functions[name]["text"])) & constants.keys()
    retained_constants = set()
    while pending_constants:
        name = pending_constants.pop()
        if name in retained_constants:
            continue
        retained_constants.add(name)
        pending_constants |= (set(re.findall(r"\b\w+\b", constants[name]["body"])) & constants.keys()) - retained_constants
    assert all(n.startswith("H_") for n in retained_constants), "unexpected external constant dependency"
    declarations = [functions[n] for n in active] + [constants[n] for n in retained_constants]
    declarations.sort(key=lambda d: d["start"])
    rust = "//! H-only dependency core of public submission 402's uniform H derivative.\n" \
           "//! Generated by make-round4-hcore.py; reachable functions and constants are copied verbatim.\n\n" + \
           "\n\n".join(d["text"] for d in declarations) + "\n"
    new_functions, new_constants = rust_declarations(rust)
    assert reachable(new_functions) == active == new_functions.keys()
    assert retained_constants == new_constants.keys()
    for name in active:
        assert new_functions[name]["text"] == functions[name]["text"], name
    for name in retained_constants:
        assert new_constants[name]["text"] == constants[name]["text"], name
    assert not re.search(r"\b(?:route|parse_c[012]|a_p_for|a_\w+|d_\w+)\s*(?=\(|::<)", mask_noncode(rust))
    assert not re.search(r"\b(?:A_\w+|D_\w+)\b", mask_noncode(rust))
    assert not re.search(r"\b(?:unsafe|extern|mod)\b", mask_noncode(rust))
    files = {"parse.rs": rust.encode(), "Parse.lean": lean.encode()}
    assert all(len(data) <= 524288 for data in files.values())
    audit = {"parent": {"candidate": parent_name, "source_sha256": source_sha, "proof_sha256": PROOF_SHA},
        "retained_functions": sorted(active), "retained_constants": sorted(retained_constants),
        "removed_functions": sorted(functions.keys() - active),
        "removed_constants": sorted(constants.keys() - retained_constants),
        "function_body_preservation": "VERIFIED exact declaration text, including adjacent attributes, for all 148 retained functions",
        "constant_preservation": "VERIFIED exact declaration text for the transitive retained constants",
        "proof": {**proof_audit, "extracted_reference_owners": proof_owners},
        "gate_interface": "Original Submission.parse_spec statement and direct EH.parse_mode_spec body retained verbatim. The official LZ77.Obligation wrapper, axiom whitelist and 900-second limit remain external and unchanged.",
        "scope": "Static dependency audit only. Fresh extraction, Lean acceptance, axioms, round trip, output equivalence and runtime remain UNKNOWN."}
    return files, audit


def main() -> None:
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument("--check", action="store_true")
    ap.add_argument("--only", action="append", choices=sorted(RECIPES), default=[])
    args = ap.parse_args()
    for name in args.only or ["r4-parse-h8d32-core"]:
        parent, source_sha = RECIPES[name]
        files, audit = generate(parent, source_sha)
        manifest = {"candidate": name, "base_submission_id": "402", "parent": audit["parent"],
            "hashes": {n: sha(data) for n, data in files.items()},
            "bytes": {n: len(data) for n, data in files.items()},
            "lines": {n: data.count(b"\n") for n, data in files.items()},
            "attribution": "External public submission 402 derivative; original metadata in references/round4-public-402/PROVENANCE.json and frozen parent manifest.",
            "mechanism": "Remove unreachable A/D/router Rust and proof namespaces to reduce extraction/elaboration work. Retained H function bodies, constants and proof blocks are byte-preserved; no algorithm policy change intended.",
            "dependency_audit": "dependency-audit.json",
            "verification": "VERIFIED local generation/dependency checks only; fresh official extraction, obligation, axiom checks, round trip, output equivalence and performance UNKNOWN."}
        files["manifest.json"] = (json.dumps(manifest, indent=2) + "\n").encode()
        files["dependency-audit.json"] = (json.dumps(audit, indent=2) + "\n").encode()
        dest = ROOT / "candidates" / name
        if args.check:
            for filename, data in files.items():
                assert (dest / filename).read_bytes() == data, f"candidate drift: {name}/{filename}"
        else:
            dest.mkdir(parents=True, exist_ok=True)
            for filename, data in files.items():
                (dest / filename).write_bytes(data)
        print(json.dumps({"candidate": name, "hashes": manifest["hashes"], "bytes": manifest["bytes"],
            "lines": manifest["lines"], "functions": len(audit["retained_functions"]), "constants": len(audit["retained_constants"])}))


if __name__ == "__main__":
    main()
