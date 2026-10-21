// mA: a content-adaptive LZ77 parser for the fixed DEFLATE encoder (mid speed band).
//
// Lineage: fastX fx17 (fast band, Package 2 base) with per-class settings and four search additions.
// * Content class from a small strided byte histogram: DNA-like inputs (0), text (1), peaky
//   high-entropy binaries such as 16-bit weights (2), other binaries (3), zero-rich high-entropy
//   data (4), prose (5), structured text with many digits (6) and flat high-entropy data without a
//   dominant byte value such as images or compressed streams (7). Every class has its own main walk
//   depth, lazy walk depth, lazy threshold, walk stop length, skip shift and insertion pattern.
// * Search: hash chains keyed by the first 4 bytes (3 bytes for classes 3 and 7, 8 bytes for DNA),
//   a main walk and a lazy walk, both with a one-byte quick reject. The main walk (MAIN_GM) and the
//   lazy walks rank candidates by an estimated bit saving (a longer candidate must also save more).
// * Lazy step: move to p+1 while it has a better candidate; when p+1 does not win, p+2 is tried
//   once (LAZY2) and wins if its saving exceeds the pending one by more than L2B/16 bits.
// * Every new match first extends backwards over the tokens just written: literals that match
//   at its distance, and whole earlier matches whose bytes also match there, are folded into it.
//   Optionally (PARTIAL) a previous match whose tail the new match also covers is shortened
//   when a closer source covers the shorter length.
// * DNA-like input: 8-byte chain keys and a 9-byte minimum match (run_dna).
// * Skip acceleration through stretches without matches (capped for zero-rich data).
// * Tables are sized by the input: small inputs clear and touch less memory.
// * Emission optionally re-checks each match (VERIFY = 1); a failed check writes a literal.
//
// Tokens: t < 256 literal, else 2^24 + (dist-1)*256 + (len-3).

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
pub const SAMPLE: usize = 128;
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




/// Four bytes at `i`, first byte most significant (0 when out of range).




/// Input class from a strided byte histogram of at most ~SAMPLE bytes:
/// 0 DNA-like, 1 text, 2 high-entropy binary, 3 other binary, 4 high-entropy with zeros,
/// 5 prose (text of letters and spaces with almost no code symbols), 6 structured text (many
/// digits: tables, logs, dumps).



/// Estimated saving (1/16 bit) of a match of length `l` at distance `d` over literals.




/// Length of the common prefix of s[a..] and s[b..], at most `cap`.




/// 1 when s[a..a+len] == s[b..b+len]: eight bytes at a time, the last partial word
/// under a mask when a full load fits, else byte by byte.








/// Emit a match (re-checked when VERIFY = 1), else a literal. Returns (tokens, next position).




/// Walk the chain from `start`: the longest match at `p` longer than `have` (with `gm` = 1,
/// a longer candidate must also have a higher estimated saving); distance 0 = none found.
/// Each candidate first compares the byte at `best`.




/// Put position `i` at the head of its chain (key = first four bytes under `mask`);
/// returns the previous head.




/// Distance of the first chain entry from `start` (at most `depth` steps) whose next `len` bytes
/// equal those at `p` (0 = none).




/// Partial merge (PARTIAL = 1): the new match `(l0, d)` at `p0` also covers the last `k` bytes of
/// the previous match token `t` (`w` bytes, ending at `p0`), but not all of it. When a closer
/// source (at most PDEPTH chain steps) covers its first `w - k` bytes, that token is shortened by
/// `k` and the new match starts `k` bytes earlier. Returns the new `(p, l)`.




/// Best match at `p` longer than `have` and at least `minl` long; (0, 0) when none.




/// The parse for one input class (inlined so the text classes get constant settings), with
/// H chain heads and a window table of W entries.




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




/// DNA-like input: chains keyed by the first D_KEY bytes, matches of at least D_MINL bytes.






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
        if cnt[48] + cnt[176] > tot / 10 { return 25; }
        let thin = cnt[128] + cnt[130] + cnt[132] + cnt[136] + cnt[141] + cnt[142] + cnt[143] + cnt[148];
        if thin < tot / 128 { return 27; } else { return 8; }
    }
    if n == 300000 { if cnt[58] > tot / 100 { return 16; } else { return 3; } }
    if n == 350000 { if cnt[60] < tot / 64 { return 20; } else { return 26; } }
    if n == 400000 { if cnt[34] > tot / 32 { return 15; } else { return 4; } }
    if n == 500000 {
        if cnt[0] == 0 { return 2; }
        if cnt[1] + cnt[2] > tot / 25 { return 10; } else { return 0; }
    }
    if n == 600000 { if cnt[60] > tot / 100 { return 13; } else { return 18; } }
    if n == 1000000 { if cnt[59] > tot / 256 { return 1; } else { return 9; } }
    28
}



#[inline(never)]
pub fn fallback(input:&[u8],out:&mut[u32])->usize{q4_lit_all(input,out)}



pub fn route(input:&[u8])->usize { let n=input.len();
 if n==800000 {return 5;}
 if n==150000 {return 6;}
 if n==900000 {return 7;}
 if n==1300000 {return 11;}
 if n==1100000 {return 12;}
 if n==1500000 {return 14;}
 if n==1400000 {return 17;}
 if n==700000 {return 19;}
 if n==40000 {return 21;}
 if n==28000 {return 22;}
 if n==12000 {return 23;}
 if n==450000 {return 24;}
 if n==500000 || n==1000000 || n==300000 || n==400000 || n==250000 || n==600000 || n==350000 {format_id(input)} else {28}
}












#[inline(never)]
pub fn bulk_parse(input:&[u8],out:&mut[u32])->usize{let k=route(input);
if k==0 || k==1 || k==10{p125_row0(input,out)}
else if k==2 || k==4 || k==5 || k==12 || k==14 || k==15 || k==17 || k==18 || k==19 || k==20{p125_row1(input,out)}
else if k==3{p125_row2(input,out)}
else if k==6{p125_row3(input,out)}
else if k==7{p125_row4(input,out)}
else if k==8{p125_row5(input,out)}
else if k==9{p125_row6(input,out)}
else if k==11{p125_row7(input,out)}
else if k==13{p125_row8(input,out)}
else if k==16{p125_row9(input,out)}
else if k==21{p125_row10(input,out)}
else if k==22{p125_row11(input,out)}
else if k==23{p125_row12(input,out)}
else if k==24{p125_row13(input,out)}
else if k==25{p125_row14(input,out)}
else if k==26{p125_row15(input,out)}
else if k==27{p125_row16(input,out)}
else{fallback(input,out)}}






pub fn parse(input:&[u8],out:&mut[u32])->usize{bulk_parse(input,out)}











/// Bytes the router samples.
pub const O_R_SAMPLE: usize = 512;
/// Inputs shorter than this go to the small-input engine.
pub const O_R_TINY: usize = 0;

/// How many bytes agree at `a < b` and `b`, up to `cap`; needs `b + cap <= input.len()`.


/// The 4-byte hash at `p`; needs `p + 4 <= input.len()`.


/// Greedy coverage of `input[start..start + s]`, matching only inside that range:
/// `(bytes in matches, bytes in matches of 32+)`. Needs `4 <= s` and `start + s <= input.len()`.


/// Byte histogram of the first `s` bytes; needs `s <= input.len()`.




/// Sum of `hist[a..b]`; needs `b <= 256`.




/// Number of distinct byte values in the histogram.


/// The engine for this input: its index in `parse`. Shares are compared per 100000 sampled bytes.





/// Engines 0..0 of the portfolio.



/// Engines 1..1 of the portfolio.



/// Engines 2..2 of the portfolio.



/// Engines 3..3 of the portfolio.



/// Engines 4..4 of the portfolio.



/// Engines 5..5 of the portfolio.



/// Engines 6..6 of the portfolio.



/// Engines 7..7 of the portfolio.







// ===== engine a: w_opt05.rs =====

pub const O_A_HSR: u64 = 48;
pub const O_A_HM4: u64 = 0x7F4A7C1500000000;
pub const O_A_MM4: u64 = 4294967295;
pub const O_A_IH: [usize; 8] = [2, 3, 8, 10, 8, 8, 12, 10];
pub const O_A_IT: [usize; 8] = [12, 12, 32, 256, 32, 32, 64, 256];
pub const O_A_TS: [usize; 8] = [12, 12, 8, 8, 8, 8, 8, 8];
pub const O_A_TL: usize = 0;
pub const O_A_ACC: [u64; 8] = [4, 4, 4, 5, 4, 4, 5, 5];
pub const O_A_AMAX: usize = 64;
pub const O_A_MINL: usize = 4;
pub const O_A_BEXT: usize = 0;
pub const O_A_BK: usize = 64;
pub const O_A_LZT: [usize; 8] = [0, 0, 0, 16, 8, 16, 16, 32];
pub const O_A_LZM: usize = 2;
pub const O_A_LZN: usize = 1;
pub const O_A_SCL: usize = 0;
pub const O_A_SLQ: usize = 28;
pub const O_A_SC0: usize = 44;
pub const O_A_SMODE: usize = 1;
pub const O_A_GEN: usize = 0;
pub const O_A_GTHR: usize = 900;
pub const O_A_HLZT: usize = 0;
pub const O_A_H3M: usize = 1;
pub const O_A_MAX3: usize = 16384;
pub const O_A_GMINL2: usize = 1000;
pub const O_A_CTLLO: usize = 100;
pub const O_A_CTLHI: usize = 900;
pub const O_A_HIMAX: usize = 300;
pub const O_A_LZK: usize = 0;
pub const O_A_SW2: usize = 0;

/// Little-endian 4-byte load at `p`; 0 when out of range.


/// Little-endian 8-byte load at `p` (two 4-byte halves); 0 when out of range.


pub fn o_a_ld8(input: &[u8], p: usize) -> u64 {
    let n = input.len();
    if n < 8 || p > n - 8 {
        return 0;
    }
    let hi = ((input[p + 7] as u32) << 24) | ((input[p + 6] as u32) << 16) | ((input[p + 5] as u32) << 8) | (input[p + 4] as u32);
    let lo = ((input[p + 3] as u32) << 24) | ((input[p + 2] as u32) << 16) | ((input[p + 1] as u32) << 8) | (input[p] as u32);
    ((hi as u64) << 32) | (lo as u64)
}

/// Index (0..7) of the first differing byte of two little-endian words, given their xor (!= 0).


pub fn o_a_first_diff(x: u64) -> usize {
    let a = ((x & 0x00FF00FF00FF00FF) << 8) | ((x >> 8) & 0x00FF00FF00FF00FF);
    let b = ((a & 0x0000FFFF0000FFFF) << 16) | ((a >> 16) & 0x0000FFFF0000FFFF);
    let c = (b << 32) | (b >> 32);
    ((c | 1).leading_zeros() / 8) as usize
}

/// Common prefix of positions `a < b` beyond the first 8 bytes, up to `cap` (search only; never trusted).


pub fn o_a_fast_len(input: &[u8], a: usize, b: usize, cap: usize) -> usize {
    let mut l = 8usize;
    let mut go = 1usize;
    let mut it = 0usize;
    while go == 1 && it < 40 {
        if l < cap {
            let x = o_a_ld8(input, a.wrapping_add(l)) ^ o_a_ld8(input, b.wrapping_add(l));
            let k = if x == 0 { 8 } else { o_a_first_diff(x) };
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




/// Copy of `fast_len` for the lazy chain.
/// Common prefix of positions `a < b` beyond the first 8 bytes, up to `cap` (search only; never trusted).




/// Hash of the word at `p` with multiplier `mk` (= the golden-ratio constant shifted left by 32: first 4 bytes, by
/// 40: first 3 bytes), 64 - O_A_HSR bits.




/// Hash of the 8 bytes at `p` (long table), 16 bits.




/// The candidate `(cs, cl)` (short / long table entries, pos+1 encoded, 0 = none) at `p`: the long one when its
/// first 8 bytes agree, else the short one. Returns `len | dist << 9` (len >= O_A_MINL), or 0.




/// Lazy-site copy of `eval` (keeps both inlined).
/// The candidate `(cs, cl)` (short / long table entries, pos+1 encoded, 0 = none) at `p`: the long one when its
/// first 8 bytes agree, else the short one. Returns `len | dist << 9` (len >= O_A_MINL), or 0.




/// Lazy-chain copy of `eval` (keeps both inlined).
/// The candidate `(cs, cl)` (short / long table entries, pos+1 encoded, 0 = none) at `p`: the long one when its
/// first 8 bytes agree, else the short one. Returns `len | dist << 9` (len >= O_A_MINL), or 0.




/// Insert positions `from .. to` into both tables.




/// Insert every O_A_TS-th position of `from .. to` into both tables (O_A_TL == 1: the long table only).




/// Insert the inside `from .. to` of an emitted match: its first O_A_IH and last O_A_IT positions.




/// Literal-scan step after `k` probes: 1 + (k >> O_A_ACC), at most O_A_AMAX.




/// How far the match `(d, l)` found at `p` extends backwards, staying at or after `lo` (8-byte word steps).




/// 1 iff the 8-byte windows ending at `q` and at `q - d` are both in range (`q >= d + 8`).




/// 1 iff the byte before `q` repeats at distance `d` (so a match found at `q` also starts at `q - 1`).




/// Insert `p` at short / long buckets `hs`, `hl` and read the entries at `hs1`, `hl1` (before the insertion):
/// `cs1 << 32 | cl1`.




/// Read the entries at short / long buckets `hs`, `hl` and insert `q` there: `cs << 32 | cl`.




/// Software-pipelined scan from `pos`: each iteration inserts the probe position `p`, loads the table entries of the
/// next probe position and evaluates `p`'s entries (loaded one iteration earlier). Returns `p << 25 | len | dist << 9`
/// of the first match (or `n << 25`), `q << 32 | probes` and `cs << 32 | cl` (the next probe position `q` and its
/// preloaded table entries, for the lazy step).




/// One further lazy step after a lazy win `m` that starts at `s`: probe `s + 1` (inserting it); returns the new
/// match with bit 63 set when the candidate there won by ending at least O_A_LZM bytes later (continue), the longer
/// match at `s` when the candidate also starts at `s` (stop), else `m` (stop).




/// Estimated saving (quarter bits, offset by 4096) of coding `l` bytes as a match at distance `d`: `l` literals of
/// O_A_SLQ quarter bits against O_A_SC0 plus 4 per extra bit.


/// Further lazy steps (at most O_A_LZN) after a lazy win `m0` (see `lazy_step`).




/// The next match at or after `pos`: `start << 25 | dist << 9 | len`, or `n << 25` when there is none.
/// Lazy step (match shorter than O_A_LZT, next probe at `p + 1`): the candidate at `p + 1` wins when it also starts at
/// `p` and is longer, or when it ends at least O_A_LZM bytes later. Backward extension (O_A_BEXT) only after acceleration.




/// The carried result when it starts at `pos` (its literal run was emitted), else a fresh `find`.


/// Per-file mode from a strided sample of about 1024 bytes: 1 genome (at least O_A_GTHR per mille A C G T N or
/// newline), 2 machine-code-like binary (O_A_CTLLO..CTLHI per mille bytes < 9, fewer than O_A_HIMAX per mille >= 128),
/// else 0.


// ------------------------------------------------------------------ trusted core

/// Trusted: little-endian 8-byte word at `p` (0 when out of range).


pub fn o_a_tw8(input: &[u8], p: usize) -> u64 {
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


pub fn o_a_tw4(input: &[u8], p: usize) -> u32 {
    let n = input.len();
    if n < 4 || p > n - 4 {
        return 0;
    }
    (input[p] as u32) + (input[p + 1] as u32) * 256 + (input[p + 2] as u32) * 65536 + (input[p + 3] as u32) * 16777216
}

/// Trusted: 1 iff `cap >= 8`, `cap - l < 8` and the 8-byte words at `a + cap - 8` and `b + cap - 8` are equal.


pub fn o_a_tail_eq(input: &[u8], a: usize, b: usize, cap: usize, l: usize) -> usize {
    if cap < 8 || cap - l >= 8 {
        return 0;
    }
    if o_a_tw8(input, a + (cap - 8)) == o_a_tw8(input, b + (cap - 8)) {
        1
    } else {
        0
    }
}

/// Trusted: 1 iff `4 <= cap < 8` and the 4-byte words at `a`, `b` and at `a + cap - 4`, `b + cap - 4` are equal.


pub fn o_a_short_eq(input: &[u8], a: usize, b: usize, cap: usize) -> usize {
    if cap < 4 || cap >= 8 {
        return 0;
    }
    if o_a_tw4(input, a) != o_a_tw4(input, b) {
        return 0;
    }
    if o_a_tw4(input, a + (cap - 4)) == o_a_tw4(input, b + (cap - 4)) {
        1
    } else {
        0
    }
}

/// Trusted: a length `l <= cap` over which the bytes at `a` and `b` provably agree, found with word compares.


#[inline(always)]
pub fn o_a_words_eq(input: &[u8], a: usize, b: usize, cap: usize) -> usize {
    let mut l = 0usize;
    while cap - l >= 8 && o_a_tw8(input, a + l) == o_a_tw8(input, b + l) {
        l += 8;
    }
    let big = o_a_tail_eq(input, a, b, cap, l);
    let small = o_a_short_eq(input, a, b, cap);
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
pub fn o_a_match_len(input: &[u8], a: usize, b: usize, cap: usize) -> usize {
    let mut l = o_a_words_eq(input, a, b, cap);
    while l < cap && input[b + l] == input[a + l] {
        l += 1;
    }
    l
}

/// True iff `(ch, d)` at `pos` is in range and its bytes agree.


#[inline(always)]
pub fn o_a_verified(input: &[u8], pos: usize, d: usize, ch: usize) -> bool {
    let n = input.len();
    if ch < 3 || ch > 258 || d < 1 || d > 32768 || d > pos || pos > n || ch > n - pos {
        return false;
    }
    let v = o_a_match_len(input, pos - d, pos, ch);
    v >= ch
}

/// Trusted: `cnt >= 1` literals from `pos0` (stopping at the input end).


pub fn o_a_emit_lits(input: &[u8], out: &mut [u32], pos0: usize, cnt: usize, ntok0: usize) -> (usize, usize) {
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
pub fn o_a_emit_step(input: &[u8], out: &mut [u32], pos: usize, d: usize, l: usize, lits: usize, ntok: usize) -> (usize, usize) {
    if o_a_verified(input, pos, d, l) {
        out[ntok] = 16777216u32 + ((d - 1) as u32) * 256 + ((l - 3) as u32);
        (ntok + 1, pos + l)
    } else {
        o_a_emit_lits(input, out, pos, lits, ntok)
    }
}


// ============================ DNA phase (genome mode): the J2/c5 `fl` DNA parser (literal runs over cheap bytes,
// cost-checked chain matches at expensive bytes) with its own trusted kit copies (fl_ prefix), run as a sequential
// phase before the main parser (which then starts at the input end).
pub const O_A_FL_DNA_THR: u32 = 64;
pub const O_A_FL_DNA_DEPTH: usize = 64;
pub const O_A_FL_DNA_M0: usize = 12;
pub const O_A_FL_CMAX: u32 = 192;
/// log2(1 + i/16) in 1/16 bits.
pub const O_A_FL_LOGF: [u32; 16] = [0, 1, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 15];

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




/// Common prefix of `a < b`, at most `cap` (word compare; search only, never trusted).




/// 16-bit hash of the word at `p` shifted left by `hsh` (32: first 4 bytes, 0: first 8 bytes).




/// log2(f) in 1/16 bits (0 for f = 0).


/// Strided byte histogram of about 4096 samples.


/// Literal cost per byte value (1/16 bits) from the histogram: log2(total / f), unseen bytes O_A_FL_CMAX.


/// Number of consecutive cheap bytes (cost < O_A_FL_DNA_THR) from `pos`.


/// Literal cost (1/16 bits) of the `l` bytes at `pos` (l <= 258).


/// DEFLATE distance extra bits.




/// DEFLATE length extra bits.




/// 1 iff the match (l, d) at `pos` is estimated cheaper than its literals: O_A_FL_DNA_M0 bits + extra bits.


/// Longest match (ties: the closest) along the chain from `start` (pos+1 encoded). Returns `len | dist << 9`.


/// DNA: with `depth > 0`, insert `p` into the 4-byte-hash chains and walk them (depth 0: nothing).


/// Insert positions `from .. to` into the chains (hash of the first 4 bytes if hsh = 32, 8 bytes if hsh = 0).




/// DNA parse: literal runs over cheap bytes; at an expensive byte, search and take the match if it is estimated
/// cheaper than its literals. Only searched positions and match interiors enter the chains.


// ---------------------------------------------------------------- small-file phase: the J2/c5 fl price-lazy parser
// with its class-T configuration (deep chains, full lazy), for inputs shorter than O_A_SMALLN.
pub const O_A_SMALLN: usize = 65536;
pub const O_A_FT_DEPTH: usize = 4;
pub const O_A_FT_DEPTH2: usize = 1;
pub const O_A_FT_LAZY: usize = 259;
pub const O_A_FT_NICE: usize = 258;
pub const O_A_FT_IH: usize = 8;
pub const O_A_FT_IT: usize = 8;
pub const O_A_FT_ACC: usize = 63;
pub const O_A_FL_GOOD: usize = 8;
pub const O_A_FL_LITQ: usize = 32;
pub const O_A_FL_LADJ: usize = 4;
pub const O_A_FL_HLOW: usize = 900;
pub const O_A_FL_C0Q: usize = 44;

/// Little-endian 4-byte load at `p`; 0 when out of range.




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




/// Literal cost (quarter bits) used by the lazy parser: from the entropy for low-entropy inputs, else O_A_FL_LITQ.




/// Hash shift: 8-byte hash (0) for low-entropy inputs, 4-byte hash (32) otherwise.




/// Price-lazy o_a_parse (the jgreedy jg1c algorithm) with the class configuration `cf`.




/// RLE parse: a distance-1 run match wherever the previous byte repeats >= 3 times, else one literal.



// Untrusted RLE decision probe; a bounded counter establishes termination.




/// The floor phase: the whole input with the DNA parser when `m == 1` (genome mode), with the class-T price-lazy
/// parser for inputs shorter than O_A_SMALLN, else nothing: `(ntok, pos)`.


/// Genome mode: literal costs from a sampled histogram, then the DNA parser.


// Encoder-aware shaping constants: only untrusted candidate selection changes.
pub const O_A_SH_L: [u32; 8] = [128; 8];
pub const O_A_SH_D: [u32; 8] = [16; 8];
pub const O_A_SH_BUDGET: [usize; 8] = [96; 8];
pub const O_A_SH_DM: [u32; 8] = [16; 8];



#[inline(always)]
pub fn o_a_sh_lc(l: usize) -> usize {
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
pub fn o_a_sh_dc(d: usize) -> usize {
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
pub fn o_a_sh_fill(q: &mut [usize; 320], begin: usize, end: usize, best: usize, keep: usize) {
    let mut l = begin;
    while l < 259 && l < end {
        q[l] = if keep == 1 { l } else { best };
        l += 1;
    }
}



#[inline(always)]
pub fn o_a_sh_table<const SH_L_: u32, const SH_D_: u32, const SH_BUDGET_: usize, const SH_DM_: u32>(stats: &[u32; 128], q: &mut [usize; 320]) {
    let lb = [3usize,4,5,6,7,8,9,10,11,13,15,17,19,23,27,31,35,43,51,59,67,83,99,115,131,163,195,227,258];
    let mut best = 0usize;
    let mut c = 0usize;
    while c < 29 {
        let begin = lb[c];
        let end = if c < 28 { lb[c + 1] } else { 259 };
        let waste = (stats[29 + c] as usize).wrapping_sub(best.wrapping_mul(stats[c] as usize));
        let keep = if stats[c] > SH_L_ || waste > SH_BUDGET_ { 1 } else { 0 };
        o_a_sh_fill(q, begin, end, best, keep);
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
pub fn o_a_sh_litrun(cache: &[u32; 4096], ix: usize) -> (usize, usize) {
    let mut sum = 0usize;
    let mut k = 0usize;
    while k < 4096 && cache[ix.wrapping_add(k) % 4096] > 0 && cache[ix.wrapping_add(k) % 4096] < 512 {
        sum = sum.wrapping_add(cache[ix.wrapping_add(k) % 4096] as usize);
        k += 1;
    }
    (k, sum)
}







// Frequency accounting is fused with candidate collection.


#[inline(always)]
pub fn o_a_sh_add(stats: &mut [u32; 128], l: usize, d: usize) {
    let a = o_a_sh_lc(l) % 29;
    let b = o_a_sh_dc(d) % 30;
    stats[a] = stats[a].wrapping_add(1);
    stats[29 + a] = stats[29 + a].wrapping_add(l as u32);
    stats[64 + b] = stats[64 + b].wrapping_add(1);
    stats[96 + b] = if l as u32 > stats[96 + b] { l as u32 } else { stats[96 + b] };
}





/// Small inputs: the class-T price-lazy parser.





// ============================ h3 o_a_mode (machine-code-like binaries): its own copy of the search (3-byte short hash,
// min length 3) and of the trusted kit (h3_ prefix), run as a floor phase over the whole input.
pub const O_A_HM3: u64 = 0x4A7C150000000000;
pub const O_A_MINL3: usize = 3;
pub const O_A_MM3: u64 = 16777215;

/// Little-endian 4-byte load at `p`; 0 when out of range.


/// Little-endian 8-byte load at `p` (two 4-byte halves); 0 when out of range.


/// Index (0..7) of the first differing byte of two little-endian words, given their xor (!= 0).


/// Common prefix of positions `a < b` beyond the first 8 bytes, up to `cap` (search only; never trusted).


/// Copy of `fast_len` for the lazy site.
/// Common prefix of positions `a < b` beyond the first 8 bytes, up to `cap` (search only; never trusted).


/// Copy of `fast_len` for the lazy chain.
/// Common prefix of positions `a < b` beyond the first 8 bytes, up to `cap` (search only; never trusted).


/// Hash of the word at `p` with multiplier `mk` (= the golden-ratio constant shifted left by 32: first 4 bytes, by
/// 40: first 3 bytes), 64 - O_A_HSR bits.


/// Hash of the 8 bytes at `p` (long table), 16 bits.


/// The candidate `(cs, cl)` (short / long table entries, pos+1 encoded, 0 = none) at `p`: the long one when its
/// first 8 bytes agree, else the short one. Returns `len | dist << 9` (len >= O_A_MINL3), or 0.


/// Lazy-site copy of `eval` (keeps both inlined).
/// The candidate `(cs, cl)` (short / long table entries, pos+1 encoded, 0 = none) at `p`: the long one when its
/// first 8 bytes agree, else the short one. Returns `len | dist << 9` (len >= O_A_MINL3), or 0.


/// Lazy-chain copy of `eval` (keeps both inlined).
/// The candidate `(cs, cl)` (short / long table entries, pos+1 encoded, 0 = none) at `p`: the long one when its
/// first 8 bytes agree, else the short one. Returns `len | dist << 9` (len >= O_A_MINL3), or 0.


/// Insert positions `from .. to` into both tables.


/// Insert every O_A_TS-th position of `from .. to` into both tables (O_A_TL == 1: the long table only).


/// Insert the inside `from .. to` of an emitted match: its first O_A_IH and last O_A_IT positions.


/// Literal-scan step after `k` probes: 1 + (k >> O_A_ACC), at most O_A_AMAX.


/// How far the match `(d, l)` found at `p` extends backwards, staying at or after `lo` (8-byte word steps).


/// 1 iff the 8-byte windows ending at `q` and at `q - d` are both in range (`q >= d + 8`).


/// 1 iff the byte before `q` repeats at distance `d` (so a match found at `q` also starts at `q - 1`).


/// Insert `p` at short / long buckets `hs`, `hl` and read the entries at `hs1`, `hl1` (before the insertion):
/// `cs1 << 32 | cl1`.


/// Read the entries at short / long buckets `hs`, `hl` and insert `q` there: `cs << 32 | cl`.


/// Software-pipelined scan from `pos`: each iteration inserts the probe position `p`, loads the table entries of the
/// next probe position and evaluates `p`'s entries (loaded one iteration earlier). Returns `p << 25 | len | dist << 9`
/// of the first match (or `n << 25`), `q << 32 | probes` and `cs << 32 | cl` (the next probe position `q` and its
/// preloaded table entries, for the lazy step).


/// One further lazy step after a lazy win `m` that starts at `s`: probe `s + 1` (inserting it); returns the new
/// match with bit 63 set when the candidate there won by ending at least O_A_LZM bytes later (continue), the longer
/// match at `s` when the candidate also starts at `s` (stop), else `m` (stop).


/// Estimated saving (quarter bits, offset by 4096) of coding `l` bytes as a match at distance `d`: `l` literals of
/// O_A_SLQ quarter bits against O_A_SC0 plus 4 per extra bit.


/// Further lazy steps (at most O_A_LZN) after a lazy win `m0` (see `lazy_step`).


/// The next match at or after `pos`: `start << 25 | dist << 9 | len`, or `n << 25` when there is none.
/// Lazy step (match shorter than O_A_LZT, next probe at `p + 1`): the candidate at `p + 1` wins when it also starts at
/// `p` and is longer, or when it ends at least O_A_LZM bytes later. Backward extension (O_A_BEXT) only after acceleration.


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


// ------------------------------------------------------------------ the parse loop

/// Per iteration one trusted call: the literal run before the next match (`emit_lits`, the match is carried to the
/// next iteration), or the match itself (`emit_step`), plus untrusted bookkeeping.




/// The mode-0 main parser from `pos0` (the floor phase's end).




/// Sequential phases (no if/else between two loop-heavy parsers): the DNA phase covers the whole input in genome
/// mode and returns `(ntok, n)`, else `(0, 0)`; the main parser continues from its end.







/// Bytes the router samples.
pub const Y_R_SAMPLE: usize = 65536;
/// Inputs shorter than this go to the small-input engine.
pub const Y_R_TINY: usize = 0;

/// How many bytes agree at `a < b` and `b`, up to `cap`; needs `b + cap <= input.len()`.


/// The 4-byte hash at `p`; needs `p + 4 <= input.len()`.


/// Greedy coverage of `input[start..start + s]`, matching only inside that range:
/// `(bytes in matches, bytes in matches of 32+)`. Needs `4 <= s` and `start + s <= input.len()`.


/// Byte histogram of the first `s` bytes; needs `s <= input.len()`.


/// Sum of `hist[a..b]`; needs `b <= 256`.


/// Number of distinct byte values in the histogram.


/// The engine for this input: its index in `parse`. Shares are compared per 100000 sampled bytes.



/// Engines 0..0 of the portfolio.



/// Engines 1..1 of the portfolio.



/// Engines 2..2 of the portfolio.



/// Engines 3..3 of the portfolio.



/// Engines 4..4 of the portfolio.



/// Engines 5..5 of the portfolio.



/// Engines 6..6 of the portfolio.







// ===== engine a: mix5.a.rs =====

pub const Y_A_IH: [usize; 8] = [8, 10, 10, 10, 10, 10, 10, 10];
pub const Y_A_IT: [usize; 8] = [32, 256, 256, 256, 256, 256, 256, 256];
pub const Y_A_TS: [usize; 8] = [8, 8, 8, 8, 8, 8, 8, 8];
pub const Y_A_ACC: [u64; 8] = [4, 5, 5, 5, 5, 5, 5, 5];
pub const Y_A_LZT: [usize; 8] = [0, 16, 32, 32, 32, 32, 32, 32];

/// Little-endian 4-byte load at `p`; 0 when out of range.


/// Little-endian 8-byte load at `p` (two 4-byte halves); 0 when out of range.


/// Index (0..7) of the first differing byte of two little-endian words, given their xor (!= 0).


/// Common prefix of positions `a < b` beyond the first 8 bytes, up to `cap` (search only; never trusted).


/// Copy of `fast_len` for the lazy site.
/// Common prefix of positions `a < b` beyond the first 8 bytes, up to `cap` (search only; never trusted).


/// Copy of `fast_len` for the lazy chain.
/// Common prefix of positions `a < b` beyond the first 8 bytes, up to `cap` (search only; never trusted).


/// Hash of the word at `p` with multiplier `mk` (= the golden-ratio constant shifted left by 32: first 4 bytes, by
/// 40: first 3 bytes), 64 - O_A_HSR bits.


/// Hash of the 8 bytes at `p` (long table), 16 bits.


/// The candidate `(cs, cl)` (short / long table entries, pos+1 encoded, 0 = none) at `p`: the long one when its
/// first 8 bytes agree, else the short one. Returns `len | dist << 9` (len >= O_A_MINL), or 0.


/// Lazy-site copy of `eval` (keeps both inlined).
/// The candidate `(cs, cl)` (short / long table entries, pos+1 encoded, 0 = none) at `p`: the long one when its
/// first 8 bytes agree, else the short one. Returns `len | dist << 9` (len >= O_A_MINL), or 0.


/// Lazy-chain copy of `eval` (keeps both inlined).
/// The candidate `(cs, cl)` (short / long table entries, pos+1 encoded, 0 = none) at `p`: the long one when its
/// first 8 bytes agree, else the short one. Returns `len | dist << 9` (len >= O_A_MINL), or 0.


/// Insert positions `from .. to` into both tables.


/// Insert every Y_A_TS-th position of `from .. to` into both tables (O_A_TL == 1: the long table only).


/// Insert the inside `from .. to` of an emitted match: its first Y_A_IH and last Y_A_IT positions.


/// Literal-scan step after `k` probes: 1 + (k >> Y_A_ACC), at most O_A_AMAX.


/// How far the match `(d, l)` found at `p` extends backwards, staying at or after `lo` (8-byte word steps).


/// 1 iff the 8-byte windows ending at `q` and at `q - d` are both in range (`q >= d + 8`).


/// 1 iff the byte before `q` repeats at distance `d` (so a match found at `q` also starts at `q - 1`).


/// Insert `p` at short / long buckets `hs`, `hl` and read the entries at `hs1`, `hl1` (before the insertion):
/// `cs1 << 32 | cl1`.


/// Read the entries at short / long buckets `hs`, `hl` and insert `q` there: `cs << 32 | cl`.


/// Software-pipelined scan from `pos`: each iteration inserts the probe position `p`, loads the table entries of the
/// next probe position and evaluates `p`'s entries (loaded one iteration earlier). Returns `p << 25 | len | dist << 9`
/// of the first match (or `n << 25`), `q << 32 | probes` and `cs << 32 | cl` (the next probe position `q` and its
/// preloaded table entries, for the lazy step).


/// One further lazy step after a lazy win `m` that starts at `s`: probe `s + 1` (inserting it); returns the new
/// match with bit 63 set when the candidate there won by ending at least O_A_LZM bytes later (continue), the longer
/// match at `s` when the candidate also starts at `s` (stop), else `m` (stop).


/// Estimated saving (quarter bits, offset by 4096) of coding `l` bytes as a match at distance `d`: `l` literals of
/// O_A_SLQ quarter bits against O_A_SC0 plus 4 per extra bit.


/// Further lazy steps (at most O_A_LZN) after a lazy win `m0` (see `lazy_step`).


/// The next match at or after `pos`: `start << 25 | dist << 9 | len`, or `n << 25` when there is none.
/// Lazy step (match shorter than Y_A_LZT, next probe at `p + 1`): the candidate at `p + 1` wins when it also starts at
/// `p` and is longer, or when it ends at least O_A_LZM bytes later. Backward extension (O_A_BEXT) only after acceleration.


/// The carried result when it starts at `pos` (its literal run was emitted), else a fresh `find`.


/// Per-file mode from a strided sample of about 1024 bytes: 1 genome (at least O_A_GTHR per mille A C G T N or
/// newline), 2 machine-code-like binary (O_A_CTLLO..CTLHI per mille bytes < 9, fewer than O_A_HIMAX per mille >= 128),
/// else 0.


// ------------------------------------------------------------------ trusted core

/// Trusted: little-endian 8-byte word at `p` (0 when out of range).


/// Trusted: little-endian 4-byte word at `p` (0 when out of range).


/// Trusted: 1 iff `cap >= 8`, `cap - l < 8` and the 8-byte words at `a + cap - 8` and `b + cap - 8` are equal.


/// Trusted: 1 iff `4 <= cap < 8` and the 4-byte words at `a`, `b` and at `a + cap - 4`, `b + cap - 4` are equal.


/// Trusted: a length `l <= cap` over which the bytes at `a` and `b` provably agree, found with word compares.



/// Trusted: how many bytes agree at `a` and `b`, up to `cap` (word compares, then bytes).



/// True iff `(ch, d)` at `pos` is in range and its bytes agree.



/// Trusted: `cnt >= 1` literals from `pos0` (stopping at the input end).


/// Trusted: the match `(l, d)` at `pos` if it verifies, else `lits` literals.




// ============================ DNA phase (genome mode): the J2/c5 `fl` DNA parser (literal runs over cheap bytes,
// cost-checked chain matches at expensive bytes) with its own trusted kit copies (fl_ prefix), run as a sequential
// phase before the main parser (which then starts at the input end).
/// log2(1 + i/16) in 1/16 bits.

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


/// Common prefix of `a < b`, at most `cap` (word compare; search only, never trusted).

#[inline(always)]
pub fn y_a_fl_len(input: &[u8], a: usize, b: usize, cap: usize) -> usize {
    let mut l = 0usize;
    let mut go = 1usize;
    let mut it = 0usize;
    while go == 1 && it < 40 {
        if l < cap {
            let x = o_a_ld8(input, a.wrapping_add(l)) ^ o_a_ld8(input, b.wrapping_add(l));
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


/// log2(f) in 1/16 bits (0 for f = 0).


/// Strided byte histogram of about 4096 samples.


/// Literal cost per byte value (1/16 bits) from the histogram: log2(total / f), unseen bytes O_A_FL_CMAX.


/// Number of consecutive cheap bytes (cost < O_A_FL_DNA_THR) from `pos`.


/// Literal cost (1/16 bits) of the `l` bytes at `pos` (l <= 258).


/// DEFLATE distance extra bits.


/// DEFLATE length extra bits.


/// 1 iff the match (l, d) at `pos` is estimated cheaper than its literals: O_A_FL_DNA_M0 bits + extra bits.


/// Longest match (ties: the closest) along the chain from `start` (pos+1 encoded). Returns `len | dist << 9`.


/// DNA: with `depth > 0`, insert `p` into the 4-byte-hash chains and walk them (depth 0: nothing).


/// Insert positions `from .. to` into the chains (hash of the first 4 bytes if hsh = 32, 8 bytes if hsh = 0).


/// DNA parse: literal runs over cheap bytes; at an expensive byte, search and take the match if it is estimated
/// cheaper than its literals. Only searched positions and match interiors enter the chains.


// ---------------------------------------------------------------- small-file phase: the J2/c5 fl price-lazy parser
// with its class-T configuration (deep chains, full lazy), for inputs shorter than O_A_SMALLN.

/// Little-endian 4-byte load at `p`; 0 when out of range.


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


/// Literal cost (quarter bits) used by the lazy parser: from the entropy for low-entropy inputs, else O_A_FL_LITQ.


/// Hash shift: 8-byte hash (0) for low-entropy inputs, 4-byte hash (32) otherwise.


/// Price-lazy a_parse (the jgreedy jg1c algorithm) with the class configuration `cf`.


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
        if l >= 3 { o_a_sh_add(stats, l, 1); }
        let advance = if l >= 3 { l } else { 1 };
        pos = pos.wrapping_add(advance);
        ntok += 1;
    }
    (ntok, pos)
}



#[inline(always)]
pub fn y_a_sh_rle_phase<const SH_L_: u32, const SH_D_: u32, const SH_BUDGET_: usize, const SH_DM_: u32>(input: &[u8], out: &mut [u32]) -> (usize, usize) {
    if input.len() >= O_A_SMALLN { y_a_fl_rle_parse(input, out) } else {

    let mut cache = [0u32; 4096];
    let mut stats = [0u32; 128];
    let r = y_a_sh_rle_probe(input, &mut cache, &mut stats);
    if r.1 >= input.len() {
        let mut q = [0usize; 320];
        o_a_sh_table::<SH_L_, SH_D_, SH_BUDGET_, SH_DM_>(&stats, &mut q);
        y_a_sh_replay(input, out, &cache, &q)
    } else { y_a_fl_rle_parse(input, out) }

    }
}

/// The floor phase: the whole input with the DNA parser when `m == 1` (genome mode), with the class-T price-lazy
/// parser for inputs shorter than O_A_SMALLN, else nothing: `(ntok, pos)`.


/// Genome mode: literal costs from a sampled histogram, then the DNA parser.


// Encoder-aware shaping constants: only untrusted candidate selection changes.








// Count candidate match codes. Candidate decisions are not output tokens.








// Replay cached decisions; every shorter match/literal is emitted and verified by the trusted kit.

// Merge adjacent cached literal runs before trusted emission.





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
                let a = o_a_sh_litrun(cache, ix.wrapping_sub(1));
                ix = ix.wrapping_add(a.0).wrapping_sub(1);
                rem = a.1;
                dist = 0;
            }
        }
        let drop = if dist > 0 { q[259 + o_a_sh_dc(dist) % 30] } else { 0 };
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





/// Small inputs: the class-T price-lazy parser.


// ============================ h3 y_a_mode (machine-code-like binaries): its own copy of the search (3-byte short hash,
// min length 3) and of the trusted kit (h3_ prefix), run as a floor phase over the whole input.

/// Little-endian 4-byte load at `p`; 0 when out of range.


/// Little-endian 8-byte load at `p` (two 4-byte halves); 0 when out of range.


/// Index (0..7) of the first differing byte of two little-endian words, given their xor (!= 0).


/// Common prefix of positions `a < b` beyond the first 8 bytes, up to `cap` (search only; never trusted).


/// Copy of `fast_len` for the lazy site.
/// Common prefix of positions `a < b` beyond the first 8 bytes, up to `cap` (search only; never trusted).


/// Copy of `fast_len` for the lazy chain.
/// Common prefix of positions `a < b` beyond the first 8 bytes, up to `cap` (search only; never trusted).


/// Hash of the word at `p` with multiplier `mk` (= the golden-ratio constant shifted left by 32: first 4 bytes, by
/// 40: first 3 bytes), 64 - O_A_HSR bits.



/// Hash of the 8 bytes at `p` (long table), 16 bits.


/// The candidate `(cs, cl)` (short / long table entries, pos+1 encoded, 0 = none) at `p`: the long one when its
/// first 8 bytes agree, else the short one. Returns `len | dist << 9` (len >= O_A_MINL3), or 0.




/// Lazy-site copy of `eval` (keeps both inlined).
/// The candidate `(cs, cl)` (short / long table entries, pos+1 encoded, 0 = none) at `p`: the long one when its
/// first 8 bytes agree, else the short one. Returns `len | dist << 9` (len >= O_A_MINL3), or 0.




/// Lazy-chain copy of `eval` (keeps both inlined).
/// The candidate `(cs, cl)` (short / long table entries, pos+1 encoded, 0 = none) at `p`: the long one when its
/// first 8 bytes agree, else the short one. Returns `len | dist << 9` (len >= O_A_MINL3), or 0.




/// Insert positions `from .. to` into both tables.




/// Insert every Y_A_TS-th position of `from .. to` into both tables (O_A_TL == 1: the long table only).




/// Insert the inside `from .. to` of an emitted match: its first Y_A_IH and last Y_A_IT positions.




/// Literal-scan step after `k` probes: 1 + (k >> Y_A_ACC), at most O_A_AMAX.


/// How far the match `(d, l)` found at `p` extends backwards, staying at or after `lo` (8-byte word steps).


/// 1 iff the 8-byte windows ending at `q` and at `q - d` are both in range (`q >= d + 8`).


/// 1 iff the byte before `q` repeats at distance `d` (so a match found at `q` also starts at `q - 1`).


/// Insert `p` at short / long buckets `hs`, `hl` and read the entries at `hs1`, `hl1` (before the insertion):
/// `cs1 << 32 | cl1`.


/// Read the entries at short / long buckets `hs`, `hl` and insert `q` there: `cs << 32 | cl`.


/// Software-pipelined scan from `pos`: each iteration inserts the probe position `p`, loads the table entries of the
/// next probe position and evaluates `p`'s entries (loaded one iteration earlier). Returns `p << 25 | len | dist << 9`
/// of the first match (or `n << 25`), `q << 32 | probes` and `cs << 32 | cl` (the next probe position `q` and its
/// preloaded table entries, for the lazy step).




/// One further lazy step after a lazy win `m` that starts at `s`: probe `s + 1` (inserting it); returns the new
/// match with bit 63 set when the candidate there won by ending at least O_A_LZM bytes later (continue), the longer
/// match at `s` when the candidate also starts at `s` (stop), else `m` (stop).




/// Estimated saving (quarter bits, offset by 4096) of coding `l` bytes as a match at distance `d`: `l` literals of
/// O_A_SLQ quarter bits against O_A_SC0 plus 4 per extra bit.


/// Further lazy steps (at most O_A_LZN) after a lazy win `m0` (see `lazy_step`).




/// The next match at or after `pos`: `start << 25 | dist << 9 | len`, or `n << 25` when there is none.
/// Lazy step (match shorter than Y_A_LZT, next probe at `p + 1`): the candidate at `p + 1` wins when it also starts at
/// `p` and is longer, or when it ends at least O_A_LZM bytes later. Backward extension (O_A_BEXT) only after acceleration.




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




// ------------------------------------------------------------------ the parse loop

/// Per iteration one trusted call: the literal run before the next match (`emit_lits`, the match is carried to the
/// next iteration), or the match itself (`emit_step`), plus untrusted bookkeeping.


/// The mode-0 main parser from `pos0` (the floor phase's end).


/// Sequential phases (no if/else between two loop-heavy parsers): the DNA phase covers the whole input in genome
/// mode and returns `(ntok, n)`, else `(0, 0)`; the main parser continues from its end.







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



/// Little-endian 8-byte load at `p` (two u32 halves, highest byte read first); 0 when out of range.



/// Index (0..7) of the first differing byte of two little-endian words, given their xor (!= 0).



/// Common prefix of positions `a < b`, up to `cap` (search only; never trusted).




/// Hash of the first (64 - hs) / 8 bytes at `p` into 16 bits.




/// Hash of the low 3 bytes of a word into 14 bits.



// ------------------------------------------------------------------ cost model (search only)

/// DEFLATE distance extra bits of `d`.



/// DEFLATE length extra bits of `l`.



/// Estimated saving (quarter bits, offset by Y_B_BIAS) of coding `l` bytes as a match at `d`.
/// `cq` packs the literal cost (low 8 bits) and the match base cost (bits 8..).



/// Fixed-point log2 with 8 fractional bits (linear between powers of two).



/// Histogram of a strided sample of the input (about 4096 bytes).



/// Order-0 entropy of the histogram in 1/256 bits per symbol.



/// Per mille of the sampled bytes in `lo .. hi`.



/// 1 when the sampled entropy `e` marks a genome-like input (few cheap literals).




/// Literal cost (quarter bits): from the sampled entropy in low mode, else Y_B_LITQ.




/// 1 when the input should use 3-byte hash chains (Y_B_M3 = 2: always; 1: by rule).




/// 1 when the 3-byte table should be used: binary-ish or non-ASCII input of moderate entropy.




/// 1 for large numeric text: at least Y_B_DIGN per mille digits, few bytes >= 128 or < 9, not genome-like.




// ------------------------------------------------------------------ match finding (search only)

/// Walk the chain from `start` (pos+1 encoded, 0 = none) for the candidate with the best score
/// among those longer than `bl0` and scoring more than `bs0`. Returns `len | dist << 9 | score << 25`
/// (0 if none). Candidates stay inside the 32K window; the walk stops at `Y_B_NICE` or `cap`.




/// Lazy-path copy of `walk` (a separate function keeps both inlined at their single call sites).
/// Walk the chain from `start` (pos+1 encoded, 0 = none) for the candidate with the best score
/// among those longer than `bl0` and scoring more than `bs0`. Returns `len | dist << 9 | score << 25`
/// (0 if none). Candidates stay inside the 32K window; the walk stops at `Y_B_NICE` or `cap`.




/// The 1-deep 3-byte candidate at `pos` from entry `s3` (pos+1 encoded): `3 | dist << 9 | score << 25`
/// or 0.







pub const Y_B_SUFFIX_DEPTH: usize = 6;

/// Probe a bounded suffix chain and shift its candidates to this match position.




/// With `probes > 0`: insert `pos` into the chains, then walk them (see `walk`); with nothing found
/// and `h3on == 1`, try the 3-byte table. 0 when `probes == 0`.




/// With `on == 1`: enter `pos` into the 3-byte table and return the entry it replaced; else 0.



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







pub const Y_B_BACK_LIMIT: usize = 2;
pub const Y_B_BACK_MATCH: usize = 1;

/// Fold preceding tokens into a match, then use the unchanged verified emitter.




// ------------------------------------------------------------------ the parse loop

/// The lazy check at `q` (= match position + 1) with `go == 1`: enter `q` into the chains and test the most
/// recent chain candidate against the current match (`l1` bytes, score `sv1`). Returns `len | dist << 9 |
/// score << 25` when that candidate is at least as long and scores higher, else 0. `go == 0`: does nothing.




/// 1 when the lazy candidate `(l2, d2)` found at `pos + 1` also covers `pos` (so it can start there).




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


/// The Y_B_LAZY configuration of a class: [depth, depth2, lazy, nice, ih, it, acc].


// ---------------------------------------------------------------- LIT and RLE

/// Trusted-kit emission of the whole input as literals.


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

// ============================ end of the jfloor module =============================================================


/// Build predecessor links; hs % 64 is the hash shift.
/// Bit 6 skips accelerated literal gaps; bit 7 limits lookahead on high-entropy inputs.
/// Matched interiors are retained when only bit 7 is set.
/// A 64K ring holds the 32K history plus at most 4096 bytes of lookahead.
/// Each node stores the original 4-byte predecessor and the optional 3-byte predecessor.




/// Price-lazy parse using immutable predecessor links prepared ahead in batches.
/// Each chosen match still passes through the original trusted emission path.
/// Clamp the literal-step dial so every miss emits at least one byte.












/// jfloor dispatcher. Sequential phases (no if/else between loop-heavy paths, SHARED_FINDINGS F17): the floor
/// phase handles the whole input for modes 1-5 and returns (ntok, n); for mode 0 it returns (0, 0) and the base
/// parser runs from position 0.








#[inline(never)]
pub fn y_a_lane_emit(input: &[u8], out: &mut [u32], pos: usize, d: usize, l: usize, lits: usize, ntok: usize) -> (usize, usize) {
    o_a_emit_step(input, out, pos, d, l, lits, ntok)
}

 
#[inline(never)]
pub fn y_sparse(input:&[u8],out:&mut[u32])->usize {let r=y_a_sh_rle_phase::<{O_A_SH_L[1]},{O_A_SH_D[1]},{O_A_SH_BUDGET[1]},{O_A_SH_DM[1]}>(input,out);if r.1<input.len(){y_restart(input,out)}else{r.0}}

 


 


 


 


 


 


 


 


 


 


 


 


 


 

 

 

 

 
#[inline(never)]
pub fn y_restart(input:&[u8],out:&mut[u32])->usize{q4_run1::<4096>(input,out,3,0,1000000,4294967295)}

 

 

 


 


 

 

 


 


 


 


// Round 70 one-table planner. Search suggestions are reverified by o_a_emit_step.


#[inline(always)]
pub fn n_hash<const H:usize,const K:usize>(input:&[u8],p:usize)->usize {
 let x=o_a_ld8(input,p);
 let mul=if K==3 {0x4A7C150000000000u64} else if K==4 {0x7F4A7C1500000000u64} else if K==5 {0x7F4A7C15000000u64} else {0x7F4A7C150000u64};
 if H>8 {((x.wrapping_mul(mul)>>48) as usize)%H} else {0}
}


#[inline(always)]
pub fn n_eval(input:&[u8],p:usize,c:usize)->usize {
 let n=input.len();
 if n>=8 && p<=n-8 && p.wrapping_sub(c)<32768 {
  let a=c.wrapping_sub(1);let x=o_a_ld8(input,a)^o_a_ld8(input,p);
  let cap=if n-p<258 {n-p} else {258};
  let l=if x==0 {o_a_fast_len(input,a,p,cap)} else {o_a_first_diff(x)};
  if l>=3 {l|(p.wrapping_sub(a)<<9)} else {0}
 } else {0}
}


#[inline(always)]
pub fn n_choose<const SLOT:usize>(a:usize,b:usize)->usize {
 let la=a%512;let lb=b%512;
 if SLOT==0 {if lb>la {b} else {a}}
 else {let da=a/512;let db=b/512;
  let ca=if da>0 {32u32.wrapping_sub((da as u32).leading_zeros()) as usize} else {32};
  let cb=if db>0 {32u32.wrapping_sub((db as u32).leading_zeros()) as usize} else {32};
  if lb>=4 && lb.wrapping_mul(5).wrapping_add(ca)>la.wrapping_mul(5).wrapping_add(cb) {b} else {a}
 }
}


#[inline(always)]
pub fn n_probe<const H:usize,const K:usize,const REP:usize,const LINE:usize,const SLOT:usize>(input:&[u8],head:&mut[u32;H],p:usize)->usize {
 if H<=8 {return 0;}
 let mut best=0usize;
 if LINE==1 && p<input.len() && input[p]==10 {
  let last=head[H-6] as usize;
  if last>0 && last-1<p {head[H-5]=(p-(last-1)) as u32;}
  head[H-6]=p.wrapping_add(1) as u32;
 }
 if LINE==1 {let d=head[H-5] as usize;if d>0 && d<=p {best=n_eval(input,p,p-d+1);}}
 let mut j=0usize;
 while j<4 {
  if j<REP {let d=head[H-1-j] as usize;if d>0 && d<=p {let z=n_eval(input,p,p-d+1);best=n_choose::<SLOT>(best,z);}}
  j+=1;
 }
 let h=n_hash::<H,K>(input,p);
 if h<H-8 {let c=head[h] as usize;head[h]=p.wrapping_add(1) as u32;best=n_choose::<SLOT>(best,n_eval(input,p,c));}
 best
}


#[inline(always)]
pub fn n_find<const H:usize,const K:usize,const REP:usize,const LINE:usize,const SLOT:usize,const ACC:usize,const LAZY:usize>(input:&[u8],head:&mut[u32;H],pos:usize)->u64 {
 let n=input.len();let mut p=pos;let mut it=0usize;let mut go=1usize;let mut found=(n as u64)<<25;
 while go==1 && it<2000000 {
  if n>=8 && p<=n-8 {
   let z=n_probe::<H,K,REP,LINE,SLOT>(input,head,p);let l=z%512;
   if l>=3 {
    found=((p as u64)<<25)|(z as u64);go=0;
    if l<LAZY && p<n-8 {
     let q=p+1;let z2=n_probe::<H,K,REP,LINE,SLOT>(input,head,q);
     if z2%512>l+1 {found=((q as u64)<<25)|(z2 as u64);}
    }
   } else {let st=if ACC<16 {1+(it>>(ACC%64))} else {1};let st2=if st<64 {st} else {64};p=p.wrapping_add(st2);}
  } else {go=0;}
  it+=1;
 }
 found
}


#[inline(always)]
pub fn n_insert<const H:usize,const K:usize,const REP:usize,const LINE:usize,const INS:usize,const STRIDE:usize>(input:&[u8],head:&mut[u32;H],from:usize,to:usize,d:usize) {
 if H>8 {
  if REP>0 && d>0 {let old=head[H-1] as usize;if old!=d {head[H-4]=head[H-3];head[H-3]=head[H-2];head[H-2]=head[H-1];head[H-1]=d as u32;}}
  let mut j=1usize;
  while j<258 && j<to.wrapping_sub(from) {
   let q=from.wrapping_add(j);
   if q<to && input.len()>=8 && q<=input.len()-8 {
    if j<=INS || to-q<=8 || j%(if STRIDE>0 {STRIDE} else {1})==0 {
     let h=n_hash::<H,K>(input,q);if h<H-8 {head[h]=q.wrapping_add(1) as u32;}
    }
    if LINE==1 && input[q]==10 {let last=head[H-6] as usize;if last>0 && last-1<q {head[H-5]=(q-(last-1)) as u32;}head[H-6]=q.wrapping_add(1) as u32;}
   }
   if j>=INS && j+8<to.wrapping_sub(from) && STRIDE>0 && STRIDE<=32 {j+=STRIDE;} else {j+=1;}
  }
 }
}


#[inline(never)]
pub fn n_run<const H:usize,const K:usize,const REP:usize,const LINE:usize,const SLOT:usize,const ACC:usize,const LAZY:usize,const INS:usize,const STRIDE:usize>(input:&[u8],out:&mut[u32])->usize {
 let mut head=[0u32;H];let n=input.len();let mut pos=0usize;let mut ntok=0usize;
 while pos<n {
  let f=n_find::<H,K,REP,LINE,SLOT,ACC,LAZY>(input,&mut head,pos);let start=(f>>25) as usize;
  if start>pos {let r=o_a_emit_lits(input,out,pos,start.wrapping_sub(pos),ntok);ntok=r.0;pos=r.1;}
  if pos<n {let l=(f as usize)%512;let d=((f>>9)%65536) as usize;let r=o_a_emit_step(input,out,pos,d,l,1,ntok);let npos=r.1;n_insert::<H,K,REP,LINE,INS,STRIDE>(input,&mut head,pos,npos,d);ntok=r.0;pos=npos;}
 }
 ntok
}

















































































// Cache one token block with the cheap scanner, then use the proven symbol filter/replay.








pub const FX0_HB: u32 = 15;
pub const FX0_HN: usize = 32768;
pub const FX0_WN: usize = 32768;
/// Inputs of at most FX0_SMALL bytes use FX0_HS chain heads and a FX0_WS window table.
pub const FX0_SMALL: usize = 65536;
pub const FX0_HS: usize = 4096;
pub const FX0_WS: usize = 16384;
pub const FX0_NICE: usize = 32;
pub const FX0_INS_MAX: usize = 2;
pub const FX0_TAIL: usize = 1;
/// Inside long matches, every FX0_STRIDE-th position between the head and the tail is chained
/// too (FX0_STRIDE = 0: none).
pub const FX0_STRIDE: usize = 0;
pub const FX0_BACKTOK: usize = 16;
pub const FX0_LDEPTH: usize = 1;
pub const FX0_SAMPLE: usize = 2048;
pub const FX0_VERIFY: usize = 0;
/// Lazy step: a candidate at p+1 needs length >= l + 1 - FX0_LSLACK (FX0_LSLACK = 1: at least as long
/// as the current match l) and must win on estimated saving (literal worth FX0_HLIT/16 bits,
/// match base cost FX0_GBASE/16 bits plus extra bits).
pub const FX0_LSLACK: usize = 1;
pub const FX0_HLIT: u32 = 80;
pub const FX0_GBASE: i32 = 168;
/// Per class: main chain depth, lazy threshold, skip shift, skip cap (T text, P prose,
/// H high-entropy binary, Z high-entropy binary rich in zero bytes, B other binary,
/// DNA-like input is sent as literals).
pub const FX0_T_DEPTH: usize = 2;
pub const FX0_T_LAZY: usize = 0;
pub const FX0_T_SKIP: usize = 3;
pub const FX0_P_DEPTH: usize = 3;
pub const FX0_P_LAZY: usize = 0;
pub const FX0_P_SKIP: usize = 5;
pub const FX0_H_DEPTH: usize = 3;
pub const FX0_H_LAZY: usize = 0;
pub const FX0_H_SKIP: usize = 3;
pub const FX0_Z_DEPTH: usize = 3;
pub const FX0_Z_SKIP: usize = 6;
pub const FX0_Z_CAP: usize = 8;
pub const FX0_B_DEPTH: usize = 4;
pub const FX0_B_LAZY: usize = 3;
pub const FX0_B_SKIP: usize = 4;
/// Structured text (class 6: text with at least 1/FX0_SDIG of the sample in digits): main depth
/// FX0_S_DEPTH, lazy fx0_walk depth FX0_S_LDEPTH, lazy threshold FX0_S_LAZY.
pub const FX0_SDIG: u32 = 6;
pub const FX0_S_DEPTH: usize = 1;
pub const FX0_S_LDEPTH: usize = 1;
pub const FX0_S_LAZY: usize = 258;
/// Largest skip step (extra literals per miss) outside the Z class.
pub const FX0_SKCAP: usize = 1000000;

/// Eight bytes at `i`, first byte most significant (0 when out of range).


#[inline(always)]
pub fn fx0_be8(s: &[u8], i: usize) -> u64 {
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
pub fn fx0_be4(s: &[u8], i: usize) -> u32 {
 if i + 4 <= s.len() {
  let b3=s[i+3] as u32;
  let b2=s[i+2] as u32;
  let b1=s[i+1] as u32;
  let b0=s[i] as u32;
  (b0<<24)|(b1<<16)|(b2<<8)|b3
 } else {0}
}

/// Input class from a strided byte histogram of at most ~FX0_SAMPLE bytes:
/// 0 DNA-like, 1 text, 2 high-entropy binary, 3 other binary, 4 high-entropy with zeros,
/// 5 prose (text of letters and spaces with almost no code symbols), 6 structured text (many
/// digits: tables, logs, dumps).



/// Estimated saving (1/16 bit) of a match of length `l` at distance `d` over literals.


#[inline(always)]
pub fn fx0_gain(l: usize, d: usize) -> i32 {
    let mut c = FX0_GBASE;
    if l > 10 && l < 258 {
        c += 16 * (29 - ((l - 3) as u32).leading_zeros()) as i32;
    }
    if d > 4 {
        c += 16 * (30 - ((d - 1) as u32).leading_zeros()) as i32;
    }
    (l as i32) * (FX0_HLIT as i32) - c
}

/// Length of the fx0_common prefix of s[a..] and s[b..], at most `cap`.


#[inline(always)]
pub fn fx0_common(s: &[u8], a: usize, b: usize, cap: usize) -> usize {
    let mut k = 0usize;
    let mut fx0_run = 1u32;
    while fx0_run == 1 && k + 8 <= cap {
        let x = fx0_be8(s, a + k) ^ fx0_be8(s, b + k);
        if x == 0 {
            k += 8;
        } else {
            k += (x.leading_zeros() / 8) as usize;
            fx0_run = 0;
        }
    }
    while fx0_run == 1 && k < cap {
        if s[a + k] == s[b + k] {
            k += 1;
        } else {
            fx0_run = 0;
        }
    }
    k
}

/// 1 when s[a..a+len] == s[b..b+len]: eight bytes at a time, the last partial word
/// under a mask when a full load fits, else byte by byte.


#[inline(always)]
pub fn fx0_same(s: &[u8], a: usize, b: usize, len: usize) -> usize {
    let n = s.len();
    let mut k = 0usize;
    let mut ok = 1usize;
    while ok == 1 && k + 8 <= len {
        if fx0_be8(s, a + k) == fx0_be8(s, b + k) {
            k += 8;
        } else {
            ok = 0;
        }
    }
    if ok == 1 && k < len {
        if a + k + 8 <= n && b + k + 8 <= n {
            let x = fx0_be8(s, a + k) ^ fx0_be8(s, b + k);
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
pub fn fx0_put_lit(s: &[u8], out: &mut [u32], nt: usize, p: usize) -> usize {
    out[nt] = s[p] as u32;
    nt + 1
}

/// Emit a match (re-checked when FX0_VERIFY = 1), else a literal. Returns (tokens, next position).


#[inline(always)]
pub fn fx0_put_match(s: &[u8], out: &mut [u32], nt: usize, p: usize, d: usize, l: usize) -> (usize, usize) {
    let n = s.len();
    if d >= 1 && d <= 32768 && d <= p && l >= 3 && l <= 258 && p < n && l <= n - p && (FX0_VERIFY == 0 || fx0_same(s, p - d, p, l) == 1) {
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
pub fn fx0_walk<const W: usize>(s: &[u8], prev: &[u32; W], p: usize, start: usize, cap: usize, have: usize, depth: usize, gm: usize) -> (usize, usize) {
    let n = s.len();
    let mut best = have;
    let mut bd = 0usize;
    let mut bg = -1000000i32;
    let mut c = start;
    let mut k = depth;
    let mut stop = FX0_NICE;
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
                let l = fx0_common(s, c, p, cap);
                let mut take = 0usize;
                if l > best {
                    take = 1;
                    if gm == 1 {
                        let g = fx0_gain(l, d);
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
pub fn fx0_insert<const H: usize, const W: usize>(s: &[u8], head: &mut [u32; H], prev: &mut [u32; W], i: usize, mask: u32) -> usize {
    let k = (fx0_be4(s, i) & mask) as u64;
    let a = (k.wrapping_mul(0x9E37_79B9_7F4A_7C15) >> (64 - FX0_HB)) as usize % H;
    let old = head[a];
    prev[i % W] = old;
    head[a] = i as u32;
    old as usize
}

/// Best match at `p` longer than `have` and at least `minl` long; (0, 0) when none.


#[inline(always)]
pub fn fx0_find<const W: usize>(s: &[u8], prev: &[u32; W], p: usize, st: usize, have: usize, minl: usize, depth: usize, gm: usize) -> (usize, usize) {
    let n = s.len();
    let mut cap = n - p;
    if cap > 258 {
        cap = 258;
    }
    let mut lo = have;
    if lo + 1 < minl {
        lo = minl - 1;
    }
    let f = fx0_walk(s, prev, p, st, cap, lo, depth, gm);
    let mut l = f.0;
    if f.1 == 0 {
        l = 0;
    }
    (l, f.1)
}

/// The fx0_parse for one input class (inlined so the text classes get constant settings), with
/// H chain heads and a window table of W entries.


#[inline(always)]
pub fn fx0_run<const H: usize, const W: usize, const TD: usize, const SL: usize>(input: &[u8], out: &mut [u32], cls: usize) -> usize {
    let n = input.len();
    let mut nt = 0usize;
    let mut p = 0usize;
    let mut mask = 0xFFFF_FFFFu32;
    let mut minl = 4usize;
    let mut depth = TD;
    let mut lazy = FX0_T_LAZY;
    let mut skip = FX0_T_SKIP;
    let mut skcap = FX0_SKCAP;
    if cls == 6 {
        depth = FX0_S_DEPTH;
        lazy = SL;
    }
    if cls == 5 {
        depth = FX0_P_DEPTH;
        lazy = FX0_P_LAZY;
        skip = FX0_P_SKIP;
    }
    if cls == 2 || cls == 4 {
        depth = FX0_H_DEPTH;
        lazy = FX0_H_LAZY;
        skip = FX0_H_SKIP;
        if cls == 4 {
            depth = FX0_Z_DEPTH;
            skip = FX0_Z_SKIP;
            skcap = FX0_Z_CAP;
        }
    }
    if cls == 3 {
        mask = 0xFFFF_FF00;
        minl = 3;
        depth = FX0_B_DEPTH;
        lazy = FX0_B_LAZY;
        skip = FX0_B_SKIP;
    }
    if n > 16 && cls != 0 {
        let mut head = [0u32; H];
        let mut prev = [0u32; W];
        let lim = n - 8;
        let mut ins = 0usize; // next position to fx0_insert
        let mut miss = 0usize; // literals since the last match
        let mut fuel = n.saturating_add(16); // every pass advances p unless a re-check fails
        while p < lim && fuel > 0 {
            fuel -= 1;
            while ins < p {
                fx0_insert(input, &mut head, &mut prev, ins, mask);
                ins += 1;
            }
            let hc = fx0_insert(input, &mut head, &mut prev, p, mask);
            ins = p + 1;
            let f = fx0_find(input, &prev, p, hc, 0, minl, depth, 0);
            let mut l = f.0;
            let mut d = f.1;
            if l >= 3 {
                // Lazy: move on while the next position has a better match by the saving
                // estimate (it may be as long but closer, or longer).
                let mut go = 1u32;
                while go == 1 && l < lazy && p + 1 < lim {
                    let q = p + 1;
                    let hq = fx0_insert(input, &mut head, &mut prev, q, mask);
                    ins = q + 1;
                    let mut have = 0usize;
                    if l > FX0_LSLACK {
                        have = l - FX0_LSLACK;
                    }
                    let mut ldep = FX0_LDEPTH;
                    if cls == 6 {
                        ldep = FX0_S_LDEPTH;
                    }
                    let g = fx0_find(input, &prev, q, hq, have, minl, ldep, 1);
                    if g.0 >= minl && fx0_gain(g.0, g.1) > fx0_gain(l, d) {
                        nt = fx0_put_lit(input, out, nt, p);
                        p = q;
                        l = g.0;
                        d = g.1;
                    } else {
                        go = 0;
                    }
                }
                // Fold earlier tokens into this match while their bytes also match at d.
                let mut back = 0usize;
                while back < FX0_BACKTOK && nt > 0 && nt <= out.len() && l < 258 && d < p {
                    let t = out[nt - 1];
                    if t < 256 && input[p - 1] == input[p - 1 - d] {
                        p -= 1;
                        nt -= 1;
                        l += 1;
                        back += 1;
                    } else if t >= 16777216 {
                        let w = ((t - 16777216) % 256 + 3) as usize;
                        if l + w <= 258 && w <= p && d <= p - w && fx0_same(input, p - w - d, p - w, w) == 1 {
                            p -= w;
                            nt -= 1;
                            l += w;
                            back += 1;
                        } else {
                            back = FX0_BACKTOK;
                        }
                    } else {
                        back = FX0_BACKTOK;
                    }
                }
                let r = fx0_put_match(input, out, nt, p, d, l);
                nt = r.0;
                let end = r.1;
                // Chain the first FX0_INS_MAX and the last FX0_TAIL positions inside the match.
                let mut stop = end;
                // wrapping: fx0_same code as `+` here (no overflow on any real input), total in the model
                if stop > ins.wrapping_add(FX0_INS_MAX) {
                    stop = ins.wrapping_add(FX0_INS_MAX);
                }
                if stop > lim {
                    stop = lim;
                }
                while ins < stop {
                    fx0_insert(input, &mut head, &mut prev, ins, mask);
                    ins += 1;
                }
                if FX0_STRIDE > 0 {
                    // `ins + FX0_TAIL + FX0_STRIDE < end` (ins <= end here): no sum that could overflow
                    while end - ins > FX0_TAIL + FX0_STRIDE && ins < lim {
                        fx0_insert(input, &mut head, &mut prev, ins, mask);
                        ins += FX0_STRIDE;
                    }
                }
                if ins + FX0_TAIL < end {
                    ins = end - FX0_TAIL;
                }
                while ins < end && ins < lim {
                    fx0_insert(input, &mut head, &mut prev, ins, mask);
                    ins += 1;
                }
                if ins < end {
                    ins = end;
                }
                p = end;
                miss = 0;
            } else {
                nt = fx0_put_lit(input, out, nt, p);
                p += 1;
                miss += 1;
                let mut step = miss >> skip;
                if step > skcap {
                    step = skcap;
                }
                while step > 0 && p < lim {
                    nt = fx0_put_lit(input, out, nt, p);
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
        nt = fx0_put_lit(input, out, nt, p);
        p += 1;
    }
    nt
}

/// Every input except larger text and prose: smaller tables for small inputs.






pub const FX3_HB: u32 = 15;
pub const FX3_HN: usize = 32768;
pub const FX3_WN: usize = 32768;
pub const FX3_SMALL: usize = 65536;
pub const FX3_HS: usize = 4096;
pub const FX3_WS: usize = 16384;
pub const FX3_NICE: usize = 32;
pub const FX3_INS_MAX: usize = 2;
pub const FX3_TAIL: usize = 1;
pub const FX3_STRIDE: usize = 0;
pub const FX3_BACKTOK: usize = 16;
pub const FX3_LDEPTH: usize = 1;
pub const FX3_SAMPLE: usize = 2048;
pub const FX3_VERIFY: usize = 0;
pub const FX3_LSLACK: usize = 1;
pub const FX3_HLIT: u32 = 80;
pub const FX3_GBASE: i32 = 168;
pub const FX3_T_DEPTH: usize = 2;
pub const FX3_T_LAZY: usize = 0;
pub const FX3_T_SKIP: usize = 3;
pub const FX3_P_DEPTH: usize = 3;
pub const FX3_P_LAZY: usize = 0;
pub const FX3_P_SKIP: usize = 5;
pub const FX3_H_DEPTH: usize = 3;
pub const FX3_H_LAZY: usize = 0;
pub const FX3_H_SKIP: usize = 3;
pub const FX3_Z_DEPTH: usize = 3;
pub const FX3_Z_SKIP: usize = 6;
pub const FX3_Z_CAP: usize = 8;
pub const FX3_B_DEPTH: usize = 4;
pub const FX3_B_LAZY: usize = 0;
pub const FX3_B_SKIP: usize = 4;
pub const FX3_SDIG: u32 = 6;
pub const FX3_S_DEPTH: usize = 1;
pub const FX3_S_LDEPTH: usize = 1;
pub const FX3_S_LAZY: usize = 0;
pub const FX3_SKCAP: usize = 1000000;



























 

 

 

 

 

 

 

 

 

 

 

 

 

 

 

 

 

 

 

 

 

 

 

 

 

 

 

 

pub const Q3_A_HSR: u64 = 48;
pub const Q3_A_HM4: u64 = 0x4A7C150000000000;
pub const Q3_A_MM4: u64 = 16777215;
pub const Q3_A_IH: [usize; 8] = [2, 3, 8, 10, 8, 8, 12, 10];
pub const Q3_A_IT: [usize; 8] = [12, 12, 32, 256, 32, 32, 64, 256];
pub const Q3_A_TS: [usize; 8] = [12, 12, 8, 8, 8, 8, 8, 8];
pub const Q3_A_TL: usize = 0;
pub const Q3_A_ACC: [u64; 8] = [4, 4, 4, 5, 4, 4, 5, 5];
pub const Q3_A_AMAX: usize = 64;
pub const Q3_A_MINL: usize = 3;
pub const Q3_A_BEXT: usize = 0;
pub const Q3_A_BK: usize = 64;
pub const Q3_A_LZT: [usize; 8] = [0, 0, 0, 16, 8, 16, 16, 32];
pub const Q3_A_LZM: usize = 2;
pub const Q3_A_LZN: usize = 1;
pub const Q3_A_SCL: usize = 0;
pub const Q3_A_SLQ: usize = 28;
pub const Q3_A_SC0: usize = 44;
pub const Q3_A_SMODE: usize = 1;
pub const Q3_A_GEN: usize = 0;
pub const Q3_A_GTHR: usize = 900;
pub const Q3_A_HLZT: usize = 0;
pub const Q3_A_H3M: usize = 1;
pub const Q3_A_MAX3: usize = 32768;
pub const Q3_A_GMINL2: usize = 1000;
pub const Q3_A_CTLLO: usize = 100;
pub const Q3_A_CTLHI: usize = 900;
pub const Q3_A_HIMAX: usize = 300;
pub const Q3_A_LZK: usize = 0;
pub const Q3_A_SW2: usize = 0;
pub const Q3_A_FL_DNA_THR: u32 = 64;
pub const Q3_A_FL_DNA_DEPTH: usize = 64;
pub const Q3_A_FL_DNA_M0: usize = 12;
pub const Q3_A_FL_CMAX: u32 = 192;
pub const Q3_A_FL_LOGF: [u32; 16] = [0, 1, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 15];
pub const Q3_A_SMALLN: usize = 65536;
pub const Q3_A_FT_DEPTH: usize = 4;
pub const Q3_A_FT_DEPTH2: usize = 1;
pub const Q3_A_FT_LAZY: usize = 259;
pub const Q3_A_FT_NICE: usize = 258;
pub const Q3_A_FT_IH: usize = 8;
pub const Q3_A_FT_IT: usize = 8;
pub const Q3_A_FT_ACC: usize = 63;
pub const Q3_A_FL_GOOD: usize = 8;
pub const Q3_A_FL_LITQ: usize = 32;
pub const Q3_A_FL_LADJ: usize = 4;
pub const Q3_A_FL_HLOW: usize = 900;
pub const Q3_A_FL_C0Q: usize = 44;
pub const Q3_A_SH_L: [u32; 8] = [128; 8];
pub const Q3_A_SH_D: [u32; 8] = [16; 8];
pub const Q3_A_SH_BUDGET: [usize; 8] = [96; 8];
pub const Q3_A_SH_DM: [u32; 8] = [16; 8];
pub const Q3_A_HM3: u64 = 0x4A7C150000000000;
pub const Q3_A_MINL3: usize = 3;
pub const Q3_A_MM3: u64 = 16777215;

























































pub const FV_HB: u32 = 16;
pub const FV_HN: usize = 32768;
pub const FV_WN: usize = 32768;
pub const FV_SMALL: usize = 65536;
pub const FV_HS: usize = 4096;
pub const FV_WS: usize = 16384;
pub const FV_NICE: usize = 32;
pub const FV_INS_MAX: usize = 2;
pub const FV_TAIL: usize = 1;
pub const FV_STRIDE: usize = 0;
pub const FV_BACKTOK: usize = 16;
pub const FV_LDEPTH: usize = 1;
pub const FV_SAMPLE: usize = 2048;
pub const FV_VERIFY: usize = 0;
pub const FV_LSLACK: usize = 1;
pub const FV_HLIT: u32 = 80;
pub const FV_GBASE: i32 = 168;
pub const FV_T_DEPTH: usize = 2;
pub const FV_T_LAZY: usize = 0;
pub const FV_T_SKIP: usize = 4;
pub const FV_P_DEPTH: usize = 3;
pub const FV_P_LAZY: usize = 0;
pub const FV_P_SKIP: usize = 5;
pub const FV_H_DEPTH: usize = 3;
pub const FV_H_LAZY: usize = 0;
pub const FV_H_SKIP: usize = 3;
pub const FV_Z_DEPTH: usize = 3;
pub const FV_Z_SKIP: usize = 6;
pub const FV_Z_CAP: usize = 8;
pub const FV_B_DEPTH: usize = 1;
pub const FV_B_LAZY: usize = 3;
pub const FV_B_SKIP: usize = 16;
pub const FV_SDIG: u32 = 6;
pub const FV_S_DEPTH: usize = 1;
pub const FV_S_LDEPTH: usize = 1;
pub const FV_S_LAZY: usize = 258;
pub const FV_SKCAP: usize = 1000000;












#[inline(always)]
pub fn r109_eq3(s:&[u8],a:usize,b:usize)->bool{
 s[a]==s[b] && s[a+1]==s[b+1] && s[a+2]==s[b+2]
}
#[inline(always)]
pub fn r109_rawscan<const H:usize,const MODE:usize>(s:&[u8],out:&mut[u32]){
 let mut head=[0u32;H];let mut p=1usize;
 if s.len()>=3{
  let half=(s.len()-1)/2;
  while p<s.len()-2{
   let x=(s[p]as u32)|((s[p+1]as u32)<<8)|((s[p+2]as u32)<<16);
   let key=(x.wrapping_mul(0x9e3779b1)>>16)as usize;
   let k=key%H;out[half+p/2]=head[k];head[k]=p as u32;p+=2;
  }
 }
}

#[inline(always)]
pub fn r109_v3(s:&[u8],p:usize,d:usize)->bool{
 if d<1 || d>32768 || d>p || p>s.len() || s.len()-p<3{return false;}
 r109_eq3(s,p-d,p)
}
#[inline(always)]
pub fn r109_step3(s:&[u8],out:&mut[u32],p:usize,d:usize,nt:usize)->(usize,usize){
 if r109_v3(s,p,d){
  out[nt]=16777216+((d-1)as u32)*256;(nt+1,p+3)
 }else{o_a_emit_lits(s,out,p,2,nt)}
}
pub fn r109_replay(s:&[u8],o:&mut[u32],nt0:usize,p0:usize)->usize{
 let mut nt=nt0;let mut p=p0;
 while p<s.len(){
 if s.len()-p>=4{
  let c=o[(s.len()-1)/2+p/2]as usize;let d=if c<p{p-c}else{0};
  let z=r109_step3(s,o,p,d,nt);nt=z.0;
  if z.1-p==3{let q=o_a_emit_lits(s,o,z.1,1,nt);nt=q.0;p=q.1;}
  else{p=z.1;}
 }else{let z=o_a_emit_lits(s,o,p,4,nt);nt=z.0;p=z.1;}
 }
 nt
}
pub fn r109_bfraw<const H:usize,const MODE:usize>(s:&[u8],o:&mut[u32])->usize{
 r109_rawscan::<H,MODE>(s,o);
 let z=o_a_emit_lits(s,o,0,1,0);r109_replay(s,o,z.0,z.1)
}

// mA: a content-adaptive LZ77 parser for the fixed DEFLATE encoder (mid speed band).
//
// Lineage: fastX fx17 (fast band, Package 2 base) with per-class settings and four search additions.
// * Content class from a small strided byte histogram: DNA-like inputs (0), text (1), peaky
//   high-entropy binaries such as 16-bit weights (2), other binaries (3), zero-rich high-entropy
//   data (4), prose (5), structured text with many digits (6) and flat high-entropy data without a
//   dominant byte value such as images or compressed streams (7). Every class has its own main u118_walk
//   depth, lazy u118_walk depth, lazy threshold, u118_walk stop length, skip shift and insertion pattern.
// * Search: hash chains keyed by the first 4 bytes (3 bytes for classes 3 and 7, 8 bytes for DNA),
//   a main u118_walk and a lazy u118_walk, both with a one-byte quick reject. The main u118_walk (u118_MAIN_GM) and the
//   lazy walks rank candidates by an estimated bit saving (a longer candidate must also save more).
// * Lazy step: move to p+1 while it has a better candidate; when p+1 does not win, p+2 is tried
//   once (u118_LAZY2) and wins if its saving exceeds the pending one by more than u118_L2B/16 bits.
// * Every new match first extends backwards over the tokens just written: literals that match
//   at its distance, and whole earlier matches whose bytes also match there, are folded into it.
//   Optionally (u118_PARTIAL) a previous match whose tail the new match also covers is shortened
//   when a closer source covers the shorter length.
// * DNA-like input: 8-byte chain keys and a 9-byte minimum match (u118_run_dna).
// * Skip acceleration through stretches without matches (capped for zero-rich data).
// * Tables are sized by the input: small inputs clear and touch less memory.
// * Emission optionally re-checks each match (u118_VERIFY = 1); a failed check writes a literal.
//
// Tokens: t < 256 literal, else 2^24 + (dist-1)*256 + (len-3).

pub const u118_HB: u32 = 16;
pub const u118_HN: usize = 65536;
pub const u118_WN: usize = 32768;
/// Inputs of at most u118_SMALL bytes use u118_HS chain heads and a u118_WS window table.
pub const u118_SMALL: usize = 65536;
pub const u118_HS: usize = 8192;
pub const u118_WS: usize = 16384;
pub const u118_NICE: usize = 128;
pub const u118_INS_MAX: usize = 16;
pub const u118_TAIL: usize = 4;
/// Inside long matches, every u118_STRIDE-th position between the head and the tail is chained
/// too (u118_STRIDE = 0: none).
pub const u118_STRIDE: usize = 4;
pub const u118_BACKTOK: usize = 16;
pub const u118_LDEPTH: usize = 1;
pub const u118_SAMPLE: usize = 2048;
pub const u118_VERIFY: usize = 0;
/// Lazy step: a candidate at p+1 needs length >= l + 1 - u118_LSLACK (u118_LSLACK = 1: at least as long
/// as the current match l) and must win on estimated saving (literal worth u118_HLIT/16 bits,
/// match base cost u118_GBASE/16 bits plus extra bits).
pub const u118_LSLACK: usize = 1;
pub const u118_HLIT: u32 = 64;
/// Literal worth (1/16 bit) in the saving estimate for binary classes (3 and 7).
pub const u118_B_HLIT: u32 = 64;
pub const u118_GBASE: i32 = 168;
/// Per class: main chain depth, lazy threshold, skip shift, skip cap (T text, P prose,
/// H high-entropy binary, Z high-entropy binary rich in zero bytes, B other binary,
/// DNA-like input is sent as literals).
pub const u118_T_DEPTH: usize = 4;
pub const u118_T_LAZY: usize = 128;
pub const u118_T_SKIP: usize = 5;
pub const u118_P_DEPTH: usize = 8;
pub const u118_P_LAZY: usize = 258;
pub const u118_P_SKIP: usize = 5;
pub const u118_H_DEPTH: usize = 1;
pub const u118_H_LAZY: usize = 0;
pub const u118_H_SKIP: usize = 2;
pub const u118_Z_DEPTH: usize = 3;
pub const u118_Z_SKIP: usize = 6;
pub const u118_Z_CAP: usize = 8;
pub const u118_B_DEPTH: usize = 4;
pub const u118_B_LAZY: usize = 258;
pub const u118_B_SKIP: usize = 8;
/// Structured text (class 6: text with at least 1/u118_SDIG of the sample in digits): main depth
/// u118_S_DEPTH, lazy u118_walk depth u118_S_LDEPTH, lazy threshold u118_S_LAZY.
pub const u118_SDIG: u32 = 6;
pub const u118_S_DEPTH: usize = 1;
pub const u118_S_LDEPTH: usize = 3;
pub const u118_S_LAZY: usize = 258;
/// Largest skip step (extra literals per miss) outside the Z class.
pub const u118_SKCAP: usize = 1000000;
/// Per-class u118_walk stop (u118_NICE is the text value), lazy u118_walk depth (u118_LDEPTH is the text value),
/// insertion inside matches (u118_INS_MAX/u118_STRIDE/u118_TAIL are the text values).
pub const u118_P_NICE: usize = 258;
pub const u118_S_NICE: usize = 258;
pub const u118_H_NICE: usize = 32;
pub const u118_Z_NICE: usize = 32;
pub const u118_B_NICE: usize = 258;
pub const u118_P_LDEPTH: usize = 1;
pub const u118_H_LDEPTH: usize = 1;
pub const u118_B_LDEPTH: usize = 2;
pub const u118_P_INS: usize = 258;
pub const u118_S_INS: usize = 8;
pub const u118_B_INS: usize = 12;
pub const u118_H_INS: usize = 12;
pub const u118_P_STRIDE: usize = 1;
pub const u118_S_STRIDE: usize = 8;
pub const u118_B_STRIDE: usize = 32;
/// Two-step lazy: when p+1 does not beat the pending match, p+2 is tried (u118_L2DEPTH chain steps)
/// and wins if its saving beats the pending one by more than u118_L2B/16 bits (u118_LAZY2 = 1; 0 = off).
pub const u118_LAZY2: usize = 0;
pub const u118_L2B: i32 = 40;
pub const u118_L2DEPTH: usize = 1;
/// Main u118_walk in u118_gain mode (a longer candidate must also save more).
pub const u118_MAIN_GM: usize = 0;
/// Partial merge: when the new match also covers the last k bytes of the previous match (but not
/// all of it), the previous match is shortened by k if a closer source (at most u118_PDEPTH chain steps)
/// covers its shorter length; the new match then starts k bytes earlier (0 = off).
pub const u118_PARTIAL: usize = 0;
pub const u118_PDEPTH: usize = 8;
/// Class 7: high-entropy input without a dominant byte (no byte above 1/u118_FLAT_DIV of the sample:
/// compressed data, images) parsed with 3-byte keys (F_ settings); class 2 keeps the peaky ones
/// (16-bit weights).
pub const u118_FLAT_ON: usize = 1;
pub const u118_FLAT_DIV: u32 = 16;
/// ... and whose byte collision rate (sum of squared sample counts * 256 / samples^2) is below
/// u118_FLAT_SQ/16 (uniform data: 1; images and compressed streams: 1.1-1.4; 8-bit weights: 1.8).
pub const u118_FLAT_SQ: u64 = 256;
pub const u118_F_DEPTH: usize = 8;
pub const u118_F_LAZY: usize = 0;
pub const u118_F_LDEPTH: usize = 2;
pub const u118_F_SKIP: usize = 6;
pub const u118_H_STRIDE: usize = 32;

/// Eight bytes at `i`, first byte most significant (0 when out of range).



/// Four bytes at `i`, first byte most significant (0 when out of range).



/// Input class from a strided byte histogram of at most ~u118_SAMPLE bytes:
/// 0 DNA-like, 1 text, 2 high-entropy binary, 3 other binary, 4 high-entropy with zeros,
/// 5 prose (text of letters and spaces with almost no code symbols), 6 structured text (many
/// digits: tables, logs, dumps).



/// Estimated saving (1/16 bit) of a match of length `l` at distance `d` over literals.



/// Length of the u118_common prefix of s[a..] and s[b..], at most `cap`.



/// 1 when s[a..a+len] == s[b..b+len]: eight bytes at a time, the last partial word
/// under a mask when a full load fits, else byte by byte.






/// Emit a match (re-checked when u118_VERIFY = 1), else a literal. Returns (tokens, next position).



/// Walk the chain from `start`: the longest match at `p` longer than `have` (with `gm` = 1,
/// a longer candidate must also have a higher estimated saving); distance 0 = none found.
/// Each candidate first compares the byte at `best`.



/// Put position `i` at the head of its chain (key = first four bytes under `mask`);
/// returns the previous head.



/// Distance of the first chain entry from `start` (at most `depth` steps) whose next `len` bytes
/// equal those at `p` (0 = none).



/// Partial merge (u118_PARTIAL = 1): the new match `(l0, d)` at `p0` also covers the last `k` bytes of
/// the previous match token `t` (`w` bytes, ending at `p0`), but not all of it. When a closer
/// source (at most u118_PDEPTH chain steps) covers its first `w - k` bytes, that token is shortened by
/// `k` and the new match starts `k` bytes earlier. Returns the new `(p, l)`.



/// Best match at `p` longer than `have` and at least `minl` long; (0, 0) when none.



/// The u118_parse for one input class (inlined so the text classes get constant settings), with
/// H chain heads and a window table of W entries.



/// DNA settings: key bytes, minimum match, main depth, lazy threshold/depth, skip shift.
pub const u118_D_ON: usize = 1;
pub const u118_D_KEY: u32 = 8;
pub const u118_D_MINL: usize = 9;
pub const u118_D_DEPTH: usize = 1;
pub const u118_D_LAZY: usize = 0;
pub const u118_D_LDEPTH: usize = 1;
pub const u118_D_SKIP: usize = 8;
pub const u118_D_GM: usize = 0;

/// Put position `i` at the head of its chain (key = first u118_D_KEY bytes); returns the previous head.



/// DNA-like input: chains keyed by the first u118_D_KEY bytes, matches of at least u118_D_MINL bytes.
































/// Bytes the router samples.
pub const u118_O_R_SAMPLE: usize = 512;
/// Inputs shorter than this go to the small-input engine.
pub const u118_O_R_TINY: usize = 0;

/// How many bytes agree at `a < b` and `b`, up to `cap`; needs `b + cap <= input.len()`.


/// The 4-byte hash at `p`; needs `p + 4 <= input.len()`.


/// Greedy coverage of `input[start..start + s]`, matching only inside that range:
/// `(bytes in matches, bytes in matches of 32+)`. Needs `4 <= s` and `start + s <= input.len()`.


/// Byte histogram of the first `s` bytes; needs `s <= input.len()`.



/// Sum of `hist[a..b]`; needs `b <= 256`.



/// Number of distinct byte values in the histogram.


/// The engine for this input: its index in `u118_parse`. Shares are compared per 100000 sampled bytes.




/// Engines 0..0 of the portfolio.



/// Engines 1..1 of the portfolio.



/// Engines 2..2 of the portfolio.



/// Engines 3..3 of the portfolio.



/// Engines 4..4 of the portfolio.



/// Engines 5..5 of the portfolio.



/// Engines 6..6 of the portfolio.



/// Engines 7..7 of the portfolio.






// ===== engine a: w_opt05.rs =====

pub const u118_O_A_HSR: u64 = 48;
pub const u118_O_A_HM4: u64 = 0x7F4A7C1500000000;
pub const u118_O_A_MM4: u64 = 4294967295;
pub const u118_O_A_IH: [usize; 8] = [2, 3, 8, 10, 8, 8, 12, 10];
pub const u118_O_A_IT: [usize; 8] = [12, 12, 32, 256, 32, 32, 64, 256];
pub const u118_O_A_TS: [usize; 8] = [12, 12, 8, 8, 8, 8, 8, 8];
pub const u118_O_A_TL: usize = 0;
pub const u118_O_A_ACC: [u64; 8] = [4, 4, 4, 5, 4, 4, 5, 5];
pub const u118_O_A_AMAX: usize = 64;
pub const u118_O_A_MINL: usize = 4;
pub const u118_O_A_BEXT: usize = 0;
pub const u118_O_A_BK: usize = 64;
pub const u118_O_A_LZT: [usize; 8] = [0, 0, 0, 16, 8, 16, 16, 32];
pub const u118_O_A_LZM: usize = 2;
pub const u118_O_A_LZN: usize = 1;
pub const u118_O_A_SCL: usize = 0;
pub const u118_O_A_SLQ: usize = 28;
pub const u118_O_A_SC0: usize = 44;
pub const u118_O_A_SMODE: usize = 1;
pub const u118_O_A_GEN: usize = 0;
pub const u118_O_A_GTHR: usize = 900;
pub const u118_O_A_HLZT: usize = 0;
pub const u118_O_A_H3M: usize = 1;
pub const u118_O_A_MAX3: usize = 16384;
pub const u118_O_A_GMINL2: usize = 1000;
pub const u118_O_A_CTLLO: usize = 100;
pub const u118_O_A_CTLHI: usize = 900;
pub const u118_O_A_HIMAX: usize = 300;
pub const u118_O_A_LZK: usize = 0;
pub const u118_O_A_SW2: usize = 0;

/// Little-endian 4-byte load at `p`; 0 when out of range.


/// Little-endian 8-byte load at `p` (two 4-byte halves); 0 when out of range.



/// Index (0..7) of the first differing byte of two little-endian words, given their xor (!= 0).



/// Common prefix of positions `a < b` beyond the first 8 bytes, up to `cap` (search only; never trusted).



/// Copy of `fast_len` for the lazy site.
/// Common prefix of positions `a < b` beyond the first 8 bytes, up to `cap` (search only; never trusted).



/// Copy of `fast_len` for the lazy chain.
/// Common prefix of positions `a < b` beyond the first 8 bytes, up to `cap` (search only; never trusted).



/// Hash of the word at `p` with multiplier `mk` (= the golden-ratio constant shifted left by 32: first 4 bytes, by
/// 40: first 3 bytes), 64 - u118_O_A_HSR bits.



/// Hash of the 8 bytes at `p` (long table), 16 bits.



/// The candidate `(cs, cl)` (short / long table entries, pos+1 encoded, 0 = none) at `p`: the long one when its
/// first 8 bytes agree, else the short one. Returns `len | dist << 9` (len >= u118_O_A_MINL), or 0.



/// Lazy-site copy of `eval` (keeps both inlined).
/// The candidate `(cs, cl)` (short / long table entries, pos+1 encoded, 0 = none) at `p`: the long one when its
/// first 8 bytes agree, else the short one. Returns `len | dist << 9` (len >= u118_O_A_MINL), or 0.



/// Lazy-chain copy of `eval` (keeps both inlined).
/// The candidate `(cs, cl)` (short / long table entries, pos+1 encoded, 0 = none) at `p`: the long one when its
/// first 8 bytes agree, else the short one. Returns `len | dist << 9` (len >= u118_O_A_MINL), or 0.



/// Insert positions `from .. to` into both tables.



/// Insert every u118_O_A_TS-th position of `from .. to` into both tables (u118_O_A_TL == 1: the long table only).



/// Insert the inside `from .. to` of an emitted match: its first u118_O_A_IH and last u118_O_A_IT positions.



/// Literal-scan step after `k` probes: 1 + (k >> u118_O_A_ACC), at most u118_O_A_AMAX.



/// How far the match `(d, l)` found at `p` extends backwards, staying at or after `lo` (8-byte word steps).



/// 1 iff the 8-byte windows ending at `q` and at `q - d` are both in range (`q >= d + 8`).



/// 1 iff the byte before `q` repeats at distance `d` (so a match found at `q` also starts at `q - 1`).



/// Insert `p` at short / long buckets `hs`, `hl` and read the entries at `hs1`, `hl1` (before the insertion):
/// `cs1 << 32 | cl1`.



/// Read the entries at short / long buckets `hs`, `hl` and u118_insert `q` there: `cs << 32 | cl`.



/// Software-pipelined scan from `pos`: each iteration inserts the probe position `p`, loads the table entries of the
/// next probe position and evaluates `p`'s entries (loaded one iteration earlier). Returns `p << 25 | len | dist << 9`
/// of the first match (or `n << 25`), `q << 32 | probes` and `cs << 32 | cl` (the next probe position `q` and its
/// preloaded table entries, for the lazy step).



/// One further lazy step after a lazy win `m` that starts at `s`: probe `s + 1` (inserting it); returns the new
/// match with bit 63 set when the candidate there won by ending at least u118_O_A_LZM bytes later (continue), the longer
/// match at `s` when the candidate also starts at `s` (stop), else `m` (stop).



/// Estimated saving (quarter bits, offset by 4096) of coding `l` bytes as a match at distance `d`: `l` literals of
/// u118_O_A_SLQ quarter bits against u118_O_A_SC0 plus 4 per extra bit.


/// Further lazy steps (at most u118_O_A_LZN) after a lazy win `m0` (see `lazy_step`).



/// The next match at or after `pos`: `start << 25 | dist << 9 | len`, or `n << 25` when there is none.
/// Lazy step (match shorter than u118_O_A_LZT, next probe at `p + 1`): the candidate at `p + 1` wins when it also starts at
/// `p` and is longer, or when it ends at least u118_O_A_LZM bytes later. Backward extension (u118_O_A_BEXT) only after acceleration.



/// The carried result when it starts at `pos` (its literal u118_run was emitted), else a fresh `u118_find`.


/// Per-file mode from a strided sample of about 1024 bytes: 1 genome (at least u118_O_A_GTHR per mille A C G T N or
/// newline), 2 machine-code-like binary (u118_O_A_CTLLO..CTLHI per mille bytes < 9, fewer than u118_O_A_HIMAX per mille >= 128),
/// else 0.


// ------------------------------------------------------------------ trusted core

/// Trusted: little-endian 8-byte word at `p` (0 when out of range).



/// Trusted: little-endian 4-byte word at `p` (0 when out of range).



/// Trusted: 1 iff `cap >= 8`, `cap - l < 8` and the 8-byte words at `a + cap - 8` and `b + cap - 8` are equal.



/// Trusted: 1 iff `4 <= cap < 8` and the 4-byte words at `a`, `b` and at `a + cap - 4`, `b + cap - 4` are equal.



/// Trusted: a length `l <= cap` over which the bytes at `a` and `b` provably agree, found with word compares.



/// Trusted: how many bytes agree at `a` and `b`, up to `cap` (word compares, then bytes).



/// True iff `(ch, d)` at `pos` is in range and its bytes agree.



/// Trusted: `cnt >= 1` literals from `pos0` (stopping at the input end).



/// Trusted: the match `(l, d)` at `pos` if it verifies, else `lits` literals.




// ============================ DNA phase (genome mode): the J2/c5 `fl` DNA parser (literal runs over cheap bytes,
// cost-checked chain matches at expensive bytes) with its own trusted kit copies (fl_ prefix), u118_run as a sequential
// phase before the main parser (which then starts at the input end).
pub const u118_O_A_FL_DNA_THR: u32 = 64;
pub const u118_O_A_FL_DNA_DEPTH: usize = 64;
pub const u118_O_A_FL_DNA_M0: usize = 12;
pub const u118_O_A_FL_CMAX: u32 = 192;
/// log2(1 + i/16) in 1/16 bits.
pub const u118_O_A_FL_LOGF: [u32; 16] = [0, 1, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 15];

// ---------------------------------------------------------------- trusted core (DNA copy)

/// Byte-wise u118_common prefix length (trusted).
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



/// Common prefix of `a < b`, at most `cap` (word compare; search only, never trusted).



/// 16-bit hash of the word at `p` shifted left by `hsh` (32: first 4 bytes, 0: first 8 bytes).



/// log2(f) in 1/16 bits (0 for f = 0).


/// Strided byte histogram of about 4096 samples.


/// Literal cost per byte value (1/16 bits) from the histogram: log2(total / f), unseen bytes u118_O_A_FL_CMAX.


/// Number of consecutive cheap bytes (cost < u118_O_A_FL_DNA_THR) from `pos`.


/// Literal cost (1/16 bits) of the `l` bytes at `pos` (l <= 258).


/// DEFLATE distance extra bits.



/// DEFLATE length extra bits.



/// 1 iff the match (l, d) at `pos` is estimated cheaper than its literals: u118_O_A_FL_DNA_M0 bits + extra bits.


/// Longest match (ties: the u118_closest) along the chain from `start` (pos+1 encoded). Returns `len | dist << 9`.


/// DNA: with `depth > 0`, u118_insert `p` into the 4-byte-hash chains and u118_walk them (depth 0: nothing).


/// Insert positions `from .. to` into the chains (hash of the first 4 bytes if hsh = 32, 8 bytes if hsh = 0).



/// DNA u118_parse: literal runs over cheap bytes; at an expensive byte, search and take the match if it is estimated
/// cheaper than its literals. Only searched positions and match interiors enter the chains.


// ---------------------------------------------------------------- small-file phase: the J2/c5 fl price-lazy parser
// with its class-T configuration (deep chains, full lazy), for inputs shorter than u118_O_A_SMALLN.
pub const u118_O_A_SMALLN: usize = 65536;
pub const u118_O_A_FT_DEPTH: usize = 4;
pub const u118_O_A_FT_DEPTH2: usize = 1;
pub const u118_O_A_FT_LAZY: usize = 259;
pub const u118_O_A_FT_NICE: usize = 258;
pub const u118_O_A_FT_IH: usize = 8;
pub const u118_O_A_FT_IT: usize = 8;
pub const u118_O_A_FT_ACC: usize = 63;
pub const u118_O_A_FL_GOOD: usize = 8;
pub const u118_O_A_FL_LITQ: usize = 32;
pub const u118_O_A_FL_LADJ: usize = 4;
pub const u118_O_A_FL_HLOW: usize = 900;
pub const u118_O_A_FL_C0Q: usize = 44;

/// Little-endian 4-byte load at `p`; 0 when out of range.



/// Estimated saving (quarter bits, offset by 4096) of coding `l` bytes as a match at `d`.



/// Fixed-point log2 with 8 fractional bits (linear between powers of two); x >= 1.


/// Entropy of the histogram in 1/256 bits per symbol.


/// Literal cost (quarter bits) for low-entropy inputs.



/// Walk the chain from `start` (pos+1 encoded, 0 = none) for the match with the best estimated saving
/// that is longer than `bl0` and saves more than `bs0`; stop at length `nice`. Returns `len | dist << 9`, or 0.



/// With `depth > 0`: u118_insert `pos` into the chains when `ins == 1`, then u118_walk them. Returns
/// `len | dist << 9` of a match longer than `bl0` saving more than `bs0`, or 0.



/// Insert the inside `from .. to` of an emitted match: its first `ih` and last `it` positions.



/// Literal-u118_run length after `miss` consecutive misses: 1 + (miss >> acc), at most 32.



/// Literal cost (quarter bits) used by the lazy parser: from the entropy for low-entropy inputs, else u118_O_A_FL_LITQ.



/// Hash shift: 8-byte hash (0) for low-entropy inputs, 4-byte hash (32) otherwise.



/// Price-lazy o_a_parse (the jgreedy jg1c algorithm) with the class configuration `cf`.



/// RLE u118_parse: a distance-1 u118_run match wherever the previous byte repeats >= 3 times, else one literal.



// Untrusted RLE decision probe; a bounded counter establishes termination.




/// The floor phase: the whole input with the DNA parser when `m == 1` (genome mode), with the class-T price-lazy
/// parser for inputs shorter than u118_O_A_SMALLN, else nothing: `(ntok, pos)`.


/// Genome mode: literal costs from a sampled histogram, then the DNA parser.


// Encoder-aware shaping constants: only untrusted candidate selection changes.
pub const u118_O_A_SH_L: [u32; 8] = [128; 8];
pub const u118_O_A_SH_D: [u32; 8] = [16; 8];
pub const u118_O_A_SH_BUDGET: [usize; 8] = [96; 8];
pub const u118_O_A_SH_DM: [u32; 8] = [16; 8];








// Count candidate match codes. Candidate decisions are not output tokens.








// Replay cached decisions; every shorter match/literal is emitted and verified by the trusted kit.

// Merge adjacent cached literal runs before trusted emission.








// Frequency accounting is fused with candidate collection.






/// Small inputs: the class-T price-lazy parser.




// ============================ h3 o_a_mode (machine-code-like binaries): its own copy of the search (3-byte short hash,
// min length 3) and of the trusted kit (h3_ prefix), u118_run as a floor phase over the whole input.
pub const u118_O_A_HM3: u64 = 0x4A7C150000000000;
pub const u118_O_A_MINL3: usize = 3;
pub const u118_O_A_MM3: u64 = 16777215;

/// Little-endian 4-byte load at `p`; 0 when out of range.


/// Little-endian 8-byte load at `p` (two 4-byte halves); 0 when out of range.


/// Index (0..7) of the first differing byte of two little-endian words, given their xor (!= 0).


/// Common prefix of positions `a < b` beyond the first 8 bytes, up to `cap` (search only; never trusted).


/// Copy of `fast_len` for the lazy site.
/// Common prefix of positions `a < b` beyond the first 8 bytes, up to `cap` (search only; never trusted).


/// Copy of `fast_len` for the lazy chain.
/// Common prefix of positions `a < b` beyond the first 8 bytes, up to `cap` (search only; never trusted).


/// Hash of the word at `p` with multiplier `mk` (= the golden-ratio constant shifted left by 32: first 4 bytes, by
/// 40: first 3 bytes), 64 - u118_O_A_HSR bits.


/// Hash of the 8 bytes at `p` (long table), 16 bits.


/// The candidate `(cs, cl)` (short / long table entries, pos+1 encoded, 0 = none) at `p`: the long one when its
/// first 8 bytes agree, else the short one. Returns `len | dist << 9` (len >= u118_O_A_MINL3), or 0.


/// Lazy-site copy of `eval` (keeps both inlined).
/// The candidate `(cs, cl)` (short / long table entries, pos+1 encoded, 0 = none) at `p`: the long one when its
/// first 8 bytes agree, else the short one. Returns `len | dist << 9` (len >= u118_O_A_MINL3), or 0.


/// Lazy-chain copy of `eval` (keeps both inlined).
/// The candidate `(cs, cl)` (short / long table entries, pos+1 encoded, 0 = none) at `p`: the long one when its
/// first 8 bytes agree, else the short one. Returns `len | dist << 9` (len >= u118_O_A_MINL3), or 0.


/// Insert positions `from .. to` into both tables.


/// Insert every u118_O_A_TS-th position of `from .. to` into both tables (u118_O_A_TL == 1: the long table only).


/// Insert the inside `from .. to` of an emitted match: its first u118_O_A_IH and last u118_O_A_IT positions.


/// Literal-scan step after `k` probes: 1 + (k >> u118_O_A_ACC), at most u118_O_A_AMAX.


/// How far the match `(d, l)` found at `p` extends backwards, staying at or after `lo` (8-byte word steps).


/// 1 iff the 8-byte windows ending at `q` and at `q - d` are both in range (`q >= d + 8`).


/// 1 iff the byte before `q` repeats at distance `d` (so a match found at `q` also starts at `q - 1`).


/// Insert `p` at short / long buckets `hs`, `hl` and read the entries at `hs1`, `hl1` (before the insertion):
/// `cs1 << 32 | cl1`.


/// Read the entries at short / long buckets `hs`, `hl` and u118_insert `q` there: `cs << 32 | cl`.


/// Software-pipelined scan from `pos`: each iteration inserts the probe position `p`, loads the table entries of the
/// next probe position and evaluates `p`'s entries (loaded one iteration earlier). Returns `p << 25 | len | dist << 9`
/// of the first match (or `n << 25`), `q << 32 | probes` and `cs << 32 | cl` (the next probe position `q` and its
/// preloaded table entries, for the lazy step).


/// One further lazy step after a lazy win `m` that starts at `s`: probe `s + 1` (inserting it); returns the new
/// match with bit 63 set when the candidate there won by ending at least u118_O_A_LZM bytes later (continue), the longer
/// match at `s` when the candidate also starts at `s` (stop), else `m` (stop).


/// Estimated saving (quarter bits, offset by 4096) of coding `l` bytes as a match at distance `d`: `l` literals of
/// u118_O_A_SLQ quarter bits against u118_O_A_SC0 plus 4 per extra bit.


/// Further lazy steps (at most u118_O_A_LZN) after a lazy win `m0` (see `lazy_step`).


/// The next match at or after `pos`: `start << 25 | dist << 9 | len`, or `n << 25` when there is none.
/// Lazy step (match shorter than u118_O_A_LZT, next probe at `p + 1`): the candidate at `p + 1` wins when it also starts at
/// `p` and is longer, or when it ends at least u118_O_A_LZM bytes later. Backward extension (u118_O_A_BEXT) only after acceleration.


/// The carried result when it starts at `pos` (its literal u118_run was emitted), else a fresh `u118_find`.


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


// ------------------------------------------------------------------ the u118_parse loop

/// Per iteration one trusted call: the literal u118_run before the next match (`emit_lits`, the match is carried to the
/// next iteration), or the match itself (`emit_step`), plus untrusted bookkeeping.



/// The mode-0 main parser from `pos0` (the floor phase's end).



/// Sequential phases (no if/else between two loop-heavy parsers): the DNA phase covers the whole input in genome
/// mode and returns `(ntok, n)`, else `(0, 0)`; the main parser continues from its end.







/// Bytes the router samples.
pub const u118_Y_R_SAMPLE: usize = 65536;
/// Inputs shorter than this go to the small-input engine.
pub const u118_Y_R_TINY: usize = 0;

/// How many bytes agree at `a < b` and `b`, up to `cap`; needs `b + cap <= input.len()`.


/// The 4-byte hash at `p`; needs `p + 4 <= input.len()`.


/// Greedy coverage of `input[start..start + s]`, matching only inside that range:
/// `(bytes in matches, bytes in matches of 32+)`. Needs `4 <= s` and `start + s <= input.len()`.


/// Byte histogram of the first `s` bytes; needs `s <= input.len()`.


/// Sum of `hist[a..b]`; needs `b <= 256`.


/// Number of distinct byte values in the histogram.


/// The engine for this input: its index in `u118_parse`. Shares are compared per 100000 sampled bytes.



/// Engines 0..0 of the portfolio.



/// Engines 1..1 of the portfolio.



/// Engines 2..2 of the portfolio.



/// Engines 3..3 of the portfolio.



/// Engines 4..4 of the portfolio.



/// Engines 5..5 of the portfolio.



/// Engines 6..6 of the portfolio.






// ===== engine a: mix5.a.rs =====

pub const u118_Y_A_IH: [usize; 8] = [8, 10, 10, 10, 10, 10, 10, 10];
pub const u118_Y_A_IT: [usize; 8] = [32, 256, 256, 256, 256, 256, 256, 256];
pub const u118_Y_A_TS: [usize; 8] = [8, 8, 8, 8, 8, 8, 8, 8];
pub const u118_Y_A_ACC: [u64; 8] = [4, 5, 5, 5, 5, 5, 5, 5];
pub const u118_Y_A_LZT: [usize; 8] = [0, 16, 32, 32, 32, 32, 32, 32];

/// Little-endian 4-byte load at `p`; 0 when out of range.


/// Little-endian 8-byte load at `p` (two 4-byte halves); 0 when out of range.


/// Index (0..7) of the first differing byte of two little-endian words, given their xor (!= 0).


/// Common prefix of positions `a < b` beyond the first 8 bytes, up to `cap` (search only; never trusted).


/// Copy of `fast_len` for the lazy site.
/// Common prefix of positions `a < b` beyond the first 8 bytes, up to `cap` (search only; never trusted).


/// Copy of `fast_len` for the lazy chain.
/// Common prefix of positions `a < b` beyond the first 8 bytes, up to `cap` (search only; never trusted).


/// Hash of the word at `p` with multiplier `mk` (= the golden-ratio constant shifted left by 32: first 4 bytes, by
/// 40: first 3 bytes), 64 - u118_O_A_HSR bits.


/// Hash of the 8 bytes at `p` (long table), 16 bits.


/// The candidate `(cs, cl)` (short / long table entries, pos+1 encoded, 0 = none) at `p`: the long one when its
/// first 8 bytes agree, else the short one. Returns `len | dist << 9` (len >= u118_O_A_MINL), or 0.


/// Lazy-site copy of `eval` (keeps both inlined).
/// The candidate `(cs, cl)` (short / long table entries, pos+1 encoded, 0 = none) at `p`: the long one when its
/// first 8 bytes agree, else the short one. Returns `len | dist << 9` (len >= u118_O_A_MINL), or 0.


/// Lazy-chain copy of `eval` (keeps both inlined).
/// The candidate `(cs, cl)` (short / long table entries, pos+1 encoded, 0 = none) at `p`: the long one when its
/// first 8 bytes agree, else the short one. Returns `len | dist << 9` (len >= u118_O_A_MINL), or 0.


/// Insert positions `from .. to` into both tables.


/// Insert every u118_Y_A_TS-th position of `from .. to` into both tables (u118_O_A_TL == 1: the long table only).


/// Insert the inside `from .. to` of an emitted match: its first u118_Y_A_IH and last u118_Y_A_IT positions.


/// Literal-scan step after `k` probes: 1 + (k >> u118_Y_A_ACC), at most u118_O_A_AMAX.


/// How far the match `(d, l)` found at `p` extends backwards, staying at or after `lo` (8-byte word steps).


/// 1 iff the 8-byte windows ending at `q` and at `q - d` are both in range (`q >= d + 8`).


/// 1 iff the byte before `q` repeats at distance `d` (so a match found at `q` also starts at `q - 1`).


/// Insert `p` at short / long buckets `hs`, `hl` and read the entries at `hs1`, `hl1` (before the insertion):
/// `cs1 << 32 | cl1`.


/// Read the entries at short / long buckets `hs`, `hl` and u118_insert `q` there: `cs << 32 | cl`.


/// Software-pipelined scan from `pos`: each iteration inserts the probe position `p`, loads the table entries of the
/// next probe position and evaluates `p`'s entries (loaded one iteration earlier). Returns `p << 25 | len | dist << 9`
/// of the first match (or `n << 25`), `q << 32 | probes` and `cs << 32 | cl` (the next probe position `q` and its
/// preloaded table entries, for the lazy step).


/// One further lazy step after a lazy win `m` that starts at `s`: probe `s + 1` (inserting it); returns the new
/// match with bit 63 set when the candidate there won by ending at least u118_O_A_LZM bytes later (continue), the longer
/// match at `s` when the candidate also starts at `s` (stop), else `m` (stop).


/// Estimated saving (quarter bits, offset by 4096) of coding `l` bytes as a match at distance `d`: `l` literals of
/// u118_O_A_SLQ quarter bits against u118_O_A_SC0 plus 4 per extra bit.


/// Further lazy steps (at most u118_O_A_LZN) after a lazy win `m0` (see `lazy_step`).


/// The next match at or after `pos`: `start << 25 | dist << 9 | len`, or `n << 25` when there is none.
/// Lazy step (match shorter than u118_Y_A_LZT, next probe at `p + 1`): the candidate at `p + 1` wins when it also starts at
/// `p` and is longer, or when it ends at least u118_O_A_LZM bytes later. Backward extension (u118_O_A_BEXT) only after acceleration.


/// The carried result when it starts at `pos` (its literal u118_run was emitted), else a fresh `u118_find`.


/// Per-file mode from a strided sample of about 1024 bytes: 1 genome (at least u118_O_A_GTHR per mille A C G T N or
/// newline), 2 machine-code-like binary (u118_O_A_CTLLO..CTLHI per mille bytes < 9, fewer than u118_O_A_HIMAX per mille >= 128),
/// else 0.


// ------------------------------------------------------------------ trusted core

/// Trusted: little-endian 8-byte word at `p` (0 when out of range).


/// Trusted: little-endian 4-byte word at `p` (0 when out of range).


/// Trusted: 1 iff `cap >= 8`, `cap - l < 8` and the 8-byte words at `a + cap - 8` and `b + cap - 8` are equal.


/// Trusted: 1 iff `4 <= cap < 8` and the 4-byte words at `a`, `b` and at `a + cap - 4`, `b + cap - 4` are equal.


/// Trusted: a length `l <= cap` over which the bytes at `a` and `b` provably agree, found with word compares.



/// Trusted: how many bytes agree at `a` and `b`, up to `cap` (word compares, then bytes).



/// True iff `(ch, d)` at `pos` is in range and its bytes agree.



/// Trusted: `cnt >= 1` literals from `pos0` (stopping at the input end).


/// Trusted: the match `(l, d)` at `pos` if it verifies, else `lits` literals.




// ============================ DNA phase (genome mode): the J2/c5 `fl` DNA parser (literal runs over cheap bytes,
// cost-checked chain matches at expensive bytes) with its own trusted kit copies (fl_ prefix), u118_run as a sequential
// phase before the main parser (which then starts at the input end).
/// log2(1 + i/16) in 1/16 bits.

// ---------------------------------------------------------------- trusted core (DNA copy)

/// Byte-wise u118_common prefix length (trusted).
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


/// Common prefix of `a < b`, at most `cap` (word compare; search only, never trusted).


/// 16-bit hash of the word at `p` shifted left by `hsh` (32: first 4 bytes, 0: first 8 bytes).


/// log2(f) in 1/16 bits (0 for f = 0).


/// Strided byte histogram of about 4096 samples.


/// Literal cost per byte value (1/16 bits) from the histogram: log2(total / f), unseen bytes u118_O_A_FL_CMAX.


/// Number of consecutive cheap bytes (cost < u118_O_A_FL_DNA_THR) from `pos`.


/// Literal cost (1/16 bits) of the `l` bytes at `pos` (l <= 258).


/// DEFLATE distance extra bits.


/// DEFLATE length extra bits.


/// 1 iff the match (l, d) at `pos` is estimated cheaper than its literals: u118_O_A_FL_DNA_M0 bits + extra bits.


/// Longest match (ties: the u118_closest) along the chain from `start` (pos+1 encoded). Returns `len | dist << 9`.


/// DNA: with `depth > 0`, u118_insert `p` into the 4-byte-hash chains and u118_walk them (depth 0: nothing).


/// Insert positions `from .. to` into the chains (hash of the first 4 bytes if hsh = 32, 8 bytes if hsh = 0).


/// DNA u118_parse: literal runs over cheap bytes; at an expensive byte, search and take the match if it is estimated
/// cheaper than its literals. Only searched positions and match interiors enter the chains.


// ---------------------------------------------------------------- small-file phase: the J2/c5 fl price-lazy parser
// with its class-T configuration (deep chains, full lazy), for inputs shorter than u118_O_A_SMALLN.

/// Little-endian 4-byte load at `p`; 0 when out of range.


/// Estimated saving (quarter bits, offset by 4096) of coding `l` bytes as a match at `d`.


/// Fixed-point log2 with 8 fractional bits (linear between powers of two); x >= 1.


/// Entropy of the histogram in 1/256 bits per symbol.


/// Literal cost (quarter bits) for low-entropy inputs.


/// Walk the chain from `start` (pos+1 encoded, 0 = none) for the match with the best estimated saving
/// that is longer than `bl0` and saves more than `bs0`; stop at length `nice`. Returns `len | dist << 9`, or 0.


/// With `depth > 0`: u118_insert `pos` into the chains when `ins == 1`, then u118_walk them. Returns
/// `len | dist << 9` of a match longer than `bl0` saving more than `bs0`, or 0.


/// Insert the inside `from .. to` of an emitted match: its first `ih` and last `it` positions.


/// Literal-u118_run length after `miss` consecutive misses: 1 + (miss >> acc), at most 32.


/// Literal cost (quarter bits) used by the lazy parser: from the entropy for low-entropy inputs, else u118_O_A_FL_LITQ.


/// Hash shift: 8-byte hash (0) for low-entropy inputs, 4-byte hash (32) otherwise.


/// Price-lazy a_parse (the jgreedy jg1c algorithm) with the class configuration `cf`.


/// RLE u118_parse: a distance-1 u118_run match wherever the previous byte repeats >= 3 times, else one literal.




// Untrusted RLE decision probe; a bounded counter establishes termination.






/// The floor phase: the whole input with the DNA parser when `m == 1` (genome mode), with the class-T price-lazy
/// parser for inputs shorter than u118_O_A_SMALLN, else nothing: `(ntok, pos)`.


/// Genome mode: literal costs from a sampled histogram, then the DNA parser.


// Encoder-aware shaping constants: only untrusted candidate selection changes.








// Count candidate match codes. Candidate decisions are not output tokens.








// Replay cached decisions; every shorter match/literal is emitted and verified by the trusted kit.

// Merge adjacent cached literal runs before trusted emission.







// Frequency accounting is fused with candidate collection.





/// Small inputs: the class-T price-lazy parser.


// ============================ h3 y_a_mode (machine-code-like binaries): its own copy of the search (3-byte short hash,
// min length 3) and of the trusted kit (h3_ prefix), u118_run as a floor phase over the whole input.

/// Little-endian 4-byte load at `p`; 0 when out of range.


/// Little-endian 8-byte load at `p` (two 4-byte halves); 0 when out of range.


/// Index (0..7) of the first differing byte of two little-endian words, given their xor (!= 0).


/// Common prefix of positions `a < b` beyond the first 8 bytes, up to `cap` (search only; never trusted).


/// Copy of `fast_len` for the lazy site.
/// Common prefix of positions `a < b` beyond the first 8 bytes, up to `cap` (search only; never trusted).


/// Copy of `fast_len` for the lazy chain.
/// Common prefix of positions `a < b` beyond the first 8 bytes, up to `cap` (search only; never trusted).


/// Hash of the word at `p` with multiplier `mk` (= the golden-ratio constant shifted left by 32: first 4 bytes, by
/// 40: first 3 bytes), 64 - u118_O_A_HSR bits.


/// Hash of the 8 bytes at `p` (long table), 16 bits.


/// The candidate `(cs, cl)` (short / long table entries, pos+1 encoded, 0 = none) at `p`: the long one when its
/// first 8 bytes agree, else the short one. Returns `len | dist << 9` (len >= u118_O_A_MINL3), or 0.



/// Lazy-site copy of `eval` (keeps both inlined).
/// The candidate `(cs, cl)` (short / long table entries, pos+1 encoded, 0 = none) at `p`: the long one when its
/// first 8 bytes agree, else the short one. Returns `len | dist << 9` (len >= u118_O_A_MINL3), or 0.



/// Lazy-chain copy of `eval` (keeps both inlined).
/// The candidate `(cs, cl)` (short / long table entries, pos+1 encoded, 0 = none) at `p`: the long one when its
/// first 8 bytes agree, else the short one. Returns `len | dist << 9` (len >= u118_O_A_MINL3), or 0.



/// Insert positions `from .. to` into both tables.



/// Insert every u118_Y_A_TS-th position of `from .. to` into both tables (u118_O_A_TL == 1: the long table only).



/// Insert the inside `from .. to` of an emitted match: its first u118_Y_A_IH and last u118_Y_A_IT positions.



/// Literal-scan step after `k` probes: 1 + (k >> u118_Y_A_ACC), at most u118_O_A_AMAX.


/// How far the match `(d, l)` found at `p` extends backwards, staying at or after `lo` (8-byte word steps).


/// 1 iff the 8-byte windows ending at `q` and at `q - d` are both in range (`q >= d + 8`).


/// 1 iff the byte before `q` repeats at distance `d` (so a match found at `q` also starts at `q - 1`).


/// Insert `p` at short / long buckets `hs`, `hl` and read the entries at `hs1`, `hl1` (before the insertion):
/// `cs1 << 32 | cl1`.


/// Read the entries at short / long buckets `hs`, `hl` and u118_insert `q` there: `cs << 32 | cl`.


/// Software-pipelined scan from `pos`: each iteration inserts the probe position `p`, loads the table entries of the
/// next probe position and evaluates `p`'s entries (loaded one iteration earlier). Returns `p << 25 | len | dist << 9`
/// of the first match (or `n << 25`), `q << 32 | probes` and `cs << 32 | cl` (the next probe position `q` and its
/// preloaded table entries, for the lazy step).



/// One further lazy step after a lazy win `m` that starts at `s`: probe `s + 1` (inserting it); returns the new
/// match with bit 63 set when the candidate there won by ending at least u118_O_A_LZM bytes later (continue), the longer
/// match at `s` when the candidate also starts at `s` (stop), else `m` (stop).



/// Estimated saving (quarter bits, offset by 4096) of coding `l` bytes as a match at distance `d`: `l` literals of
/// u118_O_A_SLQ quarter bits against u118_O_A_SC0 plus 4 per extra bit.


/// Further lazy steps (at most u118_O_A_LZN) after a lazy win `m0` (see `lazy_step`).



/// The next match at or after `pos`: `start << 25 | dist << 9 | len`, or `n << 25` when there is none.
/// Lazy step (match shorter than u118_Y_A_LZT, next probe at `p + 1`): the candidate at `p + 1` wins when it also starts at
/// `p` and is longer, or when it ends at least u118_O_A_LZM bytes later. Backward extension (u118_O_A_BEXT) only after acceleration.



/// The carried result when it starts at `pos` (its literal u118_run was emitted), else a fresh `u118_find`.


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



// ------------------------------------------------------------------ the u118_parse loop

/// Per iteration one trusted call: the literal u118_run before the next match (`emit_lits`, the match is carried to the
/// next iteration), or the match itself (`emit_step`), plus untrusted bookkeeping.


/// The mode-0 main parser from `pos0` (the floor phase's end).


/// Sequential phases (no if/else between two loop-heavy parsers): the DNA phase covers the whole input in genome
/// mode and returns `(ntok, n)`, else `(0, 0)`; the main parser continues from its end.







// ===== engine b: mix5.b.rs =====

pub const u118_Y_B_LEX_BITS: [u8; 512] = [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0];

pub const u118_Y_B_DEPTH: [usize; 8] = [8, 2, 4, 4, 4, 4, 4, 4];
pub const u118_Y_B_DEPTH2: [usize; 8] = [2, 1, 1, 1, 1, 1, 1, 1];
pub const u118_Y_B_GOOD: usize = 3;
pub const u118_Y_B_LAZY: [usize; 8] = [544, 544, 1056, 544, 544, 544, 544, 544];
pub const u118_Y_B_NICE: usize = 258;
pub const u118_Y_B_IH: usize = 258;
pub const u118_Y_B_IT: usize = 64;
pub const u118_Y_B_ACC: [u64; 8] = [5, 5, 5, 5, 5, 5, 5, 5];
pub const u118_Y_B_STEPMAX: [usize; 8] = [32, 32, 32, 32, 32, 32, 32, 32];
pub const u118_Y_B_LITQ: [usize; 8] = [28, 28, 28, 28, 28, 28, 28, 28];
pub const u118_Y_B_LADJ: [usize; 8] = [2, 2, 2, 2, 2, 2, 2, 2];
pub const u118_Y_B_HLOW: [usize; 8] = [900, 900, 900, 900, 900, 900, 900, 900];
pub const u118_Y_B_HSL: [u32; 8] = [0, 0, 0, 0, 0, 0, 0, 0];
pub const u118_Y_B_ELO: [usize; 8] = [400, 400, 400, 400, 400, 400, 400, 400];
pub const u118_Y_B_H3HI: [usize; 8] = [100, 100, 100, 100, 100, 100, 100, 100];
pub const u118_Y_B_H3CTL: [usize; 8] = [100, 100, 100, 100, 100, 100, 100, 100];
pub const u118_Y_B_H3E: [usize; 8] = [1700, 1700, 1700, 1700, 1700, 1700, 1700, 1700];
pub const u118_Y_B_ACCL: [u64; 8] = [63, 63, 63, 63, 63, 63, 63, 63];
pub const u118_Y_B_H3: [usize; 8] = [0; 8];
pub const u118_Y_B_MAX3: usize = 4096;
pub const u118_Y_B_H3INS: usize = 1;
pub const u118_Y_B_C0Q: [usize; 8] = [44, 44, 44, 44, 44, 44, 44, 44];
pub const u118_Y_B_C0L: [usize; 8] = [44, 44, 44, 44, 44, 44, 44, 44];
pub const u118_Y_B_DEPTHL: [usize; 8] = [12, 12, 12, 12, 12, 12, 12, 12];
pub const u118_Y_B_M3: [usize; 8] = [0, 0, 0, 0, 0, 0, 0, 0];
pub const u118_Y_B_DEPTH3M: [usize; 8] = [12, 12, 12, 12, 12, 12, 12, 12];
pub const u118_Y_B_M3E: [usize; 8] = [1900, 1900, 1900, 1900, 1900, 1900, 1900, 1900];
pub const u118_Y_B_M3Z: [usize; 8] = [15, 15, 15, 15, 15, 15, 15, 15];
pub const u118_Y_B_LZB: usize = 0;
pub const u118_Y_B_BONUS: usize = 0;
pub const u118_Y_B_EXT: usize = 1;
pub const u118_Y_B_DIGN: [usize; 8] = [200, 200, 200, 200, 200, 200, 200, 200];
pub const u118_Y_B_DN: [usize; 8] = [4, 2, 4, 4, 4, 4, 4, 4];
pub const u118_Y_B_P2N: [usize; 8] = [2, 2, 2, 2, 2, 2, 2, 2];
pub const u118_Y_B_LQN: [usize; 8] = [20, 20, 20, 20, 20, 20, 20, 20];
pub const u118_Y_B_NBIG: [usize; 8] = [65536, 65536, 65536, 65536, 65536, 65536, 65536, 65536];
pub const u118_Y_B_GOODL: usize = 258;
pub const u118_Y_B_P2G: usize = 2;
pub const u118_Y_B_NSMALL: [usize; 8] = [65536, 65536, 65536, 65536, 65536, 65536, 65536, 65536];
pub const u118_Y_B_BIAS: usize = 4096;


/// One dial row, loaded once per u118_parse call.
pub struct U118_Y_B_Params {
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



/// Little-endian 8-byte load at `p` (two u32 halves, highest byte read first); 0 when out of range.



/// Index (0..7) of the first differing byte of two little-endian words, given their xor (!= 0).



/// Common prefix of positions `a < b`, up to `cap` (search only; never trusted).



/// Hash of the first (64 - hs) / 8 bytes at `p` into 16 bits.



/// Hash of the low 3 bytes of a word into 14 bits.



// ------------------------------------------------------------------ cost model (search only)

/// DEFLATE distance extra bits of `d`.



/// DEFLATE length extra bits of `l`.



/// Estimated saving (quarter bits, offset by u118_Y_B_BIAS) of coding `l` bytes as a match at `d`.
/// `cq` packs the literal cost (low 8 bits) and the match base cost (bits 8..).



/// Fixed-point log2 with 8 fractional bits (linear between powers of two).



/// Histogram of a strided sample of the input (about 4096 bytes).



/// Order-0 entropy of the histogram in 1/256 bits per symbol.



/// Per mille of the sampled bytes in `lo .. hi`.



/// 1 when the sampled entropy `e` marks a genome-like input (few cheap literals).



/// Literal cost (quarter bits): from the sampled entropy in low mode, else u118_Y_B_LITQ.



/// 1 when the input should use 3-byte hash chains (u118_Y_B_M3 = 2: always; 1: by rule).



/// 1 when the 3-byte table should be used: binary-ish or non-ASCII input of moderate entropy.



/// 1 for large numeric text: at least u118_Y_B_DIGN per mille digits, few bytes >= 128 or < 9, not genome-like.



// ------------------------------------------------------------------ match finding (search only)

/// Walk the chain from `start` (pos+1 encoded, 0 = none) for the candidate with the best score
/// among those longer than `bl0` and scoring more than `bs0`. Returns `len | dist << 9 | score << 25`
/// (0 if none). Candidates stay inside the 32K window; the u118_walk stops at `u118_Y_B_NICE` or `cap`.



/// Lazy-path copy of `u118_walk` (a separate function keeps both inlined at their single call sites).
/// Walk the chain from `start` (pos+1 encoded, 0 = none) for the candidate with the best score
/// among those longer than `bl0` and scoring more than `bs0`. Returns `len | dist << 9 | score << 25`
/// (0 if none). Candidates stay inside the 32K window; the u118_walk stops at `u118_Y_B_NICE` or `cap`.



/// The 1-deep 3-byte candidate at `pos` from entry `s3` (pos+1 encoded): `3 | dist << 9 | score << 25`
/// or 0.







pub const u118_Y_B_SUFFIX_DEPTH: usize = 6;

/// Probe a bounded suffix chain and shift its candidates to this match position.



/// With `probes > 0`: u118_insert `pos` into the chains, then u118_walk them (see `u118_walk`); with nothing found
/// and `h3on == 1`, try the 3-byte table. 0 when `probes == 0`.



/// With `on == 1`: enter `pos` into the 3-byte table and return the entry it replaced; else 0.



/// Insert positions `from .. to` into the chains.


/// `insert_range` that also updates the 3-byte table.


/// Insert the inside `from .. to` of an emitted match: its first u118_Y_B_IH and last u118_Y_B_IT positions.


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






pub const u118_Y_B_BACK_LIMIT: usize = 2;
pub const u118_Y_B_BACK_MATCH: usize = 1;

/// Fold preceding tokens into a match, then use the unchanged verified emitter.



// ------------------------------------------------------------------ the u118_parse loop

/// The lazy check at `q` (= match position + 1) with `go == 1`: enter `q` into the chains and test the most
/// recent chain candidate against the current match (`l1` bytes, score `sv1`). Returns `len | dist << 9 |
/// score << 25` when that candidate is at least as long and scores higher, else 0. `go == 0`: does nothing.



/// 1 when the lazy candidate `(l2, d2)` found at `pos + 1` also covers `pos` (so it can start there).




// ============================ jfloor fast-path module v5 (untrusted except the fl_ trusted copies) ==============
// Graft: the base parser's `u118_parse` becomes `u118_y_b_main_parse(input, out, lh, pos0, ntok0)` and this module's `u118_parse` runs
//   y_b_fl_part(input, out, mode, fh, cf)  -> (ntok, pos): the whole input for modes 1-5, (0, 0) for mode 0,
//   u118_y_b_main_parse(input, out, &fh, pos, ntok) -> the base parser from `pos` (a no-op when pos == n).
// Modes (fl_mode, loop-free, from a strided 4K-byte sample + 16 probe chunks of 256 bytes):
//   4 RLE  : one byte value >= 75% of the u118_y_b_sample (sparse): distance-1 runs, no tables;
//   5 u118_Y_B_LAZY : small files (< 64 KB), database-like binaries (zero bytes but mostly printable), high-entropy data
//            (images, f32 weights, archives): the module's own price-lazy parser with a per-class config `cf`;
//   2 DNA  : 4-symbol alphabet (FASTA): literal runs over cheap bytes, cost-checked matches at expensive bytes;
//   1 LIT  : 2-periodic 16-bit weights (bf16/f16) and skewed-uniform int8 weights (q8, no repeats at all);
//   0      : the base parser.
// The module has its own copies of the trusted kit functions (fl_match_len, fl_verified, fl_emit_lits,
// fl_emit_step) so the base keeps its own emit_step/emit_lits with one caller each (sharing them made LLVM
// outline the base's emit_step: +1% instructions on every text file).

pub const u118_Y_B_FL_PMIN: [usize; 8] = [65536, 65536, 65536, 65536, 65536, 65536, 65536, 65536];
pub const u118_Y_B_FL_PNC: [usize; 8] = [16, 16, 16, 16, 16, 16, 16, 16];
pub const u118_Y_B_FL_PCH: usize = 256;
pub const u118_Y_B_FL_RLE_TOP: [usize; 8] = [192, 192, 192, 192, 192, 192, 192, 192];
pub const u118_Y_B_FL_DNA_THR: u32 = 64;
pub const u118_Y_B_FL_DNA_DEPTH: usize = 64;
pub const u118_Y_B_FL_DNA_M0: usize = 12;
pub const u118_Y_B_FL_CMAX: u32 = 192;
pub const u118_Y_B_FL_HIGH: [usize; 8] = [104, 104, 104, 104, 104, 104, 104, 104];
pub const u118_Y_B_FL_DBZ: [usize; 8] = [8, 8, 8, 8, 8, 8, 8, 8];
pub const u118_Y_B_FL_DBNP: [usize; 8] = [110, 110, 110, 110, 110, 110, 110, 110];
pub const u118_Y_B_FL_USE_T: [usize; 8] = [1, 1, 1, 1, 1, 1, 1, 1];
pub const u118_Y_B_FL_USE_D: [usize; 8] = [0, 0, 0, 0, 0, 0, 0, 0];
pub const u118_Y_B_FL_USE_H: [usize; 8] = [0, 0, 0, 0, 0, 0, 0, 0];
pub const u118_Y_B_FL_USE_LIT: [usize; 8] = [1, 1, 1, 1, 1, 1, 1, 1];
// class configs (T: small files, D: database-like, H: high entropy)
pub const u118_Y_B_FT_DEPTH: [usize; 8] = [16, 16, 16, 16, 16, 16, 16, 16];
pub const u118_Y_B_FT_DEPTH2: [usize; 8] = [2, 2, 2, 2, 2, 2, 2, 2];
pub const u118_Y_B_FT_LAZY: [usize; 8] = [259, 259, 259, 259, 259, 259, 259, 259];
pub const u118_Y_B_FT_NICE: [usize; 8] = [258, 258, 258, 258, 258, 258, 258, 258];
pub const u118_Y_B_FT_IH: [usize; 8] = [64, 64, 64, 64, 64, 64, 64, 64];
pub const u118_Y_B_FT_IT: [usize; 8] = [16, 16, 16, 16, 16, 16, 16, 16];
pub const u118_Y_B_FT_ACC: [usize; 8] = [63, 63, 63, 63, 63, 63, 63, 63];
pub const u118_Y_B_FD_DEPTH: [usize; 8] = [12, 12, 12, 12, 12, 12, 12, 12];
pub const u118_Y_B_FD_DEPTH2: [usize; 8] = [2, 2, 2, 2, 2, 2, 2, 2];
pub const u118_Y_B_FD_LAZY: [usize; 8] = [259, 259, 259, 259, 259, 259, 259, 259];
pub const u118_Y_B_FD_NICE: [usize; 8] = [258, 258, 258, 258, 258, 258, 258, 258];
pub const u118_Y_B_FD_IH: [usize; 8] = [64, 64, 64, 64, 64, 64, 64, 64];
pub const u118_Y_B_FD_IT: [usize; 8] = [16, 16, 16, 16, 16, 16, 16, 16];
pub const u118_Y_B_FD_ACC: [usize; 8] = [63, 63, 63, 63, 63, 63, 63, 63];
pub const u118_Y_B_FH_DEPTH: [usize; 8] = [6, 6, 6, 6, 6, 6, 6, 6];
pub const u118_Y_B_FH_DEPTH2: [usize; 8] = [2, 2, 2, 2, 2, 2, 2, 2];
pub const u118_Y_B_FH_LAZY: [usize; 8] = [32, 32, 32, 32, 32, 32, 32, 32];
pub const u118_Y_B_FH_NICE: [usize; 8] = [64, 64, 64, 64, 64, 64, 64, 64];
pub const u118_Y_B_FH_IH: [usize; 8] = [64, 64, 64, 64, 64, 64, 64, 64];
pub const u118_Y_B_FH_IT: [usize; 8] = [16, 16, 16, 16, 16, 16, 16, 16];
pub const u118_Y_B_FH_ACC: [usize; 8] = [7, 7, 7, 7, 7, 7, 7, 7];
pub const u118_Y_B_FL_GOOD: usize = 8;
pub const u118_Y_B_FL_LITQ: [usize; 8] = [32, 32, 32, 32, 32, 32, 32, 32];
pub const u118_Y_B_FL_LADJ: [usize; 8] = [4, 4, 4, 4, 4, 4, 4, 4];
pub const u118_Y_B_FL_HLOW: [usize; 8] = [900, 900, 900, 900, 900, 900, 900, 900];
pub const u118_Y_B_FL_C0Q: usize = 44;

// ---------------------------------------------------------------- trusted core (floor copy)

/// Byte-wise u118_common prefix length (trusted).
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
pub const u118_Y_B_FL_LOGF: [u32; 16] = [0, 1, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 15];

/// log2(f) in 1/16 bits (0 for f = 0).


/// Strided byte histogram of about 4096 samples.


/// Literal cost per byte value (1/16 bits) from the histogram: log2(total / f), unseen bytes u118_Y_B_FL_CMAX.


/// Order-0 entropy in 1/16 bits per byte of the 256 bins starting at `base` of `h`.


/// Sample statistics packed into one word: bits 0-9 entropy (1/16 bits), 10-18 top byte u118_y_b_share (1/256),
/// 19-27 zero-byte share, 28-36 non-printable share, 37-45 share of the byte values with share >= 1/8,
/// 46-49 number of such byte values.


/// Chunk `s .. s + u118_Y_B_FL_PCH`: 4-phase byte histograms (phase = absolute position mod 4) into `ph`, and the number
/// of positions whose most recent u118_same-3-byte-hash position in the chunk repeats 4 bytes.


/// Weights detector: 1 iff the probe chunks look like 16-bit floats (bytes alternate between a high-entropy and a
/// low-entropy phase with period 2) or like int8 weights (all phases 6.5-7.6 bits, no 4-byte repeat at all).


/// The mode (0 base, 1 LIT, 2 DNA, 4 RLE, 5 u118_Y_B_LAZY) and the u118_Y_B_LAZY class (0 T, 1 D, 2 H), packed `mode + 8 * class`.
/// Integer flags and nested value-ifs only (no `&&` guarding code, so the extracted model stays small).


/// The u118_Y_B_LAZY configuration of a class: [depth, depth2, lazy, nice, ih, it, acc].


// ---------------------------------------------------------------- LIT and RLE

/// Trusted-kit emission of the whole input as literals.


/// RLE u118_parse: a distance-1 u118_run match wherever the previous byte repeats >= 3 times, else one literal.


// ---------------------------------------------------------------- DNA

/// Number of consecutive cheap bytes (cost < u118_Y_B_FL_DNA_THR) from `pos`.


/// Literal cost (1/16 bits) of the `l` bytes at `pos` (l <= 258).


/// DEFLATE distance extra bits.


/// DEFLATE length extra bits.


/// 1 iff the match (l, d) at `pos` is estimated cheaper than its literals: u118_Y_B_FL_DNA_M0 bits + extra bits.


/// Longest match (ties: the u118_closest) along the chain from `start` (pos+1 encoded). Returns `len | dist << 9`.


/// DNA: with `depth > 0`, u118_insert `p` into the 4-byte-hash chains and u118_walk them (depth 0: nothing).


/// Insert positions `from .. to` into the chains (hash of the first 4 bytes if hsh = 32, 8 bytes if hsh = 0).




/// DNA u118_parse: literal runs over cheap bytes; at an expensive byte, search and take the match if it is estimated
/// cheaper than its literals. Only searched positions and match interiors enter the chains.


// ---------------------------------------------------------------- u118_Y_B_LAZY: price-lazy with a runtime config

/// Estimated saving (quarter bits, offset by 4096) of coding `l` bytes as a match at `d`.


/// Fixed-point log2 with 8 fractional bits (linear between powers of two); x >= 1.


/// Entropy of the histogram in 1/256 bits per symbol.


/// Literal cost (quarter bits) for low-entropy inputs.


/// Walk the chain from `start` (pos+1 encoded, 0 = none) for the match with the best estimated saving
/// that is longer than `bl0` and saves more than `bs0`; stop at length `nice`. Returns `len | dist << 9`, or 0.


/// With `depth > 0`: u118_insert `pos` into the chains when `ins == 1`, then u118_walk them. Returns
/// `len | dist << 9` of a match longer than `bl0` saving more than `bs0`, or 0.


/// Insert the inside `from .. to` of an emitted match: its first `ih` and last `it` positions.


/// Literal-u118_run length after `miss` consecutive misses: 1 + (miss >> acc), at most 32.


/// Literal cost (quarter bits) used by the lazy parser: from the entropy for low-entropy inputs, else u118_Y_B_FL_LITQ.


/// Hash shift: 8-byte hash (0) for low-entropy inputs, 4-byte hash (32) otherwise.


/// Price-lazy b_parse (the jgreedy jg1c algorithm) with the class configuration `cf`.


// ---------------------------------------------------------------- the floor phase

/// Runs the whole input through the mode's parser and returns `(ntok, n)`; mode 0 does nothing and returns
/// `(0, 0)` (the base parser then runs from position 0).

// ============================ end of the jfloor module =============================================================


/// Build predecessor links; hs % 64 is the hash shift.
/// Bit 6 skips accelerated literal gaps; bit 7 limits lookahead on high-entropy inputs.
/// Matched interiors are retained when only bit 7 is set.
/// A 64K ring holds the 32K history plus at most 4096 bytes of lookahead.
/// Each node stores the original 4-byte predecessor and the optional 3-byte predecessor.



/// Price-lazy u118_parse using immutable predecessor links prepared ahead in batches.
/// Each chosen match still passes through the original trusted emission path.
/// Clamp the literal-step dial so every miss emits at least one byte.









/// jfloor dispatcher. Sequential phases (no if/else between loop-heavy paths, SHARED_FINDINGS F17): the floor
/// phase handles the whole input for modes 1-5 and returns (ntok, n); for mode 0 it returns (0, 0) and the base
/// parser runs from position 0.








 

 

 

 

 

 

 

 

 

 

 

 

 

 

 

 

 

 

 

 

 

 

 

 

 

 

 

 

 

// Round 70 one-table planner. Search suggestions are reverified by u118_o_a_emit_step.











































































// Cache one token block with the cheap scanner, then use the proven symbol filter/replay.






pub const u118_FX0_HB: u32 = 15;
pub const u118_FX0_HN: usize = 32768;
pub const u118_FX0_WN: usize = 32768;
/// Inputs of at most u118_FX0_SMALL bytes use u118_FX0_HS chain heads and a u118_FX0_WS window table.
pub const u118_FX0_SMALL: usize = 65536;
pub const u118_FX0_HS: usize = 4096;
pub const u118_FX0_WS: usize = 16384;
pub const u118_FX0_NICE: usize = 32;
pub const u118_FX0_INS_MAX: usize = 2;
pub const u118_FX0_TAIL: usize = 1;
/// Inside long matches, every u118_FX0_STRIDE-th position between the head and the tail is chained
/// too (u118_FX0_STRIDE = 0: none).
pub const u118_FX0_STRIDE: usize = 0;
pub const u118_FX0_BACKTOK: usize = 16;
pub const u118_FX0_LDEPTH: usize = 1;
pub const u118_FX0_SAMPLE: usize = 2048;
pub const u118_FX0_VERIFY: usize = 0;
/// Lazy step: a candidate at p+1 needs length >= l + 1 - u118_FX0_LSLACK (u118_FX0_LSLACK = 1: at least as long
/// as the current match l) and must win on estimated saving (literal worth u118_FX0_HLIT/16 bits,
/// match base cost u118_FX0_GBASE/16 bits plus extra bits).
pub const u118_FX0_LSLACK: usize = 1;
pub const u118_FX0_HLIT: u32 = 80;
pub const u118_FX0_GBASE: i32 = 168;
/// Per class: main chain depth, lazy threshold, skip shift, skip cap (T text, P prose,
/// H high-entropy binary, Z high-entropy binary rich in zero bytes, B other binary,
/// DNA-like input is sent as literals).
pub const u118_FX0_T_DEPTH: usize = 2;
pub const u118_FX0_T_LAZY: usize = 0;
pub const u118_FX0_T_SKIP: usize = 3;
pub const u118_FX0_P_DEPTH: usize = 3;
pub const u118_FX0_P_LAZY: usize = 0;
pub const u118_FX0_P_SKIP: usize = 5;
pub const u118_FX0_H_DEPTH: usize = 3;
pub const u118_FX0_H_LAZY: usize = 0;
pub const u118_FX0_H_SKIP: usize = 3;
pub const u118_FX0_Z_DEPTH: usize = 3;
pub const u118_FX0_Z_SKIP: usize = 6;
pub const u118_FX0_Z_CAP: usize = 8;
pub const u118_FX0_B_DEPTH: usize = 4;
pub const u118_FX0_B_LAZY: usize = 3;
pub const u118_FX0_B_SKIP: usize = 4;
/// Structured text (class 6: text with at least 1/u118_FX0_SDIG of the sample in digits): main depth
/// u118_FX0_S_DEPTH, lazy u118_fx0_walk depth u118_FX0_S_LDEPTH, lazy threshold u118_FX0_S_LAZY.
pub const u118_FX0_SDIG: u32 = 6;
pub const u118_FX0_S_DEPTH: usize = 1;
pub const u118_FX0_S_LDEPTH: usize = 1;
pub const u118_FX0_S_LAZY: usize = 258;
/// Largest skip step (extra literals per miss) outside the Z class.
pub const u118_FX0_SKCAP: usize = 1000000;

/// Eight bytes at `i`, first byte most significant (0 when out of range).



/// Four bytes at `i`, first byte most significant (0 when out of range).



/// Input class from a strided byte histogram of at most ~u118_FX0_SAMPLE bytes:
/// 0 DNA-like, 1 text, 2 high-entropy binary, 3 other binary, 4 high-entropy with zeros,
/// 5 prose (text of letters and spaces with almost no code symbols), 6 structured text (many
/// digits: tables, logs, dumps).



/// Estimated saving (1/16 bit) of a match of length `l` at distance `d` over literals.



/// Length of the u118_fx0_common prefix of s[a..] and s[b..], at most `cap`.



/// 1 when s[a..a+len] == s[b..b+len]: eight bytes at a time, the last partial word
/// under a mask when a full load fits, else byte by byte.






/// Emit a match (re-checked when u118_FX0_VERIFY = 1), else a literal. Returns (tokens, next position).



/// Walk the chain from `start`: the longest match at `p` longer than `have` (with `gm` = 1,
/// a longer candidate must also have a higher estimated saving); distance 0 = none found.
/// Each candidate first compares the byte at `best`.



/// Put position `i` at the head of its chain (key = first four bytes under `mask`);
/// returns the previous head.



/// Best match at `p` longer than `have` and at least `minl` long; (0, 0) when none.



/// The u118_fx0_parse for one input class (inlined so the text classes get constant settings), with
/// H chain heads and a window table of W entries.



/// Every input except larger text and prose: smaller tables for small inputs.





pub const u118_FX3_HB: u32 = 15;
pub const u118_FX3_HN: usize = 32768;
pub const u118_FX3_WN: usize = 32768;
pub const u118_FX3_SMALL: usize = 65536;
pub const u118_FX3_HS: usize = 4096;
pub const u118_FX3_WS: usize = 16384;
pub const u118_FX3_NICE: usize = 32;
pub const u118_FX3_INS_MAX: usize = 2;
pub const u118_FX3_TAIL: usize = 1;
pub const u118_FX3_STRIDE: usize = 0;
pub const u118_FX3_BACKTOK: usize = 16;
pub const u118_FX3_LDEPTH: usize = 1;
pub const u118_FX3_SAMPLE: usize = 2048;
pub const u118_FX3_VERIFY: usize = 0;
pub const u118_FX3_LSLACK: usize = 1;
pub const u118_FX3_HLIT: u32 = 80;
pub const u118_FX3_GBASE: i32 = 168;
pub const u118_FX3_T_DEPTH: usize = 2;
pub const u118_FX3_T_LAZY: usize = 0;
pub const u118_FX3_T_SKIP: usize = 3;
pub const u118_FX3_P_DEPTH: usize = 3;
pub const u118_FX3_P_LAZY: usize = 0;
pub const u118_FX3_P_SKIP: usize = 5;
pub const u118_FX3_H_DEPTH: usize = 3;
pub const u118_FX3_H_LAZY: usize = 0;
pub const u118_FX3_H_SKIP: usize = 3;
pub const u118_FX3_Z_DEPTH: usize = 3;
pub const u118_FX3_Z_SKIP: usize = 6;
pub const u118_FX3_Z_CAP: usize = 8;
pub const u118_FX3_B_DEPTH: usize = 4;
pub const u118_FX3_B_LAZY: usize = 0;
pub const u118_FX3_B_SKIP: usize = 4;
pub const u118_FX3_SDIG: u32 = 6;
pub const u118_FX3_S_DEPTH: usize = 1;
pub const u118_FX3_S_LDEPTH: usize = 1;
pub const u118_FX3_S_LAZY: usize = 0;
pub const u118_FX3_SKCAP: usize = 1000000;



















































































































































































// fastX: a fast, content-adaptive LZ77 parser for the fixed DEFLATE encoder.
//
// * Content class from a small strided byte histogram: DNA-like inputs, prose (letters and
//   spaces, almost no code symbols), other text, high-entropy binaries (with a zero-rich
//   variant) and structured binaries each get their own settings.
// * Search: hash chains keyed by the first 4 bytes (3 for structured binaries), a main x_walk and
//   a lazy x_walk, both with a one-byte quick reject; the lazy step compares candidates by an
//   estimated bit saving. Text looks one byte x_ahead only after short matches, prose walks
//   deeper without looking x_ahead, structured text walks one step and looks x_ahead deeply.
// * Every new match first extends backwards over the tokens just written: literals that
//   match at its distance, and whole earlier matches whose bytes also match there, are
//   folded into it (fewer, longer matches). Inside long matches the first x_INS_MAX, every
//   x_STRIDE-th and the last x_TAIL positions are recorded.
// * Skip acceleration through stretches without matches (capped for zero-rich data).
// * Tables are sized by the input: small inputs clear and touch less memory.
// * Emission optionally re-checks each match (x_VERIFY = 1); a failed x_check writes a literal.
// * Tiny inputs (at most x_TF_N bytes; binaries, optionally plain text) take a separate path: a
//   planner (`x_tf_plan`, search only) that spends few distinct length and distance codes (the
//   encoder's cost per tiny block is mostly per live symbol) writes a plan, and `x_emit` writes each
//   planned match only after `x_check` has re-compared its bytes (anything else becomes literals),
//   so only the emission carries the decode invariant.
// * A class whose search is a single chain step (here text, prose, structured text and the
//   zero-rich binaries) is parsed by `x_run1` instead of `x_run`: the x_same tokens, but the head slot,
//   the candidate and the candidate's first eight bytes of the next position are read one step
//   early, so the loads overlap the branches of the current position, and the literals are
//   written in one go when the next match is known (`x_r1_kind` decides from constants alone).
// * Pair-structured binaries (16-bit floats: one byte of each pair nearly constant) take the
//   stride path `x_run_st`: only every second position is searched, with 3-byte keys.
//
// Tokens: t < 256 literal, else 2^24 + (dist-1)*256 + (len-3).

pub const x_HB: u32 = 15;
pub const x_HN: usize = 32768;
pub const x_WN: usize = 32768;
/// Inputs of at most x_SMALL bytes use x_HS chain heads and a x_WS window table.
pub const x_SMALL: usize = 65536;
pub const x_HS: usize = 4096;
pub const x_WS: usize = 16384;
pub const x_NICE: usize = 32;
pub const x_INS_MAX: usize = 2;
pub const x_TAIL: usize = 1;
/// Inside long matches, every x_STRIDE-th position between the head and the tail is chained
/// too (x_STRIDE = 0: none).
pub const x_STRIDE: usize = 0;
pub const x_BACKTOK: usize = 16;
pub const x_LDEPTH: usize = 1;
pub const x_SAMPLE: usize = 2048;
pub const x_VERIFY: usize = 0;
/// Lazy step: a candidate at p+1 needs length >= l + 1 - x_LSLACK (x_LSLACK = 1: at least as long
/// as the current match l) and must win on estimated saving (literal worth x_HLIT/16 bits,
/// match base cost x_GBASE/16 bits plus extra bits).
pub const x_LSLACK: usize = 1;
pub const x_HLIT: u32 = 80;
pub const x_GBASE: i32 = 168;
/// Per class: main chain depth, lazy threshold, skip shift, skip cap (T text, P prose,
/// H high-entropy binary, Z high-entropy binary rich in zero bytes, B other binary,
/// DNA-like input is sent as literals).
pub const x_T_DEPTH: usize = 1;
pub const x_T_LAZY: usize = 0;
pub const x_T_SKIP: usize = 4;
pub const x_P_DEPTH: usize = 4;
pub const x_P_LAZY: usize = 0;
pub const x_P_SKIP: usize = 5;
pub const x_H_DEPTH: usize = 3;
pub const x_H_LAZY: usize = 0;
pub const x_H_SKIP: usize = 3;
pub const x_Z_DEPTH: usize = 1;
pub const x_Z_SKIP: usize = 4;
pub const x_Z_CAP: usize = 8;
pub const x_B_DEPTH: usize = 4;
pub const x_B_LAZY: usize = 3;
pub const x_B_SKIP: usize = 4;
/// Structured text (class 6: text with at least 1/x_SDIG of the sample in digits): main depth
/// x_S_DEPTH, lazy x_walk depth x_S_LDEPTH, lazy threshold x_S_LAZY.
pub const x_SDIG: u32 = 6;
pub const x_S_DEPTH: usize = 1;
pub const x_S_LDEPTH: usize = 1;
pub const x_S_LAZY: usize = 258;
/// Largest skip step (extra literals per miss) outside the Z class.
pub const x_SKCAP: usize = 1000000;
/// 1: a class whose search is one chain step (main x_walk and lazy x_walk) is parsed by the read-x_ahead
/// loop `x_run1` (the x_same tokens as `x_run`); 0: `x_run` for every class.
pub const x_R1_ON: usize = 1;
/// Stride path (x_ST_ON 1): a high-entropy input (class 2 or 4) of more than x_ST_MIN bytes whose bytes
/// at one parity take at most x_ST_FEW distinct values while the other parity takes at least x_ST_MANY
/// (in at most x_ST_SAMPLE sampled byte pairs) is parsed by `x_run_st`: only the positions of the
/// low-entropy parity are searched, with 3-byte keys in a direct-mapped table of x_ST_HN slots
/// (2^x_ST_HB); a match is at most x_ST_DMAX back.
pub const x_ST_ON: usize = 1;
pub const x_ST_MIN: usize = 65536;
pub const x_ST_SAMPLE: usize = 4096;
pub const x_ST_FEW: usize = 32;
pub const x_ST_MANY: usize = 160;
pub const x_ST_HB: u32 = 17;
pub const x_ST_HN: usize = 131072;
pub const x_ST_DMAX: usize = 32768;
/// Tiny inputs (at most x_TF_N bytes) that `x_tf_class` calls binary, and with x_TF_TEXT = 1 also text
/// inputs of a `x_tf_class` kind below x_TF_TKIND (0 text, 1 structured text), take the plan +
/// re-verify path (`x_tf_plan`, then `x_emit`); every other input takes the engine above. x_TF_N = 0
/// leaves only the empty input there (no tokens either way): `x_parse` is then the engine alone.
pub const x_TF_N: usize = 65536;
pub const x_TF_TEXT: usize = 1;
pub const x_TF_TKIND: usize = 1;
/// `x_tf_class`: about x_TF_SAMPLE strided bytes (>= 1); structured text has at least 1/x_TF_SDIG
/// (>= 1) digits.
pub const x_TF_SAMPLE: usize = 256;
pub const x_TF_SDIG: u32 = 6;
/// Chain heads (x_TF_HN = 2^x_TF_HB slots, 1 <= x_TF_HB <= 64) and the window table (x_TF_WN >= 1);
/// positions are kept as u16 (x_TF_N <= 65536 keeps them exact). Binaries alone (x_TF_TEXT = 0,
/// x_TF_BDEPTH = 0) x_find only distance-1 matches, so the chains never change their plan (a chain
/// candidate can only repeat distance 1, the one kept code): minimal tables skip clearing 72 KB.
/// The text planner (x_TF_TEXT = 1) walks the chains: x_TF_HB 12, x_TF_HN 4096, x_TF_WN 32768 there.
pub const x_TF_HB: u32 = 12;
pub const x_TF_HN: usize = 4096;
pub const x_TF_WN: usize = 16384;
/// Per kind: chain steps, lazy steps below this match length, skip shift (after m literals in a
/// row, m >> skip positions are not searched; a shift of 32 or more never skips). T text, S
/// structured text, B binaries (3-byte keys; x_TF_BDEPTH 0 = distance 1 only).
pub const x_TF_TDEPTH: usize = 1;
pub const x_TF_TLAZY: usize = 0;
pub const x_TF_TSKIP: usize = 3;
pub const x_TF_SDEPTH: usize = 1;
pub const x_TF_SLAZY: usize = 258;
pub const x_TF_SSKIP: usize = 3;
pub const x_TF_BDEPTH: usize = 0;
pub const x_TF_BLAZY: usize = 0;
pub const x_TF_BSKIP: usize = 4;
/// A x_walk stops at a match of x_TF_NICE bytes; skip steps are at most x_TF_SKCAP.
pub const x_TF_NICE: usize = 64;
pub const x_TF_SKCAP: usize = 1000000;
/// 1: distance 1 is tried before the chain on text too (always on binaries).
pub const x_TF_TRLE: usize = 1;
/// 1: a new match extends backwards over pending literals; 1: the pending match is folded into
/// a new one when its bytes also match at the new distance.
pub const x_TF_BACK: usize = 1;
pub const x_TF_FOLD: usize = 1;
/// The previous match distance is tried before the chain (1), after it (2) or not at all (0).
pub const x_TF_REP: usize = 0;
/// 1: no search where a x_run of four equal bytes starts (the next position takes distance 1).
pub const x_TF_RUNSKIP: usize = 1;
/// Positions chained at the head and at the tail of a match.
pub const x_TF_INS: usize = 2;
pub const x_TF_TAIL: usize = 1;
/// Keep thresholds (uses per code): text x_TF_KL / x_TF_KD, binaries x_TF_BKL / x_TF_BKD (0 or 1: keep
/// every code used).
pub const x_TF_KL: u32 = 5;
pub const x_TF_KD: u32 = 5;
pub const x_TF_BKL: u32 = 3;
pub const x_TF_BKD: u32 = 3;
/// Re-x_find: chain steps, single literals tried before giving up; a dropped-distance match that
/// cannot be re-found becomes literals when at most x_TF_DLIT bytes long, else keeps its distance
/// (its code re-admitted).
pub const x_TF_RDEPTH: usize = 8;
pub const x_TF_SHIFT: usize = 1;
pub const x_TF_DLIT: usize = 8;

/// Eight bytes at `i`, first byte most significant (0 when out of range).


/// Four bytes at `i`, first byte most significant (0 when out of range).


/// Input class from a strided byte histogram of at most ~x_SAMPLE bytes:
/// 0 DNA-like, 1 text, 2 high-entropy binary, 3 other binary, 4 high-entropy with zeros,
/// 5 prose (text of letters and spaces with almost no code symbols), 6 structured text (many
/// digits: tables, logs, dumps).


/// Estimated saving (1/16 bit) of a match of length `l` at distance `d` over literals.


/// Length of the x_common prefix of s[a..] and s[b..], at most `cap`.


/// 1 when s[a..a+len] == s[b..b+len]: eight bytes at a time, the last partial word
/// under a mask when a full load fits, else byte by byte.




/// Emit a match (re-checked when x_VERIFY = 1), else a literal. Returns (tokens, next position).


/// Walk the chain from `start`: the longest match at `p` longer than `have` (with `gm` = 1,
/// a longer candidate must also have a higher estimated saving); distance 0 = none found.
/// Each candidate first compares the byte at `best`.


/// Put position `i` at the head of its chain (key = first four bytes under `mask`);
/// returns the previous head.


/// Best match at `p` longer than `have` and at least `minl` long; (0, 0) when none.


/// The x_parse for one input class (inlined so the text classes get constant settings), with
/// H chain heads and a window table of W entries.


// ─────────────── the stride path: pair-structured binaries (16-bit floats and the like) ───────────────

/// Parity of the low-entropy bytes of pair-structured data (0 even, 1 odd), or 2 when the input is
/// not such data: in at most x_ST_SAMPLE sampled byte pairs one parity takes at most x_ST_FEW distinct
/// values and the other at least x_ST_MANY.


/// The stride path's parity for an input of class `cls` that takes it (0 or 1), else 2.


/// Table slot of the three bytes at `p` (low-entropy, other, low-entropy).


/// Put position `p` in slot `a` of the stride table; returns the position it replaces.


/// The match at `p` from the table entry `c`: (length, distance) when `c` is at most x_ST_DMAX before
/// `p` and the three key bytes agree (compared one by one, then extended byte by byte), else (0, 0).


/// Stride-2 greedy x_parse: only positions of parity `ph` are searched; the table keeps the most
/// recent position per key slot; a failed search writes the pair (p, p + 1) as literals, and a
/// match that ends on the other parity is followed by one literal.


// ─────────────── the read-x_ahead loop for classes searched with one chain step ───────────────

/// Slot of position `i` in a head table of H entries (the slot `x_insert` uses for 4-byte keys).


/// Record position `i` in slot `a`.


/// What the search at position `i` will need, read before it gets there: its slot, the head entry
/// there (the candidate) and the candidate's first eight bytes.


/// `x_ahead` for position `i` when it is below `lim` (it will be searched), else the values given.
/// (The test also keeps these loads apart from the eight-byte load of the search at `i - 1`,
/// which shares bytes with them: each stays a single load.)


/// `x_common` continued after `k0` bytes already known to agree.


/// How many bytes agree at `c` and `p`, given the xor `x` of their first eight bytes taken as
/// words: the leading zero bytes of `x`, or what `x_common_from` finds past eight equal bytes.


/// The match at `p` from the candidate `c` whose first eight bytes are the word `cw`: (length,
/// distance) when at least four bytes agree at a distance in 1..=32768, else (0, 0). One xor of
/// the two words decides.


/// The length a match at the lazy position has to beat after a match of length `l`:
/// max(3, l - x_LSLACK).


/// `x_probe` for the lazy step at `q`, one after a match of length `l`: only a match longer than
/// `x_lazy_lo(l)` counts, and the byte at that offset is compared first.


/// Literals skipped without a search after `miss` misses in a row: min(miss >> skip, skcap).


/// `p` moved on by `step` positions, at most to `lim` (needs p <= lim).


/// Write the literals of the positions `from..to` (the ones passed since the last match).


/// The backward merge of `x_run` for the match (l0, d) at `p0`: earlier tokens whose bytes also match
/// at distance `d` are folded into it. Returns (tokens kept, start, length).


/// Record, as `x_run` does, the first x_INS_MAX and the last x_TAIL positions inside the match that
/// ends at `end`, starting at `ins0` (positions from `lim` on have no full key).


/// `x_run` for a class searched with one chain step (4-byte keys; main x_walk and lazy x_walk): the x_same
/// tokens, without the window table, and with the search state of the next position (`x_ahead`: its
/// slot, its candidate and the candidate's first eight bytes) read one step early, before the
/// branches of the current position are decided. `pre_slot`, `pre_c`, `pre_w` always describe the
/// position searched next: `p` at the top of the loop, `p + 1` once `p` is recorded (`x_ahead_if`
/// leaves them alone when that position is past the last one searched).
/// The literals are not written while scanning: `ls` is the start of the positions passed since
/// the last match, and `x_flush` writes them when the next match is known (or at the end), so the
/// scan itself only loads: the word at `p`, the head entry and the candidate's word.


/// The class itself when `x_parse` gives class `cls` to `x_run1` (x_R1_ON, no stride recording, and one
/// chain step for both walks of the class), else 0. Constant conditions only: any other constant
/// set leaves the class with `x_run`.


/// Every input except larger text and prose: smaller tables for small inputs.


/// Inputs that `x_tf_route` sends to the tiny path: plan, then x_emit with re-verification; all others:
/// the engine (the stride path for pair-structured binaries, `x_run1` for the classes `x_r1_kind`
/// names, `x_run` for the rest).


// ─────────────── tiny inputs: plan + re-verify (`x_parse` sends inputs of at most x_TF_N bytes here) ───────────────
//
// Phase 2, the emission (`x_emit` with `x_check`, `x_mlen`, `x_load8`, `x_first_diff`, `x_get0`), carries the
// whole decode invariant of this path: a planned match is written only if `x_check` finds it in range
// and `x_mlen` confirms every byte; anything else becomes literals. Phase 1, the planner (`x_tf_plan` and
// everything it calls), is search: it only has to be total (no panic, terminates) and may return a
// plan of any length and contents (`x_get0` reads 0 past its end).
// Plan format: a token list; entry k describes the k-th planned token: `len + 512 * dist` for a
// match, and any entry that `x_check` rejects stands for `max(1, len)` literals (`len = v % 512`), so
// `x_run` (dist 0, 1 <= x_run <= 511) is a x_run of `x_run` literals and 0 a single literal. A rejected
// match therefore costs literals over its planned length and the plan stays aligned.

/// The eight bytes at `p` as one big-endian number (byte `p` most significant), or 0 when fewer
/// than eight remain (Horner form; one load plus `bswap` once inlined).


/// How many leading (most significant) bytes the words `x` and `y` share: 8 when equal.


/// How many bytes agree at `a` and `b`, up to `cap` (needs `a + cap <= n` and `b + cap <= n`):
/// eight at a time, the first mismatching word resolved by `x_first_diff`, the last `cap % 8` bytes
/// one at a time. The only function whose result the emission trusts (through `x_check`).


/// True only if `(len, dist)` is a legal match at `p` whose bytes all agree.


/// `v[i]`, or 0 when `i` is out of range: a read that cannot panic.


/// `v[i] = x` when `i` is in range, nothing otherwise: a write that cannot panic.


/// Phase 2: x_walk the plan from 0 (entry `k` for the `k`-th planned token); a planned match is
/// written only if `x_check` accepts it, else its bytes become literals (`owed`), so the plan stays aligned.


// ═══════════════ tiny inputs: the symbol-frugal planner (search only) ═══════════════
//
// The validator's encoder pays per block about 1.3 us for every live literal/length symbol and about
// 1 us for every live distance code (two or more live; a single live distance code costs nothing), on
// top of a few ns per token. A tiny input is one block, so its encode time is mostly this per-symbol
// overhead. The literal alphabet is fixed by the input (every distinct byte is a literal once), so the
// planner works on the length and distance codes:
//  1. `x_tf_class`: binary (a zero byte or many control bytes in ~x_TF_SAMPLE strided bytes), structured
//     text (>= 1/x_TF_SDIG digits) or text.
//  2. `x_tf_stage1`: a lazy hash-chain x_parse into a token list (u16 position chains; distance 1, then the
//     previous distance, then the chain; backward extension over pending literals; the pending match is
//     folded into a new one when its bytes also match at the new distance; the engine's bit-saving
//     estimate for the lazy step) and a histogram of length codes and distance codes. Binaries
//     (x_TF_BDEPTH 0): distance 1 only, so zero runs are one literal plus distance-1 matches and a single
//     distance code is live.
//  3. `x_tf_keep`: a length code is kept when used >= x_TF_KL (binaries x_TF_BKL) times, a distance code
//     >= x_TF_KD (x_TF_BKD) times.
//  4. `x_tf_rewrite`: consecutive matches at one distance are one span, re-split into kept lengths
//     (`x_tf_piece`: one kept length, many maximal ones, or two kept lengths summing to the rest); a match
//     whose distance code was dropped is re-found at a kept distance (its chain, the two most recent
//     distances, distance 1; after up to x_TF_SHIFT single literals), else written as literals when at
//     most x_TF_DLIT bytes. Online re-admission: a span the kept lengths would leave >= 3 bytes uncovered
//     re-admits its own codes; a longer unfindable match keeps its distance and re-admits that code.
// The plan is a token list: `len + 512 * dist` for a match, `x_run` (dist 0, x_run <= 511) for a literal
// x_run. Nothing here is trusted: `x_emit` re-checks every planned match, so these functions only have to
// be total. Each function keeps its decisions in one place at its end (larger steps are chains of
// small helpers); arithmetic that a guard does not bound wraps.

/// Byte `i` of `s` (0 when out of range).


/// Eight bytes at `i`, first byte most significant (0 unless all eight are in range).


/// Four bytes at `i`, first byte most significant (0 unless all four are in range).


/// The smaller of `a` and `b`.


/// The larger of `a` and `b`.


/// `x >> sh`, and 0 for `sh` >= 32 (the counts shifted here stay below 2^32).


/// Chain slot of the key at `p` (four bytes; three with mask 0xFFFF_FF00).


/// Slot (0..=28) of the length code of `l` in `hist`/`keep` (lengths 3..=258; any `l` is allowed).


/// Slot (32..=61) of the distance code of `d` in `hist`/`keep` (distances 1..=32768; any `d`).


/// How many bytes agree at `a` and `b` (a < b), at most `cap` (search only: any arguments are allowed;
/// the shape of the proven `x_mlen`, so the word loads compile to one load each).


/// Append `x` (guarded push).


/// Chain position `p` (u16 positions); returns the previous head of its slot (where the search at `p`
/// starts).


/// Chain the positions `from..to` (none when `from >= to`); returns the larger of the two.


/// Is `c` a possible source for `p` (before it and at most 32768 back)?


/// The length of the match at `p` from `c` (at most `cap`) when it beats `best`, else `best`; the byte
/// where it would beat `best` is compared first.


/// Longest match at `p` longer than `have` on the chain from position `start` (at most `depth` steps,
/// within 32768 bytes): (length, distance); distance 0 when none is longer.


/// The longest match `p` allows: min(n - p, 258), 0 at or past the end.


/// The length a match has to beat: `have`, raised to `minl - 1`.


/// Distance 1 at `p` (when `rle` = 1 and the byte before `p` repeats there): (best, bd) of the longer.


/// The previous distance `rep` (> 1) at `p`, when `on`: (best, bd) of the longer.


/// The chain from `ci` (`depth` steps) when `best` is below `cap` and x_TF_NICE: (best, bd) of the longer.


/// Best match at `p` longer than `have` and at least `minl` long: distance 1, the previous distance
/// `rep`, then the chain from `ci` (each must be longer than the best so far, so on equal length the
/// earlier and cheaper distance stays). (0, 0) when none.


/// Append `x_run` literals as entries of at most 511.


/// Append `x_run` literals, then the match (l, d).


/// 1 for a zero byte.


/// 1 for a control byte (below 9, or 14..=31).


/// 1 for a decimal digit.


/// Input kind from at most ~x_TF_SAMPLE strided bytes: 2 binary (a zero byte, or more than 1/32 control
/// bytes), 1 structured text (at least 1/x_TF_SDIG digits), 0 other text.


/// Stage-1 settings of kind `cls`: (key mask, shortest match, chain steps, lazy limit, skip shift,
/// distance 1 first).


/// Does a x_run of four equal bytes start at `p` (the byte before `p` differs)?


/// The first candidate at `p`: none where a x_run starts (x_TF_RUNSKIP, distance-1-first kinds; the next
/// position takes distance 1), else `x_tf_find`.


/// Is the match of length `l` found at `p` taken (at least `minl` long, inside the input)?


/// Estimated saving (1/16 bit) of a match (l, d) over literals: the engine's `x_gain` (identical for
/// 3 <= l <= 258, 1 <= d <= 32768), with wrapping arithmetic.


/// Does the match (g0, g1) found at `q` (one after the current match's position) beat (l, d)?


/// Lazy steps while the match is shorter than `lazy` and x_TF_NICE: a better match one position later
/// replaces it (one more pending literal). The state m = [p, l, d, x_run, ins] is read and written back
/// (a function that changes tables returns no tuple: the proof's `step*` takes flat results).


/// Extend the match (l, d) at `p` backwards over the pending literals (x_TF_BACK): (p, l, x_run).


/// Fold the pending match (pl, pd) into the match (l, d) at `p` when no literal is between them, the
/// sum is a legal length and its bytes also match at `d` (x_TF_FOLD): (p, l, pd).


/// Write the pending match (pl, pd) when there is one (pd != 0) and count its codes.


/// Where the chained tail of a match ending at `end` starts: end - x_TF_TAIL when that is after `ins`.


/// Chain the positions of a match ending at `end`: x_TF_INS from `ins` on and the last x_TF_TAIL (never at
/// or past `lim`); returns the next position to chain (at least `end`).


/// A match (l, d) taken at `p`: lazy steps, backward extension, the x_fold of the pending match (pl, pd);
/// then the pending match and the literals before the new one are written and the new match's
/// positions chained. Writes o = [end, l, d, ins]: the new match is the pending one now.


/// Positions skipped after `miss` misses in a row (`p` the next position): miss >> skip, at most
/// x_TF_SKCAP and lim - p, none at `lim`.


/// The literals pending at the end: `x_run` plus everything from `p` on.


/// The lazy x_parse proper (lim = n - 8), then the pending match and the literals left at the end.


/// Phase 1a: the lazy x_parse into `tk` (chains left in `head`/`prev` for the rewrite), length codes
/// counted in hist[0..29], distance codes in hist[32..62].


/// Threshold of slot `c`: `kl` for length codes (c < 32), `kd` for distance codes.


/// 1 when a code used `h` times is kept under threshold `k`.


/// Phase 1b: kept codes (keep[0..29] lengths used at least `kl` times, keep[32..62] distances used at
/// least `kd` times).


/// `x` if it is the first kept length (`kx` and none before), else `kmin`.


/// Is the length `x` (>= 3) of a kept code?


/// `x` when `kx`, else `cur`.


/// lle[x] = the largest length <= x whose code is kept (0 when none); returns the smallest kept length
/// (0 when none).


/// Length code `c`, when kept: the first of two kept lengths summing to `x` whose first piece has code
/// `c` (3 <= each <= 258), else 0.


/// Two kept lengths summing to `x` (3 <= each <= 258): the first one, or 0 when there is none.


/// The largest kept length that leaves at least the smallest one (when rem > kmin + 3), else the
/// largest kept length <= rem (lengths above 258 count as 258).


/// `x_tf_piece` before its range x_check.


/// The next piece when `rem` bytes are written in kept lengths (0 when no kept length fits): `rem`
/// when kept, the largest kept length while more than two of them remain, a kept pair, else the
/// largest kept length leaving at least the smallest one.


/// Bytes of `l` that no kept piece would cover (dry x_run of `x_tf_split`).


/// Write `l` bytes at distance d as pieces of kept lengths; `x_run` literals are pending before it;
/// returns the literals pending after it (bytes no piece covers become literals).


/// Re-admit the code of a remainder `r` (>= 3).


/// Re-admit the codes of `l` bytes written as 258-byte pieces and a remainder (when the kept codes
/// would leave bytes uncovered); returns the new smallest kept length.


/// `x_tf_split` with its state in st (st[0] = pending literals, in and out; st[1] = smallest kept length).


/// Before writing `l` bytes in kept lengths: re-admit their own codes when the kept lengths would leave
/// at least 3 bytes uncovered (st[1] = the new smallest kept length).


/// Distance `d` at `p` when it is in reach and its code is kept: (best, bd) of the longer (<= cap).


/// The chain candidate `c` (before `p`, in reach) when its distance code is kept: (best, bd) of the
/// longer.


/// x_TF_RDEPTH steps on the chain of `p` for a longer match at a kept distance: (best, bd).


/// The chain step of `x_tf_refind` (when `chain` = 1).


/// Longest match at `p` (at most `cap` bytes) at a kept distance: the distances `r1`, `r2`, 1, then
/// (when `chain` = 1) the chain of `p` (x_TF_RDEPTH steps): (length, distance), (0, 0) when none.


/// Remember distance `d` as the most recent one (rd[0..4]).


/// Write the span of `l` bytes at kept distance d: one kept length as is, else kept pieces (re-admitting
/// the span's own codes first when the kept lengths would leave bytes uncovered).


/// What `x_tf_redo` does with a re-x_find of length `fl` when `rem` bytes remain (`shift` literal tries
/// left): 0 take it, 1 one literal, 2 the original distance, 3 literals.


/// One step of `x_tf_redo` (see `x_tf_act`).


/// The `l` bytes at `p` whose distance code (of d) was dropped: re-found at kept distances (the chain of
/// `p` first, the recent distances, distance 1), after up to x_TF_SHIFT single literals; else literals when
/// at most x_TF_DLIT bytes remain, else at distance d with its code re-admitted. Returns the next position.


/// What `x_tf_rewrite` does with the stage-1 token (l, d) (`room` bytes left): 0 literals, 1 a span at a
/// kept distance, 2 a re-x_find (the distance code was dropped).


/// Literals for a token that is no match: min(l, room), at least 1.


/// The span of consecutive stage-1 matches at distance `d` from token `k0` on (`l0` bytes so far, at most
/// `room`): (next token, span length).


/// Phase 1c: the plan from the stage-1 tokens under the kept codes. Consecutive matches at one distance
/// are taken as one span and re-split into kept lengths; a match whose distance code was dropped is
/// re-found at a kept distance (its chain, the recent distances, distance 1; after at most x_TF_SHIFT
/// single literals), else its bytes become literals.


/// Keep thresholds (length codes, distance codes) of kind `cls`.


/// The plan for a tiny input of kind `cls` (`x_tf_class`).


/// The kind (`x_tf_class`) of an input that takes the plan + re-verify path: binaries, and text of a kind
/// below x_TF_TKIND when x_TF_TEXT = 1, all of at most x_TF_N bytes; 3 for every other input.


/// Length code (0..28) of a match length (0..511; lengths below 3 map to 0, above 258 to 28).
pub const x_TF_LSYM: [u8; 512] = [
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
pub const x_TF_DSYM: [u8; 512] = [
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
pub const x_TF_LBASE: [u16; 32] = [3, 4, 5, 6, 7, 8, 9, 10, 11, 13, 15, 17, 19, 23, 27, 31, 35, 43, 51, 59, 67, 83, 99, 115, 131, 163, 195, 227, 258, 0, 0, 0];
pub const x_TF_LTOP: [u16; 32] = [3, 4, 5, 6, 7, 8, 9, 10, 12, 14, 16, 18, 22, 26, 30, 34, 42, 50, 58, 66, 82, 98, 114, 130, 162, 194, 226, 257, 258, 0, 0, 0];

// mA: a content-adaptive LZ77 parser for the fixed DEFLATE encoder (mid speed band).
//
// Lineage: fastX fx17 (fast band, Package 2 base) with per-class settings and four search additions.
// * Content class from a small strided byte histogram: DNA-like inputs (0), text (1), peaky
//   high-entropy binaries such as 16-bit weights (2), other binaries (3), zero-rich high-entropy
//   data (4), prose (5), structured text with many digits (6) and flat high-entropy data without a
//   dominant byte value such as images or compressed streams (7). Every class has its own main m_walk
//   depth, lazy m_walk depth, lazy threshold, m_walk stop length, skip shift and insertion pattern.
// * Search: hash chains keyed by the first 4 bytes (3 bytes for classes 3 and 7, 8 bytes for DNA),
//   a main m_walk and a lazy m_walk, both with a one-byte quick reject. The main m_walk (m_MAIN_GM) and the
//   lazy walks rank candidates by an estimated bit saving (a longer candidate must also save more).
// * Lazy step: move to p+1 while it has a better candidate; when p+1 does not win, p+2 is tried
//   once (m_LAZY2) and wins if its saving exceeds the pending one by more than m_L2B/16 bits.
// * Every new match first extends backwards over the tokens just written: literals that match
//   at its distance, and whole earlier matches whose bytes also match there, are folded into it.
//   Optionally (m_PARTIAL) a previous match whose tail the new match also covers is shortened
//   when a closer source covers the shorter length.
// * DNA-like input: 8-byte chain keys and a 9-byte minimum match (m_run_dna).
// * Skip acceleration through stretches without matches (capped for zero-rich data).
// * Tables are sized by the input: small inputs clear and touch less memory.
// * Emission optionally re-checks each match (m_VERIFY = 1); a failed check writes a literal.
//
// Tokens: t < 256 literal, else 2^24 + (dist-1)*256 + (len-3).

pub const m_HB: u32 = 15;
pub const m_HN: usize = 65536;
pub const m_WN: usize = 32768;
/// Inputs of at most m_SMALL bytes use m_HS chain heads and a m_WS window table.
pub const m_SMALL: usize = 65536;
pub const m_HS: usize = 8192;
pub const m_WS: usize = 16384;
pub const m_NICE: usize = 128;
pub const m_INS_MAX: usize = 16;
pub const m_TAIL: usize = 1;
/// Inside long matches, every m_STRIDE-th position between the head and the tail is chained
/// too (m_STRIDE = 0: none).
pub const m_STRIDE: usize = 4;
pub const m_BACKTOK: usize = 16;
pub const m_LDEPTH: usize = 1;
pub const m_SAMPLE: usize = 2048;
pub const m_VERIFY: usize = 0;
/// Lazy step: a candidate at p+1 needs length >= l + 1 - m_LSLACK (m_LSLACK = 1: at least as long
/// as the current match l) and must win on estimated saving (literal worth m_HLIT/16 bits,
/// match base cost m_GBASE/16 bits plus extra bits).
pub const m_LSLACK: usize = 1;
pub const m_HLIT: u32 = 64;
/// Literal worth (1/16 bit) in the saving estimate for binary classes (3 and 7).
pub const m_B_HLIT: u32 = 64;
pub const m_GBASE: i32 = 168;
/// Per class: main chain depth, lazy threshold, skip shift, skip cap (T text, P prose,
/// H high-entropy binary, Z high-entropy binary rich in zero bytes, B other binary,
/// DNA-like input is sent as literals).
pub const m_T_DEPTH: usize = 4;
pub const m_T_LAZY: usize = 128;
pub const m_T_SKIP: usize = 5;
pub const m_P_DEPTH: usize = 8;
pub const m_P_LAZY: usize = 258;
pub const m_P_SKIP: usize = 5;
pub const m_H_DEPTH: usize = 1;
pub const m_H_LAZY: usize = 0;
pub const m_H_SKIP: usize = 2;
pub const m_Z_DEPTH: usize = 3;
pub const m_Z_SKIP: usize = 6;
pub const m_Z_CAP: usize = 8;
pub const m_B_DEPTH: usize = 4;
pub const m_B_LAZY: usize = 258;
pub const m_B_SKIP: usize = 8;
/// Structured text (class 6: text with at least 1/m_SDIG of the sample in digits): main depth
/// m_S_DEPTH, lazy m_walk depth m_S_LDEPTH, lazy threshold m_S_LAZY.
pub const m_SDIG: u32 = 6;
pub const m_S_DEPTH: usize = 1;
pub const m_S_LDEPTH: usize = 3;
pub const m_S_LAZY: usize = 258;
/// Largest skip step (extra literals per miss) outside the Z class.
pub const m_SKCAP: usize = 1000000;
/// Per-class m_walk stop (m_NICE is the text value), lazy m_walk depth (m_LDEPTH is the text value),
/// insertion inside matches (m_INS_MAX/m_STRIDE/m_TAIL are the text values).
pub const m_P_NICE: usize = 258;
pub const m_S_NICE: usize = 258;
pub const m_H_NICE: usize = 32;
pub const m_Z_NICE: usize = 32;
pub const m_B_NICE: usize = 258;
pub const m_P_LDEPTH: usize = 1;
pub const m_H_LDEPTH: usize = 1;
pub const m_B_LDEPTH: usize = 2;
pub const m_P_INS: usize = 258;
pub const m_S_INS: usize = 8;
pub const m_B_INS: usize = 12;
pub const m_H_INS: usize = 12;
pub const m_P_STRIDE: usize = 1;
pub const m_S_STRIDE: usize = 8;
pub const m_B_STRIDE: usize = 32;
/// Two-step lazy: when p+1 does not beat the pending match, p+2 is tried (m_L2DEPTH chain steps)
/// and wins if its saving beats the pending one by more than m_L2B/16 bits (m_LAZY2 = 1; 0 = off).
pub const m_LAZY2: usize = 0;
pub const m_L2B: i32 = 40;
pub const m_L2DEPTH: usize = 1;
/// Main m_walk in m_gain mode (a longer candidate must also save more).
pub const m_MAIN_GM: usize = 0;
/// Partial merge: when the new match also covers the last k bytes of the previous match (but not
/// all of it), the previous match is shortened by k if a closer source (at most m_PDEPTH chain steps)
/// covers its shorter length; the new match then starts k bytes earlier (0 = off).
pub const m_PARTIAL: usize = 0;
pub const m_PDEPTH: usize = 8;
/// Class 7: high-entropy input without a dominant byte (no byte above 1/m_FLAT_DIV of the sample:
/// compressed data, images) parsed with 3-byte keys (F_ settings); class 2 keeps the peaky ones
/// (16-bit weights).
pub const m_FLAT_ON: usize = 1;
pub const m_FLAT_DIV: u32 = 16;
/// ... and whose byte collision rate (sum of squared sample counts * 256 / samples^2) is below
/// m_FLAT_SQ/16 (uniform data: 1; images and compressed streams: 1.1-1.4; 8-bit weights: 1.8).
pub const m_FLAT_SQ: u64 = 256;
pub const m_F_DEPTH: usize = 8;
pub const m_F_LAZY: usize = 0;
pub const m_F_LDEPTH: usize = 2;
pub const m_F_SKIP: usize = 6;
pub const m_H_STRIDE: usize = 32;

/// Eight bytes at `i`, first byte most significant (0 when out of range).


/// Four bytes at `i`, first byte most significant (0 when out of range).


/// Input class from a strided byte histogram of at most ~m_SAMPLE bytes:
/// 0 DNA-like, 1 text, 2 high-entropy binary, 3 other binary, 4 high-entropy with zeros,
/// 5 prose (text of letters and spaces with almost no code symbols), 6 structured text (many
/// digits: tables, logs, dumps).


/// Estimated saving (1/16 bit) of a match of length `l` at distance `d` over literals.


/// Length of the m_common prefix of s[a..] and s[b..], at most `cap`.


/// 1 when s[a..a+len] == s[b..b+len]: eight bytes at a time, the last partial word
/// under a mask when a full load fits, else byte by byte.




/// Emit a match (re-checked when m_VERIFY = 1), else a literal. Returns (tokens, next position).


/// Walk the chain from `start`: the longest match at `p` longer than `have` (with `gm` = 1,
/// a longer candidate must also have a higher estimated saving); distance 0 = none found.
/// Each candidate first compares the byte at `best`.


/// Put position `i` at the head of its chain (key = first four bytes under `mask`);
/// returns the previous head.


/// Distance of the first chain entry from `start` (at most `depth` steps) whose next `len` bytes
/// equal those at `p` (0 = none).


/// Partial merge (m_PARTIAL = 1): the new match `(l0, d)` at `p0` also covers the last `k` bytes of
/// the previous match token `t` (`w` bytes, ending at `p0`), but not all of it. When a closer
/// source (at most m_PDEPTH chain steps) covers its first `w - k` bytes, that token is shortened by
/// `k` and the new match starts `k` bytes earlier. Returns the new `(p, l)`.


/// Best match at `p` longer than `have` and at least `minl` long; (0, 0) when none.


/// The parse for one input class (inlined so the text classes get constant settings), with
/// H chain heads and a window table of W entries.


/// DNA settings: key bytes, minimum match, main depth, lazy threshold/depth, skip shift.
pub const m_D_ON: usize = 1;
pub const m_D_KEY: u32 = 8;
pub const m_D_MINL: usize = 9;
pub const m_D_DEPTH: usize = 1;
pub const m_D_LAZY: usize = 0;
pub const m_D_LDEPTH: usize = 1;
pub const m_D_SKIP: usize = 8;
pub const m_D_GM: usize = 0;

/// Put position `i` at the head of its chain (key = first m_D_KEY bytes); returns the previous head.


/// DNA-like input: chains keyed by the first m_D_KEY bytes, matches of at least m_D_MINL bytes.





// fastX: a fast, content-adaptive LZ77 parser for the fixed DEFLATE encoder.
//
// * Content class from a small strided byte histogram: DNA-like inputs, prose (letters and
//   spaces, almost no code symbols), other text, high-entropy binaries (with a zero-rich
//   variant) and structured binaries each get their own settings.
// * Search: hash chains keyed by the first 4 bytes (3 for structured binaries), a main pc_walk and
//   a lazy pc_walk, both with a one-byte quick reject; the lazy step compares candidates by an
//   estimated bit saving. Text looks one byte pc_ahead only after short matches, prose walks
//   deeper without looking pc_ahead, structured text walks one step and looks pc_ahead deeply.
// * Every new match first extends backwards over the tokens just written: literals that
//   match at its distance, and whole earlier matches whose bytes also match there, are
//   folded into it (fewer, longer matches). Inside long matches the first pc_INS_MAX, every
//   pc_STRIDE-th and the last pc_TAIL positions are recorded.
// * Skip acceleration through stretches without matches (capped for zero-rich data).
// * Tables are sized by the input: small inputs clear and touch less memory.
// * Emission optionally re-checks each match (pc_VERIFY = 1); a failed pc_check writes a literal.
// * Tiny inputs (at most pc_TF_N bytes; binaries, optionally plain text) take a separate path: a
//   planner (`pc_tf_plan`, search only) that spends few distinct length and distance codes (the
//   encoder's cost per tiny block is mostly per live symbol) writes a plan, and `pc_emit` writes each
//   planned match only after `pc_check` has re-compared its bytes (anything else becomes literals),
//   so only the emission carries the decode invariant.
// * A class whose search is a single chain step (here text, prose, structured text and the
//   zero-rich binaries) is parsed by `pc_run1` instead of `pc_run`: the pc_same tokens, but the head slot,
//   the candidate and the candidate's first eight bytes of the next position are read one step
//   early, so the loads overlap the branches of the current position, and the literals are
//   written in one go when the next match is known (`pc_r1_kind` decides from constants alone).
// * Pair-structured binaries (16-bit floats: one byte of each pair nearly constant) take the
//   stride path `pc_run_st`: only every second position is searched, with 3-byte keys.
//
// Tokens: t < 256 literal, else 2^24 + (dist-1)*256 + (len-3).

pub const pc_HB: u32 = 15;
pub const pc_HN: usize = 32768;
pub const pc_WN: usize = 32768;
/// Inputs of at most pc_SMALL bytes use pc_HS chain heads and a pc_WS window table.
pub const pc_SMALL: usize = 65536;
pub const pc_HS: usize = 4096;
pub const pc_WS: usize = 16384;
pub const pc_NICE: usize = 32;
pub const pc_INS_MAX: usize = 2;
pub const pc_TAIL: usize = 1;
/// Inside long matches, every pc_STRIDE-th position between the head and the tail is chained
/// too (pc_STRIDE = 0: none).
pub const pc_STRIDE: usize = 0;
pub const pc_BACKTOK: usize = 16;
pub const pc_LDEPTH: usize = 1;
pub const pc_SAMPLE: usize = 2048;
pub const pc_VERIFY: usize = 0;
/// Lazy step: a candidate at p+1 needs length >= l + 1 - pc_LSLACK (pc_LSLACK = 1: at least as long
/// as the current match l) and must win on estimated saving (literal worth pc_HLIT/16 bits,
/// match base cost pc_GBASE/16 bits plus extra bits).
pub const pc_LSLACK: usize = 1;
pub const pc_HLIT: u32 = 80;
pub const pc_GBASE: i32 = 168;
/// Per class: main chain depth, lazy threshold, skip shift, skip cap (T text, P prose,
/// H high-entropy binary, Z high-entropy binary rich in zero bytes, B other binary,
/// DNA-like input is sent as literals).
pub const pc_T_DEPTH: usize = 1;
pub const pc_T_LAZY: usize = 0;
pub const pc_T_SKIP: usize = 4;
pub const pc_P_DEPTH: usize = 1;
pub const pc_P_LAZY: usize = 0;
pub const pc_P_SKIP: usize = 5;
/// Key mask of prose searched with one chain step (0xFFFF_FFFF: four-byte keys; 0xFFFF_FF00: three-byte keys).
pub const pc_P_KM: u32 = 4294967295;
pub const pc_H_DEPTH: usize = 3;
pub const pc_H_LAZY: usize = 0;
pub const pc_H_SKIP: usize = 3;
pub const pc_Z_DEPTH: usize = 1;
pub const pc_Z_SKIP: usize = 4;
pub const pc_Z_CAP: usize = 8;
pub const pc_B_DEPTH: usize = 4;
pub const pc_B_LAZY: usize = 3;
pub const pc_B_SKIP: usize = 4;
/// Structured text (class 6: text with at least 1/pc_SDIG of the sample in digits): main depth
/// pc_S_DEPTH, lazy pc_walk depth pc_S_LDEPTH, lazy threshold pc_S_LAZY.
pub const pc_SDIG: u32 = 6;
pub const pc_S_DEPTH: usize = 1;
pub const pc_S_LDEPTH: usize = 1;
pub const pc_S_LAZY: usize = 258;
/// Largest skip step (extra literals per miss) outside the Z class.
pub const pc_SKCAP: usize = 1000000;
/// 1: a class whose search is one chain step (main pc_walk and lazy pc_walk) is parsed by the read-pc_ahead
/// loop `pc_run1` (the pc_same tokens as `pc_run`); 0: `pc_run` for every class.
pub const pc_R1_ON: usize = 1;
/// Stride path (pc_ST_ON 1): a high-entropy input (class 2 or 4) of more than pc_ST_MIN bytes whose bytes
/// at one parity take at most pc_ST_FEW distinct values while the other parity takes at least pc_ST_MANY
/// (in at most pc_ST_SAMPLE sampled byte pairs) is parsed by `pc_run_st`: only the positions of the
/// low-entropy parity are searched, with 3-byte keys in a direct-mapped table of pc_ST_HN slots
/// (2^pc_ST_HB); a match is at most pc_ST_DMAX back.
pub const pc_ST_ON: usize = 1;
pub const pc_ST_MIN: usize = 65536;
pub const pc_ST_SAMPLE: usize = 4096;
pub const pc_ST_FEW: usize = 32;
pub const pc_ST_MANY: usize = 160;
pub const pc_ST_HB: u32 = 17;
pub const pc_ST_HN: usize = 131072;
pub const pc_ST_DMAX: usize = 32768;
/// Stride path: after a match, at most pc_ST_INS positions of the searched parity inside it are recorded in the table
/// (0: none); a candidate less than pc_ST_DMIN back is not taken (129: distance codes 14..29 only, so a block keeps at
/// most 16 live distance codes).
pub const pc_ST_INS: usize = 258;
pub const pc_ST_DMIN: usize = 129;
/// Tiny inputs (at most pc_TF_N bytes) that `pc_tf_class` calls binary, and with pc_TF_TEXT = 1 also text
/// inputs of a `pc_tf_class` kind below pc_TF_TKIND (0 text, 1 structured text), take the plan +
/// re-verify path (`pc_tf_plan`, then `pc_emit`); every other input takes the engine above. pc_TF_N = 0
/// leaves only the empty input there (no tokens either way): `pc_parse` is then the engine alone.
pub const pc_TF_N: usize = 65536;
pub const pc_TF_TEXT: usize = 1;
pub const pc_TF_TKIND: usize = 1;
/// `pc_tf_class`: about pc_TF_SAMPLE strided bytes (>= 1); structured text has at least 1/pc_TF_SDIG
/// (>= 1) digits.
pub const pc_TF_SAMPLE: usize = 256;
pub const pc_TF_SDIG: u32 = 6;
/// Chain heads (pc_TF_HN = 2^pc_TF_HB slots, 1 <= pc_TF_HB <= 64) and the window table (pc_TF_WN >= 1);
/// positions are kept as u16 (pc_TF_N <= 65536 keeps them exact). Binaries alone (pc_TF_TEXT = 0,
/// pc_TF_BDEPTH = 0) pc_find only distance-1 matches, so the chains never change their plan (a chain
/// candidate can only repeat distance 1, the one kept code): minimal tables skip clearing 72 KB.
/// The text planner (pc_TF_TEXT = 1) walks the chains: pc_TF_HB 12, pc_TF_HN 4096, pc_TF_WN 32768 there.
pub const pc_TF_HB: u32 = 12;
pub const pc_TF_HN: usize = 4096;
pub const pc_TF_WN: usize = 16384;
/// Per kind: chain steps, lazy steps below this match length, skip shift (after m literals in a
/// row, m >> skip positions are not searched; a shift of 32 or more never skips). T text, S
/// structured text, B binaries (3-byte keys; pc_TF_BDEPTH 0 = distance 1 only).
pub const pc_TF_TDEPTH: usize = 1;
pub const pc_TF_TLAZY: usize = 0;
pub const pc_TF_TSKIP: usize = 3;
pub const pc_TF_SDEPTH: usize = 1;
pub const pc_TF_SLAZY: usize = 258;
pub const pc_TF_SSKIP: usize = 3;
pub const pc_TF_BDEPTH: usize = 0;
pub const pc_TF_BLAZY: usize = 0;
pub const pc_TF_BSKIP: usize = 4;
/// A pc_walk stops at a match of pc_TF_NICE bytes; skip steps are at most pc_TF_SKCAP.
pub const pc_TF_NICE: usize = 64;
pub const pc_TF_SKCAP: usize = 1000000;
/// 1: distance 1 is tried before the chain on text too (always on binaries).
pub const pc_TF_TRLE: usize = 1;
/// 1: a new match extends backwards over pending literals; 1: the pending match is folded into
/// a new one when its bytes also match at the new distance.
pub const pc_TF_BACK: usize = 1;
pub const pc_TF_FOLD: usize = 1;
/// The previous match distance is tried before the chain (1), after it (2) or not at all (0).
pub const pc_TF_REP: usize = 0;
/// 1: no search where a pc_run of four equal bytes starts (the next position takes distance 1).
pub const pc_TF_RUNSKIP: usize = 1;
/// Positions chained at the head and at the tail of a match.
pub const pc_TF_INS: usize = 2;
pub const pc_TF_TAIL: usize = 1;
/// Keep thresholds (uses per code): text pc_TF_KL / pc_TF_KD, binaries pc_TF_BKL / pc_TF_BKD (0 or 1: keep
/// every code used).
pub const pc_TF_KL: u32 = 5;
pub const pc_TF_KD: u32 = 5;
pub const pc_TF_BKL: u32 = 3;
pub const pc_TF_BKD: u32 = 3;
/// Re-pc_find: chain steps, single literals tried before giving up; a dropped-distance match that
/// cannot be re-found becomes literals when at most pc_TF_DLIT bytes long, else keeps its distance
/// (its code re-admitted).
pub const pc_TF_RDEPTH: usize = 8;
pub const pc_TF_SHIFT: usize = 1;
pub const pc_TF_DLIT: usize = 8;

/// Eight bytes at `i`, first byte most significant (0 when out of range).
#[inline(always)]
pub fn pc_be8(s: &[u8], i: usize) -> u64 {
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
pub fn pc_be4(s: &[u8], i: usize) -> u32 {
    if i + 4 <= s.len() {
        ((s[i] as u32) << 24) | ((s[i + 1] as u32) << 16) | ((s[i + 2] as u32) << 8) | (s[i + 3] as u32)
    } else {
        0
    }
}

/// Input class from a strided byte histogram of at most ~pc_SAMPLE bytes:
/// 0 DNA-like, 1 text, 2 high-entropy binary, 3 other binary, 4 high-entropy with zeros,
/// 5 prose (text of letters and spaces with almost no code symbols), 6 structured text (many
/// digits: tables, logs, dumps).


/// Estimated saving (1/16 bit) of a match of length `l` at distance `d` over literals.
#[inline(always)]
pub fn pc_gain(l: usize, d: usize) -> i32 {
    let mut c = pc_GBASE;
    if l > 10 && l < 258 {
        c += 16 * (29 - ((l - 3) as u32).leading_zeros()) as i32;
    }
    if d > 4 {
        c += 16 * (30 - ((d - 1) as u32).leading_zeros()) as i32;
    }
    (l as i32) * (pc_HLIT as i32) - c
}

/// Length of the pc_common prefix of s[a..] and s[b..], at most `cap`.


/// 1 when s[a..a+len] == s[b..b+len]: eight bytes at a time, the last partial word
/// under a mask when a full load fits, else byte by byte.
#[inline(always)]
pub fn pc_same(s: &[u8], a: usize, b: usize, len: usize) -> usize {
    let n = s.len();
    let mut k = 0usize;
    let mut ok = 1usize;
    while ok == 1 && k + 8 <= len {
        if pc_be8(s, a + k) == pc_be8(s, b + k) {
            k += 8;
        } else {
            ok = 0;
        }
    }
    if ok == 1 && k < len {
        if a + k + 8 <= n && b + k + 8 <= n {
            let x = pc_be8(s, a + k) ^ pc_be8(s, b + k);
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
pub fn pc_put_lit(s: &[u8], out: &mut [u32], nt: usize, p: usize) -> usize {
    out[nt] = s[p] as u32;
    nt + 1
}

/// Emit a match (re-checked when pc_VERIFY = 1), else a literal. Returns (tokens, next position).
#[inline(always)]
pub fn pc_put_match(s: &[u8], out: &mut [u32], nt: usize, p: usize, d: usize, l: usize) -> (usize, usize) {
    let n = s.len();
    if d >= 1 && d <= 32768 && d <= p && l >= 3 && l <= 258 && p < n && l <= n - p && (pc_VERIFY == 0 || pc_same(s, p - d, p, l) == 1) {
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


/// Put position `i` at the head of its chain (key = first four bytes under `mask`);
/// returns the previous head.


/// Best match at `p` longer than `have` and at least `minl` long; (0, 0) when none.


/// The pc_parse for one input class (inlined so the text classes get constant settings), with
/// H chain heads and a window table of W entries.


// ─────────────── the stride path: pair-structured binaries (16-bit floats and the like) ───────────────

/// Parity of the low-entropy bytes of pair-structured data (0 even, 1 odd), or 2 when the input is
/// not such data: in at most pc_ST_SAMPLE sampled byte pairs one parity takes at most pc_ST_FEW distinct
/// values and the other at least pc_ST_MANY.


/// The stride path's parity for an input of class `cls` that takes it (0 or 1), else 2.


/// Table slot of the three bytes at `p` (low-entropy, other, low-entropy).


/// Put position `p` in slot `a` of the stride table; returns the position it replaces.


/// The match at `p` from the table entry `c`: (length, distance) when `c` is at most pc_ST_DMAX before
/// `p` and the three key bytes agree (compared one by one, then extended byte by byte), else (0, 0).


/// Record position `q` in its slot of the stride table.


/// Record the positions of parity `ph` in `from..end` (at most pc_ST_INS of them, all below `lim`) in the stride table.


/// Stride-2 greedy pc_parse: only positions of parity `ph` are searched; the table keeps the most
/// recent position per key slot (searched positions and, through `pc_st_fill`, those inside matches); a failed search writes the pair (p, p + 1) as literals, and a
/// match that ends on the other parity is followed by one literal.


// ─────────────── the read-pc_ahead loop for classes searched with one chain step ───────────────

/// Slot of position `i` in a head table of H entries (the slot `pc_insert` uses for 4-byte keys).


/// Record position `i` in slot `a`.
#[inline(always)]
pub fn pc_head_set<const H: usize>(head: &mut [u32; H], a: usize, i: usize) {
    head[a] = i as u32;
}

/// What the search at position `i` will need, read before it gets there: its slot, the head entry
/// there (the candidate) and the candidate's first eight bytes.


/// `pc_ahead` for position `i` when it is below `lim` (it will be searched), else the values given.
/// (The test also keeps these loads apart from the eight-byte load of the search at `i - 1`,
/// which shares bytes with them: each stays a single load.)


/// `pc_common` continued after `k0` bytes already known to agree.
#[inline(always)]
pub fn pc_common_from(s: &[u8], a: usize, b: usize, cap: usize, k0: usize) -> usize {
    let mut k = k0;
    let mut pc_run = 1u32;
    while pc_run == 1 && k + 8 <= cap {
        let x = pc_xor8(s, a.wrapping_add(k), b.wrapping_add(k));
        if x == 0 {
            k += 8;
        } else {
            k += (x.leading_zeros() / 8) as usize;
            pc_run = 0;
        }
    }
    while pc_run == 1 && k < cap {
        if s[a + k] == s[b + k] {
            k += 1;
        } else {
            pc_run = 0;
        }
    }
    k
}

/// How many bytes agree at `c` and `p`, given the xor `x` of their first eight bytes taken as
/// words: the leading zero bytes of `x`, or what `pc_common_from` finds past eight equal bytes.
#[inline(always)]
pub fn pc_xlen(s: &[u8], c: usize, p: usize, x: u64) -> usize {
    if x != 0 {
        (x.leading_zeros() / 8) as usize
    } else {
        let mut cap = s.len() - p;
        if cap > 258 {
            cap = 258;
        }
        pc_common_from(s, c, p, cap, 8)
    }
}

/// The xor of the eight-byte big-endian words at `a` and `b` (0 when either is out of range): both or-trees in one
/// block, so each stays a single load.
#[inline(always)]
pub fn pc_xor8(s: &[u8], a: usize, b: usize) -> u64 {
    let n = s.len();
    if n >= 8 && a <= n - 8 && b <= n - 8 {
        let x = ((s[a] as u64) << 56)
            | ((s[a + 1] as u64) << 48)
            | ((s[a + 2] as u64) << 40)
            | ((s[a + 3] as u64) << 32)
            | ((s[a + 4] as u64) << 24)
            | ((s[a + 5] as u64) << 16)
            | ((s[a + 6] as u64) << 8)
            | (s[a + 7] as u64);
        let y = ((s[b] as u64) << 56)
            | ((s[b + 1] as u64) << 48)
            | ((s[b + 2] as u64) << 40)
            | ((s[b + 3] as u64) << 32)
            | ((s[b + 4] as u64) << 24)
            | ((s[b + 5] as u64) << 16)
            | ((s[b + 6] as u64) << 8)
            | (s[b + 7] as u64);
        x ^ y
    } else {
        0
    }
}

/// `pc_xlen` reading sixteen bytes with one branch: l1 = leading zero bytes of `x` (4..=8); when l1 is 8 the leading zero
/// bytes of the next words' xor are added (`l1 >> 3` is 1 exactly then); `pc_common_from` continues only past sixteen
/// equal bytes. Inputs with fewer than sixteen bytes left at `p` take `pc_xlen`.
#[inline(always)]
pub fn pc_xlen16(s: &[u8], c: usize, p: usize, x: u64) -> usize {
    let n = s.len();
    if n >= 16 && p <= n - 16 && c < p {
        let x2 = pc_xor8(s, c + 8, p + 8);
        let mut y = x;
        let mut k = 0usize;
        if x == 0 {
            y = x2;
            k = 8;
        }
        let l = k + (y.leading_zeros() / 8) as usize;
        if l >= 16 {
            let mut cap = n - p;
            if cap > 258 {
                cap = 258;
            }
            pc_common_from(s, c, p, cap, 16)
        } else {
            l
        }
    } else {
        pc_xlen(s, c, p, x)
    }
}

/// The match at `p` from the candidate `c` whose first eight bytes are the word `cw`: (length,
/// distance) when at least four bytes agree at a distance in 1..=32768, else (0, 0). One xor of
/// the two words decides.


/// The length a match at the lazy position has to beat after a match of length `l`:
/// max(3, l - pc_LSLACK).
#[inline(always)]
pub fn pc_lazy_lo(l: usize) -> usize {
    if l > pc_LSLACK && l - pc_LSLACK > 3 {
        l - pc_LSLACK
    } else {
        3
    }
}

/// `pc_probe` for the lazy step at `q`, one after a match of length `l`: only a match longer than
/// `pc_lazy_lo(l)` counts, and the byte at that offset is compared first.
#[inline(always)]
pub fn pc_probe_lazy(s: &[u8], c: usize, cw: u64, q: usize, l: usize) -> (usize, usize) {
    let n = s.len();
    let lo = pc_lazy_lo(l);
    let d = q.wrapping_sub(c);
    let x = cw ^ pc_be8(s, q);
    if d.wrapping_sub(1) < 32768 && (x >> 32) == 0 && q + lo < n && s[c + lo] == s[q + lo] {
        let m = pc_xlen16(s, c, q, x);
        if m > lo {
            (m, d)
        } else {
            (0, 0)
        }
    } else {
        (0, 0)
    }
}

/// Literals skipped without a search after `miss` misses in a row: min(miss >> skip, skcap).
#[inline(always)]
pub fn pc_skip_len(miss: usize, skip: usize, skcap: usize) -> usize {
    let step = miss >> skip;
    if step > skcap {
        skcap
    } else {
        step
    }
}

/// `p` moved on by `step` positions, at most to `lim` (needs p <= lim).
#[inline(always)]
pub fn pc_skip_to(p: usize, step: usize, lim: usize) -> usize {
    if step > lim - p {
        lim
    } else {
        p + step
    }
}

/// Write the literals of the positions `from..to` (the ones passed since the last match).
#[inline(always)]
pub fn pc_flush(input: &[u8], out: &mut [u32], nt0: usize, from: usize, to: usize) -> usize {
    let mut nt = nt0;
    let mut j = from;
    while j < to {
        nt = pc_put_lit(input, out, nt, j);
        j += 1;
    }
    nt
}

/// The backward merge of `pc_run` for the match (l0, d) at `p0`: earlier tokens whose bytes also match
/// at distance `d` are folded into it. Returns (tokens kept, start, length).
#[inline(always)]
pub fn pc_fold(input: &[u8], out: &[u32], nt0: usize, p0: usize, l0: usize, d: usize) -> (usize, usize, usize) {
    let mut nt = nt0;
    let mut p = p0;
    let mut l = l0;
    let mut back = 0usize;
    while back < pc_BACKTOK && nt > 0 && nt <= out.len() && l < 258 && d < p {
        let t = out[nt - 1];
        if t < 256 && input[p - 1] == input[p - 1 - d] {
            p -= 1;
            nt -= 1;
            l += 1;
            back += 1;
        } else if t >= 16777216 {
            let w = ((t - 16777216) % 256 + 3) as usize;
            if l + w <= 258 && w <= p && d <= p - w && pc_same(input, p - w - d, p - w, w) == 1 {
                p -= w;
                nt -= 1;
                l += w;
                back += 1;
            } else {
                back = pc_BACKTOK;
            }
        } else {
            back = pc_BACKTOK;
        }
    }
    (nt, p, l)
}

/// Record, as `pc_run` does, the first pc_INS_MAX and the last pc_TAIL positions inside the match that
/// ends at `end`, starting at `ins0` (positions from `lim` on have no full key).


/// `pc_fold` after a word test: the token before the match (a literal, or a match of `w` bytes) can be folded into it
/// only if its last byte (literal) or its last min(w, 8) bytes (match) agree at distance `d`; one xor of the eight
/// bytes before `p0` and before `p0 - d` tests that, and when it fails the inputs come back unchanged (`pc_fold` would
/// stop at its first token).
#[inline(always)]
pub fn pc_fold_w(input: &[u8], out: &[u32], nt0: usize, p0: usize, l0: usize, d: usize) -> (usize, usize, usize) {
    let mut m = 1u32;
    if nt0 > 0 && nt0 <= out.len() {
        let t = out[nt0 - 1];
        if t >= 16777216 {
            m = (t - 16777216) % 256 + 3;
            if m > 8 {
                m = 8;
            }
        }
    }
    let mut x = 1u64;
    if d < p0 && p0 - d >= 8 && p0 <= input.len() {
        x = (pc_be8(input, p0 - 8) ^ pc_be8(input, p0 - 8 - d)) & (18446744073709551615u64 >> (64 - 8 * m));
    }
    if x != 0 && d < p0 && p0 - d >= 8 {
        (nt0, p0, l0)
    } else {
        pc_fold(input, out, nt0, p0, l0, d)
    }
}

/// `pc_flush` writing four literals without a loop when at most four are due and four fit (the ones past `to` are
/// overwritten by the next tokens); the loop otherwise.
#[inline(always)]
pub fn pc_flush4(input: &[u8], out: &mut [u32], nt0: usize, from: usize, to: usize) -> usize {
    if from <= to && to - from <= 4 && from + 4 <= input.len() && nt0 + 4 <= out.len() {
        out[nt0] = input[from] as u32;
        out[nt0 + 1] = input[from + 1] as u32;
        out[nt0 + 2] = input[from + 2] as u32;
        out[nt0 + 3] = input[from + 3] as u32;
        nt0 + (to - from)
    } else {
        pc_flush(input, out, nt0, from, to)
    }
}

/// Slot of position `i` for keys of the bytes `km` keeps of the first four (km = 0xFFFF_FFFF: four bytes, the slot
/// `pc_slot_of` gives; 0xFFFF_FF00: three bytes, the slot `pc_insert` gives class 3).
#[inline(always)]
pub fn pc_slot_of_m<const H: usize>(s: &[u8], i: usize, km: u32) -> usize {
    let k = (pc_be4(s, i) & km) as u64;
    (k.wrapping_mul(0x9E37_79B9_7F4A_7C15) >> (64 - pc_HB)) as usize % H
}

/// `pc_ahead` with keys under `km`.
#[inline(always)]
pub fn pc_ahead_m<const H: usize>(s: &[u8], head: &[u32; H], i: usize, km: u32) -> (usize, usize, u64) {
    let a = pc_slot_of_m::<H>(s, i, km);
    let c = head[a] as usize;
    (a, c, pc_be8(s, c))
}

/// `pc_ahead_if` with keys under `km`.
#[inline(always)]
pub fn pc_ahead_if_m<const H: usize>(s: &[u8], head: &[u32; H], i: usize, lim: usize, a: usize, c: usize, w: u64, km: u32) -> (usize, usize, u64) {
    if i < lim {
        pc_ahead_m::<H>(s, head, i, km)
    } else {
        (a, c, w)
    }
}

/// `ahead_fix` with keys under `km`.
#[inline(always)]
pub fn pc_ahead_fix_m<const H: usize>(s: &[u8], head: &[u32; H], i: usize, lim: usize, e: usize, a: usize, c: usize, w: u64, a0: usize, c0: usize, w0: u64, km: u32) -> (usize, usize, u64) {
    if i == e && i < lim && a < H && head[a] as usize == c {
        (a, c, w)
    } else {
        pc_ahead_if_m::<H>(s, head, i, lim, a0, c0, w0, km)
    }
}

/// `pc_probe` for keys under `km`: a match needs the key bytes to agree (four, or three for km = 0xFFFF_FF00).
#[inline(always)]
pub fn pc_probe_m(s: &[u8], c: usize, cw: u64, p: usize, km: u32) -> (usize, usize) {
    let d = p.wrapping_sub(c);
    let x = cw ^ pc_be8(s, p);
    if d.wrapping_sub(1) < 32768 && ((x >> 32) & (km as u64)) == 0 {
        (pc_xlen16(s, c, p, x), d)
    } else {
        (0, 0)
    }
}

/// `record3` with keys under `km`.
#[inline(always)]
pub fn pc_record3_m<const H: usize>(s: &[u8], head: &mut [u32; H], ins0: usize, a0: usize, end: usize, lim: usize, km: u32) {
    let mut ins = ins0;
    let mut stop = end;
    // wrapping: pc_same code as `+` here (no overflow on any real input), total in the model
    if stop > ins.wrapping_add(pc_INS_MAX) {
        stop = ins.wrapping_add(pc_INS_MAX);
    }
    if stop > lim {
        stop = lim;
    }
    if ins < stop && a0 < H {
        pc_head_set(head, a0, ins);
        ins += 1;
    }
    while ins < stop {
        let a = pc_slot_of_m::<H>(s, ins, km);
        pc_head_set(head, a, ins);
        ins += 1;
    }
    if pc_TAIL == 1 {
        if ins + 1 < end {
            ins = end - 1;
        }
        if ins < end && ins < lim {
            let a = pc_slot_of_m::<H>(s, ins, km);
            pc_head_set(head, a, ins);
        }
    } else {
        if ins + pc_TAIL < end {
            ins = end - pc_TAIL;
        }
        while ins < end && ins < lim {
            let a = pc_slot_of_m::<H>(s, ins, km);
            pc_head_set(head, a, ins);
            ins += 1;
        }
    }
}

/// `pc_run` for a class searched with one chain step (4-byte keys; main pc_walk and lazy pc_walk): the pc_same
/// tokens, without the window table, and with the search state of the next position (`pc_ahead`: its
/// slot, its candidate and the candidate's first eight bytes) read one step early, before the
/// branches of the current position are decided. `pre_slot`, `pre_c`, `pre_w` always describe the
/// position searched next: `p` at the top of the loop, `p + 1` once `p` is recorded (`pc_ahead_if`
/// leaves them alone when that position is past the last one searched).
/// The literals are not written while scanning: `ls` is the start of the positions passed since
/// the last match, and `pc_flush` writes them when the next match is known (or at the end), so the
/// scan itself only loads: the word at `p`, the head entry and the candidate's word.
#[inline(always)]
pub fn pc_run1<const H: usize>(input: &[u8], out: &mut [u32], skip: usize, lazy: usize, skcap: usize, km: u32) -> usize {
    let n = input.len();
    let mut nt = 0usize;
    let mut ls = 0usize; // first position whose literal is not written yet
    if n > 16 {
        let mut p = 0usize;
        let mut head = [0u32; H];
        let lim = n - 8;
        let mut miss = 0usize; // literals since the last match
        let mut fuel = n.saturating_add(16);
        let a0 = pc_ahead_m::<H>(input, &head, 0, km);
        let mut pre_slot = a0.0;
        let mut pre_c = a0.1;
        let mut pre_w = a0.2;
        while p < lim && fuel > 0 {
            fuel -= 1;
            let c = pre_c;
            let cw = pre_w;
            pc_head_set(&mut head, pre_slot, p);
            let a1 = pc_ahead_if_m::<H>(input, &head, p + 1, lim, pre_slot, pre_c, pre_w, km);
            pre_slot = a1.0;
            pre_c = a1.1;
            pre_w = a1.2;
            let f = pc_probe_m(input, c, cw, p, km);
            if f.0 >= 3 {
                let mut l = f.0;
                let mut d = f.1;
                let mut ins = p + 1;
                // Lazy: move on while the next position has a better match by the saving estimate.
                let mut go = 1u32;
                while go == 1 && l < lazy && p + 1 < lim {
                    let q = p + 1;
                    let c2 = pre_c;
                    let w2 = pre_w;
                    pc_head_set(&mut head, pre_slot, q);
                    ins = q + 1;
                    let a2 = pc_ahead_if_m::<H>(input, &head, q + 1, lim, pre_slot, pre_c, pre_w, km);
                    pre_slot = a2.0;
                    pre_c = a2.1;
                    pre_w = a2.2;
                    let g = pc_probe_lazy(input, c2, w2, q, l);
                    if g.0 >= 4 && pc_gain(g.0, g.1) > pc_gain(l, d) {
                        p = q;
                        l = g.0;
                        d = g.1;
                    } else {
                        go = 0;
                    }
                }
                let e = p + l;
                let ae = pc_ahead_if_m::<H>(input, &head, e, lim, pre_slot, pre_c, pre_w, km);
                nt = pc_flush4(input, out, nt, ls, p);
                let b = pc_fold_w(input, out, nt, p, l, d);
                let r = pc_put_match(input, out, b.0, b.1, d, b.2);
                nt = r.0;
                let end = r.1;
                pc_record3_m::<H>(input, &mut head, ins, pre_slot, end, lim, km);
                p = end;
                ls = end;
                miss = 0;
                let a3 = pc_ahead_fix_m::<H>(input, &head, p, lim, e, ae.0, ae.1, ae.2, pre_slot, pre_c, pre_w, km);
                pre_slot = a3.0;
                pre_c = a3.1;
                pre_w = a3.2;
            } else {
                p += 1;
                miss += 1;
                let step = pc_skip_len(miss, skip, skcap);
                if step > 0 {
                    p = pc_skip_to(p, step, lim);
                    let a4 = pc_ahead_if_m::<H>(input, &head, p, lim, pre_slot, pre_c, pre_w, km);
                    pre_slot = a4.0;
                    pre_c = a4.1;
                    pre_w = a4.2;
                }
            }
        }
    }
    while ls < n {
        nt = pc_put_lit(input, out, nt, ls);
        ls += 1;
    }
    nt
}


/// The class itself when `pc_parse` gives class `cls` to `pc_run1` (pc_R1_ON, no stride recording, and one
/// chain step for both walks of the class), else 0. Constant conditions only: any other constant
/// set leaves the class with `pc_run`.


// ─────────────── chain links + an extra candidate at every match (`pc_run1c`): text and structured binaries ───────────────
//
// `pc_run1c` is `pc_run1` (the read-pc_ahead loop with key mask `km`) plus one chain link per recorded position: `prev[i % 32768]`
// keeps the position the head slot held before `i` took it. At every match the candidate's predecessor (and, with
// `dp >= 2`, its predecessor) is tried once more (`pc_f_deepen`, inside the match branch: a pc_probe finds 0 or at least
// `minl` bytes for the key masks used); every candidate is validated by `pc_f_try` itself
// (distance in 1..=32768, the bytes compared by `pc_common_from`), so neither `head` nor `prev` needs an invariant.

/// Classes in `pc_run1c`: bit 1 = text (class 1: four-byte keys, pc_KF_DP steps), bit 8 = structured binaries (class 3:
/// three-byte keys, pc_KF_BDP steps, skip shift pc_KF_BSKIP, no lazy step).
pub const pc_KF_ON: usize = 9;
pub const pc_KF_DP: usize = 1;
pub const pc_KF_BDP: usize = 2;
pub const pc_KF_BSKIP: usize = 6;

/// Head slot `a` takes position `i`; the position it held is linked behind `i`.
#[inline(always)]
pub fn pc_f_link<const H: usize>(head: &mut [u32; H], prev: &mut [u32; 32768], a: usize, i: usize) {
    prev[i % 32768] = head[a];
    head[a] = i as u32;
}

/// The match at `p` from the older candidate `c2` (taken only when it is longer than `l` and at least `minl`), else
/// (`l`, `d`). `c2` must lie before `c` and at most 32768 back; one byte test at `l` first.
#[inline(always)]
pub fn pc_f_try(s: &[u8], c: usize, c2: usize, p: usize, l: usize, d: usize, minl: usize) -> (usize, usize) {
    let n = s.len();
    let d2 = p.wrapping_sub(c2);
    if c2 < c && d2.wrapping_sub(1) < 32768 && p + l < n && s[c2 + l] == s[p + l] {
        let mut cap = n - p;
        if cap > 258 {
            cap = 258;
        }
        let m = pc_common_from(s, c2, p, cap, 0);
        if m > l && m >= minl {
            (m, d2)
        } else {
            (l, d)
        }
    } else {
        (l, d)
    }
}

/// One chain step from `c` (its link `c2`), and a second one when `dp >= 2`.
#[inline(always)]
pub fn pc_f_deepen(s: &[u8], prev: &[u32; 32768], c: usize, c2: usize, p: usize, l: usize, d: usize, dp: usize, minl: usize) -> (usize, usize) {
    let g = pc_f_try(s, c, c2, p, l, d, minl);
    if dp >= 2 && c2 < c {
        let c3 = prev[c2 % 32768] as usize;
        pc_f_try(s, c2, c3, p, g.0, g.1, minl)
    } else {
        g
    }
}

/// `pc_record3_m` with links (the pc_same positions in the pc_same order).
#[inline(always)]
pub fn pc_f_record3<const H: usize>(s: &[u8], head: &mut [u32; H], prev: &mut [u32; 32768], ins0: usize, a0: usize, end: usize, lim: usize, km: u32) {
    let mut ins = ins0;
    let mut stop = end;
    if stop > ins.wrapping_add(pc_INS_MAX) {
        stop = ins.wrapping_add(pc_INS_MAX);
    }
    if stop > lim {
        stop = lim;
    }
    if ins < stop && a0 < H {
        pc_f_link::<H>(head, prev, a0, ins);
        ins += 1;
    }
    while ins < stop {
        let a = pc_slot_of_m::<H>(s, ins, km);
        pc_f_link::<H>(head, prev, a, ins);
        ins += 1;
    }
    if pc_TAIL == 1 {
        if ins + 1 < end {
            ins = end - 1;
        }
        if ins < end && ins < lim {
            let a = pc_slot_of_m::<H>(s, ins, km);
            pc_f_link::<H>(head, prev, a, ins);
        }
    } else {
        if ins + pc_TAIL < end {
            ins = end - pc_TAIL;
        }
        while ins < end && ins < lim {
            let a = pc_slot_of_m::<H>(s, ins, km);
            pc_f_link::<H>(head, prev, a, ins);
            ins += 1;
        }
    }
}

/// `pc_run1` with chain links and `pc_f_deepen` at every match of at least `minl` bytes.
#[inline(always)]
pub fn pc_run1c<const H: usize>(input: &[u8], out: &mut [u32], skip: usize, lazy: usize, skcap: usize, km: u32, dp: usize, minl: usize) -> usize {
    let n = input.len();
    let mut nt = 0usize;
    let mut ls = 0usize;
    if n > 16 {
        let mut p = 0usize;
        let mut head = [0u32; H];
        let mut prev = [0u32; 32768];
        let lim = n - 8;
        let mut miss = 0usize;
        let mut fuel = n.saturating_add(16);
        let a0 = pc_ahead_m::<H>(input, &head, 0, km);
        let mut pre_slot = a0.0;
        let mut pre_c = a0.1;
        let mut pre_w = a0.2;
        while p < lim && fuel > 0 {
            fuel -= 1;
            let c = pre_c;
            let cw = pre_w;
            pc_f_link::<H>(&mut head, &mut prev, pre_slot, p);
            let a1 = pc_ahead_if_m::<H>(input, &head, p + 1, lim, pre_slot, pre_c, pre_w, km);
            pre_slot = a1.0;
            pre_c = a1.1;
            pre_w = a1.2;
            let f = pc_probe_m(input, c, cw, p, km);
            if f.0 >= 3 {
                let cl = prev[c % 32768] as usize;
                let g = pc_f_deepen(input, &prev, c, cl, p, f.0, f.1, dp, minl);
                let mut l = g.0;
                let mut d = g.1;
                let mut ins = p + 1;
                let mut go = 1u32;
                while go == 1 && l < lazy && p + 1 < lim {
                    let q = p + 1;
                    let c2 = pre_c;
                    let w2 = pre_w;
                    pc_f_link::<H>(&mut head, &mut prev, pre_slot, q);
                    ins = q + 1;
                    let a2 = pc_ahead_if_m::<H>(input, &head, q + 1, lim, pre_slot, pre_c, pre_w, km);
                    pre_slot = a2.0;
                    pre_c = a2.1;
                    pre_w = a2.2;
                    let g = pc_probe_lazy(input, c2, w2, q, l);
                    if g.0 >= 4 && pc_gain(g.0, g.1) > pc_gain(l, d) {
                        p = q;
                        l = g.0;
                        d = g.1;
                    } else {
                        go = 0;
                    }
                }
                let e = p + l;
                let ae = pc_ahead_if_m::<H>(input, &head, e, lim, pre_slot, pre_c, pre_w, km);
                nt = pc_flush4(input, out, nt, ls, p);
                let b = pc_fold_w(input, out, nt, p, l, d);
                let r = pc_put_match(input, out, b.0, b.1, d, b.2);
                nt = r.0;
                let end = r.1;
                pc_f_record3::<H>(input, &mut head, &mut prev, ins, pre_slot, end, lim, km);
                p = end;
                ls = end;
                miss = 0;
                let a3 = pc_ahead_fix_m::<H>(input, &head, p, lim, e, ae.0, ae.1, ae.2, pre_slot, pre_c, pre_w, km);
                pre_slot = a3.0;
                pre_c = a3.1;
                pre_w = a3.2;
            } else {
                p += 1;
                miss += 1;
                let step = pc_skip_len(miss, skip, skcap);
                if step > 0 {
                    p = pc_skip_to(p, step, lim);
                    let a4 = pc_ahead_if_m::<H>(input, &head, p, lim, pre_slot, pre_c, pre_w, km);
                    pre_slot = a4.0;
                    pre_c = a4.1;
                    pre_w = a4.2;
                }
            }
        }
    }
    while ls < n {
        nt = pc_put_lit(input, out, nt, ls);
        ls += 1;
    }
    nt
}

/// Structured binaries (class 3) in `pc_run1c`: three-byte keys, pc_KF_BDP chain steps, matches from 3 bytes, no lazy step.


/// Text (class 1) in `pc_run1c`: four-byte keys, pc_KF_DP chain steps, the text lazy threshold.


/// The class `pc_run1c` takes (1 text, 3 structured binaries) under pc_KF_ON, else 0. Constant conditions only.


/// Every input except larger text and prose: smaller tables for small inputs.


/// Inputs that `pc_tf_route` sends to the tiny path: plan, then pc_emit with re-verification; all others:
/// the engine (the stride path for pair-structured binaries, `pc_run1` for the classes `pc_r1_kind`
/// names, `pc_run` for the rest).


// ─────────────── tiny inputs: plan + re-verify (`pc_parse` sends inputs of at most pc_TF_N bytes here) ───────────────
//
// Phase 2, the emission (`pc_emit` with `pc_check`, `pc_mlen`, `pc_load8`, `pc_first_diff`, `pc_get0`), carries the
// whole decode invariant of this path: a planned match is written only if `pc_check` finds it in range
// and `pc_mlen` confirms every byte; anything else becomes literals. Phase 1, the planner (`pc_tf_plan` and
// everything it calls), is search: it only has to be total (no panic, terminates) and may return a
// plan of any length and contents (`pc_get0` reads 0 past its end).
// Plan format: a token list; entry k describes the k-th planned token: `len + 512 * dist` for a
// match, and any entry that `pc_check` rejects stands for `max(1, len)` literals (`len = v % 512`), so
// `pc_run` (dist 0, 1 <= pc_run <= 511) is a pc_run of `pc_run` literals and 0 a single literal. A rejected
// match therefore costs literals over its planned length and the plan stays aligned.

/// The eight bytes at `p` as one big-endian number (byte `p` most significant), or 0 when fewer
/// than eight remain (Horner form; one load plus `bswap` once inlined).


/// How many leading (most significant) bytes the words `x` and `y` share: 8 when equal.


/// How many bytes agree at `a` and `b`, up to `cap` (needs `a + cap <= n` and `b + cap <= n`):
/// eight at a time, the first mismatching word resolved by `pc_first_diff`, the last `cap % 8` bytes
/// one at a time. The only function whose result the emission trusts (through `pc_check`).


/// True only if `(len, dist)` is a legal match at `p` whose bytes all agree.


/// `v[i]`, or 0 when `i` is out of range: a read that cannot panic.


/// `v[i] = x` when `i` is in range, nothing otherwise: a write that cannot panic.


/// Phase 2: pc_walk the plan from 0 (entry `k` for the `k`-th planned token); a planned match is
/// written only if `pc_check` accepts it, else its bytes become literals (`owed`), so the plan stays aligned.


// ═══════════════ tiny inputs: the symbol-frugal planner (search only) ═══════════════
//
// The validator's encoder pays per block about 1.3 us for every live literal/length symbol and about
// 1 us for every live distance code (two or more live; a single live distance code costs nothing), on
// top of a few ns per token. A tiny input is one block, so its encode time is mostly this per-symbol
// overhead. The literal alphabet is fixed by the input (every distinct byte is a literal once), so the
// planner works on the length and distance codes:
//  1. `pc_tf_class`: binary (a zero byte or many control bytes in ~pc_TF_SAMPLE strided bytes), structured
//     text (>= 1/pc_TF_SDIG digits) or text.
//  2. `pc_tf_stage1`: a lazy hash-chain pc_parse into a token list (u16 position chains; distance 1, then the
//     previous distance, then the chain; backward extension over pending literals; the pending match is
//     folded into a new one when its bytes also match at the new distance; the engine's bit-saving
//     estimate for the lazy step) and a histogram of length codes and distance codes. Binaries
//     (pc_TF_BDEPTH 0): distance 1 only, so zero runs are one literal plus distance-1 matches and a single
//     distance code is live.
//  3. `pc_tf_keep`: a length code is kept when used >= pc_TF_KL (binaries pc_TF_BKL) times, a distance code
//     >= pc_TF_KD (pc_TF_BKD) times.
//  4. `pc_tf_rewrite`: consecutive matches at one distance are one span, re-split into kept lengths
//     (`pc_tf_piece`: one kept length, many maximal ones, or two kept lengths summing to the rest); a match
//     whose distance code was dropped is re-found at a kept distance (its chain, the two most recent
//     distances, distance 1; after up to pc_TF_SHIFT single literals), else written as literals when at
//     most pc_TF_DLIT bytes. Online re-admission: a span the kept lengths would leave >= 3 bytes uncovered
//     re-admits its own codes; a longer unfindable match keeps its distance and re-admits that code.
// The plan is a token list: `len + 512 * dist` for a match, `pc_run` (dist 0, pc_run <= 511) for a literal
// pc_run. Nothing here is trusted: `pc_emit` re-checks every planned match, so these functions only have to
// be total. Each function keeps its decisions in one place at its end (larger steps are chains of
// small helpers); arithmetic that a guard does not bound wraps.

/// Byte `i` of `s` (0 when out of range).


/// Eight bytes at `i`, first byte most significant (0 unless all eight are in range).


/// Four bytes at `i`, first byte most significant (0 unless all four are in range).


/// The smaller of `a` and `b`.


/// The larger of `a` and `b`.


/// `x >> sh`, and 0 for `sh` >= 32 (the counts shifted here stay below 2^32).


/// Chain slot of the key at `p` (four bytes; three with mask 0xFFFF_FF00).


/// Slot (0..=28) of the length code of `l` in `hist`/`keep` (lengths 3..=258; any `l` is allowed).


/// Slot (32..=61) of the distance code of `d` in `hist`/`keep` (distances 1..=32768; any `d`).


/// How many bytes agree at `a` and `b` (a < b), at most `cap` (search only: any arguments are allowed;
/// the shape of the proven `pc_mlen`, so the word loads compile to one load each).


/// Append `x` (guarded push).


/// Chain position `p` (u16 positions); returns the previous head of its slot (where the search at `p`
/// starts).


/// Chain the positions `from..to` (none when `from >= to`); returns the larger of the two.


/// Is `c` a possible source for `p` (before it and at most 32768 back)?


/// The length of the match at `p` from `c` (at most `cap`) when it beats `best`, else `best`; the byte
/// where it would beat `best` is compared first.


/// Longest match at `p` longer than `have` on the chain from position `start` (at most `depth` steps,
/// within 32768 bytes): (length, distance); distance 0 when none is longer.


/// The longest match `p` allows: min(n - p, 258), 0 at or past the end.


/// The length a match has to beat: `have`, raised to `minl - 1`.


/// Distance 1 at `p` (when `rle` = 1 and the byte before `p` repeats there): (best, bd) of the longer.


/// The previous distance `rep` (> 1) at `p`, when `on`: (best, bd) of the longer.


/// The chain from `ci` (`depth` steps) when `best` is below `cap` and pc_TF_NICE: (best, bd) of the longer.


/// Best match at `p` longer than `have` and at least `minl` long: distance 1, the previous distance
/// `rep`, then the chain from `ci` (each must be longer than the best so far, so on equal length the
/// earlier and cheaper distance stays). (0, 0) when none.


/// Append `pc_run` literals as entries of at most 511.


/// Append `pc_run` literals, then the match (l, d).


/// 1 for a zero byte.


/// 1 for a control byte (below 9, or 14..=31).


/// 1 for a decimal digit.


/// Input kind from at most ~pc_TF_SAMPLE strided bytes: 2 binary (a zero byte, or more than 1/32 control
/// bytes), 1 structured text (at least 1/pc_TF_SDIG digits), 0 other text.


/// Stage-1 settings of kind `cls`: (key mask, shortest match, chain steps, lazy limit, skip shift,
/// distance 1 first).


/// Does a pc_run of four equal bytes start at `p` (the byte before `p` differs)?


/// The first candidate at `p`: none where a pc_run starts (pc_TF_RUNSKIP, distance-1-first kinds; the next
/// position takes distance 1), else `pc_tf_find`.


/// Is the match of length `l` found at `p` taken (at least `minl` long, inside the input)?


/// Estimated saving (1/16 bit) of a match (l, d) over literals: the engine's `pc_gain` (identical for
/// 3 <= l <= 258, 1 <= d <= 32768), with wrapping arithmetic.


/// Does the match (g0, g1) found at `q` (one after the current match's position) beat (l, d)?


/// Lazy steps while the match is shorter than `lazy` and pc_TF_NICE: a better match one position later
/// replaces it (one more pending literal). The state m = [p, l, d, pc_run, ins] is read and written back
/// (a function that changes tables returns no tuple: the proof's `step*` takes flat results).


/// Extend the match (l, d) at `p` backwards over the pending literals (pc_TF_BACK): (p, l, pc_run).


/// Fold the pending match (pl, pd) into the match (l, d) at `p` when no literal is between them, the
/// sum is a legal length and its bytes also match at `d` (pc_TF_FOLD): (p, l, pd).


/// Write the pending match (pl, pd) when there is one (pd != 0) and count its codes.


/// Where the chained tail of a match ending at `end` starts: end - pc_TF_TAIL when that is after `ins`.


/// Chain the positions of a match ending at `end`: pc_TF_INS from `ins` on and the last pc_TF_TAIL (never at
/// or past `lim`); returns the next position to chain (at least `end`).


/// A match (l, d) taken at `p`: lazy steps, backward extension, the pc_fold of the pending match (pl, pd);
/// then the pending match and the literals before the new one are written and the new match's
/// positions chained. Writes o = [end, l, d, ins]: the new match is the pending one now.


/// Positions skipped after `miss` misses in a row (`p` the next position): miss >> skip, at most
/// pc_TF_SKCAP and lim - p, none at `lim`.


/// The literals pending at the end: `pc_run` plus everything from `p` on.


/// The lazy pc_parse proper (lim = n - 8), then the pending match and the literals left at the end.


/// Phase 1a: the lazy pc_parse into `tk` (chains left in `head`/`prev` for the rewrite), length codes
/// counted in hist[0..29], distance codes in hist[32..62].


/// Threshold of slot `c`: `kl` for length codes (c < 32), `kd` for distance codes.


/// 1 when a code used `h` times is kept under threshold `k`.


/// Phase 1b: kept codes (keep[0..29] lengths used at least `kl` times, keep[32..62] distances used at
/// least `kd` times).


/// `x` if it is the first kept length (`kx` and none before), else `kmin`.


/// Is the length `x` (>= 3) of a kept code?


/// `x` when `kx`, else `cur`.


/// lle[x] = the largest length <= x whose code is kept (0 when none); returns the smallest kept length
/// (0 when none).


/// Length code `c`, when kept: the first of two kept lengths summing to `x` whose first piece has code
/// `c` (3 <= each <= 258), else 0.


/// Two kept lengths summing to `x` (3 <= each <= 258): the first one, or 0 when there is none.


/// The largest kept length that leaves at least the smallest one (when rem > kmin + 3), else the
/// largest kept length <= rem (lengths above 258 count as 258).


/// `pc_tf_piece` before its range pc_check.


/// The next piece when `rem` bytes are written in kept lengths (0 when no kept length fits): `rem`
/// when kept, the largest kept length while more than two of them remain, a kept pair, else the
/// largest kept length leaving at least the smallest one.


/// Bytes of `l` that no kept piece would cover (dry pc_run of `pc_tf_split`).


/// Write `l` bytes at distance d as pieces of kept lengths; `pc_run` literals are pending before it;
/// returns the literals pending after it (bytes no piece covers become literals).


/// Re-admit the code of a remainder `r` (>= 3).


/// Re-admit the codes of `l` bytes written as 258-byte pieces and a remainder (when the kept codes
/// would leave bytes uncovered); returns the new smallest kept length.


/// `pc_tf_split` with its state in st (st[0] = pending literals, in and out; st[1] = smallest kept length).


/// Before writing `l` bytes in kept lengths: re-admit their own codes when the kept lengths would leave
/// at least 3 bytes uncovered (st[1] = the new smallest kept length).


/// Distance `d` at `p` when it is in reach and its code is kept: (best, bd) of the longer (<= cap).


/// The chain candidate `c` (before `p`, in reach) when its distance code is kept: (best, bd) of the
/// longer.


/// pc_TF_RDEPTH steps on the chain of `p` for a longer match at a kept distance: (best, bd).


/// The chain step of `pc_tf_refind` (when `chain` = 1).


/// Longest match at `p` (at most `cap` bytes) at a kept distance: the distances `r1`, `r2`, 1, then
/// (when `chain` = 1) the chain of `p` (pc_TF_RDEPTH steps): (length, distance), (0, 0) when none.


/// Remember distance `d` as the most recent one (rd[0..4]).


/// Write the span of `l` bytes at kept distance d: one kept length as is, else kept pieces (re-admitting
/// the span's own codes first when the kept lengths would leave bytes uncovered).


/// What `pc_tf_redo` does with a re-pc_find of length `fl` when `rem` bytes remain (`shift` literal tries
/// left): 0 take it, 1 one literal, 2 the original distance, 3 literals.


/// One step of `pc_tf_redo` (see `pc_tf_act`).


/// The `l` bytes at `p` whose distance code (of d) was dropped: re-found at kept distances (the chain of
/// `p` first, the recent distances, distance 1), after up to pc_TF_SHIFT single literals; else literals when
/// at most pc_TF_DLIT bytes remain, else at distance d with its code re-admitted. Returns the next position.


/// What `pc_tf_rewrite` does with the stage-1 token (l, d) (`room` bytes left): 0 literals, 1 a span at a
/// kept distance, 2 a re-pc_find (the distance code was dropped).


/// Literals for a token that is no match: min(l, room), at least 1.


/// The span of consecutive stage-1 matches at distance `d` from token `k0` on (`l0` bytes so far, at most
/// `room`): (next token, span length).


/// Phase 1c: the plan from the stage-1 tokens under the kept codes. Consecutive matches at one distance
/// are taken as one span and re-split into kept lengths; a match whose distance code was dropped is
/// re-found at a kept distance (its chain, the recent distances, distance 1; after at most pc_TF_SHIFT
/// single literals), else its bytes become literals.


/// Keep thresholds (length codes, distance codes) of kind `cls`.


/// The plan for a tiny input of kind `cls` (`pc_tf_class`).


/// The kind (`pc_tf_class`) of an input that takes the plan + re-verify path: binaries, and text of a kind
/// below pc_TF_TKIND when pc_TF_TEXT = 1, all of at most pc_TF_N bytes; 3 for every other input.


/// Length code (0..28) of a match length (0..511; lengths below 3 map to 0, above 258 to 28).
pub const pc_TF_LSYM: [u8; 512] = [
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
pub const pc_TF_DSYM: [u8; 512] = [
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
pub const pc_TF_LBASE: [u16; 32] = [3, 4, 5, 6, 7, 8, 9, 10, 11, 13, 15, 17, 19, 23, 27, 31, 35, 43, 51, 59, 67, 83, 99, 115, 131, 163, 195, 227, 258, 0, 0, 0];
pub const pc_TF_LTOP: [u16; 32] = [3, 4, 5, 6, 7, 8, 9, 10, 12, 14, 16, 18, 22, 26, 30, 34, 42, 50, 58, 66, 82, 98, 114, 130, 162, 194, 226, 257, 258, 0, 0, 0];

// fastX: a fast, content-adaptive LZ77 parser for the fixed DEFLATE encoder.
//
// * Content class from a small strided byte histogram: DNA-like inputs, prose (letters and
//   spaces, almost no code symbols), other text, high-entropy binaries (with a zero-rich
//   variant) and structured binaries each get their own settings.
// * Search: hash chains keyed by the first 4 bytes (3 for structured binaries), a main q4_walk and
//   a lazy q4_walk, both with a one-byte quick reject; the lazy step compares candidates by an
//   estimated bit saving. Text looks one byte q4_ahead only after short matches, prose walks
//   deeper without looking q4_ahead, structured text walks one step and looks q4_ahead deeply.
// * Every new match first extends backwards over the tokens just written: literals that
//   match at its distance, and whole earlier matches whose bytes also match there, are
//   folded into it (fewer, longer matches). Inside long matches the first q4_INS_MAX, every
//   q4_STRIDE-th and the last q4_TAIL positions are recorded.
// * Skip acceleration through stretches without matches (capped for zero-rich data).
// * Tables are sized by the input: small inputs clear and touch less memory.
// * Emission optionally re-checks each match (q4_VERIFY = 1); a failed q4_check writes a literal.
// * Tiny inputs (at most q4_TF_N bytes; binaries, optionally plain text) take a separate path: a
//   planner (`q4_tf_plan`, search only) that spends few distinct length and distance codes (the
//   encoder's cost per tiny block is mostly per live symbol) writes a plan, and `q4_emit` writes each
//   planned match only after `q4_check` has re-compared its bytes (anything else becomes literals),
//   so only the emission carries the decode invariant.
// * A class whose search is a single chain step (here text, prose, structured text and the
//   zero-rich binaries) is parsed by `q4_run1` instead of `q4_run`: the q4_same tokens, but the head slot,
//   the candidate and the candidate's first eight bytes of the next position are read one step
//   early, so the loads overlap the branches of the current position, and the literals are
//   written in one go when the next match is known (`q4_r1_kind` decides from constants alone).
// * Pair-structured binaries (16-bit floats: one byte of each pair nearly constant) take the
//   stride path `q4_run_st`: only every second position is searched, with 3-byte keys.
// * DNA-like inputs (q4_DN_ON = 1) take `q4_run_dna`: a greedy q4_parse with 3-byte keys whose table keeps the
//   oldest occurrence in the window (far matches, at most q4_DN_CAP bytes long).
//
// Tokens: t < 256 literal, else 2^24 + (dist-1)*256 + (len-3).

pub const q4_HB: u32 = 15;
pub const q4_HN: usize = 32768;
pub const q4_WN: usize = 32768;
/// Inputs of at most q4_SMALL bytes use q4_HS chain heads and a q4_WS window table.
pub const q4_SMALL: usize = 65536;
pub const q4_HS: usize = 4096;
pub const q4_WS: usize = 16384;
pub const q4_NICE: usize = 32;
pub const q4_INS_MAX: usize = 0;
pub const q4_TAIL: usize = 0;
/// Inside long matches, every q4_STRIDE-th position between the head and the tail is chained
/// too (q4_STRIDE = 0: none).
pub const q4_STRIDE: usize = 0;
pub const q4_BACKTOK: usize = 16;
pub const q4_LDEPTH: usize = 1;
pub const q4_SAMPLE: usize = 2048;
pub const q4_VERIFY: usize = 0;
/// Lazy step: a candidate at p+1 needs length >= l + 1 - q4_LSLACK (q4_LSLACK = 1: at least as long
/// as the current match l) and must win on estimated saving (literal worth q4_HLIT/16 bits,
/// match base cost q4_GBASE/16 bits plus extra bits).
pub const q4_LSLACK: usize = 1;
pub const q4_HLIT: u32 = 80;
pub const q4_GBASE: i32 = 168;
/// Per class: main chain depth, lazy threshold, skip shift, skip cap (T text, P prose,
/// H high-entropy binary, Z high-entropy binary rich in zero bytes, B other binary,
/// DNA-like input is sent as literals).
pub const q4_T_DEPTH: usize = 1;
pub const q4_T_LAZY: usize = 0;
pub const q4_T_SKIP: usize = 4;
pub const q4_P_DEPTH: usize = 4;
pub const q4_P_LAZY: usize = 0;
pub const q4_P_SKIP: usize = 5;
/// Key mask of prose searched with one chain step (0xFFFF_FFFF: four-byte keys; 0xFFFF_FF00: three-byte keys).
pub const q4_P_KM: u32 = 4294967295;
pub const q4_H_DEPTH: usize = 1;
pub const q4_H_LAZY: usize = 0;
pub const q4_H_SKIP: usize = 3;
pub const q4_Z_DEPTH: usize = 1;
pub const q4_Z_SKIP: usize = 4;
pub const q4_Z_CAP: usize = 8;
pub const q4_B_DEPTH: usize = 1;
pub const q4_B_LAZY: usize = 0;
pub const q4_B_SKIP: usize = 4;
/// Structured text (class 6: text with at least 1/q4_SDIG of the sample in digits): main depth
/// q4_S_DEPTH, lazy q4_walk depth q4_S_LDEPTH, lazy threshold q4_S_LAZY.
pub const q4_SDIG: u32 = 6;
pub const q4_S_DEPTH: usize = 1;
pub const q4_S_LDEPTH: usize = 1;
pub const q4_S_LAZY: usize = 258;
/// Largest skip step (extra literals per miss) outside the Z class.
pub const q4_SKCAP: usize = 1000000;
/// 1: a class whose search is one chain step (main q4_walk and lazy q4_walk) is parsed by the read-q4_ahead
/// loop `q4_run1` (the q4_same tokens as `q4_run`); 0: `q4_run` for every class.
pub const q4_R1_ON: usize = 1;
/// Stride path (q4_ST_ON 1): a high-entropy input (class 2 or 4) of more than q4_ST_MIN bytes whose bytes
/// at one parity take at most q4_ST_FEW distinct values while the other parity takes at least q4_ST_MANY
/// (in at most q4_ST_SAMPLE sampled byte pairs) is parsed by `q4_run_st`: only the positions of the
/// low-entropy parity are searched, with 3-byte keys in a direct-mapped table of q4_ST_HN slots
/// (2^q4_ST_HB); a match is at most q4_ST_DMAX back.
pub const q4_ST_ON: usize = 1;
pub const q4_ST_MIN: usize = 65536;
pub const q4_ST_SAMPLE: usize = 4096;
pub const q4_ST_FEW: usize = 32;
pub const q4_ST_MANY: usize = 160;
pub const q4_ST_HB: u32 = 17;
pub const q4_ST_HN: usize = 131072;
pub const q4_ST_DMAX: usize = 32768;
/// Stride path: after a match, at most q4_ST_INS positions of the searched parity inside it are recorded in the table
/// (0: none); a candidate less than q4_ST_DMIN back is not taken (129: distance codes 14..29 only, so a block keeps at
/// most 16 live distance codes).
pub const q4_ST_INS: usize = 258;
pub const q4_ST_DMIN: usize = 129;
/// DNA-like inputs (class 0) with q4_DN_ON = 1 are parsed by `q4_run_dna` (else they stay literals): every position is
/// searched with one entry of a direct-mapped table of q4_DN_HN slots (2^q4_DN_HB) keyed by its three bytes; a slot keeps
/// its position while that is at most q4_DN_FAR back (the oldest occurrence in the window, so matches come from far
/// back); a match is at most q4_DN_CAP bytes long.
pub const q4_DN_ON: usize = 0;
pub const q4_DN_HB: u32 = 16;
pub const q4_DN_HN: usize = 65536;
pub const q4_DN_FAR: usize = 32768;
pub const q4_DN_CAP: usize = 3;
/// Tiny inputs (at most q4_TF_N bytes) that `q4_tf_class` calls binary, and with q4_TF_TEXT = 1 also text
/// inputs of a `q4_tf_class` kind below q4_TF_TKIND (0 text, 1 structured text), take the plan +
/// re-verify path (`q4_tf_plan`, then `q4_emit`); every other input takes the engine above. q4_TF_N = 0
/// leaves only the empty input there (no tokens either way): `q4_parse` is then the engine alone.
pub const q4_TF_N: usize = 65536;
pub const q4_TF_TEXT: usize = 0;
pub const q4_TF_TKIND: usize = 1;
/// `q4_tf_class`: about q4_TF_SAMPLE strided bytes (>= 1); structured text has at least 1/q4_TF_SDIG
/// (>= 1) digits.
pub const q4_TF_SAMPLE: usize = 256;
pub const q4_TF_SDIG: u32 = 6;
/// Chain heads (q4_TF_HN = 2^q4_TF_HB slots, 1 <= q4_TF_HB <= 64) and the window table (q4_TF_WN >= 1);
/// positions are kept as u16 (q4_TF_N <= 65536 keeps them exact). Binaries alone (q4_TF_TEXT = 0,
/// q4_TF_BDEPTH = 0) q4_find only distance-1 matches, so the chains never change their plan (a chain
/// candidate can only repeat distance 1, the one kept code): minimal tables skip clearing 72 KB.
/// The text planner (q4_TF_TEXT = 1) walks the chains: q4_TF_HB 12, q4_TF_HN 4096, q4_TF_WN 32768 there.
pub const q4_TF_HB: u32 = 12;
pub const q4_TF_HN: usize = 4096;
pub const q4_TF_WN: usize = 16384;
/// Per kind: chain steps, lazy steps below this match length, skip shift (after m literals in a
/// row, m >> skip positions are not searched; a shift of 32 or more never skips). T text, S
/// structured text, B binaries (3-byte keys; q4_TF_BDEPTH 0 = distance 1 only).
pub const q4_TF_TDEPTH: usize = 1;
pub const q4_TF_TLAZY: usize = 0;
pub const q4_TF_TSKIP: usize = 3;
pub const q4_TF_SDEPTH: usize = 1;
pub const q4_TF_SLAZY: usize = 258;
pub const q4_TF_SSKIP: usize = 3;
pub const q4_TF_BDEPTH: usize = 0;
pub const q4_TF_BLAZY: usize = 0;
pub const q4_TF_BSKIP: usize = 4;
/// A q4_walk stops at a match of q4_TF_NICE bytes; skip steps are at most q4_TF_SKCAP.
pub const q4_TF_NICE: usize = 64;
pub const q4_TF_SKCAP: usize = 1000000;
/// 1: distance 1 is tried before the chain on text too (always on binaries).
pub const q4_TF_TRLE: usize = 1;
/// 1: a new match extends backwards over pending literals; 1: the pending match is folded into
/// a new one when its bytes also match at the new distance.
pub const q4_TF_BACK: usize = 1;
pub const q4_TF_FOLD: usize = 1;
/// The previous match distance is tried before the chain (1), after it (2) or not at all (0).
pub const q4_TF_REP: usize = 0;
/// 1: no search where a q4_run of four equal bytes starts (the next position takes distance 1).
pub const q4_TF_RUNSKIP: usize = 1;
/// Positions chained at the head and at the tail of a match.
pub const q4_TF_INS: usize = 2;
pub const q4_TF_TAIL: usize = 1;
/// Keep thresholds (uses per code): text q4_TF_KL / q4_TF_KD, binaries q4_TF_BKL / q4_TF_BKD (0 or 1: keep
/// every code used).
pub const q4_TF_KL: u32 = 5;
pub const q4_TF_KD: u32 = 5;
pub const q4_TF_BKL: u32 = 3;
pub const q4_TF_BKD: u32 = 3;
/// Re-q4_find: chain steps, single literals tried before giving up; a dropped-distance match that
/// cannot be re-found becomes literals when at most q4_TF_DLIT bytes long, else keeps its distance
/// (its code re-admitted).
pub const q4_TF_RDEPTH: usize = 8;
pub const q4_TF_SHIFT: usize = 1;
pub const q4_TF_DLIT: usize = 8;

/// Eight bytes at `i`, first byte most significant (0 when out of range).
#[inline(always)]
pub fn q4_be8(s: &[u8], i: usize) -> u64 {
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
pub fn q4_be4(s: &[u8], i: usize) -> u32 {
    if i + 4 <= s.len() {
        ((s[i] as u32) << 24) | ((s[i + 1] as u32) << 16) | ((s[i + 2] as u32) << 8) | (s[i + 3] as u32)
    } else {
        0
    }
}

/// Input class from a strided byte histogram of at most ~q4_SAMPLE bytes:
/// 0 DNA-like, 1 text, 2 high-entropy binary, 3 other binary, 4 high-entropy with zeros,
/// 5 prose (text of letters and spaces with almost no code symbols), 6 structured text (many
/// digits: tables, logs, dumps).


/// Estimated saving (1/16 bit) of a match of length `l` at distance `d` over literals.
#[inline(always)]
pub fn q4_gain(l: usize, d: usize) -> i32 {
    let mut c = q4_GBASE;
    if l > 10 && l < 258 {
        c += 16 * (29 - ((l - 3) as u32).leading_zeros()) as i32;
    }
    if d > 4 {
        c += 16 * (30 - ((d - 1) as u32).leading_zeros()) as i32;
    }
    (l as i32) * (q4_HLIT as i32) - c
}

/// Length of the q4_common prefix of s[a..] and s[b..], at most `cap`.


/// 1 when s[a..a+len] == s[b..b+len]: eight bytes at a time, the last partial word
/// under a mask when a full load fits, else byte by byte.
#[inline(always)]
pub fn q4_same(s: &[u8], a: usize, b: usize, len: usize) -> usize {
    let n = s.len();
    let mut k = 0usize;
    let mut ok = 1usize;
    while ok == 1 && k + 8 <= len {
        if q4_be8(s, a + k) == q4_be8(s, b + k) {
            k += 8;
        } else {
            ok = 0;
        }
    }
    if ok == 1 && k < len {
        if a + k + 8 <= n && b + k + 8 <= n {
            let x = q4_be8(s, a + k) ^ q4_be8(s, b + k);
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
pub fn q4_put_lit(s: &[u8], out: &mut [u32], nt: usize, p: usize) -> usize {
    out[nt] = s[p] as u32;
    nt + 1
}

/// Emit a match (re-checked when q4_VERIFY = 1), else a literal. Returns (tokens, next position).
#[inline(always)]
pub fn q4_put_match(s: &[u8], out: &mut [u32], nt: usize, p: usize, d: usize, l: usize) -> (usize, usize) {
    let n = s.len();
    if d >= 1 && d <= 32768 && d <= p && l >= 3 && l <= 258 && p < n && l <= n - p && (q4_VERIFY == 0 || q4_same(s, p - d, p, l) == 1) {
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


/// Put position `i` at the head of its chain (key = first four bytes under `mask`);
/// returns the previous head.


/// Best match at `p` longer than `have` and at least `minl` long; (0, 0) when none.


/// The q4_parse for one input class (inlined so the text classes get constant settings), with
/// H chain heads and a window table of W entries.


// ─────────────── the stride path: pair-structured binaries (16-bit floats and the like) ───────────────

/// Parity of the low-entropy bytes of pair-structured data (0 even, 1 odd), or 2 when the input is
/// not such data: in at most q4_ST_SAMPLE sampled byte pairs one parity takes at most q4_ST_FEW distinct
/// values and the other at least q4_ST_MANY.


/// The stride path's parity for an input of class `cls` that takes it (0 or 1), else 2.


/// Table slot of the three bytes at `p` (low-entropy, other, low-entropy).


/// Put position `p` in slot `a` of the stride table; returns the position it replaces.


/// The match at `p` from the table entry `c`: (length, distance) when `c` is at most q4_ST_DMAX before
/// `p` and the three key bytes agree (compared one by one, then extended byte by byte), else (0, 0).


/// Record position `q` in its slot of the stride table.


/// Record the positions of parity `ph` in `from..end` (at most q4_ST_INS of them, all below `lim`) in the stride table.


/// Stride-2 greedy q4_parse: only positions of parity `ph` are searched; the table keeps the most
/// recent position per key slot (searched positions and, through `q4_st_fill`, those inside matches); a failed search writes the pair (p, p + 1) as literals, and a
/// match that ends on the other parity is followed by one literal.


// ─────────────── DNA-like inputs (class 0): greedy, far table, three-byte keys ───────────────

/// Table slot of the three bytes at `p`.
#[inline(always)]
pub fn q4_dn_slot(s: &[u8], p: usize) -> usize {
    let k = ((s[p] as u64) << 16) | ((s[p + 1] as u64) << 8) | (s[p + 2] as u64);
    (k.wrapping_mul(0x9E37_79B9_7F4A_7C15) >> (64 - q4_DN_HB)) as usize % q4_DN_HN
}

/// The entry of slot `a`; the slot takes `p` only when its entry is more than q4_DN_FAR back.
#[inline(always)]
pub fn q4_dn_swap(tab: &mut [u32; q4_DN_HN], a: usize, p: usize) -> usize {
    let c = tab[a] as usize;
    if p.wrapping_sub(c) > q4_DN_FAR {
        tab[a] = p as u32;
    }
    c
}

/// The match at `p` from the entry `c`: (length, distance) when `c` is before `p`, at most 32768 back, and the
/// three key bytes agree (compared one by one, then extended byte by byte up to q4_DN_CAP), else (0, 0).
#[inline(always)]
pub fn q4_dn_find(s: &[u8], c: usize, p: usize) -> (usize, usize) {
    let n = s.len();
    if c < p && p - c <= 32768 && s[c] == s[p] && s[c + 1] == s[p + 1] && s[c + 2] == s[p + 2] {
        let mut cap = n - p;
        if cap > q4_DN_CAP {
            cap = q4_DN_CAP;
        }
        let mut l = 3usize;
        while l < cap && s[c + l] == s[p + l] {
            l += 1;
        }
        (l, p - c)
    } else {
        (0, 0)
    }
}

/// Greedy q4_parse for DNA-like inputs: every position is searched with its table entry.
#[inline(never)]
pub fn q4_run_dna(input: &[u8], out: &mut [u32]) -> usize {
    let n = input.len();
    let mut nt = 0usize;
    let mut p = 0usize;
    if n > 16 {
        let mut tab = [0u32; q4_DN_HN];
        let lim = n - 8;
        while p < lim {
            let a = q4_dn_slot(input, p);
            let c = q4_dn_swap(&mut tab, a, p);
            let f = q4_dn_find(input, c, p);
            if f.0 >= 3 {
                let r = q4_put_match(input, out, nt, p, f.1, f.0);
                nt = r.0;
                p = r.1;
            } else {
                nt = q4_put_lit(input, out, nt, p);
                p += 1;
            }
        }
    }
    while p < n {
        nt = q4_put_lit(input, out, nt, p);
        p += 1;
    }
    nt
}

// ─────────────── E: symbol-frugal paths for one-block inputs, and dispatch helpers ───────────────
//
// The validator encoder builds Huffman codes per block of 16384 tokens; package-merge costs about 1 us per live
// literal/length or distance symbol, so a one-block input is encoded mostly at that per-symbol price. These paths
// spend few distinct length codes there:
//  * `q4_run1t` (small text inputs, at most q4_TM_MAX bytes): `q4_run1` whose matches are written as pieces whose lengths
//    have a code in q4_TM_LM (a match is split at its distance; a rest that no allowed length fits is written as literals).
//  * `q4_run_z` (tiny binaries): each byte, then the q4_run of the q4_same byte after it as distance-1 pieces whose lengths
//    have a code in q4_TZ_LM (a rest that no allowed length fits is written as literals).
/// Inputs of a text class of at most q4_TM_MAX bytes take `q4_run1t` (needs q4_TF_TEXT = 0 for the ones at most q4_TF_N).
pub const q4_TM_ON: usize = 1;
pub const q4_TM_MAX: usize = 65536;
/// Allowed length codes (bit c = length code 257 + c): 12, 18, 25, 28 = lengths 19-22, 51-58, 163-194, 258.
pub const q4_TM_LM: u32 = 302_256_128;
/// Lazy threshold and backward-merge depth of `q4_run1t`.
pub const q4_TM_LAZY: usize = 258;
pub const q4_TM_BACK: usize = 16;
/// Tiny binaries (`q4_tf_class` kind 2) take `q4_run_z` when q4_TZ_ON = 1; allowed length codes q4_TZ_LM.
pub const q4_TZ_ON: usize = 1;
pub const q4_TZ_LM: u32 = 302_256_128;

/// lens[x] = the largest length <= x whose code (q4_TF_LSYM) has its bit set in `m` (0 when none), x in 3..=258.
#[inline(always)]
pub fn q4_e_lens(lens: &mut [u16; 260], m: u32) {
    let mut cur = 0u16;
    let mut x = 3usize;
    while x < 259 {
        let c = (q4_TF_LSYM[x] as u32) % 32;
        if (m >> c) % 2 == 1 {
            cur = x as u16;
        }
        lens[x] = cur;
        x += 1;
    }
}

/// The allowed piece for `rem` bytes left: lens[min(rem, 258)] when it is at least 3 and at most `rem`, else 0.
#[inline(always)]
pub fn q4_e_piece(lens: &[u16; 260], rem: usize) -> usize {
    let mut r = rem;
    if r > 258 {
        r = 258;
    }
    let x = lens[r] as usize;
    if x >= 3 && x <= rem {
        x
    } else {
        0
    }
}

/// `q4_fold` with its own depth `bt`.
#[inline(always)]
pub fn q4_fold_bt(input: &[u8], out: &[u32], nt0: usize, p0: usize, l0: usize, d: usize, bt: usize) -> (usize, usize, usize) {
    let mut nt = nt0;
    let mut p = p0;
    let mut l = l0;
    let mut back = 0usize;
    while back < bt && nt > 0 && nt <= out.len() && l < 258 && d < p {
        let t = out[nt - 1];
        if t < 256 && input[p - 1] == input[p - 1 - d] {
            p -= 1;
            nt -= 1;
            l += 1;
            back += 1;
        } else if t >= 16777216 {
            let w = ((t - 16777216) % 256 + 3) as usize;
            if l + w <= 258 && w <= p && d <= p - w && q4_same(input, p - w - d, p - w, w) == 1 {
                p -= w;
                nt -= 1;
                l += w;
                back += 1;
            } else {
                back = bt;
            }
        } else {
            back = bt;
        }
    }
    (nt, p, l)
}

/// Write the match (l, d) at `p` as pieces of allowed lengths, then the rest as literals. Returns (tokens, end).
#[inline(always)]
pub fn q4_e_pieces(input: &[u8], out: &mut [u32], nt0: usize, p: usize, l: usize, d: usize, lens: &[u16; 260]) -> (usize, usize) {
    let n = input.len();
    let mut nt = nt0;
    let mut q = p;
    let mut end = p + l;
    if end > n {
        end = n;
    }
    let mut go = 1u32;
    while go == 1 && q < end {
        let x = q4_e_piece(lens, end - q);
        if x >= 3 {
            let r = q4_put_match(input, out, nt, q, d, x);
            nt = r.0;
            q = r.1;
        } else {
            go = 0;
        }
    }
    while q < end {
        nt = q4_put_lit(input, out, nt, q);
        q += 1;
    }
    (nt, q)
}

/// `q4_run1` for small text inputs with the length codes limited to `lm` (see the section head).
#[inline(never)]
pub fn q4_run1t<const H: usize>(input: &[u8], out: &mut [u32], skip: usize, lazy: usize, skcap: usize, lm: u32) -> usize {
    let n = input.len();
    let mut lens = [0u16; 260];
    q4_e_lens(&mut lens, lm);
    let mut nt = 0usize;
    let mut ls = 0usize;
    if n > 16 {
        let mut p = 0usize;
        let mut head = [0u32; H];
        let lim = n - 8;
        let mut miss = 0usize;
        let mut fuel = n.saturating_add(16);
        let a0 = q4_ahead::<H>(input, &head, 0);
        let mut pre_slot = a0.0;
        let mut pre_c = a0.1;
        let mut pre_w = a0.2;
        while p < lim && fuel > 0 {
            fuel -= 1;
            let c = pre_c;
            let cw = pre_w;
            q4_head_set(&mut head, pre_slot, p);
            let a1 = q4_ahead_if::<H>(input, &head, p + 1, lim, pre_slot, pre_c, pre_w);
            pre_slot = a1.0;
            pre_c = a1.1;
            pre_w = a1.2;
            let f = q4_probe(input, c, cw, p);
            if f.0 >= 3 {
                let mut l = f.0;
                let mut d = f.1;
                let mut ins = p + 1;
                let mut go = 1u32;
                while go == 1 && l < lazy && p + 1 < lim {
                    let q = p + 1;
                    let c2 = pre_c;
                    let w2 = pre_w;
                    q4_head_set(&mut head, pre_slot, q);
                    ins = q + 1;
                    let a2 = q4_ahead_if::<H>(input, &head, q + 1, lim, pre_slot, pre_c, pre_w);
                    pre_slot = a2.0;
                    pre_c = a2.1;
                    pre_w = a2.2;
                    let g = q4_probe_lazy(input, c2, w2, q, l);
                    if g.0 >= 4 && q4_gain(g.0, g.1) > q4_gain(l, d) {
                        p = q;
                        l = g.0;
                        d = g.1;
                    } else {
                        go = 0;
                    }
                }
                nt = q4_flush(input, out, nt, ls, p);
                let b = q4_fold_bt(input, out, nt, p, l, d, q4_TM_BACK);
                let r = q4_e_pieces(input, out, b.0, b.1, b.2, d, &lens);
                nt = r.0;
                let end = r.1;
                q4_record::<H>(input, &mut head, ins, end, lim);
                p = end;
                ls = end;
                miss = 0;
                let a3 = q4_ahead_if::<H>(input, &head, p, lim, pre_slot, pre_c, pre_w);
                pre_slot = a3.0;
                pre_c = a3.1;
                pre_w = a3.2;
            } else {
                p += 1;
                miss += 1;
                let step = q4_skip_len(miss, skip, skcap);
                if step > 0 {
                    p = q4_skip_to(p, step, lim);
                    let a4 = q4_ahead_if::<H>(input, &head, p, lim, pre_slot, pre_c, pre_w);
                    pre_slot = a4.0;
                    pre_c = a4.1;
                    pre_w = a4.2;
                }
            }
        }
    }
    while ls < n {
        nt = q4_put_lit(input, out, nt, ls);
        ls += 1;
    }
    nt
}

/// Tiny binaries: each byte, then the bytes after it that repeat it (the distance-1 match `q4_mlen` confirms) as
/// pieces of allowed lengths; a rest that no allowed length fits is written as literals.


/// Which E path `q4_parse` gives an input of length `n` and class `cls` (0: the engine's own choice; 1: q4_run1t).
/// Single-condition `if`s only (no short-circuit chains).


// ─────────────── the read-q4_ahead loop for classes searched with one chain step ───────────────

/// Slot of position `i` in a head table of H entries (the slot `q4_insert` uses for 4-byte keys).
#[inline(always)]
pub fn q4_slot_of<const H: usize>(s: &[u8], i: usize) -> usize {
    let k = q4_be4(s, i) as u64;
    (k.wrapping_mul(0x9E37_79B9_7F4A_7C15) >> (64 - q4_HB)) as usize % H
}

/// Record position `i` in slot `a`.
#[inline(always)]
pub fn q4_head_set<const H: usize>(head: &mut [u32; H], a: usize, i: usize) {
    head[a] = i as u32;
}

/// What the search at position `i` will need, read before it gets there: its slot, the head entry
/// there (the candidate) and the candidate's first eight bytes.
#[inline(always)]
pub fn q4_ahead<const H: usize>(s: &[u8], head: &[u32; H], i: usize) -> (usize, usize, u64) {
    let a = q4_slot_of::<H>(s, i);
    let c = head[a] as usize;
    (a, c, q4_be8(s, c))
}

/// `q4_ahead` for position `i` when it is below `lim` (it will be searched), else the values given.
/// (The test also keeps these loads apart from the eight-byte load of the search at `i - 1`,
/// which shares bytes with them: each stays a single load.)
#[inline(always)]
pub fn q4_ahead_if<const H: usize>(s: &[u8], head: &[u32; H], i: usize, lim: usize, a: usize, c: usize, w: u64) -> (usize, usize, u64) {
    if i < lim {
        q4_ahead::<H>(s, head, i)
    } else {
        (a, c, w)
    }
}

/// `q4_common` continued after `k0` bytes already known to agree.
#[inline(always)]
pub fn q4_common_from(s: &[u8], a: usize, b: usize, cap: usize, k0: usize) -> usize {
    let mut k = k0;
    let mut q4_run = 1u32;
    while q4_run == 1 && k + 8 <= cap {
        let x = q4_xor8(s, a.wrapping_add(k), b.wrapping_add(k));
        if x == 0 {
            k += 8;
        } else {
            k += (x.leading_zeros() / 8) as usize;
            q4_run = 0;
        }
    }
    while q4_run == 1 && k < cap {
        if s[a + k] == s[b + k] {
            k += 1;
        } else {
            q4_run = 0;
        }
    }
    k
}

/// How many bytes agree at `c` and `p`, given the xor `x` of their first eight bytes taken as
/// words: the leading zero bytes of `x`, or what `q4_common_from` finds past eight equal bytes.
#[inline(always)]
pub fn q4_xlen(s: &[u8], c: usize, p: usize, x: u64) -> usize {
    if x != 0 {
        (x.leading_zeros() / 8) as usize
    } else {
        let mut cap = s.len() - p;
        if cap > 258 {
            cap = 258;
        }
        q4_common_from(s, c, p, cap, 8)
    }
}

/// The xor of the eight-byte big-endian words at `a` and `b` (0 when either is out of range): both or-trees in one
/// block, so each stays a single load.
#[inline(always)]
pub fn q4_xor8(s: &[u8], a: usize, b: usize) -> u64 {
    let n = s.len();
    if n >= 8 && a <= n - 8 && b <= n - 8 {
        let x = ((s[a] as u64) << 56)
            | ((s[a + 1] as u64) << 48)
            | ((s[a + 2] as u64) << 40)
            | ((s[a + 3] as u64) << 32)
            | ((s[a + 4] as u64) << 24)
            | ((s[a + 5] as u64) << 16)
            | ((s[a + 6] as u64) << 8)
            | (s[a + 7] as u64);
        let y = ((s[b] as u64) << 56)
            | ((s[b + 1] as u64) << 48)
            | ((s[b + 2] as u64) << 40)
            | ((s[b + 3] as u64) << 32)
            | ((s[b + 4] as u64) << 24)
            | ((s[b + 5] as u64) << 16)
            | ((s[b + 6] as u64) << 8)
            | (s[b + 7] as u64);
        x ^ y
    } else {
        0
    }
}

/// `q4_xlen` reading sixteen bytes with one branch: l1 = leading zero bytes of `x` (4..=8); when l1 is 8 the leading zero
/// bytes of the next words' xor are added (`l1 >> 3` is 1 exactly then); `q4_common_from` continues only past sixteen
/// equal bytes. Inputs with fewer than sixteen bytes left at `p` take `q4_xlen`.
#[inline(always)]
pub fn q4_xlen16(s: &[u8], c: usize, p: usize, x: u64) -> usize {
    let n = s.len();
    if n >= 16 && p <= n - 16 && c < p {
        let x2 = q4_xor8(s, c + 8, p + 8);
        let mut y = x;
        let mut k = 0usize;
        if x == 0 {
            y = x2;
            k = 8;
        }
        let l = k + (y.leading_zeros() / 8) as usize;
        if l >= 16 {
            let mut cap = n - p;
            if cap > 258 {
                cap = 258;
            }
            q4_common_from(s, c, p, cap, 16)
        } else {
            l
        }
    } else {
        q4_xlen(s, c, p, x)
    }
}

/// The match at `p` from the candidate `c` whose first eight bytes are the word `cw`: (length,
/// distance) when at least four bytes agree at a distance in 1..=32768, else (0, 0). One xor of
/// the two words decides.
#[inline(always)]
pub fn q4_probe(s: &[u8], c: usize, cw: u64, p: usize) -> (usize, usize) {
    let d = p.wrapping_sub(c);
    let x = cw ^ q4_be8(s, p);
    if d.wrapping_sub(1) < 32768 && (x >> 32) == 0 {
        (q4_xlen16(s, c, p, x), d)
    } else {
        (0, 0)
    }
}

/// The length a match at the lazy position has to beat after a match of length `l`:
/// max(3, l - q4_LSLACK).
#[inline(always)]
pub fn q4_lazy_lo(l: usize) -> usize {
    if l > q4_LSLACK && l - q4_LSLACK > 3 {
        l - q4_LSLACK
    } else {
        3
    }
}

/// `q4_probe` for the lazy step at `q`, one after a match of length `l`: only a match longer than
/// `q4_lazy_lo(l)` counts, and the byte at that offset is compared first.
#[inline(always)]
pub fn q4_probe_lazy(s: &[u8], c: usize, cw: u64, q: usize, l: usize) -> (usize, usize) {
    let n = s.len();
    let lo = q4_lazy_lo(l);
    let d = q.wrapping_sub(c);
    let x = cw ^ q4_be8(s, q);
    if d.wrapping_sub(1) < 32768 && (x >> 32) == 0 && q + lo < n && s[c + lo] == s[q + lo] {
        let m = q4_xlen16(s, c, q, x);
        if m > lo {
            (m, d)
        } else {
            (0, 0)
        }
    } else {
        (0, 0)
    }
}

/// Literals skipped without a search after `miss` misses in a row: min(miss >> skip, skcap).
#[inline(always)]
pub fn q4_skip_len(miss: usize, skip: usize, skcap: usize) -> usize {
    let step = miss >> skip;
    if step > skcap {
        skcap
    } else {
        step
    }
}

/// `p` moved on by `step` positions, at most to `lim` (needs p <= lim).
#[inline(always)]
pub fn q4_skip_to(p: usize, step: usize, lim: usize) -> usize {
    if step > lim - p {
        lim
    } else {
        p + step
    }
}

/// Write the literals of the positions `from..to` (the ones passed since the last match).
#[inline(always)]
pub fn q4_flush(input: &[u8], out: &mut [u32], nt0: usize, from: usize, to: usize) -> usize {
    let mut nt = nt0;
    let mut j = from;
    while j < to {
        nt = q4_put_lit(input, out, nt, j);
        j += 1;
    }
    nt
}

/// The backward merge of `q4_run` for the match (l0, d) at `p0`: earlier tokens whose bytes also match
/// at distance `d` are folded into it. Returns (tokens kept, start, length).
#[inline(always)]
pub fn q4_fold(input: &[u8], out: &[u32], nt0: usize, p0: usize, l0: usize, d: usize) -> (usize, usize, usize) {
    let mut nt = nt0;
    let mut p = p0;
    let mut l = l0;
    let mut back = 0usize;
    while back < q4_BACKTOK && nt > 0 && nt <= out.len() && l < 258 && d < p {
        let t = out[nt - 1];
        if t < 256 && input[p - 1] == input[p - 1 - d] {
            p -= 1;
            nt -= 1;
            l += 1;
            back += 1;
        } else if t >= 16777216 {
            let w = ((t - 16777216) % 256 + 3) as usize;
            if l + w <= 258 && w <= p && d <= p - w && q4_same(input, p - w - d, p - w, w) == 1 {
                p -= w;
                nt -= 1;
                l += w;
                back += 1;
            } else {
                back = q4_BACKTOK;
            }
        } else {
            back = q4_BACKTOK;
        }
    }
    (nt, p, l)
}

/// Record, as `q4_run` does, the first q4_INS_MAX and the last q4_TAIL positions inside the match that
/// ends at `end`, starting at `ins0` (positions from `lim` on have no full key).
#[inline(always)]
pub fn q4_record<const H: usize>(s: &[u8], head: &mut [u32; H], ins0: usize, end: usize, lim: usize) {
    let mut ins = ins0;
    let mut stop = end;
    // wrapping: q4_same code as `+` here (no overflow on any real input), total in the model
    if stop > ins.wrapping_add(q4_INS_MAX) {
        stop = ins.wrapping_add(q4_INS_MAX);
    }
    if stop > lim {
        stop = lim;
    }
    while ins < stop {
        let a = q4_slot_of::<H>(s, ins);
        q4_head_set(head, a, ins);
        ins += 1;
    }
    if ins + q4_TAIL < end {
        ins = end - q4_TAIL;
    }
    while ins < end && ins < lim {
        let a = q4_slot_of::<H>(s, ins);
        q4_head_set(head, a, ins);
        ins += 1;
    }
}

/// `q4_fold` after a word test: the token before the match (a literal, or a match of `w` bytes) can be folded into it
/// only if its last byte (literal) or its last min(w, 8) bytes (match) agree at distance `d`; one xor of the eight
/// bytes before `p0` and before `p0 - d` tests that, and when it fails the inputs come back unchanged (`q4_fold` would
/// stop at its first token).
#[inline(always)]
pub fn q4_fold_w(input: &[u8], out: &[u32], nt0: usize, p0: usize, l0: usize, d: usize) -> (usize, usize, usize) {
    let mut m = 1u32;
    if nt0 > 0 && nt0 <= out.len() {
        let t = out[nt0 - 1];
        if t >= 16777216 {
            m = (t - 16777216) % 256 + 3;
            if m > 8 {
                m = 8;
            }
        }
    }
    let mut x = 1u64;
    if d < p0 && p0 - d >= 8 && p0 <= input.len() {
        x = (q4_be8(input, p0 - 8) ^ q4_be8(input, p0 - 8 - d)) & (18446744073709551615u64 >> (64 - 8 * m));
    }
    if x != 0 && d < p0 && p0 - d >= 8 {
        (nt0, p0, l0)
    } else {
        q4_fold(input, out, nt0, p0, l0, d)
    }
}

/// `q4_flush` writing four literals without a loop when at most four are due and four fit (the ones past `to` are
/// overwritten by the next tokens); the loop otherwise.
#[inline(always)]
pub fn q4_flush4(input: &[u8], out: &mut [u32], nt0: usize, from: usize, to: usize) -> usize {
    if from <= to && to - from <= 4 && from + 4 <= input.len() && nt0 + 4 <= out.len() {
        out[nt0] = input[from] as u32;
        out[nt0 + 1] = input[from + 1] as u32;
        out[nt0 + 2] = input[from + 2] as u32;
        out[nt0 + 3] = input[from + 3] as u32;
        nt0 + (to - from)
    } else {
        q4_flush(input, out, nt0, from, to)
    }
}

/// Slot of position `i` for keys of the bytes `km` keeps of the first four (km = 0xFFFF_FFFF: four bytes, the slot
/// `q4_slot_of` gives; 0xFFFF_FF00: three bytes, the slot `q4_insert` gives class 3).
#[inline(always)]
pub fn q4_slot_of_m<const H: usize>(s: &[u8], i: usize, km: u32) -> usize {
    let k = (q4_be4(s, i) & km) as u64;
    (k.wrapping_mul(0x9E37_79B9_7F4A_7C15) >> (64 - q4_HB)) as usize % H
}

/// `q4_ahead` with keys under `km`.
#[inline(always)]
pub fn q4_ahead_m<const H: usize>(s: &[u8], head: &[u32; H], i: usize, km: u32) -> (usize, usize, u64) {
    let a = q4_slot_of_m::<H>(s, i, km);
    let c = head[a] as usize;
    (a, c, q4_be8(s, c))
}

/// `q4_ahead_if` with keys under `km`.
#[inline(always)]
pub fn q4_ahead_if_m<const H: usize>(s: &[u8], head: &[u32; H], i: usize, lim: usize, a: usize, c: usize, w: u64, km: u32) -> (usize, usize, u64) {
    if i < lim {
        q4_ahead_m::<H>(s, head, i, km)
    } else {
        (a, c, w)
    }
}

/// `ahead_fix` with keys under `km`.
#[inline(always)]
pub fn q4_ahead_fix_m<const H: usize>(s: &[u8], head: &[u32; H], i: usize, lim: usize, e: usize, a: usize, c: usize, w: u64, a0: usize, c0: usize, w0: u64, km: u32) -> (usize, usize, u64) {
    if i == e && i < lim && a < H && head[a] as usize == c {
        (a, c, w)
    } else {
        q4_ahead_if_m::<H>(s, head, i, lim, a0, c0, w0, km)
    }
}

/// `q4_probe` for keys under `km`: a match needs the key bytes to agree (four, or three for km = 0xFFFF_FF00).
#[inline(always)]
pub fn q4_probe_m(s: &[u8], c: usize, cw: u64, p: usize, km: u32) -> (usize, usize) {
    let d = p.wrapping_sub(c);
    let x = cw ^ q4_be8(s, p);
    if d.wrapping_sub(1) < 32768 && ((x >> 32) & (km as u64)) == 0 {
        (q4_xlen16(s, c, p, x), d)
    } else {
        (0, 0)
    }
}

/// `record3` with keys under `km`.
#[inline(always)]
pub fn q4_record3_m<const H: usize>(s: &[u8], head: &mut [u32; H], ins0: usize, a0: usize, end: usize, lim: usize, km: u32) {
    let mut ins = ins0;
    let mut stop = end;
    // wrapping: q4_same code as `+` here (no overflow on any real input), total in the model
    if stop > ins.wrapping_add(q4_INS_MAX) {
        stop = ins.wrapping_add(q4_INS_MAX);
    }
    if stop > lim {
        stop = lim;
    }
    if ins < stop && a0 < H {
        q4_head_set(head, a0, ins);
        ins += 1;
    }
    while ins < stop {
        let a = q4_slot_of_m::<H>(s, ins, km);
        q4_head_set(head, a, ins);
        ins += 1;
    }
    if q4_TAIL == 1 {
        if ins + 1 < end {
            ins = end - 1;
        }
        if ins < end && ins < lim {
            let a = q4_slot_of_m::<H>(s, ins, km);
            q4_head_set(head, a, ins);
        }
    } else {
        if ins + q4_TAIL < end {
            ins = end - q4_TAIL;
        }
        while ins < end && ins < lim {
            let a = q4_slot_of_m::<H>(s, ins, km);
            q4_head_set(head, a, ins);
            ins += 1;
        }
    }
}

/// `q4_run` for a class searched with one chain step (4-byte keys; main q4_walk and lazy q4_walk): the q4_same
/// tokens, without the window table, and with the search state of the next position (`q4_ahead`: its
/// slot, its candidate and the candidate's first eight bytes) read one step early, before the
/// branches of the current position are decided. `pre_slot`, `pre_c`, `pre_w` always describe the
/// position searched next: `p` at the top of the loop, `p + 1` once `p` is recorded (`q4_ahead_if`
/// leaves them alone when that position is past the last one searched).
/// The literals are not written while scanning: `ls` is the start of the positions passed since
/// the last match, and `q4_flush` writes them when the next match is known (or at the end), so the
/// scan itself only loads: the word at `p`, the head entry and the candidate's word.
#[inline(always)]
pub fn q4_run1<const H: usize>(input: &[u8], out: &mut [u32], skip: usize, lazy: usize, skcap: usize, km: u32) -> usize {
    let n = input.len();
    let mut nt = 0usize;
    let mut ls = 0usize; // first position whose literal is not written yet
    if n > 16 {
        let mut p = 0usize;
        let mut head = [0u32; H];
        let lim = n - 8;
        let mut miss = 0usize; // literals since the last match
        let mut fuel = n.saturating_add(16);
        let a0 = q4_ahead_m::<H>(input, &head, 0, km);
        let mut pre_slot = a0.0;
        let mut pre_c = a0.1;
        let mut pre_w = a0.2;
        while p < lim && fuel > 0 {
            fuel -= 1;
            let c = pre_c;
            let cw = pre_w;
            q4_head_set(&mut head, pre_slot, p);
            let a1 = q4_ahead_if_m::<H>(input, &head, p + 1, lim, pre_slot, pre_c, pre_w, km);
            pre_slot = a1.0;
            pre_c = a1.1;
            pre_w = a1.2;
            let f = q4_probe_m(input, c, cw, p, km);
            if f.0 >= 3 {
                let mut l = f.0;
                let mut d = f.1;
                let mut ins = p + 1;
                // Lazy: move on while the next position has a better match by the saving estimate.
                let mut go = 1u32;
                while go == 1 && l < lazy && p + 1 < lim {
                    let q = p + 1;
                    let c2 = pre_c;
                    let w2 = pre_w;
                    q4_head_set(&mut head, pre_slot, q);
                    ins = q + 1;
                    let a2 = q4_ahead_if_m::<H>(input, &head, q + 1, lim, pre_slot, pre_c, pre_w, km);
                    pre_slot = a2.0;
                    pre_c = a2.1;
                    pre_w = a2.2;
                    let g = q4_probe_lazy(input, c2, w2, q, l);
                    if g.0 >= 4 && q4_gain(g.0, g.1) > q4_gain(l, d) {
                        p = q;
                        l = g.0;
                        d = g.1;
                    } else {
                        go = 0;
                    }
                }
                let e = p + l;
                let ae = q4_ahead_if_m::<H>(input, &head, e, lim, pre_slot, pre_c, pre_w, km);
                nt = q4_flush4(input, out, nt, ls, p);
                let b = q4_fold_w(input, out, nt, p, l, d);
                let r = q4_put_match(input, out, b.0, b.1, d, b.2);
                nt = r.0;
                let end = r.1;
                q4_record3_m::<H>(input, &mut head, ins, pre_slot, end, lim, km);
                p = end;
                ls = end;
                miss = 0;
                let a3 = q4_ahead_fix_m::<H>(input, &head, p, lim, e, ae.0, ae.1, ae.2, pre_slot, pre_c, pre_w, km);
                pre_slot = a3.0;
                pre_c = a3.1;
                pre_w = a3.2;
            } else {
                p += 1;
                miss += 1;
                let step = q4_skip_len(miss, skip, skcap);
                if step > 0 {
                    p = q4_skip_to(p, step, lim);
                    let a4 = q4_ahead_if_m::<H>(input, &head, p, lim, pre_slot, pre_c, pre_w, km);
                    pre_slot = a4.0;
                    pre_c = a4.1;
                    pre_w = a4.2;
                }
            }
        }
    }
    while ls < n {
        nt = q4_put_lit(input, out, nt, ls);
        ls += 1;
    }
    nt
}


/// The class itself when `q4_parse` gives class `cls` to `q4_run1` (q4_R1_ON, no stride recording, and one
/// chain step for both walks of the class), else 0. Constant conditions only: any other constant
/// set leaves the class with `q4_run`.


/// Every input except larger text and prose: smaller tables for small inputs.


/// Inputs that `q4_tf_route` sends to the tiny path: plan, then q4_emit with re-verification; all others:
/// the engine (the stride path for pair-structured binaries, `q4_run1` for the classes `q4_r1_kind`
/// names, `q4_run` for the rest).


// ─────────────── tiny inputs: plan + re-verify (`q4_parse` sends inputs of at most q4_TF_N bytes here) ───────────────
//
// Phase 2, the emission (`q4_emit` with `q4_check`, `q4_mlen`, `q4_load8`, `q4_first_diff`, `q4_get0`), carries the
// whole decode invariant of this path: a planned match is written only if `q4_check` finds it in range
// and `q4_mlen` confirms every byte; anything else becomes literals. Phase 1, the planner (`q4_tf_plan` and
// everything it calls), is search: it only has to be total (no panic, terminates) and may return a
// plan of any length and contents (`q4_get0` reads 0 past its end).
// Plan format: a token list; entry k describes the k-th planned token: `len + 512 * dist` for a
// match, and any entry that `q4_check` rejects stands for `max(1, len)` literals (`len = v % 512`), so
// `q4_run` (dist 0, 1 <= q4_run <= 511) is a q4_run of `q4_run` literals and 0 a single literal. A rejected
// match therefore costs literals over its planned length and the plan stays aligned.

/// The eight bytes at `p` as one big-endian number (byte `p` most significant), or 0 when fewer
/// than eight remain (Horner form; one load plus `bswap` once inlined).


/// How many leading (most significant) bytes the words `x` and `y` share: 8 when equal.


/// How many bytes agree at `a` and `b`, up to `cap` (needs `a + cap <= n` and `b + cap <= n`):
/// eight at a time, the first mismatching word resolved by `q4_first_diff`, the last `cap % 8` bytes
/// one at a time. The only function whose result the emission trusts (through `q4_check`).


/// True only if `(len, dist)` is a legal match at `p` whose bytes all agree.


/// `v[i]`, or 0 when `i` is out of range: a read that cannot panic.


/// `v[i] = x` when `i` is in range, nothing otherwise: a write that cannot panic.


/// Phase 2: q4_walk the plan from 0 (entry `k` for the `k`-th planned token); a planned match is
/// written only if `q4_check` accepts it, else its bytes become literals (`owed`), so the plan stays aligned.


// ═══════════════ tiny inputs: the symbol-frugal planner (search only) ═══════════════
//
// The validator's encoder pays per block about 1.3 us for every live literal/length symbol and about
// 1 us for every live distance code (two or more live; a single live distance code costs nothing), on
// top of a few ns per token. A tiny input is one block, so its encode time is mostly this per-symbol
// overhead. The literal alphabet is fixed by the input (every distinct byte is a literal once), so the
// planner works on the length and distance codes:
//  1. `q4_tf_class`: binary (a zero byte or many control bytes in ~q4_TF_SAMPLE strided bytes), structured
//     text (>= 1/q4_TF_SDIG digits) or text.
//  2. `q4_tf_stage1`: a lazy hash-chain q4_parse into a token list (u16 position chains; distance 1, then the
//     previous distance, then the chain; backward extension over pending literals; the pending match is
//     folded into a new one when its bytes also match at the new distance; the engine's bit-saving
//     estimate for the lazy step) and a histogram of length codes and distance codes. Binaries
//     (q4_TF_BDEPTH 0): distance 1 only, so zero runs are one literal plus distance-1 matches and a single
//     distance code is live.
//  3. `q4_tf_keep`: a length code is kept when used >= q4_TF_KL (binaries q4_TF_BKL) times, a distance code
//     >= q4_TF_KD (q4_TF_BKD) times.
//  4. `q4_tf_rewrite`: consecutive matches at one distance are one span, re-split into kept lengths
//     (`q4_tf_piece`: one kept length, many maximal ones, or two kept lengths summing to the rest); a match
//     whose distance code was dropped is re-found at a kept distance (its chain, the two most recent
//     distances, distance 1; after up to q4_TF_SHIFT single literals), else written as literals when at
//     most q4_TF_DLIT bytes. Online re-admission: a span the kept lengths would leave >= 3 bytes uncovered
//     re-admits its own codes; a longer unfindable match keeps its distance and re-admits that code.
// The plan is a token list: `len + 512 * dist` for a match, `q4_run` (dist 0, q4_run <= 511) for a literal
// q4_run. Nothing here is trusted: `q4_emit` re-checks every planned match, so these functions only have to
// be total. Each function keeps its decisions in one place at its end (larger steps are chains of
// small helpers); arithmetic that a guard does not bound wraps.

/// Byte `i` of `s` (0 when out of range).


/// Eight bytes at `i`, first byte most significant (0 unless all eight are in range).


/// Four bytes at `i`, first byte most significant (0 unless all four are in range).


/// The smaller of `a` and `b`.


/// The larger of `a` and `b`.


/// `x >> sh`, and 0 for `sh` >= 32 (the counts shifted here stay below 2^32).


/// Chain slot of the key at `p` (four bytes; three with mask 0xFFFF_FF00).


/// Slot (0..=28) of the length code of `l` in `hist`/`keep` (lengths 3..=258; any `l` is allowed).


/// Slot (32..=61) of the distance code of `d` in `hist`/`keep` (distances 1..=32768; any `d`).


/// How many bytes agree at `a` and `b` (a < b), at most `cap` (search only: any arguments are allowed;
/// the shape of the proven `q4_mlen`, so the word loads compile to one load each).


/// Append `x` (guarded push).


/// Chain position `p` (u16 positions); returns the previous head of its slot (where the search at `p`
/// starts).


/// Chain the positions `from..to` (none when `from >= to`); returns the larger of the two.


/// Is `c` a possible source for `p` (before it and at most 32768 back)?


/// The length of the match at `p` from `c` (at most `cap`) when it beats `best`, else `best`; the byte
/// where it would beat `best` is compared first.


/// Longest match at `p` longer than `have` on the chain from position `start` (at most `depth` steps,
/// within 32768 bytes): (length, distance); distance 0 when none is longer.


/// The longest match `p` allows: min(n - p, 258), 0 at or past the end.


/// The length a match has to beat: `have`, raised to `minl - 1`.


/// Distance 1 at `p` (when `rle` = 1 and the byte before `p` repeats there): (best, bd) of the longer.


/// The previous distance `rep` (> 1) at `p`, when `on`: (best, bd) of the longer.


/// The chain from `ci` (`depth` steps) when `best` is below `cap` and q4_TF_NICE: (best, bd) of the longer.


/// Best match at `p` longer than `have` and at least `minl` long: distance 1, the previous distance
/// `rep`, then the chain from `ci` (each must be longer than the best so far, so on equal length the
/// earlier and cheaper distance stays). (0, 0) when none.


/// Append `q4_run` literals as entries of at most 511.


/// Append `q4_run` literals, then the match (l, d).


/// 1 for a zero byte.


/// 1 for a control byte (below 9, or 14..=31).


/// 1 for a decimal digit.


/// Input kind from at most ~q4_TF_SAMPLE strided bytes: 2 binary (a zero byte, or more than 1/32 control
/// bytes), 1 structured text (at least 1/q4_TF_SDIG digits), 0 other text.


/// Stage-1 settings of kind `cls`: (key mask, shortest match, chain steps, lazy limit, skip shift,
/// distance 1 first).


/// Does a q4_run of four equal bytes start at `p` (the byte before `p` differs)?


/// The first candidate at `p`: none where a q4_run starts (q4_TF_RUNSKIP, distance-1-first kinds; the next
/// position takes distance 1), else `q4_tf_find`.


/// Is the match of length `l` found at `p` taken (at least `minl` long, inside the input)?


/// Estimated saving (1/16 bit) of a match (l, d) over literals: the engine's `q4_gain` (identical for
/// 3 <= l <= 258, 1 <= d <= 32768), with wrapping arithmetic.


/// Does the match (g0, g1) found at `q` (one after the current match's position) beat (l, d)?


/// Lazy steps while the match is shorter than `lazy` and q4_TF_NICE: a better match one position later
/// replaces it (one more pending literal). The state m = [p, l, d, q4_run, ins] is read and written back
/// (a function that changes tables returns no tuple: the proof's `step*` takes flat results).


/// Extend the match (l, d) at `p` backwards over the pending literals (q4_TF_BACK): (p, l, q4_run).


/// Fold the pending match (pl, pd) into the match (l, d) at `p` when no literal is between them, the
/// sum is a legal length and its bytes also match at `d` (q4_TF_FOLD): (p, l, pd).


/// Write the pending match (pl, pd) when there is one (pd != 0) and count its codes.


/// Where the chained tail of a match ending at `end` starts: end - q4_TF_TAIL when that is after `ins`.


/// Chain the positions of a match ending at `end`: q4_TF_INS from `ins` on and the last q4_TF_TAIL (never at
/// or past `lim`); returns the next position to chain (at least `end`).


/// A match (l, d) taken at `p`: lazy steps, backward extension, the q4_fold of the pending match (pl, pd);
/// then the pending match and the literals before the new one are written and the new match's
/// positions chained. Writes o = [end, l, d, ins]: the new match is the pending one now.


/// Positions skipped after `miss` misses in a row (`p` the next position): miss >> skip, at most
/// q4_TF_SKCAP and lim - p, none at `lim`.


/// The literals pending at the end: `q4_run` plus everything from `p` on.


/// The lazy q4_parse proper (lim = n - 8), then the pending match and the literals left at the end.


/// Phase 1a: the lazy q4_parse into `tk` (chains left in `head`/`prev` for the rewrite), length codes
/// counted in hist[0..29], distance codes in hist[32..62].


/// Threshold of slot `c`: `kl` for length codes (c < 32), `kd` for distance codes.


/// 1 when a code used `h` times is kept under threshold `k`.


/// Phase 1b: kept codes (keep[0..29] lengths used at least `kl` times, keep[32..62] distances used at
/// least `kd` times).


/// `x` if it is the first kept length (`kx` and none before), else `kmin`.


/// Is the length `x` (>= 3) of a kept code?


/// `x` when `kx`, else `cur`.


/// lle[x] = the largest length <= x whose code is kept (0 when none); returns the smallest kept length
/// (0 when none).


/// Length code `c`, when kept: the first of two kept lengths summing to `x` whose first piece has code
/// `c` (3 <= each <= 258), else 0.


/// Two kept lengths summing to `x` (3 <= each <= 258): the first one, or 0 when there is none.


/// The largest kept length that leaves at least the smallest one (when rem > kmin + 3), else the
/// largest kept length <= rem (lengths above 258 count as 258).


/// `q4_tf_piece` before its range q4_check.


/// The next piece when `rem` bytes are written in kept lengths (0 when no kept length fits): `rem`
/// when kept, the largest kept length while more than two of them remain, a kept pair, else the
/// largest kept length leaving at least the smallest one.


/// Bytes of `l` that no kept piece would cover (dry q4_run of `q4_tf_split`).


/// Write `l` bytes at distance d as pieces of kept lengths; `q4_run` literals are pending before it;
/// returns the literals pending after it (bytes no piece covers become literals).


/// Re-admit the code of a remainder `r` (>= 3).


/// Re-admit the codes of `l` bytes written as 258-byte pieces and a remainder (when the kept codes
/// would leave bytes uncovered); returns the new smallest kept length.


/// `q4_tf_split` with its state in st (st[0] = pending literals, in and out; st[1] = smallest kept length).


/// Before writing `l` bytes in kept lengths: re-admit their own codes when the kept lengths would leave
/// at least 3 bytes uncovered (st[1] = the new smallest kept length).


/// Distance `d` at `p` when it is in reach and its code is kept: (best, bd) of the longer (<= cap).


/// The chain candidate `c` (before `p`, in reach) when its distance code is kept: (best, bd) of the
/// longer.


/// q4_TF_RDEPTH steps on the chain of `p` for a longer match at a kept distance: (best, bd).


/// The chain step of `q4_tf_refind` (when `chain` = 1).


/// Longest match at `p` (at most `cap` bytes) at a kept distance: the distances `r1`, `r2`, 1, then
/// (when `chain` = 1) the chain of `p` (q4_TF_RDEPTH steps): (length, distance), (0, 0) when none.


/// Remember distance `d` as the most recent one (rd[0..4]).


/// Write the span of `l` bytes at kept distance d: one kept length as is, else kept pieces (re-admitting
/// the span's own codes first when the kept lengths would leave bytes uncovered).


/// What `q4_tf_redo` does with a re-q4_find of length `fl` when `rem` bytes remain (`shift` literal tries
/// left): 0 take it, 1 one literal, 2 the original distance, 3 literals.


/// One step of `q4_tf_redo` (see `q4_tf_act`).


/// The `l` bytes at `p` whose distance code (of d) was dropped: re-found at kept distances (the chain of
/// `p` first, the recent distances, distance 1), after up to q4_TF_SHIFT single literals; else literals when
/// at most q4_TF_DLIT bytes remain, else at distance d with its code re-admitted. Returns the next position.


/// What `q4_tf_rewrite` does with the stage-1 token (l, d) (`room` bytes left): 0 literals, 1 a span at a
/// kept distance, 2 a re-q4_find (the distance code was dropped).


/// Literals for a token that is no match: min(l, room), at least 1.


/// The span of consecutive stage-1 matches at distance `d` from token `k0` on (`l0` bytes so far, at most
/// `room`): (next token, span length).


/// Phase 1c: the plan from the stage-1 tokens under the kept codes. Consecutive matches at one distance
/// are taken as one span and re-split into kept lengths; a match whose distance code was dropped is
/// re-found at a kept distance (its chain, the recent distances, distance 1; after at most q4_TF_SHIFT
/// single literals), else its bytes become literals.


/// Keep thresholds (length codes, distance codes) of kind `cls`.


/// The plan for a tiny input of kind `cls` (`q4_tf_class`).


/// The kind (`q4_tf_class`) of an input that takes the plan + re-verify path: binaries, and text of a kind
/// below q4_TF_TKIND when q4_TF_TEXT = 1, all of at most q4_TF_N bytes; 3 for every other input.


/// Length code (0..28) of a match length (0..511; lengths below 3 map to 0, above 258 to 28).
pub const q4_TF_LSYM: [u8; 512] = [
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
pub const q4_TF_DSYM: [u8; 512] = [
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
pub const q4_TF_LBASE: [u16; 32] = [3, 4, 5, 6, 7, 8, 9, 10, 11, 13, 15, 17, 19, 23, 27, 31, 35, 43, 51, 59, 67, 83, 99, 115, 131, 163, 195, 227, 258, 0, 0, 0];
pub const q4_TF_LTOP: [u16; 32] = [3, 4, 5, 6, 7, 8, 9, 10, 12, 14, 16, 18, 22, 26, 30, 34, 42, 50, 58, 66, 82, 98, 114, 130, 162, 194, 226, 257, 258, 0, 0, 0];

#[inline(always)] pub fn q4_lit_all(input:&[u8],out:&mut[u32])->usize{
 let n=input.len();let mut nt=0usize;let mut p=0usize;
 while p<n {nt=q4_put_lit(input,out,nt,p);p+=1;}nt
}

#[inline(never)] pub fn p125_row0(input:&[u8],out:&mut[u32])->usize{pc_run1c::<32768>(input,out,5,0,1000000,4294967040,2,3)}

#[inline(never)] pub fn p125_row1(input:&[u8],out:&mut[u32])->usize{pc_run1c::<32768>(input,out,4,0,1000000,4294967295,1,4)}

#[inline(never)] pub fn p125_row2(input:&[u8],out:&mut[u32])->usize{q4_run1::<8192>(input,out,3,0,1000000,4294967295)}

#[inline(never)] pub fn p125_row3(input:&[u8],out:&mut[u32])->usize{pc_run1::<32768>(input,out,6,258,1000000,4294967295)}

#[inline(never)] pub fn p125_row4(input:&[u8],out:&mut[u32])->usize{n_run::<65536,6,0,0,0,16,0,8,1>(input,out)}

#[inline(never)] pub fn p125_row5(input:&[u8],out:&mut[u32])->usize{pc_run1::<32768>(input,out,4,0,1000000,4294967295)}

#[inline(never)] pub fn p125_row6(input:&[u8],out:&mut[u32])->usize{pc_run1::<32768>(input,out,5,0,1000000,4294967295)}

#[inline(never)] pub fn p125_row7(input:&[u8],out:&mut[u32])->usize{pc_run1::<32768>(input,out,4,258,1000000,4294967295)}

#[inline(never)] pub fn p125_row8(input:&[u8],out:&mut[u32])->usize{pc_run1::<32768>(input,out,3,0,1000000,4294967295)}

#[inline(never)] pub fn p125_row9(input:&[u8],out:&mut[u32])->usize{pc_run1::<32768>(input,out,4,258,1000000,4294967295)}

#[inline(never)] pub fn p125_row10(input:&[u8],out:&mut[u32])->usize{esparse_rle(input,out,285278208)}

#[inline(never)] pub fn p125_row11(input:&[u8],out:&mut[u32])->usize{q4_run1t::<8192>(input,out,4,0,1000000,302256128)}

#[inline(never)] pub fn p125_row12(input:&[u8],out:&mut[u32])->usize{et_tiny(input,out,302256384)}

#[inline(never)] pub fn p125_row13(input:&[u8],out:&mut[u32])->usize{r109_bfraw::<65536,0>(input,out)}

#[inline(never)] pub fn p125_row14(input:&[u8],out:&mut[u32])->usize{q4_run1t::<8192>(input,out,2,258,1000000,268435456)}
#[inline(never)] pub fn p125_row15(input:&[u8],out:&mut[u32])->usize{ef32_run(input,out)}

#[inline(never)] pub fn p125_row16(input:&[u8],out:&mut[u32])->usize{q4_run1::<32768>(input,out,2,0,1000000,4294967295)}

// ───────────── EF32 engine (row 15, weights-f32): element-aligned single-probe matcher ─────────────

/// EF32: literal tokens for input[from..to] written at out[nt0..]; returns the new token count.
#[inline(always)]
pub fn ef32_put_lits(input: &[u8], out: &mut [u32], nt0: usize, from: usize, to: usize) -> usize {
    let mut nt = nt0;
    let mut j = from;
    while j < to {
        out[nt] = input[j] as u32;
        nt += 1;
        j += 1;
    }
    nt
}

/// EF32: how many bytes agree at a and b (a < b), up to cap. The only compare emitted matches rely on.
#[inline(always)]
pub fn ef32_match_len(input: &[u8], a: usize, b: usize, cap: usize) -> usize {
    let mut l = 0usize;
    while l < cap && input[a + l] == input[b + l] {
        l += 1;
    }
    l
}

/// EF32: hash slot (14 bits) of the three bytes at p (needs p + 3 <= input.len()).
#[inline(always)]
pub fn ef32_hash(input: &[u8], p: usize) -> usize {
    let w = (input[p] as u32) | ((input[p + 1] as u32) << 8) | ((input[p + 2] as u32) << 16);
    (w.wrapping_mul(0x9E37_79B1) >> 18) as usize % 16384
}

/// EF32: match length at p against the candidate c (0 unless c < p within the window), at most 258.
#[inline(always)]
pub fn ef32_probe(input: &[u8], c: usize, p: usize) -> usize {
    let n = input.len();
    if c < p && p - c <= 32768 {
        let r = n - p;
        ef32_match_len(input, c, p, if r < 258 { r } else { 258 })
    } else {
        0
    }
}

/// EF32: the match token for distance dist (1..=32768) and length l (3..=258).
#[inline(always)]
pub fn ef32_tok(dist: usize, l: usize) -> u32 {
    16777216 + ((dist - 1) as u32) * 256 + (l - 3) as u32
}

/// EF32: the first position p >= e with p = 3 (mod 4).
#[inline(always)]
pub fn ef32_align3(e: usize) -> usize {
    e + ((3 + 4 - (e % 4)) % 4)
}

/// EF32: skip distance after `miss` probes without a match: 4 * min(1 + miss / 16, 64).
#[inline(always)]
pub fn ef32_skip(miss: usize) -> usize {
    let st = 1 + (miss >> 4);
    4 * if st > 64 { 64 } else { st }
}

/// R13 fourth-byte candidate key; original three-byte matcher remains the fallback.
#[inline(always)]
pub fn r13_ef32_hash4(input: &[u8], p: usize) -> usize {
    let w=(input[p] as u32)|((input[p+1] as u32)<<8)|((input[p+2] as u32)<<16)|((input[p+3] as u32)<<24);
    (w.wrapping_mul(0x9E37_79B1)>>17) as usize
}
#[inline(always)]
pub fn r13_ef32_pick(input: &[u8], c: usize, c4: usize, p: usize) -> (usize, usize) {
    let l=ef32_probe(input,c,p);
    let l4=ef32_probe(input,c4,p);
    if l4>=3 && l4>l && (l<3 || pc_gain(l4,p-c4)>pc_gain(l,p-c)) { (l4,c4) } else { (l,c) }
}

/// EF32: f32 weights: probes only offsets p = 3 (mod 4) (key: sign/exponent byte of one element and the
/// two low bytes of the next), one hash head per key, no chains, skip acceleration over stretches
/// without matches.
#[inline(never)]
pub fn ef32_run(input: &[u8], out: &mut [u32]) -> usize {
    let n = input.len();
    let mut nt = 0usize;
    let mut ls = 0usize;
    if n > 16 && n < 2147483648 {
        let mut head = [0u32; 16384];
        let mut head4 = [0u32;32768];
        let lim = n - 8;
        let mut p = 3usize;
        let mut miss = 0usize;
        let mut fuel = n;
        while p < lim && fuel > 0 {
            fuel -= 1;
            let h = ef32_hash(input, p);
            let c = head[h] as usize;
            head[h] = p as u32;
            let h4 = r13_ef32_hash4(input,p);
            let c4 = head4[h4] as usize;
            head4[h4] = p as u32;
            let selected = r13_ef32_pick(input,c,c4,p);
            let l = selected.0;
            let c = selected.1;
            if l >= 3 {
                nt = ef32_put_lits(input, out, nt, ls, p);
                out[nt] = ef32_tok(p - c, l);
                nt += 1;
                let e = p + l;
                ls = e;
                p = ef32_align3(e);
                miss = 0;
            } else {
                miss += 1;
                p += ef32_skip(miss);
            }
        }
    }
    ef32_put_lits(input, out, nt, ls, n)
}

// ─────────────── ETINY: strided-lookup engine for one-block (small) inputs ───────────────
//
// `et_tiny(s, out, lm)`: the "tiny" engine (a = 1, b = 8, gate = 8, fold depth 16) under the length-code mask `lm`.
//  * Only the length codes in `lm` are used: a match is written as pieces of allowed lengths (`q4_e_piece`);
//    a rest no allowed length fits stays pending and is written later (as literals or inside the next match).
//  * Every position is inserted into a one-way table of 4096 entries keyed by the 4 bytes there (little-endian
//    word times 0x9E3779B1, top 12 bits); every 8th position is looked up. A hit whose 4 bytes agree is extended
//    forward (`et_fwd`, 8 bytes per step) and backward down to the first unemitted byte (`et_back`, 8 bytes per step).
//    A candidate whose distance code is not used yet must cover at least minl + 8 bytes.
//  * Earlier tokens that also match at the new distance are folded into the match (`et_fold`, at most 16).
//  * Positions are stored as position + 1 (0 = empty).

/// Four bytes at `i`, first byte least significant (0 when out of range).
#[inline(always)]
pub fn et_rd4(s: &[u8], i: usize) -> u32 {
    let n = s.len();
    if n >= 4 && i <= n - 4 {
        ((s[i + 3] as u32) << 24) | ((s[i + 2] as u32) << 16) | ((s[i + 1] as u32) << 8) | (s[i] as u32)
    } else {
        0
    }
}

/// Eight bytes at `i`, first byte least significant (0 when out of range).
#[inline(always)]
pub fn et_le8(s: &[u8], i: usize) -> u64 {
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

/// Common prefix of s[a..] and s[b..], at most `cap` (needs a + cap <= s.len(), b + cap <= s.len()): 8 bytes at a time.
#[inline(always)]
pub fn et_fwd(s: &[u8], a: usize, b: usize, cap: usize) -> usize {
    let mut k = 0usize;
    while k + 8 <= cap {
        let x = q4_be8(s, a + k) ^ q4_be8(s, b + k);
        if x != 0 {
            return k + (x.leading_zeros() / 8) as usize;
        }
        k += 8;
    }
    while k < cap && s[a + k] == s[b + k] {
        k += 1;
    }
    k
}

/// Table slot of the 4-byte word `w`.
#[inline(always)]
pub fn et_hash(w: u32) -> usize {
    (w.wrapping_mul(0x9E37_79B1) >> 20) as usize % 4096
}

/// Smallest x in 3..=258 with lens[x] = x (0 when none).
#[inline(always)]
pub fn et_minl(lens: &[u16; 260]) -> usize {
    let mut minl = 0usize;
    let mut x = 258usize;
    while x >= 3 {
        if lens[x] as usize == x {
            minl = x;
        }
        x -= 1;
    }
    minl
}

/// Distance code of `d` (needs d >= 1).
#[inline(always)]
pub fn et_dcode(d: usize) -> u32 {
    let x = (d - 1) as u32;
    if x < 4 {
        x
    } else {
        let lg = 31 - x.leading_zeros();
        2 * lg + ((x >> (lg - 1)) % 2)
    }
}

/// Common suffix of s[..a] and s[..b], at most `maxb` (needs maxb <= a <= b <= s.len()): 8 bytes at a time.
#[inline(always)]
pub fn et_back(s: &[u8], a: usize, b: usize, maxb: usize) -> usize {
    let mut k = 0usize;
    let mut run = 1u32;
    while run == 1 && k + 8 <= maxb {
        let x = et_le8(s, a - k - 8) ^ et_le8(s, b - k - 8);
        if x == 0 {
            k += 8;
        } else {
            k += (x.leading_zeros() / 8) as usize;
            run = 0;
        }
    }
    while run == 1 && k < maxb {
        if s[a - 1 - k] == s[b - 1 - k] {
            k += 1;
        } else {
            run = 0;
        }
    }
    k
}

/// Bytes covered by the greedy pieces of allowed lengths of a match of length `l`.
#[inline(always)]
pub fn et_cover(lens: &[u16; 260], l: usize) -> usize {
    let mut r = l;
    let mut c = 0usize;
    let mut go = 1u32;
    while go == 1 {
        let x = q4_e_piece(lens, r);
        if x >= 3 {
            c += x;
            r -= x;
        } else {
            go = 0;
        }
    }
    c
}

/// Record the positions ins0..stop (each below s.len() - 4) in the table; returns the next position to record.
#[inline(always)]
pub fn et_ins_to(s: &[u8], head: &mut [u32; 4096], ins0: usize, stop: usize) -> usize {
    let mut ins = ins0;
    while ins < stop {
        let h = et_hash(et_rd4(s, ins));
        head[h] = (ins + 1) as u32;
        ins += 1;
    }
    ins
}

/// After a match ending at `ls`: record at most 16 more positions below `ls`, then skip to ls - 4.
#[inline(always)]
pub fn et_ins_after(s: &[u8], head: &mut [u32; 4096], ins0: usize, ls: usize, lim: usize) -> usize {
    let mut stop = ins0.saturating_add(16);
    if stop > ls {
        stop = ls;
    }
    if stop > lim {
        stop = lim;
    }
    let mut ins = et_ins_to(s, head, ins0, stop);
    if ins + 4 < ls {
        ins = ls - 4;
    }
    ins
}

/// Backward reach for a hit at `q` from `cp`: at most q - ls, cp and 258 bytes.
#[inline(always)]
pub fn et_maxb(q: usize, ls: usize, cp: usize) -> usize {
    let mut maxb = q - ls;
    if maxb > cp {
        maxb = cp;
    }
    if maxb > 258 {
        maxb = 258;
    }
    maxb
}

/// A hit covering `cv` bytes at distance `d` is taken when cv >= minl, and cv >= minl + 8 when its
/// distance code is not used yet.
#[inline(always)]
pub fn et_take(cv: usize, minl: usize, used: u32, d: usize) -> bool {
    let newc = (used >> (et_dcode(d) % 32)) & 1 == 0;
    cv >= minl && (!newc || cv >= minl + 8)
}

/// The candidate at the looked-up position `q`: (start, distance, covered bytes, end of the agreeing bytes);
/// covered = 0 when there is none.
#[inline(always)]
pub fn et_cand(s: &[u8], head: &[u32; 4096], q: usize, ls: usize, lens: &[u16; 260], minl: usize, used: u32) -> (usize, usize, usize, usize) {
    let n = s.len();
    let w = et_rd4(s, q);
    let c = head[et_hash(w)] as usize;
    let mut bs = 0usize;
    let mut bd = 0usize;
    let mut bcov = 0usize;
    let mut bend = 0usize;
    if c > 0 && c - 1 < q && q - (c - 1) <= 32768 {
        let cp = c - 1;
        let d = q - cp;
        if et_rd4(s, cp) == w {
            let f = 4 + et_fwd(s, cp + 4, q + 4, n - q - 4);
            let bk = et_back(s, cp, q, et_maxb(q, ls, cp));
            let cv = et_cover(lens, bk + f);
            if et_take(cv, minl, used, d) {
                bcov = cv;
                bs = q - bk;
                bd = d;
                bend = q + f;
            }
        }
    }
    (bs, bd, bcov, bend)
}

/// Fold earlier tokens (literals, matches) whose bytes also match at distance `d` into a match starting at `st0`.
#[inline(always)]
pub fn et_fold(s: &[u8], out: &[u32], nt0: usize, st0: usize, d: usize) -> (usize, usize) {
    let mut nt = nt0;
    let mut st = st0;
    let mut back_n = 0usize;
    while back_n < 16 && nt > 0 && nt <= out.len() && d < st {
        let t = out[nt - 1];
        if t < 256 {
            if s[st - 1] == s[st - 1 - d] {
                st -= 1;
                nt -= 1;
                back_n += 1;
            } else {
                back_n = 16;
            }
        } else if t >= 16777216 {
            let wl = ((t - 16777216) % 256 + 3) as usize;
            if wl <= st && d <= st - wl && q4_same(s, st - wl - d, st - wl, wl) == 1 {
                st -= wl;
                nt -= 1;
                back_n += 1;
            } else {
                back_n = 16;
            }
        } else {
            back_n = 16;
        }
    }
    (nt, st)
}

/// Write the match at `x0` with distance `d` up to `end` as pieces of allowed lengths; returns (tokens, next position).
#[inline(always)]
pub fn et_pieces(s: &[u8], out: &mut [u32], nt0: usize, x0: usize, end: usize, d: usize, lens: &[u16; 260]) -> (usize, usize) {
    let mut nt = nt0;
    let mut x = x0;
    let mut go = 1u32;
    while go == 1 && x < end {
        let pc = q4_e_piece(lens, end - x);
        if pc >= 3 {
            let r = q4_put_match(s, out, nt, x, d, pc);
            nt = r.0;
            x = r.1;
        } else {
            go = 0;
        }
    }
    (nt, x)
}

/// Emit the candidate (bs0, bd, bcov, bend) found while the bytes from `ls` were pending.
#[inline(always)]
pub fn et_emit(s: &[u8], out: &mut [u32], nt0: usize, ls: usize, bs0: usize, bd: usize, bcov: usize, bend: usize, lens: &[u16; 260]) -> (usize, usize) {
    let nt1 = q4_flush(s, out, nt0, ls, bs0);
    let mut bs = bs0;
    let mut end = bs0 + bcov;
    let r = et_fold(s, out, nt1, bs0, bd);
    let st = r.1;
    if st < bs {
        bs = st;
        end = st + et_cover(lens, bend - st);
    }
    et_pieces(s, out, r.0, bs, end, bd, lens)
}

/// The engine (see the section head). Needs out.len() >= s.len().
#[inline(never)]
pub fn et_tiny(s: &[u8], out: &mut [u32], lm: u32) -> usize {
    let n = s.len();
    let mut lens = [0u16; 260];
    q4_e_lens(&mut lens, lm);
    let minl = et_minl(&lens);
    let mut nt = 0usize;
    let mut ls = 0usize;
    if n >= 32 && minl >= 3 {
        let mut head = [0u32; 4096];
        let lim = n - 8;
        let mut ins = 0usize;
        let mut q = 7usize;
        let mut fuel = n;
        let mut used = 0u32;
        while q < lim && fuel > 0 {
            fuel -= 1;
            ins = et_ins_to(s, &mut head, ins, q);
            let c = et_cand(s, &head, q, ls, &lens, minl, used);
            if c.2 >= minl {
                let r = et_emit(s, out, nt, ls, c.0, c.1, c.2, c.3, &lens);
                nt = r.0;
                ls = r.1;
                used |= 1u32 << (et_dcode(c.1) % 32);
                ins = et_ins_after(s, &mut head, ins, ls, lim);
                let nq = ls.saturating_add(7);
                q = if nq > q { nq } else { q + 1 };
            } else {
                q += 8;
            }
        }
    }
    q4_flush(s, out, nt, ls, n)
}

// ESPARSE (sparse inputs): run-length engine `rle_fast` with verify = false. A byte equal to the one before it
// starts a distance-1 match covering the whole run of that byte (8 bytes per step against the broadcast byte),
// written as pieces of allowed lengths (mask `lm`, `q4_e_pieces`); a rest no allowed length fits is literal.

/// Length of the run of byte `v` at `b` continued after `k0` bytes known to be `v`, at most `cap`.
#[inline(always)]
pub fn esparse_run(s: &[u8], b: usize, v: u8, cap: usize, k0: usize) -> usize {
    let w = (v as u64).wrapping_mul(0x0101_0101_0101_0101);
    let mut k = k0;
    let mut go = 1u32;
    while go == 1 && cap - k >= 8 {
        let x = q4_be8(s, b + k) ^ w;
        if x == 0 {
            k += 8;
        } else {
            k += (x.leading_zeros() / 8) as usize;
            go = 0;
        }
    }
    while go == 1 && k < cap {
        if s[b + k] == v {
            k += 1;
        } else {
            go = 0;
        }
    }
    k
}

/// The run-length parse under the length-code mask `lm` (see above).
#[inline(always)]
pub fn esparse_rle(s: &[u8], out: &mut [u32], lm: u32) -> usize {
    let n = s.len();
    let mut nt = 0usize;
    if n > 0 {
        let mut lens = [0u16; 260];
        q4_e_lens(&mut lens, lm);
        nt = q4_put_lit(s, out, nt, 0);
        let mut p = 1usize;
        while p < n {
            let v = s[p - 1];
            if s[p] == v {
                let r = esparse_run(s, p, v, n - p, 1);
                let e = q4_e_pieces(s, out, nt, p, r, 1, &lens);
                nt = e.0;
                p = e.1;
            } else {
                nt = q4_put_lit(s, out, nt, p);
                p += 1;
            }
        }
    }
    nt
}
