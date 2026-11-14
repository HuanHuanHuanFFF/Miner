"""Run only exact saved gate intake/options/policy functions, never build/replay/score."""
from pathlib import Path
from types import SimpleNamespace
import ast
import hashlib
import json
import re

HERE = Path(__file__).resolve().parent
ROOT = next(p for p in HERE.parents if (p / 'AGENTS.md').is_file())
gate_path = ROOT / 'competitions/floatlib/candidates/f01-d7-research/official-policy/gate-4b7e838.raw'
gate = gate_path.read_bytes()
assert hashlib.sha256(gate).hexdigest() == '1eb74ef7479b0023c721e776cc5e4073af21c6662b4afffcf16a48a124d27194'
tree = ast.parse(gate)
selected = [n for n in tree.body if (isinstance(n, ast.FunctionDef) and n.name in ('intake', 'options', 'policy'))
            or (isinstance(n, ast.Assign) and any(isinstance(t, ast.Name) and t.id in ('OPTIONS', 'ATTRIBUTES', 'BANNED') for t in n.targets))]
assert len(selected) == 6
env = {'Path': Path, 're': re, '_MAX_BYTES': 256000,
       'SLOTS': {'full': SimpleNamespace(contract='ContractTensor')}}
code = ast.Module(body=[ast.ImportFrom(module='__future__', names=[ast.alias(name='annotations')], level=0), *selected], type_ignores=[])
exec(compile(ast.fix_missing_locations(code), str(gate_path) + ':read-only-extract', 'exec'), env)
kernel = HERE / 'Kernel.lean'
results = {name: env[name](kernel, SimpleNamespace(slot='full')) for name in ('intake', 'policy')}
assert all(x is None for x in results.values()), results
report = {'candidate_sha256': hashlib.sha256(kernel.read_bytes()).hexdigest(), 'candidate_bytes': kernel.stat().st_size,
          'saved_gate_path': str(gate_path), 'saved_gate_sha256': hashlib.sha256(gate).hexdigest(),
          'scope': 'Only exact saved intake/options/policy function AST and exact constants. Full slot bound to original ContractTensor and max256000. No official file writes, gate invocation, Lean, replay, axiom audit or timing.',
          'result': results, 'source_preflight': 'PASS', 'statement': 'NOT_RUN', 'full_gate': 'NOT_RUN'}
(HERE / 'policy-preflight.json').write_text(json.dumps(report, ensure_ascii=False, indent=2) + '\n', encoding='utf-8')
print(json.dumps({'source_preflight': 'PASS', 'candidate_sha256': report['candidate_sha256'], 'full_gate': 'NOT_RUN'}))
