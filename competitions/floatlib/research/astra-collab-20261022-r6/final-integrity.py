from pathlib import Path
from datetime import datetime,timezone
import json,hashlib,zipfile
HERE=Path(__file__).resolve().parent
ROOT=HERE.parents[3]
prior=HERE.parent/'astra-collab-20261022-r5/download-index-final.json'
records=[]
historical_manifest=ROOT/'competitions/floatlib/research/materials/20261022/manifest.json'
cleanup=ROOT/'competitions/floatlib/research/materials/20261022/cleanup-receipt.json'
clean=json.loads(cleanup.read_text())
assert hashlib.sha256(historical_manifest.read_bytes()).hexdigest()==clean['manifest_sha256']
historical=json.loads(historical_manifest.read_text());verified_historical=0
for archive in historical['archives']:
    for member in archive['members']:
        p=ROOT/member['path'];b=p.read_bytes()
        assert len(b)==member['bytes'] and hashlib.sha256(b).hexdigest()==member['sha256']
        verified_historical+=1
for job in ['R6-W01','R6-W01b','R6-W02','R6-W03']:
    r=json.loads((HERE/'web'/job/'receipt.json').read_text())
    for k in ['archive','report']:
        records.append({'path':r[k],'bytes':Path(r[k]).stat().st_size,'sha256':r[k+'_sha256']})
seen=set()
for r in records:
    p=Path(r['path']);assert str(p) not in seen;seen.add(str(p))
    b=p.read_bytes();assert len(b)==r['bytes'] and hashlib.sha256(b).hexdigest()==r['sha256']
    r['integrity']='PASS'
    if p.suffix=='.zip':
        with zipfile.ZipFile(p) as z:assert z.testzip() is None
        r['crc']='PASS'
out={'verified_at_utc':datetime.now(timezone.utc).isoformat(),'previous_index':str(prior.relative_to(ROOT)),'historical_note':'R2-R5 ZIPs were removed by prior documented12:20 maintenance after byte-preserving extraction; no current E-path existence claimed. Initial audit correctly failed on those historical paths, then followed the current material manifest. R6 originals remain on E.','historical_manifest':str(historical_manifest.relative_to(ROOT)),'historical_manifest_sha256':clean['manifest_sha256'],'historical_members_reverified':verified_historical,'files':records,'zip_count':sum(Path(r['path']).suffix=='.zip' for r in records),'report_count':sum(Path(r['path']).suffix=='.md' for r in records)}
(HERE/'download-index-final.json').write_text(json.dumps(out,indent=2)+'\n')
cs=[]
for p in sorted((ROOT/'competitions/floatlib/candidates').glob('f01-r6-*/Kernel.lean')):
    b=p.read_bytes();m=json.loads(p.with_name('manifest.json').read_text());assert hashlib.sha256(b).hexdigest()==m['candidate_sha256'];assert len(b)==m['candidate_bytes']
    cs.append({'candidate':p.parent.name,'sha256':m['candidate_sha256'],'bytes':len(b)})
(HERE/'handoff-source-identity.json').write_text(json.dumps({'verified_at_utc':out['verified_at_utc'],'candidates':cs},indent=2)+'\n')
print(json.dumps({'verified_at_utc':out['verified_at_utc'],'zips':out['zip_count'],'reports':out['report_count'],'candidate_hashes':len(cs),'status':'PASS'},indent=2))
