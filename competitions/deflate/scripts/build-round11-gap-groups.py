"""Last fixed representation trial: validated group mask, no lc check per fill."""
from __future__ import annotations
import argparse
import hashlib
import importlib.util
import json
from pathlib import Path

ROOT=Path(__file__).resolve().parents[1]
sp=importlib.util.spec_from_file_location("r11_meta_source",ROOT/"scripts/build-round11-gap-meta.py")
m=importlib.util.module_from_spec(sp); assert sp.loader; sp.loader.exec_module(m)
NAME="r11-gap-groups"

GROUP_HELPERS=r'''
pub const D_GAP_STARTS: [usize; 20] = [11,13,15,17,19,23,27,31,35,43,51,59,67,83,99,115,131,163,195,227];
pub const D_GAP_ENDS: [usize; 20] = [13,15,17,19,23,27,31,35,43,51,59,67,83,99,115,131,163,195,227,258];

// Validated actual prices, not an assumption that arbitrary tabs follow codes.
// Bits12..31: twenty validated constant groups; bits0..11: positive maxlit.
pub fn d_gap_word(litc: &[u32;256], lc: &[u32;512]) -> u32 {
    let maximum=d_gap_positive_max(litc);
    if maximum==0 || maximum>4095 { return 0; }
    let mut mask=0u32; let mut g=0usize;
    while g<20 {
        let start=D_GAP_STARTS[g]; let end=D_GAP_ENDS[g];
        let price=lc[start%512]; let mut l=start.wrapping_add(1); let mut flat=true;
        while l<end && l<512 {
            if lc[l]!=price { flat=false; }
            l+=1;
        }
        if flat { mask |= 1u32 << g; }
        g+=1;
    }
    if mask==0 { 0 } else { (mask<<12) | maximum }
}

pub fn d_load_groups(tabs: &[u32], tb:usize, litc:&mut [u32;256], lc:&mut [u32;512], dcc:&mut [u32;32]) {
    d_load(tabs,tb,litc,lc,dcc);
    lc[511]=d_gap_word(litc,lc);
}

#[inline(always)]
pub fn d_block_groups(tabs:&[u32], bstart:&[u32], litc:&mut [u32;256], lc:&mut [u32;512], dcc:&mut [u32;32], bs:&mut [usize;2], pos:usize) {
    if pos<bs[1] && bs[0]>0 {
        let b=bs[0]-1;
        d_load_groups(tabs,b.wrapping_mul(D_TS),litc,lc,dcc);
        bs[0]=b; bs[1]=get0(bstart,b) as usize;
    }
}

#[inline(always)]
pub fn d_gap_group(rem:usize) -> (usize,usize) {
    if rem>=11 && rem<19 { let g=rem.wrapping_sub(11)/2; (g,11usize.wrapping_add(g.wrapping_add(1).wrapping_mul(2))) }
    else if rem>=19 && rem<35 { let g=rem.wrapping_sub(19)/4; (4usize.wrapping_add(g),19usize.wrapping_add(g.wrapping_add(1).wrapping_mul(4))) }
    else if rem>=35 && rem<67 { let g=rem.wrapping_sub(35)/8; (8usize.wrapping_add(g),35usize.wrapping_add(g.wrapping_add(1).wrapping_mul(8))) }
    else if rem>=67 && rem<131 { let g=rem.wrapping_sub(67)/16; (12usize.wrapping_add(g),67usize.wrapping_add(g.wrapping_add(1).wrapping_mul(16))) }
    else if rem>=131 && rem<258 { let g=rem.wrapping_sub(131)/32; (16usize.wrapping_add(g),d_min(258,131usize.wrapping_add(g.wrapping_add(1).wrapping_mul(32)))) }
    else { (20,rem) }
}

// Ascending contiguous stores: no lc/input read and no per-byte nxt recurrence.
// Explicit guards keep this helper total even for independent malformed args.
pub fn d_gap_group_fill(ring:&mut [u64;D_RING], out:&mut [u32], lo:usize, hi:usize, mut ri:usize, endpoint:usize, high:u64, chd:u64) {
    let mut p=lo;
    while p<hi && p<out.len() && ri<D_RING && endpoint>=p {
        let rem=endpoint-p;
        let v=high | chd.wrapping_add(rem as u64);
        ring[ri]=v; out[p]=v as u32;
        p+=1; ri+=1;
    }
}
'''

BULK=r'''        if vc < vl && rem >= 11 && rem < 258 && (vc >> 32).wrapping_add(maximum) < 0x1_0000_0000 {
            let (group,group_end)=d_gap_group(rem);
            if group<20 && ((word >> (12usize.wrapping_add(group)%32)) & 1)!=0 {
                let available=group_end.wrapping_sub(1).wrapping_sub(rem);
                let count=d_min(q.saturating_sub(stop),available);
                if count>0 && count<=q {
                    let lower=q-count;
                    let high=vc & 0xFFFF_FFFF_0000_0000;
                    let ri=lower%D_RING;
                    let room=D_RING-ri;
                    let middle=d_min(q,lower.saturating_add(room));
                    d_gap_group_fill(ring,out,lower,middle,ri,end,high,chd);
                    if middle<q { d_gap_group_fill(ring,out,middle,q,0,end,high,chd); }
                    q=lower;
                    nxt=high | chd.wrapping_add(end.wrapping_sub(lower) as u64);
                }
            }
        }
'''


def sha(x): return hashlib.sha256(x).hexdigest()


def generate():
    raw={f:(m.BASE/f).read_bytes() for f in m.PINS}; assert {f:sha(v) for f,v in raw.items()}==m.PINS
    src=raw['parse.rs'].decode(); before=m.function(src,'d_dp'); after=before
    for a,b,n in [('d_load(','d_load_groups(',1),('d_block(','d_block_groups(',2),('d_gap(','d_gap_groups(',1)]:
        assert after.count(a)==n; after=after.replace(a,b)
    back=after
    for a,b in [('d_load_groups(','d_load('),('d_block_groups(','d_block('),('d_gap_groups(','d_gap(')]: back=back.replace(a,b)
    assert back==before
    gap=m.function(m.HELPERS,'d_gap_meta').replace('d_gap_meta(','d_gap_groups(')
    gap=gap.replace('    let maximum = lc[511] as u64;','    let word = lc[511];\n    let maximum = (word & 4095) as u64;')
    start=gap.index('        if vc < vl && rem >= 3')
    gap=gap[:start]+BULK+'    }\n    nxt\n}'
    helpers='\n'+m.function(m.HELPERS,'d_gap_positive_max')+'\n'+GROUP_HELPERS+'\n'+gap+'\n'
    rust=(src.replace(before,after,1)+helpers).encode()
    for name in ('d_load','d_block','d_gap','d_bcost','d_best_len_scalar','d_best_len_old','d_best_len','d_push','d_cand','d_back'):
        assert m.function(rust.decode(),name)==m.function(src,name)
    h=m.BOUNDARY_HARNESS.replace('d_load_meta','d_load_groups').replace('d_gap_meta','d_gap_groups')
    h=h.replace('0..5','0..7').replace('(mode+1)%5','(mode+1)%7')
    h=h.replace('3 => if i % 3 == 0 { 0 } else { 3 }, _ => 1_000_000','3 => if i % 3 == 0 { 0 } else { 3 }, 4 => 1_000_000, _ => 3')
    h=h.replace('for i in 0..264 { tabs[256+i] = (i/4 + 2) as u32; }','for i in 0..264 { tabs[256+i] = if mode>=5 {2} else {(i/4+2) as u32}; }\n    if mode==6 { tabs[256+12]=3; }')
    h=h.replace('let expected = if b.iter().any(|&x|x==0) {0} else {*b.iter().max().unwrap()};',r'''let maximum=*b.iter().max().unwrap(); let mut mask=0u32;
        let starts=[11,13,15,17,19,23,27,31,35,43,51,59,67,83,99,115,131,163,195,227];
        let ends=[13,15,17,19,23,27,31,35,43,51,59,67,83,99,115,131,163,195,227,258];
        for g in 0..20 { if la[starts[g]..ends[g]].iter().all(|&x|x==la[starts[g]]) {mask|=1<<g;} }
        let expected=if b.iter().any(|&x|x==0) || maximum>4095 || mask==0 {0} else {(mask<<12)|maximum};''')
    h=h.replace('meta[511]=new::d_gap_positive_max(&lit);','meta[511]=new::d_gap_word(&lit,&lc);')
    h=h.replace('honest[511]=3; let mut fake=honest; fake[511]=1;','honest[511]=(0xfffff<<12)|3; let mut fake=honest; fake[511]=(0xfffff<<12)|1;')
    h=h.replace('ra[8]=(0xffff_fffeu64)<<32','ra[16]=(0xffff_fffeu64)<<32').replace(',6,3,8,0,512,100,nxt',',6,3,16,0,512,100,nxt')
    h=h.replace('R11_GAP_BOUNDARY','R11_GAP_GROUPS_BOUNDARY')
    # The fixture now starts rem=11 and tests grouped rem=12 before rem=13 transition.
    files={'parse.rs':rust,'Parse.lean':raw['Parse.lean'],'native-helper-check.rs':h.encode()}
    parent=json.loads((m.BASE/'manifest.json').read_text()); manifest={
        'candidate':NAME,'parent':'candidates/r10-finder-pipeline-proof','parent_hashes':m.PINS,
        'hashes':{f:sha(files[f]) for f in m.PINS},'bytes':{f:len(files[f]) for f in m.PINS},'attribution':parent['attribution'],
        'mechanism':'Once-per-load actual-lc20-group flat mask plus positive12-bit max; O(1)group end; up to2 ascending physical-ring fills without per-byte lc test or nxt dependency',
        'expected_equivalent_to':'r10-finder-pipeline-proof','equivalence_status':'INFERRED_SOURCE_LOADED_METADATA_INVARIANT; finite444/public/native boundaries PENDING; arbitrary fake metadata helper has counterexample',
        'proof_status':'UNADAPTED_PARENT_DRAFT / NOT_RUN; actual extraction required, no new obligation/axiom premises',
        'performance_status':'UNKNOWN; last representation trial, not parameter sweep. Previous direct per-byte lc variant was+1.0816% and remains frozen',
        'cost_scope':'Per load256 positive max plus actual group validation; query constant decode/check, two contiguous fills at most, still same required ring/out writes',
        'stop':'Any native/public mismatch or no useful paired speed signal stops; no further variants or capacity/depth sweeps',
        'native_helper_harness_sha256':sha(files['native-helper-check.rs'])}
    audit={'status':'VERIFIED_LOCAL_REVERSIBLE_SOURCE_ONLY','candidate_hashes':manifest['hashes'],'slot511_encoding':'20bit validated mask |12bit max; zero disables when any zero/max>4095/no valid group','retained_lc_prices':'0..510','group_ranges':list(zip([11,13,15,17,19,23,27,31,35,43,51,59,67,83,99,115,131,163,195,227],[13,15,17,19,23,27,31,35,43,51,59,67,83,99,115,131,163,195,227,258])), 'native_helper_cases_expected':{'loader':14,'dp':2156},'original_generic_helpers':'byte-identical','proof':'copied parent UNADAPTED; fill ascending index bounds/increments and q reduction need actual Funs'}
    files['manifest.json']=(json.dumps(manifest,indent=2,ensure_ascii=False)+'\n').encode()
    files['SOURCE_AUDIT.json']=(json.dumps(audit,indent=2,ensure_ascii=False)+'\n').encode()
    files['PROOF_PLAN.md']=b'# Actual-extraction proof pending\n\nNew max/group-validation nested loops; U32 mask shifts under g<20; O(1)group helper divisions; fixed-array loader index511; ascending contiguous fill bounds and increments; up to two calls preserve out.length; count>0 and count<=q proves lower=q-count<q after scalar seed. No metadata-origin premise added to totality. d_dp nine-state tuples expected unchanged, four call bindings. Actual Funs required before port. Original obligation/axioms unchanged.\n'
    assert all(0<len(files[f])<=524288 for f in m.PINS)
    return files


def main():
    ap=argparse.ArgumentParser();ap.add_argument('--check',action='store_true');ap.add_argument('--harness-v2',action='store_true');args=ap.parse_args(); files=generate();dest=ROOT/'candidates'/NAME;dest.mkdir(parents=True,exist_ok=True)
    if args.harness_v2:
        # Keep the failed v1 receipt/bytes. The broad mode-range substitution
        # also changed the substring in520..552 to520..752; fix only this fixture.
        old=b'for i in 520..752 { tabs[i] = 17; }'
        new=b'for i in 520..552 { tabs[i] = 17; }'
        raw=files['native-helper-check.rs'];assert raw.count(old)==1
        raw=raw.replace(old,new,1)
        p=dest/'native-helper-check-v2.rs'
        if args.check:assert p.read_bytes()==raw
        elif p.exists():assert p.read_bytes()==raw, 'Refusing frozen v2 mutation'
        else:p.write_bytes(raw)
        print(json.dumps({'candidate':NAME,'status':'FIXTURE_V2_NATIVE_UNCOMPILED','rust_sha256':sha(files['parse.rs']),'original_harness_sha256':sha(files['native-helper-check.rs']),'v2_harness_sha256':sha(raw),'builder_sha256':sha(Path(__file__).read_bytes())}))
        return
    for f,data in files.items():
        p=dest/f
        if args.check: assert p.read_bytes()==data
        elif p.exists(): assert p.read_bytes()==data, 'Refusing frozen candidate mutation'
        else:p.write_bytes(data)
    print(json.dumps({'candidate':NAME,'status':'SOURCE_READY_NATIVE_UNCOMPILED','hashes':{f:sha(v) for f,v in files.items()},'builder_sha256':sha(Path(__file__).read_bytes())}))


if __name__=='__main__':main()
