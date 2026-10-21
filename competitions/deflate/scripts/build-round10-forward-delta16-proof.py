"""Draft totality proof bridge for the D-only compact chain candidate.

Preserves the screen candidate. Fresh extraction and original gate remain
mandatory; this script does not invoke either and does not claim Lean success.
"""
from pathlib import Path
import argparse
import hashlib
import json
import re

ROOT = Path(__file__).resolve().parents[1]
BASE = ROOT / "candidates/r10-forward-delta16"
DEST = ROOT / "candidates/r10-forward-delta16-proof"
EXTRACT = ROOT / "evidence/round10/37684506856/struct-b/extraction"


def sha(data):
    return hashlib.sha256(data).hexdigest()


def generate():
    source = (BASE / "parse.rs").read_bytes()
    original = (BASE / "Parse.lean").read_text(encoding="utf-8")
    manifest = json.loads((BASE / "manifest.json").read_text())
    assert sha(source) == manifest["hashes"]["parse.rs"]
    extraction = json.loads((EXTRACT / "research.json").read_text())["extractions"][BASE.name]
    assert extraction["extraction_accepted"] and extraction["source_sha256"] == sha(source)
    for name, record in extraction["files"].items():
        assert sha((EXTRACT / BASE.name / name).read_bytes()) == record["sha256"]
    funs = (EXTRACT / BASE.name / "Funs.lean").read_text()
    expected_args = {
        "d16_link": "q c",
        "d16_insert_pos": "head3 head4 prev4 head7 prev7 q b8 sh7",
        "d16_insert_range_loop": "input head3 head4 prev4 head7 prev7 «to» sh7 q",
        "d16_insert_range": "input head3 head4 prev4 head7 prev7 «from» «to» sh7",
        "d16_skip_same": "prev start depth same",
        "d16_walk_loop": "s prev i b8 cap cands nice nc best c k",
        "d16_walk": "s prev i start depth b8 cap cands nc0 best0 nice",
        "d_parse_loop": "input plan rs ct lazyn d4 d7 skip h3d tbmax lz2max dupmode fback d7l d7e nice n head3 head4 prev4 head7 prev7 pa tb lsym dtab nextl lf df litc lc dcc lim sh7 s next_upd cands pc pn ppos cl cd cdc i anchor alen",
    }
    interfaces = {}
    for name, expected in expected_args.items():
        match = re.search(r"^def " + re.escape(name) + r"(?=\s)(.*?) := do", funs, re.M | re.S)
        assert match, name
        signature = match.group(1)
        args = " ".join(re.findall(r"\(([^():]+) : ", signature))
        assert args == expected, (name, args, expected)
        interfaces[name] = {"arguments": args, "u16_chain_arrays": signature.count("Array Std.U16 32768#usize")}
    assert interfaces["d16_walk_loop"]["u16_chain_arrays"] == 1
    assert interfaces["d_parse_loop"]["u16_chain_arrays"] == 2
    parent_funs = (ROOT / "evidence/round9/37660750561/block-a/screen/research5/r9-block-scalar/Funs.lean").read_text()
    def definition(text, name):
        match = re.search(r"^def " + re.escape(name) + r"(?=\s)(.*?)(?=\n/--|\Z)", text, re.M | re.S)
        assert match, name
        return " ".join(match.group(0).split())
    transformed_parent = {}
    for name in ("d_parse_loop.body", "d_parse_loop", "d_parse"):
        old = definition(parent_funs, name).replace("Array Std.U32 32768#usize", "Array Std.U16 32768#usize")
        old = old.replace("Array.repeat 32768#usize 0#u32", "Array.repeat 32768#usize 0#u16")
        for helper in ("insert_pos", "insert_range", "skip_same", "d_walk"):
            old = re.sub(r"\b" + helper + r"\b", "d16_" + helper.removeprefix("d_"), old)
        new = definition(funs, name)
        assert old == new, name
        transformed_parent[name] = sha(new.encode())
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
    assert walk.count("Array Std.U32 32768#usize") == 1
    walk = walk.replace("Array Std.U32 32768#usize", "Array Std.U16 32768#usize")
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
                proof_status="INTERFACE_RECONCILED_UNCOMPILED: exact helper and U16 state interfaces reconciled with run 37684506856; original full gate untested",
                extracted_funs_sha256=extraction["files"]["Funs.lean"]["sha256"])
    files["manifest.json"] = (json.dumps(meta, indent=2) + "\n").encode()
    files["interface-audit.json"] = (json.dumps({
        "status": "VERIFIED_INTERFACE_ONLY", "run_id": "37684506856", "source_sha256": sha(source),
        "proof_sha256": meta["hashes"]["Parse.lean"], "extracted_files": extraction["files"],
        "interfaces": interfaces,
        "parent_definition_check": "After omitting Source comments and normalizing whitespace, all three D parser definitions equal the parent with only expected U16 types/zero values and helper call names replaced",
        "normalized_parser_definition_sha256": transformed_parent,
        "correction": "d16_walk_loop_spec predecessor parameter explicitly corrected from U32 to U16; d_parse's four explicit tuple-array types were already U16",
        "proof_elaboration": "UNKNOWN: no local Lean toolchain; original obligation, axiom whitelist and round trip remain required",
    }, indent=2) + "\n").encode()
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
    print(json.dumps({"candidate": DEST.name, "hashes": json.loads(files["manifest.json"])["hashes"], "status": "INTERFACE_RECONCILED_UNCOMPILED"}))


if __name__ == "__main__":
    main()
