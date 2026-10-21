"""One static-cost profitability filter on the frozen one-pass lazy seed.

This tests short/far-match seed-statistics bias, not another pass/depth sweep.
The original parent proof stays explicitly unadapted; no CI is dispatched here.
"""
from pathlib import Path
import argparse
import hashlib
import json

ROOT = Path(__file__).resolve().parents[1]
BASE = ROOT / "candidates/r10-forward-lazyseed"
NAME = "r10-forward-costseed"


def sha(data):
    return hashlib.sha256(data).hexdigest()


PROFIT = r'''/// Strict static saving against literals, in the same 1/16-bit units.
/// Nonnegative literal prices make an early crossing sufficient for acceptance.
/// At most 258 u32 prices are added as u64, so the mathematical sum is <2^41.
#[inline(always)]
pub fn d_seed_profitable(input: &[u8], litc: &[u32; 256], p: usize, len: usize, match_cost: u64) -> bool {
    if len > 258 || p > input.len() || len > input.len() - p {
        return false;
    }
    let mut literal = 0u64;
    let mut j = 0usize;
    while j < len {
        literal = literal.wrapping_add(litc[input[p + j] as usize] as u64);
        if literal > match_cost {
            return true;
        }
        j += 1;
    }
    false
}

'''

INITIALIZE = '''    // A single static model uses the original strided histogram and match prior.
    let mut lsym = [0u8; 512];
    let mut dtab = [0u8; 512];
    fill_tables(&mut lsym, &mut dtab);
    let mut lf = [0u32; 320];
    let mut df = [0u32; 32];
    init_counts(input, &mut lf, &mut df);
    let mut litc = [0u32; 256];
    let mut lc = [0u32; 512];
    let mut dcc = [0u32; 32];
    make_costs(&lf, &df, &lsym, &mut litc, &mut lc, &mut dcc, 0);
'''


def generate():
    raw = {name: (BASE / name).read_bytes() for name in ("parse.rs", "Parse.lean")}
    parent = json.loads((BASE / "manifest.json").read_text())
    assert all(sha(data) == parent["hashes"][name] for name, data in raw.items())
    original = raw["parse.rs"].decode()
    a = original.index("pub fn d_seed(")
    b = original.index("// ── glue ──", a)
    old = original[a:b]
    anchor = "    let n = input.len();\n"
    assert old.count(anchor) == 1
    new = old.replace(anchor, anchor + INITIALIZE, 1)
    condition = "if left >= 3 && left <= 258 && left <= n - q && dist >= 1 && dist <= q && dist <= 32768 && !(D_SEED_LAZY > 0 && future > left + 1) {"
    replacement = "if left >= 3 && left <= 258 && left <= n - q && dist >= 1 && dist <= q && dist <= 32768 && !(D_SEED_LAZY > 0 && future > left + 1) && d_seed_profitable(input, &litc, q, left, (lc[left % 512] as u64).wrapping_add(dcc[dsym(&dtab, dist) % 32] as u64)) {"
    assert new.count(condition) == 1
    new = new.replace(condition, replacement, 1)
    source = original[:a] + PROFIT + new + original[b:]
    assert source.replace(PROFIT + new, old, 1) == original
    assert source.count("pub const D_SEED_LAZY: usize = 1;") == 1
    files = {"parse.rs": source.encode(), "Parse.lean": raw["Parse.lean"]}
    manifest = {
        "candidate": NAME, "parent": "candidates/r10-forward-lazyseed", "base_submission_id": "361",
        "parent_hashes": parent["hashes"], "hashes": {name: sha(data) for name, data in files.items()},
        "bytes": {name: len(data) for name, data in files.items()}, "attribution": parent["attribution"],
        "mechanism": "At a lazyseed token boundary, take its selected match only when static length+distance price is strictly below the literal price of the same span. Build one model via original fill_tables/init_counts/make_costs(huff=0).",
        "hypothesis": "Short distant matches can be worse than cheap literals and bias the greedy seed's block statistics; filter that mechanism directly without changing discovered matches or adding passes.",
        "price_units": "Original 1/16-bit entropy prices including length/distance extra bits; histogram and original match priors are retained.",
        "arithmetic": "Compare u64 match cost (two u32 values, <2^33) and u64 literal sum (at most258 u32 values, <2^41). Accept early only when accumulated nonnegative literal cost is already strictly greater. Ties remain literals.",
        "seed_lazy": 1, "backward_passes": 1,
        "audit": "Only one helper and the d_seed cost initialization/acceptance condition change. Reversing the region restores frozen lazyseed bytes. d_collect, rs, sparse map, active longest interval, one-byte lookahead, original routes, backward pass and emitters are byte-identical.",
        "equivalence_status": "Expected same original rs stream and valid complete seed; seed/final tokens intentionally may differ. Reuse forward diagnostics with candidate entry parameterized by the parent.",
        "proof_status": "UNADAPTED_PARENT_ONLY / UNKNOWN: copied original proof is not a proof of collect/seed/profitability helpers; seed-proof2 is also untested and not promoted.",
        "performance_status": "UNKNOWN: added one-time histogram/model work and per-accepted-match-prefix comparisons may outweigh size recovery. Require paired official axes and current projection better than verified record baseline before any full gate.",
    }
    assert all(len(data) <= 524288 for data in files.values())
    files["manifest.json"] = (json.dumps(manifest, indent=2) + "\n").encode()
    return files


def main():
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument("--check", action="store_true")
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


if __name__ == "__main__":
    main()
