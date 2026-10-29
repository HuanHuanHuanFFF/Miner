"""Explicit Int.ofNat constructor rewrite, matching fixed Mathlib's own cast proof."""
from pathlib import Path
from datetime import datetime,timezone
import hashlib,json
HERE=Path(__file__).resolve().parent
sha=lambda b:hashlib.sha256(b).hexdigest()
old=(HERE/'WidenNormal4.lean.inc').read_bytes()
assert sha(old)=='abe567751440563b142cf1b479681f81f8afe5b0ca9bd3038efcbde5e1fb4c5d'
s=old.decode()
a='Bool.false_eq_true, ite_false, ite_true, Int.cast_natCast, Nat.cast_mul, mul_assoc]'
b='Bool.false_eq_true, ite_false, ite_true, Int.ofNat_eq_natCast, Int.cast_natCast, Nat.cast_mul, mul_assoc]'
c='Bool.false_eq_true, ite_false, ite_true, Int.cast_neg, Int.cast_natCast,'
d='Bool.false_eq_true, ite_false, ite_true, Int.cast_neg, Int.ofNat_eq_natCast, Int.cast_natCast,'
assert s.count(a)==1 and s.count(c)==1
s=s.replace(a,b).replace(c,d)
new=s.encode()
(HERE/'WidenNormal5.lean.inc').write_bytes(new)
assert (HERE/'WidenNormal4.lean.inc').read_bytes()==old
r=dict(observed_at_utc=datetime.now(timezone.utc).isoformat(),phase_first_utc='2026-10-29T02:36:30Z',
    compiler_run='40804860824',old_sha256=sha(old),new_path='WidenNormal5.lean.inc',new_sha256=sha(new),new_bytes=len(new),
    changes=['Add Int.ofNat_eq_natCast before Int.cast_natCast in the two existing sign branches; no other proof/runtime change.'],
    source_validation=dict(mathlib_ref='5ed2965256430c3649e86755f9576b54eca72435',
      basic_blob='6598b95f61102f109dee2ef7b5697d7d59a09f9e',
      lemmas_blob='e76e5b8ad639472811bee0299f2ece967c6143bb',
      exact_fixed_usage='Mathlib/Data/Int/Cast/Lemmas.lean:60 rewrites ofNat_eq_natCast then Int.cast_natCast inside namespace Int.',
      not_used='Int.cast_ofNat is a numeral lemma requiring n.AtLeastTwo, not the generic constructor bridge.'),
    roots=['Submission.R24RepresentationWiden.'+n for n in
      ['normal_decode','native_model','native_finite','actual_native_value','signed_zero_bits']],
    status='NEW_FRAGMENT_NOT_RUN',old_source_unchanged=True,no_resource_change=True,no_local_Lean=True,no_CI=True,
    shared_deadline_utc='2026-10-29T03:38:56Z',tokens='UNKNOWN',cached_input_tokens='UNKNOWN')
(HERE/'widen5-repair-receipt.json').write_text(json.dumps(r,indent=2)+'\n',encoding='utf-8')
print(json.dumps(r))
