//! r9 N2 (honest) = m10 + lane R1 text loop gr_text (R1_TEXT) + FL_MC class routed to it (R1_MC); tokens = m10 except machine code
//! patch8: join=None tab=None inline=always noinline=['--noinline=g_scan,gh_scan']
//! r8 merge m9 (= m3 + G_ACC 4) = E2 parse-h (ac008b636ba09666) + E1 genome lane (lg_parse_d) + E1 high-entropy lane (lg_parse_h)
//! for sampled entropy >= FL_HIGH below the 1800 (1/256 bit) threshold of G's own high lane (f32 stays with G).
//! cx3: f82 batched parser with compact small-input tables and entropy-aware preparation.
//! The original 18 trusted helper bodies are unchanged. See README.md for the measured curve.
//! Dense text preparation, sparse high-entropy preparation, and a near-uniform literal lane.

pub const G_ACC: u64 = 4;
pub const G_AMAX: usize = 12;
pub const G_IH: usize = 2;
pub const G_IT: usize = 1;
pub const G_LZT: usize = 0;
pub const G_M3: usize = 1;
pub const G_MAX3: usize = 32768;
pub const G_WIN: usize = 32768;
pub const G_TS: usize = 16;
pub const G_MAX4: usize = 32768;
pub const G_M3Z: usize = 100;
pub const G_M3E: usize = 1800;
pub const G_HLMASK: u64 = 18446744073709551615;
pub const DEPTH: usize = 16;
pub const DEPTH2: usize = 8;
pub const GOOD: usize = 3;
pub const LAZY: usize = 258;
pub const NICE: usize = 258;
pub const IH: usize = 258;
pub const IT: usize = 64;
pub const ACC: u64 = 5;
pub const STEPMAX: usize = 32;
pub const LITQ: usize = 28;
pub const LADJ: usize = 2;
pub const HLOW: usize = 900;
pub const HSL: u32 = 0;
pub const ELO: usize = 400;
pub const H3HI: usize = 100;
pub const H3CTL: usize = 100;
pub const H3E: usize = 1700;
pub const ACCL: u64 = 63;
pub const H3: usize = 1;
pub const MAX3: usize = 4096;
pub const H3INS: usize = 1;
pub const C0Q: usize = 44;
pub const C0L: usize = 44;
pub const DEPTHL: usize = 12;
pub const M3: usize = 0;
pub const DEPTH3M: usize = 12;
pub const M3E: usize = 1900;
pub const M3Z: usize = 15;
pub const LZB: usize = 0;
pub const BONUS: usize = 0;
pub const EXT: usize = 1;
pub const DIGN: usize = 200;
pub const DN: usize = 4;
pub const P2N: usize = 8;
pub const LQN: usize = 20;
pub const NBIG: usize = 65536;
pub const GOODL: usize = 258;
pub const P2G: usize = 2;
pub const NSMALL: usize = 65536;
pub const BIAS: usize = 4096;

// ------------------------------------------------------------------ loads and compares (search only)

/// Little-endian 4-byte load at `p`; 0 when out of range.
pub fn ld4(input: &[u8], p: usize) -> u32 {
    let n = input.len();
    if n < 4 || p > n - 4 {
        return 0;
    }
    ((input[p + 3] as u32) << 24) | ((input[p + 2] as u32) << 16) | ((input[p + 1] as u32) << 8) | (input[p] as u32)
}

/// Little-endian 8-byte load at `p` (two u32 halves, highest byte read first); 0 when out of range.
pub fn ld8(input: &[u8], p: usize) -> u64 {
    let n = input.len();
    if n < 8 || p > n - 8 {
        return 0;
    }
    let hi = ((input[p + 7] as u32) << 24) | ((input[p + 6] as u32) << 16) | ((input[p + 5] as u32) << 8) | (input[p + 4] as u32);
    let lo = ((input[p + 3] as u32) << 24) | ((input[p + 2] as u32) << 16) | ((input[p + 1] as u32) << 8) | (input[p] as u32);
    ((hi as u64) << 32) | (lo as u64)
}

/// Index (0..7) of the first differing byte of two little-endian words, given their xor (!= 0).
pub fn first_diff(x: u64) -> usize {
    let low = x & 0u64.wrapping_sub(x);
    (63u32.wrapping_sub(low.leading_zeros()) / 8) as usize
}

/// Common prefix of positions `a < b`, up to `cap` (search only; never trusted).
#[inline(always)]
pub fn fast_len(input: &[u8], a: usize, b: usize, cap: usize) -> usize {
    let mut l = 0usize;
    let mut go = 1usize;
    let mut it = 0usize;
    while go == 1 && it < 40 {
        if l < cap {
            let x = ld8(input, a.wrapping_add(l)) ^ ld8(input, b.wrapping_add(l));
            let k = if x == 0 { 8 } else { first_diff(x) };
            l = l.wrapping_add(k);
            go = if x == 0 { 1 } else { 0 };
        } else {
            go = 0;
        }
        it += 1;
    }
    if l > cap { cap } else { l }
}

/// Hash of the first (64 - hs) / 8 bytes at `p` into 16 bits.
#[inline(always)]
pub fn hashp(input: &[u8], p: usize, hs: u32) -> usize {
    if hs == 32 {
        return (ld4(input, p).wrapping_mul(2654435761) >> 16) as usize;
    }
    let v = ld8(input, p) << (hs % 64);
    (v.wrapping_mul(0x9E3779B97F4A7C15) >> 48) as usize
}

/// Hash of the low 3 bytes of a word into 14 bits.
pub fn hash3(w: u32) -> usize {
    ((w << 8).wrapping_mul(2654435761) >> 18) as usize
}

// ------------------------------------------------------------------ cost model (search only)

/// DEFLATE distance extra bits of `d`.
pub fn dextra(d: usize) -> usize {
    if d <= 4 {
        0
    } else {
        let x = (d.wrapping_sub(1) as u32) | 1;
        (31u32.wrapping_sub(x.leading_zeros()) as usize).wrapping_sub(1)
    }
}

/// DEFLATE length extra bits of `l`.
pub fn lextra(l: usize) -> usize {
    if l < 11 || l >= 258 {
        0
    } else {
        let x = (l.wrapping_sub(3) as u32) | 1;
        (31u32.wrapping_sub(x.leading_zeros()) as usize).wrapping_sub(2)
    }
}

/// Estimated saving (quarter bits, offset by BIAS) of coding `l` bytes as a match at `d`.
/// `cq` packs the literal cost (low 8 bits) and the match base cost (bits 8..).
pub fn score(l: usize, d: usize, cq: usize) -> usize {
    let cost = (cq / 256).wrapping_add(dextra(d).wrapping_add(lextra(l)).wrapping_mul(4));
    l.wrapping_mul(cq % 256).wrapping_add(BIAS).wrapping_sub(cost)
}

/// Fixed-point log2 with 8 fractional bits (linear between powers of two).
pub fn lg8(x: u32) -> u64 {
    let y = x | 1;
    let e = 31u32.wrapping_sub(y.leading_zeros()) % 32;
    let m = if e >= 8 { (y >> ((e.wrapping_sub(8)) % 32)) & 255 } else { (y << ((8u32.wrapping_sub(e)) % 32)) & 255 };
    (e as u64).wrapping_mul(256).wrapping_add(m as u64)
}

/// Histogram of a strided sample of the input (about 4096 bytes).
pub fn sample(input: &[u8], h: &mut [u32; 256]) {
    let n = input.len();
    let st = n / 4096 + 1;
    let mut k = 0usize;
    let mut c = 0usize;
    while k < n && c < 8192 {
        let b = (input[k] as usize) % 256;
        h[b] = h[b].wrapping_add(1);
        k = k.wrapping_add(st);
        c += 1;
    }
}

/// Order-0 entropy of the histogram in 1/256 bits per symbol.
pub fn entropy256(h: &[u32; 256]) -> usize {
    let mut tot = 0u64;
    let mut acc = 0u64;
    let mut i = 0usize;
    while i < 256 {
        let c = h[i];
        tot = tot.wrapping_add(c as u64);
        acc = if c > 0 { acc.wrapping_add((c as u64).wrapping_mul(lg8(c))) } else { acc };
        i += 1;
    }
    let t32 = if tot > 4000000000 { 4000000000u32 } else { tot as u32 };
    let a = lg8(t32);
    let b = if tot == 0 { a } else { acc / tot };
    if a > b { (a - b) as usize } else { 0 }
}

/// Per mille of the sampled bytes in `lo .. hi`.
pub fn share(h: &[u32; 256], lo: usize, hi: usize) -> usize {
    let mut t = 0usize;
    let mut s = 0usize;
    let mut i = 0usize;
    while i < 256 {
        let c = h[i] as usize;
        t = t.wrapping_add(c);
        s = if i >= lo && i < hi { s.wrapping_add(c) } else { s };
        i += 1;
    }
    if t == 0 { 0 } else { s.wrapping_mul(1000) / t }
}

/// 1 when the sampled entropy `e` marks a genome-like input (few cheap literals).
pub fn low_mode(e: usize) -> usize {
    if e >= ELO && e < HLOW { 1 } else { 0 }
}

/// Literal cost (quarter bits): from the sampled entropy in low mode, else LITQ.
pub fn lit_cost(e: usize, low: usize) -> usize {
    let q = (e / 64).wrapping_add(LADJ);
    let q2 = if q < 6 { 6 } else if q > 36 { 36 } else { q };
    if low == 1 { q2 } else { LITQ }
}

/// 1 when the input should use 3-byte hash chains (M3 = 2: always; 1: by rule).
pub fn m3_mode(h: &[u32; 256], e: usize) -> usize {
    let z = share(h, 0, 1);
    let a = if e >= M3E { 1usize } else { 0usize };
    let b = if z >= M3Z { 1usize } else { 0usize };
    if M3 == 2 { 1 } else if M3 == 1 { a & b } else { 0 }
}

/// 1 when the 3-byte table should be used: binary-ish or non-ASCII input of moderate entropy.
pub fn h3_mode(h: &[u32; 256], e: usize) -> usize {
    let hi = share(h, 128, 256);
    let ctl = share(h, 0, 9);
    let a = if hi >= H3HI { 1usize } else { 0usize };
    let b = if ctl >= H3CTL { 1usize } else { 0usize };
    let c = if e < H3E { 1usize } else { 0usize };
    if H3 == 2 { 1 } else if H3 == 1 { (a | b) & c } else { 0 }
}

/// 1 for large numeric text: at least DIGN per mille digits, few bytes >= 128 or < 9, not genome-like.
pub fn numeric(h: &[u32; 256], n: usize, low: usize) -> usize {
    let dig = share(h, 48, 58);
    let hi = share(h, 128, 256);
    let ctl = share(h, 0, 9);
    let txt = if hi < 50 && ctl < 50 { 1usize } else { 0usize };
    let big = if n >= NBIG { 1usize } else { 0usize };
    let d = if dig >= DIGN { 1usize } else { 0usize };
    if low == 1 { 0 } else { txt & big & d }
}

// ------------------------------------------------------------------ match finding (search only)

/// Walk the chain from `start` (pos+1 encoded, 0 = none) for the candidate with the best score
/// among those longer than `bl0` and scoring more than `bs0`. Returns `len | dist << 9 | score << 25`
/// (0 if none). Candidates stay inside the 32K window; the walk stops at `NICE` or `cap`.
pub fn walk(input: &[u8], prev: &[u32; 65536], pos: usize, start: usize, cap: usize, probes: usize, bl0: usize, bs0: usize, litq: usize) -> usize {
    let lim = pos.saturating_sub(32768);
    let stop = if cap < NICE { cap } else { NICE };
    let mut cur = start;
    let mut k = 0usize;
    let mut bl = bl0;
    let mut bs = bs0;
    let mut bd = 0usize;
    let mut off = if bl >= 3 { bl - 3 } else { 0 };
    let mut want = ld4(input, pos.wrapping_add(off));
    while k < probes && cur > lim && bl < stop {
        let c = cur - 1;
        if ld4(input, c.wrapping_add(off)) == want {
            let l = fast_len(input, c, pos, cap);
            let d = pos.wrapping_sub(c);
            let s = if l > bl { score(l, d, litq) } else { 0 };
            let better = if l > bl { if s > bs { 1usize } else { 0usize } } else { 0usize };
            bd = if better == 1 { d } else { bd };
            bs = if better == 1 { s } else { bs };
            bl = if better == 1 { l } else { bl };
            if better == 1 {
                off = if bl >= 3 { bl - 3 } else { 0 };
                want = ld4(input, pos.wrapping_add(off));
            }
        }
        cur = prev[c % 65536] as usize;
        k += 1;
    }
    if bd > 0 {
        bl | bd.wrapping_mul(512) | bs.wrapping_mul(33554432)
    } else {
        0
    }
}

/// Lazy-path copy of `walk` (a separate function keeps both inlined at their single call sites).
/// Walk the chain from `start` (pos+1 encoded, 0 = none) for the candidate with the best score
/// among those longer than `bl0` and scoring more than `bs0`. Returns `len | dist << 9 | score << 25`
/// (0 if none). Candidates stay inside the 32K window; the walk stops at `NICE` or `cap`.
pub fn lwalk(input: &[u8], prev: &[u32; 65536], pos: usize, start: usize, cap: usize, probes: usize, bl0: usize, bs0: usize, litq: usize) -> usize {
    let lim = pos.saturating_sub(32768);
    let stop = if cap < NICE { cap } else { NICE };
    let mut cur = start;
    let mut k = 0usize;
    let mut bl = bl0;
    let mut bs = bs0;
    let mut bd = 0usize;
    let mut off = if bl >= 3 { bl - 3 } else { 0 };
    let mut want = ld4(input, pos.wrapping_add(off));
    while k < probes && cur > lim && bl < stop {
        let c = cur - 1;
        if ld4(input, c.wrapping_add(off)) == want {
            let l = fast_len(input, c, pos, cap);
            let d = pos.wrapping_sub(c);
            let s = if l > bl { score(l, d, litq) } else { 0 };
            let better = if l > bl { if s > bs { 1usize } else { 0usize } } else { 0usize };
            bd = if better == 1 { d } else { bd };
            bs = if better == 1 { s } else { bs };
            bl = if better == 1 { l } else { bl };
            if better == 1 {
                off = if bl >= 3 { bl - 3 } else { 0 };
                want = ld4(input, pos.wrapping_add(off));
            }
        }
        cur = prev[c % 65536] as usize;
        k += 1;
    }
    if bd > 0 {
        bl | bd.wrapping_mul(512) | bs.wrapping_mul(33554432)
    } else {
        0
    }
}

/// The 1-deep 3-byte candidate at `pos` from entry `s3` (pos+1 encoded): `3 | dist << 9 | score << 25`
/// or 0.
pub fn cand3(input: &[u8], pos: usize, s3: usize, cap: usize, bs0: usize, litq: usize) -> usize {
    if s3 == 0 || s3 > pos || cap < 3 {
        return 0;
    }
    let c = s3 - 1;
    let d = pos - c;
    if d > MAX3 || (ld4(input, c) ^ ld4(input, pos)) & 16777215 != 0 {
        return 0;
    }
    let s = score(3, d, litq);
    if s > bs0 {
        3 | d.wrapping_mul(512) | s.wrapping_mul(33554432)
    } else {
        0
    }
}

/// With `probes > 0`: insert `pos` into the chains, then walk them (see `walk`); with nothing found
/// and `h3on == 1`, try the 3-byte table. 0 when `probes == 0`.
pub fn search(input: &[u8], head: &mut [u32; 65536], prev: &mut [u32; 65536], head3: &mut [u32; 16384], shorts: &[u32; 4096], pos: usize, probes: usize, bl0: usize, bs0: usize, litq: usize, hs: u32, h3on: usize) -> usize {
    let n = input.len();
    if probes == 0 || n < 16 || pos > n - 16 {
        return 0;
    }
    let node = prev[pos % 65536];
    let start = node as usize;
    let s3 = if h3on == 1 { shorts[pos % 4096] as usize } else { 0 };
    let rem = n - pos - 8;
    let cap = if rem < 258 { rem } else { 258 };
    let w2 = walk(input, prev, pos, start, cap, probes, bl0, bs0, litq);
    if w2 != 0 || s3 == 0 || bl0 >= 3 {
        w2
    } else {
        cand3(input, pos, s3, cap, bs0, litq)
    }
}

/// With `on == 1`: enter `pos` into the 3-byte table and return the entry it replaced; else 0.
pub fn upd3(input: &[u8], head3: &mut [u32; 16384], pos: usize, on: usize) -> usize {
    if on == 1 {
        let g = hash3(ld4(input, pos)) % 16384;
        let s3 = head3[g] as usize;
        head3[g] = (pos as u32).wrapping_add(1);
        s3
    } else {
        0
    }
}

/// Insert positions `from .. to` into the chains.
pub fn insert_range(input: &[u8], head: &mut [u32; 65536], prev: &mut [u32; 32768], from: usize, to: usize, hs: u32) {
    let lim = input.len().saturating_sub(16);
    let mut p = from;
    while p < to && p <= lim {
        let h = hashp(input, p, hs) % 65536;
        prev[p % 32768] = head[h];
        head[h] = (p as u32).wrapping_add(1);
        p += 1;
    }
}

/// `insert_range` that also updates the 3-byte table.
pub fn insert_range3(input: &[u8], head: &mut [u32; 65536], prev: &mut [u32; 32768], head3: &mut [u32; 16384], from: usize, to: usize, hs: u32) {
    let lim = input.len().saturating_sub(16);
    let mut p = from;
    while p < to && p <= lim {
        let h = hashp(input, p, hs) % 65536;
        prev[p % 32768] = head[h];
        head[h] = (p as u32).wrapping_add(1);
        head3[hash3(ld4(input, p)) % 16384] = (p as u32).wrapping_add(1);
        p += 1;
    }
}

/// Insert the inside `from .. to` of an emitted match: its first IH and last IT positions.
pub fn insert_match(input: &[u8], head: &mut [u32; 65536], prev: &mut [u32; 32768], head3: &mut [u32; 16384], from: usize, to: usize, hs: u32, h3on: usize) {
    let a = from.wrapping_add(IH);
    let a2 = if a < to { a } else { to };
    let b = to.wrapping_sub(IT);
    let b2 = if b > a2 { if b < to { b } else { a2 } } else { a2 };
    if h3on == 1 {
        insert_range3(input, head, prev, head3, from, a2, hs);
        if b2 < to {
            insert_range3(input, head, prev, head3, b2, to, hs);
        }
    } else {
        insert_range(input, head, prev, from, a2, hs);
        if b2 < to {
            insert_range(input, head, prev, b2, to, hs);
        }
    }
}

// ------------------------------------------------------------------ trusted core

/// How many bytes agree at `a` and `b`, up to `cap`. The emission's byte-wise check.
/// Trusted: little-endian 8-byte word at `p` (0 when out of range).
pub fn tw8(input: &[u8], p: usize) -> u64 {
    let n = input.len();
    if n < 8 || p > n - 8 {
        return 0;
    }
    (input[p] as u64)
        + (input[p + 1] as u64) * 256
        + (input[p + 2] as u64) * 65536
        + (input[p + 3] as u64) * 16777216
        + (input[p + 4] as u64) * 4294967296
        + (input[p + 5] as u64) * 1099511627776
        + (input[p + 6] as u64) * 281474976710656
        + (input[p + 7] as u64) * 72057594037927936
}

/// Trusted: little-endian 4-byte word at `p` (0 when out of range).
pub fn tw4(input: &[u8], p: usize) -> u32 {
    let n = input.len();
    if n < 4 || p > n - 4 {
        return 0;
    }
    (input[p] as u32) + (input[p + 1] as u32) * 256 + (input[p + 2] as u32) * 65536 + (input[p + 3] as u32) * 16777216
}

/// Trusted: 1 iff `cap >= 8`, `cap - l < 8` and the 8-byte words at `a + cap - 8` and `b + cap - 8` are equal.
pub fn tail_eq(input: &[u8], a: usize, b: usize, cap: usize, l: usize) -> usize {
    if cap < 8 || cap - l >= 8 {
        return 0;
    }
    if tw8(input, a + (cap - 8)) == tw8(input, b + (cap - 8)) {
        1
    } else {
        0
    }
}

/// Trusted: 1 iff `4 <= cap < 8` and the 4-byte words at `a`, `b` and at `a + cap - 4`, `b + cap - 4` are equal.
pub fn short_eq(input: &[u8], a: usize, b: usize, cap: usize) -> usize {
    if cap < 4 || cap >= 8 {
        return 0;
    }
    if tw4(input, a) != tw4(input, b) {
        return 0;
    }
    if tw4(input, a + (cap - 4)) == tw4(input, b + (cap - 4)) {
        1
    } else {
        0
    }
}

/// Trusted: a length `l <= cap` over which the bytes at `a` and `b` provably agree, found with word compares:
/// 8-byte steps, then one overlapping 8-byte compare at `cap - 8` (or two 4-byte ones when 4 <= cap < 8); `cap`
/// itself when everything agreed.
pub fn words_eq(input: &[u8], a: usize, b: usize, cap: usize) -> usize {
    let mut l = 0usize;
    while cap - l >= 8 && tw8(input, a + l) == tw8(input, b + l) {
        l += 8;
    }
    let big = tail_eq(input, a, b, cap, l);
    let small = short_eq(input, a, b, cap);
    if big == 1 {
        cap
    } else if small == 1 {
        cap
    } else {
        l
    }
}

/// Trusted: how many bytes agree at `a` and `b`, up to `cap` (word compares, then bytes).
pub fn match_len(input: &[u8], a: usize, b: usize, cap: usize) -> usize {
    let mut l = words_eq(input, a, b, cap);
    while l < cap && input[b + l] == input[a + l] {
        l += 1;
    }
    l
}

/// True iff `(ch, d)` at `pos` is in range and its bytes agree.
#[inline(always)]
pub fn verified(input: &[u8], pos: usize, d: usize, ch: usize) -> bool {
    let n=input.len();
    if ch<3 || ch>258 || d<1 || d>32768 || d>pos || pos>n || ch>n-pos {return false;}
    let a=pos-d;
    if ch>=8 && ch<=16 {
        tw8(input,a)==tw8(input,pos) && tw8(input,a+ch-8)==tw8(input,pos+ch-8)
    } else if ch>=4 && ch<8 {
        tw4(input,a)==tw4(input,pos) && tw4(input,a+ch-4)==tw4(input,pos+ch-4)
    } else if ch==3 {
        input[a]==input[pos] && input[a+1]==input[pos+1] && input[a+2]==input[pos+2]
    } else {match_len(input,a,pos,ch)>=ch}
}

/// Trusted: `cnt >= 1` literals from `pos0` (stopping at the input end).
#[inline(always)]
pub fn emit_lits(input: &[u8], out: &mut [u32], pos0: usize, cnt: usize, ntok0: usize) -> (usize, usize) {
    let n = input.len();
    let cnt1 = if cnt == 0 { 1 } else { cnt };
    let mut k = pos0;
    let mut c = 0usize;
    let mut ntok = ntok0;
    while k < n && c < cnt1 {
        out[ntok] = input[k] as u32;
        ntok += 1;
        k += 1;
        c += 1;
    }
    (ntok, k)
}

/// Trusted: the match `(l, d)` at `pos` if it verifies, else `lits` literals.
#[inline(always)]
pub fn emit_step(input: &[u8], out: &mut [u32], pos: usize, d: usize, l: usize, lits: usize, ntok: usize) -> (usize, usize) {
    if verified(input, pos, d, l) {
        out[ntok] = 16777216u32 + ((d - 1) as u32) * 256 + ((l - 3) as u32);
        (ntok + 1, pos + l)
    } else {
        emit_lits(input, out, pos, lits, ntok)
    }
}

// ------------------------------------------------------------------ the parse loop

/// The lazy check at `q` (= match position + 1) with `go == 1`: enter `q` into the chains and test the most
/// recent chain candidate against the current match (`l1` bytes, score `sv1`). Returns `len | dist << 9 |
/// score << 25` when that candidate is at least as long and scores higher, else 0. `go == 0`: does nothing.
pub fn lazy_probe(input: &[u8], head: &mut [u32; 65536], prev: &mut [u32; 65536], head3: &mut [u32; 16384], q: usize, go: usize, p2: usize, l1: usize, sv1: usize, litq: usize, hs: u32, h3on: usize, start: usize) -> usize {
    let n = input.len();
    if go == 0 || n < 16 || q > n - 16 {
        return 0;
    }
    let rem = n - q - 8;
    let cap = if rem < 258 { rem } else { 258 };
    let pr = if l1 >= GOODL { P2G } else { p2 };
    lwalk(input, prev, q, start, cap, pr, l1.wrapping_sub(1), sv1, litq)
}

/// 1 when the lazy candidate `(l2, d2)` found at `pos + 1` also covers `pos` (so it can start there).
#[inline(always)]
pub fn ext_ok(input: &[u8], pos: usize, l2: usize, d2: usize) -> usize {
    let n = input.len();
    if EXT == 0 || l2 < 3 || l2 >= 258 || d2 < 1 || d2 > pos || pos >= n {
        return 0;
    }
    if input[pos] == input[pos - d2] { 1 } else { 0 }
}


// ============================ jfloor fast-path module v5 (untrusted except the fl_ trusted copies) ==============
// Graft: the base parser's `parse` becomes `main_parse(input, out, lh, pos0, ntok0)` and this module's `parse` runs
//   fl_part(input, out, mode, fh, cf)  -> (ntok, pos): the whole input for modes 1-5, (0, 0) for mode 0,
//   main_parse(input, out, &fh, pos, ntok) -> the base parser from `pos` (a no-op when pos == n).
// Modes (fl_mode, loop-free, from a strided 4K-byte sample + 16 probe chunks of 256 bytes):
//   4 RLE  : one byte value >= 75% of the sample (sparse): distance-1 runs, no tables;
//   5 LAZY : small files (< 64 KB), database-like binaries (zero bytes but mostly printable), high-entropy data
//            (images, f32 weights, archives): the module's own price-lazy parser with a per-class config `cf`;
//   2 DNA  : 4-symbol alphabet (FASTA): literal runs over cheap bytes, cost-checked matches at expensive bytes;
//   1 LIT  : 2-periodic 16-bit weights (bf16/f16) and skewed-uniform int8 weights (q8, no repeats at all);
//   0      : the base parser.
// The module has its own copies of the trusted kit functions (fl_match_len, fl_verified, fl_emit_lits,
// fl_emit_step) so the base keeps its own emit_step/emit_lits with one caller each (sharing them made LLVM
// outline the base's emit_step: +1% instructions on every text file).

pub const FL_PMIN: usize = 8192;
pub const FL_PNC: usize = 16;
pub const FL_PCH: usize = 256;
pub const FL_RLE_TOP: usize = 192;
pub const FL_DNA_THR: u32 = 64;
pub const FL_DNA_DEPTH: usize = 64;
pub const FL_DNA_M0: usize = 12;
pub const FL_CMAX: u32 = 192;
pub const FL_HIGH: usize = 104;
pub const FL_DBZ: usize = 8;
pub const FL_DBNP: usize = 110;
pub const FL_USE_T: usize = 1;
pub const FL_USE_D: usize = 0;
pub const FL_USE_H: usize = 0;
pub const FL_USE_LIT: usize = 1;
// class configs (T: small files, D: database-like, H: high entropy)
pub const FT_DEPTH: usize = 16;
pub const FT_DEPTH2: usize = 2;
pub const FT_LAZY: usize = 259;
pub const FT_NICE: usize = 258;
pub const FT_IH: usize = 64;
pub const FT_IT: usize = 16;
pub const FT_ACC: usize = 63;
pub const FD_DEPTH: usize = 12;
pub const FD_DEPTH2: usize = 2;
pub const FD_LAZY: usize = 259;
pub const FD_NICE: usize = 258;
pub const FD_IH: usize = 64;
pub const FD_IT: usize = 16;
pub const FD_ACC: usize = 63;
pub const FH_DEPTH: usize = 6;
pub const FH_DEPTH2: usize = 2;
pub const FH_LAZY: usize = 32;
pub const FH_NICE: usize = 64;
pub const FH_IH: usize = 64;
pub const FH_IT: usize = 16;
pub const FH_ACC: usize = 7;
pub const FL_GOOD: usize = 8;
pub const FL_LITQ: usize = 32;
pub const FL_LADJ: usize = 4;
pub const FL_HLOW: usize = 900;
pub const FL_C0Q: usize = 44;
// ---- lane E2 garbage switches: G3 = 3-byte key, OLDEST occurrence in the window, every hit a 3-byte match
pub const G_JOIN: usize = 1;  // 0: no backward token joining (public_back_gate never folds; faster, worse ratio)
pub const G3_DNA: usize = 0;   // genome (fl mode 2): the garbage parser instead of the DNA price parser
pub const G3_TEXT: usize = 0;  // base inputs (fl mode 0): the garbage parser instead of main_parse
pub const G3_TINY: usize = 0;  // inputs of at most G3_TINY_N bytes (one encoder block): literal-only
pub const G3_TINY_N: usize = 16384;
pub const G3_WIN: usize = 32768;
pub const G3_HIGH: usize = 0;  // high-entropy inputs (sampled entropy >= FL_HIGH) that are not weights: literal-only
// ---- lane E2 phase-2 class lanes (honest: fewer tokens at lower parse cost)
pub const FL_BF_ON: usize = 1;   // 2-byte-periodic weights with a low-entropy high byte (bf16): 3-byte guess lane
pub const FL_BF_ENT: usize = 52; // high-byte phase entropy bound (1/16 bits): bf16 44-45, f16 61-64
pub const FL_SM_ON: usize = 1;   // inputs of at most FL_SM_N bytes: cached greedy, thin alphabets, replay
pub const FL_SM_N: usize = 65536;
pub const FL_SM_MIN: usize = 4;
pub const FL_SM_IH: usize = 2;
pub const FL_SM_DT: usize = 1200;  // ns: one live symbol's package-merge cost per block (time-only optimum ~800; 600 keeps more ratio)
pub const FL_SM_LIT: usize = 6;   // ns per literal token
pub const FL_SM_MAT: usize = 26;  // ns per match token
pub const FL_IM_ON: usize = 1;   // high-entropy non-weights inputs (images): sparse-probe lane instead of literal-only
pub const FL_IM_MIN: usize = 8;  // shortest match taken
pub const FL_IM_PROBES: usize = 8192; // after this many probes ...
pub const FL_IM_EARLY: usize = 8;     // ... fewer matches than this: the lane sleeps (stride FL_IM_SLEEP) until a match wakes it
pub const FL_IM_SLEEP: usize = 16;
pub const FL_BF_DMIN: usize = 129; // bf16 lane: guessed matches nearer than this are not taken (their distance codes are the rare live symbols)
pub const FL_QRLE_N: usize = 32768; // inputs of at least this size: a 1 K-sample RLE class check before the full sample
pub const FL_TH: usize = 0;        // base text lane: per-block thinning of rare length / distance codes
pub const FL_TH_TL: usize = 25;    // length code kept when its expected count per block is at least this ...
pub const FL_TH_RL: usize = 60;    // ... or re-enabled once the block has this many
pub const FL_TH_TD: usize = 80;    // distance code kept when its expected bytes per block are at least this ...
pub const FL_TH_RD: usize = 200;   // ... or re-enabled once the block has this many bytes
pub const FL_IM_STEP: usize = 5; // probe stride base: the stride cycles through STEP, STEP + 1, STEP + 2
pub const FL_IM_FLAT: usize = 112; // every byte phase at least this entropy (1/16 bits): images 123-125, f32 41-45
pub const FL_DNA8_ON: usize = 1; // genome (fl mode 2) honest lane: 8-byte-key greedy, min length 9
pub const FL_DNA8_MIN: usize = 6;
pub const FL_DNA8_KEY: usize = 6; // key bytes (6 or 8)
pub const FL_MC_ON: usize = 1;   // zero-rich binaries (G's lane-b class, machine code): single-table 3-byte greedy lane
pub const FL_MC_IH: usize = 2;
pub const FL_MC_MIN: usize = 3;  // shortest match taken
pub const FL_MC_D3: usize = 32768; // 3-byte matches only up to this distance (farther: literals)
pub const FL_MC_Z0: usize = 150; // zero share (per mille of the sample) from which the lane applies
pub const FL_SM_RLE_DT: usize = 500; // sparse inputs: the thinning threshold of the cached RLE parse
pub const FL_RLE_MIN: usize = 32; // sparse inputs: runs shorter than this are literals (the rare length codes)

// ---------------------------------------------------------------- trusted core (floor copy)

/// Byte-wise common prefix length (trusted).
/// Trusted: little-endian 8-byte word at `p` (0 when out of range).
pub fn fl_tw8(input: &[u8], p: usize) -> u64 {
    let n = input.len();
    if n < 8 || p > n - 8 {
        return 0;
    }
    (input[p] as u64)
        + (input[p + 1] as u64) * 256
        + (input[p + 2] as u64) * 65536
        + (input[p + 3] as u64) * 16777216
        + (input[p + 4] as u64) * 4294967296
        + (input[p + 5] as u64) * 1099511627776
        + (input[p + 6] as u64) * 281474976710656
        + (input[p + 7] as u64) * 72057594037927936
}

/// Trusted: little-endian 4-byte word at `p` (0 when out of range).
pub fn fl_tw4(input: &[u8], p: usize) -> u32 {
    let n = input.len();
    if n < 4 || p > n - 4 {
        return 0;
    }
    (input[p] as u32) + (input[p + 1] as u32) * 256 + (input[p + 2] as u32) * 65536 + (input[p + 3] as u32) * 16777216
}

/// Trusted: 1 iff `cap >= 8`, `cap - l < 8` and the 8-byte words at `a + cap - 8` and `b + cap - 8` are equal.
pub fn fl_tail_eq(input: &[u8], a: usize, b: usize, cap: usize, l: usize) -> usize {
    if cap < 8 || cap - l >= 8 {
        return 0;
    }
    if fl_tw8(input, a + (cap - 8)) == fl_tw8(input, b + (cap - 8)) {
        1
    } else {
        0
    }
}

/// Trusted: 1 iff `4 <= cap < 8` and the 4-byte words at `a`, `b` and at `a + cap - 4`, `b + cap - 4` are equal.
pub fn fl_short_eq(input: &[u8], a: usize, b: usize, cap: usize) -> usize {
    if cap < 4 || cap >= 8 {
        return 0;
    }
    if fl_tw4(input, a) != fl_tw4(input, b) {
        return 0;
    }
    if fl_tw4(input, a + (cap - 4)) == fl_tw4(input, b + (cap - 4)) {
        1
    } else {
        0
    }
}

/// Trusted: a length `l <= cap` over which the bytes at `a` and `b` provably agree, found with word compares:
/// 8-byte steps, then one overlapping 8-byte compare at `cap - 8` (or two 4-byte ones when 4 <= cap < 8); `cap`
/// itself when everything agreed.
pub fn fl_words_eq(input: &[u8], a: usize, b: usize, cap: usize) -> usize {
    let mut l = 0usize;
    while cap - l >= 8 && fl_tw8(input, a + l) == fl_tw8(input, b + l) {
        l += 8;
    }
    let big = fl_tail_eq(input, a, b, cap, l);
    let small = fl_short_eq(input, a, b, cap);
    if big == 1 {
        cap
    } else if small == 1 {
        cap
    } else {
        l
    }
}

/// Trusted: how many bytes agree at `a` and `b`, up to `cap` (word compares, then bytes).
pub fn fl_match_len(input: &[u8], a: usize, b: usize, cap: usize) -> usize {
    let mut l = fl_words_eq(input, a, b, cap);
    while l < cap && input[b + l] == input[a + l] {
        l += 1;
    }
    l
}

/// True iff `(ch, d)` at `pos` is in range and its bytes agree (trusted).
pub fn fl_verified(input: &[u8], pos: usize, d: usize, ch: usize) -> bool {
    let n = input.len();
    if ch < 3 || ch > 258 || d < 1 || d > 32768 || d > pos || pos > n || ch > n - pos {
        return false;
    }
    let v = fl_match_len(input, pos - d, pos, ch);
    v >= ch
}

/// Trusted: `cnt >= 1` literals from `pos0` (stopping at the input end).
pub fn fl_emit_lits(input: &[u8], out: &mut [u32], pos0: usize, cnt: usize, ntok0: usize) -> (usize, usize) {
    let n = input.len();
    let cnt1 = if cnt == 0 { 1 } else { cnt };
    let mut k = pos0;
    let mut c = 0usize;
    let mut ntok = ntok0;
    while k < n && c < cnt1 {
        out[ntok] = input[k] as u32;
        ntok += 1;
        k += 1;
        c += 1;
    }
    (ntok, k)
}

/// Trusted: the match `(l, d)` at `pos` if it verifies, else `lits` literals.
pub fn fl_emit_step(input: &[u8], out: &mut [u32], pos: usize, d: usize, l: usize, lits: usize, ntok: usize) -> (usize, usize) {
    if fl_verified(input, pos, d, l) {
        out[ntok] = 16777216u32 + ((d - 1) as u32) * 256 + ((l - 3) as u32);
        (ntok + 1, pos + l)
    } else {
        fl_emit_lits(input, out, pos, lits, ntok)
    }
}

// ---------------------------------------------------------------- loads, compares, hashes (search only)

/// `input[i]`, or 0 out of range.
pub fn fl_byte(input: &[u8], i: usize) -> usize {
    if i < input.len() {
        input[i] as usize
    } else {
        0
    }
}

/// Little-endian 4-byte load at `p`; 0 when out of range.
pub fn fl_ld4(input: &[u8], p: usize) -> u32 {
    let n = input.len();
    if n < 4 || p > n - 4 {
        return 0;
    }
    ((input[p + 3] as u32) << 24) | ((input[p + 2] as u32) << 16) | ((input[p + 1] as u32) << 8) | (input[p] as u32)
}

/// Little-endian 8-byte load at `p` (two 4-byte halves); 0 when out of range.
pub fn fl_ld8(input: &[u8], p: usize) -> u64 {
    let n = input.len();
    if n < 8 || p > n - 8 {
        return 0;
    }
    let hi = ((input[p + 7] as u32) << 24) | ((input[p + 6] as u32) << 16) | ((input[p + 5] as u32) << 8) | (input[p + 4] as u32);
    let lo = ((input[p + 3] as u32) << 24) | ((input[p + 2] as u32) << 16) | ((input[p + 1] as u32) << 8) | (input[p] as u32);
    ((hi as u64) << 32) | (lo as u64)
}

/// Common prefix of `a < b`, at most `cap` (word compare; search only, never trusted).
#[inline(always)]
pub fn fl_len(input: &[u8], a: usize, b: usize, cap: usize) -> usize {
    let mut l = 0usize;
    let mut go = 1usize;
    let mut it = 0usize;
    while go == 1 && it < 40 {
        if l < cap {
            let x = fl_ld8(input, a.wrapping_add(l)) ^ fl_ld8(input, b.wrapping_add(l));
            let low = x & 0u64.wrapping_sub(x);
            let k = if x == 0 { 8 } else { (63u32.wrapping_sub(low.leading_zeros()) / 8) as usize };
            l = l.wrapping_add(k);
            go = if x == 0 { 1 } else { 0 };
        } else {
            go = 0;
        }
        it += 1;
    }
    if l > cap {
        cap
    } else {
        l
    }
}

/// 16-bit hash of the word at `p` shifted left by `hsh` (32: first 4 bytes, 0: first 8 bytes).
pub fn fl_hashp(input: &[u8], p: usize, hsh: u64) -> usize {
    let v = fl_ld8(input, p) << (hsh % 64);
    ((v.wrapping_mul(0x9E3779B97F4A7C15) >> 48) as usize) % 65536
}

// ---------------------------------------------------------------- statistics and costs (search only)

/// log2(1 + i/16) in 1/16 bits.
pub const FL_LOGF: [u32; 16] = [0, 1, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 15];

/// log2(f) in 1/16 bits (0 for f = 0).
pub fn fl_log16(f: u32) -> u32 {
    let lz = f.leading_zeros();
    let top = ((((f as u64) << ((lz as u64).wrapping_add(1) % 64)) >> 28) as usize) % 16;
    if f == 0 {
        0
    } else {
        (31u32.wrapping_sub(lz)).wrapping_mul(16).wrapping_add(FL_LOGF[top])
    }
}

/// Strided byte histogram of about 4096 samples.
pub fn fl_sample(input: &[u8], h: &mut [u32; 256]) {
    let n = input.len();
    let st = n / 4096 + 1;
    let mut k = 0usize;
    let mut c = 0usize;
    while k < n && c < 8192 {
        let b = fl_byte(input, k) % 256;
        h[b] = h[b].wrapping_add(1);
        k = k.wrapping_add(st);
        c += 1;
    }
}

/// Literal cost per byte value (1/16 bits) from the histogram: log2(total / f), unseen bytes FL_CMAX.
#[inline(always)]
pub fn fl_costs(h: &[u32; 256], cost: &mut [u32; 256]) {
    let mut t = 0u32;
    let mut i = 0usize;
    while i < 256 {
        t = t.wrapping_add(h[i]);
        i += 1;
    }
    let lt = fl_log16(t);
    let mut j = 0usize;
    while j < 256 {
        let f = h[j];
        let c = lt.wrapping_sub(fl_log16(f));
        cost[j] = if f == 0 { FL_CMAX } else if c > FL_CMAX { FL_CMAX } else { c };
        j += 1;
    }
}

/// Order-0 entropy in 1/16 bits per byte of the 256 bins starting at `base` of `h`.
pub fn fl_ent(h: &[u32; 1024], base: usize) -> usize {
    let mut t = 0u32;
    let mut i = 0usize;
    while i < 256 {
        t = t.wrapping_add(h[base.wrapping_add(i) % 1024]);
        i += 1;
    }
    let lt = fl_log16(t);
    let mut bits = 0usize;
    let mut j = 0usize;
    while j < 256 {
        let f = h[base.wrapping_add(j) % 1024];
        let c = lt.wrapping_sub(fl_log16(f)) as usize;
        bits = if f > 0 { bits.wrapping_add((f as usize).wrapping_mul(c)) } else { bits };
        j += 1;
    }
    let tt = if t == 0 { 1usize } else { t as usize };
    bits / tt
}

/// Sample statistics packed into one word: bits 0-9 entropy (1/16 bits), 10-18 top byte share (1/256),
/// 19-27 zero-byte share, 28-36 non-printable share, 37-45 share of the byte values with share >= 1/8,
/// 46-49 number of such byte values.
pub fn fl_stats(h: &[u32; 256]) -> u64 {
    let mut t = 0u32;
    let mut i = 0usize;
    while i < 256 {
        t = t.wrapping_add(h[i]);
        i += 1;
    }
    let lt = fl_log16(t);
    let mut bits = 0usize;
    let mut top = 0u32;
    let mut np = 0usize;
    let mut big = 0usize;
    let mut bigsum = 0usize;
    let mut j = 0usize;
    while j < 256 {
        let f = h[j];
        let c = lt.wrapping_sub(fl_log16(f)) as usize;
        bits = if f > 0 { bits.wrapping_add((f as usize).wrapping_mul(c)) } else { bits };
        top = if f > top { f } else { top };
        let ctl = if j < 32 { if j == 9 || j == 10 || j == 13 { 0usize } else { 1usize } } else { 0usize };
        let npj = if j >= 127 { 1usize } else { ctl };
        np = if npj == 1 { np.wrapping_add(f as usize) } else { np };
        let isbig = if (f as usize).wrapping_mul(8) >= t as usize { 1usize } else { 0usize };
        big = big.wrapping_add(isbig);
        bigsum = if isbig == 1 { bigsum.wrapping_add(f as usize) } else { bigsum };
        j += 1;
    }
    let tt = if t == 0 { 1usize } else { t as usize };
    let e = ((bits / tt) % 1024) as u64;
    let tp = (((top as usize).wrapping_mul(256) / tt) % 512) as u64;
    let z = (((h[0] as usize).wrapping_mul(256) / tt) % 512) as u64;
    let nps = ((np.wrapping_mul(256) / tt) % 512) as u64;
    let bs = ((bigsum.wrapping_mul(256) / tt) % 512) as u64;
    let bg = (big % 16) as u64;
    e | (tp << 10) | (z << 19) | (nps << 28) | (bs << 37) | (bg << 46)
}

/// Chunk `s .. s + FL_PCH`: 4-phase byte histograms (phase = absolute position mod 4) into `ph`, and the number
/// of positions whose most recent same-3-byte-hash position in the chunk repeats 4 bytes.
pub fn fl_probe_chunk(input: &[u8], tab: &mut [u32; 4096], ph: &mut [u32; 1024], s: usize) -> usize {
    let mut p = s;
    let mut k = 0usize;
    let mut c4 = 0usize;
    while k < FL_PCH {
        let x = fl_ld8(input, p);
        let b = (x as usize) % 256;
        let slot = (p % 4).wrapping_mul(256).wrapping_add(b) % 1024;
        ph[slot] = ph[slot].wrapping_add(1);
        let x3 = (x as u32) & 16777215;
        let h = (x3.wrapping_mul(2654435761) >> 20) as usize % 4096;
        let q = tab[h] as usize;
        let y = if q > s && q <= p { fl_ld8(input, q - 1) } else { !x };
        let z = x ^ y;
        c4 = if z & 4294967295 == 0 { c4.wrapping_add(1) } else { c4 };
        tab[h] = (p as u32).wrapping_add(1);
        p = p.wrapping_add(1);
        k += 1;
    }
    c4
}

/// Weights detector: bit 0 iff the probe chunks look like 16-bit floats (bytes alternate between a high-entropy and a
/// low-entropy phase with period 2) or like int8 weights (all phases 6.5-7.6 bits, no 4-byte repeat at all); bit 1
/// iff 2-periodic with a low-entropy phase of at most FL_BF_ENT (bf16-like); bit 2 iff every phase has at least
/// FL_IM_FLAT (flat high entropy: images).
pub fn fl_weights(input: &[u8]) -> usize {
    let n = input.len();
    let mut tab = [0u32; 4096];
    let mut ph = [0u32; 1024];
    let span = n / FL_PNC;
    let mut c4 = 0usize;
    let mut i = 0usize;
    while i < FL_PNC {
        c4 = c4.wrapping_add(fl_probe_chunk(input, &mut tab, &mut ph, i.wrapping_mul(span)));
        i += 1;
    }
    let e0 = fl_ent(&ph, 0);
    let e1 = fl_ent(&ph, 256);
    let e2 = fl_ent(&ph, 512);
    let e3 = fl_ent(&ph, 768);
    let d02 = if e0 > e2 { e0.wrapping_sub(e2) } else { e2.wrapping_sub(e0) };
    let d13 = if e1 > e3 { e1.wrapping_sub(e3) } else { e3.wrapping_sub(e1) };
    let s02 = e0.wrapping_add(e2);
    let s13 = e1.wrapping_add(e3);
    let dev = if s02 > s13 { s02.wrapping_sub(s13) } else { s13.wrapping_sub(s02) };
    let lo = if e0 < e1 { e0 } else { e1 };
    let lo2 = if e2 < e3 { e2 } else { e3 };
    let mn = if lo < lo2 { lo } else { lo2 };
    let hi = if e0 > e1 { e0 } else { e1 };
    let hi2 = if e2 > e3 { e2 } else { e3 };
    let mx = if hi > hi2 { hi } else { hi2 };
    let p2 = if d02 < 8 && d13 < 8 && dev > 32 { 1usize } else { 0usize };
    let q8 = if c4 == 0 && mn >= 104 && mx < 120 && dev < 8 { 1usize } else { 0usize };
    let uniform = if c4 < 4 && mn >= 124 { 1usize } else { 0usize };
    let lowph = if p2 == 1 { if mn <= FL_BF_ENT { 1usize } else { 0usize } } else { 0usize };
    let flat = if mn >= FL_IM_FLAT { 1usize } else { 0usize };
    (p2 | q8 | uniform) | lowph.wrapping_mul(2) | flat.wrapping_mul(4)
}

/// The mode (0 base, 1 LIT, 2 DNA, 4 RLE, 5 LAZY, 6 SMALL, 7 IMAGES) and the class (LAZY: 0 T, 1 D, 2 H; LIT: 1 =
/// bf16-like 2-periodic weights), packed `mode + 8 * class`.
/// Integer flags and nested value-ifs only (no `&&` guarding code, so the extracted model stays small).
pub fn fl_mode(input: &[u8], st: u64) -> usize {
    let n = input.len();
    let e = (st as usize) % 1024;
    let top = ((st >> 10) % 512) as usize;
    let z = ((st >> 19) % 512) as usize;
    let np = ((st >> 28) % 512) as usize;
    let bs = ((st >> 37) % 512) as usize;
    let bg = ((st >> 46) % 16) as usize;
    let rle = if top >= FL_RLE_TOP { if n >= 1024 { 1usize } else { 0usize } } else { 0usize };
    let tiny = if G3_TINY == 1 { if n <= G3_TINY_N { 1usize } else { 0usize } } else { 0usize };
    let sm = if FL_SM_ON == 1 { if n <= FL_SM_N { 1usize } else { 0usize } } else { 0usize };
    let small = if n < FL_PMIN { 1usize } else { 0usize };
    let dna = if bg == 4 { if bs >= 205 { if e < 52 { 1usize } else { 0usize } } else { 0usize } } else { 0usize };
    let high = if e >= FL_HIGH { 1usize } else { 0usize };
    let db = if z >= FL_DBZ { if np < FL_DBNP { 1usize } else { 0usize } } else { 0usize };
    let w = if high == 1 { if FL_USE_LIT == 1 { fl_weights(input) } else { 0 } } else { 0 };
    let bf = if FL_BF_ON == 1 { (w / 2) % 2 } else { 0 };
    let flat = if FL_IM_ON == 1 { (w / 4) % 2 } else { 0 };
    let mh = if w % 2 == 1 { if bf == 1 { 9 } else { 1 } } else if flat == 1 { 7 } else if G3_HIGH == 1 { 1 } else if FL_USE_H == 1 { 21 } else { 0 };
    let md = if FL_USE_D == 1 { 13 } else { 0 };
    let mt = if FL_USE_T == 1 { 5 } else { 0 };
    if rle == 1 {
        4
    } else if tiny == 1 {
        1
    } else if sm == 1 {
        6
    } else if small == 1 {
        mt
    } else if dna == 1 {
        2
    } else if high == 1 {
        mh
    } else if db == 1 {
        md
    } else {
        0
    }
}

/// The LAZY configuration of a class: [depth, depth2, lazy, nice, ih, it, acc].
pub fn fl_config(class: usize, cf: &mut [usize; 8]) {
    cf[0] = if class == 0 { FT_DEPTH } else if class == 1 { FD_DEPTH } else { FH_DEPTH };
    cf[1] = if class == 0 { FT_DEPTH2 } else if class == 1 { FD_DEPTH2 } else { FH_DEPTH2 };
    cf[2] = if class == 0 { FT_LAZY } else if class == 1 { FD_LAZY } else { FH_LAZY };
    cf[3] = if class == 0 { FT_NICE } else if class == 1 { FD_NICE } else { FH_NICE };
    cf[4] = if class == 0 { FT_IH } else if class == 1 { FD_IH } else { FH_IH };
    cf[5] = if class == 0 { FT_IT } else if class == 1 { FD_IT } else { FH_IT };
    cf[6] = if class == 0 { FT_ACC } else if class == 1 { FD_ACC } else { FH_ACC };
}

// ---------------------------------------------------------------- LIT and RLE

/// Trusted-kit emission of the whole input as literals.
pub fn fl_lit_parse(input: &[u8], out: &mut [u32]) -> (usize, usize) {
    let n = input.len();
    fl_emit_lits(input, out, 0, n, 0)
}

/// RLE parse: a distance-1 run match wherever the previous byte repeats >= FL_RLE_MIN times, else one literal.
pub fn fl_rle_parse(input: &[u8], out: &mut [u32]) -> (usize, usize) {
    let n = input.len();
    let mut pos = 0usize;
    let mut ntok = 0usize;
    while pos < n {
        let rem = n - pos;
        let cap = if rem < 258 { rem } else { 258 };
        let l0 = if pos >= 1 { fl_len(input, pos - 1, pos, cap) } else { 0 };
        let l = if l0 >= FL_RLE_MIN { l0 } else { 0 };
        let r = fl_emit_step(input, out, pos, 1, l, 1, ntok);
        let olen = out.len();
        ntok = r.0;
        pos = r.1;
    }
    (ntok, pos)
}

// ---------------------------------------------------------------- DNA

/// Number of consecutive cheap bytes (cost < FL_DNA_THR) from `pos`.
pub fn fl_cheap_run(input: &[u8], cost: &[u32; 256], pos: usize) -> usize {
    let n = input.len();
    let mut k = pos;
    while k < n && cost[input[k] as usize % 256] < FL_DNA_THR {
        k += 1;
    }
    k.wrapping_sub(pos)
}

/// Literal cost (1/16 bits) of the `l` bytes at `pos` (l <= 258).
pub fn fl_span_cost(input: &[u8], cost: &[u32; 256], pos: usize, l: usize) -> usize {
    let mut s = 0usize;
    let mut i = 0usize;
    while i < l && i < 258 {
        s = s.wrapping_add(cost[fl_byte(input, pos.wrapping_add(i)) % 256] as usize);
        i += 1;
    }
    s
}

/// DEFLATE distance extra bits.
pub fn fl_dextra(d: usize) -> usize {
    if d <= 4 {
        0
    } else {
        let x = (d.wrapping_sub(1) as u32) | 1;
        (31u32.wrapping_sub(x.leading_zeros()) as usize).wrapping_sub(1)
    }
}

/// DEFLATE length extra bits.
pub fn fl_lextra(l: usize) -> usize {
    if l < 11 || l >= 258 {
        0
    } else {
        let x = (l.wrapping_sub(3) as u32) | 1;
        (31u32.wrapping_sub(x.leading_zeros()) as usize).wrapping_sub(2)
    }
}

/// 1 iff the match (l, d) at `pos` is estimated cheaper than its literals: FL_DNA_M0 bits + extra bits.
pub fn fl_dna_ok(input: &[u8], cost: &[u32; 256], pos: usize, l: usize, d: usize) -> usize {
    let mc = FL_DNA_M0.wrapping_add(fl_dextra(d)).wrapping_add(fl_lextra(l)).wrapping_mul(16);
    if fl_span_cost(input, cost, pos, l) > mc {
        1
    } else {
        0
    }
}

/// Longest match (ties: the closest) along the chain from `start` (pos+1 encoded). Returns `len | dist << 9`.
pub fn fl_dwalk(input: &[u8], prev: &[u32; 32768], pos: usize, start: usize, cap: usize, depth: usize) -> usize {
    let mut bl = 3usize;
    let mut bd = 0usize;
    let mut cur = start;
    let mut k = 0usize;
    while k < depth && cur > 0 && cur <= pos && pos - (cur - 1) <= 32768 {
        let c = cur - 1;
        if bl < cap && fl_byte(input, c.wrapping_add(bl)) == fl_byte(input, pos.wrapping_add(bl)) {
            let l = fl_len(input, c, pos, cap);
            let take = if l > bl { 1usize } else if l == bl { if bd == 0 { 1usize } else { 0usize } } else { 0usize };
            bd = if take == 1 { pos - c } else { bd };
            bl = if take == 1 { l } else { bl };
        }
        cur = if bl >= cap { 0 } else { prev[c % 32768] as usize };
        k += 1;
    }
    if bd > 0 {
        bl | bd.wrapping_mul(512)
    } else {
        0
    }
}

/// DNA: with `depth > 0`, insert `p` into the 4-byte-hash chains and walk them (depth 0: nothing).
pub fn fl_dsearch(input: &[u8], head: &mut [u32; 65536], prev: &mut [u32; 32768], p: usize, depth: usize) -> usize {
    let n = input.len();
    if depth == 0 || n < 16 || p > n - 16 {
        return 0;
    }
    let h = fl_hashp(input, p, 32);
    let start = head[h] as usize;
    prev[p % 32768] = start as u32;
    head[h] = (p as u32).wrapping_add(1);
    let rem = n - p - 8;
    let cap = if rem < 258 { rem } else { 258 };
    fl_dwalk(input, prev, p, start, cap, depth)
}

/// Insert positions `from .. to` into the chains (hash of the first 4 bytes if hsh = 32, 8 bytes if hsh = 0).
pub fn fl_tinsert(input: &[u8], head: &mut [u16; 16384], prev: &mut [u16; 32768], from: usize, to: usize, hsh: u64) {
    let n = input.len();
    let lim = n.saturating_sub(16);
    let mut p = from;
    while p < to && p <= lim {
        let h = fl_hashp(input, p, hsh) % 16384;
        prev[p % 32768] = head[h];
        head[h] = (p as u16).wrapping_add(1);
        p += 1;
    }
}

pub fn fl_insert(input: &[u8], head: &mut [u32; 65536], prev: &mut [u32; 32768], from: usize, to: usize, hsh: u64) {
    let n = input.len();
    let lim = n.saturating_sub(16);
    let mut p = from;
    while p < to && p <= lim {
        let h = fl_hashp(input, p, hsh);
        prev[p % 32768] = head[h];
        head[h] = (p as u32).wrapping_add(1);
        p += 1;
    }
}

/// DNA parse: literal runs over cheap bytes; at an expensive byte, search and take the match if it is estimated
/// cheaper than its literals. Only searched positions and match interiors enter the chains.
pub fn fl_dna_parse(input: &[u8], out: &mut [u32], cost: &[u32; 256]) -> (usize, usize) {
    let n = input.len();
    let mut head = [0u32; 65536];
    let mut prev = [0u32; 32768];
    let mut pos = 0usize;
    let mut ntok = 0usize;
    while pos < n {
        let cr = fl_cheap_run(input, cost, pos);
        let harg1 = if cr == 0 { FL_DNA_DEPTH } else { 0 };
        let m = fl_dsearch(input, &mut head, &mut prev, pos, harg1);
        let l0 = m % 512;
        let d = (m / 512) % 65536;
        let ok = if l0 >= 3 { fl_dna_ok(input, cost, pos, l0, d) } else { 0 };
        let l = if ok == 1 { l0 } else { 0 };
        let lits = if cr > 0 { cr } else { 1 };
        let r = fl_emit_step(input, out, pos, d, l, lits, ntok);
        let olen = out.len();
        let npos = r.1;
        let matched = if l >= 3 { if npos == pos.wrapping_add(l) { 1usize } else { 0usize } } else { 0usize };
        let harg2 = if matched == 1 { npos } else { pos.wrapping_add(1) };
        fl_insert(input, &mut head, &mut prev, pos.wrapping_add(1), harg2, 32);
        ntok = r.0;
        pos = npos;
    }
    (ntok, pos)
}

// ---------------------------------------------------------------- LAZY: price-lazy with a runtime config

/// Estimated saving (quarter bits, offset by 4096) of coding `l` bytes as a match at `d`.
pub fn fl_score(l: usize, d: usize, litq: usize) -> usize {
    let cost = FL_C0Q.wrapping_add(fl_dextra(d).wrapping_add(fl_lextra(l)).wrapping_mul(4));
    l.wrapping_mul(litq).wrapping_add(4096).wrapping_sub(cost)
}

/// Fixed-point log2 with 8 fractional bits (linear between powers of two); x >= 1.
pub fn fl_lg8(x: u32) -> u64 {
    let y = x | 1;
    let e = 31u32.wrapping_sub(y.leading_zeros()) % 32;
    let m = if e >= 8 { (y >> (e - 8)) & 255 } else { (y << (8 - e)) & 255 };
    (e as u64).wrapping_mul(256).wrapping_add(m as u64)
}

/// Entropy of the histogram in 1/256 bits per symbol.
pub fn fl_entropy256(h: &[u32; 256]) -> usize {
    let mut tot = 0u64;
    let mut acc = 0u64;
    let mut i = 0usize;
    while i < 256 {
        let c = h[i];
        tot = tot.wrapping_add(c as u64);
        acc = if c > 0 { acc.wrapping_add((c as u64).wrapping_mul(fl_lg8(c))) } else { acc };
        i += 1;
    }
    if tot == 0 {
        return 2048;
    }
    let t32 = if tot > 4000000000 { 4000000000u32 } else { tot as u32 };
    let a = fl_lg8(t32);
    let b = acc / tot;
    if a > b {
        (a - b) as usize
    } else {
        0
    }
}

/// Literal cost (quarter bits) for low-entropy inputs.
pub fn fl_lit_cost(h0: usize) -> usize {
    let q = h0 / 64 + FL_LADJ;
    if q < 6 {
        6
    } else if q > 36 {
        36
    } else {
        q
    }
}

/// Walk the chain from `start` (pos+1 encoded, 0 = none) for the match with the best estimated saving
/// that is longer than `bl0` and saves more than `bs0`; stop at length `nice`. Returns `len | dist << 9`, or 0.
pub fn fl_walk(input: &[u8], prev: &[u16; 32768], pos: usize, start: usize, cap: usize, depth: usize, bl0: usize, bs0: usize, litq: usize, nice: usize) -> usize {
    let mut bl = bl0;
    let mut bd = 0usize;
    let mut bs = bs0;
    let mut cur = start;
    let mut k = 0usize;
    let mut off = if bl >= 3 { bl - 3 } else { 0 };
    let mut want = fl_ld4(input, pos.wrapping_add(off));
    while k < depth && cur > 0 && cur <= pos && pos - (cur - 1) <= 32768 {
        let c = cur - 1;
        if bl < cap && fl_ld4(input, c.wrapping_add(off)) == want {
            let l = fl_len(input, c, pos, cap);
            let s = fl_score(l, pos - c, litq);
            let take = if l > bl { if s > bs { 1usize } else { 0usize } } else { 0usize };
            bd = if take == 1 { pos - c } else { bd };
            bs = if take == 1 { s } else { bs };
            bl = if take == 1 { l } else { bl };
            off = if bl >= 3 { bl - 3 } else { 0 };
            want = fl_ld4(input, pos.wrapping_add(off));
        }
        cur = if bl >= nice { 0 } else { prev[c % 32768] as usize };
        k += 1;
    }
    if bd > 0 {
        bl | bd.wrapping_mul(512)
    } else {
        0
    }
}

/// With `depth > 0`: insert `pos` into the chains when `ins == 1`, then walk them. Returns
/// `len | dist << 9` of a match longer than `bl0` saving more than `bs0`, or 0.
#[inline(always)]
pub fn fl_search(input: &[u8], head: &mut [u16; 16384], prev: &mut [u16; 32768], pos: usize, depth: usize, ins: usize, bl0: usize, bs0: usize, litq: usize, hsh: u64, nice: usize) -> usize {
    let n = input.len();
    if depth == 0 || n < 16 || pos > n - 16 {
        return 0;
    }
    let h = fl_hashp(input, pos, hsh) % 16384;
    let start = head[h] as usize;
    let pw = pos % 32768;
    prev[pw] = if ins == 1 { start as u16 } else { prev[pw] };
    head[h] = if ins == 1 { (pos as u16).wrapping_add(1) } else { head[h] };
    let rem = n - pos - 8;
    let cap = if rem < 258 { rem } else { 258 };
    fl_walk(input, prev, pos, start, cap, depth, bl0, bs0, litq, nice)
}

/// Insert the inside `from .. to` of an emitted match: its first `ih` and last `it` positions.
pub fn fl_insert_match(input: &[u8], head: &mut [u16; 16384], prev: &mut [u16; 32768], from: usize, to: usize, hsh: u64, ih: usize, it: usize) {
    let a = from.wrapping_add(ih);
    let a2 = if a < to { a } else { to };
    fl_tinsert(input, head, prev, from, a2, hsh);
    let b = to.wrapping_sub(it);
    let b2 = if b > a2 { if b < to { b } else { a2 } } else { a2 };
    fl_tinsert(input, head, prev, b2, to, hsh);
}

/// Literal-run length after `miss` consecutive misses: 1 + (miss >> acc), at most 32.
pub fn fl_lits(miss: usize, acc: usize) -> usize {
    let over = ((miss as u64) >> ((acc as u64) % 64)) as usize;
    if over < 32 {
        over + 1
    } else {
        32
    }
}

/// Literal cost (quarter bits) used by the lazy parser: from the entropy for low-entropy inputs, else FL_LITQ.
pub fn fl_litq(h0: usize) -> usize {
    if h0 < FL_HLOW {
        fl_lit_cost(h0)
    } else {
        FL_LITQ
    }
}

/// Hash shift: 8-byte hash (0) for low-entropy inputs, 4-byte hash (32) otherwise.
pub fn fl_hsh(h0: usize) -> u64 {
    if h0 < FL_HLOW {
        0
    } else {
        32
    }
}

/// Price-lazy parse (the jgreedy jg1c algorithm) with the class configuration `cf`.
pub fn fl_lazy_parse(input: &[u8], out: &mut [u32], lh: &[u32; 256], cf: &[usize; 8]) -> (usize, usize) {
    let n = input.len();
    let depth = cf[0];
    let depth2 = cf[1];
    let lazy = cf[2];
    let nice = cf[3];
    let ih = cf[4];
    let it = cf[5];
    let acc = cf[6];
    let h0 = fl_entropy256(lh);
    let litq = fl_litq(h0);
    let hsh = fl_hsh(h0);
    let mut head = [0u16; 16384];
    let mut prev = [0u16; 32768];
    let mut pos = 0usize;
    let mut ntok = 0usize;
    let mut carry = 0usize;
    let mut miss = 0usize;
    while pos < n {
        let have = if carry != 0 { 1usize } else { 0usize };
        let harg3 = if have == 1 { 0 } else { depth };
        let s1 = fl_search(input, &mut head, &mut prev, pos, harg3, 1, 2, 4096, litq, hsh, nice);
        let m1 = if have == 1 { carry } else { s1 };
        let l1 = m1 % 512;
        if l1 < 3 {
            let lits = fl_lits(miss, acc);
            let r = fl_emit_step(input, out, pos, 0, 0, lits, ntok);
            let olen = out.len();
            miss = miss.wrapping_add(1);
            carry = 0;
            ntok = r.0;
            pos = r.1;
        } else {
            let d1 = (m1 / 512) % 65536;
            let want = if l1 < lazy { 1usize } else { 0usize };
            let p2 = if want == 1 { if l1 >= FL_GOOD { depth2 } else { depth } } else { 0 };
            let s2 = fl_search(input, &mut head, &mut prev, pos.wrapping_add(1), p2, 1, l1.wrapping_sub(1), fl_score(l1, d1, litq), litq, hsh, nice);
            let take2 = if s2 != 0 { 1usize } else { 0usize };
            let l = if take2 == 1 { 0 } else { l1 };
            let d = if take2 == 1 { 0 } else { d1 };
            let r = fl_emit_step(input, out, pos, d, l, 1, ntok);
            let olen = out.len();
            let npos = r.1;
            let matched = if l >= 3 { if npos == pos.wrapping_add(l) { 1usize } else { 0usize } } else { 0usize };
            let from = if want == 1 { pos.wrapping_add(2) } else { pos.wrapping_add(1) };
            let harg4 = if matched == 1 { npos } else { from };
            fl_insert_match(input, &mut head, &mut prev, from, harg4, hsh, ih, it);
            carry = if take2 == 1 { s2 } else { 0 };
            miss = 0;
            ntok = r.0;
            pos = npos;
        }
    }
    (ntok, pos)
}

// ---------------------------------------------------------------- G3: garbage 3-byte parser (lane E2)

// trusted kit, G3 copy (byte-identical to the base kit, renamed; keeps the base emit_step with one caller)
/// Trusted: little-endian 8-byte word at `p` (0 when out of range).
pub fn g3_tw8(input: &[u8], p: usize) -> u64 {
    let n = input.len();
    if n < 8 || p > n - 8 {
        return 0;
    }
    (input[p] as u64)
        + (input[p + 1] as u64) * 256
        + (input[p + 2] as u64) * 65536
        + (input[p + 3] as u64) * 16777216
        + (input[p + 4] as u64) * 4294967296
        + (input[p + 5] as u64) * 1099511627776
        + (input[p + 6] as u64) * 281474976710656
        + (input[p + 7] as u64) * 72057594037927936
}

/// Trusted: little-endian 4-byte word at `p` (0 when out of range).
pub fn g3_tw4(input: &[u8], p: usize) -> u32 {
    let n = input.len();
    if n < 4 || p > n - 4 {
        return 0;
    }
    (input[p] as u32) + (input[p + 1] as u32) * 256 + (input[p + 2] as u32) * 65536 + (input[p + 3] as u32) * 16777216
}

/// Trusted: 1 iff `cap >= 8`, `cap - l < 8` and the 8-byte words at `a + cap - 8` and `b + cap - 8` are equal.
pub fn g3_tail_eq(input: &[u8], a: usize, b: usize, cap: usize, l: usize) -> usize {
    if cap < 8 || cap - l >= 8 {
        return 0;
    }
    if g3_tw8(input, a + (cap - 8)) == g3_tw8(input, b + (cap - 8)) {
        1
    } else {
        0
    }
}

/// Trusted: 1 iff `4 <= cap < 8` and the 4-byte words at `a`, `b` and at `a + cap - 4`, `b + cap - 4` are equal.
pub fn g3_short_eq(input: &[u8], a: usize, b: usize, cap: usize) -> usize {
    if cap < 4 || cap >= 8 {
        return 0;
    }
    if g3_tw4(input, a) != g3_tw4(input, b) {
        return 0;
    }
    if g3_tw4(input, a + (cap - 4)) == g3_tw4(input, b + (cap - 4)) {
        1
    } else {
        0
    }
}

/// Trusted: a length `l <= cap` over which the bytes at `a` and `b` provably agree, found with word compares:
/// 8-byte steps, then one overlapping 8-byte compare at `cap - 8` (or two 4-byte ones when 4 <= cap < 8); `cap`
/// itself when everything agreed.
pub fn g3_words_eq(input: &[u8], a: usize, b: usize, cap: usize) -> usize {
    let mut l = 0usize;
    while cap - l >= 8 && g3_tw8(input, a + l) == g3_tw8(input, b + l) {
        l += 8;
    }
    let big = g3_tail_eq(input, a, b, cap, l);
    let small = g3_short_eq(input, a, b, cap);
    if big == 1 {
        cap
    } else if small == 1 {
        cap
    } else {
        l
    }
}

/// Trusted: how many bytes agree at `a` and `b`, up to `cap` (word compares, then bytes).
pub fn g3_match_len(input: &[u8], a: usize, b: usize, cap: usize) -> usize {
    let mut l = g3_words_eq(input, a, b, cap);
    while l < cap && input[b + l] == input[a + l] {
        l += 1;
    }
    l
}

/// True iff `(ch, d)` at `pos` is in range and its bytes agree (G3 copy of the base kit).
#[inline(always)]
pub fn g3_verified(input: &[u8], pos: usize, d: usize, ch: usize) -> bool {
    let n=input.len();
    if ch<3 || ch>258 || d<1 || d>32768 || d>pos || pos>n || ch>n-pos {return false;}
    let a=pos-d;
    if ch>=8 && ch<=16 {
        g3_tw8(input,a)==g3_tw8(input,pos) && g3_tw8(input,a+ch-8)==g3_tw8(input,pos+ch-8)
    } else if ch>=4 && ch<8 {
        g3_tw4(input,a)==g3_tw4(input,pos) && g3_tw4(input,a+ch-4)==g3_tw4(input,pos+ch-4)
    } else if ch==3 {
        input[a]==input[pos] && input[a+1]==input[pos+1] && input[a+2]==input[pos+2]
    } else {g3_match_len(input,a,pos,ch)>=ch}
}

/// Trusted: `cnt >= 1` literals from `pos0` (stopping at the input end).
#[inline(always)]
pub fn g3_emit_lits(input: &[u8], out: &mut [u32], pos0: usize, cnt: usize, ntok0: usize) -> (usize, usize) {
    let n = input.len();
    let cnt1 = if cnt == 0 { 1 } else { cnt };
    let mut k = pos0;
    let mut c = 0usize;
    let mut ntok = ntok0;
    while k < n && c < cnt1 {
        out[ntok] = input[k] as u32;
        ntok += 1;
        k += 1;
        c += 1;
    }
    (ntok, k)
}

/// Trusted: the match `(l, d)` at `pos` if it verifies, else `lits` literals.
#[inline(always)]
pub fn g3_emit_step(input: &[u8], out: &mut [u32], pos: usize, d: usize, l: usize, lits: usize, ntok: usize) -> (usize, usize) {
    if g3_verified(input, pos, d, l) {
        out[ntok] = 16777216u32 + ((d - 1) as u32) * 256 + ((l - 3) as u32);
        (ntok + 1, pos + l)
    } else {
        g3_emit_lits(input, out, pos, lits, ntok)
    }
}

// ------------------------------------------------------------------ the parse loop

/// The lazy check at `q` (= match position + 1) with `go == 1`: enter `q` into the chains and test the most
/// recent chain candidate against the current match (`l1` bytes, score `sv1`). Returns `len | dist << 9 |


/// Hash of the 3 bytes at `p` into 16 bits.
#[inline(always)]
pub fn fl_g3_hash(input: &[u8], p: usize) -> usize {
    let w = ld4(input, p) % 16777216;
    ((w.wrapping_mul(2654435761) >> 16) as usize) % 65536
}

/// Table step: returns the stored occurrence (pos + 1 encoded, 0 = none) of bucket `h` and stores `p` there when
/// the bucket is empty or its occurrence is outside the window (the OLDEST occurrence in the window is kept).
#[inline(always)]
pub fn fl_g3_probe(tab: &mut [u32; 65536], h: usize, p: usize) -> usize {
    let c = tab[h % 65536] as usize;
    let ok = if c >= 1 { if c <= p { if p - c < G3_WIN { 1usize } else { 0 } } else { 0 } } else { 0 };
    if ok == 0 {
        tab[h % 65536] = (p as u32).wrapping_add(1);
    }
    if ok == 1 { c } else { 0 }
}

/// Common prefix (at most 3) of `p - d` and `p` (d >= 1), else 0.
#[inline(always)]
pub fn fl_g3_len(input: &[u8], p: usize, d: usize) -> usize {
    if d >= 1 && d <= p { fast_len(input, p - d, p, 3) } else { 0 }
}

/// Literal run `[pos, s)` through the garbage kit (nothing when `s <= pos`); `(ntok, pos)` after it.
#[inline(always)]
pub fn g3_lits(input: &[u8], out: &mut [u32], pos: usize, s: usize, ntok: usize) -> (usize, usize) {
    if s > pos { g3_emit_lits(input, out, pos, s - pos, ntok) } else { (ntok, pos) }
}

/// Garbage parse from `pos0`: at every position one probe of the 3-byte table; a hit is written as a 3-byte match
/// at the stored (oldest) distance, else one literal. Returns (ntok, n).
pub fn fl_g3_parse(input: &[u8], out: &mut [u32], pos0: usize, ntok0: usize) -> (usize, usize) {
    let n = input.len();
    let mut tab = [0u32; 65536];
    let lim = n.saturating_sub(8);
    let mut pos = pos0;
    let mut ntok = ntok0;
    while pos < lim {
        let h = fl_g3_hash(input, pos);
        let c = fl_g3_probe(&mut tab, h, pos);
        let d = if c >= 1 && c <= pos { pos - c + 1 } else { 0 };
        let l = fl_g3_len(input, pos, d);
        let r = g3_emit_step(input, out, pos, d, l, 1, ntok);
        let olen = out.len();
        ntok = r.0;
        pos = r.1;
    }
    if pos < n {
        g3_emit_lits(input, out, pos, n - pos, ntok)
    } else {
        (ntok, pos)
    }
}



// ---------------------------------------------------------------- BF: bf16-like weights, 3-byte guess lane (lane E2)
// Values are 2 bytes (low mantissa byte, then sign/exponent byte). At odd positions the three bytes are
// [high k][low k+1][high k+1]; a 16-bit key of (4 bits of high k, low k+1, 4 bits of high k+1) indexes the newest
// occurrence; the match is only GUESSED (no byte compare here): the trusted kit compares the 3 bytes and writes two
// literals instead when they differ. After a match the position after it is written as a literal so the probes stay
// on odd positions; the skipped odd position inside the match is entered into the table.

/// 16-bit key of the three bytes at `p`: bits 0-2 and 7 of byte 0, byte 1, bits 0-2 and 7 of byte 2.
#[inline(always)]
pub fn fl_bf_key(input: &[u8], p: usize) -> usize {
    let v = ld4(input, p) % 16777216;
    let a = (v % 8) | ((v >> 4) & 8);
    let b = ((v >> 16) % 8) | ((v >> 20) & 8);
    (a | (((v >> 8) % 256) << 4) | (b << 12)) as usize % 65536
}

/// Table step: the distance to the stored occurrence of bucket `h` (0 when none within 32768), then `p` is stored.
#[inline(always)]
pub fn fl_bf_guess(tab: &mut [u32; 65536], h: usize, p: usize) -> usize {
    let c = tab[h % 65536] as usize;
    tab[h % 65536] = (p as u32).wrapping_add(1);
    if c >= 1 && c <= p && p - c < 32768 { p - c + 1 } else { 0 }
}

/// The lane from `pos0`: returns (ntok, n).
pub fn fl_bf_parse(input: &[u8], out: &mut [u32], pos0: usize, ntok0: usize) -> (usize, usize) {
    let n = input.len();
    let mut tab = [0u32; 65536];
    let lim = n.saturating_sub(8);
    let mut pos = pos0;
    let mut ntok = ntok0;
    while pos < lim {
        if pos % 2 == 1 {
            let h = fl_bf_key(input, pos);
            let d0 = fl_bf_guess(&mut tab, h, pos);
            let d = if d0 >= FL_BF_DMIN { d0 } else { 0 };
            let l = if d >= 1 { 3usize } else { 0usize };
            let r = g3_emit_step(input, out, pos, d, l, 2, ntok);
            let olen = out.len();
            let npos = r.1;
            if npos == pos.wrapping_add(3) && npos < n {
                let h2 = fl_bf_key(input, pos.wrapping_add(2));
                let unused = fl_bf_guess(&mut tab, h2, pos.wrapping_add(2));
                let r2 = g3_emit_lits(input, out, npos, 1, r.0);
                ntok = r2.0;
                pos = r2.1;
            } else {
                ntok = r.0;
                pos = npos;
            }
        } else {
            let r = g3_emit_lits(input, out, pos, 1, ntok);
            let olen = out.len();
            ntok = r.0;
            pos = r.1;
        }
    }
    if pos < n {
        g3_emit_lits(input, out, pos, n - pos, ntok)
    } else {
        (ntok, pos)
    }
}

// ---------------------------------------------------------------- IM: flat high-entropy inputs with a few long repeats (images)
// Probes positions 3..5 bytes apart (an irregular stride, so repeat distances of any residue are found) with a 4-byte
// hash into an 8 K table of 32-bit entries (16-bit tag of the hash, 16-bit position): a stale or colliding entry is
// rejected on its tag without touching the input. A match of at least FL_IM_MIN bytes is extended backwards over the
// stride gap and written through the kit; everything else is literals.

/// 32-bit hash of the 4 bytes at `p`.
#[inline(always)]
pub fn fl_im_hash(input: &[u8], p: usize) -> u32 {
    ld4(input, p).wrapping_mul(2654435761)
}

/// Table step: the entry of the bucket of hash `h` (tag << 16 | position + 1), then `p` stored there.
#[inline(always)]
pub fn fl_im_step(tab: &mut [u32; 8192], h: u32, p: usize) -> u32 {
    let i = (h >> 19) as usize % 8192;
    let c = tab[i];
    tab[i] = (h << 16) | ((p.wrapping_add(1) % 65536) as u32);
    c
}

/// Distance of the entry `c` seen from `p` when its tag matches hash `h` (0 when not).
#[inline(always)]
pub fn fl_im_dist(c: u32, h: u32, p: usize) -> usize {
    let cp = (c % 65536) as usize;
    let d = (p.wrapping_add(1).wrapping_sub(cp)) % 65536;
    if cp >= 1 && c >> 16 == h % 65536 && d >= 1 && d <= 32768 && d <= p { d } else { 0 }
}

/// Bytes before `p` (at most `back`) that also agree at distance `d`.
#[inline(always)]
pub fn fl_im_back(input: &[u8], p: usize, d: usize, back: usize) -> usize {
    let mut b = 0usize;
    while b < back && p > b && p - b > d && input[p - b - 1] == input[p - b - 1 - d] {
        b += 1;
    }
    b
}

/// The next probe position after `p`: `base`, + 1 or + 2 bytes on.
#[inline(always)]
pub fn fl_im_next(p: usize, base: usize) -> usize {
    p.wrapping_add(base).wrapping_add((p / 4) % 3)
}

/// The lane from `pos0`: returns (ntok, n).
pub fn fl_im_parse(input: &[u8], out: &mut [u32], pos0: usize, ntok0: usize) -> (usize, usize) {
    let n = input.len();
    let mut tab = [0u32; 8192];
    let lim = n.saturating_sub(8);
    let mut pos = pos0;
    let mut ntok = ntok0;
    let mut p = pos0;
    let mut probes = 0usize;
    let mut found = 0usize;
    let mut sleep = 0usize;
    while p < lim {
        let h = fl_im_hash(input, p);
        let c = fl_im_step(&mut tab, h, p);
        let d = fl_im_dist(c, h, p);
        let rem = n - p;
        let cap = if rem < 258 { rem } else { 258 };
        let l = if d >= 1 { fast_len(input, p.wrapping_sub(d), p, cap) } else { 0 };
        if l >= FL_IM_MIN {
            let b = fl_im_back(input, p, d, p.wrapping_sub(pos));
            let start = p.wrapping_sub(b);
            let lb = if l.wrapping_add(b) > 258 { 258 } else { l.wrapping_add(b) };
            let r0 = g3_lits(input, out, pos, start, ntok);
            if r0.1 < n {
                let r = g3_emit_step(input, out, r0.1, d, lb, 1, r0.0);
                let olen = out.len();
                ntok = r.0;
                pos = r.1;
            } else {
                ntok = r0.0;
                pos = r0.1;
            }
            found = found.wrapping_add(1);
            sleep = 0;
            p = if pos > p { pos } else { p + FL_IM_STEP + (p / 4) % 3 };
        } else if sleep == 1 {
            let adv = FL_IM_SLEEP + (p / 4) % 3;
            p = if adv < lim - p { p + adv } else { lim };
        } else {
            p = p + FL_IM_STEP + (p / 4) % 3;
        }
        probes = probes.wrapping_add(1);
        if probes == FL_IM_PROBES {
            if found < FL_IM_EARLY {
                sleep = 1;
            }
        }
    }
    if pos < n {
        g3_emit_lits(input, out, pos, n - pos, ntok)
    } else {
        (ntok, pos)
    }
}

// ---------------------------------------------------------------- DNA8: genome, honest lane (lane E2)
// A 64 K u32 table keyed by the 8 bytes at each position (two bits of information per DNA byte: an 8-byte key
// selects among 65536 contexts), greedy, matches of at least FL_DNA8_MIN bytes, inserts at the match start and the
// next position; literal runs between matches.

/// 16-bit hash of the FL_DNA8_KEY bytes at `p`.
#[inline(always)]
pub fn fl_dna8_hash(input: &[u8], p: usize) -> usize {
    let v = if FL_DNA8_KEY == 6 { ld8(input, p) % 281474976710656 } else { ld8(input, p) };
    ((v.wrapping_mul(0x9E3779B97F4A7C15) >> 48) as usize) % 65536
}

/// Table step: the stored occurrence (position + 1, 0 = none) of bucket `h`, then `p` stored.
#[inline(always)]
pub fn fl_dna8_step(tab: &mut [u32; 65536], h: usize, p: usize) -> usize {
    let c = tab[h % 65536] as usize;
    tab[h % 65536] = (p as u32).wrapping_add(1);
    c
}

/// The lane from `pos0`: returns (ntok, n).
pub fn fl_dna8_parse(input: &[u8], out: &mut [u32], pos0: usize, ntok0: usize) -> (usize, usize) {
    let n = input.len();
    let mut tab = [0u32; 65536];
    let lim = n.saturating_sub(16);
    let mut pos = pos0;
    let mut ntok = ntok0;
    let mut p = pos0;
    while p < lim {
        let h = fl_dna8_hash(input, p);
        let c = fl_dna8_step(&mut tab, h, p);
        let d = if c >= 1 && c <= p && p - c < 32768 { p - c + 1 } else { 0 };
        let rem = n - p;
        let cap = if rem < 258 { rem } else { 258 };
        let l = if d >= 1 { fast_len(input, p.wrapping_sub(d), p, cap) } else { 0 };
        if l >= FL_DNA8_MIN {
            let r0 = g3_lits(input, out, pos, p, ntok);
            if r0.1 < n {
                let r = g3_emit_step(input, out, r0.1, d, l, 1, r0.0);
                let olen = out.len();
                ntok = r.0;
                pos = r.1;
            } else {
                ntok = r0.0;
                pos = r0.1;
            }
            let h1 = fl_dna8_hash(input, p.wrapping_add(1));
            let unused = fl_dna8_step(&mut tab, h1, p.wrapping_add(1));
            p = if pos > p { pos } else { p + 1 };
        } else {
            p = p + 1;
        }
    }
    if pos < n {
        g3_emit_lits(input, out, pos, n - pos, ntok)
    } else {
        (ntok, pos)
    }
}

// ---------------------------------------------------------------- SM: small inputs (at most FL_SM_N bytes)
// One encoder block: its package-merge costs ≈ 1 µs per live length/distance code, a match token ≈ 26 ns and a
// literal ≈ 6 ns. Pass 1 (fl_sm_scan) runs a single-probe greedy search into a decision cache and counts, per
// length code and per distance code, the matches and the bytes they cover. Pass 2 (fl_sm_rules) drops every code
// whose matches cost more as a live symbol than they save as tokens, remapping dropped lengths to the top of the
// previous kept length code. Pass 3 (fl_sm_replay) writes the cache through the trusted kit under that remap.
// Cache entry: a literal run count (1..511) or `len | dist << 9`.

/// DEFLATE length code (0..28) of `l` (3..258).
pub fn fl_sm_lc(l: usize) -> usize {
    if l >= 258 { 28 }
    else if l <= 10 { l.wrapping_sub(3) % 29 }
    else if l <= 18 { 8 + (l - 11) / 2 }
    else if l <= 34 { 12 + (l - 19) / 4 }
    else if l <= 66 { 16 + (l - 35) / 8 }
    else if l <= 130 { 20 + (l - 67) / 16 }
    else { 24 + (l - 131) / 32 }
}

/// DEFLATE distance code (0..29) of `d` (1..32768).
pub fn fl_sm_dc(d: usize) -> usize {
    if d <= 4 { d.wrapping_sub(1) % 30 }
    else {
        let x = (d.wrapping_sub(1)) as u32;
        let e = (31u32.wrapping_sub(x.leading_zeros())) as usize % 32;
        let s = e.wrapping_sub(1) % 32;
        (2usize.wrapping_mul(e).wrapping_add(((x >> (s as u32)) as usize) % 2)) % 30
    }
}

/// Top length of length code `c`.
pub const FL_SM_LTOP: [u16; 32] = [3, 4, 5, 6, 7, 8, 9, 10, 12, 14, 16, 18, 22, 26, 30, 34, 42, 50, 58, 66, 82, 98, 114, 130, 162, 194, 226, 257, 258, 258, 258, 258];

/// 13-bit hash of the 4 bytes at `p`.
#[inline(always)]
pub fn fl_sm_hash(input: &[u8], p: usize) -> usize {
    ((ld4(input, p).wrapping_mul(2654435761) >> 19) as usize) % 8192
}

/// Table step: the stored occurrence (position + 1, 0 = none) of bucket `h`, then `p` stored.
#[inline(always)]
pub fn fl_sm_step(tab: &mut [u16; 8192], h: usize, p: usize) -> usize {
    let c = tab[h % 8192] as usize;
    tab[h % 8192] = (p.wrapping_add(1) % 65536) as u16;
    c
}

/// Enter positions `from .. to` (never at or past n - 8).
pub fn fl_sm_insert(input: &[u8], tab: &mut [u16; 8192], from: usize, to: usize) {
    let lim = input.len().saturating_sub(8);
    let mut p = from;
    while p < to && p < lim {
        let h = fl_sm_hash(input, p);
        let unused = fl_sm_step(tab, h, p);
        p += 1;
    }
}

/// Count a match: st[lc] matches, st[29 + lc] bytes, st[64 + dc] matches, st[96 + dc] bytes.
#[inline(always)]
pub fn fl_sm_add(st: &mut [u32; 128], l: usize, d: usize) {
    let a = fl_sm_lc(l) % 29;
    let b = fl_sm_dc(d) % 30;
    st[a] = st[a].wrapping_add(1);
    st[29 + a] = st[29 + a].wrapping_add(l as u32);
    st[64 + b] = st[64 + b].wrapping_add(1);
    st[96 + b] = st[96 + b].wrapping_add(l as u32);
}

/// The greedy candidate at `p`: `len | dist << 9` (len >= FL_SM_MIN) or 0; enters `p` into the table.
#[inline(always)]
pub fn fl_sm_find(input: &[u8], tab: &mut [u16; 8192], p: usize) -> usize {
    let n = input.len();
    let h = fl_sm_hash(input, p);
    let c = fl_sm_step(tab, h, p);
    let d = if c >= 1 && c <= p && p - c < 32768 { p - c + 1 } else { 0 };
    let rem = n - p;
    let cap = if rem < 258 { rem } else { 258 };
    let l = if d >= 1 { fast_len(input, p - d, p, cap) } else { 0 };
    if l >= FL_SM_MIN { l | d.wrapping_mul(512) } else { 0 }
}

/// Pass 1: decisions into `cache` (at most 16382 entries) with the code statistics; returns (entries, position reached).
pub fn fl_sm_scan(input: &[u8], cache: &mut [u32; 16384], st: &mut [u32; 128], tab: &mut [u16; 8192]) -> (usize, usize) {
    let n = input.len();
    let lim = n.saturating_sub(8);
    let mut pos = 0usize;
    let mut k = 0usize;
    let mut run = 0usize;
    while pos < lim && k < 16382 {
        let m = fl_sm_find(input, tab, pos);
        let l = m % 512;
        let d = (m / 512) % 65536;
        if l >= 3 {
            if run > 0 {
                cache[k % 16384] = run as u32;
                k += 1;
                run = 0;
            }
            cache[k % 16384] = m as u32;
            k += 1;
            fl_sm_add(st, l, d);
            let ito = if l > FL_SM_IH { pos.wrapping_add(1).wrapping_add(FL_SM_IH) } else { pos.wrapping_add(l) };
            fl_sm_insert(input, tab, pos.wrapping_add(1), ito);
            let adv = if l < n - pos { l } else { n - pos };
            pos = pos + adv;
        } else {
            run = run.wrapping_add(1);
            pos += 1;
            if run >= 511 {
                cache[k % 16384] = run as u32;
                k += 1;
                run = 0;
            }
        }
    }
    if run > 0 {
        cache[k % 16384] = run as u32;
        k = k.wrapping_add(1);
    }
    (k, pos)
}

/// Pass 1 for sparse inputs: distance-1 runs (the RLE parse) into the cache.
pub fn fl_sm_rle_scan(input: &[u8], cache: &mut [u32; 16384], st: &mut [u32; 128]) -> (usize, usize) {
    let n = input.len();
    let mut pos = 0usize;
    let mut k = 0usize;
    let mut run = 0usize;
    while pos < n && k < 16382 {
        let rem = n - pos;
        let cap = if rem < 258 { rem } else { 258 };
        let l = if pos >= 1 { fl_len(input, pos - 1, pos, cap) } else { 0 };
        if l >= 3 {
            if run > 0 {
                cache[k % 16384] = run as u32;
                k += 1;
                run = 0;
            }
            cache[k % 16384] = (l | 512) as u32;
            k += 1;
            fl_sm_add(st, l, 1);
            let adv = if l < n - pos { l } else { n - pos };
            pos = pos + adv;
        } else {
            run = run.wrapping_add(1);
            pos += 1;
            if run >= 511 {
                cache[k % 16384] = run as u32;
                k += 1;
                run = 0;
            }
        }
    }
    if run > 0 {
        cache[k % 16384] = run as u32;
        k = k.wrapping_add(1);
    }
    (k, pos)
}

/// Pass 2: q[l] = the length a match of `l` bytes is written with (0 = literals), q[259 + dc] = 1 when distance code
/// `dc` is dropped. `thin == 0` keeps everything (identity); `dt` = the live-symbol cost in ns.
pub fn fl_sm_rules(st: &[u32; 128], q: &mut [u16; 320], thin: usize, dt: usize) {
    let mut j = 0usize;
    while j < 30 {
        let c = st[64 + j] as usize;
        let b = st[96 + j] as usize;
        let drop = if thin == 1 && c > 0 && FL_SM_LIT.wrapping_mul(b) < FL_SM_MAT.wrapping_mul(c).wrapping_add(dt) { 1u16 } else { 0u16 };
        q[259 + j] = drop;
        j += 1;
    }
    let mut top = 0usize;
    let mut i = 0usize;
    let mut l = 3usize;
    while i < 29 {
        let c = st[i] as usize;
        let b = st[29 + i] as usize;
        let covered = c.wrapping_mul(top);
        let waste = if b > covered { b - covered } else { 0 };
        let cost = if top >= 3 { FL_SM_LIT.wrapping_mul(waste) } else { FL_SM_LIT.wrapping_mul(b).saturating_sub(FL_SM_MAT.wrapping_mul(c)) };
        let keep = if thin == 0 { 1usize } else if c > 0 && cost > dt { 1 } else { 0 };
        let end = FL_SM_LTOP[i % 32] as usize;
        while l <= end && l < 259 {
            q[l % 320] = if keep == 1 { l as u16 } else { top as u16 };
            l += 1;
        }
        top = if keep == 1 { end } else { top };
        i += 1;
    }
}

/// `l` bytes at distance `d` from `pos` written as kept lengths (the remainder below the smallest kept code as
/// literals); returns (ntok, pos).
pub fn fl_sm_span(input: &[u8], out: &mut [u32], pos0: usize, l0: usize, d: usize, q: &[u16; 320], ntok0: usize) -> (usize, usize) {
    let n = input.len();
    let mut rem = l0;
    let mut pos = pos0;
    let mut ntok = ntok0;
    while rem > 0 && pos < n {
        let lq = q[rem % 320] as usize;
        if lq >= 3 {
            let r = g3_emit_step(input, out, pos, d, lq, 1, ntok);
            let olen = out.len();
            let adv = r.1.wrapping_sub(pos);
            rem = if adv < rem { rem - adv } else { 0 };
            ntok = r.0;
            pos = r.1;
        } else {
            let r = g3_emit_lits(input, out, pos, rem, ntok);
            let olen = out.len();
            let adv = r.1.wrapping_sub(pos);
            rem = if adv < rem { rem - adv } else { 0 };
            ntok = r.0;
            pos = r.1;
        }
    }
    (ntok, pos)
}

/// Pass 3: the `k` cache entries through the kit under the remap `q`; returns (ntok, pos).
pub fn fl_sm_replay(input: &[u8], out: &mut [u32], cache: &[u32; 16384], k: usize, q: &[u16; 320]) -> (usize, usize) {
    let n = input.len();
    let mut pos = 0usize;
    let mut ntok = 0usize;
    let mut i = 0usize;
    while i < k && pos < n {
        let t = cache[i % 16384] as usize;
        i += 1;
        let l = t % 512;
        let d = (t / 512) % 65536;
        let drop = if d >= 1 { q[(259usize).wrapping_add(fl_sm_dc(d)) % 320] as usize } else { 1 };
        if drop == 1 {
            let r = g3_emit_lits(input, out, pos, l, ntok);
            let olen = out.len();
            ntok = r.0;
            pos = r.1;
        } else {
            let r = fl_sm_span(input, out, pos, l, d, q, ntok);
            let olen = out.len();
            ntok = r.0;
            pos = r.1;
        }
    }
    (ntok, pos)
}

/// The rest of an input whose cache filled up: plain greedy emission with the same table.
pub fn fl_sm_rest(input: &[u8], out: &mut [u32], tab: &mut [u16; 8192], pos0: usize, ntok0: usize) -> (usize, usize) {
    let n = input.len();
    let lim = n.saturating_sub(8);
    let mut pos = pos0;
    let mut ntok = ntok0;
    while pos < lim {
        let m = fl_sm_find(input, tab, pos);
        let l = m % 512;
        let d = (m / 512) % 65536;
        let r = g3_emit_step(input, out, pos, d, l, 1, ntok);
        let olen = out.len();
        let npos = r.1;
        if l >= 3 {
            let ito = if l > FL_SM_IH { pos.wrapping_add(1).wrapping_add(FL_SM_IH) } else { pos.wrapping_add(l) };
            fl_sm_insert(input, tab, pos.wrapping_add(1), ito);
        }
        ntok = r.0;
        pos = npos;
    }
    if pos < n {
        g3_emit_lits(input, out, pos, n - pos, ntok)
    } else {
        (ntok, pos)
    }
}

/// Small input: the three passes; returns (ntok, n).
pub fn fl_sm_parse(input: &[u8], out: &mut [u32]) -> (usize, usize) {
    let mut tab = [0u16; 8192];
    let mut cache = [0u32; 16384];
    let mut st = [0u32; 128];
    let sc = fl_sm_scan(input, &mut cache, &mut st, &mut tab);
    let thin = if sc.1 < input.len().saturating_sub(8) { 0usize } else { 1usize };
    let mut q = [0u16; 320];
    fl_sm_rules(&st, &mut q, thin, FL_SM_DT);
    let r = fl_sm_replay(input, out, &cache, sc.0, &q);
    if r.1 < input.len() {
        fl_sm_rest(input, out, &mut tab, r.1, r.0)
    } else {
        r
    }
}

/// Small sparse input: the RLE decisions through the same thinning and replay; returns (ntok, n).
pub fn fl_sm_rle(input: &[u8], out: &mut [u32]) -> (usize, usize) {
    let mut cache = [0u32; 16384];
    let mut st = [0u32; 128];
    let sc = fl_sm_rle_scan(input, &mut cache, &mut st);
    let thin = if sc.1 < input.len() { 0usize } else { 1usize };
    let mut q = [0u16; 320];
    fl_sm_rules(&st, &mut q, thin, FL_SM_RLE_DT);
    let r = fl_sm_replay(input, out, &cache, sc.0, &q);
    if r.1 < input.len() {
        g3_emit_lits(input, out, r.1, input.len() - r.1, r.0)
    } else {
        r
    }
}

// ---------------------------------------------------------------- MC: zero-rich binaries (machine code), 3-byte lane (lane E2)
// One 64 K u32 table keyed by the 3 bytes at a position (newest occurrence), greedy, matches of at least 3 bytes,
// the FL_MC_IH positions after a match start entered too; literal runs between matches.

/// 16-bit hash of the 3 bytes at `p`.
#[inline(always)]
pub fn fl_mc_hash(input: &[u8], p: usize) -> usize {
    (((ld4(input, p) % 16777216).wrapping_mul(2654435761) >> 16) as usize) % 65536
}

/// Table step: the stored occurrence (position + 1, 0 = none) of bucket `h`, then `p` stored.
#[inline(always)]
pub fn fl_mc_step(tab: &mut [u32; 65536], h: usize, p: usize) -> usize {
    let c = tab[h % 65536] as usize;
    tab[h % 65536] = (p as u32).wrapping_add(1);
    c
}

/// Enter positions `from .. to` (never at or past n - 8).
pub fn fl_mc_insert(input: &[u8], tab: &mut [u32; 65536], from: usize, to: usize) {
    let lim = input.len().saturating_sub(8);
    let mut p = from;
    while p < to && p < lim {
        let h = fl_mc_hash(input, p);
        let unused = fl_mc_step(tab, h, p);
        p += 1;
    }
}

/// The lane from `pos0`: returns (ntok, n).
pub fn fl_mc_parse(input: &[u8], out: &mut [u32], pos0: usize, ntok0: usize) -> (usize, usize) {
    let n = input.len();
    let mut tab = [0u32; 65536];
    let lim = n.saturating_sub(8);
    let mut pos = pos0;
    let mut ntok = ntok0;
    let mut p = pos0;
    while p < lim {
        let h = fl_mc_hash(input, p);
        let c = fl_mc_step(&mut tab, h, p);
        let d = if c >= 1 && c <= p && p - c < 32768 { p - c + 1 } else { 0 };
        let rem = n - p;
        let cap = if rem < 258 { rem } else { 258 };
        let l0 = if d >= 1 { fast_len(input, p.wrapping_sub(d), p, cap) } else { 0 };
        let l = if l0 == 3 && d > FL_MC_D3 { 0 } else { l0 };
        if l >= FL_MC_MIN {
            let r0 = g3_lits(input, out, pos, p, ntok);
            if r0.1 < n {
                let r = g3_emit_step(input, out, r0.1, d, l, 1, r0.0);
                let olen = out.len();
                ntok = r.0;
                pos = r.1;
            } else {
                ntok = r0.0;
                pos = r0.1;
            }
            let ito = if l > FL_MC_IH { p.wrapping_add(1).wrapping_add(FL_MC_IH) } else { p.wrapping_add(l) };
            fl_mc_insert(input, &mut tab, p.wrapping_add(1), ito);
            p = if pos > p { pos } else { p + 1 };
        } else {
            p = p + 1;
        }
    }
    if pos < n {
        g3_emit_lits(input, out, pos, n - pos, ntok)
    } else {
        (ntok, pos)
    }
}

// ---------------------------------------------------------------- the floor phase

// ============================ E1 lean greedy lanes (genome: 6-byte key; high-entropy: tagged long table) ======
pub const LG_D_ACC: u64 = 5;
pub const LG_D_AMAX: usize = 64;
pub const LG_D_IH: usize = 4;
pub const LG_D_KS: usize = 16;
pub const LG_D_LONG: usize = 0;
pub const LG_H_ACC: u64 = 3;
pub const LG_H_AMAX: usize = 64;
pub const LG_H_IH: usize = 2;
pub const LG_H_KS: usize = 32;
pub const LG_H_LONG: usize = 1;
pub const LG_MAX3: usize = 32768;
pub const LG_WIN: usize = 32768;

/// 15-bit hash of the word `v` shifted left by `ks` (40: first 3 bytes, 32: 4 bytes, 16: 6 bytes).
#[inline(always)]
pub fn lg_hs(v: u64, ks: usize) -> usize {
    ((v << ((ks as u64) % 64)).wrapping_mul(0x9E3779B97F4A7C15) >> 49) as usize
}

/// 15-bit hash of the 8 bytes `v`.
#[inline(always)]
pub fn lg_h8(v: u64) -> usize {
    (v.wrapping_mul(0xCF1BBCDC9E3779B1) >> 49) as usize
}

/// The entry at bucket `h` (position + 1, 0 = none).
#[inline(always)]
pub fn lg_tab(head: &[u32; 32768], h: usize) -> usize {
    head[h % 32768] as usize
}

/// Enter `p` at bucket `h`.
#[inline(always)]
pub fn lg_put(head: &mut [u32; 32768], h: usize, p: usize) {
    head[h % 32768] = (p as u32).wrapping_add(1);
}

/// Long-table entry for `p` under the short hash `h4`: `(p + 1) % 2^24 | (h4 % 256) << 24`.
#[inline(always)]
pub fn lg_ent(h4: usize, p: usize) -> u32 {
    ((p as u32).wrapping_add(1) % 16777216) | (((h4 % 256) as u32) << 24)
}

/// Decode the long entry `e` under the short hash `h4`: the candidate position + 1 when the tag matches, else 0.
#[inline(always)]
pub fn lg_dec(h4: usize, e: u32) -> usize {
    if (e >> 24) as usize == h4 % 256 { (e % 16777216) as usize } else { 0 }
}

/// Enter `p` into the short table at `h4` (and the long one when `lo == 1`) for the word `v`.
#[inline(always)]
pub fn lg_ins(head: &mut [u32; 32768], long: &mut [u32; 32768], v: u64, p: usize, h4: usize, lo: usize) {
    lg_put(head, h4, p);
    if lo == 1 {
        long[lg_h8(v) % 32768] = lg_ent(h4, p);
    }
}

/// The match `len | dist << 9` of candidate `c` (position + 1) at `p` from the xor `x` of their words (low 3 bytes
/// agree): at least 3 bytes; else 0.
#[inline(always)]
pub fn lg_fin(input: &[u8], p: usize, c: usize, x: u64, cap: usize) -> usize {
    let cc = c.wrapping_sub(1);
    let l = if x == 0 { fast_len(input, cc, p, cap) } else { first_diff(x) };
    let d = p.wrapping_sub(cc);
    let ok = if l >= 4 { 1usize } else if l == 3 { if d <= LG_MAX3 { 1usize } else { 0usize } } else { 0usize };
    if ok == 1 { l | d.wrapping_mul(512) } else { 0 }
}

/// Candidates `c4` (4-byte bucket) and `c8` (8-byte bucket), position + 1 encoded (0 = none), at `p` with the word
/// `v`: the long one when its 8 bytes agree, else the short one when at least 3 bytes agree. `len | dist << 9` or 0.
#[inline(always)]
pub fn lg_eval(input: &[u8], p: usize, v: u64, c4: usize, c8: usize, cap: usize, lo: usize) -> usize {
    let lim = if p < LG_WIN { p } else { LG_WIN };
    if lo == 1 && p.wrapping_sub(c8) < lim && c8 <= p {
        let x8 = ld8(input, c8.wrapping_sub(1)) ^ v;
        if x8 == 0 {
            return lg_fin(input, p, c8, 0, cap);
        }
    }
    if p.wrapping_sub(c4) >= lim || c4 > p {
        return 0;
    }
    let x = ld8(input, c4.wrapping_sub(1)) ^ v;
    if x & 16777215 != 0 {
        return 0;
    }
    lg_fin(input, p, c4, x, cap)
}

/// Software-pipelined scan from `pos` with skip-ahead after misses: each iteration reads the table entries of the
/// next probe position before entering and evaluating the current one. `(q, m)` = the first position with a match
/// and `len | dist << 9`, or `(n, 0)`.
#[inline(always)]
pub fn lg_scan(input: &[u8], head: &mut [u32; 32768], long: &mut [u32; 32768], pos: usize, ks: usize, lo: usize, acc: u64, amax: usize) -> (usize, usize) {
    let n = input.len();
    if n < 16 || pos > n - 16 {
        return (n, 0);
    }
    let mut p = pos;
    let mut k = 0usize;
    let mut m = 0usize;
    let mut v = ld8(input, p);
    let mut h4 = lg_hs(v, ks);
    let mut h8 = lg_h8(v);
    let mut c4 = lg_tab(head, h4);
    let mut e8 = if lo == 1 { long[h8 % 32768] } else { 0 };
    while m == 0 && p <= n - 16 && k < n {
        let over = ((k as u64) >> (acc % 64)) as usize;
        let st = if over < amax { over + 1 } else { amax };
        let q = p.wrapping_add(st);
        let vq = if q <= n - 16 { ld8(input, q) } else { 0 };
        let hq4 = lg_hs(vq, ks);
        let hq8 = lg_h8(vq);
        let cq4 = lg_tab(head, hq4);
        let eq8 = if lo == 1 { long[hq8 % 32768] } else { 0 };
        lg_put(head, h4, p);
        if lo == 1 {
            long[h8 % 32768] = lg_ent(h4, p);
        }
        let rem = n - p - 8;
        let cap = if rem < 258 { rem } else { 258 };
        m = lg_eval(input, p, v, c4, lg_dec(h4, e8), cap, lo);
        p = if m == 0 { q } else { p };
        v = vq;
        h4 = hq4;
        h8 = hq8;
        c4 = cq4;
        e8 = eq8;
        k += 1;
    }
    if m == 0 { (n, 0) } else { (p, m) }
}

/// How many of the bytes before `q` (at most `lim`, with `lim <= q - d`) also repeat at distance `d`.
#[inline(always)]
pub fn lg_bext(input: &[u8], q: usize, d: usize, lim: usize) -> usize {
    let n = input.len();
    if q > n || d > q || lim > q - d {
        return 0;
    }
    let mut e = 0usize;
    while e < lim && input[q - 1 - e] == input[q - 1 - e - d] {
        e += 1;
    }
    e
}

/// Enter the positions `from .. min(from + ih, to)` into the tables.
#[inline(always)]
pub fn lg_insert(input: &[u8], head: &mut [u32; 32768], long: &mut [u32; 32768], from: usize, to: usize, ks: usize, lo: usize, ih: usize) {
    let n = input.len();
    let a = from.wrapping_add(ih);
    let e = if a < to { a } else { to };
    let mut p = from;
    while p < e && 16 <= n && p <= n - 16 {
        let v = ld8(input, p);
        lg_ins(head, long, v, p, lg_hs(v, ks), lo);
        p += 1;
    }
}

/// The smaller of `a` and `b`.
#[inline(always)]
pub fn lg_min(a: usize, b: usize) -> usize {
    if a < b { a } else { b }
}

/// Greedy parse from `pos0` with `ntok0` tokens already written; returns the token count. The class wrappers below
/// call it with constants.
#[inline(always)]
/// Literal run `[pos, s)` through the base kit (nothing when `s <= pos`); `(ntok, pos)` after it.
#[inline(always)]
pub fn lg_lits(input: &[u8], out: &mut [u32], pos: usize, s: usize, ntok: usize) -> (usize, usize) {
    if s > pos { emit_lits(input, out, pos, s - pos, ntok) } else { (ntok, pos) }
}

/// Literal tail to the end of the input (runs once; a Valid-form loop for the proof).
pub fn lg_finish(input: &[u8], out: &mut [u32], pos0: usize, ntok0: usize) -> usize {
    let n = input.len();
    let mut pos = pos0;
    let mut ntok = ntok0;
    while pos < n {
        let r = emit_lits(input, out, pos, n - pos, ntok);
        let olen = out.len();
        ntok = r.0;
        pos = r.1;
    }
    ntok
}

pub fn lg_core(input: &[u8], out: &mut [u32], pos0: usize, ntok0: usize, ks: usize, lo: usize, ih: usize, acc: u64, amax: usize) -> usize {
    let n = input.len();
    let mut head = [0u32; 32768];
    let mut long = [0u32; 32768];
    let mut pos = pos0;
    let mut ntok = ntok0;
    while pos < n {
        let sc = lg_scan(input, &mut head, &mut long, pos, ks, lo, acc, amax);
        let q = sc.0;
        let m = sc.1;
        let l = m % 512;
        let d = (m / 512) % 65536;
        let lim0 = q.wrapping_sub(pos);
        let lim1 = if l < 258 { 258 - l } else { 0 };
        let lim2 = q.wrapping_sub(d);
        let a = lg_min(lim0, lg_min(lim1, lim2));
        let e = if m != 0 { lg_bext(input, q, d, a) } else { 0 };
        let s = q.wrapping_sub(e);
        let r0 = lg_lits(input, out, pos, s, ntok);
        ntok = r0.0;
        pos = r0.1;
        if pos < n {
            let r = emit_step(input, out, pos, d, l.wrapping_add(e), 1, ntok);
            let olen = out.len();
            let npos = r.1;
            lg_insert(input, &mut head, &mut long, pos.wrapping_add(1), npos, ks, lo, ih);
            ntok = r.0;
            pos = npos;
        }
    }
    ntok
}

/// Genome class: 6-byte key, no long table, fast skip.
#[inline(never)]
pub fn lg_parse_d(input: &[u8], out: &mut [u32]) -> usize {
    lg_core(input, out, 0, 0, LG_D_KS, LG_D_LONG, LG_D_IH, LG_D_ACC, LG_D_AMAX)
}

/// High-entropy class: 4-byte key, fast skip.
#[inline(never)]
pub fn lg_parse_h(input: &[u8], out: &mut [u32]) -> usize {
    lg_core(input, out, 0, 0, LG_H_KS, LG_H_LONG, LG_H_IH, LG_H_ACC, LG_H_AMAX)
}

/// Runs the whole input through the mode's parser and returns `(ntok, n)`; mode 0 does nothing and returns
/// `(0, 0)` (the base parser then runs from position 0).
pub fn fl_part(input: &[u8], out: &mut [u32], mc: usize, fh: &[u32; 256]) -> (usize, usize) {
    let mode = mc % 8;
    if mode == 1 {
        if mc / 8 == 1 {
            fl_bf_parse(input, out, 0, 0)
        } else {
            fl_lit_parse(input, out)
        }
    } else if mode == 6 {
        fl_sm_parse(input, out)
    } else if mode == 7 {
        fl_im_parse(input, out, 0, 0)
    } else if mode == 2 {
        if G3_DNA == 1 {
            fl_g3_parse(input, out, 0, 0)
        } else if FL_DNA8_ON == 1 {
            (lg_parse_d(input, out), input.len())
        } else {
            let mut cost = [0u32; 256];
            fl_costs(fh, &mut cost);
            fl_dna_parse(input, out, &cost)
        }
    } else if mode == 4 {
        if FL_SM_ON == 1 && input.len() <= FL_SM_N {
            fl_sm_rle(input, out)
        } else {
            fl_rle_parse(input, out)
        }
    } else if mode == 5 {
        let mut cf = [0usize; 8];
        fl_config(mc / 8, &mut cf);
        fl_lazy_parse(input, out, fh, &cf)
    } else {
        (0, 0)
    }
}
// ============================ end of the jfloor module =============================================================


/// Build predecessor links; hs % 64 is the hash shift.
/// Bit 6 skips accelerated literal gaps; bit 7 limits lookahead on high-entropy inputs.
/// Matched interiors are retained when only bit 7 is set.
/// A 64K ring holds the 32K history plus at most 4096 bytes of lookahead.
/// Each node stores the original 4-byte predecessor and the optional 3-byte predecessor.
#[inline(never)]
pub fn prepare(input: &[u8], head: &mut [u32; 65536], prev: &mut [u32; 65536], head3: &mut [u32; 16384], shorts: &mut [u32; 4096], from: usize, pos: usize, hs: u32, h3on: usize) -> usize {
    let n = input.len();
    if from >= pos.saturating_add(2) || n < 16 {
        return from;
    }
    let sparse = hs >= 64;
    let hs0 = hs % 64;
    let upto = pos.saturating_add(if sparse { 2 } else { 4096 });
    let end = if upto < n - 15 { upto } else { n - 15 };
    let mut p = if hs % 128 >= 64 && pos > from { pos } else { from };
    while p < end {
        let h = hashp(input, p, hs0) % 65536;
        let old = head[h];
        let s3 = upd3(input, head3, p, h3on);
        if h3on == 1 { shorts[p % 4096] = s3 as u32; }
        prev[p % 65536] = old;
        head[h] = (p as u32).wrapping_add(1);
        p += 1;
    }
    end
}



/// Find a closer verified source for a retained previous-token prefix.
pub fn nearer_prefix(input: &[u8], pp: usize, nl: usize, oldd: usize) -> usize {
    0
}

/// Partial token fold; separate helper keeps one extracted suffix loop.
#[inline(always)]
pub fn public_cap(p: usize,l: usize,dist: usize,w: usize) -> usize {
    let a=w-1;let b=258-l;let c=p-dist;
    let ab=if a<b {a} else {b};if ab<c {ab} else {c}
}

#[inline(always)]
pub fn public_suffix_head(input: &[u8], p: usize, dist: usize, cap: usize, k: usize) -> (usize,bool) {
    if k >= cap {return (k,false);}
    if input[p-1-k] != input[p-1-k-dist] {return (k,false);}
    (k+1,true)
}

#[inline(always)]
pub fn public_suffix(input: &[u8],p: usize,dist: usize,cap: usize) -> usize {
    let mut k=0usize;
    let r=public_suffix_w2(input,p,dist,cap);k=r.0;
    if !r.1 {return k;}
    while cap-k>=8 && tw8(input,p-k-8)==tw8(input,p-k-8-dist) {k+=8;}
    while k<cap && input[p-1-k]==input[p-1-k-dist] {k+=1;}
    k
}

#[inline(always)]
pub fn public_price(w:usize,l:usize,k:usize,nl:usize)->bool {
    let a=lextra(l);let b=lextra(l+k);
    if w<258 && b<=a {true}
    else {lextra(nl).wrapping_add(b)<=lextra(w).wrapping_add(a)}
}

#[inline(always)]
pub fn public_partial(input: &[u8], out: &mut [u32], 
    nt: usize, p: usize, l: usize, dist: usize, t: u32, w: usize, k: usize, costs:&[u32;256]) -> (usize,usize,usize) {
    if w>=3 && w<=p {
        let pp=p-w;let oldd=((t-16777216)/256+1) as usize;
        let remain=w-k;
        if remain<=2 && k>0 {
            let oldcost=176usize.wrapping_add(lextra(w).wrapping_add(dextra(oldd)).wrapping_add(lextra(l)).wrapping_mul(16));
            let mut keep=1usize;let mut lc=0usize;let mut best=oldcost;let mut chosen=0usize;
            while keep<=2 && keep<w {
                lc=lc.wrapping_add(112);
                if keep>=remain {
                    let total=lc.wrapping_add(lextra(l+w-keep).wrapping_mul(16));
                    if total<best {best=total;chosen=keep;}
                }
                keep+=1;
            }
            if chosen>0 {
                out[nt-1]=input[pp] as u32;
                if chosen==2 {out[nt]=input[pp+1] as u32;}
                return (nt-1+chosen,pp+chosen,l+w-chosen);
            }
        }
    }
    (nt,p,l)
}

/// One fold step, called under the decoder invariant and legal pending match.
#[inline(always)]
pub fn public_one(input:&[u8],out:&mut[u32],nt:usize,p:usize,l:usize,dist:usize,t:u32,w:usize,k:usize)->(usize,usize,usize) {
    if public_price(w,l,1,w-1) {
        out[nt-1]=t-1;
        (nt,p-1,l+1)
    } else {(nt,p,l)}
}

#[inline(always)]
pub fn public_back_step(input: &[u8], out: &mut [u32], 
    nt: usize, p: usize, l: usize, dist: usize, back: usize, costs:&[u32;256]) -> (usize,usize,usize,usize) {
    let t=out[nt-1];
    if t<256 && public_lit_ok(input,p,dist) {
        (nt-1,p-1,l+1,back+1)
    } else if t>=16777216 {
        let w=((t-16777216)%256+3) as usize;
        let cap=public_cap(p,l,dist,w+1);
        let k=public_suffix(input,p,dist,cap);
        if k==w {
            (nt-1,p-w,l+w,back+1)
        } else {
            if w==4 && k<2 {return (nt,p,l,16);}
            if w>4 && k==1 {
                let r=public_one(input,out,nt,p,l,dist,t,w,k);
                return (r.0,r.1,r.2,16);
            }
            let r=public_partial(input,out,nt,p,l,dist,t,w,k,costs);
            (r.0,r.1,r.2,16)
        }
    } else {(nt,p,l,16)}
}

/// Generic backwards token joining with an unchanged endpoint.
#[inline(always)]
pub fn public_back(input: &[u8], out: &mut [u32], nt0: usize, pos0: usize,
    len0: usize, dist: usize, costs:&[u32;256]) -> (usize,usize,usize) {
    let mut nt=nt0;let mut p=pos0;let mut l=len0;let mut back=0usize;
    while back<16 && nt>0 && nt<=out.len() && p>dist && l<258 {
        let r=public_back_step(input,out,nt,p,l,dist,back,costs);
        nt=r.0;p=r.1;l=r.2;back=r.3;
    }
    (nt,p,l)
}

/// Fold gate filter: true only if the three bytes before `p` agree with those `dist` earlier (word compare).
#[inline(always)]
pub fn public_gate2(input: &[u8], p: usize, dist: usize) -> bool {
    if G_JOIN == 1 && p > dist + 3 { (tw4(input, p - 4) ^ tw4(input, p - 4 - dist)) >> 8 == 0 } else { false }
}

/// Literal fold test: true only if the byte before `p` agrees with the one `dist` earlier (word compare).
#[inline(always)]
pub fn public_lit_ok(input: &[u8], p: usize, dist: usize) -> bool {
    if p > dist + 3 { (tw4(input, p - 4) ^ tw4(input, p - 4 - dist)) >> 24 == 0 } else { false }
}

/// Suffix head from one word compare: `(k, more)` with `k <= cap` agreeing bytes before `p`; `more` = keep scanning.
#[inline(always)]
pub fn public_suffix_w2(input: &[u8], p: usize, dist: usize, cap: usize) -> (usize,bool) {
    if p - dist < 8 { return (0, true); }
    let x = tw8(input, p - 8) ^ tw8(input, p - 8 - dist);
    if x != 0 {
        let z = (x.leading_zeros() / 8) as usize;
        (if z < cap { z } else { cap }, false)
    } else {
        (if 8 < cap { 8 } else { cap }, true)
    }
}

/// Folding can only start when the byte before the pending match continues it; otherwise nothing changes.
#[inline(always)]
pub fn public_back_gate(input: &[u8], out: &mut [u32], nt0: usize, pos0: usize,
    len0: usize, dist: usize, costs:&[u32;256]) -> (usize,usize,usize) {
    if public_gate2(input,pos0,dist) {public_back(input,out,nt0,pos0,len0,dist,costs)} else {(nt0,pos0,len0)}
}

/// One verified gate for pending match. Folding independently verifies every
/// newly consumed earlier prefix, so resulting match follows by concatenation.
/// Outer endpoint is unchanged. No untrusted search fact is used to delete tokens.
#[inline(always)]
pub fn public_emit_join(input: &[u8], out: &mut [u32], 
    pos: usize, dist: usize, len: usize, ntok: usize, costs:&[u32;256]) -> (usize,usize) {
    if len>=3 && len<=258 && dist>=1 && dist<=32768 && dist<=pos && pos<input.len() && len<=input.len()-pos {
        let bk=public_back_gate(input,out,ntok,pos,len,dist,costs);
        out[bk.0]=16777216u32+((dist-1) as u32)*256+((bk.2-3) as u32);
        (bk.0+1,bk.1+bk.2)
    } else {emit_lits(input,out,pos,1,ntok)}
}

/// Price-lazy parse using immutable predecessor links prepared ahead in batches.
/// Each chosen match still passes through the original trusted emission path.

/// Compare lazy candidates by the raw-byte prices only outside their common span.
/// Costs are sampled fractional bits; this is a heuristic, not trusted code.
#[inline(always)]
pub fn public_span_better(input: &[u8], costs: &[u32;256], pos: usize,
    l1: usize, d1: usize, l2: usize, d2: usize, ex: usize) -> usize {
    let n=input.len();
    if l1<3 || l2<l1 || l2>258 || pos>=n || l2>=n-pos {return 0;}
    let first=if ex==1 {0} else {(costs[input[pos] as usize] as usize).wrapping_add(80)};
    let aa=dextra(d1).wrapping_add(lextra(l1)).wrapping_mul(16);
    let bb=first.wrapping_add(dextra(d2).wrapping_add(lextra(l2+ex)).wrapping_mul(16));
    let mut tail=0usize;let mut j=l1;
    while j<=l2 {
        tail=tail.wrapping_add((costs[input[pos+j] as usize] as usize).wrapping_add(64));
        if tail.wrapping_add(aa)>bb {return 1;}
        j+=1;
    }
    0
}

#[inline(always)]
pub fn g_match(input: &[u8],p: usize,cc: usize,cap: usize) -> usize {
    if cc >= p { return 0; }
    let l0 = fast_len(input, cc, p, cap);
    let l = l0;
    let d = p.wrapping_sub(cc);
    if l < 3 || (l == 3 && d > G_MAX3) || d < 1 || d > G_WIN || cc >= p {
        0
    } else { l | d.wrapping_mul(512) }
}

#[inline(always)]
pub fn g_lazy_eval(input: &[u8], p: usize, v: u64, c8: usize, c4: usize, cap: usize, min: usize) -> usize {

    let lim = if p < G_WIN { p } else { G_WIN };
    if p.wrapping_sub(c8) < lim {
        let cc = c8.wrapping_sub(1);
        if (ld8(input, cc) ^ v) & G_HLMASK == 0 {
            if min > 8 {
                if min > cap { return 0; }
                let off = min.wrapping_sub(8);
                if ld8(input, cc.wrapping_add(off)) != ld8(input, p.wrapping_add(off)) { return 0; }
            }
            return g_match(input, p, cc, cap);
        }
    }
    0
}

#[inline(always)]
pub fn g3_lazy_eval(input: &[u8], p: usize, v: u64, c8: usize, c4: usize, c3: usize, cap: usize, min: usize) -> usize {

    let lim = if p < G_WIN { p } else { G_WIN };
    if p.wrapping_sub(c8) < lim {
        let cc = c8.wrapping_sub(1);
        if (ld8(input, cc) ^ v) & G_HLMASK == 0 {
            if min > 8 {
                if min > cap { return 0; }
                let off = min.wrapping_sub(8);
                if ld8(input, cc.wrapping_add(off)) != ld8(input, p.wrapping_add(off)) { return 0; }
            }
            return g_match(input, p, cc, cap);
        }
    }
    if p.wrapping_sub(c4) >= lim { return if c3 != 0 && min <= 3 { g3_cand3(input, p, v, c3) } else { 0 }; }
    let cc = c4.wrapping_sub(1);
    let x = ld8(input, cc) ^ v;
    let mask = if G_M3 == 1 { 16777215u64 } else { 4294967295u64 };
    if x & mask != 0 { return if c3 != 0 && min <= 3 { g3_cand3(input, p, v, c3) } else { 0 }; }
    if min > 8 {
        if x != 0 || min > cap { return 0; }
        let off = min.wrapping_sub(8);
        if ld8(input, cc.wrapping_add(off)) != ld8(input, p.wrapping_add(off)) { return 0; }
    }
    let m = g_match(input, p, cc, cap);
    if m % 512 < min { 0 } else { m }
}

#[inline(always)]
pub fn g_len(input: &[u8], a: usize, b: usize, cap: usize) -> usize {
    let mut l = 8usize;
    let mut go = 1usize;
    let mut it = 0usize;
    while go == 1 && it < 40 {
        if l < cap {
            let x = ld8(input, a.wrapping_add(l)) ^ ld8(input, b.wrapping_add(l));
            let k = if x == 0 { 8 } else { first_diff(x) };
            l = l.wrapping_add(k);
            go = if x == 0 { 1 } else { 0 };
        } else { go = 0; }
        it += 1;
    }
    if l > cap { cap } else { l }
}

/// Hash of the low 4 bytes of `v`: 24 bits, bucket = the top 16 (`h / 256`), tag = the low 8 (`h % 256`).
pub fn g_h4(v: u64) -> usize {
    ((v.wrapping_mul(0xCF1BBCDC9E3779B1) as u32) >> 8) as usize
}

/// Hash of the 8 bytes `v`: 24 bits, bucket = the top 16 (`h / 256`), tag = the low 8 (`h % 256`).
pub fn g_h8(v: u64) -> usize {
    (v.wrapping_mul(0xCF1BBCDC9E3779B1) >> 40) as usize
}

/// Long-table entry for position `p` under the short hash `h4`: `(p + 1) % 2^24 | tag << 24`.
#[inline(always)]
pub fn g_ent(h4: usize, p: usize) -> u32 {
    ((p as u32).wrapping_add(1) % 16777216) | ((h4 % 256) as u32) << 24
}

/// Decode the long entry `e` under the short hash `h4`: the candidate position + 1 if the tag matches, else 0.
#[inline(always)]
pub fn g_dec(h4: usize, e: u32) -> usize {
    (e ^ ((h4 as u32) << 24)) as usize
}

/// Evaluate the decoded entries `c8`, `c4` (position + 1, 0 = none)  at
/// `p` for the word `v`: the long candidate if its 8 bytes agree, else the short one; `len | dist << 9`, or 0.
#[inline(always)]
pub fn g_eval(input: &[u8], p: usize, v: u64, c8: usize, c4: usize, cap: usize) -> usize {

    let lim = if p < G_WIN { p } else { G_WIN };
    if p.wrapping_sub(c8) < lim {
        let cc = c8.wrapping_sub(1);
        if (ld8(input, cc) ^ v) & G_HLMASK == 0 {
            return g_match(input, p, cc, cap);
        }
    }
    if p.wrapping_sub(c4) >= lim { return 0; }
    let cc = c4.wrapping_sub(1);
    let x = ld8(input, cc) ^ v;
    let mask = if G_M3 == 1 { 16777215u64 } else { 4294967295u64 };
    if x & mask != 0 { return 0; }
    g_match(input, p, cc, cap)
}

/// Read the entries at the buckets of `h4`, `h8`, decoded: `(c4, c8)`.
#[inline(always)]
pub fn g_tab(t4: &[u32; 65536], t8: &[u32; 65536], h4: usize, h8: usize) -> (usize, usize) {
    (t4[(h4 / 256) % 65536] as usize, g_dec(h8, t8[(h8 / 256) % 65536]))
}

/// Insert `p` at its buckets.
#[inline(always)]
pub fn g_put(t4: &mut [u32; 65536], t8: &mut [u32; 65536], h4: usize, h8: usize, p: usize) {
    t4[(h4 / 256) % 65536] = (p as u32).wrapping_add(1);
    t8[(h8 / 256) % 65536] = g_ent(h8, p);
}

/// Insert every G_TS-th position of `from .. to`.
#[inline(always)]
pub fn g_insert_stride(input: &[u8], t4: &mut [u32; 65536], t8: &mut [u32; 65536], from: usize, to: usize, ts: usize) {
    let n = input.len();
    let mut p = from;
    while p < to && 16 <= n && p <= n - 16 {
        let v = ld8(input, p);
        g_put(t4, t8, g_h4(v), g_h8(v), p);
        p = p + (if ts == 0 || ts > 16 { 1 } else { ts });
    }
}

/// Insert one position `p` (the caller checks `p <= n - 16`).
#[inline(always)]
pub fn g_ins1(input: &[u8], t4: &mut [u32; 65536], t8: &mut [u32; 65536], p: usize) {
    let v = ld8(input, p);
    g_put(t4, t8, g_h4(v), g_h8(v), p);
}

/// Insert position `p` if `p < e`.
#[inline(always)]
pub fn g_ins_if(input: &[u8], t4: &mut [u32; 65536], t8: &mut [u32; 65536], p: usize, e: usize) {
    if p < e {
        g_ins1(input, t4, t8, p);
    }
}

/// Insert the interior of an emitted match `from .. to`: its first G_IH (<= 4) positions, then the last one
/// (G_IT = 1). Positions past the range repeat the previous insert (idempotent), so the inserts are branch-free.
#[inline(always)]
pub fn g_insert_match(input: &[u8], t4: &mut [u32; 65536], t8: &mut [u32; 65536], from: usize, to: usize, skip: usize) {
    let n = input.len();
    if n < 16 {
        return;
    }
    let lim = n - 15;
    let start = if skip == 1 { from.wrapping_add(1) } else { from };
    let a = from.wrapping_add(G_IH);
    let a2 = if a < to { a } else { to };
    let e = if a2 < lim { a2 } else { lim };
    if start < e {
        g_ins1(input, t4, t8, start);
        let s1 = start.wrapping_add(1);
        let p1 = if s1 < e { s1 } else { start };
        g_ins1(input, t4, t8, p1);
        let s2 = start.wrapping_add(2);
        let p2 = if s2 < e { s2 } else { p1 };
        g_ins1(input, t4, t8, p2);
        let s3 = start.wrapping_add(3);
        g_ins_if(input, t4, t8, s3, e);
        let p3 = if s3 < e { s3 } else { p2 };
        let b = to.wrapping_sub(G_IT);
        let b2 = if b > a2 { if b < to { b } else { a2 } } else { a2 };
        let pt = if b2 < to && b2 < lim { b2 } else { p3 };
        g_ins1(input, t4, t8, pt);
    } else {
        let b = to.wrapping_sub(G_IT);
        let b2 = if b > a2 { if b < to { b } else { a2 } } else { a2 };
        if b2 < to && b2 < lim { g_ins1(input, t4, t8, b2); }
    }
}

/// Probe `p` (inserting it): the best candidate there or 0.
#[inline(always)]
pub fn g_probe(input: &[u8], t4: &mut [u32; 65536], t8: &mut [u32; 65536], p: usize) -> usize {
    let n = input.len();
    if n < 16 || p > n - 16 {
        return 0;
    }
    let v = ld8(input, p);
    let h4 = g_h4(v);
    let h8 = g_h8(v);
    let e = g_tab(t4, t8, h4, h8);
    g_put(t4, t8, h4, h8, p);
    let rem = n - p - 8;
    let cap = if rem < 258 { rem } else { 258 };
    g_eval(input, p, v, e.1, e.0, cap)
}

/// Software-pipelined scan from `pos` with literal-run acceleration: each iteration reads the table entries of the
/// next probe position before inserting and evaluating the current one. Returns `(q, m)` = the first position with
/// a match and the packed match, or `(n, 0)`.
#[inline(never)]
pub fn g_scan(input: &[u8], t4: &mut [u32; 65536], t8: &mut [u32; 65536], pos: usize, acc: u64, carry: usize, cpre: usize) -> (usize, usize, usize) {
    let n = input.len();
    if carry != 0 {
        return (pos, carry, cpre);
    }
    if n < 16 || pos > n - 16 {
        return (n, 0, 0);
    }
    let mut p = pos;
    let mut k = 0usize;
    let mut m = 0usize;
    let mut v = ld8(input, p);
    let mut e = g_tab(t4, t8, g_h4(v), g_h8(v));
    let mut pre = 0usize;
    while m == 0 && p <= n - 16 {
        let over = ((k as u64) >> (acc % 64)) as usize;
        let st = if over < G_AMAX { over + 1 } else { G_AMAX };
        let q = p + st;
        let vq = if q <= n - 16 { ld8(input, q) } else { 0 };
        let hq4 = g_h4(vq);
        let hq8 = g_h8(vq);
        let eq = g_tab(t4, t8, hq4, hq8);
        g_put(t4, t8, g_h4(v), g_h8(v), p);
        let rem = n - p - 8;
        let cap = if rem < 258 { rem } else { 258 };
        m = g_eval(input, p, v, e.1, e.0, cap);
        if m != 0 {
            pre = if st == 1 { 1 } else { 0 };
            break;
        }
        p = q;
        v = vq;
        e = eq;
        k += 1;
    }
    if m == 0 { (n, 0, 0) } else { (p, m, pre) }
}

/// Lazy probe of `q` = pos + 1 from the scan's hashes `pre` (bit 0 = valid, h4 in bits 1..25, h8 in bits 25..49;
/// the table lines were touched by the scan's prefetch); falls back to a full probe.
#[inline(always)]
pub fn g_lazy(input: &[u8], t4: &mut [u32; 65536], t8: &mut [u32; 65536], q: usize, pre: usize, want: usize, min: usize) -> usize {
    let n = input.len();
    if want == 0 {
        return 0;
    }
    if pre % 2 == 0 {
        let m = g_probe(input, t4, t8, q);
        return if m%512 < min {0} else {m};
    }
    if n < 16 || q > n - 16 {
        return 0;
    }
    let v = ld8(input, q);
    let h4 = g_h4(v);
    let h8 = g_h8(v);
    let e = g_tab(t4, t8, h4, h8);
    let c4 = e.0;
    let c8 = e.1;
    g_put(t4, t8, h4, h8, q);
    let rem = n - q - 8;
    let cap = if rem < 258 { rem } else { 258 };
    g_lazy_eval(input, q, v, c8, c4, cap, min)
}

#[inline(always)]
pub fn g_plain_choose(input: &[u8], costs: &[u32;256], pos: usize, m1: usize, s2: usize) -> (usize,usize) {
    let l1=m1%512; let d1=(m1/512)%65536;
    let l2=s2%512; let d2=(s2/512)%65536;
    let ex=if s2!=0 {ext_ok(input,pos,l2,d2)} else {0};
    let take=if s2!=0 {public_span_better(input,costs,pos,l1,d1,l2,d2,ex)} else {0};
    if take==1 {if ex==1 {(s2.wrapping_add(1),0)} else {(0,s2)}} else {(m1,0)}
}

#[inline(always)]
pub fn g_choose(input: &[u8], costs: &[u32;256], pos: usize, m1: usize, s2: usize) -> (usize,usize) {
    let l1=m1%512;
    let l2=s2%512;
    if s2==0 || l2<l1 {return (m1,0);}
    let d1=(m1/512)%65536;
    let d2=(s2/512)%65536;
    let ex=ext_ok(input,pos,l2,d2);
    let take=if l2.wrapping_add(ex)>l1.wrapping_add(2) {1} else {public_span_better(input,costs,pos,l1,d1,l2,d2,ex)};
    if take==0 {return (m1,0);}
    if ex==1 {(s2.wrapping_add(1),0)} else {(0,s2)}
}

pub fn main_parse_a(input: &[u8], out: &mut [u32], pos0: usize, ntok0: usize, hist: &[u32; 256], e: usize, low: usize) -> usize {
    let n = input.len();
    let mut t4 = [0u32; 65536];
    let mut t8 = [0u32; 65536];
    let mut span_costs=[0u32;256];
    fl_costs(hist,&mut span_costs);
    let acc = if low == 1 { 63u64 } else { G_ACC };
    let mut pos = pos0;
    let mut ntok = ntok0;
    let mut carry = 0usize;
    let mut cpre = 0usize;
    while pos < n {
        let sc = g_scan(input, &mut t4, &mut t8, pos, acc, carry, cpre);
        let q = sc.0;
        let m1 = sc.1;
        let pre = sc.2;
        if q > pos {
            let r = emit_lits(input, out, pos, q - pos, ntok);
            let olen = out.len();
            ntok = r.0;
            pos = r.1;
            carry = if q < n { m1 } else { 0 };
            cpre = pre;
        } else if m1 != 0 {
            let l1 = m1 % 512;
            let d1 = (m1 / 512) % 65536;
            let want = if l1 < G_LZT { 1usize } else { 0usize };
            let s2 = g_lazy(input, &mut t4, &mut t8, pos.wrapping_add(1), pre, want, l1);
            let choice = g_choose(input,&span_costs,pos,m1,s2);
            let l = choice.0 % 512;
            let d = (choice.0 / 512) % 65536;
            let r = public_emit_join(input, out, pos, d, l, ntok, &span_costs);
            let olen = out.len();
            let npos = r.1;
            g_insert_match(input, &mut t4, &mut t8, pos.wrapping_add(1), npos, want);
            carry = choice.1;
            cpre = 0;
            ntok = r.0;
            pos = npos;
        } else {
            let r = emit_lits(input, out, pos, 1, ntok);
            let olen = out.len();
            carry = 0;
            ntok = r.0;
            pos = r.1;
        }
    }
    ntok
}

/// Hash of the low 4 bytes of `v`: 24 bits, bucket = the top 16 (`h / 256`), tag = the low 8 (`h % 256`).
pub fn gh_h4(v: u64) -> usize {
    ((v as u32).wrapping_mul(2654435761) >> 8) as usize
}

/// Hash of the 8 bytes `v`: 24 bits, bucket = the top 16 (`h / 256`), tag = the low 8 (`h % 256`).
pub fn gh_h8(v: u64) -> usize {
    ((v & G_HLMASK).wrapping_mul(0x9E3779B97F4A7C15) >> 40) as usize
}

/// Long-table entry for position `p` under the short hash `h4`: `(p + 1) % 2^24 | tag << 24`.
pub fn gh_ent(h4: usize, p: usize) -> u32 {
    ((p as u32).wrapping_add(1) % 16777216) | ((h4 % 256) as u32) << 24
}

/// Decode the long entry `e` under the short hash `h4`: the candidate position + 1 if the tag matches, else 0.
pub fn gh_dec(h4: usize, e: u32) -> usize {
    if (e / 16777216) as usize == h4 % 256 { (e % 16777216) as usize } else { 0 }
}

/// Evaluate the decoded entries `c8`, `c4` (position + 1, 0 = none)  at
/// `p` for the word `v`: the long candidate if its 8 bytes agree, else the short one; `len | dist << 9`, or 0.
#[inline(always)]
pub fn gh_eval(input: &[u8], p: usize, v: u64, c8: usize, c4: usize, cap: usize) -> usize {
    let lim = if p < G_WIN { p } else { G_WIN };
    let ok8 = if p.wrapping_sub(c8) < lim { 1usize } else { 0usize };
    let x8 = if ok8 == 1 { (ld8(input, c8.wrapping_sub(1)) ^ v) & G_HLMASK } else { 1 };
    let ok4 = if p.wrapping_sub(c4) < lim { 1usize } else { 0usize };
    let x4 = if x8 == 0 { 0 } else if ok4 == 1 { ld8(input, c4.wrapping_sub(1)) ^ v } else { 1 };
    let mask = if G_M3 == 1 { 16777215u64 } else { 4294967295u64 };
    if x8 != 0 && x4 & mask != 0 {
        return 0;
    }
    let c = if x8 == 0 { c8 } else { c4 };
    let cc = c.wrapping_sub(1);
    g_match(input, p, cc, cap)
}

/// Read the entries at the buckets of `h4`, `h8`, decoded: `(c4, c8)`.
#[inline(always)]
pub fn gh_tab(t4: &[u32; 65536], t8: &[u32; 65536], h4: usize, h8: usize) -> (usize, usize) {
    (t4[(h4 / 256) % 65536] as usize, 0)
}

/// Insert `p` at its buckets.
#[inline(always)]
pub fn gh_put(t4: &mut [u32; 65536], t8: &mut [u32; 65536], h4: usize, h8: usize, p: usize) {
    t4[(h4 / 256) % 65536] = (p as u32).wrapping_add(1);
}

/// Insert every G_TS-th position of `from .. to`.
#[inline(always)]
pub fn gh_insert_stride(input: &[u8], t4: &mut [u32; 65536], t8: &mut [u32; 65536], from: usize, to: usize, ts: usize) {
    let n = input.len();
    let mut p = from;
    while p < to && 16 <= n && p <= n - 16 {
        let v = ld8(input, p);
        gh_put(t4, t8, gh_h4(v), gh_h8(v), p);
        p = p + (if ts == 0 || ts > 16 { 1 } else { ts });
    }
}

/// Insert the interior of an emitted match `from .. to`: its first G_IH positions, then every G_TS-th up to the last G_IT.
#[inline(always)]
pub fn gh_insert_match(input: &[u8], t4: &mut [u32; 65536], t8: &mut [u32; 65536], from: usize, to: usize) {
    let a = from.wrapping_add(G_IH);
    let a2 = if a < to { a } else { to };
    let b = to.wrapping_sub(G_IT);
    let b2 = if b > a2 { if b < to { b } else { a2 } } else { a2 };
    gh_insert_stride(input, t4, t8, from, a2, 1);
    gh_insert_stride(input, t4, t8, b2, to, G_TS);
}

/// Probe `p` (inserting it): the best candidate there or 0.
#[inline(always)]
pub fn gh_probe(input: &[u8], t4: &mut [u32; 65536], t8: &mut [u32; 65536], p: usize) -> usize {
    let n = input.len();
    if n < 16 || p > n - 16 {
        return 0;
    }
    let v = ld8(input, p);
    let h4 = gh_h4(v);
    let h8 = gh_h8(v);
    let e = gh_tab(t4, t8, h4, h8);
    gh_put(t4, t8, h4, h8, p);
    let rem = n - p - 8;
    let cap = if rem < 258 { rem } else { 258 };
    gh_eval(input, p, v, e.1, e.0, cap)
}

/// Software-pipelined scan from `pos` with literal-run acceleration: each iteration reads the table entries of the
/// next probe position before inserting and evaluating the current one. Returns `(q, m)` = the first position with
/// a match and the packed match, or `(n, 0)`.
#[inline(never)]
pub fn gh_scan(input: &[u8], t4: &mut [u32; 65536], t8: &mut [u32; 65536], pos: usize, acc: u64, carry: usize, cpre: usize) -> (usize, usize, usize) {
    let n = input.len();
    if carry != 0 {
        return (pos, carry, cpre);
    }
    if n < 16 || pos > n - 16 {
        return (n, 0, 0);
    }
    let mut p = pos;
    let mut k = 0usize;
    let mut m = 0usize;
    let mut v = ld8(input, p);
    let mut h4 = gh_h4(v);
    let mut h8 = gh_h8(v);
    let mut e = gh_tab(t4, t8, h4, h8);
    let mut pre = 0usize;
    while m == 0 && p <= n - 16 {
        let over = ((k as u64) >> (acc % 64)) as usize;
        let st = if over < G_AMAX { over + 1 } else { G_AMAX };
        let q = p + st;
        pre = if st == 1 { 1 } else { 0 };
        let vq = if q <= n - 16 { ld8(input, q) } else { 0 };
        let hq4 = gh_h4(vq);
        let hq8 = gh_h8(vq);
        let eq = gh_tab(t4, t8, hq4, hq8);
        gh_put(t4, t8, h4, h8, p);
        let rem = n - p - 8;
        let cap = if rem < 258 { rem } else { 258 };
        m = gh_eval(input, p, v, e.1, e.0, cap);
        if m != 0 {
            pre = pre | (hq4 % 16777216).wrapping_mul(2) | (hq8 % 16777216).wrapping_mul(33554432);
            break;
        }
        p = q;
        v = vq;
        h4 = hq4;
        h8 = hq8;
        e = eq;
        k += 1;
    }
    if m == 0 { (n, 0, 0) } else { (p, m, pre) }
}

/// Lazy probe of `q` = pos + 1 from the scan's hashes `pre` (bit 0 = valid, h4 in bits 1..25, h8 in bits 25..49;
/// the table lines were touched by the scan's prefetch); falls back to a full probe.
#[inline(always)]
pub fn gh_lazy(input: &[u8], t4: &mut [u32; 65536], t8: &mut [u32; 65536], q: usize, pre: usize, want: usize) -> usize {
    let n = input.len();
    if want == 0 {
        return 0;
    }
    if pre % 2 == 0 {
        return gh_probe(input, t4, t8, q);
    }
    if n < 16 || q > n - 16 {
        return 0;
    }
    let h4 = (pre / 2) % 16777216;
    let h8 = (pre / 33554432) % 16777216;
    let e = gh_tab(t4, t8, h4, h8);
    let c4 = e.0;
    let c8 = e.1;
    gh_put(t4, t8, h4, h8, q);
    let v = ld8(input, q);
    let rem = n - q - 8;
    let cap = if rem < 258 { rem } else { 258 };
    gh_eval(input, q, v, c8, c4, cap)
}

pub fn main_parse_high(input: &[u8], out: &mut [u32], pos0: usize, ntok0: usize, hist: &[u32; 256], e: usize, low: usize) -> usize {
    let n = input.len();
    let mut t4 = [0u32; 65536];
    let mut t8 = [0u32; 65536];
    let mut span_costs=[0u32;256];
    fl_costs(hist,&mut span_costs);
    let acc = if low == 1 { 63u64 } else { 8u64 };
    let mut pos = pos0;
    let mut ntok = ntok0;
    let mut carry = 0usize;
    let mut cpre = 0usize;
    while pos < n {
        let sc = gh_scan(input, &mut t4, &mut t8, pos, acc, carry, cpre);
        let q = sc.0;
        let m1 = sc.1;
        let pre = sc.2;
        if q > pos {
            let r = emit_lits(input, out, pos, q - pos, ntok);
            let olen = out.len();
            ntok = r.0;
            pos = r.1;
            carry = if q < n { m1 } else { 0 };
            cpre = pre;
        } else if m1 != 0 {
            let l1 = m1 % 512;
            let want = if l1 < 0 { 1usize } else { 0usize };
            let s2 = gh_lazy(input, &mut t4, &mut t8, pos.wrapping_add(1), pre, want);
            let choice=g_plain_choose(input,&span_costs,pos,m1,s2);
            let l=choice.0%512;
            let d=(choice.0/512)%65536;
            let r = public_emit_join(input, out, pos, d, l, ntok, &span_costs);
            let olen = out.len();
            let npos = r.1;
            gh_insert_match(input, &mut t4, &mut t8, pos.wrapping_add(1), npos);
            carry = choice.1;
            cpre = 0;
            ntok = r.0;
            pos = npos;
        } else {
            let r = emit_lits(input, out, pos, 1, ntok);
            let olen = out.len();
            carry = 0;
            ntok = r.0;
            pos = r.1;
        }
    }
    ntok
}

// ===== lane b: the same engine with a 3-byte table =====
/// 16-bit hash of the low 3 bytes of `v`.
pub fn g3_h3(v: u64) -> usize {
    (((v as u32) << 8).wrapping_mul(2654435761) >> 16) as usize
}

/// 3-byte candidate at `p`: `3 | d << 9` when the entry `c3` agrees on 3 bytes within G_MAX3, else 0.
#[inline(always)]
pub fn g3_cand3(input: &[u8], p: usize, v: u64, c3: usize) -> usize {
    let lim = if p < G_MAX3 { p } else { G_MAX3 };
    if p.wrapping_sub(c3) >= lim {
        return 0;
    }
    let cc = c3.wrapping_sub(1);
    let x = ld8(input, cc) ^ v;
    if x & 16777215 != 0 || cc >= p || fast_len(input, cc, p, 3) < 3 {
        return 0;
    }
    3 | p.wrapping_sub(cc).wrapping_mul(512)
}

/// Insert `p` into the 3-byte table at `h3`, returning the displaced entry.
#[inline(always)]
pub fn g3_put3(t3: &mut [u32; 65536], h3: usize, p: usize) -> usize {
    let c = t3[h3 % 65536] as usize;
    t3[h3 % 65536] = (p as u32).wrapping_add(1);
    c
}

/// Insert every G_TS-th position of `from .. to`.
#[inline(always)]
pub fn g3_insert_stride(input: &[u8], t4: &mut [u32; 65536], t8: &mut [u32; 65536], t3: &mut [u32; 65536], from: usize, to: usize, ts: usize, m3: usize) {
    let n = input.len();
    let mut p = from;
    while p < to && 16 <= n && p <= n - 16 {
        let v = ld8(input, p);
        g_put(t4, t8, g_h4(v), g_h8(v), p);
        if m3 == 1 { g3_put3(t3, g3_h3(v), p); }
        p = p + (if ts == 0 || ts > 16 { 1 } else { ts });
    }
}

/// Insert the interior of an emitted match `from .. to`: its first G_IH positions, then every G_TS-th up to the last G_IT.
#[inline(always)]
pub fn g3_insert_match(input: &[u8], t4: &mut [u32; 65536], t8: &mut [u32; 65536], t3: &mut [u32; 65536], from: usize, to: usize, m3: usize, skip: usize) {
    let start = if skip == 1 { from.wrapping_add(1) } else { from };
    let a = from.wrapping_add(G_IH);
    let a2 = if a < to { a } else { to };
    let b = to.wrapping_sub(G_IT);
    let b2 = if b > a2 { if b < to { b } else { a2 } } else { a2 };
    g3_insert_stride(input, t4, t8, t3, start, a2, 1, m3);
    g3_insert_stride(input, t4, t8, t3, b2, to, G_TS, m3);
}

/// Probe `p` (inserting it): the best candidate there or 0.
#[inline(always)]
pub fn g3_probe(input: &[u8], t4: &mut [u32; 65536], t8: &mut [u32; 65536], t3: &mut [u32; 65536], p: usize, m3: usize) -> usize {
    let n = input.len();
    if n < 16 || p > n - 16 {
        return 0;
    }
    let v = ld8(input, p);
    let h4 = g_h4(v);
    let h8 = g_h8(v);
    let e = g_tab(t4, t8, h4, h8);
    g_put(t4, t8, h4, h8, p);
    let c3 = if m3 == 1 { g3_put3(t3, g3_h3(v), p) } else { 0 };
    let rem = n - p - 8;
    let cap = if rem < 258 { rem } else { 258 };
    g3_eval(input, p, v, e.1, e.0, c3, cap)
}

/// Software-pipelined scan from `pos` with literal-run acceleration: each iteration reads the table entries of the
/// next probe position before inserting and evaluating the current one. Returns `(q, m)` = the first position with
/// a match and the packed match, or `(n, 0)`.
#[inline(always)]
pub fn g3_scan(input: &[u8], t4: &mut [u32; 65536], t8: &mut [u32; 65536], t3: &mut [u32; 65536], pos: usize, acc: u64, m3: usize, carry: usize, cpre: usize) -> (usize, usize, usize) {
    let n = input.len();
    if carry != 0 {
        return (pos, carry, cpre);
    }
    if n < 16 || pos > n - 16 {
        return (n, 0, 0);
    }
    let mut p = pos;
    let mut k = 0usize;
    let mut m = 0usize;
    let mut v = ld8(input, p);
    let mut h4 = g_h4(v);
    let mut h8 = g_h8(v);
    let mut e = g_tab(t4, t8, h4, h8);
    let mut pre = 0usize;
    while m == 0 && p <= n - 16 {
        let over = ((k as u64) >> (acc % 64)) as usize;
        let st = if over < G_AMAX { over + 1 } else { G_AMAX };
        let q = p + st;
        pre = if st == 1 { 1 } else { 0 };
        let vq = if q <= n - 16 { ld8(input, q) } else { 0 };
        let hq4 = g_h4(vq);
        let hq8 = g_h8(vq);
        let eq = g_tab(t4, t8, hq4, hq8);
        g_put(t4, t8, h4, h8, p);
        let c3 = if m3 == 1 { g3_put3(t3, g3_h3(v), p) } else { 0 };
        let rem = n - p - 8;
        let cap = if rem < 258 { rem } else { 258 };
        m = g3_eval(input, p, v, e.1, e.0, c3, cap);
        if m != 0 {
            pre = pre | (hq4 % 16777216).wrapping_mul(2) | (hq8 % 16777216).wrapping_mul(33554432);
            break;
        }
        p = q;
        v = vq;
        h4 = hq4;
        h8 = hq8;
        e = eq;
        k += 1;
    }
    if m == 0 { (n, 0, 0) } else { (p, m, pre) }
}

/// Lazy probe of `q` = pos + 1 from the scan's hashes `pre` (bit 0 = valid, h4 in bits 1..25, h8 in bits 25..49;
/// the table lines were touched by the scan's prefetch); falls back to a full probe.
#[inline(always)]
pub fn g3_lazy(input: &[u8], t4: &mut [u32; 65536], t8: &mut [u32; 65536], t3: &mut [u32; 65536], q: usize, pre: usize, m3: usize, want: usize, min: usize) -> usize {
    let n = input.len();
    if want == 0 {
        return 0;
    }
    if pre % 2 == 0 {
        return g3_probe(input, t4, t8, t3, q, m3);
    }
    if n < 16 || q > n - 16 {
        return 0;
    }
    let h4 = (pre / 2) % 16777216;
    let h8 = (pre / 33554432) % 16777216;
    let e = g_tab(t4, t8, h4, h8);
    let c4 = e.0;
    let c8 = e.1;
    g_put(t4, t8, h4, h8, q);
    let v = ld8(input, q);
    let c3 = if m3 == 1 { g3_put3(t3, g3_h3(v), q) } else { 0 };
    let rem = n - q - 8;
    let cap = if rem < 258 { rem } else { 258 };
    g3_lazy_eval(input, q, v, c8, c4, c3, cap, min)
}

/// Evaluate the decoded entries `c8`, `c4` (position + 1, 0 = none)  at
/// `p` for the word `v`: the long candidate if its 8 bytes agree, else the short one; `len | dist << 9`, or 0.
#[inline(always)]
pub fn g3_eval(input: &[u8], p: usize, v: u64, c8: usize, c4: usize, c3: usize, cap: usize) -> usize {

    let lim = if p < G_WIN { p } else { G_WIN };
    if p.wrapping_sub(c8) < lim {
        let cc = c8.wrapping_sub(1);
        if (ld8(input, cc) ^ v) & G_HLMASK == 0 {
            return g_match(input, p, cc, cap);
        }
    }
    if p.wrapping_sub(c4) >= lim { return if c3 != 0 { g3_cand3(input, p, v, c3) } else { 0 }; }
    let cc = c4.wrapping_sub(1);
    let x = ld8(input, cc) ^ v;
    let mask = if G_M3 == 1 { 16777215u64 } else { 4294967295u64 };
    if x & mask != 0 { return if c3 != 0 { g3_cand3(input, p, v, c3) } else { 0 }; }
    g_match(input, p, cc, cap)
}

pub fn main_parse_b(input: &[u8], out: &mut [u32], pos0: usize, ntok0: usize, hist: &[u32; 256], e: usize, low: usize) -> usize {
    let n = input.len();
    let mut t4 = [0u32; 65536];
    let mut t8 = [0u32; 65536];
    let mut t3 = [0u32; 65536];
    let mut span_costs=[0u32;256];
    fl_costs(hist,&mut span_costs);
    let acc = if low == 1 { 63u64 } else { G_ACC };
    let m3 = 1usize;
    let mut pos = pos0;
    let mut ntok = ntok0;
    let mut carry = 0usize;
    let mut cpre = 0usize;
    while pos < n {
        let sc = g3_scan(input, &mut t4, &mut t8, &mut t3, pos, acc, m3, carry, cpre);
        let q = sc.0;
        let m1 = sc.1;
        let pre = sc.2;
        if q > pos {
            let r = emit_lits(input, out, pos, q - pos, ntok);
            let olen = out.len();
            ntok = r.0;
            pos = r.1;
            carry = if q < n { m1 } else { 0 };
            cpre = pre;
        } else if m1 != 0 {
            let l1 = m1 % 512;
            let want = if l1 < 8 { 1usize } else { 0usize };
            let s2 = g3_lazy(input, &mut t4, &mut t8, &mut t3, pos.wrapping_add(1), pre, m3, want, l1);
            let choice=g_plain_choose(input,&span_costs,pos,m1,s2);
            let l=choice.0%512;
            let d=(choice.0/512)%65536;
            let r = public_emit_join(input, out, pos, d, l, ntok, &span_costs);
            let olen = out.len();
            let npos = r.1;
            g3_insert_match(input, &mut t4, &mut t8, &mut t3, pos.wrapping_add(1), npos, m3, want);
            carry = choice.1;
            cpre = 0;
            ntok = r.0;
            pos = npos;
        } else {
            let r = emit_lits(input, out, pos, 1, ntok);
            let olen = out.len();
            carry = 0;
            ntok = r.0;
            pos = r.1;
        }
    }
    ntok
}

// ============================ lane R1 (round 9): the N2 text loop `gr_text` ======================================
// R1_TEXT == 1 routes the base text inputs (main_parse's lane a) to `gr_text` instead of `main_parse_a` (m10 = 0).
// Same tokens as main_parse_a (G's scan, G's tables and inserts, cand25's backward join), cheaper loop: one iteration
// = scan for the next match (`gr_scan` = g_scan without the carry, its first table entries loaded by the caller),
// insert the match interior (`gr_insert_match` = g_insert_match without its repeated insert), load the entries of
// the next scan position, write the literal run before the match (emit_lits) and the match (public_emit_join).
// Trust: the match comes from G's proven evaluation (g_eval -> GoodEncoded), as in main_parse_a; the tables and the
// look-ahead entries are untrusted values (g_eval re-checks every candidate).

pub const R1_TEXT: usize = 1;
/// R1_MC == 1: the zero-rich binaries of the FL_MC class (machine code) also go through `gr_text` instead of
/// `fl_mc_parse` (measured: better ratio and faster on that class); 0 = n2a.
pub const R1_MC: usize = 1;

/// Insert the interior of a match that ends at `to` (`from` = its start + 1): `from`, `from + 1` and `to - 1`
/// (g_insert_match with G_IH = 2, G_IT = 1, skip = 0, without the repeated insert of `from + 1`).
#[inline(always)]
pub fn gr_insert_match(input: &[u8], t4: &mut [u32; 65536], t8: &mut [u32; 65536], from: usize, to: usize) {
    let n = input.len();
    if n < 16 {
        return;
    }
    let lim = n - 15;
    let e = if to < lim { to } else { lim };
    if from < e {
        g_ins1(input, t4, t8, from);
    }
    let p1 = from.wrapping_add(1);
    if p1 < e {
        g_ins1(input, t4, t8, p1);
    }
    let pt = to.wrapping_sub(1);
    if pt > p1 && pt < e {
        g_ins1(input, t4, t8, pt);
    }
}

/// The table entries `(c4, c8)` of position `p` (decoded as `g_tab` does), read ahead of its scan.
#[inline(always)]
pub fn gr_ahead(input: &[u8], t4: &[u32; 65536], t8: &[u32; 65536], p: usize) -> (usize, usize) {
    let v = ld8(input, p);
    g_tab(t4, t8, g_h4(v), g_h8(v))
}

/// G's software-pipelined probe loop from `pos` (g_scan without the carry); `(c4, c8)` = the table entries of `pos`,
/// loaded by the caller. Returns `(q, m)` = the first position with a match and the packed match, or `(n, 0)`.
#[inline(never)]
pub fn gr_scan(input: &[u8], t4: &mut [u32; 65536], t8: &mut [u32; 65536], pos: usize, acc: u64, c4: usize, c8: usize) -> (usize, usize) {
    let n = input.len();
    if n < 16 || pos > n - 16 {
        return (n, 0);
    }
    let mut p = pos;
    let mut k = 0usize;
    let mut m = 0usize;
    let mut v = ld8(input, p);
    let mut e = (c4, c8);
    while m == 0 && p <= n - 16 {
        let over = ((k as u64) >> (acc % 64)) as usize;
        let st = if over < G_AMAX { over + 1 } else { G_AMAX };
        let q = p + st;
        let vq = if q <= n - 16 { ld8(input, q) } else { 0 };
        let hq4 = g_h4(vq);
        let hq8 = g_h8(vq);
        let eq = g_tab(t4, t8, hq4, hq8);
        g_put(t4, t8, g_h4(v), g_h8(v), p);
        let rem = n - p - 8;
        let cap = if rem < 258 { rem } else { 258 };
        m = g_eval(input, p, v, e.1, e.0, cap);
        if m != 0 {
            break;
        }
        p = q;
        v = vq;
        e = eq;
        k += 1;
    }
    if m == 0 { (n, 0) } else { (p, m) }
}

/// Literals from `pos` up to `s` (nothing when `s <= pos`).
#[inline(always)]
pub fn gr_lits(input: &[u8], out: &mut [u32], pos: usize, s: usize, ntok: usize) -> (usize, usize) {
    if s > pos { emit_lits(input, out, pos, s - pos, ntok) } else { (ntok, pos) }
}

/// The R1 text loop from `pos0` (lane a's inputs): returns the token count.
pub fn gr_text(input: &[u8], out: &mut [u32], pos0: usize, ntok0: usize, hist: &[u32; 256], low: usize) -> usize {
    let n = input.len();
    let mut t4 = [0u32; 65536];
    let mut t8 = [0u32; 65536];
    let mut span_costs = [0u32; 256];
    fl_costs(hist, &mut span_costs);
    let acc = if low == 1 { 63u64 } else { G_ACC };
    let mut pos = pos0;
    let mut ntok = ntok0;
    let mut e = gr_ahead(input, &t4, &t8, pos0);
    while pos < n {
        let sc = gr_scan(input, &mut t4, &mut t8, pos, acc, e.0, e.1);
        let q = sc.0;
        let m = sc.1;
        let l = m % 512;
        let d = (m / 512) % 65536;
        let nx = q.wrapping_add(l);
        gr_insert_match(input, &mut t4, &mut t8, q.wrapping_add(1), nx);
        e = gr_ahead(input, &t4, &t8, nx);
        let r0 = gr_lits(input, out, pos, q, ntok);
        if r0.1 < n {
            let r = public_emit_join(input, out, r0.1, d, l, r0.0, &span_costs);
            ntok = r.0;
            pos = r.1;
        } else {
            ntok = r0.0;
            pos = r0.1;
        }
    }
    ntok
}

/// Engine dispatch: the 3-byte lane for zero-rich binary data (byte statistics only), else the base engine.
pub fn main_parse(input: &[u8], out: &mut [u32], pos0: usize, ntok0: usize, hist: &[u32;256]) -> usize {
    let e = entropy256(hist);
    let low = low_mode(e);
    let z0 = share(hist, 0, 1);
    let m3 = if G_M3 == 2 { 1usize } else if G_M3 == 1 && low == 0 && z0 >= G_M3Z && e < G_M3E { 1 } else { 0 };
    if e >= 1800 { main_parse_high(input, out, pos0, ntok0, hist, e, low) } else if m3 == 1 { if FL_MC_ON == 1 && z0 >= FL_MC_Z0 { if R1_MC == 1 { gr_text(input, out, pos0, ntok0, hist, low) } else { let r = fl_mc_parse(input, out, pos0, ntok0); if r.1 < input.len() { lg_finish(input, out, r.1, r.0) } else { r.0 } } } else { main_parse_b(input, out, pos0, ntok0, hist, e, low) } } else if R1_TEXT == 1 { gr_text(input, out, pos0, ntok0, hist, low) } else { main_parse_a(input, out, pos0, ntok0, hist, e, low) }
}

/// jfloor dispatcher. Sequential phases (no if/else between loop-heavy paths, SHARED_FINDINGS F17): the floor
/// phase handles the whole input for modes 1-5 and returns (ntok, n); for mode 0 it returns (0, 0) and the base
/// parser runs from position 0.
/// Quick RLE class check on a 1 K strided sample: 1 iff the top byte has at least FL_RLE_TOP/256 of it.
pub fn fl_qrle(input: &[u8]) -> usize {
    let n = input.len();
    let mut h = [0u32; 256];
    let st = n / 1024 + 1;
    let mut k = 0usize;
    let mut c = 0usize;
    while k < n && c < 1024 {
        let b = fl_byte(input, k) % 256;
        h[b] = h[b].wrapping_add(1);
        k = k.wrapping_add(st);
        c += 1;
    }
    let mut top = 0u32;
    let mut i = 0usize;
    while i < 256 {
        top = if h[i] > top { h[i] } else { top };
        i += 1;
    }
    if (top as usize).wrapping_mul(256) >= c.wrapping_mul(FL_RLE_TOP) { 1 } else { 0 }
}

pub fn parse(input: &[u8], out: &mut [u32]) -> usize {
    let q = if input.len() >= FL_QRLE_N { fl_qrle(input) } else { 0 };
    let mut fh = [0u32; 256];
    if q == 1 {
        let r = fl_part(input, out, 4, &fh);
        if r.1 < input.len() {
            fl_sample(input, &mut fh);
            main_parse(input, out, r.1, r.0, &fh)
        } else {
            r.0
        }
    } else {
    fl_sample(input, &mut fh);
    let st = fl_stats(&fh);
    let mc = fl_mode(input, st);
    let r = fl_part(input, out, mc, &fh);
    if r.1 < input.len() {
        let hi = if (st as usize) % 1024 >= FL_HIGH { if entropy256(&fh) < 1800 { 1usize } else { 0usize } } else { 0usize };
        if hi == 1 {
            lg_parse_h(input, out)
        } else if G3_TEXT == 1 {
            let g = fl_g3_parse(input, out, r.1, r.0);
            if g.1 < input.len() { lg_finish(input, out, g.1, g.0) } else { g.0 }
        } else {
            main_parse(input, out, r.1, r.0, &fh)
        }
    } else {
        r.0
    }
    }
}
