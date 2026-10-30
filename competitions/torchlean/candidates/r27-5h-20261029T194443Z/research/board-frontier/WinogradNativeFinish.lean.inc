/- Original helper inserted within R27Winograd. Native-only: no new Correct.
The source predecessor's YL/YD perform bias insertion and exact final rounding.
Wide alignment gaps keep the complete Int fallback. -/

@[inline] def top128 (hi : UInt64) : UInt64 := 0-(hi >>> 63)

@[inline] def finishWords (X W b : Array Word) (row n col productIndex : Nat)
    (hi lo : UInt64) : Word :=
  let bw := b[col]!
  let top := top128 hi
  if mantOf bw == 0 then
    let value := Submission.YD top hi lo 0 ((productIndex : Int)-298)
    if value < 0x100000000 then value.toUInt32
    else R27PackedLinear.exactZero X W b row n col
  else
    let biasIndex := 126+idxOf bw
    let low := min productIndex biasIndex
    let bodyShift := productIndex-low
    let biasShift := biasIndex-low
    if bodyShift ≤ 63 && biasShift < 128 then
      let complete := fun w2 w1 w0 =>
        Submission.YL low.toUInt64 oneW bw w2 w1 w0 0
          (fun t2 t1 t0 c => Submission.YD t2 t1 t0 c ((low : Int)-298))
      let value := if bodyShift == 0 then complete top hi lo else
        let s := bodyShift.toUInt64
        complete ((top <<< s) ||| (hi >>> (64-s)))
          ((hi <<< s) ||| (lo >>> (64-s))) (lo <<< s)
      if value < 0x100000000 then value.toUInt32
      else R27PackedLinear.exactZero X W b row n col
    else R27PackedLinear.finish X W b row n col productIndex (signed128 hi lo)

@[specialize] def totalWords {α : Type} (next : UInt64 → UInt64 → α)
    (a b : Cached) (n : Nat) : α :=
  cross (fun h l => subtract h l a.selfHi a.selfLo fun h l =>
    subtract h l b.selfHi b.selfLo fun h l =>
      if n % 2 == 0 then next h l
      else
        let x := a.data[n-1]!.toUInt64
        let y := b.data[n-1]!.toUInt64
        addSigned h l ((x &&& 0xFFFFFFFF)*(y &&& 0xFFFFFFFF))
          (((x ^^^ y) >>> 32) != 0) next)
    a.data b.data (n/2) 0 0 0

