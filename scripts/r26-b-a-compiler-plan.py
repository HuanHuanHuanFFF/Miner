"""Freeze one current A reduction/compiler observation draft."""
from pathlib import Path
import hashlib
import importlib
import json
import sys

sys.dont_write_bytecode = True
ROOT = Path(__file__).resolve().parents[1]


def main():
    folder = ROOT/'evidence/round26/route-b'
    out = folder/'b22-a-compiler-native.json'
    assert not out.exists()
    spec = json.loads((folder/'b19-tree-edge-native.json').read_bytes())
    spec.pop('r26_b_tree_edge_counts')
    spec.pop('r26_required_files')
    spec['r26_b_a_compiler_counts'] = True
    spec['description'] = 'B22 current original552 A packed reduction widths on actual original28 trajectory plus unmodified O3/default-target lib LLVM/assembly. No DP candidate/state/price/output writes changed. Counts/IR only, not benchmark machine-code identity or whole encoder speed. 20min diagnostic cap.'
    deps = ['scripts/r26-b-a-compiler-diagnostic.py', 'scripts/r26-b-a-compiler-plan.py',
            'scripts/r26-b-preflight-draft.py', 'scripts/r26-b-fix-shared-cache.py',
            'scripts/prepare-round24-extract-repro.py', 'scripts/research-round13-counts.py',
            'evidence/round26/route-b/b22-a-compiler-predeclared.md', spec['snapshot_pages']]
    spec['r26_required_files'] = {p: hashlib.sha256((ROOT/p).read_bytes()).hexdigest() for p in deps}
    result = importlib.import_module('r26-b-a-compiler-diagnostic').preflight(spec)
    out.write_text(json.dumps(spec, indent=2)+'\n')
    check = folder/'b22-a-compiler-structure-preflight.json'
    assert not check.exists()
    check.write_text(json.dumps(result, indent=2)+'\n')
    print(json.dumps({'draft': out.relative_to(ROOT).as_posix(), **result}))


if __name__ == '__main__':
    main()
