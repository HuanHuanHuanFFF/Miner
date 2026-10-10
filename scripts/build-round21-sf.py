"""Test per-block exact acceptance and seam-price alternatives, reusing one match cache."""
from pathlib import Path
import importlib.util,json
ROOT=Path(__file__).resolve().parents[1]
E=ROOT/'evidence/round21'
def main():
 sp=importlib.util.spec_from_file_location('w',ROOT/'scripts/build-round18-start.py');w=importlib.util.module_from_spec(sp);sp.loader.exec_module(w)
 entries=[]
 for parent,tag,trials in [('references/round21-public-608','608-accept',1),('references/round21-public-608','608-seambias',3),('candidates/r19-sf-nooverlap','603-seambias',3)]:
  p=ROOT/parent;r,l=[(p/f).read_text()for f in ('parse.rs','Parse.lean')]
  old='let mut lambda=0usize;let mut next=Vec::new();let mut found=false;\n   while lambda<1 {'
  assert r.count(old)==1
  r=r.replace(old,'let mut lambda=0usize;let mut next=Vec::new();let mut found=false;let mut best_score=SFcost(&ts);\n   while lambda<'+str(trials)+' {')
  old='let v=SFpatch(&ts,lo,hi,&ch);next=v;found=true;lambda+=1;'
  assert r.count(old)==1
  r=r.replace(old,'let v=SFpatch(&ts,lo,hi,&ch);let score=SFcost(&v);if score<best_score{best_score=score;next=v;found=true;}lambda+=1;')
  name='r21-sf-'+tag;e=w.write_candidate(name,p.name,r,l,
    'Score every patched block against the current full token stream before accepting. '+('Reuse fixed block match candidates for three seam-price objectives (unbiased,+1,-1 before seam); select exact SFcost improvement.'if trials>1 else'Unbiased repair only; isolates the contribution of strict per-block acceptance.'),
    'R19 tested scope/cache/depth. This changes acceptance objective and exposes dormant price-bias alternatives, keeping the same full-context matching.608 is a newly public composition; proof loop gains a score parameter and remains draft.',
    {'parent':parent+'/source-receipt.json'if parent.startswith('references')else parent+'/manifest.json','authorship':'Original public608/581 or603/586/591 retained','reference_release':'evidence/round21/public-refresh/receipt.json'})
  anchor='public608'if tag.startswith('608')else'base603';e.update(anchor=anchor,comparison_baseline=anchor,native_decode_reference=anchor);entries.append(e)
 a=json.loads((E/'probe-a-native.json').read_bytes());a['entries']=[e for e in a['entries']if e['name']in('probe3','r3-432-fast3','public432','public514')]
 a['entries'].append(w.control('public608','references/round21-public-608','608'));shadow={**a['entries'][-1],'name':'public608-shadow'};shadow.pop('formal_id');a['entries'].append(shadow)
 a['entries'].append(w.control('base603','candidates/r18-rf-sf-content-proof1','603'));a['entries'].append(w.control('nooverlap','candidates/r19-sf-nooverlap','603'));a['entries'][-1].pop('formal_id');a['entries'][-1]['anchor']='base603';a['entries']+=entries
 a['native_encoder_references']=['public608','base603','nooverlap'];a['description']='R21 C actual encoder/decode for newly public608 baseline and three exact acceptance/seam-bias quality mechanisms. Native duration not official score;25minute cap.';ns=[e['name']for e in a['entries']];a['screen_orders']=[ns,ns[::-1]]
 (E/'probe-c-native.json').write_bytes((json.dumps(a,indent=2)+'\n').encode())
 plan={'gap':'High-quality endpoint currently needs materially improved quality/time; former603 descendants are dominated.608 provides a new independently published composition with formaltime5.5982 but insufficientsize34.0948.','difference':'Per-block exact acceptance versus final-only acceptance; expose three existing seam price objectives using the same expensive matched candidates.','minimum':'Full28file original encoder/decode baseline and candidates, retain every per-file byte result.','decision':'Only useful quality changes earn original total-time and full proof-loop migration. No quality improvement stops the exact variant; changed cost means no proxy speed claim.','cap_runner_minutes':25,'confirmation_reserve_minutes':35,'evidence':'evidence/round21/<run>/probe-c-native/diagnostics','proof_gap':'Newbest_score loop parameter must be freshly extracted and adapted; cached proofs do not establish acceptance.'}
 (E/'preflight-c.json').write_bytes((json.dumps(plan,indent=2)+'\n').encode());print([e['name']for e in entries])
if __name__=='__main__':main()
