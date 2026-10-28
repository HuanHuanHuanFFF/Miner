"""Revisit R22's unchanged ABI premise as a small diagnostic, not BMM timing."""
from pathlib import Path
import hashlib,json,datetime
ROOT=next(p for p in Path(__file__).resolve().parents if (p/'AGENTS.md').is_file())
HERE=Path(__file__).resolve().parent
def sha(b):return hashlib.sha256(b).hexdigest()
old=ROOT/'competitions/floatlib/candidates/f01-d7-research/round6h-20261027T211247Z/research/independent-frontier/Borrowed-tail-ABI.lean.inc'
raw=old.read_bytes();assert sha(raw)=='680ca1b3676bf0e3e71d92b94a858ad87c1481b41e878bab5b0fae0aeedf1495'
# Identifier-only substitution allows the already existing observer to capture both direct edges.
source=raw.decode().replace('R22TailABI','R22IndexedResident8TailABI')
import re
source=re.sub(r'\bhot\b','hotMul',source);source=re.sub(r'\bcold\b','coldMul',source)
inverse=source.replace('R22IndexedResident8TailABI','R22TailABI')
inverse=re.sub(r'\bhotMul\b','hot',inverse);inverse=re.sub(r'\bcoldMul\b','cold',inverse)
assert inverse.encode()==raw
base=ROOT/'competitions/floatlib/candidates/f01-r15-dev-packed-b2-1/Kernel.lean'
prefix=base.read_bytes();assert sha(prefix)=='622d8394a7127e93dcaf992c62c6dfcff7208d212738409a5e34525dfafd1a58'
blob=prefix+b'\n'+source.encode();assert len(blob)<=256000
out=ROOT/'competitions/floatlib/candidates/f01-r23-research-tail-abi';out.mkdir(exist_ok=True)
(out/'Kernel.lean').write_bytes(blob);(HERE/'TailABI.lean.inc').write_bytes(source.encode())
helper='f01-d7-research/round9h-20261026T194639Z/development-helper-audit-v8.py'
roots=['Submission.R22IndexedResident8TailABI.'+s for s in ['hotMul','coldMul']]
m=dict(candidate=out.name,candidate_file='Kernel.lean',candidate_sha256=sha(blob),candidate_bytes=len(blob),
 created_at_utc=datetime.datetime.now(datetime.timezone.utc).isoformat(),validation_mode='statement-only',diagnostic_only=True,
 diagnostic_timeout_seconds=180,proof_status='NOT_RUN_DIAGNOSTIC_ONLY',performance='NO_BMM_OR_SCORE_CLAIM',
 formal_submission='NOT_SUBMITTED',official_submission_inherited=False,
 helper_audit_module='development-helper-audit-v8.py',helper_audit_module_path=helper,
 helper_audit_module_sha256=sha((ROOT/'competitions/floatlib/candidates'/helper).read_bytes()),
 explicit_helper_audit=roots,helper_audit_required_endpoints=roots,helper_audit_expected_count=2,helper_audit_source_sha256=sha(blob),diagnostic_evaluations=[],
 old_fragment_sha256=sha(raw),fragment_sha256=sha(source.encode()),fragment_bytes=len(source.encode()),inverse_identifier_map_verified=True,
 runtime_base_sha256=sha(prefix),runtime_base_prefix_bytes=len(prefix),
 scope='Old R22 same-signature borrowed-array mutual 8Float32 ABI probe, only identifier renames for existing object observer. Public endpoints B2, no actual BMM. First falsifier direct cross-edge ABI/postcallRC/stack, not runtime speed.',
 components=[dict(path=old.relative_to(ROOT).as_posix(),sha256=sha(raw)),dict(path=(HERE/'TailABI.lean.inc').relative_to(ROOT).as_posix(),sha256=sha(source.encode()))])
(out/'manifest.json').write_text(json.dumps(m,indent=2)+'\n',encoding='utf-8')
print(json.dumps({'candidate':out.name,'sha256':sha(blob),'bytes':len(blob),'roots':roots}))
