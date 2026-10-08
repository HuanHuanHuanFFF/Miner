"""One supplemental D query at the true long-jump endpoint minus two.

Keep first-pass plan, original query schedule and all insertions unchanged.
Only the recorded candidate stream grows; final tokens intentionally may differ.
"""
from pathlib import Path
import argparse
import hashlib
import json

ROOT = Path(__file__).resolve().parents[1]
BASE = ROOT / "candidates/r9-block-scalar"
NAME = "r10-forward-endprobe"


def sha(data):
    return hashlib.sha256(data).hexdigest()


HELPERS = r'''/// Search one already-inserted jump-tail position with its pre-insertion heads.
/// This touches only local candidates and rs, never the original forward plan.
#[inline(always)]
pub fn ep_search(input: &[u8], rs: &mut Vec<u32>, prev4: &[u32; WN], prev7: &[u32; WN], i: usize, h3: usize, h4: usize, h7: usize, b8: u64, d4: usize, d7: usize, h3d: usize, nice: usize, tbmax: usize, dupmode: usize) {
    if i >= input.len().saturating_sub(8) {
        return;
    }
    let mut cap = input.len() - i;
    if cap > 258 {
        cap = 258;
    }
    let mut cands = [0u32; 16];
    let mut nc = 0usize;
    let mut best = 2usize;
    let d3 = i.wrapping_sub(h3);
    let p3 = d3.wrapping_sub(1) < h3d;
    if p3 {
        let l3 = probe(input, h3, i, b8, cap, 2);
        if l3 > 0 {
            cands[0] = (l3 as u32) | ((d3 as u32) << 9);
            nc = 1;
            best = l3;
        }
    }
    let s4 = skip_same(prev4, h4, d4, p3 && h4 == h3);
    let w = d_walk(input, prev4, i, s4.0, s4.1, b8, cap, &mut cands, nc, best, nice);
    nc = w.0;
    best = w.1;
    let dep7 = if best >= 4 || d4 == 0 { d7 } else { 0 };
    let s7 = skip_same(prev7, h7, dep7, (p3 && h7 == h3) || (d4 > 0 && h7 == h4));
    let w2 = d_walk(input, prev7, i, s7.0, s7.1, b8, cap, &mut cands, nc, best, nice);
    nc = w2.0;
    if nc > 0 {
        // No >=3 continuation from the old jump remains here. The original pc
        // and ppos are deliberately untouched; no duplicate suppression applies.
        d_record(input, rs, &cands, nc, i, &cands, 0, i, 0, 0, tbmax, dupmode);
    }
}

/// Exact original insertion loop with one bounded extra query at true_end-2.
/// The head snapshot is captured at that position, before any future insertion.
#[inline(always)]
pub fn ep_insert_range(input: &[u8], head3: &mut [u32; H3N], head4: &mut [u32; H4N], prev4: &mut [u32; WN], head7: &mut [u32; H7N], prev7: &mut [u32; WN], rs: &mut Vec<u32>, from: usize, to: usize, sh7: u32, true_end: usize, d4: usize, d7: usize, h3d: usize, nice: usize, tbmax: usize, dupmode: usize) {
    let target = true_end.saturating_sub(2);
    let mut q = from;
    while q < to {
        let bq = be8(input, q);
        let hc = insert_pos(head3, head4, prev4, head7, prev7, q, bq, sh7);
        if q == target {
            ep_search(input, rs, prev4, prev7, q, hc.0, hc.1, hc.2, bq, d4, d7, h3d, nice, tbmax, dupmode);
        }
        q += 1;
    }
}

'''


def generate():
    raw = {n: (BASE / n).read_bytes() for n in ("parse.rs", "Parse.lean")}
    parent = json.loads((BASE / "manifest.json").read_text())
    assert all(sha(b) == parent["hashes"][n] for n, b in raw.items())
    original = raw["parse.rs"].decode()
    a = original.index("pub fn d_parse(")
    b = original.index("// ── glue ──", a)
    old = original[a:b]
    call = "insert_range(input, &mut head3, &mut head4, &mut prev4, &mut head7, &mut prev7, i + 1, end, sh7);"
    replacement = "ep_insert_range(input, &mut head3, &mut head4, &mut prev4, &mut head7, &mut prev7, rs, i + 1, end, sh7, i + l0, d4, d7, h3d, nice, tbmax, dupmode);"
    assert old.count(call) == 1
    new = old.replace(call, replacement, 1)
    source = original[:a] + HELPERS + new + original[b:]
    assert source.replace(HELPERS + new, old, 1) == original
    files = {"parse.rs": source.encode(), "Parse.lean": raw["Parse.lean"]}
    manifest = {
        "candidate": NAME, "parent": "candidates/r9-block-scalar", "base_submission_id": "361",
        "parent_hashes": parent["hashes"], "hashes": {n: sha(data) for n, data in files.items()},
        "bytes": {n: len(data) for n, data in files.items()}, "attribution": parent["attribution"],
        "mechanism": "At each original D long jump, one extra query at true_end-2 inside the unchanged position-insertion loop; append only nonempty candidate records. No new matchfinder table or extra preprocessing pass.",
        "budget": "Use existing d4,d7,h3d,nice values at this one position. Original search and skip parameters are unchanged. Candidate backward extension uses the existing tbmax.",
        "state_isolation": "The supplementary query reads existing prev arrays and pre-insertion head snapshots; it changes only rs. Original cands, pc, pn, ppos, pa, costs, first plan, and future search schedule remain untouched.",
        "continuation_argument": "The old longest continuation has only two bytes left at true_end-2. Splitting the old gap there retains every original >=3 continuation at positions <=true_end-3. Other DP interactions and encoded size still require measurement; no size-monotonicity claim.",
        "audit": "One call replacement inside d_parse plus two helpers. Reversing that region exactly restores scalar. Every insertion still calls original insert_pos once in the original order.",
        "equivalence_status": "Expected first-plan identity and ordered preservation of original rs node payloads; final tokens intentionally may differ. Fresh byte-valid extra-record and decode diagnostics required.",
        "proof_status": "UNADAPTED_PARENT_ONLY: new helpers and changed rs mutation require fresh extraction and original totality/obligation/axiom gate.",
        "performance_status": "UNKNOWN: extra bounded search and recording may improve available parse edges but can cost more total compression time or produce worse encoded blocks.",
    }
    assert all(len(b) <= 524288 for b in files.values())
    files["manifest.json"] = (json.dumps(manifest, indent=2) + "\n").encode()
    return files


def main():
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument("--check", action="store_true")
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


if __name__ == "__main__":
    main()
