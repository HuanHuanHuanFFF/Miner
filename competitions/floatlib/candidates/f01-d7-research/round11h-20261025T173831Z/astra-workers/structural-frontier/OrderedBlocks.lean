import ContractTensor

namespace R17OrderedBlocks

def serial {α : Type} (n : Nat) (step : Nat → α → α) (k : Nat) (s : α) : α :=
  if k < n then serial n step (k + 1) (step k s) else s
termination_by n - k
decreasing_by all_goals omega

def blocks4 {α : Type} (n : Nat) (step : Nat → α → α) (k : Nat) (s : α) : α :=
  if k + 3 < n then
    blocks4 n step (k + 4) (step (k + 3) (step (k + 2) (step (k + 1) (step k s))))
  else serial n step k s
termination_by n - k
decreasing_by all_goals omega

theorem blocks4_eq_serial {α : Type} (n : Nat) (step : Nat → α → α) (k : Nat) (s : α) :
    blocks4 n step k s = serial n step k s := by
  rw [blocks4]
  split
  · rename_i hk3
    have h0 : k < n := by omega
    have h1 : k + 1 < n := by omega
    have h2 : k + 1 + 1 < n := by omega
    have h3 : k + 1 + 1 + 1 < n := by omega
    have ih := blocks4_eq_serial n step (k + 4)
      (step (k + 3) (step (k + 2) (step (k + 1) (step k s))))
    conv_rhs =>
      rw [serial, if_pos h0, serial, if_pos h1, serial, if_pos h2, serial, if_pos h3]
    simpa only [Nat.add_assoc] using ih
  · rfl
termination_by n - k
decreasing_by all_goals omega

theorem index_partition (n k : Nat) (hk : k < n) :
    k % 4 < 4 ∧ k = 4 * (k / 4) + k % 4 ∧ k / 4 < (n + 3) / 4 := by
  omega

theorem last_block_size (n : Nat) : n - 4 * (n / 4) = n % 4 := by
  omega

theorem block_index_valid (n t j : Nat) (hj : j < 4) (hk : 4 * t + j < n) :
    t < (n + 3) / 4 := by
  omega

end R17OrderedBlocks
