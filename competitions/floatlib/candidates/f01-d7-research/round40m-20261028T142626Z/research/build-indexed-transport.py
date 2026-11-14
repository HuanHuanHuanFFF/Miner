"""Assemble an exact runtime probe; delete only entirely empty lines for capacity."""
from pathlib import Path
import hashlib,json,datetime
ROOT=next(p for p in Path(__file__).resolve().parents if (p/'AGENTS.md').is_file())
HERE=Path(__file__).resolve().parent
def sha(b): return hashlib.sha256(b).hexdigest()
base=ROOT/'competitions/floatlib/candidates/f01-r22-dev-indexed8-loop-probe2/Kernel.lean'
raw=base.read_bytes()
assert sha(raw)=='7981b04cfe8fa1bf68eec31bd8c5d8abdd6a2e50c1a46bd5f7456a9a9d4d3ba8'
compact=b''.join(line for line in raw.splitlines(keepends=True) if line.strip())
assert [x for x in raw.splitlines() if x.strip()]==compact.splitlines()
proof=(HERE/'IndexedTransport.lean.inc').read_bytes()
blob=compact+b'\n'+proof
assert len(blob)<=256000,len(blob)
out=ROOT/'competitions/floatlib/candidates/f01-r23-research-indexed-transport'
out.mkdir(exist_ok=True)
(out/'Kernel.lean').write_bytes(blob)
helper='f01-d7-research/round9h-20261026T194639Z/development-helper-audit-v8.py'
roots=['Submission.R22IndexedResident8.'+s for s in ['tile_eq_nat','tiles_eq_nat','output_eq_nat']]
manifest=dict(candidate=out.name,candidate_file='Kernel.lean',candidate_sha256=sha(blob),candidate_bytes=len(blob),
 created_at_utc=datetime.datetime.now(datetime.timezone.utc).isoformat(),validation_mode='statement-only',diagnostic_only=True,
 proof_status='NOT_RUN',performance='NO_NEW_RUNTIME_NO_PERFORMANCE_CLAIM',formal_submission='NOT_SUBMITTED',
 helper_audit_module='development-helper-audit-v8.py',helper_audit_module_path=helper,
 helper_audit_module_sha256=sha((ROOT/'competitions/floatlib/candidates'/helper).read_bytes()),
 explicit_helper_audit=roots,helper_audit_required_endpoints=roots,helper_audit_expected_count=len(roots),
 helper_audit_source_sha256=sha(blob),diagnostic_evaluations=[],diagnostic_timeout_seconds=600,
 scope='Actual USize indexed8 complete output equals actual Nat resident8 output under original generated bounds. Public four remain B2. Resident8 output-to-reference proof remains open.',
 source_base_sha256=sha(raw),base_compaction='Only remove wholly blank lines; every nonblank line exact unchanged',
 components=[dict(path=proof_path,sha256=sha((ROOT/proof_path).read_bytes())) for proof_path in [(HERE/'IndexedTransport.lean.inc').relative_to(ROOT).as_posix()]],
 source_prefix_bytes=len(compact),source_prefix_sha256=sha(compact))
(out/'manifest.json').write_text(json.dumps(manifest,indent=2)+'\n',encoding='utf-8')
(HERE/'indexed-transport-source-receipt.json').write_text(json.dumps(manifest,indent=2)+'\n',encoding='utf-8')
print(json.dumps({'candidate':out.name,'bytes':len(blob),'sha256':sha(blob),'roots':roots}))
