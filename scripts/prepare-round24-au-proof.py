"""Migrate only observed AU interfaces; freezing does not imply Lean acceptance."""
from pathlib import Path
import argparse,hashlib,importlib,json
ROOT=Path(__file__).resolve().parents[1];E=ROOT/'evidence/round24';w=importlib.import_module('build-round18-start');tree=importlib.import_module('prepare-round24-tree-proof')
AP='''@[step]
theorem r24_APprices_loop_spec (src dst:Std.Array Std.U32 512#usize) (j:Std.Usize) :
 slot.APprices_loop src dst j ⦃ fun _ => True ⦄ := by
 rw [slot.APprices_loop]
 apply Std.loop.spec_decr_nat (measure := fun q => 512 - q.2.val) (inv := fun _ => True)
 · rintro ⟨dst1,j1⟩ _
   simp only [slot.APprices_loop.body]
   step*
   repeat' (split <;> step*)
   all_goals scalar_tac
 · trivial
@[step]
theorem r24_APprices_spec (src:Std.Array Std.U32 512#usize) :
 slot.APprices src ⦃ fun _ => True ⦄ := by
 rw [slot.APprices]
 step*

'''
ITEM='''@[local step]
theorem r24_SFpriceditem_spec (t:Std.U32) (ct:Array Std.U32 1024#usize) :
 slot.SFpriceditem t ct ⦃ fun _ => True ⦄ := by
 rw [slot.SFpriceditem]
 step*
 repeat' (split <;> step*)
 all_goals scalar_tac
@[local step]
theorem r24_SFitemprice_spec (t:Std.U32) :
 slot.SFitemprice t ⦃ fun _ => True ⦄ := by
 rw [slot.SFitemprice]
 step*

'''
def make(parent):
    p=ROOT/'candidates'/parent;r=(p/'parse.rs').read_text();fp=E/'38101365118/proof-au-extract/diagnostics/research5'/parent/'Funs.lean';f=fp.read_text();d=json.loads((fp.parent.parent/'research.json').read_bytes())['extractions'][parent];assert d['extraction_accepted'] and d['source_sha256']==hashlib.sha256(r.encode()).hexdigest()
    if parent.endswith('stack-adaptive'):
        base=ROOT/'candidates/r24-609-root-word-price-buffer-proof1';c=json.loads((base/'VERIFICATION.json').read_bytes());assert c['status']=='VERIFIED_EXACT_ORIGINAL_PUBLIC_GATE_PASSED';l=(base/'Parse.lean').read_text()
        for n,chain,pat,newpat in [('SFsmallmatches_loop0_loop0_spec','q.2.2.2','⟨best1, count1, q1, k1⟩','⟨best1, count1, q1, k1, longest1⟩'),('SFmorematches_loop0_loop0_spec','q.2.2.2.2','⟨best1, codes1, count1, q1, k1⟩','⟨best1, codes1, count1, q1, k1, longest1⟩')]:
            a,b,part=tree.decl(l,n);assert part.count('(k : Std.Usize):')==1 and part.count('q k ⦃')==1 and part.count('depth.val - '+chain+'.val')==1
            part=part.replace('(k : Std.Usize):','(k limit longest : Std.Usize):').replace('q k ⦃','q k limit longest ⦃').replace('depth.val - '+chain+'.val','limit.val - '+chain+'.1.val').replace(pat,newpat);l=l[:a]+part+l[b:]
        expected=4864065
    else:
        l=(p/'Parse.lean').read_text();expected=4864126
        if parent.endswith('a-packed'):
            assert 'def APprices_loop\n' in f;a,_,_=tree.decl(l,'u104');a=l.rfind('@[step]',0,a);l=l[:a]+AP+l[a:]
        elif parent.endswith('item-price'):
            marker='@[local step]\ntheorem SFsmallmatches_loop0_loop0_spec';assert l.count(marker)==1;l=l.replace(marker,ITEM+marker)
        else:raise AssertionError(parent)
    assert len(l.encode())<=524288;return r,l,fp,expected
def main():
    ap=argparse.ArgumentParser();ap.add_argument('parent',choices=['r24-609-a-packed','r24-609-item-price','r24-609-stack-adaptive']);ap.add_argument('--freeze',action='store_true');a=ap.parse_args();r,l,fp,expected=make(a.parent)
    if not a.freeze:print(json.dumps({'status':'DRAFT_ACTUAL_INTERFACE_MIGRATION_NOT_LEAN_CHECKED','candidate':a.parent,'proof_bytes':len(l.encode())}));return
    n=a.parent+'-proof1';e=w.write_candidate(n,a.parent,r,l,'Proof-only migration from the observedAUFuns: preservedcore or acceptedcomposition proof plus explicit newhelper/loopstate contracts.','SameRust as measurednative/standard source; not anotheroptimizationcandidate and notyetfullgate.',{'extraction':fp.relative_to(ROOT).as_posix(),'Funs_sha256':hashlib.sha256(fp.read_bytes()).hexdigest(),'proof':'DRAFT untiloriginalcompletegate.'})
    label='gate-'+a.parent.removeprefix('r24-609-')+'-proof1'
    for name,d in [(label,{'r24_mode':'gate','candidate':n,'path':e['path'],'files':e['hashes'],'expected_public_output_bytes':expected}),('preflight-'+label,{'gap':'NewexactRust hasactualnativeparity/qualityandoriginalextraction, but no completeacceptance for itsproof.','change':'Only proofmigration fromactualAUinterfaces, retaining originalobligation, axiompolicy and900sLeanlimit.','minimum':'Fresh unmodifiedoriginalpublicverifier androundtrip for exactpair.','decision':'Only acceptedpair getsboundcertificate. Retain failures andrepair exactproof ifuseful. Perfiletiming/finalfrozenconfirmation areseparate.','cost_cap_runner_minutes':50,'evidence':f'evidence/round24/<run>/{label}/exact-gate'})]:
        p=E/(name+'.json');assert not p.exists();p.write_bytes((json.dumps(d,indent=2)+'\n').encode())
    print(n,e['hashes'])
if __name__=='__main__':main()
