"""Freeze three fresh original-protocol runs after both selected exact gates pass."""
from pathlib import Path
from datetime import datetime,timezone
import argparse,copy,hashlib,json
ROOT=Path(__file__).resolve().parents[1];E=ROOT/'evidence/round24'
def read(p):return json.loads(p.read_bytes())
def main():
    ap=argparse.ArgumentParser();ap.add_argument('--base',required=True);ap.add_argument('--candidate',action='append',required=True);ap.add_argument('--prefix',default='confirm-final');a=ap.parse_args();assert len(a.candidate)==len(set(a.candidate))==2
    s=read(E/(a.base+'.json'));assert s['r24_mode']=='standard';s.pop('preflight_only',None);source_entries=s['entries'];chosen=[];certificates={};needed={'probe3','r3-432-fast3','public432','public607'}
    for name in a.candidate:
        path=ROOT/'candidates'/name;m=read(path/'manifest.json');c=read(path/'VERIFICATION.json');assert c['status']=='VERIFIED_EXACT_ORIGINAL_PUBLIC_GATE_PASSED' and c['files']==m['hashes'];assert all(hashlib.sha256((path/f).read_bytes()).hexdigest()==h for f,h in c['files'].items())
        rows=[e for e in source_entries if not e['control'] and e['hashes']['parse.rs']==m['hashes']['parse.rs']];assert len(rows)==1,'Selected exactRust must match one declared candidate in the chosen discovery batch'
        e=copy.deepcopy(rows[0]);e.update(name=name,path=path.relative_to(ROOT).as_posix(),hashes=c['files']);chosen.append(e);certificates[name]=c;needed|={e['anchor'],e['anchor']+'-shadow',e['comparison_baseline']}
    assert len({e['hashes']['parse.rs']for e in chosen})==2,'Proof copies are not different optimization candidates'
    controls=[copy.deepcopy(e)for e in source_entries if e['control']and e['name']in needed];assert {e['name']for e in controls}==needed
    shadows=[{'name':e['name']+'-shadow','path':e['path'],'control':True,'hashes':e['hashes'],'anchor':e['anchor']}for e in chosen]
    s['entries']=controls+chosen+shadows;s.update(screen_blocks=3,refine_blocks=0,shortlist=0,gate_candidates=[],gate_limit=0,extract_candidates=[],native_only=False,native_encoder=False,native_encoder_references=[],synthetic_validation=False,r18_role='independent_confirmation',r24_role='final_frozen_confirmation',r24_expected_candidates=2,r24_dispatch_after_gate_pair_known=True,description='Finalexact-pair confirmation:3fresh runners x3original1warmup11measured blocks. Each candidate and609reference has asame-source shadow;607supplement andactualparent retained. Everyblock/zero/below-target observation retained. Diagnosticprotocols excluded.')
    names=[e['name']for e in s['entries']]
    def rotate(k):return names[k:]+names[:k]
    schedules=[[names,names[::-1],rotate(3)],[names[::-1],rotate(5),names],[rotate(len(names)//2),rotate(3)[::-1],rotate(1)]]
    budget=read(E/'budget.json');now=datetime.now(timezone.utc);left=(datetime.fromisoformat(budget['deadline_utc'])-now).total_seconds()/60;assert left>=85,'Need original65minute cap pluscollection/report reserve'
    for i,orders in enumerate(schedules,1):
        spec=copy.deepcopy(s);spec['screen_orders']=orders;spec['r24_confirmation_runner_index']=i;p=E/f'{a.prefix}-{i}.json';assert not p.exists();p.write_bytes((json.dumps(spec,indent=2)+'\n').encode())
    record={'status':'PREDECLARED_FROZEN_FINAL_CONFIRMATION','frozen_utc':now.isoformat(),'budget_deadline_utc':budget['deadline_utc'],'candidates':a.candidate,'files':{e['name']:e['hashes']for e in chosen},'gates':certificates,'runners':3,'blocks_per_runner':3,'methods_per_block':len(names),'original_measured_reps':11,'original_warmup_reps':1,'cost_cap_runner_minutes_each':65,'screen_prefix':a.prefix,'gap':'Discovery andpriorcomponent runs cannot establish newexact-pair stability. Same-source andrelated-anchor disagreements may changewhetherpositive/targetshareexists.','change':'No codeorproof changes: freshoriginalprotocol runs afterexactpairfreeze andfullgate.','decision':'Reportindividual/joint shares onlatestofficialsnapshot, minimum/median/range,zero/10/15counts, allcandidate/anchorcontrols andrunner strata. Preserve allfailures; neverinterpretobservedpassfraction asformalsuccess probability.','limits':'Independent runs reuse the searchedpubliccorpus; no unseenprivate result, formaladmission, registration orpayable reward claim.'}
    p=E/(a.prefix+'-plan.json');assert not p.exists();p.write_bytes((json.dumps(record,indent=2)+'\n').encode());print(json.dumps({'status':record['status'],'files':record['files'],'methods_per_block':len(names),'runners':3,'blocks_per_runner':3}))
if __name__=='__main__':main()
