"""Owned complete-source recipe: admit amortizable singleton rows to prepared MD.

The private upstream full source is not redistributed. This one predicate edit
keeps every existing runtime/proof declaration, original small-k singleton
route, sparse/nonfinite checks, all twelve endpoints, and the original proof.
The proof's preparation/mutation invariant is quantified over arbitrary rows;
the exact changed full source still requires the original complete Lean gate.
"""
from pathlib import Path
import argparse
import hashlib
import json
from datetime import datetime, timezone

BASE = "595a90fa2b6bc5d3657434fae7d1292b27910ef653da2b7f409ed9c34c956e2b"
OLD = "if 2<= rows && 0< inW && inW<1048576 && rows*inW<= X"
NEW = "if (2<= rows || (rows=1 && 64<=inW)) && 0< inW && inW<1048576 && rows*inW<= X"


def sha(raw):
    return hashlib.sha256(raw).hexdigest()


def transform(raw, submission=36, variant="single-row36"):
    assert submission == 36 and variant == "single-row36"
    assert sha(raw) == BASE, "exact public36 source required"
    source = raw.decode("utf-8")
    assert source.count(OLD) == 1
    result = source.replace(OLD, NEW).encode("utf-8")
    assert len(result) <= 256000
    assert result.count(b"import ") == 1
    assert b"import ContractExact\n" in result
    assert b"theorem correct:Obligation kernels" in result
    return result


def main():
    p = argparse.ArgumentParser()
    p.add_argument("--source", type=Path, required=True)
    p.add_argument("--output", type=Path)
    p.add_argument("--receipt", type=Path, required=True)
    a = p.parse_args()
    raw = a.source.read_bytes()
    result = transform(raw)
    if a.output:
        a.output.parent.mkdir(parents=True, exist_ok=True)
        a.output.write_bytes(result)
    receipt = {
        "at_utc": datetime.now(timezone.utc).isoformat(),
        "state": "ACTUAL_ALL12_SOURCE_NOT_YET_COMPILED",
        "base_submission": 36,
        "base_sha256": sha(raw),
        "base_bytes": len(raw),
        "candidate_sha256": sha(result),
        "candidate_bytes": len(result),
        "free_bytes": 256000 - len(result),
        "recipe_sha256": sha(Path(__file__).read_bytes()),
        "edit_count": 1,
        "mechanism": "rows=1,inW>=64 now uses existing MPr/MVo/MaU/MD prepared signed128 path; rows>=2 unchanged; singleton small-k and every original fallback remain",
        "proof_review": "ZMV0 only extracts inW<1048576 from outer predicate; ZMVi and ZMVa quantify over arbitrary rows and MVi explicitly delegates the singleton tail to MVo. No theorem body or obligation is edited. Exact changed-source compilation remains required.",
        "target": "Mixer final classifier is always linear rows=1 with flattened tokens*channels, so the previous YaVM rows>=2 restriction excludes this entire stage",
        "scope": "Full original twelve endpoints remain; correctness/performance/adoption UNKNOWN until original gate and complete paired model screen",
        "speed": "UNKNOWN",
        "publication": "Owned recipe and receipt only. Upstream and reconstructed full Kernel stay private/ephemeral.",
    }
    a.receipt.write_text(json.dumps(receipt, indent=2, ensure_ascii=False) + "\n", encoding="utf-8")
    print(json.dumps({k: receipt[k] for k in ("candidate_sha256", "candidate_bytes", "free_bytes", "state")}))


if __name__ == "__main__":
    main()
