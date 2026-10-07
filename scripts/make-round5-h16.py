"""Generate proof-only H16 timeout candidates; no compilation or CI dispatch.

The Rust file is copied byte-for-byte from the frozen small-only H16 parent.
Only its unused B-engine proof section is replaced: the frozen CFG's first
column never equals 1, so plan_cfg must discharge the B branch by contradiction.
The original public parse_spec, all A/C/H proofs and official limits stay intact.
"""
from __future__ import annotations

import argparse
import hashlib
import json
import re
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
PARENT = ROOT / "candidates/r4-hybrid-h16-small299"
DEST = ROOT / "candidates/r5-h16-small-proofopt"
LOCKS = {
    "parse.rs": "d9826bc92ba02f49cb6e552ed172a4fb82dc10fa8fb51aacf73e7947ed38a94d",
    "Parse.lean": "ac2d894b3a4ccacb30ce4ed654a3dd3d3b3c167183eb8df008168772109215fa",
}
SMALL_OUTPUT_LOCKS = {
    "parse.rs": "d9826bc92ba02f49cb6e552ed172a4fb82dc10fa8fb51aacf73e7947ed38a94d",
    "Parse.lean": "d55744de52bb0469768f0bbfd73ffecbabf9899b63e0167469fd7bb79c6293c7",
    "manifest.json": "1d96b09a4305f9bdc88c57cb51efc951d507bc98c6b98d7d88d271a0e866d68e",
    "proof-audit.json": "37badcccfb3f9551dcc326f5fd8785123c997544fc9a8258c715eac73261486d",
}
RECIPES = {
    DEST.name: {
        "parent": PARENT,
        "locks": LOCKS,
        "failure": {"run_id": "37580297956", "git_sha": "8cddb52db662f2c45d8de42e412a140ea6640e59", "stage": "4 statement", "reason": "Proof/Parse.lean did not elaborate within 900s"},
    },
    "r5-h16-smallc-proofopt": {
        "parent": ROOT / "candidates/r4-hybrid-h16-smallc299",
        "locks": {
            "parse.rs": "39c82b4673440faaa7cf9f14ccbeb9367128a7f50a8ca8472880dc35ed24b83e",
            "Parse.lean": "eec49d582853cddf843c33b950f444520561bbb40ef0197ee64ce9acfbb92791",
        },
        "failure": {"run_id": "37581080647", "git_sha": "c47efca9476f375d0e801610ea90c6367530aff2", "stage": "4 statement", "reason": "Proof/Parse.lean did not elaborate within 900s"},
    },
}
B_BEGIN = "/-! # sec_engB (owner: engB)"
B_END = "/-! PROTOTYPE: sec_engC.lean"
PLAN_ANCHOR = "-- @owner spine_top @status DONE @note needs a_engine_spec, b_engine_spec, c_engine_spec"
OLD_DISCHARGE = """  all_goals
    have hc : c ∈ slot.CFG.val := by rw [c_post]; exact List.getElem_mem _
    first
    | exact spine_knob_le (spine_CFG_le c hc) (by assumption)
    | exact spine_knob_skip (spine_CFG_skip c hc) (by assumption) (by assumption) (by assumption)
"""
NEW_DISCHARGE = """  all_goals
    have hc : c ∈ slot.CFG.val := by rw [c_post]; exact List.getElem_mem _
    first
    | (exfalso
       exact spine_knob_notB (spine_CFG_noB c hc) (by assumption) (by assumption))
    | exact spine_knob_le (spine_CFG_le c hc) (by assumption)
    | exact spine_knob_skip (spine_CFG_skip c hc) (by assumption) (by assumption) (by assumption)
"""
NO_B_LEMMAS = """/-! Round 5 proof-only specialization of the frozen configuration table.
Every CFG row selects A (0) or C (2). The B implementation remains in Rust,
but its branch in plan_cfg is impossible for every k, including k >= 16.
The False premise below is an obligation discharged from this table and the
actual branch condition; it is not an assumption of the public entry theorem. -/

theorem spine_CFG_noB : ∀ r ∈ slot.CFG.val, (r.val[0]!).val ≠ 1 := by
  unfold slot.CFG; decide

theorem spine_knob_notB {m : Std.Usize} {r : Array Std.Usize m}
    (hs : (r.val[0]!).val ≠ 1)
    {x0 : Std.Usize} {h0 : 0 < r.val.length}
    (hx0 : x0 = r.val[0]) (hz : x0 = 1#usize) : False := by
  rw [getElem!_pos r.val 0 h0, ← hx0, hz] at hs
  exact hs rfl

@[local step]
theorem spine_b_engine_unreachable_spec (input : Slice Std.U8) (plan)
    (depth h3dist mode bpasses cuts : Std.Usize) (hFalse : False) :
    slot.b_engine input plan depth h3dist mode bpasses cuts ⦃ fun _ => True ⦄ :=
  False.elim hFalse

"""


def sha(data: bytes) -> str:
    return hashlib.sha256(data).hexdigest()


def without_comments(text: str) -> str:
    """Mask Lean comments while preserving offsets and line numbers."""
    chars = list(text)
    i = depth = 0
    while i < len(text):
        if depth:
            if text.startswith("/-", i):
                chars[i:i + 2] = "  "
                depth += 1
                i += 2
            elif text.startswith("-/", i):
                chars[i:i + 2] = "  "
                depth -= 1
                i += 2
            else:
                if chars[i] != "\n":
                    chars[i] = " "
                i += 1
        elif text.startswith("/-", i):
            chars[i:i + 2] = "  "
            depth = 1
            i += 2
        elif text.startswith("--", i):
            end = text.find("\n", i)
            end = len(text) if end == -1 else end
            chars[i:end] = " " * (end - i)
            i = end
        else:
            i += 1
    assert depth == 0, "unclosed parent comment"
    return "".join(chars)


def cfg_rows(source: str) -> list[list[int]]:
    block = source.split("pub const CFG: [[usize; 9]; 16] = [", 1)[1].split("\n];", 1)[0]
    block = re.sub(r"//[^\n]*", "", block)
    rows = [[int(x) for x in re.findall(r"\d+", m[1])]
            for m in re.finditer(r"(?m)^\s*\[([^\]\n]+)\],", block)]
    assert len(rows) == 16 and all(len(row) == 9 for row in rows)
    assert {row[0] for row in rows} == {0, 2}, "CFG now selects another engine"
    return rows


def generate(candidate: str = DEST.name) -> tuple[dict[str, bytes], dict]:
    recipe = RECIPES[candidate]
    parent_path, locks = recipe["parent"], recipe["locks"]
    parent = {name: (parent_path / name).read_bytes() for name in locks}
    for name, data in parent.items():
        assert sha(data) == locks[name], (name, "frozen parent drift")
    rust, proof = parent["parse.rs"].decode(), parent["Parse.lean"].decode()
    assert "\r\n" not in rust + proof
    rows = cfg_rows(rust)
    start, end = proof.index(B_BEGIN), proof.index(B_END)
    assert start < end
    removed = proof[start:end]
    kept = proof[:start] + proof[end:]
    removed_code, kept_code = without_comments(removed), without_comments(kept)
    declarations = re.findall(r"(?m)^(?:theorem|def|abbrev|lemma)\s+([\w.]+)", removed_code)
    assert len(declarations) == 104 and len(set(declarations)) == 104
    outside_refs = {
        name: [kept[:m.start()].count("\n") + 1
               for m in re.finditer(r"(?<![\w.])" + re.escape(name) + r"(?![\w.])", kept_code)]
        for name in declarations
    }
    assert not any(outside_refs.values()), "explicit reference to removed declaration"

    # B's globally active local-step rules target B functions/constants only.
    # Its generic Array rules are enabled via `attribute ... in` only inside
    # B theorem declarations, so removing the section cannot leak those rules
    # out of their existing scope. Report every registration for review.
    global_rules = []
    for match in re.finditer(r"@\[local step\]\s*theorem\s+([\w.]+)", removed_code):
        tail = removed_code[match.end():]
        signature = tail.split(":=", 1)[0]
        target_refs = re.findall(r"\bslot\.([A-Za-z0-9_]+)", signature.split("⦃", 1)[0])
        target = target_refs[-1] if target_refs else None
        assert target and (target.startswith("b_") or target.startswith("B_")), match[1]
        global_rules.append({"name": match[1], "operation": "slot." + target})
    scoped_rules = re.findall(r"attribute\s+\[local step\]\s+([^\n]+?)\s+in\b", removed_code)
    assert all(all(name in declarations for name in text.split()) for text in scoped_rules)
    assert not re.search(r"@\[local (?:simp|scalar_tac)\b", removed_code)
    assert not re.search(r"\battribute\s+\[local (?:simp|scalar_tac)\b", removed_code)

    assert kept.count(PLAN_ANCHOR) == 1 and kept.count(OLD_DISCHARGE) == 1
    optimized = kept.replace(PLAN_ANCHOR, NO_B_LEMMAS + PLAN_ANCHOR, 1)
    optimized = optimized.replace(OLD_DISCHARGE, NEW_DISCHARGE, 1)
    # Reverse the new additions and restore the removed block to prove all
    # unrelated proof bytes are preserved exactly.
    restored_kept = optimized.replace(NO_B_LEMMAS, "", 1).replace(NEW_DISCHARGE, OLD_DISCHARGE, 1)
    assert restored_kept == kept
    assert restored_kept[:start] + removed + restored_kept[start:] == proof
    final_scope = proof[proof.rindex("\nnamespace Submission\n"):]
    assert optimized.endswith(final_scope), "public obligation scope drift"
    assert optimized.count("theorem parse_spec (input : Slice Std.U8)") == 1
    assert optimized.count("namespace Submission\n") == 3
    assert optimized.count("end Submission\n") == 3
    assert not re.search(r"(?m)^\s*(?:axiom|sorry|admit)\b", without_comments(optimized))
    files = {"parse.rs": parent["parse.rs"], "Parse.lean": optimized.encode()}
    assert files["parse.rs"] == parent["parse.rs"]
    assert all(len(value) < 524288 for value in files.values())
    audit = {
        "parent": {"path": parent_path.relative_to(ROOT).as_posix(), "hashes": locks},
        "source_preservation": "VERIFIED byte-identical frozen Rust; no route, constant or engine changes",
        "frozen_CFG_rows": rows,
        "selected_engine_ids": sorted({row[0] for row in rows}),
        "removed_proof_block": {
            "original_line_start": proof[:start].count("\n") + 1,
            "original_line_end": proof[:end].count("\n"),
            "bytes": len(removed.encode()), "sha256": sha(removed.encode()),
            "declarations": declarations,
            "explicit_outside_references": {name: refs for name, refs in outside_refs.items() if refs},
            "globally_active_local_step_rules": global_rules,
            "B_theorem_scoped_step_registrations": scoped_rules,
            "generic_rule_scope": "All B-specific generic Array helpers are registered only with attribute ... in inside removed B theorem declarations; none is globally registered",
            "removed_scalar_or_simp_registrations": [],
        },
        "implicit_call_repair": {
            "only_retained_call_site": "slot.plan_cfg; actual original Funs.lean lines 11266-11300",
            "table_fact": "spine_CFG_noB, proved by unfold slot.CFG; decide",
            "read_and_branch_fact": "spine_knob_notB requires the real row membership/read equality and x0 = 1#usize branch condition",
            "B_leaf_rule": "spine_b_engine_unreachable_spec has a False premise which plan_cfg_spec must discharge; no entry theorem assumes False",
            "automatic_rule_dependency_status": "VERIFIED static explicit/registration scope checks; actual elaborator rule selection and complete gate remain UNKNOWN",
        },
        "added_lemmas_sha256": sha(NO_B_LEMMAS.encode()),
        "plan_cfg_new_discharge_sha256": sha(NEW_DISCHARGE.encode()),
        "all_other_proof_bytes": "VERIFIED reverse substitutions restore the frozen proof exactly",
        "public_obligation_scope_sha256": sha(final_scope.encode()),
        "public_obligation_scope_preserved": True,
        "correctness_scope": "Original all-input Submission.parse_spec; unchanged length bound, output length and LZ77.Valid postcondition",
        "validation_scope": "Static generation and dependency audit only; no local Rust/Lean installation, CI run, axiom-query acceptance or timeout repair claim",
    }
    manifest = {
        "candidate": candidate,
        "parent": audit["parent"],
        "hashes": {name: sha(data) for name, data in files.items()},
        "bytes": {name: len(data) for name, data in files.items()},
        "attribution": "Unmodified Rust composition of external public submissions 299 and 402; original provenance retained in references/round4-public-299 and references/round4-public-402",
        "mechanism": "Proof-only elimination of B totality proofs; every frozen CFG row selects A or C, and the impossible B branch is closed from the table and real branch condition",
        "public_obligation_preserved": True,
        "proof_audit": "proof-audit.json",
        "original_failure": recipe["failure"],
        "official_limits": "Unchanged external verifier, LZ77.Obligation, axiom whitelist and 900-second per-call timeout",
        "verification": "VERIFIED local generation, Rust equality, CFG values and static proof dependency scopes only. Fresh extraction, Lean typecheck/axioms, runtime <900s and full gate UNKNOWN; original failure is not repaired until that gate passes",
        "performance": "Rust bytes unchanged; no algorithm/performance improvement claimed",
    }
    files["proof-audit.json"] = (json.dumps(audit, indent=2) + "\n").encode()
    files["manifest.json"] = (json.dumps(manifest, indent=2) + "\n").encode()
    if candidate == DEST.name:
        assert {name: sha(data) for name, data in files.items()} == SMALL_OUTPUT_LOCKS, "running small-only candidate byte drift"
    return files, manifest


def main() -> None:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--check", action="store_true", help="compare only; no writes")
    parser.add_argument("--only", action="append", choices=sorted(RECIPES), default=[],
                        help="default remains the existing small-only candidate")
    args = parser.parse_args()
    for candidate in args.only or [DEST.name]:
        files, manifest = generate(candidate)
        target = ROOT / "candidates" / candidate
        if args.check:
            for name, data in files.items():
                assert (target / name).read_bytes() == data, (name, "candidate drift")
        else:
            target.mkdir(parents=True, exist_ok=True)
            for name, data in files.items():
                path = target / name
                if path.exists() and path.read_bytes() == data:
                    continue
                assert candidate != DEST.name or not path.exists(), "preserve running small-only input"
                path.write_bytes(data)
        print(json.dumps({"candidate": candidate, "hashes": manifest["hashes"], "bytes": manifest["bytes"], "check_only": args.check}))


if __name__ == "__main__":
    main()
