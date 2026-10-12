"""Relocate one leading chain insertion to the complete matched suffix."""
from pathlib import Path
import hashlib
import json

ROOT=Path(__file__).resolve().parents[1]
NAME='r25-root-end4-budget'
PARENT=ROOT/'candidates/r25-astra-end4'
EXPECTED={'parse.rs':'03ec0aa4e617d622755e85324a9d4fbc77ef74e6572485b3170e2790681ed8e6',
          'Parse.lean':'4ff09d168269ae8d9c93e602496b01078d2d0ec80f27d6cd16041d91a76c70a6'}


def sha(data):return hashlib.sha256(data).hexdigest()


def positions(ins0,end,lim,budget,suffix):
    ins=ins0
    stop=min(end,ins0+budget,lim)
    writes=[]
    while ins<stop:
        writes.append(ins);ins+=1
    if suffix and end>=4 and ins<=end-4 and end-4<lim:
        writes.append(end-4)
    if ins+1<end:ins=end-1
    if ins<end and ins<lim:writes.append(ins)
    return writes


def main():
    plan=ROOT/'evidence/round25/cycle-n2-predeclared.json'
    assert plan.is_file()
    raw={f:(PARENT/f).read_bytes() for f in EXPECTED}
    assert {f:sha(v) for f,v in raw.items()}==EXPECTED
    text=raw['parse.rs'].decode()
    a=text.index('pub fn pc_f_record3<const H: usize>')
    b=text.index('/// `pc_run1` with chain links',a)
    body=text[a:b]
    assert body.count('pc_INS_MAX')==2
    original_start='    let mut ins = ins0;'
    inserted_start=original_start+'\n    // Relocate only when the complete suffix can replace an existing second head key.\n    let head_budget = if end >= 4 && ins0 < end - 4 && end - 4 < lim { 1usize } else { pc_INS_MAX };'
    assert body.count(original_start)==1
    changed=body.replace('pc_INS_MAX','head_budget').replace(original_start,inserted_start)
    rust=(text[:a]+changed+text[b:]).encode()
    assert (text[:a]+changed.replace(inserted_start,original_start).replace('head_budget','pc_INS_MAX')+text[b:]).encode()==raw['parse.rs']
    checked=reduced=moved=0
    for ins in range(12):
        for end in range(40):
            for lim in range(45):
                old=positions(ins,end,lim,2,False)
                eligible=end>=4 and ins<end-4 and end-4<lim
                new=positions(ins,end,lim,1 if eligible else 2,True)
                expected=sorted((set(old)-{ins+1})|{end-4}) if eligible else old
                assert new==expected and new==sorted(set(new)) and len(new)==len(old)
                assert all(0<=x<end and x<lim for x in new)
                if old:
                    assert old[0] in new
                if end-1 in old:assert end-1 in new
                reduced+=len(new)<len(old)
                moved+=new!=old
                checked+=1
    folder=ROOT/'candidates'/NAME
    assert not folder.exists();folder.mkdir()
    files={'parse.rs':rust,'Parse.lean':raw['Parse.lean']}
    assert all(0<len(v)<=524288 for v in files.values())
    for f,v in files.items():(folder/f).write_bytes(v)
    hashes={f:sha(v) for f,v in files.items()}
    manifest={'candidate':NAME,'parent':PARENT.name,'parent_hashes':EXPECTED,'hashes':hashes,
        'mechanism':'Conditionally relocate the second leading pc_f_record3 insertion to end-4 when that position can replace it in bounds; otherwise retain the originalcombo schedule. Retain first leading and valid crossing end-1 keys with the same update count. No shared constant or other engine changed.',
        'predeclaration':plan.relative_to(ROOT).as_posix(),
        'attribution':{'original_source':'references/round21-public-595/source-receipt.json',
                       'parent':'candidates/r25-astra-end4/manifest.json','headers':'All inherited author/source headers retained.'},
        'proof_status':'DRAFT_INHERITED_END4_PROOF_REQUIRES_FRESH_EXACT_GATE',
        'performance_status':'UNKNOWN','formal_submission_sent':False,
        'risks':['Removing one early key changes future matching and can lose quality.',
                 'Same or fewer logical updates does not imply faster total compression.',
                 'Finite position model is not a Rust or full-input correctness proof.']}
    (folder/'manifest.json').write_bytes((json.dumps(manifest,indent=2)+'\n').encode())
    audit={'status':'VERIFIED_SOURCE_SCOPE_AND_FINITE_POSITION_MODEL_ONLY','hashes':hashes,
        'parent_restored_by_reversing_one_local_budget_binding_and_two_uses':True,
        'finite_cases':checked,'cases_with_fewer_updates':reduced,'cases_with_different_positions':moved,
        'preserved_in_model':'Exact replacement of second head by eligible suffix; fallback is original schedule; first and valid crossingend-1, monotone unique positions and update count preserved',
        'not_verified':['Native Rust','Original encoder bytes','Timing','Lean','Full gate']}
    p=ROOT/'evidence/round25/n-source-preflight.json';assert not p.exists();p.write_bytes((json.dumps(audit,indent=2)+'\n').encode())
    print(json.dumps(audit,indent=2))


if __name__=='__main__':main()
