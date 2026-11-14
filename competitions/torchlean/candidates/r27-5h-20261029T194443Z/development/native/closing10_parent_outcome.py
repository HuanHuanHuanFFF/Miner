from pathlib import Path
from datetime import datetime,timezone
import hashlib,json
HERE=Path(__file__).resolve().parent;BASE=HERE.parents[1]
p=BASE/'CI-RESULTS-BATCH10.json';d=json.loads(p.read_text(encoding='utf-8'))
assert d['state']=='ACTUAL_ALL12_GATE_PASS_STANDARD_COST_INSUFFICIENT'
g=d['full_gates'][0];r=d['results'][0]
assert g['source_sha256']==r['candidate_sha256']=='f60551d55be31d2d2d4a59ba2646c8769d1cb8e31538176041070a0477881bea'
assert g['exit_code']==0 and g['verdict']['passed'] and g['verdict']['stage']=='axioms'
counts={k:sum(x[k] for x in r['counts']) for k in ['paired_rows','ns_values','checksum_pairs']}
assert counts=={'paired_rows':792,'ns_values':1584,'checksum_pairs':792}
out={'at_utc':datetime.now(timezone.utc).isoformat(),'run':d['run'],'source_commit':d['source_commit'],
 'source_sha256':g['source_sha256'],'source_bytes':255666,'canonical_receipt':'../../CI-RESULTS-BATCH10.json','canonical_sha256':hashlib.sha256(p.read_bytes()).hexdigest(),
 'formal_scope':'VERIFIED_ORIGINAL_ALL12_GATE_BY_PARENT_CANONICAL_EVIDENCE','verdict':g['verdict'],
 'measurement_scope':'Parentfixedaudit, notindependentlyrescoredhere; twofreshrootstandard11/3/50 samples complete',
 'counts':counts,'target_snapshot':{'board':'mixer','last_verified_current':36,'time_over_champion_estimate':r['candidate_time_over_current_champion_estimate'],'comparison':'INFERRED report-chain crossenv, no privatecurrent-source directpair or officialranking'},
 'guard_passed':r['score_vs_calibration_internal']['guard_passed'],'decision':'PERFORMANCE_INSUFFICIENT_NO_ADOPTION_NO_CHAMPION_CLAIM',
 'metadata_note':'Generic resultstatus NATIVE_ONLY_EXPLORATION_AUDITED is measurementmode metadata; actual candidate_proof FULL_ORIGINAL_GATE_REPLAYED and exactall12PASS are authoritative forproofscope. Do notlabelthissourceunproved',
 'remaining_scope_gap':'NativeAdd-only, no optimizeddonor smallKYa3 restored. RMSoriginalkernel0, LayerNormMYbc retained. All12functionaloperators present',
 'freeze':'10complete andinputsnowseen; frozen source/roots notretuned. No newperformancequeue bythisrole',
 'work_window':'Sharedfixed00:44:43 unchanged; acceptedproof andfailedperformance are separate'}
(HERE/'CLOSING10-VERIFIED-PARENT-OUTCOME.json').write_bytes((json.dumps(out,indent=2)+'\n').encode())
print(json.dumps({'run':d['run'],'proof':out['formal_scope'],'counts':counts,'current36_time_estimate':out['target_snapshot']['time_over_champion_estimate'],'adopted':False}))
