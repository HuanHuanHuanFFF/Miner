"""Hash the latest complete text/data receipt per round4 run, without modifying it."""
from datetime import datetime, timezone
import hashlib
import json
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
BASE = ROOT / 'evidence/round4'


def main():
    runs = []
    allowed = {'.json', '.jsonl', '.txt', '.log', '.rs', '.lean', '.bin', '.csv'}
    for run in sorted(BASE.iterdir()):
        if not run.is_dir() or not run.name.isdecimal():
            continue
        directory = next((run / phase for phase in ('gate', 'refine', 'screen')
                          if (run / phase / 'analysis.json').is_file()), None)
        if directory is None:
            continue
        state = json.loads((directory / 'state.json').read_text())
        ci = json.loads((directory / 'ci-run.json').read_text())
        assert state['run_id'] == run.name and state['git_sha'] == ci['headSha']
        files = []
        for path in sorted(directory.rglob('*')):
            if not path.is_file():
                continue
            assert not path.is_symlink() and path.resolve().is_relative_to(BASE.resolve())
            assert path.suffix in allowed, path
            data = path.read_bytes()
            files.append({'path': path.relative_to(ROOT).as_posix(), 'bytes': len(data),
                          'sha256': hashlib.sha256(data).hexdigest()})
        runs.append({'run_id': run.name, 'directory': directory.relative_to(ROOT).as_posix(),
                     'uploaded_phase': directory.name, 'completed_state_phase': state['phase'],
                     'head_sha': ci['headSha'], 'ci_status': ci['status'], 'ci_conclusion': ci['conclusion'],
                     'measurement_processes': len(state['metrics']), 'files': files})
    result = {'checked_at_utc': datetime.now(timezone.utc).isoformat(),
              'scope': 'One latest complete receipt per run; source/proof, raw measurements, diagnostic text and synthetic inputs only. A cancelled gate upload may contain a completed refine state.',
              'file_count': sum(len(r['files']) for r in runs),
              'bytes': sum(f['bytes'] for r in runs for f in r['files']), 'runs': runs}
    (BASE / 'receipt-manifest.json').write_text(json.dumps(result, indent=2) + '\n')
    print('INVENTORIED', len(runs), 'runs', result['file_count'], 'files', result['bytes'], 'bytes')


if __name__ == '__main__':
    main()
