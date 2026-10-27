"""Replace obsolete checkpoint fields with a compact current R index, atomically."""
from pathlib import Path
from datetime import datetime,timezone
import json
h=Path(__file__).resolve().parent
p=h/'astra-status.json'
old=json.loads(p.read_text(encoding='utf-8'))
assert old['candidate']=='f01-r11-wide4-inline-proof3'
keep=['actual_start_utc','status_written_at_utc','window_start_utc','deadline_utc',
      'status_target_utc','status_checkpoint_delay_seconds','status_delay_reason',
      'runtime_freeze_target_utc','confirmation_dispatch_target_utc','goal','goal_achieved',
      'ownership','coordinator','prohibited','continue_to_window_end','parents',
      'candidate','candidate_sha256','candidate_bytes','source_freeze_utc','source_frozen',
      'ready_for_D','active_matrix_candidate','actual_wide','static_checks','next',
      'handoff_receipt','web_handoff_verification','codegen_request','complete_cost_notes']
s={k:old[k] for k in keep if k in old}
s.update(state='WIDE4_PROOF3_28b819_FROZEN_PREPARED_STATEMENT928',
    updated_at_utc=datetime.now(timezone.utc).isoformat(),next_checkpoint_utc='2026-10-24T00:25:00Z',
    proof_ledger='astra-proof-ledger.json',source_budget='253315 B;2685 B remain. Only within_row changed from43aa.',
    proof_status='NOT_RUN_CURRENT28b819',full_gate='NOT_RUN_CURRENT28b819',performance='UNKNOWN_CURRENT_WIDE',
    promotion_allowed=False,formal_submission='NOT_SUBMITTED',active_ci_owned_by_R=[],
    active_web_jobs=[],child_agents_created_by_R=0,
    mechanism='One global nativeA and originalF10B,4rowx10column40orderedMACs,one currentblockF40cache,directlane40,rowmajoroutput,oldtail,rawNaNreplay. Underflow first; wideguard m>=4,n>4,p>2,n/rawAsize<USize.',
    prerequisites={
        'projection923':'EXACTafd8 plusprobe e73c statementPASS; rawverdictb5c7c0e021d549efca6c67dcc0c537d35efd35084b8a5811eafa7121e3d64990',
        'backbone923':'749bc933/223584B statementPASS; combinedfull stillnotrun',
        'writer925':'ea102356 genericwriterproof2 statementPASS; rawverdict642acaf39643017549a1e6e6da12515fc835ca30f60786e83c2c666b7aa80d39',
        'machine921':'Exacteb9 probeGO:10accSIMD,13XMMnames incltransientgather,hot0x200–0x2df nocall/rsp/alloc; unusedmatrixpath, notspeed/algorithmacceptance'},
    current_failure_repair={'seed':926,'run':40042639860,'failed_source':'43aaf31f905b71a976501f8cef170c9425d28c904b73079acc6e3f16a47dd8a5',
        'verdict_sha256':'1dcd85ac2d0f33c3ddf9021b2c6cb1c7cebf2fd5b30847e96879e188db0ccc8d',
        'error':'within_row simp expandsprojectRow beforewholewordLoop_row match',
        'repair':'28b819 explicittypedhproj andwholeequalityrewritebeforeFin4cases; runtimeallunchanged; originalsretained'},
    ci_dependencies=[{'owner':'D','seed':928,'source':'28b819120cd3aaa1f19038f66042a9ceffe0c9329baab20fe223e98d151ce00b','mode':'statement-only','state':'PREPARED_PER_LOCAL_PLAN'}],
    finite_model={'file':'../f01-r11-wide4-actual/model-check.json','matrices':1280,'outputs':63270,'valid_nan_replays':16919,'padding_nan_lanes_not_emitted':8093,'status':'PASS_SAME_ALGORITHM_TRANSCRIPTION_ONLY','Lean_hardware_timing_or_independent_oracle':False},
    old_cross={'source':'5c5e7071','full914':'PASS','relative_discovery_vs_a066_whole':0.9775279143,'relative_discovery_vs_a066_bmm':0.9177310746,'codegen':'astra-cross-codegen-914.md/json','promotion':'NONE'},
    old_short={'source':'7cad7df4','full916':'PASS','clean918_incremental_BMM_vsCross':0.9990,'decision':'NO_ESTABLISHED_INCREMENTAL_GAIN','promotion':'NONE'},
    web_delivery={'index':'astra-web-deliveries.json','folder':'E:/Download/FloatLib/20261024-R11','entry':'E:/Download/FloatLib/20261024-R11/README.md','payload_files':97,'archives':3,'fresh100item_verification':'astra-web-handoff-verification.json','all_jobs':'COMPLETE','browser':'CodexIABonly','private_materials':'LOCAL_ONLY'},
    user_research_upload_authorization='Explicitcurrenthuman: allowedresearchsourceuploads; do not askagain for samepurpose. No wallets/secrets.',
    actual_handoff='User-authorized artifacthandoff sentto developmentthread01a15ce7-bf54-74b2-8a2b-4a1e2f3828d7; ordinarycoordination remainsfilebased.',
    parked_assets=['astra-sparse-math.md:36576finitewordcases,lowold852exposure,nonewKernel','astra-native-word-finish.md:wordABIalreadyuint32/selfroutebelongsSol','astra-wide-a4-bridge-design.md:conditionalwholepathnotesonly; RootexplicitlynoA4actualswitchnow'],
    last_D_feedback='925writerPASS;92643aawithin_rowFAIL; repaironlyproof andfollowmain43aaoriginalfull/C,00:46:25runtimefreeze. Panel4separateprobeownedD.',
    resource_operations_by_R='NoGit,CI,reset,formalcontest,wallet,automation,Goal,subagent,newthread.')
tmp=h/'astra-status.new.json';tmp.write_text(json.dumps(s,ensure_ascii=False,indent=2)+'\n',encoding='utf-8');tmp.replace(p)
print(json.dumps({'state':s['state'],'current':s['candidate'],'sha256':s['candidate_sha256'],'status_bytes':p.stat().st_size}))
