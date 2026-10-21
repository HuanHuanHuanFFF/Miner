"""Build bounded, streaming supplemental finders on the verified R9 scalar parent.

The copied parent proof is an explicit unadapted draft. These are screen-ready
Rust candidates, not complete-gate-ready packages. No build or CI is dispatched.
"""
from __future__ import annotations

import argparse
import hashlib
import json
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
BASE = ROOT / "candidates/r9-block-scalar"
EXPECTED = {
    "parse.rs": "faf1d7281678d12c3243002121feecdd0ea139633dea197dbc77d86fb6319257",
    "Parse.lean": "aa21da6f74e81314297df07beecbfc98b15c848354437674bdb9347d8632f0af",
}

SUPPLEMENT = r'''/// Probe one supplemental position after all original candidates and continuation.
/// Append only a strictly longer match in a free slot: original records are retained.
#[inline(always)]
pub fn r10_supplement(input: &[u8], old: usize, i: usize, b8: u64, cap: usize,
    cands: &mut [u32; 16], nc0: usize, best0: usize) -> (usize, usize) {
    if old > 0 && old <= i && nc0 < 16 && best0 < cap {
        let c = old - 1;
        let d = i.wrapping_sub(c);
        if d.wrapping_sub(1) < 32768 {
            let l = probe(input, c, i, b8, cap, best0);
            if l > best0 {
                cands[nc0 % 16] = (l as u32) | ((d as u32) << 9);
                return (nc0 + 1, l);
            }
        }
    }
    (nc0, best0)
}

'''

TAG4_STORE = r'''/// #454 q9_cache4's two-distinct-tag MRU cache, used without its tree.
/// Hash into 32768 two-slot buckets. Position is stored as p+1; zero means absent.
#[inline(always)]
pub fn r10_cache_store(cache: &mut [u64; 65536], b8: u64, p: usize) -> usize {
    let key = (b8 >> 32) as u32;
    let a = (((key.wrapping_mul(2654435761) >> 17) as usize) * 2) % 65536;
    let b = a + 1;
    let old = cache[a];
    let old2 = cache[b];
    let hit = (old >> 32) as u32 == key && old as u32 > 0;
    let found = if hit { old as u32 as usize }
        else if (old2 >> 32) as u32 == key { old2 as u32 as usize } else { 0 };
    let tag = ((key as u64) << 32) | ((p as u32).wrapping_add(1) as u64);
    if !hit { cache[b] = old; }
    cache[a] = tag;
    found
}

'''

HASH5_STORE = r'''/// Independent five-byte hash between the original four/seven-byte chains.
/// One latest position per hash, O(1) update; probe performs the byte validation.
#[inline(always)]
pub fn r10_cache_store(cache: &mut [u32; 65536], b8: u64, p: usize) -> usize {
    let key = b8 >> 24;
    let h = ((key.wrapping_mul(0x9E37_79B9_7F4A_7C15) >> 48) as usize) % 65536;
    let old = cache[h] as usize;
    cache[h] = (p as u32).wrapping_add(1);
    old
}

'''

RANGE = r'''/// Preserve every original insert inside a taken match; add one O(1) cache update.
#[inline(always)]
pub fn r10_insert_range(input: &[u8], head3: &mut [u32; H3N],
    head4: &mut [u32; H4N], prev4: &mut [u32; WN],
    head7: &mut [u32; H7N], prev7: &mut [u32; WN],
    cache: &mut [CACHE_TYPE; 65536], from: usize, to: usize, sh7: u32) {
    let mut q = from;
    while q < to {
        let bq = be8(input, q);
        insert_pos(head3, head4, prev4, head7, prev7, q, bq, sh7);
        r10_cache_store(cache, bq, q);
        q += 1;
    }
}

'''

VARIANTS = {
    "tag4": ("u64", TAG4_STORE,
        "Streaming exact-tag four-byte two-slot cache, derived from #454 q9_cache4; no tree or all-input match cache",
        524288),
    "hash5": ("u32", HASH5_STORE,
        "Streaming independent five-byte latest-position hash; supplements original four/seven-byte chains",
        262144),
}


def sha(data: bytes) -> str:
    return hashlib.sha256(data).hexdigest()


def replace_once(text: str, before: str, after: str) -> str:
    if text.count(before) != 1:
        raise ValueError(f"Expected one source anchor: {before[:120]!r}")
    return text.replace(before, after, 1)


def generate(suffix: str) -> dict[str, bytes]:
    raw = {name: (BASE / name).read_bytes() for name in EXPECTED}
    if {name: sha(value) for name, value in raw.items()} != EXPECTED:
        raise ValueError("Pinned scalar parent bytes changed")
    cache_type, store, mechanism, cache_bytes = VARIANTS[suffix]
    source = raw["parse.rs"].decode("utf-8")
    marker = "/// `dp_parse` with node recording (see the section comment);"
    start = source.index(marker)
    end = source.index("/// Engine D with knobs k", start)
    old_region = source[start:end]
    edits = []
    region = old_region
    before = "    let mut prev7 = [0u32; WN];"
    after = before + f"\n    let mut r10_cache = [0{cache_type}; 65536];"
    edits.append((before, after)); region = replace_once(region, before, after)
    before = "        let hc = insert_pos(&mut head3, &mut head4, &mut prev4, &mut head7, &mut prev7, i, b8, sh7);"
    after = before + "\n        let r10_old = r10_cache_store(&mut r10_cache, b8, i);"
    edits.append((before, after)); region = replace_once(region, before, after)
    before = "            d_record(input, rs, &cands, nc, i, &pc, pn, ppos, cl, cd, tbmax, dupmode);"
    after = """            let r10_more = r10_supplement(input, r10_old, i, b8, cap, &mut cands, nc, best);
            nc = r10_more.0;
            best = r10_more.1;
""" + before
    edits.append((before, after)); region = replace_once(region, before, after)
    before = "                insert_range(input, &mut head3, &mut head4, &mut prev4, &mut head7, &mut prev7, i + 1, end, sh7);"
    after = "                r10_insert_range(input, &mut head3, &mut head4, &mut prev4, &mut head7, &mut prev7, &mut r10_cache, i + 1, end, sh7);"
    edits.append((before, after)); region = replace_once(region, before, after)
    restored = region
    for before, after in reversed(edits):
        restored = replace_once(restored, after, before)
    if restored != old_region:
        raise ValueError("Reverse audit did not restore exact D region")
    helpers = store + SUPPLEMENT + RANGE.replace("CACHE_TYPE", cache_type)
    rust = source[:start] + helpers + region + source[end:]
    if rust[:start] != source[:start] or rust[start+len(helpers)+len(region):] != source[end:]:
        raise ValueError("Source outside helpers and d_parse changed")
    name = f"r10-finder-{suffix}"
    files = {"parse.rs": rust.encode("utf-8"), "Parse.lean": raw["Parse.lean"]}
    parent = json.loads((BASE / "manifest.json").read_text(encoding="utf-8"))
    manifest = {
        "candidate": name, "parent": "candidates/r9-block-scalar",
        "base_submission_id": "361", "parent_hashes": EXPECTED,
        "hashes": {file: sha(value) for file, value in files.items()},
        "bytes": {file: len(value) for file, value in files.items()},
        "attribution": {
            "public_reference": "references/round7-public-361/PROVENANCE.json",
            "parent": parent["attribution"],
            "supplement_source": "references/round8-public-454/PROVENANCE.json" if suffix == "tag4" else
                "Original experiment using #361 hash7 multiplicative hash on a five-byte prefix",
            "supplement_author_hotkey": "5HYsKBJ49UnjNVXBN8hMynUp2Y9M3YqPrsmAqTJrhGnBa4r9" if suffix == "tag4" else None,
        },
        "mechanism": mechanism, "supplemental_fixed_cache_bytes": cache_bytes,
        "maintenance": "One bounded O(1) update alongside every original D insertion, including taken-match inserted ranges; no byte comparison during maintenance",
        "query": "One extra probe only in the original search branch, after original chains and continuation; append a strictly longer candidate only when nc<16; never remove/replace original records",
        "coverage_limit": "Original candidates at each visited node are preserved. Supplemental longer matches can change future continuation, skipped searches and forward statistics; whole-parse equivalence is neither expected nor claimed.",
        "cost_bound": "Extra fixed cache initialization, one update per inserted position, and at most one <=258-byte probe per searched node. No all-position tree or match-record prepass.",
        "audit": "Reverse four exact D-region substitutions and remove three new helpers restores scalar source byte-for-byte. Other routes, knob tables, original chain depths, recording/DP implementations and checked emission code remain byte-identical.",
        "proof_status": "UNKNOWN / UNADAPTED_PARENT_DRAFT: copied parent Parse.lean does not match the new helper calls and cache carried by d_parse_loop. Requires fresh extraction, helper totality, loop interface/invariant adaptation, original obligation, axiom whitelist and round trip.",
        "correctness_status": "UNKNOWN until fresh Rust build and finite decode checks; parent emitter rechecks planned matches but does not replace candidate validation or full gate.",
        "performance_status": "UNKNOWN: paired official total-compression measurements required; additional discovered lengths are not encoded size gains.",
        "falsification": "Stop this variant if build/decode fails, public size gain is absent, or paired total-time/size tradeoff remains dominated; do not expand cache/depth based on unmeasured opportunity counts.",
    }
    if not all(0 < len(value) <= 524288 for value in files.values()):
        raise ValueError("Candidate file exceeds official size boundary")
    files["manifest.json"] = (json.dumps(manifest, indent=2, ensure_ascii=False) + "\n").encode("utf-8")
    return files


def main() -> None:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--check", action="store_true")
    parser.add_argument("--variant", choices=tuple(VARIANTS), action="append")
    args = parser.parse_args()
    for suffix in args.variant or VARIANTS:
        files = generate(suffix)
        destination = ROOT / "candidates" / f"r10-finder-{suffix}"
        if args.check:
            if not all((destination / file).read_bytes() == value for file, value in files.items()):
                raise ValueError(f"Existing {destination.name} differs")
        else:
            destination.mkdir(exist_ok=True)
            for file, value in files.items():
                target = destination / file
                if target.exists() and target.read_bytes() != value:
                    raise ValueError(f"Preserve differing existing candidate: {target}")
                target.write_bytes(value)
        manifest = json.loads(files["manifest.json"])
        print(json.dumps({"candidate": destination.name, "hashes": manifest["hashes"],
            "proof_status": "UNADAPTED_PARENT_DRAFT", "source_reverse_audit": True}))


if __name__ == "__main__":
    main()
