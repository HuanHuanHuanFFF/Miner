from pathlib import Path
from datetime import datetime, timezone
import ast
import hashlib
import json
import re

here = Path(__file__).resolve().parent
root = here.parents[4]
sha = lambda raw: hashlib.sha256(raw).hexdigest()
save = lambda p, value: p.write_bytes((json.dumps(value, ensure_ascii=False, indent=2) + '\n').encode())
base = here / 'development-resource-audit-v2.py'
old = base.read_bytes()
assert sha(old) == '60b0d6ecca09304f27c88c3bfcd601f20df959144f3a1ca815504b39f9b5434f'
text = old.decode()
text, count = re.subn(r'PREFIXES = \[.*?\]\nsha =', "PREFIXES = [('math-outlet', 'MathOutlet.lean', '2177e7b7e3c74f8fc7e7511cbe9d43fb34ea9d86eec97f0ab82053db49289266', 32332, 'R19MathOutletPrefix.lean')]\nsha =", text, count=1, flags=re.S)
assert count == 1
for before, after in [
    ('INDEPENDENT_COMPLETE_PREFIX_PROCESSES', 'SINGLE_COMPLETE_MATH_MODULE'),
    ("request['overall_budget_seconds'] == 110", "request['overall_budget_seconds'] == 165"),
    ('min(110, g._BUILD_TIMEOUT)', 'min(165, g._BUILD_TIMEOUT)'),
    ("here / 'development-prefix-isolation'", "here / 'development-math-isolation'"),
    ("out / 'prefix-isolation'", "out / 'math-isolation'"),
    ("'outer_default_diagnostic_seconds': 120", "'outer_default_diagnostic_seconds': 170"),
]:
    assert before in text, before
    text = text.replace(before, after)
start = text.index('        if not one_prefix(records[0], PREFIXES[0][4]):')
end = text.index('    return [(name, wrap(name, action))', start)
text = text[:start] + "        if not one_prefix(records[0], PREFIXES[0][4]):\n            return 'Independent math module incomplete: ' + records[0]['state']\n        return None\n" + text[end:]
text = text.replace("[('prefix-process-isolation', isolate)]", "[('math-module-isolation', isolate)]")
ast.parse(text)
helper = here / 'development-math-outlet-audit.py'
assert not helper.exists()
helper.write_bytes(text.encode())
source = here / 'astra-workers/exact-arithmetic/bias-frontier/public-proof-review1/MathOutlet-interface-v1.lean'
raw = source.read_bytes()
assert len(raw) == 32332 and sha(raw) == '2177e7b7e3c74f8fc7e7511cbe9d43fb34ea9d86eec97f0ab82053db49289266'
assert raw.startswith(b'import Submission\n') and b'#eval' not in raw
directory = here / 'development-math-isolation'
directory.mkdir(exist_ok=False)
target = directory / 'MathOutlet.lean'; target.write_bytes(raw)
name = 'f01-r19-dev-math-outlet-isolation1'
folder = root / 'competitions/floatlib/candidates' / name
folder.mkdir(exist_ok=False)
baseline = root / 'competitions/floatlib/candidates/f01-r15-dev-packed-b2-1/Kernel.lean'
kernel = baseline.read_bytes()
assert sha(kernel) == '622d8394a7127e93dcaf992c62c6dfcff7208d212738409a5e34525dfafd1a58'
(folder / 'Kernel.lean').write_bytes(kernel)
roots = ['Submission.' + op + '_spec' for op in ('add', 'mul', 'sum', 'bmm')]
manifest = {'candidate': name, 'candidate_file': 'Kernel.lean', 'candidate_sha256': sha(kernel), 'candidate_bytes': len(kernel),
    'created_at_utc': datetime.now(timezone.utc).isoformat(), 'validation_mode': 'statement-only', 'diagnostic_only': True,
    'proof_status': 'NOT_RUN', 'performance': 'NOT_RUN', 'formal_submission': 'NOT_SUBMITTED',
    'helper_audit_module': helper.name, 'helper_audit_module_sha256': sha(helper.read_bytes()),
    'helper_audit_source_sha256': sha(kernel), 'explicit_helper_audit': roots, 'helper_audit_expected_count': 4,
    'helper_audit_required_endpoints': roots, 'resource_base_audit_sha256': sha((here / 'development-helper-audit-v5.py').read_bytes()),
    'resource_probe': {'schema_version': 2, 'mode': 'SINGLE_COMPLETE_MATH_MODULE', 'cap_seconds': 180, 'overall_budget_seconds': 165},
    'components': [{'path': target.relative_to(root).as_posix(), 'sha256': sha(raw), 'bytes': len(raw)}],
    'scope': 'Exact B2 two-module/four-root audit then one independent complete32k math helper under original g.own4GiB. Helper exit0 is typing only; new48roots/independent math-module replay/fullfa acceptance remain NOT_RUN.'}
save(folder / 'manifest.json', manifest)
diag = root / 'competitions/floatlib/candidates/f01-word-tensors/ci-diagnostics.py'
old_diag = diag.read_bytes()
before = b"'development-route-audit-v2.py')"
after = b"'development-route-audit-v2.py', 'development-math-outlet-audit.py')"
assert old_diag.count(before) == 1
new_diag = old_diag.replace(before, after)
before = b"else 120\n"
after = b"else 170 if a.name=='f01-r19-dev-math-outlet-isolation1' else 120\n"
assert new_diag.count(before) == 1
new_diag = new_diag.replace(before, after)
tree = ast.parse(new_diag)
embedded = [n.value.value for n in ast.walk(tree) if isinstance(n, ast.Assign) and any(isinstance(t, ast.Name) and t.id == 'code' for t in n.targets)]
assert len(embedded) == 1
ast.parse(embedded[0]); diag.write_bytes(new_diag)
save(here / 'development-math-isolation-build.json', {'at_utc': manifest['created_at_utc'], 'candidate': name,
    'source_sha256': sha(raw), 'helper_sha256': sha(helper.read_bytes()), 'sampler_parent_sha256': sha(old),
    'old_diagnostic_sha256': sha(old_diag), 'new_diagnostic_sha256': sha(new_diag),
    'budget': 'Named diagnostic wrapper170s inside existing nested180s; math stage registration165s. Original gate build/time/memory/CPU/flags unchanged; not an acceptance gate.',
    'scope': manifest['scope']})
print(json.dumps({'candidate': name, 'math_module_bytes': len(raw), 'helper_sha256': sha(helper.read_bytes())}))
