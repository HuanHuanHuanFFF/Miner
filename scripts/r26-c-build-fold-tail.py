"""C2: necessary last-byte reject before U118's whole-token backward scan."""
from pathlib import Path
import hashlib
import json

ROOT = Path(__file__).resolve().parents[1]
BASE = ROOT / 'references/round26-public-658'
OUT = ROOT / 'evidence/round26/extension1h/route-c'
NAME = 'r26-c-658-fold-tail'
RUST = '1185749453a5abe100106f2e15082eca84521292b7233784a9c2f4562367f3ad'
LEAN = '354d56aa9f58536efdb410f3d5ecdf1945bded607965fe8a48161f96b035c494'
OLD = 'l + w <= 258 && w <= p && d <= p - w && u118_same(input, p - w - d, p - w, w) == 1'
NEW = 'l + w <= 258 && w <= p && d <= p - w && input[p - 1] == input[p - 1 - d] && u118_same(input, p - w - d, p - w, w) == 1'

def sha(b): return hashlib.sha256(b).hexdigest()
def dump(p, obj): p.write_bytes((json.dumps(obj, indent=2, ensure_ascii=False) + '\n').encode())

def source():
    raw = (BASE/'parse.rs').read_bytes()
    assert sha(raw) == RUST
    text = raw.decode()
    assert text.count(OLD) == 1
    return text.replace(OLD, NEW, 1).encode()

def main():
    OUT.mkdir(parents=True, exist_ok=True)
    target = ROOT/'candidates'/NAME
    assert not target.exists(), target
    target.mkdir()
    raw = source(); lean = (BASE/'Parse.lean').read_bytes()
    assert sha(lean) == LEAN
    (target/'parse.rs').write_bytes(raw)
    (target/'Parse.lean').write_bytes(lean)
    hashes = {'parse.rs': sha(raw), 'Parse.lean': sha(lean)}
    dump(target/'manifest.json', {
        'candidate': NAME, 'parent': 'references/round26-public-658', 'hashes': hashes,
        'attribution': {'source_receipt': 'references/round26-public-658/source-receipt.json',
                        'author_hotkey': '5G3YLL7PuDhRBoVoDBYKhAfTxFM4EouSDiYuFXeeWciNRzyK',
                        'ownership': 'Derivative of public658; published ancestry and all parent comments retained.'},
        'mechanism': 'Only U118 whole-token backward fold: after all original range guards, reject a previous match whose last byte fails at current distance, before scanning that entire previous token from its beginning. Tail-pass still executes original u118_same.',
        'difference': 'PC already has fold_w prefilter; U118 does not. Not A18 forward best-window filtering, not R20 removal of fold, not a same-distance cache. No new table, retained state, search parameter, route, encoder, or timing change.',
        'equivalence': 'INFERRED from necessity of the final-byte equality for every successful original same; requires actual native and complete gate.',
        'guard_safety': 'Original loop has d<p, p<=input length from valid parse; guarded w>=3 and d<=p-w imply p>=w>=3 and p-1-d is valid. All original bounds and same fallback retained.',
        'proof_status': 'DRAFT_PARENT_SCAFFOLD_ONLY. Parent Lean copied unchanged. Exact extraction, Lean build, original obligations, axiom whitelist and full gate NOT_RUN. Existing BackInv.match remains relevant on success; new failure path uses existing part_merge_spec. No equivalence or gate claim.',
        'performance': 'UNKNOWN. Count avoided actual original scans and added endpoint checks; meaningful coverage only earns original-protocol timing.',
        'formal_submission_sent': False
    })
    entry = {'name': NAME, 'path': target.relative_to(ROOT).as_posix(), 'control': False,
             'anchor': 'public658', 'comparison_baseline': 'public658',
             'native_decode_reference': 'public658', 'expected_equivalent_to': 'public658', 'hashes': hashes}
    dump(OUT/'c2-entry.json', entry)
    dump(OUT/'c2-build.json', {'status': 'VERIFIED_ONE_GUARD_SOURCE_PATCH_NOT_COMPILED',
                            'parent_rust_sha256': RUST, 'hashes': hashes,
                            'rust_bytes': len(raw), 'lean_bytes': len(lean),
                            'lean_spare_bytes': 524288-len(lean), 'changed_guard_count': 1,
                            'native': 'NOT_RUN', 'full_gate': 'NOT_RUN'})
    print(json.dumps(entry, indent=2))

if __name__ == '__main__': main()
