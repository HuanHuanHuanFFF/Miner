"""Import a frozen complete B2 indexed-loop draft for original statement replay."""
from pathlib import Path
from datetime import datetime, timezone
import hashlib
import json

HERE = Path(__file__).resolve().parent
ROOT = HERE.parents[4]
SOURCE = ROOT / 'competitions/floatlib/candidates/f01-r15-dev-packed-b2-1/Kernel.lean'
WORKER = HERE / 'development-workers/structural-cost'
raw = (WORKER / 'Kernel-hoisted-b2.draft.lean').read_bytes()
assert hashlib.sha256(raw).hexdigest() == '9f7f96d71c153681c6a2500fd229e0627cd2ea38a3ad375afdeee25a1657eee1'
assert len(raw) == 234277 and b'\r' not in raw
base = SOURCE.read_bytes()
assert hashlib.sha256(base).hexdigest() == '622d8394a7127e93dcaf992c62c6dfcff7208d212738409a5e34525dfafd1a58'
start = b'namespace Submission.R15PackedB2\n'
end = b'end Submission.R15PackedB2\n'
assert raw.split(start)[0] == base.split(start)[0]
assert raw.split(end)[1] == base.split(end)[1]
module = HERE / 'development-helper-audit.py'
if not module.exists():
    module.write_bytes((HERE.parent / 'round11h-20261025T173831Z/development-helper-audit-v3.py').read_bytes())
name = 'f01-r19-dev-b2-index1'
candidate = ROOT / 'competitions/floatlib/candidates' / name
candidate.mkdir(exist_ok=False)
(candidate / 'Kernel.lean').write_bytes(raw)
components = []
for source_name, dest_name in [('indexed-b2.lean.inc', 'development-indexed-b2-fragment.lean.inc'),
    ('hoisted-b2-entry.lean.inc', 'development-hoisted-b2-entry.lean.inc')]:
    source = WORKER / source_name
    dest = HERE / dest_name
    with dest.open('xb') as stream:
        stream.write(source.read_bytes())
    components.append({'path': dest.relative_to(ROOT).as_posix(), 'bytes': dest.stat().st_size,
        'sha256': hashlib.sha256(dest.read_bytes()).hexdigest()})
prefix = 'Submission.R15PackedB2.'
helpers = [prefix + 'Indexed.' + s for s in ('ugetA_getD', 'ugetB_get', 'wordLoop_eq', 'within_eq', 'runDot_eq', 'row_last_lt', 'rowDot_eq')]
helpers += [prefix + s for s in ('groupWithin_eq', 'rowWithin_eq', 'output_eq', 'output_prefix', 'core_eq_reference')]
helpers += ['Submission.' + op + '_spec' for op in ('add', 'mul', 'sum', 'bmm')]
manifest = {'candidate': name, 'candidate_file': 'Kernel.lean', 'candidate_sha256': hashlib.sha256(raw).hexdigest(),
    'candidate_bytes': len(raw), 'created_at_utc': datetime.now(timezone.utc).isoformat(),
    'parent': 'f01-r15-dev-packed-b2-1', 'parent_sha256': hashlib.sha256(base).hexdigest(),
    'components': components, 'mechanism': 'Raw-A USize/uget pair loop; shape bounds hoisted once per output; existing B2 preparation, arithmetic order, finish and fallback preserved; no new A allocation',
    'validation_mode': 'statement-only', 'proof_status': 'NOT_COMPILED', 'performance': 'NOT_RUN',
    'explicit_helper_audit': helpers, 'helper_audit_expected_count': len(helpers),
    'helper_audit_source_sha256': hashlib.sha256(raw).hexdigest(),
    'helper_audit_required_endpoints': ['Submission.bmm_spec', prefix + 'Indexed.wordLoop_eq'],
    'helper_audit_module': module.name, 'helper_audit_module_sha256': hashlib.sha256(module.read_bytes()).hexdigest()}
(candidate / 'manifest.json').write_bytes((json.dumps(manifest, ensure_ascii=False, indent=2) + '\n').encode())
print(json.dumps({'candidate': name, 'sha256': manifest['candidate_sha256'], 'bytes': len(raw), 'roots': len(helpers)}))
