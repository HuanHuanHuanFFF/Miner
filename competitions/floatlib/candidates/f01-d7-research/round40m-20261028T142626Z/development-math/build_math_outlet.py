"""R23 source-only repair; no Lean, compilation, Git, or CI calls."""
from pathlib import Path
import difflib
import datetime
import hashlib
import json
import re

HERE = Path(__file__).resolve().parent
ROOT = next(p for p in HERE.parents if (p / 'AGENTS.md').is_file())
OLD = ROOT / 'competitions/floatlib/candidates/f01-d7-research/round6h-20261027T211247Z'
BASE = OLD / 'development-nat-light-repair/MathOutletLightExplicit.lean'
V2 = OLD / 'development-outline-mul/math-repair/MathOutletFinalThreeFixV2.lean'
sha = lambda b: hashlib.sha256(b).hexdigest()
base = BASE.read_bytes()
assert sha(base) == 'fbd94c3f298ef606c88d29efa9a75f26c43faefee9229f0fdfd80bc55442dd5e'
v2 = V2.read_bytes()
assert sha(v2) == '4583f5f76ece3762ac81c621ab14f6138d9f936225c903e19db7b57290227ca5'
original = base.decode()
typed = original
type_replacements = [
    ('p+4194303+((p >>> 23) &&& 1)',
     'p+(4194303 : UInt64)+((p >>> (23 : UInt64)) &&& (1 : UInt64))'),
    ('p+8388607+((p >>> 24) &&& 1)',
     'p+(8388607 : UInt64)+((p >>> (24 : UInt64)) &&& (1 : UInt64))'),
]
for before, after in type_replacements:
    assert typed.count(before) == 2
    typed = typed.replace(before, after)

# Transfer only the three known insertions; never replace a complete repaired file.
before_lines, after_lines = original.splitlines(keepends=True), v2.decode().splitlines(keepends=True)
insertions = []
for tag, a0, a1, b0, b1 in difflib.SequenceMatcher(None, before_lines, after_lines, autojunk=False).get_opcodes():
    if tag == 'equal':
        continue
    assert tag == 'insert' and a0 == a1
    context = ''.join(before_lines[max(0, a0-2):a0+2])
    replacement = ''.join(before_lines[max(0, a0-2):a0]) + ''.join(after_lines[b0:b1]) + ''.join(before_lines[a0:a0+2])
    assert typed.count(context) == 1
    insertions.append((context, replacement))
assert len(insertions) == 3
repaired = typed
for context, replacement in insertions:
    repaired = repaired.replace(context, replacement, 1)
reversed_text = repaired
for context, replacement in reversed(insertions):
    reversed_text = reversed_text.replace(replacement, context, 1)
assert reversed_text == typed
for before, after in type_replacements:
    reversed_text = reversed_text.replace(after, before)
assert reversed_text == original

def signatures(text):
    return re.findall(r'(?m)^(?:private )?theorem\s+.*?\s:=', text, re.S)
assert signatures(original) == signatures(repaired)
declaration_start = re.compile(r'(?m)^(?:@\[[^\n]*\] )?(?:private )?(?:def|theorem) |^end |^namespace |^#print ')
def get_def(text, name):
    match = re.search(r'(?m)^(?:@\[[^\n]*\] )?def ' + re.escape(name) + r'\b', text)
    assert match
    end = declaration_start.search(text, match.end())
    return text[match.start():end.start() if end else len(text)].rstrip()
runtime_names = ['normalCore', 'guardedMul', 'diagnosticEntry']
runtime = {name: {'byte_identical': get_def(original, name) == get_def(repaired, name),
                  'sha256': sha(get_def(repaired, name).encode())} for name in runtime_names}
assert all(row['byte_identical'] for row in runtime.values())
typed_definition = get_def(repaired, 'biasedWord')
for before, after in type_replacements:
    typed_definition = typed_definition.replace(after, before)
assert typed_definition == get_def(original, 'biasedWord')
roots = re.findall(r'(?m)^#print axioms (\S+)$', repaired)
old_manifest = json.loads((ROOT / 'competitions/floatlib/candidates/f01-r22-dev-nat-light-repair1/manifest.json').read_text())
assert roots == old_manifest['math_outlet_expected_roots'] and len(roots) == len(set(roots)) == 48
assert not re.search(r'\b(?:sorry|admit|axiom|unsafe|implemented_by|extern)\b', repaired)
out = HERE / 'MathOutletR23Fix1.lean'
out.write_bytes(repaired.encode())
for name, a, b in [('four-hadd-fix.patch', original, typed), ('three-final-fix.patch', typed, repaired), ('all-fixes.patch', original, repaired)]:
    (HERE / name).write_text(''.join(difflib.unified_diff(a.splitlines(True), b.splitlines(True), fromfile='MathOutlet-fbd94.lean', tofile='MathOutletR23Fix1.lean')), encoding='utf-8', newline='')
(HERE / 'roots48.json').write_text(json.dumps(roots, indent=2)+'\n', encoding='utf-8')
manifest = {
    'state': 'SOURCE_REPAIR_NOT_RUN', 'created_at_utc': datetime.datetime.now(datetime.timezone.utc).isoformat(),
    'window_start_utc': '2026-10-28T14:26:26Z', 'window_cutoff_utc': '2026-10-28T15:06:26Z',
    'file': out.relative_to(ROOT).as_posix(), 'sha256': sha(out.read_bytes()), 'bytes': out.stat().st_size,
    'base': {'path': BASE.relative_to(ROOT).as_posix(), 'sha256': sha(base), 'bytes': len(base)},
    'v2_source': {'sha256': sha(v2), 'only_insertions_transferred': 3},
    'four_hadd_fix_intermediate_sha256': sha(typed.encode()),
    'd8_complete_repaired_source': 'NOT_LOCATED; d8c5cb7f is unrelated 3076-byte NatBiasSeparated. No identity inferred.',
    'theorem_statement_count': len(signatures(original)), 'all_theorem_statements_byte_identical': True,
    'all_other_source_bytes_reversible_to_base': True, 'runtime_definitions': runtime,
    'biasedWord': 'Only explicit UInt64 annotations on original constants; stripping those exact annotations recovers original definition bytes.',
    'math_outlet_expected_roots': roots, 'expected_axiom_reports': 48,
    'allowed_axioms': ['propext', 'Classical.choice', 'Quot.sound'],
    'heartbeat': 'Only normalCore_eq_roundP gets local maxHeartbeats 1000000; original process memory/caps/gate untouched.',
    'typing': 'NOT_RUN', 'axiom_audit': 'NOT_RUN', 'kernel_replay': 'NOT_RUN',
    'full_public_kernel': 'NOT_BUILT', 'performance': 'NOT_RUN', 'token': 'UNKNOWN', 'cache_input': 'UNKNOWN',
}
(HERE / 'manifest.json').write_text(json.dumps(manifest, indent=2)+'\n', encoding='utf-8')
print(json.dumps({k: manifest[k] for k in ['state','file','sha256','bytes','four_hadd_fix_intermediate_sha256','theorem_statement_count']}))
