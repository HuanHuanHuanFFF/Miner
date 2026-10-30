/- Source36-bound metadata bridge. UNCOMPILED; insert after original ZQ.
   It exposes actual producer premises, including the all-zero sentinel. -/
lemma R28MetaBounds (A:Array ExactRuntime.Word) (n row:Nat)
 (hA:row*n+n<=A.size) (hAddr:row*n+n<=4294967295)
 (hFinite:(Yc A n row&&&0xFFFF)≠255) :
 ∀ t,t<n → ExactRuntime.expOf (A[row*n+t]!) ≠255 ∧
  (ExactRuntime.mantOf (A[row*n+t]!) =0 ∨
   ((Yk (Yc A n row>>>16)).toNat<=ExactRuntime.idxOf (A[row*n+t]!) ∧
    ExactRuntime.idxOf (A[row*n+t]!)<=(Yk (Yc A n row&&&0xFFFF)).toNat)) := by
 obtain ⟨L,H,hEq,hL,hH,hValues⟩:=Zp A n row hA hAddr
 obtain ⟨hLow,hHigh⟩:=Zo (Yc A n row) L H hEq (by omega)
 have hHne:H≠255:=by
  intro eq
  exact hFinite (UInt32.toNat_inj.mp (by simpa using hHigh.trans eq))
 intro t ht
 have values:=hValues t ht
 constructor
 · exact (Zb A[row*n+t]!).2.2.1 (by omega)
 · by_cases hz:ExactRuntime.mantOf (A[row*n+t]!) =0
   · exact Or.inl hz
   · have index:=(Zb A[row*n+t]!).2.2.2 hz
     refine Or.inr ⟨?_,?_⟩
     · simpa only [Zq,hLow] using ZQa values.1 index.1
     · simpa only [Zq,hHigh] using ZQb values.2 index.2

lemma R28MetaSpan (A:Array ExactRuntime.Word) (n row cap:Nat)
 (hA:row*n+n<=A.size) (hAddr:row*n+n<=4294967295)
 (hFinite:(Yc A n row&&&0xFFFF)≠255)
 (hSpan:(Yk (Yc A n row&&&0xFFFF)).toNat-(Yk (Yc A n row>>>16)).toNat<=cap) :
 ∀ t,t<n → ExactRuntime.mantOf (A[row*n+t]!) =0 ∨
  ((Yk (Yc A n row>>>16)).toNat<=ExactRuntime.idxOf (A[row*n+t]!) ∧
   ExactRuntime.idxOf (A[row*n+t]!)-(Yk (Yc A n row>>>16)).toNat<=cap) := by
 intro t ht
 obtain ⟨_,bounds⟩:=R28MetaBounds A n row hA hAddr hFinite t ht
 rcases bounds with zero|⟨low,high⟩
 · exact Or.inl zero
 · exact Or.inr ⟨low,by omega⟩

lemma R28MetaReversedAllZero (A:Array ExactRuntime.Word) (n row:Nat)
 (hA:row*n+n<=A.size) (hAddr:row*n+n<=4294967295)
 (hFinite:(Yc A n row&&&0xFFFF)≠255)
 (hReversed:(Yk (Yc A n row&&&0xFFFF)).toNat<(Yk (Yc A n row>>>16)).toNat) :
 ∀ t,t<n → ExactRuntime.mantOf (A[row*n+t]!) =0 := by
 intro t ht
 obtain ⟨_,bounds⟩:=R28MetaBounds A n row hA hAddr hFinite t ht
 rcases bounds with zero|⟨low,high⟩
 · exact zero
 · omega
