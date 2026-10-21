"""Create review-only exact two-file bundles from accepted public-gate pairs."""
from pathlib import Path
from datetime import datetime,timezone
import hashlib,json,zipfile
ROOT=Path(__file__).resolve().parents[1];E=ROOT/'evidence/round22'

def main():
    dest=E/'delivery';dest.mkdir(exist_ok=True)
    rows=[]
    for name in ('r22-595-halfhead','r22-595-row6-chain'):
        p=ROOT/'candidates'/name
        cert=json.loads((p/'VERIFICATION.json').read_bytes())
        assert cert['status']=='VERIFIED_EXACT_ORIGINAL_PUBLIC_GATE_PASSED'
        data={f:(p/f).read_bytes() for f in ('parse.rs','Parse.lean')}
        assert {f:hashlib.sha256(b).hexdigest() for f,b in data.items()}==cert['files']
        z=dest/(name+'-review.zip');assert not z.exists()
        with zipfile.ZipFile(z,'w',compression=zipfile.ZIP_DEFLATED,compresslevel=9) as out:
            for f,b in data.items():
                info=zipfile.ZipInfo(f,(2026,10,11,0,37,6));info.compress_type=zipfile.ZIP_DEFLATED
                out.writestr(info,b,compress_type=zipfile.ZIP_DEFLATED,compresslevel=9)
        with zipfile.ZipFile(z) as bundle:
            assert set(bundle.namelist())==set(data) and len(bundle.namelist())==2
            assert all(bundle.read(f)==b for f,b in data.items())
        rows.append({'candidate':name,'source_path':p.relative_to(ROOT).as_posix(),'files':cert['files'],'public_gate_run_id':cert['run_id'],'zip':z.relative_to(ROOT).as_posix(),'zip_bytes':z.stat().st_size,'zip_sha256':hashlib.sha256(z.read_bytes()).hexdigest(),'formal_submission_sent':False,'formal_admission':'UNKNOWN','formal_reward_pool_share_pct':None})
    (dest/'receipt.json').write_bytes((json.dumps({'status':'VERIFIED_EXACT_REVIEW_BUNDLES_ONLY','created_at_utc':datetime.now(timezone.utc).isoformat(),'bundles':rows,'scope':'Two exact public-gate-accepted Rust/Lean members each. No upload, registration, private gate, signing, payment or formal submission digest claim. Performance results are separate.'},indent=2)+'\n').encode())
    print([(r['candidate'],r['zip_bytes']) for r in rows])

if __name__=='__main__':main()
