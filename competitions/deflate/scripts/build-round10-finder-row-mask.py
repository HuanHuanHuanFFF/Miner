"""One same-output row16 tag-mask experiment; no insertion/history/budget change.

Uses ordinary U64 shifts/bit operations and the existing leading_zeros intrinsic.
The explicit sixteen-iteration fuel is the loop's totality measure.
"""
from __future__ import annotations
import argparse
import hashlib
import json
from pathlib import Path
import random

ROOT = Path(__file__).resolve().parents[1]
BASE = ROOT / "candidates/r10-finder-row16"
NAME = "r10-finder-row16-mask"
PINNED = {"parse.rs": "ffe31d6253f851fd3e843a991c05e12564cbab289f117c41618653e9913dcc73",
          "Parse.lean": "aa21da6f74e81314297df07beecbfc98b15c848354437674bdb9347d8632f0af"}

MASK_HELPER = r'''/// Read the row's eight packed-tag bytes as one ordinary little-endian U64.
/// Zero-nibble test has no inter-nibble carry: (v & 0x777...) + 0x777... <= 0xEEE....
/// Override the written slot's hit with victim_tag equality, restoring pre-insert history.
#[inline(always)]
pub fn r10_row_mask(tags: &[u8; 32768], row0: usize, written: usize,
    victim_tag: u8, wanted: u8) -> u64 {
    let row = row0 % 4096;
    let base = row * 8;
    let mut word = 0u64;
    let mut j = 0usize;
    while j < 8 {
        word |= (tags[(base + j) % 32768] as u64) << ((j * 8) as u32);
        j += 1;
    }
    let repeated = ((wanted & 15) as u64) * 0x1111_1111_1111_1111;
    let v = word ^ repeated;
    let low = (v & 0x7777_7777_7777_7777) + 0x7777_7777_7777_7777;
    let mut hits = !(low | v) & 0x8888_8888_8888_8888;
    if wanted >= 16 { hits = 0; }
    let write = written % 16;
    if written / 16 == row {
        let bit = 8u64 << ((write * 4) as u32);
        hits &= !bit;
        if victim_tag == wanted { hits |= bit; }
    }
    let shift = (write * 4) as u32;
    if shift == 0 { hits } else { (hits >> shift) | (hits << (64 - shift)) }
}

'''

WALK = r'''/// Same row16 ordered probes/budget, with whole-word tag filtering.
/// The rotated highest matching nibble is the newest retained slot.
#[inline(always)]
pub fn r10_row_walk(input: &[u8], rows: &[u32; 65536], tags: &[u8; 32768],
    i: usize, h: usize, written: usize, victim: u32, victim_tag: u8, depth: usize,
    b8: u64, cap: usize, cands: &mut [u32; 16], nc0: usize, best0: usize,
    nice: usize, seen3: usize, seen4: usize) -> (usize, usize) {
    // Original row16's first loop guard: avoid tag loading on a no-work query.
    if depth == 0 || best0 >= cap || best0 >= nice || nc0 >= 15 {
        return (nc0, best0);
    }
    let row = (h / 16) % 4096;
    let write = written % 16;
    let wanted = (h % 16) as u8;
    let mut mask = r10_row_mask(tags, row, written, victim_tag, wanted);
    let mut fuel = 16usize;
    let mut k = depth;
    let mut nc = nc0;
    let mut best = best0;
    while fuel > 0 && mask != 0 && k > 0 && best < cap && best < nice && nc < 15 {
        fuel -= 1;
        let logical = 15usize.wrapping_sub((mask.leading_zeros() / 4) as usize) % 16;
        mask &= !(8u64 << ((logical * 4) as u32));
        let offset = (write + logical) % 16;
        let slot = (row * 16 + offset) % 65536;
        let old = if slot == written { victim } else { rows[slot] };
        if old > 0 && old as usize <= i {
            k -= 1;
            let c = old as usize - 1;
            let d = i.wrapping_sub(c);
            if d.wrapping_sub(1) < 32768 && c != seen3 && c != seen4 {
                let l = probe(input, c, i, b8, cap, best);
                if l > 0 {
                    cands[nc % 16] = (l as u32) | ((d as u32) << 9);
                    nc += 1;
                    best = l;
                }
            }
        }
    }
    (nc, best)
}

'''


def sha(data: bytes) -> str:
    return hashlib.sha256(data).hexdigest()


def bitmap(values: list[int], wanted: int, written: int, row: int, victim_tag: int) -> int:
    word = sum(value << (4 * index) for index, value in enumerate(values))
    v = word ^ ((wanted & 15) * 0x1111111111111111)
    low = (v & 0x7777777777777777) + 0x7777777777777777
    hits = ~(low | v) & 0x8888888888888888
    if wanted >= 16:
        hits = 0
    write = written % 16
    if written // 16 == row:
        bit = 8 << (write * 4)
        hits = (hits & ~bit) | (bit if victim_tag == wanted else 0)
    shift = write * 4
    return hits if shift == 0 else ((hits >> shift) | (hits << (64 - shift))) & ((1 << 64) - 1)


def masked_slots(values: list[int], wanted: int, written: int, row: int, victim_tag: int) -> list[int]:
    mask = bitmap(values, wanted, written, row, victim_tag)
    result = []
    for _ in range(16):
        if not mask:
            break
        lz = 64 - mask.bit_length()
        logical = (15 - lz // 4) % 16
        mask &= ~(8 << (logical * 4))
        result.append((written % 16 + logical) % 16)
    assert mask == 0
    return result


def scalar_slots(values: list[int], wanted: int, written: int, row: int, victim_tag: int) -> list[int]:
    result = []
    for step in range(16):
        offset = (written % 16 + 15 - step) % 16
        tag = victim_tag if row * 16 + offset == written else values[offset]
        if tag == wanted:
            result.append(offset)
    return result


def walk_model(slots: list[int], old_positions: list[int], lengths: list[int], i: int,
               written: int, row: int, victim: int, depth: int, cap: int, nc: int,
               best: int, nice: int, seen3: int, seen4: int) -> tuple:
    k = depth; probes = []; records = []
    for offset in slots:
        if not (k > 0 and best < cap and best < nice and nc < 15):
            break
        old = victim if row * 16 + offset == written else old_positions[offset]
        if old > 0 and old <= i:
            k -= 1; c = old - 1; distance = i - c
            if 1 <= distance <= 32768 and c != seen3 and c != seen4:
                probes.append((offset, c))
                length = min(lengths[offset], cap)
                if length > best:
                    records.append((length, distance)); best = length; nc += 1
    return nc, best, k, probes, records


def model_check() -> dict:
    rng = random.Random(3611616); tag_cases = 0; walk_cases = 0
    # Exhaust every nibble value and every adjacent pair, including victim tags
    # outside0..15 to check that packed-word truncation cannot invent a victim hit.
    for left in range(16):
        for right in range(16):
            values = [left, right] * 8
            for wanted in range(16):
                for write in range(16):
                    for victim_tag in (wanted, (wanted + 1) % 16, 255):
                        a = scalar_slots(values, wanted, write, 0, victim_tag)
                        b = masked_slots(values, wanted, write, 0, victim_tag)
                        assert a == b; tag_cases += 1
    for trial in range(6000):
        row = rng.randrange(4096); write = rng.randrange(16)
        written = row * 16 + write
        if trial % 17 == 0: written += 65536  # arbitrary inconsistent victim metadata
        values = [rng.randrange(16) for _ in range(16)]
        wanted = rng.randrange(256) if trial % 13 == 0 else rng.randrange(16)
        victim_tag = rng.randrange(256)
        a = scalar_slots(values, wanted, written, row, victim_tag)
        b = masked_slots(values, wanted, written, row, victim_tag)
        assert a == b; tag_cases += 1
        i = 50000
        olds = [rng.choice((0, i + 1, i, i - 32767, i - 32768, rng.randrange(i + 1))) for _ in range(16)]
        lengths = [rng.randrange(3, 259) for _ in range(16)]
        victim = rng.choice((0, i, i + 1, rng.randrange(i + 1)))
        for depth in (0, 1, 4, 16, 48):
            nc = rng.choice((0, 14, 15)); best = rng.choice((2, 4, 32, 258)); nice = rng.choice((16, 32, 258))
            seen3 = rng.choice((i, olds[0] - 1)); seen4 = rng.choice((i, olds[1] - 1))
            args = (olds, lengths, i, written, row, victim, depth, 258, nc, best, nice, seen3, seen4)
            assert walk_model(a, *args) == walk_model(b, *args)
            walk_cases += 1
    return {"status": "VERIFIED_FINITE_PYTHON_ROW_QUERY_MODEL_ONLY", "tag_order_cases": tag_cases,
        "ordered_probe_record_budget_cases": walk_cases,
        "scope": "Exact zero-nibble masks, victim equality, cursor rotation and newest-first matching slots; simulated probe order, record sequence, final nc/best and dep7 budget versus scalar row model",
        "not_verified": "Native Rust444 token/decode equivalence, encoded bytes, extraction, full proof or paired performance",
        "generator_sha256": sha(Path(__file__).read_bytes())}


def generate() -> dict[str, bytes]:
    raw = {file: (BASE / file).read_bytes() for file in PINNED}
    if {file: sha(value) for file, value in raw.items()} != PINNED:
        raise ValueError("Frozen row16 parent changed")
    source = raw["parse.rs"].decode("utf-8")
    start = source.index("/// Visit the 16 retained row entries newest first;")
    end = source.index("/// `dp_parse` with node recording", start)
    old = source[start:end]
    rust = source[:start] + MASK_HELPER + WALK + source[end:]
    if rust.replace(MASK_HELPER + WALK, old, 1) != source:
        raise ValueError("Exact single-walk-region reversal failed")
    files = {"parse.rs": rust.encode("utf-8"), "Parse.lean": raw["Parse.lean"]}
    parent = json.loads((BASE / "manifest.json").read_text(encoding="utf-8"))
    manifest = dict(parent)
    manifest.update(candidate=NAME, parent="candidates/r10-finder-row16", parent_hashes=PINNED,
        hashes={file: sha(value) for file, value in files.items()}, bytes={file: len(value) for file, value in files.items()},
        mechanism="Replace row16 scalar per-slot tag scan by one ordinary U64 packed-tag equality mask; same ring/history, ordered probes and dep7 budget",
        query="Same pre-insertion16-slot set and newest-first matching slots as row16; restore victim equality in the bitmap, rotate by cursor, select high matching nibble with leading_zeros, clear it, and consume explicit fuel16. Preserve all original position/distance/duplicate/nice/cap/nc/dep7 checks.",
        audit="Only replace r10_row_walk region and add r10_row_mask/load loop; reversal restores frozen row16 Rust. Entire insertion/maintenance, D parse and downstream planner/record/emission bytes unchanged.",
        equivalence_status="INFERRED same output; finite Python mask/order/record/budget model passed; must verify444 native Rust tokens/decode and public compressed bytes against exact frozen row16",
        expected_equivalent_to="r10-finder-row16",
        proof_status="UNADAPTED_PARENT_DRAFT / NOT_RUN: changed row-walk loop interface and new mask/load totality need fresh actual extraction; full proof expenditure waits for performance",
        unsupported_operation_review="No new intrinsic/module/unsafe/SIMD/rotate operation; U64 leading_zeros already present in parent, shifts/bitwise/add/mul and arrays supported in existing extracts. New totality bounds/loop interfaces remain unverified.",
        cost_question="Discriminate whether scalar tag scanning explains row16's measured ~10.9% slowdown; no claim that this is already established",
        performance_status="UNKNOWN until same-runner paired total time against scalar and row16; output size must match row16 exactly",
        falsification="Close this row implementation if whole-word filtering does not materially restore encoder-inclusive time; do not continue capacity/depth sweeps.")
    if not all(0 < len(value) <= 524288 for value in files.values()):
        raise ValueError("Official per-file boundary exceeded")
    files["manifest.json"] = (json.dumps(manifest, indent=2, ensure_ascii=False) + "\n").encode("utf-8")
    return files


def main() -> None:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--check", action="store_true")
    parser.add_argument("--model-only", action="store_true")
    parser.add_argument("--update", action="store_true", help="Update only this uncommitted experimental candidate before its CI freeze")
    args = parser.parse_args(); target = ROOT / "candidates" / NAME
    target.mkdir(exist_ok=True)
    if args.model_only:
        receipt = model_check()
        (target / "query-model-check.json").write_text(json.dumps(receipt, indent=2) + "\n", encoding="utf-8")
        print(json.dumps(receipt)); return
    files = generate()
    if args.check:
        if not all((target / file).read_bytes() == value for file, value in files.items()):
            raise ValueError("Mask candidate reconstruction differs")
    else:
        if not (target / "query-model-check.json").is_file():
            raise ValueError("Run the independent model before generating a candidate")
        model = json.loads((target / "query-model-check.json").read_text(encoding="utf-8"))
        if model["status"] != "VERIFIED_FINITE_PYTHON_ROW_QUERY_MODEL_ONLY" or model["generator_sha256"] != sha(Path(__file__).read_bytes()):
            raise ValueError("Model receipt is stale or not verified for this exact generator")
        for file, value in files.items():
            path = target / file
            if path.exists() and path.read_bytes() != value and not args.update:
                raise ValueError(f"Preserve differing existing mask candidate: {path}")
            path.write_bytes(value)
    print(json.dumps({"candidate": NAME, "hashes": json.loads(files["manifest.json"])["hashes"],
        "proof_status": "UNADAPTED_PARENT_DRAFT", "expected_equivalent_to": "r10-finder-row16"}))


if __name__ == "__main__":
    main()
