/-! Precompute each spatial input window once, sharing its indices across output channels.
The patch arrays hold references to the shared decoded input words.
-/

def patchWords (s : ConvShape) (inp : Array Word) : Array (Array DecodedWord) :=
  let dinp := cacheWords inp
  Array.ofFn (n := s.ho * s.wo) fun p =>
    Array.ofFn (n := s.cin * s.kh * s.kw) fun t =>
      windowCached s dinp (p.val / s.wo % s.ho) (p.val % s.wo) t.val

theorem patchWords_get (s : ConvShape) (inp : Array Word) (p : Nat)
    (hp : p < s.ho * s.wo) (t : Nat) (ht : t < s.cin * s.kh * s.kw) :
    (patchWords s inp)[p]![t]! =
      decodeWord (windowAt s inp (p / s.wo % s.ho) (p % s.wo) t) := by
  simp [patchWords, getElem!_pos, hp, ht, windowCached_eq]

theorem patch_row (q h w : Nat) : (q % (h * w)) / w % h = q / w % h := by
  rw [Nat.mul_comm h w, Nat.mod_mul_right_div_self, Nat.mod_mod]

theorem patch_col (q h w : Nat) : (q % (h * w)) % w = q % w := by
  rw [Nat.mul_comm h w, Nat.mod_mul_right_mod]

def conv2dCached (s : ConvShape) (relu : Bool) (inp wts b : Array Word) : Array Word :=
  let patches := patchWords s inp
  let dwts := cacheWords wts
  let k := s.cin * s.kh * s.kw
  Array.ofFn (n := s.cout * (s.ho * s.wo)) fun q =>
    let o := q.val / (s.ho * s.wo)
    let y := q.val / s.wo % s.ho
    let x := q.val % s.wo
    let dp := patches[q.val % (s.ho * s.wo)]!
    act relu <| dotCached (k + 1)
      (fun t => if t < k then windowAt s inp y x t else oneW)
      (fun t => if t < k then wts[o * k + t]! else b[o]!)
      (fun t => if t < k then dp[t]! else decodeWord oneW)
      (fun t => if t < k then dwts[o * k + t]! else decodeWord b[o]!)

theorem conv2dCached_eq : conv2dCached = conv2dWith dotFn := by
  funext s relu inp wts b
  unfold conv2dCached conv2dWith
  apply congrArg (fun f : Fin (s.cout * (s.ho * s.wo)) → Word => Array.ofFn f)
  funext q
  have hsize : 0 < s.ho * s.wo := by
    by_contra hn
    have hz : s.ho * s.wo = 0 := Nat.eq_zero_of_not_pos hn
    have hq := q.isLt
    simp [hz] at hq
  have hp : q.val % (s.ho * s.wo) < s.ho * s.wo := Nat.mod_lt _ hsize
  dsimp only
  apply congrArg (act relu)
  apply dotCached_eq
  · intro t
    by_cases ht : t < s.cin * s.kh * s.kw
    · simp only [ht, ite_true]
      rw [patchWords_get s inp _ hp t ht, patch_row, patch_col]
    · simp only [ht, ite_false]
  · intro t
    split_ifs <;> simp only [cacheWords_get]
