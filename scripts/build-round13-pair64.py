"""Two full32-bit recent positions in one64-bit cell, PC depth1 row only."""
from pathlib import Path
import argparse,hashlib,json

ROOT=Path(__file__).resolve().parents[1];BASE=ROOT/'references/round13-public-514';NAME='r13-514-pair64'

def sha(b):return hashlib.sha256(b).hexdigest()

HELPERS='''/// R13 packed two-recent full-position head, specialized to the original lazy0/depth1 row.
#[inline(always)]
pub fn r13_pair_link<const H: usize>(head: &mut [u64; H], a: usize, i: usize) {
    head[a] = (((i as u32) as u64) << 32) | (head[a] >> 32);
}
#[inline(always)]
pub fn r13_pair_ahead<const H: usize>(s: &[u8], head: &[u64; H], i: usize, km: u32) -> (usize, usize, u64, usize) {
    let a = pc_slot_of_m::<H>(s, i, km);
    let h = head[a];
    let c = (h >> 32) as usize;
    (a, c, pc_be8(s, c), (h as u32) as usize)
}
#[inline(always)]
pub fn r13_pair_ahead_if<const H: usize>(s: &[u8], head: &[u64; H], i: usize, lim: usize, a: usize, c: usize, w: u64, cl: usize, km: u32) -> (usize, usize, u64, usize) {
    if i < lim { r13_pair_ahead::<H>(s, head, i, km) } else { (a, c, w, cl) }
}
#[inline(always)]
pub fn r13_pair_ahead_fix<const H: usize>(s: &[u8], head: &[u64; H], i: usize, lim: usize, e: usize, a: usize, c: usize, w: u64, cl: usize, a0: usize, c0: usize, w0: u64, cl0: usize, km: u32) -> (usize, usize, u64, usize) {
    if i == e && i < lim && a < H && (head[a] >> 32) as usize == c {
        (a, c, w, (head[a] as u32) as usize)
    } else {
        r13_pair_ahead_if::<H>(s, head, i, lim, a0, c0, w0, cl0, km)
    }
}

'''

def generate():
    raw={f:(BASE/f).read_bytes()for f in('parse.rs','Parse.lean')};origin=json.loads((BASE/'receipt.json').read_bytes());assert {f:sha(b)for f,b in raw.items()}==origin['files']
    original=raw['parse.rs'].decode()
    a=original.index('pub fn pc_f_record3<const H: usize>');b=original.index('/// `pc_run1` with chain links',a);record=original[a:b]
    record=record.replace('pc_f_record3','r13_pair_record3',1).replace('head: &mut [u32; H], prev: &mut [u32; 32768],','head: &mut [u64; H],',1)
    assert record.count('pc_f_link::<H>(head, prev,')==4
    record=record.replace('pc_f_link::<H>(head, prev,','r13_pair_link::<H>(head,')
    a=original.index('pub fn pc_run1c<const H: usize>');b=original.index('/// Structured binaries (class 3)',a);run=original[a:b]
    before='pc_run1c<const H: usize>(input: &[u8], out: &mut [u32], skip: usize, lazy: usize, skcap: usize, km: u32, dp: usize, minl: usize)'
    after='r13_pair_run1<const H: usize>(input: &[u8], out: &mut [u32], skip: usize, skcap: usize, km: u32, minl: usize)'
    assert run.count(before)==1;run=run.replace(before,after,1)
    lazy_start=run.index('                let mut go = 1u32;');lazy_end=run.index('                let e = p + l;',lazy_start)
    lazy_removed=run[lazy_start:lazy_end];assert 'while go == 1 && l < lazy' in lazy_removed
    run=run[:lazy_start]+run[lazy_end:]
    edits=[('let mut head = [0u32; H];','let mut head = [0u64; H];',1),
        ('        let mut prev = [0u32; 32768];\n','',1),
        ('pc_ahead_m::<H>','r13_pair_ahead::<H>',1),
        ('let mut pre_w = a0.2;','let mut pre_w = a0.2;\n        let mut pre_cl = a0.3;',1),
        ('            let cw = pre_w;','            let cw = pre_w;\n            let cl = pre_cl;',1),
        ('pc_f_link::<H>(&mut head, &mut prev, pre_slot, p);','r13_pair_link::<H>(&mut head, pre_slot, p);',1),
        ('pc_ahead_if_m::<H>','r13_pair_ahead_if::<H>',3),
        ('pre_slot, pre_c, pre_w, km);','pre_slot, pre_c, pre_w, pre_cl, km);',4),
        ('            pre_w = a1.2;','            pre_w = a1.2;\n            pre_cl = a1.3;',1),
        ('                let cl = prev[c % 32768] as usize;\n','',1),
        ('pc_f_deepen(input, &prev, c, cl, p, f.0, f.1, dp, minl)','pc_f_try(input, c, cl, p, f.0, f.1, minl)',1),
        ('pc_f_record3::<H>(input, &mut head, &mut prev,','r13_pair_record3::<H>(input, &mut head,',1),
        ('pc_ahead_fix_m::<H>','r13_pair_ahead_fix::<H>',1),
        ('e, ae.0, ae.1, ae.2, pre_slot, pre_c, pre_w, pre_cl, km);','e, ae.0, ae.1, ae.2, ae.3, pre_slot, pre_c, pre_w, pre_cl, km);',1),
        ('                pre_w = a3.2;','                pre_w = a3.2;\n                pre_cl = a3.3;',1),
        ('                    pre_w = a4.2;','                    pre_w = a4.2;\n                    pre_cl = a4.3;',1)]
    for x,y,n in edits:
        assert run.count(x)==n,(x,run.count(x),n);run=run.replace(x,y)
    assert 'prev'not in run and 'lazy'not in run and 'dp'not in run
    helpers=HELPERS+'#[inline(always)]\n'+record+'#[inline(always)]\n'+run
    marker='/// Structured binaries (class 3)';assert original.count(marker)==1
    rust=original.replace(marker,helpers+marker,1)
    old='pc_run1c::<32768>(input,out,4,0,1000000,4294967295,1,4)';new='r13_pair_run1::<32768>(input,out,4,1000000,4294967295,4)'
    assert rust.count(old)==1;rust=rust.replace(old,new,1)
    assert rust.replace(helpers,'',1).replace(new,old,1)==original
    files={'parse.rs':rust.encode(),'Parse.lean':raw['Parse.lean']};assert all(len(b)<=524288 for b in files.values())
    manifest={'candidate':NAME,'parent':'public514','comparison_baseline':'public514','formal_anchor_id':'514','native_relation':'token_equality','hashes':{f:sha(b)for f,b in files.items()},'parent_original_hashes':origin['files'],
        'mechanism':'Only depth1/lazy0 PC row1 uses an AoS U64 head with two fullU32 positions. Both candidates arrive through one keyed cell; position-indexed predecessor ring removed. Original head order, key, skip, match validator and insertion schedule preserved.',
        'difference_from_previous':'Old bucket2 was HN-family two-plane SoA and showed no speed gain. This exact source changes physical load dependency/layout of new PC family, retains full positions, targets only the one-chain specialization; not Chat pair16 and not table shrinking.',
        'bytes_in_row1_before':262144,'bytes_in_row1_after':262144,
        'attribution':{'source':'Official public514; original source headers retained','author_hotkey':origin['author_hotkey'],'reference':'references/round13-public-514/PROVENANCE.md'},
        'source_reversal':'Removing added helpers and reversing the one row1 call restores exact parent bytes; other engines, depth2 row0 and all dispatch rules unchanged.',
        'equality_status':'INFERRED for one-chain recent-head invariant, including expired-ring alias rejection. Actual finite/public token equality required before performance claim; no universal equality certificate.',
        'proof_status':'PARENT_PROOF_UNADAPTED_FOR_NEW_PACKED_HELPERS; new immutable proof variant required if actual performance justifies migration',
        'performance_status':'UNKNOWN; cache/one-cell shape is a mechanism hypothesis, not a measured saving',
        'stop_condition':'Any finite/public token or decode mismatch stops this fixed source; no repeated worthwhile same-family total-time signal closes timing investment.',
        'formal_submission_sent':False}
    files['manifest.json']=(json.dumps(manifest,indent=2)+'\n').encode();return files

def main():
    ap=argparse.ArgumentParser();ap.add_argument('--check',action='store_true');args=ap.parse_args();files=generate();p=ROOT/'candidates'/NAME
    if args.check:assert all((p/f).read_bytes()==b for f,b in files.items())
    else:
        assert not p.exists();p.mkdir()
        for f,b in files.items():(p/f).write_bytes(b)
    print(json.dumps({'candidate':NAME,'hashes':{f:sha(b)for f,b in files.items()},'status':'DRAFT_NOT_RUN'}))

if __name__=='__main__':main()
