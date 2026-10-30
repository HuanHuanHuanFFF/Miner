import ContractExact

/- Original small proof interface. UNCOMPILED: no acceptance is asserted.
   These roots do not cover real getters, metadata, finish, or all12. -/
namespace R28CrossSource

theorem affine_list (xs : List (Int × Int)) (p q : Int) :
    (xs.map (fun z => z.1*z.2)).sum
      - q*(xs.map Prod.fst).sum - p*(xs.map Prod.snd).sum
      + (xs.length : Int)*p*q =
    (xs.map (fun z => (z.1-p)*(z.2-q))).sum := by
  induction xs with
  | nil => simp
  | cons z zs ih =>
    simp only [List.map_cons, List.sum_cons, List.length_cons,
      Nat.cast_add, Nat.cast_one]
    nlinarith [ih]

theorem product_unsigned64 (u v ex ew : Nat)
    (hu : u < 2^(ex+1)) (hv : v < 2^(ew+1)) (he : ex+ew ≤ 62) :
    u*v < 2^64 := by
  calc
    u*v < 2^(ex+1)*2^(ew+1) := Nat.mul_lt_mul'' hu hv
    _ = 2^(ex+ew+2) := by rw [← Nat.pow_add]; congr 1; omega
    _ ≤ 2^64 := Nat.pow_le_pow_right (by decide) (by omega)

theorem cache_smallnat (u exponent : Nat) (he : exponent ≤ 39)
    (hu : u < 2^(exponent+1)) : u < 2^63 := by
  have h : 2^(exponent+1) ≤ 2^40 :=
    Nat.pow_le_pow_right (by decide) (by omega)
  have : u < 2^40 := lt_of_lt_of_le hu h
  exact lt_trans this (by norm_num)

theorem cached_sum_lt60 (n : Nat) (u : Fin n → Nat)
    (hn : n < 2^20) (hu : ∀ i, u i < 2^40) :
    (∑ i, u i) < 2^60 := by
  classical
  have hs : (∑ i, u i) ≤ n*2^40 := by
    calc
      (∑ i, u i) ≤ ∑ _i : Fin n, 2^40 :=
        Finset.sum_le_sum (fun i _ => (hu i).le)
      _ = n*2^40 := by simp
  have h := Nat.mul_lt_mul_of_pos_right hn (by norm_num : 0 < 2^40)
  norm_num at h
  exact lt_of_le_of_lt hs h

theorem unsigned128_step (h l p : UInt64) :
    let low := l+p
    (((h + (if low < l then 1 else 0)).toNat * 2^64 + low.toNat) % 2^128) =
      (h.toNat * 2^64 + l.toNat + p.toNat) % 2^128 := by
  have hh : h.toNat < 2^64 := UInt64.toNat_lt_size h
  have hl : l.toNat < 2^64 := UInt64.toNat_lt_size l
  have hp : p.toNat < 2^64 := UInt64.toNat_lt_size p
  dsimp only
  split_ifs with hc
  · have hc' : (l.toNat+p.toNat)%2^64 < l.toNat := by
      simpa only [UInt64.lt_iff_toNat_lt, UInt64.toNat_add] using hc
    simp only [UInt64.toNat_add, UInt64.toNat_one]
    omega
  · have hc' : ¬ (l.toNat+p.toNat)%2^64 < l.toNat := by
      simpa only [UInt64.lt_iff_toNat_lt, UInt64.toNat_add] using hc
    simp only [UInt64.toNat_add, UInt64.toNat_zero]
    omega

end R28CrossSource
