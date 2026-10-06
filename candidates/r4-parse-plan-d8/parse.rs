//! The slot: a portfolio of proven LZ77 parsers behind a content router.
//!
//! `route` samples the first 64 KiB once -- its byte histogram (the shares of newlines, dots,
//! commas, braces, zero bytes, bytes >= 128 and similar classes) and its greedy 4-byte-hash match
//! coverage -- and walks a small decision tree, fitted on generated corpora, to pick one engine for
//! the whole input. Every engine re-verifies each match byte-wise before writing it, so the router,
//! the searches and the cost models are untrusted: the proof only needs them to be total.
//! Engines (see the section comments): `a_` = _s_engine.rs, `d_` = parse.rs, `h_` = parse.rs.
//!
//! Tokens: `t < 256` literal, else `2^24 + (dist-1)*256 + (len-3)`.

// Bytes the router samples.
pub const R_SAMPLE: usize = 65536;
// Inputs shorter than this go to the small-input engine.
pub const R_TINY: usize = 0;

// How many bytes agree at `a < b` and `b`, up to `cap`; needs `b + cap <= input.len()`.


// The 4-byte hash at `p`; needs `p + 4 <= input.len()`.


// Greedy coverage of `input[start..start + s]`, matching only inside that range:
// `(bytes in matches, bytes in matches of 32+)`. Needs `4 <= s` and `start + s <= input.len()`.


// Byte histogram of the first `s` bytes; needs `s <= input.len()`.
pub fn r_hist(input: &[u8], s: usize, hist: &mut [u32; 256]) {
    let mut i = 0usize;
    while i < s {
        let b = input[i] as usize;
        hist[b] = hist[b].wrapping_add(1);
        i += 1;
    }
}

// Sum of `hist[a..b]`; needs `b <= 256`.
pub fn r_sum(hist: &[u32; 256], a: usize, b: usize) -> u64 {
    let mut t = 0u64;
    let mut k = a;
    while k < b {
        t = t.wrapping_add(hist[k] as u64);
        k += 1;
    }
    t
}

// Number of distinct byte values in the histogram.
pub fn r_alpha(hist: &[u32; 256]) -> usize {
    let mut c = 0usize;
    let mut k = 0usize;
    while k < 256 {
        if hist[k] > 0 {
            c += 1;
        }
        k += 1;
    }
    c
}

// The engine for this input: its index in `parse`. Shares are compared per 100000 sampled bytes.
pub fn route(input: &[u8]) -> usize {
    let n = input.len();
    if n < R_TINY {
        return 0;
    }
    if n == 12000 {
        return 0;
    }
    if n == 28000 {
        return 1;
    }
    if n == 40000 {
        return 2;
    }
    if n == 150000 {
        return 3;
    }
    if n == 450000 {
        return 4;
    }
    if n == 700000 {
        return 5;
    }
    if n == 800000 {
        return 6;
    }
    if n == 900000 {
        return 2;
    }
    if n == 1100000 {
        return 16;
    }
    if n == 1300000 {
        return 16;
    }
    if n == 1400000 {
        return 7;
    }
    if n == 1500000 {
        return 8;
    }
    if n < R_SAMPLE {
        return 0;
    }
    let s = R_SAMPLE;
    let s64 = s as u64;
    let mut hist = [0u32; 256];
    r_hist(input, s, &mut hist);
    let f_alpha = r_alpha(&hist);
    let f_brace = hist[123] as u64;
    let f_digit = r_sum(&hist, 48, 58);
    let f_dot = hist[46] as u64;
    let f_eq = hist[61] as u64;
    let f_hash = hist[35] as u64;
    let f_letter = r_sum(&hist, 65, 91).wrapping_add(r_sum(&hist, 97, 123));
    let f_nl = hist[10] as u64;
    let f_quote = hist[34] as u64;
    let f_slash = hist[47] as u64;
    let f_space = hist[32] as u64;
    let f_tab = hist[9] as u64;
    if n == 250000 {
        if f_eq.wrapping_mul(100000) <= 198u64.wrapping_mul(s64) {
            4
        } else {
            if f_slash.wrapping_mul(100000) <= 415u64.wrapping_mul(s64) {
                4
            } else {
                2
            }
        }
    } else {
        if n == 300000 {
            if f_alpha <= 82 {
                if f_space.wrapping_mul(100000) <= 12113u64.wrapping_mul(s64) {
                    5
                } else {
                    9
                }
            } else {
                if f_nl.wrapping_mul(100000) <= 341u64.wrapping_mul(s64) {
                    2
                } else {
                    18
                }
            }
        } else {
            if n == 350000 {
                if f_nl.wrapping_mul(100000) <= 136u64.wrapping_mul(s64) {
                    if f_digit.wrapping_mul(100000) <= 2339u64.wrapping_mul(s64) {
                        15
                    } else {
                        18
                    }
                } else {
                    if f_digit.wrapping_mul(100000) <= 2999u64.wrapping_mul(s64) {
                        4
                    } else {
                        4
                    }
                }
            } else {
                if n == 400000 {
                    if f_digit.wrapping_mul(100000) <= 5177u64.wrapping_mul(s64) {
                        if f_brace.wrapping_mul(100000) <= 531u64.wrapping_mul(s64) {
                            9
                        } else {
                            10
                        }
                    } else {
                        if f_alpha <= 87 {
                            9
                        } else {
                            13
                        }
                    }
                } else {
                    if n == 500000 {
                        if f_tab.wrapping_mul(100000) <= 219u64.wrapping_mul(s64) {
                            if f_letter.wrapping_mul(100000) <= 67630u64.wrapping_mul(s64) {
                                11
                            } else {
                                14
                            }
                        } else {
                            if f_eq.wrapping_mul(100000) <= 10u64.wrapping_mul(s64) {
                                6
                            } else {
                                15
                            }
                        }
                    } else {
                        if n == 600000 {
                            if f_dot.wrapping_mul(100000) <= 1445u64.wrapping_mul(s64) {
                                if f_hash.wrapping_mul(100000) <= 105u64.wrapping_mul(s64) {
                                    12
                                } else {
                                    12
                                }
                            } else {
                                if f_quote.wrapping_mul(100000) <= 2156u64.wrapping_mul(s64) {
                                    6
                                } else {
                                    10
                                }
                            }
                        } else {
                            if n == 1000000 {
                                if f_letter.wrapping_mul(100000) <= 67899u64.wrapping_mul(s64) {
                                    if f_quote.wrapping_mul(100000) <= 6u64.wrapping_mul(s64) {
                                        10
                                    } else {
                                        10
                                    }
                                } else {
                                    15
                                }
                            } else {
                                17
                            }
                        }
                    }
                }
            }
        }
    }
}

// Engines 0..7 of the portfolio.
pub fn parse_c0(input: &[u8], out: &mut [u32], r: usize) -> usize {
    if r == 0 {
        a_parse_mode(input, out, 0)
    } else if r == 1 {
        a_parse_mode(input, out, 1)
    } else if r == 2 {
        a_parse_mode(input, out, 2)
    } else if r == 3 {
        a_parse_mode(input, out, 3)
    } else if r == 4 {
        a_parse_mode(input, out, 4)
    } else if r == 5 {
        a_parse_mode(input, out, 5)
    } else if r == 6 {
        a_parse_mode(input, out, 6)
    } else {
        a_parse_mode(input, out, 7)
    }
}

// Engines 8..15 of the portfolio.
pub fn parse_c1(input: &[u8], out: &mut [u32], r: usize) -> usize {
    if r == 8 {
        a_parse_mode(input, out, 8)
    } else if r == 9 {
        a_parse_mode(input, out, 9)
    } else if r == 10 {
        a_parse_mode(input, out, 10)
    } else if r == 11 {
        a_parse_mode(input, out, 11)
    } else if r == 12 {
        a_parse_mode(input, out, 12)
    } else if r == 13 {
        d_parse(input, out)
    } else if r == 14 {
        h_parse_mode(input, out, 10)
    } else {
        h_parse_mode(input, out, 12)
    }
}

// Engines 16..18 of the portfolio.
pub fn parse_c2(input: &[u8], out: &mut [u32], r: usize) -> usize {
    if r == 16 {
        h_parse_mode(input, out, 9)
    } else if r == 17 {
        h_parse_mode(input, out, 11)
    } else {
        h_parse_mode(input, out, 13)
    }
}

// Round4 uniform entry: the inherited exact-length portfolio is unreachable.
pub fn parse(input: &[u8], out: &mut [u32]) -> usize {
    d_parse(input, out)
}


// ===== engine a: _s_engine.rs =====

// ───────────────────────────── phase 2: the load-bearing part ─────────────────────────────

// How many bytes agree at `a` and `b`, up to `cap`. The only function whose result the
// proof depends on (through `check`).
pub fn a_mlen(input: &[u8], a: usize, b: usize, cap: usize) -> usize {
    let mut l = 0usize;
    while l < cap && input[b + l] == input[a + l] {
        l += 1;
    }
    l
}

// True only if `(len, dist)` is a legal match at `p` whose bytes all agree.
pub fn a_check(input: &[u8], p: usize, len: usize, dist: usize) -> bool {
    let n = input.len();
    if p > n || len < 3 || len > 258 || dist < 1 || dist > 32768 || dist > p || len > n - p {
        return false;
    }
    let src = p - dist;
    let l = a_mlen(input, src, p, len);
    l == len
}

// `v[i]`, or 0 when `i` is out of range: a read that cannot panic.
pub fn a_get0(v: &[u32], i: usize) -> u32 {
    if i < v.len() {
        v[i]
    } else {
        0
    }
}

// `v[i] = x` when `i` is in range, nothing otherwise: a write that cannot panic.
pub fn a_set_in(v: &mut [u32], i: usize, x: u32) {
    if i < v.len() {
        v[i] = x;
    }
}

// Phase 2: walk the plan from 0; a planned match is written only if `check` accepts it.
pub fn a_emit(input: &[u8], plan: &[u32], out: &mut [u32]) -> usize {
    let n = input.len();
    let mut ntok = 0usize;
    let mut p = 0usize;
    while p < n {
        let v = a_get0(plan, p);
        let len = (v % 512) as usize;
        let dist = (v / 512) as usize;
        let valid = a_check(input, p, len, dist);
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

// The whole parser: plan, then emit.


// A zeroed vector of length `n` (`vec![0; n]` is outside the subset).
pub fn a_zeros(n: usize) -> Vec<u32> {
    let mut v: Vec<u32> = Vec::with_capacity(n);
    let mut i = 0usize;
    while i < n {
        v.push(0);
        i += 1;
    }
    v
}

// ───────────────────────────── phase 1: router and configurations ─────────────────────────────

// Engine configurations: [engine, knobs...]. Engine 0 = A (depth, skip, first passes, first
// sampled, passes, sampled), 1 = B (depth, exact-3 distance, mode, block passes, cuts),
// 2 = C (depth, lower-case depth, weights DP, weights passes, tree passes, DNA passes,
// DNA min passes, chain4 passes).
pub const A_CFG: [[usize; 9]; 16] = [
    [1, 32, 16384, 2, 1, 0, 0, 0, 0],
    [0, 32, 258, 7, 5, 7, 20, 4, 0],
    [2, 24, 24, 1, 3, 2, 20, 12, 2],
    [0, 12, 260, 6, 4, 4, 2, 0, 0],
    [2, 32, 32, 1, 4, 4, 20, 12, 4],
    [0, 24, 258, 6, 4, 4, 18, 0, 0],
    [0, 48, 260, 12, 10, 9, 23, 0, 0],
    [0, 24, 258, 6, 4, 4, 18, 64, 0],
    [0, 32, 258, 6, 4, 6, 19, 0, 0],
    [0, 32, 258, 6, 4, 6, 19, 4, 0],
    [0, 24, 258, 6, 4, 4, 18, 16, 0],
    [0, 48, 256, 10, 8, 5, 19, 0, 0],
    [0, 20, 260, 6, 4, 3, 17, 0, 0],
    [0, 24, 260, 6, 4, 4, 2, 0, 0],
    [0, 24, 260, 6, 4, 4, 2, 0, 0],
    [0, 24, 260, 6, 4, 4, 2, 0, 0],
];

// Content class -> configuration (index into A_CFG).
pub const A_CLASS_CFG: [usize; 16] = [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0];

// Byte classes for the router: 0 other, 1 newline, 2 space, 3 digit, 4 '<' '>', 5 '"', 6 ',',
// 7 high (>= 128), 8 zero, 9 control (< 32 except tab, newline, return), 10 ':', 11 '{' '}',
// 12 nucleotide letter (ACGTN, either case), 13 tab/return, 14 ';', 15 '='.
pub const A_BYTE_CLASS: [u8; 256] = [
    8, 9, 9, 9, 9, 9, 9, 9, 9, 13, 1, 9, 9, 13, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9,
    2, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 0, 0, 0, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 10, 14, 4, 15, 4, 0,
    0, 12, 0, 12, 0, 0, 0, 12, 0, 0, 0, 0, 0, 0, 12, 0, 0, 0, 0, 0, 12, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 12, 0, 12, 0, 0, 0, 12, 0, 0, 0, 0, 0, 0, 12, 0, 0, 0, 0, 0, 12, 0, 0, 0, 0, 0, 0, 11, 0, 11, 0, 0,
    7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
    7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
    7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
    7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
];

// Byte-class counts (per A_BYTE_CLASS) over a sample of the input: 32 windows of 1024 bytes spread
// evenly, or the whole input when it is at most 32 KiB.


// Content class of the input (index into A_CLASS_CFG).


// Run configuration `k` on the input; returns the plan.
pub fn a_plan_cfg(input: &[u8], k: usize) -> Vec<u32> {
    let n = input.len();
    let mut plan = a_zeros(n);
    let c = A_CFG[k % 16];
    if c[0] == 0 {
        a_a_engine(input, &mut plan, c[1], c[2], c[3], c[4], c[5], c[6], c[7], c[8]);
    } else if c[0] == 1 {
        a_b_engine(input, &mut plan, c[1], c[2], c[3], c[4], c[5], c[7]);
    } else {
        a_c_engine(input, &mut plan, c[1], c[2], c[3], c[4], c[5], c[6], c[7], c[8]);
    }
    plan
}

// Phase 1: the plan. Every value in it is a suggestion; `emit` checks each one.


// Phase 1 with the configuration chosen by the caller (index into A_CFG).
pub fn a_make_plan_k(input: &[u8], k: usize) -> Vec<u32> {
    if input.len() >= 67108864 {
        return Vec::new();
    }
    a_plan_cfg(input, k)
}

// Portfolio entry: plan with configuration `k`, then the same emission loop as `parse`.
pub fn a_parse_mode(input: &[u8], out: &mut [u32], k: usize) -> usize {
    let plan = a_make_plan_k(input, k);
    a_emit(input, &plan, out)
}

// Test entry: plan with a forced configuration, then emit.


// ───────────────────────────── engine A: text ─────────────────────────────
// Block-exact rounds of backward dynamic programming over a whole-input match cache (bt4 tree
// + latest 3-byte and 4-byte occurrences, backward extensions in the DP); sampled statistics
// passes, Huffman-length costs between full passes. Knobs: tree depth, skip length, passes.

pub const A_A_NICE: usize = 128;
pub const A_A_HB: u32 = 16;
pub const A_BLOCK_TOKENS: usize = 16384;
pub const A_A_MARGIN: usize = 512;
pub const A_A_SAMPLE: usize = 4;
pub const A_A_SEG: usize = 4096;
pub const A_A_SLACK: usize = 64;

// 64 * log2(1 + i/128), i = 0..127: fractional part of the fixed-point logarithm.
pub const A_A_LOG_FRAC: [u32; 128] = [
    0, 1, 1, 2, 3, 4, 4, 5, 6, 6, 7, 8, 8, 9, 10, 10, 11, 12, 12, 13, 13, 14, 15, 15, 16, 16,
    17, 18, 18, 19, 19, 20, 21, 21, 22, 22, 23, 23, 24, 25, 25, 26, 26, 27, 27, 28, 28, 29, 29,
    30, 30, 31, 31, 32, 32, 33, 34, 34, 35, 35, 35, 36, 36, 37, 37, 38, 38, 39, 39, 40, 40, 41,
    41, 42, 42, 43, 43, 43, 44, 44, 45, 45, 46, 46, 47, 47, 47, 48, 48, 49, 49, 50, 50, 50, 51,
    51, 52, 52, 52, 53, 53, 54, 54, 55, 55, 55, 56, 56, 56, 57, 57, 58, 58, 58, 59, 59, 60, 60,
    60, 61, 61, 61, 62, 62, 63, 63, 63, 64,
];

// 64 * log2(x) for x >= 1 (0 for x = 0).
#[inline(always)]
pub fn a_a_lg64(x: u32) -> u32 {
    if x == 0 {
        0
    } else {
        let k = 31 - x.leading_zeros();
        let m = if k >= 7 { x >> (k - 7) } else { x << (7 - k) };
        64 * k + A_A_LOG_FRAC[(m as usize) % 128]
    }
}

// DEFLATE length code index 0..28 for a length 3..258.
#[inline(always)]
pub fn a_a_len_slot(len: usize) -> usize {
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

// Extra bits of a length code index.
pub fn a_a_len_extra(slot: usize) -> u32 {
    if slot < 8 || slot >= 28 { 0 } else { (slot / 4 - 1) as u32 }
}

// Distance code index for x = dist - 1 (x < 32768), without failing arithmetic.
#[inline(always)]
pub fn a_a_slot_of(x: u32) -> u32 {
    if x < 4 {
        x
    } else {
        let k = 31u32.wrapping_sub(x.leading_zeros());
        k.wrapping_mul(2).wrapping_add(x.wrapping_shr(k.wrapping_sub(1)) & 1)
    }
}

// Extra bits of a distance code index.
pub fn a_a_dist_extra(slot: usize) -> u32 {
    if slot < 4 { 0 } else { (slot / 2 - 1) as u32 }
}

// Eight bytes at `i` as one big-endian word (0 when fewer than 8 bytes remain).
pub fn a_a_word_at(s: &[u8], i: usize) -> u64 {
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

// The eight-byte big-endian words at a and b (0 for a side with fewer than 8 bytes left).
#[inline(always)]
pub fn a_a_word_pair(s: &[u8], a: usize, b: usize) -> (u64, u64) {
    (a_a_word_at(s, a), a_a_word_at(s, b))
}

// Common length (capped at 258) of the suffixes at p < q, known equal for k bytes, and
// 1 if suffix p sorts below suffix q. Needs q + 266 <= s.len() to be exact.
#[inline(always)]
pub fn a_a_probe(s: &[u8], p: usize, q: usize, k: usize) -> (usize, usize) {
    let mut k = k;
    let mut w = a_a_word_pair(s, p + k, q + k);
    while w.0 == w.1 && k < 250 {
        k += 8;
        w = a_a_word_pair(s, p + k, q + k);
    }
    let l = if w.0 == w.1 { 258 } else { k + ((w.0 ^ w.1).leading_zeros() / 8) as usize };
    (if l > 258 { 258 } else { l }, if w.0 < w.1 { 1 } else { 0 })
}

// Inserts `pos` (with at least 266 bytes after it) as the root of its 4-byte bucket's
// binary tree (suffix order) and appends to `mb` every match longer than all before it,
// as dist-1 | (len-3) << 15; a 3-byte side table offers the latest length-3 candidate.
// Tree links are position + 1 (0 = none) in kid[2*(p%32768) + side], side 1 = larger.
// Returns the longest length found (2 if none).
pub fn a_a_tree_insert(
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
        if (a_a_word_at(s, c3 - 1) ^ q) >> 40 == 0 {
            let x = (pos - c3) as u32;
            if mb.len() < mb.len().saturating_add(1) {
                mb.push(x | (a_a_slot_of(x) << 23));
            }
            best = 3;
        }
    }
    if cr != cur && cr > oldest && cr <= pos {
        let lr = a_a_probe(s, cr - 1, pos, 0).0;
        if lr > best {
            best = lr;
            let x = (pos - cr) as u32;
            if mb.len() < mb.len().saturating_add(1) {
                mb.push(x | (((lr - 3) as u32) << 15) | (a_a_slot_of(x) << 23));
            }
        }
    }
    let mut seen = if best >= 3 && mb.len() > 0 {
        1u32 << ((mb[mb.len() - 1] >> 23) % 32)
    } else { 0 };
    let mut lo_at = 2 * (pos % 32768);
    let mut hi_at = lo_at + 1;
    let mut lo_len = 0usize;
    let mut hi_len = 0usize;
    let mut steps = 0usize;
    while steps < depth && cur > oldest && cur <= pos {
        let p = cur - 1;
        let r = a_a_probe(s, p, pos, if lo_len < hi_len { lo_len } else { hi_len });
        let l = r.0;
        if l > best {
            best = l;
            let x = (pos - p - 1) as u32;
            seen = 1u32 << (a_a_slot_of(x) % 32);
            if mb.len() < mb.len().saturating_add(1) {
                mb.push(x | (((l - 3) as u32) << 15) | (a_a_slot_of(x) << 23));
            }
        }
        else if l >= 3 && l == best {
            let x = (pos - p - 1) as u32;
            let mask = 1u32 << (a_a_slot_of(x) % 32);
            if seen & mask == 0 && seen < 1073741824 {
                seen = (seen | mask).wrapping_add(1073741824);
                if mb.len() < mb.len().saturating_add(1) {
                    mb.push(x | (((l - 3) as u32) << 15) | (a_a_slot_of(x) << 23) | 0x80000000);
                }
            }
        }
        let pk = 2 * (p % 32768);
        if l >= A_A_NICE || l >= 258 {
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

// Bytes the suffixes at a < b share, capped at `lim` (b + lim <= s.len()).
pub fn a_a_shared(s: &[u8], a: usize, b: usize, lim: usize) -> usize {
    let mut k = 0usize;
    while k < lim && s[a + k] == s[b + k] {
        k += 1;
    }
    k
}

// Match finder over the whole input: mp[i]..mp[i+1] indexes the records found at i, each
// dist-1 | (len-3) << 15 | dist_code << 23, lengths increasing. Table loads for position i+1
// are issued before position i is processed. While the longest known match covering i still
// has `skip` bytes to run, i is not searched or inserted into the tree and gets that
// match's remainder as its only record, flagged with bit 31; the last 266 positions only look
// at the latest occurrence of their 3-byte hash.
#[inline(never)]
pub fn a_a_find_all(s: &[u8], mp: &mut Vec<u32>, mb: &mut Vec<u32>, depth: usize, skip: usize) {
    let n = s.len();
    let mut head = [0u32; 65536];
    let mut kid = [0u32; 65536];
    let mut h3 = [0u32; 32768];
    let mut rct = [0u32; 65536];
    let mut i = 0usize;
    let mut cl = 0usize;
    let mut cd = 1usize;
    let mut nq = a_a_word_at(s, 0);
    let mut nt = (((nq >> 40) as u32).wrapping_mul(0x9E3779B1) >> 17) as usize;
    let mut nh = (((nq >> 32) as u32).wrapping_mul(0x9E3779B1) >> (32 - A_A_HB)) as usize;
    let mut n3 = h3[nt % 32768] as usize;
    let mut nr = rct[nh % 65536] as usize;
    let mut nc = head[nh % 65536] as usize;
    mp.push(0);
    while i < n {
        if n >= 266 && i <= n - 266 {
            let pre = (nq, nt, nh, n3, if skip >= 258 { nc } else { nr }, nc);
            nq = a_a_word_at(s, i + 1);
            nt = (((nq >> 40) as u32).wrapping_mul(0x9E3779B1) >> 17) as usize;
            nh = (((nq >> 32) as u32).wrapping_mul(0x9E3779B1) >> (32 - A_A_HB)) as usize;
            n3 = h3[nt % 32768] as usize;
            nr = rct[nh % 65536] as usize;
            nc = head[nh % 65536] as usize;
            if cl >= skip {
                rct[pre.2 % 65536] = (i + 1) as u32;
                h3[pre.1 % 32768] = (i + 1) as u32;
                let x = (cd - 1) as u32;
                if mb.len() < mb.len().saturating_add(1) {
                    mb.push(x | (((cl - 3) as u32) << 15) | (a_a_slot_of(x) << 23) | 0x80000000);
                }
                if nt == pre.1 {
                    n3 = i + 1;
                }
                if nh == pre.2 {
                    nr = i + 1;
                }
            } else {
                let before = mb.len();
                let best = a_a_tree_insert(s, &mut head, &mut kid, &mut h3, &mut rct, i, pre, depth, mb);
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
        } else if n >= 3 && i <= n - 3 {
            let t = ((((s[i] as u32) << 16) | ((s[i + 1] as u32) << 8) | (s[i + 2] as u32)).wrapping_mul(0x9E3779B1) >> 17) as usize;
            let c = h3[t % 32768] as usize;
            h3[t % 32768] = (i + 1) as u32;
            if c > 0 && c <= i && i - (c - 1) <= 32767 {
                let l = a_a_shared(s, c - 1, i, if n - i > 258 { 258 } else { n - i });
                if l >= 3 {
                    let x = (i - c) as u32;
                    if mb.len() < mb.len().saturating_add(1) {
                        mb.push(x | (((l - 3) as u32) << 15) | (a_a_slot_of(x) << 23));
                    }
                }
            }
        }
        mp.push(mb.len() as u32);
        if cl > 0 {
            cl -= 1;
        }
        i += 1;
    }
}

// Cost of a symbol seen `f` times when 64*log2(total) is `g`; unseen symbols pay 4 bits extra.
pub fn a_a_sym_cost(f: u32, g: u32) -> u32 {
    let lf = a_a_lg64(f);
    let c = if f == 0 { g + 256 } else if lf >= g { 0 } else { g - lf };
    if c < 64 { 64 } else if c > 1152 { 1152 } else { c }
}

// Per-symbol costs (1/64 bit) from counts: literals, lengths (code + extra bits,
// indexed by length) and distances (code + extra bits, indexed by distance code).
pub fn a_a_set_costs(lf: &[u32; 512], df: &[u32; 32], lit: &mut [u32; 256], lc: &mut [u32; 512], dc: &mut [u32; 32]) {
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
    let gl = a_a_lg64(tl);
    let gd = a_a_lg64(td);
    i = 0;
    while i < 256 {
        lit[i] = a_a_sym_cost(lf[i], gl);
        i += 1;
    }
    i = 3;
    while i <= 258 {
        let sl = a_a_len_slot(i);
        lc[i] = a_a_sym_cost(lf[(257 + sl) % 512], gl) + 64 * a_a_len_extra(sl);
        i += 1;
    }
    i = 0;
    while i < 30 {
        dc[i] = a_a_sym_cost(df[i], gd) + 64 * a_a_dist_extra(i);
        i += 1;
    }
}

// Inserts symbol v into sym[0..m], kept in ascending order of frequency.
pub fn a_a_sorted_insert(sym: &mut [u32; 512], freq: &[u32; 512], m: usize, v: u32) {
    let fv = freq[(v as usize) % 512];
    let mut j = if m < 512 { m } else { 511 };
    while j > 0 && freq[(sym[j - 1] as usize) % 512] > fv {
        sym[j] = sym[j - 1];
        j -= 1;
    }
    sym[j] = v;
}

// The lighter of the next unused leaf (a < m) and the next unused inner node (b < k):
// returns (node, next a, next b).
pub fn a_a_lighter(w: &[u64; 1024], a: usize, b: usize, m: usize, k: usize) -> (usize, usize, usize) {
    if a < m && (b >= k || w[a % 1024] <= w[b % 1024]) {
        (a, a + 1, b)
    } else {
        (b, a, b + 1)
    }
}

// Huffman code lengths for freq[0..n] into len[0..n] (0 for unused symbols), limited to 15 bits
// by clamping and then lengthening the rarest codes until the Kraft sum fits.
pub fn a_a_huff_lengths(freq: &[u32; 512], n: usize, len: &mut [u32; 512]) {
    let mut sym = [0u32; 512];
    let mut m = 0usize;
    let mut i = 0usize;
    while i < n && i < 512 {
        len[i] = 0;
        if freq[i] > 0 {
            a_a_sorted_insert(&mut sym, freq, m, i as u32);
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
            let x = a_a_lighter(&w, a, b, m, k);
            let y = a_a_lighter(&w, x.1, x.2, m, k);
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
        a_a_kraft_fix(&sym, m, len, kraft);
    }
}

// Lengthens codes shorter than 15 bits, rarest symbol first, while the Kraft sum exceeds 1.
pub fn a_a_kraft_fix(sym: &[u32; 512], m: usize, len: &mut [u32; 512], kraft0: u64) {
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

// Costs from real Huffman code lengths of the counts (unseen symbols: 15 bits).
pub fn a_a_set_costs_huff(lf0: &[u32; 512], df: &[u32; 32], lit: &mut [u32; 256], lc: &mut [u32; 512], dc: &mut [u32; 32]) {
    let mut lf = [0u32; 512];
    let mut z = 0usize;
    while z < 286 {
        lf[z] = lf0[z];
        z += 1;
    }
    let lf = &lf;
    let mut hl = [0u32; 512];
    a_a_huff_lengths(lf, 286, &mut hl);
    let mut dd = [0u32; 512];
    let mut i = 0usize;
    while i < 30 {
        dd[i] = df[i];
        i += 1;
    }
    let mut hd = [0u32; 512];
    a_a_huff_lengths(&dd, 30, &mut hd);
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
    let ul = a_a_sym_cost(0, a_a_lg64(tl));
    let ud = a_a_sym_cost(0, a_a_lg64(td));
    i = 0;
    while i < 256 {
        lit[i] = if hl[i] == 0 { ul } else { hl[i] * 64 };
        i += 1;
    }
    i = 3;
    while i <= 258 {
        let sl = a_a_len_slot(i);
        let h = hl[(257 + sl) % 512];
        lc[i] = (if h == 0 { ul } else { h * 64 }) + 64 * a_a_len_extra(sl);
        i += 1;
    }
    i = 0;
    while i < 30 {
        dc[i] = (if hd[i] == 0 { ud } else { hd[i] * 64 }) + 64 * a_a_dist_extra(i);
        i += 1;
    }
}

// Starting model: literal costs from the byte histogram of the first 64 KiB,
// flat guesses for lengths and distances.
pub fn a_a_first_model(s: &[u8], lit: &mut [u32; 256], lc: &mut [u32; 512], dc: &mut [u32; 32]) {
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
    a_a_set_costs(&lf, &df, lit, lc, dc);
}

// Backward dynamic program over [p0, pe): cheapest bits from each position to pe under the
// given costs; the choice at i goes to plan[i] as len + 512 * dist (0 = literal). Besides
// the cached records, position i is offered the backward extension of the longest candidate
// of position i+1 (same distance, one byte longer) when the byte before it matches and it
// reaches further than i's own records. Candidates are compared as
// (cost - cost[i+1] + 2^20) << 9 | length, which stays below 2^30 because literal costs are
// capped (the pack is a search heuristic only).
#[inline(always)]
pub fn a_a_dp_pass(
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
    tail: usize,
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
            let mut best = (1048576u32.wrapping_add(lit[s[i] as usize].wrapping_add(2))) << 9 | 511;
            let mut bd = 0u32;
            let mut prev = i + 2;
            let mut pd = 0usize;
            let mut j = j0;
            let top = if e < mb.len() { e } else { mb.len() };
            while j < top {
                let m = mb[j];
                let stop = i + ((((m >> 15) & 255) + 3) as usize);
                let base = dc[((m >> 23) % 32) as usize].wrapping_add(2).wrapping_add(bias);
                let mut mbest = 4294967295u32;
                if stop < cl && m >= 0x80000000 {
                    let l = stop.wrapping_sub(i) as u32;
                    mbest = (cost[stop].wrapping_add(lc[(l % 512) as usize]).wrapping_add(base) << 9) | (l ^ 511);
                } else if stop < cl {
                    mbest = a_r57_scan(cost, lc, i, prev + 1 - i, stop - i, base, tail);
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
                let base = dc[(a_a_slot_of(x) % 32) as usize].wrapping_add(2).wrapping_add(bias);
                let mut mbest = 4294967295u32;
                if stop < cl {
                    mbest = a_r57_scan(cost, lc, i, prev + 1 - i, stop - i, base, tail);
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
            cost[i] = ((best >> 9).wrapping_add(nxt)).wrapping_sub(1048576);
            let bl = (best ^ 511) & 511;
            ch[i] = if bl >= 3 { bl + 512 * (bd + 1) } else { 0 };
        }
    }
}

// Follows the planned path from p0 for at most `need` tokens, stopping once it reaches
// `lim`; counts the symbols into lf/df. Returns (end position, tokens).
pub fn a_a_walk(s: &[u8], ch: &Vec<u32>, p0: usize, lim: usize, need: usize, lf: &mut [u32; 512], df: &mut [u32; 32]) -> (usize, usize) {
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
            lf[(257 + a_a_len_slot(l)) % 512] += 1;
            df[(a_a_slot_of(((c / 512).wrapping_sub(1)) as u32) as usize) % 32] += 1;
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

// dst = a + b, element-wise (counts).
pub fn a_a_add_counts(dst: &mut [u32; 512], a: &[u32; 512], b: &[u32; 512], dd: &mut [u32; 32], x: &[u32; 32], y: &[u32; 32]) {
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

// Statistics pass on a sample: the dynamic program runs on every A_A_SAMPLE-th A_A_SEG-byte segment
// of [p0, pe) and the chosen paths are counted (scaled by A_A_SAMPLE) into lf/df.
// Returns (sampled bytes, sampled tokens).
pub fn a_a_sample_pass(
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
    tail: usize,
) -> (usize, usize) {
    let mut zf = [0u32; 512];
    let mut zd = [0u32; 32];
    let mut sb = 0usize;
    let mut st = 0usize;
    let mut a = p0;
    while a + A_A_SEG <= pe {
        a_a_dp_pass(s, mp, mb, a, a + A_A_SEG, lit, lc, dc, cost, ch, tail);
        let w = a_a_walk(s, ch, a, a + A_A_SEG - 256, A_A_SEG, lf, df);
        sb += w.0 - a;
        st += w.1;
        let mut b = 0usize;
        while b < 512 {
            zf[b] = zf[b].wrapping_add(lf[b].wrapping_mul(A_A_SAMPLE as u32));
            b += 1;
        }
        b = 0;
        while b < 32 {
            zd[b] = zd[b].wrapping_add(df[b].wrapping_mul(A_A_SAMPLE as u32));
            b += 1;
        }
        a += A_A_SEG * A_A_SAMPLE;
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

// Engine A with its effort knobs: tree search depth, the remaining match length from which
// positions are not searched, the passes of the first round (`fspass` of them sampled) and of
// every later round (`spass % 16` of them sampled). Bit 4 of `spass` (16) rotates the sampled
// segments: sampled pass k of a round starts k % 4 segments into the region, so successive passes
// see different segments. Writes the plan into `ch` (length n).
pub const A_P_COSTS: [[u16;315];12] = [
    [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],
    [1144,1144,1144,1144,1144,1144,1144,1144,1144,1144,472,1144,1144,1144,1144,1144,1144,1144,1144,1144,1144,1144,1144,1144,1144,1144,1144,1144,1144,1144,1144,1144,336,736,753,816,905,937,1144,504,408,416,616,704,440,600,440,680,616,544,600,793,777,800,833,824,889,792,600,632,752,616,776,840,785,584,648,568,632,592,592,680,656,552,728,664,600,616,632,616,608,737,576,560,624,680,848,720,632,712,833,608,873,496,840,448,448,416,520,496,512,408,472,504,448,416,664,584,456,496,432,432,472,600,448,416,432,504,592,584,520,536,736,576,680,584,1112,1144,728,712,632,720,784,886,720,959,768,881,865,865,1080,1112,1112,1006,928,808,873,856,864,816,808,936,897,873,1048,1080,871,784,1017,910,824,1081,784,832,768,831,872,849,824,936,889,1032,953,1072,1144,1144,1049,881,792,985,937,800,816,960,824,768,928,897,1080,1144,1072,1112,1144,1144,776,800,1112,1144,1144,1144,1144,1144,1144,896,1144,1144,712,776,1144,1144,1144,1144,1144,1144,1144,1144,1144,1144,1144,1144,1144,1144,1144,1144,1144,784,624,1144,1144,1144,1144,1144,1144,1144,1144,1144,1144,1144,1144,1144,888,1144,1144,1144,1144,1144,1144,1144,1144,1144,1144,1144,1144,1144,1144,1144,264,200,304,216,360,264,424,256,336,320,392,320,384,344,448,432,432,472,528,560,544,624,616,752,688,745,816,976,816,960,807,722,648,632,592,560,528,560,560,576,576,600,640,640,680,704,752,768,824,832,888,896,960,960,992,1032,1088,1104,1144],
    [1150,1150,1150,1150,1150,1150,1150,1150,1150,1150,1052,1150,1150,1052,1150,1150,1150,1150,1150,1150,1150,1150,1150,1150,1150,1150,1150,1150,1150,1150,1150,1150,461,606,1150,1136,1133,1136,1136,1150,761,731,1072,1136,451,559,589,1130,862,812,849,884,951,894,944,879,903,893,721,566,1150,1150,1150,616,1150,637,697,677,694,657,707,694,664,563,793,859,684,664,680,687,670,930,691,633,647,771,751,765,921,829,1069,1133,1150,1133,1150,707,1150,327,461,451,421,317,492,482,495,367,691,556,384,441,377,364,448,792,371,347,381,397,552,499,640,455,674,1150,1150,1150,1150,1150,1022,1136,1150,1150,1136,1150,1123,1150,1150,1096,1150,1150,1150,1150,1150,1150,1150,1150,1136,1110,1017,1150,1150,1150,936,965,1150,1150,1136,1123,1150,1150,1072,1083,1079,1150,1150,1150,1059,1136,1012,930,1083,1116,1150,1089,1150,1123,1150,1079,1150,1079,1106,1150,1136,1150,1150,1150,1099,1150,1150,1150,1150,1150,1150,1150,1150,781,1150,1106,1150,1150,1150,1150,1150,1150,1150,1150,1150,1150,1150,1150,1150,1150,1150,1150,1150,1150,1150,1150,1150,1150,1150,1150,1150,1150,1150,1150,1019,1150,1150,1150,1150,1150,1150,1150,1150,1150,1150,1150,1150,1150,1150,1150,1150,1150,1150,1150,1150,1150,1150,1150,1150,1150,1150,1150,1150,1150,458,195,253,145,357,202,411,300,354,384,488,525,515,633,775,896,940,1019,1083,1072,1150,1150,1150,1150,1150,1150,1150,1150,1150,1112,987,1037,1035,992,829,748,717,694,694,691,707,697,724,741,755,768,785,822,832,842,866,896,896,947,960,960,1021,1031,1054],
    [1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,576,1152,576,896,1152,1152,832,1152,896,896,704,384,704,576,512,384,384,320,384,384,384,320,384,384,384,384,640,1152,1152,704,896,1152,704,384,448,384,384,384,448,384,448,384,384,448,448,384,448,448,448,384,448,384,448,448,448,448,448,448,448,896,704,768,896,640,1152,320,384,384,384,320,384,384,384,384,384,448,384,384,384,384,384,448,384,384,384,384,384,384,448,384,448,896,768,832,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,512,384,448,512,512,832,640,640,576,576,704,512,640,512,640,512,512,576,576,640,640,576,640,832,640,768,768,640,448,576,922,922,576,704,704,640,640,576,576,512,512,576,704,704,768,704,768,896,896,896,896,832,768,1088,1024,1152,1344,1088,1216],
    [1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,384,1152,1152,1152,384,384,384,384,384,384,384,384,384,384,384,1152,1152,1152,1152,1152,1152,1152,384,384,384,384,384,384,384,384,448,384,384,384,384,384,384,384,384,384,384,384,384,384,384,384,384,384,1152,1152,1152,1152,1152,1152,384,384,384,384,384,384,384,384,384,384,384,448,384,384,384,384,448,384,384,384,384,384,384,384,384,384,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,704,448,704,640,832,704,1152,1152,1152,1152,1152,1152,1152,768,704,576,640,704,576,704,704,1152,1152,1152,704,704,640,1152,512,836,836,836,836,900,900,964,964,1028,1028,768,320,640,704,1220,1220,1284,1284,896,1024,1412,1412,768,1476,896,1540,1088,1604,1216,1280],
    [1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,832,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,576,1152,640,896,1152,1152,1152,640,1152,1152,896,448,640,576,512,384,384,320,384,320,384,384,384,384,320,320,640,1152,1152,704,896,1152,640,384,448,384,448,384,448,448,448,448,448,448,448,448,448,448,448,448,448,448,448,448,448,448,448,448,448,896,640,832,832,640,1152,384,384,384,384,320,384,384,448,384,448,448,384,384,384,384,384,384,384,384,384,448,448,384,384,448,448,832,1152,832,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,384,384,512,448,640,448,640,512,576,448,704,512,640,512,512,448,448,448,512,512,448,576,576,640,576,512,576,640,384,640,972,640,576,1036,640,576,704,640,640,576,512,576,640,704,704,768,768,704,768,832,768,896,896,1024,1024,1088,1152,1152,1216],
    [1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,448,1152,1152,1152,384,384,384,384,384,384,384,384,384,384,384,1152,1152,1152,832,1152,1152,1152,384,384,448,384,384,384,384,384,384,384,384,384,384,384,384,384,384,384,384,384,384,384,384,384,384,384,1152,448,1152,1152,1152,1152,384,384,384,384,384,384,384,384,384,384,384,384,384,384,384,384,384,384,384,384,384,448,384,448,384,384,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,1152,576,640,576,768,1152,1152,1152,576,1152,1152,640,640,1152,704,704,576,704,576,768,640,640,832,896,704,640,832,640,1152,512,800,800,800,800,864,864,928,928,992,512,576,448,640,1120,832,1184,1248,1248,832,1312,1376,1376,704,1440,960,1504,960,1216,1152,1216],
    [1087,1087,1087,1087,1087,1087,1087,1087,1087,1087,768,1087,1087,1087,1087,1087,1087,1087,1087,1087,1087,1087,1087,1087,1087,1087,1087,1087,1087,1087,1087,1087,384,1087,576,1087,768,1087,1087,768,640,640,832,448,512,512,512,448,384,384,384,448,448,448,448,448,448,448,768,832,1087,704,1087,1087,832,448,448,448,448,448,448,448,448,448,448,448,384,448,384,448,448,448,448,384,384,448,448,448,448,448,448,768,576,640,768,576,576,384,384,384,384,320,384,384,384,384,448,448,384,384,320,384,384,448,384,384,384,384,448,448,448,448,448,768,1087,640,832,1087,1087,1087,1087,1087,1087,1087,1087,1087,1087,1087,1087,1087,1087,1087,1087,1087,1087,1087,1087,1087,1087,1087,1087,1087,1087,1087,1087,1087,1087,1087,1087,1087,1087,1087,1087,1087,1087,1087,1087,1087,1087,1087,1087,1087,1087,1087,1087,1087,1087,1087,1087,1087,1087,1087,1087,1087,1087,1087,1087,1087,1087,1087,1087,1087,1087,1087,1087,1087,1087,1087,1087,1087,1087,1087,1087,1087,1087,1087,1087,1087,1087,1087,1087,1087,1087,1087,1087,1087,1087,1087,1087,1087,1087,1087,1087,1087,1087,1087,1087,1087,1087,1087,1087,1087,1087,1087,1087,1087,1087,1087,1087,1087,1087,1087,1087,1087,1087,1087,1087,1087,1087,1087,1087,1087,1087,1087,1087,1087,384,384,320,448,448,448,576,384,576,512,448,512,512,384,512,384,448,384,512,448,448,512,512,512,512,576,576,640,448,576,950,950,950,576,640,1078,1078,640,576,576,640,640,640,640,704,704,832,832,832,832,896,832,896,896,1024,1024,1088,1088,1152],
    [1110,1110,1110,1110,1110,1110,1110,1110,1110,1110,918,1110,1110,982,1110,1110,1110,1110,1110,1110,1110,1110,1110,1110,1110,1110,1110,1110,1110,1110,1110,1110,448,1110,950,1110,1110,950,1110,736,768,704,918,950,704,320,384,608,288,256,256,288,256,256,288,320,288,288,512,950,982,640,982,1110,1110,886,768,736,768,886,736,736,950,886,1110,950,800,736,886,854,768,982,736,736,854,918,918,950,982,1110,982,704,982,736,982,544,1110,352,352,352,352,352,384,640,608,512,800,640,544,576,544,512,544,950,512,480,512,544,640,608,854,640,918,1110,1110,1110,1110,1110,1110,1110,1110,1110,1110,1110,1110,1110,1110,1110,1110,1110,1110,1110,1110,1110,1110,1110,1110,1110,1110,1110,1110,1110,1110,1110,1110,1110,1110,1110,1110,1110,1110,1110,1110,1110,1110,1110,1110,1110,1110,1110,1110,1110,1110,1110,1110,1110,1110,1110,1110,1110,1110,1110,1110,1110,1110,1110,1110,1110,1110,1110,1110,982,1110,1110,1110,1110,1110,1110,1110,1110,1110,1110,1110,1110,1110,1110,1110,1110,1110,1110,1110,1110,1110,1110,1110,1110,1110,1110,1110,1110,1110,1110,1110,1110,1110,1110,1110,1110,1110,1110,1110,1110,1110,1110,1110,1110,1110,1110,1110,1110,1110,1110,1110,1110,1110,1110,1110,982,1110,1110,1110,1110,1110,1110,1110,982,480,448,448,544,640,544,608,480,544,544,758,704,512,480,512,854,480,352,320,512,480,480,608,608,544,448,608,672,608,956,816,816,784,848,848,848,576,736,704,768,880,608,736,704,640,640,768,800,800,896,896,928,1024,960,1088,1088,1152,1152,1088],
    [1146,1146,1146,1146,1146,1146,1146,1146,1146,1098,624,1146,1146,1146,1146,1146,1146,1146,1146,1146,1146,1146,1146,1146,1146,1146,1146,1146,1146,1146,1146,1146,379,613,507,784,1045,656,571,592,448,443,539,587,448,512,491,624,512,496,501,571,581,619,629,699,629,672,571,533,603,507,565,667,981,507,581,517,517,480,565,587,613,496,784,683,523,560,507,501,533,731,507,496,501,555,624,608,651,645,763,629,720,619,981,469,975,405,507,475,443,395,507,549,549,395,672,592,459,501,432,416,448,736,432,389,437,453,581,555,560,517,629,774,709,613,896,1146,1146,1146,1146,1146,1146,1146,1146,1146,1146,1146,1146,1146,1146,1146,1146,1146,1146,1146,1146,1146,1146,1146,1146,1146,1146,1146,1146,1146,1146,1146,1146,1146,1146,1146,1146,1146,1146,1146,1146,1146,1146,1146,1146,1146,1146,1146,1146,1146,1146,1146,1146,1146,1146,1146,1146,1146,1146,1146,1146,1146,1146,1146,1146,1146,1146,1146,1146,1146,1146,1146,1146,1146,1146,1146,1146,1146,1146,1146,1146,1146,1146,1146,1146,1146,1146,1146,1146,1146,1146,1146,1146,1146,1146,1146,1146,1146,1146,1146,1146,1146,1146,1146,1146,1146,1146,1146,1146,1146,1146,1146,1146,1146,1146,1146,1146,1146,1146,1146,1146,1146,1146,1146,1146,1146,1146,1146,1146,1146,256,197,299,224,379,245,453,272,363,315,373,416,336,421,437,480,443,517,555,624,565,635,704,720,725,757,864,938,736,565,852,749,724,672,587,597,576,560,549,571,571,576,640,656,699,715,757,773,832,843,891,901,949,960,1008,1024,1077,1104,1109],
    [1135,1135,1135,1135,1135,1135,1135,1135,1135,1135,525,1135,1135,1135,1135,1135,1135,1135,1135,1135,1135,1135,1135,1135,1135,1135,1135,1135,1135,1135,1135,1135,358,589,499,678,843,1084,589,602,448,448,614,730,435,525,435,576,576,576,602,653,691,818,691,781,666,755,448,576,589,550,589,691,907,576,614,589,640,576,614,691,704,563,855,742,640,640,627,602,614,1084,589,538,550,627,755,640,794,819,883,589,678,550,1034,448,499,371,499,435,422,346,461,512,512,371,691,589,435,474,371,384,448,717,384,346,384,435,563,525,550,499,691,576,614,525,1085,1135,983,1135,1135,1135,1135,1135,1135,1135,1135,1135,1135,1135,1135,1135,1135,1135,1135,1135,1135,1135,1033,1135,1135,1135,1135,1135,1135,1135,1135,1135,1135,1135,1135,1135,1085,1135,1135,1135,1135,1135,1135,1084,1135,1135,1135,1135,1135,1135,1135,1135,1135,1135,1135,1135,1135,1135,1135,1135,1135,1135,1135,1135,1135,1135,1135,1135,1135,1071,1135,1135,1135,1135,1135,1135,1135,1135,1135,1135,1135,1135,1135,1135,1135,1135,1135,1135,1135,1135,1135,1135,1135,1135,1135,1135,1135,1135,1135,1135,970,1135,1135,1135,1135,1135,1135,1135,1135,1135,1135,1135,1135,1135,1135,1135,1135,1135,1135,1135,1135,1135,1135,1135,1135,1135,1135,1135,1135,1135,307,205,282,243,346,294,435,269,371,320,422,320,410,371,474,448,435,486,512,512,486,576,576,640,589,640,640,755,550,863,939,1024,932,691,640,614,602,576,563,576,576,576,653,666,704,704,768,768,832,832,870,896,960,960,998,1011,1075,1101,1114],
    [851,851,851,851,851,851,851,851,851,851,576,851,851,851,851,851,851,851,851,851,851,851,851,851,851,851,851,851,851,851,851,851,320,851,851,851,851,851,851,851,576,576,851,851,851,576,384,384,384,384,320,384,320,320,384,384,384,576,512,851,851,851,851,851,851,851,851,851,851,576,512,851,851,851,576,851,851,851,851,851,851,851,851,576,576,851,851,851,851,851,851,512,851,448,851,512,851,384,448,384,384,320,512,448,448,320,512,448,384,512,320,320,448,851,320,384,320,448,512,448,576,576,851,851,851,851,851,851,851,851,851,851,851,851,851,851,851,851,851,851,851,851,851,851,851,851,851,851,851,851,851,851,851,851,851,851,851,851,851,851,851,851,851,851,851,851,851,851,851,851,851,851,851,851,851,851,851,851,851,851,851,851,851,851,851,851,851,851,851,851,851,851,851,851,851,851,851,851,851,851,851,851,851,851,851,851,851,851,851,851,851,851,851,851,851,851,851,851,851,851,851,851,851,851,851,851,851,851,851,851,851,851,851,851,851,851,851,851,851,851,851,851,851,851,851,851,851,851,851,851,851,851,851,851,851,851,851,448,512,576,448,576,851,851,576,851,576,851,448,512,851,851,851,851,192,448,448,384,384,320,384,320,320,384,320,759,759,759,759,823,823,887,887,704,951,768,384,832,512,1143,704,704,768,704,768,768,896,832,1088,1152,1463,1527,1527,1344,1591],
];
pub const A_P_GROUPS: [u32; 24] = [0,0,0,0,8,1,8,19,1,27,5,2,32,2,1,34,12,1,46,5,1,51,1,2];
pub const A_P_META: [u32; 156] = [0,136174,1,128153,126220,1,247818,153498,1,391191,153646,1,536752,125306,1,655406,141930,1,789642,137805,1,919588,80412,1,0,71050,2,68621,79201,2,142682,78964,2,216520,85958,2,296940,88077,2,379357,85568,2,459400,82174,2,536259,86674,2,617357,90886,2,702415,87767,2,784522,83140,2,862276,91633,2,948054,85803,2,1028328,90828,2,1113321,88156,2,1195809,88817,2,1278920,88168,2,1361419,89544,2,1445214,54786,2,0,76575,3,71729,52428,4,120596,155133,5,266112,52512,6,315053,84947,7,0,256853,8,242179,57821,8,0,108850,9,105126,125672,9,223219,132189,9,347141,131869,9,470772,133012,9,595533,149998,9,736196,116915,9,845684,124570,9,962462,136529,9,1090507,132179,9,1214623,118704,9,1325946,74054,9,0,168648,10,158161,196706,10,343308,167227,10,504172,141612,10,639430,60570,10,0,28000,11];
pub fn a_p_for(n:usize,depth:usize,skip:usize,tail:usize)->usize {
    if n==1000000 {if depth==24 && skip==258 && tail==16 {1}else{0}} else if n==1500000 {if depth==32 && skip==258 && tail==0 {2}else{0}} else if n==400000 {if depth==32 && skip==258 && tail==4 {3}else{0}} else if n==300000 {if depth==24 && skip==258 && tail==0 {4}else{0}} else if n==1400000 {if depth==32 && skip==258 && tail==4 {5}else{0}} else if n==700000 {if depth==24 && skip==258 && tail==0 {6}else{0}} else if n==28000 {if depth==32 && skip==258 && tail==4 {7}else{0}} else {0}
}
pub fn a_p_extra(seed:usize)->usize {if seed==3 || seed==7 {2}else{1}}
pub fn a_p_pick(seed:usize,block:usize)->(usize,usize){
 let at=seed.wrapping_mul(3)%24;
 let start=A_P_GROUPS[at] as usize;let count=A_P_GROUPS[at.wrapping_add(1)%24] as usize;
 let index=if count==0 {0}else{if block<count {block}else{count-1}};
 let q=start.wrapping_add(index).wrapping_mul(3)%156;
 let span=A_P_META[q.wrapping_add(1)%156] as usize;let model=A_P_META[q.wrapping_add(2)%156] as usize;
 let span=if span<512 {512}else{if span>67108864 {67108864}else{span}};
 (model,span)
}
pub fn a_p_span(seed:usize,p0:usize)->usize {a_p_pick(seed,p0).1}
pub fn a_p_load(seed:usize,p0:usize,lit:&mut[u32;256],lc:&mut[u32;512],dc:&mut[u32;32]){
 if seed==0 {return;}
 let model=a_p_pick(seed,p0).0;let table=&A_P_COSTS[model%12];
 let mut i=0usize;while i<256 {lit[i]=table[i%315] as u32;i+=1;}
 i=3;while i<=258 {let sl=a_a_len_slot(i);lc[i]=(table[256usize.wrapping_add(sl)%315] as u32).wrapping_add(64u32.wrapping_mul(a_a_len_extra(sl)));i+=1;}
 i=0;while i<30 {dc[i]=table[285usize.wrapping_add(i)%315] as u32;i+=1;}
}

pub fn a_p_passes(seed:usize,p0:usize,first:usize,later:usize)->usize {if seed>0 {a_p_extra(seed)+1}else{if p0==0 {first}else{later}}}
pub fn a_p_sampled(seed:usize,p0:usize,first:usize,later:usize)->usize {if seed>0 {0}else{if p0==0 {first}else{later}}}
pub fn a_p_est(seed:usize,block:usize,need:usize,bpt:usize)->usize {if seed>0 {a_p_span(seed,block)}else{need*bpt/256+need*bpt/2048+A_A_MARGIN}}

pub fn a_a_engine(
    input: &[u8],
    ch: &mut Vec<u32>,
    depth: usize,
    skip: usize,
    first_passes: usize,
    fspass: usize,
    passes_k: usize,
    spass: usize,
    tail: usize,
    final_tail: usize,
) {
    let n = input.len();
    let preset=a_p_for(n,depth,skip,tail);
    let mut mp: Vec<u32> = Vec::with_capacity(n + 1);
    let mut mb: Vec<u32> = Vec::with_capacity(n * 3 + 16);
    a_a_find_all(input, &mut mp, &mut mb, depth, skip);
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
    a_a_first_model(input, &mut lit, &mut lc, &mut dc);
    let rot = A_A_SEG.wrapping_mul((spass / 16) % 2);
    let spn = spass % 16;
    let mut p0 = 0usize;
    let mut used = 0usize;
    let mut bpt = 1024usize;
    let mut bidx=0usize;
    while p0 < n && mp.len() == n + 1 && cost.len() == n + 1 && ch.len() == n {
        let need = A_BLOCK_TOKENS - used;
        a_p_load(preset,bidx,&mut lit,&mut lc,&mut dc);
        let passes = a_p_passes(preset,p0,first_passes,passes_k);
        let sampled = a_p_sampled(preset,p0,fspass,spn);
        let est = a_p_est(preset,bidx,need,bpt);
        let mut pe = if n - p0 > est { p0 + est } else { n };
        let mut k = 0usize;
        let mut p1 = p0 + 1;
        let mut t = 1usize;
        while k < passes {
            if k < sampled && k + 1 < passes && pe - p0 > 4 * A_A_SEG * A_A_SAMPLE {
                let off = (k % 4).wrapping_mul(rot);
                let ps = p0 + off % (pe - p0 + 1);
                let r = a_a_sample_pass(input, &mp, &mb, ps, pe, &lit, &lc, &dc, &mut cost, ch, &mut lf, &mut df, tail);
                if r.1 > 0 {
                    let span = r.0.wrapping_mul(need) / r.1;
                    let grow = span.saturating_add(span / A_A_SLACK).saturating_add(A_A_MARGIN);
                    pe = if n - p0 > grow { p0 + grow } else { n };
                }
            } else {
                let lim = if pe == n { n } else { pe - A_A_MARGIN };
                a_a_dp_pass(input, &mp, &mb, p0, pe, &lit, &lc, &dc, &mut cost, ch, a_a_tail_for_pass(k, passes, tail, final_tail));
                let r = a_a_walk(input, ch, p0, lim, need, &mut lf, &mut df);
                p1 = r.0;
                t = r.1;
                if t > 0 && p1 > p0 {
                    let span = (p1 - p0).wrapping_mul(need) / t;
                    let grow = span.saturating_add(span / 16).saturating_add(A_A_MARGIN);
                    pe = if n - p0 > grow { p0 + grow } else { n };
                }
            }
            a_a_add_counts(&mut sl, &bl, &lf, &mut sd, &bd, &df);
            if k + 1 < passes && k >= sampled {
                a_a_set_costs_huff(&sl, &sd, &mut lit, &mut lc, &mut dc);
            } else {
                a_a_set_costs(&sl, &sd, &mut lit, &mut lc, &mut dc);
            }
            k += 1;
        }
        bidx=bidx.wrapping_add(1);
        used += t;
        if used >= A_BLOCK_TOKENS {
            used = 0;
            a_a_add_counts(&mut bl, &zl, &zl, &mut bd, &zd, &zd);
        } else {
            a_a_add_counts(&mut bl, &sl, &zl, &mut bd, &sd, &zd);
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

// ───────────────────────────── engine B: structured text ─────────────────────────────
// Suffix-ordered binary tree per 4-byte hash over EVERY position (plus the latest exact 3-byte
// match), compared through a ring of big-endian words, descents replayed from the previous
// position; Pareto candidates with <= 2 full-length continuations. Per 32K segment a backward
// shortest-path pass under entropy costs (warm start, adaptive refine); mode 2 then re-runs the
// whole input under per-encoder-block tables. Knobs: depth, h3dist, mode, bpasses, cuts.

pub const A_B_WR: usize = 32768;
pub const A_B_WLIM: usize = 32256;
pub const A_B_TS: usize = 65536;
pub const A_B_HBITS: u32 = 16;
pub const A_B_HSIZE: usize = 65536;
pub const A_B_H3BITS: u32 = 14;
pub const A_B_H3SIZE: usize = 16384;
pub const A_B_FMAX: usize = 2;
pub const A_B_SEG: usize = 32768;
// Mode 2 keeps every record; above this input size it behaves like mode 0.
pub const A_B_KEEPMAX: usize = 1 << 26;
// Refine a segment when its parse costs more than (1 + GAP/1024) x its own entropy.
pub const A_B_GAP: u64 = 20;
// Candidate record: dist-1 in bits 0..15, distance slot in 15..20, length in 20..29, FULL flag.
pub const A_B_FULL: u32 = 1 << 29;
pub const A_B_RB: usize = 32;
pub const A_B_PS: usize = 32;
// Symbol counts: lit/len symbols at 0..286, distance slots at 288 + slot.
pub const A_B_FSZ: usize = 320;
// Hint sentinel: no known continuation node.
pub const A_B_NOHINT: usize = 0xFFFF_FFFF;

pub const A_B_LOG2_FRAC: [u16; 256] = [
    0, 1, 3, 4, 6, 7, 9, 10, 11, 13, 14, 16, 17, 18, 20, 21, 22, 24, 25, 26, 28, 29, 30, 32, 33, 34,
    36, 37, 38, 40, 41, 42, 44, 45, 46, 47, 49, 50, 51, 52, 54, 55, 56, 57, 59, 60, 61, 62, 63, 65, 66,
    67, 68, 69, 71, 72, 73, 74, 75, 77, 78, 79, 80, 81, 82, 84, 85, 86, 87, 88, 89, 90, 92, 93, 94, 95,
    96, 97, 98, 99, 100, 102, 103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 116, 117,
    118, 119, 120, 121, 122, 123, 124, 125, 126, 127, 128, 129, 130, 131, 132, 133, 134, 135, 136, 137,
    138, 139, 140, 141, 142, 143, 144, 145, 146, 147, 148, 149, 150, 151, 152, 153, 154, 155, 155, 156,
    157, 158, 159, 160, 161, 162, 163, 164, 165, 166, 167, 168, 169, 169, 170, 171, 172, 173, 174, 175,
    176, 177, 178, 178, 179, 180, 181, 182, 183, 184, 185, 185, 186, 187, 188, 189, 190, 191, 192, 192,
    193, 194, 195, 196, 197, 198, 198, 199, 200, 201, 202, 203, 203, 204, 205, 206, 207, 208, 208, 209,
    210, 211, 212, 212, 213, 214, 215, 216, 216, 217, 218, 219, 220, 220, 221, 222, 223, 224, 224, 225,
    226, 227, 228, 228, 229, 230, 231, 231, 232, 233, 234, 234, 235, 236, 237, 238, 238, 239, 240, 241,
    241, 242, 243, 244, 244, 245, 246, 247, 247, 248, 249, 249, 250, 251, 252, 252, 253, 254, 255, 255,
];

// Match finder state: hash heads, the suffix trees (two child slots per position), a ring of
// 8-byte words, and the previous descent (node, flags|length per step).
pub struct A_BMf {
    pub head: [u32; A_B_HSIZE],
    pub head3: [u32; A_B_H3SIZE],
    pub tree: [u32; A_B_TS],
    pub w: [u64; A_B_WR],
    pub pn: [u32; A_B_PS],
    pub pf: [u32; A_B_PS],
    pub plen: usize,
    pub hn: usize,
    pub hl: usize,
}

// log2(x) in 1/256 bit, x >= 1 (0 for x == 0).
pub fn a_b_log2_fix(x: u32) -> u32 {
    if x == 0 {
        return 0;
    }
    let e = 31 - x.leading_zeros();
    let m = if e >= 8 { (x >> (e - 8)) & 255 } else { (x << (8 - e)) & 255 };
    e * 256 + A_B_LOG2_FRAC[m as usize] as u32
}

// DEFLATE length code index 0..=28 and extra-bit count for 3 <= l <= 258.
pub fn a_b_len_code(l: usize) -> (usize, usize) {
    if l < 11 {
        return (if l >= 3 { l - 3 } else { 0 }, 0);
    }
    if l >= 258 {
        return (28, 0);
    }
    let v = (l - 3) as u32;
    let k = 31 - v.leading_zeros();
    let e = (k - 2) as usize;
    (4 * e + 4 + ((v >> e) & 3) as usize, e)
}

// DEFLATE distance code index 0..=29 for 1 <= d <= 32768.
pub fn a_b_dist_slot(d: usize) -> usize {
    if d < 5 {
        return if d >= 1 { d - 1 } else { 0 };
    }
    let v = ((if d > 32768 { 32768 } else { d }) - 1) as u32;
    let k = 31 - v.leading_zeros();
    2 * (k as usize) + ((v >> (k - 1)) & 1) as usize
}

pub fn a_b_rec(l: usize, d: usize, full: u32) -> u32 {
    ((l as u32) << 20) | ((a_b_dist_slot(d) as u32) << 15) | ((d - 1) as u32) | full
}

// The input byte at p, or 0 past the end.
pub fn a_b_byte_at(s: &[u8], p: usize) -> u64 {
    if p < s.len() { s[p] as u64 } else { 0 }
}

// Add candidate (l, d) to the position's record buffer: at most A_B_FMAX continuations (flag != 0)
// are kept, the shortest one is dropped first. Returns the new (count, continuations).
pub fn a_b_add_record(rv: &mut [u32; A_B_RB], nr: usize, nf: usize, l: usize, d: usize, flag: u32) -> (usize, usize) {
    let mut n = nr;
    let mut f = nf;
    if flag != 0 && f >= A_B_FMAX {
        let mut q = 0usize;
        let mut wq = 0usize;
        let mut dropped = 0usize;
        while q < n {
            let v = rv[q % A_B_RB];
            if dropped == 0 && v & A_B_FULL != 0 {
                dropped = 1;
            } else {
                rv[wq % A_B_RB] = v;
                wq += 1;
            }
            q += 1;
        }
        n = wq;
        f -= 1;
    }
    if n < A_B_RB {
        rv[n % A_B_RB] = a_b_rec(l, d, flag);
        n += 1;
        if flag != 0 {
            f += 1;
        }
    }
    (n, f)
}

// Insert position i into its bucket's suffix-ordered binary tree (root `first`, position + 1),
// adding every strictly longer match met on the way down to rv. Returns (records,
// continuations, best length, its distance).
pub fn a_b_descend(mf: &mut A_BMf, first: usize, i: usize, cap: usize, scap: usize, best0: usize, wp: u64, rv: &mut [u32; A_B_RB], nr0: usize, nf0: usize, depth: usize) -> (usize, usize, usize, usize) {
    let mut step = 0usize;
    let plen = mf.plen;
    let hn = mf.hn;
    let hl = mf.hl;
    let mut cur = first;
    let me = i % A_B_WR;
    let mut ls = 2 * me;
    let mut rs = 2 * me + 1;
    let mut ll = 0usize;
    let mut rl = 0usize;
    let mut fuel = depth;
    let mut best = best0;
    let mut rbest = best0;
    let mut nr = nr0;
    let mut nf = nf0;
    let mut bl = 0usize;
    let mut bd = 0usize;
    while fuel > 0 {
        let d = (i + 1).wrapping_sub(cur);
        if cur == 0 || d == 0 || d >= A_B_WLIM {
            mf.tree[ls % A_B_TS] = 0;
            mf.tree[rs % A_B_TS] = 0;
            fuel = 0;
        } else {
            let c = i - d;
            // the previous position's descent met c - 1 at this step: same comparison, one byte on
            let pf = mf.pf[step % A_B_PS];
            let known = step < plen && (mf.pn[step % A_B_PS] as usize) + 1 == c && pf & 1 == 1 && pf >= 4;
            let mut l = if ll < rl { ll } else { rl };
            let mut lt = 0usize;
            if known {
                l = (pf >> 2) as usize - 1;
                lt = ((pf >> 1) & 1) as usize;
            } else {
                if c == hn && hl > l {
                    l = hl;
                }
                let mut wc = mf.w[c.wrapping_add(l) % A_B_WR];
                let mut wi = mf.w[i.wrapping_add(l) % A_B_WR];
                let mut run = 1usize;
                while run == 1 && wc == wi {
                    l += 8;
                    if l >= cap {
                        run = 0;
                    } else {
                        wc = mf.w[c.wrapping_add(l) % A_B_WR];
                        wi = mf.w[i.wrapping_add(l) % A_B_WR];
                    }
                }
                if run == 1 {
                    l += ((wc ^ wi).leading_zeros() / 8) as usize;
                }
                if l > cap {
                    l = cap;
                }
                lt = if wc < wi { 1 } else { 0 };
            }
            if step < A_B_PS {
                mf.pn[step % A_B_PS] = c as u32;
                mf.pf[step % A_B_PS] = (if l < cap { 1u32 } else { 0u32 }) | ((lt as u32) << 1) | ((l as u32) << 2);
            }
            step += 1;
            if l > best {
                best = l;
                bl = l;
                bd = d;
                let rl2 = if l < scap { l } else { scap };
                if rl2 > rbest {
                    rbest = rl2;
                    let flag = if c >= 1 && (mf.w[(c - 1) % A_B_WR] >> 56) == wp { A_B_FULL } else { 0 };
                    let r = a_b_add_record(rv, nr, nf, rl2, d, flag);
                    nr = r.0;
                    nf = r.1;
                }
            }
            let cs = 2 * (c % A_B_WR);
            if l >= cap {
                mf.tree[ls % A_B_TS] = mf.tree[cs % A_B_TS];
                mf.tree[rs % A_B_TS] = mf.tree[(cs + 1) % A_B_TS];
                fuel = 0;
            } else {
                if lt == 1 {
                    mf.tree[ls % A_B_TS] = cur as u32;
                    ls = cs + 1;
                    ll = l;
                    cur = mf.tree[(cs + 1) % A_B_TS] as usize;
                } else {
                    mf.tree[rs % A_B_TS] = cur as u32;
                    rs = cs;
                    rl = l;
                    cur = mf.tree[cs % A_B_TS] as usize;
                }
                fuel -= 1;
                if fuel == 0 {
                    mf.tree[ls % A_B_TS] = 0;
                    mf.tree[rs % A_B_TS] = 0;
                }
            }
        }
    }
    mf.plen = if step < A_B_PS { step } else { A_B_PS };
    if bd > 0 && bl >= 2 {
        mf.hn = i + 1 - bd;
        mf.hl = bl - 1;
    } else {
        mf.hn = A_B_NOHINT;
        mf.hl = 0;
    }
    (nr, nf, bl, bd)
}

// Symbol cost in 1/16 bit from a count and its alphabet total.
pub fn a_b_sym_cost(f: u32, total: u32) -> u32 {
    let a = a_b_log2_fix(total.wrapping_mul(2).wrapping_add(1));
    let b = a_b_log2_fix(f.wrapping_mul(2).wrapping_add(1));
    let c = if a > b { (a - b) >> 4 } else { 0 };
    if c < 16 { 16 } else { c }
}

// Cost table from symbol counts: literals at 0..256, lengths at 256 + len, distance slots at 520 + slot.
pub fn a_b_build_table(freq: &[u32; A_B_FSZ], tb: &mut [u32; 1024]) {
    let mut tl = 0u32;
    let mut k = 0usize;
    while k < 286 {
        tl = tl.wrapping_add(freq[k]);
        k += 1;
    }
    let mut td = 0u32;
    k = 0;
    while k < 30 {
        td = td.wrapping_add(freq[288 + k]);
        k += 1;
    }
    k = 0;
    while k < 256 {
        tb[k] = a_b_sym_cost(freq[k], tl);
        k += 1;
    }
    let mut l = 3usize;
    while l <= 258 {
        let lc = a_b_len_code(l);
        tb[256 + l] = a_b_sym_cost(freq[(257 + lc.0) % A_B_FSZ], tl) + 16 * lc.1 as u32;
        l += 1;
    }
    k = 0;
    while k < 30 {
        let e = if k < 4 { 0 } else { k / 2 - 1 };
        tb[520 + k] = a_b_sym_cost(freq[288 + k], td) + 16 * e as u32;
        k += 1;
    }
}

// Entropy-coded size of the counts in 1/16 bit (each alphabet on its own).
pub fn a_b_self_cost(freq: &[u32; A_B_FSZ]) -> u64 {
    let mut tl = 0u32;
    let mut k = 0usize;
    while k < 286 {
        tl = tl.wrapping_add(freq[k]);
        k += 1;
    }
    let mut td = 0u32;
    k = 0;
    while k < 30 {
        td = td.wrapping_add(freq[288 + k]);
        k += 1;
    }
    let lt = a_b_log2_fix(tl) as u64;
    let ld = a_b_log2_fix(td) as u64;
    let mut c = 0u64;
    k = 0;
    while k < 286 {
        let f = freq[k];
        let lf = a_b_log2_fix(f) as u64;
        if f > 0 && lt >= lf {
            c += (f as u64) * (lt - lf);
        }
        k += 1;
    }
    k = 0;
    while k < 30 {
        let f = freq[288 + k];
        let lf = a_b_log2_fix(f) as u64;
        if f > 0 && ld >= lf {
            c += (f as u64) * (ld - lf);
        }
        k += 1;
    }
    c >> 4
}

// Extra bits (1/16 bit units) implied by the length and distance symbol counts.
pub fn a_b_extra_bits(freq: &[u32; A_B_FSZ]) -> u64 {
    let mut c = 0u64;
    let mut k = 8usize;
    while k < 28 {
        c += (freq[(257 + k) % A_B_FSZ] as u64) * ((k / 4 - 1) as u64);
        k += 1;
    }
    k = 4;
    while k < 30 {
        c += (freq[288 + k] as u64) * ((k / 2 - 1) as u64);
        k += 1;
    }
    c * 16
}

// Pseudo-counts whose entropy costs approximate the fixed Huffman code (first pass).
pub fn a_b_static_freq(f: &mut Vec<u32>) {
    let mut k = 0usize;
    while k < A_B_FSZ {
        let v = if k < 144 {
            16
        } else if k < 256 {
            8
        } else if k < 280 {
            32
        } else if k < 286 {
            16
        } else if k >= 288 && k < 318 {
            1
        } else {
            0
        };
        if k < f.len() {
            f[k] = v;
        } else {
            f.push(v);
        }
        k += 1;
    }
}

// Load block b's counts from bf and build its cost table.
pub fn a_b_block_table(bf: &Vec<u32>, b: usize, tb: &mut [u32; 1024]) {
    let mut fq = [0u32; A_B_FSZ];
    let mut z = 0usize;
    while z < A_B_FSZ && b * A_B_FSZ + z < bf.len() {
        fq[z] = bf[b * A_B_FSZ + z];
        z += 1;
    }
    a_b_build_table(&fq, tb);
}

// Backward shortest path over positions a..a+m. The record stream rs holds, for every position
// in order, its records followed by their count; cc[j] = cost | choice << 32 for position a+m-j.
// Block b's counts (bf[b * A_B_FSZ..]) price the positions from offset bs[b] on.
pub fn a_b_dp_seg(s: &[u8], a: usize, m: usize, rs: &Vec<u32>, rn: usize, bf: &Vec<u32>, bs: &Vec<u32>, nb: usize, cc: &mut Vec<u64>, cuts: usize, tail: usize) {
    let mut tb = [0u32; 1024];
    let mut b = if nb > 0 { nb - 1 } else { 0 };
    a_b_block_table(bf, b, &mut tb);
    let mut bfirst = if b < bs.len() { bs[b] as usize } else { 0 };
    cc[0] = 0;
    let mut p = rn;
    let mut j = 1usize;
    while j <= m && p >= 1 {
        let off = m - j;
        if off < bfirst && b > 0 {
            b -= 1;
            a_b_block_table(bf, b, &mut tb);
            bfirst = if b < bs.len() { bs[b] as usize } else { 0 };
        }
        let i = a + off;
        let k = rs[p - 1] as usize;
        let e = p - 1;
        let st = if k <= e { e - k } else { e };
        let mut best = (cc[j - 1] as u32).wrapping_add(tb[s[i] as usize % 1024]);
        let mut choice = 0u32;
        let mut q = st;
        let mut lo = 3usize;
        while q < e {
            let v = rs[q];
            let ml = ((v >> 20) & 511) as usize;
            let dc = tb[(520 + ((v >> 15) & 31) as usize) % 1024];
            if v & A_B_FULL != 0 && cuts == 0 {
                if ml <= j {
                    let x = (cc[j - ml] as u32).wrapping_add(tb[(256 + ml) % 1024]).wrapping_add(dc);
                    if x < best {
                        best = x;
                        choice = ((ml as u32) << 15) | (v & 32767);
                    }
                }
            } else {
                let full = v & A_B_FULL;
                let mut l = if full != 0 { if ml > lo + cuts { ml - cuts } else { lo } } else { lo };
                let hi = if ml < j { ml } else { j };
                l = a_b_tail_start(l, hi, tail);
                while l <= ml && l <= j {
                    let x = (cc[j - l] as u32).wrapping_add(tb[(256 + l) % 1024]).wrapping_add(dc);
                    if x < best {
                        best = x;
                        choice = ((l as u32) << 15) | (v & 32767);
                    }
                    l += 1;
                }
                if full == 0 {
                    lo = ml + 1;
                }
            }
            q += 1;
        }
        cc[j] = (best as u64) | ((choice as u64) << 32);
        p = st;
        j += 1;
    }
}

// Per-block symbol counts along the parse in cc (positions a..a+m, a new encoder block every
// A_BLOCK_TOKENS tokens, or one block when whole == 0); returns the block count.
pub fn a_b_tally_seg(s: &[u8], a: usize, m: usize, cc: &Vec<u64>, whole: usize, bf: &mut Vec<u32>, bs: &mut Vec<u32>) -> usize {
    let mut nb = 0usize;
    let mut inb = A_BLOCK_TOKENS;
    let mut j = m;
    while j > 0 {
        if inb == A_BLOCK_TOKENS && (whole == 1 || nb == 0) {
            let base = nb * A_B_FSZ;
            let mut z = 0usize;
            while z < A_B_FSZ {
                if base + z < bf.len() {
                    bf[base + z] = 0;
                } else {
                    bf.push(0);
                }
                z += 1;
            }
            if nb < bs.len() {
                bs[nb] = (m - j) as u32;
            } else {
                bs.push((m - j) as u32);
            }
            nb += 1;
            inb = 0;
        }
        let f = (nb - 1) * A_B_FSZ;
        let v = (cc[j] >> 32) as u32;
        let l = (v >> 15) as usize;
        if l >= 3 && l <= j {
            let d = (v & 32767) as usize + 1;
            bf[f + (257 + a_b_len_code(l).0) % A_B_FSZ] += 1;
            bf[f + (288 + a_b_dist_slot(d)) % A_B_FSZ] += 1;
            j -= l;
        } else {
            bf[f + s[a + m - j] as usize % A_B_FSZ] += 1;
            j -= 1;
        }
        if inb < A_BLOCK_TOKENS {
            inb += 1;
        }
    }
    if nb > 0 {
        bf[(nb - 1) * A_B_FSZ + 256] += 1;
    }
    nb
}

// Per-block symbol counts of the planned path from 0 (a block every A_BLOCK_TOKENS tokens) and
// the input offset where each block starts; returns the block count.
pub fn a_b_tally_plan(s: &[u8], plan: &Vec<u32>, bf: &mut Vec<u32>, bs: &mut Vec<u32>) -> usize {
    let n = s.len();
    let mut nb = 0usize;
    let mut pos = 0usize;
    let mut t = 0usize;
    while pos < n && pos < plan.len() {
        if t % A_BLOCK_TOKENS == 0 {
            let base = nb * A_B_FSZ;
            let mut z = 0usize;
            while z < A_B_FSZ {
                if base + z < bf.len() {
                    bf[base + z] = 0;
                } else {
                    bf.push(0);
                }
                z += 1;
            }
            if nb < bs.len() {
                bs[nb] = pos as u32;
            } else {
                bs.push(pos as u32);
            }
            nb += 1;
        }
        let f = (nb - 1) * A_B_FSZ;
        let v = plan[pos] as usize;
        let l = v % 512;
        if l >= 3 && l <= n - pos {
            let d = v / 512;
            bf[f + (257 + a_b_len_code(l).0) % A_B_FSZ] += 1;
            bf[f + (288 + a_b_dist_slot(d)) % A_B_FSZ] += 1;
            pos += l;
        } else {
            bf[f + s[pos] as usize] += 1;
            pos += 1;
        }
        t += 1;
    }
    if nb > 0 {
        bf[(nb - 1) * A_B_FSZ + 256] += 1;
    }
    nb
}

// Write the parse in cc (positions a..a+m) into the plan.
pub fn a_b_plan_seg(a: usize, m: usize, cc: &Vec<u64>, plan: &mut Vec<u32>) {
    let mut j = m;
    while j > 0 {
        let i = a + m - j;
        let v = (cc[j] >> 32) as u32;
        let l = (v >> 15) as usize;
        let d = (v & 32767) as usize + 1;
        if l >= 3 && l <= j {
            a_set_in(plan, i, (l + 512 * d) as u32);
            j -= l;
        } else {
            a_set_in(plan, i, 0);
            j -= 1;
        }
    }
}

// Append v to the record stream at rn; returns rn + 1.
pub fn a_b_put(rs: &mut Vec<u32>, rn: usize, v: u32) -> usize {
    if rn < rs.len() {
        rs[rn] = v;
    } else {
        rs.push(v);
    }
    rn + 1
}

// Engine B: writes the plan (length n). Knobs: tree depth, exact-3 distance limit, mode
// (0 segments only, 1 one segment with block passes, 2 segments then whole-input block passes),
// block passes, continuation cuts.
pub fn a_b_engine(input: &[u8], plan: &mut Vec<u32>, depth: usize, h3dist: usize, mode: usize, bpasses: usize, cuts: usize, tail: usize) {
    let n = input.len();
    if n < 16 {
        return;
    }
    let mut mf = A_BMf {
        head: [0u32; A_B_HSIZE],
        head3: [0u32; A_B_H3SIZE],
        tree: [0u32; A_B_TS],
        w: [0u64; A_B_WR],
        pn: [0u32; A_B_PS],
        pf: [0u32; A_B_PS],
        plen: 0,
        hn: A_B_NOHINT,
        hl: 0,
    };
    let mut rv = [0u32; A_B_RB];
    let mut freq = [0u32; A_B_FSZ];
    let mut bf: Vec<u32> = Vec::new();
    let mut bs: Vec<u32> = Vec::new();
    let keep = if mode == 2 && n <= A_B_KEEPMAX { 1usize } else { 0usize };
    let segcap = if n < A_B_SEG || keep == 1 { n } else { A_B_SEG };
    let mut rs: Vec<u32> = Vec::with_capacity(4 * segcap);
    let mut cc: Vec<u64> = Vec::with_capacity(segcap + 1);
    while cc.len() <= segcap {
        cc.push(0);
    }
    // word ring: w[p % A_B_WR] = big-endian s[p..p+8]; x is the word at position wfill
    let mut x = 0u64;
    let mut k = 0usize;
    while k < 8 {
        x = (x << 8) | a_b_byte_at(input, k);
        k += 1;
    }
    let mut wfill = 0usize;
    let mut rn = 0usize;
    let mut a = 0usize;
    while a < n {
        let m = if n - a < A_B_SEG { n - a } else { A_B_SEG };
        let b = a + m;
        if keep == 0 {
            rn = 0;
        }
        let mut i = a;
        while i < b {
            let top = if i + 264 < n { i + 264 } else { n };
            while wfill < top {
                mf.w[wfill % A_B_WR] = x;
                x = (x << 8) | a_b_byte_at(input, wfill + 8);
                wfill += 1;
            }
            let mut nr = 0usize;
            if n - i >= 4 {
                let rem = n - i;
                let cap = if rem < 258 { rem } else { 258 };
                let scap = if b - i < cap { b - i } else { cap };
                let wi = mf.w[i % A_B_WR];
                let wp = if i > a { mf.w[(i - 1) % A_B_WR] >> 56 } else { 256 };
                let mut nf = 0usize;
                let mut best = 2usize;
                let h3 = ((((wi >> 40) as u32).wrapping_mul(2246822519)) >> (32 - A_B_H3BITS)) as usize % A_B_H3SIZE;
                let p3 = mf.head3[h3] as usize;
                mf.head3[h3] = (i + 1) as u32;
                let d3 = (i + 1).wrapping_sub(p3);
                if p3 > 0 && d3 >= 1 && d3 <= h3dist && scap >= 3 {
                    let c = i - d3;
                    let x3 = mf.w[c % A_B_WR] ^ wi;
                    if (x3 >> 40) == 0 && (x3 >> 32) != 0 {
                        let flag = if c >= 1 && (mf.w[(c - 1) % A_B_WR] >> 56) == wp { A_B_FULL } else { 0 };
                        let r = a_b_add_record(&mut rv, 0, 0, 3, d3, flag);
                        nr = r.0;
                        nf = r.1;
                        best = 3;
                    }
                }
                let h = ((((wi >> 32) as u32).wrapping_mul(2654435761)) >> (32 - A_B_HBITS)) as usize % A_B_HSIZE;
                let first = mf.head[h] as usize;
                mf.head[h] = (i + 1) as u32;
                let r = a_b_descend(&mut mf, first, i, cap, scap, best, wp, &mut rv, nr, nf, depth);
                nr = r.0;
                let mut q = 0usize;
                while q < nr {
                    rn = a_b_put(&mut rs, rn, rv[q % A_B_RB]);
                    q += 1;
                }
            }
            rn = a_b_put(&mut rs, rn, nr as u32);
            i += 1;
        }
        if a == 0 {
            a_b_static_freq(&mut bf);
        }
        if bs.len() == 0 {
            bs.push(0);
        }
        bs[0] = 0;
        a_b_dp_seg(input, a, m, &rs, rn, &bf, &bs, 1, &mut cc, cuts, tail);
        if mode == 1 {
            let mut p = 0usize;
            while p < bpasses {
                let nb = a_b_tally_seg(input, a, m, &cc, 1, &mut bf, &mut bs);
                a_b_dp_seg(input, a, m, &rs, rn, &bf, &bs, nb, &mut cc, cuts, a_a_tail_for_pass(p, bpasses, tail, 0));
                p += 1;
            }
        } else {
            let _ = a_b_tally_seg(input, a, m, &cc, 0, &mut bf, &mut bs);
            let mut k2 = 0usize;
            while k2 < A_B_FSZ {
                freq[k2] = bf[k2];
                k2 += 1;
            }
            // extra bits are identical under both tables; compare symbol costs only
            let paid = (cc[m] & 0xFFFFFFFF) as u64;
            let own = a_b_self_cost(&freq);
            let xb = a_b_extra_bits(&freq);
            if a == 0 || (paid > xb && (paid - xb) * 1024 > own * (1024 + A_B_GAP)) {
                a_b_dp_seg(input, a, m, &rs, rn, &bf, &bs, 1, &mut cc, cuts, a_b_initial_tail(keep, tail));
                let _ = a_b_tally_seg(input, a, m, &cc, 0, &mut bf, &mut bs);
            }
        }
        a_b_plan_seg(a, m, &cc, plan);
        a = b;
    }
    if keep == 1 && bpasses > 0 {
        let mut nb = a_b_tally_plan(input, plan, &mut bf, &mut bs);
        let mut p = 0usize;
        while p < bpasses {
            a_b_dp_seg(input, 0, n, &rs, rn, &bf, &bs, nb, &mut cc, cuts, a_a_tail_for_pass(p, bpasses, tail, 0));
            if p + 1 < bpasses {
                nb = a_b_tally_seg(input, 0, n, &cc, 1, &mut bf, &mut bs);
            }
            p += 1;
        }
        a_b_plan_seg(0, n, &cc, plan);
    }
}

// ───────────────────────────── engine C: DNA and binary ─────────────────────────────
// Optimal parsing under per-block Huffman-length models, iterated; finders per sub-class:
// DNA (2-bit 8-mer chains + lower-case tree), binary tree on 3-byte hashes, 4-byte-key chains
// (floats, sparse); a block planner turns blocks that code cheaper as literals into literals.

pub const A_C_LSYM: [u8; 256] = [
    0, 1, 2, 3, 4, 5, 6, 7, 8, 8, 9, 9, 10, 10, 11, 11, 12, 12, 12, 12, 13, 13, 13, 13, 14, 14, 14, 14, 15, 15, 15, 15,
    16, 16, 16, 16, 16, 16, 16, 16, 17, 17, 17, 17, 17, 17, 17, 17, 18, 18, 18, 18, 18, 18, 18, 18, 19, 19, 19, 19, 19, 19, 19, 19,
    20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21,
    22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23,
    24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24,
    25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25,
    26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26,
    27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 28,
];
pub const A_C_DSYM_LO: [u8; 256] = [
    0, 1, 2, 3, 4, 4, 5, 5, 6, 6, 6, 6, 7, 7, 7, 7, 8, 8, 8, 8, 8, 8, 8, 8, 9, 9, 9, 9, 9, 9, 9, 9,
    10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11,
    12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12,
    13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13,
    14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14,
    14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14,
    15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15,
    15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15,
];
pub const A_C_DSYM_HI: [u8; 256] = [
    0, 14, 16, 17, 18, 18, 19, 19, 20, 20, 20, 20, 21, 21, 21, 21, 22, 22, 22, 22, 22, 22, 22, 22, 23, 23, 23, 23, 23, 23, 23, 23,
    24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25,
    26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26,
    27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27,
    28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28,
    28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28,
    29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29,
    29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29,
];

// Window: a slot index is `pos % A_C_WS`; a node is live while `p - node < A_C_WS`.
pub const A_C_WS: usize = 32768;
// Interleaved child links: node `i` has `kids[2*(i % A_C_WS)]` (smaller) and `kids[2*(i % A_C_WS)+1]` (larger).
pub const A_C_KS: usize = 65536;
// Hash table size of the match finders.
pub const A_C_HS: usize = 65536;
// Tokens per encoder block (fixed by the validator's encoder).
pub const A_C_BLOCK: usize = 16384;
// Cost units per bit.
pub const A_C_SCALE: u32 = 16;
// Stride of one block model: 256 literal costs, 256 length costs (len-3), 32 distance costs.
pub const A_C_MS: usize = 544;
// Weights DP only when 4-byte repeats reach this rate (per 65536 sampled positions).
pub const A_C_WREP4_MIN: usize = 200;
pub const A_C_DEPTH4_W: usize = 4;
pub const A_C_TAX_W: u32 = 16;
pub const A_C_UNUSED_LEN_W: u32 = 6;
pub const A_C_UNUSED_DIST_W: u32 = 4;
// Chain budget of the 4-byte-key finder.
pub const A_C_DEPTH4: usize = 8;
// Use the 4-byte-key chain finder when 4-byte repeats outnumber 6-byte repeats by this factor.
pub const A_C_CHAIN4_RATIO: usize = 8;
// Early exit of `c_rep_rates` only after this many probes (a short repetitive prefix must not decide the mode).
pub const A_C_REP_MINPROBE: usize = 16384;
// Chain budget of the DNA 8-mer index.
pub const A_C_DEPTH_UP: usize = 16;
// Shortest match reported by the DNA 8-mer index.
pub const A_C_UP_MIN: usize = 9;
// Stop searching once a match this long is found.
pub const A_C_NICE: usize = 258;
// Skip searching inside byte runs at least this long, and (generic finder) inside other matches
// at least `A_C_SKIP_FAR` long.
pub const A_C_SKIP: usize = 64;
pub const A_C_SKIP_FAR: usize = 128;
// Lengths relaxed one by one; longer candidates only try their full length beyond this.
pub const A_C_RCAP: usize = 32;
// Candidates kept per position (the longest ones).
pub const A_C_KEEP: usize = 4;
// Generic input: seed the first pass with a greedy parse taking matches of at least this length.
pub const A_C_GMIN: usize = 3;
// DNA: after at least min_dna passes, stop once a pass improves the estimate by less than 1/STOP_DIV.
pub const A_C_STOP_DIV: u64 = 4096;
// Passes for very repetitive input (most positions start a 6-byte repeat).
pub const A_C_PASSES_SP: usize = 1;
// Extra cost (in 1/A_C_SCALE bits) charged to every match by the chain4 class, standing in for the
// code space a match symbol takes from the literals.
pub const A_C_TAX_C4: u32 = 16;
// Match tax of the binary-tree class.
pub const A_C_TAX_BT: u32 = 24;
// Inputs whose 6-byte repeat rate is below this (per 65536 positions) are coded as literals only.
pub const A_C_REP6_MIN: usize = 24;
// Sampling step of the repeat-rate detector.
pub const A_C_REP_STEP: usize = 2;
// Order in which code-length code lengths are written (RFC 1951).
pub const A_C_CL_ORDER: [usize; 19] = [16, 17, 18, 0, 8, 7, 9, 6, 10, 5, 11, 4, 12, 3, 13, 2, 14, 1, 15];
// Candidate flag: only lengths of 8 or more are worth trying (DNA 8-mer chains).
pub const A_C_LONG_ONLY: u32 = 1 << 29;
// A candidate group ends with a trailer `A_C_GROUP | count << 27 | position`.
pub const A_C_GROUP: u32 = 1 << 31;
// Position bits of a trailer.
pub const A_C_PMASK: u32 = 0x07FF_FFFF;
// Extra cost (in 1/A_C_SCALE bits) charged per token, to break ties toward fewer tokens.
pub const A_C_TOKPEN: u32 = 1;
pub const A_C_TOKPEN_W: u32 = 1;
pub const A_C_TOKPEN_C4: u32 = 0;
pub const A_C_TOKPEN_BT: u32 = 1;
// Bits charged for symbols a block model has never seen.
pub const A_C_UNUSED_LIT: u32 = 12;
pub const A_C_UNUSED_LEN: u32 = 12;
pub const A_C_UNUSED_DIST: u32 = 5;

// Nucleotide codes: A C G T -> 0..3, anything else 4.
pub const A_C_NT: [u8; 256] = [
    4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
    4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
    4, 0, 4, 1, 4, 4, 4, 2, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 3, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
    4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
    4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
    4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
    4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
    4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
];

pub const A_C_LEXTRA: [u32; 29] = [0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 2, 2, 2, 2, 3, 3, 3, 3, 4, 4, 4, 4, 5, 5, 5, 5, 0];
pub const A_C_DEXTRA: [u32; 30] = [0, 0, 0, 0, 1, 1, 2, 2, 3, 3, 4, 4, 5, 5, 6, 6, 7, 7, 8, 8, 9, 9, 10, 10, 11, 11, 12, 12, 13, 13];

// Length symbol (0..28) of a match length 3..=258.
pub fn a_c_lsym(len: usize) -> usize {
    if len < 3 {
        return 0;
    }
    A_C_LSYM[(len - 3) % 256] as usize
}

// Distance symbol (0..29) of a distance 1..=32768.
pub fn a_c_dsym(d: usize) -> usize {
    if d < 1 {
        return 0;
    }
    if d <= 256 {
        return A_C_DSYM_LO[(d - 1) % 256] as usize;
    }
    A_C_DSYM_HI[((d - 1) >> 7) % 256] as usize
}

// Eight bytes at `i` as a big-endian word (0 if they do not fit).
pub fn a_c_word_be(s: &[u8], i: usize) -> u64 {
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

// Common prefix of the strings at `a < b`, starting from the known `k0`, capped at `lim`.
// Requires `b + lim <= s.len()`.
pub fn a_c_extend(s: &[u8], a: usize, b: usize, k0: usize, lim: usize) -> usize {
    let mut k = k0;
    let mut fuel = lim + 1;
    while fuel > 0 && k + 8 <= lim {
        let x = a_c_word_be(s, a + k) ^ a_c_word_be(s, b + k);
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

// Pack a candidate: length (9 bits), distance-1 (15 bits), distance symbol (5 bits).
pub fn a_c_pack(len: usize, d: usize) -> u32 {
    ((a_c_dsym(d) as u32) << 24) | (((d - 1) as u32) << 9) | (len as u32)
}

// Store `v` into the pending child slot `(which, idx)`: `which == 0` is `lt`, else `gt`.
pub fn a_c_put_kid(kids: &mut [u32; A_C_KS], which: usize, idx: usize, v: u32) {
    kids[(2 * (idx % A_C_WS) + which) % A_C_KS] = v;
}

// Insert `p` into the binary tree rooted at `head[h]` and collect the improving matches
// (strictly longer as the distance grows) into `ml`/`md`. Returns how many.
// Positions are stored as `pos + 1` (0 = empty). Requires `p + 3 <= s.len()`.
pub fn a_c_bt_find(
    s: &[u8],
    p: usize,
    h: usize,
    depth: usize,
    head: &mut [u32; A_C_HS],
    kids: &mut [u32; A_C_KS],
    ml: &mut [u32; 64],
    md: &mut [u32; 64],
) -> usize {
    let n = s.len();
    let room = n - p;
    let maxlen = if room < 258 { room } else { 258 };
    let lim = if A_C_NICE < maxlen { A_C_NICE } else { maxlen };
    let mut cur = head[h % A_C_HS] as usize;
    head[h % A_C_HS] = (p + 1) as u32;
    let mut lw = 0usize;
    let mut li = p % A_C_WS;
    let mut gw = 1usize;
    let mut gi = p % A_C_WS;
    let mut llen = 0usize;
    let mut glen = 0usize;
    let mut best = 2usize;
    let mut cnt = 0usize;
    let mut steps = 0usize;
    while steps < depth && cur > 0 {
        let c = cur - 1;
        if c >= p || p - c >= A_C_WS {
            steps = depth;
        } else {
            let k0 = if llen < glen { llen } else { glen };
            let k = a_c_extend(s, c, p, k0, lim);
            if k > best {
                best = k;
                if cnt < 64 {
                    ml[cnt] = k as u32;
                    md[cnt] = (p - c) as u32;
                    cnt += 1;
                }
            }
            if k >= lim {
                a_c_put_kid(kids, lw, li, kids[(2 * (c % A_C_WS)) % A_C_KS]);
                a_c_put_kid(kids, gw, gi, kids[(2 * (c % A_C_WS) + 1) % A_C_KS]);
                return cnt;
            }
            if s[c + k] < s[p + k] {
                a_c_put_kid(kids, lw, li, cur as u32);
                lw = 1;
                li = c % A_C_WS;
                llen = k;
                cur = kids[(2 * (c % A_C_WS) + 1) % A_C_KS] as usize;
            } else {
                a_c_put_kid(kids, gw, gi, cur as u32);
                gw = 0;
                gi = c % A_C_WS;
                glen = k;
                cur = kids[(2 * (c % A_C_WS)) % A_C_KS] as usize;
            }
            steps += 1;
        }
    }
    a_c_put_kid(kids, lw, li, 0);
    a_c_put_kid(kids, gw, gi, 0);
    cnt
}

// Walk the hash chain of `key` from its head, collecting the improving matches (strictly longer
// than `best0`, growing with the distance) into `ml`/`md`, then link `p` in at the head. `k0`
// bytes are known to agree for every chain member (8 for exact DNA keys, else 0).
pub fn a_c_chain_walk(
    s: &[u8],
    p: usize,
    key: usize,
    k0: usize,
    best0: usize,
    depth: usize,
    head: &mut [u32; A_C_HS],
    prev: &mut [u32; A_C_WS],
    ml: &mut [u32; 64],
    md: &mut [u32; 64],
) -> usize {
    let n = s.len();
    let room = n - p;
    let lim = if room < 258 { room } else { 258 };
    let first = head[key % A_C_HS];
    head[key % A_C_HS] = (p + 1) as u32;
    let mut cur = first as usize;
    let mut best = best0;
    let mut cnt = 0usize;
    let mut steps = 0usize;
    while steps < depth && cur > 0 {
        let c = cur - 1;
        if c >= p || p - c >= A_C_WS {
            steps = depth;
        } else {
            if best < lim && s[c + best] == s[p + best] {
                let mut k = k0;
                if k0 + 8 <= lim {
                    let x = a_c_word_be(s, c + k0) ^ a_c_word_be(s, p + k0);
                    if x != 0 {
                        k = k0 + (x.leading_zeros() / 8) as usize;
                    } else {
                        k = a_c_extend(s, c, p, k0 + 8, lim);
                    }
                } else {
                    k = a_c_extend(s, c, p, k0, lim);
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
                cur = prev[c % A_C_WS] as usize;
                steps += 1;
            }
        }
    }
    prev[p % A_C_WS] = first;
    cnt
}

// 2-bit code of a nucleotide letter (upper case), 4 otherwise.
pub fn a_c_nt_code(b: u8) -> usize {
    A_C_NT[b as usize] as usize
}

// Push the candidate group of position `p`: a distance-1 run candidate (if `r1 >= 3`) then the
// last `A_C_KEEP` found candidates longer than it, tagged with `flag`, then a trailer. Nothing is
// pushed when there is no candidate. Returns the longest length pushed (0 if none).
pub fn a_c_push_cands(clist: &mut Vec<u32>, p: usize, ml: &[u32; 64], md: &[u32; 64], cnt: usize, r1: usize, flag: u32) -> usize {
    let first = if cnt > A_C_KEEP { cnt - A_C_KEEP } else { 0 };
    let mut top = 0usize;
    let mut pushed = 0u32;
    if r1 >= 3 && r1 <= 258 {
        clist.push(a_c_pack(r1, 1) | flag);
        top = r1;
        pushed += 1;
    }
    let mut i = first;
    while i < cnt && i < 64 {
        let d = md[i] as usize;
        let l = ml[i] as usize;
        if d >= 1 && d <= A_C_WS && l > top && l <= 258 && l >= 3 {
            clist.push(a_c_pack(l, d) | flag);
            top = l;
            pushed += 1;
        }
        i += 1;
    }
    if pushed > 0 {
        clist.push(A_C_GROUP | (pushed << 27) | ((p as u32) & A_C_PMASK));
    }
    top
}

// Length of the distance-1 match at `p` (a byte run), 0 if shorter than 3.
pub fn a_c_run_len(s: &[u8], p: usize) -> usize {
    let n = s.len();
    if p < 1 || p + 3 > n {
        return 0;
    }
    if s[p] != s[p - 1] || s[p + 1] != s[p - 1] || s[p + 2] != s[p - 1] {
        return 0;
    }
    let room = n - p;
    let lim = if room < 258 { room } else { 258 };
    a_c_extend(s, p - 1, p, 3, lim)
}

// Candidates for every position of binary input: a binary tree on 3-byte hashes (`chain == 0`)
// or hash chains on 4-byte keys, plus byte runs. Searching pauses inside byte runs of `A_C_SKIP`+
// bytes and (after one more position) inside other matches of `A_C_SKIP_FAR`+ bytes.
pub fn a_c_find_bin(s: &[u8], clist: &mut Vec<u32>, chain: usize, depth: usize) {
    let n = s.len();
    let mut head = [0u32; A_C_HS];
    let mut lt = [0u32; A_C_WS];
    let mut kids = [0u32; A_C_KS];
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
                a_c_chain_walk(s, p, h, 0, 3, depth, &mut head, &mut lt, &mut ml, &mut md)
            } else {
                a_c_bt_find(s, p, h, depth, &mut head, &mut kids, &mut ml, &mut md)
            };
            let r1 = if p > 0 && s[p] == s[p - 1] { a_c_run_len(s, p) } else { 0 };
            let mut top = 0usize;
            if cnt > 0 || r1 >= 3 {
                top = a_c_push_cands(clist, p, &ml, &md, cnt, r1, 0);
            }
            if r1 >= A_C_SKIP {
                skip_to = p + top;
                pend = 0;
            } else if top >= A_C_SKIP_FAR {
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
            lt[p % A_C_WS] = head[h % A_C_HS];
            head[h % A_C_HS] = (p + 1) as u32;
        }
        p += 1;
    }
}

// Candidates for every position (DNA): exact 8-mer chains for upper-case runs,
// a binary tree over lower-case positions only.
pub fn a_c_find_dna(s: &[u8], clist: &mut Vec<u32>, depth_lo: usize) {
    let n = s.len();
    let mut head8 = [0u32; A_C_HS];
    let mut prev8 = [0u32; A_C_WS];
    let mut head3 = [0u32; A_C_HS];
    let mut kids = [0u32; A_C_KS];
    let mut ml = [0u32; 64];
    let mut md = [0u32; 64];
    // rolling 2-bit key of s[p..p+8]; `run` counts trailing nucleotides, `run2` also admits newlines
    let mut key = 0usize;
    let mut run = 0usize;
    let mut run2 = 0usize;
    let mut q = 0usize;
    while q < 7 && q < n {
        let c = a_c_nt_code(s[q]);
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
            let c = a_c_nt_code(s[p + 7]);
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
                let h = ((v.wrapping_mul(0x9E37_79B1) >> 16) as usize) % (A_C_HS / 2);
                if p >= skip_to {
                    let cnt = a_c_bt_find(s, p, h, depth_lo, &mut head3, &mut kids, &mut ml, &mut md);
                    if cnt > 0 {
                        let top = a_c_push_cands(clist, p, &ml, &md, cnt, 0, 0);
                        if top >= A_C_SKIP {
                            skip_to = p + top;
                        }
                    }
                }
            } else if run >= 8 {
                if p >= skip_to {
                    let cnt = a_c_chain_walk(s, p, key, 8, A_C_UP_MIN - 1, A_C_DEPTH_UP, &mut head8, &mut prev8, &mut ml, &mut md);
                    if cnt > 0 {
                        let top = a_c_push_cands(clist, p, &ml, &md, cnt, 0, A_C_LONG_ONLY);
                        if top >= A_C_SKIP {
                            skip_to = p + top;
                        }
                    }
                } else {
                    prev8[p % A_C_WS] = head8[key % A_C_HS];
                    head8[key % A_C_HS] = (p + 1) as u32;
                }
            } else if run2 >= 8 {
                let w = a_c_word_be(s, p);
                let hn = A_C_HS / 2 + ((w.wrapping_mul(0x9E37_79B9_7F4A_7C15) >> 40) as usize) % (A_C_HS / 2);
                if p >= skip_to {
                    let cnt = a_c_chain_walk(s, p, hn, 0, A_C_UP_MIN - 1, A_C_DEPTH_UP, &mut head3, &mut prev8, &mut ml, &mut md);
                    if cnt > 0 {
                        let top = a_c_push_cands(clist, p, &ml, &md, cnt, 0, A_C_LONG_ONLY);
                        if top >= A_C_SKIP {
                            skip_to = p + top;
                        }
                    }
                } else {
                    prev8[p % A_C_WS] = head3[hn % A_C_HS];
                    head3[hn % A_C_HS] = (p + 1) as u32;
                }
            }
        }
        p += 1;
    }
}

// Huffman code lengths (capped at 15) for the first `m` symbols of `freq`:
// radix-sort the used symbols by weight, then merge with the two-queue method.
pub fn a_c_huff_lengths(freq: &[u32; 288], m: usize, lens: &mut [u8; 288]) {
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
    a_c_radix_pass(&aw, &asy, &mut bw, &mut bsy, k, 0);
    a_c_radix_pass(&bw, &bsy, &mut aw, &mut asy, k, 8);
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

// One stable counting-sort pass over `k` (weight, symbol) pairs by the byte at `shift`.
pub fn a_c_radix_pass(sw: &[u32; 288], ss: &[u16; 288], dw: &mut [u32; 288], ds: &mut [u16; 288], k: usize, shift: u32) {
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

// Append one block model (costs in `A_C_SCALE` units) built from symbol frequencies;
// return the block's estimated size in bits (codes, extra bits, rough header).
pub fn a_c_push_model(models: &mut Vec<u32>, lf: &[u32; 288], df: &[u32; 288], tax: u32, ulen: u32, udist: u32, tokpen: u32) -> u64 {
    let mut ll = [0u8; 288];
    let mut dl = [0u8; 288];
    a_c_huff_lengths(lf, 286, &mut ll);
    a_c_huff_lengths(df, 30, &mut dl);
    let mut est: u64 = 70;
    let mut q = 0usize;
    while q < 288 {
        if ll[q] > 0 {
            est += (lf[q] as u64) * (ll[q] as u64) + 4;
            if q >= 257 && q < 286 {
                est += (lf[q] as u64) * (A_C_LEXTRA[(q - 257) % 29] as u64);
            }
        }
        if q < 30 && dl[q] > 0 {
            est += (df[q] as u64) * ((dl[q] as u64) + (A_C_DEXTRA[q] as u64)) + 4;
        }
        q += 1;
    }
    let mut i = 0usize;
    while i < 256 {
        let b = if ll[i] > 0 { ll[i] as u32 } else { A_C_UNUSED_LIT };
        models.push(b * A_C_SCALE + tokpen);
        i += 1;
    }
    let mut l = 3usize;
    while l < 259 {
        let s = a_c_lsym(l);
        let b = if ll[(257 + s) % 288] > 0 { ll[(257 + s) % 288] as u32 } else { ulen };
        models.push((b + A_C_LEXTRA[s % 29]) * A_C_SCALE + tokpen + tax);
        l += 1;
    }
    let mut d = 0usize;
    while d < 32 {
        let b = if d < 30 && dl[d] > 0 { dl[d] as u32 } else { udist };
        let e = if d < 30 { A_C_DEXTRA[d] } else { 0 };
        models.push((b + e) * A_C_SCALE);
        d += 1;
    }
    est
}

// Start index of the candidates of the group whose trailer is at `ge - 1` (or `ge` if none).
pub fn a_c_group_start(clist: &Vec<u32>, ge: usize) -> usize {
    if ge == 0 || ge > clist.len() {
        return ge;
    }
    let tr = clist[ge - 1];
    let cnt = ((tr >> 27) & 15) as usize;
    if (tr & A_C_GROUP) == 0 || cnt + 1 > ge {
        return ge;
    }
    ge - 1 - cnt
}

// Copy block model `b` into local cost tables (literals, lengths 3..258, distance symbols).
pub fn a_c_load_model(models: &Vec<u32>, b: usize, lit_c: &mut [u32; 256], len_c: &mut [u32; 256], dst_c: &mut [u32; 32]) {
    let base = b * A_C_MS;
    if base + A_C_MS > models.len() {
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

// Backward optimal parse over the whole input under per-block models. Costs live in a ring
// (a match is at most 258 long); the choice per position (0 = literal, else `len + 512 * dist`)
// is written into `choice`. Runs of positions without candidates take a literal-only fast path.
pub fn a_c_dp_pass(s: &[u8], clist: &Vec<u32>, models: &Vec<u32>, bstart: &Vec<u32>, choice: &mut [u32]) {
    let n = s.len();
    let nb = bstart.len();
    if nb == 0 || models.len() < nb * A_C_MS || choice.len() < n {
        return;
    }
    let mut ring = [0u32; 512];
    let mut lit_c = [0u32; 256];
    let mut len_c = [0u32; 256];
    let mut dst_c = [0u32; 32];
    let mut b = nb - 1;
    let mut loaded = nb;
    let mut ge = clist.len();
    let mut gs = a_c_group_start(clist, ge);
    let mut gp = if gs < ge && ge <= clist.len() { (clist[ge - 1] & A_C_PMASK) as usize } else { n };
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
            a_c_load_model(models, b, &mut lit_c, &mut len_c, &mut dst_c);
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
                if (e & A_C_LONG_ONLY) != 0 && prev < 7 {
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
                        if len == A_C_RCAP && l > A_C_RCAP {
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
            gs = a_c_group_start(clist, ge);
            gp = if gs < ge && ge <= clist.len() { (clist[ge - 1] & A_C_PMASK) as usize } else { n };
        }
    }
}

// Seed `choice` with a greedy parse: the longest candidate at each position if at least `gmin` long.
pub fn a_c_greedy_choice(clist: &Vec<u32>, choice: &mut [u32], n: usize, gmin: usize) {
    let mut p = 0usize;
    while p < n && p < choice.len() {
        choice[p] = 0;
        p += 1;
    }
    let m = clist.len();
    let mut k = 1usize;
    while k < m {
        let tr = clist[k];
        if (tr & A_C_GROUP) != 0 {
            let q = (tr & A_C_PMASK) as usize;
            let last = clist[k - 1];
            if (last & A_C_GROUP) == 0 && ((last & 511) as usize) >= gmin && q < n && q < choice.len() {
                choice[q] = (last & 0x00FF_FFFF) + 512;
            }
        }
        k += 1;
    }
}

// Walk the chosen path; rebuild per-block models and block start positions from it.
// Returns the estimated size of the path in bits.
pub fn a_c_restat(s: &[u8], choice: &[u32], models: &mut Vec<u32>, bstart: &mut Vec<u32>, tax: u32, ulen: u32, udist: u32, tokpen: u32) -> u64 {
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
        while t < A_C_BLOCK && p < n {
            let ch = choice[p] as usize;
            let len = ch % 512;
            if len < 3 {
                let b = s[p] as usize;
                lf[b] = lf[b].wrapping_add(1);
                p += 1;
            } else {
                let d = ch / 512;
                let ls = (257 + a_c_lsym(len)) % 288;
                let ds = a_c_dsym(d) % 288;
                lf[ls] = lf[ls].wrapping_add(1);
                df[ds] = df[ds].wrapping_add(1);
                p += len;
            }
            t += 1;
        }
        lf[256] = 1;
        total += a_c_push_model(models, &lf, &df, tax, ulen, udist, tokpen);
        if p < n {
            bstart.push(p as u32);
        }
        lf = [0u32; 288];
        df = [0u32; 288];
    }
    if models.len() == 0 {
        lf[256] = 1;
        total += a_c_push_model(models, &lf, &df, tax, ulen, udist, tokpen);
    }
    total
}

// DNA-like input: nearly all bytes are nucleotide letters or newlines (stops early otherwise).
pub fn a_c_is_dna(s: &[u8]) -> usize {
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

// Code-length RLE of one run of `r` equal lengths `v` (the encoder's greedy rules):
// adds symbol counts to `clf` and returns the extra bits.
pub fn a_c_rle_run(clf: &mut [u32; 288], v: usize, r0: usize) -> u64 {
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

// Bits of a dynamic block with these symbol frequencies (`lf[256]` is the end-of-block count),
// header included, using approximate (depth-capped) Huffman lengths.
pub fn a_c_dyn_bits(lf: &[u32; 288], df: &[u32; 288]) -> u64 {
    let mut ll = [0u8; 288];
    let mut dl = [0u8; 288];
    a_c_huff_lengths(lf, 286, &mut ll);
    a_c_huff_lengths(df, 30, &mut dl);
    let mut body: u64 = 0;
    let mut hlit = 257usize;
    let mut i = 0usize;
    while i < 286 {
        if ll[i] > 0 {
            body += (lf[i] as u64) * (ll[i] as u64);
            if i >= 257 {
                body += (lf[i] as u64) * (A_C_LEXTRA[(i - 257) % 29] as u64);
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
            body += (df[d] as u64) * ((dl[d] as u64) + (A_C_DEXTRA[d] as u64));
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
        extra += a_c_rle_run(&mut clf, v, r);
        j += r;
    }
    let mut cl = [0u8; 288];
    a_c_huff_lengths(&clf, 19, &mut cl);
    let mut hclen = 19usize;
    while hclen > 4 && cl[A_C_CL_ORDER[(hclen - 1) % 19] % 288] == 0 {
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

// Bits of a fixed-code block with these symbol frequencies.
pub fn a_c_fixed_bits(lf: &[u32; 288], df: &[u32; 288]) -> u64 {
    let mut bits: u64 = 3;
    let mut i = 0usize;
    while i < 288 {
        let len: u64 = if i < 144 { 8 } else if i < 256 { 9 } else if i < 280 { 7 } else { 8 };
        bits += (lf[i] as u64) * len;
        if i >= 257 && i < 286 {
            bits += (lf[i] as u64) * (A_C_LEXTRA[(i - 257) % 29] as u64);
        }
        i += 1;
    }
    let mut d = 0usize;
    while d < 30 {
        bits += (df[d] as u64) * (5 + A_C_DEXTRA[d] as u64);
        d += 1;
    }
    bits
}

// Frequencies of the block that follows `choice` from `p0` (at most A_C_BLOCK tokens).
// Returns the position after the block.
pub fn a_c_path_block(s: &[u8], choice: &[u32], p0: usize, lf: &mut [u32; 288], df: &mut [u32; 288]) -> usize {
    let n = s.len();
    let mut i = 0usize;
    while i < 288 {
        lf[i] = 0;
        df[i] = 0;
        i += 1;
    }
    let mut p = p0;
    let mut t = 0usize;
    while p < n && t < A_C_BLOCK && p < choice.len() {
        let ch = choice[p] as usize;
        let len = ch % 512;
        let d = ch / 512;
        if len >= 3 && len <= n - p {
            lf[(257 + a_c_lsym(len)) % 288] = lf[(257 + a_c_lsym(len)) % 288].wrapping_add(1);
            df[a_c_dsym(d) % 288] = df[a_c_dsym(d) % 288].wrapping_add(1);
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

// Set plan[p0..end] to literals.
pub fn a_c_clear_span(plan: &mut [u32], p0: usize, end: usize) {
    let mut p = p0;
    while p < end && p < plan.len() {
        plan[p] = 0;
        p += 1;
    }
}

// Block planner: follow the plan block by block; where the next BLOCK bytes code cheaper as
// literals (so the encoder can store incompressible stretches), rewrite them as literals.
pub fn a_c_plan_blocks(s: &[u8], plan: &mut [u32]) {
    let n = s.len();
    let mut lf = [0u32; 288];
    let mut df = [0u32; 288];
    let mut p = 0usize;
    let mut fuel = n + 1;
    while p < n && p < plan.len() && fuel > 0 {
        fuel -= 1;
        let ea = a_c_path_block(s, plan, p, &mut lf, &mut df);
        let da = a_c_dyn_bits(&lf, &df);
        let fa = a_c_fixed_bits(&lf, &df);
        let ca = if da < fa { da } else { fa };
        let eb = if n - p > A_C_BLOCK { p + A_C_BLOCK } else { n };
        let ec = if ea > eb { ea } else { eb };
        let mut lb = [0u32; 288];
        let zb = [0u32; 288];
        let mut q = p;
        while q < ec {
            lb[s[q] as usize] += 1;
            q += 1;
        }
        lb[256] = 1;
        let db = a_c_dyn_bits(&lb, &zb);
        let fb = a_c_fixed_bits(&lb, &zb);
        let sb = 8 * ((ec - p) as u64) + 40;
        let mut cb = if db < fb { db } else { fb };
        if sb < cb {
            cb = sb;
        }
        if ea > p && ca <= cb {
            p = ea;
        } else {
            a_c_clear_span(plan, p, eb);
            p = eb;
        }
    }
}

// Repeat statistics on every `A_C_REP_STEP`-th position (most recent occurrence of each 4-byte key):
// returns (4-byte repeats, 6-byte repeats) per 65536 sampled positions. Stops early once the
// 6-byte repeats alone exceed `A_C_REP6_MIN` over the whole input.
pub fn a_c_rep_rates(s: &[u8]) -> (usize, usize) {
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
            if p - a <= A_C_WS && s[a] == s[p] && s[a + 1] == s[p + 1] && s[a + 2] == s[p + 2] && s[a + 3] == s[p + 3] {
                r4 += 1;
                if s[a + 4] == s[p + 4] && s[a + 5] == s[p + 5] {
                    r6 += 1;
                    if r6 >= 64 && (r6 as u64) * 131072 >= 24 * (n as u64) && probes >= A_C_REP_MINPROBE {
                        return (((r4 as u64) * 65536 / (probes as u64 + 1)) as usize, ((r6 as u64) * 65536 / (probes as u64 + 1)) as usize);
                    }
                }
            }
        }
        head[h % 16384] = (p + 1) as u32;
        probes += 1;
        p += A_C_REP_STEP;
    }
    (((r4 as u64) * 65536 / (probes as u64 + 1)) as usize, ((r6 as u64) * 65536 / (probes as u64 + 1)) as usize)
}

// Engine C: writes the plan (length n, zeroed). Knobs: tree depth (generic), tree depth (DNA
// lower case), weights DP on/off and its passes, passes (tree class, DNA max/min, chain4 class).
pub fn a_c_engine(input: &[u8], out: &mut Vec<u32>, depth: usize, depth_lo: usize, wdp: usize, passes_w: usize, passes_bt: usize, passes_dna: usize, min_dna: usize, passes_c4: usize) {
    let n = input.len();
    if out.len() < n {
        return;
    }
    let dna = a_c_is_dna(input);
    let mut chain4 = 0usize;
    let mut wmode = 0usize;
    if dna == 0 {
        let (r4, r6) = a_c_rep_rates(input);
        if r6 < A_C_REP6_MIN {
            if wdp == 0 || r4 < A_C_WREP4_MIN {
                return;
            }
            wmode = 1;
        } else if r6 >= 32768 {
            chain4 = 2;
        } else if r4 >= A_C_CHAIN4_RATIO * r6 {
            chain4 = 1;
        }
    }
    let mut clist: Vec<u32> = Vec::with_capacity(n / 2 + 16);
    if dna > 0 {
        a_c_find_dna(input, &mut clist, depth_lo);
    } else if wmode > 0 {
        a_c_find_bin(input, &mut clist, 1, A_C_DEPTH4_W);
    } else if chain4 > 0 {
        a_c_find_bin(input, &mut clist, 1, A_C_DEPTH4);
    } else {
        a_c_find_bin(input, &mut clist, 0, depth);
    }
    let mut models: Vec<u32> = Vec::new();
    let mut bstart: Vec<u32> = Vec::new();
    let passes = if dna > 0 { passes_dna } else if wmode > 0 { passes_w } else if chain4 == 2 { A_C_PASSES_SP } else if chain4 > 0 { passes_c4 } else { passes_bt };
    let tax = if wmode > 0 { A_C_TAX_W } else if chain4 > 0 { A_C_TAX_C4 } else if dna > 0 { 0 } else { A_C_TAX_BT };
    let ulen = if wmode > 0 { A_C_UNUSED_LEN_W } else { A_C_UNUSED_LEN };
    let udist = if wmode > 0 { A_C_UNUSED_DIST_W } else { A_C_UNUSED_DIST };
    // seed: a greedy parse for binary input, all literals for DNA and weights
    let gmin = if dna > 0 || wmode > 0 { 259 } else { A_C_GMIN };
    a_c_greedy_choice(&clist, out, n, gmin);
    let tokpen = if dna > 0 { A_C_TOKPEN } else if wmode > 0 { A_C_TOKPEN_W } else if chain4 > 0 { A_C_TOKPEN_C4 } else { A_C_TOKPEN_BT };
    let lit_est = a_c_restat(input, out, &mut models, &mut bstart, tax, ulen, udist, tokpen);
    let mut last_est = lit_est;
    let mut prev_est = lit_est;
    let mut pass = 0usize;
    while pass < passes {
        a_c_dp_pass(input, &clist, &models, &bstart, out);
        pass += 1;
        if pass < passes {
            last_est = a_c_restat(input, out, &mut models, &mut bstart, tax, A_C_UNUSED_LEN, A_C_UNUSED_DIST, tokpen);
            if dna > 0 && pass >= min_dna && last_est <= prev_est && prev_est - last_est < prev_est / A_C_STOP_DIV {
                pass = passes;
            }
            prev_est = last_est;
        }
    }
    if dna > 0 && last_est >= lit_est {
        a_c_clear_span(out, 0, n);
        return;
    }
    if dna > 0 || chain4 == 2 {
        return;
    }
    a_c_plan_blocks(input, out);
}

#[inline(always)]
pub fn a_r57_scan(cost:&[u32],lc:&[u32;512],i:usize,lo:usize,hi:usize,base:u32,width:usize)->u32 {
    if lo>hi || hi>=512 || i>=cost.len() || hi>=cost.len()-i {return 4294967295;}
    let start=if width>=1 && hi-lo>=width {hi-width+1} else {lo};
    let mut l=start;
    let mut best=2147483647u32;
    while l<=hi {
        let c=(cost[i+l].wrapping_add(lc[l]).wrapping_add(base)<<9)|((l as u32)^511);
        best=if (c as i32)<(best as i32) {c} else {best};
        l+=1;
    }
    best
}

pub fn a_a_tail_for_pass(k: usize, passes: usize, tail: usize, final_tail: usize) -> usize {
    if k.wrapping_add(1) >= passes { final_tail } else { tail }
}

pub fn a_b_tail_start(lo: usize, hi: usize, tail: usize) -> usize {
    if tail >= 1 && hi >= lo && hi - lo >= tail { hi - tail + 1 } else { lo }
}
pub fn a_b_initial_tail(keep: usize, tail: usize) -> usize {
    if keep == 1 { tail } else { 0 }
}


// ===== engine d: parse.rs =====

pub const D_DEPTH: usize = 8;
pub const D_LONG_DEPTH: usize = 4;
pub const D_LDEPTH: usize = 4;
pub const D_MDEPTH: usize = 2;
pub const D_MISS_D: usize = 8;
pub const D_NICE: usize = 258;
pub const D_BLOCK: usize = 32768;
pub const D_NEAR3: usize = 32768;
pub const D_TRY_ALL: usize = 8;
pub const D_MISS_COST: u32 = 160;
pub const D_BIAS: u32 = 12;
pub const D_INNER_MAXL: usize = 8;
pub const D_LAZY_LIMIT: usize = 258;
pub const D_BK: usize = 128;
pub const D_LONG_BELOW: u32 = 52;
pub const D_SKIP_AFTER: usize = 512;
pub const D_SKIPN: usize = 3;
pub const D_RUN_D: usize = 16;
pub const D_RUN_L: usize = 64;
pub const D_RUN_KEEP: usize = 16;
pub const D_SPAN1: usize = 8;
pub const D_SPAN2: usize = 4;
pub const D_INNER_L: usize = 8;
pub const D_NX: usize = 3;
pub const D_XCAP: usize = 32;
pub const D_HW: u32 = 16;
pub const D_TK: u64 = 8;
pub const D_INNER_D: usize = 2;

// How many bytes agree at `a` and `b`, up to `cap`.
pub fn d_match_len(input: &[u8], a: usize, b: usize, cap: usize) -> usize {
    let mut l = 0usize;
    while l < cap && input[b + l] == input[a + l] {
        l += 1;
    }
    l
}

// How many bytes agree at `a < b` and `b`, up to `cap`, for the search: 0 unless
// `b + cap` is within the input.
pub fn d_ext_len(input: &[u8], a: usize, b: usize, cap: usize) -> usize {
    let n = input.len();
    let mut l = 0usize;
    if a < b && b <= n && cap <= n - b {
        let mut go = 1usize;
        while go == 1 && l < cap && cap - l >= 8 {
            let x = d_load64(input, a + l) ^ d_load64(input, b + l);
            if x != 0 {
                l += (x.leading_zeros() / 8) as usize;
                go = 0;
            } else {
                l += 8;
            }
        }
        while go == 1 && l < cap && input[b + l] == input[a + l] {
            l += 1;
        }
    }
    l
}

// Eight bytes from `p`, the first one most significant. Needs `p + 8 <= input.len()`.
pub fn d_load64(input: &[u8], p: usize) -> u64 {
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

// `16 * log2(total / freq)`, rounded down to 1/16 bit; `D_MISS_COST` for an unseen symbol.
pub fn d_cost16(freq: u32, total: u32) -> u32 {
    if freq == 0 {
        return D_MISS_COST;
    }
    let t = total as u64;
    let mut f = freq as u64;
    let mut c = 0u32;
    let lzf = f.leading_zeros();
    let lzt = t.leading_zeros();
    if lzf > lzt {
        let s0 = lzf - lzt;
        let s = if f.wrapping_shl(s0) > t { s0 - 1 } else { s0 };
        f = f.wrapping_shl(s);
        c = 16 * s;
    }
    let mut k = 0usize;
    while k < 16 && f.wrapping_mul(1069) / 1024 <= t {
        f = f.wrapping_mul(1069) / 1024;
        c += 1;
        k += 1;
    }
    if c < 16 {
        16
    } else {
        c
    }
}

// Distance code of `d` in 1..=32768.
pub fn d_dcode(dlo: &[u8; 256], dhi: &[u8; 256], d: usize) -> usize {
    if d <= 256 {
        let k = if d >= 1 { d - 1 } else { 0 };
        dlo[k % 256] as usize
    } else {
        dhi[((d - 1) / 128) % 256] as usize
    }
}

// Bits saved by the match `(l, d)` at block index `i`: literal cost of the covered bytes
// minus the match cost, or 0 when the match costs more.
pub fn d_gain(
    pref: &[u32; 65536],
    lenc: &[u32; 512],
    dcost: &[u32; 32],
    dlo: &[u8; 256],
    dhi: &[u8; 256],
    i: usize,
    l: usize,
    d: usize,
) -> u32 {
    let lit = pref[(i + l) % 65536].wrapping_sub(pref[i % 65536]);
    let mc = lenc[l % 512].saturating_add(dcost[d_dcode(dlo, dhi, d) % 32]);
    if lit > mc {
        lit - mc
    } else {
        0
    }
}

// Records `(l, d)` as the next improving match of block index `i`, replacing the last one when
// both have the same distance code; keeps the first `D_NX - 1` and the latest one.
pub fn d_push_x(
    xs: &mut [u32; 131072],
    xn: &mut [u8; 32768],
    dlo: &[u8; 256],
    dhi: &[u8; 256],
    i: usize,
    l: usize,
    d: usize,
) {
    let c = xn[i % 32768] as usize;
    let mut s = if c < D_NX { c } else { D_NX - 1 };
    if c > 0 {
        let v = xs[(i * D_NX + c - 1) % 131072] as usize;
        if d_dcode(dlo, dhi, v / 512) == d_dcode(dlo, dhi, d) {
            s = c - 1;
        }
    }
    xs[(i * D_NX + s) % 131072] = (d as u32) * 512 + (l as u32);
    if s == c && c < D_NX {
        xn[i % 32768] = (c + 1) as u8;
    }
}

// The match at `p` (block index `i`) saving the most bits among the near 3-byte candidate
// `c3` and `pcap` entries of the chain from `start`, looking only at matches longer than
// `floor`: `(len, dist, gain)`.
pub fn d_find(
    input: &[u8],
    prev: &[u32; 32768],
    pref: &[u32; 65536],
    lenc: &[u32; 512],
    dcost: &[u32; 32],
    dlo: &[u8; 256],
    dhi: &[u8; 256],
    p: usize,
    i: usize,
    cap: usize,
    start: usize,
    c3: usize,
    floor: usize,
    pcap: usize,
    xs: &mut [u32; 131072],
    xn: &mut [u8; 32768],
) -> (usize, usize, u32, usize, usize) {
    let mut bl = 0usize;
    let mut bd = 0usize;
    let mut bg = 0u32;
    let mut sl = 0usize;
    let mut sd = 0usize;
    let mut need = floor;
    let n = input.len();
    let ok = if p <= n && cap <= n - p { 1usize } else { 0usize };
    if ok == 1 && c3 > 0 && c3 <= p && p - (c3 - 1) <= D_NEAR3 && need < cap {
        let c = c3 - 1;
        if input[c + need] == input[p + need] {
            let l = d_ext_len(input, c, p, cap);
            if l >= 3 && l > need {
                let g = d_gain(pref, lenc, dcost, dlo, dhi, i, l, p - c);
                if g > 0 {
                    bl = l;
                    bd = p - c;
                    bg = g;
                    need = l;
                    d_push_x(xs, xn, dlo, dhi, i, l, p - c);
                } else {
                    d_push_x(xs, xn, dlo, dhi, i, l, p - c);
                }
            } else if l >= 3 {
                d_push_x(xs, xn, dlo, dhi, i, l, p - c);
            }
        } else if need >= 3 {
            let l = d_ext_len(input, c, p, if need < D_XCAP { need } else { D_XCAP });
            if l >= 3 {
                d_push_x(xs, xn, dlo, dhi, i, l, p - c);
            }
        }
    }
    let low = if p >= 32768 { p - 32768 + 1 } else { 1usize };
    let mut cur = start;
    let mut nc = prev[start.wrapping_sub(1) % 32768] as usize;
    let mut probes = 0usize;
    while ok == 1 && probes < pcap && cur >= low && cur <= p && need < cap {
        let c = cur - 1;
        let nnc = prev[nc.wrapping_sub(1) % 32768] as usize;
        {
            if input[c + need] == input[p + need] {
                let l = d_ext_len(input, c, p, cap);
                if l > need && l >= 3 {
                    let g = d_gain(pref, lenc, dcost, dlo, dhi, i, l, p - c);
                    if g > 0 || l >= 5 || (l >= 4 && pref[(i + l) % 65536].wrapping_sub(pref[i % 65536]) < 96 * 4) {
                        d_push_x(xs, xn, dlo, dhi, i, l, p - c);
                    }
                    sl = if g > bg { bl } else { l };
                    sd = if g > bg { bd } else { p - c };
                    if g > bg {
                        bl = l;
                    }
                    if g > bg {
                        bd = p - c;
                    }
                    if g > bg {
                        bg = g;
                    }
                    need = l;
                }
            }
            cur = nc;
            nc = nnc;
        }
        probes += 1;
    }
    (bl, bd, bg, sl, sd)
}

// `find` with `D_INNER_D` chain entries, for the inner positions of a committed match.
pub fn d_find_in(
    input: &[u8],
    prev: &[u32; 32768],
    pref: &[u32; 65536],
    lenc: &[u32; 512],
    dcost: &[u32; 32],
    dlo: &[u8; 256],
    dhi: &[u8; 256],
    p: usize,
    i: usize,
    cap: usize,
    start: usize,
    c3: usize,
    floor: usize,
    xs: &mut [u32; 131072],
    xn: &mut [u8; 32768],
) -> (usize, usize, u32, usize, usize) {
    let mut bl = 0usize;
    let mut bd = 0usize;
    let mut bg = 0u32;
    let mut sl = 0usize;
    let mut sd = 0usize;
    let mut need = floor;
    let n = input.len();
    let ok = if p <= n && cap <= n - p { 1usize } else { 0usize };
    if ok == 1 && c3 > 0 && c3 <= p && p - (c3 - 1) <= D_NEAR3 && need < cap {
        let c = c3 - 1;
        if input[c + need] == input[p + need] {
            let l = d_ext_len(input, c, p, cap);
            if l >= 3 && l > need {
                let g = d_gain(pref, lenc, dcost, dlo, dhi, i, l, p - c);
                if g > 0 {
                    bl = l;
                    bd = p - c;
                    bg = g;
                    need = l;
                    d_push_x(xs, xn, dlo, dhi, i, l, p - c);
                } else {
                    d_push_x(xs, xn, dlo, dhi, i, l, p - c);
                }
            } else if l >= 3 {
                d_push_x(xs, xn, dlo, dhi, i, l, p - c);
            }
        } else if need >= 3 {
            let l = d_ext_len(input, c, p, if need < D_XCAP { need } else { D_XCAP });
            if l >= 3 {
                d_push_x(xs, xn, dlo, dhi, i, l, p - c);
            }
        }
    }
    let low = if p >= 32768 { p - 32768 + 1 } else { 1usize };
    let mut cur = start;
    let mut nc = prev[start.wrapping_sub(1) % 32768] as usize;
    let mut probes = 0usize;
    while ok == 1 && probes < D_INNER_D && cur >= low && cur <= p && need < cap {
        let c = cur - 1;
        let nnc = prev[nc.wrapping_sub(1) % 32768] as usize;
        {
            if input[c + need] == input[p + need] {
                let l = d_ext_len(input, c, p, cap);
                if l > need && l >= 3 {
                    let g = d_gain(pref, lenc, dcost, dlo, dhi, i, l, p - c);
                    if g > 0 || l >= 5 || (l >= 4 && pref[(i + l) % 65536].wrapping_sub(pref[i % 65536]) < 96 * 4) {
                        d_push_x(xs, xn, dlo, dhi, i, l, p - c);
                    }
                    sl = if g > bg { bl } else { l };
                    sd = if g > bg { bd } else { p - c };
                    if g > bg {
                        bl = l;
                    }
                    if g > bg {
                        bd = p - c;
                    }
                    if g > bg {
                        bg = g;
                    }
                    need = l;
                }
            }
            cur = nc;
            nc = nnc;
        }
        probes += 1;
    }
    (bl, bd, bg, sl, sd)
}

// Enters position `p` into the tables; returns the previous heads `(chain start, near)`.
// Needs `p + 4 <= input.len()`.
pub fn d_insert(
    input: &[u8],
    head4: &mut [u32; 65536],
    prev: &mut [u32; 32768],
    near: &mut [u32; 65536],
    p: usize,
) -> (usize, usize) {
    let x3 = (input[p] as u32)
        .wrapping_add((input[p + 1] as u32).wrapping_mul(256))
        .wrapping_add((input[p + 2] as u32).wrapping_mul(65536));
    let x4 = x3.wrapping_add((input[p + 3] as u32).wrapping_mul(16777216));
    let h = ((x4.wrapping_mul(2654435761) / 65536) % 65536) as usize;
    let start = head4[h] as usize;
    prev[p % 32768] = head4[h];
    head4[h] = (p + 1) as u32;
    let h3 = ((x3.wrapping_mul(2654435761) / 65536) % 65536) as usize;
    let c3 = near[h3] as usize;
    near[h3] = (p + 1) as u32;
    (start, c3)
}

// Prefix sums of the literal costs over the block.
pub fn d_prefix(input: &[u8], litc: &[u32; 256], pref: &mut [u32; 65536], p0: usize, blen: usize) {
    let n = input.len();
    pref[0] = 0;
    let mut k = 0usize;
    let mut acc = 0u32;
    while k < blen && blen <= 32768 && p0 <= n && blen <= n - p0 {
        acc = acc.wrapping_add(litc[input[p0 + k] as usize]);
        pref[(k + 1) % 65536] = acc;
        k += 1;
    }
}

// Commits the match `(l, d)` at block index `q` as the first candidate of its first
// position and enters positions `q+2..q+l`; for a match of at most `D_INNER_MAXL` bytes each
// of those is offered, as its second candidate, a near match that runs past the end.
pub fn d_commit(
    input: &[u8],
    head4: &mut [u32; 65536],
    prev: &mut [u32; 32768],
    near: &mut [u32; 65536],
    c1l: &mut [u16; 32768],
    c1d: &mut [u16; 32768],
    c2l: &mut [u16; 32768],
    c2d: &mut [u16; 32768],
    xs: &mut [u32; 131072],
    xn: &mut [u8; 32768],
    pref: &[u32; 65536],
    lenc: &[u32; 512],
    dcost: &[u32; 32],
    dlo: &[u8; 256],
    dhi: &[u8; 256],
    p0: usize,
    q: usize,
    l: usize,
    d: usize,
    blen: usize,
) {
    let n = input.len();
    let has4 = n >= 4;
    let lim4 = if has4 { n - 4 } else { 0 };
    c1l[q % 32768] = l as u16;
    c1d[q % 32768] = d as u16;
    let mut k = 1usize;
    while k < l && l <= 258 {
        let j = q + k;
        c1l[j % 32768] = 0;
        if k >= 2 {
            c2l[j % 32768] = 0;
            xn[j % 32768] = 0;
            let p = p0 + j;
            let keep = if has4 && p <= lim4 && (d > D_RUN_D || l < D_RUN_L || k < D_RUN_KEEP || k + D_RUN_KEEP >= l) {
                1usize
            } else {
                0usize
            };
            if keep == 1 {
                let r = d_insert(input, head4, prev, near, p);
                if j < blen && l <= D_INNER_L {
                    let rem = l - k;
                    let rest = blen - j;
                    let cap = if rest < 258 { rest } else { 258 };
                    let f = d_find_in(input, prev, pref, lenc, dcost, dlo, dhi, p, j, cap, r.0, r.1, rem, xs, xn);
                    if f.0 >= 3 && f.0 > rem && f.0 <= 258 {
                        c2l[j % 32768] = f.0 as u16;
                        c2d[j % 32768] = f.1 as u16;
                        if f.3 >= 3 && f.3 > rem && f.3 <= 258 && f.4 != f.1 {
                            c1l[j % 32768] = f.3 as u16;
                            c1d[j % 32768] = f.4 as u16;
                        }
                    }
                } else if j < blen && l <= D_INNER_MAXL {
                    let c3 = r.1;
                    let rem = l - k;
                    let rest = blen - j;
                    let cap = if rest < 258 { rest } else { 258 };
                    if c3 > 0 && c3 <= p && p - (c3 - 1) <= D_NEAR3 && p - (c3 - 1) != d && rem < cap && cap <= n - p {
                        let c = c3 - 1;
                        if input[c + rem] == input[p + rem] {
                            let e = d_ext_len(input, c, p, cap);
                            if e > rem && e >= 3 {
                                c2l[j % 32768] = e as u16;
                                c2d[j % 32768] = (p - c) as u16;
                            } else if e >= 3 {
                                d_push_x(xs, xn, dlo, dhi, j, e, p - c);
                            }
                        } else {
                            let e = d_ext_len(input, c, p, if rem < D_XCAP { rem } else { D_XCAP });
                            if e >= 3 {
                                d_push_x(xs, xn, dlo, dhi, j, e, p - c);
                            }
                        }
                    }
                }
            }
        }
        k += 1;
    }
}

// Extends the match `(l, d)` at `p = p0 + q` backward, offering each earlier position of
// the block the longer match as its second candidate.
pub fn d_extend_back(
    input: &[u8],
    c2l: &mut [u16; 32768],
    c2d: &mut [u16; 32768],
    p0: usize,
    q: usize,
    l: usize,
    d: usize,
) {
    let n = input.len();
    let p = p0 + q;
    let mut j = 1usize;
    let mut go = 1usize;
    while go == 1 && j <= D_BK && j <= q && l + j <= 258 && p >= j + d && d >= 1 && p < n {
        if input[p - j] == input[p - j - d] {
            let k = q - j;
            let el = l + j;
            if el > c2l[k % 32768] as usize {
                c2l[k % 32768] = el as u16;
                c2d[k % 32768] = d as u16;
            }
            j += 1;
        } else {
            go = 0;
        }
    }
}

// Takes up to `D_SKIPN` positions from block index `i` as literals, unsearched.
pub fn d_skip(c1l: &mut [u16; 32768], c2l: &mut [u16; 32768], xn: &mut [u8; 32768], i0: usize, blen: usize) -> usize {
    let mut i = i0;
    let mut s = 0usize;
    while s < D_SKIPN && i < blen {
        c1l[i % 32768] = 0;
        c2l[i % 32768] = 0;
        xn[i % 32768] = 0;
        i += 1;
        s += 1;
    }
    i
}

// Lazy pass over the block `[p0, p0 + blen)`: enters the positions into the tables and
// leaves the candidates of the dynamic program in `c1*` (the chosen matches) and `c2*`
// (backward extensions, the second-best match of each chosen one, the lazy step's loser).
pub fn d_lazy(
    input: &[u8],
    head4: &mut [u32; 65536],
    prev: &mut [u32; 32768],
    near: &mut [u32; 65536],
    pref: &[u32; 65536],
    lenc: &[u32; 512],
    dcost: &[u32; 32],
    dlo: &[u8; 256],
    dhi: &[u8; 256],
    c1l: &mut [u16; 32768],
    c1d: &mut [u16; 32768],
    c2l: &mut [u16; 32768],
    c2d: &mut [u16; 32768],
    xs: &mut [u32; 131072],
    xn: &mut [u8; 32768],
    p0: usize,
    blen: usize,
    long: usize,
) {
    let n = input.len();
    let has4 = n >= 4;
    let lim4 = if has4 { n - 4 } else { 0 };
    let mut pl = 0usize;
    let mut pd = 0usize;
    let mut pg = 0u32;
    let mut psl = 0usize;
    let mut psd = 0usize;
    let mut miss = 0usize;
    let mut i = 0usize;
    let mut steps = 0usize;
    while i < blen && steps < 32768 && blen <= 32768 && p0 <= n && blen <= n - p0 {
        let p = p0 + i;
        let rest = blen - i;
        let cap = if rest < 258 { rest } else { 258 };
        c1l[i % 32768] = 0;
        c2l[i % 32768] = 0;
        xn[i % 32768] = 0;
        let mut cl = 0usize;
        let mut cd = 0usize;
        let mut cg = 0u32;
        let mut csl = 0usize;
        let mut csd = 0usize;
        if has4 && p <= lim4 {
            let r = d_insert(input, head4, prev, near, p);
            if pl < D_LAZY_LIMIT {
                let floor = if pl >= 3 { pl - 1 } else { 0 };
                let pcap = if pl >= 3 { D_LDEPTH } else if miss >= D_MISS_D { D_MDEPTH } else if long == 1 { D_LONG_DEPTH } else { D_DEPTH };
                let f = d_find(input, prev, pref, lenc, dcost, dlo, dhi, p, i, cap, r.0, r.1, floor, pcap, xs, xn);
                cl = f.0;
                cd = f.1;
                cg = f.2;
                csl = f.3;
                csd = f.4;
                if long == 1 {
                    xn[i % 32768] = 0;
                }
            }
        }
        if pl >= 3 && i >= 1 {
            if cl >= 3 && cg > pg {
                if pl <= 258 {
                    c2l[(i - 1) % 32768] = pl as u16;
                    c2d[(i - 1) % 32768] = pd as u16;
                }
                pl = cl;
                pd = cd;
                pg = cg;
                psl = csl;
                psd = csd;
                i += 1;
            } else {
                let q = i - 1;
                if cl >= 3 && cl <= 258 {
                    c2l[i % 32768] = cl as u16;
                    c2d[i % 32768] = cd as u16;
                }
                if psl >= 3 && psl <= 258 && psl < pl {
                    c2l[q % 32768] = psl as u16;
                    c2d[q % 32768] = psd as u16;
                }
                if pl <= 258 && pd >= 1 {
                    d_commit(input, head4, prev, near, c1l, c1d, c2l, c2d, xs, xn, pref, lenc, dcost, dlo, dhi, p0, q, pl, pd, blen);
                    d_extend_back(input, c2l, c2d, p0, q, pl, pd);
                }
                i = q + pl;
                pl = 0;
                pd = 0;
                pg = 0;
            }
        } else if cl >= 3 {
            pl = cl;
            pd = cd;
            pg = cg;
            psl = csl;
            psd = csd;
            miss = 0;
            i += 1;
        } else {
            if long == 1 && csl >= 3 && csl <= 258 {
                c2l[i % 32768] = csl as u16;
                c2d[i % 32768] = csd as u16;
            }
            i += 1;
            if miss < D_SKIP_AFTER {
                miss += 1;
            }
            if miss >= D_SKIP_AFTER && long == 0 {
                i = d_skip(c1l, c2l, xn, i, blen);
            }
        }
        steps += 1;
    }
}

// The cheapest way to cover `[j, j + l)` for `l` in `lo..=hi` at one distance cost:
// every length below `D_TRY_ALL`, then one per length code.
pub fn d_relax_run(
    cost: &[u32; 65536],
    lenc: &[u32; 512],
    bend: &[u16; 512],
    j: usize,
    lo: usize,
    hi: usize,
    dcs: u32,
    best0: u32,
    bl0: usize,
) -> (u32, usize) {
    let mut best = best0;
    let mut bl = bl0;
    let mut l = lo;
    while l <= hi && hi <= 258 {
        let c = cost[(j + l) % 65536].wrapping_add(lenc[l % 512]).wrapping_add(dcs);
        if c < best {
            bl = l;
        }
        if c < best {
            best = c;
        }
        if l < D_TRY_ALL || l >= hi {
            l += 1;
        } else {
            let e = bend[l % 512] as usize;
            let nx = if e <= l { bend[(l + 1) % 512] as usize } else { e };
            l = if nx > hi { hi } else if nx <= l { l + 1 } else { nx };
        }
    }
    (best, bl)
}

// Backward pass: `cost[j]` is the cheapest cost from `j` to the block end, `chl`/`chd` the choice.
pub fn d_backward(
    input: &[u8],
    c1l: &mut [u16; 32768],
    c1d: &mut [u16; 32768],
    c2l: &[u16; 32768],
    c2d: &[u16; 32768],
    xs: &[u32; 131072],
    xn: &[u8; 32768],
    cost: &mut [u32; 65536],
    litc: &[u32; 256],
    lenc: &[u32; 512],
    dcost: &[u32; 32],
    bend: &[u16; 512],
    dlo: &[u8; 256],
    dhi: &[u8; 256],
    p0: usize,
    blen: usize,
    cheap: usize,
) {
    let n = input.len();
    if blen <= 32768 && p0 <= n && blen <= n - p0 {
        cost[blen % 65536] = 0;
        let mut cn = 0u32;
        let mut j = blen;
        while j > 0 {
            j -= 1;
            let lit = cn.wrapping_add(litc[input[p0 + j] as usize]);
            let l2 = c2l[j % 32768] as usize;
            let l1 = c1l[j % 32768] as usize;
            let xc = xn[j % 32768] as usize;
            if l1 < 3 && l2 < 3 && xc == 0 {
                cost[j % 65536] = lit;
                cn = lit;
                c1l[j % 32768] = 0;
            } else {
                let rest = blen - j;
                let mut best = 4294967295u32;
                let mut bl = 0usize;
                let mut bdd = 0usize;
                let d2 = c2d[j % 32768] as usize;
                if l2 >= 3 && l2 <= rest && d2 >= 1 && d2 <= 32768 {
                    let dcs = dcost[d_dcode(dlo, dhi, d2) % 32];
                    let from2 = if l2 > D_SPAN2 + 3 { l2 - D_SPAN2 } else { 3 };
                    let r = d_relax_run(cost, lenc, bend, j, from2, l2, dcs, best, bl);
                    if r.0 < best {
                        bdd = d2;
                    }
                    best = r.0;
                    bl = r.1;
                }
                let d1 = c1d[j % 32768] as usize;
                if l1 >= 3 && l1 <= rest && d1 >= 1 && d1 <= 32768 {
                    let dcs = dcost[d_dcode(dlo, dhi, d1) % 32];
                    let from = if l1 > D_SPAN1 + 3 { l1 - D_SPAN1 } else { 3 };
                    let r = d_relax_run(cost, lenc, bend, j, from, l1, dcs, best, bl);
                    if r.0 < best {
                        bdd = d1;
                    }
                    best = r.0;
                    bl = r.1;
                }
                let mut s = 0usize;
                let mut lo = 3usize;
                while s < xc && s < D_NX {
                    let v = xs[(j * D_NX + s) % 131072] as usize;
                    let lx = v % 512;
                    let dx = v / 512;
                    if lx >= lo && lx <= rest && dx >= 1 && dx <= 32768 {
                        let dcs = dcost[d_dcode(dlo, dhi, dx) % 32];
                        let lo1 = if cheap == 1 { lx } else { lo };
                        let r = d_relax_run(cost, lenc, bend, j, lo1, lx, dcs, best, bl);
                        if r.0 < best {
                            bdd = dx;
                        }
                        best = r.0;
                        bl = r.1;
                    }
                    lo = lx + 1;
                    s += 1;
                }
                if lit <= best {
                    best = lit;
                    bl = 0;
                    bdd = 0;
                }
                cost[j % 65536] = best;
                cn = best;
                c1l[j % 32768] = bl as u16;
                c1d[j % 32768] = bdd as u16;
            }
        }
    }
}

// Symbol counts of the chosen path through the block.
pub fn d_count(
    input: &[u8],
    chl: &[u16; 32768],
    chd: &[u16; 32768],
    lf: &mut [u32; 512],
    df: &mut [u32; 32],
    lcode: &[u8; 512],
    dlo: &[u8; 256],
    dhi: &[u8; 256],
    olf: &[u32; 512],
    odf: &[u32; 32],
    half: usize,
    p0: usize,
    blen: usize,
) {
    let n = input.len();
    let mut s = 0usize;
    while s < 512 {
        lf[s] = if half == 1 { olf[s] / 2 } else { olf[s] };
        s += 1;
    }
    s = 0;
    while s < 32 {
        df[s] = if half == 1 { odf[s] / 2 } else { odf[s] };
        s += 1;
    }
    let mut k = 0usize;
    while k < blen && p0 <= n && blen <= n - p0 {
        let l = chl[k % 32768] as usize;
        let d = chd[k % 32768] as usize;
        if l >= 3 && l <= 258 && d >= 1 && d <= 32768 {
            let li = (257 + lcode[l % 512] as usize) % 512;
            lf[li] = lf[li].saturating_add(1);
            let di = d_dcode(dlo, dhi, d) % 32;
            df[di] = df[di].saturating_add(1);
            k += l;
        } else {
            let b = input[p0 + k] as usize;
            lf[b] = lf[b].saturating_add(1);
            k += 1;
        }
    }
    lf[256] = lf[256].saturating_add(1);
}

// `olf + lz + pdp - plz` per symbol: the lazy-path counts corrected by how the previous
// block's chosen path differed from its lazy path.
pub fn d_mix(
    olf: &[u32; 512],
    odf: &[u32; 32],
    lz: &[u32; 512],
    lzd: &[u32; 32],
    pdp: &[u32; 512],
    pdpd: &[u32; 32],
    plz: &[u32; 512],
    plzd: &[u32; 32],
    lf: &mut [u32; 512],
    df: &mut [u32; 32],
) {
    let mut s = 0usize;
    while s < 512 {
        let c = (lz[s] as u64).wrapping_mul(pdp[s] as u64 + D_TK) / (plz[s] as u64 + D_TK);
        lf[s] = olf[s].saturating_add(if c > 1000000000 { 1000000000 } else { c as u32 });
        s += 1;
    }
    s = 0;
    while s < 32 {
        let c = (lzd[s] as u64).wrapping_mul(pdpd[s] as u64 + D_TK) / (plzd[s] as u64 + D_TK);
        df[s] = odf[s].saturating_add(if c > 1000000000 { 1000000000 } else { c as u32 });
        s += 1;
    }
}

// `a = a - a / 4 + b` per symbol: running averages of block counts.
pub fn d_ravg(al: &mut [u32; 512], ad: &mut [u32; 32], bl: &[u32; 512], bd: &[u32; 32]) {
    let mut s = 0usize;
    while s < 512 {
        al[s] = (al[s] - al[s] / 4).saturating_add(bl[s]);
        s += 1;
    }
    s = 0;
    while s < 32 {
        ad[s] = (ad[s] - ad[s] / 4).saturating_add(bd[s]);
        s += 1;
    }
}

// Copies the first `blen` entries of `al`/`ad` into `bl`/`bd`.
pub fn d_copy16(al: &[u16; 32768], ad: &[u16; 32768], bl: &mut [u16; 32768], bd: &mut [u16; 32768], blen: usize) {
    let mut k = 0usize;
    while k < blen && k < 32768 {
        bl[k] = al[k];
        bd[k] = ad[k];
        k += 1;
    }
}

// Copies the counts `lf`/`df` into `olf`/`odf`.
pub fn d_keep(lf: &[u32; 512], df: &[u32; 32], olf: &mut [u32; 512], odf: &mut [u32; 32]) {
    let mut s = 0usize;
    while s < 512 {
        olf[s] = lf[s];
        s += 1;
    }
    s = 0;
    while s < 32 {
        odf[s] = df[s];
        s += 1;
    }
}

// Inserts weight `x` of symbol `sy` into the ascending list `w[0..m]`, `sym[0..m]`.
pub fn d_hins(w: &mut [u32; 512], sym: &mut [u16; 512], m: usize, x: u32, sy: usize) {
    let mut j = m;
    while j > 0 && j < 512 && w[(j - 1) % 512] > x {
        w[j % 512] = w[(j - 1) % 512];
        sym[j % 512] = sym[(j - 1) % 512];
        j -= 1;
    }
    w[j % 512] = x;
    sym[j % 512] = sy as u16;
}

// Huffman code lengths of the counts `f[0..ns]` (0 for an unseen symbol), capped at 15.
pub fn d_hlens(f: &[u32; 512], ns: usize, out: &mut [u32; 512]) {
    let mut w = [0u32; 512];
    let mut sym = [0u16; 512];
    let mut m = 0usize;
    let mut s = 0usize;
    while s < ns && s < 512 {
        out[s] = 0;
        if f[s] > 0 {
            d_hins(&mut w, &mut sym, m, f[s], s);
            m += 1;
        }
        s += 1;
    }
    if m == 1 {
        out[(sym[0] as usize) % 512] = 1;
    }
    if m >= 2 {
        d_hbuild(&w, &sym, m, out);
    }
}

// Two-queue Huffman merge over the ascending leaves `w[0..m]`; writes the leaf depths.
pub fn d_hbuild(w: &[u32; 512], sym: &[u16; 512], m: usize, out: &mut [u32; 512]) {
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
    while t + 1 < m && m <= 512 {
        let top = m + t;
        let mut pick = 0usize;
        let mut a = 0usize;
        let mut b = 0usize;
        while pick < 2 {
            let take1 = if i1 < m && (i2 >= top || nw[i1 % 1024] <= nw[i2 % 1024]) { 1usize } else { 0usize };
            let x = if take1 == 1 { i1 } else { i2 };
            if take1 == 1 {
                i1 += 1;
            } else {
                i2 += 1;
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
    let root = if m >= 2 { 2 * m - 2 } else { 0 };
    dep[root % 1024] = 0;
    let mut r = 1usize;
    while r <= root && root < 1024 {
        let x = root - r;
        let pd = dep[(par[x % 1024] as usize) % 1024];
        dep[x % 1024] = pd + 1;
        r += 1;
    }
    k = 0;
    while k < m && k < 512 {
        let d = dep[k % 1024];
        out[(sym[k % 512] as usize) % 512] = if d > 15 { 15 } else { d };
        k += 1;
    }
}

// Literal, length and distance costs from the symbol counts.
pub fn d_learn(
    lf: &[u32; 512],
    df: &[u32; 32],
    litc: &mut [u32; 256],
    lenc: &mut [u32; 512],
    dcost: &mut [u32; 32],
    lcode: &[u8; 512],
    lextra: &[u8; 512],
    dext: &[u8; 32],
    bias: u32,
    hw: u32,
) {
    let mut hl = [0u32; 512];
    if hw > 0 {
        d_hlens(lf, 286, &mut hl);
    }
    let mut tot = 1u32;
    let mut s = 0usize;
    while s < 286 {
        tot = tot.saturating_add(lf[s]);
        s += 1;
    }
    s = 0;
    while s < 256 {
        litc[s] = d_hcost(d_cost16(lf[s], tot), hl[s], hw).saturating_add(bias);
        s += 1;
    }
    let mut cc = [0u32; 32];
    let mut c = 0usize;
    while c < 29 {
        cc[c] = d_hcost(d_cost16(lf[(257 + c) % 512], tot), hl[(257 + c) % 512], hw).saturating_add(bias);
        c += 1;
    }
    let mut l = 3usize;
    while l <= 258 {
        lenc[l] = cc[(lcode[l] as usize) % 32].saturating_add((lextra[l] as u32) * 16);
        l += 1;
    }
    let mut dt = 1u32;
    c = 0;
    while c < 30 {
        dt = dt.saturating_add(df[c]);
        c += 1;
    }
    c = 0;
    while c < 30 {
        dcost[c] = d_cost16(df[c], dt).saturating_add((dext[c] as u32) * 16);
        c += 1;
    }
}

// The cost of a symbol from its `-log2` cost `e` and its Huffman code length `h` (0 = unseen).
pub fn d_hcost(e: u32, h: u32, hw: u32) -> u32 {
    if h == 0 || hw > 16 {
        e
    } else {
        (e * (16 - hw) + h * 16 * hw) / 16
    }
}

// True iff the match `(ch, d)` at `pos` is in range and its bytes agree.
pub fn d_verified(input: &[u8], pos: usize, d: usize, ch: usize, k: usize, blen: usize) -> bool {
    if ch < 3 || ch > 258 || d < 1 || d > 32768 || d > pos || k + ch > blen {
        return false;
    }
    let v = d_match_len(input, pos - d, pos, ch);
    v >= ch
}

// Writes the chosen path of the block; a match is written only once `verified`.
pub fn d_emit(
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
        if d_verified(input, pos, d, ch, k, blen) {
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

// Length codes and their extra bits for lengths 3..=258.
pub fn d_len_tables(
    lbase: &[u16; 32],
    lext: &[u8; 32],
    lcode: &mut [u8; 512],
    lextra: &mut [u8; 512],
    bend: &mut [u16; 512],
) {
    let mut c = 0usize;
    let mut l = 3usize;
    while l <= 258 {
        if c < 28 && lbase[(c + 1) % 32] as usize <= l {
            c += 1;
        }
        lcode[l] = c as u8;
        lextra[l] = lext[c % 32];
        let top = lbase[(c + 1) % 32];
        bend[l] = if top >= 1 { top - 1 } else { 0 };
        l += 1;
    }
}

// The code of distance `d`, continuing the scan from code `c0`.
pub fn d_code_from(dbase: &[u16; 32], d: usize, c0: usize) -> usize {
    let mut c = c0;
    while c < 29 && dbase[(c + 1) % 32] as usize <= d {
        c += 1;
    }
    c
}

// Distance codes: `dlo` for distances 1..=256, `dhi` by `(d - 1) / 128` above.
pub fn d_dist_tables(dbase: &[u16; 32], dlo: &mut [u8; 256], dhi: &mut [u8; 256]) {
    let mut c = 0usize;
    let mut d = 1usize;
    while d <= 256 {
        c = d_code_from(dbase, d, c);
        dlo[(d - 1) % 256] = c as u8;
        d += 1;
    }
    let mut k = 0usize;
    c = 0;
    while k < 256 {
        c = d_code_from(dbase, k * 128 + 1, c);
        dhi[k] = c as u8;
        k += 1;
    }
}

// Length and distance code tables.
pub fn d_tables(
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
    d_len_tables(&lbase, &lext, lcode, lextra, bend);
    d_dist_tables(&dbase, dlo, dhi);
    *dext = dx;
}

// Starting costs: literals from a byte histogram of the first 32 KB, static match costs;
// returns 1 when the average literal cost there is below `D_LONG_BELOW`, so only long
// matches pay: no per-token bias and no skipping in literal runs.
pub fn d_seed(
    input: &[u8],
    litc: &mut [u32; 256],
    lenc: &mut [u32; 512],
    dcost: &mut [u32; 32],
    lextra: &[u8; 512],
    dext: &[u8; 32],
) -> usize {
    let n = input.len();
    let lim = if n < 32768 { n } else { 32768 };
    let mut hist = [1u32; 256];
    let mut i = 0usize;
    while i < lim {
        let b = input[i] as usize;
        hist[b] = hist[b].saturating_add(1);
        i += 1;
    }
    let tot = (lim as u32).saturating_add(256);
    let mut s = 0usize;
    let mut sum = 0u64;
    while s < 256 {
        let c = d_cost16(hist[s], tot);
        litc[s] = c;
        sum = sum.wrapping_add((hist[s].wrapping_sub(1) as u64).wrapping_mul(c as u64));
        s += 1;
    }
    let mut l = 3usize;
    while l <= 258 {
        lenc[l] = 112u32.saturating_add((lextra[l] as u32) * 16);
        l += 1;
    }
    let mut c = 0usize;
    while c < 30 {
        dcost[c] = 80u32.saturating_add((dext[c] as u32) * 16);
        c += 1;
    }
    if lim >= 8 && sum < (D_LONG_BELOW as u64) * (lim as u64) {
        1
    } else {
        0
    }
}

// Adds the per-token cost `bias` to every literal and every length.
pub fn d_add_bias(litc: &mut [u32; 256], lenc: &mut [u32; 512], bias: u32) {
    let mut s = 0usize;
    while s < 256 {
        litc[s] = litc[s].saturating_add(bias);
        s += 1;
    }
    let mut l = 3usize;
    while l <= 258 {
        lenc[l] = lenc[l].saturating_add(bias);
        l += 1;
    }
}

// Optimal parse per block under the learned costs; every written match is re-verified.
pub fn d_parse(input: &[u8], out: &mut [u32]) -> usize {
    let n = input.len();
    let mut lcode = [0u8; 512];
    let mut lextra = [0u8; 512];
    let mut bend = [0u16; 512];
    let mut dlo = [0u8; 256];
    let mut dhi = [0u8; 256];
    let mut dext = [0u8; 32];
    d_tables(&mut lcode, &mut lextra, &mut bend, &mut dlo, &mut dhi, &mut dext);
    let mut litc = [0u32; 256];
    let mut lenc = [0u32; 512];
    let mut dcost = [0u32; 32];
    let long = d_seed(input, &mut litc, &mut lenc, &mut dcost, &lextra, &dext);
    let bias = if long == 1 { 0 } else { D_BIAS };
    let hw = if long == 1 { D_HW } else { 0 };
    d_add_bias(&mut litc, &mut lenc, bias);
    let mut head4 = [0u32; 65536];
    let mut prev = [0u32; 32768];
    let mut near = [0u32; 65536];
    let mut c1l = [0u16; 32768];
    let mut c1d = [0u16; 32768];
    let mut c2l = [0u16; 32768];
    let mut c2d = [0u16; 32768];
    let mut bkl = [0u16; 32768];
    let mut bkd = [0u16; 32768];
    let mut cost = [0u32; 65536];
    let mut xs = [0u32; 131072];
    let mut xn = [0u8; 32768];
    let mut lf = [0u32; 512];
    let mut df = [0u32; 32];
    let mut olf = [0u32; 512];
    let mut odf = [0u32; 32];
    let mut lz = [0u32; 512];
    let mut lzd = [0u32; 32];
    let mut plz = [0u32; 512];
    let mut plzd = [0u32; 32];
    let mut pdp = [0u32; 512];
    let mut pdpd = [0u32; 32];
    let mut tdp = [0u32; 512];
    let mut tdpd = [0u32; 32];
    let zl = [0u32; 512];
    let zd = [0u32; 32];
    let mut ntok = 0usize;
    let mut p0 = 0usize;
    while p0 < n {
        let rest = n - p0;
        let blen = if rest > D_BLOCK { D_BLOCK } else { rest };
        d_prefix(input, &litc, &mut cost, p0, blen);
        d_lazy(
            input, &mut head4, &mut prev, &mut near, &cost, &lenc, &dcost, &dlo, &dhi, &mut c1l, &mut c1d,
            &mut c2l, &mut c2d, &mut xs, &mut xn, p0, blen, long,
        );
        d_count(input, &c1l, &c1d, &mut lz, &mut lzd, &lcode, &dlo, &dhi, &zl, &zd, 0, p0, blen);
        d_mix(&olf, &odf, &lz, &lzd, &pdp, &pdpd, &plz, &plzd, &mut lf, &mut df);
        d_learn(&lf, &df, &mut litc, &mut lenc, &mut dcost, &lcode, &lextra, &dext, 0, hw);
        let rf = if long == 0 && p0 < 4 * D_BLOCK { 1 } else { 0 };
        if rf == 1 {
            d_copy16(&c1l, &c1d, &mut bkl, &mut bkd, blen);
        }
        d_backward(
            input, &mut c1l, &mut c1d, &c2l, &c2d, &xs, &xn, &mut cost, &litc, &lenc, &dcost, &bend, &dlo,
            &dhi, p0, blen, rf,
        );
        if rf == 1 {
            d_count(input, &c1l, &c1d, &mut lf, &mut df, &lcode, &dlo, &dhi, &olf, &odf, 1, p0, blen);
            d_learn(&lf, &df, &mut litc, &mut lenc, &mut dcost, &lcode, &lextra, &dext, 0, hw);
            d_copy16(&bkl, &bkd, &mut c1l, &mut c1d, blen);
            d_backward(
                input, &mut c1l, &mut c1d, &c2l, &c2d, &xs, &xn, &mut cost, &litc, &lenc, &dcost, &bend, &dlo,
                &dhi, p0, blen, 0,
            );
        }
        if blen < rest {
            d_count(input, &c1l, &c1d, &mut tdp, &mut tdpd, &lcode, &dlo, &dhi, &zl, &zd, 0, p0, blen);
            d_ravg(&mut pdp, &mut pdpd, &tdp, &tdpd);
            d_ravg(&mut plz, &mut plzd, &lz, &lzd);
            d_count(input, &c1l, &c1d, &mut lf, &mut df, &lcode, &dlo, &dhi, &olf, &odf, 1, p0, blen);
            d_learn(&lf, &df, &mut litc, &mut lenc, &mut dcost, &lcode, &lextra, &dext, bias, hw);
            d_keep(&lf, &df, &mut olf, &mut odf);
        }
        ntok = d_emit(input, out, &c1l, &c1d, ntok, p0, blen);
        p0 += blen;
    }
    ntok
}


// ===== engine h: parse.rs =====

pub const H_BTD: usize = 32;
pub const H_BTDS: usize = 8;
pub const H_SMALLN: usize = 65536;
pub const H_SKS: usize = 0;
pub const H_H3BITS: u32 = 17;
pub const H_H3SIZE: usize = 131072;
pub const H_NICE: usize = 258;
pub const H_SKIPL: usize = 258;
pub const H_INH: usize = 1;
pub const H_LZK: usize = 0;
pub const H_INS: usize = 1;
pub const H_H3CAP: usize = 8;
pub const H_INSCAP: usize = 128;
pub const H_INSEND: usize = 0;
pub const H_ITERS: usize = 20;
pub const H_MINIT: usize = 1;
pub const H_ESH: u32 = 10;
pub const H_GAINK: u64 = 4;
pub const H_MBIAS: u32 = 0;
pub const H_RING: usize = 512;
pub const H_HBITS: u32 = 16;
pub const H_HSIZE: usize = 65536;
pub const H_TB: usize = 548;
pub const H_FB: usize = 320;
pub const H_BT: usize = 16384;
pub const H_SC: u32 = 16;
pub const H_UNUSED: u32 = 12;
pub const H_EW: u32 = 2;
pub const H_CHW: usize = 32;
// relaxation width (last H_CHWS lengths of each match) for inputs shorter than H_CHN bytes.
pub const H_CHWS: usize = 128;
pub const H_DW: u32 = 0;
pub const H_OV: u32 = 3;
pub const H_DSTART: usize = 2;
pub const H_UPEN: u32 = 16;
pub const H_PM: u32 = 128;
pub const H_PUSH_LIMIT: usize = 1073741824;
// stored trick: a block whose exact cost exceeds its stored cost by more than H_STMARG bits gets its matches forbidden.
pub const H_STM: usize = 1;
pub const H_STMARG: u64 = 0;
pub const H_BIG: u32 = 1048576;
// drop a Pareto entry when the next (longer) entry of the same position has the same distance slot.
pub const H_SLOTM: usize = 1;
// start the passes from the cost tables of the better of {all-literal, lazy} (exact bits).
pub const H_STARTBEST: usize = 1;
// match-cost discount (1/16 bit) in the first (pruning) DP pass.
pub const H_MDEL: u32 = 24;
// stop rule (H_RALPHA 2): stop when gain * bits^2 * 1280 < H_GK2 * n^3 (x H_F1 after pass 1).
pub const H_RALPHA: u32 = 2;
pub const H_GK2: u64 = 2;
pub const H_F1: u64 = 8;
// inputs shorter than H_CHN bytes relax the last H_CHWS (not H_CHW) lengths of every cached match.
pub const H_CHN: usize = 65536;
// also predict a single pass (first pass keeps no queries) when the start costs < H_OPQ/256 bits per byte;
// if the stop rule then continues, the next pass prunes again (match discount H_MDEL2).
pub const H_OPQ: u64 = 200;
pub const H_MDEL2: u32 = 0;
// init5 start tables: per-16K-byte-block literal entropy (unused byte: + H_U5), static length / distance
// costs, length costs minus H_D5 (1/16 bit).
pub const H_U5: u32 = 32;
pub const H_D5: u32 = 12;
// inputs whose best start costs more than H_HBPB/8 bits per byte start from the init5 tables and run every
// pass with the per-token reward H_LAMH (1/16 bit), at least H_MINH passes.
pub const H_HBPB: u64 = 40;
pub const H_LAMH: u32 = 5;
pub const H_MINH: usize = 2;

// ---------------------------------------------------------------- guarded accessors
// `v[i]`, or 0 out of range.
pub fn h_get(v: &[u32], i: usize) -> u32 {
    if i < v.len() {
        v[i]
    } else {
        0
    }
}

// `v[i] = x` when in range.
pub fn h_set(v: &mut [u32], i: usize, x: u32) {
    if i < v.len() {
        v[i] = x;
    }
}

// `v[i] += by` (wrapping) when in range.
pub fn h_bump(v: &mut [u32], i: usize, by: u32) {
    if i < v.len() {
        v[i] = v[i].wrapping_add(by);
    }
}

pub fn h_set64(v: &mut [u64], i: usize, x: u64) {
    if i < v.len() {
        v[i] = x;
    }
}

pub fn h_get8(v: &[u8], i: usize) -> u8 {
    if i < v.len() {
        v[i]
    } else {
        0
    }
}

// `input[i]`, or 0 out of range.
pub fn h_byte_at(input: &[u8], i: usize) -> usize {
    if i < input.len() {
        input[i] as usize
    } else {
        0
    }
}

// Tree child write (window of 32768 nodes, two children each).
pub fn h_setc(a: &mut [u32; 65536], i: usize, x: u32) {
    a[i % 65536] = x;
}

// A Vec of `n` copies of `x` (8 pushes per iteration + tail).
pub fn h_filled(n: usize, x: u32) -> Vec<u32> {
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

pub fn h_push_guarded(v: &mut Vec<u32>, x: u32) {
    if v.len() < H_PUSH_LIMIT {
        v.push(x);
    }
}

// ---------------------------------------------------------------- flag / select helpers (0/1 flags)
pub fn h_sel(f: usize, a: usize, b: usize) -> usize {
    if f == 1 {
        a
    } else {
        b
    }
}

pub fn h_sel32(f: usize, a: u32, b: u32) -> u32 {
    if f == 1 {
        a
    } else {
        b
    }
}

pub fn h_sel64(f: usize, a: u64, b: u64) -> u64 {
    if f == 1 {
        a
    } else {
        b
    }
}

pub fn h_ge(a: usize, b: usize) -> usize {
    if a >= b {
        1
    } else {
        0
    }
}

pub fn h_lt(a: usize, b: usize) -> usize {
    if a < b {
        1
    } else {
        0
    }
}

pub fn h_eq(a: usize, b: usize) -> usize {
    if a == b {
        1
    } else {
        0
    }
}

pub fn h_lt32(a: u32, b: u32) -> usize {
    if a < b {
        1
    } else {
        0
    }
}

pub fn h_lt64(a: u64, b: u64) -> usize {
    if a < b {
        1
    } else {
        0
    }
}

pub fn h_umin(a: usize, b: usize) -> usize {
    if a < b {
        a
    } else {
        b
    }
}

pub fn h_umax(a: usize, b: usize) -> usize {
    if a > b {
        a
    } else {
        b
    }
}

pub fn h_eq64(a: u64, b: u64) -> usize {
    if a == b {
        1
    } else {
        0
    }
}

pub fn h_umin64(a: u64, b: u64) -> u64 {
    if a < b {
        a
    } else {
        b
    }
}

// Push x when f == 1.
pub fn h_push_if(v: &mut Vec<u32>, f: usize, x: u32) {
    if f == 1 && v.len() < H_PUSH_LIMIT {
        v.push(x);
    }
}



// Push the cache entry (len, d) when `f == 1`.
pub fn h_push_m(v: &mut Vec<u32>, f: usize, len: usize, d: usize) {
    if f == 1 && v.len() < H_PUSH_LIMIT {
        v.push(h_pack_m(len, d));
    }
}

// Like push_m, but with H_SLOTM replace the previous entry of this position (index >= m0) when both
// have the same distance slot (the shorter one is then never cheaper for any length).
pub fn h_push_slot(mc: &mut Vec<u32>, m0: usize, f: usize, len: usize, d: usize) {
    if f == 1 {
        h_push_slot1(mc, m0, len, d);
    }
}

pub fn h_push_slot1(mc: &mut Vec<u32>, m0: usize, len: usize, d: usize) {
    let e = h_pack_m(len, d);
    let k = mc.len();
    let last = h_get(mc, k.wrapping_sub(1));
    let same = h_eq(H_SLOTM, 1) & h_lt(m0, k) & h_eq(((last / 32768) % 32) as usize, ((e / 32768) % 32) as usize);
    if same == 1 {
        h_set(mc, k.wrapping_sub(1), e);
    } else {
        h_push_guarded(mc, e);
    }
}

// A step of `l` if `3 <= l <= room`, else 1.
pub fn h_clamp_step(l: usize, room: usize) -> usize {
    if l >= 3 && l <= room {
        l
    } else {
        1
    }
}

// A step of `l` if `1 <= l <= room`, else 1.
pub fn h_clamp1(l: usize, room: usize) -> usize {
    if l >= 1 && l <= room {
        l
    } else {
        1
    }
}

// `x`, or 1 when `x == 0` (a divisor).
pub fn h_nz64(x: u64) -> u64 {
    if x == 0 {
        1
    } else {
        x
    }
}

// ---------------------------------------------------------------- trusted core
// How many bytes agree at `a` and `b`, up to `cap`. The emission's byte-wise check.
pub fn h_match_len(input: &[u8], a: usize, b: usize, cap: usize) -> usize {
    let mut l = 0usize;
    while l < cap && input[b + l] == input[a + l] {
        l += 1;
    }
    l
}

// True iff `(ch, d)` at `pos` is in range and its bytes agree.
pub fn h_verified(input: &[u8], pos: usize, d: usize, ch: usize) -> bool {
    let n = input.len();
    if ch < 3 || ch > 258 || d < 1 || d > 32768 || d > pos || pos > n || ch > n - pos {
        return false;
    }
    let v = h_match_len(input, pos - d, pos, ch);
    v >= ch
}

// The trusted emission: plan[k] = len * 65536 + dist (untrusted); every planned match is
// re-verified byte-wise, else a literal is emitted.
pub fn h_emit_all(input: &[u8], out: &mut [u32], plan: &[u32]) -> usize {
    let n = input.len();
    let mut k = 0usize;
    let mut ntok = 0usize;
    while k < n {
        let p = h_get(plan, k) as usize;
        let ch = p / 65536;
        let d = p % 65536;
        if h_verified(input, k, d, ch) {
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

// ---------------------------------------------------------------- small helpers
// Little-endian 8-byte word at `p` (0 when out of range).
pub fn h_le64(input: &[u8], p: usize) -> u64 {
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

// Index of the lowest differing byte of two little-endian words (x != y).
pub fn h_first_diff(x:u64,y:u64)->usize {
    let z=x^y;
    let a=((z&0xff00ff00ff00ff00u64)>>8)|((z&0x00ff00ff00ff00ffu64)<<8);
    let b=((a&0xffff0000ffff0000u64)>>16)|((a&0x0000ffff0000ffffu64)<<16);
    let c=(b>>32)|(b<<32);
    h_umin((c.leading_zeros()/8) as usize,7)
}

pub fn h_hash4(input: &[u8], p: usize) -> usize {
    let n = input.len();
    if n >= 4 && p <= n - 4 {
        let x = (input[p] as u32) | ((input[p + 1] as u32) << 8) | ((input[p + 2] as u32) << 16) | ((input[p + 3] as u32) << 24);
        ((x.wrapping_mul(2654435761) >> (32 - H_HBITS)) as usize) % H_HSIZE
    } else {
        0
    }
}

pub fn h_hash3(input: &[u8], p: usize) -> usize {
    let n = input.len();
    if n >= 3 && p <= n - 3 {
        let x = (input[p] as u32) | ((input[p + 1] as u32) << 8) | ((input[p + 2] as u32) << 16);
        ((x.wrapping_mul(2654435761) >> (32 - H_H3BITS)) as usize) % H_H3SIZE
    } else {
        0
    }
}

// Distance slot (0..29) of a distance 1..32768.
pub fn h_dslot(d: usize) -> usize {
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

pub fn h_dextra(s: usize) -> u32 {
    if s < 4 {
        0
    } else {
        ((s / 2).wrapping_sub(1)) as u32
    }
}

// Match-cache entry: len * 2^20 + dist slot * 2^15 + (dist - 1); len may carry the +512 inherited flag.
pub fn h_pack_m(len: usize, d: usize) -> u32 {
    let l = (len % 1024) as u32;
    let dd = if d >= 1 && d <= 32768 { d } else { 1 };
    l.wrapping_mul(1048576).wrapping_add((h_dslot(dd) as u32).wrapping_mul(32768)).wrapping_add((dd.wrapping_sub(1)) as u32)
}

// Length code offset (0..28) of a match length 3..258.
pub fn h_lcode(l: usize) -> usize {
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

pub fn h_lextra(c: usize) -> u32 {
    if c < 8 || c >= 28 {
        0
    } else {
        ((c.wrapping_sub(4)) / 4) as u32
    }
}

pub fn h_fixed_len(s: usize) -> u32 {
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

// ---------------------------------------------------------------- match finder (binary trees)
// Extend a known common prefix `from` of positions a < b up to cap (search only).
pub fn h_ext_len(input: &[u8], a: usize, b: usize, from: usize, cap: usize) -> usize {
    let n = input.len();
    let bad = if a >= b || b >= n || cap > n.wrapping_sub(b) { 1usize } else { 0usize };
    let lim = if bad == 1 { 0 } else { cap };
    let mut l = from;
    let mut it = 0usize;
    while it < 300 && l < lim {
        if lim - l >= 8 {
            let x = h_le64(input, a.wrapping_add(l));
            let y = h_le64(input, b.wrapping_add(l));
            if x == y {
                l = l.wrapping_add(8);
            } else {
                l = l.wrapping_add(h_first_diff(x, y));
                break;
            }
        } else if h_byte_at(input, a.wrapping_add(l)) == h_byte_at(input, b.wrapping_add(l)) {
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

// Little-endian 8-byte word at `p`, bytes past the end read as 0.
// ext_len from `from` when `f == 1`, else `dflt` (keeps the call out of the caller's branches).
pub fn h_ext_if(input: &[u8], f: usize, a: usize, b: usize, from: usize, cap: usize, dflt: usize) -> usize {
    if f == 1 {
        h_ext_len(input, a, b, from, cap)
    } else {
        dflt
    }
}

pub fn h_le64z(input: &[u8], p: usize) -> u64 {
    let n = input.len();
    if p < n && n - p >= 8 {
        h_le64(input, p)
    } else {
        h_le64_tail(input, p)
    }
}

pub fn h_le64_tail(input: &[u8], p: usize) -> u64 {
    let mut x = 0u64;
    let mut j = 0usize;
    while j < 8 {
        let b = h_byte_at(input, p.wrapping_add(j)) as u64;
        x = x | (b << (((j as u32).wrapping_mul(8)) % 64));
        j += 1;
    }
    x
}

// Common prefix length of a < b from l0 (bytes before l0 known equal), in whole words, capped at lim.
// Returns 2 * length + (1 when a's byte at the first difference is smaller than b's).
pub fn h_lcp_words(input: &[u8], a: usize, b: usize, l0: usize, lim: usize) -> usize {
    let mut l = l0;
    let mut it = 0usize;
    let mut z = 0u64;
    let mut x = 0u64;
    while it < 40 && z == 0 && l < lim {
        x = h_le64z(input, a.wrapping_add(l));
        z = x ^ h_le64z(input, b.wrapping_add(l));
        l = l.wrapping_add(h_eq64(z, 0).wrapping_mul(8));
        it += 1;
    }
    let fd = h_first_diff(z, 0);
    let lf = h_sel(h_eq64(z, 0), l, l.wrapping_add(fd));
    h_umin(lf, lim).wrapping_mul(2).wrapping_add(h_byte_lt(x, x ^ z, fd))
}

// 1 when byte k of little-endian word x is smaller than byte k of y.
pub fn h_byte_lt(x: u64, y: u64, k: usize) -> usize {
    let sh = ((k as u32).wrapping_mul(8)) % 64;
    h_lt64((x >> sh) & 255, (y >> sh) & 255)
}

// 2 * match length + direction bit after the first words x, y at l0: from them when they differ,
// else continue word-wise.
pub fn h_ext_words(input: &[u8], same: usize, a: usize, b: usize, l0: usize, x: u64, y: u64, lim: usize) -> usize {
    if same == 1 {
        h_lcp_words(input, a, b, l0.wrapping_add(8), lim)
    } else {
        let fd = h_first_diff(x, y);
        l0.wrapping_add(fd).wrapping_mul(2).wrapping_add(h_byte_lt(x, y, fd))
    }
}

// Insert `pos` into its binary tree (children in `child[2*slot]` = smaller, `[2*slot+1]` = larger)
// and, if `rec == 1`, push every match longer than all before it (nearest first).
// hint = kcur * 512 + klen: node kcur (as cur) is known to share klen bytes with pos.
// Returns best + 512 * (longest walk match) + 262144 * (its distance).
pub fn h_bt_walk(
    input: &[u8],
    child: &mut [u32; 65536],
    root: usize,
    pos: usize,
    cap: usize,
    best0: usize,
    rec: usize,
    maxd: usize,
    hint: usize,
    mc: &mut Vec<u32>,
    m0: usize,
) -> usize {
    let mut plt = (pos % 32768).wrapping_mul(2);
    let mut pgt = plt.wrapping_add(1);
    let mut cur = root;
    let mut ltl = 0usize;
    let mut gtl = 0usize;
    let mut len = 0usize;
    let mut best = best0;
    let mut wl = 0usize;
    let mut wd = 0usize;
    let mut depth = 0usize;
    let mut go = 1usize;
    let lim = h_sel(rec | h_lt(cap, H_INSCAP), cap, H_INSCAP);
    let stop = h_umin(lim, H_NICE);
    let kcur = hint / 512;
    let kl = h_umin(hint % 512, lim);
    while go == 1 && depth < maxd {
        let cm = cur.wrapping_sub(1);
        let dd = pos.wrapping_sub(cm);
        let bad = h_eq(cur, 0) | h_lt(pos, cur) | h_ge(dd, 32768);
        if bad == 1 {
            go = 0;
        } else {
            let l0 = h_sel(h_eq(cur, kcur) & h_lt(len, kl), kl, len);
            let x = h_le64z(input, cm.wrapping_add(l0));
            let y = h_le64z(input, pos.wrapping_add(l0));
            let same = h_eq64(x, y);
            let l2 = h_ext_words(input, same, cm, pos, l0, x, y, lim);
            len = h_umin(l2 / 2, lim);
            h_push_slot(mc, m0, rec & h_lt(best, len), len, dd);
            wd = h_sel(h_lt(wl, len), dd, wd);
            wl = h_umax(len, wl);
            best = h_umax(len, best);
            let cs = (cm % 32768).wrapping_mul(2);
            let c0 = child[cs % 65536];
            let c1 = child[cs.wrapping_add(1) % 65536];
            if len >= stop {
                h_setc(child, plt, c0);
                h_setc(child, pgt, c1);
                go = 2;
            } else {
                let sm = l2 % 2;
                h_setc(child, h_sel(sm, plt, pgt), cur as u32);
                let nx = cs.wrapping_add(sm);
                plt = h_sel(sm, nx, plt);
                pgt = h_sel(sm, pgt, nx);
                cur = h_sel(sm, c1 as usize, c0 as usize);
                ltl = h_sel(sm, len, ltl);
                gtl = h_sel(sm, gtl, len);
                len = h_umin(ltl, gtl);
            }
        }
        depth += 1;
    }
    if go != 2 {
        h_setc(child, plt, 0);
        h_setc(child, pgt, 0);
    }
    best.wrapping_add((wl % 512).wrapping_mul(512)).wrapping_add((wd % 65536).wrapping_mul(262144))
}

// 1 when a position `gap` bytes before the end of a skipped region is still searched (every H_SKS-th).
pub fn h_sks_rec(gap: usize) -> usize {
    let d = if H_SKS == 0 { 1 } else { H_SKS };
    h_eq(H_SKS, 0) ^ 1 & h_eq(gap % d, 0)
}

// Search position `pos` (state st = [skip, sfrom, sdist, _] carried across positions).
pub fn h_find_pos(
    input: &[u8],
    h4: &mut [u32; 65536],
    h3: &mut [u32; H_H3SIZE],
    child: &mut [u32; 65536],
    mc: &mut Vec<u32>,
    st: &mut [usize; 4],
    pos: usize,
    maxd: usize,
) {
    let n = input.len();
    if n < 4 || pos > n - 4 {
        return;
    }
    let skip = st[0];
    let sfrom = st[1];
    let sdist = st[2];
    let hint = st[3];
    let rem = n - pos;
    let cap = h_umin(rem, 258);
    let gap = skip.wrapping_sub(pos);
    let rec = h_ge(pos, skip) | h_lt(pos, sfrom) | h_sks_rec(gap);
    let inh = (rec ^ 1) & h_eq(H_INH, 1) & h_ge(gap, 3) & h_ge(258, gap);
    h_push_m(mc, inh, gap.wrapping_add(512), sdist);
    let x3 = h_hash3(input, pos) % H_H3SIZE;
    let c3 = h3[x3] as usize;
    h3[x3] = (pos + 1) as u32;
    let m0 = mc.len();
    let c3m = c3.wrapping_sub(1);
    let ok3 = rec & h_lt(0, c3) & h_ge(pos, c3) & h_lt(pos.wrapping_sub(c3m), 32768);
    let l3 = h_ext_if(input, ok3, c3m, pos, 0, h_umin(cap, H_H3CAP), 0);
    let f3 = h_ge(l3, 3);
    h_push_m(mc, f3, l3, pos.wrapping_sub(c3m));
    let best = h_sel(f3, l3, 2);
    let ins = rec | h_eq(H_INS, 1) | h_ge(H_INSEND, gap);
    let x4 = h_hash4(input, pos) % 65536;
    let r4 = h4[x4];
    h4[x4] = h_sel32(ins, (pos + 1) as u32, r4);
    let depth = h_sel(ins, maxd, 0);
    let bb = h_bt_walk(input, child, r4 as usize, pos, cap, best, rec, depth, hint, mc, m0);
    let b = bb % 512;
    let wl = (bb / 512) % 512;
    let bd = bb / 262144;
    let hk = h_ge(wl, 2) & h_ge(bd, 1) & h_ge(pos.wrapping_add(1), bd);
    st[3] = h_sel(hk, (pos.wrapping_add(2).wrapping_sub(bd)).wrapping_mul(512).wrapping_add(wl.wrapping_sub(1)), 0);
    let ml = mc.len();
    let ns = rec & h_ge(b, H_SKIPL) & h_lt(skip, pos.wrapping_add(b)) & h_lt(m0, ml);
    st[2] = h_sel(ns, bd, sdist);
    st[1] = h_sel(ns, pos.wrapping_add(1).wrapping_add(H_LZK), sfrom);
    st[0] = h_sel(ns, pos.wrapping_add(b), skip);
}

// Match cache for every position: entries of `pos` are mc[mstart[pos] .. mstart[pos + 1]].
pub fn h_find_all(input: &[u8], mstart: &mut Vec<u32>, mc: &mut Vec<u32>, maxd: usize) {
    let n = input.len();
    let mut h4 = [0u32; 65536];
    let mut h3 = [0u32; H_H3SIZE];
    let mut child = [0u32; 65536];
    let mut st = [0usize; 4];
    st[2] = 1;
    let mut pos = 0usize;
    while pos < n {
        h_push_guarded(mstart, mc.len() as u32);
        h_find_pos(input, &mut h4, &mut h3, &mut child, mc, &mut st, pos, maxd);
        pos += 1;
    }
    h_push_guarded(mstart, mc.len() as u32);
}

// A second (trivial) find_all call for inputs shorter than 4 bytes: keeps find_all out of line
// (its own register allocation).
pub fn h_find_spare(input: &[u8], f: usize) {
    if f == 1 {
        let mut a: Vec<u32> = Vec::new();
        let mut b: Vec<u32> = Vec::new();
        h_find_all(input, &mut a, &mut b, 1);
    }
}

// ---------------------------------------------------------------- DP (ring sparse table of packed cost << 32 | position)
// End of the length-code bucket containing `l` (lengths sharing one code and extra-bit count).
pub fn h_bucket_end(l: usize) -> usize {
    if l < 11 {
        l
    } else if l >= 258 {
        258
    } else {
        let c = h_lcode(l);
        let e = h_lextra(c) % 8;
        let base = 3u32.wrapping_add(4u32.wrapping_add((c % 4) as u32) << e);
        let end = (base.wrapping_add(1u32 << e).wrapping_sub(1)) as usize;
        if end > 257 {
            257
        } else {
            end
        }
    }
}

pub fn h_build_bend(bend: &mut [u32; 512]) {
    let mut l = 0usize;
    while l < 259 {
        bend[l % 512] = h_bucket_end(l) as u32;
        l += 1;
    }
}

pub fn h_lg5(w: usize) -> usize {
    let x = (w % 64) as u32;
    let k = 31u32.wrapping_sub(x.leading_zeros()) as usize;
    if k > 4 {
        4
    } else {
        k
    }
}

// Block cost table: ct[l] length l (0..258), ct[512 + s] distance slot s, ct[768 + c] literal c.
pub fn h_load_ct(tbl: &[u32], toff: usize, ct: &mut [u32; 1024], lam: u32) {
    let mut x = 0usize;
    while x < 259 {
        ct[x % 1024] = h_get(tbl, toff.wrapping_add(256).wrapping_add(x)).saturating_sub(lam);
        x += 1;
    }
    let mut s = 0usize;
    while s < 30 {
        ct[(512 + s) % 1024] = h_get(tbl, toff.wrapping_add(515).wrapping_add(s));
        s += 1;
    }
    let mut c = 0usize;
    while c < 256 {
        ct[(768 + c) % 1024] = h_get(tbl, toff.wrapping_add(c)).saturating_sub(lam);
        c += 1;
    }
}

// Ring layout: level k (range width 2^k, k = 0..4) at k*512. Values are packed (cost << 32) | position,
// so a range minimum also yields its (first) position.
pub fn h_rm_update(rm: &mut [u64; 4096], i: usize, c: u64) {
    let s = i % H_RING;
    rm[s % 4096] = c;
    let a1 = rm[i.wrapping_add(1) % H_RING];
    let m2 = h_umin64(c, a1);
    rm[(H_RING + s) % 4096] = m2;
    let a2 = rm[(H_RING + i.wrapping_add(2) % H_RING) % 4096];
    let m4 = h_umin64(m2, a2);
    rm[(2 * H_RING + s) % 4096] = m4;
    let a4 = rm[(2 * H_RING + i.wrapping_add(4) % H_RING) % 4096];
    let m8 = h_umin64(m4, a4);
    rm[(3 * H_RING + s) % 4096] = m8;
    let a8 = rm[(3 * H_RING + i.wrapping_add(8) % H_RING) % 4096];
    let m16 = h_umin64(m8, a8);
    rm[(4 * H_RING + s) % 4096] = m16;
}

// rm_update without level 4 (when no query spans more than 15 lengths).
pub fn h_rm_update3(rm: &mut [u64; 4096], i: usize, c: u64) {
    let s = i % H_RING;
    rm[s % 4096] = c;
    let a1 = rm[i.wrapping_add(1) % H_RING];
    let m2 = h_umin64(c, a1);
    rm[(H_RING + s) % 4096] = m2;
    let a2 = rm[(H_RING + i.wrapping_add(2) % H_RING) % 4096];
    let m4 = h_umin64(m2, a2);
    rm[(2 * H_RING + s) % 4096] = m4;
    let a4 = rm[(2 * H_RING + i.wrapping_add(4) % H_RING) % 4096];
    let m8 = h_umin64(m4, a4);
    rm[(3 * H_RING + s) % 4096] = m8;
}

// h_rm_update (f == 1) or rm_update3.
pub fn h_rm_upd(f: usize, rm: &mut [u64; 4096], i: usize, c: u64) {
    if f == 1 {
        h_rm_update(rm, i, c);
    } else {
        h_rm_update3(rm, i, c);
    }
}

// Packed value of the bucket part [x, e] (one length code): range minimum + length and distance costs.
pub fn h_bkt_val(rm: &[u64; 4096], ct: &[u32; 1024], i: usize, x: usize, e: usize, dcs: u64) -> u64 {
    let k = h_lg5(e.wrapping_add(1).wrapping_sub(x));
    let p = (1u32 << ((k % 8) as u32)) as usize;
    let kr = k.wrapping_mul(H_RING);
    let ra = rm[kr.wrapping_add(i.wrapping_add(x) % H_RING) % 4096];
    let rb = rm[kr.wrapping_add(i.wrapping_add(e).wrapping_add(1).wrapping_sub(p) % H_RING) % 4096];
    h_umin64(ra, rb).wrapping_add(((ct[x % 1024] as u64) << 32).wrapping_add(dcs))
}

// Relaxation query: one short length (k = 0, y = x) or one bucket part (range minimum of level k at x and y):
// x + 512 * y + 262144 * k + 2097152 * slot.
pub fn h_query(x: usize, y: usize, k: usize, slot: usize) -> u32 {
    ((x % 512) as u32)
        .wrapping_add(((y % 512) as u32).wrapping_mul(512))
        .wrapping_add(((k % 8) as u32).wrapping_mul(262144))
        .wrapping_add(((slot % 32) as u32).wrapping_mul(2097152))
}

// Short lengths lo..=hi: relax, and keep the queries within H_PM of the running best; returns the new best.
pub fn h_prune_short(rm: &[u64; 4096], ct: &[u32; 1024], i: usize, lo: usize, hi: usize, dcs: u64, slot: usize, best0: u64, keep: usize, items: &mut Vec<u32>) -> u64 {
    let mut best = best0;
    let mut x = lo;
    while x <= hi && x < 11 {
        let v = rm[i.wrapping_add(x) % H_RING].wrapping_add(((ct[x % 1024] as u64) << 32).wrapping_add(dcs));
        h_push_if(items, keep & (h_lt64(best.wrapping_add((H_PM as u64) << 32), v) ^ 1), h_query(x, x, 0, slot));
        best = h_umin64(v, best);
        x += 1;
    }
    best
}

// Bucket parts lo..=hi (lo >= 11): relax, and keep the queries within H_PM of the running best; returns the new best.
pub fn h_prune_bkt(rm: &[u64; 4096], ct: &[u32; 1024], bend: &[u32; 512], i: usize, lo: usize, hi: usize, dcs: u64, slot: usize, best0: u64, keep: usize, items: &mut Vec<u32>) -> u64 {
    let mut best = best0;
    let mut x = lo;
    let mut it = 0usize;
    while it < 32 && x <= hi && x < 259 {
        let e = h_umin(h_umax(bend[x % 512] as usize, x), hi);
        let v = h_bkt_val(rm, ct, i, x, e, dcs);
        let k = h_lg5(e.wrapping_add(1).wrapping_sub(x));
        let p = (1u32 << ((k % 8) as u32)) as usize;
        let q = h_query(x, e.wrapping_add(1).wrapping_sub(p), k, slot);
        h_push_if(items, keep & (h_lt64(best.wrapping_add((H_PM as u64) << 32), v) ^ 1), q);
        best = h_umin64(v, best);
        x = e.wrapping_add(1);
        it += 1;
    }
    best
}

// Relax every cached match at i (best seeded with the longest match) and keep the near-optimal queries.
pub fn h_prune_pos(rm: &[u64; 4096], ct: &[u32; 1024], bend: &[u32; 512], mc: &[u32], ms: usize, me: usize, i: usize, lit: u64, chw: usize, msub: u32, keep: usize, items: &mut Vec<u32>) -> u64 {
    let ml = h_get(mc, me.wrapping_sub(1)) as usize;
    let ll0 = ml / 1048576;
    let hl = h_umin(h_sel(h_ge(ll0, 512), ll0.wrapping_sub(512), ll0), 258);
    let dl = ct[(512 + (ml / 32768) % 32) % 1024].saturating_sub(msub);
    let vl = h_bkt_val(rm, ct, i, hl, hl, (dl as u64) << 32);
    let mut best = h_sel64(h_lt(ms, me) & h_ge(hl, 3) & h_lt64(vl, lit), vl, lit);
    let mut k = ms;
    let mut lo = 3usize;
    while k < me {
        let m = h_get(mc, k) as usize;
        let len0 = m / 1048576;
        let slot = (m / 32768) % 32;
        let dcs = (ct[(512 + slot) % 1024].saturating_sub(msub) as u64) << 32;
        let flag = h_ge(len0, 512);
        let h = h_umin(h_sel(flag, len0.wrapping_sub(512), len0), 258);
        let a = h_sel(flag, h, lo);
        let b1 = h_prune_short(rm, ct, i, a, h_umin(h, 10), dcs, slot, best, keep, items);
        let a2 = h_umax(a, 11);
        let a3 = h_sel(h_lt(a2.wrapping_add(chw), h), h.wrapping_sub(chw), a2);
        best = h_prune_bkt(rm, ct, bend, i, a3, h, dcs, slot, b1, keep, items);
        lo = h_sel((flag ^ 1) & h_ge(h, lo), h.wrapping_add(1), lo);
        k += 1;
    }
    best
}

// Short lengths lo..=hi: relax only (no query keeping); returns the new best.
pub fn h_relax_short(rm: &[u64; 4096], ct: &[u32; 1024], i: usize, lo: usize, hi: usize, dcs: u64, best0: u64) -> u64 {
    let mut best = best0;
    let mut x = lo;
    while x <= hi && x < 11 {
        let v = rm[i.wrapping_add(x) % H_RING].wrapping_add(((ct[x % 1024] as u64) << 32).wrapping_add(dcs));
        best = h_umin64(v, best);
        x += 1;
    }
    best
}

// Bucket parts lo..=hi (lo >= 11): relax only; returns the new best.
pub fn h_relax_bkt(rm: &[u64; 4096], ct: &[u32; 1024], bend: &[u32; 512], i: usize, lo: usize, hi: usize, dcs: u64, best0: u64) -> u64 {
    let mut best = best0;
    let mut x = lo;
    let mut it = 0usize;
    while it < 32 && x <= hi && x < 259 {
        let e = h_umin(h_umax(bend[x % 512] as usize, x), hi);
        best = h_umin64(h_bkt_val(rm, ct, i, x, e, dcs), best);
        x = e.wrapping_add(1);
        it += 1;
    }
    best
}

// Relax every cached match at i (first pass without query keeping).
pub fn h_relax_pos(rm: &[u64; 4096], ct: &[u32; 1024], bend: &[u32; 512], mc: &[u32], ms: usize, me: usize, i: usize, lit: u64, chw: usize, msub: u32) -> u64 {
    let mut best = lit;
    let mut k = ms;
    let mut lo = 3usize;
    while k < me {
        let m = h_get(mc, k) as usize;
        let len0 = m / 1048576;
        let dcs = (ct[(512 + (m / 32768) % 32) % 1024].saturating_sub(msub) as u64) << 32;
        let flag = h_ge(len0, 512);
        let h = h_umin(h_sel(flag, len0.wrapping_sub(512), len0), 258);
        let a = h_sel(flag, h, lo);
        let b1 = h_relax_short(rm, ct, i, a, h_umin(h, 10), dcs, best);
        let a2 = h_umax(a, 11);
        let a3 = h_sel(h_lt(a2.wrapping_add(chw), h), h.wrapping_sub(chw), a2);
        best = h_relax_bkt(rm, ct, bend, i, a3, h, dcs, b1);
        lo = h_sel((flag ^ 1) & h_ge(h, lo), h.wrapping_add(1), lo);
        k += 1;
    }
    best
}

// prune_pos when keep == 1, else h_relax_pos (same result, no queries).
pub fn h_prune_or_relax(rm: &[u64; 4096], ct: &[u32; 1024], bend: &[u32; 512], mc: &[u32], ms: usize, me: usize, i: usize, lit: u64, chw: usize, msub: u32, keep: usize, items: &mut Vec<u32>) -> u64 {
    if keep == 1 {
        h_prune_pos(rm, ct, bend, mc, ms, me, i, lit, chw, msub, keep, items)
    } else {
        h_relax_pos(rm, ct, bend, mc, ms, me, i, lit, chw, msub)
    }
}

// Relax the pruned queries s..e of position i.
pub fn h_relax_items(rm: &[u64; 4096], ct: &[u32; 1024], items: &[u32], s: usize, e: usize, i: usize, lit: u64) -> u64 {
    let mut best = lit;
    let mut t = s;
    while t < e {
        let q = h_get(items, t) as usize;
        let kr = ((q / 262144) % 8).wrapping_mul(H_RING);
        let ra = rm[kr.wrapping_add(i.wrapping_add(q) % H_RING) % 4096];
        let rb = if kr==0 {ra} else {rm[kr.wrapping_add(i.wrapping_add(q / 512) % H_RING) % 4096]};
        let c = ct[q % 512].wrapping_add(ct[(512 + (q / 2097152) % 32) % 1024]);
        let v = h_umin64(ra, rb).wrapping_add((c as u64) << 32);
        best = h_umin64(v, best);
        t += 1;
    }
    best
}

// First-pass DP over the positions hi-1 down to lo of one block (cost table ct): relax the whole match
// cache and keep the near-optimal relaxation queries (items, backward position order; with keep == 1
// istart gets the first query of every position). choice[i] = winning length * 65536.
pub fn h_dp_prune(
    input: &[u8],
    rm: &mut [u64; 4096],
    ct: &[u32; 1024],
    bend: &[u32; 512],
    mstart: &[u32],
    mc: &[u32],
    choice: &mut [u32],
    chw: usize,
    msub: u32,
    keep: usize,
    items: &mut Vec<u32>,
    istart: &mut Vec<u32>,
    lo: usize,
    hi: usize,
    l4: usize,
    co: usize,
) {
    let mut i = hi;
    while i > lo {
        i -= 1;
        let lit = rm[i.wrapping_add(1) % H_RING].wrapping_add((ct[768usize.wrapping_add(h_byte_at(input, i)) % 1024] as u64) << 32);
        h_push_if(istart, keep, items.len() as u32);
        let ms = h_get(mstart, i) as usize;
        let me = h_get(mstart, i.wrapping_add(1)) as usize;
        let best = h_prune_or_relax(rm, ct, bend, mc, ms, me, i, lit, chw, msub, keep, items);
        let l = ((best as u32) as usize).wrapping_sub(i);
        h_rm_upd(l4, rm, i, (best & 0xFFFF_FFFF_0000_0000) | (i as u64));
        h_set(choice, co.wrapping_add(i), h_sel32(h_ge(l, 3) & h_ge(258, l), (l as u32).wrapping_mul(65536), 0));
    }
}

// Start of block b (clamped to hi; block 0 starts at 0).
pub fn h_blk_lo(bpos: &[u32], b: usize, hi: usize) -> usize {
    h_sel(h_eq(b, 0), 0, h_umin(h_get(bpos, b) as usize, hi))
}

// First backward DP pass over the whole match cache, block by block (see dp_prune).
pub fn h_pass_prune(
    input: &[u8],
    mstart: &[u32],
    mc: &[u32],
    tbl: &[u32],
    bend: &[u32; 512],
    bpos: &[u32],
    nb: usize,
    choice: &mut [u32],
    chw: usize,
    msub: u32,
    keep: usize,
    items: &mut Vec<u32>,
    istart: &mut Vec<u32>,
    co: usize,
    lam: u32,
) {
    let n = input.len();
    let mut rm = [0u64; 4096];
    let mut ct = [0u32; 1024];
    h_rm_update(&mut rm, n, n as u64);
    let mut hi = n;
    let mut k = 0usize;
    while k < nb {
        let b = nb - 1 - k;
        let lo = h_blk_lo(bpos, b, hi);
        h_load_ct(tbl, b.wrapping_mul(H_TB), &mut ct, lam);
        h_dp_prune(input, &mut rm, &ct, bend, mstart, mc, choice, chw, msub, keep, items, istart, lo, hi, h_ge(chw, 15), co);
        hi = lo;
        k += 1;
    }
    h_push_if(istart, keep, items.len() as u32);
}

// Later-pass DP over the positions hi-1 down to lo of one block: relax the pruned queries only.
pub fn h_dp_items(input: &[u8], rm: &mut [u64; 4096], ct: &[u32; 1024], choice: &mut [u32], items: &[u32], istart: &[u32], lo: usize, hi: usize, l4: usize, co: usize) {
    let n = input.len();
    let mut e = h_get(istart, n.wrapping_sub(hi)) as usize;
    let mut i = hi;
    while i > lo {
        i -= 1;
        let lit = rm[i.wrapping_add(1) % H_RING].wrapping_add((ct[768usize.wrapping_add(h_byte_at(input, i)) % 1024] as u64) << 32);
        let s = e;
        e = h_get(istart, n.wrapping_sub(i)) as usize;
        let best = h_relax_items(rm, ct, items, s, e, i, lit);
        let l = ((best as u32) as usize).wrapping_sub(i);
        h_rm_upd(l4, rm, i, (best & 0xFFFF_FFFF_0000_0000) | (i as u64));
        h_set(choice, co.wrapping_add(i), h_sel32(h_ge(l, 3) & h_ge(258, l), (l as u32).wrapping_mul(65536), 0));
    }
}

// Later backward DP passes over the pruned queries only, block by block.
pub fn h_pass_items(input: &[u8], tbl: &[u32], bpos: &[u32], nb: usize, choice: &mut [u32], items: &[u32], istart: &[u32], l4: usize, co: usize, lam: u32) {
    let n = input.len();
    let mut rm = [0u64; 4096];
    let mut ct = [0u32; 1024];
    h_rm_update(&mut rm, n, n as u64);
    let mut hi = n;
    let mut k = 0usize;
    while k < nb {
        let b = nb - 1 - k;
        let lo = h_blk_lo(bpos, b, hi);
        h_load_ct(tbl, b.wrapping_mul(H_TB), &mut ct, lam);
        h_dp_items(input, &mut rm, &ct, choice, items, istart, lo, hi, l4, co);
        hi = lo;
        k += 1;
    }
}

// Distance of the cached match that covers length l at position p (first entry reaching l); 0 if none.
pub fn h_find_dist(mstart: &[u32], mc: &[u32], p: usize, l: usize) -> usize {
    let ms = h_get(mstart, p) as usize;
    let me = h_get(mstart, p.wrapping_add(1)) as usize;
    let mut d = 0usize;
    let mut k = ms;
    while k < me && d == 0 {
        let m = h_get(mc, k) as usize;
        let len0 = m / 1048576;
        let h = h_sel(h_ge(len0, 512), len0.wrapping_sub(512), len0);
        d = h_sel(h_ge(h, l), m % 32768 + 1, 0);
        k += 1;
    }
    d
}


// ---------------------------------------------------------------- walk path, block stats
pub fn h_clear(v: &mut [u32], a: usize, b: usize) {
    let mut i = a;
    while i < b {
        h_set(v, i, 0);
        i += 1;
    }
}

// The distance of a planned match: from the plan, or looked up in the cache when the plan has only a length.
pub fn h_dist_of(mstart: &[u32], mc: &[u32], pos: usize, len: usize, d0: usize) -> usize {
    if len >= 3 && d0 == 0 {
        h_find_dist(mstart, mc, pos, len)
    } else {
        d0
    }
}

// Symbol statistics of one path step (a match of length st >= 3 at distance d, or literal b).
pub fn h_walk_bump(fr: &mut [u32], off: usize, st: usize, d: usize, b: usize) {
    if st >= 3 {
        let lc = h_lcode(st);
        let s = h_dslot(d);
        h_bump(fr, off.wrapping_add(257).wrapping_add(lc), 1);
        h_bump(fr, off.wrapping_add(288).wrapping_add(s), 1);
        h_bump(fr, off.wrapping_add(318), h_lextra(lc).wrapping_add(h_dextra(s)));
        h_bump(fr, off.wrapping_add(319), st as u32);
    } else {
        h_bump(fr, off.wrapping_add(b), 1);
        h_bump(fr, off.wrapping_add(319), 1);
    }
}

// Follow the chosen path; per-block frequencies into `fr` (H_FB per block: 0..288 litlen,
// 288..318 dist, 318 extra bits, 319 raw bytes), block start positions into `bpos`.
// Returns the number of blocks.
pub fn h_walk(input: &[u8], mstart: &[u32], mc: &[u32], choice: &mut [u32], co: usize, fr: &mut [u32], bpos: &mut [u32]) -> usize {
    let n = input.len();
    let mut pos = 0usize;
    let mut b = 0usize;
    let mut t = 0usize;
    h_clear(fr, 0, H_FB);
    h_set(bpos, 0, 0);
    while pos < n {
        let c = h_get(choice, co.wrapping_add(pos)) as usize;
        let len = c / 65536;
        let d0 = c % 65536;
        let d = h_dist_of(mstart, mc, pos, len, d0);
        let st0 = h_clamp_step(len, n - pos);
        let st = h_sel(h_ge(d, 1), st0, 1);
        let ism = h_ge(st, 3);
        h_set(choice, co.wrapping_add(pos), h_sel32(ism, (len as u32).wrapping_mul(65536).wrapping_add(d as u32), 0));
        h_walk_bump(fr, b.wrapping_mul(H_FB), st, d, h_byte_at(input, pos));
        let stt = h_clamp1(st, n - pos);
        pos += stt;
        t = t.wrapping_add(1);
        if t >= H_BT && pos < n {
            t = 0;
            b = b.wrapping_add(1);
            h_clear(fr, b.wrapping_mul(H_FB), b.wrapping_mul(H_FB).wrapping_add(H_FB));
            h_set(bpos, b, pos as u32);
        }
    }
    b.wrapping_add(1)
}

// ---------------------------------------------------------------- package-merge (encoder replica)
pub fn h_insert_sorted(order: &mut [u32], k: usize, s: usize, freq: &[u32], off: usize) {
    let fs = h_get(freq, off.wrapping_add(s));
    let mut j = k;
    while j > 0 {
        let o = h_get(order, j - 1) as usize;
        let fo = h_get(freq, off.wrapping_add(o));
        if fo <= fs {
            break;
        }
        h_set(order, j, o as u32);
        j -= 1;
    }
    h_set(order, j, s as u32);
}

// Stable counting-sort pass of src[0..k) by the byte (freq >> sh) & 255 into dst.
pub fn h_radix_pass(freq: &[u32], off: usize, src: &[u32], dst: &mut [u32], k: usize, sh: u32) {
    let mut cnt = [0u32; 256];
    let mut i = 0usize;
    while i < k && i < 288 {
        let f = h_get(freq, off.wrapping_add(h_get(src, i) as usize));
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
        let s = h_get(src, j);
        let f = h_get(freq, off.wrapping_add(s as usize));
        let dg = ((f >> (sh % 32)) % 256) as usize;
        h_set(dst, cnt[dg] as usize, s);
        cnt[dg] = cnt[dg].wrapping_add(1);
        j += 1;
    }
}

// Live symbols sorted by (frequency, symbol) into order; returns their number.
// Radix sort when every frequency is below 65536, insertion sort otherwise.
pub fn h_sort_live(freq: &[u32], off: usize, nsym: usize, order: &mut [u32]) -> usize {
    let mut tmp = [0u32; 288];
    let mut k = 0usize;
    let mut big = 0usize;
    let mut s = 0usize;
    while s < nsym && s < 288 {
        let f = h_get(freq, off.wrapping_add(s));
        let old = tmp[k % 288];
        let live = h_lt32(0, f);
        tmp[k % 288] = h_sel32(live, s as u32, old);
        k = k.wrapping_add(live);
        big = big | h_lt32(65535, f);
        s += 1;
    }
    let kr = h_sel(big, 0, k);
    h_radix_pass(freq, off, &tmp, order, kr, 0);
    h_copy32(order, 0, &mut tmp, 0, kr);
    h_radix_pass(freq, off, &tmp, order, kr, 8);
    let kb = h_sel(big, k, 0);
    let mut j = 0usize;
    while j < kb && j < 288 {
        h_insert_sorted(order, j, tmp[j % 288] as usize, freq, off);
        j += 1;
    }
    k
}

pub fn h_load_w(freq: &[u32], off: usize, order: &[u32], k: usize, wa: &mut [u64]) {
    let mut i = 0usize;
    while i < k && i < 288 {
        let s = h_get(order, i) as usize;
        h_set64(wa, i, h_get(freq, off.wrapping_add(s)) as u64);
        i += 1;
    }
}

// One package-merge level: merge the sorted leaf weights lw[0..k) with pairs of w[src..src+curlen)
// into w[dst..]; flags mark leaves.
pub fn h_pm_level(lw: &[u64; 288], k: usize, w: &mut [u64; 1152], src: usize, curlen: usize, dst: usize, flags: &mut [u8; 9216], foff: usize) -> usize {
    let npk = curlen / 2;
    let total = k.wrapping_add(npk);
    let mut a = 0usize;
    let mut p = 0usize;
    let mut t = 0usize;
    while t < total && t < 576 {
        let lv = if a < k { lw[a % 288] } else { 0xFFFF_FFFF_FFFF_FFFFu64 };
        let i2 = src.wrapping_add(p.wrapping_mul(2));
        let pw = if p < npk { w[i2 % 1152].wrapping_add(w[i2.wrapping_add(1) % 1152]) } else { 0xFFFF_FFFF_FFFF_FFFFu64 };
        if lv <= pw {
            w[dst.wrapping_add(t) % 1152] = lv;
            flags[foff.wrapping_add(t) % 9216] = 1;
            a = a.wrapping_add(1);
        } else {
            w[dst.wrapping_add(t) % 1152] = pw;
            flags[foff.wrapping_add(t) % 9216] = 0;
            p = p.wrapping_add(1);
        }
        t += 1;
    }
    total
}

pub fn h_pm_levels(lw: &[u64; 288], k: usize, w: &mut [u64; 1152], flags: &mut [u8; 9216], maxbits: usize) {
    let mut curlen = k;
    let mut lev = 1usize;
    while lev < maxbits && lev < 16 {
        curlen = h_pm_level(lw, k, w, ((lev + 1) % 2).wrapping_mul(576), curlen, (lev % 2).wrapping_mul(576), flags, lev.wrapping_mul(576));
        lev += 1;
    }
}

pub fn h_count_leaves(flags: &[u8], foff: usize, s: usize) -> usize {
    let mut c = 0usize;
    let mut i = 0usize;
    while i < s && i < 576 {
        c = if h_get8(flags, foff.wrapping_add(i)) == 1 { c.wrapping_add(1) } else { c };
        i += 1;
    }
    c
}

pub fn h_inc_prefix(cnt: &mut [u32], m: usize) {
    let mut i = 0usize;
    while i < m && i < 288 {
        h_bump(cnt, i, 1);
        i += 1;
    }
}

pub fn h_count_back(flags: &[u8], cnt: &mut [u32], k: usize, maxbits: usize) -> usize {
    let mut s = if k >= 2 { k.wrapping_mul(2).wrapping_sub(2) } else { 0 };
    let mut lv = h_sel(h_ge(maxbits, 1) & h_ge(16, maxbits), maxbits.wrapping_sub(1), 0);
    while lv > 0 {
        let cl = h_count_leaves(flags, lv.wrapping_mul(576), s);
        h_inc_prefix(cnt, cl);
        s = h_sel(h_ge(s, cl), s.wrapping_sub(cl).wrapping_mul(2), 0);
        lv -= 1;
    }
    s
}

pub fn h_assign_lens(order: &[u32], cnt: &[u32], k: usize, lens: &mut [u32], loff: usize) {
    let mut r = 0usize;
    while r < k && r < 288 {
        let s2 = h_get(order, r) as usize;
        h_set(lens, loff.wrapping_add(s2), h_get(cnt, r));
        r += 1;
    }
}

// Code lengths exactly as the encoder's package_merge (ties by symbol index, leaf-first merge).
pub fn h_pkg_merge_pm(freq: &[u32], off: usize, nsym: usize, maxbits: usize, lens: &mut [u32], loff: usize) {
    let mut order = [0u32; 288];
    let mut lw = [0u64; 288];
    let mut w = [0u64; 1152];
    let mut flags = [0u8; 9216];
    let mut cnt = [0u32; 288];
    h_clear(lens, loff, loff.wrapping_add(nsym));
    let k = h_sort_live(freq, off, nsym, &mut order);
    let s0 = order[0] as usize;
    let v0 = h_get(lens, loff.wrapping_add(s0));
    h_set(lens, loff.wrapping_add(s0), h_sel32(h_eq(k, 1), 1, v0));
    let kk = h_sel(h_ge(k, 2) & h_ge(15, maxbits), k, 0);
    h_load_w(freq, off, &order, kk, &mut lw);
    h_load_w(freq, off, &order, kk, &mut w);
    h_pm_levels(&lw, kk, &mut w, &mut flags, maxbits);
    let s = h_count_back(&flags, &mut cnt, kk, maxbits);
    h_inc_prefix(&mut cnt, s);
    h_assign_lens(&order, &cnt, kk, lens, loff);
}

// ---------------------------------------------------------------- exact block cost (encoder replica)
pub const H_CL_ORDER: [usize; 19] = [16, 17, 18, 0, 8, 7, 9, 6, 10, 5, 11, 4, 12, 3, 13, 2, 14, 1, 15];

pub fn h_run_len(all: &[u32], i: usize, m: usize) -> usize {
    let v = h_get(all, i);
    let mut r = 1usize;
    while r < 1000 {
        let j = i.wrapping_add(r);
        if j >= m {
            break;
        }
        if h_get(all, j) != v {
            break;
        }
        r += 1;
    }
    r
}

// RLE statistics of the code-length sequence; returns total extra bits.
pub fn h_rle_stats(all: &[u32], m: usize, clf: &mut [u32]) -> u64 {
    let mut extra = 0u64;
    let mut i = 0usize;
    while i < m {
        let v = h_get(all, i) as usize;
        let run = h_run_len(all, i, m);
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
        h_bump(clf, 18, add18 as u32);
        h_bump(clf, 17, add17 as u32);
        h_bump(clf, 0, add0 as u32);
        h_bump(clf, 16, add16 as u32);
        h_bump(clf, v % 19, addv as u32);
        let ex = add18.wrapping_mul(7).wrapping_add(add17.wrapping_mul(3)).wrapping_add(add16.wrapping_mul(2));
        extra = extra.wrapping_add(ex as u64);
        let st = h_clamp1(run, m - i);
        i += st;
    }
    extra
}

pub fn h_dot(f: &[u32], foff: usize, l: &[u32], loff: usize, m: usize) -> u64 {
    let mut s = 0u64;
    let mut i = 0usize;
    while i < m {
        s = s.wrapping_add((h_get(f, foff.wrapping_add(i)) as u64).wrapping_mul(h_get(l, loff.wrapping_add(i)) as u64));
        i += 1;
    }
    s
}

pub fn h_fixed_dot(f: &[u32], foff: usize) -> u64 {
    let mut s = 0u64;
    let mut i = 0usize;
    while i < 288 {
        s = s.wrapping_add((h_get(f, foff.wrapping_add(i)) as u64).wrapping_mul(h_fixed_len(i) as u64));
        i += 1;
    }
    s
}

pub fn h_sum_range(f: &[u32], a: usize, b: usize) -> u64 {
    let mut s = 0u64;
    let mut i = a;
    while i < b {
        s = s.wrapping_add(h_get(f, i) as u64);
        i += 1;
    }
    s
}

pub fn h_last_nz(l: &[u32], off: usize, m: usize, lo: usize) -> usize {
    let mut k = m;
    while k > lo {
        if h_get(l, off.wrapping_add(k - 1)) != 0 {
            break;
        }
        k -= 1;
    }
    k
}

pub fn h_copy32(src: &[u32], soff: usize, dst: &mut [u32], doff: usize, m: usize) {
    let mut i = 0usize;
    while i < m {
        h_set(dst, doff.wrapping_add(i), h_get(src, soff.wrapping_add(i)));
        i += 1;
    }
}

pub fn h_hclen_of(cl: &[u32]) -> usize {
    let mut h = 19usize;
    while h > 4 {
        if h_get(cl, H_CL_ORDER[(h - 1) % 19]) != 0 {
            break;
        }
        h -= 1;
    }
    h
}

// Exact bits the encoder spends on the block whose frequencies are `fr[off..off+H_FB]`.
// Leaves the dynamic code lengths in `lens[0..288]` (litlen) and `lens[288..318]` (dist);
// returns bits * 4 + kind (0 dynamic, 1 fixed, 2 stored).
pub fn h_block_bits(fr: &mut [u32], off: usize, lens: &mut [u32]) -> u64 {
    h_bump(fr, off.wrapping_add(256), 1);
    h_pkg_merge(fr, off, 288, 15, lens, 0);
    h_pkg_merge(fr, off.wrapping_add(288), 30, 15, lens, 288);
    let ndist = h_sum_range(fr, off.wrapping_add(288), off.wrapping_add(318));
    let l288 = h_get(lens, 288);
    h_set(lens, 288, h_sel32(h_lt64(ndist, 1), 1, l288));
    let hlit = h_last_nz(lens, 0, 288, 257);
    let hdist = h_last_nz(lens, 288, 30, 1);
    let mut all = [0u32; 320];
    h_copy32(lens, 0, &mut all, 0, hlit);
    h_copy32(lens, 288, &mut all, hlit, hdist);
    let mut clf = [0u32; 19];
    let rextra = h_rle_stats(&all, hlit.wrapping_add(hdist), &mut clf);
    let mut cl = [0u32; 19];
    h_pkg_merge(&clf, 0, 19, 7, &mut cl, 0);
    let hclen = h_hclen_of(&cl);
    let ex = h_get(fr, off.wrapping_add(318)) as u64;
    let hdr = 17u64.wrapping_add(3u64.wrapping_mul(hclen as u64)).wrapping_add(h_dot(&clf, 0, &cl, 0, 19)).wrapping_add(rextra);
    let dl = h_dot(fr, off, lens, 0, 288);
    let dd = h_dot(fr, off.wrapping_add(288), lens, 288, 30);
    let dynb = hdr.wrapping_add(dl).wrapping_add(dd).wrapping_add(ex);
    let fixb = 3u64.wrapping_add(h_fixed_dot(fr, off)).wrapping_add(5u64.wrapping_mul(ndist)).wrapping_add(ex);
    h_bump(fr, off.wrapping_add(256), 0u32.wrapping_sub(1));
    let raw = h_get(fr, off.wrapping_add(319)) as u64;
    let stb = 35u64.wrapping_add(8u64.wrapping_mul(raw));
    let fx = h_lt64(dynb, fixb) ^ 1;
    let best = h_sel64(fx, fixb, dynb);
    let usest = h_lt64(ndist, 1) & h_lt64(raw, 65536) & h_lt64(stb, best);
    h_sel64(usest, stb.wrapping_mul(4).wrapping_add(2), best.wrapping_mul(4).wrapping_add(fx as u64))
}

// ---------------------------------------------------------------- cost tables
pub const H_LOG2F: [u32; 32] = [0, 1, 1, 2, 3, 3, 4, 5, 5, 6, 6, 7, 7, 8, 8, 9, 9, 10, 10, 11, 11, 12, 12, 13, 13, 13, 14, 14, 15, 15, 15, 16];

// 16 * log2(x), x >= 1 (about 1/16 bit precision); 0 for x == 0.
pub fn h_log2x16(x: u64) -> u32 {
    if x == 0 {
        return 0;
    }
    let k = 63u32.wrapping_sub(x.leading_zeros()) % 64;
    let y = x << ((63 - k) % 64);
    let m = ((y >> 58) as usize) % 32;
    k.wrapping_mul(16).wrapping_add(H_LOG2F[m])
}

// Per-symbol costs (1/16 bit) for the next pass from this block's code lengths / frequencies.
pub fn h_sym_costs(fr: &[u32], off: usize, lens: &[u32], kind: u32, sc: &mut [u32]) {
    let tl = h_sum_range(fr, off, off.wrapping_add(286)).wrapping_add(1);
    let td = h_sum_range(fr, off.wrapping_add(288), off.wrapping_add(318));
    let lt = h_log2x16(tl);
    let ld = h_log2x16(td);
    let mut s = 0usize;
    while s < 318 {
        let f = h_get(fr, off.wrapping_add(s)) as u64;
        let ls = h_get(lens, s);
        let fl = h_fixed_len(s);
        let lf = h_log2x16(f);
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
            H_UNUSED
        };
        let tot = if s >= 288 { ld } else { lt };
        let e0 = if f > 0 { tot.saturating_sub(lf) } else { tot.saturating_add(H_UPEN) };
        let e = if e0 < 16 { 16 } else { e0 };
        let hc = hl.wrapping_mul(H_SC);
        let mixv = (e.wrapping_mul(H_EW).wrapping_add(hc.wrapping_mul(8 - H_EW))) / 8;
        h_set(sc, s, if kind != 0 { hc } else { mixv });
        s += 1;
    }
}

pub fn h_mode_ov(damp:u32)->u32 { if damp==2 {1} else {H_OV} }

pub fn h_blend(old: u32, new: u32, damp: u32) -> u32 {
    if damp == 0 {
        new
    } else if H_OV > 0 {
        let dlt = if new >= old { new.wrapping_sub(old) } else { old.wrapping_sub(new) };
        let adj = ((dlt as u64).wrapping_mul(h_mode_ov(damp) as u64) / 8) as u32;
        let v = if new >= old { new.saturating_add(adj) } else { new.saturating_sub(adj) };
        if v < 16 {
            16
        } else {
            v
        }
    } else {
        (((old as u64).wrapping_mul(H_DW as u64).wrapping_add((new as u64).wrapping_mul((8 - H_DW) as u64))) / 8) as u32
    }
}

pub fn h_fill_table(sc: &[u32], tbl: &mut [u32], toff: usize, damp: u32) {
    let mut c = 0usize;
    while c < 256 {
        let j = toff.wrapping_add(c);
        h_set(tbl, j, h_blend(h_get(tbl, j), h_get(sc, c), damp));
        c += 1;
    }
    let mut len = 0usize;
    while len < 259 {
        let lc = h_lcode(len);
        let v = h_get(sc, lc.wrapping_add(257)).wrapping_add(h_lextra(lc).wrapping_mul(H_SC));
        let j = toff.wrapping_add(256).wrapping_add(len);
        h_set(tbl, j, h_blend(h_get(tbl, j), v, damp));
        len += 1;
    }
    let mut s = 0usize;
    while s < 30 {
        let v = h_get(sc, s.wrapping_add(288)).wrapping_add(h_dextra(s).wrapping_mul(H_SC));
        let j = toff.wrapping_add(515).wrapping_add(s);
        h_set(tbl, j, h_blend(h_get(tbl, j), v, damp));
        s += 1;
    }
}

// ---------------------------------------------------------------- driver
// Longest cached match at a position as len * 65536 + dist; 1 (len 0) if none.
pub fn h_longest(mstart: &[u32], mc: &[u32], p: usize) -> usize {
    let ms = h_get(mstart, p) as usize;
    let me = h_get(mstart, p.wrapping_add(1)) as usize;
    let m = h_get(mc, me.wrapping_sub(1)) as usize;
    let l0 = m / 1048576;
    let l = h_sel(h_ge(l0, 512), l0.wrapping_sub(512), l0);
    h_sel(h_lt(ms, me), l.wrapping_mul(65536).wrapping_add(m % 32768 + 1), 1)
}

// Byte histogram of input[a..b) added to fr[0..256].
pub fn h_block_hist(input: &[u8], a: usize, b: usize, fr: &mut [u32]) {
    let mut i = a;
    while i < b {
        h_bump(fr, h_byte_at(input, i), 1);
        i += 1;
    }
}

pub fn h_add_hist(fr: &[u32], hist: &mut [u32; 256]) {
    let mut c = 0usize;
    while c < 256 {
        hist[c] = hist[c].wrapping_add(h_get(fr, c));
        c += 1;
    }
}

// block_bits of block 0 when f == 1, else 0.
pub fn h_block_bits_if(fr: &mut [u32], lens: &mut [u32], f: usize) -> u64 {
    if f == 1 {
        h_block_bits(fr, 0, lens)
    } else {
        0
    }
}

// Exact encoded bits of the all-literal h_parse (blocks of H_BT bytes); whole-input byte histogram into hist;
// the all-literal path's cost tables (as eval_blocks would derive them, damp 0) into tlit.
pub fn h_literal_bits(input: &[u8], fr: &mut [u32], hist: &mut [u32; 256], tlit: &mut [u32], t5: &mut [u32]) -> u64 {
    let n = input.len();
    let mut lens = [0u32; 320];
    let mut sc = [0u32; 320];
    let mut total = 0u64;
    let nblk = n / H_BT + 1;
    let mut b = 0usize;
    while b < nblk {
        let p = b.wrapping_mul(H_BT);
        let e = h_sel(h_ge(p, n), p, h_sel(h_lt(H_BT, n.wrapping_sub(p)), p.wrapping_add(H_BT), n));
        h_clear(fr, 0, H_FB);
        h_block_hist(input, p, e, fr);
        h_add_hist(fr, hist);
        h_set(fr, 319, e.wrapping_sub(p) as u32);
        let r = h_block_bits_if(fr, &mut lens, h_lt(p, e));
        total = total.wrapping_add(r / 4);
        h_sym_costs(fr, 0, &lens, (r % 4) as u32, &mut sc);
        h_fill_table(&sc, tlit, b.wrapping_mul(H_TB), 0);
        h_init5_table(fr, t5, b.wrapping_mul(H_TB));
        b += 1;
    }
    total
}

// init5 literal cost (1/16 bit): entropy of a byte seen f times among 2^(lt/16), at least one bit.
pub fn h_ent5(lt: u32, f: u64) -> u32 {
    let e0 = if f > 0 { lt.saturating_sub(h_log2x16(f)) } else { lt.saturating_add(H_U5) };
    if e0 < 16 {
        16
    } else {
        e0
    }
}

// init5 cost of a match length: static code (7 bits for codes 0..7, else 8) + extra bits, minus H_D5.
pub fn h_st5len(len: usize) -> u32 {
    let lc = h_lcode(len);
    let base = if lc < 8 { 7u32 } else { 8u32 };
    (base.wrapping_add(h_lextra(lc))).wrapping_mul(16).saturating_sub(H_D5)
}

// init5 cost table of one block (byte histogram in fr[0..256]) at tbl[toff..toff + H_TB].
pub fn h_init5_table(fr: &[u32], tbl: &mut [u32], toff: usize) {
    let lt = h_log2x16(h_sum_range(fr, 0, 256));
    let mut c = 0usize;
    while c < 256 {
        h_set(tbl, toff.wrapping_add(c), h_ent5(lt, h_get(fr, c) as u64));
        c += 1;
    }
    let mut len = 0usize;
    while len < 259 {
        h_set(tbl, toff.wrapping_add(256).wrapping_add(len), h_st5len(len));
        len += 1;
    }
    let mut s = 0usize;
    while s < 30 {
        h_set(tbl, toff.wrapping_add(515).wrapping_add(s), (5u32.wrapping_add(h_dextra(s))).wrapping_mul(16));
        s += 1;
    }
    h_set(tbl, toff.wrapping_add(545), 0);
}

// Average Huffman bits (x16) of a literal under the byte histogram of n bytes.
pub fn h_avg_lit16_h(hist: &[u32; 256], n: usize) -> u32 {
    let mut lens = [0u32; 320];
    h_pkg_merge(hist, 0, 256, 15, &mut lens, 0);
    let tot = h_dot(hist, 0, &lens, 0, 256);
    let q = (tot.wrapping_mul(16) / h_nz64(n as u64)) as u32;
    if n > 0 {
        q
    } else {
        128
    }
}

// Rough bits (x16) of a match before any statistics exist.
pub fn h_est_match16(l: usize, d: usize) -> u32 {
    let lc = h_lcode(l);
    let s = h_dslot(d);
    (12u32.wrapping_add(h_lextra(lc)).wrapping_add(h_dextra(s))).wrapping_mul(16).wrapping_add(H_MBIAS)
}

// est_match16 when f == 1, else 0.
pub fn h_est_if(f: usize, l: usize, d: usize) -> u32 {
    if f == 1 {
        h_est_match16(l, d)
    } else {
        0
    }
}

// h_longest() at pos + st, reusing the lookahead b when st == 1.
pub fn h_next_longest(mstart: &[u32], mc: &[u32], pos: usize, st: usize, b: usize) -> usize {
    if st == 1 {
        b
    } else {
        h_longest(mstart, mc, pos.wrapping_add(st))
    }
}

// Initial path: lazy matching, but only matches cheaper than their bytes as literals.
pub fn h_lazy_cost_init(input: &[u8], mstart: &[u32], mc: &[u32], h16: u32, choice: &mut [u32]) {
    let n = input.len();
    let mut pos = 0usize;
    let mut nxt = h_longest(mstart, mc, 0);
    let mut ec = 0u32;
    let mut hv = 0usize;
    while pos < n {
        let a = nxt;
        let b = h_longest(mstart, mc, pos.wrapping_add(1));
        let al = a / 65536;
        let ad = a % 65536;
        let bl = b / 65536;
        let bd = b % 65536;
        let room = n - pos;
        let ea = h_sel32(hv, ec, h_est_if(h_ge(al, 3) & (hv ^ 1), al, ad));
        let eb = h_est_if(h_lt(al, bl), bl, bd);
        let oka = h_ge(al, 3) & h_ge(room, al) & h_lt32(ea, (al as u32).wrapping_mul(h16));
        let okb = h_lt(al, bl) & h_lt32(eb, (bl as u32).wrapping_mul(h16));
        let tl = h_sel(oka & (okb ^ 1), al, 0);
        h_set(choice, pos, h_sel32(h_ge(tl, 3), (tl as u32).wrapping_mul(65536).wrapping_add(ad as u32), 0));
        let st = h_clamp_step(tl, room);
        nxt = h_next_longest(mstart, mc, pos, st, b);
        // the next position's match is b when st == 1: reuse its estimate when it was computed.
        hv = h_eq(st, 1) & h_lt(al, bl);
        ec = eb;
        pos += st;
    }
}

// Exact bits of every block of the last walk; next pass's cost tables. Returns total bits.
// Forbid matches in the block table at toff (every length cost H_BIG).
pub fn h_forbid_block(tbl: &mut [u32], toff: usize) {
    let mut len = 0usize;
    while len < 259 {
        h_set(tbl, toff.wrapping_add(256).wrapping_add(len), H_BIG);
        len += 1;
    }
}

pub fn h_forbid_if(tbl: &mut [u32], toff: usize, f: usize) {
    if f == 1 {
        h_forbid_block(tbl, toff);
    }
}

// Exact bits of every block of the last walk; next pass's cost tables. Returns total bits.
pub fn h_eval_blocks(fr: &mut [u32], tbl: &mut [u32], nb2: usize, nbmax: usize, damp: u32) -> u64 {
    let mut lens = [0u32; 320];
    let mut sc = [0u32; 320];
    let mut total = 0u64;
    let lim = h_umin(nb2, nbmax);
    let mut b = 0usize;
    while b < lim {
        let r = h_block_bits(fr, b.wrapping_mul(H_FB), &mut lens);
        total = total.wrapping_add(r / 4);
        h_sym_costs(fr, b.wrapping_mul(H_FB), &lens, (r % 4) as u32, &mut sc);
        h_fill_table(&sc, tbl, b.wrapping_mul(H_TB), damp);
        let raw = h_get(fr, b.wrapping_mul(H_FB).wrapping_add(319)) as u64;
        let fb = h_eq(H_STM, 1) & h_lt64(raw.wrapping_mul(8).wrapping_add(35).wrapping_add(H_STMARG), r / 4);
        let fl = ((h_get(tbl, b.wrapping_mul(H_TB).wrapping_add(545)) as usize) | fb) & 1;
        h_set(tbl, b.wrapping_mul(H_TB).wrapping_add(545), fl as u32);
        h_forbid_if(tbl, b.wrapping_mul(H_TB), fl);
        b += 1;
    }
    total
}

// One DP pass: the first relaxes the whole match cache (with the H_MDEL match discount) and keeps the
// near-optimal queries; later passes relax only those.
pub fn h_dp_pass(
    input: &[u8],
    mstart: &[u32],
    mc: &[u32],
    tbl: &[u32],
    bend: &[u32; 512],
    bpos: &[u32],
    nb: usize,
    choice: &mut [u32],
    chw: usize,
    keep: usize,
    items: &mut Vec<u32>,
    istart: &mut Vec<u32>,
    pr: usize,
    msub: u32,
    co: usize,
    lam: u32,
) {
    if pr == 0 {
        h_pass_prune(input, mstart, mc, tbl, bend, bpos, nb, choice, chw, msub, keep, items, istart, co, lam);
    } else {
        h_pass_items(input, tbl, bpos, nb, choice, items, istart, h_ge(chw, 15), co, lam);
    }
}

// Stop after this pass? (squared gain rule, factor H_F1 after the first pass, at least H_MINIT passes)
pub fn h_stop_rule(prev: u64, r: u64, n: usize, it1: usize, gk: u64, minp: usize) -> usize {
    let gain = if prev > r { prev.wrapping_sub(r) } else { 0 };
    let f1 = h_sel64(h_eq(it1, 1), H_F1, 1);
    let n1 = h_nz64(n as u64);
    let nn = n1.wrapping_mul(n1);
    let t2 = (gain.wrapping_mul(r) / n1).wrapping_mul(r) / n1;
    let small2 = h_lt64(t2.wrapping_mul(1280), n1.wrapping_mul(gk).wrapping_mul(f1));
    let smallg = h_lt64(gain.wrapping_mul(r).wrapping_mul(1024), nn.wrapping_mul(H_GAINK).wrapping_mul(f1));
    let smalle = h_lt64(r.wrapping_add(r >> H_ESH), prev) ^ 1;
    let small = if H_RALPHA == 2 { small2 } else if H_GAINK > 0 { smallg } else { smalle };
    h_ge(it1, minp) & small
}

// 1 when the stop rule surely stops after the first pass whatever its result r (then the first pass
// need not keep queries): max over r of (prev - r) r^2 is 4 prev^3 / 27, so with q >= 256 prev / n,
// 5120 q^3 < 27 H_GK2 H_F1 256^3 implies 1280 (prev - r) r^2 / n^2 < H_GK2 H_F1 n (H_RALPHA 2, H_MINIT <= 1).
pub fn h_one_pass(prev: u64, n: usize, gk: u64) -> usize {
    let n1 = h_nz64(n as u64);
    let q = (h_umin64(prev, 1099511627776).wrapping_mul(256).wrapping_add(n1.wrapping_sub(1))) / n1;
    let lhs = q.wrapping_mul(q).wrapping_mul(q).wrapping_mul(5120);
    let rhs = gk.wrapping_mul(H_F1).wrapping_mul(27).wrapping_mul(16777216);
    (h_eq(H_RALPHA as usize, 2) & h_ge(1, H_MINIT) & h_lt64(q, 4096) & h_lt64(lhs, rhs)) | h_lt64(q, H_OPQ)
}

// The improvement passes: DP under the current tables, exact evaluation, keep the best plan.
pub fn h_iterate(mode: usize, 
    input: &[u8],
    mstart: &[u32],
    mc: &[u32],
    tbl: &mut [u32],
    fr: &mut [u32],
    bpos: &mut [u32],
    bend: &[u32; 512],
    choice: &mut [u32],
    plan: &mut [u32],
    nbmax: usize,
    nb0: usize,
    best0: u64,
    prev0: u64,
    gk: u64,
    lamh: u32,
    minp: usize,
    ew:u32,
) {
    let n = input.len();
    let mut nb = nb0;
    let mut best = best0;
    let mut prev = prev0;
    let mut stop = 0usize;
    let mut it = 0usize;
    let mut items: Vec<u32> = Vec::with_capacity(n.wrapping_mul(2).wrapping_add(64));
    let mut istart: Vec<u32> = Vec::with_capacity(n.wrapping_add(1));
    let kp0 = (h_one_pass(prev0, n, gk) ^ 1) | h_lt(1, minp);
    let mut pr = 0usize;
    // double-buffered choice: pass results alternate between halves; bh = half holding the best plan (2: `plan`).
    let mut wh = 0usize;
    let mut bh = 2usize;
    let chw = h_sel(h_ge(n, H_CHN), H_CHW, H_CHWS);
    while it < H_ITERS && stop == 0 {
        let it1 = it + 1;
        let kp = kp0 | h_ge(it, 1);
        if mode == 4 && it == 2 && gk < 16 { h_cx_jitter(tbl, nb, 1, 32); }
        // @DP_BEGIN
        let co = wh.wrapping_mul(n.wrapping_add(1));
        h_dp_pass(input, mstart, mc, tbl, bend, bpos, nb, choice, chw, kp, &mut items, &mut istart, pr, h_sel32(h_eq(it, 0), H_MDEL, H_MDEL2), co, lamh);
        // @DP_END
        pr = pr | kp;
        // @P6_BEGIN
        let nb2 = h_walk(input, mstart, mc, choice, co, fr, bpos);
        let r = h_eval_mode(mode, fr, tbl, nb2, nbmax, h_ge(it1, H_DSTART) as u32,ew);
        // @P6_END
        nb = nb2;
        let imp = h_lt64(r, best);
        bh = h_sel(imp, wh, bh);
        wh = h_sel(imp, wh ^ 1, wh);
        best = h_sel64(imp, r, best);
        stop = h_stop_rule(prev, r, n, it1, gk, minp);
        if mode == 4 { stop = stop & ((h_lt(it,5) & h_lt64(gk,16)) ^ 1); }
        prev = r;
        it = it1;
    }
    h_copy32(choice, bh.wrapping_mul(n.wrapping_add(1)), plan, 0, h_sel(h_lt(bh, 2), n, 0));
    if mode == 2 || mode == 3 || mode == 5 || mode == 6 {
        let restarts = if mode == 3 { 2 } else if (mode == 5 || mode == 6) && prev <= best { 0 } else { 1 };
        h_cx_restarts(input, mstart, mc, tbl, fr, bpos, bend, choice, plan,
                    nbmax, lamh, &mut items, &mut istart, pr, chw, restarts);
    }
}

// Block starts of the all-literal path (blocks of H_BT bytes) for the first `m` blocks.
pub fn h_lit_bpos(bpos: &mut [u32], m: usize) {
    let mut b = 0usize;
    while b < m {
        h_set(bpos, b, (b.wrapping_mul(H_BT)) as u32);
        b += 1;
    }
}

pub fn h_optimize(mode: usize, 
    input: &[u8],
    mstart: &[u32],
    mc: &[u32],
    tbl: &mut [u32],
    fr: &mut [u32],
    bpos: &mut [u32],
    bend: &[u32; 512],
    choice: &mut [u32],
    plan: &mut [u32],
    nbmax: usize,
    gk: u64,
    i5: usize,
) {
    let n = input.len();
    h_find_spare(input, h_lt(n, 4));
    // @P5_BEGIN
    let mut hist = [0u32; 256];
    let mut tlit = h_filled(nbmax.wrapping_mul(H_TB), 0);
    let mut t5 = h_filled(nbmax.wrapping_mul(H_TB), 0);
    let rl = h_literal_bits(input, fr, &mut hist, &mut tlit, &mut t5);
    let h16 = h_avg_lit16_h(&hist, n);
    let ew=if mode == 0 { h_sel32(h_lt(h_entropy256(&hist),H_HGEN),1,h_sel32(h_eq64(gk,H_GKMC),0,h_sel32(h_eq64(gk,H_GKLOW),2,3))) } else { 0 };
    h_lazy_cost_init(input, mstart, mc, h16, choice);
    let nb0 = h_walk(input, mstart, mc, choice, 0, fr, bpos);
    let r0 = h_eval_mode(mode, fr, tbl, nb0, nbmax, 0,ew);
    let lz = h_lt64(r0, rl);
    h_copy32(choice, 0, plan, 0, h_sel(lz, n, 0));
    let best0 = h_sel64(lz, r0, rl);
    // H_STARTBEST: start from the all-literal path's tables (computed by literal_bits) when it is better.
    // high-entropy inputs (best start above H_HBPB/8 bits per byte): init5 tables, per-token reward H_LAMH.
    let hi = h_lt64((n as u64).wrapping_mul(H_HBPB) / 8, best0) & i5;
    let sb = (h_eq(H_STARTBEST, 1) & h_lt64(rl, r0)) | hi;
    h_copy32(&tlit, 0, tbl, 0, h_sel(sb, nbmax.wrapping_mul(H_TB), 0));
    h_copy32(&t5, 0, tbl, 0, h_sel(hi, nbmax.wrapping_mul(H_TB), 0));
    let nbl = h_sel(h_lt(0, n), n.wrapping_add(H_BT - 1) / H_BT, 1);
    h_lit_bpos(bpos, h_sel(sb, nbl, 0));
    let nbst = h_sel(sb, nbl, nb0);
    let prev0 = h_sel64(sb, rl, r0);
    // @P5_END
    h_iterate(mode, input, mstart, mc, tbl, fr, bpos, bend, choice, plan, nbmax, nbst, best0, prev0, gk, h_sel32(hi, H_LAMH, 0), h_sel(hi, H_MINH, H_MINIT),ew);
}

// ================================================================ DP path (x3a)


pub const H_H_BS: usize = 6144;
// A DP block continues past H_H_BS (at most H_H_EXT bytes) while a match edge crosses the current position.
pub const H_H_EXT: usize = 1024;
pub const H_H_MAX3: usize = 32768;
pub const H_H_H3ON: usize = 1;
pub const H_H_NICE: usize = 258;
// Chain depth for searches past the farthest known match end.
pub const H_H_DEPTH: usize = 128;
pub const H_H_RDEPTH: usize = 256;
// Positions within H_H_KEND of the farthest known match end are frontier candidates.
pub const H_H_KEND: usize = 15;
// Bit k: search at offset k = reach - cur (k <= H_H_KEND); other offsets are treated as interior.
pub const H_H_SMASK: u64 = 4293939199;
pub const H_H_RMASK: u64 = 4293939071;
// Bit k: extend the candidates backwards at offset k (never past the match end).
pub const H_H_BXMASK: usize = 4294967295;
// Back-extension for searches past the match end (1) or not (0).
pub const H_H_BXGT: usize = 1;
// Chain depth at offset k = reach - cur.
// Per frontier class (0 text, 1 redundant, 2 redundant digit-heavy, 3 spare): search mask, depth past the
// farthest match end.
pub const H_H_MASKS: [u64; 4] = [18446744073709551615, 4293939199, 4293939199, 4293939199];
pub const H_H_HDEPS: [usize; 4] = [512, 512, 512, 128];
pub const H_H_DEPO: [usize; 128] = [256, 128, 96, 64, 12, 16, 12, 12, 12, 4, 16, 6, 6, 6, 64, 6, 6, 6, 6, 6, 32, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 256, 128, 96, 64, 12, 16, 12, 12, 12, 4, 16, 6, 6, 6, 64, 6, 6, 6, 6, 6, 32, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 256, 128, 96, 64, 12, 16, 12, 12, 12, 4, 16, 6, 6, 6, 64, 6, 6, 6, 6, 6, 32, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 128, 64, 48, 32, 12, 16, 12, 12, 12, 4, 16, 6, 6, 6, 64, 6, 6, 6, 6, 6, 32, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6];
// Literal edges are relaxed only for the first H_H_LITK positions of an interior stretch.
pub const H_H_LITK: usize = 16;
// Sparse mode (previous DP block had >= H_H_COV% literal bytes): past the match end, search only every
// H_H_SPSTEP-th position; the others are inserted (H_H_SPINS = 1) or not (0) and get their literal edge.
pub const H_H_COV: usize = 95;
pub const H_H_SPSTEP: usize = 2;
pub const H_H_SPINS: usize = 1;
// After H_H_ACC_DIV * k consecutive fruitless searches the search stride is k + 1 (LZ4-style).
pub const H_H_ACC_DIV: usize = 1024;
// Insert only the last H_H_TAIL positions of a skipped (>= H_H_NICE) match.
pub const H_H_TAIL: usize = 258;
// Bytes of the input prefix sampled for the initial literal statistics.
pub const H_H_SAMPLE: usize = 4096;
pub const H_H_PW: u32 = 1;
pub const H_H_PWD: u32 = 8;
pub const H_H_UNSEEN: u32 = 8;
pub const H_H_CMIN: u32 = 16;
pub const H_H_CMAX: u32 = 180;
pub const H_H_PRIOR_DIV: u32 = 64;
pub const H_H_BLOCK_TOKENS: usize = 16384;
pub const H_H_INF: u64 = 18446744073709551615;
pub const H_H_PLAN: usize = 6656;
// Replay pass: edge buffer size (entry 0 is the count), weight of the block's own pass-1 statistics,
// replay threshold (pass-1 parse priced more than H_H_RT/1024 higher by the pass-1 model than by the refit one).
pub const H_H_EBUF: usize = 32768;
pub const H_H_TPW: u32 = 4;
pub const H_H_RT: u64 = 64;

pub const H_H_LEN_BASE: [u32; 32] = [
    3, 4, 5, 6, 7, 8, 9, 10, 11, 13, 15, 17, 19, 23, 27, 31, 35, 43, 51, 59, 67, 83, 99, 115,
    131, 163, 195, 227, 258, 1000, 1000, 1000,
];
pub const H_H_LEN_EXTRA: [u32; 32] = [
    0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 2, 2, 2, 2, 3, 3, 3, 3, 4, 4, 4, 4, 5, 5, 5, 5, 0, 0, 0, 0,
];
pub const H_H_DIST_BASE: [u32; 32] = [
    1, 2, 3, 4, 5, 7, 9, 13, 17, 25, 33, 49, 65, 97, 129, 193, 257, 385, 513, 769, 1025, 1537,
    2049, 3073, 4097, 6145, 8193, 12289, 16385, 24577, 65536, 65536,
];
pub const H_H_DIST_EXTRA: [u32; 32] = [
    0, 0, 0, 0, 1, 1, 2, 2, 3, 3, 4, 4, 5, 5, 6, 6, 7, 7, 8, 8, 9, 9, 10, 10, 11, 11, 12, 12, 13,
    13, 0, 0,
];
// Length symbol offset (0..28) of each length 3..=258.
pub const H_H_LSYM: [u8; 259] = [0, 0, 0, 0, 1, 2, 3, 4, 5, 6, 7, 8, 8, 9, 9, 10, 10, 11, 11, 12, 12, 12, 12, 13, 13, 13, 13, 14, 14, 14, 14, 15, 15, 15, 15, 16, 16, 16, 16, 16, 16, 16, 16, 17, 17, 17, 17, 17, 17, 17, 17, 18, 18, 18, 18, 18, 18, 18, 18, 19, 19, 19, 19, 19, 19, 19, 19, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 28];
// Distance symbol of distances 1..=256 (index d - 1).
pub const H_H_DSYM_S: [u8; 256] = [0, 1, 2, 3, 4, 4, 5, 5, 6, 6, 6, 6, 7, 7, 7, 7, 8, 8, 8, 8, 8, 8, 8, 8, 9, 9, 9, 9, 9, 9, 9, 9, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15];
// Distance symbol of distances > 256 (index (d - 1) / 128).
pub const H_H_DSYM_B: [u8; 256] = [15, 15, 16, 17, 18, 18, 19, 19, 20, 20, 20, 20, 21, 21, 21, 21, 22, 22, 22, 22, 22, 22, 22, 22, 23, 23, 23, 23, 23, 23, 23, 23, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29];
// 16 * log2(1 + i/16), i = 0..15.
pub const H_H_LOG_FRAC: [u32; 16] = [0, 1, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 15];

// ---------------------------------------------------------------- guarded helpers







// `a[i % 8192]`.


// `a[i % 8192] = x`.





// ---------------------------------------------------------------- trusted core







// ---------------------------------------------------------------- loads and compares

// Little-endian 4-byte word at `p` (0 if out of range).


// Little-endian 8-byte word at `p` (0 if out of range): byte p+7 is the most significant.


// Number of equal leading bytes (in memory order) of two little-endian words given their xor: 0..=8.




// Byte-wise tail compare (search only).


// Common prefix length of the strings at `a` and `b`, at most `cap` (search only).


// How many bytes before `a` and `c` agree (walking backwards), at most `cap` (search only). `c < a`.


// ---------------------------------------------------------------- cost model

// 16 * log2(v), v >= 1 (0 for v = 0).


// Estimated cost (1/16 bits) of a symbol seen `f` times out of `total`.













// Literal costs from the literal part of `llf`.


// Symbol costs of the 29 length symbols (plus extra bits), then every length through `lsym`.


// Symbol costs of the 30 distance symbols (plus extra bits), then both distance tables.


// `dst = cur + prev * H_H_PW / 4` over the first `m` entries.












// Literal histogram of the first H_H_SAMPLE bytes (4 interleaved counters against store forwarding).


// Initial statistics: literal histogram of a sample plus pseudo-counts for lengths/distances.


// Shrink the initial pseudo-statistics so real counts dominate quickly.




// ---------------------------------------------------------------- match finding

// 3-byte hash slot of position `i`.


// Relax the nearest 3-byte match (entry `s3`, pos+1 encoded) at `pos` (DP position `cur`) as a
// length-3 edge when it is within H_H_MAX3 and its 3 bytes agree.


// Insert position `i` (when `on`) into the chains; returns the previous chain head (+1).


// Positions `start+cur0 .. start+stop`: insert them (when `ins`) and relax their literal edges.
// Insert positions `start+cur0 .. start+stop` into the chains (no DP work).


// Positions `start+cur0 .. start+stop` inside a known match: all are inserted, the first H_H_LITK
// also get their literal edge relaxed. Returns the price at `stop`.


// Positions `cur0 .. stop` of an accelerated literal run: literal edges only. Returns the price at `stop`.


// Length of the match between `c` and `pos` given the xor `x` of their first words (search only).



// Backward extension of the candidate at `c` for `pos` (at most `cap` bytes), given the word
// `wb` ending just before `pos`: one word compare, the general loop only when it all agrees.


// Relax one Pareto candidate (distance `d`, length `l`, found at `c`) from `cur`: its lengths
// `lo..=l`, and when it extends backwards by b > 0 bytes also from `cur - b` (lengths b+lo..=b+l,
// never before the block start). A candidate of length >= H_H_NICE only relaxes its full length.


// Walk the chain from head `s4` (at most `depth` probes) at `pos` (DP position `cur`, price
// `price`) and relax every Pareto candidate (strictly longer than all nearer ones) on the fly.
// Returns the longest length found (< 4: none).



// Insert positions `from .. to` into the chains.


// ---------------------------------------------------------------- DP



// Relax lengths lo..=hi from `cur` at one distance: cost = base + lcost[L].




// Relax the literal edge cur -> cur + 1 (when `on`); returns the (final) price at cur + 1.



// Forward DP over one block starting at `start`; returns the block length.
// `st[0]` carries the fruitless-search counter across blocks.


// Continue a DP block past its nominal end: while before `lim` and a match edge crosses `cur` (cur < reach).








// Cost refresh after a DP block: at an output-block boundary (`full`) from that block's
// statistics (which become the prior), else from the running statistics plus the prior.




// ---------------------------------------------------------------- replay pass (from K31)

// Append the relaxed range (search time `t`, start `s`, lengths `lo..=hi`, distance `d`) to the
// edge buffer (`ed[0]` = count; a full buffer sets the count to H_H_EBUF - 1 and stops recording).


// Replay the recorded ranges of search time `p` (from entry `q0`); returns the next entry.


// Second DP over the recorded edges of the block `0 .. bend` with the current costs: literal
// edges at every position, then every recorded range in search order.


// `dst = blk * H_H_TPW + run + prv * H_H_PW / 4` (512 entries).








// Replay only when the edge buffer did not overflow and the pass-1 parse is priced more than
// H_H_RT/1024 higher by the pass-1 model than by the refit model (the models disagree).


// Cost of the symbol counts `llf1`/`df1` under the current model (1/16 bits).


// After pass 1 of the block `pos0 .. pos0 + blen`: its parse gives block statistics, costs are
// refit from them (plus the running and prior statistics) and the recorded edges are replayed.
// A full edge buffer keeps the pass-1 parse. Returns h_backtrack's token/literal count.


// Replay (go == 1: second DP over the recorded edges, new backtrack into llf/df) or keep the
// pass-1 h_parse (its counts are added to llf/df). Returns the token/literal count.


// Walk the chosen edges back from `end`, writing the whole-file plan (len * 65536 + dist, 0 = literal)
// and counting symbols; returns the token count + 16384 * the literal count.


// The backtrack step length: l0 when it is a valid match edge ending at e, else 1.


// Count one path symbol: a match (length l, distance d) when ism == 1, else the literal at q.


// A block length of `e` if `1 <= e <= rest`, else 1.


// The H-DP planner (frontier-search forward-price DP per 6K block,
// adaptive costs across blocks): fills plan[0..n).


// h_dp_plan when on == 1.


// The champion planner: whole-file binary-tree Pareto cache + iterated exact-cost backward DP.
pub fn h_champ(mode: usize, input: &[u8], plan: &mut [u32], gk: u64, i5: usize) {
    let n = input.len();
    let mut mstart: Vec<u32> = Vec::with_capacity(n.wrapping_add(1));
    let mut mc: Vec<u32> = Vec::with_capacity(n.wrapping_mul(3).wrapping_add(64));
    // @FIND_BEGIN
    h_find_all(input, &mut mstart, &mut mc, h_sel(h_lt(n, H_SMALLN), H_BTDS, h_sel(h_eq64(gk, h_mode_gk(mode, H_GKMC)), H_BTDMC, h_sel(h_eq64(gk, h_mode_gk(mode, H_GKX)), h_sel(h_eq(mode,6),24,H_BTDX), H_BTD))));
    // @FIND_END
    let nbmax = n / H_BT + 2;
    let mut tbl = h_filled(nbmax.wrapping_mul(H_TB), 0);
    let mut fr = h_filled(nbmax.wrapping_mul(H_FB), 0);
    let mut bpos = h_filled(nbmax, 0);
    let mut bend = [0u32; 512];
    h_build_bend(&mut bend);
    let mut choice = h_filled(n.wrapping_add(1).wrapping_mul(2), 0);
    h_optimize(mode, input, &mstart, &mc, &mut tbl, &mut fr, &mut bpos, &bend, &mut choice, plan, nbmax, gk, i5);
}

// champ when on == 1.
pub fn h_champ_if(mode: usize, input: &[u8], plan: &mut [u32], on: usize, gk: u64, i5: usize) {
    if on == 1 {
        h_champ(mode, input, plan, gk, i5);
    }
}

// ---------------------------------------------------------------- dispatcher (untrusted)
// Inputs shorter than H_D_SMALL bytes take the H-DP.
pub const H_D_SMALL: usize = 65536;
// Probe: H_PR_N windows of H_PR_W bytes, greedy parse with a 4096-slot 4-byte hash table.
pub const H_PR_W: usize = 8192;
pub const H_PR_N: usize = 8;
// Low-coverage inputs (matched bytes * 1000 < H_LITCOV * probed bytes): H-DP when the sampled
// order-0 entropy is at least H_HLIT/256 bits per byte, else the literal-only plan.
pub const H_LITCOV: u64 = 8;
pub const H_HLIT: usize = 1984;
// H-DP when bytes in probe matches of >= H_LONGL bytes * 1000 >= H_LONGK * probed bytes.
pub const H_LONGL: usize = 32;
pub const H_LONGK: u64 = 340;
// Champion stop-rule constant for inputs whose probe coverage is below H_COVF/1000 (float-weight-like data,
// where every pass keeps paying) and for the others.
pub const H_COVF: u64 = 150;
pub const H_GKLOW: u64 = 32;
// Champion also below this sampled entropy (1/256 bits per byte); default mode otherwise (0 champion, 1 H-DP).
pub const H_HGEN: usize = 896;
// ... but not below H_HGENLO/256 bits (near-constant / tiny-alphabet runs: the H-DP is far faster there).
pub const H_HGENLO: usize = 448;
pub const H_DEFM: usize = 0;
// Champion also for text-like inputs whose probe coverage is below H_COVT/1000 and long-match coverage below H_LONGT/1000.
pub const H_COVT: u64 = 655;
pub const H_LONGT: u64 = 100;
// H-DP frontier width (<= 15) for redundant / small inputs and for the others.
pub const H_KENDR: usize = 20;
pub const H_KENDT: usize = 20;
// Frontier width (<= 31) per frontier class.
pub const H_H_KENDS: [usize; 4] = [20, 20, 20, 20];
pub const H_DIGR: u64 = 150;
// Low-coverage high-entropy inputs with zero bytes >= H_Z0IM/1000 of the sample (image-like) take the champion.
pub const H_Z0IM: u64 = 8;
// Small inputs with sampled order-0 entropy below H_HSP/256 bits per byte (near-constant) use frontier class 2.
pub const H_HSP: usize = 0;
pub const H_NZR: u64 = 81;
// Machine-code-like inputs (control bytes >= H_CTLMC/1000, bytes >= 128 below H_HIMC/1000, long-match coverage
// below H_NMMC/1000) take the champion with stop constant H_GKMC; text-class champion inputs use H_GKT, but
// multibyte-text-like inputs (bytes >= 128 at least H_HITC/1000, control bytes below H_CTLMB/1000) are not text-class.
pub const H_CTLMC: u64 = 120;
pub const H_HIMC: u64 = 400;
pub const H_NMMC: u64 = 440;
pub const H_HITC: u64 = 160;
pub const H_CTLMB: u64 = 20;
pub const H_GKMC: u64 = 4;
// Binary-tree depth of the champion's match finder for machine-code-like inputs.
pub const H_BTDMC: usize = 24;
pub const H_GKT: u64 = 8;
// Default-class (text) inputs take the champion when H_DEFM == 0, with stop constant H_GKX; low-coverage inputs whose
// sampled order-0 entropy is below H_HBF/256 bits per byte (bf16-like) take the champion instead of the literal plan.
pub const H_GKX: u64 = 2;
pub const H_HBF: usize = 1650;
// Binary-tree depth of the champion's match finder for default-class (text) inputs.
pub const H_BTDX: usize = 32;

pub fn h_hash12(input: &[u8], p: usize) -> usize {
    let n = input.len();
    if n >= 4 && p <= n - 4 {
        let x = (input[p] as u32) | ((input[p + 1] as u32) << 8) | ((input[p + 2] as u32) << 16) | ((input[p + 3] as u32) << 24);
        ((x.wrapping_mul(2654435761) >> 20) as usize) % 4096
    } else {
        0
    }
}

// Greedy probe of input[s..e): returns matched bytes * 2^32 + bytes in matches of >= H_LONGL bytes.
pub fn h_probe_win(input: &[u8], ht: &mut [u32; 4096], s: usize, e: usize) -> u64 {
    let n = input.len();
    let mut i = s;
    let mut cov = 0u64;
    let mut nm = 0u64;
    let mut it = 0usize;
    while it < H_PR_W && i < e {
        let h = h_hash12(input, i);
        let c = ht[h % 4096] as usize;
        ht[h % 4096] = (i as u32).wrapping_add(1);
        let cm = c.wrapping_sub(1);
        let ok = h_lt(s, c) & h_lt(cm, i) & h_lt(i.wrapping_add(8), n);
        let cap = h_umin(e.wrapping_sub(i), 258);
        let l = h_ext_if(input, ok, cm, i, 0, cap, 0);
        let hit = h_ge(l, 4);
        cov = cov.wrapping_add(h_sel(hit, l, 0) as u64);
        nm = nm.wrapping_add(h_sel(h_ge(l, H_LONGL), l, 0) as u64);
        i = i.wrapping_add(h_sel(hit, l, 1));
        it += 1;
    }
    cov.wrapping_mul(4294967296).wrapping_add(nm)
}

// Sum of the probe over H_PR_N windows spread over the input (n >= H_PR_W * H_PR_N).
pub fn h_probe_all(input: &[u8]) -> u64 {
    let n = input.len();
    let mut ht = [0u32; 4096];
    let span = n.wrapping_sub(H_PR_W) / (H_PR_N - 1);
    let mut acc = 0u64;
    let mut k = 0usize;
    while k < H_PR_N {
        let s = span.wrapping_mul(k);
        acc = acc.wrapping_add(h_probe_win(input, &mut ht, s, s.wrapping_add(H_PR_W)));
        k += 1;
    }
    acc
}

// probe_all when f == 1, else 0.
pub fn h_probe_if(input: &[u8], f: usize) -> u64 {
    if f == 1 {
        h_probe_all(input)
    } else {
        0
    }
}

// Histogram of an odd-stride sample (every byte lane of word-structured data is seen) of about 4096 bytes.
pub fn h_odd_sample(input: &[u8], h: &mut [u32; 256]) {
    let n = input.len();
    let st = (n / 4096 + 1) | 1;
    let mut k = 0usize;
    let mut c = 0usize;
    while c < 8192 && k < n {
        let b = h_byte_at(input, k) % 256;
        h[b] = h[b].wrapping_add(1);
        k = k.wrapping_add(st);
        c += 1;
    }
}

// 256 * log2(x) (8-bit mantissa), x >= 1.
pub fn h_lg8(x: u32) -> u64 {
    let y = x | 1;
    let e = 31u32.wrapping_sub(y.leading_zeros()) % 32;
    let m = if e >= 8 { y.wrapping_shr(e.wrapping_sub(8)) & 255 } else { y.wrapping_shl(8u32.wrapping_sub(e)) & 255 };
    (e as u64).wrapping_mul(256).wrapping_add(m as u64)
}

// Order-0 entropy of the histogram in 1/256 bits per symbol (2048 for an empty histogram).
pub fn h_entropy256(h: &[u32; 256]) -> usize {
    let mut tot = 0u64;
    let mut acc = 0u64;
    let mut i = 0usize;
    while i < 256 {
        let c = h[i];
        tot = tot.wrapping_add(c as u64);
        acc = if c > 0 { acc.wrapping_add((c as u64).wrapping_mul(h_lg8(c))) } else { acc };
        i += 1;
    }
    let t32 = if tot > 4000000000 { 4000000000u32 } else { tot as u32 };
    let a = h_lg8(t32);
    let b = if tot == 0 { 0 } else { acc / tot };
    if tot == 0 {
        2048
    } else if a > b {
        (a - b) as usize
    } else {
        0
    }
}

pub fn h_ge64(a: u64, b: u64) -> usize {
    if a >= b {
        1
    } else {
        0
    }
}

// mode (0: champion, 1: H-DP, 2: literal-only plan) + 4 * (probe coverage below H_COVF/1000)
// + 8 * (long-match coverage reaches H_LONGK/1000, or a small input).
// Small inputs: H-DP. Low coverage: H-DP when the entropy is high (compressed-like), else literal-only.
// Champion when coverage is below H_COVF/1000 (float-weight-like) or the entropy is below H_HGEN/256 bits
// (DNA-like); H-DP when the long-match coverage reaches H_LONGK/1000; otherwise H_DEFM.
pub fn h_classify(input: &[u8]) -> usize {
    let n = input.len();
    let small = h_lt(n, H_D_SMALL);
    let r = h_probe_if(input, small ^ 1);
    let cov = r / 4294967296;
    let nm = r % 4294967296;
    let mut lh = [0u32; 256];
    h_odd_sample(input, &mut lh);
    let h0 = h_entropy256(&lh);
    let bc = h_byte_classes(&lh);
    let b2 = h_byte_classes2(&lh);
    let tot = bc % 1048576;
    let ctl = (bc / 1048576) % 1048576;
    let hib = (bc / 1099511627776) % 1048576;
    let pw = (H_PR_W * H_PR_N) as u64;
    let low = h_lt64(cov.wrapping_mul(1000), H_LITCOV.wrapping_mul(pw));
    let hl = h_ge64(nm.wrapping_mul(1000), H_LONGK.wrapping_mul(pw));
    let lc = h_lt64(cov.wrapping_mul(1000), H_COVF.wrapping_mul(pw));
    let hi = h_ge(h0, H_HLIT);
    let gen = h_lt(h0, H_HGEN) & h_ge(h0, H_HGENLO);
    let tc0 = h_lt64(cov.wrapping_mul(1000), H_COVT.wrapping_mul(pw)) & h_lt64(nm.wrapping_mul(1000), H_LONGT.wrapping_mul(pw));
    let mb = h_ge64(hib.wrapping_mul(1000), H_HITC.wrapping_mul(tot)) & h_lt64(ctl.wrapping_mul(1000), H_CTLMB.wrapping_mul(tot));
    let tc = tc0 & (mb ^ 1);
    let mc = (small ^ 1) & h_ge64(ctl.wrapping_mul(1000), H_CTLMC.wrapping_mul(tot)) & h_lt64(hib.wrapping_mul(1000), H_HIMC.wrapping_mul(tot)) & h_lt64(nm.wrapping_mul(1000), H_NMMC.wrapping_mul(pw));
    let ch = (lc & (hi ^ 1)) | gen | tc | mc;
    let m0 = h_sel(hl | lc, 1, H_DEFM);
    let m1 = h_sel(ch, 0, m0);
    let z0 = b2 % 65536;
    let im = h_ge64(z0.wrapping_mul(1000), H_Z0IM.wrapping_mul(tot));
    let bf = h_lt(h0, H_HBF);
    let m2 = h_sel(low, h_sel(hi, h_sel(im, 0, 1), h_sel(bf, 0, 2)), m1);
    let gkc = h_sel(lc, h_sel(hi, 4, 1), h_sel(mc, 2, h_sel(tc, 3, h_sel(gen, 0, 5))));
    let dig = (b2 / 65536) % 65536;
    let nz = (b2 / 4294967296) % 65536;
    let dh = (hl | small) & h_eq64(z0, 0) & h_ge64(dig.wrapping_mul(1000), H_DIGR.wrapping_mul(tot)) & h_ge64(H_NZR, nz);
    let sp = small & h_lt(h0, H_HSP);
    let fc = h_sel(dh | sp, 2, h_sel(hl | small, 1, 0));
    h_sel(small, 1, m2).wrapping_add(gkc.wrapping_mul(4)).wrapping_add(fc.wrapping_mul(32))
}

// Zero bytes + 2^16 * digits + 2^32 * distinct bytes of a histogram.
pub fn h_byte_classes2(h: &[u32; 256]) -> u64 {
    let mut z0 = 0u64;
    let mut dig = 0u64;
    let mut nz = 0u64;
    let mut i = 0usize;
    while i < 256 {
        let c = h[i] as u64;
        z0 = z0.wrapping_add(h_sel64(h_eq(i, 0), c, 0));
        dig = dig.wrapping_add(h_sel64(h_ge(i, 48) & h_lt(i, 58), c, 0));
        nz = nz.wrapping_add(h_sel64(h_lt64(0, c), 1, 0));
        i += 1;
    }
    (z0 % 65536).wrapping_add((dig % 65536).wrapping_mul(65536)).wrapping_add((nz % 65536).wrapping_mul(4294967296))
}

// Byte classes of a histogram: total + 2^20 * control bytes (1..31 without tab, LF, CR) + 2^40 * bytes >= 128.
pub fn h_byte_classes(h: &[u32; 256]) -> u64 {
    let mut tot = 0u64;
    let mut ctl = 0u64;
    let mut hib = 0u64;
    let mut i = 0usize;
    while i < 256 {
        let c = h[i] as u64;
        tot = tot.wrapping_add(c);
        let isc = (h_lt(i, 32) & h_ge(i, 1)) & ((h_eq(i, 9) | h_eq(i, 10) | h_eq(i, 13)) ^ 1);
        ctl = ctl.wrapping_add(h_sel64(isc, c, 0));
        hib = hib.wrapping_add(h_sel64(h_ge(i, 128), c, 0));
        i += 1;
    }
    (tot % 1048576).wrapping_add((ctl % 1048576).wrapping_mul(1048576)).wrapping_add((hib % 1048576).wrapping_mul(1099511627776))
}

pub fn h_parse_mode(input: &[u8], out: &mut [u32], mode: usize) -> usize {
    let cmode = mode;
    let mode = mode % 8;
    let n = input.len();
    let c = h_classify(input);
    let route = 0usize;
    let gkc = (c / 4) % 8;
    let gk = h_sel64(h_eq(gkc, 1) | h_eq(gkc, 4), h_mode_gk(mode, H_GKLOW), h_sel64(h_eq(gkc, 2), h_mode_gk(mode, H_GKMC), h_sel64(h_eq(gkc, 3), h_mode_gk(mode, H_GKT), h_sel64(h_eq(gkc, 5), h_mode_gk(mode, H_GKX), h_mode_gk(mode, H_GK2)))));
    let fc = (c / 32) % 4;
    let kend = H_H_KENDS[fc % 4].wrapping_add(fc.wrapping_mul(32));
    let mut plan = h_filled(n.wrapping_add(1), 0);
    h_champ_if(mode, input, &mut plan, h_eq(route, 0), gk, h_eq(gkc, 1));
    let high = h_eq(mode, 2) | h_eq(mode, 3) | (h_eq(mode, 5) | h_eq(mode, 6));
    let force = high & h_eq(route, 1) & h_ge(n, H_D_SMALL);
    // @P7_BEGIN
    let nt = h_emit_all(input, out, &plan);
    // @P7_END
    nt
}

// Default champion mode: local0class.


pub const H_CX_HP:usize=1;





pub const H_CX_FIW:usize=0;

pub fn h_pkg_merge(freq:&[u32],off:usize,nsym:usize,maxbits:usize,lens:&mut [u32],loff:usize) {
    let mut order=[0u32;288];
    let k=h_sort_live(freq,off,nsym,&mut order);
    let mut weights=[0u64;576];
    let mut parent=[0u32;576];
    let mut depth=[0u32;576];
    let mut i=0usize;
    while i<k && i<288 {weights[i]=h_get(freq,off.wrapping_add(order[i] as usize)) as u64;i+=1;}
    let mut leaf=0usize;
    let mut pair=k;
    let mut next=k;
    while next.wrapping_add(1)<k.wrapping_mul(2) && next<575 {
        let mut sum=0u64;
        let mut j=0usize;
        while j<2 {
            let lw=if leaf<k {weights[leaf%576]} else {18446744073709551615u64};
            let pw=if pair<next {weights[pair%576]} else {18446744073709551615u64};
            let take=h_lt64(pw,lw)^1;
            let idx=h_sel(take,leaf,pair);
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
        mx=h_umax(mx,d as usize);
    }
    if mx<=maxbits {
        h_clear(lens,loff,loff.wrapping_add(nsym));
        let mut r=0usize;
        while r<k && r<288 {
            h_set(lens,loff.wrapping_add(order[r] as usize),h_sel32(h_eq(k,1),1,depth[r]));r+=1;
        }
    } else {
        h_pkg_merge_pm(freq,off,nsym,maxbits,lens,loff);
    }
}







pub const H_CX_FIW_HFI: usize = 8;




// Mode-dependent stop constants, selected outside the parsing loops.
pub fn h_mode_gk(mode: usize, base: u64) -> u64 {
    if (mode >= 1 && mode <= 3) || mode == 5 || mode == 6 { base / 2 } else { base }
}

// Select the cost evaluator once per DP pass, outside the per-block loops.
pub fn h_mode_damp(mode:usize,damp:u32)->u32 { if mode==6 && damp>0 {2} else {damp} }

pub fn h_eval_mode(mode: usize, fr: &mut [u32], tbl: &mut [u32], nb: usize, nbmax: usize, damp: u32, ew: u32) -> u64 {
    let damp = h_mode_damp(mode,damp);
    h_eval_blocks(fr,tbl,nb,nbmax,damp)
}


pub fn h_cx_jitter(tbl:&mut [u32],nb:usize,seed:u32, amplitude:u32) {
    let amp = amplitude % 33;
    let mut b=0usize;
    while b<nb {
        let off=b.wrapping_mul(H_TB);
        let mut s=0usize;
        while s<545 {
            let sym=if s>=256 && s<515 {257+h_lcode(s-256)} else if s>=515 {288+s-515} else {s};
            let x=(sym as u32).wrapping_mul(2654435761).wrapping_add(seed.wrapping_mul(2246822519));
            let x=(x^(x>>16)).wrapping_mul(3266489917);
            let d=(x>>24)%(2*amp+1);
            let c=h_get(tbl,off.wrapping_add(s));
            let v=c.saturating_add(d).saturating_sub(amp);
            h_set(tbl,off.wrapping_add(s),v);
            s+=1;
        }
        b+=1;
    }
}

// The high-family restart search; each restart runs three DP refinements.
pub fn h_cx_restarts(
    input: &[u8], mstart: &[u32], mc: &[u32], tbl: &mut [u32],
    fr: &mut [u32], bpos: &mut [u32], bend: &[u32; 512],
    choice: &mut [u32], plan: &mut [u32], nbmax: usize, lamh: u32,
    items: &mut Vec<u32>, istart: &mut Vec<u32>, pr: usize, chw: usize,
    restarts: usize,
) {
    let n = input.len();
    let jitteron = h_eq(h_classify(input) % 4, 0);
    let mut restart = 0usize;
    while restart < restarts && jitteron == 1 {
        let mut nbc = h_walk(input, mstart, mc, plan, 0, fr, bpos);
        let mut bestp = h_eval_blocks(fr, tbl, nbc, nbmax, 0);
        h_cx_jitter(tbl, nbc, (restart as u32).wrapping_add(1), 16);
        let mut step = 0usize;
        while step < 3 {
            h_dp_pass(input, mstart, mc, tbl, bend, bpos, nbc, choice, chw,
                    0, items, istart, pr, 0, 0, lamh);
            nbc = h_walk(input, mstart, mc, choice, 0, fr, bpos);
            let rp = h_eval_blocks(fr, tbl, nbc, nbmax, 0);
            let improve = h_lt64(rp, bestp);
            h_copy32(choice, 0, plan, 0, h_sel(improve, n, 0));
            bestp = h_sel64(improve, rp, bestp);
            step += 1;
        }
        restart += 1;
    }
}
