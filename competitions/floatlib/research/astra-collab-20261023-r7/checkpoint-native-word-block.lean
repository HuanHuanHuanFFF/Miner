/- Prepared concrete raw-Vector adapter for the checkpoint route.
   Intended after Submission.NativeDecodeSumWord, before the final public sum.
   No candidate/Lean acceptance is claimed for this draft until the actual block
   specification is integrated and the fixed toolchain checks it. -/
namespace Submission.R7CheckpointWord

open FloatLib.Floats Competition

/-- A bounded interval of the existing fast, proven raw-word decoder. -/
def natChunk {n : Nat} (x : Vector Binary32 n) (stop : Nat)
    (hs : stop ≤ n) (k : Nat) (acc : Float32) : Float32 :=
  if hk : k < stop then
    natChunk x stop hs (k + 1)
      (acc + NativeDecodeSum.decode (x.get ⟨k, by omega⟩))
  else acc
termination_by stop - k

/-- Native word indexing with an erased proof that every accessed raw element exists. -/
def wordChunk {n : Nat} (x : Vector Binary32 n) (stop : USize)
    (hs : stop.toNat ≤ n) (k : USize) (acc : Float32) : Float32 :=
  if hk : k < stop then
    have hkn : k.toNat < n := by
      have hks := USize.lt_iff_toNat_lt.mp hk
      omega
    let value := x.toArray.uget k (by simpa only [x.size_toArray] using hkn)
    wordChunk x stop hs (k + 1) (acc + NativeDecodeSum.decode value)
  else acc
termination_by stop.toNat - k.toNat
decreasing_by exact Packed10Index.next_decreases (by assumption)

theorem wordChunk_eq {n : Nat} (x : Vector Binary32 n) (stop : USize)
    (hs : stop.toNat ≤ n) (k : USize) (acc : Float32) :
    wordChunk x stop hs k acc = natChunk x stop.toNat hs k.toNat acc := by
  rw [wordChunk]
  split
  · rename_i hk
    have hks : k.toNat < stop.toNat := USize.lt_iff_toNat_lt.mp hk
    rw [natChunk, dif_pos hks]
    dsimp only
    rw [wordChunk_eq, Packed10Index.stepNat hk]
    rfl
  · rename_i hk
    have hks : ¬ k.toNat < stop.toNat := by
      simpa only [USize.lt_iff_toNat_lt] using hk
    rw [natChunk, dif_neg hks]
termination_by stop.toNat - k.toNat
decreasing_by exact Packed10Index.next_decreases (by assumption)

/-- An interval wrapper retains the Nat route when its stop cannot fit a native index.
start≤stop is a proof parameter: this prevents a wrapped start silently accessing data. -/
def chunk {n : Nat} (x : Vector Binary32 n) (start stop : Nat)
    (hs : stop ≤ n) (hstart : start ≤ stop) (acc : Float32) : Float32 :=
  if hw : stop < USize.size then
    wordChunk x (USize.ofNat stop)
      (by rw [USize.toNat_ofNat_of_lt' hw]; exact hs) (USize.ofNat start) acc
  else natChunk x stop hs start acc

theorem chunk_eq {n : Nat} (x : Vector Binary32 n) (start stop : Nat)
    (hs : stop ≤ n) (hstart : start ≤ stop) (acc : Float32) :
    chunk x start stop hs hstart acc = natChunk x stop hs start acc := by
  unfold chunk
  split
  · rename_i hw
    have hstartw : start < USize.size := by omega
    rw [wordChunk_eq, USize.toNat_ofNat_of_lt' hw, USize.toNat_ofNat_of_lt' hstartw]
  · rfl

end Submission.R7CheckpointWord
