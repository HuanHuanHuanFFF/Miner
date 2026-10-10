"""Build bounded R23 infrastructure and exact combination input before dispatch."""
from pathlib import Path
from datetime import datetime,timezone,timedelta
import hashlib,json
ROOT=Path(__file__).resolve().parents[1];E=ROOT/'evidence/round23'

def save(path,data):path.write_bytes((json.dumps(data,indent=2,ensure_ascii=False)+'\n').encode())

def main():
    E.mkdir(exist_ok=True);assert not (E/'budget.json').exists()
    start=datetime.fromisoformat('2026-10-10T17:38:14+00:00');deadline=start+timedelta(minutes=50);bjt=timezone(timedelta(hours=8))
    save(E/'budget.json',{'start_utc':start.isoformat(),'deadline_utc':deadline.isoformat(),'start_bjt':start.astimezone(bjt).isoformat(),'deadline_bjt':deadline.astimezone(bjt).isoformat(),'budget_minutes':50,'objective':'Continue single>=10percentcompetitionrewardpool, conditionalpublicprojections only; formalpayabilityUNKNOWN.','baseline_main_sha':'da8a102dcd6245e6b935387fc6cb55496838a3ef','baseline_research_sha':'3ccbc7d4e217575d34fbf6d15f4cabd85ac0d315','branch':'codex/round23-tenpct','confirmation_reserve_minutes':20,'previous_round':'R22closedhour retainedunchanged; explicitnew50minuteuserauthorization.','authorization':'Research,necessarypublicrunnerverification,experimentalbranchcommits/pushes; no officialupload,registration,signingorfinancialactions.','status':'ACTIVE'})
    for name in ('dispatch','round-preflight','verify-exact','bind-gate','capture-frontier','audit'):
        src={'dispatch':'dispatch-round22.py','round-preflight':'round22-preflight.py','verify-exact':'verify-round22-exact.py','bind-gate':'bind-round22-gate.py','capture-frontier':'capture-round22-frontier.py','audit':'audit-round22.py'}[name]
        data=(ROOT/'scripts'/src).read_bytes().replace(b'round22',b'round23').replace(b'ROUND22',b'ROUND23').replace(b'R22',b'R23').replace(b'r22-',b'r23-').replace(b'r22_',b'r23_')
        (ROOT/'scripts'/src.replace('round22','round23')).write_bytes(data)
    p=ROOT/'.github/workflows/deflate-round9.yml';s=p.read_text()
    assert "'21', '22']" in s and '\n  round23:' not in s
    s=s.replace("'21', '22']","'21', '22', '23']").replace("inputs.experiment_round != '22'","inputs.experiment_round != '22' && inputs.experiment_round != '23'",1)
    block=s[s.index('\n  round22:'):]
    s+=block.replace('round22','round23').replace('ROUND22','ROUND23').replace("== '22'","== '23'").replace('r22-','r23-');p.write_bytes(s.encode())
    p=ROOT/'scripts/round4.py';s=p.read_text();old="'evidence/round21', 'evidence/round22')";assert s.count(old)==1;p.write_bytes(s.replace(old,"'evidence/round21', 'evidence/round22', 'evidence/round23')").encode())
    p=ROOT/'scripts/collect-round4.py';s=p.read_text();old="'21', '22'], default='4'";assert s.count(old)==1;p.write_bytes(s.replace(old,"'21', '22', '23'], default='4'").encode())
    prior=json.loads((ROOT/'evidence/round22/highest-potential.json').read_bytes());source=ROOT/prior['path']
    assert {f:hashlib.sha256((source/f).read_bytes()).hexdigest() for f in prior['files']}==prior['files']
    save(E/'gate-combo.json',{'r23_mode':'gate','candidate':prior['candidate'],'path':prior['path'],'files':prior['files'],'expected_public_output_bytes':5332621,'description':'Exact frozen R22combination with one>=10percentblock under bothcontrols and onezero. Neworiginalextract/obligation/axioms/roundtrip mandatory; unchangedLean text doesnot inheritparentRust acceptance.'})
    save(E/'preflight-a.json',{'gap':'R22combo hasoneblock16.67/16.35percent and anotherzero; exactfullgate and freshindependentconfirmation notrun. Highwindow partlybelowobservedvariance.','substantial_change':'Preserve exactRust/Lean, neworiginalfullgate and new independentrunner opportunity; no renamedcandidate and no inventedgain.','minimum':'Original fullgate of frozen twofilepair, currentofficialfrontier snapshot and lowcostperblockscoring replay; reserve twofreshrunner confirmations afteracceptedpair.','decision':'Ifaccepted, newpaired originalprotocol confirmation; ifproofrejected repairboundedly onnewproofdirectory. Ifhighsignalsstillconflict, matchedrep20orderdiagnostic while preservingoriginalscores. Noformalupload.','cost_cap_minutes':{'gate_combo':22,'independent_confirmation_each':16,'matched_order_diagnostic':18},'evidence':'evidence/round23/<run>/gate-combo and frozenconfirmation receipts','fixed_deadline_utc':deadline.isoformat()})
    print('R23_FROZEN',start.isoformat(),deadline.isoformat(),prior['files'])

if __name__=='__main__':main()
