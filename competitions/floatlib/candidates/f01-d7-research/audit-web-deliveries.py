"""Independently verify inbound original archives, manifests and extracted bytes."""
from pathlib import Path,PurePosixPath
import datetime,hashlib,json,zipfile

root=Path.cwd().resolve();own=Path(__file__).resolve().parent
research=root/'competitions/floatlib/research/astra-collab-20261023-r7'
index_path=research/'web-deliveries.json';index_raw=index_path.read_bytes();index=json.loads(index_raw)
def sha(raw):return hashlib.sha256(raw).hexdigest()
rows=[]
for d in index['deliveries']:
    receipt_path=research/d['receipt'];receipt_raw=receipt_path.read_bytes();r=json.loads(receipt_raw)
    archive=Path(r['archive']);raw=archive.read_bytes()
    assert len(raw)==r['archive_bytes'] and sha(raw)==r['archive_sha256'],archive
    report=Path(r['report']);assert sha(report.read_bytes())==r['report_sha256'],report
    extracted=Path(d['extracted_root']).resolve();assert extracted.is_relative_to(research.resolve())
    expected={f['file']:f for f in r['files']}
    assert len(expected)==len(r['files'])
    payloads={};size=0
    with zipfile.ZipFile(archive) as z:
        names=[f.filename for f in z.infolist() if not f.is_dir()]
        assert len(names)==len(set(names)) and set(names)==set(expected)
        for name in names:
            member=PurePosixPath(name)
            assert not member.is_absolute() and '..' not in member.parts
            target=(extracted/Path(*member.parts)).resolve();assert target.is_relative_to(extracted)
            content=z.read(name) # zipfile checks the original CRC while reading.
            h=sha(content);f=expected[name]
            assert len(content)==f['bytes'] and h==f['sha256'],name
            assert target.is_file() and target.read_bytes()==content,target
            payloads[name]=h;size+=len(content)
        manifests=[n for n in names if n.endswith('/MANIFEST.sha256')]
        assert len(manifests)==1,manifests
        m=manifests[0];prefix=PurePosixPath(m).parent
        checks=0
        for line in z.read(m).decode('utf-8-sig').splitlines():
            if not line.strip():continue
            h,name=line.split(maxsplit=1);name=name.lstrip('*')
            key=(prefix/name).as_posix();assert payloads[key]==h,(d['job'],key)
            checks+=1
        assert checks==r['manifest_entries_verified']==len(names)-1
    rows.append({'job':d['job'],'archive_sha256':r['archive_sha256'],'report_sha256':r['report_sha256'],'receipt_sha256':sha(receipt_raw),'payload_files':len(payloads),'manifest_entries':checks,'extracted_bytes':size,'crc_and_exact_bytes':'PASS'})
out={'verified_at_utc':datetime.datetime.now(datetime.timezone.utc).isoformat(),'status':'PASS_ORIGINAL_ARCHIVE_CRC_MANIFEST_AND_EXTRACTED_BYTES','delivery_index_sha256':sha(index_raw),'deliveries':rows,'scope':'Read-only independent integrity audit. External compiler claims are retained evidence, not inherited full candidate gate acceptance. No archive deleted, source uploaded or code executed.'}
(own/'web-delivery-integrity.json').write_text(json.dumps(out,indent=2)+'\n',encoding='utf8')
print(json.dumps({'deliveries':len(rows),'payload_files':sum(x['payload_files'] for x in rows),'manifest_entries':sum(x['manifest_entries'] for x in rows),'extracted_bytes':sum(x['extracted_bytes'] for x in rows),'status':out['status']}))
