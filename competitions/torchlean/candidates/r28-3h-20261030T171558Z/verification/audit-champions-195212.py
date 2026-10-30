from pathlib import Path
import datetime,hashlib,json

root=Path.cwd();round_dir=root/'competitions/torchlean/candidates/r28-3h-20261030T171558Z'
folder=round_dir/'competition-state/refresh-20261030T195212Z'
receipt=json.loads((folder/'receipt.json').read_bytes());sha=lambda b:hashlib.sha256(b).hexdigest()
expected={'overall':59,'mlp':33,'mixer':56,'resnet':64,'mobilenet':57,'normalized_mlp':51}
names={'overall':'overall','mlp':'mlp','mixer':'mixer','resnet':'resnet','mobilenet':'mobilenet','normalized_mlp':'normalized_mlp'}
receipt_by={Path(x['path']).name:x for x in receipt['receipts'] if 'path' in x}
rows=[];checks={}
boards_raw=(folder/'boards.raw').read_bytes();boards=json.loads(boards_raw)
checks['boards_hash_and_status']=sha(boards_raw)==receipt_by['boards.raw']['sha256'] and len(boards_raw)==receipt_by['boards.raw']['bytes'] and receipt_by['boards.raw']['status']==200
checks['receipt_live_all_six']=receipt['state']=='LIVE_ALL_SIX_BEFORE_STANDARD_FREEZE'
checks['six_boards_share_one_publication']=len(boards['boards'])==6 and len({x['id'] for x in boards['boards']})==6 and bool(boards['publication_hash'])
for key,board in names.items():
 path=folder/f'champions-{board}.raw';raw=path.read_bytes();meta=receipt_by[path.name];data=json.loads(raw)
 currents=[x for x in data['champions'] if x.get('current') is True]
 current=currents[0] if len(currents)==1 else {}
 mobile_board=next((x for x in boards['boards'] if x['id']==board),{})
 checks[f'{key}_raw_hash_and_status']=sha(raw)==meta['sha256'] and len(raw)==meta['bytes'] and meta['status']==200
 checks[f'{key}_publication_and_one_current']=data['publication_hash']==boards['publication_hash'] and len(currents)==1
 checks[f'{key}_expected_current_id']=current.get('submission')==expected[key] and mobile_board.get('current_promotion_id')==current.get('promotion_id')
 rows.append({'board':key,'current_submission':current.get('submission'),'promotion_id':current.get('promotion_id'),'source_sha256':current.get('source_sha256'),'ratio':current.get('ratio'),'source_available':current.get('source_available'),'response_sha256':sha(raw),'raw_status':meta['status'],'publication_hash':data['publication_hash']})
plan=json.loads((round_dir/'ci-plan.json').read_bytes())
checks['ci6_mixer_plan_matches_live_snapshot']=plan['champion']['submission']==next(x for x in rows if x['board']=='mixer')['current_submission'] and plan['champion']['source_sha256']==next(x for x in rows if x['board']=='mixer')['source_sha256'] and plan['champion']['current_champion_over_calibration']==next(x for x in rows if x['board']=='mixer')['ratio'] and plan['champion']['champion_response_sha256']==next(x for x in rows if x['board']=='mixer')['response_sha256'] and plan['champion']['boards_response_sha256']==sha(boards_raw)
ci5_plan=json.loads((round_dir/'evidence/41117223550/download-e48d841d4921418d9efbbef8ac2542f6/plan.json').read_bytes())
mobile_row=next(x for x in rows if x['board']=='mobilenet')
checks['ci5_mobile_current57_ratio_unchanged_in_fresh_snapshot']=mobile_row['current_submission']==ci5_plan['champion']['submission']==57 and mobile_row['source_sha256']==ci5_plan['champion']['source_sha256'] and mobile_row['ratio']==ci5_plan['champion']['current_champion_over_calibration']
out={'round':'R28','scope':'READ_ONLY_FRESH_OFFICIAL_CHAMPION_SNAPSHOT_AUDIT','captured_at_utc':datetime.datetime.now(datetime.timezone.utc).isoformat(),'snapshot_at_utc':receipt['at_utc'],'publication_hash':boards['publication_hash'],'boards_sha256':sha(boards_raw),'champions':rows,'checks':checks,'checks_passed':all(checks.values()),'ci6_mixer_binding':{'candidate_board':'mixer','submission':plan['champion']['submission'],'ratio':plan['champion']['current_champion_over_calibration'],'matches_snapshot':checks['ci6_mixer_plan_matches_live_snapshot']},'ci5_mobile_score_context':{'plan_candidate':'17befe6a4afb7dac0dc19090970812b1890d147154932f610f015b6dd1b0d044','snapshot_current_mobilenet':next(x['current_submission'] for x in rows if x['board']=='mobilenet'),'ratio':next(x['ratio'] for x in rows if x['board']=='mobilenet'),'saved_plan_ratio':ci5_plan['champion']['current_champion_over_calibration'],'same_ratio':next(x['ratio'] for x in rows if x['board']=='mobilenet')==ci5_plan['champion']['current_champion_over_calibration']}}
(round_dir/'verification/audit-champions-195212.json').write_text(json.dumps(out,indent=2)+'\n',encoding='utf-8')
print(json.dumps({'checks_passed':out['checks_passed'],'failed_checks':[k for k,v in checks.items() if not v],'snapshot':out['snapshot_at_utc'],'publication':out['publication_hash'],'champions':[(x['board'],x['current_submission'],x['ratio'])for x in rows],'ci6_mixer_binding':out['ci6_mixer_binding'],'ci5_mobile_score_context':out['ci5_mobile_score_context']},indent=2))
