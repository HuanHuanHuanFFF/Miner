from pathlib import Path
from datetime import datetime,timezone
import json,hashlib,re
H=Path(__file__).resolve().parent;W=H/'web/R7-W13d/original-extracted/R7-W13d';OLD=H/'web/R7-W13c/original-extracted/R7-W13c'
expected={'Kernel':'e8fb1bb6671db553162a4e5fcd44d5bc47c7923df68b32cd7cbb9bd8bf65bf54','KernelDiagnostics':'4db627a9824f7737aa6c44a0d3ae7cf7ba60c15a31f31314f3690b91ab527453'}
rows=[]
for name,sha in expected.items():
 b=(W/'source'/(name+'.lean')).read_bytes();assert hashlib.sha256(b).hexdigest()==sha;assert b==(OLD/(name+'.lean')).read_bytes()
 assert b==(W/'logs'/(name+'-strict-source.lean')).read_bytes()
 assert not re.search(rb'\bset_option\s+(?:autoImplicit|relaxedAutoImplicit)\b',b)
 d=json.loads((W/'logs'/(name+'-strict.json')).read_text());assert d['exit_code']==0 and d['spawned'] and not d['output_existed_before'] and d['output_exists_after'];assert d['source_sha256']==sha==d['source_sha256_after']
 for flag in ['-DautoImplicit=false','-DrelaxedAutoImplicit=false']:assert d['argv'].count(flag)==1
 assert not any(x in d['argv'] for x in ['-DautoImplicit=true','-DrelaxedAutoImplicit=true'])
 for stream in ['stdout','stderr']:
  p=W/d[stream]['path'];raw=p.read_bytes();assert len(raw)==d[stream]['bytes'] and hashlib.sha256(raw).hexdigest()==d[stream]['sha256'];assert not re.search(rb'(^|\n).*\berror(?:\(|:)',raw)
 rows.append({k:d[k] for k in ['label','argv','source_sha256','exit_code','start_utc','end_utc','output_existed_before','output_sha256']})
main=(W/'source/Kernel.lean').read_bytes();diag=(W/'source/KernelDiagnostics.lean').read_bytes();assert diag.startswith(main)
assert re.findall(rb'(?m)^import\s+([^\r\n]+)',diag)==[b'ContractTensor']
audit=json.loads((W/'logs/strict-axiom-audit.json').read_text());assert audit['status']=='PASS' and audit['checked_declarations']==80 and not audit['unapproved']
out={'checked_at_utc':datetime.now(timezone.utc).isoformat(),'scope':'Exactpublice8fb same-source strictPLAINLean compilation plusdiagnostic80declarationaudit. No candidate353d/3d9 compile, no officialkernelreplay/fullgate/C/timing inherited.','strict_invocations':rows,'source_bytes_equal_W13c':True,'diagnostic_contains_exact_main_without_importing_main_olean':True,'axiom_audit_declarations':80,'allowed_axioms':audit['allowed'],'environment_boundary':'Relocatedexistingfixedtoolchain/cache; Leanexecutable/sharedlibSHA,pins,Contract/config matched. EntireoldprunedoleancachebyteidentityUNKNOWN; no newtoolchaininstall. See originalenvironment-identity.json.','recovery_timing':'Externaljobwithin10min; Rstartabout01:42, originalfilesverified01:53:11,totalabout11min, includedinunchangedtenhourwindow.'}
(H/'w13d-strict-independent-audit.json').write_text(json.dumps(out,indent=2)+'\n');print(json.dumps({k:v for k,v in out.items() if k!='strict_invocations'},indent=2))
