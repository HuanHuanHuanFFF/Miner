"""Build one scalar, tagged-row replacement for the D seven-byte hash chain.

Concept source: facebook/zstd v1.5.7 row matchfinder (BSD/GPL source and licenses
retained with provenance). No SIMD, unsafe code, foreign module or prefetch API.
The parent Lean is retained only as an explicitly unadapted migration draft.
"""
from __future__ import annotations
import argparse
from collections import deque
import hashlib
import json
from pathlib import Path
import random

ROOT = Path(__file__).resolve().parents[1]
BASE = ROOT / "candidates/r9-block-scalar"
NAME = "r10-finder-row16"
EXPECTED = {
    "parse.rs": "faf1d7281678d12c3243002121feecdd0ea139633dea197dbc77d86fb6319257",
    "Parse.lean": "aa21da6f74e81314297df07beecbfc98b15c848354437674bdb9347d8632f0af",
}
ZSTD_SHA256 = "dd6ccf357165dc8cb574ea56a34ff1db57b7b31728b32103d0c6b72319fd45b1"

HELPERS = r'''/// Scalar row/tag/ring design inspired by facebook/zstd v1.5.7 zstd_lazy.c.
/// See this candidate's provenance and retained BSD/GPL licenses. No SIMD port.
/// Read the packed four-bit tag of one of 65536 row slots.
#[inline(always)]
pub fn r10_row_tag(tags: &[u8; 32768], slot: usize) -> u8 {
    let shift = ((slot % 2) * 4) as u32;
    (tags[(slot / 2) % 32768] >> shift) & 15
}

/// O(1) row insertion; return the hash/slot and overwritten entry for this query.
/// Keeping that victim lets the current node query all 16 PRE-insertion entries.
#[inline(always)]
pub fn r10_row_store(rows: &mut [u32; 65536], tags: &mut [u8; 32768],
    heads: &mut [u8; 4096], q: usize, b8: u64, sh7: u32) -> (usize, usize, u32, u8) {
    let h = hash7(b8 >> (sh7 % 64));
    let row = (h / 16) % 4096;
    let write = heads[row] as usize % 16;
    let slot = (row * 16 + write) % 65536;
    let old = rows[slot];
    let old_tag = r10_row_tag(tags, slot);
    rows[slot] = (q as u32).wrapping_add(1);
    let ts = (slot / 2) % 32768;
    let shift = ((slot % 2) * 4) as u32;
    let mask = 15u8 << shift;
    tags[ts] = (tags[ts] & !mask) | (((h % 16) as u8) << shift);
    heads[row] = ((write + 1) % 16) as u8;
    (h, slot, old, old_tag)
}

/// Preserve the original H3/H4 insertion exactly; replace H7 head/prev by a row.
#[inline(always)]
pub fn r10_row_insert_pos(head3: &mut [u32; H3N], head4: &mut [u32; H4N],
    prev4: &mut [u32; WN], rows: &mut [u32; 65536], tags: &mut [u8; 32768],
    heads: &mut [u8; 4096], q: usize, b8: u64, sh7: u32)
    -> (usize, usize, usize, usize, u32, u8) {
    let x4 = (b8 >> 32) as u32;
    let h3 = hash3(x4 >> 8);
    let c3 = head3[h3] as usize;
    head3[h3] = q as u32;
    let h4 = hash4(x4);
    let c4 = head4[h4] as usize;
    head4[h4] = q as u32;
    prev4[q % WN] = c4 as u32;
    let r = r10_row_store(rows, tags, heads, q, b8, sh7);
    (c3, c4, r.0, r.1, r.2, r.3)
}

/// Same inserted range as scalar: preserve H3/H4 and update the replacement row.
#[inline(always)]
pub fn r10_row_insert_range(input: &[u8], head3: &mut [u32; H3N],
    head4: &mut [u32; H4N], prev4: &mut [u32; WN], rows: &mut [u32; 65536],
    tags: &mut [u8; 32768], heads: &mut [u8; 4096], from: usize, to: usize, sh7: u32) {
    let mut q = from;
    while q < to {
        let bq = be8(input, q);
        r10_row_insert_pos(head3, head4, prev4, rows, tags, heads, q, bq, sh7);
        q += 1;
    }
}

/// Visit the 16 retained row entries newest first; row+tag is the full H7 hash.
/// Mismatching tags never call probe or consume the original long-chain budget.
/// All positions are independently guarded, so totality needs no row-content trust.
#[inline(always)]
pub fn r10_row_walk(input: &[u8], rows: &[u32; 65536], tags: &[u8; 32768],
    i: usize, h: usize, written: usize, victim: u32, victim_tag: u8, depth: usize,
    b8: u64, cap: usize, cands: &mut [u32; 16], nc0: usize, best0: usize,
    nice: usize, seen3: usize, seen4: usize) -> (usize, usize) {
    let row = (h / 16) % 4096;
    let write = written % 16;
    let wanted = (h % 16) as u8;
    let mut step = 0usize;
    let mut k = depth;
    let mut nc = nc0;
    let mut best = best0;
    while step < 16 && k > 0 && best < cap && best < nice && nc < 15 {
        let offset = write.wrapping_add(15).wrapping_sub(step) % 16;
        let slot = (row * 16 + offset) % 65536;
        let old = if slot == written { victim } else { rows[slot] };
        let tag = if slot == written { victim_tag } else { r10_row_tag(tags, slot) };
        if tag == wanted && old > 0 && old as usize <= i {
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
        step += 1;
    }
    (nc, best)
}

'''


def sha(data: bytes) -> str:
    return hashlib.sha256(data).hexdigest()


def once(s: str, old: str, new: str) -> str:
    if s.count(old) != 1:
        raise ValueError(f"Expected one exact D anchor: {old[:100]!r}")
    return s.replace(old, new, 1)


def generate() -> dict[str, bytes]:
    raw = {file: (BASE / file).read_bytes() for file in EXPECTED}
    if {file: sha(value) for file, value in raw.items()} != EXPECTED:
        raise ValueError("Pinned scalar parent changed")
    provenance_dir = ROOT / "candidates" / NAME / "provenance"
    if sha((provenance_dir / "zstd_lazy.c").read_bytes()) != ZSTD_SHA256:
        raise ValueError("Reviewed official Zstandard source bytes changed")
    source = raw["parse.rs"].decode("utf-8")
    start = source.index("/// `dp_parse` with node recording (see the section comment);")
    end = source.index("/// Engine D with knobs k", start)
    original = source[start:end]
    region = original
    edits = []
    before = "    let mut head7 = [0u32; H7N];\n    let mut prev7 = [0u32; WN];"
    after = """    let mut r10_rows = [0u32; 65536];
    let mut r10_tags = [0u8; 32768];
    let mut r10_heads = [0u8; 4096];"""
    edits.append((before, after)); region = once(region, before, after)
    before = "        let hc = insert_pos(&mut head3, &mut head4, &mut prev4, &mut head7, &mut prev7, i, b8, sh7);"
    after = "        let hc = r10_row_insert_pos(&mut head3, &mut head4, &mut prev4, &mut r10_rows, &mut r10_tags, &mut r10_heads, i, b8, sh7);"
    edits.append((before, after)); region = once(region, before, after)
    before = """            let s7 = skip_same(&prev7, hc.2, dep7, (p3 && hc.2 == hc.0) || (d4 > 0 && hc.2 == hc.1));
            let w2 = d_walk(input, &prev7, i, s7.0, s7.1, b8, cap, &mut cands, nc, best, nice);"""
    after = """            let seen3 = if p3 { hc.0 } else { i };
            let seen4 = if d4 > 0 { hc.1 } else { i };
            let w2 = r10_row_walk(input, &r10_rows, &r10_tags, i, hc.2, hc.3, hc.4, hc.5,
                dep7, b8, cap, &mut cands, nc, best, nice, seen3, seen4);"""
    edits.append((before, after)); region = once(region, before, after)
    before = "                insert_range(input, &mut head3, &mut head4, &mut prev4, &mut head7, &mut prev7, i + 1, end, sh7);"
    after = "                r10_row_insert_range(input, &mut head3, &mut head4, &mut prev4, &mut r10_rows, &mut r10_tags, &mut r10_heads, i + 1, end, sh7);"
    edits.append((before, after)); region = once(region, before, after)
    restored = region
    for before, after in reversed(edits):
        restored = once(restored, after, before)
    if restored != original or "prev7" in region or "head7" in region:
        raise ValueError("Replacement/reversal audit failed")
    rust = (source[:start] + HELPERS + region + source[end:]).encode("utf-8")
    files = {"parse.rs": rust, "Parse.lean": raw["Parse.lean"]}
    parent = json.loads((BASE / "manifest.json").read_text(encoding="utf-8"))
    manifest = {
        "candidate": NAME, "parent": "candidates/r9-block-scalar", "base_submission_id": "361",
        "parent_hashes": EXPECTED, "hashes": {file: sha(value) for file, value in files.items()},
        "bytes": {file: len(value) for file, value in files.items()},
        "attribution": {"parent": parent["attribution"],
            "row_design": "facebook/zstd v1.5.7 lib/compress/zstd_lazy.c, ZSTD_row_nextIndex / row_update_internalImpl / RowFindBestMatch and high-level design comment1124..1138",
            "source_sha256": ZSTD_SHA256, "local_provenance": f"candidates/{NAME}/provenance/sources.json",
            "license": "Zstandard dual BSD/GPL; source and both license notices retained. Scalar Rust implementation of row/tag/ring concept, not the SIMD/SWAR code.",
        },
        "mechanism": "Replace D's H7 head/prev chain with4096 rows x16 recent u32 positions, packed4-bit tags and one cursor per row; H3/H4 and all downstream planners/recorders/emitters retain parent code",
        "shape": {"buckets": 4096, "entries_per_row": 16, "hash_bits": 16,
            "row_bits": 12, "tag_bits": 4, "position_bytes": 262144,
            "tag_bytes": 32768, "cursor_bytes": 4096, "total_bytes": 299008,
            "old_h7_head_plus_prev_bytes": 393216, "state_delta_bytes": -94208},
        "maintenance": "One O(1) ring insertion at each original inserted position, including taken-match ranges; update position, one packed tag byte and cursor. Capture evicted entry to query all16 entries existing before the current insertion.",
        "query": "Scan at most16 consecutive row slots newest to oldest; row+tag reconstructs the original16-bit hash. Only valid matching tags consume the unchanged dep7 budget; duplicate already-probed H3/H4 heads consume budget but avoid byte probing. Existing nice/cap/nc guards and probe are retained.",
        "cost_tradeoff": "Saves old head+prev state and pointer-dependent traversal, adds nibble/cursor maintenance and scalar tag scanning. SIMD release-note speed figures do not transfer; actual encoder-inclusive time remains unknown.",
        "coverage_limit": "Only latest16 positions sharing a12-bit row are retained, so other tags can evict deep original chain nodes; no original long-chain coverage or token equivalence claim. The saved victim prevents accidental loss of one pre-insertion slot but does not restore older history.",
        "audit": "Remove five new helpers and reverse four exact substitutions inside d_parse to restore scalar bytes. Original insert_pos/insert_range/d_walk functions, other routes/knobs, H3/H4 statements and every downstream planner/recorder/checked emitter remain byte-identical.",
        "proof_status": "UNADAPTED_PARENT_DRAFT / NOT_RUN: new tag/store/insert/range/walk totality and D-state replacement require actual extraction and proof port. Original obligation/allowed axioms/full round trip must pass on exact final files.",
        "proof_cost": "Retain H3/H4 head bounds; rows/tags/cursor content need not be trusted because query guards position<=i, nonzero and valid distance before probe. Replace two old chain arrays with three row arrays, remove H7 head bound, and preserve probe's best<=cap postcondition and bounded16-step termination.",
        "correctness_status": "UNKNOWN native build/finite decode/full gate; parent checked emission is not a gate for changed Rust",
        "performance_status": "UNKNOWN until same-runner paired public total-compression and encoded size; this is one fixed shape, not a row/depth sweep",
        "falsification": "Stop if extraction/build/decode rejects, or loss of original long-chain coverage costs too much size for measured time gains; do not attribute any speed gain solely to layout without code/phase evidence.",
    }
    if not all(0 < len(value) <= 524288 for value in files.values()):
        raise ValueError("Candidate per-file size boundary exceeded")
    files["manifest.json"] = (json.dumps(manifest, indent=2, ensure_ascii=False) + "\n").encode("utf-8")
    return files


def model_check() -> dict:
    """Finite row-layout check against an independent per-row deque oracle.

    This validates the proposed encoding/traversal, not native Rust execution,
    extractor acceptance, real match bytes, full proof or performance.
    """
    scenarios = {
        "one-hash-evicted-sixteenth": [(0x1234, q) for q in range(96)],
        "all-tags-same-row": [(0xABCDE % 65536 // 16 * 16 + q % 16, q) for q in range(256)],
        "packed-neighbor-tags": [(0xFFF0 + q % 2, q) for q in range(256)],
        "window-boundaries": [(0x5555, q) for q in (0, 1, 2, 32767, 32768, 32769, 65535, 65536, 65537)],
    }
    rng = random.Random(3611666)
    scenarios["deterministic-mixed-rows"] = [
        ((0x3210 + rng.randrange(16)) if q % 3 else rng.randrange(65536), q)
        for q in range(10000)]
    total = 0; rescued = 0; report = {}
    for label, sequence in scenarios.items():
        rows = [0] * 65536; tags = bytearray(32768); heads = bytearray(4096)
        oracle = [deque(maxlen=16) for _ in range(4096)]
        checks = 0; local_rescued = 0
        for h, q in sequence:
            row = h // 16; wanted = h % 16; write = heads[row] % 16
            slot = row * 16 + write
            victim = rows[slot]
            victim_tag = (tags[slot // 2] >> ((slot % 2) * 4)) & 15
            previous = list(oracle[row])
            expected = [(hash_value, pos) for hash_value, pos in reversed(previous)
                if hash_value == h and 1 <= q - pos <= 32768]
            rows[slot] = q + 1
            shift = (slot % 2) * 4; ts = slot // 2
            neighbor_tag = (tags[ts] >> (4 - shift)) & 15
            tags[ts] = (tags[ts] & ~(15 << shift)) | (wanted << shift)
            assert ((tags[ts] >> (4 - shift)) & 15) == neighbor_tag
            heads[row] = (write + 1) % 16
            observed = []
            recovered_victim = False
            for step in range(16):
                offset = (write + 15 - step) % 16; target = row * 16 + offset
                old = victim if target == slot else rows[target]
                tag = victim_tag if target == slot else (tags[target // 2] >> ((target % 2) * 4)) & 15
                if tag == wanted and old > 0 and old <= q and q - (old - 1) <= 32768:
                    observed.append((row * 16 + tag, old - 1))
                    recovered_victim |= target == slot
            assert observed == expected, (label, q, observed, expected)
            assert all(observed[i][1] > observed[i + 1][1] for i in range(len(observed) - 1))
            for depth in (0, 1, 4, 16, 48):
                assert len(observed[:depth]) <= min(depth, 16)
                checks += 1
            local_rescued += int(recovered_victim)
            oracle[row].append((h, q)); total += 1
        rescued += local_rescued
        report[label] = {"inserted_positions": len(sequence), "budget_checks": checks,
            "valid_overwritten_oldest_matches_retained": local_rescued}
    return {"status": "VERIFIED_FINITE_PYTHON_LAYOUT_MODEL_ONLY", "positions": total,
        "scope": "Packed-tag neighbor preservation, pre-insertion16-slot history, exact16-bit hash filtering, newest-first order, window boundary filtering and bounded budgets against independent deque oracle",
        "not_verified": "Native Rust compilation/byte match validity, extraction, Lean gate, encoded output or performance",
        "valid_overwritten_oldest_matches_retained": rescued, "scenarios": report,
        "generator_sha256": sha(Path(__file__).read_bytes())}


def main() -> None:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--check", action="store_true")
    parser.add_argument("--model-check", action="store_true")
    args = parser.parse_args()
    files = generate(); target = ROOT / "candidates" / NAME
    if args.check:
        if not all((target / file).read_bytes() == value for file, value in files.items()):
            raise ValueError("Row candidate regeneration differs")
    else:
        target.mkdir(exist_ok=True)
        for file, value in files.items():
            path = target / file
            if path.exists() and path.read_bytes() != value:
                raise ValueError(f"Preserve differing existing row candidate: {path}")
            path.write_bytes(value)
    manifest = json.loads(files["manifest.json"])
    print(json.dumps({"candidate": NAME, "hashes": manifest["hashes"], "state_bytes": 299008,
        "proof_status": "UNADAPTED_PARENT_DRAFT", "source_reverse_audit": True}))
    if args.model_check:
        receipt = model_check()
        (target / "layout-model-check.json").write_text(json.dumps(receipt, indent=2) + "\n", encoding="utf-8")
        print(json.dumps(receipt))


if __name__ == "__main__":
    main()
