from pathlib import Path
import hashlib, json, datetime

ROOT = Path(__file__).resolve().parents[4]
BASE = ROOT / 'competitions/floatlib/references/official-incumbent/Kernel.lean'
OUT = ROOT / 'competitions/floatlib/candidates/f01-r1-direct-sum-loop'
assert hashlib.sha256(BASE.read_bytes()).hexdigest() == '5d0cef3ff21093ca05cde92e516edfe45afca8e11996ad4858e7fb2407d65868'
s = BASE.read_text(encoding='utf-8')
start = s.index('/-- TorchLean\'s sum:')
end = s.index('/-- TorchLean\'s batched matmul:', start)
s = s[:start] + r'''/-- Sum with an explicit accumulator and a direct, bounded vector read. -/
def sumLoop {n : Nat} (x : Vector Binary32 n) (k : Nat) (acc : Binary32) : Binary32 :=
  if h : k < n then
    sumLoop x (k + 1) (add acc (x.get ⟨k, h⟩))
  else acc
termination_by n - k

theorem sumLoop_eq {n : Nat} (x : Vector Binary32 n) (k : Nat) (acc : Binary32) :
    sumLoop x k acc =
      Fin.foldl.loop n (fun a i => add a (x.get i)) acc k := by
  rw [sumLoop, Fin.foldl.loop]
  split
  · exact sumLoop_eq x (k + 1) _
  · rfl
termination_by n - k

def sum {n : Nat} (x : Vector Binary32 n) : Binary32 := sumLoop x 0 posZero

theorem sum_spec : ∀ (n : Nat) (x : Vector Binary32 n), sum x = sumSpec x.get := by
  intro n x
  unfold sum
  rw [sumLoop_eq]
  change Fin.foldl n (fun a i => add a (x.get i)) posZero = sumSpec x.get
  rw [Fin.foldl_eq_finRange_foldl, add_eq]
  rfl

''' + s[end:]
OUT.mkdir(parents=True, exist_ok=True)
(OUT / 'Kernel.lean').write_text(s, encoding='utf-8', newline='\n')
data = (OUT / 'Kernel.lean').read_bytes()
manifest = {
  'candidate':OUT.name, 'candidate_sha256':hashlib.sha256(data).hexdigest(),
  'kernel_sha256':hashlib.sha256(data).hexdigest(), 'kernel_bytes':len(data),
  'baseline_sha256':hashlib.sha256(BASE.read_bytes()).hexdigest(),
  'mechanism':'Only sum: explicit scalar accumulator tail recursion and bounded Vector.get; replaces generic Array fold callback/Monad dictionary. Every input visited in ascending index from positive zero.',
  'proof_status':'DRAFT_NOT_COMPILED: pointwise recursion equality to Fin.foldl.loop and exact specification rewriting',
  'performance':'NOT_RUN', 'validation_mode':'full-gate',
  'created_at_utc':datetime.datetime.now(datetime.timezone.utc).isoformat(),
  'minimal_request':'Copy to D-owned candidate only if validation bandwidth permits; full gate and direct-loop C check. This isolates sum and leaves bmm baseline unchanged.'
}
(OUT/'manifest.json').write_text(json.dumps(manifest,indent=2)+'\n',encoding='utf8')
print(json.dumps(manifest,indent=2))
