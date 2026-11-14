"""Compose frozen mathematical components under the original ContractTensor.

This is a proof integration probe. It preserves the shipped four public callbacks,
and is not a performance candidate or a new competition implementation.
"""
from pathlib import Path
import datetime, hashlib, json

ROOT = next(p for p in Path(__file__).resolve().parents if (p/'AGENTS.md').is_file())
HERE = Path(__file__).resolve().parent
BASE = ROOT/'competitions/floatlib/candidates'
NAME = 'f01-r24-dev-portable-island1'
OUT = BASE/NAME
OUT.mkdir(exist_ok=True)
sha = lambda b: hashlib.sha256(b).hexdigest()
retained = BASE/'f01-r15-dev-packed-b2-1/Kernel.lean'
b2 = retained.read_bytes()
assert sha(b2) == '622d8394a7127e93dcaf992c62c6dfcff7208d212738409a5e34525dfafd1a58'
incumbent = ROOT/'competitions/floatlib/references/official-incumbent/Kernel.lean'
prefix = incumbent.read_bytes()
assert sha(prefix) == '5d0cef3ff21093ca05cde92e516edfe45afca8e11996ad4858e7fb2407d65868'

# The old B2 proof is format-polymorphic. Reuse its exact four-lemma closure,
# excluding its width-specific Float32 wrapper and unrelated runtime kernels.
start = b2.index(b'namespace R2W01c\n\nnamespace NativeBridge')
end = b2.index(b'theorem toModelNativeMul', start)
bridge = b2[start:end] + b'end NativeBridge\nend R2W01c\n'
bridge_path = HERE/'PortableNativeMulBridge.lean.inc'
if bridge_path.exists(): assert bridge_path.read_bytes() == bridge
else: bridge_path.write_bytes(bridge)

inputs = [
    ('f01-r24-research-scalar-quotient2', None),
    ('f01-r24-dev-broad-cell-primitive2', None),
    ('f01-r24-dev-scalar-power-cell2', 'CellPower-v2.lean.inc'),
    ('f01-r24-research-representation-widen2', None),
    ('f01-r24-research-native-mul-bridge2', None),
    ('f01-r24-research-representation-sum1', None),
]
parts = [bridge]
components = [{'path':bridge_path.relative_to(ROOT).as_posix(), 'bytes':len(bridge), 'sha256':sha(bridge)}]
parents = []
names = ['Submission.add_spec','Submission.mul_spec','Submission.sum_spec','Submission.bmm_spec']
for name, selected in inputs:
    path = BASE/name
    manifest = json.loads((path/'manifest.json').read_bytes())
    kernel = (path/'Kernel.lean').read_bytes()
    assert sha(kernel) == manifest['candidate_sha256'] and kernel.startswith(b2)
    if 'components' in manifest:
        children = manifest['components']
    else:
        children = [manifest['fragment']]
    for component in children:
        p = ROOT/component['path']
        raw = p.read_bytes()
        assert sha(raw) == component['sha256'] and len(raw) == component['bytes']
        if selected and p.name != selected: continue
        parts.append(raw)
        components.append({'path':p.relative_to(ROOT).as_posix(), 'bytes':len(raw), 'sha256':sha(raw)})
    names += [n for n in manifest['explicit_helper_audit'] if n not in names]
    parents.append({'candidate':name,'sha256':sha(kernel),'status':'FROZEN_UNCOMPILED_SOURCE_NOT_INHERITED_ACCEPTANCE'})

raw = prefix + b'\n\n' + b'\n\n'.join(parts)
assert len(raw) <= 256000 and len(names) == len(set(names))
kernel_path = OUT/'Kernel.lean'
if kernel_path.exists(): assert kernel_path.read_bytes() == raw, 'Frozen island requires a new version'
else: kernel_path.write_bytes(raw)
manifest = dict(candidate=NAME, candidate_file='Kernel.lean', candidate_sha256=sha(raw), candidate_bytes=len(raw),
    validation_mode='statement-only', diagnostic_only=True, diagnostic_timeout_seconds=600,
    proof_status='NOT_RUN_INTEGRATED_PORTABLE_PROOF_ISLAND', performance='NOT_A_PERFORMANCE_CANDIDATE',
    formal_submission='NOT_SUBMITTED', official_submission_inherited=False,
    helper_audit_module='development-helper-audit-v8.py',
    helper_audit_module_path='f01-d7-research/round9h-20261026T194639Z/development-helper-audit-v8.py',
    helper_audit_module_sha256='5b58eece211bd9cdaa270fc82bef624a5974c7d056732e19f54547c0fe6ef975',
    explicit_helper_audit=names, helper_audit_required_endpoints=names,
    helper_audit_expected_count=len(names), helper_audit_source_sha256=sha(raw), diagnostic_evaluations=[],
    components=components, parents=parents,
    runtime_prefix={'path':incumbent.relative_to(ROOT).as_posix(),'sha256':sha(prefix),'bytes':len(prefix),'byte_identical':True},
    extracted_dependency={'source_path':retained.relative_to(ROOT).as_posix(),'source_sha256':sha(b2),
        'start_byte':start,'end_byte_exclusive':end,'exact_extracted_bytes':end-start,
        'extracted_sha256':sha(b2[start:end]),'only_added_text':'Two namespace end lines'},
    scope='Original ContractTensor portable component integration; exact shipped four callbacks/proofs. No new competition record, source algorithm, whole-kernel performance or adoption.',
    acceptance_boundary='Only this precise composed source can receive CI acceptance. Parent helper packages remain NOT_RUN unless separately validated.',
    common_deadline_utc='2026-10-29T03:38:56Z')
target = OUT/'manifest.json'
if target.exists(): assert json.loads(target.read_bytes()) == manifest
else: target.write_text(json.dumps(manifest,ensure_ascii=False,indent=2)+'\n',encoding='utf-8')
print(json.dumps({'candidate':NAME,'sha256':sha(raw),'bytes':len(raw),'roots':len(names),
    'retained_B2_bytes':len(b2),'shipped_prefix_bytes':len(prefix),'status':'PREPARED_NOT_COMPILED'}))
