@[inline] def rC:UInt64:=0x4000000000000000
@[inline] def rX:UInt64:=0x400000000000000
@[inline] def rZ:UInt64:=0x200000000000000
@[inline] def rQ:UInt64:=0x800000000
@[inline] def rJ (a b:UInt64):UInt64×UInt64 :=
 let l:=b<<<25
 let lo:=l+a
 ((b>>>39)+(((0:UInt64)-(b>>>63))<<<25)+((0:UInt64)-(a>>>63))+(if lo<l then 1 else 0),lo)
@[inline] def rA (a b:UInt64×UInt64):UInt64×UInt64 :=
 let l:=a.2+b.2
 (a.1+b.1+(if l<a.2 then 1 else 0),l)
@[inline] def rS (a b:UInt64×UInt64):UInt64×UInt64 :=
 (a.1-b.1-(if a.2<b.2 then 1 else 0),a.2-b.2)
structure rT where
 hi:UInt64
 lo:UInt64
 e:UInt64
 neg:Bool
 deriving Inhabited
@[inline] def rB (e:UInt64) (bw:UInt32):rT :=
 let sh:=Yd bw+126-e
 let m:=Yf bw<<<23
 ⟨if sh<64 then (m>>>1)>>>(63-sh) else m<<<(sh-64),if sh<64 then m<<<sh else 0,e,signOf bw⟩
@[inline] def rF (s:ConvShape) (relu:Bool) (inp wts b:Array Word) (o y x:Nat) (cb:rT) (v:UInt64×UInt64):Word :=
 let a:=if cb.neg then v.2-cb.lo else v.2+cb.lo
 let h:=if cb.neg then v.1-cb.hi-(if v.2<cb.lo then 1 else 0) else v.1+cb.hi+(if v.2+cb.lo<v.2 then 1 else 0)
 let z:=(0:UInt64)-(h>>>63)
 act relu (if (a|||h|||z)==0 then
  if zW s inp wts b (s.cin*9) o 0 y x 0 (s.cin*9+1) then 0x80000000 else 0
  else YaTT z h a (fun _=>(cb.e.toNat:Int)-298) false true (cb.e-298))
def rW (W:Array UInt32) (ci co:Nat):Array Nat := Id.run do
 let mut v:=Array.mkEmpty (co*ci*16)
 for o in [:co] do
  for c in [:ci] do
   let z:=o*(ci*9)+c*9
   let a00:=(W[z+0]!).toUInt64-0x80000000
   let a01:=(W[z+1]!).toUInt64-0x80000000
   let a02:=(W[z+2]!).toUInt64-0x80000000
   let r00:=a00+a00
   let r01:=a00+a01+a02
   let r02:=a00-a01+a02
   let r03:=a02+a02
   let a10:=(W[z+3]!).toUInt64-0x80000000
   let a11:=(W[z+4]!).toUInt64-0x80000000
   let a12:=(W[z+5]!).toUInt64-0x80000000
   let r10:=a10+a10
   let r11:=a10+a11+a12
   let r12:=a10-a11+a12
   let r13:=a12+a12
   let a20:=(W[z+6]!).toUInt64-0x80000000
   let a21:=(W[z+7]!).toUInt64-0x80000000
   let a22:=(W[z+8]!).toUInt64-0x80000000
   let r20:=a20+a20
   let r21:=a20+a21+a22
   let r22:=a20-a21+a22
   let r23:=a22+a22
   v:=v.push ((r00+r00+rQ).toNat)
   v:=v.push ((r00+r10+r20+rQ).toNat)
   v:=v.push ((r00-r10+r20+rQ).toNat)
   v:=v.push ((r20+r20+rQ).toNat)
   v:=v.push ((r01+r01+rQ).toNat)
   v:=v.push ((r01+r11+r21+rQ).toNat)
   v:=v.push ((r01-r11+r21+rQ).toNat)
   v:=v.push ((r21+r21+rQ).toNat)
   v:=v.push ((r02+r02+rQ).toNat)
   v:=v.push ((r02+r12+r22+rQ).toNat)
   v:=v.push ((r02-r12+r22+rQ).toNat)
   v:=v.push ((r22+r22+rQ).toNat)
   v:=v.push ((r03+r03+rQ).toNat)
   v:=v.push ((r03+r13+r23+rQ).toNat)
   v:=v.push ((r03-r13+r23+rQ).toNat)
   v:=v.push ((r23+r23+rQ).toNat)
 return v
def rI (s:ConvShape) (P:Array Nat) (y x:Nat):Array Nat := Id.run do
 let mut v:=Array.mkEmpty (s.cin*16)
 for c in [:s.cin] do
  let z:=(c*(s.h+2)+y)*(s.w+2)+x
  let a00:=(P[z+0*(s.w+2)+0]!).toUInt64-rZ
  let a01:=(P[z+0*(s.w+2)+1]!).toUInt64-rZ
  let a02:=(P[z+0*(s.w+2)+2]!).toUInt64-rZ
  let a03:=(P[z+0*(s.w+2)+3]!).toUInt64-rZ
  let r00:=a00-a02
  let r01:=a01+a02
  let r02:=a02-a01
  let r03:=a01-a03
  let a10:=(P[z+1*(s.w+2)+0]!).toUInt64-rZ
  let a11:=(P[z+1*(s.w+2)+1]!).toUInt64-rZ
  let a12:=(P[z+1*(s.w+2)+2]!).toUInt64-rZ
  let a13:=(P[z+1*(s.w+2)+3]!).toUInt64-rZ
  let r10:=a10-a12
  let r11:=a11+a12
  let r12:=a12-a11
  let r13:=a11-a13
  let a20:=(P[z+2*(s.w+2)+0]!).toUInt64-rZ
  let a21:=(P[z+2*(s.w+2)+1]!).toUInt64-rZ
  let a22:=(P[z+2*(s.w+2)+2]!).toUInt64-rZ
  let a23:=(P[z+2*(s.w+2)+3]!).toUInt64-rZ
  let r20:=a20-a22
  let r21:=a21+a22
  let r22:=a22-a21
  let r23:=a21-a23
  let a30:=(P[z+3*(s.w+2)+0]!).toUInt64-rZ
  let a31:=(P[z+3*(s.w+2)+1]!).toUInt64-rZ
  let a32:=(P[z+3*(s.w+2)+2]!).toUInt64-rZ
  let a33:=(P[z+3*(s.w+2)+3]!).toUInt64-rZ
  let r30:=a30-a32
  let r31:=a31+a32
  let r32:=a32-a31
  let r33:=a31-a33
  v:=v.push ((r00-r20+rX).toNat)
  v:=v.push ((r10+r20+rX).toNat)
  v:=v.push ((r20-r10+rX).toNat)
  v:=v.push ((r10-r30+rX).toNat)
  v:=v.push ((r01-r21+rX).toNat)
  v:=v.push ((r11+r21+rX).toNat)
  v:=v.push ((r21-r11+rX).toNat)
  v:=v.push ((r11-r31+rX).toNat)
  v:=v.push ((r02-r22+rX).toNat)
  v:=v.push ((r12+r22+rX).toNat)
  v:=v.push ((r22-r12+rX).toNat)
  v:=v.push ((r12-r32+rX).toNat)
  v:=v.push ((r03-r23+rX).toNat)
  v:=v.push ((r13+r23+rX).toNat)
  v:=v.push ((r23-r13+rX).toNat)
  v:=v.push ((r13-r33+rX).toNat)
 return v
def rD (V U:Array Nat) (ci o:Nat) (fuel q c:Nat) (a0 a1:UInt64) (L H:Array Nat):Array Nat×Array Nat :=
 match fuel with
 | 0 => (L,H)
 | n+1 =>
  if c<ci then
   let x:=(V[c*16+q]!).toUInt64
   let w:=(U[(o*ci+c)*16+q]!).toUInt64-rQ
   rD V U ci o n q (c+1) (a0+(x&&&0x1ffffff)*w) (a1+((x>>>25)-0x200000000)*w) L H
  else rD V U ci o n (q+1) 0 0 0 (L.push ((a0+rC).toNat)) (H.push ((a1+rC).toNat))
@[inline] def rO (s:ConvShape) (relu:Bool) (inp wts b:Array Word) (cb:rT)
 (o y x:Nat) (L H:Array Nat) (out:Array Word):Array Word :=
 let m0:=rJ ((L[0]!).toUInt64-rC) ((H[0]!).toUInt64-rC)
 let m1:=rJ ((L[1]!).toUInt64-rC) ((H[1]!).toUInt64-rC)
 let m2:=rJ ((L[2]!).toUInt64-rC) ((H[2]!).toUInt64-rC)
 let m3:=rJ ((L[3]!).toUInt64-rC) ((H[3]!).toUInt64-rC)
 let m4:=rJ ((L[4]!).toUInt64-rC) ((H[4]!).toUInt64-rC)
 let m5:=rJ ((L[5]!).toUInt64-rC) ((H[5]!).toUInt64-rC)
 let m6:=rJ ((L[6]!).toUInt64-rC) ((H[6]!).toUInt64-rC)
 let m7:=rJ ((L[7]!).toUInt64-rC) ((H[7]!).toUInt64-rC)
 let m8:=rJ ((L[8]!).toUInt64-rC) ((H[8]!).toUInt64-rC)
 let m9:=rJ ((L[9]!).toUInt64-rC) ((H[9]!).toUInt64-rC)
 let m10:=rJ ((L[10]!).toUInt64-rC) ((H[10]!).toUInt64-rC)
 let m11:=rJ ((L[11]!).toUInt64-rC) ((H[11]!).toUInt64-rC)
 let m12:=rJ ((L[12]!).toUInt64-rC) ((H[12]!).toUInt64-rC)
 let m13:=rJ ((L[13]!).toUInt64-rC) ((H[13]!).toUInt64-rC)
 let m14:=rJ ((L[14]!).toUInt64-rC) ((H[14]!).toUInt64-rC)
 let m15:=rJ ((L[15]!).toUInt64-rC) ((H[15]!).toUInt64-rC)
 let t00:=rA (rA m0 m4) m8
 let t01:=rS (rS m4 m8) m12
 let t10:=rA (rA m1 m5) m9
 let t11:=rS (rS m5 m9) m13
 let t20:=rA (rA m2 m6) m10
 let t21:=rS (rS m6 m10) m14
 let t30:=rA (rA m3 m7) m11
 let t31:=rS (rS m7 m11) m15
 let a:=rA (rA t00 t10) t20
 let b0:=rA (rA t01 t11) t21
 let c:=rS (rS t10 t20) t30
 let d:=rS (rS t11 t21) t31
 let j:=o*(s.h*s.w)+y*s.w+x
 let out:=out.set! j (rF s relu inp wts b o y x cb a)
 let out:=out.set! (j+1) (rF s relu inp wts b o y (x+1) cb b0)
 let out:=out.set! (j+s.w) (rF s relu inp wts b o (y+1) x cb c)
 out.set! (j+s.w+1) (rF s relu inp wts b o (y+1) (x+1) cb d)
def rR (s:ConvShape) (relu:Bool) (inp wts b:Array Word) (P:Array Nat) (W BW:Array UInt32) (xm:UInt64):Array Word := Id.run do
 let U:=rW W s.cin s.cout
 let ctx:=Array.ofFn (n:=s.cout) (fun o=>rB (xm+YG BW[o.val]! b[o.val]! xm-2) b[o.val]!)
 let mut out:=Array.replicate (s.cout*s.h*s.w) 0
 for y in [:s.h/2] do
  for x in [:s.w/2] do
   let V:=rI s P (2*y) (2*x)
   for o in [:s.cout] do
    let z:=rD V U s.cin o (16*(s.cin+1)) 0 0 0 0 (Array.mkEmpty 16) (Array.mkEmpty 16)
    out:=rO s relu inp wts b ctx[o]! o (2*y) (2*x) z.1 z.2 out
 return out
def rV (s:ConvShape) (relu:Bool) (inp wts b:Array Word):Array Word :=
 if s.kh==3&&s.kw==3&&s.stride==1&&s.pad==1&&0<s.cin&&s.cin<=8&&0<s.h&&0<s.w&&
   s.h%2==0&&s.w%2==0&&s.cout>=4&&wts.all (fun w=>Yf w !=0) then
  let k:=s.cin*9
  let bp:=Yc inp inp.size 0
  let BW:=Array.ofFn (n:=s.cout) (fun o=>Yc wts k o.val)
  let xm:=Ybh bp BW b
  if s.cout*k<=wts.size&&s.cin*((s.h+2)*(s.w+2))+(s.h+2)*(s.w+2)+inp.size+wts.size+
     s.cout*(s.ho*s.wo)+s.ho*s.wo+s.stride<=4294967295&&
     (Array.range s.cout).all (fun o=>
      let e:=xm+YG BW[o]! b[o]! xm
      Ybg BW[o]! b[o]! bp k xm&&2<=e&&e<=1000&&(Yf b[o]! ==0||Yd b[o]!+126-e<=76)) then
   rR s relu inp wts b (Ybi s inp xm) (YW2 wts BW b xm k) BW xm
  else Ybp s relu inp wts b
 else Ybp s relu inp wts b
