
#![allow(dead_code)]
#[path="/home/runner/work/_temp/deflate-native-upstream/validator/measure/src/token.rs"] mod token;
#[path="/home/runner/work/_temp/deflate-native-upstream/validator/measure/src/deflate.rs"] mod codec;
#[path="/home/runner/work/Miner/Miner/candidates/r22-595-chain-halfhead/parse.rs"] mod frozen0;
#[path="/home/runner/work/_temp/r25-heldout-quality-build/observed0.rs"] mod observed0;
#[path="/home/runner/work/Miner/Miner/candidates/r25-astra-end4/parse.rs"] mod frozen1;
#[path="/home/runner/work/_temp/r25-heldout-quality-build/observed1.rs"] mod observed1;
#[path="/home/runner/work/Miner/Miner/candidates/r25-astra-tiny-pc8-proof1/parse.rs"] mod frozen2;
#[path="/home/runner/work/_temp/r25-heldout-quality-build/observed2.rs"] mod observed2;
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
            _ => panic!("invalid original token"),
        }
    }
    assert_eq!(out, s);
}
fn main() {
    let args: Vec<_> = std::env::args().collect(); let spool = std::path::Path::new(&args[2]);
    let cases: &[(&str, Parser, Parser, Routes)] = &[("combo", frozen0::parse, observed0::parse, observed0::r25_hq_take),
("end4", frozen1::parse, observed1::parse, observed1::r25_hq_take),
("tiny-pc8", frozen2::parse, observed2::parse, observed2::r25_hq_take)];
    let mut files: Vec<_> = std::fs::read_dir(&args[1]).unwrap().map(|x| x.unwrap().path()).filter(|p| p.is_file()).collect();
    files.sort(); assert_eq!(files.len(), 27);
    for (i, p) in files.iter().enumerate() {
        let s = std::fs::read(p).unwrap(); assert!(std::str::from_utf8(&s).is_ok());
        let name = p.file_name().unwrap().to_str().unwrap();
        for &(label, frozen, observed, routes) in cases {
            let a = parse(&s, frozen); let b = parse(&s, observed);
            assert_eq!(a, b, "route observer token mismatch {} {}", label, name); decode(&s, &a);
            let hits = routes(); assert_eq!(hits.iter().sum::<u64>(), 1, "top-level route count");
            let route = hits.iter().position(|&v| v == 1).unwrap();
            let enc = codec::encode(&a, s.len()).unwrap(); let mut raw = Vec::new();
            for &t in &a { raw.extend(t.to_le_bytes()); }
            std::fs::write(spool.join(format!("{}-{}.tokens", i, label)), raw).unwrap();
            std::fs::write(spool.join(format!("{}-{}.deflate", i, label)), &enc).unwrap();
            println!("R25_HQ {} {} {} {} {} {}", label, i, name, enc.len(), a.len(), route);
        }
    }
}
