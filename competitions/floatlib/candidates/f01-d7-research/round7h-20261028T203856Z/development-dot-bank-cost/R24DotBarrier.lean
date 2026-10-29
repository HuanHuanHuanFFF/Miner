import Submission
namespace R24DotBarrier
abbrev RawBank := Array (Array UInt32)
abbrev BankPair := RawBank × RawBank
@[noinline] def touchBank (i : Nat) (p : BankPair) : BankPair :=
  if i == 1000000007 then (p.1, p.1) else p
end R24DotBarrier
