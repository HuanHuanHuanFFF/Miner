"""One same-result four-lane minimum reduction on the profiled high-end base."""
from pathlib import Path
import copy
import hashlib
import json

ROOT = Path(__file__).resolve().parents[1]

def save(p, value):
    p.write_bytes((json.dumps(value, indent=2) + '\n').encode())

def main():
    parent = ROOT / 'candidates/r15-550-base-only'
    rust = (parent / 'parse.rs').read_text()
    a = rust.index('pub fn Z314(')
    b = rust.index('\n}', a) + 2
    before = rust[a:b]
    old = '''    while l<=hi {
        let c=(cost[i+l].wrapping_add(lc[l]).wrapping_add(base)<<9)|((l as u32)^511);
        best=if c<best {c} else {best};
        l+=1;
    }'''
    new = '''    while l<=hi {
        if hi-l>=3 {
            let c0=(cost[i+l].wrapping_add(lc[l]).wrapping_add(base)<<9)|((l as u32)^511);
            let c1=(cost[i+l+1].wrapping_add(lc[l+1]).wrapping_add(base)<<9)|(((l+1) as u32)^511);
            let c2=(cost[i+l+2].wrapping_add(lc[l+2]).wrapping_add(base)<<9)|(((l+2) as u32)^511);
            let c3=(cost[i+l+3].wrapping_add(lc[l+3]).wrapping_add(base)<<9)|(((l+3) as u32)^511);
            let c01=if c0<c1 {c0} else {c1};
            let c23=if c2<c3 {c2} else {c3};
            let c=if c01<c23 {c01} else {c23};
            best=if c<best {c} else {best};
            l+=4;
        } else {
            let c=(cost[i+l].wrapping_add(lc[l]).wrapping_add(base)<<9)|((l as u32)^511);
            best=if c<best {c} else {best};
            l+=1;
        }
    }'''
    assert before.count(old) == 1
    name = 'r15-550-base-range4'
    data = {'parse.rs': (rust[:a] + before.replace(old, new) + rust[b:]).encode(), 'Parse.lean': (parent / 'Parse.lean').read_bytes()}
    dest = ROOT / 'candidates' / name
    dest.mkdir(exist_ok=True)
    for f, raw in data.items():
        assert not (dest / f).exists() or (dest / f).read_bytes() == raw
        (dest / f).write_bytes(raw)
    hashes = {f: hashlib.sha256(raw).hexdigest() for f, raw in data.items()}
    save(dest / 'manifest.json', {
        'candidate': name, 'parent': parent.name, 'formal_anchor_id': '550', 'comparison_baseline': parent.name,
        'hashes': hashes, 'attribution': json.loads((parent / 'manifest.json').read_bytes())['attribution'],
        'mechanism': 'Z314 retains the same valid length range and exact wrapping cost/tie encoding, but reduces four independent costs through a balanced minimum tree per iteration. No changed match set, price or iteration budget.',
        'opportunity': 'J profile locates30percent of base cost in Z312 and16percent in Z318; both use repeated Z307 planning and Z314 scans. L diagnostic separates the actual matching/planning/model costs. Base-only already measured18.586percent total reduction but0.7755percent conditional pool.',
        'stop_condition': 'Any changed public token/output rejects the intended same-output mechanism. No total-time improvement or failure to reach target closes this exact source; no automatic unroll-factor sweep.',
        'proof_status': 'DRAFT_UNCOMPILED_FOR_CHANGED_LOOP_BODY', 'performance_status': 'UNKNOWN', 'formal_submission_sent': False,
    })
    ev = ROOT / 'evidence/round15'
    spec = json.loads((ev / 'high-e-native.json').read_bytes())
    entries = [e for e in spec['entries'] if e['control']]
    base = copy.deepcopy(next(e for e in spec['entries'] if e['name'] == parent.name))
    base['control'] = True
    base.pop('native_decode_reference', None)
    entries.append(base)
    entries.append({'name': name, 'path': f'candidates/{name}', 'control': False, 'anchor': 'public550', 'comparison_baseline': parent.name, 'hashes': hashes})
    spec.update(entries=entries, native_encoder_references=[parent.name], snapshot_pages='evidence/round15/official-checkpoint/pareto-pages.json', screen_orders=[[e['name'] for e in entries], [e['name'] for e in reversed(entries)]], description='R15 M: one four-lane reduction in a genuine repeated length-cost scan. Public tokens/output must match exact base-only. Native measurement establishes equality and decode only; later original paired total-time measurements decide value.')
    save(ev / 'range-m-native.json', spec)
    print(json.dumps({'candidate': name, 'hashes': hashes}))

if __name__ == '__main__':
    main()
