import ContractExact

/- Self-authored R27 dynamic moment discriminator, NOT a proven kernel.
Returns none on malformed, nonfinite, unaligned or overflowing input.
Every failed case must use the caller's exact original fallback. -/
namespace R27NormMoment
open ExactRuntime

@[inline] def addPair (h l ah al : UInt64) : Option (UInt64 × UInt64) :=
  let ll := l + al
  let carry : UInt64 := if ll < l then 1 else 0
  let h1 := h + carry
  let h2 := h1 + ah
  if h1 < h || h2 < h1 then none else some (h2, ll)

def minimum (x : Array Word) (base n : Nat) : Nat := Id.run do
  let mut low := 254
  for j in [0:n] do
    let w := x[base+j]!
    if mantOf w ≠ 0 then low := min low (idxOf w)
  return low

def scan (x : Array Word) (base low : Nat) :
    Nat → Nat → UInt64 → UInt64 → UInt64 → UInt64 → UInt64 → UInt64 →
    Option (Int × Nat)
  | 0, _, ph, pl, nh, nl, qh, ql =>
      some (Int.ofNat ((ph.toNat <<< 64) + pl.toNat) -
        Int.ofNat ((nh.toNat <<< 64) + nl.toNat),
        (qh.toNat <<< 64) + ql.toNat)
  | left+1, j, ph, pl, nh, nl, qh, ql =>
      let w := x[base+j]!
      let magnitude := mantOf w
      let index := idxOf w
      if expOf w = 255 || (magnitude ≠ 0 && (index < low || 40 < index-low)) then none
      else
        let m := magnitude.toUInt64
        let s := (index-low).toUInt64
        let term := m <<< s
        let square := m*m
        let lo := if 2*s < 64 then square <<< (2*s) else 0
        let hi := if 2*s < 64 then (square >>> 1) >>> (63-2*s) else square <<< (2*s-64)
        match addPair qh ql hi lo with
        | none => none
        | some (qh',ql') =>
          if signOf w then
            match addPair nh nl 0 term with
            | none => none
            | some (nh',nl') => scan x base low left (j+1) ph pl nh' nl' qh' ql'
          else
            match addPair ph pl 0 term with
            | none => none
            | some (ph',pl') => scan x base low left (j+1) ph' pl' nh nl qh' ql'

def prepare (x : Array Word) (base n : Nat) : Option (Nat × Int × Nat) :=
  if base+n > x.size then none
  else
    let low := minimum x base n
    match scan x base low n 0 0 0 0 0 0 0 with
    | none => none
    | some (s,q) => some (low,s,q)

end R27NormMoment
