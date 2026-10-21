
#![allow(dead_code)]
#[path="/home/runner/work/Miner/Miner/candidates/r26-a-658-window-filter/parse.rs"]mod frozen;
#[path="/home/runner/work/_temp/r26-a-window-build/observed.rs"]mod observed;
#[path="/home/runner/work/Miner/Miner/references/round26-public-658/parse.rs"]mod parent;
fn tokens(s:&[u8],f:fn(&[u8],&mut[u32])->usize)->Vec<u32>{let mut v=vec![0;s.len()];let n=f(s,&mut v);assert!(n<=s.len());v.truncate(n);v}
fn decode(s:&[u8],ts:&[u32])->bool{let mut out=Vec::with_capacity(s.len());for&t in ts{if t<256{out.push(t as u8)}else{if !(16777216..25165824).contains(&t){return false}let v=t-16777216;let d=(v/256+1)as usize;let l=(v%256+3)as usize;if d>out.len()||out.len()+l>s.len(){return false}for _ in 0..l{let b=out[out.len()-d];out.push(b)}}}out==s}
fn common(s:&[u8],a:usize,b:usize)->usize{let mut k=0;while k<258&&a+k<s.len()&&b+k<s.len()&&s[a+k]==s[b+k]{k+=1;}k}
fn helpers(){let mut cases=0usize;
 for n in [0,1,7,8,9,16,17,31,64,300]{for period in [1,3,7,17]{let s:Vec<u8>=(0..n).map(|i|(i%period)as u8).collect();
 for p in [0,n/2,n,n+1]{for best in [0,1,2,3,4,5,6,7,8,9,15,31,257,258]{let b8=frozen::a18_word(&s,p);let f=frozen::a18_filter(&s,p,b8,best);
 let active=n>=8&&p<=n-8&&best<n-p;assert_eq!(f.2!=0,active);
 if p<=n{for c in [0,p.saturating_sub(1),p.saturating_sub(8)]{if common(&s,c,p)>best{assert!(frozen::a18_pass(&s,c,f));}cases+=1;}}
 }}}}
 // Critical non-full8 short case: best+1 bytes agree, the immediately following byte differs.
 for best in 0..7{let mut s=vec![0u8;512];for i in 0..8{s[i]=(i+11)as u8;s[256+i]=(i+11)as u8;}s[256+best+1]^=1;
 let f=frozen::a18_filter(&s,256,frozen::a18_word(&s,256),best);assert_eq!(common(&s,0,256),best+1);assert!(frozen::a18_pass(&s,0,f));cases+=1;}
 let prev:[u32;32768]=std::array::from_fn(|i|i.saturating_sub(7)as u32);
 for period in [1,3,7,17]{let s:Vec<u8>=(0..300).map(|i|(i%period)as u8).collect();for p in [16,31,64,257,290]{let cap=std::cmp::min(258,s.len()-p);for have in [0,3,7,cap]{if have>cap{continue;}for dep in [1,6,12]{for gm in [0,1]{
 let a=parent::u118_walk(&s,&prev,p,p-9,cap,have,dep,128,gm,64);let b=frozen::u118_walk(&s,&prev,p,p-9,cap,have,dep,128,gm,64);assert_eq!(a,b);cases+=1;
 }}}}}
 println!("A18_HELPERS {}",cases);}
fn main(){helpers();let args:Vec<_>=std::env::args().collect();let mut files:Vec<_>=std::fs::read_dir(&args[1]).unwrap().map(|p|p.unwrap().path()).filter(|p|p.is_file()).collect();files.sort();
 for p in files{let s=std::fs::read(&p).unwrap();let a=tokens(&s,frozen::parse);let b=tokens(&s,observed::parse);let c=tokens(&s,parent::parse);assert_eq!(a,b,"observer {}",p.display());assert_eq!(a,c,"parent {}",p.display());assert!(decode(&s,&b));let counts=observed::a18_take();
 let name=p.file_name().unwrap().to_str().unwrap();let raw:Vec<u8>=b.iter().flat_map(|t|t.to_le_bytes()).collect();std::fs::write(std::path::Path::new(&args[2]).join(format!("{}.tokens",name)),raw).unwrap();
 print!("A18_CORPUS {} {} {}",name,s.len(),b.len());for x in counts{print!(" {}",x)}println!();}}
