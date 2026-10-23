"""Compose two exact accepted parents; default verifies without writing files."""
from pathlib import Path
from datetime import datetime, timezone
import argparse, ast, hashlib, json, re

HERE = Path(__file__).resolve().parent
ROOT = HERE.parents[3]
CANDIDATES = HERE.parent
REPORT = CANDIDATES / 'f01-d7-research/round1h-20261023T110107Z/astra-composition.json'
PINS = {
    'f01-d7-direct-nonnan': '60f74aa4af01a9b35ece66a7c310e6b05b5b84b9b7121a4cccd12a0a9c987e15',
    'f01-d7-result-guard-both-proof2': 'bee6ccdfec16d2b21810af4bea2389bcb2765e534b667cdc952188845227f183',
    'f01-d7-direct-singlepass-proof2': 'a84c1618cebe5892cbffd3657de8f2e6b96f0f70df2811af75c09a6ea3c5f736',
}

def sha(data):
    return hashlib.sha256(data).hexdigest()

def fixed(name):
    p = CANDIDATES / name / 'Kernel.lean'
    b = p.read_bytes()
    assert sha(b) == PINS[name], name
    s = b.decode('utf-8')
    assert '\r' not in s
    return s

def closed_block(text, name):
    start = text.index('\nnamespace ' + name + '\n', text.index('\nnamespace Submission\n'))
    end = text.index('\nend ' + name, start) + len('\nend ' + name)
    return text[start:end]

def interval(text, begin, end):
    assert text.count(begin) == 1
    a = text.index(begin)
    z = text.index(end, a)
    return text[a:z]

def compose(parent, donor, source_blocks):
    text = parent
    operations = []

    def replace_once(before, after, name):
        nonlocal text
        assert text.count(before) == 1, name
        offset = text.index(before)
        operations.append({'name': name, 'offset_in_previous_stage': offset,
                           'before': before, 'after': after,
                           'before_sha256': sha(before.encode()),
                           'after_sha256': sha(after.encode())})
        text = text[:offset] + after + text[offset + len(before):]

    for name, block in source_blocks.items():
        assert closed_block(text, name) == block
        replace_once(block, '', 'move_out_' + name)
    old_add_anchor = '/-- Raw exponent tests establish both native input conditions. -/'
    old_mul_anchor = '/-- Raw finite input guards retain the original multiplication fallback. -/'
    new_add_anchor = '/-- Classify the native result; raw NaN inputs/results retain exact fallback. -/'
    new_mul_anchor = '/-- Only a native NaN result requires the original raw-word fallback. -/'
    mul_export = '@[inline] def mul (x y : Binary32)'
    replace_once(old_add_anchor, '\n'.join(source_blocks.values()) + '\n\n' + old_add_anchor,
                 'move_in_exact_closed_blocks')
    gs = donor.index('namespace R7W04\n')
    gz = donor.index('end R7W04', gs) + len('end R7W04')
    guard = donor[gs:gz]
    assert text.count('namespace R7W04\n') == 0
    replace_once('import ContractTensor\n', 'import ContractTensor\n\n' + guard + '\n',
                 'insert_exact_R7W04')
    old_add = interval(text, old_add_anchor, old_mul_anchor)
    old_mul = interval(text, old_mul_anchor, mul_export)
    new_add = interval(donor, new_add_anchor, new_mul_anchor)
    new_mul = interval(donor, new_mul_anchor, mul_export)
    replace_once(old_add, new_add, 'replace_scalar_add_and_proof')
    replace_once(old_mul, new_mul, 'replace_scalar_nativeMul_and_proof')
    inverse = text
    for op in reversed(operations):
        at = op['offset_in_previous_stage']
        assert inverse[at:at + len(op['after'])] == op['after']
        inverse = inverse[:at] + op['before'] + inverse[at + len(op['after']):]
    assert inverse == parent
    return text, operations, guard

def strip_comments(text):
    # Nested block comments and strings are masked for command inventory only.
    out = []; i = depth = 0; string = False
    while i < len(text):
        if depth:
            if text.startswith('/-', i): depth += 1; out.extend('  '); i += 2
            elif text.startswith('-/', i): depth -= 1; out.extend('  '); i += 2
            else: out.append('\n' if text[i] == '\n' else ' '); i += 1
        elif string:
            if text[i] == '\\' and i + 1 < len(text): out.extend('  '); i += 2
            elif text[i] == '"': string = False; out.append(' '); i += 1
            else: out.append('\n' if text[i] == '\n' else ' '); i += 1
        elif text.startswith('/-', i): depth = 1; out.extend('  '); i += 2
        elif text.startswith('--', i):
            j = text.find('\n', i)
            if j < 0: j = len(text)
            out.extend(' ' * (j - i)); i = j
        elif text[i] == '"': string = True; out.append(' '); i += 1
        else: out.append(text[i]); i += 1
    assert depth == 0 and not string
    return ''.join(out)

def declarations(text):
    stack = []; found = {}
    for line_no, line in enumerate(strip_comments(text).splitlines(), 1):
        line = line.strip()
        m = re.fullmatch(r'namespace\s+([\w.]+)', line)
        if m: stack.append(('namespace', m.group(1))); continue
        m = re.fullmatch(r'(?:noncomputable\s+)?section(?:\s+([\w.]+))?', line)
        if m: stack.append(('section', m.group(1))); continue
        m = re.fullmatch(r'end(?:\s+([\w.]+))?', line)
        if m:
            assert stack, (line_no, line)
            kind, name = stack.pop()
            assert m.group(1) is None or m.group(1) == name, (line_no, name, line)
            continue
        m = re.match(r'(?:@\[[^\]]+\]\s*)?(?:(?:private|protected|noncomputable)\s+)*(?:def|theorem|abbrev)\s+([\w\u0080-\uffff.]+)', line)
        if m:
            qualified = '.'.join([name for kind, name in stack if kind == 'namespace'] + [m.group(1)])
            found.setdefault(qualified, []).append(line_no)
    assert not stack, stack
    return found

def main():
    ap = argparse.ArgumentParser(); ap.add_argument('--write', action='store_true'); args = ap.parse_args()
    base = fixed('f01-d7-direct-nonnan')
    donor = fixed('f01-d7-result-guard-both-proof2')
    parent = fixed('f01-d7-direct-singlepass-proof2')
    blocks = {name: closed_block(base, name) for name in ['NativeBridge', 'NotNaNProbe', 'R7Native']}
    for name, block in blocks.items():
        assert closed_block(donor, name) == block == closed_block(parent, name)
    reproduced, base_ops, guard = compose(base, donor, blocks)
    assert reproduced == donor, 'The proposed mechanical patch must reproduce ALL exact bee6 bytes.'
    new, ops, _ = compose(parent, donor, blocks)
    for left, right in zip(base_ops, ops):
        assert left['name'] == right['name'] and left['before'] == right['before'] and left['after'] == right['after']
    nb = new.encode(); assert len(nb) <= 256000
    # All a84-specific mathematical/runtime material follows the moved R7Native block.
    block_end = parent.index('\nend R7Native', parent.index('\nnamespace Submission\n')) + len('\nend R7Native')
    tail = parent[block_end:]
    assert new.endswith(tail)
    sp = parent[parent.index('namespace R7SinglePassSum\n'):]
    assert new.endswith(sp)
    decl = declarations(new)
    exports = ['Submission.' + name for name in ['add', 'add_spec', 'mul', 'mul_spec', 'sum', 'sum_spec', 'bmm', 'bmm_spec']]
    for name in exports: assert len(decl.get(name, [])) == 1, (name, decl.get(name))
    for name in ['NativeBridge', 'NotNaNProbe', 'R7Native']:
        for d in declarations(parent):
            if d.startswith('Submission.' + name + '.'):
                assert len(decl.get(d, [])) == 1, d
    assert new.count('namespace R7W04\n') == 1
    gate = ROOT / 'competitions/floatlib/research/astra-collab-20261023-r7/upstream/gate-4b7e838.py'
    assert sha(gate.read_bytes()) == '1eb74ef7479b0023c721e776cc5e4073af21c6662b4afffcf16a48a124d27194'
    tree = ast.parse(gate.read_text())
    def assignment(name):
        return next(n for n in tree.body if isinstance(n, ast.Assign) and any(isinstance(t, ast.Name) and t.id == name for t in n.targets))
    banned = re.compile(ast.literal_eval(assignment('BANNED').value.args[0])); assert not banned.search(new)
    opts = ast.literal_eval(assignment('OPTIONS').value); attrs = ast.literal_eval(assignment('ATTRIBUTES').value)
    env = {'re': re, 'OPTIONS': opts}; node = next(n for n in tree.body if isinstance(n, ast.FunctionDef) and n.name == 'options')
    exec(compile(ast.Module(body=[node], type_ignores=[]), str(gate), 'exec'), env)
    assert env['options'](new) is None
    assert [line for line in new.splitlines() if re.search(r'\bimport\b', line)] == ['import ContractTensor']
    for group in re.findall(r'@\[([^\]]*)\]', new):
        for item in group.split(','): assert item.split()[-1] in attrs
    now = datetime.now(timezone.utc).isoformat()
    manifest = {'candidate': HERE.name, 'candidate_file': 'Kernel.lean', 'candidate_sha256': sha(nb), 'candidate_bytes': len(nb),
                'created_at_utc': now, 'parents': {'runtime_parent': {'candidate': 'f01-d7-direct-singlepass-proof2', 'sha256': PINS['f01-d7-direct-singlepass-proof2']}, 'scalar_donor': {'candidate': 'f01-d7-result-guard-both-proof2', 'sha256': PINS['f01-d7-result-guard-both-proof2']}, 'patch_baseline': {'candidate': 'f01-d7-direct-nonnan', 'sha256': PINS['f01-d7-direct-nonnan']}},
                'mechanism': 'Exact accepted bee6 scalar native-result self-BEq guards and proofs on exact a84 singlepass-sum/direct-BMM parent. Move the same three closed proof/type-alias namespaces; insert exact W04; retain exact bee6 add-spec representation repair.',
                'source_boundary': 'Inverse patch recovers full a84. Entire a84 suffix following original R7Native end is byte-identical, including all repaired sum,NaN suffix,Nat/USize and BMM declarations. Scalar callees change, so tensor call-path performance is not inherited.',
                'validation_mode': 'full-gate', 'proof_status': 'NOT_RUN_EXACT_COMPOSITION', 'full_gate': 'NOT_RUN', 'codegen': 'NOT_RUN', 'performance': 'UNKNOWN', 'formal_submission': 'NOT_SUBMITTED',
                'attribution': 'All existing notices/licences retained; donor guard and scalar documentation copied byte-for-byte. No source minification.', 'build_script_sha256': sha(Path(__file__).read_bytes())}
    report = {'state': 'READY_STATIC_ONLY_EXACT_CI_NOT_RUN', 'recorded_at_utc': now, 'window_start_utc': '2026-10-23T11:01:07Z', 'candidate_target_utc': '2026-10-23T11:13:00Z', 'window_deadline_utc': '2026-10-23T12:01:07Z',
              'candidate': manifest, 'patch_reproduces_exact_bee6_from60f': True, 'same_seven_operations_apply_to_a84': True,
              'moved_blocks': {n: {'bytes': len(b.encode()), 'sha256': sha(b.encode()), 'identity_across_60f_bee6_a84': True} for n,b in blocks.items()},
              'guard': {'bytes': len(guard.encode()), 'sha256': sha(guard.encode())},
              'preserved_a84_tail': {'bytes': len(tail.encode()), 'sha256': sha(tail.encode()), 'byte_identical': True},
              'preserved_singlepass_namespace_and_exports': {'bytes': len(sp.encode()), 'sha256': sha(sp.encode()), 'byte_identical': True},
              'namespace_precheck': {'balanced': True, 'four_exports_and_four_specs': {n: decl[n] for n in exports}, 'moved_public_names_unique': True, 'R7W04_unique': True, 'scope': 'Lightweight command inventory, not Lean parsing/elaboration.'},
              'static_policy': {'original_gate_sha256': sha(gate.read_bytes()), 'bytes': len(nb), 'limit': 256000, 'margin': 256000-len(nb), 'result': 'PASS_STATIC_ONLY'},
              'operations': ops, 'inverse_parent_sha256': sha(parent.encode()),
              'next_falsifiable_checks': ['Exact combined statement under pinned Lean4.34/FloatLib settings; no missing moved namespace dependency or duplicate declaration', 'Original four specs,kernel replay,only three allowed axioms,all checksum cases', 'Same-runner a84 control and complete25pairedround public-v2; inspect scalar gains,NaN native-work regressions andsum/BMM cold callees', 'Freeze exact combined source and confirm with newseed/newrunner withoutobservers if discovery useful'],
              'restrictions': 'No Git,push,CI,web,subagent or otherthread action by this builder. No existing candidate mutated. No formal submission/funds.', 'gain': 'UNKNOWN; do not add standalone parent gains'}
    if args.write:
        assert not (HERE / 'Kernel.lean').exists()
        assert not (HERE / 'manifest.json').exists()
        assert not REPORT.exists()
        (HERE / 'Kernel.lean').write_bytes(nb)
        (HERE / 'manifest.json').write_text(json.dumps(manifest, ensure_ascii=False, indent=2) + '\n', encoding='utf-8')
        REPORT.parent.mkdir(parents=True, exist_ok=True)
        REPORT.write_text(json.dumps(report, ensure_ascii=False, indent=2) + '\n', encoding='utf-8')
    else:
        assert (HERE / 'Kernel.lean').read_bytes() == nb
        saved = json.loads((HERE / 'manifest.json').read_text())
        assert saved['candidate_sha256'] == sha(nb) and saved['candidate_bytes'] == len(nb)
    print(json.dumps({'sha256': sha(nb), 'bytes': len(nb), 'static': 'PASS', 'exact_compile': 'NOT_RUN', 'tail_preserved_bytes': len(tail.encode()), 'operations': len(ops)}, ensure_ascii=False))

if __name__ == '__main__':
    main()
