"""Final fixed R10 experiment: 32-endpoint prefix-record masks, not rmq8.

Parent: verified record-nonempty. No speculative forward optimization is mixed
in. The parent proof is explicitly unadapted; no CI is dispatched here.
"""
from pathlib import Path
import argparse
import ast
import hashlib
import json
import random

ROOT = Path(__file__).resolve().parents[1]
BASE = ROOT / "candidates/r10-record-nonempty"
NAME = "r10-backward-prefixmask"


def sha(data):
    return hashlib.sha256(data).hexdigest()


HELPERS = r'''/// Small getters avoid direct array-read borrows between extracted loops.
#[inline(always)]
pub fn pm_cost(ring: &[u64; D_RING], p: usize) -> u64 {
    d_cell(ring, p) >> 32
}

#[inline(always)]
pub fn pm_mask(masks: &[u32; D_RING], p: usize) -> u32 {
    masks[p % D_RING]
}

#[inline(always)]
pub fn pm_end(ends: &[u16; 512], l: usize) -> usize {
    ends[l % 512] as usize
}

#[inline(always)]
pub fn pm_price(lc: &[u32; 512], l: usize) -> u64 {
    lc[l % 512] as u64
}

#[inline(always)]
pub fn pm_state_get(state: &[usize; 4], k: usize) -> usize {
    state[k % 4]
}

/// state = [last finalized position, rolling u32 mask, enabled, input end].
/// Publish only final cells, in descending consecutive order. A broken order
/// disables all subsequent mask queries instead of fabricating a valid window.
#[inline(always)]
pub fn pm_publish(ring: &[u64; D_RING], masks: &mut [u32; D_RING], state: &mut [usize; 4], p: usize) {
    if pm_state_get(state, 2) != 1 {
        return;
    }
    let front = pm_state_get(state, 0);
    let old = pm_state_get(state, 1) as u32;
    if (old == 0 && p != front) || (old != 0 && p.wrapping_add(1) != front) {
        state[2] = 0;
        return;
    }
    let cost = pm_cost(ring, p);
    let mut m = old << 1;
    let mut fuel = 32usize;
    while m != 0 && fuel > 0 {
        fuel -= 1;
        let low = m & (!m).wrapping_add(1);
        let offset = 31u32.saturating_sub(low.leading_zeros()) as usize;
        if pm_cost(ring, p.wrapping_add(offset)) >= cost {
            m &= m.wrapping_sub(1);
        } else {
            fuel = 0;
        }
    }
    let next = m | 1;
    masks[p % D_RING] = next;
    state[0] = p;
    state[1] = next as usize;
}

/// Return the shortest minimum offset in a valid prefix, or sentinel32.
#[inline(always)]
pub fn pm_prefix_offset(masks: &[u32; D_RING], a: usize, len: usize) -> usize {
    if len == 0 || len > 32 {
        return 32;
    }
    let keep = if len == 32 { 0xFFFF_FFFFu32 } else { (1u32 << (len as u32)).wrapping_sub(1) };
    let m = pm_mask(masks, a) & keep;
    if m == 0 {
        32
    } else {
        31u32.saturating_sub(m.leading_zeros()) as usize
    }
}

/// Constant-price runs use <=32 endpoint-prefix queries with shortest ties.
/// Singleton ranges use the original exact scalar base case; malformed or
/// unpublished state falls back to the original d_best_len implementation.
#[inline(always)]
pub fn pm_best_len(lc: &[u32; 512], ring: &[u64; D_RING], masks: &[u32; D_RING], ends: &[u16; 512], state: &[usize; 4], p: usize, lo: usize, e: usize) -> u64 {
    if lo >= e || e > 259 {
        return d_best_len(lc, ring, p, lo, e);
    }
    if e - lo == 1 {
        return (d_bcost(lc, ring, p, lo) << 9) | lo as u64;
    }
    let n = pm_state_get(state, 3);
    if lo < 3 || pm_state_get(state, 2) != 1 || p >= n || e - 1 > n - p || pm_state_get(state, 0) != p.wrapping_add(1) {
        return d_best_len(lc, ring, p, lo, e);
    }
    let mut best = 0xFFFF_FFFF_FFFF_FFFFu64;
    let mut l = lo;
    let mut runs = 259usize;
    while l < e && runs > 0 {
        runs -= 1;
        let raw_stop = pm_end(ends, l);
        if raw_stop <= l || raw_stop > 512 {
            return d_best_len(lc, ring, p, lo, e);
        }
        let stop = if raw_stop < e { raw_stop } else { e };
        let price = pm_price(lc, l);
        let mut chunks = 9usize;
        while l < stop && chunks > 0 {
            chunks -= 1;
            let remaining = stop - l;
            let width = if remaining > 32 { 32 } else { remaining };
            let v;
            if width == 1 {
                v = (d_bcost(lc, ring, p, l) << 9) | l as u64;
            } else {
                let a = p.wrapping_add(l);
                let offset = pm_prefix_offset(masks, a, width);
                if offset >= width {
                    return d_best_len(lc, ring, p, lo, e);
                }
                let endpoint_cost = pm_cost(ring, a.wrapping_add(offset));
                v = (endpoint_cost.wrapping_add(price) << 9) | l.wrapping_add(offset) as u64;
            }
            if v < best {
                best = v;
            }
            l += width;
        }
        if l < stop {
            return d_best_len(lc, ring, p, lo, e);
        }
    }
    if l < e { d_best_len(lc, ring, p, lo, e) } else { best }
}

'''


def price_helper():
    tree = ast.parse((ROOT / "scripts/build-round10-rmq.py").read_text())
    assignment = next(node for node in tree.body if isinstance(node, ast.Assign) and any(isinstance(t, ast.Name) and t.id == "HELPERS" for t in node.targets))
    old = ast.literal_eval(assignment.value)
    helper = old[:old.index("/// Once the low end")]
    assert helper.count("pub fn r10_price_ends(") == 1
    return helper.replace("r10_price_ends", "pm_price_ends")


def generate():
    raw = {n: (BASE / n).read_bytes() for n in ("parse.rs", "Parse.lean")}
    parent = json.loads((BASE / "manifest.json").read_text())
    assert all(sha(data) == parent["hashes"][n] for n, data in raw.items())
    gate = json.loads((BASE / "VERIFICATION.json").read_text())
    assert gate["official_accepted"] and gate["files"] == parent["hashes"]
    original = raw["parse.rs"].decode()
    edits = [
        ("pub fn d_gap(", price_helper() + HELPERS + "pub fn d_gap(", 1),
        ("ring: &mut [u64; D_RING], out: &mut [u32], hi: usize,", "ring: &mut [u64; D_RING], masks: &mut [u32; D_RING], pmstate: &mut [usize; 4], out: &mut [u32], hi: usize,", 1),
        ("        ring[q % D_RING] = v;\n        out[q] = v as u32;", "        ring[q % D_RING] = v;\n        pm_publish(ring, masks, pmstate, q);\n        out[q] = v as u32;", 3),
        ("ring: &mut [u64; D_RING], r: u32, p: usize, prev: usize,", "ring: &mut [u64; D_RING], masks: &[u32; D_RING], ends: &[u16; 512], pmstate: &[usize; 4], r: u32, p: usize, prev: usize,", 1),
        ("let bb = d_best_len(lc, ring, p, prev + 1, len + 1);", "let bb = pm_best_len(lc, ring, masks, ends, pmstate, p, prev + 1, len + 1);", 1),
        ("dcc: &mut [u32; 32], bs: &mut [usize; 2], pos: usize)", "dcc: &mut [u32; 32], ends: &mut [u16; 512], bs: &mut [usize; 2], pos: usize)", 1),
        ("        d_load(tabs, b.wrapping_mul(D_TS), litc, lc, dcc);", "        d_load(tabs, b.wrapping_mul(D_TS), litc, lc, dcc);\n        pm_price_ends(lc, ends);", 1),
        ("    let mut ring = [D_UNSET; D_RING];", "    let mut ring = [D_UNSET; D_RING];\n    let mut masks = [0u32; D_RING];\n    let mut ends = [0u16; 512];\n    let mut pmstate = [n, 0usize, 1usize, n];", 1),
        ("    ring[n % D_RING] = 0;", "    ring[n % D_RING] = 0;\n    pm_publish(&ring, &mut masks, &mut pmstate, n);", 1),
        ("    d_load(tabs, b0.wrapping_mul(D_TS), &mut litc, &mut lc, &mut dcc);", "    d_load(tabs, b0.wrapping_mul(D_TS), &mut litc, &mut lc, &mut dcc);\n    pm_price_ends(&lc, &mut ends);", 1),
        ("d_block(tabs, bstart, &mut litc, &mut lc, &mut dcc, &mut bs,", "d_block(tabs, bstart, &mut litc, &mut lc, &mut dcc, &mut ends, &mut bs,", 2),
        ("d_gap(s, &litc, &lc, &mut ring, out,", "d_gap(s, &litc, &lc, &mut ring, &mut masks, &mut pmstate, out,", 1),
        ("d_cand(&lc, &dcc, dtab, &mut ring, get0(rs, j),", "d_cand(&lc, &dcc, dtab, &mut ring, &masks, &ends, &pmstate, get0(rs, j),", 1),
        ("            ring[p % D_RING] = best;", "            ring[p % D_RING] = best;\n            pm_publish(&ring, &mut masks, &mut pmstate, p);", 1),
    ]
    source = original
    for before, after, count in edits:
        assert source.count(before) == count, before[:90]
        source = source.replace(before, after)
    restored = source
    for before, after, count in reversed(edits):
        assert restored.count(after) == count
        restored = restored.replace(after, before)
    assert restored == original
    # All publication calls are the terminal, three final gap cells and final node.
    assert source.count("pm_publish(") == 6  # definition + five call sites
    files = {"parse.rs": source.encode(), "Parse.lean": raw["Parse.lean"]}
    manifest = {
        "candidate": NAME, "parent": "candidates/r10-record-nonempty", "base_submission_id": "361",
        "parent_hashes": parent["hashes"], "hashes": {n: sha(data) for n, data in files.items()},
        "bytes": {n: len(data) for n, data in files.items()}, "attribution": parent["attribution"],
        "verified_parent": "candidates/r10-record-nonempty/VERIFICATION.json",
        "mechanism": "Publish a 32-bit strict prefix-record mask at every finalized endpoint; constant-length-price segments use <=32 prefix queries and one endpoint read per nonsingleton chunk.",
        "differences_from_rmq8": "Arbitrary-alignment prefix queries avoid scalar edge fragments; rolling monotone-mask publication replaces aligned eight-cell rescans. Publication now occurs at every finalized byte and uses a larger 4KiB mask cache.",
        "local_reuse": "pm_price_ends is a renamed copy of the existing r10_price_ends helper in scripts/build-round10-rmq.py; original #361 attribution remains inherited. Other mask/getter/state/query helpers are new experiment code.",
        "tie_policy": "Pop earlier rolling records on cost>=new cost; masks compare upper32 endpoint cost only; queries select the highest low-prefix set bit, then packed cost/length minima preserve shortest global ties.",
        "publication": "Only terminal n, all three final d_gap writes and final d_dp node write. Never d_init or d_push. Nonconsecutive publication disables the cache for the rest of that DP call.",
        "fallback": "Original d_best_len for invalid ranges, invalid/unpublished state, position/domain mismatch, malformed run ends, empty masks or exhausted bounded progress. Singleton ranges/chunks use original d_bcost directly. len32 uses u32::MAX explicitly.",
        "bounds": "Publish loop fuel32; run loop fuel259; per-run chunk loop fuel9. Existing <=258 future query and <=255 pending-backward writes fit well inside D_RING1024; each snapshot reaches at most p+289.",
        "audit": "Fourteen exact reversible regions restore verified parent. Original forward parser, finder, model, routing, record payloads and emitter are unchanged; no costcache/pipeline/packing combination.",
        "model_reference": "evidence/round10/prefix-mask-review.json",
        "equivalence_status": "INFERRED exact endpoint minima with shortest ties; source recurrence model passed, but actual 444 token/decode checks and public same bytes are still required.",
        "proof_status": "UNADAPTED_PARENT_ONLY: new bounded helpers and extra D cache state/interfaces require actual extraction and original full obligation/axiom gate. No formal acceptance is claimed.",
        "performance_status": "UNKNOWN: every-byte publication, pop comparisons, 4KiB cache traffic and run-end loading can outweigh constant-query savings. Paired total-compression screen is mandatory before proof work.",
    }
    assert all(len(data) <= 524288 for data in files.values())
    files["manifest.json"] = (json.dumps(manifest, indent=2) + "\n").encode()
    return files


def model_check():
    rng = random.Random(321024259)
    max32 = (1 << 32) - 1
    max64 = (1 << 64) - 1
    totals = {"publications": 0, "queries": 0, "scalar_fallbacks": 0, "singleton_queries": 0, "pop_comparisons": 0, "block_changes": 0}
    for pattern in range(5):
        n = 2305
        costs = [7 if pattern == 0 else q if pattern == 1 else n - q if pattern == 2 else rng.choice([0, 1, 2, max32, rng.getrandbits(32)]) for q in range(n + 1)]
        costs[n] = 0
        ring = [0] * 1024; masks = [0] * 1024; state = [n, 0, 1, n]
        def publish(p):
            if state[2] != 1: return
            front, old = state[:2]
            if (old == 0 and p != front) or (old != 0 and ((p + 1) & max64) != front):
                state[2] = 0
                return
            cost = ring[p % 1024]
            m = (old << 1) & max32
            fuel = 32
            while m and fuel:
                fuel -= 1
                low = m & (((~m) & max32) + 1)
                offset = low.bit_length() - 1
                totals["pop_comparisons"] += 1
                if ring[(p + offset) % 1024] >= cost: m &= m - 1
                else: fuel = 0
            mask = m | 1
            masks[p % 1024] = mask; state[0] = p; state[1] = mask
            totals["publications"] += 1
        def scalar(lc, p, lo, e):
            if lo < e <= 259:
                value, length = min((ring[((p + l) & max64) % 1024] + lc[l % 512], l) for l in range(lo, e))
                return (value << 9) | length
            return min([(((ring[((p + l) & max64) % 1024] + lc[l % 512]) << 9) & max64) | l for l in range(lo, e)], default=max64)
        def query(lc, ends, p, lo, e):
            def fallback():
                totals["scalar_fallbacks"] += 1
                return scalar(lc, p, lo, e)
            if lo >= e or e > 259: return fallback()
            if e - lo == 1:
                totals["singleton_queries"] += 1
                return scalar(lc, p, lo, e)
            if lo < 3 or state[2] != 1 or p >= state[3] or e - 1 > state[3] - p or state[0] != ((p + 1) & max64): return fallback()
            best = max64; l = lo; runs = 259
            while l < e and runs:
                runs -= 1; raw_stop = ends[l % 512]
                if raw_stop <= l or raw_stop > 512: return fallback()
                stop = min(raw_stop, e); price = lc[l % 512]; chunks = 9
                while l < stop and chunks:
                    chunks -= 1; width = min(32, stop - l)
                    if width == 1: v = ((ring[(p + l) % 1024] + lc[l % 512]) << 9) | l
                    else:
                        a = p + l; keep = max32 if width == 32 else (1 << width) - 1
                        m = masks[a % 1024] & keep
                        offset = m.bit_length() - 1 if m else 32
                        if offset >= width: return fallback()
                        v = ((ring[(a + offset) % 1024] + price) << 9) | (l + offset)
                    best = min(best, v); l += width
                if l < stop: return fallback()
            return fallback() if l < e else best
        def prices(p):
            if pattern == 4: lc = [q % 2 for q in range(512)]
            elif p % 3 == 0: lc = [16] * 512
            else: lc = [((q // (1 + p % 32)) % 7) * 16 for q in range(512)]
            ends = [512] * 512; stop = 512
            for q in range(511, -1, -1):
                if q < 511 and lc[q] != lc[q + 1]: stop = q + 1
                ends[q] = stop
            return lc, ends
        ring[n % 1024] = 0; publish(n)
        lc, ends = prices(n)
        for p in range(n - 1, -1, -1):
            if p % 41 == 0: lc, ends = prices(p); totals["block_changes"] += 1
            for x in (1, 31, 127, 255):
                if p >= x: ring[(p - x) % 1024] = rng.getrandbits(32)
            room = min(258, n - p)
            if room >= 3:
                intervals = [(3, room + 1), (room, room + 1)]
                lo = rng.randrange(3, room + 1); intervals.append((lo, rng.randrange(lo + 1, room + 2)))
                for lo, e in intervals:
                    assert query(lc, ends, p, lo, e) == scalar(lc, p, lo, e)
                    totals["queries"] += 1
                if p % 127 == 0 and room >= 4:
                    at = (p + 3) % 1024; saved = masks[at]; masks[at] = 0
                    assert query(lc, ends, p, 3, 5) == scalar(lc, p, 3, 5); masks[at] = saved
                    invalid_ends = ends[:]; invalid_ends[3] = 3
                    assert query(lc, invalid_ends, p, 3, 5) == scalar(lc, p, 3, 5)
            ring[p % 1024] = costs[p]; publish(p)
        old_flag = state[2]; publish(7); assert old_flag == 1 and state[2] == 0
        for lo, e in [(3, 3), (9, 3), (3, 260), (0, 2), (3, 35), (8, 9)]:
            assert query(lc, ends, 0, lo, e) == scalar(lc, 0, lo, e)
    return {"status": "VERIFIED_EXACT_HELPER_MODEL", "random_seed": 321024259, "patterns": 5,
            "counts": totals, "scope": "Python translation of frozen helper control flow, including fuels, singleton paths, zero masks, bad ends, nonconsecutive disable and scalar fallbacks. No Rust execution or total-time claim.",
            "source_sha256": json.loads(generate()["manifest.json"])["hashes"]["parse.rs"]}


def main():
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument("--check", action="store_true")
    ap.add_argument("--model-check", action="store_true")
    args = ap.parse_args()
    files = generate()
    dest = ROOT / "candidates" / NAME
    if args.check:
        assert all((dest / n).read_bytes() == data for n, data in files.items())
    else:
        dest.mkdir(parents=True, exist_ok=True)
        for n, data in files.items():
            if (dest / n).exists() and (dest / n).read_bytes() != data:
                raise ValueError(f"preserve existing different file {dest / n}")
            (dest / n).write_bytes(data)
    print(json.dumps({"candidate": NAME, "hashes": json.loads(files["manifest.json"])["hashes"], "status": "UNADAPTED_PARENT_ONLY"}))
    if args.model_check:
        report = model_check()
        (dest / "helper-model-check.json").write_text(json.dumps(report, indent=2) + "\n")
        print(json.dumps({"status": report["status"], "counts": report["counts"]}))


if __name__ == "__main__":
    main()
