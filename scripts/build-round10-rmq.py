"""R10 bounded range-minimum experiment for the recorded backward planner.

This is a combinable alternative, not a claim that backward work alone can
cross the frontier. The parent proof is explicitly unadapted until a fresh gate.
"""
from pathlib import Path
import argparse
import hashlib
import json

ROOT = Path(__file__).resolve().parents[1]
BASE = ROOT / 'candidates/r9-block-scalar'

HELPERS = r'''/// Price-run endpoints, rebuilt only when a block's length prices change.
pub fn r10_price_ends(lc: &[u32; 512], ends: &mut [u16; 512]) {
    let mut q = 512usize;
    let mut stop = 512usize;
    while q > 0 {
        q -= 1;
        if q < 511 && lc[q] != lc[q + 1] { stop = q + 1; }
        ends[q] = stop as u16;
    }
}

/// Once the low end of an aligned group is final, summarize its eight prices.
/// Low bits retain the earliest endpoint on ties. Backward pushes reach only
/// not-yet-final positions and cannot change this future group in the DP sweep.
#[inline(always)]
pub fn r10_min8_commit(ring: &[u64; D_RING], mins: &mut [u64; 128], p: usize) {
    if p % 8 == 0 {
        let mut best = 0xFFFF_FFFF_FFFF_FFFFu64;
        let mut k = 0usize;
        while k < 8 {
            let v = ((ring[p.wrapping_add(k) % D_RING] >> 32) << 3) | k as u64;
            if v < best { best = v; }
            k += 1;
        }
        mins[(p / 8) % 128] = best;
    }
}

/// Exact scalar tails plus eight-endpoint summaries inside constant-price runs.
#[inline(always)]
pub fn r10_best_len(lc: &[u32; 512], ring: &[u64; D_RING], mins: &[u64; 128],
    ends: &[u16; 512], p: usize, lo: usize, e: usize) -> u64 {
    if lo >= e || e > 259 { return d_best_len(lc, ring, p, lo, e); }
    let mut best = 0xFFFF_FFFF_FFFF_FFFFu64;
    let mut l = lo;
    while l < e {
        let raw_stop = ends[l % 512] as usize;
        let stop = if raw_stop > l { if raw_stop < e { raw_stop } else { e } } else { l + 1 };
        let price = lc[l % 512] as u64;
        while l < stop {
            let q = p.wrapping_add(l);
            let v;
            if q % 8 == 0 && stop - l >= 8 {
                let m = mins[(q / 8) % 128];
                v = ((m >> 3).wrapping_add(price) << 9) | (l + (m % 8) as usize) as u64;
                l += 8;
            } else {
                v = ((ring[q % D_RING] >> 32).wrapping_add(price) << 9) | l as u64;
                l += 1;
            }
            if v < best { best = v; }
        }
    }
    best
}

'''


def replace(text, old, new, count=1):
    assert text.count(old) == count, (old[:90], text.count(old), count)
    return text.replace(old, new)


def source_variant(source):
    s = replace(source, 'pub fn d_gap(', HELPERS + 'pub fn d_gap(')
    s = replace(s, 'ring: &mut [u64; D_RING], out: &mut [u32], hi: usize,',
                'ring: &mut [u64; D_RING], mins: &mut [u64; 128], out: &mut [u32], hi: usize,')
    s = replace(s, '        ring[q % D_RING] = v;\n        out[q] = v as u32;',
                '        ring[q % D_RING] = v;\n        r10_min8_commit(ring, mins, q);\n        out[q] = v as u32;', 3)
    s = replace(s, 'ring: &mut [u64; D_RING], r: u32, p: usize, prev: usize,',
                'ring: &mut [u64; D_RING], mins: &[u64; 128], ends: &[u16; 512], r: u32, p: usize, prev: usize,')
    s = replace(s, 'let bb = d_best_len(lc, ring, p, prev + 1, len + 1);',
                'let bb = r10_best_len(lc, ring, mins, ends, p, prev + 1, len + 1);')
    s = replace(s, 'dcc: &mut [u32; 32], bs: &mut [usize; 2], pos: usize)',
                'dcc: &mut [u32; 32], ends: &mut [u16; 512], bs: &mut [usize; 2], pos: usize)')
    s = replace(s, '        d_load(tabs, b.wrapping_mul(D_TS), litc, lc, dcc);',
                '        d_load(tabs, b.wrapping_mul(D_TS), litc, lc, dcc);\n        r10_price_ends(lc, ends);')
    s = replace(s, '    let mut ring = [D_UNSET; D_RING];',
                '    let mut ring = [D_UNSET; D_RING];\n    let mut mins = [0u64; 128];\n    let mut ends = [0u16; 512];')
    s = replace(s, '    ring[n % D_RING] = 0;',
                '    ring[n % D_RING] = 0;\n    r10_min8_commit(&ring, &mut mins, n);')
    s = replace(s, '    d_load(tabs, b0.wrapping_mul(D_TS), &mut litc, &mut lc, &mut dcc);',
                '    d_load(tabs, b0.wrapping_mul(D_TS), &mut litc, &mut lc, &mut dcc);\n    r10_price_ends(&lc, &mut ends);')
    s = replace(s, 'd_block(tabs, bstart, &mut litc, &mut lc, &mut dcc, &mut bs,',
                'd_block(tabs, bstart, &mut litc, &mut lc, &mut dcc, &mut ends, &mut bs,', 2)
    s = replace(s, 'd_gap(s, &litc, &lc, &mut ring, out,',
                'd_gap(s, &litc, &lc, &mut ring, &mut mins, out,')
    s = replace(s, 'd_cand(&lc, &dcc, dtab, &mut ring, get0(rs, j),',
                'd_cand(&lc, &dcc, dtab, &mut ring, &mins, &ends, get0(rs, j),')
    s = replace(s, '            ring[p % D_RING] = best;',
                '            ring[p % D_RING] = best;\n            r10_min8_commit(&ring, &mut mins, p);')
    return s


def main():
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument('--check', action='store_true')
    args = ap.parse_args()
    raw = {f: (BASE / f).read_bytes() for f in ['parse.rs', 'Parse.lean']}
    parent = json.loads((BASE / 'manifest.json').read_text())
    assert all(hashlib.sha256(b).hexdigest() == parent['hashes'][f] for f, b in raw.items())
    files = {'parse.rs': source_variant(raw['parse.rs'].decode()).encode(), 'Parse.lean': raw['Parse.lean']}
    manifest = {'candidate': 'r10-rmq8', 'parent': 'candidates/r9-block-scalar',
                'parent_hashes': parent['hashes'], 'attribution': parent.get('attribution', 'Original #361 attribution retained in parent manifest'),
                'hashes': {f: hashlib.sha256(b).hexdigest() for f, b in files.items()},
                'mechanism': 'Finalize aligned eight-position minima during backward sweep; query summaries only inside actual constant-length-price runs. Scalar edges preserve shortest-endpoint tie order.',
                'hypothesis': 'Saving repeated endpoint-price reads may beat one extra summary construction per eight finalized positions; benefit and output equality unmeasured.',
                'proof_status': 'UNADAPTED_PARENT_DRAFT; helper totality and changed D interfaces require fresh official extraction and full gate.',
                'performance_status': 'NOT_RUN',
                'falsifier': 'Any finite output mismatch rejects equivalence claim; no stable paired total-time gain stops this combinable optimization.'}
    files['manifest.json'] = (json.dumps(manifest, indent=2) + '\n').encode()
    target = ROOT / 'candidates/r10-rmq8'
    target.mkdir(exist_ok=True)
    for f, b in files.items():
        assert len(b) <= 524288
        if args.check:
            assert (target / f).read_bytes() == b
        else:
            assert not (target / f).exists() or (target / f).read_bytes() == b
            (target / f).write_bytes(b)
    print(json.dumps(manifest))


if __name__ == '__main__':
    main()
