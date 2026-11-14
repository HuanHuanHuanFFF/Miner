import ContractExact

/- Original arithmetic proof interfaces. UNCOMPILED; not an all12 kernel proof. -/
namespace R28PackedSupport

def payload (x : Int) : Nat := (x + 2^55).toNat
def pack (t : Nat) (x : Int) : Nat := t * 2^56 + payload x

theorem payload_bounds (x : Int) (lo : -(2:Int)^55 < x) (hi : x < (2:Int)^55) :
    0 < payload x ∧ payload x < 2^56 := by
  unfold payload
  norm_num at lo hi ⊢
  omega

theorem pack_bounds (t : Nat) (x : Int) (ht : t<128)
    (lo : -(2:Int)^55 < x) (hi : x < (2:Int)^55) :
    0 < pack t x ∧ pack t x < 2^63 := by
  have h := payload_bounds x lo hi
  unfold pack
  norm_num at h ⊢
  omega

theorem decode_index (t : Nat) (x : Int)
    (lo : -(2:Int)^55 < x) (hi : x < (2:Int)^55) :
    pack t x / 2^56 = t := by
  have h := payload_bounds x lo hi
  unfold pack
  norm_num at h ⊢
  omega

theorem decode_payload (t : Nat) (x : Int)
    (lo : -(2:Int)^55 < x) (hi : x < (2:Int)^55) :
    pack t x % 2^56 = payload x := by
  have h := payload_bounds x lo hi
  unfold pack
  norm_num at h ⊢
  omega

theorem decode_signed (t : Nat) (x : Int)
    (lo : -(2:Int)^55 < x) (hi : x < (2:Int)^55) :
    ((pack t x % 2^56 : Nat) : Int) - 2^55 = x := by
  rw [decode_payload t x lo hi]
  unfold payload
  norm_num at lo hi ⊢
  omega

theorem recover_old_encoding (t : Nat) (x : Int)
    (lo : -(2:Int)^55 < x) (hi : x < (2:Int)^55) :
    ((pack t x % 2^56 : Nat) : Int) + 3*2^55 = x+2^57 := by
  have h := decode_signed t x lo hi
  norm_num at h ⊢
  omega

def fold (f : Nat → Int) : List Nat → Int
  | [] => 0
  | t::ts => f t + fold f ts

theorem omit_zero_terms (f : Nat → Int) (live : Nat → Bool)
    (h : ∀ t, live t = false → f t=0) (ts : List Nat) :
    fold f (ts.filter live) = fold f ts := by
  induction ts with
  | nil => rfl
  | cons t ts ih =>
    cases q : live t
    · simp [fold, q, ih, h t q]
    · simp [fold, q, ih]

end R28PackedSupport
