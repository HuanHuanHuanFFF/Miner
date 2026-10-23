"""Record exact local runtime sources after the scheduled R7 source freeze."""
from datetime import datetime, timezone
import hashlib
import json
from pathlib import Path
import subprocess

ROOT = Path(__file__).resolve().parents[4]
HERE = Path(__file__).resolve().parent
SCHEDULED = datetime.fromisoformat('2026-10-23T02:45:00+00:00')
now = datetime.now(timezone.utc)
assert now >= SCHEDULED, 'Do not record a future freeze as an actual event'
target = HERE / 'source-freeze.json'
assert not target.exists(), 'Preserve the existing freeze receipt'
assert subprocess.check_output(['git', 'branch', '--show-current'], cwd=ROOT, text=True).strip() == 'codex/multi-track-floatlib'

def record(path):
    raw = path.read_bytes()
    return {'path': path.relative_to(ROOT).as_posix(), 'bytes': len(raw),
            'sha256': hashlib.sha256(raw).hexdigest()}

sources = []
for kernel in sorted((ROOT / 'competitions/floatlib/candidates').glob('*/Kernel.lean')):
    row = record(kernel)
    manifest = kernel.with_name('manifest.json')
    if manifest.is_file():
        data = json.loads(manifest.read_bytes())
        assert data['candidate_sha256'] == row['sha256'], kernel
        assert data.get('candidate_bytes', row['bytes']) == row['bytes'], kernel
        row['manifest'] = record(manifest)
    sources.append(row)
assert len(sources) == 190, len(sources)
by_name = {Path(r['path']).parent.name: r for r in sources}
assert by_name['f01-d7-direct-singlepass']['sha256'] == 'cc06a47faf9f982c324d265c90beb2b9cea953f33773eabed3ed6eab29260dfc'
assert by_name['f01-d7-direct-nonnan']['sha256'] == '60f74aa4af01a9b35ece66a7c310e6b05b5b84b9b7121a4cccd12a0a9c987e15'
protected_names = [
    'competitions/floatlib/pins.json',
    'competitions/floatlib/references/official-incumbent/Kernel.lean',
    'competitions/floatlib/candidates/f01-d7-public-suite/suite-plan.json',
    'competitions/floatlib/candidates/f01-d7-research/public-suite.py',
    'competitions/floatlib/candidates/f01-d7-research/capture-codegen.py',
    'competitions/floatlib/candidates/f01-d7-research/official-policy/gate-4b7e838.raw',
    'competitions/floatlib/candidates/f01-mul-log2-proof1/ci.py',
    'competitions/floatlib/scripts/run-gates.py',
    'competitions/floatlib/scripts/ci-prepare.sh',
    'competitions/floatlib/scripts/ci-setup.sh',
    'competitions/floatlib/scripts/ci-validate.sh',
    '.github/workflows/floatlib-validate.yml',
]
result = {
    'recorded_at_utc': now.isoformat(), 'scheduled_source_freeze_utc': SCHEDULED.isoformat(),
    'research_deadline_utc': '2026-10-23T04:22:17Z',
    'state': 'RUNTIME_SOURCES_FROZEN_CONTINUING_EVIDENCE_AND_AUTHORIZED_VALIDATION',
    'head_at_record': subprocess.check_output(['git', 'rev-parse', 'HEAD'], cwd=ROOT, text=True).strip(),
    'retained_candidate': 'f01-d7-direct-nonnan',
    'retained_full_gate_runs': [39840672791, 39847080316],
    'new_runtime_acceptance': 'NOT_RUN_FOR_NEW_LOCAL_INTEGRATIONS; static source freeze is not acceptance',
    'public_push_authorization': 'AWAITING_EXISTING_HUMAN_QUESTION_AFTER_AUTOMATIC_REVIEW_REJECTION',
    'active_ci_at_last_readonly_snapshot': [],
    'ci_observed_at_utc': '2026-10-23T02:35:25.798772+00:00',
    'ci_readonly_receipt': record(ROOT / '.local-maintenance/r7-20261023/ci-readonly-20261023T023525Z.json'),
    'prepared_810_dispatch': 'NOT_DISPATCHED',
    'candidate_source_count': len(sources), 'sources': sources,
    'supporting_files': [record(ROOT / p) for p in protected_names],
    'boundary': 'Byte and identity snapshot only. Documentation, source reviews and evidence recovery may continue. A later source repair requires an explicit new identity and freeze receipt; no result is inherited from this snapshot.',
}
with target.open('x', encoding='utf8') as stream:
    stream.write(json.dumps(result, ensure_ascii=False, indent=2)+'\n')
print(json.dumps({'recorded_at_utc': result['recorded_at_utc'], 'candidate_source_count': len(sources),
                  'supporting_files': len(protected_names), 'receipt_sha256': record(target)['sha256']}))
