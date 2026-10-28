"""UInt32 field relocation only; no new runtime, Float32 execution, or timing."""
from pathlib import Path
from datetime import datetime,timezone
import json
HERE=Path(__file__).resolve().parent
M=(1<<32)-1;B=1<<23;checks=0;first_bad=None
for s in range(128,381):
 for ep in [173,174]:
  for sign in [0,1<<31]:
   for frac in [0,1,B-2,B-1]:
    mid=(ep<<23)|frac
    shifted=((s-300)&M)<<23&M
    delta=(shifted+sign)&M
    result=(mid+delta)&M
    target=sign|((s+ep-300)<<23)|frac
    assert 1<=s+ep-300<=254 and result==target
    wrong=(mid+(shifted|sign))&M
    if wrong!=target and first_bad is None:
     first_bad=dict(S=s,Ep=ep,sign=hex(sign),frac=frac,mid=hex(mid),shifted=hex(shifted),
       additive_delta=hex(delta),wrong_or_delta=hex(shifted|sign),correct=hex(target),wrong=hex(wrong),
       raw_input_witness=['0xa0000000','0x20000000'])
    checks+=1
assert first_bad['correct']=='0x80800000' and first_bad['wrong']=='0x800000'
out=dict(at_utc=datetime.now(timezone.utc).isoformat(),cases=checks,counterexample=first_bad,
 scope='Pure UInt32 wrap/shift/add model. A generic field identity, not a new native product implementation or Lean proof. No confirmation data/CI.',
 universal_paper_argument='mid=Ep*B+f; signed delta=(S-300)*B+sign; total=sign+(S+Ep-300)*B+f lies in [0,2^32), so modulo2^32 equals target. OR sign is invalid when negative delta already has bit31 set.',
 formal='NOT_RUN',native_cost='UNKNOWN')
(HERE/'delta-word-receipt.json').write_text(json.dumps(out,indent=2)+'\n',encoding='utf-8')
print(json.dumps(out))
