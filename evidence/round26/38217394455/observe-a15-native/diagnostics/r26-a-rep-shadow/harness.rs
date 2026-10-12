
#![allow(dead_code)]
#[path="/home/runner/work/Miner/Miner/references/round26-public-641/parse.rs"]mod frozen;
#[path="/home/runner/work/_temp/r26-a-rep-shadow-build/observed.rs"]mod observed;
fn tokens(s:&[u8],f:fn(&[u8],&mut[u32])->usize)->Vec<u32>{let mut v=vec![0;s.len()];let n=f(s,&mut v);assert!(n<=s.len());v.truncate(n);v}
fn decode(s:&[u8],ts:&[u32])->bool{let mut out=Vec::with_capacity(s.len());for&t in ts{if t<256{out.push(t as u8)}else{if !(16777216..25165824).contains(&t){return false}let v=t-16777216;let d=(v/256+1)as usize;let l=(v%256+3)as usize;if d>out.len()||out.len()+l>s.len(){return false}for _ in 0..l{let b=out[out.len()-d];out.push(b)}}}out==s}
fn main(){let args:Vec<_>=std::env::args().collect();let mut files:Vec<_>=std::fs::read_dir(&args[1]).unwrap().map(|p|p.unwrap().path()).filter(|p|p.is_file()).collect();files.sort();
 for p in files{let s=std::fs::read(&p).unwrap();let a=tokens(&s,frozen::parse);let b=tokens(&s,observed::parse);assert_eq!(a,b,"{}",p.display());assert!(decode(&s,&b));let counts=observed::a15_take();
 let name=p.file_name().unwrap().to_str().unwrap();let raw:Vec<u8>=b.iter().flat_map(|t|t.to_le_bytes()).collect();std::fs::write(std::path::Path::new(&args[2]).join(format!("{}.tokens",name)),raw).unwrap();
 print!("A15_CORPUS {} {} {}",name,s.len(),b.len());for x in counts{print!(" {}",x)}println!();}}
