"""C3 proof3: replace the real invalid match-goal syntax with apply/case."""
from pathlib import Path
import datetime
import hashlib
import json

ROOT = Path(__file__).resolve().parents[1]
SRC = ROOT / "candidates/r26-c-658-deferred-extension-proof2"
DST = ROOT / "candidates/r26-c-658-deferred-extension-proof3"
OUT = ROOT / "evidence/round26/extension90m/proof"
FAIL = ROOT / "evidence/round26/38270325708/gate-90-c3-proof2/exact-gate/exact-gate"
OLD = '''    | (match goal with
       | hm : Matches input _ pos.val ?full |- _ =>
         apply c3_write_post (input := input) (out := out) (pos := pos)
           (d := d) (full := full) (ntok := ntok)
         all_goals first | assumption | (simp only [LZ77.mkMatch, LZ77.MATCH_BASE]; scalar_tac))'''
NEW = '''    | (apply c3_write_post (input := input) (out := out) (pos := pos)
          (d := d) (ntok := ntok)
       case hm => assumption
       all_goals first | assumption | (simp only [LZ77.mkMatch, LZ77.MATCH_BASE]; scalar_tac))'''


def sha(raw):
    return hashlib.sha256(raw).hexdigest()


def dump(path, obj):
    path.write_bytes((json.dumps(obj, indent=2, ensure_ascii=False)+"\n").encode())


def main():
    assert not DST.exists()
    rust = (SRC / "parse.rs").read_bytes()
    lean2 = (SRC / "Parse.lean").read_bytes()
    assert sha(rust) == "58324f244b6deb669e4a4af523a09e5900a016d027b32cc90c785363a19b8da7"
    assert sha(lean2) == "e193b0c34200c4177395e7b0502b8ee51a12de2995052ffc457185764f376300"
    text = lean2.decode()
    assert text.count(OLD) == 1
    lean3 = text.replace(OLD, NEW, 1).encode()
    assert len(lean3) <= 524288
    DST.mkdir()
    (DST / "parse.rs").write_bytes(rust)
    (DST / "Parse.lean").write_bytes(lean3)
    metadata = json.loads((SRC / "manifest.json").read_bytes())
    metadata.update({"candidate": DST.name,
        "hashes": {"parse.rs": sha(rust), "Parse.lean": sha(lean3)},
        "proof_status": "UNCOMPILED_ORIGINAL_GATE_NOT_RUN",
        "proof_origin": {"path": SRC.relative_to(ROOT).as_posix()+"/Parse.lean", "sha256": sha(lean2)},
        "proof_adaptation": "Only replace invalid match-goal syntax by apply c3_write_post; discharge its named hm premise by assumption first to infer full and source, then prove remaining unchanged premises. No generated variable names referenced.",
        "proof_freeze_time_utc": datetime.datetime.now(datetime.timezone.utc).isoformat(),
        "prior_failure_receipt": (FAIL / "gate-receipt.json").relative_to(ROOT).as_posix(),
        "prior_failure_receipt_sha256": sha((FAIL / "gate-receipt.json").read_bytes()),
        "prior_failure_log_sha256": sha((FAIL / "logs/005-lake.log").read_bytes()),
        "confirmation_status": "New pair gate and post-freeze confirmation NOT_RUN.",
        "formal_submission_sent": False})
    for key in ["gate_receipt", "gate_receipt_sha256", "verification"]:
        metadata.pop(key, None)
    dump(DST / "manifest.json", metadata)
    entry = {"name": DST.name, "path": DST.relative_to(ROOT).as_posix(),
        "hashes": metadata["hashes"], "status": metadata["proof_status"],
        "rust_bytes": len(rust), "lean_bytes": len(lean3), "lean_spare_bytes": 524288-len(lean3),
        "control": False, "anchor": "public658", "comparison_baseline": "public658"}
    dump(OUT / "c3-proof3-entry.json", entry)
    print(json.dumps(entry, indent=2))


if __name__ == "__main__":
    main()
