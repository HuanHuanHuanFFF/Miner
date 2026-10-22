"""Build a two-step machine-word loop, retaining ordered rounding in each lane."""
from pathlib import Path
import hashlib,json
ROOT=Path(__file__).resolve().parents[1];OUT=Path(__file__).resolve().parent
raw=(ROOT/'f01-d3-final-package/Kernel.lean').read_bytes()
assert hashlib.sha256(raw).hexdigest()=='6744be2bd784bea7a7e347d68f813bc865d2d18abab87f19fa37aec8a8c2c1f7'
s=raw.decode()
args=' '.join('s'+str(i) for i in range(8))
params='(s0 s1 s2 s3 s4 s5 s6 s7 : Float32)'
updates1=' '.join(f'(s{i} + a * v.s{i})' for i in range(8))
updates2=' '.join(f'((s{i} + a * v.s{i}) + a1 * v1.s{i})' for i in range(8))
tuple0='\u27e8'+', '.join('s'+str(i) for i in range(8))+'\u27e9'
tuple1='\u27e8'+', '.join(f's{i} + a * v.s{i}' for i in range(8))+'\u27e9'
common='''{n : Nat} (count baseA : USize) (A : Array Float32) (B : Vector F8 n)
    (hn : count.toNat = n)
    (hA : baseA.toNat + (count.toNat - 1) < A.size)
    (hAS : A.size < USize.size)
    (k : USize) '''+params
extra='''namespace Unroll2

theorem two_decreases {n k : USize} (hk : k < n) (hk1 : k + 1 < n) :
    n.toNat - (k + 1 + 1).toNat < n.toNat - k.toNat := by
  rw [stepNat hk1, stepNat hk]
  have hkn := USize.lt_iff_toNat_lt.mp hk
  omega

def loop '''+common+''' : F8 :=
  if hk : k < count then
    have hkn : k.toNat < n := by rw [\u2190 hn]; exact USize.lt_iff_toNat_lt.mp hk
    have ha := boundA baseA.toNat count.toNat k.toNat A.size hA
      (USize.lt_iff_toNat_lt.mp hk)
    let a := A.uget (baseA + k)
      (by rw [addNat baseA k (Nat.lt_trans ha hAS)]; exact ha)
    let v := B.toArray.uget k (by simpa only [B.size_toArray] using hkn)
    if hk1 : k + 1 < count then
      have hkn1 : (k + 1).toNat < n := by rw [\u2190 hn]; exact USize.lt_iff_toNat_lt.mp hk1
      have ha1 := boundA baseA.toNat count.toNat (k + 1).toNat A.size hA
        (USize.lt_iff_toNat_lt.mp hk1)
      let a1 := A.uget (baseA + (k + 1))
        (by rw [addNat baseA (k + 1) (Nat.lt_trans ha1 hAS)]; exact ha1)
      let v1 := B.toArray.uget (k + 1) (by simpa only [B.size_toArray] using hkn1)
      loop count baseA A B hn hA hAS (k + 1 + 1)
        '''+updates2+'''
    else '''+tuple1+'''
  else '''+tuple0+'''
termination_by count.toNat - k.toNat
decreasing_by exact two_decreases (by assumption) (by assumption)

theorem loop_eq_base '''+common+''' :
    loop count baseA A B hn hA hAS k '''+args+''' =
      Packed8Index.loop count baseA A B hn hA hAS k '''+args+''' := by
  rw [loop]
  split
  \u00b7 rename_i hk
    rw [Packed8Index.loop, dif_pos hk]
    dsimp only
    split
    \u00b7 rename_i hk1
      rw [Packed8Index.loop, dif_pos hk1]
      dsimp only
      rw [loop_eq_base]
    \u00b7 rename_i hk1
      rw [Packed8Index.loop, dif_neg hk1]
  \u00b7 rename_i hk
    rw [Packed8Index.loop, dif_neg hk]
termination_by count.toNat - k.toNat
decreasing_by exact two_decreases (by assumption) (by assumption)

end Unroll2

'''
pos=s.index('@[inline] def within (n baseA : Nat)')
s=s[:pos]+extra+s[pos:]
pos=s.index('@[inline] def within (n baseA : Nat)');end=s.index('theorem within_eq',pos)
s=s[:pos]+s[pos:end].replace('  loop (USize.ofNat n)','  Unroll2.loop (USize.ofNat n)')+s[end:]
s=s.replace('simp only [within, loop_eq,','simp only [within, Unroll2.loop_eq_base, loop_eq,',1)
data=s.encode();(OUT/'Kernel.lean').write_bytes(data)
m=dict(candidate=OUT.name,candidate_file='Kernel.lean',candidate_sha256=hashlib.sha256(data).hexdigest(),candidate_bytes=len(data),parent='f01-d3-final-package',validation_mode='full-gate',proof_status='NOT_RUN',mechanism='Two ordered k steps per eight-lane USize recursive loop; exact scalar rounding and unpaired tail retained, equality proved to the existing loop.')
(OUT/'manifest.json').write_text(json.dumps(m,indent=2)+'\n');print(json.dumps(m))
