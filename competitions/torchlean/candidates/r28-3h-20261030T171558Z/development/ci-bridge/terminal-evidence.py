"""Release an actual compute slot only after independently checked final evidence.

The platform's stale status is retained verbatim. This never cancels or retries
a workflow, and is not a fallback for merely slow, missing, or partial jobs.
"""
from pathlib import Path
import hashlib
import json


def verified(run_dir, expected_source=None):
    run_dir = Path(run_dir)
    path = run_dir / 'execution-reconciliation.json'
    if not path.is_file():
        return False
    rec = json.loads(path.read_bytes())
    if rec.get('independent_review') == 'PENDING':
        return False
    assert rec['state'] in {
        'RUNNER_EXECUTION_FINISHED_FAILURE_PLATFORM_METADATA_STALE',
        'RUNNER_EXECUTION_FINISHED_SUCCESS_PLATFORM_METADATA_STALE',
    }
    review = rec['independent_review']
    root = next(p for p in run_dir.resolve().parents if (p / 'AGENTS.md').is_file())
    review_path = root / review['path']
    assert hashlib.sha256(review_path.read_bytes()).hexdigest() == review['sha256']
    decision = json.loads(review_path.read_bytes())
    assert decision['runner_execution_terminal_verified'] is True
    assert str(decision['run']) == str(rec['run']) == run_dir.name
    assert decision['source_commit'] == rec['source_commit']
    if expected_source is not None:
        assert rec['source_commit'] == expected_source
    manifest_path = run_dir / 'original-artifact-hashes.json'
    assert hashlib.sha256(manifest_path.read_bytes()).hexdigest() == rec['artifact_manifest_sha256']
    manifest = json.loads(manifest_path.read_bytes())
    assert manifest['artifact']['id'] == rec['artifact_id']
    folder = run_dir / manifest['directory']
    for name, entry in manifest['files'].items():
        p = (folder / name).resolve()
        assert p.is_relative_to(folder.resolve())
        data = p.read_bytes()
        assert len(data) == entry['bytes'] and hashlib.sha256(data).hexdigest() == entry['sha256']
    raw = (folder / 'summary.json').read_bytes()
    assert hashlib.sha256(raw).hexdigest() == rec['summary_sha256']
    summary = json.loads(raw)
    assert str(summary['run_id']) == run_dir.name and summary['source_commit'] == rec['source_commit']
    assert summary['finished_at_utc'] == rec['observed_runner_finished_at_utc']
    log_bytes = (run_dir / 'ci.log').read_bytes()
    assert hashlib.sha256(log_bytes).hexdigest() == rec['job_log_sha256']
    log = log_bytes.decode('utf-8')
    assert f"Artifact torchlean-{rec['run']}-receipts.zip successfully finalized" in log
    assert 'Post job cleanup.' in log and 'Cleaning up orphan processes' in log
    if 'FAILURE' in rec['state']:
        assert 'Process completed with exit code 1.' in log and summary['complete'] is False
    else:
        assert summary['complete'] is True
    return True
