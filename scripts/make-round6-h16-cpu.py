"""Generate at most two attribute-only CPU hypotheses from the frozen H16 baseline.

Writes only candidates/r6-h16-cpu-{rm-inline,replay-inline}. No compiler,
toolchain installation, measurement, CI, Git or external action. --check only
reconstructs bytes in memory and compares them with saved candidate artifacts.
"""
from __future__ import annotations

import argparse
import hashlib
import json
import re
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
BASE = ROOT / "candidates/r5-h16-small-proofopt"
LOCKS = {
    "parse.rs": "d9826bc92ba02f49cb6e552ed172a4fb82dc10fa8fb51aacf73e7947ed38a94d",
    "Parse.lean": "d55744de52bb0469768f0bbfd73ffecbabf9899b63e0167469fd7bb79c6293c7",
}
INLINE = "#[inline(always)]\n"
RECIPES = {
    "r6-h16-cpu-rm-inline": {
        "functions": ["h_rm_update", "h_rm_update3", "h_rm_upd"],
        "mechanism": "Add inline(always) only to the guarded ring-minimum update dispatcher and its two fixed-depth leaf updates; retain every body, index, comparison, budget and call site",
        "source_evidence": "h_dp_prune and h_dp_items call h_rm_upd once per backward byte; h_rm_upd selects the four/five-level ring update from l4. These functions have no parent inline attribute",
        "hypothesis": "Inlining this bounded update chain may remove per-byte dispatch/call boundaries or expose a stable l4 branch to the surrounding DP loop. The release compiler may already inline it",
        "diagnostic": "Compare baseline/shadow/candidate symbol sizes and actual calls in h_dp_prune/h_dp_items; inspect whether h_rm_upd and its leaf calls survive, and whether total code size grows",
    },
    "r6-h16-cpu-replay-inline": {
        "functions": ["h_relax_items"],
        "mechanism": "Add inline(always) only to h_relax_items, the cached-query replay kernel called by h_dp_items; retain every query, scan order, cost and update",
        "source_evidence": "h_dp_items calls h_relax_items once per backward byte during h_pass_items, which h_dp_pass selects for pr != 0; h_relax_items has exactly one syntactic caller and no parent inline attribute",
        "hypothesis": "Inlining the replay kernel may remove the per-byte call/argument boundary and expose the query loop to the caller. It may instead duplicate code or have no effect because fat LTO already inlines it",
        "diagnostic": "Compare baseline/shadow/candidate h_dp_items/h_relax_items call sites and sizes; retain the hypothesis only with realized paired total-compression gain and unchanged token/output identities",
    },
}


def sha(data: bytes) -> str:
    return hashlib.sha256(data).hexdigest()


def masked(source: str) -> str:
    return re.sub(r'//[^\n]*|/\*.*?\*/|"(?:\\.|[^"\\])*"',
                  lambda m: "".join("\n" if c == "\n" else " " for c in m[0]),
                  source, flags=re.S)


def functions(source: str) -> dict:
    plain = masked(source)
    found = {}
    for match in re.finditer(r"(?m)^(?:#\[[^\n]*\]\s*\n)*pub fn (\w+)\b[^{}]*\{", plain):
        pos, depth = match.end(), 1
        while depth:
            assert pos < len(plain), match[1]
            depth += (plain[pos] == "{") - (plain[pos] == "}")
            pos += 1
        found[match[1]] = {
            "start": match.start(), "end": pos,
            "declaration": source[match.start():pos],
            "body": plain[match.end():pos - 1],
        }
    assert len(found) == len(re.findall(r"\bfn\s+\w+\s*[<(]", plain)) == 233
    return found


def generate(name: str) -> tuple[dict[str, bytes], dict]:
    recipe = RECIPES[name]
    base = {file: (BASE / file).read_bytes() for file in LOCKS}
    for file, expected in LOCKS.items():
        assert sha(base[file]) == expected, (file, "frozen H16 base drift")
    source, proof = base["parse.rs"].decode(), base["Parse.lean"]
    assert "\r\n" not in source
    old_functions = functions(source)
    result = source
    target_audit = []
    for target in recipe["functions"]:
        declaration = old_functions[target]
        assert declaration["declaration"].startswith("pub fn " + target), (target, "unexpected parent attribute")
        line = source[:declaration["start"]].count("\n") + 1
        callers = {
            caller: len(re.findall(r"\b" + re.escape(target) + r"\s*\(", data["body"]))
            for caller, data in old_functions.items()
            if re.search(r"\b" + re.escape(target) + r"\s*\(", data["body"])
        }
        pattern = r"(?m)^pub fn " + re.escape(target) + r"\b"
        result, count = re.subn(pattern, INLINE + "pub fn " + target, result)
        assert count == 1, (target, count)
        target_audit.append({
            "function": target, "parent_line": line,
            "original_declaration_sha256": sha(declaration["declaration"].encode()),
            "original_declaration_bytes": len(declaration["declaration"].encode()),
            "parent_attribute": None, "new_attribute": "inline(always)",
            "syntactic_callers": callers,
            "actual_compiled_calls": "UNKNOWN until same-run assembly is collected",
        })
    assert result.count(INLINE) == source.count(INLINE) + len(recipe["functions"])
    restored = result
    for target in recipe["functions"]:
        restored, count = re.subn(r"(?m)^#\[inline\(always\)\]\n(?=pub fn " + re.escape(target) + r"\b)", "", restored)
        assert count == 1
    assert restored == source, "non-attribute source byte changed"
    new_functions = functions(result)
    assert new_functions.keys() == old_functions.keys()
    for function, original in old_functions.items():
        candidate_declaration = new_functions[function]["declaration"]
        if function in recipe["functions"]:
            assert candidate_declaration.startswith(INLINE)
            candidate_declaration = candidate_declaration[len(INLINE):]
        assert candidate_declaration == original["declaration"], function
    files = {"parse.rs": result.encode(), "Parse.lean": proof}
    assert sha(files["Parse.lean"]) == LOCKS["Parse.lean"]
    assert all(len(data) < 524288 for data in files.values())
    audit = {
        "parent": {"path": BASE.relative_to(ROOT).as_posix(), "hashes": LOCKS},
        "targets": target_audit,
        "attribute_only_reverse_check": "VERIFIED removing exactly the added inline(always) lines restores the complete parent Rust byte-for-byte",
        "all_233_function_declarations": "VERIFIED identical after removing only the named attributes",
        "constants_types_comments_route_budget_model": "VERIFIED all non-attribute bytes unchanged",
        "proof": "VERIFIED exact frozen baseline Lean bytes; obligation, false-branch proof and axiom policy unchanged",
        "extraction_expectation": "INFERRED same function bodies/specs: only code-generation hints change, no Rust expression/signature/loop/call graph changes. Official Charon/Aeneas re-extraction must still establish compatibility",
        "extraction_reference": "sources/conjectures-optimisation-deflate/validator/verifier/extract.sh uses charon --preset=aeneas --translate-all-methods; fresh extracted semantic definitions and complete 900s gate remain required",
        "not_established": ["Rust build", "realized inline/call/layout change", "re-extraction equivalence", "Lean/axiom acceptance", "finite token/output identity", "paired total-time gain"],
    }
    manifest = {
        "candidate": name,
        "parent": audit["parent"],
        "hashes": {file: sha(data) for file, data in files.items()},
        "bytes": {file: len(data) for file, data in files.items()},
        "mechanism": recipe["mechanism"],
        "source_evidence": recipe["source_evidence"],
        "hypothesis": recipe["hypothesis"],
        "diagnostic": recipe["diagnostic"],
        "attribute_functions": recipe["functions"],
        "attribute_audit": "attribute-audit.json",
        "expected_equivalent": True,
        "equivalence_reference": BASE.name,
        "expected_equivalence_scope": "INFERRED identical Rust bodies/control flow plus unchanged proof; finite execution and fresh official proof still required",
        "baseline_gate": {"run_id": "37584216832", "commit": "3d9494eb4370e20e8c76ed243a2093d6c8b2ec60", "scope": "Full public gate only; does not certify changed source hashes"},
        "attribution": "CPU derivative of frozen H16 small-only combination of external public submissions 299 and 402; original source/provenance retained in references/round4-public-299 and references/round4-public-402",
        "verification": "VERIFIED static generation/reverse-byte/function/proof checks only. Fresh build, extraction, Lean/axioms, round trip, token/output identity and paired H16-baseline/shadow performance UNKNOWN",
        "scope": "CPU code-generation hypothesis only; no H/S routing, search budget, global cost model or encoder change; no private-stage2, admission, rank or reward claim",
    }
    files["attribute-audit.json"] = (json.dumps(audit, indent=2) + "\n").encode()
    files["manifest.json"] = (json.dumps(manifest, indent=2) + "\n").encode()
    return files, manifest


def main() -> None:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--only", action="append", choices=sorted(RECIPES), default=[])
    parser.add_argument("--check", action="store_true", help="compare only; no writes")
    args = parser.parse_args()
    for name in args.only or RECIPES:
        files, manifest = generate(name)
        target = ROOT / "candidates" / name
        if args.check:
            for file, data in files.items():
                assert (target / file).read_bytes() == data, (name, file, "candidate drift")
        else:
            target.mkdir(parents=True, exist_ok=True)
            for file, data in files.items():
                path = target / file
                if not path.exists() or path.read_bytes() != data:
                    path.write_bytes(data)
        print(json.dumps({"candidate": name, "hashes": manifest["hashes"], "bytes": manifest["bytes"], "check_only": args.check}))


if __name__ == "__main__":
    main()
