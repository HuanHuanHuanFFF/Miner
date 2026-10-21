"""Initialize the explicitly authorized ten-hour R24 window; never reset it."""
from pathlib import Path
from datetime import datetime, timedelta, timezone
import json

ROOT = Path(__file__).resolve().parents[1]
E = ROOT / 'evidence/round24'

def save(path, obj):
    path.write_bytes((json.dumps(obj, indent=2, ensure_ascii=False) + '\n').encode())

def main():
    E.mkdir(exist_ok=True)
    assert not (E / 'budget.json').exists()
    start = datetime.fromisoformat('2026-10-10T19:28:08+00:00')
    end = start + timedelta(hours=10)
    bjt = timezone(timedelta(hours=8))
    save(E / 'budget.json', {
        'start_utc': start.isoformat(), 'deadline_utc': end.isoformat(),
        'start_bjt': start.astimezone(bjt).isoformat(), 'deadline_bjt': end.astimezone(bjt).isoformat(),
        'budget_minutes': 600, 'confirmation_reserve_minutes': 120,
        'objective': 'Two behaviorally different candidates: stable competition-pool share >=10% and >=15%, individually; also recompute joint interaction. Public projections remain conditional; formal payable results UNKNOWN until separately authorized official submission.',
        'stability_acceptance': 'Freeze exact Rust/Lean pairs, then fresh independent runners. Report every per-run/per-block result, observed minimum/median/range, zero and threshold counts, same-source control agreement, original full gate. No zero or below-target confirmation is hidden; no empirical pass frequency is a success probability.',
        'baseline_main_sha': '5bd2a57597aa92219a39a28edace88bc059587f2',
        'branch': 'codex/round24-stable-dual', 'status': 'ACTIVE',
        'authorization': 'Current 10h research plus established necessary public GitHub runner and experiment-branch commit/push scope. No formal competition upload, registration, wallet signing, or funding.',
        'quota': 'Read live account limits periodically. No reset at startup; prior reset-card restriction must be rechecked at <=1% remaining and tool ability to choose designated card; at most one successful redemption, no purchase.'
    })
    for old in ['capture-round23-frontier.py', 'dispatch-round23.py', 'round23-preflight.py', 'verify-round23-exact.py', 'bind-round23-gate.py']:
        new = old.replace('round23', 'round24')
        src = (ROOT / 'scripts' / old).read_text(encoding='utf-8')
        src = src.replace('round23', 'round24').replace('ROUND23', 'ROUND24').replace('R23', 'R24').replace('r23_', 'r24_').replace('r23-', 'r24-')
        src = src.replace("'experiment_round':'23'", "'experiment_round':'24'").replace("'round':23", "'round':24").replace('codex/round24-tenpct', 'codex/round24-stable-dual')
        (ROOT / 'scripts' / new).write_bytes(src.encode())
    p = ROOT.parents[1] / '.github/workflows/deflate-round9.yml'
    s = p.read_text()
    assert "'22', '23']" in s and '\n  round24:' not in s
    s = s.replace("'22', '23']", "'22', '23', '24']").replace("inputs.experiment_round != '23'", "inputs.experiment_round != '23' && inputs.experiment_round != '24'", 1)
    s += s[s.index('\n  round23:'):].replace('round23', 'round24').replace('ROUND23', 'ROUND24').replace("== '23'", "== '24'").replace('r23-', 'r24-')
    p.write_bytes(s.encode())
    for name, old, new in [
        ('round4.py', "'evidence/round22', 'evidence/round23')", "'evidence/round22', 'evidence/round23', 'evidence/round24')"),
        ('collect-round4.py', "'22', '23'], default='4'", "'22', '23', '24'], default='4'")
    ]:
        p = ROOT / 'scripts' / name
        s = p.read_text(); assert s.count(old) == 1
        p.write_bytes(s.replace(old, new).encode())
    print(json.dumps({'start': start.isoformat(), 'deadline': end.isoformat(), 'namespace': str(E)}))

if __name__ == '__main__':
    main()
