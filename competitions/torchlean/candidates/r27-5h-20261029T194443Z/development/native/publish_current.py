"""Publish this role's file-only checkpoint, without touching another scope."""
from pathlib import Path
from datetime import datetime, timezone
import hashlib,json
HERE=Path(__file__).resolve().parent
now=datetime.now(timezone.utc).isoformat()
def write(name, value):
    (HERE/name).write_text(json.dumps(value,indent=2)+'\n',encoding='utf-8')
def digest(name):return hashlib.sha256((HERE/name).read_bytes()).hexdigest()
candidate={'name':'public23-row-reciprocal-v2','sha256':'9654b727badce93d0727ece982a0ccedce99107ce98235b18e0e5cdc79e8944e','bytes':253499,'free_bytes':2501,'intake_policy':'PASS','state':'ACTUAL_ALL12_DECLARED_NOT_COMPILED'}
helper={'path':'ReciprocalUInt64ContractOnly-v4.lean','sha256':'013a5fd2e87c4da32bf791529564b587d67f8a94d096fe9f058826f2a8873dda','bytes':12500,'state':'BATCH4_ACTUAL_REPAIR_NOT_COMPILED'}
write('CI-REQUEST-13-PUBLIC23-RECIPROCAL.json',{
 'at_utc':now,'request':candidate['name'],'priority':'Primary norm mechanism after actual batch4 proof repair; original all12 gate required',
 'ci_owner':'Droot only','official_commit':'27fb1d19c712ead50ad34b4ad0d4ba597161e616',
 'source':'competition-state/source-private/submission23-Kernel.lean','source_sha256':'1010c0744f0506974c64601e8ce7335bea56d0cb21b655543d390794df0665fe',
 'recipe':'development/native/public23_reciprocal_v3.py','recipe_sha256':digest('public23_reciprocal_v3.py'),
 'interface':"transform(data:bytes, submission=23, variant='row-reciprocal23-v3')->bytes",'candidate':candidate,
 'runtime_changes':'Cache one reciprocal per norm row; replace three UInt64 q/r pairs with multiply-high and one correction; final rounding/fallback retained',
 'proof_changes':'Reuse m64/m64_v; B explicit Nat cancellation replaces failed nlinarith paths; normalize word estimate; update actual Ya7Ge/Zdt',
 'all12_correct':'Original entry preserved and connected to actual changed functions, but NOT_COMPILED; no accepted gate claim',
 'stage':'Source compile/full original all12 gate, then whole normalized_mlp paired screen only if gate passes',
 'dependencies':[
 {'path':'development/native/public23_reciprocal.py','sha256':digest('public23_reciprocal.py')},
 {'path':'development/native/ReciprocalUInt64ContractOnly-v4.lean','sha256':helper['sha256']},
 {'path':'development/native/frozen_compact_public23.py','sha256':'4c3dd79284f6701d3b128687f9f973f47d9236f8d9db502d398e2eb4d131e129'}],
 'helper_only_optional':helper,'old_v3_result':'Helper elaboration failed; printed sorryAx is not accepted',
 'current_target':{'board':'normalized_mlp','champion':43,'current43_over_public23_time':.9072362322024092,'scope':'Cross-environment exact report chain only; direct source43 UNKNOWN'},
 'supersedes':'Old source12+27 native-stat graft; no further old graft queue',
 'publication':'Own recipes/helpers/receipts only; reconstructed whole source private/ephemeral, never public artifacts'})
write('READY.json',{'updated_at_utc':now,'deadline_utc':'2026-10-30T00:44:43Z','role':'Dnative','communication':'STRICT_FILES_ONLY',
 'ci_owner':'Droot','preferred':'CI-REQUEST-13-PUBLIC23-RECIPROCAL.json','candidate':candidate,'helper':helper,
 'current_normalized_mlp_champion':43,'43_over_public23_time':.9072362322024092,
 'stopped':'Old public12+27 native layer graft dominated by public23 native both norms',
 'batch4':'Reciprocal v3 failed helper elaboration; original logs retained; new v4 not compiled',
 'publication':'Own recipes/helpers/receipts only; whole source private/ephemeral',
 'tokens_actual':'UNKNOWN','cached_input_tokens':'UNKNOWN','model_cpu':'UNKNOWN'})
write('status.json',{'updated_at_utc':now,'first_clock_utc':'2026-10-29T19:46:53Z','deadline_utc':'2026-10-30T00:44:43Z',
 'active':True,'role':'Dnative','state':'PUBLIC23_COMPACT_RECIPROCAL_EXACT_RECIPE_READY_FOR_GATE',
 'request':'CI-REQUEST-13-PUBLIC23-RECIPROCAL.json','candidate':candidate,
 'next':'Inspect actual new bridge and cost assumptions while D owns queue; no source43 or champion claim',
 'communication':'STRICT_FILES_ONLY','writes':'development/native only','resources':'Actual tokens/cache/modelCPU UNKNOWN'})
handoff='''# R27 native current handoff

Updated {now}. Join19:46:53, cutoff00:44:43 unchanged; stop new long work00:00. Droot only Git/CI, native-only writes, strict files. No local Lean/native, formal submission/funds/reset; tokens/cache/CPU UNKNOWN.

- **Primary exact recipe fits:** `CI-REQUEST-13-PUBLIC23-RECIPROCAL.json`, `public23_reciprocal_v3.py`. Source23 `1010c074…` → **253499B/9654b727…8944e**, 2501B free, original intake/policy PASS. v3 freezes the cross-role compactor in this scope; exact candidate unchanged. Reuses public23 `m64/m64_v`, caches reciprocal per row, replaces3 q/r pairs in Ya7G, preserves final round/fallback. Actual Ya7Ge/Zdt and all12 correct connected but **NOT_COMPILED**, no accepted correctness claim.
- **Space solved jointly:** C proof-only existing-alias transform saves4454B without deleting declarations or changing original runtime declaration bytes. New helper4978B. Old v1 257392B/71dad662 overcap1392 remains negative receipt. New source needs real full gate for alias resolution/proof.
- **Actual batch4 failure used:** run40964374666 reciprocal v3 failed Nat nonlinear automation/no-progress plus numeric normalization; printed sorryAx is failure. `ReciprocalUInt64ContractOnly-v4.lean` **12500B/013a5fd2…73dda** uses B explicit Nat cancellation, original primitive runtime unchanged, repairs diagnosed word proof lines. Fresh compilation still UNKNOWN. B modular v3 separately accepted, no inheritance here.
- **Current target43:** latest normalizedMLP champion43/public23=.9072362322. Proven guard26-v2 quick chain versus43~1.1368, insufficient. Public23 already native128 in both RMS and layer: **stop old12+27 graft** and old prep-only primary work. No new original-shipped performance comparison.
- **Historical receipts retained:** batch3ZIP `evidence-40952423982/receipts.zip` SHA45565509…cb026, original guard26 full12 PASS. Own prep3/39f377f9 and smallbatch rawcols/8f86645e remain uncompiled/unselected. Fetch403 is transport UNKNOWN; no bypass. Prior raw failures retained.

NextD: compile exact253499B candidate on current official27fb, complete original all12 gate, collect exact goals. If gate passes, use complete model paired screen and current champion report chain, then fresh frozen confirmation. Further research uses prefreeze inputs only. Whole unknown-license source private/ephemeral; own recipes/helper proof/receipts publish.
'''
(HERE/'HANDOFF.md').write_text(handoff.format(now=now),encoding='utf-8')
print(json.dumps({'updated_at_utc':now,'request':'CI-REQUEST-13-PUBLIC23-RECIPROCAL.json','candidate':candidate,'recipe_sha256':digest('public23_reciprocal_v3.py')}))
