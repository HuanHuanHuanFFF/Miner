"""Exact a066 experiment: official add fallback, then remove unused TunedAdd.

Default dry run. --write creates one source and receipts, refusing overwrite.
--verify reproduces the frozen bytes. No Lean, Git, CI, or downloads.
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
PARENT = HERE.parent / 'f01-d10-bmm-direct-rows/Kernel.lean'
PARENT_SHA = 'a06608bdc419d4647af301bfdd617d52e4796c404661a28672a022eef4a10b78'
BLOCK_SHA = '04f2b622654ce1c70972fa600a27736339b74129a8cd5ca38c922cca6cef9743'
GATE = ROOT / 'competitions/floatlib/research/astra-collab-20261023-r7/upstream/gate-4b7e838.py'
GATE_SHA = '1eb74ef7479b0023c721e776cc5e4073af21c6662b4afffcf16a48a124d27194'
PARSER = HERE.parent / 'f01-r8-combined-result-guard/build.py'
PARSER_SHA = '58662bf7218de54978d999bfb424975732cf845708869e1d611dd712d7470f22'


def sha(raw):
    return sha256(raw).hexdigest()


def pinned(path, expected):
    raw = path.read_bytes()
    assert sha(raw) == expected, ('Pinned source mismatch', str(path))
    return raw


def functions(raw, names, env):
    nodes = [n for n in ast.parse(raw.decode()).body if isinstance(n, ast.FunctionDef) and n.name in names]
    assert {n.name for n in nodes} == set(names)
    exec(compile(ast.Module(body=nodes, type_ignores=[]), '<pinned pure helpers>', 'exec'), env)
    return env


def construct():
    parent = pinned(PARENT, PARENT_SHA)
    assert len(parent) == 237142 and b'\r' not in parent
    start = parent.index(b'namespace TunedAdd\n')
    end = parent.index(b'end TunedAdd\n', start) + len(b'end TunedAdd\n')
    block = parent[start:end]
    assert (start, end, len(block), sha(block)) == (79586, 95110, 15524, BLOCK_SHA)
    outside = parent[:start] + parent[end:]
    assert re.findall(rb'^.*TunedAdd.*$', outside, re.M) == [
        b'  else TunedAdd.add x y', b'  \xc2\xb7 exact TunedAdd.add_spec x y']
    # All opens and declarations are inside the closed namespace. Only inline
    # attributes occur; no global instances or simp/notation/option effects.
    plain = block.decode()
    parser = functions(pinned(PARSER, PARSER_SHA), ['strip_comments', 'declarations'], {'re': re})
    code_plain = parser['strip_comments'](plain)
    assert set(re.findall(r'@\[([^]]+)\]', plain)) == {'inline'}
    assert not re.search(r'\b(instance|attribute|export|syntax|macro|notation|infix|prefix|postfix|set_option|initialize|class)\b', code_plain)
    notice_pattern = r'copyright|licen[cs]e|SPDX|author|attribution|permission|\bMIT\b|\bBSD\b|Apache|版权所有|作者|许可'
    assert not re.search(notice_pattern, plain, re.I), 'Preserve any notice instead of deleting it'
    assert b'namespace FastMul\n' not in block and b'namespace LowScale\n' not in block
    result, edits = parent, []

    def replace(name, before, after):
        nonlocal result
        assert result.count(before) == 1, name
        at = result.index(before)
        new = result[:at] + after + result[at + len(before):]
        edits.append({'name': name, 'offset_in_previous_stage': at,
                      'before': before.decode(), 'after': after.decode(),
                      'before_bytes': len(before), 'after_bytes': len(after),
                      'before_sha256': sha(before), 'after_sha256': sha(after),
                      'previous_source_sha256': sha(result), 'next_source_sha256': sha(new)})
        result = new

    replace('NaN-result add fallback uses official executable',
            b'  else TunedAdd.add x y\n', b'  else ExecFloat.add x y\n')
    replace('Fallback proof uses original official theorem',
            b'  \xc2\xb7 exact TunedAdd.add_spec x y\n',
            b'  \xc2\xb7 exact ExecFloat.Proof.add_eq_spec x y\n')
    replace('Delete exact unused closed TunedAdd namespace; leave surrounding comments intact', block, b'')
    inverse = result
    for op in reversed(edits):
        assert sha(inverse) == op['next_source_sha256']
        at, before, after = op['offset_in_previous_stage'], op['before'].encode(), op['after'].encode()
        assert inverse[at:at + len(after)] == after
        inverse = inverse[:at] + before + inverse[at + len(after):]
        assert sha(inverse) == op['previous_source_sha256']
    assert inverse == parent
    assert b'TunedAdd' not in result
    assert len(result) <= 256000

    old_decl, new_decl = [parser['declarations'](b.decode()) for b in (parent, result)]
    removed = {name: lines for name, lines in old_decl.items() if name.startswith('Submission.TunedAdd.')}
    assert removed
    assert set(old_decl) - set(new_decl) == set(removed)
    assert set(new_decl) - set(old_decl) == set()
    assert all(len(new_decl[k]) == len(old_decl[k]) for k in new_decl)
    exports = ['Submission.' + name for name in ['add', 'add_spec', 'mul', 'mul_spec', 'sum', 'sum_spec', 'bmm', 'bmm_spec']]
    assert all(len(new_decl.get(name, [])) == 1 for name in exports)
    option_lines = lambda b: re.findall(rb'^.*\bset_option\b.*$', b, re.M)
    assert option_lines(parent) == option_lines(result)
    # Everything after this theorem contains all native loops, sum and BMM code.
    anchor = b'/-- Only a native NaN result requires the original raw-word fallback. -/'
    assert parent[parent.index(anchor):] == result[result.index(anchor):]
    # Before the fallback definition, deletion is the sole modification.
    add_anchor = b'/-- Classify the native result; raw NaN inputs/results retain exact fallback. -/'
    assert (parent[:parent.index(add_anchor)].replace(block, b'', 1)
            == result[:result.index(add_anchor)])
    finite_before = b'  let result := R2W01b.convert x.raw.1 + R2W01b.convert y.raw.1\n  if hn : R7W04.nonNaN result = true then ExecFloat.Binary.ofFloat32 result\n'
    assert parent.count(finite_before) == result.count(finite_before) == 1
    # Every notice-like source line outside the removed, notice-free block is
    # retained with its exact bytes and order; no comments are edited in place.
    notices = lambda raw: [line for line in raw.decode().splitlines(keepends=True) if re.search(notice_pattern, line, re.I)]
    assert notices(parent) == notices(result)

    gate_raw = pinned(GATE, GATE_SHA)
    assignments = {t.id: node.value for node in ast.parse(gate_raw.decode()).body
                   if isinstance(node, ast.Assign) for t in node.targets if isinstance(t, ast.Name)}
    env = {'re': re, 'Path': Path, 'Verdict': object,
           'SLOTS': {'full': SimpleNamespace(contract='ContractTensor')},
           'OPTIONS': ast.literal_eval(assignments['OPTIONS']),
           'ATTRIBUTES': ast.literal_eval(assignments['ATTRIBUTES']),
           'BANNED': re.compile(ast.literal_eval(assignments['BANNED'].args[0]))}
    env = functions(gate_raw, ['policy', 'options'], env)
    assert env['policy'](SimpleNamespace(read_text=lambda: result.decode()), SimpleNamespace(slot='full')) is None
    checks = {'parent_pin': 'PASS', 'exact_block_boundary_and_sha256': 'PASS', 'two_external_references_only': 'PASS',
              'closed_namespace_no_instances_simp_or_global_effects': 'PASS', 'notice_preservation': 'PASS',
              'exact_three_edits_and_full_inverse': 'PASS', 'declarations_removed_only_TunedAdd': 'PASS',
              'finite_add_path_exact_bytes': 'PASS', 'nativeMul_and_later_native_loop_sum_bmm_tail_exact_bytes': 'PASS',
              'resource_options_unchanged': 'PASS', 'original_gate_policy': 'PASS', 'exports_and_specs_unique': 'PASS',
              'gate_sha256': GATE_SHA, 'inventory_parser_sha256': PARSER_SHA,
              'deleted_block': {'parent_start': start, 'parent_end_exclusive': end, 'bytes': len(block), 'sha256': BLOCK_SHA,
                                'declaration_names': sorted(removed), 'block_doc_comments': len(re.findall(r'/-.*?-/', plain, re.S))},
              'remaining_TunedAdd_references': 0,
              'modified_retained_declarations': ['Submission.add', 'Submission.add_spec'],
              'deleted_declarations_count': len(removed),
              'call_context_limit': 'NativeLoop/sum/BMM source bytes are unchanged; any path calling shared Submission.add may execute the new official fallback on a native NaN result. Specials/repair cost is not assumed free.',
              'lean_statement': 'NOT_RUN', 'leanchecker': 'NOT_RUN', 'axiom_audit': 'NOT_RUN', 'checksum': 'NOT_RUN',
              'full_gate': 'NOT_RUN', 'generated_c_assembly': 'NOT_RUN', 'performance': 'UNKNOWN'}
    return result, edits, checks


def main():
    ap = ArgumentParser()
    modes = ap.add_mutually_exclusive_group()
    modes.add_argument('--write', action='store_true')
    modes.add_argument('--verify', action='store_true')
    args = ap.parse_args()
    result, edits, checks = construct()
    summary = {'candidate': HERE.name, 'candidate_sha256': sha(result), 'candidate_bytes': len(result),
               'parent_sha256': PARENT_SHA, 'delta_bytes': len(result) - 237142,
               'headroom_bytes': 256000 - len(result), 'checks': checks}
    if args.verify:
        assert (HERE / 'Kernel.lean').read_bytes() == result
    elif args.write:
        assert not any((HERE / n).exists() for n in ['Kernel.lean', 'manifest.json', 'exact-inverse.json', 'static-checks.json']), 'Refuse overwrite'
        manifest = dict(summary, created_at_utc=datetime.now(timezone.utc).isoformat(), candidate_file='Kernel.lean',
            parent='f01-d10-bmm-direct-rows', state='READY_FOR_STATEMENT', proof_status='NOT_RUN',
            mechanism='Only native-NaN result fallback of Submission.add changes from TunedAdd.add to original ExecFloat.add; then remove now-unreferenced exact closed TunedAdd namespace. No self-classifier or other candidate changes.',
            proof='NaN-result branch directly uses ExecFloat.Proof.add_eq_spec; finite branch and all downstream proofs unchanged.',
            purpose='Measure full specials/repair cost before deciding whether reclaimed source capacity supports larger BMM restructuring; no speed claim and cold fallback is not assumed free.',
            validation_mode='full-gate', performance='UNKNOWN', formal_submission='NOT_SUBMITTED', ci_owner='root')
        (HERE / 'Kernel.lean').write_bytes(result)
        for name, payload in [('manifest.json', manifest), ('exact-inverse.json', edits), ('static-checks.json', summary)]:
            (HERE / name).write_bytes((json.dumps(payload, ensure_ascii=False, indent=2) + '\n').encode())
    print(json.dumps({k: v for k, v in summary.items() if k != 'checks'}, indent=2))
    print('Static exact-source checks: PASS; all new Lean/fullgate/codegen NOT_RUN.')


if __name__ == '__main__':
    main()
