
#![allow(dead_code)]
#[path="/home/runner/work/Miner/Miner/candidates/r26-a-641-row8/parse.rs"]mod frozen;
#[path="/home/runner/work/Miner/Miner/references/round26-public-641/parse.rs"]mod parent;
#[path="/home/runner/work/_temp/r26-a-link-replay-build/observed.rs"]mod observed;
use std::hint::black_box;
use std::time::Instant;
fn tokens(s:&[u8],f:fn(&[u8],&mut[u32])->usize)->Vec<u32>{let mut v=vec![0;s.len()];let n=f(s,&mut v);assert!(n<=s.len());v.truncate(n);v}
fn decode(s:&[u8],ts:&[u32])->bool{let mut out=Vec::with_capacity(s.len());for&t in ts{if t<256{out.push(t as u8)}else{if !(16777216..25165824).contains(&t){return false}let v=t-16777216;let d=(v/256+1)as usize;let l=(v%256+3)as usize;if d>out.len()||out.len()+l>s.len(){return false}for _ in 0..l{let b=out[out.len()-d];out.push(b)}}}out==s}
fn mix(d:u64,v:u64)->u64{(d^v).wrapping_mul(0x100000001b3)}
fn used(v:u32,p:usize)->u64{(v as u64).wrapping_mul(0x9e3779b97f4a7c15)^(p as u64)}
fn old_digest(head:&[u32],prev:&[u32])->u64{let mut d=0xcbf29ce484222325;for&v in head{d=mix(d,v as u64);}for&v in prev{d=mix(d,v as u64);}d}
fn row_digest(pos:&[u32],tags:&[u64],cur:&[u8])->u64{let mut d=0xcbf29ce484222325;for&v in pos{d=mix(d,v as u64);}for&v in tags{d=mix(d,v);}for&v in cur{d=mix(d,v as u64);}d}
// Timing encloses only the event loop and final black_box barrier, not zeroing/digest.
// MODE0 discards every return, MODE1 consumes every return, MODE2 uses actual event flags.
#[inline(never)]
fn link_parent<const H:usize,const MODE:usize>(events:&[u64])->(u128,u64,u64){
 let mut head=[0u32;H];let mut prev=[0u32;32768];black_box((&mut head,&mut prev));
 let mut sum=0u64;let start=Instant::now();
 for &e in black_box(events){let p=(e as u32)as usize;let rt=((e>>32)&0xfffff)as usize;
  let slot=((rt&4095)<<3)|((rt>>12)>>5);
  let old=head[slot];parent::pc_f_link::<H>(&mut head,&mut prev,slot,p);
  if MODE==1||(MODE==2&&((e>>52)&1)!=0){sum=sum.wrapping_add(used(old,p));}
 }black_box((&head,&prev,sum));let ns=start.elapsed().as_nanos();(ns,old_digest(&head,&prev),sum)
}
#[inline(never)]
fn link_row<const MODE:usize>(events:&[u64])->(u128,u64,u64){
 let mut pos=[0u32;32768];let mut tags=[0u64;4096];let mut cur=[0u8;4096];black_box((&mut pos,&mut tags,&mut cur));
 let mut sum=0u64;let start=Instant::now();
 for &e in black_box(events){let p=(e as u32)as usize;let rt=(e>>32)&0xfffff;
  let old=frozen::ar_link(&mut pos,&mut tags,&mut cur,(rt&4095)as usize,rt>>12,p);
  if MODE==1||(MODE==2&&((e>>52)&1)!=0){sum=sum.wrapping_add(used(old,p));}
 }black_box((&pos,&tags,&cur,sum));let ns=start.elapsed().as_nanos();(ns,row_digest(&pos,&tags,&cur),sum)
}
fn reference<const H:usize>(s:&[u8],events:&[u64],km:u32)->(u64,u64,[u64;3],[u64;3]){
 let mut head=vec![0u32;H];let mut prev=vec![0u32;32768];let mut pos=vec![0u32;32768];let mut tags=vec![0u64;4096];let mut cur=vec![0u8;4096];
 let mut oldsum=[0u64;3];let mut rowsum=[0u64;3];
 for&e in events{assert_eq!(e>>53,0);let p=(e as u32)as usize;let rt=(e>>32)&0xfffff;let row=(rt&4095)as usize;let tag=rt>>12;
  assert_eq!(frozen::ar_key(s,p,km),(row,tag));let slot=(row<<3)|((tag as usize)>>5);
  assert_eq!(parent::pc_slot_of_m::<H>(s,p,km),slot);
  let old=head[slot];prev[p%32768]=old;head[slot]=p as u32;
  let cursor=cur[row]as usize;let idx=row*8+cursor;let victim=pos[idx];pos[idx]=(p as u32).wrapping_add(1);
  tags[row]=(tags[row]&!(255u64<<(cursor*8)))|(tag<<(cursor*8));cur[row]=((cursor+1)%8)as u8;
  oldsum[1]=oldsum[1].wrapping_add(used(old,p));rowsum[1]=rowsum[1].wrapping_add(used(victim,p));
  if ((e>>52)&1)!=0{oldsum[2]=oldsum[2].wrapping_add(used(old,p));rowsum[2]=rowsum[2].wrapping_add(used(victim,p));}
 }(old_digest(&head,&prev),row_digest(&pos,&tags,&cur),oldsum,rowsum)
}
fn bench<const H:usize>(name:&str,s:&[u8],events:&[u64],km:u32){
 let expected=reference::<H>(s,events,km);println!("R26_MODEL {} {:016x} {:016x} {:?} {:?}",name,expected.0,expected.1,expected.2,expected.3);
 for block in 0..2{for rep in 0..12{for order in 0..6{let kernel=if block==0{order}else{5-order};
  let (r,method,mode)=match kernel{
   0=>(link_parent::<H,0>(events),"parent",0),1=>(link_row::<0>(events),"row",0),
   2=>(link_parent::<H,1>(events),"parent",1),3=>(link_row::<1>(events),"row",1),
   4=>(link_parent::<H,2>(events),"parent",2),_=>(link_row::<2>(events),"row",2)};
  assert_eq!(r.1,if method=="parent"{expected.0}else{expected.1});assert_eq!(r.2,if method=="parent"{expected.2[mode]}else{expected.3[mode]});
  println!("R26_TIME {} {} {} {} {} {} {} {} {:016x} {:016x}",name,block+1,rep,order,method,mode,events.len(),r.0,r.1,r.2);
 }}}
}
fn main(){let args:Vec<_>=std::env::args().collect();let mut files:Vec<_>=std::fs::read_dir(&args[1]).unwrap().map(|p|p.unwrap().path()).filter(|p|p.is_file()).collect();files.sort();
 for p in files{let s=std::fs::read(&p).unwrap();let a=tokens(&s,frozen::parse);let b=tokens(&s,observed::parse);assert_eq!(a,b);assert!(decode(&s,&b));
  let(events,h,km)=observed::r26_l_take();let name=p.file_name().unwrap().to_str().unwrap();let query=events.iter().filter(|&&e|((e>>52)&1)!=0).count();
  let tr:Vec<u8>=events.iter().flat_map(|e|e.to_le_bytes()).collect();let ts:Vec<u8>=b.iter().flat_map(|t|t.to_le_bytes()).collect();let spool=std::path::Path::new(&args[2]);
  std::fs::write(spool.join(format!("{}.events",name)),tr).unwrap();std::fs::write(spool.join(format!("{}.tokens",name)),ts).unwrap();
  println!("R26_TRACE {} {} {} {} {} {} {}",name,s.len(),b.len(),h,km,events.len(),query);
  if events.is_empty(){assert_eq!(h,0);}else{match h{
   32768=>bench::<32768>(name,&s,&events,km),32769=>bench::<32769>(name,&s,&events,km),32781=>bench::<32781>(name,&s,&events,km),
   32785=>bench::<32785>(name,&s,&events,km),131100=>bench::<131100>(name,&s,&events,km),_=>panic!("unexpectedH {}",h)}}
 }
}
