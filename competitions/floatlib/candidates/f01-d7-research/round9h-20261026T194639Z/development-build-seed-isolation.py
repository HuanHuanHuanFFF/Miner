"""Narrow the actual SIGTERM seam using compiled B2 and flushed proof markers."""
from pathlib import Path
from datetime import datetime, timezone
import ast
import hashlib
import json
import re

here = Path(__file__).resolve().parent
root = here.parents[4]
sha = lambda data: hashlib.sha256(data).hexdigest()
save = lambda p, value: p.write_bytes((json.dumps(value, ensure_ascii=False, indent=2) + '\n').encode())
producer = here / 'astra-workers/exact-arithmetic/bias-frontier'
parts = [producer / 'Retained-BranchlessRNE-seed.lean.inc', producer / 'PostBias.lean.inc']
expected = ['5a06c12700e015d3aecbfdbcd2abe879d2bbd68f0d7ed8d75f29289806652279',
            'f60bed0349b0a2ad255636098cde7e9b28a2d874b7bb68fa6ee668b2d83cbc7e']
destination = here / 'development-seed-isolation'
destination.mkdir(exist_ok=False)
joined = b''
components = []
for source, digest in zip(parts, expected):
    raw = source.read_bytes()
    assert sha(raw) == digest and b'\r' not in raw
    target = destination / source.name
    target.write_bytes(raw)
    components.append({'path': target.relative_to(root).as_posix(), 'sha256': digest, 'bytes': len(raw)})
    joined += raw + b'\n'

text = joined.decode()
pattern = re.compile(r'^(?:/--.*?-/\s*)?(?:@\[[^\n]+\]\s*)?(?:private )?(?:theorem|def)\s+([A-Za-z0-9_]+)', re.M | re.S)
matches = list(pattern.finditer(text))
assert [m.group(1) for m in matches] == ['quotient_bias', 'nat_bias', 'nat_grouped_bias', 'grouped', 'word_grouped',
    'grouped_eq_existing_rse', 'shift', 'biased', 'biased_quotient', 'biased_bounds', 'normalized_quotient']
labels = [str(index) + ':' + match.group(1) for index, match in enumerate(matches)]
def marker(event, label):
    return '\n#eval do\n  let stream ← IO.getStdout\n  stream.putStrLn "[DEBUG-R19-SEED] ' + event + ' ' + label + '"\n  stream.flush\n\n'
rendered = text[:matches[0].start()]
markers = []
for index, match in enumerate(matches):
    chunk = text[match.start():matches[index + 1].start() if index + 1 < len(matches) else len(text)]
    before, after = marker('BEFORE', labels[index]), marker('AFTER', labels[index])
    rendered += before + chunk + after
    markers.extend([before, after])
restored = rendered
for item in markers:
    assert restored.count(item) == 1
    restored = restored.replace(item, '')
assert restored == text
marked = destination / 'marked-proof.lean.inc'
marked.write_bytes(rendered.encode())
components.append({'path': marked.relative_to(root).as_posix(), 'sha256': sha(marked.read_bytes()), 'bytes': marked.stat().st_size})
name = 'f01-r19-dev-seed-isolation1'
folder = root / 'competitions/floatlib/candidates' / name
folder.mkdir(exist_ok=False)
baseline = root / 'competitions/floatlib/candidates/f01-r15-dev-packed-b2-1/Kernel.lean'
raw = baseline.read_bytes()
assert sha(raw) == '622d8394a7127e93dcaf992c62c6dfcff7208d212738409a5e34525dfafd1a58'
(folder / 'Kernel.lean').write_bytes(raw)
helper = here / 'development-resource-audit.py'
base = here / 'development-helper-audit-v5.py'
roots = ['Submission.' + op + '_spec' for op in ('add', 'mul', 'sum', 'bmm')]
manifest = {
    'candidate': name, 'candidate_file': 'Kernel.lean', 'candidate_sha256': sha(raw), 'candidate_bytes': len(raw),
    'created_at_utc': datetime.now(timezone.utc).isoformat(), 'validation_mode': 'statement-only',
    'proof_status': 'B2_SOURCE_UNCHANGED_SEPARATE_HELPER_ISOLATION_NOT_RUN', 'performance': 'NOT_RUN',
    'explicit_helper_audit': roots, 'helper_audit_expected_count': 4, 'helper_audit_source_sha256': sha(raw),
    'helper_audit_required_endpoints': roots, 'helper_audit_module': helper.name,
    'helper_audit_module_sha256': sha(helper.read_bytes()), 'resource_base_audit_sha256': sha(base.read_bytes()),
    'resource_probe': {'tag': '[DEBUG-R19-SEED]', 'cap_seconds': 180, 'source_sha256': sha(marked.read_bytes()), 'declarations': labels},
    'components': components,
    'scope': 'Diagnostic only: compile exact B2, then separately typecheck exact seed/PostBias with flushed per-declaration markers and read-only resource samples; never a new accepted public MUL or score.',
    'formal_submission': 'NOT_SUBMITTED',
}
save(folder / 'manifest.json', manifest)
diagnostic = root / 'competitions/floatlib/candidates/f01-word-tensors/ci-diagnostics.py'
old = diagnostic.read_bytes()
before = b"'development-helper-audit-v5.py')"
after = b"'development-helper-audit-v5.py', 'development-resource-audit.py')"
assert old.count(before) == 1
updated = old.replace(before, after)
tree = ast.parse(updated)
embedded = [node.value.value for node in ast.walk(tree) if isinstance(node, ast.Assign) and any(isinstance(t, ast.Name) and t.id == 'code' for t in node.targets)]
assert len(embedded) == 1
ast.parse(embedded[0]); ast.parse(helper.read_bytes())
diagnostic.write_bytes(updated)
save(here / 'development-seed-isolation-build.json', {
    'at_utc': manifest['created_at_utc'], 'candidate': name, 'kernel_sha256': sha(raw),
    'components': components, 'exact_inverse_of_marker_insertion': True, 'declarations': labels,
    'old_diagnostic_sha256': sha(old), 'new_diagnostic_sha256': sha(updated),
    'scope': 'Build the narrow remote feedback loop before causal hypotheses; no local Lean, no resource cap lifted, no original1180 failure rewritten',
    'red_evidence': {'run': 40410895344, 'original_command': 'lake build VerifyFull', 'exit_code': -15, 'elapsed_seconds': 31.3, 'full_build_output_bytes': 1},
})
print(json.dumps({'candidate': name, 'kernel': sha(raw), 'math_declarations': len(labels), 'marker_inverse': True}))
