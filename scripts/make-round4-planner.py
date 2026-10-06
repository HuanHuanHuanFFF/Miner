"""Generate two uniform cost-planning experiments from public submission 402.

Only writes candidates/r4-parse-plan*/. The original exact-length portfolio and
the A engine's additional exact-length model selection are statically unreachable.
This is a source audit, not an official extraction, Lean or performance result.
"""
from __future__ import annotations

import argparse
import hashlib
import json
import re
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
BASE = ROOT / "references/round4-public-402"
HASHES = {
    "parse.rs": "0be90fc1b0f8e751012d259cda70a84a160b812dcc134b4c7e96071797166dca",
    "Parse.lean": "e470d3d09d56b275556c36c5892ee68781a594cb7d6237255f009a62e18bce1d",
}
OLD_ENTRY = """pub fn parse(input: &[u8], out: &mut [u32]) -> usize {
    let r = route(input);
    if r < 8 {
        parse_c0(input, out, r)
    } else if r < 16 {
        parse_c1(input, out, r)
    } else {
        parse_c2(input, out, r)
    }
}"""
OLD_PROOF = """  rw [slot.parse]
  apply Std.WP.spec_bind (route_spec input)
  intro r _
  split
  · exact parse_c0_spec input out r hlen
  · split
    · exact parse_c1_spec input out r hlen
    · exact parse_c2_spec input out r hlen"""


def digest(data: bytes) -> str:
    return hashlib.sha256(data).hexdigest()


def replace_once(text: str, old: str, new: str) -> str:
    assert text.count(old) == 1, (old, text.count(old))
    return text.replace(old, new, 1)


def constant(text: str, name: str, old: int, new: int) -> str:
    return replace_once(text, f"pub const {name}: usize = {old};", f"pub const {name}: usize = {new};")


def function_bodies(source: str) -> dict[str, str]:
    # The frozen source has no callbacks or function-pointer dispatch. This
    # conservative direct-call closure includes both sides of conditionals.
    plain = re.sub(r"/\*.*?\*/|//[^\n]*", "", source, flags=re.S)
    result = {}
    for match in re.finditer(r"\bpub fn (\w+)\b[^{}]*\{", plain):
        pos = match.end()
        start, depth = pos, 1
        while depth:
            assert pos < len(plain), match[1]
            depth += (plain[pos] == "{") - (plain[pos] == "}")
            pos += 1
        assert match[1] not in result, match[1]
        result[match[1]] = plain[start:pos - 1]
    assert len(result) == len(re.findall(r"\bfn\s+\w+\s*[<(]", plain)), "unsupported private function or parser shape"
    assert not re.search(r"\bfn\s*\(", plain), "function pointer requires a stronger audit"
    return result


def closure(source: str, entry_call: str, prefix: str) -> list[str]:
    bodies = function_bodies(source)
    assert bodies["parse"].strip() == entry_call
    pending, active = ["parse"], set()
    while pending:
        name = pending.pop()
        if name in active:
            continue
        active.add(name)
        symbols = set(re.findall(r"\b([A-Za-z_]\w*)\s*(?=\(|::<)", bodies[name]))
        pending.extend((symbols & bodies.keys()) - active)
    assert all(name == "parse" or name.startswith(prefix) for name in active), sorted(active)
    assert {"route", "parse_c0", "parse_c1", "parse_c2", "a_p_for"}.isdisjoint(active)
    suspect = []
    for name in active:
        for match in re.finditer(r"\b(?:n|input\.len\(\))\s*==\s*(\d+)", bodies[name]):
            if int(match[1]) >= 4096:
                suspect.append((name, match[0]))
    assert not suspect, suspect
    return sorted(active)


def main() -> None:
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument("--check", action="store_true")
    args = ap.parse_args()
    base = {name: (BASE / name).read_bytes() for name in HASHES}
    for name, sha in HASHES.items():
        assert digest(base[name]) == sha, f"base drift: {name}"
    source = base["parse.rs"].decode().replace("\r\n", "\n")
    proof = base["Parse.lean"].decode().replace("\r\n", "\n")
    provenance = (BASE / "PROVENANCE.json").read_bytes()
    origin = json.loads(provenance)
    policies = {
        "r4-parse-plan-d8": {
            "entry": "d_parse(input, out)",
            "theorem": "ED.parse_spec input out hlen",
            "prefix": "d_",
            "constants": {
                "D_DEPTH": (512, 8), "D_LONG_DEPTH": (64, 4), "D_LDEPTH": (128, 4),
                "D_MDEPTH": (32, 2), "D_INNER_D": (24, 2), "D_INNER_L": (24, 8),
                "D_INNER_MAXL": (24, 8), "D_TRY_ALL": (24, 8),
                "D_SPAN1": (16, 8), "D_SPAN2": (8, 4),
            },
            "mechanism": "One uniform D engine: 32KiB blocks, sparse lazy match alternatives, learned literal/length/distance costs, backward DP and verified emit. Reduce search and short-length relaxation budgets; retain its existing second pass in the first four non-low-entropy blocks.",
        },
        "r4-parse-plan-h2": {
            "entry": "h_parse_mode(input, out, 0)",
            "theorem": "EH.parse_mode_spec input out 0#usize hlen",
            "prefix": "h_",
            "constants": {
                "H_ITERS": (20, 2), "H_BTD": (32, 8), "H_BTDS": (8, 4),
                "H_BTDMC": (24, 8), "H_BTDX": (32, 8),
                "H_CHW": (32, 8), "H_CHWS": (128, 16),
            },
            "mechanism": "One uniform H engine in mode 0: whole-input Pareto match cache, lazy/all-literal warm start, at most two learned-cost DP passes, verified emit. Depth 8 (4 for small inputs), narrowed length relaxation. Content features still set cost/stop parameters; mode 0 performs no restart passes.",
        },
    }
    for name, policy in policies.items():
        text = replace_once(source, OLD_ENTRY,
            "// Round4 uniform entry: the inherited exact-length portfolio is unreachable.\n"
            "pub fn parse(input: &[u8], out: &mut [u32]) -> usize {\n"
            f"    {policy['entry']}\n}}")
        for key, (old, new) in policy["constants"].items():
            text = constant(text, key, old, new)
        active = closure(text, policy["entry"], policy["prefix"])
        lean = replace_once(proof, OLD_PROOF, f"  rw [slot.parse]\n  exact {policy['theorem']}")
        files = {"parse.rs": text.encode(), "Parse.lean": lean.encode()}
        assert all(len(data) <= 524288 for data in files.values())
        metadata = {
            "candidate": name,
            "base_submission_id": "402",
            "base_path": BASE.relative_to(ROOT).as_posix(),
            "base_hashes": HASHES,
            "hashes": {file: digest(data) for file, data in files.items()},
            "bytes": {file: len(data) for file, data in files.items()},
            "source_attribution": {
                "miner_hotkey": origin["official_item"]["hotkey"],
                "source_url": origin["url"],
                "retrieved_at_utc": origin["retrieved_at_utc"],
                "reference_metadata_sha256": digest(provenance),
                "note": "External public source, not an independent algorithm. Original provenance retained unchanged in the reference directory.",
            },
            "entrypoint": policy["entry"] + " for every input",
            "constants": {key: {"old": old, "new": new} for key, (old, new) in policy["constants"].items()},
            "mechanism": policy["mechanism"],
            "active_functions_static": active,
            "routing_audit": "VERIFIED source-only direct-call closure excludes route, parse_c0/c1/c2 and all A-engine functions including hidden exact-length a_p_for; official extraction and deployed behavior unverified.",
            "proof_change": "Only final Submission.parse_spec body replaced by direct existing engine theorem; all engine proof text retained. New constants and parser still require official re-extraction and complete gate.",
            "proof_entry_theorem": policy["theorem"],
            "proof_entry_body": "rw [slot.parse]\nexact " + policy["theorem"],
            "verification": "UNKNOWN: Rust build, extraction, Lean obligation, axiom whitelist, public round trip/performance, private stage2 and admission.",
            "comparison_limit": "Original #402 mixes engines with exact-length routing, so its official point is not a matched same-engine calibration anchor for these uniform candidates.",
        }
        files["manifest.json"] = (json.dumps(metadata, indent=2) + "\n").encode()
        dest = ROOT / "candidates" / name
        if args.check:
            for file, data in files.items():
                assert (dest / file).read_bytes() == data, f"candidate drift: {name}/{file}"
        else:
            dest.mkdir(parents=True, exist_ok=True)
            for file, data in files.items():
                (dest / file).write_bytes(data)
        print(json.dumps({"candidate": name, "hashes": metadata["hashes"], "bytes": metadata["bytes"], "active_function_count": len(active)}))


if __name__ == "__main__":
    main()
