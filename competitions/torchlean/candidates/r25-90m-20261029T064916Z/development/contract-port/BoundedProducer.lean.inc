/-! Optional next producer interface; not part of the first frozen candidates.
Accept cache equality only on indices the actual dot loop visits. This permits
precomputed rows with bias/one sentinels and direct array lookup in the loop.
-/

theorem dotLoopCached_eq_bounded (fa fb : Nat → Word) (da db : Nat → DecodedWord)
    (limit : Nat) (ha : ∀ t, t < limit → da t = decodeWord (fa t))
    (hb : ∀ t, t < limit → db t = decodeWord (fb t))
    (pos neg : Array Nat) (sp nz : Bool) (index count : Nat)
    (hbound : index + count ≤ limit) :
    dotLoopCached da db pos neg sp nz index count = dotLoop fa fb pos neg sp nz index count := by
  induction count generalizing pos neg sp nz index with
  | zero => rfl
  | succ count ih =>
    rw [dotLoopCached, ha index (by omega), hb index (by omega),
      dotStepCached_decode, dotLoop]
    generalize dotStep ⟨pos, neg, sp, nz⟩ (fa index) (fb index) = r
    obtain ⟨p, n, s, z⟩ := r
    exact ih p n s z (index + 1) (by omega)

theorem dotCached_eq_bounded (n : Nat) (fa fb : Nat → Word) (da db : Nat → DecodedWord)
    (ha : ∀ t, t < n → da t = decodeWord (fa t))
    (hb : ∀ t, t < n → db t = decodeWord (fb t)) :
    dotCached n fa fb da db = dotFn n fa fb := by
  unfold dotCached dotFn
  rw [dotLoopCached_eq_bounded fa fb da db n ha hb _ _ _ _ 0 n (by omega)]
