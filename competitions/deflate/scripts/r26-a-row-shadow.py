"""Fixed4096x8 tagged-row shadow on the unchanged public641 PC trajectory."""
from pathlib import Path
import ast
import hashlib
import importlib
import json
import os
import random
import re
import sys

ROOT=Path(__file__).resolve().parents[1]
OUT=ROOT/'evidence/round26/route-a'
SOURCE=ROOT/'references/round26-public-641/parse.rs'
RUST='97254225b7a7a5c67a749b9fed7b58c94a9612b816c233581db6d7401d502181'
EXPECTED='evidence/round26/38176193246/quality-a3-native/diagnostics/r13-encoder/encoder.json'
EXPECTED_SHA='bfc644c34707e1320ff10c82019ca870a20baf91060c29c884a2b15fbdaca806'
UTIL=importlib.import_module('research-round25-len3-price')
GLOBALS=['engine_calls','insertions','tag_rmw','position_writes','cursor_rmw','nonempty_victims',
         'parent_prefetches','parent_prefetch_source_word_reads','parent_prefetch_window_sources','parent_prefetch_equal_masked_keys',
         'prefetch_empty_tag_mask','prefetch_empty_with_parent_equal_key','prefetch_tag_bits','query_after_changed_row_since_prefetch',
         'parent_primary_calls','parent_lazy_calls','parent_secondary_calls',
         'parent_be4_reads','parent_be8_reads','parent_xor8_pairs','parent_scalar_pairs',
         'parent_prev_reads','parent_cache_fix_head_reads','maintenance_key_be4_reads',
         'row_query_be4_reads','row_query_be8_reads','row_query_xor8_pairs','row_query_scalar_pairs']
QUERIES=['queries','tag_bits','position_reads','empty_positions','out_of_window','validator_calls','tag_false_positive',
         'budget_exhausted','parent_match','row_match','winner_retained','winner_evicted','longer','equal_length','shorter',
         'gain_better','gain_worse','parent_len3','row_len3','parent_len3_lost',
         'parent_accepted','row_accepted','row_only_accepted','parent_only_accepted']
FIELDS=GLOBALS+[phase+'_'+field for phase in ['normal','lazy']for field in QUERIES]


def sha(raw):return hashlib.sha256(raw).hexdigest()
def dump(path,value):path.write_bytes((json.dumps(value,indent=2)+'\n').encode())
def once(text,old,new):
    assert text.count(old)==1,(old,text.count(old))
    return text.replace(old,new,1)
def edit_fn(text,name,edit):
    start=text.index('pub fn '+name);opening=text.index('{',start);end=opening+1;depth=1
    while depth:depth+=(text[end]=='{')-(text[end]=='}');end+=1
    body=text[start:end];return text[:start]+edit(body)+text[end:]


APPEND=r'''
use std::cell::RefCell;
use std::sync::atomic::{AtomicU64,Ordering};
const R26_RW_WIDTH:usize=@width@;
static R26_RW_COUNTS:[AtomicU64;R26_RW_WIDTH]=[const{AtomicU64::new(0)};R26_RW_WIDTH];
static R26_RW_ACTIVE:AtomicU64=AtomicU64::new(0);
// 0 parent, 1 telemetry/maintenance, 2 counterfactual row query. No timing is taken.
static R26_RW_MODE:AtomicU64=AtomicU64::new(0);
fn r26_rw_hit(i:usize,n:u64){R26_RW_COUNTS[i].fetch_add(n,Ordering::Relaxed);}
fn r26_rw_qhit(phase:usize,i:usize,n:u64){r26_rw_hit(@global_width@+phase*@query_width@+i,n);}
struct R26RowState{pos:Vec<u32>,tags:Vec<u64>,cursor:Vec<u8>,versions:Vec<u64>,km:u32,
                  last_i:usize,last_row:usize,last_version:u64,has_prefetch:bool}
std::thread_local!{static R26_RW_STATE:RefCell<Option<R26RowState>>=const{RefCell::new(None)};
                  static R26_RW_META:RefCell<Vec<u64>>=const{RefCell::new(Vec::new())};}
#[derive(Clone,Copy)]
struct R26RowOffer{l:usize,d:usize,positions:[u32;8]}
fn r26_rw_key(s:&[u8],i:usize,km:u32)->(usize,u8){let k=(pc_be4(s,i)&km)as u64;let h=k.wrapping_mul(0x9E37_79B9_7F4A_7C15);((h>>52)as usize,(h>>44)as u8)}
fn r26_rw_mask(word:u64,wanted:u8)->u64{
 let x=word^((wanted as u64).wrapping_mul(0x0101_0101_0101_0101));
 !(((x&0x7F7F_7F7F_7F7F_7F7F).wrapping_add(0x7F7F_7F7F_7F7F_7F7F))|x|0x7F7F_7F7F_7F7F_7F7F)&0x8080_8080_8080_8080
}
fn r26_rw_begin(n:usize,h:usize,skip:usize,lazy:usize,km:u32,dp:usize,minl:usize){
 assert_eq!(R26_RW_ACTIVE.swap(1,Ordering::Relaxed),0);
 R26_RW_STATE.with(|v|{let mut v=v.borrow_mut();assert!(v.is_none());*v=Some(R26RowState{
  pos:vec![0;32768],tags:vec![0;4096],cursor:vec![0;4096],versions:vec![0;4096],km,
  last_i:0,last_row:0,last_version:0,has_prefetch:false});});
 R26_RW_META.with(|v|v.borrow_mut().extend([n as u64,h as u64,skip as u64,lazy as u64,km as u64,dp as u64,minl as u64]));
 r26_rw_hit(@engine_calls@,1);
}
fn r26_rw_end(){if R26_RW_ACTIVE.swap(0,Ordering::Relaxed)==1{R26_RW_STATE.with(|v|{assert!(v.borrow_mut().take().is_some());});}}
fn r26_rw_word(kind:usize,valid:bool){
 if !valid||R26_RW_ACTIVE.load(Ordering::Relaxed)==0{return;}
 let mode=R26_RW_MODE.load(Ordering::Relaxed);
 if mode==0{r26_rw_hit(if kind==4{@parent_be4_reads@}else if kind==8{@parent_be8_reads@}else{@parent_xor8_pairs@},1);}
 else if mode==2{r26_rw_hit(if kind==4{@row_query_be4_reads@}else if kind==8{@row_query_be8_reads@}else{@row_query_xor8_pairs@},1);}
}
fn r26_rw_eqbyte(s:&[u8],a:usize,b:usize)->bool{
 if R26_RW_ACTIVE.load(Ordering::Relaxed)==1{
  let mode=R26_RW_MODE.load(Ordering::Relaxed);
  if mode==0{r26_rw_hit(@parent_scalar_pairs@,1);}else if mode==2{r26_rw_hit(@row_query_scalar_pairs@,1);}
 }s[a]==s[b]
}
fn r26_rw_head_equal(a:u32,c:usize)->bool{
 if R26_RW_ACTIVE.load(Ordering::Relaxed)==1{r26_rw_hit(@parent_cache_fix_head_reads@,1);}a as usize==c
}
fn r26_rw_prefetch(s:&[u8],i:usize,c:usize,cw:u64,km:u32){
 if R26_RW_ACTIVE.load(Ordering::Relaxed)==0{return;}
 R26_RW_MODE.store(1,Ordering::Relaxed);
 r26_rw_hit(@parent_prefetches@,1);r26_rw_hit(@parent_prefetch_source_word_reads@,(c+8<=s.len())as u64);
 let live=c<i&&i-c<=32768;r26_rw_hit(@parent_prefetch_window_sources@,live as u64);
 let equal=live&&(((cw>>32)as u32)&km)==(pc_be4(s,i)&km);r26_rw_hit(@parent_prefetch_equal_masked_keys@,equal as u64);
 let (row,tag)=r26_rw_key(s,i,km);
 R26_RW_STATE.with(|v|{let mut v=v.borrow_mut();let st=v.as_mut().unwrap();assert_eq!(st.km,km);
  let mask=r26_rw_mask(st.tags[row],tag);r26_rw_hit(@prefetch_tag_bits@,mask.count_ones()as u64);
  r26_rw_hit(@prefetch_empty_tag_mask@,(mask==0)as u64);r26_rw_hit(@prefetch_empty_with_parent_equal_key@,(mask==0&&equal)as u64);
  st.last_i=i;st.last_row=row;st.last_version=st.versions[row];st.has_prefetch=true;
 });R26_RW_MODE.store(0,Ordering::Relaxed);
}
fn r26_rw_link<const H:usize>(s:&[u8],km:u32,head:&mut[u32;H],prev:&mut[u32;32768],a:usize,i:usize){
 pc_f_link::<H>(head,prev,a,i);assert_eq!(R26_RW_ACTIVE.load(Ordering::Relaxed),1);
 R26_RW_MODE.store(1,Ordering::Relaxed);let(row,tag)=r26_rw_key(s,i,km);r26_rw_hit(@maintenance_key_be4_reads@,1);
 R26_RW_STATE.with(|v|{let mut v=v.borrow_mut();let st=v.as_mut().unwrap();assert_eq!(st.km,km);
  let slot=(st.cursor[row]as usize)%8;let index=row*8+slot;let shift=(slot*8)as u32;
  r26_rw_hit(@nonempty_victims@,(st.pos[index]!=0)as u64);
  st.pos[index]=(i as u32).wrapping_add(1);
  st.tags[row]=(st.tags[row]&!(255u64<<shift))|((tag as u64)<<shift);
  st.cursor[row]=((slot+1)%8)as u8;st.versions[row]+=1;
 });r26_rw_hit(@insertions@,1);r26_rw_hit(@tag_rmw@,1);r26_rw_hit(@position_writes@,1);r26_rw_hit(@cursor_rmw@,1);
 R26_RW_MODE.store(0,Ordering::Relaxed);
}
fn r26_rw_offer(s:&[u8],p:usize,km:u32,budget:usize,minl:usize,threshold:usize,phase:usize)->R26RowOffer{
 assert_eq!(R26_RW_ACTIVE.load(Ordering::Relaxed),1);R26_RW_MODE.store(2,Ordering::Relaxed);
 let(row,tag)=r26_rw_key(s,p,km);
 R26_RW_MODE.store(1,Ordering::Relaxed);let key=pc_be4(s,p)&km;R26_RW_MODE.store(2,Ordering::Relaxed);
 let answer=R26_RW_STATE.with(|v|{let v=v.borrow();let st=v.as_ref().unwrap();assert_eq!(st.km,km);
  assert!(st.has_prefetch&&st.last_i==p);assert_eq!(st.last_row,row);
  r26_rw_hit(@query_after_changed_row_since_prefetch@,(st.last_version!=st.versions[row])as u64);
  let mut positions=[0u32;8];for j in 0..8{positions[j]=st.pos[row*8+j];}
  let mask=r26_rw_mask(st.tags[row],tag);
  // Exact scalar tag check, including zero-initialized slots, is telemetry only.
  for j in 0..8{assert_eq!((mask&(128u64<<(j*8)))!=0,((st.tags[row]>>(j*8))&255)==tag as u64);}
  let cursor=(st.cursor[row]as usize)%8;let shift=(cursor*8)as u32;
  let mut ordered=if shift==0{mask}else{(mask>>shift)|(mask<<(64-shift))};
  let mut fuel=8usize;let mut tried=0usize;let mut best=(0usize,0usize);
  r26_rw_qhit(phase,@q_queries@,1);r26_rw_qhit(phase,@q_tag_bits@,mask.count_ones()as u64);
  while ordered!=0&&fuel>0&&tried<budget{
   fuel-=1;let logical=7-(ordered.leading_zeros()/8)as usize;
   ordered&=!(128u64<<((logical*8)as u32));let slot=(cursor+logical)%8;let old=positions[slot];
   r26_rw_qhit(phase,@q_position_reads@,1);
   if old==0{r26_rw_qhit(phase,@q_empty_positions@,1);continue;}
   let c=old as usize-1;
   if c>=p||p-c>32768{r26_rw_qhit(phase,@q_out_of_window@,1);continue;}
   tried+=1;r26_rw_qhit(phase,@q_validator_calls@,1);
   R26_RW_MODE.store(1,Ordering::Relaxed);r26_rw_qhit(phase,@q_tag_false_positive@,((pc_be4(s,c)&km)!=key)as u64);R26_RW_MODE.store(2,Ordering::Relaxed);
   let got=if phase==1{let w=pc_be8(s,c);r26_parent_probe_lazy(s,c,w,p,threshold)}
    else if best.0>=3{r26_parent_f_try(s,p,c,p,best.0,best.1,minl)}
    else{let w=pc_be8(s,c);r26_parent_probe_m(s,c,w,p,km)};
   if got.0>=3&&got.0>best.0{best=got;}
   if best.0==258{break;}
  }
  r26_rw_qhit(phase,@q_budget_exhausted@,(tried==budget&&ordered!=0)as u64);
  R26RowOffer{l:best.0,d:best.1,positions}
 });R26_RW_MODE.store(0,Ordering::Relaxed);answer
}
fn r26_rw_compare(s:&[u8],p:usize,old:(usize,usize),row:R26RowOffer,phase:usize,current:(usize,usize)){
 R26_RW_MODE.store(1,Ordering::Relaxed);
 let om=old.0>=3;let rm=row.l>=3;r26_rw_qhit(phase,@q_parent_match@,om as u64);r26_rw_qhit(phase,@q_row_match@,rm as u64);
 if om{
  assert!(old.1>0&&old.1<=p&&old.1<=32768&&p+old.0<=s.len());
  let wanted=p-old.1;let retained=row.positions.iter().any(|&v|v!=0&&v as usize-1==wanted);
  r26_rw_qhit(phase,if retained{@q_winner_retained@}else{@q_winner_evicted@},1);
 }
 r26_rw_qhit(phase,@q_longer@,(row.l>old.0)as u64);r26_rw_qhit(phase,@q_equal_length@,(row.l==old.0)as u64);r26_rw_qhit(phase,@q_shorter@,(row.l<old.0)as u64);
 r26_rw_qhit(phase,@q_parent_len3@,(old.0==3)as u64);r26_rw_qhit(phase,@q_row_len3@,(row.l==3)as u64);r26_rw_qhit(phase,@q_parent_len3_lost@,(old.0==3&&row.l<3)as u64);
 if rm{assert!(row.d>0&&row.d<=p&&row.d<=32768&&p+row.l<=s.len());for j in 0..row.l{assert_eq!(s[p+j],s[p-row.d+j]);}}
 if om&&rm{r26_rw_qhit(phase,@q_gain_better@,(pc_gain(row.l,row.d)>pc_gain(old.0,old.1))as u64);r26_rw_qhit(phase,@q_gain_worse@,(pc_gain(row.l,row.d)<pc_gain(old.0,old.1))as u64);}
 if phase==1{
  let oa=old.0>=4&&pc_gain(old.0,old.1)>pc_gain(current.0,current.1);
  let ra=row.l>=4&&pc_gain(row.l,row.d)>pc_gain(current.0,current.1);
  r26_rw_qhit(phase,@q_parent_accepted@,oa as u64);r26_rw_qhit(phase,@q_row_accepted@,ra as u64);
  r26_rw_qhit(phase,@q_row_only_accepted@,(ra&&!oa)as u64);r26_rw_qhit(phase,@q_parent_only_accepted@,(oa&&!ra)as u64);
 }R26_RW_MODE.store(0,Ordering::Relaxed);
}
#[inline(always)]pub fn pc_probe_m(s:&[u8],c:usize,cw:u64,p:usize,km:u32)->(usize,usize){
 if R26_RW_ACTIVE.load(Ordering::Relaxed)==1{r26_rw_hit(@parent_primary_calls@,1);}r26_parent_probe_m(s,c,cw,p,km)
}
#[inline(always)]pub fn pc_probe_lazy(s:&[u8],c:usize,cw:u64,q:usize,l:usize)->(usize,usize){
 if R26_RW_ACTIVE.load(Ordering::Relaxed)==1{r26_rw_hit(@parent_lazy_calls@,1);}r26_parent_probe_lazy(s,c,cw,q,l)
}
#[inline(always)]pub fn pc_f_try(s:&[u8],c:usize,c2:usize,p:usize,l:usize,d:usize,minl:usize)->(usize,usize){
 if R26_RW_ACTIVE.load(Ordering::Relaxed)==1{r26_rw_hit(@parent_secondary_calls@,1);}r26_parent_f_try(s,c,c2,p,l,d,minl)
}
pub fn r26_rw_take()->(Vec<u64>,Vec<u64>){assert_eq!(R26_RW_ACTIVE.load(Ordering::Relaxed),0);
 let counts=(0..R26_RW_WIDTH).map(|i|R26_RW_COUNTS[i].swap(0,Ordering::Relaxed)).collect();
 let meta=R26_RW_META.with(|v|std::mem::take(&mut*v.borrow_mut()));(counts,meta)
}
'''


def instrument(raw):
    assert sha(raw)==RUST;text=raw.decode()
    text=once(text,'pub fn pc_probe_m(','pub fn r26_parent_probe_m(')
    text=once(text,'pub fn pc_probe_lazy(','pub fn r26_parent_probe_lazy(')
    text=once(text,'pub fn pc_f_try(','pub fn r26_parent_f_try(')
    text=edit_fn(text,'pc_be4',lambda b:once(b,'    if i + 4 <= s.len() {','    r26_rw_word(4,i+4<=s.len());\n    if i + 4 <= s.len() {'))
    text=edit_fn(text,'pc_be8',lambda b:once(b,'    if i + 8 <= s.len() {','    r26_rw_word(8,i+8<=s.len());\n    if i + 8 <= s.len() {'))
    text=edit_fn(text,'pc_xor8',lambda b:once(b,'    if n >= 8 && a <= n - 8 && b <= n - 8 {','    r26_rw_word(16,n>=8&&a<=n-8&&b<=n-8);\n    if n >= 8 && a <= n - 8 && b <= n - 8 {'))
    text=edit_fn(text,'pc_ahead_m',lambda b:once(b,'    (a, c, pc_be8(s, c))','    let w=pc_be8(s,c);r26_rw_prefetch(s,i,c,w,km);\n    (a,c,w)'))
    text=edit_fn(text,'pc_ahead_fix_m',lambda b:once(b,'head[a] as usize == c','r26_rw_head_equal(head[a],c)'))
    text=edit_fn(text,'pc_common_from',lambda b:once(b,'s[a + k] == s[b + k]','r26_rw_eqbyte(s,a+k,b+k)'))
    text=edit_fn(text,'r26_parent_probe_lazy',lambda b:once(b,'s[c + lo] == s[q + lo]','r26_rw_eqbyte(s,c+lo,q+lo)'))
    text=edit_fn(text,'r26_parent_f_try',lambda b:once(b,'s[c2 + l] == s[p + l]','r26_rw_eqbyte(s,c2+l,p+l)'))
    text=edit_fn(text,'pc_f_deepen',lambda b:once(b,'        let c3 = prev[c2 % 32768] as usize;',
        '        if R26_RW_ACTIVE.load(Ordering::Relaxed)==1{r26_rw_hit('+str(GLOBALS.index('parent_prev_reads'))+',1);}\n        let c3 = prev[c2 % 32768] as usize;'))
    def record(b):
        assert b.count('pc_f_link::<H>(')==4
        return b.replace('pc_f_link::<H>(', 'r26_rw_link::<H>(s,km,')
    text=edit_fn(text,'pc_f_record3',record)
    def main(b):
        b=once(b,'        let mut p = 0usize;','        let mut p = 0usize;\n        r26_rw_begin(n,H,skip,lazy,km,dp,minl);')
        b=once(b,'            let cw = pre_w;','            let cw = pre_w;\n            let r26_normal=r26_rw_offer(input,p,km,if dp>=2{3}else{2},minl,0,0);')
        assert b.count('pc_f_link::<H>(')==2
        b=b.replace('pc_f_link::<H>(', 'r26_rw_link::<H>(input,km,')
        marker='                let g = pc_f_deepen(input, &prev, c, cl, p, f.0, f.1, dp, minl);'
        b=once(b,marker,marker+'\n                r26_rw_compare(input,p,g,r26_normal,0,(0,0));')
        b=once(b,'                let cl = prev[c % 32768] as usize;',
          '                r26_rw_hit('+str(GLOBALS.index('parent_prev_reads'))+',1);\n                let cl = prev[c % 32768] as usize;')
        marker='                    let w2 = pre_w;'
        b=once(b,marker,marker+'\n                    let r26_lazy=r26_rw_offer(input,q,km,1,minl,l,1);')
        marker='                    let g = pc_probe_lazy(input, c2, w2, q, l);'
        b=once(b,marker,marker+'\n                    r26_rw_compare(input,q,g,r26_lazy,1,(l,d));')
        b=once(b,'            } else {\n                p += 1;','            } else {\n                r26_rw_compare(input,p,f,r26_normal,0,(0,0));\n                p += 1;')
        assert b.endswith('    nt\n}')
        return b[:-len('    nt\n}')]+ '    r26_rw_end();\n    nt\n}'
    text=edit_fn(text,'pc_run1c',main)
    replace={name:i for i,name in enumerate(GLOBALS)}
    replace.update({'q_'+name:i for i,name in enumerate(QUERIES)})
    replace.update(width=len(FIELDS),global_width=len(GLOBALS),query_width=len(QUERIES))
    append=re.sub(r'@([a-z0-9_]+)@',lambda m:str(replace[m[1]]),APPEND)
    assert '@'not in append
    return (text+append).encode()


HARNESS=r'''
#![allow(dead_code)]
#[path=FROZEN]mod frozen;
#[path=OBSERVED]mod observed;
fn tokens(s:&[u8],f:fn(&[u8],&mut[u32])->usize)->Vec<u32>{let mut v=vec![0;s.len()];let n=f(s,&mut v);assert!(n<=s.len());v.truncate(n);v}
fn decode(s:&[u8],ts:&[u32])->bool{let mut out=Vec::with_capacity(s.len());for&t in ts{if t<256{out.push(t as u8)}else{if !(16777216..25165824).contains(&t){return false}let v=t-16777216;let d=(v/256+1)as usize;let l=(v%256+3)as usize;if d>out.len()||out.len()+l>s.len(){return false}for _ in 0..l{let b=out[out.len()-d];out.push(b)}}}out==s}
fn main(){let args:Vec<_>=std::env::args().collect();let mut files:Vec<_>=std::fs::read_dir(&args[1]).unwrap().map(|p|p.unwrap().path()).filter(|p|p.is_file()).collect();files.sort();for p in files{let s=std::fs::read(&p).unwrap();let a=tokens(&s,frozen::parse);let b=tokens(&s,observed::parse);assert_eq!(a,b,"{}",p.display());assert!(decode(&s,&b));let(counts,meta)=observed::r26_rw_take();let name=p.file_name().unwrap().to_str().unwrap();let raw:Vec<u8>=b.iter().flat_map(|t|t.to_le_bytes()).collect();std::fs::write(std::path::Path::new(&args[2]).join(format!("{}.tokens",name)),raw).unwrap();print!("R26_ROW {} {} {}",name,s.len(),b.len());for x in counts{print!(" {}",x)}println!();println!("R26_META {} {:?}",name,meta);}}
'''


def build_harness(frozen,observed):
    result=HARNESS
    for key,path in [('FROZEN',frozen),('OBSERVED',observed)]:result=once(result,'#[path='+key+']','#[path='+json.dumps(str(path))+']')
    assert '#[path=FROZEN]'not in result and '#[path=OBSERVED]'not in result and result.count('#[path=')==2
    return result


def model():
    mask64=(1<<64)-1;lo=0x7f7f7f7f7f7f7f7f;hi=0x8080808080808080
    def matches(word,tag):
        x=word^(tag*0x0101010101010101)
        return (~(((x&lo)+lo)|x|lo))&hi
    cases=0
    for a in range(256):
        for b in range(256):
            word=(a|(b<<8))*0x0001000100010001
            expected=sum((128<<(8*i))for i in range(8)if ((word>>(8*i))&255)==0)
            assert matches(word,0)==expected;cases+=1
    rng=random.Random(261108)
    for _ in range(10000):
        word=rng.getrandbits(64);tag=rng.randrange(256)
        expected=sum((128<<(8*i))for i in range(8)if ((word>>(8*i))&255)==tag)
        assert matches(word,tag)==expected;cases+=1
    order=0
    for bits in range(256):
        m=sum((128<<(8*i))for i in range(8)if bits&(1<<i))
        for cursor in range(8):
            shift=cursor*8;rot=m if not shift else ((m>>shift)|(m<<(64-shift)))&mask64;seen=[]
            while rot:
                lane=7-(64-rot.bit_length())//8;rot&=~(128<<(lane*8));seen.append((cursor+lane)%8)
            assert seen==[(cursor+7-i)%8 for i in range(8)if bits&(1<<((cursor+7-i)%8))];order+=1
    return {'status':'VERIFIED_FINITE_BYTE_TAG_MASK_AND_NEWEST_ORDER_ONLY','mask_cases':cases,'order_cases':order,
            'state_bytes':32768*4+4096*8+4096,'observer_version_bytes_excluded_from_candidate_model':4096*8}


def preflight(spec=None):
    raw=SOURCE.read_bytes();assert sha(raw)==RUST
    expected=(ROOT/EXPECTED).read_bytes();assert sha(expected)==EXPECTED_SHA
    rows=[r for r in json.loads(expected)['rows']if r['candidate']=='public641'];assert len(rows)==28
    if spec:
        assert spec['r26_mode']=='native'and spec['native_encoder']is False and all(e['control']for e in spec['entries'])
        assert spec['r26_a_row_shadow'] is True
        assert spec['r26_a_row_expected_encoder']=={'path':EXPECTED,'sha256':EXPECTED_SHA}
        assert spec['gate_candidates']==[] and spec['extract_candidates']==[]
        assert next(e for e in spec['entries']if e['name']=='public641')['hashes']['parse.rs']==RUST
    observer=instrument(raw);harness=build_harness(SOURCE,Path('observed.rs'))
    return {'status':'VERIFIED_FROZEN_SOURCE_OBSERVER_GENERATION_AND_FINITE_ROW_MODEL_NOT_NATIVE','source_sha256':RUST,
            'observer_sha256':sha(observer),'harness_preflight_sha256':sha(harness.encode()),'expected_encoder_sha256':EXPECTED_SHA,
            'model':model(),'fields':FIELDS}


def run():
    assert os.environ.get('GITHUB_ACTIONS')=='true'and os.environ.get('RUNNER_OS')=='Linux'
    from round4 import validate
    spec=validate(os.environ['ROUND4_SPEC']);checked=preflight(spec)
    build=Path(os.environ['RUNNER_TEMP'])/'r26-a-row-shadow-build';build.mkdir();spool=build/'spool';spool.mkdir()
    out=Path(os.environ['RUNNER_TEMP'])/'round4-receipts/r26-a-row-shadow';out.mkdir(parents=True)
    observed=build/'observed.rs';raw=instrument(SOURCE.read_bytes());observed.write_bytes(raw);(out/'observer.rs').write_bytes(raw)
    harness=build_harness(SOURCE,observed);driver=build/'main.rs';driver.write_text(harness);(out/'harness.rs').write_text(harness)
    result={'status':'STARTED_FROZEN_PC_ROW_SHADOW','run_id':os.environ['GITHUB_RUN_ID'],'git_sha':os.environ['GITHUB_SHA'],'batch':os.environ['ROUND4_SPEC'],
            'source_sha256':RUST,'observer_sha256':sha(raw),'harness_sha256':sha(harness.encode()),'expected_encoder_sha256':EXPECTED_SHA,
            'scope':'Counterfactual fixed row on original641trajectory; parenttokens unchanged. No hypotheticaloffer is emitted. Query budgets limit in-window bytevalidator invocations; tag/position/window scans up to8 are counted separately. Bytehelper counters are source-level, not instructions or time.',
            'state_model':checked['model']};report=out/'receipt.json';dump(report,result)
    try:
        binary=build/'check';UTIL.captured(['rustc','+nightly-2026-08-18','--edition=2021','-O','-C','overflow-checks=yes',str(driver),'-o',str(binary)],out/'compile.log',240)
        corpus=Path(os.environ['DEFLATE_ROOT'])/'data/benchmark/corpus-stage1';process=UTIL.captured([str(binary),str(corpus),str(spool)],out/'run.log',240)
        expected={r['file']:r for r in json.loads((ROOT/EXPECTED).read_bytes())['rows']if r['candidate']=='public641'};meta={};counts={}
        for line in process.stdout.splitlines():
            if line.startswith('R26_META '):
                _,file,array=line.split(' ',2);values=ast.literal_eval(array);assert len(values)%7==0
                meta[file]=[dict(zip(['input_bytes','H','skip','lazy','km','dp','minl'],values[i:i+7]))for i in range(0,len(values),7)]
            elif line.startswith('R26_ROW '):
                _,file,n,nt,*values=line.split();assert len(values)==len(FIELDS)
                data=(corpus/file).read_bytes();tokens=(spool/(file+'.tokens')).read_bytes();e=expected[file]
                assert len(data)==int(n)==e['raw_bytes']and len(tokens)==4*int(nt)and int(nt)==e['tokens']
                assert sha(data)==e['input_sha256']and sha(tokens)==e['tokens_sha256']
                counts[file]=dict(zip(FIELDS,map(int,values)))
        assert set(counts)==set(meta)==set(expected)
        files=[]
        for file,c in counts.items():
            assert c['engine_calls']==len(meta[file])
            assert c['normal_queries']==c['parent_primary_calls']and c['lazy_queries']==c['parent_lazy_calls']
            assert c['tag_rmw']==c['position_writes']==c['cursor_rmw']==c['insertions']
            for phase in ['normal','lazy']:
                v=lambda name:c[phase+'_'+name]
                assert v('winner_retained')+v('winner_evicted')==v('parent_match')
                assert v('longer')+v('equal_length')+v('shorter')==v('queries')
                assert v('validator_calls')<=v('queries')*(3 if phase=='normal'else 1)
                assert v('position_reads')<=8*v('queries')
            files.append({'file':file,'input_sha256':expected[file]['input_sha256'],'tokens_sha256':expected[file]['tokens_sha256'],'engine_calls':meta[file],'counts':c})
        result.update(status='VERIFIED_FROZEN_PARENT_TOKEN_DECODE_AND_FIXED_ROW_COUNTERFACTUAL',files=files,
                      totals={f:sum(r['counts'][f]for r in files)for f in FIELDS})
    except Exception as exc:
        result.update(status='FAILED_OR_INCOMPLETE_ROW_SHADOW',error_type=type(exc).__name__,error=str(exc));dump(report,result);raise
    dump(report,result);print(json.dumps({'status':result['status'],'totals':result['totals']},indent=2))


if __name__=='__main__':
    if sys.argv[1:]==['--self-check']:
        result=preflight();dump(OUT/'row-shadow-source-preflight.json',result);print(json.dumps({k:v for k,v in result.items()if k!='fields'},indent=2))
    else:run()
