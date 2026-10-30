from pathlib import Path
from datetime import datetime,timezone
import json,hashlib
HERE=Path(__file__).resolve().parent;now=datetime.now(timezone.utc).isoformat()
receipt=json.loads((HERE/'native-add-portfolio10-receipt.json').read_text())
deps=[]
for p in sorted((HERE/'portfolio10_components').glob('*')):
 deps.append({'path':'development/native/portfolio10_components/'+p.name,'sha256':hashlib.sha256(p.read_bytes()).hexdigest()})
deps.append({'path':'development/native/frozen_compact_public23.py','sha256':hashlib.sha256((HERE/'frozen_compact_public23.py').read_bytes()).hexdigest()})
request={'at_utc':now,'request':'mixer-native-add-portfolio10','reply_to':'MIXER-NATIVE-ADD-PORTFOLIO10.json',
 'recipe':'development/native/graft_native_add_portfolio10.py','recipe_sha256':hashlib.sha256((HERE/'graft_native_add_portfolio10.py').read_bytes()).hexdigest(),
 'interface':"transform(raw23,submission=23,variant='mixer-native-add-portfolio10',donor_raw=None)->bytes; exact donor from TORCHLEAN_ROOT/r27-source-private/official-27.lean or explicit donor_raw",
 'candidate_sha256':receipt['candidate_sha256'],'candidate_bytes':receipt['candidate_bytes'],'free_bytes':receipt['free_bytes'],
 'dependencies':deps,'source23_sha256':'1010c0744f0506974c64601e8ce7335bea56d0cb21b655543d390794df0665fe','donor27_sha256':'f92ee2c9a29de78dc434ad158b7141c0e4b5a67a5a198a353d59a4703481aa67',
 'state':'ACTUAL_ALL12_DECLARED_NOT_COMPILED','intake_policy':'PASS','actual_binding':receipt['actual_binding'],
 'changes':'Base frozen6fe5 + native64YaW/YaX/Ybf/W1; largegap fallback exactModel.add, directofFnYbf. RMS-exclusive12decls removed with0remainingrefs, RMSfield originalkernels0; MYbc/positiveGEMM retained',
 'space':'Newproofclosure7641B,9missingaliases opened late only; proofhorizontalpunctuation579B removed, application parentheses/indentation retained. All actualsource needs fullgate',
 'independence':'PRE9 source/premises only, no9materializedinput/nativeoutput read; not tuning onacceptance. Standalone pre9Cproof bridge proposal used',
 'validation':'Fresh original all12gate before measurement; freshstandard roots/newpublicrunner for thisnewsource. CurrentMixer36 only, include allfallback/transpose/prep/output. No summedgainclaim',
 'timeline':'NativeAdd first inspected23:40, firstcap-fit23:45, canonical two-process byte reproduction23:47. Target23:43 missed; no9scopechange or deadlineextension',
 'prior_nondeterministic_order':'15805149precanonical receipt retained, NOT_SELECT. Canonicalsortedaliases e45b7088 only',
 'deadline':'No newlong after00:00; common00:44:43 unchanged. DrootonlyGit/CI, allow_private=false',
 'publication':'Ownrecipe/components/receipts only; whole reconstructedsource private/ephemeral'}
(HERE/'CI-REQUEST-17-NATIVE-ADD-PORTFOLIO10.json').write_text(json.dumps(request,indent=2)+'\n',encoding='utf-8')
for name in ['READY.json','status.json']:
 d=json.loads((HERE/name).read_text());d['updated_at_utc']=now;d['preferred']='CI-REQUEST-17-NATIVE-ADD-PORTFOLIO10.json';d['portfolio10']=request;d['state']='NATIVE_ADD_PORTFOLIO10_EXACT_ALL12_READY_NOT_COMPILED'
 (HERE/name).write_text(json.dumps(d,indent=2)+'\n',encoding='utf-8')
text=(HERE/'HANDOFF.md').read_text();insert='''
**Current requested portfolio10 ready:** `CI-REQUEST-17-NATIVE-ADD-PORTFOLIO10.json`, **255604B/e45b7088…8d3fb**,396B free, policyPASS, exact2-process reproduction. Canonicalsortedaliases only; old15805149 pre-canonical notselect. Native64add YaW/YaX/Ybf/W1 + frozen6fe5 GEMM; retainMYbc, RMSfieldkernel0 with12exclusiveRMSdecls pruned (zero refs). Ccuts use directModel.add largegap fallback and directofFnYbf. Actualall12connected but NOT_COMPILED. Missing9aliases opened late; onlyproof punctuation spaces compressed, application spaces/indentation retained. No9nativeoutputs/inputread, no tuning; target23:43 missed, canonicalready23:47. Gate thenfreshstandardcurrentMixer36 only. Drootsolequeue.
'''
text=text.replace('# R27 native current handoff\n','# R27 native current handoff\n'+insert,1)
(HERE/'HANDOFF.md').write_text(text,encoding='utf-8');print(json.dumps({k:request[k] for k in ['at_utc','request','recipe_sha256','candidate_sha256','candidate_bytes','free_bytes','state']}))
