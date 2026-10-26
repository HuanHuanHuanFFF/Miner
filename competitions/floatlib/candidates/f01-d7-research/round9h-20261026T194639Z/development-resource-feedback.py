"""Read-only summary of original resource-isolation evidence, not a proof gate."""
from pathlib import Path
import argparse
import hashlib
import json

ap = argparse.ArgumentParser()
ap.add_argument('--run', type=int, required=True)
args = ap.parse_args()
here = Path(__file__).resolve().parent
root = here.parents[4]
base = root / 'competitions/floatlib/candidates/f01-mul-log2-proof1/ci-runs' / str(args.run)
index = json.loads((base / 'original-artifact-hashes.json').read_bytes())
artifact = base / index['directory']
sha = lambda p: hashlib.sha256(p.read_bytes()).hexdigest()
def authenticate(path):
    item = index['files'][path.relative_to(artifact).as_posix()]
    assert path.stat().st_size == item['bytes'] and sha(path) == item['sha256']

rows = []
for path in sorted(artifact.rglob('seed-isolation.json')):
    authenticate(path)
    record = json.loads(path.read_bytes())
    output = path.parent / 'seed-isolation-output.raw'
    samples = path.parent / 'seed-isolation-resources.json'
    source = path.parent / 'seed-isolation-source.lean'
    audit_path = path.parent / 'helper-audit.json'
    for item in (output, samples, source, audit_path):
        authenticate(item)
    assert sha(output) == record['output_sha256'] and sha(samples) == record['sampling_sha256']
    assert sha(source) == record['helper_source_sha256']
    audit = json.loads(audit_path.read_bytes())
    assert audit['accepted'] and audit['kernel_replay'] and audit['expected_count'] == 4
    properties = []
    for scope in record['systemd_scopes']:
        text = scope.get('properties', '')
        values = dict(line.split('=', 1) for line in text.splitlines() if '=' in line)
        properties.append({'unit': scope['unit'], **values})
    oom = any(item.get('Result') == 'oom-kill' for item in properties)
    status = 'VERIFIED_SCOPE_OOM' if oom else ('SEPARATE_HELPER_TYPECHECK_COMPLETE' if record['helper_typecheck_complete'] else 'CAUSE_UNKNOWN')
    rows.append({
        'candidate': path.parent.name, 'run': args.run, 'status': status,
        'base_B2_module_and_four_roots_pass': True,
        'helper_source_sha256': sha(source), 'exit_code': record['exit_code'],
        'elapsed_seconds': record['elapsed_seconds'], 'helper_typecheck_complete': record['helper_typecheck_complete'],
        'completed_declarations': record['completed_declarations'], 'active_at_end': record['active_at_end'],
        'stdout_bytes': output.stat().st_size, 'scope_properties': properties,
        'resource_record': path.relative_to(root).as_posix(), 'resource_record_sha256': sha(path),
        'resource_samples': samples.relative_to(root).as_posix(), 'resource_samples_sha256': sha(samples),
        'RSS_scope': 'Process RSS sum may double-count shared pages; use cgroup MemoryPeak/MemoryMax and OOM events for cap evidence',
        'scope': 'Diagnostic causal evidence only; no new full candidate, proof/spec replay or score accepted. Earlier historical UNKNOWN causes remain historical UNKNOWN.',
    })
assert rows
destination = here / f'development-resource-feedback-{args.run}.json'
destination.write_bytes((json.dumps(rows, ensure_ascii=False, indent=2) + '\n').encode())
print(json.dumps(rows, ensure_ascii=False))
