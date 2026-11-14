from pathlib import Path
from datetime import datetime, timezone
import hashlib,json

HERE=Path(__file__).resolve().parent
ROUND=HERE.parents[1]
RUN=ROUND/'ci-runs/40588875685/download-7e10038626b14b4fa0b4efba2c7100c9'
RAW=RUN/'diagnostics/f01-r22-dev-scaled-product-probe1'
SOURCE=RUN/'inputs/f01-r22-dev-scaled-product-probe1/Kernel.lean'
AUDIT=RAW/'helper-audit.json'
AXIOMS=RAW/'helper-axioms.raw'
LOG=RAW/'replay.log'
VERDICT=RUN/'f01-r22-dev-scaled-product-probe1-verdict.json'
manifest=json.loads((HERE/'probe1-manifest.json').read_text())
audit=json.loads(AUDIT.read_text()); verdict=json.loads(VERDICT.read_text())
sha=lambda p:hashlib.sha256(p.read_bytes()).hexdigest()
assert SOURCE.read_bytes()==(HERE/'Kernel-probe1.lean').read_bytes()
assert sha(SOURCE)==audit['kernel_sha256']=='6589f24df6d0048533e3689733d291c5b6f9a0a86328d689fd54c029be595d5e'
assert audit['names']==manifest['explicit_helper_audit'] and audit['expected_count']==5
assert audit['accepted'] and audit['kernel_replay'] and audit['exit_code']==0 and verdict['passed']
assert sha(AXIOMS)==audit['output_sha256']
assert set(audit['reports'])==set(audit['names'])
assert all(set(v)<={'propext','Classical.choice','Quot.sound'} for v in audit['reports'].values())
log=LOG.read_text()
assert 'Submission replays cleanly' in log and 'VerifyFull replays cleanly' in log
assert '[statement] ok' in log and '[helper-axioms] ok' in log
out={
 'checked_utc':datetime.now(timezone.utc).isoformat(),
 'state':'VERIFIED_STATEMENT_TWO_MODULE_REPLAY_FIVE_ROOTS_ALLOWED_AXIOMS',
 'run_id':40588875685,'source_sha256':sha(SOURCE),'source_bytes':SOURCE.stat().st_size,
 'files':{str(p.relative_to(ROUND)).replace('\\','/'):{'sha256':sha(p),'bytes':p.stat().st_size} for p in [SOURCE,AUDIT,AXIOMS,LOG,VERDICT]},
 'old_support_roots':3,'new_substantive_bridge_roots':2,'accepted_roots':audit['names'],
 'scope':'Actual nonwrapping UInt64 product native Float32 decode and R21 scaled fields. B2 public endpoints unchanged.',
 'probe2_repack_guard_status':'NOT_RUN','full_new_public_MUL':'NOT_PROVED',
 'runtime_cost':'NEGATIVE_COMPLETE_CALL_DISCOVERY_RETAINED','full_gate':False,'formal_submission':'NOT_SUBMITTED',
}
(HERE/'probe1-acceptance-40588875685.json').write_text(json.dumps(out,indent=2)+'\n',encoding='utf-8')
print(json.dumps({k:v for k,v in out.items() if k!='files'},indent=2))
