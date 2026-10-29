import ContractExact

/- Original R25 proof probe. NOT_COMPILED. No complete Kernel or runtime claim.
   This checks only the overflow predicate and the signed bucket recurrence.
   Raw32 decoding, common-base preparation, finite guards, zero signs and the
   ContractExact dotFn bridge must still be supplied by an integrating caller. -/
namespace R25CheckedBucket64

@[inline] def addChecked (a b : UInt64) : Option UInt64 :=
  let c := a + b
  if c < a then none else some c

/-- A successful machine addition has not lost a carry. -/
theorem addChecked_value (a b c : UInt64) (h : addChecked a b = some c) :
    c.toNat = a.toNat + b.toNat := by
  unfold addChecked at h
  split at h
  · cases h
  · rename_i hn
    cases h
    have ha := a.toNat_lt
    have hb := b.toNat_lt
    have hs : a.toNat + b.toNat < 2 ^ 64 := by
      simp only [UInt64.lt_iff_toNat_lt, UInt64.toNat_add] at hn
      omega
    rw [UInt64.toNat_add, Nat.mod_eq_of_lt hs]

structure State where
  pos : UInt64
  neg : UInt64

def State.total (s : State) : Int := (s.pos.toNat : Int) - s.neg.toNat

@[inline] def step (s : State) (negative : Bool) (m : UInt64) : Option State :=
  if negative then
    match addChecked s.neg m with
    | none => none
    | some n => some ⟨s.pos, n⟩
  else
    match addChecked s.pos m with
    | none => none
    | some p => some ⟨p, s.neg⟩

def termValue (t : Bool × UInt64) : Int :=
  if t.1 then -(t.2.toNat : Int) else (t.2.toNat : Int)

theorem step_value (s r : State) (negative : Bool) (m : UInt64)
    (h : step s negative m = some r) :
    r.total = s.total + termValue (negative, m) := by
  cases negative with
  | false =>
    cases hs : addChecked s.pos m with
    | none => simp [step, hs] at h
    | some p =>
      have hp := addChecked_value s.pos m p hs
      simp only [step, Bool.false_eq_true, if_false, hs] at h
      cases h
      simp only [State.total, termValue, Bool.false_eq_true, if_false]
      omega
  | true =>
    cases hs : addChecked s.neg m with
    | none => simp [step, hs] at h
    | some n =>
      have hn := addChecked_value s.neg m n hs
      simp only [step, if_true, hs] at h
      cases h
      simp only [State.total, termValue, if_true]
      omega

def foldChecked : List (Bool × UInt64) → State → Option State
  | [], s => some s
  | t :: ts, s =>
    match step s t.1 t.2 with
    | none => none
    | some next => foldChecked ts next

/-- Successful checked accumulation is exact without an assumed L1 bound. -/
theorem foldChecked_value (ts : List (Bool × UInt64)) (s r : State)
    (h : foldChecked ts s = some r) :
    r.total = s.total + (ts.map termValue).sum := by
  induction ts generalizing s with
  | nil =>
    simp only [foldChecked] at h
    cases h
    simp
  | cons t ts ih =>
    cases hs : step s t.1 t.2 with
    | none => simp [foldChecked, hs] at h
    | some next =>
      have hh : foldChecked ts next = some r := by simpa [foldChecked, hs] using h
      have htail := ih next hh
      have hhead := step_value s next t.1 t.2 hs
      have ht : (t.1, t.2) = t := by cases t; rfl
      rw [ht] at hhead
      simp only [List.map_cons, List.sum_cons]
      rw [htail, hhead]
      omega

end R25CheckedBucket64
