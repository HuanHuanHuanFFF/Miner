import Submission

namespace R24DotBarrier
abbrev RawPair := Array UInt32 × Array UInt32
abbrev ExactPair := Submission.R24DotProbe.ExactOperand × Submission.R24DotProbe.ExactOperand
abbrev LazyPair := Submission.R24DotProbe.FpPrepared × Submission.R24DotProbe.FpPrepared
abbrev EagerPair := Submission.R24DotProbe.EagerOperand × Submission.R24DotProbe.EagerOperand

@[noinline] def touchRaw (i : Nat) (p : RawPair) : RawPair :=
  if i == 1000000007 then (p.1, p.1) else p

@[noinline] def touchExact (i : Nat) (p : ExactPair) : ExactPair :=
  if i == 1000000007 then (p.1, p.1) else p

@[noinline] def touchLazy (i : Nat) (p : LazyPair) : LazyPair :=
  if i == 1000000007 then (p.1, p.1) else p

@[noinline] def touchEager (i : Nat) (p : EagerPair) : EagerPair :=
  if i == 1000000007 then (p.1, p.1) else p

end R24DotBarrier
