namespace R27N
-- R is floor((B-1)/d),so multiply-high underestimates by at most one.
-- This theorem is about mathematical integers,independent of word wrapping.
theorem b(B a d:ٳ)(hB:0 < B)(ha:a < B)(hd:0 < d):
    let R:=(B - 1)/ d
    let q:= a * R / B
    q * d ≤ a ∧ a <(q + 2)* d:= by
  dsimp only
  let R:=(B - 1)/ d
  let q:= a * R / B
  change q * d ≤ a ∧ a <(q + 2)* d
  have hR0:R * d ≤ B - 1:= by
    simpa only[R]using Av(B - 1)d
  have hR1:B ≤(R + 1)* d:= by
    have he:= Ez(B - 1)d
    have hr:= Ε(B - 1)hd
    change(B - 1)% d + d * R = B - 1 at he
    rw[ϟ,Ϙ,Θ R d]
    omega
  have hq0:q * B ≤ a * R:= by
    simpa only[q]using Av(a * R)B
  have hq1:a * R <(q + 1)* B:= by
    have he:= Ez(a * R)B
    have hr:= Ε(a * R)hB
    change a * R % B + B * q = a * R at he
    rw[ϟ,Ϙ,Θ q B]
    omega
  have ll:(q * d)* B ≤ a * B:= calc
    (q * d)* B =(q * B)* d:= by ring
    _ ≤(a * R)* d:= ω d hq0
    _ = a *(R * d):= by ring
    _ ≤ a * B:= Ci a(by omega)
  have high:a * B <((q + 2)* d)* B:= calc
    a * B ≤ a *((R + 1)* d):= Ci a hR1
    _ =(a * R)* d + a * d:= by ring
    _ <((q + 1)* B)* d + B * d:=
      Nat.add_lt_add(Aj hq1 hd)
        (Aj ha hd)
    _ =((q + 2)* d)* B:= by ring
  constructor
  · by_contra h
    have h':a * B <(q * d)* B:=
      Aj(by omega)hB
    omega
  · by_contra h
    have h':((q + 2)* d)* B ≤ a * B:= ω B(by omega)
    omega
def corrected(B a d:ٳ):ٳ × ٳ:=
  let q:= a *((B - 1)/ d)/ B
  let r:= a - q * d
  if d ≤ r then(q + 1,r - d)else(q,r)
theorem corrected_exact(B a d:ٳ)(hB:0 < B)(ha:a < B)(hd:0 < d):
    corrected B a d =(a / d,a % d):= by
  have hb:= b B a d hB ha hd
  let q:= a *((B - 1)/ d)/ B
  change q * d ≤ a ∧ a <(q + 2)* d at hb
  let r:= a - q * d
  have he:r + q * d = a:= Aw hb.1
  have hr:r < 2 * d:= by
    have hu:= hb.2
    rw[ϟ]at hu
    omega
  change(if d ≤ r then(q + 1,r - d)else(q,r))= _
  by_cases hc:d ≤ r
  · rw[if_pos hc]
    have hq:a / d = q + 1:= Nat.div_eq_of_lt_le
      (by rw[ϟ,Ϙ];omega)
      (by simpa[BU]using hb.2)
    have hm:= Ez a d
    rw[hq,Nat.mul_add,Nat.mul_one,Θ d q]at hm
    have hm':a % d = r - d:= by omega
    rw[hq,hm']
  · rw[if_neg hc]
    have hq:a / d = q:= Nat.div_eq_of_lt_le hb.1
      (by rw[ϟ,Ϙ];omega)
    have hm:= Ez a d
    rw[hq,Θ d q]at hm
    have hm':a % d = r:= by omega
    rw[hq,hm']
theorem c(B a d:ٳ)
    (bp:0 < B)(ab:a < B)
    (dp:0 < d):
    let R:=(B - 1)/ d
    let q:= a * R / B
    let r:= a - q * d
    (if d ≤ r then(q + 1,r - d)
     else(q,r))=(a / d,a % d):=
  corrected_exact B a d bp ab dp
end R27N
namespace R27D
@[inline]def h(a b:ػ):ػ:=(m64 a b).1
theorem hv(a b:ػ):
    (h a b)˧ = a˧ * b˧ / 2^64:= by
  unfold h
  have vv:= m64_v a b
  have ll:=(m64 a b).2.toNat_lt
  omega
@[inline]def p(d:ػ):ػ:=
  0xffffffffffffffff / d
@[inline]def r(a d R:ػ):ػ × ػ:=
  if d == 0 then(a / d,a % d)
  else
    let q:= h a R
    let r:= a - q * d
    if d ≤ r then(q + 1,r - d)
    else(q,r)
theorem pn(d:ػ):
    (p d)˧ =(2^64 - 1)/ d˧:= by
  exact UInt64.toNat_div(0xffffffffffffffff:ػ)d
theorem v(a d:ػ):
    r a d(p d)=
      (a / d,a % d):= by
  unfold r
  split
  · rfl
  · rename_i nz
    have dn:d ≠ 0:= by simpa only[beq_iff_eq]using nz
    have dp:0 < d˧:= by
      apply Ο
      intro zero
      exact dn(σ.mp zero)
    let q:= h a(p d)
    let r:= a - q * d
    change(if d ≤ r then(q + 1,r - d)
      else(q,r))= _
    have e:q˧ =
        a˧ *((2^64 - 1)/ d˧)/ 2^64:= by
      dsimp[q]
      rw[hv,pn]
      norm_num
    obtain ⟨l,u⟩:= R27N.b
      (2^64)a˧ d˧(by decide)a.toNat_lt dp
    rw[← e]at l u
    have pf:q˧ * d˧ < 2^64:=
      lt_of_le_of_lt l a.toNat_lt
    have pv:(q * d)˧ = q˧ * d˧:= by
      rw[ϯ]
      exact ν pf
    have rv:r˧ = a˧ - q˧ * d˧:= by
      dsimp[r]
      rw[Η _ _(ϐ.mpr(by rw[pv];exact l)),pv]
    have nr:= R27N.c
      (2^64)a˧ d˧(by decide)a.toNat_lt dp
    dsimp only at nr
    rw[← e]at nr
    by_cases k:d ≤ r
    · rw[if_pos k]
      have nc:d˧ ≤ a˧ - q˧ * d˧:= by
        have h:= ϐ.mp k
        rwa[rv]at h
      rw[if_pos nc]at nr
      have qe:= congrArg Prod.fst nr
      have re:= congrArg Prod.snd nr
      dsimp only at qe re
      have qf:q˧ + 1 < 2^64:= by
        rw[qe]
        have h:=(a / d).toNat_lt
        rwa[UInt64.toNat_div]at h
      apply Prod.ext
      · apply σ.mp
        rw[ξ,Da,ν qf,UInt64.toNat_div]
        exact qe
      · apply σ.mp
        rw[Η _ _ k,rv,UInt64.toNat_mod]
        exact re
    · rw[if_neg k]
      have nc:¬ d˧ ≤ a˧ - q˧ * d˧:= by
        intro h
        apply k
        apply ϐ.mpr
        rwa[rv]
      rw[if_neg nc]at nr
      have qe:= congrArg Prod.fst nr
      have re:= congrArg Prod.snd nr
      dsimp only at qe re
      apply Prod.ext
      · apply σ.mp
        rw[UInt64.toNat_div]
        exact qe
      · apply σ.mp
        rw[rv,UInt64.toNat_mod]
        exact re
end R27D
