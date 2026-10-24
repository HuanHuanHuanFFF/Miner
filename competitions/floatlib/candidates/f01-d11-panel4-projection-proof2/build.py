"""Single proof-tactic deletion from frozen ec112. No runtime changes.
Dry run by default. --write creates once; --verify reads only. No Lean/Git/CI.
"""
from argparse import ArgumentParser
from datetime import datetime, timezone
from hashlib import sha256
from pathlib import Path
from types import SimpleNamespace
import ast, importlib.util, json, re, sys

HERE = Path(__file__).resolve().parent
OLD = HERE.parent / 'f01-d11-panel4-projection-proof'
PARENT_SHA = 'ec11262306db740f79a51af22a13230963fdc9ac9e77a99e45fcb9a07dfe7d4e'
BUILDER_SHA = 'b75c4405c66234695e7a6e6081a0d557c972fe9f5d1d8d5da28cebc0c68c448e'
LOG = HERE.parent / 'f01-mul-log2-proof1/ci-runs/40049985877/download-b9f28e83c1b945279ccbff8b9b41c63a/diagnostics/f01-d7-public-suite/public-suite/diagnostics/f01-d11-panel4-projection-proof/replay.log'


def sha(raw):
    return sha256(raw).hexdigest()


def construct():
    assert sha((OLD / 'build.py').read_bytes()) == BUILDER_SHA
    sys.dont_write_bytecode = True
    spec = importlib.util.spec_from_file_location('frozen_ec112_constructor', OLD / 'build.py')
    old = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(old)
    reproduced, original_asset, prior, _ = old.construct()
    parent = (OLD / 'Kernel.lean').read_bytes()
    assert parent == reproduced and sha(parent) == PARENT_SHA
    before = b'    rw [Packed10.dot10, dif_neg hkn]\n    rfl\ntermination_by count.toNat-k.toNat\n'
    after = b'    rw [Packed10.dot10, dif_neg hkn]\ntermination_by count.toNat-k.toNat\n'
    assert parent.count(before) == 1
    offset = parent.index(before)
    assert offset >= 229218
    data = parent.replace(before, after)
    assert len(data) == len(parent) - 8 and data[:229218] == parent[:229218]
    assert data.count(after) == 1 and data.replace(after, before) == parent
    asset = data[229218:]
    assert asset.replace(after, before) == original_asset
    helpers_spec = importlib.util.spec_from_file_location('pinned_f767_helpers', old.OLD_BUILDER)
    helpers = importlib.util.module_from_spec(helpers_spec)
    helpers_spec.loader.exec_module(helpers)
    parser = helpers.functions(helpers.PARSER.read_bytes(), ['strip_comments', 'declarations'], {'re': re})
    a, b = [parser['declarations'](x.decode()) for x in (parent, data)]
    assert {k: len(v) for k, v in a.items()} == {k: len(v) for k, v in b.items()}
    gate = helpers.GATE.read_bytes()
    tree = ast.parse(gate.decode())
    assign = {t.id: n.value for n in tree.body if isinstance(n, ast.Assign)
              for t in n.targets if isinstance(t, ast.Name)}
    env = {'re': re, 'Path': Path, 'Verdict': object,
           'SLOTS': {'full': SimpleNamespace(contract='ContractTensor')},
           'OPTIONS': ast.literal_eval(assign['OPTIONS']),
           'ATTRIBUTES': ast.literal_eval(assign['ATTRIBUTES']),
           'BANNED': re.compile(ast.literal_eval(assign['BANNED'].args[0]))}
    env = helpers.functions(gate, ['policy', 'options'], env)
    assert env['policy'](SimpleNamespace(read_text=lambda: data.decode()), SimpleNamespace(slot='full')) is None
    receipt = dict(prior, candidate=HERE.name, candidate_sha256=sha(data), candidate_bytes=len(data),
        headroom_bytes=256000-len(data), parent_sha256=PARENT_SHA, parent_bytes=len(parent),
        asset_sha256=sha(asset), asset_bytes=len(asset), builder_sha256=sha(Path(__file__).read_bytes()),
        failed936_log_sha256=sha(LOG.read_bytes()))
    receipt['checks'] = dict(prior['checks'], exactly_one_redundant_rfl_deleted='PASS',
        exact_inverse_to_ec112='PASS', full9a_runtime_prefix_and_all_eight_new_declarations='UNCHANGED',
        resource_options_and_original_donors='UNCHANGED')
    inverse = {'parent_sha256': PARENT_SHA, 'candidate_sha256': sha(data), 'offset': offset,
        'before': before.decode(), 'after': after.decode(), 'before_sha256': sha(before),
        'after_sha256': sha(after), 'inverse_recovers_exact_ec112': data.replace(after, before) == parent}
    return data, asset, receipt, inverse


def main():
    ap = ArgumentParser()
    mode = ap.add_mutually_exclusive_group()
    mode.add_argument('--write', action='store_true')
    mode.add_argument('--verify', action='store_true')
    args = ap.parse_args()
    data, asset, receipt, inverse = construct()
    if args.verify:
        assert (HERE / 'Kernel.lean').read_bytes() == data
        assert (HERE / 'panel4-projection-proof2.lean').read_bytes() == asset
    elif args.write:
        names = ['Kernel.lean', 'panel4-projection-proof2.lean', 'manifest.json', 'static-checks.json', 'exact-inverse.json']
        assert not any((HERE / n).exists() for n in names), 'Refuse overwrite'
        (HERE / 'Kernel.lean').write_bytes(data)
        (HERE / 'panel4-projection-proof2.lean').write_bytes(asset)
        manifest = dict(receipt, candidate_file='Kernel.lean', created_at_utc=datetime.now(timezone.utc).isoformat(),
            parent='f01-d11-panel4-projection-proof', ci_owner='root',
            repair='Delete only redundant rfl after terminal-branch rewrite in wordLoop_row; all runtime and theorem statements identical.',
            trigger='936/run40049985877 source ec112:6258 No goals to be solved. Exact failed source and donors preserved.',
            missing='No concrete Projects/active Panel output-tail dispatch, full gate, kernel replay, axiom audit, checksum or Panel performance acceptance.')
        for name, obj in [('manifest.json', manifest), ('static-checks.json', receipt), ('exact-inverse.json', inverse)]:
            (HERE / name).write_bytes((json.dumps(obj, ensure_ascii=False, indent=2)+'\n').encode())
    print(json.dumps(receipt, ensure_ascii=False, indent=2))


if __name__ == '__main__':
    main()
