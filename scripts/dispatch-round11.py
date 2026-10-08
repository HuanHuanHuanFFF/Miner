"""Dispatch an explicitly named R11 batch on its exact pushed experimental ref.

Existing Git credentials are resolved only in memory via collect-round2. Never
print the child environment. The workflow is manual and requires allow_private.
"""
import argparse
import importlib.util
import json
import os
from pathlib import Path
import subprocess
import time

ROOT = Path(__file__).resolve().parents[1]
REPO = 'HuanHuanHuanFFF/Miner'


def main():
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument('batch')
    ap.add_argument('--ref', default='codex/round11-frontier')
    args = ap.parse_args()
    os.environ['ROUND4_SPEC_DIR'] = 'evidence/round11'
    from round4 import validate
    validate(args.batch)
    assert args.ref.startswith('codex/')
    sha = subprocess.check_output(['git', 'rev-parse', args.ref], text=True).strip()
    spec = importlib.util.spec_from_file_location('r11_gh', ROOT / 'scripts/collect-round2.py')
    helper = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(helper)
    env = helper.gh_env()
    remote = json.loads(helper.run(['api', f'repos/{REPO}/commits/{args.ref}'], env))['sha']
    assert remote == sha, 'Push the frozen commit before dispatch'
    list_args = ['run', 'list', '--repo', REPO, '--branch', args.ref,
                 '--workflow', 'deflate-round9.yml', '--limit', '20',
                 '--json', 'databaseId,headSha,status,createdAt,url']
    existing = {r['databaseId'] for r in json.loads(helper.run(list_args, env))}
    helper.run(['workflow', 'run', 'deflate-round9.yml', '--repo', REPO, '--ref', args.ref,
                '-f', 'experiment_round=11', '-f', 'specification=' + args.batch,
                '-f', 'allow_private=true'], env)
    for _ in range(10):
        runs = json.loads(helper.run(list_args, env))
        matching = [r for r in runs if r['headSha'] == sha and r['databaseId'] not in existing]
        if matching:
            record = {'batch': args.batch, 'git_sha': sha, 'allow_private': True,
                      'workflow': 'deflate-round9.yml', 'ref': args.ref, 'run': matching[0]}
            target = ROOT / 'evidence/round11' / ('dispatch-' + str(matching[0]['databaseId']) + '.json')
            assert not target.exists(), 'Do not overwrite a dispatch receipt'
            target.write_text(json.dumps(record, indent=2) + '\n')
            print(json.dumps(record))
            return
        time.sleep(2)
    raise RuntimeError('Dispatch returned success; run discovery pending. Inspect Actions before retrying.')


if __name__ == '__main__':
    main()
