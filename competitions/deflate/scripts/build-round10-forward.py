"""Generate R10 forward-planning structural experiments from verified scalar.

The copied Lean file is an UNVERIFIED parent proof, not a proof of the new
planner. Screen and extract before spending time on the missing totality bridge.
No CI, submission, toolchain installation, or external operation is performed.
"""
from pathlib import Path
import argparse
import hashlib
import json
import re

ROOT = Path(__file__).resolve().parents[1]
BASE = ROOT / "candidates/r9-block-scalar"


def sha(data):
    return hashlib.sha256(data).hexdigest()


def once(text, old, new):
    assert text.count(old) == 1, old[:100]
    return text.replace(old, new, 1)


def collector(source):
    begin = source.index("pub fn d_parse(")
    end = source.index("// ── glue ──", begin)
    text = source[begin:end]
    text = once(text, "pub fn d_parse(", "pub fn d_collect(")
    text = once(text, "    let huff = 0usize;\n", "")
    a = text.index("    let mut pa = [UNREACHED; RING];")
    b = text.index("    let lim = n - 8;", a)
    text = text[:a] + text[b:]
    text = once(text, "    let mut s = 0usize;\n    open_chunk(&mut pa, 0);\n    let mut next_upd = UPD;\n", "")
    text = once(text, "    let mut cdc = 0u32;\n", "")
    text = once(text, "        if i > s {\n            pa[(i + 258) % RING] = UNREACHED;\n        }\n", "")
    text = once(text, "        let base = (pa[i % RING] >> 32) as u32;\n        relax_one(&mut pa, i + 1, base.wrapping_add(litc[(b8 >> 56) as usize % 256]), 0);\n", "")
    text = once(text, "            relax_one(&mut pa, i + cl, base.wrapping_add(cdc).wrapping_add(lc[cl % 512]), ((cd as u32) << 9) | cl as u32);\n", "")
    text = once(text, "            let pcd = if cl >= 3 { cd } else { 0 };\n", "")
    text = once(text, "                cdc = dcc[dsym(&dtab, cd) % 32];\n", "")
    a = text.index("                let c0 = cands[(nc - 1) % 16];")
    b = text.index("                let mut end = i + l0;", a)
    text = text[:a] + "                let l0 = best;\n" + text[b:]
    text = once(text, "                s = i;\n", "")
    text = once(text, "                open_chunk(&mut pa, s);\n", "")
    text = once(text, "                d_relax(input, &mut pa, &cands, nc, &lc, &nextl, &dtab, &dcc, i, s, base, pcd, fback);\n", "")
    a = text.index("        if i - s >= CHUNK {")
    text = text[:a] + "    }\n}\n\n"
    assert all(word not in text for word in ("backtrack(", "relax_one(", "make_costs(", "update_costs(", "open_chunk(", "d_relax("))
    return "/// Collect exactly the original D search stream without its forward price planner.\n" + text


SEED = r'''/// Keep the longest interval at a start; equal lengths prefer the nearer distance.
#[inline(always)]
pub fn d_seed_put(out: &mut [u32], p: usize, len: usize, dist: usize) {
    if p < out.len() && len >= 3 && len <= 258 && len <= out.len() - p && dist >= 1 && dist <= 32768 && dist <= p {
        let old = out[p];
        let ol = (old % 512) as usize;
        let od = (old >> 9) as usize;
        if len > ol || (len == ol && dist < od) {
            out[p] = ((dist as u32) << 9) | len as u32;
        }
    }
}

/// Reuse the caller's positional output as a sparse longest-match scratch map.
/// Every recorded candidate contributes its ordinary and maximal backward start.
pub fn d_seed_map(rs: &[u32], out: &mut [u32], n: usize) {
    let mut q = 0usize;
    while q < n && q < out.len() {
        out[q] = 0;
        q += 1;
    }
    let mut e = rs.len();
    while e >= 2 {
        let k = get0(rs, e - 1) as usize;
        let p = get0(rs, e - 2) as usize;
        if k > e - 2 {
            e = 0;
        } else {
            let a = e - 2 - k;
            let mut j = a;
            while j < e - 2 {
                let r = get0(rs, j);
                let len = (r % 512) as usize;
                let dist = ((r >> 9) % 32768) as usize + 1;
                let t = (r >> 24) as usize;
                d_seed_put(out, p, len, dist);
                if t <= p && len <= 258 && t <= 258 - len {
                    d_seed_put(out, p - t, len + t, dist);
                }
                j += 1;
            }
            e = a;
        }
    }
}

/// Cheap initial block statistics: sweep recorded intervals and greedily consume
/// their longest valid continuation. The optional one-byte lazy decision uses
/// only the sparse map already built, without another matchfinder query.
pub fn d_seed(input: &[u8], rs: &[u32], out: &mut [u32], plan: &mut Vec<u32>) {
    let n = input.len();
    d_seed_map(rs, out, n);
    let mut q = 0usize;
    let mut end = 0usize;
    let mut dist = 0usize;
    let mut next = 0usize;
    while q < n && q < out.len() {
        let c = out[q];
        let len = (c % 512) as usize;
        let d = (c >> 9) as usize;
        if len >= 3 && len <= n - q && d >= 1 && d <= q && d <= 32768 {
            let stop = q + len;
            if stop > end || (stop == end && d < dist) {
                end = stop;
                dist = d;
            }
        }
        if q == next && plan.len() < n {
            let left = end.saturating_sub(q);
            let future = (get0(out, q.wrapping_add(1)) % 512) as usize;
            if left >= 3 && left <= 258 && left <= n - q && dist >= 1 && dist <= q && dist <= 32768 && !(D_SEED_LAZY > 0 && future > left + 1) {
                plan.push(((dist as u32) << 9) | left as u32);
                next = q + left;
            } else {
                plan.push(0);
                next = q + 1;
            }
        }
        q += 1;
    }
}

'''


def generate(lazy, passes=1):
    raw = {name: (BASE / name).read_bytes() for name in ("parse.rs", "Parse.lean")}
    parent = json.loads((BASE / "manifest.json").read_text())
    assert all(sha(raw[n]) == parent["hashes"][n] for n in raw)
    source = raw["parse.rs"].decode()
    extra = f"pub const D_SEED_LAZY: usize = {lazy};\n\n" + collector(source) + SEED
    source = once(source, "// ── glue ──", extra + "// ── glue ──")
    call = "    d_parse(input, &mut plan, &mut rs, k[0], k[1], k[2], k[3], k[4], k[5], k[8], k[9], k[10], k[11], k[12], k[13], k[14], k[15]);"
    source = once(source, call, call.replace("d_parse(", "d_collect(") + "\n    d_seed(input, &rs, out, &mut plan);")
    name = "r10-forward-lazyseed" if lazy else "r10-forward-seed"
    if passes == 2:
        assert lazy == 0
        name = "r10-forward-seed2"
        a = source.index("pub const D_KNOBS:")
        b = source.index("\n];", a)
        table = source[a:b]
        def row(match):
            values = [int(v.strip()) for v in match.group(1).split(",")]
            assert len(values) == 17
            values[6] = 2
            return "[" + ", ".join(map(str, values)) + "]"
        new_table, count = re.subn(r"\[([0-9, ]+)\]", row, table)
        assert count == 16
        source = source[:a] + new_table + source[b:]
    files = {"parse.rs": source.encode(), "Parse.lean": raw["Parse.lean"]}
    manifest = {
        "candidate": name,
        "parent": "candidates/r9-block-scalar",
        "base_submission_id": "361",
        "parent_hashes": parent["hashes"],
        "hashes": {n: sha(b) for n, b in files.items()},
        "bytes": {n: len(b) for n, b in files.items()},
        "attribution": parent["attribution"],
        "mechanism": "Remove the first forward price planner while retaining D's original search schedule and candidate stream. Build greedy block statistics from recorded intervals, then run the unchanged scalar backward DP.",
        "seed_lazy": lazy,
        "backward_passes": passes,
        "seed_uses_backward_endpoints": True,
        "audit": "Original d_parse remains byte-identical and callable as a diagnostic reference. Only d_plan_k calls new d_collect and d_seed; router, finder, recording, backward planner, emitters and encoder are unchanged.",
        "equivalence_status": "INFERRED exact rs stream; final tokens intentionally may differ. Fresh rs differential and decode/public round trip required.",
        "proof_status": "UNVERIFIED_PARENT_ONLY: Parse.lean is copied verbatim. New d_collect/d_seed totality and changed d_plan_k bridge are missing; do not run or label a successful gate until completed.",
        "performance_status": "UNKNOWN: no Rust runtime or paired total-compression result locally. Public screen plus independent confirmation required.",
    }
    assert all(len(b) <= 524288 for b in files.values())
    files["manifest.json"] = (json.dumps(manifest, indent=2) + "\n").encode()
    return name, files


def main():
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument("--check", action="store_true")
    args = ap.parse_args()
    for lazy, passes in ((0, 1), (1, 1), (0, 2)):
        name, files = generate(lazy, passes)
        dest = ROOT / "candidates" / name
        if args.check:
            assert all((dest / n).read_bytes() == data for n, data in files.items())
        else:
            dest.mkdir(parents=True, exist_ok=True)
            for n, data in files.items():
                if (dest / n).exists() and (dest / n).read_bytes() != data:
                    raise ValueError(f"preserve existing different file {dest / n}")
                (dest / n).write_bytes(data)
        print(json.dumps({"candidate": name, "hashes": json.loads(files["manifest.json"])["hashes"], "status": "UNVERIFIED_PARENT_ONLY"}))


if __name__ == "__main__":
    main()
