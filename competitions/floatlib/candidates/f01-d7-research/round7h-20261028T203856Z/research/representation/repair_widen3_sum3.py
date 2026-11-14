"""Expression/API repairs from island5; no resource increase or candidate/CI mutation."""
from pathlib import Path
from datetime import datetime,timezone
import hashlib,json
HERE=Path(__file__).resolve().parent
ROOT=next(p for p in HERE.parents if (p/'AGENTS.md').is_file())
C=ROOT/'competitions/floatlib/candidates'
sha=lambda b:hashlib.sha256(b).hexdigest()
wp=C/'f01-d7-research/round3h30m-20261028T230130Z/research/representation/WidenNormal.lean.inc'
sp=HERE/'NativeSumEnclosure2.lean.inc'
wraw,sraw=wp.read_bytes(),sp.read_bytes()
assert sha(wraw)=='5e09ce0e1222074c48896394285796b276faf13b7c686c2e2eaa67548cf97fa3'
assert sha(sraw)=='674492a63911c717cb4e55778681eb82f020ee14c6429b8a76ccfc47181cb76e'
w,s=wraw.decode(),sraw.decode()
old='''  have hF : wordFrac u * 536870912 < 2 ^ 52 := by
    change wordFrac u * 536870912 < 4503599627370496
    omega'''
new='''  have hF : wordFrac u * 536870912 < 2 ^ 52 := by
    calc
      _ < (2 ^ 23) * 536870912 := Nat.mul_lt_mul_of_pos_right hf (by norm_num)
      _ = 2 ^ 52 := by norm_num'''
assert w.count(old)==1
w=w.replace(old,new)
a=w.index('theorem shift29_toReal')
b=w.index('theorem native_value',a)
w=w[:a]+'''theorem shift29_toReal (s : Bool) (m : Nat) (e : Int) :
    (FloatLib.Numerics.Dyadic.mk s (m * 536870912) (e - 29)).toReal =
      (FloatLib.Numerics.Dyadic.mk s m e).toReal := by
  have hp : (536870912 : ℝ) * (2 : ℝ) ^ (e - 29) = (2 : ℝ) ^ e := by
    have hc : (536870912 : ℝ) = (2 : ℝ) ^ (29 : Int) := by norm_num
    rw [hc, ← zpow_add₀ (by norm_num : (2 : ℝ) ≠ 0)]
    congr 1
    omega
  cases s with
  | false =>
    simpa only [FloatLib.Numerics.Dyadic.toReal, FloatLib.Numerics.Dyadic.signedSignificand,
      Int.cast_natCast, Nat.cast_mul, mul_assoc] using congrArg (fun x : ℝ => (m : ℝ) * x) hp
  | true =>
    simpa only [FloatLib.Numerics.Dyadic.toReal, FloatLib.Numerics.Dyadic.signedSignificand,
      Int.cast_neg, Int.cast_natCast, Nat.cast_mul, neg_mul, mul_assoc] using
      congrArg (fun x : ℝ => -(m : ℝ) * x) hp

'''+w[b:]
a=s.index('theorem round_grid')
b=s.index('/- This is obtained',a)
s=s[:a]+'''theorem round_grid (j : Nat) (k : Int) (hj : j ≤ 2 ^ 30) (hk : -250 ≤ k) :
    Model.roundAt FloatFormat.binary64 ((j : ℝ) * p2 k) = (j : ℝ) * p2 k := by
  let d : FloatLib.Numerics.Dyadic := ⟨false, j, k⟩
  have hs : d.significand < 2 ^ (FloatFormat.binary64.fracWidth + 1) := by
    change j < 2 ^ 53
    exact lt_of_le_of_lt hj (by norm_num)
  have he : FloatFormat.binary64.minSubnormalExponent ≤ d.exponent := by
    change (-1074 : Int) ≤ k
    omega
  have hg := Model.Dyadic.genericFormat_of_significand_lt FloatFormat.binary64 d hs he
  have hv : d.toReal = (j : ℝ) * p2 k := by
    change (FloatLib.Numerics.Dyadic.mk false j k).toReal = _
    rw [FloatLib.Numerics.Dyadic.toReal_mk_false]
    rfl
  rw [hv] at hg
  exact round_preserves_generic nearestEven _ hg

'''+s[b:]
a=s.index('theorem actual_sum_enclosure')
s=s[:a]+'end Submission.R24RepresentationSum\n'
outs=[(HERE/'WidenNormal3.lean.inc',w.encode()),(HERE/'NativeSumEnclosure3.lean.inc',s.encode())]
for p,blob in outs:p.write_bytes(blob)
assert wp.read_bytes()==wraw and sp.read_bytes()==sraw
rootsW=['Submission.R24RepresentationWiden.'+n for n in
    ['normal_decode','native_model','native_finite','actual_native_value','signed_zero_bits']]
rootsS=['Submission.R24RepresentationSum.'+n for n in
    ['native_add_finite_real','round_grid','round_error_power','loop_invariant','sum_enclosure']]
r=dict(observed_at_utc=datetime.now(timezone.utc).isoformat(),phase_first_utc='2026-10-29T00:47:22Z',
    compiler_run='40793795026',failed_island_sha256='c7b7a4139c7de06bcb56464ff0d667fa95d04b8c321b76e06a91fd7c54a0082d',
    log_sha256='b6a17252e1aaa99a3c225eac26795bb301df7d920f5b5b5a6f273ab6a0853919',
    inputs=[dict(path=str(wp),sha256=sha(wraw)),dict(path=str(sp),sha256=sha(sraw))],
    outputs=[dict(path=str(p),sha256=sha(blob),bytes=len(blob)) for p,blob in outs],
    required_roots_widen=rootsW,required_roots_sum=rootsS,
    removed_roots=['Submission.R24RepresentationSum.actual_sum_enclosure'],
    changes=['1546 large-coefficient omega replaced by Nat.mul_lt_mul_of_pos_right',
      '1700/1703 signedSignificand shift helper/cast unification replaced by two sign cases and a scalar zpow identity',
      '1998 FLTFormat construction/instance conversion replaced by existing Dyadic.genericFormat_of_significand_lt',
      '2152/2153 redundant Binary presentation wrapper removed; actual native sum_enclosure unchanged'],
    status='NEW_FRAGMENTS_NOT_RUN',no_resource_increase=True,no_local_Lean=True,no_CI=True,
    accepted_core_boundary='Reported core13/049b01fa PASS applies only to that exact core; no acceptance inherited by these fragments.',
    old_sources_unchanged=True,shared_deadline_utc='2026-10-29T03:38:56Z',tokens='UNKNOWN',cached_input_tokens='UNKNOWN')
(HERE/'widen3-sum3-repair-receipt.json').write_text(json.dumps(r,indent=2)+'\n',encoding='utf-8')
print(json.dumps(r))
