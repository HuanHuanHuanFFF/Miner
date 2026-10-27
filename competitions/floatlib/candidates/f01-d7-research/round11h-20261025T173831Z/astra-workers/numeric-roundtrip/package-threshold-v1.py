"""Check fixed source/policy bindings for the focused threshold proof attempts; no Lean or Kernel."""
from pathlib import Path
from datetime import datetime, timezone
from types import SimpleNamespace
import ast
import hashlib
import json
import re

HERE = Path(__file__).resolve().parent
ROOT = next(p for p in HERE.parents if (p / 'AGENTS.md').exists())
GATE = ROOT / 'competitions/floatlib/research/astra-collab-20261023-r7/upstream/gate-4b7e838.py'
UPROOT = ROOT / 'competitions/floatlib/candidates/f01-d7-research/round8h-20261024T190259Z'
SHIFT = UPROOT / 'astra-upstream/FloatLib/Numerics/Quantization/Deterministic/ShiftRight.lean'
INDEX = UPROOT / 'astra-upstream-index.json'
PROBE = HERE / 'Probe-high-u32-roundtrip-repair1.lean'
RUNTIME = HERE / 'Runtime-sorted-roundtrip-v1.lean.inc'

def binding(p):
    raw = p.read_bytes()
    return {'path': p.relative_to(ROOT).as_posix(), 'sha256': hashlib.sha256(raw).hexdigest(), 'bytes': len(raw)}

assert binding(PROBE)['sha256'] == '01cff324ee8bd142ec9753a2ca72c9ecb7ca24cd8c1bcac9a0925e77fd5e4905'
assert binding(RUNTIME)['sha256'] == 'e08543ac5c20cd53c39b010edfc684226032926418ea3125df8aa4a3805f799e'
assert binding(GATE)['sha256'] == '1eb74ef7479b0023c721e776cc5e4073af21c6662b4afffcf16a48a124d27194'
raw = SHIFT.read_bytes()
blob = hashlib.sha1(b'blob ' + str(len(raw)).encode() + b'\0' + raw).hexdigest()
assert blob == 'd53bd9ec15f51006a945e3c49d7c3e1d3185af19'
assert '0d91825727839f597fd06b22fdd038ea21480f0c/FloatLib/Numerics/Quantization/Deterministic/ShiftRight.lean' in INDEX.read_text(encoding='utf-8')
for decl in ['roundShiftRightEven_one', 'roundShiftRightEven_le_shiftRight_add1']:
    assert re.search(r'^theorem ' + decl + r'\b', raw.decode(), re.M)

paths = [HERE / 'Threshold-from-inputs-v1.lean.inc', HERE / 'Threshold-word-lift-v1.lean.inc']
tree = ast.parse(GATE.read_text(encoding='utf-8'))
env = {'re': re, 'Path': Path, 'Verdict': SimpleNamespace, '_MAX_BYTES': 256000,
       'SLOTS': {'full': SimpleNamespace(contract='ContractTensor')}}
for name in ['OPTIONS', 'ATTRIBUTES', 'BANNED']:
    n = next(n for n in tree.body if isinstance(n, ast.Assign) and any(
        isinstance(t, ast.Name) and t.id == name for t in n.targets))
    env[name] = re.compile(ast.literal_eval(n.value.args[0])) if name == 'BANNED' else ast.literal_eval(n.value)
fs = [n for n in tree.body if isinstance(n, ast.FunctionDef) and n.name in ['intake', 'policy', 'options']]
exec(compile(ast.Module(body=fs, type_ignores=[]), str(GATE), 'exec'), env)
checks = {}
roots = []
for p in paths:
    assert b'\r' not in p.read_bytes()
    text = p.read_text(encoding='utf-8')
    checks[p.name] = {'intake': env['intake'](p, SimpleNamespace(slot='full')),
                     'policy': env['policy'](p, SimpleNamespace(slot='full')),
                     'options': env['options'](text)}
    roots += ['Submission.R17Threshold.' + name for name in re.findall(r'^(?:abbrev|theorem) (\w+)', text, re.M)]
assert all(value is None for result in checks.values() for value in result.values())
assert len(roots) == 18 and len(set(roots)) == 18

numeric = (HERE / 'threshold-arithmetic-check.json').read_bytes()
numeric_result = json.loads(numeric)
assert numeric_result['source_sha256'] == binding(HERE / 'check-threshold-arithmetic.py')['sha256']
out = {
    'created_utc': datetime.now(timezone.utc).isoformat(),
    'state': 'ORIGINAL_DOMAIN_DERIVATION_AND_WORD_SHIFT_ATTEMPTS_DELIVERED_NOT_COMPILED',
    'artifacts': [binding(p) for p in paths],
    'paper': binding(HERE / 'threshold-proof.md'),
    'arithmetic_check': binding(HERE / 'threshold-arithmetic-check.json'),
    'sources': [binding(p) for p in [PROBE, RUNTIME, GATE, SHIFT, INDEX]],
    'fixed_ShiftRight_git_blob_sha1': blob,
    'fixed_ShiftRight_url': 'https://github.com/lean-dojo/FloatLib/blob/0d91825727839f597fd06b22fdd038ea21480f0c/FloatLib/Numerics/Quantization/Deterministic/ShiftRight.lean',
    'original_text_checks': checks, 'comments_scanned': True,
    'text_check_scope': 'Fragments only; no new full Kernel was assembled',
    'explicit_new_roots': roots,
    'original_domain': '2^23 <= a,b < 2^24, d <= 7; same sign N=a*2^d+b; opposite d>=1 and N=a*2^d-b>=2^23',
    'final_Nat_targets': ['same_threshold_from_inputs', 'opposite_threshold_from_inputs'],
    'final_word_targets': ['same_word_shift_from_inputs', 'opposite_word_shift_from_inputs'],
    'new_normalization_assumption_in_final_targets': False,
    'retained_word_interface_premise': 'n.toNat equals the original aligned Nat magnitude; this must be supplied by the old exact no-wrap alignment proof, not assumed in the public spec',
    'pending_foundation': ['R14NatNormal.carry_le', 'R16UInt32Roundtrip.rounded_leading',
                           'R16UInt32Roundtrip.high_mantissa', 'R16UInt32Roundtrip.high_roundtrip'],
    'frozen_01cff_unchanged': True, 'frozen_e085_unchanged': True,
    'new_runtime_variant': False, 'new_complete_Kernel': False,
    'compile': 'NOT_RUN', 'kernel': 'NOT_RUN', 'axiom_audit': 'NOT_RUN', 'performance': 'NOT_RUN',
    'scope_of_arithmetic_check': 'All exponent-case constants and all four d=0 residues; not native floating semantics or proof elaboration',
    'stop_reason': 'Focused proof chain and paper derivation are complete as drafts; pinned compilation resources remain unavailable pending D startup authorization. No further proof family or runtime variant is opened.',
    'tokens': {'input': 'UNKNOWN', 'cached_input': 'UNKNOWN', 'output': 'UNKNOWN', 'reasoning': 'UNKNOWN'},
    'CI_minutes': 0,
}
(HERE / 'threshold-v1-manifest.json').write_bytes((json.dumps(out, indent=2, ensure_ascii=False) + '\n').encode('utf-8'))
print(json.dumps({k: out[k] for k in ['state', 'artifacts', 'original_text_checks',
                                     'new_normalization_assumption_in_final_targets',
                                     'frozen_01cff_unchanged', 'frozen_e085_unchanged', 'compile']}, indent=2))
