from pathlib import Path
from datetime import datetime,timezone
import json,hashlib
HERE=Path(__file__).resolve().parent;now=datetime.now(timezone.utc).isoformat()
original=json.loads((HERE/'CI-REQUEST-17-NATIVE-ADD-PORTFOLIO10.json').read_text())
out=dict(original);out.update(at_utc=now,request='mixer-native-add-portfolio10-qualified-v2',
 recipe='development/native/graft_native_add_portfolio10_v2.py',
 recipe_sha256=hashlib.sha256((HERE/'graft_native_add_portfolio10_v2.py').read_bytes()).hexdigest(),
 interface="transform(raw23,submission=23,variant='mixer-native-add-portfolio10-qualified-v2',donor_raw=None)->bytes",
 candidate_sha256='f60551d55be31d2d2d4a59ba2646c8769d1cb8e31538176041070a0477881bea',candidate_bytes=255666,free_bytes=334,
 preference='Prefer thisfullyqualifiedv2 if10notdispatched. Ife45v1 alreadydispatched, keepitunchanged andcollect; v2 onlyifactualresolutionfailure. No duplicateconsensus queue',
 reason='Late openNat/Model imports also unrelatednamespaceconstants;9fullyqualifiedconstants avoidchangingresolution. Proof-only punctuation579Bsavingsnowfitsfullqualifications',
 space='No newlateopens. Nativeaddclosure7972B, retainedall12/LayerNorm/GEMM,12RMS-exclusivedeclarationspruned. Same runtime algorithmasv1, exactsourcegate stillUNKNOWN',
 prior_nondeterministic_order='158precanonical NOTSELECT; e45canonicalv1 retainedbutnotpreferredifnotdispatched; f605fullyqualifiedv2 preferred',
 timeline='Firstcap-fit23:45, e45canonical23:47, saferfullyqualifiedf60523:52; target23:43missed. No9nativeinputs/outputs consumed')
out['dependencies'].append({'path':'development/native/graft_native_add_portfolio10.py','sha256':'6d4f12349641bbb6587d844414cf1a5209c7f874a7ca4a1f1a51f2aec2123943'})
(HERE/'CI-REQUEST-17-QUALIFIED-ADDENDUM.json').write_text(json.dumps(out,indent=2)+'\n',encoding='utf-8')
for n in ['READY.json','status.json']:
 d=json.loads((HERE/n).read_text());d['updated_at_utc']=now;d['preferred']='CI-REQUEST-17-QUALIFIED-ADDENDUM.json';d['portfolio10_v2']=out
 (HERE/n).write_text(json.dumps(d,indent=2)+'\n',encoding='utf-8')
t=(HERE/'HANDOFF.md').read_text();t=t.replace('# R27 native current handoff\n','# R27 native current handoff\n\n**23:52 saferqualifiedv2 preferred ifnotdispatched:** `CI-REQUEST-17-QUALIFIED-ADDENDUM.json`, **255666B/f60551d5…81bea**,334Bfree/policyPASS/all12declaredNOT_COMPILED. Nine fullyqualifiedconstants avoidlateopenNat/Model broadresolution. Samealgorithm/pruning; no9inputs/outputstuning. Ife45v1 alreadyrunning, do notmutate/cancel orduplicate; collectandusev2onlyonactualresolutionfailure.\n',1)
(HERE/'HANDOFF.md').write_text(t,encoding='utf-8');print(json.dumps({k:out[k] for k in ['at_utc','candidate_sha256','candidate_bytes','recipe_sha256','preference']}))
