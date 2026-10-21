"""A18: transfer public652's necessary end-at-best window filter into public658 U118."""
from pathlib import Path
import hashlib
import importlib
import json

ROOT=Path(__file__).resolve().parents[1]
BASE=ROOT/'references/round26-public-658'
OUT=ROOT/'evidence/round26/route-a'
NAME='r26-a-658-window-filter'
RS='1185749453a5abe100106f2e15082eca84521292b7233784a9c2f4562367f3ad'
LEAN='354d56aa9f58536efdb410f3d5ecdf1945bded607965fe8a48161f96b035c494'
HELP=importlib.import_module('r26-a-rep-shadow')

ADDED=r'''
// A18: necessary prefix window from public652 d_filt, with bounded fallback.
#[inline(always)]
pub fn a18_word(s:&[u8],i:usize)->u64{
 if s.len()>=8&&i<=s.len()-8{u118_be8(s,i)}else{0}
}
#[inline(always)]
pub fn a18_filter(s:&[u8],p:usize,b8:u64,best:usize)->(usize,u64,u64){
 if s.len()<8||p>s.len()-8||best>=s.len()-p{(0,0,0)}
 else if best<7{(0,b8,1u64<<((56-8*best)as u32))}
 else if best<8{(0,b8,1)}
 else{let off=best-7;(off,a18_word(s,p.wrapping_add(off)),1)}
}
#[inline(always)]
pub fn a18_pass(s:&[u8],c:usize,f:(usize,u64,u64))->bool{
 f.2==0||(a18_word(s,c.wrapping_add(f.0))^f.1)<f.2
}
'''

def sha(raw):return hashlib.sha256(raw).hexdigest()
def dump(p,obj):p.write_bytes((json.dumps(obj,indent=2)+'\n').encode())

def source():
 raw=(BASE/'parse.rs').read_bytes();assert sha(raw)==RS
 def edit(b):
  marker='''    if p + best < n {
        pb = s[p + best];
    }'''
  b=HELP.once(b,marker,marker+'\n    let b8=a18_word(s,p);\n    let mut filter=a18_filter(s,p,b8,best);')
  b=HELP.once(b,'            if s[c + best] == pb {','            if s[c + best] == pb && a18_pass(s,c,filter) {')
  b=HELP.once(b,'                        pb = s[p + l];','                        pb = s[p + l];\n                        filter=a18_filter(s,p,b8,l);')
  return b
 return (HELP.edit_fn(raw.decode(),'u118_walk<',edit)+ADDED).encode()

def main():
 raw=source();lean=(BASE/'Parse.lean').read_bytes();assert sha(lean)==LEAN
 p=ROOT/'candidates'/NAME;assert not p.exists();p.mkdir();(p/'parse.rs').write_bytes(raw);(p/'Parse.lean').write_bytes(lean)
 hashes={'parse.rs':sha(raw),'Parse.lean':sha(lean)}
 dump(p/'manifest.json',{'candidate':NAME,'parent':'references/round26-public-658','hashes':hashes,
  'attribution':{'parent_receipt':'references/round26-public-658/source-receipt.json','filter_source_receipt':'references/round26-public-652/source-receipt.json','filter_source_rust_sha256':'20992b6048110ad2837e8e0006936e1539a20d223031b838a7815517e2859d71','ownership':'Derivative of public658 U118 with public652 d_filt mechanism; original authors retained, no independent invention claim.'},
  'mechanism':'After originalbyteatbest succeeds, require the previous min(best+1,8) bytes ending atbest to match before fullcommon. Cache targetwindow, refreshonlywhenbestchanges, retain existing traversal/budgets/routes/oldbytefilter. best<7 uses onlybest+1highbytes, notall8. Bounded tails disable filter.',
  'not_combined':'Independent ofA17 lastlink control, A14tag andA16retention. No head/prev changes or extra matcher probes.',
  'proof_status':'Parent Lean copied; new pureguard/helper andloopcache proofs notadapted; fullgate NOT_RUN.',
  'quality_performance':'Expected same tokens from necessarycondition; native/encoder/pairedtime UNKNOWN.',
  'formal_submission_sent':False})
 dump(OUT/'a18-entry.json',{'name':NAME,'path':p.relative_to(ROOT).as_posix(),'control':False,'anchor':'public658','comparison_baseline':'public658','native_decode_reference':'public658','expected_equivalent_to':'public658','hashes':hashes})
 audit={'status':'VERIFIED_ONE_U118_CONSUMER_PATCH_AND_FIXED8BYTE_NECESSARY_FILTER_NOT_NATIVE','hashes':hashes,'parent_rust_sha256':RS,'filter_source':'public652 d_filt','lean_spare_bytes':524288-len(lean),'rust_bytes':len(raw),'full_gate':'NOT_RUN'};dump(OUT/'a18-build.json',audit);print(json.dumps(audit,indent=2))

if __name__=='__main__':main()
