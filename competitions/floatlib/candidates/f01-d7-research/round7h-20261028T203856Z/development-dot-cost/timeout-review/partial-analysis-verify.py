from __future__ import annotations
import hashlib
import json
from pathlib import Path

OWNER = Path(__file__).resolve().parent
REPO = OWNER.parents[6]
RUN = REPO / 'competitions/floatlib/candidates/f01-d7-research/round7h-20261028T203856Z/ci-runs/40801622733'
HASH_INDEX = RUN / 'original-artifact-hashes.json'
index_bytes = HASH_INDEX.read_bytes()
index = json.loads(index_bytes)
root = (RUN / index['directory']).resolve()
assert root.is_relative_to(REPO.resolve()), 'download root escaped repository'
expected = index['files']
actual_paths = {p.relative_to(root).as_posix() for p in root.rglob('*') if p.is_file()}
expected_paths = set(expected)
missing = sorted(expected_paths - actual_paths)
unexpected = sorted(actual_paths - expected_paths)
checks = []
for rel in sorted(expected_paths):
    path = (root / Path(rel)).resolve()
    assert path.is_relative_to(root), f'indexed path escaped artifact root: {rel}'
    if not path.is_file():
        checks.append({'path': rel, 'pass': False, 'reason': 'missing'})
        continue
    data = path.read_bytes()
    record = expected[rel]
    got_sha = hashlib.sha256(data).hexdigest()
    got_bytes = len(data)
    checks.append({'path': rel, 'pass': got_sha == record['sha256'] and got_bytes == record['bytes'],
                   'expected_sha256': record['sha256'], 'actual_sha256': got_sha,
                   'expected_bytes': record['bytes'], 'actual_bytes': got_bytes})
failed = [c for c in checks if not c['pass']]
result = {
    'status': 'PASS' if len(expected) == 119 and len(actual_paths) == 119 and not missing and not unexpected and not failed else 'FAIL',
    'artifact_id': index['artifact']['id'],
    'workflow_run_id': index['artifact']['workflow_run']['id'],
    'artifact_zip_sha256_receipt': index['artifact']['digest'].removeprefix('sha256:'),
    'artifact_zip_digest_recomputed': False,
    'hash_index_sha256': hashlib.sha256(index_bytes).hexdigest(),
    'expected_file_count': len(expected), 'actual_file_count': len(actual_paths),
    'matched_file_count': sum(c['pass'] for c in checks),
    'missing_paths': missing, 'unexpected_paths': unexpected, 'failed_files': failed,
    'files': checks,
}
out = OWNER / 'partial-analysis-hash-audit.json'
out.write_text(json.dumps(result, indent=2) + '\n', encoding='utf-8')
print(json.dumps({k:v for k,v in result.items() if k != 'files'}, indent=2))
if result['status'] != 'PASS':
    raise SystemExit(1)