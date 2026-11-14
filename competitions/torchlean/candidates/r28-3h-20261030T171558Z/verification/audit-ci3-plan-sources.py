from pathlib import Path
import hashlib,importlib.util,json,datetime,sys,subprocess
sys.dont_write_bytecode=True
root=Path.cwd();round=root/'competitions/torchlean/candidates/r28-3h-20261030T171558Z';plan=json.loads((round/'ci-plan.json').read_bytes());request=json.loads((round/'CI-REQUEST.json').read_bytes());snap=round/'competition-state/refresh-20261030T181518Z';live=json.loads((snap/'receipt.json').read_bytes());boards=json.loads((snap/'boards.raw').read_bytes());mixer=json.loads((snap/'champions-mixer.raw').read_bytes())
root_status=json.loads((round/'development-status.json').read_bytes())
def digest(b):return hashlib.sha256(b).hexdigest()
def module(path,name):
 s=importlib.util.spec_from_file_location(name,path);m=importlib.util.module_from_spec(s);s.loader.exec_module(m);return m
ref=round/'competition-state/source-private/official-36.lean';refraw=ref.read_bytes();basehash=digest(refraw)
assert basehash==plan['reference']['sha256']==plan['reference']['fetch']['sha256']
source_results=[]
for entry in plan['candidates']:
 patch=root/entry['patch_script'];mod=module(patch,'r28_ci3_'+entry['name'].replace('-','_'))
 donor=None
 if entry.get('extra_fetches'):
  pin=entry['extra_fetches'][0]; donor=root/'competitions/torchlean/candidates/r27-5h-20261029T194443Z/competition-state/source-private/submission27-Kernel.lean'
  donorraw=donor.read_bytes(); donorhash=digest(donorraw); assert donorhash==pin['sha256']
 else: donorraw=None; donorhash=None
 try: built=mod.transform(refraw,36,entry['variant'],donor_raw=donorraw) if 'donor_raw' in mod.transform.__code__.co_varnames else mod.transform(refraw,36,entry['variant'])
 except TypeError: built=mod.transform(refraw,submission=36,variant=entry['variant'],donor_raw=donorraw)
 if isinstance(built,tuple): built=built[0]
 h=digest(built); size=len(built)
 source_results.append({'name':entry['name'],'sha256_recomputed':h,'sha256_planned':entry['sha256'],'hash_matches':h==entry['sha256'],'bytes_recomputed':size,'bytes_planned':entry['bytes'],'size_matches':size==entry['bytes'],'within_256000':size<=256000,'full_gate':entry.get('full_gate'),'declares_correct':entry.get('declares_correct'),'patch_script_sha256':digest(patch.read_bytes()),'patch_script_hash_matches_plan':digest(patch.read_bytes())==entry['patch_script_sha256'],'donor27_sha256':donorhash,'donor27_hash_matches_plan':donorhash==pin['sha256'] if donorhash and pin else None})
cur=[x for x in mixer['champions'] if x.get('current') is True]; mrec=next(x for x in live['receipts'] if x['url'].endswith('/champions?board=mixer')); boardsrec=next(x for x in live['receipts'] if x['url'].endswith('/boards'))
champbind=len(cur)==1 and cur[0]['submission']==plan['champion']['submission'] and cur[0]['source_sha256']==plan['champion']['source_sha256'] and cur[0]['ratio']==plan['champion']['current_champion_over_calibration'] and mixer['publication_hash']==boards['publication_hash']==plan['champion']['publication_hash'] and digest((snap/'champions-mixer.raw').read_bytes())==mrec['sha256']==plan['champion']['champion_response_sha256'] and digest((snap/'boards.raw').read_bytes())==boardsrec['sha256']==plan['champion']['boards_response_sha256'] and plan['reference']['fetch']['sha256']==next(x['source_sha256'] for x in mixer['champions'] if x['submission']==36)
planhash=digest((round/'ci-plan.json').read_bytes())
profile_path=root/plan['profile_adapter']; profile_hash=digest(profile_path.read_bytes()); profile_text=profile_path.read_text(encoding='utf-8')
profile_mod=module(profile_path,'r28_ci3_profile_review')
runner_text=(round/'development/ci-bridge/runner.py').read_text(encoding='utf-8')
head=subprocess.check_output(['git','rev-parse','HEAD'],cwd=root,text=True).strip()
plan_rel=(round/'ci-plan.json').relative_to(root).as_posix()
dispatch_dirs=sorted((round/'evidence').glob('dispatch-*/dispatch.json'))
dispatch=None
for path in dispatch_dirs:
 candidate=json.loads(path.read_bytes())
 if candidate.get('run',{}).get('databaseId')==request.get('run'):
  dispatch=candidate; break
assert dispatch is not None
freeze_paths=[Path('.github/workflows/deflate-baseline.yml'),Path('competitions/torchlean/candidates/r28-3h-20261030T171558Z/development/ci-bridge/client.py'),Path('competitions/torchlean/candidates/r28-3h-20261030T171558Z/development/ci-bridge/terminal-evidence.py'),Path(plan['prepare_script']),Path(plan_rel)]+[Path(x['path']) for x in plan.get('helpers',[])]+[Path(x) for x in plan.get('owned_sources',[])]
frozen=[]
for path in freeze_paths:
 rel=path.as_posix(); current=(root/rel).read_bytes(); wh=digest(current)
 try:
  blob=subprocess.check_output(['git','show',f'{head}:{rel}'],cwd=root); bh=digest(blob); tracked=True
 except subprocess.CalledProcessError:
  bh=None; tracked=False
 frozen.append({'path':rel,'commit_blob_sha256':bh,'workspace_sha256':wh,'tracked_in_head':tracked,'commit_blob_matches_workspace':tracked and bh==wh})
request_active=[x for x in root_status.get('active_CI',[]) if x.get('run')==request.get('run')]
profile_checks={'profile_sha256_matches_plan':profile_hash==plan['profile_adapter_sha256'],'profile_is_frozen_owned_source':plan['profile_adapter'] in plan['owned_sources'],'four_entry_mapping':profile_mod.KERNELS=={'YaVM':'linear','Ya3M':'gemm','Ybf':'add_relu','YbcN':'layernorm'},'global_profile_cap_240':plan.get('profile_budget_seconds')==240 and 'time.monotonic()+240' in profile_text,'per_call_profile_cap_20':'min(20,max(1,global_end-time.monotonic()-15))' in profile_text,'reference_only_profile_nonfatal':"if plan.get('profile_control') and entry.get('reference')" in runner_text and "record['cost_profile']={'state':'INCOMPLETE_DIAGNOSTIC_ONLY'" in runner_text}
checks={'root_request_state_valid':request['state'] in {'READY','RUN_IDENTIFIED'},'root_request_plan_matches':request['plan_sha256']==planhash,'dispatch_plan_matches':dispatch['frozen_files'].get(plan_rel)==planhash,'root_request_candidates_match':[x['sha256'] for x in plan['candidates']]==request['candidate_hashes'],'dispatch_request_matches_root':dispatch['state']=='RUN_IDENTIFIED' and dispatch['run']['databaseId']==request['run'] and dispatch['source_commit']==head==dispatch['run']['headSha'],'request_run_active_in_root':len(request_active)==1,'manual_public_false_inputs':dispatch['repository_public'] is True and dispatch['request']['inputs']['allow_private']=='false' and dispatch['request']['inputs']['candidates']=='__torchlean_r28__','reference_hash_matches_saved_source':basehash==plan['reference']['sha256'],'fresh_mixer_champion_bound':champbind,'all_candidate_transforms_match':all(x['hash_matches'] and x['size_matches'] and x['patch_script_hash_matches_plan'] for x in source_results),'nativeonly_boundary_explicit':plan['candidates'][0]['full_gate'] is False and plan['candidates'][0]['declares_correct'] is False,'two_fullgate_candidates_explicit':all(x['full_gate'] is True and x['declares_correct'] is True for x in plan['candidates'][1:]),'quick_only_not_confirmation':plan['measurement_mode']=='quick' and len(plan['seeds'])==2 and 'confirmation' not in plan,'frozen_commit_blobs_match_workspace':all(x['commit_blob_matches_workspace'] for x in frozen),'profile_boundary_and_hashes':all(profile_checks.values())}
out={'round':'R28','scope':'READ_ONLY_CI3_MIXER_PLAN_AND_EXACT_SOURCE_HASH_RECONSTRUCTION','captured_at_utc':datetime.datetime.now(datetime.timezone.utc).isoformat(),'source_commit':head,'run':request.get('run'),'plan_sha256':planhash,'request_plan_sha256':request['plan_sha256'],'current_mixer':{'submission':cur[0]['submission'] if cur else None,'source_available':cur[0]['source_available'] if cur else None,'current_over_public36':cur[0]['ratio'] if cur else None,'plan_factor':plan['champion']['current_champion_over_calibration'],'publication_hash':boards['publication_hash']},'sources':source_results,'profile':{'path':plan['profile_adapter'],'sha256':profile_hash,'mapping':profile_mod.KERNELS,'checks':profile_checks},'frozen_files':frozen,'checks':checks,'checks_passed':all(checks.values()),'budget_note':'driver_seconds 1800 includes reference build, a 240-second profile, one NativeOnly cost-first candidate, and two full gates each with a 600-second cap. If earlier stages consume the budget, a later gate may be clipped; classify any exhaustion as INCOMPLETE, not a source counterexample.','classification':'All source hashes/size and proof flags are bound; NativeOnly cost probe has no correct proof; two other candidates require fresh original all12 gates; quick measurements are exploration only.'}
(round/'verification/audit-ci3-plan-sources.json').write_text(json.dumps(out,indent=2)+'\n',encoding='utf-8');print(json.dumps({'checks_passed':out['checks_passed'],'plan_sha256':planhash,'source_results':source_results,'checks':checks},indent=2))
