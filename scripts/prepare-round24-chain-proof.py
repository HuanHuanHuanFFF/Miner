"""Migrate exact BF chain interfaces; default only drafts, never executes Lean."""
from pathlib import Path
import argparse,hashlib,importlib,json,re
ROOT=Path(__file__).resolve().parents[1];E=ROOT/'evidence/round24';w=importlib.import_module('build-round18-start');tree=importlib.import_module('prepare-round24-tree-proof')
HELPERS='''@[local step]
theorem r24_SFparent_spec (prev:Slice Std.U32) (p:Std.Usize) :
 slot.SFparent prev p ⦃ fun _ => True ⦄ := by
 rw [slot.SFparent]
 step*
 repeat' (split <;> step*)
 all_goals scalar_tac
@[local step]
theorem r24_SFchainlen_spec (input:Slice Std.U8) (prev:Slice Std.U32) (frm j p cap prior seed:Std.Usize) :
 slot.SFchainlen input prev frm j p cap prior seed ⦃ fun _ => True ⦄ := by
 rw [slot.SFchainlen]
 step*
 repeat' (split <;> step*)
 all_goals scalar_tac

'''
def make():
    p=ROOT/'candidates/r24-609-chain-lcp8';r=(p/'parse.rs').read_text();l=(p/'Parse.lean').read_text();fp=E/'38104761403/proof-bf-extract/diagnostics/research5'/p.name/'Funs.lean';f=fp.read_text();d=json.loads((fp.parent.parent/'research.json').read_bytes())['extractions'][p.name];assert d['extraction_accepted']and d['source_sha256']==hashlib.sha256(r.encode()).hexdigest()
    a=l.index('@[local step]\ntheorem SFmatchlen_loop_spec');b=l.index('@[local step]',l.index('theorem SFmatchlen_spec',a));matcher=l[a:b];l=l[:a]+l[b:];at=l.index('@[local step]\ntheorem SFprev_loop_spec');l=l[:at]+matcher+HELPERS+l[at:]
    for name,chain,pat,newpat in [('SFsmallmatches_loop0_loop0_spec','q.2.2.2','⟨best1, count1, q1, k1⟩','⟨best1, count1, q1, k1, frm1, prior1⟩'),('SFmorematches_loop0_loop0_spec','q.2.2.2.2','⟨best1, codes1, count1, q1, k1⟩','⟨best1, codes1, count1, q1, k1, frm1, prior1⟩')]:
        n=name.removesuffix('_spec');start=f.index('def '+n+'\n');actual=f[start:f.index('\n/--',start)];assert '(«from» : Std.Usize) (prior : Std.Usize)'in actual or '(«from» : Std.Usize)\n  (prior : Std.Usize)'in actual
        a,b,part=tree.decl(l,name);assert part.count('(k : Std.Usize):')==1 and part.count('q k ⦃')==1 and part.count('depth.val - '+chain+'.val')==1
        part=part.replace('(k : Std.Usize):','(k frm prior : Std.Usize):').replace('q k ⦃','q k frm prior ⦃').replace('depth.val - '+chain+'.val','depth.val - '+chain+'.1.val').replace(pat,newpat);l=l[:a]+part+l[b:]
    assert len(l.encode())<=524288;return r,l,fp
def main():
    ap=argparse.ArgumentParser();ap.add_argument('--freeze',action='store_true');a=ap.parse_args();r,l,fp=make()
    if not a.freeze:print(json.dumps({'status':'DRAFT_REAL_INTERFACES_NOT_LEAN_CHECKED','proof_bytes':len(l.encode())}));return
    e=w.write_candidate('r24-609-chain-lcp8-proof1','r24-609-chain-lcp8',r,l,'Move the existing totalmatcher proof before the newlydependent indexbuilder, add SFparent/SFchainlen totality and migrate actual BFfrom/prior loopstate fields.','SameRust as the measuredchaincandidate. Finitequery equality doesnotreplaceoriginalLZ77 obligation or freshgate.',{'extraction':fp.relative_to(ROOT).as_posix(),'Funs_sha256':hashlib.sha256(fp.read_bytes()).hexdigest(),'proof':'DRAFT untilfreshoriginalfullgate.'})
    for name,data in [('gate-chain-lcp8-proof1',{'r24_mode':'gate','candidate':e['name'],'path':e['path'],'files':e['hashes'],'expected_public_output_bytes':4864126}),('preflight-gate-chain-lcp8-proof1',{'gap':'Exactchaincandidate hasactualquery/publicparity andBFinterfaces, but newdependencies andchainstates needfullacceptance.','change':'Proof-only migration against emittedFuns, originalobligation and900sLean limitretained.','minimum':'Freshoriginalcompletegate for exactpair.','decision':'Bindacceptedexactpair only; performanceandindependentconfirmation remainseparate. Retainactualfailures anddo notextendfixedresearchdeadline.','cost_cap_runner_minutes':50,'evidence':'evidence/round24/<run>/gate-chain-lcp8-proof1/exact-gate'})]:
        p=E/(name+'.json');assert not p.exists();p.write_bytes((json.dumps(data,indent=2)+'\n').encode())
    print(e['hashes'])
if __name__=='__main__':main()
