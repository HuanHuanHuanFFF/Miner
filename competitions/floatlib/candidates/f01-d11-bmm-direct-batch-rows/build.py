"""One direct-writer loop-structure experiment from exact 2aaa.

Dry run by default. --write creates frozen source/receipts once; --verify checks
them without writing. No Lean, Git, CI, toolchain options or downloads.
"""
from argparse import ArgumentParser
from datetime import datetime, timezone
from hashlib import sha256
from pathlib import Path
from types import SimpleNamespace
import ast
import json
import re

HERE = Path(__file__).resolve().parent
ROOT = HERE.parents[3]
PARENT = HERE.parent / 'f01-d11-bmm-direct-continuous/Kernel.lean'
PARENT_SHA = '2aaa5d9e84c758a23a8c6dc1f77d800950fbaa5769aec7a38d299741c17a5f56'
BLOCK_SHA = '702e9f00339055525588fcf6ac71c29996ae4f819da60a5c3e4211059ee30890'
GATE = ROOT / 'competitions/floatlib/research/astra-collab-20261023-r7/upstream/gate-4b7e838.py'
GATE_SHA = '1eb74ef7479b0023c721e776cc5e4073af21c6662b4afffcf16a48a124d27194'
PARSER = HERE.parent / 'f01-r8-combined-result-guard/build.py'
PARSER_SHA = '58662bf7218de54978d999bfb424975732cf845708869e1d611dd712d7470f22'


def sha(raw):
    return sha256(raw).hexdigest()


def functions(raw, names, env):
    nodes = [n for n in ast.parse(raw.decode()).body if isinstance(n, ast.FunctionDef) and n.name in names]
    assert {n.name for n in nodes} == set(names)
    exec(compile(ast.Module(body=nodes, type_ignores=[]), '<pinned pure helpers>', 'exec'), env)
    return env


def construct():
    parent, block = PARENT.read_bytes(), (HERE / 'batch-rows.lean').read_bytes()
    assert sha(parent) == PARENT_SHA and len(parent) == 248566
    assert sha(block) == BLOCK_SHA and len(block) == 3985
    namespace = parent.index(b'namespace Submission.DirectContinuous\n')
    start, end = parent.index(b'def output (', namespace), parent.index(b'def core (', namespace)
    before = parent[start:end]
    assert (start, end, len(before), sha(before)) == (246462, 247204, 742, '30e2caceb92e6599ea69acc4418d8401f994d1eaab6bb8b4217521ba4cc6e35e')
    assert parent.count(before) == 1
    assert b'/-' not in before and b'--' not in before
    result = parent[:start] + block + parent[end:]
    assert result[:start] + before + result[start + len(block):] == parent
    assert len(result) <= 256000
    op = {'name': 'Replace only DirectContinuous.output/output_prefix with nested batch-row writer and proof bridges',
          'offset_in_parent': start, 'before': before.decode(), 'after': block.decode(),
          'before_sha256': sha(before), 'after_sha256': sha(block),
          'parent_sha256': sha(parent), 'candidate_sha256': sha(result)}
    parser_raw = PARSER.read_bytes()
    assert sha(parser_raw) == PARSER_SHA
    parser = functions(parser_raw, ['strip_comments', 'declarations'], {'re': re})
    old_decl, new_decl = [parser['declarations'](b.decode()) for b in (parent, result)]
    added = {'Submission.DirectContinuous.' + name for name in
             ['batchRowIndex', 'batchRow', 'batchRow_eq_row', 'batchRow_prefix', 'batchStep', 'batchStep_prefix']}
    assert set(new_decl) - set(old_decl) == added and not (set(old_decl) - set(new_decl))
    assert all(len(new_decl[k]) == len(old_decl[k]) for k in old_decl)

    def chunk(raw, inventory, name):
        lines = raw.decode().splitlines(keepends=True)
        index = inventory[name][0] - 1
        stop = index + 1
        while stop < len(lines) and not re.match(r'^(?:@\[[^]]+\]\s*)?(?:(?:private|protected|noncomputable)\s+)*(?:def|theorem|abbrev|namespace|end)\b', lines[stop]):
            stop += 1
        return ''.join(lines[index:stop]).encode()

    exports = ['Submission.' + name for name in ['add', 'add_spec', 'mul', 'mul_spec', 'sum', 'sum_spec', 'bmm', 'bmm_spec']]
    export_hashes = {}
    for name in exports:
        assert len(new_decl.get(name, [])) == 1
        old, new = chunk(parent, old_decl, name), chunk(result, new_decl, name)
        assert old == new, ('Public export or proof changed', name)
        export_hashes[name] = sha(new)
    # Only the new writer is on the changed runtime route. The old row and its
    # division survive solely as an unchanged proof target.
    runtime = {}
    for name in ['batchRow', 'batchStep', 'output']:
        source = chunk(result, new_decl, 'Submission.DirectContinuous.' + name)
        code = parser['strip_comments'](source.decode())
        assert '/' not in code and '%' not in code
        assert 'packedB' not in code and 'nativeA' not in code
        assert not re.search(r'\b(row|batchRowIndex)\b', code)
        runtime[name] = {'sha256': sha(source), 'division_modulo_absent': True,
                         'nativeA_packedB_absent': True, 'old_row_not_called': True}
    options = lambda b: re.findall(rb'^.*\bset_option\b.*$', b, re.M)
    assert options(parent) == options(result)
    gate_raw = GATE.read_bytes()
    assert sha(gate_raw) == GATE_SHA
    assignments = {t.id: n.value for n in ast.parse(gate_raw.decode()).body if isinstance(n, ast.Assign)
                   for t in n.targets if isinstance(t, ast.Name)}
    env = {'re': re, 'Path': Path, 'Verdict': object, 'SLOTS': {'full': SimpleNamespace(contract='ContractTensor')},
           'OPTIONS': ast.literal_eval(assignments['OPTIONS']), 'ATTRIBUTES': ast.literal_eval(assignments['ATTRIBUTES']),
           'BANNED': re.compile(ast.literal_eval(assignments['BANNED'].args[0]))}
    env = functions(gate_raw, ['policy', 'options'], env)
    assert env['policy'](SimpleNamespace(read_text=lambda: result.decode()), SimpleNamespace(slot='full')) is None
    return result, op, {'candidate': HERE.name, 'candidate_sha256': sha(result), 'candidate_bytes': len(result),
        'parent_sha256': PARENT_SHA, 'delta_bytes': len(result) - len(parent), 'headroom_bytes': 256000 - len(result),
        'checks': {'exact_parent_and_replacement_pins': 'PASS', 'exact_full_inverse': 'PASS',
                   'declaration_inventory': 'PASS', 'public_exports_and_four_specs_exact_bytes': export_hashes,
                   'new_runtime_source_checks': runtime, 'author_notices_and_old_helpers_preserved': 'PASS',
                   'resources_unchanged': 'PASS', 'original_gate_policy': 'PASS', 'gate_sha256': GATE_SHA,
                   'new_statement': 'NOT_RUN', 'leanchecker': 'NOT_RUN', 'axiom_audit': 'NOT_RUN', 'checksum': 'NOT_RUN',
                   'full_gate': 'NOT_RUN', 'generated_c_assembly': 'NOT_RUN', 'performance': 'UNKNOWN'}}


def main():
    ap = ArgumentParser()
    modes = ap.add_mutually_exclusive_group()
    modes.add_argument('--write', action='store_true')
    modes.add_argument('--verify', action='store_true')
    args = ap.parse_args()
    result, op, receipt = construct()
    if args.verify:
        assert (HERE / 'Kernel.lean').read_bytes() == result
    elif args.write:
        assert not any((HERE / n).exists() for n in ['Kernel.lean', 'manifest.json', 'exact-inverse.json', 'static-checks.json']), 'Refuse overwrite'
        manifest = dict(receipt, candidate_file='Kernel.lean', parent='f01-d11-bmm-direct-continuous',
            created_at_utc=datetime.now(timezone.utc).isoformat(), state='READY_FOR_STATEMENT',
            mechanism='Same n<=4,p>2 dispatch and scalar dots; nested batch then row Fin.foldl. Per-batch baseA0=b*m*n and baseB=b*n*p, rows use baseA0+i*n. No flattened-row division, no extra tuple accumulator, nativeA or packedB. All new loop costs remain in call.',
            proof='New batchRow equals unchanged old row at proof-only flattened row index, using mul_add_div and add_mul. Existing row_prefix -> inner foldl_inv -> outer foldl_inv -> unchanged core/reference and all four public spec proofs.',
            edge_cases='Proof states cover all Nat dimensions, including m=0/batch=0/p=0/n=0. Positivity needed for division only under i:Fin m in proof. Original fallback dispatcher and HugeNat representation unchanged.',
            lowering_limit='No source-level div on new writer path; generated C/asm may introduce closure/loop/address costs and are NOT_RUN. Prior row had one dynamic div, with64/32 alternatives; not two independent divisions.',
            proof_status='NOT_RUN_NEW_LOOP_PROOF', validation_mode='statement first then original full gate paired with exact2aaa',
            performance='UNKNOWN', formal_submission='NOT_SUBMITTED', ci_owner='root')
        (HERE / 'Kernel.lean').write_bytes(result)
        for name, payload in [('manifest.json', manifest), ('exact-inverse.json', op), ('static-checks.json', receipt)]:
            (HERE / name).write_bytes((json.dumps(payload, ensure_ascii=False, indent=2) + '\n').encode())
    print(json.dumps({k: v for k, v in receipt.items() if k != 'checks'}, indent=2))
    print('Static source checks PASS; new Lean/fullgate/codegen NOT_RUN.')


if __name__ == '__main__':
    main()
