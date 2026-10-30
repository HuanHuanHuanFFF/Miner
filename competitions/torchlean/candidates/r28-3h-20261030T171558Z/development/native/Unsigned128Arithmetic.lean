import ContractExact

/- Own small helpers for the affine centered candidate's terminal correction.
   UNCOMPILED. No getters/loop/metadata/finish/all12 statement is proved here. -/
namespace R28NativeArithmetic

theorem add128_mod (h l a b:UInt64):
 let low:=l+b
 (((h+a+(if low<l then 1 else 0)).toNat*2^64+low.toNat:Nat):Int)%2^128=
 (((h.toNat*2^64+l.toNat:Nat):Int)+((a.toNat*2^64+b.toNat:Nat):Int))%2^128:=by
 have hh:h.toNat<2^64:=UInt64.toNat_lt_size h
 have hl:l.toNat<2^64:=UInt64.toNat_lt_size l
 have ha:a.toNat<2^64:=UInt64.toNat_lt_size a
 have hb:b.toNat<2^64:=UInt64.toNat_lt_size b
 dsimp only
 split_ifs with hc
 . have hc':(l.toNat+b.toNat)%2^64<l.toNat:=by
    simpa only[UInt64.lt_iff_toNat_lt,UInt64.toNat_add]using hc
   simp only[UInt64.toNat_add,UInt64.toNat_one]
   omega
 . have hc':¬(l.toNat+b.toNat)%2^64<l.toNat:=by
    simpa only[UInt64.lt_iff_toNat_lt,UInt64.toNat_add]using hc
   simp only[UInt64.toNat_add,UInt64.toNat_zero]
   omega

theorem sub128_mod (h l a b:UInt64):
 (((h-a-(if l<b then 1 else 0)).toNat*2^64+(l-b).toNat:Nat):Int)%2^128=
 (((h.toNat*2^64+l.toNat:Nat):Int)-((a.toNat*2^64+b.toNat:Nat):Int))%2^128:=by
 have hh:h.toNat<2^64:=UInt64.toNat_lt_size h
 have hl:l.toNat<2^64:=UInt64.toNat_lt_size l
 have ha:a.toNat<2^64:=UInt64.toNat_lt_size a
 have hb:b.toNat<2^64:=UInt64.toNat_lt_size b
 split_ifs with hc
 . have hc':l.toNat<b.toNat:=UInt64.lt_iff_toNat_lt.mp hc
   simp only[UInt64.toNat_sub,UInt64.toNat_one]
   omega
 . have hc':¬l.toNat<b.toNat:=by simpa only[UInt64.lt_iff_toNat_lt]using hc
   simp only[UInt64.toNat_sub,UInt64.toNat_zero]
   omega

theorem signed128_unique (h l:UInt64) (S:Int)
 (hS0:-(2^127:Int)<=S) (hS1:S<2^127)
 (hv:((h.toNat*2^64+l.toNat:Nat):Int)%2^128=S%2^128):
 ((h.toNat*2^64+l.toNat:Nat):Int)-(if h.toNat<2^63 then 0 else 2^128)=S:=by
 have hh:h.toNat<2^64:=UInt64.toNat_lt_size h
 have hl:l.toNat<2^64:=UInt64.toNat_lt_size l
 split_ifs <;> omega

end R28NativeArithmetic
