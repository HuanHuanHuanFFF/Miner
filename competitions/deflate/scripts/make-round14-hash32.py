"""Compare a 32-bit hash mix at unchanged PC table capacity and search depth."""
from pathlib import Path
import hashlib,json
ROOT=Path(__file__).resolve().parents[1]
def main():
    parent=ROOT/'candidates/r13-514-abs15';rust=(parent/'parse.rs').read_text()
    old='''    let k = (pc_be4(s, i) & km) as u64;
    (k.wrapping_mul(0x9E37_79B9_7F4A_7C15) >> (64 - pc_HB)) as usize % H'''
    new='''    let k = pc_be4(s, i) & km;
    (k.wrapping_mul(0x9E37_79B1) >> (32 - pc_HB)) as usize % H'''
    assert rust.count(old)==1;rust=rust.replace(old,new)
    name='r14-514-hash32';dest=ROOT/'candidates'/name;dest.mkdir(exist_ok=True)
    files={'parse.rs':rust.encode(),'Parse.lean':(parent/'Parse.lean').read_bytes()}
    for f,b in files.items():
        assert not (dest/f).exists() or (dest/f).read_bytes()==b
        (dest/f).write_bytes(b)
    hashes={f:hashlib.sha256(b).hexdigest()for f,b in files.items()}
    manifest={'candidate':name,'parent':'r13-514-abs15','formal_anchor_id':'514','comparison_baseline':'r13-514-abs15','hashes':hashes,
        'attribution':json.loads((parent/'manifest.json').read_bytes())['attribution'],
        'mechanism':'32-bit multiplicative PC key mixing at unchanged head capacity, insertion rules and depth; one controlled alternative hash, no parameter sweep.',
        'difference_from_old_work':'Head14 lost8355B through reduced capacity. This changes collision distribution while preserving capacity; previous compact links and packed cells did not change hash mixing. Neither source-level arithmetic width nor a new constant proves speed.',
        'proof_status':'PARENT_PROOF_UNCOMPILED_FOR_NEW_RUST','performance_status':'UNKNOWN','formal_submission_sent':False}
    (dest/'manifest.json').write_bytes((json.dumps(manifest,indent=2)+'\n').encode())
    evidence=ROOT/'evidence/round14';spec=json.loads((evidence/'probe-a-native.json').read_bytes())
    spec['entries']=[e for e in spec['entries']if e['control']]+[{'name':name,'path':f'candidates/{name}','control':False,'anchor':'public514','comparison_baseline':'r13-514-abs15','native_decode_reference':'r13-514-abs15','hashes':hashes}]
    spec['screen_orders']=[[e['name']for e in spec['entries']],[e['name']for e in reversed(spec['entries'])]]
    spec['description']='R14 E native byte screen: changed hash distribution at constant memory budget. Head14 byte loss motivates testing distribution rather than another table size. At most one hash32 source in this probe; all output changes retained.'
    (evidence/'hash-e-native.json').write_bytes((json.dumps(spec,indent=2)+'\n').encode())
    print(json.dumps({'candidate':name,'hashes':hashes}))
if __name__=='__main__':main()
