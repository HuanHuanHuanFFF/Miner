"""Replace just the proved scale reader; preserve all numerical expressions."""
from pathlib import Path
from datetime import datetime, timezone
import hashlib,json

HERE=Path(__file__).resolve().parent
ROOT=next(p for p in HERE.parents if (p/'AGENTS.md').is_file())
CANDIDATES=ROOT/'competitions/floatlib/candidates'
sha=lambda b:hashlib.sha256(b).hexdigest()
raw=(CANDIDATES/'f01-r15-dev-packed-b2-1/Kernel.lean').read_bytes()
assert sha(raw)=='622d8394a7127e93dcaf992c62c6dfcff7208d212738409a5e34525dfafd1a58'
base=raw.decode()
start=base.index('@[inline] def scaleAt (u : UInt32)')
end=base.index('theorem zero_fields',start)
old=base[start:end]
assert old.count('def ')==1 and old.count('theorem ')==1
fragment=(HERE/'DenseScale.lean.inc').read_bytes()
blob=base[:start].encode()+fragment+b'\n\n'+base[end:].encode()
assert len(blob)<=256000
out=CANDIDATES/'f01-r24-research-representation-densescale1'
out.mkdir(exist_ok=True)
(out/'Kernel.lean').write_bytes(blob)
helper='f01-d7-research/round9h-20261026T194639Z/development-helper-audit-v8.py'
roots=['R2W01b.'+r for r in ['denseScaleTable_size','denseScaleFloat_eq','denseScaleRead_eq','scaleAt_eq']]
m=dict(candidate=out.name,candidate_file='Kernel.lean',candidate_sha256=sha(blob),candidate_bytes=len(blob),
    created_at_utc=datetime.now(timezone.utc).isoformat(),validation_mode='statement-only',diagnostic_only=True,
    diagnostic_timeout_seconds=240,proof_status='NOT_RUN',performance='NOT_RUN',formal_submission='NOT_SUBMITTED',
    official_submission_inherited=False,helper_audit_module='development-helper-audit-v8.py',
    helper_audit_module_path=helper,helper_audit_module_sha256=sha((CANDIDATES/helper).read_bytes()),
    explicit_helper_audit=roots,helper_audit_required_endpoints=roots,helper_audit_expected_count=len(roots),
    helper_audit_source_sha256=sha(blob),diagnostic_evaluations=[],runtime_base_sha256=sha(raw),
    old_reader_sha256=sha(old.encode()),fragment_sha256=sha(fragment),
    byte_identical_base_prefix=len(base[:start].encode()),byte_identical_base_suffix=len(base[end:].encode()),
    semantics='Only scaleAt storage/reader changed, original scaleAt_eq preserved. Every scalar and fold arithmetic order and fallback is byte-identical.',
    mechanism='Static checked FloatArray scale table replaces Array Float32 pointer chase with direct double load plus inline narrowing. Original 512-entry table remains for validation and fallback. One global bool read/branch is charged.',
    first_falsifier='Actual hot scalar path has extra calls, per-op checks/boxing/allocation, or the dense load and narrowing fail to reduce complete scalar cost. Module initialization must also be reported.',
    cost_boundary='Original public full call; no benchmark/gate/compiler modifications and no assumption opaque wide/narrow roundtrip is generally exact.')
(out/'manifest.json').write_text(json.dumps(m,indent=2)+'\n',encoding='utf-8')
(HERE/'dense-scale-source-receipt.json').write_text(json.dumps(m,indent=2)+'\n',encoding='utf-8')
print(json.dumps({'candidate':out.name,'bytes':len(blob),'sha256':sha(blob),'roots':roots}))
