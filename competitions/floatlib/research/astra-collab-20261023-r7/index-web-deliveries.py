from pathlib import Path
from datetime import datetime,timezone
import hashlib,json
HERE=Path(__file__).resolve().parent
rows=[]
for receipt in sorted((HERE/'web').glob('*/receipt.json')):
    r=json.loads(receipt.read_text());row={'job':r['job'],'receipt':str(receipt.relative_to(HERE)),'recovered_at_utc':r['recovered_at_utc'],'manifest_entries_verified_at_recovery':r['manifest_entries_verified'],'files':[]}
    for kind,key in [('archive','archive'),('report','report')]:
        p=Path(r[key]);f={'kind':kind,'path':str(p),'exists_now':p.is_file(),'original_sha256':r[key+'_sha256']}
        if p.is_file():
            b=p.read_bytes();f.update(bytes=len(b),sha256=hashlib.sha256(b).hexdigest());assert f['sha256']==f['original_sha256']
        row['files'].append(f)
    extracted=receipt.parent/'original-extracted';row['extracted_root']=str(extracted.resolve());entries=set(extracted.glob('*/*.lean')) | set(extracted.glob('*/src/*.lean'));row['top_level_lean']=[{'path':str(p.resolve()),'bytes':p.stat().st_size,'sha256':hashlib.sha256(p.read_bytes()).hexdigest()} for p in sorted(entries)]
    rows.append(row)
out={'checked_at_utc':datetime.now(timezone.utc).isoformat(),'scope':'R7 inbound original web6Pro deliveries; byte hashes/manifest integrity, not inherited full-gate acceptance. Prior-round files are indexed in their own handoffs.','deliveries':rows}
(HERE/'web-deliveries.json').write_text(json.dumps(out,ensure_ascii=False,indent=2)+'\n',encoding='utf-8');print(json.dumps({'deliveries':len(rows),'files_present':sum(f['exists_now'] for r in rows for f in r['files'])}))
