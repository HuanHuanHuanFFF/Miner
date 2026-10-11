
#![allow(dead_code)]
#[path="/home/runner/work/_temp/deflate-native-upstream/validator/measure/src/token.rs"] mod token;
#[path="/home/runner/work/_temp/deflate-native-upstream/validator/measure/src/deflate.rs"] mod codec;
#[path="/home/runner/work/_temp/r25-tiny-encoder-build/deflate-observed.rs"] mod observed;
#[path="/home/runner/work/Miner/Miner/candidates/r22-595-chain-halfhead/parse.rs"] mod parser0;
#[path="/home/runner/work/Miner/Miner/candidates/r25-root-tiny-pc8/parse.rs"] mod parser1;
type Parser=fn(&[u8],&mut[u32])->usize;
fn tokens(s:&[u8],f:Parser)->Vec<u32>{let mut out=vec![0;s.len()];let n=f(s,&mut out);assert!(n<=s.len());out.truncate(n);out}
fn decode(s:&[u8],ts:&[u32])->bool{let mut out=Vec::new();for&t in ts{match token::decode(t){token::Token::Literal(x)=>out.push(x),token::Token::Match{dist,len}=>{if dist as usize>out.len()||out.len()+len as usize>s.len(){return false;}for _ in 0..len{let x=out[out.len()-dist as usize];out.push(x);}},_=>return false}}out==s}
fn main(){let args:Vec<_>=std::env::args().collect();let corpus=std::path::Path::new(&args[1]);let spool=std::path::Path::new(&args[2]);let cases:&[(&str,Parser)]=&[("combo",parser0::parse),("tiny_pc8",parser1::parse)];
for name in ["tiny-config.json.txt","tiny-app.log"]{let s=std::fs::read(corpus.join(name)).unwrap();for&(label,f)in cases{
let ts=tokens(&s,f);assert!(decode(&s,&ts));println!("R25_CONTEXT {} {}",label,name);
let original=codec::encode(&ts,s.len()).unwrap();let measured=observed::encode(&ts,s.len()).unwrap();assert_eq!(original,measured,"encoder identity {} {}",label,name);
let mut raw=Vec::new();for&t in&ts{raw.extend(t.to_le_bytes());}let stem=format!("{}-{}",label,name);
std::fs::write(spool.join(format!("{}.tokens",stem)),raw).unwrap();std::fs::write(spool.join(format!("{}.deflate",stem)),&original).unwrap();std::fs::write(spool.join(format!("{}.observed.deflate",stem)),&measured).unwrap();
println!("R25_RESULT {} {} {} {}",label,name,ts.len(),original.len());}}}
