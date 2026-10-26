"""One next diagnostic batch after both previous clean discoveries failed."""
from pathlib import Path
from datetime import datetime, timezone
import ast
import hashlib
import json
import re

here = Path(__file__).resolve().parent
root = here.parents[4]
sha = lambda data: hashlib.sha256(data).hexdigest()
save = lambda p, value: p.write_bytes((json.dumps(value, ensure_ascii=False, indent=2) + '\n').encode())
state = json.loads((root / 'competitions/floatlib/coordination/development-status.json').read_bytes())
assert state['research_round']['id'] == 'R19-20261026T194639Z' and not state['research_round']['active_ci']
for name in ('f01-r19-dev-jam17-public1', 'f01-r19-dev-b2-index-inline1'):
    result = json.loads((here / f'result-1927005-{name}-vs-f01-r15-dev-packed-b2-1.json').read_bytes())
    assert result['full_gate_both'] and not result['local_discovery_screen_passed'] and result['run'] == 40407333869
    path = root / 'competitions/floatlib/candidates' / name / 'manifest.json'
    manifest = json.loads(path.read_bytes())
    manifest.update(full_gate='PASS', performance='FIRST_D_BELOW_ADOPTION_THRESHOLD_NO_RESEED', first_discovery={
        k: result[k] for k in ('run', 'seed', 'relative_normalized_ratio', 'gain_p05', 'per_operation_normalized', 'local_discovery_screen_passed')})
    save(path, manifest)

# Earlier v5 was not executed; keep its initial exact digest in the receipt.
helper = here / 'development-helper-audit-v5.py'
helper_hash = sha(helper.read_bytes())
probe_path = root / 'competitions/floatlib/candidates/f01-r19-dev-direct-bias-probe1/manifest.json'
probe = json.loads(probe_path.read_bytes())
old_v5_hash = probe['helper_audit_module_sha256']
probe['helper_audit_module_sha256'] = helper_hash
probe['execution_status'] = 'READY_STATEMENT_ONLY_AFTER_EXECUTION_BINDING_UPDATE'
save(probe_path, probe)

matrix_dir = here / 'astra-workers/matrix-structure/dual-temporal-frontier'
matrix = json.loads((matrix_dir / 'build-receipt.json').read_bytes())
compact_dir = here / 'astra-workers/runtime-representation'
public_roots = ['Submission.' + op + '_spec' for op in ('add', 'mul', 'sum', 'bmm')]
compact_roots = public_roots + re.findall(r'^#print axioms (\S+)', (compact_dir / 'HelperAudit-compact-scales.lean.inc').read_text('utf-8'), re.M)
sources = [
    ('f01-r19-dev-dual-temporal-a4-1', matrix_dir / matrix['source'],
     '9a5f19bea40d607de2e491aa45ab2deaac8fb68ea34a939817380eb7b362f4de',
     'f01-r19-dev-temporal-b2-1', matrix['explicit_helper_roots'],
     'One flat A4 temporal input cache coupled to accepted c70c B8, ordered two-chain MAC and original finish/replay; 3<=p<=8,n>1,m>=4; all preparation and destruction charged', []),
    ('f01-r19-dev-compact-scales1', compact_dir / 'Kernel-compact-scales.lean',
     '9c4e9505702231fdb93f47f8d767ba0b2b0c2ad7ec48d8894b5a53ba87657645',
     'f01-r15-dev-packed-b2-1', compact_roots,
     'Once-checked fixed512-entry FloatArray scale table, compact double loads plus narrowing, original live fallback; not input preprocessing',
     ['R19CompactScales.valid', 'R19CompactScales.packed.size']),
]
created = []
for name, source, expected, parent, roots, mechanism, evaluations in sources:
    raw = source.read_bytes()
    assert sha(raw) == expected and len(raw) <= 256000 and b'\r' not in raw
    assert len(roots) == len(set(roots)) and set(public_roots) <= set(roots)
    assert all(re.fullmatch(r'(?:Submission|R19CompactScales)\.[A-Za-z0-9_.]+', value) for value in roots)
    target = root / 'competitions/floatlib/candidates' / name
    target.mkdir(exist_ok=False)
    (target / 'Kernel.lean').write_bytes(raw)
    parent_kernel = root / 'competitions/floatlib/candidates' / parent / 'Kernel.lean'
    manifest = {
        'candidate': name, 'candidate_file': 'Kernel.lean', 'candidate_sha256': expected, 'candidate_bytes': len(raw),
        'created_at_utc': datetime.now(timezone.utc).isoformat(), 'parent': parent, 'parent_sha256': sha(parent_kernel.read_bytes()),
        'mechanism': mechanism, 'validation_mode': 'statement-only', 'proof_status': 'NOT_RUN', 'performance': 'NOT_RUN',
        'explicit_helper_audit': roots, 'helper_audit_expected_count': len(roots), 'helper_audit_source_sha256': expected,
        'helper_audit_required_endpoints': ['Submission.bmm_spec', roots[0]],
        'helper_audit_module': helper.name, 'helper_audit_module_sha256': helper_hash,
        'diagnostic_evaluations': evaluations, 'source_producer_path': source.relative_to(root).as_posix(),
        'source_producer_sha256': expected, 'formal_submission': 'NOT_SUBMITTED',
    }
    save(target / 'manifest.json', manifest)
    created.append({'candidate': name, 'sha256': expected, 'bytes': len(raw), 'helper_roots': len(roots), 'diagnostic_evaluations': evaluations})

diagnostic = root / 'competitions/floatlib/candidates/f01-word-tensors/ci-diagnostics.py'
old = diagnostic.read_bytes()
new = old
for before, after in [
    (b"or 'R19Temporal' in name)", b"or 'R19Temporal' in name or 'R19DualTemporal' in name)"),
    (b"'lp_competition_Submission_R19Jam17_diagnosticEntry',", b"'lp_competition_Submission_R19Jam17_diagnosticEntry','lp_competition_Submission_R19DirectBias_normalCore','lp_competition_Submission_R19DirectBias_diagnosticEntry',"),
    (b"('development-helper-audit.py', 'development-helper-audit-v4.py')", b"('development-helper-audit.py', 'development-helper-audit-v4.py', 'development-helper-audit-v5.py')"),
]:
    assert new.count(before) == 1, before
    new = new.replace(before, after)
tree = ast.parse(new)
embedded = [node.value.value for node in ast.walk(tree) if isinstance(node, ast.Assign) and any(isinstance(t, ast.Name) and t.id == 'code' for t in node.targets)]
assert len(embedded) == 1
ast.parse(embedded[0])
ast.parse(helper.read_bytes())
diagnostic.write_bytes(new)
save(here / 'development-next-diagnostic-binding.json', {
    'at_utc': datetime.now(timezone.utc).isoformat(), 'previous_discovery_run': 40407333869,
    'previous_discovery_candidates_both_failed': True, 'created': created,
    'helper_v5_initial_unexecuted_sha256': old_v5_hash, 'helper_v5_sha256': helper_hash,
    'diagnostic_path': diagnostic.relative_to(root).as_posix(), 'old_sha256': sha(old), 'new_sha256': sha(new),
    'change': 'Diagnostic object symbol selection and explicit helper v5 binding only; original official gate/contracts/compiler flags/adoption thresholds unchanged',
    'syntax': 'outer and embedded Python parsed', 'no_confirmation_cohort_changed': True,
})
print(json.dumps({'created': created, 'probe': probe['candidate'], 'diagnostic_sha256': sha(new)}))
