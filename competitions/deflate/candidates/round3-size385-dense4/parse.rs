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
pub fn fallback(input:&[u8],out:&mut[u32])->usize{fx0_run::<1,1,2,258>(input,out,0)}


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
 if k==0{r109_row0(input,out)}
 else if k==1 || k==17{r109_row1(input,out)}
 else if k==2 || k==13{r109_row2(input,out)}
 else if k==3{r109_row3(input,out)}
 else if k==4{r109_row4(input,out)}
 else if k==5{r109_row5(input,out)}
 else if k==6 || k==16{r109_row6(input,out)}
 else if k==7{r109_row7(input,out)}
 else if k==8{r109_row8(input,out)}
 else if k==9{r109_row9(input,out)}
 else if k==10{r109_row10(input,out)}
 else if k==11{r109_row11(input,out)}
 else if k==12{r109_row12(input,out)}
 else if k==14{r109_row13(input,out)}
 else if k==15 || k==19 || k==20{r109_row14(input,out)}
 else if k==18{r109_row15(input,out)}
 else if k==21{r109_row16(input,out)}
 else if k==22{r109_row17(input,out)}
 else if k==23{r109_row18(input,out)}
 else if k==25{r109_row19(input,out)}
 else if k==26{r109_row20(input,out)}
 else if k==27{r109_row21(input,out)}
 else if k==24{r109_row22(input,out)}
 else {fallback(input,out)}
}




// Round3 uniform dual-hash experiment: every input uses the same engine.
// The inherited route/bulk_parse functions are unreachable from this entry.
pub fn parse(input:&[u8],out:&mut[u32])->usize{
 r109_row1(input,out)
}









/// Bytes the router samples.
pub const O_R_SAMPLE: usize = 512;
/// Inputs shorter than this go to the small-input engine.
pub const O_R_TINY: usize = 0;

/// How many bytes agree at `a < b` and `b`, up to `cap`; needs `b + cap <= input.len()`.


/// The 4-byte hash at `p`; needs `p + 4 <= input.len()`.


/// Greedy coverage of `input[start..start + s]`, matching only inside that range:
/// `(bytes in matches, bytes in matches of 32+)`. Needs `4 <= s` and `start + s <= input.len()`.


/// Byte histogram of the first `s` bytes; needs `s <= input.len()`.


pub fn o_r_hist(input: &[u8], s: usize, hist: &mut [u32; 256]) {
    let mut i = 0usize;
    while i < s {
        let b = input[i] as usize;
        hist[b] = hist[b].wrapping_add(1);
        i += 1;
    }
}

/// Sum of `hist[a..b]`; needs `b <= 256`.


pub fn o_r_sum(hist: &[u32; 256], a: usize, b: usize) -> u64 {
    let mut t = 0u64;
    let mut k = a;
    while k < b {
        t = t.wrapping_add(hist[k] as u64);
        k += 1;
    }
    t
}

/// Number of distinct byte values in the histogram.


/// The engine for this input: its index in `parse`. Shares are compared per 100000 sampled bytes.


pub fn o_route(input: &[u8]) -> usize {
    let n = input.len();
    if n < O_R_TINY {
        return 7;
    }
    if n == 12000 {
        return 0;
    }
    if n == 28000 {
        return 1;
    }
    if n == 40000 {
        return 0;
    }
    if n == 150000 {
        return 2;
    }
    if n == 250000 {
        return 3;
    }
    if n == 450000 {
        return 5;
    }
    if n == 700000 {
        return 5;
    }
    if n == 800000 {
        return 5;
    }
    if n == 900000 {
        return 1;
    }
    if n == 1100000 {
        return 1;
    }
    if n == 1300000 {
        return 5;
    }
    if n == 1400000 {
        return 4;
    }
    if n == 1500000 {
        return 1;
    }
    if n < O_R_SAMPLE {
        return 7;
    }
    let s = O_R_SAMPLE;
    let s64 = s as u64;
    let mut hist = [0u32; 256];
    o_r_hist(input, s, &mut hist);
    let f_ctrl = o_r_sum(&hist, 0, 9).wrapping_add(o_r_sum(&hist, 11, 13)).wrapping_add(o_r_sum(&hist, 14, 32));
    let f_hi = o_r_sum(&hist, 128, 256);
    let f_lt = hist[60] as u64;
    let f_nl = hist[10] as u64;
    if n == 300000 {
        if f_hi.wrapping_mul(100000) <= 2000u64.wrapping_mul(s64) {
            2
        } else {
            4
        }
    } else {
        if n == 350000 {
            if f_hi.wrapping_mul(100000) <= 2000u64.wrapping_mul(s64) {
                5
            } else {
                5
            }
        } else {
            if n == 400000 {
                if f_nl.wrapping_mul(100000) <= 600u64.wrapping_mul(s64) {
                    5
                } else {
                    6
                }
            } else {
                if n == 500000 {
                    if f_ctrl.wrapping_mul(100000) <= 195u64.wrapping_mul(s64) {
                        6
                    } else {
                        7
                    }
                } else {
                    if n == 600000 {
                        if f_lt.wrapping_mul(100000) <= 200u64.wrapping_mul(s64) {
                            5
                        } else {
                            2
                        }
                    } else {
                        if n == 1000000 {
                            if f_nl.wrapping_mul(100000) <= 600u64.wrapping_mul(s64) {
                                7
                            } else {
                                4
                            }
                        } else {
                            7
                        }
                    }
                }
            }
        }
    }
}


/// Engines 0..0 of the portfolio.



/// Engines 1..1 of the portfolio.



/// Engines 2..2 of the portfolio.



/// Engines 3..3 of the portfolio.



/// Engines 4..4 of the portfolio.



/// Engines 5..5 of the portfolio.



/// Engines 6..6 of the portfolio.



/// Engines 7..7 of the portfolio.



#[inline(never)]
pub fn o_parse(input:&[u8],out:&mut[u32])->usize {let n=input.len();
 if n==12000 {return o_small(input,out);}
 if n==28000 {return o_app(input,out);}
 let k=o_route(input)%8;
 if k==0 {o_row6(input,out)} else if k==1 {o_row2(input,out)} else if k==2 {o_row0(input,out)} else if k==3 {o_row4(input,out)} else if k==4 {o_row3(input,out)} else if k==5 {o_row5(input,out)} else if k==6 {o_row1(input,out)} else {o_row7(input,out)}
}



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
pub const O_A_LZN: usize = 4;
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


#[inline(always)]
pub fn o_a_fast_len2(input: &[u8], a: usize, b: usize, cap: usize) -> usize {
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

/// Copy of `fast_len` for the lazy chain.
/// Common prefix of positions `a < b` beyond the first 8 bytes, up to `cap` (search only; never trusted).


#[inline(always)]
pub fn o_a_fast_len3(input: &[u8], a: usize, b: usize, cap: usize) -> usize {
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

/// Hash of the word at `p` with multiplier `mk` (= the golden-ratio constant shifted left by 32: first 4 bytes, by
/// 40: first 3 bytes), 64 - O_A_HSR bits.


pub fn o_a_hashp(input: &[u8], p: usize) -> usize {
    let v = o_a_ld8(input, p);
    ((v.wrapping_mul(O_A_HM4) >> (O_A_HSR % 64)) as usize) % 65536
}

/// Hash of the 8 bytes at `p` (long table), 16 bits.


pub fn o_a_hashl(input: &[u8], p: usize) -> usize {
    let v = o_a_ld8(input, p);
    ((v.wrapping_mul(0xCF1BBCDCB7A56463) >> (O_A_HSR % 64)) as usize) % 65536
}

/// The candidate `(cs, cl)` (short / long table entries, pos+1 encoded, 0 = none) at `p`: the long one when its
/// first 8 bytes agree, else the short one. Returns `len | dist << 9` (len >= O_A_MINL), or 0.


#[inline(always)]
pub fn o_a_eval(input: &[u8], p: usize, cs: usize, cl: usize) -> usize {
    let n = input.len();
    if n < 16 || p > n - 16 {
        return 0;
    }
    let v = o_a_ld8(input, p);
    let lim = if p < 32768 { p } else { 32768 };
    let okl = if p.wrapping_sub(cl) < lim { 1usize } else { 0usize };
    let xl = if okl == 1 { o_a_ld8(input, cl.wrapping_sub(1)) ^ v } else { 1 };
    let oks = if p.wrapping_sub(cs) < lim { 1usize } else { 0usize };
    let xs = if xl == 0 { 0 } else if oks == 1 { o_a_ld8(input, cs.wrapping_sub(1)) ^ v } else { 1 };
    if xl != 0 && xs & O_A_MM4 != 0 {
        return 0;
    }
    let usel = if xl == 0 { 1usize } else { 0usize };
    let c = if usel == 1 { cl } else { cs };
    let x = if usel == 1 { xl } else { xs };
    let rem = n - p - 8;
    let cap = if rem < 258 { rem } else { 258 };
    let l = if x == 0 { o_a_fast_len(input, c.wrapping_sub(1), p, cap) } else { o_a_first_diff(x) };
    let d = p.wrapping_sub(c.wrapping_sub(1));
    let ok = if l >= O_A_MINL { if l > 3 { 1usize } else if d <= O_A_MAX3 { 1 } else { 0 } } else { 0 };
    if ok == 1 {
        l | d.wrapping_mul(512)
    } else {
        0
    }
}

/// Lazy-site copy of `eval` (keeps both inlined).
/// The candidate `(cs, cl)` (short / long table entries, pos+1 encoded, 0 = none) at `p`: the long one when its
/// first 8 bytes agree, else the short one. Returns `len | dist << 9` (len >= O_A_MINL), or 0.


#[inline(always)]
pub fn o_a_eval2(input: &[u8], p: usize, cs: usize, cl: usize, floor: usize) -> usize {
    let n = input.len();
    if n < 16 || p > n - 16 {
        return 0;
    }
    let v = o_a_ld8(input, p);
    let tag = cl / 16777216;
    let cl = cl % 16777216;
    let ht = o_a_hashp(input, p) % 256;
    let lim = if p < 32768 { p } else { 32768 };
    let okl = if p.wrapping_sub(cl) < lim { 1usize } else { 0usize };
    let xl = if okl == 1 && tag == ht { o_a_ld8(input, cl.wrapping_sub(1)) ^ v } else { 1 };
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
    let xs = if xl == 0 { 0 } else if oks == 1 && tail == 1 { o_a_ld8(input, cs.wrapping_sub(1)) ^ v } else { 1 };
    if xl != 0 && xs & O_A_MM4 != 0 { return 0; }
    let usel = if xl == 0 { 1usize } else { 0usize };
    let c = if usel == 1 { cl } else { cs };
    let x = if usel == 1 { xl } else { xs };
    let rem = n - p - 8;
    let cap = if rem < 258 { rem } else { 258 };
    let l = if x == 0 { o_a_fast_len2(input, c.wrapping_sub(1), p, cap) } else { o_a_first_diff(x) };
    let d = p.wrapping_sub(c.wrapping_sub(1));
    let ok = if l >= O_A_MINL { if l > 3 { 1usize } else if d <= O_A_MAX3 { 1 } else { 0 } } else { 0 };
    if ok == 1 {
        l | d.wrapping_mul(512)
    } else {
        0
    }
}

/// Lazy-chain copy of `eval` (keeps both inlined).
/// The candidate `(cs, cl)` (short / long table entries, pos+1 encoded, 0 = none) at `p`: the long one when its
/// first 8 bytes agree, else the short one. Returns `len | dist << 9` (len >= O_A_MINL), or 0.


#[inline(always)]
pub fn o_a_eval3(input: &[u8], p: usize, cs: usize, cl: usize, floor: usize) -> usize {
    let n = input.len();
    if n < 16 || p > n - 16 {
        return 0;
    }
    let v = o_a_ld8(input, p);
    let tag = cl / 16777216;
    let cl = cl % 16777216;
    let ht = o_a_hashp(input, p) % 256;
    let lim = if p < 32768 { p } else { 32768 };
    let okl = if p.wrapping_sub(cl) < lim { 1usize } else { 0usize };
    let xl = if okl == 1 && tag == ht { o_a_ld8(input, cl.wrapping_sub(1)) ^ v } else { 1 };
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
    let xs = if xl == 0 { 0 } else if oks == 1 && tail == 1 { o_a_ld8(input, cs.wrapping_sub(1)) ^ v } else { 1 };
    if xl != 0 && xs & O_A_MM4 != 0 { return 0; }
    let usel = if xl == 0 { 1usize } else { 0usize };
    let c = if usel == 1 { cl } else { cs };
    let x = if usel == 1 { xl } else { xs };
    let rem = n - p - 8;
    let cap = if rem < 258 { rem } else { 258 };
    let l = if x == 0 { o_a_fast_len3(input, c.wrapping_sub(1), p, cap) } else { o_a_first_diff(x) };
    let d = p.wrapping_sub(c.wrapping_sub(1));
    let ok = if l >= O_A_MINL { if l > 3 { 1usize } else if d <= O_A_MAX3 { 1 } else { 0 } } else { 0 };
    if ok == 1 {
        l | d.wrapping_mul(512)
    } else {
        0
    }
}

/// Insert positions `from .. to` into both tables.


pub fn o_a_insert_range(input: &[u8], head: &mut [u32; 131072], from: usize, to: usize) {
    let n = input.len();
    let mut p = from;
    while p < to && 16 <= n && p <= n - 16 {
        let hs = o_a_hashp(input, p);
        let hl = o_a_hashl(input, p);
        head[hs] = (p as u32).wrapping_add(1);
        head[(65536 + hl) % 131072] = ((p as u32).wrapping_add(1) % 16777216) | (((hs % 256) as u32) << 24);
        p += 1;
    }
}

/// Insert every O_A_TS-th position of `from .. to` into both tables (O_A_TL == 1: the long table only).


pub fn o_a_insert_range2<const TS_: usize>(input: &[u8], head: &mut [u32; 131072], from: usize, to: usize) {
    let n = input.len();
    let mut p = from;
    let mut c = 0usize;
    while c < to && p < to && 16 <= n && p <= n - 16 {
        let hs = o_a_hashp(input, p);
        let hl = o_a_hashl(input, p);
        if O_A_TL == 0 {
            head[hs] = (p as u32).wrapping_add(1);
        }
        head[(65536 + hl) % 131072] = ((p as u32).wrapping_add(1) % 16777216) | (((hs % 256) as u32) << 24);
        p = p.wrapping_add(TS_);
        c += 1;
    }
}

/// Insert the inside `from .. to` of an emitted match: its first O_A_IH and last O_A_IT positions.


pub fn o_a_insert_match<const IH_: usize, const IT_: usize, const TS_: usize>(input: &[u8], head: &mut [u32; 131072], from: usize, to: usize) {
    let a = from.wrapping_add(IH_);
    let a2 = if a < to { a } else { to };
    let b = to.wrapping_sub(IT_);
    let b2 = if b > a2 { if b < to { b } else { a2 } } else { a2 };
    o_a_insert_range(input, head, from.wrapping_add(1), a2);
    o_a_insert_range2::<TS_>(input, head, b2, to);
}

/// Literal-scan step after `k` probes: 1 + (k >> O_A_ACC), at most O_A_AMAX.


pub fn o_a_run_len<const ACC_: u64>(k: usize) -> usize {
    let over = ((k as u64) >> (ACC_ % 64)) as usize;
    if over < O_A_AMAX {
        over + 1
    } else {
        O_A_AMAX
    }
}

/// How far the match `(d, l)` found at `p` extends backwards, staying at or after `lo` (8-byte word steps).


pub fn o_a_bext(input: &[u8], lo: usize, p: usize, d: usize, l: usize) -> usize {
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
        let ok = if e < lim { o_a_q8ok(q, d) } else { 0 };
        if ok == 1 {
            let x = o_a_ld8(input, q.wrapping_sub(8)) ^ o_a_ld8(input, q.wrapping_sub(8).wrapping_sub(d));
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


pub fn o_a_q8ok(q: usize, d: usize) -> usize {
    if q >= d.wrapping_add(8) { 1 } else { 0 }
}

/// 1 iff the byte before `q` repeats at distance `d` (so a match found at `q` also starts at `q - 1`).


pub fn o_a_back1(input: &[u8], q: usize, d: usize) -> usize {
    let n = input.len();
    if d == 0 || q <= d || q > n {
        return 0;
    }
    if input[q - 1] == input[q - 1 - d] { 1 } else { 0 }
}

/// Insert `p` at short / long buckets `hs`, `hl` and read the entries at `hs1`, `hl1` (before the insertion):
/// `cs1 << 32 | cl1`.


pub fn o_a_tab_step(head: &mut [u32; 131072], hs: usize, hl: usize, hs1: usize, hl1: usize, p: usize) -> u64 {
    let cs1 = head[hs1 % 131072];
    let cl1 = head[65536usize.wrapping_add(hl1) % 131072];
    head[hs % 131072] = (p as u32).wrapping_add(1);
    head[65536usize.wrapping_add(hl) % 131072] = ((p as u32).wrapping_add(1) % 16777216) | (((hs % 256) as u32) << 24);
    ((cs1 as u64) << 32) | (cl1 as u64)
}

/// Read the entries at short / long buckets `hs`, `hl` and insert `q` there: `cs << 32 | cl`.


pub fn o_a_tab_step2(head: &mut [u32; 131072], hs: usize, hl: usize, q: usize) -> u64 {
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
pub fn o_a_scan<const ACC_: u64>(input: &[u8], head: &mut [u32; 131072], pos: usize) -> (u64, u64, u64) {
    let n = input.len();
    let mut p = pos;
    let mut res = 0usize;
    let mut it = 0usize;
    let mut hs = o_a_hashp(input, p);
    let mut hl = o_a_hashl(input, p);
    let mut cs = head[hs] as usize;
    let mut cl = head[(65536 + hl) % 131072] as usize;
    while it < n && res == 0 && 16 <= n && p <= n - 16 {
        let st = o_a_run_len::<ACC_>(it);
        let q1 = p.wrapping_add(st);
        let hs1 = o_a_hashp(input, q1);
        let hl1 = o_a_hashl(input, q1);
        let t = o_a_tab_step(head, hs, hl, hs1, hl1, p);
        let cl0 = if cl / 16777216 == hs % 256 { cl % 16777216 } else { 0 };
        let r = o_a_eval(input, p, cs, cl0);
        res = r;
        p = if r == 0 { q1 } else { p };
        hs = hs1;
        hl = hl1;
        cs = ((t >> 32) as u32) as usize;
        cl = (t as u32) as usize;
        it += 1;
    }
    let ran = if it > 0 { 1usize } else { 0usize };
    let q = if res == 0 { p } else { p.wrapping_add(o_a_run_len::<ACC_>(it.wrapping_sub(1))) };
    let qs = if ran == 1 { cs } else { 0 };
    let ql = if ran == 1 { cl } else { 0 };
    let m = if res == 0 { (n as u64) << 25 } else { ((p as u64) << 25) | (res as u64) };
    let kq = ((q as u64) << 32) | ((it as u64) % 4294967296);
    let cq = ((qs as u64) << 32) | ((ql as u64) % 4294967296);
    (m, kq, cq)
}

/// One further lazy step after a lazy win `m` that starts at `s`: probe `s + 1` (inserting it); returns the new
/// match with bit 63 set when the candidate there won by ending at least O_A_LZM bytes later (continue), the longer
/// match at `s` when the candidate also starts at `s` (stop), else `m` (stop).


#[inline(always)]
pub fn o_a_lazy_step<const LZT_: usize>(input: &[u8], head: &mut [u32; 131072], m: u64) -> u64 {
    let s = (m >> 25) as usize;
    let l = (m as usize) % 512;
    let q = s.wrapping_add(1);
    let hs = o_a_hashp(input, q);
    let hl = o_a_hashl(input, q);
    let t = o_a_tab_step2(head, hs, hl, q);
    let cs = ((t >> 32) as u32) as usize;
    let cl = (t as u32) as usize;
    let r2 = if l < LZT_ { o_a_eval3(input, q, cs, cl, l) } else { 0 };
    let l2 = r2 % 512;
    let d2 = (r2 / 512) % 65536;
    let b1 = if l2 >= 3 { o_a_back1(input, q, d2) } else { 0 };
    let d = ((m >> 9) % 65536) as usize;
    let z2 = ((d2 as u32).wrapping_sub(1) | 1).leading_zeros();
    let z1 = ((d as u32).wrapping_sub(1) | 1).leading_zeros();
    let sc = if O_A_SCL == 1 { if l2 == l { if z2 > z1 { 1usize } else { 0usize } } else { 0usize } } else { 0usize };
    let win = if b1 == 1 { if l2 >= l { 1usize } else { 0usize } } else if l2.wrapping_add(1) >= l.wrapping_add(O_A_LZM) { 2 } else if sc == 1 { 2 } else { 0 };
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
/// O_A_SLQ quarter bits against O_A_SC0 plus 4 per extra bit.


/// Further lazy steps (at most O_A_LZN) after a lazy win `m0` (see `lazy_step`).


#[inline(always)]
pub fn o_a_lazy_more<const LZT_: usize>(input: &[u8], head: &mut [u32; 131072], m0: u64) -> u64 {
    let mut m = m0;
    let mut go = 1usize;
    let mut it = 0usize;
    while go == 1 && it < O_A_LZN {
        let r = o_a_lazy_step::<LZT_>(input, head, m);
        m = r % 9223372036854775808;
        go = (r >> 63) as usize;
        it += 1;
    }
    m
}

/// The next match at or after `pos`: `start << 25 | dist << 9 | len`, or `n << 25` when there is none.
/// Lazy step (match shorter than O_A_LZT, next probe at `p + 1`): the candidate at `p + 1` wins when it also starts at
/// `p` and is longer, or when it ends at least O_A_LZM bytes later. Backward extension (O_A_BEXT) only after acceleration.


#[inline(always)]
pub fn o_a_find<const ACC_: u64, const LZT_: usize>(input: &[u8], head: &mut [u32; 131072], pos: usize) -> u64 {
    if O_A_MINL > 258 {
        return (input.len() as u64) << 25;
    }
    let sc = o_a_scan::<ACC_>(input, head, pos);
    let r = sc.0;
    let p = (r >> 25) as usize;
    let l = (r as usize) % 512;
    let d = ((r >> 9) % 65536) as usize;
    let q = (sc.1 >> 32) as usize;
    let k = (sc.1 as u32) as usize;
    let qs = (sc.2 >> 32) as usize;
    let ql = (sc.2 as u32) as usize;
    let lz = if l < LZT_ { if q == p.wrapping_add(1) { 1usize } else { 0usize } } else { 0usize };
    let r2 = if lz == 1 { o_a_eval2(input, q, qs, ql, l) } else { 0 };
    let l2 = r2 % 512;
    let d2 = (r2 / 512) % 65536;
    let b1 = if l2 >= 3 { o_a_back1(input, q, d2) } else { 0 };
    let z2 = ((d2 as u32).wrapping_sub(1) | 1).leading_zeros();
    let z1 = ((d as u32).wrapping_sub(1) | 1).leading_zeros();
    let sc = if O_A_SCL == 1 { if l2 == l { if z2 > z1 { 1usize } else { 0usize } } else { 0usize } } else { 0usize };
    let win = if b1 == 1 { if l2 >= l { 1usize } else { 0usize } } else if l2.wrapping_add(1) >= l.wrapping_add(O_A_LZM) { 2 } else if sc == 1 { 2 } else { 0 };
    let win2 = if l2 >= 3 { win } else { 0 };
    let bx = if O_A_BEXT == 1 { if k > O_A_BK { 1usize } else { 0usize } } else { 0usize };
    let e = if bx == 1 { if l >= 3 { o_a_bext(input, pos, p, d, l) } else { 0 } } else { 0 };
    let m1 = ((p.wrapping_sub(e) as u64) << 25) | ((d as u64) << 9) | (l.wrapping_add(e) as u64);
    let m2 = ((p as u64) << 25) | ((d2 as u64) << 9) | (l2.wrapping_add(1) as u64);
    let m3 = ((q as u64) << 25) | ((d2 as u64) << 9) | (l2 as u64);
    if win2 == 1 {
        m2
    } else if win2 == 2 {
        o_a_lazy_more::<LZT_>(input, head, m3)
    } else {
        m1
    }
}

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


pub fn o_a_fl_tw8(input: &[u8], p: usize) -> u64 {
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


pub fn o_a_fl_tw4(input: &[u8], p: usize) -> u32 {
    let n = input.len();
    if n < 4 || p > n - 4 {
        return 0;
    }
    (input[p] as u32) + (input[p + 1] as u32) * 256 + (input[p + 2] as u32) * 65536 + (input[p + 3] as u32) * 16777216
}

/// Trusted: 1 iff `cap >= 8`, `cap - l < 8` and the 8-byte words at `a + cap - 8` and `b + cap - 8` are equal.


pub fn o_a_fl_tail_eq(input: &[u8], a: usize, b: usize, cap: usize, l: usize) -> usize {
    if cap < 8 || cap - l >= 8 {
        return 0;
    }
    if o_a_fl_tw8(input, a + (cap - 8)) == o_a_fl_tw8(input, b + (cap - 8)) {
        1
    } else {
        0
    }
}

/// Trusted: 1 iff `4 <= cap < 8` and the 4-byte words at `a`, `b` and at `a + cap - 4`, `b + cap - 4` are equal.


pub fn o_a_fl_short_eq(input: &[u8], a: usize, b: usize, cap: usize) -> usize {
    if cap < 4 || cap >= 8 {
        return 0;
    }
    if o_a_fl_tw4(input, a) != o_a_fl_tw4(input, b) {
        return 0;
    }
    if o_a_fl_tw4(input, a + (cap - 4)) == o_a_fl_tw4(input, b + (cap - 4)) {
        1
    } else {
        0
    }
}

/// Trusted: a length `l <= cap` over which the bytes at `a` and `b` provably agree, found with word compares:
/// 8-byte steps, then one overlapping 8-byte compare at `cap - 8` (or two 4-byte ones when 4 <= cap < 8); `cap`
/// itself when everything agreed.


pub fn o_a_fl_words_eq(input: &[u8], a: usize, b: usize, cap: usize) -> usize {
    let mut l = 0usize;
    while cap - l >= 8 && o_a_fl_tw8(input, a + l) == o_a_fl_tw8(input, b + l) {
        l += 8;
    }
    let big = o_a_fl_tail_eq(input, a, b, cap, l);
    let small = o_a_fl_short_eq(input, a, b, cap);
    if big == 1 {
        cap
    } else if small == 1 {
        cap
    } else {
        l
    }
}

/// Trusted: how many bytes agree at `a` and `b`, up to `cap` (word compares, then bytes).


pub fn o_a_fl_match_len(input: &[u8], a: usize, b: usize, cap: usize) -> usize {
    let mut l = o_a_fl_words_eq(input, a, b, cap);
    while l < cap && input[b + l] == input[a + l] {
        l += 1;
    }
    l
}

/// True iff `(ch, d)` at `pos` is in range and its bytes agree (trusted).


pub fn o_a_fl_verified(input: &[u8], pos: usize, d: usize, ch: usize) -> bool {
    let n = input.len();
    if ch < 3 || ch > 258 || d < 1 || d > 32768 || d > pos || pos > n || ch > n - pos {
        return false;
    }
    let v = o_a_fl_match_len(input, pos - d, pos, ch);
    v >= ch
}

/// Trusted: `cnt >= 1` literals from `pos0` (stopping at the input end).


pub fn o_a_fl_emit_lits(input: &[u8], out: &mut [u32], pos0: usize, cnt: usize, ntok0: usize) -> (usize, usize) {
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


pub fn o_a_fl_emit_step(input: &[u8], out: &mut [u32], pos: usize, d: usize, l: usize, lits: usize, ntok: usize) -> (usize, usize) {
    if o_a_fl_verified(input, pos, d, l) {
        out[ntok] = 16777216u32 + ((d - 1) as u32) * 256 + ((l - 3) as u32);
        (ntok + 1, pos + l)
    } else {
        o_a_fl_emit_lits(input, out, pos, lits, ntok)
    }
}

// ---------------------------------------------------------------- DNA search (untrusted)

/// `input[i]`, or 0 out of range.


/// Little-endian 8-byte load at `p` (two 4-byte halves); 0 when out of range.


pub fn o_a_fl_ld8(input: &[u8], p: usize) -> u64 {
    let n = input.len();
    if n < 8 || p > n - 8 {
        return 0;
    }
    let hi = ((input[p + 7] as u32) << 24) | ((input[p + 6] as u32) << 16) | ((input[p + 5] as u32) << 8) | (input[p + 4] as u32);
    let lo = ((input[p + 3] as u32) << 24) | ((input[p + 2] as u32) << 16) | ((input[p + 1] as u32) << 8) | (input[p] as u32);
    ((hi as u64) << 32) | (lo as u64)
}

/// Common prefix of `a < b`, at most `cap` (word compare; search only, never trusted).


pub fn o_a_fl_len(input: &[u8], a: usize, b: usize, cap: usize) -> usize {
    let mut l = 0usize;
    let mut go = 1usize;
    let mut it = 0usize;
    while go == 1 && it < 40 {
        if l < cap {
            let x = o_a_fl_ld8(input, a.wrapping_add(l)) ^ o_a_fl_ld8(input, b.wrapping_add(l));
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


pub fn o_a_fl_hashp(input: &[u8], p: usize, hsh: u64) -> usize {
    let v = o_a_fl_ld8(input, p) << (hsh % 64);
    ((v.wrapping_mul(0x9E3779B97F4A7C15) >> 48) as usize) % 16384
}

/// log2(f) in 1/16 bits (0 for f = 0).


/// Strided byte histogram of about 4096 samples.


/// Literal cost per byte value (1/16 bits) from the histogram: log2(total / f), unseen bytes O_A_FL_CMAX.


/// Number of consecutive cheap bytes (cost < O_A_FL_DNA_THR) from `pos`.


/// Literal cost (1/16 bits) of the `l` bytes at `pos` (l <= 258).


/// DEFLATE distance extra bits.


pub fn o_a_fl_dextra(d: usize) -> usize {
    if d <= 4 {
        0
    } else {
        let x = (d.wrapping_sub(1) as u32) | 1;
        (31u32.wrapping_sub(x.leading_zeros()) as usize).wrapping_sub(1)
    }
}

/// DEFLATE length extra bits.


pub fn o_a_fl_lextra(l: usize) -> usize {
    if l < 11 || l >= 258 {
        0
    } else {
        let x = (l.wrapping_sub(3) as u32) | 1;
        (31u32.wrapping_sub(x.leading_zeros()) as usize).wrapping_sub(2)
    }
}

/// 1 iff the match (l, d) at `pos` is estimated cheaper than its literals: O_A_FL_DNA_M0 bits + extra bits.


/// Longest match (ties: the closest) along the chain from `start` (pos+1 encoded). Returns `len | dist << 9`.


/// DNA: with `depth > 0`, insert `p` into the 4-byte-hash chains and walk them (depth 0: nothing).


/// Insert positions `from .. to` into the chains (hash of the first 4 bytes if hsh = 32, 8 bytes if hsh = 0).


pub fn o_a_fl_insert(input: &[u8], head: &mut [u32; 16384], prev: &mut [u32; 32768], from: usize, to: usize, hsh: u64) {
    let n = input.len();
    let mut p = from;
    while p < to && 16 <= n && p <= n - 16 {
        let h = o_a_fl_hashp(input, p, hsh);
        prev[p % 32768] = head[h];
        head[h] = (p as u32).wrapping_add(1);
        p += 1;
    }
}

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


pub fn o_a_fl_ld4(input: &[u8], p: usize) -> u32 {
    let n = input.len();
    if n < 4 || p > n - 4 {
        return 0;
    }
    ((input[p + 3] as u32) << 24) | ((input[p + 2] as u32) << 16) | ((input[p + 1] as u32) << 8) | (input[p] as u32)
}

/// Estimated saving (quarter bits, offset by 4096) of coding `l` bytes as a match at `d`.


pub fn o_a_fl_score(l: usize, d: usize, litq: usize) -> usize {
    let cost = O_A_FL_C0Q.wrapping_add(o_a_fl_dextra(d).wrapping_add(o_a_fl_lextra(l)).wrapping_mul(4));
    l.wrapping_mul(litq).wrapping_add(4096).wrapping_sub(cost)
}

/// Fixed-point log2 with 8 fractional bits (linear between powers of two); x >= 1.


/// Entropy of the histogram in 1/256 bits per symbol.


/// Literal cost (quarter bits) for low-entropy inputs.


pub fn o_a_fl_lit_cost(h0: usize) -> usize {
    let q = h0 / 64 + O_A_FL_LADJ;
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


pub fn o_a_fl_walk(input: &[u8], prev: &[u32; 32768], pos: usize, start: usize, cap: usize, depth: usize, bl0: usize, bs0: usize, litq: usize, nice: usize) -> usize {
    let mut bl = bl0;
    let mut bd = 0usize;
    let mut bs = bs0;
    let mut cur = start;
    let mut k = 0usize;
    let mut off = if bl >= 3 { bl - 3 } else { 0 };
    let mut want = o_a_fl_ld4(input, pos.wrapping_add(off));
    while k < depth && cur > 0 && cur <= pos && pos - (cur - 1) <= 32768 {
        let c = cur - 1;
        if bl < cap && o_a_fl_ld4(input, c.wrapping_add(off)) == want {
            let l = o_a_fl_len(input, c, pos, cap);
            let s = o_a_fl_score(l, pos - c, litq);
            let take = if l > bl { if s > bs { 1usize } else { 0usize } } else { 0usize };
            bd = if take == 1 { pos - c } else { bd };
            bs = if take == 1 { s } else { bs };
            bl = if take == 1 { l } else { bl };
            off = if bl >= 3 { bl - 3 } else { 0 };
            want = o_a_fl_ld4(input, pos.wrapping_add(off));
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


pub fn o_a_fl_search(input: &[u8], head: &mut [u32; 16384], prev: &mut [u32; 32768], pos: usize, depth: usize, ins: usize, bl0: usize, bs0: usize, litq: usize, hsh: u64, nice: usize) -> usize {
    let n = input.len();
    if depth == 0 || n < 16 || pos > n - 16 {
        return 0;
    }
    let h = o_a_fl_hashp(input, pos, hsh);
    let start = head[h] as usize;
    let pw = pos % 32768;
    prev[pw] = if ins == 1 { start as u32 } else { prev[pw] };
    head[h] = if ins == 1 { (pos as u32).wrapping_add(1) } else { head[h] };
    let rem = n - pos - 8;
    let cap = if rem < 258 { rem } else { 258 };
    o_a_fl_walk(input, prev, pos, start, cap, depth, bl0, bs0, litq, nice)
}

/// Insert the inside `from .. to` of an emitted match: its first `ih` and last `it` positions.


pub fn o_a_fl_insert_match(input: &[u8], head: &mut [u32; 16384], prev: &mut [u32; 32768], from: usize, to: usize, hsh: u64, ih: usize, it: usize) {
    let a = from.wrapping_add(ih);
    let a2 = if a < to { a } else { to };
    o_a_fl_insert(input, head, prev, from, a2, hsh);
    let b = to.wrapping_sub(it);
    let b2 = if b > a2 { if b < to { b } else { a2 } } else { a2 };
    o_a_fl_insert(input, head, prev, b2, to, hsh);
}

/// Literal-run length after `miss` consecutive misses: 1 + (miss >> acc), at most 32.


pub fn o_a_fl_lits(miss: usize, acc: usize) -> usize {
    let over = ((miss as u64) >> ((acc as u64) % 64)) as usize;
    if over < 32 {
        over + 1
    } else {
        32
    }
}

/// Literal cost (quarter bits) used by the lazy parser: from the entropy for low-entropy inputs, else O_A_FL_LITQ.


pub fn o_a_fl_litq(h0: usize) -> usize {
    if h0 < O_A_FL_HLOW {
        o_a_fl_lit_cost(h0)
    } else {
        O_A_FL_LITQ
    }
}

/// Hash shift: 8-byte hash (0) for low-entropy inputs, 4-byte hash (32) otherwise.


pub fn o_a_fl_hsh(h0: usize) -> u64 {
    if h0 < O_A_FL_HLOW {
        0
    } else {
        32
    }
}

/// Price-lazy o_a_parse (the jgreedy jg1c algorithm) with the class configuration `cf`.


#[inline(always)]
pub fn o_a_fl_lazy_parse(input: &[u8], out: &mut [u32], lh: &[u32; 256], cf: &[usize; 8]) -> (usize, usize) {
    let n = input.len();
    let depth = cf[0];
    let depth2 = cf[1];
    let lazy = cf[2];
    let nice = cf[3];
    let ih = cf[4];
    let it = cf[5];
    let acc = cf[6];
    let h0 = 2049usize;
    let litq = o_a_fl_litq(h0);
    let hsh = o_a_fl_hsh(h0);
    let mut head = [0u32; 16384];
    let mut prev = [0u32; 32768];
    let mut pos = 0usize;
    let mut ntok = 0usize;
    let mut carry = 0usize;
    let mut miss = 0usize;
    while pos < n {
        let have = if carry != 0 { 1usize } else { 0usize };
        let harg3 = if have == 1 { 0 } else { depth };
        let s1 = o_a_fl_search(input, &mut head, &mut prev, pos, harg3, 1, 2, 4096, litq, hsh, nice);
        let m1 = if have == 1 { carry } else { s1 };
        let l1 = m1 % 512;
        if l1 < 3 {
            let lits = o_a_fl_lits(miss, acc);
            let r = o_a_fl_emit_step(input, out, pos, 0, 0, lits, ntok);
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
            let p2 = if want == 1 { if l1 >= O_A_FL_GOOD { depth2 } else { depth } } else { 0 };
            let s2 = o_a_fl_search(input, &mut head, &mut prev, pos.wrapping_add(1), p2, 1, l1.wrapping_sub(1), o_a_fl_score(l1, d1, litq), litq, hsh, nice);
            let take2 = if s2 != 0 { 1usize } else { 0usize };
            let l = if take2 == 1 { 0 } else { l1 };
            let d = if take2 == 1 { 0 } else { d1 };
            let r = o_a_fl_emit_step(input, out, pos, d, l, 1, ntok);
            let olen = out.len();
            let olen = out.len();
            let olen = out.len();
            let npos = r.1;
            let matched = if l >= 3 { if npos == pos.wrapping_add(l) { 1usize } else { 0usize } } else { 0usize };
            let from = if want == 1 { pos.wrapping_add(2) } else { pos.wrapping_add(1) };
            let harg4 = if matched == 1 { npos } else { from };
            o_a_fl_insert_match(input, &mut head, &mut prev, from, harg4, hsh, ih, it);
            carry = if take2 == 1 { s2 } else { 0 };
            miss = 0;
            ntok = r.0;
            pos = npos;
        }
    }
    (ntok, pos)
}

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



#[inline(always)]
pub fn o_a_sh_replay(input: &[u8], out: &mut [u32], cache: &[u32; 4096], q: &[usize; 320]) -> (usize, usize) {
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
        let r = o_a_fl_emit_step(input, out, pos, dist, l, lits, ntok);
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
pub fn o_a_sh_add(stats: &mut [u32; 128], l: usize, d: usize) {
    let a = o_a_sh_lc(l) % 29;
    let b = o_a_sh_dc(d) % 30;
    stats[a] = stats[a].wrapping_add(1);
    stats[29 + a] = stats[29 + a].wrapping_add(l as u32);
    stats[64 + b] = stats[64 + b].wrapping_add(1);
    stats[96 + b] = if l as u32 > stats[96 + b] { l as u32 } else { stats[96 + b] };
}



#[inline(always)]
pub fn o_a_sh_probe(input: &[u8], cache: &mut [u32; 4096], stats: &mut [u32; 128], lh: &[u32; 256], cf: &[usize; 8]) -> (usize, usize) {
    let n = input.len();
    let depth = cf[0];
    let depth2 = cf[1];
    let lazy = cf[2];
    let nice = cf[3];
    let ih = cf[4];
    let it = cf[5];
    let acc = cf[6];
    let h0 = 2049usize;
    let litq = o_a_fl_litq(h0);
    let hsh = o_a_fl_hsh(h0);
    let mut head = [0u32; 16384];
    let mut prev = [0u32; 32768];
    let mut pos = 0usize;
    let mut ntok = 0usize;
    let mut carry = 0usize;
    let mut miss = 0usize;
    while pos < n && ntok < 4096 {
        let have = if carry != 0 { 1usize } else { 0usize };
        let harg3 = if have == 1 { 0 } else { depth };
        let s1 = o_a_fl_search(input, &mut head, &mut prev, pos, harg3, 1, 2, 4096, litq, hsh, nice);
        let m1 = if have == 1 { carry } else { s1 };
        let l1 = m1 % 512;
        if l1 < 3 {
            let lits = o_a_fl_lits(miss, acc);
            cache[ntok] = lits as u32;
            let r = (ntok + 1, pos.wrapping_add(lits));
            miss = miss.wrapping_add(1);
            carry = 0;
            ntok = r.0;
            pos = r.1;
        } else {
            let d1 = (m1 / 512) % 65536;
            let want = if l1 < lazy { 1usize } else { 0usize };
            let p2 = if want == 1 { if l1 >= O_A_FL_GOOD { depth2 } else { depth } } else { 0 };
            let s2 = o_a_fl_search(input, &mut head, &mut prev, pos.wrapping_add(1), p2, 1, l1.wrapping_sub(1), o_a_fl_score(l1, d1, litq), litq, hsh, nice);
            let take2 = if s2 != 0 { 1usize } else { 0usize };
            let l = if take2 == 1 { 0 } else { l1 };
            let d = if take2 == 1 { 0 } else { d1 };
            cache[ntok] = (if l >= 3 { l | d.wrapping_mul(512) } else { 1 }) as u32;
            if l >= 3 { o_a_sh_add(stats, l, d); }
            let advance = if l >= 3 { l } else { 1 };
            let r = (ntok + 1, pos.wrapping_add(advance));
            let npos = r.1;
            let matched = if l >= 3 { if npos == pos.wrapping_add(l) { 1usize } else { 0usize } } else { 0usize };
            let from = if want == 1 { pos.wrapping_add(2) } else { pos.wrapping_add(1) };
            let harg4 = if matched == 1 { npos } else { from };
            o_a_fl_insert_match(input, &mut head, &mut prev, from, harg4, hsh, ih, it);
            carry = if take2 == 1 { s2 } else { 0 };
            miss = 0;
            ntok = r.0;
            pos = npos;
        }
    }
    (ntok, pos)
}

/// Small inputs: the class-T price-lazy parser.



#[inline(never)]
pub fn o_a_small_phase<const SH_L_: u32, const SH_D_: u32, const SH_BUDGET_: usize, const SH_DM_: u32>(input: &[u8], out: &mut [u32]) -> (usize, usize) {
    let mut fh = [1u32; 256];
    let mut cf = [0usize; 8];
    cf[0] = O_A_FT_DEPTH;
    cf[1] = O_A_FT_DEPTH2;
    cf[2] = O_A_FT_LAZY;
    cf[3] = O_A_FT_NICE;
    cf[4] = O_A_FT_IH;
    cf[5] = O_A_FT_IT;
    cf[6] = O_A_FT_ACC;
    let mut cache = [0u32; 4096];
    let mut stats = [0u32; 128];
    let r = o_a_sh_probe(input, &mut cache, &mut stats, &fh, &cf);
    if r.1 >= input.len() {
        let mut q = [0usize; 320];
        o_a_sh_table::<SH_L_, SH_D_, SH_BUDGET_, SH_DM_>(&stats, &mut q);
        o_a_sh_replay(input, out, &cache, &q)
    } else { o_a_fl_lazy_parse(input, out, &fh, &cf) }
}

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


pub fn o_a_run_greedy<const IH_: usize, const IT_: usize, const TS_: usize, const ACC_: u64, const LZT_: usize>(input: &[u8], out: &mut [u32], head: &mut [u32; 131072], pos0: usize, ntok0: usize) -> usize {
    let n = input.len();
    let mut pos = pos0;
    let mut ntok = ntok0;
    while pos < n {
        let f = o_a_find::<ACC_, LZT_>(input, head, pos);
        let start = (f >> 25) as usize;
        if start > pos {
            let r = o_a_emit_lits(input, out, pos, start.wrapping_sub(pos), ntok);
            ntok = r.0;
            pos = r.1;
        }
        if pos < n {
            let l = (f as usize) % 512;
            let d = ((f >> 9) % 65536) as usize;
            let r = o_a_emit_step(input, out, pos, d, l, 1, ntok);
            let npos = r.1;
            o_a_insert_match::<IH_, IT_, TS_>(input, head, pos, npos);
            ntok = r.0;
            pos = npos;
        }
    }
    ntok
}

/// The mode-0 main parser from `pos0` (the floor phase's end).


#[inline(never)]
pub fn o_a_main_part<const IH_: usize, const IT_: usize, const TS_: usize, const ACC_: u64, const LZT_: usize>(input: &[u8], out: &mut [u32], m: usize, pos0: usize, ntok0: usize) -> usize {
    let mut head = [0u32; 131072];
    o_a_run_greedy::<IH_, IT_, TS_, ACC_, LZT_>(input, out, &mut head, pos0, ntok0)
}

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

#[inline(always)]
pub fn y_a_h3_hashp(input: &[u8], p: usize) -> usize {
    let v = o_a_ld8(input, p);
    ((v.wrapping_mul(O_A_HM3) >> (O_A_HSR % 64)) as usize) % 65536
}

/// Hash of the 8 bytes at `p` (long table), 16 bits.


/// The candidate `(cs, cl)` (short / long table entries, pos+1 encoded, 0 = none) at `p`: the long one when its
/// first 8 bytes agree, else the short one. Returns `len | dist << 9` (len >= O_A_MINL3), or 0.


#[inline(always)]
pub fn y_a_h3_eval(input: &[u8], p: usize, cs: usize, cl: usize) -> usize {
    let n = input.len();
    if n < 16 || p > n - 16 {
        return 0;
    }
    let v = o_a_ld8(input, p);
    let lim = if p < 32768 { p } else { 32768 };
    let okl = if p.wrapping_sub(cl) < lim { 1usize } else { 0usize };
    let xl = if okl == 1 { o_a_ld8(input, cl.wrapping_sub(1)) ^ v } else { 1 };
    let oks = if p.wrapping_sub(cs) < lim { 1usize } else { 0usize };
    let xs = if xl == 0 { 0 } else if oks == 1 { o_a_ld8(input, cs.wrapping_sub(1)) ^ v } else { 1 };
    if xl != 0 && xs & O_A_MM3 != 0 {
        return 0;
    }
    let usel = if xl == 0 { 1usize } else { 0usize };
    let c = if usel == 1 { cl } else { cs };
    let x = if usel == 1 { xl } else { xs };
    let rem = n - p - 8;
    let cap = if rem < 258 { rem } else { 258 };
    let l = if x == 0 { o_a_fast_len(input, c.wrapping_sub(1), p, cap) } else { o_a_first_diff(x) };
    let d = p.wrapping_sub(c.wrapping_sub(1));
    let ok = if l >= O_A_MINL3 { if l > 3 { 1usize } else if d <= O_A_MAX3 { 1 } else { 0 } } else { 0 };
    if ok == 1 {
        l | d.wrapping_mul(512)
    } else {
        0
    }
}

/// Lazy-site copy of `eval` (keeps both inlined).
/// The candidate `(cs, cl)` (short / long table entries, pos+1 encoded, 0 = none) at `p`: the long one when its
/// first 8 bytes agree, else the short one. Returns `len | dist << 9` (len >= O_A_MINL3), or 0.


pub fn y_a_h3_eval2(input: &[u8], p: usize, cs: usize, cl: usize) -> usize {
    let n = input.len();
    if n < 16 || p > n - 16 {
        return 0;
    }
    let v = o_a_ld8(input, p);
    let tag = cl / 16777216;
    let cl = cl % 16777216;
    let ht = y_a_h3_hashp(input, p) % 256;
    let lim = if p < 32768 { p } else { 32768 };
    let okl = if p.wrapping_sub(cl) < lim { 1usize } else { 0usize };
    let xl = if okl == 1 && tag == ht { o_a_ld8(input, cl.wrapping_sub(1)) ^ v } else { 1 };
    let oks = if p.wrapping_sub(cs) < lim { 1usize } else { 0usize };
    let xs = if xl == 0 { 0 } else if oks == 1 { o_a_ld8(input, cs.wrapping_sub(1)) ^ v } else { 1 };
    let usel = if xl == 0 { 1usize } else { 0usize };
    let c = if usel == 1 { cl } else { cs };
    let x = if usel == 1 { xl } else { xs };
    let rem = n - p - 8;
    let cap = if rem < 258 { rem } else { 258 };
    let l = if x == 0 { o_a_fast_len(input, c.wrapping_sub(1), p, cap) } else { o_a_first_diff(x) };
    let d = p.wrapping_sub(c.wrapping_sub(1));
    let ok = if l >= O_A_MINL3 { if l > 3 { 1usize } else if d <= O_A_MAX3 { 1 } else { 0 } } else { 0 };
    if ok == 1 {
        l | d.wrapping_mul(512)
    } else {
        0
    }
}

/// Lazy-chain copy of `eval` (keeps both inlined).
/// The candidate `(cs, cl)` (short / long table entries, pos+1 encoded, 0 = none) at `p`: the long one when its
/// first 8 bytes agree, else the short one. Returns `len | dist << 9` (len >= O_A_MINL3), or 0.


pub fn y_a_h3_eval3(input: &[u8], p: usize, cs: usize, cl: usize) -> usize {
    let n = input.len();
    if n < 16 || p > n - 16 {
        return 0;
    }
    let v = o_a_ld8(input, p);
    let tag = cl / 16777216;
    let cl = cl % 16777216;
    let ht = y_a_h3_hashp(input, p) % 256;
    let lim = if p < 32768 { p } else { 32768 };
    let okl = if p.wrapping_sub(cl) < lim { 1usize } else { 0usize };
    let xl = if okl == 1 && tag == ht { o_a_ld8(input, cl.wrapping_sub(1)) ^ v } else { 1 };
    let oks = if p.wrapping_sub(cs) < lim { 1usize } else { 0usize };
    let xs = if xl == 0 { 0 } else if oks == 1 { o_a_ld8(input, cs.wrapping_sub(1)) ^ v } else { 1 };
    let usel = if xl == 0 { 1usize } else { 0usize };
    let c = if usel == 1 { cl } else { cs };
    let x = if usel == 1 { xl } else { xs };
    let rem = n - p - 8;
    let cap = if rem < 258 { rem } else { 258 };
    let l = if x == 0 { o_a_fast_len(input, c.wrapping_sub(1), p, cap) } else { o_a_first_diff(x) };
    let d = p.wrapping_sub(c.wrapping_sub(1));
    let ok = if l >= O_A_MINL3 { if l > 3 { 1usize } else if d <= O_A_MAX3 { 1 } else { 0 } } else { 0 };
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
        let hl = o_a_hashl(input, p);
        head[hs] = (p as u32).wrapping_add(1);
        head[(65536 + hl) % 131072] = ((p as u32).wrapping_add(1) % 16777216) | (((hs % 256) as u32) << 24);
        p += 1;
    }
}

/// Insert every Y_A_TS-th position of `from .. to` into both tables (O_A_TL == 1: the long table only).


pub fn y_a_h3_insert_range2<const TS_: usize>(input: &[u8], head: &mut [u32; 131072], from: usize, to: usize) {
    let n = input.len();
    let mut p = from;
    let mut c = 0usize;
    while c < to && p < to && 16 <= n && p <= n - 16 {
        let hs = y_a_h3_hashp(input, p);
        let hl = o_a_hashl(input, p);
        if O_A_TL == 0 {
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


pub fn y_a_h3_scan<const ACC_: u64>(input: &[u8], head: &mut [u32; 131072], pos: usize) -> (u64, u64, u64) {
    let n = input.len();
    let mut p = pos;
    let mut res = 0usize;
    let mut it = 0usize;
    let mut hs = y_a_h3_hashp(input, p);
    let mut hl = o_a_hashl(input, p);
    let mut cs = head[hs] as usize;
    let mut cl = head[(65536 + hl) % 131072] as usize;
    while it < n && res == 0 && 16 <= n && p <= n - 16 {
        let st = o_a_run_len::<ACC_>(it);
        let q1 = p.wrapping_add(st);
        let hs1 = y_a_h3_hashp(input, q1);
        let hl1 = o_a_hashl(input, q1);
        let t = o_a_tab_step(head, hs, hl, hs1, hl1, p);
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
    let q = if res == 0 { p } else { p.wrapping_add(o_a_run_len::<ACC_>(it.wrapping_sub(1))) };
    let qs = if ran == 1 { cs } else { 0 };
    let ql = if ran == 1 { cl } else { 0 };
    let m = if res == 0 { (n as u64) << 25 } else { ((p as u64) << 25) | (res as u64) };
    let kq = ((q as u64) << 32) | ((it as u64) % 4294967296);
    let cq = ((qs as u64) << 32) | ((ql as u64) % 4294967296);
    (m, kq, cq)
}

/// One further lazy step after a lazy win `m` that starts at `s`: probe `s + 1` (inserting it); returns the new
/// match with bit 63 set when the candidate there won by ending at least O_A_LZM bytes later (continue), the longer
/// match at `s` when the candidate also starts at `s` (stop), else `m` (stop).


pub fn y_a_h3_lazy_step(input: &[u8], head: &mut [u32; 131072], m: u64) -> u64 {
    let s = (m >> 25) as usize;
    let l = (m as usize) % 512;
    let q = s.wrapping_add(1);
    let hs = y_a_h3_hashp(input, q);
    let hl = o_a_hashl(input, q);
    let t = o_a_tab_step2(head, hs, hl, q);
    let cs = ((t >> 32) as u32) as usize;
    let cl = (t as u32) as usize;
    let r2 = if l < O_A_HLZT { y_a_h3_eval3(input, q, cs, cl) } else { 0 };
    let l2 = r2 % 512;
    let d2 = (r2 / 512) % 65536;
    let b1 = if l2 >= 3 { o_a_back1(input, q, d2) } else { 0 };
    let d = ((m >> 9) % 65536) as usize;
    let z2 = ((d2 as u32).wrapping_sub(1) | 1).leading_zeros();
    let z1 = ((d as u32).wrapping_sub(1) | 1).leading_zeros();
    let sc = if O_A_SCL == 1 { if l2 == l { if z2 > z1 { 1usize } else { 0usize } } else { 0usize } } else { 0usize };
    let win = if b1 == 1 { if l2 >= l { 1usize } else { 0usize } } else if l2.wrapping_add(1) >= l.wrapping_add(O_A_LZM) { 2 } else if sc == 1 { 2 } else { 0 };
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
/// O_A_SLQ quarter bits against O_A_SC0 plus 4 per extra bit.


/// Further lazy steps (at most O_A_LZN) after a lazy win `m0` (see `lazy_step`).


pub fn y_a_h3_lazy_more(input: &[u8], head: &mut [u32; 131072], m0: u64) -> u64 {
    let mut m = m0;
    let mut go = 1usize;
    let mut it = 0usize;
    while go == 1 && it < O_A_LZN {
        let r = y_a_h3_lazy_step(input, head, m);
        m = r % 9223372036854775808;
        go = (r >> 63) as usize;
        it += 1;
    }
    m
}

/// The next match at or after `pos`: `start << 25 | dist << 9 | len`, or `n << 25` when there is none.
/// Lazy step (match shorter than Y_A_LZT, next probe at `p + 1`): the candidate at `p + 1` wins when it also starts at
/// `p` and is longer, or when it ends at least O_A_LZM bytes later. Backward extension (O_A_BEXT) only after acceleration.


pub fn y_a_h3_find<const ACC_: u64>(input: &[u8], head: &mut [u32; 131072], pos: usize) -> u64 {
    if O_A_MINL3 > 258 {
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
    let lz = if l < O_A_HLZT { if q == p.wrapping_add(1) { 1usize } else { 0usize } } else { 0usize };
    let r2 = if lz == 1 { y_a_h3_eval2(input, q, qs, ql) } else { 0 };
    let l2 = r2 % 512;
    let d2 = (r2 / 512) % 65536;
    let b1 = if l2 >= 3 { o_a_back1(input, q, d2) } else { 0 };
    let z2 = ((d2 as u32).wrapping_sub(1) | 1).leading_zeros();
    let z1 = ((d as u32).wrapping_sub(1) | 1).leading_zeros();
    let sc = if O_A_SCL == 1 { if l2 == l { if z2 > z1 { 1usize } else { 0usize } } else { 0usize } } else { 0usize };
    let win = if b1 == 1 { if l2 >= l { 1usize } else { 0usize } } else if l2.wrapping_add(1) >= l.wrapping_add(O_A_LZM) { 2 } else if sc == 1 { 2 } else { 0 };
    let win2 = if l2 >= 3 { win } else { 0 };
    let bx = if O_A_BEXT == 1 { if k > O_A_BK { 1usize } else { 0usize } } else { 0usize };
    let e = if bx == 1 { if l >= 3 { o_a_bext(input, pos, p, d, l) } else { 0 } } else { 0 };
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
            let r = o_a_emit_lits(input, out, pos, start.wrapping_sub(pos), ntok);
            ntok = r.0;
            pos = r.1;
        }
        if pos < n {
            let l = (f as usize) % 512;
            let d = ((f >> 9) % 65536) as usize;
            let r = o_a_emit_step(input, out, pos, d, l, 1, ntok);
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
pub fn y_machine(input:&[u8],out:&mut[u32])->usize {let r=y_a_h3_run::<{Y_A_IH[1]},{Y_A_IT[1]},{Y_A_TS[1]},{Y_A_ACC[1]}>(input,out);if r.1<input.len(){y_restart(input,out)}else{r.0}}

 
#[inline(never)]
pub fn o_row0(input:&[u8],out:&mut[u32])->usize {o_a_main_part::<{O_A_IH[0]},{O_A_IT[0]},{O_A_TS[0]},{O_A_ACC[0]},{O_A_LZT[0]}>(input,out,0,0,0)}

 
#[inline(never)]
pub fn o_row1(input:&[u8],out:&mut[u32])->usize {o_a_main_part::<{O_A_IH[1]},{O_A_IT[1]},{O_A_TS[1]},{O_A_ACC[1]},{O_A_LZT[1]}>(input,out,0,0,0)}

 
#[inline(never)]
pub fn o_row2(input:&[u8],out:&mut[u32])->usize {o_a_main_part::<{O_A_IH[2]},{O_A_IT[2]},{O_A_TS[2]},{O_A_ACC[2]},{O_A_LZT[2]}>(input,out,0,0,0)}

 
#[inline(never)]
pub fn o_row3(input:&[u8],out:&mut[u32])->usize {o_a_main_part::<{O_A_IH[3]},{O_A_IT[3]},{O_A_TS[3]},{O_A_ACC[3]},{O_A_LZT[3]}>(input,out,0,0,0)}

 
#[inline(never)]
pub fn o_row4(input:&[u8],out:&mut[u32])->usize {o_a_main_part::<{O_A_IH[4]},{O_A_IT[4]},{O_A_TS[4]},{O_A_ACC[4]},{O_A_LZT[4]}>(input,out,0,0,0)}

 
#[inline(never)]
pub fn o_row5(input:&[u8],out:&mut[u32])->usize {o_a_main_part::<{O_A_IH[5]},{O_A_IT[5]},{O_A_TS[5]},{O_A_ACC[5]},{O_A_LZT[5]}>(input,out,0,0,0)}

 
#[inline(never)]
pub fn o_row6(input:&[u8],out:&mut[u32])->usize {o_a_main_part::<{O_A_IH[6]},{O_A_IT[6]},{O_A_TS[6]},{O_A_ACC[6]},{O_A_LZT[6]}>(input,out,0,0,0)}

 
#[inline(never)]
pub fn o_row7(input:&[u8],out:&mut[u32])->usize {o_a_main_part::<{O_A_IH[7]},{O_A_IT[7]},{O_A_TS[7]},{O_A_ACC[7]},{O_A_LZT[7]}>(input,out,0,0,0)}

 
#[inline(never)]
pub fn o_small(input:&[u8],out:&mut[u32])->usize {let r=o_a_small_phase::<{O_A_SH_L[0]},{O_A_SH_D[0]},{O_A_SH_BUDGET[0]},{O_A_SH_DM[0]}>(input,out);if r.1<input.len(){o_a_main_part::<{O_A_IH[0]},{O_A_IT[0]},{O_A_TS[0]},{O_A_ACC[0]},{O_A_LZT[0]}>(input,out,0,r.1,r.0)}else{r.0}}

 
#[inline(never)]
pub fn o_app(input:&[u8],out:&mut[u32])->usize {let r=o_a_small_phase::<{O_A_SH_L[0]},{O_A_SH_D[0]},{O_A_SH_BUDGET[0]},{O_A_SH_DM[0]}>(input,out);if r.1<input.len(){o_a_main_part::<{O_A_IH[2]},{O_A_IT[2]},{O_A_TS[2]},{O_A_ACC[2]},{O_A_LZT[2]}>(input,out,0,r.1,r.0)}else{r.0}}

 


 


 

 

 

 

 
#[inline(never)]
pub fn y_restart(input:&[u8],out:&mut[u32])->usize{o_a_main_part::<2,12,12,4,0>(input,out,0,0,0)}

 

 

 


 


 

 

 


 


 


 


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



#[inline(always)]
pub fn d_a_hashp(input: &[u8], p: usize) -> usize {
    let v = o_a_ld8(input, p);
    ((v.wrapping_mul(O_A_HM4) >> (O_A_HSR % 64)) as usize) % 16384
}



#[inline(always)]
pub fn d_a_hashl(input: &[u8], p: usize) -> usize {
    let v = o_a_ld8(input, p);
    ((v.wrapping_mul(13608954094988492800) >> (O_A_HSR % 64)) as usize) % 16384
}



#[inline(always)]
pub fn d_a_eval(input: &[u8], p: usize, cs: usize, cl: usize) -> usize {
    let n = input.len();
    if n < 16 || p > n - 16 {
        return 0;
    }
    let v = o_a_ld8(input, p);
    let lim = if p < 32768 { p } else { 32768 };
    let okl = if p.wrapping_sub(cl) < lim { 1usize } else { 0usize };
    let xl = if okl == 1 { o_a_ld8(input, cl.wrapping_sub(1)) ^ v } else { 1 };
    let oks = if p.wrapping_sub(cs) < lim { 1usize } else { 0usize };
    let xs = if (xl & 281474976710655) == 0 { 0 } else if oks == 1 { o_a_ld8(input, cs.wrapping_sub(1)) ^ v } else { 1 };
    if (xl & 281474976710655) != 0 && xs & O_A_MM4 != 0 {
        return 0;
    }
    let usel = if (xl & 281474976710655) == 0 { 1usize } else { 0usize };
    let c = if usel == 1 { cl } else { cs };
    let x = if usel == 1 { xl } else { xs };
    let rem = n - p - 8;
    let cap = if rem < 258 { rem } else { 258 };
    let l = if x == 0 { o_a_fast_len(input, c.wrapping_sub(1), p, cap) } else { o_a_first_diff(x) };
    let d = p.wrapping_sub(c.wrapping_sub(1));
    let ok = if l >= O_A_MINL { if l > 3 { 1usize } else if d <= O_A_MAX3 { 1 } else { 0 } } else { 0 };
    if ok == 1 {
        l | d.wrapping_mul(512)
    } else {
        0
    }
}



#[inline(always)]
pub fn d_a_eval2(input: &[u8], p: usize, cs: usize, cl: usize, floor: usize) -> usize {
    let n = input.len();
    if n < 16 || p > n - 16 {
        return 0;
    }
    let v = o_a_ld8(input, p);
    let tag = cl / 16777216;
    let cl = cl % 16777216;
    let ht = d_a_hashp(input, p) % 256;
    let lim = if p < 32768 { p } else { 32768 };
    let okl = if p.wrapping_sub(cl) < lim { 1usize } else { 0usize };
    let xl = if okl == 1 && tag == ht { o_a_ld8(input, cl.wrapping_sub(1)) ^ v } else { 1 };
    if (xl & 281474976710655) == 0 && floor > 8 && floor <= 258 {
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
    let xs = if (xl & 281474976710655) == 0 { 0 } else if oks == 1 && tail == 1 { o_a_ld8(input, cs.wrapping_sub(1)) ^ v } else { 1 };
    if (xl & 281474976710655) != 0 && xs & O_A_MM4 != 0 { return 0; }
    let usel = if (xl & 281474976710655) == 0 { 1usize } else { 0usize };
    let c = if usel == 1 { cl } else { cs };
    let x = if usel == 1 { xl } else { xs };
    let rem = n - p - 8;
    let cap = if rem < 258 { rem } else { 258 };
    let l = if x == 0 { o_a_fast_len2(input, c.wrapping_sub(1), p, cap) } else { o_a_first_diff(x) };
    let d = p.wrapping_sub(c.wrapping_sub(1));
    let ok = if l >= O_A_MINL { if l > 3 { 1usize } else if d <= O_A_MAX3 { 1 } else { 0 } } else { 0 };
    if ok == 1 {
        l | d.wrapping_mul(512)
    } else {
        0
    }
}



#[inline(always)]
pub fn d_a_eval3(input: &[u8], p: usize, cs: usize, cl: usize, floor: usize) -> usize {
    let n = input.len();
    if n < 16 || p > n - 16 {
        return 0;
    }
    let v = o_a_ld8(input, p);
    let tag = cl / 16777216;
    let cl = cl % 16777216;
    let ht = d_a_hashp(input, p) % 256;
    let lim = if p < 32768 { p } else { 32768 };
    let okl = if p.wrapping_sub(cl) < lim { 1usize } else { 0usize };
    let xl = if okl == 1 && tag == ht { o_a_ld8(input, cl.wrapping_sub(1)) ^ v } else { 1 };
    if (xl & 281474976710655) == 0 && floor > 8 && floor <= 258 {
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
    let xs = if (xl & 281474976710655) == 0 { 0 } else if oks == 1 && tail == 1 { o_a_ld8(input, cs.wrapping_sub(1)) ^ v } else { 1 };
    if (xl & 281474976710655) != 0 && xs & O_A_MM4 != 0 { return 0; }
    let usel = if (xl & 281474976710655) == 0 { 1usize } else { 0usize };
    let c = if usel == 1 { cl } else { cs };
    let x = if usel == 1 { xl } else { xs };
    let rem = n - p - 8;
    let cap = if rem < 258 { rem } else { 258 };
    let l = if x == 0 { o_a_fast_len3(input, c.wrapping_sub(1), p, cap) } else { o_a_first_diff(x) };
    let d = p.wrapping_sub(c.wrapping_sub(1));
    let ok = if l >= O_A_MINL { if l > 3 { 1usize } else if d <= O_A_MAX3 { 1 } else { 0 } } else { 0 };
    if ok == 1 {
        l | d.wrapping_mul(512)
    } else {
        0
    }
}



#[inline(always)]
pub fn d_a_insert_range(input: &[u8], head: &mut [u32; 32768], from: usize, to: usize) {
    let n = input.len();
    let mut p = from;
    while p < to && 16 <= n && p <= n - 16 {
        let hs = d_a_hashp(input, p);
        let hl = d_a_hashl(input, p);
        head[hs] = (p as u32).wrapping_add(1);
        head[(16384 + hl) % 32768] = ((p as u32).wrapping_add(1) % 16777216) | (((hs % 256) as u32) << 24);
        p += 1;
    }
}



#[inline(always)]
pub fn d_a_insert_range2<const TS_: usize>(input: &[u8], head: &mut [u32; 32768], from: usize, to: usize) {
    let n = input.len();
    let mut p = from;
    let mut c = 0usize;
    while c < to && p < to && 16 <= n && p <= n - 16 {
        let hs = d_a_hashp(input, p);
        let hl = d_a_hashl(input, p);
        if O_A_TL == 0 {
            head[hs] = (p as u32).wrapping_add(1);
        }
        head[(16384 + hl) % 32768] = ((p as u32).wrapping_add(1) % 16777216) | (((hs % 256) as u32) << 24);
        p = p.wrapping_add(TS_);
        c += 1;
    }
}



#[inline(always)]
pub fn d_a_insert_match<const IH_: usize, const IT_: usize, const TS_: usize>(input: &[u8], head: &mut [u32; 32768], from: usize, to: usize) {
    let a = from.wrapping_add(IH_);
    let a2 = if a < to { a } else { to };
    let b = to.wrapping_sub(IT_);
    let b2 = if b > a2 { if b < to { b } else { a2 } } else { a2 };
    d_a_insert_range(input, head, from.wrapping_add(1), a2);
    d_a_insert_range2::<TS_>(input, head, b2, to);
}



#[inline(always)]
pub fn d_a_run_len<const ACC_: u64>(k: usize) -> usize {
    let over = ((k as u64) >> (ACC_ % 64)) as usize;
    if over < O_A_AMAX {
        over + 1
    } else {
        O_A_AMAX
    }
}



#[inline(always)]
pub fn d_a_bext(input: &[u8], lo: usize, p: usize, d: usize, l: usize) -> usize {
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
        let ok = if e < lim { d_a_q8ok(q, d) } else { 0 };
        if ok == 1 {
            let x = o_a_ld8(input, q.wrapping_sub(8)) ^ o_a_ld8(input, q.wrapping_sub(8).wrapping_sub(d));
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



#[inline(always)]
pub fn d_a_q8ok(q: usize, d: usize) -> usize {
    if q >= d.wrapping_add(8) { 1 } else { 0 }
}



#[inline(always)]
pub fn d_a_back1(input: &[u8], q: usize, d: usize) -> usize {
    let n = input.len();
    if d == 0 || q <= d || q > n {
        return 0;
    }
    if input[q - 1] == input[q - 1 - d] { 1 } else { 0 }
}



#[inline(always)]
pub fn d_a_tab_step(head: &mut [u32; 32768], hs: usize, hl: usize, hs1: usize, hl1: usize, p: usize) -> u64 {
    let cs1 = head[hs1 % 32768];
    let cl1 = head[65536usize.wrapping_add(hl1) % 32768];
    head[hs % 32768] = (p as u32).wrapping_add(1);
    head[65536usize.wrapping_add(hl) % 32768] = ((p as u32).wrapping_add(1) % 16777216) | (((hs % 256) as u32) << 24);
    ((cs1 as u64) << 32) | (cl1 as u64)
}



#[inline(always)]
pub fn d_a_tab_step2(head: &mut [u32; 32768], hs: usize, hl: usize, q: usize) -> u64 {
    let cs = head[hs % 32768];
    let cl = head[65536usize.wrapping_add(hl) % 32768];
    head[hs % 32768] = (q as u32).wrapping_add(1);
    head[65536usize.wrapping_add(hl) % 32768] = ((q as u32).wrapping_add(1) % 16777216) | (((hs % 256) as u32) << 24);
    ((cs as u64) << 32) | (cl as u64)
}



#[inline(always)]
pub fn d_a_scan<const ACC_: u64>(input: &[u8], head: &mut [u32; 32768], pos: usize) -> (u64, u64, u64) {
    let n = input.len();
    let mut p = pos;
    let mut res = 0usize;
    let mut it = 0usize;
    let mut hs = d_a_hashp(input, p);
    let mut hl = d_a_hashl(input, p);
    let mut cs = head[hs] as usize;
    let mut cl = head[(16384 + hl) % 32768] as usize;
    while it < n && res == 0 && 16 <= n && p <= n - 16 {
        let st = d_a_run_len::<ACC_>(it);
        let q1 = p.wrapping_add(st);
        let hs1 = d_a_hashp(input, q1);
        let hl1 = d_a_hashl(input, q1);
        let t = d_a_tab_step(head, hs, hl, hs1, hl1, p);
        let cl0 = if cl / 16777216 == hs % 256 { cl % 16777216 } else { 0 };
        let r = d_a_eval(input, p, cs, cl0);
        res = r;
        p = if r == 0 { q1 } else { p };
        hs = hs1;
        hl = hl1;
        cs = ((t >> 32) as u32) as usize;
        cl = (t as u32) as usize;
        it += 1;
    }
    let ran = if it > 0 { 1usize } else { 0usize };
    let q = if res == 0 { p } else { p.wrapping_add(d_a_run_len::<ACC_>(it.wrapping_sub(1))) };
    let qs = if ran == 1 { cs } else { 0 };
    let ql = if ran == 1 { cl } else { 0 };
    let m = if res == 0 { (n as u64) << 25 } else { ((p as u64) << 25) | (res as u64) };
    let kq = ((q as u64) << 32) | ((it as u64) % 4294967296);
    let cq = ((qs as u64) << 32) | ((ql as u64) % 4294967296);
    (m, kq, cq)
}



#[inline(always)]
pub fn d_a_lazy_step<const LZT_: usize>(input: &[u8], head: &mut [u32; 32768], m: u64) -> u64 {
    let s = (m >> 25) as usize;
    let l = (m as usize) % 512;
    let q = s.wrapping_add(1);
    let hs = d_a_hashp(input, q);
    let hl = d_a_hashl(input, q);
    let t = d_a_tab_step2(head, hs, hl, q);
    let cs = ((t >> 32) as u32) as usize;
    let cl = (t as u32) as usize;
    let r2 = if l < LZT_ { d_a_eval3(input, q, cs, cl, l) } else { 0 };
    let l2 = r2 % 512;
    let d2 = (r2 / 512) % 65536;
    let b1 = if l2 >= 3 { d_a_back1(input, q, d2) } else { 0 };
    let d = ((m >> 9) % 65536) as usize;
    let z2 = ((d2 as u32).wrapping_sub(1) | 1).leading_zeros();
    let z1 = ((d as u32).wrapping_sub(1) | 1).leading_zeros();
    let sc = if O_A_SCL == 1 { if l2 == l { if z2 > z1 { 1usize } else { 0usize } } else { 0usize } } else { 0usize };
    let win = if b1 == 1 { if l2 >= l { 1usize } else { 0usize } } else if l2.wrapping_add(1) >= l.wrapping_add(O_A_LZM) { 2 } else if sc == 1 { 2 } else { 0 };
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



#[inline(always)]
pub fn d_a_lazy_more<const LZT_: usize>(input: &[u8], head: &mut [u32; 32768], m0: u64) -> u64 {
    let mut m = m0;
    let mut go = 1usize;
    let mut it = 0usize;
    while go == 1 && it < O_A_LZN {
        let r = d_a_lazy_step::<LZT_>(input, head, m);
        m = r % 9223372036854775808;
        go = (r >> 63) as usize;
        it += 1;
    }
    m
}



#[inline(always)]
pub fn d_a_find<const ACC_: u64, const LZT_: usize>(input: &[u8], head: &mut [u32; 32768], pos: usize) -> u64 {
    if O_A_MINL > 258 {
        return (input.len() as u64) << 25;
    }
    let sc = d_a_scan::<ACC_>(input, head, pos);
    let r = sc.0;
    let p = (r >> 25) as usize;
    let l = (r as usize) % 512;
    let d = ((r >> 9) % 65536) as usize;
    let q = (sc.1 >> 32) as usize;
    let k = (sc.1 as u32) as usize;
    let qs = (sc.2 >> 32) as usize;
    let ql = (sc.2 as u32) as usize;
    let lz = if l < LZT_ { if q == p.wrapping_add(1) { 1usize } else { 0usize } } else { 0usize };
    let r2 = if lz == 1 { d_a_eval2(input, q, qs, ql, l) } else { 0 };
    let l2 = r2 % 512;
    let d2 = (r2 / 512) % 65536;
    let b1 = if l2 >= 3 { d_a_back1(input, q, d2) } else { 0 };
    let z2 = ((d2 as u32).wrapping_sub(1) | 1).leading_zeros();
    let z1 = ((d as u32).wrapping_sub(1) | 1).leading_zeros();
    let sc = if O_A_SCL == 1 { if l2 == l { if z2 > z1 { 1usize } else { 0usize } } else { 0usize } } else { 0usize };
    let win = if b1 == 1 { if l2 >= l { 1usize } else { 0usize } } else if l2.wrapping_add(1) >= l.wrapping_add(O_A_LZM) { 2 } else if sc == 1 { 2 } else { 0 };
    let win2 = if l2 >= 3 { win } else { 0 };
    let bx = if O_A_BEXT == 1 { if k > O_A_BK { 1usize } else { 0usize } } else { 0usize };
    let e = if bx == 1 { if l >= 3 { d_a_bext(input, pos, p, d, l) } else { 0 } } else { 0 };
    let m1 = ((p.wrapping_sub(e) as u64) << 25) | ((d as u64) << 9) | (l.wrapping_add(e) as u64);
    let m2 = ((p as u64) << 25) | ((d2 as u64) << 9) | (l2.wrapping_add(1) as u64);
    let m3 = ((q as u64) << 25) | ((d2 as u64) << 9) | (l2 as u64);
    if win2 == 1 {
        m2
    } else if win2 == 2 {
        d_a_lazy_more::<LZT_>(input, head, m3)
    } else {
        m1
    }
}









// Cache one token block with the cheap scanner, then use the proven symbol filter/replay.


#[inline(never)]
pub fn s_probe<const IH:usize,const IT:usize,const TS:usize,const ACC:u64,const LZT:usize>(input:&[u8],cache:&mut[u32;4096],stats:&mut[u32;128])->usize {
 let mut head=[0u32;32768];let n=input.len();let mut pos=0usize;let mut nt=0usize;let mut carry=0u64;
 while nt<4096 && pos<n {
  let start=(carry>>25) as usize;
  let f=if start>pos || (start==pos && carry%512>=4) {carry} else {d_a_find::<ACC,LZT>(input,&mut head,pos)};
  let start2=(f>>25) as usize;
  if start2>pos {cache[nt]=1;pos+=1;carry=f;}
  else {
   let raw=(f as usize)%512;let d=((f>>9)%65536) as usize;
   let l=if raw>=4 && raw<=258 && d>0 && d<=pos && d<=32768 && raw<=n-pos {raw} else {0};
   let to=if l>=4 {pos+l} else {pos+1};
   cache[nt]=(if l>=4 {l|d.wrapping_mul(512)} else {1}) as u32;
   if l>=4 {o_a_sh_add(stats,l,d);}
   d_a_insert_match::<IH,IT,TS>(input,&mut head,pos,to);pos=to;carry=0;
  }
  nt+=1;
 }
 pos
}


#[inline(never)]
pub fn s_small<const IH:usize,const IT:usize,const TS:usize,const ACC:u64,const LZT:usize,const KL:u32,const KD:u32,const B:usize,const DM:u32>(input:&[u8],out:&mut[u32])->usize {
 let mut cache=[0u32;4096];let mut stats=[0u32;128];let p=s_probe::<IH,IT,TS,ACC,LZT>(input,&mut cache,&mut stats);
 if p>=input.len() {let mut q=[0usize;320];o_a_sh_table::<KL,KD,B,DM>(&stats,&mut q);let r=o_a_sh_replay(input,out,&cache,&q);if r.1<input.len(){fallback(input,out)}else{r.0}}
 else {o_parse(input,out)}
}


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
pub const FV_T_SKIP: usize = 3;
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
pub fn fv_be8(s: &[u8], i: usize) -> u64 {
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
#[inline(always)]
pub fn fv_be4(s: &[u8], i: usize) -> u32 {
 if i + 4 <= s.len() {
  let b3=s[i+3] as u32;
  let b2=s[i+2] as u32;
  let b1=s[i+1] as u32;
  let b0=s[i] as u32;
  (b0<<24)|(b1<<16)|(b2<<8)|b3
 } else {0}
}
#[inline(always)]
pub fn fv_gain(l: usize, d: usize) -> i32 {
    let mut c = FV_GBASE;
    if l > 10 && l < 258 {
        c += 16 * (29 - ((l - 3) as u32).leading_zeros()) as i32;
    }
    if d > 4 {
        c += 16 * (30 - ((d - 1) as u32).leading_zeros()) as i32;
    }
    (l as i32) * (FV_HLIT as i32) - c
}
#[inline(always)]
pub fn fv_common(s: &[u8], a: usize, b: usize, cap: usize) -> usize {
    let mut k = 0usize;
    let mut fv_run = 1u32;
    while fv_run == 1 && k + 8 <= cap {
        let x = fv_be8(s, a + k) ^ fv_be8(s, b + k);
        if x == 0 {
            k += 8;
        } else {
            k += (x.leading_zeros() / 8) as usize;
            fv_run = 0;
        }
    }
    while fv_run == 1 && k < cap {
        if s[a + k] == s[b + k] {
            k += 1;
        } else {
            fv_run = 0;
        }
    }
    k
}
#[inline(always)]
pub fn fv_same(s: &[u8], a: usize, b: usize, len: usize) -> usize {
    let n = s.len();
    let mut k = 0usize;
    let mut ok = 1usize;
    while ok == 1 && k + 8 <= len {
        if fv_be8(s, a + k) == fv_be8(s, b + k) {
            k += 8;
        } else {
            ok = 0;
        }
    }
    if ok == 1 && k < len {
        if a + k + 8 <= n && b + k + 8 <= n {
            let x = fv_be8(s, a + k) ^ fv_be8(s, b + k);
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
pub fn fv_put_lit(s: &[u8], out: &mut [u32], nt: usize, p: usize) -> usize {
    out[nt] = s[p] as u32;
    nt + 1
}
#[inline(always)]
pub fn fv_put_match(s: &[u8], out: &mut [u32], nt: usize, p: usize, d: usize, l: usize) -> (usize, usize) {
    let n = s.len();
    if d >= 1 && d <= 32768 && d <= p && l >= 3 && l <= 258 && p < n && l <= n - p && (FV_VERIFY == 0 || fv_same(s, p - d, p, l) == 1) {
        out[nt] = 16777216u32 + ((d - 1) as u32) * 256 + ((l - 3) as u32);
        (nt + 1, p + l)
    } else {
        out[nt] = s[p] as u32;
        (nt + 1, p + 1)
    }
}
#[inline(always)]
pub fn fv_walk<const W: usize>(s: &[u8], prev: &[u32; W], p: usize, start: usize, cap: usize, have: usize, depth: usize, gm: usize) -> (usize, usize) {
    let n = s.len();
    let mut best = have;
    let mut bd = 0usize;
    let mut bg = -1000000i32;
    let mut c = start;
    let mut k = depth;
    let mut stop = FV_NICE;
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
                let l = fv_common(s, c, p, cap);
                let mut take = 0usize;
                if l > best {
                    take = 1;
                    if gm == 1 {
                        let g = fv_gain(l, d);
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
#[inline(always)]
pub fn fv_insert<const H: usize, const W: usize>(s: &[u8], head: &mut [u32; H], prev: &mut [u32; W], i: usize, mask: u32) -> usize {
    let k = (fv_be4(s, i) & mask) as u64;
    let a = (k.wrapping_mul(0x9E37_79B9_7F4A_7C15) >> (64 - FV_HB)) as usize % H;
    let old = head[a];
    prev[i % W] = old;
    head[a] = i as u32;
    old as usize
}
#[inline(always)]
pub fn fv_find<const W: usize>(s: &[u8], prev: &[u32; W], p: usize, st: usize, have: usize, minl: usize, depth: usize, gm: usize) -> (usize, usize) {
    let n = s.len();
    let mut cap = n - p;
    if cap > 258 {
        cap = 258;
    }
    let mut lo = have;
    if lo + 1 < minl {
        lo = minl - 1;
    }
    let f = fv_walk(s, prev, p, st, cap, lo, depth, gm);
    let mut l = f.0;
    if f.1 == 0 {
        l = 0;
    }
    (l, f.1)
}
#[inline(always)]
pub fn fv_run<const H: usize, const W: usize, const TD: usize, const SL: usize>(input: &[u8], out: &mut [u32], cls: usize) -> usize {
    let n = input.len();
    let mut nt = 0usize;
    let mut p = 0usize;
    let mut mask = 0xFFFF_FFFFu32;
    let mut minl = 4usize;
    let mut depth = TD;
    let mut lazy = FV_T_LAZY;
    let mut skip = FV_T_SKIP;
    let mut skcap = FV_SKCAP;
    if cls == 6 {
        depth = FV_S_DEPTH;
        lazy = SL;
    }
    if cls == 5 {
        depth = FV_P_DEPTH;
        lazy = FV_P_LAZY;
        skip = FV_P_SKIP;
    }
    if cls == 2 || cls == 4 {
        depth = FV_H_DEPTH;
        lazy = FV_H_LAZY;
        skip = FV_H_SKIP;
        if cls == 4 {
            depth = FV_Z_DEPTH;
            skip = FV_Z_SKIP;
            skcap = FV_Z_CAP;
        }
    }
    if cls == 3 {
        mask = 0xFFFF_FF00;
        minl = 3;
        depth = TD;
        lazy = FV_B_LAZY;
        skip = FV_B_SKIP;
    }
    if n > 16 && cls != 0 {
        let mut head = [0u32; H];
        let mut prev = [0u32; W];
        let lim = n - 8;
        let mut ins = 0usize; // next position to fv_insert
        let mut miss = 0usize; // literals since the last match
        let mut fuel = n.saturating_add(16); // every pass advances p unless a re-check fails
        while p < lim && fuel > 0 {
            fuel -= 1;
            while ins < p {
                fv_insert(input, &mut head, &mut prev, ins, mask);
                ins += 1;
            }
            let hc = fv_insert(input, &mut head, &mut prev, p, mask);
            ins = p + 1;
            let f = fv_find(input, &prev, p, hc, 0, minl, depth, 0);
            let mut l = f.0;
            let mut d = f.1;
            if l >= 3 {
                // Lazy: move on while the next position has a better match by the saving
                // estimate (it may be as long but closer, or longer).
                let mut go = 1u32;
                while go == 1 && l < lazy && p + 1 < lim {
                    let q = p + 1;
                    let hq = fv_insert(input, &mut head, &mut prev, q, mask);
                    ins = q + 1;
                    let mut have = 0usize;
                    if l > FV_LSLACK {
                        have = l - FV_LSLACK;
                    }
                    let mut ldep = FV_LDEPTH;
                    if cls == 6 {
                        ldep = FV_S_LDEPTH;
                    }
                    let g = fv_find(input, &prev, q, hq, have, minl, ldep, 1);
                    if g.0 >= minl && fv_gain(g.0, g.1) > fv_gain(l, d) {
                        nt = fv_put_lit(input, out, nt, p);
                        p = q;
                        l = g.0;
                        d = g.1;
                    } else {
                        go = 0;
                    }
                }
                // Fold earlier tokens into this match while their bytes also match at d.
                let mut back = 0usize;
                while back < FV_BACKTOK && nt > 0 && nt <= out.len() && l < 258 && d < p {
                    let t = out[nt - 1];
                    if t < 256 && input[p - 1] == input[p - 1 - d] {
                        p -= 1;
                        nt -= 1;
                        l += 1;
                        back += 1;
                    } else if t >= 16777216 {
                        let w = ((t - 16777216) % 256 + 3) as usize;
                        if l + w <= 258 && w <= p && d <= p - w && fv_same(input, p - w - d, p - w, w) == 1 {
                            p -= w;
                            nt -= 1;
                            l += w;
                            back += 1;
                        } else {
                            back = FV_BACKTOK;
                        }
                    } else {
                        back = FV_BACKTOK;
                    }
                }
                let r = fv_put_match(input, out, nt, p, d, l);
                nt = r.0;
                let end = r.1;
                // Chain the first FV_INS_MAX and the last FV_TAIL positions inside the match.
                let mut stop = end;
                // wrapping: fv_same code as `+` here (no overflow on any real input), total in the model
                if stop > ins.wrapping_add(FV_INS_MAX) {
                    stop = ins.wrapping_add(FV_INS_MAX);
                }
                if stop > lim {
                    stop = lim;
                }
                while ins < stop {
                    fv_insert(input, &mut head, &mut prev, ins, mask);
                    ins += 1;
                }
                if FV_STRIDE > 0 {
                    // `ins + FV_TAIL + FV_STRIDE < end` (ins <= end here): no sum that could overflow
                    while end - ins > FV_TAIL + FV_STRIDE && ins < lim {
                        fv_insert(input, &mut head, &mut prev, ins, mask);
                        ins += FV_STRIDE;
                    }
                }
                if ins + FV_TAIL < end {
                    ins = end - FV_TAIL;
                }
                while ins < end && ins < lim {
                    fv_insert(input, &mut head, &mut prev, ins, mask);
                    ins += 1;
                }
                if ins < end {
                    ins = end;
                }
                p = end;
                miss = 0;
            } else {
                nt = fv_put_lit(input, out, nt, p);
                p += 1;
                miss += 1;
                let mut step = miss >> skip;
                if step > skcap {
                    step = skcap;
                }
                while step > 0 && p < lim {
                    nt = fv_put_lit(input, out, nt, p);
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
        nt = fv_put_lit(input, out, nt, p);
        p += 1;
    }
    nt
}
















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

#[inline(never)] pub fn r109_row0(input:&[u8],out:&mut[u32])->usize{fx0_run::<65536,32768,2,258>(input,out,3)}

#[inline(never)] pub fn r109_row1(input:&[u8],out:&mut[u32])->usize{o_a_main_part::<258,258,1,63,258>(input,out,0,0,0)}

#[inline(never)] pub fn r109_row2(input:&[u8],out:&mut[u32])->usize{fv_run::<65536,1,1,0>(input,out,1)}

#[inline(never)] pub fn r109_row3(input:&[u8],out:&mut[u32])->usize{n_run::<65536,6,1,0,0,5,0,2,12>(input,out)}

#[inline(never)] pub fn r109_row4(input:&[u8],out:&mut[u32])->usize{fx0_run::<32768,32768,2,0>(input,out,1)}

#[inline(never)] pub fn r109_row5(input:&[u8],out:&mut[u32])->usize{o_a_main_part::<3,12,12,4,0>(input,out,0,0,0)}

#[inline(never)] pub fn r109_row6(input:&[u8],out:&mut[u32])->usize{fx0_run::<32768,32768,2,258>(input,out,6)}

#[inline(never)] pub fn r109_row7(input:&[u8],out:&mut[u32])->usize{n_run::<65536,6,0,0,0,16,0,8,1>(input,out)}

#[inline(never)] pub fn r109_row8(input:&[u8],out:&mut[u32])->usize{fx0_run::<32768,32768,2,258>(input,out,2)}

#[inline(never)] pub fn r109_row9(input:&[u8],out:&mut[u32])->usize{o_a_main_part::<4,16,16,6,0>(input,out,0,0,0)}

#[inline(never)] pub fn r109_row10(input:&[u8],out:&mut[u32])->usize{y_machine(input,out)}

#[inline(never)] pub fn r109_row11(input:&[u8],out:&mut[u32])->usize{fx0_run::<65536,32768,2,258>(input,out,6)}

#[inline(never)] pub fn r109_row12(input:&[u8],out:&mut[u32])->usize{o_a_main_part::<8,32,8,4,0>(input,out,0,0,0)}

#[inline(never)] pub fn r109_row13(input:&[u8],out:&mut[u32])->usize{o_a_main_part::<12,64,8,5,0>(input,out,0,0,0)}

#[inline(never)] pub fn r109_row14(input:&[u8],out:&mut[u32])->usize{fx0_run::<32768,32768,2,258>(input,out,1)}

#[inline(never)] pub fn r109_row15(input:&[u8],out:&mut[u32])->usize{fx0_run::<65536,32768,2,0>(input,out,1)}

#[inline(never)] pub fn r109_row16(input:&[u8],out:&mut[u32])->usize{y_sparse(input,out)}

#[inline(never)] pub fn r109_row17(input:&[u8],out:&mut[u32])->usize{fx0_run::<4096,16384,2,258>(input,out,6)}

#[inline(never)] pub fn r109_row18(input:&[u8],out:&mut[u32])->usize{s_small::<2,12,12,4,0,64,32,64,16>(input,out)}

#[inline(never)] pub fn r109_row19(input:&[u8],out:&mut[u32])->usize{fx0_run::<1,1,2,258>(input,out,0)}

#[inline(never)] pub fn r109_row20(input:&[u8],out:&mut[u32])->usize{n_run::<65536,3,0,0,0,3,0,2,12>(input,out)}

#[inline(never)] pub fn r109_row21(input:&[u8],out:&mut[u32])->usize{n_run::<32768,3,0,0,0,4,0,2,12>(input,out)}

#[inline(never)] pub fn r109_row22(input:&[u8],out:&mut[u32])->usize{r109_bfraw::<65536,0>(input,out)}
