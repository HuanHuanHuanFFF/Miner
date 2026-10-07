"""Restore original DP model settings for its migrated D routes, keeping flen16.

This is one precise migration-coupling experiment, not full first-plan recovery
and not a parameter sweep. Native D rows retain their old fixed model settings.
"""
from pathlib import Path
import argparse
import hashlib
import json
import re

ROOT = Path(__file__).resolve().parents[1]
BASE = ROOT / "candidates/r10-record-nonempty"
PUBLIC = ROOT / "references/round7-public-361"
NAME = "r10-forward-routecfg"
ROUTES = {5: (5, 0), 6: (5, 0), 10: (6, 2), 11: (7, 3), 12: (8, 4), 13: (9, 5), 15: (10, 6)}


def sha(data):
    return hashlib.sha256(data).hexdigest()


def once(text, old, new):
    assert text.count(old) == 1, old
    return text.replace(old, new, 1)


def table(source, name, width):
    pattern = r"pub const " + name + r": \[\[usize; " + str(width) + r"\]; 16\] = \[\n(.*?)\n\];"
    match = re.search(pattern, source, re.S)
    assert match, name
    rows = [[int(x.strip()) for x in row.split(",")] for row in re.findall(r"\[([0-9, ]+)\]", match.group(1))]
    assert len(rows) == 16 and all(len(row) == width for row in rows)
    return rows


def generate():
    raw = {n: (BASE / n).read_bytes() for n in ("parse.rs", "Parse.lean")}
    parent = json.loads((BASE / "manifest.json").read_text())
    assert all(sha(data) == parent["hashes"][n] for n, data in raw.items())
    gate = json.loads((BASE / "VERIFICATION.json").read_text())
    assert gate["official_accepted"] and gate["files"] == parent["hashes"]
    public_raw = (PUBLIC / "parse.rs").read_bytes()
    provenance = json.loads((PUBLIC / "PROVENANCE.json").read_text())
    assert sha(public_raw) == provenance["hashes"]["parse.rs"]
    original = raw["parse.rs"].decode()
    for declaration in ("pub const KB7: u32 = 7;", "pub const UPD: usize = 2048;",
                        "pub const HALF_AT: u32 = 10000;", "pub const TMAX: usize = 64;",
                        "pub const BTRUNC: usize = 1;", "pub const LZ2MAX: usize = 258;"):
        assert original.count(declaration) == 1, declaration
    dp = table(public_raw.decode(), "DP_KNOBS", 11)
    assert table(original, "DP_KNOBS", 11) == dp
    d = table(original, "D_KNOBS", 17)
    classes = table(original, "CLASS_TAB", 2)
    old_classes = table(public_raw.decode(), "CLASS_TAB", 2)
    models = [[7, 2048, 10000] for _ in range(16)]
    rows = []
    for cls, (drow, dprow) in ROUTES.items():
        assert classes[cls] == [2, drow] and old_classes[cls] == [1, dprow]
        assert d[drow][:6] == dp[dprow][:6]
        assert dp[dprow][6] == 0 and dp[dprow][10] == 64
        assert d[drow][8] == 16 and d[drow][10] == 258 and d[drow][12] == 100
        assert d[drow][13] == d[drow][14] == d[drow][3] and d[drow][15] == 258
        models[drow] = dp[dprow][7:10]
        rows.append({"class": cls, "D_row": drow, "original_DP_row": dprow,
                     "before": [7, 2048, 10000], "after": models[drow],
                     "model_changes": models[drow] != [7, 2048, 10000], "D_flen_retained": 16})
    assert [row["class"] for row in rows if row["model_changes"]] == [5, 6, 10, 11]
    model_table = """
/// Per-D-row [long-key bytes, price-update interval, count-halving threshold].
/// Migrated DP rows recover their original model settings; native D is unchanged.
/// The D first pass still uses its original sparse flen, so this is not full DP recovery.
pub const D_MODEL: [[usize; 3]; 16] = [
""" + "\n".join("    [" + ", ".join(map(str, row)) + "]," for row in models) + "\n];\n"
    edits = []
    marker = "pub const D_NK: usize = 16;\n"
    edits.append((marker, marker + model_table))
    edits.append(("d_plan_k(input, out, &D_KNOBS[dk % D_NK])",
                  "d_plan_k(input, out, &D_KNOBS[dk % D_NK], &D_MODEL[dk % D_NK])"))
    a = original.index("pub fn d_parse(")
    b = original.index("// ── glue ──", a)
    old_parse = original[a:b]
    new_parse = once(old_parse, "nice: usize) {", "nice: usize, kb7: usize, upd: usize, half: usize) {")
    new_parse = once(new_parse, "    let sh7 = 64 - 8 * KB7;", "    let sh7 = dp_sh7(kb7);\n    let updn = dp_upd(upd);\n    let halfn = dp_half(half);")
    new_parse = once(new_parse, "    let mut next_upd = UPD;", "    let mut next_upd = updn;")
    new_parse = once(new_parse, "            next_upd = i + UPD;", "            next_upd = i + updn;")
    new_parse = once(new_parse, "            update_costs(&mut lf, &mut df, &lsym, &mut litc, &mut lc, &mut dcc, huff);",
                     "            update_costs_h(&mut lf, &mut df, &lsym, &mut litc, &mut lc, &mut dcc, huff, halfn);")
    edits.append((old_parse, new_parse))
    edits.append(("pub fn d_plan_k(input: &[u8], out: &mut [u32], k: &[usize; 17]) -> Vec<u32> {",
                  "pub fn d_plan_k(input: &[u8], out: &mut [u32], k: &[usize; 17], model: &[usize; 3]) -> Vec<u32> {"))
    call = "    d_parse(input, &mut plan, &mut rs, k[0], k[1], k[2], k[3], k[4], k[5], k[8], k[9], k[10], k[11], k[12], k[13], k[14], k[15]);"
    edits.append((call, call.removesuffix(");") + ", model[0], model[1], model[2]);"))
    source = original
    for before, after in edits:
        source = once(source, before, after)
    restored = source
    for before, after in reversed(edits):
        restored = once(restored, after, before)
    assert restored == original
    assert table(source, "D_KNOBS", 17) == d
    assert table(source, "CLASS_TAB", 2) == classes
    files = {"parse.rs": source.encode(), "Parse.lean": raw["Parse.lean"]}
    manifest = {
        "candidate": NAME, "parent": "candidates/r10-record-nonempty", "base_submission_id": "361",
        "parent_hashes": parent["hashes"], "hashes": {n: sha(data) for n, data in files.items()},
        "bytes": {n: len(data) for n, data in files.items()}, "attribution": parent["attribution"],
        "verified_parent": "candidates/r10-record-nonempty/VERIFICATION.json",
        "mechanism": "Restore original DP long-key/update/halving settings to its migrated D content rows via one D_MODEL table. Retain D's sparse flen16 first pass and single backward refinement.",
        "model_columns": ["kb7", "upd", "half"], "route_models": rows,
        "native_D": "Rows0,1,3,4 retain [7,2048,10000]; other unassigned D rows retain the same defaults.",
        "important_limit": "Not an exact reconstruction of the original DP first plan: D still uses sparse length endpoints above flen16, direct insertion and plain D walk instead of the DP pipeline and tail-word walk.",
        "same_mathematical_settings": "First six search knobs, huff0, tmax64 on fback100, BTRUNC1, lz2max258, and equal D long depths at normal/lazy/end nodes already matched the original DP profiles.",
        "bounds": "Reuse original dp_sh7, dp_upd and dp_half clamps. updn<=1048576; halfn fits u32; key shifts remain in the original safe 0..56 range. No new evolving loop state is required.",
        "audit": "Five reversible regions: one constant model table, D wrapper/model plumbing, and D model initialization/update calls. D_KNOBS/CLASS_TAB/record optimization/search code/backward planning/emitters are unchanged; costcache is not combined.",
        "equivalence_status": "Final tokens may change for classes5,6,10,11; other route model settings are unchanged. No all-parser token equivalence or original-DP first-plan identity claim.",
        "proof_status": "UNADAPTED_PARENT_ONLY: D parser/glue signatures and frozen loop parameters require fresh extraction and bridge to original obligation; copied record proof does not validate the new code.",
        "performance_status": "UNKNOWN: exact old model settings can improve or worsen this sparse-D/refinement combination. Compare paired axes and current projection against record, scalar and public361 before any full gate.",
    }
    assert all(len(data) <= 524288 for data in files.values())
    files["manifest.json"] = (json.dumps(manifest, indent=2) + "\n").encode()
    audit = {"status": "VERIFIED_SOURCE_MAPPING_ONLY", "parent_source_sha256": parent["hashes"]["parse.rs"],
             "public361_source_sha256": sha(public_raw), "models": models, "routes": rows,
             "D_KNOBS_unchanged": True, "CLASS_TAB_unchanged": True,
             "source_reverse_exact": True, "passes_added": 0, "flen258_variant": False,
             "remaining_first_pass_differences": ["DP rc_seq tries every length; D relax_cands uses nextl from flen16", "DP uses pipelined head reads; D directly inserts", "DP long chain uses tail-word rejection; D plain walk retains nice258"]}
    files["source-audit.json"] = (json.dumps(audit, indent=2) + "\n").encode()
    return files


def boundary_model():
    vals = [0, 1, 2, 7, 8, 9, 63, 64, 255, 258, 2048, 4096, 8192, 8000, 10000,
            1048575, 1048576, 1048577, (1 << 32) - 1, 1 << 32, (1 << 64) - 1]
    checks = []
    for value in vals:
        shift = 0 if value >= 8 else 56 if value == 0 else 64 - 8 * value
        update = min(value, 1048576)
        half = min(value, (1 << 32) - 1)
        assert 0 <= shift <= 56 and shift % 8 == 0
        assert 0 <= update <= 1048576 and 0 <= half <= (1 << 32) - 1
        checks.append({"raw": value, "key_shift": shift, "update": update, "half_u32": half})
    for bits in (32, 64):
        maximum = (1 << bits) - 1
        max_n = maximum // 2
        assert max_n + 1048576 <= maximum
    return {"status": "VERIFIED_FINITE_PARAMETER_MODEL", "cases": checks,
            "scope": "Clamp boundary arithmetic and 32/64-bit maximum guarded input + largest update; not Rust execution or a Lean proof.",
            "source_sha256": json.loads(generate()["manifest.json"])["hashes"]["parse.rs"]}


def main():
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument("--check", action="store_true")
    ap.add_argument("--model-check", action="store_true")
    args = ap.parse_args()
    files = generate()
    dest = ROOT / "candidates" / NAME
    if args.check:
        assert all((dest / name).read_bytes() == data for name, data in files.items())
    else:
        dest.mkdir(parents=True, exist_ok=True)
        for name, data in files.items():
            if (dest / name).exists() and (dest / name).read_bytes() != data:
                raise ValueError(f"preserve existing different file {dest / name}")
            (dest / name).write_bytes(data)
    print(json.dumps({"candidate": NAME, "hashes": json.loads(files["manifest.json"])["hashes"], "status": "UNADAPTED_PARENT_ONLY"}))
    if args.model_check:
        report = boundary_model()
        (dest / "parameter-model-check.json").write_text(json.dumps(report, indent=2) + "\n")
        print(json.dumps({"status": report["status"], "boundary_cases": len(report["cases"])}))


if __name__ == "__main__":
    main()
