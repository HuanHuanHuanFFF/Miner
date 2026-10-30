namespace R27Band
structure Four where
 l0:UInt64
 h0:UInt64
 l1:UInt64
 h1:UInt64
 l2:UInt64
 h2:UInt64
 l3:UInt64
 h3:UInt64
@[inline] def ext (w:UInt32):UInt64 :=
 (w.toUInt64 ^^^ 0x80000000)-0x80000000
@[inline] def shifted (lo hi:UInt64) (d:Nat):UInt64×UInt64 :=
 if d=0 then (lo,hi) else
 ((lo <<< d.toUInt64),(hi <<< d.toUInt64) ||| (lo >>> (64-d).toUInt64))
@[specialize] def sum4 (v:Array (UInt32×UInt32)) (a b c d:Array UInt32) :
 Nat -> Nat -> UInt64 -> UInt64 -> UInt64 -> UInt64 -> (UInt64×UInt64)×(UInt64×UInt64)
 | 0,_,p,q,r,s=>((p,q),(r,s))
 | n+1,i,p,q,r,s=>
   let e:=v[i]!
   let k:=e.1.toNat
   let x:=ext e.2
   sum4 v a b c d n (i+1) (p+x*ext a[k]!) (q+x*ext b[k]!)
    (r+x*ext c[k]!) (s+x*ext d[k]!)
def group4 (v:Array (UInt32×UInt32)) (a b c d:Array UInt32):Four := Id.run do
 let mut l0:UInt64:=0
 let mut h0:UInt64:=0
 let mut l1:UInt64:=0
 let mut h1:UInt64:=0
 let mut l2:UInt64:=0
 let mut h2:UInt64:=0
 let mut l3:UInt64:=0
 let mut h3:UInt64:=0
 for t in [0:(v.size+63)/64] do
  let start:=t*64
  let q:=sum4 v a b c d (min 64 (v.size-start)) start 0 0 0 0
  h0:=QhiS h0 l0 q.1.1
  l0:=l0+q.1.1
  h1:=QhiS h1 l1 q.1.2
  l1:=l1+q.1.2
  h2:=QhiS h2 l2 q.2.1
  l2:=l2+q.2.1
  h3:=QhiS h3 l3 q.2.2
  l3:=l3+q.2.2
 return ⟨l0,h0,l1,h1,l2,h2,l3,h3⟩
def body4 (g:Array (Array (UInt32×UInt32))) (a b c d:Array UInt32):Four := Id.run do
 let mut l0:UInt64:=0
 let mut h0:UInt64:=0
 let mut l1:UInt64:=0
 let mut h1:UInt64:=0
 let mut l2:UInt64:=0
 let mut h2:UInt64:=0
 let mut l3:UInt64:=0
 let mut h3:UInt64:=0
 for t in [0:g.size] do
  if 0<g[t]!.size then
   let q:=group4 g[t]! a b c d
   let p0:=shifted q.l0 q.h0 (4*t)
   let p1:=shifted q.l1 q.h1 (4*t)
   let p2:=shifted q.l2 q.h2 (4*t)
   let p3:=shifted q.l3 q.h3 (4*t)
   let n0:=l0+p0.1
   let n1:=l1+p1.1
   let n2:=l2+p2.1
   let n3:=l3+p3.1
   h0:=h0+p0.2+(if n0<l0 then 1 else 0)
   h1:=h1+p1.2+(if n1<l1 then 1 else 0)
   h2:=h2+p2.2+(if n2<l2 then 1 else 0)
   h3:=h3+p3.2+(if n3<l3 then 1 else 0)
   l0:=n0
   l1:=n1
   l2:=n2
   l3:=n3
 return ⟨l0,h0,l1,h1,l2,h2,l3,h3⟩
@[inline] def low (m:UInt32):Nat := (Yk (m >>> 16)).toNat
@[inline] def high (m:UInt32):Nat := (Yk (m &&& 0xffff)).toNat
@[inline] def ok (m:UInt32):Bool := (m &&& 0xffff != 255) && low m<=high m
def row (X:Array Word) (start n:Nat) (m:UInt32):Array (Array (UInt32×UInt32)) := Id.run do
 let base:UInt64:=(low m).toUInt64
 let mut gs:Array (Array (UInt32×UInt32)):=Array.replicate ((high m-low m)/4+1) #[]
 for t in [0:n] do
  let w:=X[start+t]!
  if Yf w != 0 then
   let delta:=Yd w-base
   let band:=(delta >>> 2).toNat
   let v:UInt32:=(Yf w <<< (delta &&& 3)).toUInt32
   let factor:=if signOf w then (0:UInt32)-v else v
   gs:=gs.set! band (gs[band]!.push (t.toUInt32,factor))
 return gs
def column (W:Array Word) (start n:Nat) (m:UInt32):Array UInt32 :=
 Array.ofFn (n:=n) fun t=>
  let w:=W[start+t.val]!
  let v:UInt32:=(Yf w <<< (Yd w-(low m).toUInt64)).toUInt32
  if signOf w then (0:UInt32)-v else v
@[inline] def finish (X W b:Array Word) (n i j:Nat) (bx bv:UInt32) (lo hi:UInt64):Word :=
 let B:=Yp bx bv b[j]!
 let body:=(low bx+low bv).toUInt64
 let v:=shifted lo hi (body-B).toNat
 let q:=YL B oneW b[j]! ((0:UInt64)-(v.2 >>> 63)) v.2 v.1 0
  (fun a h l c=>YD a h l c ((B.toNat:Int)-298))
 if q<0x100000000 then q.toUInt32 else Yai X W b n i j
def eligible (BX BV:Array UInt32) (b:Array Word):Bool := Id.run do
 if !(BX.all ok && BV.all (fun v=>ok v && high v-low v<=6) && b.all finiteWord) then return false
 for i in [0:BX.size] do
  for j in [0:BV.size] do
   if (Yu BX[i]! BV[j]! b[j]!-Yp BX[i]! BV[j]! b[j]!).toNat>58 then return false
 return true
def linear (rows n outW:Nat) (relu:Bool) (X W b:Array Word):Array Word :=
 if n=0 || n>=1048576 || rows=0 || outW<4 ||
  !(X.size==rows*n && W.size==outW*n && b.size==outW) then YaV rows n outW relu X W b else
 let BX:=Array.ofFn (n:=rows) fun i=>Yc X n i.val
 let BV:=Array.ofFn (n:=outW) fun j=>Yc W n j.val
 if !(eligible BX BV b) then YaV rows n outW relu X W b else Id.run do
  let weights:=Array.ofFn (n:=outW) fun j=>column W (j.val*n) n BV[j.val]!
  let mut result:Array Word:=Array.emptyWithCapacity (rows*outW)
  for i in [0:rows] do
   let groups:=row X (i*n) n BX[i]!
   for tile in [0:outW/4] do
    let j:=tile*4
    let q:=body4 groups weights[j]! weights[j+1]! weights[j+2]! weights[j+3]!
    result:=result.push (act relu (finish X W b n i j BX[i]! BV[j]! q.l0 q.h0))
    result:=result.push (act relu (finish X W b n i (j+1) BX[i]! BV[j+1]! q.l1 q.h1))
    result:=result.push (act relu (finish X W b n i (j+2) BX[i]! BV[j+2]! q.l2 q.h2))
    result:=result.push (act relu (finish X W b n i (j+3) BX[i]! BV[j+3]! q.l3 q.h3))
   for j in [outW/4*4:outW] do
    result:=result.push (act relu (YaU X W b n i j BX[i]! BV[j]!))
  return result
end R27Band
