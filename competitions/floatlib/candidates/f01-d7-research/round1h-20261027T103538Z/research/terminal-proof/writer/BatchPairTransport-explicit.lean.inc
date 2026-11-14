/- R21 isolated post-freeze writer interface. NOT_RUN.
   Pairs are formed inside each batch; an odd final row is emitted separately. -/
namespace Submission.R21BatchPairTransport
open FloatLib.Floats Competition

theorem pair_rows_valid (m : Nat) (g : Fin (m/2)) : 2*g.val+1<m := by
  have hg := g.isLt
  have hm := Nat.div_add_mod m 2
  omega

theorem odd_tail_valid (m : Nat) (h : m%2=1) : 2*(m/2)<m := by
  have hm := Nat.div_add_mod m 2
  omega

theorem pair_fold_prefix (f : Nat → Binary32) (start m p : Nat)
    (step : Array Binary32 → Fin (m/2) → Array Binary32)
    (hstep : ∀ (g : Fin (m/2)) (acc : Array Binary32),
      RowStream.Prefix f (start+2*g.val*p) acc →
        RowStream.Prefix f ((start+2*g.val*p)+2*p) (step acc g))
    (out : Array Binary32) (hout : RowStream.Prefix f start out) :
    RowStream.Prefix f (start+2*(m/2)*p) (Fin.foldl (m/2) step out) := by
  exact RowStream.foldl_inv (β := Array Binary32) (m/2) step
    (fun g acc => RowStream.Prefix f (start+2*g*p) acc)
    (by
      intro g acc hacc
      have hs := hstep g acc hacc
      have hnext : (start+2*g.val*p)+2*p=start+2*(g.val+1)*p := by
        simp only [Nat.mul_add, Nat.add_mul, Nat.mul_one, Nat.add_assoc]
      simpa only [hnext] using hs)
    out (by simpa only [Nat.mul_zero, Nat.zero_mul, Nat.add_zero] using hout)

theorem pairs_then_tail_prefix (f : Nat → Binary32) (start m p : Nat)
    (step : Array Binary32 → Fin (m/2) → Array Binary32)
    (hstep : ∀ (g : Fin (m/2)) (acc : Array Binary32),
      RowStream.Prefix f (start+2*g.val*p) acc →
        RowStream.Prefix f ((start+2*g.val*p)+2*p) (step acc g))
    (readTail : Fin p → Binary32)
    (hTail : m%2=1 → ∀ j, readTail j=f (start+2*(m/2)*p+j.val))
    (out : Array Binary32) (hout : RowStream.Prefix f start out) :
    RowStream.Prefix f (start+m*p)
      (if m%2=1 then RowStream.emit p readTail (Fin.foldl (m/2) step out)
       else Fin.foldl (m/2) step out) := by
  have hpairs := pair_fold_prefix f start m p step hstep out hout
  by_cases hm : m%2=1
  · rw [if_pos hm]
    have htail := RowStream.emit_prefix f (start+2*(m/2)*p) p readTail
      (Fin.foldl (m/2) step out) hpairs (hTail hm)
    have hsplit : 2*(m/2)+1=m := by
      have h := Nat.div_add_mod m 2
      omega
    have hcursor : (start+2*(m/2)*p)+p=start+m*p := by
      calc
        (start+2*(m/2)*p)+p = start+(2*(m/2)+1)*p := by
          simp only [Nat.add_mul, Nat.one_mul, Nat.add_assoc]
        _ = start+m*p := congrArg (fun x : Nat => start+x*p) hsplit
    simpa only [hcursor] using htail
  · rw [if_neg hm]
    have hrem : m%2=0 := by
      have h := Nat.mod_lt m (by decide : 0<2)
      omega
    have hsplit : 2*(m/2)=m := by
      have h := Nat.div_add_mod m 2
      omega
    have hcursor : start+2*(m/2)*p=start+m*p :=
      congrArg (fun x : Nat => start+x*p) hsplit
    simpa only [hcursor] using hpairs

end Submission.R21BatchPairTransport
