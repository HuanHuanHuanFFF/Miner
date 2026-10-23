"""Keep one-column-group F10 computation but eliminate the global boxed A map."""
from datetime import datetime, timezone
import hashlib
import json
from pathlib import Path

ROOT=Path(__file__).resolve().parents[5]
parent=ROOT/'competitions/floatlib/candidates/f01-d10-bmm-direct-rows/Kernel.lean'
raw=parent.read_bytes();expected='a06608bdc419d4647af301bfdd617d52e4796c404661a28672a022eef4a10b78'
assert hashlib.sha256(raw).hexdigest()==expected
source=raw.decode('utf-8')
start=source.index('namespace Packed10Index\n')
end=source.index('end Packed10Index',start)+len('end Packed10Index')
block=source[start:end]
block=block.replace('namespace Packed10Index\n','namespace Submission.R11RawIndex\n\nopen FloatLib.Floats Competition\n',1)
block=block.replace('end Packed10Index','end Submission.R11RawIndex')
block=block.replace('(A : Array Float32)','(A : Array Binary32)')
old='''theorem ugetA_getD (A : Array Binary32) (i : USize) (h : i.toNat < A.size) :
    A.uget i h = A.getD i.toNat zero32 := by
  simp [Array.uget, Array.getD, h]'''
new='''theorem ugetA_getD (A : Array Binary32) (i : USize) (h : i.toNat < A.size) :
    ExecFloat.Binary.toFloat32 (A.uget i h) =
      (A.map ExecFloat.Binary.toFloat32).getD i.toNat zero32 := by
  rw [Packed10.nativeA_getD]
  congr 1
  simp [Array.uget, Array.getD, h]'''
assert block.count(old)==1
block=block.replace(old,new,1)
old='''    let a := A.uget (baseA + k)
      (by rw [addNat baseA k (Nat.lt_trans ha hAS)]; exact ha)'''
new='''    let a := ExecFloat.Binary.toFloat32 (A.uget (baseA + k)
      (by rw [addNat baseA k (Nat.lt_trans ha hAS)]; exact ha))'''
assert block.count(old)==1
block=block.replace(old,new,1)
block=block.replace('Packed10.dot10 n baseA.toNat A B','Packed10.dot10 n baseA.toNat (A.map ExecFloat.Binary.toFloat32) B')
block=block.replace('Packed10.dot10 n baseA A B','Packed10.dot10 n baseA (A.map ExecFloat.Binary.toFloat32) B')

anchor='\nnamespace Submission\nopen FloatLib.Floats Competition\n\ndef bmm (batch m n p : Nat)'
assert source.count(anchor)==1
prefix,last=source.rsplit(anchor,1);last=anchor+last
last=last.replace('def bmm (','def bmmBeforeRawA (',1).replace('theorem bmm_spec :','theorem bmmBeforeRawA_spec :',1)
last=last.replace('(bmm batch m n p A B).get','(bmmBeforeRawA batch m n p A B).get',1).replace('  unfold bmm\n','  unfold bmmBeforeRawA\n',1)
extra='''

namespace Submission.R11RawA
open FloatLib.Floats Competition

def core (batch m n p : Nat)
    (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p)) : Vector Binary32 (batch * m * p) :=
  let packedB := Packed10.packB batch n p B
  (Vector.ofFn fun r : Fin (batch * m) => r).flatMap fun r =>
    have hm : 0 < m := Nat.pos_of_lt_mul_left r.isLt
    let b : Fin batch := ⟨r.val / m, (Nat.div_lt_iff_lt_mul hm).2 r.isLt⟩
    let i : Fin m := ⟨r.val % m, Nat.mod_lt _ hm⟩
    let rowTiles := Vector.ofFn fun g : Fin (Packed10.groups p) =>
      R11RawIndex.runDot n ((b.val * m + i.val) * n) A.toArray ((packedB.get b).get g)
    RowOutput.row batch m n p A B b i rowTiles

theorem core_eq (batch m n p : Nat)
    (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p)) :
    core batch m n p A B = RowStream.core batch m n p A B := by
  simp only [core, RowStream.core, R11RawIndex.runDot_eq, Packed10Index.runDot_eq]

end Submission.R11RawA

namespace Submission
open FloatLib.Floats Competition

def bmm (batch m n p : Nat) (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p)) : Vector Binary32 (batch * m * p) :=
  if 4 < n ∧ 2 < p ∧ p ≤ 10 then R11RawA.core batch m n p A B
  else bmmBeforeRawA batch m n p A B

theorem bmm_spec : ∀ (batch m n p : Nat) (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p)),
    (bmm batch m n p A B).get = bmmSpec batch m n p A.get B.get := by
  intro batch m n p A B
  unfold bmm
  split
  · rw [R11RawA.core_eq, RowStream.core_eq, Packed10.core_eq_reference]
    exact referenceBmm_spec batch m n p A B
  · exact bmmBeforeRawA_spec batch m n p A B

end Submission
'''
result=(prefix+last+'\n\n'+block+extra).encode('utf-8')
out=ROOT/'competitions/floatlib/candidates/f01-d11-bmm-raw-a-one-group'
out.mkdir(exist_ok=False);assert len(result)<=256000
(out/'Kernel.lean').write_bytes(result)
manifest={'candidate':out.name,'candidate_file':'Kernel.lean','candidate_sha256':hashlib.sha256(result).hexdigest(),'candidate_bytes':len(result),
 'created_at_utc':datetime.now(timezone.utc).isoformat(),'parent':parent.parent.name,'parent_sha256':expected,
 'mechanism':'For n>4 and3<=p<=10 only, keep F10 packedB, one-group machine-index dot and ordered native MAC; remove boxed nativeA array and convert each raw A value once per k inside the shared ten-output loop. All preparations and outputs counted. Other shapes exact a066.',
 'proof':'New raw USize loop equals existing Packed10.dot10 on mapped A via total uget/map equality; raw RowStream equals original RowStream. New source statement/full gate NOT_RUN.',
 'validation_mode':'full-gate','proof_status':'NOT_RUN','performance':'UNKNOWN','formal_submission':'NOT_SUBMITTED'}
(out/'manifest.json').write_text(json.dumps(manifest,ensure_ascii=False,indent=2)+'\n',encoding='utf-8')
print(json.dumps(manifest,ensure_ascii=False))
