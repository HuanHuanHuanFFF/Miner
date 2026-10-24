"""Read-only artifact recovery into R-owned evidence; never invokes Git/CI tools."""
from pathlib import Path
from datetime import datetime,timezone
import argparse,hashlib,io,json,urllib.request,zipfile
HERE=Path(__file__).resolve().parent
def main():
    ap=argparse.ArgumentParser();ap.add_argument('--url',required=True);ap.add_argument('--sha',required=True);a=ap.parse_args()
    assert a.url.startswith('https://') and '.oaiusercontent.com/' in a.url
    with urllib.request.urlopen(a.url,timeout=45) as response:raw=response.read(20_000_001)
    assert len(raw)<=20_000_000
    digest=hashlib.sha256(raw).hexdigest();assert digest==a.sha
    dest=HERE/'astra-ci1224016';assert not dest.exists();dest.mkdir()
    records=[]
    with zipfile.ZipFile(io.BytesIO(raw)) as z:
        members=z.infolist();assert sum(x.file_size for x in members)<40_000_000
        assert z.testzip() is None
        for e in members:
            if e.is_dir():continue
            p=Path(e.filename)
            assert not p.is_absolute() and '..' not in p.parts
            data=z.read(e)
            entry={'name':e.filename,'bytes':len(data),'sha256':hashlib.sha256(data).hexdigest()}
            # Only textual evidence; no executable/object/dependency installation.
            try:data.decode('utf-8')
            except UnicodeDecodeError:entry['saved']=False;records.append(entry);continue
            target=dest/p;target.parent.mkdir(parents=True,exist_ok=True);target.write_bytes(data)
            entry['saved']=True;records.append(entry)
    receipt={'at_utc':datetime.now(timezone.utc).isoformat(),'run':40080782614,'artifact':12556090363,
             'archive_sha256':digest,'archive_bytes':len(raw),'members':records,
             'scope':'Original artifact bytes verified in memory; exact text evidence only saved underR12/astra-ci1224016. No Root CI directory/state mutation, no dispatch/cancel, no binary installation.'}
    (dest/'astra-recovery-receipt.json').write_text(json.dumps(receipt,ensure_ascii=False,indent=2)+'\n',encoding='utf-8',newline='\n')
    for f in dest.rglob('f01-r12-column4-narrow-verdict.json'):
        d=json.loads(f.read_text());print(json.dumps({'path':str(f),'sha256':hashlib.sha256(f.read_bytes()).hexdigest(),**{k:d.get(k) for k in ['passed','stage','mode','ratio','reason','seed']}}))
    print(json.dumps({'saved_text_files':sum(x['saved'] for x in records),'members':len(records),'archive_sha256':digest}))
if __name__=='__main__':main()
