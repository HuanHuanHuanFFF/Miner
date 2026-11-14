/- Own derivation using source36 ZaT/Zck after their declarations.
   UNCOMPILED. Provides the exact high/low shape used by affine correction. -/
lemma R28Shift64Pair (m s:UInt64) (hs:s.toNat<64):
 (if s=0 then (0:UInt64) else m>>>(64-s)).toNat*2^64+(m<<<s).toNat=
 m.toNat*2^s.toNat:=by
 by_cases hz:s=0
 . subst s
   simp
 . have hpos:0<s.toNat:=by
    have hne:s.toNat≠0:=by intro he;apply hz;apply UInt64.toNat_inj.mp;simpa using he
    omega
   have hsub:(64-s).toNat=64-s.toNat:=by
    rw[UInt64.toNat_sub_of_le (by rw[UInt64.le_iff_toNat_le];simp;omega)]
    rfl
   have he:(m>>>(64-s)).toNat=((m>>>1)>>>(63-s)).toNat:=by
    rw[ZaT m s hs,UInt64.toNat_shiftRight,hsub,Nat.mod_eq_of_lt (by omega),Nat.shiftRight_eq_div_pow]
   rw[if_neg hz,he]
   exact Zck m s hs
