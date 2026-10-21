"""Pack node metadata into one u32 below 128 MiB; retain the old large-input format."""
from pathlib import Path
import argparse
import hashlib
import json
import random

ROOT = Path(__file__).resolve().parents[1]
BASE = ROOT / 'candidates/r10-record-nonempty'
NAME = 'r10-record-packed'
LIMIT = 1 << 27


def sha(data):
    return hashlib.sha256(data).hexdigest()


HELPERS = '''/// Small inputs need 27 position bits and at most 5 count bits (count <= 16).
/// Large inputs retain the original two-word format, including its u32 positions.
pub const D_PACK_LIMIT: usize = 134217728;

#[inline(always)]
pub fn d_header_words(n: usize) -> usize {
    if n < D_PACK_LIMIT { 1 } else { 2 }
}

#[inline(always)]
pub fn d_write_header(rs: &mut Vec<u32>, i: usize, count: u32, n: usize) {
    if n < D_PACK_LIMIT {
        d_push32(rs, ((i as u32) << 5) | (count & 31));
    } else {
        d_push32(rs, i as u32);
        d_push32(rs, count);
    }
}

#[inline(always)]
pub fn d_read_header(rs: &[u32], e: usize, words: usize) -> (usize, usize) {
    let last = get0(rs, e.wrapping_sub(1));
    if words == 1 {
        ((last % 32) as usize, (last >> 5) as usize)
    } else {
        (last as usize, get0(rs, e.wrapping_sub(2)) as usize)
    }
}

'''


def generate():
    raw = {f: (BASE/f).read_bytes() for f in ('parse.rs', 'Parse.lean')}
    parent = json.loads((BASE/'manifest.json').read_bytes())
    verified = json.loads((BASE/'VERIFICATION.json').read_bytes())
    assert {f: sha(b) for f,b in raw.items()} == parent['hashes'] == verified['files']
    assert verified['official_accepted']
    original = raw['parse.rs'].decode()
    edits = [
        ('pub const D_RING: usize = 1024;\n', 'pub const D_RING: usize = 1024;\n\n' + HELPERS),
        ('''/// The longest candidate of the node record that ends at `e` (the last of its `k` candidates), 0 when it has none.
#[inline(always)]
pub fn d_top(rs: &[u32], e: usize, k: usize) -> u32 {
    if k > 0 {
        get0(rs, e.wrapping_sub(3))''', '''/// The longest candidate before payload end `e` (excluding the metadata), 0 when it has none.
#[inline(always)]
pub fn d_top(rs: &[u32], e: usize, k: usize) -> u32 {
    if k > 0 {
        get0(rs, e.wrapping_sub(1))'''),
        ('''    while e >= 2 {
        let k = get0(rs, e - 1) as usize;
        let p = get0(rs, e - 2) as usize;
        if k > e - 2 || p >= hi {''', '''    let header_words = d_header_words(n);
    while e >= header_words {
        let node = d_read_header(rs, e, header_words);
        let k = node.0;
        let p = node.1;
        if k > e - header_words || p >= hi {'''),
        ('''            let a = e - 2 - k;
            let e2 = e - 2;
            let top = d_top(rs, e, k);''', '''            let a = e - header_words - k;
            let e2 = e - header_words;
            let top = d_top(rs, e2, k);'''),
        ('''    if cnt > 0 || i == 0 {
        d_push32(rs, i as u32);
        d_push32(rs, cnt);
    }''', '''    if cnt > 0 || i == 0 {
        d_write_header(rs, i, cnt, input.len());
    }'''),
    ]
    source = original
    for old,new in edits:
        assert source.count(old) == 1, old
        source = source.replace(old,new,1)
    restored = source
    for old,new in reversed(edits):
        assert restored.count(new) == 1
        restored = restored.replace(new,old,1)
    assert restored == original
    files = {'parse.rs': source.encode(), 'Parse.lean': raw['Parse.lean']}
    manifest = {'candidate': NAME, 'parent': 'candidates/r10-record-nonempty',
        'parent_hashes': parent['hashes'], 'attribution': parent['attribution'],
        'verified_parent': 'candidates/r10-record-nonempty/VERIFICATION.json',
        'hashes': {f:sha(b) for f,b in files.items()}, 'bytes': {f:len(b) for f,b in files.items()},
        'mechanism': 'Remove one u32 metadata word from every retained node for n<2^27; pack position in high27 bits and count in low5. Candidate words and parse/search/price decisions unchanged.',
        'fallback': 'For n>=2^27 keep original [position as u32,count] format. The decoder uses the same input-length decision. No forced threshold or exact corpus length routing.',
        'node_zero': 'The retained empty position-zero node is a single word0. The backward loop now accepts e>=header_words, including this one-word sentinel.',
        'bounds': 'Actual small-input positions <2^27 and counts<=16 encode exactly. Malformed streams still have guarded lengths/positions, get0 reads and strictly decreasing e with header_words in {1,2}. No arithmetic is unchecked.',
        'source_audit': 'Five reversed substitutions restore exact accepted record source. Three small format helpers, d_top offset, D decoder and header writer only; no finder, choice, route, cost or push-heuristic change.',
        'equivalence_status': 'INFERRED same decoded node stream, hence same planner inputs. Require finite native token/decode, node-stream comparison and public same output. Not an all-input equivalence theorem.',
        'proof_status': 'UNADAPTED_PARENT_ONLY: new format helpers, changed d_top and D decoder loop/header bound need actual extraction and full original gate.',
        'performance_status': 'UNKNOWN: saves four rs bytes per retained node; unpacking/branching and allocation capacity may erase the gain. Compare paired total time to record, no assumed benefit.',
        'stop': 'Reject unexplained node/token/output mismatch. Stop if total time does not improve beyond existing record; do not sweep packing widths or format thresholds.'}
    assert all(len(b)<=524288 for b in files.values())
    files['manifest.json'] = (json.dumps(manifest, indent=2)+'\n').encode()
    return files


def model():
    rng = random.Random(1007361)
    boundary = []
    for n in (0,1,16,LIMIT-1,LIMIT,LIMIT+1,(1<<32)-1,1<<32,(1<<63)-1):
        for p in sorted({0,max(0,n-1),min(max(0,n-1),(1<<32)-1)}):
            for count in (0,1,15,16):
                original = [p & 0xffffffff,count]
                packed = [((p<<5)|count)&0xffffffff] if n<LIMIT else original
                got = (packed[-1] >> 5, packed[-1]&31) if n<LIMIT else tuple(packed)
                assert got == (p & 0xffffffff,count)
                boundary.append({'n':n,'position':p,'count':count,'words':packed})
    streams = 0
    def encode(nodes, short):
        out=[]
        for p,payload in nodes:
            out.extend(payload)
            out.extend([(p<<5)|len(payload)] if short else [p & 0xffffffff,len(payload)])
        return out
    def decode(raw, short):
        out=[]; e=len(raw); width=1 if short else 2
        while e>=width:
            k=raw[e-1]&31 if short else raw[e-1]
            p=raw[e-1]>>5 if short else raw[e-2]
            assert k<=e-width
            a=e-width-k
            out.append((p,raw[a:e-width]))
            e=a
        assert e==0
        return list(reversed(out))
    for count in (1,2,3,16,127,1000):
        for rep in range(12):
            p=0; nodes=[(0,[])]
            for j in range(count):
                p+=rng.randrange(1,259)
                nodes.append((p,[rng.getrandbits(32) for _ in range(rng.randrange(1,17))]))
            old=encode(nodes,False); new=encode(nodes,True)
            assert decode(old,False)==decode(new,True)==nodes
            assert len(old)-len(new)==len(nodes)
            streams+=1
    return {'status':'VERIFIED_FINITE_HEADER_CODEC_MODEL', 'boundary_cases':len(boundary),
        'stream_cases':streams, 'boundaries':boundary, 'single_zero_word_decodes_to_origin':decode([0],True)==[(0,[])],
        'scope':'Mathematical Python codec model; not native Rust, all-input proof, actual rs counts or performance.',
        'source_sha256':json.loads(generate()['manifest.json'])['hashes']['parse.rs']}


def main():
    ap=argparse.ArgumentParser(description=__doc__)
    ap.add_argument('--check',action='store_true')
    ap.add_argument('--model-check',action='store_true')
    args=ap.parse_args(); files=generate(); folder=ROOT/'candidates'/NAME
    if args.check:
        assert all((folder/f).read_bytes()==b for f,b in files.items())
    else:
        folder.mkdir(exist_ok=True)
        for f,b in files.items():
            assert not (folder/f).exists() or (folder/f).read_bytes()==b
            (folder/f).write_bytes(b)
    print(json.dumps({'candidate':NAME,'hashes':json.loads(files['manifest.json'])['hashes']}))
    if args.model_check:
        result=model(); (folder/'codec-model-check.json').write_bytes((json.dumps(result,indent=2)+'\n').encode())
        print(json.dumps({k:v for k,v in result.items() if k!='boundaries'}))


if __name__=='__main__':
    main()
