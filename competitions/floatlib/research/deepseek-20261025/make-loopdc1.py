"""Patch B2's DirectContinuous row to a first-order loop (no per-row closure allocation).

Only the iteration structure changes: `row` keeps computing one output per lane with
NativeFinal.dot, but iterates with an explicit recursive loop instead of
`RowStream.emit` + a capturing lambda.
"""
import datetime
import hashlib
import json
from pathlib import Path

TRACK = Path(r"D:\CodingProject\Bitget-DeepSeek\competitions\floatlib")
PARENT = TRACK / "candidates/f01-r15-dev-packed-b2-1/Kernel.lean"
SRC = PARENT.read_text(encoding="utf-8")
PARENT_SHA = hashlib.sha256(PARENT.read_bytes()).hexdigest()
assert PARENT_SHA == "622d8394a7127e93dcaf992c62c6dfcff7208d212738409a5e34525dfafd1a58"

OLD_ROW = """@[inline] def row (batch m n p : Nat)
    (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p))
    (out : Array Binary32) (r : Fin (batch * m)) : Array Binary32 :=
  let baseA := r.val * n
  let baseB := r.val / m * n * p
  RowStream.emit p (fun j =>
    NativeFinal.dot n baseA (baseB + j.val) p A.toArray B.toArray) out"""

NEW_ROW = """def emitLoop (n baseA baseB p : Nat) (A B : Array Binary32)
    (out : Array Binary32) (j : Nat) : Array Binary32 :=
  if hj : j < p then
    emitLoop n baseA baseB p A B
      (out.push (NativeFinal.dot n baseA (baseB + j) p A B)) (j + 1)
  else out

theorem emitLoop_eq (n baseA baseB p : Nat) (A B : Array Binary32)
    (out : Array Binary32) (j : Nat) :
    emitLoop n baseA baseB p A B out j =
      Fin.foldl.loop p (fun acc (l : Fin p) =>
        acc.push (NativeFinal.dot n baseA (baseB + l.val) p A B)) out j := by
  rw [emitLoop]
  split
  · rename_i hj
    rw [Fin.foldl.loop, dif_pos hj]
    exact emitLoop_eq n baseA baseB p A B _ (j + 1)
  · rename_i hj
    rw [Fin.foldl.loop, dif_neg hj]
termination_by p - j

@[inline] def row (batch m n p : Nat)
    (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p))
    (out : Array Binary32) (r : Fin (batch * m)) : Array Binary32 :=
  let baseA := r.val * n
  let baseB := r.val / m * n * p
  emitLoop n baseA baseB p A.toArray B.toArray out 0

theorem row_emit_eq (batch m n p : Nat)
    (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p))
    (out : Array Binary32) (r : Fin (batch * m)) :
    row batch m n p A B out r =
      RowStream.emit p (fun j : Fin p => NativeFinal.dot n (r.val * n)
        (r.val / m * n * p + j.val) p A.toArray B.toArray) out := by
  dsimp only [row, RowStream.emit]
  rw [emitLoop_eq]
  rfl"""

OLD_TAIL = """  simpa only [row, Nat.add_mul, Nat.one_mul] using h"""
NEW_TAIL = """  rw [row_emit_eq]
  simpa only [Nat.add_mul, Nat.one_mul] using h"""

FIX_OLD = """  dsimp only [row, DirectContinuous.row]
  apply congrArg (fun read : Fin p → Binary32 => RowStream.emit p read out)"""
FIX_NEW = """  dsimp only [row]
  rw [DirectContinuous.row_emit_eq]
  apply congrArg (fun read : Fin p → Binary32 => RowStream.emit p read out)"""

assert SRC.count(OLD_ROW) == 1, SRC.count(OLD_ROW)
assert SRC.count(OLD_TAIL) == 1, SRC.count(OLD_TAIL)
assert SRC.count(FIX_OLD) == 1, SRC.count(FIX_OLD)
text = SRC.replace(OLD_ROW, NEW_ROW).replace(OLD_TAIL, NEW_TAIL).replace(FIX_OLD, FIX_NEW)
data = text.encode("utf-8")
sha = hashlib.sha256(data).hexdigest()
out = TRACK / "candidates/f01-deepseek-loopdc1"
out.mkdir(parents=True, exist_ok=True)
(out / "Kernel.lean").write_bytes(data)
manifest = {
    "candidate": "f01-deepseek-loopdc1",
    "candidate_file": "Kernel.lean",
    "candidate_sha256": sha,
    "candidate_bytes": len(data),
    "created_at_utc": datetime.datetime.now(datetime.timezone.utc).isoformat(),
    "parent": "competitions/floatlib/candidates/f01-r15-dev-packed-b2-1/Kernel.lean",
    "parent_sha256": PARENT_SHA,
    "mechanism": "DirectContinuous.row iterates outputs with a first-order recursive emitLoop instead of RowStream.emit with a capturing lambda, removing one closure allocation (alloc_closure + closure_set + refcount traffic) per row. Arithmetic, order, NativeFinal.dot and the writer's push semantics are unchanged.",
    "proof": "emitLoop_eq shows the loop equals Fin.foldl.loop over the same step; row_emit_eq bridges row to the previous RowStream.emit form, so row_prefix/output_prefix/core_eq_reference keep their meaning.",
    "validation_mode": "statement-only",
    "proof_status": "STATIC_PATCH_NOT_COMPILED",
    "performance": "NOT_RUN",
    "hypothesis": "Per-row closure allocation is a measurable part of BMM cost; removing it should improve shapes with many rows.",
    "formal_submission": "NOT_SUBMITTED",
}
(out / "manifest.json").write_text(json.dumps(manifest, ensure_ascii=False, indent=2) + "\n", encoding="utf-8")
print("candidate", sha, len(data))
