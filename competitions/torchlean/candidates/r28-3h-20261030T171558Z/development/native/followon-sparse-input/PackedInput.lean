import ContractExact

/- Independent post-1957-freeze arithmetic only. UNCOMPILED.
   No CI6 data/parameters are used; no runtime source or all12 claim. -/
namespace R28SparseInput

def pack (a:Int) (i:Nat):Nat := (a+2^39).toNat*2^20+i

theorem packed_lt60 (a:Int) (i:Nat)
 (ha0:-(2^39:Int)<a) (ha1:a<2^39) (hi:i<2^20):pack a i<2^60:=by
 unfold pack
 have h:(a+2^39).toNat<2^40:=by omega
 omega

theorem index_roundtrip (a:Int) (i:Nat) (hi:i<2^20):
 pack a i%2^20=i:=by
 unfold pack
 omega

theorem coefficient_roundtrip (a:Int) (i:Nat)
 (ha:-(2^39:Int)<=a) (hi:i<2^20):
 ((pack a i/2^20:Nat):Int)-2^39=a:=by
 unfold pack
 have h:((a+2^39).toNat:Int)=a+2^39:=by omega
 have hd:((a+2^39).toNat*2^20+i)/2^20=(a+2^39).toNat:=by omega
 rw[hd]
 omega

theorem packet_lt63 (a:Int) (i:Nat)
 (ha0:-(2^39:Int)<a) (ha1:a<2^39) (hi:i<2^20):pack a i<2^63:=by
 exact (packed_lt60 a i ha0 ha1 hi).trans (by norm_num)

theorem omit_zero_products (xs:List (Int×Int)):
 ((xs.filter (fun z=>z.1!=0)).map (fun z=>z.1*z.2)).sum=
 (xs.map (fun z=>z.1*z.2)).sum:=by
 induction xs with
 | nil=>simp
 | cons z zs ih=>
   by_cases hz:z.1=0 <;> simp[hz,ih]

end R28SparseInput
