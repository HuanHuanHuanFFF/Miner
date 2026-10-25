"""Link exact collected statement receipts and original compiler failures."""
from pathlib import Path
from datetime import datetime, timezone
import argparse
import hashlib
import json

OUT = Path(__file__).resolve().parent
ROOT = OUT.parents[4]
parser = argparse.ArgumentParser(description=__doc__)
parser.add_argument('--run', type=int, required=True)
args = parser.parse_args()
base = ROOT / 'competitions/floatlib/candidates/f01-mul-log2-proof1/ci-runs' / str(args.run)
meta = json.loads((base / 'ci-run.json').read_bytes())
assert meta['status'] == 'completed'
index = json.loads((base / 'original-artifact-hashes.json').read_bytes())
stage = base / index['directory']
for relative, record in index['files'].items():
    data = (stage / relative).read_bytes()
    assert len(data) == record['bytes'] and hashlib.sha256(data).hexdigest() == record['sha256']
folder = stage / 'diagnostics/f01-d7-public-suite/public-suite'
summary = json.loads((folder / 'summary.json').read_bytes())
assert summary['source_commit'] == meta['headSha']
rows = []
for row in summary['results']:
    assert row['validation_mode'] == 'statement-only'
    original = folder / row['verdict']
    assert hashlib.sha256(original.read_bytes()).hexdigest() == row['verdict_sha256']
    result = {key: row.get(key) for key in ('candidate', 'kernel_sha256', 'statement_pass', 'stage', 'reason', 'full_gate')}
    result.update(run=args.run, source_commit=meta['headSha'], verdict=original.relative_to(ROOT).as_posix(),
                  verdict_sha256=row['verdict_sha256'], kernel_replay_and_helper_axiom_audit='NOT_RUN')
    output = folder / 'diagnostics' / row['candidate'] / 'full-build-output.txt'
    if output.exists():
        data = output.read_bytes()
        lines = data.decode('utf-8', errors='replace').splitlines()
        result.update(compiler_output=output.relative_to(ROOT).as_posix(), compiler_output_sha256=hashlib.sha256(data).hexdigest(),
                      compiler_errors=['\n'.join(lines[i:i + 4]) for i, line in enumerate(lines) if line.startswith('error:')])
    rows.append(result)
    (OUT / f'development-proof-{row["candidate"]}-{args.run}.json').write_bytes((json.dumps(result, ensure_ascii=False, indent=2) + '\n').encode())
result = dict(run=args.run, source_commit=meta['headSha'], rows=rows,
              original_artifact_files_verified=len(index['files']), at_utc=datetime.now(timezone.utc).isoformat(),
              scope='Original statement/build diagnostics only; unused helper axiom audit, independent kernel replay, full gate and performance remain NOT_RUN.')
(OUT / f'development-proof-batch-{args.run}.json').write_bytes((json.dumps(result, ensure_ascii=False, indent=2) + '\n').encode())
print(json.dumps({key: value for key, value in result.items() if key != 'rows'}))
print(json.dumps([{key: row[key] for key in ('candidate', 'kernel_sha256', 'statement_pass', 'reason')} for row in rows]))
