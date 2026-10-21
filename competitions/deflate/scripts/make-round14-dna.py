"""Probe a direct-emission search engine on the existing DNA route."""
from pathlib import Path
import hashlib,json
ROOT=Path(__file__).resolve().parents[1]

def main():
    p=ROOT/'candidates/r13-514-abs15';s=(p/'parse.rs').read_text();proof=(p/'Parse.lean').read_text()
    needle='''    let k = (pc_be4(s, i) & km) as u64;
    (k.wrapping_mul(0x9E37_79B9_7F4A_7C15) >> (64 - pc_HB)) as usize % H'''
    assert s.count(needle)==1
    s=s.replace(needle,'''    if km == 0 {
        // New six-byte key for the existing DNA route; bounds are still checked by the matcher.
        let k = pc_be8(s, i) >> 16;
        (k.wrapping_mul(0x9E37_79B9_7F4A_7C15) >> 48) as usize % H
    } else {
        let k = (pc_be4(s, i) & km) as u64;
        (k.wrapping_mul(0x9E37_79B9_7F4A_7C15) >> (64 - pc_HB)) as usize % H
    }''')
    start=s.index('pub fn pc_record3_m<');end=s.index('pub fn pc_run1<',start)
    body=s[start:end];needle='if stop > ins.wrapping_add(pc_INS_MAX) {';assert body.count(needle)==1
    body=body.replace(needle,'if km != 0 && stop > ins.wrapping_add(pc_INS_MAX) {')
    s=s[:start]+body+s[end:]
    needle='pub fn p125_row4(input:&[u8],out:&mut[u32])->usize{n_run::<65536,6,0,0,0,16,0,8,1>(input,out)}'
    assert s.count(needle)==1
    s=s.replace(needle,'pub fn p125_row4(input:&[u8],out:&mut[u32])->usize{pc_run1::<65536>(input,out,16,0,0,0)}')
    needle='rw [slot.p125_row4]\n exact N70.n_run_spec _ _ _ _ _ _ _ _ _ input out hlen';assert proof.count(needle)==1
    proof=proof.replace(needle,'rw [slot.p125_row4]\n exact PC.run1_spec _ input out _ _ _ _ hlen (by simp) (by simp)')
    name='r14-514-dna-direct';dest=ROOT/'candidates'/name;dest.mkdir(exist_ok=True)
    files={'parse.rs':s.encode(),'Parse.lean':proof.encode()}
    for f,b in files.items():
        assert not (dest/f).exists() or (dest/f).read_bytes()==b
        (dest/f).write_bytes(b)
    hashes={f:hashlib.sha256(b).hexdigest()for f,b in files.items()}
    manifest={'candidate':name,'parent':'r13-514-abs15','formal_anchor_id':'514',
        'comparison_baseline':'r13-514-abs15','hashes':hashes,
        'attribution':json.loads((p/'manifest.json').read_bytes())['attribution'],
        'mechanism':'Replace existing DNA N70 planner plus revalidating emitter by the existing proven-family PC direct emission engine, with a six-byte key and dense insertion. Existing route/classifier remains byte-identical.',
        'difference_from_old_work':'R13 focused on PC predecessor layout and EF32. This targets a separate N70 route where the previous four blocks show about31percent of per-file time in parsing. It changes search/folding as well as emission, so byte results and full-source performance are required.',
        'proof_status':'DRAFT_UNCOMPILED: existing generic PC obligation plus one route theorem edit; new hash/record branches still require fresh extraction and gate.',
        'performance_status':'UNKNOWN','formal_submission_sent':False}
    (dest/'manifest.json').write_bytes((json.dumps(manifest,indent=2)+'\n').encode())
    e=ROOT/'evidence/round14';spec=json.loads((e/'probe-a-native.json').read_bytes())
    spec['entries']=[x for x in spec['entries']if x['control']]+[{'name':name,'path':f'candidates/{name}','control':False,'anchor':'public514','comparison_baseline':'r13-514-abs15','native_decode_reference':'r13-514-abs15','hashes':hashes}]
    spec['screen_orders']=[[x['name']for x in spec['entries']],[x['name']for x in reversed(spec['entries'])]]
    spec['description']='Independent structural probe of the current N70 DNA route. Native original-encoder bytes first; public parent outputs are calibrated against prior original-harness receipts. Reject if size tradeoff cannot plausibly clear frontier. No inherited gate or timing.'
    (e/'dna-c-native.json').write_bytes((json.dumps(spec,indent=2)+'\n').encode())
    print(json.dumps({'candidate':name,'hashes':hashes}))

if __name__=='__main__':main()
