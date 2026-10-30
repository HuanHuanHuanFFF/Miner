namespace R27Band
@[inline] def ext (w:UInt32):UInt64:=(w.toUInt64^^^0x80000000)-0x80000000
@[inline] def merge (lo hi q:UInt64):UInt64:=hi+(0-(q>>>63))+(if lo+q<lo then 1 else 0)
@[inline] def signed (q:UInt64):Int:=if q<0x8000000000000000 then q.toNat else (q.toNat:Int)-18446744073709551616
@[inline] def value (lo hi:UInt64):Int:=(lo.toNat:Int)+signed hi*18446744073709551616
structure Row where
 valid:Bool
 factors:Array UInt32
 indices:Array UInt32
 starts:Array Nat
 lengths:Array Nat
 deriving Inhabited
@[inline] def factor (w:Word) (base:UInt64):UInt32:=
 let m:=(Yf w<<<(Yd w-base)).toUInt32
 if signOf w then 0-m else m
def prepare (x:Array Word) (offset n:Nat) (base:UInt64):Row:=Id.run do
 let mut counts:=Array.replicate 16 (0:Nat)
 let mut valid:=true
 for j in [:n] do
  let w:=x[offset+j]!
  if Yf w != 0 then
   let band:=(Yd w-base).toNat/4
   if band<16 then counts:=counts.set! band (counts[band]!+1)
   else valid:=false
 let mut starts:=Array.replicate 16 (0:Nat)
 let mut total:=0
 for band in [:16] do
  starts:=starts.set! band total
  total:=total+counts[band]!
 let mut cursor:=starts
 let mut factors:=Array.replicate total (0:UInt32)
 let mut indices:=Array.replicate total (0:UInt32)
 for j in [:n] do
  let w:=x[offset+j]!
  if Yf w != 0 then
   let delta:=(Yd w-base).toNat
   let band:=delta/4
   if band<16 then
    let dst:=cursor[band]!
    factors:=factors.set! dst (factor w (base+(4*band).toUInt64))
    indices:=indices.set! dst j.toUInt32
    cursor:=cursor.set! band (dst+1)
 return ⟨valid,factors,indices,starts,counts⟩
@[specialize] def block (a ids w:Array UInt32):Nat -> Nat -> UInt64 -> UInt64
 | 0,_,acc=>acc
 | fuel+1,j,acc=>block a ids w fuel (j+1) (acc+ext a[j]!*ext w[ids[j]!.toNat]!)
@[specialize] def groups (a ids w:Array UInt32):Nat -> Nat -> UInt64 -> UInt64 -> UInt64×UInt64
 | 0,_,lo,hi=>(lo,hi)
 | fuel+1,j,lo,hi=>
   let q:=block a ids w 64 j 0
   groups a ids w fuel (j+64) (lo+q) (merge lo hi q)
@[inline] def group (a ids w:Array UInt32) (start n:Nat):UInt64×UInt64:=
 let full:=groups a ids w (n/64) start 0 0
 if n%64=0 then full else
 let q:=block a ids w (n%64) (start+n/64*64) 0
 (full.1+q,merge full.1 full.2 q)
@[inline] def shlo (lo:UInt64) (delta:Nat):UInt64:=if delta<64 then lo<<<delta.toUInt64 else 0
@[inline] def shhi (lo hi:UInt64) (delta:Nat):UInt64:=
 if delta=0 then hi else if delta<64 then (hi<<<delta.toUInt64)|||(lo>>>(64-delta).toUInt64)
 else if delta<128 then lo<<<(delta-64).toUInt64 else 0
def bands (r:Row) (w:Array UInt32) (delta:Nat):Nat -> Nat -> UInt64 -> UInt64 -> UInt64×UInt64
 | 0,_,lo,hi=>(lo,hi)
 | fuel+1,band,lo,hi=>
   let q:=group r.factors r.indices w r.starts[band]! r.lengths[band]!
   let sl:=shlo q.1 (delta+4*band)
   let sh:=shhi q.1 q.2 (delta+4*band)
   let next:=lo+sl
   bands r w delta fuel (band+1) next (hi+sh+(if next<lo then 1 else 0))
@[inline] def dot (r:Row) (w:Array UInt32) (n:Nat) (bx bv:UInt32) (bw:Word) (fallback:Unit -> Word):Word:=
 let body:=Yk (bx>>>16)+Yk (bv>>>16)
 let rawBias:=Yd bw+126
 let base:=if Yf bw=0 then body else min body rawBias
 let bodyHi:=Yk (bx&&&65535)+Yk (bv&&&65535)
 let high:=if Yf bw=0 then bodyHi else max bodyHi rawBias
 if !r.valid||w.size != n||expOf bw=255||high<base||high-base>58 then fallback () else
 let q:=bands r w (body-base).toNat 16 0 0 0
 let bias:Int:=if signOf bw then -((Yf bw).toNat:Int) else (Yf bw).toNat
 let total:=value q.1 q.2+bias*2^((Yd bw).toNat+149-base.toNat)
 if total=0 then fallback () else ExactRuntime.finishWord total ((base.toNat:Int)-298) false
def dense (rows n outW:Nat) (relu:Bool) (X W b:Array Word):Array Word:=
 if rows<4||outW=0||n<16||1048576<n||rows*n>X.size||outW*n>W.size then YaV rows n outW relu X W b else
 let BX:=Array.ofFn (n:=rows) fun i=>Yc X n i.val
 let BV:=Array.ofFn (n:=outW) fun j=>Yc W n j.val
 if !(BX.all fun bx=>(bx&&&(65535:UInt32)) != 255 && QYF bx<=52)||
    !(BV.all fun bv=>(bv&&&(65535:UInt32)) != 255 && QYF bv<=6 && 1<=Yk (bv>>>16)) then YaV rows n outW relu X W b else
 let preparedX:=Array.ofFn (n:=rows) fun i=>prepare X (i.val*n) n (Yk (BX[i.val]!>>>16))
 let preparedW:=Array.ofFn (n:=outW) fun j=>Array.ofFn (n:=n) fun k=>factor W[j.val*n+k.val]! (Yk (BV[j.val]!>>>16))
 YT rows outW fun i j=>act relu (dot preparedX[i]! preparedW[j]! n BX[i]! BV[j]! b[j]! (fun _=>YaU X W b n i j BX[i]! BV[j]!))
end R27Band
