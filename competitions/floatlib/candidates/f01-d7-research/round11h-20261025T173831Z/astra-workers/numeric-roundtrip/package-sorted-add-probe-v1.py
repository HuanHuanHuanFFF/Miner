"""Assemble the bounded pruned mathematical chain; public entry remains exact B2."""
from pathlib import Path
from datetime import datetime, timezone
from types import SimpleNamespace
import ast
import hashlib
import json
import re

HERE = Path(__file__).resolve().parent
ROOT = next(p for p in HERE.parents if (p / 'AGENTS.md').exists())
ROUND = HERE.parents[1]
BASE = ROOT / 'competitions/floatlib/candidates/f01-r15-dev-packed-b2-1/Kernel.lean'
PRUNED = HERE / 'source-budget-add/B2-ADD-budget-replay.lean'
FOUNDATION = HERE / 'Probe-high-u32-roundtrip-repair2.lean'
OLD = ROOT / 'competitions/floatlib/candidates/f01-r16-dev-native-add-high3/Kernel.lean'
GATE = ROOT / 'competitions/floatlib/research/astra-collab-20261023-r7/upstream/gate-4b7e838.py'

def sha(b): return hashlib.sha256(b).hexdigest()
def binding(p):
    b = p.read_bytes()
    return {'path': p.relative_to(ROOT).as_posix(), 'sha256': sha(b), 'bytes': len(b)}

assert binding(BASE)['sha256'] == '622d8394a7127e93dcaf992c62c6dfcff7208d212738409a5e34525dfafd1a58'
assert binding(PRUNED)['sha256'] == '775b76fb787b4dfbf8864a091f5f40ac21537d184ebf62752f6aebe8fc4ecc83'
assert binding(FOUNDATION)['sha256'] == '0873268d474eb79301a929e744271c2c48ea547161ed52eda18b5e4aa4bd8fd9'
assert binding(OLD)['sha256'] == 'f7f4702f9191061bb70a274610c9b735967ce4460ca2ef6ae121b9264fad18dd'
assert binding(GATE)['sha256'] == '1eb74ef7479b0023c721e776cc5e4073af21c6662b4afffcf16a48a124d27194'
feedback_path = ROUND / 'development-proof-f01-r17-dev-u32-roundtrip-repair2-40296747927.json'
feedback = json.loads(feedback_path.read_text(encoding='utf-8'))
audit_path = ROOT / feedback['extra_helper_audit']['path']
assert binding(audit_path)['sha256'] == feedback['extra_helper_audit']['sha256']
audit = json.loads(audit_path.read_text(encoding='utf-8'))
assert audit['accepted'] and audit['kernel_replay'] and len(audit['names']) == 22

oldraw = OLD.read_bytes()
oldtext = oldraw.decode('utf-8')
pos = 0; alignment = []; maps = []
while True:
    a = oldtext.find('namespace Submission.A16L\n', pos)
    if a < 0: break
    b = oldtext.index('end Submission.A16L', a) + len('end Submission.A16L')
    if b < len(oldtext) and oldtext[b] == '\n': b += 1
    piece = oldtext[a:b].encode('utf-8')
    alignment.append(piece)
    maps.append({'original_byte_start': len(oldtext[:a].encode('utf-8')),
                 'original_byte_end_exclusive': len(oldtext[:b].encode('utf-8')),
                 'sha256': sha(piece), 'bytes': len(piece), 'transform': 'NONE'})
    pos = b
align_path = HERE / 'Old-A16L-alignment-exact.lean.inc'
align_path.write_bytes(b''.join(alignment))
assert align_path.stat().st_size == 4392
base = BASE.read_bytes(); foundation = FOUNDATION.read_bytes()
assert foundation.startswith(base)
tail = foundation[len(base):]
tail_path = HERE / 'Verified-u32-foundation-tail.lean.inc'
tail_path.write_bytes(tail)
parts = [PRUNED, tail_path,
         HERE / 'Bridge-normalize-v1.lean.inc', HERE / 'Threshold-from-inputs-v1.lean.inc',
         HERE / 'Threshold-word-lift-v1.lean.inc', HERE / 'Output-model-bridge-v1.lean.inc',
         align_path, HERE / 'Sorted-word-alignment-v1.lean.inc', HERE / 'Runtime-sorted-roundtrip-v1.lean.inc']
raw = b'\n'.join(p.read_bytes() for p in parts)
assert len(raw) <= 256000 and b'\r' not in raw
probe = HERE / 'Probe-sorted-add-chain-v1.lean'
probe.write_bytes(raw)

# Every deleted theorem must remain absent from the complete retained source.
plan = json.loads((HERE / 'source-budget-add/plan.json').read_text(encoding='utf-8'))
for row in plan['selected']:
    assert not re.search(r"(?<![\w'])" + re.escape(row['leaf']) + r"(?![\w'])", raw.decode('utf-8'))

tree = ast.parse(GATE.read_text(encoding='utf-8'))
env = {'re': re, 'Path': Path, 'Verdict': SimpleNamespace, '_MAX_BYTES': 256000,
       'SLOTS': {'full': SimpleNamespace(contract='ContractTensor')}}
for name in ['OPTIONS', 'ATTRIBUTES', 'BANNED']:
    n = next(n for n in tree.body if isinstance(n, ast.Assign) and any(
        isinstance(t, ast.Name) and t.id == name for t in n.targets))
    env[name] = re.compile(ast.literal_eval(n.value.args[0])) if name == 'BANNED' else ast.literal_eval(n.value)
fs = [n for n in tree.body if isinstance(n, ast.FunctionDef) and n.name in ['intake', 'policy', 'options']]
exec(compile(ast.Module(body=fs, type_ignores=[]), str(GATE), 'exec'), env)
checks = {'intake': env['intake'](probe, SimpleNamespace(slot='full')),
          'policy': env['policy'](probe, SimpleNamespace(slot='full')),
          'options': env['options'](probe.read_text(encoding='utf-8'))}
assert all(v is None for v in checks.values())

roots = list(audit['names'])
root_groups = {'foundation22_original0873_passed_only': list(audit['names'])}
groups = [(parts[2], 'Submission.R17NumericNormalize'), (parts[3], 'Submission.R17Threshold'),
          (parts[4], 'Submission.R17Threshold'), (parts[5], 'Submission.R17NumericOutput'),
          (align_path, 'Submission.A16L'), (parts[7], 'Submission.R18SortedWord'),
          (parts[8], 'Submission.R17NumericAdd')]
for path, namespace in groups:
    names = [namespace + '.' + name for name in re.findall(
        r'^(?:@\[[^\]]*\]\s*)?(?:def|abbrev|theorem) (\w+)', path.read_text(encoding='utf-8'), re.M)]
    roots += names; root_groups[path.name] = names
assert len(roots) == len(set(roots)) == 63
(HERE / 'SortedAddChainAudit.lean.inc').write_bytes(('\n'.join('#print axioms ' + n for n in roots) + '\n').encode('utf-8'))
remaining = {
    'public_entry_and_fallback': 'Still B2. The new guardedAdd helper is appended only and has no public spec yet.',
    'normal_guard': 'Convert each eu-1<=253 word guard into 1<=wordExp<255; the old normal_field proof can be instantiated.',
    'single_sort': 'Two wrapper branches must relate hi/lo/ehi/elo to original x/y and preserve equal-exponent left bias.',
    'gap_domain': 'Use UInt32.toNat_sub_of_le once after sorting; derive same-sign OR gap>=1 from adjust<=gap.',
    'magnitude': 'New magnitude_word_nat plus old A16L.magnitude_bounds closes no-wrap and the upper N bound; high guard supplies the lower bound.',
    'shift': 'The two frozen word-threshold final theorems discharge actual normalization shift; not yet compiled in this combination.',
    'exponent': 'word_exponent_shift_relation supplies E=elo+shift; actual upper E guard and normal elo feed numeric_pack_model.',
    'alignment': 'New high_low_model/low_high_model produces the exact original-order dyadic identity required by numeric_add_of_alignment.',
    'all_rejects': 'Must discharge using the original B2 fallback spec, including nonnormal, zero/low-N, disallowed gaps/signs and overflow.',
    'byte_budget': 'This math chain preserves all current helper roots. Only remaining bytes shown below are available for public wiring; further exact dependency work may be needed.',
}
manifest = {
    'created_utc': datetime.now(timezone.utc).isoformat(),
    'state': 'BOUNDED_COMPLETE_MATH_CHAIN_READY_PUBLIC_ADD_NOT_WIRED',
    'probe': binding(probe), 'bytes_remaining': 256000 - len(raw),
    'parts': [binding(p) for p in parts], 'alignment_exact_original_ranges': maps,
    'foundation_evidence': [binding(feedback_path), binding(audit_path)],
    'pruning_receipt': binding(HERE / 'source-budget-add/replay-verification.json'),
    'pruned_copy_status': 'Forward/reverse byte mechanics verified; semantic safety NOT_COMPILED.',
    'original_text_checks': checks, 'comments_scanned': True, 'canonical_LF': True,
    'root_groups': root_groups, 'explicit_roots': roots, 'root_count': len(roots),
    'inherited_validation': 'Only original0873 and its22 roots were accepted. No validity is inherited by this pruned or extended module; 32b/threshold/output/new alignment remain pending.',
    'remaining_public_spec_obligations': remaining,
    'requested_validation': 'Compile this exact module, replay complete Submission/VerifyFull, audit all63 roots. Full public runtime/performance gate is later after actual wiring.',
    'compile': 'NOT_RUN', 'kernel': 'NOT_RUN', 'helper_audit': 'NOT_RUN', 'full_gate': 'NOT_RUN', 'performance': 'UNKNOWN',
    'new_public_runtime': False, 'old_frozen_sources_unchanged': True,
    'tokens': 'UNKNOWN', 'CI_seconds': 0,
}
(HERE / 'sorted-add-chain-v1-manifest.json').write_bytes((json.dumps(manifest, indent=2, ensure_ascii=False) + '\n').encode('utf-8'))
print(json.dumps({k: manifest[k] for k in ['state', 'probe', 'bytes_remaining', 'root_count',
                                          'original_text_checks', 'compile', 'new_public_runtime']}, indent=2))
