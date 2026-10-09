"""Read-only comparison of captured official reward snapshots."""
import json
from datetime import datetime
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
DEST = ROOT / 'evidence/reward-analysis-20261010'
def read(p):
    return json.loads(p.read_text(encoding='utf-8-sig'))
current = read(DEST / 'leaderboard-pages.json')
ranking = [r for p in current for r in p['ranking']]
assert len(ranking) == len({r['hotkey'] for r in ranking})
assert current[-1].get('next_cursor') is None
history = {}
for path in (ROOT / 'evidence').rglob('leaderboard-pages.json'):
    pages = read(path)
    if not pages or pages[-1].get('next_cursor'):
        continue
    context = pages[0]['context']
    assert all(p['context']['snapshot_id'] == context['snapshot_id'] for p in pages)
    history[context['snapshot_id']] = (context, {r['hotkey']: r for p in pages for r in p['ranking']})
pareto = {r['id']: r for p in read(DEST/'pareto-pages.json') for r in p['items']}
results = []
for r in sorted(ranking, key=lambda r:r.get('bounty_earned_alpha') or 0, reverse=True)[:20]:
    observations = []
    for context, rows in sorted(history.values(), key=lambda pair:datetime.fromisoformat(pair[0]['computed_at'])):
        if r['hotkey'] in rows:
            old = rows[r['hotkey']]
            observations.append({'snapshot_id':context['snapshot_id'], 'at':context['computed_at'], 'share_pct':100*old['payable_weight'], 'earned_alpha':old.get('bounty_earned_alpha')})
    submissions = [{'id':i, 'submitted_at':pareto[i]['submitted_at'], 'metrics':pareto[i].get('metrics'), 'score':pareto[i].get('score')} for i in r['submission_ids'] if i in pareto]
    results.append({'hotkey':r['hotkey'],'ids':r['submission_ids'],'current_share_pct':100*r['payable_weight'],'earned_alpha':r.get('bounty_earned_alpha'),'observations':observations,'submissions':submissions})
output={'current_context':current[0]['context'],'ranking_rows':len(ranking),'history_snapshots':len(history),'top_earned':results,'limits':'Sparse snapshots, not continuous frontier duration or peak; official accounting, not independently checked chain receipt. Hotkeys are not identities.'}
(DEST/'analysis.json').write_text(json.dumps(output,ensure_ascii=False,indent=2)+'\n',encoding='utf-8')
print(json.dumps({k:v for k,v in output.items() if k!='top_earned'},ensure_ascii=False))
for r in results:
    obs=r['observations']; peak=max(obs,key=lambda o:o['share_pct']) if obs else None
    print(json.dumps({'ids':r['ids'],'earned':r['earned_alpha'],'now':r['current_share_pct'],'first':obs[0] if obs else None,'peak_observed':peak,'submitted':[s['submitted_at'] for s in r['submissions']]},ensure_ascii=False))
