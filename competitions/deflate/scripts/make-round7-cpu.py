"""DP instruction-layout and contiguous ring-relaxation experiments on #361."""
from pathlib import Path
import hashlib
import importlib.util
import json
import argparse

ROOT=Path(__file__).resolve().parents[1]
BASE=ROOT/'references/round7-public-361'
spec=importlib.util.spec_from_file_location('r7_decl',ROOT/'scripts/make-round4-hcore.py')
decl=importlib.util.module_from_spec(spec);spec.loader.exec_module(decl)

LINEAR='''#[inline(always)]
pub fn relax_linear(pa: &mut [u64; RING], lc: &[u32; 512], slot: usize, lo: usize, end: usize, base: u32, dpack: u32) {
    let mut p = slot;
    let mut l = lo;
    while l < end && l < 512 && p < RING {
        let c = base.wrapping_add(lc[l]);
        let v = ((c as u64) << 32) | ((dpack | l as u32) as u64);
        let old = pa[p];
        pa[p] = if v < old { v } else { old };
        p += 1;
        l += 1;
    }
}

'''
CONTIG='''#[inline(always)]
pub fn relax_seq(pa: &mut [u64; RING], lc: &[u32; 512], i: usize, lo: usize, hi: usize, base: u32, dpack: u32) {
    let start = if lo > 512 { 512 } else { lo };
    let end = if hi >= 511 { 512 } else { hi + 1 };
    let slot = i.wrapping_add(start) % RING;
    let span = end.saturating_sub(start);
    let room = RING - slot;
    let first = if span < room { span } else { room };
    let mid = start + first;
    relax_linear(pa, lc, slot, start, mid, base, dpack);
    relax_linear(pa, lc, 0, mid, end, base, dpack);
}'''

def main():
    ap=argparse.ArgumentParser();ap.add_argument('--check',action='store_true');args=ap.parse_args()
    provenance=json.loads((BASE/'PROVENANCE.json').read_text())
    data={n:(BASE/n).read_bytes() for n in ['parse.rs','Parse.lean']}
    assert all(hashlib.sha256(b).hexdigest()==provenance['hashes'][n] for n,b in data.items())
    source=data['parse.rs'].decode();functions,_=decl.rust_declarations(source)
    for suffix, names, note in [
        ('walk-outline',['walk','walk_t'],'Move the two chain walks out of the DP loop to reduce hot-loop instruction footprint; algorithms and bytes compared remain unchanged.'),
        ('rc-outline',['rc_seq'],'Move candidate relaxation out of the main DP loop; test instruction-cache and branch-layout effects with unchanged Rust function bodies.'),
        ('relax-contiguous',[],'Split each ring relaxation into at most two contiguous spans to remove per-length ring masking and allow vectorization. New helper and proof adaptation remain unverified research.'),
    ]:
        text=source;edits=[]
        for n in names:
            old=functions[n]['text'];assert old.startswith('#[inline(always)]')
            new=old.replace('#[inline(always)]','#[inline(never)]',1)
            assert text.count(old)==1;text=text.replace(old,new,1);edits.append((old,new))
        if suffix=='relax-contiguous':
            old=functions['relax_seq']['text'];new=LINEAR+CONTIG
            assert text.count(old)==1;text=text.replace(old,new,1);edits.append((old,new))
        restored=text
        for old,new in reversed(edits):assert restored.count(new)==1;restored=restored.replace(new,old,1)
        assert restored==source
        candidate='r7-mid361-'+suffix;files={'parse.rs':text.encode(),'Parse.lean':data['Parse.lean']}
        manifest={'candidate':candidate,'base_submission_id':'361','parent':'references/round7-public-361','base_hashes':provenance['hashes'],
            'hashes':{n:hashlib.sha256(b).hexdigest() for n,b in files.items()},'bytes':{n:len(b) for n,b in files.items()},'mechanism':note,
            'attribution':provenance['author_hotkey'],'audit':'Reverse declared edits restores Rust exactly; all emitter, router and knob-table bytes unchanged.',
            'proof_status':'UNKNOWN fresh obligation/axioms. For contiguous relaxation the copied proof still names the old loop and requires adaptation; never submit it as accepted.',
            'equivalence_status':'UNKNOWN finite tests requested; no all-input equivalence claim.'}
        files['manifest.json']=(json.dumps(manifest,indent=2)+'\n').encode()
        dest=ROOT/'candidates'/candidate
        if args.check:assert all((dest/n).read_bytes()==b for n,b in files.items())
        else:
            dest.mkdir(exist_ok=True)
            for n,b in files.items():assert not (dest/n).exists() or (dest/n).read_bytes()==b;(dest/n).write_bytes(b)
        print(json.dumps({'candidate':candidate,'hashes':manifest['hashes']}))

if __name__=='__main__':main()
