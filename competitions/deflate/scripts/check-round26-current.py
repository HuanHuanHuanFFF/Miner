"""Read only the latest official snapshot identity before final delivery."""
from pathlib import Path
from datetime import datetime, timezone
import argparse
import hashlib
import json
import requests

ROOT = Path(__file__).resolve().parents[1]
URL = 'https://conjectures.io/v1/competitions/deflate'


def main():
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument('--capture', type=Path, required=True)
    ap.add_argument('--destination', type=Path, required=True)
    a = ap.parse_args()
    expected = json.loads((a.capture / 'competition.json').read_bytes())
    dest = a.destination.resolve()
    assert dest.is_relative_to((ROOT / 'evidence/round26').resolve())
    dest.mkdir(exist_ok=False)
    before = datetime.now(timezone.utc).isoformat()
    response = requests.get(URL, timeout=35)
    after = datetime.now(timezone.utc).isoformat()
    raw = response.content
    (dest / 'competition.response.json').write_bytes(raw)
    meta = {'file': 'competition.response.json', 'url': URL,
            'request_start_utc': before, 'request_end_utc': after,
            'http_status': response.status_code, 'response_date_header': response.headers.get('Date'),
            'bytes': len(raw), 'sha256': hashlib.sha256(raw).hexdigest()}
    if response.status_code != 200:
        (dest / 'receipt.json').write_bytes((json.dumps({'status': 'LATEST_CHECK_FAILED',
             'request_start_utc': before, 'request_end_utc': after,
             'raw_response_files': [meta]}, indent=2) + '\n').encode())
        response.raise_for_status()
    current = response.json()
    result = {'status': 'VERIFIED_OFFICIAL_LATEST_SNAPSHOT_IDENTITY_READ',
              'request_start_utc': before, 'request_end_utc': after,
              'current_snapshot_id': current['current_snapshot_id'],
              'expected_snapshot_id': expected['current_snapshot_id'],
              'context': current['context'],
              'latest_snapshot_matches': current['current_snapshot_id'] == expected['current_snapshot_id'],
              'policy_matches': current['policy'] == expected['policy'],
              'raw_response_files': [meta],
              'scope': 'Snapshot/policy identity only. If either changed, existing projections are historical until a new full capture and replay.'}
    (dest / 'receipt.json').write_bytes((json.dumps(result, indent=2) + '\n').encode())
    print(json.dumps({k: result[k] for k in ('current_snapshot_id', 'latest_snapshot_matches', 'policy_matches', 'request_end_utc')}))


if __name__ == '__main__':
    main()
