"""Repair only the actual run40293041239 final cast-normalization error; no Lean or CI."""
from pathlib import Path
from datetime import datetime, timezone
from types import SimpleNamespace
import ast
import difflib
import hashlib
import json
import re

HERE = Path(__file__).resolve().parent
ROOT = next(p for p in HERE.parents if (p / 'AGENTS.md').exists())
ROUND = HERE.parents[1]
OLD = HERE / 'Probe-high-u32-roundtrip-repair1.lean'
OUT = HERE / 'Probe-high-u32-roundtrip-repair2.lean'
OLD_OUTPUT = HERE / 'Probe-output-model-v1.lean'
NEW_OUTPUT = HERE / 'Probe-output-model-repair2.lean'
GATE = ROOT / 'competitions/floatlib/research/astra-collab-20261023-r7/upstream/gate-4b7e838.py'
FEEDBACK = ROUND / 'development-proof-f01-r17-dev-u32-roundtrip-repair1-40293041239.json'

def binding(p):
    raw = p.read_bytes()
    return {'path': p.relative_to(ROOT).as_posix(), 'sha256': hashlib.sha256(raw).hexdigest(), 'bytes': len(raw)}

assert binding(OLD)['sha256'] == '01cff324ee8bd142ec9753a2ca72c9ecb7ca24cd8c1bcac9a0925e77fd5e4905'
assert binding(OLD_OUTPUT)['sha256'] == '77036fcac800231fcd6933a8c6abc41c09a9e5313c342a55fbd74f4fa6daf39c'
assert binding(GATE)['sha256'] == '1eb74ef7479b0023c721e776cc5e4073af21c6662b4afffcf16a48a124d27194'
feedback = json.loads(FEEDBACK.read_text(encoding='utf-8'))
log = ROOT / feedback['compiler_output']
assert binding(log)['sha256'] == 'f35859ac7478162b9d71bf3fc9f8f02749968334afd88c11f05bba0a45db9ee8'
old_line = '  simpa using (UInt32.toNat_ofNatClamp_of_lt hfit)\n'
new_line = '  simpa only [Int.toNat_natCast] using (UInt32.toNat_ofNatClamp_of_lt hfit)\n'
old = OLD.read_text(encoding='utf-8')
assert old.count(old_line) == 1
new = old.replace(old_line, new_line)
OUT.write_bytes(new.encode('utf-8'))
old_output = OLD_OUTPUT.read_text(encoding='utf-8')
assert old_output.startswith(old)
NEW_OUTPUT.write_bytes((new + old_output[len(old):]).encode('utf-8'))
assert OUT.read_bytes().replace(new_line.encode(), old_line.encode()) == OLD.read_bytes()
assert NEW_OUTPUT.read_bytes().replace(new_line.encode(), old_line.encode()) == OLD_OUTPUT.read_bytes()
(HERE / 'repair2-minimal.lean.inc').write_bytes(new_line.encode('utf-8'))
(HERE / 'repair2.patch').write_bytes(''.join(difflib.unified_diff(
    old.splitlines(keepends=True), new.splitlines(keepends=True),
    fromfile=OLD.name, tofile=OUT.name)).encode('utf-8'))

tree = ast.parse(GATE.read_text(encoding='utf-8'))
env = {'re': re, 'Path': Path, 'Verdict': SimpleNamespace, '_MAX_BYTES': 256000,
       'SLOTS': {'full': SimpleNamespace(contract='ContractTensor')}}
for name in ['OPTIONS', 'ATTRIBUTES', 'BANNED']:
    node = next(n for n in tree.body if isinstance(n, ast.Assign) and any(
        isinstance(t, ast.Name) and t.id == name for t in n.targets))
    env[name] = re.compile(ast.literal_eval(node.value.args[0])) if name == 'BANNED' else ast.literal_eval(node.value)
fs = [n for n in tree.body if isinstance(n, ast.FunctionDef) and n.name in ['intake', 'policy', 'options']]
exec(compile(ast.Module(body=fs, type_ignores=[]), str(GATE), 'exec'), env)
checks = {}
for p in [OUT, NEW_OUTPUT]:
    assert b'\r' not in p.read_bytes()
    checks[p.name] = {'intake': env['intake'](p, SimpleNamespace(slot='full')),
                     'policy': env['policy'](p, SimpleNamespace(slot='full')),
                     'options': env['options'](p.read_text(encoding='utf-8'))}
assert all(x is None for v in checks.values() for x in v.values())
roots = json.loads((HERE / 'repair1-manifest.json').read_text(encoding='utf-8'))['explicit_helper_audit']
output_roots = json.loads((HERE / 'output-probe-v1-manifest.json').read_text(encoding='utf-8'))['explicit_total_roots']
out = {
    'created_utc': datetime.now(timezone.utc).isoformat(),
    'state': 'REAL_COMPILER_ERROR_MINIMAL_REPAIR2_READY_NOT_COMPILED',
    'primary_probe': binding(OUT), 'dependent_output_probe': binding(NEW_OUTPUT),
    'failure_bindings': [binding(FEEDBACK), binding(log), binding(OLD)],
    'repair': {'old': old_line.strip(), 'new': new_line.strip(),
               'scope': 'Restrict simplification to the whole-Nat-cast Int.toNat identity; no statement, premise, runtime, proof order or other proof line changed'},
    'fixed_interface': {
        'pin': '293d5d0c0c3f3dded4688b3ccd6a33939ac5102b',
        'lemma': 'Int.toNat_natCast (n : Nat) : Int.toNat (n : Int) = n',
        'proof': 'rfl',
        'source_url': 'https://raw.githubusercontent.com/leanprover/lean4/293d5d0c0c3f3dded4688b3ccd6a33939ac5102b/src/Init/Data/Int/Order.lean',
        'source_line_1_based': 622,
        'verified_via': 'Primary pinned raw source read with web tool; Basic.lean lines345-348 also gives toNat constructor reduction',
        'raw_local_fetch': 'Failed with WinError10013; did not escalate or invent a raw file hash',
        'raw_local_sha256': 'UNKNOWN',
    },
    'diagnosis': 'The actual post-simpa goal has the Int coercion pushed into multiplication/power. hr was stated as one Nat cast. The repair preserves that cast until Int.toNat_natCast removes it; it does not introduce a new power theorem or broaden simp.',
    'original_text_checks': checks, 'comments_scanned': True, 'canonical_LF': True,
    'primary_helper_roots': roots, 'output_helper_roots': output_roots,
    'root_counts': {'primary': len(roots), 'dependent_output': len(output_roots)},
    'requested_order': 'Compile repair2 primary first; the output probe has the same repaired prefix and should not be independently queued to rediscover the same former failure. UInt64 equivalent tail should receive the same scoped Int.toNat_natCast normalization.',
    'original01cff_and77036_unchanged': True,
    'compile': 'NOT_RUN', 'kernel': 'NOT_RUN', 'helper_audit': 'NOT_RUN', 'performance': 'NOT_RUN',
    'source_budget_status': 'Stopped immediately on actual compiler feedback; source-budget-add/plan.json and deletion-only patch retain the 14648B static plan. No expansion or application.',
    'tokens': 'UNKNOWN', 'CI_seconds': 0,
}
(HERE / 'repair2-manifest.json').write_bytes((json.dumps(out, indent=2, ensure_ascii=False) + '\n').encode('utf-8'))
print(json.dumps({k: out[k] for k in ['state', 'primary_probe', 'dependent_output_probe', 'repair',
                                     'original_text_checks', 'root_counts', 'compile']}, indent=2))
