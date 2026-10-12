"""Freeze B20 exact prefix seed diagnostic after B19 real coverage."""
from pathlib import Path
import hashlib
import importlib
import json
import sys

sys.dont_write_bytecode = True
ROOT = Path(__file__).resolve().parents[1]


def main():
    folder = ROOT / 'evidence/round26/route-b'
    output = folder / 'b20-tree-seed-native.json'
    assert not output.exists()
    spec = json.loads((folder / 'b19-tree-edge-native.json').read_bytes())
    spec['r26_b_tree_edge_module'] = 'r26-b-tree-seed-diagnostic'
    spec['description'] = 'B20 B19 exact active-tree metadata plus valid-prefix seed raised on remaining probes. Original decisions untouched; raised probe length/direction checked, cap258 unused-direction differences retained. Original28token/decode parity and combined wordpair opportunity vs metadata maintenance only. No candidate or speed/proof claim,15minute diagnostic cap.'
    deps = list(spec['r26_required_files']) + ['scripts/r26-b-tree-seed-diagnostic.py', 'scripts/r26-b-tree-seed-model.py',
              'scripts/r26-b-tree-seed-plan.py', 'evidence/round26/route-b/b20-seed-finite-model.json',
              'evidence/round26/route-b/b20-seed-predeclared.md',
              'evidence/round26/38215726866/tree-b19-native/diagnostics/r26-b-tree-edge/receipt.json']
    spec['r26_required_files'] = {p: hashlib.sha256((ROOT/p).read_bytes()).hexdigest() for p in deps}
    check = importlib.import_module('r26-b-tree-seed-diagnostic').preflight(spec)
    output.write_text(json.dumps(spec, indent=2) + '\n')
    record = folder / 'b20-seed-structure-preflight.json'
    assert not record.exists()
    record.write_text(json.dumps(check, indent=2)+'\n')
    print(json.dumps({'draft': output.relative_to(ROOT).as_posix(), **check}))


if __name__ == '__main__':
    main()
