"""Correct unroll4's tail-loop proof against the real Round 9 extraction.

Preserves the original r9-block-unroll4 directory and all Rust bytes. The
corrected proof still requires a fresh official obligation and axiom gate.
"""

from pathlib import Path
import argparse
import hashlib
import json


ROOT = Path(__file__).resolve().parents[1]
BASE = ROOT / "candidates/r9-block-unroll4"
EXTRACT = ROOT / "evidence/round9/37660750561/block-a/extraction/r9-block-unroll4/Funs.lean"
NAME = "r9-block-unroll4-proof"
EXPECTED_EXTRACT_SHA = "e1444e6bfc52d5355c952f9fc0cc6bbb779e587ecf8d06fcf05544fe5a8a433c"


def sha(data: bytes) -> str:
    return hashlib.sha256(data).hexdigest()


def generate() -> dict[str, bytes]:
    parent = json.loads((BASE / "manifest.json").read_text())
    raw = {n: (BASE / n).read_bytes() for n in ("parse.rs", "Parse.lean")}
    assert all(sha(raw[n]) == parent["hashes"][n] for n in raw)
    extracted = EXTRACT.read_bytes()
    assert sha(extracted) == EXPECTED_EXTRACT_SHA
    normalized = " ".join(extracted.decode().split())
    assert "(fun (l1, bv1) => d_best_len_four_loop1.body lc ring p e l1 bv1) (l, bv)" in normalized
    assert "d_best_len_four_loop1 lc ring p e l1 bv" in normalized
    proof = raw["Parse.lean"].decode()
    start = proof.index("@[local step]\ntheorem d_best_len_four_loop1_spec")
    end = proof.index("@[local step]\ntheorem d_best_len_four_spec", start)
    old = proof[start:end]
    changes = {
        "(lc ring p e) (bv : Std.U64) (l : Std.Usize)": "(lc ring p e) (l : Std.Usize) (bv : Std.U64)",
        "slot.d_best_len_four_loop1 lc ring p e bv l": "slot.d_best_len_four_loop1 lc ring p e l bv",
        "(measure := fun (_, l') => e.val - l'.val)": "(measure := fun (l', _) => e.val - l'.val)",
        "rintro ⟨bv', l'⟩": "rintro ⟨l', bv'⟩",
    }
    patched = old
    for before, after in changes.items():
        assert patched.count(before) == 1
        patched = patched.replace(before, after, 1)
    lean = proof[:start] + patched + proof[end:]
    assert lean.replace(patched, old, 1) == proof
    files = {"parse.rs": raw["parse.rs"], "Parse.lean": lean.encode()}
    assert files["parse.rs"] == raw["parse.rs"]
    assert all(len(b) <= 524288 for b in files.values())
    manifest = {
        **parent,
        "candidate": NAME,
        "parent": "candidates/r9-block-unroll4",
        "parent_hashes": parent["hashes"],
        "hashes": {n: sha(b) for n, b in files.items()},
        "bytes": {n: len(b) for n, b in files.items()},
        "proof_change": "Correct d_best_len_four_loop1_spec call/binder order and measure/pattern from guessed (bv,l) to extracted (l,bv); all other proof text preserved",
        "extraction": {
            "run_id": "37660750561",
            "batch": "block-a",
            "path": str(EXTRACT.relative_to(ROOT)).replace("\\", "/"),
            "funs_sha256": EXPECTED_EXTRACT_SHA,
        },
        "proof_status": "UNKNOWN: matches the observed tail-loop interface; corrected proof has not been compiled or passed original Lean obligation/axiom gate",
        "audit": "Original unroll4 Rust bytes preserved; reverse only the tail-loop proof lemma edit restores original proof; original candidate directory unchanged",
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
    print(json.dumps({"candidate": NAME, "hashes": json.loads(files["manifest.json"])["hashes"], "proof_status": "CORRECTED_INTERFACE_NOT_LEAN_VERIFIED"}))


if __name__ == "__main__":
    main()
