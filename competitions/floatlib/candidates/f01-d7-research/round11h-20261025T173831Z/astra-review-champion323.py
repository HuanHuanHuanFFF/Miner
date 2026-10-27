"""Independent read-only successor-chain and weighted projection check."""
from pathlib import Path
from datetime import datetime, timezone
import hashlib, json, math, statistics

HERE=Path(__file__).resolve().parent
ROOT=HERE.parents[4]
D7=HERE.parent
S=D7/'official-20261026T111838Z'
read=lambda p:json.loads(p.read_bytes())
sha=lambda p:hashlib.sha256(p.read_bytes()).hexdigest()
unpack=lambda x:json.loads(x) if isinstance(x,str) else x
receipt=read(S/'receipts.json')
for item in receipt['responses'].values():
    p=S/item['file']; assert p.stat().st_size==item['bytes'] and sha(p)==item['sha256']
archive=HERE/'development-previous-champion-model.json'
oldpath=archive if archive.is_file() else D7/'champion-time-estimate.json'
assert sha(oldpath)=='9222bdf6edec6efe75c009203405357155045f75028727a2e1fc237b9a343e53'
old=read(oldpath); previous=unpack(read(ROOT/old['champion_report'])['report'])
assert sha(ROOT/old['champion_report'])==old['champion_report_sha256']
detail=read(S/'champion-detail.raw'); report=unpack(read(S/'champion-report.raw')['report'])
current=next(x for x in read(S/'champions.raw') if x['current'])
assert detail['id']==current['submission']==read(S/'leaderboard.raw')['leader']==int(report['submission'])==323
assert detail['state']=='accepted' and detail['verification_current'] and report['passed']
assert detail['classes']==report['classes']
assert detail['champion_sha256']==report['champion_sha256']==old['champion_digest']
assert detail['incumbent_sha256']==report['incumbent_sha256']
assert detail['verifier_fingerprint']==report['verifier_fingerprint']==report['verifier_fingerprint_end']==previous['verifier_fingerprint']==previous['verifier_fingerprint_end']
assert report['suite']==old['champion_suite'] and set(report['classes'])==set(previous['classes'])
assert report['reference_complete'] and not report['incumbent_failed'] and not report['exhausted'] and len(report['rounds'])==25
assert receipt['responses']['champion-report']['url'].endswith('/submissions/323/report')
assert receipt['responses']['champion-source']['status']==404
assert old['status']=='INFERRED'
ops=('add','mul','sum','bmm'); computed={op:[] for op in ops}; whole=[]
for sample in old['samples']:
    denominators={}
    for op in ops:
        cells=[c for c in previous['classes'] if c.startswith(op+':')]
        base=sample['champion_projected_total_ns'][op]
        weights={c:previous['classes'][c]['submission_ns']*sample['cell_work'][c]/base for c in cells}
        assert math.isclose(sum(weights.values()),1,rel_tol=1e-12)
        factor=0
        for c in cells:
            row=report['classes'][c]
            assert row['submission_ns']>0 and row['incumbent_ns']>0
            ratio=row['submission_ns']/row['incumbent_ns']
            assert math.isclose(ratio,row['ratio'],rel_tol=1e-12)
            factor+=weights[c]*ratio
        denominators[op]=base*factor
        computed[op].append(sample['candidate_total_ns'][op]/denominators[op])
    whole.append(sum(sample['candidate_total_ns'].values())/sum(denominators.values()))
result={'checked_utc':datetime.now(timezone.utc).isoformat(),'state':'CHAIN_AND_ESTIMATOR_FORMULA_VERIFIED_MODEL_REMAINS_INFERRED',
 'snapshot':S.name,'receipt_sha256':sha(S/'receipts.json'),'old_model_sha256':sha(oldpath),
 'old_reference_digest':old['champion_digest'],'new_official_reported_digest':detail['digest'],
 'suite':report['suite'],'frozen_workloads':len(old['samples']),
 'independent_operation_medians':{op:statistics.median(computed[op]) for op in ops},
 'independent_whole_median':statistics.median(whole),
 'checks':['All raw hashes/lengths','323 endpoint/id/detail/classes agreement','309 raw reference digest chain','Separate transformed incumbent digest agreement','Same suite and verifier','25-round complete report','Weighted cell-ratio projection and workload medians'],
 'limits':['Report has no own-source SHA field; new digest is official detail metadata tied by323 endpoint/id/classes, source404','Original cross-suite/cross-host calibration uncertainty remains','No new candidate cost, source delta, or workload refit','Not a direct B2 versus323 benchmark or official admission'],
 'apply_by':'D only; retain original9222 bytes and INFERRED status/scope; no changes made by this checker'}
out=HERE/('astra-review-champion323-replay.json' if (HERE/'astra-review-champion323.json').exists() else 'astra-review-champion323.json')
out.write_text(json.dumps(result,ensure_ascii=False,indent=2)+'\n',encoding='utf-8')
print(json.dumps(result,ensure_ascii=False))
