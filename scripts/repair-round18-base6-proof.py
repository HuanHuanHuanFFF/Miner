"""Repair the exact gate's six table-index bounds and nested slot totality."""
from pathlib import Path
import hashlib,importlib.util,json

ROOT=Path(__file__).resolve().parents[1]

def main():
    p=ROOT/'candidates/r18-dna-base6';rust=(p/'parse.rs').read_bytes();proof=(p/'Parse.lean').read_text()
    assert hashlib.sha256(rust).hexdigest()=='f5c1437c6e613a5a3c0740d590ac7ce972a24b86d963122c6ace3c576c3a98fd'
    a=proof.index('theorem slot_of_m_spec',proof.index('\nnamespace PC\n'));b=proof.index('@[local step]',a);part=proof[a:b]
    old='''  rw [slot.pc_slot_of_m]
  have hmax : s.length ≤ Std.Usize.max := Std.Slice.length_ineq s
  step*
'''
    new='''  rw [slot.pc_slot_of_m]
  have hmax : s.length ≤ Std.Usize.max := Std.Slice.length_ineq s
  have htab : slot.R18_DNA_DIGIT.length = 256 := slot.R18_DNA_DIGIT.property
  step*
  all_goals try (
    rw [htab]
    subst_vars
    simp_all only [UScalar.cast_val_eq, UScalar.val_and]
    exact Nat.lt_of_le_of_lt (Nat.mod_le _ _) (Nat.lt_succ_of_le Nat.and_le_right))
  all_goals try
    apply WP.spec_bind (Pₘ := fun (_ : Std.Usize) => True)
    · repeat' (split <;> step*)
      all_goals (scalar_tac (simpAllMaxSteps := 0))
    intro selected _
    step*
'''
    assert part.count(old)==1;proof=proof[:a]+part.replace(old,new)+proof[b:]
    sp=importlib.util.spec_from_file_location('builder',ROOT/'scripts/build-round18-start.py');m=importlib.util.module_from_spec(sp);sp.loader.exec_module(m)
    e=m.write_candidate('r18-dna-base6-proof1',p.name,rust.decode(),proof,
      'Same exact base6 Rust; repair only the Lean proof obligations reported by original gate1: masked64-bit-to-Usize table indices and the nested total slot-selection computation before moduloH.',
      'Gate1 atstage4 emitted six index-bound goals and one nested monadic continuation; extraction passed. The repair uses existing array-length property, cast modulo bound, Nat.and_le_right and explicit WP.spec_bind. No new axiom, statement, corpus, gate or Rust change. This is a proof revision of the same candidate, not a second optimization candidate.',
      {'parent':'candidates/r18-dna-base6/manifest.json','failure_receipt':'evidence/round18/37994890861/gate-base6-1/exact-gate/exact-gate/gate-receipt.json','repair_log':'evidence/round18/37994890861/gate-base6-1/exact-gate/exact-gate/logs/005-lake.log'})
    assert e['hashes']['parse.rs']==hashlib.sha256(rust).hexdigest();mp=ROOT/e['path']/'manifest.json';mf=json.loads(mp.read_bytes());mf['artifact_role']='PROOF_REVISION_SAME_RUST_NOT_DISTINCT_CANDIDATE';mp.write_bytes((json.dumps(mf,indent=2)+'\n').encode())
    E=ROOT/'evidence/round18';g=json.loads((E/'gate-base6-1.json').read_bytes());g.update(candidate=e['name'],path=e['path'],files=e['hashes'],scope='Original fullgate attempt2 for same frozenRust and repaired proof. Gate1 rawfailure preserved. This proof is uncompiled until currentgate confirms; formal/private/admission/payability remain unknown.');(E/'gate-base6-2.json').write_bytes((json.dumps(g,indent=2)+'\n').encode())
    c=json.loads((E/'confirm-at.json').read_bytes());oldname='r18-dna-base6'
    for i,entry in enumerate(c['entries']):
        if entry['name']==oldname:
            c['entries'][i]={**entry,**e,'anchor':'dna582','comparison_baseline':'dna582','native_decode_reference':'dna582'}
    c['screen_orders']=[[e['name']if n==oldname else n for n in row]for row in c['screen_orders']];c['description']+=' Finalproof revision1 is now staged; dispatch remains blocked until its exact original gate certificate exists.';(E/'confirm-at.json').write_bytes((json.dumps(c,indent=2)+'\n').encode());print(json.dumps(e))

if __name__=='__main__':main()
