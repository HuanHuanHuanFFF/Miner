"""Replace U16 extra table with fixed high6 prefix metadata in original low26 kid links."""
from pathlib import Path
from datetime import datetime, timezone
import hashlib
import importlib
import json
import sys

sys.dont_write_bytecode = True
ROOT = Path(__file__).resolve().parents[1]
BASE = ROOT/'references/round24-public-552'
U16 = ROOT/'candidates/r26-b-552-tree-prefix'
NAME = 'r26-b-552-tree-packed'

PACK = '''
#[inline(always)]
pub fn a_edge_pack(child:u32,tag:u16)->u32 {
 let l=(tag&511)as u32;let low=if l>31{31}else{l};
 let flag=if l<=31&&(tag&512)!=0{32}else{0};
 (child&67108863)|((low|flag)<<26)
}
#[inline(always)]
pub fn a_edge_unpack(word:u32)->u16 {
 let t=word>>26;((t&31)as u16)|if(t&32)!=0{512}else{0}
}
'''


def sha(raw):
    return hashlib.sha256(raw).hexdigest()


def build():
    raw = (U16/'parse.rs').read_bytes()
    assert sha(raw) == '4924b7919c73d39ebd14397da566b47cf3bc6c2f66b80a9547ad803a3d336c2c'
    source = raw.decode()
    original = (BASE/'parse.rs').read_bytes()
    original_text = original.decode()
    fn = importlib.import_module('prepare-round24-extract-repro').fn
    assert 'if input.len() >= 67108864' in fn(original_text, 's_plan')
    assert original_text.count('a_tree_insert(') == 2
    old = fn(source, 'a_tree_insert')
    part = old.replace('    edge: &mut [u16; 65536],\n', '', 1)
    copy = '''            let t0=edge[pk%65536];let t1=edge[(pk+1)%65536];
            let pl0=if lo_at==2*(pos%32768){258}else{lo_len};
            let pl1=if hi_at==2*(pos%32768)+1{258}else{hi_len};
            let e0=a_edge_join(pl0,a_edge_join(l,t0));let e1=a_edge_join(pl1,a_edge_join(l,t1));
            edge[lo_at%65536]=e0;edge[hi_at%65536]=e1;
            kid[lo_at % 65536] = kid[pk % 65536];
            kid[hi_at % 65536] = kid[(pk + 1) % 65536];'''
    assert part.count(copy) == 1
    part = part.replace(copy, '''            let c0=kid[pk%65536];let c1=kid[(pk+1)%65536];
            let t0=a_edge_unpack(c0);let t1=a_edge_unpack(c1);
            let pl0=if lo_at==2*(pos%32768){258}else{lo_len};
            let pl1=if hi_at==2*(pos%32768)+1{258}else{hi_len};
            let e0=a_edge_join(pl0,a_edge_join(l,t0));let e1=a_edge_join(pl1,a_edge_join(l,t1));
            kid[lo_at%65536]=a_edge_pack(c0,e0);kid[hi_at%65536]=a_edge_pack(c1,e1);''', 1)
    for at in ['lo_at', 'hi_at']:
        pair = f'            edge[{at}%65536]=a_edge_pair(l,parent_l);\n            kid[{at} % 65536] = cur as u32;'
        assert part.count(pair) == 1
        part = part.replace(pair, f'            kid[{at}%65536]=a_edge_pack(cur as u32,a_edge_pair(l,parent_l));', 1)
        load = f'            incoming=edge[{at}%65536];last_l=l;last_cmp=r.1;\n            cur = kid[{at} % 65536] as usize;'
        assert part.count(load) == 1
        part = part.replace(load, f'            let link=kid[{at}%65536];incoming=a_edge_unpack(link);last_l=l;last_cmp=r.1;\n            cur=(link&67108863)as usize;', 1)
    end = '\n        edge[lo_at%65536]=0;edge[hi_at%65536]=0;'
    assert part.count(end) == 1
    part = part.replace(end, '', 1)
    assert 'edge:' not in part and 'edge[' not in part
    source = source.replace(old, part, 1)
    source = source.replace(fn(source, 'a_find_all'), fn(original_text, 'a_find_all'), 1) + PACK
    importlib.import_module('r26-b-fix-shared-cache').spans(source)
    assert fn(source, 'a_find_all') == fn(original_text, 'a_find_all')
    # Helpers and one exact original function are the entire delta.
    helpers = importlib.import_module('r26-b-build-tree-prefix').HELPERS
    assert source.endswith(helpers+PACK)
    reverse = source[:-len(helpers+PACK)]
    reverse = reverse.replace(fn(reverse, 'a_tree_insert'), fn(original_text, 'a_tree_insert'), 1)
    assert reverse.encode() == original
    proof = (BASE/'Parse.lean').read_bytes()
    rust = source.encode()
    manifest = {'candidate': NAME, 'parent': 'public552', 'different_representation_parent': 'r26-b-552-tree-prefix',
                'written_utc': datetime.now(timezone.utc).isoformat(), 'hashes': {'parse.rs': sha(rust), 'Parse.lean': sha(proof)},
                'mechanism': 'Existing U32 kid stores complete low26timestamp plus capped31 prefix/exact in high6bits. Removes whole additional U16table and all of its clearing/reads/writes; one original child load/write carries both. Exact flags degrade only for prefix>31; original probe recovers all longer prefixes.',
                'domain': 's_plan returns empty for n>=2^26; tree insert caller closure is unique A finder inside guarded plan_cfg. Active pos+1 timestamp strictly below2^26. Full32bit head/recent timestamps retained. Original a_find_all byte-preserved.',
                'source_audit': {'only_original_function_changed': 'a_tree_insert', 'a_find_all_byte_identity': True,
                                 'full_source_reversal': True, 'fixed_timestamp_bits': 26, 'fixed_prefix_bits': 5, 'fixed_exact_bits': 1,
                                 'additional_table_bytes': 0},
                'attribution': {'original_receipt': 'references/round24-public-552/source-receipt.json',
                                'original_author_hotkey': '5FnYJUitGUNdNyWAB7YnjoYoacLsd7TKxeAND4eYyiFVBP8q'},
                'proof_status': 'DRAFT_PARENT_PROOF_UNCHANGED; newhelpers/tree scalar loop state require exact extraction/gate.',
                'semantic_status': 'Finite fixed-bit model only; actual original encoder/tokens and per-probe consumption audit still required.',
                'performance_status': 'UNKNOWN; U16 original total cost was slower, this different zero-extra-table representation is not assumed better.',
                'formal_submission_sent': False}
    assert len(rust) <= 524288 and len(proof) <= 524288
    return rust, proof, manifest


def main():
    folder = ROOT/'candidates'/NAME
    assert not folder.exists()
    rust, proof, manifest = build()
    folder.mkdir()
    for f, raw in [('parse.rs', rust), ('Parse.lean', proof)]:
        (folder/f).write_bytes(raw)
    (folder/'manifest.json').write_text(json.dumps(manifest, indent=2)+'\n')
    print(json.dumps({'candidate': NAME, 'hashes': manifest['hashes'], 'source_audit': manifest['source_audit']}))


if __name__ == '__main__':
    main()
