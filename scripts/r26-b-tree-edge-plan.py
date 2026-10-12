"""Prepare one immutable original-path edge metadata diagnostic draft."""
from pathlib import Path
import hashlib
import importlib
import json
import sys

sys.dont_write_bytecode = True
ROOT = Path(__file__).resolve().parents[1]


def main():
    folder = ROOT / 'evidence/round26/route-b'
    output = folder / 'b19-tree-edge-native.json'
    assert not output.exists()
    base = json.loads((folder / 'overlap-b12-native.json').read_bytes())
    base.pop('r26_b_a_overlap_counts')
    base.pop('r26_required_files')
    base['r26_b_tree_edge_counts'] = True
    base['description'] = 'B19 original552 A-tree edge exact/lower-bound LCP metadata, original decisions preserved. Every inferred tuple checked against original a_probe; original28file token/decode parity, edge reads/writes/copy/window counts. No precompute matches, source-load deletion, candidate or performance/proof claim. All counters flush once per tree call. 15minute diagnostic cap.'
    deps = ['scripts/r26-b-tree-edge-diagnostic.py', 'scripts/r26-b-tree-edge-model.py',
            'scripts/r26-b-tree-edge-plan.py', 'scripts/r26-b-preflight-draft.py',
            'scripts/r26-b-fix-shared-cache.py', 'scripts/prepare-round24-extract-repro.py',
            'scripts/research-round13-counts.py',
            'evidence/round26/route-b/b19-edge-predeclared.md',
            'evidence/round26/route-b/b19-edge-finite-model.json', base['snapshot_pages']]
    base['r26_required_files'] = {p: hashlib.sha256((ROOT/p).read_bytes()).hexdigest() for p in deps}
    check = importlib.import_module('r26-b-tree-edge-diagnostic').preflight(base)
    output.write_text(json.dumps(base, indent=2) + '\n')
    proof = folder / 'b19-edge-structure-preflight.json'
    assert not proof.exists()
    proof.write_text(json.dumps(check, indent=2) + '\n')
    print(json.dumps({'draft': output.relative_to(ROOT).as_posix(), **check}))


if __name__ == '__main__':
    main()
