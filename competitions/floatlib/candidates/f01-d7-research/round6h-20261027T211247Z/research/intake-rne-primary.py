"""Pinned public MIT source intake: E first, exact byte verification into research."""
from pathlib import Path
from datetime import datetime, timezone
from urllib.request import Request, urlopen
from concurrent.futures import ThreadPoolExecutor
import hashlib
import json
import shutil

HERE = Path(__file__).resolve().parent
REF = '0d91825727839f597fd06b22fdd038ea21480f0c'
ITEMS = [["Quotient.lean","b43c26d020590fd922cdd9ab26e9cf0000cce15d"],["ShiftRight.lean","d53bd9ec15f51006a945e3c49d7c3e1d3185af19"]]

if __name__ == '__main__':
    stamp = datetime.now(timezone.utc).strftime('%Y%m%dT%H%M%SZ')
    stage = Path('E:/Download/FloatLib/20261028-R22/rne-primary') / stamp
    stage.mkdir(parents=True, exist_ok=False)
    def fetch(item):
        name, expected = item
        url = f'https://raw.githubusercontent.com/lean-dojo/FloatLib/{REF}/FloatLib/Numerics/Quantization/Deterministic/{name}'
        with urlopen(Request(url, headers={'User-Agent': 'FloatLib-public-research'}), timeout=15) as response:
            raw = response.read(262145)
            assert response.status == 200 and len(raw) <= 262144
        git_blob = hashlib.sha1(f'blob {len(raw)}\0'.encode() + raw).hexdigest()
        assert git_blob == expected
        (stage / name).write_bytes(raw)
        return {'name': name, 'url': url, 'git_blob': git_blob, 'bytes': len(raw),
                'sha256': hashlib.sha256(raw).hexdigest(), 'utc': datetime.now(timezone.utc).isoformat()}
    with ThreadPoolExecutor(max_workers=2) as pool:
        rows = list(pool.map(fetch, ITEMS))
    receipt = {'scope': 'Pinned FloatLib Team MIT source, read-only; no local compiler or source execution',
               'staging': str(stage), 'items': rows, 'archives': 0}
    (stage / 'receipt.json').write_text(json.dumps(receipt, indent=2) + '\n')
    target = HERE / 'rne-primary' / stamp
    target.mkdir(parents=True, exist_ok=False)
    for p in stage.iterdir():
        q = target / p.name
        shutil.copyfile(p, q)
        assert p.read_bytes() == q.read_bytes()
    print(json.dumps({'branch_directory': str(target), 'files': len(rows), 'bytes': sum(x['bytes'] for x in rows), 'archives': 0}))
