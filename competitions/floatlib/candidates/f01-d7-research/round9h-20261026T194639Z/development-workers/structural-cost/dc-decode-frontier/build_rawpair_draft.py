"""Build one raw-DC-pair source/proof draft. Static only, explicitly NOT_RUN."""
from pathlib import Path
from datetime import datetime,timezone
import difflib,hashlib,json
H=Path(__file__).resolve().parent
R=next(p for p in H.parents if(p/'competitions/floatlib/pins.json').is_file())
parent=R/'competitions/floatlib/candidates/f01-r15-dev-packed-b2-1/Kernel.lean'
raw=parent.read_bytes();text=raw.decode();sha=lambda b:hashlib.sha256(b).hexdigest()
assert sha(raw)=='622d8394a7127e93dcaf992c62c6dfcff7208d212738409a5e34525dfafd1a58'
a=text.index('namespace Submission.R15ThinPairs\n');b=text.index('\ndef dispatch ',a)
fragment=text[a:b].replace('Submission.R15ThinPairs','Submission.R19DCRawPair')
fragment=fragment.replace('(A : Array Binary32) (B : Array Float32)','(A B : Array Binary32)')
fragment=fragment.replace('let b0 := B.getD (baseB + k * p) Packed10.zero32',
 'let b0 := ExecFloat.Binary.toFloat32 (B.getD (baseB + k * p) posZero)')
fragment=fragment.replace('let b1 := B.getD (baseB + 1 + k * p) Packed10.zero32',
 'let b1 := ExecFloat.Binary.toFloat32 (B.getD (baseB + 1 + k * p) posZero)')
fragment=fragment.replace('(B.map ExecFloat.Binary.toFloat32)','B')
fragment=fragment.replace('    simp only [Packed10.nativeA_getD]\n','')
fragment=fragment.replace(' (preparedB : Array Float32)','')
fragment=fragment.replace('loop n baseA baseB p A.toArray preparedB','loop n baseA baseB p A.toArray B.toArray')
fragment=fragment.replace(' preparedB','')
fragment=fragment.replace(' (B.toArray.map ExecFloat.Binary.toFloat32)','')
fragment=fragment.replace('  let preparedB := B.toArray.map ExecFloat.Binary.toFloat32\n','')
# Prior replacement removed the variable name in this one declaration; remove the resulting line.
fragment=fragment.replace('  let := B.toArray.map ExecFloat.Binary.toFloat32\n','')
ga=fragment.index('  let result := loop',fragment.index('@[inline] def group'))
gb=fragment.index('\ntheorem group_prefix',ga)
fragment=fragment[:ga]+'''  let count := min 2 (p - 2 * g.val)
  if count = 1 then
    RowStream.emit count (fun l =>
      NativeFinal.dot n baseA (baseB + l.val) p A.toArray B.toArray) out
  else
    let result := loop n baseA baseB p A.toArray B.toArray
      0 Packed10.zero32 Packed10.zero32
    RowStream.emit count (fun l =>
      Packed10.finish n baseA (baseB + l.val) p A.toArray B.toArray
        (select result l.val)) out
''' +fragment[gb:]
pa=fragment.index('  unfold group\n',fragment.index('theorem group_prefix'))
pb=fragment.index('\n@[inline] def row',pa)
shared='''    have hcol : 2 * g.val + l.val < p := by
      have hl := l.isLt
      omega
    rw [show r.val * p + 2 * g.val + l.val =
      r.val * p + (2 * g.val + l.val) by omega,
      RowStream.point_row batch m n p A B r.val (2 * g.val + l.val) hm hp hcol]
'''
fragment=fragment[:pa]+'''  unfold group
  dsimp only
  split
  · apply RowStream.emit_prefix
    · simpa only [hstart] using hout
    · intro l
'''+''.join('  '+line+'\n'for line in shared.splitlines())+'''      simp only [Nat.add_assoc]
  · apply RowStream.emit_prefix
    · simpa only [hstart] using hout
    · intro l
'''+''.join('  '+line+'\n'for line in shared.splitlines())+'''      have h := finish_select n (r.val * n) (r.val / m * n * p + 2 * g.val) p
        A.toArray B.toArray l.val (Nat.lt_of_lt_of_le l.isLt (Nat.min_le_left _ _))
      simpa only [Nat.add_assoc] using h
''' +fragment[pb:]
fragment=fragment.replace('def core (batch','def pairCore (batch').replace('theorem core_eq_reference','theorem pairCore_eq_reference')
fragment=fragment.replace('    core batch m n p A B = referenceBmm','    pairCore batch m n p A B = referenceBmm')
# Keep baseline DC's one row-address computation per row, instead of importing
# ThinPairs' per-group quotient/address duplication.
ga=fragment.index('@[inline] def group (');gb=fragment.index('\ntheorem group_prefix',ga)
generic=fragment[ga:gb]
body=generic[generic.index('  let count :='):]
body=body.replace('baseB + l.val','(baseB + 2 * g.val) + l.val')
body=body.replace('loop n baseA baseB p A.toArray B.toArray','loop n baseA (baseB + 2 * g.val) p A B')
body=body.replace('A.toArray B.toArray','A B')
fragment=fragment[:ga]+'''@[inline] def groupFrom (n baseA baseB p : Nat) (A B : Array Binary32)
    (out : Array Binary32) (g : Fin (groups p)) : Array Binary32 :=
'''+body+'''
@[inline] def group (batch m n p : Nat)
    (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p))
    (r : Fin (batch * m)) (out : Array Binary32) (g : Fin (groups p)) :
    Array Binary32 :=
  groupFrom n (r.val * n) (r.val / m * n * p) p A.toArray B.toArray out g
''' +fragment[gb:]
fragment=fragment.replace('  unfold group\n','  unfold group groupFrom\n')
fragment=fragment.replace('  Fin.foldl (groups p) (group batch m n p A B r) out',
'''  let baseA := r.val * n
  let baseB := r.val / m * n * p
  Fin.foldl (groups p) (groupFrom n baseA baseB p A.toArray B.toArray) out''')
fragment=fragment.replace('simpa only [row, hlast,','simpa only [row, group, hlast,')
fragment='''/- R19 diagnostic draft: no prepared A/B. Full raw pairs share one A decode;
   odd tail uses original NativeFinal.dot. New proofs/whole source NOT_RUN. -/
'''+fragment
fragment+='''
/-- Keep old n=0/1 and p=0/1 runtime; target complete pairs with n>1. -/
def core (batch m n p : Nat)
    (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p)) : Vector Binary32 (batch * m * p) :=
  if n ≤ 1 ∨ p ≤ 1 then DirectContinuous.core batch m n p A B
  else pairCore batch m n p A B

theorem core_eq_reference (batch m n p : Nat)
    (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p)) :
    core batch m n p A B = referenceBmm batch m n p A B := by
  unfold core
  split
  · exact DirectContinuous.core_eq_reference batch m n p A B
  · exact pairCore_eq_reference batch m n p A B

theorem core_eq_direct (batch m n p : Nat)
    (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p)) :
    core batch m n p A B = DirectContinuous.core batch m n p A B :=
  (core_eq_reference batch m n p A B).trans
    (DirectContinuous.core_eq_reference batch m n p A B).symm

end Submission.R19DCRawPair

'''
assert 'preparedB'not in fragment and '.map'not in fragment and 'Array Float32'not in fragment
marker='namespace Submission\nopen FloatLib.Floats Competition\n\ndef bmmBeforeR11Cross'
assert text.count(marker)==1
start=text.index(marker);end=text.index('\nend Submission',start)
oldRoute=text[start:end]
newRoute=oldRoute.replace('DirectContinuous.core','R19DCRawPair.core')
assert oldRoute.count('DirectContinuous.core')==2
draft=text[:start]+fragment+newRoute+text[end:]
inverse=draft.replace(fragment,'',1).replace(newRoute,oldRoute,1)
assert inverse.encode()==raw
out=draft.encode();assert len(out)<=256000
(H/'RawPair.lean.inc').write_bytes(fragment.encode())
(H/'Kernel-dc-rawpair.draft.lean').write_bytes(out)
(H/'rawpair-forward.diff.txt').write_bytes(''.join(difflib.unified_diff(text.splitlines(True),draft.splitlines(True),fromfile='622d/Kernel.lean',tofile='DRAFT/rawpair')).encode())
(H/'rawpair-inverse.diff.txt').write_bytes(''.join(difflib.unified_diff(draft.splitlines(True),text.splitlines(True),fromfile='DRAFT/rawpair',tofile='622d/Kernel.lean')).encode())
roots=['loop_s0','loop_s1','finish_select','group_prefix','row_prefix','output_prefix','pairCore_eq_reference','core_eq_reference','core_eq_direct']
rec=dict(at_utc=datetime.now(timezone.utc).isoformat(),state='COMPLETE_DC_RAW_PAIR_SOURCE_PROOF_DRAFT_NOT_RUN',
 parent_sha256=sha(raw),parent_bytes=len(raw),draft_sha256=sha(out),draft_bytes=len(out),delta_bytes=len(out)-len(raw),
 fragment_sha256=sha(fragment.encode()),fragment_bytes=len(fragment.encode()),exact_inverse_to_parent=True,
 scope='One new namespace plus only existing DC runtime/proof target substitutions; outer guard, underflow/B2 routing and public other3 unchanged',
 proof_roots=['Submission.R19DCRawPair.'+x for x in roots]+['Submission.bmmBeforeR11Cross_spec',
 'Submission.add_spec','Submission.mul_spec','Submission.sum_spec','Submission.bmm_spec'],
 Lean='NOT_RUN',C='NOT_RUN',ASM='NOT_RUN',full_gate='NOT_RUN',performance='UNKNOWN')
(H/'draft-receipt.json').write_bytes((json.dumps(rec,indent=2)+'\n').encode());print(json.dumps(rec,indent=2))
