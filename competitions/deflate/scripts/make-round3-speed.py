"""Generate two bucket-specific footprint candidates from the accepted bucket2 source.

This runs only lightweight file operations. A copied proof is not a gate receipt:
both changed sources require fresh official extraction, Lean, and round trips.
"""
from __future__ import annotations

import argparse
import hashlib
import json
from pathlib import Path
import re

ROOT = Path(__file__).resolve().parents[1]
BASE = ROOT / "candidates" / "bucket2"
EXPECTED = {
    "parse.rs": "38bb6c7d4df093e6cedbad9651d5ee4377d75fa995106d70dce5c08585cac4db",
    "Parse.lean": "421c58d4695b80d25b3b17eb53d065fa5764185352491f4c1b17d32fff26a7c1",
}
VARIANTS = {
    "round3-speed-bucket16k": 14,
    "round3-speed-bucket8k": 13,
}


def sha(data: bytes) -> str:
    return hashlib.sha256(data).hexdigest()


def generate(check: bool = False) -> dict:
    frozen = {name: (BASE / name).read_bytes() for name in EXPECTED}
    for name, expected in EXPECTED.items():
        assert sha(frozen[name]) == expected, f"bucket2 base drift: {name}"
    source = frozen["parse.rs"].decode("utf-8")
    proof = frozen["Parse.lean"]
    result = {}
    for name, hash_bits in VARIANTS.items():
        table_entries = 1 << hash_bits
        text = source
        begin = text.index("pub fn bucket_insert<")
        end = text.index("pub fn bucket_find<", begin)
        helper = text[begin:end]
        # Only bucket insertion uses the shorter high-bit hash. Ordinary run,
        # run_rest and the tiny planner retain every original constant and table.
        before = " >> (64 - HB)) as usize % H;"
        after = f" >> {64 - hash_bits}) as usize % H;"
        assert helper.count(before) == 1
        helper = helper.replace(before, after)
        text = text[:begin] + helper + text[end:]
        parse_begin = text.index("pub fn parse(")
        parse_end = text.index("// ─", parse_begin)
        dispatch = text[parse_begin:parse_end]
        assert dispatch.count("bucket_run::<HN, WN>") == 3
        dispatch = dispatch.replace("bucket_run::<HN, WN>",
                                    f"bucket_run::<{table_entries}, {table_entries}>")
        text = text[:parse_begin] + dispatch + text[parse_end:]
        # Four substitutions are intentional: one hash slice and three routes.
        source_lines = source.splitlines()
        changed_lines = text.splitlines()
        assert len(source_lines) == len(changed_lines)
        assert sum(a != b for a, b in zip(source_lines, changed_lines)) == 4
        assert re.findall(r"pub const [^\n]+", source) == re.findall(r"pub const [^\n]+", text)
        files = {"parse.rs": text.encode("utf-8"), "Parse.lean": proof}
        manifest = {
            "candidate": name,
            "base": "candidates/bucket2",
            "base_sha256": EXPECTED,
            "sha256": {filename: sha(data) for filename, data in files.items()},
            "hash_bits": hash_bits,
            "entries_per_slot": table_entries,
            "bucket_table_bytes": 2 * table_entries * 4,
            "base_bucket_table_bytes": 2 * 32768 * 4,
            "changed_source_lines": 4,
            "proof_bytes_unchanged": True,
            "scope": "large text/prose/structured-text bucket routes only; fresh gate required",
            "status": {"generation": "VERIFIED", "official_gate": "UNKNOWN", "performance": "UNKNOWN"},
        }
        files["manifest.json"] = (json.dumps(manifest, indent=2, ensure_ascii=False) + "\n").encode("utf-8")
        target = ROOT / "candidates" / name
        if check:
            for filename, data in files.items():
                assert (target / filename).read_bytes() == data, f"generated-file drift: {name}/{filename}"
        else:
            target.mkdir(exist_ok=True)
            for filename, data in files.items():
                (target / filename).write_bytes(data)
        result[name] = manifest
    return result


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--check", action="store_true", help="verify exact reconstruction without writing")
    args = parser.parse_args()
    print(json.dumps(generate(args.check), indent=2, ensure_ascii=False))
