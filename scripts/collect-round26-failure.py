"""Bind an early failed native artifact via GitHub run metadata, never as a measurement."""
from pathlib import Path
from datetime import datetime, timezone
import argparse
import hashlib
import importlib
import json
import re

ROOT = Path(__file__).resolve().parents[1]

def main():
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument('run_id')
    ap.add_argument('batch')
    a = ap.parse_args()
    assert a.run_id.isdecimal() and re.fullmatch(r'[a-z0-9-]{1,48}', a.batch)
    helper = importlib.import_module('collect-round2')
    env = helper.gh_env()
    repo = 'HuanHuanHuanFFF/Miner'
    meta = json.loads(helper.run(['run', 'view', a.run_id, '--repo', repo, '--json',
        'databaseId,headSha,headBranch,event,status,conclusion,createdAt,updatedAt,url,jobs'], env))
    assert meta['status'] == 'completed' and meta['conclusion'] == 'failure'
    assert meta['headBranch'] == 'codex/round26-stable-pair'
    artifacts = json.loads(helper.run(['api', f'repos/{repo}/actions/runs/{a.run_id}/artifacts'], env))['artifacts']
    name = f'r26-{a.run_id}-{a.batch}-diagnostics'
    artifact = next(x for x in artifacts if x['name'] == name and not x['expired'])
    assert str(artifact['workflow_run']['id']) == a.run_id
    assert artifact['workflow_run']['head_sha'] == meta['headSha']
    base = (ROOT / 'evidence/round26' / a.run_id / a.batch).resolve()
    stages = list(base.glob('.diagnostics-download-*'))
    assert len(stages) == 1
    stage = stages[0].resolve()
    target = (base / 'failed-before-receipt').resolve()
    assert stage.is_relative_to(base) and target.is_relative_to(base)
    assert not stage.is_symlink() and not target.exists()
    files = {p.relative_to(stage).as_posix(): {'bytes': p.stat().st_size,
        'sha256': hashlib.sha256(p.read_bytes()).hexdigest()} for p in stage.rglob('*') if p.is_file()}
    assert files and all(not (stage / f).is_symlink() for f in files)
    assert not any(f.endswith('encoder.json') for f in files), 'This path is only for failure before a bound native receipt'
    stage.rename(target)
    for filename, data in [('ci-run.json', meta), ('artifact-receipt.json', artifact),
                           ('raw-artifact-files.json', {'artifact_name': name, 'artifact_id': artifact['id'],
                             'github_artifact_digest': artifact.get('digest'), 'files': files})]:
        (target / filename).write_text(json.dumps(data, indent=2) + '\n', encoding='utf-8')
    receipt = {'status': 'VERIFIED_FAILED_JOB_ARTIFACT_API_BINDING_ONLY',
        'run_id': a.run_id, 'git_sha': meta['headSha'], 'batch': a.batch,
        'retrieved_utc': datetime.now(timezone.utc).isoformat(),
        'original_stage': stage.relative_to(ROOT).as_posix(), 'files': files,
        'scope': 'Artifact API binds failed run and commit. Original files unchanged. No native output, timing, gate or candidate correctness result.'}
    (target / 'failure-receipt.json').write_text(json.dumps(receipt, indent=2) + '\n', encoding='utf-8')
    print(json.dumps(receipt))

if __name__ == '__main__':
    main()
