"""Repair the exact observed owned-array argument reordering; retain the failed pair."""
from pathlib import Path
import importlib,json,hashlib
ROOT=Path(__file__).resolve().parents[1];E=ROOT/'evidence/round24';w=importlib.import_module('build-round18-start')
def fix_orders(l):
    changes={
        'slot.Z184_loop1_loop0_loop0 lc cost':'slot.Z184_loop1_loop0_loop0 cost lc',
        'slot.Z184_loop1_loop0_loop1 lc cost':'slot.Z184_loop1_loop0_loop1 cost lc',
        'slot.Z184_loop1_loop1 lc cost':'slot.Z184_loop1_loop1 cost lc',
        'slot.Z184_loop1_loop0 mb lc dc cost cl':'slot.Z184_loop1_loop0 mb dc cost lc cl',
        'slot.Z184_loop1 s mp mb p0 lit lc dc cost ch cl':'slot.Z184_loop1 s mp mb p0 lit dc cost ch lc cl',
        'slot.Z307_loop1_loop0 mb lc dc cost tail cl':'slot.Z307_loop1_loop0 mb dc cost tail lc cl',
        'slot.Z307_loop1 s mp mb p0 lit lc dc cost ch tail cl':'slot.Z307_loop1 s mp mb p0 lit dc cost ch tail lc cl',
    }
    for a,b in changes.items():assert l.count(a)==1,(a,l.count(a));l=l.replace(a,b)
    return l,changes
def main():
    parent=ROOT/'candidates/r24-609-a-packed-proof1';r=(parent/'parse.rs').read_text();l,changes=fix_orders((parent/'Parse.lean').read_text());f=E/'38102363209/gate-a-packed-proof1/exact-gate/exact-gate/extracted/Funs.lean';assert f.is_file()
    e=w.write_candidate('r24-609-a-packed-proof2',parent.name,r,l,'Repair sevenactualextracted argumentorders after lengthprice array becomes ownedlocal: cost/lc order inreductions andlc captureposition inouterloops. NoRust,verifier,axiomortimeoutchange.','Proof1failure preserved. Missingactualsignature migration, not a Rustcounterexample or fullcorrectness claim.',{'failed_gate':'evidence/round24/38102363209/gate-a-packed-proof1/exact-gate/exact-gate/gate-receipt.json','extracted_Funs':f.relative_to(ROOT).as_posix(),'Funs_sha256':hashlib.sha256(f.read_bytes()).hexdigest(),'argument_rewrites':changes,'proof':'DRAFT untilfreshoriginalfullgate.'})
    for n,d in [('gate-a-packed-proof2',{'r24_mode':'gate','candidate':e['name'],'path':e['path'],'files':e['hashes'],'expected_public_output_bytes':4864126}),('preflight-gate-a-packed-proof2',{'gap':'Proof1statementfails withtypeerrors because actualownedlc iscaptured aftercost/state ratherthan the oldborrowed-parameterposition. Allsevenmismatches arepresent inretainedFuns/logs.','change':'Only thoseexplicit theoremcall argumentorders; keepfailedpair andoriginal900sLeanpolicy.','minimum':'Freshoriginalcompleteverifier onexactsameRust/newLean pair.','decision':'Bind onlyacceptedpair; specific remainingerrors directboundedrepair. Candidateperformance stillonlydiscovery andprivateUNKNOWN.','cost_cap_runner_minutes':50,'evidence':'evidence/round24/<run>/gate-a-packed-proof2/exact-gate'})]:
        p=E/(n+'.json');assert not p.exists();p.write_bytes((json.dumps(d,indent=2)+'\n').encode())
    print(e['hashes'])
if __name__=='__main__':main()
