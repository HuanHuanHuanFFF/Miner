// Prepared only: UNCOMPILED / UNRUN. This is an extra confirmation fixture,
// not a replacement for the frozen native-helper-check.rs or a proof.
// A runner should copy the exact parent to frozen.rs and exact groups source to
// candidate.rs beside this file, then compile with overflow checks enabled.
#![allow(dead_code, unused_variables)]
#[path = "frozen.rs"] mod base;
#[path = "candidate.rs"] mod new;

fn make_tables(mode: usize) -> Vec<u32> {
    let mut tabs = vec![0u32; base::D_TS];
    for i in 0..256 {
        tabs[i] = match mode {
            1 => 4095, // All mask bits plus the complete 12-bit maximum.
            2 => if i == 7 { 0 } else { 1 }, // An unused zero disables metadata.
            3 => 4096, // Positive, but outside the packed maximum's domain.
            5 => if i == 1 { 3 } else { 1 }, // Honest max prevents cost wrap.
            _ => 1,
        };
    }
    for l in 0..264 {
        tabs[256 + l] = if mode == 4 { l as u32 } else { 2 };
    }
    tabs
}

fn check_case(
    label: &str,
    hi: usize,
    stop: usize,
    endpoint: usize,
    mode: usize,
    endpoint_cost: u64,
    next_cost: u64,
    expected_group: Option<(usize, usize, usize, usize)>,
) {
    let tabs = make_tables(mode);
    let mut lit_old = [0u32; 256];
    let mut lit_new = [0u32; 256];
    let mut lc_old = [0u32; 512];
    let mut lc_new = [0u32; 512];
    let mut dc_old = [0u32; 32];
    let mut dc_new = [0u32; 32];
    base::d_load(&tabs, 0, &mut lit_old, &mut lc_old, &mut dc_old);
    new::d_load_groups(&tabs, 0, &mut lit_new, &mut lc_new, &mut dc_new);
    assert_eq!(lit_old, lit_new, "literal prices: {label}");
    assert_eq!(&lc_old[..511], &lc_new[..511], "length prices: {label}");
    assert_eq!(dc_old, dc_new, "distance prices: {label}");
    let metadata = lc_new[511];
    if mode == 2 || mode == 3 || mode == 4 {
        assert_eq!(metadata, 0, "disabled metadata: {label}");
    } else {
        assert_ne!(metadata & (1u32 << 31), 0, "last group bit: {label}");
        if mode == 1 {
            assert_eq!(metadata, u32::MAX, "full mask/max encoding: {label}");
        }
    }

    let mut input = vec![0u8; endpoint + 8];
    if mode == 5 {
        // Seed uses price1; its next position uses price3, which would wrap.
        input[hi - 2] = 1;
    }
    let mut ring_old = [0u64; base::D_RING];
    for i in 0..base::D_RING {
        ring_old[i] = ((1000 + i as u64) << 32) | (i as u64 * 17);
    }
    ring_old[endpoint % base::D_RING] = endpoint_cost << 32;
    let mut ring_new = ring_old;
    let mut out_old = vec![0xDEAD_BEEFu32; input.len()];
    let mut out_new = out_old.clone();
    let kcd = 0u64;
    let chd = 512u64;
    let dlit = base::D_LIT;
    let nxt0 = next_cost << 32;
    // lo above hi makes the pending-push segment empty. endpoint-hi>=18
    // makes the initial fewer-than-three-bytes segment empty as well.
    let lo = input.len();
    assert!(lo > hi && endpoint >= hi + 18);

    if let Some((group, group_end, count, lower)) = expected_group {
        let seed_q = hi - 1;
        let rem = endpoint - seed_q;
        assert_eq!(new::d_gap_group(rem), (group, group_end), "group: {label}");
        assert_ne!(metadata & (1u32 << (12 + group)), 0, "enabled group: {label}");
        assert_eq!(count, (seed_q - stop).min(group_end - 1 - rem));
        assert_eq!(lower, seed_q - count);
        assert_eq!(lower, stop, "fixture ends exactly after the bulk: {label}");
        let high = endpoint_cost + lc_old[rem] as u64;
        assert!(high + ((metadata & 4095) as u64) < (1u64 << 32));
        assert!(high < next_cost + lit_old[input[seed_q] as usize] as u64);
    }

    let old_nxt = base::d_gap(
        &input, &lit_old, &lc_old, &mut ring_old, &mut out_old,
        hi, stop, endpoint, kcd, chd, lo, nxt0, dlit,
    );
    let new_nxt = new::d_gap_groups(
        &input, &lit_new, &lc_new, &mut ring_new, &mut out_new,
        hi, stop, endpoint, kcd, chd, lo, nxt0, dlit,
    );
    assert_eq!(old_nxt, new_nxt, "nxt: {label}");
    assert_eq!(ring_old, ring_new, "entire ring: {label}");
    assert_eq!(out_old, out_new, "entire output: {label}");
    assert_eq!(new_nxt, ring_new[stop % base::D_RING], "restored lower cell: {label}");
    if mode == 0 || mode == 1 {
        for p in stop..hi {
            let expected = ((endpoint_cost + 2) << 32) | (chd + (endpoint - p) as u64);
            assert_eq!(ring_new[p % base::D_RING], expected, "expected cell {p}: {label}");
            assert_eq!(out_new[p], expected as u32, "expected choice {p}: {label}");
        }
    }
}

fn main() {
    // Group4 [19,23): seed1026, then bulk[1023,1026), ring1023 + ring0/1.
    check_case("cross1024-small", 1027, 1023, 1045, 0, 10, 13, Some((4, 23, 3, 1023)));
    // Same first bulk, then continue to stop1020; final choice is537, not534.
    check_case("cross1024-continue-to-stop", 1027, 1020, 1045, 0, 10, 13, None);
    // Same lengths/costs, translated away from the ring seam.
    check_case("no-cross-small", 515, 511, 533, 0, 10, 13, Some((4, 23, 3, 511)));
    // Group19 [227,258), which is metadata bit31; packed metadata=u32::MAX.
    // seed1040, bulk[1010,1040), splitting at1024 into14+16 positions.
    check_case("cross1024-highbit", 1041, 1010, 1267, 1, 10, 13, Some((19, 258, 30, 1010)));
    check_case("no-cross-highbit", 529, 498, 755, 1, 10, 13, Some((19, 258, 30, 498)));
    check_case("disabled-zero-literal", 1027, 1023, 1045, 2, 10, 13, None);
    check_case("disabled-max4096", 1027, 1023, 1045, 3, 10, 13, None);
    check_case("disabled-nonflat", 1027, 1023, 1045, 4, 10, 1000, None);
    check_case("honest-cost-wrap-fallback", 1027, 1023, 1045, 5, 0xFFFF_FFFC, 0xFFFF_FFFE, None);
    println!("R11_GAP_GROUPS_CROSS_RING {{\"cases\":9,\"explicit_cross_ring_bulk\":3,\"noncross_controls\":2,\"disabled_cases\":3,\"honest_wrap_fallback\":1,\"whole_ring_out_nxt_equal\":true}}");
}
