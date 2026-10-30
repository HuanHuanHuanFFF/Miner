from pathlib import Path
import hashlib,json,datetime
root=Path.cwd(); round=root/'competitions/torchlean/candidates/r28-3h-20261030T171558Z'; snap=round/'competition-state/refresh-20261030T181518Z'; receipt=json.loads((snap/'receipt.json').read_bytes()); boards_raw=(snap/'boards.raw').read_bytes(); boards=json.loads(boards_raw); board_hash=hashlib.sha256(boards_raw).hexdigest()
allchecks={'boards_receipt_hash':board_hash==next(x['sha256'] for x in receipt['receipts'] if x['url'].endswith('/boards')),'all_champion_responses_bound':True,'one_current_per_board':True,'board_current_promotions_match':True}
rows=[]
for board in ('overall','mlp','mixer','resnet','mobilenet','normalized_mlp'):
    path=snap/f'champions-{board}.raw'; raw=path.read_bytes(); body=json.loads(raw)
    rec=next(x for x in receipt['receipts'] if x['url'].endswith(f'/champions?board={board}'))
    bdef=next(x for x in boards['boards'] if x['id']==board)
    current=[x for x in body['champions'] if x.get('current') is True]
    matches=hashlib.sha256(raw).hexdigest()==rec['sha256'] and len(raw)==rec['bytes'] and rec['status']==200
    pub=body.get('publication_hash')==boards['publication_hash']
    one=len(current)==1
    promo=one and bdef['current_promotion_id']==current[0]['promotion_id']
    allchecks['all_champion_responses_bound']=allchecks['all_champion_responses_bound'] and matches and pub
    allchecks['one_current_per_board']=allchecks['one_current_per_board'] and one
    allchecks['board_current_promotions_match']=allchecks['board_current_promotions_match'] and promo
    c=current[0] if one else {}
    rows.append({'board':board,'response_sha256':hashlib.sha256(raw).hexdigest(),'receipt_status':rec['status'],'receipt_hash_match':matches,'publication_match':pub,'current_rows':len(current),'current_promotion_matches_board':promo,'submission':c.get('submission'),'promotion_id':c.get('promotion_id'),'source_sha256':c.get('source_sha256'),'source_available':c.get('source_available'),'ratio':c.get('ratio'),'promoted_at':c.get('promoted_at')})
res=next(x for x in rows if x['board']=='resnet'); rbody=json.loads((snap/'champions-resnet.raw').read_bytes()); chain=rbody['champions']; idx=next(i for i,x in enumerate(chain) if x.get('current') is True); anchor_id=11; anchoridx=next(i for i,x in enumerate(chain) if x['submission']==anchor_id); edges=chain[idx:anchoridx]; product=1.0
for x in edges: product*=float(x['ratio'])
plan=json.loads((round/'development/ci-bridge/batch-resnet-draft/plan-draft.json').read_bytes()); plan_hash=hashlib.sha256((round/'development/ci-bridge/batch-resnet-draft/plan-draft.json').read_bytes()).hexdigest()
planbind=plan['champion']['submission']==res['submission'] and plan['champion']['source_sha256']==res['source_sha256'] and plan['champion']['current_champion_over_calibration']==product and plan['champion']['publication_hash']==boards['publication_hash'] and plan['champion']['champion_response_sha256']==res['response_sha256'] and plan['champion']['boards_response_sha256']==board_hash and plan['reference']['sha256']==next(x['source_sha256'] for x in chain if x['submission']==anchor_id)
bar_reduction=1-0.97*product
current_mobile=next(x for x in rows if x['board']=='mobilenet')
mobile_plan=json.loads((round/'ci-plan.json').read_bytes()); mobile_plan_identity_still_current=(mobile_plan['champion']['submission']==current_mobile['submission'] and mobile_plan['champion']['source_sha256']==current_mobile['source_sha256'] and mobile_plan['champion']['current_champion_over_calibration']==current_mobile['ratio'])
allchecks['resnet_plan_rebound']=planbind
allchecks['mobile_dispatch_target_identity_unchanged']=mobile_plan_identity_still_current
out={'round':'R28','scope':'READ_ONLY_LIVE_CHAMPION_REFRESH_AND_RESNET_PLAN_REBIND','captured_at_utc':datetime.datetime.now(datetime.timezone.utc).isoformat(),'snapshot':{'path':'competition-state/refresh-20261030T181518Z','received_at_utc':receipt['at_utc'],'publication_hash':boards['publication_hash'],'boards_sha256':board_hash,'champion_response_count':len(rows)},'current_boards':rows,'resnet_to_public11_chain':[{'submission':x['submission'],'promotion_id':x['promotion_id'],'ratio':float(x['ratio']),'source_available':x['source_available']} for x in edges]+[{'submission':anchor_id,'anchor':True,'source_available':next(x for x in chain if x['submission']==anchor_id)['source_available']}],'resnet_current_over_public11':product,'public11_over_current64':1.0/product,'additional_reduction_from_public11_to_0_97_current64':bar_reduction,'resnet_draft':{'plan_sha256':plan_hash,'candidate_sha256s':[x['sha256'] for x in plan['candidates']],'current_champion':plan['champion']['submission'],'response_binding_matches':planbind,'classification':plan['champion']['comparison']},'mobile_ci2_target':{'current_submission':current_mobile['submission'],'same_current_id_source_and_ratio_as_dispatched_plan':mobile_plan_identity_still_current,'new_publication_hash':boards['publication_hash'],'old_dispatched_publication_hash':mobile_plan['champion']['publication_hash'],'classification':'The Mobile #57 identity/source/ratio is unchanged; run remains bound to its pre-dispatch snapshot.'},'checks':allchecks,'checks_passed':all(allchecks.values()),'source_policy':'Only official board/champion response bytes and source hash metadata read; no current champion source body fetched or emitted.'}
(round/'verification/audit-champions-181518.json').write_text(json.dumps(out,indent=2)+'\n',encoding='utf-8'); print(json.dumps({'checks_passed':out['checks_passed'],'publication_hash':boards['publication_hash'],'resnet_current':res['submission'],'resnet_current_over_public11':product,'public11_over_current64':1/product,'additional_reduction_to_0_97':bar_reduction,'mobile_target_still_current':mobile_plan_identity_still_current,'resnet_plan_rebound':planbind},indent=2))
