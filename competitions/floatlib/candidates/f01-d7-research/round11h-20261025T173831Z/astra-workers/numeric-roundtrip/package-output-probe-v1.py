"""Package an independent output-model math probe; no compiler, Git or CI actions."""
from pathlib import Path
from datetime import datetime, timezone
from types import SimpleNamespace
import ast
import hashlib
import json
import re

HERE = Path(__file__).resolve().parent
ROOT = next(p for p in HERE.parents if (p / 'AGENTS.md').exists())
PREFIX = HERE / 'Probe-high-u32-roundtrip-repair1.lean'
NORMALIZE = HERE / 'Bridge-normalize-v1.lean.inc'
OUTPUT = HERE / 'Output-model-bridge-v1.lean.inc'
DEST = HERE / 'Probe-output-model-v1.lean'
GATE = ROOT / 'competitions/floatlib/research/astra-collab-20261023-r7/upstream/gate-4b7e838.py'
OLD = ROOT / 'competitions/floatlib/candidates/f01-r16-dev-native-add-high3/Kernel.lean'
UINT = ROOT / 'competitions/floatlib/candidates/f01-d7-research/round7h-20261023T193125Z/astra-Lean-UInt-Lemmas.lean'
UINT_RECEIPT = UINT.parent / 'astra-word-finish-source-receipts.json'

def binding(path):
    raw = path.read_bytes()
    return {'path': path.relative_to(ROOT).as_posix(), 'sha256': hashlib.sha256(raw).hexdigest(), 'bytes': len(raw)}

assert binding(PREFIX)['sha256'] == '01cff324ee8bd142ec9753a2ca72c9ecb7ca24cd8c1bcac9a0925e77fd5e4905'
assert binding(NORMALIZE)['sha256'] == 'bb8621c843a678ca3256faab9d8ea484db26c7b456da190e6a442bce9fb75505'
assert binding(OLD)['sha256'] == 'f7f4702f9191061bb70a274610c9b735967ce4460ca2ef6ae121b9264fad18dd'
assert binding(UINT)['sha256'] == 'faf52161e05982b8572e93928f7ec24b86d44d0d40c20fbf8d64cd2fd6c536b7'
assert binding(GATE)['sha256'] == '1eb74ef7479b0023c721e776cc5e4073af21c6662b4afffcf16a48a124d27194'
raw = PREFIX.read_bytes() + b'\n' + NORMALIZE.read_bytes() + b'\n' + OUTPUT.read_bytes()
assert b'\r' not in raw and len(raw) <= 256000
DEST.write_bytes(raw)
assert DEST.read_bytes().startswith(PREFIX.read_bytes())

tree = ast.parse(GATE.read_text(encoding='utf-8'))
env = {'re': re, 'Path': Path, 'Verdict': SimpleNamespace, '_MAX_BYTES': 256000,
       'SLOTS': {'full': SimpleNamespace(contract='ContractTensor')}}
for name in ['OPTIONS', 'ATTRIBUTES', 'BANNED']:
    node = next(n for n in tree.body if isinstance(n, ast.Assign) and any(
        isinstance(t, ast.Name) and t.id == name for t in n.targets))
    env[name] = re.compile(ast.literal_eval(node.value.args[0])) if name == 'BANNED' else ast.literal_eval(node.value)
fs = [n for n in tree.body if isinstance(n, ast.FunctionDef) and n.name in ['intake', 'policy', 'options']]
exec(compile(ast.Module(body=fs, type_ignores=[]), str(GATE), 'exec'), env)
checks = {'intake': env['intake'](DEST, SimpleNamespace(slot='full')),
          'policy': env['policy'](DEST, SimpleNamespace(slot='full')),
          'options': env['options'](DEST.read_text(encoding='utf-8'))}
assert all(x is None for x in checks.values())

old_roots = json.loads((HERE / 'repair1-manifest.json').read_text(encoding='utf-8'))['explicit_helper_audit']
new_roots = []
for path, namespace in [(NORMALIZE, 'Submission.R17NumericNormalize'), (OUTPUT, 'Submission.R17NumericOutput')]:
    new_roots += [namespace + '.' + name for name in re.findall(r'^theorem (\w+)', path.read_text(encoding='utf-8'), re.M)]
assert len(old_roots) == 22 and len(new_roots) == 8
roots = old_roots + new_roots
(HERE / 'OutputProbeAudit.lean.inc').write_bytes(('\n'.join('#print axioms ' + n for n in roots) + '\n').encode('utf-8'))
chain = [PREFIX, NORMALIZE, HERE / 'Runtime-sorted-roundtrip-v1.lean.inc',
         HERE / 'Threshold-from-inputs-v1.lean.inc', HERE / 'Threshold-word-lift-v1.lean.inc', OUTPUT]
out = {
    'created_utc': datetime.now(timezone.utc).isoformat(), 'phase': 'R18-3h30-20261026T081528Z',
    'state': 'OUTPUT_RECONSTRUCTION_TO_PUBLIC_ADD_MATH_PROBE_READY_NOT_COMPILED',
    'probe': binding(DEST), 'parts': [binding(p) for p in [PREFIX, NORMALIZE, OUTPUT]],
    'bindings': [binding(p) for p in [GATE, OLD, UINT, UINT_RECEIPT]],
    'policy': checks, 'comments_scanned': True, 'canonical_LF': True,
    'exact_prefix_01cff': True,
    'new_roots': new_roots, 'explicit_total_roots': roots,
    'requested_check': 'Statement elaboration, complete Submission kernel replay, all 30 explicit roots with only the standard 3 dependencies. Unchanged public specs are insufficient for these appended helpers.',
    'runtime_public_delta': 'NONE: original B2 four public implementations and specs retained through exact01cff prefix; no appended runtime ADD variant',
    'mathematical_delta': 'Prove masked UInt32 packing, actual output-E/shift arithmetic, numeric repack equals scaled Model.roundDyadic, and then equals ExecFloat.Spec.add under the existing exact alignment identity',
    'remaining_actual_entry_obligations': {
        'hs': 'Discharge using the existing frozen Threshold-word-lift-v1 same/opposite final theorems; those remain uncompiled and are not duplicated in this probe',
        'he': 'word_exponent_shift_relation instantiates the actual ehi/elo/gap/adjust/bump locals; old sorted-gap arithmetic supplies its premise',
        'halign': 'Use exact original-order R16AddWord.raw_add_dyadic plus magW_nat after relating the single-sort locals to old high/low definitions',
        'guards': 'Original normal, gap/sign and high-N bounds; upper E comparison; fallback spec for all rejects',
    },
    'probe_bytes_remaining': 256000 - len(raw),
    'naive_known_chain_bytes_without_separators_or_old_alignment_support': sum(p.stat().st_size for p in chain),
    'source_size_conclusion': 'The independent output probe fits. Naively appending every frozen fragment already exceeds256000 before old alignment/public wiring. Full candidate requires exact dependency extraction/compaction and fresh validation; no source was pruned here.',
    'compile': 'NOT_RUN', 'kernel': 'NOT_RUN', 'axiom_audit': 'NOT_RUN', 'performance': 'UNKNOWN',
    'local_Lean': False, 'Git': False, 'CI': False,
    'tokens': {'input': 'UNKNOWN', 'cached_input': 'UNKNOWN', 'output': 'UNKNOWN', 'reasoning': 'UNKNOWN'},
}
(HERE / 'output-probe-v1-manifest.json').write_bytes((json.dumps(out, indent=2, ensure_ascii=False) + '\n').encode('utf-8'))
print(json.dumps({k: out[k] for k in ['state', 'probe', 'policy', 'probe_bytes_remaining',
                                     'naive_known_chain_bytes_without_separators_or_old_alignment_support',
                                     'compile', 'performance']}, indent=2))
