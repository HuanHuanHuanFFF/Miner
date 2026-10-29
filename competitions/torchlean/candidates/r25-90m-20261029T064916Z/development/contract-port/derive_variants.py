"""Derive own cache experiments; no native toolchain or official file is changed."""
from pathlib import Path

HERE = Path(__file__).resolve().parent

ADAPTIVE = r'''
/-! One-row dense calls reuse X across output channels but do not reuse W. -/
def linearInputCached (rows inW outW : Nat) (relu : Bool) (X W b : Array Word) : Array Word :=
  let dx := cacheWords X
  Array.ofFn (n := rows * outW) fun q =>
    let i := q.val / outW
    let j := q.val % outW
    act relu <| dotCached (inW + 1)
      (fun t => if t < inW then X[i * inW + t]! else oneW)
      (fun t => if t < inW then W[j * inW + t]! else b[j]!)
      (fun t => if t < inW then dx[i * inW + t]! else decodeWord oneW)
      (fun t => decodeWord (if t < inW then W[j * inW + t]! else b[j]!))

theorem linearInputCached_eq : linearInputCached = linearWith dotFn := by
  funext rows inW outW relu X W b
  unfold linearInputCached linearWith
  apply congrArg (fun f : Fin (rows * outW) → Word => Array.ofFn f)
  funext q
  dsimp only
  apply congrArg (act relu)
  apply dotCached_eq
  · intro t
    split_ifs <;> simp only [cacheWords_get]
  · intro t; rfl

def linearCached (rows inW outW : Nat) (relu : Bool) (X W b : Array Word) : Array Word :=
  if rows ≤ 1 then linearInputCached rows inW outW relu X W b
  else linearBothCached rows inW outW relu X W b

theorem linearCached_eq : linearCached = linearWith dotFn := by
  funext rows inW outW relu X W b
  simp only [linearCached, linearInputCached_eq, linearBothCached_eq, ite_self]
'''

def main() -> None:
    original = (HERE / "DecodeCache.lean.inc").read_text(encoding="utf-8")
    adaptive = original.replace("linearCached", "linearBothCached") + "\n" + ADAPTIVE
    (HERE / "AdaptiveCache.lean.inc").write_text(adaptive, encoding="utf-8")
    patch = adaptive.replace("conv2dCached", "conv2dTensorCached") + "\n" + (HERE / "PatchCacheExtra.lean.inc").read_text(encoding="utf-8")
    (HERE / "PatchCache.lean.inc").write_text(patch, encoding="utf-8")
    (HERE / "PatchNormCache.lean.inc").write_text(patch + "\n" + (HERE / "NormCache.lean.inc").read_text(encoding="utf-8"), encoding="utf-8")
    norm_helpers = (HERE / "NormCache.lean.inc").read_text(encoding="utf-8").split("def rmsnormStableCached", 1)[0]
    integer_norm = norm_helpers + "\n" + (HERE / "IntegerNormStats.lean.inc").read_text(encoding="utf-8") + "\n" + (HERE / "IntegerNormRuntime.lean.inc").read_text(encoding="utf-8")
    (HERE / "IntegerNormCache.lean.inc").write_text(integer_norm, encoding="utf-8")


if __name__ == "__main__":
    main()
