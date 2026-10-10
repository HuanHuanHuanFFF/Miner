"""Migrate actual O extraction and discriminate the minimized L extraction failure."""
from pathlib import Path
import hashlib,importlib,json,random
ROOT=Path(__file__).resolve().parents[1];E=ROOT/'evidence/round24'
w=importlib.import_module('build-round18-start');fn=importlib.import_module('prepare-round24-extract-repro').fn
def save(p,d):
    assert not p.exists();p.write_bytes((json.dumps(d,indent=2)+'\n').encode())
def main():
    p=ROOT/'candidates/r24-609-inline-slot';r=(p/'parse.rs').read_text();l=(p/'Parse.lean').read_text()
    helpers='''@[local step]
theorem SFslot_encode_spec (count : Std.Usize) (first : Std.U32) (begin : Std.Usize) :
 slot.SFslot_encode count first begin ⦃ fun _ => True ⦄ := by
 rw [slot.SFslot_encode]
 step*
 repeat' (split <;> step*)
 all_goals scalar_tac

@[local step]
theorem SFrelax_token_spec (rm : Array Std.U64 4096#usize) (ct : Array Std.U32 1024#usize) (bend : Array Std.U32 512#usize) (i : Std.Usize) (t : Std.U32) (bc : Std.U64) (bt : Std.U32) :
 slot.SFrelax_token rm ct bend i t bc bt ⦃ fun _ => True ⦄ := by
 rw [slot.SFrelax_token]
 step*
 repeat' (split <;> step*)
 all_goals scalar_tac

'''
    marker='@[local step]\ntheorem SFsmallmatches_loop0_loop1_spec';assert l.count(marker)==1;l=l.replace(marker,helpers+marker)
    for n in ['SFsmallmatches_loop0_loop1','SFmorematches_loop0_loop1']:
        a=l.index('theorem '+n+'_spec');b=l.index('\n@[local step]',a);s=l[a:b]
        s=s.replace('(count : Std.Usize) (c : Std.Usize)', '(count : Std.Usize) (seen : Std.Usize) (first : Std.U32) (c : Std.Usize)')
        s=s.replace('count c ⦃','count seen first c ⦃').replace('4 - q.2.val','4 - q.2.2.2.val').replace('⟨items1, c1⟩','⟨items1, seen1, first1, c1⟩')
        l=l[:a]+s+l[b:]
    o=w.write_candidate('r24-609-inline-slot-proof1',p.name,r,l,'Proof-only migration against the actual O extracted Funs, including new helper specs and four-component retention loop states.','Same Rust as O; not another optimization candidate.',{'extraction':'evidence/round24/38087248563/proof-p-extract/diagnostics/research5/r24-609-inline-slot/Funs.lean','proof':'DRAFT until original complete gate.'})
    assert o['hashes']['parse.rs']==hashlib.sha256((p/'parse.rs').read_bytes()).hexdigest()
    save(E/'gate-slot-proof1.json',{'r24_mode':'gate','candidate':o['name'],'path':o['path'],'files':o['hashes'],'expected_public_output_bytes':4864126})
    save(E/'preflight-gate-slot-proof1.json',{'gap':'Actual O extraction succeeded but inherited proof has changed signatures. Need original all-stage acceptance for this exact pair.','change':'Only Lean helpers and actual extracted loop parameter/state migration.','minimum':'One unmodified original public verifier, including extraction,900s Lean obligation/axioms and roundtrip.','decision':'Actual errors drive bounded repair; a passed gate is correctness evidence only, not timing or a second candidate.','cost_cap_runner_minutes':50,'evidence':'evidence/round24/<run>/gate-slot-proof1/diagnostics/exact-gate'})
    p=ROOT/'candidates/r24-609-buffer-frontier';r=(p/'parse.rs').read_text();l=(p/'Parse.lean').read_text();old=fn(r,'SFroom')
    split='''pub fn SFroom(best:&[u32;4],codes:&[usize;4],t:u32,ct:&[u32;1024])->usize {
 let nc=ct[Z353(SFdist(t)).wrapping_add(512)%1024];let nl=SFlen(t);let mut i=0usize;
 while i<4 {
  let c=ct[codes[i%4].wrapping_add(512)%1024];let l=SFlen(best[i%4]);
  if (nc<=c && nl>=l && (nc<c || nl>l)) || !SFfastkeep(best,codes,4,i,ct) {return i;}
  i+=1;
 }4
}
'''
    assert r.count(old)==1;r=r.replace(old,split)
    e=w.write_candidate('r24-609-buffer-split',p.name,r,l,'Factor the inner existing-slot dominance test through the already extracted SFfastkeep helper. Preserve the first replaceable slot.','Extraction repair hypothesis, not a new quality policy. Native equivalence and full gate remain required.',{'parent':p.name,'red':'evidence/round24/38088860305/repro-s-extract/diagnostics/research5/research.json','proof':'DRAFT; wait for actual extracted interfaces.'})
    e.update(anchor='public609',comparison_baseline='buffer-original',native_decode_reference='buffer-original',expected_equivalent_to='buffer-original')
    base=json.loads((E/'buffer-l-native.json').read_bytes());base.pop('r24_buffer_counts',None)
    parent=w.control('buffer-original',str(p.relative_to(ROOT)).replace('\\','/'),'609');parent['anchor']='public609'
    base['entries']=[x for x in base['entries']if x['control']]+[parent,e]
    base.update(native_encoder_references=['public609','once','buffer-original'],description='T equivalent source-structure repair of L; original encoder tokens/bytes/decode, not a new score.')
    ns=[x['name']for x in base['entries']];base['screen_orders']=[ns,ns[::-1]];save(E/'split-t-native.json',base)
    # Same minimized shell: constant control, and nested loops with no early return.
    mini=(E/'extraction-repro/sfroom-only/parse.rs').read_text()
    flag=old.replace('let mut i=0usize;','let mut answer=4usize;let mut i=0usize;').replace('while i<4 {','while i<4 && answer==4 {').replace('{return i;}','{answer=i;}').replace('while j<4 {','while j<4 && answer==4 {').replace(' }4\n}',' }answer\n}')
    assert 'return' not in flag and 'answer\n}' in flag
    const='pub fn SFroom(best:&[u32;4],codes:&[usize;4],t:u32,ct:&[u32;1024])->usize {4}\n'
    entries=[]
    for name,new in [('sfroom-constant',const),('sfroom-flag',flag)]:
        dest=E/'extraction-repro'/name;dest.mkdir();data={'parse.rs':mini.replace(old,new).encode(),'Parse.lean':b'import Lz77\n-- Debug fixture only.\n'}
        for f,b in data.items():(dest/f).write_bytes(b)
        entries.append({'name':'debug-'+name,'path':dest.relative_to(ROOT).as_posix(),'control':False,'debug_fixture':True,'anchor':'public609','hashes':{f:hashlib.sha256(b).hexdigest()for f,b in data.items()}})
    spec=json.loads((E/'repro-s-extract.json').read_bytes());spec['entries']=[x for x in spec['entries']if x['control']]+[parent,e]+entries
    spec.update(extract_candidates=[e['name']]+[x['name']for x in entries],description='T ranked hypotheses: nested early return, nested loop itself, or shared minimal shell. Constant/flag fixtures plus full split helper discriminate without claiming a cause yet.')
    spec['screen_orders']=[[x['name']for x in spec['entries']]];save(E/'repair-t-extract.json',spec)
    save(E/'preflight-t.json',{'gap':'Original L fails twice and its two reduced fixtures fail in under1second with no detailed error. O extraction in P succeeds.','ranked_hypotheses':['Nested nonlocal return is unsupported; flag and split pass while original fails.','Nested loop itself causes translation failure; split passes, flag fails.','Shared reduced shell or basic operations fail; constant control also fails.','Full source context adds another independent issue; reduced flag passes but fullsplit fails.'],'change':'Equivalent helper factoring plus two controlled reduced fixtures, preserving original failing sources.','minimum':'Three original stage-extract invocations on one prepared runner; original28file encoder equality on a separate native runner.','decision':'Use red/green discriminator and exact emitted interfaces; do not equate workaround success with compiler root-cause proof.','cost_cap_runner_minutes':55,'native_cost_cap_runner_minutes':15,'evidence':'evidence/round24/<run>/repair-t-extract and split-t-native'})
    print('O_PROOF1_AND_T_FROZEN',o['hashes'],e['hashes'])
if __name__=='__main__':main()
