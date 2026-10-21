"""Initialize fixed R26 budget and reuse the verified R25 capture/CI interfaces."""
from pathlib import Path
import ast
import hashlib
import json

ROOT = Path(__file__).resolve().parents[1]
E = ROOT / 'evidence/round26'
E.mkdir(exist_ok=True)
assert not (E / 'budget.json').exists()
budget = {
    'round': 26, 'start_utc': '2026-10-11T21:06:52+00:00',
    'deadline_utc': '2026-10-12T05:06:52+00:00',
    'start_beijing': '2026-10-12 05:06:52 +08:00',
    'deadline_beijing': '2026-10-12 13:06:52 +08:00',
    'authorized_wall_seconds': 28800,
    'baseline_main_sha': '48baf622466792f4d505c5c06d5696f784e27b7a',
    'baseline_research_sha': '4864aef6',
    'branch': 'codex/round26-stable-pair',
    'objective': 'Two different stable competition-pool share candidates: 5% and 10%, higher if achieved; actual formal payability remains separate.',
    'scope': 'Research implementation, experiment-branch commits/pushes, manual public GitHub runner experiments, original public gates and independent confirmation. No formal upload, registration, signing or spending.',
    'confirmation_reserve_minutes': 120,
    'freeze_target_utc': '2026-10-12T03:06:52+00:00',
    'latest_new_research_dispatch_utc': '2026-10-12T03:06:52+00:00',
    'running_job_policy': 'Started jobs finish naturally or at declared timeout; timeout plus collection must fit deadline. No budget restart after compaction.',
    'default_active_children': 2, 'maximum_active_children': 3,
    'delegation': 'Two end-to-end independent route owners; third child only for a specific measurement, verification or proof bottleneck.',
    'worktree_policy': 'One existing checkout and independent file ownership; root alone handles Git and CI dispatch.',
    'status': 'RESEARCH_ACTIVE_TARGETS_UNMET',
}
(E / 'budget.json').write_text(json.dumps(budget, indent=2) + '\n', encoding='utf-8')
names = ['capture-round25-frontier.py', 'capture-round25-rules.py', 'check-round25-current.py',
         'dispatch-round25.py', 'verify-round25-exact.py', 'bind-round25-gate.py',
         'make-round25-batch.py', 'check-round25-route.py']
provenance = {}
for name in names:
    p = ROOT / 'scripts' / name
    raw = p.read_bytes()
    text = raw.decode('utf-8').replace('round25', 'round26').replace('ROUND25', 'ROUND26').replace('r25', 'r26').replace('R25', 'R26')
    text = text.replace('codex/round26-fast-quality', 'codex/round26-stable-pair')
    if name == 'dispatch-round25.py':
        text = text.replace("'experiment_round':'25'", "'experiment_round':'26'").replace("'round':25", "'round':26")
    if name == 'check-round25-route.py':
        text = text.replace("'25'", "'26'").replace('==25', '==26')
    if name == 'make-round25-batch.py':
        text = text.replace('official-frontier-current', 'official-start')
    ast.parse(text)
    dest = ROOT / 'scripts' / name.replace('25', '26')
    assert not dest.exists()
    dest.write_text(text, encoding='utf-8', newline='\n')
    provenance[dest.relative_to(ROOT).as_posix()] = {'source': p.relative_to(ROOT).as_posix(), 'source_sha256': hashlib.sha256(raw).hexdigest()}
(E / 'infrastructure-provenance.json').write_text(json.dumps(provenance, indent=2) + '\n', encoding='utf-8')
workflow = ROOT.parents[1] / '.github/workflows/deflate-round9.yml'
text = workflow.read_text()
assert "  round26:" not in text
text = text.replace("'24', '25']", "'24', '25', '26']")
text = text.replace("&& inputs.experiment_round != '25'", "&& inputs.experiment_round != '25' && inputs.experiment_round != '26'")
job = text[text.index('  round25:'):].replace('round25', 'round26').replace('ROUND25', 'ROUND26').replace('r25', 'r26').replace("== '25'", "== '26'")
workflow.write_text(text.rstrip() + '\n\n' + job, encoding='utf-8', newline='\n')
print('R26_FIXED_WINDOW_INITIALIZED')
