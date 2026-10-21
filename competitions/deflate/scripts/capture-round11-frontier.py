"""Capture full official public pages with original bodies and request times."""
from pathlib import Path
from datetime import datetime, timezone
import argparse
import hashlib
import json
import requests

ROOT = Path(__file__).resolve().parents[1]
BASE = 'https://conjectures.io/v1/competitions/deflate'


def now():
    return datetime.now(timezone.utc).isoformat()


def main():
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument('--destination', type=Path, required=True)
    args = ap.parse_args()
    dest = args.destination.resolve()
    assert dest.is_relative_to((ROOT / 'evidence/round11').resolve())
    dest.mkdir(parents=True, exist_ok=True)
    assert not any(dest.iterdir()), 'Use a fresh directory; prior response bodies are immutable'
    started = now()
    raw_receipts = []
    session = requests.Session()

    def get(endpoint, filename, params=None):
        before = now()
        response = session.get(BASE + endpoint, params=params, timeout=40)
        after = now()
        raw = response.content
        (dest / filename).write_bytes(raw)
        raw_receipts.append({'file': filename, 'url': response.url,
                             'request_start_utc': before, 'request_end_utc': after,
                             'http_status': response.status_code,
                             'response_date_header': response.headers.get('Date'),
                             'bytes': len(raw), 'sha256': hashlib.sha256(raw).hexdigest()})
        response.raise_for_status()
        return response.json()

    try:
        competition = get('', 'competition.response.json')
        snapshot = competition['current_snapshot_id']
        derived = {'competition.json': competition}
        pagination = {}
        for endpoint, identity, rows_key in [('pareto', 'id', 'items'), ('leaderboard', 'hotkey', 'ranking')]:
            pages, cursor, seen = [], None, set()
            for page_no in range(1, 21):
                params = {'limit': 100, 'snapshot_id': snapshot}
                if cursor:
                    params['cursor'] = cursor
                page = get('/' + endpoint, f'{endpoint}-page-{page_no:03d}.response.json', params)
                assert page['context']['snapshot_id'] == snapshot
                pages.append(page)
                cursor = page.get('next_cursor')
                if not cursor:
                    break
                assert cursor not in seen
                seen.add(cursor)
            else:
                raise RuntimeError('Pagination exceeded the bounded page count')
            items = [r for p in pages for r in p[rows_key]]
            assert len(items) == len({r[identity] for r in items})
            pagination[endpoint] = {'pages': len(pages), 'rows': len(items), 'terminal_next_cursor': cursor}
            derived[endpoint + '-pages.json'] = pages
        weights = get('/weights/current', 'weights-current.response.json')
        derived['weights-current.json'] = weights
        files = {}
        for filename, value in derived.items():
            raw = (json.dumps(value, indent=2) + '\n').encode()
            (dest / filename).write_bytes(raw)
            files[filename] = {'bytes': len(raw), 'sha256': hashlib.sha256(raw).hexdigest()}
        receipt = {'status': 'VERIFIED_OFFICIAL_READ_ONLY_API_CAPTURE', 'source_url': BASE,
                   'snapshot_id': snapshot, 'retrieval_start_utc': started, 'retrieval_end_utc': now(),
                   'competition_context': competition['context'], 'policy': competition['policy'],
                   'pagination': pagination, 'raw_response_files': raw_receipts, 'derived_files': files,
                   'weights_context': weights.get('context'),
                   'weights_same_snapshot': str(weights.get('context', {}).get('snapshot_id')) == str(snapshot),
                   'scope': 'Pareto and leaderboard are pinned to one published snapshot. weights/current is a separately timed current response and may advance. API freshness is retained, not upgraded.'}
        (dest / 'receipt.json').write_text(json.dumps(receipt, indent=2) + '\n')
        print(json.dumps({'snapshot_id': snapshot, 'context': competition['context'],
                          'pagination': pagination, 'destination': str(dest),
                          'weights_same_snapshot': receipt['weights_same_snapshot']}))
    except Exception as error:
        (dest / 'capture-failure.json').write_text(json.dumps({'status': 'CAPTURE_FAILED',
            'started_utc': started, 'ended_utc': now(), 'error': f'{type(error).__name__}: {error}',
            'raw_response_files': raw_receipts}, indent=2) + '\n')
        raise
    finally:
        session.close()


if __name__ == '__main__':
    main()
