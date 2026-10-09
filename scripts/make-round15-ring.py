"""Bounded backward-cost storage experiment on the profiled high-end base."""
from pathlib import Path
import copy, hashlib, json

ROOT = Path(__file__).resolve().parents[1]

def function(text, name):
    a = text.index('pub fn ' + name + '(')
    b = text.index('{', a) + 1
    depth = 1
    while depth:
        if text[b] == '{': depth += 1
        elif text[b] == '}': depth -= 1
        b += 1
    return a, b, text[a:b]

def main():
    parent = ROOT / 'candidates/r15-550-base-only'
    rust = (parent / 'parse.rs').read_text()
    _, _, kernel = function(rust, 'Z307')
    kernel = kernel.replace('pub fn Z307(', 'pub fn r15_dp_ring(')
    reset = '''        let mut z = pe;
        while z < cl && z <= pe + 258 {
            cost[z] = 0;
            z += 1;
        }'''
    assert kernel.count(reset) == 1
    kernel = kernel.replace(reset, '        let mut ring = [0u32; 1024];')
    kernel = kernel.replace('            i -= 1;', '            i -= 1;\n            let at = i % 512;')
    assert kernel.count('cost[i + 1]') == 1 and kernel.count('cost[stop]') == 1
    kernel = kernel.replace('cost[i + 1]', 'ring[(i + 1) % 512]').replace('cost[stop]', 'ring[stop % 512]')
    assert kernel.count('Z314(cost, lc, i,') == 2
    kernel = kernel.replace('Z314(cost, lc, i,', 'r15_min_ring(&ring, lc, at,')
    old = '            cost[i] = ((best >> 9).wrapping_add(nxt)).wrapping_sub(1048576);'
    assert kernel.count(old) == 1
    kernel = kernel.replace(old, '''            let cv = ((best >> 9).wrapping_add(nxt)).wrapping_sub(1048576);
            ring[at] = cv;
            ring[at + 512] = cv;''')
    assert 'cost[' not in kernel
    minimum = '''#[inline(always)]
pub fn r15_min_ring(cost:&[u32;1024],lc:&[u32;512],at:usize,lo:usize,hi:usize,base:u32,width:usize)->u32 {
    if lo>hi || hi>=512 || at>=512 {return 4294967295;}
    let start=if width>=1 && hi-lo>=width {hi-width+1} else {lo};
    let mut l=start;
    let mut best=4294967295u32;
    while l<=hi {
        let c=(cost[at+l].wrapping_add(lc[l]).wrapping_add(base)<<9)|((l as u32)^511);
        best=if c<best {c} else {best};
        l+=1;
    }
    best
}
'''
    # Preserve the old kernel and its source/proof lineage. Only active callers
    # switch to the new bounded representation, so existing declarations remain.
    for name in ('Z308', 'Z309'):
        a, b, part = function(rust, name)
        assert part.count('Z307(') == 1
        rust = rust[:a] + part.replace('Z307(', 'r15_dp_ring(') + rust[b:]
    rust += '\n' + minimum + '\n' + kernel + '\n'
    name = 'r15-550-base-ring1024'
    dest = ROOT / 'candidates' / name; dest.mkdir(exist_ok=True)
    data = {'parse.rs': rust.encode(), 'Parse.lean': (parent / 'Parse.lean').read_bytes()}
    for f, raw in data.items():
        assert not (dest / f).exists() or (dest / f).read_bytes() == raw
        (dest / f).write_bytes(raw)
    hashes = {f: hashlib.sha256(raw).hexdigest() for f, raw in data.items()}
    manifest = {'candidate': name, 'parent': parent.name, 'formal_anchor_id': '550', 'comparison_baseline': parent.name, 'hashes': hashes,
        'attribution': json.loads((parent / 'manifest.json').read_bytes())['attribution'],
        'mechanism': 'A backward DP reads at most258future positions. Replace its large streamed cost writes with512live costs mirrored in1024slots, retaining contiguous length-range reads. Initialize all local slots to0 for each call, preserve every cost, match, tie and pass budget. Original large cost allocation is retained in this first isolated experiment.',
        'opportunity': 'L observes repeatedZ307 calls taking0.523s of2.495s native base time; model building is negligible. A distinct storage experiment after the range4 arithmetic attempt, not a new RMQ cache or planning pass.',
        'proof_status': 'DRAFT_ORIGINAL_PROOF_WITH_NEW_HELPER_LEMMAS_PENDING; fresh extraction required before proof completion',
        'performance_status': 'UNKNOWN', 'formal_submission_sent': False,
        'stop_condition': 'Any native token/output difference rejects the intended representation equivalence. Advance only with exact output and actual paired total-time improvement; confirmation and original gate still required.'}
    (dest / 'manifest.json').write_bytes((json.dumps(manifest, indent=2) + '\n').encode())
    ev = ROOT / 'evidence/round15'; spec = json.loads((ev / 'range-m-native.json').read_bytes())
    entries = [copy.deepcopy(e) for e in spec['entries'] if e['control']]
    entries.append({'name': name, 'path': f'candidates/{name}', 'control': False, 'anchor': 'public550', 'comparison_baseline': parent.name, 'hashes': hashes})
    spec.update(entries=entries, screen_orders=[[e['name'] for e in entries], [e['name'] for e in reversed(entries)]], description='R15 R: one bounded DP-cost representation. Local512slot mirrored buffer retains a258lookahead and contiguous range reads. First require exact frozen-parent tokens and encoded bytes on28files. Proof helpers are pending; this native-only batch does not establish total time,proof or private performance.')
    (ev / 'ring-r-native.json').write_bytes((json.dumps(spec, indent=2) + '\n').encode())
    print(json.dumps({'candidate': name, 'hashes': hashes}))

if __name__ == '__main__': main()
