"""Two different follow-ups: exact no-improvement stopping and sparse cost modeling."""
from pathlib import Path
import importlib,json
ROOT=Path(__file__).resolve().parents[1];E=ROOT/'evidence/round24';w=importlib.import_module('build-round18-start')
def main():
    p=ROOT/'candidates/r24-609-once';r,l=[(p/f).read_text() for f in ('parse.rs','Parse.lean')]
    old='let bits=SFcost(&trial);if bits<best{ts=trial;best=bits;}round+=1;'
    assert r.count(old)==1
    f=w.write_candidate('r24-609-tiny-converge',p.name,r.replace(old,'let bits=SFcost(&trial);if bits<best{ts=trial;best=bits;}else{break;}round+=1;'),l,
        'Stop the tiny token-reassignment loop after a non-improving deterministic trial. Its token stream, predecessor table, cost model and next search would otherwise remain unchanged; preserve every improving iteration.',
        'R18 exact-price DP convergence found no repeats in Z308. This concerns the separate newer SFtinytokens loop, with an explicit unchanged-state condition after rejection. Actual original-protocol per-file ratios identified tiny-app as a major equal-file contribution despite few absolute milliseconds.',
        {'source':'references/round24-public-609/source-receipt.json','parent':p.name,'measurement':'evidence/round24/38080816639/screen-b/gate/round1-r24-609-once.jsonl','prior_negative':'evidence/round18/repeat-e-decision.json'})
    f.update(anchor='public609',comparison_baseline='once',native_decode_reference='once',expected_equivalent_to='once')
    helper='''pub fn SFmodel_counts(fr:&mut[u32;320]) {
 let mut i=288usize;
 while i<318 {if fr[i]==0 {fr[i]=1;}i+=1;}
}

'''
    g=r.replace('pub fn SFtable(',helper+'pub fn SFtable(')
    needle='SFhist(ts,lo,hi,&mut fr);Z331(&mut fr,256,1);';assert g.count(needle)==1
    g=g.replace(needle,needle+'SFmodel_counts(&mut fr);')
    proof='''@[local step]
theorem SFmodel_counts_loop_spec (fr : Array Std.U32 320#usize) (i : Std.Usize) :
 slot.SFmodel_counts_loop fr i ⦃ fun _ => True ⦄ := by
 rw [slot.SFmodel_counts_loop]
 apply Std.loop.spec_decr_nat (measure := fun q => 318 - q.2.val) (inv := fun _ => True)
 · rintro ⟨fr1,i1⟩ _
   simp only [slot.SFmodel_counts_loop.body]
   step*
   repeat' (split <;> step*)
   all_goals scalar_tac
 · trivial
@[local step]
theorem SFmodel_counts_spec (fr : Array Std.U32 320#usize) :
 slot.SFmodel_counts fr ⦃ fun _ => True ⦄ := by
 rw [slot.SFmodel_counts]
 step*

'''
    pos=l.index('theorem SFtable');pos=l.rfind('@[local step]',0,pos);assert pos>=0
    gp=l[:pos]+proof+l[pos:]
    e=w.write_candidate('r24-609-distance-prior',p.name,g,gp,
        'Build the SF model with one pseudo-observation for each absent legal distance symbol before the existing Huffman model. Replace the discontinuous unseen15-bit proxy by the same code-construction mechanism used for observed symbols. Original actual encoder and final cost acceptance remain unchanged.',
        'Changes statistical modeling rather than search depth, repetitions or table capacity. Existing price hypotheses are not a guarantee; test whether actual final bytes improve on this exact new609quality parent before buying timing/proof.',
        {'source':'references/round24-public-609/source-receipt.json','parent':p.name,'model':'Laplace-style missing-category prior applied only to the SF distance model; no encoder changes','boundary':'Native observations do not establish private quality transfer.'})
    e.update(anchor='public609',comparison_baseline='once',native_decode_reference='once')
    s=json.loads((E/'seedtail-d-native.json').read_bytes());s['entries']=[x for x in s['entries'] if x['control']]+[f,e]
    s.update(r24_expected_candidates=2,r24_tiny_counts=True,native_encoder_references=['public609','once'],description='R24 F/G: exact fixed-point stopping in tiny-token refinement and a distinct unseen-distance model prior. First original28fileencode/decode plus native original-loop opportunity counts; each mechanism judged separately.')
    names=[x['name']for x in s['entries']];s['screen_orders']=[names,names[::-1]]
    (E/'refine-f-native.json').write_bytes((json.dumps(s,indent=2)+'\n').encode())
    plan={'gap':'Once609is29percentfaster thanoriginal609but projectszero atlatest29610; needs substantialfurtherimprovement. Largest equal-file time contributionis tiny-app, unlikeabsolute-total ranking.',
        'changes':['Exactnon-improvement stop in separateSFtinytokens loop; quantify actualrejection-withremaining-round count before timing.','Principled distancecost prior forabsent categories; trueencoding and finalcostacceptance decideswhether morequalityis obtained.'],
        'minimum':'Native fixed28fileencode and independentdecode versus exactonce609; equalityrequiredforstoppingvariant; recordoriginal-loop rejectedrepeat opportunities. Modelvariant permitschangedoutput and retainsnegativefiles.',
        'decision':'No rejectedrepeat -> do not spend originaltime on claimedconvergence speedup. Realquality change that altersrequiredtime -> original pairedscreen. Newproofhelper remainsdraft; independentconfirmation afterexactpairfreeze.',
        'cost_cap_runner_minutes':15,'evidence':'evidence/round24/<run>/refine-f-native/diagnostics','status':'PREDECLARED'}
    (E/'preflight-f.json').write_bytes((json.dumps(plan,indent=2)+'\n').encode());print(f['name'],e['name'])
if __name__=='__main__':main()
