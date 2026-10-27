from pathlib import Path
from datetime import datetime, timezone
import ast
import hashlib
import json
import re

here = Path(__file__).resolve().parent
root = here.parents[4]
sha = lambda raw: hashlib.sha256(raw).hexdigest()
save = lambda p, value: p.write_bytes((json.dumps(value, ensure_ascii=False, indent=2) + '\n').encode())
base = here / 'development-helper-audit-v5.py'
helper = here / 'development-helper-audit-v7.py'
old = base.read_bytes()
assert old.count(b'|R19Base|') == 1 and not helper.exists()
new = old.replace(b'|R19Base|', b'|R19Base|R19BiasBase|')
helper.write_bytes(new)
folder = here / 'astra-workers/exact-arithmetic/bias-frontier/public-proof-review1'
roots = re.findall(r'^#print axioms (\S+)', (folder / 'HelperAudit-public-direct-bias.lean.inc').read_text('utf-8'), re.M)
assert len(roots) == len(set(roots)) == 48
prefix_run = root / 'competitions/floatlib/candidates/f01-mul-log2-proof1/ci-runs/40425497337'
index = json.loads((prefix_run / 'original-artifact-hashes.json').read_bytes())
prefix_path = prefix_run / index['directory'] / 'diagnostics/f01-d7-public-suite/public-suite/diagnostics/f01-r19-dev-prefix-isolation1/prefix-isolation/summary.json'
prefix = json.loads(prefix_path.read_bytes())
assert prefix['base_B2_audit'] == 'PASS_ORIGINAL_REPLAY_AND_FOUR_ROOTS'
assert [p['exit_code'] for p in prefix['prefixes']] == [0, 0]
matrix_parent = json.loads((root / 'competitions/floatlib/candidates/f01-r19-dev-dual-temporal-a4-2/manifest.json').read_bytes())
grs = json.loads((here / 'astra-grs-add-runtime-only.json').read_bytes())
entries = [
    ('f01-r19-dev-direct-bias-public1', folder / 'Kernel-direct-bias-public-v1.lean',
     'fa6529613fe10bd431ead1511900be989c2b80976423b31d90747f8651f37ac5', roots,
     'True public guarded DirectBias MUL connected to original all-input specification. Prefix control/quotient pass; this original wholeKernel/replay/48roots remains NOT_RUN.', helper),
    ('f01-r19-dev-dual-equation-diagnostic1', here / 'astra-workers/matrix-structure/dual-temporal-frontier/proof3-diagnostic/Kernel-dual-temporal-a4-proof3-diagnostic.lean',
     'c5981413680244f3d93d79a372a09b36dcbe22028a942b8a35fd2cd18d5f0cf7', matrix_parent['explicit_helper_audit'],
     'Expected-red first-point equation diagnostic: three trace_state calls and explicit qualified eq_def, original runtime/domain unchanged; not a repair/performance candidate.', base),
    ('f01-r19-dev-grs-add-runtime1', here / 'astra-grs-add-runtime-only.lean',
     '35347e37e2c8d593d868c80522659b4fb18bda7604fc830a9f14eb7d39be33c5', grs['roots'],
     'Normal all-sign/all-gap UInt32 GRS ADD complete diagnostic caller; public fouroperations remainB2. Cost/type discriminator only, no new publicADD proof.', base),
]
public = ['Submission.' + op + '_spec' for op in ('add', 'mul', 'sum', 'bmm')]
records = []
for name, source, expected, names, mechanism, audit in entries:
    raw = source.read_bytes()
    assert sha(raw) == expected and len(raw) <= 256000 and b'\r' not in raw
    assert len(names) == len(set(names)) and set(public) <= set(names)
    target = root / 'competitions/floatlib/candidates' / name
    target.mkdir(exist_ok=False)
    (target / 'Kernel.lean').write_bytes(raw)
    manifest = {
        'candidate': name, 'candidate_file': 'Kernel.lean', 'candidate_sha256': expected, 'candidate_bytes': len(raw),
        'created_at_utc': datetime.now(timezone.utc).isoformat(), 'validation_mode': 'statement-only', 'proof_status': 'NOT_RUN',
        'performance': 'NOT_RUN', 'mechanism': mechanism, 'explicit_helper_audit': names,
        'helper_audit_expected_count': len(names), 'helper_audit_source_sha256': expected,
        'helper_audit_required_endpoints': ['Submission.mul_spec', 'Submission.bmm_spec', names[-1]],
        'helper_audit_module': audit.name, 'helper_audit_module_sha256': sha(audit.read_bytes()),
        'source_producer_path': source.relative_to(root).as_posix(), 'source_producer_sha256': expected,
        'formal_submission': 'NOT_SUBMITTED',
    }
    if name.endswith('public1'):
        manifest['prefix_release_evidence'] = {'run': 40425497337, 'path': prefix_path.relative_to(root).as_posix(), 'sha256': sha(prefix_path.read_bytes()),
            'scope': 'Both requested small prefix processes exit0; not wholeKernel acceptance. Resource7b03 repair remains HOLD.'}
    save(target / 'manifest.json', manifest)
    records.append({'candidate': name, 'sha256': expected, 'bytes': len(raw), 'roots': len(names)})
diagnostic = root / 'competitions/floatlib/candidates/f01-word-tensors/ci-diagnostics.py'
old_diagnostic = diagnostic.read_bytes()
updated = old_diagnostic
for before, after in [
    (b"'development-helper-audit-v5.py',", b"'development-helper-audit-v5.py', 'development-helper-audit-v7.py',"),
    (b"'lp_competition_Submission_R19DirectBias_diagnosticEntry',", b"'lp_competition_Submission_R19DirectBias_diagnosticEntry','lp_competition_Submission_R19GRS32Add_alignNonzero','lp_competition_Submission_R19GRS32Add_guardedAdd','lp_competition_Submission_R19GRS32Add_diagnosticEntry',"),
]:
    assert updated.count(before) == 1
    updated = updated.replace(before, after)
tree = ast.parse(updated)
embedded = [node.value.value for node in ast.walk(tree) if isinstance(node, ast.Assign) and any(isinstance(t, ast.Name) and t.id == 'code' for t in node.targets)]
assert len(embedded) == 1
ast.parse(embedded[0]); ast.parse(new)
diagnostic.write_bytes(updated)
save(here / 'development-batch11-import.json', {
    'at_utc': datetime.now(timezone.utc).isoformat(), 'rows': records,
    'old_diagnostic_sha256': sha(old_diagnostic), 'new_diagnostic_sha256': sha(updated),
    'scope': 'Statement-only next batch after positive prefix controls; original gate/contract/bench/flags/4GiB and adoption thresholds unchanged. New helper namespace/symbol diagnostics only.',
})
print(json.dumps(records))
