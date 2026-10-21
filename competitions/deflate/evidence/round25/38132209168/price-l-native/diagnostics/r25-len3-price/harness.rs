
#![allow(dead_code)]
#[path="/home/runner/work/_temp/deflate-native-upstream/validator/measure/src/token.rs"] mod token;
#[path="/home/runner/work/_temp/deflate-native-upstream/validator/measure/src/deflate.rs"] mod trusted;
#[path="/home/runner/work/_temp/r25-len3-price-build/prices.rs"] mod prices;
#[path="/home/runner/work/Miner/Miner/candidates/r22-595-chain-halfhead/parse.rs"] mod frozen0;
#[path="/home/runner/work/_temp/r25-len3-price-build/observed0.rs"] mod observed0;
#[path="/home/runner/work/Miner/Miner/references/round25-public-578/parse.rs"] mod frozen1;
#[path="/home/runner/work/_temp/r25-len3-price-build/observed1.rs"] mod observed1;
#[path="/home/runner/work/Miner/Miner/references/round18-public-584/parse.rs"] mod frozen2;
#[path="/home/runner/work/_temp/r25-len3-price-build/observed2.rs"] mod observed2;
type Parser = fn(&[u8], &mut [u32]) -> usize;
type Routes = fn() -> [u64; 33];
fn parse(s: &[u8], f: Parser) -> Vec<u32> {
    let mut out = vec![0u32; s.len()]; let n = f(s, &mut out);
    assert!(n <= s.len()); out.truncate(n); out
}
fn decode(s: &[u8], ts: &[u32]) {
    let mut out = Vec::new();
    for &t in ts {
        match token::decode(t) {
            token::Token::Literal(x) => out.push(x),
            token::Token::Match { dist, len } => {
                assert!(dist >= 1 && dist as usize <= out.len() && out.len() + len as usize <= s.len());
                for _ in 0..len { let x = out[out.len() - dist as usize]; out.push(x); }
            },
            _ => panic!("invalid token"),
        }
    }
    assert_eq!(out, s);
}
fn main() {
    let args: Vec<_> = std::env::args().collect();
    let spool = std::path::Path::new(&args[2]);
    let cases: &[(&str, Parser, Parser, Routes)] = &[("combo", frozen0::parse, observed0::parse, observed0::r25_lp_take),
("public578", frozen1::parse, observed1::parse, observed1::r25_lp_take),
("public584", frozen2::parse, observed2::parse, observed2::r25_lp_take)];
    let mut files: Vec<_> = std::fs::read_dir(&args[1]).unwrap().map(|x| x.unwrap().path()).filter(|p| p.is_file()).collect();
    files.sort();
    for (i, p) in files.iter().enumerate() {
        let s = std::fs::read(p).unwrap(); let name = p.file_name().unwrap().to_str().unwrap();
        for &(label, frozen, observed, routes) in cases {
            let a = parse(&s, frozen); let b = parse(&s, observed);
            assert_eq!(a, b, "observed parser differs: {} {}", label, name); decode(&s, &a);
            let hits = routes(); assert!(hits.iter().sum::<u64>() <= 1, "multiple top-level rows");
            let route = hits.iter().position(|&v| v > 0).unwrap_or(32);
            let enc = trusted::encode(&a, s.len()).unwrap();
            assert_eq!(enc, prices::encode(&a, s.len()).unwrap(), "instrumented encoder differs");
            let mut raw = Vec::new(); for &t in &a { raw.extend(t.to_le_bytes()); }
            std::fs::write(spool.join(format!("{}-{}.tokens", i, label)), raw).unwrap();
            std::fs::write(spool.join(format!("{}-{}.deflate", i, label)), &enc).unwrap();
            println!("R25_LP_FILE {} {} {} {} {} {}", label, i, name, enc.len(), a.len(), route);
            for (bi, (counts, from, to, kind, fix, dyn_, stored)) in prices::r25_lp_prices(&a, &s).iter().enumerate() {
                print!("R25_LP_BLOCK {} {} {} {} {} {} {} {} {} {}", label, i, name, bi, from, to, kind, fix, dyn_, stored);
                for v in counts { print!(" {}", v); } println!();
            }
        }
    }
}
