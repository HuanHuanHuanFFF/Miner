"""Create a deterministic two-file review payload only for an accepted exact pair."""
from pathlib import Path
from datetime import datetime,timezone
import argparse,hashlib,json,zipfile

ROOT=Path(__file__).resolve().parents[1]

def sha(p):return hashlib.sha256(p.read_bytes()).hexdigest()

def main():
    ap=argparse.ArgumentParser(description=__doc__);ap.add_argument('candidate');args=ap.parse_args()
    source=(ROOT/'candidates'/args.candidate).resolve();assert source.is_relative_to((ROOT/'candidates').resolve())and source.name==args.candidate and source.name.startswith('r18-')
    cert=json.loads((source/'VERIFICATION.json').read_bytes());assert cert['status']=='VERIFIED_EXACT_ORIGINAL_PUBLIC_GATE_PASSED';files=cert['files'];assert set(files)=={'parse.rs','Parse.lean'}
    for name,h in files.items():assert 0<(source/name).stat().st_size<=524288 and sha(source/name)==h
    receipt=(ROOT/cert['receipt']).resolve();assert receipt.is_relative_to((ROOT/'evidence/round18').resolve());gate=json.loads(receipt.read_bytes());assert gate['status']=='EXACT_ORIGINAL_PUBLIC_GATE_ACCEPTED'and all(gate['checks'].values())and gate['spec']['files']==files
    assert gate['run_id']==cert['run_id']and gate['git_sha']==cert['git_sha']
    artifact=next(p for p in(receipt.parent,receipt.parent.parent)if(p/'raw-artifact-files.json').exists());inv=json.loads((artifact/'raw-artifact-files.json').read_bytes());ci=json.loads((artifact/'ci-run.json').read_bytes());assert ci['status']=='completed'and ci['conclusion']=='success'and ci['headSha']==gate['git_sha']
    for name,v in inv['files'].items():
        p=(artifact/name).resolve();assert p.is_relative_to(artifact.resolve())and p.stat().st_size==v['bytes']and sha(p)==v['sha256']
    folder=ROOT/'evidence/round18/review-packages';folder.mkdir(exist_ok=True);stem=args.candidate+'-'+files['parse.rs'][:12]+'-'+files['Parse.lean'][:12];payload=folder/(stem+'.zip');manifest=folder/(stem+'.json');assert not payload.exists()and not manifest.exists()
    with zipfile.ZipFile(payload,'w',compression=zipfile.ZIP_DEFLATED,compresslevel=9)as z:
        for name in('parse.rs','Parse.lean'):
            info=zipfile.ZipInfo(name,date_time=(1980,1,1,0,0,0));info.create_system=3;info.external_attr=0o644<<16;info.compress_type=zipfile.ZIP_DEFLATED;z.writestr(info,(source/name).read_bytes(),compress_type=zipfile.ZIP_DEFLATED,compresslevel=9)
    with zipfile.ZipFile(payload)as z:
        assert z.namelist()==['parse.rs','Parse.lean']
        for name,h in files.items():assert hashlib.sha256(z.read(name)).hexdigest()==h
    record={'status':'VERIFIED_EXACT_PUBLIC_GATE_PAIR_REVIEW_PAYLOAD_NOT_UPLOADED','created_at_utc':datetime.now(timezone.utc).isoformat(),'candidate':args.candidate,'source_path':str(source.relative_to(ROOT)).replace('\\','/'),'files':files,'payload_path':str(payload.relative_to(ROOT)).replace('\\','/'),'payload_sha256':sha(payload),'payload_bytes':payload.stat().st_size,'original_gate_run_id':gate['run_id'],'original_gate_run_url':ci['url'],'original_gate_git_sha':gate['git_sha'],'original_gate_receipt':cert['receipt'],'original_gate_receipt_sha256':sha(receipt),'formal_submission_sent':False,'formal_admission':'UNKNOWN','formal_payable_pool_share_pct':None,'current_registration_owner_and_quota':'UNKNOWN; not checked for an authorized upload','performance_evidence':'See the round18 final/current report and raw confirmation analysis separately; this payload manifest certifies exact public-gate file binding only.','scope':'Only the exact two UTF8source/proof files are in the deterministic zip. The archive is for review and is not an official submission, signature or admission result. New registration, wallet actions and formal upload are outside this research authorization.'};manifest.write_bytes((json.dumps(record,indent=2)+'\n').encode());print(json.dumps(record))

if __name__=='__main__':main()
