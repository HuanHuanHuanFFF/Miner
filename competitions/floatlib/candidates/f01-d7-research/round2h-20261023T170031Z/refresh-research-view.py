"""Display the fully measured research leader without changing the retained kernel."""
from pathlib import Path
import datetime, hashlib, importlib.util, json

root=Path(__file__).resolve().parents[5]
out=Path(__file__).resolve().parent
d7=out.parent
spec=importlib.util.spec_from_file_location('estimate',root/'competitions/floatlib/scripts/estimate_champion_time.py')
e=importlib.util.module_from_spec(spec);spec.loader.exec_module(e)
freeze=e.load(out/'cohort-freeze.json')
candidate=freeze['candidate']['name'];sha=freeze['candidate']['sha256']
source=root/'competitions/floatlib/candidates'/candidate/'Kernel.lean'
assert e.sha(source)==sha
view_path=d7/'multiplier-comparison.json';view=e.load(view_path)
state_path=root/'competitions/floatlib/coordination/development-status.json';state=e.load(state_path)
retained_before=(state['kernel'],state['kernel_sha256'],state['performance'])
records=e.load(d7/'public-suite-results.json')['records']
rows=[r for r in records if r['kernel_sha256']==sha and r.get('full_gate')]
runs=sorted(r['run'] for r in rows)
assert len(set(runs))==len(runs) and len({r['seed'] for r in rows})>=3
anchor=e.load(e.DEFAULT_ANCHOR);e.validate_anchor(anchor)
snapshot=e.load(d7/'current-official-snapshot.json')
official=d7/snapshot['directory']
detail=e.load(official/'champion-detail.raw')
report=e.load(official/'champion-report.raw')['report']
report=json.loads(report) if isinstance(report,str) else report
assert detail['id']==view['champion']['submission']==snapshot['champion']
assert detail['digest']==anchor['champion_digest'] and report['suite']==anchor['champion_suite']
pairs=e.select_pairs(records,runs,sha,anchor,root)
model=e.estimate_from_anchor(anchor,sha,detail['digest'],report['suite'],pairs)
model.update(candidate=candidate,full_gate_runs=runs,as_of_utc=datetime.datetime.now(datetime.timezone.utc).isoformat(),
             estimator_sha256=e.sha(root/'competitions/floatlib/scripts/estimate_champion_time.py'),
             anchor=e.DEFAULT_ANCHOR.relative_to(root).as_posix(),anchor_sha256=e.sha(e.DEFAULT_ANCHOR),
             champion_submission=detail['id'],retained=False,
             selection_scope='Research display only. Every exact-source complete input group is included. Retention policy and current kernel unchanged.')
path=out/'best-research-champion-estimate.json'
e.save(path,model)
if model['whole']['ratio_median']<view['champion_time_estimate']['whole']['ratio_median']:
    displayed={'candidate':candidate,'kernel':source.relative_to(root).as_posix(),'kernel_sha256':sha,
               'full_gate_runs':runs,'evidence':path.relative_to(root).as_posix(),'evidence_sha256':e.sha(path),
               'retained':False,'bmm_label':'按行寻址'}
    view['dashboard_research_candidate']=displayed
    state['current_multiplier_view']['displayed_research_candidate']=displayed
else:
    view.pop('dashboard_research_candidate',None)
    state['current_multiplier_view'].pop('displayed_research_candidate',None)
assert retained_before==(state['kernel'],state['kernel_sha256'],state['performance'])
e.save(view_path,view);e.save(state_path,state)
print(json.dumps({'displayed':view.get('dashboard_research_candidate'),'operations':model['operations'],'whole':model['whole'],'retained_unchanged':True}))
