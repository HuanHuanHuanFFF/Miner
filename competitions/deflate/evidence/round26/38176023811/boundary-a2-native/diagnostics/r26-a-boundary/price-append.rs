
// R25 read-only block prices; original encode/write_block bytes above retained.
const LP_TOKENS: usize = 0;
const LP_LITERAL_TOKENS: usize = 1;
const LP_MATCH_TOKENS: usize = 2;
const LP_MATCH_BYTES: usize = 3;
const LP_LEN3_MATCHES: usize = 4;
const LP_KNOWN_LITERAL_PRICES: usize = 5;
const LP_MISSING_LITERAL_PRICES: usize = 6;
const LP_MATCH_CHEAPER: usize = 7;
const LP_LITERAL_CHEAPER: usize = 8;
const LP_EQUAL_PRICE: usize = 9;
const LP_MATCH_SAVINGS_BITS: usize = 10;
const LP_MATCH_LOSS_BITS: usize = 11;
const LP_KNOWN_MATCH_BITS: usize = 12;
const LP_KNOWN_LITERAL_BITS: usize = 13;
const LP_STORED_BLOCKS: usize = 14;
const LP_FIXED_BLOCKS: usize = 15;
const LP_DYNAMIC_BLOCKS: usize = 16;
const LP_WIDTH: usize = 257;
const LP_CODE_BASE: usize = 17;
const LP_CODE_WIDTH: usize = 8;

fn r25_lp_tables(b: &Block) -> (Vec<u8>, Vec<u8>, usize, u64, u64, u64) {
    // Dynamic tables.
    let mut lf = b.litlen_freq;
    lf[END_OF_BLOCK] += 1;
    let mut ll = package_merge(&lf, MAX_BITS_LITLEN);
    let mut dl = package_merge(&b.dist_freq, MAX_BITS_LITLEN);
    // A block with no matches still has to name at least one distance code.
    if dl.iter().all(|&x| x == 0) {
        dl[0] = 1;
    }

    let hlit = {
        let mut n = NUM_LITLEN;
        while n > 257 && ll[n - 1] == 0 {
            n -= 1;
        }
        n
    };
    let hdist = {
        let mut n = NUM_DIST;
        while n > 1 && dl[n - 1] == 0 {
            n -= 1;
        }
        n
    };
    ll.truncate(hlit.max(257));
    ll.resize(NUM_LITLEN, 0);
    let mut all: Vec<u8> = Vec::with_capacity(hlit + hdist);
    all.extend_from_slice(&ll[..hlit]);
    all.extend_from_slice(&dl[..hdist]);
    let rle = rle_lengths(&all);
    let mut clf = [0u32; NUM_CODELEN];
    for &(sym, _, _) in &rle {
        clf[sym as usize] += 1;
    }
    let cl = package_merge(&clf, MAX_BITS_CODELEN);

    let dyn_bits = b.dynamic_cost(&ll, &dl, &cl, &rle);
    let fix_bits = b.fixed_cost();
    let stored_bits = 3 + 32 + 8 * b.raw_len as u64;


    let stored = stored_bits < dyn_bits.min(fix_bits) && b.raw_len < 65536 &&
        b.items.iter().all(|&(_, _, _, d, _, _)| d == u16::MAX);
    if stored { return (ll, dl, 0, fix_bits, dyn_bits, stored_bits); }
    if fix_bits <= dyn_bits {
        let (fll, fdl) = fixed_tables();
        (fll.to_vec(), fdl.to_vec(), 1, fix_bits, dyn_bits, stored_bits)
    } else { (ll, dl, 2, fix_bits, dyn_bits, stored_bits) }
}

pub fn r25_lp_prices(ts: &[u32], input: &[u8]) -> Vec<([u64; LP_WIDTH], usize, usize, usize, u64, u64, u64)> {
    let mut result = Vec::new();
    let mut pos = 0usize;
    for chunk in ts.chunks(BLOCK_TOKENS) {
        let mut b = Block::new();
        for &t in chunk {
            match token::decode(t) {
                token::Token::Literal(x) => b.push_literal(x),
                token::Token::Match { dist, len } => b.push_match(dist, len),
                _ => panic!("invalid frozen token"),
            }
        }
        let (ll, dl, kind, fix_bits, dyn_bits, stored_bits) = r25_lp_tables(&b);
        let from = pos;
        let mut counts = [0u64; LP_WIDTH];
        counts[LP_TOKENS] = chunk.len() as u64;
        counts[match kind { 0 => LP_STORED_BLOCKS, 1 => LP_FIXED_BLOCKS, 2 => LP_DYNAMIC_BLOCKS, _ => panic!("block type") }] = 1;
        for &t in chunk {
            match token::decode(t) {
                token::Token::Literal(_) => { counts[LP_LITERAL_TOKENS] += 1; pos += 1; },
                token::Token::Match { dist, len } => {
                    counts[LP_MATCH_TOKENS] += 1;
                    counts[LP_MATCH_BYTES] += len as u64;
                    assert!(dist >= 1 && dist as usize <= pos && pos + len as usize <= input.len());
                    if len == 3 {
                        assert_ne!(kind, 0, "a stored block cannot contain a match");
                        let (dc, extra, _) = dist_code(dist);
                        assert!(dc < 30 && ll[257] > 0 && dl[dc] > 0);
                        let cell = LP_CODE_BASE + dc * LP_CODE_WIDTH;
                        counts[LP_LEN3_MATCHES] += 1; counts[cell] += 1;
                        let known = input[pos..pos + 3].iter().all(|&x| ll[x as usize] > 0);
                        if known {
                            let mc = ll[257] as u64 + dl[dc] as u64 + extra as u64;
                            let lc = input[pos..pos + 3].iter().map(|&x| ll[x as usize] as u64).sum::<u64>();
                            counts[LP_KNOWN_LITERAL_PRICES] += 1; counts[cell + 1] += 1;
                            counts[LP_KNOWN_MATCH_BITS] += mc; counts[LP_KNOWN_LITERAL_BITS] += lc;
                            if mc < lc {
                                counts[LP_MATCH_CHEAPER] += 1; counts[cell + 3] += 1;
                                counts[LP_MATCH_SAVINGS_BITS] += lc - mc; counts[cell + 6] += lc - mc;
                            } else if mc > lc {
                                counts[LP_LITERAL_CHEAPER] += 1; counts[cell + 4] += 1;
                                counts[LP_MATCH_LOSS_BITS] += mc - lc; counts[cell + 7] += mc - lc;
                            } else { counts[LP_EQUAL_PRICE] += 1; counts[cell + 5] += 1; }
                        } else {
                            counts[LP_MISSING_LITERAL_PRICES] += 1; counts[cell + 2] += 1;
                        }
                    }
                    pos += len as usize;
                },
                _ => panic!("invalid frozen token"),
            }
        }
        assert_eq!(pos - from, b.raw_len);
        result.push((counts, from, pos, kind, fix_bits, dyn_bits, stored_bits));
    }
    assert_eq!(pos, input.len());
    result
}

pub fn r26_length_prices(ts:&[u32])->Vec<Vec<u32>> {
 let mut result=Vec::new();
 for chunk in ts.chunks(BLOCK_TOKENS) {
  let mut b=Block::new();
  for &t in chunk {match token::decode(t){token::Token::Literal(x)=>b.push_literal(x),token::Token::Match{dist,len}=>b.push_match(dist,len),_=>panic!("bad token")}}
  let (ll,_,kind,_,_,_)=r25_lp_tables(&b);
  let mut prices=vec![u32::MAX;259];
  if kind!=0 {for length in 3..=258 {let (lc,extra,_)=len_code(length as u32);if lc<ll.len()&&ll[lc]>0 {prices[length]=ll[lc] as u32+extra as u32;}}}
  result.push(prices);
 }
 result
}
