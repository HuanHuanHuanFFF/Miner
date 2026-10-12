"""A14: preserve public641 PC-chain order while packing an 8-bit prefix tag into head."""
from pathlib import Path
import hashlib
import json
import re

ROOT=Path(__file__).resolve().parents[1]
PARENT=ROOT/'references/round26-public-641'
OUT=ROOT/'evidence/round26/route-a'
NAME='r26-a-641-tagged-head'
RUST='97254225b7a7a5c67a749b9fed7b58c94a9612b816c233581db6d7401d502181'
LEAN='7a30722b3a337918422e3af277bf33f48073594483b9df7a7ae3c43cbf81412e'

HELPERS=r'''
// R26 A14: slot15/query-tag8/old-tag8 in a, position24/miss1 in c.
#[inline(always)]
pub fn at_key(s:&[u8],p:usize,km:u32)->usize{
 let h=((pc_be4(s,p)&km)as u64).wrapping_mul(0x9E37_79B9_7F4A_7C15);
 ((h>>49)as usize)|((((h>>41)&255)as usize)<<15)
}
#[inline(always)]
pub fn at_ahead<const H:usize>(s:&[u8],head:&[u32;H],p:usize,km:u32)->(usize,usize,u64){
 let k=at_key(s,p,km);let old=head[k&32767];let c=(old&0x00FF_FFFF)as usize;
 let tag=old>>24;let miss=old!=0&&tag!=((k>>15)&255)as u32;
 let w=if miss{0}else{pc_be8(s,c)};
 (k|((tag as usize)<<23),c|((miss as usize)<<24),w)
}
#[inline(always)]
pub fn at_ahead_if<const H:usize>(s:&[u8],head:&[u32;H],p:usize,lim:usize,a:usize,c:usize,w:u64,km:u32)->(usize,usize,u64){
 if p<lim{at_ahead(s,head,p,km)}else{(a,c,w)}
}
#[inline(always)]
pub fn at_ahead_fix<const H:usize>(s:&[u8],head:&[u32;H],p:usize,lim:usize,e:usize,a:usize,c:usize,w:u64,a0:usize,c0:usize,w0:u64,km:u32)->(usize,usize,u64){
 let old=((c&0x00FF_FFFF)as u32)|((((a>>23)&255)as u32)<<24);
 if p==e&&p<lim&&(a&32767)<H&&head[a&32767]==old{(a,c,w)}
 else{at_ahead_if(s,head,p,lim,a0,c0,w0,km)}
}
#[inline(always)]
pub fn at_link<const H:usize>(head:&mut[u32;H],prev:&mut[u32;32768],a:usize,p:usize){
 let slot=a&32767;prev[p%32768]=head[slot]&0x00FF_FFFF;
 head[slot]=(p as u32)|((((a>>15)&255)as u32)<<24);
}
#[inline(always)]
pub fn at_probe(s:&[u8],c:usize,w:u64,p:usize,km:u32)->(usize,usize){
 if c>=0x0100_0000{(0,0)}else{pc_probe_m(s,c,w,p,km)}
}
#[inline(always)]
pub fn at_lazy(s:&[u8],c:usize,w:u64,p:usize,l:usize)->(usize,usize){
 if c>=0x0100_0000{(0,0)}else{pc_probe_lazy(s,c,w,p,l)}
}
'''

def sha(raw):return hashlib.sha256(raw).hexdigest()
def dump(path,obj):path.write_bytes((json.dumps(obj,indent=2)+'\n').encode())
def fn(text,name):
 start=text.index('pub fn '+name);start=text.rfind('#[inline(always)]',0,start)
 pos=text.index('{',start)+1;depth=1;end=pos
 while depth:depth+=(text[end]=='{')-(text[end]=='}');end+=1
 return text[start:end]

def source():
 raw=(PARENT/'parse.rs').read_bytes();assert sha(raw)==RUST
 s=raw.decode();record=fn(s,'pc_f_record3<');core=fn(s,'pc_run1c<')
 record=record.replace('pc_f_record3','at_record').replace('pc_f_link','at_link')
 record=record.replace('a0 < H','(a0 & 32767) < H')
 record=record.replace('pc_slot_of_m::<H>','at_key')
 core=core.replace('pc_run1c','at_run1c')
 for old,new in [('pc_ahead_m','at_ahead'),('pc_ahead_if_m','at_ahead_if'),('pc_ahead_fix_m','at_ahead_fix'),
                 ('pc_f_link','at_link'),('pc_f_record3','at_record'),('pc_probe_m','at_probe'),('pc_probe_lazy','at_lazy')]:
  core=core.replace(old,new)
 # In the successful-primary branch the miss bit is absent; masking is explicit for proof/local audit.
 core=core.replace('let cl = prev[c % 32768] as usize;','let c = c & 0x00FF_FFFF;\n                let cl = prev[c % 32768] as usize;')
 core=core.replace('    let n = input.len();','    let n = input.len();\n    if n>=0x0100_0000||H<32768||H==65536||H==131072||H==262144 {\n        return pc_run1c::<H>(input,out,skip,lazy,skcap,km,dp,minl);\n    }',1)
 # Rename only original chain call sites, retaining the complete original kernel for the fallback.
 calls=list(re.finditer(r'pc_run1c::<\d+>',s));assert len(calls)==13,len(calls)
 s=re.sub(r'pc_run1c::<(\d+)>',r'at_run1c::<\1>',s)
 return (s+'\n'+HELPERS+'\n'+record+'\n'+core+'\n').encode()

def main():
 raw=source();lean=(PARENT/'Parse.lean').read_bytes();assert sha(lean)==LEAN
 directory=ROOT/'candidates'/NAME;assert not directory.exists(),'Frozen directory exists';directory.mkdir()
 (directory/'parse.rs').write_bytes(raw);(directory/'Parse.lean').write_bytes(lean)
 hashes={'parse.rs':sha(raw),'Parse.lean':sha(lean)}
 manifest={'candidate':NAME,'parent':'references/round26-public-641','hashes':hashes,
  'attribution':{'source_receipt':'references/round26-public-641/source-receipt.json','source_submission':'641','author_hotkey':'5FYhJSAu4q86E2Yn8UjNvpbUQVZGzq5wB7W7YFqnmvz288yo'},
  'mechanism':'Tag8 + absolute position24 in existing head u32; unchanged prev position32, same slot15, original normal/lazy order, depths, recording and emission. A nonzero mismatched head suppresses one source word load and primary/lazy probe only.',
  'boundaries':'Exact original kernel for n>=2^24 or H outside original 15bit domain. head==0 still means original source0, km applies before hash, ahead-fix compares full cached head identity.',
  'proof_status':'Parent proof copied; not adapted. Old chain proof remains required for fallback. Native/equivalence/extraction/full gate not yet run.',
  'performance_status':'UNKNOWN; tag rejection counts do not imply speedup. One new representation, no row/sweep.',
  'formal_submission_sent':False}
 dump(directory/'manifest.json',manifest)
 entry={'name':NAME,'path':directory.relative_to(ROOT).as_posix(),'control':False,'anchor':'public641','comparison_baseline':'public641','native_decode_reference':'public641','expected_equivalent_to':'public641','hashes':hashes}
 dump(OUT/'a14-tagged-entry.json',entry)
 audit={'status':'VERIFIED_EXACT_SOURCE_TRANSFORM_ONLY_NATIVE_NOT_RUN','hashes':hashes,'parent_rust_sha256':RUST,'parent_lean_sha256':LEAN,
  'new_rust_bytes':len(raw),'parent_lean_bytes':len(lean),'lean_spare_bytes_to_512KiB':524288-len(lean),'original_kernel_byte_identity':fn(raw.decode(),'pc_run1c<')==fn((PARENT/'parse.rs').read_text(),'pc_run1c<'),
  'changed_chain_calls':13,'native':'NOT_RUN','full_gate':'NOT_RUN','paired_timing':'NOT_RUN'}
 dump(OUT/'a14-tagged-build.json',audit);print(json.dumps(audit,indent=2))

if __name__=='__main__':main()
