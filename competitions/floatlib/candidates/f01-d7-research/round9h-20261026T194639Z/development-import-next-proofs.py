from pathlib import Path
from datetime import datetime, timezone
import hashlib
import json
import re

HERE = Path(__file__).resolve().parent
ROOT = HERE.parents[4]
sha = lambda raw: hashlib.sha256(raw).hexdigest()
save = lambda p, x: p.write_bytes((json.dumps(x, ensure_ascii=False, indent=2) + '\n').encode())
module = HERE / 'development-helper-audit-v4.py'
old_module = module.read_text('utf-8')
assert 'R19Base' not in old_module
module.write_bytes(old_module.replace('|R19CompactScales)', '|R19CompactScales|R19Base)').encode())
eager_path = ROOT / 'competitions/floatlib/candidates/f01-r19-dev-eager-classifier1/manifest.json'
eager = json.loads(eager_path.read_bytes())
eager['helper_audit_module_sha256'] = sha(module.read_bytes())
save(eager_path, eager)
public = ['Submission.' + op + '_spec' for op in ('add', 'mul', 'sum', 'bmm')]
probe_parent = ROOT / 'competitions/floatlib/candidates/f01-r19-dev-jam17-probe1/manifest.json'
probe_roots = json.loads(probe_parent.read_bytes())['explicit_helper_audit']
public_roots = re.findall(r'^#print axioms (\S+)', (HERE / 'astra-workers/exact-arithmetic/HelperAudit-public-jam17.lean.inc').read_text('utf-8'), re.M)
assert len(public_roots) == len(set(public_roots)) == 40
index_parent = ROOT / 'competitions/floatlib/candidates/f01-r19-dev-b2-index1/manifest.json'
index_roots = json.loads(index_parent.read_bytes())['explicit_helper_audit']
sources = [
    ('f01-r19-dev-jam17-probe2', HERE / 'astra-workers/exact-arithmetic/repair1/Probe-jam17-repair1.lean',
     '12341d5b5ddaa82e234a6da3ac1868a59634c9d99d6f6c621d4ee413a315b182', 'f01-r19-dev-jam17-probe1', probe_roots,
     'Proof-only repair of actual403954 parity/BEq andUInt64toNat0 goals; original guard and runtime unchanged; separately named diagnostic caller'),
    ('f01-r19-dev-jam17-public1', HERE / 'astra-workers/exact-arithmetic/repair1/Kernel-jam17-public-repair1-parser.lean',
     'b2710197d387bb22c4f0395f24d39543299965867b95cabb6965ce3df48f4bff', 'f01-r19-dev-jam17-probe2', public_roots,
     'Complete guarded jam17 UInt32 native-roundtrip public MUL, original4 public operations/spec shapes; original ordered fallback'),
    ('f01-r19-dev-b2-index-inline1', HERE / 'development-workers/structural-cost/Kernel-index-inline-convert.draft.lean',
     'f84ea2dbffbf0406f453bbc20b4335288ba5d77bb787ae33db203665016ac384', 'f01-r19-dev-b2-index1', index_roots,
     'Only indexed-loop A conversion uses existing all-input-proved R2W01b.convert; old low-domain foreign fallback, B packing, shape/word guards and ordered finish unchanged')]
results = []
for name, source, expected, parent, roots, mechanism in sources:
    raw = source.read_bytes()
    assert sha(raw) == expected and len(raw) <= 256000 and b'\r' not in raw
    assert len(roots) == len(set(roots)) and set(public) <= set(roots)
    target = ROOT / 'competitions/floatlib/candidates' / name
    target.mkdir(exist_ok=False)
    (target / 'Kernel.lean').write_bytes(raw)
    parent_kernel = ROOT / 'competitions/floatlib/candidates' / parent / 'Kernel.lean'
    manifest = {'candidate': name, 'candidate_file': 'Kernel.lean', 'candidate_sha256': expected, 'candidate_bytes': len(raw),
        'created_at_utc': datetime.now(timezone.utc).isoformat(), 'parent': parent, 'parent_sha256': sha(parent_kernel.read_bytes()),
        'mechanism': mechanism, 'validation_mode': 'statement-only', 'proof_status': 'NOT_COMPILED', 'performance': 'NOT_RUN',
        'explicit_helper_audit': roots, 'helper_audit_expected_count': len(roots), 'helper_audit_source_sha256': expected,
        'helper_audit_required_endpoints': ['Submission.bmm_spec', roots[0]],
        'helper_audit_module': module.name, 'helper_audit_module_sha256': sha(module.read_bytes()),
        'source_producer_path': source.relative_to(ROOT).as_posix(), 'source_producer_sha256': expected}
    save(target / 'manifest.json', manifest)
    results.append({'candidate': name, 'sha256': expected, 'bytes': len(raw), 'roots': len(roots)})
for name in ('f01-r19-dev-b2-index1', 'f01-r19-dev-temporal-b2-1'):
    result = json.loads((HERE / f'result-1927003-{name}-vs-f01-r15-dev-packed-b2-1.json').read_bytes())
    assert result['full_gate_both'] and not result['local_discovery_screen_passed']
    path = ROOT / 'competitions/floatlib/candidates' / name / 'manifest.json'
    manifest = json.loads(path.read_bytes())
    manifest.update(full_gate='PASS', performance='FIRST_D_BELOW_ADOPTION_THRESHOLD_NO_RESEED', first_discovery={
        k: result[k] for k in ('run', 'seed', 'relative_normalized_ratio', 'gain_p05', 'per_operation_normalized', 'local_discovery_screen_passed')})
    save(path, manifest)
save(HERE / 'development-next-proofs-import.json', {'at_utc': datetime.now(timezone.utc).isoformat(), 'sources': results,
    'audit_module_change': 'UnexecutedR19v4 now permits exactR19Base public carrier namespace; standard3/source binding/cardinality checks unchanged'})
print(json.dumps(results))
