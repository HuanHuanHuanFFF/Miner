/- Original source11-specific shape/prepared-read interface, to append after the
   base module (or its native-only prototype). UNCOMPILED; no all12 claim. -/
namespace Submission

theorem R28packed_ho (s:ExactRuntime.ConvShape) (kh:s.kh=3)
 (pad:s.pad=1) (stride:s.stride=1) (height:0<s.h) : s.ho=s.h := by
 simp only [ExactRuntime.ConvShape.ho,kh,pad,stride,Nat.mul_one,Nat.div_one]
 omega

theorem R28packed_wo (s:ExactRuntime.ConvShape) (kw:s.kw=3)
 (pad:s.pad=1) (stride:s.stride=1) (width:0<s.w) : s.wo=s.w := by
 simp only [ExactRuntime.ConvShape.wo,kw,pad,stride,Nat.mul_one,Nat.div_one]
 omega

theorem R28packed_padded_read (s:ExactRuntime.ConvShape) (inp:Array ExactRuntime.Word)
 (kh:s.kh=3) (kw:s.kw=3) (pad:s.pad=1) (stride:s.stride=1)
 (height:0<s.h) (width:0<s.w) (c y x dy dx:Nat)
 (hc:c<s.cin) (hy:y<s.h) (hx:x<s.w) (hdy:dy<3) (hdx:dx<3) :
 let j:=(c*(s.h+2)+y)*(s.w+2)+x+dy*(s.w+2)+dx
 j<s.cin*(Yb s*Ya s) ∧
 YI s inp j=ExactRuntime.windowAt s inp y x (c*9+3*dy+dx) := by
 have ht:3*dy+dx<s.kh*s.kw := by rw[kh,kw];omega
 have hdiv:(3*dy+dx)/9=0 := by omega
 have hrow:(3*dy+dx)/3%3=dy := by omega
 have hcol:(3*dy+dx)%3=dx := by omega
 have hz:=ZZ s inp c (3*dy+dx) y x
  (by simp only [Yb,pad,kh];omega)
  (by simp only [Ya,pad,kw];omega) hc ht
  (by rw[R28packed_ho s kh pad stride height];exact hy)
  (by rw[R28packed_wo s kw pad stride width];exact hx)
 have he:c*(Yb s*Ya s)+(y*s.stride*Ya s+x*s.stride)+Ys s (3*dy+dx)=
   (c*(s.h+2)+y)*(s.w+2)+x+dy*(s.w+2)+dx := by
  simp only [Yb,Ya,Ys,pad,stride,kh,kw,Nat.reduceMul,Nat.mul_one,hdiv,hrow,hcol,Nat.zero_mul,Nat.zero_add]
  ring
 rw[he] at hz
 simpa only [kh,kw,Nat.reduceMul,Nat.add_assoc] using hz

theorem R28packed_prepared_read (s:ExactRuntime.ConvShape) (inp:Array ExactRuntime.Word)
 (xm:UInt64) (kh:s.kh=3) (kw:s.kw=3) (pad:s.pad=1) (stride:s.stride=1)
 (height:0<s.h) (width:0<s.w) (c y x dy dx:Nat)
 (hc:c<s.cin) (hy:y<s.h) (hx:x<s.w) (hdy:dy<3) (hdx:dx<3)
 (area:0<Yb s*Ya s) (size:s.cin*(Yb s*Ya s)<4294967296)
 (plane:Yb s*Ya s<4294967296) :
 (Ybi s inp xm)[(c*(s.h+2)+y)*(s.w+2)+x+dy*(s.w+2)+dx]! =
 YV (ExactRuntime.windowAt s inp y x (c*9+3*dy+dx)) xm := by
 have h:=R28packed_padded_read s inp kh kw pad stride height width c y x dy dx hc hy hx hdy hdx
 dsimp only at h
 rw[Zbz s inp xm area size plane,gO _ _ _ h.1,h.2]

end Submission
