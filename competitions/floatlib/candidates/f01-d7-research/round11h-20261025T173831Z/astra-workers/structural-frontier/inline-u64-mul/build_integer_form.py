"""Build one small selected form from identified proof bodies; never compile or create a full package."""
from pathlib import Path
from datetime import datetime,timezone
import hashlib,json
H=Path(__file__).resolve().parent
R=next(p for p in H.parents if (p/'competitions/floatlib/pins.json').is_file())
A=H/'Bridge-u64-product-v1.lean.inc';a=A.read_text()
prefix=a[:a.index('theorem native_product_decode')]
threshold=a[a.index('theorem rounded_threshold'):a.index('theorem shift_recovery')]
old=R/'competitions/floatlib/candidates/f01-d7-research/round8h-20261024T190259Z/development-int64-rounding-bridge.lean'
ob=old.read_bytes();assert hashlib.sha256(ob).hexdigest()=='99c2e2f6bd1ea54a695d204beea8b006abbf1a481584d4b10838ab36173e40a9'
ot=ob.decode();forward=ot[ot.index('theorem uint64_model_eq_roundDyadic'):ot.index('theorem int64_model_eq_roundDyadic')]
new='''theorem native_uint64_decode (n : UInt64)
    (hlo : 70368744177664 ≤ n.toNat) (hhi : n.toNat ≤ 281474943156225) :
    Model.toDyadic? (Model.ofFloat32Model n.toFloat32.toModel) =
      some ⟨false,R14NatNormal.mantissa n.toNat,(roundedShift n.toNat : Int)⟩ := by
  have hl := R14NatNormal.leading_bounds n.toNat hlo (by omega)
  have hc := R14NatNormal.carry_le n.toNat
  have he := R14ExponentShift.middle_bounds n.toNat hlo hhi
  have hshift : (n.toNat.log2 : Int)+0+(R14NatNormal.carry n.toNat : Int)-23 =
      (roundedShift n.toNat : Int) := by
    unfold roundedShift R14ExponentShift.middleExponent
    omega
  rw [uint64_model_eq_roundDyadic]
  have hd := R14NatNormal.round_normal_decode false n.toNat 0 hlo (by omega)
    (by omega) (by omega)
  simpa only [hshift] using hd

theorem uint64_roundtrip (n : UInt64)
    (hlo : 70368744177664 ≤ n.toNat) (hhi : n.toNat ≤ 281474943156225) :
    n.toFloat32.toUInt64.toNat = roundedInteger n.toNat := by
  exact toUInt64_of_nonnegative_integral_decode _ _ _
    (native_uint64_decode n hlo hhi) (rounded_integer_fit _ hlo hhi)

theorem product_word_nat (a b : UInt32)
    (ha0 : 8388608 ≤ a.toNat) (ha : a.toNat < 16777216)
    (hb0 : 8388608 ≤ b.toNat) (hb : b.toNat < 16777216) :
    (a.toUInt64*b.toUInt64).toNat = R14ExponentShift.product a b := by
  have hp := R14ExponentShift.product_bounds a b ha0 ha hb0 hb
  unfold R14ExponentShift.product
  rw [UInt64.toNat_mul,UInt32.toNat_toUInt64,UInt32.toNat_toUInt64]
  exact Nat.mod_eq_of_lt (by change R14ExponentShift.product a b < _; omega)

theorem numeric_integer_product (a b : UInt32)
    (ha0 : 8388608 ≤ a.toNat) (ha : a.toNat < 16777216)
    (hb0 : 8388608 ≤ b.toNat) (hb : b.toNat < 16777216) :
    (a.toUInt64*b.toUInt64).toFloat32.toUInt64.toNat =
      roundedInteger (R14ExponentShift.product a b) := by
  have hp := R14ExponentShift.product_bounds a b ha0 ha hb0 hb
  have hw := product_word_nat a b ha0 ha hb0 hb
  have hd := uint64_roundtrip (a.toUInt64*b.toUInt64)
    (by rw [hw]; exact hp.1) (by rw [hw]; exact hp.2)
  simpa only [hw] using hd

'''
shift='''theorem shift_recovery (a b : UInt32) (s64 : UInt64)
    (ha0 : 8388608 ≤ a.toNat) (ha : a.toNat < 16777216)
    (hb0 : 8388608 ≤ b.toNat) (hb : b.toNat < 16777216)
    (hs : s64.toNat = roundedShift (R14ExponentShift.product a b)) :
    ((a.toUInt64*b.toUInt64).toFloat32.toUInt64 >>> s64).toNat =
      R14NatNormal.mantissa (R14ExponentShift.product a b) := by
  have hp := R14ExponentShift.product_bounds a b ha0 ha hb0 hb
  have hc := rounded_shift_cases _ hp.1 hp.2
  have hsbound : s64.toNat < 64 := by rw [hs]; omega
  rw [UInt64.toNat_shiftRight,Nat.mod_eq_of_lt hsbound,hs,
    numeric_integer_product a b ha0 ha hb0 hb]
  unfold roundedInteger
  simp [Nat.shiftRight_eq_div_pow,Nat.two_pow_pos]

end Submission.R17UInt64Integer
'''
data=(prefix+forward+new+threshold+shift).replace('namespace Submission.R17UInt64Product','namespace Submission.R17UInt64Integer')
bp=H/'Bridge-u64-integer-v2.lean.inc';bp.write_text(data)
runtime=(H/'Runtime-u64-mul-v1.lean.inc').read_text()
runtime=runtime.replace('Submission.R17NumericMul','Submission.R17NumericMulInteger')
runtime=runtime.replace('  let r : UInt64 := (a.toFloat32 * b.toFloat32).toUInt64',
    '  let product : UInt64 := a.toUInt64 * b.toUInt64\n  let r : UInt64 := product.toFloat32.toUInt64')
rp=H/'Runtime-u64-mul-integer-v2.lean.inc';rp.write_text(runtime)
manifest=dict(updated_utc=datetime.now(timezone.utc).isoformat(),state='SELECTED_INTEGER_FORM_NOT_COMPILED',
    chosen='integer product -> numeric Float32 -> numeric UInt64',
    files={p.name:dict(bytes=p.stat().st_size,sha256=hashlib.sha256(p.read_bytes()).hexdigest()) for p in (A,old,bp,rp)},
    provenance='Common bounds/reverse-cast/threshold proof text from v1; exact old R14 U64 forward theorem body; new product-specific bridges; runtime guard/repack unchanged except product path and namespace',
    required_next='Pinned helper elaboration and actual selected-code conversion lowering; no claims about performance',
    tokens='UNKNOWN',local_Lean=False,CI=False,full_package=False)
(H/'integer-form-manifest.json').write_text(json.dumps(manifest,indent=2)+'\n')
print(json.dumps(manifest))
