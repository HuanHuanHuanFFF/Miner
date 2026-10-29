"""Four diagnostic-driven repairs; freezes the original fragment and candidates."""
from pathlib import Path
from datetime import datetime, timezone
import hashlib,json
HERE=Path(__file__).resolve().parent
sha=lambda b:hashlib.sha256(b).hexdigest()
p=HERE/'NativeSumEnclosure.lean.inc'
old=p.read_bytes()
assert sha(old)=='99d69cc98d96662d2daab76a907af18fdd263136881d62f8947d76795b3bee73'
s=old.decode()
changes=[('native-add descriptor', '''  simpa only [ExecFloat.Binary.toModel_ofFloat] using
    ExecFloat.Binary.toModel_ofFloat_add_of_isFinite x y hx hy''', '''  change Model.ofFloatModel (Float.Model.add x.toModel y.toModel) = _
  rw [Float.Model.add, Model.ofFloatModel_pack]
  have h := Model.add_eq_ofModel_add_of_isFinite (fmt := FloatFormat.binary64)
    (by decide) (Model.ofFloatModel x.toModel) (Model.ofFloatModel y.toModel)
    (by simpa only [Model.toModel_ofFloatModel, Float.isFinite,
      Float.Model.isFinite] using hx)
    (by simpa only [Model.toModel_ofFloatModel, Float.isFinite,
      Float.Model.isFinite] using hy)
  rw [Model.toModel_ofFloatModel, Model.toModel_ofFloatModel] at h
  exact h.symm'''),
('FLT record projections', '''    refine ⟨by norm_num, ⟨(j : Int), k⟩, ?_, ?_, by omega⟩
    · simp only [FloatLib.Floats.Formats.Flocq.toReal, Int.cast_natCast]
      rfl
    · change j < 2 ^ 53
      exact lt_of_le_of_lt hj (by decide)''', '''    refine ⟨by norm_num, ⟨(j : Int), k⟩, ?_, ?_, ?_⟩
    · change (j : ℝ) * p2 k = (j : ℝ) * bpow FloatLib.Numerics.binaryRadix k
      rfl
    · change j < 2 ^ 53
      exact lt_of_le_of_lt hj (by norm_num)
    · change (-1074 : Int) ≤ k
      omega'''),
('no-progress convert/simp chain', '''    · convert hout.2.1 using 1 <;> simp only [List.length_cons] <;> push_cast <;> ring''', '''    · simpa only [loop, List.length_cons, Nat.add_assoc, Nat.add_comm, Nat.add_left_comm]
        using hout.2.1'''),
('actual wrapper explicit native alias', '''    simpa only [ExecFloat.Binary.toModel_ofFloat, rval] using hxs
  simpa only [ExecFloat.Binary.toModel_ofFloat, rval, exactSum] using''', '''    simpa only [ExecFloat.Binary.toModel_ofFloat, rval, native] using hxs
  simpa only [ExecFloat.Binary.toModel_ofFloat, rval, native, exactSum] using''')]
for label,a,b in changes:
    assert s.count(a)==1,(label,s.count(a))
    s=s.replace(a,b)
new=s.encode()
out=HERE/'NativeSumEnclosure2.lean.inc'
out.write_bytes(new)
assert p.read_bytes()==old
receipt=dict(created_at_utc=datetime.now(timezone.utc).isoformat(),phase_first_utc='2026-10-29T00:05:59Z',
    old_sha256=sha(old),new_sha256=sha(new),new_bytes=len(new),path=str(out),
    compiler_run='40790240320',frozen_candidate='f01-r24-dev-portable-island3',
    diagnostic_lines=[1853,1892,1990,2039,2040],changes=[c[0] for c in changes],
    roots=['Submission.R24RepresentationSum.'+n for n in ['native_add_finite_real','round_grid',
        'round_error_power','loop_invariant','sum_enclosure','actual_sum_enclosure']],
    old_source_unchanged=True,Lean='NOT_RUN_NEW_REVISION',CI='D_OWNS_NO_NEW_QUEUE_FROM_A',
    shared_deadline_utc='2026-10-29T03:38:56Z',tokens='UNKNOWN',cached_input_tokens='UNKNOWN',
    paused_work='exact128 chain2 b2f408 source remains NOT_RUN_NOT_QUEUED; phase23:55:43 to00:05:29 then compiler repair priority')
(HERE/'sum2-repair-receipt.json').write_text(json.dumps(receipt,indent=2)+'\n',encoding='utf-8')
print(json.dumps(receipt))
