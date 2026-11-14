@[inline] def R8C:UInt64:=0x4000000000000000
@[inline] def R8X:UInt64:=0x400000000000000
@[inline] def R8Z:UInt64:=0x200000000000000
@[inline] def R8Q:UInt64:=0x800000000
@[inline] def R8J(a b:UInt64):UInt64×UInt64 :=
 let l:=b<<<25
 let lo:=l+a
((b>>>39)+(((0:UInt64)-(b>>>63))<<<25)+((0:UInt64)-(a>>>63))+(if lo<l then 1 else 0),lo)
@[inline] def R8A(a b:UInt64×UInt64):UInt64×UInt64 :=
 let l:=a.2+b.2
(a.1+b.1+(if l<a.2 then 1 else 0),l)
@[inline] def R8S(a b:UInt64×UInt64):UInt64×UInt64 :=
(a.1-b.1-(if a.2<b.2 then 1 else 0),a.2-b.2)
structure R8T where
 hi:UInt64
 lo:UInt64
 e:UInt64
 neg:Bool
 deriving Inhabited
@[inline] def R8B(e:UInt64)(bw:UInt32):R8T :=
 let sh:=Yd bw+126-e
 let m:=Yf bw<<<23
 ⟨if sh<64 then(m>>>1)>>>(63-sh)else m<<<(sh-64),if sh<64 then m<<<sh else 0,e,signOf bw⟩
@[inline] def R8F(s:ConvShape)(relu:Bool)(inp wts b:Array Word)(o y x:Nat)(cb:R8T)(v:UInt64×UInt64):Word :=
 let a:=if cb.neg then v.2-cb.lo else v.2+cb.lo
 let h:=if cb.neg then v.1-cb.hi-(if v.2<cb.lo then 1 else 0)else v.1+cb.hi+(if v.2+cb.lo<v.2 then 1 else 0)
 let z:=(0:UInt64)-(h>>>63)
 act relu(if(a|||h|||z)==0 then
  if zW s inp wts b(s.cin*9)o 0 y x 0(s.cin*9+1)then 0x80000000 else 0
  else YaTT z h a(fun _=>(cb.e.toNat:Int)-298)false true(cb.e-298))
def R8W(W:Array UInt32)(ci co:Nat):Array Nat := Id.run do
 let mut v:=Array.mkEmpty(co*ci*16)
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
   v:=v.push((r00+r00+R8Q).toNat)
   v:=v.push((r00+r10+r20+R8Q).toNat)
   v:=v.push((r00-r10+r20+R8Q).toNat)
   v:=v.push((r20+r20+R8Q).toNat)
   v:=v.push((r01+r01+R8Q).toNat)
   v:=v.push((r01+r11+r21+R8Q).toNat)
   v:=v.push((r01-r11+r21+R8Q).toNat)
   v:=v.push((r21+r21+R8Q).toNat)
   v:=v.push((r02+r02+R8Q).toNat)
   v:=v.push((r02+r12+r22+R8Q).toNat)
   v:=v.push((r02-r12+r22+R8Q).toNat)
   v:=v.push((r22+r22+R8Q).toNat)
   v:=v.push((r03+r03+R8Q).toNat)
   v:=v.push((r03+r13+r23+R8Q).toNat)
   v:=v.push((r03-r13+r23+R8Q).toNat)
   v:=v.push((r23+r23+R8Q).toNat)
 return v
def R8I(s:ConvShape)(P:Array Nat)(y x:Nat):Array Nat := Id.run do
 let mut v:=Array.mkEmpty(s.cin*16)
 for c in [:s.cin] do
  let z:=(c*(s.h+2)+y)*(s.w+2)+x
  let a00:=(P[z+0*(s.w+2)+0]!).toUInt64-R8Z
  let a01:=(P[z+0*(s.w+2)+1]!).toUInt64-R8Z
  let a02:=(P[z+0*(s.w+2)+2]!).toUInt64-R8Z
  let a03:=(P[z+0*(s.w+2)+3]!).toUInt64-R8Z
  let r00:=a00-a02
  let r01:=a01+a02
  let r02:=a02-a01
  let r03:=a01-a03
  let a10:=(P[z+1*(s.w+2)+0]!).toUInt64-R8Z
  let a11:=(P[z+1*(s.w+2)+1]!).toUInt64-R8Z
  let a12:=(P[z+1*(s.w+2)+2]!).toUInt64-R8Z
  let a13:=(P[z+1*(s.w+2)+3]!).toUInt64-R8Z
  let r10:=a10-a12
  let r11:=a11+a12
  let r12:=a12-a11
  let r13:=a11-a13
  let a20:=(P[z+2*(s.w+2)+0]!).toUInt64-R8Z
  let a21:=(P[z+2*(s.w+2)+1]!).toUInt64-R8Z
  let a22:=(P[z+2*(s.w+2)+2]!).toUInt64-R8Z
  let a23:=(P[z+2*(s.w+2)+3]!).toUInt64-R8Z
  let r20:=a20-a22
  let r21:=a21+a22
  let r22:=a22-a21
  let r23:=a21-a23
  let a30:=(P[z+3*(s.w+2)+0]!).toUInt64-R8Z
  let a31:=(P[z+3*(s.w+2)+1]!).toUInt64-R8Z
  let a32:=(P[z+3*(s.w+2)+2]!).toUInt64-R8Z
  let a33:=(P[z+3*(s.w+2)+3]!).toUInt64-R8Z
  let r30:=a30-a32
  let r31:=a31+a32
  let r32:=a32-a31
  let r33:=a31-a33
  v:=v.push((r00-r20+R8X).toNat)
  v:=v.push((r10+r20+R8X).toNat)
  v:=v.push((r20-r10+R8X).toNat)
  v:=v.push((r10-r30+R8X).toNat)
  v:=v.push((r01-r21+R8X).toNat)
  v:=v.push((r11+r21+R8X).toNat)
  v:=v.push((r21-r11+R8X).toNat)
  v:=v.push((r11-r31+R8X).toNat)
  v:=v.push((r02-r22+R8X).toNat)
  v:=v.push((r12+r22+R8X).toNat)
  v:=v.push((r22-r12+R8X).toNat)
  v:=v.push((r12-r32+R8X).toNat)
  v:=v.push((r03-r23+R8X).toNat)
  v:=v.push((r13+r23+R8X).toNat)
  v:=v.push((r23-r13+R8X).toNat)
  v:=v.push((r13-r33+R8X).toNat)
 return v
def R8D(V U:Array Nat)(ci o:Nat)(fuel q c:Nat)(a0 a1:UInt64)(L H:Array Nat):Array Nat×Array Nat :=
 match fuel with
 | 0 =>(L,H)
 | n+1 =>
  if c<ci then
   let x:=(V[c*16+q]!).toUInt64
   let w:=(U[(o*ci+c)*16+q]!).toUInt64-R8Q
   R8D V U ci o n q(c+1)(a0+(x&&&0x1ffffff)*w)(a1+((x>>>25)-0x200000000)*w)L H
  else R8D V U ci o n(q+1)0 0 0(L.push((a0+R8C).toNat))(H.push((a1+R8C).toNat))
@[inline] def R8O(s:ConvShape)(relu:Bool)(inp wts b:Array Word)(cb:R8T)
(o y x:Nat)(L H:Array Nat)(out:Array Word):Array Word :=
 let m0:=R8J((L[0]!).toUInt64-R8C)((H[0]!).toUInt64-R8C)
 let m1:=R8J((L[1]!).toUInt64-R8C)((H[1]!).toUInt64-R8C)
 let m2:=R8J((L[2]!).toUInt64-R8C)((H[2]!).toUInt64-R8C)
 let m3:=R8J((L[3]!).toUInt64-R8C)((H[3]!).toUInt64-R8C)
 let m4:=R8J((L[4]!).toUInt64-R8C)((H[4]!).toUInt64-R8C)
 let m5:=R8J((L[5]!).toUInt64-R8C)((H[5]!).toUInt64-R8C)
 let m6:=R8J((L[6]!).toUInt64-R8C)((H[6]!).toUInt64-R8C)
 let m7:=R8J((L[7]!).toUInt64-R8C)((H[7]!).toUInt64-R8C)
 let m8:=R8J((L[8]!).toUInt64-R8C)((H[8]!).toUInt64-R8C)
 let m9:=R8J((L[9]!).toUInt64-R8C)((H[9]!).toUInt64-R8C)
 let m10:=R8J((L[10]!).toUInt64-R8C)((H[10]!).toUInt64-R8C)
 let m11:=R8J((L[11]!).toUInt64-R8C)((H[11]!).toUInt64-R8C)
 let m12:=R8J((L[12]!).toUInt64-R8C)((H[12]!).toUInt64-R8C)
 let m13:=R8J((L[13]!).toUInt64-R8C)((H[13]!).toUInt64-R8C)
 let m14:=R8J((L[14]!).toUInt64-R8C)((H[14]!).toUInt64-R8C)
 let m15:=R8J((L[15]!).toUInt64-R8C)((H[15]!).toUInt64-R8C)
 let t00:=R8A(R8A m0 m4)m8
 let t01:=R8S(R8S m4 m8)m12
 let t10:=R8A(R8A m1 m5)m9
 let t11:=R8S(R8S m5 m9)m13
 let t20:=R8A(R8A m2 m6)m10
 let t21:=R8S(R8S m6 m10)m14
 let t30:=R8A(R8A m3 m7)m11
 let t31:=R8S(R8S m7 m11)m15
 let a:=R8A(R8A t00 t10)t20
 let b0:=R8A(R8A t01 t11)t21
 let c:=R8S(R8S t10 t20)t30
 let d:=R8S(R8S t11 t21)t31
 let j:=o*(s.h*s.w)+y*s.w+x
 let out:=out.set! j(R8F s relu inp wts b o y x cb a)
 let out:=out.set!(j+1)(R8F s relu inp wts b o y(x+1)cb b0)
 let out:=out.set!(j+s.w)(R8F s relu inp wts b o(y+1)x cb c)
 out.set!(j+s.w+1)(R8F s relu inp wts b o(y+1)(x+1)cb d)
def R8Run(s:ConvShape)(relu:Bool)(inp wts b:Array Word)(P:Array Nat)(W BW:Array UInt32)(xm:UInt64):Array Word := Id.run do
 let U:=R8W W s.cin s.cout
 let ctx:=Array.ofFn(n:=s.cout)(fun o=>R8B(xm+YG BW[o.val]! b[o.val]! xm-2)b[o.val]!)
 let mut out:=Array.replicate(s.cout*s.h*s.w)0
 for y in [:s.h/2] do
  for x in [:s.w/2] do
   let V:=R8I s P(2*y)(2*x)
   for o in [:s.cout] do
    let z:=R8D V U s.cin o(16*(s.cin+1))0 0 0 0(Array.mkEmpty 16)(Array.mkEmpty 16)
    out:=R8O s relu inp wts b ctx[o]! o(2*y)(2*x)z.1 z.2 out
 return out
def R8Conv(s:ConvShape)(relu:Bool)(inp wts b:Array Word):Array Word :=
 if s.kh==3&&s.kw==3&&s.stride==1&&s.pad==1&&0<s.cin&&s.cin<=8&&0<s.h&&0<s.w&&
   s.h%2==0&&s.w%2==0&&s.cout>=4&&wts.all(fun w=>Yf w!=0)then
  let k:=s.cin*9
  let bp:=Yc inp inp.size 0
  let BW:=Array.ofFn(n:=s.cout)(fun o=>Yc wts k o.val)
  let xm:=Ybh bp BW b
  if s.cout*k<=wts.size&&s.cin*((s.h+2)*(s.w+2))+(s.h+2)*(s.w+2)+inp.size+wts.size+
     s.cout*(s.ho*s.wo)+s.ho*s.wo+s.stride<=4294967295&&
    (Array.range s.cout).all(fun o=>
      let e:=xm+YG BW[o]! b[o]! xm
      Ybg BW[o]! b[o]! bp k xm&&2<=e&&e<=1000&&(Yf b[o]! ==0||Yd b[o]!+126-e<=76))then
   R8Run s relu inp wts b(Ybi s inp xm)(YW2 wts BW b xm k)BW xm
  else Ybp s relu inp wts b
 else Ybp s relu inp wts b
