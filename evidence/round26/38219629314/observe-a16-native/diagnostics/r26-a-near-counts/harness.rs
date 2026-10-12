
#![allow(dead_code)]
#[path="/home/runner/work/Miner/Miner/candidates/r26-a-641-near-retain/parse.rs"]mod frozen;
#[path="/home/runner/work/_temp/r26-a-near-counts-build/observed.rs"]mod observed;
fn tokens(s:&[u8],f:fn(&[u8],&mut[u32])->usize)->Vec<u32>{let mut v=vec![0;s.len()];let n=f(s,&mut v);assert!(n<=s.len());v.truncate(n);v}
fn helpers(){for n in [100000,500000]{for gap in [0,1,2,3,8,9,32768]{
 let mut head=[0u32;32768];let mut prev=[77u32;32768];let p=32769usize;let old=(p-gap)as u32;head[0]=old;head[1]=1;
 frozen::a16_link(&mut head,&mut prev,0,p,n);let skip=n!=500000&&gap>=2&&gap<=8;
 assert_eq!(head[0],if skip{old}else{p as u32});assert_eq!(head[1],1);assert_eq!(prev[p%32768],if skip{77}else{old});}}
 println!("A16_HELPERS 14");}
fn main(){helpers();let args:Vec<_>=std::env::args().collect();let mut files:Vec<_>=std::fs::read_dir(&args[1]).unwrap().map(|p|p.unwrap().path()).filter(|p|p.is_file()).collect();files.sort();
 for p in files{let s=std::fs::read(&p).unwrap();let a=tokens(&s,frozen::parse);let b=tokens(&s,observed::parse);assert_eq!(a,b,"{}",p.display());let counts=observed::a16_take();
 let name=p.file_name().unwrap().to_str().unwrap();let raw:Vec<u8>=b.iter().flat_map(|t|t.to_le_bytes()).collect();std::fs::write(std::path::Path::new(&args[2]).join(format!("{}.tokens",name)),raw).unwrap();
 print!("A16_CORPUS {} {} {}",name,s.len(),b.len());for x in counts{print!(" {}",x)}println!();}}
