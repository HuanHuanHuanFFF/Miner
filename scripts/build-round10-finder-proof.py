"""Assemble unverified finder proof ports against the actual R10 extraction.

Only independent *-proof directories are written; measured first-batch bytes
are preserved. This source-interface audit is not a Lean acceptance claim.
"""
from __future__ import annotations
import argparse
import hashlib
import json
from pathlib import Path
import re

ROOT = Path(__file__).resolve().parents[1]
PARENT = ROOT / "candidates/r9-block-scalar/Parse.lean"
EXTRACT = ROOT / "evidence/round10/37679261323/explore-a/extraction"


def sha(b: bytes) -> str:
    return hashlib.sha256(b).hexdigest()


def once(s: str, old: str, new: str) -> str:
    if s.count(old) != 1:
        raise ValueError(f"Expected one proof anchor ({s.count(old)}): {old[:120]}")
    return s.replace(old, new, 1)


def tuple_insert(s: str, prefix: str, index: int, value: str) -> str:
    start = s.index(prefix) + len(prefix)
    end = s.index(")", start)
    parts = [p.strip() for p in s[start:end].split(",")]
    parts.insert(index, value)
    return s[:start] + ", ".join(parts) + s[end:]


def port(source: str, cache_type: str) -> tuple[str, str]:
    start = source.index("@[local step]\ntheorem d_parse_loop_spec")
    end = source.index("@[local step]\ntheorem d_plan_k_loop_spec", start)
    region = source[start:end]
    original = region
    region = once(region, "(head7 : Array Std.U32 65536#usize) (prev7 pa tb)",
        f"(head7 : Array Std.U32 65536#usize) (prev7) (r10_cache : Array Std.{cache_type} 65536#usize) (pa tb)")
    region = region.replace("head3 head4 prev4 head7 prev7 pa tb", "head3 head4 prev4 head7 prev7 r10_cache pa tb")
    region = region.replace("clear plan rs head3 head4 prev4 head7 prev7 pa tb", "clear plan rs head3 head4 prev4 head7 prev7 r10_cache pa tb")
    region = tuple_insert(region, "(measure := fun (", 7, "_")
    region = tuple_insert(region, "(inv := fun (", 7, "_")
    region = once(region, "rintro ⟨plan', rs', h3', h4', p4', h7', p7', pa',", "rintro ⟨plan', rs', h3', h4', p4', h7', p7', cache', pa',")
    before = "    iterate 5 refine d3_unc ?_\n    refine d3_rem (b := 8192)"
    after = """    iterate 5 refine d3_unc ?_
    refine d3_bind (r10_cache_store_spec cache' b8 i') ?_
    rintro ⟨r10_old, r10_cache1⟩ _
    refine d3_unc ?_
    refine d3_rem (b := 8192)"""
    region = once(region, before, after)
    # Two branch-state annotations carry the cache immediately after prev7.
    pattern = r"Array Std\.U32 32768#usize ×(\s+)Array Std\.U64 8192#usize"
    region, count = re.subn(pattern, rf"Array Std.U32 32768#usize ×\1Array Std.{cache_type} 65536#usize × Array Std.U64 8192#usize", region)
    if count != 2:
        raise ValueError(f"Expected two branch tuple cache type insertions, got {count}")
    region = once(region, "| (_, _, g3, g4, _, g7, _, _, _, _, _, s1,", "| (_, _, g3, g4, _, g7, _, _, _, _, _, _, s1,")
    region = once(region, "| (_, g3, g4, _, g7, _, _, _, _, _, s1,", "| (_, g3, g4, _, g7, _, _, _, _, _, _, s1,")
    # Bind the supplement after continuation. Later code follows extracted names.
    boundary = "        refine d3_bind (d_record_spec"
    pos = region.index(boundary)
    prefix, suffix = region[:pos], region[pos:]
    suffix = re.sub(r"\bnc3\b", "nc4", suffix)
    suffix = re.sub(r"\bbest3\b", "best4", suffix)
    suffix = re.sub(r"\bcands6\b", "cands7", suffix)
    inserted = """        refine d3_bind (r10_supplement_spec _ _ _ _ _ _ _ _ hcap1 hic hs8 hb4) ?_
        rintro ⟨⟨nc4, best4⟩, cands7⟩ ⟨hmore1, hmore2⟩
        have hb3 : 2 ≤ best4.val := Nat.le_trans hb3 hmore1
        have hb4 : best4.val ≤ cap1.val := hmore2
        iterate 2 refine d3_unc ?_

"""
    region = prefix + inserted + suffix
    region = once(region,
        "refine d3_bind (insert_range_spec _ _ _ _ _ _ _ _ _ «end».val",
        "refine d3_bind (r10_insert_range_spec _ _ _ _ _ _ r10_cache1 _ _ _ «end».val")
    region = once(region,
        "rintro ⟨head33, head43, prev43, head73, prev73⟩ ⟨hr3, hr4, hr7⟩\n            iterate 4",
        "rintro ⟨head33, head43, prev43, head73, prev73, r10_cache3⟩ ⟨hr3, hr4, hr7⟩\n            iterate 5")
    region = once(region, "rintro ⟨v, a, a1, a2, a3, a4, a5, a6, a7, a8, i21, i22, i23⟩", "rintro ⟨v, a, a1, a2, a3, a4, a5, a6, a7, a8, a9, i21, i22, i23⟩")
    region = once(region, "iterate 12 refine d3_unc ?_", "iterate 13 refine d3_unc ?_")
    region = once(region, "rintro ⟨plan1, rs1, head32, head42, prev42, head72, prev72, pa3,", "rintro ⟨plan1, rs1, head32, head42, prev42, head72, prev72, r10_cache2, pa3,")
    region = once(region, "iterate 21 refine d3_unc ?_", "iterate 22 refine d3_unc ?_")
    # The loop's done value is unchanged; no cache invariant is introduced.
    if region.count("r10_cache_store_spec") != 1 or region.count("r10_supplement_spec") != 1 or region.count("r10_insert_range_spec") != 1:
        raise ValueError("D proof helper binding audit failed")
    return source[:start] + region + source[end:], original


def generate(suffix: str) -> dict[str, bytes]:
    name = f"r10-finder-{suffix}"
    base = ROOT / "candidates" / name
    target = ROOT / "candidates" / (name + "-proof")
    original = PARENT.read_bytes()
    if sha(original) != "aa21da6f74e81314297df07beecbfc98b15c848354437674bdb9347d8632f0af":
        raise ValueError("Scalar proof parent changed")
    cache_type = "U64" if suffix == "tag4" else "U32"
    funs_raw = (EXTRACT / name / "Funs.lean").read_bytes()
    funs = funs_raw.decode("utf-8")
    # Checked against actual extraction, including returned and carried state.
    if f"(cache : Array Std.{cache_type} 65536#usize)" not in funs:
        raise ValueError("Extracted cache type differs")
    if "let ((nc4, best4), cands7) ←" not in funs or "prev71, r10_cache1, pa1" not in funs:
        raise ValueError("Extracted supplemental/state tuple interface differs")
    helpers = (target / "helper-draft.lean").read_text(encoding="utf-8")
    helpers = helpers[helpers.index("@[local step]"):]
    changed, old_region = port(original.decode("utf-8"), cache_type)
    marker = "@[local step]\ntheorem d_parse_loop_spec"
    changed = once(changed, marker, helpers + "\n\n" + marker)
    source = (base / "parse.rs").read_bytes()
    files = {"parse.rs": source, "Parse.lean": changed.encode("utf-8")}
    if not all(len(value) <= 524288 for value in files.values()):
        raise ValueError("Proof port file exceeds official size boundary")
    manifest = json.loads((base / "manifest.json").read_text(encoding="utf-8"))
    manifest.update(candidate=name + "-proof", parent="candidates/" + name,
        parent_hashes=manifest["hashes"], hashes={key: sha(value) for key, value in files.items()},
        bytes={key: len(value) for key, value in files.items()},
        proof_status="UNVERIFIED_INTERFACE_PORT: helper totality and D loop cache bridges assembled against accepted actual extraction; native Lean compilation/original obligation/allowed axioms/full round trip NOT_RUN",
        extraction_interface={"run_id": "37679261323", "path": str((EXTRACT / name).relative_to(ROOT)).replace("\\", "/"), "Funs.lean_sha256": sha(funs_raw)},
        proof_audit="Only four new helper specifications plus original d_parse_loop_spec/d_parse_spec region change; suffix outside that region, including final parse validity theorem, remains exact scalar parent bytes. Rust remains exact measured candidate.")
    files["manifest.json"] = (json.dumps(manifest, ensure_ascii=False, indent=2) + "\n").encode("utf-8")
    return files


def main() -> None:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--check", action="store_true")
    parser.add_argument("--variant", choices=("hash5", "tag4"), action="append")
    args = parser.parse_args()
    for suffix in args.variant or ("hash5", "tag4"):
        files = generate(suffix)
        target = ROOT / "candidates" / f"r10-finder-{suffix}-proof"
        if args.check:
            if not all((target / file).read_bytes() == value for file, value in files.items()):
                raise ValueError("Proof draft reproducibility failed")
        else:
            target.mkdir(exist_ok=True)
            for file, value in files.items():
                (target / file).write_bytes(value)
        print(json.dumps({"candidate": target.name, "hashes": json.loads(files["manifest.json"])["hashes"], "proof_status": "UNVERIFIED_INTERFACE_PORT"}))


if __name__ == "__main__":
    main()
