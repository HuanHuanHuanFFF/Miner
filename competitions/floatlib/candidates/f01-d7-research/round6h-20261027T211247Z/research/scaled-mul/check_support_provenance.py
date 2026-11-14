"""Bind reused R17 support to the exact archived accepted input and its raw audit."""
from pathlib import Path
from datetime import datetime, timezone
import hashlib, json

HERE = Path(__file__).resolve().parent
ROOT = next(p for p in HERE.parents if (p/'AGENTS.md').exists())
R17 = ROOT/'competitions/floatlib/candidates/f01-r17-dev-u64-roundtrip-repair1/Kernel.lean'
FRAGMENT = ROOT/'competitions/floatlib/candidates/f01-d7-research/round11h-20261025T173831Z/development-u64-roundtrip-repair1-fragment.lean'
BASE = ROOT/'competitions/floatlib/candidates/f01-r15-dev-packed-b2-1/Kernel.lean'
RUN = ROOT/'competitions/floatlib/candidates/f01-mul-log2-proof1/ci-runs/40296747927/download-cbb1d67b6cc844608eaa522694021fd7/diagnostics/f01-d7-public-suite/public-suite'
ARCHIVE = RUN/'inputs/f01-r17-dev-u64-roundtrip-repair1/Kernel.lean'
AUDIT = RUN/'diagnostics/f01-r17-dev-u64-roundtrip-repair1/helper-audit.json'
VERDICT = RUN/'f01-r17-dev-u64-roundtrip-repair1-verdict.json'
sha=lambda p:hashlib.sha256(p.read_bytes()).hexdigest()
assert R17.read_bytes()==ARCHIVE.read_bytes()==BASE.read_bytes()+FRAGMENT.read_bytes()
audit=json.loads(AUDIT.read_text()); verdict=json.loads(VERDICT.read_text())
assert audit['kernel_sha256']==sha(R17) and audit['accepted'] and audit['kernel_replay'] and verdict['passed']
allowed={'propext','Classical.choice','Quot.sound'}
assert all(set(v)<=allowed for v in audit['reports'].values())
out={
  'checked_utc':datetime.now(timezone.utc).isoformat(),
  'state':'REUSED_R17_SOURCE_ARCHIVE_REPLAY_AXIOM_BINDING_VERIFIED',
  'run_id':40296747927,
  'files':{str(p.relative_to(ROOT)).replace('\\','/'):{'sha256':sha(p),'bytes':p.stat().st_size} for p in [BASE,FRAGMENT,R17,ARCHIVE,AUDIT,VERDICT]},
  'exact_fragment_in_archived_kernel':True,'old_root_count':28,
  'new_probe_status':'NOT_RUN',
  'scope':'Historical R17 source provenance only. Does not transfer replay/audit acceptance to R22 composition.',
}
(HERE/'support-provenance.json').write_text(json.dumps(out,indent=2)+'\n',encoding='utf-8')
print(json.dumps({k:v for k,v in out.items() if k!='files'},indent=2))
