import Submission

/- Optional owned diagnostic executable only. No benchmark, proof or adoption.
   Compare actual full-record entry to its proved retained reference on explicit
   special values, signed zeros, subnormals and zero output extents. -/
open ExactRuntime

def compareKernel (label : String) (f : Kernels → Array Word) : IO Unit := do
  let observed := f Submission.kernels
  let expected := f Submission.retainedKernels
  if observed != expected then
    throw <| IO.userError s!"NATIVE_FIXTURE_MISMATCH {label}: actual={observed.toList} expected={expected.toList}"

def fixtures : Array Word := #[
  0, 0x80000000, 1, 0x80000001, 0x007fffff, 0x00800000,
  0x3f800000, 0xbf800000, 0x7f7fffff, 0xff7fffff,
  0x7f800000, 0xff800000, 0x7fa12345, 0x7fc54321, 0xffa22222]

def main : IO Unit := do
  let mut checks := 0
  for i in [:fixtures.size] do
    let word := fixtures[i]!
    let a := Array.replicate 40 word
    let ones := Array.replicate 40 oneW
    compareKernel s!"sum/{i}" (fun k => #[k.core.sum a])
    compareKernel s!"dot/{i}" (fun k => #[k.core.dot a ones])
    compareKernel s!"dot-mismatch/{i}" (fun k => #[k.core.dot a #[]])
    compareKernel s!"linear/{i}" (fun k =>
      k.dense.linear 1 39 2 false (Array.replicate 39 word)
        (Array.replicate 78 oneW) #[0x80000000, word])
    compareKernel s!"gemm/{i}" (fun k =>
      k.dense.gemm 1 2 40 2 (Array.replicate 80 word) (Array.replicate 80 oneW))
    let sh : ConvShape := ⟨1, 1, 1, 2, 3, 3, 1, 1⟩
    compareKernel s!"conv-padding/{i}" (fun k =>
      k.conv.conv2d sh false #[word] (Array.replicate 18 word) #[0x80000000, word])
    let dw : ConvShape := ⟨2, 2, 2, 0, 1, 1, 1, 0⟩
    compareKernel s!"depthwise-ignore-cout/{i}" (fun k =>
      k.conv.depthwise dw false (Array.replicate 8 word) #[oneW, oneW] #[0x80000000, word])
    compareKernel s!"avgpool/{i}" (fun k => k.elem.avgpool 1 2 2 2 (Array.replicate 4 word))
    checks := checks + 8
  compareKernel "linear-empty-rows" (fun k => k.dense.linear 0 1000000 3 false #[] #[] #[])
  compareKernel "linear-empty-out" (fun k => k.dense.linear 3 1000000 0 false #[] #[] #[])
  compareKernel "gemm-empty-n" (fun k => k.dense.gemm 2 3 1000000 0 #[] #[])
  compareKernel "gemm-empty-m" (fun k => k.dense.gemm 2 0 1000000 3 #[] #[])
  compareKernel "gemm-empty-batch" (fun k => k.dense.gemm 0 3 1000000 3 #[] #[])
  compareKernel "conv-empty-cout" (fun k =>
    k.conv.conv2d ⟨3, 1000, 1000, 0, 3, 3, 1, 1⟩ false #[] #[] #[])
  compareKernel "depthwise-empty-cin" (fun k =>
    k.conv.depthwise ⟨0, 1000, 1000, 99, 3, 3, 1, 1⟩ false #[] #[] #[])
  compareKernel "conv-zero-k-bias" (fun k =>
    k.conv.conv2d ⟨0, 1, 1, 2, 1, 1, 1, 0⟩ false #[] #[] #[0x80000000, 0x7fa12345])
  compareKernel "maxpool" (fun k => k.elem.maxpool 1 2 2 2 #[0x80000000, 0, 0xbf800000, oneW])
  compareKernel "addRelu" (fun k => k.elem.addRelu true #[0x80000000, 0x7fa12345, oneW] #[0, oneW, 0xbf800000])
  compareKernel "scaleShift" (fun k => k.elem.scaleShift false 1 3 #[0x80000000, 0x7fa12345, oneW] #[oneW] #[0x80000000])
  compareKernel "rmsnorm" (fun k => k.norm.rmsnorm 1 2 0x358637bd #[oneW, 0xbf800000] #[oneW, oneW])
  compareKernel "layernorm" (fun k => k.norm.layernorm 1 2 0x358637bd #[oneW, 0xbf800000] #[oneW, oneW] #[0, 0])
  IO.println s!"NATIVE_FIXTURE_DONE checks={checks + 13} all_words_match=true scope=FINITE_ONLY_UNPROVED"
