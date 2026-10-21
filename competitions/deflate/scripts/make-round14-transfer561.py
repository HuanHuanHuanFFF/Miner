"""One hash-width transfer to the newly public, admission-inconclusive561 reference."""
from pathlib import Path
import json,hashlib,copy
ROOT=Path(__file__).resolve().parents[1]
def main():
    p=ROOT/'references/round14-public-561';rust=(p/'parse.rs').read_text()
    old='''    let k = (pc_be4(s, i) & km) as u64;
    let hb = if H >= 65536 { 16u32 } else { 15u32 };
    (k.wrapping_mul(0x9E37_79B9_7F4A_7C15) >> (64 - hb)) as usize % H'''
    new='''    let k = pc_be4(s, i) & km;
    let hb = if H >= 65536 { 16u32 } else { 15u32 };
    (k.wrapping_mul(0x9E37_79B1) >> (32 - hb)) as usize % H'''
    assert rust.count(old)==1;rust=rust.replace(old,new)
    name='r14-561-hash32';dest=ROOT/'candidates'/name;dest.mkdir(exist_ok=True)
    files={'parse.rs':rust.encode(),'Parse.lean':(p/'Parse.lean').read_bytes()}
    for f,b in files.items():assert not (dest/f).exists()or(dest/f).read_bytes()==b;(dest/f).write_bytes(b)
    hashes={f:hashlib.sha256(b).hexdigest()for f,b in files.items()};receipt=json.loads((p/'source-receipt.json').read_bytes())
    manifest={'candidate':name,'parent':'public561','formal_anchor_id':'561','comparison_baseline':'public561','hashes':hashes,
        'attribution':{'source':'Official public submission561, itself derived from514; full original source headers retained','reference':'references/round14-public-561/source-receipt.json'},
        'parent_admission':'INCONCLUSIVE at snapshot29286; gate passed, no payable position. Parent formal coordinates are only a declared transfer anchor.',
        'mechanism':'Same single32-bit PC mix while retaining561 per-capacity15/16-bit indexing, U32 predecessor links, zero-flush check and tiny-route settings.',
        'difference_from_old_work':'New official public source after this window began, better size coordinate36.587685 than514. This is a transfer test, not independent discovery or additive reuse of the unconfirmed514 hash result.',
        'proof_status':'PUBLIC_PARENT_PROOF_UNCOMPILED_FOR_NEW_RUST','performance_status':'UNKNOWN','formal_submission_sent':False}
    (dest/'manifest.json').write_bytes((json.dumps(manifest,indent=2)+'\n').encode())
    E=ROOT/'evidence/round14';s=json.loads((E/'hash-e-native.json').read_bytes());s['entries']=[e for e in s['entries']if e['control']and e['name']not in('r13-514-abs15','public514-shadow')]
    parent_hash={f:r['sha256']for f,r in receipt['files'].items()}
    s['entries'] += [{'name':'public561','path':'references/round14-public-561','control':True,'anchor':'public561','formal_id':'561','hashes':parent_hash},
        {'name':'public561-shadow','path':'references/round14-public-561','control':True,'anchor':'public561','hashes':parent_hash},
        {'name':name,'path':f'candidates/{name}','control':False,'anchor':'public561','comparison_baseline':'public561','native_decode_reference':'public561','hashes':hashes}]
    s['native_encoder_references']=['public561'];s['snapshot_pages']='evidence/round14/official-checkpoint-1/pareto-pages.json'
    s['screen_orders']=[[e['name']for e in s['entries']],[e['name']for e in reversed(s['entries'])]]
    s['description']='R14 new-source transfer K: one fixed32-bit mix on newly published561, holding its full routing and table widths. Native actual bytes before paired time. No claim of inherited admission or transfer of514 speed.'
    (E/'transfer-k-native.json').write_bytes((json.dumps(s,indent=2)+'\n').encode());print(json.dumps({'candidate':name,'hashes':hashes}))
if __name__=='__main__':main()
