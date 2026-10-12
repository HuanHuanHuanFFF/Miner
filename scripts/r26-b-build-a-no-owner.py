"""Delete flattened DP owner scratch stores, recover only actual winning original owner."""
from pathlib import Path
from datetime import datetime, timezone
import hashlib
import importlib
import json
import sys

sys.dont_write_bytecode=True
ROOT=Path(__file__).resolve().parents[1]
BASE=ROOT/'candidates/r26-b-552-a-flatten'
NAME='r26-b-552-a-no-owner'
OWNER='''
#[inline(always)]
pub fn a_dp_owner(mb:&Vec<u32>,j0:usize,top:usize,len:usize,prev_len:usize,ext:bool,xd:usize)->u32 {
 if ext&&len>prev_len{return xd.wrapping_sub(1)as u32;}
 let mut j=j0;
 while j<top&&j<mb.len(){
  let m=mb[j];let stop=(((m>>15)&255)+3)as usize;
  if stop>=len{return m&32767;}
  j=j.wrapping_add(1);
 }
 0
}
'''


def sha(raw):return hashlib.sha256(raw).hexdigest()


def build():
    raw=(BASE/'parse.rs').read_bytes();assert sha(raw)=='e609a1aee215165a8df155ab124dbaa538fbd5111d956098cce4154431cd72f9'
    source=raw.decode();fn=importlib.import_module('prepare-round24-extract-repro').fn
    old=fn(source,'a_fill');part=old
    for before,after in [('bl: &mut [u32; 1024], dl: &mut [u32; 1024],','bl: &mut [u32; 1024],'),('base: u32, d: u32)','base: u32)'),('            dl[b + k] = d;\n','')]:
        assert part.count(before)==1;part=part.replace(before,after,1)
    source=source.replace(old,part,1)
    old=fn(source,'a_dp_fill');part=old
    before='bl: &mut [u32; 1024], dl: &mut [u32; 1024],';assert part.count(before)==1;part=part.replace(before,'bl: &mut [u32; 1024],',1)
    before='a_fill(bl, dl, prev + 1 - i, stop - i, base, m & 32767)';assert part.count(before)==1;part=part.replace(before,'a_fill(bl, prev + 1 - i, stop - i, base)',1)
    source=source.replace(old,part,1)
    old=fn(source,'a_dp_pass');part=old
    changes={'        let mut dl = [0u32; 1024];\n':'',
             'a_dp_fill(mb, dc, &mut bl, &mut dl, cl, i, bias, j0, top)':'a_dp_fill(mb, dc, &mut bl, cl, i, bias, j0, top)',
             'a_fill(&mut bl, &mut dl, prev + 1 - i, el, base, x)':'a_fill(&mut bl, prev + 1 - i, el, base)',
             'bd = dl[((r & 511) % 1024) as usize];':'bd = a_dp_owner(mb,j0,top,(r&511)as usize,prev-i,ext,xd);'}
    for before,after in changes.items():assert part.count(before)==1;part=part.replace(before,after,1)
    source=source.replace(old,part,1)+OWNER
    importlib.import_module('r26-b-fix-shared-cache').spans(source)
    assert ' dl' not in fn(source,'a_dp_pass') and ' dl' not in fn(source,'a_fill') and ' dl' not in fn(source,'a_dp_fill')
    assert fn(source,'a_dp_recs')==fn(raw.decode(),'a_dp_recs') and fn(source,'a_dp_min')==fn(raw.decode(),'a_dp_min')
    proof=(BASE/'Parse.lean').read_bytes();rust=source.encode()
    manifest={'candidate':NAME,'parent':BASE.name,'written_utc':datetime.now(timezone.utc).isoformat(),
              'hashes':{'parse.rs':sha(rust),'Parse.lean':sha(proof)},'mechanism':'Remove4KiB owner scratch and every dl slot store; keep full base scratch/overshoot/roundedscan/fallback. Recover owner only if normal packedmin beats literal, with direct inheritedowner or first original cached interval covering the winninglength.',
              'preserved':'a_dp_min/a_dp_recs, matcher/route/fitter/encoder and originalprev/pd/XL/XD exactly; no cap/threshold sweep.',
              'costs_retained':'4096byte base scratch, all bl fills including odd work and masked reads; winning cached owner scan and inheritance test are real production costs.',
              'domain':'Normal p.2=false implies ordinary valid cached domains cover all3..prev-i; their original order identifies firststop>=winninglength. Inherited len>prev-i uses existing validxd. Odd/fixed/tail reducer unchanged.',
              'proof_status':'DRAFT_PARENT_PROOF_UNCHANGED; changed helper signatures/loopcaptured arrays/newowner totality need exact extraction/fullgate.',
              'semantic_status':'UNKNOWN until native everyactualcall full cost/ch equality and original28encoder parity.',
              'performance_status':'UNKNOWN; previousflatten regression does not establish this corrected real-consumer net gain.',
              'attribution':json.loads((BASE/'manifest.json').read_bytes())['attribution'],'formal_submission_sent':False}
    assert len(rust)<=524288 and len(proof)<=524288
    return rust,proof,manifest


def main():
    folder=ROOT/'candidates'/NAME;assert not folder.exists();rust,proof,manifest=build();folder.mkdir()
    (folder/'parse.rs').write_bytes(rust);(folder/'Parse.lean').write_bytes(proof);(folder/'manifest.json').write_text(json.dumps(manifest,indent=2)+'\n')
    print(json.dumps({'candidate':NAME,'hashes':manifest['hashes']}))


if __name__=='__main__':main()
