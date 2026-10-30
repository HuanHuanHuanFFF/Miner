import ContractExact

/- Original arithmetic bridge for the spatial transform. UNCOMPILED.
   This does not establish the actual cache producer or UInt64 loop refinement. -/
namespace R28SpatialWordBounds

def D : Int := 33554432

theorem split_identity (v u : Int) :
    (v % D)*u + D*((v / D)*u) = v*u := by
  have h := Int.emod_add_mul_ediv v D
  linear_combination u*h

theorem quotient_bound (v : Int) : |v / D|*D ≤ |v|+D := by
  have hr : 0 ≤ v % D := Int.emod_nonneg v (by decide)
  have hs : v % D < D := Int.emod_lt_of_pos v (by decide)
  have he : (v / D)*D = v-v%D := by
    have h := Int.emod_add_mul_ediv v D
    linarith
  calc
    |v / D|*D = |(v / D)*D| := by rw [abs_mul, abs_of_pos (show 0<D by decide)]
    _ = |v-v%D| := by rw [he]
    _ ≤ |v|+|v%D| := abs_sub _ _
    _ ≤ |v|+D := by rw [abs_of_nonneg hr]; omega

theorem high_term_bound (A B v u : Int)
    (hA : 0≤A) (hB : 0≤B) (hAB : A*B≤2^79) (hBmax : B≤2^30)
    (hv : |v|≤4*A) (hu : |u|≤9*B) :
    |(v / D)*u| ≤ 36*2^54+9*2^30 := by
  have hq := quotient_bound v
  have hQ : |v / D|*D≤4*A+D := hq.trans (by omega)
  have huB : 0≤9*B := by omega
  have hmul : (|v / D|*D)*|u| ≤ (4*A+D)*(9*B) :=
    mul_le_mul hQ hu (abs_nonneg _) (by unfold D; omega)
  have hR : (4*A+D)*(9*B) ≤ 36*2^79+9*2^30*D := by
    unfold D at *
    nlinarith
  rw [abs_mul]
  unfold D at *
  norm_num at hR ⊢
  nlinarith

theorem low_term_bound (B v u : Int) (hB : 0≤B) (hBmax : B≤2^30)
    (hu : |u|≤9*B) : |(v%D)*u| ≤ 9*2^55 := by
  have hr : 0≤v%D := Int.emod_nonneg v (by decide)
  have hs : v%D≤D := (Int.emod_lt_of_pos v (by decide)).le
  have hu' : |u|≤9*2^30 := hu.trans (by omega)
  rw [abs_mul, abs_of_nonneg hr]
  have h := mul_le_mul hs hu' (abs_nonneg u) (show 0≤D by decide)
  norm_num [D] at h ⊢
  exact h

def prefix (f : Nat → Int) : Nat → Int
  | 0 => 0
  | n+1 => prefix f n+f n

theorem abs_prefix (f : Nat → Int) (B : Int) (n : Nat)
    (h : ∀ i, i<n → |f i|≤B) : |prefix f n|≤(n:Int)*B := by
  revert h
  induction n with
  | zero => intro h; simp [prefix]
  | succ n ih =>
    intro h
    calc
      |prefix f (n+1)| = |prefix f n+f n| := rfl
      _ ≤ |prefix f n|+|f n| := abs_add _ _
      _ ≤ (n:Int)*B+B := add_le_add (ih (fun i hi=>h i (by omega))) (h n (by omega))
      _ = ((n+1:Nat):Int)*B := by push_cast; ring

theorem high_eight_safe (f : Nat → Int) (n : Nat) (hn : n≤8)
    (h : ∀ i, i<n → |f i|≤36*2^54+9*2^30) : |prefix f n|<2^63 := by
  have hs := abs_prefix f (36*2^54+9*2^30) n h
  have hn' : (n:Int)≤8 := by exact_mod_cast hn
  norm_num at hs ⊢
  nlinarith

theorem low_eight_safe (f : Nat → Int) (n : Nat) (hn : n≤8)
    (h : ∀ i, i<n → |f i|≤9*2^55) : |prefix f n|<2^63 := by
  have hs := abs_prefix f (9*2^55) n h
  have hn' : (n:Int)≤8 := by exact_mod_cast hn
  norm_num at hs ⊢
  nlinarith

def signed64 (x : Int) : Int :=
  let r:=x%(2^64)
  if r<2^63 then r else r-2^64

theorem signed64_exact (x : Int) (h : |x|<2^63) : signed64 x=x := by
  rw [abs_lt] at h
  unfold signed64
  norm_num at h ⊢
  split_ifs <;> omega

end R28SpatialWordBounds
