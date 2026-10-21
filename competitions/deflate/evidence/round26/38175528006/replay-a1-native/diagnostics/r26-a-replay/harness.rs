
#![allow(dead_code)]
#[path="/home/runner/work/_temp/deflate-native-upstream/validator/measure/src/token.rs"] mod token;
#[path="/home/runner/work/_temp/deflate-native-upstream/validator/measure/src/deflate.rs"] mod codec;
#[path="/home/runner/work/_temp/r26-a-replay-build/observed.rs"] mod observed;
#[path="/home/runner/work/Miner/Miner/candidates/r25-astra-tiny-pc8-proof1/parse.rs"] mod parser;
fn main(){
  let args:Vec<_>=std::env::args().collect();
  let root=std::path::Path::new(&args[1]);let spool=std::path::Path::new(&args[2]);
  let cases:&[(&str,&str,&str,&str,usize)]=&[("combo","tiny-config.json.txt","evidence/round26/route-a/replay/combo-tiny-config.json.txt.tokens","evidence/round26/route-a/replay/tiny-config.json.txt.input",23),
("strong","tiny-config.json.txt","evidence/round26/route-a/replay/strong-tiny-config.json.txt.tokens","evidence/round26/route-a/replay/tiny-config.json.txt.input",23),
("fixed5","tiny-config.json.txt","evidence/round26/route-a/replay/fixed5-tiny-config.json.txt.tokens","evidence/round26/route-a/replay/tiny-config.json.txt.input",23),
("coverage5","tiny-config.json.txt","evidence/round26/route-a/replay/coverage5-tiny-config.json.txt.tokens","evidence/round26/route-a/replay/tiny-config.json.txt.input",23),
("distance12","tiny-config.json.txt","evidence/round26/route-a/replay/distance12-tiny-config.json.txt.tokens","evidence/round26/route-a/replay/tiny-config.json.txt.input",23),
("combo","tiny-app.log","evidence/round26/route-a/replay/combo-tiny-app.log.tokens","evidence/round26/route-a/replay/tiny-app.log.input",22),
("strong","tiny-app.log","evidence/round26/route-a/replay/strong-tiny-app.log.tokens","evidence/round26/route-a/replay/tiny-app.log.input",22),
("fixed5","tiny-app.log","evidence/round26/route-a/replay/fixed5-tiny-app.log.tokens","evidence/round26/route-a/replay/tiny-app.log.input",22),
("coverage5","tiny-app.log","evidence/round26/route-a/replay/coverage5-tiny-app.log.tokens","evidence/round26/route-a/replay/tiny-app.log.input",22),
("distance12","tiny-app.log","evidence/round26/route-a/replay/distance12-tiny-app.log.tokens","evidence/round26/route-a/replay/tiny-app.log.input",22)];
  for &(label,file,tp,ip,route) in cases {
    let data=std::fs::read(root.join(ip)).unwrap();
    let raw=std::fs::read(root.join(tp)).unwrap();
    assert_eq!(raw.len()%4,0);
    let ts:Vec<u32>=raw.chunks_exact(4).map(|v|u32::from_le_bytes(v.try_into().unwrap())).collect();
    let mut decoded=Vec::new();
    for &t in &ts {match token::decode(t){token::Token::Literal(x)=>decoded.push(x),token::Token::Match{dist,len}=>{assert!(dist as usize<=decoded.len());for _ in 0..len{let x=decoded[decoded.len()-dist as usize];decoded.push(x);}},_=>panic!("invalid token")}}
    assert_eq!(decoded,data);
    assert_eq!(parser::route(&data),route);
    if label=="strong" || route!=23 {let mut fresh=vec![0;data.len()];let count=parser::parse(&data,&mut fresh);fresh.truncate(count);assert_eq!(fresh,ts);}
    println!("R25_CONTEXT {} {}",label,file);
    let original=codec::encode(&ts,data.len()).unwrap();let observed=observed::encode(&ts,data.len()).unwrap();
    assert_eq!(original,observed);
    std::fs::write(spool.join(format!("{}-{}.deflate",label,file)),&original).unwrap();
    println!("R26_RESULT {} {} {} {}",label,file,ts.len(),original.len());
  }
}
