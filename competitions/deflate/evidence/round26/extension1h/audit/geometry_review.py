"""Read captured current evidence; write only this audit's planning results."""
import sys, json, importlib, hashlib
from pathlib import Path
from datetime import datetime, timezone

ROOT = Path(__file__).resolve().parents[4]
sys.path.insert(0, str(ROOT / 'scripts'))
M = importlib.import_module('r26-score-map')
OUT = Path(__file__).parent
CAP = ROOT / 'evidence/round26/extension1h/official-start'
RULES = ROOT / 'evidence/round26/extension4h/rules-start'
r = M.Replay(CAP, RULES)
audit = M.audit(r)
(OUT / 'api-audit-29907.json').write_text(json.dumps(audit, indent=2) + '\n', encoding='utf-8')
anchor = r.byid['658']['metrics']
x, y = anchor['balanced_time_ratio'], anchor['mean_file_compression_pct']
rows = []
for k in range(601):
    reduction = k / 100
    xx = x * (1 - reduction / 100)
    score = r.describe([('C2-hypothetical', xx, y)])['points']['C2-hypothetical']
    rows.append({'time_reduction_pct': reduction, 'x': xx, 'share_pct': score['share_pct'],
                 'terms': score['terms'], 'dominator_ids': score['dominator_ids']})
old = json.loads((ROOT / 'evidence/round26/extension4h/all-roles-29888.json').read_bytes())
controls = [row for row in old['all_same_source_controls']
            if row['main'] == 'public658' and row['copy'] == 'public658-shadow']
result = {'status': 'INFERRED_CURRENT_SNAPSHOT_FIXED_QUALITY_GEOMETRY_NOT_PERFORMANCE',
          'checked_utc': datetime.now(timezone.utc).isoformat(), 'snapshot': r.context,
          'anchor_id': '658', 'anchor_x': x, 'anchor_y_pct': y,
          'anchor_metrics_sha256': M.digest(CAP / 'pareto-pages.json'),
          'same_source_old_controls': controls,
          'nearest_sampled_targets': {str(t): next((p for p in rows if p['share_pct'] >= t), None)
                                     for t in [.1, .25, .5, 1, 5]},
          'grid': rows,
          'limits': ['Time reductions are hypothetical and cannot be promised by C2.',
                     'Historical control gaps are sensitivity context, not a future error bound.',
                     'Public calibration, formal admission and payable position remain unverified.',
                     'Nonmonotone scoring: nearest sampled target is not a speed guarantee.']}
(OUT / 'geometry-29907.json').write_text(json.dumps(result, indent=2) + '\n', encoding='utf-8')
print(json.dumps({'snapshot': r.context['snapshot_id'], 'frontier_count': len(r.base),
                  'targets': {t: None if p is None else (p['time_reduction_pct'], p['share_pct'])
                              for t,p in result['nearest_sampled_targets'].items()},
                  'control_gaps_pct': [p['relative_time_gap_pct'] for p in controls]}))
