/- ORIGINAL NATIVE-ONLY PROTOTYPE. No Submission.correct for the new kernels.
   Source11's original complete implementation remains the fallback.
   Proving the support loop/packing and native cost are separate outstanding tasks. -/
@[inline] def R28finishPacked (s:ConvShape) (relu:Bool) (inp wts b:Array Word)
 (k o p:Nat) (fast neg:Bool) (bh bl e:UInt64) (bw:UInt32) (a z:UInt64):Word :=
 let v:=Yq5 fast neg bh bl e bw a z
 act relu (if v<0x100000000 then v.toUInt32
  else if zW s inp wts b k o 0 (p/s.wo) (p%s.wo) 0 (k+1) then 0x80000000 else 0)

def R28packedLoop (s:ConvShape) (relu:Bool) (inp wts b:Array Word)
 (packed:Array Nat) (weights:Array UInt32) (k o:Nat) (two:Bool)
 (f0 n0:Bool) (h0 l0 e0:UInt64) (w0:UInt32)
 (f1 n1:Bool) (h1 l1 e1:UInt64) (w1:UInt32)
 (remaining i p:Nat) (a0 a1 b0 b1:UInt64) (out out2:Array Word):Array Word :=
 match remaining with
 | 0 => out++out2
 | r+1 =>
  let v:=packed[i]!
  if v==0 then
   let out:=out.push (R28finishPacked s relu inp wts b k o p f0 n0 h0 l0 e0 w0 a0 a1)
   let out2:=if two then out2.push (R28finishPacked s relu inp wts b k (o+1) p f1 n1 h1 l1 e1 w1 b0 b1) else out2
   R28packedLoop s relu inp wts b packed weights k o two f0 n0 h0 l0 e0 w0 f1 n1 h1 l1 e1 w1 r (i+1) (p+1) 0 0 0 0 out out2
  else
   let v:=v.toUInt64
   let t:=(v>>>56).toNat
   let x:=(v&&&0xffffffffffffff)+0x180000000000000
   let w:=(weights[o*k+t]!).toUInt64
   let u:=if two then (weights[(o+1)*k+t]!).toUInt64 else 0x80000000
   R28packedLoop s relu inp wts b packed weights k o two f0 n0 h0 l0 e0 w0 f1 n1 h1 l1 e1 w1 r (i+1) p
    (a0+Y9 x w) (a1+cq1 x w) (b0+Y9 x u) (b1+cq1 x u) out out2

def R28packWindows (s:ConvShape) (P:Array Nat):Array Nat := Id.run do
 let mut packed:=Array.mkEmpty (s.ho*s.wo*(s.cin*9+1))
 for y in [:s.ho] do
  for x in [:s.wo] do
   for c in [:s.cin] do
    let row:=(c*(s.h+2)+y)*(s.w+2)+x
    for dy in [:3] do
     for dx in [:3] do
      let v:=(P[row+dy*(s.w+2)+dx]!).toUInt64
      if v!=0x200000000000000 then
       packed:=packed.push ((((c*9+dy*3+dx).toUInt64<<<56)|||(v-0x180000000000000)).toNat)
   packed:=packed.push 0
 return packed

def R28packedRun (s:ConvShape) (relu:Bool) (inp wts b:Array Word)
 (P:Array Nat) (W BW:Array UInt32) (xm:UInt64):Array Word := Id.run do
 let packed:=R28packWindows s P
 let k:=s.cin*9
 let mut out:=Array.mkEmpty (s.cout*s.ho*s.wo)
 for pair in [:((s.cout+1)/2)] do
  let o:=2*pair
  let a:=b[o]!
  let d:=b[o+1]!
  let e0:=xm+YG BW[o]! a xm
  let e1:=xm+YG BW[o+1]! d xm
  let sh0:=Yd a+126-e0
  let sh1:=Yd d+126-e1
  let m0:=Yf a<<<23
  let m1:=Yf d<<<23
  out:=R28packedLoop s relu inp wts b packed W k o (o+1<s.cout)
   ((Yf a==0||sh0<=78)&&e0<=1000) (signOf a)
   (if sh0<64 then (m0>>>1)>>>(63-sh0) else m0<<<(sh0-64)) (if sh0<64 then m0<<<sh0 else 0) e0 a
   ((Yf d==0||sh1<=78)&&e1<=1000) (signOf d)
   (if sh1<64 then (m1>>>1)>>>(63-sh1) else m1<<<(sh1-64)) (if sh1<64 then m1<<<sh1 else 0) e1 d
   packed.size 0 0 0 0 0 0 out (Array.mkEmpty (s.ho*s.wo))
 return out

def R28packedConv (s:ConvShape) (relu:Bool) (inp wts b:Array Word):Array Word :=
 let k:=s.cin*9
 let shape:=s.kh==3&&s.kw==3&&s.stride==1&&s.pad==1&&0<s.h&&0<s.w&&0<s.cin&&k<128&&s.cout>=4
 if shape then
  let zeros:=inp.foldl (fun n x=>n+(if x&&&0x7fffffff==0 then 1 else 0)) 0
  if zeros*4>=inp.size then
   let bp:=Yc inp inp.size 0
   let BW:=Array.ofFn (n:=s.cout) (fun o=>Yc wts k o.val)
   let xm:=Ybh bp BW b
   if s.cout*k<=wts.size&&s.cin*((s.h+2)*(s.w+2))+(s.h+2)*(s.w+2)+inp.size+wts.size+
      s.cout*(s.ho*s.wo)+s.ho*s.wo+s.stride<=4294967295&&
      (Array.range s.cout).all (fun o=>Ybg BW[o]! b[o]! bp k xm) then
    R28packedRun s relu inp wts b (Ybi s inp xm) (YW2 wts BW b xm k) BW xm
   else Ybp s relu inp wts b
  else Ybp s relu inp wts b
 else Ybp s relu inp wts b
