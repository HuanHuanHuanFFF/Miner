"""Unused factored local-tail diagnostic on exact ea102. No active entry edits.
Default dry run; --write creates once; --verify reads only. No Lean/Git/CI.
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
PARENT = HERE.parent / 'f01-d11-wide-writer-proof2/Kernel.lean'
PARENT_SHA = 'ea10235659e5c3eef3ed1bd0e32920a0f479dd04d4188d22083e0ab8aee1a1d7'
ASSET = R11 / 'review-output-tail-factoring.lean'
ASSET_SHA = '9d7bcb60b483b1b1994836c679e8b466d3cac1c17bc0532875aaf69cbdb2d486'
DONOR = HERE.parent / 'f01-d11-panel4-tail-proof2/panel4-tail-proof2.lean'
DONOR_SHA = 'ff487d27aa2f7b39029d3bee57d92d1a2abbd65e41329981d30c7abdd861fc54'
HELPERS = HERE.parent / 'f01-d11-panel4-tail-proof/build.py'
HELPERS_SHA = 'ca9e0c37a66a01487b0da83419ea881bf209e9177853a764fd57f94309eef70b'


def sha(raw):
    return sha256(raw).hexdigest()


def construct():
    parent, asset, donor = PARENT.read_bytes(), ASSET.read_bytes(), DONOR.read_bytes()
    assert sha(parent) == PARENT_SHA and len(parent) == 244990
    assert sha(asset) == ASSET_SHA and len(asset) == 6165
    assert sha(donor) == DONOR_SHA
    prefix = donor[:donor.index(b'/-- Local numeric base')]
    assert len(prefix) == 3154 and asset.startswith(prefix) and len(asset) <= 6500
    assert parent.endswith(b'\n') and asset.endswith(b'\n')
    data = parent + asset
    assert len(data) <= 256000 and data[:-len(asset)] == parent
    assert sha(HELPERS.read_bytes()) == HELPERS_SHA
    sys.dont_write_bytecode = True
    spec = importlib.util.spec_from_file_location('pinned_tail_helpers', HELPERS)
    helper = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(helper)
    parser = helper.PARSER.read_bytes()
    assert sha(parser) == '58662bf7218de54978d999bfb424975732cf845708869e1d611dd712d7470f22'
    inv = helper.functions(parser, ['strip_comments', 'declarations'], {'re': re})
    a, b = [inv['declarations'](x.decode()) for x in (parent, data)]
    assert set(a) <= set(b) and all(len(v) == 1 for v in b.values())
    expected = {'Submission.Panel4Tail.' + n for n in ['prepare', 'prepare_getD', 'prepare_read',
        'dot10_shift', 'runDot_shift', 'runDot_prepared', 'group', 'row', 'group_eq', 'row_eq',
        'tail', 'tail_eq', 'tail_prefix']}
    assert set(b) - set(a) == expected
    gate = helper.GATE.read_bytes()
    assert sha(gate) == '1eb74ef7479b0023c721e776cc5e4073af21c6662b4afffcf16a48a124d27194'
    tree = ast.parse(gate.decode())
    assign = {t.id: n.value for n in tree.body if isinstance(n, ast.Assign)
              for t in n.targets if isinstance(t, ast.Name)}
    env = {'re': re, 'Path': Path, 'Verdict': object,
           'SLOTS': {'full': SimpleNamespace(contract='ContractTensor')},
           'OPTIONS': ast.literal_eval(assign['OPTIONS']),
           'ATTRIBUTES': ast.literal_eval(assign['ATTRIBUTES']),
           'BANNED': re.compile(ast.literal_eval(assign['BANNED'].args[0]))}
    env = helper.functions(gate, ['policy', 'options'], env)
    assert env['policy'](SimpleNamespace(read_text=lambda: data.decode()), SimpleNamespace(slot='full')) is None
    code = inv['strip_comments'](asset.decode())
    runtime = []
    for name in ['prepare', 'group', 'row', 'tail']:
        m = re.search(r'^(?:@\[inline\] )?def ' + name + r'\b', code, re.M)
        assert m
        end = re.search(r'^(?:theorem |(?:@\[inline\] )?def |end Submission)', code[m.end():], re.M)
        body = code[m.start():m.end()+end.start()]
        assert '.map' not in body
        runtime.append({'name': name, 'source_sha256': sha(body.encode())})
    assert 'foldl_inv' not in code and 'group_prefix' not in code and 'row_prefix' not in code
    receipt = {'candidate': HERE.name, 'candidate_sha256': sha(data), 'candidate_bytes': len(data),
        'headroom_bytes': 256000-len(data), 'parent_sha256': PARENT_SHA, 'parent_bytes': len(parent),
        'asset_sha256': sha(asset), 'asset_bytes': len(asset), 'builder_sha256': sha(Path(__file__).read_bytes()),
        'donor_sha256': DONOR_SHA, 'exact_accepted_helper_prefix_bytes': len(prefix),
        'exact_helper_prefix_sha256': sha(prefix), 'saved_vs935_full_tail_asset_bytes': len(donor)-len(asset),
        'added_declarations': sorted(expected), 'runtime_definitions': runtime,
        'checks': {'full_inverse_to_ea102': 'PASS', 'active_entry_and_four_specs_unchanged': 'PASS',
          'exact935_helper_prefix': 'PASS', 'only_new_Panel4Tail_namespace': 'PASS',
          'unique_declarations': 'PASS', 'original_policy': 'PASS', 'runtime_no_globalAmap': 'PASS',
          'no_new_Prefix_fold_induction': 'PASS', 'parent_options_and_author_notices': 'UNCHANGED'},
        'validation_mode': 'STATEMENT_DIAGNOSTIC', 'statement': 'NOT_RUN', 'kernel_replay': 'NOT_RUN',
        'axiom_audit': 'NOT_RUN', 'checksum': 'NOT_RUN', 'full_gate': 'NOT_RUN',
        'matrix_algorithm_acceptance': 'NOT_APPLICABLE_NO_ACTIVE_PANEL_OR_TAIL_ENTRY',
        'performance': 'NOT_APPLICABLE_UNUSED_TAIL_HELPER', 'formal_submission': 'NOT_SUBMITTED'}
    inverse = {'parent_sha256': PARENT_SHA, 'candidate_sha256': sha(data), 'append_offset': len(parent),
        'appended_text': asset.decode(), 'appended_sha256': sha(asset),
        'inverse_recovers_exact_parent': data[:-len(asset)] == parent}
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
        assert (HERE / 'tail-factoring.lean').read_bytes() == asset
    elif args.write:
        names = ['Kernel.lean', 'tail-factoring.lean', 'manifest.json', 'static-checks.json', 'exact-inverse.json']
        assert not any((HERE / n).exists() for n in names), 'Refuse overwrite'
        (HERE / 'Kernel.lean').write_bytes(data)
        (HERE / 'tail-factoring.lean').write_bytes(asset)
        manifest = dict(receipt, candidate_file='Kernel.lean', created_at_utc=datetime.now(timezone.utc).isoformat(),
            parent='f01-d11-wide-writer-proof2', ci_owner='root',
            mechanism='Local numeric r*n and original raw-finish address remain separate. Group/row/tail exact function equalities reuse original emitTail_prefix, with no repeated Prefix fold induction.',
            acceptance='ea102 passed925 statement; donor3154B helper prefix occurred in6e99 passed935 statement. This combined source and every new equality are NOT_RUN.',
            missing='No actual GeneralPanel entry/Projects/output dispatch/lifecycle/full gate/performance. Full GeneralPanel source capacity remains a separate integration audit.')
        for name, obj in [('manifest.json', manifest), ('static-checks.json', receipt), ('exact-inverse.json', inverse)]:
            (HERE / name).write_bytes((json.dumps(obj, ensure_ascii=False, indent=2)+'\n').encode())
    print(json.dumps(receipt, ensure_ascii=False, indent=2))


if __name__ == '__main__':
    main()
