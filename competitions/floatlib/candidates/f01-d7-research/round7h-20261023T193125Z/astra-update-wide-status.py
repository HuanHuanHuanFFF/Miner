from pathlib import Path
from datetime import datetime,timezone
import json,hashlib
h=Path(__file__).resolve().parent
p=h/'astra-status.json'
s=json.loads(p.read_text(encoding='utf-8'))
now=datetime.now(timezone.utc).isoformat()
m=json.loads((h.parent.parent/'f01-r11-wide4-inline/manifest.json').read_text(encoding='utf-8'))
s.update(state='WIDE4_ACTUAL_INITIAL_FROZEN_READY_FOR_STATEMENT',updated_at_utc=now,
    next_checkpoint_utc='2026-10-24T00:00:00Z',candidate=m['candidate'],
    candidate_sha256=m['candidate_sha256'],candidate_bytes=m['candidate_bytes'],
    source_freeze_utc=m['created_at_utc'],source_frozen=True,
    ready_for_D='USE 43aaf31f/252421B f01-r11-wide4-inline for next statement. READY NOW complete actual entry. ALL THREE924 Nat.succ_mul fixes ALREADY INCLUDED since initialb554 generator, currentlines6158/6161/6295. Fiveinlineattrs overaa837346. Original sources retained, inverse/staticPASS. 923 projectionPASS. Default build.py readonlyPASS. New full/perf NOT_RUN.',
    active_route='Real 4row x existingF10B; one globalA/B prep, perblockF40 cache, direct lane40 output, original NaNfinish/tail; n/USize guards before prep.',
    new_Lean_fullgate_performance='NOT_RUN_NEW_ACTUAL_43aaf31f; probe921 originalactiveentryPASS is not new algorithm acceptance.',
    next='D statement of 43aaf31f actual-inline. 924 originalwriter twofailures already repaired in thiscandidate beforedispatch; exact projection923PASS. Audit concrete caller/fullperformance afteracceptance.',
    source_budget='749b223584B base + actual wide path =252421B, remaining3579B; full inverse and underflow suffix identity.',
    web_research='W01,W02,W03 completed; 97 payload/extracted files and archive hashes verified in E:/Download/FloatLib/20261024-R11. IAB only for browser work.',
    formal_progress='5c5e full914PASS;7cad full916/918PASS; short incremental918 BMM .9990 no gain. Wide b554 new algorithm NOT_RUN.',
    checkpoint_note='23:51 actual43aaf31f frozen ready, singlecurrentcandidate. Fiveallowedinlineattrs targethigherorderchain, callbackeliminationUNKNOWN. Initialb554/aa837 retained, no observedCI failures. Existingprobe/projection unchanged.',
    last_D_feedback='924 originalwriter failedtwo Nat.succ-vs-add rewrite sites, thirdhs anticipated. Ractual43aa alreadyhasallthreefixes. 923 projection and749b backbonePASS;921GO.',
    feedback_read_at_utc=now)
s['codegen_probe'].update(full_gate_921='PASS_ORIGINAL_ACTIVE_ENTRY_ONLY',actual_codegen='GO: 10acc vectors; MAC12XMM, A assembly temporaryxmm2 yields13names total. Hot0x200–0x2df no call/rsp/heapalloc. D/Luna exact capture audit.',promotion_allowed=False)
s['projection_asset']={'path':'astra-wide4-projection.lean','sha256':'afd8d0bf8598f2f7eb612d2b53f8c318a8f4eb0b6eec41502c135db060774291','bytes':3649,'state':'STATEMENT_PASS923_EXACT_e73c','verdict_sha256':'b5c7c0e021d549efca6c67dcc0c537d35efd35084b8a5811eafa7121e3d64990','full_gate_new_algorithm':False}
s['actual_wide']=m
s['active_matrix_candidate']={'candidate':m['candidate'],'sha256':m['candidate_sha256'],'statement':'NOT_RUN','full_gate':'NOT_RUN','performance':'UNKNOWN'}
s['latest_actual_result']={'seed':921,'run':40039524733,'candidate':'f01-r11-wide4-codegen-probe','full_gate':'PASS_ORIGINAL_ENTRY_ONLY','new_algorithm_acceptance':'NOT_APPLICABLE_UNUSED','decision':'GO_REAL_ENTRY_EXPERIMENT'}
s['ci_dependencies']=[{'owner':'D','seed':923,'run':40040850289,'mode':'statement-only','scope':'afd8projection and749bbackbone','result':'PASS_BOTH_RAW_VERDICTS_REHASHED'}, {'owner':'D','seed':924,'run':40041351847,'mode':'statement-only','scope':'20a42e29 base+probe+projection+original42awriter, originalentry','result':'FAIL_TWO_REWRITE_SITES_ALREADY_FIXED_IN43aa','verdict_sha256':'f13544f6b370561c0a350e3fd1ad169e74ac043e837df569b709ddba2992df25'}]
s['finite_word_wiring_model']={'status':'PASS_FINITE_MODEL_ONLY','candidate':m['candidate'],'file':'../f01-r11-wide4-actual/model-check.json','matrices':1280,'outputs':63270,'valid_nan_replays':16919,'padding_nan_lanes_not_emitted':8093,'independent_oracle':False,'Lean_or_hardware':False}
s.pop('ci_dependency',None)
p.write_text(json.dumps(s,ensure_ascii=False,indent=2)+'\n',encoding='utf-8')
receipt={'at_utc':now,'candidate':m['candidate'],'sha256':m['candidate_sha256'],'bytes':m['candidate_bytes'],'state':'FROZEN_READY_FOR_STATEMENT','status_file':'astra-status.json','proof_status':'NOT_RUN'}
(h/'astra-wide-actual-ready.json').write_text(json.dumps(receipt,ensure_ascii=False,indent=2)+'\n',encoding='utf-8')
print(json.dumps(receipt))
