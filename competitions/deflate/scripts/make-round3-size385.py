"""Generate uniform dual-hash compression candidates from public reference 385.

The reference's length-specific routing is bypassed at the public entrypoint.
All inputs take the same row1 engine. This generator never certifies or submits.
"""
from __future__ import annotations

import argparse
import hashlib
import json
import re
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
BASE_SOURCE = "56b92f95a93fd8662c20dd26934fed065f812a685610d09f58d01148cfdb367f"
BASE_PROOF = "db97b9e2c525995a63e31f6b720ff0f234b4acd2a5822663f026848dd0864d62"
OLD_PARSE = """pub fn parse(input:&[u8],out:&mut[u32])->usize{
 if input.len()==28000{return r109_row17(input,out);}
 if input.len()==12000{return r109_row18(input,out);}
 bulk_parse(input,out)
}"""
NEW_PARSE = """// Round3 uniform dual-hash experiment: every input uses the same engine.
// The inherited route/bulk_parse functions are unreachable from this entry.
pub fn parse(input:&[u8],out:&mut[u32])->usize{
 r109_row1(input,out)
}"""


def digest(data: bytes) -> str:
    return hashlib.sha256(data).hexdigest()


def replace_once(text: str, old: str, new: str) -> str:
    assert text.count(old) == 1, (old, text.count(old))
    return text.replace(old, new, 1)


def const(text: str, name: str, value: str) -> str:
    text, count = re.subn(rf"(pub const {name}: \w+ = )[^;]+;", lambda m: m[1] + value + ";", text)
    assert count == 1, name
    return text


def function_bodies(text: str) -> dict[str, str]:
    # This source has direct function calls, no callbacks. Remove comments so
    # braces in inherited explanatory prose do not affect the source audit.
    plain = re.sub(r"/\*.*?\*/|//[^\n]*", "", text, flags=re.S)
    result = {}
    for match in re.finditer(r"\bpub fn (\w+)\b[^{}]*\{", plain):
        pos = match.end()
        start = pos
        depth = 1
        while depth:
            if plain[pos] == "{":
                depth += 1
            elif plain[pos] == "}":
                depth -= 1
            pos += 1
        result[match[1]] = plain[start:pos - 1]
    return result


def active_functions(text: str) -> list[str]:
    bodies = function_bodies(text)
    pending = ["parse"]
    found = set()
    while pending:
        name = pending.pop()
        if name in found:
            continue
        found.add(name)
        for callee in re.findall(r"\b(\w+)\s*(?=\(|::<)", bodies[name]):
            if callee in bodies and callee not in found:
                pending.append(callee)
    assert bodies["parse"].strip() == "r109_row1(input,out)"
    assert {"route", "bulk_parse", "format_id"}.isdisjoint(found)
    assert {n for n in found if n.startswith("r109_row")} == {"r109_row1"}
    assert "o_a_main_part" in found and "o_a_verified" in found
    return sorted(found)


def generate() -> dict[str, tuple[str, dict]]:
    source_bytes = (ROOT / "references/round3-public-385/parse.rs").read_bytes()
    proof = (ROOT / "references/round3-public-385/Parse.lean").read_bytes()
    assert digest(source_bytes) == BASE_SOURCE, "reference source drift"
    assert digest(proof) == BASE_PROOF, "reference proof drift"
    source = replace_once(source_bytes.decode("utf-8"), OLD_PARSE, NEW_PARSE)
    source = replace_once(source,
        "pub fn r109_row1(input:&[u8],out:&mut[u32])->usize{o_a_main_part::<10,256,8,5,32>(input,out,0,0,0)}",
        "pub fn r109_row1(input:&[u8],out:&mut[u32])->usize{o_a_main_part::<258,258,1,63,258>(input,out,0,0,0)}")
    source = const(source, "O_A_LZN", "4")
    three = const(source, "O_A_HM4", "0x4A7C150000000000")
    three = const(three, "O_A_MM4", "16777215")
    three = const(three, "O_A_MINL", "3")
    three = const(three, "O_A_MAX3", "1024")
    descriptions = {
        "round3-size385-dense4": (source, {"short_key_bytes": 4, "minimum_match": 4}),
        "round3-size385-dense3": (three, {"short_key_bytes": 3, "minimum_match": 3, "length3_max_distance": 1024}),
    }
    result = {}
    for name, (text, parameters) in descriptions.items():
        data = text.encode("utf-8")
        assert len(data) <= 524288 and len(proof) <= 524288
        active = active_functions(text)
        metadata = {
            "candidate": name,
            "base": "references/round3-public-385",
            "source_attribution": "Public submission 385; original miner and receipt in references/round3-public-385/PROVENANCE.md",
            "base_source_sha256": BASE_SOURCE,
            "base_proof_sha256": BASE_PROOF,
            "parse_rs_sha256": digest(data),
            "parse_lean_sha256": digest(proof),
            "entrypoint": "parse -> r109_row1 -> o_a_main_part for every input; inherited exact-length router is unreachable",
            "row1_parameters": {"IH": 258, "IT": 258, "TS": 1, "ACC": 63, "LZT": 258},
            "constants": {"O_A_LZN": 4, **parameters},
            "active_functions_static": active,
            "proof_change": "none; copied byte-for-byte, must be checked against fresh official extraction",
            "upstream_revision": "a356bbff18b60c4527fbcc85d5a28ef9c20214e0",
            "status": "UNVERIFIED; no build, gate, timing, admission, or reward claim",
        }
        result[name] = (text, metadata)
    return result


def main() -> None:
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument("--check", action="store_true")
    args = ap.parse_args()
    proof = (ROOT / "references/round3-public-385/Parse.lean").read_bytes()
    for name, (text, metadata) in generate().items():
        files = {
            "parse.rs": text.encode("utf-8"),
            "Parse.lean": proof,
            "manifest.json": (json.dumps(metadata, indent=2) + "\n").encode("utf-8"),
        }
        target = ROOT / "candidates" / name
        if args.check:
            for file, expected in files.items():
                assert (target / file).read_bytes() == expected, (name, file)
        else:
            target.mkdir(exist_ok=True)
            for file, expected in files.items():
                (target / file).write_bytes(expected)
        print(json.dumps({k: v for k, v in metadata.items() if k != "active_functions_static"}))


if __name__ == "__main__":
    main()
