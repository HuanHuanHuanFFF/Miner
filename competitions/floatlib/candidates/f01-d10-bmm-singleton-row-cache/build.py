from pathlib import Path
import datetime, hashlib, json

out=Path(__file__).resolve().parent
parent=out.parent/'f01-r10-bmm-singleton-native/Kernel.lean'
raw=parent.read_bytes()
assert hashlib.sha256(raw).hexdigest()=='ff34b1b7e2166b7b22f53d5f3e656b6567fd7487d457343e3599885757ab25ad'
assert not (out/'Kernel.lean').exists(), 'Do not overwrite frozen candidate'
s=raw.decode()
start=s.rindex('\ndef bmm (batch m n p : Nat)')
end=s.index('\nend Submission',start)
old=s[start:end]
new=old.replace('def bmm (','def bmmBeforeRowCache (').replace('theorem bmm_spec','theorem bmmBeforeRowCache_spec').replace('(bmm batch','(bmmBeforeRowCache batch').replace('  unfold bmm\n','  unfold bmmBeforeRowCache\n')
s=s[:start]+new+s[end:]
rows=(out.parent/'f01-d10-bmm-direct-rows/Kernel.lean').read_text()
rs=rows.index('namespace Submission.DirectRows')
re=rows.index('end Submission.DirectRows',rs)+len('end Submission.DirectRows')
rows_block=rows[rs:re]
cache='''

namespace Submission.SingletonRowCache
open FloatLib.Floats Competition

def core (batch m n p : Nat) (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p)) : Vector Binary32 (batch * m * p) :=
  (Vector.ofFn fun r : Fin (batch * m) => r).flatMap fun r =>
    let b := r.val / m
    let i := r.val % m
    let x := A.toArray.getD ((b * m + i) * n + 0) posZero
    let fa := ExecFloat.Binary.toFloat32 x
    let baseB := (b * n + 0) * p
    Vector.ofFn fun j : Fin p =>
      let y := B.toArray.getD (baseB + j.val) posZero
      let result := fa * ExecFloat.Binary.toFloat32 y
      let product := if hr : result.isNaN = false then ExecFloat.Binary.ofFloat32 result
        else Submission.mul x y
      D7SeedNormalize.normalizeProductSeedRaw product

theorem core_eq (batch m n p : Nat)
    (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p)) :
    core batch m n p A B = singletonCore batch m n p A B := by
  apply Vector.ext
  intro q hq
  have hmp : m * p ≠ 0 := by
    intro h
    have hq' : q < batch * (m * p) := by simpa only [Nat.mul_assoc] using hq
    rw [h, Nat.mul_zero] at hq'
    omega
  have hp : p ≠ 0 := by
    intro h
    apply hmp
    simp only [h, Nat.mul_zero]
  simp only [core, singletonCore, Vector.getElem_flatMap,
    Vector.getElem_ofFn, bmmDecodeC, hmp, hp, if_false,
    Nat.div_div_eq_div_mul, Nat.mul_comm p m,
    Nat.mod_mul_left_div_self, Nat.mod_mul_left_mod,
    D7SingletonNative.nativeProduct]

end Submission.SingletonRowCache

namespace Submission
open FloatLib.Floats Competition

def bmm (batch m n p : Nat) (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p)) : Vector Binary32 (batch * m * p) :=
  if n = 1 ∧ 2 < p then SingletonRowCache.core batch m n p A B
  else if n ≤ 4 ∧ 2 < p then DirectRows.core batch m n p A B
  else bmmBeforeRowCache batch m n p A B

theorem bmm_spec : ∀ (batch m n p : Nat) (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p)),
    (bmm batch m n p A B).get = bmmSpec batch m n p A.get B.get := by
  intro batch m n p A B
  unfold bmm
  split
  · rename_i h
    rw [SingletonRowCache.core_eq, singletonCore_eq_reference batch m n p A B h.1]
    exact referenceBmm_spec batch m n p A B
  · split
    · rw [DirectRows.core_eq, DirectSmall.core_eq_reference]
      exact referenceBmm_spec batch m n p A B
    · exact bmmBeforeRowCache_spec batch m n p A B

end Submission
'''
result=(s+'\n\n'+rows_block+cache).encode()
assert len(result)<=256000
(out/'Kernel.lean').write_bytes(result)
m={'candidate':out.name,'candidate_file':'Kernel.lean','candidate_sha256':hashlib.sha256(result).hexdigest(),'candidate_bytes':len(result),
   'parent':parent.parent.name,'parent_sha256':hashlib.sha256(raw).hexdigest(),'created_at_utc':datetime.datetime.now(datetime.timezone.utc).isoformat(),
   'components':['ff34 exact all-input native singleton + seed normalization','a066 exact DirectRows block, unchanged','n=1,p>2 row traversal caching A raw/native conversion outside the column loop'],
   'mechanism':'n=1,p>2 shares row address and native A conversion across columns, computing the exact same nativeProduct/NaN fallback and raw seed normalization. Other n<=4,p>2 use full original DirectRows dot; remaining shapes use ff34 dispatcher. All map/allocation/output costs retained.',
   'proof':'Row-wise Vector.ext address equality plus definitional nativeProduct unfolding; no new floating-point arithmetic theorem or assumption.',
   'validation_mode':'full-gate','proof_status':'NOT_RUN_NEW_COMPOSITION','performance':'UNKNOWN','formal_submission':'NOT_SUBMITTED'}
(out/'manifest.json').write_bytes((json.dumps(m,indent=2)+'\n').encode())
print(json.dumps(m))
