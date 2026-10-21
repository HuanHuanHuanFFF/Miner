"""Freeze R26 C2/C3/C4 proof pairs without changing any prior source or evidence.

This performs byte-level preparation and static checks only. Lean acceptance must
come from the original remote gate, bound to the exact hashes written here.
"""
from pathlib import Path
import datetime
import hashlib
import json
import re

ROOT = Path(__file__).resolve().parents[1]
OUT = ROOT / "evidence/round26/extension90m/proof"
AUDIT = ROOT / "evidence/round26/extension1h/audit"


def sha(raw):
    return hashlib.sha256(raw).hexdigest()


def read(path, expected=None):
    raw = (ROOT / path).read_bytes()
    if expected is not None:
        assert sha(raw) == expected, (path, sha(raw))
    return raw


def dump(path, obj):
    path.write_bytes((json.dumps(obj, indent=2, ensure_ascii=False) + "\n").encode())


def pair(old_name, new_name, lean, origin, adaptation):
    old = ROOT / "candidates" / old_name
    new = ROOT / "candidates" / new_name
    assert not new.exists(), new
    rust = (old / "parse.rs").read_bytes()
    metadata = json.loads((old / "manifest.json").read_bytes())
    assert sha(rust) == metadata["hashes"]["parse.rs"]
    assert len(lean) <= 524288
    forbidden = re.findall(rb"(?m)^\s*(?:axiom\s|.*\b(?:sorry|admit)\b)", lean)
    assert not forbidden, forbidden
    new.mkdir()
    (new / "parse.rs").write_bytes(rust)
    (new / "Parse.lean").write_bytes(lean)
    metadata.update({
        "candidate": new_name,
        "hashes": {"parse.rs": sha(rust), "Parse.lean": sha(lean)},
        "implementation_parent": f"candidates/{old_name}",
        "implementation_parent_hashes": json.loads((old / "manifest.json").read_bytes())["hashes"],
        "proof_status": "UNCOMPILED_ORIGINAL_GATE_NOT_RUN",
        "proof_origin": origin,
        "proof_adaptation": adaptation,
        "proof_static_scope": "Byte-preserving Rust copy, complete parent proof with local adaptations, no sorry/admit/new axiom; static checks are not Lean acceptance.",
        "proof_freeze_time_utc": datetime.datetime.now(datetime.timezone.utc).isoformat(),
        "formal_submission_sent": False,
    })
    metadata.pop("gate_receipt", None)
    metadata.pop("gate_receipt_sha256", None)
    dump(new / "manifest.json", metadata)
    return {"name": new_name, "path": new.relative_to(ROOT).as_posix(),
            "hashes": metadata["hashes"], "rust_bytes": len(rust),
            "lean_bytes": len(lean), "lean_spare_bytes": 524288-len(lean),
            "status": metadata["proof_status"], "proof_origin": origin,
            "control": False, "anchor": "public658", "comparison_baseline": "public658"}


def main():
    OUT.mkdir(parents=True, exist_ok=True)
    baseline = read("references/round26-public-658/Parse.lean",
                    "354d56aa9f58536efdb410f3d5ecdf1945bded607965fe8a48161f96b035c494")
    c4 = read("evidence/round26/extension1h/audit/C4-Parse-proof2-UNCOMPILED.lean",
              "1182e84949bf7e1003af878ff9253ea39d9238147c9e138c374610f104cf53c1")
    c3old = read("evidence/round26/extension1h/audit/C3-Parse-draft.lean")
    c4text = c4.decode()
    helper_start = c4text.index("/- C4 proof draft; not compiled.")
    helper_end = c4text.index("@[local step]\ntheorem fl_tw8_spec", helper_start)
    c4helper = c4text[helper_start:helper_end]
    c3text = c3old.decode()
    c3start = c3text.index("/- C3 proof draft; not compiled.")
    c3end = c3text.index("@[local step]\ntheorem fl_tw8_spec", c3start)
    c3 = (c3text[:c3start] + c4helper.replace("C4", "C3").replace("c4_", "c3_")
          + c3text[c3end:]).encode()
    c2text = baseline.decode()
    back_start = c2text.index("theorem back_loop_inv {W : Std.Usize}")
    back_end = c2text.index("@[local step]\ntheorem back_loop_spec", back_start)
    back = c2text[back_start:back_end]
    old = "    simp only [slot.u118_run_loop0_loop2.body]\n    step*"
    assert back.count(old) == 1
    replacement = ("    -- C2: the added endpoint reads are in bounds; successful whole-token\n"
                   "    -- merges still require the original same_spec, and all failed guards\n"
                   "    -- keep the original part_merge_spec path. Original gate not yet run.\n"
                   "    have c2_tail_left_lt : p.val - 1 < input.length := by omega\n"
                   "    have c2_tail_right_lt : p.val - 1 - d.val < input.length := by omega\n"
                   "    simp only [slot.u118_run_loop0_loop2.body]\n    step*")
    c2 = (c2text[:back_start] + back.replace(old, replacement) + c2text[back_end:]).encode()
    entries = [
        pair("r26-c-658-fold-tail", "r26-c-658-fold-tail-proof1", c2,
             {"path": "references/round26-public-658/Parse.lean", "sha256": sha(baseline)},
             "Retain full U118 BackInv proof. Add explicit input endpoint bounds in the loop body; step* must verify newly extracted short-circuit branches. Original successful same_spec and failed part_merge_spec remain the only correctness paths."),
        pair("r26-c-658-deferred-extension", "r26-c-658-deferred-extension-proof1", c3,
             {"path": "evidence/round26/extension1h/audit/C3-Parse-draft.lean", "sha256": sha(c3old),
              "cap_bind_patch_origin": "evidence/round26/extension1h/audit/C4-Parse-proof2-UNCOMPILED.lean", "cap_bind_patch_sha256": sha(c4)},
             "Replace only the C3 helper block with renamed C4 proof2 explicit cap bind proof. Keep C3-specific eval and greedy loop. Match bytes come from unchanged match_len_spec; original obligation remains complete."),
        pair("r26-c-658-greedy-once-proof1", "r26-c-658-greedy-once-proof2", c4,
             {"path": "evidence/round26/extension1h/audit/C4-Parse-proof2-UNCOMPILED.lean", "sha256": sha(c4)},
             "Exact bytes of prior UNCOMPILED proof2 draft, addressing observed cap if/bind failure. No claim about later casts/writer/fallback or original full gate acceptance."),
    ]
    dump(OUT / "frozen-pairs.json", {"status": "STATIC_PREPARATION_ONLY_UNCOMPILED",
         "prepared_utc": datetime.datetime.now(datetime.timezone.utc).isoformat(), "pairs": entries})
    print(json.dumps(entries, indent=2))


if __name__ == "__main__":
    main()
