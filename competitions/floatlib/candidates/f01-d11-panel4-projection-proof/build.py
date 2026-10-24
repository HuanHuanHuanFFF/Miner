"""Unused exact-F4 projection diagnostic. No active entry is changed.
Dry run by default. --write creates once; --verify reads only. No Lean/Git/CI.
"""
from argparse import ArgumentParser
from datetime import datetime, timezone
from hashlib import sha256
from pathlib import Path
from types import SimpleNamespace
import ast, importlib.util, json, re, sys

HERE = Path(__file__).resolve().parent
ROOT = HERE.parents[3]
R11 = HERE.parent / 'f01-d7-research/round7h-20261023T193125Z'
PARENT = HERE.parent / 'f01-d11-panel4-codegen-probe/Kernel.lean'
PARENT_SHA = '9a40118eae28c92c1abeca7f6a141fb0fbfe963cbf40321681b8013782f9f7ac'
OLD_BUILDER = HERE.parent / 'f01-d11-panel4-tail-proof/build.py'
OLD_BUILDER_SHA = 'ca9e0c37a66a01487b0da83419ea881bf209e9177853a764fd57f94309eef70b'
DONORS = [
    ('astra-panel4-projectRow-required.lean', '42f9f17550cb68ec5f43db0ac97931d648bf8bbe634a98cf801d9998b3515607'),
    ('astra-panel4-loop-projection.lean', 'cf1110a49df7eedc9b533dc0699c92b4c8d7c484e001f5d7ed60fc1abb0b650c'),
]


def sha(raw):
    return sha256(raw).hexdigest()


def construct():
    parent = PARENT.read_bytes()
    assert sha(parent) == PARENT_SHA and len(parent) == 229218
    pieces, lineage = [], []
    for name, expected in DONORS:
        raw = (R11 / name).read_bytes()
        assert sha(raw) == expected and raw.endswith(b'\n')
        pieces.append(raw)
        lineage.append({'path': (R11 / name).relative_to(ROOT).as_posix(),
                        'sha256': expected, 'bytes': len(raw)})
    original_asset = b''.join(pieces)
    before = b'  unfold Panel4.block\n  dsimp only\n  rw [Packed10.vector_get_ofFn, runDot_row]\n'
    after = b'  simp only [Panel4.block, Packed10.vector_get_ofFn, runDot_row]\n'
    assert original_asset.count(before) == 1
    asset = original_asset.replace(before, after)
    data = parent + asset
    assert len(data) <= 256000 and data[:-len(asset)] == parent

    assert sha(OLD_BUILDER.read_bytes()) == OLD_BUILDER_SHA
    sys.dont_write_bytecode = True
    spec = importlib.util.spec_from_file_location('frozen_tail_static_helpers', OLD_BUILDER)
    old = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(old)
    parser = old.PARSER.read_bytes()
    assert sha(parser) == '58662bf7218de54978d999bfb424975732cf845708869e1d611dd712d7470f22'
    inv = old.functions(parser, ['strip_comments', 'declarations'], {'re': re})
    a, b = [inv['declarations'](raw.decode()) for raw in (parent, data)]
    assert set(a) <= set(b) and all(len(v) == 1 for v in b.values())
    added = set(b) - set(a)
    expected = {'Submission.R11WideRows4.projectRow'} | {
        'Submission.Panel4Bridge.' + n for n in
        ['laneA', 'baseFor', 'packA_read', 'wordLoop_row', 'runDot_row', 'block_row', 'baseFor_rows']}
    assert added == expected
    gate = old.GATE.read_bytes()
    assert sha(gate) == '1eb74ef7479b0023c721e776cc5e4073af21c6662b4afffcf16a48a124d27194'
    tree = ast.parse(gate.decode())
    assign = {t.id: n.value for n in tree.body if isinstance(n, ast.Assign)
              for t in n.targets if isinstance(t, ast.Name)}
    env = {'re': re, 'Path': Path, 'Verdict': object,
           'SLOTS': {'full': SimpleNamespace(contract='ContractTensor')},
           'OPTIONS': ast.literal_eval(assign['OPTIONS']),
           'ATTRIBUTES': ast.literal_eval(assign['ATTRIBUTES']),
           'BANNED': re.compile(ast.literal_eval(assign['BANNED'].args[0]))}
    env = old.functions(gate, ['policy', 'options'], env)
    assert env['policy'](SimpleNamespace(read_text=lambda: data.decode()), SimpleNamespace(slot='full')) is None
    receipt = {
        'candidate': HERE.name, 'candidate_sha256': sha(data), 'candidate_bytes': len(data),
        'headroom_bytes': 256000 - len(data), 'parent_sha256': PARENT_SHA, 'parent_bytes': len(parent),
        'asset_sha256': sha(asset), 'asset_bytes': len(asset), 'builder_sha256': sha(Path(__file__).read_bytes()),
        'donors': lineage, 'added_declarations': sorted(added),
        'checks': {'exact9a_active_prefix_and_all_four_specs_unchanged': 'PASS',
                   'exact_inverse_to9a': 'PASS', 'original_policy': 'PASS', 'unique_declarations': 'PASS',
                   'single_existing40_chain_no_new_numeric_loop': 'PASS',
                   'parent_author_notices_and_resource_options': 'UNCHANGED'},
        'validation_mode': 'STATEMENT_DIAGNOSTIC', 'statement': 'NOT_RUN', 'kernel_replay': 'NOT_RUN',
        'axiom_audit': 'NOT_RUN', 'checksum': 'NOT_RUN', 'full_gate': 'NOT_RUN',
        'matrix_algorithm_acceptance': 'NOT_APPLICABLE_NO_ACTIVE_PANEL_ENTRY',
        'performance': 'NOT_APPLICABLE_UNUSED_PROJECTION_ASSET', 'formal_submission': 'NOT_SUBMITTED'}
    inverse = {'parent_sha256': PARENT_SHA, 'candidate_sha256': sha(data),
               'append_offset': len(parent), 'appended_text': asset.decode(), 'appended_sha256': sha(asset),
               'inverse_recovers_exact_parent': data[:len(parent)] == parent,
               'donor_proof_only_patch': {'before': before.decode(), 'after': after.decode(),
                   'original_concatenated_asset_sha256': sha(original_asset),
                   'inverse_recovers_exact_donors': asset.replace(after, before) == original_asset}}
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
        assert (HERE / 'panel4-projection.lean').read_bytes() == asset
        assert (R11 / 'review-output-panel4-projection.lean').read_bytes() == asset
    elif args.write:
        names = ['Kernel.lean', 'panel4-projection.lean', 'manifest.json', 'static-checks.json', 'exact-inverse.json']
        assert not any((HERE / name).exists() for name in names), 'Refuse overwrite'
        assert not (R11 / 'review-output-panel4-projection.lean').exists(), 'Refuse overwrite'
        (HERE / 'Kernel.lean').write_bytes(data)
        (HERE / 'panel4-projection.lean').write_bytes(asset)
        (R11 / 'review-output-panel4-projection.lean').write_bytes(asset)
        manifest = dict(receipt, candidate_file='Kernel.lean', parent='f01-d11-panel4-codegen-probe',
            created_at_utc=datetime.now(timezone.utc).isoformat(), ci_owner='root',
            attribution='Astra authored the two exact NOT_RUN donor assets; this diagnostic binds required projectRow and normalizes only block_row proof simplification.',
            mechanism='Exact VectorF4 reading, arbitrary40-accumulator row recurrence to Packed10.dot10, concrete packA and block row equalities to Packed10Index.runDot. No new active entry.',
            missing='No concrete Projects instance, generalPanel output/tail dispatch, hugeNat fallback integration, lifecycle verification or full acceptance/performance.')
        for name, obj in [('manifest.json', manifest), ('static-checks.json', receipt), ('exact-inverse.json', inverse)]:
            (HERE / name).write_bytes((json.dumps(obj, ensure_ascii=False, indent=2) + '\n').encode())
    print(json.dumps(receipt, ensure_ascii=False, indent=2))


if __name__ == '__main__':
    main()
