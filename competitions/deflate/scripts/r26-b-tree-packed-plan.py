"""Freeze packed real encoder, complete production profile and query audit."""
from pathlib import Path
import hashlib
import importlib
import json
import sys

sys.dont_write_bytecode = True
ROOT = Path(__file__).resolve().parents[1]
NAME = 'r26-b-552-tree-packed'
CAPTURE = 'evidence/round26/extension4h/official-b23-live/pareto-pages.json'


def sha(raw):
    return hashlib.sha256(raw).hexdigest()


def main():
    folder = ROOT/'evidence/round26/route-b'
    out = folder/'b27-tree-packed-native.json'
    assert not out.exists()
    spec = json.loads((folder/'b21-tree-prefix-native.json').read_bytes())
    original = next(e for e in spec['entries'] if e['name']=='r26-b-552-tree-prefix')
    original.update(control=True)
    for key in ['comparison_baseline', 'native_decode_reference', 'expected_equivalent_to']:
        original.pop(key, None)
    candidate = {'name': NAME, 'path': 'candidates/'+NAME, 'control': False, 'anchor': 'public552',
                 'hashes': {f: sha((ROOT/'candidates'/NAME/f).read_bytes()) for f in ('parse.rs', 'Parse.lean')},
                 'comparison_baseline': 'public552', 'native_decode_reference': 'public552', 'expected_equivalent_to': 'public552'}
    spec['entries'].append(candidate)
    names = [e['name'] for e in spec['entries']]
    spec.update(snapshot_pages=CAPTURE, r15_profile_entry=NAME, r26_b_tree_packed_counts=True,
                native_encoder_references=['public552','r26-b-552-tree-prefix'], screen_orders=[names, names[::-1]],
                description='B27 fixed low26timestamp/high6prefix packed in originalkid, no newtable, original finder byte-preserved. Original28encoder vs552/U16, pure productionprofile and every helper oldprobe assertion; actual31-cap lost opportunities vsB20. Current29871, no assumed speed/gate/share.25min nativecap.')
    deps = ['scripts/r26-b-tree-packed-counts.py', 'scripts/r26-b-build-tree-packed.py', 'scripts/r26-b-tree-packed-model.py',
            'scripts/r26-b-tree-packed-plan.py', 'scripts/r26-b-preflight-draft.py', 'scripts/r26-b-tree-edge-model.py',
            'evidence/round26/route-b/b27-tree-packed-predeclared.md', 'evidence/round26/route-b/b27-tree-packed-finite-model.json',
            'evidence/round26/38216239816/tree-b20-native/diagnostics/r26-b-tree-edge/receipt.json', CAPTURE]
    spec['r26_required_files'] = {p: sha((ROOT/p).read_bytes()) for p in deps}
    check = importlib.import_module('r26-b-tree-packed-counts').preflight(spec)
    out.write_text(json.dumps(spec, indent=2)+'\n')
    pre = folder/'b27-tree-packed-structure-preflight.json'
    assert not pre.exists()
    pre.write_text(json.dumps(check, indent=2)+'\n')
    print(json.dumps({'draft': out.relative_to(ROOT).as_posix(), 'hashes': candidate['hashes'], **check}))


if __name__ == '__main__':
    main()
