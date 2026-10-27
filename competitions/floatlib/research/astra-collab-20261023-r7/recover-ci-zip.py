"""Read-only ZIP integrity/path audit and extraction; never run downloaded code."""
from pathlib import Path
from datetime import datetime,timezone
import argparse,hashlib,json,stat,zipfile
HERE=Path(__file__).resolve().parent
ap=argparse.ArgumentParser();ap.add_argument('--seed',required=True);ap.add_argument('--run',required=True);ap.add_argument('--digest',required=True);args=ap.parse_args()
assert args.seed.isdigit() and args.run.isdigit()
folder=HERE/'ci-recovery'/args.seed;zpath=folder/'receipts.zip';b=zpath.read_bytes();digest=hashlib.sha256(b).hexdigest();assert digest==args.digest
dest=folder/'original-extracted';dest.mkdir(exist_ok=False);members=[]
with zipfile.ZipFile(zpath) as z:
    infos=z.infolist();assert len(infos)<500 and sum(x.file_size for x in infos)<40_000_000
    assert z.testzip() is None
    for i in infos:
        target=(dest/i.filename).resolve();assert target.is_relative_to(dest.resolve())
        assert not stat.S_ISLNK(i.external_attr >> 16)
        if i.is_dir():target.mkdir(parents=True,exist_ok=True);continue
        data=z.read(i);target.parent.mkdir(parents=True,exist_ok=True);target.write_bytes(data)
        members.append({'path':i.filename,'bytes':len(data),'sha256':hashlib.sha256(data).hexdigest()})
r={'recovered_at_utc':datetime.now(timezone.utc).isoformat(),'run':int(args.run),'seed':int(args.seed),'archive_sha256':digest,'github_digest_verified':True,'archive_bytes':len(b),'zip_crc':'PASS','members':members,'scope':'Original public CI artifact bytes, no source/log alteration, no downloaded code execution. Ephemeral signed download URL deliberately not persisted.'}
(folder/'receipt.json').write_text(json.dumps(r,indent=2)+'\n');print(json.dumps({k:v for k,v in r.items() if k!='members'},indent=2));print('members',len(members))
