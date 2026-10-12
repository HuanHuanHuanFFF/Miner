"""Replace one shallow predecessor ring by an independent eight-byte head table."""
from pathlib import Path
import hashlib
import json

ROOT = Path(__file__).resolve().parents[1]
PARENT = ROOT / "candidates/r22-595-chain-halfhead"
OUT = ROOT / "evidence/round25/astra"
NAME = "r25-astra-dual8"


def sha(b):
    return hashlib.sha256(b).hexdigest()


def region(source, start, end):
    a = source.index(start)
    b = source.index(end, a)
    return source[a:b]


def main():
    raw = (PARENT / "parse.rs").read_bytes()
    assert sha(raw) == "57a8fb4feffa52d6b966899c4a56bc4754f6fc967a05cf52d5b02a574d037275"
    base = raw.decode()
    helpers = """// R25: independent four/eight-byte retention in the same 256KiB table budget.
// Public #385 supplies the prior dual-hash idea, not copied implementation bytes here.
// All validators, insertion positions and emission helpers below derive from the595 parent.
#[inline(always)]
pub fn r25_d8_slot(s: &[u8], i: usize) -> usize {
    (pc_be8(s, i).wrapping_mul(0x9E37_79B9_7F4A_7C15) >> 49) as usize
}

#[inline(always)]
pub fn r25_d8_link<const H: usize>(s: &[u8], head: &mut [u32; H], long: &mut [u32; 32768], a: usize, i: usize) {
    head[a] = i as u32;
    long[r25_d8_slot(s, i)] = i as u32;
}

/// Original short head, plus one independent long-prefix hint validated over all eight bytes.
#[inline(always)]
pub fn r25_d8_probe(s: &[u8], c: usize, cw: u64, c8: usize, p: usize, km: u32) -> (usize, usize) {
    let f = pc_probe_m(s, c, cw, p, km);
    let d8 = p.wrapping_sub(c8);
    if f.0 < 258 && c8 < c && d8.wrapping_sub(1) < 32768 && p + 8 <= s.len()
        && pc_be8(s, c8) == pc_be8(s, p) {
        let m = pc_xlen16(s, c8, p, 0);
        if m > f.0 && m >= 8 { (m, d8) } else { f }
    } else { f }
}

"""
    record = region(base, "pub fn pc_record3_m<const H: usize>",
                    "/// `pc_run` for a class searched with one chain step")
    record = record.replace("pub fn pc_record3_m<", "pub fn r25_d8_record3<", 1)
    old_signature = "head: &mut [u32; H], ins0: usize"
    assert record.count(old_signature) == 1
    record = record.replace(old_signature, "head: &mut [u32; H], long: &mut [u32; 32768], ins0: usize")
    assert record.count("pc_head_set(head, ") == 4
    record = record.replace("pc_head_set(head, ", "r25_d8_link::<H>(s, head, long, ")
    record = "#[inline(always)]\n" + record

    run = region(base, "pub fn pc_run1<const H: usize>",
                 "/// The class itself when `pc_parse` gives class `cls`")
    run = run.replace("pub fn pc_run1<", "pub fn r25_d8_run1<", 1)
    old_head = "        let mut head = [0u32; H];"
    assert run.count(old_head) == 1
    run = run.replace(old_head, old_head + "\n        let mut long = [0u32; 32768];")
    original_store = "            pc_head_set(&mut head, pre_slot, p);"
    assert run.count(original_store) == 1
    run = run.replace(original_store, """            let la = r25_d8_slot(input, p);
            let c8 = long[la] as usize;
            pc_head_set(&mut head, pre_slot, p);
            long[la] = p as u32;""")
    original_probe = "let f = pc_probe_m(input, c, cw, p, km);"
    assert run.count(original_probe) == 1
    run = run.replace(original_probe, "let f = r25_d8_probe(input, c, cw, c8, p, km);")
    assert run.count("pc_head_set(&mut head, pre_slot, q);") == 1
    run = run.replace("pc_head_set(&mut head, pre_slot, q);",
                      "r25_d8_link::<H>(input, &mut head, &mut long, pre_slot, q);")
    old_record = "pc_record3_m::<H>(input, &mut head, ins, pre_slot, end, lim, km);"
    assert run.count(old_record) == 1
    run = run.replace(old_record, "r25_d8_record3::<H>(input, &mut head, &mut long, ins, pre_slot, end, lim, km);")
    run = "#[inline(always)]\n" + run
    source = base + "\n" + helpers + record + run
    changes = []
    for row, skip in ((1, 4), (6, 6)):
        old = f"pub fn p125_row{row}(input:&[u8],out:&mut[u32])->usize{{pc_run1c::<32768>(input,out,{skip},0,1000000,4294967295,1,4)}}"
        new = f"pub fn p125_row{row}(input:&[u8],out:&mut[u32])->usize{{r25_d8_run1::<32768>(input,out,{skip},0,1000000,4294967295)}}"
        assert source.count(old) == 1
        source = source.replace(old, new)
        changes.append({"row": row, "from": old, "to": new})
    # The original engine region is byte-identical except the two wrapper calls.
    restored = source[:len(base)]
    for c in changes:
        restored = restored.replace(c["to"], c["from"])
    # Appended bytes begin after the changed wrapper lengths; use the known section boundary instead.
    restored = source.split("\n// R25: independent four/eight-byte retention", 1)[0]
    for c in changes:
        restored = restored.replace(c["to"], c["from"])
    assert restored == base
    assert "let mut prev" not in run and "pc_f_deepen" not in run
    assert "let mut long = [0u32; 32768]" in run
    path = ROOT / "candidates" / NAME
    assert not path.exists(), path
    path.mkdir()
    files = {"parse.rs": source.encode(), "Parse.lean": (PARENT / "Parse.lean").read_bytes()}
    assert all(len(b) <= 524288 for b in files.values())
    for filename, data in files.items():
        (path / filename).write_bytes(data)
    hashes = {filename: sha(data) for filename, data in files.items()}
    manifest = {"candidate": NAME, "parent": PARENT.name, "hashes": hashes,
        "mechanism": "For four-byte PC rows1/6, replace the32768-entry predecessor ring by an independently indexed32768-entry eight-byte latest-position head. Preserve the32768 short head, original insertion positions, skip, lazy0 and fold/emission. Compare at most the short head and one fully byte-validated >=8-byte long hint; all three-byte row0 paths retain the original chain.",
        "difference_from_old_work": "R13 pair64 retained exactly the latest two positions of one short key and tested physical layout. R10 hash5 added a cache outside existing deep4/7-byte chains and paid extra storage/updates. Here the same second-table budget retains a different prefix neighborhood instead of a predecessor; no array or depth is added. Old R3 dense385 used a whole dual-hash engine on all inputs with different routing/insertion; this is a fixed retention change in current595 four-byte PC routes.",
        "attribution": {"source": "references/round21-public-595/source-receipt.json",
                        "code_parent": "candidates/r22-595-chain-halfhead",
                        "idea_reference": "references/round3-public-385/parse.rs o_a_hashp/o_a_hashl and paired-table maintenance; concept only, no385 code copied into this new helper implementation.",
                        "original_headers": "Retained byte-identically."},
        "table_bytes_per_changed_route": {"parent_short_head": 131072, "parent_predecessor": 131072,
                                          "new_short_head": 131072, "new_long_head": 131072},
        "coverage_risk": "Loses the old immediate predecessor when that candidate is not retained by the long hash. Original deeper4..7-byte opportunities may be lost; far long-head match can cost more, and different subsequent parse states make quality nonmonotone.",
        "proof_status": "DRAFT_UNCOMPILED_FOR_NEW_EXACT_PAIR",
        "proof_migration": "New slot/link/probe and cloned run1/record loops require actual extraction. Probe guards c8<c<=p/window and tests all8 bytes before pc_xlen16. Existing FoundAt/Matches/HeadBound/Dec proofs are reusable; long-head contents can be treated as untrusted hints. New source never inherits parent gate.",
        "performance_status": "UNKNOWN", "formal_submission_sent": False}
    (path / "manifest.json").write_bytes((json.dumps(manifest, indent=2) + "\n").encode())
    entry = {"name": NAME, "path": path.relative_to(ROOT).as_posix(), "control": False,
             "hashes": hashes, "anchor": "public595", "comparison_baseline": "combo", "native_decode_reference": "combo"}
    preflight = {"status": "PREDECLARED_NATIVE_RETENTION_TEST",
        "hypothesis": "A nearest short-prefix occurrence often hides an older long-prefix match outside shallow predecessor coverage. Independent8-byte retention may recover more bytes without adding a table or a third candidate.",
        "coverage_frequency": "UNKNOWN; no rate inferred from old deep-D hash5 or EF32 trials.",
        "actual_extra_cost": "One8-byte hash and an independently indexed second-table read at searched positions; one8-byte hash at recorded interior positions. Same two-table stores/allocated bytes, but changed random-access pattern and full long verification can add cost. Primary misses may now perform a long probe.",
        "minimum": "Actual full28 original encoder and independentdecode with combo, public595 and frozenend4 references. Per-file tokens/bytes and exactsource/library identities; no parser-only time promotion.",
        "cost_cap_runner_minutes": 12,
        "stop": "Panic/decode error stops. No meaningful new quality margin, or large losses from missing oldshort-chain matches, closes this fixed representation without a key-length/capacity sweep. If quality is substantial, require original paired total time before full proof investment.",
        "proof": "All inherited Lean is DRAFT; source interfaces and full original obligation remain unverified."}
    for filename, value in (("dual8-entry.json", entry), ("dual8-preflight.json", preflight),
                            ("dual8-static-audit.json", {"status": "VERIFIED_SOURCE_SCOPE_ONLY",
                                "wrapper_changes": changes, "changed_route_k": [2, 4, 5, 9, 12, 14, 15, 17, 18, 19, 20],
                                "original_source_reversal": "exact parent recovered after removing appended helpers and reversing two wrapper calls",
                                "new_functions": ["r25_d8_slot", "r25_d8_link", "r25_d8_probe", "r25_d8_record3", "r25_d8_run1"],
                                "tables_total_bytes": 262144, "native_validation": "NOT_RUN"})):
        target = OUT / filename
        assert not target.exists(), target
        target.write_bytes((json.dumps(value, indent=2) + "\n").encode())
    print(json.dumps(entry, indent=2))


if __name__ == "__main__":
    main()
