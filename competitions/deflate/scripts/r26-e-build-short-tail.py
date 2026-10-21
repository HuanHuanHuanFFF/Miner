"""Controlled E2 combination: exact C2 fold guard plus exact E1 short same.

Only static preparation is performed. Combination performance is not inferred
by adding component gains, and component gates do not validate this new pair.
"""
from pathlib import Path
import datetime
import hashlib
import importlib
import json
import re

ROOT = Path(__file__).resolve().parents[1]
OUT = ROOT / "evidence/round26/extension90m/route-e"
EDIT = importlib.import_module("r26-a-rep-shadow")
C2 = ROOT / "candidates/r26-c-658-fold-tail-proof1"
E1 = ROOT / "candidates/r26-e-658-short-same-proof2"
NAME = "r26-e-658-short-tail"


def sha(raw):
    return hashlib.sha256(raw).hexdigest()


def dump(path, obj):
    path.write_bytes((json.dumps(obj, indent=2, ensure_ascii=False)+"\n").encode())


def read_pair(path, expected):
    raw = {name: (path / name).read_bytes() for name in expected}
    assert all(sha(raw[name]) == expected[name] for name in expected)
    return raw


def fn(text, name):
    start = text.index("pub fn "+name)
    end = text.index("{", start)+1
    depth = 1
    while depth:
        depth += (text[end] == "{")-(text[end] == "}")
        end += 1
    return text[start:end]


def back(text):
    start = text.index("theorem back_loop_inv {W : Std.Usize}")
    end = text.index("@[local step]\ntheorem back_loop_spec", start)
    return start, end, text[start:end]


def main():
    c2_hashes = {"parse.rs": "305f6089dc6f4210e9c6041e69f16e1727cba22b191e8f4a8c9c427380227d24",
                 "Parse.lean": "c3e5a4abef255100412497069c1971df4f7d636064f8f3296e8ca0c6432229b9"}
    e1_hashes = {"parse.rs": "bc1b3fec788a0d58d220efb84505e26f83a7045129c724f43095704c6097adc0",
                 "Parse.lean": "b0d67036601c00bd7cb9831f26693e70d08ab9d529a0b2c5ac5a7562b60c8275"}
    c2 = read_pair(C2, c2_hashes)
    e1 = read_pair(E1, e1_hashes)
    verified = json.loads((C2 / "VERIFICATION.json").read_bytes())
    assert verified["status"] == "VERIFIED_EXACT_ORIGINAL_PUBLIC_GATE_PASSED"
    assert verified["files"] == c2_hashes
    rust_text = EDIT.edit_fn(c2["parse.rs"].decode(), "u118_same(",
                            lambda old: fn(e1["parse.rs"].decode(), "u118_same("))
    rust = rust_text.encode()
    old_guard = "l + w <= 258 && w <= p && d <= p - w && u118_same(input, p - w - d, p - w, w) == 1"
    new_guard = "l + w <= 258 && w <= p && d <= p - w && input[p - 1] == input[p - 1 - d] && u118_same(input, p - w - d, p - w, w) == 1"
    assert rust_text.count(new_guard) == 1 and rust_text.count(old_guard) == 0
    # The inverse fold patch recovers exact E1, proving no third Rust edit.
    assert sha(rust_text.replace(new_guard, old_guard, 1).encode()) == e1_hashes["parse.rs"]
    lean_text = e1["Parse.lean"].decode()
    a, b, e1back = back(lean_text)
    _, _, c2back = back(c2["Parse.lean"].decode())
    baseline = (ROOT / "references/round26-public-658/Parse.lean").read_bytes().decode()
    assert e1back == back(baseline)[2]
    lean = (lean_text[:a] + c2back + lean_text[b:]).encode()
    assert len(lean) <= 524288
    assert not re.search(rb"(?m)^\s*(axiom\s|.*\b(sorry|admit)\b)", lean)
    hashes = {"parse.rs": sha(rust), "Parse.lean": sha(lean)}
    starts = {"c2": {"path": C2.relative_to(ROOT).as_posix(), "hashes": c2_hashes,
                      "verification_sha256": sha((C2 / "VERIFICATION.json").read_bytes())},
              "e1": {"path": E1.relative_to(ROOT).as_posix(), "hashes": e1_hashes,
                      "proof_status": "UNCOMPILED_ORIGINAL_GATE_NOT_RUN_AT_COMBINATION_PREPARATION"}}
    metadata = json.loads((E1 / "manifest.json").read_bytes())
    metadata.update({"hashes": hashes, "combination_parents": starts,
        "mechanism": "Controlled combination of C2 necessary final-byte filtering in U118 backward whole-token merge and E1 direct len1..8 word-prefix equality. All remaining source is exactE1; inverse C2guard patch recovers exactE1 Rust hash.",
        "difference": "C2changes howmany originalsame calls areentered; E1changes shortsame control flow. Their netcost andscore are not assumedadditive; one actualoriginal-protocol comparison must decide retention.",
        "equivalence": "INFERRED from two component necessaryconditions/prefixequality, pending actual combinednative/extraction/gate. No allinputexecution claim.",
        "guard_safety": "Original C2guard order and E1 full-load/shiftguards retained exactly; zero/near-tail/longfallback unchanged.",
        "proof_status": "UNCOMPILED_ORIGINAL_GATE_NOT_RUN",
        "proof_origin": starts,
        "proof_adaptation": "Exact E1proof2 completeLean plus replacement of its unchanged BackInvloop theorem by exact C2gated theorem (five added lines). Componentproof acceptance doesnotvalidate thecombinedpair.",
        "performance": "UNKNOWN until actual combinedoriginal-protocol timing. Do notadd componentgains or discardwithout themeasurement.",
        "confirmation_status": "No combinedpair postfreezeindependent confirmation.",
        "prepared_utc": datetime.datetime.now(datetime.timezone.utc).isoformat(),
        "formal_submission_sent": False})
    for name in [NAME, NAME+"-proof1"]:
        target = ROOT / "candidates" / name
        assert not target.exists(), target
        target.mkdir()
        (target / "parse.rs").write_bytes(rust)
        (target / "Parse.lean").write_bytes(lean)
        metadata["candidate"] = name
        metadata["implementation_parent"] = "references/round26-public-658"
        dump(target / "manifest.json", metadata)
    entry = {"name": NAME+"-proof1", "path": "candidates/"+NAME+"-proof1",
        "hashes": hashes, "status": "UNCOMPILED_ORIGINAL_GATE_NOT_RUN",
        "rust_bytes": len(rust), "lean_bytes": len(lean), "lean_spare_bytes": 524288-len(lean),
        "control": False, "anchor": "public658", "comparison_baseline": "public658",
        "native_decode_reference": "public658", "expected_equivalent_to": "public658"}
    dump(OUT / "e2-entry.json", entry)
    dump(OUT / "e2-static-preparation.json", {"status": "STATIC_COMBINATION_ONLY_UNCOMPILED",
        "hashes": hashes, "parents": starts, "same_function_exact_e1": True,
        "inverse_c2_guard_recovers_exact_e1": True, "backloop_exact_gated_c2": True,
        "main_and_proof1_identical_pair": True,
        "gate": "NOT_RUN", "native": "NOT_RUN", "original_protocol": "NOT_RUN"})
    print(json.dumps(entry, indent=2))


if __name__ == "__main__":
    main()
