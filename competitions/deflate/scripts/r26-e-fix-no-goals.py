"""E1 proof3 / E2 proof2: guard fallback finishing tactics by remaining goals.

Only the real E1 proof2 No-goals error is addressed. Preserve every prior pair.
"""
from pathlib import Path
import datetime
import hashlib
import json
import re

ROOT = Path(__file__).resolve().parents[1]
OUT = ROOT / "evidence/round26/extension90m/route-e"
FAIL = ROOT / "evidence/round26/38270692372/gate-90-e1-proof2/exact-gate/exact-gate"
OLD = '''       step*
       intro _
       exact Matches.mask hm (by assumption) (by assumption) (by assumption)
         (by assumption) (by assumption) (by assumption) (by assumption)
         (by scalar_tac) (by scalar_tac) (by scalar_tac))'''
NEW = '''       step*
       all_goals
         intro _
         exact Matches.mask hm (by assumption) (by assumption) (by assumption)
           (by assumption) (by assumption) (by assumption) (by assumption)
           (by scalar_tac) (by scalar_tac) (by scalar_tac))'''


def sha(raw):
    return hashlib.sha256(raw).hexdigest()


def dump(path, obj):
    path.write_bytes((json.dumps(obj, indent=2, ensure_ascii=False)+"\n").encode())


def main():
    failures = (FAIL / "logs/005-lake.log").read_bytes()
    errors = re.findall(rb"Proof/Parse\.lean:\d+:\d+: error: [^\r\n]+", failures)
    assert len(errors) == 4
    assert all(b"3537:13: error: No goals to be solved" in error for error in errors)
    pairs = [
        ("r26-e-658-short-same-proof2", "r26-e-658-short-same-proof3",
         "bc1b3fec788a0d58d220efb84505e26f83a7045129c724f43095704c6097adc0",
         "b0d67036601c00bd7cb9831f26693e70d08ab9d529a0b2c5ac5a7562b60c8275", "e1-proof3-entry.json"),
        ("r26-e-658-short-tail-proof1", "r26-e-658-short-tail-proof2",
         "586dec576a2026a5f8c40b82f67e306bd3422faaf938eef2b477477e6af12b06",
         "623d2986bb15846b777c34ca4c17fe6f76ed43a9c4909e8c65ff95a397df3732", "e2-proof2-entry.json"),
    ]
    result = []
    for source, target, rust_hash, lean_hash, entry_name in pairs:
        src = ROOT / "candidates" / source
        dst = ROOT / "candidates" / target
        assert not dst.exists(), dst
        rust = (src / "parse.rs").read_bytes()
        lean1 = (src / "Parse.lean").read_bytes()
        assert sha(rust) == rust_hash and sha(lean1) == lean_hash
        text = lean1.decode()
        start = text.index("theorem same_spec", text.index("namespace U118_MAIN"))
        end = text.index("theorem lz32_le", start)
        theorem = text[start:end]
        assert theorem.count(OLD) == 1
        theorem2 = theorem.replace(OLD, NEW, 1)
        lean2 = (text[:start]+theorem2+text[end:]).encode()
        assert len(lean2) <= 524288
        assert not re.search(rb"(?m)^\s*(axiom\s|.*\b(sorry|admit)\b)", lean2)
        dst.mkdir()
        (dst / "parse.rs").write_bytes(rust)
        (dst / "Parse.lean").write_bytes(lean2)
        metadata = json.loads((src / "manifest.json").read_bytes())
        metadata.update({"candidate": target,
            "hashes": {"parse.rs": sha(rust), "Parse.lean": sha(lean2)},
            "proof_status": "UNCOMPILED_ORIGINAL_GATE_NOT_RUN",
            "proof_origin": {"path": src.relative_to(ROOT).as_posix()+"/Parse.lean", "sha256": sha(lean1)},
            "proof_adaptation": "Only wrap intro/Matches.mask after fallback step* in all_goals. This prevents a finishing tactic from running when step* already closed its branch. Original invariants, clone aliases, short-path obligations and all Rust retained.",
            "proof_freeze_time_utc": datetime.datetime.now(datetime.timezone.utc).isoformat(),
            "observed_failure_receipt": (FAIL / "gate-receipt.json").relative_to(ROOT).as_posix(),
            "observed_failure_receipt_sha256": sha((FAIL / "gate-receipt.json").read_bytes()),
            "observed_failure_log_sha256": sha(failures),
            "observed_failure_scope": "E1 proof2 had4 No-goals errors at3537:13. Same source proof block is in E2; E2 gate outcome not inferred from E1.",
            "confirmation_status": "New exact pair requires its own post-freeze confirmation; prior measurements remain separately bound.",
            "formal_submission_sent": False})
        for key in ["gate_receipt", "gate_receipt_sha256", "verification"]:
            metadata.pop(key, None)
        dump(dst / "manifest.json", metadata)
        entry = {"name": target, "path": dst.relative_to(ROOT).as_posix(),
            "hashes": metadata["hashes"], "status": metadata["proof_status"],
            "rust_bytes": len(rust), "lean_bytes": len(lean2), "lean_spare_bytes": 524288-len(lean2),
            "control": False, "anchor": "public658", "comparison_baseline": "public658"}
        dump(OUT / entry_name, entry)
        result.append(entry)
    dump(OUT / "e1-e2-no-goals-patch.json", {"status": "STATIC_LOCAL_PATCH_ONLY_UNCOMPILED",
        "real_error_lines": [error.decode() for error in errors],
        "log_sha256": sha(failures), "pairs": result,
        "scope": "One same_spec fallback finishing block, Rust unchanged for each algorithm. No clone/mask success is inferred from absence of other reported errors."})
    print(json.dumps(result, indent=2))


if __name__ == "__main__":
    main()
