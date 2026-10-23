from pathlib import Path
import datetime, hashlib, json

out=Path(__file__).resolve().parent
parent=out.parent/'f01-d10-bmm-singleton-row-cache/Kernel.lean'
raw=parent.read_bytes()
assert hashlib.sha256(raw).hexdigest()=='f44802093e149959a4b64c519464f9d445de040b6bc2f760512a70596e2640b8'
assert not (out/'Kernel.lean').exists(), 'Frozen candidates cannot be overwritten'
s=raw.decode()
start=s.rindex('\ndef bmm (batch m n p : Nat)')
end=s.index('\nend Submission',start)
old=s[start:end]
renamed=old.replace('def bmm (','def bmmBeforeDoubleCache (').replace('theorem bmm_spec','theorem bmmBeforeDoubleCache_spec').replace('(bmm batch','(bmmBeforeDoubleCache batch').replace('  unfold bmm\n','  unfold bmmBeforeDoubleCache\n')
s=s[:start]+renamed+s[end:]
block='''

namespace Submission.SingletonBPredecode
open FloatLib.Floats Competition

def core (batch m n p : Nat) (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p)) : Vector Binary32 (batch * m * p) :=
  let nativeB := B.toArray.map ExecFloat.Binary.toFloat32
  (Vector.ofFn fun r : Fin (batch * m) => r).flatMap fun r =>
    let b := r.val / m
    let i := r.val % m
    let x := A.toArray.getD ((b * m + i) * n + 0) posZero
    let fa := ExecFloat.Binary.toFloat32 x
    let baseB := (b * n + 0) * p
    Vector.ofFn fun j : Fin p =>
      let y := B.toArray.getD (baseB + j.val) posZero
      let result := fa * nativeB.getD (baseB + j.val) Packed10.zero32
      let product := if hr : result.isNaN = false then ExecFloat.Binary.ofFloat32 result
        else Submission.mul x y
      D7SeedNormalize.normalizeProductSeedRaw product

theorem core_eq (batch m n p : Nat)
    (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p)) :
    core batch m n p A B = SingletonRowCache.core batch m n p A B := by
  unfold core SingletonRowCache.core
  simp only [Packed10.nativeA_getD]

end Submission.SingletonBPredecode

namespace Submission
open FloatLib.Floats Competition

def bmm (batch m n p : Nat) (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p)) : Vector Binary32 (batch * m * p) :=
  if n = 1 ∧ 2 < p ∧ 4 ≤ m then SingletonBPredecode.core batch m n p A B
  else bmmBeforeDoubleCache batch m n p A B

theorem bmm_spec : ∀ (batch m n p : Nat) (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p)),
    (bmm batch m n p A B).get = bmmSpec batch m n p A.get B.get := by
  intro batch m n p A B
  unfold bmm
  split
  · rename_i h
    rw [SingletonBPredecode.core_eq, SingletonRowCache.core_eq,
      singletonCore_eq_reference batch m n p A B h.1]
    exact referenceBmm_spec batch m n p A B
  · exact bmmBeforeDoubleCache_spec batch m n p A B

end Submission
'''
result=(s+block).encode()
assert len(result)<=256000
(out/'Kernel.lean').write_bytes(result)
m={'candidate':out.name,'candidate_file':'Kernel.lean','candidate_sha256':hashlib.sha256(result).hexdigest(),'candidate_bytes':len(result),
   'parent':parent.parent.name,'parent_sha256':hashlib.sha256(raw).hexdigest(),'created_at_utc':datetime.datetime.now(datetime.timezone.utc).isoformat(),
   'mechanism':'For n=1,p>2,m>=4, also decode B once for reuse across rows, retaining A row cache. Conservative fixed reuse guard amortizes map/allocation across at least4rows; no width/threshold grid. Raw B remains for exact NaN fallback. All maps, closure allocation and output stay in complete entry timing. Other shapes retain f448.',
   'proof':'Existing Packed10.nativeA_getD proves mapped B reads exactly equal the old conversion for ALL indices/defaults, then reuses row-cache and singleton proofs.',
   'validation_mode':'full-gate','proof_status':'NOT_RUN_NEW_COMPOSITION','performance':'UNKNOWN','formal_submission':'NOT_SUBMITTED'}
(out/'manifest.json').write_bytes((json.dumps(m,indent=2)+'\n').encode())
print(json.dumps(m))
