//! fastX: a fast, content-adaptive LZ77 parser for the fixed DEFLATE encoder.
//!
//! * Content class from a small strided byte histogram: DNA-like inputs, prose (letters and
//!   spaces, almost no code symbols), other text, high-entropy binaries (with a zero-rich
//!   variant) and structured binaries each get their own settings.
//! * Search: hash chains keyed by the first 4 bytes (3 for structured binaries), a main walk and
//!   a lazy walk, both with a one-byte quick reject; the lazy step compares candidates by an
//!   estimated bit saving. Text looks one byte ahead only after short matches, prose walks
//!   deeper without looking ahead, structured text walks one step and looks ahead deeply.
//! * Every new match first extends backwards over the tokens just written: literals that
//!   match at its distance, and whole earlier matches whose bytes also match there, are
//!   folded into it (fewer, longer matches). Inside long matches the first INS_MAX, every
//!   STRIDE-th and the last TAIL positions are recorded.
//! * Skip acceleration through stretches without matches (capped for zero-rich data).
//! * Tables are sized by the input: small inputs clear and touch less memory.
//! * Emission optionally re-checks each match (VERIFY = 1); a failed check writes a literal.
//! * Tiny inputs (at most TF_N bytes; binaries, optionally plain text) take a separate path: a
//!   planner (`tf_plan`, search only) that spends few distinct length and distance codes (the
//!   encoder's cost per tiny block is mostly per live symbol) writes a plan, and `emit` writes each
//!   planned match only after `check` has re-compared its bytes (anything else becomes literals),
//!   so only the emission carries the decode invariant.
//!
//! Tokens: t < 256 literal, else 2^24 + (dist-1)*256 + (len-3).

pub const HB: u32 = 15;
pub const HN: usize = 32768;
pub const WN: usize = 32768;
/// Inputs of at most SMALL bytes use HS chain heads and a WS window table.
pub const SMALL: usize = 65536;
pub const HS: usize = 4096;
pub const WS: usize = 16384;
pub const NICE: usize = 32;
pub const INS_MAX: usize = 2;
pub const TAIL: usize = 1;
/// Inside long matches, every STRIDE-th position between the head and the tail is chained
/// too (STRIDE = 0: none).
pub const STRIDE: usize = 0;
pub const BACKTOK: usize = 16;
pub const LDEPTH: usize = 1;
pub const SAMPLE: usize = 2048;
pub const VERIFY: usize = 0;
/// Lazy step: a candidate at p+1 needs length >= l + 1 - LSLACK (LSLACK = 1: at least as long
/// as the current match l) and must win on estimated saving (literal worth HLIT/16 bits,
/// match base cost GBASE/16 bits plus extra bits).
pub const LSLACK: usize = 1;
pub const HLIT: u32 = 80;
pub const GBASE: i32 = 168;
/// Per class: main chain depth, lazy threshold, skip shift, skip cap (T text, P prose,
/// H high-entropy binary, Z high-entropy binary rich in zero bytes, B other binary,
/// DNA-like input is sent as literals).
pub const T_DEPTH: usize = 3;
pub const T_LAZY: usize = 0;
pub const T_SKIP: usize = 3;
pub const P_DEPTH: usize = 3;
pub const P_LAZY: usize = 0;
pub const P_SKIP: usize = 5;
pub const H_DEPTH: usize = 3;
pub const H_LAZY: usize = 0;
pub const H_SKIP: usize = 3;
pub const Z_DEPTH: usize = 1;
pub const Z_SKIP: usize = 4;
pub const Z_CAP: usize = 8;
pub const B_DEPTH: usize = 4;
pub const B_LAZY: usize = 3;
pub const B_SKIP: usize = 4;
/// Structured text (class 6: text with at least 1/SDIG of the sample in digits): main depth
/// S_DEPTH, lazy walk depth S_LDEPTH, lazy threshold S_LAZY.
pub const SDIG: u32 = 6;
pub const S_DEPTH: usize = 3;
pub const S_LDEPTH: usize = 1;
pub const S_LAZY: usize = 258;
/// Largest skip step (extra literals per miss) outside the Z class.
pub const SKCAP: usize = 1000000;
/// Tiny inputs (at most TF_N bytes) that `tf_class` calls binary, and with TF_TEXT = 1 also text
/// inputs of a `tf_class` kind below TF_TKIND (0 text, 1 structured text), take the plan +
/// re-verify path (`tf_plan`, then `emit`); every other input takes the engine above. TF_N = 0
/// leaves only the empty input there (no tokens either way): `parse` is then the engine alone.
pub const TF_N: usize = 65536;
pub const TF_TEXT: usize = 1;
pub const TF_TKIND: usize = 1;
/// `tf_class`: about TF_SAMPLE strided bytes (>= 1); structured text has at least 1/TF_SDIG
/// (>= 1) digits.
pub const TF_SAMPLE: usize = 256;
pub const TF_SDIG: u32 = 6;
/// Chain heads (TF_HN = 2^TF_HB slots, 1 <= TF_HB <= 64) and the window table (TF_WN >= 1);
/// positions are kept as u16 (TF_N <= 65536 keeps them exact). Binaries alone (TF_TEXT = 0,
/// TF_BDEPTH = 0) find only distance-1 matches, so the chains never change their plan (a chain
/// candidate can only repeat distance 1, the one kept code): minimal tables skip clearing 72 KB.
/// The text planner (TF_TEXT = 1) walks the chains: TF_HB 12, TF_HN 4096, TF_WN 32768 there.
pub const TF_HB: u32 = 12;
pub const TF_HN: usize = 4096;
pub const TF_WN: usize = 16384;
/// Per kind: chain steps, lazy steps below this match length, skip shift (after m literals in a
/// row, m >> skip positions are not searched; a shift of 32 or more never skips). T text, S
/// structured text, B binaries (3-byte keys; TF_BDEPTH 0 = distance 1 only).
pub const TF_TDEPTH: usize = 1;
pub const TF_TLAZY: usize = 0;
pub const TF_TSKIP: usize = 3;
pub const TF_SDEPTH: usize = 1;
pub const TF_SLAZY: usize = 258;
pub const TF_SSKIP: usize = 3;
pub const TF_BDEPTH: usize = 0;
pub const TF_BLAZY: usize = 0;
pub const TF_BSKIP: usize = 4;
/// A walk stops at a match of TF_NICE bytes; skip steps are at most TF_SKCAP.
pub const TF_NICE: usize = 64;
pub const TF_SKCAP: usize = 1000000;
/// 1: distance 1 is tried before the chain on text too (always on binaries).
pub const TF_TRLE: usize = 1;
/// 1: a new match extends backwards over pending literals; 1: the pending match is folded into
/// a new one when its bytes also match at the new distance.
pub const TF_BACK: usize = 1;
pub const TF_FOLD: usize = 1;
/// The previous match distance is tried before the chain (1), after it (2) or not at all (0).
pub const TF_REP: usize = 1;
/// 1: no search where a run of four equal bytes starts (the next position takes distance 1).
pub const TF_RUNSKIP: usize = 1;
/// Positions chained at the head and at the tail of a match.
pub const TF_INS: usize = 2;
pub const TF_TAIL: usize = 1;
/// Keep thresholds (uses per code): text TF_KL / TF_KD, binaries TF_BKL / TF_BKD (0 or 1: keep
/// every code used).
pub const TF_KL: u32 = 5;
pub const TF_KD: u32 = 5;
pub const TF_BKL: u32 = 3;
pub const TF_BKD: u32 = 3;
/// Re-find: chain steps, single literals tried before giving up; a dropped-distance match that
/// cannot be re-found becomes literals when at most TF_DLIT bytes long, else keeps its distance
/// (its code re-admitted).
pub const TF_RDEPTH: usize = 8;
pub const TF_SHIFT: usize = 1;
pub const TF_DLIT: usize = 8;

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
    // `tot < 4097` always holds here (at most 4095 samples); with it the loop is total even
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
        }
    }
    cls
}

/// Estimated saving (1/16 bit) of a match of length `l` at distance `d` over literals.
#[inline(always)]
pub fn gain(l: usize, d: usize) -> i32 {
    let mut c = GBASE;
    if l > 10 && l < 258 {
        c += 16 * (29 - ((l - 3) as u32).leading_zeros()) as i32;
    }
    if d > 4 {
        c += 16 * (30 - ((d - 1) as u32).leading_zeros()) as i32;
    }
    (l as i32) * (HLIT as i32) - c
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
pub fn walk<const W: usize>(s: &[u8], prev: &[u32; W], p: usize, start: usize, cap: usize, have: usize, depth: usize, gm: usize) -> (usize, usize) {
    let n = s.len();
    let mut best = have;
    let mut bd = 0usize;
    let mut bg = -1000000i32;
    let mut c = start;
    let mut k = depth;
    let mut stop = NICE;
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
                        let g = gain(l, d);
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

/// Best match at `p` longer than `have` and at least `minl` long; (0, 0) when none.
#[inline(always)]
pub fn find<const W: usize>(s: &[u8], prev: &[u32; W], p: usize, st: usize, have: usize, minl: usize, depth: usize, gm: usize) -> (usize, usize) {
    let n = s.len();
    let mut cap = n - p;
    if cap > 258 {
        cap = 258;
    }
    let mut lo = have;
    if lo + 1 < minl {
        lo = minl - 1;
    }
    let f = walk(s, prev, p, st, cap, lo, depth, gm);
    let mut l = f.0;
    if f.1 == 0 {
        l = 0;
    }
    (l, f.1)
}

/// The parse for one input class (inlined so the text classes get constant settings), with
/// H chain heads and a window table of W entries.
#[inline(always)]
pub fn run<const H: usize, const W: usize>(input: &[u8], out: &mut [u32], cls: usize) -> usize {
    let n = input.len();
    let mut nt = 0usize;
    let mut p = 0usize;
    let mut mask = 0xFFFF_FFFFu32;
    let mut minl = 4usize;
    let mut depth = T_DEPTH;
    let mut lazy = T_LAZY;
    let mut skip = T_SKIP;
    let mut skcap = SKCAP;
    if cls == 6 {
        depth = S_DEPTH;
        lazy = S_LAZY;
    }
    if cls == 5 {
        depth = P_DEPTH;
        lazy = P_LAZY;
        skip = P_SKIP;
    }
    if cls == 2 || cls == 4 {
        depth = H_DEPTH;
        lazy = H_LAZY;
        skip = H_SKIP;
        if cls == 4 {
            depth = Z_DEPTH;
            skip = Z_SKIP;
            skcap = Z_CAP;
        }
    }
    if cls == 3 {
        mask = 0xFFFF_FF00;
        minl = 3;
        depth = B_DEPTH;
        lazy = B_LAZY;
        skip = B_SKIP;
    }
    if n > 16 && cls != 0 {
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
            let hc = insert(input, &mut head, &mut prev, p, mask);
            ins = p + 1;
            let f = find(input, &prev, p, hc, 0, minl, depth, 0);
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
                    let mut ldep = LDEPTH;
                    if cls == 6 {
                        ldep = S_LDEPTH;
                    }
                    let g = find(input, &prev, q, hq, have, minl, ldep, 1);
                    if g.0 >= minl && gain(g.0, g.1) > gain(l, d) {
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
                    insert(input, &mut head, &mut prev, ins, mask);
                    ins += 1;
                }
                if STRIDE > 0 {
                    // `ins + TAIL + STRIDE < end` (ins <= end here): no sum that could overflow
                    while end - ins > TAIL + STRIDE && ins < lim {
                        insert(input, &mut head, &mut prev, ins, mask);
                        ins += STRIDE;
                    }
                }
                if ins + TAIL < end {
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

/// Every input except larger text and prose: smaller tables for small inputs.
#[inline(never)]
pub fn run_rest(input: &[u8], out: &mut [u32], cls: usize) -> usize {
    if input.len() <= SMALL {
        if cls == 1 {
            run::<HS, WS>(input, out, 1)
        } else {
            run::<HS, WS>(input, out, cls)
        }
    } else {
        run::<HN, WN>(input, out, cls)
    }
}

/// Inputs that `tf_route` sends to the tiny path: plan, then emit with re-verification; all others:
/// the engine.
pub fn parse(input: &[u8], out: &mut [u32]) -> usize {
    let kind = tf_route(input);
    if kind < 3 {
        let plan = tf_plan(input, kind);
        emit(input, &plan, out)
    } else {
        let cls = sniff(input);
        if input.len() > SMALL && cls == 1 {
            run::<HN, WN>(input, out, 1)
        } else if input.len() > SMALL && cls == 5 {
            run::<HN, WN>(input, out, 5)
        } else if input.len() > SMALL && cls == 6 {
            run::<HN, WN>(input, out, 6)
        } else {
            run_rest(input, out, cls)
        }
    }
}

// ─────────────── tiny inputs: plan + re-verify (`parse` sends inputs of at most TF_N bytes here) ───────────────
//
// Phase 2, the emission (`emit` with `check`, `mlen`, `load8`, `first_diff`, `get0`), carries the
// whole decode invariant of this path: a planned match is written only if `check` finds it in range
// and `mlen` confirms every byte; anything else becomes literals. Phase 1, the planner (`tf_plan` and
// everything it calls), is search: it only has to be total (no panic, terminates) and may return a
// plan of any length and contents (`get0` reads 0 past its end).
// Plan format: a token list; entry k describes the k-th planned token: `len + 512 * dist` for a
// match, and any entry that `check` rejects stands for `max(1, len)` literals (`len = v % 512`), so
// `run` (dist 0, 1 <= run <= 511) is a run of `run` literals and 0 a single literal. A rejected
// match therefore costs literals over its planned length and the plan stays aligned.

/// The eight bytes at `p` as one big-endian number (byte `p` most significant), or 0 when fewer
/// than eight remain (Horner form; one load plus `bswap` once inlined).
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

/// How many bytes agree at `a` and `b`, up to `cap` (needs `a + cap <= n` and `b + cap <= n`):
/// eight at a time, the first mismatching word resolved by `first_diff`, the last `cap % 8` bytes
/// one at a time. The only function whose result the emission trusts (through `check`).
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
#[inline(always)]
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
#[inline(always)]
pub fn get0(v: &[u32], i: usize) -> u32 {
    if i < v.len() {
        v[i]
    } else {
        0
    }
}

/// `v[i] = x` when `i` is in range, nothing otherwise: a write that cannot panic.
#[inline(always)]
pub fn set_in(v: &mut [u32], i: usize, x: u32) {
    if i < v.len() {
        v[i] = x;
    }
}

/// Phase 2: walk the plan from 0 (entry `k` for the `k`-th planned token); a planned match is
/// written only if `check` accepts it, else its bytes become literals (`owed`), so the plan stays aligned.
#[inline(never)]
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

// ═══════════════ tiny inputs: the symbol-frugal planner (search only) ═══════════════
//
// The validator's encoder pays per block about 1.3 us for every live literal/length symbol and about
// 1 us for every live distance code (two or more live; a single live distance code costs nothing), on
// top of a few ns per token. A tiny input is one block, so its encode time is mostly this per-symbol
// overhead. The literal alphabet is fixed by the input (every distinct byte is a literal once), so the
// planner works on the length and distance codes:
//  1. `tf_class`: binary (a zero byte or many control bytes in ~TF_SAMPLE strided bytes), structured
//     text (>= 1/TF_SDIG digits) or text.
//  2. `tf_stage1`: a lazy hash-chain parse into a token list (u16 position chains; distance 1, then the
//     previous distance, then the chain; backward extension over pending literals; the pending match is
//     folded into a new one when its bytes also match at the new distance; the engine's bit-saving
//     estimate for the lazy step) and a histogram of length codes and distance codes. Binaries
//     (TF_BDEPTH 0): distance 1 only, so zero runs are one literal plus distance-1 matches and a single
//     distance code is live.
//  3. `tf_keep`: a length code is kept when used >= TF_KL (binaries TF_BKL) times, a distance code
//     >= TF_KD (TF_BKD) times.
//  4. `tf_rewrite`: consecutive matches at one distance are one span, re-split into kept lengths
//     (`tf_piece`: one kept length, many maximal ones, or two kept lengths summing to the rest); a match
//     whose distance code was dropped is re-found at a kept distance (its chain, the two most recent
//     distances, distance 1; after up to TF_SHIFT single literals), else written as literals when at
//     most TF_DLIT bytes. Online re-admission: a span the kept lengths would leave >= 3 bytes uncovered
//     re-admits its own codes; a longer unfindable match keeps its distance and re-admits that code.
// The plan is a token list: `len + 512 * dist` for a match, `run` (dist 0, run <= 511) for a literal
// run. Nothing here is trusted: `emit` re-checks every planned match, so these functions only have to
// be total. Each function keeps its decisions in one place at its end (larger steps are chains of
// small helpers); arithmetic that a guard does not bound wraps.

/// Byte `i` of `s` (0 when out of range).
#[inline(always)]
pub fn tf_at(s: &[u8], i: usize) -> u8 {
    if i < s.len() {
        s[i]
    } else {
        0
    }
}

/// Eight bytes at `i`, first byte most significant (0 unless all eight are in range).
#[inline(always)]
pub fn tf_w8(s: &[u8], i: usize) -> u64 {
    let n = s.len();
    if n >= 8 && i <= n - 8 {
        let mut v = s[i] as u64;
        v = v * 256 + s[i + 1] as u64;
        v = v * 256 + s[i + 2] as u64;
        v = v * 256 + s[i + 3] as u64;
        v = v * 256 + s[i + 4] as u64;
        v = v * 256 + s[i + 5] as u64;
        v = v * 256 + s[i + 6] as u64;
        v * 256 + s[i + 7] as u64
    } else {
        0
    }
}

/// Four bytes at `i`, first byte most significant (0 unless all four are in range).
#[inline(always)]
pub fn tf_w4(s: &[u8], i: usize) -> u32 {
    let n = s.len();
    if n >= 4 && i <= n - 4 {
        let mut v = s[i] as u32;
        v = v * 256 + s[i + 1] as u32;
        v = v * 256 + s[i + 2] as u32;
        v * 256 + s[i + 3] as u32
    } else {
        0
    }
}

/// The smaller of `a` and `b`.
#[inline(always)]
pub fn tf_min(a: usize, b: usize) -> usize {
    if a < b {
        a
    } else {
        b
    }
}

/// The larger of `a` and `b`.
#[inline(always)]
pub fn tf_max(a: usize, b: usize) -> usize {
    if a < b {
        b
    } else {
        a
    }
}

/// `x >> sh`, and 0 for `sh` >= 32 (the counts shifted here stay below 2^32).
#[inline(always)]
pub fn tf_shr(x: usize, sh: usize) -> usize {
    if sh < 32 {
        x >> sh
    } else {
        0
    }
}

/// Chain slot of the key at `p` (four bytes; three with mask 0xFFFF_FF00).
#[inline(always)]
pub fn tf_slot(s: &[u8], p: usize, mask: u32) -> usize {
    let k = (tf_w4(s, p) & mask) as u64;
    (k.wrapping_mul(0x9E37_79B9_7F4A_7C15) >> (64 - TF_HB)) as usize % TF_HN
}

/// Slot (0..=28) of the length code of `l` in `hist`/`keep` (lengths 3..=258; any `l` is allowed).
#[inline(always)]
pub fn tf_lslot(l: usize) -> usize {
    (TF_LSYM[l % 512] as usize) % 64
}

/// Slot (32..=61) of the distance code of `d` in `hist`/`keep` (distances 1..=32768; any `d`).
#[inline(always)]
pub fn tf_dslot(d: usize) -> usize {
    let dm = d.wrapping_sub(1);
    let idx = if dm < 256 { dm } else { (dm / 128).wrapping_add(256) };
    (32 + TF_DSYM[idx % 512] as usize) % 64
}

/// How many bytes agree at `a` and `b` (a < b), at most `cap` (search only: any arguments are allowed;
/// the shape of the proven `mlen`, so the word loads compile to one load each).
#[inline(always)]
pub fn tf_common(s: &[u8], a: usize, b: usize, cap: usize) -> usize {
    let n = s.len();
    if a >= b || b >= n {
        return 0;
    }
    let lim = tf_min(n - b, cap);
    let mut l = 0usize;
    while lim - l >= 8 {
        let x = tf_w8(s, a + l);
        let y = tf_w8(s, b + l);
        if x != y {
            return l + first_diff(x, y);
        }
        l += 8;
    }
    while l < lim && s[a + l] == s[b + l] {
        l += 1;
    }
    l
}

/// Append `x` (guarded push).
#[inline(always)]
pub fn tf_push(v: &mut Vec<u32>, x: u32) {
    if v.len() < v.len().saturating_add(1) {
        v.push(x);
    }
}

/// Chain position `p` (u16 positions); returns the previous head of its slot (where the search at `p`
/// starts).
#[inline(always)]
pub fn tf_insert(s: &[u8], head: &mut [u16; TF_HN], prev: &mut [u16; TF_WN], p: usize, mask: u32) -> usize {
    let h = tf_slot(s, p, mask);
    let old = head[h];
    prev[p % TF_WN] = old;
    head[h] = p as u16;
    old as usize
}

/// Chain the positions `from..to` (none when `from >= to`); returns the larger of the two.
#[inline(always)]
pub fn tf_chain(s: &[u8], head: &mut [u16; TF_HN], prev: &mut [u16; TF_WN], from: usize, to: usize, mask: u32) -> usize {
    let mut i = from;
    while i < to {
        tf_insert(s, head, prev, i, mask);
        i += 1;
    }
    i
}

/// Is `c` a possible source for `p` (before it and at most 32768 back)?
#[inline(always)]
pub fn tf_near(c: usize, p: usize) -> bool {
    c < p && p - c <= 32768
}

/// The length of the match at `p` from `c` (at most `cap`) when it beats `best`, else `best`; the byte
/// where it would beat `best` is compared first.
#[inline(always)]
pub fn tf_try(s: &[u8], c: usize, p: usize, cap: usize, best: usize) -> usize {
    if tf_at(s, c.wrapping_add(best)) == tf_at(s, p.wrapping_add(best)) {
        let l = tf_common(s, c, p, cap);
        if l > best {
            return l;
        }
    }
    best
}

/// Longest match at `p` longer than `have` on the chain from position `start` (at most `depth` steps,
/// within 32768 bytes): (length, distance); distance 0 when none is longer.
#[inline(always)]
pub fn tf_walk(s: &[u8], prev: &[u16; TF_WN], p: usize, start: usize, cap: usize, have: usize, depth: usize) -> (usize, usize) {
    let mut best = have;
    let mut bd = 0usize;
    let mut c = start;
    let mut k = depth;
    while k > 0 {
        k -= 1;
        if tf_near(c, p) {
            let l = tf_try(s, c, p, cap, best);
            if l > best {
                best = l;
                bd = p.wrapping_sub(c);
                if l >= TF_NICE || l >= cap {
                    k = 0;
                }
            }
            let nx = prev[c % TF_WN] as usize;
            if nx < c {
                c = nx;
            } else {
                k = 0;
            }
        } else {
            k = 0;
        }
    }
    (best, bd)
}

/// The longest match `p` allows: min(n - p, 258), 0 at or past the end.
#[inline(always)]
pub fn tf_cap(n: usize, p: usize) -> usize {
    if p < n {
        tf_min(n - p, 258)
    } else {
        0
    }
}

/// The length a match has to beat: `have`, raised to `minl - 1`.
#[inline(always)]
pub fn tf_floor(have: usize, minl: usize) -> usize {
    if minl >= 1 && have < minl - 1 {
        minl - 1
    } else {
        have
    }
}

/// Distance 1 at `p` (when `rle` = 1 and the byte before `p` repeats there): (best, bd) of the longer.
#[inline(always)]
pub fn tf_cand1(s: &[u8], p: usize, cap: usize, best: usize, bd: usize, rle: usize) -> (usize, usize) {
    if rle == 1 && p >= 1 && best < cap && tf_at(s, p - 1) == tf_at(s, p) {
        let l = tf_try(s, p - 1, p, cap, best);
        if l > best {
            return (l, 1);
        }
    }
    (best, bd)
}

/// The previous distance `rep` (> 1) at `p`, when `on`: (best, bd) of the longer.
#[inline(always)]
pub fn tf_cand_rep(s: &[u8], p: usize, rep: usize, cap: usize, best: usize, bd: usize, on: bool) -> (usize, usize) {
    if on && rep > 1 && rep <= p && rep <= 32768 && best < cap {
        let l = tf_try(s, p - rep, p, cap, best);
        if l > best {
            return (l, rep);
        }
    }
    (best, bd)
}

/// The chain from `ci` (`depth` steps) when `best` is below `cap` and TF_NICE: (best, bd) of the longer.
#[inline(always)]
pub fn tf_cand_chain(s: &[u8], prev: &[u16; TF_WN], p: usize, ci: usize, cap: usize, best: usize, bd: usize, depth: usize) -> (usize, usize) {
    if best < cap && best < TF_NICE {
        let (wl, wd) = tf_walk(s, prev, p, ci, cap, best, depth);
        if wd != 0 {
            return (wl, wd);
        }
    }
    (best, bd)
}

/// Best match at `p` longer than `have` and at least `minl` long: distance 1, the previous distance
/// `rep`, then the chain from `ci` (each must be longer than the best so far, so on equal length the
/// earlier and cheaper distance stays). (0, 0) when none.
#[inline(always)]
pub fn tf_find(s: &[u8], prev: &[u16; TF_WN], p: usize, ci: usize, rep: usize, minl: usize, depth: usize, have: usize, rle: usize) -> (usize, usize) {
    let cap = tf_cap(s.len(), p);
    let b0 = tf_floor(have, minl);
    let (b1, d1) = tf_cand1(s, p, cap, b0, 0, rle);
    let (b2, d2) = tf_cand_rep(s, p, rep, cap, b1, d1, TF_REP == 1);
    let (b3, d3) = tf_cand_chain(s, prev, p, ci, cap, b2, d2, depth);
    let (b4, d4) = tf_cand_rep(s, p, rep, cap, b3, d3, TF_REP == 2);
    if d4 == 0 {
        (0, 0)
    } else {
        (b4, d4)
    }
}

/// Append `run` literals as entries of at most 511.
pub fn tf_lits(plan: &mut Vec<u32>, run: usize) {
    let mut r = run;
    while r > 0 {
        let k = tf_min(r, 511);
        tf_push(plan, k as u32);
        r -= k;
    }
}

/// Append `run` literals, then the match (l, d).
#[inline(always)]
pub fn tf_put(plan: &mut Vec<u32>, run: usize, l: usize, d: usize) {
    tf_lits(plan, run);
    tf_push(plan, (l as u32).wrapping_add((d as u32).wrapping_mul(512)));
}

/// 1 for a zero byte.
#[inline(always)]
pub fn tf_iszero(b: u8) -> u32 {
    if b == 0 {
        1
    } else {
        0
    }
}

/// 1 for a control byte (below 9, or 14..=31).
#[inline(always)]
pub fn tf_isctl(b: u8) -> u32 {
    if b < 9 || (b > 13 && b < 32) {
        1
    } else {
        0
    }
}

/// 1 for a decimal digit.
#[inline(always)]
pub fn tf_isdig(b: u8) -> u32 {
    if b >= 48 && b <= 57 {
        1
    } else {
        0
    }
}

/// Input kind from at most ~TF_SAMPLE strided bytes: 2 binary (a zero byte, or more than 1/32 control
/// bytes), 1 structured text (at least 1/TF_SDIG digits), 0 other text.
pub fn tf_class(s: &[u8]) -> usize {
    let n = s.len();
    let step = (n / TF_SAMPLE) | 1;
    let mut i = 0usize;
    let mut tot = 0u32;
    let mut ctl = 0u32;
    let mut zero = 0u32;
    let mut dig = 0u32;
    while i < n && tot < 65536 {
        let b = s[i];
        zero = zero.wrapping_add(tf_iszero(b));
        ctl = ctl.wrapping_add(tf_isctl(b));
        dig = dig.wrapping_add(tf_isdig(b));
        tot += 1;
        i = i.wrapping_add(step);
    }
    if zero > 0 || ctl > tot / 32 {
        2
    } else if dig >= tot / TF_SDIG {
        1
    } else {
        0
    }
}

/// Stage-1 settings of kind `cls`: (key mask, shortest match, chain steps, lazy limit, skip shift,
/// distance 1 first).
#[inline(always)]
pub fn tf_cfg(cls: usize) -> (u32, usize, usize, usize, usize, usize) {
    if cls == 2 {
        (0xFFFF_FF00, 3, TF_BDEPTH, TF_BLAZY, TF_BSKIP, 1)
    } else if cls == 1 {
        (0xFFFF_FFFF, 4, TF_SDEPTH, TF_SLAZY, TF_SSKIP, TF_TRLE)
    } else {
        (0xFFFF_FFFF, 4, TF_TDEPTH, TF_TLAZY, TF_TSKIP, TF_TRLE)
    }
}

/// Does a run of four equal bytes start at `p` (the byte before `p` differs)?
#[inline(always)]
pub fn tf_run4(s: &[u8], p: usize) -> bool {
    let w = tf_w4(s, p);
    w % 16777216 == w / 256 && tf_at(s, p.wrapping_sub(1)) != tf_at(s, p) && p >= 1
}

/// The first candidate at `p`: none where a run starts (TF_RUNSKIP, distance-1-first kinds; the next
/// position takes distance 1), else `tf_find`.
#[inline(always)]
pub fn tf_first_cand(s: &[u8], prev: &[u16; TF_WN], p: usize, ci: usize, rep: usize, minl: usize, depth: usize, rle: usize) -> (usize, usize) {
    if TF_RUNSKIP == 1 && rle == 1 && tf_run4(s, p) {
        (0, 0)
    } else {
        tf_find(s, prev, p, ci, rep, minl, depth, 0, rle)
    }
}

/// Is the match of length `l` found at `p` taken (at least `minl` long, inside the input)?
#[inline(always)]
pub fn tf_take(l: usize, minl: usize, n: usize, p: usize) -> bool {
    l >= minl && p <= n && l <= n - p
}

/// Estimated saving (1/16 bit) of a match (l, d) over literals: the engine's `gain` (identical for
/// 3 <= l <= 258, 1 <= d <= 32768), with wrapping arithmetic.
#[inline(always)]
pub fn tf_gain(l: usize, d: usize) -> i32 {
    let mut c = GBASE;
    if l > 10 && l < 258 {
        let z = ((l - 3) as u32).leading_zeros();
        c = c.wrapping_add(16i32.wrapping_mul(29u32.wrapping_sub(z) as i32));
    }
    if d > 4 {
        let z = ((d - 1) as u32).leading_zeros();
        c = c.wrapping_add(16i32.wrapping_mul(30u32.wrapping_sub(z) as i32));
    }
    (l as i32).wrapping_mul(HLIT as i32).wrapping_sub(c)
}

/// Does the match (g0, g1) found at `q` (one after the current match's position) beat (l, d)?
#[inline(always)]
pub fn tf_better(g0: usize, g1: usize, l: usize, d: usize, n: usize, q: usize) -> bool {
    g1 != 0 && g0 >= l && q <= n && g0 <= n - q && tf_gain(g0, g1) > tf_gain(l, d)
}

/// Lazy steps while the match is shorter than `lazy` and TF_NICE: a better match one position later
/// replaces it (one more pending literal). The state m = [p, l, d, run, ins] is read and written back
/// (a function that changes tables returns no tuple: the proof's `step*` takes flat results).
pub fn tf_lazy(s: &[u8], head: &mut [u16; TF_HN], prev: &mut [u16; TF_WN], n: usize, lim: usize, rep: usize, mask: u32, minl: usize, depth: usize, lazy: usize, rle: usize, m: &mut [usize; 5]) {
    let mut p = m[0];
    let mut l = m[1];
    let mut d = m[2];
    let mut run = m[3];
    let mut ins = m[4];
    let mut go = 1u32;
    while go == 1 && l < lazy && l < TF_NICE && p < lim && lim - p > 1 {
        let q = p + 1;
        let cq = tf_insert(s, head, prev, q, mask);
        ins = q + 1;
        let g = tf_find(s, prev, q, cq, rep, minl, depth, l.saturating_sub(1), rle);
        if tf_better(g.0, g.1, l, d, n, q) {
            run = run.wrapping_add(1);
            p = q;
            l = g.0;
            d = g.1;
        } else {
            go = 0;
        }
    }
    m[0] = p;
    m[1] = l;
    m[2] = d;
    m[3] = run;
    m[4] = ins;
}

/// Extend the match (l, d) at `p` backwards over the pending literals (TF_BACK): (p, l, run).
pub fn tf_back(s: &[u8], p0: usize, l0: usize, d: usize, run0: usize) -> (usize, usize, usize) {
    let mut p = p0;
    let mut l = l0;
    let mut run = run0;
    while TF_BACK == 1 && run > 0 && l < 258 && d < p && tf_at(s, p - 1) == tf_at(s, p - 1 - d) {
        p -= 1;
        l += 1;
        run -= 1;
    }
    (p, l, run)
}

/// Fold the pending match (pl, pd) into the match (l, d) at `p` when no literal is between them, the
/// sum is a legal length and its bytes also match at `d` (TF_FOLD): (p, l, pd).
#[inline(always)]
pub fn tf_fold(s: &[u8], p: usize, l: usize, d: usize, run: usize, pl: usize, pd: usize) -> (usize, usize, usize) {
    if TF_FOLD == 1 && run == 0 && pd != 0 && pl <= p && pl <= 258 && l <= 258 - pl && d <= p - pl && tf_common(s, p - pl - d, p - pl, pl) == pl {
        (p - pl, l + pl, 0)
    } else {
        (p, l, pd)
    }
}

/// Write the pending match (pl, pd) when there is one (pd != 0) and count its codes.
#[inline(always)]
pub fn tf_flush(tk: &mut Vec<u32>, hist: &mut [u32; 64], pl: usize, pd: usize) {
    if pd != 0 {
        tf_push(tk, (pl as u32).wrapping_add((pd as u32).wrapping_mul(512)));
        let lc = tf_lslot(pl);
        hist[lc] = hist[lc].wrapping_add(1);
        let dc = tf_dslot(pd);
        hist[dc] = hist[dc].wrapping_add(1);
    }
}

/// Where the chained tail of a match ending at `end` starts: end - TF_TAIL when that is after `ins`.
#[inline(always)]
pub fn tf_tailfrom(ins: usize, end: usize) -> usize {
    if end >= TF_TAIL && ins < end - TF_TAIL {
        end - TF_TAIL
    } else {
        ins
    }
}

/// Chain the positions of a match ending at `end`: TF_INS from `ins` on and the last TF_TAIL (never at
/// or past `lim`); returns the next position to chain (at least `end`).
#[inline(always)]
pub fn tf_ins_match(s: &[u8], head: &mut [u16; TF_HN], prev: &mut [u16; TF_WN], ins: usize, end: usize, lim: usize, mask: u32) -> usize {
    let stop = tf_min(tf_min(end, ins.wrapping_add(TF_INS)), lim);
    let i1 = tf_chain(s, head, prev, ins, stop, mask);
    let i2 = tf_tailfrom(i1, end);
    let i3 = tf_chain(s, head, prev, i2, tf_min(end, lim), mask);
    tf_max(i3, end)
}

/// A match (l, d) taken at `p`: lazy steps, backward extension, the fold of the pending match (pl, pd);
/// then the pending match and the literals before the new one are written and the new match's
/// positions chained. Writes o = [end, l, d, ins]: the new match is the pending one now.
pub fn tf_s1_match(s: &[u8], tk: &mut Vec<u32>, head: &mut [u16; TF_HN], prev: &mut [u16; TF_WN], hist: &mut [u32; 64], n: usize, lim: usize, p: usize, l: usize, d: usize, run: usize, pl: usize, pd: usize, ins: usize, rep: usize, mask: u32, minl: usize, depth: usize, lazy: usize, rle: usize, o: &mut [usize; 4]) {
    let mut m = [0usize; 5];
    m[0] = p;
    m[1] = l;
    m[2] = d;
    m[3] = run;
    m[4] = ins;
    tf_lazy(s, head, prev, n, lim, rep, mask, minl, depth, lazy, rle, &mut m);
    let d1 = m[2];
    let (p2, l2, run2) = tf_back(s, m[0], m[1], d1, m[3]);
    let (p3, l3, pd3) = tf_fold(s, p2, l2, d1, run2, pl, pd);
    tf_flush(tk, hist, pl, pd3);
    tf_lits(tk, run2);
    let end = p3.wrapping_add(l3);
    let ins2 = tf_ins_match(s, head, prev, m[4], end, lim, mask);
    o[0] = end;
    o[1] = l3;
    o[2] = d1;
    o[3] = ins2;
}

/// Positions skipped after `miss` misses in a row (`p` the next position): miss >> skip, at most
/// TF_SKCAP and lim - p, none at `lim`.
#[inline(always)]
pub fn tf_skipn(p: usize, lim: usize, miss: usize, skip: usize) -> usize {
    let st = tf_min(tf_shr(miss, skip), TF_SKCAP);
    if p < lim {
        tf_min(st, lim - p)
    } else {
        0
    }
}

/// The literals pending at the end: `run` plus everything from `p` on.
#[inline(always)]
pub fn tf_rest(n: usize, p: usize, run: usize) -> usize {
    if p < n {
        run.wrapping_add(n - p)
    } else {
        run
    }
}

/// The lazy parse proper (lim = n - 8), then the pending match and the literals left at the end.
pub fn tf_s1_loop(s: &[u8], tk: &mut Vec<u32>, head: &mut [u16; TF_HN], prev: &mut [u16; TF_WN], hist: &mut [u32; 64], n: usize, lim: usize, mask: u32, minl: usize, depth: usize, lazy: usize, skip: usize, rle: usize) {
    let mut p = 0usize;
    let mut run = 0usize;
    let mut pl = 0usize;
    let mut pd = 0usize;
    let mut ins = 0usize;
    let mut miss = 0usize;
    let mut rep = 0usize;
    let mut fuel = n;
    while p < lim && fuel > 0 {
        fuel -= 1;
        tf_chain(s, head, prev, ins, p, mask);
        let ci = tf_insert(s, head, prev, p, mask);
        let (fl, fd) = tf_first_cand(s, prev, p, ci, rep, minl, depth, rle);
        if tf_take(fl, minl, n, p) {
            let mut o = [0usize; 4];
            tf_s1_match(s, tk, head, prev, hist, n, lim, p, fl, fd, run, pl, pd, p + 1, rep, mask, minl, depth, lazy, rle, &mut o);
            p = o[0];
            run = 0;
            pl = o[1];
            pd = o[2];
            rep = o[2];
            ins = o[3];
            miss = 0;
        } else {
            let q = p + 1;
            miss = miss.wrapping_add(1);
            let k = tf_skipn(q, lim, miss, skip);
            run = run.wrapping_add(1).wrapping_add(k);
            p = q.wrapping_add(k);
            ins = tf_max(q, p);
        }
    }
    let rest = tf_rest(n, p, run);
    tf_flush(tk, hist, pl, pd);
    tf_lits(tk, rest);
}

/// Phase 1a: the lazy parse into `tk` (chains left in `head`/`prev` for the rewrite), length codes
/// counted in hist[0..29], distance codes in hist[32..62].
pub fn tf_stage1(s: &[u8], tk: &mut Vec<u32>, head: &mut [u16; TF_HN], prev: &mut [u16; TF_WN], hist: &mut [u32; 64], cls: usize) {
    let n = s.len();
    if n > 16 {
        let (mask, minl, depth, lazy, skip, rle) = tf_cfg(cls);
        tf_s1_loop(s, tk, head, prev, hist, n, n - 8, mask, minl, depth, lazy, skip, rle);
    } else {
        tf_lits(tk, n);
    }
}

/// Threshold of slot `c`: `kl` for length codes (c < 32), `kd` for distance codes.
#[inline(always)]
pub fn tf_thr(c: usize, kl: u32, kd: u32) -> u32 {
    if c < 32 {
        kl
    } else {
        kd
    }
}

/// 1 when a code used `h` times is kept under threshold `k`.
#[inline(always)]
pub fn tf_kept(h: u32, k: u32) -> u8 {
    if h > 0 && h >= k {
        1
    } else {
        0
    }
}

/// Phase 1b: kept codes (keep[0..29] lengths used at least `kl` times, keep[32..62] distances used at
/// least `kd` times).
pub fn tf_keep(hist: &[u32; 64], keep: &mut [u8; 64], kl: u32, kd: u32) {
    let mut c = 0usize;
    while c < 64 {
        keep[c] = tf_kept(hist[c], tf_thr(c, kl, kd));
        c += 1;
    }
}

/// `x` if it is the first kept length (`kx` and none before), else `kmin`.
#[inline(always)]
pub fn tf_first(kmin: usize, x: usize, kx: bool) -> usize {
    if kx && kmin == 0 {
        x
    } else {
        kmin
    }
}

/// Is the length `x` (>= 3) of a kept code?
#[inline(always)]
pub fn tf_kx(keep: &[u8; 64], x: usize) -> bool {
    x >= 3 && keep[tf_lslot(x)] == 1
}

/// `x` when `kx`, else `cur`.
#[inline(always)]
pub fn tf_cur(cur: u16, x: usize, kx: bool) -> u16 {
    if kx {
        x as u16
    } else {
        cur
    }
}

/// lle[x] = the largest length <= x whose code is kept (0 when none); returns the smallest kept length
/// (0 when none).
pub fn tf_lle(keep: &[u8; 64], lle: &mut [u16; 260]) -> usize {
    let mut x = 0usize;
    let mut cur = 0u16;
    let mut kmin = 0usize;
    while x < 259 {
        let kx = tf_kx(keep, x);
        cur = tf_cur(cur, x, kx);
        kmin = tf_first(kmin, x, kx);
        lle[x] = cur;
        x += 1;
    }
    kmin
}

/// Length code `c`, when kept: the first of two kept lengths summing to `x` whose first piece has code
/// `c` (3 <= each <= 258), else 0.
#[inline(always)]
pub fn tf_pair1(x: usize, c: usize, keep: &[u8; 64], lle: &[u16; 260]) -> usize {
    if keep[c % 64] == 1 {
        let lo = TF_LBASE[c % 32] as usize;
        let hi = TF_LTOP[c % 32] as usize;
        if x >= lo + 3 {
            let b = lle[tf_min(x - lo, 258) % 260] as usize;
            if b >= 3 && b + hi >= x && b + lo <= x {
                return x - b;
            }
        }
    }
    0
}

/// Two kept lengths summing to `x` (3 <= each <= 258): the first one, or 0 when there is none.
pub fn tf_pair(x: usize, keep: &[u8; 64], lle: &[u16; 260]) -> usize {
    let mut c = 29usize;
    let mut a = 0usize;
    while c > 0 && a == 0 {
        c -= 1;
        a = tf_pair1(x, c, keep, lle);
    }
    a
}

/// The largest kept length that leaves at least the smallest one (when rem > kmin + 3), else the
/// largest kept length <= rem (lengths above 258 count as 258).
#[inline(always)]
pub fn tf_lastpiece(rem: usize, lle: &[u16; 260], kmin: usize) -> usize {
    let y = if rem > 3 && rem - 3 > kmin { rem - kmin } else { rem };
    lle[tf_min(y, 258) % 260] as usize
}

/// `tf_piece` before its range check.
#[inline(always)]
pub fn tf_piece0(rem: usize, keep: &[u8; 64], lle: &[u16; 260], kmin: usize) -> usize {
    let top = lle[258] as usize;
    if top < 3 {
        return 0;
    }
    if rem <= 258 && keep[tf_lslot(rem)] == 1 {
        return rem;
    }
    if rem > top + top {
        return top;
    }
    let a = tf_pair(rem, keep, lle);
    if a != 0 {
        return a;
    }
    tf_lastpiece(rem, lle, kmin)
}

/// The next piece when `rem` bytes are written in kept lengths (0 when no kept length fits): `rem`
/// when kept, the largest kept length while more than two of them remain, a kept pair, else the
/// largest kept length leaving at least the smallest one.
#[inline(always)]
pub fn tf_piece(rem: usize, keep: &[u8; 64], lle: &[u16; 260], kmin: usize) -> usize {
    let a = tf_piece0(rem, keep, lle, kmin);
    if a > rem {
        0
    } else {
        a
    }
}

/// Bytes of `l` that no kept piece would cover (dry run of `tf_split`).
pub fn tf_left(l: usize, keep: &[u8; 64], lle: &[u16; 260], kmin: usize) -> usize {
    let mut rem = l;
    let mut fuel = l;
    while rem >= 3 && fuel > 0 {
        fuel -= 1;
        let a = tf_piece(rem, keep, lle, kmin);
        if a >= 3 {
            rem -= a;
        } else {
            fuel = 0;
        }
    }
    rem
}

/// Write `l` bytes at distance d as pieces of kept lengths; `run` literals are pending before it;
/// returns the literals pending after it (bytes no piece covers become literals).
pub fn tf_split(plan: &mut Vec<u32>, run: usize, l: usize, d: usize, keep: &[u8; 64], lle: &[u16; 260], kmin: usize) -> usize {
    let mut r = run;
    let mut rem = l;
    let mut fuel = l;
    while rem >= 3 && fuel > 0 {
        fuel -= 1;
        let a = tf_piece(rem, keep, lle, kmin);
        if a >= 3 {
            tf_put(plan, r, a, d);
            r = 0;
            rem -= a;
        } else {
            fuel = 0;
        }
    }
    r.wrapping_add(rem)
}

/// Re-admit the code of a remainder `r` (>= 3).
#[inline(always)]
pub fn tf_admit1(keep: &mut [u8; 64], r: usize) {
    if r >= 3 {
        keep[tf_lslot(r)] = 1;
    }
}

/// Re-admit the codes of `l` bytes written as 258-byte pieces and a remainder (when the kept codes
/// would leave bytes uncovered); returns the new smallest kept length.
pub fn tf_admit(l: usize, keep: &mut [u8; 64], lle: &mut [u16; 260]) -> usize {
    let mut r = l;
    while r > 258 {
        keep[28] = 1;
        r -= 258;
    }
    tf_admit1(keep, r);
    tf_lle(keep, lle)
}

/// `tf_split` with its state in st (st[0] = pending literals, in and out; st[1] = smallest kept length).
pub fn tf_split_st(plan: &mut Vec<u32>, st: &mut [usize; 4], l: usize, d: usize, keep: &[u8; 64], lle: &[u16; 260]) {
    let r = tf_split(plan, st[0], l, d, keep, lle, st[1]);
    st[0] = r;
}

/// Before writing `l` bytes in kept lengths: re-admit their own codes when the kept lengths would leave
/// at least 3 bytes uncovered (st[1] = the new smallest kept length).
pub fn tf_fit_st(l: usize, keep: &mut [u8; 64], lle: &mut [u16; 260], st: &mut [usize; 4]) {
    if tf_left(l, keep, lle, st[1]) >= 3 {
        let k = tf_admit(l, keep, lle);
        st[1] = k;
    }
}

/// Distance `d` at `p` when it is in reach and its code is kept: (best, bd) of the longer (<= cap).
#[inline(always)]
pub fn tf_rcand(s: &[u8], keep: &[u8; 64], p: usize, d: usize, cap: usize, best: usize, bd: usize) -> (usize, usize) {
    if d >= 1 && d <= p && d <= 32768 && keep[tf_dslot(d)] == 1 {
        let l = tf_common(s, p - d, p, cap);
        if l > best {
            return (l, d);
        }
    }
    (best, bd)
}

/// The chain candidate `c` (before `p`, in reach) when its distance code is kept: (best, bd) of the
/// longer.
#[inline(always)]
pub fn tf_rtry(s: &[u8], keep: &[u8; 64], c: usize, p: usize, cap: usize, best: usize, bd: usize) -> (usize, usize) {
    let d = p.wrapping_sub(c);
    if keep[tf_dslot(d)] == 1 {
        let l = tf_try(s, c, p, cap, best);
        if l > best {
            return (l, d);
        }
    }
    (best, bd)
}

/// TF_RDEPTH steps on the chain of `p` for a longer match at a kept distance: (best, bd).
pub fn tf_rwalk(s: &[u8], prev: &[u16; TF_WN], keep: &[u8; 64], p: usize, cap: usize, best0: usize, bd0: usize) -> (usize, usize) {
    let mut best = best0;
    let mut bd = bd0;
    let mut c = prev[p % TF_WN] as usize;
    let mut k = TF_RDEPTH;
    while k > 0 && best < cap {
        k -= 1;
        if tf_near(c, p) {
            let r = tf_rtry(s, keep, c, p, cap, best, bd);
            best = r.0;
            bd = r.1;
            let nx = prev[c % TF_WN] as usize;
            if nx < c {
                c = nx;
            } else {
                k = 0;
            }
        } else {
            k = 0;
        }
    }
    (best, bd)
}

/// The chain step of `tf_refind` (when `chain` = 1).
#[inline(always)]
pub fn tf_rchain(s: &[u8], prev: &[u16; TF_WN], keep: &[u8; 64], p: usize, chain: usize, cap: usize, best: usize, bd: usize) -> (usize, usize) {
    if chain == 1 {
        tf_rwalk(s, prev, keep, p, cap, best, bd)
    } else {
        (best, bd)
    }
}

/// Longest match at `p` (at most `cap` bytes) at a kept distance: the distances `r1`, `r2`, 1, then
/// (when `chain` = 1) the chain of `p` (TF_RDEPTH steps): (length, distance), (0, 0) when none.
pub fn tf_refind(s: &[u8], prev: &[u16; TF_WN], keep: &[u8; 64], p: usize, chain: usize, cap: usize, r1: usize, r2: usize) -> (usize, usize) {
    let a = tf_rcand(s, keep, p, r1, cap, 0, 0);
    let b = tf_rcand(s, keep, p, r2, cap, a.0, a.1);
    let c = tf_rcand(s, keep, p, 1, cap, b.0, b.1);
    let w = tf_rchain(s, prev, keep, p, chain, cap, c.0, c.1);
    if w.0 < 3 {
        (0, 0)
    } else {
        w
    }
}

/// Remember distance `d` as the most recent one (rd[0..4]).
#[inline(always)]
pub fn tf_note(rd: &mut [usize; 4], d: usize) {
    if rd[0] != d {
        rd[3] = rd[2];
        rd[2] = rd[1];
        rd[1] = rd[0];
        rd[0] = d;
    }
}

/// Write the span of `l` bytes at kept distance d: one kept length as is, else kept pieces (re-admitting
/// the span's own codes first when the kept lengths would leave bytes uncovered).
pub fn tf_span(plan: &mut Vec<u32>, st: &mut [usize; 4], l: usize, d: usize, keep: &mut [u8; 64], lle: &mut [u16; 260]) {
    if l <= 258 && keep[tf_lslot(l)] == 1 {
        tf_put(plan, st[0], l, d);
        st[0] = 0;
    } else {
        tf_fit_st(l, keep, lle, st);
        tf_split_st(plan, st, l, d, keep, lle);
    }
}

/// What `tf_redo` does with a re-find of length `fl` when `rem` bytes remain (`shift` literal tries
/// left): 0 take it, 1 one literal, 2 the original distance, 3 literals.
#[inline(always)]
pub fn tf_act(fl: usize, rem: usize, shift: usize) -> usize {
    if fl >= 3 && fl <= rem {
        0
    } else if shift > 0 {
        1
    } else if rem > TF_DLIT {
        2
    } else {
        3
    }
}

/// One step of `tf_redo` (see `tf_act`).
pub fn tf_step(plan: &mut Vec<u32>, st: &mut [usize; 4], rd: &mut [usize; 4], keep: &mut [u8; 64], lle: &mut [u16; 260], act: usize, fl: usize, fd: usize, rem: usize, d: usize) {
    if act == 0 {
        tf_fit_st(fl, keep, lle, st);
        tf_split_st(plan, st, fl, fd, keep, lle);
        tf_note(rd, fd);
    } else if act == 1 {
        st[0] = st[0].wrapping_add(1);
    } else if act == 2 {
        keep[tf_dslot(d)] = 1;
        tf_fit_st(rem, keep, lle, st);
        tf_split_st(plan, st, rem, d, keep, lle);
        tf_note(rd, d);
    } else {
        st[0] = st[0].wrapping_add(rem);
    }
}

/// The `l` bytes at `p` whose distance code (of d) was dropped: re-found at kept distances (the chain of
/// `p` first, the recent distances, distance 1), after up to TF_SHIFT single literals; else literals when
/// at most TF_DLIT bytes remain, else at distance d with its code re-admitted. Returns the next position.
pub fn tf_redo(s: &[u8], prev: &[u16; TF_WN], keep: &mut [u8; 64], lle: &mut [u16; 260], plan: &mut Vec<u32>, st: &mut [usize; 4], rd: &mut [usize; 4], p: usize, l: usize, d: usize) -> usize {
    let mut q = p;
    let mut rem = l;
    let mut chain = 1usize;
    let mut shift = TF_SHIFT;
    while rem >= 3 {
        let f = tf_refind(s, prev, keep, q, chain, rem, rd[0], rd[1]);
        chain = 0;
        let fl = f.0;
        let fd = f.1;
        let act = tf_act(fl, rem, shift);
        tf_step(plan, st, rd, keep, lle, act, fl, fd, rem, d);
        if act == 0 {
            q = q.wrapping_add(fl);
            rem -= fl;
        } else if act == 1 {
            shift -= 1;
            q = q.wrapping_add(1);
            rem -= 1;
        } else {
            q = q.wrapping_add(rem);
            rem = 0;
        }
    }
    st[0] = st[0].wrapping_add(rem);
    q.wrapping_add(rem)
}

/// What `tf_rewrite` does with the stage-1 token (l, d) (`room` bytes left): 0 literals, 1 a span at a
/// kept distance, 2 a re-find (the distance code was dropped).
#[inline(always)]
pub fn tf_tkind(l: usize, d: usize, room: usize, keep: &[u8; 64]) -> usize {
    if d == 0 || l > room || l < 3 {
        0
    } else if keep[tf_dslot(d)] == 1 {
        1
    } else {
        2
    }
}

/// Literals for a token that is no match: min(l, room), at least 1.
#[inline(always)]
pub fn tf_litstep(l: usize, room: usize) -> usize {
    let st = tf_min(l, room);
    if st == 0 {
        1
    } else {
        st
    }
}

/// The span of consecutive stage-1 matches at distance `d` from token `k0` on (`l0` bytes so far, at most
/// `room`): (next token, span length).
pub fn tf_extend(tk: &[u32], k0: usize, d: usize, room: usize, l0: usize) -> (usize, usize) {
    let mut k = k0;
    let mut l = l0;
    while k < tk.len() && (tk[k] as usize) / 512 == d && l <= room && (tk[k] as usize) % 512 <= room - l {
        l += (tk[k] as usize) % 512;
        k += 1;
    }
    (k, l)
}

/// Phase 1c: the plan from the stage-1 tokens under the kept codes. Consecutive matches at one distance
/// are taken as one span and re-split into kept lengths; a match whose distance code was dropped is
/// re-found at a kept distance (its chain, the recent distances, distance 1; after at most TF_SHIFT
/// single literals), else its bytes become literals.
pub fn tf_rewrite(s: &[u8], tk: &[u32], prev: &[u16; TF_WN], keep: &mut [u8; 64], lle: &mut [u16; 260], kmin0: usize, plan: &mut Vec<u32>) {
    let n = s.len();
    // st[0] = pending literals, st[1] = smallest kept length
    let mut st = [0usize; 4];
    st[1] = kmin0;
    let mut p = 0usize;
    let mut rd = [0usize; 4];
    let mut k = 0usize;
    while k < tk.len() && p < n {
        let v = tk[k] as usize;
        k += 1;
        let l = v % 512;
        let d = v / 512;
        let room = n - p;
        let kind = tf_tkind(l, d, room, keep);
        if kind == 0 {
            let step = tf_litstep(l, room);
            st[0] = st[0].wrapping_add(step);
            p = p.wrapping_add(step);
        } else if kind == 1 {
            let e = tf_extend(tk, k, d, room, l);
            k = e.0;
            tf_span(plan, &mut st, e.1, d, keep, lle);
            tf_note(&mut rd, d);
            p = p.wrapping_add(e.1);
        } else {
            p = tf_redo(s, prev, keep, lle, plan, &mut st, &mut rd, p, l, d);
        }
    }
    let rest = tf_rest(n, p, st[0]);
    tf_lits(plan, rest);
}

/// Keep thresholds (length codes, distance codes) of kind `cls`.
#[inline(always)]
pub fn tf_thrs(cls: usize) -> (u32, u32) {
    if cls == 2 {
        (TF_BKL, TF_BKD)
    } else {
        (TF_KL, TF_KD)
    }
}

/// The plan for a tiny input of kind `cls` (`tf_class`).
pub fn tf_plan(input: &[u8], cls: usize) -> Vec<u32> {
    let n = input.len();
    let mut tk: Vec<u32> = Vec::with_capacity((n / 16).wrapping_add(64));
    let mut head = [0u16; TF_HN];
    let mut prev = [0u16; TF_WN];
    let mut hist = [0u32; 64];
    tf_stage1(input, &mut tk, &mut head, &mut prev, &mut hist, cls);
    let mut keep = [0u8; 64];
    let t = tf_thrs(cls);
    tf_keep(&hist, &mut keep, t.0, t.1);
    let mut lle = [0u16; 260];
    let kmin = tf_lle(&keep, &mut lle);
    let mut plan: Vec<u32> = Vec::with_capacity(tk.len().wrapping_add(64));
    tf_rewrite(input, &tk, &prev, &mut keep, &mut lle, kmin, &mut plan);
    plan
}

/// The kind (`tf_class`) of an input that takes the plan + re-verify path: binaries, and text of a kind
/// below TF_TKIND when TF_TEXT = 1, all of at most TF_N bytes; 3 for every other input.
#[inline(always)]
pub fn tf_route(input: &[u8]) -> usize {
    if input.len() <= TF_N {
        let kind = tf_class(input);
        if kind == 2 || (TF_TEXT == 1 && kind < TF_TKIND) {
            return kind;
        }
    }
    3
}

/// Length code (0..28) of a match length (0..511; lengths below 3 map to 0, above 258 to 28).
pub const TF_LSYM: [u8; 512] = [
    0, 0, 0, 0, 1, 2, 3, 4, 5, 6, 7, 8, 8, 9, 9, 10, 10, 11, 11, 12, 12, 12, 12, 13, 13, 13, 13, 14, 14, 14, 14, 15,
    15, 15, 15, 16, 16, 16, 16, 16, 16, 16, 16, 17, 17, 17, 17, 17, 17, 17, 17, 18, 18, 18, 18, 18, 18, 18, 18, 19, 19, 19, 19, 19,
    19, 19, 19, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21,
    21, 21, 21, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23,
    23, 23, 23, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24,
    24, 24, 24, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25,
    25, 25, 25, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26,
    26, 26, 26, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27,
    27, 27, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28,
    28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28,
    28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28,
    28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28,
    28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28,
    28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28,
    28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28,
    28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28,
];
/// Distance code (0..29) of d (index d - 1 for d <= 256, else 256 + (d - 1) / 128).
pub const TF_DSYM: [u8; 512] = [
    0, 1, 2, 3, 4, 4, 5, 5, 6, 6, 6, 6, 7, 7, 7, 7, 8, 8, 8, 8, 8, 8, 8, 8, 9, 9, 9, 9, 9, 9, 9, 9,
    10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11,
    12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12,
    13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13,
    14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14,
    14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14,
    15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15,
    15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15,
    0, 14, 16, 17, 18, 18, 19, 19, 20, 20, 20, 20, 21, 21, 21, 21, 22, 22, 22, 22, 22, 22, 22, 22, 23, 23, 23, 23, 23, 23, 23, 23,
    24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25,
    26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26,
    27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27,
    28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28,
    28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28,
    29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29,
    29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29,
];
/// Smallest and largest length of each length code (entries 29..31 unused).
pub const TF_LBASE: [u16; 32] = [3, 4, 5, 6, 7, 8, 9, 10, 11, 13, 15, 17, 19, 23, 27, 31, 35, 43, 51, 59, 67, 83, 99, 115, 131, 163, 195, 227, 258, 0, 0, 0];
pub const TF_LTOP: [u16; 32] = [3, 4, 5, 6, 7, 8, 9, 10, 12, 14, 16, 18, 22, 26, 30, 34, 42, 50, 58, 66, 82, 98, 114, 130, 162, 194, 226, 257, 258, 0, 0, 0];
