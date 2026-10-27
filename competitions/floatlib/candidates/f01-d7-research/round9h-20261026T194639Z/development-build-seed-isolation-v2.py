"""Build a raw-stderr marker control and the unchanged proof fragment."""
from pathlib import Path
from datetime import datetime, timezone
import ast
import hashlib
import json

here = Path(__file__).resolve().parent
root = here.parents[4]
sha = lambda raw: hashlib.sha256(raw).hexdigest()
save = lambda p, value: p.write_bytes((json.dumps(value, ensure_ascii=False, indent=2) + '\n').encode())
parent = json.loads((root / 'competitions/floatlib/candidates/f01-r19-dev-seed-isolation1/manifest.json').read_bytes())
old_marked = here / 'development-seed-isolation/marked-proof.lean.inc'
assert sha(old_marked.read_bytes()) == parent['resource_probe']['source_sha256']
old_line = 'let stream ← IO.getStdout'
new_line = 'let stream ← IO.FS.Handle.mk "/dev/stderr" .write'
old_text = old_marked.read_text('utf-8')
assert old_text.count(old_line) == 22
new_text = old_text.replace(old_line, new_line)
assert new_text.replace(new_line, old_line) == old_text
folder = here / 'development-seed-isolation-v2'
folder.mkdir(exist_ok=False)
marked = folder / 'marked-proof.lean.inc'
marked.write_bytes(new_text.encode())
control = folder / 'marker-control.lean.inc'
def marker(event):
    return '#eval do\n  let stream ← IO.FS.Handle.mk "/dev/stderr" .write\n  stream.putStrLn "[DEBUG-R19-SEED] '+event+' 0:marker_control"\n  stream.flush\n\n'
control.write_bytes((marker('BEFORE') + 'def r19MarkerControl : Nat := 0\n\n' + marker('AFTER')).encode())

old_helper = here / 'development-resource-audit.py'
helper = here / 'development-resource-audit-v2.py'
raw = old_helper.read_bytes()
before = b"    source = here / 'development-seed-isolation/marked-proof.lean.inc'"
after = b"    assert request['source_file'] in ('development-seed-isolation-v2/marked-proof.lean.inc', 'development-seed-isolation-v2/marker-control.lean.inc')\n    source = here / request['source_file']"
assert raw.count(before) == 1 and not helper.exists()
new_helper = raw.replace(before, after)
ast.parse(new_helper)
helper.write_bytes(new_helper)
baseline = root / 'competitions/floatlib/candidates/f01-r15-dev-packed-b2-1/Kernel.lean'
kernel = baseline.read_bytes()
assert sha(kernel) == '622d8394a7127e93dcaf992c62c6dfcff7208d212738409a5e34525dfafd1a58'
rows = []
for name, source, labels, kind in (
    ('f01-r19-dev-marker-control1', control, ['0:marker_control'], 'RAW_STDERR_MARKER_CONTROL'),
    ('f01-r19-dev-seed-isolation2', marked, parent['resource_probe']['declarations'], 'UNCHANGED_SEED_POSTBIAS_RAW_STDERR'),
):
    candidate = root / 'competitions/floatlib/candidates' / name
    candidate.mkdir(exist_ok=False)
    (candidate / 'Kernel.lean').write_bytes(kernel)
    manifest = {key: value for key, value in parent.items() if key not in ('resource_feedback', 'resource_feedback_sha256', 'components')}
    manifest.update(candidate=name, created_at_utc=datetime.now(timezone.utc).isoformat(),
        proof_status='B2_UNCHANGED_NEW_DIAGNOSTIC_HELPER_NOT_RUN', performance='NOT_RUN',
        helper_audit_module=helper.name, helper_audit_module_sha256=sha(new_helper),
        resource_probe={'tag': '[DEBUG-R19-SEED]', 'cap_seconds': 180, 'source_sha256': sha(source.read_bytes()),
                        'source_file': source.relative_to(here).as_posix(), 'declarations': labels, 'kind': kind},
        components=[{'path': source.relative_to(root).as_posix(), 'sha256': sha(source.read_bytes()), 'bytes': source.stat().st_size}],
        scope='Independent diagnostic, not scored or a new public MUL. Original seed/PostBias proof text unchanged; raw stderr bypass and pure marker control distinguish missing progress from proof resource cost.')
    save(candidate / 'manifest.json', manifest)
    rows.append({'candidate': name, 'kernel_sha256': sha(kernel), 'helper_source_sha256': sha(source.read_bytes()), 'kind': kind})
save(here / 'development-seed-isolation-v2-build.json', {
    'at_utc': datetime.now(timezone.utc).isoformat(), 'rows': rows,
    'old_marked_source_sha256': sha(old_marked.read_bytes()), 'new_marked_source_sha256': sha(marked.read_bytes()),
    'marker_io_line_replacement_inverse_exact': True, 'old_helper_sha256': sha(raw), 'new_helper_sha256': sha(new_helper),
    'scope': 'Separate control plus one unchanged proof payload, same4GiB public-runner constraints. No official gate/flags/CI execution file changed.',
})
print(json.dumps(rows))
