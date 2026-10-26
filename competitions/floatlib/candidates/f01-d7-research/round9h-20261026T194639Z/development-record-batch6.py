from pathlib import Path
from datetime import datetime, timezone
import hashlib
import json

here = Path(__file__).resolve().parent
root = here.parents[4]
read = lambda p: json.loads(p.read_bytes())
save = lambda p, value: p.write_bytes((json.dumps(value, ensure_ascii=False, indent=2) + '\n').encode())
sha = lambda p: hashlib.sha256(p.read_bytes()).hexdigest()
run = 40410895344
rows = []
for name, status in (
    ('f01-r19-dev-direct-bias-probe1', 'STATEMENT_SIGTERM_EMPTY_OUTPUT_CAUSE_UNKNOWN'),
    ('f01-r19-dev-dual-temporal-a4-1', 'STATEMENT_RECURSIVE_REWRITE_AND_FINAL_DEF_EQ_GOALS_FAILED'),
    ('f01-r19-dev-compact-scales1', 'STATEMENT_WHOLE_MODULE_AND_10_HELPERS_PASS'),
):
    proof_path = here / f'development-proof-{name}-{run}.json'
    proof = read(proof_path)
    folder = root / 'competitions/floatlib/candidates' / name
    path = folder / 'manifest.json'
    manifest = read(path)
    assert sha(folder / 'Kernel.lean') == proof['kernel_sha256'] == manifest['candidate_sha256']
    manifest.update(proof_status=status, statement_run=run, statement_evidence=proof_path.relative_to(root).as_posix(),
                    statement_evidence_sha256=sha(proof_path), performance='NOT_RUN')
    if name.endswith('compact-scales1'):
        audit_path = root / proof['extra_helper_audit']['path']
        audit = read(audit_path)
        assert sha(audit_path) == proof['extra_helper_audit']['sha256']
        assert audit['accepted'] and audit['kernel_replay'] and audit['expected_count'] == 10
        output = audit_path.parent / 'helper-axioms.raw'
        assert sha(output) == audit['output_sha256']
        assert output.read_text('utf-8').strip().splitlines()[-2:] == ['true', '512']
        manifest['activation'] = {'valid': True, 'size': 512, 'run': run, 'raw_sha256': sha(output)}
    save(path, manifest)
    rows.append({'candidate': name, 'sha256': manifest['candidate_sha256'], 'proof_status': status})
save(here / 'development-batch6-source-status.json', {'at_utc': datetime.now(timezone.utc).isoformat(), 'run': run, 'rows': rows})
print(json.dumps(rows))
