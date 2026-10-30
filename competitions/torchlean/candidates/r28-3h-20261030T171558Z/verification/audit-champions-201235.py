from pathlib import Path
import datetime,hashlib,json

round_dir=Path.cwd()/'competitions/torchlean/candidates/r28-3h-20261030T171558Z';snapshot=round_dir/'competition-state/refresh-20261030T201235Z'
receipt=json.loads((snapshot/'receipt.json').read_bytes());sha=lambda b:hashlib.sha256(b).hexdigest()
root=Path.cwd()
expected={'overall':59,'mlp':33,'mixer':56,'resnet':64,'mobilenet':57,'normalized_mlp':51}
names={'overall':'overall','mlp':'mlp','mixer':'mixer','resnet':'resnet','mobilenet':'mobilenet','normalized_mlp':'normalized_mlp'}
receipt_by={Path(x['path']).name:x for x in receipt['receipts'] if 'path' in x}
checks={};boards_raw=(snapshot/'boards.raw').read_bytes();boards=json.loads(boards_raw)
response_receipts=[x for x in receipt['receipts'] if Path(x.get('path','')).suffix=='.raw']
checks['all_seven_live_board_responses_200_and_hash_bound']=len(response_receipts)==7 and all(x['status']==200 and sha((root/Path(*x['path'].split('/'))).read_bytes())==x['sha256'] and (root/Path(*x['path'].split('/'))).stat().st_size==x['bytes'] for x in response_receipts)
checks['boards_has_six_current_board_rows']=len(boards['boards'])==6 and len({x['id'] for x in boards['boards']})==6 and len(boards_raw)==receipt_by['boards.raw']['bytes'] and sha(boards_raw)==receipt_by['boards.raw']['sha256']
checks['receipt_publication_matches_boards']=receipt['state'] in {'LIVE_ALL_SIX','LIVE_ALL_SIX_BEFORE_STANDARD_FREEZE','LIVE_FINAL_ALL_SIX'} and len(receipt['rows'])==6
rows=[]
for key,board in names.items():
 raw=(snapshot/f'champions-{board}.raw').read_bytes();data=json.loads(raw);meta=receipt_by[f'champions-{board}.raw'];currents=[x for x in data['champions'] if x.get('current') is True];current=currents[0] if len(currents)==1 else {};brow=next(x for x in boards['boards'] if x['id']==board)
 checks[f'{key}_response_and_current_row']=sha(raw)==meta['sha256'] and len(raw)==meta['bytes'] and meta['status']==200 and data['publication_hash']==boards['publication_hash'] and len(currents)==1 and current.get('submission')==expected[key] and brow.get('current_promotion_id')==current.get('promotion_id')
 rows.append({'board':key,'current_submission':current.get('submission'),'promotion_id':current.get('promotion_id'),'source_sha256':current.get('source_sha256'),'ratio':current.get('ratio'),'source_available':current.get('source_available'),'response_sha256':sha(raw)})
plan=json.loads((round_dir/'ci-plan.json').read_bytes())
mix=next(x for x in rows if x['board']=='mixer');checks['ci6_mixer_plan_still_matches_refresh']=plan['champion']['submission']==mix['current_submission'] and plan['champion']['source_sha256']==mix['source_sha256'] and plan['champion']['current_champion_over_calibration']==mix['ratio'] and plan['champion']['publication_hash']==boards['publication_hash'] and plan['champion']['champion_response_sha256']==mix['response_sha256'] and plan['champion']['boards_response_sha256']==sha(boards_raw)
out={'round':'R28','scope':'READ_ONLY_LIVE_CHAMPION_REFRESH_AUDIT','captured_at_utc':datetime.datetime.now(datetime.timezone.utc).isoformat(),'snapshot_at_utc':receipt['at_utc'],'publication_hash':boards['publication_hash'],'boards_sha256':sha(boards_raw),'champions':rows,'checks':checks,'checks_passed':all(checks.values()),'ci6_mixer_plan_match':checks['ci6_mixer_plan_still_matches_refresh'],'response_count':len(response_receipts)}
(round_dir/'verification/audit-champions-201235.json').write_text(json.dumps(out,indent=2)+'\n',encoding='utf-8')
print(json.dumps({'checks_passed':out['checks_passed'],'failed_checks':[k for k,v in checks.items() if not v],'snapshot':out['snapshot_at_utc'],'publication':out['publication_hash'],'champions':[(x['board'],x['current_submission'],x['ratio'])for x in rows],'ci6_mixer_plan_match':out['ci6_mixer_plan_match']},indent=2))
