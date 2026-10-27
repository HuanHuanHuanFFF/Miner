"""Optional proof-engineering alternative; no source/candidate/CI is changed.
The SIGTERM reason remains UNKNOWN. Avoid large-modulus omega in nat_bias.
"""
from pathlib import Path
from hashlib import sha256
from datetime import datetime, timezone
import json

base=Path(__file__).resolve().parent;root=base.parents[4]
old=(base/'astra-biased-rne3.lean').read_bytes()
generic=(base/'astra-general-bias-rne-draft.lean').read_bytes()
q=generic[generic.index(b'theorem quotient_bias '):generic.index(b'theorem nat_bias ')]
q=q.replace(b'theorem quotient_bias ',b'private theorem quotient_bias ',1)
first=old.index(b'theorem nat_bias ');last=old.index(b'@[inline] def biased ',first)
statement=old[first:old.index(b' := by',first)]
proof=b''' := by
  rcases ht with rfl | rfl
  \xc2\xb7 simpa [roundShiftRightEven_eq_roundQuotientEven, Nat.shiftRight_eq_div_pow] using
      quotient_bias p 4194304 (by decide)
  \xc2\xb7 simpa [roundShiftRightEven_eq_roundQuotientEven, Nat.shiftRight_eq_div_pow] using
      quotient_bias p 8388608 (by decide)

'''
new=old[:first]+q+statement+proof+old[last:]
target=base/'astra-biased-rne4-quotient.lean'
if target.exists():assert target.read_bytes()==new
else:target.write_bytes(new)
assert new[new.index(b'@[inline] def biased '):]==old[last:]
assert statement==new[new.index(b'theorem nat_bias '):new.index(b' := by',new.index(b'theorem nat_bias '))]
pred=[]
for name in ['f01-r14-dev-integer-exponent4','f01-r14-dev-allword-combined2']:
    src=root/'competitions/floatlib/candidates'/name/'Kernel.lean'
    raw=src.read_bytes();count=raw.count(old)
    row=dict(source=name,source_sha256=sha256(raw).hexdigest(),old_fragment_occurrences=count)
    if count==1:
        changed=raw.replace(old,new)
        row.update(preview_bytes=len(changed),preview_sha256=sha256(changed).hexdigest(),within_source_limit=len(changed)<=256000)
    pred.append(row)
record=dict(timestamp_utc=datetime.now(timezone.utc).isoformat(),state='OPTIONAL_PROOF_ENGINEERING_NOT_RUN_NO_CANDIDATE',
    file=target.name,bytes=len(new),sha256=sha256(new).hexdigest(),
    old_fragment_sha256=sha256(old).hexdigest(),nat_bias_statement_unchanged=True,
    runtime_and_word_bias_suffix_identical=True,
    mechanism='General quotient/remainder proof with small symbolic coefficients; instantiate half=2^22/2^23. Avoid asking omega to discover the entire large-modulus periodic identity directly.',
    evidence='40151550349 MUL4/combined2 VerifyFull exit=-15 around22seconds, empty output; official timeout path returns124 and OOM helper recognizes-9. Actual termination cause UNKNOWN, so this does not diagnose a false theorem or claim resource improvement.',
    preview=pred,decision='D may use only if actual resource/proof-cost diagnosis warrants; do not replace accepted ADD small-shift proof or expand runtime/CI queue.')
(base/'astra-biased-rne4-quotient.json').write_text(json.dumps(record,ensure_ascii=False,indent=2)+'\n',encoding='utf-8')
print(json.dumps(record,ensure_ascii=False,indent=2))
