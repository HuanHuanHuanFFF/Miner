"""Pinned R11 structural composition. Default: dry run, never a Kernel write.

Examples:
  python compose-structural.py --recipe cross+underflow+direct
  python compose-structural.py --recipe short+underflow+direct
  python compose-structural.py --self-test
Root only, after selection:
  python compose-structural.py --write --recipe cross+underflow+direct --output-dir f01-d11-selected
No candidate overwrite, Git/CI, toolchain execution, timing, or acceptance inheritance.
"""
from argparse import ArgumentParser
from collections import Counter
from datetime import datetime, timezone
from hashlib import sha256
from pathlib import Path
from types import SimpleNamespace
import ast
import hashlib
import itertools
import json
import re

HERE = Path(__file__).resolve().parent
ROOT = HERE.parents[4]
CANDIDATES = HERE.parents[1]
CAP = 256000
PINS = {
    'base': ('f01-d11-bmm-fused-output-compact', 'f2fa8d10872e1b341f2400db3ceb3c2a9e4f0f6e6d9cd9779469bc9286760553', 236400),
    'cross': ('f01-r11-crossrow-p2-pack12-proof2', '5c5e7071927400ecd75d02d69b0ce62236a50a615912d99e7f8470a9ccf19c6b', 252699),
    'short': ('f01-r11-crossrow-short-shared', '7cad7df494da6004b9e4b202f4d09b838ef8d4b79ba6fe934eea7287784fea28', 254550),
    'underflow': ('f01-d11-bmm-underflow-zero-proof2', '6a69d6edd8afe6240fc6970c5eb8957a26f50595158c2020715f769dd094ea81', 244896),
    'direct': ('f01-d11-bmm-direct-continuous', '2aaa5d9e84c758a23a8c6dc1f77d800950fbaa5769aec7a38d299741c17a5f56', 248566),
    'origin5b': ('f01-d11-bmm-fused-output-proof3', '5b7d926cf628c2d87042386834f7c1581b9a6aa7441af196453984b395534ba2', 245841),
}
SUPPORT = {
    'inventory': (HERE / 'review-integration-headroom.json', '975eb739f0e7cdb3da585aee2fa4f21eea25d7b8b00844f78373a3082c0769cb'),
    'gate': (ROOT / 'competitions/floatlib/research/astra-collab-20261023-r7/upstream/gate-4b7e838.py', '1eb74ef7479b0023c721e776cc5e4073af21c6662b4afffcf16a48a124d27194'),
    'inventory_parser': (CANDIDATES / 'f01-r8-combined-result-guard/build.py', '58662bf7218de54978d999bfb424975732cf845708869e1d611dd712d7470f22'),
    'comment_parser': (CANDIDATES / 'f01-d7-research/source-budget.py', 'e1ee62f4d61219a80fffe20b54b869baf666b25d136a08a4087f3380a5d6ee51'),
}
FINAL = b'namespace Submission\nopen FloatLib.Floats Competition\n\ndef bmm ('
INCREMENT_PINS = {
    'cross': (15499, 'b71d8bd078ccdb534c572f7bc92cfe7e1a283949100b3a8c550bd1e8e9c0d938'),
    'short': (17350, 'f0d6a0ecee51161ac10fc5f8161f3ba67834876720373c0996fc82c1967d9f65'),
    'underflow': (7676, '9d51b419744126977922e4a2bb98b42987460ead1707f5c61045c9dbe6689a09'),
    'direct': (2732, '458c393b340be8b9553d945b3fc8c95e142a08e353b924a477b755488bb89811'),
}

def sha(raw):
    return sha256(raw).hexdigest()

def label(path):
    return path.relative_to(ROOT).as_posix()

def require(condition, message):
    if not condition:
        raise ValueError(message)

def recipe_parts(value):
    names = value.split('+') if value != 'base' else []
    require(len(names) == len(set(names)), 'Duplicate recipe module')
    require(set(names) <= {'cross', 'short', 'underflow', 'direct'}, 'Unknown recipe module')
    require(not {'cross', 'short'} <= set(names), 'Cross5c and short7cad are alternatives')
    return tuple(k for k in ('cross', 'short', 'underflow', 'direct') if k in names)

def recipe_name(parts):
    return '+'.join(parts) or 'base'

def load_functions(raw, names, constants=(), env=None):
    tree = ast.parse(raw.decode('utf-8'))
    nodes = [n for n in tree.body if isinstance(n, ast.FunctionDef) and n.name in names
             or isinstance(n, ast.Assign) and any(isinstance(t, ast.Name) and t.id in constants for t in n.targets)]
    require({n.name for n in nodes if isinstance(n, ast.FunctionDef)} == set(names), 'Helper function set mismatch')
    result = dict(env or {})
    exec(compile(ast.Module(body=nodes, type_ignores=[]), '<pinned helper definitions>', 'exec'), result)
    return result

def snapshots():
    raw, records = {}, []
    for key, (name, expected, size) in PINS.items():
        path = CANDIDATES / name / 'Kernel.lean'
        value = path.read_bytes()
        require(sha(value) == expected and len(value) == size, 'Pinned source mismatch: ' + key)
        require(b'\r' not in value, 'Only exact LF sources are supported')
        raw[key] = value
        records.append({'role': key, 'path': label(path), 'sha256': expected, 'bytes': size})
    for key, (path, expected) in SUPPORT.items():
        value = path.read_bytes()
        require(sha(value) == expected, 'Pinned support mismatch: ' + key)
        raw[key] = value
        records.append({'role': key, 'path': label(path), 'sha256': expected, 'bytes': len(value)})
    return raw, records

class Edits:
    def __init__(self, raw):
        self.data, self.initial, self.ledger = raw, raw, []

    def at(self, offset, old, new, name):
        require(self.data[offset:offset + len(old)] == old, 'Edit range mismatch: ' + name)
        before = sha(self.data)
        self.data = self.data[:offset] + new + self.data[offset + len(old):]
        self.ledger.append({'name': name, 'offset_in_previous_stage': offset,
                            'before_stage_sha256': before, 'after_stage_sha256': sha(self.data),
                            'old_sha256': sha(old), 'new_sha256': sha(new),
                            'old_bytes': len(old), 'new_bytes': len(new),
                            'old_text': old.decode('utf-8'), 'new_text': new.decode('utf-8')})

    def unique(self, old, new, name):
        require(bool(old) and self.data.count(old) == 1, 'Nonunique/missing exact span: ' + name)
        self.at(self.data.index(old), old, new, name)

    def append(self, new, name):
        require(self.data.endswith(b'end Submission\n'), 'Unexpected append boundary')
        self.at(len(self.data), b'', new, name)

    def inverse(self, value=None):
        value = self.data if value is None else value
        for op in reversed(self.ledger):
            require(sha(value) == op['after_stage_sha256'], 'Inverse stage hash mismatch')
            old, new, at = op['old_text'].encode(), op['new_text'].encode(), op['offset_in_previous_stage']
            require(sha(old) == op['old_sha256'] and sha(new) == op['new_sha256'], 'Inverse span hash mismatch')
            require(value[at:at + len(new)] == new, 'Inverse span bytes mismatch')
            value = value[:at] + old + value[at + len(new):]
            require(sha(value) == op['before_stage_sha256'], 'Inverse recovered stage mismatch')
        require(value == self.initial, 'Inverse did not recover exact compact base')
        return value

def final_wrapper(raw):
    require(raw.count(FINAL) == 1, 'Expected exactly one final public bmm namespace')
    return raw[raw.index(FINAL):]

def rename_final(edits, name):
    old = final_wrapper(edits.data)
    text = old.decode()
    require(len(re.findall(r'\bbmm\b', text)) == 3 and len(re.findall(r'\bbmm_spec\b', text)) == 1,
            'Unexpected public dispatcher alias surface')
    changed = re.sub(r'\bbmm_spec\b', name + '_spec', text)
    changed = re.sub(r'\bbmm\b', name, changed)
    edits.unique(old, changed.encode(), 'alias_current_final_to_' + name)

def increment(raw, kind):
    if kind in ('cross', 'short'):
        anchor = b'/- R11 cross-row p=2 kernel.'
        require(raw.count(anchor) == 1, 'Cross attribution/start boundary mismatch')
        block = raw[raw.index(anchor):]
    elif kind == 'underflow':
        anchor = b'namespace Submission.UnderflowZero\n'
        require(raw.count(anchor) == 1, 'Underflow namespace boundary mismatch')
        block = raw[raw.index(anchor):]
    else:
        anchor, end = b'namespace Submission.DirectContinuous\n', b'end Submission.DirectContinuous'
        require(raw.count(anchor) == raw.count(end) == 1, 'Direct namespace boundary mismatch')
        a = raw.index(anchor)
        block = raw[a:raw.index(end, a) + len(end)]
    size, expected = INCREMENT_PINS[kind]
    require(len(block) == size and sha(block) == expected, 'Exact increment hash mismatch: ' + kind)
    return block

def prune(edits, sources):
    inventory = json.loads(sources['inventory'])
    blocks = inventory['new_direct_delete_sum_blocks'] + [b for b in inventory['P_O_blocks_rebound_to5b7d'] if b['id'].startswith('O')]
    require({b['id'] for b in blocks} == {f'{p}{i}' for p in ('S', 'O') for i in range(1, 6)}, 'Prune inventory set differs')
    total = 0
    for b in blocks:
        a, z = b['byte_range_half_open']
        old = sources['origin5b'][a:z]
        require(len(old) == b['bytes'] and sha(old) == b['sha256'], 'Prune oracle span hash mismatch: ' + b['id'])
        require(old.startswith(b['start_anchor_unique'].encode()) and old.endswith(b['end_anchor_unique'].encode()), 'Prune semantic anchors mismatch')
        edits.unique(old, b'', 'delete_exact_' + b['id'] + '_' + b['name'])
        total += len(old)
    require(total == 5011 + 2837, 'Pruned byte total differs')
    return blocks

def helpers(sources):
    inv = load_functions(sources['inventory_parser'], {'strip_comments', 'declarations'}, env={'re': re})
    comments = load_functions(sources['comment_parser'], {'is_notice', 'comment_spans', 'protected_spans', 'licence_hashes'}, {'LICENCE_WORDS'}, {'re': re, 'hashlib': hashlib})
    tree = ast.parse(sources['gate'].decode())
    assigns = {t.id: n.value for n in tree.body if isinstance(n, ast.Assign) for t in n.targets if isinstance(t, ast.Name)}
    env = {'re': re, 'Path': Path, 'Verdict': object,
           'SLOTS': {'full': SimpleNamespace(contract='ContractTensor')},
           'OPTIONS': ast.literal_eval(assigns['OPTIONS']), 'ATTRIBUTES': ast.literal_eval(assigns['ATTRIBUTES']),
           'BANNED': re.compile(ast.literal_eval(assigns['BANNED'].args[0]))}
    env = load_functions(sources['gate'], {'policy', 'options'}, env=env)
    return inv, comments, env

def trim_blank_lines(edits, comments, parts):
    before = edits.data
    if len(before) <= CAP:
        return {'applied': False, 'saved_bytes': 0, 'removed_lines': 0}
    require('underflow' in parts and 'direct' in parts and bool({'cross', 'short'} & set(parts)),
            'Unexpected over-cap partial recipe; no broader source trimming permitted')
    spans = comments['comment_spans'](before)
    candidates, at = [], 0
    for line in before.splitlines(keepends=True):
        end = at + len(line)
        if not line.strip(b' \t\r\n') and not any(a < end and b > at for a, b in spans):
            candidates.append((at, end))
        at = end
    require(sum(b - a for a, b in candidates) >= len(before) - CAP, 'Not enough ordinary blank lines to fit')
    removed = 0
    for a, b in reversed(candidates):
        if len(edits.data) <= CAP:
            break
        edits.at(a, before[a:b], b'', 'remove_ordinary_blank_line_only')
        removed += 1
    after = edits.data
    require([l for l in before.splitlines(keepends=True) if l.strip()] ==
            [l for l in after.splitlines(keepends=True) if l.strip()], 'Nonblank physical line changed')
    require([sha(before[a:b]) for a, b in spans] ==
            [sha(after[a:b]) for a, b in comments['comment_spans'](after)], 'Comment bytes/order changed during blank trimming')
    return {'applied': True, 'saved_bytes': len(before) - len(after), 'removed_lines': removed,
            'nonblank_physical_lines_byte_identical': True, 'all_comment_bytes_and_order_identical': True,
            'nonblank_physical_lines_sha256': sha(b''.join(l for l in before.splitlines(keepends=True) if l.strip())),
            'comment_hash_sequence_sha256': sha(json.dumps([sha(before[a:b]) for a, b in spans]).encode())}

def body(text, name):
    start = list(re.finditer(r'(?m)^def ' + re.escape(name) + r'\b', text))
    require(len(start) == 1, 'Dispatcher declaration not unique: ' + name)
    a = start[0].start()
    z = text.index('\ntheorem ' + name + '_spec', a)
    return text[a:z]

def static_verify(raw, parts, inv, policy):
    text = raw.decode('utf-8')
    require(len(raw) <= CAP and b'\r' not in raw, 'Size/UTF8/LF check failed')
    reason = policy['policy'](SimpleNamespace(read_text=lambda: text), SimpleNamespace(slot='full'))
    require(reason is None, 'Original pinned policy rejected: ' + str(reason))
    decls = inv['declarations'](text)
    for name in ('add', 'add_spec', 'mul', 'mul_spec', 'sum', 'sum_spec', 'bmm', 'bmm_spec'):
        require(len(decls.get('Submission.' + name, [])) == 1, 'Export inventory mismatch: ' + name)
    duplicate = {n: lines for n, lines in decls.items() if len(lines) > 1}
    require(not duplicate, 'Duplicate fully qualified declarations: ' + str(duplicate))
    plain = inv['strip_comments'](text)
    retired = ('NativeDecodeSum', 'NativeDecodeSumWord', 'sumBeforeR7SinglePass', 'originalSum', 'originalSum_spec',
               'sumLoop', 'sumLoop_eq', 'decode_bounds', 'groups_pos_of_col', 'column_decomposition',
               'finish_eq_fold', 'finish_eq_kernel_fold', 'finish_dot10_lane_fold', 'tileResults', 'outputFromTiles',
               'inlineDecodeC', 'bmmR4', 'bmmRows')
    remaining = {n: len(re.findall(r'\b' + n + r'\b', plain)) for n in retired}
    require(not any(remaining.values()), 'Remaining references to retired chain: ' + str(remaining))
    require(not re.search(r'\bPacked10\.lane_zero\b', plain), 'Removed Packed10.lane_zero still referenced')
    keep = ['Submission.DirectRows.core', 'Submission.DirectRows.core_eq', 'Submission.NativeFinal.dot',
            'Submission.NativeFinal.dot_eq', 'Submission.R7SinglePassSum.run', 'Submission.R7SinglePassSum.run_spec',
            'Submission.Packed10Index.runDot', 'Submission.RowStream.core_eq_reference']
    require(all(n in decls for n in keep), 'Required fallback/proof component missing')
    cross = bool({'cross', 'short'} & set(parts))
    underflow, direct = 'underflow' in parts, 'direct' in parts
    base_name = 'bmmBeforeR11Cross' if cross else 'bmmBeforeUnderflowZero' if underflow else 'bmm'
    base_body = body(text, base_name)
    expected_direct = 'DirectContinuous.core' if direct else 'DirectRows.core'
    require('if n ≤ 4 ∧ 2 < p then ' + expected_direct in base_body, 'Direct/base guard route wrong')
    require('else bmmBeforeDirectRows batch m n p A B' in base_body, 'Base miss bypasses fused dispatcher')
    chain = [{'entry': base_name, 'guard': 'n<=4 and p>2', 'hit': expected_direct, 'miss': 'bmmBeforeDirectRows'}]
    if cross:
        cross_name = 'bmmBeforeUnderflowZero' if underflow else 'bmm'
        cross_body = body(text, cross_name)
        require('R11CrossRows.core' in cross_body and 'else bmmBeforeR11Cross batch m n p A B' in cross_body, 'Cross miss route wrong')
        require('p=2 ∧ 4≤batch*m ∧ 0<n ∧ n<USize.size' in cross_body, 'Cross guard altered')
        require('Submission.R11CrossRows.lane_zero' in decls, 'Cross own lane_zero proof was incorrectly removed')
        chain.insert(0, {'entry': cross_name, 'guard': 'exact donor p2/machine bounds', 'hit': 'R11CrossRows.core', 'miss': 'bmmBeforeR11Cross'})
    if underflow:
        top = body(text, 'bmm')
        require('A.toArray.all UnderflowZero.small && B.toArray.all UnderflowZero.small' in top,
                'Underflow all-input guard altered')
        require('else bmmBeforeUnderflowZero batch m n p A B' in top, 'Underflow miss route wrong')
        chain.insert(0, {'entry': 'bmm', 'guard': 'exact6a two Array.all', 'hit': 'UnderflowZero.zeros', 'miss': 'bmmBeforeUnderflowZero'})
    require('else bmmPackedBase batch m n p A B' in body(text, 'bmmBeforeDirectRows'), 'Existing DirectSmall/packed fallback changed')
    require('else RowStream.core batch m n p A B' in body(text, 'bmmPackedBase'), 'Packed path no longer reaches fused RowStream')
    if not cross:
        require('Submission.R11CrossRows.core' not in decls, 'Unselected Cross block leaked in')
    if not underflow:
        require('Submission.UnderflowZero.zeros' not in decls, 'Unselected underflow block leaked in')
    if not direct:
        require('Submission.DirectContinuous.core' not in decls, 'Unselected Direct block leaked in')
    require('Submission.BatchLocalPacked.core' not in decls, 'Deferred batch-local B module must not be mixed in')
    return {'original_policy': 'PASS_EXACT_PINNED_POLICY_FUNCTION', 'namespace_stack': 'BALANCED',
            'four_exports_and_specs': 'EXACTLY_ONE_EACH', 'duplicate_declarations': duplicate,
            'remaining_retired_name_counts': remaining, 'required_preserved_declarations': keep,
            'new_decl_count': len(decls), 'fallback_chain': chain,
            'fallback_tail': 'bmmBeforeDirectRows -> DirectSmall or bmmPackedBase -> empty/n0 reference or RowStream.core',
            'Lean_dependency_closure': 'STATIC_ONLY_NOT_RUN'}

def compose(sources, records, parts):
    inv, comments, policy = helpers(sources)
    edits = Edits(sources['base'])
    pruned = prune(edits, sources)
    module_records = []
    expected_notices = Counter(comments['licence_hashes'](sources['base']))
    if 'direct' in parts:
        block = increment(sources['direct'], 'direct')
        old = final_wrapper(edits.data)
        edits.unique(old, block + b'\n\n' + old, 'insert_exact_DirectContinuous_namespace')
        edits.unique(final_wrapper(edits.data), final_wrapper(sources['direct']), 'connect_direct_final_dispatch_and_spec')
        module_records.append({'module': 'direct', 'increment_bytes': len(block), 'increment_sha256': sha(block)})
        expected_notices.update(comments['licence_hashes'](block))
    cross = next((k for k in ('cross', 'short') if k in parts), None)
    if cross:
        rename_final(edits, 'bmmBeforeR11Cross')
        block = increment(sources[cross], cross)
        edits.append(b'\n\n' + block, 'append_exact_' + cross + '_increment')
        module_records.append({'module': cross, 'increment_bytes': len(block), 'increment_sha256': sha(block)})
        expected_notices.update(comments['licence_hashes'](block))
    if 'underflow' in parts:
        rename_final(edits, 'bmmBeforeUnderflowZero')
        block = increment(sources['underflow'], 'underflow')
        edits.append(b'\n\n' + block, 'append_exact_underflow_increment_outermost')
        module_records.append({'module': 'underflow', 'increment_bytes': len(block), 'increment_sha256': sha(block)})
        expected_notices.update(comments['licence_hashes'](block))
    before_trim_bytes = len(edits.data)
    trimming = trim_blank_lines(edits, comments, parts)
    checks = static_verify(edits.data, parts, inv, policy)
    require(Counter(comments['licence_hashes'](edits.data)) == expected_notices, 'Author/licence/source paragraph bytes changed')
    edits.inverse()
    report = {'state': 'PASS_DRY_RUN_STATIC_ONLY', 'updated_at_utc': datetime.now(timezone.utc).isoformat(),
              'recipe': recipe_name(parts), 'inputs': records, 'selected_increments': module_records,
              'base_P_net_saved_already': 9441, 'additional_S1_S5_saved': 5011, 'additional_O1_O5_saved': 2837,
              'exact_pruned_spans': [{k: b[k] for k in ('id', 'name', 'bytes', 'sha256')} for b in pruned],
              'bytes_before_optional_blank_trim': before_trim_bytes, 'blank_line_only_trim': trimming,
              'candidate_sha256': sha(edits.data), 'candidate_bytes': len(edits.data), 'headroom_bytes': CAP - len(edits.data),
              'inverse_recovers_exact_compact_f2fa': True, 'inverse_base_sha256': sha(edits.initial),
              'preserved_notice_hash_counts': dict(expected_notices), 'static_checks': checks,
              'all_new_Lean_kernel_axiom_checksum_full_gate': 'NOT_RUN', 'performance': 'UNKNOWN_NOT_ADDITIVE',
              'formal_submission': 'NOT_SUBMITTED', 'Kernel_written': False, 'edit_ledger': edits.ledger}
    return edits.data, report, edits

def write_target(recipe_arg, target):
    require(recipe_arg is not None and bool(recipe_arg), '--write requires an explicit --recipe')
    require(target is not None, '--write requires --output-dir')
    target = Path(target)
    if not target.is_absolute() and len(target.parts) == 1:
        target = CANDIDATES / target
    target = target.resolve()
    require(target.parent == CANDIDATES.resolve() and re.fullmatch(r'f01-d11-[A-Za-z0-9][A-Za-z0-9_-]*', target.name),
            'Output must be a new f01-d11-* directory directly under candidates')
    require(not target.exists() and not target.is_symlink(), 'Refusing to overwrite existing destination')
    return target

def emit(raw, report, target):
    target.mkdir()
    with (target / 'Kernel.lean').open('xb') as f:
        f.write(raw)
    require((target / 'Kernel.lean').read_bytes() == raw, 'Written source bytes differ')
    report['Kernel_written'], report['destination'] = True, label(target)
    report['state'] = 'WRITTEN_EXACT_COMBINATION_NOT_LEAN_VERIFIED'
    manifest = {'candidate': target.name, 'candidate_file': 'Kernel.lean',
                'candidate_sha256': report['candidate_sha256'], 'candidate_bytes': len(raw),
                'created_at_utc': report['updated_at_utc'], 'parent': PINS['base'][0], 'parent_sha256': PINS['base'][1],
                'recipe': report['recipe'], 'component_sources': report['inputs'],
                'builder_sha256': report['builder_sha256'],
                'mechanism': 'Exact selected structural increments, reversible BMM/spec aliases; outer underflow miss -> Cross if selected -> DirectContinuous if selected / fused parent fallback. Exact S/O obsolete-chain pruning; ordinary blank lines only if required for cap.',
                'proof_status': 'NOT_RUN_NEW_COMBINATION', 'validation_mode': 'statement-only first; original full gate required',
                'kernel_replay': 'NOT_RUN', 'axiom_audit': 'NOT_RUN', 'checksum': 'NOT_RUN',
                'performance': 'UNKNOWN_NOT_ADDITIVE', 'formal_submission': 'NOT_SUBMITTED',
                'attribution': 'Exact selected module notices and common parent licence/source paragraphs preserved. Original candidates unchanged.'}
    for name, obj in [('manifest.json', manifest), ('composition-evidence.json', report)]:
        with (target / name).open('x', encoding='utf-8', newline='\n') as f:
            f.write(json.dumps(obj, indent=2, ensure_ascii=False) + '\n')

def self_test(sources, records):
    results = []
    for cross, zero, direct in itertools.product((None, 'cross', 'short'), (False, True), (False, True)):
        parts = tuple(k for k in (cross, 'underflow' if zero else None, 'direct' if direct else None) if k)
        raw, report, edits = compose(sources, records, parts)
        try:
            edits.inverse(raw + b' ')
            raise RuntimeError('Tampered inverse unexpectedly passed')
        except ValueError:
            pass
        results.append({k: report[k] for k in ('recipe', 'candidate_sha256', 'candidate_bytes', 'headroom_bytes', 'blank_line_only_trim')})
    for bad in ('cross+short', 'direct+direct', 'width8'):
        try:
            recipe_parts(bad)
            raise RuntimeError('Invalid recipe unexpectedly passed')
        except ValueError:
            pass
    for recipe, destination in [(None, 'f01-d11-test'), ('cross', None), ('cross', CANDIDATES / PINS['base'][0]), ('cross', ROOT / 'unrelated')]:
        try:
            write_target(recipe, destination)
            raise RuntimeError('Unsafe write target unexpectedly passed')
        except ValueError:
            pass
    _, _, original_policy = helpers(sources)
    rejected = original_policy['policy'](SimpleNamespace(read_text=lambda: sources['base'].decode() + '\n-- unsafe\n'), SimpleNamespace(slot='full'))
    require(rejected is not None and 'banned name' in rejected, 'Original policy negative control did not reject')
    return {'state': 'PASS_12_STRUCTURAL_RECIPES_AND_REFUSAL_TESTS', 'Kernel_written': False,
            'inputs': records, 'recipes': results, 'tests': ['All recipe caps/namespaces/exports/original policy',
            'Every inverse recovers exact f2fa', 'Tampered inverse rejected', 'Mutually exclusive/duplicate/unknown recipes rejected',
            'Missing explicit recipe/target and existing/outside destinations rejected', 'Exact original policy rejects in-memory banned-token negative control'],
            'Lean_full_gate_timing': 'NOT_RUN'}

def main():
    parser = ArgumentParser(description=__doc__)
    parser.add_argument('--recipe')
    parser.add_argument('--write', action='store_true')
    parser.add_argument('--output-dir', type=Path)
    parser.add_argument('--report', type=Path)
    parser.add_argument('--self-test', action='store_true')
    args = parser.parse_args()
    require(not args.self_test or not args.write, '--self-test never writes a candidate')
    require(args.write or args.output_dir is None, '--output-dir without --write is refused')
    destination = write_target(args.recipe, args.output_dir) if args.write else None
    parts = recipe_parts(args.recipe if args.recipe is not None else 'cross+underflow+direct')
    sources, records = snapshots()
    if args.self_test:
        report = self_test(sources, records)
        default_report = HERE / 'review-output-composition-selftest.json'
    else:
        raw, report, _ = compose(sources, records, parts)
        default_report = HERE / ('review-output-composition-' + recipe_name(parts).replace('+', '-') + '.json')
    report_path = (args.report or default_report).resolve()
    require(report_path.parent == HERE.resolve() and report_path.name.startswith('review-output-composition-')
            and report_path.suffix == '.json', 'Report must stay in owned review-output-composition-*.json scope')
    # Validate scope and all frozen source bytes before any candidate publication.
    snapshots()
    report['builder_sha256'] = sha(Path(__file__).read_bytes())
    if args.write:
        # write_target is repeated after all CPU-only preparation, closing a race
        # with a destination created while the dry-run checks were executing.
        destination = write_target(args.recipe, args.output_dir)
        emit(raw, report, destination)
    report_path.write_text(json.dumps(report, indent=2, ensure_ascii=False) + '\n', encoding='utf-8')
    keys = ('state', 'recipe', 'candidate_sha256', 'candidate_bytes', 'headroom_bytes', 'Kernel_written')
    print(json.dumps({k: report[k] for k in keys if k in report}, ensure_ascii=False))

if __name__ == '__main__':
    main()
