"""Read current official source metadata and raw scoring documentation/code."""
from pathlib import Path
from datetime import datetime, timezone
import hashlib, json, requests

ROOT = Path(__file__).resolve().parents[1]
E = ROOT / 'evidence/round24/official-rules-start'
E.mkdir(exist_ok=False)
session = requests.Session()
records = []
def get(url, filename):
    start = datetime.now(timezone.utc).isoformat()
    r = session.get(url, timeout=40)
    (E / filename).write_bytes(r.content)
    records.append({'url': url, 'file': filename, 'request_start_utc': start,
        'request_end_utc': datetime.now(timezone.utc).isoformat(), 'status': r.status_code,
        'bytes': len(r.content), 'sha256': hashlib.sha256(r.content).hexdigest()})
    r.raise_for_status()
    return r
try:
    meta = get('https://api.github.com/repos/conjectures-io/conjectures-optimisation-deflate/commits/main', 'main-commit.response.json').json()
    revision = meta['sha']
    for path in ['docs/SCORING.md', 'docs/BENCHMARK.md', 'docs/MINER.md', 'validator/scoring/pareto.py', 'validator/scoring/combine.py']:
        get(f'https://raw.githubusercontent.com/conjectures-io/conjectures-optimisation-deflate/{revision}/{path}', path.replace('/', '--'))
    result = {'status': 'VERIFIED_CURRENT_PUBLIC_SOURCE_CAPTURE', 'commit': revision, 'files': records,
              'scope': 'Current public repository source, not proof of exact live deployment. Replay must independently match current official snapshot weights.'}
except Exception as e:
    result = {'status': 'CAPTURE_FAILED', 'error': str(e), 'files': records}
    raise
finally:
    (E / 'receipt.json').write_bytes((json.dumps(result, indent=2) + '\n').encode())
    session.close()
print(json.dumps({'commit': revision, 'files': len(records)}))
