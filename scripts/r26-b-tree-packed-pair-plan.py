"""Prepare one packed/U16/public552 same-run total pair only after native parity."""
from pathlib import Path
import argparse
import hashlib
import json

ROOT = Path(__file__).resolve().parents[1]
NAME = 'r26-b-552-tree-packed'


def sha(raw):
    return hashlib.sha256(raw).hexdigest()


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument('--native-receipt', type=Path, required=True)
    ap.add_argument('--capture', type=Path, required=True)
    a = ap.parse_args()
    assert a.native_receipt.resolve().is_relative_to(ROOT/'evidence/round26')
    assert a.capture.resolve().is_relative_to(ROOT/'evidence/round26')
    data = json.loads(a.native_receipt.read_bytes())
    assert data['status'] == 'VERIFIED_FINITE_NATIVE_ORIGINAL_ENCODER_BYTES'
    rows = {r['candidate']: {} for r in data['rows']}
    for r in data['rows']:
        rows[r['candidate']][r['file']] = r
    assert len(rows[NAME]) == len(rows['public552']) == 28
    keys = ['input_sha256', 'tokens_sha256', 'output_sha256', 'output_bytes']
    assert all(all(r[k] == rows['public552'][file][k] for k in keys) for file, r in rows[NAME].items())
    source = ROOT/'evidence/round26/route-b/b23-tree-prefix-screen.json'
    spec = json.loads(source.read_bytes())
    spec['entries'] = [e for e in spec['entries'] if e['name']!='r26-b-552-tree-prefix-shadow']
    old = next(e for e in spec['entries'] if e['name']=='r26-b-552-tree-prefix')
    old.update(control=True)
    for key in ['comparison_baseline', 'native_decode_reference', 'expected_equivalent_to']:
        old.pop(key, None)
    hashes = {f: sha((ROOT/'candidates'/NAME/f).read_bytes()) for f in ('parse.rs', 'Parse.lean')}
    assert data['source_hashes'][NAME] == hashes
    spec['entries'] += [{'name': NAME, 'path': 'candidates/'+NAME, 'control': False, 'anchor': 'public552', 'hashes': hashes,
                        'comparison_baseline': 'public552', 'native_decode_reference': 'public552', 'expected_equivalent_to': 'public552'},
                       {'name': NAME+'-shadow', 'path': 'candidates/'+NAME, 'control': True, 'anchor': 'public552', 'hashes': hashes}]
    names = [e['name'] for e in spec['entries']]
    spec.update(snapshot_pages=a.capture.resolve().relative_to(ROOT).as_posix(), extract_candidates=[NAME],
                screen_orders=[names, names[::-1]],
                description='B29 exact fixed26/6 packedkid representation vs original552 and actualU16consumer in one fresh original11rep two-block screen, parent/packed same-source shadows. Native28tokens/output/decode parity prerequisite; exact extraction before timing. Full kid mask/rebase costs retained, no fullproof or stable share claim.')
    deps = ['scripts/r26-b-tree-packed-pair-plan.py', 'scripts/r26-b-preflight-draft.py',
            a.capture.resolve().relative_to(ROOT).as_posix(), a.native_receipt.resolve().relative_to(ROOT).as_posix(),
            'evidence/round26/route-b/b29-tree-packed-pair-predeclared.md']
    spec['r26_required_files'] = {p: sha((ROOT/p).read_bytes()) for p in deps}
    out = ROOT/'evidence/round26/route-b/b29-tree-packed-screen.json'
    assert not out.exists()
    out.write_text(json.dumps(spec, indent=2)+'\n')
    print(json.dumps({'draft': out.relative_to(ROOT).as_posix(), 'entries': len(names), 'blocks': 2, 'hashes': hashes}))


if __name__ == '__main__':
    main()
