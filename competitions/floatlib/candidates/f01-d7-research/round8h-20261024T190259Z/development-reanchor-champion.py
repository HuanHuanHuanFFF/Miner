"""Reviewed champion change: preserve frozen numerator/work; replace denominator only."""
from pathlib import Path
from datetime import datetime,timezone
from copy import deepcopy
import argparse,hashlib,importlib.util,json,math

OUT=Path(__file__).resolve().parent;ROOT=OUT.parents[4];DATA=OUT.parent
ap=argparse.ArgumentParser();ap.add_argument('--official',required=True);ap.add_argument('--apply',action='store_true');a=ap.parse_args()
def load(p):return json.loads(p.read_bytes())
def encoded(v):return (json.dumps(v,ensure_ascii=False,indent=2)+'\n').encode()
def digest(p):return hashlib.sha256(p.read_bytes()).hexdigest()
def module(name,p):
    spec=importlib.util.spec_from_file_location(name,p);m=importlib.util.module_from_spec(spec);spec.loader.exec_module(m);return m
est=module('r14_champion_estimator',ROOT/'competitions/floatlib/scripts/estimate_champion_time.py')
adopter=module('r14_reanchor_transaction',OUT/'adopt-three-confirmed.py')
official=DATA/a.official;assert official.resolve().parent==DATA.resolve()
receipt=load(official/'receipts.json');assert receipt['status']=='VERIFIED_SNAPSHOT' and receipt['compatible_frozen_protocol']
for key in ('champions','competition','champion-detail','champion-report'):
    rec=receipt['responses'][key];p=official/rec['file'];assert rec['status']==200 and p.stat().st_size==rec['bytes'] and digest(p)==rec['sha256']
detail=load(official/'champion-detail.raw');report=load(official/'champion-report.raw')['report'];report=json.loads(report) if isinstance(report,str) else report
champ=next(r for r in load(official/'champions.raw') if r['current']);competition=load(official/'competition.raw')
assert detail['id']==receipt['champion']==champ['submission']==int(report['submission'])
assert detail['state']=='accepted' and detail['verification_current'] and report['passed'] and detail['classes']==report['classes']
old_anchor_path=DATA/'round2h-20261023T170031Z/freeze-anchor.json';old_anchor=load(old_anchor_path);est.validate_anchor(old_anchor)
model_path=DATA/'champion-time-estimate.json';old_model=load(model_path)
assert digest(model_path)=='5d946420b8e1a7ecc68aacde44b0e2910a467ee3e3546724d502f252fe8a031f'
assert old_model['champion_submission']==285 and detail['id']!=285 and detail['digest']!=old_anchor['champion_digest']
assert report['suite']==old_anchor['champion_suite']
index=load(DATA/'public-suite-results.json')['records'];pairs=[]
for prior in old_model['paired_updates']:
    def get(sha):
        rows=[r for r in index if r['run']==prior['run'] and r['kernel_sha256']==sha and r.get('full_gate')]
        assert len(rows)==1
        return est.checked_record(rows[0],ROOT)
    c,b=get(old_model['kernel_sha256']),get(old_anchor['candidate_kernel_sha256'])
    assert c['verdict_sha256']==prior['candidate_verdict_sha256'] and b['verdict_sha256']==prior['baseline_verdict_sha256']
    pairs.append((c,b))
reproduced=est.estimate_from_anchor(old_anchor,old_model['kernel_sha256'],old_anchor['champion_digest'],old_anchor['champion_suite'],pairs)
assert reproduced['operations']==old_model['operations'] and reproduced['whole']==old_model['whole']
assert reproduced['cell_relative_delta_median']==old_model['cell_relative_delta_median']
now=datetime.now(timezone.utc).isoformat();original=deepcopy(old_anchor['original_model'])
original.update(champion_submission=detail['id'],champion_digest=detail['digest'],champion_suite=report['suite'],as_of_utc=now,
                champion_report=(official/'champion-report.raw').relative_to(ROOT).as_posix(),champion_report_sha256=digest(official/'champion-report.raw'),
                official_receipts=(official/'receipts.json').relative_to(ROOT).as_posix(),official_receipts_sha256=digest(official/'receipts.json'))
for sample in original['samples']:
    projected={op:sum(v['submission_ns']*sample['cell_work'][cell] for cell,v in report['classes'].items() if cell.startswith(op+':')) for op in est.OPS}
    sample.update(champion_projected_total_ns=projected,operation_ratios={op:sample['candidate_total_ns'][op]/projected[op] for op in est.OPS},whole_ratio=sum(sample['candidate_total_ns'].values())/sum(projected.values()))
original.update(operations={op:est.aggregate([s['operation_ratios'][op] for s in original['samples']]) for op in est.OPS},whole=est.aggregate([s['whole_ratio'] for s in original['samples']]))
provenance={'kind':'REVIEWED_CHAMPION_CHANGE_ONLY','previous_anchor':old_anchor_path.relative_to(ROOT).as_posix(),'previous_anchor_sha256':digest(old_anchor_path),
            'old_champion':285,'new_champion':detail['id'],'official_receipts_sha256':digest(official/'receipts.json'),
            'rule':'Keep every frozen source, source costs, matched deltas, record order and workload unchanged; only project the new champion group costs.'}
anchor=est.build_frozen_anchor(original,old_anchor['frozen_records'],provenance,report['classes']);est.validate_anchor(anchor)
new=est.estimate_from_anchor(anchor,old_model['kernel_sha256'],detail['digest'],report['suite'],pairs)
assert all(n['candidate_total_ns']==o['candidate_total_ns'] and n['cell_work']==o['cell_work'] for n,o in zip(new['samples'],old_model['samples']))
assert new['cell_relative_delta_median']==old_model['cell_relative_delta_median']
assert len(new['samples'])==len(old_model['samples']) and len(pairs)==len(old_model['paired_updates'])
for sample in new['samples']:
    for op in est.OPS:
        independent=sum(detail['classes'][cell]['submission_ns']*work for cell,work in sample['cell_work'].items() if cell.startswith(op+':'))
        assert math.isclose(independent,sample['champion_projected_total_ns'][op],rel_tol=1e-14)
        assert math.isclose(sample['operation_ratios'][op],sample['candidate_total_ns'][op]/independent,rel_tol=1e-14)
try: est.estimate_from_anchor(old_anchor,old_model['kernel_sha256'],detail['digest'],report['suite'],pairs)
except est.EstimateRejected: pass
else: raise AssertionError('Old anchor must reject a new champion')
anchor_path=OUT/'freeze-anchor.json'
new.update(candidate=old_model['candidate'],as_of_utc=now,estimator_sha256=digest(ROOT/'competitions/floatlib/scripts/estimate_champion_time.py'),
           anchor=anchor_path.relative_to(ROOT).as_posix(),anchor_sha256=hashlib.sha256(encoded(anchor)).hexdigest(),
           current_public_results_sha256=digest(DATA/'public-suite-results.json'),current_champion_report=(official/'champion-report.raw').relative_to(ROOT).as_posix(),
           current_champion_report_sha256=digest(official/'champion-report.raw'),reanchor=provenance)
preview={'status':'VERIFIED_DENOMINATOR_ONLY_REANCHOR','old_champion':285,'new_champion':detail['id'],'source_sha256':old_model['kernel_sha256'],
         'source_costs_and_work_unchanged':True,'source_delta_samples_unchanged':True,'source_samples':len(new['samples']),'paired_samples':len(pairs),
         'old_operations':old_model['operations'],'new_operations':new['operations'],'old_whole':old_model['whole'],'new_whole':new['whole'],
         'new_anchor_sha256':new['anchor_sha256'],'new_model_sha256':hashlib.sha256(encoded(new)).hexdigest(),'apply':a.apply}
if a.apply:
    paths=[model_path,anchor_path,DATA/'multiplier-comparison.json',DATA/'current-official-snapshot.json',ROOT/'competitions/floatlib/coordination/development-status.json',OUT/'retained-estimate-freeze.json',OUT/'round-plan.json',OUT/'development-before-champion309-model.json']
    tx=adopter.Transaction(paths)
    assert tx.before[model_path.resolve()]==encoded(old_model) or json.loads(tx.before[model_path.resolve()])==old_model
    assert tx.before[anchor_path.resolve()] is None
    summary={k:new[k] for k in ('status','method','candidate','kernel_sha256','champion_submission','champion_digest','operations','whole')}
    summary.update(evidence=model_path.relative_to(ROOT).as_posix(),evidence_sha256=hashlib.sha256(encoded(new)).hexdigest())
    view=load(DATA/'multiplier-comparison.json');state=load(ROOT/'competitions/floatlib/coordination/development-status.json');plan=load(OUT/'round-plan.json')
    view['champion'].update(submission=detail['id'],digest=detail['digest'],snapshot=competition['current_snapshot_id'],official_cumulative_speedup_vs_shipped=champ['speedup_vs_shipped'],official_speedup_basis=champ['speedup_basis'],receipts=(official/'receipts.json').relative_to(ROOT).as_posix(),candidate_over_champion_time='UNKNOWN',candidate_over_champion_time_by_operation={op:'UNKNOWN' for op in est.OPS})
    view.update(champion_time_estimate=summary,as_of_utc=now)
    assert not view.get('dashboard_research_candidate')
    state['current_multiplier_view'].update(official_champion=detail['id'],snapshot=competition['current_snapshot_id'],champion_time_estimate=summary,champion_official_historical_speedup_vs_shipped=champ['speedup_vs_shipped'],champion_official_speedup_basis=champ['speedup_basis'])
    state['current_champion_comparison'].update(submission=detail['id'],source_digest=detail['digest'],policy_snapshot=competition['current_snapshot_id'],queried_at_utc=receipt['queried_at_utc'])
    plan['frozen_current_model_sha256']=summary['evidence_sha256']
    retained={'recorded_at_utc':now,'candidate':new['candidate'],'source_sha256':new['kernel_sha256'],'champion':detail['id'],'champion_digest':detail['digest'],'model_path':summary['evidence'],'model_sha256':summary['evidence_sha256'],'anchor_sha256':new['anchor_sha256'],'original_model_sha256':digest(model_path),'declared_source_full_gate_runs':[p['run'] for p in new['paired_updates']],'rule':'Keep numeric model frozen for this exact source and champion; refresh raw control counts independently.'}
    snapshot={'queried_at_utc':receipt['queried_at_utc'],'champion':detail['id'],'official_commit':receipt['official_commit'],'directory':a.official,'policy_snapshot':competition['current_snapshot_id']}
    values={model_path:new,anchor_path:anchor,DATA/'multiplier-comparison.json':view,DATA/'current-official-snapshot.json':snapshot,ROOT/'competitions/floatlib/coordination/development-status.json':state,OUT/'retained-estimate-freeze.json':retained,OUT/'round-plan.json':plan,OUT/'development-before-champion309-model.json':old_model}
    try:
        for p,v in values.items():tx.write(p,encoded(v))
        tx.unchanged()
    except BaseException:
        tx.rollback();raise
(OUT/('development-reanchor-applied.json' if a.apply else 'development-reanchor-preview.json')).write_bytes(encoded(preview))
print(json.dumps(preview,ensure_ascii=False))
