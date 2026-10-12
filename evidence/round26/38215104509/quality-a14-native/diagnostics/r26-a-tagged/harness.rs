
#![allow(dead_code)]
#[path="/home/runner/work/Miner/Miner/candidates/r26-a-641-tagged-head/parse.rs"]mod frozen;
#[path="/home/runner/work/_temp/r26-a-tagged-build/observed.rs"]mod observed;
#[path="/home/runner/work/Miner/Miner/references/round26-public-641/parse.rs"]mod parent;
fn tokens(s:&[u8],f:fn(&[u8],&mut[u32])->usize)->Vec<u32>{let mut v=vec![0;s.len()];let n=f(s,&mut v);assert!(n<=s.len());v.truncate(n);v}
fn decode(s:&[u8],ts:&[u32])->bool{let mut out=Vec::with_capacity(s.len());for&t in ts{if t<256{out.push(t as u8)}else{if !(16777216..25165824).contains(&t){return false}let v=t-16777216;let d=(v/256+1)as usize;let l=(v%256+3)as usize;if d>out.len()||out.len()+l>s.len(){return false}for _ in 0..l{let b=out[out.len()-d];out.push(b)}}}out==s}
fn direct<const H:usize>(s:&[u8],km:u32){let mut a=vec![0;s.len()];let mut b=vec![0;s.len()];let mut c=vec![0;s.len()];
 let na=parent::pc_run1c::<H>(s,&mut a,4,258,1000000,km,2,if km==0xFFFF_FFFF{4}else{3});
 let nb=frozen::at_run1c::<H>(s,&mut b,4,258,1000000,km,2,if km==0xFFFF_FFFF{4}else{3});
 let nc=observed::at_run1c::<H>(s,&mut c,4,258,1000000,km,2,if km==0xFFFF_FFFF{4}else{3});
 a.truncate(na);b.truncate(nb);c.truncate(nc);assert_eq!(a,b,"parent/direct H{} n{} km{}",H,s.len(),km);assert_eq!(b,c);assert!(decode(s,&a));
 let counts=observed::a14_take();let fallback=s.len()>=0x0100_0000||H<32768||H==65536||H==131072||H==262144;
 assert_eq!(counts[0],1);assert_eq!(counts[1],fallback as u64);println!("A14_DIRECT {} {} {} {}",H,s.len(),km,counts[1]);}
fn helpers(){let s:Vec<u8>=(0..128).map(|i|(i%7)as u8).collect();
 for km in [0xFFFF_FFFF,0xFFFF_FF00]{let mut head=[0u32;32768];let mut prev=[0u32;32768];
 for p in [0,1,15]{let a=frozen::at_ahead(&s,&head,p,km);assert_eq!(a.0&32767,parent::pc_slot_of_m::<32768>(&s,p,km));assert_eq!(a.1,0);assert_eq!(a.2,parent::pc_be8(&s,0));}
 let k=frozen::at_key(&s,0,km);frozen::at_link(&mut head,&mut prev,k,0);assert_eq!(prev[0],0);
 let a=frozen::at_ahead(&s,&head,7,km);assert_eq!(a.1,0);assert_eq!(a.2,parent::pc_be8(&s,0));
 // Synthetic high positions test exact packing/link projection only; no out-of-range byte read.
 for p in [0x00FF_FFFE,0x00FF_FFFF]{let old=head[k&32767];frozen::at_link(&mut head,&mut prev,k,p);
 assert_eq!(head[k&32767]&0x00FF_FFFF,p as u32);assert_eq!(head[k&32767]>>24,((k>>15)&255)as u32);assert_eq!(prev[p%32768],old&0x00FF_FFFF);}
 }
 let mut s3=vec![0u8;64];s3[0..4].copy_from_slice(&[11,22,33,44]);s3[16..20].copy_from_slice(&[11,22,33,99]);
 assert_eq!(frozen::at_key(&s3,0,0xFFFF_FF00),frozen::at_key(&s3,16,0xFFFF_FF00));
 println!("A14_HELPERS source0_km3_maxpos PASS");}
fn main(){helpers();for n in 0..65{let s:Vec<u8>=(0..n).map(|i|(i%7)as u8).collect();for km in [0xFFFF_FFFF,0xFFFF_FF00]{direct::<32768>(&s,km);}}
 for period in [1,2,7,17,251]{for n in [257,1024,32784]{let s:Vec<u8>=(0..n).map(|i|(i%period)as u8).collect();for km in [0xFFFF_FFFF,0xFFFF_FF00]{direct::<32781>(&s,km);}}}
 let mut x=7u32;let mut s=Vec::new();for _ in 0..66000{x=x.wrapping_mul(1664525).wrapping_add(1013904223);s.push((x>>24)as u8);}for i in 0..258{s[33040+i]=s[272+i];}
 for km in [0xFFFF_FFFF,0xFFFF_FF00]{direct::<131100>(&s,km);direct::<65536>(&s,km);direct::<16384>(&s,km);}
 // Exercise actual original-kernel fallback and just-below-boundary tagged execution.
 for n in [0x00FF_FFFF,0x0100_0000,0x0100_0001]{let s:Vec<u8>=(0..n).map(|i|(i%7)as u8).collect();direct::<32768>(&s,0xFFFF_FFFF);}
 let args:Vec<_>=std::env::args().collect();let mut files:Vec<_>=std::fs::read_dir(&args[1]).unwrap().map(|p|p.unwrap().path()).filter(|p|p.is_file()).collect();files.sort();
 for p in files{let s=std::fs::read(&p).unwrap();let a=tokens(&s,frozen::parse);let b=tokens(&s,observed::parse);let c=tokens(&s,parent::parse);
 assert_eq!(a,b,"observer {}",p.display());assert_eq!(a,c,"parent {}",p.display());assert!(decode(&s,&b));let counts=observed::a14_take();
 let name=p.file_name().unwrap().to_str().unwrap();let raw:Vec<u8>=b.iter().flat_map(|t|t.to_le_bytes()).collect();std::fs::write(std::path::Path::new(&args[2]).join(format!("{}.tokens",name)),raw).unwrap();
 print!("A14_CORPUS {} {} {}",name,s.len(),b.len());for x in counts{print!(" {}",x)}println!();}}
