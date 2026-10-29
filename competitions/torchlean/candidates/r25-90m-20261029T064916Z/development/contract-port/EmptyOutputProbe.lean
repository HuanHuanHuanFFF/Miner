import Submission

open ExactRuntime

def expectEmpty (label : String) (out : Array Word) : IO Unit := do
  if out.size != 0 then throw (IO.userError s!"{label}: expected empty output")
  IO.println s!"EMPTY_OK {label}"

/-- Diagnostic only. Pass runtime argument0; capture stderr as well as exit code.
The runtime argument prevents treating the zero dimensions as source constants. -/
def main (args : List String) : IO Unit := do
  let z := (args.head?.getD "0").toNat!
  let k := Submission.kernels
  expectEmpty "linear-zero-rows" (k.dense.linear z 1 1 false #[] #[] #[])
  expectEmpty "linear-zero-width" (k.dense.linear 1 1 z false #[] #[] #[])
  expectEmpty "gemm-zero-batch" (k.dense.gemm z 1 1 1 #[] #[])
  expectEmpty "gemm-zero-rows" (k.dense.gemm 1 z 1 1 #[] #[])
  let conv : ConvShape := ⟨1, 1, 1, z, 1, 1, 1, 0⟩
  expectEmpty "conv-zero-cout-empty-input" (k.conv.conv2d conv false #[] #[] #[])
  let dw : ConvShape := ⟨z, 1, 1, 1, 1, 1, 1, 0⟩
  expectEmpty "depthwise-zero-cin" (k.conv.depthwise dw false #[] #[] #[])
  expectEmpty "rms-zero-rows" (k.norm.rmsnorm z 1 0x3727C5AC #[] #[])
  expectEmpty "rms-zero-width" (k.norm.rmsnorm 1 z 0x3727C5AC #[] #[])
  expectEmpty "layer-zero-rows" (k.norm.layernorm z 1 0x3727C5AC #[] #[] #[])
  expectEmpty "layer-zero-width" (k.norm.layernorm 1 z 0x3727C5AC #[] #[] #[])
