"""Acquire ordinary publicly released sources for current dominated quality anchors."""
from pathlib import Path
from datetime import datetime, timezone
import hashlib, json, requests

ROOT = Path(__file__).resolve().parents[1]
E = ROOT / 'evidence/round24/public-start'
E.mkdir(exist_ok=False)
rows = {str(r['id']):r for page in json.loads((ROOT/'evidence/round24/official-start/pareto-pages.json').read_bytes()) for r in page['items']}
records = []
session = requests.Session()
try:
    for id in ['607','609','615','617']:
        row = rows[id]
        if row['score']['on_frontier']:
            records.append({'id':id, 'status':'NOT_REQUESTED_CURRENT_FRONTIER', 'snapshot_id':'29607'})
            continue
        url = f'https://conjectures.io/v1/competitions/deflate/submissions/{id}/source'
        start = datetime.now(timezone.utc).isoformat()
        r = session.get(url, timeout=40)
        (E / f'{id}.response.json').write_bytes(r.content)
        receipt = {'id':id, 'url':url, 'snapshot_id':'29607', 'request_start_utc':start,
            'request_end_utc':datetime.now(timezone.utc).isoformat(), 'http_status':r.status_code,
            'bytes':len(r.content), 'sha256':hashlib.sha256(r.content).hexdigest(),
            'author_hotkey':row.get('hotkey'), 'metrics':row['metrics'],
            'reason':'Distinct high-compression frontier region; sources are read only through the ordinary unauthenticated endpoint. No restricted source access attempted.'}
        if r.status_code == 200:
            source = r.json(); assert str(source['id']) == id
            dest = ROOT / f'references/round24-public-{id}'; dest.mkdir(exist_ok=False)
            receipt['files'] = {}
            for name,key in [('parse.rs','parse_rs'),('Parse.lean','proof_lean')]:
                raw = source[key].encode(); assert 0 < len(raw) <= 524288
                (dest/name).write_bytes(raw)
                receipt['files'][name]={'sha256':hashlib.sha256(raw).hexdigest(),'bytes':len(raw)}
            (dest/'source-receipt.json').write_bytes((json.dumps(receipt,indent=2)+'\n').encode())
        records.append(receipt)
finally:
    (E/'receipt.json').write_bytes((json.dumps(records,indent=2)+'\n').encode())
    session.close()
print(json.dumps([{'id':r['id'],'status':r['http_status'],'files':r.get('files')} for r in records],indent=2))
