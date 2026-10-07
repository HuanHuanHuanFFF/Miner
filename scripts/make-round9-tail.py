"""Add #361's exact tail-word rejection to block1's D finder.

Candidate proof reuses walk_t's totality argument with D's nice stop retained.
Actual extraction, original Lean obligation, and performance remain untested.
"""

from pathlib import Path
import argparse
import hashlib
import json


ROOT = Path(__file__).resolve().parents[1]
BASE = ROOT / "candidates/r7-mid361-block1"
NAME = "r9-block-tail"


def sha(data: bytes) -> str:
    return hashlib.sha256(data).hexdigest()


def generate() -> dict[str, bytes]:
    raw = {n: (BASE / n).read_bytes() for n in ("parse.rs", "Parse.lean")}
    parent = json.loads((BASE / "manifest.json").read_text())
    assert all(sha(raw[n]) == parent["hashes"][n] for n in raw)
    source, proof = (raw[n].decode("utf-8") for n in ("parse.rs", "Parse.lean"))
    start = source.index("/// `walk` with a stop once a match of at least `nice` bytes is known.")
    end = source.index("/// `back_best` with a limit", start)
    old_source = source[start:end]
    old_probe = """            let l = probe(s, c, i, b8, cap, best);
            if l > 0 && nc < 15 {
                cands[nc % 16] = (l as u32) | ((d as u32) << 9);
                nc += 1;
                best = l;
            }"""
    new_probe = """            if tailw(s, c, best) == tw {
                let l = probe(s, c, i, b8, cap, best);
                if l > 0 && nc < 15 {
                    cands[nc % 16] = (l as u32) | ((d as u32) << 9);
                    nc += 1;
                    best = l;
                    tw = tailw(s, i, best);
                }
            }"""
    assert old_source.count(old_probe) == 1
    assert old_source.count("    let mut best = best0;") == 1
    changed = old_source.replace(
        "/// `walk` with a stop once a match of at least `nice` bytes is known.",
        "/// D chain walk with walk_t's exact tail-word rejection and the original nice stop.",
        1,
    ).replace("    let mut best = best0;", "    let mut best = best0;\n    let mut tw = tailw(s, i, best);", 1).replace(old_probe, new_probe, 1)
    rust = source[:start] + changed + source[end:]
    assert rust.replace(changed, old_source, 1) == source
    assert "best < cap && best < nice && nc < 15" in changed
    assert "probe(s, c, i, b8, cap, best)" in changed

    template_start = proof.index("@[local step]\ntheorem walk_t_loop_spec")
    template_end = proof.index("@[local step] theorem dp_store_spec", template_start)
    template = proof[template_start:template_end]
    new_proof = template.replace("walk_t", "d_walk")
    assert new_proof.count("(cands) (nc best : Std.Usize)") == 1
    assert new_proof.count("(cap : Std.Usize) (cands) (nc0 best0 : Std.Usize)") == 1
    new_proof = new_proof.replace("(cands) (nc best : Std.Usize)", "(cands) (nice nc best : Std.Usize)", 1)
    new_proof = new_proof.replace("s prev i b8 cap cands nc best tw c k", "s prev i b8 cap cands nice nc best tw c k", 1)
    new_proof = new_proof.replace("(cap : Std.Usize) (cands) (nc0 best0 : Std.Usize)", "(cap : Std.Usize) (cands) (nc0 best0 nice : Std.Usize)", 1)
    new_proof = new_proof.replace("s prev i start depth b8 cap cands nc0 best0 ⦃", "s prev i start depth b8 cap cands nc0 best0 nice ⦃", 1)
    ps = proof.index("@[local step]\ntheorem d_walk_loop_spec")
    pe = proof.index("@[local step]\ntheorem d_back_best_loop_spec", ps)
    old_proof = proof[ps:pe]
    lean = proof[:ps] + new_proof + proof[pe:]
    assert lean.replace(new_proof, old_proof, 1) == proof
    assert lean.count("theorem d_walk_loop_spec") == 1
    assert lean.count("theorem d_walk_spec") == 1
    files = {"parse.rs": rust.encode(), "Parse.lean": lean.encode()}
    assert all(len(b) <= 524288 for b in files.values())
    manifest = {
        "candidate": NAME,
        "parent": "candidates/r7-mid361-block1",
        "base_submission_id": "361",
        "parent_hashes": parent["hashes"],
        "hashes": {n: sha(b) for n, b in files.items()},
        "bytes": {n: len(b) for n, b in files.items()},
        "attribution": {
            "author_hotkey": parent["attribution"],
            "public_reference": "references/round7-public-361/PROVENANCE.json",
            "verified_parent": "candidates/r7-mid361-block1/VERIFICATION.json",
            "mechanism_source": "#361 walk_t/tailw, copied into D's walk while retaining D's nice guard",
        },
        "mechanism": "Before probe, reject a chain node whose eight bytes ending at current best differ; update the cached tail only when best increases",
        "audit": "Reverse only the d_walk source/proof region replacement restores block1 bytes. Original signature, nice guard, probe cap, candidate sequence, routes, depths, records, backward DP and emitters are retained.",
        "equivalence_status": "INFERRED: beating best requires the checked tail bytes; below 8 both tails are zero. Fresh token/output differential required.",
        "proof_status": "UNKNOWN: d_walk loop proof adapted from existing walk_t totality; six-state loop interface needs fresh extraction and original obligation/axiom gate.",
        "performance_status": "UNKNOWN: tail filtering may save common scans or add load overhead; paired total compression required.",
    }
    files["manifest.json"] = (json.dumps(manifest, indent=2) + "\n").encode()
    return files


def main() -> None:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--check", action="store_true")
    args = parser.parse_args()
    files = generate()
    dest = ROOT / "candidates" / NAME
    if args.check:
        assert all((dest / n).read_bytes() == b for n, b in files.items())
    else:
        dest.mkdir(parents=True, exist_ok=True)
        for n, b in files.items():
            if (dest / n).exists() and (dest / n).read_bytes() != b:
                raise ValueError(f"existing {NAME}/{n} differs; preserve it")
            (dest / n).write_bytes(b)
    print(json.dumps({"candidate": NAME, "hashes": json.loads(files["manifest.json"])["hashes"], "proof_status": "DRAFT_UNTESTED"}))


if __name__ == "__main__":
    main()
