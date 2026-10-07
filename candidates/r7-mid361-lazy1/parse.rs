//! Combined host (r25/port of r23/host assembly h2): mB's lazy engine, the DNA-lite planner, the forward dynamic
//! program (r23/lc's finder; its cost-model globals per DP_KNOBS row), engine D and S's engine C behind S's content
//! router, with both emission loops.
//!
//! `parse` takes the input's routing class (`route_class`: `classify`'s byte-class shares over 32 sampled
//! windows of 1 KiB, the tiny inputs split by size, multi-byte text and prose split off default text) and looks
//! it up in `CLASS_TAB`: an engine and a row of that engine's knob table.
//! * Engine 0, the positional planner slot (`s_plan`): S's engine C (DNA and binary data), a row of `CFG`. Its plan is POSITIONAL
//!   (`plan[p] = len + 512 * dist` for position `p`, `len < 3` a literal), re-checked by `emit_pos`.
//! * Engine 1, the forward dynamic program (`dp_plan`, a row of `DP_KNOBS`: search knobs and the long-chain key,
//!   cost-update interval, count-halving threshold and backward-extension limit): a TOKEN LIST plan
//!   (entry k = the k-th planned token, `len | dist << 9`, 0 for a literal), re-checked by `emit`.
//! * Engine 2, engine D (`d_plan`, a row of `D_KNOBS`): the forward dynamic program with every searched
//!   position recorded, then a backward shortest path under per-encoder-block Huffman-length costs; a
//!   token list re-checked by `emit`.
//! * Engine 3, mB's lazy engine (`lazy_parse`: its own sniffed class `a_sniff` picks its settings, the row
//!   is its level, 1 full / 0 lighter text settings); it writes its tokens directly and is proved in full.
//! * Engine 4, the DNA-lite planner (`dna_plan`): cheap bytes (the four common bases) as literal runs,
//!   matches searched only at expensive bytes; a token list re-checked by `emit`.
//! Every planner is untrusted search code (totality only): the emission loops re-check every planned match
//! (`check`: range tests, then `mlen` compares 8 bytes at a time).
//! Tokens: t < 256 literal, else 2^24 + (dist-1)*256 + (len-3).

// ════════════════════ tables: BEGIN (r23/host mock defaults; constant values only) ════════════════════
// table set: T1750 (055f49267db8)

/// Classifier splits. A tiny input (below 32 KiB) is class 14 below TINY_SPLIT bytes and class 0 from there on.
pub const TINY_SPLIT: usize = 20000;
/// Default text with at least MB_HI/1000 of the sampled bytes >= 128 is class 13 (multi-byte text).
pub const MB_HI: usize = 148;
/// Default text whose strided sample has at least PROSE_W/1024 letters and spaces and at most PROSE_S/1024
/// code symbols is class 15 (prose). PROSE_W above 1024 switches this split and its sampling off.
pub const PROSE_W: usize = 878;
pub const PROSE_S: usize = 16;

/// Routing class -> [engine, knob row]. Engine 2: engine D (row of D_KNOBS), 1: the forward dynamic program
/// (row of DP_KNOBS), 3: the lazy engine (row = its level), 4: the DNA-lite planner (row unused), anything
/// else: the positional planner slot (row of CFG: engine C).
pub const CLASS_TAB: [[usize; 2]; 16] = [
    [3, 1],  // 0  LZ tiny input (< 32 KiB), at least TINY_SPLIT bytes
    [0, 1],  // 1  C  DNA
    [3, 1],  // 2  LZ sparse (mostly zero bytes)
    [0, 2],  // 3  C  binary with high-byte noise (weights, images, compressed)
    [2, 1],  // 4  D  binary with structure (databases, machine code)
    [1, 0],  // 5  DP markup, many lines (XML)
    [1, 0],  // 6  DP markup, few lines (HTML)
    [2, 3],  // 7  D  numeric table with quotes and commas (CSV)
    [2, 4],  // 8  D  numeric rows with commas (SQL dump)
    [3, 1],  // 9  LZ numeric lines (logs)
    [1, 2],  // 10 DP quoted text (JSON)
    [1, 3],  // 11 DP long lines (minified code, source maps)
    [1, 4],  // 12 DP default text (docs, source code, config)
    [1, 5],  // 13 DP multi-byte text
    [2, 0],  // 14 D  tiny input (< 32 KiB), below TINY_SPLIT bytes
    [1, 6],  // 15 DP prose
];

/// Engine C configurations: [unused (engine A removed), depth, lower-case depth, weights DP, weights passes,
/// tree passes, DNA passes, DNA min passes, chain4 passes].
pub const CFG: [[usize; 9]; 16] = [
    [2, 24, 24, 1, 3, 2, 8, 7, 2],  // 0 filler (unused)
    [2, 24, 24, 1, 3, 2, 8, 7, 2],  // 1 genome
    [2, 48, 12, 0, 1, 1, 4, 4, 1],  // 2 hbin
    [2, 24, 24, 1, 3, 2, 8, 7, 2],  // 3 unused (= row 0)
    [2, 24, 24, 1, 3, 2, 8, 7, 2],  // 4 unused (= row 0)
    [2, 24, 24, 1, 3, 2, 8, 7, 2],  // 5 unused (= row 0)
    [2, 24, 24, 1, 3, 2, 8, 7, 2],  // 6 unused (= row 0)
    [2, 24, 24, 1, 3, 2, 8, 7, 2],  // 7 unused (= row 0)
    [2, 24, 24, 1, 3, 2, 8, 7, 2],  // 8 unused (= row 0)
    [2, 24, 24, 1, 3, 2, 8, 7, 2],  // 9 unused (= row 0)
    [2, 24, 24, 1, 3, 2, 8, 7, 2],  // 10 unused (= row 0)
    [2, 24, 24, 1, 3, 2, 8, 7, 2],  // 11 unused (= row 0)
    [2, 24, 24, 1, 3, 2, 8, 7, 2],  // 12 unused (= row 0)
    [2, 24, 24, 1, 3, 2, 8, 7, 2],  // 13 unused (= row 0)
    [2, 24, 24, 1, 3, 2, 8, 7, 2],  // 14 unused (= row 0)
    [2, 24, 24, 1, 3, 2, 8, 7, 2],  // 15 unused (= row 0)
];

/// Knob rows of the forward dynamic program: [ct (continuation threshold), lazy positions searched, d4 and d7
/// (chain depths), skip (take-as-is length), h3 distance, huff (1 = Huffman-length costs), kb7 (long-chain key
/// bytes, clamped to 1..8), upd (cost-update interval in positions, clamped to 1048576), half (counts are halved
/// above this many symbols, clamped to 2^32 - 1), tmax (backward-extension limit in bytes; above 255 = none)].
/// Any values are safe (the forward DP clamps columns 7-9); h2's globals were [7, 2048, 10000, 64].
pub const DP_KNOBS: [[usize; 11]; 16] = [
    [4, 1, 2, 16, 64, 32768, 0, 8, 8192, 8000, 64],  // 0 xml+html
    [4, 1, 2, 16, 64, 32768, 0, 8, 8192, 8000, 64],  // 1 filler (unused)
    [4, 1, 2, 24, 128, 32768, 0, 8, 8192, 8000, 64],  // 2 json
    [3, 1, 1, 16, 64, 32768, 0, 8, 4096, 10000, 64],  // 3 long
    [3, 1, 2, 32, 64, 32768, 0, 7, 2048, 10000, 64],  // 4 text
    [4, 1, 2, 24, 128, 32768, 0, 7, 2048, 10000, 64],  // 5 mbyte
    [4, 1, 4, 48, 32, 32768, 0, 7, 2048, 10000, 64],  // 6 prose
    [4, 1, 2, 16, 64, 32768, 0, 8, 8192, 8000, 64],  // 7 unused (= row 0)
    [4, 1, 2, 16, 64, 32768, 0, 8, 8192, 8000, 64],  // 8 unused (= row 0)
    [4, 1, 2, 16, 64, 32768, 0, 8, 8192, 8000, 64],  // 9 unused (= row 0)
    [4, 1, 2, 16, 64, 32768, 0, 8, 8192, 8000, 64],  // 10 unused (= row 0)
    [4, 1, 2, 16, 64, 32768, 0, 8, 8192, 8000, 64],  // 11 unused (= row 0)
    [4, 1, 2, 16, 64, 32768, 0, 8, 8192, 8000, 64],  // 12 unused (= row 0)
    [4, 1, 2, 16, 64, 32768, 0, 8, 8192, 8000, 64],  // 13 unused (= row 0)
    [4, 1, 2, 16, 64, 32768, 0, 8, 8192, 8000, 64],  // 14 unused (= row 0)
    [4, 1, 2, 16, 64, 32768, 0, 8, 8192, 8000, 64],  // 15 unused (= row 0)
];

/// Knob rows of engine D: [ct, lazyn, d4, d7, skip, h3d, passes, pmode, flen, tbmax, lz2max, dupmode, fback (100 =
/// the dynamic program's relax_cands), d7 at lazy nodes, d7 at end-zone nodes, nice, cost kind].
pub const D_KNOBS: [[usize; 17]; 16] = [
    [4, 1, 2, 48, 32, 32768, 1, 1, 8, 255, 258, 1, 0, 48, 24, 258, 0],  // 0 tinycfg
    [4, 1, 2, 48, 32, 32768, 1, 1, 16, 255, 258, 1, 16, 24, 48, 258, 0],  // 1 sbin
    [4, 1, 2, 48, 32, 32768, 1, 1, 8, 255, 258, 1, 0, 48, 24, 258, 0],  // 2 filler (unused)
    [4, 1, 2, 48, 128, 32768, 1, 1, 16, 255, 258, 1, 16, 24, 24, 258, 2],  // 3 csv
    [4, 1, 2, 48, 160, 32768, 1, 1, 16, 255, 258, 1, 16, 8, 24, 258, 0],  // 4 sql
    [4, 1, 2, 48, 32, 32768, 1, 1, 8, 255, 258, 1, 0, 48, 24, 258, 0],  // 5 unused (= row 0)
    [4, 1, 2, 48, 32, 32768, 1, 1, 8, 255, 258, 1, 0, 48, 24, 258, 0],  // 6 unused (= row 0)
    [4, 1, 2, 48, 32, 32768, 1, 1, 8, 255, 258, 1, 0, 48, 24, 258, 0],  // 7 unused (= row 0)
    [4, 1, 2, 48, 32, 32768, 1, 1, 8, 255, 258, 1, 0, 48, 24, 258, 0],  // 8 unused (= row 0)
    [4, 1, 2, 48, 32, 32768, 1, 1, 8, 255, 258, 1, 0, 48, 24, 258, 0],  // 9 unused (= row 0)
    [4, 1, 2, 48, 32, 32768, 1, 1, 8, 255, 258, 1, 0, 48, 24, 258, 0],  // 10 unused (= row 0)
    [4, 1, 2, 48, 32, 32768, 1, 1, 8, 255, 258, 1, 0, 48, 24, 258, 0],  // 11 unused (= row 0)
    [4, 1, 2, 48, 32, 32768, 1, 1, 8, 255, 258, 1, 0, 48, 24, 258, 0],  // 12 unused (= row 0)
    [4, 1, 2, 48, 32, 32768, 1, 1, 8, 255, 258, 1, 0, 48, 24, 258, 0],  // 13 unused (= row 0)
    [4, 1, 2, 48, 32, 32768, 1, 1, 8, 255, 258, 1, 0, 48, 24, 258, 0],  // 14 unused (= row 0)
    [4, 1, 2, 48, 32, 32768, 1, 1, 8, 255, 258, 1, 0, 48, 24, 258, 0],  // 15 unused (= row 0)
];
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
/// Engine D's long chain key length in bytes (5..8). The forward DP takes its own from DP_KNOBS column 7.
pub const KB7: u32 = 7;
/// Engine D's symbol costs are rebuilt every UPD positions; counts are halved above HALF_AT symbols. The forward
/// DP takes its own from DP_KNOBS columns 8 and 9.
pub const UPD: usize = 2048;
pub const HALF_AT: u32 = 10000;
pub const INF: u32 = 0x3FFF_FFFF;
pub const UNREACHED: u64 = 0x3FFF_FFFF_0000_0000;
/// Backward extension: at most TMAX bytes (engine D's `relax_cands` path; the forward DP takes its own limit from
/// DP_KNOBS column 10), for the BEXT_TOP longest candidates of a position.
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

/// The whole parser: the input's routing class picks an engine and a knob row (`CLASS_TAB`). Plans are re-checked by
/// the emission loop of their encoding (`emit`: token lists, `emit_pos`: positional plans); the lazy engine writes its
/// tokens directly.
pub fn parse(input: &[u8], out: &mut [u32]) -> usize {
    let cls = route_class(input);
    let e = CLASS_TAB[cls % 16];
    if e[0] == 2 {
        let plan = d_plan(input, out, e[1]);
        emit(input, &plan, out)
    } else if e[0] == 1 {
        let plan = dp_plan(input, e[1]);
        emit(input, &plan, out)
    } else if e[0] == 3 {
        lazy_parse(input, out, e[1])
    } else if e[0] == 4 {
        let plan = dna_plan(input);
        emit(input, &plan, out)
    } else {
        let plan = s_plan(input, e[1]);
        emit_pos(input, &plan, out)
    }
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
pub fn plan_cfg(input: &[u8], k: usize) -> Vec<u32> {
    let n = input.len();
    let mut plan = zeros(n);
    let c = CFG[k % 16];
    c_engine(input, &mut plan, c[1], c[2], c[3], c[4], c[5], c[6], c[7], c[8]);
    plan
}

/// Phase 1 for the positional slot (engine C): configuration row `k` of CFG. Inputs of 2^26 bytes or more get an empty plan
/// (all literals): the engines' index arithmetic is proved total below that size.
#[inline(never)]
pub fn s_plan(input: &[u8], k: usize) -> Vec<u32> {
    if input.len() >= 67108864 {
        return Vec::new();
    }
    plan_cfg(input, k)
}

/// The lazy engine (mB): its own sniffed class picks its settings; `lvl` 1 = full settings, 0 = lighter text settings.
/// It writes its tokens directly (proved in full: every token decodes to the input).
#[inline(never)]
pub fn lazy_parse(input: &[u8], out: &mut [u32], lvl: usize) -> usize {
    let c = a_sniff(input);
    a_parse_cls(input, out, c, lvl)
}

/// Phase 1 for the forward dynamic program with knob row `r` of DP_KNOBS: the plan (a token list). Every
/// entry is a suggestion; `emit` checks each one.
#[inline(never)]
pub fn dp_plan(input: &[u8], r: usize) -> Vec<u32> {
    let n = input.len();
    let k = DP_KNOBS[r % DP_NK];
    let mut plan: Vec<u32> = Vec::with_capacity(n / 2 + 16);
    if n >= 16 && n.wrapping_add(n) > n {
        dp_parse(input, &mut plan, k[0], k[1], k[2], k[3], k[4], k[5], k[6], k[7], k[8], k[9], k[10]);
    }
    plan
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
pub fn route_class(input: &[u8]) -> usize {
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

/// Halve the counts when they exceed `half` symbols, then rebuild the costs.
pub fn update_costs_h(
    lf: &mut [u32; 320],
    df: &mut [u32; 32],
    lsym: &[u8; 512],
    litc: &mut [u32; 256],
    lc: &mut [u32; 512],
    dcc: &mut [u32; 32],
    huff: usize,
    half: u32,
) {
    let mut tot = 0u32;
    let mut z = 0usize;
    while z < 286 {
        tot = tot.wrapping_add(lf[z]);
        z += 1;
    }
    if tot > half {
        halve(lf, df);
    }
    make_costs(lf, df, lsym, litc, lc, dcc, huff);
}

/// `update_costs_h` at engine D's threshold HALF_AT.
pub fn update_costs(
    lf: &mut [u32; 320],
    df: &mut [u32; 32],
    lsym: &[u8; 512],
    litc: &mut [u32; 256],
    lc: &mut [u32; 512],
    dcc: &mut [u32; 32],
    huff: usize,
) {
    update_costs_h(lf, df, lsym, litc, lc, dcc, huff, HALF_AT);
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

/// Walk a chain from `start` for at most `depth` steps: push each match longer than all
/// before it as `len | dist << 9`. Returns (count, longest).
#[inline(always)]
pub fn walk(
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
) -> (usize, usize) {
    let mut nc = nc0;
    let mut best = best0;
    let mut c = start;
    let mut k = depth;
    while k > 0 {
        let d = i.wrapping_sub(c);
        if d.wrapping_sub(1) < 32768 && best < cap && nc < 15 {
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

/// Among the starts i-1 .. i-t of a candidate extended backwards (t <= tmax), the one
/// where arriving and then taking the whole match (to i + len) is cheapest: (t, cost).
#[inline(always)]
pub fn back_best(input: &[u8], pa: &[u64; RING], lc: &[u32; 512], i: usize, s: usize, len: usize, dd: usize, tmax: usize) -> (usize, u32) {
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
            let r = back_best(input, pa, lc, i, s, len, dd, TMAX);
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

/// The long-chain hash shift for a key of `kb7` bytes (DP_KNOBS column 7, clamped to 1..8): `b8 >> (sh7 % 64)`
/// keeps the key's bytes.
#[inline(always)]
pub fn dp_sh7(kb7: usize) -> u32 {
    if kb7 >= 8 {
        0
    } else if kb7 == 0 {
        56
    } else {
        64 - 8 * (kb7 as u32)
    }
}

/// The cost-update interval (DP_KNOBS column 8), at most 1048576 positions.
#[inline(always)]
pub fn dp_upd(upd: usize) -> usize {
    if upd > 1048576 {
        1048576
    } else {
        upd
    }
}

/// The count-halving threshold (DP_KNOBS column 9) as a `u32` (at most 2^32 - 1).
#[inline(always)]
pub fn dp_half(half: usize) -> u32 {
    if half > 4294967295 {
        4294967295
    } else {
        half as u32
    }
}

// ─────────── r23/lc's finder (search code, totality only): same candidates and relaxations as walk / relax_cands ───────────

/// The word compared by the tail test for the current best: bytes best-7 .. best of position i (0 below 8).
#[inline(always)]
pub fn tailw(s: &[u8], i: usize, best: usize) -> u64 {
    if best >= 8 {
        be8(s, i.wrapping_add(best).wrapping_sub(7))
    } else {
        0
    }
}

/// `walk` with tail-word rejection (same candidates): once `best >= 8`, a node can only win if the eight
/// bytes ending at offset `best` agree, so one word compare against `tw` = `tailw(s, i, best)` rejects
/// it before `probe` (below 8 both words are 0: every node goes to `probe`).
#[inline(always)]
pub fn walk_t(
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
) -> (usize, usize) {
    let mut nc = nc0;
    let mut best = best0;
    let mut tw = tailw(s, i, best);
    let mut c = start;
    let mut k = depth;
    while k > 0 {
        let d = i.wrapping_sub(c);
        if d.wrapping_sub(1) < 32768 && best < cap && nc < 15 {
            if tailw(s, c, best) == tw {
                let l = probe(s, c, i, b8, cap, best);
                if l > 0 && nc < 15 {
                    cands[nc % 16] = (l as u32) | ((d as u32) << 9);
                    nc += 1;
                    best = l;
                    tw = tailw(s, i, best);
                }
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

/// The three table indices of a position whose eight bytes are `b8` (nearest 3-byte, 4-byte chain, long chain).
#[inline(always)]
pub fn hashes(b8: u64, sh7: u32) -> (usize, usize, usize) {
    let x4 = (b8 >> 32) as u32;
    (hash3(x4 >> 8), hash4(x4), hash7(b8 >> (sh7 % 64)))
}

/// Insert position `i` into the three tables: the heads at the indices `x3`, `x4`, `x7` become `i`, the chains link
/// `i` to the old 4-byte and long-chain heads `c4`, `c7` (read one iteration early by `dp_heads`).
#[inline(always)]
pub fn dp_store(
    head3: &mut [u32; H3N],
    head4: &mut [u32; H4N],
    prev4: &mut [u32; WN],
    head7: &mut [u32; H7N],
    prev7: &mut [u32; WN],
    i: usize,
    x3: usize,
    x4: usize,
    x7: usize,
    c4: usize,
    c7: usize,
) {
    let q = i as u32;
    let p4 = c4 as u32;
    let p7 = c7 as u32;
    head3[x3 % H3N] = q;
    head4[x4 % H4N] = q;
    prev4[i % WN] = p4;
    head7[x7 % H7N] = q;
    prev7[i % WN] = p7;
}

/// The heads at the table indices `x3`, `x4`, `x7`: (nearest 3-byte position, 4-byte chain head, long chain head).
#[inline(always)]
pub fn dp_heads(head3: &[u32; H3N], head4: &[u32; H4N], head7: &[u32; H7N], x3: usize, x4: usize, x7: usize) -> (usize, usize, usize) {
    (head3[x3 % H3N] as usize, head4[x4 % H4N] as usize, head7[x7 % H7N] as usize)
}

/// Relax lengths lo..=hi (below 512) of one candidate from position i.
#[inline(always)]
pub fn relax_seq(pa: &mut [u64; RING], lc: &[u32; 512], i: usize, lo: usize, hi: usize, base: u32, dpack: u32) {
    let mut l = lo;
    while l <= hi && l < 512 {
        let c = base.wrapping_add(lc[l % 512]);
        let slot = i.wrapping_add(l) % RING;
        let v = ((c as u64) << 32) | ((dpack | l as u32) as u64);
        let old = pa[slot];
        pa[slot] = if v < old { v } else { old };
        l += 1;
    }
}

/// `relax_cands` with sequential lengths (the host's relax_run + nextl with every length tried) and the
/// backward-extension limit `tmax`.
#[inline(always)]
pub fn rc_seq(
    input: &[u8],
    pa: &mut [u64; RING],
    cands: &[u32; 16],
    nc: usize,
    lc: &[u32; 512],
    dtab: &[u8; 512],
    dcc: &[u32; 32],
    i: usize,
    s: usize,
    base: u32,
    pcd: usize,
    tmax: usize,
) {
    let mut lo = 3usize;
    let mut k = 0usize;
    while k < nc && k < 16 {
        let c = cands[k];
        let len = (c % 512) as usize;
        let dd = (c >> 9) as usize;
        let ds = dsym(dtab, dd) % 32;
        let bd = base.wrapping_add(dcc[ds]);
        relax_seq(pa, lc, i, lo, len, bd, c & !511u32);
        lo = len + 1;
        if dd != pcd && (k + BEXT_TOP >= nc) {
            let r = back_best(input, pa, lc, i, s, len, dd, tmax);
            if r.0 > 0 {
                relax_one(pa, i + len, r.1.wrapping_add(dcc[ds]), (c & !511u32) | (len + r.0) as u32);
                if BTRUNC == 1 {
                    let j = i - r.0;
                    let pj = (pa[j % RING] >> 32) as u32;
                    relax_seq(pa, lc, j, r.0 + 3, r.0 + len - 1, pj.wrapping_add(dcc[ds]), c & !511u32);
                }
            }
        }
        k += 1;
    }
}

/// The forward dynamic program with the knobs of one DP_KNOBS row (search code: totality only; `emit` re-checks
/// every planned match). The cost model's settings come from the row: `kb7` (long-chain key bytes), `upd`
/// (cost-update interval), `half` (count-halving threshold), `tmax` (backward-extension limit); `dp_sh7`,
/// `dp_upd`, `dp_half` clamp them, `tmax` needs no clamp (`back_best` stops below length 258).
/// r23/lc's finder, same output as the h2 host's search: (1) software-pipelined inserts (the hashes and the three
/// head reads of position i + 1 are issued in iteration i, after the head stores of i, so a same-hash i + 1 reads
/// i; the loop carries `b8`, `hh`, `pre`; after a taken match they are read fresh), (2) the long chain is walked by
/// `walk_t` (tail-word rejection), (3) the candidates are relaxed by `rc_seq` (every length, `relax_seq`).
pub fn dp_parse(input: &[u8], plan: &mut Vec<u32>, ct: usize, lazyn: usize, d4: usize, d7: usize, skip: usize, h3d: usize, huff: usize,
    kb7: usize, upd: usize, half: usize, tmax: usize) {
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
    let sh7 = dp_sh7(kb7);
    let updn = dp_upd(upd);
    let halfn = dp_half(half);
    let mut s = 0usize; // chunk start
    open_chunk(&mut pa, 0);
    let mut next_upd = updn;
    let mut cands = [0u32; 16];
    let mut cl = 0usize; // continuation of the previous position's longest candidate
    let mut cd = 0usize;
    let mut cdc = 0u32; // its distance cost
    let mut i = 0usize;
    let mut anchor = 0usize; // the position that found the current longest candidate
    let mut alen = 0usize; // the longest candidate length found at the anchor
    // pipelined: the eight bytes, table indices and old heads of position i
    let mut b8 = be8(input, 0);
    let mut hh = hashes(b8, sh7);
    let mut pre = dp_heads(&head3, &head4, &head7, hh.0, hh.1, hh.2);
    while i < lim {
        if i > s {
            pa[(i + 258) % RING] = UNREACHED;
        }
        // insert i (heads read one iteration early)
        let hc = pre;
        dp_store(&mut head3, &mut head4, &mut prev4, &mut head7, &mut prev7, i, hh.0, hh.1, hh.2, hc.1, hc.2);
        // the next position's bytes, indices and heads (after the stores above)
        let b8n = be8(input, i.wrapping_add(1));
        let hn = hashes(b8n, sh7);
        let pn1 = dp_heads(&head3, &head4, &head7, hn.0, hn.1, hn.2);
        let base = (pa[i % RING] >> 32) as u32;
        // literal
        relax_one(&mut pa, i + 1, base.wrapping_add(litc[(b8 >> 56) as usize % 256]), 0);
        // the LAZYN positions right after the one that found the current match are searched too
        let lzn = if alen <= LZ2MAX { lazyn } else { 1 };
        let lazy_here = i.wrapping_sub(anchor).wrapping_sub(1) < lzn;
        let mut jumped = false;
        if cl >= ct && cl >= 3 && !lazy_here {
            // inside a match: only the continuation's full length (it ends where it did)
            relax_one(&mut pa, i + cl, base.wrapping_add(cdc).wrapping_add(lc[cl % 512]), ((cd as u32) << 9) | cl as u32);
            cl -= 1;
            i += 1;
        } else {
            let mut cap = n - i;
            if cap > 258 {
                cap = 258;
            }
            // candidates: nearest 3-byte match, 4-byte chain, long chain, continuation
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
            // a chain head equal to a position already probed is stepped over (same result)
            let s4 = skip_same(&prev4, hc.1, d4, p3 && hc.1 == hc.0);
            let w = walk(input, &prev4, i, s4.0, s4.1, b8, cap, &mut cands, nc, best);
            nc = w.0;
            best = w.1;
            let dep7 = if best >= 4 || d4 == 0 { d7 } else { 0 };
            let s7 = skip_same(&prev7, hc.2, dep7, (p3 && hc.2 == hc.0) || (d4 > 0 && hc.2 == hc.1));
            let w2 = walk_t(input, &prev7, i, s7.0, s7.1, b8, cap, &mut cands, nc, best);
            nc = w2.0;
            best = w2.1;
            if cl > best && cl <= cap {
                // the continuation is the longest: drop farther shorter candidates, append it
                nc = drop_farther(&cands, nc, cd);
                cands[nc % 16] = (cl as u32) | ((cd as u32) << 9);
                if nc < 16 {
                    nc += 1;
                }
                best = cl;
            }
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
                // take the longest candidate, extended backwards, as is; close the chunk before it
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
                jumped = true;
            } else {
                rc_seq(input, &mut pa, &cands, nc, &lc, &dtab, &dcc, i, s, base, pcd, tmax);
                i += 1;
            }
        }
        // the pipeline: after a jump the heads of the new i are read fresh (the range inserts changed them)
        if jumped {
            b8 = be8(input, i);
            hh = hashes(b8, sh7);
            pre = dp_heads(&head3, &head4, &head7, hh.0, hh.1, hh.2);
        } else {
            b8 = b8n;
            hh = hn;
            pre = pn1;
        }
        if i - s >= CHUNK {
            backtrack(input, &pa, plan, s, i, &lsym, &dtab, &mut lf, &mut df, &mut tb);
            s = i;
            open_chunk(&mut pa, s);
        }
        if i >= next_upd {
            next_upd = i + updn;
            update_costs_h(&mut lf, &mut df, &lsym, &mut litc, &mut lc, &mut dcc, huff, halfn);
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

/// nextl[l]: the next length to try after l (every length below `flen`, then the last length of each length code).
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

// ───────────────────────── lazy engine (mA lineage, names prefixed a_/A_) ─────────────────────────

pub const A_HB: u32 = 15;
pub const A_HN: usize = 32768;
pub const A_WN: usize = 32768;
/// Inputs of at most A_SMALL bytes use A_HS chain heads and a A_WS window table.
pub const A_SMALL: usize = 65536;
pub const A_HS: usize = 16384;
pub const A_WS: usize = 32768;
pub const A_NICE: usize = 258;
pub const A_INS_MAX: usize = 258;
pub const A_TAIL: usize = 8;
/// Inside long matches, every A_STRIDE-th position between the head and the tail is chained
/// too (A_STRIDE = 0: none).
pub const A_STRIDE: usize = 1;
pub const A_BACKTOK: usize = 16;
pub const A_LDEPTH: usize = 64;
pub const A_SAMPLE: usize = 2048;
pub const A_VERIFY: usize = 0;
/// Lazy step: a candidate at p+1 needs length >= l + 1 - A_LSLACK (A_LSLACK = 1: at least as long
/// as the current match l) and must win on estimated saving (literal worth A_HLIT/16 bits,
/// match base cost A_GBASE/16 bits plus extra bits).
pub const A_LSLACK: usize = 1;
pub const A_HLIT: u32 = 64;
/// Literal worth (1/16 bit) in the saving estimate for binary classes (3 and 7).
pub const A_B_HLIT: u32 = 64;
pub const A_GBASE: i32 = 168;
/// Per class: main chain depth, lazy threshold, skip shift, skip cap (T text, P prose,
/// H high-entropy binary, Z high-entropy binary rich in zero bytes, B other binary,
/// DNA-like input is sent as literals).
pub const A_T_DEPTH: usize = 256;
/// Lighter text settings (level 0): walk depth, insertion head, stride, two-step lazy depth, partial merge.
pub const A_T_DEPTH0: usize = 24;
pub const A_INS_MAX0: usize = 128;
pub const A_STRIDE0: usize = 2;
pub const A_L2DEPTH0: usize = 2;
pub const A_PARTIAL0: usize = 0;
pub const A_T_LAZY: usize = 258;
pub const A_T_SKIP: usize = 5;
pub const A_P_DEPTH: usize = 128;
pub const A_P_LAZY: usize = 258;
pub const A_P_SKIP: usize = 5;
pub const A_H_DEPTH: usize = 2;
pub const A_H_LAZY: usize = 0;
pub const A_H_SKIP: usize = 4;
pub const A_Z_DEPTH: usize = 3;
pub const A_Z_SKIP: usize = 8;
pub const A_Z_CAP: usize = 8;
pub const A_B_DEPTH: usize = 32;
pub const A_B_LAZY: usize = 258;
pub const A_B_SKIP: usize = 8;
/// Structured text (class 6: text with at least 1/A_SDIG of the sample in digits): main depth
/// A_S_DEPTH, lazy a_walk depth A_S_LDEPTH, lazy threshold A_S_LAZY.
pub const A_SDIG: u32 = 6;
pub const A_S_DEPTH: usize = 32;
pub const A_S_LDEPTH: usize = 16;
pub const A_S_LAZY: usize = 258;
/// Largest skip step (extra literals per miss) outside the Z class.
pub const A_SKCAP: usize = 1000000;
/// Per-class a_walk stop (A_NICE is the text value), lazy a_walk depth (A_LDEPTH is the text value),
/// insertion inside matches (A_INS_MAX/A_STRIDE/A_TAIL are the text values).
pub const A_P_NICE: usize = 258;
pub const A_S_NICE: usize = 258;
pub const A_H_NICE: usize = 32;
pub const A_Z_NICE: usize = 32;
pub const A_B_NICE: usize = 258;
pub const A_P_LDEPTH: usize = 8;
pub const A_H_LDEPTH: usize = 1;
pub const A_B_LDEPTH: usize = 2;
pub const A_P_INS: usize = 258;
pub const A_S_INS: usize = 258;
pub const A_B_INS: usize = 64;
pub const A_H_INS: usize = 12;
pub const A_P_STRIDE: usize = 1;
pub const A_S_STRIDE: usize = 1;
pub const A_B_STRIDE: usize = 4;
/// Two-step lazy: when p+1 does not beat the pending match, p+2 is tried (A_L2DEPTH chain steps)
/// and wins if its saving beats the pending one by more than A_L2B/16 bits (A_LAZY2 = 1; 0 = off).
pub const A_LAZY2: usize = 1;
pub const A_L2B: i32 = 40;
pub const A_L2DEPTH: usize = 4;
/// Main a_walk in a_gain mode (a longer candidate must also save more).
pub const A_MAIN_GM: usize = 1;
/// Partial merge: when the new match also covers the last k bytes of the previous match (but not
/// all of it), the previous match is shortened by k if a closer source (at most A_PDEPTH chain steps)
/// covers its shorter length; the new match then starts k bytes earlier (0 = off).
pub const A_PARTIAL: usize = 1;
pub const A_PDEPTH: usize = 4;
/// Class 7: high-entropy input without a dominant byte (no byte above 1/A_FLAT_DIV of the sample:
/// compressed data, images) parsed with 3-byte keys (F_ settings); class 2 keeps the peaky ones
/// (16-bit weights).
pub const A_FLAT_ON: usize = 1;
pub const A_FLAT_DIV: u32 = 16;
/// ... and whose byte collision rate (sum of squared sample counts * 256 / samples^2) is below
/// A_FLAT_SQ/16 (uniform data: 1; images and compressed streams: 1.1-1.4; 8-bit weights: 1.8).
pub const A_FLAT_SQ: u64 = 26;
pub const A_F_DEPTH: usize = 32;
pub const A_F_LAZY: usize = 258;
pub const A_F_LDEPTH: usize = 2;
pub const A_F_SKIP: usize = 7;
pub const A_H_STRIDE: usize = 32;

/// Eight bytes at `i`, first byte most significant (0 when out of range).
#[inline(always)]
pub fn a_be8(s: &[u8], i: usize) -> u64 {
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

/// Four bytes at `i`, first byte most significant (0 when out of range).
#[inline(always)]
pub fn a_be4(s: &[u8], i: usize) -> u32 {
    if i + 4 <= s.len() {
        ((s[i] as u32) << 24) | ((s[i + 1] as u32) << 16) | ((s[i + 2] as u32) << 8) | (s[i + 3] as u32)
    } else {
        0
    }
}

/// Input class from a strided byte histogram of at most ~A_SAMPLE bytes:
/// 0 DNA-like, 1 text, 2 high-entropy binary, 3 other binary, 4 high-entropy with zeros,
/// 5 prose (text of letters and spaces with almost no code symbols), 6 structured text (many
/// digits: tables, logs, dumps).
pub fn a_sniff(s: &[u8]) -> usize {
    let n = s.len();
    let mut cnt = [0u32; 256];
    let step = (n / A_SAMPLE) | 1;
    let mut i = 0usize;
    let mut tot = 0u32;
    // `tot < 4097` always holds here (at most 4096 samples); with it the loop is total even
    // for a slice of usize::MAX bytes, where `i + step` could overflow.
    while i < n && tot < 4097 {
        cnt[s[i] as usize % 256] += 1;
        tot += 1;
        i = i.wrapping_add(step);
    }
    let dna = cnt[65] + cnt[67] + cnt[71] + cnt[84] + cnt[97] + cnt[99] + cnt[103] + cnt[116] + cnt[78] + cnt[110] + cnt[10];
    let mut text = cnt[9] + cnt[10] + cnt[13];
    let mut high = 0u32;
    let mut words = cnt[32];
    let mut b = 32usize;
    while b < 256 {
        if b != 127 {
            text += cnt[b];
        }
        if b >= 128 {
            high += cnt[b];
        }
        if (b >= 65 && b <= 90) || (b >= 97 && b <= 122) {
            words += cnt[b];
        }
        b += 1;
    }
    let syms = cnt[35] + cnt[36] + cnt[37] + cnt[38] + cnt[40] + cnt[41] + cnt[42] + cnt[43] + cnt[47] + cnt[59] + cnt[60] + cnt[61] + cnt[62] + cnt[64] + cnt[91] + cnt[92] + cnt[93] + cnt[94] + cnt[95] + cnt[96] + cnt[123] + cnt[124] + cnt[125] + cnt[126];
    let mut cls = 3usize;
    if tot > 0 && dna >= tot - tot / 10 {
        cls = 0;
    } else if text >= tot - tot / 100 && cnt[0] == 0 {
        cls = 1;
        let digits = cnt[48] + cnt[49] + cnt[50] + cnt[51] + cnt[52] + cnt[53] + cnt[54] + cnt[55] + cnt[56] + cnt[57];
        if words >= tot - tot / 7 && syms <= tot / 64 {
            cls = 5;
        } else if digits >= tot / A_SDIG {
            cls = 6;
        }
    } else if high >= tot / 3 {
        cls = 2;
        if cnt[0] >= tot / 20 {
            cls = 4;
        } else if A_FLAT_ON == 1 {
            let mut mx = 0u32;
            let mut sq = 0u64;
            let mut b2 = 0usize;
            while b2 < 256 {
                let c2 = cnt[b2] as u64;
                if cnt[b2] > mx {
                    mx = cnt[b2];
                }
                sq = sq.wrapping_add(c2.wrapping_mul(c2));
                b2 += 1;
            }
            let t2 = (tot as u64).wrapping_mul(tot as u64);
            if mx < tot / A_FLAT_DIV && sq.wrapping_mul(256) < t2.wrapping_mul(A_FLAT_SQ) / 16 {
                cls = 7;
            }
        }
    }
    cls
}

/// Estimated saving (1/16 bit) of a match of length `l` at distance `d` over literals.
#[inline(always)]
pub fn a_gain(l: usize, d: usize, hlit: i32) -> i32 {
    let mut c = A_GBASE;
    if l > 10 && l < 258 {
        c += 16 * (29 - ((l - 3) as u32).leading_zeros()) as i32;
    }
    if d > 4 {
        c += 16 * (30 - ((d - 1) as u32).leading_zeros()) as i32;
    }
    (l as i32) * hlit - c
}

/// Length of the a_common prefix of s[a..] and s[b..], at most `cap`.
#[inline(always)]
pub fn a_common(s: &[u8], a: usize, b: usize, cap: usize) -> usize {
    let mut k = 0usize;
    let mut a_run = 1u32;
    while a_run == 1 && k + 8 <= cap {
        let x = a_be8(s, a + k) ^ a_be8(s, b + k);
        if x == 0 {
            k += 8;
        } else {
            k += (x.leading_zeros() / 8) as usize;
            a_run = 0;
        }
    }
    while a_run == 1 && k < cap {
        if s[a + k] == s[b + k] {
            k += 1;
        } else {
            a_run = 0;
        }
    }
    k
}

/// 1 when s[a..a+len] == s[b..b+len]: eight bytes at a time, the last partial word
/// under a mask when a full load fits, else byte by byte.
#[inline(always)]
pub fn a_same(s: &[u8], a: usize, b: usize, len: usize) -> usize {
    let n = s.len();
    let mut k = 0usize;
    let mut ok = 1usize;
    while ok == 1 && k + 8 <= len {
        if a_be8(s, a + k) == a_be8(s, b + k) {
            k += 8;
        } else {
            ok = 0;
        }
    }
    if ok == 1 && k < len {
        if a + k + 8 <= n && b + k + 8 <= n {
            let x = a_be8(s, a + k) ^ a_be8(s, b + k);
            if (x >> (64 - 8 * (len - k) as u32)) != 0 {
                ok = 0;
            }
        } else {
            while ok == 1 && k < len {
                if s[a + k] == s[b + k] {
                    k += 1;
                } else {
                    ok = 0;
                }
            }
        }
    }
    ok
}

#[inline(always)]
pub fn a_put_lit(s: &[u8], out: &mut [u32], nt: usize, p: usize) -> usize {
    out[nt] = s[p] as u32;
    nt + 1
}

/// Emit a match (re-checked when A_VERIFY = 1), else a literal. Returns (tokens, next position).
#[inline(always)]
pub fn a_put_match(s: &[u8], out: &mut [u32], nt: usize, p: usize, d: usize, l: usize) -> (usize, usize) {
    let n = s.len();
    if d >= 1 && d <= 32768 && d <= p && l >= 3 && l <= 258 && p < n && l <= n - p && (A_VERIFY == 0 || a_same(s, p - d, p, l) == 1) {
        out[nt] = 16777216u32 + ((d - 1) as u32) * 256 + ((l - 3) as u32);
        (nt + 1, p + l)
    } else {
        out[nt] = s[p] as u32;
        (nt + 1, p + 1)
    }
}

/// Walk the chain from `start`: the longest match at `p` longer than `have` (with `gm` = 1,
/// a longer candidate must also have a higher estimated saving); distance 0 = none found.
/// Each candidate first compares the byte at `best`.
#[inline(always)]
pub fn a_walk<const W: usize>(s: &[u8], prev: &[u32; W], p: usize, start: usize, cap: usize, have: usize, depth: usize, nice: usize, gm: usize, hlit: i32) -> (usize, usize) {
    let n = s.len();
    let mut best = have;
    let mut bd = 0usize;
    let mut bg = -1000000i32;
    let mut c = start;
    let mut k = depth;
    let mut stop = nice;
    if stop > cap {
        stop = cap;
    }
    let mut pb = 0u8;
    if best < n - p {
        pb = s[p + best];
    }
    while k > 0 {
        let d = p.wrapping_sub(c);
        if d.wrapping_sub(1) < 32768 && c + best < n {
            if s[c + best] == pb {
                let l = a_common(s, c, p, cap);
                let mut take = 0usize;
                if l > best {
                    take = 1;
                    if gm == 1 {
                        let g = a_gain(l, d, hlit);
                        if g > bg {
                            bg = g;
                        } else {
                            take = 0;
                        }
                    }
                }
                if take == 1 {
                    best = l;
                    bd = d;
                    if l >= stop || p + l >= n {
                        k = 1;
                    } else {
                        pb = s[p + l];
                    }
                }
            }
            let nx = prev[c % W] as usize;
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
    (best, bd)
}

/// Put position `i` at the head of its chain (key = first four bytes under `mask`);
/// returns the previous head.
#[inline(always)]
pub fn a_insert<const H: usize, const W: usize>(s: &[u8], head: &mut [u32; H], prev: &mut [u32; W], i: usize, mask: u32) -> usize {
    let k = (a_be4(s, i) & mask) as u64;
    let a = (k.wrapping_mul(0x9E37_79B9_7F4A_7C15) >> (64 - A_HB)) as usize % H;
    let old = head[a];
    prev[i % W] = old;
    head[a] = i as u32;
    old as usize
}

/// Distance of the first chain entry from `start` (at most `depth` steps) whose next `len` bytes
/// equal those at `p` (0 = none).
#[inline(always)]
pub fn a_closest<const W: usize>(s: &[u8], prev: &[u32; W], p: usize, start: usize, len: usize, depth: usize) -> usize {
    let n = s.len();
    let mut c = start;
    let mut k = depth;
    let mut res = 0usize;
    while k > 0 {
        let d = p.wrapping_sub(c);
        if d.wrapping_sub(1) < 32768 && len >= 1 && c < p && p + len <= n {
            if s[c + len - 1] == s[p + len - 1] && a_same(s, c, p, len) == 1 {
                res = d;
                k = 0;
            } else {
                let nx = prev[c % W] as usize;
                if nx < c {
                    c = nx;
                    k -= 1;
                } else {
                    k = 0;
                }
            }
        } else {
            k = 0;
        }
    }
    res
}

/// Partial merge (`partial` = 1): the new match `(l0, d)` at `p0` also covers the last `k` bytes of
/// the previous match token `t` (`w` bytes, ending at `p0`), but not all of it. When a closer
/// source (at most A_PDEPTH chain steps) covers its first `w - k` bytes, that token is shortened by
/// `k` and the new match starts `k` bytes earlier. Returns the new `(p, l)`.
#[inline(always)]
pub fn a_part_merge<const W: usize>(input: &[u8], out: &mut [u32], prev: &[u32; W], nt: usize, p0: usize, l0: usize, d: usize, t: u32, w: usize, partial: usize) -> (usize, usize) {
    let mut p = p0;
    let mut l = l0;
    if partial == 1 && w > 4 && w <= p {
        let mut k = 0usize;
        while k + 4 < w && l + k < 258 && d + k < p && input[p - 1 - k] == input[p - 1 - k - d] {
            k += 1;
        }
        let pd = ((t - 16777216) / 256 + 1) as usize;
        if k > 0 {
            let pp = p - w;
            let nl = w - k;
            let c = a_closest(input, prev, pp, prev[pp % W] as usize, nl, A_PDEPTH);
            if c > 0 && c < pd && c <= pp && nl >= 3 && nl <= 258 {
                out[nt - 1] = 16777216u32 + ((c - 1) as u32) * 256 + ((nl - 3) as u32);
                p -= k;
                l += k;
            }
        }
    }
    (p, l)
}

/// Best match at `p` longer than `have` and at least `minl` long; (0, 0) when none.
#[inline(always)]
pub fn a_find<const W: usize>(s: &[u8], prev: &[u32; W], p: usize, st: usize, have: usize, minl: usize, depth: usize, nice: usize, gm: usize, hlit: i32) -> (usize, usize) {
    let n = s.len();
    let mut cap = n - p;
    if cap > 258 {
        cap = 258;
    }
    let mut lo = have;
    if lo + 1 < minl {
        lo = minl - 1;
    }
    let f = a_walk(s, prev, p, st, cap, lo, depth, nice, gm, hlit);
    let mut l = f.0;
    if f.1 == 0 {
        l = 0;
    }
    (l, f.1)
}

/// The a_parse for one input class (inlined so the text classes get constant settings), with
/// H chain heads and a window table of W entries.
#[inline(always)]
pub fn a_run<const H: usize, const W: usize>(input: &[u8], out: &mut [u32], cls: usize, lvl: usize) -> usize {
    let n = input.len();
    let mut nt = 0usize;
    let mut p = 0usize;
    let mut mask = 0xFFFF_FFFFu32;
    let mut minl = 4usize;
    let mut depth = if lvl == 0 { A_T_DEPTH0 } else { A_T_DEPTH };
    let l2d = if lvl == 0 { A_L2DEPTH0 } else { A_L2DEPTH };
    let partial = if lvl == 0 { A_PARTIAL0 } else { A_PARTIAL };
    let mut lazy = A_T_LAZY;
    let mut skip = A_T_SKIP;
    let mut skcap = A_SKCAP;
    let mut nice = A_NICE;
    let mut ldep = A_LDEPTH;
    let mut insm = if lvl == 0 { A_INS_MAX0 } else { A_INS_MAX };
    let mut stride = if lvl == 0 { A_STRIDE0 } else { A_STRIDE };
    let mut hlit = A_HLIT as i32;
    if cls == 6 {
        depth = A_S_DEPTH;
        lazy = A_S_LAZY;
        nice = A_S_NICE;
        ldep = A_S_LDEPTH;
        insm = A_S_INS;
        stride = A_S_STRIDE;
    }
    if cls == 5 {
        depth = A_P_DEPTH;
        lazy = A_P_LAZY;
        skip = A_P_SKIP;
        nice = A_P_NICE;
        ldep = A_P_LDEPTH;
        insm = A_P_INS;
        stride = A_P_STRIDE;
    }
    if cls == 2 || cls == 4 {
        depth = A_H_DEPTH;
        lazy = A_H_LAZY;
        skip = A_H_SKIP;
        nice = A_H_NICE;
        ldep = A_H_LDEPTH;
        insm = A_H_INS;
        stride = A_H_STRIDE;
        if cls == 4 {
            depth = A_Z_DEPTH;
            skip = A_Z_SKIP;
            skcap = A_Z_CAP;
            nice = A_Z_NICE;
        }
    }
    if cls == 3 || cls == 7 {
        hlit = A_B_HLIT as i32;
    }
    if cls == 7 {
        mask = 0xFFFF_FF00;
        minl = 3;
        depth = A_F_DEPTH;
        lazy = A_F_LAZY;
        skip = A_F_SKIP;
        nice = A_B_NICE;
        ldep = A_F_LDEPTH;
        insm = A_B_INS;
        stride = A_B_STRIDE;
    }
    if cls == 3 {
        mask = 0xFFFF_FF00;
        minl = 3;
        depth = A_B_DEPTH;
        lazy = A_B_LAZY;
        skip = A_B_SKIP;
        nice = A_B_NICE;
        ldep = A_B_LDEPTH;
        insm = A_B_INS;
        stride = A_B_STRIDE;
    }
    if n > 16 && cls != 0 {
        let mut head = [0u32; H];
        let mut prev = [0u32; W];
        let lim = n - 8;
        let mut ins = 0usize; // next position to a_insert
        let mut miss = 0usize; // literals since the last match
        let mut fuel = n.saturating_add(16); // every pass advances p unless a re-check fails
        while p < lim && fuel > 0 {
            fuel -= 1;
            while ins < p {
                a_insert(input, &mut head, &mut prev, ins, mask);
                ins += 1;
            }
            // `ins == p` here (a match leaves `ins = end = p`, literals leave `ins = p`)
            let hc = a_insert(input, &mut head, &mut prev, p, mask);
            ins = p + 1;
            let f = a_find(input, &prev, p, hc, 0, minl, depth, nice, A_MAIN_GM, hlit);
            let mut l = f.0;
            let mut d = f.1;
            if l >= 3 {
                // Lazy: move on while the next position has a better match by the saving
                // estimate (it may be as long but closer, or longer).
                let mut go = 1u32;
                while go == 1 && l < lazy && p + 1 < lim {
                    let q = p + 1;
                    let hq = a_insert(input, &mut head, &mut prev, q, mask);
                    ins = q + 1;
                    let mut have = 0usize;
                    if l > A_LSLACK {
                        have = l - A_LSLACK;
                    }
                    let g = a_find(input, &prev, q, hq, have, minl, ldep, nice, 1, hlit);
                    if g.0 >= minl && a_gain(g.0, g.1, hlit) > a_gain(l, d, hlit) {
                        nt = a_put_lit(input, out, nt, p);
                        p = q;
                        l = g.0;
                        d = g.1;
                    } else {
                        go = 0;
                        if A_LAZY2 == 1 && p + 2 < lim {
                            let q2 = p + 2;
                            // `ins == q2` here (`ins = q + 1` above)
                            let hq2 = a_insert(input, &mut head, &mut prev, q2, mask);
                            ins = q2 + 1;
                            let g2 = a_find(input, &prev, q2, hq2, have, minl, l2d, nice, 1, hlit);
                            if g2.0 >= minl && a_gain(g2.0, g2.1, hlit) > a_gain(l, d, hlit) + A_L2B {
                                nt = a_put_lit(input, out, nt, p);
                                nt = a_put_lit(input, out, nt, p + 1);
                                p = q2;
                                l = g2.0;
                                d = g2.1;
                                go = 1;
                            }
                        }
                    }
                }
                // Fold earlier tokens into this match while their bytes also match at d.
                let mut back = 0usize;
                while back < A_BACKTOK && nt > 0 && nt <= out.len() && l < 258 && d < p {
                    let t = out[nt - 1];
                    if t < 256 && input[p - 1] == input[p - 1 - d] {
                        p -= 1;
                        nt -= 1;
                        l += 1;
                        back += 1;
                    } else if t >= 16777216 {
                        let w = ((t - 16777216) % 256 + 3) as usize;
                        if l + w <= 258 && w <= p && d <= p - w && a_same(input, p - w - d, p - w, w) == 1 {
                            p -= w;
                            nt -= 1;
                            l += w;
                            back += 1;
                        } else {
                            let r = a_part_merge(input, out, &prev, nt, p, l, d, t, w, partial);
                            p = r.0;
                            l = r.1;
                            back = A_BACKTOK;
                        }
                    } else {
                        back = A_BACKTOK;
                    }
                }
                let r = a_put_match(input, out, nt, p, d, l);
                nt = r.0;
                let end = r.1;
                // Chain the first A_INS_MAX and the last A_TAIL positions inside the match.
                let mut stop = end;
                // wrapping: a_same code as `+` here (no overflow on any real input), total in the model
                if stop > ins.wrapping_add(insm) {
                    stop = ins.wrapping_add(insm);
                }
                if stop > lim {
                    stop = lim;
                }
                while ins < stop {
                    a_insert(input, &mut head, &mut prev, ins, mask);
                    ins += 1;
                }
                if stride > 0 {
                    // `ins + A_TAIL + stride < end`, with the bound computed once (total in the model)
                    let e2 = end.saturating_sub(A_TAIL.saturating_add(stride));
                    while ins < e2 && ins < lim {
                        a_insert(input, &mut head, &mut prev, ins, mask);
                        ins += stride;
                    }
                }
                if ins.wrapping_add(A_TAIL) < end {
                    ins = end - A_TAIL;
                }
                while ins < end && ins < lim {
                    a_insert(input, &mut head, &mut prev, ins, mask);
                    ins += 1;
                }
                if ins < end {
                    ins = end;
                }
                p = end;
                miss = 0;
            } else {
                nt = a_put_lit(input, out, nt, p);
                p += 1;
                miss += 1;
                let mut step = miss >> skip;
                if step > skcap {
                    step = skcap;
                }
                while step > 0 && p < lim {
                    nt = a_put_lit(input, out, nt, p);
                    p += 1;
                    step -= 1;
                }
                if ins < p {
                    ins = p;
                }
            }
        }
    }
    while p < n {
        nt = a_put_lit(input, out, nt, p);
        p += 1;
    }
    nt
}

/// DNA settings: key bytes, minimum match, main depth, lazy threshold/depth, skip shift.
pub const A_D_ON: usize = 1;
pub const A_D_KEY: u32 = 8;
pub const A_D_MINL: usize = 9;
pub const A_D_DEPTH: usize = 4;
pub const A_D_LAZY: usize = 0;
pub const A_D_LDEPTH: usize = 1;
pub const A_D_SKIP: usize = 8;
pub const A_D_GM: usize = 0;

/// Put position `i` at the head of its chain (key = first A_D_KEY bytes); returns the previous head.
#[inline(always)]
pub fn a_insert_dna<const H: usize, const W: usize>(s: &[u8], head: &mut [u32; H], prev: &mut [u32; W], i: usize, mask: u32) -> usize {
    let k = (a_be8(s, i) >> (64 - 8 * A_D_KEY)) & (mask as u64 | 0xFFFF_FFFF_0000_0000);
    let a = (k.wrapping_mul(0x9E37_79B9_7F4A_7C15) >> (64 - A_HB)) as usize % H;
    let old = head[a];
    prev[i % W] = old;
    head[a] = i as u32;
    old as usize
}

/// DNA-like input: chains keyed by the first A_D_KEY bytes, matches of at least A_D_MINL bytes.
pub fn a_run_dna<const H: usize, const W: usize>(input: &[u8], out: &mut [u32], cls: usize) -> usize {
    let n = input.len();
    let mut nt = 0usize;
    let mut p = 0usize;
    let mask = 0xFFFF_FFFFu32;
    let minl = A_D_MINL;
    let depth = A_D_DEPTH;
    let lazy = A_D_LAZY;
    let skip = A_D_SKIP;
    let skcap = A_SKCAP;
    let _ = cls;
    let hlit = A_HLIT as i32;
    if n > 16 {
        let mut head = [0u32; H];
        let mut prev = [0u32; W];
        let lim = n - 8;
        let mut ins = 0usize; // next position to a_insert
        let mut miss = 0usize; // literals since the last match
        let mut fuel = n.saturating_add(16); // every pass advances p unless a re-check fails
        while p < lim && fuel > 0 {
            fuel -= 1;
            while ins < p {
                a_insert_dna(input, &mut head, &mut prev, ins, mask);
                ins += 1;
            }
            let hc = a_insert_dna(input, &mut head, &mut prev, p, mask);
            ins = p + 1;
            let f = a_find(input, &prev, p, hc, 0, minl, depth, 258, A_D_GM, hlit);
            let mut l = f.0;
            let mut d = f.1;
            if l >= 3 {
                // Lazy: move on while the next position has a better match by the saving
                // estimate (it may be as long but closer, or longer).
                let mut go = 1u32;
                while go == 1 && l < lazy && p + 1 < lim {
                    let q = p + 1;
                    let hq = a_insert_dna(input, &mut head, &mut prev, q, mask);
                    ins = q + 1;
                    let mut have = 0usize;
                    if l > A_LSLACK {
                        have = l - A_LSLACK;
                    }
                    let ldep = A_D_LDEPTH;
                    let g = a_find(input, &prev, q, hq, have, minl, ldep, 258, 1, hlit);
                    if g.0 >= minl && a_gain(g.0, g.1, hlit) > a_gain(l, d, hlit) {
                        nt = a_put_lit(input, out, nt, p);
                        p = q;
                        l = g.0;
                        d = g.1;
                    } else {
                        go = 0;
                    }
                }
                // Fold earlier tokens into this match while their bytes also match at d.
                let mut back = 0usize;
                while back < A_BACKTOK && nt > 0 && nt <= out.len() && l < 258 && d < p {
                    let t = out[nt - 1];
                    if t < 256 && input[p - 1] == input[p - 1 - d] {
                        p -= 1;
                        nt -= 1;
                        l += 1;
                        back += 1;
                    } else if t >= 16777216 {
                        let w = ((t - 16777216) % 256 + 3) as usize;
                        if l + w <= 258 && w <= p && d <= p - w && a_same(input, p - w - d, p - w, w) == 1 {
                            p -= w;
                            nt -= 1;
                            l += w;
                            back += 1;
                        } else {
                            back = A_BACKTOK;
                        }
                    } else {
                        back = A_BACKTOK;
                    }
                }
                let r = a_put_match(input, out, nt, p, d, l);
                nt = r.0;
                let end = r.1;
                // Chain the first A_INS_MAX and the last A_TAIL positions inside the match.
                let mut stop = end;
                // wrapping: a_same code as `+` here (no overflow on any real input), total in the model
                if stop > ins.wrapping_add(A_INS_MAX) {
                    stop = ins.wrapping_add(A_INS_MAX);
                }
                if stop > lim {
                    stop = lim;
                }
                while ins < stop {
                    a_insert_dna(input, &mut head, &mut prev, ins, mask);
                    ins += 1;
                }
                if A_STRIDE > 0 {
                    // `ins + A_TAIL + A_STRIDE < end`, with the bound computed once (total in the model)
                    let e2 = end.saturating_sub(A_TAIL + A_STRIDE);
                    while ins < e2 && ins < lim {
                        a_insert_dna(input, &mut head, &mut prev, ins, mask);
                        ins += A_STRIDE;
                    }
                }
                if ins.wrapping_add(A_TAIL) < end {
                    ins = end - A_TAIL;
                }
                while ins < end && ins < lim {
                    a_insert_dna(input, &mut head, &mut prev, ins, mask);
                    ins += 1;
                }
                if ins < end {
                    ins = end;
                }
                p = end;
                miss = 0;
            } else {
                nt = a_put_lit(input, out, nt, p);
                p += 1;
                miss += 1;
                let mut step = miss >> skip;
                if step > skcap {
                    step = skcap;
                }
                while step > 0 && p < lim {
                    nt = a_put_lit(input, out, nt, p);
                    p += 1;
                    step -= 1;
                }
                if ins < p {
                    ins = p;
                }
            }
        }
    }
    while p < n {
        nt = a_put_lit(input, out, nt, p);
        p += 1;
    }
    nt
}

/// Every input except larger text and prose: smaller tables for small inputs.
#[inline(never)]
pub fn a_run_rest(input: &[u8], out: &mut [u32], cls: usize, lvl: usize) -> usize {
    if input.len() <= A_SMALL {
        if cls == 1 {
            a_run::<A_HS, A_WS>(input, out, 1, lvl)
        } else {
            a_run::<A_HS, A_WS>(input, out, cls, lvl)
        }
    } else {
        a_run::<A_HN, A_WN>(input, out, cls, lvl)
    }
}

/// The lazy engine for an input of class `cls` (= `a_sniff(input)`).
pub fn a_parse_cls(input: &[u8], out: &mut [u32], cls: usize, lvl: usize) -> usize {
    if A_D_ON == 1 && cls == 0 && input.len() > A_SMALL {
        return a_run_dna::<A_HN, A_WN>(input, out, 0);
    }
    if input.len() > A_SMALL && cls == 1 {
        a_run::<A_HN, A_WN>(input, out, 1, lvl)
    } else if input.len() > A_SMALL && cls == 5 {
        a_run::<A_HN, A_WN>(input, out, 5, lvl)
    } else if input.len() > A_SMALL && cls == 6 {
        a_run::<A_HN, A_WN>(input, out, 6, lvl)
    } else {
        a_run_rest(input, out, cls, lvl)
    }
}
// ───────────────────────── DNA-lite planner (phase 1, untrusted: totality only) ─────────────────────────
// For DNA-like input: bytes whose literal cost (from a strided histogram) is below DL_THRC (the four common
// bases) are planned as literals without any search; only the expensive bytes (soft-masked lower-case bases,
// newlines, rare symbols) are chained (DL_KEY-byte keys) and searched (DL_DEPTH chain steps). A match is
// planned when the literal cost it covers exceeds its estimated cost (symbols DL_LSYM/DL_DSYM plus extra bits),
// after a one-step lazy check. Literal runs are planned as entries `run` (distance 0): `emit` rejects them and
// writes `run` literals, so the plan stays aligned.

/// DNA-lite: key bytes (1..8), chain depth, search threshold (1/16 bit), symbol cost estimates (1/16 bit),
/// minimum match, one-step lazy check (1 = on).
pub const DL_KEY: u32 = 5;
pub const DL_DEPTH: usize = 32;
pub const DL_THRC: u32 = 64;
pub const DL_LSYM: u32 = 80;
pub const DL_DSYM: u32 = 80;
pub const DL_MINL: usize = 4;
pub const DL_LAZY: usize = 1;
pub const DLHN: usize = 65536;

/// Chain slot of the DL_KEY bytes at `p`.
#[inline(always)]
pub fn dl_key(s: &[u8], p: usize) -> usize {
    let k = be8(s, p) >> ((64 - 8 * (DL_KEY % 9)) % 64);
    ((k.wrapping_mul(0x9E37_79B9_7F4A_7C15)) >> 48) as usize % DLHN
}

/// Literal cost of `s[p..p+l)` (1/16 bit).
#[inline(always)]
pub fn dl_litsum(s: &[u8], litc: &[u32; 256], p: usize, l: usize) -> u32 {
    let mut acc = 0u32;
    let mut q = 0usize;
    while q < l && p + q < s.len() {
        acc = acc.saturating_add(litc[s[p + q] as usize]);
        q += 1;
    }
    acc
}

/// Estimated cost of a match (1/16 bit).
#[inline(always)]
pub fn dl_mcost(lsym: &[u8; 512], dtab: &[u8; 512], l: usize, d: usize) -> u32 {
    let ls = lsym[l % 512] as usize % 32;
    let ds = dsym(dtab, d) % 32;
    DL_LSYM.wrapping_add(LEXTRA[ls].wrapping_mul(16)).wrapping_add(DL_DSYM).wrapping_add(DEXTRA[ds].wrapping_mul(16))
}

/// The most profitable match at `p` on the chain from `start` (DL_DEPTH steps): (gain, length, distance).
pub fn dl_best(s: &[u8], litc: &[u32; 256], prev: &[u32; WN], start: usize, p: usize, lsym: &[u8; 512], dtab: &[u8; 512]) -> (u32, usize, usize) {
    let n = s.len();
    let mut cap = 0usize;
    if p < n {
        cap = n - p;
    }
    if cap > 258 {
        cap = 258;
    }
    let mut bg = 0u32;
    let mut bl = 0usize;
    let mut bd = 0usize;
    let mut c = start;
    let mut k = DL_DEPTH;
    while k > 0 {
        if c < p && p - c <= 32768 {
            let l = common(s, c, p, cap);
            if l >= DL_MINL && l >= 3 && l > bl {
                let lit = dl_litsum(s, litc, p, l);
                let cost = dl_mcost(lsym, dtab, l, p - c);
                if lit > cost && lit - cost > bg {
                    bg = lit - cost;
                    bl = l;
                    bd = p - c;
                }
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
    (bg, bl, bd)
}

/// Append a literal run of `run` bytes to the plan (entries of at most 511 literals, distance 0).
pub fn dl_flush(plan: &mut Vec<u32>, run: usize, lim: usize) {
    let mut r = run;
    while r > 0 {
        let k = if r > 511 { 511 } else { r };
        if plan.len() < lim {
            plan.push(k as u32);
        }
        r -= k;
    }
}

/// Chain the expensive positions `from..to` (inside a planned match).
pub fn dl_insert_range(s: &[u8], cheap: &[u8; 256], head: &mut [u32; DLHN], prev: &mut [u32; WN], from: usize, to: usize) {
    let mut q = from;
    while q < to && q < s.len() {
        if cheap[s[q] as usize] == 0 {
            let h = dl_key(s, q);
            prev[q % WN] = head[h];
            head[h] = q as u32;
        }
        q += 1;
    }
}

/// Literal costs (1/16 bit) from a strided byte histogram, and the bytes cheaper than DL_THRC.
pub fn dl_costs(s: &[u8], litc: &mut [u32; 256], cheap: &mut [u8; 256]) {
    let n = s.len();
    let mut cnt = [0u32; 256];
    let step = (n / 65536) | 1;
    let mut i = 0usize;
    let mut tot = 0u32;
    while i < n && tot < 65600 {
        cnt[s[i] as usize] += 1;
        tot += 1;
        i = i.wrapping_add(step);
    }
    let lt = log2_16(tot + 1);
    let mut b = 0usize;
    while b < 256 {
        let c = if cnt[b] == 0 { lt.saturating_add(32) } else { lt.saturating_sub(log2_16(cnt[b])) };
        litc[b] = c;
        cheap[b] = if c < DL_THRC { 1 } else { 0 };
        b += 1;
    }
}

/// Phase 1 for DNA-like input: the plan (literal runs and matches).
pub fn dna_plan(input: &[u8]) -> Vec<u32> {
    let n = input.len();
    let mut plan: Vec<u32> = Vec::with_capacity(n / 16 + 16);
    if n >= 32 && n.wrapping_add(n) > n {
        let mut lsym = [0u8; 512];
        let mut dtab = [0u8; 512];
        fill_tables(&mut lsym, &mut dtab);
        let mut litc = [0u32; 256];
        let mut cheap = [0u8; 256];
        dl_costs(input, &mut litc, &mut cheap);
        let mut head = [0u32; DLHN];
        let mut prev = [0u32; WN];
        let lim = n - 16;
        let mut p = 0usize;
        let mut run = 0usize;
        while p < lim {
            if cheap[input[p] as usize] == 1 {
                run += 1;
                p += 1;
            } else {
                let h = dl_key(input, p);
                let hc = head[h] as usize;
                prev[p % WN] = head[h];
                head[h] = p as u32;
                let r = dl_best(input, &litc, &prev, hc, p, &lsym, &dtab);
                let mut take = 0usize;
                if r.1 >= 3 && r.1 <= n - p {
                    take = 1;
                    if DL_LAZY == 1 && cheap[input[p + 1] as usize] == 0 {
                        let h1 = dl_key(input, p + 1);
                        let r1 = dl_best(input, &litc, &prev, head[h1] as usize, p + 1, &lsym, &dtab);
                        if r1.1 >= 3 && r1.0 > r.0.saturating_add(litc[input[p] as usize]) {
                            take = 0;
                        }
                    }
                }
                if take == 1 {
                    dl_flush(&mut plan, run, n);
                    run = 0;
                    if plan.len() < n {
                        plan.push((r.1 as u32) | ((r.2 as u32) << 9));
                    }
                    let mut e = p + r.1;
                    if e > lim {
                        e = lim;
                    }
                    dl_insert_range(input, &cheap, &mut head, &mut prev, p + 1, e);
                    p += r.1;
                } else {
                    run += 1;
                    p += 1;
                }
            }
        }
        if p < n {
            run += n - p;
        }
        dl_flush(&mut plan, run, n);
    }
    plan
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
        cnt[b % 257] = at + 1;
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
            lf[s[p] as usize] += 1;
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
            lb[s[q] as usize] += 1;
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
            if p - a <= C_WS && s[a] == s[p] && s[a + 1] == s[p + 1] && s[a + 2] == s[p + 2] && s[a + 3] == s[p + 3] {
                r4 += 1;
                if s[a + 4] == s[p + 4] && s[a + 5] == s[p + 5] {
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
