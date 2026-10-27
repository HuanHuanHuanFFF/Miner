"""Final exact-source/component/metadata check; no compiler or benchmark."""
from pathlib import Path
from datetime import datetime,timezone
import ast,hashlib,json
H=Path(__file__).resolve().parent;R=next(p for p in H.parents if(p/'competitions/floatlib/pins.json').is_file())
C=R/'competitions/floatlib/candidates/f01-r19-dev-add-cost1';m=json.loads((C/'manifest.json').read_text())
sha=lambda p:hashlib.sha256(p.read_bytes()).hexdigest()
assert sha(C/'Kernel.lean')==m['candidate_sha256']=='d3c550da05a3e91b5b037bed77623545dbe72af385d826ebc73236d2ed7ec2b5'
assert (C/'Kernel.lean').stat().st_size==m['candidate_bytes']==228686
assert (C/'Kernel.lean').read_bytes().startswith((R/'competitions/floatlib/candidates/f01-r15-dev-packed-b2-1/Kernel.lean').read_bytes())
assert len(m['components'])==16 and len({x['path']for x in m['components']})==16
for x in m['components']:
 p=R/x['path'];assert p.resolve().is_relative_to(H.resolve()) and sha(p)==x['sha256']and p.stat().st_size==x['bytes']
hook=H.parent/'development-add-cost-audit.py';assert sha(hook)==m['helper_audit_module_sha256']
for p in(H/'driver.py',hook,H/'build-package.py',H/'make-local-verifier.py',H/'verify-local.py',Path(__file__)):ast.parse(p.read_text())
assert m['historical_statement_evidence']['run']==40430974047
assert m['historical_statement_evidence']['relationship']=='PARENT_ONLY_NOT_CURRENT_D3_REPLAY'
assert m['historical_statement_evidence']['source_sha256']==m['parent_sha256']=='77377f8b373988545c557aa6f5cd5edfd82ec772bb643a404a15e26e02d627af'
binding=json.loads((H/'historical-bindings.json').read_text());assert binding['source_sha256']==m['parent_sha256']and binding['current_carrier_sha256']==m['candidate_sha256']
assert sha(H/'historical-bindings.json')==m['historical_statement_evidence']['binding_sha256']
assert m['runtime_cost']['changed_operation']=='ADD'and m['runtime_cost']['overall_budget_seconds_from_stage_registration']==580 and m['diagnostic_timeout_seconds']==600
assert m['runtime_cost']['order_per_seed']==['control','guarded','guarded','control']and m['runtime_cost']['processes']==8
assert m['current_carrier_replay_status']=='NOT_RUN'and len(m['current_carrier_followup_roots'])==7
local=json.loads((H/'local-verification.json').read_text());assert len(local['checks'])==24 and all(x['pass']for x in local['checks'])
assert not list(H.glob('.local-fixtures-*'))
snap=json.loads((H/'carrier-77377-before-switch/snapshot-receipt.json').read_text())
for x in snap['files']:assert sha(Path(x['snapshot']))==x['sha256']and Path(x['snapshot']).stat().st_size==x['bytes']
main=(H/'R19AddCostMain.lean').read_text();assert main.count('@[noinline] def r19Cost')==2 and main.count('Bench.Suite.run ')==1
assert 'Bench.Suite.run add Submission.mul Submission.sum Submission.bmm'in main
assert 'diagnosticEntry'not in main and 'guardedMul'not in main
receipt=dict(at_utc=datetime.now(timezone.utc).isoformat(),state='ADD_D3_PACKAGE_STATIC_PASS_REMOTE_NOT_RUN',
 source_sha256=m['candidate_sha256'],source_bytes=m['candidate_bytes'],manifest_sha256=sha(C/'manifest.json'),
 hook_sha256=sha(hook),driver_sha256=sha(H/'driver.py'),caller_sha256=sha(H/'R19AddCostMain.lean'),
 components=16,local_synthetic_checks=24,synthetic_fixtures_remaining=0,
 historical_replay='CI12 parent77377 only',current_D3_statement='NOT_RUN',current_D3_replay7roots='NOT_RUN',
 actual_arity_C_ASM='NOT_RUN; driver requires two static arity2 zero-capture closures before any timer',actual_benchmark='NOT_RUN')
(H/'final-verification.json').write_bytes((json.dumps(receipt,indent=2)+'\n').encode());print(json.dumps(receipt,indent=2))
