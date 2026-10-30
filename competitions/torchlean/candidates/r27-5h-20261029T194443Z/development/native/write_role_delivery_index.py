"""Curate exact role outcomes without consuming ongoing acceptance outputs."""
from pathlib import Path
from datetime import datetime,timezone
import hashlib,json
HERE=Path(__file__).resolve().parent;BASE=HERE.parents[1]
def file(name):
 p=HERE/name;raw=p.read_bytes();return {'path':name,'bytes':len(raw),'sha256':hashlib.sha256(raw).hexdigest()}
history=[]
for batch in [6,8,9,11,10,12]:
 p=BASE/f'CI-RESULTS-BATCH{batch}.json'
 if not p.is_file():continue
 d=json.loads(p.read_text(encoding='utf-8'));state=d.get('state','')
 if batch in [10,12] and not (any(t in state.lower() for t in ['terminal','collected','complete']) or state.startswith('ACTUAL_ALL12_GATE_PASS_STANDARD_COST_')):
  history.append({'batch':batch,'state':'ACCEPTANCE_ONGOING_NOT_READ_FOR_RESULTS'});continue
 row={'batch':batch,'run':d.get('run'),'canonical_receipt':f'../../CI-RESULTS-BATCH{batch}.json','canonical_sha256':hashlib.sha256(p.read_bytes()).hexdigest(),'state':state}
 results=[]
 for r in d.get('results',[]):
  results.append({k:r.get(k) for k in ['candidate','candidate_sha256','current_champion_submission','candidate_time_over_current_champion_estimate','candidate_proof','eligibility','status']})
 row['results']=results
 row['full_gates']=[{'name':g.get('name'),'source_sha256':g.get('source_sha256'),'exit_code':g.get('exit_code'),'passed':g.get('verdict',{}).get('passed'),'stage':g.get('verdict',{}).get('stage')} for g in d.get('full_gates',[])]
 row['interpretation']='Parent canonical fixed audit, not independently recomputed by this role; ratio is historical-current-report-chain INFERRED, not liveprivate-source/directranking'
 history.append(row)
assets=[
 'ReciprocalUInt64ContractOnly-v4.lean','ACCEPTED-RECIPROCAL-COMPONENT.md','batch6-native-result.json','CLOSING10-VERIFIED-PARENT-OUTCOME.json',
 'public23_block16_cost_v2.py','Block16PreparedUnrolled.lean.inc','public23-block16-unrolled-cost-receipt.json','block16-model.json','block16-actual-guard-census.json',
 'selected-gemm-c9-critical-review.json','graft_native_add_portfolio10.py','graft_native_add_portfolio10_v2.py','native-add-portfolio10-v2-receipt.json','CI-REQUEST-17-QUALIFIED-ADDENDUM.json','PORTFOLIO10-SMALLK-SCOPE-GAP.json',
 'followon-band/BandRuntime.lean.inc','followon-band/band-native-cost-receipt.json','followon-band/band-source-model.json',
 'followon-band/BandRuntime-v2.lean.inc','followon-band/repair_band_v2.py','followon-band/band-types-v2-repair-receipt.json','BAND11-TYPE-REPAIR-READY.json',
 'followon-whole64/DECISION.md','followon-whole64/whole64-scaling-census.json','followon-whole64/SPLIT12-UNEXECUTED-NOTE.md',
 'archive/graft_native_add_portfolio10-precanonical.py','native-add-portfolio10-precanonical-receipt.json']
now=datetime.now(timezone.utc).isoformat()
out={'updated_at_utc':now,'role':'Dnative','first_clock_utc':'2026-10-29T19:46:53Z','common_start_utc':'2026-10-29T19:44:43Z','common_deadline_utc':'2026-10-30T00:44:43Z','actual_end_utc':None,
 'state':'COLLECTING_CLOSING10_AND_CURATING_TO_FIXED_DEADLINE','current_selected_source':{'sha256':'f60551d55be31d2d2d4a59ba2646c8769d1cb8e31538176041070a0477881bea','bytes':255666,'recipe_sha256':'5af18daceb4906bed7cdb46999f73dec17d5dd62ea37479bca0ad387ddc59880','run':40977309820,'scope':'NativeAdd-only, allpositiveGEMM9 andMYbc retained, RMSoriginalkernel0; optimizedsmallKrestore notimplemented','proof':'Actualall12connected, use terminalcanonical10 for accepted/rejected status'},
 'canonical_outcomes':history,'assets':[file(n) for n in assets],
 'negative_route_decisions':['Reciprocalactualcompletecost insufficient; retainaccepted4root helper only','Block16b1 smallinsufficientgain, allrowsguardfail; stopactualendpointprimary','FPonlylazy2.405xhistoricalcurrent43; no fullactualproof','Commonweighttrailingzero premise0 onall1980oldseenweightrow observations; no implementation','Band11 only2literaltypeerrors, no candidate timing; repairafd08uncompiled fornextwindow'],
 'freeze_and_authority':'No9/10 nativeoutputs used for source tuning. OnlyparentDrootGit/CI/publication. No newlongroutes after00:00; closing10 predeclared beforecutoff andstarted00:04:22 perparent. No formalcontest/funds/reset/localLean-native builds',
 'resources':{'actual_tokens':'UNKNOWN','cached_input_tokens':'UNKNOWN','model_cpu':'UNKNOWN','own_CI_dispatches':0,'own_Git_mutations':0,'local_Lean_native_builds':0},
 'public_index':'NATIVE-PUBLIC-MANIFEST.json; currentCoordinatorprivacy exclusions authoritative. RawmaterializedKernel andbulkZIP hash-onlylocal here; no fullunknownlicense23/27 bodies inpublic set',
 'completion_boundary':'Window completion and anyboardchampion goal are separate. Never infer eligibility/currentranking from finitechecksums, standalone proof roots or a negativeexperiment workflow state'}
(HERE/'ROLE-DELIVERY-INDEX.json').write_bytes((json.dumps(out,indent=2)+'\n').encode())
print(json.dumps({'updated_at_utc':now,'canonical_batches':[x['batch'] for x in history],'assets':len(assets),'closing10_result_available':any(x['batch']==10 and x.get('results') for x in history)}))
