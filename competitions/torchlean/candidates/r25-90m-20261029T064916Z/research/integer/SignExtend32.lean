import ContractExact

/- Original minimal word-identity draft. NOT_COMPILED; even availability of the
   bv_decide tactic through ContractExact is unverified. The Python/paper
   evidence must not be reported as acceptance of this source. -/
namespace R25SignExtend32

@[inline] def extend (w : UInt32) : UInt64 :=
  (w.toUInt64 ^^^ 0x80000000) - 0x80000000

/-- The xor/sub expression has exactly the standard 32-to-64 sign-extension
    bit pattern, including -2^31 and -1. This is a word equality only. -/
theorem extend_eq (w : UInt32) :
    extend w =
      if w < 0x80000000 then w.toUInt64
      else w.toUInt64 + 0xffffffff00000000 := by
  unfold extend
  bv_decide

end R25SignExtend32
