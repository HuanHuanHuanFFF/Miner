from pathlib import Path
from datetime import datetime, timezone
import hashlib
import json
import os

here = Path(__file__).resolve().parent
root = here.parents[4]
sha = lambda data: hashlib.sha256(data).hexdigest()
read = lambda p: json.loads(p.read_bytes())
save = lambda p, value: p.write_bytes((json.dumps(value, ensure_ascii=False, indent=2) + '\n').encode())
result = read(here / 'result-1927008-f01-r19-dev-compact-scales1-vs-f01-r15-dev-packed-b2-1.json')
assert result['run'] == 40417039536 and result['full_gate_both'] and not result['local_discovery_screen_passed']
path = root / 'competitions/floatlib/candidates/f01-r19-dev-compact-scales1/manifest.json'
manifest = read(path)
manifest.update(full_gate='PASS', performance='FIRST_D_BELOW_ADOPTION_THRESHOLD_NO_RESEED', first_discovery={
    key: result[key] for key in ('run', 'seed', 'relative_normalized_ratio', 'gain_p05', 'per_operation_normalized', 'local_discovery_screen_passed')})
save(path, manifest)
runtime = here / 'astra-direct-bias-runtime-only.lean'
runtime_meta = read(here / 'astra-direct-bias-runtime-only.json')
matrix_dir = here / 'astra-workers/matrix-structure/dual-temporal-frontier/proof2'
repair = read(matrix_dir / 'repair-receipt.json')
assert repair['runtime_and_domain_and_all_theorem_statements_byte_identical'] and repair['inverse_to_failed_9a5']
module = here / 'development-helper-audit-v5.py'
public = ['Submission.' + op + '_spec' for op in ('add', 'mul', 'sum', 'bmm')]
entries = [
    ('f01-r19-dev-direct-bias-runtime1', runtime,
     '74899988939a056a40675aefe8c63f2f9db1c7b4728f3d496bf140ede6ad85dc',
     'f01-r15-dev-packed-b2-1', public + ['Submission.R19DirectBias.normalCore', 'Submission.R19DirectBias.guardedMul', 'Submission.R19DirectBias.diagnosticEntry'],
     'Exact1180 direct-bias runtime tail on unchangedB2, omitting all new proof sections to discriminate actual caller costs before expensive proof; public operations remainB2'),
    ('f01-r19-dev-dual-temporal-a4-2', matrix_dir / 'Kernel-dual-temporal-a4-proof2.lean',
     'd765bd41234a26640eaa6df6c7134e0d4d8dca760e50eaef3aa82eff1fac0847',
     'f01-r19-dev-dual-temporal-a4-1', repair['explicit_helper_roots'],
     'Proof-only repair of loop equation unfolding and final group definitional equality; original9a5 runtime, domain, flatA4/B8 layout and all theorem statements unchanged'),
]
records = []
for name, source, expected, parent, roots, mechanism in entries:
    raw = source.read_bytes()
    assert sha(raw) == expected and len(raw) <= 256000 and b'\r' not in raw
    assert len(roots) == len(set(roots)) and set(public) <= set(roots)
    folder = root / 'competitions/floatlib/candidates' / name
    folder.mkdir(exist_ok=False)
    (folder / 'Kernel.lean').write_bytes(raw)
    parent_source = root / 'competitions/floatlib/candidates' / parent / 'Kernel.lean'
    manifest = {
        'candidate': name, 'candidate_file': 'Kernel.lean', 'candidate_sha256': expected, 'candidate_bytes': len(raw),
        'created_at_utc': datetime.now(timezone.utc).isoformat(), 'parent': parent, 'parent_sha256': sha(parent_source.read_bytes()),
        'mechanism': mechanism, 'validation_mode': 'statement-only', 'proof_status': 'NOT_RUN', 'performance': 'NOT_RUN',
        'explicit_helper_audit': roots, 'helper_audit_expected_count': len(roots), 'helper_audit_source_sha256': expected,
        'helper_audit_required_endpoints': ['Submission.bmm_spec', roots[-1]],
        'helper_audit_module': module.name, 'helper_audit_module_sha256': sha(module.read_bytes()),
        'source_producer_path': source.relative_to(root).as_posix(), 'source_producer_sha256': expected,
        'formal_submission': 'NOT_SUBMITTED',
    }
    save(folder / 'manifest.json', manifest)
    records.append({'candidate': name, 'sha256': expected, 'bytes': len(raw), 'roots': len(roots)})
save(here / 'development-runtime-dual2-import.json', {
    'at_utc': datetime.now(timezone.utc).isoformat(), 'sources': records,
    'runtime_producer_manifest_sha256': sha((here / 'astra-direct-bias-runtime-only.json').read_bytes()),
    'matrix_repair_receipt_sha256': sha((matrix_dir / 'repair-receipt.json').read_bytes()),
    'scope': 'First exact diagnostic build, not scored/adopted. Runtime-only output is not a new public MUL proof; old proof/performance failures retained.',
})
state_path = root / 'competitions/floatlib/coordination/development-status.json'
state_raw = state_path.read_bytes()
state = json.loads(state_raw)
assert state['research_round']['id'] == 'R19-20261026T194639Z' and not state['research_round']['active_ci']
state['collaboration']['research_latest_self_reported_window'] = {
    'start_utc': '2026-10-26T22:58:21Z', 'deadline_utc': '2026-10-27T02:28:21Z', 'budget_minutes': 210,
    'receipt': '20261026T230600000Z-r-latest-direct-3h30-window.md', 'scope': 'R latest direct window; does not change D9h or peer6h window'}
state['research_round'].setdefault('allocation_decisions', []).append({
    'at_utc': datetime.now(timezone.utc).isoformat(),
    'decision': 'Compact9c4e firstD1.029671 with negativep05 parked; next validate proof2 dual cache and exact runtime-only DirectBias while minimal independent-process resource controls are prepared',
    'basis': '40417039536 original three full gates pass. Scalar table representation cost premise held but complete cost lost; no reseed or confirmation.',
    'used_tokens': 'UNKNOWN', 'cached_input_tokens': 'UNKNOWN', 'CI': 'standard public single slot; no local Lean',
})
state['updated_at_utc'] = datetime.now(timezone.utc).isoformat()
tmp = state_path.with_name('development-status-runtime-dual.tmp')
assert not tmp.exists()
tmp.write_bytes((json.dumps(state, ensure_ascii=False, indent=2) + '\n').encode())
assert state_path.read_bytes() == state_raw
os.replace(tmp, state_path)
print(json.dumps(records))
