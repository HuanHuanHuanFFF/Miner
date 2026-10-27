from pathlib import Path
import datetime,hashlib,json

here=Path(__file__).resolve().parent
root=here.parents[3]
base=root/'competitions/floatlib/candidates/f01-d2-final-finite/Kernel.lean'
parent_sha='86312a3759286cb207f946af9db95546777fdb16f1bd147f7892c0f9e1d79217'
assert hashlib.sha256(base.read_bytes()).hexdigest()==parent_sha
source=base.read_text(encoding='utf8')
fragment=(here/'word-finite-bridge-draft.lean').read_text(encoding='utf8').removeprefix('import ContractTensor\n\n').replace('namespace Submission.WordFinite','namespace WordFinite').replace('end Submission.WordFinite','end WordFinite')
start=source.index('/-- Native finite addition; bit round-trip follows from finiteness. -/')
end=source.index('namespace NativeBridge',start)
source=source[:start]+fragment+'\n'+'''/-- Raw exponent tests establish both native input conditions. -/
@[inline] def add (x y : Binary32) : Binary32 :=
  if hf : Model.NativeBinary32.expField x.raw.1 ≠ 0xff ∧
      Model.NativeBinary32.expField y.raw.1 ≠ 0xff then
    ExecFloat.Binary.ofFloat32 (ExecFloat.Binary.toFloat32 x + ExecFloat.Binary.toFloat32 y)
  else TunedAdd.add x y

theorem add_spec : ∀ x y : Binary32, add x y = ExecFloat.Spec.add x y := by
  intro x y
  unfold add
  split
  · rename_i hf
    have hx := WordFinite.nativeFiniteOfExp x hf.1
    have hy := WordFinite.nativeFiniteOfExp y hf.2
    rw [ExecFloat.Binary.ofFloat32_add_of_isFinite _ _ hx hy,
      GuardBridge.finiteRoundtrip x hx, GuardBridge.finiteRoundtrip y hy]
    exact ExecFloat.Proof.add_eq_spec x y
  · exact TunedAdd.add_spec x y

'''+source[end:]
start=source.index('/-- Native finite multiplication with the same exact fallback. -/')
end=source.index('/-- `add` and `mul` are FloatLib',start)
source=source[:start]+'''/-- Raw finite input guards retain the original multiplication fallback. -/
@[inline] def mul (x y : Binary32) : Binary32 :=
  if hf : Model.NativeBinary32.expField x.raw.1 ≠ 0xff ∧
      Model.NativeBinary32.expField y.raw.1 ≠ 0xff then
    ExecFloat.Binary.ofFloat32 (ExecFloat.Binary.toFloat32 x * ExecFloat.Binary.toFloat32 y)
  else FastMul.mul x y

theorem mul_spec : ∀ x y : Binary32, mul x y = ExecFloat.Spec.mul x y := by
  intro x y
  unfold mul
  split
  · rename_i hf
    have hx := WordFinite.nativeFiniteOfExp x hf.1
    have hy := WordFinite.nativeFiniteOfExp y hf.2
    rw [NativeBridge.ofFloat32Mul _ _ hx hy,
      GuardBridge.finiteRoundtrip x hx, GuardBridge.finiteRoundtrip y hy]
    exact ExecFloat.Proof.mul_eq_spec x y
  · exact FastMul.mul_spec x y

'''+source[end:]
out=root/'competitions/floatlib/candidates/f01-r2-word-finite-guards';out.mkdir(exist_ok=True)
assert not (out/'Kernel.lean').exists(), 'Frozen candidate exists; use a new name.'
(out/'Kernel.lean').write_text(source,encoding='utf8',newline='\n');data=(out/'Kernel.lean').read_bytes()
manifest={'candidate':out.name,'candidate_file':'Kernel.lean','candidate_sha256':hashlib.sha256(data).hexdigest(),'candidate_bytes':len(data),'parent':base.parent.name,'parent_sha256':parent_sha,'validation_mode':'statement-only','proof_status':'NOT_RUN: new raw exponent to native finite bridge; existing arithmetic/roundtrip unchanged','mechanism':'Scalar add/mul use raw UInt32 exponent guards before conversion instead of two native isFinite calls. Finite input overflow remains on proven native path. Production sum/bmm final-finite loops unchanged; their slow scalar fallback shares the new exact wrappers.','created_at_utc':datetime.datetime.now(datetime.timezone.utc).isoformat(),'formal_submission':'NOT_SUBMITTED'}
(out/'manifest.json').write_text(json.dumps(manifest,indent=2)+'\n',encoding='utf8');print(json.dumps(manifest,indent=2))
