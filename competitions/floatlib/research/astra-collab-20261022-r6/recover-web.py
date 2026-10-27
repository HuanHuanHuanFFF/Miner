from pathlib import Path
import zipfile,hashlib,json,sys
from datetime import datetime,timezone
HERE=Path(__file__).resolve().parent
name=sys.argv[1]
archive=Path('E:/Download')/(sys.argv[2] if len(sys.argv)>2 else name+'.zip')
report=Path('E:/Download')/(sys.argv[3] if len(sys.argv)>3 else name+'-report.md')
dest=HERE/'web'/name/'original-extracted'
dest.mkdir(parents=True,exist_ok=True)
receipts=[]
with zipfile.ZipFile(archive) as z:
    assert sum(i.file_size for i in z.infolist())<20_000_000
    assert len(z.infolist())<200
    assert z.testzip() is None
    for i in z.infolist():
        target=(dest/i.filename).resolve()
        assert target.is_relative_to(dest.resolve())
        assert not i.is_dir()
        data=z.read(i)
        if target.exists():assert target.read_bytes()==data
        else:
            target.parent.mkdir(parents=True,exist_ok=True);target.write_bytes(data)
        receipts.append({'file':i.filename,'bytes':len(data),'sha256':hashlib.sha256(data).hexdigest()})
manifest=list(dest.rglob('MANIFEST.sha256'))+list(dest.rglob('SHA256SUMS.txt'))
verified=[]
for m in manifest:
    for line in m.read_text().splitlines():
        if not line.strip():continue
        sha,rel=line.split(maxsplit=1);rel=rel.lstrip('*')
        target=(m.parent/rel).resolve()
        assert target.is_relative_to(dest.resolve())
        assert hashlib.sha256(target.read_bytes()).hexdigest()==sha,(name,rel)
        verified.append(rel)
out={'job':name,'recovered_at_utc':datetime.now(timezone.utc).isoformat(),'archive':str(archive),'archive_bytes':archive.stat().st_size,'archive_sha256':hashlib.sha256(archive.read_bytes()).hexdigest(),'report':str(report),'report_sha256':hashlib.sha256(report.read_bytes()).hexdigest(),'zip_crc':'PASS','manifest_entries_verified':len(verified),'files':receipts,'scope':'Original bytes only; no downloaded executable/script run, no Lean acceptance inherited.'}
(HERE/'web'/name/'receipt.json').write_text(json.dumps(out,indent=2)+'\n')
print(json.dumps({k:v for k,v in out.items() if k!='files'},indent=2))
