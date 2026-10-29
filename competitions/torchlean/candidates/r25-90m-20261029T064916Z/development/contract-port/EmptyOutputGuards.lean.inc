/-! Return empty outputs before constructing caches or input windows. -/

theorem array_empty_of_size (a : Array Word) (h : a.size = 0) : a = #[] := by
  apply Array.ext (by simpa using h)
  intro i h1 h2
  simp at h2

def linearCached (rows inW outW : Nat) (relu : Bool) (X W b : Array Word) : Array Word :=
  if rows * outW = 0 then #[] else linearPreGuard rows inW outW relu X W b

theorem linearCached_eq : linearCached = linearWith dotFn := by
  funext rows inW outW relu X W b
  unfold linearCached
  split_ifs with hz
  · symm; apply array_empty_of_size; simp [linearWith, hz]
  · rw [linearPreGuard_eq]

def gemmCached (batch m k n : Nat) (A B : Array Word) : Array Word :=
  if batch * (m * n) = 0 then #[] else gemmPreGuard batch m k n A B

theorem gemmCached_eq : gemmCached = gemmWith dotFn := by
  funext batch m k n A B
  unfold gemmCached
  split_ifs with hz
  · symm; apply array_empty_of_size; simp [gemmWith, hz]
  · rw [gemmPreGuard_eq]

def conv2dCached (s : ConvShape) (relu : Bool) (inp wts b : Array Word) : Array Word :=
  if s.cout * (s.ho * s.wo) = 0 then #[] else conv2dPreGuard s relu inp wts b

theorem conv2dCached_eq : conv2dCached = conv2dWith dotFn := by
  funext s relu inp wts b
  unfold conv2dCached
  split_ifs with hz
  · symm; apply array_empty_of_size; simp [conv2dWith, hz]
  · rw [conv2dPreGuard_eq]

def depthwiseCached (s : ConvShape) (relu : Bool) (inp wts b : Array Word) : Array Word :=
  if s.cin * (s.ho * s.wo) = 0 then #[] else depthwisePreGuard s relu inp wts b

theorem depthwiseCached_eq : depthwiseCached = depthwiseWith dotFn := by
  funext s relu inp wts b
  unfold depthwiseCached
  split_ifs with hz
  · symm; apply array_empty_of_size; simp [depthwiseWith, hz]
  · rw [depthwisePreGuard_eq]

def rmsnormCached (rows n : Nat) (eps : Word) (x g : Array Word) : Array Word :=
  if rows * n = 0 then #[] else rmsnormPreGuard rows n eps x g

theorem rmsnormCached_eq : rmsnormCached = rmsnormWith dotFn := by
  funext rows n eps x g
  unfold rmsnormCached
  split_ifs with hz
  · symm
    apply array_empty_of_size
    simp only [rmsnormWith]
    split_ifs <;> simp [rmsnormStable, rmsnormLegacyWith, hz]
  · rw [rmsnormPreGuard_eq]

def layernormCached (rows n : Nat) (eps : Word) (x g b : Array Word) : Array Word :=
  if rows * n = 0 then #[] else layernormPreGuard rows n eps x g b

theorem layernormCached_eq : layernormCached = layernormWith dotFn := by
  funext rows n eps x g b
  unfold layernormCached
  split_ifs with hz
  · symm
    apply array_empty_of_size
    simp only [layernormWith]
    split_ifs <;> simp [layernormStable, layernormLegacyWith, hz]
  · rw [layernormPreGuard_eq]
