/- Owned follow-on helper. Insert after public36 Z128; NOT COMPILED.
   This conditional algebra lemma does not claim an original all12 gate. -/
def r28PairStep (h l p:UInt64):UInt64×UInt64 :=
 (h+((0:UInt64)-(p>>>63))+(if l+p<l then 1 else 0),l+p)

lemma r28SignedBounds (p:UInt64):-(2^63:Int)<=Ym p ∧ Ym p<2^63:=by
 have hp:=UInt64.toNat_lt_size p
 unfold Ym
 split_ifs <;> omega

lemma r28SignedMod (p:UInt64):(p.toNat:Int)=Ym p%2^64:=by
 have hp:=UInt64.toNat_lt_size p
 unfold Ym
 split_ifs <;> omega

lemma r28SignedAddMod (p q:UInt64):
 ((p+q).toNat:Int)=(Ym p+Ym q)%2^64:=by
 have hp:=UInt64.toNat_lt_size p
 have hq:=UInt64.toNat_lt_size q
 rw[UInt64.toNat_add]
 unfold Ym
 split_ifs <;> omega

lemma r28PairModInject (a b c d:UInt64)
 (he:((a.toNat*2^64+b.toNat:Nat):Int)%2^128=
     ((c.toNat*2^64+d.toNat:Nat):Int)%2^128):a=c ∧ b=d:=by
 have ha:=UInt64.toNat_lt_size a
 have hb:=UInt64.toNat_lt_size b
 have hc:=UInt64.toNat_lt_size c
 have hd:=UInt64.toNat_lt_size d
 have h0:0<=((a.toNat*2^64+b.toNat:Nat):Int):=by positivity
 have h1:((a.toNat*2^64+b.toNat:Nat):Int)<2^128:=by omega
 have h2:0<=((c.toNat*2^64+d.toNat:Nat):Int):=by positivity
 have h3:((c.toNat*2^64+d.toNat:Nat):Int)<2^128:=by omega
 rw[Int.emod_eq_of_lt h0 h1,Int.emod_eq_of_lt h2 h3]at he
 constructor <;> apply UInt64.toNat_inj.mp <;> omega

lemma r28PairMerge2 (h l p q:UInt64)
 (hS0:-(2^63:Int)<=Ym p+Ym q) (hS1:Ym p+Ym q<2^63):
 r28PairStep (r28PairStep h l p).1 (r28PairStep h l p).2 q=
 r28PairStep h l (p+q):=by
 let P:Int:=((h.toNat*2^64+l.toNat:Nat):Int)
 let A:=r28PairStep h l p
 let B:=r28PairStep A.1 A.2 q
 let C:=r28PairStep h l (p+q)
 have hp:=r28SignedBounds p
 have hq:=r28SignedBounds q
 have hA:((A.1.toNat*2^64+A.2.toNat:Nat):Int)%2^128=(P+Ym p)%2^128:=by
  simpa[A,r28PairStep,P]using Z128 h l p (Ym p) P (r28SignedMod p) hp.1 hp.2 rfl
 have hB:((B.1.toNat*2^64+B.2.toNat:Nat):Int)%2^128=((P+Ym p)+Ym q)%2^128:=by
  simpa[B,r28PairStep]using Z128 A.1 A.2 q (Ym q) (P+Ym p) (r28SignedMod q) hq.1 hq.2 hA
 have hC:((C.1.toNat*2^64+C.2.toNat:Nat):Int)%2^128=(P+(Ym p+Ym q))%2^128:=by
  simpa[C,r28PairStep,P]using Z128 h l (p+q) (Ym p+Ym q) P (r28SignedAddMod p q) hS0 hS1 rfl
 have hBC:((B.1.toNat*2^64+B.2.toNat:Nat):Int)%2^128=
           ((C.1.toNat*2^64+C.2.toNat:Nat):Int)%2^128:=by
  rw[hB,hC,add_assoc]
 have he:=r28PairModInject B.1 B.2 C.1 C.2 hBC
 exact Prod.ext he.1 he.2
