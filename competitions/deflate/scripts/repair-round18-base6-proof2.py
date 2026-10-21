"""Replace costly context simplification with local, bound-only key specs."""
from pathlib import Path
import hashlib,importlib.util,json

ROOT=Path(__file__).resolve().parents[1]

def main():
    parent=ROOT/'candidates/r18-dna-base6';rust=(parent/'parse.rs').read_bytes();proof=(parent/'Parse.lean').read_text()
    a=proof.index('theorem slot_of_m_spec',proof.index('\nnamespace PC\n'));start=proof.rfind('@[local step]',0,a);end=proof.index('@[local step]',a)
    signature=proof[a:proof.index(':= by',a)]
    replacement='''section R18KeyRange

theorem r18_key_and_bound (x y : Std.U64) :
    lift (x &&& y) ⦃ fun r => r.val ≤ y.val ⦄ := by
  simp only [lift, WP.spec_ok]
  simpa only [Std.UScalar.val_and] using (Nat.and_le_right : x.val &&& y.val ≤ y.val)

theorem r18_key_cast_bound (x : Std.U64) :
    lift (UScalar.cast .Usize x) ⦃ fun r => r.val ≤ x.val ⦄ := by
  simp only [lift, WP.spec_ok]
  rw [UScalar.cast_val_eq]
  exact Nat.mod_le _ _

theorem r18_key_lookup_total (i : Std.Usize) (hi : i.val < 256) :
    Std.Array.index_usize slot.R18_DNA_DIGIT i ⦃ fun _ => True ⦄ :=
  WP.spec_mono
    (Std.Array.index_usize_spec slot.R18_DNA_DIGIT i
      (Nat.lt_of_lt_of_eq hi slot.R18_DNA_DIGIT.property.symm))
    (fun _ _ => trivial)

attribute [local step] r18_key_and_bound r18_key_cast_bound r18_key_lookup_total

@[local step]
'''+signature+''':= by
  rw [slot.pc_slot_of_m]
  have hmax : s.length ≤ Std.Usize.max := Std.Slice.length_ineq s
  step*
  all_goals try
    apply WP.spec_bind (Pₘ := fun (_ : Std.Usize) => True)
    · repeat' (split <;> step*)
      all_goals (first | trivial | scalar_tac (simpAllMaxSteps := 0))
    intro selected _
    step*

end R18KeyRange
attribute [local step] slot_of_m_spec

'''
    proof=proof[:start]+replacement+proof[end:]
    sp=importlib.util.spec_from_file_location('builder',ROOT/'scripts/build-round18-start.py');m=importlib.util.module_from_spec(sp);sp.loader.exec_module(m)
    e=m.write_candidate('r18-dna-base6-proof2',parent.name,rust.decode(),proof,
      'Same exactRust; use three proved local helper specifications for U64mask bounds, cast non-increase and total digit-table lookup. Their step hints exist only inside the hash-range proof section; restore only the completed slot-range theorem afterward. Explicitly handle the nested total slot choice.',
      'Gate2 hit the original900second proof elaboration cap. Its broad simp_all is removed rather than increasing timeout or changing the gate. The three bounds are direct Nat.and_le_right/Nat.mod_le/array property proofs; original parse obligation and axiom policy remain intact. Same optimization candidate, proof revision only.',
      {'parent':'candidates/r18-dna-base6/manifest.json','timeout_receipt':'evidence/round18/37998658096/gate-base6-2/exact-gate/exact-gate/gate-receipt.json','helper_pattern_reference':'candidates/r18-586-selective-rf/Parse.lean:total_array_get,rf_and_usize,d3_cast_le'})
    assert e['hashes']['parse.rs']==hashlib.sha256(rust).hexdigest();p=ROOT/e['path']/'manifest.json';mf=json.loads(p.read_bytes());mf['artifact_role']='PROOF_REVISION_SAME_RUST_NOT_DISTINCT_CANDIDATE';p.write_bytes((json.dumps(mf,indent=2)+'\n').encode())
    E=ROOT/'evidence/round18';s=json.loads((E/'gate-base6-2.json').read_bytes());s.update(candidate=e['name'],path=e['path'],files=e['hashes'],scope='Original complete gate attempt3; sameRust with bounded-local-spec proof revision2. Gate1goals andgate2original900secondtimeout preserved. No increasedprooflimit, changedcontract or newaxiom. Confirmation waitsfor acceptedexactpair.');(E/'gate-base6-3.json').write_bytes((json.dumps(s,indent=2)+'\n').encode())
    c=json.loads((E/'confirm-at.json').read_bytes());old='r18-dna-base6-proof1'
    for i,x in enumerate(c['entries']):
        if x['name']==old:c['entries'][i]={**x,**e}
    c['screen_orders']=[[e['name']if x==old else x for x in row]for row in c['screen_orders']];c['description']='Fresh original-protocol jointconfirmation, fourblocks with base6proofrevision2 andselectiveRF, bothsamefamilyanchors andidenticalshadows. Exactaccepted Rust/Lean certificates requiredbydispatch guard. Gate2timedoutat900s; revision2removesbroadcontextsimplification, notthelimit. No source selection or modification during this confirmation. Cap60job-minutes, individual/jointconditionalgeometry frommatchedblocks.';(E/'confirm-at.json').write_bytes((json.dumps(c,indent=2)+'\n').encode());print(json.dumps(e))

if __name__=='__main__':main()
