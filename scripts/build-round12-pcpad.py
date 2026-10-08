"""One same-token layout probe on frozen abs15; no parameter sweep."""
from pathlib import Path
import argparse,hashlib,json

ROOT=Path(__file__).resolve().parents[1]
BASE=ROOT/'candidates/r12-fast-pc507-abs15'
NAME='r12-fast-pc507-pad64'

def sha(b):return hashlib.sha256(b).hexdigest()

def generate():
    raw={f:(BASE/f).read_bytes()for f in('parse.rs','Parse.lean')};parent=json.loads((BASE/'manifest.json').read_bytes());assert {f:sha(v)for f,v in raw.items()}==parent['hashes']
    original=raw['parse.rs'].decode();start=original.index('pub fn pc_f_link<const H: usize>');end=original.index('/// Structured binaries (class 3)',start)
    section=original[start:end];changed=section
    edits=[('[u16; 32768]','[u16; 32800]',3),('let mut prev = [0u16; 32768];','let mut prev = [0u16; 32800];',1),
        ('prev[i % 32768]','prev[i % 32768 + 32]',1),('prev[c2 % 32768]','prev[c2 % 32768 + 32]',1),('prev[c % 32768]','prev[c % 32768 + 32]',1)]
    for a,b,n in edits:assert changed.count(a)==n,(a,changed.count(a),n);changed=changed.replace(a,b)
    back=changed
    for a,b,n in reversed(edits):assert back.count(b)==n;back=back.replace(b,a)
    assert back==section
    rust=(original[:start]+changed+original[end:]).encode()
    lean=raw['Parse.lean'].decode();ls=lean.index('theorem f_link_spec');le=lean.index('end PC',ls);body=lean[ls:le];assert body.count('Array Std.U16 32768#usize')==9
    proof=(lean[:ls]+body.replace('Array Std.U16 32768#usize','Array Std.U16 32800#usize')+lean[le:]).encode()
    files={'parse.rs':rust,'Parse.lean':proof};assert all(len(v)<=524288 for v in files.values())
    manifest={**parent,'candidate':NAME,'parent':BASE.relative_to(ROOT).as_posix(),'parent_hashes':parent['hashes'],
        'hashes':{f:sha(v)for f,v in files.items()},'comparison_baseline':BASE.name,'native_relation':'token_equality',
        'mechanism':'Add32 unused U16 prefix cells and shift every PC predecessor access by32, moving the logical64KiB data region by64B. Hash heads, modular positions, matching, insert order, rows and output decisions stay unchanged.',
        'difference_from_previous':'Frozen abs15 has repeatable small parent-relative signal but a remaining0.14% time gap. This isolates head/prev relative layout, not another decoder mask or chain-depth change. Only one64B displacement is proposed.',
        'source_reversal':'Three array types, initializer and all three predecessor accesses reverse to exact abs15 bytes. Logical ring still32768; maximum shifted index32799 fits32800.',
        'equivalence_status':'INFERRED by ring-cell offset mapping; native444/public exact identity versus abs15 required',
        'proof_status':'DRAFT_UNCOMPILED; nine predecessor types become32800. Addition bounds need actual extraction/full original gate; no accepted parent proof inherited.',
        'cache_hypothesis':'Two power-of-two data regions can share set alignment. Actual compiler may reorder arrays; inspect measured library machine code before attributing any result to alignment. No hardware-counter evidence currently available.',
        'fixed_predecessor_bytes_before':65536,'fixed_predecessor_bytes_after':65600,
        'stop_condition':'Any equality/decode failure rejects mapping. No paired two-axis gain or no effective data displacement closes this fixed version. Single screen cannot establish independent confirmation or private admission.',
        'formal_submission_sent':False}
    files['manifest.json']=(json.dumps(manifest,ensure_ascii=False,indent=2)+'\n').encode()
    return files

def main():
    ap=argparse.ArgumentParser(description=__doc__);ap.add_argument('--check',action='store_true');args=ap.parse_args();files=generate();dest=ROOT/'candidates'/NAME
    if args.check:assert all((dest/f).read_bytes()==v for f,v in files.items())
    else:
        assert not dest.exists();dest.mkdir()
        for f,v in files.items():(dest/f).write_bytes(v)
    print(json.dumps({'candidate':NAME,'hashes':{f:sha(v)for f,v in files.items()},'validation':'UNKNOWN; no runner dispatched'}))

if __name__=='__main__':main()
