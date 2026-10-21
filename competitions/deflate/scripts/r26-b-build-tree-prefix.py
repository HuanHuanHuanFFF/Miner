"""One U16 A tree edge-prefix production implementation; original encoder parity first."""
from pathlib import Path
from datetime import datetime, timezone
import hashlib
import importlib
import json
import sys

sys.dont_write_bytecode = True
ROOT = Path(__file__).resolve().parents[1]
BASE = ROOT / 'references/round24-public-552'
NAME = 'r26-b-552-tree-prefix'
EXPECTED = '5adaaeac471b86128778bf6b67f786542f5c8e079adbf1160f0502309f7befb9'

HELPERS = '''
#[inline(always)]
pub fn a_edge_join(l:usize,tag:u16)->u16 {
 let t=(tag&511)as usize;let low=if l<t{l}else{t};
 let exact=(l<t&&l<258)||(t<l&&(tag&512)!=0);
 (low as u16)|if exact{512}else{0}
}
#[inline(always)]
pub fn a_edge_pair(l:usize,p:usize)->u16 {
 let low=if l<p{l}else{p};(low as u16)|if l!=p&&low<258{512}else{0}
}
#[inline(always)]
pub fn a_edge_probe(s:&[u8],p:usize,q:usize,seed:usize,tag:u16,last_l:usize,last_cmp:usize)->(usize,usize) {
 let t=(tag&511)as usize;
 if ((tag&512)!=0&&t<last_l)||t>last_l {
  let l=if t<last_l{t}else{last_l};
  let cmp=if t<last_l{if last_cmp==1{0}else{1}}else{last_cmp};
  (if l>258{258}else{l},cmp)
 }else{
  let low=if t<last_l{t}else{last_l};let raised=if low>seed{low}else{seed};
  a_probe(s,p,q,if raised>258{258}else{raised})
 }
}
'''


def sha(raw):
    return hashlib.sha256(raw).hexdigest()


def build():
    raw = (BASE / 'parse.rs').read_bytes()
    assert sha(raw) == EXPECTED
    source = raw.decode()
    fn = importlib.import_module('prepare-round24-extract-repro').fn
    old = fn(source, 'a_tree_insert')
    part = old.replace('    pos: usize,', '    edge: &mut [u16; 65536],\n    pos: usize,', 1)
    part = part.replace('    let mut steps = 0usize;', '    let mut steps = 0usize;\n    let mut incoming=0u16;let mut last_l=0usize;let mut last_cmp=0usize;', 1)
    probe = '        let r = a_probe(s, p, pos, if lo_len < hi_len { lo_len } else { hi_len });'
    assert part.count(probe) == 1
    part = part.replace(probe, '        let r = a_edge_probe(s,p,pos,if lo_len<hi_len{lo_len}else{hi_len},incoming,last_l,last_cmp);', 1)
    copy = '            kid[lo_at % 65536] = kid[pk % 65536];\n            kid[hi_at % 65536] = kid[(pk + 1) % 65536];'
    assert part.count(copy) == 1
    part = part.replace(copy, '''            let t0=edge[pk%65536];let t1=edge[(pk+1)%65536];
            let pl0=if lo_at==2*(pos%32768){258}else{lo_len};
            let pl1=if hi_at==2*(pos%32768)+1{258}else{hi_len};
            let e0=a_edge_join(pl0,a_edge_join(l,t0));let e1=a_edge_join(pl1,a_edge_join(l,t1));
            edge[lo_at%65536]=e0;edge[hi_at%65536]=e1;
''' + copy, 1)
    lower = '            kid[lo_at % 65536] = cur as u32;\n            lo_at = pk + 1;\n            lo_len = l;\n            cur = kid[lo_at % 65536] as usize;'
    upper = '            kid[hi_at % 65536] = cur as u32;\n            hi_at = pk;\n            hi_len = l;\n            cur = kid[hi_at % 65536] as usize;'
    for original, at, length, nxt, root in [(lower, 'lo_at', 'lo_len', 'pk + 1', '2*(pos%32768)'),
                                          (upper, 'hi_at', 'hi_len', 'pk', '2*(pos%32768)+1')]:
        assert part.count(original) == 1
        part = part.replace(original, f'''            let parent_l=if {at}=={root}{{258}}else{{{length}}};
            edge[{at}%65536]=a_edge_pair(l,parent_l);
            kid[{at} % 65536] = cur as u32;
            {at} = {nxt};
            {length} = l;
            incoming=edge[{at}%65536];last_l=l;last_cmp=r.1;
            cur = kid[{at} % 65536] as usize;''', 1)
    ending = '        kid[lo_at % 65536] = 0;\n        kid[hi_at % 65536] = 0;'
    assert part.count(ending) == 1
    part = part.replace(ending, ending + '\n        edge[lo_at%65536]=0;edge[hi_at%65536]=0;', 1)
    source = source.replace(old, part, 1)
    old = fn(source, 'a_find_all')
    part = old.replace('    let n = s.len();', '    let n = s.len();\n    let mut edge=[0u16;65536];', 1)
    call = 'a_tree_insert(s, &mut head, &mut kid, &mut h3, &mut rct, i, pre, depth, mb)'
    assert part.count(call) == 1
    part = part.replace(call, 'a_tree_insert(s, &mut head, &mut kid, &mut h3, &mut rct, &mut edge, i, pre, depth, mb)', 1)
    source = source.replace(old, part, 1) + HELPERS
    importlib.import_module('r26-b-fix-shared-cache').spans(source)
    proof = (BASE / 'Parse.lean').read_bytes()
    manifest = {'candidate': NAME, 'parent': 'public552', 'parent_path': BASE.relative_to(ROOT).as_posix(),
                'written_utc': datetime.now(timezone.utc).isoformat(),
                'mechanism': 'Actual U16 edge metadata plus exact unequal-prefix shortcuts and raised valid-prefix fallback; every real metadata update/read/clear remains. Same original tree/root/3byte/continuation/DP/route knobs and guarded pushes.',
                'evidence': ['evidence/round26/38215726866/tree-b19-native/diagnostics/r26-b-tree-edge/receipt.json',
                             'evidence/round26/38216239816/tree-b20-native/diagnostics/r26-b-tree-edge/receipt.json'],
                'metadata_invariants': 'B19 real-owner double NICE rebasing; smaller exact prefix permits shortcut, equal or uncertain lower bound permits seeded original probe. Capped258 direction is unused by copy branch.',
                'table_bytes': 131072, 'attribution': 'Original public552 receipt/author and source header retained; edge metadata mechanism is the R26 research delta.',
                'proof_status': 'DRAFT_UNCHANGED_PARENT_PROOF_NOT_ACCEPTED_FOR_CHANGED_HELPERS_OR_ARRAY_STATE',
                'performance_status': 'UNKNOWN: original encoder/native finite parity first; original total paired timing and fresh independent confirmation mandatory.',
                'formal_submission_sent': False}
    rust = source.encode()
    manifest['hashes'] = {'parse.rs': sha(rust), 'Parse.lean': sha(proof)}
    assert len(rust) <= 524288 and len(proof) <= 524288
    return rust, proof, manifest


def main():
    folder = ROOT / 'candidates' / NAME
    assert not folder.exists()
    rust, proof, manifest = build()
    folder.mkdir()
    (folder / 'parse.rs').write_bytes(rust)
    (folder / 'Parse.lean').write_bytes(proof)
    (folder / 'manifest.json').write_text(json.dumps(manifest, indent=2) + '\n')
    spec = json.loads((ROOT / 'evidence/round26/route-b/b19-tree-edge-native.json').read_bytes())
    spec.pop('r26_b_tree_edge_counts')
    spec.pop('r26_required_files')
    public514 = ROOT / 'references/round13-public-514'
    spec['entries'].append({'name': 'public514', 'path': public514.relative_to(ROOT).as_posix(), 'control': True,
                            'anchor': 'public514', 'formal_id': '514',
                            'hashes': {f: sha((public514/f).read_bytes()) for f in ('parse.rs', 'Parse.lean')}})
    spec['entries'].append({'name': NAME, 'path': folder.relative_to(ROOT).as_posix(), 'control': False,
                           'anchor': 'public552', 'hashes': manifest['hashes'], 'comparison_baseline': 'public552',
                           'native_decode_reference': 'public552', 'expected_equivalent_to': 'public552'})
    names = [r['name'] for r in spec['entries']]
    spec.update(native_encoder=True, native_encoder_references=['public552'], r26_expected_candidates=1,
                screen_orders=[names, names[::-1]], r18_function_profile=True,
                r15_profile_entry=NAME, r15_profile_functions=['parse', 'a_engine', 'a_find_all'],
                description='B21 actual U16 A-tree prefix consumption after B19/B20 exact originaltrajectory evidence. New128KiB initialization and full reads/writes are real; original28encoder bytes/tokens/decode vs public552 plus pure candidate coarse function profile. Parent proof draft, no total paired timing/gate/stable share claim.')
    deps = ['scripts/r26-b-build-tree-prefix.py', 'scripts/r26-b-preflight-draft.py',
            'evidence/round26/route-b/b21-tree-prefix-predeclared.md', spec['snapshot_pages']] + manifest['evidence']
    spec['r26_required_files'] = {p: sha((ROOT/p).read_bytes()) for p in deps}
    output = ROOT / 'evidence/round26/route-b/b21-tree-prefix-native.json'
    assert not output.exists()
    output.write_text(json.dumps(spec, indent=2) + '\n')
    print(json.dumps({'candidate': NAME, 'hashes': manifest['hashes'], 'draft': output.relative_to(ROOT).as_posix()}))


if __name__ == '__main__':
    main()
