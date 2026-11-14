"""Pinned original source intake/policy only; no Lean/native compilation."""
from pathlib import Path
import importlib.util
import json
import sys
sys.dont_write_bytecode = True
HERE = Path(__file__).resolve().parent
ROOT = next(p for p in HERE.parents if (p / 'AGENTS.md').is_file())
loader = ROOT / 'competitions/torchlean/candidates/r25-90m-20261029T064916Z/verification/exact-policy-preflight.py'
spec = importlib.util.spec_from_file_location('r26_pinned_original_policy', loader)
module = importlib.util.module_from_spec(spec)
spec.loader.exec_module(module)
ns, sources = module.load_official_policy()
rows = []
for file in sorted(HERE.glob('*/Kernel.lean')):
    intake = ns['intake'](module.Utf8Path(file), None)
    policy = ns['policy'](module.Utf8Path(file), None) if intake is None else None
    rows.append({'id': file.parent.name, 'sha256': module.sha256(file.read_bytes()),
                 'intake': intake, 'policy': policy, 'passed': intake is None and policy is None})
report = {'scope': 'PINNED_INTAKE_POLICY_ONLY', 'sources': sources, 'results': rows,
          'lean_native_proof': 'NOT_RUN'}
(HERE / 'policy-preflight.json').write_text(json.dumps(report, indent=2) + '\n', encoding='utf-8')
print(json.dumps(rows, indent=2))
