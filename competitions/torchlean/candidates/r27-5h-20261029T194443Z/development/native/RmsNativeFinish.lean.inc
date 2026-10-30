@[inline] def R27RmsFinish (w gw dw:Word):Word :=
 if sv dw <= 0 then Ya7 w gw dw else
 let N:=Yf w*Yf gw
 let D:=Yf dw
 if N=0 then 0 else
 if D <= N then
  rrsG (signOf w != signOf gw) N D (Yd w+Yd gw) (Yd dw+22) (fun _=>Ya7 w gw dw)
 else Ya7 w gw dw
lemma R27RmsFinish_eq (w gw dw:Word):R27RmsFinish w gw dw=Ya7 w gw dw:=by
 unfold R27RmsFinish
 split
 . rfl
 . rename_i hd
   dsimp only
   split
   . rename_i hz
     have hh:=congrArg UInt64.toNat hz
     have hpn:mantOf w*mantOf gw=0:=by simpa only [K4,UInt64.toNat_zero] using hh
     have hp:0 < mantOf dw:=(eD dw hd).2
     have hd0:mantOf dw ≠ 0:=by omega
     simp [Ya7,hd,hpn,YN,hd0]
   . split
     . rename_i hnd
       have hp:0 < mantOf dw:=(eD dw hd).2
       have hpn:mantOf w*mantOf gw ≠ 0:=by
        have hn:=UInt64.le_iff_toNat_le.mp hnd
        rw [Zk,K4] at hn
        omega
       have hv:(Yd dw+22).toNat=idxOf dw+22:=by
        rw [UInt64.toNat_add,Zf]
        have hi:=Zg dw
        norm_num
        omega
       refine rrsGe _ _ _ _ _ ((idxOf w:Int)+idxOf gw-idxOf dw-149) (Ya7 w gw dw) ?_ ?_ ?_ ?_ ?_ ?_ ?_
       . rw [Zk];exact hp
       . exact UInt64.le_iff_toNat_le.mp hnd
       . rw [Zk];have hm:=mantOf_lt_24 dw;omega
       . rw [B6];have hi:=Zg w;have hg:=Zg gw;omega
       . rw [hv];have hi:=Zg dw;omega
       . rw [B6,hv];push_cast;ring
       . rw [K4,Zk]
         unfold Ya7
         rw [if_neg hd]
         dsimp only
         simp [hpn]
     . rfl
