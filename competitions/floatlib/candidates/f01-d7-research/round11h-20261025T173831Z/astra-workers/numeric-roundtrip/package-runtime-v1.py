"""Bind runtime fragments and original text policy; never assemble or compile a new Kernel."""
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
BASE = ROOT / 'competitions/floatlib/candidates/f01-r15-dev-packed-b2-1/Kernel.lean'
OLD = ROOT / 'competitions/floatlib/candidates/f01-r16-dev-native-add-high3/Kernel.lean'
FROZEN = HERE / 'Probe-high-u32-roundtrip-repair1.lean'
HEADER = ROOT / 'competitions/floatlib/candidates/f01-d7-research/round3h-20261025T043928Z/astra-workers/public-source-runtime/sources/lean-header.txt'

def binding(p):
    raw = p.read_bytes()
    return {'path': p.relative_to(ROOT).as_posix(), 'sha256': hashlib.sha256(raw).hexdigest(), 'bytes': len(raw)}

assert binding(GATE)['sha256'] == '1eb74ef7479b0023c721e776cc5e4073af21c6662b4afffcf16a48a124d27194'
assert binding(BASE)['sha256'] == '622d8394a7127e93dcaf992c62c6dfcff7208d212738409a5e34525dfafd1a58'
assert binding(OLD)['sha256'] == 'f7f4702f9191061bb70a274610c9b735967ce4460ca2ef6ae121b9264fad18dd'
assert binding(FROZEN)['sha256'] == '01cff324ee8bd142ec9753a2ca72c9ecb7ca24cd8c1bcac9a0925e77fd5e4905'
assert binding(HEADER)['sha256'] == '982c731a1fbacc7688006f44f9f7af9d9e3e0247d310a728827f49e7f1466c13'
runtime = HERE / 'Runtime-sorted-roundtrip-v1.lean.inc'
lemmas = HERE / 'Bridge-normalize-v1.lean.inc'
for p in (runtime, lemmas):
    assert b'\r' not in p.read_bytes()

tree = ast.parse(GATE.read_text(encoding='utf-8'))
env = {'re': re, 'Path': Path, 'Verdict': SimpleNamespace, '_MAX_BYTES': 256000,
       'SLOTS': {'full': SimpleNamespace(contract='ContractTensor')}}
for name in ['OPTIONS', 'ATTRIBUTES', 'BANNED']:
    n = next(n for n in tree.body if isinstance(n, ast.Assign) and any(
        isinstance(t, ast.Name) and t.id == name for t in n.targets))
    env[name] = re.compile(ast.literal_eval(n.value.args[0])) if name == 'BANNED' else ast.literal_eval(n.value)
fs = [n for n in tree.body if isinstance(n, ast.FunctionDef) and n.name in ['intake', 'policy', 'options']]
exec(compile(ast.Module(body=fs, type_ignores=[]), str(GATE), 'exec'), env)
checks = {p.name: {'intake': env['intake'](p, SimpleNamespace(slot='full')),
                  'policy': env['policy'](p, SimpleNamespace(slot='full')),
                  'options': env['options'](p.read_text(encoding='utf-8'))}
          for p in (runtime, lemmas)}
assert all(value is None for result in checks.values() for value in result.values())

source = runtime.read_text(encoding='utf-8')
assert source.count('n.toFloat32.toUInt32') == 1
assert 'toBits' not in source and 'log2' not in source and '.toNat' not in source
assert source.count('Model.NativeBinary32.expField') == 2
assert source.count('let n :=') == 1 and source.count('let d :=') == 1
assert source.count('let highSign :=') == source.count('let lowSign :=') == 1
assert source.count('R2W01b.mantissa') == 2
assert 'structure ' not in source and 'Option ' not in source

out = {
    'created_utc': datetime.now(timezone.utc).isoformat(),
    'state': 'RUNTIME_AND_CONDITIONAL_PROOF_FRAGMENTS_READY_FOR_CONTROLLED_INTEGRATION_NOT_COMPILED',
    'runtime': binding(runtime), 'conditional_helpers': binding(lemmas),
    'obligations': binding(HERE / 'runtime-equivalence-v1.md'),
    'finite_check': binding(HERE / 'runtime-flow-v1-check.json'),
    'source_bindings': [binding(p) for p in [BASE, OLD, FROZEN, GATE, HEADER]],
    'text_checks': checks, 'comments_scanned': True,
    'text_check_scope': 'Each fragment only; neither fragment is a standalone Kernel and no integrated candidate gate is claimed',
    'static_source_shape': 'One numeric roundtrip, two exponent extractions, one magnitude, one gap, each sign once, two mantissas, no toBits/log2/toNat/Prepared/Option in the runtime fragment',
    'helper_roots_pending': ['Submission.R17NumericAdd.sortedAdd', 'Submission.R17NumericAdd.guardedAdd',
                             'Submission.R17NumericNormalize.output_exponent_bounds',
                             'Submission.R17NumericNormalize.output_exponent_guard',
                             'Submission.R17NumericNormalize.numeric_shift_toNat',
                             'Submission.R17NumericNormalize.numeric_fraction_toNat'],
    'frozen_probe_unchanged': True, 'new_complete_Kernel_created': False,
    'bare_known_bytes': FROZEN.stat().st_size + runtime.stat().st_size + lemmas.stat().st_size,
    'bare_margin_excluding_alignment_threshold_public_spec_wiring': 256000 - FROZEN.stat().st_size - runtime.stat().st_size - lemmas.stat().st_size,
    'size_warning': 'This arithmetic is not a final dependency-closed source size. Old alignment support plus threshold proof and public wiring still need accounting.',
    'compile': 'NOT_RUN', 'kernel': 'NOT_RUN', 'axiom_audit': 'NOT_RUN', 'C': 'NOT_RUN',
    'assembly': 'NOT_RUN', 'performance': 'NOT_RUN',
    'no_new_assumptions_in_frozen_probe': True,
    'conditional_helper_boundary': 'numeric_shift/fraction retain the actual normalization shift equality hs as a visible premise; the final public spec must discharge it',
    'local_Lean': False, 'Git': False, 'CI': False,
    'tokens': {'input': 'UNKNOWN', 'cached_input': 'UNKNOWN', 'output': 'UNKNOWN', 'reasoning': 'UNKNOWN'},
}
(HERE / 'runtime-v1-manifest.json').write_bytes((json.dumps(out, indent=2) + '\n').encode('utf-8'))
print(json.dumps({k: out[k] for k in ['state', 'runtime', 'conditional_helpers', 'text_checks',
                                     'bare_known_bytes', 'bare_margin_excluding_alignment_threshold_public_spec_wiring',
                                     'compile', 'performance']}, indent=2))
