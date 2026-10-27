from pathlib import Path
from datetime import datetime,timezone
import json,hashlib
H=Path(__file__).resolve().parent;R=H.parents[3]
D=R/'competitions/floatlib/candidates/f01-mul-log2-proof1/ci-runs/39840672791/download-81e3479e9e2b47249bf76c8d44eb2e62/diagnostics/f01-d7-public-suite'
W=H/'web/R7-W11/original-extracted/R7-W11'
idx=json.loads((D/'candidate-c-index.json').read_text());asm=json.loads((D/'native-assembly-index.json').read_text());plan=json.loads((D/'public-suite/parent-stage-profile/profile-current-plan.json').read_text())
rows=[]
for x in idx:
 p=D/x['file'];b=p.read_bytes();assert hashlib.sha256(b).hexdigest()==x['sha256'];assert x['kernel_sha256']=='8eb63a2fea39f8c483eb16857cb1dcc35ac4a30168ab91046a48aa1cb561e045'
 q=W/'generated'/(x['module']+'.c');qb=q.read_bytes()
 rows.append({'module':x['module'],'ci_diagnostic_kernel':x['kernel_sha256'],'ci_c_sha256':x['sha256'],'ci_c_bytes':len(b),'ci_source_path_recorded':x['source'],'web_kernel_sha256':'60f74aa4af01a9b35ece66a7c310e6b05b5b84b9b7121a4cccd12a0a9c987e15','web_c_sha256':hashlib.sha256(qb).hexdigest(),'web_c_bytes':len(qb),'identical_bytes':b==qb})
assert plan['kernel_sha256']==idx[0]['kernel_sha256']
original=(D/'public-suite/parent-stage-profile/profile-current-original.c').read_bytes();assert original==(D/'candidate-generated-0.c').read_bytes()
for x in asm:
 assert hashlib.sha256((D/x['file']).read_bytes()).hexdigest()==x['sha256']
out={'checked_at_utc':datetime.now(timezone.utc).isoformat(),'rows':rows,'profile_current_name_actual_kernel':plan['kernel_sha256'],'profile_original_C_equals_8eb_diagnostic_C':True,'native_asm_scope_from_original':asm[0]['scope'],'native_asm_object_sha256':asm[0]['object_sha256'],'finding':'The saved807 generatedC andnative-loopasm are8eb diagnosticstatementreplay, not60f andnotcleanedtimedgateobject. W11 uses60f/currentofficialMainFull includingBenchSuite, soCbyteidentity isnotexpected andnotestablished. No compilerinstability ornewruntimefailure followsfromthisdifferent-subject mismatch.','remaining':'No bridge toexact80760ftimedobject. KeepW11 offlinecodegen,8ebdiagnosticreplay,andfullgate timingverdicts separate. Parentprofilechecksums remainsemanticfiniteanchors, notnewcandidate runtimecall measurements.'}
(H/'codegen-subject-audit-807-w11.json').write_text(json.dumps(out,indent=2)+'\n');print(json.dumps(out,indent=2))
