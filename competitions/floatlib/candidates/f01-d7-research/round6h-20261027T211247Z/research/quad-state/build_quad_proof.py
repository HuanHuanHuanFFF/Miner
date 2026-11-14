from pathlib import Path
from datetime import datetime, timezone
import hashlib, json

HERE=Path(__file__).resolve().parent
ROUND=HERE.parents[1]
RUNTIME=ROUND/'development-cost/StreamingQuad.lean.inc'
ROOT=next(p for p in HERE.parents if (p/'AGENTS.md').exists())
BASE=ROOT/'competitions/floatlib/candidates/f01-r21-dev-streaming-pair-probe2/Kernel.lean'

text='''/- Proof-only refinement for the exact R22StreamingQuad runtime.
   Uses R20WideRowRefinement from the accepted R21 4e36 carrier. NOT_RUN. -/
namespace Submission.R22StreamingQuad
open FloatLib.Floats Competition

theorem advance_get (p n baseA baseB : Nat) (A B : Array Binary32)
    (k : Nat) (s : State p) (j : Fin p) :
    (advance p n baseA baseB A B k s).get j =
      update (ExecFloat.Binary.toFloat32 (A.getD (baseA+k) posZero))
        (ExecFloat.Binary.toFloat32 (A.getD (baseA+n+k) posZero))
        (ExecFloat.Binary.toFloat32 (A.getD (baseA+2*n+k) posZero))
        (ExecFloat.Binary.toFloat32 (A.getD (baseA+3*n+k) posZero))
        (ExecFloat.Binary.toFloat32 (B.getD (baseB+j.val+k*p) posZero)) (s.get j) := by
  change (s.toArray.mapIdx (fun i cell => update
    (ExecFloat.Binary.toFloat32 (A.getD (baseA+k) posZero))
    (ExecFloat.Binary.toFloat32 (A.getD (baseA+n+k) posZero))
    (ExecFloat.Binary.toFloat32 (A.getD (baseA+2*n+k) posZero))
    (ExecFloat.Binary.toFloat32 (A.getD (baseA+3*n+k) posZero))
    (ExecFloat.Binary.toFloat32 (B.getD (baseB+k*p+i) posZero)) cell))[j.val] = _
  rw [Array.getElem_mapIdx]
  have haddr : baseB+k*p+j.val = baseB+j.val+k*p := by omega
  rw [haddr]
  rfl

'''
roots=['advance_get']
for i in range(4):
    offset=['baseA','(baseA+n)','(baseA+2*n)','(baseA+3*n)'][i]
    text+=f'''@[inline] def view{i} {{p : Nat}} (s : State p) (j : Fin p) : Float32 := (s.get j).s{i}

theorem advance_view{i} (p n baseA baseB : Nat) (A B : Array Binary32)
    (k : Nat) (s : State p) (j : Fin p) :
    view{i} (advance p n baseA baseB A B k s) j = view{i} s j +
      ExecFloat.Binary.toFloat32 (A.getD ({offset}+k) posZero) *
      ExecFloat.Binary.toFloat32 (B.getD (baseB+j.val+k*p) posZero) := by
  simpa only [view{i},update] using congrArg (fun x : Cell => x.s{i})
    (advance_get p n baseA baseB A B k s j)

theorem initial_view{i} (p : Nat) (j : Fin p) : view{i} (initial p) j = Packed10.zero32 := by
  change ((Array.replicate p (⟨Packed10.zero32,Packed10.zero32,
    Packed10.zero32,Packed10.zero32⟩ : Cell))[j.val]).s{i} = _
  simp only [Array.getElem_replicate]

'''
    roots += [f'advance_view{i}',f'initial_view{i}']
text+='''theorem loop_eq_storage (p n baseA baseB : Nat) (A B : Array Binary32)
    (k : Nat) (s : State p) :
    loop p n baseA baseB A B k s =
      R20WideRowRefinement.storageLoop n (advance p n baseA baseB A B) k s := by
  have he := @loop.eq_def p n baseA baseB A B k s
  have hg := @R20WideRowRefinement.storageLoop.eq_def (State p) n
    (advance p n baseA baseB A B) k s
  by_cases hk : k<n
  · rw [he,hg]
    simp only [dif_pos hk]
    exact loop_eq_storage p n baseA baseB A B (k+1) _
  · rw [he,hg]
    simp only [dif_neg hk]
termination_by n-k
decreasing_by all_goals omega

'''
roots+=['loop_eq_storage']
for i in range(4):
    offset=['baseA','(baseA+n)','(baseA+2*n)','(baseA+3*n)'][i]
    text+=f'''theorem loop_view{i} (p n baseA baseB : Nat) (A B : Array Binary32)
    (k : Nat) (s : State p) (j : Fin p) :
    view{i} (loop p n baseA baseB A B k s) j =
      NativeFinal.dotLoop n {offset} (baseB+j.val) p A B k (view{i} s j) := by
  rw [loop_eq_storage]
  exact R20WideRowRefinement.storageLoop_lane n p p {offset} baseB A B view{i}
    (advance p n baseA baseB A B)
    (fun k _ s j => advance_view{i} p n baseA baseB A B k s j) k s j

theorem finish{i} (p n baseA baseB : Nat) (A B : Array Binary32) (j : Fin p) :
    Packed10.finish n {offset} (baseB+j.val) p A B
      ((loop p n baseA baseB A B 0 (initial p)).get j).s{i} =
      NativeFinal.dot n {offset} (baseB+j.val) p A B := by
  apply Packed10.finish_eq_dot
  simpa only [initial_view{i}] using
    loop_view{i} p n baseA baseB A B 0 (initial p) j

'''
    roots += [f'loop_view{i}',f'finish{i}']
text+='''theorem rows4_eq_control (p n baseA baseB : Nat) (A B : Array Binary32)
    (out : Array Binary32) :
    rows4 p n baseA baseB A B out =
      RowStream.emit p (fun j => NativeFinal.dot n (baseA+3*n) (baseB+j.val) p A B)
        (RowStream.emit p (fun j => NativeFinal.dot n (baseA+2*n) (baseB+j.val) p A B)
          (RowStream.emit p (fun j => NativeFinal.dot n (baseA+n) (baseB+j.val) p A B)
            (RowStream.emit p (fun j => NativeFinal.dot n baseA (baseB+j.val) p A B) out))) := by
  by_cases hp : p=0
  · subst p
    rfl
  · simp only [rows4,hp,if_false,finish0,finish1,finish2,finish3]

end Submission.R22StreamingQuad
'''
roots+=['rows4_eq_control']
proof=HERE/'QuadStateProof.lean.inc'
proof.write_text(text,encoding='utf-8',newline='\n')
fullroots=['Submission.R22StreamingQuad.'+r for r in roots]
(HERE/'HelperAudit.lean.inc').write_text(''.join('#print axioms '+r+'\n' for r in fullroots),encoding='utf-8',newline='\n')
sha=lambda p:hashlib.sha256(p.read_bytes()).hexdigest()
manifest={
 'state':'NOT_RUN_PROOF_ONLY_FRAGMENT','created_utc':datetime.now(timezone.utc).isoformat(),
 'actual_role_start_utc':'2026-10-27T21:17:57Z','quad_work_start_utc':'2026-10-27T21:37:13Z',
 'deadline_utc':'2026-10-28T03:12:47Z',
 'runtime_path':str(RUNTIME.relative_to(ROOT)).replace('\\','/'),'runtime_sha256':sha(RUNTIME),
 'runtime_bytes':RUNTIME.stat().st_size,
 'required_carrier':str(BASE.relative_to(ROOT)).replace('\\','/'),'carrier_sha256':sha(BASE),
 'proof_file':proof.name,'proof_sha256':sha(proof),'proof_bytes':proof.stat().st_size,
 'helper_audit_sha256':sha(HERE/'HelperAudit.lean.inc'),'explicit_helper_audit':fullroots,
 'scope':'Actual4lane advance/mapIdx, four view projections, original dotLoop order, +0 initial and Packed10.finish including raw fallback; rows4 equals four original dot rows.',
 'runtime_modified':False,'public_candidate_assembled':False,'CI':'NOT_RUN','local_Lean':False,
 'missing':['pinned Lean/replay/helper audit','A block/tail/batch writer integration','complete public BMM gate','runtime cost and independent confirmation'],
}
(HERE/'manifest.json').write_text(json.dumps(manifest,indent=2)+'\n',encoding='utf-8')
print(json.dumps(manifest,indent=2))
