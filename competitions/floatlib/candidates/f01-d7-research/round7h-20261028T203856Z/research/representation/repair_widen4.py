"""Two explicit Bool-branch simplifications from the island6 diagnostic."""
from pathlib import Path
from datetime import datetime,timezone
import hashlib,json
HERE=Path(__file__).resolve().parent
sha=lambda b:hashlib.sha256(b).hexdigest()
old=(HERE/'WidenNormal3.lean.inc').read_bytes()
assert sha(old)=='9a1e894c10c9e8bcc160133d1d2aab084c358a24a04a5f78e11361ae0be8a517'
s=old.decode()
a='''      Int.cast_natCast, Nat.cast_mul, mul_assoc] using congrArg (fun x : ℝ => (m : ℝ) * x) hp'''
b='''      Bool.false_eq_true, ite_false, ite_true, Int.cast_natCast, Nat.cast_mul, mul_assoc] using
      congrArg (fun x : ℝ => (m : ℝ) * x) hp'''
c='''      Int.cast_neg, Int.cast_natCast, Nat.cast_mul, neg_mul, mul_assoc] using'''
d='''      Bool.false_eq_true, ite_false, ite_true, Int.cast_neg, Int.cast_natCast,
      Nat.cast_mul, neg_mul, mul_assoc] using'''
assert s.count(a)==1 and s.count(c)==1
s=s.replace(a,b).replace(c,d)
new=s.encode()
(HERE/'WidenNormal4.lean.inc').write_bytes(new)
assert (HERE/'WidenNormal3.lean.inc').read_bytes()==old
indexed=(HERE/'TwoChain128Indexed.lean.inc').read_bytes()
assert sha(indexed)=='25ed9a4ee68384e03e3db32c5e7fa56dcafb340d8628d178056b67cf2c26b2cd'
r=dict(observed_at_utc=datetime.now(timezone.utc).isoformat(),phase_first_utc='2026-10-29T01:27:00Z',
    compiler_run='40798250042',log_sha256='095db5ed8f8a897191d72d1f51e1eff02e0841bcedde66ea5cd9eeffbc136cc6',
    old_sha256=sha(old),new_path='WidenNormal4.lean.inc',new_sha256=sha(new),new_bytes=len(new),
    changed_diagnostic_lines=[1707,1710],change='Only explicitly eliminate Bool false=true / True conditionals in the two existing sign branches.',
    roots=['Submission.R24RepresentationWiden.'+n for n in
      ['normal_decode','native_model','native_finite','actual_native_value','signed_zero_bits']],
    status='NEW_FRAGMENT_NOT_RUN',no_resource_change=True,no_local_Lean=True,no_CI=True,
    indexed_first_draft_frozen=dict(sha256=sha(indexed),bytes=len(indexed),source='TwoChain128Indexed.lean.inc',
      phase_first_utc='2026-10-29T01:19:21Z',last_word_model_utc='2026-10-29T01:26:11Z',Lean='NOT_RUN',queue='NOT_QUEUED'),
    acceptance_boundary='Other roots having no error in island6 is not a module PASS; no replay/AX acceptance inherited.',
    shared_deadline_utc='2026-10-29T03:38:56Z',tokens='UNKNOWN',cached_input_tokens='UNKNOWN')
(HERE/'widen4-repair-receipt.json').write_text(json.dumps(r,indent=2)+'\n',encoding='utf-8')
print(json.dumps(r))
