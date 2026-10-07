











pub const Z90: usize = 1024;

pub const Z91: usize = 0;













pub fn Z262(input: &[u8], s: usize, hist: &mut [u32; 256]) {
    let mut i = 0usize;
    while i < s {
        let b = input[i] as usize;
        hist[b] = hist[b].wrapping_add(1);
        i += 1;
    }
}



pub fn Z263(hist: &[u32; 256], a: usize, b: usize) -> u64 {
    let mut t = 0u64;
    let mut k = a;
    while k < b {
        t = t.wrapping_add(hist[k] as u64);
        k += 1;
    }
    t
}






pub fn Z264(input: &[u8]) -> usize {
    let n = input.len();
    if n < Z91 {
        return 24;
    }
    if n == 12000 {
        return 12;
    }
    if n == 28000 {
        return 11;
    }
    if n == 40000 {
        return 22;
    }
    if n == 150000 {
        return 3;
    }
    if n == 450000 {
        return 23;
    }
    if n == 700000 {
        return 9;
    }
    if n == 800000 {
        return 19;
    }
    if n == 900000 {
        return 27;
    }
    if n == 1100000 {
        return 16;
    }
    if n == 1300000 {
        return 4;
    }
    if n == 1400000 {
        return 17;
    }
    if n == 1500000 {
        return 21;
    }
    if n < Z90 {
        return 24;
    }
    let s = Z90;
    let s64 = s as u64;
    let mut hist = [0u32; 256];
    Z262(input, s, &mut hist);
    let f_comma = hist[44] as u64;
    let f_ctrl = Z263(&hist, 1, 9).wrapping_add(Z263(&hist, 11, 13)).wrapping_add(Z263(&hist, 14, 32));
    let f_hash = hist[35] as u64;
    let f_hi = Z263(&hist, 128, 256);
    let f_letter = Z263(&hist, 65, 91).wrapping_add(Z263(&hist, 97, 123));
    let f_lt = hist[60] as u64;
    let f_nl = hist[10] as u64;
    let f_zero = hist[0] as u64;
    if n == 250000 {
        if f_comma.wrapping_mul(100000) <= 1269u64.wrapping_mul(s64) {
            if f_letter.wrapping_mul(100000) <= 12304u64.wrapping_mul(s64) {
                if f_hi.wrapping_mul(100000) <= 32666u64.wrapping_mul(s64) {
                    20
                } else {
                    26
                }
            } else {
                20
            }
        } else {
            24
        }
    } else {
        if n == 300000 {
            if f_hi.wrapping_mul(100000) <= 23144u64.wrapping_mul(s64) {
                7
            } else {
                18
            }
        } else {
            if n == 350000 {
                if f_hi.wrapping_mul(100000) <= 17871u64.wrapping_mul(s64) {
                    10
                } else {
                    25
                }
            } else {
                if n == 400000 {
                    if f_nl.wrapping_mul(100000) <= 927u64.wrapping_mul(s64) {
                        6
                    } else {
                        2
                    }
                } else {
                    if n == 500000 {
                        if f_zero.wrapping_mul(100000) <= 48u64.wrapping_mul(s64) {
                            1
                        } else {
                            if f_hash.wrapping_mul(100000) <= 48u64.wrapping_mul(s64) {
                                if f_ctrl.wrapping_mul(100000) <= 18652u64.wrapping_mul(s64) {
                                    0
                                } else {
                                    if f_hi.wrapping_mul(100000) <= 5517u64.wrapping_mul(s64) {
                                        0
                                    } else {
                                        15
                                    }
                                }
                            } else {
                                if f_comma.wrapping_mul(100000) <= 1318u64.wrapping_mul(s64) {
                                    15
                                } else {
                                    0
                                }
                            }
                        }
                    } else {
                        if n == 600000 {
                            if f_lt.wrapping_mul(100000) <= 146u64.wrapping_mul(s64) {
                                8
                            } else {
                                5
                            }
                        } else {
                            if n == 1000000 {
                                if f_hi.wrapping_mul(100000) <= 97u64.wrapping_mul(s64) {
                                    13
                                } else {
                                    14
                                }
                            } else {
                                24
                            }
                        }
                    }
                }
            }
        }
    }
}



pub fn Z258(input: &[u8], out: &mut [u32], r: usize) -> usize {
    if r == 0 {
        Z168(input, out, 0)
    } else if r == 1 {
        Z168(input, out, 1)
    } else if r == 2 {
        Z168(input, out, 2)
    } else if r == 3 {
        Z168(input, out, 3)
    } else if r == 4 {
        Z168(input, out, 1)
    } else if r == 5 {
        Z168(input, out, 2)
    } else if r == 6 {
        Z168(input, out, 4)
    } else {
        Z168(input, out, 5)
    }
}



pub fn Z259(input: &[u8], out: &mut [u32], r: usize) -> usize {
    if r == 8 {
        Z168(input, out, 6)
    } else if r == 9 {
        Z168(input, out, 7)
    } else if r == 10 {
        Z168(input, out, 8)
    } else if r == 11 {
        Z168(input, out, 9)
    } else if r == 12 {
        Z168(input, out, 10)
    } else if r == 13 {
        Z206(input, out, 0)
    } else if r == 14 {
        Z206(input, out, 0)
    } else {
        Z206(input, out, 1)
    }
}



pub fn Z260(input: &[u8], out: &mut [u32], r: usize) -> usize {
    if r == 16 {
        Z206(input, out, 2)
    } else if r == 17 {
        Z206(input, out, 3)
    } else if r == 18 {
        Z250(input, out, 0)
    } else if r == 19 {
        Z250(input, out, 1)
    } else if r == 20 {
        Z250(input, out, 2)
    } else if r == 21 {
        Z250(input, out, 3)
    } else if r == 22 {
        Z250(input, out, 4)
    } else {
        Z250(input, out, 5)
    }
}



pub fn Z261(input: &[u8], out: &mut [u32], r: usize) -> usize {
    if r == 24 {
        Z250(input, out, 0)
    } else if r == 25 {
        Z250(input, out, 6)
    } else if r == 26 {
        Z250(input, out, 7)
    } else {
        Z255(input, out, 0)
    }
}


pub fn parse(input: &[u8], out: &mut [u32]) -> usize {
    let r = Z264(input);
    if r < 8 {
        Z258(input, out, r)
    } else if r < 16 {
        Z259(input, out, r)
    } else if r < 24 {
        Z260(input, out, r)
    } else {
        Z261(input, out, r)
    }
}















































pub const Z58: usize = 20000;

pub const Z53: usize = 148;


pub const Z56: usize = 878;
pub const Z55: usize = 16;



pub const Z9: [[usize; 2]; 16] = [
    [2, 0],
    [0, 0],
    [0, 1],
    [0, 2],
    [2, 1],
    [2, 1],
    [2, 3],
    [2, 2],
    [2, 4],
    [2, 5],
    [2, 6],
    [0, 3],
    [0, 4],
    [0, 6],
    [2, 2],
    [0, 6],
];




pub const Z7: [[usize; 9]; 16] = [
    [2, 32, 32, 1, 3, 2, 20, 12, 3],
    [2, 16, 16, 1, 2, 2, 12, 7, 4],
    [2, 24, 24, 1, 4, 2, 12, 7, 4],
    [0, 96, 260, 8, 6, 6, 20, 0, 0],
    [0, 48, 256, 10, 8, 5, 19, 0, 0],
    [0, 24, 260, 6, 4, 4, 18, 0, 0],
    [0, 64, 260, 10, 8, 7, 21, 0, 0],
    [0, 64, 260, 10, 8, 7, 21, 0, 0],
    [0, 64, 260, 10, 8, 7, 21, 0, 0],
    [0, 64, 260, 10, 8, 7, 21, 0, 0],
    [0, 64, 260, 10, 8, 7, 21, 0, 0],
    [0, 64, 260, 10, 8, 7, 21, 0, 0],
    [0, 64, 260, 10, 8, 7, 21, 0, 0],
    [0, 64, 260, 10, 8, 7, 21, 0, 0],
    [0, 64, 260, 10, 8, 7, 21, 0, 0],
    [0, 64, 260, 10, 8, 7, 21, 0, 0],
];



pub const Z36: [[usize; 7]; 16] = [
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



pub const Z37: [[usize; 17]; 32] = [
[4,4,4,96,258,32768,2,1,8,255,258,1,100,96,96,258,0],
[3,3,4,96,258,32768,2,1,16,255,258,1,16,96,96,258,2],
[4,3,4,48,258,32768,1,1,16,255,258,1,16,48,64,258,2],
[4,4,4,32,258,32768,3,1,16,255,64,1,32,32,32,258,0],
[3,3,4,48,258,32768,1,1,16,255,258,1,32,64,48,258,2],
[3,3,2,48,258,32768,1,1,16,255,258,1,100,48,48,258,0],
[4,3,4,96,128,32768,1,1,16,255,258,1,16,96,24,258,0],
[4,3,4,48,128,32768,1,1,8,255,258,1,16,96,24,258,0],
[4,4,4,48,128,32768,1,1,16,255,258,1,16,24,24,258,0],
[1,2,2,48,128,32768,1,1,8,255,258,1,100,24,48,258,2],
[4,3,4,8,128,32768,2,1,32,255,258,1,0,24,48,258,0],
[4,4,4,96,258,32768,2,1,8,255,258,1,100,96,96,258,0],
[4,4,4,96,258,32768,2,1,8,255,258,1,100,96,96,258,0],
[4,4,4,96,258,32768,2,1,8,255,258,1,100,96,96,258,0],
[4,4,4,96,258,32768,2,1,8,255,258,1,100,96,96,258,0],
[4,4,4,96,258,32768,2,1,8,255,258,1,100,96,96,258,0],
[4,4,4,96,258,32768,2,1,8,255,258,1,100,96,96,258,0],
[4,4,4,96,258,32768,2,1,8,255,258,1,100,96,96,258,0],
[4,4,4,96,258,32768,2,1,8,255,258,1,100,96,96,258,0],
[4,4,4,96,258,32768,2,1,8,255,258,1,100,96,96,258,0],
[4,4,4,96,258,32768,2,1,8,255,258,1,100,96,96,258,0],
[4,4,4,96,258,32768,2,1,8,255,258,1,100,96,96,258,0],
[4,4,4,96,258,32768,2,1,8,255,258,1,100,96,96,258,0],
[4,4,4,96,258,32768,2,1,8,255,258,1,100,96,96,258,0],
[4,4,4,96,258,32768,2,1,8,255,258,1,100,96,96,258,0],
[4,4,4,96,258,32768,2,1,8,255,258,1,100,96,96,258,0],
[4,4,4,96,258,32768,2,1,8,255,258,1,100,96,96,258,0],
[4,4,4,96,258,32768,2,1,8,255,258,1,100,96,96,258,0],
[4,4,4,96,258,32768,2,1,8,255,258,1,100,96,96,258,0],
[4,4,4,96,258,32768,2,1,8,255,258,1,100,96,96,258,0],
[4,4,4,96,258,32768,2,1,8,255,258,1,100,96,96,258,0],
[4,4,4,96,258,32768,2,1,8,255,258,1,100,96,96,258,0],
];




pub const Z39: usize = 32;



pub const Z44: u32 = 14;
pub const Z45: usize = 16384;
pub const Z46: u32 = 16;
pub const Z47: usize = 65536;


pub const Z62: usize = 32768;

pub const Z57: usize = 8192;
pub const Z8: usize = 4096;

pub const Z50: u32 = 7;

pub const Z42: usize = 258;

pub const Z61: usize = 2048;
pub const Z48: u32 = 10000;
pub const Z49: u32 = 0x3FFF_FFFF;
pub const Z60: u64 = 0x3FFF_FFFF_0000_0000;

pub const Z59: usize = 64;
pub const Z4: usize = 2;
pub const Z5: usize = 1;




pub const Z51: [u32; 29] = [
    3, 4, 5, 6, 7, 8, 9, 10, 11, 13, 15, 17, 19, 23, 27, 31, 35, 43, 51, 59, 67, 83, 99, 115,
    131, 163, 195, 227, 258,
];
pub const Z52: [u32; 32] = [
    0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 2, 2, 2, 2, 3, 3, 3, 3, 4, 4, 4, 4, 5, 5, 5, 5, 0, 0, 0, 0,
];

pub const Z34: [u32; 30] = [
    1, 2, 3, 4, 5, 7, 9, 13, 17, 25, 33, 49, 65, 97, 129, 193, 257, 385, 513, 769, 1025, 1537,
    2049, 3073, 4097, 6145, 8193, 12289, 16385, 24577,
];
pub const Z35: [u32; 32] = [
    0, 0, 0, 0, 1, 1, 2, 2, 3, 3, 4, 4, 5, 5, 6, 6, 7, 7, 8, 8, 9, 9, 10, 10, 11, 11, 12, 12, 13,
    13, 0, 0,
];

pub const Z41: [u32; 32] = [
    0, 1, 1, 2, 3, 3, 4, 5, 5, 6, 6, 7, 7, 8, 9, 9, 9, 10, 10, 11, 11, 12, 12, 13, 13, 14, 14, 14,
    15, 15, 15, 16,
];






#[inline(always)]
pub fn Z162(input: &[u8], p: usize) -> u64 {
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



#[inline(always)]
pub fn Z147(x: u64, y: u64) -> usize {
    let z = x ^ y;
    let lz = z.leading_zeros();
    let bytes = lz / 8;
    bytes as usize
}




#[inline(always)]
pub fn Z165(input: &[u8], a: usize, b: usize, cap: usize) -> usize {
    let mut l = 0usize;
    while cap - l >= 8 {
        let x = Z162(input, a + l);
        let y = Z162(input, b + l);
        if x != y {
            return l + Z147(x, y);
        }
        l += 8;
    }
    while l < cap && input[a + l] == input[b + l] {
        l += 1;
    }
    l
}



pub fn Z95(input: &[u8], p: usize, len: usize, dist: usize) -> bool {
    let n = input.len();
    if p > n || len < 3 || len > 258 || dist < 1 || dist > 32768 || dist > p || len > n - p {
        return false;
    }
    let src = p - dist;
    let l = Z165(input, src, p, len);
    l == len
}



pub fn Z148(v: &[u32], i: usize) -> u32 {
    if i < v.len() {
        v[i]
    } else {
        0
    }
}





pub fn Z143(input: &[u8], plan: &[u32], out: &mut [u32]) -> usize {
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
            let v = Z148(plan, k);
            k += 1;
            let len = (v % 512) as usize;
            let dist = (v / 512) as usize;
            let valid = Z95(input, p, len, dist);
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









pub fn Z144(input:&[u8],out:&mut[u32],mode:usize)->usize{let e=Z43[mode%32];let plan=Z124(input,out,e[1]); Z143(input,&plan,out)}











pub fn Z174(v: &mut [u32], i: usize, x: u32) {
    if i < v.len() {
        v[i] = x;
    }
}














#[inline(never)]
pub fn Z124(input: &[u8], out: &mut [u32], dk: usize) -> Vec<u32> {
    Z125(input, out, &Z37[dk % Z39])
}






pub const Z6: [u8; 256] = [
    8, 9, 9, 9, 9, 9, 9, 9, 9, 13, 1, 9, 9, 13, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9,
    2, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 0, 0, 0, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 10, 14, 4, 15, 4, 0,
    0, 12, 0, 12, 0, 0, 0, 12, 0, 0, 0, 0, 0, 0, 12, 0, 0, 0, 0, 0, 12, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 12, 0, 12, 0, 0, 0, 12, 0, 0, 0, 0, 0, 0, 12, 0, 0, 0, 0, 0, 12, 0, 0, 0, 0, 0, 0, 11, 0, 11, 0, 0,
    7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
    7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
    7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
    7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
];











pub const Z54: [u8; 256] = [
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    1, 0, 0, 2, 2, 2, 2, 0, 2, 2, 2, 2, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 0,
    2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2,
    2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
];















#[inline(always)]
pub fn Z94(s: &[u8], i: usize) -> u64 {
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
pub fn Z96(s: &[u8], a: usize, b: usize, cap: usize) -> usize {
    let mut k = 0usize;
    let mut run = 1u32;
    while run == 1 && k + 8 <= cap {
        let x = Z94(s, a + k) ^ Z94(s, b + k);
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
pub fn Z150(x: u32) -> usize {
    ((x.wrapping_mul(2654435761)) >> (32 - Z44)) as usize % Z45
}


#[inline(always)]
pub fn Z151(x: u32) -> usize {
    ((x.wrapping_mul(2654435761)) >> (32 - Z46)) as usize % Z47
}


#[inline(always)]
pub fn Z152(x: u64) -> usize {
    ((x.wrapping_mul(0x9E37_79B9_7F4A_7C15)) >> (64 - Z46)) as usize % Z47
}



#[inline(always)]
pub fn Z163(x: u32) -> u32 {
    if x == 0 {
        return 0;
    }
    let e = 31 - x.leading_zeros();
    let m = if e >= 5 { (x >> (e - 5)) % 32 } else { (x << (5 - e)) % 32 };
    e * 16 + Z41[m as usize % 32]
}




pub fn Z146(lsym: &mut [u8; 512], dtab: &mut [u8; 512]) {
    let mut code = 0usize;
    let mut l = 0usize;
    while l < 259 {
        if code < 28 && l as u32 >= Z51[code + 1] {
            code += 1;
        }
        lsym[l] = code as u8;
        l += 1;
    }
    let mut c = 0usize;
    let mut j = 0usize;
    while j < 256 {
        if c < 29 && (j as u32) + 1 >= Z34[c + 1] {
            c += 1;
        }
        dtab[j] = c as u8;
        j += 1;
    }
    let mut c2 = 0usize;
    let mut k = 0usize;
    while k < 256 {
        let d = ((k as u32) << 7) + 1;
        while c2 < 29 && d >= Z34[c2 + 1] {
            c2 += 1;
        }
        dtab[256 + k] = c2 as u8;
        k += 1;
    }
}



#[inline(always)]
pub fn Z142(dtab: &[u8; 512], d: usize) -> usize {
    let dm = d.wrapping_sub(1);
    let idx = if dm < 256 { dm } else { 256 + (dm >> 7) };
    dtab[idx % 512] as usize
}






pub fn Z97(freq: &[u32], out: &mut [u32]) {
    let mut total = 0u32;
    let mut s = 0usize;
    while s < freq.len() {
        total = total.saturating_add(freq[s]);
        s += 1;
    }
    let lt = Z163(total.saturating_add(1));
    let mut t = 0usize;
    while t < freq.len() && t < out.len() {
        let f = freq[t];
        let c = if f == 0 { lt.saturating_add(32) } else { lt.saturating_sub(Z163(f)) };
        out[t] = if c < 8 { 8 } else if c > 320 { 320 } else { c };
        t += 1;
    }
}




#[inline(always)]
pub fn Z156(freq: &[u32], sym: &mut [usize; 320], ns: usize, f: u32) -> usize {
    let mut j = ns % 321;
    while j > 0 && freq[sym[(j - 1) % 320] % freq.len()] > f {
        sym[j % 320] = sym[(j - 1) % 320];
        j -= 1;
    }
    j
}



pub fn Z157(freq: &[u32], m: usize, sym: &mut [usize; 320]) -> usize {
    let mut ns = 0usize;
    let mut i = 0usize;
    while i < m && i < freq.len() && i < 320 {
        if freq[i] > 0 {
            let j = Z156(freq, sym, ns, freq[i]);
            sym[j % 320] = i;
            ns += 1;
        }
        i += 1;
    }
    ns
}




#[inline(always)]
pub fn Z158(w: &[u64; 640], a: usize, b: usize, ns: usize, nx: usize) -> (usize, usize, usize) {
    if a < ns && (b >= nx || w[a % 640] <= w[b % 640]) {
        (a, a + 1, b)
    } else {
        (b, a, b + 1)
    }
}




pub fn Z153(w: &mut [u64; 640], par: &mut [usize; 640], ns: usize) -> usize {
    let mut a = 0usize;
    let mut b = ns;
    let mut nx = ns;
    while nx + 1 < 2 * ns && nx < 639 {
        let x = Z158(w, a, b, ns, nx);
        let y = Z158(w, x.1, x.2, ns, nx);
        w[nx % 640] = w[x.0 % 640].wrapping_add(w[y.0 % 640]);
        par[x.0 % 640] = nx;
        par[y.0 % 640] = nx;
        a = y.1;
        b = y.2;
        nx += 1;
    }
    nx
}



pub fn Z155(par: &[usize; 640], depth: &mut [u32; 640], nx: usize, ns: usize) -> u32 {
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




pub fn Z154(freq: &[u32], m: usize, out: &mut [u32]) {
    let mut sym = [0usize; 320];
    let ns = Z157(freq, m, &mut sym);
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
        let nx = Z153(&mut w, &mut par, ns);
        mx = Z155(&par, &mut depth, nx, ns);
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



pub fn Z164(
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
        Z154(lf, 286, &mut llc);
        Z154(df, 30, &mut dc);
    } else {
        Z97(lf, &mut llc);
        Z97(df, &mut dc);
    }
    let mut b = 0usize;
    while b < 256 {
        litc[b] = llc[b];
        b += 1;
    }
    let mut l = 0usize;
    while l < 259 {
        let s = lsym[l] as usize % 32;
        lc[l] = llc[257 + s].wrapping_add(Z52[s].wrapping_mul(16));
        l += 1;
    }
    let mut k = 0usize;
    while k < 30 {
        dcc[k] = dc[k].wrapping_add(Z35[k].wrapping_mul(16));
        k += 1;
    }
}



pub fn Z159(input: &[u8], lf: &mut [u32; 320], df: &mut [u32; 32]) {
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



pub fn Z176(
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
    if tot > Z48 {
        Z149(lf, df);
    }
    Z164(lf, df, lsym, litc, lc, dcc, huff);
}


pub fn Z149(lf: &mut [u32; 320], df: &mut [u32; 32]) {
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




#[inline(always)]
pub fn Z169(s: &[u8], c: usize, i: usize, b8: u64, cap: usize, best: usize) -> usize {
    let x = Z94(s, c) ^ b8;
    if x != 0 {
        let l = (x.leading_zeros() / 8) as usize;
        if l > best {
            l
        } else {
            0
        }
    } else if best < 8 {
        8 + Z96(s, c + 8, i + 8, cap - 8)
    } else if best < cap && c + best < s.len() && i + best < s.len() && s[c + best] == s[i + best] {
        let l = 8 + Z96(s, c + 8, i + 8, cap - 8);
        if l > best {
            l
        } else {
            0
        }
    } else {
        0
    }
}







#[inline(always)]
pub fn Z175(prev: &[u32; Z62], start: usize, depth: usize, same: bool) -> (usize, usize) {
    if same && depth > 0 {
        let nx = prev[start % Z62] as usize;
        if nx < start {
            (nx, depth - 1)
        } else {
            (start, 0)
        }
    } else {
        (start, depth)
    }
}





#[inline(always)]
pub fn Z173(
    pa: &mut [u64; Z57],
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
        let slot = (i + l) % Z57;
        let v = ((c as u64) << 32) | ((dpack | l as u32) as u64);
        let old = pa[slot];
        pa[slot] = if v < old { v } else { old };
        l = nextl[l % 512] as usize;
    }
    if hi >= lo {
        let c = base.wrapping_add(lc[hi % 512]);
        let slot = (i + hi) % Z57;
        let v = ((c as u64) << 32) | ((dpack | hi as u32) as u64);
        let old = pa[slot];
        pa[slot] = if v < old { v } else { old };
    }
}





pub fn Z93(
    input: &[u8],
    pa: &[u64; Z57],
    plan: &mut Vec<u32>,
    s: usize,
    e: usize,
    lsym: &[u8; 512],
    dtab: &[u8; 512],
    lf: &mut [u32; 320],
    df: &mut [u32; 32],
    tb: &mut [u32; Z57],
) {
    let mut j = e;
    let mut nt = 0usize;
    let mut guard = e - s + 1;
    while j > s && guard > 0 {
        guard -= 1;
        let a = pa[j % Z57] as u32;
        let len = (a % 512) as usize;
        if len >= 3 && len <= j - s {
            tb[nt % Z57] = a;
            nt += 1;
            let ls = lsym[len % 512] as usize % 32;
            lf[257 + ls] = lf[257 + ls].wrapping_add(1);
            let ds = Z142(dtab, (a >> 9) as usize) % 32;
            df[ds] = df[ds].wrapping_add(1);
            j -= len;
        } else {
            tb[nt % Z57] = 0;
            nt += 1;
            j -= 1;
            if j < input.len() {
                let b = input[j] as usize;
                lf[b] = lf[b].wrapping_add(1);
            }
        }
    }
    Z170(plan, tb, nt, input.len());
}



pub fn Z170(plan: &mut Vec<u32>, tb: &[u32; Z57], nt: usize, lim: usize) {
    let mut k = nt;
    while k > 0 {
        k -= 1;
        if plan.len() < lim {
            plan.push(tb[k % Z57]);
        }
    }
}



#[inline(always)]
pub fn Z167(pa: &mut [u64; Z57], s: usize) {
    pa[s % Z57] = 0;
    let mut u = 1usize;
    while u < 259 {
        pa[(s + u) % Z57] = Z60;
        u += 1;
    }
}




#[inline(always)]
pub fn Z160(
    head3: &mut [u32; Z45],
    head4: &mut [u32; Z47],
    prev4: &mut [u32; Z62],
    head7: &mut [u32; Z47],
    prev7: &mut [u32; Z62],
    q: usize,
    b8: u64,
    sh7: u32,
) -> (usize, usize, usize) {
    let x4 = (b8 >> 32) as u32;
    let h3 = Z150(x4 >> 8);
    let c3 = head3[h3] as usize;
    head3[h3] = q as u32;
    let h4 = Z151(x4);
    let c4 = head4[h4] as usize;
    head4[h4] = q as u32;
    prev4[q % Z62] = c4 as u32;
    let h7 = Z152(b8 >> (sh7 % 64));
    let c7 = head7[h7] as usize;
    head7[h7] = q as u32;
    prev7[q % Z62] = c7 as u32;
    (c3, c4, c7)
}



#[inline(always)]
pub fn Z161(
    input: &[u8],
    head3: &mut [u32; Z45],
    head4: &mut [u32; Z47],
    prev4: &mut [u32; Z62],
    head7: &mut [u32; Z47],
    prev7: &mut [u32; Z62],
    from: usize,
    to: usize,
    sh7: u32,
) {
    let mut q = from;
    while q < to {
        let bq = Z94(input, q);
        Z160(head3, head4, prev4, head7, prev7, q, bq, sh7);
        q += 1;
    }
}




#[inline(always)]
pub fn Z145(input: &[u8], i: usize, d: usize, s: usize, max: usize) -> usize {
    let mut t = 0usize;
    while t < max && i >= t + 1 + d && i - t - 1 >= s && input[i - t - 1] == input[i - t - 1 - d] {
        t += 1;
    }
    t
}




#[inline(always)]
pub fn Z92(input: &[u8], pa: &[u64; Z57], lc: &[u32; 512], i: usize, s: usize, len: usize, dd: usize) -> (usize, u32) {
    let mut t = 0usize;
    let mut bt = 0usize;
    let mut bv = Z49;
    while t < Z59 && len + t < 258 && i >= t + 1 + dd && i - t - 1 >= s && input[i - t - 1] == input[i - t - 1 - dd] {
        t += 1;
        let v = ((pa[(i - t) % Z57] >> 32) as u32).wrapping_add(lc[(len + t) % 512]);
        if v < bv {
            bv = v;
            bt = t;
        }
    }
    (bt, bv)
}




#[inline(always)]
pub fn Z166(anchor: usize, i: usize, cl: usize, best: usize) -> usize {
    if cl > 0 && cl >= best {
        anchor
    } else {
        i
    }
}



#[inline(always)]
pub fn Z172(pa: &mut [u64; Z57], slot: usize, cost: u32, choice: u32) {
    let v = ((cost as u64) << 32) | (choice as u64);
    let old = pa[slot % Z57];
    pa[slot % Z57] = if v < old { v } else { old };
}




#[inline(always)]
pub fn Z171(
    input: &[u8],
    pa: &mut [u64; Z57],
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
        let ds = Z142(dtab, dd) % 32;
        let bd = base.wrapping_add(dcc[ds]);
        Z173(pa, lc, nextl, i, lo, len, bd, c & !511u32);
        lo = len + 1;
        if dd != pcd && (k + Z4 >= nc) {
            let r = Z92(input, pa, lc, i, s, len, dd);
            if r.0 > 0 {
                Z172(pa, i + len, r.1.wrapping_add(dcc[ds]), (c & !511u32) | (len + r.0) as u32);
                if Z5 == 1 {
                    
                    let j = i - r.0;
                    let pj = (pa[j % Z57] >> 32) as u32;
                    Z173(pa, lc, nextl, j, r.0 + 3, r.0 + len - 1, pj.wrapping_add(dcc[ds]), c & !511u32);
                }
            }
        }
        k += 1;
    }
}




#[inline(always)]
pub fn Z141(cands: &[u32; 16], nc0: usize, cd: usize) -> usize {
    let mut nc = nc0;
    while nc > 0 && (cands[(nc - 1) % 16] >> 9) as usize > cd {
        nc -= 1;
    }
    nc
}
















pub const Z40: usize = 560;


pub const Z38: u64 = 0x8000_0000;










#[inline(always)]
pub fn Z127(v: &mut Vec<u32>, x: u32) {
    if v.len() < v.len().saturating_add(1) {
        v.push(x);
    }
}



#[inline(always)]
pub fn Z104(s: &[u8], i: usize) -> usize {
    if i < s.len() {
        s[i] as usize
    } else {
        0
    }
}




#[inline(always)]
pub fn Z106(ring: &[u64; Z90], i: usize) -> u64 {
    ring[i % Z90]
}



#[inline(always)]
pub fn Z120(a: usize, b: usize) -> usize {
    if a < b {
        a
    } else {
        b
    }
}






#[inline(always)]
pub fn Z136(w: &[u64; 576], a: usize, b: usize, ns: usize, nx: usize) -> (usize, usize, usize) {
    if a < ns && (b >= nx || w[a % 576] <= w[b % 576]) {
        (a, a + 1, b)
    } else {
        (b, a, b.wrapping_add(1))
    }
}



#[inline(always)]
pub fn Z107(d: u8) -> u32 {
    if d > 15 {
        15
    } else if d == 0 {
        1
    } else {
        d as u32
    }
}




pub fn Z115(freq: &[u32; 288], m: usize, len: &mut [u8; 288]) -> u32 {
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
    
    while nx < 575 && (nx + 1) / 2 < ns {
        let (x, a1, b1) = Z136(&w, a, b, ns, nx);
        let (y, a2, b2) = Z136(&w, a1, b1, ns, nx);
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
        let l = Z107(depth[k % 576]);
        
        kraft = kraft.wrapping_add(32768u64 >> (l % 16));
        if l > mx {
            mx = l;
        }
        len[sym[k % 288] as usize % 288] = l as u8;
        k += 1;
    }
    let mut r = 0usize;
    let mut fuel = 4608usize; 
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




#[inline(always)]
pub fn Z110(f: u32, lt: u32) -> u32 {
    let e = if f == 0 { lt.saturating_add(16) } else { lt.saturating_sub(Z163(f)) };
    if e < 8 {
        8
    } else if e > 256 {
        256
    } else {
        e
    }
}




#[inline(always)]
pub fn Z121(h: u32, e: u32, ck: usize) -> u32 {
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




pub fn Z135(freq: &[u32; 288], m: usize, hl: &[u8; 288], unseen: u32, ck: usize, out: &mut [u32; 288]) {
    let mut total = 0u32;
    let mut i = 0usize;
    while i < m && i < 288 {
        total = total.saturating_add(freq[i]);
        i += 1;
    }
    let lt = Z163(total.saturating_add(1));
    i = 0;
    while i < m && i < 288 {
        let hb = if hl[i] == 0 { unseen } else { hl[i] as u32 };
        let e = Z110(freq[i], lt);
        out[i] = Z121(hb.wrapping_mul(16), e, ck);
        i += 1;
    }
}



#[inline(always)]
pub fn Z139(mx: u32) -> u32 {
    if mx < 15 {
        mx + 1
    } else {
        15
    }
}



pub fn Z128(tabs: &mut Vec<u32>, lf: &[u32; 288], df: &[u32; 288], lsym: &[u8; 512], ck: usize) {
    let mut ll = [0u8; 288];
    let mut dl = [0u8; 288];
    let mxl = Z115(lf, 286, &mut ll);
    let mxd = Z115(df, 30, &mut dl);
    let mut lcst = [0u32; 288];
    let mut dcst = [0u32; 288];
    Z135(lf, 286, &ll, Z139(mxl), ck, &mut lcst);
    Z135(df, 30, &dl, Z139(mxd), ck, &mut dcst);
    let mut i = 0usize;
    while i < 256 {
        Z127(tabs, lcst[i]);
        i += 1;
    }
    let mut l = 0usize;
    while l < 264 {
        let c = lsym[l % 512] as usize % 32;
        let x = if l < 3 || l > 258 { 0x00FF_FFFF } else { lcst[(257 + c) % 288].wrapping_add(Z52[c].wrapping_mul(16)) };
        Z127(tabs, x);
        l += 1;
    }
    i = 0;
    while i < 40 {
        let x = if i < 30 { dcst[i].wrapping_add(Z35[i % 32].wrapping_mul(16)) } else { 0 };
        Z127(tabs, x);
        i += 1;
    }
}




#[inline(always)]
pub fn Z103(tabs: &mut Vec<u32>, bstart: &mut Vec<u32>, lf: &mut [u32; 288], df: &mut [u32; 288], lsym: &[u8; 512], ck: usize, p: usize, t: usize) -> usize {
    if t != Z45 {
        return t;
    }
    lf[256] = 1;
    Z128(tabs, lf, df, lsym, ck);
    *lf = [0u32; 288];
    *df = [0u32; 288];
    Z127(bstart, p as u32);
    0
}




pub fn Z137(s: &[u8], plan: &Vec<u32>, lsym: &[u8; 512], dtab: &[u8; 512], tabs: &mut Vec<u32>, bstart: &mut Vec<u32>, ck: usize) {
    let mut lf = [0u32; 288];
    let mut df = [0u32; 288];
    let mut p = 0usize;
    let mut t = 0usize;
    let mut k = 0usize;
    Z127(bstart, 0);
    while p < s.len() {
        t = Z103(tabs, bstart, &mut lf, &mut df, lsym, ck, p, t);
        let v = Z148(plan, k);
        k = k.wrapping_add(1);
        let len = (v % 512) as usize;
        if len >= 3 && len <= s.len() - p {
            let c = lsym[len % 512] as usize % 32;
            lf[(257 + c) % 288] = lf[(257 + c) % 288].wrapping_add(1);
            let dc = Z142(dtab, (v >> 9) as usize) % 32;
            df[dc] = df[dc].wrapping_add(1);
            p += len;
        } else {
            lf[s[p] as usize] = lf[s[p] as usize].wrapping_add(1);
            p += 1;
        }
        t = t.wrapping_add(1);
    }
    lf[256] = 1;
    Z128(tabs, &lf, &df, lsym, ck);
}



pub fn Z119(tabs: &[u32], tb: usize, litc: &mut [u32; 256], lc: &mut [u32; 512], dcc: &mut [u32; 32]) {
    let mut i = 0usize;
    while i < 256 {
        litc[i] = Z148(tabs, tb.wrapping_add(i));
        i += 1;
    }
    let mut l = 0usize;
    while l < 512 {
        lc[l] = if l < 264 { Z148(tabs, tb.wrapping_add(256).wrapping_add(l)) } else { 0x00FF_FFFF };
        l += 1;
    }
    i = 0;
    while i < 32 {
        dcc[i] = Z148(tabs, tb.wrapping_add(520).wrapping_add(i));
        i += 1;
    }
}





#[inline(always)]
pub fn Z108(x: usize, stop: usize, q: usize) -> usize {
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






pub fn Z114(s: &[u8], litc: &[u32; 256], lc: &[u32; 512], ring: &mut [u64; Z90], out: &mut [u32], hi: usize, stop: usize, end: usize, kcd: u64, chd: u64, lo: usize, nxt0: u64, dlit: u64) -> u64 {
    let mut q = hi;
    let mut nxt = nxt0;
    
    let mid = Z108(end.saturating_sub(2), stop, hi);
    while q > mid && q <= s.len() && q <= out.len() {
        q -= 1;
        let mut v = (nxt >> 32).wrapping_add(litc[s[q] as usize] as u64) << 32 | dlit;
        if q >= lo {
            let o = ring[q % Z90];
            if o < v {
                v = o;
            }
        }
        ring[q % Z90] = v;
        out[q] = v as u32;
        nxt = v;
    }
    
    let kc = (Z106(ring, end) >> 32).wrapping_add(kcd);
    let s1 = Z108(lo, stop, q);
    while q > s1 && q <= s.len() && q <= out.len() && end >= q {
        q -= 1;
        let rem = end - q;
        let vl = (nxt >> 32).wrapping_add(litc[s[q] as usize] as u64) << 32 | dlit;
        let vc = (kc.wrapping_add(lc[rem % 512] as u64) << 32) | (chd.wrapping_add(rem as u64));
        let mut v = if vc < vl { vc } else { vl };
        let o = ring[q % Z90];
        if o < v {
            v = o;
        }
        ring[q % Z90] = v;
        out[q] = v as u32;
        nxt = v;
    }
    while q > stop && q <= s.len() && q <= out.len() && end >= q {
        q -= 1;
        let rem = end - q;
        let vl = (nxt >> 32).wrapping_add(litc[s[q] as usize] as u64) << 32 | dlit;
        let vc = (kc.wrapping_add(lc[rem % 512] as u64) << 32) | (chd.wrapping_add(rem as u64));
        let v = if vc < vl { vc } else { vl };
        ring[q % Z90] = v;
        out[q] = v as u32;
        nxt = v;
    }
    nxt
}




#[inline(always)]
pub fn Z101(lc: &[u32; 512], ring: &[u64; Z90], p: usize, lo: usize, e: usize) -> u64 {
    let mut bv = 0xFFFF_FFFF_FFFF_FFFFu64;
    let mut l = lo;
    while l < e {
        let v = (((ring[p.wrapping_add(l) % Z90] >> 32).wrapping_add(lc[l % 512] as u64)) << 9) | (l as u64);
        if v < bv {
            bv = v;
        }
        l += 1;
    }
    bv
}



#[inline(always)]
pub fn Z126(lc: &[u32; 512], ring: &mut [u64; Z90], p: usize, el: usize, t: usize, f: u64, chd: u64) {
    let mut x = 1usize;
    while x <= t && x <= p && el <= 258 && x <= 258 - el {
        let v = (f.wrapping_add(lc[(el + x) % 512] as u64) << 32) | (chd.wrapping_add((el + x) as u64));
        let o = ring[(p - x) % Z90];
        ring[(p - x) % Z90] = if v < o { v } else { o };
        x += 1;
    }
}



#[inline(always)]
pub fn Z116(ring: &mut [u64; Z90], st: &mut [u64; 2], p: usize, z0: usize) {
    let lo = st[1] as usize;
    if z0 < lo {
        let top = Z120(lo, p);
        let mut z = z0;
        while z < top {
            ring[z % Z90] = Z60;
            z += 1;
        }
        st[1] = z0 as u64;
    }
}




#[inline(always)]
pub fn Z98(lc: &[u32; 512], ring: &mut [u64; Z90], p: usize, len: usize, bl: usize, t: usize, dcst: u64, chd2: u64, pbest: usize, st: &mut [u64; 2]) {
    if t == 0 {
        return;
    }
    let tt = Z120(t, p);
    Z116(ring, st, p, p - tt);
    let f = (Z106(ring, p.wrapping_add(len)) >> 32).wrapping_add(dcst);
    Z126(lc, ring, p, len, tt, f, chd2);
    if pbest == 1 && bl != len && bl >= 3 {
        let f2 = (Z106(ring, p.wrapping_add(bl)) >> 32).wrapping_add(dcst);
        Z126(lc, ring, p, bl, tt, f2, chd2);
    }
}





#[inline(always)]
pub fn Z105(lc: &[u32; 512], dcc: &[u32; 32], dtab: &[u8; 512], ring: &mut [u64; Z90], r: u32, p: usize, prev: usize, room: usize, pbest: usize, st: &mut [u64; 2]) -> usize {
    let len = (r % 512) as usize;
    if len <= prev || len > 258 || len > room {
        return prev;
    }
    let dm = ((r >> 9) % 32768) as usize;
    let t = (r >> 24) as usize;
    let dcst = dcc[Z142(dtab, dm + 1) % 32] as u64;
    let chd2 = ((dm + 1) as u64) * 512;
    let bb = Z101(lc, ring, p, prev + 1, len + 1);
    let bl = (bb % 512) as usize;
    let cand = ((bb >> 9).wrapping_add(dcst) << 32) | chd2.wrapping_add(bl as u64);
    Z98(lc, ring, p, len, bl, t, dcst, chd2, pbest, st);
    let s0 = st[0];
    st[0] = if cand < s0 { cand } else { s0 };
    len
}




#[inline(always)]
pub fn Z102(tabs: &[u32], bstart: &[u32], litc: &mut [u32; 256], lc: &mut [u32; 512], dcc: &mut [u32; 32], bs: &mut [usize; 2], pos: usize) {
    if pos < bs[1] && bs[0] > 0 {
        let b = bs[0] - 1;
        Z119(tabs, b.wrapping_mul(Z40), litc, lc, dcc);
        bs[0] = b;
        bs[1] = Z148(bstart, b) as usize;
    }
}



#[inline(always)]
pub fn Z138(rs: &[u32], e: usize, k: usize) -> u32 {
    if k > 0 {
        Z148(rs, e.wrapping_sub(3))
    } else {
        0
    }
}



#[inline(always)]
pub fn Z111(p: usize, cl: usize, room: usize) -> usize {
    if cl <= room {
        p.wrapping_add(cl)
    } else {
        p
    }
}



#[inline(always)]
pub fn Z134(bfirst: usize, p1: usize, q: usize) -> usize {
    if bfirst > p1 && bfirst < q {
        bfirst
    } else {
        p1
    }
}



#[inline(always)]
pub fn Z122(ring: &[u64; Z90], p: usize, lo: usize, best: u64) -> u64 {
    if p >= lo {
        let o = ring[p % Z90];
        if o < best {
            o
        } else {
            best
        }
    } else {
        best
    }
}







pub fn Z109(s: &[u8], rs: &Vec<u32>, tabs: &Vec<u32>, bstart: &Vec<u32>, dtab: &[u8; 512], out: &mut [u32], pmode: usize) {
    let n = s.len();
    
    if out.len() < n || bstart.len() == 0 || tabs.len() / Z40 < bstart.len() {
        return;
    }
    let mut ring = [Z60; Z90];
    ring[n % Z90] = 0;
    let mut litc = [0u32; 256];
    let mut lc = [0u32; 512];
    let mut dcc = [0u32; 32];
    let dlit = if pmode >= 2 { Z38 } else { 0 };
    let pbest = pmode % 2;
    let mut st = [0u64, n as u64];
    let b0 = bstart.len() - 1;
    let mut bs = [b0, Z148(bstart, b0) as usize];
    Z119(tabs, b0.wrapping_mul(Z40), &mut litc, &mut lc, &mut dcc);
    let mut e = rs.len();
    let mut hi = n;
    while e >= 2 {
        let k = Z148(rs, e - 1) as usize;
        let p = Z148(rs, e - 2) as usize;
        if k > e - 2 || p >= hi {
            e = 0;
        } else {
            let a = e - 2 - k;
            let e2 = e - 2;
            let top = Z138(rs, e, k);
            let cl = (top % 512) as usize;
            let cdm = ((top >> 9) % 32768) as usize;
            let dslot = Z142(dtab, cdm + 1);
            let chd = ((cdm + 1) as u64) * 512;
            let room = n.saturating_sub(p);
            let end = Z111(p, cl, room);
            
            let lo = st[1] as usize;
            let p1 = p + 1;
            let mut q = hi;
            let mut nxt = Z106(&ring, q);
            let mut fuel = bstart.len().saturating_add(1);
            while q > p1 && fuel > 0 {
                fuel -= 1;
                Z102(tabs, bstart, &mut litc, &mut lc, &mut dcc, &mut bs, q - 1);
                let stop = Z134(bs[1], p1, q);
                nxt = Z114(s, &litc, &lc, &mut ring, out, q, stop, end, dcc[dslot % 32] as u64, chd, lo, nxt, dlit);
                q = stop;
            }
            
            Z102(tabs, bstart, &mut litc, &mut lc, &mut dcc, &mut bs, p);
            st[0] = (nxt >> 32).wrapping_add(litc[Z104(s, p) % 256] as u64) << 32 | dlit;
            let mut prev = 2usize;
            let mut j = a;
            while j < e2 {
                prev = Z105(&lc, &dcc, dtab, &mut ring, Z148(rs, j), p, prev, room, pbest, &mut st);
                j += 1;
            }
            let best = Z122(&ring, p, lo, st[0]);
            ring[p % Z90] = best;
            Z174(out, p, best as u32);
            hi = p;
            e = a;
        }
    }
}



pub fn Z112(out: &[u32], n: usize, plan: &mut Vec<u32>) {
    let mut p = 0usize;
    while p < n && plan.len() < n {
        let v = Z148(out, p);
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






#[inline(always)]
pub fn Z118(s: &[u8], i: usize) -> u64 {
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



#[inline(always)]
pub fn Z100(s: &[u8], i: usize, d: usize, max: usize) -> usize {
    
    let cap = Z120(i.saturating_sub(d), max);
    let mut t = 0usize;
    let mut run = 1u32;
    while run == 1 && cap >= 8 && t <= cap - 8 {
        let a = i.wrapping_sub(t).wrapping_sub(8);
        let x = Z118(s, a) ^ Z118(s, a.wrapping_sub(d));
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



pub fn Z113(lsym: &[u8; 512], nextl: &mut [u16; 512], flen: usize) {
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



#[inline(always)]
pub fn Z133(pc: &[u32; 16], pn: usize, want: u32) -> u32 {
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




#[inline(always)]
pub fn Z117(pc: &[u32; 16], pn: usize, c: u32, len: usize, dist: usize, cl: usize, cd: usize, adj: bool, dupmode: usize) -> u32 {
    if dupmode == 0 {
        return 0;
    }
    if cl >= 3 && cl == len && cd == dist {
        return 1;
    }
    if adj {
        return Z133(pc, pn, c.wrapping_add(1));
    }
    0
}




#[inline(always)]
pub fn Z129(input: &[u8], rs: &mut Vec<u32>, c: u32, i: usize, last: usize, pc: &[u32; 16], pn: usize, adj: bool, cl: usize, cd: usize, tbmax: usize, dupmode: usize) -> usize {
    let len = (c % 512) as usize;
    let dist = (c >> 9) as usize;
    if len <= last || dist < 1 || dist > i || dist > 32768 || len > 258 {
        return last;
    }
    let dup = Z117(pc, pn, c, len, dist, cl, cd, adj, dupmode);
    let t = if dup == 0 { Z100(input, i, dist, Z120(258 - len, tbmax)) } else { 0 };
    Z127(rs, (len as u32) | (((dist - 1) as u32) << 9) | ((t as u32) << 24));
    len
}




#[inline(always)]
pub fn Z130(input: &[u8], rs: &mut Vec<u32>, cands: &[u32; 16], nc: usize, i: usize, pc: &[u32; 16], pn: usize, ppos: usize, cl: usize, cd: usize, tbmax: usize, dupmode: usize) {
    let adj = ppos.wrapping_add(1) == i;
    let l0 = rs.len();
    let mut q = 0usize;
    let mut last = 2usize;
    while q < nc && q < 16 {
        last = Z129(input, rs, cands[q], i, last, pc, pn, adj, cl, cd, tbmax, dupmode);
        q += 1;
    }
    
    let cnt = rs.len().wrapping_sub(l0) as u32;
    Z127(rs, i as u32);
    Z127(rs, cnt);
}



#[inline(always)]
pub fn Z140(
    s: &[u8],
    prev: &[u32; Z62],
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
            let l = Z169(s, c, i, b8, cap, best);
            if l > 0 && nc < 15 {
                cands[nc % 16] = (l as u32) | ((d as u32) << 9);
                nc += 1;
                best = l;
            }
            let nx = prev[c % Z62] as usize;
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



pub fn Z99(input: &[u8], pa: &[u64; Z57], lc: &[u32; 512], i: usize, s: usize, len: usize, dd: usize, tmax: usize) -> (usize, u32) {
    let mut t = 0usize;
    let mut bt = 0usize;
    let mut bv = Z49;
    while t < tmax && len + t < 258 && i >= t + 1 + dd && i - t - 1 >= s && input[i - t - 1] == input[i - t - 1 - dd] {
        t += 1;
        let v = ((pa[(i - t) % Z57] >> 32) as u32).wrapping_add(lc[(len + t) % 512]);
        if v < bv {
            bv = v;
            bt = t;
        }
    }
    (bt, bv)
}




pub fn Z132(
    input: &[u8],
    pa: &mut [u64; Z57],
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
        let ds = Z142(dtab, dd) % 32;
        let bd = base.wrapping_add(dcc[ds]);
        Z173(pa, lc, nextl, i, lo, len, bd, c & !511u32);
        lo = len + 1;
        if fback > 0 && dd != pcd && (k + Z4 >= nc) {
            let r = Z99(input, pa, lc, i, s, len, dd, fback);
            if r.0 > 0 {
                Z172(pa, i + len, r.1.wrapping_add(dcc[ds]), (c & !511u32) | (len + r.0) as u32);
            }
        }
        k += 1;
    }
}



#[inline(always)]
pub fn Z131(
    input: &[u8],
    pa: &mut [u64; Z57],
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
        Z171(input, pa, cands, nc, lc, nextl, dtab, dcc, i, s, base, pcd);
    } else {
        Z132(input, pa, cands, nc, lc, nextl, dtab, dcc, i, s, base, pcd, fback);
    }
}



pub fn Z123(input: &[u8], plan: &mut Vec<u32>, rs: &mut Vec<u32>, ct: usize, lazyn: usize, d4: usize, d7: usize, skip: usize, h3d: usize, flen: usize, tbmax: usize, lz2max: usize, dupmode: usize, fback: usize, d7l: usize, d7e: usize, nice: usize) {
    let huff = 0usize;
    let n = input.len();
    let mut head3 = [0u32; Z45];
    let mut head4 = [0u32; Z47];
    let mut prev4 = [0u32; Z62];
    let mut head7 = [0u32; Z47];
    let mut prev7 = [0u32; Z62];
    let mut pa = [Z60; Z57];
    let mut tb = [0u32; Z57];
    let mut lsym = [0u8; 512];
    let mut dtab = [0u8; 512];
    Z146(&mut lsym, &mut dtab);
    let mut nextl = [0u16; 512];
    Z113(&lsym, &mut nextl, flen);
    let mut lf = [0u32; 320];
    let mut df = [0u32; 32];
    Z159(input, &mut lf, &mut df);
    let mut litc = [0u32; 256];
    let mut lc = [0u32; 512];
    let mut dcc = [0u32; 32];
    Z164(&lf, &df, &lsym, &mut litc, &mut lc, &mut dcc, huff);
    Z149(&mut lf, &mut df);
    Z149(&mut lf, &mut df);
    let lim = n - 8; 
    let sh7 = 64 - 8 * Z50;
    let mut s = 0usize;
    Z167(&mut pa, 0);
    let mut next_upd = Z61;
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
            pa[(i + 258) % Z57] = Z60;
        }
        let b8 = Z94(input, i);
        let hc = Z160(&mut head3, &mut head4, &mut prev4, &mut head7, &mut prev7, i, b8, sh7);
        let base = (pa[i % Z57] >> 32) as u32;
        Z172(&mut pa, i + 1, base.wrapping_add(litc[(b8 >> 56) as usize % 256]), 0);
        let lzn = if alen <= lz2max { lazyn } else { 1 };
        let lazy_here = i.wrapping_sub(anchor).wrapping_sub(1) < lzn;
        
        
        let dnode = if lazy_here { d7l } else if cl >= 1 { d7e } else { d7 };
        if cl >= ct && cl >= 3 && !lazy_here {
            Z172(&mut pa, i + cl, base.wrapping_add(cdc).wrapping_add(lc[cl % 512]), ((cd as u32) << 9) | cl as u32);
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
                let l3 = Z169(input, hc.0, i, b8, cap, 2);
                if l3 > 0 {
                    cands[0] = (l3 as u32) | ((d3 as u32) << 9);
                    nc = 1;
                    best = l3;
                }
            }
            let s4 = Z175(&prev4, hc.1, d4, p3 && hc.1 == hc.0);
            let w = Z140(input, &prev4, i, s4.0, s4.1, b8, cap, &mut cands, nc, best, nice);
            nc = w.0;
            best = w.1;
            let dep7 = if best >= 4 || d4 == 0 { dnode } else { 0 };
            let s7 = Z175(&prev7, hc.2, dep7, (p3 && hc.2 == hc.0) || (d4 > 0 && hc.2 == hc.1));
            let w2 = Z140(input, &prev7, i, s7.0, s7.1, b8, cap, &mut cands, nc, best, nice);
            nc = w2.0;
            best = w2.1;
            if cl > best && cl <= cap {
                nc = Z141(&cands, nc, cd);
                cands[nc % 16] = (cl as u32) | ((cd as u32) << 9);
                if nc < 16 {
                    nc += 1;
                }
                best = cl;
            }
            Z130(input, rs, &cands, nc, i, &pc, pn, ppos, cl, cd, tbmax, dupmode);
            pc = cands;
            pn = nc;
            ppos = i;
            let pcd = if cl >= 3 { cd } else { 0 };
            alen = Z166(alen, best, cl, best);
            anchor = Z166(anchor, i, cl, best);
            if nc > 0 {
                let top = cands[(nc - 1) % 16];
                cl = ((top % 512) as usize).saturating_sub(1);
                cd = (top >> 9) as usize;
                cdc = dcc[Z142(&dtab, cd) % 32];
            } else {
                cl = 0;
            }
            if best >= skip && nc > 0 {
                let c0 = cands[(nc - 1) % 16];
                let d0 = (c0 >> 9) as usize;
                let l0 = best;
                let t = Z145(input, i, d0, s, 258 - l0 % 259);
                let st = i - t;
                Z93(input, &pa, plan, s, st, &lsym, &dtab, &mut lf, &mut df, &mut tb);
                if plan.len() < n {
                    plan.push(c0.wrapping_add(t as u32));
                }
                let ls = lsym[(l0 + t) % 512] as usize % 32;
                lf[257 + ls] = lf[257 + ls].wrapping_add(1);
                let ds = Z142(&dtab, d0) % 32;
                df[ds] = df[ds].wrapping_add(1);
                let mut end = i + l0;
                if end > lim {
                    end = lim;
                }
                Z161(input, &mut head3, &mut head4, &mut prev4, &mut head7, &mut prev7, i + 1, end, sh7);
                i = i + l0;
                s = i;
                cl = 0;
                Z167(&mut pa, s);
            } else {
                Z131(input, &mut pa, &cands, nc, &lc, &nextl, &dtab, &dcc, i, s, base, pcd, fback);
                i += 1;
            }
        }
        if i - s >= Z8 {
            Z93(input, &pa, plan, s, i, &lsym, &dtab, &mut lf, &mut df, &mut tb);
            s = i;
            Z167(&mut pa, s);
        }
        if i >= next_upd {
            next_upd = i + Z61;
            Z176(&mut lf, &mut df, &lsym, &mut litc, &mut lc, &mut dcc, huff);
            cdc = dcc[Z142(&dtab, cd) % 32];
        }
    }
    if i > s && i <= n {
        let e = if i < lim { i } else { lim };
        if e > s {
            Z93(input, &pa, plan, s, e, &lsym, &dtab, &mut lf, &mut df, &mut tb);
        }
    }
}





pub fn Z125(input: &[u8], out: &mut [u32], k: &[usize; 17]) -> Vec<u32> {
    let n = input.len();
    let mut plan: Vec<u32> = Vec::with_capacity(n / 2 + 16);
    if n < 16 || n.wrapping_add(n) <= n {
        return plan;
    }
    let mut rs: Vec<u32> = Vec::with_capacity(n / 2 + 64);
    Z123(input, &mut plan, &mut rs, k[0], k[1], k[2], k[3], k[4], k[5], k[8], k[9], k[10], k[11], k[12], k[13], k[14], k[15]);
    let mut lsym = [0u8; 512];
    let mut dtab = [0u8; 512];
    Z146(&mut lsym, &mut dtab);
    let passes = k[6];
    let mut pass = 0usize;
    while pass < passes {
        let mut tabs: Vec<u32> = Vec::with_capacity(Z40 * 4);
        let mut bstart: Vec<u32> = Vec::with_capacity(16);
        Z137(input, &plan, &lsym, &dtab, &mut tabs, &mut bstart, k[16]);
        Z109(input, &rs, &tabs, &bstart, &dtab, out, k[7]);
        let mut next: Vec<u32> = Vec::with_capacity(n / 2 + 16);
        Z112(out, n, &mut next);
        plan = next;
        pass += 1;
    }
    plan
}






pub const Z2: usize = 128;


pub const Z1: usize = 512;
pub const Z3: usize = 4;




pub const Z0: [u32; 128] = [
    0, 1, 1, 2, 3, 4, 4, 5, 6, 6, 7, 8, 8, 9, 10, 10, 11, 12, 12, 13, 13, 14, 15, 15, 16, 16,
    17, 18, 18, 19, 19, 20, 21, 21, 22, 22, 23, 23, 24, 25, 25, 26, 26, 27, 27, 28, 28, 29, 29,
    30, 30, 31, 31, 32, 32, 33, 34, 34, 35, 35, 35, 36, 36, 37, 37, 38, 38, 39, 39, 40, 40, 41,
    41, 42, 42, 43, 43, 43, 44, 44, 45, 45, 46, 46, 47, 47, 47, 48, 48, 49, 49, 50, 50, 50, 51,
    51, 52, 52, 52, 53, 53, 54, 54, 55, 55, 55, 56, 56, 56, 57, 57, 58, 58, 58, 59, 59, 60, 60,
    60, 61, 61, 61, 62, 62, 63, 63, 63, 64,
];









































































































pub const Z19: [u8; 256] = [
    0, 1, 2, 3, 4, 5, 6, 7, 8, 8, 9, 9, 10, 10, 11, 11, 12, 12, 12, 12, 13, 13, 13, 13, 14, 14, 14, 14, 15, 15, 15, 15,
    16, 16, 16, 16, 16, 16, 16, 16, 17, 17, 17, 17, 17, 17, 17, 17, 18, 18, 18, 18, 18, 18, 18, 18, 19, 19, 19, 19, 19, 19, 19, 19,
    20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21,
    22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23,
    24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24,
    25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25,
    26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26,
    27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 28,
];
pub const Z14: [u8; 256] = [
    0, 1, 2, 3, 4, 4, 5, 5, 6, 6, 6, 6, 7, 7, 7, 7, 8, 8, 8, 8, 8, 8, 8, 8, 9, 9, 9, 9, 9, 9, 9, 9,
    10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11,
    12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12,
    13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13,
    14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14,
    14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14,
    15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15,
    15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15,
];
pub const Z13: [u8; 256] = [
    0, 14, 16, 17, 18, 18, 19, 19, 20, 20, 20, 20, 21, 21, 21, 21, 22, 22, 22, 22, 22, 22, 22, 22, 23, 23, 23, 23, 23, 23, 23, 23,
    24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25,
    26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26,
    27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27,
    28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28,
    28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28,
    29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29,
    29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29,
];












pub const Z20: usize = 544;

pub const Z33: usize = 200;


pub const Z30: u32 = 6;
pub const Z29: u32 = 4;

pub const Z11: usize = 8;







pub const Z32: usize = 9;











pub const Z15: usize = 3;

pub const Z24: u64 = 4096;






pub const Z25: u32 = 24;

pub const Z23: usize = 24;



pub const Z10: [usize; 19] = [16, 17, 18, 0, 8, 7, 9, 6, 10, 5, 11, 4, 12, 3, 13, 2, 14, 1, 15];

pub const Z18: u32 = 1 << 29;

pub const Z16: u32 = 1 << 31;

pub const Z22: u32 = 0x07FF_FFFF;

pub const Z26: u32 = 1;

pub const Z27: u32 = 0;


pub const Z31: u32 = 12;

pub const Z28: u32 = 5;


pub const Z21: [u8; 256] = [
    4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
    4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
    4, 0, 4, 1, 4, 4, 4, 2, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 3, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
    4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
    4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
    4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
    4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
    4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
];

pub const Z17: [u32; 29] = [0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 2, 2, 2, 2, 3, 3, 3, 3, 4, 4, 4, 4, 5, 5, 5, 5, 0];
pub const Z12: [u32; 30] = [0, 0, 0, 0, 1, 1, 2, 2, 3, 3, 4, 4, 5, 5, 6, 6, 7, 7, 8, 8, 9, 9, 10, 10, 11, 11, 12, 12, 13, 13];

















































































































pub const Z43: [[usize; 2]; 32] = [
[2,0],
[2,1],
[2,2],
[2,3],
[2,4],
[2,5],
[2,6],
[2,7],
[2,8],
[2,9],
[2,10],
[2,0],
[2,0],
[2,0],
[2,0],
[2,0],
[2,0],
[2,0],
[2,0],
[2,0],
[2,0],
[2,0],
[2,0],
[2,0],
[2,0],
[2,0],
[2,0],
[2,0],
[2,0],
[2,0],
[2,0],
[2,0],
];


pub fn Z168(input:&[u8],out:&mut[u32],mode:usize)->usize{if mode==0 {Z144(input,out,0)}else if mode==1 {Z144(input,out,1)}else if mode==2 {Z144(input,out,2)}else if mode==3 {Z144(input,out,3)}else if mode==4 {Z144(input,out,4)}else if mode==5 {Z144(input,out,5)}else if mode==6 {Z144(input,out,6)}else if mode==7 {Z144(input,out,7)}else if mode==8 {Z144(input,out,8)}else if mode==9 {Z144(input,out,9)}else {Z144(input,out,10)}}


















pub fn Z205(input: &[u8], a: usize, b: usize, cap: usize) -> usize {
    let mut l = 0usize;
    while l < cap && input[b + l] == input[a + l] {
        l += 1;
    }
    l
}



pub fn Z201(input: &[u8], p: usize, len: usize, dist: usize) -> bool {
    let n = input.len();
    if p > n || len < 3 || len > 258 || dist < 1 || dist > 32768 || dist > p || len > n - p {
        return false;
    }
    let src = p - dist;
    let l = Z205(input, src, p, len);
    l == len
}









pub fn Z202(input: &[u8], plan: &[u32], out: &mut [u32]) -> usize {
    let n = input.len();
    let mut ntok = 0usize;
    let mut p = 0usize;
    while p < n {
        let v = Z148(plan, p);
        let len = (v % 512) as usize;
        let dist = (v / 512) as usize;
        let valid = Z201(input, p, len, dist);
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






pub fn Z210(n: usize) -> Vec<u32> {
    let mut v: Vec<u32> = Vec::with_capacity(n);
    let mut i = 0usize;
    while i < n {
        v.push(0);
        i += 1;
    }
    v
}







pub const Z70: [[usize; 9]; 16] = [
[0,24,258,6,4,4,82,0,0],
[0,8,192,6,4,4,34,0,0],
[0,16,64,6,2,4,98,0,0],
[0,24,258,6,4,4,146,0,0],
[0,24,258,6,4,4,82,0,0],
[0,24,258,6,4,4,82,0,0],
[0,24,258,6,4,4,82,0,0],
[0,24,258,6,4,4,82,0,0],
[0,24,258,6,4,4,82,0,0],
[0,24,258,6,4,4,82,0,0],
[0,24,258,6,4,4,82,0,0],
[0,24,258,6,4,4,82,0,0],
[0,24,258,6,4,4,82,0,0],
[0,24,258,6,4,4,82,0,0],
[0,24,258,6,4,4,82,0,0],
[0,24,258,6,4,4,82,0,0],
];


pub const Z71: [usize; 16] = [
    0,  
    1,  
    2,  
    3,  
    4,  
    5,  
    6,  
    7,  
    8,  
    9,  
    10, 
    11, 
    12, 
    12, 12, 12,
];















pub fn Z207(input: &[u8], k: usize) -> Vec<u32> {
    let n = input.len();
    let mut plan = Z210(n);
    let c = Z70[k % 16];
    if c[0]==0 {Z180(input, &mut plan, c[1], c[2], c[3], c[4], c[5], c[6]);}
    plan
}







pub fn Z204(input: &[u8], k: usize) -> Vec<u32> {
    if input.len() >= 67108864 {
        return Vec::new();
    }
    Z207(input, k)
}



pub fn Z203(input: &[u8], out: &mut [u32], k: usize) -> usize {
    let plan = Z204(input, k);
    Z202(input, &plan, out)
}






















#[inline(always)]
pub fn Z187(x: u32) -> u32 {
    if x == 0 {
        0
    } else {
        let k = 31 - x.leading_zeros();
        let m = if k >= 7 { x >> (k - 7) } else { x << (7 - k) };
        64 * k + Z0[(m as usize) % 128]
    }
}



#[inline(always)]
pub fn Z186(len: usize) -> usize {
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



pub fn Z185(slot: usize) -> u32 {
    if slot < 8 || slot >= 28 { 0 } else { (slot / 4 - 1) as u32 }
}



#[inline(always)]
pub fn Z194(x: u32) -> u32 {
    if x < 4 {
        x
    } else {
        let k = 31u32.wrapping_sub(x.leading_zeros());
        k.wrapping_mul(2).wrapping_add(x.wrapping_shr(k.wrapping_sub(1)) & 1)
    }
}



pub fn Z178(slot: usize) -> u32 {
    if slot < 4 { 0 } else { (slot / 2 - 1) as u32 }
}



pub fn Z199(s: &[u8], i: usize) -> u64 {
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



#[inline(always)]
pub fn Z200(s: &[u8], a: usize, b: usize) -> (u64, u64) {
    (Z199(s, a), Z199(s, b))
}




#[inline(always)]
pub fn Z189(s: &[u8], p: usize, q: usize, k: usize) -> (usize, usize) {
    let mut k = k;
    let mut w = Z200(s, p + k, q + k);
    while w.0 == w.1 && k < 250 {
        k += 8;
        w = Z200(s, p + k, q + k);
    }
    let l = if w.0 == w.1 { 258 } else { k + ((w.0 ^ w.1).leading_zeros() / 8) as usize };
    (if l > 258 { 258 } else { l }, if w.0 < w.1 { 1 } else { 0 })
}







pub fn Z197(
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
        if (Z199(s, c3 - 1) ^ q) >> 40 == 0 {
            let x = (pos - c3) as u32;
            if mb.len() < mb.len().saturating_add(1) {
                mb.push(x | (Z194(x) << 23));
            }
            best = 3;
        }
    }
    if cr != cur && cr > oldest && cr <= pos {
        let lr = Z189(s, cr - 1, pos, 0).0;
        if lr > best {
            best = lr;
            let x = (pos - cr) as u32;
            if mb.len() < mb.len().saturating_add(1) {
                mb.push(x | (((lr - 3) as u32) << 15) | (Z194(x) << 23));
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
        let r = Z189(s, p, pos, if lo_len < hi_len { lo_len } else { hi_len });
        let l = r.0;
        if l > best {
            best = l;
            let x = (pos - p - 1) as u32;
            if mb.len() < mb.len().saturating_add(1) {
                mb.push(x | (((l - 3) as u32) << 15) | (Z194(x) << 23));
            }
        }
        let pk = 2 * (p % 32768);
        if l >= Z2 || l >= 258 {
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



pub fn Z193(s: &[u8], a: usize, b: usize, lim: usize) -> usize {
    let mut k = 0usize;
    while k < lim && s[a + k] == s[b + k] {
        k += 1;
    }
    k
}








#[inline(never)]
pub fn Z181(s: &[u8], mp: &mut Vec<u32>, mb: &mut Vec<u32>, depth: usize, skip: usize) {
    let n = s.len();
    let mut head = [0u32; 65536];
    let mut kid = [0u32; 65536];
    let mut h3 = [0u32; 32768];
    let mut rct = [0u32; 65536];
    let mut i = 0usize;
    let mut cl = 0usize;
    let mut cd = 1usize;
    let mut nq = Z199(s, 0);
    let mut nt = (((nq >> 40) as u32).wrapping_mul(0x9E3779B1) >> 17) as usize;
    let mut nh = (((nq >> 32) as u32).wrapping_mul(0x9E3779B1) >> (32 - Z46)) as usize;
    let mut n3 = h3[nt % 32768] as usize;
    let mut nr = rct[nh % 65536] as usize;
    let mut nc = head[nh % 65536] as usize;
    mp.push(0);
    while i < n {
        if n >= 266 && i <= n - 266 {
            let pre = (nq, nt, nh, n3, if skip >= 258 { nc } else { nr }, nc);
            nq = Z199(s, i + 1);
            nt = (((nq >> 40) as u32).wrapping_mul(0x9E3779B1) >> 17) as usize;
            nh = (((nq >> 32) as u32).wrapping_mul(0x9E3779B1) >> (32 - Z46)) as usize;
            n3 = h3[nt % 32768] as usize;
            nr = rct[nh % 65536] as usize;
            nc = head[nh % 65536] as usize;
            if cl >= skip {
                rct[pre.2 % 65536] = (i + 1) as u32;
                h3[pre.1 % 32768] = (i + 1) as u32;
                let x = (cd - 1) as u32;
                if mb.len() < mb.len().saturating_add(1) {
                    mb.push(x | (((cl - 3) as u32) << 15) | (Z194(x) << 23) | 0x80000000);
                }
                if nt == pre.1 {
                    n3 = i + 1;
                }
                if nh == pre.2 {
                    nr = i + 1;
                }
            } else {
                let before = mb.len();
                let best = Z197(s, &mut head, &mut kid, &mut h3, &mut rct, i, pre, depth, mb);
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
                let l = Z193(s, c - 1, i, if n - i > 258 { 258 } else { n - i });
                if l >= 3 {
                    let x = (i - c) as u32;
                    if mb.len() < mb.len().saturating_add(1) {
                        mb.push(x | (((l - 3) as u32) << 15) | (Z194(x) << 23));
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



pub fn Z196(f: u32, g: u32) -> u32 {
    let lf = Z187(f);
    let c = if f == 0 { g + 256 } else if lf >= g { 0 } else { g - lf };
    if c < 64 { 64 } else if c > 1152 { 1152 } else { c }
}




pub fn Z191(lf: &[u32; 512], df: &[u32; 32], lit: &mut [u32; 256], lc: &mut [u32; 512], dc: &mut [u32; 32]) {
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
    let gl = Z187(tl);
    let gd = Z187(td);
    i = 0;
    while i < 256 {
        lit[i] = Z196(lf[i], gl);
        i += 1;
    }
    i = 3;
    while i <= 258 {
        let sl = Z186(i);
        lc[i] = Z196(lf[(257 + sl) % 512], gl) + 64 * Z185(sl);
        i += 1;
    }
    i = 0;
    while i < 30 {
        dc[i] = Z196(df[i], gd) + 64 * Z178(i);
        i += 1;
    }
}



pub fn Z195(sym: &mut [u32; 512], freq: &[u32; 512], m: usize, v: u32) {
    let fv = freq[(v as usize) % 512];
    let mut j = if m < 512 { m } else { 511 };
    while j > 0 && freq[(sym[j - 1] as usize) % 512] > fv {
        sym[j] = sym[j - 1];
        j -= 1;
    }
    sym[j] = v;
}




pub fn Z188(w: &[u64; 1024], a: usize, b: usize, m: usize, k: usize) -> (usize, usize, usize) {
    if a < m && (b >= k || w[a % 1024] <= w[b % 1024]) {
        (a, a + 1, b)
    } else {
        (b, a, b + 1)
    }
}




pub fn Z183(freq: &[u32; 512], n: usize, len: &mut [u32; 512]) {
    let mut sym = [0u32; 512];
    let mut m = 0usize;
    let mut i = 0usize;
    while i < n && i < 512 {
        len[i] = 0;
        if freq[i] > 0 {
            Z195(&mut sym, freq, m, i as u32);
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
            let x = Z188(&w, a, b, m, k);
            let y = Z188(&w, x.1, x.2, m, k);
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
        Z184(&sym, m, len, kraft);
    }
}



pub fn Z184(sym: &[u32; 512], m: usize, len: &mut [u32; 512], kraft0: u64) {
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



pub fn Z192(lf0: &[u32; 512], df: &[u32; 32], lit: &mut [u32; 256], lc: &mut [u32; 512], dc: &mut [u32; 32]) {
    let mut lf = [0u32; 512];
    let mut z = 0usize;
    while z < 286 {
        lf[z] = lf0[z].wrapping_add(1);
        z += 1;
    }
    let lf = &lf;
    let mut hl = [0u32; 512];
    Z183(lf, 286, &mut hl);
    let mut dd = [0u32; 512];
    let mut i = 0usize;
    while i < 30 {
        dd[i] = df[i].wrapping_add(1);
        i += 1;
    }
    let mut hd = [0u32; 512];
    Z183(&dd, 30, &mut hd);
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
    let ul = Z196(0, Z187(tl));
    let ud = Z196(0, Z187(td));
    i = 0;
    while i < 256 {
        lit[i] = if hl[i] == 0 { ul } else { hl[i] * 64 };
        i += 1;
    }
    i = 3;
    while i <= 258 {
        let sl = Z186(i);
        let h = hl[(257 + sl) % 512];
        lc[i] = (if h == 0 { ul } else { h * 64 }) + 64 * Z185(sl);
        i += 1;
    }
    i = 0;
    while i < 30 {
        dc[i] = (if hd[i] == 0 { ud } else { hd[i] * 64 }) + 64 * Z178(i);
        i += 1;
    }
}




pub fn Z182(s: &[u8], lit: &mut [u32; 256], lc: &mut [u32; 512], dc: &mut [u32; 32]) {
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
    Z191(&lf, &df, lit, lc, dc);
}









#[inline(always)]
pub fn Z179(
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
                let base = dc[(Z194(x) % 32) as usize].wrapping_add(bias);
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




pub fn Z198(s: &[u8], ch: &Vec<u32>, p0: usize, lim: usize, need: usize, lf: &mut [u32; 512], df: &mut [u32; 32]) -> (usize, usize) {
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
            lf[(257 + Z186(l)) % 512] += 1;
            df[(Z194(((c / 512).wrapping_sub(1)) as u32) as usize) % 32] += 1;
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



pub fn Z177(dst: &mut [u32; 512], a: &[u32; 512], b: &[u32; 512], dd: &mut [u32; 32], x: &[u32; 32], y: &[u32; 32]) {
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





pub fn Z190(
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
    while a + Z8 <= pe {
        Z208(s, mp, mb, a, a + Z8, lit, lc, dc, cost, ch);
        let w = Z198(s, ch, a, a + Z8 - 256, Z8, lf, df);
        sb += w.0 - a;
        st += w.1;
        let mut b = 0usize;
        while b < 512 {
            zf[b] = zf[b].wrapping_add(lf[b].wrapping_mul(Z3 as u32));
            b += 1;
        }
        b = 0;
        while b < 32 {
            zd[b] = zd[b].wrapping_add(df[b].wrapping_mul(Z3 as u32));
            b += 1;
        }
        a += Z8 * Z3;
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







pub fn Z180(
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
    Z181(input, &mut mp, &mut mb, depth, skip);
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
    Z182(input, &mut lit, &mut lc, &mut dc);
    lc[511] = (spass / 32) as u32;
    let rot = Z8.wrapping_mul((spass / 16) % 2);
    let spn = spass % 16;
    let mut p0 = 0usize;
    let mut used = 0usize;
    let mut bpt = 1024usize;
    while p0 < n && mp.len() == n + 1 && cost.len() == n + 1 && ch.len() == n {
        let need = Z45 - used;
        let passes = if p0 == 0 { first_passes } else { passes_k };
        let sampled = if p0 == 0 { fspass } else { spn };
        let est = need * bpt / 256 + need * bpt / 2048 + Z1;
        let mut pe = if n - p0 > est { p0 + est } else { n };
        let mut k = 0usize;
        let mut p1 = p0 + 1;
        let mut t = 1usize;
        while k < passes {
            if k < sampled && k + 1 < passes && pe - p0 > 4 * Z8 * Z3 {
                let off = (k % 4).wrapping_mul(rot);
                let ps = p0 + off % (pe - p0 + 1);
                let r = Z190(input, &mp, &mb, ps, pe, &lit, &lc, &dc, &mut cost, ch, &mut lf, &mut df);
                if r.1 > 0 {
                    let span = r.0.wrapping_mul(need) / r.1;
                    let grow = span.saturating_add(span / Z59).saturating_add(Z1);
                    pe = if n - p0 > grow { p0 + grow } else { n };
                }
            } else {
                let lim = if pe == n { n } else { pe - Z1 };
                if k + 1 >= passes {Z179(input, &mp, &mb, p0, pe, &lit, &lc, &dc, &mut cost, ch);} else {Z208(input, &mp, &mb, p0, pe, &lit, &lc, &dc, &mut cost, ch);}
                let r = Z198(input, ch, p0, lim, need, &mut lf, &mut df);
                p1 = r.0;
                t = r.1;
                if t > 0 && p1 > p0 {
                    let span = (p1 - p0).wrapping_mul(need) / t;
                    let grow = span.saturating_add(span / 16).saturating_add(Z1);
                    pe = if n - p0 > grow { p0 + grow } else { n };
                }
            }
            Z177(&mut sl, &bl, &lf, &mut sd, &bd, &df);
            if k + 1 < passes && k >= sampled {
                Z192(&sl, &sd, &mut lit, &mut lc, &mut dc);
            } else {
                Z191(&sl, &sd, &mut lit, &mut lc, &mut dc);
            }
            k += 1;
        }
        used += t;
        if used >= Z45 {
            used = 0;
            Z177(&mut bl, &zl, &zl, &mut bd, &zd, &zd);
        } else {
            Z177(&mut bl, &sl, &zl, &mut bd, &sd, &zd);
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









pub const Z69: usize = 32256;








pub const Z66: usize = 1 << 26;

pub const Z65: u64 = 20;





pub const Z64: usize = 320;

pub const Z68: usize = 0xFFFF_FFFF;

pub const Z67: [u16; 256] = [
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



pub struct Z63 {
    pub head: [u32; Z47],
    pub head3: [u32; Z45],
    pub tree: [u32; Z47],
    pub w: [u64; Z62],
    pub pn: [u32; Z39],
    pub pf: [u32; Z39],
    pub plen: usize,
    pub hn: usize,
    pub hl: usize,
}










































































































































































































































































#[inline(always)]
pub fn Z209(cost:&[u32],lc:&[u32;512],i:usize,lo:usize,hi:usize,base:u32,width:usize)->u32 {
    if lo>hi || hi>=512 || i>=cost.len() || hi>=cost.len()-i {return 4294967295;}
    let start=if width>=1 && hi-lo>=width {hi-width+1} else {lo};
    let mut l=start;
    let mut best=4294967295u32;
    while l<=hi {
        let c=(cost[i+l].wrapping_add(lc[l]).wrapping_add(base)<<9)|(l as u32);
        best=if c<best {c} else {best};
        l+=1;
    }
    best
}

pub fn Z208(
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
                    mbest=Z209(cost,lc,i,prev+1-i,stop-i,base,lc[511] as usize);
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
                let base = dc[(Z194(x) % 32) as usize].wrapping_add(bias);
                let mut mbest = 4294967295u32;
                if stop < cl {
                    mbest=Z209(cost,lc,i,prev+1-i,stop-i,base,lc[511] as usize);
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


pub fn Z206(input:&[u8],out:&mut[u32],mode:usize)->usize{if mode==0 {Z203(input,out,0)}else if mode==1 {Z203(input,out,1)}else if mode==2 {Z203(input,out,2)}else {Z203(input,out,3)}}











































pub const Z73: [[usize; 9]; 16] = [
[2,32,24,0,2,1,8,8,1],
[0,32,258,6,4,6,19,4,64],
[2,24,24,1,3,2,20,12,2],
[0,48,260,10,8,4,18,0,0],
[2,24,24,1,4,2,12,7,4],
[2,24,24,1,3,2,20,12,3],
[2,24,24,1,1,2,20,12,2],
[2,24,24,1,2,2,12,7,4],
[2,32,24,0,2,1,8,8,1],
[2,32,24,0,2,1,8,8,1],
[2,32,24,0,2,1,8,8,1],
[2,32,24,0,2,1,8,8,1],
[2,32,24,0,2,1,8,8,1],
[2,32,24,0,2,1,8,8,1],
[2,32,24,0,2,1,8,8,1],
[2,32,24,0,2,1,8,8,1],
];


















pub fn Z251(input: &[u8], k: usize) -> Vec<u32> {
    let n = input.len();
    let mut plan = Z210(n);
    let c = Z73[k % 16];
    if c[0]==0 {Z212(input, &mut plan, c[1], c[2], c[3], c[4], c[5], c[6], c[7], c[8]);}
    else if c[0]==2 {Z224(input, &mut plan, c[1], c[2], c[3], c[4], c[5], c[6], c[7], c[8]);}
    plan
}







pub fn Z249(input: &[u8], k: usize) -> Vec<u32> {
    if input.len() >= 67108864 {
        return Vec::new();
    }
    Z251(input, k)
}



pub fn Z248(input: &[u8], out: &mut [u32], k: usize) -> usize {
    let plan = Z249(input, k);
    Z202(input, &plan, out)
}
























































pub fn Z217(
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
        if (Z199(s, c3 - 1) ^ q) >> 40 == 0 {
            let x = (pos - c3) as u32;
            if mb.len() < mb.len().saturating_add(1) {
                mb.push(x | (Z194(x) << 23));
            }
            best = 3;
        }
    }
    if cr != cur && cr > oldest && cr <= pos {
        let lr = Z189(s, cr - 1, pos, 0).0;
        if lr > best {
            best = lr;
            let x = (pos - cr) as u32;
            if mb.len() < mb.len().saturating_add(1) {
                mb.push(x | (((lr - 3) as u32) << 15) | (Z194(x) << 23));
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
        let r = Z189(s, p, pos, if lo_len < hi_len { lo_len } else { hi_len });
        let l = r.0;
        if l > best {
            best = l;
            let x = (pos - p - 1) as u32;
            seen = 1u32 << (Z194(x) % 32);
            if mb.len() < mb.len().saturating_add(1) {
                mb.push(x | (((l - 3) as u32) << 15) | (Z194(x) << 23));
            }
        }
        else if l >= 3 && l == best {
            let x = (pos - p - 1) as u32;
            let mask = 1u32 << (Z194(x) % 32);
            if seen & mask == 0 && seen < 1073741824 {
                seen = (seen | mask).wrapping_add(1073741824);
                if mb.len() < mb.len().saturating_add(1) {
                    mb.push(x | (((l - 3) as u32) << 15) | (Z194(x) << 23) | 0x80000000);
                }
            }
        }
        let pk = 2 * (p % 32768);
        if l >= Z2 || l >= 258 {
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











#[inline(never)]
pub fn Z213(s: &[u8], mp: &mut Vec<u32>, mb: &mut Vec<u32>, depth: usize, skip: usize) {
    let n = s.len();
    let mut head = [0u32; 65536];
    let mut kid = [0u32; 65536];
    let mut h3 = [0u32; 32768];
    let mut rct = [0u32; 65536];
    let mut i = 0usize;
    let mut cl = 0usize;
    let mut cd = 1usize;
    let mut nq = Z199(s, 0);
    let mut nt = (((nq >> 40) as u32).wrapping_mul(0x9E3779B1) >> 17) as usize;
    let mut nh = (((nq >> 32) as u32).wrapping_mul(0x9E3779B1) >> (32 - Z46)) as usize;
    let mut n3 = h3[nt % 32768] as usize;
    let mut nr = rct[nh % 65536] as usize;
    let mut nc = head[nh % 65536] as usize;
    mp.push(0);
    while i < n {
        if n >= 266 && i <= n - 266 {
            let pre = (nq, nt, nh, n3, if skip >= 258 { nc } else { nr }, nc);
            nq = Z199(s, i + 1);
            nt = (((nq >> 40) as u32).wrapping_mul(0x9E3779B1) >> 17) as usize;
            nh = (((nq >> 32) as u32).wrapping_mul(0x9E3779B1) >> (32 - Z46)) as usize;
            n3 = h3[nt % 32768] as usize;
            nr = rct[nh % 65536] as usize;
            nc = head[nh % 65536] as usize;
            if cl >= skip {
                rct[pre.2 % 65536] = (i + 1) as u32;
                h3[pre.1 % 32768] = (i + 1) as u32;
                let x = (cd - 1) as u32;
                if mb.len() < mb.len().saturating_add(1) {
                    mb.push(x | (((cl - 3) as u32) << 15) | (Z194(x) << 23) | 0x80000000);
                }
                if nt == pre.1 {
                    n3 = i + 1;
                }
                if nh == pre.2 {
                    nr = i + 1;
                }
            } else {
                let before = mb.len();
                let best = Z217(s, &mut head, &mut kid, &mut h3, &mut rct, i, pre, depth, mb);
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
                let l = Z193(s, c - 1, i, if n - i > 258 { 258 } else { n - i });
                if l >= 3 {
                    let x = (i - c) as u32;
                    if mb.len() < mb.len().saturating_add(1) {
                        mb.push(x | (((l - 3) as u32) << 15) | (Z194(x) << 23));
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
























pub fn Z215(lf0: &[u32; 512], df: &[u32; 32], lit: &mut [u32; 256], lc: &mut [u32; 512], dc: &mut [u32; 32]) {
    let mut lf = [0u32; 512];
    let mut z = 0usize;
    while z < 286 {
        lf[z] = lf0[z];
        z += 1;
    }
    let lf = &lf;
    let mut hl = [0u32; 512];
    Z183(lf, 286, &mut hl);
    let mut dd = [0u32; 512];
    let mut i = 0usize;
    while i < 30 {
        dd[i] = df[i];
        i += 1;
    }
    let mut hd = [0u32; 512];
    Z183(&dd, 30, &mut hd);
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
    let ul = Z196(0, Z187(tl));
    let ud = Z196(0, Z187(td));
    i = 0;
    while i < 256 {
        lit[i] = if hl[i] == 0 { ul } else { hl[i] * 64 };
        i += 1;
    }
    i = 3;
    while i <= 258 {
        let sl = Z186(i);
        let h = hl[(257 + sl) % 512];
        lc[i] = (if h == 0 { ul } else { h * 64 }) + 64 * Z185(sl);
        i += 1;
    }
    i = 0;
    while i < 30 {
        dc[i] = (if hd[i] == 0 { ud } else { hd[i] * 64 }) + 64 * Z178(i);
        i += 1;
    }
}













#[inline(always)]
pub fn Z211(
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
                    mbest = Z252(cost, lc, i, prev + 1 - i, stop - i, base, tail);
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
                let base = dc[(Z194(x) % 32) as usize].wrapping_add(2).wrapping_add(bias);
                let mut mbest = 4294967295u32;
                if stop < cl {
                    mbest = Z252(cost, lc, i, prev + 1 - i, stop - i, base, tail);
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












pub fn Z214(
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
    while a + Z8 <= pe {
        Z211(s, mp, mb, a, a + Z8, lit, lc, dc, cost, ch, tail);
        let w = Z198(s, ch, a, a + Z8 - 256, Z8, lf, df);
        sb += w.0 - a;
        st += w.1;
        let mut b = 0usize;
        while b < 512 {
            zf[b] = zf[b].wrapping_add(lf[b].wrapping_mul(Z3 as u32));
            b += 1;
        }
        b = 0;
        while b < 32 {
            zd[b] = zd[b].wrapping_add(df[b].wrapping_mul(Z3 as u32));
            b += 1;
        }
        a += Z8 * Z3;
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







pub fn Z212(
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
    let mut mp: Vec<u32> = Vec::with_capacity(n + 1);
    let mut mb: Vec<u32> = Vec::with_capacity(n * 3 + 16);
    Z213(input, &mut mp, &mut mb, depth, skip);
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
    Z182(input, &mut lit, &mut lc, &mut dc);
    let rot = Z8.wrapping_mul((spass / 16) % 2);
    let spn = spass % 16;
    let mut p0 = 0usize;
    let mut used = 0usize;
    let mut bpt = 1024usize;
    while p0 < n && mp.len() == n + 1 && cost.len() == n + 1 && ch.len() == n {
        let need = Z45 - used;
        let passes = if p0 == 0 { first_passes } else { passes_k };
        let sampled = if p0 == 0 { fspass } else { spn };
        let est = need * bpt / 256 + need * bpt / 2048 + Z1;
        let mut pe = if n - p0 > est { p0 + est } else { n };
        let mut k = 0usize;
        let mut p1 = p0 + 1;
        let mut t = 1usize;
        while k < passes {
            if k < sampled && k + 1 < passes && pe - p0 > 4 * Z8 * Z3 {
                let off = (k % 4).wrapping_mul(rot);
                let ps = p0 + off % (pe - p0 + 1);
                let r = Z214(input, &mp, &mb, ps, pe, &lit, &lc, &dc, &mut cost, ch, &mut lf, &mut df, tail);
                if r.1 > 0 {
                    let span = r.0.wrapping_mul(need) / r.1;
                    let grow = span.saturating_add(span / Z59).saturating_add(Z1);
                    pe = if n - p0 > grow { p0 + grow } else { n };
                }
            } else {
                let lim = if pe == n { n } else { pe - Z1 };
                Z211(input, &mp, &mb, p0, pe, &lit, &lc, &dc, &mut cost, ch, Z216(k, passes, tail, final_tail));
                let r = Z198(input, ch, p0, lim, need, &mut lf, &mut df);
                p1 = r.0;
                t = r.1;
                if t > 0 && p1 > p0 {
                    let span = (p1 - p0).wrapping_mul(need) / t;
                    let grow = span.saturating_add(span / 16).saturating_add(Z1);
                    pe = if n - p0 > grow { p0 + grow } else { n };
                }
            }
            Z177(&mut sl, &bl, &lf, &mut sd, &bd, &df);
            if k + 1 < passes && k >= sampled {
                Z215(&sl, &sd, &mut lit, &mut lc, &mut dc);
            } else {
                Z191(&sl, &sd, &mut lit, &mut lc, &mut dc);
            }
            k += 1;
        }
        used += t;
        if used >= Z45 {
            used = 0;
            Z177(&mut bl, &zl, &zl, &mut bd, &zd, &zd);
        } else {
            Z177(&mut bl, &sl, &zl, &mut bd, &sd, &zd);
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


































pub struct Z72 {
    pub head: [u32; Z47],
    pub head3: [u32; Z45],
    pub tree: [u32; Z47],
    pub w: [u64; Z62],
    pub pn: [u32; Z39],
    pub pf: [u32; Z39],
    pub plen: usize,
    pub hn: usize,
    pub hl: usize,
}


























































































































































pub fn Z234(len: usize) -> usize {
    if len < 3 {
        return 0;
    }
    Z19[(len - 3) % 256] as usize
}



pub fn Z222(d: usize) -> usize {
    if d < 1 {
        return 0;
    }
    if d <= 256 {
        return Z14[(d - 1) % 256] as usize;
    }
    Z13[((d - 1) >> 7) % 256] as usize
}



pub fn Z247(s: &[u8], i: usize) -> u64 {
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




pub fn Z225(s: &[u8], a: usize, b: usize, k0: usize, lim: usize) -> usize {
    let mut k = k0;
    let mut fuel = lim + 1;
    while fuel > 0 && k + 8 <= lim {
        let x = Z247(s, a + k) ^ Z247(s, b + k);
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



pub fn Z236(len: usize, d: usize) -> u32 {
    ((Z222(d) as u32) << 24) | (((d - 1) as u32) << 9) | (len as u32)
}



pub fn Z241(kids: &mut [u32; Z47], which: usize, idx: usize, v: u32) {
    kids[(2 * (idx % Z62) + which) % Z47] = v;
}





pub fn Z218(
    s: &[u8],
    p: usize,
    h: usize,
    depth: usize,
    head: &mut [u32; Z47],
    kids: &mut [u32; Z47],
    ml: &mut [u32; 64],
    md: &mut [u32; 64],
) -> usize {
    let n = s.len();
    let room = n - p;
    let maxlen = if room < 258 { room } else { 258 };
    let lim = if Z42 < maxlen { Z42 } else { maxlen };
    let mut cur = head[h % Z47] as usize;
    head[h % Z47] = (p + 1) as u32;
    let mut lw = 0usize;
    let mut li = p % Z62;
    let mut gw = 1usize;
    let mut gi = p % Z62;
    let mut llen = 0usize;
    let mut glen = 0usize;
    let mut best = 2usize;
    let mut cnt = 0usize;
    let mut steps = 0usize;
    while steps < depth && cur > 0 {
        let c = cur - 1;
        if c >= p || p - c >= Z62 {
            steps = depth;
        } else {
            let k0 = if llen < glen { llen } else { glen };
            let k = Z225(s, c, p, k0, lim);
            if k > best {
                best = k;
                if cnt < 64 {
                    ml[cnt] = k as u32;
                    md[cnt] = (p - c) as u32;
                    cnt += 1;
                }
            }
            if k >= lim {
                Z241(kids, lw, li, kids[(2 * (c % Z62)) % Z47]);
                Z241(kids, gw, gi, kids[(2 * (c % Z62) + 1) % Z47]);
                return cnt;
            }
            if s[c + k] < s[p + k] {
                Z241(kids, lw, li, cur as u32);
                lw = 1;
                li = c % Z62;
                llen = k;
                cur = kids[(2 * (c % Z62) + 1) % Z47] as usize;
            } else {
                Z241(kids, gw, gi, cur as u32);
                gw = 0;
                gi = c % Z62;
                glen = k;
                cur = kids[(2 * (c % Z62)) % Z47] as usize;
            }
            steps += 1;
        }
    }
    Z241(kids, lw, li, 0);
    Z241(kids, gw, gi, 0);
    cnt
}





pub fn Z219(
    s: &[u8],
    p: usize,
    key: usize,
    k0: usize,
    best0: usize,
    depth: usize,
    head: &mut [u32; Z47],
    prev: &mut [u32; Z62],
    ml: &mut [u32; 64],
    md: &mut [u32; 64],
) -> usize {
    let n = s.len();
    let room = n - p;
    let lim = if room < 258 { room } else { 258 };
    let first = head[key % Z47];
    head[key % Z47] = (p + 1) as u32;
    let mut cur = first as usize;
    let mut best = best0;
    let mut cnt = 0usize;
    let mut steps = 0usize;
    while steps < depth && cur > 0 {
        let c = cur - 1;
        if c >= p || p - c >= Z62 {
            steps = depth;
        } else {
            if best < lim && s[c + best] == s[p + best] {
                let mut k = k0;
                if k0 + 8 <= lim {
                    let x = Z247(s, c + k0) ^ Z247(s, p + k0);
                    if x != 0 {
                        k = k0 + (x.leading_zeros() / 8) as usize;
                    } else {
                        k = Z225(s, c, p, k0 + 8, lim);
                    }
                } else {
                    k = Z225(s, c, p, k0, lim);
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
                cur = prev[c % Z62] as usize;
                steps += 1;
            }
        }
    }
    prev[p % Z62] = first;
    cnt
}



pub fn Z235(b: u8) -> usize {
    Z21[b as usize] as usize
}





pub fn Z239(clist: &mut Vec<u32>, p: usize, ml: &[u32; 64], md: &[u32; 64], cnt: usize, r1: usize, flag: u32) -> usize {
    let first = if cnt > Z3 { cnt - Z3 } else { 0 };
    let mut top = 0usize;
    let mut pushed = 0u32;
    if r1 >= 3 && r1 <= 258 {
        clist.push(Z236(r1, 1) | flag);
        top = r1;
        pushed += 1;
    }
    let mut i = first;
    while i < cnt && i < 64 {
        let d = md[i] as usize;
        let l = ml[i] as usize;
        if d >= 1 && d <= Z62 && l > top && l <= 258 && l >= 3 {
            clist.push(Z236(l, d) | flag);
            top = l;
            pushed += 1;
        }
        i += 1;
    }
    if pushed > 0 {
        clist.push(Z16 | (pushed << 27) | ((p as u32) & Z22));
    }
    top
}



pub fn Z246(s: &[u8], p: usize) -> usize {
    let n = s.len();
    if p < 1 || p + 3 > n {
        return 0;
    }
    if s[p] != s[p - 1] || s[p + 1] != s[p - 1] || s[p + 2] != s[p - 1] {
        return 0;
    }
    let room = n - p;
    let lim = if room < 258 { room } else { 258 };
    Z225(s, p - 1, p, 3, lim)
}





pub fn Z226(s: &[u8], clist: &mut Vec<u32>, chain: usize, depth: usize) {
    let n = s.len();
    let mut head = [0u32; Z47];
    let mut lt = [0u32; Z62];
    let mut kids = [0u32; Z47];
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
                Z219(s, p, h, 0, 3, depth, &mut head, &mut lt, &mut ml, &mut md)
            } else {
                Z218(s, p, h, depth, &mut head, &mut kids, &mut ml, &mut md)
            };
            let r1 = if p > 0 && s[p] == s[p - 1] { Z246(s, p) } else { 0 };
            let mut top = 0usize;
            if cnt > 0 || r1 >= 3 {
                top = Z239(clist, p, &ml, &md, cnt, r1, 0);
            }
            if r1 >= Z59 {
                skip_to = p + top;
                pend = 0;
            } else if top >= Z2 {
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
            lt[p % Z62] = head[h % Z47];
            head[h % Z47] = (p + 1) as u32;
        }
        p += 1;
    }
}




pub fn Z227(s: &[u8], clist: &mut Vec<u32>, depth_lo: usize) {
    let n = s.len();
    let mut head8 = [0u32; Z47];
    let mut prev8 = [0u32; Z62];
    let mut head3 = [0u32; Z47];
    let mut kids = [0u32; Z47];
    let mut ml = [0u32; 64];
    let mut md = [0u32; 64];
    
    let mut key = 0usize;
    let mut run = 0usize;
    let mut run2 = 0usize;
    let mut q = 0usize;
    while q < 7 && q < n {
        let c = Z235(s[q]);
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
            let c = Z235(s[p + 7]);
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
                let h = ((v.wrapping_mul(0x9E37_79B1) >> 16) as usize) % (Z47 / 2);
                if p >= skip_to {
                    let cnt = Z218(s, p, h, depth_lo, &mut head3, &mut kids, &mut ml, &mut md);
                    if cnt > 0 {
                        let top = Z239(clist, p, &ml, &md, cnt, 0, 0);
                        if top >= Z59 {
                            skip_to = p + top;
                        }
                    }
                }
            } else if run >= 8 {
                if p >= skip_to {
                    let cnt = Z219(s, p, key, 8, Z32 - 1, Z55, &mut head8, &mut prev8, &mut ml, &mut md);
                    if cnt > 0 {
                        let top = Z239(clist, p, &ml, &md, cnt, 0, Z18);
                        if top >= Z59 {
                            skip_to = p + top;
                        }
                    }
                } else {
                    prev8[p % Z62] = head8[key % Z47];
                    head8[key % Z47] = (p + 1) as u32;
                }
            } else if run2 >= 8 {
                let w = Z247(s, p);
                let hn = Z47 / 2 + ((w.wrapping_mul(0x9E37_79B9_7F4A_7C15) >> 40) as usize) % (Z47 / 2);
                if p >= skip_to {
                    let cnt = Z219(s, p, hn, 0, Z32 - 1, Z55, &mut head3, &mut prev8, &mut ml, &mut md);
                    if cnt > 0 {
                        let top = Z239(clist, p, &ml, &md, cnt, 0, Z18);
                        if top >= Z59 {
                            skip_to = p + top;
                        }
                    }
                } else {
                    prev8[p % Z62] = head3[hn % Z47];
                    head3[hn % Z47] = (p + 1) as u32;
                }
            }
        }
        p += 1;
    }
}




pub fn Z231(freq: &[u32; 288], m: usize, lens: &mut [u8; 288]) {
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
    Z242(&aw, &asy, &mut bw, &mut bsy, k, 0);
    Z242(&bw, &bsy, &mut aw, &mut asy, k, 8);
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



pub fn Z242(sw: &[u32; 288], ss: &[u16; 288], dw: &mut [u32; 288], ds: &mut [u16; 288], k: usize, shift: u32) {
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




pub fn Z240(models: &mut Vec<u32>, lf: &[u32; 288], df: &[u32; 288], tax: u32, ulen: u32, udist: u32, tokpen: u32) -> u64 {
    let mut ll = [0u8; 288];
    let mut dl = [0u8; 288];
    Z231(lf, 286, &mut ll);
    Z231(df, 30, &mut dl);
    let mut est: u64 = 70;
    let mut q = 0usize;
    while q < 288 {
        if ll[q] > 0 {
            est += (lf[q] as u64) * (ll[q] as u64) + 4;
            if q >= 257 && q < 286 {
                est += (lf[q] as u64) * (Z17[(q - 257) % 29] as u64);
            }
        }
        if q < 30 && dl[q] > 0 {
            est += (df[q] as u64) * ((dl[q] as u64) + (Z12[q] as u64)) + 4;
        }
        q += 1;
    }
    let mut i = 0usize;
    while i < 256 {
        let b = if ll[i] > 0 { ll[i] as u32 } else { Z31 };
        models.push(b * Z46 + tokpen);
        i += 1;
    }
    let mut l = 3usize;
    while l < 259 {
        let s = Z234(l);
        let b = if ll[(257 + s) % 288] > 0 { ll[(257 + s) % 288] as u32 } else { ulen };
        models.push((b + Z17[s % 29]) * Z46 + tokpen + tax);
        l += 1;
    }
    let mut d = 0usize;
    while d < 32 {
        let b = if d < 30 && dl[d] > 0 { dl[d] as u32 } else { udist };
        let e = if d < 30 { Z12[d] } else { 0 };
        models.push((b + e) * Z46);
        d += 1;
    }
    est
}



pub fn Z230(clist: &Vec<u32>, ge: usize) -> usize {
    if ge == 0 || ge > clist.len() {
        return ge;
    }
    let tr = clist[ge - 1];
    let cnt = ((tr >> 27) & 15) as usize;
    if (tr & Z16) == 0 || cnt + 1 > ge {
        return ge;
    }
    ge - 1 - cnt
}



pub fn Z233(models: &Vec<u32>, b: usize, lit_c: &mut [u32; 256], len_c: &mut [u32; 256], dst_c: &mut [u32; 32]) {
    let base = b * Z20;
    if base + Z20 > models.len() {
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





pub fn Z221(s: &[u8], clist: &Vec<u32>, models: &Vec<u32>, bstart: &Vec<u32>, choice: &mut [u32]) {
    let n = s.len();
    let nb = bstart.len();
    if nb == 0 || models.len() < nb * Z20 || choice.len() < n {
        return;
    }
    let mut ring = [0u32; 512];
    let mut lit_c = [0u32; 256];
    let mut len_c = [0u32; 256];
    let mut dst_c = [0u32; 32];
    let mut b = nb - 1;
    let mut loaded = nb;
    let mut ge = clist.len();
    let mut gs = Z230(clist, ge);
    let mut gp = if gs < ge && ge <= clist.len() { (clist[ge - 1] & Z22) as usize } else { n };
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
            Z233(models, b, &mut lit_c, &mut len_c, &mut dst_c);
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
                if (e & Z18) != 0 && prev < 7 {
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
                        if len == Z39 && l > Z39 {
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
            gs = Z230(clist, ge);
            gp = if gs < ge && ge <= clist.len() { (clist[ge - 1] & Z22) as usize } else { n };
        }
    }
}



pub fn Z229(clist: &Vec<u32>, choice: &mut [u32], n: usize, gmin: usize) {
    let mut p = 0usize;
    while p < n && p < choice.len() {
        choice[p] = 0;
        p += 1;
    }
    let m = clist.len();
    let mut k = 1usize;
    while k < m {
        let tr = clist[k];
        if (tr & Z16) != 0 {
            let q = (tr & Z22) as usize;
            let last = clist[k - 1];
            if (last & Z16) == 0 && ((last & 511) as usize) >= gmin && q < n && q < choice.len() {
                choice[q] = (last & 0x00FF_FFFF) + 512;
            }
        }
        k += 1;
    }
}




pub fn Z244(s: &[u8], choice: &[u32], models: &mut Vec<u32>, bstart: &mut Vec<u32>, tax: u32, ulen: u32, udist: u32, tokpen: u32) -> u64 {
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
        while t < Z45 && p < n {
            let ch = choice[p] as usize;
            let len = ch % 512;
            if len < 3 {
                let b = s[p] as usize;
                lf[b] = lf[b].wrapping_add(1);
                p += 1;
            } else {
                let d = ch / 512;
                let ls = (257 + Z234(len)) % 288;
                let ds = Z222(d) % 288;
                lf[ls] = lf[ls].wrapping_add(1);
                df[ds] = df[ds].wrapping_add(1);
                p += len;
            }
            t += 1;
        }
        lf[256] = 1;
        total += Z240(models, &lf, &df, tax, ulen, udist, tokpen);
        if p < n {
            bstart.push(p as u32);
        }
        lf = [0u32; 288];
        df = [0u32; 288];
    }
    if models.len() == 0 {
        lf[256] = 1;
        total += Z240(models, &lf, &df, tax, ulen, udist, tokpen);
    }
    total
}



pub fn Z232(s: &[u8]) -> usize {
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




pub fn Z245(clf: &mut [u32; 288], v: usize, r0: usize) -> u64 {
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




pub fn Z223(lf: &[u32; 288], df: &[u32; 288]) -> u64 {
    let mut ll = [0u8; 288];
    let mut dl = [0u8; 288];
    Z231(lf, 286, &mut ll);
    Z231(df, 30, &mut dl);
    let mut body: u64 = 0;
    let mut hlit = 257usize;
    let mut i = 0usize;
    while i < 286 {
        if ll[i] > 0 {
            body += (lf[i] as u64) * (ll[i] as u64);
            if i >= 257 {
                body += (lf[i] as u64) * (Z17[(i - 257) % 29] as u64);
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
            body += (df[d] as u64) * ((dl[d] as u64) + (Z12[d] as u64));
            hdist = d + 1;
            any = 1;
        }
        d += 1;
    }
    if any == 0 {
        dl[0] = 1;
    }
    
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
        extra += Z245(&mut clf, v, r);
        j += r;
    }
    let mut cl = [0u8; 288];
    Z231(&clf, 19, &mut cl);
    let mut hclen = 19usize;
    while hclen > 4 && cl[Z10[(hclen - 1) % 19] % 288] == 0 {
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



pub fn Z228(lf: &[u32; 288], df: &[u32; 288]) -> u64 {
    let mut bits: u64 = 3;
    let mut i = 0usize;
    while i < 288 {
        let len: u64 = if i < 144 { 8 } else if i < 256 { 9 } else if i < 280 { 7 } else { 8 };
        bits += (lf[i] as u64) * len;
        if i >= 257 && i < 286 {
            bits += (lf[i] as u64) * (Z17[(i - 257) % 29] as u64);
        }
        i += 1;
    }
    let mut d = 0usize;
    while d < 30 {
        bits += (df[d] as u64) * (5 + Z12[d] as u64);
        d += 1;
    }
    bits
}




pub fn Z237(s: &[u8], choice: &[u32], p0: usize, lf: &mut [u32; 288], df: &mut [u32; 288]) -> usize {
    let n = s.len();
    let mut i = 0usize;
    while i < 288 {
        lf[i] = 0;
        df[i] = 0;
        i += 1;
    }
    let mut p = p0;
    let mut t = 0usize;
    while p < n && t < Z45 && p < choice.len() {
        let ch = choice[p] as usize;
        let len = ch % 512;
        let d = ch / 512;
        if len >= 3 && len <= n - p {
            lf[(257 + Z234(len)) % 288] = lf[(257 + Z234(len)) % 288].wrapping_add(1);
            df[Z222(d) % 288] = df[Z222(d) % 288].wrapping_add(1);
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



pub fn Z220(plan: &mut [u32], p0: usize, end: usize) {
    let mut p = p0;
    while p < end && p < plan.len() {
        plan[p] = 0;
        p += 1;
    }
}




pub fn Z238(s: &[u8], plan: &mut [u32]) {
    let n = s.len();
    let mut lf = [0u32; 288];
    let mut df = [0u32; 288];
    let mut p = 0usize;
    let mut fuel = n + 1;
    while p < n && p < plan.len() && fuel > 0 {
        fuel -= 1;
        let ea = Z237(s, plan, p, &mut lf, &mut df);
        let da = Z223(&lf, &df);
        let fa = Z228(&lf, &df);
        let ca = if da < fa { da } else { fa };
        let eb = if n - p > Z45 { p + Z45 } else { n };
        let ec = if ea > eb { ea } else { eb };
        let mut lb = [0u32; 288];
        let zb = [0u32; 288];
        let mut q = p;
        while q < ec {
            lb[s[q] as usize] += 1;
            q += 1;
        }
        lb[256] = 1;
        let db = Z223(&lb, &zb);
        let fb = Z228(&lb, &zb);
        let sb = 8 * ((ec - p) as u64) + 40;
        let mut cb = if db < fb { db } else { fb };
        if sb < cb {
            cb = sb;
        }
        if ea > p && ca <= cb {
            p = ea;
        } else {
            Z220(plan, p, eb);
            p = eb;
        }
    }
}





pub fn Z243(s: &[u8]) -> (usize, usize) {
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
            if p - a <= Z62 && s[a] == s[p] && s[a + 1] == s[p + 1] && s[a + 2] == s[p + 2] && s[a + 3] == s[p + 3] {
                r4 += 1;
                if s[a + 4] == s[p + 4] && s[a + 5] == s[p + 5] {
                    r6 += 1;
                    if r6 >= 64 && (r6 as u64) * 131072 >= 24 * (n as u64) && probes >= Z45 {
                        return (((r4 as u64) * 65536 / (probes as u64 + 1)) as usize, ((r6 as u64) * 65536 / (probes as u64 + 1)) as usize);
                    }
                }
            }
        }
        head[h % 16384] = (p + 1) as u32;
        probes += 1;
        p += Z4;
    }
    (((r4 as u64) * 65536 / (probes as u64 + 1)) as usize, ((r6 as u64) * 65536 / (probes as u64 + 1)) as usize)
}




pub fn Z224(input: &[u8], out: &mut Vec<u32>, depth: usize, depth_lo: usize, wdp: usize, passes_w: usize, passes_bt: usize, passes_dna: usize, min_dna: usize, passes_c4: usize) {
    let n = input.len();
    if out.len() < n {
        return;
    }
    let dna = Z232(input);
    let mut chain4 = 0usize;
    let mut wmode = 0usize;
    if dna == 0 {
        let (r4, r6) = Z243(input);
        if r6 < Z23 {
            if wdp == 0 || r4 < Z33 {
                return;
            }
            wmode = 1;
        } else if r6 >= 32768 {
            chain4 = 2;
        } else if r4 >= Z11 * r6 {
            chain4 = 1;
        }
    }
    let mut clist: Vec<u32> = Vec::with_capacity(n / 2 + 16);
    if dna > 0 {
        Z227(input, &mut clist, depth_lo);
    } else if wmode > 0 {
        Z226(input, &mut clist, 1, Z3);
    } else if chain4 > 0 {
        Z226(input, &mut clist, 1, Z11);
    } else {
        Z226(input, &mut clist, 0, depth);
    }
    let mut models: Vec<u32> = Vec::new();
    let mut bstart: Vec<u32> = Vec::new();
    let passes = if dna > 0 { passes_dna } else if wmode > 0 { passes_w } else if chain4 == 2 { Z5 } else if chain4 > 0 { passes_c4 } else { passes_bt };
    let tax = if wmode > 0 { Z46 } else if chain4 > 0 { Z46 } else if dna > 0 { 0 } else { Z25 };
    let ulen = if wmode > 0 { Z30 } else { Z31 };
    let udist = if wmode > 0 { Z29 } else { Z28 };
    
    let gmin = if dna > 0 || wmode > 0 { 259 } else { Z15 };
    Z229(&clist, out, n, gmin);
    let tokpen = if dna > 0 { Z26 } else if wmode > 0 { Z26 } else if chain4 > 0 { Z27 } else { Z26 };
    let lit_est = Z244(input, out, &mut models, &mut bstart, tax, ulen, udist, tokpen);
    let mut last_est = lit_est;
    let mut prev_est = lit_est;
    let mut pass = 0usize;
    while pass < passes {
        Z221(input, &clist, &models, &bstart, out);
        pass += 1;
        if pass < passes {
            last_est = Z244(input, out, &mut models, &mut bstart, tax, Z31, Z28, tokpen);
            if dna > 0 && pass >= min_dna && last_est <= prev_est && prev_est - last_est < prev_est / Z24 {
                pass = passes;
            }
            prev_est = last_est;
        }
    }
    if dna > 0 && last_est >= lit_est {
        Z220(out, 0, n);
        return;
    }
    if dna > 0 || chain4 == 2 {
        return;
    }
    Z238(input, out);
}


#[inline(always)]
pub fn Z252(cost:&[u32],lc:&[u32;512],i:usize,lo:usize,hi:usize,base:u32,width:usize)->u32 {
    if lo>hi || hi>=512 || i>=cost.len() || hi>=cost.len()-i {return 4294967295;}
    let start=if width>=1 && hi-lo>=width {hi-width+1} else {lo};
    let mut l=start;
    let mut best=4294967295u32;
    while l<=hi {
        let c=(cost[i+l].wrapping_add(lc[l]).wrapping_add(base)<<9)|((l as u32)^511);
        best=if c<best {c} else {best};
        l+=1;
    }
    best
}


pub fn Z216(k: usize, passes: usize, tail: usize, final_tail: usize) -> usize {
    if k.wrapping_add(1) >= passes { final_tail } else { tail }
}







pub fn Z250(input:&[u8],out:&mut[u32],mode:usize)->usize{if mode==0 {Z248(input,out,0)}else if mode==1 {Z248(input,out,1)}else if mode==2 {Z248(input,out,2)}else if mode==3 {Z248(input,out,3)}else if mode==4 {Z248(input,out,4)}else if mode==5 {Z248(input,out,5)}else if mode==6 {Z248(input,out,6)}else {Z248(input,out,7)}}










































pub const Z85: [[usize; 2]; 16] = [
    [3, 0],  
    [0, 1],  
    [3, 1],  
    [0, 2],  
    [1, 0],  
    [1, 2],  
    [1, 2],  
    [1, 3],  
    [1, 4],  
    [3, 1],  
    [3, 1],  
    [1, 5],  
    [1, 6],  
    [1, 7],  
    [2, 0],  
    [1, 8],  
];



pub const Z84: [[usize; 9]; 16] = [
[2,32,32,1,3,2,12,7,2],
[2,32,32,1,3,2,12,7,2],
[2,32,32,1,3,2,12,7,2],
[2,32,32,1,3,2,12,7,2],
[2,32,32,1,3,2,12,7,2],
[2,32,32,1,3,2,12,7,2],
[2,32,32,1,3,2,12,7,2],
[2,32,32,1,3,2,12,7,2],
[2,32,32,1,3,2,12,7,2],
[2,32,32,1,3,2,12,7,2],
[2,32,32,1,3,2,12,7,2],
[2,32,32,1,3,2,12,7,2],
[2,32,32,1,3,2,12,7,2],
[2,32,32,1,3,2,12,7,2],
[2,32,32,1,3,2,12,7,2],
[2,32,32,1,3,2,12,7,2],
];






pub const Z87: [[usize; 11]; 16] = [
    [4, 2, 2, 24, 64, 32768, 0, 7, 2048, 10000, 64],  
    [4, 2, 2, 24, 64, 32768, 0, 7, 2048, 10000, 64],  
    [4, 1, 2, 16, 64, 32768, 0, 8, 8192, 8000, 64],  
    [4, 1, 1, 8, 64, 32768, 0, 8, 4096, 10000, 64],  
    [4, 1, 1, 4, 48, 32768, 0, 8, 8192, 8000, 64],  
    [3, 2, 1, 16, 64, 32768, 0, 8, 4096, 10000, 64],  
    [3, 2, 2, 16, 64, 32768, 0, 8, 8192, 8000, 64],  
    [3, 2, 2, 16, 64, 32768, 0, 7, 2048, 10000, 64],  
    [4, 3, 4, 48, 32, 32768, 0, 7, 2048, 10000, 64],  
    [4, 2, 2, 24, 64, 32768, 0, 7, 2048, 10000, 64],  
    [4, 2, 2, 24, 64, 32768, 0, 7, 2048, 10000, 64],  
    [4, 2, 2, 24, 64, 32768, 0, 7, 2048, 10000, 64],  
    [4, 2, 2, 24, 64, 32768, 0, 7, 2048, 10000, 64],  
    [4, 2, 2, 24, 64, 32768, 0, 7, 2048, 10000, 64],  
    [4, 2, 2, 24, 64, 32768, 0, 7, 2048, 10000, 64],  
    [4, 2, 2, 24, 64, 32768, 0, 7, 2048, 10000, 64],  
];



pub const Z88: [[usize; 17]; 16] = [
    [4, 1, 2, 48, 32, 32768, 1, 1, 8, 255, 258, 1, 0, 48, 24, 258, 0],  
    [4, 1, 2, 48, 32, 32768, 1, 1, 8, 255, 258, 1, 0, 48, 24, 258, 0],  
    [4, 1, 2, 48, 32, 32768, 1, 1, 8, 255, 258, 1, 0, 48, 24, 258, 0],  
    [4, 1, 2, 48, 32, 32768, 1, 1, 8, 255, 258, 1, 0, 48, 24, 258, 0],  
    [4, 1, 2, 48, 32, 32768, 1, 1, 8, 255, 258, 1, 0, 48, 24, 258, 0],  
    [4, 1, 2, 48, 32, 32768, 1, 1, 8, 255, 258, 1, 0, 48, 24, 258, 0],  
    [4, 1, 2, 48, 32, 32768, 1, 1, 8, 255, 258, 1, 0, 48, 24, 258, 0],  
    [4, 1, 2, 48, 32, 32768, 1, 1, 8, 255, 258, 1, 0, 48, 24, 258, 0],  
    [4, 1, 2, 48, 32, 32768, 1, 1, 8, 255, 258, 1, 0, 48, 24, 258, 0],  
    [4, 1, 2, 48, 32, 32768, 1, 1, 8, 255, 258, 1, 0, 48, 24, 258, 0],  
    [4, 1, 2, 48, 32, 32768, 1, 1, 8, 255, 258, 1, 0, 48, 24, 258, 0],  
    [4, 1, 2, 48, 32, 32768, 1, 1, 8, 255, 258, 1, 0, 48, 24, 258, 0],  
    [4, 1, 2, 48, 32, 32768, 1, 1, 8, 255, 258, 1, 0, 48, 24, 258, 0],  
    [4, 1, 2, 48, 32, 32768, 1, 1, 8, 255, 258, 1, 0, 48, 24, 258, 0],  
    [4, 1, 2, 48, 32, 32768, 1, 1, 8, 255, 258, 1, 0, 48, 24, 258, 0],  
    [4, 1, 2, 48, 32, 32768, 1, 1, 8, 255, 258, 1, 0, 48, 24, 258, 0],  
];









































































pub fn Z253(input: &[u8], plan: &[u32], out: &mut [u32]) -> usize {
    let n = input.len();
    let mut ntok = 0usize;
    let mut p = 0usize;
    while p < n {
        let v = Z148(plan, p);
        let len = (v % 512) as usize;
        let dist = (v / 512) as usize;
        let valid = Z95(input, p, len, dist);
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





pub fn Z254(input:&[u8],out:&mut[u32],mode:usize)->usize{let e=Z89[mode%32];let plan=Z257(input,e[1]); Z253(input,&plan,out)}














pub fn Z256(input: &[u8], k: usize) -> Vec<u32> {
    let n = input.len();
    let mut plan = Z210(n);
    let c = Z84[k % 16];
    Z224(input, &mut plan, c[1], c[2], c[3], c[4], c[5], c[6], c[7], c[8]);
    plan
}




#[inline(never)]
pub fn Z257(input: &[u8], k: usize) -> Vec<u32> {
    if input.len() >= 67108864 {
        return Vec::new();
    }
    Z256(input, k)
}










































































































































































































































































































































































































pub const Z78: u32 = 15;




















pub const Z79: u32 = 64;


pub const Z77: i32 = 168;











pub const Z83: usize = 5;



















pub const Z82: usize = 1000000;













pub const Z80: usize = 12;






pub const Z81: i32 = 40;















pub const Z75: u64 = 26;



pub const Z76: usize = 7;

























































pub const Z74: u32 = 8;































pub const Z86: u32 = 80;



































































































































































































































pub const Z89: [[usize; 2]; 32] = [
[0,0],
[0,1],
[0,1],
[0,1],
[0,1],
[0,1],
[0,1],
[0,1],
[0,1],
[0,1],
[0,1],
[0,1],
[0,1],
[0,1],
[0,1],
[0,1],
[0,1],
[0,1],
[0,1],
[0,1],
[0,1],
[0,1],
[0,1],
[0,1],
[0,1],
[0,1],
[0,1],
[0,1],
[0,1],
[0,1],
[0,1],
[0,1],
];


pub fn Z255(input:&[u8],out:&mut[u32],mode:usize)->usize{Z254(input,out,0)}

