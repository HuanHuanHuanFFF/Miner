import ContractExact

/- Original UInt64 bitfield bridge. UNCOMPILED; generated-array producer/open loop
   obligations are separate. The small-Nat storage statement concerns64-bit runners. -/
namespace R28PackedWord

def encode (t : Nat) (p : UInt64) : UInt64 := (t.toUInt64<<<56)|||p

theorem shifted_index (t : Nat) (ht:t<128) :
    (t.toUInt64<<<(56:UInt64)).toNat=t*2^56 := by
  have ht64:t<2^64 := by norm_num at *;omega
  have hn:t.toUInt64.toNat=t := by
    rw [Nat.toUInt64_eq]
    exact UInt64.toNat_ofNat_of_lt' ht64
  have hm:t*2^56<2^64 := by norm_num at *;omega
  rw [UInt64.toNat_shiftLeft,hn]
  simp only [show (56:UInt64).toNat%64=56 from rfl,Nat.shiftLeft_eq]
  exact Nat.mod_eq_of_lt hm

theorem encode_toNat (t : Nat) (p : UInt64) (ht:t<128) (hp:p.toNat<2^56) :
    (encode t p).toNat=t*2^56+p.toNat := by
  unfold encode
  rw [UInt64.toNat_or,shifted_index t ht,←Nat.shiftLeft_eq,←Nat.shiftLeft_add_eq_or_of_lt hp]

theorem encode_positive_small (t : Nat) (p : UInt64) (ht:t<128)
    (hp:0<p.toNat) (hmax:p.toNat<2^56) :
    0<(encode t p).toNat ∧ (encode t p).toNat<2^63 := by
  rw [encode_toNat t p ht hmax]
  norm_num at hmax ⊢
  omega

theorem decode_index (t : Nat) (p : UInt64) (ht:t<128) (hp:p.toNat<2^56) :
    (encode t p >>> (56:UInt64)).toNat=t := by
  rw [UInt64.toNat_shiftRight,encode_toNat t p ht hp]
  simp only [show (56:UInt64).toNat%64=56 from rfl,Nat.shiftRight_eq_div_pow]
  norm_num at hp ⊢
  omega

theorem decode_payload (t : Nat) (p : UInt64) (ht:t<128) (hp:p.toNat<2^56) :
    (encode t p &&& 0xffffffffffffff).toNat=p.toNat := by
  rw [UInt64.toNat_and,encode_toNat t p ht hp,
    show (0xffffffffffffff:UInt64).toNat=2^56-1 from rfl,
    Nat.and_two_pow_sub_one_eq_mod]
  norm_num at hp ⊢
  omega

theorem decode_payload_word (t : Nat) (p : UInt64) (ht:t<128) (hp:p.toNat<2^56) :
    encode t p &&& 0xffffffffffffff=p := by
  apply UInt64.toNat_inj.mp
  exact decode_payload t p ht hp

theorem source_payload (x : UInt64)
    (lo:0x180000000000000<x.toNat) (hi:x.toNat<0x280000000000000) :
    0<(x-0x180000000000000).toNat ∧ (x-0x180000000000000).toNat<2^56 := by
  have hle:(0x180000000000000:UInt64)≤x := by
    rw [UInt64.le_iff_toNat_le]
    change 0x180000000000000≤x.toNat
    omega
  rw [UInt64.toNat_sub_of_le _ _ hle]
  change 0<x.toNat-0x180000000000000 ∧ x.toNat-0x180000000000000<2^56
  norm_num at lo hi ⊢
  omega

theorem recover_source_word (t : Nat) (x : UInt64) (ht:t<128)
    (lo:0x180000000000000<x.toNat) (hi:x.toNat<0x280000000000000) :
    (encode t (x-0x180000000000000) &&& 0xffffffffffffff)+0x180000000000000=x := by
  have hp:=source_payload x lo hi
  rw [decode_payload_word t (x-0x180000000000000) ht hp.2]
  exact UInt64.sub_add_cancel _ _

end R28PackedWord
