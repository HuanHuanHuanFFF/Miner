"""Verify the final packages differ exactly in the intended bounded-search mechanism."""
from pathlib import Path
import difflib,hashlib,importlib,json
ROOT=Path(__file__).resolve().parents[1];E=ROOT/'evidence/round24';fn=importlib.import_module('prepare-round24-extract-repro').fn;decl=importlib.import_module('prepare-round24-tree-proof').decl
def sha(data):return hashlib.sha256(data).hexdigest()
def main():
    plan=json.loads((E/'confirm-final-plan.json').read_bytes());names=plan['candidates'];assert len(names)==2;paths=[ROOT/'candidates'/n for n in names];rust=[];lean=[]
    for n,p in zip(names,paths):
        assert {f:sha((p/f).read_bytes())for f in ['parse.rs','Parse.lean']}==plan['files'][n]
        cert=json.loads((p/'VERIFICATION.json').read_bytes());assert cert['files']==plan['files'][n]and cert['status']=='VERIFIED_EXACT_ORIGINAL_PUBLIC_GATE_PASSED';rust.append((p/'parse.rs').read_text());lean.append((p/'Parse.lean').read_text())
    changed_rust=['SFsmallmatches','SFmorematches'];expected=rust[0];changes=[]
    for n in changed_rust:
        a,b=fn(rust[0],n),fn(rust[1],n);assert a!=b and expected.count(a)==1;expected=expected.replace(a,b);changes.append({'rust_function':n,'A_sha256':sha(a.encode()),'B_sha256':sha(b.encode())})
    assert expected==rust[1],'Unexpected Rust change outside the two intended matcher loops'
    changed_lean=['SFsmallmatches_loop0_loop0_spec','SFmorematches_loop0_loop0_spec'];expected=lean[0]
    for n in changed_lean:
        a,b=decl(lean[0],n)[2],decl(lean[1],n)[2];assert a!=b and expected.count(a)==1;expected=expected.replace(a,b)
    assert expected==lean[1],'Unexpected Lean change outside the two actual loop-state proofs'
    out=E/'review-packages';diffs={}
    for f,texts in [('parse.rs',rust),('Parse.lean',lean)]:
        p=out/(f+'.A-to-B.diff');assert not p.exists();raw=''.join(difflib.unified_diff(texts[0].splitlines(keepends=True),texts[1].splitlines(keepends=True),fromfile=names[0]+'/'+f,tofile=names[1]+'/'+f,n=3)).encode();p.write_bytes(raw);diffs[f]={'path':p.relative_to(ROOT).as_posix(),'sha256':sha(raw)}
    result={'status':'VERIFIED_EXACT_INTENDED_FINAL_SOURCE_DELTA','frozen_utc':plan['frozen_utc'],'candidates':names,'files':plan['files'],'only_changed_rust_functions':changes,'only_changed_lean_theorems':changed_lean,'diffs':diffs,'mechanism':'B adds atmost2x originalSFpredecessor work onlywhile longestseed/foundmatch isbelow8bytes. OtherRustfunctions, tables, authorshipcomments and prooftext remainidentical toA. Thecorrespondingloopbound andlongeststate proofstatements arethe onlyLeanchanges.','scope':'Exacttext/file identity audit plusalreadyacceptedgate bindings. It isnot a newperformance or all-input optimization-equivalence proof; originalgate correctness andfreshconfirmation areseparate.'};p=out/'source-delta-audit.json';assert not p.exists();p.write_bytes((json.dumps(result,indent=2)+'\n').encode());print(json.dumps({'status':result['status'],'rust_functions':changed_rust,'lean_theorems':changed_lean,'diffs':diffs},indent=2))
if __name__=='__main__':main()
