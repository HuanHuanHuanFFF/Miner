"""Single fixed 4096x8 PC primary row candidate, preserving bounded validators and read-ahead."""
from pathlib import Path
import hashlib
import json
import random
import sys

ROOT=Path(__file__).resolve().parents[1]
OUT=ROOT/'evidence/round26/route-a'
PARENT=ROOT/'references/round26-public-641'
NAME='r26-a-641-row8'
RUST='97254225b7a7a5c67a749b9fed7b58c94a9612b816c233581db6d7401d502181'
LEAN='7a30722b3a337918422e3af277bf33f48073594483b9df7a7ae3c43cbf81412e'

ADDED=r'''
// R26 A12: fixed PC primary index. Every hint is validated against input bytes.
// Ahead fields: row, tag, pre-insert cursor, remaining mask, first encoded position, word8.
#[inline(always)]
pub fn ar_key(s:&[u8],p:usize,km:u32)->(usize,u64){
 let h=((pc_be4(s,p)&km)as u64).wrapping_mul(0x9E37_79B9_7F4A_7C15);
 ((h>>52)as usize,(h>>44)&255)
}
#[inline(always)]
pub fn ar_mask(word:u64,tag:u64)->u64{
 let x=word^(tag.wrapping_mul(0x0101_0101_0101_0101));
 !(((x&0x7F7F_7F7F_7F7F_7F7F).wrapping_add(0x7F7F_7F7F_7F7F_7F7F))|x|0x7F7F_7F7F_7F7F_7F7F)&0x8080_8080_8080_8080
}
#[inline(always)]
pub fn ar_rotate(mask:u64,cursor:usize)->u64{
 let shift=((cursor%8)*8)as u32;
 if shift==0{mask}else{(mask>>shift)|(mask<<(64-shift))}
}
#[inline(always)]
pub fn ar_ahead(s:&[u8],pos:&[u32;32768],tags:&[u64;4096],cur:&[u8;4096],p:usize,km:u32)->(usize,u64,usize,u64,u32,u64){
 let k=ar_key(s,p,km);let row=k.0;let cursor=(cur[row]as usize)%8;
 let mut mask=ar_rotate(ar_mask(tags[row],k.1),cursor);
 let mut first=0u32;let mut word=0u64;let mut fuel=8usize;
 while mask!=0&&first==0&&fuel>0{
  fuel-=1;
  let logical=7usize.wrapping_sub((mask.leading_zeros()/8)as usize)%8;
  mask&=!(128u64<<((logical*8)as u32));let slot=(cursor+logical)%8;
  let old=pos[row*8+slot];
  if old>0{let c=old as usize-1;if c<p&&p-c<=32768{first=old;word=pc_be8(s,c);}}
 }
 (row,k.1,cursor,mask,first,word)
}
#[inline(always)]
pub fn ar_ahead_if(s:&[u8],pos:&[u32;32768],tags:&[u64;4096],cur:&[u8;4096],p:usize,lim:usize,km:u32,
 a:(usize,u64,usize,u64,u32,u64))->(usize,u64,usize,u64,u32,u64){
 if p<lim{ar_ahead(s,pos,tags,cur,p,km)}else{a}
}
#[inline(always)]
pub fn ar_link(pos:&mut[u32;32768],tags:&mut[u64;4096],cur:&mut[u8;4096],row:usize,tag:u64,p:usize)->u32{
 let r=row%4096;let slot=(cur[r]as usize)%8;let idx=r*8+slot;let victim=pos[idx];
 pos[idx]=(p as u32).wrapping_add(1);
 let shift=(slot*8)as u32;tags[r]=(tags[r]&!(255u64<<shift))|((tag&255)<<shift);
 cur[r]=((slot+1)%8)as u8;victim
}
#[inline(always)]
pub fn ar_offer(s:&[u8],pos:&[u32;32768],p:usize,km:u32,budget:usize,minl:usize,threshold:usize,lazy:bool,
 a:(usize,u64,usize,u64,u32,u64),victim:u32)->(usize,usize){
 let mut mask=a.3;let mut next=a.4;let mut cached=true;let mut fuel=8usize;
 let mut tried=0usize;let mut best=(0usize,0usize);
 while (next>0||mask!=0)&&tried<budget&&fuel>0&&best.0<258{
  fuel-=1;let mut old=next;let use_cache=cached&&old>0;next=0;cached=false;
  if old==0{
   let logical=7usize.wrapping_sub((mask.leading_zeros()/8)as usize)%8;
   mask&=!(128u64<<((logical*8)as u32));let slot=(a.2+logical)%8;
   old=if slot==a.2%8{victim}else{pos[(a.0%4096)*8+slot]};
  }
  if old>0{
   let c=old as usize-1;
   if c<p&&p-c<=32768{
    tried+=1;
    let got=if lazy{
     let w=if use_cache{a.5}else{pc_be8(s,c)};pc_probe_lazy(s,c,w,p,threshold)
    }else if best.0>=3{pc_f_try(s,p,c,p,best.0,best.1,minl)}
    else{let w=if use_cache{a.5}else{pc_be8(s,c)};pc_probe_m(s,c,w,p,km)};
    if got.0>=3&&got.0>best.0{best=got;}
   }
  }
 }
 best
}
#[inline(always)]
pub fn ar_record(s:&[u8],pos:&mut[u32;32768],tags:&mut[u64;4096],cur:&mut[u8;4096],
 ins0:usize,row0:usize,tag0:u64,end:usize,lim:usize,km:u32,watch:usize)->bool{
 let mut ins=ins0;let mut stop=end;let mut dirty=false;
 if stop>ins.wrapping_add(pc_INS_MAX){stop=ins.wrapping_add(pc_INS_MAX);}
 if stop>lim{stop=lim;}
 if ins<stop&&row0<4096{ar_link(pos,tags,cur,row0,tag0,ins);dirty=dirty||row0==watch;ins+=1;}
 while ins<stop{let k=ar_key(s,ins,km);ar_link(pos,tags,cur,k.0,k.1,ins);dirty=dirty||k.0==watch;ins+=1;}
 if pc_TAIL==1{
  if ins+1<end{ins=end-1;}
  if ins<end&&ins<lim{let k=ar_key(s,ins,km);ar_link(pos,tags,cur,k.0,k.1,ins);dirty=dirty||k.0==watch;}
 }else{
  if ins+pc_TAIL<end{ins=end-pc_TAIL;}
  while ins<end&&ins<lim{let k=ar_key(s,ins,km);ar_link(pos,tags,cur,k.0,k.1,ins);dirty=dirty||k.0==watch;ins+=1;}
 }dirty
}
#[inline(always)]
pub fn ar_run1c<const H:usize>(input:&[u8],out:&mut[u32],skip:usize,lazy:usize,skcap:usize,km:u32,dp:usize,minl:usize)->usize{
 let n=input.len();let mut nt=0usize;let mut ls=0usize;
 if n>16{
  let mut p=0usize;let mut pos=[0u32;32768];let mut tags=[0u64;4096];let mut cur=[0u8;4096];
  let lim=n-8;let mut miss=0usize;let mut fuel=n.saturating_add(16);
  let mut pre=ar_ahead(input,&pos,&tags,&cur,0,km);
  while p<lim&&fuel>0{
   fuel-=1;let old=pre;
   let victim=ar_link(&mut pos,&mut tags,&mut cur,old.0,old.1,p);
   pre=ar_ahead_if(input,&pos,&tags,&cur,p+1,lim,km,pre);
   let f=ar_offer(input,&pos,p,km,if dp>=2{3}else{2},minl,0,false,old,victim);
   if f.0>=3{
    let mut l=f.0;let mut d=f.1;let mut ins=p+1;let mut go=1u32;
    while go==1&&l<lazy&&p+1<lim{
     let q=p+1;let old=pre;
     let victim=ar_link(&mut pos,&mut tags,&mut cur,old.0,old.1,q);ins=q+1;
     pre=ar_ahead_if(input,&pos,&tags,&cur,q+1,lim,km,pre);
     let g=ar_offer(input,&pos,q,km,1,minl,l,true,old,victim);
     if g.0>=4&&pc_gain(g.0,g.1)>pc_gain(l,d){p=q;l=g.0;d=g.1;}else{go=0;}
    }
    let e=p+l;let ae=ar_ahead_if(input,&pos,&tags,&cur,e,lim,km,pre);
    nt=pc_flush4(input,out,nt,ls,p);let b=pc_fold_w(input,out,nt,p,l,d);
    let r=pc_put_match_h::<H>(input,out,b.0,b.1,d,b.2);nt=r.0;let end=r.1;
    let dirty=ar_record(input,&mut pos,&mut tags,&mut cur,ins,pre.0,pre.1,end,lim,km,ae.0);
    p=end;ls=end;miss=0;
    pre=if p==e&&p<lim&&!dirty{ae}else{ar_ahead_if(input,&pos,&tags,&cur,p,lim,km,pre)};
   }else{
    p+=1;miss+=1;let step=pc_skip_len(miss,skip,skcap);
    if step>0{p=pc_skip_to(p,step,lim);pre=ar_ahead_if(input,&pos,&tags,&cur,p,lim,km,pre);}
   }
  }
 }
 while ls<n{nt=pc_put_lit(input,out,nt,ls);ls+=1;}nt
}
'''

def sha(raw):return hashlib.sha256(raw).hexdigest()

def source():
    raw=(PARENT/'parse.rs').read_bytes();assert sha(raw)==RUST
    text=raw.decode();count=text.count('pc_run1c::<');assert count==13,count
    # Keep the old kernel and proof intact; change only existing chain entry calls.
    return (text.replace('pc_run1c::<','ar_run1c::<')+ADDED).encode()

def model():
    rng=random.Random(261208);cases=0;cache_cases=0
    for _ in range(12000):
        cursor=rng.randrange(8);positions=[rng.randrange(1,10000)for _ in range(8)]
        bits=rng.randrange(256);mask=sum(128<<(8*i)for i in range(8)if bits&(1<<i))
        shift=cursor*8;ordered=mask if not shift else ((mask>>shift)|(mask<<(64-shift)))&((1<<64)-1)
        original=positions[:];victim=positions[cursor];positions[cursor]=10001
        seen=[];fuel=8
        while ordered and fuel:
            fuel-=1;logical=7-(64-ordered.bit_length())//8;ordered&=~(128<<(logical*8));slot=(cursor+logical)%8
            seen.append(victim if slot==cursor else positions[slot])
        expected=[original[(cursor+7-i)%8]for i in range(8)if bits&(1<<((cursor+7-i)%8))]
        assert seen==expected;cases+=1
        watched=rng.randrange(4096);rows=[rng.randrange(4096)for _ in range(rng.randrange(260))]
        dirty=False
        for row in rows:dirty=dirty or row==watched
        assert dirty==(watched in rows);cache_cases+=1
    return {'status':'VERIFIED_FINITE_PREINSERT_VICTIM_AND_CACHE_DIRTY_MODELS_NOT_RUST',
            'victim_cases':cases,'cache_cases':cache_cases}

def main():
    dest=ROOT/'candidates'/NAME;raw=source();lean=(PARENT/'Parse.lean').read_bytes();assert sha(lean)==LEAN
    if sys.argv[1:]==['--check']:
        assert (dest/'parse.rs').read_bytes()==raw and (dest/'Parse.lean').read_bytes()==lean
    else:
        assert sys.argv[1:]==[];dest.mkdir(exist_ok=True);(dest/'parse.rs').write_bytes(raw);(dest/'Parse.lean').write_bytes(lean)
        info={'candidate':NAME,'parent':'references/round26-public-641','parent_author':'5FYhJSAu4q86E2Yn8UjNvpbUQVZGzq5wB7W7YFqnmvz288yo',
              'parent_rust_sha256':RUST,'parse_sha256':sha(raw),'lean_sha256':LEAN,'proof_status':'UNADAPTED_PARENT_NOT_A_NEW_PROOF',
              'mechanism':'Fixed4096x8primaryrow actualkm; normal2/3 lazy1 validators, preinsertvictim, firstsourceword readahead, explicitrecord-rowdirty invalidation. No capacityscan.'}
        (dest/'source.json').write_text(json.dumps(info,indent=2)+'\n')
    checked={'status':'VERIFIED_LOCAL_SOURCE_GENERATION_AND_MODELS_NOT_NATIVE','candidate':NAME,'rust_sha256':sha(raw),'lean_sha256':LEAN,
             'rust_bytes':len(raw),'lean_bytes':len(lean),'model':model()}
    (OUT/'row-candidate-source-preflight.json').write_text(json.dumps(checked,indent=2)+'\n');print(json.dumps(checked,indent=2))

if __name__=='__main__':main()
