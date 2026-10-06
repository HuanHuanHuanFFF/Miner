//! S: the slow-region composite. A content router picks one of three optimal-parsing engines
//! (A: text, B: structured, C: DNA/binary) with an effort configuration; every engine writes an
//! untrusted PLAN, `plan[p] = len + 512 * dist` (len < 3: literal), and ONE emission loop walks
//! the plan from 0, re-verifying every planned match byte by byte before writing it.
//!
//! Phase 1 (`make_plan`: router + engines) is search: it only has to be total.
//! Phase 2 (`emit`, `check`, `mlen`, `get0`) carries the decode invariant.
//! Tokens: t < 256 literal, else 2^24 + (dist-1)*256 + (len-3).

// ───────────────────────────── phase 2: the load-bearing part ─────────────────────────────

/// How many bytes agree at `a` and `b`, up to `cap`. The only function whose result the
/// proof depends on (through `check`).
pub fn mlen(input: &[u8], a: usize, b: usize, cap: usize) -> usize {
    let mut l = 0usize;
    while l < cap && input[b + l] == input[a + l] {
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

/// `v[i]`, or 0 when `i` is out of range: a read that cannot panic.
pub fn get0(v: &[u32], i: usize) -> u32 {
    if i < v.len() {
        v[i]
    } else {
        0
    }
}

/// `v[i] = x` when `i` is in range, nothing otherwise: a write that cannot panic.
pub fn set_in(v: &mut [u32], i: usize, x: u32) {
    if i < v.len() {
        v[i] = x;
    }
}

/// Phase 2: walk the plan from 0; a planned match is written only if `check` accepts it.
pub fn emit(input: &[u8], plan: &[u32], out: &mut [u32]) -> usize {
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

/// The whole parser: plan, then emit.
pub fn parse(input: &[u8], out: &mut [u32]) -> usize {
    let plan = make_plan(input);
    emit(input, &plan, out)
}

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

// ───────────────────────────── phase 1: router and configurations ─────────────────────────────

/// Engine configurations: [engine, knobs...]. Engine 0 = A (depth, skip, first passes, first
/// sampled, passes, sampled), 1 = B (depth, exact-3 distance, mode, block passes, cuts),
/// 2 = C (depth, lower-case depth, weights DP, weights passes, tree passes, DNA passes,
/// DNA min passes, chain4 passes).
pub const CFG: [[usize; 9]; 16] = [
    [0, 16, 260, 7, 4, 4, 2, 0, 0],       // 0  A (depth 16 skip 260 first 7/4 passes 4/2)
    [2, 24, 24, 1, 3, 2, 20, 12, 2],      // 1  C (24 24 1 3 2 20 12 2)
    [2, 24, 24, 1, 3, 2, 12, 7, 2],       // 2  C (24 24 1 3 2 12 7 2)
    [2, 24, 24, 1, 3, 4, 12, 7, 4],       // 3  C (24 24 1 3 4 12 7 4)
    [0, 48, 260, 9, 2, 9, 23, 0, 0],      // 4  A (depth 48 skip 260 first 9/2 passes 9/7, rotated samples)
    [0, 18, 260, 12, 10, 6, 20, 0, 0],    // 5  A (depth 18 skip 260 first 12/10 passes 6/4, rotated samples)
    [0, 24, 260, 6, 4, 4, 18, 0, 0],      // 6  A (depth 24 skip 260 first 6/4 passes 4/2, rotated samples)
    [0, 36, 260, 9, 9, 6, 18, 0, 0],      // 7  A (depth 36 skip 260 first 9/9 passes 6/2, rotated samples)
    [0, 16, 260, 8, 6, 5, 4, 0, 0],       // 8  A (depth 16 skip 260 first 8/6 passes 5/4)
    [0, 64, 260, 12, 8, 12, 8, 0, 0],     // 9  A (depth 64 skip 260 first 12/8 passes 12/8)
    [0, 64, 260, 12, 8, 12, 8, 0, 0],     // 10 A (depth 64 skip 260 first 12/8 passes 12/8)
    [0, 96, 260, 8, 6, 6, 20, 0, 0],      // 11 A (depth 96 skip 260 first 8/6 passes 6/4, rotated samples)
    [0, 32, 260, 8, 6, 16, 24, 0, 0],     // 12 A (depth 32 skip 260 first 8/6 passes 16/8, rotated samples)
    [0, 24, 260, 6, 4, 4, 2, 0, 0],       // 13 unused
    [0, 24, 260, 6, 4, 4, 2, 0, 0],       // 14 unused
    [0, 24, 260, 6, 4, 4, 2, 0, 0],       // 15 unused
];

/// Content class -> configuration (index into CFG).
pub const CLASS_CFG: [usize; 16] = [
    0,  // 0  tiny text (< 32 KiB)
    1,  // 1  DNA
    2,  // 2  sparse (mostly zero bytes)
    3,  // 3  binary with high-byte noise (weights, images, compressed)
    4,  // 4  binary with structure (databases, machine code)
    5,  // 5  markup, many lines (XML)
    6,  // 6  markup, few lines (HTML)
    7,  // 7  numeric table with quotes and commas (CSV)
    8,  // 8  numeric rows with commas (SQL dump)
    9,  // 9  numeric lines (logs)
    10, // 10 quoted text (JSON)
    11, // 11 long lines (minified code, source maps)
    12, // 12 default text (prose, docs, source code, config)
    12, 12, 12,
];

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

/// Content class of the input (index into CLASS_CFG).
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
    12
}

/// Run configuration `k` on the input; returns the plan.
pub fn plan_cfg(input: &[u8], k: usize) -> Vec<u32> {
    let n = input.len();
    let mut plan = zeros(n);
    let c = CFG[k % 16];
    if c[0] == 0 {
        a_engine(input, &mut plan, c[1], c[2], c[3], c[4], c[5], c[6]);
    } else if c[0] == 1 {
        b_engine(input, &mut plan, c[1], c[2], c[3], c[4], c[5]);
    } else {
        c_engine(input, &mut plan, c[1], c[2], c[3], c[4], c[5], c[6], c[7], c[8]);
    }
    plan
}

/// Phase 1: the plan. Every value in it is a suggestion; `emit` checks each one.
pub fn make_plan(input: &[u8]) -> Vec<u32> {
    if input.len() >= 67108864 {
        return Vec::new();
    }
    let cls = classify(input);
    plan_cfg(input, CLASS_CFG[cls % 16])
}

/// Test entry: plan with a forced configuration, then emit.
pub fn parse_cfg(input: &[u8], out: &mut [u32], k: usize) -> usize {
    let plan = plan_cfg(input, k);
    emit(input, &plan, out)
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
    mp.push(0);
    while i < n {
        if n >= 266 && i <= n - 266 {
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
                let x = (cd - 1) as u32;
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
        } else if n >= 3 && i <= n - 3 {
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
        mp.push(mb.len() as u32);
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
        lf[z] = lf0[z];
        z += 1;
    }
    let lf = &lf;
    let mut hl = [0u32; 512];
    a_huff_lengths(lf, 286, &mut hl);
    let mut dd = [0u32; 512];
    let mut i = 0usize;
    while i < 30 {
        dd[i] = df[i];
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
            cost[i] = ((best >> 9).wrapping_add(nxt)).wrapping_sub(1048576);
            let bl = best & 511;
            ch[i] = if bl >= 3 { bl + 512 * (bd + 1) } else { 0 };
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
            if k < sampled && k + 1 < passes && pe - p0 > 4 * A_SEG * A_SAMPLE {
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

// ───────────────────────────── engine B: structured text ─────────────────────────────
// Suffix-ordered binary tree per 4-byte hash over EVERY position (plus the latest exact 3-byte
// match), compared through a ring of big-endian words, descents replayed from the previous
// position; Pareto candidates with <= 2 full-length continuations. Per 32K segment a backward
// shortest-path pass under entropy costs (warm start, adaptive refine); mode 2 then re-runs the
// whole input under per-encoder-block tables. Knobs: depth, h3dist, mode, bpasses, cuts.

pub const B_WR: usize = 32768;
pub const B_WLIM: usize = 32256;
pub const B_TS: usize = 65536;
pub const B_HBITS: u32 = 16;
pub const B_HSIZE: usize = 65536;
pub const B_H3BITS: u32 = 14;
pub const B_H3SIZE: usize = 16384;
pub const B_FMAX: usize = 2;
pub const B_SEG: usize = 32768;
/// Mode 2 keeps every record; above this input size it behaves like mode 0.
pub const B_KEEPMAX: usize = 1 << 26;
/// Refine a segment when its parse costs more than (1 + GAP/1024) x its own entropy.
pub const B_GAP: u64 = 20;
/// Candidate record: dist-1 in bits 0..15, distance slot in 15..20, length in 20..29, FULL flag.
pub const B_FULL: u32 = 1 << 29;
pub const B_RB: usize = 32;
pub const B_PS: usize = 32;
/// Symbol counts: lit/len symbols at 0..286, distance slots at 288 + slot.
pub const B_FSZ: usize = 320;
/// Hint sentinel: no known continuation node.
pub const B_NOHINT: usize = 0xFFFF_FFFF;

pub const B_LOG2_FRAC: [u16; 256] = [
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

/// Match finder state: hash heads, the suffix trees (two child slots per position), a ring of
/// 8-byte words, and the previous descent (node, flags|length per step).
pub struct BMf {
    pub head: [u32; B_HSIZE],
    pub head3: [u32; B_H3SIZE],
    pub tree: [u32; B_TS],
    pub w: [u64; B_WR],
    pub pn: [u32; B_PS],
    pub pf: [u32; B_PS],
    pub plen: usize,
    pub hn: usize,
    pub hl: usize,
}

/// log2(x) in 1/256 bit, x >= 1 (0 for x == 0).
pub fn b_log2_fix(x: u32) -> u32 {
    if x == 0 {
        return 0;
    }
    let e = 31 - x.leading_zeros();
    let m = if e >= 8 { (x >> (e - 8)) & 255 } else { (x << (8 - e)) & 255 };
    e * 256 + B_LOG2_FRAC[m as usize] as u32
}

/// DEFLATE length code index 0..=28 and extra-bit count for 3 <= l <= 258.
pub fn b_len_code(l: usize) -> (usize, usize) {
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

/// DEFLATE distance code index 0..=29 for 1 <= d <= 32768.
pub fn b_dist_slot(d: usize) -> usize {
    if d < 5 {
        return if d >= 1 { d - 1 } else { 0 };
    }
    let v = ((if d > 32768 { 32768 } else { d }) - 1) as u32;
    let k = 31 - v.leading_zeros();
    2 * (k as usize) + ((v >> (k - 1)) & 1) as usize
}

pub fn b_rec(l: usize, d: usize, full: u32) -> u32 {
    ((l as u32) << 20) | ((b_dist_slot(d) as u32) << 15) | ((d - 1) as u32) | full
}

/// The input byte at p, or 0 past the end.
pub fn b_byte_at(s: &[u8], p: usize) -> u64 {
    if p < s.len() { s[p] as u64 } else { 0 }
}

/// Add candidate (l, d) to the position's record buffer: at most B_FMAX continuations (flag != 0)
/// are kept, the shortest one is dropped first. Returns the new (count, continuations).
pub fn b_add_record(rv: &mut [u32; B_RB], nr: usize, nf: usize, l: usize, d: usize, flag: u32) -> (usize, usize) {
    let mut n = nr;
    let mut f = nf;
    if flag != 0 && f >= B_FMAX {
        let mut q = 0usize;
        let mut wq = 0usize;
        let mut dropped = 0usize;
        while q < n {
            let v = rv[q % B_RB];
            if dropped == 0 && v & B_FULL != 0 {
                dropped = 1;
            } else {
                rv[wq % B_RB] = v;
                wq += 1;
            }
            q += 1;
        }
        n = wq;
        f -= 1;
    }
    if n < B_RB {
        rv[n % B_RB] = b_rec(l, d, flag);
        n += 1;
        if flag != 0 {
            f += 1;
        }
    }
    (n, f)
}

/// Insert position i into its bucket's suffix-ordered binary tree (root `first`, position + 1),
/// adding every strictly longer match met on the way down to rv. Returns (records,
/// continuations, best length, its distance).
pub fn b_descend(mf: &mut BMf, first: usize, i: usize, cap: usize, scap: usize, best0: usize, wp: u64, rv: &mut [u32; B_RB], nr0: usize, nf0: usize, depth: usize) -> (usize, usize, usize, usize) {
    let mut step = 0usize;
    let plen = mf.plen;
    let hn = mf.hn;
    let hl = mf.hl;
    let mut cur = first;
    let me = i % B_WR;
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
        if cur == 0 || d == 0 || d >= B_WLIM {
            mf.tree[ls % B_TS] = 0;
            mf.tree[rs % B_TS] = 0;
            fuel = 0;
        } else {
            let c = i - d;
            // the previous position's descent met c - 1 at this step: same comparison, one byte on
            let pf = mf.pf[step % B_PS];
            let known = step < plen && (mf.pn[step % B_PS] as usize) + 1 == c && pf & 1 == 1 && pf >= 4;
            let mut l = if ll < rl { ll } else { rl };
            let mut lt = 0usize;
            if known {
                l = (pf >> 2) as usize - 1;
                lt = ((pf >> 1) & 1) as usize;
            } else {
                if c == hn && hl > l {
                    l = hl;
                }
                let mut wc = mf.w[c.wrapping_add(l) % B_WR];
                let mut wi = mf.w[i.wrapping_add(l) % B_WR];
                let mut run = 1usize;
                while run == 1 && wc == wi {
                    l += 8;
                    if l >= cap {
                        run = 0;
                    } else {
                        wc = mf.w[c.wrapping_add(l) % B_WR];
                        wi = mf.w[i.wrapping_add(l) % B_WR];
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
            if step < B_PS {
                mf.pn[step % B_PS] = c as u32;
                mf.pf[step % B_PS] = (if l < cap { 1u32 } else { 0u32 }) | ((lt as u32) << 1) | ((l as u32) << 2);
            }
            step += 1;
            if l > best {
                best = l;
                bl = l;
                bd = d;
                let rl2 = if l < scap { l } else { scap };
                if rl2 > rbest {
                    rbest = rl2;
                    let flag = if c >= 1 && (mf.w[(c - 1) % B_WR] >> 56) == wp { B_FULL } else { 0 };
                    let r = b_add_record(rv, nr, nf, rl2, d, flag);
                    nr = r.0;
                    nf = r.1;
                }
            }
            let cs = 2 * (c % B_WR);
            if l >= cap {
                mf.tree[ls % B_TS] = mf.tree[cs % B_TS];
                mf.tree[rs % B_TS] = mf.tree[(cs + 1) % B_TS];
                fuel = 0;
            } else {
                if lt == 1 {
                    mf.tree[ls % B_TS] = cur as u32;
                    ls = cs + 1;
                    ll = l;
                    cur = mf.tree[(cs + 1) % B_TS] as usize;
                } else {
                    mf.tree[rs % B_TS] = cur as u32;
                    rs = cs;
                    rl = l;
                    cur = mf.tree[cs % B_TS] as usize;
                }
                fuel -= 1;
                if fuel == 0 {
                    mf.tree[ls % B_TS] = 0;
                    mf.tree[rs % B_TS] = 0;
                }
            }
        }
    }
    mf.plen = if step < B_PS { step } else { B_PS };
    if bd > 0 && bl >= 2 {
        mf.hn = i + 1 - bd;
        mf.hl = bl - 1;
    } else {
        mf.hn = B_NOHINT;
        mf.hl = 0;
    }
    (nr, nf, bl, bd)
}

/// Symbol cost in 1/16 bit from a count and its alphabet total.
pub fn b_sym_cost(f: u32, total: u32) -> u32 {
    let a = b_log2_fix(total.wrapping_mul(2).wrapping_add(1));
    let b = b_log2_fix(f.wrapping_mul(2).wrapping_add(1));
    let c = if a > b { (a - b) >> 4 } else { 0 };
    if c < 16 { 16 } else { c }
}

/// Cost table from symbol counts: literals at 0..256, lengths at 256 + len, distance slots at 520 + slot.
pub fn b_build_table(freq: &[u32; B_FSZ], tb: &mut [u32; 1024]) {
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
        tb[k] = b_sym_cost(freq[k], tl);
        k += 1;
    }
    let mut l = 3usize;
    while l <= 258 {
        let lc = b_len_code(l);
        tb[256 + l] = b_sym_cost(freq[(257 + lc.0) % B_FSZ], tl) + 16 * lc.1 as u32;
        l += 1;
    }
    k = 0;
    while k < 30 {
        let e = if k < 4 { 0 } else { k / 2 - 1 };
        tb[520 + k] = b_sym_cost(freq[288 + k], td) + 16 * e as u32;
        k += 1;
    }
}

/// Entropy-coded size of the counts in 1/16 bit (each alphabet on its own).
pub fn b_self_cost(freq: &[u32; B_FSZ]) -> u64 {
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
    let lt = b_log2_fix(tl) as u64;
    let ld = b_log2_fix(td) as u64;
    let mut c = 0u64;
    k = 0;
    while k < 286 {
        let f = freq[k];
        let lf = b_log2_fix(f) as u64;
        if f > 0 && lt >= lf {
            c += (f as u64) * (lt - lf);
        }
        k += 1;
    }
    k = 0;
    while k < 30 {
        let f = freq[288 + k];
        let lf = b_log2_fix(f) as u64;
        if f > 0 && ld >= lf {
            c += (f as u64) * (ld - lf);
        }
        k += 1;
    }
    c >> 4
}

/// Extra bits (1/16 bit units) implied by the length and distance symbol counts.
pub fn b_extra_bits(freq: &[u32; B_FSZ]) -> u64 {
    let mut c = 0u64;
    let mut k = 8usize;
    while k < 28 {
        c += (freq[(257 + k) % B_FSZ] as u64) * ((k / 4 - 1) as u64);
        k += 1;
    }
    k = 4;
    while k < 30 {
        c += (freq[288 + k] as u64) * ((k / 2 - 1) as u64);
        k += 1;
    }
    c * 16
}

/// Pseudo-counts whose entropy costs approximate the fixed Huffman code (first pass).
pub fn b_static_freq(f: &mut Vec<u32>) {
    let mut k = 0usize;
    while k < B_FSZ {
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

/// Load block b's counts from bf and build its cost table.
pub fn b_block_table(bf: &Vec<u32>, b: usize, tb: &mut [u32; 1024]) {
    let mut fq = [0u32; B_FSZ];
    let mut z = 0usize;
    while z < B_FSZ && b * B_FSZ + z < bf.len() {
        fq[z] = bf[b * B_FSZ + z];
        z += 1;
    }
    b_build_table(&fq, tb);
}

/// Backward shortest path over positions a..a+m. The record stream rs holds, for every position
/// in order, its records followed by their count; cc[j] = cost | choice << 32 for position a+m-j.
/// Block b's counts (bf[b * B_FSZ..]) price the positions from offset bs[b] on.
pub fn b_dp_seg(s: &[u8], a: usize, m: usize, rs: &Vec<u32>, rn: usize, bf: &Vec<u32>, bs: &Vec<u32>, nb: usize, cc: &mut Vec<u64>, cuts: usize) {
    let mut tb = [0u32; 1024];
    let mut b = if nb > 0 { nb - 1 } else { 0 };
    b_block_table(bf, b, &mut tb);
    let mut bfirst = if b < bs.len() { bs[b] as usize } else { 0 };
    cc[0] = 0;
    let mut p = rn;
    let mut j = 1usize;
    while j <= m && p >= 1 {
        let off = m - j;
        if off < bfirst && b > 0 {
            b -= 1;
            b_block_table(bf, b, &mut tb);
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
            if v & B_FULL != 0 && cuts == 0 {
                if ml <= j {
                    let x = (cc[j - ml] as u32).wrapping_add(tb[(256 + ml) % 1024]).wrapping_add(dc);
                    if x < best {
                        best = x;
                        choice = ((ml as u32) << 15) | (v & 32767);
                    }
                }
            } else {
                let full = v & B_FULL;
                let mut l = if full != 0 { if ml > lo + cuts { ml - cuts } else { lo } } else { lo };
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

/// Per-block symbol counts along the parse in cc (positions a..a+m, a new encoder block every
/// BLOCK_TOKENS tokens, or one block when whole == 0); returns the block count.
pub fn b_tally_seg(s: &[u8], a: usize, m: usize, cc: &Vec<u64>, whole: usize, bf: &mut Vec<u32>, bs: &mut Vec<u32>) -> usize {
    let mut nb = 0usize;
    let mut inb = BLOCK_TOKENS;
    let mut j = m;
    while j > 0 {
        if inb == BLOCK_TOKENS && (whole == 1 || nb == 0) {
            let base = nb * B_FSZ;
            let mut z = 0usize;
            while z < B_FSZ {
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
        let f = (nb - 1) * B_FSZ;
        let v = (cc[j] >> 32) as u32;
        let l = (v >> 15) as usize;
        if l >= 3 && l <= j {
            let d = (v & 32767) as usize + 1;
            bf[f + (257 + b_len_code(l).0) % B_FSZ] += 1;
            bf[f + (288 + b_dist_slot(d)) % B_FSZ] += 1;
            j -= l;
        } else {
            bf[f + s[a + m - j] as usize % B_FSZ] += 1;
            j -= 1;
        }
        if inb < BLOCK_TOKENS {
            inb += 1;
        }
    }
    if nb > 0 {
        bf[(nb - 1) * B_FSZ + 256] += 1;
    }
    nb
}

/// Per-block symbol counts of the planned path from 0 (a block every BLOCK_TOKENS tokens) and
/// the input offset where each block starts; returns the block count.
pub fn b_tally_plan(s: &[u8], plan: &Vec<u32>, bf: &mut Vec<u32>, bs: &mut Vec<u32>) -> usize {
    let n = s.len();
    let mut nb = 0usize;
    let mut pos = 0usize;
    let mut t = 0usize;
    while pos < n && pos < plan.len() {
        if t % BLOCK_TOKENS == 0 {
            let base = nb * B_FSZ;
            let mut z = 0usize;
            while z < B_FSZ {
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
        let f = (nb - 1) * B_FSZ;
        let v = plan[pos] as usize;
        let l = v % 512;
        if l >= 3 && l <= n - pos {
            let d = v / 512;
            bf[f + (257 + b_len_code(l).0) % B_FSZ] += 1;
            bf[f + (288 + b_dist_slot(d)) % B_FSZ] += 1;
            pos += l;
        } else {
            bf[f + s[pos] as usize] += 1;
            pos += 1;
        }
        t += 1;
    }
    if nb > 0 {
        bf[(nb - 1) * B_FSZ + 256] += 1;
    }
    nb
}

/// Write the parse in cc (positions a..a+m) into the plan.
pub fn b_plan_seg(a: usize, m: usize, cc: &Vec<u64>, plan: &mut Vec<u32>) {
    let mut j = m;
    while j > 0 {
        let i = a + m - j;
        let v = (cc[j] >> 32) as u32;
        let l = (v >> 15) as usize;
        let d = (v & 32767) as usize + 1;
        if l >= 3 && l <= j {
            set_in(plan, i, (l + 512 * d) as u32);
            j -= l;
        } else {
            set_in(plan, i, 0);
            j -= 1;
        }
    }
}

/// Append v to the record stream at rn; returns rn + 1.
pub fn b_put(rs: &mut Vec<u32>, rn: usize, v: u32) -> usize {
    if rn < rs.len() {
        rs[rn] = v;
    } else {
        rs.push(v);
    }
    rn + 1
}

/// Engine B: writes the plan (length n). Knobs: tree depth, exact-3 distance limit, mode
/// (0 segments only, 1 one segment with block passes, 2 segments then whole-input block passes),
/// block passes, continuation cuts.
pub fn b_engine(input: &[u8], plan: &mut Vec<u32>, depth: usize, h3dist: usize, mode: usize, bpasses: usize, cuts: usize) {
    let n = input.len();
    if n < 16 {
        return;
    }
    let mut mf = BMf {
        head: [0u32; B_HSIZE],
        head3: [0u32; B_H3SIZE],
        tree: [0u32; B_TS],
        w: [0u64; B_WR],
        pn: [0u32; B_PS],
        pf: [0u32; B_PS],
        plen: 0,
        hn: B_NOHINT,
        hl: 0,
    };
    let mut rv = [0u32; B_RB];
    let mut freq = [0u32; B_FSZ];
    let mut bf: Vec<u32> = Vec::new();
    let mut bs: Vec<u32> = Vec::new();
    let keep = if mode == 2 && n <= B_KEEPMAX { 1usize } else { 0usize };
    let segcap = if n < B_SEG || keep == 1 { n } else { B_SEG };
    let mut rs: Vec<u32> = Vec::with_capacity(4 * segcap);
    let mut cc: Vec<u64> = Vec::with_capacity(segcap + 1);
    while cc.len() <= segcap {
        cc.push(0);
    }
    // word ring: w[p % B_WR] = big-endian s[p..p+8]; x is the word at position wfill
    let mut x = 0u64;
    let mut k = 0usize;
    while k < 8 {
        x = (x << 8) | b_byte_at(input, k);
        k += 1;
    }
    let mut wfill = 0usize;
    let mut rn = 0usize;
    let mut a = 0usize;
    while a < n {
        let m = if n - a < B_SEG { n - a } else { B_SEG };
        let b = a + m;
        if keep == 0 {
            rn = 0;
        }
        let mut i = a;
        while i < b {
            let top = if i + 264 < n { i + 264 } else { n };
            while wfill < top {
                mf.w[wfill % B_WR] = x;
                x = (x << 8) | b_byte_at(input, wfill + 8);
                wfill += 1;
            }
            let mut nr = 0usize;
            if n - i >= 4 {
                let rem = n - i;
                let cap = if rem < 258 { rem } else { 258 };
                let scap = if b - i < cap { b - i } else { cap };
                let wi = mf.w[i % B_WR];
                let wp = if i > a { mf.w[(i - 1) % B_WR] >> 56 } else { 256 };
                let mut nf = 0usize;
                let mut best = 2usize;
                let h3 = ((((wi >> 40) as u32).wrapping_mul(2246822519)) >> (32 - B_H3BITS)) as usize % B_H3SIZE;
                let p3 = mf.head3[h3] as usize;
                mf.head3[h3] = (i + 1) as u32;
                let d3 = (i + 1).wrapping_sub(p3);
                if p3 > 0 && d3 >= 1 && d3 <= h3dist && scap >= 3 {
                    let c = i - d3;
                    let x3 = mf.w[c % B_WR] ^ wi;
                    if (x3 >> 40) == 0 && (x3 >> 32) != 0 {
                        let flag = if c >= 1 && (mf.w[(c - 1) % B_WR] >> 56) == wp { B_FULL } else { 0 };
                        let r = b_add_record(&mut rv, 0, 0, 3, d3, flag);
                        nr = r.0;
                        nf = r.1;
                        best = 3;
                    }
                }
                let h = ((((wi >> 32) as u32).wrapping_mul(2654435761)) >> (32 - B_HBITS)) as usize % B_HSIZE;
                let first = mf.head[h] as usize;
                mf.head[h] = (i + 1) as u32;
                let r = b_descend(&mut mf, first, i, cap, scap, best, wp, &mut rv, nr, nf, depth);
                nr = r.0;
                let mut q = 0usize;
                while q < nr {
                    rn = b_put(&mut rs, rn, rv[q % B_RB]);
                    q += 1;
                }
            }
            rn = b_put(&mut rs, rn, nr as u32);
            i += 1;
        }
        if a == 0 {
            b_static_freq(&mut bf);
        }
        if bs.len() == 0 {
            bs.push(0);
        }
        bs[0] = 0;
        b_dp_seg(input, a, m, &rs, rn, &bf, &bs, 1, &mut cc, cuts);
        if mode == 1 {
            let mut p = 0usize;
            while p < bpasses {
                let nb = b_tally_seg(input, a, m, &cc, 1, &mut bf, &mut bs);
                b_dp_seg(input, a, m, &rs, rn, &bf, &bs, nb, &mut cc, cuts);
                p += 1;
            }
        } else {
            let _ = b_tally_seg(input, a, m, &cc, 0, &mut bf, &mut bs);
            let mut k2 = 0usize;
            while k2 < B_FSZ {
                freq[k2] = bf[k2];
                k2 += 1;
            }
            // extra bits are identical under both tables; compare symbol costs only
            let paid = (cc[m] & 0xFFFFFFFF) as u64;
            let own = b_self_cost(&freq);
            let xb = b_extra_bits(&freq);
            if a == 0 || (paid > xb && (paid - xb) * 1024 > own * (1024 + B_GAP)) {
                b_dp_seg(input, a, m, &rs, rn, &bf, &bs, 1, &mut cc, cuts);
                let _ = b_tally_seg(input, a, m, &cc, 0, &mut bf, &mut bs);
            }
        }
        b_plan_seg(a, m, &cc, plan);
        a = b;
    }
    if keep == 1 && bpasses > 0 {
        let mut nb = b_tally_plan(input, plan, &mut bf, &mut bs);
        let mut p = 0usize;
        while p < bpasses {
            b_dp_seg(input, 0, n, &rs, rn, &bf, &bs, nb, &mut cc, cuts);
            if p + 1 < bpasses {
                nb = b_tally_seg(input, 0, n, &cc, 1, &mut bf, &mut bs);
            }
            p += 1;
        }
        b_plan_seg(0, n, &cc, plan);
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
