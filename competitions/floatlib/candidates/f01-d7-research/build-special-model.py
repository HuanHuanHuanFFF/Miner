"""Hoist the exact official special branch ahead of dyadic operand decoding."""
from pathlib import Path
import json,hashlib

root=Path(__file__).resolve().parents[1]
parent=root/'f01-d5-stream-pack/Kernel.lean';raw=parent.read_bytes()
assert hashlib.sha256(raw).hexdigest()=='8eb63a2fea39f8c483eb16857cb1dcc35ac4a30168ab91046a48aa1cb561e045'
s=raw.decode('utf-8')
block='''
namespace SpecialDispatch

open FloatLib.Floats Competition
open FloatLib.Floats.Formats.BinaryInterchange

abbrev Fmt := TunedAdd.Fmt
abbrev M := Model Fmt

/-- Special cases follow the original MIT FloatLib Spec/Dyadic at 0d918257. -/
@[inline] def modelAdd (x y : M) : M :=
  match Model.chooseNaN2 x y with
  | some nan => nan
  | none =>
      if Model.isInf x then
        if Model.isInf y then
          if Model.signBit x == Model.signBit y then x else Model.invalidResult Fmt
        else x
      else if Model.isInf y then y
      else Model.invalidResult Fmt

@[inline] def modelMul (x y : M) : M :=
  match Model.chooseNaN2 x y with
  | some nan => nan
  | none =>
      if Model.isInf x then
        if Model.isZero y then Model.invalidResult Fmt
        else Model.nativeOverflow Fmt (Model.signBit x != Model.signBit y)
      else if Model.isInf y then
        if Model.isZero x then Model.invalidResult Fmt
        else Model.nativeOverflow Fmt (Model.signBit x != Model.signBit y)
      else Model.invalidResult Fmt

theorem modelAdd_eq (x y : M)
    (h : Model.toDyadic? x = none ∨ Model.toDyadic? y = none) :
    modelAdd x y = Model.Spec.add x y := by
  rcases h with hx | hy
  · unfold Model.Spec.add
    rw [hx]
    cases Model.toDyadic? y <;> rfl
  · unfold Model.Spec.add
    rw [hy]
    cases Model.toDyadic? x <;> rfl

theorem modelMul_eq (x y : M)
    (h : Model.toDyadic? x = none ∨ Model.toDyadic? y = none) :
    modelMul x y = Model.Spec.mul x y := by
  rcases h with hx | hy
  · unfold Model.Spec.mul
    rw [hx]
    cases Model.toDyadic? y <;> rfl
  · unfold Model.Spec.mul
    rw [hy]
    cases Model.toDyadic? x <;> rfl

theorem specialDecode (x : Binary32)
    (hx : Model.NativeBinary32.expField x.raw.1 = 0xff) :
    Model.toDyadic? (TunedAdd.dec x) = none := by
  rw [TunedAdd.dec_eq, ← Model.NativeBinary32.toDyadic_eq]
  simp only [Model.NativeBinary32.toUInt32_ofUInt32]
  unfold Model.NativeBinary32.toDyadic?
  simp [hx]

theorem rejectedFinite (x y : Binary32)
    (h : ¬ (Model.NativeBinary32.expField x.raw.1 ≠ 0xff ∧
      Model.NativeBinary32.expField y.raw.1 ≠ 0xff)) :
    Model.toDyadic? (TunedAdd.dec x) = none ∨
      Model.toDyadic? (TunedAdd.dec y) = none := by
  by_cases hx : Model.NativeBinary32.expField x.raw.1 = 0xff
  · exact Or.inl (specialDecode x hx)
  · by_cases hy : Model.NativeBinary32.expField y.raw.1 = 0xff
    · exact Or.inr (specialDecode y hy)
    · exact False.elim (h ⟨hx, hy⟩)

@[inline] def add (x y : Binary32) : Binary32 :=
  ExecFloat.ModelCodec.liftBinary (F := TunedAdd.Fam) (plan := TunedAdd.Plan) modelAdd x y

@[inline] def mul (x y : Binary32) : Binary32 :=
  ExecFloat.ModelCodec.liftBinary (F := TunedAdd.Fam) (plan := TunedAdd.Plan) modelMul x y

theorem add_spec (x y : Binary32)
    (h : ¬ (Model.NativeBinary32.expField x.raw.1 ≠ 0xff ∧
      Model.NativeBinary32.expField y.raw.1 ≠ 0xff)) :
    add x y = ExecFloat.Spec.add x y := by
  change ExecFloat.ModelCodec.liftBinary (F := TunedAdd.Fam) (plan := TunedAdd.Plan) modelAdd x y =
    ExecFloat.ModelCodec.liftBinary (F := TunedAdd.Fam) (plan := TunedAdd.Plan) Model.Spec.add x y
  unfold ExecFloat.ModelCodec.liftBinary
  exact congrArg (fun value : M =>
    ExecFloat.ModelCodec.encode (F := TunedAdd.Fam) (plan := TunedAdd.Plan) value)
      (modelAdd_eq _ _ (rejectedFinite x y h))

theorem mul_spec (x y : Binary32)
    (h : ¬ (Model.NativeBinary32.expField x.raw.1 ≠ 0xff ∧
      Model.NativeBinary32.expField y.raw.1 ≠ 0xff)) :
    mul x y = ExecFloat.Spec.mul x y := by
  change ExecFloat.ModelCodec.liftBinary (F := TunedAdd.Fam) (plan := TunedAdd.Plan) modelMul x y =
    ExecFloat.ModelCodec.liftBinary (F := TunedAdd.Fam) (plan := TunedAdd.Plan) Model.Spec.mul x y
  unfold ExecFloat.ModelCodec.liftBinary
  exact congrArg (fun value : M =>
    ExecFloat.ModelCodec.encode (F := TunedAdd.Fam) (plan := TunedAdd.Plan) value)
      (modelMul_eq _ _ (rejectedFinite x y h))

end SpecialDispatch

'''
anchor='/-- Raw exponent tests establish both native input conditions. -/'
assert s.count(anchor)==1;s=s.replace(anchor,block+anchor)
assert s.count('else TunedAdd.add x y')==1;s=s.replace('else TunedAdd.add x y','else SpecialDispatch.add x y')
assert s.count('  · exact TunedAdd.add_spec x y')==1;s=s.replace('  · exact TunedAdd.add_spec x y','  · rename_i hf\n    exact SpecialDispatch.add_spec x y hf')
assert s.count('else FastMul.mul x y')==1;s=s.replace('else FastMul.mul x y','else SpecialDispatch.mul x y')
assert s.count('  · exact FastMul.mul_spec x y')==1;s=s.replace('  · exact FastMul.mul_spec x y','  · rename_i hf\n    exact SpecialDispatch.mul_spec x y hf')
out=root/'f01-d7-special-model';out.mkdir(exist_ok=True);data=s.encode('utf-8');(out/'Kernel.lean').write_bytes(data)
m={'candidate':out.name,'candidate_file':'Kernel.lean','candidate_sha256':hashlib.sha256(data).hexdigest(),'candidate_bytes':len(data),'validation_mode':'statement-only','proof_status':'NOT_RUN','parent':'f01-d5-stream-pack','parent_sha256':hashlib.sha256(raw).hexdigest(),'mechanism':'On exactly the existing rejected-finite scalar branches, execute the original Spec special-value branch before constructing either dyadic operand. Preserve exact signaling/quiet NaN priority, raw sign/payload, Inf/zero behavior and all normal scalar paths. This also affects software tensor-replay prefix costs.','source_attribution':'FloatLib Team MIT, lean-dojo/FloatLib 0d918257 Spec/Dyadic.lean and ModelCodec lossless carrier','expected_gain':'UNKNOWN; compile core equivalence first, then inspect actual generated C and measure complete current public-suite calls','formal_submission':'NOT_SUBMITTED'}
(out/'manifest.json').write_text(json.dumps(m,indent=2)+'\n','utf-8')
assert len(data)<256000
print(json.dumps({'candidate':out.name,'sha256':m['candidate_sha256'],'bytes':len(data),'mode':m['validation_mode']}))
