import ContractExact

namespace R28ZeroWord

def lo (x w : UInt64) : UInt64 := (x &&& 0x1FFFFFF) * (w - 0x80000000)
def hi (x w : UInt64) : UInt64 := ((x >>> 25) - 0x100000000) * (w - 0x80000000)

theorem lowZero (w : UInt64) : lo 0x200000000000000 w = 0 := by
  simp only [lo, show ((0x200000000000000 : UInt64) &&& 0x1FFFFFF) = 0 from by decide,
    UInt64.zero_mul]

theorem highZero (w : UInt64) : hi 0x200000000000000 w = 0 := by
  simp only [hi, show (((0x200000000000000 : UInt64) >>> 25) - 0x100000000) = 0 from by decide,
    UInt64.zero_mul]

end R28ZeroWord
