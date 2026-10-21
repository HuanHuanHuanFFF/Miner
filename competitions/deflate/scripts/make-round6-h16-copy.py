"""Generate the final single H16 CPU hypothesis: a guarded copy32 fast path.

Writes only candidates/r6-h16-cpu-copyfast. No compiler, CI, Git or toolchain
installation. The unchanged parent Lean is deliberately NOT_ADAPTED to the new
two-loop extraction until actual official Funs is available. --check is read-only.
"""
from __future__ import annotations

import argparse
import hashlib
import json
import re
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
BASE = ROOT / "candidates/r5-h16-small-proofopt"
DEST = ROOT / "candidates/r6-h16-cpu-copyfast"
LOCKS = {
    "parse.rs": "d9826bc92ba02f49cb6e552ed172a4fb82dc10fa8fb51aacf73e7947ed38a94d",
    "Parse.lean": "d55744de52bb0469768f0bbfd73ffecbabf9899b63e0167469fd7bb79c6293c7",
}
OLD = """pub fn h_copy32(src: &[u32], soff: usize, dst: &mut [u32], doff: usize, m: usize) {
    let mut i = 0usize;
    while i < m {
        h_set(dst, doff.wrapping_add(i), h_get(src, soff.wrapping_add(i)));
        i += 1;
    }
}"""
NEW = """pub fn h_copy32(src: &[u32], soff: usize, dst: &mut [u32], doff: usize, m: usize) {
    if soff <= src.len() && doff <= dst.len()
        && m <= src.len() - soff && m <= dst.len() - doff {
        let mut i = 0usize;
        while i < m {
            dst[doff + i] = src[soff + i];
            i += 1;
        }
        return;
    }
    let mut i = 0usize;
    while i < m {
        h_set(dst, doff.wrapping_add(i), h_get(src, soff.wrapping_add(i)));
        i += 1;
    }
}"""


def sha(data: bytes) -> str:
    return hashlib.sha256(data).hexdigest()


def generate() -> tuple[dict[str, bytes], dict]:
    base = {name: (BASE / name).read_bytes() for name in LOCKS}
    for name, expected in LOCKS.items():
        assert sha(base[name]) == expected, (name, "frozen baseline drift")
    source = base["parse.rs"].decode()
    assert "\r\n" not in source and source.count(OLD) == 1
    modified = source.replace(OLD, NEW, 1)
    assert modified.count(NEW) == 1 and modified.replace(NEW, OLD, 1) == source
    # The fallback includes the exact complete original loop and counter setup.
    fallback = OLD[OLD.index("    let mut i"):OLD.rindex("}")]
    assert NEW.endswith(fallback + "}")
    assert not re.search(r"\b(?:unsafe|extern|copy_from_slice|copy_nonoverlapping)\b", NEW)
    assert not any(x in NEW for x in ("H_ITERS", "H_BTD", "H_GK", "classify"))
    files = {"parse.rs": modified.encode(), "Parse.lean": base["Parse.lean"]}
    assert all(len(data) < 524288 for data in files.values())
    audit = {
        "parent": {"path": BASE.relative_to(ROOT).as_posix(), "hashes": LOCKS},
        "changed_function": "h_copy32",
        "parent_line": source[:source.index(OLD)].count("\n") + 1,
        "old_declaration_sha256": sha(OLD.encode()),
        "new_declaration_sha256": sha(NEW.encode()),
        "all_other_Rust_bytes": "VERIFIED reverse replacement restores the entire baseline source byte-for-byte",
        "fallback_loop": {"sha256": sha(fallback.encode()), "preservation": "VERIFIED exact original wrapping/get/set loop, including counter initialization and increment"},
        "valid_range_reasoning": "If soff<=src.length, doff<=dst.length and m<=both remaining lengths, then every 0<=i<m has soff+i<src.length and doff+i<dst.length; sums cannot wrap and ordinary indexing has the same read/write semantics as original guarded helpers",
        "invalid_range_reasoning": "Short-circuit guard evaluates subtraction only after offset<=length. A false guard mutates nothing and reaches the byte-identical original loop, preserving wrapping indices, out-of-range zero reads and skipped writes",
        "formal_reasoning_status": "INFERRED source-level reasoning, not a new Lean proof; platform widths and actual extracted branch/loop names must be validated",
        "unsafe_or_external_copy_added": False,
        "proof": {"sha256": LOCKS["Parse.lean"], "status": "NOT_ADAPTED", "reason": "New guarded direct-index loop plus original fallback may introduce h_copy32_loop0/loop1; inherited copy32_loop_spec/copy32_spec do not certify this new extraction"},
        "assembly_evidence": {
            "run_id": "37594267200",
            "source": "evidence/round6/37594267200/cpu-screen/screen/cpu/h16-base-assembly.txt",
            "fully_covered_symbol": "candidate::parse::parse at 0x177f0, size 0x5197",
            "first_plan_copy": "after h_eval_mode call at 0x1a9f8, scalar copy at 0x1aa40-0x1aad4",
            "per_element_checks": ["source cmp/branch at 0x1aa50/0x1aa55", "destination cmp/branch at 0x1aa62/0x1aa65", "next-element source cmp/branch at 0x1aa6d/0x1aa72", "next-element destination cmp/branch at 0x1aa80/0x1aa83"],
            "observed_loads": ["0x1aa5f", "0x1aa7c"],
            "observed_stores": ["0x1aa95", "0x1aaaa"],
            "interpretation": "VERIFIED scalar two-element unroll with repeated src/dst guards; no memcpy/memmove/rep-movs call in the complete parse symbol. Location-to-source copy association is INFERRED from immediately preceding h_walk/h_eval_mode and the guarded best-cost branch",
        },
        "diagnostic": "Measure unchanged public/finite token outputs and baseline/shadow paired total time; inspect whether only legal-range copy becomes vectorized/memcpy or fewer-guard scalar code. Copy time fraction and realized gain remain UNKNOWN",
    }
    manifest = {
        "candidate": DEST.name,
        "parent": audit["parent"],
        "hashes": {name: sha(data) for name, data in files.items()},
        "bytes": {name: len(data) for name, data in files.items()},
        "mechanism": "Single h_copy32 legal-range fast path: check both offset/remaining-length conditions once, use ordinary indexed copy loop; retain exact original guarded wrapping fallback for every invalid range",
        "expected_equivalent": True,
        "equivalence_reference": BASE.name,
        "expected_equivalence_scope": "INFERRED valid-range arithmetic plus byte-preserved fallback; finite execution and adapted formal proof required",
        "proof_status": "NOT_ADAPTED",
        "proof_scope": "Frozen Lean is carried for provenance only until actual Funs and new copy32 loop specs are supplied; no gate acceptance claim",
        "proof_audit": "copy-audit.json",
        "baseline_gate": {"run_id": "37584216832", "commit": "3d9494eb4370e20e8c76ed243a2093d6c8b2ec60", "scope": "Exact baseline only"},
        "attribution": "H16 small-only CPU derivative of external public submissions 299 and 402; original provenance remains in references/round4-public-299 and references/round4-public-402",
        "verification": "VERIFIED static single-function delta/fallback preservation/generation only. New Rust build, finite/public output identity, realized copy optimization, adapted Lean/axioms, complete gate and total-time gain UNKNOWN",
        "scope": "Last extra CPU hypothesis; no routing, budgets, model, encoder, official gate or pins changed; no stage2/admission/reward inference",
    }
    files["copy-audit.json"] = (json.dumps(audit, indent=2) + "\n").encode()
    files["manifest.json"] = (json.dumps(manifest, indent=2) + "\n").encode()
    return files, manifest


def main() -> None:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--check", action="store_true", help="compare only; no writes")
    args = parser.parse_args()
    files, manifest = generate()
    if args.check:
        for name, data in files.items():
            assert (DEST / name).read_bytes() == data, (name, "candidate drift")
    else:
        DEST.mkdir(parents=True, exist_ok=True)
        for name, data in files.items():
            path = DEST / name
            if not path.exists() or path.read_bytes() != data:
                path.write_bytes(data)
    print(json.dumps({"candidate": DEST.name, "hashes": manifest["hashes"], "bytes": manifest["bytes"], "proof_status": "NOT_ADAPTED", "check_only": args.check}))


if __name__ == "__main__":
    main()
