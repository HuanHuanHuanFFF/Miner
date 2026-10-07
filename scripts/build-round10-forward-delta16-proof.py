"""Draft totality proof bridge for the D-only compact chain candidate.

Preserves the screen candidate. Fresh extraction and original gate remain
mandatory; this script does not invoke either and does not claim Lean success.
"""
from pathlib import Path
import argparse
import hashlib
import json

ROOT = Path(__file__).resolve().parents[1]
BASE = ROOT / "candidates/r10-forward-delta16"
DEST = ROOT / "candidates/r10-forward-delta16-proof"


def sha(data):
    return hashlib.sha256(data).hexdigest()


def generate():
    source = (BASE / "parse.rs").read_bytes()
    original = (BASE / "Parse.lean").read_text(encoding="utf-8")
    manifest = json.loads((BASE / "manifest.json").read_text())
    assert sha(source) == manifest["hashes"]["parse.rs"]
    # These old helper proofs concern totality and head bounds, not any
    # representation invariant of the prev arrays. They therefore adapt locally.
    a = original.index("@[local step] theorem skip_same_spec")
    b = original.index("theorem dp_nextl_lt", a)
    helpers = original[a:b]
    for old, new in (("skip_same", "d16_skip_same"), ("insert_pos", "d16_insert_pos"), ("insert_range", "d16_insert_range")):
        helpers = helpers.replace(old, new)
    a = original.index("@[local step]\ntheorem d_walk_loop_spec")
    b = original.index("@[local step]\ntheorem d_back_best_loop_spec", a)
    walk = original[a:b].replace("d_walk", "d16_walk")
    old_next = "(by omega : (UScalar.cast .Usize i3).val ≤ i.val)"
    new_next = "(by omega : (core.num.Usize.wrapping_sub c' (UScalar.cast .Usize i3)).val ≤ i.val)"
    assert walk.count(old_next) == 1
    walk = walk.replace(old_next, new_next)
    link = '''@[local step]
theorem d16_link_spec (q c : Std.Usize) : slot.d16_link q c ⦃ fun _ => True ⦄ := by
  rw [slot.d16_link]
  step*
  repeat' (split <;> step*)
  all_goals scalar_tac

'''
    a = original.index("@[local step]\ntheorem d_parse_loop_spec")
    b = original.index("@[local step]\ntheorem d_plan_k_loop_spec", a)
    old_parse = original[a:b]
    parse = old_parse.replace("Array Std.U32 32768#usize", "Array Std.U16 32768#usize")
    assert old_parse.count("Array Std.U32 32768#usize") == 4
    for old, new in (("insert_pos_spec", "d16_insert_pos_spec"), ("insert_range_spec", "d16_insert_range_spec"),
                     ("skip_same_spec", "d16_skip_same_spec"), ("d_walk_spec", "d16_walk_spec")):
        assert old in parse
        parse = parse.replace(old, new)
    proof = original[:a] + link + helpers + walk + parse + original[b:]
    files = {"parse.rs": source, "Parse.lean": proof.encode()}
    assert len(files["Parse.lean"]) < 524288
    meta = dict(manifest)
    meta.update(candidate=DEST.name, parent="candidates/r10-forward-delta16", parent_hashes=manifest["hashes"],
                hashes={n: sha(data) for n, data in files.items()}, bytes={n: len(data) for n, data in files.items()},
                proof_status="DRAFT_UNTESTED: local helper and U16 loop-state bridge; real extraction signatures and complete original gate remain pending")
    files["manifest.json"] = (json.dumps(meta, indent=2) + "\n").encode()
    return files


def main():
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument("--check", action="store_true")
    args = ap.parse_args()
    files = generate()
    if args.check:
        assert all((DEST / n).read_bytes() == data for n, data in files.items())
    else:
        DEST.mkdir(parents=True, exist_ok=True)
        for n, data in files.items():
            (DEST / n).write_bytes(data)
    print(json.dumps({"candidate": DEST.name, "hashes": json.loads(files["manifest.json"])["hashes"], "status": "DRAFT_UNTESTED"}))


if __name__ == "__main__":
    main()
