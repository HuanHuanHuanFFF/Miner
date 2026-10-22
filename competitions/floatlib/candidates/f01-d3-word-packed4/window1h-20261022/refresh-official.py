"""Capture the current public champion and immutable response bytes."""
from pathlib import Path
import datetime, hashlib, json, os, urllib.request

ROOT = Path(__file__).resolve().parent
STAMP = datetime.datetime.now(datetime.timezone.utc).strftime('%Y%m%dT%H%M%SZ')
OUT = ROOT / ('official-' + STAMP)
OUT.mkdir()
rows = {}

def get(name, endpoint):
    url = 'https://conjectures.io/v1/competitions/floatlib' + endpoint
    now = datetime.datetime.now(datetime.timezone.utc).isoformat()
    req = urllib.request.Request(url, headers={'User-Agent': 'FloatLib-development-evidence/1.0'})
    with urllib.request.urlopen(req, timeout=30) as response:
        data = response.read()
        status = response.status
    filename = name + '.raw'
    (OUT / filename).write_bytes(data)
    rows[name] = dict(url=url, queried_at_utc=now, http_status=status,
                      bytes=len(data), sha256=hashlib.sha256(data).hexdigest(), file=filename)
    return json.loads(data)

try:
    competition = get('competition', '')
    champions = get('champions', '/champions')
    get('leaderboard', '/leaderboard')
    current = next(row for row in champions if row['current'])
    champion = get('champion-detail', '/submissions/' + str(current['submission']))
    (OUT / 'receipts.json').write_text(json.dumps({'responses': rows}, indent=2) + '\n', encoding='utf-8')
    pointer = ROOT / 'current-official-snapshot.json'
    tmp = pointer.with_suffix('.update-tmp')
    tmp.write_text(json.dumps(dict(directory=OUT.name, queried_at_utc=rows['champion-detail']['queried_at_utc']), indent=2) + '\n', encoding='utf-8')
    os.replace(tmp, pointer)
    print(json.dumps(dict(champion=champion['id'], digest=champion['digest'], snapshot=competition['current_snapshot_id'])))
except Exception as error:
    (OUT / 'failure.json').write_text(json.dumps(dict(error=str(error), responses=rows), indent=2) + '\n', encoding='utf-8')
    raise
