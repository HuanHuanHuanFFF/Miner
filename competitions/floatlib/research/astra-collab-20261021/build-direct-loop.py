from pathlib import Path
import hashlib, json, datetime

ROOT = Path(__file__).resolve().parents[4]
BASE = ROOT / 'competitions/floatlib/candidates/f01-index-hoist-proof2/Kernel.lean'
OUT = ROOT / 'competitions/floatlib/candidates/f01-r1-direct-dot-loop'
assert hashlib.sha256(BASE.read_bytes()).hexdigest() == '7d3539b8ccdd847ab8ac27390abedfe4f6e804ccd0c2d3c80990258d059b46fc'
s = BASE.read_text(encoding='utf-8')
start = s.index('/-- Preserve every reduction order while moving address products outside the inner loop. -/')
s = s[:start] + r'''/-- Direct accumulator recursion, with no higher-order callback in the reduction loop. -/
def dotLoop (n baseA baseB p : Nat) (A B : Array Binary32)
    (k : Nat) (acc : Binary32) : Binary32 :=
  if h : k < n then
    dotLoop n baseA baseB p A B (k + 1)
      (add acc (mul (A.getD (baseA + k) posZero) (B.getD (baseB + k * p) posZero)))
  else acc
termination_by n - k

theorem dotLoop_eq (n baseA baseB p : Nat) (A B : Array Binary32)
    (k : Nat) (acc : Binary32) :
    dotLoop n baseA baseB p A B k acc =
      Fin.foldl.loop n
        (fun a i => add a (mul (A.getD (baseA + i.val) posZero)
          (B.getD (baseB + i.val * p) posZero))) acc k := by
  rw [dotLoop, Fin.foldl.loop]
  split
  · exact dotLoop_eq n baseA baseB p A B (k + 1) _
  · rfl
termination_by n - k

/-- The same ordered dot products, using a direct recursive body. -/
def bmm (batch m n p : Nat) (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p)) : Vector Binary32 (batch * m * p) :=
  Vector.ofFn fun q =>
    let (b, i, j) := bmmDecodeC m p q.val
    let baseA := (b * m + i) * n
    let baseB := b * n * p + j
    dotLoop n baseA baseB p A.toArray B.toArray 0 posZero

theorem bmm_spec : ∀ (batch m n p : Nat) (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p)),
    (bmm batch m n p A B).get = bmmSpec batch m n p A.get B.get := by
  intro batch m n p A B
  have h : bmm batch m n p A B = referenceBmm batch m n p A B := by
    unfold bmm referenceBmm
    apply congrArg (fun (f : Fin (batch * m * p) → Binary32) => Vector.ofFn f)
    funext q
    dsimp only
    rw [dotLoop_eq]
    change Fin.foldl n _ posZero = Fin.foldl n _ posZero
    apply congrArg (fun (f : Binary32 → Fin n → Binary32) => Fin.foldl n f posZero)
    funext acc k
    have hi := index_address ((bmmDecodeC m p q.val).1 * n) k.val p
      (bmmDecodeC m p q.val).2.2
    rw [hi]
  exact (congrArg (fun v : Vector Binary32 (batch * m * p) => v.get) h).trans
    (referenceBmm_spec batch m n p A B)

end Submission
'''
OUT.mkdir(parents=True, exist_ok=True)
(OUT / 'Kernel.lean').write_text(s, encoding='utf-8', newline='\n')
data = (OUT / 'Kernel.lean').read_bytes()
manifest = {
  'candidate': OUT.name,
  'candidate_sha256': hashlib.sha256(data).hexdigest(),
  'kernel_sha256': hashlib.sha256(data).hexdigest(),
  'kernel_bytes': len(data),
  'parent': 'f01-index-hoist-proof2',
  'parent_sha256': hashlib.sha256(BASE.read_bytes()).hexdigest(),
  'baseline_sha256': '5d0cef3ff21093ca05cde92e516edfe45afca8e11996ad4858e7fb2407d65868',
  'mechanism': 'Direct tail-recursive dot product with scalar Binary32 accumulator and original add/mul; compiler should erase Binary32 to UInt32. Removes generic Fin.foldl callback from runtime reduction. Base address hoisting is inherited.',
  'validation_mode': 'full-gate',
  'proof_status': 'DRAFT_NOT_COMPILED: pointwise recursive equivalence to Fin.foldl.loop; four exact obligations included',
  'performance': 'NOT_RUN',
  'created_at_utc': datetime.datetime.now(datetime.timezone.utc).isoformat(),
  'minimal_request': 'D copies frozen Kernel into own f01-d1 directory; statement/full gate; inspect dotLoop C for direct recursion, scalar accumulator, no lean_apply/Fin.foldl callback. Collect original official 12-class 25-pair score.',
  'authority': 'Research artifact only; D owns Git/push/CI. No formal upload.'
}
(OUT / 'manifest.json').write_text(json.dumps(manifest, indent=2) + '\n', encoding='utf-8')
print(json.dumps(manifest, indent=2))
