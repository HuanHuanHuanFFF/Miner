"""Controlled wider prefix partitions in the new element-aligned EF32 matcher."""
from pathlib import Path
import argparse,hashlib,json

ROOT=Path(__file__).resolve().parents[1];BASE=ROOT/'references/round13-public-514'

def sha(b):return hashlib.sha256(b).hexdigest()

def generate(bits):
    assert bits in(15,16);size=1<<bits;shift=32-bits
    raw={f:(BASE/f).read_bytes()for f in('parse.rs','Parse.lean')};origin=json.loads((BASE/'receipt.json').read_bytes());assert {f:sha(b)for f,b in raw.items()}==origin['files']
    original=raw['parse.rs'].decode();a=original.index('/// EF32: hash slot (14 bits)');b=original.index('// ─────────────── ETINY:',a)
    old=original[a:b];body=old;edits=[('(14 bits)',f'({bits} bits)',1),('>> 18) as usize % 16384',f'>> {shift}) as usize % {size}',1),('[0u32; 16384]',f'[0u32; {size}]',1)]
    for x,y,n in edits:assert body.count(x)==n;body=body.replace(x,y)
    restored=body
    for x,y,n in reversed(edits):assert restored.count(y)==n;restored=restored.replace(y,x)
    assert restored==old
    rust=(original[:a]+body+original[b:]).encode()
    lean=raw['Parse.lean'].decode();a=lean.index('namespace EF32');b=lean.index('end EF32',a);oldproof=lean[a:b];assert oldproof.count('16384')==2
    newproof=oldproof.replace('16384',str(size));proof=(lean[:a]+newproof+lean[b:]).encode()
    assert proof.decode().replace(newproof,oldproof,1).encode()==raw['Parse.lean']
    name=f'r13-514-ef32-h{bits}';files={'parse.rs':rust,'Parse.lean':proof}
    assert all(len(b)<=524288 for b in files.values())
    manifest={'candidate':name,'parent':'public514','comparison_baseline':'public514','formal_anchor_id':'514','native_relation':'decode_only',
        'hashes':{f:sha(b)for f,b in files.items()},'parent_original_hashes':origin['files'],
        'mechanism':f'Partition the original14-bit EF32 prefix hash into{bits}-bit slots; same three-byte key, multiplicative hash, aligned probes, single head, search budget and byte validator. Table16384→{size}.',
        'difference_from_previous':'Earlier generic HN table widening was inconclusive. This is the newly public514 element-aligned single-probe EF32 engine; allocate timing only if fixed-position shadow replay finds missing genuine matches.',
        'attribution':{'source':'Official public514; original source headers retained','author_hotkey':origin['author_hotkey'],'reference':'references/round13-public-514/PROVENANCE.md'},
        'source_reversal':'Exact parent recovered by reversing three isolated EF32 edits and two proof dimension constants. No routes or other engines changed.',
        'proof_status':'DRAFT_UNCOMPILED; EF32 hash bound and head array dimension adapted; original obligation unchanged',
        'performance_status':'UNKNOWN; shadow coverage is neither saved compressed bytes nor timing gain',
        'stop_condition':'No missing valid match opportunities, any decode/panic failure, or public two-axis change insufficient for current boundary closes this frozen size.',
        'formal_submission_sent':False}
    files['manifest.json']=(json.dumps(manifest,indent=2)+'\n').encode();return name,files

def main():
    ap=argparse.ArgumentParser();ap.add_argument('--check',action='store_true');args=ap.parse_args()
    for bits in(15,16):
        n,files=generate(bits);p=ROOT/'candidates'/n
        if args.check:assert all((p/f).read_bytes()==b for f,b in files.items())
        else:
            assert not p.exists();p.mkdir()
            for f,b in files.items():(p/f).write_bytes(b)
        print(json.dumps({'candidate':n,'hashes':{f:sha(b)for f,b in files.items()},'status':'DRAFT_NOT_RUN'}))

if __name__=='__main__':main()
