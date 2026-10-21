"""Read bounded repository/run metadata through the existing credential helper."""
from pathlib import Path
from datetime import datetime, timezone
import importlib.util, json

ROOT = Path(__file__).resolve().parents[1]
sp = importlib.util.spec_from_file_location('helper', ROOT / 'scripts/collect-round2.py')
helper = importlib.util.module_from_spec(sp); sp.loader.exec_module(helper)
env = helper.gh_env()
repo = 'HuanHuanHuanFFF/Miner'
meta = json.loads(helper.run(['api', f'repos/{repo}'], env))
runs = json.loads(helper.run(['run', 'list', '--repo', repo, '--limit', '30', '--json', 'databaseId,status,conclusion,headBranch,headSha,createdAt,updatedAt,url,workflowName'], env))
value = {'retrieved_utc': datetime.now(timezone.utc).isoformat(), 'repository': repo,
         'private': meta['private'], 'default_branch': meta['default_branch'], 'runs': runs}
p = ROOT / 'evidence/round24/github-start.json'
assert not p.exists()
p.write_bytes((json.dumps(value, indent=2) + '\n').encode())
print(json.dumps({'private': value['private'], 'default_branch': value['default_branch'],
                  'active_runs': [r for r in runs if r['status'] != 'completed'],
                  'recent': runs[:3]}))
