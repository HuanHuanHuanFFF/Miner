from pathlib import Path
import hashlib, json, datetime

ROOT = Path(__file__).resolve().parents[4]
BASE = ROOT / 'competitions/floatlib/references/official-incumbent/Kernel.lean'
OUT = ROOT / 'competitions/floatlib/candidates/f01-r1-guarded-native-add'
assert hashlib.sha256(BASE.read_bytes()).hexdigest() == '5d0cef3ff21093ca05cde92e516edfe45afca8e11996ad4858e7fb2407d65868'
s = BASE.read_text(encoding='utf-8')
old = '''def add (x y : Binary32) : Binary32 := TunedAdd.add x y

theorem add_spec : ∀ x y : Binary32, add x y = ExecFloat.Spec.add x y := TunedAdd.add_spec'''
new = r'''@[inline] def add (x y : Binary32) : Binary32 :=
  let fx := ExecFloat.Binary.toFloat32 x
  let fy := ExecFloat.Binary.toFloat32 y
  if hf : fx.isFinite = true ∧ fy.isFinite = true then
    if hw : (ExecFloat.Binary.ofFloat32 fx).raw.1 = x.raw.1 ∧
        (ExecFloat.Binary.ofFloat32 fy).raw.1 = y.raw.1 then
      ExecFloat.Binary.ofFloat32 (fx + fy)
    else TunedAdd.add x y
  else TunedAdd.add x y

theorem add_spec : ∀ x y : Binary32, add x y = ExecFloat.Spec.add x y := by
  intro x y
  unfold add
  split
  · rename_i hf
    split
    · rename_i hw
      have hx : ExecFloat.Binary.ofFloat32 (ExecFloat.Binary.toFloat32 x) = x := by
        apply ExecFloat.ext
        apply Subtype.ext
        exact hw.1
      have hy : ExecFloat.Binary.ofFloat32 (ExecFloat.Binary.toFloat32 y) = y := by
        apply ExecFloat.ext
        apply Subtype.ext
        exact hw.2
      rw [ExecFloat.Binary.ofFloat32_add_of_isFinite _ _ hf.1 hf.2, hx, hy]
      exact ExecFloat.Proof.add_eq_spec x y
    · exact TunedAdd.add_spec x y
  · exact TunedAdd.add_spec x y'''
assert s.count(old) == 1
s = s.replace(old,new)
OUT.mkdir(parents=True, exist_ok=True)
(OUT / 'Kernel.lean').write_text(s, encoding='utf-8', newline='\n')
data = (OUT / 'Kernel.lean').read_bytes()
manifest = {
  'candidate':OUT.name, 'candidate_sha256':hashlib.sha256(data).hexdigest(),
  'kernel_sha256':hashlib.sha256(data).hexdigest(), 'kernel_bytes':len(data),
  'baseline_sha256':hashlib.sha256(BASE.read_bytes()).hexdigest(),
  'mechanism':'Public Lean 4.34 Float32.add logical-model definition plus pinned FloatLib ofFloat32_add_of_isFinite theorem. Finite and exact bit round-trip guards; all other cases use original TunedAdd. No new external declarations or native assumptions.',
  'proof_status':'DRAFT_NOT_COMPILED; theorem source checked, transitive axiom audit NOT_RUN',
  'performance':'NOT_RUN', 'validation_mode':'full-gate',
  'created_at_utc':datetime.datetime.now(datetime.timezone.utc).isoformat(),
  'minimal_request':'Priority feasibility gate: confirm four statements, replay and allowed axioms before performance adoption. Inspect C for lean_float32_add and exact fallback. Do not assume source theorem has permissible axioms without gate.'
}
(OUT/'manifest.json').write_text(json.dumps(manifest,indent=2)+'\n',encoding='utf8')
print(json.dumps(manifest,indent=2))
