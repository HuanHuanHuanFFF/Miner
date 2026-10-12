"""A16: retain older head when a close overwrite lies in the parent's rejected distance band."""
from pathlib import Path
import hashlib
import json

ROOT=Path(__file__).resolve().parents[1]
BASE=ROOT/'references/round26-public-641'
OUT=ROOT/'evidence/round26/route-a'
NAME='r26-a-641-near-retain'
RS='97254225b7a7a5c67a749b9fed7b58c94a9612b816c233581db6d7401d502181'
LEAN='7a30722b3a337918422e3af277bf33f48073594483b9df7a7ae3c43cbf81412e'
ADDED=r'''
// A16: the consumer's existing d2..8 rejection band also controls overwrites.
#[inline(always)]
pub fn a16_link<const H:usize>(head:&mut[u32;H],prev:&mut[u32;32768],a:usize,p:usize,n:usize){
 let old=head[a]as usize;let gap=p.wrapping_sub(old);
 if n!=500000&&gap>=2&&gap<=8{return;}
 pc_f_link::<H>(head,prev,a,p);
}
'''

def sha(raw):return hashlib.sha256(raw).hexdigest()
def dump(p,obj):p.write_bytes((json.dumps(obj,indent=2)+'\n').encode())
def source():
 raw=(BASE/'parse.rs').read_bytes();assert sha(raw)==RS;s=raw.decode();original=s
 changes=[('pc_f_link::<H>(head, prev, a0, ins);','a16_link::<H>(head, prev, a0, ins, s.len());',1),
  ('pc_f_link::<H>(head, prev, a, ins);','a16_link::<H>(head, prev, a, ins, s.len());',3),
  ('pc_f_link::<H>(&mut head, &mut prev, pre_slot, p);','a16_link::<H>(&mut head, &mut prev, pre_slot, p, n);',1),
  ('pc_f_link::<H>(&mut head, &mut prev, pre_slot, q);','a16_link::<H>(&mut head, &mut prev, pre_slot, q, n);',1)]
 for a,b,count in changes:assert s.count(a)==count,(a,s.count(a));s=s.replace(a,b)
 reverse=s
 for a,b,count in changes:assert reverse.count(b)==count;reverse=reverse.replace(b,a)
 assert reverse==original
 assert original.count('if d>=2 && d<=8 && s.len()!=500000 {return (0,0);}')==2
 assert original.count('if d2>=2 && d2<=8 && s.len()!=500000 {return (l,d);}')==1
 return (s+ADDED).encode()

def main():
 raw=source();lean=(BASE/'Parse.lean').read_bytes();assert sha(lean)==LEAN
 p=ROOT/'candidates'/NAME;assert not p.exists();p.mkdir();(p/'parse.rs').write_bytes(raw);(p/'Parse.lean').write_bytes(lean)
 hashes={'parse.rs':sha(raw),'Parse.lean':sha(lean)}
 dump(p/'manifest.json',{'candidate':NAME,'parent':'references/round26-public-641','hashes':hashes,
  'attribution':{'source_receipt':'references/round26-public-641/source-receipt.json','author_hotkey':'5FYhJSAu4q86E2Yn8UjNvpbUQVZGzq5wB7W7YFqnmvz288yo'},
  'mechanism':'One existing-link wrapper suppresses bothheadandprev overwrite when newposition-oldhead is2..8 and n!=500000; preserve originalconsumernear guards, distance1 and500000 exception, head/prev allocation/hash/lazy/depth/emit/routes.',
  'difference_from_prior':'A7 removedconsumer rejection. R25 density reducedscheduled records or movedfixedpositions. A16 retainsolderactualsamehashhead accordingto existingconsumerband; no table/tag/extraquery orthresholdsweep.',
  'correctness':'OldHBound retained onno-op; originalpc_f_link onupdate. FullnewRust extraction andoriginalgate NOT_RUN; copiedparent proof needs wrapper spec.',
  'quality_time':'UNKNOWN: modifiedhistory maylosefuture closer/wider matches orsaveusableolderones. Counts are not compression or speed.',
  'formal_submission_sent':False})
 entry={'name':NAME,'path':p.relative_to(ROOT).as_posix(),'control':False,'anchor':'public641','comparison_baseline':'public641','native_decode_reference':'public641','hashes':hashes};dump(OUT/'a16-entry.json',entry)
 audit={'status':'VERIFIED_EXACT_SIX_CALL_PATCH_AND_RETAINED_CONSUMER_GUARDS_NOT_NATIVE','hashes':hashes,'parent_rust_sha256':RS,'link_call_sites':6,'new_rust_bytes':len(raw),'lean_bytes':len(lean),'full_gate':'NOT_RUN'}
 dump(OUT/'a16-build.json',audit);print(json.dumps(audit,indent=2))

if __name__=='__main__':main()
