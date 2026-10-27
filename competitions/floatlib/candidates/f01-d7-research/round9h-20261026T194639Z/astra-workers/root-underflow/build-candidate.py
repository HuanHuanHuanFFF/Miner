"""Research draft only: exactly retained B2 plus proof-backed zero shortcut."""
from pathlib import Path
from hashlib import sha256
import json

HERE = Path(__file__).resolve().parent
ROOT = HERE.parents[6]
BASE = ROOT / 'competitions/floatlib/candidates/f01-r15-dev-packed-b2-1/Kernel.lean'
raw = BASE.read_bytes()
assert sha256(raw).hexdigest() == '622d8394a7127e93dcaf992c62c6dfcff7208d212738409a5e34525dfafd1a58'
source = raw.decode('utf-8')
# Insert after the already-proved generic underflow lemma; public wrappers below
# bind their fallback to the renamed original package, avoiding a cyclic alias.
renamed = source.replace('Submission', 'R19ZeroBase')
fragment = (HERE / 'low-zero84.lean.inc').read_text(encoding='utf-8')
wrapper = '''
namespace Submission
open FloatLib.Floats Competition
open FloatLib.Floats.Formats.BinaryInterchange.Model.NativeBinary32
open R19ZeroBase

def add := R19ZeroBase.add
theorem add_spec := R19ZeroBase.add_spec

@[inline] def mul (x y : Binary32) : Binary32 :=
  let ex := expField x.raw.1
  let ey := expField y.raw.1
  if ex + ey ≤ (84 : UInt32) then R19LowZero.signed x y
  else R19ZeroBase.mul x y

theorem mul_spec (x y : Binary32) : mul x y = ExecFloat.Spec.mul x y := by
  unfold mul
  dsimp only
  split
  · rename_i h
    exact (R19LowZero.eq_exec x y h).trans (ExecFloat.Proof.mul_eq_spec x y)
  · exact R19ZeroBase.mul_spec x y

def sum := @R19ZeroBase.sum
theorem sum_spec := @R19ZeroBase.sum_spec
def bmm := R19ZeroBase.bmm
theorem bmm_spec := R19ZeroBase.bmm_spec
end Submission
'''
out = (renamed + '\nnamespace R19ZeroBase\n' + fragment + '\nend R19ZeroBase\n' + wrapper).encode('utf-8')
assert len(out) < 256000
dest = HERE / 'Kernel.lean'
dest.write_bytes(out)
manifest = dict(status='NOT_RUN', source_sha256=sha256(raw).hexdigest(),
                candidate_sha256=sha256(out).hexdigest(), candidate_bytes=len(out),
                fragment_sha256=sha256(fragment.encode()).hexdigest(),
                mechanism='Existing underflow certificate <=84 generalized to exponent sum, public MUL only, exact old fallback',
                math_scope='Both signs, all fractions/subnormals/zeros; guard excludes nonfinite by proven exponent bounds',
                history='Old low-zero=e139 only actual zero operands; old R14 normal-edge<=102 was counts only; no novelty claim for underflow identity',
                full_gate='NOT_RUN', timing='NOT_RUN', expected_gain='UNKNOWN',
                proof_roots=['R19ZeroBase.R19LowZero.bounds','R19ZeroBase.R19LowZero.scale_bound','R19ZeroBase.R19LowZero.eq_exec',
                             'Submission.add_spec','Submission.mul_spec','Submission.sum_spec','Submission.bmm_spec'])
(HERE / 'manifest.json').write_text(json.dumps(manifest, indent=2) + '\n', encoding='utf-8')
print(json.dumps(manifest, indent=2))
