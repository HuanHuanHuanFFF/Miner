namespace Submission.R26WordBlock

def shapeArrayBlock (n : Nat) (a b : Array UInt32) : UInt64 × UInt64 :=
  body128 n (fun i => a[i]!) (fun i => b[i]!)

def shapeLiteralPrepared (n : Nat) (a b : Array UInt32) : UInt64 × UInt64 :=
  preparedBody n (fun i => a[i]!) (fun i => b[i]!)

def shapeCachedPrepared (n : Nat) (a b : Array UInt32) (ma mb : UInt32) : UInt64 × UInt64 :=
  if canBlock16 n ma mb then body128 n (fun i => a[i]!) (fun i => b[i]!)
  else body128Each (fun i => a[i]!) (fun i => b[i]!) n 0 0 0

end Submission.R26WordBlock
