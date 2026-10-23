from pathlib import Path
import datetime
import hashlib
import json

out = Path(__file__).resolve().parent
parent = out.parent / 'f01-r8-combined-result-guard/Kernel.lean'
original = parent.read_bytes()
assert hashlib.sha256(original).hexdigest() == '41bce4856c4c921dd67b6115928df16e5e8ed08a55b71f1296d28b77cf9ce9a7'
s = original.decode()
block = '''
@[inline] def smallStep (baseA baseB p : Nat) (A B : Array Binary32)
    (k : Nat) (acc : Float32) : Float32 :=
  acc + ExecFloat.Binary.toFloat32 (A.getD (baseA + k) posZero) *
    ExecFloat.Binary.toFloat32 (B.getD (baseB + k * p) posZero)

def smallLoop (n baseA baseB p : Nat) (A B : Array Binary32) : Float32 :=
  let z := Float32.ofBits 0
  match n with
  | 0 => z
  | 1 => smallStep baseA baseB p A B 0 z
  | 2 => smallStep baseA baseB p A B 1 (smallStep baseA baseB p A B 0 z)
  | 3 => smallStep baseA baseB p A B 2
      (smallStep baseA baseB p A B 1 (smallStep baseA baseB p A B 0 z))
  | 4 => smallStep baseA baseB p A B 3 (smallStep baseA baseB p A B 2
      (smallStep baseA baseB p A B 1 (smallStep baseA baseB p A B 0 z)))
  | _ => dotLoop n baseA baseB p A B 0 z

theorem smallLoop_eq (n baseA baseB p : Nat) (A B : Array Binary32) :
    smallLoop n baseA baseB p A B = dotLoop n baseA baseB p A B 0 (Float32.ofBits 0) := by
  rcases n with _ | n
  · simp [smallLoop, dotLoop]
  rcases n with _ | n
  · simp [smallLoop, smallStep, dotLoop]
  rcases n with _ | n
  · simp [smallLoop, smallStep, dotLoop]
  rcases n with _ | n
  · simp [smallLoop, smallStep, dotLoop]
  rcases n with _ | n
  · simp [smallLoop, smallStep, dotLoop]
  · rfl

def dotSmall (n baseA baseB p : Nat) (A B : Array Binary32) : Binary32 :=
  let result := smallLoop n baseA baseB p A B
  if hf : result.isNaN = false then ExecFloat.Binary.ofFloat32 result
  else R7NaNReplay.replayEarly n baseA baseB p A B

theorem dotSmall_eq (n baseA baseB p : Nat) (A B : Array Binary32) :
    dotSmall n baseA baseB p A B = dot n baseA baseB p A B := by
  unfold dotSmall dot
  rw [smallLoop_eq]

'''
assert s.count('\nend NativeFinal\n') == 1
s = s.replace('\nend NativeFinal\n', '\n' + block + 'end NativeFinal\n')
start = s.index('namespace Submission.DirectSmall')
end = s.index('end Submission.DirectSmall', start)
old = s[start:end]
new = old.replace('    NativeFinal.dot n ', '    NativeFinal.dotSmall n ')
new = new.replace('  rw [NativeFinal.dot_eq]', '  rw [NativeFinal.dotSmall_eq, NativeFinal.dot_eq]')
assert new != old and new.count('NativeFinal.dotSmall') == 2
s = s[:start] + new + s[end:]
data = s.encode()
(out / 'Kernel.lean').write_bytes(data)
manifest = {'candidate': out.name, 'candidate_file': 'Kernel.lean',
    'candidate_sha256': hashlib.sha256(data).hexdigest(), 'candidate_bytes': len(data),
    'created_at_utc': datetime.datetime.now(datetime.timezone.utc).isoformat(),
    'parent': parent.parent.name, 'parent_sha256': hashlib.sha256(original).hexdigest(),
    'mechanism': 'Only DirectSmall uses an explicit n=0..4 straight-line ordered native MAC chain. n>=5 calls original dotLoop; packed code unchanged. Initial +0, all multiplications/additions, native conversion and original exact NaN replay retained.',
    'proof': 'New smallLoop_eq by exhaustive n=0..4 equations; dotSmall_eq transports to accepted original dot. No new arithmetic or NaN equivalence assumptions.',
    'validation_mode': 'full-gate', 'proof_status': 'NOT_RUN', 'performance': 'UNKNOWN',
    'formal_submission': 'NOT_SUBMITTED'}
(out / 'manifest.json').write_text(json.dumps(manifest, indent=2) + '\n', encoding='utf-8')
assert len(data) <= 256000
print(json.dumps(manifest))
