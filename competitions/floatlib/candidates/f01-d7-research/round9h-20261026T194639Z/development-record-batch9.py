from pathlib import Path
from datetime import datetime, timezone
import hashlib
import json

here = Path(__file__).resolve().parent
root = here.parents[4]
read = lambda p: json.loads(p.read_bytes())
save = lambda p, value: p.write_bytes((json.dumps(value, ensure_ascii=False, indent=2) + '\n').encode())
rows = []
for name, status in (
    ('f01-r19-dev-direct-bias-runtime1', 'RUNTIME_DEFINITIONS_AND_B2_PUBLIC_SPECS_REPLAYED_7_ROOTS_PUBLIC_MUL_UNCHANGED'),
    ('f01-r19-dev-dual-temporal-a4-2', 'STATEMENT_FIVE_NEW_LOOP_EQUATION_REWRITE_ERRORS'),
):
    feedback = here / f'development-proof-{name}-40420540388.json'
    report = read(feedback)
    path = root / 'competitions/floatlib/candidates' / name / 'manifest.json'
    manifest = read(path)
    assert manifest['candidate_sha256'] == report['kernel_sha256']
    assert hashlib.sha256(path.with_name('Kernel.lean').read_bytes()).hexdigest() == report['kernel_sha256']
    if name.endswith('runtime1'):
        assert report['statement_pass'] and report['extra_helper_audit']['accepted']
    else:
        assert not report['statement_pass']
    manifest.update(proof_status=status, statement_run=40420540388, statement_evidence=feedback.relative_to(root).as_posix(),
                    statement_evidence_sha256=hashlib.sha256(feedback.read_bytes()).hexdigest(), performance='NOT_RUN')
    save(path, manifest)
    rows.append({'candidate': name, 'sha256': manifest['candidate_sha256'], 'proof_status': status})
save(here / 'development-batch9-source-status.json', {'at_utc': datetime.now(timezone.utc).isoformat(), 'run': 40420540388, 'rows': rows})
print(json.dumps(rows))
