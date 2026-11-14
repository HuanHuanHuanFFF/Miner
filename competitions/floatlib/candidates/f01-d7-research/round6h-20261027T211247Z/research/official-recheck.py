"""Small public-source intake. No authentication, executable, or archive handling."""
from pathlib import Path
from urllib.request import Request, urlopen
from urllib.error import HTTPError
from concurrent.futures import ThreadPoolExecutor
from datetime import datetime, timezone
import hashlib
import json
import shutil

here = Path(__file__).resolve().parent
stamp = datetime.now(timezone.utc).strftime('%Y%m%dT%H%M%SZ')
staging = Path('E:/Download/FloatLib/20261028-R22/official') / stamp
dest = here / 'official-public' / stamp
urls = {
    'champion-status': 'https://conjectures.io/v1/competitions/floatlib/submissions/323',
    'leaderboard': 'https://conjectures.io/v1/competitions/floatlib/leaderboard',
}

def fetch(item):
    label, url = item
    at = datetime.now(timezone.utc).isoformat()
    try:
        response = urlopen(Request(url, headers={'User-Agent': 'FloatLib-public-research'}), timeout=18)
        status = response.status
        raw = response.read(1024 * 1024 + 1)
    except HTTPError as error:
        status, raw = error.code, error.read(1024 * 1024 + 1)
    except Exception as error:
        return {'label': label, 'url': url, 'utc': at, 'status': 'UNKNOWN', 'error': str(error)}
    if len(raw) > 1024 * 1024:
        raise RuntimeError('Public response exceeds this small read boundary')
    file = staging / (label + '.raw')
    file.write_bytes(raw)
    return {'label': label, 'url': url, 'utc': at, 'status': status,
            'bytes': len(raw), 'file': file.name,
            'sha256': hashlib.sha256(raw).hexdigest()}

if __name__ == '__main__':
    staging.mkdir(parents=True, exist_ok=False)
    with ThreadPoolExecutor(max_workers=3) as pool:
        receipts = list(pool.map(fetch, urls.items()))
    payload = {'scope': 'Public source/status read only; old snapshot retained on failure',
               'staging': str(staging), 'downloaded_archives': 0, 'items': receipts,
               'source_route': {'state': 'KNOWN_UNSUPPORTED_NOT_REQUERIED',
                                'prior_receipt': '../20261027T212356Z/receipts.json',
                                'reason': 'Existing validator source survey records no FloatLib source route. Do not repeat a known unsupported URL as a new source search.'}}
    (staging / 'receipts.json').write_text(json.dumps(payload, indent=2) + '\n', encoding='utf-8')
    dest.mkdir(parents=True, exist_ok=False)
    for original in staging.iterdir():
        target = dest / original.name
        shutil.copyfile(original, target)
        assert original.read_bytes() == target.read_bytes()
    print(json.dumps({'branch_directory': str(dest), 'items': receipts}, indent=2))
