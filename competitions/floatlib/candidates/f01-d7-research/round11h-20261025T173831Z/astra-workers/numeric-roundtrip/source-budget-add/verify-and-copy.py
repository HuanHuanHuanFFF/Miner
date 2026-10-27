"""Independent unified-patch replay and reverse replay; emit only a private pruned B2 copy."""
from pathlib import Path
from datetime import datetime, timezone
import hashlib
import importlib.util
import json
import re

HERE = Path(__file__).resolve().parent
ROOT = next(p for p in HERE.parents if (p / 'AGENTS.md').exists())
PARENT = HERE.parent
plan = json.loads((HERE / 'plan.json').read_text(encoding='utf-8'))
source = ROOT / plan['source']['path']
raw = source.read_bytes()
digest = lambda b: hashlib.sha256(b).hexdigest()
assert digest(raw) == plan['source']['sha256']
patch = (HERE / 'b2-add-budget-delete.patch').read_bytes()
assert digest(patch) == plan['patch_sha256']

def apply_unified(data, reverse=False):
    old = data.decode('utf-8').splitlines(keepends=True)
    diff = patch.decode('utf-8').splitlines(keepends=True)
    assert diff[0].startswith('--- ') and diff[1].startswith('+++ ')
    output = []
    at = 0
    k = 2
    while k < len(diff):
        m = re.fullmatch(r'@@ -(\d+)(?:,(\d+))? \+(\d+)(?:,(\d+))? @@[^\n]*\n?', diff[k])
        assert m, diff[k]
        left_start, left_count = int(m[1]), int(m[2] or 1)
        right_start, right_count = int(m[3]), int(m[4] or 1)
        begin, consumed_expected, produced_expected = (
            (right_start - 1, right_count, left_count) if reverse else
            (left_start - 1, left_count, right_count))
        assert begin >= at
        output.extend(old[at:begin]); at = begin
        consumed = produced = 0
        k += 1
        while k < len(diff) and not diff[k].startswith('@@ '):
            line = diff[k]; k += 1
            tag, content = line[0], line[1:]
            assert tag in ' +-'
            if reverse and tag != ' ':
                tag = '+' if tag == '-' else '-'
            if tag in ' -':
                assert old[at] == content, (at, old[at], content)
                at += 1; consumed += 1
            if tag in ' +':
                output.append(content); produced += 1
        assert consumed == consumed_expected and produced == produced_expected
    output.extend(old[at:])
    return ''.join(output).encode('utf-8')

replay = apply_unified(raw)
assert digest(replay) == plan['result_sha256'] and len(replay) == plan['result_bytes']
reverse = apply_unified(replay, reverse=True)
assert reverse == raw

# A separately implemented exact-byte slice replay must agree with the line-based patch.
pieces = []
at = 0
for row in plan['selected']:
    removed = raw[row['byte_start']:row['byte_end_exclusive']]
    assert len(removed) == row['bytes'] and digest(removed) == row['sha256']
    pieces.append(raw[at:row['byte_start']]); at = row['byte_end_exclusive']
pieces.append(raw[at:])
assert b''.join(pieces) == replay

lexer = ROOT / plan['lexer_source']['path']
assert digest(lexer.read_bytes()) == plan['lexer_source']['sha256']
spec = importlib.util.spec_from_file_location('budget_lex', lexer)
lex = importlib.util.module_from_spec(spec); spec.loader.exec_module(lex)
clean_before = lex.lex(raw.decode('utf-8'))[0]
clean_after = lex.lex(replay.decode('utf-8'))[0]
frozen = PARENT / 'Probe-high-u32-roundtrip-repair2.lean'
frozen_raw = frozen.read_bytes()
assert digest(frozen_raw) == '0873268d474eb79301a929e744271c2c48ea547161ed52eda18b5e4aa4bd8fd9'
assert frozen_raw.startswith(raw)
extra = frozen_raw[len(raw):].decode('utf-8')
fragments = [PARENT / name for name in ['Runtime-sorted-roundtrip-v1.lean.inc', 'Bridge-normalize-v1.lean.inc',
    'Threshold-from-inputs-v1.lean.inc', 'Threshold-word-lift-v1.lean.inc', 'Output-model-bridge-v1.lean.inc']]
extra += '\n' + '\n'.join(p.read_text(encoding='utf-8') for p in fragments)
extra = lex.lex(extra)[0]
for row in plan['selected']:
    pattern = r"(?<![\w'])" + re.escape(row['leaf']) + r"(?![\w'])"
    assert not re.search(pattern, clean_after)
    assert not re.search(pattern, extra)

def controls(text):
    return [m.group(0) for m in re.finditer(r'(?m)^(?:namespace|section|end|open|variable|variables|instance|attribute|set_option|local|scoped|notation|syntax|macro|elab|initialize|export|include|omit|import)\b[^\n]*', text)]

assert controls(clean_before) == controls(clean_after)
assert re.findall(r'@\[[^\]]*\]', clean_before) == re.findall(r'@\[[^\]]*\]', clean_after)
assert all(row['kind'] in ['theorem', 'lemma'] and not row['excluded_reasons'] for row in plan['selected'])
private_copy = HERE / 'B2-ADD-budget-replay.lean'
private_copy.write_bytes(replay)
assert source.read_bytes() == raw
receipt = {
    'checked_utc': datetime.now(timezone.utc).isoformat(),
    'state': 'BYTE_REPLAY_AND_REVERSE_VERIFIED_PRIVATE_COPY_NOT_LEAN_VALIDATED',
    'original_sha256': digest(raw), 'private_copy': private_copy.name,
    'private_copy_sha256': digest(replay), 'private_copy_bytes': len(replay),
    'saved_bytes': len(raw) - len(replay), 'declarations_deleted': len(plan['selected']),
    'line_patch_forward': True, 'line_patch_reverse_exact_original': True,
    'independent_byte_slice_replay_matches': True,
    'namespace_open_variable_option_instance_sequence_unchanged': True,
    'attribute_sequence_unchanged': True,
    'runtime_declarations_and_all_public_root_leaves_preserved': True,
    'new0873_and_current_ADD_fragment_reference_census': 'NO_DELETED_LEAF_OR_GENERATED_CHILD_PREFIX_REFERENCE',
    'external_bindings': [{'path': p.relative_to(ROOT).as_posix(), 'sha256': digest(p.read_bytes())} for p in [frozen, *fragments]],
    'frozen_sources_unchanged': True,
    'warning': 'Verified byte mechanics and lexical absence only. The private pruned module and future combination still need pinned elaboration, full kernel replay, original specs and explicit helper audits. No semantic safety or performance claim.',
    'Lean': 'NOT_RUN', 'kernel': 'NOT_RUN', 'helper_audit': 'NOT_RUN', 'Git': False, 'CI': False,
}
(HERE / 'replay-verification.json').write_bytes((json.dumps(receipt, indent=2) + '\n').encode('utf-8'))
print(json.dumps(receipt, indent=2))
