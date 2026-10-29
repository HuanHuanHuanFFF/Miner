/- One terminal integer conversion and official finishWord call per dot.
   This avoids assuming the unproved manual word RNE implementation correct. -/
def finishOfficial64 (base : UInt32) (negativeZero : Bool) (acc : UInt64) : UInt32 :=
  let signed : Int := if acc &&& 0x8000000000000000 == 0 then (acc.toNat : Int)
    else (acc.toNat : Int) - 18446744073709551616
  finishWord signed ((base.toNat : Int) - 298) negativeZero

def finishOfficial128 (base : UInt32) (negativeZero : Bool)
    (pLo pHi nLo nHi : UInt64) : UInt32 :=
  let positive : Int := (pLo.toNat : Int) + (pHi.toNat : Int) * 18446744073709551616
  let negative : Int := (nLo.toNat : Int) + (nHi.toNat : Int) * 18446744073709551616
  finishWord (positive - negative) ((base.toNat : Int) - 298) negativeZero

