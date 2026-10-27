"""Independent byte audit only; do not modify development sources or Git."""
from pathlib import Path
from hashlib import sha256
from datetime import datetime, timezone
from time import monotonic
import json

start=monotonic();base=Path(__file__).resolve().parent;root=base.parents[4]
support_dir=root/'competitions/floatlib/candidates/f01-r14-dev-word-add-support1'
manifest=json.loads((support_dir/'manifest.json').read_bytes())
parent=root/'competitions/floatlib/candidates/f01-r14-dev-compact-base/Kernel.lean'
parent_bytes=parent.read_bytes()
assert sha256(parent_bytes).hexdigest()==manifest['parent_sha256']
assembled=parent_bytes;components=[]
for component in manifest['components']:
    b=(root/component['path']).read_bytes()
    assert len(b)==component['bytes'] and sha256(b).hexdigest()==component['sha256']
    components.append(dict(path=component['path'],bytes=len(b),sha256=component['sha256']))
    assembled+=b'\n'+b
source=(support_dir/'Kernel.lean').read_bytes()
assert source==assembled
assert len(source)==manifest['candidate_bytes']<256001
assert sha256(source).hexdigest()==manifest['candidate_sha256']

repairs=[]
for original,newer in [('f01-r14-dev-integer-exponent1','f01-r14-dev-integer-exponent3'),
                       ('f01-r14-dev-combined-slim1','f01-r14-dev-combined-slim3'),
                       ('f01-r14-dev-combined-headroom1','f01-r14-dev-combined-headroom3')]:
    old=(root/'competitions/floatlib/candidates'/original/'Kernel.lean').read_bytes()
    new=(root/'competitions/floatlib/candidates'/newer/'Kernel.lean').read_bytes()
    assert old.count(b'FastMul.mkW_eq')==1
    needle=b'    rw [parity, UInt64.toNat_and, hshift]'
    assert old.count(needle)==1
    nl=b'\r\n' if b'\r\n' in old else b'\n'
    expected=old.replace(b'FastMul.mkW_eq',b'FastMul.mkW_ofNat').replace(needle,
        b'    dsimp only [parity]'+nl+b'    rw [UInt64.toNat_and, hshift]')
    assert new==expected
    repairs.append(dict(original=original,original_sha256=sha256(old).hexdigest(),
        newer=newer,newer_sha256=sha256(new).hexdigest(),bytes=len(new),
        only_name_and_local_let_unfold_changed=True,original_preserved=True))

runtime=(base/'development-word-add-runtime3.lean').read_bytes()
assert b'R14SmallShiftBias.biased' in runtime
assert 'if e - 1 ≤ (253 : UInt32) then' in runtime.decode('utf-8')
assert b'else fallback x y' in runtime
old_bias=(base/'astra-biased-rne2.lean').read_text(encoding='utf-8')
small_bias=(base/'astra-small-shift-bias2.lean').read_text(encoding='utf-8')
definition='  (p + ((1 : UInt64) <<< (t - 1)) - 1 + ((p >>> t) &&& 1)) >>> t'
assert definition in old_bias and definition in small_bias

record=dict(timestamp_utc=datetime.now(timezone.utc).isoformat(),
    state='EXACT_SOURCE_COMPOSITION_VERIFIED_NOT_COMPILED',elapsed_seconds=monotonic()-start,
    support=dict(candidate=manifest['candidate'],sha256=manifest['candidate_sha256'],
        bytes=len(source),remaining_bytes=256000-len(source),
        parent=manifest['parent'],parent_preserved_as_exact_prefix=True,
        components=components,public_runtime='Unchanged compact retained four-kernel prefix; appended diagnostic helpers only'),
    repairs=repairs,
    add_runtime=dict(component='development-word-add-runtime3.lean',
        sha256=sha256(runtime).hexdigest(),biased_runtime_definition_identical=True,
        result_guard='Full UInt32 e-1<=253, not masked exponent field',
        fallback_order='original x y'),
    remaining='Actual UInt32 magnitude/one-bit-log/rounding/field composition and final public add_spec; all Lean/public gate/performance NOT_RUN. Diagnostic support source alone has1443B headroom, so pruning/new integration is required.',
    authorization='Read-only audit, no candidate/index/push/CI mutation.')
record['audit_preflight_failure']='An unnecessary assertion expected the comment token Option in runtime3; it was absent. Removed that comment-dependent assertion. This was an audit-script issue, not candidate arithmetic or Lean feedback.'
Path(__file__).with_suffix('.json').write_text(json.dumps(record,indent=2,ensure_ascii=False)+'\n',encoding='utf-8')
print(json.dumps({k:v for k,v in record.items() if k not in ['support']},indent=2,ensure_ascii=False))
print(json.dumps({k:v for k,v in record['support'].items() if k!='components'},indent=2,ensure_ascii=False))
