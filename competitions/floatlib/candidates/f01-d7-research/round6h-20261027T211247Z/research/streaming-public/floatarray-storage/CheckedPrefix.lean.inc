/- Proof-only append protocol for frozen f5a6. NOT_RUN.
   Push/get transport follows checked98cef; native-value check is exact fb7d.
   No recursive builder, loop, or public bmm theorem is claimed here. -/
namespace Submission.R22FloatArrayPrefix
open FloatLib.Floats Competition
open R22FloatArrayB2 (push_size)

def read (out : FloatArray) (i : Nat) : Float32 :=
  if hi : i < out.size then (out.get i hi).toFloat32 else Packed10.zero32

def Prefix (point : Nat → Float32) (count : Nat) (out : FloatArray) : Prop :=
  out.size = count ∧ ∀ i, i < count → read out i = point i

private theorem get_push_lt (out : FloatArray) (d : Float) (i : Nat)
    (hi : i < out.size) :
    (out.push d).get i (by rw [push_size]; omega) = out.get i hi := by
  cases out with
  | mk ds =>
    simpa only [FloatArray.push, FloatArray.get, FloatArray.size] using
      (Array.getElem_push_lt (xs := ds) (x := d) hi)

private theorem get_push_eq (out : FloatArray) (d : Float) :
    (out.push d).get out.size (by rw [push_size]; omega) = d := by
  cases out with
  | mk ds =>
    simpa only [FloatArray.push, FloatArray.get, FloatArray.size] using
      (Array.getElem_push_eq (xs := ds) (x := d))

private theorem read_push_lt (out : FloatArray) (d : Float) (i : Nat)
    (hi : i < out.size) : read (out.push d) i = read out i := by
  have hp : i < (out.push d).size := by rw [push_size]; omega
  simp only [read, dif_pos hi, dif_pos hp]
  exact congrArg Float.toFloat32 (get_push_lt out d i hi)

private theorem read_push_eq (out : FloatArray) (d : Float) :
    read (out.push d) out.size = d.toFloat32 := by
  have hp : out.size < (out.push d).size := by rw [push_size]; omega
  simp only [read, dif_pos hp]
  exact congrArg Float.toFloat32 (get_push_eq out d)

theorem prefix_empty (point : Nat → Float32) (capacity : Nat) :
    Prefix point 0 (FloatArray.emptyWithCapacity capacity) := by
  refine ⟨rfl, ?_⟩
  intro i hi
  omega

theorem prefix_push (point : Nat → Float32) (k : Nat) (out : FloatArray)
    (d : Float) (hpre : Prefix point k out)
    (hc : R22FloatArrayBridgeReview.checkNative (point k) d = true) :
    Prefix point (k + 1) (out.push d) := by
  refine ⟨by rw [push_size, hpre.1], ?_⟩
  intro i hi
  by_cases hik : i < k
  · rw [read_push_lt out d i (by simpa only [hpre.1] using hik)]
    exact hpre.2 i hik
  · have he : i = k := by omega
    subst i
    have hr : read (out.push d) k = d.toFloat32 := by
      simpa only [hpre.1] using read_push_eq out d
    exact hr.trans (R22FloatArrayBridgeReview.checked_native (point k) d hc)

theorem prefix_get (point : Nat → Float32) (k : Nat) (out : FloatArray)
    (hpre : Prefix point k out) (i : Nat) (hi : i < out.size) :
    (out.get i hi).toFloat32 = point i := by
  have h := hpre.2 i (by simpa only [hpre.1] using hi)
  simpa only [read, dif_pos hi] using h

def point (base p : Nat) (B : Array Binary32) (i : Nat) : Float32 :=
  ExecFloat.Binary.toFloat32 (B.getD (base + i % 2 + (i / 2) * p) posZero)

private theorem point_left (base p k : Nat) (B : Array Binary32) :
    point base p B (2 * k) =
      ExecFloat.Binary.toFloat32 (B.getD (base + k * p) posZero) := by
  have hd : 2 * k / 2 = k := by omega
  have hm : 2 * k % 2 = 0 := by omega
  simp only [point, hd, hm, Nat.add_zero]

private theorem point_right (base p k : Nat) (B : Array Binary32) :
    point base p B (2 * k + 1) =
      ExecFloat.Binary.toFloat32 (B.getD (base + 1 + k * p) posZero) := by
  have hd : (2 * k + 1) / 2 = k := by omega
  have hm : (2 * k + 1) % 2 = 1 := by omega
  simp only [point, hd, hm]

theorem prefix_actual_pair (base p k : Nat) (B : Array Binary32)
    (out : FloatArray) (d0 d1 : Float)
    (hpre : Prefix (point base p B) (2 * k) out)
    (h0 : R22FloatArrayBridgeReview.checkNative
      (ExecFloat.Binary.toFloat32 (B.getD (base + k * p) posZero)) d0 = true)
    (h1 : R22FloatArrayBridgeReview.checkNative
      (ExecFloat.Binary.toFloat32 (B.getD (base + 1 + k * p) posZero)) d1 = true) :
    Prefix (point base p B) (2 * (k + 1)) ((out.push d0).push d1) := by
  have hc0 : R22FloatArrayBridgeReview.checkNative (point base p B (2 * k)) d0 = true := by
    simpa only [point_left] using h0
  have hc1 : R22FloatArrayBridgeReview.checkNative (point base p B (2 * k + 1)) d1 = true := by
    simpa only [point_right] using h1
  have h := prefix_push (point base p B) (2 * k + 1) (out.push d0) d1
    (prefix_push (point base p B) (2 * k) out d0 hpre hc0) hc1
  have he : 2 * k + 1 + 1 = 2 * (k + 1) := by omega
  simpa only [he] using h

end Submission.R22FloatArrayPrefix
