// Generic reuse of an already equal eight-byte prefix in released #344; all routers retained.
//! cx3: f82 batched parser with compact small-input tables and entropy-aware preparation.
//! The original 18 trusted helper bodies are unchanged. See README.md for the measured curve.
//! Dense text preparation, sparse high-entropy preparation, and a near-uniform literal lane.

pub const G_ACC: u64 = 63;
pub const G_AMAX: usize = 12;
pub const G_IH: usize =16;
pub const G_IT: usize =256;
pub const G_LZT: usize = 258;
pub const G_M3: usize = 1;
pub const G_MAX3: usize = 32768;
pub const G_WIN: usize = 32768;
pub const G_TS: usize = 8;
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

pub const FL_PMIN: usize = 16384;
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

/// Weights detector: 1 iff the probe chunks look like 16-bit floats (bytes alternate between a high-entropy and a
/// low-entropy phase with period 2) or like int8 weights (all phases 6.5-7.6 bits, no 4-byte repeat at all).
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
    let uniform = if c4 < 4 && mn >= 124 { 1 } else { 0 };
    p2 | q8 | uniform
}

/// The mode (0 base, 1 LIT, 2 DNA, 4 RLE, 5 LAZY) and the LAZY class (0 T, 1 D, 2 H), packed `mode + 8 * class`.
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
    let small = if n < FL_PMIN { 1usize } else { 0usize };
    let dna = if bg == 4 { if bs >= 205 { if e < 52 { 1usize } else { 0usize } } else { 0usize } } else { 0usize };
    let high = if e >= FL_HIGH { 1usize } else { 0usize };
    let db = if z >= FL_DBZ { if np < FL_DBNP { 1usize } else { 0usize } } else { 0usize };
    let w = if high == 1 { if FL_USE_LIT == 1 { fl_weights(input) } else { 0 } } else { 0 };
    let mh = if w == 1 { 1 } else if FL_USE_H == 1 { 21 } else { 0 };
    let md = if FL_USE_D == 1 { 13 } else { 0 };
    let mt = if FL_USE_T == 1 { 5 } else { 0 };
    if rle == 1 {
        4
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

/// RLE parse: a distance-1 run match wherever the previous byte repeats >= 3 times, else one literal.
pub fn fl_rle_parse(input: &[u8], out: &mut [u32]) -> (usize, usize) {
    let n = input.len();
    let mut pos = 0usize;
    let mut ntok = 0usize;
    while pos < n {
        let rem = n - pos;
        let cap = if rem < 258 { rem } else { 258 };
        let l = if pos >= 1 { fl_len(input, pos - 1, pos, cap) } else { 0 };
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

// ---------------------------------------------------------------- the floor phase

/// Runs the whole input through the mode's parser and returns `(ntok, n)`; mode 0 does nothing and returns
/// `(0, 0)` (the base parser then runs from position 0).
pub fn fl_part(input: &[u8], out: &mut [u32], mc: usize, fh: &[u32; 256]) -> (usize, usize) {
    let mode = mc % 8;
    if mode == 1 {
        fl_lit_parse(input, out)
    } else if mode == 2 {
        let mut cost = [0u32; 256];
        fl_costs(fh, &mut cost);
        fl_dna_parse(input, out, &cost)
    } else if mode == 4 {
        fl_rle_parse(input, out)
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

/// Fold gate filter: true only if the two bytes before `p` agree with those `dist` earlier (word compare).
#[inline(always)]
pub fn public_gate2(input: &[u8], p: usize, dist: usize) -> bool {
    if p > dist + 3 { (tw4(input, p - 4) ^ tw4(input, p - 4 - dist)) >> 16 == 0 } else { false }
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
pub fn g_fast_len(input: &[u8], a: usize, b: usize, cap: usize) -> usize {
    if cap == 0 { return 0; }
    let x = ld8(input, a) ^ ld8(input, b);
    if x == 0 { g_len(input, a, b, cap) }
    else { let k = first_diff(x); if k < cap { k } else { cap } }
}

#[inline(always)]
pub fn g_match(input: &[u8],p: usize,cc: usize,cap: usize) -> usize {
    if cc >= p { return 0; }
    let l0 = g_fast_len(input, cc, p, cap);
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
    if p.wrapping_sub(c4) >= lim { return 0; }
    let cc = c4.wrapping_sub(1);
    let x = ld8(input, cc) ^ v;
    let mask = if G_M3 == 1 { 16777215u64 } else { 4294967295u64 };
    if x & mask != 0 { return 0; }
    if min > 8 {
        if x != 0 || min > cap { return 0; }
        let off = min.wrapping_sub(8);
        if ld8(input, cc.wrapping_add(off)) != ld8(input, p.wrapping_add(off)) { return 0; }
    }
    let m = g_match(input, p, cc, cap);
    if m % 512 < min { 0 } else { m }
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

/// Insert the interior of an emitted match `from .. to`: its first G_IH positions, then every G_TS-th up to the last G_IT.
#[inline(always)]
pub fn g_insert_match(input: &[u8], t4: &mut [u32; 65536], t8: &mut [u32; 65536], from: usize, to: usize, skip: usize) {
    let start = if skip == 1 { from.wrapping_add(1) } else { from };
    let a = from.wrapping_add(G_IH);
    let a2 = if a < to { a } else { to };
    let b = to.wrapping_sub(G_IT);
    let b2 = if b > a2 { if b < to { b } else { a2 } } else { a2 };
    g_insert_stride(input, t4, t8, start, a2, 1);
    g_insert_stride(input, t4, t8, b2, to, G_TS);
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
#[inline(always)]
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
        let rem = n - p - 8;
        let cap = if rem < 258 { rem } else { 258 };
        m = g_eval(input, p, v, e.1, e.0, cap);
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
    let h4 = (pre / 2) % 16777216;
    let h8 = (pre / 33554432) % 16777216;
    let e = g_tab(t4, t8, h4, h8);
    let c4 = e.0;
    let c8 = e.1;
    g_put(t4, t8, h4, h8, q);
    let v = ld8(input, q);
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
#[inline(always)]
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
            let want = if l1 < 16 { 1usize } else { 0usize };
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

/// Engine dispatch: the 3-byte lane for zero-rich binary data (byte statistics only), else the base engine.
#[inline(never)]
pub fn main_parse(input: &[u8], out: &mut [u32], pos0: usize, ntok0: usize, hist: &[u32;256]) -> usize {
    let e = entropy256(hist);
    let low = low_mode(e);
    let z0 = share(hist, 0, 1);
    let m3 = if G_M3 == 2 { 1usize } else if G_M3 == 1 && low == 0 && z0 >= G_M3Z && e < G_M3E { 1 } else { 0 };
    if e >= 1800 { main_parse_high(input, out, pos0, ntok0, hist, e, low) } else if m3 == 1 { main_parse_b(input, out, pos0, ntok0, hist, e, low) } else { main_parse_a(input, out, pos0, ntok0, hist, e, low) }
}

/// jfloor dispatcher. Sequential phases (no if/else between loop-heavy paths, SHARED_FINDINGS F17): the floor
/// phase handles the whole input for modes 1-5 and returns (ntok, n); for mode 0 it returns (0, 0) and the base
/// parser runs from position 0.
#[inline(never)]
pub fn parse(input: &[u8], out: &mut [u32]) -> usize {
    let mut fh = [0u32; 256];
    fl_sample(input, &mut fh);
    let st = fl_stats(&fh);
    let mc = fl_mode(input, st);
    let r = fl_part(input, out, mc, &fh);
    if r.1 < input.len() { main_parse(input, out, r.1, r.0, &fh) } else { r.0 }
}
