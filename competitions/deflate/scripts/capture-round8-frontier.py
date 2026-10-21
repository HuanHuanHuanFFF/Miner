"""Capture one explicitly pinned official public frontier for Round 8 analysis."""
from pathlib import Path
from datetime import datetime, timezone
import argparse
import hashlib
import json
import requests

ROOT = Path(__file__).resolve().parents[1]
BASE = 'https://conjectures.io/v1/competitions/deflate'


def main():
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument('--destination', type=Path, required=True)
    args = ap.parse_args()
    dest = args.destination.resolve()
    assert dest.is_relative_to((ROOT / 'evidence/round8').resolve())
    dest.mkdir(parents=True, exist_ok=True)
    assert not any(dest.iterdir()), 'Use a fresh capture directory; preserve prior receipts'
    started = datetime.now(timezone.utc).isoformat()
    response = requests.get(BASE, timeout=30)
    response.raise_for_status()
    competition = response.json()
    snapshot = competition['current_snapshot_id']
    pages, cursor, cursors = [], None, set()
    for _ in range(20):
        params = {'limit': 100, 'snapshot_id': snapshot}
        if cursor:
            params['cursor'] = cursor
        result = requests.get(BASE + '/pareto', params=params, timeout=30)
        result.raise_for_status()
        page = result.json()
        assert page['context']['snapshot_id'] == snapshot
        pages.append(page)
        cursor = page.get('next_cursor')
        if not cursor:
            break
        assert cursor not in cursors
        cursors.add(cursor)
    else:
        raise RuntimeError('Pagination did not complete within 20 pages')
    rows = [r for p in pages for r in p['items']]
    assert len(rows) == len({r['id'] for r in rows})
    files = {'competition.json': competition, 'pareto-pages.json': pages}
    manifest = {}
    for name, value in files.items():
        raw = (json.dumps(value, indent=2) + '\n').encode()
        (dest / name).write_bytes(raw)
        manifest[name] = {'sha256': hashlib.sha256(raw).hexdigest(), 'bytes': len(raw)}
    receipt = {'status': 'VERIFIED_OFFICIAL_READ_ONLY_API_CAPTURE', 'source_url': BASE,
               'retrieved_start_utc': started, 'retrieved_end_utc': datetime.now(timezone.utc).isoformat(),
               'snapshot_id': snapshot, 'context': pages[0]['context'], 'pages': len(pages), 'rows': len(rows),
               'files': manifest, 'scope': 'Latest published snapshot returned at capture start; all pages pinned to it; live policy freshness remains as reported by the API.'}
    (dest / 'receipt.json').write_text(json.dumps(receipt, indent=2) + '\n')
    print(json.dumps(receipt))


if __name__ == '__main__':
    main()
