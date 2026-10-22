"""Replace the inline-decoder ordered sum's Nat loop with proven USize indexing."""
from pathlib import Path
import hashlib,json
ROOT=Path(__file__).resolve().parents[1];OUT=Path(__file__).resolve().parent
raw=(ROOT/'f01-d3-final-package/Kernel.lean').read_bytes()
assert hashlib.sha256(raw).hexdigest()=='6744be2bd784bea7a7e347d68f813bc865d2d18abab87f19fa37aec8a8c2c1f7'
s=raw.decode()
extra='''namespace Submission.NativeDecodeSumWord

open FloatLib.Floats Competition

def loop {n : Nat} (x : Vector Binary32 n) (count : USize)
    (hn : count.toNat = n) (k : USize) (acc : Float32) : Float32 :=
  if hk : k < count then
    have hkn : k.toNat < n := by rw [\u2190 hn]; exact USize.lt_iff_toNat_lt.mp hk
    let value := x.toArray.uget k (by simpa only [x.size_toArray] using hkn)
    loop x count hn (k + 1) (acc + NativeDecodeSum.decode value)
  else acc
termination_by count.toNat - k.toNat
decreasing_by exact Packed8Index.next_decreases (by assumption)

theorem loop_eq {n : Nat} (x : Vector Binary32 n) (count : USize)
    (hn : count.toNat = n) (k : USize) (acc : Float32) :
    loop x count hn k acc = NativeDecodeSum.loop x k.toNat acc := by
  rw [loop]
  split
  \u00b7 rename_i hk
    have hkn : k.toNat < n := by rw [\u2190 hn]; exact USize.lt_iff_toNat_lt.mp hk
    rw [NativeDecodeSum.loop, dif_pos hkn]
    dsimp only
    rw [loop_eq, Packed8Index.stepNat hk]
    rfl
  \u00b7 rename_i hk
    have hkn : \u00ac k.toNat < n := by
      rw [\u2190 hn]
      simpa only [USize.lt_iff_toNat_lt] using hk
    rw [NativeDecodeSum.loop, dif_neg hkn]
termination_by count.toNat - k.toNat
decreasing_by exact Packed8Index.next_decreases (by assumption)

@[inline] def run {n : Nat} (x : Vector Binary32 n) : Float32 :=
  if hn : n < USize.size then
    loop x (USize.ofNat n) (USize.toNat_ofNat_of_lt' hn) 0 (Float32.ofBits 0)
  else NativeDecodeSum.loop x 0 (Float32.ofBits 0)

theorem run_eq {n : Nat} (x : Vector Binary32 n) :
    run x = NativeDecodeSum.loop x 0 (Float32.ofBits 0) := by
  unfold run
  split
  \u00b7 rw [loop_eq, USize.toNat_zero]
  \u00b7 rfl

end Submission.NativeDecodeSumWord

'''
marker='namespace Submission\n\nopen FloatLib.Floats Competition\n\ndef sum'
pos=s.index(marker);s=s[:pos]+extra+s[pos:]
s=s.replace('let result := NativeDecodeSum.loop x 0 (Float32.ofBits 0)','let result := NativeDecodeSumWord.run x',1)
s=s.replace('rw [NativeDecodeSum.loop_eq]','rw [NativeDecodeSumWord.run_eq, NativeDecodeSum.loop_eq]',1)
data=s.encode();(OUT/'Kernel.lean').write_bytes(data)
m=dict(candidate=OUT.name,candidate_file='Kernel.lean',candidate_sha256=hashlib.sha256(data).hexdigest(),candidate_bytes=len(data),parent='f01-d3-final-package',validation_mode='full-gate',proof_status='NOT_RUN',mechanism='Machine-word count/index and proven uget for ordered inline-decoder sum, one length guard, same finite and exact fallback; other operations unchanged.')
(OUT/'manifest.json').write_text(json.dumps(m,indent=2)+'\n');print(json.dumps(m))
