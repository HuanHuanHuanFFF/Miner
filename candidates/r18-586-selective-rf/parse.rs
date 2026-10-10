//! Combined LZ77 parse for the fixed DEFLATE encoder: one content router, four planners, two
//! emission loops.
//!
//! `parse` takes the input's routing class (`route_class`: `classify`'s byte-class shares over 32
//! sampled windows of 1 KiB, with multi-byte text split off default text by its share of bytes >= 128,
//! the tiny inputs split by size and prose split off default text by `prose_like`) and looks it up in
//! `CLASS_TAB`: an engine and a row of that engine's knob table.
//! * Engine 0, S's planners (`s_plan`, a row of `CFG`): engine A (text: block-exact rounds of backward
//!   dynamic programming over a whole-input match cache) or engine C (DNA and binary data). They write
//!   a POSITIONAL plan (`plan[p] = len + 512 * dist` for position `p`, `len < 3` a literal).
//! * Engine 1, the forward dynamic program (`dp_plan`, a row of `DP_KNOBS`). Its plan is a TOKEN LIST
//!   (entry k = the k-th planned token, `len | dist << 9`, 0 for a literal).
//! * Engine 2, engine D (`d_plan`, a row of `D_KNOBS`): the forward dynamic program with every searched
//!   position recorded, then a backward shortest path under per-encoder-block Huffman-length costs
//!   over the recorded candidates (see its section). Its plan is a token list too.
//! Every planner is untrusted search code: it only has to be total, because phase 2 re-checks every
//! planned match.
//!
//! Forward dynamic program, phase 1 (`dp_parse`). One forward pass; every position is inserted into
//! three tables (nearest earlier 3-byte match, hash chain on 4-byte keys, hash chain on KB7-byte keys).
//! A position is searched when the continuation of the current match (the previous position's longest
//! candidate, one shorter) is shorter than `ct`, and at the `lazyn` positions after the one that found
//! the current match. A search takes the nearest 3-byte match (up to `h3d` back), `d4` steps of the
//! 4-byte chain and `d7` steps of the long chain (a chain head equal to a position already probed is
//! stepped over), keeping candidates longer than all closer ones; the continuation joins them. A
//! forward dynamic program over a ring of prices (price << 32 | choice) relaxes the literal, every
//! length of every candidate and each candidate extended backwards (up to TMAX bytes, the cheapest
//! start taking the whole match, and its shorter lengths from that start). Unsearched positions relax
//! the literal and the continuation's full length. A candidate at least `skip` long is taken as is
//! (extended backwards); the positions it covers are only inserted. The path is backtracked every
//! CHUNK positions into the plan. Symbol costs (1/16 bit) come from running counts of the backtracked
//! symbols, rebuilt every UPD positions and halved above HALF_AT: entropy costs, or Huffman code
//! lengths (`huff_costs`) with the knob `huff` = 1.
//!
//! Phase 2. `emit` (token lists) reads plan entry k for the k-th planned token and writes a planned
//! match only if `check` finds it in range and `mlen` (8 bytes at a time) confirms every byte; a
//! rejected match is written as literals over its planned length, so the plan stays aligned.
//! `emit_pos` (positional plans) reads the entry of the current position and applies the same `check`.
//! Tokens: t < 256 literal, else 2^24 + (dist-1)*256 + (len-3).

// ════════════════════ tables: BEGIN (written by tools/build.py from a table spec; constant values only) ════════════════════
// table set: d3020 (ba4a346e3d35)

/// Classifier splits. A tiny input (below 32 KiB) is class 14 below TINY_SPLIT bytes and class 0 from there on.
pub const TINY_SPLIT: usize = 20000;
/// Default text with at least MB_HI/1000 of the sampled bytes >= 128 is class 13 (multi-byte text).
pub const MB_HI: usize = 148;
/// Default text whose strided sample has at least PROSE_W/1024 letters and spaces and at most PROSE_S/1024
/// code symbols is class 15 (prose). PROSE_W above 1024 switches this split and its sampling off.
pub const PROSE_W: usize = 878;
pub const PROSE_S: usize = 16;

/// Routing class -> [engine, knob row]. Engine 6: the binary-tree parse of #109 (`x32b_parse`). Engine 2: engine D (row of D_KNOBS), 1: the forward dynamic program
/// (row of DP_KNOBS), anything else: S's planners (row of CFG; engine A or C as the row says).
pub const CLASS_TAB: [[usize; 2]; 32] = [[2, 0], [0, 0], [3, 1], [0, 1], [0, 2], [0, 3], [2, 1], [2, 2], [0, 4], [2, 3], [2, 4], [0, 5], [0, 6], [0, 7], [2, 5], [0, 3], [0, 8], [0, 9], [0, 10], [0, 11], [0, 12], [0, 8], [0, 13], [0, 14], [5, 0], [4, 0], [0, 15], [3, 0], [3, 0], [6, 0], [0, 6], [0, 6]];

/// S's engine configurations: [engine, knobs...]. Engine 0 = A (depth, skip, first passes, first
/// sampled, passes, sampled), anything else = C (depth, lower-case depth, weights DP, weights passes,
/// tree passes, DNA passes, DNA min passes, chain4 passes).
pub const CFG: [[usize; 9]; 16] = [[2, 32, 32, 1, 3, 2, 20, 12, 3], [2, 32, 32, 1, 3, 2, 21, 12, 3], [0, 48, 260, 6, 4, 5, 274, 0, 0], [0, 64, 260, 10, 8, 7, 21, 0, 0], [0, 16, 260, 8, 6, 5, 4, 0, 0], [0, 16, 260, 8, 6, 4, 2, 0, 0], [0, 48, 256, 10, 8, 5, 19, 0, 0], [0, 64, 260, 8, 6, 6, 21, 0, 0], [0, 48, 260, 8, 6, 6, 20, 0, 0], [0, 48, 260, 10, 8, 6, 20, 0, 0], [0, 32, 1024, 8, 6, 4, 530, 0, 0], [0, 12, 256, 10, 8, 5, 19, 0, 0], [0, 18, 260, 12, 10, 6, 20, 0, 0], [0, 64, 260, 8, 6, 7, 21, 0, 0], [0, 96, 260, 6, 4, 6, 20, 0, 0], [2, 4, 24, 1, 4, 2, 12, 7, 4]];

/// Knob rows of the forward dynamic program: [ct (continuation threshold), lazy positions searched, d4 and d7
/// (chain depths), skip (take-as-is length), h3 distance, huff (1 = Huffman-length costs)].
pub const DP_KNOBS: [[usize; 7]; 16] = [
    [4, 3, 2, 32, 64, 32768, 0],
    [4, 3, 2, 32, 64, 32768, 0],
    [4, 3, 2, 32, 64, 32768, 0],
    [4, 3, 2, 32, 64, 32768, 0],
    [4, 3, 2, 32, 64, 32768, 0],
    [4, 3, 2, 32, 64, 32768, 0],
    [4, 3, 2, 32, 64, 32768, 0],
    [4, 3, 2, 32, 64, 32768, 0],
    [4, 3, 2, 32, 64, 32768, 0],
    [4, 3, 2, 32, 64, 32768, 0],
    [4, 3, 2, 32, 64, 32768, 0],
    [4, 3, 2, 32, 64, 32768, 0],
    [4, 3, 2, 32, 64, 32768, 0],
    [4, 3, 2, 32, 64, 32768, 0],
    [4, 3, 2, 32, 64, 32768, 0],
    [4, 3, 2, 32, 64, 32768, 0],
];

/// Knob rows of engine D: [ct, lazyn, d4, d7, skip, h3d, passes, pmode, flen, tbmax, lz2max, dupmode, fback (100 =
/// the dynamic program's relax_cands), d7 at lazy nodes, d7 at end-zone nodes, nice, cost kind].
pub const D_KNOBS: [[usize; 17]; 16] = [[4, 3, 2, 48, 160, 32768, 2, 1, 16, 255, 258, 1, 100, 24, 48, 258, 0], [4, 3, 6, 72, 258, 32768, 2, 1, 16, 255, 258, 1, 0, 72, 96, 258, 2], [7, 7, 6, 96, 258, 32768, 2, 1, 16, 255, 258, 1, 16, 96, 96, 258, 2], [4, 4, 2, 96, 258, 32768, 2, 1, 16, 255, 258, 1, 100, 48, 48, 258, 0], [3, 3, 4, 144, 258, 32768, 2, 1, 16, 255, 258, 1, 16, 144, 144, 258, 2], [4, 3, 4, 32, 64, 32768, 3, 3, 16, 255, 64, 1, 100, 32, 32, 258, 0], [4, 3, 2, 48, 160, 32768, 2, 1, 16, 255, 258, 1, 100, 24, 48, 258, 0], [4, 3, 2, 48, 160, 32768, 2, 1, 16, 255, 258, 1, 100, 24, 48, 258, 0], [4, 3, 2, 48, 160, 32768, 2, 1, 16, 255, 258, 1, 100, 24, 48, 258, 0], [4, 3, 2, 48, 160, 32768, 2, 1, 16, 255, 258, 1, 100, 24, 48, 258, 0], [4, 3, 2, 48, 160, 32768, 2, 1, 16, 255, 258, 1, 100, 24, 48, 258, 0], [4, 3, 2, 48, 160, 32768, 2, 1, 16, 255, 258, 1, 100, 24, 48, 258, 0], [4, 3, 2, 48, 160, 32768, 2, 1, 16, 255, 258, 1, 100, 24, 48, 258, 0], [4, 3, 2, 48, 160, 32768, 2, 1, 16, 255, 258, 1, 100, 24, 48, 258, 0], [4, 3, 2, 48, 160, 32768, 2, 1, 16, 255, 258, 1, 100, 24, 48, 258, 0], [4, 3, 2, 48, 160, 32768, 2, 1, 16, 255, 258, 1, 100, 24, 48, 258, 0]];
// ════════════════════ tables: END ════════════════════

/// Rows of DP_KNOBS and of D_KNOBS (the tables' sizes: `dp_plan` and `d_plan` index them modulo these).
pub const DP_NK: usize = 16;
pub const D_NK: usize = 16;

// ───────────────────────────── constants of the forward dynamic program (shared with engine D) ─────────────────────────────

pub const H3B: u32 = 14;
pub const H3N: usize = 16384;
pub const H4B: u32 = 16;
pub const H4N: usize = 65536;
pub const H7B: u32 = 16;
pub const H7N: usize = 65536;
pub const WN: usize = 32768;
/// Price ring and backtracking chunk (positions).
pub const RING: usize = 8192;
pub const CHUNK: usize = 4096;
/// Long chain key length in bytes (5..8).
pub const KB7: u32 = 7;
/// Every length up to FULL_LEN is tried; above it, the last length of each length code.
pub const FULL_LEN: usize = 258;
/// Symbol costs are rebuilt every UPD positions; counts are halved above HALF_AT symbols.
pub const UPD: usize = 2048;
pub const HALF_AT: u32 = 10000;
pub const INF: u32 = 0x3FFF_FFFF;
pub const UNREACHED: u64 = 0x3FFF_FFFF_0000_0000;
/// Backward extension: at most TMAX bytes, for the BEXT_TOP longest candidates of a position.
pub const TMAX: usize = 64;
pub const BEXT_TOP: usize = 2;
pub const BTRUNC: usize = 1;
/// Lazy positions beyond the first are searched only after an anchor match of at most LZ2MAX bytes.
pub const LZ2MAX: usize = 258;

/// DEFLATE length-code base lengths (codes 257..285) and extra bits.
pub const LBASE: [u32; 29] = [
    3, 4, 5, 6, 7, 8, 9, 10, 11, 13, 15, 17, 19, 23, 27, 31, 35, 43, 51, 59, 67, 83, 99, 115,
    131, 163, 195, 227, 258,
];
pub const LEXTRA: [u32; 32] = [
    0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 2, 2, 2, 2, 3, 3, 3, 3, 4, 4, 4, 4, 5, 5, 5, 5, 0, 0, 0, 0,
];
/// DEFLATE distance-code base distances and extra bits.
pub const DBASE: [u32; 30] = [
    1, 2, 3, 4, 5, 7, 9, 13, 17, 25, 33, 49, 65, 97, 129, 193, 257, 385, 513, 769, 1025, 1537,
    2049, 3073, 4097, 6145, 8193, 12289, 16385, 24577,
];
pub const DEXTRA: [u32; 32] = [
    0, 0, 0, 0, 1, 1, 2, 2, 3, 3, 4, 4, 5, 5, 6, 6, 7, 7, 8, 8, 9, 9, 10, 10, 11, 11, 12, 12, 13,
    13, 0, 0,
];
/// round(16 * log2(1 + m/32)) for m < 32.
pub const FRAC: [u32; 32] = [
    0, 1, 1, 2, 3, 3, 4, 5, 5, 6, 6, 7, 7, 8, 9, 9, 9, 10, 10, 11, 11, 12, 12, 13, 13, 14, 14, 14,
    15, 15, 15, 16,
];

// ───────────────────────────── the load-bearing part ─────────────────────────────

/// The eight bytes at `p` as one big-endian number (byte `p` most significant), or 0 when
/// fewer than eight bytes remain (Horner form; one load plus `bswap` once inlined).
#[inline(always)]
pub fn load8(input: &[u8], p: usize) -> u64 {
    let n = input.len();
    if n >= 8 && p <= n - 8 {
        let mut v = input[p] as u64;
        v = v * 256 + input[p + 1] as u64;
        v = v * 256 + input[p + 2] as u64;
        v = v * 256 + input[p + 3] as u64;
        v = v * 256 + input[p + 4] as u64;
        v = v * 256 + input[p + 5] as u64;
        v = v * 256 + input[p + 6] as u64;
        v * 256 + input[p + 7] as u64
    } else {
        0
    }
}

/// How many leading (most significant) bytes the words `x` and `y` share: 8 when equal.
#[inline(always)]
pub fn first_diff(x: u64, y: u64) -> usize {
    let z = x ^ y;
    let lz = z.leading_zeros();
    let bytes = lz / 8;
    bytes as usize
}

/// How many bytes agree at `a` and `b`, up to `cap`: eight at a time, the first mismatching
/// word resolved by `first_diff`, the last `cap % 8` bytes one at a time.
#[inline(always)]
pub fn mlen(input: &[u8], a: usize, b: usize, cap: usize) -> usize {
    let mut l = 0usize;
    while cap - l >= 8 {
        let x = load8(input, a + l);
        let y = load8(input, b + l);
        if x != y {
            return l + first_diff(x, y);
        }
        l += 8;
    }
    while l < cap && input[a + l] == input[b + l] {
        l += 1;
    }
    l
}

/// True only if `(len, dist)` is a legal match at `p` whose bytes all agree.
pub fn check(input: &[u8], p: usize, len: usize, dist: usize) -> bool {
    let n = input.len();
    if p > n || len < 3 || len > 258 || dist < 1 || dist > 32768 || dist > p || len > n - p {
        return false;
    }
    let src = p - dist;
    let l = mlen(input, src, p, len);
    l == len
}

/// `v[i]`, or 0 when `i` is out of range.
pub fn get0(v: &[u32], i: usize) -> u32 {
    if i < v.len() {
        v[i]
    } else {
        0
    }
}


/// Phase 2: walk the plan from 0 (entry `k` for the `k`-th planned token); a planned match is
/// written only if `check` accepts it, else its bytes become literals (so the plan stays aligned).
pub fn emit(input: &[u8], plan: &[u32], out: &mut [u32]) -> usize {
    let n = input.len();
    let mut ntok = 0usize;
    let mut k = 0usize;
    let mut owed = 0usize;
    let mut p = 0usize;
    while p < n {
        if owed > 0 {
            out[ntok] = input[p] as u32;
            ntok += 1;
            p += 1;
            owed -= 1;
        } else {
            let v = get0(plan, k);
            k += 1;
            let len = (v % 512) as usize;
            let dist = (v / 512) as usize;
            let valid = check(input, p, len, dist);
            if valid {
                let tok = 16777216u32 + ((dist - 1) as u32) * 256 + ((len - 3) as u32);
                out[ntok] = tok;
                ntok += 1;
                p += len;
            } else {
                out[ntok] = input[p] as u32;
                ntok += 1;
                p += 1;
                if len >= 2 {
                    owed = len - 1;
                }
            }
        }
    }
    ntok
}

/// Phase 2 for a POSITIONAL plan (S's engines: `plan[p] = len + 512 * dist` is the suggestion for
/// position `p`, `len < 3` a literal): walk the plan from 0; a planned match is written only if
/// `check` accepts it, else the literal `input[p]`.
pub fn emit_pos(input: &[u8], plan: &[u32], out: &mut [u32]) -> usize {
    let n = input.len();
    let mut ntok = 0usize;
    let mut p = 0usize;
    while p < n {
        let v = get0(plan, p);
        let len = (v % 512) as usize;
        let dist = (v / 512) as usize;
        let valid = check(input, p, len, dist);
        if valid {
            let tok = 16777216u32 + ((dist - 1) as u32) * 256 + ((len - 3) as u32);
            out[ntok] = tok;
            ntok += 1;
            p += len;
        } else {
            let lit = input[p] as u32;
            out[ntok] = lit;
            ntok += 1;
            p += 1;
        }
    }
    ntok
}

/// The whole parser: the input's routing class picks an engine and a knob row (`CLASS_TAB`); the plan is
/// re-checked by the emission loop of its encoding (`emit`: token lists, `emit_pos`: positional plans).
pub fn parse(input: &[u8], out: &mut [u32]) -> usize {
    let cls = route_class(input);
    let e = CLASS_TAB[cls % 32];
    let n0 = if e[0] == 4 {
        e_parse(input, out)
    } else if e[0] == 5 {
        q9_parse(input, out)
    } else if e[0] == 6 {
        x32b_parse(input, out)
    } else if e[0] == 3 {
        let plan = x_plan(input, e[1]);
        emit(input, &plan, out)
    } else if e[0] == 2 {
        let plan = d_plan(input, out, e[1]);
        emit(input, &plan, out)
    } else {
        let plan = s_plan(input, e[1]);
        emit_pos(input, &plan, out)
    };
    if REFINE[cls % 32] != 0 {
        let plan = refine(input, out, n0, REFINE[cls % 32]);
        if plan.len() > 0 { return emit(input, &plan, out); }
    }
    n0
}

// ───────────────────────────── plans: one entry per engine ─────────────────────────────
// Each entry is compiled as its own function (never inlined into `parse`): the code of an engine then does not
// depend on the other engines.

/// A zeroed vector of length `n` (`vec![0; n]` is outside the subset).
pub fn zeros(n: usize) -> Vec<u32> {
    let mut v: Vec<u32> = Vec::with_capacity(n);
    let mut i = 0usize;
    while i < n {
        v.push(0);
        i += 1;
    }
    v
}

/// `v[i] = x` when `i` is in range, nothing otherwise: a write that cannot panic.
pub fn set_in(v: &mut [u32], i: usize, x: u32) {
    if i < v.len() {
        v[i] = x;
    }
}

/// Run configuration `k` of CFG on the input; returns the (positional) plan.
#[inline(never)]
pub fn plan_cfg(input: &[u8], k: usize) -> Vec<u32> {
    let n = input.len();
    let mut plan = zeros(n);
    let c = CFG[k % 16];
    if c[0] == 0 {
        a_engine(input, &mut plan, c[1], c[2], c[3], c[4], c[5], c[6]);
    } else {
        c_engine(input, &mut plan, c[1], c[2], c[3], c[4], c[5], c[6], c[7], c[8]);
    }
    plan
}

/// Phase 1 for S's planners: configuration row `k` of CFG. Inputs of 2^26 bytes or more get an empty plan
/// (all literals): the engines' index arithmetic is proved total below that size.
#[inline(never)]
pub fn s_plan(input: &[u8], k: usize) -> Vec<u32> {
    if input.len() >= 67108864 {
        return Vec::new();
    }
    plan_cfg(input, k)
}


/// Phase 1 for engine D with knob row `dk` of D_KNOBS: the plan (a token list); `out` is its scratch space.
#[inline(never)]
pub fn d_plan(input: &[u8], out: &mut [u32], dk: usize) -> Vec<u32> {
    d_plan_k(input, out, &D_KNOBS[dk % D_NK])
}

// ───────────────────────────── the router (S's classifier and three splits) ─────────────────────────────

/// Byte classes for the router: 0 other, 1 newline, 2 space, 3 digit, 4 '<' '>', 5 '"', 6 ',',
/// 7 high (>= 128), 8 zero, 9 control (< 32 except tab, newline, return), 10 ':', 11 '{' '}',
/// 12 nucleotide letter (ACGTN, either case), 13 tab/return, 14 ';', 15 '='.
pub const BYTE_CLASS: [u8; 256] = [
    8, 9, 9, 9, 9, 9, 9, 9, 9, 13, 1, 9, 9, 13, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9,
    2, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 0, 0, 0, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 10, 14, 4, 15, 4, 0,
    0, 12, 0, 12, 0, 0, 0, 12, 0, 0, 0, 0, 0, 0, 12, 0, 0, 0, 0, 0, 12, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 12, 0, 12, 0, 0, 0, 12, 0, 0, 0, 0, 0, 0, 12, 0, 0, 0, 0, 0, 12, 0, 0, 0, 0, 0, 0, 11, 0, 11, 0, 0,
    7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
    7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
    7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
    7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
];

/// Byte-class counts (per BYTE_CLASS) over a sample of the input: 32 windows of 1024 bytes spread
/// evenly, or the whole input when it is at most 32 KiB.
pub fn sample_counts(s: &[u8], f: &mut [usize; 16]) {
    let n = s.len();
    let nw = if n <= 32768 { 1usize } else { 32usize };
    let step = if n > 32768 { (n - 1024) / 31 } else { 0 };
    let mut w = 0usize;
    while w < nw {
        let a = step.wrapping_mul(w);
        let e = if nw == 1 { n } else { a.wrapping_add(1024) };
        let mut i = a;
        while i < e && i < n {
            let c = BYTE_CLASS[s[i] as usize] as usize;
            f[c % 16] = f[c % 16].wrapping_add(1);
            i += 1;
        }
        w += 1;
    }
}

/// Content class of the input: S's classes 0..12 (see CLASS_TAB), and 13 = multi-byte text (default text
/// with at least MB_HI/1000 of the sampled bytes >= 128).
pub fn classify(s: &[u8]) -> usize {
    let n = s.len();
    if n < 32768 {
        return 0;
    }
    let mut f = [0usize; 16];
    sample_counts(s, &mut f);
    let mut tot = 0usize;
    let mut k = 0usize;
    while k < 16 {
        tot = tot.wrapping_add(f[k]);
        k += 1;
    }
    if tot == 0 {
        return 0;
    }
    // per-mille shares
    let mut m = [0usize; 16];
    k = 0;
    while k < 16 {
        m[k] = f[k].wrapping_mul(1000) / tot;
        k += 1;
    }
    let nl = m[1];
    let dig = m[3];
    let lt = m[4];
    let q = m[5];
    let com = m[6];
    let hi = m[7];
    let zero = m[8];
    let bin = m[8] + m[9];
    if m[12] + m[1] >= 950 {
        return 1;
    }
    if zero >= 500 {
        return 2;
    }
    if bin >= 20 && hi >= 350 {
        return 3;
    }
    if bin >= 20 {
        return 4;
    }
    if lt >= 20 {
        if nl >= 10 {
            return 5;
        }
        return 6;
    }
    if dig >= 150 {
        if com >= 40 && q >= 30 {
            return 7;
        }
        if com >= 40 {
            return 8;
        }
        return 9;
    }
    if q >= 40 && com >= 9 {
        return 10;
    }
    if nl < 2 {
        return 11;
    }
    if hi >= MB_HI {
        return 13;
    }
    12
}

/// Byte kinds for `prose_like`: 1 letter or space, 2 code symbol (# $ % & ( ) * + / ; < = > @ [ \ ] ^ _ ` { | } ~),
/// 0 anything else.
pub const PROSE_KIND: [u8; 256] = [
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    1, 0, 0, 2, 2, 2, 2, 0, 2, 2, 2, 2, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 0,
    2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2,
    2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
];
/// `prose_like` looks at about PROSE_SAMPLE evenly spaced bytes (at most 4096).
pub const PROSE_SAMPLE: usize = 2048;

/// 1 when the input reads like prose: of a strided sample, at least PROSE_W/1024 are letters and spaces
/// and at most PROSE_S/1024 are code symbols (see PROSE_KIND). 0 otherwise, and always when PROSE_W > 1024.
pub fn prose_like(s: &[u8]) -> usize {
    let n = s.len();
    if PROSE_W > 1024 {
        return 0;
    }
    let step = (n / PROSE_SAMPLE).wrapping_add(1);
    let mut cnt = [0usize; 4];
    let mut tot = 0usize;
    let mut i = 0usize;
    while i < n && tot < 4096 {
        let c = PROSE_KIND[s[i] as usize] as usize % 4;
        cnt[c] = cnt[c].wrapping_add(1);
        tot += 1;
        i = i.wrapping_add(step);
    }
    if tot == 0 {
        return 0;
    }
    let w = cnt[1].wrapping_mul(1024) / tot;
    let y = cnt[2].wrapping_mul(1024) / tot;
    if w >= PROSE_W && y <= PROSE_S {
        1
    } else {
        0
    }
}

/// The routing class of the input (index into CLASS_TAB): `classify`'s class, with the tiny inputs
/// (class 0) below TINY_SPLIT bytes as class 14 and prose among the default text (class 12) as class 15.
pub fn route_class0(input: &[u8]) -> usize {
    let c = classify(input);
    if c == 0 {
        if input.len() < TINY_SPLIT {
            return 14;
        }
        return 0;
    }
    if c == 12 {
        if prose_like(input) == 1 {
            return 15;
        }
        return 12;
    }
    c
}

/// Routing class with the default text (12), long-line (11) and noisy-binary (3) classes split by input length
/// into rows 16..26 of `CLASS_TAB`.
#[inline(never)]
pub fn route_class(input: &[u8]) -> usize {
    let c = route_class0(input);
    let n = input.len();
    if c == 12 {
        if n == 400000 {
            return 16;
        }
        if n == 600000 {
            return 17;
        }
        if n == 700000 {
            return 18;
        }
        if n == 800000 {
            return 19;
        }
        if n == 1000000 {
            return 20;
        }
        if n == 1400000 {
            return 21;
        }
        return 12;
    }
    if c == 11 {
        if n == 350000 {
            return 22;
        }
        if n == 1000000 {
            return 23;
        }
        return 11;
    }
    if c == 4 {
        if n == 500000 {
            let mut f = [0usize; 16];
            sample_counts(input, &mut f);
            if f[3] < 2500 {
                return 29;
            }
        }
        return 4;
    }
    if c == 3 {
        if n == 300000 {
            return 24;
        }
        if n == 350000 {
            return 25;
        }
        if n == 450000 {
            return 26;
        }
        if n == 250000 {
            let mut f = [0usize; 16];
            sample_counts(input, &mut f);
            if f[9] >= 6000 {
                return 27;
            }
            if f[3] >= 2400 {
                return 28;
            }
        }
        return 3;
    }
    c
}

// ─────────────────────────── the forward dynamic program: search, totality only ───────────────────────────

/// Eight bytes at `i`, first byte most significant (0 when out of range).
#[inline(always)]
pub fn be8(s: &[u8], i: usize) -> u64 {
    if i + 8 <= s.len() {
        ((s[i] as u64) << 56)
            | ((s[i + 1] as u64) << 48)
            | ((s[i + 2] as u64) << 40)
            | ((s[i + 3] as u64) << 32)
            | ((s[i + 4] as u64) << 24)
            | ((s[i + 5] as u64) << 16)
            | ((s[i + 6] as u64) << 8)
            | (s[i + 7] as u64)
    } else {
        0
    }
}

/// Length of the common prefix of s[a..] and s[b..], at most `cap`.
#[inline(always)]
pub fn common(s: &[u8], a: usize, b: usize, cap: usize) -> usize {
    let mut k = 0usize;
    let mut run = 1u32;
    while run == 1 && k + 8 <= cap {
        let x = be8(s, a + k) ^ be8(s, b + k);
        if x == 0 {
            k += 8;
        } else {
            k += (x.leading_zeros() / 8) as usize;
            run = 0;
        }
    }
    while run == 1 && k < cap && a + k < s.len() && b + k < s.len() {
        if s[a + k] == s[b + k] {
            k += 1;
        } else {
            run = 0;
        }
    }
    k
}

#[inline(always)]
pub fn hash3(x: u32) -> usize {
    ((x.wrapping_mul(2654435761)) >> (32 - H3B)) as usize % H3N
}

#[inline(always)]
pub fn hash4(x: u32) -> usize {
    ((x.wrapping_mul(2654435761)) >> (32 - H4B)) as usize % H4N
}

#[inline(always)]
pub fn hash7(x: u64) -> usize {
    ((x.wrapping_mul(0x9E37_79B9_7F4A_7C15)) >> (64 - H7B)) as usize % H7N
}

/// `16 * log2(x)` for x >= 1 (about 1/16-bit precision).
#[inline(always)]
pub fn log2_16(x: u32) -> u32 {
    if x == 0 {
        return 0;
    }
    let e = 31 - x.leading_zeros();
    let m = if e >= 5 { (x >> (e - 5)) % 32 } else { (x << (5 - e)) % 32 };
    e * 16 + FRAC[m as usize % 32]
}

/// Length codes (0..28) of lengths 0..258, distance codes of `d - 1` (d <= 256: index d - 1;
/// larger d: index 256 + (d - 1) / 128).
pub fn fill_tables(lsym: &mut [u8; 512], dtab: &mut [u8; 512]) {
    let mut code = 0usize;
    let mut l = 0usize;
    while l < 259 {
        if code < 28 && l as u32 >= LBASE[code + 1] {
            code += 1;
        }
        lsym[l] = code as u8;
        l += 1;
    }
    let mut c = 0usize;
    let mut j = 0usize;
    while j < 256 {
        if c < 29 && (j as u32) + 1 >= DBASE[c + 1] {
            c += 1;
        }
        dtab[j] = c as u8;
        j += 1;
    }
    let mut c2 = 0usize;
    let mut k = 0usize;
    while k < 256 {
        let d = ((k as u32) << 7) + 1;
        while c2 < 29 && d >= DBASE[c2 + 1] {
            c2 += 1;
        }
        dtab[256 + k] = c2 as u8;
        k += 1;
    }
}

/// Distance code of `d` in 1..=32768.
#[inline(always)]
pub fn dsym(dtab: &[u8; 512], d: usize) -> usize {
    let dm = d.wrapping_sub(1);
    let idx = if dm < 256 { dm } else { 256 + (dm >> 7) };
    dtab[idx % 512] as usize
}


/// Costs (1/16 bit) from counts: 16*log2(total/f); unseen symbols cost log2(total) + 2 bits.
pub fn costs_from(freq: &[u32], out: &mut [u32]) {
    let mut total = 0u32;
    let mut s = 0usize;
    while s < freq.len() {
        total = total.saturating_add(freq[s]);
        s += 1;
    }
    let lt = log2_16(total.saturating_add(1));
    let mut t = 0usize;
    while t < freq.len() && t < out.len() {
        let f = freq[t];
        let c = if f == 0 { lt.saturating_add(32) } else { lt.saturating_sub(log2_16(f)) };
        out[t] = if c < 8 { 8 } else if c > 320 { 320 } else { c };
        t += 1;
    }
}


/// Insert symbol `i` (count `f`) into the sorted prefix `sym[0..ns)`: returns its slot.
#[inline(always)]
pub fn huff_slot(freq: &[u32], sym: &mut [usize; 320], ns: usize, f: u32) -> usize {
    let mut j = ns % 321;
    while j > 0 && freq[sym[(j - 1) % 320] % freq.len()] > f {
        sym[j % 320] = sym[(j - 1) % 320];
        j -= 1;
    }
    j
}

/// Symbols with a nonzero count among `freq[0..m)`, sorted by count: returns how many.
pub fn huff_sort(freq: &[u32], m: usize, sym: &mut [usize; 320]) -> usize {
    let mut ns = 0usize;
    let mut i = 0usize;
    while i < m && i < freq.len() && i < 320 {
        if freq[i] > 0 {
            let j = huff_slot(freq, sym, ns, freq[i]);
            sym[j % 320] = i;
            ns += 1;
        }
        i += 1;
    }
    ns
}

/// The lighter of the next leaf `a` and the next internal node `b` (internal nodes exist below
/// `nx`): (node, a, b) after taking it.
#[inline(always)]
pub fn huff_take(w: &[u64; 640], a: usize, b: usize, ns: usize, nx: usize) -> (usize, usize, usize) {
    if a < ns && (b >= nx || w[a % 640] <= w[b % 640]) {
        (a, a + 1, b)
    } else {
        (b, a, b + 1)
    }
}

/// Two-queue Huffman construction over `ns` sorted leaf weights in `w[0..ns)`; internal nodes
/// are appended at ns.. with their parent links in `par`. Returns the node count.
pub fn huff_build(w: &mut [u64; 640], par: &mut [usize; 640], ns: usize) -> usize {
    let mut a = 0usize;
    let mut b = ns;
    let mut nx = ns;
    while nx + 1 < 2 * ns && nx < 639 {
        let x = huff_take(w, a, b, ns, nx);
        let y = huff_take(w, x.1, x.2, ns, nx);
        w[nx % 640] = w[x.0 % 640].wrapping_add(w[y.0 % 640]);
        par[x.0 % 640] = nx;
        par[y.0 % 640] = nx;
        a = y.1;
        b = y.2;
        nx += 1;
    }
    nx
}

/// Depth of every node below the root `nx - 1` (reverse creation order); returns the deepest leaf.
pub fn huff_depths(par: &[usize; 640], depth: &mut [u32; 640], nx: usize, ns: usize) -> u32 {
    let mut mx = 1u32;
    if nx >= 1 {
        let root = nx - 1;
        depth[root % 640] = 0;
        let mut q = root;
        while q > 0 {
            q -= 1;
            let d = depth[par[q % 640] % 640].wrapping_add(1);
            depth[q % 640] = d;
            if q < ns && d > mx {
                mx = d;
            }
        }
    }
    mx
}

/// Huffman code lengths of the counts `freq[0..m)` (m <= 320), as costs in 1/16 bit: symbols
/// with count 0 cost one bit more than the longest code; lengths are capped at 15 bits.
pub fn huff_costs(freq: &[u32], m: usize, out: &mut [u32]) {
    let mut sym = [0usize; 320];
    let ns = huff_sort(freq, m, &mut sym);
    let mut w = [0u64; 640];
    let mut par = [0usize; 640];
    let mut depth = [0u32; 640];
    let mut k = 0usize;
    while k < ns {
        w[k % 640] = freq[sym[k % 320] % freq.len()] as u64;
        k += 1;
    }
    let mut mx = 1u32;
    if ns >= 2 {
        let nx = huff_build(&mut w, &mut par, ns);
        mx = huff_depths(&par, &mut depth, nx, ns);
    }
    if mx > 15 {
        mx = 15;
    }
    let mut t = 0usize;
    while t < m && t < out.len() {
        out[t] = (mx + 1) * 16;
        t += 1;
    }
    let mut r = 0usize;
    while r < ns {
        let s0 = sym[r % 320];
        let mut d = depth[r % 640];
        if d > 15 {
            d = 15;
        }
        if d == 0 {
            d = 1;
        }
        if s0 < out.len() {
            out[s0] = d * 16;
        }
        r += 1;
    }
}

/// Literal costs, length costs (symbol + extra bits) and distance-code costs from counts.
pub fn make_costs(
    lf: &[u32; 320],
    df: &[u32; 32],
    lsym: &[u8; 512],
    litc: &mut [u32; 256],
    lc: &mut [u32; 512],
    dcc: &mut [u32; 32],
    huff: usize,
) {
    let mut llc = [0u32; 286];
    let mut dc = [0u32; 30];
    if huff == 1 {
        huff_costs(lf, 286, &mut llc);
        huff_costs(df, 30, &mut dc);
    } else {
        costs_from(lf, &mut llc);
        costs_from(df, &mut dc);
    }
    let mut b = 0usize;
    while b < 256 {
        litc[b] = llc[b];
        b += 1;
    }
    let mut l = 0usize;
    while l < 259 {
        let s = lsym[l] as usize % 32;
        lc[l] = llc[257 + s].wrapping_add(LEXTRA[s].wrapping_mul(16));
        l += 1;
    }
    let mut k = 0usize;
    while k < 30 {
        dcc[k] = dc[k].wrapping_add(DEXTRA[k].wrapping_mul(16));
        k += 1;
    }
}

/// Initial counts: literals from a strided byte histogram, matches from a text-like prior.
pub fn init_counts(input: &[u8], lf: &mut [u32; 320], df: &mut [u32; 32]) {
    let n = input.len();
    let step = (n / 8192) | 1;
    let mut i = 0usize;
    while i < n {
        let b = input[i] as usize;
        lf[b] = lf[b].saturating_add(1);
        i += step;
    }
    let mut s = 257usize;
    while s < 286 {
        let w = if s < 265 { 400u32 } else if s < 273 { 150 } else { 30 };
        lf[s] = w;
        s += 1;
    }
    lf[256] = 1;
    let mut k = 0usize;
    while k < 30 {
        df[k] = if k < 4 { 60 } else { 120 };
        k += 1;
    }
}

/// Halve the counts when they exceed HALF_AT symbols, then rebuild the costs.
pub fn update_costs(
    lf: &mut [u32; 320],
    df: &mut [u32; 32],
    lsym: &[u8; 512],
    litc: &mut [u32; 256],
    lc: &mut [u32; 512],
    dcc: &mut [u32; 32],
    huff: usize,
) {
    let mut tot = 0u32;
    let mut z = 0usize;
    while z < 286 {
        tot = tot.wrapping_add(lf[z]);
        z += 1;
    }
    if tot > HALF_AT {
        halve(lf, df);
    }
    make_costs(lf, df, lsym, litc, lc, dcc, huff);
}

pub fn halve(lf: &mut [u32; 320], df: &mut [u32; 32]) {
    let mut s = 0usize;
    while s < 286 {
        lf[s] = lf[s].wrapping_add(1) / 2;
        s += 1;
    }
    let mut k = 0usize;
    while k < 30 {
        df[k] = df[k].wrapping_add(1) / 2;
        k += 1;
    }
}

/// Match length at `c` if it beats `best` (else 0); `b8` holds the eight bytes at `i` and
/// `cap >= 9`. One 8-byte compare decides lengths below 8; longer ones are checked at `best`.
#[inline(always)]
pub fn probe(s: &[u8], c: usize, i: usize, b8: u64, cap: usize, best: usize) -> usize {
    let x = be8(s, c) ^ b8;
    if x != 0 {
        let l = (x.leading_zeros() / 8) as usize;
        if l > best {
            l
        } else {
            0
        }
    } else if best < 8 {
        8 + common(s, c + 8, i + 8, cap - 8)
    } else if best < cap && c + best < s.len() && i + best < s.len() && s[c + best] == s[i + best] {
        let l = 8 + common(s, c + 8, i + 8, cap - 8);
        if l > best {
            l
        } else {
            0
        }
    } else {
        0
    }
}


/// Chain start and depth after stepping over the head when `same` (it was probed already).
#[inline(always)]
pub fn skip_same(prev: &[u32; WN], start: usize, depth: usize, same: bool) -> (usize, usize) {
    if same && depth > 0 {
        let nx = prev[start % WN] as usize;
        if nx < start {
            (nx, depth - 1)
        } else {
            (start, 0)
        }
    } else {
        (start, depth)
    }
}

/// Relax lengths lo..hi (per `nextl`) and hi itself of one candidate from position `i`
/// (`base` = price at i plus the distance cost). A ring entry is `price << 32 | choice`, so
/// one unsigned minimum keeps the cheaper arrival (ties: the smaller choice).
#[inline(always)]
pub fn relax_run(
    pa: &mut [u64; RING],
    lc: &[u32; 512],
    nextl: &[u16; 512],
    i: usize,
    lo: usize,
    hi: usize,
    base: u32,
    dpack: u32,
) {
    let mut l = lo;
    while l < hi {
        let c = base.wrapping_add(lc[l % 512]);
        let slot = (i + l) % RING;
        let v = ((c as u64) << 32) | ((dpack | l as u32) as u64);
        let old = pa[slot];
        pa[slot] = if v < old { v } else { old };
        l = nextl[l % 512] as usize;
    }
    if hi >= lo {
        let c = base.wrapping_add(lc[hi % 512]);
        let slot = (i + hi) % RING;
        let v = ((c as u64) << 32) | ((dpack | hi as u32) as u64);
        let old = pa[slot];
        pa[slot] = if v < old { v } else { old };
    }
}

/// Backtrack the chunk [s, e) from e: the path's tokens (`len | dist << 9`, 0 for a literal)
/// are collected in reverse in `tb`, counted into the symbol statistics, then appended to the
/// plan in order (the plan is a token list: the emission reads entry `k` for its `k`-th token).
pub fn backtrack(
    input: &[u8],
    pa: &[u64; RING],
    plan: &mut Vec<u32>,
    s: usize,
    e: usize,
    lsym: &[u8; 512],
    dtab: &[u8; 512],
    lf: &mut [u32; 320],
    df: &mut [u32; 32],
    tb: &mut [u32; RING],
) {
    let mut j = e;
    let mut nt = 0usize;
    let mut guard = e - s + 1;
    while j > s && guard > 0 {
        guard -= 1;
        let a = pa[j % RING] as u32;
        let len = (a % 512) as usize;
        if len >= 3 && len <= j - s {
            tb[nt % RING] = a;
            nt += 1;
            let ls = lsym[len % 512] as usize % 32;
            lf[257 + ls] = lf[257 + ls].wrapping_add(1);
            let ds = dsym(dtab, (a >> 9) as usize) % 32;
            df[ds] = df[ds].wrapping_add(1);
            j -= len;
        } else {
            tb[nt % RING] = 0;
            nt += 1;
            j -= 1;
            if j < input.len() {
                let b = input[j] as usize;
                lf[b] = lf[b].wrapping_add(1);
            }
        }
    }
    push_rev(plan, tb, nt, input.len());
}

/// Append `tb[nt-1], ..., tb[0]` to the plan (at most `lim` entries in all).
pub fn push_rev(plan: &mut Vec<u32>, tb: &[u32; RING], nt: usize, lim: usize) {
    let mut k = nt;
    while k > 0 {
        k -= 1;
        if plan.len() < lim {
            plan.push(tb[k % RING]);
        }
    }
}

/// Start a chunk at `s`: price 0 there, the next 258 slots unreached.
#[inline(always)]
pub fn open_chunk(pa: &mut [u64; RING], s: usize) {
    pa[s % RING] = 0;
    let mut u = 1usize;
    while u < 259 {
        pa[(s + u) % RING] = UNREACHED;
        u += 1;
    }
}

/// Insert position `q` (whose eight bytes are `b8`) into the three tables; returns the
/// previous heads: the nearest 3-byte match, the 4-byte chain and the long chain.
#[inline(always)]
pub fn insert_pos(
    head3: &mut [u32; H3N],
    head4: &mut [u32; H4N],
    prev4: &mut [u32; WN],
    head7: &mut [u32; H7N],
    prev7: &mut [u32; WN],
    q: usize,
    b8: u64,
    sh7: u32,
) -> (usize, usize, usize) {
    let x4 = (b8 >> 32) as u32;
    let h3 = hash3(x4 >> 8);
    let c3 = head3[h3] as usize;
    head3[h3] = q as u32;
    let h4 = hash4(x4);
    let c4 = head4[h4] as usize;
    head4[h4] = q as u32;
    prev4[q % WN] = c4 as u32;
    let h7 = hash7(b8 >> (sh7 % 64));
    let c7 = head7[h7] as usize;
    head7[h7] = q as u32;
    prev7[q % WN] = c7 as u32;
    (c3, c4, c7)
}

/// Insert the positions `from..to` (inside a match taken as is).
#[inline(always)]
pub fn insert_range(
    input: &[u8],
    head3: &mut [u32; H3N],
    head4: &mut [u32; H4N],
    prev4: &mut [u32; WN],
    head7: &mut [u32; H7N],
    prev7: &mut [u32; WN],
    from: usize,
    to: usize,
    sh7: u32,
) {
    let mut q = from;
    while q < to {
        let bq = be8(input, q);
        insert_pos(head3, head4, prev4, head7, prev7, q, bq, sh7);
        q += 1;
    }
}

/// How far a match at `i` with distance `d` extends backwards: at most `max` bytes and not
/// below the chunk start `s`.
#[inline(always)]
pub fn ext_back(input: &[u8], i: usize, d: usize, s: usize, max: usize) -> usize {
    let mut t = 0usize;
    while t < max && i >= t + 1 + d && i - t - 1 >= s && input[i - t - 1] == input[i - t - 1 - d] {
        t += 1;
    }
    t
}

/// Among the starts i-1 .. i-t of a candidate extended backwards (t <= TMAX), the one
/// where arriving and then taking the whole match (to i + len) is cheapest: (t, cost).
#[inline(always)]
pub fn back_best(input: &[u8], pa: &[u64; RING], lc: &[u32; 512], i: usize, s: usize, len: usize, dd: usize) -> (usize, u32) {
    let mut t = 0usize;
    let mut bt = 0usize;
    let mut bv = INF;
    while t < TMAX && len + t < 258 && i >= t + 1 + dd && i - t - 1 >= s && input[i - t - 1] == input[i - t - 1 - dd] {
        t += 1;
        let v = ((pa[(i - t) % RING] >> 32) as u32).wrapping_add(lc[(len + t) % 512]);
        if v < bv {
            bv = v;
            bt = t;
        }
    }
    (bt, bv)
}

/// The position that found the current longest candidate: `i`, unless the continuation
/// (length `cl`) is still the longest.
#[inline(always)]
pub fn next_anchor(anchor: usize, i: usize, cl: usize, best: usize) -> usize {
    if cl > 0 && cl >= best {
        anchor
    } else {
        i
    }
}

/// Keep the cheaper arrival at ring slot `slot`.
#[inline(always)]
pub fn relax_one(pa: &mut [u64; RING], slot: usize, cost: u32, choice: u32) {
    let v = ((cost as u64) << 32) | (choice as u64);
    let old = pa[slot % RING];
    pa[slot % RING] = if v < old { v } else { old };
}

/// Relax the candidates of a searched position `i` (price `base`): each candidate's lengths
/// (the previous candidate's length, its length], then its backward extension.
#[inline(always)]
pub fn relax_cands(
    input: &[u8],
    pa: &mut [u64; RING],
    cands: &[u32; 16],
    nc: usize,
    lc: &[u32; 512],
    nextl: &[u16; 512],
    dtab: &[u8; 512],
    dcc: &[u32; 32],
    i: usize,
    s: usize,
    base: u32,
    pcd: usize,
) {
    let mut lo = 3usize;
    let mut k = 0usize;
    while k < nc && k < 16 {
        let c = cands[k];
        let len = (c % 512) as usize;
        let dd = (c >> 9) as usize;
        let ds = dsym(dtab, dd) % 32;
        let bd = base.wrapping_add(dcc[ds]);
        relax_run(pa, lc, nextl, i, lo, len, bd, c & !511u32);
        lo = len + 1;
        if dd != pcd && (k + BEXT_TOP >= nc) {
            let r = back_best(input, pa, lc, i, s, len, dd);
            if r.0 > 0 {
                relax_one(pa, i + len, r.1.wrapping_add(dcc[ds]), (c & !511u32) | (len + r.0) as u32);
                if BTRUNC == 1 {
                    // the extended match may also end early: lengths reaching i+3 .. i+len-1
                    let j = i - r.0;
                    let pj = (pa[j % RING] >> 32) as u32;
                    relax_run(pa, lc, nextl, j, r.0 + 3, r.0 + len - 1, pj.wrapping_add(dcc[ds]), c & !511u32);
                }
            }
        }
        k += 1;
    }
}

/// Drop candidates farther than `cd` from the end of the list (they are shorter than the
/// continuation at `cd`); returns the new count.
#[inline(always)]
pub fn drop_farther(cands: &[u32; 16], nc0: usize, cd: usize) -> usize {
    let mut nc = nc0;
    while nc > 0 && (cands[(nc - 1) % 16] >> 9) as usize > cd {
        nc -= 1;
    }
    nc
}


// ───────────────────────── engine D (r19/da design, r20/prep provable form): mB dynamic program + backward refinement ─────────────────────────
// Forward: `d_parse` = `dp_parse` with every searched position ("node") recorded: its candidates
// (len | (dist-1) << 9 | backext << 24) followed by [position, count], in a stream `rs`. The forward DP's own
// parse gives the first statistics. Backward: `d_dp` runs a shortest path from the end under per-encoder-block
// Huffman-length costs over the nodes (every length of every candidate), the gaps between nodes (literal or the
// continuation of the node's longest candidate) and pushes each candidate back over its backward extension
// (same end, earlier start). The result is a token list for `emit` (which re-checks every match).
// Search code: totality only. Every function is total for all arguments except `d_parse` (callers guarantee
// 16 <= n and n + n does not wrap, as for `dp_parse`) and the copies of mB helpers (`d_walk`, `d_back_best`,
// `d_relax_cands`, `d_fill_nextl`), which keep mB's contracts.

/// One block's cost table (1/16 bit): [0..256) literals, [256..515) lengths 0..258 (code + extra),
/// [520..550) distance codes (code + extra).
pub const D_TS: usize = 560;
pub const D_UNSET: u64 = 0x3FFF_FFFF_0000_0000;
/// Choice word of a literal (bit 31 set, length bits 0): a match of equal cost compares lower and wins the tie.
pub const D_LIT: u64 = 0x8000_0000;
/// Statistics of a token-list plan: one cost table per encoder block of D_BLOCK tokens.
pub const D_BLOCK: usize = 16384;
/// The backward DP keeps its cells (cost << 32 | choice) for a sliding window of positions in a ring: a cell is
/// read at most 258 positions above the sweep and pushed at most 255 below it.
pub const D_RING: usize = 1024;

// ── shared helpers (total, no contract) ──

/// `v.push(x)` unless the vector already holds `usize::MAX` entries (it never does): a push that cannot panic.
#[inline(always)]
pub fn d_push32(v: &mut Vec<u32>, x: u32) {
    if v.len() < v.len().saturating_add(1) {
        v.push(x);
    }
}

/// `s[i]` as an index, 0 out of range.
#[inline(always)]
pub fn d_byte(s: &[u8], i: usize) -> usize {
    if i < s.len() {
        s[i] as usize
    } else {
        0
    }
}

/// The ring cell of position `i` (a function: a direct array read between two loops of one function is not
/// translated by the extraction).
#[inline(always)]
pub fn d_cell(ring: &[u64; D_RING], i: usize) -> u64 {
    ring[i % D_RING]
}

/// The smaller of `a` and `b`.
#[inline(always)]
pub fn d_min(a: usize, b: usize) -> usize {
    if a < b {
        a
    } else {
        b
    }
}

// ── part 1: cost tables ──

/// The lighter of the next leaf `a` and the next internal node `b` (internal nodes exist below `nx`):
/// (node, a, b) after taking it.
#[inline(always)]
pub fn d_take(w: &[u64; 576], a: usize, b: usize, ns: usize, nx: usize) -> (usize, usize, usize) {
    if a < ns && (b >= nx || w[a % 576] <= w[b % 576]) {
        (a, a + 1, b)
    } else {
        (b, a, b.wrapping_add(1))
    }
}

/// The code length of a leaf at tree depth `d`: clamped to 1..=15.
#[inline(always)]
pub fn d_clamp_len(d: u8) -> u32 {
    if d > 15 {
        15
    } else if d == 0 {
        1
    } else {
        d as u32
    }
}

/// Huffman code lengths of freq[0..m) (m <= 288), limited to 15 by clamping and lengthening the rarest codes
/// until the Kraft sum fits; len[i] = 0 for unused symbols. Returns the longest length used.
pub fn d_huff(freq: &[u32; 288], m: usize, len: &mut [u8; 288]) -> u32 {
    let mut sym = [0u16; 288];
    let mut ns = 0usize;
    let mut i = 0usize;
    while i < m && i < 288 {
        let f = freq[i];
        if f > 0 {
            let mut j = ns;
            while j > 0 && freq[sym[(j - 1) % 288] as usize % 288] > f {
                sym[j % 288] = sym[(j - 1) % 288];
                j -= 1;
            }
            sym[j % 288] = i as u16;
            ns = ns.wrapping_add(1);
        }
        len[i] = 0;
        i += 1;
    }
    if ns == 0 {
        return 1;
    }
    if ns == 1 {
        len[sym[0] as usize % 288] = 1;
        return 1;
    }
    let mut w = [0u64; 576];
    let mut par = [0u16; 576];
    let mut k = 0usize;
    while k < ns {
        w[k % 576] = freq[sym[k % 288] as usize % 288] as u64;
        k += 1;
    }
    let mut a = 0usize;
    let mut b = ns;
    let mut nx = ns;
    // (nx + 1) / 2 < ns  <=>  nx + 1 < 2 * ns
    while nx < 575 && (nx + 1) / 2 < ns {
        let (x, a1, b1) = d_take(&w, a, b, ns, nx);
        let (y, a2, b2) = d_take(&w, a1, b1, ns, nx);
        w[nx % 576] = w[x % 576].wrapping_add(w[y % 576]);
        par[x % 576] = nx as u16;
        par[y % 576] = nx as u16;
        a = a2;
        b = b2;
        nx += 1;
    }
    let mut depth = [0u8; 576];
    let mut q = nx.saturating_sub(1);
    while q > 0 {
        q -= 1;
        depth[q % 576] = depth[par[q % 576] as usize % 576].wrapping_add(1);
    }
    let mut mx = 1u32;
    let mut kraft = 0u64;
    k = 0;
    while k < ns {
        let l = d_clamp_len(depth[k % 576]);
        // 32768 >> l = 1 << (15 - l) for l in 1..=15
        kraft = kraft.wrapping_add(32768u64 >> (l % 16));
        if l > mx {
            mx = l;
        }
        len[sym[k % 288] as usize % 288] = l as u8;
        k += 1;
    }
    let mut r = 0usize;
    let mut fuel = 4608usize; // 288 symbols x 16 steps
    while kraft > 32768 && r < ns && fuel > 0 {
        fuel -= 1;
        let s2 = sym[r % 288] as usize % 288;
        let l = len[s2];
        if l < 15 {
            kraft = kraft.wrapping_sub(1u64 << (14 - l as u32));
            if l as u32 + 1 > mx {
                mx = l as u32 + 1;
            }
            len[s2] = l + 1;
        } else {
            r += 1;
        }
    }
    mx
}

/// Entropy cost (1/16 bit) of a symbol with count `f` when the total's log2 is `lt` / 16: an unseen symbol costs
/// one bit more than the total's log; clamped to 8..=256.
#[inline(always)]
pub fn d_ecost(f: u32, lt: u32) -> u32 {
    let e = if f == 0 { lt.saturating_add(16) } else { lt.saturating_sub(log2_16(f)) };
    if e < 8 {
        8
    } else if e > 256 {
        256
    } else {
        e
    }
}

/// A symbol's cost under cost kind `ck` from its Huffman cost `h` and entropy cost `e`: 0 `h`, 1 `e`, 2 their
/// mean, 3 / 4 `h` moved towards `e` by at most 6/16 or 12/16 bit (a tie-break).
#[inline(always)]
pub fn d_mix(h: u32, e: u32, ck: usize) -> u32 {
    if ck == 0 {
        h
    } else if ck == 1 {
        e
    } else if ck == 2 {
        h.wrapping_add(e) / 2
    } else {
        let lim = if ck == 3 { 6u32 } else { 12u32 };
        if e > h {
            let g = e - h;
            h.wrapping_add(if g > lim { lim } else { g })
        } else {
            let g = h - e;
            h.wrapping_sub(if g > lim { lim } else { g })
        }
    }
}

/// Symbol costs (1/16 bit) of freq[0..m) under cost kind `ck` (see `d_mix`).
/// `hl` = Huffman lengths (0 = unused symbol, priced `unseen` bits).
pub fn d_sym_costs(freq: &[u32; 288], m: usize, hl: &[u8; 288], unseen: u32, ck: usize, out: &mut [u32; 288]) {
    let mut total = 0u32;
    let mut i = 0usize;
    while i < m && i < 288 {
        total = total.saturating_add(freq[i]);
        i += 1;
    }
    let lt = log2_16(total.saturating_add(1));
    i = 0;
    while i < m && i < 288 {
        let hb = if hl[i] == 0 { unseen } else { hl[i] as u32 };
        let e = d_ecost(freq[i], lt);
        out[i] = d_mix(hb.wrapping_mul(16), e, ck);
        i += 1;
    }
}

/// Bits charged for a symbol without a code: one more than the longest code, at most 15.
#[inline(always)]
pub fn d_unseen(mx: u32) -> u32 {
    if mx < 15 {
        mx + 1
    } else {
        15
    }
}

/// Append one block's cost table built from its symbol counts (lit/len counts at 0..286, distance codes in df).
pub fn d_push_table(tabs: &mut Vec<u32>, lf: &[u32; 288], df: &[u32; 288], lsym: &[u8; 512], ck: usize) {
    let mut ll = [0u8; 288];
    let mut dl = [0u8; 288];
    let mxl = d_huff(lf, 286, &mut ll);
    let mxd = d_huff(df, 30, &mut dl);
    let mut lcst = [0u32; 288];
    let mut dcst = [0u32; 288];
    d_sym_costs(lf, 286, &ll, d_unseen(mxl), ck, &mut lcst);
    d_sym_costs(df, 30, &dl, d_unseen(mxd), ck, &mut dcst);
    let mut i = 0usize;
    while i < 256 {
        d_push32(tabs, lcst[i]);
        i += 1;
    }
    let mut l = 0usize;
    while l < 264 {
        let c = lsym[l % 512] as usize % 32;
        let x = if l < 3 || l > 258 { 0x00FF_FFFF } else { lcst[(257 + c) % 288].wrapping_add(LEXTRA[c].wrapping_mul(16)) };
        d_push32(tabs, x);
        l += 1;
    }
    i = 0;
    while i < 40 {
        let x = if i < 30 { dcst[i].wrapping_add(DEXTRA[i % 32].wrapping_mul(16)) } else { 0 };
        d_push32(tabs, x);
        i += 1;
    }
}

/// At an encoder-block boundary (`t` == D_BLOCK tokens counted, next token at `p`): append the block's cost table,
/// clear the counts, record the next block's start. Returns the token count of the current block.
#[inline(always)]
pub fn d_block_end(tabs: &mut Vec<u32>, bstart: &mut Vec<u32>, lf: &mut [u32; 288], df: &mut [u32; 288], lsym: &[u8; 512], ck: usize, p: usize, t: usize) -> usize {
    if t != D_BLOCK {
        return t;
    }
    lf[256] = 1;
    d_push_table(tabs, lf, df, lsym, ck);
    *lf = [0u32; 288];
    *df = [0u32; 288];
    d_push32(bstart, p as u32);
    0
}

/// Statistics of a token-list plan (`len | dist << 9`, 0 = literal): one cost table per encoder block
/// (D_BLOCK tokens) and the input position where each block starts.
#[inline(never)]
pub fn d_tally(s: &[u8], plan: &Vec<u32>, lsym: &[u8; 512], dtab: &[u8; 512], tabs: &mut Vec<u32>, bstart: &mut Vec<u32>, ck: usize) {
    let mut lf = [0u32; 288];
    let mut df = [0u32; 288];
    let mut p = 0usize;
    let mut t = 0usize;
    let mut k = 0usize;
    d_push32(bstart, 0);
    while p < s.len() {
        t = d_block_end(tabs, bstart, &mut lf, &mut df, lsym, ck, p, t);
        let v = get0(plan, k);
        k = k.wrapping_add(1);
        let len = (v % 512) as usize;
        if len >= 3 && len <= s.len() - p {
            let c = lsym[len % 512] as usize % 32;
            lf[(257 + c) % 288] = lf[(257 + c) % 288].wrapping_add(1);
            let dc = dsym(dtab, (v >> 9) as usize) % 32;
            df[dc] = df[dc].wrapping_add(1);
            p += len;
        } else {
            lf[s[p] as usize] = lf[s[p] as usize].wrapping_add(1);
            p += 1;
        }
        t = t.wrapping_add(1);
    }
    lf[256] = 1;
    d_push_table(tabs, &lf, &df, lsym, ck);
}

/// Block cost table at offset `tb` of `tabs` into fixed arrays (literals, lengths, distance codes).
pub fn d_load(tabs: &[u32], tb: usize, litc: &mut [u32; 256], lc: &mut [u32; 512], dcc: &mut [u32; 32]) {
    let mut i = 0usize;
    while i < 256 {
        litc[i] = get0(tabs, tb.wrapping_add(i));
        i += 1;
    }
    let mut l = 0usize;
    while l < 512 {
        lc[l] = if l < 264 { get0(tabs, tb.wrapping_add(256).wrapping_add(l)) } else { 0x00FF_FFFF };
        l += 1;
    }
    i = 0;
    while i < 32 {
        dcc[i] = get0(tabs, tb.wrapping_add(520).wrapping_add(i));
        i += 1;
    }
}

// ── part 2: backward DP ──

/// `x` limited to the range stop ..= q (stop when x <= stop).
#[inline(always)]
pub fn d_clip(x: usize, stop: usize, q: usize) -> usize {
    if x > stop {
        if x < q {
            x
        } else {
            q
        }
    } else {
        stop
    }
}

/// Gap positions hi-1 down to stop: literal, or the continuation that ends at `end` (while at least 3 bytes
/// remain), or a value pushed earlier (positions >= lo). The choice of every position goes to `out`. Returns the
/// cell of `stop` (`nxt0` when the range is empty). `kcd` = the continuation's distance cost, `chd` = its
/// distance * 512.
pub fn d_gap(s: &[u8], litc: &[u32; 256], lc: &[u32; 512], ring: &mut [u64; D_RING], out: &mut [u32], hi: usize, stop: usize, end: usize, kcd: u64, chd: u64, lo: usize, nxt0: u64, dlit: u64) -> u64 {
    let mut q = hi;
    let mut nxt = nxt0;
    // literal-only part: fewer than 3 bytes of the continuation remain (positions above end - 3)
    let mid = d_clip(end.saturating_sub(2), stop, hi);
    while q > mid && q <= s.len() && q <= out.len() {
        q -= 1;
        let mut v = (nxt >> 32).wrapping_add(litc[s[q] as usize] as u64) << 32 | dlit;
        if q >= lo {
            let o = ring[q % D_RING];
            if o < v {
                v = o;
            }
        }
        ring[q % D_RING] = v;
        out[q] = v as u32;
        nxt = v;
    }
    // continuation part, first the positions pushes have reached
    let kc = (d_cell(ring, end) >> 32).wrapping_add(kcd);
    let s1 = d_clip(lo, stop, q);
    while q > s1 && q <= s.len() && q <= out.len() && end >= q {
        q -= 1;
        let rem = end - q;
        let vl = (nxt >> 32).wrapping_add(litc[s[q] as usize] as u64) << 32 | dlit;
        let vc = (kc.wrapping_add(lc[rem % 512] as u64) << 32) | (chd.wrapping_add(rem as u64));
        let mut v = if vc < vl { vc } else { vl };
        let o = ring[q % D_RING];
        if o < v {
            v = o;
        }
        ring[q % D_RING] = v;
        out[q] = v as u32;
        nxt = v;
    }
    while q > stop && q <= s.len() && q <= out.len() && end >= q {
        q -= 1;
        let rem = end - q;
        let vl = (nxt >> 32).wrapping_add(litc[s[q] as usize] as u64) << 32 | dlit;
        let vc = (kc.wrapping_add(lc[rem % 512] as u64) << 32) | (chd.wrapping_add(rem as u64));
        let v = if vc < vl { vc } else { vl };
        ring[q % D_RING] = v;
        out[q] = v as u32;
        nxt = v;
    }
    nxt
}

/// The cheapest end of one candidate at node p over the lengths lo .. e - 1: min over l of cost(p + l) + length
/// cost, packed as value << 9 | l (the value is below 2^40).
#[inline(always)]
pub fn d_best_len(lc: &[u32; 512], ring: &[u64; D_RING], p: usize, lo: usize, e: usize) -> u64 {
    let mut bv = 0xFFFF_FFFF_FFFF_FFFFu64;
    let mut l = lo;
    while l < e {
        let v = (((ring[p.wrapping_add(l) % D_RING] >> 32).wrapping_add(lc[l % 512] as u64)) << 9) | (l as u64);
        if v < bv {
            bv = v;
        }
        l += 1;
    }
    bv
}

/// Push a candidate's end `p + el` back over `t` earlier starts (each start p - x pays the length el + x <= 258).
#[inline(always)]
pub fn d_push(lc: &[u32; 512], ring: &mut [u64; D_RING], p: usize, el: usize, t: usize, f: u64, chd: u64) {
    let mut x = 1usize;
    while x <= t && x <= p && el <= 258 && x <= 258 - el {
        let v = (f.wrapping_add(lc[(el + x) % 512] as u64) << 32) | (chd.wrapping_add((el + x) as u64));
        let o = ring[(p - x) % D_RING];
        ring[(p - x) % D_RING] = if v < o { v } else { o };
        x += 1;
    }
}

/// Lower st[1] (the lowest initialised position) to `z0`: the cells z0 .. min(st[1], p) are set to D_UNSET first.
#[inline(always)]
pub fn d_init(ring: &mut [u64; D_RING], st: &mut [u64; 2], p: usize, z0: usize) {
    let lo = st[1] as usize;
    if z0 < lo {
        let top = d_min(lo, p);
        let mut z = z0;
        while z < top {
            ring[z % D_RING] = D_UNSET;
            z += 1;
        }
        st[1] = z0 as u64;
    }
}

/// The back-extension pushes of one candidate of node p (length `len`, cheapest end `bl`, extension `t`): the
/// same end from x <= t bytes earlier, and with `pbest` == 1 also the cheapest end.
#[inline(always)]
pub fn d_back(lc: &[u32; 512], ring: &mut [u64; D_RING], p: usize, len: usize, bl: usize, t: usize, dcst: u64, chd2: u64, pbest: usize, st: &mut [u64; 2]) {
    if t == 0 {
        return;
    }
    let tt = d_min(t, p);
    d_init(ring, st, p, p - tt);
    let f = (d_cell(ring, p.wrapping_add(len)) >> 32).wrapping_add(dcst);
    d_push(lc, ring, p, len, tt, f, chd2);
    if pbest == 1 && bl != len && bl >= 3 {
        let f2 = (d_cell(ring, p.wrapping_add(bl)) >> 32).wrapping_add(dcst);
        d_push(lc, ring, p, bl, tt, f2, chd2);
    }
}

/// One candidate `r` of node p (`room` = bytes from p to the end of the input): every length in (prev, len],
/// then its pushes. st[0] = the node's best cell so far, st[1] = the lowest initialised position. Returns the
/// new `prev` (unchanged for a malformed record).
#[inline(always)]
pub fn d_cand(lc: &[u32; 512], dcc: &[u32; 32], dtab: &[u8; 512], ring: &mut [u64; D_RING], r: u32, p: usize, prev: usize, room: usize, pbest: usize, st: &mut [u64; 2]) -> usize {
    let len = (r % 512) as usize;
    if len <= prev || len > 258 || len > room {
        return prev;
    }
    let dm = ((r >> 9) % 32768) as usize;
    let t = (r >> 24) as usize;
    let dcst = dcc[dsym(dtab, dm + 1) % 32] as u64;
    let chd2 = ((dm + 1) as u64) * 512;
    let bb = d_best_len(lc, ring, p, prev + 1, len + 1);
    let bl = (bb % 512) as usize;
    let cand = ((bb >> 9).wrapping_add(dcst) << 32) | chd2.wrapping_add(bl as u64);
    d_back(lc, ring, p, len, bl, t, dcst, chd2, pbest, st);
    let s0 = st[0];
    st[0] = if cand < s0 { cand } else { s0 };
    len
}

/// Step to the previous encoder block when `pos` lies below the current block's first position
/// (bs = [block, its first position]) and load that block's cost table.
#[inline(always)]
pub fn d_block(tabs: &[u32], bstart: &[u32], litc: &mut [u32; 256], lc: &mut [u32; 512], dcc: &mut [u32; 32], bs: &mut [usize; 2], pos: usize) {
    if pos < bs[1] && bs[0] > 0 {
        let b = bs[0] - 1;
        d_load(tabs, b.wrapping_mul(D_TS), litc, lc, dcc);
        bs[0] = b;
        bs[1] = get0(bstart, b) as usize;
    }
}

/// The longest candidate of the node record that ends at `e` (the last of its `k` candidates), 0 when it has none.
#[inline(always)]
pub fn d_top(rs: &[u32], e: usize, k: usize) -> u32 {
    if k > 0 {
        get0(rs, e.wrapping_sub(3))
    } else {
        0
    }
}

/// Where the continuation of node p's longest candidate (length `cl`) ends: p + cl, or p when it does not fit.
#[inline(always)]
pub fn d_end(p: usize, cl: usize, room: usize) -> usize {
    if cl <= room {
        p.wrapping_add(cl)
    } else {
        p
    }
}

/// Where a gap run below q stops: the current block's first position when it lies inside (p1, q), else p1.
#[inline(always)]
pub fn d_stop(bfirst: usize, p1: usize, q: usize) -> usize {
    if bfirst > p1 && bfirst < q {
        bfirst
    } else {
        p1
    }
}

/// The cell of node p: `best` over its literal and candidates, or the value pushed there (positions >= lo).
#[inline(always)]
pub fn d_node_best(ring: &[u64; D_RING], p: usize, lo: usize, best: u64) -> u64 {
    if p >= lo {
        let o = ring[p % D_RING];
        if o < best {
            o
        } else {
            best
        }
    } else {
        best
    }
}

/// Backward shortest path over the node stream `rs`. A cell is cost << 32 | choice (len + 512 * dist; D_LIT or 0
/// = literal) for the cheapest way from its position to the end; cells live in a ring, the choice of every
/// position is written to `out` (which `d_extract` then follows from 0). Positions >= lo that the sweep has not
/// reached hold D_UNSET or a pushed value.
/// pmode bit 0: also push each candidate's best end; bit 1: a match wins a cost tie against a literal.
#[inline(never)]
pub fn d_dp(s: &[u8], rs: &Vec<u32>, tabs: &Vec<u32>, bstart: &Vec<u32>, dtab: &[u8; 512], out: &mut [u32], pmode: usize) {
    let n = s.len();
    // tabs.len() / D_TS < bstart.len()  <=>  tabs.len() < bstart.len() * D_TS
    if out.len() < n || bstart.len() == 0 || tabs.len() / D_TS < bstart.len() {
        return;
    }
    let mut ring = [D_UNSET; D_RING];
    ring[n % D_RING] = 0;
    let mut litc = [0u32; 256];
    let mut lc = [0u32; 512];
    let mut dcc = [0u32; 32];
    let dlit = if pmode >= 2 { D_LIT } else { 0 };
    let pbest = pmode % 2;
    let mut st = [0u64, n as u64];
    let b0 = bstart.len() - 1;
    let mut bs = [b0, get0(bstart, b0) as usize];
    d_load(tabs, b0.wrapping_mul(D_TS), &mut litc, &mut lc, &mut dcc);
    let mut e = rs.len();
    let mut hi = n;
    while e >= 2 {
        let k = get0(rs, e - 1) as usize;
        let p = get0(rs, e - 2) as usize;
        if k > e - 2 || p >= hi {
            e = 0;
        } else {
            let a = e - 2 - k;
            let e2 = e - 2;
            let top = d_top(rs, e, k);
            let cl = (top % 512) as usize;
            let cdm = ((top >> 9) % 32768) as usize;
            let dslot = dsym(dtab, cdm + 1);
            let chd = ((cdm + 1) as u64) * 512;
            let room = n.saturating_sub(p);
            let end = d_end(p, cl, room);
            // gap (p, hi), high to low, block by block
            let lo = st[1] as usize;
            let p1 = p + 1;
            let mut q = hi;
            let mut nxt = d_cell(&ring, q);
            let mut fuel = bstart.len().saturating_add(1);
            while q > p1 && fuel > 0 {
                fuel -= 1;
                d_block(tabs, bstart, &mut litc, &mut lc, &mut dcc, &mut bs, q - 1);
                let stop = d_stop(bs[1], p1, q);
                nxt = d_gap(s, &litc, &lc, &mut ring, out, q, stop, end, dcc[dslot % 32] as u64, chd, lo, nxt, dlit);
                q = stop;
            }
            // node p
            d_block(tabs, bstart, &mut litc, &mut lc, &mut dcc, &mut bs, p);
            st[0] = (nxt >> 32).wrapping_add(litc[d_byte(s, p) % 256] as u64) << 32 | dlit;
            let mut prev = 2usize;
            let mut j = a;
            while j < e2 {
                prev = d_cand(&lc, &dcc, dtab, &mut ring, get0(rs, j), p, prev, room, pbest, &mut st);
                j += 1;
            }
            let best = d_node_best(&ring, p, lo, st[0]);
            ring[p % D_RING] = best;
            set_in(out, p, best as u32);
            hi = p;
            e = a;
        }
    }
}

/// The path from 0 through the choices in `out` as a token list (at most `n` entries).
pub fn d_extract(out: &[u32], n: usize, plan: &mut Vec<u32>) {
    let mut p = 0usize;
    while p < n && plan.len() < n {
        let v = get0(out, p);
        let len = (v % 512) as usize;
        if len >= 3 && len <= n - p && v < 0x8000_0000 {
            plan.push(v);
            p += len;
        } else {
            plan.push(0);
            p += 1;
        }
    }
}

// ── part 3: forward pass ──

/// Eight bytes at `i`, LAST byte most significant (0 when out of range): two such words differ first, counting
/// from the top, at the highest differing position.
#[inline(always)]
pub fn d_le8(s: &[u8], i: usize) -> u64 {
    let n = s.len();
    if n >= 8 && i <= n - 8 {
        ((s[i + 7] as u64) << 56)
            | ((s[i + 6] as u64) << 48)
            | ((s[i + 5] as u64) << 40)
            | ((s[i + 4] as u64) << 32)
            | ((s[i + 3] as u64) << 24)
            | ((s[i + 2] as u64) << 16)
            | ((s[i + 1] as u64) << 8)
            | (s[i] as u64)
    } else {
        0
    }
}

/// How far the match at `i` with distance `d` extends backwards, at most `max` bytes.
#[inline(always)]
pub fn d_backext(s: &[u8], i: usize, d: usize, max: usize) -> usize {
    // the extension stays inside the input: t <= i - d
    let cap = d_min(i.saturating_sub(d), max);
    let mut t = 0usize;
    let mut run = 1u32;
    while run == 1 && cap >= 8 && t <= cap - 8 {
        let a = i.wrapping_sub(t).wrapping_sub(8);
        let x = d_le8(s, a) ^ d_le8(s, a.wrapping_sub(d));
        if x == 0 {
            t += 8;
        } else {
            t += (x.leading_zeros() / 8) as usize;
            run = 0;
        }
    }
    while run == 1 && t < cap {
        let a = i.wrapping_sub(t).wrapping_sub(1);
        if a < s.len() && d <= a && s[a] == s[a - d] {
            t += 1;
        } else {
            run = 0;
        }
    }
    t
}

/// nextl with a full-length limit `flen` (see `fill_nextl`).
pub fn d_fill_nextl(lsym: &[u8; 512], nextl: &mut [u16; 512], flen: usize) {
    let mut l = 0usize;
    while l < 512 {
        if l < flen || l >= 257 {
            nextl[l] = (l + 1) as u16;
        } else {
            let mut e = l + 1;
            while e < 258 && lsym[e + 1] == lsym[l + 1] {
                e += 1;
            }
            nextl[l] = e as u16;
        }
        l += 1;
    }
}

/// 1 when `want` is among pc[0..pn).
#[inline(always)]
pub fn d_seen(pc: &[u32; 16], pn: usize, want: u32) -> u32 {
    let mut dup = 0u32;
    let mut z = 0usize;
    while z < pn && z < 16 {
        if pc[z] == want {
            dup = 1;
        }
        z += 1;
    }
    dup
}

/// 1 when the candidate `c` = (len, dist) of the node at `i` is already offered with the same end: by the running
/// continuation (cl, cd), or (`adj`: the previous node is at i - 1) by a candidate of the previous node.
#[inline(always)]
pub fn d_isdup(pc: &[u32; 16], pn: usize, c: u32, len: usize, dist: usize, cl: usize, cd: usize, adj: bool, dupmode: usize) -> u32 {
    if dupmode == 0 {
        return 0;
    }
    if cl >= 3 && cl == len && cd == dist {
        return 1;
    }
    if adj {
        return d_seen(pc, pn, c.wrapping_add(1));
    }
    0
}

/// Record one candidate `c` of the node at `i` when it is longer than `last` and well-formed, with its backward
/// extension (0 for a duplicate, see `d_isdup`). Returns the new `last`.
#[inline(always)]
pub fn d_rec_cand(input: &[u8], rs: &mut Vec<u32>, c: u32, i: usize, last: usize, pc: &[u32; 16], pn: usize, adj: bool, cl: usize, cd: usize, tbmax: usize, dupmode: usize) -> usize {
    let len = (c % 512) as usize;
    let dist = (c >> 9) as usize;
    if len <= last || dist < 1 || dist > i || dist > 32768 || len > 258 {
        return last;
    }
    let dup = d_isdup(pc, pn, c, len, dist, cl, cd, adj, dupmode);
    let t = if dup == 0 { d_backext(input, i, dist, d_min(258 - len, tbmax)) } else { 0 };
    d_push32(rs, (len as u32) | (((dist - 1) as u32) << 9) | ((t as u32) << 24));
    len
}

/// Record the node at `i`: candidates with their backward extension (0 for a candidate that the previous
/// node or the running continuation already offers with the same end), then [i, count].
#[inline(always)]
pub fn d_record(input: &[u8], rs: &mut Vec<u32>, cands: &[u32; 16], nc: usize, i: usize, pc: &[u32; 16], pn: usize, ppos: usize, cl: usize, cd: usize, tbmax: usize, dupmode: usize) {
    let adj = ppos.wrapping_add(1) == i;
    let l0 = rs.len();
    let mut q = 0usize;
    let mut last = 2usize;
    while q < nc && q < 16 {
        last = d_rec_cand(input, rs, cands[q], i, last, pc, pn, adj, cl, cd, tbmax, dupmode);
        q += 1;
    }
    // the count = the entries pushed for this node
    let cnt = rs.len().wrapping_sub(l0) as u32;
    d_push32(rs, i as u32);
    d_push32(rs, cnt);
}

/// `walk` with a stop once a match of at least `nice` bytes is known.
#[inline(always)]
pub fn d_walk(
    s: &[u8],
    prev: &[u32; WN],
    i: usize,
    start: usize,
    depth: usize,
    b8: u64,
    cap: usize,
    cands: &mut [u32; 16],
    nc0: usize,
    best0: usize,
    nice: usize,
) -> (usize, usize) {
    let mut nc = nc0;
    let mut best = best0;
    let mut c = start;
    let mut k = depth;
    while k > 0 {
        let d = i.wrapping_sub(c);
        if d.wrapping_sub(1) < 32768 && best < cap && best < nice && nc < 15 {
            let l = probe(s, c, i, b8, cap, best);
            if l > 0 && nc < 15 {
                cands[nc % 16] = (l as u32) | ((d as u32) << 9);
                nc += 1;
                best = l;
            }
            let nx = prev[c % WN] as usize;
            if nx < c {
                c = nx;
                k -= 1;
            } else {
                k = 0;
            }
        } else {
            k = 0;
        }
    }
    (nc, best)
}

/// `back_best` with a limit `tmax` on the backward extension.
pub fn d_back_best(input: &[u8], pa: &[u64; RING], lc: &[u32; 512], i: usize, s: usize, len: usize, dd: usize, tmax: usize) -> (usize, u32) {
    let mut t = 0usize;
    let mut bt = 0usize;
    let mut bv = INF;
    while t < tmax && len + t < 258 && i >= t + 1 + dd && i - t - 1 >= s && input[i - t - 1] == input[i - t - 1 - dd] {
        t += 1;
        let v = ((pa[(i - t) % RING] >> 32) as u32).wrapping_add(lc[(len + t) % 512]);
        if v < bv {
            bv = v;
            bt = t;
        }
    }
    (bt, bv)
}

/// `relax_cands` of the forward DP with a backward-extension limit `fback` (0 = none; the forward DP only has to
/// give realistic statistics).
pub fn d_relax_cands(
    input: &[u8],
    pa: &mut [u64; RING],
    cands: &[u32; 16],
    nc: usize,
    lc: &[u32; 512],
    nextl: &[u16; 512],
    dtab: &[u8; 512],
    dcc: &[u32; 32],
    i: usize,
    s: usize,
    base: u32,
    pcd: usize,
    fback: usize,
) {
    let mut lo = 3usize;
    let mut k = 0usize;
    while k < nc && k < 16 {
        let c = cands[k];
        let len = (c % 512) as usize;
        let dd = (c >> 9) as usize;
        let ds = dsym(dtab, dd) % 32;
        let bd = base.wrapping_add(dcc[ds]);
        relax_run(pa, lc, nextl, i, lo, len, bd, c & !511u32);
        lo = len + 1;
        if fback > 0 && dd != pcd && (k + BEXT_TOP >= nc) {
            let r = d_back_best(input, pa, lc, i, s, len, dd, fback);
            if r.0 > 0 {
                relax_one(pa, i + len, r.1.wrapping_add(dcc[ds]), (c & !511u32) | (len + r.0) as u32);
            }
        }
        k += 1;
    }
}

/// The forward relaxation of a searched position: mB's `relax_cands` (fback >= 100) or `d_relax_cands`.
#[inline(always)]
pub fn d_relax(
    input: &[u8],
    pa: &mut [u64; RING],
    cands: &[u32; 16],
    nc: usize,
    lc: &[u32; 512],
    nextl: &[u16; 512],
    dtab: &[u8; 512],
    dcc: &[u32; 32],
    i: usize,
    s: usize,
    base: u32,
    pcd: usize,
    fback: usize,
) {
    if fback >= 100 {
        relax_cands(input, pa, cands, nc, lc, nextl, dtab, dcc, i, s, base, pcd);
    } else {
        d_relax_cands(input, pa, cands, nc, lc, nextl, dtab, dcc, i, s, base, pcd, fback);
    }
}

/// `dp_parse` with node recording (see the section comment); `flen` = full-length limit of the forward DP.
#[inline(never)]
pub fn d_parse(input: &[u8], plan: &mut Vec<u32>, rs: &mut Vec<u32>, ct: usize, lazyn: usize, d4: usize, d7: usize, skip: usize, h3d: usize, flen: usize, tbmax: usize, lz2max: usize, dupmode: usize, fback: usize, d7l: usize, d7e: usize, nice: usize) {
    let huff = 0usize;
    let n = input.len();
    let mut head3 = [0u32; H3N];
    let mut head4 = [0u32; H4N];
    let mut prev4 = [0u32; WN];
    let mut head7 = [0u32; H7N];
    let mut prev7 = [0u32; WN];
    let mut pa = [UNREACHED; RING];
    let mut tb = [0u32; RING];
    let mut lsym = [0u8; 512];
    let mut dtab = [0u8; 512];
    fill_tables(&mut lsym, &mut dtab);
    let mut nextl = [0u16; 512];
    d_fill_nextl(&lsym, &mut nextl, flen);
    let mut lf = [0u32; 320];
    let mut df = [0u32; 32];
    init_counts(input, &mut lf, &mut df);
    let mut litc = [0u32; 256];
    let mut lc = [0u32; 512];
    let mut dcc = [0u32; 32];
    make_costs(&lf, &df, &lsym, &mut litc, &mut lc, &mut dcc, huff);
    halve(&mut lf, &mut df);
    halve(&mut lf, &mut df);
    let lim = n - 8; // callers guarantee n >= 16
    let sh7 = 64 - 8 * KB7;
    let mut s = 0usize;
    open_chunk(&mut pa, 0);
    let mut next_upd = UPD;
    let mut cands = [0u32; 16];
    let mut pc = [0u32; 16];
    let mut pn = 0usize;
    let mut ppos = n;
    let mut cl = 0usize;
    let mut cd = 0usize;
    let mut cdc = 0u32;
    let mut i = 0usize;
    let mut anchor = 0usize;
    let mut alen = 0usize;
    while i < lim {
        if i > s {
            pa[(i + 258) % RING] = UNREACHED;
        }
        let b8 = be8(input, i);
        let hc = insert_pos(&mut head3, &mut head4, &mut prev4, &mut head7, &mut prev7, i, b8, sh7);
        let base = (pa[i % RING] >> 32) as u32;
        relax_one(&mut pa, i + 1, base.wrapping_add(litc[(b8 >> 56) as usize % 256]), 0);
        let lzn = if alen <= lz2max { lazyn } else { 1 };
        let lazy_here = i.wrapping_sub(anchor).wrapping_sub(1) < lzn;
        // long-chain depth of this node, should it be searched (bound here: the search block below is then the
        // same text on every path of the extraction)
        let dnode = if lazy_here { d7l } else if cl >= 1 { d7e } else { d7 };
        if cl >= ct && cl >= 3 && !lazy_here {
            relax_one(&mut pa, i + cl, base.wrapping_add(cdc).wrapping_add(lc[cl % 512]), ((cd as u32) << 9) | cl as u32);
            cl -= 1;
            i += 1;
        } else {
            let mut cap = n - i;
            if cap > 258 {
                cap = 258;
            }
            let mut nc = 0usize;
            let mut best = 2usize;
            let d3 = i.wrapping_sub(hc.0);
            let p3 = d3.wrapping_sub(1) < h3d;
            if p3 {
                let l3 = probe(input, hc.0, i, b8, cap, 2);
                if l3 > 0 {
                    cands[0] = (l3 as u32) | ((d3 as u32) << 9);
                    nc = 1;
                    best = l3;
                }
            }
            let s4 = skip_same(&prev4, hc.1, d4, p3 && hc.1 == hc.0);
            let w = d_walk(input, &prev4, i, s4.0, s4.1, b8, cap, &mut cands, nc, best, nice);
            nc = w.0;
            best = w.1;
            let dep7 = if best >= 4 || d4 == 0 { dnode } else { 0 };
            let s7 = skip_same(&prev7, hc.2, dep7, (p3 && hc.2 == hc.0) || (d4 > 0 && hc.2 == hc.1));
            let w2 = d_walk(input, &prev7, i, s7.0, s7.1, b8, cap, &mut cands, nc, best, nice);
            nc = w2.0;
            best = w2.1;
            if cl > best && cl <= cap {
                nc = drop_farther(&cands, nc, cd);
                cands[nc % 16] = (cl as u32) | ((cd as u32) << 9);
                if nc < 16 {
                    nc += 1;
                }
                best = cl;
            }
            d_record(input, rs, &cands, nc, i, &pc, pn, ppos, cl, cd, tbmax, dupmode);
            pc = cands;
            pn = nc;
            ppos = i;
            let pcd = if cl >= 3 { cd } else { 0 };
            alen = next_anchor(alen, best, cl, best);
            anchor = next_anchor(anchor, i, cl, best);
            if nc > 0 {
                let top = cands[(nc - 1) % 16];
                cl = ((top % 512) as usize).saturating_sub(1);
                cd = (top >> 9) as usize;
                cdc = dcc[dsym(&dtab, cd) % 32];
            } else {
                cl = 0;
            }
            if best >= skip && nc > 0 {
                let c0 = cands[(nc - 1) % 16];
                let d0 = (c0 >> 9) as usize;
                let l0 = best;
                let t = ext_back(input, i, d0, s, 258 - l0 % 259);
                let st = i - t;
                backtrack(input, &pa, plan, s, st, &lsym, &dtab, &mut lf, &mut df, &mut tb);
                if plan.len() < n {
                    plan.push(c0.wrapping_add(t as u32));
                }
                let ls = lsym[(l0 + t) % 512] as usize % 32;
                lf[257 + ls] = lf[257 + ls].wrapping_add(1);
                let ds = dsym(&dtab, d0) % 32;
                df[ds] = df[ds].wrapping_add(1);
                let mut end = i + l0;
                if end > lim {
                    end = lim;
                }
                insert_range(input, &mut head3, &mut head4, &mut prev4, &mut head7, &mut prev7, i + 1, end, sh7);
                i = i + l0;
                s = i;
                cl = 0;
                open_chunk(&mut pa, s);
            } else {
                d_relax(input, &mut pa, &cands, nc, &lc, &nextl, &dtab, &dcc, i, s, base, pcd, fback);
                i += 1;
            }
        }
        if i - s >= CHUNK {
            backtrack(input, &pa, plan, s, i, &lsym, &dtab, &mut lf, &mut df, &mut tb);
            s = i;
            open_chunk(&mut pa, s);
        }
        if i >= next_upd {
            next_upd = i + UPD;
            update_costs(&mut lf, &mut df, &lsym, &mut litc, &mut lc, &mut dcc, huff);
            cdc = dcc[dsym(&dtab, cd) % 32];
        }
    }
    if i > s && i <= n {
        let e = if i < lim { i } else { lim };
        if e > s {
            backtrack(input, &pa, plan, s, e, &lsym, &dtab, &mut lf, &mut df, &mut tb);
        }
    }
}

// ── glue ──

/// Engine D with knobs k (see D_KNOBS): the token-list plan.
#[inline(never)]
pub fn d_plan_k(input: &[u8], out: &mut [u32], k: &[usize; 17]) -> Vec<u32> {
    let n = input.len();
    let mut plan: Vec<u32> = Vec::with_capacity(n / 2 + 16);
    if n < 16 || n.wrapping_add(n) <= n {
        return plan;
    }
    let mut rs: Vec<u32> = Vec::with_capacity(n / 2 + 64);
    d_parse(input, &mut plan, &mut rs, k[0], k[1], k[2], k[3], k[4], k[5], k[8], k[9], k[10], k[11], k[12], k[13], k[14], k[15]);
    let mut lsym = [0u8; 512];
    let mut dtab = [0u8; 512];
    fill_tables(&mut lsym, &mut dtab);
    let passes = k[6];
    let mut pass = 0usize;
    while pass < passes {
        let mut tabs: Vec<u32> = Vec::with_capacity(D_TS * 4);
        let mut bstart: Vec<u32> = Vec::with_capacity(16);
        d_tally(input, &plan, &lsym, &dtab, &mut tabs, &mut bstart, k[16]);
        d_dp(input, &rs, &tabs, &bstart, &dtab, out, k[7]);
        let mut next: Vec<u32> = Vec::with_capacity(n / 2 + 16);
        d_extract(out, n, &mut next);
        plan = next;
        pass += 1;
    }
    plan
}

// ───────────────────────────── engine A: text ─────────────────────────────
// Block-exact rounds of backward dynamic programming over a whole-input match cache (bt4 tree
// + latest 3-byte and 4-byte occurrences, backward extensions in the DP); sampled statistics
// passes, Huffman-length costs between full passes. Knobs: tree depth, skip length, passes.

pub const A_NICE: usize = 128;
pub const A_HB: u32 = 16;
pub const BLOCK_TOKENS: usize = 16384;
pub const A_MARGIN: usize = 512;
pub const A_SAMPLE: usize = 4;
pub const A_SEG: usize = 4096;
pub const A_SLACK: usize = 64;

/// 64 * log2(1 + i/128), i = 0..127: fractional part of the fixed-point logarithm.
pub const A_LOG_FRAC: [u32; 128] = [
    0, 1, 1, 2, 3, 4, 4, 5, 6, 6, 7, 8, 8, 9, 10, 10, 11, 12, 12, 13, 13, 14, 15, 15, 16, 16,
    17, 18, 18, 19, 19, 20, 21, 21, 22, 22, 23, 23, 24, 25, 25, 26, 26, 27, 27, 28, 28, 29, 29,
    30, 30, 31, 31, 32, 32, 33, 34, 34, 35, 35, 35, 36, 36, 37, 37, 38, 38, 39, 39, 40, 40, 41,
    41, 42, 42, 43, 43, 43, 44, 44, 45, 45, 46, 46, 47, 47, 47, 48, 48, 49, 49, 50, 50, 50, 51,
    51, 52, 52, 52, 53, 53, 54, 54, 55, 55, 55, 56, 56, 56, 57, 57, 58, 58, 58, 59, 59, 60, 60,
    60, 61, 61, 61, 62, 62, 63, 63, 63, 64,
];

/// 64 * log2(x) for x >= 1 (0 for x = 0).
#[inline(always)]
pub fn a_lg64(x: u32) -> u32 {
    if x == 0 {
        0
    } else {
        let k = 31 - x.leading_zeros();
        let m = if k >= 7 { x >> (k - 7) } else { x << (7 - k) };
        64 * k + A_LOG_FRAC[(m as usize) % 128]
    }
}

/// DEFLATE length code index 0..28 for a length 3..258.
#[inline(always)]
pub fn a_len_slot(len: usize) -> usize {
    if len >= 258 {
        28
    } else if len <= 10 {
        if len >= 3 { len - 3 } else { 0 }
    } else {
        let x = (len - 3) as u32;
        let k = 31 - x.leading_zeros();
        (4 * (k - 1) + ((x >> (k - 2)) & 3)) as usize
    }
}

/// Extra bits of a length code index.
pub fn a_len_extra(slot: usize) -> u32 {
    if slot < 8 || slot >= 28 { 0 } else { (slot / 4 - 1) as u32 }
}

/// Distance code index for x = dist - 1 (x < 32768), without failing arithmetic.
#[inline(always)]
pub fn a_slot_of(x: u32) -> u32 {
    if x < 4 {
        x
    } else {
        let k = 31u32.wrapping_sub(x.leading_zeros());
        k.wrapping_mul(2).wrapping_add(x.wrapping_shr(k.wrapping_sub(1)) & 1)
    }
}

/// Extra bits of a distance code index.
pub fn a_dist_extra(slot: usize) -> u32 {
    if slot < 4 { 0 } else { (slot / 2 - 1) as u32 }
}

/// Eight bytes at `i` as one big-endian word (0 when fewer than 8 bytes remain).
pub fn a_word_at(s: &[u8], i: usize) -> u64 {
    if i + 8 <= s.len() {
        let mut w = s[i] as u64;
        w = (w << 8) | s[i + 1] as u64;
        w = (w << 8) | s[i + 2] as u64;
        w = (w << 8) | s[i + 3] as u64;
        w = (w << 8) | s[i + 4] as u64;
        w = (w << 8) | s[i + 5] as u64;
        w = (w << 8) | s[i + 6] as u64;
        (w << 8) | s[i + 7] as u64
    } else {
        0
    }
}

/// The eight-byte big-endian words at a and b (0 for a side with fewer than 8 bytes left).
#[inline(always)]
pub fn a_word_pair(s: &[u8], a: usize, b: usize) -> (u64, u64) {
    (a_word_at(s, a), a_word_at(s, b))
}

/// Common length (capped at 258) of the suffixes at p < q, known equal for k bytes, and
/// 1 if suffix p sorts below suffix q. Needs q + 266 <= s.len() to be exact.
#[inline(always)]
pub fn a_probe(s: &[u8], p: usize, q: usize, k: usize) -> (usize, usize) {
    let mut k = k;
    let mut w = a_word_pair(s, p + k, q + k);
    while w.0 == w.1 && k < 250 {
        k += 8;
        w = a_word_pair(s, p + k, q + k);
    }
    let l = if w.0 == w.1 { 258 } else { k + ((w.0 ^ w.1).leading_zeros() / 8) as usize };
    (if l > 258 { 258 } else { l }, if w.0 < w.1 { 1 } else { 0 })
}

/// Inserts `pos` (with at least 266 bytes after it) as the root of its 4-byte bucket's
/// binary tree (suffix order) and appends to `mb` every match longer than all before it,
/// as dist-1 | (len-3) << 15; a 3-byte side table offers the latest length-3 candidate.
/// Tree links are position + 1 (0 = none) in kid[2*(p%32768) + side], side 1 = larger.
/// Returns the longest length found (2 if none).
pub fn a_tree_insert(
    s: &[u8],
    head: &mut [u32; 65536],
    kid: &mut [u32; 65536],
    h3: &mut [u32; 32768],
    rct: &mut [u32; 65536],
    pos: usize,
    pre: (u64, usize, usize, usize, usize, usize),
    depth: usize,
    mb: &mut Vec<u32>,
) -> usize {
    let oldest = if pos > 32767 { pos - 32767 } else { 0 };
    let q = pre.0;
    let t = pre.1;
    let h = pre.2;
    let c3 = pre.3;
    let cr = pre.4;
    let mut cur = pre.5;
    h3[t % 32768] = (pos + 1) as u32;
    rct[h % 65536] = (pos + 1) as u32;
    head[h % 65536] = (pos + 1) as u32;
    let mut best = 2usize;
    if c3 > oldest && c3 <= pos {
        if (a_word_at(s, c3 - 1) ^ q) >> 40 == 0 {
            let x = (pos - c3) as u32;
            if mb.len() < mb.len().saturating_add(1) {
                mb.push(x | (a_slot_of(x) << 23));
            }
            best = 3;
        }
    }
    if cr != cur && cr > oldest && cr <= pos {
        let lr = a_probe(s, cr - 1, pos, 0).0;
        if lr > best {
            best = lr;
            let x = (pos - cr) as u32;
            if mb.len() < mb.len().saturating_add(1) {
                mb.push(x | (((lr - 3) as u32) << 15) | (a_slot_of(x) << 23));
            }
        }
    }
    let mut lo_at = 2 * (pos % 32768);
    let mut hi_at = lo_at + 1;
    let mut lo_len = 0usize;
    let mut hi_len = 0usize;
    let mut steps = 0usize;
    while steps < depth && cur > oldest && cur <= pos {
        let p = cur - 1;
        let r = a_probe(s, p, pos, if lo_len < hi_len { lo_len } else { hi_len });
        let l = r.0;
        if l > best {
            best = l;
            let x = (pos - p - 1) as u32;
            if mb.len() < mb.len().saturating_add(1) {
                mb.push(x | (((l - 3) as u32) << 15) | (a_slot_of(x) << 23));
            }
        }
        let pk = 2 * (p % 32768);
        if l >= A_NICE || l >= 258 {
            kid[lo_at % 65536] = kid[pk % 65536];
            kid[hi_at % 65536] = kid[(pk + 1) % 65536];
            lo_at = 65536;
            cur = 0;
        } else if r.1 == 1 {
            kid[lo_at % 65536] = cur as u32;
            lo_at = pk + 1;
            lo_len = l;
            cur = kid[lo_at % 65536] as usize;
        } else {
            kid[hi_at % 65536] = cur as u32;
            hi_at = pk;
            hi_len = l;
            cur = kid[hi_at % 65536] as usize;
        }
        steps += 1;
    }
    if lo_at < 65536 {
        kid[lo_at % 65536] = 0;
        kid[hi_at % 65536] = 0;
    }
    best
}

/// Bytes the suffixes at a < b share, capped at `lim` (b + lim <= s.len()).
pub fn a_shared(s: &[u8], a: usize, b: usize, lim: usize) -> usize {
    let mut k = 0usize;
    while k < lim && s[a + k] == s[b + k] {
        k += 1;
    }
    k
}

/// Match finder over the whole input: mp[i]..mp[i+1] indexes the records found at i, each
/// dist-1 | (len-3) << 15 | dist_code << 23, lengths increasing. Table loads for position i+1
/// are issued before position i is processed. While the longest known match covering i still
/// has `skip` bytes to run, i is not searched or inserted into the tree and gets that
/// match's remainder as its only record, flagged with bit 31; the last 266 positions only look
/// at the latest occurrence of their 3-byte hash.
pub fn a_has_room(n: usize, i: usize, room: usize) -> bool {
    n >= room && i <= n - room
}

#[inline(never)]
pub fn a_find_all(s: &[u8], mp: &mut Vec<u32>, mb: &mut Vec<u32>, depth: usize, skip: usize) {
    let n = s.len();
    let mut head = [0u32; 65536];
    let mut kid = [0u32; 65536];
    let mut h3 = [0u32; 32768];
    let mut rct = [0u32; 65536];
    let mut i = 0usize;
    let mut cl = 0usize;
    let mut cd = 1usize;
    let mut nq = a_word_at(s, 0);
    let mut nt = (((nq >> 40) as u32).wrapping_mul(0x9E3779B1) >> 17) as usize;
    let mut nh = (((nq >> 32) as u32).wrapping_mul(0x9E3779B1) >> (32 - A_HB)) as usize;
    let mut n3 = h3[nt % 32768] as usize;
    let mut nr = rct[nh % 65536] as usize;
    let mut nc = head[nh % 65536] as usize;
    d_push32(mp, 0);
    while i < n {
        if a_has_room(n, i, 266) {
            let pre = (nq, nt, nh, n3, nr, nc);
            nq = a_word_at(s, i + 1);
            nt = (((nq >> 40) as u32).wrapping_mul(0x9E3779B1) >> 17) as usize;
            nh = (((nq >> 32) as u32).wrapping_mul(0x9E3779B1) >> (32 - A_HB)) as usize;
            n3 = h3[nt % 32768] as usize;
            nr = rct[nh % 65536] as usize;
            nc = head[nh % 65536] as usize;
            if cl >= skip {
                rct[pre.2 % 65536] = (i + 1) as u32;
                h3[pre.1 % 32768] = (i + 1) as u32;
                let x = cd.wrapping_sub(1) as u32;
                if mb.len() < mb.len().saturating_add(1) {
                    mb.push(x | (((cl - 3) as u32) << 15) | (a_slot_of(x) << 23) | 0x80000000);
                }
                if nt == pre.1 {
                    n3 = i + 1;
                }
                if nh == pre.2 {
                    nr = i + 1;
                }
            } else {
                let before = mb.len();
                let best = a_tree_insert(s, &mut head, &mut kid, &mut h3, &mut rct, i, pre, depth, mb);
                if best > cl && mb.len() > before {
                    cl = best;
                    cd = ((mb[mb.len() - 1] & 32767) + 1) as usize;
                }
                if nt == pre.1 {
                    n3 = i + 1;
                }
                if nh == pre.2 {
                    nr = i + 1;
                    nc = i + 1;
                }
            }
        } else if a_has_room(n, i, 3) {
            let t = ((((s[i] as u32) << 16) | ((s[i + 1] as u32) << 8) | (s[i + 2] as u32)).wrapping_mul(0x9E3779B1) >> 17) as usize;
            let c = h3[t % 32768] as usize;
            h3[t % 32768] = (i + 1) as u32;
            if c > 0 && c <= i && i - (c - 1) <= 32767 {
                let l = a_shared(s, c - 1, i, if n - i > 258 { 258 } else { n - i });
                if l >= 3 {
                    let x = (i - c) as u32;
                    if mb.len() < mb.len().saturating_add(1) {
                        mb.push(x | (((l - 3) as u32) << 15) | (a_slot_of(x) << 23));
                    }
                }
            }
        }
        d_push32(mp, mb.len() as u32);
        if cl > 0 {
            cl -= 1;
        }
        i += 1;
    }
}

/// Cost of a symbol seen `f` times when 64*log2(total) is `g`; unseen symbols pay 4 bits extra.
pub fn a_sym_cost(f: u32, g: u32) -> u32 {
    let lf = a_lg64(f);
    let c = if f == 0 { g + 256 } else if lf >= g { 0 } else { g - lf };
    if c < 64 { 64 } else if c > 1152 { 1152 } else { c }
}

/// Per-symbol costs (1/64 bit) from counts: literals, lengths (code + extra bits,
/// indexed by length) and distances (code + extra bits, indexed by distance code).
pub fn a_set_costs(lf: &[u32; 512], df: &[u32; 32], lit: &mut [u32; 256], lc: &mut [u32; 512], dc: &mut [u32; 32]) {
    let mut tl = 0u32;
    let mut i = 0usize;
    while i < 286 {
        tl = tl.wrapping_add(lf[i]);
        i += 1;
    }
    let mut td = 0u32;
    i = 0;
    while i < 30 {
        td = td.wrapping_add(df[i]);
        i += 1;
    }
    let gl = a_lg64(tl);
    let gd = a_lg64(td);
    i = 0;
    while i < 256 {
        lit[i] = a_sym_cost(lf[i], gl);
        i += 1;
    }
    i = 3;
    while i <= 258 {
        let sl = a_len_slot(i);
        lc[i] = a_sym_cost(lf[(257 + sl) % 512], gl) + 64 * a_len_extra(sl);
        i += 1;
    }
    i = 0;
    while i < 30 {
        dc[i] = a_sym_cost(df[i], gd) + 64 * a_dist_extra(i);
        i += 1;
    }
}

/// Inserts symbol v into sym[0..m], kept in ascending order of frequency.
pub fn a_sorted_insert(sym: &mut [u32; 512], freq: &[u32; 512], m: usize, v: u32) {
    let fv = freq[(v as usize) % 512];
    let mut j = if m < 512 { m } else { 511 };
    while j > 0 && freq[(sym[j - 1] as usize) % 512] > fv {
        sym[j] = sym[j - 1];
        j -= 1;
    }
    sym[j] = v;
}

/// The lighter of the next unused leaf (a < m) and the next unused inner node (b < k):
/// returns (node, next a, next b).
pub fn a_lighter(w: &[u64; 1024], a: usize, b: usize, m: usize, k: usize) -> (usize, usize, usize) {
    if a < m && (b >= k || w[a % 1024] <= w[b % 1024]) {
        (a, a + 1, b)
    } else {
        (b, a, b + 1)
    }
}

/// Huffman code lengths for freq[0..n] into len[0..n] (0 for unused symbols), limited to 15 bits
/// by clamping and then lengthening the rarest codes until the Kraft sum fits.
pub fn a_huff_lengths(freq: &[u32; 512], n: usize, len: &mut [u32; 512]) {
    let mut sym = [0u32; 512];
    let mut m = 0usize;
    let mut i = 0usize;
    while i < n && i < 512 {
        len[i] = 0;
        if freq[i] > 0 {
            a_sorted_insert(&mut sym, freq, m, i as u32);
            m += 1;
        }
        i += 1;
    }
    if m == 1 {
        len[(sym[0] as usize) % 512] = 1;
    } else if m >= 2 {
        let mut w = [0u64; 1024];
        let mut par = [0u32; 1024];
        i = 0;
        while i < m {
            w[i % 1024] = freq[(sym[i % 512] as usize) % 512] as u64;
            i += 1;
        }
        let mut a = 0usize;
        let mut b = m;
        let mut k = m;
        while k + 1 < 2 * m && k < 1024 {
            let x = a_lighter(&w, a, b, m, k);
            let y = a_lighter(&w, x.1, x.2, m, k);
            a = y.1;
            b = y.2;
            par[x.0 % 1024] = k as u32;
            par[y.0 % 1024] = k as u32;
            w[k % 1024] = w[x.0 % 1024].wrapping_add(w[y.0 % 1024]);
            k += 1;
        }
        let mut d = [0u32; 1024];
        let mut j = k;
        while j > 1 {
            j -= 1;
            let pj = (par[(j - 1) % 1024] as usize) % 1024;
            d[(j - 1) % 1024] = d[pj].wrapping_add(1);
        }
        let mut kraft = 0u64;
        i = 0;
        while i < m {
            let l = if d[i % 1024] > 15 { 15 } else if d[i % 1024] == 0 { 1 } else { d[i % 1024] };
            len[(sym[i % 512] as usize) % 512] = l;
            kraft = kraft.wrapping_add(1u64 << (15 - l));
            i += 1;
        }
        a_kraft_fix(&sym, m, len, kraft);
    }
}

/// Lengthens codes shorter than 15 bits, rarest symbol first, while the Kraft sum exceeds 1.
pub fn a_kraft_fix(sym: &[u32; 512], m: usize, len: &mut [u32; 512], kraft0: u64) {
    let mut kraft = kraft0;
    let mut q = 0usize;
    while kraft > 32768 && q < m && q < 512 {
        let s2 = (sym[q] as usize) % 512;
        if len[s2] < 15 {
            kraft = kraft.wrapping_sub(1u64 << (14 - len[s2]));
            len[s2] += 1;
        } else {
            q += 1;
        }
    }
}

/// Costs from real Huffman code lengths of the counts (unseen symbols: 15 bits).
pub fn a_set_costs_huff(lf0: &[u32; 512], df: &[u32; 32], lit: &mut [u32; 256], lc: &mut [u32; 512], dc: &mut [u32; 32]) {
    let mut lf = [0u32; 512];
    let mut z = 0usize;
    while z < 286 {
        lf[z] = lf0[z].wrapping_add(1);
        z += 1;
    }
    let lf = &lf;
    let mut hl = [0u32; 512];
    a_huff_lengths(lf, 286, &mut hl);
    let mut dd = [0u32; 512];
    let mut i = 0usize;
    while i < 30 {
        dd[i] = df[i].wrapping_add(1);
        i += 1;
    }
    let mut hd = [0u32; 512];
    a_huff_lengths(&dd, 30, &mut hd);
    let mut tl = 0u32;
    i = 0;
    while i < 286 {
        tl = tl.wrapping_add(lf[i]);
        i += 1;
    }
    let mut td = 0u32;
    i = 0;
    while i < 30 {
        td = td.wrapping_add(df[i]);
        i += 1;
    }
    let ul = a_sym_cost(0, a_lg64(tl));
    let ud = a_sym_cost(0, a_lg64(td));
    i = 0;
    while i < 256 {
        lit[i] = if hl[i] == 0 { ul } else { hl[i] * 64 };
        i += 1;
    }
    i = 3;
    while i <= 258 {
        let sl = a_len_slot(i);
        let h = hl[(257 + sl) % 512];
        lc[i] = (if h == 0 { ul } else { h * 64 }) + 64 * a_len_extra(sl);
        i += 1;
    }
    i = 0;
    while i < 30 {
        dc[i] = (if hd[i] == 0 { ud } else { hd[i] * 64 }) + 64 * a_dist_extra(i);
        i += 1;
    }
}

/// Starting model: literal costs from the byte histogram of the first 64 KiB,
/// flat guesses for lengths and distances.
pub fn a_first_model(s: &[u8], lit: &mut [u32; 256], lc: &mut [u32; 512], dc: &mut [u32; 32]) {
    let mut lf = [0u32; 512];
    let mut df = [0u32; 32];
    let n = s.len();
    let m = if n > 65536 { 65536 } else { n };
    let mut i = 0usize;
    while i < m {
        lf[s[i] as usize] += 1;
        i += 1;
    }
    i = 0;
    while i < 29 {
        lf[257 + i] = if i < 8 { 64 } else { 16 };
        i += 1;
    }
    lf[256] = 1;
    i = 0;
    while i < 30 {
        df[i] = 32;
        i += 1;
    }
    a_set_costs(&lf, &df, lit, lc, dc);
}

/// Backward dynamic program over [p0, pe): cheapest bits from each position to pe under the
/// given costs; the choice at i goes to plan[i] as len + 512 * dist (0 = literal). Besides
/// the cached records, position i is offered the backward extension of the longest candidate
/// of position i+1 (same distance, one byte longer) when the byte before it matches and it
/// reaches further than i's own records. Candidates are compared as
/// (cost - cost[i+1] + 2^20) << 9 | length, which stays below 2^30 because literal costs are
/// capped (the pack is a search heuristic only).
pub fn a_store_choice(cost: &mut Vec<u32>, ch: &mut Vec<u32>,
    i: usize, best: u32, bd: u32, nxt: u32) {
    let value = ((best >> 9).wrapping_add(nxt)).wrapping_sub(1048576);
    if i < cost.len() { cost[i] = value; }
    let bl = best & 511;
    let tok = if bl >= 3 {
        bl.wrapping_add(512u32.wrapping_mul(bd.wrapping_add(1)))
    } else { 0 };
    if i < ch.len() { ch[i] = tok; }
}

#[inline(never)]
pub fn a_dp_pass(
    s: &[u8],
    mp: &Vec<u32>,
    mb: &Vec<u32>,
    p0: usize,
    pe: usize,
    lit: &[u32; 256],
    lc: &[u32; 512],
    dc: &[u32; 32],
    cost: &mut Vec<u32>,
    ch: &mut Vec<u32>,
) {
    let cl = cost.len();
    if pe < cl && pe < mp.len() && pe <= s.len() && pe <= ch.len() {
        let mut z = pe;
        while z < cl && z <= pe + 258 {
            cost[z] = 0;
            z += 1;
        }
        let mut i = pe;
        let mut e = mp[pe] as usize;
        let mut xl = 0usize;
        let mut xd = 0usize;
        while i > p0 {
            i -= 1;
            let j0 = mp[i] as usize;
            let nxt = cost[i + 1];
            let bias = 1048576u32.wrapping_sub(nxt);
            let mut best = (1048576u32.wrapping_add(lit[s[i] as usize])) << 9;
            let mut bd = 0u32;
            let mut prev = i + 2;
            let mut pd = 0usize;
            let mut j = j0;
            let top = if e < mb.len() { e } else { mb.len() };
            while j < top {
                let m = mb[j];
                let stop = i + ((((m >> 15) & 255) + 3) as usize);
                let base = dc[((m >> 23) % 32) as usize].wrapping_add(bias);
                let mut mbest = 4294967295u32;
                if stop < cl && m >= 0x80000000 {
                    let l = stop.wrapping_sub(i) as u32;
                    mbest = (cost[stop].wrapping_add(lc[(l % 512) as usize]).wrapping_add(base) << 9) | l;
                } else if stop < cl {
                    let mut at = prev + 1;
                    let mut l = at.wrapping_sub(i) as u32;
                    while at <= stop {
                        let c = (cost[at].wrapping_add(lc[(l % 512) as usize]).wrapping_add(base) << 9) | l;
                        mbest = if c < mbest { c } else { mbest };
                        at += 1;
                        l = l.wrapping_add(1);
                    }
                }
                if mbest < best {
                    best = mbest;
                    bd = m & 32767;
                }
                if stop > prev {
                    prev = stop;
                    pd = ((m & 32767) + 1) as usize;
                }
                j += 1;
            }
            let el = if xl + 1 > 258 { 258 } else { xl + 1 };
            if xl >= 3 && xd >= 1 && xd <= i && i + el > prev && s[i] == s[i - xd] {
                let stop = i + el;
                let x = (xd - 1) as u32;
                let base = dc[(a_slot_of(x) % 32) as usize].wrapping_add(bias);
                let mut mbest = 4294967295u32;
                if stop < cl {
                    let mut at = prev + 1;
                    let mut l = at.wrapping_sub(i) as u32;
                    while at <= stop {
                        let c = (cost[at].wrapping_add(lc[(l % 512) as usize]).wrapping_add(base) << 9) | l;
                        mbest = if c < mbest { c } else { mbest };
                        at += 1;
                        l = l.wrapping_add(1);
                    }
                }
                if mbest < best {
                    best = mbest;
                    bd = x;
                }
                xl = el;
            } else {
                xl = prev - i;
                xd = pd;
            }
            e = j0;
            a_store_choice(cost, ch, i, best, bd, nxt);
        }
    }
}

/// Follows the planned path from p0 for at most `need` tokens, stopping once it reaches
/// `lim`; counts the symbols into lf/df. Returns (end position, tokens).
pub fn a_walk(s: &[u8], ch: &Vec<u32>, p0: usize, lim: usize, need: usize, lf: &mut [u32; 512], df: &mut [u32; 32]) -> (usize, usize) {
    let mut k = 0usize;
    while k < 512 {
        lf[k] = 0;
        k += 1;
    }
    k = 0;
    while k < 32 {
        df[k] = 0;
        k += 1;
    }
    let mut i = p0;
    let mut t = 0usize;
    while i < lim && t < need && i < ch.len() {
        let c = ch[i] as usize;
        let l = c % 512;
        if l >= 3 {
            lf[(257 + a_len_slot(l)) % 512] += 1;
            df[(a_slot_of(((c / 512).wrapping_sub(1)) as u32) as usize) % 32] += 1;
            i += l;
        } else {
            lf[s[i] as usize] += 1;
            i += 1;
        }
        t += 1;
    }
    lf[256] = 1;
    (i, t)
}

/// dst = a + b, element-wise (counts).
pub fn a_add_counts(dst: &mut [u32; 512], a: &[u32; 512], b: &[u32; 512], dd: &mut [u32; 32], x: &[u32; 32], y: &[u32; 32]) {
    let mut k = 0usize;
    while k < 512 {
        dst[k] = a[k].wrapping_add(b[k]);
        k += 1;
    }
    k = 0;
    while k < 32 {
        dd[k] = x[k].wrapping_add(y[k]);
        k += 1;
    }
}

/// Statistics pass on a sample: the dynamic program runs on every A_SAMPLE-th A_SEG-byte segment
/// of [p0, pe) and the chosen paths are counted (scaled by A_SAMPLE) into lf/df.
/// Returns (sampled bytes, sampled tokens).
#[inline(never)]
pub fn a_sample_pass(
    s: &[u8],
    mp: &Vec<u32>,
    mb: &Vec<u32>,
    p0: usize,
    pe: usize,
    lit: &[u32; 256],
    lc: &[u32; 512],
    dc: &[u32; 32],
    cost: &mut Vec<u32>,
    ch: &mut Vec<u32>,
    lf: &mut [u32; 512],
    df: &mut [u32; 32],
) -> (usize, usize) {
    let mut zf = [0u32; 512];
    let mut zd = [0u32; 32];
    let mut sb = 0usize;
    let mut st = 0usize;
    let mut a = p0;
    while a + A_SEG <= pe {
        a_dp_pass(s, mp, mb, a, a + A_SEG, lit, lc, dc, cost, ch);
        let w = a_walk(s, ch, a, a + A_SEG - 256, A_SEG, lf, df);
        sb += w.0 - a;
        st += w.1;
        let mut b = 0usize;
        while b < 512 {
            zf[b] = zf[b].wrapping_add(lf[b].wrapping_mul(A_SAMPLE as u32));
            b += 1;
        }
        b = 0;
        while b < 32 {
            zd[b] = zd[b].wrapping_add(df[b].wrapping_mul(A_SAMPLE as u32));
            b += 1;
        }
        a += A_SEG * A_SAMPLE;
    }
    let mut b = 0usize;
    while b < 512 {
        lf[b] = zf[b];
        b += 1;
    }
    b = 0;
    while b < 32 {
        df[b] = zd[b];
        b += 1;
    }
    (sb, st)
}

/// Engine A with its effort knobs: tree search depth, the remaining match length from which
/// positions are not searched, the passes of the first round (`fspass` of them sampled) and of
/// every later round (`spass % 16` of them sampled). Bit 4 of `spass` (16) rotates the sampled
/// segments: sampled pass k of a round starts k % 4 segments into the region, so successive passes
/// see different segments. Writes the plan into `ch` (length n).
pub fn a_should_sample(k: usize, sampled: usize, passes: usize,
    pe: usize, p0: usize) -> bool {
    k < sampled && k.wrapping_add(1) < passes
        && pe.wrapping_sub(p0) > 4 * A_SEG * A_SAMPLE
}

#[inline(never)]
pub fn a_engine(
    input: &[u8],
    ch: &mut Vec<u32>,
    depth: usize,
    skip: usize,
    first_passes: usize,
    fspass: usize,
    passes_k: usize,
    spass: usize,
) {
    let n = input.len();
    let mut mp: Vec<u32> = Vec::with_capacity(n + 1);
    let mut mb: Vec<u32> = Vec::with_capacity(n * 3 + 16);
    a_find_all(input, &mut mp, &mut mb, depth, skip);
    let mut cost: Vec<u32> = Vec::with_capacity(n + 1);
    let mut i = 0usize;
    while i <= n {
        cost.push(0);
        i += 1;
    }
    let mut lit = [0u32; 256];
    let mut lc = [0u32; 512];
    let mut dc = [0u32; 32];
    let mut lf = [0u32; 512];
    let mut df = [0u32; 32];
    let mut bl = [0u32; 512];
    let mut bd = [0u32; 32];
    let mut sl = [0u32; 512];
    let mut sd = [0u32; 32];
    let zl = [0u32; 512];
    let zd = [0u32; 32];
    a_first_model(input, &mut lit, &mut lc, &mut dc);
    let rot = A_SEG.wrapping_mul((spass / 16) % 2);
    let spn = spass % 16;
    let mut p0 = 0usize;
    let mut used = 0usize;
    let mut bpt = 1024usize;
    while p0 < n && mp.len() == n + 1 && cost.len() == n + 1 && ch.len() == n {
        let need = BLOCK_TOKENS - used;
        let passes = if p0 == 0 { first_passes } else { passes_k };
        let sampled = if p0 == 0 { fspass } else { spn };
        let est = need * bpt / 256 + need * bpt / 2048 + A_MARGIN;
        let mut pe = if n - p0 > est { p0 + est } else { n };
        let mut k = 0usize;
        let mut p1 = p0 + 1;
        let mut t = 1usize;
        while k < passes {
            if a_should_sample(k, sampled, passes, pe, p0) {
                let off = (k % 4).wrapping_mul(rot);
                let ps = p0 + off % (pe - p0 + 1);
                let r = a_sample_pass(input, &mp, &mb, ps, pe, &lit, &lc, &dc, &mut cost, ch, &mut lf, &mut df);
                if r.1 > 0 {
                    let span = r.0.wrapping_mul(need) / r.1;
                    let grow = span.saturating_add(span / A_SLACK).saturating_add(A_MARGIN);
                    pe = if n - p0 > grow { p0 + grow } else { n };
                }
            } else {
                let lim = if pe == n { n } else { pe - A_MARGIN };
                a_dp_pass(input, &mp, &mb, p0, pe, &lit, &lc, &dc, &mut cost, ch);
                let r = a_walk(input, ch, p0, lim, need, &mut lf, &mut df);
                p1 = r.0;
                t = r.1;
                if t > 0 && p1 > p0 {
                    let span = (p1 - p0).wrapping_mul(need) / t;
                    let grow = span.saturating_add(span / 16).saturating_add(A_MARGIN);
                    pe = if n - p0 > grow { p0 + grow } else { n };
                }
            }
            a_add_counts(&mut sl, &bl, &lf, &mut sd, &bd, &df);
            if k + 1 < passes && k >= sampled {
                a_set_costs_huff(&sl, &sd, &mut lit, &mut lc, &mut dc);
            } else {
                a_set_costs(&sl, &sd, &mut lit, &mut lc, &mut dc);
            }
            k += 1;
        }
        used += t;
        if used >= BLOCK_TOKENS {
            used = 0;
            a_add_counts(&mut bl, &zl, &zl, &mut bd, &zd, &zd);
        } else {
            a_add_counts(&mut bl, &sl, &zl, &mut bd, &sd, &zd);
        }
        if t > 0 && p1 > p0 {
            if t >= 4096 {
                bpt = (p1 - p0) * 256 / t;
                if bpt < 256 {
                    bpt = 256;
                }
            }
            p0 = p1;
        } else {
            p0 = n;
        }
    }
}

// ───────────────────────────── engine C: DNA and binary ─────────────────────────────
// Optimal parsing under per-block Huffman-length models, iterated; finders per sub-class:
// DNA (2-bit 8-mer chains + lower-case tree), binary tree on 3-byte hashes, 4-byte-key chains
// (floats, sparse); a block planner turns blocks that code cheaper as literals into literals.

pub const C_LSYM: [u8; 256] = [
    0, 1, 2, 3, 4, 5, 6, 7, 8, 8, 9, 9, 10, 10, 11, 11, 12, 12, 12, 12, 13, 13, 13, 13, 14, 14, 14, 14, 15, 15, 15, 15,
    16, 16, 16, 16, 16, 16, 16, 16, 17, 17, 17, 17, 17, 17, 17, 17, 18, 18, 18, 18, 18, 18, 18, 18, 19, 19, 19, 19, 19, 19, 19, 19,
    20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21,
    22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23,
    24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24,
    25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25,
    26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26,
    27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 28,
];
pub const C_DSYM_LO: [u8; 256] = [
    0, 1, 2, 3, 4, 4, 5, 5, 6, 6, 6, 6, 7, 7, 7, 7, 8, 8, 8, 8, 8, 8, 8, 8, 9, 9, 9, 9, 9, 9, 9, 9,
    10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11,
    12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12,
    13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13,
    14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14,
    14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14,
    15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15,
    15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15,
];
pub const C_DSYM_HI: [u8; 256] = [
    0, 14, 16, 17, 18, 18, 19, 19, 20, 20, 20, 20, 21, 21, 21, 21, 22, 22, 22, 22, 22, 22, 22, 22, 23, 23, 23, 23, 23, 23, 23, 23,
    24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25,
    26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26,
    27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27,
    28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28,
    28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28,
    29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29,
    29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29,
];

/// Window: a slot index is `pos % C_WS`; a node is live while `p - node < C_WS`.
pub const C_WS: usize = 32768;
/// Interleaved child links: node `i` has `kids[2*(i % C_WS)]` (smaller) and `kids[2*(i % C_WS)+1]` (larger).
pub const C_KS: usize = 65536;
/// Hash table size of the match finders.
pub const C_HS: usize = 65536;
/// Tokens per encoder block (fixed by the validator's encoder).
pub const C_BLOCK: usize = 16384;
/// Cost units per bit.
pub const C_SCALE: u32 = 16;
/// Stride of one block model: 256 literal costs, 256 length costs (len-3), 32 distance costs.
pub const C_MS: usize = 544;
/// Weights DP only when 4-byte repeats reach this rate (per 65536 sampled positions).
pub const C_WREP4_MIN: usize = 200;
pub const C_DEPTH4_W: usize = 4;
pub const C_TAX_W: u32 = 16;
pub const C_UNUSED_LEN_W: u32 = 6;
pub const C_UNUSED_DIST_W: u32 = 4;
/// Chain budget of the 4-byte-key finder.
pub const C_DEPTH4: usize = 8;
/// Use the 4-byte-key chain finder when 4-byte repeats outnumber 6-byte repeats by this factor.
pub const C_CHAIN4_RATIO: usize = 8;
/// Early exit of `c_rep_rates` only after this many probes (a short repetitive prefix must not decide the mode).
pub const C_REP_MINPROBE: usize = 16384;
/// Chain budget of the DNA 8-mer index.
pub const C_DEPTH_UP: usize = 16;
/// Shortest match reported by the DNA 8-mer index.
pub const C_UP_MIN: usize = 9;
/// Stop searching once a match this long is found.
pub const C_NICE: usize = 258;
/// Skip searching inside byte runs at least this long, and (generic finder) inside other matches
/// at least `C_SKIP_FAR` long.
pub const C_SKIP: usize = 64;
pub const C_SKIP_FAR: usize = 128;
/// Lengths relaxed one by one; longer candidates only try their full length beyond this.
pub const C_RCAP: usize = 32;
/// Candidates kept per position (the longest ones).
pub const C_KEEP: usize = 4;
/// Generic input: seed the first pass with a greedy parse taking matches of at least this length.
pub const C_GMIN: usize = 3;
/// DNA: after at least min_dna passes, stop once a pass improves the estimate by less than 1/STOP_DIV.
pub const C_STOP_DIV: u64 = 4096;
/// Passes for very repetitive input (most positions start a 6-byte repeat).
pub const C_PASSES_SP: usize = 1;
/// Extra cost (in 1/C_SCALE bits) charged to every match by the chain4 class, standing in for the
/// code space a match symbol takes from the literals.
pub const C_TAX_C4: u32 = 16;
/// Match tax of the binary-tree class.
pub const C_TAX_BT: u32 = 24;
/// Inputs whose 6-byte repeat rate is below this (per 65536 positions) are coded as literals only.
pub const C_REP6_MIN: usize = 24;
/// Sampling step of the repeat-rate detector.
pub const C_REP_STEP: usize = 2;
/// Order in which code-length code lengths are written (RFC 1951).
pub const C_CL_ORDER: [usize; 19] = [16, 17, 18, 0, 8, 7, 9, 6, 10, 5, 11, 4, 12, 3, 13, 2, 14, 1, 15];
/// Candidate flag: only lengths of 8 or more are worth trying (DNA 8-mer chains).
pub const C_LONG_ONLY: u32 = 1 << 29;
/// A candidate group ends with a trailer `C_GROUP | count << 27 | position`.
pub const C_GROUP: u32 = 1 << 31;
/// Position bits of a trailer.
pub const C_PMASK: u32 = 0x07FF_FFFF;
/// Extra cost (in 1/C_SCALE bits) charged per token, to break ties toward fewer tokens.
pub const C_TOKPEN: u32 = 1;
pub const C_TOKPEN_W: u32 = 1;
pub const C_TOKPEN_C4: u32 = 0;
pub const C_TOKPEN_BT: u32 = 1;
/// Bits charged for symbols a block model has never seen.
pub const C_UNUSED_LIT: u32 = 12;
pub const C_UNUSED_LEN: u32 = 12;
pub const C_UNUSED_DIST: u32 = 5;

/// Nucleotide codes: A C G T -> 0..3, anything else 4.
pub const C_NT: [u8; 256] = [
    4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
    4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
    4, 0, 4, 1, 4, 4, 4, 2, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 3, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
    4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
    4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
    4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
    4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
    4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
];

pub const C_LEXTRA: [u32; 29] = [0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 2, 2, 2, 2, 3, 3, 3, 3, 4, 4, 4, 4, 5, 5, 5, 5, 0];
pub const C_DEXTRA: [u32; 30] = [0, 0, 0, 0, 1, 1, 2, 2, 3, 3, 4, 4, 5, 5, 6, 6, 7, 7, 8, 8, 9, 9, 10, 10, 11, 11, 12, 12, 13, 13];

/// Length symbol (0..28) of a match length 3..=258.
pub fn c_lsym(len: usize) -> usize {
    if len < 3 {
        return 0;
    }
    C_LSYM[(len - 3) % 256] as usize
}

/// Distance symbol (0..29) of a distance 1..=32768.
pub fn c_dsym(d: usize) -> usize {
    if d < 1 {
        return 0;
    }
    if d <= 256 {
        return C_DSYM_LO[(d - 1) % 256] as usize;
    }
    C_DSYM_HI[((d - 1) >> 7) % 256] as usize
}

/// Eight bytes at `i` as a big-endian word (0 if they do not fit).
pub fn c_word_be(s: &[u8], i: usize) -> u64 {
    if i + 8 > s.len() {
        return 0;
    }
    ((s[i] as u64) << 56)
        | ((s[i + 1] as u64) << 48)
        | ((s[i + 2] as u64) << 40)
        | ((s[i + 3] as u64) << 32)
        | ((s[i + 4] as u64) << 24)
        | ((s[i + 5] as u64) << 16)
        | ((s[i + 6] as u64) << 8)
        | (s[i + 7] as u64)
}

/// Common prefix of the strings at `a < b`, starting from the known `k0`, capped at `lim`.
/// Requires `b + lim <= s.len()`.
pub fn c_extend(s: &[u8], a: usize, b: usize, k0: usize, lim: usize) -> usize {
    let mut k = k0;
    let mut fuel = lim + 1;
    while fuel > 0 && k + 8 <= lim {
        let x = c_word_be(s, a + k) ^ c_word_be(s, b + k);
        if x != 0 {
            return k + (x.leading_zeros() / 8) as usize;
        }
        k += 8;
        fuel -= 1;
    }
    while k < lim && s[a + k] == s[b + k] {
        k += 1;
    }
    k
}

/// Pack a candidate: length (9 bits), distance-1 (15 bits), distance symbol (5 bits).
pub fn c_pack(len: usize, d: usize) -> u32 {
    ((c_dsym(d) as u32) << 24) | (((d - 1) as u32) << 9) | (len as u32)
}

/// Store `v` into the pending child slot `(which, idx)`: `which == 0` is `lt`, else `gt`.
pub fn c_put_kid(kids: &mut [u32; C_KS], which: usize, idx: usize, v: u32) {
    kids[(2 * (idx % C_WS) + which) % C_KS] = v;
}

/// Insert `p` into the binary tree rooted at `head[h]` and collect the improving matches
/// (strictly longer as the distance grows) into `ml`/`md`. Returns how many.
/// Positions are stored as `pos + 1` (0 = empty). Requires `p + 3 <= s.len()`.
pub fn c_bt_find(
    s: &[u8],
    p: usize,
    h: usize,
    depth: usize,
    head: &mut [u32; C_HS],
    kids: &mut [u32; C_KS],
    ml: &mut [u32; 64],
    md: &mut [u32; 64],
) -> usize {
    let n = s.len();
    let room = n - p;
    let maxlen = if room < 258 { room } else { 258 };
    let lim = if C_NICE < maxlen { C_NICE } else { maxlen };
    let mut cur = head[h % C_HS] as usize;
    head[h % C_HS] = (p + 1) as u32;
    let mut lw = 0usize;
    let mut li = p % C_WS;
    let mut gw = 1usize;
    let mut gi = p % C_WS;
    let mut llen = 0usize;
    let mut glen = 0usize;
    let mut best = 2usize;
    let mut cnt = 0usize;
    let mut steps = 0usize;
    while steps < depth && cur > 0 {
        let c = cur - 1;
        if c >= p || p - c >= C_WS {
            steps = depth;
        } else {
            let k0 = if llen < glen { llen } else { glen };
            let k = c_extend(s, c, p, k0, lim);
            if k > best {
                best = k;
                if cnt < 64 {
                    ml[cnt] = k as u32;
                    md[cnt] = (p - c) as u32;
                    cnt += 1;
                }
            }
            if k >= lim {
                c_put_kid(kids, lw, li, kids[(2 * (c % C_WS)) % C_KS]);
                c_put_kid(kids, gw, gi, kids[(2 * (c % C_WS) + 1) % C_KS]);
                return cnt;
            }
            if s[c + k] < s[p + k] {
                c_put_kid(kids, lw, li, cur as u32);
                lw = 1;
                li = c % C_WS;
                llen = k;
                cur = kids[(2 * (c % C_WS) + 1) % C_KS] as usize;
            } else {
                c_put_kid(kids, gw, gi, cur as u32);
                gw = 0;
                gi = c % C_WS;
                glen = k;
                cur = kids[(2 * (c % C_WS)) % C_KS] as usize;
            }
            steps += 1;
        }
    }
    c_put_kid(kids, lw, li, 0);
    c_put_kid(kids, gw, gi, 0);
    cnt
}

/// Walk the hash chain of `key` from its head, collecting the improving matches (strictly longer
/// than `best0`, growing with the distance) into `ml`/`md`, then link `p` in at the head. `k0`
/// bytes are known to agree for every chain member (8 for exact DNA keys, else 0).
pub fn c_chain_walk(
    s: &[u8],
    p: usize,
    key: usize,
    k0: usize,
    best0: usize,
    depth: usize,
    head: &mut [u32; C_HS],
    prev: &mut [u32; C_WS],
    ml: &mut [u32; 64],
    md: &mut [u32; 64],
) -> usize {
    let n = s.len();
    let room = n - p;
    let lim = if room < 258 { room } else { 258 };
    let first = head[key % C_HS];
    head[key % C_HS] = (p + 1) as u32;
    let mut cur = first as usize;
    let mut best = best0;
    let mut cnt = 0usize;
    let mut steps = 0usize;
    while steps < depth && cur > 0 {
        let c = cur - 1;
        if c >= p || p - c >= C_WS {
            steps = depth;
        } else {
            if best < lim && s[c + best] == s[p + best] {
                let mut k = k0;
                if k0 + 8 <= lim {
                    let x = c_word_be(s, c + k0) ^ c_word_be(s, p + k0);
                    if x != 0 {
                        k = k0 + (x.leading_zeros() / 8) as usize;
                    } else {
                        k = c_extend(s, c, p, k0 + 8, lim);
                    }
                } else {
                    k = c_extend(s, c, p, k0, lim);
                }
                if k > best {
                    best = k;
                    if cnt < 64 {
                        ml[cnt] = k as u32;
                        md[cnt] = (p - c) as u32;
                        cnt += 1;
                    }
                }
            }
            if best >= lim {
                steps = depth;
            } else {
                cur = prev[c % C_WS] as usize;
                steps += 1;
            }
        }
    }
    prev[p % C_WS] = first;
    cnt
}

/// 2-bit code of a nucleotide letter (upper case), 4 otherwise.
pub fn c_nt_code(b: u8) -> usize {
    C_NT[b as usize] as usize
}

/// Push the candidate group of position `p`: a distance-1 run candidate (if `r1 >= 3`) then the
/// last `C_KEEP` found candidates longer than it, tagged with `flag`, then a trailer. Nothing is
/// pushed when there is no candidate. Returns the longest length pushed (0 if none).
pub fn c_push_cands(clist: &mut Vec<u32>, p: usize, ml: &[u32; 64], md: &[u32; 64], cnt: usize, r1: usize, flag: u32) -> usize {
    let first = if cnt > C_KEEP { cnt - C_KEEP } else { 0 };
    let mut top = 0usize;
    let mut pushed = 0u32;
    if r1 >= 3 && r1 <= 258 {
        clist.push(c_pack(r1, 1) | flag);
        top = r1;
        pushed += 1;
    }
    let mut i = first;
    while i < cnt && i < 64 {
        let d = md[i] as usize;
        let l = ml[i] as usize;
        if d >= 1 && d <= C_WS && l > top && l <= 258 && l >= 3 {
            clist.push(c_pack(l, d) | flag);
            top = l;
            pushed += 1;
        }
        i += 1;
    }
    if pushed > 0 {
        clist.push(C_GROUP | (pushed << 27) | ((p as u32) & C_PMASK));
    }
    top
}

/// Length of the distance-1 match at `p` (a byte run), 0 if shorter than 3.
pub fn c_run_len(s: &[u8], p: usize) -> usize {
    let n = s.len();
    if p < 1 || p + 3 > n {
        return 0;
    }
    if s[p] != s[p - 1] || s[p + 1] != s[p - 1] || s[p + 2] != s[p - 1] {
        return 0;
    }
    let room = n - p;
    let lim = if room < 258 { room } else { 258 };
    c_extend(s, p - 1, p, 3, lim)
}

/// Candidates for every position of binary input: a binary tree on 3-byte hashes (`chain == 0`)
/// or hash chains on 4-byte keys, plus byte runs. Searching pauses inside byte runs of `C_SKIP`+
/// bytes and (after one more position) inside other matches of `C_SKIP_FAR`+ bytes.
pub fn c_find_bin(s: &[u8], clist: &mut Vec<u32>, chain: usize, depth: usize) {
    let n = s.len();
    let mut head = [0u32; C_HS];
    let mut lt = [0u32; C_WS];
    let mut kids = [0u32; C_KS];
    let mut ml = [0u32; 64];
    let mut md = [0u32; 64];
    let mut p = 0usize;
    let mut skip_to = 0usize;
    let mut pend = 0usize;
    while p + 4 <= n {
        let v = ((s[p] as u32) << 24) | ((s[p + 1] as u32) << 16) | ((s[p + 2] as u32) << 8) | (s[p + 3] as u32);
        let key = if chain > 0 { v } else { v >> 8 };
        let h = (key.wrapping_mul(0x9E37_79B1) >> 16) as usize;
        if p >= skip_to {
            let cnt = if chain > 0 {
                c_chain_walk(s, p, h, 0, 3, depth, &mut head, &mut lt, &mut ml, &mut md)
            } else {
                c_bt_find(s, p, h, depth, &mut head, &mut kids, &mut ml, &mut md)
            };
            let r1 = if p > 0 && s[p] == s[p - 1] { c_run_len(s, p) } else { 0 };
            let mut top = 0usize;
            if cnt > 0 || r1 >= 3 {
                top = c_push_cands(clist, p, &ml, &md, cnt, r1, 0);
            }
            if r1 >= C_SKIP {
                skip_to = p + top;
                pend = 0;
            } else if top >= C_SKIP_FAR {
                if pend > 0 {
                    skip_to = p + top;
                    pend = 0;
                } else {
                    pend = 1;
                }
            } else {
                pend = 0;
            }
        } else if chain > 0 {
            lt[p % C_WS] = head[h % C_HS];
            head[h % C_HS] = (p + 1) as u32;
        }
        p += 1;
    }
}

/// Candidates for every position (DNA): exact 8-mer chains for upper-case runs,
/// a binary tree over lower-case positions only.
pub fn c_find_dna(s: &[u8], clist: &mut Vec<u32>, depth_lo: usize) {
    let n = s.len();
    let mut head8 = [0u32; C_HS];
    let mut prev8 = [0u32; C_WS];
    let mut head3 = [0u32; C_HS];
    let mut kids = [0u32; C_KS];
    let mut ml = [0u32; 64];
    let mut md = [0u32; 64];
    // rolling 2-bit key of s[p..p+8]; `run` counts trailing nucleotides, `run2` also admits newlines
    let mut key = 0usize;
    let mut run = 0usize;
    let mut run2 = 0usize;
    let mut q = 0usize;
    while q < 7 && q < n {
        let c = c_nt_code(s[q]);
        if c < 4 {
            key = ((key << 2) | c) & 65535;
            run += 1;
            run2 += 1;
        } else {
            run = 0;
            run2 = if s[q] == 10 { run2 + 1 } else { 0 };
        }
        q += 1;
    }
    let mut p = 0usize;
    let mut skip_to = 0usize;
    while p < n {
        if p + 7 < n {
            let c = c_nt_code(s[p + 7]);
            if c < 4 {
                key = ((key << 2) | c) & 65535;
                run += 1;
                run2 += 1;
            } else {
                run = 0;
                run2 = if s[p + 7] == 10 { run2 + 1 } else { 0 };
            }
        } else {
            run = 0;
            run2 = 0;
        }
        if p + 3 <= n {
            let b = s[p];
            if b >= 97 && b <= 122 {
                let v = ((b as u32) << 16) | ((s[p + 1] as u32) << 8) | (s[p + 2] as u32);
                let h = ((v.wrapping_mul(0x9E37_79B1) >> 16) as usize) % (C_HS / 2);
                if p >= skip_to {
                    let cnt = c_bt_find(s, p, h, depth_lo, &mut head3, &mut kids, &mut ml, &mut md);
                    if cnt > 0 {
                        let top = c_push_cands(clist, p, &ml, &md, cnt, 0, 0);
                        if top >= C_SKIP {
                            skip_to = p + top;
                        }
                    }
                }
            } else if run >= 8 {
                if p >= skip_to {
                    let cnt = c_chain_walk(s, p, key, 8, C_UP_MIN - 1, C_DEPTH_UP, &mut head8, &mut prev8, &mut ml, &mut md);
                    if cnt > 0 {
                        let top = c_push_cands(clist, p, &ml, &md, cnt, 0, C_LONG_ONLY);
                        if top >= C_SKIP {
                            skip_to = p + top;
                        }
                    }
                } else {
                    prev8[p % C_WS] = head8[key % C_HS];
                    head8[key % C_HS] = (p + 1) as u32;
                }
            } else if run2 >= 8 {
                let w = c_word_be(s, p);
                let hn = C_HS / 2 + ((w.wrapping_mul(0x9E37_79B9_7F4A_7C15) >> 40) as usize) % (C_HS / 2);
                if p >= skip_to {
                    let cnt = c_chain_walk(s, p, hn, 0, C_UP_MIN - 1, C_DEPTH_UP, &mut head3, &mut prev8, &mut ml, &mut md);
                    if cnt > 0 {
                        let top = c_push_cands(clist, p, &ml, &md, cnt, 0, C_LONG_ONLY);
                        if top >= C_SKIP {
                            skip_to = p + top;
                        }
                    }
                } else {
                    prev8[p % C_WS] = head3[hn % C_HS];
                    head3[hn % C_HS] = (p + 1) as u32;
                }
            }
        }
        p += 1;
    }
}

/// Huffman code lengths (capped at 15) for the first `m` symbols of `freq`:
/// radix-sort the used symbols by weight, then merge with the two-queue method.
pub fn c_huff_lengths(freq: &[u32; 288], m: usize, lens: &mut [u8; 288]) {
    let mut aw = [0u32; 288];
    let mut asy = [0u16; 288];
    let mut k = 0usize;
    let mut i = 0usize;
    while i < 288 {
        lens[i] = 0;
        if i < m && freq[i] > 0 {
            aw[k % 288] = if freq[i] < 65535 { freq[i] } else { 65535 };
            asy[k % 288] = i as u16;
            k += 1;
        }
        i += 1;
    }
    if k == 0 {
        return;
    }
    if k == 1 {
        lens[asy[0] as usize % 288] = 1;
        return;
    }
    let mut bw = [0u32; 288];
    let mut bsy = [0u16; 288];
    c_radix_pass(&aw, &asy, &mut bw, &mut bsy, k, 0);
    c_radix_pass(&bw, &bsy, &mut aw, &mut asy, k, 8);
    let mut iw = [0u32; 288];
    let mut ipar = [0u16; 288];
    let mut lpar = [0u16; 288];
    let mut li = 0usize;
    let mut ii = 0usize;
    let mut ni = 0usize;
    while ni + 1 < k && ni < 287 {
        let mut w2 = 0u32;
        let mut t = 0usize;
        while t < 2 {
            let take_leaf = li < k && (ii >= ni || aw[li % 288] <= iw[ii % 288]);
            if take_leaf {
                w2 = w2.saturating_add(aw[li % 288]);
                lpar[li % 288] = ni as u16;
                li += 1;
            } else {
                w2 = w2.saturating_add(iw[ii % 288]);
                ipar[ii % 288] = ni as u16;
                ii += 1;
            }
            t += 1;
        }
        iw[ni % 288] = w2;
        ni += 1;
    }
    let mut idep = [0u8; 288];
    let mut j = ni - 1;
    while j > 0 {
        j -= 1;
        let d = idep[ipar[j % 288] as usize % 288];
        idep[j % 288] = if d < 15 { d + 1 } else { 15 };
    }
    let mut x = 0usize;
    while x < k {
        let d = idep[lpar[x % 288] as usize % 288];
        lens[asy[x % 288] as usize % 288] = if d < 15 { d + 1 } else { 15 };
        x += 1;
    }
}

/// One stable counting-sort pass over `k` (weight, symbol) pairs by the byte at `shift`.
pub fn c_radix_pass(sw: &[u32; 288], ss: &[u16; 288], dw: &mut [u32; 288], ds: &mut [u16; 288], k: usize, shift: u32) {
    let mut cnt = [0usize; 257];
    let mut i = 0usize;
    while i < k && i < 288 {
        let b = ((sw[i] >> shift) & 255) as usize;
        cnt[(b + 1) % 257] = cnt[(b + 1) % 257].wrapping_add(1);
        i += 1;
    }
    let mut c = 1usize;
    while c < 257 {
        cnt[c] = cnt[c].wrapping_add(cnt[c - 1]);
        c += 1;
    }
    let mut j = 0usize;
    while j < k && j < 288 {
        let b = ((sw[j] >> shift) & 255) as usize;
        let at = cnt[b % 257];
        dw[at % 288] = sw[j];
        ds[at % 288] = ss[j];
        cnt[b % 257] = at.wrapping_add(1);
        j += 1;
    }
}

/// Append one block model (costs in `C_SCALE` units) built from symbol frequencies;
/// return the block's estimated size in bits (codes, extra bits, rough header).
pub fn c_push_model(models: &mut Vec<u32>, lf: &[u32; 288], df: &[u32; 288], tax: u32, ulen: u32, udist: u32, tokpen: u32) -> u64 {
    let mut ll = [0u8; 288];
    let mut dl = [0u8; 288];
    c_huff_lengths(lf, 286, &mut ll);
    c_huff_lengths(df, 30, &mut dl);
    let mut est: u64 = 70;
    let mut q = 0usize;
    while q < 288 {
        if ll[q] > 0 {
            est += (lf[q] as u64) * (ll[q] as u64) + 4;
            if q >= 257 && q < 286 {
                est += (lf[q] as u64) * (C_LEXTRA[(q - 257) % 29] as u64);
            }
        }
        if q < 30 && dl[q] > 0 {
            est += (df[q] as u64) * ((dl[q] as u64) + (C_DEXTRA[q] as u64)) + 4;
        }
        q += 1;
    }
    let mut i = 0usize;
    while i < 256 {
        let b = if ll[i] > 0 { ll[i] as u32 } else { C_UNUSED_LIT };
        models.push(b * C_SCALE + tokpen);
        i += 1;
    }
    let mut l = 3usize;
    while l < 259 {
        let s = c_lsym(l);
        let b = if ll[(257 + s) % 288] > 0 { ll[(257 + s) % 288] as u32 } else { ulen };
        models.push((b + C_LEXTRA[s % 29]) * C_SCALE + tokpen + tax);
        l += 1;
    }
    let mut d = 0usize;
    while d < 32 {
        let b = if d < 30 && dl[d] > 0 { dl[d] as u32 } else { udist };
        let e = if d < 30 { C_DEXTRA[d] } else { 0 };
        models.push((b + e) * C_SCALE);
        d += 1;
    }
    est
}

/// Start index of the candidates of the group whose trailer is at `ge - 1` (or `ge` if none).
pub fn c_group_start(clist: &Vec<u32>, ge: usize) -> usize {
    if ge == 0 || ge > clist.len() {
        return ge;
    }
    let tr = clist[ge - 1];
    let cnt = ((tr >> 27) & 15) as usize;
    if (tr & C_GROUP) == 0 || cnt + 1 > ge {
        return ge;
    }
    ge - 1 - cnt
}

/// Copy block model `b` into local cost tables (literals, lengths 3..258, distance symbols).
pub fn c_load_model(models: &Vec<u32>, b: usize, lit_c: &mut [u32; 256], len_c: &mut [u32; 256], dst_c: &mut [u32; 32]) {
    let base = b * C_MS;
    if base + C_MS > models.len() {
        return;
    }
    let mut i = 0usize;
    while i < 256 {
        lit_c[i] = models[base + i];
        len_c[i] = models[base + 256 + i];
        i += 1;
    }
    let mut d = 0usize;
    while d < 32 {
        dst_c[d] = models[base + 512 + d];
        d += 1;
    }
}

/// Backward optimal parse over the whole input under per-block models. Costs live in a ring
/// (a match is at most 258 long); the choice per position (0 = literal, else `len + 512 * dist`)
/// is written into `choice`. Runs of positions without candidates take a literal-only fast path.
pub fn c_dp_pass(s: &[u8], clist: &Vec<u32>, models: &Vec<u32>, bstart: &Vec<u32>, choice: &mut [u32]) {
    let n = s.len();
    let nb = bstart.len();
    if nb == 0 || models.len() < nb * C_MS || choice.len() < n {
        return;
    }
    let mut ring = [0u32; 512];
    let mut lit_c = [0u32; 256];
    let mut len_c = [0u32; 256];
    let mut dst_c = [0u32; 32];
    let mut b = nb - 1;
    let mut loaded = nb;
    let mut ge = clist.len();
    let mut gs = c_group_start(clist, ge);
    let mut gp = if gs < ge && ge <= clist.len() { (clist[ge - 1] & C_PMASK) as usize } else { n };
    let mut next = 0u32;
    let mut p = n;
    let mut fuel = 2 * n + nb + 2;
    while p > 0 && fuel > 0 {
        fuel -= 1;
        let q = p - 1;
        while b > 0 && bstart[b] as usize > q {
            b -= 1;
        }
        if loaded != b {
            c_load_model(models, b, &mut lit_c, &mut len_c, &mut dst_c);
            loaded = b;
        }
        let bs = bstart[b] as usize;
        let lo = if gp < p && gp >= bs { gp + 1 } else { bs };
        while p > lo {
            p -= 1;
            let c = next.wrapping_add(lit_c[s[p] as usize]);
            ring[p % 512] = c;
            choice[p] = 0;
            next = c;
        }
        if p > 0 && gp + 1 == p && gp >= bs {
            p -= 1;
            let lit = next.wrapping_add(lit_c[s[p] as usize]);
            let mut best = 0xFFFF_FFFFu32;
            let mut ch = 0u32;
            let mut prev = 2usize;
            let room = n - p;
            let mut k = gs;
            while k + 1 < ge && k < clist.len() {
                let e = clist[k];
                if (e & C_LONG_ONLY) != 0 && prev < 7 {
                    prev = 7;
                }
                let mut l = (e & 511) as usize;
                if l > room {
                    l = room;
                }
                if l > prev {
                    let dc = dst_c[((e >> 24) as usize) % 32];
                    let tag = (e & 0x00FF_FE00) + 512;
                    let mut len = prev + 1;
                    while len <= l {
                        let c = ring[(p + len) % 512].wrapping_add(len_c[(len - 3) % 256]).wrapping_add(dc);
                        if c <= best {
                            best = c;
                            ch = tag | (len as u32);
                        }
                        if len == C_RCAP && l > C_RCAP {
                            len = l;
                        } else {
                            len += 1;
                        }
                    }
                    prev = l;
                }
                k += 1;
            }
            if lit <= best {
                best = lit;
                ch = 0;
            }
            ring[p % 512] = best;
            choice[p] = ch;
            next = best;
            ge = gs;
            gs = c_group_start(clist, ge);
            gp = if gs < ge && ge <= clist.len() { (clist[ge - 1] & C_PMASK) as usize } else { n };
        }
    }
}

/// Seed `choice` with a greedy parse: the longest candidate at each position if at least `gmin` long.
pub fn c_greedy_choice(clist: &Vec<u32>, choice: &mut [u32], n: usize, gmin: usize) {
    let mut p = 0usize;
    while p < n && p < choice.len() {
        choice[p] = 0;
        p += 1;
    }
    let m = clist.len();
    let mut k = 1usize;
    while k < m {
        let tr = clist[k];
        if (tr & C_GROUP) != 0 {
            let q = (tr & C_PMASK) as usize;
            let last = clist[k - 1];
            if (last & C_GROUP) == 0 && ((last & 511) as usize) >= gmin && q < n && q < choice.len() {
                choice[q] = (last & 0x00FF_FFFF) + 512;
            }
        }
        k += 1;
    }
}

/// Walk the chosen path; rebuild per-block models and block start positions from it.
/// Returns the estimated size of the path in bits.
pub fn c_restat(s: &[u8], choice: &[u32], models: &mut Vec<u32>, bstart: &mut Vec<u32>, tax: u32, ulen: u32, udist: u32, tokpen: u32) -> u64 {
    let mut total: u64 = 0;
    let n = if s.len() < choice.len() { s.len() } else { choice.len() };
    *models = Vec::new();
    *bstart = Vec::new();
    let mut lf = [0u32; 288];
    let mut df = [0u32; 288];
    let mut p = 0usize;
    bstart.push(0);
    while p < n {
        let mut t = 0usize;
        while t < C_BLOCK && p < n {
            let ch = choice[p] as usize;
            let len = ch % 512;
            if len < 3 {
                let b = s[p] as usize;
                lf[b] = lf[b].wrapping_add(1);
                p += 1;
            } else {
                let d = ch / 512;
                let ls = (257 + c_lsym(len)) % 288;
                let ds = c_dsym(d) % 288;
                lf[ls] = lf[ls].wrapping_add(1);
                df[ds] = df[ds].wrapping_add(1);
                p += len;
            }
            t += 1;
        }
        lf[256] = 1;
        total += c_push_model(models, &lf, &df, tax, ulen, udist, tokpen);
        if p < n {
            bstart.push(p as u32);
        }
        lf = [0u32; 288];
        df = [0u32; 288];
    }
    if models.len() == 0 {
        lf[256] = 1;
        total += c_push_model(models, &lf, &df, tax, ulen, udist, tokpen);
    }
    total
}

/// DNA-like input: nearly all bytes are nucleotide letters or newlines (stops early otherwise).
pub fn c_is_dna(s: &[u8]) -> usize {
    let n = s.len();
    if n < 1024 {
        return 0;
    }
    let allow = n / 20;
    let mut bad = 0usize;
    let mut i = 0usize;
    while i < n {
        let c = s[i] | 32;
        if !(c == 97 || c == 99 || c == 103 || c == 116 || c == 110 || s[i] == 10) {
            bad += 1;
            if bad > allow {
                return 0;
            }
        }
        i += 1;
    }
    1
}

/// Code-length RLE of one run of `r` equal lengths `v` (the encoder's greedy rules):
/// adds symbol counts to `clf` and returns the extra bits.
pub fn c_rle_run(clf: &mut [u32; 288], v: usize, r0: usize) -> u64 {
    let mut r = r0;
    let mut extra: u64 = 0;
    let mut fuel = r0 + 1;
    if v == 0 {
        while r >= 3 && fuel > 0 {
            if r >= 11 {
                let take = if r < 138 { r } else { 138 };
                clf[18] = clf[18].wrapping_add(1);
                extra += 7;
                r -= take;
            } else {
                let take = if r < 10 { r } else { 10 };
                clf[17] = clf[17].wrapping_add(1);
                extra += 3;
                r -= take;
            }
            fuel -= 1;
        }
        clf[0] = clf[0].wrapping_add(r as u32);
    } else {
        clf[v % 288] = clf[v % 288].wrapping_add(1);
        r -= 1;
        while r >= 3 && fuel > 0 {
            let take = if r < 6 { r } else { 6 };
            clf[16] = clf[16].wrapping_add(1);
            extra += 2;
            r -= take;
            fuel -= 1;
        }
        clf[v % 288] = clf[v % 288].wrapping_add(r as u32);
    }
    extra
}

/// Bits of a dynamic block with these symbol frequencies (`lf[256]` is the end-of-block count),
/// header included, using approximate (depth-capped) Huffman lengths.
pub fn c_dyn_bits(lf: &[u32; 288], df: &[u32; 288]) -> u64 {
    let mut ll = [0u8; 288];
    let mut dl = [0u8; 288];
    c_huff_lengths(lf, 286, &mut ll);
    c_huff_lengths(df, 30, &mut dl);
    let mut body: u64 = 0;
    let mut hlit = 257usize;
    let mut i = 0usize;
    while i < 286 {
        if ll[i] > 0 {
            body += (lf[i] as u64) * (ll[i] as u64);
            if i >= 257 {
                body += (lf[i] as u64) * (C_LEXTRA[(i - 257) % 29] as u64);
                hlit = i + 1;
            }
        }
        i += 1;
    }
    let mut hdist = 1usize;
    let mut any = 0usize;
    let mut d = 0usize;
    while d < 30 {
        if dl[d] > 0 {
            body += (df[d] as u64) * ((dl[d] as u64) + (C_DEXTRA[d] as u64));
            hdist = d + 1;
            any = 1;
        }
        d += 1;
    }
    if any == 0 {
        dl[0] = 1;
    }
    // run-length code the concatenated length sequence
    let mut clf = [0u32; 288];
    let mut extra: u64 = 0;
    let total = hlit + hdist;
    let mut seq = [0u8; 512];
    let mut i2 = 0usize;
    while i2 < total && i2 < 512 {
        seq[i2] = if i2 < hlit { ll[i2 % 288] } else { dl[(i2 - hlit) % 288] };
        i2 += 1;
    }
    let mut j = 0usize;
    while j < total && j < 512 {
        let v = seq[j] as usize;
        let mut r = 1usize;
        while j + r < total && j + r < 512 && seq[(j + r) % 512] as usize == v {
            r += 1;
        }
        extra += c_rle_run(&mut clf, v, r);
        j += r;
    }
    let mut cl = [0u8; 288];
    c_huff_lengths(&clf, 19, &mut cl);
    let mut hclen = 19usize;
    while hclen > 4 && cl[C_CL_ORDER[(hclen - 1) % 19] % 288] == 0 {
        hclen -= 1;
    }
    let mut hdr: u64 = 17 + 3 * (hclen as u64) + extra;
    let mut c = 0usize;
    while c < 19 {
        let len = if cl[c] > 7 { 7 } else { cl[c] };
        hdr += (clf[c] as u64) * (len as u64);
        c += 1;
    }
    hdr + body
}

/// Bits of a fixed-code block with these symbol frequencies.
pub fn c_fixed_bits(lf: &[u32; 288], df: &[u32; 288]) -> u64 {
    let mut bits: u64 = 3;
    let mut i = 0usize;
    while i < 288 {
        let len: u64 = if i < 144 { 8 } else if i < 256 { 9 } else if i < 280 { 7 } else { 8 };
        bits += (lf[i] as u64) * len;
        if i >= 257 && i < 286 {
            bits += (lf[i] as u64) * (C_LEXTRA[(i - 257) % 29] as u64);
        }
        i += 1;
    }
    let mut d = 0usize;
    while d < 30 {
        bits += (df[d] as u64) * (5 + C_DEXTRA[d] as u64);
        d += 1;
    }
    bits
}

/// Frequencies of the block that follows `choice` from `p0` (at most C_BLOCK tokens).
/// Returns the position after the block.
pub fn c_path_block(s: &[u8], choice: &[u32], p0: usize, lf: &mut [u32; 288], df: &mut [u32; 288]) -> usize {
    let n = s.len();
    let mut i = 0usize;
    while i < 288 {
        lf[i] = 0;
        df[i] = 0;
        i += 1;
    }
    let mut p = p0;
    let mut t = 0usize;
    while p < n && t < C_BLOCK && p < choice.len() {
        let ch = choice[p] as usize;
        let len = ch % 512;
        let d = ch / 512;
        if len >= 3 && len <= n - p {
            lf[(257 + c_lsym(len)) % 288] = lf[(257 + c_lsym(len)) % 288].wrapping_add(1);
            df[c_dsym(d) % 288] = df[c_dsym(d) % 288].wrapping_add(1);
            p += len;
        } else {
            let sym = s[p] as usize;
            lf[sym] = lf[sym].wrapping_add(1);
            p += 1;
        }
        t += 1;
    }
    lf[256] = 1;
    p
}

/// Set plan[p0..end] to literals.
pub fn c_clear_span(plan: &mut [u32], p0: usize, end: usize) {
    let mut p = p0;
    while p < end && p < plan.len() {
        plan[p] = 0;
        p += 1;
    }
}

/// Block planner: follow the plan block by block; where the next BLOCK bytes code cheaper as
/// literals (so the encoder can store incompressible stretches), rewrite them as literals.
pub fn c_plan_blocks(s: &[u8], plan: &mut [u32]) {
    let n = s.len();
    let mut lf = [0u32; 288];
    let mut df = [0u32; 288];
    let mut p = 0usize;
    let mut fuel = n + 1;
    while p < n && p < plan.len() && fuel > 0 {
        fuel -= 1;
        let ea = c_path_block(s, plan, p, &mut lf, &mut df);
        let da = c_dyn_bits(&lf, &df);
        let fa = c_fixed_bits(&lf, &df);
        let ca = if da < fa { da } else { fa };
        let eb = if n - p > C_BLOCK { p + C_BLOCK } else { n };
        let ec = if ea > eb { ea } else { eb };
        let mut lb = [0u32; 288];
        let zb = [0u32; 288];
        let mut q = p;
        while q < ec {
            let sym = s[q] as usize;
            lb[sym] = lb[sym].wrapping_add(1);
            q += 1;
        }
        lb[256] = 1;
        let db = c_dyn_bits(&lb, &zb);
        let fb = c_fixed_bits(&lb, &zb);
        let sb = 8 * ((ec - p) as u64) + 40;
        let mut cb = if db < fb { db } else { fb };
        if sb < cb {
            cb = sb;
        }
        if ea > p && ca <= cb {
            p = ea;
        } else {
            c_clear_span(plan, p, eb);
            p = eb;
        }
    }
}

/// Repeat statistics on every `C_REP_STEP`-th position (most recent occurrence of each 4-byte key):
/// returns (4-byte repeats, 6-byte repeats) per 65536 sampled positions. Stops early once the
/// 6-byte repeats alone exceed `C_REP6_MIN` over the whole input.
pub fn c_rep_match(s: &[u8], a: usize, p: usize) -> usize {
    if p - a > C_WS { return 0; }
    if s[a] != s[p] || s[a + 1] != s[p + 1]
        || s[a + 2] != s[p + 2] || s[a + 3] != s[p + 3] {
        return 0;
    }
    if s[a + 4] == s[p + 4] && s[a + 5] == s[p + 5] { return 6; }
    4
}

pub fn c_rep_rates(s: &[u8]) -> (usize, usize) {
    let n = s.len();
    if n < 64 {
        return (0, 0);
    }
    let mut head = [0u32; 16384];
    let mut r4 = 0usize;
    let mut r6 = 0usize;
    let mut probes = 0usize;
    let mut p = 0usize;
    while p + 8 <= n {
        let v = ((s[p] as u32) << 24) | ((s[p + 1] as u32) << 16) | ((s[p + 2] as u32) << 8) | (s[p + 3] as u32);
        let h = (v.wrapping_mul(0x9E37_79B1) >> 18) as usize;
        let c = head[h % 16384] as usize;
        if c > 0 && c <= p {
            let a = c - 1;
            let matched = c_rep_match(s, a, p);
            if matched >= 4 {
                r4 += 1;
                if matched >= 6 {
                    r6 += 1;
                    if r6 >= 64 && (r6 as u64) * 131072 >= 24 * (n as u64) && probes >= C_REP_MINPROBE {
                        return (((r4 as u64) * 65536 / (probes as u64 + 1)) as usize, ((r6 as u64) * 65536 / (probes as u64 + 1)) as usize);
                    }
                }
            }
        }
        head[h % 16384] = (p + 1) as u32;
        probes += 1;
        p += C_REP_STEP;
    }
    (((r4 as u64) * 65536 / (probes as u64 + 1)) as usize, ((r6 as u64) * 65536 / (probes as u64 + 1)) as usize)
}

/// Engine C: writes the plan (length n, zeroed). Knobs: tree depth (generic), tree depth (DNA
/// lower case), weights DP on/off and its passes, passes (tree class, DNA max/min, chain4 class).
#[inline(never)]
pub fn c_engine(input: &[u8], out: &mut Vec<u32>, depth: usize, depth_lo: usize, wdp: usize, passes_w: usize, passes_bt: usize, passes_dna: usize, min_dna: usize, passes_c4: usize) {
    let n = input.len();
    if out.len() < n {
        return;
    }
    let dna = c_is_dna(input);
    let mut chain4 = 0usize;
    let mut wmode = 0usize;
    if dna == 0 {
        let (r4, r6) = c_rep_rates(input);
        if r6 < C_REP6_MIN {
            if wdp == 0 || r4 < C_WREP4_MIN {
                return;
            }
            wmode = 1;
        } else if r6 >= 32768 {
            chain4 = 2;
        } else if r4 >= C_CHAIN4_RATIO * r6 {
            chain4 = 1;
        }
    }
    let mut clist: Vec<u32> = Vec::with_capacity(n / 2 + 16);
    if dna > 0 {
        c_find_dna(input, &mut clist, depth_lo);
    } else if wmode > 0 {
        c_find_bin(input, &mut clist, 1, C_DEPTH4_W);
    } else if chain4 > 0 {
        c_find_bin(input, &mut clist, 1, C_DEPTH4);
    } else {
        c_find_bin(input, &mut clist, 0, depth);
    }
    let mut models: Vec<u32> = Vec::new();
    let mut bstart: Vec<u32> = Vec::new();
    let passes = if dna > 0 { passes_dna } else if wmode > 0 { passes_w } else if chain4 == 2 { C_PASSES_SP } else if chain4 > 0 { passes_c4 } else { passes_bt };
    let tax = if wmode > 0 { C_TAX_W } else if chain4 > 0 { C_TAX_C4 } else if dna > 0 { 0 } else { C_TAX_BT };
    let ulen = if wmode > 0 { C_UNUSED_LEN_W } else { C_UNUSED_LEN };
    let udist = if wmode > 0 { C_UNUSED_DIST_W } else { C_UNUSED_DIST };
    // seed: a greedy parse for binary input, all literals for DNA and weights
    let gmin = if dna > 0 || wmode > 0 { 259 } else { C_GMIN };
    c_greedy_choice(&clist, out, n, gmin);
    let tokpen = if dna > 0 { C_TOKPEN } else if wmode > 0 { C_TOKPEN_W } else if chain4 > 0 { C_TOKPEN_C4 } else { C_TOKPEN_BT };
    let lit_est = c_restat(input, out, &mut models, &mut bstart, tax, ulen, udist, tokpen);
    let mut last_est = lit_est;
    let mut prev_est = lit_est;
    let mut pass = 0usize;
    while pass < passes {
        c_dp_pass(input, &clist, &models, &bstart, out);
        pass += 1;
        if pass < passes {
            last_est = c_restat(input, out, &mut models, &mut bstart, tax, C_UNUSED_LEN, C_UNUSED_DIST, tokpen);
            if dna > 0 && pass >= min_dna && last_est <= prev_est && prev_est - last_est < prev_est / C_STOP_DIV {
                pass = passes;
            }
            prev_est = last_est;
        }
    }
    if dna > 0 && last_est >= lit_est {
        c_clear_span(out, 0, n);
        return;
    }
    if dna > 0 || chain4 == 2 {
        return;
    }
    c_plan_blocks(input, out);
}

// ───────────────────────────── engine X: light planners (search only) ─────────────────────────────

/// Engine X, a light planner for row `k`: 1 = runs of the previous byte (`r_plan`), anything else = no plan
/// (every byte a literal). The plan is a token list for `emit`, which re-checks every planned match.
#[inline(never)]
pub fn x_plan(input: &[u8], k: usize) -> Vec<u32> {
    if k == 1 && input.len() < 67108864 {
        r_plan(input)
    } else {
        Vec::new()
    }
}

/// Length of the run of byte `c` starting at `p` (at most 258).
pub fn r_run(input: &[u8], p: usize, c: u8) -> usize {
    let n = input.len();
    let mut l = 0usize;
    while l < 258 && p + l < n && input[p + l] == c {
        l += 1;
    }
    l
}

/// Run planner: at a position whose previous byte repeats at least 3 times, a distance-1 match over the run;
/// elsewhere a literal.
#[inline(never)]
pub fn r_plan(input: &[u8]) -> Vec<u32> {
    let n = input.len();
    let mut plan: Vec<u32> = Vec::with_capacity(n / 4 + 16);
    let mut p = 0usize;
    while p < n {
        let l = if p >= 1 { r_run(input, p, input[p - 1]) } else { 0 };
        if l >= 3 {
            d_push32(&mut plan, (l as u32) | 512);
            p += l;
        } else {
            d_push32(&mut plan, 0);
            p += 1;
        }
    }
    plan
}

// ===== engine e: parse.rs =====
pub const E_SHIFT: u32 = 22;
pub const E_F3: usize = 16;
pub const E_FP: usize = 2;
pub const E_FB: u32 = 96;
// Numeric short-match block DP. All search is untrusted; emission rechecks every byte.

pub fn e_match_len(input: &[u8], a: usize, b: usize, cap: usize) -> usize {
    let mut l = 0usize;
    while l < cap && input[b + l] == input[a + l] {
        l += 1;
    }
    l
}


#[inline(always)]
pub fn e_dcode(dlo: &[u8; 256], dhi: &[u8; 256], d: usize) -> usize {
    if d <= 256 {
        let k = if d >= 1 { d - 1 } else { 0 };
        dlo[k % 256] as usize
    } else {
        dhi[((d - 1) / 128) % 256] as usize
    }
}


pub fn e_hins(w: &mut [u32; 512], sym: &mut [u16; 512], m: usize, x: u32, sy: usize) {
    let mut j = m;
    while j > 0 && j < 512 && w[(j - 1) % 512] > x {
        w[j % 512] = w[(j - 1) % 512];
        sym[j % 512] = sym[(j - 1) % 512];
        j -= 1;
    }
    w[j % 512] = x;
    sym[j % 512] = sy as u16;
}


pub fn e_hlens(f: &[u32; 512], ns: usize, out: &mut [u32; 512]) {
    let mut w = [0u32; 512];
    let mut sym = [0u16; 512];
    let mut m = 0usize;
    let mut s = 0usize;
    while s < ns && s < 512 {
        out[s] = 0;
        if f[s] > 0 {
            e_hins(&mut w, &mut sym, m, f[s], s);
            m = m.wrapping_add(1);
        }
        s += 1;
    }
    if m == 1 {
        out[(sym[0] as usize) % 512] = 1;
    }
    if m >= 2 {
        e_hbuild(&w, &sym, m, out);
    }
}


pub fn e_hbuild(w: &[u32; 512], sym: &[u16; 512], m: usize, out: &mut [u32; 512]) {
    let mut nw = [0u32; 1024];
    let mut par = [0u16; 1024];
    let mut dep = [0u32; 1024];
    let mut k = 0usize;
    while k < m && k < 512 {
        nw[k] = w[k];
        k += 1;
    }
    let mut i1 = 0usize;
    let mut i2 = m;
    let mut t = 0usize;
    while t < 512 && t + 1 < m && m <= 512 {
        let top = m.wrapping_add(t);
        let mut pick = 0usize;
        let mut a = 0usize;
        let mut b = 0usize;
        while pick < 2 {
            let take1 = if i1 < m && (i2 >= top || nw[i1 % 1024] <= nw[i2 % 1024]) { 1usize } else { 0usize };
            let x = if take1 == 1 { i1 } else { i2 };
            if take1 == 1 {
                i1 = i1.wrapping_add(1);
            } else {
                i2 = i2.wrapping_add(1);
            }
            if pick == 0 {
                a = x;
            } else {
                b = x;
            }
            pick += 1;
        }
        nw[top % 1024] = nw[a % 1024].wrapping_add(nw[b % 1024]);
        par[a % 1024] = top as u16;
        par[b % 1024] = top as u16;
        t += 1;
    }
    let root = if m >= 2 { m.wrapping_mul(2).wrapping_sub(2) } else { 0 };
    dep[root % 1024] = 0;
    let mut r = 1usize;
    while r <= root && root < 1024 {
        let x = root - r;
        let pd = dep[(par[x % 1024] as usize) % 1024];
        dep[x % 1024] = pd.wrapping_add(1);
        r += 1;
    }
    k = 0;
    while k < m && k < 512 {
        let d = dep[k % 1024];
        out[(sym[k % 512] as usize) % 512] = if d > 15 { 15 } else { d };
        k += 1;
    }
}


pub fn e_verified(input: &[u8], pos: usize, d: usize, ch: usize, k: usize, blen: usize) -> bool {
    if ch < 3 || ch > 258 || d < 1 || d > 32768 || d > pos || k + ch > blen {
        return false;
    }
    let v = e_match_len(input, pos - d, pos, ch);
    v >= ch
}


pub fn e_emit(
    input: &[u8],
    out: &mut [u32],
    chl: &[u16; 32768],
    chd: &[u16; 32768],
    ntok0: usize,
    p0: usize,
    blen: usize,
) -> usize {
    let mut ntok = ntok0;
    let mut k = 0usize;
    while k < blen {
        let pos = p0 + k;
        let ch = chl[k % 32768] as usize;
        let d = chd[k % 32768] as usize;
        if e_verified(input, pos, d, ch, k, blen) {
            out[ntok] = 16777216u32 + ((d - 1) as u32) * 256 + ((ch - 3) as u32);
            ntok += 1;
            k += ch;
        } else {
            out[ntok] = input[pos] as u32;
            ntok += 1;
            k += 1;
        }
    }
    ntok
}


pub fn e_len_tables(
    lbase: &[u16; 32],
    lext: &[u8; 32],
    lcode: &mut [u8; 512],
    lextra: &mut [u8; 512],
    bend: &mut [u16; 512],
) {
    let mut c = 0usize;
    let mut l = 3usize;
    while l <= 258 {
        if c < 28 && lbase[(c.wrapping_add(1)) % 32] as usize <= l {
            c = c.wrapping_add(1);
        }
        lcode[l] = c as u8;
        lextra[l] = lext[c % 32];
        let top = lbase[(c.wrapping_add(1)) % 32];
        bend[l] = if top >= 1 { top - 1 } else { 0 };
        l += 1;
    }
}


pub fn e_code_from(dbase: &[u16; 32], d: usize, c0: usize) -> usize {
    let mut c = c0;
    while c < 29 && dbase[(c + 1) % 32] as usize <= d {
        c += 1;
    }
    c
}


pub fn e_dist_tables(dbase: &[u16; 32], dlo: &mut [u8; 256], dhi: &mut [u8; 256]) {
    let mut c = 0usize;
    let mut d = 1usize;
    while d <= 256 {
        c = e_code_from(dbase, d, c);
        dlo[(d.wrapping_sub(1)) % 256] = c as u8;
        d += 1;
    }
    let mut k = 0usize;
    c = 0;
    while k < 256 {
        c = e_code_from(dbase, k * 128 + 1, c);
        dhi[k] = c as u8;
        k += 1;
    }
}


pub fn e_tables(
    lcode: &mut [u8; 512],
    lextra: &mut [u8; 512],
    bend: &mut [u16; 512],
    dlo: &mut [u8; 256],
    dhi: &mut [u8; 256],
    dext: &mut [u8; 32],
) {
    let lbase: [u16; 32] = [
        3, 4, 5, 6, 7, 8, 9, 10, 11, 13, 15, 17, 19, 23, 27, 31, 35, 43, 51, 59, 67, 83, 99, 115,
        131, 163, 195, 227, 258, 259, 259, 259,
    ];
    let lext: [u8; 32] = [
        0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 2, 2, 2, 2, 3, 3, 3, 3, 4, 4, 4, 4, 5, 5, 5, 5, 0, 0, 0,
        0,
    ];
    let dbase: [u16; 32] = [
        1, 2, 3, 4, 5, 7, 9, 13, 17, 25, 33, 49, 65, 97, 129, 193, 257, 385, 513, 769, 1025, 1537,
        2049, 3073, 4097, 6145, 8193, 12289, 16385, 24577, 32769, 32769,
    ];
    let dx: [u8; 32] = [
        0, 0, 0, 0, 1, 1, 2, 2, 3, 3, 4, 4, 5, 5, 6, 6, 7, 7, 8, 8, 9, 9, 10, 10, 11, 11, 12, 12,
        13, 13, 0, 0,
    ];
    e_len_tables(&lbase, &lext, lcode, lextra, bend);
    e_dist_tables(&dbase, dlo, dhi);
    *dext = dx;
}



pub const E_BLOCK: usize = 32768;
pub const E_PROBES: usize = 8;
pub const E_NX: usize = 3;
pub const E_PASSES: usize = 1;
pub const E_HW: u32 = 0;
pub const E_BIAS: u32 = 0;

#[inline(always)]
pub fn e_ld4(input: &[u8], p: usize) -> u32 {
    let n = input.len();
    if n < 4 || p > n - 4 { return 0; }
    (input[p] as u32) | ((input[p + 1] as u32) << 8)
       | ((input[p + 2] as u32) << 16) | ((input[p + 3] as u32) << 24)
}



#[inline(always)]
pub fn e_lcp_after(input: &[u8], a: usize, b: usize, cap: usize, start: usize) -> usize {
    let mut l=start;
    while l < cap && l < 258 && e_at(input,a.wrapping_add(l)) == e_at(input,b.wrapping_add(l)) { l += 1; }
    l
}

#[inline(always)]
pub fn e_at(input: &[u8], p: usize) -> u8 {
    if p < input.len() { input[p] } else { 0 }
}

pub fn e_log16(x: u32) -> u32 {
    let y = x | 1;
    let e = 31u32.wrapping_sub(y.leading_zeros()) % 32;
    let m = if e >= 8 { (y >> (e.wrapping_sub(8) % 32)) & 255 }
            else { (y << (8u32.wrapping_sub(e) % 32)) & 255 };
    e.wrapping_mul(16).wrapping_add(m / 16)
}

#[inline(always)]
pub fn e_cost16(f: u32, total: u32) -> u32 {
    if f == 0 { 192 } else {
        let v = e_log16(total).saturating_sub(e_log16(f));
        if v < 16 { 16 } else { v }
    }
}



#[inline(always)]
pub fn e_prices(lf: &[u32; 512], df: &[u32; 32],
    litc: &mut [u32; 256], lenc: &mut [u32; 512], dc: &mut [u32; 32],
    lc: &[u8; 512], le: &[u8; 512], de: &[u8; 32], hw0: u32, penalty: u32) {
    let hw=hw0 % 17;
    let mut hl = [0u32; 512];
    if hw > 0 { e_hlens(lf, 286, &mut hl); }
    let mut dh = [0u32; 512];
    let mut tmp = [0u32; 512];
    let mut i = 0usize;
    while i < 32 { tmp[i] = df[i]; i += 1; }
    if hw > 0 { e_hlens(&tmp, 30, &mut dh); }
    let mut total = 1u32;
    i = 0;
    while i < 286 { total = total.wrapping_add(lf[i]); i += 1; }
    i = 0;
    while i < 256 {
        let e = e_cost16(lf[i],total);
        let h = if hl[i] == 0 { e } else { hl[i].wrapping_mul(16) };
        litc[i] = e.wrapping_mul(16u32.wrapping_sub(hw)).wrapping_add(h.wrapping_mul(hw)) / 16;
        i += 1;
    }
    i = 3;
    while i <= 258 {
        let c = (257 + lc[i] as usize) % 512;
        let e = e_cost16(lf[c],total);
        let h = if hl[c] == 0 { e } else { hl[c].wrapping_mul(16) };
        lenc[i] = (e.wrapping_mul(16u32.wrapping_sub(hw)).wrapping_add(h.wrapping_mul(hw)) / 16).wrapping_add((le[i] as u32)*16).wrapping_add(penalty);
        if penalty > 0 && i == 4 {lenc[i]=lenc[i].saturating_sub(28);}
        i += 1;
    }
    total = 1; i = 0;
    while i < 30 { total = total.wrapping_add(df[i]); i += 1; }
    i = 0;
    while i < 30 {
        let e = e_cost16(df[i],total);
        let h = if dh[i] == 0 { e } else { dh[i].wrapping_mul(16) };
        dc[i] = (e.wrapping_mul(16u32.wrapping_sub(hw)).wrapping_add(h.wrapping_mul(hw)) / 16).wrapping_add((de[i] as u32)*16);
        i += 1;
    }
}



#[inline(always)]
pub fn e_put(xs: &mut [u32; 131072], k: usize, s: usize, v: u32) {
    xs[k.wrapping_mul(E_NX).wrapping_add(s)%131072]=v;
}

#[inline(always)]
pub fn e_near_candidate(input: &[u8], c: usize, pos: usize, cap: usize, key: u32, max3: usize) -> u32 {
    if c > 0 && c <= pos && pos-(c-1) <= max3 && pos-(c-1) <= 32768 && e_ld4(input,c-1)&16777215 == key {
        let l=e_lcp_after(input,c-1,pos,cap,3);
        ((pos-(c-1)) as u32).wrapping_mul(512).wrapping_add(l as u32)
    } else {0}
}

#[inline(always)]
pub fn e_walk_four(input: &[u8], prev: &[u32; 32768], xs: &mut [u32; 131072],
    pos: usize, k: usize, cap: usize, word: u32, cur0: usize, longest0: usize, s0: usize) {
    let mut cur=cur0;let mut longest=longest0;let mut s=s0;let mut it=0usize;
    while it < E_PROBES && s < E_NX && cur > 0 && cur <= pos && pos-(cur-1) <= 32768 && longest < cap {
        let a=cur-1;
        if e_ld4(input,a) == word {
            let l=e_lcp_after(input,a,pos,cap,4);
            if l > longest && s < E_NX {
                e_put(xs,k,s,((pos-a) as u32).wrapping_mul(512).wrapping_add(l as u32));
                longest=l;s=s.wrapping_add(1);
            }
        }
        cur=prev[a%32768] as usize;it += 1;
    }
}




#[inline(always)]
pub fn e_exact4(input: &[u8], c: usize, pos: usize, cap: usize, word: u32) -> u32 {
    if c > 0 && c <= pos && pos-(c-1) <= 32768 && e_ld4(input,c-1) == word {
        let l=e_lcp_after(input,c-1,pos,cap,4);
        ((pos-(c-1)) as u32).wrapping_mul(512).wrapping_add(l as u32)
    } else {0}
}



#[inline(always)]
pub fn e_exact_bf(input: &[u8], c: u32, pos: usize, cap: usize, word: u32, tag: u32) -> u32 {
    let d=pos.wrapping_sub((c&65535) as usize)&65535;
    if c>>16 == tag && d >= 1 && d <= 32768 && d <= pos && e_ld4(input,pos-d) == word {
        let l=e_lcp_after(input,pos-d,pos,cap,4);
        (d as u32).wrapping_mul(512).wrapping_add(l as u32)
    } else {0}
}


#[inline(always)]
pub fn e_bf_choice(xs: &mut [u32; 131072], k: usize, v: u32, longest: usize, s: usize) -> (usize, usize) {
    let l=v as usize%512;
    if l > longest && s < 2 {
        xs[k.wrapping_mul(2).wrapping_add(s)%131072]=v;
        (l,s+1)
    } else {(longest,s)}
}

#[inline(always)]
pub fn e_find_bf(input: &[u8], near: &mut [u32; 65536], head: &mut [u32; 131072], xs: &mut [u32; 131072], pos: usize, k: usize, cap: usize) {
    let word=e_ld4(input,pos);
    let hash=word.wrapping_mul(2654435761);
    let tag=hash&65535;
    let h=((hash>>16) as usize).wrapping_mul(2)%131072;
    let h2=h.wrapping_add(1)%131072;
    let c=head[h];let c2=head[h2];
    head[h2]=c;head[h]=(tag<<16)|((pos as u32)&65535);
    let hh=((word&16777215).wrapping_mul(2654435761)>>E_SHIFT) as usize;
    let c3=near[hh%65536] as usize;near[hh%65536]=(pos as u32).wrapping_add(1);
    let v=e_near_candidate(input,c3,pos,cap,word&16777215,16);
    let z=e_bf_choice(xs,k,v,2,0);
    let v=e_exact_bf(input,c,pos,cap,word,tag);
    let z=e_bf_choice(xs,k,v,z.0,z.1);
    let v=e_exact_bf(input,c2,pos,cap,word,tag);
    let z=e_bf_choice(xs,k,v,z.0,z.1);
    if z.1 < 2 {xs[k.wrapping_mul(2).wrapping_add(z.1)%131072]=0;}
}

#[inline(always)]
pub fn e_find_dual(input: &[u8], near: &mut [u32; 65536], head: &mut [u32; 131072],
    prev: &mut [u32; 32768], xs: &mut [u32; 131072], pos: usize, k: usize, cap: usize, max3: usize, mode: usize) {
    let n=input.len();
    if pos > n || cap < 4 || cap > 258 || cap > n-pos { return; }
    let word=e_ld4(input,pos);
    let key=word & 16777215;
    let h3=(key.wrapping_mul(2654435761)>>16) as usize;
    let h4=(word.wrapping_mul(2654435761)>>16) as usize;
    let near0=near[h3%65536] as usize;
    near[h3%65536]=(pos as u32).wrapping_add(1);
    let cur=head[h4%65536] as usize;
    prev[pos%32768]=head[h4%65536];
    head[h4%65536]=(pos as u32).wrapping_add(1);
    let v=e_near_candidate(input,near0,pos,cap,key,max3);
    let longest=if v > 0 {v as usize%512} else {2};
    let s=if v > 0 {1} else {0};
    if v > 0 {e_put(xs,k,0,v);}
    e_walk_four(input,prev,xs,pos,k,cap,word,cur,longest,s);
}

#[inline(always)]
pub fn e_clear_pos(xs: &mut [u32; 131072], k: usize) {
    let mut s=0usize;
    while s < E_NX { xs[(k.wrapping_mul(E_NX).wrapping_add(s))%131072]=0; s += 1; }
}

#[inline(always)]
pub fn e_long_at(xs: &[u32; 131072], k: usize, stride: usize) -> usize {
    let mut i=0usize;let mut flag=0usize;
    while i < stride && i < E_NX {
        if xs[k.wrapping_mul(stride).wrapping_add(i)%131072]%512 >= 12 {flag=1;}
        i += 1;
    }
    flag
}

#[inline(always)]
pub fn e_candidates(input: &[u8], near: &mut [u32; 65536], head: &mut [u32; 131072],
    prev: &mut [u32; 32768], xs: &mut [u32; 131072], p0: usize, blen: usize, max3: usize, mode: usize, stride: usize) -> usize {
    let n=input.len();
    let mut k=0usize;let mut flag=0usize;
    while k < blen && k < 32768 && flag == 0 && p0 <= n && blen <= n-p0 {
        if mode != 2 {e_clear_pos(xs,k);}
        let rest=blen-k;
        let cap=if rest < 258 {rest} else {258};
        if mode == 2 {
            if cap >= 4 {e_find_bf(input,near,head,xs,p0.wrapping_add(k),k,cap);}
            else {xs[k.wrapping_mul(2)%131072]=0;}
        } else {e_find_dual(input,near,head,prev,xs,p0.wrapping_add(k),k,cap,max3,mode);}
        flag=e_long_at(xs,k,stride);
        k += 1;
    }
    flag
}

#[inline(always)]
pub fn e_boot(input: &[u8], litc: &mut [u32; 256], lenc: &mut [u32; 512],
    dc: &mut [u32; 32], le: &[u8; 512], de: &[u8; 32], p0: usize, blen: usize, bc: u32) {
    let n=input.len();
    let mut hist=[0u32;256];
    let mut k=0usize;
    while k < blen && k < 32768 && p0 <= n && blen <= n-p0 {
        let b=e_at(input,p0.wrapping_add(k)) as usize;hist[b]=hist[b].wrapping_add(1);k += 1;
    }
    k=0;
    while k < 256 { litc[k]=e_cost16(hist[k],(blen as u32).wrapping_add(1)); k += 1; }
    k=3;
    while k <= 258 { lenc[k]=bc.wrapping_add((le[k] as u32)*16); k += 1; }
    k=0;
    while k < 30 { dc[k]=48+(de[k] as u32)*16; k += 1; }
}

#[inline(always)]
pub fn e_backward(input: &[u8], xs: &[u32; 131072], cost: &mut [u32; 65536],
    chl: &mut [u16; 32768], chd: &mut [u16; 32768],
    litc: &[u32; 256], lenc: &[u32; 512], dc: &[u32; 32],
    dlo: &[u8; 256], dhi: &[u8; 256], p0: usize, blen: usize, stride: usize) {
    let n = input.len();
    if blen <= 32768 && p0 <= n && blen <= n - p0 {
        cost[blen%65536]=0;
        let mut k = blen;
        while k > 0 && k <= blen {
            k -= 1;
            let mut best = cost[(k.wrapping_add(1))%65536].wrapping_add(litc[e_at(input,p0.wrapping_add(k)) as usize]);
            let mut bl = 0usize;
            let mut bd = 0usize;
            let mut s = 0usize;
            let mut lo = 3usize;
            while s < E_NX && s < stride && xs[(k.wrapping_mul(stride).wrapping_add(s))%131072] != 0 {
                let v = xs[(k.wrapping_mul(stride).wrapping_add(s))%131072] as usize;
                let lm = v%512;
                let d = v/512;
                if lm >= lo && lm <= 258 && k <= blen && lm <= blen-k && d >= 1 && d <= 32768 {
                    let dcs = dc[e_dcode(dlo,dhi,d)%32];
                    let mut l = lo;
                    while l <= lm && l <= 258 {
                        let price = cost[(k.wrapping_add(l))%65536].wrapping_add(lenc[l%512]).wrapping_add(dcs);
                        if price < best { best=price; bl=l; bd=d; }
                        l += 1;
                    }
                    lo = lm.wrapping_add(1);
                }
                s += 1;
            }
            cost[k%65536]=best;
            chl[k%32768]=bl as u16;
            chd[k%32768]=bd as u16;
        }
    }
}

#[inline(always)]
pub fn e_count(input: &[u8], chl: &[u16; 32768], chd: &[u16; 32768],
    lf: &mut [u32; 512], df: &mut [u32; 32], lc: &[u8; 512],
    dlo: &[u8; 256], dhi: &[u8; 256], p0: usize, blen: usize) {
    let n=input.len();
    let mut i=0usize;
    while i < 512 { lf[i]=0; i += 1; }
    i=0;
    while i < 32 { df[i]=0; i += 1; }
    let mut k=0usize;
    while k < blen && k < 32768 && p0 <= n && blen <= n-p0 {
        let l=chl[k%32768] as usize;
        let d=chd[k%32768] as usize;
        if l >= 3 && l <= 258 && l <= blen-k && d >= 1 && d <= 32768 {
            let a=(257+lc[l%512] as usize)%512;
            lf[a]=lf[a].wrapping_add(1);
            let a=e_dcode(dlo,dhi,d)%32;
            df[a]=df[a].wrapping_add(1);
            k += l;
        } else {
            let a=e_at(input,p0.wrapping_add(k)) as usize;
            lf[a]=lf[a].wrapping_add(1);
            k += 1;
        }
    }
    lf[256]=1;
}



pub fn e_quality(input: &[u8]) -> usize {
    let mut seen=[0u8;2048];let mut cnt=[0usize;8];let mut i=0usize;
    while i < input.len() && i < 4096 {
        let lane=i%8;let h=lane*256+input[i] as usize;
        if seen[h%2048] == 0 {cnt[lane]=cnt[lane].wrapping_add(1);seen[h%2048]=1;}
        i += 1;
    }
    let mut m=0usize;i=0;
    while i < 8 {if cnt[i] > m {m=cnt[i];}i += 1;}
    if m >= 180 {1} else {0}
}

pub fn e_pick(input: &[u8]) -> usize {
    let mut k=8usize;
    let mut hi=0usize;
    let mut a1=0usize;
    let mut a2=0usize;
    let mut a4=0usize;
    while k >= 8 && k < input.len() && k < 4104 {
        let x=input[k];
        if x >= 128 {hi=hi.wrapping_add(1);}
        if x == input[k-1] {a1=a1.wrapping_add(1);}
        if x == input[k-2] {a2=a2.wrapping_add(1);}
        if x == input[k-4] {a4=a4.wrapping_add(1);}
        k += 1;
    }
    let m=k.wrapping_sub(8);
    if e_quality(input) == 1 && m >= 256 && hi.wrapping_mul(4) > m && a1.wrapping_mul(16) < m {
        if a2.wrapping_mul(32) > m {2} else if a4.wrapping_mul(32) > m {4} else {0}
    } else {0}
}

pub fn e_literal_plan(chl: &mut [u16; 32768], blen: usize) {
    let mut k=0usize;
    while k < blen && k < 32768 { chl[k]=0; k += 1; }
}

#[inline(always)]
pub fn e_head_put(head: &mut [u32; 131072], h: usize, x: u32) {head[h%131072]=x;}

pub fn e_fallback(input: &[u8], head: &mut [u32; 131072],
    chl: &mut [u16; 32768], chd: &mut [u16; 32768], p0: usize, blen: usize) {
    let mut k=0usize;
    while k < blen && k < 32768 {
        let pos=p0.wrapping_add(k);
        let rest=blen-k;
        let cap=if rest < 258 {rest} else {258};
        let w=e_ld4(input,pos);
        let h=(w.wrapping_mul(2654435761)>>16) as usize;
        let c=head[h%65536] as usize;
        e_head_put(head,h%65536,(pos as u32).wrapping_add(1));
        let v=e_exact4(input,c,pos,cap,w) as usize;
        let l=v%512;let d=v/512;
        if l >= 4 && l <= cap {
            chl[k%32768]=l as u16;chd[k%32768]=d as u16;
            k += l;
        } else {
            chl[k%32768]=0;k += 1;
        }
    }
}

pub fn e_zeros(input: &[u8], p0: usize, blen: usize) -> usize {
    let mut k=0usize;let mut z=0usize;
    while k < blen && k < 1024 {
        if e_at(input,p0.wrapping_add(k)) == 0 {z=z.wrapping_add(1);}
        k += 1;
    }
    z
}

#[inline(always)]
pub fn e_refine(input: &[u8], xs: &[u32; 131072], cost: &mut [u32; 65536],
    chl: &mut [u16; 32768], chd: &mut [u16; 32768],
    lf: &mut [u32; 512], df: &mut [u32; 32],
    lc: &[u8; 512], le: &[u8; 512], de: &[u8; 32], dlo: &[u8; 256], dhi: &[u8; 256],
    p0: usize, blen: usize, rounds: usize, hw: u32, penalty: u32, stride: usize) {
    let mut litc=[0u32;256];let mut lenc=[0u32;512];let mut dc=[0u32;32];
    let mut pass=0usize;
    while pass < rounds {
        e_prices(lf,df,&mut litc,&mut lenc,&mut dc,lc,le,de,hw,penalty);
        e_backward(input,xs,cost,chl,chd,&litc,&lenc,&dc,dlo,dhi,p0,blen,stride);
        if pass.wrapping_add(1) < rounds {e_count(input,chl,chd,lf,df,lc,dlo,dhi,p0,blen);}
        pass += 1;
    }
}

#[inline(always)]
pub fn e_settings(mode: usize) -> (usize, u32, u32, usize, u32, usize) {
    if mode == 4 {(E_FP,0,8,E_F3,E_FB,E_NX)} else {(E_PASSES,16,0,16,96,2)}
}


pub fn e_probe(input: &[u8], head: &mut [u32; 131072], p0: usize, blen: usize) -> usize {
    let mut i=0usize;let mut flag=0usize;
    while i < blen && i < 32768 && flag == 0 {
        let pos=p0.wrapping_add(i);let rest=blen-i;
        let cap=if rest < 12 {rest} else {12};
        let word=e_ld4(input,pos);
        let h=(word.wrapping_mul(2654435761)>>16) as usize;
        let c=head[h%65536] as usize;
        e_head_put(head,h%65536,(pos as u32).wrapping_add(1));
        let v=e_exact4(input,c,pos,cap,word);
        if v%512 >= 12 {flag=1;}
        i += 4;
    }
    flag
}

pub fn e_literal_fast(input: &[u8], head: &mut [u32; 131072],
    chl: &mut [u16; 32768], chd: &mut [u16; 32768], p0: usize, blen: usize) {
    let flag=e_probe(input,head,p0,blen);
    if flag > 0 {e_fallback(input,head,chl,chd,p0,blen);}
    else {e_literal_plan(chl,blen);}
}

#[inline(always)]
pub fn e_finish(input: &[u8], head: &mut [u32; 131072], xs: &[u32; 131072],
    cost: &mut [u32; 65536], chl: &mut [u16; 32768], chd: &mut [u16; 32768],
    lf: &mut [u32; 512], df: &mut [u32; 32],
    lc: &[u8; 512], le: &[u8; 512], de: &[u8; 32], dlo: &[u8; 256], dhi: &[u8; 256],
    p0: usize, blen: usize, cfg: (usize,u32,u32,usize,u32,usize), flag: usize) {
    if flag > 0 {e_fallback(input,head,chl,chd,p0,blen);return;}
    let mut litc=[0u32;256];let mut lenc=[0u32;512];let mut dc=[0u32;32];
    e_boot(input,&mut litc,&mut lenc,&mut dc,le,de,p0,blen,cfg.4);
    e_backward(input,xs,cost,chl,chd,&litc,&lenc,&dc,dlo,dhi,p0,blen,cfg.5);
    e_count(input,chl,chd,lf,df,lc,dlo,dhi,p0,blen);
    e_refine(input,xs,cost,chl,chd,lf,df,lc,le,de,dlo,dhi,p0,blen,cfg.0,cfg.1,cfg.2,cfg.5);
}

#[inline(always)]
pub fn e_plan(input: &[u8], near: &mut [u32; 65536], head: &mut [u32; 131072], prev: &mut [u32; 32768],
    xs: &mut [u32; 131072], cost: &mut [u32; 65536],
    chl: &mut [u16; 32768], chd: &mut [u16; 32768],
    lf: &mut [u32; 512], df: &mut [u32; 32],
    lc: &[u8; 512], le: &[u8; 512], de: &[u8; 32],
    dlo: &[u8; 256], dhi: &[u8; 256], mode: usize, p0: usize, blen: usize) {
    if mode == 0 {e_fallback(input,head,chl,chd,p0,blen); return;}
    if e_zeros(input,p0,blen) > 400 {e_fallback(input,head,chl,chd,p0,blen); return;}
    if mode == 4 && e_zeros(input,p0,blen) < 64 {e_literal_fast(input,head,chl,chd,p0,blen); return;}
    let cfg=e_settings(mode);
    let flag=e_candidates(input,near,head,prev,xs,p0,blen,cfg.3,mode,cfg.5);
    e_finish(input,head,xs,cost,chl,chd,lf,df,lc,le,de,dlo,dhi,p0,blen,cfg,flag);
}

#[inline(never)]
pub fn e_parse(input: &[u8], out: &mut [u32]) -> usize {
    let n=input.len();
    let mode=e_pick(input);
    let mut lc=[0u8;512]; let mut le=[0u8;512]; let mut bend=[0u16;512];
    let mut dlo=[0u8;256]; let mut dhi=[0u8;256]; let mut de=[0u8;32];
    e_tables(&mut lc,&mut le,&mut bend,&mut dlo,&mut dhi,&mut de);
    let mut near=[0u32;65536];
    let mut head=[0u32;131072]; let mut prev=[0u32;32768];
    let mut xs=[0u32;131072]; let mut cost=[0u32;65536];
    let mut chl=[0u16;32768]; let mut chd=[0u16;32768];
    let mut lf=[0u32;512]; let mut df=[0u32;32];
    let mut ntok=0usize;
    let mut p0=0usize;
    while p0 < n {
        let rest=n-p0;
        let blen=if rest > E_BLOCK {E_BLOCK} else {rest};
        e_plan(input,&mut near,&mut head,&mut prev,&mut xs,&mut cost,&mut chl,&mut chd,
            &mut lf,&mut df,&lc,&le,&de,&dlo,&dhi,mode,p0,blen);
        ntok=e_emit(input,out,&chl,&chd,ntok,p0,blen);
        p0 += blen;
    }
    ntok
}

// ===== engine d of submission 239 (renamed q9_): parse.rs =====
pub const Q9_Y_PAIR4SIZE:usize=32768;
pub const Q9_Y_PAIR4SHIFT:u32=18;
pub const Q9_Y_SEEDBASE:u32=10;
pub const Q9_Y_H3SHIFT:u32=17;
pub const Q9_Y_WAYS:usize=2;
pub const Q9_TB: usize = 548;
pub const Q9_FB: usize = 320;
pub const Q9_BT: usize = 16384;
pub const Q9_SC: u32 = 16;
pub const Q9_UNUSED: u32 = 12;
pub const Q9_EW: u32 = 0;
pub const Q9_DW: u32 = 0;
pub const Q9_OV: u32 = 3;
pub const Q9_UPEN: u32 = 16;
pub const Q9_PUSH_LIMIT: usize = 1073741824;
pub const Q9_SLOTM: usize = 1;
pub const Q9_CL_ORDER: [usize; 19] = [16, 17, 18, 0, 8, 7, 9, 6, 10, 5, 11, 4, 12, 3, 13, 2, 14, 1, 15];
pub const Q9_LOG2F: [u32; 32] = [0, 1, 1, 2, 3, 3, 4, 5, 5, 6, 6, 7, 7, 8, 8, 9, 9, 10, 10, 11, 11, 12, 12, 13, 13, 13, 14, 14, 15, 15, 15, 16];
pub const Q9_Y_ITERS:usize=1;

pub fn q9_get(v: &[u32], i: usize) -> u32 {
    if i < v.len() {
        v[i]
    } else {
        0
    }
}

pub fn q9_set(v: &mut [u32], i: usize, x: u32) {
    if i < v.len() {
        v[i] = x;
    }
}

pub fn q9_bump(v: &mut [u32], i: usize, by: u32) {
    if i < v.len() {
        v[i] = v[i].wrapping_add(by);
    }
}

pub fn q9_byte_at(input: &[u8], i: usize) -> usize {
    if i < input.len() {
        input[i] as usize
    } else {
        0
    }
}

pub fn q9_filled(n: usize, x: u32) -> Vec<u32> {
    let mut v: Vec<u32> = Vec::with_capacity(n);
    let n8 = n / 8;
    let mut i = 0usize;
    while i < n8 {
        v.push(x);
        v.push(x);
        v.push(x);
        v.push(x);
        v.push(x);
        v.push(x);
        v.push(x);
        v.push(x);
        i += 1;
    }
    let mut j = n8 * 8;
    while j < n {
        v.push(x);
        j += 1;
    }
    v
}

pub fn q9_push_guarded(v: &mut Vec<u32>, x: u32) {
    if v.len() < Q9_PUSH_LIMIT {
        v.push(x);
    }
}

pub fn q9_sel(f: usize, a: usize, b: usize) -> usize {
    if f == 1 {
        a
    } else {
        b
    }
}

pub fn q9_sel32(f: usize, a: u32, b: u32) -> u32 {
    if f == 1 {
        a
    } else {
        b
    }
}

pub fn q9_sel64(f: usize, a: u64, b: u64) -> u64 {
    if f == 1 {
        a
    } else {
        b
    }
}

pub fn q9_lt(a: usize, b: usize) -> usize {
    if a < b {
        1
    } else {
        0
    }
}

pub fn q9_eq(a: usize, b: usize) -> usize {
    if a == b {
        1
    } else {
        0
    }
}

pub fn q9_lt32(a: u32, b: u32) -> usize {
    if a < b {
        1
    } else {
        0
    }
}

pub fn q9_lt64(a: u64, b: u64) -> usize {
    if a < b {
        1
    } else {
        0
    }
}

pub fn q9_umin(a: usize, b: usize) -> usize {
    if a < b {
        a
    } else {
        b
    }
}

pub fn q9_umax(a: usize, b: usize) -> usize {
    if a > b {
        a
    } else {
        b
    }
}

pub fn q9_clamp_step(l: usize, room: usize) -> usize {
    if l >= 3 && l <= room {
        l
    } else {
        1
    }
}

pub fn q9_clamp1(l: usize, room: usize) -> usize {
    if l >= 1 && l <= room {
        l
    } else {
        1
    }
}

pub fn q9_match_len(input: &[u8], a: usize, b: usize, cap: usize) -> usize {
    let mut l = 0usize;
    while l < cap && input[b + l] == input[a + l] {
        l += 1;
    }
    l
}

pub fn q9_verified(input: &[u8], pos: usize, d: usize, ch: usize) -> bool {
    let n = input.len();
    if ch < 3 || ch > 258 || d < 1 || d > 32768 || d > pos || pos > n || ch > n - pos {
        return false;
    }
    let v = q9_match_len(input, pos - d, pos, ch);
    v >= ch
}

pub fn q9_emit_all(input: &[u8], out: &mut [u32], plan: &[u32]) -> usize {
    let n = input.len();
    let mut k = 0usize;
    let mut ntok = 0usize;
    while k < n {
        let p = q9_get(plan, k) as usize;
        let ch = p / 65536;
        let d = p % 65536;
        if q9_verified(input, k, d, ch) {
            out[ntok] = 16777216u32 + ((d - 1) as u32) * 256 + ((ch - 3) as u32);
            ntok += 1;
            k += ch;
        } else {
            out[ntok] = input[k] as u32;
            ntok += 1;
            k += 1;
        }
    }
    ntok
}

pub fn q9_le64(input: &[u8], p: usize) -> u64 {
    let n = input.len();
    if p < n && n - p >= 8 {
        let b7 = input[p + 7] as u64;
        let lo = (input[p] as u32) | ((input[p + 1] as u32) << 8) | ((input[p + 2] as u32) << 16) | ((input[p + 3] as u32) << 24);
        let hi = (input[p + 4] as u32) | ((input[p + 5] as u32) << 8) | ((input[p + 6] as u32) << 16) | ((b7 as u32) << 24);
        (lo as u64) | ((hi as u64) << 32)
    } else {
        0
    }
}

pub fn q9_first_diff(x: u64, y: u64) -> usize {
    let z = x ^ y;
    let low = z & (!z).wrapping_add(1);
    let bit = 63u32.wrapping_sub(low.leading_zeros());
    let b = (bit / 8) as usize;
    if b > 7 {
        7
    } else {
        b
    }
}

pub fn q9_dslot(d: usize) -> usize {
    let small = if d >= 1 { d.wrapping_sub(1) } else { 0 };
    let x = (d.wrapping_sub(1) % 65536) as u32;
    let msb = 31u32.wrapping_sub(x.leading_zeros());
    let sh = if msb >= 1 && msb <= 31 { msb.wrapping_sub(1) } else { 0 };
    let s = (2u32.wrapping_mul(msb % 32).wrapping_add((x >> (sh % 32)) & 1)) as usize;
    let big = if s > 29 { 29 } else { s };
    if d <= 4 {
        small
    } else {
        big
    }
}

pub fn q9_dextra(s: usize) -> u32 {
    if s < 4 {
        0
    } else {
        ((s / 2).wrapping_sub(1)) as u32
    }
}

pub fn q9_lcode(l: usize) -> usize {
    let small = if l >= 3 { l.wrapping_sub(3) } else { 0 };
    let x = (l.wrapping_sub(3) % 1024) as u32;
    let msb = 31u32.wrapping_sub(x.leading_zeros());
    let sh = if msb >= 2 && msb <= 31 { msb.wrapping_sub(2) } else { 0 };
    let m = if msb >= 1 && msb <= 31 { msb.wrapping_sub(1) } else { 0 };
    let c = (4u32.wrapping_mul(m).wrapping_add((x >> (sh % 32)) & 3)) as usize;
    let big = if c > 28 { 28 } else { c };
    if l < 11 {
        small
    } else if l >= 258 {
        28
    } else {
        big
    }
}

pub fn q9_lextra(c: usize) -> u32 {
    if c < 8 || c >= 28 {
        0
    } else {
        ((c.wrapping_sub(4)) / 4) as u32
    }
}

pub fn q9_fixed_len(s: usize) -> u32 {
    if s < 144 {
        8
    } else if s < 256 {
        9
    } else if s < 280 {
        7
    } else {
        8
    }
}

pub fn q9_ext_len(input: &[u8], a: usize, b: usize, from: usize, cap: usize) -> usize {
    let n = input.len();
    let bad = if a >= b || b >= n || cap > n.wrapping_sub(b) { 1usize } else { 0usize };
    let lim = if bad == 1 { 0 } else { cap };
    let mut l = from;
    let mut it = 0usize;
    while it < 300 && l < lim {
        if lim - l >= 8 {
            let x = q9_le64(input, a.wrapping_add(l));
            let y = q9_le64(input, b.wrapping_add(l));
            if x == y {
                l = l.wrapping_add(8);
            } else {
                l = l.wrapping_add(q9_first_diff(x, y));
                break;
            }
        } else if q9_byte_at(input, a.wrapping_add(l)) == q9_byte_at(input, b.wrapping_add(l)) {
            l = l.wrapping_add(1);
        } else {
            break;
        }
        it += 1;
    }
    let lb = if from > cap { cap } else { from };
    let lg = if l > cap { cap } else { l };
    if bad == 1 {
        lb
    } else {
        lg
    }
}

pub fn q9_clear(v: &mut [u32], a: usize, b: usize) {
    let mut i = a;
    while i < b {
        q9_set(v, i, 0);
        i += 1;
    }
}

pub fn q9_walk_bump(fr: &mut [u32], off: usize, st: usize, d: usize, b: usize) {
    if st >= 3 {
        let lc = q9_lcode(st);
        let s = q9_dslot(d);
        q9_bump(fr, off.wrapping_add(257).wrapping_add(lc), 1);
        q9_bump(fr, off.wrapping_add(288).wrapping_add(s), 1);
        q9_bump(fr, off.wrapping_add(318), q9_lextra(lc).wrapping_add(q9_dextra(s)));
        q9_bump(fr, off.wrapping_add(319), st as u32);
    } else {
        q9_bump(fr, off.wrapping_add(b), 1);
        q9_bump(fr, off.wrapping_add(319), 1);
    }
}

pub fn q9_insert_sorted(order: &mut [u32], k: usize, s: usize, freq: &[u32], off: usize) {
    let fs = q9_get(freq, off.wrapping_add(s));
    let mut j = k;
    while j > 0 {
        let o = q9_get(order, j - 1) as usize;
        let fo = q9_get(freq, off.wrapping_add(o));
        if fo <= fs {
            break;
        }
        q9_set(order, j, o as u32);
        j -= 1;
    }
    q9_set(order, j, s as u32);
}

pub fn q9_radix_pass(freq: &[u32], off: usize, src: &[u32], dst: &mut [u32], k: usize, sh: u32) {
    let mut cnt = [0u32; 256];
    let mut i = 0usize;
    while i < k && i < 288 {
        let f = q9_get(freq, off.wrapping_add(q9_get(src, i) as usize));
        let dg = ((f >> (sh % 32)) % 256) as usize;
        cnt[dg] = cnt[dg].wrapping_add(1);
        i += 1;
    }
    let mut acc = 0u32;
    let mut d = 0usize;
    while d < 256 {
        let c = cnt[d];
        cnt[d] = acc;
        acc = acc.wrapping_add(c);
        d += 1;
    }
    let mut j = 0usize;
    while j < k && j < 288 {
        let s = q9_get(src, j);
        let f = q9_get(freq, off.wrapping_add(s as usize));
        let dg = ((f >> (sh % 32)) % 256) as usize;
        q9_set(dst, cnt[dg] as usize, s);
        cnt[dg] = cnt[dg].wrapping_add(1);
        j += 1;
    }
}

pub fn q9_sort_live(freq: &[u32], off: usize, nsym: usize, order: &mut [u32]) -> usize {
    let mut tmp = [0u32; 288];
    let mut k = 0usize;
    let mut big = 0usize;
    let mut s = 0usize;
    while s < nsym && s < 288 {
        let f = q9_get(freq, off.wrapping_add(s));
        let old = tmp[k % 288];
        let live = q9_lt32(0, f);
        tmp[k % 288] = q9_sel32(live, s as u32, old);
        k = k.wrapping_add(live);
        big = big | q9_lt32(65535, f);
        s += 1;
    }
    let kr = q9_sel(big, 0, k);
    q9_radix_pass(freq, off, &tmp, order, kr, 0);
    q9_copy32(order, 0, &mut tmp, 0, kr);
    q9_radix_pass(freq, off, &tmp, order, kr, 8);
    let kb = q9_sel(big, k, 0);
    let mut j = 0usize;
    while j < kb && j < 288 {
        q9_insert_sorted(order, j, tmp[j % 288] as usize, freq, off);
        j += 1;
    }
    k
}

pub fn q9_run_len(all: &[u32], i: usize, m: usize) -> usize {
    let v = q9_get(all, i);
    let mut r = 1usize;
    while r < 1000 {
        let j = i.wrapping_add(r);
        if j >= m {
            break;
        }
        if q9_get(all, j) != v {
            break;
        }
        r += 1;
    }
    r
}

pub fn q9_rle_stats(all: &[u32], m: usize, clf: &mut [u32]) -> u64 {
    let mut extra = 0u64;
    let mut i = 0usize;
    while i < m {
        let v = q9_get(all, i) as usize;
        let run = q9_run_len(all, i, m);
        let q0 = run / 138;
        let r0 = run % 138;
        let rest = run.wrapping_sub(1);
        let q1 = rest / 6;
        let r1 = rest % 6;
        let e18 = if r0 >= 11 { 1usize } else { 0usize };
        let e16 = if r1 >= 3 { 1usize } else { 0usize };
        let add18 = if v == 0 { q0.wrapping_add(e18) } else { 0 };
        let add17 = if v == 0 && r0 >= 3 && r0 < 11 { 1usize } else { 0usize };
        let add0 = if v == 0 && r0 < 3 { r0 } else { 0 };
        let add16 = if v == 0 { 0 } else { q1.wrapping_add(e16) };
        let addv = if v == 0 { 0 } else if r1 < 3 { r1.wrapping_add(1) } else { 1 };
        q9_bump(clf, 18, add18 as u32);
        q9_bump(clf, 17, add17 as u32);
        q9_bump(clf, 0, add0 as u32);
        q9_bump(clf, 16, add16 as u32);
        q9_bump(clf, v % 19, addv as u32);
        let ex = add18.wrapping_mul(7).wrapping_add(add17.wrapping_mul(3)).wrapping_add(add16.wrapping_mul(2));
        extra = extra.wrapping_add(ex as u64);
        let st = q9_clamp1(run, m - i);
        i += st;
    }
    extra
}

pub fn q9_dot(f: &[u32], foff: usize, l: &[u32], loff: usize, m: usize) -> u64 {
    let mut s = 0u64;
    let mut i = 0usize;
    while i < m {
        s = s.wrapping_add((q9_get(f, foff.wrapping_add(i)) as u64).wrapping_mul(q9_get(l, loff.wrapping_add(i)) as u64));
        i += 1;
    }
    s
}

pub fn q9_fixed_dot(f: &[u32], foff: usize) -> u64 {
    let mut s = 0u64;
    let mut i = 0usize;
    while i < 288 {
        s = s.wrapping_add((q9_get(f, foff.wrapping_add(i)) as u64).wrapping_mul(q9_fixed_len(i) as u64));
        i += 1;
    }
    s
}

pub fn q9_sum_range(f: &[u32], a: usize, b: usize) -> u64 {
    let mut s = 0u64;
    let mut i = a;
    while i < b {
        s = s.wrapping_add(q9_get(f, i) as u64);
        i += 1;
    }
    s
}

pub fn q9_last_nz(l: &[u32], off: usize, m: usize, lo: usize) -> usize {
    let mut k = m;
    while k > lo {
        if q9_get(l, off.wrapping_add(k - 1)) != 0 {
            break;
        }
        k -= 1;
    }
    k
}

pub fn q9_copy32(src: &[u32], soff: usize, dst: &mut [u32], doff: usize, m: usize) {
    let mut i = 0usize;
    while i < m {
        q9_set(dst, doff.wrapping_add(i), q9_get(src, soff.wrapping_add(i)));
        i += 1;
    }
}

pub fn q9_hclen_of(cl: &[u32]) -> usize {
    let mut h = 19usize;
    while h > 4 {
        if q9_get(cl, Q9_CL_ORDER[(h - 1) % 19]) != 0 {
            break;
        }
        h -= 1;
    }
    h
}

pub fn q9_block_bits(fr: &mut [u32], off: usize, lens: &mut [u32]) -> u64 {
    q9_bump(fr, off.wrapping_add(256), 1);
    q9_pkg_merge(fr, off, 288, 15, lens, 0);
    q9_pkg_merge(fr, off.wrapping_add(288), 30, 15, lens, 288);
    let ndist = q9_sum_range(fr, off.wrapping_add(288), off.wrapping_add(318));
    let l288 = q9_get(lens, 288);
    q9_set(lens, 288, q9_sel32(q9_lt64(ndist, 1), 1, l288));
    let hlit = q9_last_nz(lens, 0, 288, 257);
    let hdist = q9_last_nz(lens, 288, 30, 1);
    let mut all = [0u32; 320];
    q9_copy32(lens, 0, &mut all, 0, hlit);
    q9_copy32(lens, 288, &mut all, hlit, hdist);
    let mut clf = [0u32; 19];
    let rextra = q9_rle_stats(&all, hlit.wrapping_add(hdist), &mut clf);
    let mut cl = [0u32; 19];
    q9_pkg_merge(&clf, 0, 19, 7, &mut cl, 0);
    let hclen = q9_hclen_of(&cl);
    let ex = q9_get(fr, off.wrapping_add(318)) as u64;
    let hdr = 17u64.wrapping_add(3u64.wrapping_mul(hclen as u64)).wrapping_add(q9_dot(&clf, 0, &cl, 0, 19)).wrapping_add(rextra);
    let dl = q9_dot(fr, off, lens, 0, 288);
    let dd = q9_dot(fr, off.wrapping_add(288), lens, 288, 30);
    let dynb = hdr.wrapping_add(dl).wrapping_add(dd).wrapping_add(ex);
    let fixb = 3u64.wrapping_add(q9_fixed_dot(fr, off)).wrapping_add(5u64.wrapping_mul(ndist)).wrapping_add(ex);
    q9_bump(fr, off.wrapping_add(256), 0u32.wrapping_sub(1));
    let raw = q9_get(fr, off.wrapping_add(319)) as u64;
    let stb = 35u64.wrapping_add(8u64.wrapping_mul(raw));
    let fx = q9_lt64(dynb, fixb) ^ 1;
    let best = q9_sel64(fx, fixb, dynb);
    let usest = q9_lt64(ndist, 1) & q9_lt64(raw, 65536) & q9_lt64(stb, best);
    q9_sel64(usest, stb.wrapping_mul(4).wrapping_add(2), best.wrapping_mul(4).wrapping_add(fx as u64))
}

pub fn q9_log2x16(x: u64) -> u32 {
    if x == 0 {
        return 0;
    }
    let k = 63u32.wrapping_sub(x.leading_zeros()) % 64;
    let y = x << ((63 - k) % 64);
    let m = ((y >> 58) as usize) % 32;
    k.wrapping_mul(16).wrapping_add(Q9_LOG2F[m])
}

pub fn q9_sym_costs(fr: &[u32], off: usize, lens: &[u32], kind: u32, sc: &mut [u32]) {
    let tl = q9_sum_range(fr, off, off.wrapping_add(286)).wrapping_add(1);
    let td = q9_sum_range(fr, off.wrapping_add(288), off.wrapping_add(318));
    let lt = q9_log2x16(tl);
    let ld = q9_log2x16(td);
    let mut s = 0usize;
    while s < 318 {
        let f = q9_get(fr, off.wrapping_add(s)) as u64;
        let ls = q9_get(lens, s);
        let fl = q9_fixed_len(s);
        let lf = q9_log2x16(f);
        let hl = if kind == 1 {
            if s >= 288 {
                5
            } else {
                fl
            }
        } else if kind == 2 && s < 256 {
            8
        } else if ls > 0 {
            ls
        } else {
            Q9_UNUSED
        };
        let tot = if s >= 288 { ld } else { lt };
        let e0 = if f > 0 { tot.saturating_sub(lf) } else { tot.saturating_add(Q9_UPEN) };
        let e = if e0 < 16 { 16 } else { e0 };
        let hc = hl.wrapping_mul(Q9_SC);
        let mixv = (e.wrapping_mul(Q9_EW).wrapping_add(hc.wrapping_mul(8 - Q9_EW))) / 8;
        q9_set(sc, s, if kind != 0 { hc } else { mixv });
        s += 1;
    }
}

pub fn q9_blend(old: u32, new: u32, damp: u32) -> u32 {
    if damp == 0 {
        new
    } else if Q9_OV > 0 {
        let dlt = if new >= old { new.wrapping_sub(old) } else { old.wrapping_sub(new) };
        let adj = ((dlt as u64).wrapping_mul(Q9_OV as u64) / 8) as u32;
        let v = if new >= old { new.saturating_add(adj) } else { new.saturating_sub(adj) };
        if v < 16 {
            16
        } else {
            v
        }
    } else {
        (((old as u64).wrapping_mul(Q9_DW as u64).wrapping_add((new as u64).wrapping_mul((8 - Q9_DW) as u64))) / 8) as u32
    }
}

pub fn q9_fill_table(sc: &[u32], tbl: &mut [u32], toff: usize, damp: u32) {
    let mut c = 0usize;
    while c < 256 {
        let j = toff.wrapping_add(c);
        q9_set(tbl, j, q9_blend(q9_get(tbl, j), q9_get(sc, c), damp));
        c += 1;
    }
    let mut len = 0usize;
    while len < 259 {
        let lc = q9_lcode(len);
        let v = q9_get(sc, lc.wrapping_add(257)).wrapping_add(q9_lextra(lc).wrapping_mul(Q9_SC));
        let j = toff.wrapping_add(256).wrapping_add(len);
        q9_set(tbl, j, q9_blend(q9_get(tbl, j), v, damp));
        len += 1;
    }
    let mut s = 0usize;
    while s < 30 {
        let v = q9_get(sc, s.wrapping_add(288)).wrapping_add(q9_dextra(s).wrapping_mul(Q9_SC));
        let j = toff.wrapping_add(515).wrapping_add(s);
        q9_set(tbl, j, q9_blend(q9_get(tbl, j), v, damp));
        s += 1;
    }
}

pub fn q9_pkg_merge(freq:&[u32],off:usize,nsym:usize,maxbits:usize,lens:&mut [u32],loff:usize) {
    let mut order=[0u32;288];
    let k=q9_sort_live(freq,off,nsym,&mut order);
    let mut weights=[0u64;576];
    let mut parent=[0u32;576];
    let mut depth=[0u32;576];
    let mut i=0usize;
    while i<k && i<288 {weights[i]=q9_get(freq,off.wrapping_add(order[i] as usize)) as u64;i+=1;}
    let mut leaf=0usize;
    let mut pair=k;
    let mut next=k;
    while next.wrapping_add(1)<k.wrapping_mul(2) && next<575 {
        let mut sum=0u64;
        let mut j=0usize;
        while j<2 {
            let lw=if leaf<k {weights[leaf%576]} else {18446744073709551615u64};
            let pw=if pair<next {weights[pair%576]} else {18446744073709551615u64};
            let take=q9_lt64(pw,lw)^1;
            let idx=q9_sel(take,leaf,pair);
            sum=sum.wrapping_add(weights[idx%576]);
            parent[idx%576]=next as u32;
            leaf=leaf.wrapping_add(take);
            pair=pair.wrapping_add(take^1);
            j+=1;
        }
        weights[next%576]=sum;
        next+=1;
    }
    let mut mx=0usize;
    let mut node=next.saturating_sub(1);
    while node>0 {
        node-=1;
        let d=depth[(parent[node%576] as usize)%576].wrapping_add(1);
        depth[node%576]=d;
        mx=q9_umax(mx,d as usize);
    }
    q9_clear(lens,loff,loff.wrapping_add(nsym));
    let mut r=0usize;
    while r<k && r<288 {
     let d=depth[r] as usize;let c=q9_umin(d,maxbits);
     q9_set(lens,loff.wrapping_add(order[r] as usize),if k==1 {1} else {c as u32});r+=1;
    }
}

pub fn q9_push_m(v: &mut Vec<u32>, f: usize, len: usize, d: usize) {
    if f == 1 && v.len() < Q9_PUSH_LIMIT {
        v.push(q9_pack_m(len, d));
    }
}

pub fn q9_pack_m(len: usize, d: usize) -> u32 {
    let l = (len % 1024) as u32;
    let dd = if d >= 1 && d <= 32768 { d } else { 1 };
    l.wrapping_mul(1048576).wrapping_add((q9_dslot(dd) as u32).wrapping_mul(32768)).wrapping_add((dd.wrapping_sub(1)) as u32)
}

pub fn q9_push_slot1(mc: &mut Vec<u32>, m0: usize, len: usize, d: usize) {
    let e = q9_pack_m(len, d);
    let k = mc.len();
    let last = q9_get(mc, k.wrapping_sub(1));
    let same = q9_eq(Q9_SLOTM, 1) & q9_lt(m0, k) & q9_eq(((last / 32768) % 32) as usize, ((e / 32768) % 32) as usize);
    if same == 1 {
        q9_set(mc, k.wrapping_sub(1), e);
    } else {
        q9_push_guarded(mc, e);
    }
}

pub fn q9_yeval(fr:&mut [u32],tbl:&mut [u32],nb:usize,damp:u32)->u64 {
    let mut lens=[0u32;320];let mut sc=[0u32;320];
    let mut b=0usize;let mut total=0u64;
    while b<nb {
        let off=b.wrapping_mul(Q9_FB);
        let r=q9_block_bits(fr,off,&mut lens);
        total=total.wrapping_add(r/4);
        q9_sym_costs(fr,off,&lens,(r%4) as u32,&mut sc);
        q9_fill_table(&sc,tbl,b.wrapping_mul(Q9_TB),damp);
        let raw=q9_get(fr,off.wrapping_add(319)) as u64;
        let fl=if raw.wrapping_mul(8).wrapping_add(35)<r/4 {1} else {q9_get(tbl,b.wrapping_mul(Q9_TB).wrapping_add(545))};
        q9_set(tbl,b.wrapping_mul(Q9_TB).wrapping_add(545),fl);
        if fl==1 {
            let mut j=0usize;
            while j<289 {q9_set(tbl,b.wrapping_mul(Q9_TB).wrapping_add(256).wrapping_add(j),1048576);j+=1;}
        }
        b+=1;
    }
    total
}

pub fn q9_hpref(input:&[u8])->Vec<u32> {
 let mut v:Vec<u32>=Vec::with_capacity((input.len()/1024).wrapping_add(1).wrapping_mul(256));let mut h=[0u32;256];let mut p=0usize;
 while p<input.len() {
  if p%1024==0 {let mut b=0usize;while b<256 {q9_push_guarded(&mut v,h[b]);b+=1;}}
  let b=q9_byte_at(input,p)%256;h[b]=h[b].wrapping_add(1);p+=1;
 }
 if input.len()%1024==0 {let mut b=0usize;while b<256 {q9_push_guarded(&mut v,h[b]);b+=1;}}
 v
}

pub fn q9_addhist(input:&[u8],hist:&[u32],fr:&mut [u32],off:usize,lo:usize,hi:usize) {
 let a=lo.wrapping_add(1023)/1024;let b=hi/1024;
 if a<b {
  let mut c=0usize;
  while c<256 {q9_bump(fr,off.wrapping_add(c),q9_get(hist,b.wrapping_mul(256).wrapping_add(c)).wrapping_sub(q9_get(hist,a.wrapping_mul(256).wrapping_add(c))));c+=1;}
  let mut p=lo;let end=a.wrapping_mul(1024);
  while p<end {q9_bump(fr,off.wrapping_add(q9_byte_at(input,p)),1);p+=1;}
  let mut p=b.wrapping_mul(1024);
  while p<hi {q9_bump(fr,off.wrapping_add(q9_byte_at(input,p)),1);p+=1;}
 } else {
  let mut p=lo;
  while p<hi {q9_bump(fr,off.wrapping_add(q9_byte_at(input,p)),1);p+=1;}
 }
}

pub fn q9_ywalk(input:&[u8],plan:&[u32],ev:&[u32],hist:&[u32],fr:&mut [u32],bpos:&mut [u32])->usize {
 let n=input.len();let mut pos=0usize;let mut b=0usize;let mut t=0usize;let mut ei=0usize;let mut start=0usize;let fuel=ev.len().wrapping_add(n/Q9_BT).wrapping_add(2).wrapping_mul(3);let mut it=0usize;
 q9_clear(fr,0,Q9_FB);q9_set(bpos,0,0);
 while it<fuel && pos<n {
  let p=if ei<ev.len() {q9_get(ev,ei) as usize} else {n};
  let m=q9_get(plan,ei) as usize;let l=q9_clamp_step(m/65536,n.saturating_sub(p));let d=m%65536;
  if p<pos || l<3 || d==0 || p>=n {
   if ei<ev.len() {ei=ei.wrapping_add(1);} else {
    let gap=q9_umin(n.saturating_sub(pos),Q9_BT.saturating_sub(t));pos=pos.wrapping_add(gap);t=t.wrapping_add(gap);
   }
  } else if pos<p {
   let gap=q9_umin(p.saturating_sub(pos),Q9_BT.saturating_sub(t));pos=pos.wrapping_add(gap);t=t.wrapping_add(gap);
  } else {
   let mut j=0usize;
   while j<l && j<258 {q9_bump(fr,b.wrapping_mul(Q9_FB).wrapping_add(q9_byte_at(input,pos.wrapping_add(j))),0u32.wrapping_sub(1));j+=1;}
   q9_walk_bump(fr,b.wrapping_mul(Q9_FB),l,d,0);
   pos=pos.wrapping_add(l);t=t.wrapping_add(1);ei=ei.wrapping_add(1);
  }
  if t>=Q9_BT || pos>=n {
   q9_addhist(input,hist,fr,b.wrapping_mul(Q9_FB),start,pos);
   q9_set(fr,b.wrapping_mul(Q9_FB).wrapping_add(319),pos.wrapping_sub(start) as u32);
   start=pos;
   if pos<n {t=0;b=b.wrapping_add(1);q9_clear(fr,b.wrapping_mul(Q9_FB),b.wrapping_add(1).wrapping_mul(Q9_FB));q9_set(bpos,b,pos as u32);}
  }
  it+=1;
 }
 b.wrapping_add(1)
}

pub fn q9_word4(input:&[u8],p:usize)->u32 {
 let n=input.len();
 if p<n && n-p>=4 {(input[p] as u32)|((input[p+1] as u32)<<8)|((input[p+2] as u32)<<16)|((input[p+3] as u32)<<24)} else {0}
}

pub fn q9_lprefix(input:&[u8],ep:&[u32],ms:&[u32],mc:&[u32],tbl:&[u32],bp:&[u32],nb:usize,pref:&mut [u32],lam:u32) {
 let mut ei=0usize;let mut p=0usize;let mut b=0usize;let mut val=0u32;
 while ei<ep.len() {
  let start=q9_get(ep,ei) as usize;let en=q9_get(ms,ei.wrapping_add(1)) as usize;
  let ml=q9_umin(258,((q9_get(mc,en.wrapping_sub(1)) as usize)/1048576)%512);
  let end=start.wrapping_add(ml);
  if p<start {p=start;q9_set(pref,p,val);}
  while p<end {
   while b<nb.saturating_sub(1) && (q9_get(bp,b.wrapping_add(1)) as usize)<=p {b+=1;}
   val=val.wrapping_add(q9_get(tbl,b.wrapping_mul(Q9_TB).wrapping_add(q9_byte_at(input,p))).saturating_sub(lam));
   p+=1;q9_set(pref,p,val);
  }
  ei+=1;
 }
}

pub fn q9_bwalk(input:&[u8],child:&mut [u32;65536],start:usize,p:usize,cap:usize,best0:usize,budget:usize,mc:&mut Vec<u32>,m0:usize) {
 let mut plt=(p%32768)*2;let mut pgt=plt+1;let mut cur=start;let mut low=4usize;let mut high=4usize;let mut best=best0;let mut it=0usize;let mut done=0usize;
 while it<budget && cur>0 && cur<=p && p-(cur-1)<32768 {
  let c=cur-1;let l=q9_ext_len(input,c,p,q9_umin(low,high),cap);
  if l>best {q9_push_slot1(mc,m0,l,p-c);best=l;}
  let cs=(c%32768)*2;let c0=child[cs];let c1=child[cs+1];
  if l>=cap {
   child[plt%65536]=c0;child[pgt%65536]=c1;done=1;cur=0;
  } else {
   let sm=if q9_byte_at(input,c.wrapping_add(l))<q9_byte_at(input,p.wrapping_add(l)) {1usize} else {0};
   let dst=if sm==1 {plt} else {pgt};child[dst%65536]=cur as u32;
   let nx=cs.wrapping_add(sm);
   plt=if sm==1 {nx} else {plt};pgt=if sm==1 {pgt} else {nx};
   low=if sm==1 {l} else {low};high=if sm==1 {high} else {l};
   cur=if sm==1 {c1 as usize} else {c0 as usize};
  }
  it+=1;
 }
 if done==0 {child[plt%65536]=0;child[pgt%65536]=0;}
}

#[inline(always)]
pub fn q9_cache3(h3:&mut [u64;65536],k:usize,w4:u32,w3:u32,p:usize)->usize {
 let a=k%65536;let b=k.wrapping_add(1)%65536;let old=h3[a];let old2=h3[b];
 let hit=((old>>32) as u32)&16777215==w3 && old as u32>0;
 let c=if hit {(old as u32) as usize} else if ((old2>>32) as u32)&16777215==w3 {(old2 as u32) as usize} else {0};
 let tag=((w4 as u64)<<32)|((p as u32).wrapping_add(1) as u64);
 if !hit {h3[b]=old;}h3[a]=tag;c
}

pub fn q9_near_tag(input:&[u8],p:usize,c:usize,cap:usize)->usize {
 if c>0 && c<=p && p-(c-1)<=32768 && cap>=3 {q9_ext_len(input,c-1,p,0,q9_umin(cap,8))} else {0}
}

#[inline(always)]
pub fn q9_cache4(h4:&mut [u64;Q9_Y_PAIR4SIZE],k:usize,w:u32,p:usize)->usize {
 let a=k%Q9_Y_PAIR4SIZE;let b=k.wrapping_add(1)%Q9_Y_PAIR4SIZE;let old=h4[a];let old2=h4[b];
 let hit=(old>>32) as u32==w && old as u32>0;
 let c=if hit {(old as u32) as usize} else if (old2>>32) as u32==w {(old2 as u32) as usize} else {0};
 let tag=((w as u64)<<32)|((p as u32).wrapping_add(1) as u64);
 if !hit {h4[b]=old;}h4[a]=tag;c
}

pub fn q9_hfind(input:&[u8],ep:&mut Vec<u32>,ms:&mut Vec<u32>,mc:&mut Vec<u32>,depth:usize) {
 let mut h4=[0u64;Q9_Y_PAIR4SIZE];let mut h3=[0u64;65536];let mut child=[0u32;65536];let mut p=0usize;
 let n=input.len();
 while p<n {
  let w4=q9_word4(input,p);let w3=w4&16777215;
  let k3=(((w3.wrapping_mul(2654435761)>>Q9_Y_H3SHIFT) as usize).wrapping_mul(Q9_Y_WAYS))%65536;
  let c3=q9_cache3(&mut h3,k3,w4,w3,p);
  let cap=q9_umin(n-p,258);let m0=mc.len();
  let l3=q9_near_tag(input,p,c3,cap);
  q9_push_m(mc,if l3>=3 {1} else {0},l3,p.wrapping_sub(c3.wrapping_sub(1)));
  let k4=((w4.wrapping_mul(2654435761)>>Q9_Y_PAIR4SHIFT) as usize).wrapping_mul(2)%Q9_Y_PAIR4SIZE;
  let cur=q9_cache4(&mut h4,k4,w4,p);
  let old4=((w4 as u64)<<32)|(cur as u64);
  if (old4>>32) as u32==w4 && cur>0 && cur<=p && p-(cur-1)<32768 && cap>=4 {
   q9_bwalk(input,&mut child,cur,p,cap,q9_umax(l3,3),depth,mc,m0);
  } else {
   child[(p%32768)*2]=0;child[(p%32768)*2+1]=0;
  }
  if mc.len()>m0 {q9_push_guarded(ep,p as u32);q9_push_guarded(ms,m0 as u32);}
  p+=1;
 }
 q9_push_guarded(ms,mc.len() as u32);
}

pub fn q9_sfill(dp:&mut [u32;512],p:usize,next:usize,ml:usize,last:u32) {
 if ml==3 {
  if p.wrapping_add(1)<next {dp[p.wrapping_add(1)%512]=last;}
  if p.wrapping_add(2)<next {dp[p.wrapping_add(2)%512]=last;}
  if p.wrapping_add(3)<next {dp[p.wrapping_add(3)%512]=last;}
 } else {
  let mut j=1usize;while j<=ml && j<259 && p.wrapping_add(j)<next {dp[p.wrapping_add(j)%512]=last;j+=1;}
 }
}

pub fn q9_sload(tbl:&[u32],off:usize,prices:&mut [u32;289]) {
 let mut j=0usize;while j<289 {prices[j]=q9_get(tbl,off.wrapping_add(256).wrapping_add(j));j+=1;}
}

pub fn q9_spick(dp:&[u32;512],mc:&[u32],pref:&[u32],prices:&[u32;289],p:usize,st:usize,en:usize,ml:usize,last:u32,lam:u32)->u64 {
 let mut best=(last as u64)<<32;
 if ml==3 && en==st.wrapping_add(1) {
  let m=q9_get(mc,st) as usize;let ds=(m/32768)%32;let d=m%32768+1;
  let lit=q9_get(pref,p.wrapping_add(3)).wrapping_sub(q9_get(pref,p));
  let price=prices[3].wrapping_add(prices[(259+ds)%289].saturating_sub(lam));
  let saving=dp[p.wrapping_add(3)%512].wrapping_add(lit).saturating_sub(price);
  if saving>last {best=((saving as u64)<<32)|(3u64<<16)|(d as u64);}
 } else {
  let mut mi=en;let mut mind=1048576u32;let mut choose_d=1usize;
  while mi>st {
   mi-=1;let m=q9_get(mc,mi) as usize;let l=(m/1048576)%512;let ds=(m/32768)%32;let d=m%32768+1;
   let dc0=prices[(259+ds)%289].saturating_sub(lam);
   if dc0<=mind {mind=dc0;choose_d=d;}let dc=mind;
   let prev=if mi>st {((q9_get(mc,mi-1) as usize)/1048576)%512} else {2};
   let mut k=q9_umax(prev.wrapping_add(1),if l>16 {l-16} else {3});
   while k<=l && k<259 {
    let lit=q9_get(pref,p.wrapping_add(k)).wrapping_sub(q9_get(pref,p));
    let price=prices[k%289].wrapping_add(dc);
    let saving=dp[p.wrapping_add(k)%512].wrapping_add(lit).saturating_sub(price);
    if saving>(best>>32) as u32 {best=((saving as u64)<<32)|((k as u64)<<16)|(choose_d as u64);}
    k+=1;
   }
  }
 }
 best
}

pub fn q9_sedp(input:&[u8],ep:&[u32],ms:&[u32],mc:&[u32],tbl:&[u32],bp:&[u32],nb:usize,pref:&mut [u32],plan:&mut [u32],lam:u32) {
 q9_lprefix(input,ep,ms,mc,tbl,bp,nb,pref,lam);
 let mut dp=[0u32;512];let mut e=ep.len();let mut next=input.len();let mut last=0u32;let mut b=nb.saturating_sub(1);let mut lastb=4294967295usize;let mut prices=[0u32;289];
 while e>0 {
  e-=1;let p=q9_get(ep,e) as usize;
  let st=q9_get(ms,e) as usize;let en=q9_get(ms,e.wrapping_add(1)) as usize;
  let ml=q9_umin(258,(q9_get(mc,en.wrapping_sub(1))/1048576) as usize);
  q9_sfill(&mut dp,p,next,ml,last);
  while b>0 && p<(q9_get(bp,b) as usize) {b-=1;}
  let off=b.wrapping_mul(Q9_TB);
  if b!=lastb {q9_sload(tbl,off,&mut prices);lastb=b;}
  let best=q9_spick(&dp,mc,pref,&prices,p,st,en,ml,last,lam);
  last=(best>>32) as u32;dp[p%512]=last;q9_set(plan,e,best as u32);next=p;
 }
}

pub fn q9_hseed(ep:&[u32],ms:&[u32],mc:&[u32],plan:&mut [u32]) {
 let mut e=0usize;let mut pos=0usize;
 while e<ep.len() {
  let p=q9_get(ep,e) as usize;let st=q9_get(ms,e) as usize;let en=q9_get(ms,e.wrapping_add(1)) as usize;
  let m=q9_get(mc,en.wrapping_sub(1)) as usize;let l=(m/1048576)%512;
  let ne=q9_get(ep,e.wrapping_add(1)) as usize;
  let nm=q9_get(mc,(q9_get(ms,e.wrapping_add(2)) as usize).wrapping_sub(1)) as usize;
  let lazy=ne==p.wrapping_add(1) && (nm/1048576)%512>l && e.wrapping_add(1)<ep.len();
  let mut mi=st;let mut best=0u32;let mut ch=0u32;
  while mi<en {
   let m=q9_get(mc,mi) as usize;let l=(m/1048576)%512;let ds=(m/32768)%32;let d=m%32768+1;
   let cost=Q9_Y_SEEDBASE.wrapping_add(q9_lextra(q9_lcode(l))).wrapping_add(q9_dextra(ds)).wrapping_mul(16);
   let saving=(l as u32).wrapping_mul(128).saturating_sub(cost);
   if saving>best && l>=3 {best=saving;ch=(l as u32).wrapping_mul(65536).wrapping_add(d as u32);}
   mi+=1;
  }
  if p>=pos && !lazy && ch!=0 {q9_set(plan,e,ch);pos=p.wrapping_add((ch/65536) as usize);}
  e+=1;
 }
}

pub fn q9_hplan(input:&[u8],plan:&mut [u32]) {
 let n=input.len();let nbmax=n/Q9_BT+2;
 let mut ep:Vec<u32>=Vec::with_capacity(n/6+1);let mut ms:Vec<u32>=Vec::with_capacity(n/6+1);let mut mc:Vec<u32>=Vec::with_capacity(n/3+1);
 q9_hfind(input,&mut ep,&mut ms,&mut mc,32);
 let hist=q9_hpref(input);let mut pref=q9_filled(n.wrapping_add(1),0);
 let mut tbl=q9_filled(nbmax.wrapping_mul(Q9_TB),0);let mut fr=q9_filled(nbmax.wrapping_mul(Q9_FB),0);let mut bp=q9_filled(nbmax,0);let mut cand=q9_filled(ep.len(),0);let mut kept=q9_filled(ep.len(),0);
 let mut best=18446744073709551615u64;
 q9_hseed(&ep,&ms,&mc,&mut cand);
 let mut nb=q9_ywalk(input,&cand,&ep,&hist,&mut fr,&mut bp);let seedscore=q9_yeval(&mut fr,&mut tbl,nb,0);
 q9_copy32(&cand,0,&mut kept,0,ep.len());best=seedscore;let mut it=0usize;
 while it<Q9_Y_ITERS {
  q9_sedp(input,&ep,&ms,&mc,&tbl,&bp,nb,&mut pref,&mut cand,5);
  nb=q9_ywalk(input,&cand,&ep,&hist,&mut fr,&mut bp);
  let score=q9_yeval(&mut fr,&mut tbl,nb,if it==0 {0} else {1});
  if score<best {q9_copy32(&cand,0,&mut kept,0,ep.len());best=score;}it+=1;
 }
 let mut e=0usize;while e<ep.len() {q9_set(plan,q9_get(&ep,e) as usize,q9_get(&kept,e));e+=1;}
}

pub fn q9_gkey(input:&[u8],p:usize)->usize {
 let w=q9_le64(input,p);
 let a=(w>>1)&0x0303030303030303u64;
 let b=(a|(a>>6))&0x000f000f000f000fu64;
 let c=(b|(b>>12))&0x000000ff000000ffu64;
 ((c|(c>>24))&65535) as usize
}

pub fn q9_gwalk(input:&[u8],prev:&[u32;32768],p:usize,start:usize,cap:usize,inh:usize,depth:usize)->u32 {
 let il=inh/65536;let mut bl=if il>=4 {il-1} else {2};let mut bd=if il>=4 {inh%65536} else {0};
 let mut cur=start;let mut it=0usize;
 while it<depth && cur>0 && cur<=p && p-(cur-1)<=32768 {
  let c=cur-1;
  if bl<cap && q9_byte_at(input,c.wrapping_add(bl))==q9_byte_at(input,p.wrapping_add(bl)) {
   let l=q9_ext_len(input,c,p,0,cap);
   if l>bl {bl=l;bd=p-c;}
  }
  cur=if bl>=cap {0} else {prev[c%32768] as usize};it+=1;
 }
 if bd>0 && bl>=3 {(bl as u32).wrapping_mul(65536).wrapping_add(bd as u32)} else {0}
}

#[inline(never)]
pub fn q9_dcandidates(input:&[u8],cm:&mut [u32],cn:&mut [u32]) {
 let n=input.len();let mut h8=[0u32;65536];let mut pr8=[0u32;32768];let mut h6=[0u32;4096];let mut pr6=[0u32;32768];let mut hlo=[0u32;1024];let mut prlo=[0u32;32768];
 let mut p=0usize;let mut inherited=0usize;
 while p<n {
  let key=q9_gkey(input,p)%65536;let k6=key%4096;let c6=h6[k6] as usize;let cur=h8[key] as usize;
  pr8[p%32768]=cur as u32;h8[key]=(p as u32).wrapping_add(1);
  pr6[p%32768]=c6 as u32;h6[k6]=(p as u32).wrapping_add(1);
  let room=n-p;let cap=if room<258 {room} else {258};
  let lo=q9_byte_at(input,p)>=97;let lkey=key%1024;let lc=hlo[lkey] as usize;
  if lo {prlo[p%32768]=lc as u32;hlo[lkey]=(p as u32).wrapping_add(1);}
  let m=if lo {q9_gwalk(input,&prlo,p,lc,cap,inherited,16)} else {q9_gwalk(input,&pr8,p,cur,cap,inherited,16)};
  let near=q9_gwalk(input,&pr6,p,c6,cap,0,4);
  q9_set(cm,p,m);q9_set(cn,p,near);inherited=m as usize;p+=1;
 }
}

pub fn q9_dna_prices(input:&[u8],lit:&mut [u32;256],lc:&mut [u32;259],dc:&mut [u32;30]) {
 let mut f=[0u32;320];let mut lens=[0u32;320];let mut p=0usize;
 while p<input.len() {let b=q9_byte_at(input,p)%256;f[b]=f[b].wrapping_add(1);p+=1;}
 q9_pkg_merge(&f,0,256,15,&mut lens,0);
 let mut b=0usize;while b<256 {lit[b]=if lens[b]>0 {lens[b].wrapping_mul(16).wrapping_add(4)} else {160};b+=1;}
 let mut l=0usize;while l<259 {
  let c=q9_lcode(l);let bits:u32=if c==7 {4} else if c>=3 && c<=6 {7} else if c<3 {9} else if c<12 {9} else {11};
  lc[l]=bits.wrapping_add(q9_lextra(c)).wrapping_mul(16).wrapping_add(4);l+=1;
 }
 let mut d=0usize;while d<30 {let bits:u32=if d>=26 {3} else if d>=22 {4} else if d>=18 {5} else if d>=12 {6} else {8};dc[d]=bits.wrapping_add(q9_dextra(d)).wrapping_mul(16);d+=1;}
}

#[inline(always)]
pub fn q9_drelax(dp:&[u32;512],lc:&[u32;259],dc:&[u32;30],p:usize,m:u32,best0:u64)->u64 {
 let l=(m/65536) as usize;let d=(m%65536) as usize;let mut best=best0;let cost=dc[q9_dslot(d)%30];
 let mut k=if l>8 {l-8} else {3};
 while k<=l && k<259 {
  let price=dp[p.wrapping_add(k)%512].wrapping_add(lc[k]).wrapping_add(cost);
  let ch=((price as u64)<<32)|((k as u64)<<16)|(d as u64);if ch<best {best=ch;}k+=1;
 }
 best
}

pub fn q9_dplan(input:&[u8],plan:&mut [u32]) {
 let n=input.len();let mut cm=q9_filled(n,0);let mut cn=q9_filled(n,0);q9_dcandidates(input,&mut cm,&mut cn);
 let mut lit=[0u32;256];let mut lc=[0u32;259];let mut dc=[0u32;30];q9_dna_prices(input,&mut lit,&mut lc,&mut dc);
 let mut dp=[0u32;512];let mut p=n;
 while p>0 {
  p-=1;let v=dp[p.wrapping_add(1)%512].wrapping_add(lit[q9_byte_at(input,p)%256]);let mut best=(v as u64)<<32;
  let m=q9_get(&cm,p);if m>=196608 {best=q9_drelax(&dp,&lc,&dc,p,m,best);}
  let m=q9_get(&cn,p);if m>=196608 {best=q9_drelax(&dp,&lc,&dc,p,m,best);}
  dp[p%512]=(best>>32) as u32;q9_set(plan,p,best as u32);
 }
}

pub fn q9_quick_plan(input:&[u8],plan:&mut [u32]) {
 let n=input.len();let mut head=[0u64;16384];let mut p=0usize;let mut fuel=n;
 while p<n && fuel>0 {
  fuel-=1;let w=q9_word4(input,p);let k=((w.wrapping_mul(2654435761)>>18) as usize)%16384;
  let old=head[k];let tag=((w as u64)<<32)|((p as u32).wrapping_add(1) as u64);head[k]=tag;
  let c=(old as u32) as usize;
  let l=if (old>>32) as u32==w && c>0 && c<=p && p-(c-1)<=32768 && n-p>=4 {q9_ext_len(input,c-1,p,4,q9_umin(n-p,258))} else {0};
  if l>=4 && l<=258 && l<=n-p {q9_set(plan,p,(l as u32).wrapping_mul(65536).wrapping_add(p.wrapping_sub(c.wrapping_sub(1)) as u32));p+=l;} else {p+=1;}
 }
}

pub fn q9_mode(input:&[u8])->usize {
 let n=input.len();let mut fr=[0u32;256];let mut p=0usize;let mut i=0usize;let mut dna=0usize;
 let stride=q9_umax(1,n/1024);
 while i<1024 && p<n {
  let c=q9_byte_at(input,p)%256;fr[c]=fr[c].wrapping_add(1);let b=c|32;
  if b==97 || b==99 || b==103 || b==116 {dna=dna.wrapping_add(1);}
  i+=1;p=if n-p>stride {p+stride} else {n};
 }
 if dna.wrapping_mul(100)>i.wrapping_mul(90) && i>32 {return 1;}
 let mut live=0usize;let mut mx=0u32;let mut b=0usize;
 while b<256 {if fr[b]>0 {live=live.wrapping_add(1);}if fr[b]>mx {mx=fr[b];}b+=1;}
 if live>=160 && mx<((i/12) as u32).wrapping_add(1) {2} else {0}
}

pub fn q9_choose_plan(input:&[u8],plan:&mut [u32]) {
 let m=q9_mode(input);
 if m==1 {q9_dplan(input,plan);} else if m==2 {q9_hplan(input,plan);} else {q9_quick_plan(input,plan);}
}
#[inline(never)]
pub fn q9_parse(input:&[u8],out:&mut [u32])->usize {
 let mut plan=q9_filled(input.len(),0);q9_choose_plan(input,&mut plan);q9_emit_all(input,out,&plan)
}

// ======================= binary-tree parse (public #32 engine, items renamed x32_/X32_) =======================

/// Match finder: 0 = hash chains, anything else = binary tree.
pub const X32_MF: usize = 1;
/// Every length 3..=X32_LEN_FULL of a match is tried; above it only the full length.
pub const X32_LEN_FULL: usize = 48;

pub fn x32_load32(input: &[u8], p: usize) -> u32 {
    let b3 = input[p + 3] as u32;
    let b2 = input[p + 2] as u32;
    let b1 = input[p + 1] as u32;
    let b0 = input[p] as u32;
    b0 + 256 * (b1 + 256 * (b2 + 256 * b3))
}

/// Eight bytes, big-endian (the byte at `p` is the most significant).
pub fn x32_load64(input: &[u8], p: usize) -> u64 {
    let b7 = input[p + 7] as u64;
    let b6 = input[p + 6] as u64;
    let b5 = input[p + 5] as u64;
    let b4 = input[p + 4] as u64;
    let b3 = input[p + 3] as u64;
    let b2 = input[p + 2] as u64;
    let b1 = input[p + 1] as u64;
    let b0 = input[p] as u64;
    b7 + 256 * (b6 + 256 * (b5 + 256 * (b4 + 256 * (b3 + 256 * (b2 + 256 * (b1 + 256 * b0))))))
}

/// Length of agreement at `a`, `b` (a < b) from `start`, at most `cap`. Search only.
pub fn x32_ext(input: &[u8], a: usize, b: usize, start: usize, cap: usize) -> usize {
    let n = input.len();
    let n8 = if n >= 8 { n - 8 } else { 0 };
    let mut l = start;
    while l < cap && cap - l >= 8 && b <= n8 && l <= n8 - b {
        let x = x32_load64(input, a + l) ^ x32_load64(input, b + l);
        if x != 0 {
            l = l.wrapping_add((x.leading_zeros() / 8) as usize);
            break;
        }
        l += 8;
    }
    while l < cap && input[b + l] == input[a + l] {
        l += 1;
    }
    if l > cap { cap } else { l }
}

/// How many bytes agree at `a` and `b`, up to `cap`. The only function the proof depends on.
pub fn x32_match_len(input: &[u8], a: usize, b: usize, cap: usize) -> usize {
    let mut l = 0usize;
    while l < cap && input[b + l] == input[a + l] {
        l += 1;
    }
    l
}

pub fn x32_h4(x: u32) -> usize {
    (x.wrapping_mul(0x1E35A7BD) >> 16) as usize % 65536
}

pub fn x32_h3(x: u32) -> usize {
    ((x % 16777216).wrapping_mul(0x1E35A7BD) >> 17) as usize % 32768
}

pub fn x32_len_slot(len: usize) -> usize {
    if len >= 258 {
        return 28;
    }
    let l3 = if len >= 3 { len - 3 } else { 0 };
    if l3 < 8 {
        return l3;
    }
    let lz0 = (l3 as u32).leading_zeros();
    let lz = if lz0 > 28 { 28 } else { lz0 };
    let b = (31 - lz) as usize;
    4 * (b - 1) + ((l3 >> (b - 2)) % 4)
}

pub fn x32_len_extra(len: usize) -> u32 {
    if len >= 258 || len < 11 {
        return 0;
    }
    let lz0 = ((len - 3) as u32).leading_zeros();
    let lz = if lz0 > 29 { 29 } else { lz0 };
    29 - lz
}

pub fn x32_dist_slot(d: usize) -> usize {
    let d1 = if d >= 1 { d - 1 } else { 0 };
    if d1 < 4 {
        return d1;
    }
    let lz0 = (d1 as u32).leading_zeros();
    let lz = if lz0 > 29 { 29 } else { lz0 };
    let b = (31 - lz) as usize;
    (2 * b + ((d1 >> (b - 1)) % 2)) % 32
}

pub fn x32_dist_extra(s: usize) -> u32 {
    if s < 4 { 0 } else { (s / 2 - 1) as u32 }
}

pub fn x32_log2x16(x: u32) -> u32 {
    let lz = x.leading_zeros();
    let b = if lz > 31 { 0 } else { 31 - lz };
    let frac = if b >= 5 { (x >> (b - 5)) % 32 } else { (x << (5 - b)) % 32 };
    let tab: [u8; 32] = [0, 1, 1, 2, 3, 3, 4, 5, 5, 6, 6, 7, 7, 8, 8, 9, 9, 10, 10, 11, 11, 12, 12, 12, 13, 13, 14, 14, 14, 15, 15, 16];
    b * 16 + tab[frac as usize] as u32
}

/// Cost of a symbol seen `f` times out of `total`, in 1/16 bits, clamped to 16..=240.
pub fn x32_cost_of(f: u32, total: u32, nostat: u32) -> u32 {
    if f == 0 {
        return nostat;
    }
    let c = x32_log2x16(total).wrapping_sub(x32_log2x16(f));
    if c < 16 { 16 } else if c > 240 { 240 } else { c }
}

/// Distance of a x32_verified 3-byte match at the hash3 candidate `c3`, or 0.
pub fn x32_probe3(input: &[u8], c3: usize, pos: usize) -> usize {
    if c3 > 0 && c3 <= pos && pos - (c3 - 1) <= 32768 {
        let cp = c3 - 1;
        if input[cp] == input[pos] && input[cp + 1] == input[pos + 1] && input[cp + 2] == input[pos + 2] {
            return pos - cp;
        }
    }
    0
}

/// Hash-chain finder. Records improving matches at cache[nm..]; returns (new nm, best_len).
pub fn x32_hc_find(
    input: &[u8],
    head4: &mut [u32; 65536],
    head3: &mut [u32; 65536],
    prev: &mut [u32; 65536],
    pos: usize,
    cap: usize,
    ml: &mut [u16; 262144],
    md: &mut [u16; 262144],
    nm0: usize,
    depth: usize,
    nice_c: usize,
) -> (usize, usize) {
    let seq = x32_load32(input, pos);
    let hh4 = x32_h4(seq);
    let hh3 = x32_h3(seq);
    let c4 = head4[hh4] as usize;
    let c3 = head3[hh3] as usize;
    head4[hh4] = (pos + 1) as u32;
    head3[hh3] = (pos + 1) as u32;
    prev[pos % 32768] = c4 as u32;
    x32_hc_walk(input, prev, pos, cap, ml, md, nm0, depth, nice_c, c4, c3, seq)
}

/// The chain walk of `x32_hc_find` (split off: Aeneas cannot translate the loop after the `prev` write).
pub fn x32_hc_walk(
    input: &[u8],
    prev: &[u32; 65536],
    pos: usize,
    cap: usize,
    ml: &mut [u16; 262144],
    md: &mut [u16; 262144],
    nm0: usize,
    depth: usize,
    nice_c: usize,
    c4: usize,
    c3: usize,
    seq: u32,
) -> (usize, usize) {
    let mut nm = nm0;
    let d3 = if cap >= 3 { x32_probe3(input, c3, pos) } else { 0 };
    let mut best_len = if d3 > 0 { 3 } else { 2 };
    let mut first = 1usize;
    let mut cur = c4;
    let mut probes = 0usize;
    let nice = if nice_c < cap { nice_c } else { cap };
    while probes < depth && cur > 0 && cur <= pos {
        let cp = cur - 1;
        if pos - cp > 32768 {
            cur = 0;
        } else {
            if best_len < cap && cap >= 4 && input[cp + best_len] == input[pos + best_len] && x32_load32(input, cp) == seq {
                let l = x32_ext(input, cp, pos, 4, cap);
                if l > best_len {
                    if first == 1 && d3 > 0 && d3 < pos - cp {
                        ml[nm % 262144] = 3;
                        md[nm % 262144] = (d3 - 1) as u16;
                        nm = nm.wrapping_add(1);
                    }
                    first = 0;
                    best_len = l;
                    ml[nm % 262144] = l as u16;
                    md[nm % 262144] = (pos - cp - 1) as u16;
                    nm = nm.wrapping_add(1);
                }
            }
            if best_len >= nice {
                cur = 0;
            } else {
                cur = prev[cp % 32768] as usize;
            }
        }
        probes += 1;
    }
    if first == 1 && d3 > 0 {
        ml[nm % 262144] = 3;
        md[nm % 262144] = (d3 - 1) as u16;
        nm = nm.wrapping_add(1);
    }
    (nm, if best_len < 3 { 0 } else { best_len })
}

pub fn x32_hc_insert(input: &[u8], head4: &mut [u32; 65536], head3: &mut [u32; 65536], prev: &mut [u32; 65536], k: usize) {
    let seq = x32_load32(input, k);
    let hh4 = x32_h4(seq);
    prev[k % 32768] = head4[hh4];
    head4[hh4] = (k + 1) as u32;
    head3[x32_h3(seq)] = (k + 1) as u32;
}

/// The two hash3 candidates of the tree finder: record the first that verifies.
pub fn x32_bt_rec3(
    input: &[u8],
    c3a: usize,
    c3b: usize,
    pos: usize,
    ml: &mut [u16; 262144],
    md: &mut [u16; 262144],
    nm0: usize,
) -> usize {
    let da = x32_probe3(input, c3a, pos);
    if da > 0 {
        ml[nm0 % 262144] = 3;
        md[nm0 % 262144] = (da - 1) as u16;
        return nm0.wrapping_add(1);
    }
    let db = x32_probe3(input, c3b, pos);
    if db > 0 {
        ml[nm0 % 262144] = 3;
        md[nm0 % 262144] = (db - 1) as u16;
        return nm0.wrapping_add(1);
    }
    nm0
}

/// Binary-tree finder (libdeflate bt_matchfinder_advance_one_byte). `record == 0` only inserts.
/// The children of the node at `s = pos % 32768` are `lr[2*s]` (smaller) and `lr[2*s+1]` (larger).
pub fn x32_bt_find(
    input: &[u8],
    head4: &mut [u32; 65536],
    h3w: &mut [u32; 65536],
    lr: &mut [u32; 65536],
    pos: usize,
    cap: usize,
    depth: usize,
    record: usize,
    ml: &mut [u16; 262144],
    md: &mut [u16; 262144],
    nm0: usize,
    nice_c: usize,
) -> (usize, usize) {
    let seq = x32_load32(input, pos);
    let hh4 = x32_h4(seq);
    let hh3 = x32_h3(seq) % 32768;
    let c3a = h3w[2 * hh3] as usize;
    let c3b = h3w[2 * hh3 + 1] as usize;
    h3w[2 * hh3] = (pos + 1) as u32;
    h3w[2 * hh3 + 1] = c3a as u32;
    let nm = if record == 1 && cap >= 3 { x32_bt_rec3(input, c3a, c3b, pos, ml, md, nm0) } else { nm0 };
    let cur = head4[hh4] as usize;
    head4[hh4] = (pos + 1) as u32;
    let slot = pos % 32768;
    if cur == 0 || cur > pos || pos - (cur - 1) > 32768 || cap < 4 {
        lr[2 * slot] = 0;
        lr[2 * slot + 1] = 0;
        return (nm, if nm > nm0 { 3 } else { 0 });
    }
    x32_bt_walk(input, lr, pos, cap, depth, record, ml, md, nm, nm0, nice_c, cur, slot)
}

/// The tree walk of `x32_bt_find`. `lt_p`/`gt_p` are the pending child slots in `lr`.
pub fn x32_bt_walk(
    input: &[u8],
    lr: &mut [u32; 65536],
    pos: usize,
    cap: usize,
    depth: usize,
    record: usize,
    ml: &mut [u16; 262144],
    md: &mut [u16; 262144],
    nm1: usize,
    nm0: usize,
    nice_c: usize,
    cur0: usize,
    slot: usize,
) -> (usize, usize) {
    let mut nm = nm1;
    let mut cur = cur0;
    let mut lt_p = 2 * (slot % 32768);
    let mut gt_p = 2 * (slot % 32768) + 1;
    let mut best_lt = 0usize;
    let mut best_gt = 0usize;
    let mut len = 0usize;
    let mut best_len = 3usize;
    let nice = if nice_c < cap { nice_c } else { cap };
    let mut probes = 0usize;
    while probes < depth {
        let cp = cur - 1;
        let cs = cp % 32768;
        if input[cp + len] == input[pos + len] {
            len = x32_ext(input, cp, pos, len + 1, cap);
            if record == 1 && len > best_len {
                best_len = len;
                ml[nm % 262144] = len as u16;
                md[nm % 262144] = (pos - cp - 1) as u16;
                nm = nm.wrapping_add(1);
            }
        }
        if len >= nice {
            let lc = lr[2 * cs];
            let rc = lr[2 * cs + 1];
            lr[lt_p % 65536] = lc;
            lr[gt_p % 65536] = rc;
            break;
        }
        if input[cp + len] < input[pos + len] {
            lr[lt_p % 65536] = cur as u32;
            lt_p = 2 * cs + 1;
            cur = lr[2 * cs + 1] as usize;
            best_lt = len;
            if best_gt < len {
                len = best_gt;
            }
        } else {
            lr[gt_p % 65536] = cur as u32;
            gt_p = 2 * cs;
            cur = lr[2 * cs] as usize;
            best_gt = len;
            if best_lt < len {
                len = best_lt;
            }
        }
        probes += 1;
        if cur == 0 || cur > pos || pos - (cur - 1) > 32768 || probes >= depth {
            lr[lt_p % 65536] = 0;
            lr[gt_p % 65536] = 0;
            break;
        }
    }
    (nm, if record == 1 && best_len > 3 { best_len } else if nm > nm0 { 3 } else { 0 })
}

/// Match finding for one segment (`prev` is the hash chain for X32_MF=0, the tree for X32_MF=1): fills the cache `ml/md` and the per-position starts `mstart`.
pub fn x32_find_seg(
    input: &[u8],
    head4: &mut [u32; 65536],
    head3: &mut [u32; 65536],
    prev: &mut [u32; 65536],
    ml: &mut [u16; 262144],
    md: &mut [u16; 262144],
    mstart: &mut [u32; 65536],
    pos0: usize,
    slen: usize,
    depth: usize,
    nice: usize,
) {
    let n = input.len();
    let mut nm = 0usize;
    let mut k = 0usize;
    while k < slen {
        let p = pos0 + k;
        mstart[k % 65536] = nm as u32;
        let mut skip = 0usize;
        if n - p >= 4 && nm < 262080 {
            let cap = if n - p > 258 { 258 } else { n - p };
            let r = if X32_MF == 0 {
                x32_hc_find(input, head4, head3, prev, p, cap, ml, md, nm, depth, nice)
            } else {
                x32_bt_find(input, head4, head3, prev, p, cap, depth, 1, ml, md, nm, nice)
            };
            nm = r.0;
            if r.1 >= nice && r.1 > 0 {
                skip = r.1 - 1;
            }
        } else if n - p >= 4 {
            if X32_MF == 0 {
                x32_hc_insert(input, head4, head3, prev, p);
            }
        }
        k += 1;
        while skip > 0 && k < slen {
            let p2 = pos0 + k;
            mstart[k % 65536] = nm as u32;
            if n - p2 >= 4 {
                if X32_MF == 0 {
                    x32_hc_insert(input, head4, head3, prev, p2);
                } else {
                    let cap2 = if n - p2 > nice { nice } else { n - p2 };
                    let _ = x32_bt_find(input, head4, head3, prev, p2, cap2, depth, 0, ml, md, nm, nice);
                }
            }
            k += 1;
            skip -= 1;
        }
    }
    mstart[slen % 65536] = nm as u32;
}

/// Starting costs for the first segment: literals from byte counts, static match costs.
pub fn x32_init_costs(
    input: &[u8],
    lit_cost: &mut [u32; 256],
    len_cost: &mut [u32; 512],
    dcost: &mut [u32; 32],
    pos0: usize,
    slen: usize,
) {
    let mut hist = [0u32; 256];
    let mut q = 0usize;
    while q < slen {
        let b = input[pos0 + q] as usize;
        hist[b] = hist[b].wrapping_add(1);
        q += 1;
    }
    let mut s = 0usize;
    while s < 256 {
        lit_cost[s] = x32_cost_of(hist[s], slen as u32, 13 * 16).wrapping_add(16);
        s += 1;
    }
    let mut l = 3usize;
    while l <= 258 {
        len_cost[l] = 94u32.wrapping_add(16u32.wrapping_mul(x32_len_extra(l)));
        l += 1;
    }
    s = 0;
    while s < 30 {
        dcost[s] = 78u32.wrapping_add(16u32.wrapping_mul(x32_dist_extra(s)));
        s += 1;
    }
}

/// Backward DP over the segment under the current costs: `cte` cost-to-end, `chl/chd` choice.
pub fn x32_dp_pass(
    input: &[u8],
    ml: &[u16; 262144],
    md: &[u16; 262144],
    mstart: &[u32; 65536],
    cte: &mut [u32; 65536],
    chl: &mut [u16; 65536],
    chd: &mut [u16; 65536],
    lit_cost: &[u32; 256],
    len_cost: &[u32; 512],
    dcost: &[u32; 32],
    pos0: usize,
    slen: usize,
) {
    cte[slen % 65536] = 0;
    let mut j = slen;
    while j > 0 {
        j -= 1;
        let b = input[pos0 + j] as usize;
        let mut best = cte[(j + 1) % 65536].wrapping_add(lit_cost[b]);
        let mut bl = 0usize;
        let mut bd = 0usize;
        let a = mstart[j % 65536] as usize;
        let e = mstart[(j + 1) % 65536] as usize;
        let lmax = slen - j;
        let mut m = a;
        let mut l = 3usize;
        while m < e {
            let mut mlen = ml[m % 262144] as usize;
            if mlen > lmax {
                mlen = lmax;
            }
            let dd = md[m % 262144] as usize;
            let dc = dcost[x32_dist_slot(dd + 1)];
            let top = if mlen > X32_LEN_FULL { X32_LEN_FULL } else { mlen };
            while l <= top {
                let c = cte[(j + l) % 65536].wrapping_add(len_cost[l % 512]).wrapping_add(dc);
                if c < best {
                    best = c;
                    bl = l;
                    bd = dd;
                }
                l += 1;
            }
            if mlen > top && l <= mlen {
                let c = cte[(j + mlen) % 65536].wrapping_add(len_cost[mlen % 512]).wrapping_add(dc);
                if c < best {
                    best = c;
                    bl = mlen;
                    bd = dd;
                }
                l = mlen + 1;
            }
            m += 1;
        }
        cte[j % 65536] = best;
        chl[j % 65536] = bl as u16;
        chd[j % 65536] = bd as u16;
    }
}

/// Symbol counts of the chosen path.
pub fn x32_tally(
    input: &[u8],
    chl: &[u16; 65536],
    chd: &[u16; 65536],
    llf: &mut [u32; 286],
    df: &mut [u32; 32],
    pos0: usize,
    slen: usize,
) {
    let mut s = 0usize;
    while s < 286 {
        llf[s] = 0;
        s += 1;
    }
    s = 0;
    while s < 32 {
        df[s] = 0;
        s += 1;
    }
    let mut q = 0usize;
    while q < slen {
        let l = chl[q % 65536] as usize;
        if l >= 3 {
            let ls = 257 + x32_len_slot(l) % 29;
            llf[ls] = llf[ls].wrapping_add(1);
            let ds = x32_dist_slot(chd[q % 65536] as usize + 1);
            df[ds] = df[ds].wrapping_add(1);
            q += l;
        } else {
            let b = input[pos0 + q] as usize;
            llf[b] = llf[b].wrapping_add(1);
            q += 1;
        }
    }
    llf[256] = llf[256].wrapping_add(1);
}

/// New costs from the counts.
pub fn x32_refresh(
    llf: &[u32; 286],
    df: &[u32; 32],
    lit_cost: &mut [u32; 256],
    len_cost: &mut [u32; 512],
    dcost: &mut [u32; 32],
) {
    let mut lt = 0u32;
    let mut s = 0usize;
    while s < 286 {
        lt = lt.wrapping_add(llf[s]);
        s += 1;
    }
    let mut dt = 0u32;
    s = 0;
    while s < 30 {
        dt = dt.wrapping_add(df[s]);
        s += 1;
    }
    if dt == 0 {
        dt = 1;
    }
    s = 0;
    while s < 256 {
        lit_cost[s] = x32_cost_of(llf[s], lt, 13 * 16);
        s += 1;
    }
    let mut l = 3usize;
    while l <= 258 {
        len_cost[l] = x32_cost_of(llf[257 + x32_len_slot(l) % 29], lt, 13 * 16).wrapping_add(16u32.wrapping_mul(x32_len_extra(l)));
        l += 1;
    }
    s = 0;
    while s < 30 {
        dcost[s] = x32_cost_of(df[s], dt, 10 * 16).wrapping_add(16u32.wrapping_mul(x32_dist_extra(s)));
        s += 1;
    }
}

/// `np` rounds of DP + recount + new costs.
pub fn x32_run_passes(
    input: &[u8],
    ml: &[u16; 262144],
    md: &[u16; 262144],
    mstart: &[u32; 65536],
    cte: &mut [u32; 65536],
    chl: &mut [u16; 65536],
    chd: &mut [u16; 65536],
    lit_cost: &mut [u32; 256],
    len_cost: &mut [u32; 512],
    dcost: &mut [u32; 32],
    llf: &mut [u32; 286],
    df: &mut [u32; 32],
    pos0: usize,
    slen: usize,
    np: usize,
) {
    let mut pass = 0usize;
    while pass < np {
        x32_dp_pass(input, ml, md, mstart, cte, chl, chd, lit_cost, len_cost, dcost, pos0, slen);
        x32_tally(input, chl, chd, llf, df, pos0, slen);
        x32_refresh(llf, df, lit_cost, len_cost, dcost);
        pass += 1;
    }
}


/// True iff the chosen match `(ch, d)` at `pos` is in range and its bytes agree. The only
/// check the proof relies on; the dynamic program that chose it is never trusted.
pub fn x32_verified(input: &[u8], pos: usize, d: usize, ch: usize, k: usize, blen: usize) -> bool {
    if ch < 3 || ch > 258 || d < 1 || d > 32768 || d > pos || k + ch > blen {
        return false;
    }
    let v = x32_match_len(input, pos - d, pos, ch);
    v >= ch
}

/// Emit the chosen path of one segment; every match is re-x32_verified before it is written.
pub fn x32_emit_seg(
    input: &[u8],
    out: &mut [u32],
    chl: &[u16; 65536],
    chd: &[u16; 65536],
    ntok0: usize,
    pos0: usize,
    slen: usize,
) -> usize {
    let mut ntok = ntok0;
    let mut q = 0usize;
    while q < slen {
        let p = pos0 + q;
        let l = chl[q % 65536] as usize;
        let d = chd[q % 65536] as usize + 1;
        if x32_verified(input, p, d, l, q, slen) {
            out[ntok] = 16777216u32 + ((d - 1) as u32) * 256 + ((l - 3) as u32);
            ntok += 1;
            q += l;
        } else {
            out[ntok] = input[p] as u32;
            ntok += 1;
            q += 1;
        }
    }
    ntok
}



// ── Block-aware refinement ───────────────────────────────────────────────────
// The shared encoder cuts a block every XB_BLOCK_TOKENS tokens and gives each block its own
// Huffman tables. After the per-segment passes, the whole path is cut into those blocks, each
// block's exact code lengths become its cost table, and every segment is parsed again under
// the costs of the block each position falls in. All of it is untrusted: emission re-verifies.


/// Dials of x32b_parse (see the X32_* twins).
pub const XB_DEPTH: usize = 64;
pub const XB_NICE: usize = 258;
pub const XB_PASSES: usize = 2;
pub const XB_PASSES_FIRST: usize = 2;
pub const XB_LEN_FULL: usize = 258;
pub const XB_SEG: usize = 16384;

/// Block-aware passes over the whole file after the per-segment ones.
pub const XB_BLK: usize = 2;
/// Bits charged for a symbol the block's table does not have yet.
pub const XB_UNUSED_LIT: u32 = 14;
pub const XB_UNUSED_DIST: u32 = 11;
/// Tokens per block of the shared encoder.
pub const XB_BLOCK_TOKENS: usize = 16384;
/// Cost table per block: 256 literals, lengths 0..=258, 30 distance slots (1/16 bit).
pub const XB_CW: usize = 545;
/// Cap on every whole-file buffer.
pub const XB_GCAP: usize = 1073741824;

pub fn x32_g16(v: &[u16], i: usize) -> usize {
    if i < v.len() { v[i] as usize } else { 0 }
}

pub fn x32_g32(v: &[u32], i: usize) -> u32 {
    if i < v.len() { v[i] } else { 0 }
}

/// Append one segment's match cache (rebased) and chosen path to the whole-file copies.
pub fn x32_save_seg(
    ml: &[u16; 262144],
    md: &[u16; 262144],
    mstart: &[u32; 65536],
    chl: &[u16; 65536],
    chd: &[u16; 65536],
    slen: usize,
    gml: &mut Vec<u16>,
    gmd: &mut Vec<u16>,
    gms: &mut Vec<u32>,
    gchl: &mut Vec<u16>,
    gchd: &mut Vec<u16>,
) {
    let base = gml.len() as u32;
    let mut k = 0usize;
    while k < slen {
        if gms.len() < XB_GCAP {
            gms.push(base.wrapping_add(mstart[k % 65536]));
        }
        if gchl.len() < XB_GCAP {
            gchl.push(chl[k % 65536]);
        }
        if gchd.len() < XB_GCAP {
            gchd.push(chd[k % 65536]);
        }
        k += 1;
    }
    let e = mstart[slen % 65536] as usize;
    let mut m = 0usize;
    while m < e {
        if gml.len() < XB_GCAP {
            gml.push(ml[m % 262144]);
        }
        if gmd.len() < XB_GCAP {
            gmd.push(md[m % 262144]);
        }
        m += 1;
    }
}

/// Insert symbol `s` into `idx[0..m]`, kept sorted by count ascending.
pub fn x32_sort_insert(f: &[u32; 512], idx: &mut [u32; 512], m: usize, s: usize) {
    let fs = f[s % 512];
    let mut j = m % 512;
    while j > 0 && f[idx[(j - 1) % 512] as usize % 512] > fs {
        idx[j % 512] = idx[(j - 1) % 512];
        j -= 1;
    }
    idx[j % 512] = s as u32;
}

/// Moffat-Katajainen phase 1: in-place combine of the sorted weights `a[0..m]`, `m >= 2`.
pub fn x32_mk_phase1(a: &mut [u32; 512], m: usize) {
    a[0] = a[0].wrapping_add(a[1]);
    let mut root = 0usize;
    let mut leaf = 2usize;
    let mut next = 1usize;
    while next < m - 1 && next < 512 {
        let r1 = if leaf >= m { 1usize } else if a[root % 512] < a[leaf % 512] { 1 } else { 0 };
        let v1 = if r1 == 1 { a[root % 512] } else { a[leaf % 512] };
        a[next % 512] = v1;
        if r1 == 1 {
            a[root % 512] = next as u32;
        }
        root = root.wrapping_add(r1);
        leaf = leaf.wrapping_add(1 - r1);
        let r2 = if leaf >= m { 1usize } else if root < next && a[root % 512] < a[leaf % 512] { 1 } else { 0 };
        let v2 = if r2 == 1 { a[root % 512] } else { a[leaf % 512] };
        a[next % 512] = a[next % 512].wrapping_add(v2);
        if r2 == 1 {
            a[root % 512] = next as u32;
        }
        root = root.wrapping_add(r2);
        leaf = leaf.wrapping_add(1 - r2);
        next += 1;
    }
}

/// Phase 2: parent pointers to internal-node depths, `m >= 2`.
pub fn x32_mk_phase2(a: &mut [u32; 512], m: usize) {
    a[(m - 2) % 512] = 0;
    let mut next = m - 2;
    while next > 0 {
        next -= 1;
        let p = a[next % 512] as usize;
        a[next % 512] = a[p % 512].wrapping_add(1);
    }
}

/// Phase 3, inner step: count the internal nodes at `depth`, walking `r` (one past the root) down.
pub fn x32_mk_used(a: &[u32; 512], r0: usize, depth: u32) -> (usize, usize) {
    let mut r = r0;
    let mut used = 0usize;
    while r > 0 && a[(r - 1) % 512] == depth {
        used = used.wrapping_add(1);
        r -= 1;
    }
    (used, r)
}

/// Phase 3, inner step: `avbl - used` leaves get length `depth`, written down from `nx` (one past).
pub fn x32_mk_assign(a: &mut [u32; 512], nx0: usize, avbl: usize, used: usize, depth: u32) -> usize {
    let mut nx = nx0;
    let mut k = avbl;
    while k > used && nx > 0 {
        a[(nx - 1) % 512] = depth;
        nx -= 1;
        k -= 1;
    }
    nx
}

/// Phase 3: internal-node depths to leaf code lengths, `m >= 2`.
pub fn x32_mk_phase3(a: &mut [u32; 512], m: usize) {
    let mut avbl = 1usize;
    let mut depth = 0u32;
    let mut r = m - 1;
    let mut nx = m;
    let mut fuel = 0usize;
    while avbl > 0 && fuel < 64 {
        let u = x32_mk_used(a, r, depth);
        let used = u.0;
        r = u.1;
        nx = x32_mk_assign(a, nx, avbl, used, depth);
        avbl = used.wrapping_mul(2);
        depth = depth.wrapping_add(1);
        fuel += 1;
    }
}

/// Huffman code lengths of `f[0..ns]`, clamped to 1..=15, into `lens` (0 for an unused symbol).
pub fn x32_huff(f: &[u32; 512], ns: usize, lens: &mut [u32; 512]) {
    let mut idx = [0u32; 512];
    let mut a = [0u32; 512];
    let mut m = 0usize;
    let mut s = 0usize;
    while s < ns && s < 512 {
        lens[s] = 0;
        if f[s] > 0 {
            x32_sort_insert(f, &mut idx, m, s);
            m += 1;
        }
        s += 1;
    }
    if m == 1 {
        lens[idx[0] as usize % 512] = 1;
    }
    if m >= 2 {
        let mut i = 0usize;
        while i < m {
            a[i % 512] = f[idx[i % 512] as usize % 512];
            i += 1;
        }
        x32_mk_phase1(&mut a, m);
        x32_mk_phase2(&mut a, m);
        x32_mk_phase3(&mut a, m);
        i = 0;
        while i < m {
            let l = a[i % 512];
            lens[idx[i % 512] as usize % 512] = if l > 15 { 15 } else if l < 1 { 1 } else { l };
            i += 1;
        }
    }
}

pub fn x32_push_cost(costs: &mut Vec<u32>, len: u32, unused: u32, extra: u32) {
    let b = if len == 0 { unused } else { len };
    if costs.len() < XB_GCAP {
        costs.push(b.wrapping_add(extra).wrapping_mul(16));
    }
}

/// Close a block: its start and its cost table from the counts; the counts are cleared.
pub fn x32_push_block(llf: &mut [u32; 512], df: &mut [u32; 512], bs: usize, bstart: &mut Vec<u32>, costs: &mut Vec<u32>) {
    llf[256] = llf[256].wrapping_add(1);
    let mut ll = [0u32; 512];
    let mut dl = [0u32; 512];
    x32_huff(llf, 286, &mut ll);
    x32_huff(df, 30, &mut dl);
    if bstart.len() < XB_GCAP {
        bstart.push(bs as u32);
    }
    let mut s = 0usize;
    while s < 256 {
        x32_push_cost(costs, ll[s], XB_UNUSED_LIT, 0);
        s += 1;
    }
    s = 0;
    while s < 259 {
        x32_push_cost(costs, ll[(257 + x32_len_slot(s) % 29) % 512], XB_UNUSED_LIT, x32_len_extra(s));
        s += 1;
    }
    s = 0;
    while s < 30 {
        x32_push_cost(costs, dl[s], XB_UNUSED_DIST, x32_dist_extra(s));
        s += 1;
    }
    s = 0;
    while s < 512 {
        llf[s] = 0;
        df[s] = 0;
        s += 1;
    }
}

/// Cut the whole-file path into the encoder's blocks: per block its start and cost table.
pub fn x32_blk_costs(input: &[u8], gchl: &[u16], gchd: &[u16], bstart: &mut Vec<u32>, costs: &mut Vec<u32>) {
    let n = input.len();
    let mut llf = [0u32; 512];
    let mut df = [0u32; 512];
    let mut q = 0usize;
    let mut t = 0usize;
    let mut bs = 0usize;
    while q < n {
        let l = x32_g16(gchl, q);
        if l >= 3 && l <= 258 {
            let ls = 257 + x32_len_slot(l) % 29;
            llf[ls % 512] = llf[ls % 512].wrapping_add(1);
            let ds = x32_dist_slot(x32_g16(gchd, q) + 1);
            df[ds % 512] = df[ds % 512].wrapping_add(1);
            let rest = n - q;
            q = if l < rest { q + l } else { n };
        } else {
            let b = input[q] as usize;
            llf[b % 512] = llf[b % 512].wrapping_add(1);
            q += 1;
        }
        t = t.wrapping_add(1);
        if t >= XB_BLOCK_TOKENS {
            x32_push_block(&mut llf, &mut df, bs, bstart, costs);
            bs = q;
            t = 0;
        }
    }
    if t > 0 || bstart.len() == 0 {
        x32_push_block(&mut llf, &mut df, bs, bstart, costs);
    }
}

/// The block holding position `p`: the last whose start is at or before it.
pub fn x32_find_blk(bstart: &[u32], p: usize) -> usize {
    let mut b = bstart.len();
    while b > 1 && x32_g32(bstart, b - 1) as usize > p {
        b -= 1;
    }
    if b > 0 { b - 1 } else { 0 }
}

/// Backward DP over one segment, each position priced by its block's table.
pub fn x32_dp_blk(
    input: &[u8],
    gml: &[u16],
    gmd: &[u16],
    gms: &[u32],
    costs: &[u32],
    bstart: &[u32],
    cte: &mut [u32; 65536],
    chl: &mut [u16; 65536],
    chd: &mut [u16; 65536],
    pos0: usize,
    slen: usize,
    b0: usize,
) {
    cte[slen % 65536] = 0;
    let mut b = b0;
    let mut j = slen;
    while j > 0 {
        j -= 1;
        let p = pos0 + j;
        if b > 0 && x32_g32(bstart, b) as usize > p {
            b -= 1;
        }
        let cb = b.wrapping_mul(XB_CW);
        let byte = input[p] as usize;
        let mut best = cte[(j + 1) % 65536].wrapping_add(x32_g32(costs, cb.wrapping_add(byte)));
        let mut bl = 0usize;
        let mut bd = 0usize;
        let a = x32_g32(gms, p) as usize;
        let e = x32_g32(gms, p + 1) as usize;
        let lmax = slen - j;
        let mut m = a;
        let mut l = 3usize;
        while m < e {
            let mut mlen = x32_g16(gml, m);
            if mlen > lmax {
                mlen = lmax;
            }
            let dd = x32_g16(gmd, m);
            let dc = x32_g32(costs, cb.wrapping_add(515).wrapping_add(x32_dist_slot(dd + 1) % 30));
            let top = if mlen > XB_LEN_FULL { XB_LEN_FULL } else { mlen };
            while l <= top {
                let c = cte[(j + l) % 65536].wrapping_add(x32_g32(costs, cb.wrapping_add(256).wrapping_add(l % 512))).wrapping_add(dc);
                if c < best {
                    best = c;
                    bl = l;
                    bd = dd;
                }
                l += 1;
            }
            if mlen > top && l <= mlen {
                let c = cte[(j + mlen) % 65536].wrapping_add(x32_g32(costs, cb.wrapping_add(256).wrapping_add(mlen % 512))).wrapping_add(dc);
                if c < best {
                    best = c;
                    bl = mlen;
                    bd = dd;
                }
                l = mlen + 1;
            }
            m += 1;
        }
        cte[j % 65536] = best;
        chl[j % 65536] = bl as u16;
        chd[j % 65536] = bd as u16;
    }
}

/// Write one segment's path into the whole-file path.
pub fn x32_put_path(chl: &[u16; 65536], chd: &[u16; 65536], gchl: &mut [u16], gchd: &mut [u16], pos0: usize, slen: usize) {
    let mut k = 0usize;
    while k < slen {
        let p = pos0.wrapping_add(k);
        if p < gchl.len() {
            gchl[p] = chl[k % 65536];
        }
        if p < gchd.len() {
            gchd[p] = chd[k % 65536];
        }
        k += 1;
    }
}

/// Read one segment's path out of the whole-file path.
pub fn x32_get_path(gchl: &[u16], gchd: &[u16], chl: &mut [u16; 65536], chd: &mut [u16; 65536], pos0: usize, slen: usize) {
    let mut k = 0usize;
    while k < slen {
        let p = pos0.wrapping_add(k);
        chl[k % 65536] = x32_g16(gchl, p) as u16;
        chd[k % 65536] = x32_g16(gchd, p) as u16;
        k += 1;
    }
}

/// One block-aware pass: every segment re-parsed under its blocks' costs.
pub fn x32_blk_pass(
    input: &[u8],
    gml: &[u16],
    gmd: &[u16],
    gms: &[u32],
    costs: &[u32],
    bstart: &[u32],
    cte: &mut [u32; 65536],
    chl: &mut [u16; 65536],
    chd: &mut [u16; 65536],
    gchl: &mut [u16],
    gchd: &mut [u16],
    seg: usize,
) {
    let n = input.len();
    let mut pos0 = 0usize;
    while pos0 < n {
        let rest = n - pos0;
        let slen = if rest > seg { seg } else { rest };
        let b0 = x32_find_blk(bstart, pos0 + slen - 1);
        x32_dp_blk(input, gml, gmd, gms, costs, bstart, cte, chl, chd, pos0, slen, b0);
        x32_put_path(chl, chd, gchl, gchd, pos0, slen);
        pos0 += slen;
    }
}

/// f32 lanes: the binary-tree parse plus block-aware refinement (public #99 engine), own dials XB_*.
#[inline(never)]
#[inline(never)]
pub fn x32b_parse(input: &[u8], out: &mut [u32]) -> usize {
    let n = input.len();
    let mut head4 = [0u32; 65536];
    let mut head3 = [0u32; 65536];
    let mut prev = [0u32; 65536];
    let mut ml = [0u16; 262144];
    let mut md = [0u16; 262144];
    let mut mstart = [0u32; 65536];
    let mut cte = [0u32; 65536];
    let mut chl = [0u16; 65536];
    let mut chd = [0u16; 65536];
    let mut lit_cost = [0u32; 256];
    let mut len_cost = [0u32; 512];
    let mut dcost = [0u32; 32];
    let mut llf = [0u32; 286];
    let mut df = [0u32; 32];
    let mut gml: Vec<u16> = Vec::new();
    let mut gmd: Vec<u16> = Vec::new();
    let mut gms: Vec<u32> = Vec::new();
    let mut gchl: Vec<u16> = Vec::new();
    let mut gchd: Vec<u16> = Vec::new();
    let seg = if XB_SEG < 1 { 1 } else if XB_SEG > 32768 { 32768 } else { XB_SEG };
    let mut pos0 = 0usize;
    while pos0 < n {
        let rest = n - pos0;
        let slen = if rest > seg { seg } else { rest };
        x32_find_seg(input, &mut head4, &mut head3, &mut prev, &mut ml, &mut md, &mut mstart, pos0, slen, XB_DEPTH, XB_NICE);
        if pos0 == 0 {
            x32_init_costs(input, &mut lit_cost, &mut len_cost, &mut dcost, pos0, slen);
        }
        let np = if pos0 == 0 { XB_PASSES_FIRST } else { XB_PASSES };
        x32_run_passes(input, &ml, &md, &mstart, &mut cte, &mut chl, &mut chd, &mut lit_cost, &mut len_cost, &mut dcost, &mut llf, &mut df, pos0, slen, np);
        x32_save_seg(&ml, &md, &mstart, &chl, &chd, slen, &mut gml, &mut gmd, &mut gms, &mut gchl, &mut gchd);
        pos0 += slen;
    }
    if gms.len() < XB_GCAP {
        gms.push(gml.len() as u32);
    }
    let mut it = 0usize;
    while it < XB_BLK {
        let mut bstart: Vec<u32> = Vec::new();
        let mut costs: Vec<u32> = Vec::new();
        x32_blk_costs(input, &gchl, &gchd, &mut bstart, &mut costs);
        x32_blk_pass(input, &gml, &gmd, &gms, &costs, &bstart, &mut cte, &mut chl, &mut chd, &mut gchl, &mut gchd, seg);
        it += 1;
    }
    let mut ntok = 0usize;
    pos0 = 0;
    while pos0 < n {
        let rest = n - pos0;
        let slen = if rest > seg { seg } else { rest };
        x32_get_path(&gchl, &gchd, &mut chl, &mut chd, pos0, slen);
        ntok = x32_emit_seg(input, out, &chl, &chd, ntok, pos0, slen);
        pos0 += slen;
    }
    ntok
}

// ═══ r17 refine: BEGIN ═══
// Seeded global refiner; pasted after #459 or included in a module importing its helpers.
// Exact model 0, lambda=0, unused=15. cfg rows: visits, iterations, repeat stride, perturb.
pub const RF_CONFIG: [[usize; 7]; 64] = [[0, 0, 1, 0, 0, 0, 16], [16, 2, 16, 4, 1, 0, 16], [4, 2, 1, 4, 2, 0, 16], [16, 2, 1, 0, 1, 2, 12], [64, 3, 1, 4, 1, 2, 16], [32, 2, 16, 4, 1, 2, 12], [32, 2, 1, 0, 1, 2, 16], [4, 2, 1, 4, 2, 0, 20], [16, 2, 1, 0, 1, 1, 12], [16, 4, 8, 4, 2, 0, 14], [128, 4, 1, 4, 0, 0, 16], [256, 4, 1, 4, 0, 0, 16], [16, 2, 1, 0, 0, 0, 16], [64, 2, 1, 0, 0, 0, 16], [8, 2, 1, 0, 0, 0, 16], [6, 2, 1, 4, 2, 0, 16], [4, 3, 1, 4, 2, 0, 16], [16, 4, 1, 4, 1, 0, 16], [8, 4, 1, 4, 1, 0, 16], [16, 2, 1, 4, 1, 0, 16], [8, 2, 1, 4, 1, 0, 16], [64, 4, 1, 4, 1, 0, 16], [32768, 4, 1, 4, 1, 0, 16], [16, 4, 4, 4, 1, 0, 16], [16, 4, 8, 4, 1, 0, 16], [64, 2, 1, 4, 1, 0, 16], [128, 4, 1, 4, 1, 0, 16], [256, 4, 1, 4, 1, 0, 16], [16, 2, 1, 0, 1, 0, 16], [64, 2, 1, 0, 1, 0, 16], [8, 2, 1, 0, 1, 0, 16], [32768, 2, 1, 4, 1, 0, 16], [8, 3, 1, 4, 1, 0, 16], [16, 3, 1, 4, 1, 0, 16], [32, 2, 1, 0, 1, 0, 16], [32, 2, 1, 4, 1, 0, 16], [32, 3, 1, 4, 1, 0, 16], [32, 4, 1, 4, 1, 0, 16], [64, 3, 1, 4, 1, 0, 16], [128, 3, 1, 4, 1, 0, 16], [256, 3, 1, 4, 1, 0, 16], [8, 3, 1, 4, 2, 0, 16], [16, 3, 1, 4, 2, 0, 16], [32, 2, 1, 0, 2, 0, 16], [32, 2, 1, 4, 2, 0, 16], [32, 3, 1, 4, 2, 0, 16], [32, 4, 1, 4, 2, 0, 16], [64, 3, 1, 4, 2, 0, 16], [32, 2, 16, 4, 1, 0, 16], [16, 4, 1, 4, 2, 0, 16], [8, 4, 1, 4, 2, 0, 16], [16, 2, 1, 4, 2, 0, 16], [8, 2, 1, 4, 2, 0, 16], [64, 4, 1, 4, 2, 0, 16], [32768, 4, 1, 4, 2, 0, 16], [16, 4, 4, 4, 2, 0, 16], [16, 4, 8, 4, 2, 0, 16], [64, 2, 1, 4, 2, 0, 16], [128, 4, 1, 4, 2, 0, 16], [256, 4, 1, 4, 2, 0, 16], [16, 2, 1, 0, 2, 0, 16], [64, 2, 1, 0, 2, 0, 16], [8, 2, 1, 0, 2, 0, 16], [32768, 2, 1, 4, 2, 0, 16]];
pub const REFINE: [usize; 32] = [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 48, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 8, 0, 0, 9, 0, 0];

pub fn rf_zeros64(n: usize) -> Vec<u64> {
    let mut v = Vec::with_capacity(n);
    let mut i = 0usize;
    while i < n { v.push(0); i += 1; }
    v
}
pub fn rf_get64(v: &[u64], i: usize) -> u64 {
    if i < v.len() { v[i] } else { 0 }
}
pub fn rf_set64(v: &mut [u64], i: usize, x: u64) {
    if i < v.len() { v[i] = x; }
}
pub fn rf_byte(input: &[u8], i: usize) -> u8 {
    if i < input.len() { input[i] } else { 0 }
}

// Exact length-limited package merge. Scratch lists: 16 levels, stride 1024.
pub fn rf_pm_level(w: &mut [u64], r: &mut [u32], c: &mut [u32], src: usize, m: usize, live: usize, dst: usize) -> usize {
    let np = m / 2;
    let mut a = 0usize;
    let mut b = 0usize;
    let mut k = 0usize;
    while (a < live || b < np) && k < 1024 {
        let pw = if b < np { rf_get64(w, src.wrapping_add(2*b)).wrapping_add(rf_get64(w, src.wrapping_add(2*b+1))) } else { 0 };
        if b >= np || (a < live && rf_get64(w, a) <= pw) {
            rf_set64(w, dst.wrapping_add(k), rf_get64(w, a));
            set_in(r, dst.wrapping_add(k), 2147483648 | a as u32);
            a = a.wrapping_add(1);
        } else {
            rf_set64(w, dst.wrapping_add(k), pw);
            set_in(r, dst.wrapping_add(k), b as u32);
            b = b.wrapping_add(1);
        }
        set_in(c, dst.wrapping_add(k), 0);
        k += 1;
    }
    k
}
pub fn rf_pm_count(r: &[u32], c: &mut [u32], order: &[u32], lens: &mut [u32], loff: usize, off: usize, m: usize, below: usize) {
    let mut i = 0usize;
    while i < m && i < 1024 {
        let x = get0(c, off.wrapping_add(i));
        let rr = get0(r, off.wrapping_add(i));
        if rr >= 2147483648 {
            let s = get0(order, (rr & 511) as usize) as usize;
            let at = loff.wrapping_add(s);
            set_in(lens, at, get0(lens, at).wrapping_add(x));
        } else {
            let at = below.wrapping_add((rr as usize).wrapping_mul(2));
            set_in(c, at, get0(c, at).wrapping_add(x));
            set_in(c, at.wrapping_add(1), get0(c, at.wrapping_add(1)).wrapping_add(x));
        }
        i += 1;
    }
}
pub fn rf_pm(freq: &[u32], off: usize, nsym: usize, maxbits: usize, lens: &mut [u32], loff: usize, w: &mut [u64], r: &mut [u32], c: &mut [u32]) {
    q9_pkg_merge(freq, off, nsym, 32, lens, loff);
    let mut maxdepth = 0u32;
    let mut scan = 0usize;
    while scan < nsym && scan < 288 {
        let d = get0(lens, loff.wrapping_add(scan));
        if d > maxdepth { maxdepth = d; }
        scan += 1;
    }
    if maxdepth <= maxbits as u32 { return; }
    let mut order = zeros(288);
    let live = q9_sort_live(freq, off, nsym, &mut order);
    q9_clear(lens, loff, loff.wrapping_add(nsym));
    if live == 0 { return; }
    if live == 1 { set_in(lens, loff.wrapping_add(get0(&order, 0) as usize), 1); return; }
    let mut ms = zeros(16);
    let mut p = 0usize;
    while p < live && p < 288 {
        rf_set64(w, p, get0(freq, off.wrapping_add(get0(&order, p) as usize)) as u64);
        set_in(r, p, 2147483648 | p as u32);
        set_in(c, p, 0);
        p += 1;
    }
    set_in(&mut ms, 0, live as u32);
    let mut m = live;
    let mut level = 1usize;
    while level < maxbits && level < 16 {
        m = rf_pm_level(w, r, c, (level-1)*1024, m, live, level*1024);
        set_in(&mut ms, level, m as u32);
        level += 1;
    }
    let fin = level.saturating_sub(1)*1024;
    let take = live.wrapping_mul(2).saturating_sub(2);
    let mut j = 0usize;
    while j < take && j < m { set_in(c, fin.wrapping_add(j), 1); j += 1; }
    while level > 0 {
        level -= 1;
        rf_pm_count(r, c, &order, lens, loff, level*1024, get0(&ms, level) as usize, level.saturating_sub(1)*1024);
    }
}

// fr layout = 288 lit/len counts, 30 distances, extra bits, raw bytes.
// Return bits << 2 | mode (0 dynamic, 1 fixed, 2 stored before alignment).
pub fn rf_block(fr: &mut [u32], lens: &mut [u32], w: &mut [u64], r: &mut [u32], c: &mut [u32]) -> u64 {
    q9_bump(fr, 256, 1);
    rf_pm(fr, 0, 288, 15, lens, 0, w, r, c);
    rf_pm(fr, 288, 30, 15, lens, 288, w, r, c);
    let ndist = q9_sum_range(fr, 288, 318);
    if ndist == 0 { set_in(lens, 288, 1); }
    let hlit = q9_last_nz(lens, 0, 288, 257);
    let hdist = q9_last_nz(lens, 288, 30, 1);
    let mut all = zeros(320);
    q9_copy32(lens, 0, &mut all, 0, hlit);
    q9_copy32(lens, 288, &mut all, hlit, hdist);
    let mut clf = zeros(19);
    let rextra = q9_rle_stats(&all, hlit.wrapping_add(hdist), &mut clf);
    let mut cl = zeros(19);
    rf_pm(&clf, 0, 19, 7, &mut cl, 0, w, r, c);
    let hclen = q9_hclen_of(&cl);
    let ex = get0(fr, 318) as u64;
    let hdr = 17u64.wrapping_add(3u64.wrapping_mul(hclen as u64)).wrapping_add(q9_dot(&clf, 0, &cl, 0, 19)).wrapping_add(rextra);
    let dynb = hdr.wrapping_add(q9_dot(fr, 0, lens, 0, 288)).wrapping_add(q9_dot(fr, 288, lens, 288, 30)).wrapping_add(ex);
    let fixb = 3u64.wrapping_add(q9_fixed_dot(fr, 0)).wrapping_add(5u64.wrapping_mul(ndist)).wrapping_add(ex);
    q9_bump(fr, 256, 0u32.wrapping_sub(1));
    let raw = get0(fr, 319) as u64;
    let stb = 35u64.wrapping_add(8u64.wrapping_mul(raw));
    let best = if fixb <= dynb { fixb } else { dynb };
    if ndist == 0 && raw < 65536 && stb < best { stb.wrapping_mul(4).wrapping_add(2) }
    else { best.wrapping_mul(4).wrapping_add(if fixb <= dynb { 1 } else { 0 }) }
}

// One table: literals 0..256, lengths 256+len, distances 515+bucket (stride 576).

// entropy price (1/16 bit) of a count f against log2_16(total); unused symbols cost 15 bits.
pub fn rf_ent(f: u32, ltot: u32) -> u32 {
    if f == 0 { return 240; }
    let lf = log2_16(f);
    let v = if ltot > lf { ltot.wrapping_sub(lf) } else { 1 };
    if v > 240 { 240 } else { v }
}
pub fn rf_mix(h: u32, e: u32, model: usize) -> u32 {
    if model == 1 { e } else if model == 2 { (e.wrapping_add(h.wrapping_mul(3))) / 4 } else { h }
}
pub fn rf_lam(x: u32, lam16: usize) -> u32 {
    let l = (lam16 % 64) as u32;
    if l >= 16 { x.wrapping_add(l.wrapping_sub(16)) } else { x.saturating_sub(16u32.wrapping_sub(l)) }
}
pub fn rf_table(lens: &[u32], fr: &[u32], mode: u64, pm: usize, lam16: usize, tab: &mut [u32], off: usize) {
    let lt = log2_16(q9_sum_range(fr, 0, 288) as u32);
    let dt = log2_16(q9_sum_range(fr, 288, 318) as u32);
    let model = if mode == 0 { pm } else { 0 };
    let mut b = 0usize;
    while b < 256 {
        let v = get0(lens, b);
        let x = if mode == 2 { 8 } else if mode == 1 { q9_fixed_len(b) } else if v == 0 { 15 } else { v };
        set_in(tab, off.wrapping_add(b), rf_lam(rf_mix(x.wrapping_mul(16), rf_ent(get0(fr, b), lt), model), lam16));
        b += 1;
    }
    let mut l = 3usize;
    while l <= 258 {
        let lc = q9_lcode(l);
        let v = get0(lens, 257usize.wrapping_add(lc));
        let x = if mode != 0 { q9_fixed_len(257usize.wrapping_add(lc)) } else if v == 0 { 15 } else { v };
        let e = rf_ent(get0(fr, 257usize.wrapping_add(lc)), lt);
        set_in(tab, off.wrapping_add(256+l), rf_lam(rf_mix(x.wrapping_mul(16), e, model).wrapping_add(q9_lextra(lc).wrapping_mul(16)), lam16));
        l += 1;
    }
    let mut d = 0usize;
    while d < 30 {
        let v = get0(lens, 288+d);
        let x = if mode != 0 { 5 } else if v == 0 { 15 } else { v };
        let e = rf_ent(get0(fr, 288+d), dt);
        set_in(tab, off.wrapping_add(515+d), rf_mix(x.wrapping_mul(16), e, model).wrapping_add(q9_dextra(d).wrapping_mul(16)));
        d += 1;
    }
}
pub fn rf_exact(input: &[u8], plan: &[u32], nt: usize, ends: &mut [u32], tab: &mut [u32], w: &mut [u64], r: &mut [u32], c: &mut [u32], pm: usize, lam16: usize) -> u64 {
    let mut fr = zeros(320);
    let mut lens = zeros(320);
    let mut bitpos = 0u64;
    let mut p = 0usize;
    let mut i = 0usize;
    let mut b = 0usize;
    while i < nt {
        q9_clear(&mut fr, 0, 320);
        let mut k = 0usize;
        while k < 16384 && i < nt {
            let x = get0(plan, i);
            let l = (x & 511) as usize;
            let d = (x >> 9) as usize;
            q9_walk_bump(&mut fr, 0, l, d, rf_byte(input, p) as usize);
            p = p.wrapping_add(if l < 3 { 1 } else { l });
            i += 1;
            k += 1;
        }
        let bc = rf_block(&mut fr, &mut lens, w, r, c);
        let mode = bc & 3;
        let bits = (bc >> 2).wrapping_add(if mode == 2 { (8u64.wrapping_sub(bitpos.wrapping_add(3) & 7)) & 7 } else { 0 });
        bitpos = bitpos.wrapping_add(bits);
        set_in(ends, b, p as u32);
        rf_table(&lens, &fr, mode, pm, lam16, tab, b.wrapping_mul(576));
        b = b.wrapping_add(1);
    }
    bitpos.wrapping_add(7) / 8
}
pub fn rf_perturb(tab: &mut [u32], nb: usize, rng0: u64) -> u64 {
    let mut rng = rng0;
    let mut b = 0usize;
    while b < nb {
        let mut j = 0usize;
        while j < 542 {
            // Reference visits 256 literals, lengths 3..258, then 30 distances.
            let s = if j < 256 { j } else if j < 512 { j+3 } else { j+3 };
            rng ^= rng << 13;
            rng ^= rng >> 7;
            rng ^= rng << 17;
            let at = b.wrapping_mul(576).wrapping_add(s);
            let x = get0(tab, at);
            if rng % 3 == 0 {
                let d = (rng >> 8) % 3;
                let v = if d == 0 { x.saturating_sub(16) } else if d == 2 { x.wrapping_add(16) } else { x };
                set_in(tab, at, if v < 16 { 16 } else { v });
            }
            j += 1;
        }
        b += 1;
    }
    rng
}

// Hash chain visits, not retained Pareto entries, are bounded by depth.
// Cached candidates: len bits 0..8, distance bits 9..24, distance bucket bits 25..29.
// One maximum length per distance bucket; smaller equal-length choices retain their original tie order.
pub fn rf_cache_push(cand: &mut Vec<u32>, start: usize, x: u32) {
    let bucket = x >> 25;
    let mut j = start;
    let end = cand.len();
    while j < end {
        let old = get0(cand, j);
        if old >> 25 == bucket {
            if (x & 511) > (old & 511) { set_in(cand, j, x); }
            return;
        }
        j += 1;
    }
    d_push32(cand, x);
}

pub fn rf_find(input: &[u8], seedplan: &[u32], nseed: usize, depth: usize, stride: usize, boost: usize, off: &mut [u32], cand: &mut Vec<u32>) {
    let n = input.len();
    let mut head = zeros(65536);
    let mut prev = zeros(n);
    let mut head4 = zeros(if boost >= 2 { 65536 } else { 0 });
    let mut prev4 = zeros(if boost >= 2 { n } else { 0 });
    let mut p = 0usize;
    let mut carry = 0u32;
    let mut skip = 0usize;
    let mut seedleft = 0usize;
    let mut seeddist = 0usize;
    let mut si = 0usize;
    while p < n {
        if seedleft == 0 && si < nseed {
            let x = get0(seedplan, si);
            let l = (x & 511) as usize;
            seedleft = if l >= 3 { l } else { 1 };
            seeddist = (x >> 9) as usize;
            si += 1;
        }
        let start = cand.len();
        set_in(off, p, start as u32);
        if n-p >= 3 {
            let key = ((rf_byte(input,p) as u32) << 16) | ((rf_byte(input,p+1) as u32) << 8) | rf_byte(input,p+2) as u32;
            let h = (key.wrapping_mul(2654435761) >> 16) as usize;
            let mut cur = get0(&head, h);
            set_in(&mut prev, p, cur);
            set_in(&mut head, h, p.wrapping_add(1) as u32);
            let cap = if n-p < 258 { n-p } else { 258 };
            let mut best = 2usize;
            let mut besttok = 0u32;
            if skip > 0 && (carry & 511) >= 4 {
                let l = ((carry & 511)-1) as usize;
                besttok = (carry & !511) | l as u32;
                rf_cache_push(cand, start, besttok);
                skip -= 1;
            } else {
                let mut step = 0usize;
                while step < depth && cur > 0 && (cur as usize) <= p && best < cap {
                    let q = cur as usize - 1;
                    let d = p-q;
                    if d > 32768 { break; }
                    if rf_byte(input,q+best) == rf_byte(input,p+best) {
                        let l = mlen(input, q, p, cap);
                        if l > best {
                            best = l;
                            besttok = (l as u32) | ((d as u32) << 9) | ((q9_dslot(d) as u32) << 25);
                            rf_cache_push(cand, start, besttok);
                        }
                    }
                    cur = get0(&prev, q);
                    step += 1;
                }
                skip = if best >= 32 { stride.saturating_sub(1) } else { 0 };
            }
            carry = besttok;
            if boost >= 2 && n-p >= 4 {
                let key4 = q9_word4(input, p);
                let h4 = (key4.wrapping_mul(2654435761) >> 16) as usize;
                let mut c4 = get0(&head4, h4);
                set_in(&mut prev4, p, c4);
                set_in(&mut head4, h4, p.wrapping_add(1) as u32);
                let mut best4 = 3usize;
                let mut step4 = 0usize;
                while step4 < depth && c4 > 0 && (c4 as usize) <= p && best4 < cap {
                    let q = c4 as usize - 1;
                    let d = p-q;
                    if d > 32768 { break; }
                    if rf_byte(input,q+best4) == rf_byte(input,p+best4) {
                        let l = mlen(input,q,p,cap);
                        if l > best4 {
                            best4 = l;
                            rf_cache_push(cand, start, l as u32 | ((d as u32) << 9) | ((q9_dslot(d) as u32) << 25));
                        }
                    }
                    c4 = get0(&prev4,q);
                    step4 += 1;
                }
            }
            if boost != 0 && seedleft >= 3 && seeddist > 0 && seeddist <= p {
                let l = if seedleft < cap { seedleft } else { cap };
                rf_cache_push(cand, start, l as u32 | ((seeddist as u32) << 9) | ((q9_dslot(seeddist) as u32) << 25));
            }
        }
        seedleft = seedleft.saturating_sub(1);
        p += 1;
    }
    set_in(off, n, cand.len() as u32);
}

pub fn rf_dp_relax(ring: &mut [u64; 512], prices: &[u32; 1024],
    p: usize, maxlen: usize, base: u64, choice: u32, lo: usize) {
    let mut l = lo;
    while l <= maxlen && l <= 258 {
        let v = base.wrapping_add(prices[(256+l) & 1023] as u64);
        let at = p.wrapping_add(l) & 511;
        if v < ring[at & 511] >> 32 {
            ring[at & 511] = (v << 32) | choice as u64 | l as u64;
        }
        l += 1;
    }
}

pub fn rf_dp(input: &[u8], off: &[u32], cand: &[u32], ends: &[u32], tab: &[u32], back: &mut [u32], out: &mut [u32]) -> usize {
    let n = input.len();
    let mut ring = [0xffffffff00000000u64; 512];
    ring[0] = 0;
    let mut ml = [0u32; 32];
    let mut md = [0u32; 32];
    let mut order = [0u32; 32];
    let mut prices = [0u32; 1024];
    q9_copy32(tab, 0, &mut prices, 0, 545);
    let mut bend = get0(ends, 0) as usize;
    let mut p = 0usize;
    let mut b = 0usize;
    while p < n {
        let state = ring[p & 511];
        set_in(back, p, state as u32);
        ring[p & 511] = 0xffffffff00000000;
        if p >= bend {
            if b+1 < ends.len() { b += 1; }
            bend = get0(ends, b) as usize;
            q9_copy32(tab, b.wrapping_mul(576), &mut prices, 0, 545);
        }
        let cost = state >> 32;
        let lc = cost.wrapping_add(prices[rf_byte(input,p) as usize] as u64);
        let at = (p+1) & 511;
        if lc < ring[at & 511] >> 32 { ring[at & 511] = (lc << 32) | 1; }
        let mut j = get0(off,p) as usize;
        let e = get0(off,p+1) as usize;
        let mut k = 0usize;
        while j < e {
            let x = get0(cand,j);
            let bucket = ((x >> 25) & 31) as usize;
            let l = x & 511;
            if ml[bucket & 31] == 0 {
                let pr = prices[(515+bucket) & 1023];
                let mut q = k;
                while q > 0 {
                    let ob = order[(q-1) & 31] as usize;
                    let op = prices[515usize.wrapping_add(ob) & 1023];
                    if op < pr || (op == pr && ob < bucket) { break; }
                    order[q & 31] = ob as u32;
                    q -= 1;
                }
                order[q & 31] = bucket as u32;
                k = k.wrapping_add(1);
            }
            if l > ml[bucket & 31] {
                ml[bucket & 31] = l;
                md[bucket & 31] = x & 0x1ffffff;
            }
            j += 1;
        }
        let mut lo = 3usize;
        let mut t = 0usize;
        while t < k && t < 32 {
            let bucket = order[t & 31] as usize;
            let maxlen = ml[bucket & 31] as usize;
            let base = cost.wrapping_add(prices[515usize.wrapping_add(bucket) & 1023] as u64);
            let choice = md[bucket & 31] & !511;
            rf_dp_relax(&mut ring, &prices, p, maxlen, base, choice, lo);
            if maxlen >= lo { lo = maxlen.wrapping_add(1); }
            ml[bucket & 31] = 0;
            t += 1;
        }
        p += 1;
    }
    set_in(back,n,ring[n & 511] as u32);
    let mut nt = 0usize;
    while p > 0 {
        let x = get0(back,p);
        let l = (x & 511) as usize;
        let len = if l < 3 || l > p { 1 } else { l };
        set_in(out,nt,if len == 1 { 0 } else { x });
        nt = nt.wrapping_add(1);
        p -= len;
    }
    let mut i = 0usize;
    while i < nt/2 {
        let x = get0(out,i);
        let j = nt-1-i;
        set_in(out,i,get0(out,j));
        set_in(out,j,x);
        i += 1;
    }
    nt
}

pub fn refine(input: &[u8], seed: &[u32], nseed: usize, cfg: usize) -> Vec<u32> {
    let n = input.len();
    if n == 0 || n >= 16777216 || nseed > n || nseed > seed.len() { return Vec::new(); }
    let conf = RF_CONFIG[cfg % 64];
    if conf[1] == 0 { return Vec::new(); }
    let mut cur = zeros(n);
    let mut i = 0usize;
    while i < nseed {
        let t = get0(seed,i);
        let v = if t < 256 { 0 } else {
            let x = t.wrapping_sub(16777216);
            ((x & 255)+3) | ((x.wrapping_shr(8).wrapping_add(1)) << 9)
        };
        set_in(&mut cur,i,v);
        i += 1;
    }
    let mut ends = zeros(n/16384+1);
    let mut tab = zeros((n/16384+1)*576);
    let mut w = rf_zeros64(16384);
    let mut r = zeros(16384);
    let mut c = zeros(16384);
    let seedbytes = rf_exact(input,&cur,nseed,&mut ends,&mut tab,&mut w,&mut r,&mut c,conf[5],conf[6]);
    let mut off = zeros(n+1);
    let mut cand = Vec::with_capacity(n);
    rf_find(input,&cur,nseed,conf[0],conf[2],conf[4],&mut off,&mut cand);
    let mut back = zeros(n+1);
    let mut best = zeros(n);
    let mut bestbytes = 18446744073709551615u64;
    let mut bestnt = 0usize;
    let mut rng = 0x9E3779B97F4A7C15u64;
    let mut it = 0usize;
    while it < conf[1] && it < 16 {
        let nt = rf_dp(input,&off,&cand,&ends,&tab,&mut back,&mut cur);
        let bytes = rf_exact(input,&cur,nt,&mut ends,&mut tab,&mut w,&mut r,&mut c,conf[5],conf[6]);
        if bytes < bestbytes {
            bestbytes = bytes;
            bestnt = nt;
            q9_copy32(&cur,0,&mut best,0,nt);
        } else if conf[3] > 0 {
            rf_exact(input,&best,bestnt,&mut ends,&mut tab,&mut w,&mut r,&mut c,conf[5],conf[6]);
            rng = rf_perturb(&mut tab,bestnt.wrapping_add(16383)/16384,rng);
        }
        it += 1;
    }
    let mut result = Vec::new();
    if bestbytes < seedbytes {
        let mut j = 0usize;
        while j < bestnt { result.push(get0(&best,j)); j += 1; }
    }
    result
}

// ═══ r17 refine: END ═══
