"""Freeze exact official-settings checked A increment lowering discriminator."""
from pathlib import Path
import hashlib
import importlib
import json
import sys

sys.dont_write_bytecode = True
ROOT = Path(__file__).resolve().parents[1]


def main():
    folder = ROOT/'evidence/round26/route-b'
    out = folder/'b25-checked-lowering-native.json'
    assert not out.exists()
    spec = json.loads((folder/'b22-a-compiler-native.json').read_bytes())
    spec['r26_b_a_compiler_module'] = 'r26-b-a-checked-lowering'
    spec['description'] = 'B25 official copied cdylib shim/release flags on original552 versus only two dominated safe wrapping A-loop increments, real LLVM/assembly discriminator. No candidate parse/encoder execution yet. Keep raw generated source/shim/commands/hash and relevant loop bodies; neither scalar/vector conclusion is speed.15min cap.'
    deps = ['scripts/r26-b-a-checked-lowering.py', 'scripts/r26-b-a-checked-plan.py',
            'scripts/r26-b-preflight-draft.py', 'scripts/r26-b-fix-shared-cache.py',
            'scripts/prepare-round24-extract-repro.py', 'evidence/round26/route-b/b25-checked-lowering-predeclared.md',
            'evidence/round26/route-b/b25-official-template/Cargo.toml',
            'evidence/round26/route-b/b25-official-template/lib.rs',
            'evidence/round26/route-b/b25-official-template/receipt.json',
            spec['snapshot_pages'], 'evidence/round26/38217519276/compiler-b22-native/diagnostics/r26-b-a-compiler/receipt.json']
    spec['r26_required_files'] = {p: hashlib.sha256((ROOT/p).read_bytes()).hexdigest() for p in deps}
    result = importlib.import_module('r26-b-a-checked-lowering').preflight(spec)
    out.write_text(json.dumps(spec, indent=2)+'\n')
    pre = folder/'b25-checked-lowering-structure-preflight.json'
    assert not pre.exists()
    pre.write_text(json.dumps(result, indent=2)+'\n')
    print(json.dumps({'draft': out.relative_to(ROOT).as_posix(), **result}))


if __name__ == '__main__':
    main()
