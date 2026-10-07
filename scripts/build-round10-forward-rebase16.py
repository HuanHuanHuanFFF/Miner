"""Generate one D-only whole-matchfinder relative-u16/rebase experiment.

Reference: libdeflate 92e6a0d matchfinder_common.h and hc_matchfinder.h.
The original source uses signed positions and a strict distance cutoff; this
candidate preserves the parent's inclusive 32768 boundary with a 32767 shift.
No unsafe code, intrinsic, toolchain installation, CI or external submission.
"""
from pathlib import Path
import argparse
import hashlib
import json
import random

ROOT = Path(__file__).resolve().parents[1]
BASE = ROOT / "candidates/r9-block-scalar"
NAME = "r10-forward-rebase16"


def sha(data):
    return hashlib.sha256(data).hexdigest()


def once(text, old, new):
    assert text.count(old) == 1, old
    return text.replace(old, new, 1)


def function(source, name):
    a = source.index("pub fn " + name + "(")
    b = source.index("{", a) + 1
    depth = 1
    while depth:
        depth += (source[b] == "{") - (source[b] == "}")
        b += 1
    return source[a:b]


HELPERS = r'''/// Decode zero as the stale position base-1, or zero in the initial epoch.
/// Before the first rebase this also preserves the original default head at 0.
#[inline(always)]
pub fn rb16_abs(base: usize, code: u16) -> usize {
    base.wrapping_add(code as usize).saturating_sub(1)
}

/// Ordinary unsigned saturating subtraction; LLVM may vectorize this scan.
pub fn rb16_shift<const N: usize>(table: &mut [u16; N], shift: u16) {
    let mut j = 0usize;
    while j < N {
        table[j] = table[j].saturating_sub(shift);
        j += 1;
    }
}

/// Refresh all relative tables before a new coordinate would reach 65536.
/// Keeping q-32768 at code 1 retains the inclusive DEFLATE window boundary.
#[inline(always)]
pub fn rb16_rebase(head3: &mut [u16; H3N], head4: &mut [u16; H4N], prev4: &mut [u16; WN], head7: &mut [u16; H7N], prev7: &mut [u16; WN], base: &mut [usize; 1], q: usize) {
    if q.wrapping_sub(base[0]) >= 65535 {
        let next = q.saturating_sub(32768);
        let shift = next.saturating_sub(base[0]);
        let amount = if shift <= 65535 { shift as u16 } else { 65535u16 };
        rb16_shift(head3, amount);
        rb16_shift(head4, amount);
        rb16_shift(prev4, amount);
        rb16_shift(head7, amount);
        rb16_shift(prev7, amount);
        base[0] = next;
    }
}

/// One encoded current position is shared by all three head stores.
#[inline(always)]
pub fn rb16_insert_pos(head3: &mut [u16; H3N], head4: &mut [u16; H4N], prev4: &mut [u16; WN], head7: &mut [u16; H7N], prev7: &mut [u16; WN], base: &mut [usize; 1], q: usize, b8: u64, sh7: u32) -> (usize, usize, usize) {
    rb16_rebase(head3, head4, prev4, head7, prev7, base, q);
    let code = q.wrapping_sub(base[0]).wrapping_add(1) as u16;
    let x4 = (b8 >> 32) as u32;
    let h3 = hash3(x4 >> 8);
    let c3 = head3[h3];
    head3[h3] = code;
    let h4 = hash4(x4);
    let c4 = head4[h4];
    head4[h4] = code;
    prev4[q % WN] = c4;
    let h7 = hash7(b8 >> (sh7 % 64));
    let c7 = head7[h7];
    head7[h7] = code;
    prev7[q % WN] = c7;
    (rb16_abs(base[0], c3), rb16_abs(base[0], c4), rb16_abs(base[0], c7))
}

/// Rebase inside this loop as needed, including a taken match crossing an epoch.
#[inline(always)]
pub fn rb16_insert_range(input: &[u8], head3: &mut [u16; H3N], head4: &mut [u16; H4N], prev4: &mut [u16; WN], head7: &mut [u16; H7N], prev7: &mut [u16; WN], base: &mut [usize; 1], from: usize, to: usize, sh7: u32) {
    let mut q = from;
    while q < to {
        let bq = be8(input, q);
        rb16_insert_pos(head3, head4, prev4, head7, prev7, base, q, bq, sh7);
        q += 1;
    }
}

'''


def generate():
    raw = {n: (BASE / n).read_bytes() for n in ("parse.rs", "Parse.lean")}
    parent = json.loads((BASE / "manifest.json").read_text())
    assert all(sha(b) == parent["hashes"][n] for n, b in raw.items())
    original = raw["parse.rs"].decode()
    skip = function(original, "skip_same").replace("skip_same(", "rb16_skip_same(")
    skip = once(skip, "prev: &[u32; WN]", "prev: &[u16; WN]")
    skip = once(skip, "same: bool)", "same: bool, base: usize)")
    skip = once(skip, "let nx = prev[start % WN] as usize;", "let nx = rb16_abs(base, prev[start % WN]);")
    walk = function(original, "d_walk").replace("d_walk(", "rb16_walk(")
    walk = once(walk, "prev: &[u32; WN]", "prev: &[u16; WN]")
    walk = once(walk, "    nice: usize,\n", "    nice: usize,\n    base: usize,\n")
    walk = once(walk, "let nx = prev[c % WN] as usize;", "let nx = rb16_abs(base, prev[c % WN]);")
    parse = function(original, "d_parse").replace("pub fn d_parse(", "pub fn rb16_parse(")
    for name, size in (("head3", "H3N"), ("head4", "H4N"), ("prev4", "WN"), ("head7", "H7N"), ("prev7", "WN")):
        parse = once(parse, f"let mut {name} = [0u32; {size}];", f"let mut {name} = [0u16; {size}];")
    parse = once(parse, "    let n = input.len();\n", "    let n = input.len();\n    let mut rbbase = [0usize; 1];\n")
    parse = once(parse, "insert_pos(&mut head3, &mut head4, &mut prev4, &mut head7, &mut prev7, i, b8, sh7)",
                 "rb16_insert_pos(&mut head3, &mut head4, &mut prev4, &mut head7, &mut prev7, &mut rbbase, i, b8, sh7)")
    parse = once(parse, "insert_range(input, &mut head3, &mut head4, &mut prev4, &mut head7, &mut prev7, i + 1, end, sh7)",
                 "rb16_insert_range(input, &mut head3, &mut head4, &mut prev4, &mut head7, &mut prev7, &mut rbbase, i + 1, end, sh7)")
    parse = once(parse, "skip_same(&prev4, hc.1, d4, p3 && hc.1 == hc.0)", "rb16_skip_same(&prev4, hc.1, d4, p3 && hc.1 == hc.0, rbbase[0])")
    parse = once(parse, "skip_same(&prev7, hc.2, dep7, (p3 && hc.2 == hc.0) || (d4 > 0 && hc.2 == hc.1))",
                 "rb16_skip_same(&prev7, hc.2, dep7, (p3 && hc.2 == hc.0) || (d4 > 0 && hc.2 == hc.1), rbbase[0])")
    for channel, result in (("4", "s4"), ("7", "s7")):
        old = f"d_walk(input, &prev{channel}, i, {result}.0, {result}.1, b8, cap, &mut cands, nc, best, nice)"
        new = f"rb16_walk(input, &prev{channel}, i, {result}.0, {result}.1, b8, cap, &mut cands, nc, best, nice, rbbase[0])"
        parse = once(parse, old, new)
    extra = HELPERS + "#[inline(always)]\n" + skip + "\n\n#[inline(always)]\n" + walk + "\n\n" + parse + "\n\n"
    source = once(original, "// ── glue ──", extra + "// ── glue ──")
    call = "    d_parse(input, &mut plan, &mut rs, k[0], k[1], k[2], k[3], k[4], k[5], k[8], k[9], k[10], k[11], k[12], k[13], k[14], k[15]);"
    replacement = """    // Preserve the parent's u32 absolute-position truncation on inputs above 4 GiB.
    if n <= 4294967295 {
    """ + call.replace("d_parse(", "rb16_parse(") + "\n    } else {\n    " + call + "\n    }"
    source = once(source, call, replacement)
    assert source.replace(replacement, call, 1).replace(extra, "", 1) == original
    files = {"parse.rs": source.encode(), "Parse.lean": raw["Parse.lean"]}
    manifest = {
        "candidate": NAME, "parent": "candidates/r9-block-scalar", "base_submission_id": "361",
        "parent_hashes": parent["hashes"], "hashes": {n: sha(b) for n, b in files.items()},
        "bytes": {n: len(b) for n, b in files.items()}, "attribution": parent["attribution"],
        "mechanism": "For D inputs <=u32::MAX, all three heads and two predecessor arrays use u16 positions relative to a shared base. Rebase all five arrays by unsigned saturating subtraction before q-base reaches 65535. Original forward/backward planning is retained.",
        "encoding": "code=position-base+1; zero decodes to max(base-1,0). Rebase next=q-32768, normal shift=32767, preserving distance exactly 32768.",
        "fixed_finder_bytes_before": 851968, "fixed_finder_bytes_after": 425984,
        "ordinary_store_cost": "One current-position encoding shared across all heads; predecessor stores copy existing u16 codes, avoiding per-link distance calculations.",
        "rebase_cost": "212992 u16 cells scanned about every 32767 inserted bytes after the first 65535; nominal read+write traffic about 26 bytes per input byte, sequential. Actual vectorization and net time remain unmeasured.",
        "huge_input_fallback": "For input.len()>u32::MAX use byte-identical parent d_parse, preserving its truncated u32 head semantics.",
        "audit": "Original d_parse and all its helpers remain byte-identical. New rb16 helpers plus copied D parser are appended, and d_plan_k selects the new path only below the u32 limit. Search schedule, planning, record encoding, routes and checked emission are unchanged in intent.",
        "equivalence_status": "INFERRED: boundary state model and 444 Rust token/decode comparisons plus public output equality required. Representation equivalence is not assumed from libdeflate precedent.",
        "proof_status": "UNADAPTED_PARENT_ONLY: relative coordinate invariants, rebasing helpers and new call bridge need fresh extraction and original complete gate; copied proof is not validation.",
        "performance_status": "UNKNOWN: half-sized random-access state trades against periodic full-table scans and position decoding.",
    }
    assert all(len(b) <= 524288 for b in files.values())
    files["manifest.json"] = (json.dumps(manifest, indent=2) + "\n").encode()
    files["primary-source-reference.json"] = (json.dumps({
        "repo": "ebiggers/libdeflate", "commit": "92e6a0db9fa848d742f9eb286c92afc60f2c3dda",
        "read_utc_date": "2026-10-07", "files": [
            {"path": "lib/matchfinder_common.h", "sha256": "47199708cd30c44772fbaed3da4b34533541d6f33ffa7279651a137887756ab3", "bytes": 7032,
             "url": "https://github.com/ebiggers/libdeflate/blob/92e6a0db9fa848d742f9eb286c92afc60f2c3dda/lib/matchfinder_common.h", "relevant_lines": [47, 51, 118, 157]},
            {"path": "lib/hc_matchfinder.h", "sha256": "b37e8c48957f8d7773a847a1d5a5fe5343b85e0f9c43ddce2e55eb24d58a1704", "bytes": 13970,
             "url": "https://github.com/ebiggers/libdeflate/blob/92e6a0db9fa848d742f9eb286c92afc60f2c3dda/lib/hc_matchfinder.h", "relevant_lines": [143, 149, 200, 212, 270, 273, 379, 393]},
        ],
        "verified_mechanism": "Signed 16-bit matchfinder positions; whole head and link state slides together; architecture-specific implementations plus portable saturating fallback; skipped-byte insertion also handles rebasing.",
        "difference": "libdeflate's <=cutoff rejection excludes distance exactly WINDOW_SIZE. This candidate retains the parent's inclusive 32768 endpoint and uses unsigned nonzero encoding with shift32767, not a direct transplant.",
    }, indent=2) + "\n").encode()
    return files


def model_check():
    total_insertions = comparisons = boundaries = rebases = 0
    cases = []
    for window in (7, 16, 31, 32768):
        limit = 2 * window - 1
        for mode in range(4):
            heads = [[0] * 17 for _ in range(3)]
            rel_heads = [[0] * 17 for _ in range(3)]
            prev = [[0] * window for _ in range(2)]
            rel_prev = [[0] * window for _ in range(2)]
            base = 0
            rng = random.Random(927361 + 17 * window + mode)
            n = 8 * window + 19
            local_rebases = local_comparisons = 0
            def decode(code):
                return max(base + code - 1, 0)
            def visits(i, c, depth, table, compact):
                result = []
                while depth and 1 <= i - c <= window:
                    result.append(c)
                    nx = decode(table[c % window]) if compact else table[c % window]
                    if nx >= c:
                        break
                    c, depth = nx, depth - 1
                return result
            for i in range(n):
                if i - base >= limit:
                    next_base = i - window
                    shift = next_base - base
                    assert shift == window - 1
                    for table in rel_heads + rel_prev:
                        table[:] = [max(x - shift, 0) for x in table]
                    base = next_base
                    local_rebases += 1
                code = i - base + 1
                assert 1 <= code <= limit
                if mode == 0:
                    keys = [0, 0, 0]
                elif mode == 1:
                    keys = [i % 17, i % 17, (i // 3) % 17]
                elif mode == 2:
                    keys = [rng.randrange(17) for _ in range(3)]
                else:
                    keys = [0 if i % window < 4 else i % 17, (i % window) % 17, (i // 7) % 17]
                old_h = [heads[j][keys[j]] for j in range(3)]
                new_h = [decode(rel_heads[j][keys[j]]) for j in range(3)]
                for j in range(2):
                    prev[j][i % window] = old_h[j + 1]
                    rel_prev[j][i % window] = rel_heads[j + 1][keys[j + 1]]
                for j in range(3):
                    heads[j][keys[j]] = i
                    rel_heads[j][keys[j]] = code
                total_insertions += 1
                near_rebase = i < 2 * window + 4 or i - base < window + 4 or i - base > limit - 5
                if window == 32768 and not (i % 257 == 0 or (near_rebase and (i < 16 or i >= 2 * window - 5))):
                    continue
                for j in range(3):
                    assert old_h[j] == new_h[j] or (i - old_h[j] > window and i - new_h[j] > window)
                for channel in range(2):
                    for old_start, new_start in ((old_h[channel + 1], new_h[channel + 1]), (max(0, i - window), max(0, i - window))):
                        for depth in (1, 2, 7, 48):
                            a = visits(i, old_start, depth, prev[channel], False)
                            b = visits(i, new_start, depth, rel_prev[channel], True)
                            assert a == b, (window, mode, i, base, a, b)
                            boundaries += sum(i - c == window for c in a)
                            comparisons += 1
                            local_comparisons += 1
                            ax = prev[channel][old_start % window]
                            bx = decode(rel_prev[channel][new_start % window])
                            ac, ad = (ax, depth - 1) if ax < old_start else (old_start, 0)
                            bc, bd = (bx, depth - 1) if bx < new_start else (new_start, 0)
                            a = visits(i, ac, ad, prev[channel], False)
                            b = visits(i, bc, bd, rel_prev[channel], True)
                            assert a == b, ("skip", window, mode, i, base, old_start, new_start, a, b)
                            comparisons += 1
                            local_comparisons += 1
                # Range insertion is exactly these same calls at every byte;
                # query suppression across a range never suppresses this rebase.
            rebases += local_rebases
            cases.append({"window": window, "mode": mode, "insertions": n, "rebases": local_rebases, "comparisons": local_comparisons})
    return {"status": "VERIFIED_FINITE_REBASE_MODEL", "scope": "Python model, complete inserts with sampled queries for W32768; no Rust token or universal-equivalence claim",
            "insertions": total_insertions, "comparisons": comparisons, "rebases": rebases, "exact_window_boundary_visits": boundaries,
            "cases": cases, "source_sha256": json.loads(generate()["manifest.json"])["hashes"]["parse.rs"]}


def main():
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument("--check", action="store_true")
    ap.add_argument("--model-check", action="store_true")
    args = ap.parse_args()
    files = generate()
    dest = ROOT / "candidates" / NAME
    if args.check:
        assert all((dest / n).read_bytes() == b for n, b in files.items())
    else:
        dest.mkdir(parents=True, exist_ok=True)
        for n, b in files.items():
            if (dest / n).exists() and (dest / n).read_bytes() != b:
                raise ValueError(f"preserve existing different file {dest / n}")
            (dest / n).write_bytes(b)
    print(json.dumps({"candidate": NAME, "hashes": json.loads(files["manifest.json"])["hashes"], "status": "UNADAPTED_PARENT_ONLY"}))
    if args.model_check:
        report = model_check()
        (dest / "rebase-model-check.json").write_text(json.dumps(report, indent=2) + "\n")
        print(json.dumps({k: v for k, v in report.items() if k != "cases"}))


if __name__ == "__main__":
    main()
