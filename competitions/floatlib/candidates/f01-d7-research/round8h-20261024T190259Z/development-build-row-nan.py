"""Restructure RowStream: raw-NaN rows use exact early replay before native work."""
from pathlib import Path
from datetime import datetime,timezone
import hashlib,json
OUT=Path(__file__).resolve().parent;ROOT=OUT.parents[4];C=ROOT/'competitions/floatlib/candidates'
parent=C/'f01-d12-scalar-combined/Kernel.lean';raw=parent.read_bytes();assert hashlib.sha256(raw).hexdigest()=='df5c61a0ca24a8ef18c0c42d83bdd23466872d3fe8f39dd912e9c347b27fb172'
text=raw.decode();left=text.index('namespace Submission.RowStream');right=text.index('end Submission.RowStream',left)
block=text[left:right]
start=block.index('@[inline] def row (');end=block.index('\ntheorem row_prefix',start)
row='''def rowHasNaN (n baseA : Nat) (A : Array Binary32) (k : Nat) : Bool :=
  if hk : k < n then
    if DWordNaN.rawNaN (A.getD (baseA + k) posZero).raw.1 then true
    else rowHasNaN n baseA A (k + 1)
  else false
termination_by n - k

theorem softwareDot_eq (n baseA baseB p : Nat) (A B : Array Binary32) :
    R7NaNReplay.replayEarly n baseA baseB p A B = NativeFinal.dot n baseA baseB p A B := by
  rw [R7NaNReplay.replayEarly_eq, NativeFinal.dot_eq]
  apply congrArg (fun step : Binary32 → Fin n → Binary32 => Fin.foldl n step posZero)
  funext acc i
  simp only [R7NaNReplay.replayStep, Submission.add_eq, Submission.mul_eq]

@[inline] def row (batch m n p : Nat)
    (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p)) (nativeA : Thunk (Array Float32))
    (packedB : Thunk (Vector (Vector (Vector Packed10.F10 n) (Packed10.groups p)) batch))
    (out : Array Binary32) (r : Fin (batch * m)) : Array Binary32 :=
  if rowHasNaN n (r.val * n) A.toArray 0 then
    emit p (fun j => R7NaNReplay.replayEarly n (r.val * n)
      (r.val / m * n * p + j.val) p A.toArray B.toArray) out
  else Fin.foldl (Packed10.groups p)
    (group batch m n p A B nativeA.get packedB.get r) out
'''
block=block[:start]+row+block[end:]
start=block.index('theorem row_prefix');end=block.index('\ndef output',start)
proof=block[start:end]
target='''      (row batch m n p A B (A.toArray.map ExecFloat.Binary.toFloat32)
        (Packed10.packB batch n p B) out r) := by
'''
replacement='''      (row batch m n p A B (Thunk.mk fun _ => A.toArray.map ExecFloat.Binary.toFloat32)
        (Thunk.mk fun _ => Packed10.packB batch n p B) out r) := by
  unfold row
  split
  · have h : Prefix (point batch m n p A B) (r.val * p + p)
        (emit p (fun j => R7NaNReplay.replayEarly n (r.val * n)
          (r.val / m * n * p + j.val) p A.toArray B.toArray) out) := by
      apply emit_prefix
      · exact hout
      · intro j
        have hm : 0 < m := Nat.pos_of_lt_mul_left r.isLt
        have hp : 0 < p := by have hj := j.isLt; omega
        rw [softwareDot_eq, point_row batch m n p A B r.val j.val hm hp j.isLt]
    simpa only [Nat.add_mul, Nat.one_mul] using h
  · change Prefix (point batch m n p A B) ((r.val + 1) * p)
      (Fin.foldl (Packed10.groups p)
        (group batch m n p A B (A.toArray.map ExecFloat.Binary.toFloat32)
          (Packed10.packB batch n p B) r) out)
'''
assert proof.count(target)==1
head,tail=proof.split(target)
proof=head+replacement+''.join('  '+line if line.strip() else line for line in tail.splitlines(keepends=True))
proof=proof.replace('simpa only [row, hlast, Nat.add_mul, Nat.one_mul]', 'simpa only [hlast, Nat.add_mul, Nat.one_mul]')
block=block[:start]+proof+block[end:]
block=block.replace('  let nativeA := A.toArray.map ExecFloat.Binary.toFloat32\n  let packedB := Packed10.packB batch n p B\n',
                    '  let nativeA := Thunk.mk fun _ => A.toArray.map ExecFloat.Binary.toFloat32\n  let packedB := Thunk.mk fun _ => Packed10.packB batch n p B\n')
start=block.index('theorem output_prefix');end=block.index('\ndef core',start)
prefix=block[start:end].replace('(row batch m n p A B (A.toArray.map ExecFloat.Binary.toFloat32)\n      (Packed10.packB batch n p B))',
                                  '(row batch m n p A B (Thunk.mk fun _ => A.toArray.map ExecFloat.Binary.toFloat32)\n      (Thunk.mk fun _ => Packed10.packB batch n p B))')
block=block[:start]+prefix+block[end:]
result=(text[:left]+block+text[right:]).encode();assert len(result)<=256000
folder=C/'f01-r14-dev-row-nan-lazy';assert not folder.exists();folder.mkdir()
(folder/'Kernel.lean').write_bytes(result)
meta={'candidate':folder.name,'candidate_file':'Kernel.lean','candidate_sha256':hashlib.sha256(result).hexdigest(),'candidate_bytes':len(result),'parent':'f01-d12-scalar-combined','parent_sha256':hashlib.sha256(raw).hexdigest(),'created_at_utc':datetime.now(timezone.utc).isoformat(),'validation_mode':'statement-only','proof_status':'NOT_RUN','mechanism':'Before RowStream native work, scan each A row for a raw NaN; those rows directly run the existing exact early software replay per output. Other rows use the same packed native path. Pure lazy thunks defer A conversion/B packing until a row actually needs them, and share those arrays across remaining rows.','correctness':'Classification never establishes a numeric equality: both selected computations are independently proved equal to the complete original ordered dot. Sign/payload replay remains original. No p-threshold, tensor shape cutoff or sum reordering.','performance':'UNKNOWN; measures raw scan/thunk overhead together with avoided native first pass and preparation. All non-RowStream paths unchanged.'}
(folder/'manifest.json').write_bytes((json.dumps(meta,ensure_ascii=False,indent=2)+'\n').encode())
(OUT/'development-row-nan-build.json').write_bytes((json.dumps(meta,ensure_ascii=False,indent=2)+'\n').encode())
print(json.dumps(meta,ensure_ascii=False))
