
#![allow(dead_code)]
#[path="/home/runner/work/Miner/Miner/references/round26-public-658/parse.rs"]mod parent;
#[path="/home/runner/work/_temp/r26-a-common-lowering-build/safe_wrapping_words/parse.rs"]mod changed;
fn tokens(s:&[u8],f:fn(&[u8],&mut[u32])->usize)->Vec<u32>{let mut v=vec![0;s.len()];let n=f(s,&mut v);assert!(n<=s.len());v.truncate(n);v}
fn decode(s:&[u8],ts:&[u32])->bool{let mut out=Vec::with_capacity(s.len());for&t in ts{if t<256{out.push(t as u8)}else{if !(16777216..25165824).contains(&t){return false}let v=t-16777216;let d=(v/256+1)as usize;let l=(v%256+3)as usize;if d>out.len()||out.len()+l>s.len(){return false}for _ in 0..l{let b=out[out.len()-d];out.push(b)}}}out==s}
fn main(){let mut cases=0;for n in [0,1,7,8,9,16,17,257,258,259,512]{for period in [1,3,7,17]{let s:Vec<u8>=(0..n).map(|i|(i%period)as u8).collect();for b in [0,n/2,n]{for a in [0,b/2,b]{for cap in [0,1,7,8,9,15,16,31,257,258]{if b+cap<=n{let x=parent::u118_common(&s,a,b,cap);let y=changed::u118_common(&s,a,b,cap);assert_eq!(x,y);cases+=1;}}}}}}println!("A19_HELPERS {}",cases);
 let args:Vec<_>=std::env::args().collect();let mut files:Vec<_>=std::fs::read_dir(&args[1]).unwrap().map(|p|p.unwrap().path()).filter(|p|p.is_file()).collect();files.sort();
 for p in files{let s=std::fs::read(&p).unwrap();let a=tokens(&s,parent::parse);let b=tokens(&s,changed::parse);assert_eq!(a,b,"{}",p.display());assert!(decode(&s,&b));let name=p.file_name().unwrap().to_str().unwrap();let raw:Vec<u8>=b.iter().flat_map(|t|t.to_le_bytes()).collect();std::fs::write(std::path::Path::new(&args[2]).join(format!("{}.tokens",name)),raw).unwrap();println!("A19_CORPUS {} {} {}",name,s.len(),b.len());}}
