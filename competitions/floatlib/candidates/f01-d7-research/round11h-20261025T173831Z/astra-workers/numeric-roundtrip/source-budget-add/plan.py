"""Fresh B2 plus new-ADD reference census; emit deletion-only plan, never a candidate."""
from pathlib import Path
from datetime import datetime, timezone
import difflib
import hashlib
import importlib.util
import json
import re
import time

HERE = Path(__file__).resolve().parent
ROOT = next(p for p in HERE.parents if (p / 'AGENTS.md').exists())
PARENT = HERE.parent
BASE = ROOT / 'competitions/floatlib/candidates/f01-r15-dev-packed-b2-1/Kernel.lean'
OLD = ROOT / 'competitions/floatlib/candidates/f01-r16-dev-native-add-high3/Kernel.lean'
PREVIOUS = ROOT / 'competitions/floatlib/candidates/f01-d7-research/round3h-20261025T091810Z/astra-workers/source-budget/audit_budget.py'
EXPECTED = '622d8394a7127e93dcaf992c62c6dfcff7208d212738409a5e34525dfafd1a58'

def digest(raw):
    return hashlib.sha256(raw).hexdigest()

def binding(path):
    raw = path.read_bytes()
    return {'path': path.relative_to(ROOT).as_posix(), 'bytes': len(raw), 'sha256': digest(raw)}

start = time.monotonic()
spec = importlib.util.spec_from_file_location('old_lex', PREVIOUS)
oldlex = importlib.util.module_from_spec(spec)
spec.loader.exec_module(oldlex)
raw = BASE.read_bytes()
assert digest(raw) == EXPECTED
text = raw.decode('utf-8')
clean, comments, literals = oldlex.lex(text)
assert not literals

# Exact suffix only, rather than counting duplicated B2 declarations as references.
prefix = PARENT / 'Probe-high-u32-roundtrip-repair1.lean'
prefix_raw = prefix.read_bytes()
assert prefix_raw.startswith(raw)
assert digest(prefix_raw) == '01cff324ee8bd142ec9753a2ca72c9ecb7ca24cd8c1bcac9a0925e77fd5e4905'
fragments = [PARENT / f for f in [
    'Runtime-sorted-roundtrip-v1.lean.inc', 'Bridge-normalize-v1.lean.inc',
    'Threshold-from-inputs-v1.lean.inc', 'Threshold-word-lift-v1.lean.inc',
    'Output-model-bridge-v1.lean.inc']]
external_parts = [('frozen01cff-append-only', prefix_raw[len(raw):].decode('utf-8'))]
external_parts += [(p.name, p.read_text(encoding='utf-8')) for p in fragments]
oldtext = OLD.read_text(encoding='utf-8')
assert digest(OLD.read_bytes()) == 'f7f4702f9191061bb70a274610c9b735967ce4460ca2ef6ae121b9264fad18dd'
pos = 0
while True:
    a = oldtext.find('namespace Submission.A16L\n', pos)
    if a < 0:
        break
    b = oldtext.index('end Submission.A16L', a) + len('end Submission.A16L')
    external_parts.append(('old-full-gate-A16L-' + str(pos), oldtext[a:b]))
    pos = b
external_clean = '\n'.join(oldlex.lex(s)[0] for _, s in external_parts)

hazard_re = r'(?<!\w)(?:exact\?|apply\?|simp\?|rw\?|library_search\b|aesop\b|solve_by_elim\b|grind\b|run_tac\b|run_elab\b|mkConst\b|decl_name\b)'
hazards = re.findall(hazard_re, clean + '\n' + external_clean)
commands = re.findall(r'(?m)^\s*(?:attribute|export|notation|local\s+(?:notation|instance)|macro|syntax|elab|initialize)\b[^\n]*', clean + '\n' + external_clean)
assert not hazards and not commands, (hazards, commands)

cmds = list(oldlex.CMD.finditer(clean))
boundaries = [m.start() for m in cmds] + [len(text)]
ns_at = {}
scope = []
current = ''
for m in cmds:
    line = clean[m.start():clean.find('\n', m.start()) if '\n' in clean[m.start():] else len(clean)].strip()
    ns_at[m.start()] = current
    if line.startswith('namespace '):
        name = line.split()[1]
        scope.append(('namespace', current))
        current = current + '.' + name if current else name
    elif line.startswith('section'):
        scope.append(('section', current))
    elif line == 'end' or line.startswith('end '):
        assert scope, (m.start(), line)
        _, current = scope.pop()
assert not scope

all_rows = []
for decl in oldlex.DECL.finditer(clean):
    end = next(x for x in boundaries if x > decl.start())
    piece = text[decl.start():end]
    leaf = decl['name'].split('.')[-1]
    namespace = ns_at[decl.start()]
    fullname = namespace + '.' + decl['name'] if namespace else decl['name']
    prior = next((x for x in reversed(text[:decl.start()].splitlines()) if x.strip()), '')
    reasons = []
    if decl['kind'] not in ['theorem', 'lemma']:
        reasons.append('runtime_or_structure_or_instance_preserved')
    if decl['attr'] or prior.lstrip().startswith('@['):
        reasons.append('attribute_preserved')
    if '/-' in piece or '--' in piece:
        reasons.append('comment_bearing_slice_preserved')
    if oldlex.ATTRIBUTION.search(piece):
        reasons.append('provenance_preserved')
    if leaf in oldlex.PROTECTED:
        reasons.append('public_root_leaf_preserved')
    all_rows.append({'name': fullname, 'leaf': leaf, 'namespace': namespace,
                     'kind': decl['kind'], 'modifier': decl['modifier'].strip(),
                     'char_start': decl.start(), 'char_end': end,
                     'byte_start': len(text[:decl.start()].encode('utf-8')),
                     'byte_end_exclusive': len(text[:end].encode('utf-8')),
                     'line_start': text.count('\n', 0, decl.start()) + 1,
                     'line_end_exclusive': text.count('\n', 0, end) + 1,
                     'bytes': len(piece.encode('utf-8')), 'sha256': digest(piece.encode('utf-8')),
                     'header': piece.splitlines()[0], 'excluded_reasons': reasons})

def matches(leaf, body):
    # Also protects generated child-name prefixes, e.g. foo.eq_1.
    return list(re.finditer(r"(?<![\w'])" + re.escape(leaf) + r"(?![\w'])", body))

deleted = []
working = list(clean)
waves = []
for wave in range(1, 9):
    body = ''.join(working)
    eligible = []
    for row in all_rows:
        if row['excluded_reasons'] or row in deleted:
            continue
        own = matches(row['leaf'], body)
        extra = matches(row['leaf'], external_clean)
        if len(own) == 1 and row['char_start'] <= own[0].start() < row['char_end'] and not extra:
            eligible.append(row)
    if not eligible:
        break
    for row in eligible:
        row['wave'] = wave
        row['remaining_source_leaf_or_child_prefix_refs_at_removal'] = 1
        row['new_fragment_leaf_or_child_prefix_refs_at_removal'] = 0
        deleted.append(row)
        for i in range(row['char_start'], row['char_end']):
            if working[i] not in '\r\n':
                working[i] = ' '
    waves.append({'wave': wave, 'declarations': [r['name'] for r in eligible],
                  'recovered_bytes': sum(r['bytes'] for r in eligible),
                  'cumulative_recovered_bytes': sum(r['bytes'] for r in deleted)})
    if sum(r['bytes'] for r in deleted) >= 14336:
        break

deleted.sort(key=lambda r: r['byte_start'])
assert deleted
pieces = []
at = 0
for row in deleted:
    piece = raw[row['byte_start']:row['byte_end_exclusive']]
    assert digest(piece) == row['sha256']
    pieces.append(raw[at:row['byte_start']])
    at = row['byte_end_exclusive']
pieces.append(raw[at:])
replay = b''.join(pieces)
assert len(raw) - len(replay) == sum(r['bytes'] for r in deleted)
remaining = oldlex.lex(replay.decode('utf-8'))[0]
for row in deleted:
    assert not matches(row['leaf'], remaining)
    assert not matches(row['leaf'], external_clean)

# Reference evidence is measured against every retained declaration, not just the roots.
survivors = [r for r in all_rows if r not in deleted]
for row in deleted:
    refs = []
    for kept in survivors:
        body = clean[kept['char_start']:kept['char_end']]
        if matches(row['leaf'], body):
            refs.append(kept['name'])
    assert not refs
    row['retained_declaration_reference_hits'] = refs
    row['initial_reference_owners_removed_earlier'] = [
        other['name'] for other in deleted if other is not row and
        matches(row['leaf'], clean[other['char_start']:other['char_end']])]

patch = ''.join(difflib.unified_diff(text.splitlines(keepends=True), replay.decode('utf-8').splitlines(keepends=True),
                                  fromfile='a/competitions/floatlib/candidates/f01-r15-dev-packed-b2-1/Kernel.lean',
                                  tofile='b/competitions/floatlib/candidates/f01-r15-dev-packed-b2-1/Kernel.lean', n=3))
(HERE / 'b2-add-budget-delete.patch').write_bytes(patch.encode('utf-8'))
protected_hits = []
for row in all_rows:
    hits = matches(row['leaf'], external_clean)
    if hits:
        protected_hits.append({'name': row['name'], 'external_hits': len(hits), 'status': 'PRESERVED'})
namespaces = {}
for row in deleted:
    item = namespaces.setdefault(row['namespace'], {'bytes': 0, 'declarations': []})
    item['bytes'] += row['bytes']; item['declarations'].append(row['name'])

result = {
    'checked_utc': datetime.now(timezone.utc).isoformat(),
    'state': 'FRESH_EXTERNAL_REFERENCE_AWARE_PLAIN_THEOREM_PLAN_NOT_LEAN_VALIDATED',
    'source': binding(BASE), 'lexer_source': binding(PREVIOUS),
    'external_bindings': [binding(p) for p in [prefix, *fragments, OLD]],
    'external_coverage': [name for name, _ in external_parts],
    'selected': deleted, 'waves': waves, 'namespace_summary': namespaces,
    'protected_external_reference_hits': protected_hits,
    'saved_bytes': len(raw) - len(replay), 'result_bytes': len(replay), 'result_sha256': digest(replay),
    'patch_sha256': digest(patch.encode('utf-8')),
    'coordinate_units': 'byte_start/byte_end_exclusive are exact original UTF-8 byte offsets; char offsets separately provided; no source mutation occurred',
    'source_unchanged': BASE.read_bytes() == raw, 'candidate_emitted': False,
    'preserved_kinds': ['all runtime definitions', 'all structures and generated projections', 'all instances',
                        'all attributed declarations', 'all namespaces/open/variables/options', 'provenance comments',
                        'four public implementations and four public specs'],
    'risks': ['Lexical reference absence is not Lean elaboration or dependency checking.',
              'Unqualified references and generated child prefixes are conservatively counted, but implicit elaboration can still depend on declarations.',
              'No global search/reflection or explicit registration command was found; attributed declarations are excluded.',
              'The audit only binds the listed exact external fragments. New/repaired source requires refreshing this plan.',
              'Compilation, complete Submission replay, original specs and explicit helper dependency audit remain mandatory.'],
    'environment_search_hazards': hazards, 'registration_commands': commands,
    'retained_original_roots': ['Submission.add', 'Submission.add_spec', 'Submission.mul', 'Submission.mul_spec',
                                'Submission.sum', 'Submission.sum_spec', 'Submission.bmm', 'Submission.bmm_spec'],
    'known_264179_byte_chain_after_deletions_before_final_wiring': 264179 - (len(raw) - len(replay)),
    'Lean': 'NOT_RUN', 'kernel': 'NOT_RUN', 'helper_audit': 'NOT_RUN', 'full_gate': 'NOT_RUN',
    'tokens': 'UNKNOWN', 'CI_seconds': 0, 'elapsed_seconds': time.monotonic() - start,
}
assert result['source_unchanged']
(HERE / 'plan.json').write_bytes((json.dumps(result, indent=2, ensure_ascii=False) + '\n').encode('utf-8'))
print(json.dumps({k: result[k] for k in ['state', 'saved_bytes', 'result_bytes', 'result_sha256',
                                       'known_264179_byte_chain_after_deletions_before_final_wiring',
                                       'Lean', 'source_unchanged', 'elapsed_seconds']}, indent=2))
print(json.dumps({'waves': waves}, indent=2))
