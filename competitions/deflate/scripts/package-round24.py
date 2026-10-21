"""Package exact frozen source pairs, without uploads, secrets or signing data."""
from pathlib import Path
from datetime import datetime,timezone
import hashlib,json,zipfile
ROOT=Path(__file__).resolve().parents[1];E=ROOT/'evidence/round24'
def sha(p):return hashlib.sha256(p.read_bytes()).hexdigest()
def main():
    plan=json.loads((E/'confirm-final-plan.json').read_bytes());selection=json.loads((E/'final-selection-decision.json').read_bytes());out=E/'review-packages';out.mkdir(exist_ok=True);manifest=out/'packages.json';assert not manifest.exists();stamp=datetime.fromisoformat(plan['frozen_utc']).astimezone(timezone.utc);rows=[]
    for e in selection['selected']:
        name=e['candidate'];source=ROOT/'candidates'/name;files=plan['files'][name];cert=json.loads((source/'VERIFICATION.json').read_bytes());assert cert['status']=='VERIFIED_EXACT_ORIGINAL_PUBLIC_GATE_PASSED' and cert['files']==files;assert all(sha(source/f)==h for f,h in files.items())
        receipt=json.loads((ROOT/cert['receipt']).read_bytes());assert receipt['status']=='EXACT_ORIGINAL_PUBLIC_GATE_ACCEPTED' and all(receipt['checks'].values())and receipt['spec']['files']==files
        filename=f"{e['label']}-{name}-{files['parse.rs'][:12]}-{files['Parse.lean'][:8]}.zip";path=out/filename;assert not path.exists()
        with zipfile.ZipFile(path,'w',compression=zipfile.ZIP_DEFLATED,compresslevel=9)as z:
            for f in ['parse.rs','Parse.lean']:
                info=zipfile.ZipInfo(f,date_time=stamp.timetuple()[:6]);info.compress_type=zipfile.ZIP_DEFLATED;info.create_system=3;info.external_attr=0o100644<<16;z.writestr(info,(source/f).read_bytes(),compress_type=zipfile.ZIP_DEFLATED,compresslevel=9)
        with zipfile.ZipFile(path)as z:
            assert z.namelist()==['parse.rs','Parse.lean'] and z.testzip()is None
            assert all(hashlib.sha256(z.read(f)).hexdigest()==h for f,h in files.items())
        rows.append({'label':e['label'],'candidate':name,'target_pool_share_pct_NOT_achieved':e['target_pool_share_pct'],'archive':path.relative_to(ROOT).as_posix(),'archive_sha256':sha(path),'archive_bytes':path.stat().st_size,'source_files':{f:{'sha256':h,'bytes':(source/f).stat().st_size}for f,h in files.items()},'gate_run_id':cert['run_id'],'gate_receipt':cert['receipt'],'source_freeze_utc':plan['frozen_utc'],'contents':['parse.rs','Parse.lean'],'formal_submission_sent':False,'formal_admission':'UNKNOWN','formal_payable_pool_share_pct':None})
    result={'status':'VERIFIED_SOURCE_ONLY_PACKAGES_MATCH_FROZEN_GATE_PAIRS','prepared_utc':datetime.now(timezone.utc).isoformat(),'packages':rows,'scope':'Archives contain exactlythe two sourcefiles, checked byte-for-byte againstfrozenplan andacceptedoriginalgate. Performanceconfirmation isseparate andstillrunning at preparation. No wallet,secret,nonce,signature,registration orcompetition upload action.'};manifest.write_bytes((json.dumps(result,indent=2)+'\n').encode());print(json.dumps({'status':result['status'],'packages':[{k:r[k]for k in ['label','archive','archive_sha256','archive_bytes']}for r in rows]},indent=2))
if __name__=='__main__':main()
