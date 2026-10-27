from pathlib import Path
import datetime,hashlib,json

HERE=Path(__file__).resolve().parent
ROOT=HERE.parents[3]
BASE=ROOT/'competitions/floatlib/candidates/f01-d1-native-both-proof1/Kernel.lean'
OUT=ROOT/'competitions/floatlib/candidates/f01-r2-no-raw-guards'
assert hashlib.sha256(BASE.read_bytes()).hexdigest()=='707d22fed8443d883a183983397496492f9a09e071ffcf2715ef818384e44b85'
s=BASE.read_text(encoding='utf8')
bridge=(ROOT/'competitions/floatlib/research/astra-collab-20261021/native-roundtrip-bridge-draft.lean').read_text(encoding='utf8')
bridge=bridge.removeprefix('import ContractTensor\n\n').replace('Submission.NativeBridge','GuardBridge')
start=s.index('/-- Stage 1\'s `tuned` addition. -/')
end=s.index('namespace NativeBridge',start)
# Keep the existing multiplication proof namespace and replace only the add wrapper/proof.
s=s[:start]+bridge+'\n'+r'''/-- Native finite addition; bit round-trip follows from finiteness. -/
@[inline] def add (x y : Binary32) : Binary32 :=
  let fx := ExecFloat.Binary.toFloat32 x
  let fy := ExecFloat.Binary.toFloat32 y
  if hf : fx.isFinite = true ∧ fy.isFinite = true then
    ExecFloat.Binary.ofFloat32 (fx + fy)
  else TunedAdd.add x y

theorem add_spec : ∀ x y : Binary32, add x y = ExecFloat.Spec.add x y := by
  intro x y
  unfold add
  dsimp only
  split
  · rename_i hf
    rw [ExecFloat.Binary.ofFloat32_add_of_isFinite _ _ hf.1 hf.2,
      GuardBridge.finiteRoundtrip x hf.1, GuardBridge.finiteRoundtrip y hf.2]
    exact ExecFloat.Proof.add_eq_spec x y
  · exact TunedAdd.add_spec x y

'''+s[end:]
start=s.index('@[inline] def mul (x y : Binary32) : Binary32 :=',s.index('end NativeBridge'))
end=s.index('/-- `add` and `mul` are FloatLib\'s executable operations',start)
s=s[:start]+r'''/-- Native finite multiplication with the same exact fallback. -/
@[inline] def mul (x y : Binary32) : Binary32 :=
  let fx := ExecFloat.Binary.toFloat32 x
  let fy := ExecFloat.Binary.toFloat32 y
  if hf : fx.isFinite = true ∧ fy.isFinite = true then
    ExecFloat.Binary.ofFloat32 (fx * fy)
  else FastMul.mul x y

theorem mul_spec : ∀ x y : Binary32, mul x y = ExecFloat.Spec.mul x y := by
  intro x y
  unfold mul
  dsimp only
  split
  · rename_i hf
    rw [NativeBridge.ofFloat32Mul _ _ hf.1 hf.2,
      GuardBridge.finiteRoundtrip x hf.1, GuardBridge.finiteRoundtrip y hf.2]
    exact ExecFloat.Proof.mul_eq_spec x y
  · exact FastMul.mul_spec x y

'''+s[end:]
OUT.mkdir(parents=True,exist_ok=True)
(OUT/'Kernel.lean').write_text(s,encoding='utf8',newline='\n')
d=(OUT/'Kernel.lean').read_bytes()
manifest={'candidate':OUT.name,'candidate_file':'Kernel.lean','candidate_sha256':hashlib.sha256(d).hexdigest(),'candidate_bytes':len(d),
 'parent':'f01-d1-native-both-proof1','parent_sha256':hashlib.sha256(BASE.read_bytes()).hexdigest(),
 'validation_mode':'full-gate','proof_status':'NOT_RUN_DRAFT: finiteRoundtrip canonicalization proof; existing mul bridge unchanged',
 'mechanism':'Remove the two raw round-trip runtime comparisons from each native scalar wrapper. Retain native finite tests, original software fallbacks, all tensor loops and rounding order.',
 'created_at_utc':datetime.datetime.now(datetime.timezone.utc).isoformat(),
 'minimal_request':'D copies exact source to f01-d2 scope; statement/axiom check then full gate with C capture. Expected C change: two fewer lean_float32_to_bits calls per scalar fast path. No performance claim before measurement.',
 'formal_submission':'NOT_SUBMITTED'}
(OUT/'manifest.json').write_text(json.dumps(manifest,indent=2)+'\n',encoding='utf8')
print(json.dumps(manifest,indent=2))
