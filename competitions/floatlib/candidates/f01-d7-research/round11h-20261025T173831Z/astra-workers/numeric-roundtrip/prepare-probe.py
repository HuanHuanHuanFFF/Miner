"""Prepare the smallest source repair from the exact archived R16 probe; no Lean or CI."""
from pathlib import Path
from types import SimpleNamespace
from datetime import datetime, timezone
import ast
import difflib
import hashlib
import json
import re

HERE = Path(__file__).resolve().parent
ROOT = next(p for p in HERE.parents if (p / 'AGENTS.md').exists())
OLD = ROOT / 'competitions/floatlib/candidates/f01-r16-dev-u32-roundtrip-probe1/Kernel.lean'
BASE = ROOT / 'competitions/floatlib/candidates/f01-r15-dev-packed-b2-1/Kernel.lean'
PREV = ROOT / 'competitions/floatlib/candidates/f01-d7-research/round3h-20261025T091810Z'
PACK = PREV / 'astra-workers/matrix-architecture/future-u32-roundtrip'
GATE = ROOT / 'competitions/floatlib/research/astra-collab-20261023-r7/upstream/gate-4b7e838.py'
ERROR_MAP = PREV / 'development-compiler-error-map-40192000569.json'
OUT = HERE / 'Probe-high-u32-roundtrip-repair1.lean'

def sha(raw):
    return hashlib.sha256(raw).hexdigest()

def binding(path):
    raw = path.read_bytes()
    return {'path': path.relative_to(ROOT).as_posix(), 'sha256': sha(raw), 'bytes': len(raw)}

old_raw = OLD.read_bytes()
assert sha(old_raw) == '4e97be71ed7b4633d6e8db21b1487d3fde50ef64e387dea441a9bc53f94bcb03'
assert sha(BASE.read_bytes()) == '622d8394a7127e93dcaf992c62c6dfcff7208d212738409a5e34525dfafd1a58'
assert sha(GATE.read_bytes()) == '1eb74ef7479b0023c721e776cc5e4073af21c6662b4afffcf16a48a124d27194'
error = json.loads(ERROR_MAP.read_text(encoding='utf-8'))['candidates'][0]
log = ROOT / error['original_output']
assert sha(log.read_bytes()) == '81518415b7bdd4b325def6456ebc44cf80d4879662b7191a561b9d8522427d39'

old = old_raw.decode('utf-8').replace('\r\n', '\n')
needle = '  rw [Model.toModel_ofFloat32Model,hv] at hi\n'
assert old.count(needle) == 1
repair = '''  change x.toModel.unpack.toInt 0 (UInt32.size-1) =
    Model.roundDyadicToInt .towardZero
      (⟨false,m,(e : Int)⟩ : FloatLib.Numerics.Dyadic) at hi
'''
new = old.replace(needle, needle + repair)
OUT.write_bytes(new.encode('utf-8'))
assert b'\r' not in OUT.read_bytes()
assert OUT.read_bytes().startswith(BASE.read_bytes())
assert len(OUT.read_bytes()) <= 256000
(HERE / 'minimal-repair.patch').write_bytes(''.join(difflib.unified_diff(
    old.splitlines(keepends=True), new.splitlines(keepends=True),
    fromfile=str(OLD.relative_to(ROOT)), tofile=OUT.name)).encode('utf-8'))
fragment = new[new.index('namespace Submission.R16UInt32Roundtrip'):]
(HERE / 'HighRoundtrip-repair1.lean.inc').write_bytes(fragment.encode('utf-8'))

tree = ast.parse(GATE.read_text(encoding='utf-8'))
env = {'re': re, 'Path': Path, 'Verdict': SimpleNamespace, '_MAX_BYTES': 256000,
       'SLOTS': {'full': SimpleNamespace(contract='ContractTensor')}}
for name in ['OPTIONS', 'ATTRIBUTES', 'BANNED']:
    node = next(n for n in tree.body if isinstance(n, ast.Assign) and any(
        isinstance(t, ast.Name) and t.id == name for t in n.targets))
    env[name] = re.compile(ast.literal_eval(node.value.args[0])) if name == 'BANNED' else ast.literal_eval(node.value)
fs = [n for n in tree.body if isinstance(n, ast.FunctionDef) and n.name in ['intake', 'policy', 'options']]
exec(compile(ast.Module(body=fs, type_ignores=[]), str(GATE), 'exec'), env)
verdict = SimpleNamespace(slot='full')
checks = {'intake': env['intake'](OUT, verdict), 'policy': env['policy'](OUT, verdict),
          'options': env['options'](OUT.read_text(encoding='utf-8'))}

previous_manifest = json.loads((PACK / 'packaged-probe-manifest.json').read_text(encoding='utf-8'))
roots = previous_manifest['explicit_helper_audit']
assert len(roots) == 22
(HERE / 'HelperAudit.lean.inc').write_bytes(('\n'.join('#print axioms ' + n for n in roots) + '\n').encode('utf-8'))
fixed_sources = [PACK / p for p in ['fixed-Native-ToInt.lean', 'fixed-Native-Model.lean',
                                 'fixed-Operations-Runtime.lean', 'fixed-ExactValue.lean', 'ToNat.lean']]
source_bindings = [binding(p) for p in [OLD, BASE, GATE, ERROR_MAP, log,
                                      PACK / 'packaged-probe-manifest.json', PACK / 'bridge-check.json',
                                      PACK / 'fixed-import-chain.json', *fixed_sources]]
manifest = {
    'created_utc': datetime.now(timezone.utc).isoformat(),
    'state': 'MINIMAL_SOURCE_REPAIR_READY_FOR_PINNED_COMPILATION',
    'probe': binding(OUT), 'source_bindings': source_bindings,
    'repair': 'Insert an explicit change at hi to expose the finite constructor reduction before rewriting; all original statements and other proof lines are unchanged.',
    'new_assumptions': [], 'original_input_domain': '8388608 <= n.toNat <= 2164260735',
    'output': 'RNE integer R, not the original input N',
    'byte_format': 'UTF-8 canonical LF', 'remaining_bytes': 256000 - OUT.stat().st_size,
    'retained_B2_is_exact_byte_prefix': True,
    'public_runtime_delta': 'NONE; appended helper remains unreferenced by the four entry points',
    'fixed_original_text_checks': checks, 'comments_scanned': True,
    'explicit_helper_audit': roots,
    'required_remote_validation': ['Exact source identity', 'Original statement build',
                                   'Full Submission kernel replay', 'All 22 helper axiom roots',
                                   'Original four public obligations and full gate if used as a candidate'],
    'compile': 'NOT_RUN', 'kernel': 'NOT_RUN', 'axiom_audit': 'NOT_RUN', 'performance': 'NOT_RUN',
    'local_Lean': False, 'CI': False, 'Git': False,
    'tokens': {'input': 'UNKNOWN', 'cached_input': 'UNKNOWN', 'output': 'UNKNOWN', 'reasoning': 'UNKNOWN'},
}
(HERE / 'repair1-manifest.json').write_bytes((json.dumps(manifest, indent=2, ensure_ascii=False) + '\n').encode('utf-8'))
print(json.dumps({'probe': manifest['probe'], 'checks': checks, 'remaining_bytes': manifest['remaining_bytes'],
                  'compile': manifest['compile'], 'kernel': manifest['kernel'], 'audit': manifest['axiom_audit']}, indent=2))
assert all(v is None for v in checks.values())
