/- Diagnostic only: same raw4 x row-major B2 arithmetic/output as resident8.
   Only word-fit guarding and hot address/cursor representation change.
   New all-input equality/Lean/native/cost remain NOT_RUN. -/
namespace Submission.R22IndexedResident8
open FloatLib.Floats Competition

abbrev BP := R22Pair8.BP
abbrev Acc := R22Pair8.Cell
abbrev Words := R22Resident8.Words

/- Proof-only cursor iteration; no Nat ghost value is a runtime loop argument. -/
def advance (cursor stride : USize) : Nat → USize
  | 0 => cursor
  | t + 1 => advance cursor stride t + stride

theorem advance_shift (cursor stride : USize) (t : Nat) :
    advance (cursor + stride) stride t = advance cursor stride (t + 1) := by
  induction t with
  | zero => rfl
  | succ t ih => exact congrArg (fun v : USize => v + stride) ih

theorem advance_toNat (base stride : Nat) (hb : base < USize.size)
    (hs : stride < USize.size) (t : Nat) :
    base + t * stride < USize.size →
      (advance (USize.ofNat base) (USize.ofNat stride) t).toNat = base + t * stride := by
  induction t with
  | zero =>
    intro h
    simpa only [advance, Nat.zero_mul, Nat.add_zero] using USize.toNat_ofNat_of_lt' hb
  | succ t ih =>
    intro h
    have hp : base + t * stride < USize.size := by
      rw [Nat.succ_mul] at h
      omega
    have ht := ih hp
    have ha : (advance (USize.ofNat base) (USize.ofNat stride) t).toNat +
        (USize.ofNat stride).toNat < USize.size := by
      rw [ht, USize.toNat_ofNat_of_lt' hs]
      simpa only [Nat.succ_mul, Nat.add_assoc] using h
    change (advance (USize.ofNat base) (USize.ofNat stride) t + USize.ofNat stride).toNat = _
    rw [Packed10Index.addNat _ _ ha, ht, USize.toNat_ofNat_of_lt' hs]
    simp only [Nat.succ_mul, Nat.add_assoc]

theorem add_read_bound (base n size : Nat) (hb : base < USize.size)
    (hn : n < USize.size) (hl : base + (n - 1) < size) (hs : size < USize.size)
    (j : USize) (hj : j < USize.ofNat n) : (USize.ofNat base + j).toNat < size := by
  have hkn : j.toNat < n := by
    have h := USize.lt_iff_toNat_lt.mp hj
    simpa only [USize.toNat_ofNat_of_lt' hn] using h
  have h := Packed10Index.boundA base n j.toNat size hl hkn
  have ha : (USize.ofNat base).toNat + j.toNat < USize.size := by
    rw [USize.toNat_ofNat_of_lt' hb]
    exact Nat.lt_trans h hs
  rw [Packed10Index.addNat _ _ ha, USize.toNat_ofNat_of_lt' hb]
  exact h

def wordLoop (count a0 a1 a2 a3 stride : USize) (A : Array Binary32) (cache : Array BP)
    (hA : ∀ j : USize, j < count →
      (a0 + j).toNat < A.size ∧ (a1 + j).toNat < A.size ∧
      (a2 + j).toNat < A.size ∧ (a3 + j).toNat < A.size)
    (k cursor : USize)
    (hB : ∀ t : Nat, k.toNat + t < count.toNat → (advance cursor stride t).toNat < cache.size)
    (q00 q10 q20 q30 q01 q11 q21 q31 : Float32) : Acc :=
  if hk : k < count then
    have hb : cursor.toNat < cache.size := by
      have h := hB 0 (by have hh := USize.lt_iff_toNat_lt.mp hk; omega)
      simpa only [advance] using h
    have nextB : ∀ t : Nat, (k + 1).toNat + t < count.toNat →
        (advance (cursor + stride) stride t).toNat < cache.size := by
      intro t ht
      rw [advance_shift]
      apply hB (t + 1)
      rw [Packed10Index.stepNat hk] at ht
      omega
    let f0 := R2W01b.convert (A.uget (a0 + k) (hA k hk).1).raw.1
    let f1 := R2W01b.convert (A.uget (a1 + k) (hA k hk).2.1).raw.1
    let f2 := R2W01b.convert (A.uget (a2 + k) (hA k hk).2.2.1).raw.1
    let f3 := R2W01b.convert (A.uget (a3 + k) (hA k hk).2.2.2).raw.1
    let b := cache.uget cursor hb
    wordLoop count a0 a1 a2 a3 stride A cache hA (k + 1) (cursor + stride) nextB
      (q00 + f0 * b.s0) (q10 + f1 * b.s0) (q20 + f2 * b.s0) (q30 + f3 * b.s0)
      (q01 + f0 * b.s1) (q11 + f1 * b.s1) (q21 + f2 * b.s1) (q31 + f3 * b.s1)
  else ⟨q00, q10, q20, q30, q01, q11, q21, q31⟩
termination_by count.toNat - k.toNat
decreasing_by all_goals exact Packed10Index.next_decreases (by assumption)

structure TileBounds (p n baseA baseC asize csize : Nat) : Prop where
  positive : 1 < n
  nword : n < USize.size
  aword : asize < USize.size
  cword : csize < USize.size
  alast : baseA + 3 * n + (n - 1) < asize
  blast : baseC + (n - 1) * R22Pair8.groups p < csize

structure BlockBounds (p n baseA baseC asize csize : Nat) : Prop where
  positive : 1 < n
  nword : n < USize.size
  aword : asize < USize.size
  cword : csize < USize.size
  alast : baseA + 3 * n + (n - 1) < asize
  blast : baseC + (n - 1) * R22Pair8.groups p + (R22Pair8.groups p - 1) < csize

def within (p n baseA baseC : Nat) (A : Array Binary32) (cache : Array BP)
    (h : TileBounds p n baseA baseC A.size cache.size) : Acc :=
  have haLast := h.alast
  have haSize := h.aword
  have hcLast := h.blast
  have hcSize := h.cword
  have hb0 : baseA < USize.size := by omega
  have hb1 : baseA + n < USize.size := by omega
  have hb2 : baseA + 2 * n < USize.size := by omega
  have hb3 : baseA + 3 * n < USize.size := by omega
  have hbc : baseC < USize.size := by omega
  have hstride : R22Pair8.groups p < USize.size := by
    have hm := Nat.mul_le_mul_right (R22Pair8.groups p)
      (show 1 ≤ n - 1 by have hn := h.positive; omega)
    simp only [Nat.one_mul] at hm
    have hl := h.blast
    have hc := h.cword
    omega
  have hA : ∀ j : USize, j < USize.ofNat n →
      (USize.ofNat baseA + j).toNat < A.size ∧
      (USize.ofNat (baseA + n) + j).toNat < A.size ∧
      (USize.ofNat (baseA + 2 * n) + j).toNat < A.size ∧
      (USize.ofNat (baseA + 3 * n) + j).toNat < A.size := by
    intro j hj
    exact ⟨add_read_bound _ _ _ hb0 h.nword (by have hl := h.alast; omega) h.aword j hj,
      add_read_bound _ _ _ hb1 h.nword (by have hl := h.alast; omega) h.aword j hj,
      add_read_bound _ _ _ hb2 h.nword (by have hl := h.alast; omega) h.aword j hj,
      add_read_bound _ _ _ hb3 h.nword h.alast h.aword j hj⟩
  have hB : ∀ t : Nat, (0 : USize).toNat + t < (USize.ofNat n).toNat →
      (advance (USize.ofNat baseC) (USize.ofNat (R22Pair8.groups p)) t).toNat < cache.size := by
    intro t ht
    have htn : t < n := by
      simpa only [USize.toNat_zero, Nat.zero_add, USize.toNat_ofNat_of_lt' h.nword] using ht
    have hm := Nat.mul_le_mul_right (R22Pair8.groups p) (show t ≤ n - 1 by omega)
    have hl : baseC + t * R22Pair8.groups p < cache.size := by have hh := h.blast; omega
    rw [advance_toNat baseC (R22Pair8.groups p) hbc hstride t (Nat.lt_trans hl h.cword)]
    exact hl
  wordLoop (USize.ofNat n) (USize.ofNat baseA) (USize.ofNat (baseA + n))
    (USize.ofNat (baseA + 2 * n)) (USize.ofNat (baseA + 3 * n))
    (USize.ofNat (R22Pair8.groups p)) A cache hA 0 (USize.ofNat baseC) hB
    Packed10.zero32 Packed10.zero32 Packed10.zero32 Packed10.zero32
    Packed10.zero32 Packed10.zero32 Packed10.zero32 Packed10.zero32

@[noinline] def tile (p n baseA baseB baseC : Nat) (A B : Array Binary32)
    (cache : Array BP) (h : TileBounds p n baseA baseC A.size cache.size) (second : Bool) : Words :=
  let r := within p n baseA baseC A cache h
  match r with
  | ⟨q00, q10, q20, q30, q01, q11, q21, q31⟩ =>
    let w00 := (Packed10.finish n baseA baseB p A B q00).raw.1
    let w10 := (Packed10.finish n (baseA + n) baseB p A B q10).raw.1
    let w20 := (Packed10.finish n (baseA + 2 * n) baseB p A B q20).raw.1
    let w30 := (Packed10.finish n (baseA + 3 * n) baseB p A B q30).raw.1
    if second then
      ⟨w00, w10, w20, w30,
        (Packed10.finish n baseA (baseB + 1) p A B q01).raw.1,
        (Packed10.finish n (baseA + n) (baseB + 1) p A B q11).raw.1,
        (Packed10.finish n (baseA + 2 * n) (baseB + 1) p A B q21).raw.1,
        (Packed10.finish n (baseA + 3 * n) (baseB + 1) p A B q31).raw.1⟩
    else ⟨w00, w10, w20, w30, (0 : UInt32), (0 : UInt32), (0 : UInt32), (0 : UInt32)⟩

def tiles (p n baseA baseB baseC : Nat) (A B : Array Binary32) (cache : Array BP)
    (h : BlockBounds p n baseA baseC A.size cache.size) : Vector Words (R22Pair8.groups p) :=
  Vector.ofFn (fun g => tile p n baseA (baseB + 2 * g.val) (baseC + g.val) A B cache
    { positive := h.positive, nword := h.nword, aword := h.aword, cword := h.cword,
      alast := h.alast, blast := by have hg := g.isLt; have hl := h.blast; omega }
    (decide (2 * g.val + 1 < p)))

@[noinline] def rows4 (p n baseA baseB baseC : Nat) (A B : Array Binary32) (cache : Array BP)
    (h : BlockBounds p n baseA baseC A.size cache.size) (out : Array Binary32) : Array Binary32 :=
  if p = 0 then out else
    let t := tiles p n baseA baseB baseC A B cache h
    let out := RowStream.emit p (R22Resident8.read0 t) out
    let out := RowStream.emit p (R22Resident8.read1 t) out
    let out := RowStream.emit p (R22Resident8.read2 t) out
    RowStream.emit p (R22Resident8.read3 t) out

theorem rows4_size (p n baseA baseB baseC : Nat) (A B : Array Binary32) (cache : Array BP)
    (h : BlockBounds p n baseA baseC A.size cache.size) (out : Array Binary32) :
    (rows4 p n baseA baseB baseC A B cache h out).size = out.size + 4 * p := by
  unfold rows4
  split
  · rename_i hp; subst p; simp
  · simp only [R21StreamingPair.emit_size]; omega

abbrev RowBounds (m n p b : Nat) (A : Array Binary32) (cache : Array BP) : Prop :=
  ∀ r : Fin (m / 4), BlockBounds p n ((b * m + 4 * r.val) * n)
    (b * n * R22Pair8.groups p) A.size cache.size

def blocks (m n p b : Nat) (A B : Array Binary32) (cache : Array BP)
    (h : RowBounds m n p b A cache) (out : Array Binary32) : Array Binary32 :=
  Fin.foldl (m / 4) (fun acc r => rows4 p n ((b * m + 4 * r.val) * n)
    (b * n * p) (b * n * R22Pair8.groups p) A B cache (h r) acc) out

theorem blocks_size (m n p b : Nat) (A B : Array Binary32) (cache : Array BP)
    (h : RowBounds m n p b A cache) (out : Array Binary32) :
    (blocks m n p b A B cache h out).size = out.size + (m / 4) * (4 * p) := by
  unfold blocks
  apply RowStream.foldl_inv (m / 4) _
    (fun k (acc : Array Binary32) => acc.size = out.size + k * (4 * p))
  · intro r acc ha
    rw [rows4_size, ha, Nat.add_mul]
    simp only [Nat.one_mul, Nat.add_assoc]
  · simp

def rows (m n p b : Nat) (A B : Array Binary32) (cache : Array BP)
    (h : RowBounds m n p b A cache) (out : Array Binary32) : Array Binary32 :=
  let out := blocks m n p b A B cache h out
  RowStream.emit ((m % 4) * p) (fun j => NativeFinal.dot n
    ((b * m + m / 4 * 4 + j.val / p) * n) (b * n * p + j.val % p) p A B) out

theorem rows_size (m n p b : Nat) (A B : Array Binary32) (cache : Array BP)
    (h : RowBounds m n p b A cache) (out : Array Binary32) :
    (rows m n p b A B cache h out).size = out.size + m * p := by
  have hd : m / 4 * 4 + m % 4 = m := by omega
  simp only [rows, R21StreamingPair.emit_size, blocks_size]
  calc
    out.size + m / 4 * (4 * p) + m % 4 * p =
        out.size + (m / 4 * 4 + m % 4) * p := by
      simp only [Nat.add_mul, Nat.mul_assoc, Nat.add_assoc]
    _ = out.size + m * p := by rw [hd]

def output (batch m n p : Nat) (A B : Array Binary32) (cache : Array BP)
    (h : ∀ b : Fin batch, RowBounds m n p b.val A cache) : Array Binary32 :=
  Fin.foldl batch (fun acc b => rows m n p b.val A B cache (h b) acc)
    (Array.mkEmpty (batch * m * p))

theorem output_size (batch m n p : Nat) (A B : Array Binary32) (cache : Array BP)
    (h : ∀ b : Fin batch, RowBounds m n p b.val A cache) :
    (output batch m n p A B cache h).size = batch * m * p := by
  unfold output
  have hh := RowStream.foldl_inv batch (fun acc b => rows m n p b.val A B cache (h b) acc)
    (fun k (acc : Array Binary32) => acc.size = k * (m * p))
    (by intro b acc ha; rw [rows_size, ha, Nat.add_mul]; simp)
    (Array.mkEmpty (batch * m * p)) (by simp)
  simpa only [Nat.mul_assoc] using hh

theorem all_bounds (batch m n p : Nat) (A : Array Binary32) (cache : Array BP)
    (ha : A.size = batch * m * n) (hc : cache.size = batch * n * R22Pair8.groups p)
    (hn : 1 < n) (hp : 2 ≤ p)
    (hnw : n < USize.size) (haw : A.size < USize.size) (hcw : cache.size < USize.size) :
    ∀ b : Fin batch, RowBounds m n p b.val A cache := by
  intro b r
  have hr : 4 * r.val + 4 ≤ m := by have hh := r.isLt; omega
  have hbm := Nat.mul_le_mul_right m (Nat.succ_le_of_lt b.isLt)
  rw [Nat.succ_mul] at hbm
  have hrow : b.val * m + 4 * r.val + 4 ≤ batch * m := by omega
  have hrows := Nat.mul_le_mul_right n hrow
  rw [Nat.add_mul] at hrows
  have halast : (b.val * m + 4 * r.val) * n + 3 * n + (n - 1) < A.size := by
    rw [ha]
    omega
  have hbn := Nat.mul_le_mul_right n (Nat.succ_le_of_lt b.isLt)
  rw [Nat.succ_mul] at hbn
  have hbg := Nat.mul_le_mul_right (R22Pair8.groups p) hbn
  rw [Nat.add_mul] at hbg
  have hG : 0 < R22Pair8.groups p := by unfold R22Pair8.groups; omega
  have hnstep : n * R22Pair8.groups p =
      (n - 1) * R22Pair8.groups p + R22Pair8.groups p := by
    calc
      n * R22Pair8.groups p = ((n - 1) + 1) * R22Pair8.groups p := by congr 1; omega
      _ = _ := by rw [Nat.add_mul]; simp
  rw [hnstep] at hbg
  refine ⟨hn, hnw, haw, hcw, halast, ?_⟩
  rw [hc]
  omega

def core (batch m n p : Nat) (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p)) (hn : 1 < n) (hp : 2 ≤ p) :
    Vector Binary32 (batch * m * p) :=
  let cache := R22Pair8.packB batch n p B.toArray
  if h : n < USize.size ∧ A.toArray.size < USize.size ∧ cache.size < USize.size then
    let bound := all_bounds batch m n p A.toArray cache A.size_toArray
      (R22Pair8.packB_size batch n p B.toArray) hn hp h.1 h.2.1 h.2.2
    ⟨output batch m n p A.toArray B.toArray cache bound,
      output_size batch m n p A.toArray B.toArray cache bound⟩
  else
    ⟨R22Resident8.output batch m n p A.toArray B.toArray cache,
      R22Resident8.output_size batch m n p A.toArray B.toArray cache⟩

def guarded (batch m n p : Nat) (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p)) : Vector Binary32 (batch * m * p) :=
  if A.toArray.all UnderflowZero.small && B.toArray.all UnderflowZero.small then
    UnderflowZero.zeros batch m p
  else if h : 1 < n ∧ 4 ≤ m ∧ 2 ≤ p then core batch m n p A B h.1 h.2.2
  else Submission.bmm batch m n p A B

end Submission.R22IndexedResident8
