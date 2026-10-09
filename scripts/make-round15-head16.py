"""One text-only capacity tradeoff on the previously gated 32-bit-hash parent."""
from pathlib import Path
import copy, hashlib, json
ROOT = Path(__file__).resolve().parents[1]

def main():
    parent = ROOT / 'candidates/r14-514-hash32'
    rust = (parent / 'parse.rs').read_text(); proof = (parent / 'Parse.lean').read_text()
    old = 'pub fn p125_row1(input:&[u8],out:&mut[u32])->usize{pc_run1c::<32768>(input,out,4,0,1000000,4294967295,1,4)}'
    assert rust.count(old) == 1
    rust = rust.replace(old, old.replace('::<32768>', '::<65536>'))
    old = '(k.wrapping_mul(0x9E37_79B1) >> (32 - pc_HB)) as usize % H'
    assert rust.count(old) == 1
    rust = rust.replace(old, '(k.wrapping_mul(0x9E37_79B1) >> (if H == 65536 {16u32} else {17u32})) as usize % H')
    old = '  rw [slot.pc_slot_of_m]\n  step*'
    assert proof.count(old) == 1
    proof = proof.replace(old, old + "\n  repeat' (split <;> step*)")
    name = 'r15-hash32-text-head16'; dest = ROOT / 'candidates' / name; dest.mkdir(exist_ok=True)
    data = {'parse.rs': rust.encode(), 'Parse.lean': proof.encode()}
    for f,raw in data.items():
        assert not (dest / f).exists() or (dest / f).read_bytes() == raw
        (dest / f).write_bytes(raw)
    hashes = {f: hashlib.sha256(v).hexdigest() for f,v in data.items()}
    m = {'candidate': name, 'parent': parent.name, 'formal_anchor_id': '514', 'comparison_baseline': parent.name, 'hashes': hashes,
        'attribution': json.loads((parent / 'manifest.json').read_bytes())['attribution'],
        'mechanism': 'Only text row1 head expands32768to65536 with one additional hash bit. Binary and every other original32768table keep their old17-bit shift; the32768predecessor window, chain depth, routes, key widths and emission are unchanged.',
        'difference_from_old_work': 'R14 shrinking a different64-bit-hash parent tohead14 increased output8355B and was slower; that is negative evidence for that shrink, not a measured expansion result. This bounded inverse capacity tradeoff starts from the gated32-bit parent and needs real byte/time feedback. No depth or gain combination.',
        'proof_status': 'DRAFT_UNCOMPILED_FOR_NEW_RUST; generic hash branch proof split added', 'performance_status': 'UNKNOWN', 'formal_submission_sent': False,
        'stop_condition': 'No automatic width sweep. Stop if actual bytes or paired total time fail to provide a viable single-candidate1percent region; original gate only after frozen fresh confirmation.'}
    (dest / 'manifest.json').write_bytes((json.dumps(m, indent=2) + '\n').encode())
    ev = ROOT / 'evidence/round15'; s = json.loads((ev / 'tradeoff-b-native.json').read_bytes())
    entries = [copy.deepcopy(e) for e in s['entries'] if e['control']]
    entries.append({'name': name, 'path': f'candidates/{name}', 'control': False, 'anchor': 'public514', 'comparison_baseline': parent.name, 'native_decode_reference': parent.name, 'hashes': hashes})
    s.update(entries=entries, snapshot_pages='evidence/round15/official-confirmation/pareto-pages.json', screen_orders=[[e['name'] for e in entries], [e['name'] for e in reversed(entries)]], description='R15 V: one remaining bounded capacity mechanism before10:36freeze. Text-only head16 from gatedhash32, other paths unchanged; real output first, no assumed inverse ofhead14 loss and no automatic width sweep.')
    (ev / 'head-v-native.json').write_bytes((json.dumps(s, indent=2) + '\n').encode()); print(json.dumps({'candidate': name, 'hashes': hashes}))

if __name__ == '__main__': main()
