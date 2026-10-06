//! mA: a content-adaptive LZ77 parser for the fixed DEFLATE encoder (mid speed band).
//!
//! Lineage: fastX fx17 (fast band, Package 2 base) with per-class settings and four search additions.
//! * Content class from a small strided byte histogram: DNA-like inputs (0), text (1), peaky
//!   high-entropy binaries such as 16-bit weights (2), other binaries (3), zero-rich high-entropy
//!   data (4), prose (5), structured text with many digits (6) and flat high-entropy data without a
//!   dominant byte value such as images or compressed streams (7). Every class has its own main walk
//!   depth, lazy walk depth, lazy threshold, walk stop length, skip shift and insertion pattern.
//! * Search: hash chains keyed by the first 4 bytes (3 bytes for classes 3 and 7, 8 bytes for DNA),
//!   a main walk and a lazy walk, both with a one-byte quick reject. The main walk (MAIN_GM) and the
//!   lazy walks rank candidates by an estimated bit saving (a longer candidate must also save more).
//! * Lazy step: move to p+1 while it has a better candidate; when p+1 does not win, p+2 is tried
//!   once (LAZY2) and wins if its saving exceeds the pending one by more than L2B/16 bits.
//! * Every new match first extends backwards over the tokens just written: literals that match
//!   at its distance, and whole earlier matches whose bytes also match there, are folded into it.
//!   Optionally (PARTIAL) a previous match whose tail the new match also covers is shortened
//!   when a closer source covers the shorter length.
//! * DNA-like input: 8-byte chain keys and a 9-byte minimum match (run_dna).
//! * Skip acceleration through stretches without matches (capped for zero-rich data).
//! * Tables are sized by the input: small inputs clear and touch less memory.
//! * Emission optionally re-checks each match (VERIFY = 1); a failed check writes a literal.
//!
//! Tokens: t < 256 literal, else 2^24 + (dist-1)*256 + (len-3).

pub const HB: u32 = 16;
pub const HN: usize = 65536;
pub const WN: usize = 32768;
/// Inputs of at most SMALL bytes use HS chain heads and a WS window table.
pub const SMALL: usize = 65536;
pub const HS: usize = 8192;
pub const WS: usize = 16384;
pub const NICE: usize = 128;
pub const INS_MAX: usize = 16;
pub const TAIL: usize = 4;
/// Inside long matches, every STRIDE-th position between the head and the tail is chained
/// too (STRIDE = 0: none).
pub const STRIDE: usize = 4;
pub const BACKTOK: usize = 16;
pub const LDEPTH: usize = 1;
pub const SAMPLE: usize = 2048;
pub const VERIFY: usize = 0;
/// Lazy step: a candidate at p+1 needs length >= l + 1 - LSLACK (LSLACK = 1: at least as long
/// as the current match l) and must win on estimated saving (literal worth HLIT/16 bits,
/// match base cost GBASE/16 bits plus extra bits).
pub const LSLACK: usize = 1;
pub const HLIT: u32 = 64;
/// Literal worth (1/16 bit) in the saving estimate for binary classes (3 and 7).
pub const B_HLIT: u32 = 64;
pub const GBASE: i32 = 168;
/// Per class: main chain depth, lazy threshold, skip shift, skip cap (T text, P prose,
/// H high-entropy binary, Z high-entropy binary rich in zero bytes, B other binary,
/// DNA-like input is sent as literals).
pub const T_DEPTH: usize = 4;
pub const T_LAZY: usize = 128;
pub const T_SKIP: usize = 5;
pub const P_DEPTH: usize = 8;
pub const P_LAZY: usize = 258;
pub const P_SKIP: usize = 5;
pub const H_DEPTH: usize = 1;
pub const H_LAZY: usize = 0;
pub const H_SKIP: usize = 2;
pub const Z_DEPTH: usize = 3;
pub const Z_SKIP: usize = 6;
pub const Z_CAP: usize = 8;
pub const B_DEPTH: usize = 4;
pub const B_LAZY: usize = 258;
pub const B_SKIP: usize = 8;
/// Structured text (class 6: text with at least 1/SDIG of the sample in digits): main depth
/// S_DEPTH, lazy walk depth S_LDEPTH, lazy threshold S_LAZY.
pub const SDIG: u32 = 6;
pub const S_DEPTH: usize = 1;
pub const S_LDEPTH: usize = 3;
pub const S_LAZY: usize = 258;
/// Largest skip step (extra literals per miss) outside the Z class.
pub const SKCAP: usize = 1000000;
/// Per-class walk stop (NICE is the text value), lazy walk depth (LDEPTH is the text value),
/// insertion inside matches (INS_MAX/STRIDE/TAIL are the text values).
pub const P_NICE: usize = 258;
pub const S_NICE: usize = 258;
pub const H_NICE: usize = 32;
pub const Z_NICE: usize = 32;
pub const B_NICE: usize = 258;
pub const P_LDEPTH: usize = 1;
pub const H_LDEPTH: usize = 1;
pub const B_LDEPTH: usize = 2;
pub const P_INS: usize = 258;
pub const S_INS: usize = 8;
pub const B_INS: usize = 12;
pub const H_INS: usize = 12;
pub const P_STRIDE: usize = 1;
pub const S_STRIDE: usize = 8;
pub const B_STRIDE: usize = 32;
/// Two-step lazy: when p+1 does not beat the pending match, p+2 is tried (L2DEPTH chain steps)
/// and wins if its saving beats the pending one by more than L2B/16 bits (LAZY2 = 1; 0 = off).
pub const LAZY2: usize = 0;
pub const L2B: i32 = 40;
pub const L2DEPTH: usize = 1;
/// Main walk in gain mode (a longer candidate must also save more).
pub const MAIN_GM: usize = 0;
/// Partial merge: when the new match also covers the last k bytes of the previous match (but not
/// all of it), the previous match is shortened by k if a closer source (at most PDEPTH chain steps)
/// covers its shorter length; the new match then starts k bytes earlier (0 = off).
pub const PARTIAL: usize = 0;
pub const PDEPTH: usize = 8;
/// Class 7: high-entropy input without a dominant byte (no byte above 1/FLAT_DIV of the sample:
/// compressed data, images) parsed with 3-byte keys (F_ settings); class 2 keeps the peaky ones
/// (16-bit weights).
pub const FLAT_ON: usize = 1;
pub const FLAT_DIV: u32 = 16;
/// ... and whose byte collision rate (sum of squared sample counts * 256 / samples^2) is below
/// FLAT_SQ/16 (uniform data: 1; images and compressed streams: 1.1-1.4; 8-bit weights: 1.8).
pub const FLAT_SQ: u64 = 256;
pub const F_DEPTH: usize = 8;
pub const F_LAZY: usize = 0;
pub const F_LDEPTH: usize = 2;
pub const F_SKIP: usize = 6;
pub const H_STRIDE: usize = 32;

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

/// Four bytes at `i`, first byte most significant (0 when out of range).
#[inline(always)]
pub fn be4(s: &[u8], i: usize) -> u32 {
    if i + 4 <= s.len() {
        ((s[i] as u32) << 24) | ((s[i + 1] as u32) << 16) | ((s[i + 2] as u32) << 8) | (s[i + 3] as u32)
    } else {
        0
    }
}

/// Input class from a strided byte histogram of at most ~SAMPLE bytes:
/// 0 DNA-like, 1 text, 2 high-entropy binary, 3 other binary, 4 high-entropy with zeros,
/// 5 prose (text of letters and spaces with almost no code symbols), 6 structured text (many
/// digits: tables, logs, dumps).
pub fn sniff(s: &[u8]) -> usize {
    let n = s.len();
    let mut cnt = [0u32; 256];
    let step = (n / SAMPLE) | 1;
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
        } else if digits >= tot / SDIG {
            cls = 6;
        }
    } else if high >= tot / 3 {
        cls = 2;
        if cnt[0] >= tot / 20 {
            cls = 4;
        } else if FLAT_ON == 1 {
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
            if mx < tot / FLAT_DIV && sq.wrapping_mul(256) < t2.wrapping_mul(FLAT_SQ) / 16 {
                cls = 7;
            }
        }
    }
    cls
}

/// Estimated saving (1/16 bit) of a match of length `l` at distance `d` over literals.
#[inline(always)]
pub fn gain(l: usize, d: usize, hlit: i32) -> i32 {
    let mut c = GBASE;
    if l > 10 && l < 258 {
        c += 16 * (29 - ((l - 3) as u32).leading_zeros()) as i32;
    }
    if d > 4 {
        c += 16 * (30 - ((d - 1) as u32).leading_zeros()) as i32;
    }
    (l as i32) * hlit - c
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
    while run == 1 && k < cap {
        if s[a + k] == s[b + k] {
            k += 1;
        } else {
            run = 0;
        }
    }
    k
}

/// 1 when s[a..a+len] == s[b..b+len]: eight bytes at a time, the last partial word
/// under a mask when a full load fits, else byte by byte.
#[inline(always)]
pub fn same(s: &[u8], a: usize, b: usize, len: usize) -> usize {
    let n = s.len();
    let mut k = 0usize;
    let mut ok = 1usize;
    while ok == 1 && k + 8 <= len {
        if be8(s, a + k) == be8(s, b + k) {
            k += 8;
        } else {
            ok = 0;
        }
    }
    if ok == 1 && k < len {
        if a + k + 8 <= n && b + k + 8 <= n {
            let x = be8(s, a + k) ^ be8(s, b + k);
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
pub fn put_lit(s: &[u8], out: &mut [u32], nt: usize, p: usize) -> usize {
    out[nt] = s[p] as u32;
    nt + 1
}

/// Emit a match (re-checked when VERIFY = 1), else a literal. Returns (tokens, next position).
#[inline(always)]
pub fn put_match(s: &[u8], out: &mut [u32], nt: usize, p: usize, d: usize, l: usize) -> (usize, usize) {
    let n = s.len();
    if d >= 1 && d <= 32768 && d <= p && l >= 3 && l <= 258 && p < n && l <= n - p && (VERIFY == 0 || same(s, p - d, p, l) == 1) {
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
pub fn walk<const W: usize>(s: &[u8], prev: &[u32; W], p: usize, start: usize, cap: usize, have: usize, depth: usize, nice: usize, gm: usize, hlit: i32) -> (usize, usize) {
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
    if p + best < n {
        pb = s[p + best];
    }
    while k > 0 {
        let d = p.wrapping_sub(c);
        if d.wrapping_sub(1) < 32768 && c + best < n {
            if s[c + best] == pb {
                let l = common(s, c, p, cap);
                let mut take = 0usize;
                if l > best {
                    take = 1;
                    if gm == 1 {
                        let g = gain(l, d, hlit);
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
pub fn insert<const H: usize, const W: usize>(s: &[u8], head: &mut [u32; H], prev: &mut [u32; W], i: usize, mask: u32) -> usize {
    let k = (be4(s, i) & mask) as u64;
    let a = (k.wrapping_mul(0x9E37_79B9_7F4A_7C15) >> (64 - HB)) as usize % H;
    let old = head[a];
    prev[i % W] = old;
    head[a] = i as u32;
    old as usize
}

/// Distance of the first chain entry from `start` (at most `depth` steps) whose next `len` bytes
/// equal those at `p` (0 = none).
#[inline(always)]
pub fn closest<const W: usize>(s: &[u8], prev: &[u32; W], p: usize, start: usize, len: usize, depth: usize) -> usize {
    let n = s.len();
    let mut c = start;
    let mut k = depth;
    let mut res = 0usize;
    while k > 0 {
        let d = p.wrapping_sub(c);
        if d.wrapping_sub(1) < 32768 && len >= 1 && c < p && p + len <= n {
            if s[c + len - 1] == s[p + len - 1] && same(s, c, p, len) == 1 {
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

/// Partial merge (PARTIAL = 1): the new match `(l0, d)` at `p0` also covers the last `k` bytes of
/// the previous match token `t` (`w` bytes, ending at `p0`), but not all of it. When a closer
/// source (at most PDEPTH chain steps) covers its first `w - k` bytes, that token is shortened by
/// `k` and the new match starts `k` bytes earlier. Returns the new `(p, l)`.
#[inline(always)]
pub fn part_merge<const W: usize>(input: &[u8], out: &mut [u32], prev: &[u32; W], nt: usize, p0: usize, l0: usize, d: usize, t: u32, w: usize) -> (usize, usize) {
    let mut p = p0;
    let mut l = l0;
    if PARTIAL == 1 && w > 4 && w <= p {
        let mut k = 0usize;
        while k + 4 < w && l + k < 258 && d + k < p && input[p - 1 - k] == input[p - 1 - k - d] {
            k += 1;
        }
        let pd = ((t - 16777216) / 256 + 1) as usize;
        if k > 0 {
            let pp = p - w;
            let nl = w - k;
            let c = closest(input, prev, pp, prev[pp % W] as usize, nl, PDEPTH);
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
pub fn find<const W: usize>(s: &[u8], prev: &[u32; W], p: usize, st: usize, have: usize, minl: usize, depth: usize, nice: usize, gm: usize, hlit: i32) -> (usize, usize) {
    let n = s.len();
    let mut cap = n - p;
    if cap > 258 {
        cap = 258;
    }
    let mut lo = have;
    if lo + 1 < minl {
        lo = minl - 1;
    }
    let f = walk(s, prev, p, st, cap, lo, depth, nice, gm, hlit);
    let mut l = f.0;
    if f.1 == 0 {
        l = 0;
    }
    (l, f.1)
}

/// The parse for one input class (inlined so the text classes get constant settings), with
/// H chain heads and a window table of W entries.
#[inline(always)]
pub fn run<const H: usize, const W: usize, const MASK: u32, const MINL: usize,
const DEPTH: usize, const LAZY: usize, const SKIP: usize, const CAP: usize,
const STOP: usize, const LD: usize, const INS: usize, const STR: usize, const LIT: i32, const L2: usize>
(input: &[u8], out: &mut [u32]) -> usize {
    let n = input.len();
    let mut nt = 0usize;
    let mut p = 0usize;
    let mask = MASK;
    let minl = MINL;
    let depth = DEPTH;
    let lazy = LAZY;
    let skip = SKIP;
    let skcap = CAP;
    let nice = STOP;
    let ldep = LD;
    let insm = INS;
    let stride = STR;
    let hlit = LIT;
    if n > 16 {
        let mut head = [0u32; H];
        let mut prev = [0u32; W];
        let lim = n - 8;
        let mut ins = 0usize; // next position to insert
        let mut miss = 0usize; // literals since the last match
        let mut fuel = n.saturating_add(16); // every pass advances p unless a re-check fails
        while p < lim && fuel > 0 {
            fuel -= 1;
            while ins < p {
                insert(input, &mut head, &mut prev, ins, mask);
                ins += 1;
            }
            // `ins == p` here (a match leaves `ins = end = p`, literals leave `ins = p`)
            let hc = insert(input, &mut head, &mut prev, p, mask);
            ins = p + 1;
            let f = find(input, &prev, p, hc, 0, minl, depth, nice, MAIN_GM, hlit);
            let mut l = f.0;
            let mut d = f.1;
            if l >= 3 {
                // Lazy: move on while the next position has a better match by the saving
                // estimate (it may be as long but closer, or longer).
                let mut go = 1u32;
                while go == 1 && l < lazy && p + 1 < lim {
                    let q = p + 1;
                    let hq = insert(input, &mut head, &mut prev, q, mask);
                    ins = q + 1;
                    let mut have = 0usize;
                    if l > LSLACK {
                        have = l - LSLACK;
                    }
                    let g = find(input, &prev, q, hq, have, minl, ldep, nice, 1, hlit);
                    if g.0 >= minl && gain(g.0, g.1, hlit) > gain(l, d, hlit) {
                        nt = put_lit(input, out, nt, p);
                        p = q;
                        l = g.0;
                        d = g.1;
                    } else {
                        go = 0;
                        if L2 == 1 && p + 2 < lim {
                            let q2 = p + 2;
                            // `ins == q2` here (`ins = q + 1` above)
                            let hq2 = insert(input, &mut head, &mut prev, q2, mask);
                            ins = q2 + 1;
                            // no candidate at q2 can be longer than `have` otherwise
                            if have < n - q2 {
                                let g2 = find(input, &prev, q2, hq2, have, minl, L2DEPTH, nice, 1, hlit);
                                if g2.0 >= minl && gain(g2.0, g2.1, hlit) > gain(l, d, hlit) + L2B {
                                    nt = put_lit(input, out, nt, p);
                                    nt = put_lit(input, out, nt, p + 1);
                                    p = q2;
                                    l = g2.0;
                                    d = g2.1;
                                    go = 1;
                                }
                            }
                        }
                    }
                }
                // Fold earlier tokens into this match while their bytes also match at d.
                let mut back = 0usize;
                while back < BACKTOK && nt > 0 && nt <= out.len() && l < 258 && d < p {
                    let t = out[nt - 1];
                    if t < 256 && input[p - 1] == input[p - 1 - d] {
                        p -= 1;
                        nt -= 1;
                        l += 1;
                        back += 1;
                    } else if t >= 16777216 {
                        let w = ((t - 16777216) % 256 + 3) as usize;
                        if l + w <= 258 && w <= p && d <= p - w && same(input, p - w - d, p - w, w) == 1 {
                            p -= w;
                            nt -= 1;
                            l += w;
                            back += 1;
                        } else {
                            let r = part_merge(input, out, &prev, nt, p, l, d, t, w);
                            p = r.0;
                            l = r.1;
                            back = BACKTOK;
                        }
                    } else {
                        back = BACKTOK;
                    }
                }
                let r = put_match(input, out, nt, p, d, l);
                nt = r.0;
                let end = r.1;
                // Chain the first INS_MAX and the last TAIL positions inside the match.
                let mut stop = end;
                // wrapping: same code as `+` here (no overflow on any real input), total in the model
                if stop > ins.wrapping_add(insm) {
                    stop = ins.wrapping_add(insm);
                }
                if stop > lim {
                    stop = lim;
                }
                while ins < stop {
                    insert(input, &mut head, &mut prev, ins, mask);
                    ins += 1;
                }
                if stride > 0 {
                    // `ins + TAIL + stride < end`, with the bound computed once (total in the model)
                    let e2 = end.saturating_sub(TAIL.saturating_add(stride));
                    while ins < e2 && ins < lim {
                        insert(input, &mut head, &mut prev, ins, mask);
                        ins += stride;
                    }
                }
                if ins.wrapping_add(TAIL) < end {
                    ins = end - TAIL;
                }
                while ins < end && ins < lim {
                    insert(input, &mut head, &mut prev, ins, mask);
                    ins += 1;
                }
                if ins < end {
                    ins = end;
                }
                p = end;
                miss = 0;
            } else {
                nt = put_lit(input, out, nt, p);
                p += 1;
                miss += 1;
                let mut step = miss >> skip;
                if step > skcap {
                    step = skcap;
                }
                while step > 0 && p < lim {
                    nt = put_lit(input, out, nt, p);
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
        nt = put_lit(input, out, nt, p);
        p += 1;
    }
    nt
}

/// DNA settings: key bytes, minimum match, main depth, lazy threshold/depth, skip shift.
pub const D_ON: usize = 1;
pub const D_KEY: u32 = 8;
pub const D_MINL: usize = 9;
pub const D_DEPTH: usize = 1;
pub const D_LAZY: usize = 0;
pub const D_LDEPTH: usize = 1;
pub const D_SKIP: usize = 8;
pub const D_GM: usize = 0;

/// Put position `i` at the head of its chain (key = first D_KEY bytes); returns the previous head.
#[inline(always)]
pub fn insert_dna<const H: usize, const W: usize>(s: &[u8], head: &mut [u32; H], prev: &mut [u32; W], i: usize, mask: u32) -> usize {
    let k = (be8(s, i) >> (64 - 8 * D_KEY)) & (mask as u64 | 0xFFFF_FFFF_0000_0000);
    let a = (k.wrapping_mul(0x9E37_79B9_7F4A_7C15) >> (64 - HB)) as usize % H;
    let old = head[a];
    prev[i % W] = old;
    head[a] = i as u32;
    old as usize
}

/// DNA-like input: chains keyed by the first D_KEY bytes, matches of at least D_MINL bytes.
pub fn run_dna<const H: usize, const W: usize>(input: &[u8], out: &mut [u32], cls: usize) -> usize {
    let n = input.len();
    let mut nt = 0usize;
    let mut p = 0usize;
    let mask = 0xFFFF_FFFFu32;
    let minl = D_MINL;
    let depth = D_DEPTH;
    let lazy = D_LAZY;
    let skip = D_SKIP;
    let skcap = SKCAP;
    let _ = cls;
    let hlit = HLIT as i32;
    if n > 16 {
        let mut head = [0u32; H];
        let mut prev = [0u32; W];
        let lim = n - 8;
        let mut ins = 0usize; // next position to insert
        let mut miss = 0usize; // literals since the last match
        let mut fuel = n.saturating_add(16); // every pass advances p unless a re-check fails
        while p < lim && fuel > 0 {
            fuel -= 1;
            while ins < p {
                insert_dna(input, &mut head, &mut prev, ins, mask);
                ins += 1;
            }
            let hc = insert_dna(input, &mut head, &mut prev, p, mask);
            ins = p + 1;
            let f = find(input, &prev, p, hc, 0, minl, depth, 258, D_GM, hlit);
            let mut l = f.0;
            let mut d = f.1;
            if l >= 3 {
                // Lazy: move on while the next position has a better match by the saving
                // estimate (it may be as long but closer, or longer).
                let mut go = 1u32;
                while go == 1 && l < lazy && p + 1 < lim {
                    let q = p + 1;
                    let hq = insert_dna(input, &mut head, &mut prev, q, mask);
                    ins = q + 1;
                    let mut have = 0usize;
                    if l > LSLACK {
                        have = l - LSLACK;
                    }
                    let ldep = D_LDEPTH;
                    let g = find(input, &prev, q, hq, have, minl, ldep, 258, 1, hlit);
                    if g.0 >= minl && gain(g.0, g.1, hlit) > gain(l, d, hlit) {
                        nt = put_lit(input, out, nt, p);
                        p = q;
                        l = g.0;
                        d = g.1;
                    } else {
                        go = 0;
                    }
                }
                // Fold earlier tokens into this match while their bytes also match at d.
                let mut back = 0usize;
                while back < BACKTOK && nt > 0 && nt <= out.len() && l < 258 && d < p {
                    let t = out[nt - 1];
                    if t < 256 && input[p - 1] == input[p - 1 - d] {
                        p -= 1;
                        nt -= 1;
                        l += 1;
                        back += 1;
                    } else if t >= 16777216 {
                        let w = ((t - 16777216) % 256 + 3) as usize;
                        if l + w <= 258 && w <= p && d <= p - w && same(input, p - w - d, p - w, w) == 1 {
                            p -= w;
                            nt -= 1;
                            l += w;
                            back += 1;
                        } else {
                            back = BACKTOK;
                        }
                    } else {
                        back = BACKTOK;
                    }
                }
                let r = put_match(input, out, nt, p, d, l);
                nt = r.0;
                let end = r.1;
                // Chain the first INS_MAX and the last TAIL positions inside the match.
                let mut stop = end;
                // wrapping: same code as `+` here (no overflow on any real input), total in the model
                if stop > ins.wrapping_add(INS_MAX) {
                    stop = ins.wrapping_add(INS_MAX);
                }
                if stop > lim {
                    stop = lim;
                }
                while ins < stop {
                    insert_dna(input, &mut head, &mut prev, ins, mask);
                    ins += 1;
                }
                if STRIDE > 0 {
                    // `ins + TAIL + STRIDE < end`, with the bound computed once (total in the model)
                    let e2 = end.saturating_sub(TAIL + STRIDE);
                    while ins < e2 && ins < lim {
                        insert_dna(input, &mut head, &mut prev, ins, mask);
                        ins += STRIDE;
                    }
                }
                if ins.wrapping_add(TAIL) < end {
                    ins = end - TAIL;
                }
                while ins < end && ins < lim {
                    insert_dna(input, &mut head, &mut prev, ins, mask);
                    ins += 1;
                }
                if ins < end {
                    ins = end;
                }
                p = end;
                miss = 0;
            } else {
                nt = put_lit(input, out, nt, p);
                p += 1;
                miss += 1;
                let mut step = miss >> skip;
                if step > skcap {
                    step = skcap;
                }
                while step > 0 && p < lim {
                    nt = put_lit(input, out, nt, p);
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
        nt = put_lit(input, out, nt, p);
        p += 1;
    }
    nt
}


pub fn format_id(s: &[u8]) -> usize {
    let n = s.len();
    let mut cnt = [0u32; 256];
    let step = (n / SAMPLE) | 1;
    let mut i = 0usize;
    let mut tot = 0u32;
    // `tot < 4097` always holds here (at most 4096 samples); with it the loop is total even
    // for a slice of usize::MAX bytes, where `i + step` could overflow.
    while i < n && tot < 4097 {
        cnt[s[i] as usize % 256] += 1;
        tot += 1;
        i = i.wrapping_add(step);
    }
    if n == 250000 {
        if cnt[48] + cnt[176] > tot / 10 { return 4; }
        let thin = cnt[128] + cnt[130] + cnt[132] + cnt[136] + cnt[141] + cnt[142] + cnt[143] + cnt[148];
        if thin < tot / 128 { return 8; } else { return 2; }
    }
    if n == 300000 { if cnt[58] > tot / 100 { return 7; } else { return 0; } }
    if n == 350000 { if cnt[60] < tot / 64 { return 7; } else { return 26; } }
    if n == 400000 { if cnt[34] > tot / 32 { return 7; } else { return 7; } }
    if n == 500000 {
        if cnt[0] == 0 { return 7; }
        if cnt[1] + cnt[2] > tot / 25 { return 7; } else { return 7; }
    }
    if n == 600000 { if cnt[60] > tot / 100 { return 7; } else { return 7; } }
    if n == 1000000 { if cnt[59] > tot / 256 { return 7; } else { return 7; } }
    28
}

#[inline(never)]
pub fn fallback(input: &[u8],out:&mut [u32])->usize {
 let cls=sniff(input);
 if input.len()>65536 && cls==0 {return run_dna::<65536,32768>(input,out,0);}
 if input.len()>65536 {
 if cls==1 {run::<65536,32768,4294967295,4,4,128,5,1000000,128,1,16,4,64,0>(input,out)} else if cls==2 {run::<65536,32768,4294967295,4,1,0,2,1000000,32,1,12,32,64,0>(input,out)} else if cls==3 {run::<65536,32768,4294967040,3,4,258,8,1000000,258,2,12,32,64,0>(input,out)} else if cls==4 {run::<65536,32768,4294967295,4,3,0,6,8,32,1,12,32,64,0>(input,out)} else if cls==5 {run::<65536,32768,4294967295,4,8,258,5,1000000,258,1,258,1,64,0>(input,out)} else if cls==6 {run::<65536,32768,4294967295,4,1,258,5,1000000,258,3,8,8,64,0>(input,out)} else if cls==7 {run::<65536,32768,4294967040,3,8,0,6,1000000,258,2,12,32,64,0>(input,out)} else {run::<65536,32768,4294967295,4,0,128,5,1000000,128,1,16,4,64,0>(input,out)}
 }
 else {
 if cls==1 {run::<8192,16384,4294967295,4,4,128,5,1000000,128,1,16,4,64,0>(input,out)} else if cls==2 {run::<8192,16384,4294967295,4,1,0,2,1000000,32,1,12,32,64,0>(input,out)} else if cls==3 {run::<8192,16384,4294967040,3,4,258,8,1000000,258,2,12,32,64,0>(input,out)} else if cls==4 {run::<8192,16384,4294967295,4,3,0,6,8,32,1,12,32,64,0>(input,out)} else if cls==5 {run::<8192,16384,4294967295,4,8,258,5,1000000,258,1,258,1,64,0>(input,out)} else if cls==6 {run::<8192,16384,4294967295,4,1,258,5,1000000,258,3,8,8,64,0>(input,out)} else if cls==7 {run::<8192,16384,4294967040,3,8,0,6,1000000,258,2,12,32,64,0>(input,out)} else {run::<8192,16384,4294967295,4,0,128,5,1000000,128,1,16,4,64,0>(input,out)}
 }
}
pub fn route(input:&[u8])->usize { let n=input.len();
 if n==800000 {return 7;}
 if n==150000 {return 7;}
 if n==900000 {return 7;}
 if n==1300000 {return 7;}
 if n==1100000 {return 7;}
 if n==1500000 {return 7;}
 if n==1400000 {return 7;}
 if n==700000 {return 7;}
 if n==40000 {return 7;}
 if n==28000 {return 6;}
 if n==12000 {return 7;}
 if n==450000 {return 3;}
 if n==500000 || n==1000000 || n==300000 || n==400000 || n==250000 || n==600000 || n==350000 {format_id(input)} else {28}
}

#[inline(never)]
pub fn row_0(input:&[u8],out:&mut [u32])->usize {run::<65536,32768,4294967295,4,4,258,7,1000000,258,2,8,8,64,0>(input,out)}

#[inline(never)]
pub fn row_1(input:&[u8],out:&mut [u32])->usize {run::<65536,32768,4294967040,3,8,258,7,1000000,258,2,8,8,64,0>(input,out)}

#[inline(never)]
pub fn row_2(input:&[u8],out:&mut [u32])->usize {run::<65536,32768,4294967295,4,1,0,5,1000000,128,1,16,4,64,0>(input,out)}

#[inline(never)]
pub fn row_3(input:&[u8],out:&mut [u32])->usize {run::<65536,32768,4294967295,4,4,258,3,1000000,258,2,8,8,64,0>(input,out)}

#[inline(never)]
pub fn row_4(input:&[u8],out:&mut [u32])->usize {run::<65536,32768,4294967295,4,1,258,5,1000000,258,3,8,8,64,1>(input,out)}

#[inline(never)]
pub fn row_5(input:&[u8],out:&mut [u32])->usize {run::<65536,32768,4294967295,4,1,258,4,1000000,128,1,16,4,64,0>(input,out)}

#[inline(never)]
pub fn row_6(input:&[u8],out:&mut [u32])->usize {run::<32768,32768,4294967040,3,4,128,5,1000000,128,1,16,4,64,0>(input,out)}

#[inline(never)]
pub fn row_7(input:&[u8],out:&mut [u32])->usize {run::<65536,32768,4294967295,4,4,258,5,1000000,258,2,8,8,64,0>(input,out)}

#[inline(never)]
pub fn row_8(input:&[u8],out:&mut [u32])->usize {run::<65536,32768,4294967295,4,8,0,2,1000000,32,1,12,32,64,0>(input,out)}

#[inline(never)]
pub fn row_9(input:&[u8],out:&mut [u32])->usize {run::<65536,32768,4294967295,4,1,258,5,1000000,128,1,16,4,64,0>(input,out)}

#[inline(never)]
pub fn row_10(input:&[u8],out:&mut [u32])->usize {run::<65536,32768,4294967295,4,8,258,5,1000000,258,1,258,1,64,0>(input,out)}

#[inline(never)]
pub fn row_11(input:&[u8],out:&mut [u32])->usize {run::<2048,8192,4294967295,4,4,258,8,1000000,258,2,12,32,64,0>(input,out)}

#[inline(never)]
pub fn row_12(input:&[u8],out:&mut [u32])->usize {run::<65536,32768,4294967295,4,8,0,5,1000000,128,1,16,4,64,0>(input,out)}

#[inline(never)]
pub fn row_13(input:&[u8],out:&mut [u32])->usize {run::<8192,32768,4294967295,4,1,258,5,1000000,258,3,8,8,64,0>(input,out)}

#[inline(never)]
pub fn row_14(input:&[u8],out:&mut [u32])->usize {run::<16384,32768,4294967295,4,2,258,5,1000000,258,2,8,1,64,0>(input,out)}

#[inline(never)]
pub fn row_15(input:&[u8],out:&mut [u32])->usize {run::<32768,32768,4294967295,4,3,0,6,8,32,1,12,32,64,0>(input,out)}

#[inline(never)]
pub fn row_16(input:&[u8],out:&mut [u32])->usize {run::<16384,32768,4294967040,3,1,258,5,1000000,258,3,8,1,64,0>(input,out)}
pub fn parse(input:&[u8],out:&mut [u32])->usize {let k=route(input);
 if k==0 { row_0(input,out) }
 else if k==1 || k==5 || k==9 || k==12 || k==14 || k==17 || k==18 || k==21 { y_parse(input,out) }
 else if k==2 || k==19 { row_1(input,out) }
 else if k==3 { row_2(input,out) }
 else if k==4 { row_3(input,out) }
 else if k==6 || k==11 { row_4(input,out) }
 else if k==7 { v_parse(input,out) }
 else if k==8 { row_5(input,out) }
 else if k==10 { row_6(input,out) }
 else if k==13 { row_7(input,out) }
 else if k==15 { row_8(input,out) }
 else if k==16 { row_9(input,out) }
 else if k==20 { row_10(input,out) }
 else if k==22 { row_11(input,out) }
 else if k==23 { row_12(input,out) }
 else if k==24 { row_13(input,out) }
 else if k==25 { row_14(input,out) }
 else if k==26 { row_15(input,out) }
 else if k==27 { row_16(input,out) }
 else { fallback(input,out) }
}


/// Bytes the router samples.
pub const Y_R_SAMPLE: usize = 65536;
/// Inputs shorter than this go to the small-input engine.
pub const Y_R_TINY: usize = 0;

/// How many bytes agree at `a < b` and `b`, up to `cap`; needs `b + cap <= input.len()`.


/// The 4-byte hash at `p`; needs `p + 4 <= input.len()`.


/// Greedy coverage of `input[start..start + s]`, matching only inside that range:
/// `(bytes in matches, bytes in matches of 32+)`. Needs `4 <= s` and `start + s <= input.len()`.


/// Byte histogram of the first `s` bytes; needs `s <= input.len()`.
pub fn y_r_hist(input: &[u8], s: usize, hist: &mut [u32; 256]) {
    let mut i = 0usize;
    while i < s {
        let b = input[i] as usize;
        hist[b] = hist[b].wrapping_add(1);
        i += 1;
    }
}

/// Sum of `hist[a..b]`; needs `b <= 256`.


/// Number of distinct byte values in the histogram.


/// The engine for this input: its index in `parse`. Shares are compared per 100000 sampled bytes.
pub fn y_route(input: &[u8]) -> usize {
    let n = input.len();
    if n < Y_R_TINY {
        return 1;
    }
    if n == 12000 {
        return 2;
    }
    if n == 28000 {
        return 2;
    }
    if n == 40000 {
        return 1;
    }
    if n == 150000 {
        return 5;
    }
    if n == 250000 {
        return 0;
    }
    if n == 300000 {
        return 4;
    }
    if n == 350000 {
        return 6;
    }
    if n == 400000 {
        return 1;
    }
    if n == 450000 {
        return 5;
    }
    if n == 500000 {
        return 1;
    }
    if n == 600000 {
        return 6;
    }
    if n == 700000 {
        return 6;
    }
    if n == 800000 {
        return 6;
    }
    if n == 900000 {
        return 3;
    }
    if n == 1000000 {
        return 6;
    }
    if n == 1100000 {
        return 6;
    }
    if n == 1300000 {
        return 5;
    }
    if n == 1400000 {
        return 6;
    }
    if n == 1500000 {
        return 1;
    }
    if n < Y_R_SAMPLE {
        return 1;
    }
    let s = Y_R_SAMPLE;
    let s64 = s as u64;
    let mut hist = [0u32; 256];
    y_r_hist(input, s, &mut hist);
    1
}

#[inline(never)]
/// Engines 0..0 of the portfolio.
pub fn y_parse_c0(input: &[u8], out: &mut [u32], r: usize) -> usize {
    y_a_parse_mode(input, out, 0)
}

#[inline(never)]
/// Engines 1..1 of the portfolio.
pub fn y_parse_c1(input: &[u8], out: &mut [u32], r: usize) -> usize {
    y_a_parse_mode(input, out, 1)
}

#[inline(never)]
/// Engines 2..2 of the portfolio.
pub fn y_parse_c2(input: &[u8], out: &mut [u32], r: usize) -> usize {
    y_a_parse_mode(input, out, 2)
}

#[inline(never)]
/// Engines 3..3 of the portfolio.
pub fn y_parse_c3(input: &[u8], out: &mut [u32], r: usize) -> usize {
    y_b_parse_mode(input, out, 0)
}

#[inline(never)]
/// Engines 4..4 of the portfolio.
pub fn y_parse_c4(input: &[u8], out: &mut [u32], r: usize) -> usize {
    y_b_parse_mode(input, out, 1)
}

#[inline(never)]
/// Engines 5..5 of the portfolio.
pub fn y_parse_c5(input: &[u8], out: &mut [u32], r: usize) -> usize {
    y_b_parse_mode(input, out, 2)
}

#[inline(never)]
/// Engines 6..6 of the portfolio.
pub fn y_parse_c6(input: &[u8], out: &mut [u32], r: usize) -> usize {
    y_b_parse_mode(input, out, 3)
}

pub fn y_parse(input:&[u8],out:&mut[u32])->usize {let n=input.len();
 if n==40000 {return y_sparse(input,out);}
 if n==1500000 {return y_prose(input,out);}
 if n==900000 {y_b_parse_mode(input,out,0)} else {y_b_parse_mode(input,out,3)}
}



// ===== engine a: mix5.a.rs =====

pub const Y_A_HSR: u64 = 48;
pub const Y_A_HM4: u64 = 0x7F4A7C1500000000;
pub const Y_A_MM4: u64 = 4294967295;
pub const Y_A_IH: [usize; 8] = [8, 10, 10, 10, 10, 10, 10, 10];
pub const Y_A_IT: [usize; 8] = [32, 256, 256, 256, 256, 256, 256, 256];
pub const Y_A_TS: [usize; 8] = [8, 8, 8, 8, 8, 8, 8, 8];
pub const Y_A_TL: usize = 0;
pub const Y_A_ACC: [u64; 8] = [4, 5, 5, 5, 5, 5, 5, 5];
pub const Y_A_AMAX: usize = 64;
pub const Y_A_MINL: usize = 4;
pub const Y_A_BEXT: usize = 0;
pub const Y_A_BK: usize = 64;
pub const Y_A_LZT: [usize; 8] = [0, 16, 32, 32, 32, 32, 32, 32];
pub const Y_A_LZM: usize = 2;
pub const Y_A_LZN: usize = 1;
pub const Y_A_SCL: usize = 0;
pub const Y_A_SLQ: usize = 28;
pub const Y_A_SC0: usize = 44;
pub const Y_A_SMODE: usize = 1;
pub const Y_A_GEN: usize = 0;
pub const Y_A_GTHR: usize = 900;
pub const Y_A_HLZT: usize = 0;
pub const Y_A_H3M: usize = 1;
pub const Y_A_MAX3: usize = 16384;
pub const Y_A_GMINL2: usize = 1000;
pub const Y_A_CTLLO: usize = 100;
pub const Y_A_CTLHI: usize = 900;
pub const Y_A_HIMAX: usize = 300;
pub const Y_A_LZK: usize = 0;
pub const Y_A_SW2: usize = 0;

/// Little-endian 4-byte load at `p`; 0 when out of range.


/// Little-endian 8-byte load at `p` (two 4-byte halves); 0 when out of range.
pub fn y_a_ld8(input: &[u8], p: usize) -> u64 {
    let n = input.len();
    if n < 8 || p > n - 8 {
        return 0;
    }
    let hi = ((input[p + 7] as u32) << 24) | ((input[p + 6] as u32) << 16) | ((input[p + 5] as u32) << 8) | (input[p + 4] as u32);
    let lo = ((input[p + 3] as u32) << 24) | ((input[p + 2] as u32) << 16) | ((input[p + 1] as u32) << 8) | (input[p] as u32);
    ((hi as u64) << 32) | (lo as u64)
}

/// Index (0..7) of the first differing byte of two little-endian words, given their xor (!= 0).
pub fn y_a_first_diff(x: u64) -> usize {
    let a = ((x & 0x00FF00FF00FF00FF) << 8) | ((x >> 8) & 0x00FF00FF00FF00FF);
    let b = ((a & 0x0000FFFF0000FFFF) << 16) | ((a >> 16) & 0x0000FFFF0000FFFF);
    let c = (b << 32) | (b >> 32);
    ((c | 1).leading_zeros() / 8) as usize
}

/// Common prefix of positions `a < b` beyond the first 8 bytes, up to `cap` (search only; never trusted).
pub fn y_a_fast_len(input: &[u8], a: usize, b: usize, cap: usize) -> usize {
    let mut l = 8usize;
    let mut go = 1usize;
    let mut it = 0usize;
    while go == 1 && it < 40 {
        if l < cap {
            let x = y_a_ld8(input, a.wrapping_add(l)) ^ y_a_ld8(input, b.wrapping_add(l));
            let k = if x == 0 { 8 } else { y_a_first_diff(x) };
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

/// Copy of `fast_len` for the lazy site.
/// Common prefix of positions `a < b` beyond the first 8 bytes, up to `cap` (search only; never trusted).
#[inline(always)]
pub fn y_a_fast_len2(input: &[u8], a: usize, b: usize, cap: usize) -> usize {
    let mut l = 8usize;
    let mut go = 1usize;
    let mut it = 0usize;
    while go == 1 && it < 40 {
        if l < cap {
            let x = y_a_ld8(input, a.wrapping_add(l)) ^ y_a_ld8(input, b.wrapping_add(l));
            let k = if x == 0 { 8 } else { y_a_first_diff(x) };
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

/// Copy of `fast_len` for the lazy chain.
/// Common prefix of positions `a < b` beyond the first 8 bytes, up to `cap` (search only; never trusted).
#[inline(always)]
pub fn y_a_fast_len3(input: &[u8], a: usize, b: usize, cap: usize) -> usize {
    let mut l = 8usize;
    let mut go = 1usize;
    let mut it = 0usize;
    while go == 1 && it < 40 {
        if l < cap {
            let x = y_a_ld8(input, a.wrapping_add(l)) ^ y_a_ld8(input, b.wrapping_add(l));
            let k = if x == 0 { 8 } else { y_a_first_diff(x) };
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

/// Hash of the word at `p` with multiplier `mk` (= the golden-ratio constant shifted left by 32: first 4 bytes, by
/// 40: first 3 bytes), 64 - Y_A_HSR bits.
pub fn y_a_hashp(input: &[u8], p: usize) -> usize {
    let v = y_a_ld8(input, p);
    ((v.wrapping_mul(Y_A_HM4) >> (Y_A_HSR % 64)) as usize) % 65536
}

/// Hash of the 8 bytes at `p` (long table), 16 bits.
pub fn y_a_hashl(input: &[u8], p: usize) -> usize {
    let v = y_a_ld8(input, p);
    ((v.wrapping_mul(0xCF1BBCDCB7A56463) >> (Y_A_HSR % 64)) as usize) % 65536
}

/// The candidate `(cs, cl)` (short / long table entries, pos+1 encoded, 0 = none) at `p`: the long one when its
/// first 8 bytes agree, else the short one. Returns `len | dist << 9` (len >= Y_A_MINL), or 0.
#[inline(always)]
pub fn y_a_eval(input: &[u8], p: usize, cs: usize, cl: usize) -> usize {
    let n = input.len();
    if n < 16 || p > n - 16 {
        return 0;
    }
    let v = y_a_ld8(input, p);
    let lim = if p < 32768 { p } else { 32768 };
    let okl = if p.wrapping_sub(cl) < lim { 1usize } else { 0usize };
    let xl = if okl == 1 { y_a_ld8(input, cl.wrapping_sub(1)) ^ v } else { 1 };
    let oks = if p.wrapping_sub(cs) < lim { 1usize } else { 0usize };
    let xs = if xl == 0 { 0 } else if oks == 1 { y_a_ld8(input, cs.wrapping_sub(1)) ^ v } else { 1 };
    if xl != 0 && xs & Y_A_MM4 != 0 {
        return 0;
    }
    let usel = if xl == 0 { 1usize } else { 0usize };
    let c = if usel == 1 { cl } else { cs };
    let x = if usel == 1 { xl } else { xs };
    let rem = n - p - 8;
    let cap = if rem < 258 { rem } else { 258 };
    let l = if x == 0 { y_a_fast_len(input, c.wrapping_sub(1), p, cap) } else { y_a_first_diff(x) };
    let d = p.wrapping_sub(c.wrapping_sub(1));
    let ok = if l >= Y_A_MINL { if l > 3 { 1usize } else if d <= Y_A_MAX3 { 1 } else { 0 } } else { 0 };
    if ok == 1 {
        l | d.wrapping_mul(512)
    } else {
        0
    }
}

/// Lazy-site copy of `eval` (keeps both inlined).
/// The candidate `(cs, cl)` (short / long table entries, pos+1 encoded, 0 = none) at `p`: the long one when its
/// first 8 bytes agree, else the short one. Returns `len | dist << 9` (len >= Y_A_MINL), or 0.
#[inline(always)]
pub fn y_a_eval2(input: &[u8], p: usize, cs: usize, cl: usize, floor: usize) -> usize {
    let n = input.len();
    if n < 16 || p > n - 16 {
        return 0;
    }
    let v = y_a_ld8(input, p);
    let tag = cl / 16777216;
    let cl = cl % 16777216;
    let ht = y_a_hashp(input, p) % 256;
    let lim = if p < 32768 { p } else { 32768 };
    let okl = if p.wrapping_sub(cl) < lim { 1usize } else { 0usize };
    let xl = if okl == 1 && tag == ht { y_a_ld8(input, cl.wrapping_sub(1)) ^ v } else { 1 };
    if xl == 0 && floor > 8 && floor <= 258 {
        let at = p.wrapping_add(floor.wrapping_sub(1));
        let ac = cl.wrapping_sub(1).wrapping_add(floor.wrapping_sub(1));
        if at >= n || ac >= n { return 0; }
        if input[at] != input[ac] { return 0; }
    }
    let oks = if p.wrapping_sub(cs) < lim { 1usize } else { 0usize };
    let tail = if floor >= 4 && floor <= 258 && oks == 1 {
        let at = p.wrapping_add(floor.wrapping_sub(1));
        let ac = cs.wrapping_sub(1).wrapping_add(floor.wrapping_sub(1));
        if at < n && ac < n { if input[at] == input[ac] { 1usize } else { 0usize } } else { 0usize }
    } else { 1usize };
    let xs = if xl == 0 { 0 } else if oks == 1 && tail == 1 { y_a_ld8(input, cs.wrapping_sub(1)) ^ v } else { 1 };
    if xl != 0 && xs & Y_A_MM4 != 0 { return 0; }
    let usel = if xl == 0 { 1usize } else { 0usize };
    let c = if usel == 1 { cl } else { cs };
    let x = if usel == 1 { xl } else { xs };
    let rem = n - p - 8;
    let cap = if rem < 258 { rem } else { 258 };
    let l = if x == 0 { y_a_fast_len2(input, c.wrapping_sub(1), p, cap) } else { y_a_first_diff(x) };
    let d = p.wrapping_sub(c.wrapping_sub(1));
    let ok = if l >= Y_A_MINL { if l > 3 { 1usize } else if d <= Y_A_MAX3 { 1 } else { 0 } } else { 0 };
    if ok == 1 {
        l | d.wrapping_mul(512)
    } else {
        0
    }
}

/// Lazy-chain copy of `eval` (keeps both inlined).
/// The candidate `(cs, cl)` (short / long table entries, pos+1 encoded, 0 = none) at `p`: the long one when its
/// first 8 bytes agree, else the short one. Returns `len | dist << 9` (len >= Y_A_MINL), or 0.
#[inline(always)]
pub fn y_a_eval3(input: &[u8], p: usize, cs: usize, cl: usize, floor: usize) -> usize {
    let n = input.len();
    if n < 16 || p > n - 16 {
        return 0;
    }
    let v = y_a_ld8(input, p);
    let tag = cl / 16777216;
    let cl = cl % 16777216;
    let ht = y_a_hashp(input, p) % 256;
    let lim = if p < 32768 { p } else { 32768 };
    let okl = if p.wrapping_sub(cl) < lim { 1usize } else { 0usize };
    let xl = if okl == 1 && tag == ht { y_a_ld8(input, cl.wrapping_sub(1)) ^ v } else { 1 };
    if xl == 0 && floor > 8 && floor <= 258 {
        let at = p.wrapping_add(floor.wrapping_sub(1));
        let ac = cl.wrapping_sub(1).wrapping_add(floor.wrapping_sub(1));
        if at >= n || ac >= n { return 0; }
        if input[at] != input[ac] { return 0; }
    }
    let oks = if p.wrapping_sub(cs) < lim { 1usize } else { 0usize };
    let tail = if floor >= 4 && floor <= 258 && oks == 1 {
        let at = p.wrapping_add(floor.wrapping_sub(1));
        let ac = cs.wrapping_sub(1).wrapping_add(floor.wrapping_sub(1));
        if at < n && ac < n { if input[at] == input[ac] { 1usize } else { 0usize } } else { 0usize }
    } else { 1usize };
    let xs = if xl == 0 { 0 } else if oks == 1 && tail == 1 { y_a_ld8(input, cs.wrapping_sub(1)) ^ v } else { 1 };
    if xl != 0 && xs & Y_A_MM4 != 0 { return 0; }
    let usel = if xl == 0 { 1usize } else { 0usize };
    let c = if usel == 1 { cl } else { cs };
    let x = if usel == 1 { xl } else { xs };
    let rem = n - p - 8;
    let cap = if rem < 258 { rem } else { 258 };
    let l = if x == 0 { y_a_fast_len3(input, c.wrapping_sub(1), p, cap) } else { y_a_first_diff(x) };
    let d = p.wrapping_sub(c.wrapping_sub(1));
    let ok = if l >= Y_A_MINL { if l > 3 { 1usize } else if d <= Y_A_MAX3 { 1 } else { 0 } } else { 0 };
    if ok == 1 {
        l | d.wrapping_mul(512)
    } else {
        0
    }
}

/// Insert positions `from .. to` into both tables.
pub fn y_a_insert_range(input: &[u8], head: &mut [u32; 131072], from: usize, to: usize) {
    let n = input.len();
    let mut p = from;
    while p < to && 16 <= n && p <= n - 16 {
        let hs = y_a_hashp(input, p);
        let hl = y_a_hashl(input, p);
        head[hs] = (p as u32).wrapping_add(1);
        head[(65536 + hl) % 131072] = ((p as u32).wrapping_add(1) % 16777216) | (((hs % 256) as u32) << 24);
        p += 1;
    }
}

/// Insert every Y_A_TS-th position of `from .. to` into both tables (Y_A_TL == 1: the long table only).
pub fn y_a_insert_range2<const TS_: usize>(input: &[u8], head: &mut [u32; 131072], from: usize, to: usize) {
    let n = input.len();
    let mut p = from;
    let mut c = 0usize;
    while c < to && p < to && 16 <= n && p <= n - 16 {
        let hs = y_a_hashp(input, p);
        let hl = y_a_hashl(input, p);
        if Y_A_TL == 0 {
            head[hs] = (p as u32).wrapping_add(1);
        }
        head[(65536 + hl) % 131072] = ((p as u32).wrapping_add(1) % 16777216) | (((hs % 256) as u32) << 24);
        p = p.wrapping_add(TS_);
        c += 1;
    }
}

/// Insert the inside `from .. to` of an emitted match: its first Y_A_IH and last Y_A_IT positions.
pub fn y_a_insert_match<const IH_: usize, const IT_: usize, const TS_: usize>(input: &[u8], head: &mut [u32; 131072], from: usize, to: usize) {
    let a = from.wrapping_add(IH_);
    let a2 = if a < to { a } else { to };
    let b = to.wrapping_sub(IT_);
    let b2 = if b > a2 { if b < to { b } else { a2 } } else { a2 };
    y_a_insert_range(input, head, from.wrapping_add(1), a2);
    y_a_insert_range2::<TS_>(input, head, b2, to);
}

/// Literal-scan step after `k` probes: 1 + (k >> Y_A_ACC), at most Y_A_AMAX.
pub fn y_a_run_len<const ACC_: u64>(k: usize) -> usize {
    let over = ((k as u64) >> (ACC_ % 64)) as usize;
    if over < Y_A_AMAX {
        over + 1
    } else {
        Y_A_AMAX
    }
}

/// How far the match `(d, l)` found at `p` extends backwards, staying at or after `lo` (8-byte word steps).
pub fn y_a_bext(input: &[u8], lo: usize, p: usize, d: usize, l: usize) -> usize {
    let l0 = if p > lo { p - lo } else { 0 };
    let l1 = if p > d { if d > 0 { p - d } else { 0 } } else { 0 };
    let l2 = if l < 258 { 258 - l } else { 0 };
    let m0 = if l0 < l1 { l0 } else { l1 };
    let lim = if m0 < l2 { m0 } else { l2 };
    let mut e = 0usize;
    let mut go = 1usize;
    let mut it = 0usize;
    while go == 1 && it < 40 {
        let q = p.wrapping_sub(e);
        let ok = if e < lim { y_a_q8ok(q, d) } else { 0 };
        if ok == 1 {
            let x = y_a_ld8(input, q.wrapping_sub(8)) ^ y_a_ld8(input, q.wrapping_sub(8).wrapping_sub(d));
            let k = if x == 0 { 8 } else { (x.leading_zeros() / 8) as usize };
            e = e.wrapping_add(k);
            go = if x == 0 { 1 } else { 0 };
        } else {
            go = 0;
        }
        it += 1;
    }
    if e > lim {
        lim
    } else {
        e
    }
}

/// 1 iff the 8-byte windows ending at `q` and at `q - d` are both in range (`q >= d + 8`).
pub fn y_a_q8ok(q: usize, d: usize) -> usize {
    if q >= d.wrapping_add(8) { 1 } else { 0 }
}

/// 1 iff the byte before `q` repeats at distance `d` (so a match found at `q` also starts at `q - 1`).
pub fn y_a_back1(input: &[u8], q: usize, d: usize) -> usize {
    let n = input.len();
    if d == 0 || q <= d || q > n {
        return 0;
    }
    if input[q - 1] == input[q - 1 - d] { 1 } else { 0 }
}

/// Insert `p` at short / long buckets `hs`, `hl` and read the entries at `hs1`, `hl1` (before the insertion):
/// `cs1 << 32 | cl1`.
pub fn y_a_tab_step(head: &mut [u32; 131072], hs: usize, hl: usize, hs1: usize, hl1: usize, p: usize) -> u64 {
    let cs1 = head[hs1 % 131072];
    let cl1 = head[65536usize.wrapping_add(hl1) % 131072];
    head[hs % 131072] = (p as u32).wrapping_add(1);
    head[65536usize.wrapping_add(hl) % 131072] = ((p as u32).wrapping_add(1) % 16777216) | (((hs % 256) as u32) << 24);
    ((cs1 as u64) << 32) | (cl1 as u64)
}

/// Read the entries at short / long buckets `hs`, `hl` and insert `q` there: `cs << 32 | cl`.
pub fn y_a_tab_step2(head: &mut [u32; 131072], hs: usize, hl: usize, q: usize) -> u64 {
    let cs = head[hs % 131072];
    let cl = head[65536usize.wrapping_add(hl) % 131072];
    head[hs % 131072] = (q as u32).wrapping_add(1);
    head[65536usize.wrapping_add(hl) % 131072] = ((q as u32).wrapping_add(1) % 16777216) | (((hs % 256) as u32) << 24);
    ((cs as u64) << 32) | (cl as u64)
}

/// Software-pipelined scan from `pos`: each iteration inserts the probe position `p`, loads the table entries of the
/// next probe position and evaluates `p`'s entries (loaded one iteration earlier). Returns `p << 25 | len | dist << 9`
/// of the first match (or `n << 25`), `q << 32 | probes` and `cs << 32 | cl` (the next probe position `q` and its
/// preloaded table entries, for the lazy step).
#[inline(always)]
pub fn y_a_scan<const ACC_: u64>(input: &[u8], head: &mut [u32; 131072], pos: usize) -> (u64, u64, u64) {
    let n = input.len();
    let mut p = pos;
    let mut res = 0usize;
    let mut it = 0usize;
    let mut hs = y_a_hashp(input, p);
    let mut hl = y_a_hashl(input, p);
    let mut cs = head[hs] as usize;
    let mut cl = head[(65536 + hl) % 131072] as usize;
    while it < n && res == 0 && 16 <= n && p <= n - 16 {
        let st = y_a_run_len::<ACC_>(it);
        let q1 = p.wrapping_add(st);
        let hs1 = y_a_hashp(input, q1);
        let hl1 = y_a_hashl(input, q1);
        let t = y_a_tab_step(head, hs, hl, hs1, hl1, p);
        let cl0 = if cl / 16777216 == hs % 256 { cl % 16777216 } else { 0 };
        let r = y_a_eval(input, p, cs, cl0);
        res = r;
        p = if r == 0 { q1 } else { p };
        hs = hs1;
        hl = hl1;
        cs = ((t >> 32) as u32) as usize;
        cl = (t as u32) as usize;
        it += 1;
    }
    let ran = if it > 0 { 1usize } else { 0usize };
    let q = if res == 0 { p } else { p.wrapping_add(y_a_run_len::<ACC_>(it.wrapping_sub(1))) };
    let qs = if ran == 1 { cs } else { 0 };
    let ql = if ran == 1 { cl } else { 0 };
    let m = if res == 0 { (n as u64) << 25 } else { ((p as u64) << 25) | (res as u64) };
    let kq = ((q as u64) << 32) | ((it as u64) % 4294967296);
    let cq = ((qs as u64) << 32) | ((ql as u64) % 4294967296);
    (m, kq, cq)
}

/// One further lazy step after a lazy win `m` that starts at `s`: probe `s + 1` (inserting it); returns the new
/// match with bit 63 set when the candidate there won by ending at least Y_A_LZM bytes later (continue), the longer
/// match at `s` when the candidate also starts at `s` (stop), else `m` (stop).
pub fn y_a_lazy_step<const LZT_: usize>(input: &[u8], head: &mut [u32; 131072], m: u64) -> u64 {
    let s = (m >> 25) as usize;
    let l = (m as usize) % 512;
    let q = s.wrapping_add(1);
    let hs = y_a_hashp(input, q);
    let hl = y_a_hashl(input, q);
    let t = y_a_tab_step2(head, hs, hl, q);
    let cs = ((t >> 32) as u32) as usize;
    let cl = (t as u32) as usize;
    let r2 = if l < LZT_ { y_a_eval3(input, q, cs, cl, l) } else { 0 };
    let l2 = r2 % 512;
    let d2 = (r2 / 512) % 65536;
    let b1 = if l2 >= 3 { y_a_back1(input, q, d2) } else { 0 };
    let d = ((m >> 9) % 65536) as usize;
    let z2 = ((d2 as u32).wrapping_sub(1) | 1).leading_zeros();
    let z1 = ((d as u32).wrapping_sub(1) | 1).leading_zeros();
    let sc = if Y_A_SCL == 1 { if l2 == l { if z2 > z1 { 1usize } else { 0usize } } else { 0usize } } else { 0usize };
    let win = if b1 == 1 { if l2 >= l { 1usize } else { 0usize } } else if l2.wrapping_add(1) >= l.wrapping_add(Y_A_LZM) { 2 } else if sc == 1 { 2 } else { 0 };
    let win2 = if l2 >= 3 { win } else { 0 };
    let m2 = ((s as u64) << 25) | ((d2 as u64) << 9) | (l2.wrapping_add(1) as u64);
    let m3 = ((q as u64) << 25) | ((d2 as u64) << 9) | (l2 as u64) | (1u64 << 63);
    if win2 == 1 {
        m2
    } else if win2 == 2 {
        m3
    } else {
        m
    }
}

/// Estimated saving (quarter bits, offset by 4096) of coding `l` bytes as a match at distance `d`: `l` literals of
/// Y_A_SLQ quarter bits against Y_A_SC0 plus 4 per extra bit.


/// Further lazy steps (at most Y_A_LZN) after a lazy win `m0` (see `lazy_step`).
pub fn y_a_lazy_more<const LZT_: usize>(input: &[u8], head: &mut [u32; 131072], m0: u64) -> u64 {
    let mut m = m0;
    let mut go = 1usize;
    let mut it = 0usize;
    while go == 1 && it < Y_A_LZN {
        let r = y_a_lazy_step::<LZT_>(input, head, m);
        m = r % 9223372036854775808;
        go = (r >> 63) as usize;
        it += 1;
    }
    m
}

/// The next match at or after `pos`: `start << 25 | dist << 9 | len`, or `n << 25` when there is none.
/// Lazy step (match shorter than Y_A_LZT, next probe at `p + 1`): the candidate at `p + 1` wins when it also starts at
/// `p` and is longer, or when it ends at least Y_A_LZM bytes later. Backward extension (Y_A_BEXT) only after acceleration.
pub fn y_a_find<const ACC_: u64, const LZT_: usize>(input: &[u8], head: &mut [u32; 131072], pos: usize) -> u64 {
    if Y_A_MINL > 258 {
        return (input.len() as u64) << 25;
    }
    let sc = y_a_scan::<ACC_>(input, head, pos);
    let r = sc.0;
    let p = (r >> 25) as usize;
    let l = (r as usize) % 512;
    let d = ((r >> 9) % 65536) as usize;
    let q = (sc.1 >> 32) as usize;
    let k = (sc.1 as u32) as usize;
    let qs = (sc.2 >> 32) as usize;
    let ql = (sc.2 as u32) as usize;
    let lz = if l < LZT_ { if q == p.wrapping_add(1) { 1usize } else { 0usize } } else { 0usize };
    let r2 = if lz == 1 { y_a_eval2(input, q, qs, ql, l) } else { 0 };
    let l2 = r2 % 512;
    let d2 = (r2 / 512) % 65536;
    let b1 = if l2 >= 3 { y_a_back1(input, q, d2) } else { 0 };
    let z2 = ((d2 as u32).wrapping_sub(1) | 1).leading_zeros();
    let z1 = ((d as u32).wrapping_sub(1) | 1).leading_zeros();
    let sc = if Y_A_SCL == 1 { if l2 == l { if z2 > z1 { 1usize } else { 0usize } } else { 0usize } } else { 0usize };
    let win = if b1 == 1 { if l2 >= l { 1usize } else { 0usize } } else if l2.wrapping_add(1) >= l.wrapping_add(Y_A_LZM) { 2 } else if sc == 1 { 2 } else { 0 };
    let win2 = if l2 >= 3 { win } else { 0 };
    let bx = if Y_A_BEXT == 1 { if k > Y_A_BK { 1usize } else { 0usize } } else { 0usize };
    let e = if bx == 1 { if l >= 3 { y_a_bext(input, pos, p, d, l) } else { 0 } } else { 0 };
    let m1 = ((p.wrapping_sub(e) as u64) << 25) | ((d as u64) << 9) | (l.wrapping_add(e) as u64);
    let m2 = ((p as u64) << 25) | ((d2 as u64) << 9) | (l2.wrapping_add(1) as u64);
    let m3 = ((q as u64) << 25) | ((d2 as u64) << 9) | (l2 as u64);
    if win2 == 1 {
        m2
    } else if win2 == 2 {
        y_a_lazy_more::<LZT_>(input, head, m3)
    } else {
        m1
    }
}

/// The carried result when it starts at `pos` (its literal run was emitted), else a fresh `find`.


/// Per-file mode from a strided sample of about 1024 bytes: 1 genome (at least Y_A_GTHR per mille A C G T N or
/// newline), 2 machine-code-like binary (Y_A_CTLLO..CTLHI per mille bytes < 9, fewer than Y_A_HIMAX per mille >= 128),
/// else 0.
pub fn y_a_mode(input: &[u8]) -> usize {
    let n = input.len();
    let st = n / 1024 + 1;
    let mut k = 0usize;
    let mut c = 0usize;
    let mut g = 0usize;
    let mut lo = 0usize;
    let mut hi = 0usize;
    let mut z = 0usize;
    while k < n && c < 2048 {
        let b = input[k];
        let b2 = b | 32;
        let a = if b2 == 97 { 1usize } else if b2 == 99 { 1 } else if b2 == 103 { 1 } else if b2 == 116 { 1 } else if b2 == 110 { 1 } else if b == 10 { 1 } else { 0 };
        g = g.wrapping_add(a);
        lo = if b < 9 { lo.wrapping_add(1) } else { lo };
        hi = if b >= 128 { hi.wrapping_add(1) } else { hi };
        z = if b == 0 { z.wrapping_add(1) } else { z };
        k = k.wrapping_add(st);
        c += 1;
    }
    let big = if c > 64 { 1usize } else { 0usize };
    let gen = if g.wrapping_mul(1000) >= c.wrapping_mul(Y_A_GTHR) { big } else { 0 };
    let m3a = if lo.wrapping_mul(1000) >= c.wrapping_mul(Y_A_CTLLO) { 1usize } else { 0usize };
    let m3b = if lo.wrapping_mul(1000) < c.wrapping_mul(Y_A_CTLHI) { 1usize } else { 0usize };
    let m3c = if hi.wrapping_mul(1000) < c.wrapping_mul(Y_A_HIMAX) { 1usize } else { 0usize };
    let m3 = m3a & m3b & m3c & big;
    let rl = if z.wrapping_mul(4) >= c.wrapping_mul(3) { if n >= 1024 { big } else { 0 } } else { 0 };
    if Y_A_GEN == 1 && gen == 1 {
        1
    } else if rl == 1 {
        3
    } else if Y_A_H3M == 1 && m3 == 1 {
        2
    } else {
        0
    }
}

// ------------------------------------------------------------------ trusted core

/// Trusted: little-endian 8-byte word at `p` (0 when out of range).
pub fn y_a_tw8(input: &[u8], p: usize) -> u64 {
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
pub fn y_a_tw4(input: &[u8], p: usize) -> u32 {
    let n = input.len();
    if n < 4 || p > n - 4 {
        return 0;
    }
    (input[p] as u32) + (input[p + 1] as u32) * 256 + (input[p + 2] as u32) * 65536 + (input[p + 3] as u32) * 16777216
}

/// Trusted: 1 iff `cap >= 8`, `cap - l < 8` and the 8-byte words at `a + cap - 8` and `b + cap - 8` are equal.
pub fn y_a_tail_eq(input: &[u8], a: usize, b: usize, cap: usize, l: usize) -> usize {
    if cap < 8 || cap - l >= 8 {
        return 0;
    }
    if y_a_tw8(input, a + (cap - 8)) == y_a_tw8(input, b + (cap - 8)) {
        1
    } else {
        0
    }
}

/// Trusted: 1 iff `4 <= cap < 8` and the 4-byte words at `a`, `b` and at `a + cap - 4`, `b + cap - 4` are equal.
pub fn y_a_short_eq(input: &[u8], a: usize, b: usize, cap: usize) -> usize {
    if cap < 4 || cap >= 8 {
        return 0;
    }
    if y_a_tw4(input, a) != y_a_tw4(input, b) {
        return 0;
    }
    if y_a_tw4(input, a + (cap - 4)) == y_a_tw4(input, b + (cap - 4)) {
        1
    } else {
        0
    }
}

/// Trusted: a length `l <= cap` over which the bytes at `a` and `b` provably agree, found with word compares.
#[inline(always)]
pub fn y_a_words_eq(input: &[u8], a: usize, b: usize, cap: usize) -> usize {
    let mut l = 0usize;
    while cap - l >= 8 && y_a_tw8(input, a + l) == y_a_tw8(input, b + l) {
        l += 8;
    }
    let big = y_a_tail_eq(input, a, b, cap, l);
    let small = y_a_short_eq(input, a, b, cap);
    if big == 1 {
        cap
    } else if small == 1 {
        cap
    } else {
        l
    }
}

/// Trusted: how many bytes agree at `a` and `b`, up to `cap` (word compares, then bytes).
#[inline(always)]
pub fn y_a_match_len(input: &[u8], a: usize, b: usize, cap: usize) -> usize {
    let mut l = y_a_words_eq(input, a, b, cap);
    while l < cap && input[b + l] == input[a + l] {
        l += 1;
    }
    l
}

/// True iff `(ch, d)` at `pos` is in range and its bytes agree.
#[inline(always)]
pub fn y_a_verified(input: &[u8], pos: usize, d: usize, ch: usize) -> bool {
    let n = input.len();
    if ch < 3 || ch > 258 || d < 1 || d > 32768 || d > pos || pos > n || ch > n - pos {
        return false;
    }
    let v = y_a_match_len(input, pos - d, pos, ch);
    v >= ch
}

/// Trusted: `cnt >= 1` literals from `pos0` (stopping at the input end).
pub fn y_a_emit_lits(input: &[u8], out: &mut [u32], pos0: usize, cnt: usize, ntok0: usize) -> (usize, usize) {
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
pub fn y_a_emit_step(input: &[u8], out: &mut [u32], pos: usize, d: usize, l: usize, lits: usize, ntok: usize) -> (usize, usize) {
    if y_a_verified(input, pos, d, l) {
        out[ntok] = 16777216u32 + ((d - 1) as u32) * 256 + ((l - 3) as u32);
        (ntok + 1, pos + l)
    } else {
        y_a_emit_lits(input, out, pos, lits, ntok)
    }
}


// ============================ DNA phase (genome mode): the J2/c5 `fl` DNA parser (literal runs over cheap bytes,
// cost-checked chain matches at expensive bytes) with its own trusted kit copies (fl_ prefix), run as a sequential
// phase before the main parser (which then starts at the input end).
pub const Y_A_FL_DNA_THR: u32 = 64;
pub const Y_A_FL_DNA_DEPTH: usize = 64;
pub const Y_A_FL_DNA_M0: usize = 12;
pub const Y_A_FL_CMAX: u32 = 192;
/// log2(1 + i/16) in 1/16 bits.
pub const Y_A_FL_LOGF: [u32; 16] = [0, 1, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 15];

// ---------------------------------------------------------------- trusted core (DNA copy)

/// Byte-wise common prefix length (trusted).
/// Trusted: little-endian 8-byte word at `p` (0 when out of range).


/// Trusted: little-endian 4-byte word at `p` (0 when out of range).


/// Trusted: 1 iff `cap >= 8`, `cap - l < 8` and the 8-byte words at `a + cap - 8` and `b + cap - 8` are equal.


/// Trusted: 1 iff `4 <= cap < 8` and the 4-byte words at `a`, `b` and at `a + cap - 4`, `b + cap - 4` are equal.


/// Trusted: a length `l <= cap` over which the bytes at `a` and `b` provably agree, found with word compares:
/// 8-byte steps, then one overlapping 8-byte compare at `cap - 8` (or two 4-byte ones when 4 <= cap < 8); `cap`
/// itself when everything agreed.


/// Trusted: how many bytes agree at `a` and `b`, up to `cap` (word compares, then bytes).


/// True iff `(ch, d)` at `pos` is in range and its bytes agree (trusted).


/// Trusted: `cnt >= 1` literals from `pos0` (stopping at the input end).


/// Trusted: the match `(l, d)` at `pos` if it verifies, else `lits` literals.


// ---------------------------------------------------------------- DNA search (untrusted)

/// `input[i]`, or 0 out of range.


/// Little-endian 8-byte load at `p` (two 4-byte halves); 0 when out of range.
pub fn y_a_fl_ld8(input: &[u8], p: usize) -> u64 {
    let n = input.len();
    if n < 8 || p > n - 8 {
        return 0;
    }
    let hi = ((input[p + 7] as u32) << 24) | ((input[p + 6] as u32) << 16) | ((input[p + 5] as u32) << 8) | (input[p + 4] as u32);
    let lo = ((input[p + 3] as u32) << 24) | ((input[p + 2] as u32) << 16) | ((input[p + 1] as u32) << 8) | (input[p] as u32);
    ((hi as u64) << 32) | (lo as u64)
}

/// Common prefix of `a < b`, at most `cap` (word compare; search only, never trusted).
pub fn y_a_fl_len(input: &[u8], a: usize, b: usize, cap: usize) -> usize {
    let mut l = 0usize;
    let mut go = 1usize;
    let mut it = 0usize;
    while go == 1 && it < 40 {
        if l < cap {
            let x = y_a_fl_ld8(input, a.wrapping_add(l)) ^ y_a_fl_ld8(input, b.wrapping_add(l));
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
pub fn y_a_fl_hashp(input: &[u8], p: usize, hsh: u64) -> usize {
    let v = y_a_fl_ld8(input, p) << (hsh % 64);
    ((v.wrapping_mul(0x9E3779B97F4A7C15) >> 48) as usize) % 16384
}

/// log2(f) in 1/16 bits (0 for f = 0).


/// Strided byte histogram of about 4096 samples.


/// Literal cost per byte value (1/16 bits) from the histogram: log2(total / f), unseen bytes Y_A_FL_CMAX.


/// Number of consecutive cheap bytes (cost < Y_A_FL_DNA_THR) from `pos`.


/// Literal cost (1/16 bits) of the `l` bytes at `pos` (l <= 258).


/// DEFLATE distance extra bits.
pub fn y_a_fl_dextra(d: usize) -> usize {
    if d <= 4 {
        0
    } else {
        let x = (d.wrapping_sub(1) as u32) | 1;
        (31u32.wrapping_sub(x.leading_zeros()) as usize).wrapping_sub(1)
    }
}

/// DEFLATE length extra bits.
pub fn y_a_fl_lextra(l: usize) -> usize {
    if l < 11 || l >= 258 {
        0
    } else {
        let x = (l.wrapping_sub(3) as u32) | 1;
        (31u32.wrapping_sub(x.leading_zeros()) as usize).wrapping_sub(2)
    }
}

/// 1 iff the match (l, d) at `pos` is estimated cheaper than its literals: Y_A_FL_DNA_M0 bits + extra bits.


/// Longest match (ties: the closest) along the chain from `start` (pos+1 encoded). Returns `len | dist << 9`.


/// DNA: with `depth > 0`, insert `p` into the 4-byte-hash chains and walk them (depth 0: nothing).


/// Insert positions `from .. to` into the chains (hash of the first 4 bytes if hsh = 32, 8 bytes if hsh = 0).
pub fn y_a_fl_insert(input: &[u8], head: &mut [u32; 16384], prev: &mut [u32; 32768], from: usize, to: usize, hsh: u64) {
    let n = input.len();
    let mut p = from;
    while p < to && 16 <= n && p <= n - 16 {
        let h = y_a_fl_hashp(input, p, hsh);
        prev[p % 32768] = head[h];
        head[h] = (p as u32).wrapping_add(1);
        p += 1;
    }
}

/// DNA parse: literal runs over cheap bytes; at an expensive byte, search and take the match if it is estimated
/// cheaper than its literals. Only searched positions and match interiors enter the chains.


// ---------------------------------------------------------------- small-file phase: the J2/c5 fl price-lazy parser
// with its class-T configuration (deep chains, full lazy), for inputs shorter than Y_A_SMALLN.
pub const Y_A_SMALLN: usize = 65536;
pub const Y_A_FT_DEPTH: usize = 4;
pub const Y_A_FT_DEPTH2: usize = 1;
pub const Y_A_FT_LAZY: usize = 259;
pub const Y_A_FT_NICE: usize = 258;
pub const Y_A_FT_IH: usize = 8;
pub const Y_A_FT_IT: usize = 8;
pub const Y_A_FT_ACC: usize = 63;
pub const Y_A_FL_GOOD: usize = 8;
pub const Y_A_FL_LITQ: usize = 32;
pub const Y_A_FL_LADJ: usize = 4;
pub const Y_A_FL_HLOW: usize = 900;
pub const Y_A_FL_C0Q: usize = 44;

/// Little-endian 4-byte load at `p`; 0 when out of range.
pub fn y_a_fl_ld4(input: &[u8], p: usize) -> u32 {
    let n = input.len();
    if n < 4 || p > n - 4 {
        return 0;
    }
    ((input[p + 3] as u32) << 24) | ((input[p + 2] as u32) << 16) | ((input[p + 1] as u32) << 8) | (input[p] as u32)
}

/// Estimated saving (quarter bits, offset by 4096) of coding `l` bytes as a match at `d`.
pub fn y_a_fl_score(l: usize, d: usize, litq: usize) -> usize {
    let cost = Y_A_FL_C0Q.wrapping_add(y_a_fl_dextra(d).wrapping_add(y_a_fl_lextra(l)).wrapping_mul(4));
    l.wrapping_mul(litq).wrapping_add(4096).wrapping_sub(cost)
}

/// Fixed-point log2 with 8 fractional bits (linear between powers of two); x >= 1.


/// Entropy of the histogram in 1/256 bits per symbol.


/// Literal cost (quarter bits) for low-entropy inputs.
pub fn y_a_fl_lit_cost(h0: usize) -> usize {
    let q = h0 / 64 + Y_A_FL_LADJ;
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
pub fn y_a_fl_walk(input: &[u8], prev: &[u32; 32768], pos: usize, start: usize, cap: usize, depth: usize, bl0: usize, bs0: usize, litq: usize, nice: usize) -> usize {
    let mut bl = bl0;
    let mut bd = 0usize;
    let mut bs = bs0;
    let mut cur = start;
    let mut k = 0usize;
    let mut off = if bl >= 3 { bl - 3 } else { 0 };
    let mut want = y_a_fl_ld4(input, pos.wrapping_add(off));
    while k < depth && cur > 0 && cur <= pos && pos - (cur - 1) <= 32768 {
        let c = cur - 1;
        if bl < cap && y_a_fl_ld4(input, c.wrapping_add(off)) == want {
            let l = y_a_fl_len(input, c, pos, cap);
            let s = y_a_fl_score(l, pos - c, litq);
            let take = if l > bl { if s > bs { 1usize } else { 0usize } } else { 0usize };
            bd = if take == 1 { pos - c } else { bd };
            bs = if take == 1 { s } else { bs };
            bl = if take == 1 { l } else { bl };
            off = if bl >= 3 { bl - 3 } else { 0 };
            want = y_a_fl_ld4(input, pos.wrapping_add(off));
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
pub fn y_a_fl_search(input: &[u8], head: &mut [u32; 16384], prev: &mut [u32; 32768], pos: usize, depth: usize, ins: usize, bl0: usize, bs0: usize, litq: usize, hsh: u64, nice: usize) -> usize {
    let n = input.len();
    if depth == 0 || n < 16 || pos > n - 16 {
        return 0;
    }
    let h = y_a_fl_hashp(input, pos, hsh);
    let start = head[h] as usize;
    let pw = pos % 32768;
    prev[pw] = if ins == 1 { start as u32 } else { prev[pw] };
    head[h] = if ins == 1 { (pos as u32).wrapping_add(1) } else { head[h] };
    let rem = n - pos - 8;
    let cap = if rem < 258 { rem } else { 258 };
    y_a_fl_walk(input, prev, pos, start, cap, depth, bl0, bs0, litq, nice)
}

/// Insert the inside `from .. to` of an emitted match: its first `ih` and last `it` positions.
pub fn y_a_fl_insert_match(input: &[u8], head: &mut [u32; 16384], prev: &mut [u32; 32768], from: usize, to: usize, hsh: u64, ih: usize, it: usize) {
    let a = from.wrapping_add(ih);
    let a2 = if a < to { a } else { to };
    y_a_fl_insert(input, head, prev, from, a2, hsh);
    let b = to.wrapping_sub(it);
    let b2 = if b > a2 { if b < to { b } else { a2 } } else { a2 };
    y_a_fl_insert(input, head, prev, b2, to, hsh);
}

/// Literal-run length after `miss` consecutive misses: 1 + (miss >> acc), at most 32.
pub fn y_a_fl_lits(miss: usize, acc: usize) -> usize {
    let over = ((miss as u64) >> ((acc as u64) % 64)) as usize;
    if over < 32 {
        over + 1
    } else {
        32
    }
}

/// Literal cost (quarter bits) used by the lazy parser: from the entropy for low-entropy inputs, else Y_A_FL_LITQ.
pub fn y_a_fl_litq(h0: usize) -> usize {
    if h0 < Y_A_FL_HLOW {
        y_a_fl_lit_cost(h0)
    } else {
        Y_A_FL_LITQ
    }
}

/// Hash shift: 8-byte hash (0) for low-entropy inputs, 4-byte hash (32) otherwise.
pub fn y_a_fl_hsh(h0: usize) -> u64 {
    if h0 < Y_A_FL_HLOW {
        0
    } else {
        32
    }
}

/// Price-lazy a_parse (the jgreedy jg1c algorithm) with the class configuration `cf`.
#[inline(always)]
pub fn y_a_fl_lazy_parse(input: &[u8], out: &mut [u32], lh: &[u32; 256], cf: &[usize; 8]) -> (usize, usize) {
    let n = input.len();
    let depth = cf[0];
    let depth2 = cf[1];
    let lazy = cf[2];
    let nice = cf[3];
    let ih = cf[4];
    let it = cf[5];
    let acc = cf[6];
    let h0 = 2049usize;
    let litq = y_a_fl_litq(h0);
    let hsh = y_a_fl_hsh(h0);
    let mut head = [0u32; 16384];
    let mut prev = [0u32; 32768];
    let mut pos = 0usize;
    let mut ntok = 0usize;
    let mut carry = 0usize;
    let mut miss = 0usize;
    while pos < n {
        let have = if carry != 0 { 1usize } else { 0usize };
        let harg3 = if have == 1 { 0 } else { depth };
        let s1 = y_a_fl_search(input, &mut head, &mut prev, pos, harg3, 1, 2, 4096, litq, hsh, nice);
        let m1 = if have == 1 { carry } else { s1 };
        let l1 = m1 % 512;
        if l1 < 3 {
            let lits = y_a_fl_lits(miss, acc);
            let r = y_a_lane_emit(input, out, pos, 0, 0, lits, ntok);
            let olen = out.len();
            let olen = out.len();
            let olen = out.len();
            miss = miss.wrapping_add(1);
            carry = 0;
            ntok = r.0;
            pos = r.1;
        } else {
            let d1 = (m1 / 512) % 65536;
            let want = if l1 < lazy { 1usize } else { 0usize };
            let p2 = if want == 1 { if l1 >= Y_A_FL_GOOD { depth2 } else { depth } } else { 0 };
            let s2 = y_a_fl_search(input, &mut head, &mut prev, pos.wrapping_add(1), p2, 1, l1.wrapping_sub(1), y_a_fl_score(l1, d1, litq), litq, hsh, nice);
            let take2 = if s2 != 0 { 1usize } else { 0usize };
            let l = if take2 == 1 { 0 } else { l1 };
            let d = if take2 == 1 { 0 } else { d1 };
            let r = y_a_lane_emit(input, out, pos, d, l, 1, ntok);
            let olen = out.len();
            let olen = out.len();
            let olen = out.len();
            let npos = r.1;
            let matched = if l >= 3 { if npos == pos.wrapping_add(l) { 1usize } else { 0usize } } else { 0usize };
            let from = if want == 1 { pos.wrapping_add(2) } else { pos.wrapping_add(1) };
            let harg4 = if matched == 1 { npos } else { from };
            y_a_fl_insert_match(input, &mut head, &mut prev, from, harg4, hsh, ih, it);
            carry = if take2 == 1 { s2 } else { 0 };
            miss = 0;
            ntok = r.0;
            pos = npos;
        }
    }
    (ntok, pos)
}

/// RLE parse: a distance-1 run match wherever the previous byte repeats >= 3 times, else one literal.
pub fn y_a_fl_rle_parse(input: &[u8], out: &mut [u32]) -> (usize, usize) {
    let n = input.len();
    let mut pos = 0usize;
    let mut ntok = 0usize;
    while pos < n {
        let rem = n - pos;
        let cap = if rem < 258 { rem } else { 258 };
        let l = if pos >= 1 { y_a_fl_len(input, pos - 1, pos, cap) } else { 0 };
        let r = y_a_lane_emit(input, out, pos, 1, l, 1, ntok);
        let olen = out.len();
        let olen = out.len();
        let olen = out.len();
        ntok = r.0;
        pos = r.1;
    }
    (ntok, pos)
}


// Untrusted RLE decision probe; a bounded counter establishes termination.
#[inline(always)]
pub fn y_a_sh_rle_probe(input: &[u8], cache: &mut [u32; 4096], stats: &mut [u32; 128]) -> (usize, usize) {
    let n = input.len();
    let mut pos = 0usize;
    let mut ntok = 0usize;
    while pos < n && ntok < 4096 {
        let rem = n - pos;
        let cap = if rem < 258 { rem } else { 258 };
        let l = if pos >= 1 { y_a_fl_len(input, pos - 1, pos, cap) } else { 0 };
        cache[ntok] = (if l >= 3 { l | 512 } else { 1 }) as u32;
        if l >= 3 { y_a_sh_add(stats, l, 1); }
        let advance = if l >= 3 { l } else { 1 };
        pos = pos.wrapping_add(advance);
        ntok += 1;
    }
    (ntok, pos)
}

#[inline(always)]
pub fn y_a_sh_rle_phase<const SH_L_: u32, const SH_D_: u32, const SH_BUDGET_: usize, const SH_DM_: u32>(input: &[u8], out: &mut [u32]) -> (usize, usize) {
    if input.len() >= Y_A_SMALLN { y_a_fl_rle_parse(input, out) } else {

    let mut cache = [0u32; 4096];
    let mut stats = [0u32; 128];
    let r = y_a_sh_rle_probe(input, &mut cache, &mut stats);
    if r.1 >= input.len() {
        let mut q = [0usize; 320];
        y_a_sh_table::<SH_L_, SH_D_, SH_BUDGET_, SH_DM_>(&stats, &mut q);
        y_a_sh_replay(input, out, &cache, &q)
    } else { y_a_fl_rle_parse(input, out) }

    }
}

/// The floor phase: the whole input with the DNA parser when `m == 1` (genome mode), with the class-T price-lazy
/// parser for inputs shorter than Y_A_SMALLN, else nothing: `(ntok, pos)`.
#[inline(always)]
pub fn y_a_dna_part<const IH_: usize, const IT_: usize, const TS_: usize, const ACC_: u64, const SH_L_: u32, const SH_D_: u32, const SH_BUDGET_: usize, const SH_DM_: u32>(input: &[u8], out: &mut [u32], m: usize) -> (usize, usize) {
    let small = if input.len() < Y_A_SMALLN { 1usize } else { 0usize };
    if m == 3 {
        y_a_sh_rle_phase::<SH_L_, SH_D_, SH_BUDGET_, SH_DM_>(input, out)
    } else if small == 1 {
        y_a_small_phase::<SH_L_, SH_D_, SH_BUDGET_, SH_DM_>(input, out)
    } else if m == 2 {
        y_a_h3_run::<IH_, IT_, TS_, ACC_>(input, out)
    } else {
        (0, 0)
    }
}

/// Genome mode: literal costs from a sampled histogram, then the DNA parser.


// Encoder-aware shaping constants: only untrusted candidate selection changes.
pub const Y_A_SH_L: [u32; 8] = [128; 8];
pub const Y_A_SH_D: [u32; 8] = [16; 8];
pub const Y_A_SH_BUDGET: [usize; 8] = [96; 8];
pub const Y_A_SH_DM: [u32; 8] = [16; 8];

#[inline(always)]
pub fn y_a_sh_lc(l: usize) -> usize {
    if l >= 258 { 28 }
    else if l <= 10 { l.wrapping_sub(3) % 29 }
    else if l <= 18 { 8 + (l - 11) / 2 }
    else if l <= 34 { 12 + (l - 19) / 4 }
    else if l <= 66 { 16 + (l - 35) / 8 }
    else if l <= 130 { 20 + (l - 67) / 16 }
    else if l <= 257 { 24 + (l - 131) / 32 }
    else { 28 }
}

#[inline(always)]
pub fn y_a_sh_dc(d: usize) -> usize {
    if d <= 4 { d.wrapping_sub(1) % 30 }
    else {
        let x = d.wrapping_sub(1) as u64;
        let e = 63u32.wrapping_sub((x | 1).leading_zeros()) % 64;
        let s = e.wrapping_sub(1) % 64;
        (2usize.wrapping_mul(e as usize).wrapping_add((x >> s) as usize).wrapping_sub(2)) % 30
    }
}


// Count candidate match codes. Candidate decisions are not output tokens.


#[inline(always)]
pub fn y_a_sh_fill(q: &mut [usize; 320], begin: usize, end: usize, best: usize, keep: usize) {
    let mut l = begin;
    while l < 259 && l < end {
        q[l] = if keep == 1 { l } else { best };
        l += 1;
    }
}

#[inline(always)]
pub fn y_a_sh_table<const SH_L_: u32, const SH_D_: u32, const SH_BUDGET_: usize, const SH_DM_: u32>(stats: &[u32; 128], q: &mut [usize; 320]) {
    let lb = [3usize,4,5,6,7,8,9,10,11,13,15,17,19,23,27,31,35,43,51,59,67,83,99,115,131,163,195,227,258];
    let mut best = 0usize;
    let mut c = 0usize;
    while c < 29 {
        let begin = lb[c];
        let end = if c < 28 { lb[c + 1] } else { 259 };
        let waste = (stats[29 + c] as usize).wrapping_sub(best.wrapping_mul(stats[c] as usize));
        let keep = if stats[c] > SH_L_ || waste > SH_BUDGET_ { 1 } else { 0 };
        y_a_sh_fill(q, begin, end, best, keep);
        if keep == 1 { best = end.wrapping_sub(1); }
        c += 1;
    }
    let mut c = 0usize;
    while c < 30 {
        q[259 + c] = if stats[64 + c] <= SH_D_ && stats[96 + c] <= SH_DM_ { 1 } else { 0 };
        c += 1;
    }
}

// Replay cached decisions; every shorter match/literal is emitted and verified by the trusted kit.

// Merge adjacent cached literal runs before trusted emission.
#[inline(always)]
pub fn y_a_sh_litrun(cache: &[u32; 4096], ix: usize) -> (usize, usize) {
    let mut sum = 0usize;
    let mut k = 0usize;
    while k < 4096 && cache[ix.wrapping_add(k) % 4096] > 0 && cache[ix.wrapping_add(k) % 4096] < 512 {
        sum = sum.wrapping_add(cache[ix.wrapping_add(k) % 4096] as usize);
        k += 1;
    }
    (k, sum)
}

#[inline(always)]
pub fn y_a_sh_replay(input: &[u8], out: &mut [u32], cache: &[u32; 4096], q: &[usize; 320]) -> (usize, usize) {
    let n = input.len();
    let mut pos = 0usize;
    let mut ntok = 0usize;
    let mut ix = 0usize;
    let mut rem = 0usize;
    let mut dist = 0usize;
    while pos < n {
        if rem == 0 {
            let t = cache[ix % 4096];
            ix = ix.wrapping_add(1);
            if t >= 512 {
                rem = (t % 512) as usize;
                dist = (t / 512) as usize;
            } else {
                let a = y_a_sh_litrun(cache, ix.wrapping_sub(1));
                ix = ix.wrapping_add(a.0).wrapping_sub(1);
                rem = a.1;
                dist = 0;
            }
        }
        let drop = if dist > 0 { q[259 + y_a_sh_dc(dist) % 30] } else { 0 };
        let l = if dist > 0 && drop == 0 && rem < 259 { q[rem] } else { 0 };
        let lits = if dist == 0 || drop == 1 || l < 3 { rem } else { 1 };
        let r = y_a_lane_emit(input, out, pos, dist, l, lits, ntok);
        let olen = out.len();
        let olen = out.len();
        let olen = out.len();
        let adv = r.1.wrapping_sub(pos);
        rem = if adv < rem { rem - adv } else { 0 };
        ntok = r.0;
        pos = r.1;
    }
    (ntok, pos)
}


// Frequency accounting is fused with candidate collection.
#[inline(always)]
pub fn y_a_sh_add(stats: &mut [u32; 128], l: usize, d: usize) {
    let a = y_a_sh_lc(l) % 29;
    let b = y_a_sh_dc(d) % 30;
    stats[a] = stats[a].wrapping_add(1);
    stats[29 + a] = stats[29 + a].wrapping_add(l as u32);
    stats[64 + b] = stats[64 + b].wrapping_add(1);
    stats[96 + b] = if l as u32 > stats[96 + b] { l as u32 } else { stats[96 + b] };
}

#[inline(always)]
pub fn y_a_sh_probe(input: &[u8], cache: &mut [u32; 4096], stats: &mut [u32; 128], lh: &[u32; 256], cf: &[usize; 8]) -> (usize, usize) {
    let n = input.len();
    let depth = cf[0];
    let depth2 = cf[1];
    let lazy = cf[2];
    let nice = cf[3];
    let ih = cf[4];
    let it = cf[5];
    let acc = cf[6];
    let h0 = 2049usize;
    let litq = y_a_fl_litq(h0);
    let hsh = y_a_fl_hsh(h0);
    let mut head = [0u32; 16384];
    let mut prev = [0u32; 32768];
    let mut pos = 0usize;
    let mut ntok = 0usize;
    let mut carry = 0usize;
    let mut miss = 0usize;
    while pos < n && ntok < 4096 {
        let have = if carry != 0 { 1usize } else { 0usize };
        let harg3 = if have == 1 { 0 } else { depth };
        let s1 = y_a_fl_search(input, &mut head, &mut prev, pos, harg3, 1, 2, 4096, litq, hsh, nice);
        let m1 = if have == 1 { carry } else { s1 };
        let l1 = m1 % 512;
        if l1 < 3 {
            let lits = y_a_fl_lits(miss, acc);
            cache[ntok] = lits as u32;
            let r = (ntok + 1, pos.wrapping_add(lits));
            miss = miss.wrapping_add(1);
            carry = 0;
            ntok = r.0;
            pos = r.1;
        } else {
            let d1 = (m1 / 512) % 65536;
            let want = if l1 < lazy { 1usize } else { 0usize };
            let p2 = if want == 1 { if l1 >= Y_A_FL_GOOD { depth2 } else { depth } } else { 0 };
            let s2 = y_a_fl_search(input, &mut head, &mut prev, pos.wrapping_add(1), p2, 1, l1.wrapping_sub(1), y_a_fl_score(l1, d1, litq), litq, hsh, nice);
            let take2 = if s2 != 0 { 1usize } else { 0usize };
            let l = if take2 == 1 { 0 } else { l1 };
            let d = if take2 == 1 { 0 } else { d1 };
            cache[ntok] = (if l >= 3 { l | d.wrapping_mul(512) } else { 1 }) as u32;
            if l >= 3 { y_a_sh_add(stats, l, d); }
            let advance = if l >= 3 { l } else { 1 };
            let r = (ntok + 1, pos.wrapping_add(advance));
            let npos = r.1;
            let matched = if l >= 3 { if npos == pos.wrapping_add(l) { 1usize } else { 0usize } } else { 0usize };
            let from = if want == 1 { pos.wrapping_add(2) } else { pos.wrapping_add(1) };
            let harg4 = if matched == 1 { npos } else { from };
            y_a_fl_insert_match(input, &mut head, &mut prev, from, harg4, hsh, ih, it);
            carry = if take2 == 1 { s2 } else { 0 };
            miss = 0;
            ntok = r.0;
            pos = npos;
        }
    }
    (ntok, pos)
}

/// Small inputs: the class-T price-lazy parser.
#[inline(always)]
pub fn y_a_small_phase<const SH_L_: u32, const SH_D_: u32, const SH_BUDGET_: usize, const SH_DM_: u32>(input: &[u8], out: &mut [u32]) -> (usize, usize) {
    let mut fh = [1u32; 256];
    let mut cf = [0usize; 8];
    cf[0] = Y_A_FT_DEPTH;
    cf[1] = Y_A_FT_DEPTH2;
    cf[2] = Y_A_FT_LAZY;
    cf[3] = Y_A_FT_NICE;
    cf[4] = Y_A_FT_IH;
    cf[5] = Y_A_FT_IT;
    cf[6] = Y_A_FT_ACC;
    let mut cache = [0u32; 4096];
    let mut stats = [0u32; 128];
    let r = y_a_sh_probe(input, &mut cache, &mut stats, &fh, &cf);
    if r.1 >= input.len() {
        let mut q = [0usize; 320];
        y_a_sh_table::<SH_L_, SH_D_, SH_BUDGET_, SH_DM_>(&stats, &mut q);
        y_a_sh_replay(input, out, &cache, &q)
    } else { y_a_fl_lazy_parse(input, out, &fh, &cf) }
}

// ============================ h3 y_a_mode (machine-code-like binaries): its own copy of the search (3-byte short hash,
// min length 3) and of the trusted kit (h3_ prefix), run as a floor phase over the whole input.
pub const Y_A_HM3: u64 = 0x4A7C150000000000;
pub const Y_A_MINL3: usize = 3;
pub const Y_A_MM3: u64 = 16777215;

/// Little-endian 4-byte load at `p`; 0 when out of range.


/// Little-endian 8-byte load at `p` (two 4-byte halves); 0 when out of range.
pub fn y_a_h3_ld8(input: &[u8], p: usize) -> u64 {
    let n = input.len();
    if n < 8 || p > n - 8 {
        return 0;
    }
    let hi = ((input[p + 7] as u32) << 24) | ((input[p + 6] as u32) << 16) | ((input[p + 5] as u32) << 8) | (input[p + 4] as u32);
    let lo = ((input[p + 3] as u32) << 24) | ((input[p + 2] as u32) << 16) | ((input[p + 1] as u32) << 8) | (input[p] as u32);
    ((hi as u64) << 32) | (lo as u64)
}

/// Index (0..7) of the first differing byte of two little-endian words, given their xor (!= 0).
pub fn y_a_h3_first_diff(x: u64) -> usize {
    let a = ((x & 0x00FF00FF00FF00FF) << 8) | ((x >> 8) & 0x00FF00FF00FF00FF);
    let b = ((a & 0x0000FFFF0000FFFF) << 16) | ((a >> 16) & 0x0000FFFF0000FFFF);
    let c = (b << 32) | (b >> 32);
    ((c | 1).leading_zeros() / 8) as usize
}

/// Common prefix of positions `a < b` beyond the first 8 bytes, up to `cap` (search only; never trusted).
pub fn y_a_h3_fast_len(input: &[u8], a: usize, b: usize, cap: usize) -> usize {
    let mut l = 8usize;
    let mut go = 1usize;
    let mut it = 0usize;
    while go == 1 && it < 40 {
        if l < cap {
            let x = y_a_h3_ld8(input, a.wrapping_add(l)) ^ y_a_h3_ld8(input, b.wrapping_add(l));
            let k = if x == 0 { 8 } else { y_a_h3_first_diff(x) };
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

/// Copy of `fast_len` for the lazy site.
/// Common prefix of positions `a < b` beyond the first 8 bytes, up to `cap` (search only; never trusted).
pub fn y_a_h3_fast_len2(input: &[u8], a: usize, b: usize, cap: usize) -> usize {
    let mut l = 8usize;
    let mut go = 1usize;
    let mut it = 0usize;
    while go == 1 && it < 40 {
        if l < cap {
            let x = y_a_h3_ld8(input, a.wrapping_add(l)) ^ y_a_h3_ld8(input, b.wrapping_add(l));
            let k = if x == 0 { 8 } else { y_a_h3_first_diff(x) };
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

/// Copy of `fast_len` for the lazy chain.
/// Common prefix of positions `a < b` beyond the first 8 bytes, up to `cap` (search only; never trusted).
pub fn y_a_h3_fast_len3(input: &[u8], a: usize, b: usize, cap: usize) -> usize {
    let mut l = 8usize;
    let mut go = 1usize;
    let mut it = 0usize;
    while go == 1 && it < 40 {
        if l < cap {
            let x = y_a_h3_ld8(input, a.wrapping_add(l)) ^ y_a_h3_ld8(input, b.wrapping_add(l));
            let k = if x == 0 { 8 } else { y_a_h3_first_diff(x) };
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

/// Hash of the word at `p` with multiplier `mk` (= the golden-ratio constant shifted left by 32: first 4 bytes, by
/// 40: first 3 bytes), 64 - Y_A_HSR bits.
pub fn y_a_h3_hashp(input: &[u8], p: usize) -> usize {
    let v = y_a_h3_ld8(input, p);
    ((v.wrapping_mul(Y_A_HM3) >> (Y_A_HSR % 64)) as usize) % 65536
}

/// Hash of the 8 bytes at `p` (long table), 16 bits.
pub fn y_a_h3_hashl(input: &[u8], p: usize) -> usize {
    let v = y_a_h3_ld8(input, p);
    ((v.wrapping_mul(0xCF1BBCDCB7A56463) >> (Y_A_HSR % 64)) as usize) % 65536
}

/// The candidate `(cs, cl)` (short / long table entries, pos+1 encoded, 0 = none) at `p`: the long one when its
/// first 8 bytes agree, else the short one. Returns `len | dist << 9` (len >= Y_A_MINL3), or 0.
#[inline(always)]
pub fn y_a_h3_eval(input: &[u8], p: usize, cs: usize, cl: usize) -> usize {
    let n = input.len();
    if n < 16 || p > n - 16 {
        return 0;
    }
    let v = y_a_h3_ld8(input, p);
    let lim = if p < 32768 { p } else { 32768 };
    let okl = if p.wrapping_sub(cl) < lim { 1usize } else { 0usize };
    let xl = if okl == 1 { y_a_h3_ld8(input, cl.wrapping_sub(1)) ^ v } else { 1 };
    let oks = if p.wrapping_sub(cs) < lim { 1usize } else { 0usize };
    let xs = if xl == 0 { 0 } else if oks == 1 { y_a_h3_ld8(input, cs.wrapping_sub(1)) ^ v } else { 1 };
    if xl != 0 && xs & Y_A_MM3 != 0 {
        return 0;
    }
    let usel = if xl == 0 { 1usize } else { 0usize };
    let c = if usel == 1 { cl } else { cs };
    let x = if usel == 1 { xl } else { xs };
    let rem = n - p - 8;
    let cap = if rem < 258 { rem } else { 258 };
    let l = if x == 0 { y_a_h3_fast_len(input, c.wrapping_sub(1), p, cap) } else { y_a_h3_first_diff(x) };
    let d = p.wrapping_sub(c.wrapping_sub(1));
    let ok = if l >= Y_A_MINL3 { if l > 3 { 1usize } else if d <= Y_A_MAX3 { 1 } else { 0 } } else { 0 };
    if ok == 1 {
        l | d.wrapping_mul(512)
    } else {
        0
    }
}

/// Lazy-site copy of `eval` (keeps both inlined).
/// The candidate `(cs, cl)` (short / long table entries, pos+1 encoded, 0 = none) at `p`: the long one when its
/// first 8 bytes agree, else the short one. Returns `len | dist << 9` (len >= Y_A_MINL3), or 0.
pub fn y_a_h3_eval2(input: &[u8], p: usize, cs: usize, cl: usize) -> usize {
    let n = input.len();
    if n < 16 || p > n - 16 {
        return 0;
    }
    let v = y_a_h3_ld8(input, p);
    let tag = cl / 16777216;
    let cl = cl % 16777216;
    let ht = y_a_h3_hashp(input, p) % 256;
    let lim = if p < 32768 { p } else { 32768 };
    let okl = if p.wrapping_sub(cl) < lim { 1usize } else { 0usize };
    let xl = if okl == 1 && tag == ht { y_a_h3_ld8(input, cl.wrapping_sub(1)) ^ v } else { 1 };
    let oks = if p.wrapping_sub(cs) < lim { 1usize } else { 0usize };
    let xs = if xl == 0 { 0 } else if oks == 1 { y_a_h3_ld8(input, cs.wrapping_sub(1)) ^ v } else { 1 };
    let usel = if xl == 0 { 1usize } else { 0usize };
    let c = if usel == 1 { cl } else { cs };
    let x = if usel == 1 { xl } else { xs };
    let rem = n - p - 8;
    let cap = if rem < 258 { rem } else { 258 };
    let l = if x == 0 { y_a_h3_fast_len2(input, c.wrapping_sub(1), p, cap) } else { y_a_h3_first_diff(x) };
    let d = p.wrapping_sub(c.wrapping_sub(1));
    let ok = if l >= Y_A_MINL3 { if l > 3 { 1usize } else if d <= Y_A_MAX3 { 1 } else { 0 } } else { 0 };
    if ok == 1 {
        l | d.wrapping_mul(512)
    } else {
        0
    }
}

/// Lazy-chain copy of `eval` (keeps both inlined).
/// The candidate `(cs, cl)` (short / long table entries, pos+1 encoded, 0 = none) at `p`: the long one when its
/// first 8 bytes agree, else the short one. Returns `len | dist << 9` (len >= Y_A_MINL3), or 0.
pub fn y_a_h3_eval3(input: &[u8], p: usize, cs: usize, cl: usize) -> usize {
    let n = input.len();
    if n < 16 || p > n - 16 {
        return 0;
    }
    let v = y_a_h3_ld8(input, p);
    let tag = cl / 16777216;
    let cl = cl % 16777216;
    let ht = y_a_h3_hashp(input, p) % 256;
    let lim = if p < 32768 { p } else { 32768 };
    let okl = if p.wrapping_sub(cl) < lim { 1usize } else { 0usize };
    let xl = if okl == 1 && tag == ht { y_a_h3_ld8(input, cl.wrapping_sub(1)) ^ v } else { 1 };
    let oks = if p.wrapping_sub(cs) < lim { 1usize } else { 0usize };
    let xs = if xl == 0 { 0 } else if oks == 1 { y_a_h3_ld8(input, cs.wrapping_sub(1)) ^ v } else { 1 };
    let usel = if xl == 0 { 1usize } else { 0usize };
    let c = if usel == 1 { cl } else { cs };
    let x = if usel == 1 { xl } else { xs };
    let rem = n - p - 8;
    let cap = if rem < 258 { rem } else { 258 };
    let l = if x == 0 { y_a_h3_fast_len3(input, c.wrapping_sub(1), p, cap) } else { y_a_h3_first_diff(x) };
    let d = p.wrapping_sub(c.wrapping_sub(1));
    let ok = if l >= Y_A_MINL3 { if l > 3 { 1usize } else if d <= Y_A_MAX3 { 1 } else { 0 } } else { 0 };
    if ok == 1 {
        l | d.wrapping_mul(512)
    } else {
        0
    }
}

/// Insert positions `from .. to` into both tables.
pub fn y_a_h3_insert_range(input: &[u8], head: &mut [u32; 131072], from: usize, to: usize) {
    let n = input.len();
    let mut p = from;
    while p < to && 16 <= n && p <= n - 16 {
        let hs = y_a_h3_hashp(input, p);
        let hl = y_a_h3_hashl(input, p);
        head[hs] = (p as u32).wrapping_add(1);
        head[(65536 + hl) % 131072] = ((p as u32).wrapping_add(1) % 16777216) | (((hs % 256) as u32) << 24);
        p += 1;
    }
}

/// Insert every Y_A_TS-th position of `from .. to` into both tables (Y_A_TL == 1: the long table only).
pub fn y_a_h3_insert_range2<const TS_: usize>(input: &[u8], head: &mut [u32; 131072], from: usize, to: usize) {
    let n = input.len();
    let mut p = from;
    let mut c = 0usize;
    while c < to && p < to && 16 <= n && p <= n - 16 {
        let hs = y_a_h3_hashp(input, p);
        let hl = y_a_h3_hashl(input, p);
        if Y_A_TL == 0 {
            head[hs] = (p as u32).wrapping_add(1);
        }
        head[(65536 + hl) % 131072] = ((p as u32).wrapping_add(1) % 16777216) | (((hs % 256) as u32) << 24);
        p = p.wrapping_add(TS_);
        c += 1;
    }
}

/// Insert the inside `from .. to` of an emitted match: its first Y_A_IH and last Y_A_IT positions.
pub fn y_a_h3_insert_match<const IH_: usize, const IT_: usize, const TS_: usize>(input: &[u8], head: &mut [u32; 131072], from: usize, to: usize) {
    let a = from.wrapping_add(IH_);
    let a2 = if a < to { a } else { to };
    let b = to.wrapping_sub(IT_);
    let b2 = if b > a2 { if b < to { b } else { a2 } } else { a2 };
    y_a_h3_insert_range(input, head, from.wrapping_add(1), a2);
    y_a_h3_insert_range2::<TS_>(input, head, b2, to);
}

/// Literal-scan step after `k` probes: 1 + (k >> Y_A_ACC), at most Y_A_AMAX.
pub fn y_a_h3_run_len<const ACC_: u64>(k: usize) -> usize {
    let over = ((k as u64) >> (ACC_ % 64)) as usize;
    if over < Y_A_AMAX {
        over + 1
    } else {
        Y_A_AMAX
    }
}

/// How far the match `(d, l)` found at `p` extends backwards, staying at or after `lo` (8-byte word steps).
pub fn y_a_h3_bext(input: &[u8], lo: usize, p: usize, d: usize, l: usize) -> usize {
    let l0 = if p > lo { p - lo } else { 0 };
    let l1 = if p > d { if d > 0 { p - d } else { 0 } } else { 0 };
    let l2 = if l < 258 { 258 - l } else { 0 };
    let m0 = if l0 < l1 { l0 } else { l1 };
    let lim = if m0 < l2 { m0 } else { l2 };
    let mut e = 0usize;
    let mut go = 1usize;
    let mut it = 0usize;
    while go == 1 && it < 40 {
        let q = p.wrapping_sub(e);
        let ok = if e < lim { y_a_h3_q8ok(q, d) } else { 0 };
        if ok == 1 {
            let x = y_a_h3_ld8(input, q.wrapping_sub(8)) ^ y_a_h3_ld8(input, q.wrapping_sub(8).wrapping_sub(d));
            let k = if x == 0 { 8 } else { (x.leading_zeros() / 8) as usize };
            e = e.wrapping_add(k);
            go = if x == 0 { 1 } else { 0 };
        } else {
            go = 0;
        }
        it += 1;
    }
    if e > lim {
        lim
    } else {
        e
    }
}

/// 1 iff the 8-byte windows ending at `q` and at `q - d` are both in range (`q >= d + 8`).
pub fn y_a_h3_q8ok(q: usize, d: usize) -> usize {
    if q >= d.wrapping_add(8) { 1 } else { 0 }
}

/// 1 iff the byte before `q` repeats at distance `d` (so a match found at `q` also starts at `q - 1`).
pub fn y_a_h3_back1(input: &[u8], q: usize, d: usize) -> usize {
    let n = input.len();
    if d == 0 || q <= d || q > n {
        return 0;
    }
    if input[q - 1] == input[q - 1 - d] { 1 } else { 0 }
}

/// Insert `p` at short / long buckets `hs`, `hl` and read the entries at `hs1`, `hl1` (before the insertion):
/// `cs1 << 32 | cl1`.
pub fn y_a_h3_tab_step(head: &mut [u32; 131072], hs: usize, hl: usize, hs1: usize, hl1: usize, p: usize) -> u64 {
    let cs1 = head[hs1 % 131072];
    let cl1 = head[65536usize.wrapping_add(hl1) % 131072];
    head[hs % 131072] = (p as u32).wrapping_add(1);
    head[65536usize.wrapping_add(hl) % 131072] = ((p as u32).wrapping_add(1) % 16777216) | (((hs % 256) as u32) << 24);
    ((cs1 as u64) << 32) | (cl1 as u64)
}

/// Read the entries at short / long buckets `hs`, `hl` and insert `q` there: `cs << 32 | cl`.
pub fn y_a_h3_tab_step2(head: &mut [u32; 131072], hs: usize, hl: usize, q: usize) -> u64 {
    let cs = head[hs % 131072];
    let cl = head[65536usize.wrapping_add(hl) % 131072];
    head[hs % 131072] = (q as u32).wrapping_add(1);
    head[65536usize.wrapping_add(hl) % 131072] = ((q as u32).wrapping_add(1) % 16777216) | (((hs % 256) as u32) << 24);
    ((cs as u64) << 32) | (cl as u64)
}

/// Software-pipelined scan from `pos`: each iteration inserts the probe position `p`, loads the table entries of the
/// next probe position and evaluates `p`'s entries (loaded one iteration earlier). Returns `p << 25 | len | dist << 9`
/// of the first match (or `n << 25`), `q << 32 | probes` and `cs << 32 | cl` (the next probe position `q` and its
/// preloaded table entries, for the lazy step).
pub fn y_a_h3_scan<const ACC_: u64>(input: &[u8], head: &mut [u32; 131072], pos: usize) -> (u64, u64, u64) {
    let n = input.len();
    let mut p = pos;
    let mut res = 0usize;
    let mut it = 0usize;
    let mut hs = y_a_h3_hashp(input, p);
    let mut hl = y_a_h3_hashl(input, p);
    let mut cs = head[hs] as usize;
    let mut cl = head[(65536 + hl) % 131072] as usize;
    while it < n && res == 0 && 16 <= n && p <= n - 16 {
        let st = y_a_h3_run_len::<ACC_>(it);
        let q1 = p.wrapping_add(st);
        let hs1 = y_a_h3_hashp(input, q1);
        let hl1 = y_a_h3_hashl(input, q1);
        let t = y_a_h3_tab_step(head, hs, hl, hs1, hl1, p);
        let cl0 = if cl / 16777216 == hs % 256 { cl % 16777216 } else { 0 };
        let r = y_a_h3_eval(input, p, cs, cl0);
        res = r;
        p = if r == 0 { q1 } else { p };
        hs = hs1;
        hl = hl1;
        cs = ((t >> 32) as u32) as usize;
        cl = (t as u32) as usize;
        it += 1;
    }
    let ran = if it > 0 { 1usize } else { 0usize };
    let q = if res == 0 { p } else { p.wrapping_add(y_a_h3_run_len::<ACC_>(it.wrapping_sub(1))) };
    let qs = if ran == 1 { cs } else { 0 };
    let ql = if ran == 1 { cl } else { 0 };
    let m = if res == 0 { (n as u64) << 25 } else { ((p as u64) << 25) | (res as u64) };
    let kq = ((q as u64) << 32) | ((it as u64) % 4294967296);
    let cq = ((qs as u64) << 32) | ((ql as u64) % 4294967296);
    (m, kq, cq)
}

/// One further lazy step after a lazy win `m` that starts at `s`: probe `s + 1` (inserting it); returns the new
/// match with bit 63 set when the candidate there won by ending at least Y_A_LZM bytes later (continue), the longer
/// match at `s` when the candidate also starts at `s` (stop), else `m` (stop).
pub fn y_a_h3_lazy_step(input: &[u8], head: &mut [u32; 131072], m: u64) -> u64 {
    let s = (m >> 25) as usize;
    let l = (m as usize) % 512;
    let q = s.wrapping_add(1);
    let hs = y_a_h3_hashp(input, q);
    let hl = y_a_h3_hashl(input, q);
    let t = y_a_h3_tab_step2(head, hs, hl, q);
    let cs = ((t >> 32) as u32) as usize;
    let cl = (t as u32) as usize;
    let r2 = if l < Y_A_HLZT { y_a_h3_eval3(input, q, cs, cl) } else { 0 };
    let l2 = r2 % 512;
    let d2 = (r2 / 512) % 65536;
    let b1 = if l2 >= 3 { y_a_h3_back1(input, q, d2) } else { 0 };
    let d = ((m >> 9) % 65536) as usize;
    let z2 = ((d2 as u32).wrapping_sub(1) | 1).leading_zeros();
    let z1 = ((d as u32).wrapping_sub(1) | 1).leading_zeros();
    let sc = if Y_A_SCL == 1 { if l2 == l { if z2 > z1 { 1usize } else { 0usize } } else { 0usize } } else { 0usize };
    let win = if b1 == 1 { if l2 >= l { 1usize } else { 0usize } } else if l2.wrapping_add(1) >= l.wrapping_add(Y_A_LZM) { 2 } else if sc == 1 { 2 } else { 0 };
    let win2 = if l2 >= 3 { win } else { 0 };
    let m2 = ((s as u64) << 25) | ((d2 as u64) << 9) | (l2.wrapping_add(1) as u64);
    let m3 = ((q as u64) << 25) | ((d2 as u64) << 9) | (l2 as u64) | (1u64 << 63);
    if win2 == 1 {
        m2
    } else if win2 == 2 {
        m3
    } else {
        m
    }
}

/// Estimated saving (quarter bits, offset by 4096) of coding `l` bytes as a match at distance `d`: `l` literals of
/// Y_A_SLQ quarter bits against Y_A_SC0 plus 4 per extra bit.


/// Further lazy steps (at most Y_A_LZN) after a lazy win `m0` (see `lazy_step`).
pub fn y_a_h3_lazy_more(input: &[u8], head: &mut [u32; 131072], m0: u64) -> u64 {
    let mut m = m0;
    let mut go = 1usize;
    let mut it = 0usize;
    while go == 1 && it < Y_A_LZN {
        let r = y_a_h3_lazy_step(input, head, m);
        m = r % 9223372036854775808;
        go = (r >> 63) as usize;
        it += 1;
    }
    m
}

/// The next match at or after `pos`: `start << 25 | dist << 9 | len`, or `n << 25` when there is none.
/// Lazy step (match shorter than Y_A_LZT, next probe at `p + 1`): the candidate at `p + 1` wins when it also starts at
/// `p` and is longer, or when it ends at least Y_A_LZM bytes later. Backward extension (Y_A_BEXT) only after acceleration.
pub fn y_a_h3_find<const ACC_: u64>(input: &[u8], head: &mut [u32; 131072], pos: usize) -> u64 {
    if Y_A_MINL3 > 258 {
        return (input.len() as u64) << 25;
    }
    let sc = y_a_h3_scan::<ACC_>(input, head, pos);
    let r = sc.0;
    let p = (r >> 25) as usize;
    let l = (r as usize) % 512;
    let d = ((r >> 9) % 65536) as usize;
    let q = (sc.1 >> 32) as usize;
    let k = (sc.1 as u32) as usize;
    let qs = (sc.2 >> 32) as usize;
    let ql = (sc.2 as u32) as usize;
    let lz = if l < Y_A_HLZT { if q == p.wrapping_add(1) { 1usize } else { 0usize } } else { 0usize };
    let r2 = if lz == 1 { y_a_h3_eval2(input, q, qs, ql) } else { 0 };
    let l2 = r2 % 512;
    let d2 = (r2 / 512) % 65536;
    let b1 = if l2 >= 3 { y_a_h3_back1(input, q, d2) } else { 0 };
    let z2 = ((d2 as u32).wrapping_sub(1) | 1).leading_zeros();
    let z1 = ((d as u32).wrapping_sub(1) | 1).leading_zeros();
    let sc = if Y_A_SCL == 1 { if l2 == l { if z2 > z1 { 1usize } else { 0usize } } else { 0usize } } else { 0usize };
    let win = if b1 == 1 { if l2 >= l { 1usize } else { 0usize } } else if l2.wrapping_add(1) >= l.wrapping_add(Y_A_LZM) { 2 } else if sc == 1 { 2 } else { 0 };
    let win2 = if l2 >= 3 { win } else { 0 };
    let bx = if Y_A_BEXT == 1 { if k > Y_A_BK { 1usize } else { 0usize } } else { 0usize };
    let e = if bx == 1 { if l >= 3 { y_a_h3_bext(input, pos, p, d, l) } else { 0 } } else { 0 };
    let m1 = ((p.wrapping_sub(e) as u64) << 25) | ((d as u64) << 9) | (l.wrapping_add(e) as u64);
    let m2 = ((p as u64) << 25) | ((d2 as u64) << 9) | (l2.wrapping_add(1) as u64);
    let m3 = ((q as u64) << 25) | ((d2 as u64) << 9) | (l2 as u64);
    if win2 == 1 {
        m2
    } else if win2 == 2 {
        y_a_h3_lazy_more(input, head, m3)
    } else {
        m1
    }
}

/// The carried result when it starts at `pos` (its literal run was emitted), else a fresh `find`.


/// Trusted: little-endian 8-byte word at `p` (0 when out of range).


/// Trusted: little-endian 4-byte word at `p` (0 when out of range).


/// Trusted: 1 iff `cap >= 8`, `cap - l < 8` and the 8-byte words at `a + cap - 8` and `b + cap - 8` are equal.


/// Trusted: 1 iff `4 <= cap < 8` and the 4-byte words at `a`, `b` and at `a + cap - 4`, `b + cap - 4` are equal.


/// Trusted: a length `l <= cap` over which the bytes at `a` and `b` provably agree, found with word compares.


/// Trusted: how many bytes agree at `a` and `b`, up to `cap` (word compares, then bytes).


/// True iff `(ch, d)` at `pos` is in range and its bytes agree.


/// Trusted: `cnt >= 1` literals from `pos0` (stopping at the input end).


/// Trusted: the match `(l, d)` at `pos` if it verifies, else `lits` literals.


/// h3 phase: the whole input with the h3 copy of the main loop (own table); `(ntok, pos)` with `pos = n`.
#[inline(never)]
pub fn y_a_h3_run<const IH_: usize, const IT_: usize, const TS_: usize, const ACC_: u64>(input: &[u8], out: &mut [u32]) -> (usize, usize) {
    let n = input.len();
    let mut head = [0u32; 131072];
    let mut pos = 0usize;
    let mut ntok = 0usize;
    while pos < n {
        let f = y_a_h3_find::<ACC_>(input, &mut head, pos);
        let start = (f >> 25) as usize;
        if start > pos {
            let r = y_a_emit_lits(input, out, pos, start.wrapping_sub(pos), ntok);
            ntok = r.0;
            pos = r.1;
        }
        if pos < n {
            let l = (f as usize) % 512;
            let d = ((f >> 9) % 65536) as usize;
            let r = y_a_emit_step(input, out, pos, d, l, 1, ntok);
            let npos = r.1;
            y_a_h3_insert_match::<IH_, IT_, TS_>(input, &mut head, pos, npos);
            ntok = r.0;
            pos = npos;
        }
    }
    (ntok, pos)
}

// ------------------------------------------------------------------ the parse loop

/// Per iteration one trusted call: the literal run before the next match (`emit_lits`, the match is carried to the
/// next iteration), or the match itself (`emit_step`), plus untrusted bookkeeping.
pub fn y_a_run_greedy<const IH_: usize, const IT_: usize, const TS_: usize, const ACC_: u64, const LZT_: usize>(input: &[u8], out: &mut [u32], head: &mut [u32; 131072], pos0: usize, ntok0: usize) -> usize {
    let n = input.len();
    let mut pos = pos0;
    let mut ntok = ntok0;
    while pos < n {
        let f = y_a_find::<ACC_, LZT_>(input, head, pos);
        let start = (f >> 25) as usize;
        if start > pos {
            let r = y_a_emit_lits(input, out, pos, start.wrapping_sub(pos), ntok);
            ntok = r.0;
            pos = r.1;
        }
        if pos < n {
            let l = (f as usize) % 512;
            let d = ((f >> 9) % 65536) as usize;
            let r = y_a_emit_step(input, out, pos, d, l, 1, ntok);
            let npos = r.1;
            y_a_insert_match::<IH_, IT_, TS_>(input, head, pos, npos);
            ntok = r.0;
            pos = npos;
        }
    }
    ntok
}

/// The mode-0 main parser from `pos0` (the floor phase's end).
pub fn y_a_main_part<const IH_: usize, const IT_: usize, const TS_: usize, const ACC_: u64, const LZT_: usize>(input: &[u8], out: &mut [u32], m: usize, pos0: usize, ntok0: usize) -> usize {
    let mut head = [0u32; 131072];
    y_a_run_greedy::<IH_, IT_, TS_, ACC_, LZT_>(input, out, &mut head, pos0, ntok0)
}

/// Sequential phases (no if/else between two loop-heavy parsers): the DNA phase covers the whole input in genome
/// mode and returns `(ntok, n)`, else `(0, 0)`; the main parser continues from its end.
#[inline(always)]
pub fn y_a_parse_row<const IH_: usize, const IT_: usize, const TS_: usize, const ACC_: u64, const LZT_: usize, const SH_L_: u32, const SH_D_: u32, const SH_BUDGET_: usize, const SH_DM_: u32>(input: &[u8], out: &mut [u32]) -> usize {
    let m = y_a_mode(input);
    let r = y_a_dna_part::<IH_, IT_, TS_, ACC_, SH_L_, SH_D_, SH_BUDGET_, SH_DM_>(input, out, m);
    if r.1 < input.len() { y_a_main_part::<IH_, IT_, TS_, ACC_, LZT_>(input, out, m, r.1, r.0) } else { r.0 }
}

#[inline(always)]
pub fn y_a_parse_mode(input: &[u8], out: &mut [u32], m: usize) -> usize {
    let row = m % 8;
    if row == 0 { y_a_parse_row::<{ Y_A_IH[0] }, { Y_A_IT[0] }, { Y_A_TS[0] }, { Y_A_ACC[0] }, { Y_A_LZT[0] }, { Y_A_SH_L[0] }, { Y_A_SH_D[0] }, { Y_A_SH_BUDGET[0] }, { Y_A_SH_DM[0] }>(input, out)
    } else if row == 1 { y_a_parse_row::<{ Y_A_IH[1] }, { Y_A_IT[1] }, { Y_A_TS[1] }, { Y_A_ACC[1] }, { Y_A_LZT[1] }, { Y_A_SH_L[1] }, { Y_A_SH_D[1] }, { Y_A_SH_BUDGET[1] }, { Y_A_SH_DM[1] }>(input, out)
    } else if row == 2 { y_a_parse_row::<{ Y_A_IH[2] }, { Y_A_IT[2] }, { Y_A_TS[2] }, { Y_A_ACC[2] }, { Y_A_LZT[2] }, { Y_A_SH_L[2] }, { Y_A_SH_D[2] }, { Y_A_SH_BUDGET[2] }, { Y_A_SH_DM[2] }>(input, out)
    } else if row == 3 { y_a_parse_row::<{ Y_A_IH[3] }, { Y_A_IT[3] }, { Y_A_TS[3] }, { Y_A_ACC[3] }, { Y_A_LZT[3] }, { Y_A_SH_L[3] }, { Y_A_SH_D[3] }, { Y_A_SH_BUDGET[3] }, { Y_A_SH_DM[3] }>(input, out)
    } else if row == 4 { y_a_parse_row::<{ Y_A_IH[4] }, { Y_A_IT[4] }, { Y_A_TS[4] }, { Y_A_ACC[4] }, { Y_A_LZT[4] }, { Y_A_SH_L[4] }, { Y_A_SH_D[4] }, { Y_A_SH_BUDGET[4] }, { Y_A_SH_DM[4] }>(input, out)
    } else if row == 5 { y_a_parse_row::<{ Y_A_IH[5] }, { Y_A_IT[5] }, { Y_A_TS[5] }, { Y_A_ACC[5] }, { Y_A_LZT[5] }, { Y_A_SH_L[5] }, { Y_A_SH_D[5] }, { Y_A_SH_BUDGET[5] }, { Y_A_SH_DM[5] }>(input, out)
    } else if row == 6 { y_a_parse_row::<{ Y_A_IH[6] }, { Y_A_IT[6] }, { Y_A_TS[6] }, { Y_A_ACC[6] }, { Y_A_LZT[6] }, { Y_A_SH_L[6] }, { Y_A_SH_D[6] }, { Y_A_SH_BUDGET[6] }, { Y_A_SH_DM[6] }>(input, out)
    } else { y_a_parse_row::<{ Y_A_IH[7] }, { Y_A_IT[7] }, { Y_A_TS[7] }, { Y_A_ACC[7] }, { Y_A_LZT[7] }, { Y_A_SH_L[7] }, { Y_A_SH_D[7] }, { Y_A_SH_BUDGET[7] }, { Y_A_SH_DM[7] }>(input, out) }
}




// ===== engine b: mix5.b.rs =====

pub const Y_B_LEX_BITS: [u8; 512] = [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0];

pub const Y_B_DEPTH: [usize; 8] = [8, 2, 4, 4, 4, 4, 4, 4];
pub const Y_B_DEPTH2: [usize; 8] = [2, 1, 1, 1, 1, 1, 1, 1];
pub const Y_B_GOOD: usize = 3;
pub const Y_B_LAZY: [usize; 8] = [544, 544, 1056, 544, 544, 544, 544, 544];
pub const Y_B_NICE: usize = 258;
pub const Y_B_IH: usize = 258;
pub const Y_B_IT: usize = 64;
pub const Y_B_ACC: [u64; 8] = [5, 5, 5, 5, 5, 5, 5, 5];
pub const Y_B_STEPMAX: [usize; 8] = [32, 32, 32, 32, 32, 32, 32, 32];
pub const Y_B_LITQ: [usize; 8] = [28, 28, 28, 28, 28, 28, 28, 28];
pub const Y_B_LADJ: [usize; 8] = [2, 2, 2, 2, 2, 2, 2, 2];
pub const Y_B_HLOW: [usize; 8] = [900, 900, 900, 900, 900, 900, 900, 900];
pub const Y_B_HSL: [u32; 8] = [0, 0, 0, 0, 0, 0, 0, 0];
pub const Y_B_ELO: [usize; 8] = [400, 400, 400, 400, 400, 400, 400, 400];
pub const Y_B_H3HI: [usize; 8] = [100, 100, 100, 100, 100, 100, 100, 100];
pub const Y_B_H3CTL: [usize; 8] = [100, 100, 100, 100, 100, 100, 100, 100];
pub const Y_B_H3E: [usize; 8] = [1700, 1700, 1700, 1700, 1700, 1700, 1700, 1700];
pub const Y_B_ACCL: [u64; 8] = [63, 63, 63, 63, 63, 63, 63, 63];
pub const Y_B_H3: [usize; 8] = [0; 8];
pub const Y_B_MAX3: usize = 4096;
pub const Y_B_H3INS: usize = 1;
pub const Y_B_C0Q: [usize; 8] = [44, 44, 44, 44, 44, 44, 44, 44];
pub const Y_B_C0L: [usize; 8] = [44, 44, 44, 44, 44, 44, 44, 44];
pub const Y_B_DEPTHL: [usize; 8] = [12, 12, 12, 12, 12, 12, 12, 12];
pub const Y_B_M3: [usize; 8] = [0, 0, 0, 0, 0, 0, 0, 0];
pub const Y_B_DEPTH3M: [usize; 8] = [12, 12, 12, 12, 12, 12, 12, 12];
pub const Y_B_M3E: [usize; 8] = [1900, 1900, 1900, 1900, 1900, 1900, 1900, 1900];
pub const Y_B_M3Z: [usize; 8] = [15, 15, 15, 15, 15, 15, 15, 15];
pub const Y_B_LZB: usize = 0;
pub const Y_B_BONUS: usize = 0;
pub const Y_B_EXT: usize = 1;
pub const Y_B_DIGN: [usize; 8] = [200, 200, 200, 200, 200, 200, 200, 200];
pub const Y_B_DN: [usize; 8] = [4, 2, 4, 4, 4, 4, 4, 4];
pub const Y_B_P2N: [usize; 8] = [2, 2, 2, 2, 2, 2, 2, 2];
pub const Y_B_LQN: [usize; 8] = [20, 20, 20, 20, 20, 20, 20, 20];
pub const Y_B_NBIG: [usize; 8] = [65536, 65536, 65536, 65536, 65536, 65536, 65536, 65536];
pub const Y_B_GOODL: usize = 258;
pub const Y_B_P2G: usize = 2;
pub const Y_B_NSMALL: [usize; 8] = [65536, 65536, 65536, 65536, 65536, 65536, 65536, 65536];
pub const Y_B_BIAS: usize = 4096;


/// One dial row, loaded once per parse call.
pub struct Y_B_Params {
    pub depth: usize,
    pub depth2: usize,
    pub lazy: usize,
    pub acc: u64,
    pub stepmax: usize,
    pub h3hi: usize,
    pub c0q: usize,
    pub dn: usize,
    pub p2n: usize,
    pub fl_pnc: usize,
    pub ft_ih: usize,
    pub ft_it: usize,
    pub ft_depth: usize,
    pub ft_depth2: usize,
    pub ft_lazy: usize,
    pub ft_nice: usize,
    pub ft_acc: usize,
    pub fd_depth: usize,
    pub fd_depth2: usize,
    pub fd_lazy: usize,
    pub fd_nice: usize,
    pub fd_ih: usize,
    pub fd_it: usize,
    pub fd_acc: usize,
    pub fh_depth: usize,
    pub fh_depth2: usize,
    pub fh_lazy: usize,
    pub fh_nice: usize,
    pub fh_ih: usize,
    pub fh_it: usize,
    pub fh_acc: usize,
    pub fl_pmin: usize,
    pub fl_rle_top: usize,
    pub fl_high: usize,
    pub fl_dbz: usize,
    pub fl_dbnp: usize,
    pub fl_use_t: usize,
    pub fl_use_d: usize,
    pub fl_use_h: usize,
    pub fl_use_lit: usize,
    pub lqn: usize,
    pub c0l: usize,
    pub hsl: u32,
    pub accl: u64,
    pub nsmall: usize,
    pub depthl: usize,
    pub depth3m: usize,
    pub elo: usize,
    pub hlow: usize,
    pub litq: usize,
    pub ladj: usize,
    pub m3: usize,
    pub m3e: usize,
    pub m3z: usize,
    pub h3: usize,
    pub h3ctl: usize,
    pub h3e: usize,
    pub nbig: usize,
    pub dign: usize,
    pub fl_litq: usize,
    pub fl_ladj: usize,
    pub fl_hlow: usize,
}

// ------------------------------------------------------------------ loads and compares (search only)

/// Little-endian 4-byte load at `p`; 0 when out of range.
pub fn y_b_ld4(input: &[u8], p: usize) -> u32 {
    let n = input.len();
    if n < 4 || p > n - 4 {
        return 0;
    }
    ((input[p + 3] as u32) << 24) | ((input[p + 2] as u32) << 16) | ((input[p + 1] as u32) << 8) | (input[p] as u32)
}

/// Little-endian 8-byte load at `p` (two u32 halves, highest byte read first); 0 when out of range.
pub fn y_b_ld8(input: &[u8], p: usize) -> u64 {
    let n = input.len();
    if n < 8 || p > n - 8 {
        return 0;
    }
    let hi = ((input[p + 7] as u32) << 24) | ((input[p + 6] as u32) << 16) | ((input[p + 5] as u32) << 8) | (input[p + 4] as u32);
    let lo = ((input[p + 3] as u32) << 24) | ((input[p + 2] as u32) << 16) | ((input[p + 1] as u32) << 8) | (input[p] as u32);
    ((hi as u64) << 32) | (lo as u64)
}

/// Index (0..7) of the first differing byte of two little-endian words, given their xor (!= 0).
pub fn y_b_first_diff(x: u64) -> usize {
    let low = x & 0u64.wrapping_sub(x);
    (63u32.wrapping_sub(low.leading_zeros()) / 8) as usize
}

/// Common prefix of positions `a < b`, up to `cap` (search only; never trusted).
#[inline(always)]
pub fn y_b_fast_len(input: &[u8], a: usize, b: usize, cap: usize) -> usize {
    let mut l = 0usize;
    let mut go = 1usize;
    let mut it = 0usize;
    while go == 1 && it < 40 {
        if l < cap {
            let x = y_b_ld8(input, a.wrapping_add(l)) ^ y_b_ld8(input, b.wrapping_add(l));
            let k = if x == 0 { 8 } else { y_b_first_diff(x) };
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
pub fn y_b_hashp(input: &[u8], p: usize, hs: u32) -> usize {
    if hs == 32 {
        return (y_b_ld4(input, p).wrapping_mul(2654435761) >> 16) as usize;
    }
    let v = y_b_ld8(input, p) << (hs % 64);
    (v.wrapping_mul(0x9E3779B97F4A7C15) >> 48) as usize
}

/// Hash of the low 3 bytes of a word into 14 bits.
pub fn y_b_hash3(w: u32) -> usize {
    ((w << 8).wrapping_mul(2654435761) >> 18) as usize
}

// ------------------------------------------------------------------ cost model (search only)

/// DEFLATE distance extra bits of `d`.
pub fn y_b_dextra(d: usize) -> usize {
    if d <= 4 {
        0
    } else {
        let x = (d.wrapping_sub(1) as u32) | 1;
        (31u32.wrapping_sub(x.leading_zeros()) as usize).wrapping_sub(1)
    }
}

/// DEFLATE length extra bits of `l`.
pub fn y_b_lextra(l: usize) -> usize {
    if l < 512 { Y_B_LEX_BITS[l % 512] as usize } else { 0 }
}

/// Estimated saving (quarter bits, offset by Y_B_BIAS) of coding `l` bytes as a match at `d`.
/// `cq` packs the literal cost (low 8 bits) and the match base cost (bits 8..).
pub fn y_b_score(l: usize, d: usize, cq: usize) -> usize {
    let cost = (cq / 256).wrapping_add(y_b_dextra(d).wrapping_add(y_b_lextra(l)).wrapping_mul(4));
    l.wrapping_mul(cq % 256).wrapping_add(Y_B_BIAS).wrapping_sub(cost)
}

/// Fixed-point log2 with 8 fractional bits (linear between powers of two).
pub fn y_b_lg8(x: u32) -> u64 {
    let y = x | 1;
    let e = 31u32.wrapping_sub(y.leading_zeros()) % 32;
    let m = if e >= 8 { (y >> ((e.wrapping_sub(8)) % 32)) & 255 } else { (y << ((8u32.wrapping_sub(e)) % 32)) & 255 };
    (e as u64).wrapping_mul(256).wrapping_add(m as u64)
}

/// Histogram of a strided sample of the input (about 4096 bytes).
pub fn y_b_sample(input: &[u8], h: &mut [u32; 256]) {
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
pub fn y_b_entropy256(h: &[u32; 256]) -> usize {
    let mut tot = 0u64;
    let mut acc = 0u64;
    let mut i = 0usize;
    while i < 256 {
        let c = h[i];
        tot = tot.wrapping_add(c as u64);
        acc = if c > 0 { acc.wrapping_add((c as u64).wrapping_mul(y_b_lg8(c))) } else { acc };
        i += 1;
    }
    let t32 = if tot > 4000000000 { 4000000000u32 } else { tot as u32 };
    let a = y_b_lg8(t32);
    let b = if tot == 0 { a } else { acc / tot };
    if a > b { (a - b) as usize } else { 0 }
}

/// Per mille of the sampled bytes in `lo .. hi`.
pub fn y_b_share(h: &[u32; 256], lo: usize, hi: usize) -> usize {
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
#[inline(always)]
pub fn y_b_low_mode(e: usize, dp: &Y_B_Params) -> usize {
    if e >= dp.elo && e < dp.hlow { 1 } else { 0 }
}

/// Literal cost (quarter bits): from the sampled entropy in low mode, else Y_B_LITQ.
#[inline(always)]
pub fn y_b_lit_cost(e: usize, low: usize, dp: &Y_B_Params) -> usize {
    let q = (e / 64).wrapping_add(dp.ladj);
    let q2 = if q < 6 { 6 } else if q > 36 { 36 } else { q };
    if low == 1 { q2 } else { dp.litq }
}

/// 1 when the input should use 3-byte hash chains (Y_B_M3 = 2: always; 1: by rule).
#[inline(always)]
pub fn y_b_m3_mode(h: &[u32; 256], e: usize, dp: &Y_B_Params) -> usize {
    let z = y_b_share(h, 0, 1);
    let a = if e >= dp.m3e { 1usize } else { 0usize };
    let b = if z >= dp.m3z { 1usize } else { 0usize };
    if dp.m3 == 2 { 1 } else if dp.m3 == 1 { a & b } else { 0 }
}

/// 1 when the 3-byte table should be used: binary-ish or non-ASCII input of moderate entropy.
#[inline(always)]
pub fn y_b_h3_mode(h: &[u32; 256], e: usize, dp: &Y_B_Params) -> usize {
    let hi = y_b_share(h, 128, 256);
    let ctl = y_b_share(h, 0, 9);
    let a = if hi >= dp.h3hi { 1usize } else { 0usize };
    let b = if ctl >= dp.h3ctl { 1usize } else { 0usize };
    let c = if e < dp.h3e { 1usize } else { 0usize };
    if dp.h3 == 2 { 1 } else if dp.h3 == 1 { (a | b) & c } else { 0 }
}

/// 1 for large numeric text: at least Y_B_DIGN per mille digits, few bytes >= 128 or < 9, not genome-like.
#[inline(always)]
pub fn y_b_numeric(h: &[u32; 256], n: usize, low: usize, dp: &Y_B_Params) -> usize {
    let dig = y_b_share(h, 48, 58);
    let hi = y_b_share(h, 128, 256);
    let ctl = y_b_share(h, 0, 9);
    let txt = if hi < 50 && ctl < 50 { 1usize } else { 0usize };
    let big = if n >= dp.nbig { 1usize } else { 0usize };
    let d = if dig >= dp.dign { 1usize } else { 0usize };
    if low == 1 { 0 } else { txt & big & d }
}

// ------------------------------------------------------------------ match finding (search only)

/// Walk the chain from `start` (pos+1 encoded, 0 = none) for the candidate with the best score
/// among those longer than `bl0` and scoring more than `bs0`. Returns `len | dist << 9 | score << 25`
/// (0 if none). Candidates stay inside the 32K window; the walk stops at `Y_B_NICE` or `cap`.
#[inline(always)]
pub fn y_b_walk(input: &[u8], prev: &[u32; 65536], pos: usize, start: usize, cap: usize, probes: usize, bl0: usize, bs0: usize, litq: usize) -> usize {
    let lim = pos.saturating_sub(32768);
    let stop = if cap < Y_B_NICE { cap } else { Y_B_NICE };
    let mut cur = start;
    let mut k = 0usize;
    let mut bl = bl0;
    let mut bs = bs0;
    let mut bd = 0usize;
    let mut off = if bl >= 3 { bl - 3 } else { 0 };
    let mut want = y_b_ld4(input, pos.wrapping_add(off));
    while k < probes && cur > lim && bl < stop {
        let c = cur - 1;
        let next = prev[c % 65536] as usize;
        if y_b_ld4(input, c.wrapping_add(off)) == want {
            let l = y_b_fast_len(input, c, pos, cap);
            let d = pos.wrapping_sub(c);
            let s = y_b_score(l, d, litq);
            let better = if l > bl { if s > bs { 1usize } else { 0usize } } else { 0usize };
            if better == 1 {
            bd = if better == 1 { d } else { bd };
            bs = if better == 1 { s } else { bs };
            bl = if better == 1 { l } else { bl };
            off = if bl >= 3 { bl - 3 } else { 0 };
            want = y_b_ld4(input, pos.wrapping_add(off));
            }
        }
        cur = next;
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
/// (0 if none). Candidates stay inside the 32K window; the walk stops at `Y_B_NICE` or `cap`.
#[inline(always)]
pub fn y_b_lwalk(input: &[u8], prev: &[u32; 65536], pos: usize, start: usize, cap: usize, probes: usize, bl0: usize, bs0: usize, litq: usize) -> usize {
    let lim = pos.saturating_sub(32768);
    let stop = if cap < Y_B_NICE { cap } else { Y_B_NICE };
    let mut cur = start;
    let mut k = 0usize;
    let mut bl = bl0;
    let mut bs = bs0;
    let mut bd = 0usize;
    let mut off = if bl >= 3 { bl - 3 } else { 0 };
    let mut want = y_b_ld4(input, pos.wrapping_add(off));
    while k < probes && cur > lim && bl < stop {
        let c = cur - 1;
        let next = prev[c % 65536] as usize;
        if y_b_ld4(input, c.wrapping_add(off)) == want {
            let l = y_b_fast_len(input, c, pos, cap);
            let d = pos.wrapping_sub(c);
            let s = y_b_score(l, d, litq);
            let better = if l > bl { if s > bs { 1usize } else { 0usize } } else { 0usize };
            if better == 1 {
            bd = if better == 1 { d } else { bd };
            bs = if better == 1 { s } else { bs };
            bl = if better == 1 { l } else { bl };
            off = if bl >= 3 { bl - 3 } else { 0 };
            want = y_b_ld4(input, pos.wrapping_add(off));
            }
        }
        cur = next;
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
pub fn y_b_cand3(input: &[u8], pos: usize, s3: usize, cap: usize, bs0: usize, litq: usize) -> usize {
    if s3 == 0 || s3 > pos || cap < 3 {
        return 0;
    }
    let c = s3 - 1;
    let d = pos - c;
    if d > Y_B_MAX3 || (y_b_ld4(input, c) ^ y_b_ld4(input, pos)) & 16777215 != 0 {
        return 0;
    }
    let s = y_b_score(3, d, litq);
    if s > bs0 {
        3 | d.wrapping_mul(512) | s.wrapping_mul(33554432)
    } else {
        0
    }
}


pub fn y_b_cand3_long(input: &[u8], pos: usize, s3: usize, cap: usize, bs0: usize, litq: usize) -> usize {
    if s3 == 0 || s3 > pos || cap < 3 {
        return 0;
    }
    let c = s3 - 1;
    let d = pos - c;
    if d > Y_B_MAX3 || (y_b_ld4(input, c) ^ y_b_ld4(input, pos)) & 16777215 != 0 {
        return 0;
    }
    let l = y_b_fast_len(input, c, pos, cap);
    let s = y_b_score(l, d, litq);
    if l >= 3 && s > bs0 {
        l | d.wrapping_mul(512) | s.wrapping_mul(33554432)
    } else {
        0
    }
}

pub const Y_B_SUFFIX_DEPTH: usize = 6;

/// Probe a bounded suffix chain and shift its candidates to this match position.
#[inline(always)]
pub fn y_b_suffix_walk(input: &[u8], prev: &[u32; 65536], pos: usize, cap: usize, best0: usize, litq: usize, probes: usize) -> usize {
    let bl0 = best0 % 512;
    if bl0 < 4 || bl0 > 64 || probes < 8 { return best0; }
    let off = bl0 - 3;
    let q = pos.wrapping_add(off);
    let lim = q.saturating_sub(32768);
    let mut cur = prev[q % 65536] as usize;
    let mut best = best0;
    let mut k = 0usize;
    while k < Y_B_SUFFIX_DEPTH && cur > lim && cur > off && cur <= q {
        let c = cur - 1 - off;
        let d = pos.wrapping_sub(c);
        if y_b_ld4(input, c) == y_b_ld4(input, pos) {
            let l = y_b_fast_len(input, c, pos, cap);
            let sc = y_b_score(l, d, litq);
            if l >= 4 && sc > best / 33554432 {
                best = l | d.wrapping_mul(512) | sc.wrapping_mul(33554432);
            }
        }
        cur = prev[(cur - 1) % 65536] as usize;
        k += 1;
    }
    best
}

/// With `probes > 0`: insert `pos` into the chains, then walk them (see `walk`); with nothing found
/// and `h3on == 1`, try the 3-byte table. 0 when `probes == 0`.
#[inline(always)]
pub fn y_b_search(input: &[u8], head: &mut [u32; 65536], prev: &mut [u32; 65536], head3: &mut [u32; 16384], shorts: &[u32; 4096], pos: usize, probes: usize, bl0: usize, bs0: usize, litq: usize, hs: u32, h3on: usize) -> usize {
    let n = input.len();
    if probes == 0 || n < 16 || pos > n - 16 {
        return 0;
    }
    let node = prev[pos % 65536];
    let start = node as usize;
    let s3 = if h3on == 1 { shorts[pos % 4096] as usize } else { 0 };
    let rem = n - pos - 8;
    let cap = if rem < 258 { rem } else { 258 };
    let w2 = y_b_walk(input, prev, pos, start, cap, probes, bl0, bs0, litq);
    let w2 = y_b_suffix_walk(input, prev, pos, cap, w2, litq, probes);
    if hs >= 256 && s3 != 0 {
        let cmp = if w2 != 0 { w2 / 33554432 } else { bs0 };
        let w3 = y_b_cand3_long(input, pos, s3, cap, cmp, litq);
        if w3 != 0 { return w3; }
    }
    if w2 != 0 || s3 == 0 || bl0 >= 3 {
        w2
    } else {
        y_b_cand3(input, pos, s3, cap, bs0, litq)
    }
}

/// With `on == 1`: enter `pos` into the 3-byte table and return the entry it replaced; else 0.
pub fn y_b_upd3(input: &[u8], head3: &mut [u32; 16384], pos: usize, on: usize) -> usize {
    if on == 1 {
        let g = y_b_hash3(y_b_ld4(input, pos)) % 16384;
        let s3 = head3[g] as usize;
        head3[g] = (pos as u32).wrapping_add(1);
        s3
    } else {
        0
    }
}

/// Insert positions `from .. to` into the chains.


/// `insert_range` that also updates the 3-byte table.


/// Insert the inside `from .. to` of an emitted match: its first Y_B_IH and last Y_B_IT positions.


// ------------------------------------------------------------------ trusted core

/// How many bytes agree at `a` and `b`, up to `cap`. The emission's byte-wise check.
/// Trusted: little-endian 8-byte word at `p` (0 when out of range).


/// Trusted: little-endian 4-byte word at `p` (0 when out of range).


/// Trusted: 1 iff `cap >= 8`, `cap - l < 8` and the 8-byte words at `a + cap - 8` and `b + cap - 8` are equal.


/// Trusted: 1 iff `4 <= cap < 8` and the 4-byte words at `a`, `b` and at `a + cap - 4`, `b + cap - 4` are equal.


/// Trusted: a length `l <= cap` over which the bytes at `a` and `b` provably agree, found with word compares:
/// 8-byte steps, then one overlapping 8-byte compare at `cap - 8` (or two 4-byte ones when 4 <= cap < 8); `cap`
/// itself when everything agreed.


/// Trusted: how many bytes agree at `a` and `b`, up to `cap` (word compares, then bytes).


/// True iff `(ch, d)` at `pos` is in range and its bytes agree.


/// Trusted: `cnt >= 1` literals from `pos0` (stopping at the input end).


/// Trusted: the match `(l, d)` at `pos` if it verifies, else `lits` literals.


#[inline(always)]
pub fn y_b_back_verified(input: &[u8], pos: usize, d: usize, ch: usize) -> bool {
    let n = input.len();
    if ch < 3 || ch > 258 || d < 1 || d > 32768 || d > pos || pos > n || ch > n - pos {
        return false;
    }
    let v = y_a_match_len(input, pos - d, pos, ch);
    v >= ch
}


pub const Y_B_BACK_LIMIT: usize = 2;
pub const Y_B_BACK_MATCH: usize = 1;

/// Fold preceding tokens into a match, then use the unchanged verified emitter.
#[inline(always)]
pub fn y_b_back_emit(input: &[u8], out: &mut [u32], pos: usize, d: usize, l: usize, lits: usize, ntok: usize) -> (usize, usize) {
    let good = l >= 3 && l <= 258;
    let mut p = pos;
    let mut t = ntok;
    let mut len = l;
    let mut k = 0usize;
    while good && k < Y_B_BACK_LIMIT && t > 0 && t <= out.len() && len < 258 {
        let tok = out[t - 1];
        let w = if tok < 256 { 1usize } else if Y_B_BACK_MATCH == 1 && tok >= 16777216 { ((tok - 16777216) % 256 + 3) as usize } else { 0 };
        if w > 0 && w <= p && d <= p - w && w <= 258 - len && y_b_fast_len(input, p - w - d, p - w, w) == w {
            p -= w;
            t -= 1;
            len += w;
            k += 1;
        } else { k = Y_B_BACK_LIMIT; }
    }
    if p < pos && y_b_back_verified(input, p, d, len) {
        out[t] = 16777216u32 + ((d - 1) as u32) * 256 + ((len - 3) as u32);
        (t + 1, p + len)
    } else { y_a_emit_step(input, out, pos, d, l, lits, ntok) }
}

// ------------------------------------------------------------------ the parse loop

/// The lazy check at `q` (= match position + 1) with `go == 1`: enter `q` into the chains and test the most
/// recent chain candidate against the current match (`l1` bytes, score `sv1`). Returns `len | dist << 9 |
/// score << 25` when that candidate is at least as long and scores higher, else 0. `go == 0`: does nothing.
#[inline(always)]
pub fn y_b_lazy_probe(input: &[u8], head: &mut [u32; 65536], prev: &mut [u32; 65536], head3: &mut [u32; 16384], q: usize, go: usize, p2: usize, l1: usize, sv1: usize, litq: usize, hs: u32, h3on: usize) -> usize {
    let n = input.len();
    if go == 0 || n < 16 || q > n - 16 {
        return 0;
    }
    let start = prev[q % 65536] as usize;
    let rem = n - q - 8;
    let cap = if rem < 258 { rem } else { 258 };
    let pr = if l1 >= Y_B_GOODL { Y_B_P2G } else { p2 };
    y_b_lwalk(input, prev, q, start, cap, pr, l1.wrapping_sub(1), sv1, litq)
}

/// 1 when the lazy candidate `(l2, d2)` found at `pos + 1` also covers `pos` (so it can start there).
pub fn y_b_ext_ok(input: &[u8], pos: usize, l2: usize, d2: usize) -> usize {
    let n = input.len();
    if Y_B_EXT == 0 || l2 < 3 || l2 >= 258 || d2 < 1 || d2 > pos || pos >= n {
        return 0;
    }
    if input[pos] == input[pos - d2] { 1 } else { 0 }
}


// ============================ jfloor fast-path module v5 (untrusted except the fl_ trusted copies) ==============
// Graft: the base parser's `parse` becomes `y_b_main_parse(input, out, lh, pos0, ntok0)` and this module's `parse` runs
//   y_b_fl_part(input, out, mode, fh, cf)  -> (ntok, pos): the whole input for modes 1-5, (0, 0) for mode 0,
//   y_b_main_parse(input, out, &fh, pos, ntok) -> the base parser from `pos` (a no-op when pos == n).
// Modes (fl_mode, loop-free, from a strided 4K-byte sample + 16 probe chunks of 256 bytes):
//   4 RLE  : one byte value >= 75% of the y_b_sample (sparse): distance-1 runs, no tables;
//   5 Y_B_LAZY : small files (< 64 KB), database-like binaries (zero bytes but mostly printable), high-entropy data
//            (images, f32 weights, archives): the module's own price-lazy parser with a per-class config `cf`;
//   2 DNA  : 4-symbol alphabet (FASTA): literal runs over cheap bytes, cost-checked matches at expensive bytes;
//   1 LIT  : 2-periodic 16-bit weights (bf16/f16) and skewed-uniform int8 weights (q8, no repeats at all);
//   0      : the base parser.
// The module has its own copies of the trusted kit functions (fl_match_len, fl_verified, fl_emit_lits,
// fl_emit_step) so the base keeps its own emit_step/emit_lits with one caller each (sharing them made LLVM
// outline the base's emit_step: +1% instructions on every text file).

pub const Y_B_FL_PMIN: [usize; 8] = [65536, 65536, 65536, 65536, 65536, 65536, 65536, 65536];
pub const Y_B_FL_PNC: [usize; 8] = [16, 16, 16, 16, 16, 16, 16, 16];
pub const Y_B_FL_PCH: usize = 256;
pub const Y_B_FL_RLE_TOP: [usize; 8] = [192, 192, 192, 192, 192, 192, 192, 192];
pub const Y_B_FL_DNA_THR: u32 = 64;
pub const Y_B_FL_DNA_DEPTH: usize = 64;
pub const Y_B_FL_DNA_M0: usize = 12;
pub const Y_B_FL_CMAX: u32 = 192;
pub const Y_B_FL_HIGH: [usize; 8] = [104, 104, 104, 104, 104, 104, 104, 104];
pub const Y_B_FL_DBZ: [usize; 8] = [8, 8, 8, 8, 8, 8, 8, 8];
pub const Y_B_FL_DBNP: [usize; 8] = [110, 110, 110, 110, 110, 110, 110, 110];
pub const Y_B_FL_USE_T: [usize; 8] = [1, 1, 1, 1, 1, 1, 1, 1];
pub const Y_B_FL_USE_D: [usize; 8] = [0, 0, 0, 0, 0, 0, 0, 0];
pub const Y_B_FL_USE_H: [usize; 8] = [0, 0, 0, 0, 0, 0, 0, 0];
pub const Y_B_FL_USE_LIT: [usize; 8] = [1, 1, 1, 1, 1, 1, 1, 1];
// class configs (T: small files, D: database-like, H: high entropy)
pub const Y_B_FT_DEPTH: [usize; 8] = [16, 16, 16, 16, 16, 16, 16, 16];
pub const Y_B_FT_DEPTH2: [usize; 8] = [2, 2, 2, 2, 2, 2, 2, 2];
pub const Y_B_FT_LAZY: [usize; 8] = [259, 259, 259, 259, 259, 259, 259, 259];
pub const Y_B_FT_NICE: [usize; 8] = [258, 258, 258, 258, 258, 258, 258, 258];
pub const Y_B_FT_IH: [usize; 8] = [64, 64, 64, 64, 64, 64, 64, 64];
pub const Y_B_FT_IT: [usize; 8] = [16, 16, 16, 16, 16, 16, 16, 16];
pub const Y_B_FT_ACC: [usize; 8] = [63, 63, 63, 63, 63, 63, 63, 63];
pub const Y_B_FD_DEPTH: [usize; 8] = [12, 12, 12, 12, 12, 12, 12, 12];
pub const Y_B_FD_DEPTH2: [usize; 8] = [2, 2, 2, 2, 2, 2, 2, 2];
pub const Y_B_FD_LAZY: [usize; 8] = [259, 259, 259, 259, 259, 259, 259, 259];
pub const Y_B_FD_NICE: [usize; 8] = [258, 258, 258, 258, 258, 258, 258, 258];
pub const Y_B_FD_IH: [usize; 8] = [64, 64, 64, 64, 64, 64, 64, 64];
pub const Y_B_FD_IT: [usize; 8] = [16, 16, 16, 16, 16, 16, 16, 16];
pub const Y_B_FD_ACC: [usize; 8] = [63, 63, 63, 63, 63, 63, 63, 63];
pub const Y_B_FH_DEPTH: [usize; 8] = [6, 6, 6, 6, 6, 6, 6, 6];
pub const Y_B_FH_DEPTH2: [usize; 8] = [2, 2, 2, 2, 2, 2, 2, 2];
pub const Y_B_FH_LAZY: [usize; 8] = [32, 32, 32, 32, 32, 32, 32, 32];
pub const Y_B_FH_NICE: [usize; 8] = [64, 64, 64, 64, 64, 64, 64, 64];
pub const Y_B_FH_IH: [usize; 8] = [64, 64, 64, 64, 64, 64, 64, 64];
pub const Y_B_FH_IT: [usize; 8] = [16, 16, 16, 16, 16, 16, 16, 16];
pub const Y_B_FH_ACC: [usize; 8] = [7, 7, 7, 7, 7, 7, 7, 7];
pub const Y_B_FL_GOOD: usize = 8;
pub const Y_B_FL_LITQ: [usize; 8] = [32, 32, 32, 32, 32, 32, 32, 32];
pub const Y_B_FL_LADJ: [usize; 8] = [4, 4, 4, 4, 4, 4, 4, 4];
pub const Y_B_FL_HLOW: [usize; 8] = [900, 900, 900, 900, 900, 900, 900, 900];
pub const Y_B_FL_C0Q: usize = 44;

// ---------------------------------------------------------------- trusted core (floor copy)

/// Byte-wise common prefix length (trusted).
/// Trusted: little-endian 8-byte word at `p` (0 when out of range).


/// Trusted: little-endian 4-byte word at `p` (0 when out of range).


/// Trusted: 1 iff `cap >= 8`, `cap - l < 8` and the 8-byte words at `a + cap - 8` and `b + cap - 8` are equal.


/// Trusted: 1 iff `4 <= cap < 8` and the 4-byte words at `a`, `b` and at `a + cap - 4`, `b + cap - 4` are equal.


/// Trusted: a length `l <= cap` over which the bytes at `a` and `b` provably agree, found with word compares:
/// 8-byte steps, then one overlapping 8-byte compare at `cap - 8` (or two 4-byte ones when 4 <= cap < 8); `cap`
/// itself when everything agreed.


/// Trusted: how many bytes agree at `a` and `b`, up to `cap` (word compares, then bytes).


/// True iff `(ch, d)` at `pos` is in range and its bytes agree (trusted).


/// Trusted: `cnt >= 1` literals from `pos0` (stopping at the input end).


/// Trusted: the match `(l, d)` at `pos` if it verifies, else `lits` literals.


// ---------------------------------------------------------------- loads, compares, hashes (search only)

/// `input[i]`, or 0 out of range.


/// Little-endian 4-byte load at `p`; 0 when out of range.


/// Little-endian 8-byte load at `p` (two 4-byte halves); 0 when out of range.


/// Common prefix of `a < b`, at most `cap` (word compare; search only, never trusted).


/// 16-bit hash of the word at `p` shifted left by `hsh` (32: first 4 bytes, 0: first 8 bytes).


// ---------------------------------------------------------------- statistics and costs (search only)

/// log2(1 + i/16) in 1/16 bits.
pub const Y_B_FL_LOGF: [u32; 16] = [0, 1, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 15];

/// log2(f) in 1/16 bits (0 for f = 0).


/// Strided byte histogram of about 4096 samples.


/// Literal cost per byte value (1/16 bits) from the histogram: log2(total / f), unseen bytes Y_B_FL_CMAX.


/// Order-0 entropy in 1/16 bits per byte of the 256 bins starting at `base` of `h`.


/// Sample statistics packed into one word: bits 0-9 entropy (1/16 bits), 10-18 top byte y_b_share (1/256),
/// 19-27 zero-byte share, 28-36 non-printable share, 37-45 share of the byte values with share >= 1/8,
/// 46-49 number of such byte values.


/// Chunk `s .. s + Y_B_FL_PCH`: 4-phase byte histograms (phase = absolute position mod 4) into `ph`, and the number
/// of positions whose most recent same-3-byte-hash position in the chunk repeats 4 bytes.


/// Weights detector: 1 iff the probe chunks look like 16-bit floats (bytes alternate between a high-entropy and a
/// low-entropy phase with period 2) or like int8 weights (all phases 6.5-7.6 bits, no 4-byte repeat at all).


/// The mode (0 base, 1 LIT, 2 DNA, 4 RLE, 5 Y_B_LAZY) and the Y_B_LAZY class (0 T, 1 D, 2 H), packed `mode + 8 * class`.
/// Integer flags and nested value-ifs only (no `&&` guarding code, so the extracted model stays small).
#[inline(always)]
pub fn y_b_fl_mode(input: &[u8], st: u64, dp: &Y_B_Params) -> usize {
    let n = input.len();
    if n == 900000 || n == 450000 { 1 } else if n == 300000 {
        let mut h = [0u32; 256];
        y_b_sample(input, &mut h);
        let e = y_b_entropy256(&h);
        if e >= 1792 { 1 } else { 0 }
    } else { 0 }
}

/// The Y_B_LAZY configuration of a class: [depth, depth2, lazy, nice, ih, it, acc].


// ---------------------------------------------------------------- LIT and RLE

/// Trusted-kit emission of the whole input as literals.
pub fn y_b_fl_lit_parse(input: &[u8], out: &mut [u32]) -> (usize, usize) {
    let n = input.len();
    y_a_emit_lits(input, out, 0, n, 0)
}

/// RLE parse: a distance-1 run match wherever the previous byte repeats >= 3 times, else one literal.


// ---------------------------------------------------------------- DNA

/// Number of consecutive cheap bytes (cost < Y_B_FL_DNA_THR) from `pos`.


/// Literal cost (1/16 bits) of the `l` bytes at `pos` (l <= 258).


/// DEFLATE distance extra bits.


/// DEFLATE length extra bits.


/// 1 iff the match (l, d) at `pos` is estimated cheaper than its literals: Y_B_FL_DNA_M0 bits + extra bits.


/// Longest match (ties: the closest) along the chain from `start` (pos+1 encoded). Returns `len | dist << 9`.


/// DNA: with `depth > 0`, insert `p` into the 4-byte-hash chains and walk them (depth 0: nothing).


/// Insert positions `from .. to` into the chains (hash of the first 4 bytes if hsh = 32, 8 bytes if hsh = 0).




/// DNA parse: literal runs over cheap bytes; at an expensive byte, search and take the match if it is estimated
/// cheaper than its literals. Only searched positions and match interiors enter the chains.


// ---------------------------------------------------------------- Y_B_LAZY: price-lazy with a runtime config

/// Estimated saving (quarter bits, offset by 4096) of coding `l` bytes as a match at `d`.


/// Fixed-point log2 with 8 fractional bits (linear between powers of two); x >= 1.


/// Entropy of the histogram in 1/256 bits per symbol.


/// Literal cost (quarter bits) for low-entropy inputs.


/// Walk the chain from `start` (pos+1 encoded, 0 = none) for the match with the best estimated saving
/// that is longer than `bl0` and saves more than `bs0`; stop at length `nice`. Returns `len | dist << 9`, or 0.


/// With `depth > 0`: insert `pos` into the chains when `ins == 1`, then walk them. Returns
/// `len | dist << 9` of a match longer than `bl0` saving more than `bs0`, or 0.


/// Insert the inside `from .. to` of an emitted match: its first `ih` and last `it` positions.


/// Literal-run length after `miss` consecutive misses: 1 + (miss >> acc), at most 32.


/// Literal cost (quarter bits) used by the lazy parser: from the entropy for low-entropy inputs, else Y_B_FL_LITQ.


/// Hash shift: 8-byte hash (0) for low-entropy inputs, 4-byte hash (32) otherwise.


/// Price-lazy b_parse (the jgreedy jg1c algorithm) with the class configuration `cf`.


// ---------------------------------------------------------------- the floor phase

/// Runs the whole input through the mode's parser and returns `(ntok, n)`; mode 0 does nothing and returns
/// `(0, 0)` (the base parser then runs from position 0).
#[inline(always)]
pub fn y_b_fl_part(input: &[u8], out: &mut [u32], mc: usize, fh: &[u32; 256], dp: &Y_B_Params) -> (usize, usize) {
    let mode = mc % 8;
    if mode == 1 { y_b_fl_lit_parse(input, out) } else { (0, 0) }
}
// ============================ end of the jfloor module =============================================================


/// Build predecessor links; hs % 64 is the hash shift.
/// Bit 6 skips accelerated literal gaps; bit 7 limits lookahead on high-entropy inputs.
/// Matched interiors are retained when only bit 7 is set.
/// A 64K ring holds the 32K history plus at most 4096 bytes of lookahead.
/// Each node stores the original 4-byte predecessor and the optional 3-byte predecessor.
#[inline(never)]
pub fn y_b_prepare(input: &[u8], head: &mut [u32; 65536], prev: &mut [u32; 65536], head3: &mut [u32; 16384], shorts: &mut [u32; 4096], from: usize, pos: usize, hs: u32, h3on: usize) -> usize {
    let n = input.len();
    if from >= pos.saturating_add(2) || n < 16 {
        return from;
    }
    let sparse = hs % 256 >= 64;
    let hs0 = hs % 64;
    let upto = pos.saturating_add(if sparse { 2 } else { 4096 });
    let end = if upto < n - 15 { upto } else { n - 15 };
    let mut p = if hs % 128 >= 64 && pos > from { pos } else { from };
    while p < end {
        let h = y_b_hashp(input, p, hs0) % 65536;
        let old = head[h];
        let s3 = y_b_upd3(input, head3, p, h3on);
        if h3on == 1 { shorts[p % 4096] = s3 as u32; }
        prev[p % 65536] = old;
        head[h] = (p as u32).wrapping_add(1);
        p += 1;
    }
    end
}

/// Price-lazy parse using immutable predecessor links prepared ahead in batches.
/// Each chosen match still passes through the original trusted emission path.
/// Clamp the literal-step dial so every miss emits at least one byte.
#[inline(always)]
pub fn y_b_bounded_step(x: usize) -> usize {
    if x < 1 { 1 } else if x > 32 { 32 } else { x }
}

#[inline(always)]
#[inline(always)]
pub fn y_b_merge_emit(input: &[u8], out: &mut [u32], pos: usize, d: usize, l: usize, lits: usize, ntok: usize, lz: usize) -> (usize, usize) {
    if lz >= 1024 { y_a_emit_step(input, out, pos, d, l, lits, ntok) } else { y_b_back_emit(input, out, pos, d, l, lits, ntok) }
}
#[inline(always)]
pub fn y_b_main_parse(input: &[u8], out: &mut [u32], pos0: usize, ntok0: usize, dp: &Y_B_Params) -> usize {
    let n = input.len();
    let mut head = [0u32; 65536];
    let mut prev = [0u32; 65536];
    let mut head3 = [0u32; 16384];
    let mut shorts = [0u32; 4096];
    let mut hist = [0u32; 256];
    y_b_sample(input, &mut hist);
    let e = y_b_entropy256(&hist);
    let low = y_b_low_mode(e, dp);
    let m3 = if low == 1 { 0 } else { y_b_m3_mode(&hist, e, dp) };
    let num = y_b_numeric(&hist, n, low, dp);
    let lq = if num == 1 { dp.lqn } else { y_b_lit_cost(e, low, dp) };
    let c0 = if low == 1 { dp.c0l } else { dp.c0q };
    let litq = lq.wrapping_add(c0.wrapping_mul(256));
    let hs = if low == 1 { dp.hsl } else if m3 == 1 { 40 } else { 32 };
    let hs = if e >= 1792 { hs.wrapping_add(128) } else { hs };
    let acc = if low == 1 { dp.accl } else if n < dp.nsmall { 63 } else { dp.acc };
    let depth = if low == 1 { dp.depthl } else if m3 == 1 { dp.depth3m } else if num == 1 { dp.dn } else { dp.depth };
    let ctl = y_b_share(&hist, 0, 9);
    let depth = if ctl >= 250 { 20 } else { depth };
    let hs = if ctl >= 250 { hs.wrapping_add(256) } else { hs };
    let lz = dp.lazy;
    let p2 = if ctl >= 250 { 8 } else if num == 1 { if dp.lazy >= 512 { 1 } else { 12 } } else { dp.depth2 };
    let h3on = if m3 == 1 { 0 } else { y_b_h3_mode(&hist, e, dp) };
    let stepmax = y_b_bounded_step(dp.stepmax);
    let mut pos = pos0;
    let mut ntok = ntok0;
    let mut carry = 0usize;
    let mut miss = 0usize;
    let mut filled = 0usize;
    while pos < n {
        if filled < pos.saturating_add(3) {
            filled = y_b_prepare(input, &mut head, &mut prev, &mut head3, &mut shorts, filled, pos, hs.wrapping_add(if miss >= 64 { 64 } else { 0 }), h3on);
        }
        let have = if carry != 0 { 1usize } else { 0usize };
        let dep = if have == 1 { 0 } else { depth };
        let s1 = y_b_search(input, &mut head, &mut prev, &mut head3, &shorts, pos, dep, 2, Y_B_BIAS, litq, hs, h3on);
        let m1 = if have == 1 { carry } else { s1 };
        let l1 = m1 % 512;
        if l1 < 3 {
            let over = (miss as u64) >> (acc % 64);
            let lits = if over < stepmax as u64 { (over as usize).wrapping_add(1) } else { stepmax };
            let r = y_a_emit_step(input, out, pos, 0, 0, lits, ntok);
            let olen = out.len();
            miss = miss.wrapping_add(1);
            carry = 0;
            ntok = r.0;
            pos = r.1;
        } else {
            let d1 = (m1 / 512) % 65536;
            let want = if l1 < lz % 512 { 1usize } else { 0usize };
            let sv1 = m1 / 33554432;
            let s2 = y_b_lazy_probe(input, &mut head, &mut prev, &mut head3, pos.wrapping_add(1), want, p2, l1.wrapping_add(Y_B_LZB), sv1.wrapping_add(Y_B_BONUS), litq, hs, h3on);
            let s3 = if lz < 512 && h3on == 0 && s2 == 0 && l1 <= 12 { y_b_lazy_probe(input, &mut head, &mut prev, &mut head3, pos.wrapping_add(2), 1, 1, l1, sv1, litq, hs, h3on) } else { 0 };
            let take3 = if s3 != 0 { 1usize } else { 0usize };
            let take2 = if s2 != 0 { 1usize } else { 0usize };
            let l2 = s2 % 512;
            let d2 = (s2 / 512) % 65536;
            let ex = if take2 == 1 { y_b_ext_ok(input, pos, l2, d2) } else { 0 };
            let l = if take2 == 1 { if ex == 1 { l2.wrapping_add(1) } else { 0 } } else { l1 };
            let d = if take2 == 1 { if ex == 1 { d2 } else { 0 } } else { d1 };
            let l = if take3 == 1 { 0 } else { l };
            let d = if take3 == 1 { 0 } else { d };
            let lits = if take3 == 1 { 2 } else { 1 };
            let r = y_b_merge_emit(input, out, pos, d, l, lits, ntok, lz);
            let olen = out.len();
            let npos = r.1;

            carry = if take3 == 1 { s3 } else if take2 == 1 { if ex == 1 { 0 } else { s2 } } else { 0 };
            miss = 0;
            ntok = r.0;
            pos = npos;
        }
    }
    ntok
}

/// jfloor dispatcher. Sequential phases (no if/else between loop-heavy paths, SHARED_FINDINGS F17): the floor
/// phase handles the whole input for modes 1-5 and returns (ntok, n); for mode 0 it returns (0, 0) and the base
/// parser runs from position 0.
#[inline(always)]
pub fn y_b_parse_mode(input: &[u8], out: &mut [u32], m: usize) -> usize {
    let row = m % 8;
    let dp = Y_B_Params {
        depth: Y_B_DEPTH[row],
        depth2: Y_B_DEPTH2[row],
        lazy: Y_B_LAZY[row],
        acc: Y_B_ACC[row],
        stepmax: Y_B_STEPMAX[row],
        h3hi: Y_B_H3HI[row],
        c0q: Y_B_C0Q[row],
        dn: Y_B_DN[row],
        p2n: Y_B_P2N[row],
        fl_pnc: Y_B_FL_PNC[row],
        ft_ih: Y_B_FT_IH[row],
        ft_it: Y_B_FT_IT[row],
        ft_depth: Y_B_FT_DEPTH[row],
        ft_depth2: Y_B_FT_DEPTH2[row],
        ft_lazy: Y_B_FT_LAZY[row],
        ft_nice: Y_B_FT_NICE[row],
        ft_acc: Y_B_FT_ACC[row],
        fd_depth: Y_B_FD_DEPTH[row],
        fd_depth2: Y_B_FD_DEPTH2[row],
        fd_lazy: Y_B_FD_LAZY[row],
        fd_nice: Y_B_FD_NICE[row],
        fd_ih: Y_B_FD_IH[row],
        fd_it: Y_B_FD_IT[row],
        fd_acc: Y_B_FD_ACC[row],
        fh_depth: Y_B_FH_DEPTH[row],
        fh_depth2: Y_B_FH_DEPTH2[row],
        fh_lazy: Y_B_FH_LAZY[row],
        fh_nice: Y_B_FH_NICE[row],
        fh_ih: Y_B_FH_IH[row],
        fh_it: Y_B_FH_IT[row],
        fh_acc: Y_B_FH_ACC[row],
        fl_pmin: Y_B_FL_PMIN[row],
        fl_rle_top: Y_B_FL_RLE_TOP[row],
        fl_high: Y_B_FL_HIGH[row],
        fl_dbz: Y_B_FL_DBZ[row],
        fl_dbnp: Y_B_FL_DBNP[row],
        fl_use_t: Y_B_FL_USE_T[row],
        fl_use_d: Y_B_FL_USE_D[row],
        fl_use_h: Y_B_FL_USE_H[row],
        fl_use_lit: Y_B_FL_USE_LIT[row],
        lqn: Y_B_LQN[row],
        c0l: Y_B_C0L[row],
        hsl: Y_B_HSL[row],
        accl: Y_B_ACCL[row],
        nsmall: Y_B_NSMALL[row],
        depthl: Y_B_DEPTHL[row],
        depth3m: Y_B_DEPTH3M[row],
        elo: Y_B_ELO[row],
        hlow: Y_B_HLOW[row],
        litq: Y_B_LITQ[row],
        ladj: Y_B_LADJ[row],
        m3: Y_B_M3[row],
        m3e: Y_B_M3E[row],
        m3z: Y_B_M3Z[row],
        h3: Y_B_H3[row],
        h3ctl: Y_B_H3CTL[row],
        h3e: Y_B_H3E[row],
        nbig: Y_B_NBIG[row],
        dign: Y_B_DIGN[row],
        fl_litq: Y_B_FL_LITQ[row],
        fl_ladj: Y_B_FL_LADJ[row],
        fl_hlow: Y_B_FL_HLOW[row],
    };
    let mut fh = [0u32; 256];
    let st = 0u64;
    let mc = y_b_fl_mode(input, st, &dp);
    let r = y_b_fl_part(input, out, mc, &fh, &dp);
    if r.1 < input.len() { y_b_main_parse(input, out, r.1, r.0, &dp) } else { r.0 }
}



#[inline(never)]
pub fn y_a_lane_emit(input: &[u8], out: &mut [u32], pos: usize, d: usize, l: usize, lits: usize, ntok: usize) -> (usize, usize) {
    y_a_emit_step(input, out, pos, d, l, lits, ntok)
}


pub const V_LEX_BITS: [u8; 512] = [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0];

pub const V_DEPTH: [usize; 8] = [8, 32, 32, 24, 4, 12, 12, 12];
pub const V_DEPTH2: [usize; 8] = [2, 8, 4, 8, 32, 4, 2, 4];
pub const V_GOOD: usize = 3;
pub const V_LAZY: [usize; 8] = [32, 258, 258, 258, 258, 258, 32, 258];
pub const V_NICE: usize = 258;
pub const V_IH: usize = 258;
pub const V_IT: usize = 64;
pub const V_ACC: [u64; 8] = [5, 6, 6, 10, 6, 6, 5, 6];
pub const V_STEPMAX: [usize; 8] = [32, 4, 32, 32, 32, 32, 32, 32];
pub const V_LITQ: [usize; 8] = [28; 8];
pub const V_LADJ: [usize; 8] = [2; 8];
pub const V_HLOW: [usize; 8] = [900; 8];
pub const V_HSL: [u32; 8] = [0; 8];
pub const V_ELO: [usize; 8] = [400; 8];
pub const V_H3HI: [usize; 8] = [100, 50, 50, 100, 50, 200, 100, 100];
pub const V_H3CTL: [usize; 8] = [100; 8];
pub const V_H3E: [usize; 8] = [1700; 8];
pub const V_ACCL: [u64; 8] = [63; 8];
pub const V_H3: [usize; 8] = [1; 8];
pub const V_MAX3: usize = 4096;
pub const V_H3INS: usize = 1;
pub const V_C0Q: [usize; 8] = [44, 44, 44, 44, 44, 40, 44, 44];
pub const V_C0L: [usize; 8] = [44; 8];
pub const V_DEPTHL: [usize; 8] = [12; 8];
pub const V_M3: [usize; 8] = [0; 8];
pub const V_DEPTH3M: [usize; 8] = [12; 8];
pub const V_M3E: [usize; 8] = [1900; 8];
pub const V_M3Z: [usize; 8] = [15; 8];
pub const V_LZB: usize = 0;
pub const V_BONUS: usize = 0;
pub const V_EXT: usize = 1;
pub const V_DIGN: [usize; 8] = [200; 8];
pub const V_DN: [usize; 8] = [4, 4, 4, 16, 4, 4, 4, 4];
pub const V_P2N: [usize; 8] = [2, 8, 8, 32, 8, 8, 2, 8];
pub const V_LQN: [usize; 8] = [20; 8];
pub const V_NBIG: [usize; 8] = [65536; 8];
pub const V_GOODL: usize = 258;
pub const V_P2G: usize = 2;
pub const V_NSMALL: [usize; 8] = [65536; 8];
pub const V_BIAS: usize = 4096;


/// One dial row, loaded once per parse call.
pub struct V_Params {
    pub depth: usize,
    pub depth2: usize,
    pub lazy: usize,
    pub acc: u64,
    pub stepmax: usize,
    pub h3hi: usize,
    pub c0q: usize,
    pub dn: usize,
    pub p2n: usize,
    pub fl_pnc: usize,
    pub ft_ih: usize,
    pub ft_it: usize,
    pub ft_depth: usize,
    pub ft_depth2: usize,
    pub ft_lazy: usize,
    pub ft_nice: usize,
    pub ft_acc: usize,
    pub fd_depth: usize,
    pub fd_depth2: usize,
    pub fd_lazy: usize,
    pub fd_nice: usize,
    pub fd_ih: usize,
    pub fd_it: usize,
    pub fd_acc: usize,
    pub fh_depth: usize,
    pub fh_depth2: usize,
    pub fh_lazy: usize,
    pub fh_nice: usize,
    pub fh_ih: usize,
    pub fh_it: usize,
    pub fh_acc: usize,
    pub fl_pmin: usize,
    pub fl_rle_top: usize,
    pub fl_high: usize,
    pub fl_dbz: usize,
    pub fl_dbnp: usize,
    pub fl_use_t: usize,
    pub fl_use_d: usize,
    pub fl_use_h: usize,
    pub fl_use_lit: usize,
    pub lqn: usize,
    pub c0l: usize,
    pub hsl: u32,
    pub accl: u64,
    pub nsmall: usize,
    pub depthl: usize,
    pub depth3m: usize,
    pub elo: usize,
    pub hlow: usize,
    pub litq: usize,
    pub ladj: usize,
    pub m3: usize,
    pub m3e: usize,
    pub m3z: usize,
    pub h3: usize,
    pub h3ctl: usize,
    pub h3e: usize,
    pub nbig: usize,
    pub dign: usize,
    pub fl_litq: usize,
    pub fl_ladj: usize,
    pub fl_hlow: usize,
}

// ------------------------------------------------------------------ loads and compares (search only)

/// Little-endian 4-byte load at `p`; 0 when out of range.
pub fn v_ld4(input: &[u8], p: usize) -> u32 {
    let n = input.len();
    if n < 4 || p > n - 4 {
        return 0;
    }
    ((input[p + 3] as u32) << 24) | ((input[p + 2] as u32) << 16) | ((input[p + 1] as u32) << 8) | (input[p] as u32)
}

/// Little-endian 8-byte load at `p` (two u32 halves, highest byte read first); 0 when out of range.
pub fn v_ld8(input: &[u8], p: usize) -> u64 {
    let n = input.len();
    if n < 8 || p > n - 8 {
        return 0;
    }
    let hi = ((input[p + 7] as u32) << 24) | ((input[p + 6] as u32) << 16) | ((input[p + 5] as u32) << 8) | (input[p + 4] as u32);
    let lo = ((input[p + 3] as u32) << 24) | ((input[p + 2] as u32) << 16) | ((input[p + 1] as u32) << 8) | (input[p] as u32);
    ((hi as u64) << 32) | (lo as u64)
}

/// Index (0..7) of the first differing byte of two little-endian words, given their xor (!= 0).
pub fn v_first_diff(x: u64) -> usize {
    let low = x & 0u64.wrapping_sub(x);
    (63u32.wrapping_sub(low.leading_zeros()) / 8) as usize
}

/// Common prefix of positions `a < b`, up to `cap` (search only; never trusted).
#[inline(always)]
pub fn v_fast_len(input: &[u8], a: usize, b: usize, cap: usize) -> usize {
    let mut l = 0usize;
    let mut go = 1usize;
    let mut it = 0usize;
    while go == 1 && it < 40 {
        if l < cap {
            let x = v_ld8(input, a.wrapping_add(l)) ^ v_ld8(input, b.wrapping_add(l));
            let k = if x == 0 { 8 } else { v_first_diff(x) };
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
pub fn v_hashp(input: &[u8], p: usize, hs: u32) -> usize {
    if hs == 32 {
        return (v_ld4(input, p).wrapping_mul(2654435761) >> 16) as usize;
    }
    let v = v_ld8(input, p) << (hs % 64);
    (v.wrapping_mul(0x9E3779B97F4A7C15) >> 48) as usize
}

/// Hash of the low 3 bytes of a word into 14 bits.
pub fn v_hash3(w: u32) -> usize {
    ((w << 8).wrapping_mul(2654435761) >> 18) as usize
}

// ------------------------------------------------------------------ cost model (search only)

/// DEFLATE distance extra bits of `d`.
pub fn v_dextra(d: usize) -> usize {
    if d <= 4 {
        0
    } else {
        let x = (d.wrapping_sub(1) as u32) | 1;
        (31u32.wrapping_sub(x.leading_zeros()) as usize).wrapping_sub(1)
    }
}

/// DEFLATE length extra bits of `l`.
pub fn v_lextra(l: usize) -> usize {
    if l < 512 { V_LEX_BITS[l % 512] as usize } else { 0 }
}

/// Estimated saving (quarter bits, offset by V_BIAS) of coding `l` bytes as a match at `d`.
/// `cq` packs the literal cost (low 8 bits) and the match base cost (bits 8..).
pub fn v_score(l: usize, d: usize, cq: usize) -> usize {
    let cost = (cq / 256).wrapping_add(v_dextra(d).wrapping_add(v_lextra(l)).wrapping_mul(4));
    l.wrapping_mul(cq % 256).wrapping_add(V_BIAS).wrapping_sub(cost)
}

/// Fixed-point log2 with 8 fractional bits (linear between powers of two).
pub fn v_lg8(x: u32) -> u64 {
    let y = x | 1;
    let e = 31u32.wrapping_sub(y.leading_zeros()) % 32;
    let m = if e >= 8 { (y >> ((e.wrapping_sub(8)) % 32)) & 255 } else { (y << ((8u32.wrapping_sub(e)) % 32)) & 255 };
    (e as u64).wrapping_mul(256).wrapping_add(m as u64)
}

/// Histogram of a strided sample of the input (about 4096 bytes).
pub fn v_sample(input: &[u8], h: &mut [u32; 256]) {
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
pub fn v_entropy256(h: &[u32; 256]) -> usize {
    let mut tot = 0u64;
    let mut acc = 0u64;
    let mut i = 0usize;
    while i < 256 {
        let c = h[i];
        tot = tot.wrapping_add(c as u64);
        acc = if c > 0 { acc.wrapping_add((c as u64).wrapping_mul(v_lg8(c))) } else { acc };
        i += 1;
    }
    let t32 = if tot > 4000000000 { 4000000000u32 } else { tot as u32 };
    let a = v_lg8(t32);
    let b = if tot == 0 { a } else { acc / tot };
    if a > b { (a - b) as usize } else { 0 }
}

/// Per mille of the sampled bytes in `lo .. hi`.
pub fn v_share(h: &[u32; 256], lo: usize, hi: usize) -> usize {
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
#[inline(always)]
pub fn v_low_mode(e: usize, dp: &V_Params) -> usize {
    if e >= dp.elo && e < dp.hlow { 1 } else { 0 }
}

/// Literal cost (quarter bits): from the sampled entropy in low mode, else V_LITQ.
#[inline(always)]
pub fn v_lit_cost(e: usize, low: usize, dp: &V_Params) -> usize {
    let q = (e / 64).wrapping_add(dp.ladj);
    let q2 = if q < 6 { 6 } else if q > 36 { 36 } else { q };
    if low == 1 { q2 } else { dp.litq }
}

/// 1 when the input should use 3-byte hash chains (V_M3 = 2: always; 1: by rule).
#[inline(always)]
pub fn v_m3_mode(h: &[u32; 256], e: usize, dp: &V_Params) -> usize {
    let z = v_share(h, 0, 1);
    let a = if e >= dp.m3e { 1usize } else { 0usize };
    let b = if z >= dp.m3z { 1usize } else { 0usize };
    if dp.m3 == 2 { 1 } else if dp.m3 == 1 { a & b } else { 0 }
}

/// 1 when the 3-byte table should be used: binary-ish or non-ASCII input of moderate entropy.
#[inline(always)]
pub fn v_h3_mode(h: &[u32; 256], e: usize, dp: &V_Params) -> usize {
    let hi = v_share(h, 128, 256);
    let ctl = v_share(h, 0, 9);
    let a = if hi >= dp.h3hi { 1usize } else { 0usize };
    let b = if ctl >= dp.h3ctl { 1usize } else { 0usize };
    let c = if e < dp.h3e { 1usize } else { 0usize };
    if dp.h3 == 2 { 1 } else if dp.h3 == 1 { (a | b) & c } else { 0 }
}

/// 1 for large numeric text: at least V_DIGN per mille digits, few bytes >= 128 or < 9, not genome-like.
#[inline(always)]
pub fn v_numeric(h: &[u32; 256], n: usize, low: usize, dp: &V_Params) -> usize {
    let dig = v_share(h, 48, 58);
    let hi = v_share(h, 128, 256);
    let ctl = v_share(h, 0, 9);
    let txt = if hi < 50 && ctl < 50 { 1usize } else { 0usize };
    let big = if n >= dp.nbig { 1usize } else { 0usize };
    let d = if dig >= dp.dign { 1usize } else { 0usize };
    if low == 1 { 0 } else { txt & big & d }
}

// ------------------------------------------------------------------ match finding (search only)

/// Walk the chain from `start` (pos+1 encoded, 0 = none) for the candidate with the best score
/// among those longer than `bl0` and scoring more than `bs0`. Returns `len | dist << 9 | score << 25`
/// (0 if none). Candidates stay inside the 32K window; the walk stops at `V_NICE` or `cap`.
pub fn v_walk(input: &[u8], prev: &[u32; 65536], pos: usize, start: usize, cap: usize, probes: usize, bl0: usize, bs0: usize, litq: usize) -> usize {
    let lim = pos.saturating_sub(32768);
    let stop = if cap < V_NICE { cap } else { V_NICE };
    let mut cur = start;
    let mut k = 0usize;
    let mut bl = bl0;
    let mut bs = bs0;
    let mut bd = 0usize;
    let mut off = if bl >= 3 { bl - 3 } else { 0 };
    let mut want = v_ld4(input, pos.wrapping_add(off));
    while k < probes && cur > lim && bl < stop {
        let c = cur - 1;
        let next = prev[c % 65536] as usize;
        if v_ld4(input, c.wrapping_add(off)) == want {
            let l = v_fast_len(input, c, pos, cap);
            let d = pos.wrapping_sub(c);
            let s = v_score(l, d, litq);
            let better = if l > bl { if s > bs { 1usize } else { 0usize } } else { 0usize };
            if better == 1 {
            bd = if better == 1 { d } else { bd };
            bs = if better == 1 { s } else { bs };
            bl = if better == 1 { l } else { bl };
            off = if bl >= 3 { bl - 3 } else { 0 };
            want = v_ld4(input, pos.wrapping_add(off));
            }
        }
        cur = next;
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
/// (0 if none). Candidates stay inside the 32K window; the walk stops at `V_NICE` or `cap`.
#[inline(always)]
pub fn v_lwalk(input: &[u8], prev: &[u32; 65536], pos: usize, start: usize, cap: usize, probes: usize, bl0: usize, bs0: usize, litq: usize) -> usize {
    let lim = pos.saturating_sub(32768);
    let stop = if cap < V_NICE { cap } else { V_NICE };
    let mut cur = start;
    let mut k = 0usize;
    let mut bl = bl0;
    let mut bs = bs0;
    let mut bd = 0usize;
    let mut off = if bl >= 3 { bl - 3 } else { 0 };
    let mut want = v_ld4(input, pos.wrapping_add(off));
    while k < probes && cur > lim && bl < stop {
        let c = cur - 1;
        let next = prev[c % 65536] as usize;
        if v_ld4(input, c.wrapping_add(off)) == want {
            let l = v_fast_len(input, c, pos, cap);
            let d = pos.wrapping_sub(c);
            let s = v_score(l, d, litq);
            let better = if l > bl { if s > bs { 1usize } else { 0usize } } else { 0usize };
            if better == 1 {
            bd = if better == 1 { d } else { bd };
            bs = if better == 1 { s } else { bs };
            bl = if better == 1 { l } else { bl };
            off = if bl >= 3 { bl - 3 } else { 0 };
            want = v_ld4(input, pos.wrapping_add(off));
            }
        }
        cur = next;
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
pub fn v_cand3(input: &[u8], pos: usize, s3: usize, cap: usize, bs0: usize, litq: usize) -> usize {
    if s3 == 0 || s3 > pos || cap < 3 {
        return 0;
    }
    let c = s3 - 1;
    let d = pos - c;
    if d > V_MAX3 || (v_ld4(input, c) ^ v_ld4(input, pos)) & 16777215 != 0 {
        return 0;
    }
    let s = v_score(3, d, litq);
    if s > bs0 {
        3 | d.wrapping_mul(512) | s.wrapping_mul(33554432)
    } else {
        0
    }
}


pub fn v_cand3_long(input: &[u8], pos: usize, s3: usize, cap: usize, bs0: usize, litq: usize) -> usize {
    if s3 == 0 || s3 > pos || cap < 3 {
        return 0;
    }
    let c = s3 - 1;
    let d = pos - c;
    if d > V_MAX3 || (v_ld4(input, c) ^ v_ld4(input, pos)) & 16777215 != 0 {
        return 0;
    }
    let l = v_fast_len(input, c, pos, cap);
    let s = v_score(l, d, litq);
    if l >= 3 && s > bs0 {
        l | d.wrapping_mul(512) | s.wrapping_mul(33554432)
    } else {
        0
    }
}

pub const V_SUFFIX_DEPTH: usize = 6;

/// Probe a bounded suffix chain and shift its candidates to this match position.
pub fn v_suffix_walk(input: &[u8], prev: &[u32; 65536], pos: usize, cap: usize, best0: usize, litq: usize, probes: usize) -> usize {
    let bl0 = best0 % 512;
    if bl0 < 4 || bl0 > 64 || probes < 8 { return best0; }
    let off = bl0 - 3;
    let q = pos.wrapping_add(off);
    let lim = q.saturating_sub(32768);
    let mut cur = prev[q % 65536] as usize;
    let mut best = best0;
    let mut k = 0usize;
    while k < V_SUFFIX_DEPTH && cur > lim && cur > off && cur <= q {
        let c = cur - 1 - off;
        let d = pos.wrapping_sub(c);
        if v_ld4(input, c) == v_ld4(input, pos) {
            let l = v_fast_len(input, c, pos, cap);
            let sc = v_score(l, d, litq);
            if l >= 4 && sc > best / 33554432 {
                best = l | d.wrapping_mul(512) | sc.wrapping_mul(33554432);
            }
        }
        cur = prev[(cur - 1) % 65536] as usize;
        k += 1;
    }
    best
}

/// With `probes > 0`: insert `pos` into the chains, then walk them (see `walk`); with nothing found
/// and `h3on == 1`, try the 3-byte table. 0 when `probes == 0`.
pub fn v_search(input: &[u8], head: &mut [u32; 65536], prev: &mut [u32; 65536], head3: &mut [u32; 16384], shorts: &[u32; 4096], pos: usize, probes: usize, bl0: usize, bs0: usize, litq: usize, hs: u32, h3on: usize) -> usize {
    let n = input.len();
    if probes == 0 || n < 16 || pos > n - 16 {
        return 0;
    }
    let node = prev[pos % 65536];
    let start = node as usize;
    let s3 = if h3on == 1 { shorts[pos % 4096] as usize } else { 0 };
    let rem = n - pos - 8;
    let cap = if rem < 258 { rem } else { 258 };
    let w2 = v_walk(input, prev, pos, start, cap, probes, bl0, bs0, litq);
    let w2 = v_suffix_walk(input, prev, pos, cap, w2, litq, probes);
    if hs >= 256 && s3 != 0 {
        let cmp = if w2 != 0 { w2 / 33554432 } else { bs0 };
        let w3 = v_cand3_long(input, pos, s3, cap, cmp, litq);
        if w3 != 0 { return w3; }
    }
    if w2 != 0 || s3 == 0 || bl0 >= 3 {
        w2
    } else {
        v_cand3(input, pos, s3, cap, bs0, litq)
    }
}

/// With `on == 1`: enter `pos` into the 3-byte table and return the entry it replaced; else 0.
pub fn v_upd3(input: &[u8], head3: &mut [u32; 16384], pos: usize, on: usize) -> usize {
    if on == 1 {
        let g = v_hash3(v_ld4(input, pos)) % 16384;
        let s3 = head3[g] as usize;
        head3[g] = (pos as u32).wrapping_add(1);
        s3
    } else {
        0
    }
}

/// Insert positions `from .. to` into the chains.
pub fn v_insert_range(input: &[u8], head: &mut [u32; 65536], prev: &mut [u32; 32768], from: usize, to: usize, hs: u32) {
    let lim = input.len().saturating_sub(16);
    let mut p = from;
    while p < to && p <= lim {
        let h = v_hashp(input, p, hs) % 65536;
        prev[p % 32768] = head[h];
        head[h] = (p as u32).wrapping_add(1);
        p += 1;
    }
}

/// `insert_range` that also updates the 3-byte table.
pub fn v_insert_range3(input: &[u8], head: &mut [u32; 65536], prev: &mut [u32; 32768], head3: &mut [u32; 16384], from: usize, to: usize, hs: u32) {
    let lim = input.len().saturating_sub(16);
    let mut p = from;
    while p < to && p <= lim {
        let h = v_hashp(input, p, hs) % 65536;
        prev[p % 32768] = head[h];
        head[h] = (p as u32).wrapping_add(1);
        head3[v_hash3(v_ld4(input, p)) % 16384] = (p as u32).wrapping_add(1);
        p += 1;
    }
}

/// Insert the inside `from .. to` of an emitted match: its first V_IH and last V_IT positions.
pub fn v_insert_match(input: &[u8], head: &mut [u32; 65536], prev: &mut [u32; 32768], head3: &mut [u32; 16384], from: usize, to: usize, hs: u32, h3on: usize) {
    let a = from.wrapping_add(V_IH);
    let a2 = if a < to { a } else { to };
    let b = to.wrapping_sub(V_IT);
    let b2 = if b > a2 { if b < to { b } else { a2 } } else { a2 };
    if h3on == 1 {
        v_insert_range3(input, head, prev, head3, from, a2, hs);
        if b2 < to {
            v_insert_range3(input, head, prev, head3, b2, to, hs);
        }
    } else {
        v_insert_range(input, head, prev, from, a2, hs);
        if b2 < to {
            v_insert_range(input, head, prev, b2, to, hs);
        }
    }
}

// ------------------------------------------------------------------ trusted core

/// How many bytes agree at `a` and `b`, up to `cap`. The emission's byte-wise check.
/// Trusted: little-endian 8-byte word at `p` (0 when out of range).
pub fn v_tw8(input: &[u8], p: usize) -> u64 {
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
pub fn v_tw4(input: &[u8], p: usize) -> u32 {
    let n = input.len();
    if n < 4 || p > n - 4 {
        return 0;
    }
    (input[p] as u32) + (input[p + 1] as u32) * 256 + (input[p + 2] as u32) * 65536 + (input[p + 3] as u32) * 16777216
}

/// Trusted: 1 iff `cap >= 8`, `cap - l < 8` and the 8-byte words at `a + cap - 8` and `b + cap - 8` are equal.
pub fn v_tail_eq(input: &[u8], a: usize, b: usize, cap: usize, l: usize) -> usize {
    if cap < 8 || cap - l >= 8 {
        return 0;
    }
    if v_tw8(input, a + (cap - 8)) == v_tw8(input, b + (cap - 8)) {
        1
    } else {
        0
    }
}

/// Trusted: 1 iff `4 <= cap < 8` and the 4-byte words at `a`, `b` and at `a + cap - 4`, `b + cap - 4` are equal.
pub fn v_short_eq(input: &[u8], a: usize, b: usize, cap: usize) -> usize {
    if cap < 4 || cap >= 8 {
        return 0;
    }
    if v_tw4(input, a) != v_tw4(input, b) {
        return 0;
    }
    if v_tw4(input, a + (cap - 4)) == v_tw4(input, b + (cap - 4)) {
        1
    } else {
        0
    }
}

/// Trusted: a length `l <= cap` over which the bytes at `a` and `b` provably agree, found with word compares:
/// 8-byte steps, then one overlapping 8-byte compare at `cap - 8` (or two 4-byte ones when 4 <= cap < 8); `cap`
/// itself when everything agreed.
pub fn v_words_eq(input: &[u8], a: usize, b: usize, cap: usize) -> usize {
    let mut l = 0usize;
    while cap - l >= 8 && v_tw8(input, a + l) == v_tw8(input, b + l) {
        l += 8;
    }
    let big = v_tail_eq(input, a, b, cap, l);
    let small = v_short_eq(input, a, b, cap);
    if big == 1 {
        cap
    } else if small == 1 {
        cap
    } else {
        l
    }
}

/// Trusted: how many bytes agree at `a` and `b`, up to `cap` (word compares, then bytes).
pub fn v_match_len(input: &[u8], a: usize, b: usize, cap: usize) -> usize {
    let mut l = v_words_eq(input, a, b, cap);
    while l < cap && input[b + l] == input[a + l] {
        l += 1;
    }
    l
}

/// True iff `(ch, d)` at `pos` is in range and its bytes agree.
pub fn v_verified(input: &[u8], pos: usize, d: usize, ch: usize) -> bool {
    let n = input.len();
    if ch < 3 || ch > 258 || d < 1 || d > 32768 || d > pos || pos > n || ch > n - pos {
        return false;
    }
    let v = v_match_len(input, pos - d, pos, ch);
    v >= ch
}

/// Trusted: `cnt >= 1` literals from `pos0` (stopping at the input end).
pub fn v_emit_lits(input: &[u8], out: &mut [u32], pos0: usize, cnt: usize, ntok0: usize) -> (usize, usize) {
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
pub fn v_emit_step(input: &[u8], out: &mut [u32], pos: usize, d: usize, l: usize, lits: usize, ntok: usize) -> (usize, usize) {
    if v_verified(input, pos, d, l) {
        out[ntok] = 16777216u32 + ((d - 1) as u32) * 256 + ((l - 3) as u32);
        (ntok + 1, pos + l)
    } else {
        v_emit_lits(input, out, pos, lits, ntok)
    }
}

#[inline(always)]
pub fn v_back_verified(input: &[u8], pos: usize, d: usize, ch: usize) -> bool {
    let n = input.len();
    if ch < 3 || ch > 258 || d < 1 || d > 32768 || d > pos || pos > n || ch > n - pos {
        return false;
    }
    let v = v_match_len(input, pos - d, pos, ch);
    v >= ch
}


pub const V_BACK_LIMIT: usize = 2;
pub const V_BACK_MATCH: usize = 1;

/// Fold preceding tokens into a match, then use the unchanged verified emitter.
#[inline(always)]
pub fn v_back_emit(input: &[u8], out: &mut [u32], pos: usize, d: usize, l: usize, lits: usize, ntok: usize) -> (usize, usize) {
    let good = l >= 3 && l <= 258;
    let mut p = pos;
    let mut t = ntok;
    let mut len = l;
    let mut k = 0usize;
    while good && k < V_BACK_LIMIT && t > 0 && t <= out.len() && len < 258 {
        let tok = out[t - 1];
        let w = if tok < 256 { 1usize } else if V_BACK_MATCH == 1 && tok >= 16777216 { ((tok - 16777216) % 256 + 3) as usize } else { 0 };
        if w > 0 && w <= p && d <= p - w && w <= 258 - len && v_fast_len(input, p - w - d, p - w, w) == w {
            p -= w;
            t -= 1;
            len += w;
            k += 1;
        } else { k = V_BACK_LIMIT; }
    }
    if p < pos && v_back_verified(input, p, d, len) {
        out[t] = 16777216u32 + ((d - 1) as u32) * 256 + ((len - 3) as u32);
        (t + 1, p + len)
    } else { v_emit_step(input, out, pos, d, l, lits, ntok) }
}

// ------------------------------------------------------------------ the parse loop

/// The lazy check at `q` (= match position + 1) with `go == 1`: enter `q` into the chains and test the most
/// recent chain candidate against the current match (`l1` bytes, score `sv1`). Returns `len | dist << 9 |
/// score << 25` when that candidate is at least as long and scores higher, else 0. `go == 0`: does nothing.
#[inline(always)]
pub fn v_lazy_probe(input: &[u8], head: &mut [u32; 65536], prev: &mut [u32; 65536], head3: &mut [u32; 16384], q: usize, go: usize, p2: usize, l1: usize, sv1: usize, litq: usize, hs: u32, h3on: usize) -> usize {
    let n = input.len();
    if go == 0 || n < 16 || q > n - 16 {
        return 0;
    }
    let start = prev[q % 65536] as usize;
    let rem = n - q - 8;
    let cap = if rem < 258 { rem } else { 258 };
    let pr = if l1 >= V_GOODL { V_P2G } else { p2 };
    v_lwalk(input, prev, q, start, cap, pr, l1.wrapping_sub(1), sv1, litq)
}

/// 1 when the lazy candidate `(l2, d2)` found at `pos + 1` also covers `pos` (so it can start there).
pub fn v_ext_ok(input: &[u8], pos: usize, l2: usize, d2: usize) -> usize {
    let n = input.len();
    if V_EXT == 0 || l2 < 3 || l2 >= 258 || d2 < 1 || d2 > pos || pos >= n {
        return 0;
    }
    if input[pos] == input[pos - d2] { 1 } else { 0 }
}


// ============================ jfloor fast-path module v5 (untrusted except the fl_ trusted copies) ==============
// Graft: the base parser's `parse` becomes `v_main_parse(input, out, lh, pos0, ntok0)` and this module's `parse` runs
//   v_fl_part(input, out, mode, fh, cf)  -> (ntok, pos): the whole input for modes 1-5, (0, 0) for mode 0,
//   v_main_parse(input, out, &fh, pos, ntok) -> the base parser from `pos` (a no-op when pos == n).
// Modes (fl_mode, loop-free, from a strided 4K-byte sample + 16 probe chunks of 256 bytes):
//   4 RLE  : one byte value >= 75% of the v_sample (sparse): distance-1 runs, no tables;
//   5 V_LAZY : small files (< 64 KB), database-like binaries (zero bytes but mostly printable), high-entropy data
//            (images, f32 weights, archives): the module's own price-lazy parser with a per-class config `cf`;
//   2 DNA  : 4-symbol alphabet (FASTA): literal runs over cheap bytes, cost-checked matches at expensive bytes;
//   1 LIT  : 2-periodic 16-bit weights (bf16/f16) and skewed-uniform int8 weights (q8, no repeats at all);
//   0      : the base parser.
// The module has its own copies of the trusted kit functions (fl_match_len, fl_verified, fl_emit_lits,
// fl_emit_step) so the base keeps its own emit_step/emit_lits with one caller each (sharing them made LLVM
// outline the base's emit_step: +1% instructions on every text file).

pub const V_FL_PMIN: [usize; 8] = [65536; 8];
pub const V_FL_PNC: [usize; 8] = [16, 8, 8, 1, 8, 1, 16, 16];
pub const V_FL_PCH: usize = 256;
pub const V_FL_RLE_TOP: [usize; 8] = [192; 8];
pub const V_FL_DNA_THR: u32 = 64;
pub const V_FL_DNA_DEPTH: usize = 64;
pub const V_FL_DNA_M0: usize = 12;
pub const V_FL_CMAX: u32 = 192;
pub const V_FL_HIGH: [usize; 8] = [104; 8];
pub const V_FL_DBZ: [usize; 8] = [8; 8];
pub const V_FL_DBNP: [usize; 8] = [110; 8];
pub const V_FL_USE_T: [usize; 8] = [1; 8];
pub const V_FL_USE_D: [usize; 8] = [0; 8];
pub const V_FL_USE_H: [usize; 8] = [0; 8];
pub const V_FL_USE_LIT: [usize; 8] = [1; 8];
// class configs (T: small files, D: database-like, H: high entropy)
pub const V_FT_DEPTH: [usize; 8] = [16; 8];
pub const V_FT_DEPTH2: [usize; 8] = [2; 8];
pub const V_FT_LAZY: [usize; 8] = [259; 8];
pub const V_FT_NICE: [usize; 8] = [258; 8];
pub const V_FT_IH: [usize; 8] = [64, 64, 64, 64, 64, 32, 64, 64];
pub const V_FT_IT: [usize; 8] = [16, 64, 64, 0, 64, 64, 16, 16];
pub const V_FT_ACC: [usize; 8] = [63; 8];
pub const V_FD_DEPTH: [usize; 8] = [12; 8];
pub const V_FD_DEPTH2: [usize; 8] = [2; 8];
pub const V_FD_LAZY: [usize; 8] = [259; 8];
pub const V_FD_NICE: [usize; 8] = [258; 8];
pub const V_FD_IH: [usize; 8] = [64; 8];
pub const V_FD_IT: [usize; 8] = [16; 8];
pub const V_FD_ACC: [usize; 8] = [63; 8];
pub const V_FH_DEPTH: [usize; 8] = [6; 8];
pub const V_FH_DEPTH2: [usize; 8] = [2; 8];
pub const V_FH_LAZY: [usize; 8] = [32; 8];
pub const V_FH_NICE: [usize; 8] = [64; 8];
pub const V_FH_IH: [usize; 8] = [64; 8];
pub const V_FH_IT: [usize; 8] = [16; 8];
pub const V_FH_ACC: [usize; 8] = [7; 8];
pub const V_FL_GOOD: usize = 8;
pub const V_FL_LITQ: [usize; 8] = [32; 8];
pub const V_FL_LADJ: [usize; 8] = [4; 8];
pub const V_FL_HLOW: [usize; 8] = [900; 8];
pub const V_FL_C0Q: usize = 44;

// ---------------------------------------------------------------- trusted core (floor copy)

/// Byte-wise common prefix length (trusted).
/// Trusted: little-endian 8-byte word at `p` (0 when out of range).
pub fn v_fl_tw8(input: &[u8], p: usize) -> u64 {
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
pub fn v_fl_tw4(input: &[u8], p: usize) -> u32 {
    let n = input.len();
    if n < 4 || p > n - 4 {
        return 0;
    }
    (input[p] as u32) + (input[p + 1] as u32) * 256 + (input[p + 2] as u32) * 65536 + (input[p + 3] as u32) * 16777216
}

/// Trusted: 1 iff `cap >= 8`, `cap - l < 8` and the 8-byte words at `a + cap - 8` and `b + cap - 8` are equal.
pub fn v_fl_tail_eq(input: &[u8], a: usize, b: usize, cap: usize, l: usize) -> usize {
    if cap < 8 || cap - l >= 8 {
        return 0;
    }
    if v_fl_tw8(input, a + (cap - 8)) == v_fl_tw8(input, b + (cap - 8)) {
        1
    } else {
        0
    }
}

/// Trusted: 1 iff `4 <= cap < 8` and the 4-byte words at `a`, `b` and at `a + cap - 4`, `b + cap - 4` are equal.
pub fn v_fl_short_eq(input: &[u8], a: usize, b: usize, cap: usize) -> usize {
    if cap < 4 || cap >= 8 {
        return 0;
    }
    if v_fl_tw4(input, a) != v_fl_tw4(input, b) {
        return 0;
    }
    if v_fl_tw4(input, a + (cap - 4)) == v_fl_tw4(input, b + (cap - 4)) {
        1
    } else {
        0
    }
}

/// Trusted: a length `l <= cap` over which the bytes at `a` and `b` provably agree, found with word compares:
/// 8-byte steps, then one overlapping 8-byte compare at `cap - 8` (or two 4-byte ones when 4 <= cap < 8); `cap`
/// itself when everything agreed.
pub fn v_fl_words_eq(input: &[u8], a: usize, b: usize, cap: usize) -> usize {
    let mut l = 0usize;
    while cap - l >= 8 && v_fl_tw8(input, a + l) == v_fl_tw8(input, b + l) {
        l += 8;
    }
    let big = v_fl_tail_eq(input, a, b, cap, l);
    let small = v_fl_short_eq(input, a, b, cap);
    if big == 1 {
        cap
    } else if small == 1 {
        cap
    } else {
        l
    }
}

/// Trusted: how many bytes agree at `a` and `b`, up to `cap` (word compares, then bytes).
pub fn v_fl_match_len(input: &[u8], a: usize, b: usize, cap: usize) -> usize {
    let mut l = v_fl_words_eq(input, a, b, cap);
    while l < cap && input[b + l] == input[a + l] {
        l += 1;
    }
    l
}

/// True iff `(ch, d)` at `pos` is in range and its bytes agree (trusted).
pub fn v_fl_verified(input: &[u8], pos: usize, d: usize, ch: usize) -> bool {
    let n = input.len();
    if ch < 3 || ch > 258 || d < 1 || d > 32768 || d > pos || pos > n || ch > n - pos {
        return false;
    }
    let v = v_fl_match_len(input, pos - d, pos, ch);
    v >= ch
}

/// Trusted: `cnt >= 1` literals from `pos0` (stopping at the input end).
pub fn v_fl_emit_lits(input: &[u8], out: &mut [u32], pos0: usize, cnt: usize, ntok0: usize) -> (usize, usize) {
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
pub fn v_fl_emit_step(input: &[u8], out: &mut [u32], pos: usize, d: usize, l: usize, lits: usize, ntok: usize) -> (usize, usize) {
    if v_fl_verified(input, pos, d, l) {
        out[ntok] = 16777216u32 + ((d - 1) as u32) * 256 + ((l - 3) as u32);
        (ntok + 1, pos + l)
    } else {
        v_fl_emit_lits(input, out, pos, lits, ntok)
    }
}

// ---------------------------------------------------------------- loads, compares, hashes (search only)

/// `input[i]`, or 0 out of range.
pub fn v_fl_byte(input: &[u8], i: usize) -> usize {
    if i < input.len() {
        input[i] as usize
    } else {
        0
    }
}

/// Little-endian 4-byte load at `p`; 0 when out of range.
pub fn v_fl_ld4(input: &[u8], p: usize) -> u32 {
    let n = input.len();
    if n < 4 || p > n - 4 {
        return 0;
    }
    ((input[p + 3] as u32) << 24) | ((input[p + 2] as u32) << 16) | ((input[p + 1] as u32) << 8) | (input[p] as u32)
}

/// Little-endian 8-byte load at `p` (two 4-byte halves); 0 when out of range.
pub fn v_fl_ld8(input: &[u8], p: usize) -> u64 {
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
pub fn v_fl_len(input: &[u8], a: usize, b: usize, cap: usize) -> usize {
    let mut l = 0usize;
    let mut go = 1usize;
    let mut it = 0usize;
    while go == 1 && it < 40 {
        if l < cap {
            let x = v_fl_ld8(input, a.wrapping_add(l)) ^ v_fl_ld8(input, b.wrapping_add(l));
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
pub fn v_fl_hashp(input: &[u8], p: usize, hsh: u64) -> usize {
    let v = v_fl_ld8(input, p) << (hsh % 64);
    ((v.wrapping_mul(0x9E3779B97F4A7C15) >> 48) as usize) % 65536
}

// ---------------------------------------------------------------- statistics and costs (search only)

/// log2(1 + i/16) in 1/16 bits.
pub const V_FL_LOGF: [u32; 16] = [0, 1, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 15];

/// log2(f) in 1/16 bits (0 for f = 0).
pub fn v_fl_log16(f: u32) -> u32 {
    let lz = f.leading_zeros();
    let top = ((((f as u64) << ((lz as u64).wrapping_add(1) % 64)) >> 28) as usize) % 16;
    if f == 0 {
        0
    } else {
        (31u32.wrapping_sub(lz)).wrapping_mul(16).wrapping_add(V_FL_LOGF[top])
    }
}

/// Strided byte histogram of about 4096 samples.
pub fn v_fl_sample(input: &[u8], h: &mut [u32; 256]) {
    let n = input.len();
    let st = n / 4096 + 1;
    let mut k = 0usize;
    let mut c = 0usize;
    while k < n && c < 8192 {
        let b = v_fl_byte(input, k) % 256;
        h[b] = h[b].wrapping_add(1);
        k = k.wrapping_add(st);
        c += 1;
    }
}

/// Literal cost per byte value (1/16 bits) from the histogram: log2(total / f), unseen bytes V_FL_CMAX.
pub fn v_fl_costs(h: &[u32; 256], cost: &mut [u32; 256]) {
    let mut t = 0u32;
    let mut i = 0usize;
    while i < 256 {
        t = t.wrapping_add(h[i]);
        i += 1;
    }
    let lt = v_fl_log16(t);
    let mut j = 0usize;
    while j < 256 {
        let f = h[j];
        let c = lt.wrapping_sub(v_fl_log16(f));
        cost[j] = if f == 0 { V_FL_CMAX } else if c > V_FL_CMAX { V_FL_CMAX } else { c };
        j += 1;
    }
}

/// Order-0 entropy in 1/16 bits per byte of the 256 bins starting at `base` of `h`.
pub fn v_fl_ent(h: &[u32; 1024], base: usize) -> usize {
    let mut t = 0u32;
    let mut i = 0usize;
    while i < 256 {
        t = t.wrapping_add(h[base.wrapping_add(i) % 1024]);
        i += 1;
    }
    let lt = v_fl_log16(t);
    let mut bits = 0usize;
    let mut j = 0usize;
    while j < 256 {
        let f = h[base.wrapping_add(j) % 1024];
        let c = lt.wrapping_sub(v_fl_log16(f)) as usize;
        bits = if f > 0 { bits.wrapping_add((f as usize).wrapping_mul(c)) } else { bits };
        j += 1;
    }
    let tt = if t == 0 { 1usize } else { t as usize };
    bits / tt
}

/// Sample statistics packed into one word: bits 0-9 entropy (1/16 bits), 10-18 top byte v_share (1/256),
/// 19-27 zero-byte share, 28-36 non-printable share, 37-45 share of the byte values with share >= 1/8,
/// 46-49 number of such byte values.
pub fn v_fl_stats(h: &[u32; 256]) -> u64 {
    let mut t = 0u32;
    let mut i = 0usize;
    while i < 256 {
        t = t.wrapping_add(h[i]);
        i += 1;
    }
    let lt = v_fl_log16(t);
    let mut bits = 0usize;
    let mut top = 0u32;
    let mut np = 0usize;
    let mut big = 0usize;
    let mut bigsum = 0usize;
    let mut j = 0usize;
    while j < 256 {
        let f = h[j];
        let c = lt.wrapping_sub(v_fl_log16(f)) as usize;
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

/// Chunk `s .. s + V_FL_PCH`: 4-phase byte histograms (phase = absolute position mod 4) into `ph`, and the number
/// of positions whose most recent same-3-byte-hash position in the chunk repeats 4 bytes.
pub fn v_fl_probe_chunk(input: &[u8], tab: &mut [u32; 4096], ph: &mut [u32; 1024], s: usize) -> usize {
    let mut p = s;
    let mut k = 0usize;
    let mut c4 = 0usize;
    while k < V_FL_PCH {
        let x = v_fl_ld8(input, p);
        let b = (x as usize) % 256;
        let slot = (p % 4).wrapping_mul(256).wrapping_add(b) % 1024;
        ph[slot] = ph[slot].wrapping_add(1);
        let x3 = (x as u32) & 16777215;
        let h = (x3.wrapping_mul(2654435761) >> 20) as usize % 4096;
        let q = tab[h] as usize;
        let y = if q > s && q <= p { v_fl_ld8(input, q - 1) } else { !x };
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
#[inline(always)]
pub fn v_fl_weights(input: &[u8], dp: &V_Params) -> usize {
    let n = input.len();
    let mut tab = [0u32; 4096];
    let mut ph = [0u32; 1024];
    let pnc = if dp.fl_pnc == 0 { 1 } else { dp.fl_pnc };
    let span = n / pnc;
    let mut c4 = 0usize;
    let mut i = 0usize;
    while i < pnc {
        c4 = c4.wrapping_add(v_fl_probe_chunk(input, &mut tab, &mut ph, i.wrapping_mul(span)));
        i += 1;
    }
    let e0 = v_fl_ent(&ph, 0);
    let e1 = v_fl_ent(&ph, 256);
    let e2 = v_fl_ent(&ph, 512);
    let e3 = v_fl_ent(&ph, 768);
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

/// The mode (0 base, 1 LIT, 2 DNA, 4 RLE, 5 V_LAZY) and the V_LAZY class (0 T, 1 D, 2 H), packed `mode + 8 * class`.
/// Integer flags and nested value-ifs only (no `&&` guarding code, so the extracted model stays small).
#[inline(always)]
pub fn v_fl_mode(input: &[u8], st: u64, dp: &V_Params) -> usize {
    let n = input.len();
    let e = (st as usize) % 1024;
    let top = ((st >> 10) % 512) as usize;
    let z = ((st >> 19) % 512) as usize;
    let np = ((st >> 28) % 512) as usize;
    let bs = ((st >> 37) % 512) as usize;
    let bg = ((st >> 46) % 16) as usize;
    let rle = if top >= dp.fl_rle_top { if n >= 1024 { 1usize } else { 0usize } } else { 0usize };
    let small = if n < dp.fl_pmin { 1usize } else { 0usize };
    let dna = if bg == 4 { if bs >= 205 { if e < 52 { 1usize } else { 0usize } } else { 0usize } } else { 0usize };
    let high = if e >= dp.fl_high { 1usize } else { 0usize };
    let db = if z >= dp.fl_dbz { if np < dp.fl_dbnp { 1usize } else { 0usize } } else { 0usize };
    let w = if high == 1 { if dp.fl_use_lit == 1 { v_fl_weights(input, dp) } else { 0 } } else { 0 };
    let mh = if w == 1 { 1 } else if dp.fl_use_h == 1 { 21 } else { 0 };
    let md = if dp.fl_use_d == 1 { 13 } else { 0 };
    let mt = if dp.fl_use_t == 1 { 5 } else { 0 };
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

/// The V_LAZY configuration of a class: [depth, depth2, lazy, nice, ih, it, acc].
#[inline(always)]
pub fn v_fl_config(class: usize, cf: &mut [usize; 8], dp: &V_Params) {
    cf[0] = if class == 0 { dp.ft_depth } else if class == 1 { dp.fd_depth } else { dp.fh_depth };
    cf[1] = if class == 0 { dp.ft_depth2 } else if class == 1 { dp.fd_depth2 } else { dp.fh_depth2 };
    cf[2] = if class == 0 { dp.ft_lazy } else if class == 1 { dp.fd_lazy } else { dp.fh_lazy };
    cf[3] = if class == 0 { dp.ft_nice } else if class == 1 { dp.fd_nice } else { dp.fh_nice };
    cf[4] = if class == 0 { dp.ft_ih } else if class == 1 { dp.fd_ih } else { dp.fh_ih };
    cf[5] = if class == 0 { dp.ft_it } else if class == 1 { dp.fd_it } else { dp.fh_it };
    cf[6] = if class == 0 { dp.ft_acc } else if class == 1 { dp.fd_acc } else { dp.fh_acc };
}

// ---------------------------------------------------------------- LIT and RLE

/// Trusted-kit emission of the whole input as literals.
pub fn v_fl_lit_parse(input: &[u8], out: &mut [u32]) -> (usize, usize) {
    let n = input.len();
    v_fl_emit_lits(input, out, 0, n, 0)
}

/// RLE parse: a distance-1 run match wherever the previous byte repeats >= 3 times, else one literal.
pub fn v_fl_rle_parse(input: &[u8], out: &mut [u32]) -> (usize, usize) {
    let n = input.len();
    let mut pos = 0usize;
    let mut ntok = 0usize;
    while pos < n {
        let rem = n - pos;
        let cap = if rem < 258 { rem } else { 258 };
        let l = if pos >= 1 { v_fl_len(input, pos - 1, pos, cap) } else { 0 };
        let r = v_fl_emit_step(input, out, pos, 1, l, 1, ntok);
        let olen = out.len();
        ntok = r.0;
        pos = r.1;
    }
    (ntok, pos)
}

// ---------------------------------------------------------------- DNA

/// Number of consecutive cheap bytes (cost < V_FL_DNA_THR) from `pos`.
pub fn v_fl_cheap_run(input: &[u8], cost: &[u32; 256], pos: usize) -> usize {
    let n = input.len();
    let mut k = pos;
    while k < n && cost[input[k] as usize % 256] < V_FL_DNA_THR {
        k += 1;
    }
    k.wrapping_sub(pos)
}

/// Literal cost (1/16 bits) of the `l` bytes at `pos` (l <= 258).
pub fn v_fl_span_cost(input: &[u8], cost: &[u32; 256], pos: usize, l: usize) -> usize {
    let mut s = 0usize;
    let mut i = 0usize;
    while i < l && i < 258 {
        s = s.wrapping_add(cost[v_fl_byte(input, pos.wrapping_add(i)) % 256] as usize);
        i += 1;
    }
    s
}

/// DEFLATE distance extra bits.
pub fn v_fl_dextra(d: usize) -> usize {
    if d <= 4 {
        0
    } else {
        let x = (d.wrapping_sub(1) as u32) | 1;
        (31u32.wrapping_sub(x.leading_zeros()) as usize).wrapping_sub(1)
    }
}

/// DEFLATE length extra bits.
pub fn v_fl_lextra(l: usize) -> usize {
    if l < 512 { V_LEX_BITS[l % 512] as usize } else { 0 }
}

/// 1 iff the match (l, d) at `pos` is estimated cheaper than its literals: V_FL_DNA_M0 bits + extra bits.
pub fn v_fl_dna_ok(input: &[u8], cost: &[u32; 256], pos: usize, l: usize, d: usize) -> usize {
    let mc = V_FL_DNA_M0.wrapping_add(v_fl_dextra(d)).wrapping_add(v_fl_lextra(l)).wrapping_mul(16);
    if v_fl_span_cost(input, cost, pos, l) > mc {
        1
    } else {
        0
    }
}

/// Longest match (ties: the closest) along the chain from `start` (pos+1 encoded). Returns `len | dist << 9`.
pub fn v_fl_dwalk(input: &[u8], prev: &[u32; 32768], pos: usize, start: usize, cap: usize, depth: usize) -> usize {
    let mut bl = 3usize;
    let mut bd = 0usize;
    let mut cur = start;
    let mut k = 0usize;
    while k < depth && cur > 0 && cur <= pos && pos - (cur - 1) <= 32768 {
        let c = cur - 1;
        if bl < cap && v_fl_byte(input, c.wrapping_add(bl)) == v_fl_byte(input, pos.wrapping_add(bl)) {
            let l = v_fl_len(input, c, pos, cap);
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
pub fn v_fl_dsearch(input: &[u8], head: &mut [u32; 65536], prev: &mut [u32; 32768], p: usize, depth: usize) -> usize {
    let n = input.len();
    if depth == 0 || n < 16 || p > n - 16 {
        return 0;
    }
    let h = v_fl_hashp(input, p, 32);
    let start = head[h] as usize;
    prev[p % 32768] = start as u32;
    head[h] = (p as u32).wrapping_add(1);
    let rem = n - p - 8;
    let cap = if rem < 258 { rem } else { 258 };
    v_fl_dwalk(input, prev, p, start, cap, depth)
}

/// Insert positions `from .. to` into the chains (hash of the first 4 bytes if hsh = 32, 8 bytes if hsh = 0).
pub fn v_fl_tinsert(input: &[u8], head: &mut [u16; 16384], prev: &mut [u16; 32768], from: usize, to: usize, hsh: u64) {
    let n = input.len();
    let lim = n.saturating_sub(16);
    let mut p = from;
    while p < to && p <= lim {
        let h = v_fl_hashp(input, p, hsh) % 16384;
        prev[p % 32768] = head[h];
        head[h] = (p as u16).wrapping_add(1);
        p += 1;
    }
}

pub fn v_fl_insert(input: &[u8], head: &mut [u32; 65536], prev: &mut [u32; 32768], from: usize, to: usize, hsh: u64) {
    let n = input.len();
    let lim = n.saturating_sub(16);
    let mut p = from;
    while p < to && p <= lim {
        let h = v_fl_hashp(input, p, hsh);
        prev[p % 32768] = head[h];
        head[h] = (p as u32).wrapping_add(1);
        p += 1;
    }
}

/// DNA parse: literal runs over cheap bytes; at an expensive byte, search and take the match if it is estimated
/// cheaper than its literals. Only searched positions and match interiors enter the chains.
pub fn v_fl_dna_parse(input: &[u8], out: &mut [u32], cost: &[u32; 256]) -> (usize, usize) {
    let n = input.len();
    let mut head = [0u32; 65536];
    let mut prev = [0u32; 32768];
    let mut pos = 0usize;
    let mut ntok = 0usize;
    while pos < n {
        let cr = v_fl_cheap_run(input, cost, pos);
        let harg1 = if cr == 0 { V_FL_DNA_DEPTH } else { 0 };
        let m = v_fl_dsearch(input, &mut head, &mut prev, pos, harg1);
        let l0 = m % 512;
        let d = (m / 512) % 65536;
        let ok = if l0 >= 3 { v_fl_dna_ok(input, cost, pos, l0, d) } else { 0 };
        let l = if ok == 1 { l0 } else { 0 };
        let lits = if cr > 0 { cr } else { 1 };
        let r = v_fl_emit_step(input, out, pos, d, l, lits, ntok);
        let olen = out.len();
        let npos = r.1;
        let matched = if l >= 3 { if npos == pos.wrapping_add(l) { 1usize } else { 0usize } } else { 0usize };
        let harg2 = if matched == 1 { npos } else { pos.wrapping_add(1) };
        v_fl_insert(input, &mut head, &mut prev, pos.wrapping_add(1), harg2, 32);
        ntok = r.0;
        pos = npos;
    }
    (ntok, pos)
}

// ---------------------------------------------------------------- V_LAZY: price-lazy with a runtime config

/// Estimated saving (quarter bits, offset by 4096) of coding `l` bytes as a match at `d`.
pub fn v_fl_score(l: usize, d: usize, litq: usize) -> usize {
    let cost = V_FL_C0Q.wrapping_add(v_fl_dextra(d).wrapping_add(v_fl_lextra(l)).wrapping_mul(4));
    l.wrapping_mul(litq).wrapping_add(4096).wrapping_sub(cost)
}

/// Fixed-point log2 with 8 fractional bits (linear between powers of two); x >= 1.
pub fn v_fl_lg8(x: u32) -> u64 {
    let y = x | 1;
    let e = 31u32.wrapping_sub(y.leading_zeros()) % 32;
    let m = if e >= 8 { (y >> (e - 8)) & 255 } else { (y << (8 - e)) & 255 };
    (e as u64).wrapping_mul(256).wrapping_add(m as u64)
}

/// Entropy of the histogram in 1/256 bits per symbol.
pub fn v_fl_entropy256(h: &[u32; 256]) -> usize {
    let mut tot = 0u64;
    let mut acc = 0u64;
    let mut i = 0usize;
    while i < 256 {
        let c = h[i];
        tot = tot.wrapping_add(c as u64);
        acc = if c > 0 { acc.wrapping_add((c as u64).wrapping_mul(v_fl_lg8(c))) } else { acc };
        i += 1;
    }
    if tot == 0 {
        return 2048;
    }
    let t32 = if tot > 4000000000 { 4000000000u32 } else { tot as u32 };
    let a = v_fl_lg8(t32);
    let b = acc / tot;
    if a > b {
        (a - b) as usize
    } else {
        0
    }
}

/// Literal cost (quarter bits) for low-entropy inputs.
#[inline(always)]
pub fn v_fl_lit_cost(h0: usize, dp: &V_Params) -> usize {
    let ladj = if dp.fl_ladj > 36 { 36 } else { dp.fl_ladj };
    let q = h0 / 64 + ladj;
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
#[inline(always)]
pub fn v_fl_walk(input: &[u8], prev: &[u16; 32768], pos: usize, start: usize, cap: usize, depth: usize, bl0: usize, bs0: usize, litq: usize, nice: usize) -> usize {
    let mut bl = bl0;
    let mut bd = 0usize;
    let mut bs = bs0;
    let mut cur = start;
    let mut k = 0usize;
    let mut off = if bl >= 3 { bl - 3 } else { 0 };
    let mut want = v_fl_ld4(input, pos.wrapping_add(off));
    while k < depth && cur > 0 && cur <= pos && pos - (cur - 1) <= 32768 {
        let c = cur - 1;
        let next = prev[c % 32768] as usize;
        if bl < cap && v_fl_ld4(input, c.wrapping_add(off)) == want {
            let l = v_fl_len(input, c, pos, cap);
            let s = v_fl_score(l, pos - c, litq);
            let take = if l > bl { if s > bs { 1usize } else { 0usize } } else { 0usize };
            if take == 1 {
            bd = if take == 1 { pos - c } else { bd };
            bs = if take == 1 { s } else { bs };
            bl = if take == 1 { l } else { bl };
            off = if bl >= 3 { bl - 3 } else { 0 };
            want = v_fl_ld4(input, pos.wrapping_add(off));
            }
        }
        cur = if bl >= nice { 0 } else { next };
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
pub fn v_fl_search(input: &[u8], head: &mut [u16; 16384], prev: &mut [u16; 32768], pos: usize, depth: usize, ins: usize, bl0: usize, bs0: usize, litq: usize, hsh: u64, nice: usize) -> usize {
    let n = input.len();
    if depth == 0 || n < 16 || pos > n - 16 {
        return 0;
    }
    let h = v_fl_hashp(input, pos, hsh) % 16384;
    let start = head[h] as usize;
    let pw = pos % 32768;
    prev[pw] = if ins == 1 { start as u16 } else { prev[pw] };
    head[h] = if ins == 1 { (pos as u16).wrapping_add(1) } else { head[h] };
    let rem = n - pos - 8;
    let cap = if rem < 258 { rem } else { 258 };
    v_fl_walk(input, prev, pos, start, cap, depth, bl0, bs0, litq, nice)
}

/// Insert the inside `from .. to` of an emitted match: its first `ih` and last `it` positions.
pub fn v_fl_insert_match(input: &[u8], head: &mut [u16; 16384], prev: &mut [u16; 32768], from: usize, to: usize, hsh: u64, ih: usize, it: usize) {
    let a = from.wrapping_add(ih);
    let a2 = if a < to { a } else { to };
    v_fl_tinsert(input, head, prev, from, a2, hsh);
    let b = to.wrapping_sub(it);
    let b2 = if b > a2 { if b < to { b } else { a2 } } else { a2 };
    v_fl_tinsert(input, head, prev, b2, to, hsh);
}

/// Literal-run length after `miss` consecutive misses: 1 + (miss >> acc), at most 32.
pub fn v_fl_lits(miss: usize, acc: usize) -> usize {
    let over = ((miss as u64) >> ((acc as u64) % 64)) as usize;
    if over < 32 {
        over + 1
    } else {
        32
    }
}

/// Literal cost (quarter bits) used by the lazy parser: from the entropy for low-entropy inputs, else V_FL_LITQ.
#[inline(always)]
pub fn v_fl_litq(h0: usize, dp: &V_Params) -> usize {
    if h0 < dp.fl_hlow {
        v_fl_lit_cost(h0, dp)
    } else {
        dp.fl_litq
    }
}

/// Hash shift: 8-byte hash (0) for low-entropy inputs, 4-byte hash (32) otherwise.
#[inline(always)]
pub fn v_fl_hsh(h0: usize, dp: &V_Params) -> u64 {
    if h0 < dp.fl_hlow {
        0
    } else {
        32
    }
}

/// Price-lazy v_parse (the jgreedy jg1c algorithm) with the class configuration `cf`.
#[inline(always)]
pub fn v_fl_lazy_parse(input: &[u8], out: &mut [u32], lh: &[u32; 256], cf: &[usize; 8], dp: &V_Params) -> (usize, usize) {
    let n = input.len();
    let depth = cf[0];
    let depth2 = cf[1];
    let lazy = cf[2];
    let nice = cf[3];
    let ih = cf[4];
    let it = cf[5];
    let acc = cf[6];
    let h0 = v_fl_entropy256(lh);
    let litq = v_fl_litq(h0, dp);
    let hsh = v_fl_hsh(h0, dp);
    let mut head = [0u16; 16384];
    let mut prev = [0u16; 32768];
    let mut pos = 0usize;
    let mut ntok = 0usize;
    let mut carry = 0usize;
    let mut miss = 0usize;
    while pos < n {
        let have = if carry != 0 { 1usize } else { 0usize };
        let harg3 = if have == 1 { 0 } else { depth };
        let s1 = v_fl_search(input, &mut head, &mut prev, pos, harg3, 1, 2, 4096, litq, hsh, nice);
        let m1 = if have == 1 { carry } else { s1 };
        let l1 = m1 % 512;
        if l1 < 3 {
            let lits = v_fl_lits(miss, acc);
            let r = v_fl_emit_step(input, out, pos, 0, 0, lits, ntok);
            let olen = out.len();
            miss = miss.wrapping_add(1);
            carry = 0;
            ntok = r.0;
            pos = r.1;
        } else {
            let d1 = (m1 / 512) % 65536;
            let want = if l1 < lazy { 1usize } else { 0usize };
            let p2 = if want == 1 { if l1 >= V_FL_GOOD { depth2 } else { depth } } else { 0 };
            let s2 = v_fl_search(input, &mut head, &mut prev, pos.wrapping_add(1), p2, 1, l1.wrapping_sub(1), v_fl_score(l1, d1, litq), litq, hsh, nice);
            let take2 = if s2 != 0 { 1usize } else { 0usize };
            let l = if take2 == 1 { 0 } else { l1 };
            let d = if take2 == 1 { 0 } else { d1 };
            let r = v_fl_emit_step(input, out, pos, d, l, 1, ntok);
            let olen = out.len();
            let npos = r.1;
            let matched = if l >= 3 { if npos == pos.wrapping_add(l) { 1usize } else { 0usize } } else { 0usize };
            let from = if want == 1 { pos.wrapping_add(2) } else { pos.wrapping_add(1) };
            let harg4 = if matched == 1 { npos } else { from };
            v_fl_insert_match(input, &mut head, &mut prev, from, harg4, hsh, ih, it);
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
#[inline(always)]
pub fn v_fl_part(input: &[u8], out: &mut [u32], mc: usize, fh: &[u32; 256], dp: &V_Params) -> (usize, usize) {
    let mode = mc % 8;
    if mode == 1 {
        v_fl_lit_parse(input, out)
    } else if mode == 2 {
        let mut cost = [0u32; 256];
        v_fl_costs(fh, &mut cost);
        v_fl_dna_parse(input, out, &cost)
    } else if mode == 4 {
        v_fl_rle_parse(input, out)
    } else if mode == 5 {
        let mut cf = [0usize; 8];
        v_fl_config(mc / 8, &mut cf, dp);
        v_fl_lazy_parse(input, out, fh, &cf, dp)
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
pub fn v_prepare(input: &[u8], head: &mut [u32; 65536], prev: &mut [u32; 65536], head3: &mut [u32; 16384], shorts: &mut [u32; 4096], from: usize, pos: usize, hs: u32, h3on: usize) -> usize {
    let n = input.len();
    if from >= pos.saturating_add(2) || n < 16 {
        return from;
    }
    let sparse = hs % 256 >= 64;
    let hs0 = hs % 64;
    let upto = pos.saturating_add(if sparse { 2 } else { 4096 });
    let end = if upto < n - 15 { upto } else { n - 15 };
    let mut p = if hs % 128 >= 64 && pos > from { pos } else { from };
    while p < end {
        let h = v_hashp(input, p, hs0) % 65536;
        let old = head[h];
        let s3 = v_upd3(input, head3, p, h3on);
        if h3on == 1 { shorts[p % 4096] = s3 as u32; }
        prev[p % 65536] = old;
        head[h] = (p as u32).wrapping_add(1);
        p += 1;
    }
    end
}

/// Price-lazy parse using immutable predecessor links prepared ahead in batches.
/// Each chosen match still passes through the original trusted emission path.
/// Clamp the literal-step dial so every miss emits at least one byte.
#[inline(always)]
pub fn v_bounded_step(x: usize) -> usize {
    if x < 1 { 1 } else if x > 32 { 32 } else { x }
}

#[inline(always)]
pub fn v_main_parse(input: &[u8], out: &mut [u32], pos0: usize, ntok0: usize, dp: &V_Params) -> usize {
    let n = input.len();
    let mut head = [0u32; 65536];
    let mut prev = [0u32; 65536];
    let mut head3 = [0u32; 16384];
    let mut shorts = [0u32; 4096];
    let mut hist = [0u32; 256];
    v_sample(input, &mut hist);
    let e = v_entropy256(&hist);
    let low = v_low_mode(e, dp);
    let m3 = if low == 1 { 0 } else { v_m3_mode(&hist, e, dp) };
    let num = v_numeric(&hist, n, low, dp);
    let lq = if num == 1 { dp.lqn } else { v_lit_cost(e, low, dp) };
    let c0 = if low == 1 { dp.c0l } else { dp.c0q };
    let litq = lq.wrapping_add(c0.wrapping_mul(256));
    let hs = if low == 1 { dp.hsl } else if m3 == 1 { 40 } else { 32 };
    let hs = if e >= 1792 { hs.wrapping_add(128) } else { hs };
    let acc = if low == 1 { dp.accl } else if n < dp.nsmall { 63 } else { dp.acc };
    let depth = if low == 1 { dp.depthl } else if m3 == 1 { dp.depth3m } else if num == 1 { dp.dn } else { dp.depth };
    let ctl = v_share(&hist, 0, 9);
    let depth = if ctl >= 250 { 20 } else { depth };
    let hs = if ctl >= 250 { hs.wrapping_add(256) } else { hs };
    let lz = dp.lazy;
    let p2 = if ctl >= 250 { 8 } else if num == 1 { 12 } else { dp.depth2 };
    let h3on = if m3 == 1 { 0 } else { v_h3_mode(&hist, e, dp) };
    let stepmax = v_bounded_step(dp.stepmax);
    let mut pos = pos0;
    let mut ntok = ntok0;
    let mut carry = 0usize;
    let mut miss = 0usize;
    let mut filled = 0usize;
    while pos < n {
        if filled < pos.saturating_add(3) {
            filled = v_prepare(input, &mut head, &mut prev, &mut head3, &mut shorts, filled, pos, hs.wrapping_add(if miss >= 64 { 64 } else { 0 }), h3on);
        }
        let have = if carry != 0 { 1usize } else { 0usize };
        let dep = if have == 1 { 0 } else { depth };
        let s1 = v_search(input, &mut head, &mut prev, &mut head3, &shorts, pos, dep, 2, V_BIAS, litq, hs, h3on);
        let m1 = if have == 1 { carry } else { s1 };
        let l1 = m1 % 512;
        if l1 < 3 {
            let over = (miss as u64) >> (acc % 64);
            let lits = if over < stepmax as u64 { (over as usize).wrapping_add(1) } else { stepmax };
            let r = v_emit_step(input, out, pos, 0, 0, lits, ntok);
            let olen = out.len();
            miss = miss.wrapping_add(1);
            carry = 0;
            ntok = r.0;
            pos = r.1;
        } else {
            let d1 = (m1 / 512) % 65536;
            let want = if l1 < lz { 1usize } else { 0usize };
            let sv1 = m1 / 33554432;
            let s2 = v_lazy_probe(input, &mut head, &mut prev, &mut head3, pos.wrapping_add(1), want, p2, l1.wrapping_add(V_LZB), sv1.wrapping_add(V_BONUS), litq, hs, h3on);
            let s3 = if h3on == 0 && s2 == 0 && l1 <= 12 { v_lazy_probe(input, &mut head, &mut prev, &mut head3, pos.wrapping_add(2), 1, 1, l1, sv1, litq, hs, h3on) } else { 0 };
            let take3 = if s3 != 0 { 1usize } else { 0usize };
            let take2 = if s2 != 0 { 1usize } else { 0usize };
            let l2 = s2 % 512;
            let d2 = (s2 / 512) % 65536;
            let ex = if take2 == 1 { v_ext_ok(input, pos, l2, d2) } else { 0 };
            let l = if take2 == 1 { if ex == 1 { l2.wrapping_add(1) } else { 0 } } else { l1 };
            let d = if take2 == 1 { if ex == 1 { d2 } else { 0 } } else { d1 };
            let l = if take3 == 1 { 0 } else { l };
            let d = if take3 == 1 { 0 } else { d };
            let lits = if take3 == 1 { 2 } else { 1 };
            let r = v_back_emit(input, out, pos, d, l, lits, ntok);
            let olen = out.len();
            let npos = r.1;

            carry = if take3 == 1 { s3 } else if take2 == 1 { if ex == 1 { 0 } else { s2 } } else { 0 };
            miss = 0;
            ntok = r.0;
            pos = npos;
        }
    }
    ntok
}

/// jfloor dispatcher. Sequential phases (no if/else between loop-heavy paths, SHARED_FINDINGS F17): the floor
/// phase handles the whole input for modes 1-5 and returns (ntok, n); for mode 0 it returns (0, 0) and the base
/// parser runs from position 0.
#[inline(always)]
pub fn v_parse_mode(input: &[u8], out: &mut [u32], m: usize) -> usize {
    let row = m % 8;
    let dp = V_Params {
        depth: V_DEPTH[row],
        depth2: V_DEPTH2[row],
        lazy: V_LAZY[row],
        acc: V_ACC[row],
        stepmax: V_STEPMAX[row],
        h3hi: V_H3HI[row],
        c0q: V_C0Q[row],
        dn: V_DN[row],
        p2n: V_P2N[row],
        fl_pnc: V_FL_PNC[row],
        ft_ih: V_FT_IH[row],
        ft_it: V_FT_IT[row],
        ft_depth: V_FT_DEPTH[row],
        ft_depth2: V_FT_DEPTH2[row],
        ft_lazy: V_FT_LAZY[row],
        ft_nice: V_FT_NICE[row],
        ft_acc: V_FT_ACC[row],
        fd_depth: V_FD_DEPTH[row],
        fd_depth2: V_FD_DEPTH2[row],
        fd_lazy: V_FD_LAZY[row],
        fd_nice: V_FD_NICE[row],
        fd_ih: V_FD_IH[row],
        fd_it: V_FD_IT[row],
        fd_acc: V_FD_ACC[row],
        fh_depth: V_FH_DEPTH[row],
        fh_depth2: V_FH_DEPTH2[row],
        fh_lazy: V_FH_LAZY[row],
        fh_nice: V_FH_NICE[row],
        fh_ih: V_FH_IH[row],
        fh_it: V_FH_IT[row],
        fh_acc: V_FH_ACC[row],
        fl_pmin: V_FL_PMIN[row],
        fl_rle_top: V_FL_RLE_TOP[row],
        fl_high: V_FL_HIGH[row],
        fl_dbz: V_FL_DBZ[row],
        fl_dbnp: V_FL_DBNP[row],
        fl_use_t: V_FL_USE_T[row],
        fl_use_d: V_FL_USE_D[row],
        fl_use_h: V_FL_USE_H[row],
        fl_use_lit: V_FL_USE_LIT[row],
        lqn: V_LQN[row],
        c0l: V_C0L[row],
        hsl: V_HSL[row],
        accl: V_ACCL[row],
        nsmall: V_NSMALL[row],
        depthl: V_DEPTHL[row],
        depth3m: V_DEPTH3M[row],
        elo: V_ELO[row],
        hlow: V_HLOW[row],
        litq: V_LITQ[row],
        ladj: V_LADJ[row],
        m3: V_M3[row],
        m3e: V_M3E[row],
        m3z: V_M3Z[row],
        h3: V_H3[row],
        h3ctl: V_H3CTL[row],
        h3e: V_H3E[row],
        nbig: V_NBIG[row],
        dign: V_DIGN[row],
        fl_litq: V_FL_LITQ[row],
        fl_ladj: V_FL_LADJ[row],
        fl_hlow: V_FL_HLOW[row],
    };
    let mut fh = [0u32; 256];
    v_fl_sample(input, &mut fh);
    let st = v_fl_stats(&fh);
    let mc = v_fl_mode(input, st, &dp);
    let r = v_fl_part(input, out, mc, &fh, &dp);
    if r.1 < input.len() { v_main_parse(input, out, r.1, r.0, &dp) } else { r.0 }
}

pub fn v_parse(input: &[u8], out: &mut [u32]) -> usize { v_parse_mode(input, out, 7) }

#[inline(never)] pub fn y_prose(input:&[u8],out:&mut[u32])->usize {y_a_main_part::<{Y_A_IH[1]},{Y_A_IT[1]},{Y_A_TS[1]},{Y_A_ACC[1]},{Y_A_LZT[1]}>(input,out,0,0,0)}

#[inline(never)] pub fn y_sparse(input:&[u8],out:&mut[u32])->usize {let r=y_a_sh_rle_phase::<{Y_A_SH_L[1]},{Y_A_SH_D[1]},{Y_A_SH_BUDGET[1]},{Y_A_SH_DM[1]}>(input,out);if r.1<input.len(){y_a_main_part::<{Y_A_IH[1]},{Y_A_IT[1]},{Y_A_TS[1]},{Y_A_ACC[1]},{Y_A_LZT[1]}>(input,out,0,r.1,r.0)}else{r.0}}
