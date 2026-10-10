"""Compact SF predecessor distances and build them in one pass, preserving zero sentinel."""
from pathlib import Path
import importlib.util,json,re
ROOT=Path(__file__).resolve().parents[1]
E=ROOT/'evidence/round21'
def main():
 sp=importlib.util.spec_from_file_location('w',ROOT/'scripts/build-round18-start.py');w=importlib.util.module_from_spec(sp);sp.loader.exec_module(w)
 entries=[]
 for parent,name,anchor in [('candidates/r19-sf-nooverlap','r21-sf-prevdist16','base603'),('references/round21-public-608','r21-608-prevdist16','public608')]:
  p=ROOT/parent;r,l=[(p/f).read_text()for f in ('parse.rs','Parse.lean')]
  get='q9_get'if anchor=='base603'else'Z168'
  start=r.index('pub fn SFprev(');end=r.index('pub fn SFpositions(',start)
  new='''pub fn SFprev_get(v:&[u16],p:usize)->u32 {
 if p<v.len(){let d=v[p] as usize;if d>0&&d<=p{p.wrapping_add(1).wrapping_sub(d) as u32}else{0}}else{0}
}
pub fn SFprev(input:&[u8])->Vec<u16> {
 let mut v:Vec<u16>=Vec::with_capacity(input.len());let mut head=[0u32;65536];let mut p=0usize;
 while p<input.len(){let h=SFhash(input,p)%65536;let cur=head[h] as usize;let d=p.wrapping_add(1).wrapping_sub(cur);
 v.push(if cur>0&&d>0&&d<=32768{d as u16}else{0});head[h]=(p as u32).wrapping_add(1);p+=1;}v
}

'''
  r=r[:start]+new+r[end:]
  assert r.count('prev:&[u32]')==2;r=r.replace('prev:&[u32]','prev:&[u16]')
  assert r.count(f'{get}(prev,p)')==1 and r.count(f'{get}(prev,j)')==1
  r=r.replace(f'{get}(prev,p)','SFprev_get(prev,p)').replace(f'{get}(prev,j)','SFprev_get(prev,j)')
  # SF search helpers only carry totality contracts; emitter still checks every match.
  a=l.index('theorem SFprev_loop_spec');b=l.index('theorem SFpositions_loop_spec',a)
  part=l[a:b].replace('alloc.vec.Vec Std.U32','alloc.vec.Vec Std.U16')
  l=l[:a]+part+l[b:]
  for term in ['theorem SFlookup_spec','theorem SFsmallmatches_loop0_loop0_spec','theorem SFsmallmatches_loop0_spec','theorem SFsmallmatches_spec','theorem SFshape_loop0_spec']:
   a=l.index(term);b=l.index(' := by',a)if ' := by' in l[a:]else a
   # Header-only replacements avoid changing unrelated original token vectors.
   head=l[a:b];head=head.replace('(prev : Slice Std.U32)','(prev : Slice Std.U16)').replace('(prev : alloc.vec.Vec Std.U32)','(prev : alloc.vec.Vec Std.U16)');l=l[:a]+head+l[b:]
  proof='''@[local step]
theorem SFprev_get_spec (v : Slice Std.U16) (p : Std.Usize) :
 slot.SFprev_get v p ⦃ fun _ => True ⦄ := by
 rw [slot.SFprev_get]
 step*
 repeat' (split <;> step*)
 all_goals scalar_tac

'''
  marker='@[local step]\ntheorem SFprev_loop_spec';assert l.count(marker)==1;l=l.replace(marker,proof+marker)
  e=w.write_candidate(name,p.name,r,l,
   'Replace full-input32-bit absolute SF predecessors with16-bit legal backward distances; zero remains no predecessor. Push distances during hashing to remove the separate zero-fill pass. Reconstruct at guarded lookup; far predecessors are discarded exactly where old search stopped.',
   'R19 shared match caches increased lifecycle overhead and mostly covered existing candidates. This changes predecessor representation and construction, preserving matching search policy. Unlike modular hints, explicit distancezero avoids wrap alias. Proof is a type-adapted draft until fresh extraction/gate.',
   {'parent':parent,'mechanism_evidence':'evidence/round19/38042741551/profile-b-native/diagnostics/r18-functions/functions.json','ownership':'Original public source authors retained; derived representation change.'})
  e.update(anchor=anchor,comparison_baseline=anchor,native_decode_reference=anchor);entries.append(e)
 s=json.loads((E/'probe-c2-native.json').read_bytes());s['entries']=[e for e in s['entries']if e.get('control')]+entries;s['native_encoder_references']=['base603','public608','nooverlap'];ns=[e['name']for e in s['entries']];s['screen_orders']=[ns,ns[::-1]];s['description']='R21 D original encoding and decode for compact explicit-distance SF predecessor storage. Two baselines, two representation candidates,6native methods. Quality equality remains finite evidence.'
 (E/'probe-d-native.json').write_bytes((json.dumps(s,indent=2)+'\n').encode());(E/'preflight-d.json').write_bytes((json.dumps({'gap':'SFsmallmatches is material in prior diagnostics; full-input predecessor array uses4B perposition and two write passes. Need real total-time savings while preserving expensive quality.','change':'Legal16-bitdistance storage, explicitzero sentinel, onepass construction, unchanged search/match validation.','minimum':'Realoriginal28file encoder/decode and exact tokens versus ownsameparent; 6methodnativecap prechecked.','decision':'Ifsamebytes, evaluate original paired total time against publicformal603/608 and precise localparents. If quality changes, diagnose first; no blind promotion.','cost_cap_minutes':20,'proof_risk':'Newguarded getter and VecU16 loop types; proofdraft must survive original extraction.','evidence':'evidence/round21/<run>/probe-d-native/diagnostics'},indent=2)+'\n').encode());print([e['name']for e in entries])
if __name__=='__main__':main()
