"""Pinned 0655 integration, independent of frozen compose-structural.py.

Default dry run. --write may create ONLY the classifier recipe in this directory.
The classifier+fallback recipe is dry-run only pending Root's 919 decision.
--verify checks the existing classifier source. No Lean, Git, CI or downloads.
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
CANDIDATES = HERE.parent
PINS = {
    'parent': ('f01-d11-bmm-combined-direct/Kernel.lean', '0655b26612f7359c100b2c7e091e3d2f4c53fcde5e8286d25f3c41cbdc75f06e', 254588),
    'origin': ('f01-d10-bmm-direct-rows/Kernel.lean', 'a06608bdc419d4647af301bfdd617d52e4796c404661a28672a022eef4a10b78', 237142),
    'classifier': ('f01-d11-bmm-self-classifier/Kernel.lean', '6457ed8f64714c116d8e861e612c53a9019446e8a282964611c794ccba29f482', 237208),
    'classifier_patch': ('f01-d11-bmm-self-classifier/exact-inverse.json', '4a3bb638c3af18cdc676e6e5a6372a639854f495f2d70eeb72d20ba300e1a789', None),
    'fallback': ('f01-d11-add-official-fallback/Kernel.lean', '73177f570f584f3429e181e5a27f98bfb56e6fc26fd6b7b3e0fbd3ba2152a553', 221629),
    'fallback_patch': ('f01-d11-add-official-fallback/exact-inverse.json', '2ffae7b91d1ce43dfadac0cc3ddd3d37ccc510a06da50cfe6e02cc2886c79a0d', None),
    'parser': ('f01-r8-combined-result-guard/build.py', '58662bf7218de54978d999bfb424975732cf845708869e1d611dd712d7470f22', 13088),
}
GATE = ROOT / 'competitions/floatlib/research/astra-collab-20261023-r7/upstream/gate-4b7e838.py'
GATE_SHA = '1eb74ef7479b0023c721e776cc5e4073af21c6662b4afffcf16a48a124d27194'
STATEMENT = CANDIDATES / 'f01-mul-log2-proof1/ci-runs/40034884263/download-d41168a29dcc470f82e334b20f4724e6/diagnostics/f01-d7-public-suite/public-suite/summary.json'
STATEMENT_SHA = '5353b65fe9e8acb1c216aa59b1aa618603e273e03bb52495774351a749e02661'


def sha(raw):
    return sha256(raw).hexdigest()


def functions(raw, names, env):
    nodes = [n for n in ast.parse(raw.decode()).body if isinstance(n, ast.FunctionDef) and n.name in names]
    assert {n.name for n in nodes} == set(names)
    exec(compile(ast.Module(body=nodes, type_ignores=[]), '<pinned pure helpers>', 'exec'), env)
    return env


def apply(raw, operations):
    ledger = []
    for op in operations:
        before, after = op['before'].encode(), op['after'].encode()
        assert sha(before) == op['before_sha256'] and sha(after) == op['after_sha256']
        assert raw.count(before) == 1, ('Non-unique patch source', op['name'])
        at = raw.index(before)
        updated = raw[:at] + after + raw[at + len(before):]
        ledger.append({'name': op['name'], 'offset_in_previous_stage': at,
                       'before': before.decode(), 'after': after.decode(),
                       'before_sha256': sha(before), 'after_sha256': sha(after),
                       'previous_source_sha256': sha(raw), 'next_source_sha256': sha(updated)})
        raw = updated
    return raw, ledger


def inverse(raw, ledger):
    for op in reversed(ledger):
        assert sha(raw) == op['next_source_sha256']
        at, before, after = op['offset_in_previous_stage'], op['before'].encode(), op['after'].encode()
        assert raw[at:at + len(after)] == after
        raw = raw[:at] + before + raw[at + len(after):]
        assert sha(raw) == op['previous_source_sha256']
    return raw


def construct(recipe):
    assert recipe in ('classifier', 'classifier+fallback')
    raw, inputs = {}, []
    for role, (name, expected, size) in PINS.items():
        path = CANDIDATES / name
        value = path.read_bytes()
        assert sha(value) == expected and (size is None or len(value) == size), role
        raw[role] = value
        inputs.append({'role': role, 'path': path.relative_to(ROOT).as_posix(), 'sha256': expected, 'bytes': len(value)})
    gate_raw = GATE.read_bytes()
    assert sha(gate_raw) == GATE_SHA
    statement_raw = STATEMENT.read_bytes()
    assert sha(statement_raw) == STATEMENT_SHA
    statement = json.loads(statement_raw)
    accepted = next(r for r in statement['results'] if r['kernel_sha256'] == PINS['classifier'][1])
    assert accepted['statement_pass'] is True and accepted['exit_code'] == 0
    classifier_ops, fallback_ops = [json.loads(raw[k + '_patch']) for k in ('classifier', 'fallback')]
    assert len(classifier_ops) == len(fallback_ops) == 3
    for role, operations in [('classifier', classifier_ops), ('fallback', fallback_ops)]:
        reproduced, donor_ledger = apply(raw['origin'], operations)
        assert reproduced == raw[role], ('Donor recipe identity', role)
        assert inverse(reproduced, donor_ledger) == raw['origin']
    # Both donors are exactly reproduced first. Their same unique before/after
    # bytes now apply to the independently pinned combined parent.
    result, ledger = apply(raw['parent'], classifier_ops)
    if recipe == 'classifier+fallback':
        result, more = apply(result, fallback_ops)
        ledger.extend(more)
    assert inverse(result, ledger) == raw['parent']
    assert len(result) <= 256000
    parser = functions(raw['parser'], ['strip_comments', 'declarations'], {'re': re})
    old_decl, new_decl = [parser['declarations'](b.decode()) for b in (raw['parent'], result)]
    removed = set(old_decl) - set(new_decl)
    expected_removed = {k for k in old_decl if k.startswith('Submission.TunedAdd.')} if recipe.endswith('+fallback') else set()
    assert removed == expected_removed and not (set(new_decl) - set(old_decl))
    assert all(len(old_decl[k]) == len(new_decl[k]) for k in new_decl)
    exports = ['Submission.' + name for name in ['add', 'add_spec', 'mul', 'mul_spec', 'sum', 'sum_spec', 'bmm', 'bmm_spec']]
    assert all(len(new_decl.get(k, [])) == 1 for k in exports)

    def declaration_chunk(source, inventory, name):
        lines = source.decode().splitlines(keepends=True)
        index = inventory[name][0] - 1
        # This boundary recognizes following namespace/end commands too. All
        # exported types are unchanged, with a separate exact-body check below.
        end = index + 1
        while end < len(lines) and not re.match(r'^(?:@\[[^]]+\]\s*)?(?:(?:private|protected|noncomputable)\s+)*(?:def|theorem|abbrev|namespace|end)\b', lines[end]):
            end += 1
        return ''.join(lines[index:end]).encode()

    chunks = {}
    for name in exports:
        old, new = [declaration_chunk(b, d, name) for b, d in ((raw['parent'], old_decl), (result, new_decl))]
        assert old.split(b':=', 1)[0] == new.split(b':=', 1)[0], ('Export obligation changed', name)
        if recipe == 'classifier' or name not in ('Submission.add', 'Submission.add_spec'):
            assert old == new, ('Unexpected export body change', name)
        chunks[name] = {'type_unchanged': True, 'full_chunk_unchanged': old == new,
                        'parent_sha256': sha(old), 'candidate_sha256': sha(new)}
    option_lines = lambda b: re.findall(rb'^.*\bset_option\b.*$', b, re.M)
    assert option_lines(raw['parent']) == option_lines(result)
    if recipe == 'classifier':
        assert all('/-' not in op['before'] + op['after'] and '--' not in op['before'] + op['after'] for op in ledger)
    else:
        deleted = fallback_ops[-1]['before']
        assert sha(deleted.encode()) == '04f2b622654ce1c70972fa600a27736339b74129a8cd5ca38c922cca6cef9743'
        notice = r'copyright|licen[cs]e|SPDX|author|attribution|permission|\bMIT\b|\bBSD\b|Apache|版权所有|作者|许可'
        assert not re.search(notice, deleted, re.I)
        notices = lambda b: [line for line in b.decode().splitlines(keepends=True) if re.search(notice, line, re.I)]
        assert notices(raw['parent']) == notices(result)
        assert b'TunedAdd' not in result
    assignments = {t.id: n.value for n in ast.parse(gate_raw.decode()).body if isinstance(n, ast.Assign)
                   for t in n.targets if isinstance(t, ast.Name)}
    env = {'re': re, 'Path': Path, 'Verdict': object, 'SLOTS': {'full': SimpleNamespace(contract='ContractTensor')},
           'OPTIONS': ast.literal_eval(assignments['OPTIONS']), 'ATTRIBUTES': ast.literal_eval(assignments['ATTRIBUTES']),
           'BANNED': re.compile(ast.literal_eval(assignments['BANNED'].args[0]))}
    env = functions(gate_raw, ['policy', 'options'], env)
    assert env['policy'](SimpleNamespace(read_text=lambda: result.decode()), SimpleNamespace(slot='full')) is None
    checks = {'donor_exact_source_reproduction': 'PASS', 'combined_parent_full_inverse': 'PASS',
              'unique_patch_ranges_and_sha256': 'PASS', 'namespace_inventory_exact': 'PASS',
              'export_obligation_types_unchanged': 'PASS', 'export_body_checks': chunks,
              'author_notice_preservation': 'PASS', 'resource_options_unchanged': 'PASS', 'original_gate_policy': 'PASS',
              'gate_sha256': GATE_SHA, 'removed_declarations': sorted(removed),
              'new_statement': 'NOT_RUN', 'leanchecker': 'NOT_RUN', 'axiom_audit': 'NOT_RUN', 'checksum': 'NOT_RUN',
              'full_gate': 'NOT_RUN', 'generated_c_assembly': 'NOT_RUN', 'performance': 'UNKNOWN_NOT_ADDITIVE'}
    return result, ledger, {'recipe': recipe, 'candidate_sha256': sha(result), 'candidate_bytes': len(result),
        'parent_sha256': PINS['parent'][1], 'delta_from_parent_bytes': len(result) - len(raw['parent']),
        'headroom_bytes': 256000 - len(result), 'component_sources': inputs, 'checks': checks,
        'classifier_component_statement': {'run': 40034884263, 'seed': 917, 'summary_sha256': STATEMENT_SHA,
            'component_sha256': PINS['classifier'][1], 'statement_pass': True, 'full_gate': False,
            'does_not_validate_new_combination': True}}


def main():
    ap = ArgumentParser()
    ap.add_argument('--recipe', choices=['classifier', 'classifier+fallback'], default='classifier')
    mode = ap.add_mutually_exclusive_group()
    mode.add_argument('--write', action='store_true')
    mode.add_argument('--verify', action='store_true')
    args = ap.parse_args()
    if args.write or args.verify:
        assert args.recipe == 'classifier', 'Fallback recipe is dry-run only pending Root 919 decision'
    result, ledger, receipt = construct(args.recipe)
    if args.verify:
        assert (HERE / 'Kernel.lean').read_bytes() == result
    elif args.write:
        assert not any((HERE / n).exists() for n in ['Kernel.lean', 'manifest.json', 'exact-inverse.json', 'static-checks.json']), 'Refuse overwrite'
        manifest = dict(receipt, candidate=HERE.name, candidate_file='Kernel.lean', parent='f01-d11-bmm-combined-direct',
            created_at_utc=datetime.now(timezone.utc).isoformat(), state='READY_FOR_STATEMENT',
            mechanism='Exactly three6457 self-classifier edits on0655: NativeFinal.dot and Packed10.finish guards plus dot_eq premise. Existing Cross/Underflow/DirectContinuous/fused dispatcher and four public specs unchanged. No official-add fallback.',
            proof_status='NOT_RUN_NEW_COMBINATION', validation_mode='statement first, then original full gate',
            performance='UNKNOWN_NOT_ADDITIVE', formal_submission='NOT_SUBMITTED', ci_owner='root')
        (HERE / 'Kernel.lean').write_bytes(result)
        for name, payload in [('manifest.json', manifest), ('exact-inverse.json', ledger), ('static-checks.json', receipt)]:
            (HERE / name).write_bytes((json.dumps(payload, ensure_ascii=False, indent=2) + '\n').encode())
    print(json.dumps(receipt, ensure_ascii=False, indent=2))


if __name__ == '__main__':
    main()
