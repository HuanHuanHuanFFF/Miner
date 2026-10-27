"""Import exact UInt64 math probe; audit both direct and support roots."""
from pathlib import Path
from datetime import datetime,timezone
import hashlib,json,re
HERE=Path(__file__).resolve().parent;ROOT=HERE.parents[4]
worker=HERE/'astra-workers/structural-frontier/inline-u64-mul/probe-b2-v1'
sha=lambda b:hashlib.sha256(b).hexdigest()
record=json.loads((worker/'manifest.json').read_bytes());raw=(worker/record['probe']['path']).read_bytes()
assert sha(raw)==record['probe']['sha256']=='9f9a297e90f236c349283248cca9aa8f94c35ff24ebe9e26873e2c63d708a933'
assert len(raw)==240164 and b'\r' not in raw
base=ROOT/'competitions/floatlib/candidates/f01-r15-dev-packed-b2-1/Kernel.lean';parent=base.read_bytes()
assert sha(parent)==record['parent']['sha256'] and raw.startswith(parent)
assert all(x is None for x in record['static_checks']['intake_policy_options'].values())
fragment=HERE/'development-u64-roundtrip-probe1-fragment.lean';assert not fragment.exists();fragment.write_bytes(raw[len(parent):])
names=record['dependency_support_roots']+record['explicit_helper_audit'];assert len(names)==len(set(names))==28
audit=HERE/'development-u64-roundtrip-28-helper-audit.lean.inc';audit.write_bytes(''.join('#print axioms '+n+'\n' for n in names).encode())
original_audit=(worker/record['audit_file']['path']).read_bytes();assert sha(original_audit)==record['audit_file']['sha256']
assert [x.decode() for x in re.findall(rb'^#print axioms ([A-Za-z0-9_.]+)\s*$',original_audit,re.M)]==record['explicit_helper_audit']
name='f01-r17-dev-u64-roundtrip-probe1';folder=base.parent.with_name(name);folder.mkdir();(folder/'Kernel.lean').write_bytes(raw)
manifest=dict(candidate=name,candidate_file='Kernel.lean',candidate_sha256=sha(raw),candidate_bytes=len(raw),parent=base.parent.name,parent_sha256=sha(parent),created_at_utc=datetime.now(timezone.utc).isoformat(),
    components=[dict(path=p.relative_to(ROOT).as_posix(),sha256=sha(p.read_bytes()),bytes=p.stat().st_size) for p in (fragment,audit)],
    mechanism='B2-prefix UInt64 exact product/numeric round-trip interface; no changed public runtime or timing claim.',validation_mode='statement-only',proof_status='NOT_COMPILED',performance='NOT_RUN',
    explicit_helper_audit=names,helper_audit_expected_count=28,helper_audit_source_sha256=sha(raw),helper_audit_required_endpoints=['Submission.R17UInt64Integer.numeric_integer_product','Submission.R17UInt64Integer.shift_recovery'],helper_audit_module_sha256=sha((HERE/'development-helper-audit.py').read_bytes()),
    source_policy='Exact producer source already passed original intake/policy/options; D rechecked SHA/LF/size/B2 prefix. Reuse only these unchanged text-check facts.',
    known_shared_issue='R18 first UInt32 compiler feedback shows final Int.toNat product normalization needs repair; do not dispatch this immutable source before that shared issue is resolved.')
(folder/'manifest.json').write_bytes((json.dumps(manifest,ensure_ascii=False,indent=2)+'\n').encode())
print(json.dumps(dict(candidate=name,sha256=sha(raw),bytes=len(raw),explicit_roots=28,dispatch='HELD_FOR_SHARED_NORMALIZATION_REPAIR')))
