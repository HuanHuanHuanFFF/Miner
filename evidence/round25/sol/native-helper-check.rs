#![allow(dead_code)]
mod original {
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
}

mod changed {
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

pub fn pc_f_try(s: &[u8], c: usize, c2: usize, p: usize, l: usize, d: usize, minl: usize, ls: usize) -> (usize, usize) {
    let n = s.len();
    let d2 = p.wrapping_sub(c2);
    if c2 < c && d2.wrapping_sub(1) < 32768 && p + l < n {
        // An equal forward match may cover one more pending literal backwards.
        // The original source must fail that byte; full forward validation follows.
        let forward = s[c2 + l] == s[p + l];
        let backtie = !forward && ls < p && l < 258 && c2 > 0 && d < p
            && s[c2 - 1] == s[p - 1] && s[p - 1 - d] != s[p - 1];
        if forward
            || (backtie && l >= 3 && s[c2 + l - 1] == s[p + l - 1]) {
            let mut cap = n - p;
            if cap > 258 {
                cap = 258;
            }
            let m = pc_common_from(s, c2, p, cap, 0);
            if (m > l || (m == l && backtie)) && m >= minl {
                (m, d2)
            } else {
                (l, d)
            }
        } else {
            (l, d)
        }
    } else {
        (l, d)
    }
}
}

fn valid(s: &[u8], p: usize, result: (usize, usize)) -> bool {
    let (length, distance) = result;
    length >= 3 && length <= 258 && distance > 0 && distance <= 32768
        && distance <= p && p + length <= s.len()
        && s[p - distance..p - distance + length] == s[p..p + length]
}

fn check(s: &[u8], c: usize, c2: usize, p: usize, l: usize, d: usize,
         minl: usize, ls: usize, counts: &mut [usize; 3]) {
    assert!(c <= p && valid(s, p, (l, d)), "generator violated original MatchAt");
    let old = original::pc_f_try(s, c, c2, p, l, d, minl);
    let new = changed::pc_f_try(s, c, c2, p, l, d, minl, ls);
    assert!(valid(s, p, old), "original helper selected invalid source");
    assert!(valid(s, p, new), "changed helper selected invalid source");
    counts[0] += 1;
    if old.0 > l {
        assert_eq!(new, old, "lost original strictly longer acceptance");
        counts[1] += 1;
    }
    if old != new {
        assert_eq!(old, (l, d), "change outside an original rejection");
        assert_eq!(new.0, l, "unexpected non-tie change");
        assert_eq!(new.1, p - c2);
        assert!(ls < p && l < 258 && c2 > 0 && d < p && l >= minl);
        assert_eq!(s[p - 1], s[c2 - 1], "new source cannot cover pending literal");
        assert_ne!(s[p - 1], s[p - 1 - d], "original source already covers it");
        counts[2] += 1;
    }
}

fn disjoint(counts: &mut [usize; 3]) {
    for l in 3..=258usize {
        for minl in [3usize, 4] {
            for prior in 0..4usize {
                for pending in [false, true] {
                    let (c2, c, p) = (16usize, 320usize, 640usize);
                    let mut s = vec![b'!'; 1100];
                    for start in [c2, c, p] {
                        for i in 0..l { s[start + i] = b'A' + (i % 23) as u8; }
                        s[start + l] = if start == p { b'R' } else { b'Q' };
                    }
                    s[p - 1] = b'z';
                    s[c2 - 1] = if prior & 1 == 0 { b'z' } else { b'x' };
                    s[c - 1] = if prior & 2 == 0 { b'y' } else { b'z' };
                    let ls = if pending { p - 1 } else { p };
                    check(&s, c, c2, p, l, p - c, minl, ls, counts);
                }
            }
            // Same source-prefix but a genuinely longer predecessor.
            let (c2, c, p) = (16usize, 320usize, 640usize);
            let mut s = vec![b'!'; 1100];
            for i in 0..258usize {
                s[c2 + i] = b'A' + (i % 23) as u8;
                s[p + i] = b'A' + (i % 23) as u8;
                if i < l { s[c + i] = b'A' + (i % 23) as u8; }
            }
            s[c + l] = b'Q';
            check(&s, c, c2, p, l, p - c, minl, p - 1, counts);
        }
    }
}

fn window_and_end(counts: &mut [usize; 3]) {
    for p in [32767usize, 32768, 32769, 32770, 33000] {
        for c2 in [0usize, 1, 2, p.saturating_sub(32767), p.saturating_sub(32768)] {
            let (c, l) = (p - 100, 4usize);
            let mut s = vec![b'!'; p + 16];
            for start in [c2, c, p] { s[start..start + l].copy_from_slice(b"abcd"); }
            if c2 > 0 { s[c2 - 1] = b'z'; }
            s[p - 1] = b'z'; s[c - 1] = b'y';
            s[c2 + l] = b'Q'; s[p + l] = b'R';
            check(&s, c, c2, p, l, 100, 4, p - 1, counts);
        }
    }
    for l in [3usize, 4, 16, 128, 257, 258] {
        let (c2, c, p) = (16usize, 320usize, 640usize);
        let mut s = vec![b'!'; p + l];
        for start in [c2, c, p] {
            for i in 0..l { s[start + i] = b'A' + (i % 23) as u8; }
        }
        s[p - 1] = b'z'; s[c2 - 1] = b'z'; s[c - 1] = b'y';
        check(&s, c, c2, p, l, p - c, 3, p - 1, counts);
        // Future/self head links must still reject without inspecting that source.
        check(&s, c, p, p, l, p - c, 3, p - 1, counts);
    }
}

fn periodic(counts: &mut [usize; 3]) {
    // Actual old MatchAt positions include overlapping sources and short periods.
    let mut state = 0x5a17_2026_1011u64;
    for case in 0..20000usize {
        state = state.wrapping_mul(6364136223846793005).wrapping_add(1);
        let period = 1 + (state as usize % 23);
        let mut s = vec![b'!'; 1200];
        for i in 0..s.len() { s[i] = b'A' + (i % period) as u8; }
        let p = 400 + case % 400;
        let d = period * (1 + case % 8);
        let c = p - d;
        let c2 = c.saturating_sub(period * (1 + (case / 8) % 8));
        let l = 3 + (case * 17) % 256;
        let ls = if case & 1 == 0 { p - 1 } else { p };
        check(&s, c, c2, p, l, d, if case & 2 == 0 { 3 } else { 4 }, ls, counts);
    }
}

fn main() {
    let mut counts = [0usize; 3];
    disjoint(&mut counts);
    window_and_end(&mut counts);
    periodic(&mut counts);
    assert!(counts[1] > 0 && counts[2] > 0, "both old and new branches must execute");
    println!("{{\"status\":\"PASS_ACTUAL_RUST_HELPER_BOUNDED\",\"cases\":{},\"strictly_longer_acceptances_preserved\":{},\"new_backward_ties\":{},\"scope\":\"Extracted exact helper only; not whole parse, Lean gate, corpus coverage or performance\"}}",
             counts[0], counts[1], counts[2]);
}
