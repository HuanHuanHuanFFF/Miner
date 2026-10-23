"""Cost boundary from completed807 counts and original fullgate cells; no new timing."""
from collections import Counter
from datetime import datetime, timezone
import hashlib
import json
from pathlib import Path

HERE=Path(__file__).resolve().parent
ROOT=HERE.parents[3]
R=ROOT/'competitions/floatlib/research/astra-collab-20261023-r7'
inputs={}
def load(path):
    raw=path.read_bytes()
    inputs[path.relative_to(ROOT).as_posix()]={'sha256':hashlib.sha256(raw).hexdigest(),'bytes':len(raw)}
    return json.loads(raw)
low=load(R/'sum-decoder-low-screen.json')
results=load(HERE/'public-suite-results.json')
retained=next(row for row in results['records'] if row['run']==39840672791 and row['candidate']=='f01-d7-direct-nonnan')
parent=next(row for row in results['records'] if row['run']==39840672791 and row['candidate']=='f01-r7-nonnan-runtime')
assert low['plan_sha256']=='9cc5d7368749c369172b019d66bc4cd8455ae4323d0b9a175bd031f936e78622'
assert retained['full_gate'] and parent['full_gate']
assert retained['kernel_sha256']=='60f74aa4af01a9b35ece66a7c310e6b05b5b84b9b7121a4cccd12a0a9c987e15'
assert parent['kernel_sha256']=='c76056882d69a1122da44b4bc0bb3ab5274251826f0677af2aec5771926d7435'
by_cell={}
for row in low['cases']:
    if not row['timed']:continue
    cell=row['name'].rsplit(':',1)[0]
    out=by_cell.setdefault(cell,Counter())
    for key in ['all_words','low_normal_full','subnormal_full','zero_full']:
        out[key]+=row[key]
assert sum(x['all_words'] for x in by_cell.values())==5046844
assert sum(x['low_normal_full'] for x in by_cell.values())==295268
assert sum(x['subnormal_full'] for x in by_cell.values())==32164
total_time=sum(retained['operation_total_ns'].values())
parent_total=sum(parent['operation_total_ns'].values())
rows=[]
for cell,counts in by_cell.items():
    work=retained['cell_work'][cell]
    assert counts['all_words']==work,(cell,counts['all_words'],work)
    times=retained['classes'][cell]['submission_ns']*work
    row={'cell':cell,**counts,'observed_retained_cell_ns':times,
         'observed_retained_cell_share_percent':times/total_time*100,
         'new_low_branch_guard_evaluations':counts['low_normal_full']+counts['subnormal_full'],
         'new_helper_hits':counts['low_normal_full'],
         'new_low_branch_guard_nonzero_subnormal_misses':counts['subnormal_full']}
    rows.append(row)
eligible=[row for row in rows if row['new_helper_hits']]
guard_count=sum(row['new_low_branch_guard_evaluations'] for row in rows)
hit_count=sum(row['new_helper_hits'] for row in rows)
miss_count=guard_count-hit_count
eligible_parent=sum(parent['classes'][row['cell']]['submission_ns']*parent['cell_work'][row['cell']] for row in eligible)
out={'status':'SOURCE_COUNT_AND_COMPLETED_CELL_COST_BOUNDARY_ONLY',
     'computed_at_utc':datetime.now(timezone.utc).isoformat(),
     'candidate':'f01-r7-low-normal-sum-decode',
     'candidate_sha256':'353d9816425d92fbc6d0cc14c9d30e17fb64d6d4fb7ebdf594700ef02c417c2a',
     'discovery_run':39840672791,'discovery_seed':807,'inputs':inputs,
     'cell_rows':rows,
     'counted_guard_evaluations':guard_count,'counted_helper_hits':hit_count,
     'counted_guard_misses':miss_count,
     'helper_hit_fraction_all_sum_input_words':hit_count/5046844,
     'helper_hit_fraction_new_guard_evaluations':hit_count/guard_count,
     'new_guard_fraction_all_sum_input_words':guard_count/5046844,
     'affected_cells':[row['cell'] for row in eligible],
     'retained_complete_involved_cell_time_share_percent_ceiling':sum(row['observed_retained_cell_share_percent'] for row in eligible),
     'isolated_parent_complete_involved_cell_time_share_percent_ceiling':eligible_parent/parent_total*100,
     'break_even_model':{
         'symbols':'S = net ns saved per helper-hit excluding its new guard; G = ns per new guard evaluation; L = all other layout/setup/loop changes in ns',
         'delta_ns':'295268*S - 327432*G - L',
         'zero_layout_required_S_over_G':guard_count/hit_count,
         'scope':'Symbolic first-order pass model only. No S/G/L measured, no cycles assigned and no independence/additivity assumed.'},
     'decision':'One distinct controlled decoder candidate only. Its measured source-cell exposure is smaller than the whole sum share; keep behind accepted nonfinite composition and singlepass proof feedback. Do not park it merely because only5.85percent of words hit: the added source guard is only on the old nonzero low branch.',
     'measurement_boundary':[
         'Original measure uses best of3 timed sweeps and original gate aggregates per-case samples across25 paired rounds. Counts are one repeated input pass, not multiplied by inner/rounds.',
         'Zero uses old unsigned-wrap table path; ordinary high/table and nonfinite branches keep source tests. Added threshold test occurs only for nonzero exponent0..23 inputs. Compiler may still change other branch layout.',
         'Entire involved cell time is an exposure ceiling, not helper time or a predicted saving. No claim that this one route can recover all of it.',
         '807 source counts anchored to prior actual outputs; 353d exact compile/fullgate/C/timing remain NOT_RUN. No private suite/prevalence or champion gap claimed.',
         '353d isolates c760 sum decoder. 3d9 is an alternative singlepass mechanism; these gains are not added.'
     ]}
(HERE/'low-normal-cost-screen.json').write_text(json.dumps(out,ensure_ascii=False,indent=2)+'\n',encoding='utf8')
print(json.dumps({k:out[k] for k in ['counted_guard_evaluations','counted_helper_hits','counted_guard_misses','retained_complete_involved_cell_time_share_percent_ceiling','isolated_parent_complete_involved_cell_time_share_percent_ceiling']},ensure_ascii=False))
