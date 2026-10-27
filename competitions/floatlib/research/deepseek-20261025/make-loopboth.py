"""Combine the DirectContinuous and R15PackedB2 first-order-loop patches."""
import datetime
import hashlib
import json
from pathlib import Path

TRACK = Path(r"D:\CodingProject\Bitget-DeepSeek\competitions\floatlib")
BASE = TRACK / "candidates/f01-deepseek-loopdc1/Kernel.lean"
SRC = BASE.read_text(encoding="utf-8")
BASE_SHA = hashlib.sha256(BASE.read_bytes()).hexdigest()

OLD = """@[inline] def row (batch m n p : Nat)
    (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p))
    (packedB : Vector (Vector B2 n) (batch * R15ThinPairs.groups p))
    (out : Array Binary32) (r : Fin (batch * m)) : Array Binary32 :=
  Fin.foldl (R15ThinPairs.groups p) (group batch m n p A B packedB r) out"""

NEW = """def rowLoop (batch m n p : Nat)
    (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p))
    (packedB : Vector (Vector B2 n) (batch * R15ThinPairs.groups p))
    (out : Array Binary32) (r : Fin (batch * m)) (g : Nat) : Array Binary32 :=
  if hg : g < R15ThinPairs.groups p then
    rowLoop batch m n p A B packedB
      (group batch m n p A B packedB r out ⟨g, hg⟩) r (g + 1)
  else out

theorem rowLoop_eq (batch m n p : Nat)
    (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p))
    (packedB : Vector (Vector B2 n) (batch * R15ThinPairs.groups p))
    (out : Array Binary32) (r : Fin (batch * m)) (k : Nat) :
    rowLoop batch m n p A B packedB out r k =
      Fin.foldl.loop (R15ThinPairs.groups p) (group batch m n p A B packedB r) out k := by
  rw [rowLoop]
  split
  · rename_i hk
    rw [Fin.foldl.loop, dif_pos hk]
    exact rowLoop_eq batch m n p A B packedB _ r (k + 1)
  · rename_i hk
    rw [Fin.foldl.loop, dif_neg hk]
termination_by R15ThinPairs.groups p - k

@[inline] def row (batch m n p : Nat)
    (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p))
    (packedB : Vector (Vector B2 n) (batch * R15ThinPairs.groups p))
    (out : Array Binary32) (r : Fin (batch * m)) : Array Binary32 :=
  rowLoop batch m n p A B packedB out r 0"""

OLD_EQ = """theorem row_eq (batch m n p : Nat)
    (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p)) (out : Array Binary32) (r : Fin (batch * m)) :
    row batch m n p A B (packB batch n p B) out r =
      R15ThinPairs.row batch m n p A B (B.toArray.map ExecFloat.Binary.toFloat32) out r := by
  unfold row R15ThinPairs.row
  apply congrArg (fun step : Array Binary32 → Fin (R15ThinPairs.groups p) → Array Binary32 =>
    Fin.foldl (R15ThinPairs.groups p) step out)
  funext acc g
  exact group_eq batch m n p A B r acc g"""

NEW_EQ = """theorem row_foldl (batch m n p : Nat)
    (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p))
    (packedB : Vector (Vector B2 n) (batch * R15ThinPairs.groups p))
    (out : Array Binary32) (r : Fin (batch * m)) :
    row batch m n p A B packedB out r =
      Fin.foldl (R15ThinPairs.groups p) (group batch m n p A B packedB r) out := by
  unfold row
  rw [rowLoop_eq]
  rfl

theorem row_eq (batch m n p : Nat)
    (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p)) (out : Array Binary32) (r : Fin (batch * m)) :
    row batch m n p A B (packB batch n p B) out r =
      R15ThinPairs.row batch m n p A B (B.toArray.map ExecFloat.Binary.toFloat32) out r := by
  rw [row_foldl]
  unfold R15ThinPairs.row
  apply congrArg (fun step : Array Binary32 → Fin (R15ThinPairs.groups p) → Array Binary32 =>
    Fin.foldl (R15ThinPairs.groups p) step out)
  funext acc g
  exact group_eq batch m n p A B r acc g"""

assert SRC.count(OLD) == 1 and SRC.count(OLD_EQ) == 1
text = SRC.replace(OLD, NEW).replace(OLD_EQ, NEW_EQ)
data = text.encode("utf-8")
sha = hashlib.sha256(data).hexdigest()
out = TRACK / "candidates/f01-deepseek-loopboth1"
out.mkdir(parents=True, exist_ok=True)
(out / "Kernel.lean").write_bytes(data)
manifest = {
    "candidate": "f01-deepseek-loopboth1",
    "candidate_file": "Kernel.lean",
    "candidate_sha256": sha,
    "candidate_bytes": len(data),
    "created_at_utc": datetime.datetime.now(datetime.timezone.utc).isoformat(),
    "parent": "competitions/floatlib/candidates/f01-r15-dev-packed-b2-1/Kernel.lean",
    "parent_sha256": "622d8394a7127e93dcaf992c62c6dfcff7208d212738409a5e34525dfafd1a58",
    "mechanism": "Combines the DirectContinuous emitLoop patch and the R15PackedB2 rowLoop patch; both replace per-row capturing closures with first-order recursion. Arithmetic/order identical.",
    "proof": "Union of the two patches' proof lemmas (emitLoop_eq/row_emit_eq and rowLoop_eq/row_foldl).",
    "validation_mode": "statement-only",
    "proof_status": "STATIC_PATCH_NOT_COMPILED",
    "performance": "NOT_RUN",
    "formal_submission": "NOT_SUBMITTED",
}
(out / "manifest.json").write_text(json.dumps(manifest, ensure_ascii=False, indent=2) + "\n", encoding="utf-8")
print("combined", sha, len(data))
