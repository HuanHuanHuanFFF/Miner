"""Combine only the two measured incremental quality mechanisms on depth3."""
from pathlib import Path
import copy, hashlib, json

ROOT = Path(__file__).resolve().parents[1]

def main():
    name = 'r15-hash32-depth3-gain'
    parent = ROOT / 'candidates/r15-hash32-chain-depth3'
    rust = (parent / 'parse.rs').read_text()
    a = rust.index('pub fn pc_f_try(')
    b = rust.index('pub fn pc_f_deepen(', a)
    part = rust[a:b]
    old = 'if m > l && m >= minl {'
    assert part.count(old) == 1
    code = rust[:a] + part.replace(old, 'if m > l && m >= minl && pc_gain(m, d2) > pc_gain(l, d) {') + rust[b:]
    data = {'parse.rs': code.encode(), 'Parse.lean': (parent / 'Parse.lean').read_bytes()}
    dest = ROOT / 'candidates' / name
    dest.mkdir(exist_ok=True)
    for f, raw in data.items():
        assert not (dest / f).exists() or (dest / f).read_bytes() == raw
        (dest / f).write_bytes(raw)
    hashes = {f: hashlib.sha256(raw).hexdigest() for f, raw in data.items()}
    manifest = {'candidate': name, 'parent': parent.name, 'formal_anchor_id': '514', 'comparison_baseline': parent.name, 'hashes': hashes,
        'mechanism': 'Third real predecessor plus length/distance gain acceptance; no artificial work or timing delay.',
        'evidence_for_combination': 'G original encoder measured depth3 another11798B below depth2 and depth2+gain another1792B below depth2. Depth3 projected size36.514586 is close to555 size36.514473; actual additional quality could widen the viable region. Combined bytes/time are independently measured; gains are not added.',
        'attribution': json.loads((parent / 'manifest.json').read_bytes())['attribution'],
        'proof_status': 'DRAFT_UNCOMPILED_FOR_NEW_RUST', 'performance_status': 'UNKNOWN', 'formal_submission_sent': False}
    (dest / 'manifest.json').write_bytes((json.dumps(manifest, indent=2) + '\n').encode())
    ev = ROOT / 'evidence/round15'
    spec = json.loads((ev / 'deeper-g-native.json').read_bytes())
    keep = {'probe3', 'r3-432-fast3', 'public432', 'fast-shadow', 'public514', 'public514-shadow'}
    entries = [copy.deepcopy(e) for e in spec['entries'] if e['name'] in keep]
    pe = copy.deepcopy(next(e for e in spec['entries'] if e['name'] == parent.name))
    pe['control'] = True
    pe.pop('native_decode_reference', None)
    entries.append(pe)
    entries.append({'name': name, 'path': f'candidates/{name}', 'control': False, 'anchor': 'public514', 'comparison_baseline': parent.name, 'native_decode_reference': parent.name, 'hashes': hashes})
    spec.update(entries=entries, native_encoder_references=[parent.name], snapshot_pages='evidence/round15/official-checkpoint/pareto-pages.json', screen_orders=[[e['name'] for e in entries], [e['name'] for e in reversed(entries)]], description='R15 O: one measured-mechanism composition to improve the depth3 real compression tradeoff. Exact output first; independent paired total time and frozen share confirmation remain necessary. No automatic deeper-level sweep.')
    (ev / 'deep-o-native.json').write_bytes((json.dumps(spec, indent=2) + '\n').encode())
    print(json.dumps({'candidate': name, 'hashes': hashes}))

if __name__ == '__main__':
    main()
