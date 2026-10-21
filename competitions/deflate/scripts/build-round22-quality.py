"""Two distinct parsing mechanisms on newly public595, not a parameter sweep."""
from pathlib import Path
import importlib.util,json
ROOT=Path(__file__).resolve().parents[1]
E=ROOT/'evidence/round22'

def main():
    sp=importlib.util.spec_from_file_location('w',ROOT/'scripts/build-round18-start.py')
    w=importlib.util.module_from_spec(sp);sp.loader.exec_module(w)
    p=ROOT/'references/round21-public-595'
    r,l=[(p/f).read_text() for f in ('parse.rs','Parse.lean')]
    old='pub fn p125_row6(input:&[u8],out:&mut[u32])->usize{pc_run1::<65536>(input,out,6,0,1000000,4294967295)}'
    assert r.count(old)==1
    chain=r.replace(old,old.replace('pc_run1::<65536>(input,out,6,0,1000000,4294967295)','pc_run1c::<65536>(input,out,6,0,1000000,4294967295,1,4)'))
    oldproof='rw [slot.p125_row6]\n exact PC.run1_spec _ input out _ _ _ _ hlen (by simp) (by simp)'
    assert l.count(oldproof)==1
    chainproof=l.replace(oldproof,'rw [slot.p125_row6]\n exact PC.run1c_spec _ input out _ _ _ _ _ _ hlen (by simp) (by simp)')
    a=r.index('pub fn pc_fold_w(');b=r.index('\n}\n',a)+2
    head=r[a:r.index('{',a)+1]
    nofold=r[:a]+head+'\n    (nt0, p0, l0)\n}'+r[b:]
    old='⦄ := C12569! slot.pc_fold_w'
    assert l.count(old)==1
    nofoldproof=l.replace(old,'⦄ := by\n  rw [slot.pc_fold_w]\n  step*\n  all_goals exact ⟨hdec, hm, rfl, Nat.le_refl _⟩')
    variants=[('r22-595-row6-chain',chain,chainproof,'Add exactly one older bytevalidated match to original595 head-only route6 using the existing PC chain engine; preserve65536table, skip6, lazy0, folding and everyotherroute. Existingchainminimum4 reused, no new classifier.','R21 removed chain consumers from different539parent. This adds an actual matching capability to the newly public595 parent and tests measured quality versus overhead.'),('r22-595-nofold',nofold,nofoldproof,'Remove backward token folding in the shared PC helper while preserving match search, distance validation and output obligation; identity helper has a direct proof draft.','Historical nofold only applied to DNA582. This tests actual generic/structured PC routes of newly public595, not repeated DNA parameters. Byte/token cost can worsen while timing improves; replay both axes.')]
    entries=[]
    for name,rust,lean,mechanism,gap in variants:
        en=w.write_candidate(name,p.name,rust,lean,mechanism,gap,{'original_source':'references/round21-public-595/source-receipt.json','ownership':'Original595/514/590 provenance retained; chain engine inherited; identity proof adapted from existing R17 helper theorem.'})
        en.update(anchor='public595',comparison_baseline='public595',native_decode_reference='public595');entries.append(en)
    s=json.loads((E/'probe-b-native.json').read_bytes())
    s['entries']=[e for e in s['entries'] if e.get('control')]+entries
    s['r22_expected_candidates']=2
    s['description']='R22 D first actual native595 matching-depth and nofold tradeoffs; two structurally different mechanisms, original28file encoding/decode. Not a timing or full proof result.'
    ns=[e['name'] for e in s['entries']];s['screen_orders']=[ns,ns[::-1]]
    (E/'probe-d-native.json').write_bytes((json.dumps(s,indent=2)+'\n').encode())
    plan={'gap':'Initial three variants have identical595 output, so they depend entirely on narrow speed geometry. Test real parsing quality/time tradeoffs rather than allocating all budget to representations.', 'changes':[{'candidate':v[0],'mechanism':v[3],'difference':v[4]} for v in variants], 'minimum':'Original encoder and decoder on28 corpus files, exact595 comparison; inspect perfile tokens/bytes.', 'decision':'Use observed byte differences and current target geometry to allocate original total-time screening. Native quality regression alone is not a veto; same-source timing disagreement triggers measurement diagnosis. Full gate/confirmation reserved before deadline.', 'cost_cap_minutes':10,'evidence':'evidence/round22/<run>/probe-d-native/diagnostics','research_cutoff_utc':'2026-10-10T17:17:07+00:00'}
    (E/'preflight-d.json').write_bytes((json.dumps(plan,indent=2)+'\n').encode())
    print([e['name'] for e in entries])

if __name__=='__main__':main()
