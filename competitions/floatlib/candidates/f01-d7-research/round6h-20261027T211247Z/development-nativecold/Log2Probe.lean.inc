/- NOT_RUN: ordinary existing public API, codegen prerequisite only. -/
namespace R22Log2SourceProbe
@[noinline] def word32 (x : UInt32) : UInt32 := x.log2
@[noinline] def word64 (x : UInt64) : UInt64 := x.log2
theorem word32_eq (x : UInt32) : word32 x = x.log2 := rfl
theorem word64_eq (x : UInt64) : word64 x = x.log2 := rfl
end R22Log2SourceProbe
