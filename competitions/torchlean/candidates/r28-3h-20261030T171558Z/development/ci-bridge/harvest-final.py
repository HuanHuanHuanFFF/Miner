"""Collect a finalized runner artifact even when workflow metadata is stale.

This is read-only on GitHub. It neither frees a CI slot nor rewrites platform
status; a separate independent review must validate the terminal evidence.
"""
from pathlib import Path
import argparse
import datetime
import hashlib
import importlib.util
import json
import subprocess
import uuid
import zipfile

ROOT = next(p for p in Path(__file__).resolve().parents if (p / 'AGENTS.md').is_file())
ROUND = Path(__file__).resolve().parents[2]
REPO = 'HuanHuanHuanFFF/Miner'
spec = importlib.util.spec_from_file_location('ci_credentials', ROOT / 'scripts/github-ci.py')
base = importlib.util.module_from_spec(spec)
spec.loader.exec_module(base)


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument('--run', required=True, type=int)
    args = parser.parse_args()
    env = base.env()
    gh = lambda xs: base.gh(xs, env)
    run = args.run
    out = ROUND / 'evidence' / str(run)
    out.mkdir(exist_ok=True)
    meta = json.loads(gh(['run', 'view', str(run), '--repo', REPO, '--json',
        'databaseId,headSha,status,conclusion,url,jobs,createdAt,updatedAt']))
    jobs = json.loads(gh(['api', f'repos/{REPO}/actions/runs/{run}/jobs']))['jobs']
    selected = [x for x in jobs if x['name'] == 'torchlean_r28']
    assert len(selected) == 1
    job = selected[0]
    assert all(x['name'] == job['name'] or x['status'] == 'completed' for x in jobs)
    log = gh(['api', f"repos/{REPO}/actions/jobs/{job['id']}/logs"])
    assert f'Artifact torchlean-{run}-receipts.zip successfully finalized' in log
    assert 'Post job cleanup.' in log and 'Cleaning up orphan processes' in log
    artifact_text = gh(['api', f'repos/{REPO}/actions/runs/{run}/artifacts'])
    artifacts = json.loads(artifact_text)
    artifact = next(x for x in artifacts['artifacts']
        if x['name'] == f'torchlean-{run}-receipts' and not x['expired'])
    manifest_path = out / 'original-artifact-hashes.json'
    if manifest_path.exists():
        manifest = json.loads(manifest_path.read_bytes())
        assert manifest['artifact']['id'] == artifact['id']
        folder = out / manifest['directory']
    else:
        archive = out / 'original-artifact.zip'
        with archive.open('wb') as stream:
            process = subprocess.run(['gh', 'api', f"repos/{REPO}/actions/artifacts/{artifact['id']}/zip"],
                cwd=ROOT, env=env, stdout=stream, stderr=subprocess.PIPE)
        assert process.returncode == 0, process.stderr.decode('utf-8')[:400]
        archive_hash = hashlib.sha256(archive.read_bytes()).hexdigest()
        if artifact.get('digest'):
            assert artifact['digest'] == 'sha256:' + archive_hash
        folder = out / ('download-' + uuid.uuid4().hex)
        folder.mkdir()
        with zipfile.ZipFile(archive) as zipped:
            assert sum(x.file_size for x in zipped.infolist()) <= 512 * 2**20
            for entry in zipped.infolist():
                assert (folder / entry.filename).resolve().is_relative_to(folder.resolve())
            zipped.extractall(folder)
        files = {p.relative_to(folder).as_posix(): {
            'bytes': p.stat().st_size, 'sha256': hashlib.sha256(p.read_bytes()).hexdigest()
        } for p in folder.rglob('*') if p.is_file()}
        manifest = {'artifact': artifact, 'directory': folder.name, 'files': files,
            'original_zip_sha256': archive_hash}
        base.save(manifest_path, manifest)
    for name, entry in manifest['files'].items():
        data = (folder / name).read_bytes()
        assert len(data) == entry['bytes'] and hashlib.sha256(data).hexdigest() == entry['sha256']
    raw = (folder / 'summary.json').read_bytes()
    summary = json.loads(raw)
    assert str(summary['run_id']) == str(run) and summary['source_commit'] == meta['headSha']
    assert summary['finished_at_utc']
    state = 'SUCCESS' if summary['complete'] else 'FAILURE'
    if state == 'FAILURE':
        assert 'Process completed with exit code 1.' in log
    base.save(out / 'ci-run.json', meta)
    base.save(out / 'jobs-observed.json', jobs)
    (out / 'artifacts.response.raw').write_bytes(artifact_text.encode('utf-8'))
    (out / 'ci.log').write_bytes(log.encode('utf-8'))
    rec = {
        'at_utc': datetime.datetime.now(datetime.timezone.utc).isoformat(),
        'state': f'RUNNER_EXECUTION_FINISHED_{state}_PLATFORM_METADATA_STALE',
        'run': run, 'source_commit': meta['headSha'], 'job_id': job['id'],
        'platform_status': meta['status'], 'platform_conclusion': meta['conclusion'],
        'observed_runner_finished_at_utc': summary['finished_at_utc'],
        'job_log_sha256': hashlib.sha256((out / 'ci.log').read_bytes()).hexdigest(),
        'summary_sha256': hashlib.sha256(raw).hexdigest(),
        'artifact_id': artifact['id'],
        'artifact_manifest_sha256': hashlib.sha256(manifest_path.read_bytes()).hexdigest(),
        'independent_review': 'PENDING',
        'scope': 'Final artifact and runner exit observed; raw platform status retained, no cancellation/retry/slot-release',
    }
    base.save(out / 'execution-reconciliation.json', rec)
    print(json.dumps({'run': run, 'state': rec['state'], 'files': len(manifest['files']),
        'platform_status': meta['status'], 'source': meta['headSha'], 'independent_review': 'PENDING'}))


if __name__ == '__main__':
    main()
