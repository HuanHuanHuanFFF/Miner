"""Archive six primary-source files through the authorized E: staging area."""
from pathlib import Path
from hashlib import sha1, sha256
from datetime import datetime, timezone
import argparse, json

HERE = Path(__file__).resolve().parent
ap = argparse.ArgumentParser()
ap.add_argument('--stage', type=Path, required=True)
args = ap.parse_args()
payload = json.loads((HERE/'mpfx-payload.json').read_text(encoding='utf-8'))
assert payload['commit'] == '8bd80452927ae9234fc378c07a00f2962e1e5b6f'
stage = args.stage.resolve()
expected_stage = Path('E:/Download/FloatLib/20261027-R19/mpfx-8bd80452').resolve()
assert stage == expected_stage
dest = HERE/'mpfx-8bd80452'
rows, pending = [], []
for item in payload['files']:
    path = Path(item['path'])
    assert not path.is_absolute() and '..' not in path.parts
    assert isinstance(item['text'], str)
    text = item['text'].encode('utf-8')
    candidates = [text, text+b'\n']
    matches = [raw for raw in candidates if len(raw) == item['expected']['size'] and
               sha1(b'blob '+str(len(raw)).encode()+b'\0'+raw).hexdigest() == item['expected']['sha']]
    assert len(matches) == 1, f'Cannot recover exact Git blob: {path}'
    raw = matches[0]
    pending.append((path,raw))
    rows.append(dict(path=path.as_posix(),bytes=len(raw),git_blob_sha=item['expected']['sha'],
                     sha256=sha256(raw).hexdigest(),connector_final_newline_restored=raw!=text))
for path, raw in pending:
    for root in (stage,dest):
        target = (root/path).resolve()
        assert target.is_relative_to(root.resolve())
        target.parent.mkdir(parents=True,exist_ok=True)
        if target.exists():
            assert target.read_bytes() == raw
        else:
            target.write_bytes(raw)
    assert (stage/path).read_bytes() == (dest/path).read_bytes()
record=dict(recorded_utc=datetime.now(timezone.utc).isoformat(),repository=payload['repository'],
            commit=payload['commit'],stage=str(stage),workspace_destination=str(dest),files=rows,
            license='MIT; original LICENSE preserved',
            scope='Selective primary-source intake; source bytes match exact Git blobs; no build or FloatLib proof transfer.',
            archive_cleanup='No archive downloaded; no ZIP created or deleted.')
(HERE/'intake-receipt.json').write_text(json.dumps(record,ensure_ascii=False,indent=2)+'\n',encoding='utf-8')
print(json.dumps(dict(files=len(rows),bytes=sum(r['bytes'] for r in rows),all_git_blobs_match=True,stage=str(stage),destination=str(dest)),ensure_ascii=False))
