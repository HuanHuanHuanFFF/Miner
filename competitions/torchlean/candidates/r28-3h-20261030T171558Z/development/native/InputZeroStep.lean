import ContractExact

/- Own, nonrecursive input-zero algebra interface. UNCOMPILED.
   Does not prove the new MD2 loop, caller dispatch or all12. -/
universe u
namespace R28NativeInputZero

def advance (h l p:UInt64):UInt64×UInt64 :=
 (h+((0:UInt64)-(p>>>63))+(if l+p<l then 1 else 0),l+p)

theorem advance_zero (h l:UInt64):advance h l 0=(h,l):=by
 simp only[advance,UInt64.zero_shiftRight,UInt64.sub_zero,UInt64.add_zero,
   lt_self_iff_false,ite_false]

theorem input_pair_step {α:Type u}
 (K:UInt64→UInt64→UInt64→UInt64→α)
 (h1 l1 h2 l2 a1 a2 w d1 d2:UInt64):
 (let p1:=(a1*w)<<<d1
  let p2:=(a2*w)<<<d2
  if a1=0 then
   if a2=0 then K h1 l1 h2 l2
   else let q:=advance h2 l2 p2;K h1 l1 q.1 q.2
  else if a2=0 then
   let q:=advance h1 l1 p1;K q.1 q.2 h2 l2
  else
   let q1:=advance h1 l1 p1
   let q2:=advance h2 l2 p2
   K q1.1 q1.2 q2.1 q2.2)=
 (let q1:=advance h1 l1 ((a1*w)<<<d1)
  let q2:=advance h2 l2 ((a2*w)<<<d2)
  K q1.1 q1.2 q2.1 q2.2):=by
 dsimp only
 by_cases ha:a1=0 <;> by_cases hb:a2=0 <;>
  simp only[ha,hb,ite_true,ite_false,UInt64.zero_mul,UInt64.zero_shiftLeft,
    advance_zero,advance,UInt64.zero_shiftRight,UInt64.sub_zero,
    UInt64.add_zero,lt_self_iff_false]

end R28NativeInputZero
