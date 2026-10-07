"""Retain a four-line seed proof repair draft without scheduling another gate.

The failed frozen proof is preserved. Explicit arithmetic goal types make the
tuple projections definitionally reduce before omega; this remains untested.
"""
from pathlib import Path
import argparse
import hashlib
import json
import re

ROOT = Path(__file__).resolve().parents[1]
BASE = ROOT / "candidates/r10-forward-seed-proof"
DEST = ROOT / "candidates/r10-forward-seed-proof2"
LOG = ROOT / "evidence/round10/37682364860/prove-a/gate/r10-forward-seed-proof-005-lake.log"
FROZEN = "b41316b50ffee2a7f26ec3ec87e14cb65dbe777b00aadca628f69a5887cfcca2"


def sha(data):
    return hashlib.sha256(data).hexdigest()


def generate():
    raw = (BASE / "Parse.lean").read_bytes()
    assert sha(raw) == FROZEN
    proof = raw.decode()
    replacements = [
        ("(by clear * - h14 hlt'; omega)", "(by clear * - h14 hlt'; omega : lim.val - i4.val < lim.val - i'.val)", 2),
        ("(by clear * - hend hb3 hlt'; omega)", "(by clear * - hend hb3 hlt'; omega : lim.val - «end».val < lim.val - i'.val)", 1),
        ("(by clear * - hq' hq1; omega)", "(by clear * - hq' hq1; omega : n.val - q1.val < n.val - q'.val)", 1),
    ]
    for old, new, count in replacements:
        assert proof.count(old) == count
        proof = proof.replace(old, new)
    log = LOG.read_text()
    errors = re.findall(r"^Proof/Parse\.lean:(\d+):(\d+): error: (.*)$", log, re.M)
    assert [int(e[0]) for e in errors] == [3676, 3815, 3821, 3945]
    files = {"parse.rs": (BASE / "parse.rs").read_bytes(), "Parse.lean": proof.encode()}
    parent = json.loads((BASE / "manifest.json").read_text())
    meta = dict(parent)
    meta.update(candidate=DEST.name, parent="candidates/r10-forward-seed-proof", parent_hashes=parent["hashes"],
                hashes={n: sha(data) for n, data in files.items()}, bytes={n: len(data) for n, data in files.items()},
                proof_status="UNTESTED_REPAIR_DRAFT_NO_CI: four termination-goal projection repairs; no new Lean execution and no renewed gate requested",
                performance_status="REJECTED_FOR_FURTHER_SEED_SEARCH: first screen and independent remeasurement retain material size regression; this proof draft is retained only for reuse")
    files["manifest.json"] = (json.dumps(meta, indent=2) + "\n").encode()
    note = {
        "failed_run": "37682364860", "failed_proof_sha256": FROZEN,
        "log_path": str(LOG.relative_to(ROOT)), "log_sha256": sha(LOG.read_bytes()),
        "errors": [{"line": int(a), "column": int(b), "message": c} for a, b, c in errors],
        "observed_failure": "Four omega goals still contained tuple projection expressions for a strictly advancing cursor; no other error was emitted in the retained log.",
        "proposed_repair": "State each arithmetic decrease as an explicit proposition, allowing definitional equality to reduce the tuple projection before omega.",
        "scope": "Only four proof terms change. Rust, declarations, loop invariants and original obligation are unchanged.",
        "validation": "UNTESTED: no Lean elaboration or gate was run for this repair. Lack of other reported errors is not a complete proof.",
        "dispatch": "No additional seed gate requested; poor measured size tradeoff stops this family.",
    }
    files["failure-repair-note.json"] = (json.dumps(note, indent=2) + "\n").encode()
    return files


def main():
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument("--check", action="store_true")
    args = ap.parse_args()
    files = generate()
    if args.check:
        assert all((DEST / name).read_bytes() == data for name, data in files.items())
    else:
        DEST.mkdir(parents=True, exist_ok=True)
        for name, data in files.items():
            if (DEST / name).exists() and (DEST / name).read_bytes() != data:
                raise ValueError(f"preserve existing different file {DEST / name}")
            (DEST / name).write_bytes(data)
    print(json.dumps({"candidate": DEST.name, "hashes": json.loads(files["manifest.json"])["hashes"], "status": "UNTESTED_REPAIR_DRAFT_NO_CI"}))


if __name__ == "__main__":
    main()
