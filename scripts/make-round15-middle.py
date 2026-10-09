"""Finish the checked 542-to-553 route transfer with a 32-bit PC hash."""
from pathlib import Path
import copy
import hashlib
import json

ROOT = Path(__file__).resolve().parents[1]

def save(path, value):
    path.write_bytes((json.dumps(value, indent=2) + '\n').encode())

def main():
    name = 'r15-553-compact-hash32'
    dest = ROOT / 'candidates' / name
    rust = (dest / 'parse.rs').read_text()
    old = '''    let k = (pc_be4(s, i) & km) as u64;
    (k.wrapping_mul(0x9E37_79B9_7F4A_7C15) >> (if H == 262144 {46u32} else if H == 131072 {47u32} else if H == 65536 {48u32} else {49u32})) as usize % H'''
    new = '''    let k = pc_be4(s, i) & km;
    (k.wrapping_mul(0x9E37_79B1) >> (if H == 262144 {14u32} else if H == 131072 {15u32} else if H == 65536 {16u32} else {17u32})) as usize % H'''
    assert rust.count(old) == 1 or rust.count(new) == 1
    rust = rust.replace(old, new)
    (dest / 'parse.rs').write_bytes(rust.encode())
    # The proof remains a draft until fresh extraction and the original gate.
    hashes = {f: hashlib.sha256((dest / f).read_bytes()).hexdigest() for f in ('parse.rs', 'Parse.lean')}
    reference = ROOT / 'references/round14-public-553'
    receipt = json.loads((reference / 'source-receipt.json').read_bytes())
    save(dest / 'manifest.json', {
        'candidate': name, 'parent': 'public553', 'formal_anchor_id': '553',
        'comparison_baseline': 'public553', 'hashes': hashes,
        'mechanism': 'Preserve every original553 route and table width; transfer PC-only U16 predecessor representation with original U32 PIM callees, then use the measured 32-bit multiplicative PC hash. The 18/17/16/15-bit table selectors use shifts14/15/16/17.',
        'attribution': {'source': 'Original public553; original542 and R13 private-PC lineage preserved', 'author_hotkey': receipt['submission']['hotkey'], 'reference': 'references/round14-public-553/source-receipt.json'},
        'route_transfer': 'evidence/round15/553-public-route-transfer.patch',
        'proof_status': 'DRAFT_UNCOMPILED_FOR_NEW_SOURCE', 'performance_status': 'UNKNOWN',
        'non_additivity': 'Previous542 representation and514 hash results do not establish a553 gain; own parent and same-source shadow required.',
        'formal_submission_sent': False,
    })
    ev = ROOT / 'evidence/round15'
    spec = json.loads((ev / 'tradeoff-b-native.json').read_bytes())
    keep = {'probe3', 'r3-432-fast3', 'public432', 'fast-shadow', 'public514'}
    entries = [copy.deepcopy(e) for e in spec['entries'] if e['name'] in keep]
    parent = {'name': 'public553', 'path': str(reference.relative_to(ROOT)).replace('\\', '/'), 'control': True, 'anchor': 'public553', 'formal_id': '553', 'hashes': {f: receipt['files'][f]['sha256'] for f in ('parse.rs', 'Parse.lean')}}
    entries.append(parent)
    shadow = copy.deepcopy(parent)
    shadow['name'] = 'public553-shadow'
    shadow.pop('formal_id')
    entries.append(shadow)
    entries.append({'name': name, 'path': f'candidates/{name}', 'control': False, 'anchor': 'public553', 'comparison_baseline': 'public553', 'native_decode_reference': 'public553', 'hashes': hashes})
    spec.update(entries=entries, native_encoder_references=['public553'], screen_orders=[[e['name'] for e in entries], [e['name'] for e in reversed(entries)]], description='R15 H: bounded transfer to the middle-frontier553 family. Current geometric grid suggests about0.5percent real speed improvement at unchanged size could yield1percent pool. First measure actual encoded size; original553 routing and authorship retained, and no cross-family performance addition.')
    save(ev / 'middle-h-native.json', spec)
    print(json.dumps({'candidate': name, 'hashes': hashes}))

if __name__ == '__main__':
    main()
