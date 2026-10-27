"""Reuse the historical Nat attempt, then add a bounded grouped-bias word bridge; no compilation."""
from pathlib import Path
from datetime import datetime,timezone
import hashlib,json
H=Path(__file__).resolve().parent
R=next(p for p in H.parents if (p/'competitions/floatlib/pins.json').is_file())
src=R/'competitions/floatlib/candidates/f01-d7-research/round8h-20261024T190259Z/astra-biased-rne4-quotient.lean'
raw=src.read_bytes();assert hashlib.sha256(raw).hexdigest()=='f30f16a715db5773356781f4f5544d5cbb5afcbf64fd28596a898d50b86661c7'
s=raw.decode();lo=s.index('private theorem quotient_bias');hi=s.index('@[inline] def biased')
nat=s[lo:hi]
new='''namespace BranchlessRNESeed
open FloatLib.Numerics

'''+nat+'''
theorem nat_grouped_bias (p t : Nat) (ht : t=23 ∨ t=24) :
    roundShiftRightEven p t =
      (p+(2^(t-1)-1)+(p >>> t)%2) >>> t := by
  have hpos := Nat.two_pow_pos (t-1)
  have he : p+2^(t-1)-1 = p+(2^(t-1)-1) := by omega
  simpa only [he] using nat_bias p t ht

@[inline] def grouped (p t : UInt64) : UInt64 :=
  (p+(((1 : UInt64) <<< (t-1))-1)+((p >>> t) &&& 1)) >>> t

theorem word_grouped (p t : UInt64) (hp : p.toNat ≤ 281474943156225)
    (ht : t=23 ∨ t=24) :
    grouped p t = FixedWord.roundShiftRightEven p t.toNat := by
  let half : UInt64 := (1 : UInt64) <<< (t-1)
  let bias : UInt64 := half-1
  let parity : UInt64 := (p >>> t) &&& 1
  have htNat : t.toNat=23 ∨ t.toNat=24 := by
    rcases ht with rfl | rfl <;> norm_num
  have ht64 : t.toNat < 64 := by omega
  have hhalf : half.toNat=2^(t.toNat-1) := by
    rcases ht with rfl | rfl <;> decide
  have hb : 4194304 ≤ half.toNat ∧ half.toNat ≤ 8388608 := by
    rcases ht with rfl | rfl <;> decide
  have hone : (1 : UInt64) ≤ half := by
    rw [UInt64.le_iff_toNat_le]
    change 1 ≤ half.toNat
    omega
  have hminus : bias.toNat=half.toNat-1 := by
    dsimp only [bias]
    rw [UInt64.toNat_sub_of_le _ _ hone]
    rfl
  have hshift : (p >>> t).toNat=p.toNat >>> t.toNat := by
    rw [UInt64.toNat_shiftRight,Nat.mod_eq_of_lt ht64]
  have hparity : parity.toNat=(p.toNat >>> t.toNat)%2 := by
    dsimp only [parity]
    rw [UInt64.toNat_and,hshift]
    change (p.toNat >>> t.toNat) &&& (2^1-1) = (p.toNat >>> t.toNat)%2
    exact Nat.and_two_pow_sub_one_eq_mod _ 1
  have hparityBound : parity.toNat ≤ 1 := by rw [hparity]; omega
  have hplus : (p+bias).toNat=p.toNat+(half.toNat-1) := by
    rw [UInt64.toNat_add,hminus,Nat.mod_eq_of_lt (by omega)]
  have hsum : (p+bias+parity).toNat=p.toNat+(half.toNat-1)+parity.toNat := by
    rw [UInt64.toNat_add,hplus,Nat.mod_eq_of_lt (by omega)]
  apply UInt64.toNat.inj
  change ((p+bias+parity) >>> t).toNat = (FixedWord.roundShiftRightEven p t.toNat).toNat
  rw [UInt64.toNat_shiftRight,Nat.mod_eq_of_lt ht64,hsum,
    FixedWord.roundShiftRightEven_toNat,hhalf,hparity]
  exact (nat_grouped_bias p.toNat t.toNat htNat).symm

theorem grouped_eq_existing_rse (p t : UInt64) (hp : p.toNat ≤ 281474943156225)
    (ht : t=23 ∨ t=24) :
    grouped p t = Submission.FastMul.rse p t := by
  calc
    _ = FixedWord.roundShiftRightEven p t.toNat := word_grouped p t hp ht
    _ = Submission.FastMul.rseAny p t := (Submission.FastMul.rseAny_eq p t).symm
    _ = Submission.FastMul.rse p t := by rcases ht with rfl | rfl <;> rfl

end BranchlessRNESeed
'''
out=H/'BranchlessRNE-seed.lean.inc';out.write_bytes(new.replace('\r\n','\n').encode())
j=dict(created_utc=datetime.now(timezone.utc).isoformat(),state='HISTORICAL_NAT_REUSE_AND_BOUNDED_WORD_PROOF_ATTEMPT_NOT_COMPILED',
 source=dict(path=str(src.relative_to(R)),sha256=hashlib.sha256(raw).hexdigest()),
 reused_nat_chars=[lo,hi],seed=dict(path=out.name,bytes=out.stat().st_size,sha256=hashlib.sha256(out.read_bytes()).hexdigest()),
 novelty='No new formula; Nat proof is the exact existing R14 quotient attempt. New grouping and product-specific upper bound are a small reusable bridge only.',
 dependency='Append fragment after exact B2 for Submission.FastMul.rse/rseAny_eq; no complete candidate generated',
 history='Old direct-Nat and quotient variants were actually tried and terminated without Lean goal output; cause UNKNOWN, never a verified theorem or speed result',
 CI=False,Git=False,local_Lean=False)
(H/'seed-manifest.json').write_bytes((json.dumps(j,indent=2)+'\n').encode())
print(json.dumps(j['seed']))
