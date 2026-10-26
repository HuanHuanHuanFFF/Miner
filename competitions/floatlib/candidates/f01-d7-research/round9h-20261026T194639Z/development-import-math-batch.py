"""Freeze three independent research sources and correct one audit-list typo."""
from pathlib import Path
from datetime import datetime, timezone
import hashlib
import json
import re
import subprocess

HERE = Path(__file__).resolve().parent
ROOT = HERE.parents[4]
sha = lambda raw: hashlib.sha256(raw).hexdigest()
save = lambda p, x: p.write_bytes((json.dumps(x, ensure_ascii=False, indent=2) + '\n').encode())
module = HERE / 'development-helper-audit.py'
public = ['Submission.' + op + '_spec' for op in ('add', 'mul', 'sum', 'bmm')]
manifest_path = ROOT / 'competitions/floatlib/candidates/f01-r19-dev-b2-index1/manifest.json'
old = manifest_path.read_bytes()
assert old == subprocess.check_output(['git', 'show', '454d9d23d836b211d99fefad27ef9d4845defdb2:' + manifest_path.relative_to(ROOT).as_posix()], cwd=ROOT)
m = json.loads(old)
unused = 'Submission.R15PackedB2.Indexed.runDot_eq'
assert unused in m['explicit_helper_audit']
kernel = manifest_path.parent / 'Kernel.lean'
indexed_scope = kernel.read_text('utf-8').split('namespace Submission.R15PackedB2\n', 1)[1].split('end Submission.R15PackedB2', 1)[0]
assert not re.search(r'^(?:theorem|def) runDot_eq\b', indexed_scope, re.M)
m['explicit_helper_audit'].remove(unused)
m['helper_audit_expected_count'] = len(m['explicit_helper_audit'])
m.update(proof_status='STATEMENT_AND_WHOLE_MODULE_REPLAY_PASS_AUDIT_LIST_REPAIR_PENDING',
    statement_run=40392789163, helper_audit_metadata_repair='Removed nonexistent unused prototype runDot_eq; exact Kernel bytes unchanged')
save(manifest_path, m)
save(HERE / 'development-index-audit-list-repair.json', {'at_utc': datetime.now(timezone.utc).isoformat(),
    'original_commit': '454d9d23d836b211d99fefad27ef9d4845defdb2', 'old_manifest_sha256': sha(old),
    'new_manifest_sha256': sha(manifest_path.read_bytes()), 'kernel_sha256_unchanged': sha(kernel.read_bytes()),
    'removed_nonexistent_name': unused, 'remaining_actual_roots': len(m['explicit_helper_audit']),
    'original_failure_preserved': 40392789163})
jam = json.loads((HERE / 'astra-workers/exact-arithmetic/probe-manifest.json').read_bytes())
runtime = json.loads((HERE / 'astra-workers/runtime-representation/helper-roots.json').read_bytes())
sources = [
    ('f01-r19-dev-jam17-probe1', 'exact-arithmetic/Probe-jam17-v1.lean',
     'f78490eb6a2c2aa7a8b68ebdf54c43d68a39c8bd3bea43e9ee462bcc3cd68679',
     'f01-r17-dev-u32-roundtrip-repair2', jam['helper_roots'] + ['Submission.R19Jam17.diagnosticEntry'] + public,
     ['exact-arithmetic/Jam17.lean.inc'], 'Jammed48-to31-bit product then UInt32 native roundtrip; separately guarded diagnostic caller, public operations remain B2'),
    ('f01-r19-dev-temporal-b2-1', 'matrix-structure/Kernel-temporal-b2.lean',
     'c70cf9479ca48b4690990ebbd0b3781139cbeb94e46b28bbe61563e3eeaced1c',
     'f01-r15-dev-packed-b2-1', ['Submission.R19Temporal.' + n for n in ('pack_get', 'loop_eq', 'packB_get', 'group_eq', 'row_eq', 'output_eq', 'output_prefix', 'core_eq_reference', 'dispatch_spec')] + public,
     ['matrix-structure/Temporal.lean.inc'], 'One native8 record per4 k positions, two original ordered chains, exact tail and raw replay; complete public BMM caller'),
    ('f01-r19-dev-eager-classifier1', 'runtime-representation/Kernel-eager-classifier.lean',
     'cc9268820d3c9b3c4e664d6a659a12ef259c7c8443db61980a686cad974ea5a5',
     'f01-r15-dev-packed-b2-1', ['Submission.' + n for n in runtime['explicit_new_helper_roots']['classifier']] + public,
     ['runtime-representation/Classifier-bridge.lean.inc'], 'Same accepted scalar domain with eager Boolean equality in place of short-circuit conjunction; all native codecs and fallback unchanged')]
results = []
for name, source, expected, parent, roots, fragments, mechanism in sources:
    raw = (HERE / 'astra-workers' / source).read_bytes()
    assert sha(raw) == expected and len(raw) <= 256000 and b'\r' not in raw
    assert len(roots) == len(set(roots))
    text = raw.decode()
    for full in roots:
        assert re.search(r'^(?:@\[[^\n]*\]\s*)?(?:theorem|lemma|def|abbrev)\s+' + re.escape(full.split('.')[-1]) + r'\b', text, re.M), full
    candidate = ROOT / 'competitions/floatlib/candidates' / name
    candidate.mkdir(exist_ok=False)
    (candidate / 'Kernel.lean').write_bytes(raw)
    components = []
    for i, fragment in enumerate(fragments, 1):
        data = (HERE / 'astra-workers' / fragment).read_bytes()
        dest = HERE / ('development-' + name.removeprefix('f01-r19-dev-') + f'-fragment{i}.lean.inc')
        with dest.open('xb') as stream:
            stream.write(data)
        components.append({'path': dest.relative_to(ROOT).as_posix(), 'sha256': sha(data), 'bytes': len(data)})
    parent_path = ROOT / 'competitions/floatlib/candidates' / parent / 'Kernel.lean'
    manifest = {'candidate': name, 'candidate_file': 'Kernel.lean', 'candidate_sha256': sha(raw), 'candidate_bytes': len(raw),
        'parent': parent, 'parent_sha256': sha(parent_path.read_bytes()), 'created_at_utc': datetime.now(timezone.utc).isoformat(),
        'components': components, 'mechanism': mechanism, 'validation_mode': 'statement-only',
        'proof_status': 'NOT_COMPILED', 'performance': 'NOT_RUN', 'explicit_helper_audit': roots,
        'helper_audit_expected_count': len(roots), 'helper_audit_source_sha256': sha(raw),
        'helper_audit_required_endpoints': [roots[0], 'Submission.bmm_spec'],
        'helper_audit_module': module.name, 'helper_audit_module_sha256': sha(module.read_bytes())}
    save(candidate / 'manifest.json', manifest)
    results.append({'candidate': name, 'sha256': sha(raw), 'bytes': len(raw), 'roots': len(roots)})
save(HERE / 'development-math-batch-import.json', {'at_utc': datetime.now(timezone.utc).isoformat(), 'sources': results})
print(json.dumps(results))
