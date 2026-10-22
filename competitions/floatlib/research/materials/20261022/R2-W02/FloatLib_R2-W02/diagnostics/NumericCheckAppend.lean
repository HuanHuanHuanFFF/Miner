namespace R2W02NumericCheck

open Competition FloatLib.Floats

structure Case where
  label : String
  batch : Nat
  m : Nat
  n : Nat
  p : Nat
  a : Array UInt32
  b : Array UInt32

def cases : Array Case := #[
  ⟨"initial-positive-zero", 1, 1, 1, 1, #[0x80000000], #[0x3f800000]⟩,
  ⟨"fma-witness", 1, 1, 2, 1, #[0xbf800000, 0x3f800001], #[0x3f800000, 0x3f7ffffe]⟩,
  ⟨"k-order-witness", 1, 1, 3, 1, #[0x4b800000, 0x3f800000, 0xcb800000],
    #[0x3f800000, 0x3f800000, 0x3f800000]⟩,
  ⟨"underflow-positive-half", 1, 1, 1, 1, #[0x00000001], #[0x3f000000]⟩,
  ⟨"underflow-negative-half", 1, 1, 1, 1, #[0x80000001], #[0x3f000000]⟩,
  ⟨"subnormal-retained", 1, 1, 1, 1, #[0x00800000], #[0x3f000000]⟩,
  ⟨"nan-A-payload", 1, 1, 1, 1, #[0x7fc12345], #[0x3f800000]⟩,
  ⟨"nan-B-sign-payload", 1, 1, 1, 1, #[0x3f800000], #[0xffa12345]⟩,
  ⟨"zero-times-infinity", 1, 1, 1, 1, #[0x00000000], #[0x7f800000]⟩,
  ⟨"overflow-opposition", 1, 1, 2, 1, #[0x7f7fffff, 0x7f7fffff],
    #[0x40000000, 0xc0000000]⟩,
  ⟨"negative-infinity", 1, 1, 1, 1, #[0x7f800000], #[0xbf800000]⟩,
  ⟨"row-boundary-p3", 1, 2, 1, 3, #[0x3f800000, 0x40000000],
    #[0x3f800000, 0x3f800000, 0x3f800000]⟩,
  ⟨"mixed-valid-lanes-p5", 1, 1, 2, 5, #[0x3f800000, 0xbf800000],
    #[0x3f800000, 0x7fc12345, 0x00000001, 0x80000000, 0x7f800000,
      0x40000000, 0x3f800000, 0x00800000, 0x00000000, 0xff800000]⟩,
  ⟨"empty-batch", 0, 3, 2, 5, #[], #[]⟩,
  ⟨"empty-m", 1, 0, 2, 3, #[],
    #[0x7fc12345, 0x7f800000, 0x80000000, 1, 2, 3]⟩,
  ⟨"empty-p", 1, 2, 2, 0, #[0x7fc12345, 0x7f800000, 0, 1], #[]⟩,
  ⟨"empty-reduction", 2, 3, 0, 5, #[], #[]⟩
]

def check (c : Case) : IO Bool := do
  if c.a.size != c.batch * c.m * c.n || c.b.size != c.batch * c.n * c.p then
    IO.println s!"INVALID_TEST_SHAPE {c.label}"
    return false
  let A : Vector Binary32 (c.batch * c.m * c.n) :=
    Vector.ofFn fun i => ExecFloat.Binary.ofBits32 (c.a.getD i.val 0)
  let B : Vector Binary32 (c.batch * c.n * c.p) :=
    Vector.ofFn fun i => ExecFloat.Binary.ofBits32 (c.b.getD i.val 0)
  let got := Submission.bmm c.batch c.m c.n c.p A B
  let expected := Vector.ofFn (bmmSpec c.batch c.m c.n c.p A.get B.get)
  let mut ok := true
  for q in [0:c.batch * c.m * c.p] do
    let g := (got.toArray.getD q posZero).raw.1
    let e := (expected.toArray.getD q posZero).raw.1
    if g != e then
      IO.println s!"FAIL {c.label} q={q} got-word={g.toNat} expected-word={e.toNat}"
      ok := false
  IO.println s!"{c.label} passed={ok} outputs={c.batch * c.m * c.p}"
  return ok

end R2W02NumericCheck

def main : IO UInt32 := do
  let mut ok := true
  for c in R2W02NumericCheck.cases do
    let result ← R2W02NumericCheck.check c
    ok := result && ok
  return if ok then 0 else 1
