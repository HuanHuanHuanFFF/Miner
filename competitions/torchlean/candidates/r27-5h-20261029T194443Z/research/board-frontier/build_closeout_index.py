"""C owned-scope technical delivery manifest; never includes private source/chat bytes."""

from pathlib import Path

from datetime import datetime,timezone

import hashlib,json

HERE=Path(__file__).resolve().parent

PUBLIC_OUTPUT='PUBLIC-TECHNICAL-MANIFEST.json'

PRIVATE_OUTPUT=HERE/'private/LOCAL-ONLY-RESTORE-INDEX.json'

def sha(p):return hashlib.sha256(p.read_bytes()).hexdigest()

def jread(name):return json.loads((HERE/name).read_bytes())

def earliest(names):

 stamps=[]

 for n in names:

  d=jread(n)

  for k in ['start_utc','started_utc','created_utc','created_at_utc','at_utc','created_at']:

   x=d.get(k)

   if isinstance(x,str)and x.startswith('2026-'):

    try:stamps.append(datetime.fromisoformat(x.replace('Z','+00:00')))

    except ValueError:pass

 return min(stamps).isoformat()if stamps else'UNKNOWN'

def main():

 now=datetime.now(timezone.utc).isoformat();g=jread('guard26-v2-verified-result.json');m=jread('gemm9-verified-result.json')

 routes=[

  ('guard26','Exactnormalizationguardcoverage',['norm-guard26-receipt.json','norm-guard26-v2-receipt.json','guard26-v2-verified-result.json'],'Actualall12PASS; reliable1.24percentinternalquickgain, insufficientvsfinaltarget43'),

  ('packed_output','Balancedmultioutputpacking',['packed-model-result.json','packed-caller-result.json','packed12-native-v1-receipt.json'],'Finiteword/integerchecks; nativecost/actualcorrectUNKNOWN, heldnotqueued'),

  ('paired_products','Sharedrow/columnpairedproductswithnative192terminal',['winograd-discriminator-result.json','winograd-word-result.json','winograd12-nativefinish-v2-receipt.json'],'Finiteidentity/signcounterexample; nativecost/actualcorrectUNKNOWN, held'),

  ('proof_space','Existingaliasproofcompaction',['public23-proof-alias-compact-receipt.json','gemm9-verified-result.json'],'4454Bfreed; runtimeunchanged; componentusedwithinall12-accepted6fe5, notstandalonegateclaim'),

  ('rms_terminal','Existingnativequotient-roundterminalatRMS',['public23-rms-native-finish-receipt.json','public23-rms-native-cost-receipt.json','rms-native-finish-check.json'],'Realcallerconnection/finitecoverage; noLean/native; unselected'),

  ('gemm_composition','ExactGEMMinterfacearound23preparedlinear',['gemm27-public23-receipt.json','gemm27-public23-all-positive-receipt.json','gemm9-verified-result.json'],'Actualall12PASS, independentstandardPERFORMANCEFAIL; noadoption'),

  ('native_add_premise','Closednativeaddproofreuse/bytebudgetforD17',['MIXER-ADD-PREMISE.json','MIXER-ADD-SPACE-CUTS.json'],'Downsimplementation/current10acceptance; C staticpremiseonly'),

  ('pro_norm_review','Exactbiasednumeratorandstrictnormalcellcriticalreview',['PRO-NORM-INTAKE-REVIEW.json','pro-norm-intake-independent-model.json'],'Noactualintegrationerrorfound; formalwordbridgeOPEN; CIheldafterprofile'),

  ('followon_inventory','Final12bindingsandproof-space/counterexamples',['follow-on/operator-binding-matrix.json','follow-on/crossboard/norm-fallback-census.json','BAND64-ENDPOINT-PREMISE.json'],'Boundedstatic/finiteevidence, noalgorithmgain ornewproofclaim')]

 ledger=[]

 for rid,mechanism,files,state in routes:

  ledger.append({'id':rid,'mechanism':mechanism,'first_available_artifact_timestamp':earliest(files),'actual_route_effort_seconds':'UNKNOWN_OVERLAPPING_NOT_METERED','tokens':'UNKNOWN','cached_input_tokens':'UNKNOWN','CI_occupancy_C':0,'result':state,'evidence':[{'path':f,'sha256':sha(HERE/f)}for f in files]})

 out={'at_utc':now,'state':'CLOSING_ACTIVE_UNTIL_ORIGINAL_DEADLINE','actual_start_utc':'2026-10-29T19:48:32Z','common_start_utc':'2026-10-29T19:44:43Z','deadline_utc':'2026-10-30T00:44:43Z','objective':'AnycurrentTorchLeanboardchampion, championonlycomparison','objective_achieved':False,'proof_and_performance_separate':True,'proven_sources':[{'sha256':'dced7848655a50a136750c1837b46f084a25ec26d13df72fe907d4a162bf1cb9','bytes':218583,'run':40952423982,'gate':'PASS actualall12','performance':'quicknotchampion','receipt':'guard26-v2-verified-result.json'},{'sha256':m['candidate_sha256'],'bytes':m['candidate_bytes'],'run':m['run'],'gate':'PASS actualall12','performance':'standardguard-fail','receipt':'gemm9-verified-result.json'}],'routes':ledger,'allocation_changes':['Released12/27 madeactualstrongpredecessorinterfacesbetterstartingpoints; oldR26 fourkernel/fullmodel claimsnotinherited','guard26provedsmallgainpreservedbutcapretuningstoppedafteractualcost','Newcurrent43/public23native128bothnorms retiredweaker12+27graft; proofspacecompactionenabledactualintegration','GEMMstructuredproofreuse selectedbefore9freshcohort; allpositivek repairbasedfixedoperatorcoverage, not9data','Standard9negativeclosed; noadoption, no inferredcomponentbenefits. D17nextsourceindependentpre9; newcohortneeded','Profilelayer3.55-6.23percentofthreeentries pausedProNormCI/largeproof; notafullmodelhardbound'],'resources':{'actual_tokens':'UNKNOWN','cached_input_tokens':'UNKNOWN','model_CPU_seconds':'UNKNOWN','local_native_Lean_builds':0,'C_CI_dispatches':0,'C_Git_mutations':0,'C_direct_messages_after_initial_dispatch':0,'C_nested_agents':0,'public_manual_CI_owner':'Droot','D_gate_seconds_for_guard26':'Seeoriginalreceipt','D_gate_seconds_for_gemm9':m['gate_seconds'],'per_route_token_sums':'UNKNOWN; no reasoning/output doublecount invented'},'budget_audit':'BUDGET-ORIGINAL-HUMAN-AUDIT.json; parentretractedhistorical3h30misintake, no extension','pending_owner_result':'D closing10 f605/40977309820; sourceoutcomenotclaimedhereuntilterminal','publication':'Onlyownedtechnicalcode/proofs/models/receipts; privatewholeupstreamKernel/generatedcode/chatoriginalsexcluded','local_restore_index':'private/LOCAL-ONLY-RESTORE-INDEX.json'}

 deadline=datetime.fromisoformat('2026-10-30T00:44:43+00:00')
 if datetime.now(timezone.utc)>=deadline:
  out['state']='ORIGINAL_RESEARCH_WINDOW_CLOSED_NO_CHAMPION'
  out['research_cutoff_utc']='2026-10-30T00:44:43Z'
  out['final_delivery_timestamp_utc']=now
  out['delivery_after_cutoff_seconds']=int((datetime.fromisoformat(now)-deadline).total_seconds())
  out['C_in_window_wall_seconds']=17771
  out['C_actual_wall_through_delivery_seconds']=int((datetime.fromisoformat(now)-datetime.fromisoformat('2026-10-29T19:48:32+00:00')).total_seconds())
  out['common_window_seconds']=18000
  out['late_join_seconds']=229
  out['new_research_stopped_at_original_cutoff']=True
 downstream=HERE/'native-add10-owner-result.json'
 if downstream.exists():
  out['downstream_native_add']=json.loads(downstream.read_bytes())
  out['pending_owner_result']='D closing12 Band11two-literaltype-retest; algorithmunchanged, actualnewcorrectabsent; no resultclaimuntilterminal'
  for route in out['routes']:
   if route['id']=='native_add_premise':route['result']='D exactf605all12PASS; standardcostinsufficient; scopeNativeAdd-only withsmallKrestoremissing'
 band=HERE/'band12-owner-result.json'
 if band.exists():
  out['downstream_band12']=json.loads(band.read_bytes())
  out['pending_owner_result']='NONE: Dreportsall12CIruns terminal/collected; finalGit/rootchecks remainDowner'
 (HERE/'CLOSEOUT-INDEX.json').write_text(json.dumps(out,indent=2,ensure_ascii=False),encoding='utf8')

 pub=[];private=[];cache_count=0

 for f in sorted(HERE.rglob('*')):

  if not f.is_file():continue

  rel=f.relative_to(HERE);parts=set(rel.parts)

  if f.name in[PUBLIC_OUTPUT]or f==PRIVATE_OUTPUT:continue

  if '__pycache__'in parts or f.suffix=='.pyc':cache_count+=1;continue

  row={'path':rel.as_posix(),'bytes':f.stat().st_size,'sha256':sha(f)}

  if 'private'in parts or 'source-private'in parts:private.append(row)

  else:pub.append(row)

 # The onlyprivatehumanliteral knownfromthebudgetaudit mustnotappear inpublictechnicalbytes.

 forbidden=[]
 auth=HERE/'private/authorization/3h30-original-human-records.json'
 if auth.exists():
  for item in json.loads(auth.read_bytes()):
   payload=item['record'].get('payload',{})
   for content in payload.get('content',[]):
    if content.get('type')=='input_text':
     forbidden.extend(x for x in content.get('text','').splitlines()if x)
 for row in pub:

  f=HERE/row['path']

  if f.suffix in['.json','.md','.py','.lean','.inc']:

   txt=f.read_text(encoding='utf8')

   assert not any(s in txt for s in forbidden),(row['path'],'private historical request literal')

 PRIVATE_OUTPUT.parent.mkdir(parents=True,exist_ok=True)

 PRIVATE_OUTPUT.write_text(json.dumps({'at_utc':now,'state':'LOCAL_ONLY_NOT_FOR_PUBLIC_MANIFEST','files':private,'note':'Preservewholethirdpartyreconstructionsandhumanrawrecords locally; sourcepins/ownedrecipesprovideindependentrestore'},indent=2),encoding='utf8')

 manifest={'at_utc':now,'scope':'OnlythisCownedfolderpublictechnicalsnapshot','files':pub,'file_count':len(pub),'total_bytes':sum(x['bytes']for x in pub),'excluded_private_count':len(private),'excluded_cache_count':cache_count,'private_restore_index':'private/LOCAL-ONLY-RESTORE-INDEX.json','manifest_self_excluded':True,'not_a_Git_publication':'Drootstageonlyexactmatchinghashes; mutableindexesmayrefreshatfinalcutoff','builder_sha256':sha(Path(__file__))}

 (HERE/PUBLIC_OUTPUT).write_text(json.dumps(manifest,indent=2),encoding='utf8')

 print(json.dumps({'public_files':len(pub),'public_bytes':manifest['total_bytes'],'private_files_excluded':len(private),'cache_files_excluded':cache_count,'manifest_sha256':sha(HERE/PUBLIC_OUTPUT),'state':out['state']}))

if __name__=='__main__':main()

