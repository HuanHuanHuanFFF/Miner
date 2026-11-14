"""Fixed encoder boundary falsifiers; integer oracle, no tensors/timing/randomness."""
from pathlib import Path
from datetime import datetime,timezone
import hashlib,json
HERE=Path(__file__).resolve().parent
B=1<<64
MASK=B-1
MAX=(1<<24)-1
def signed(q): return q-B if q>=1<<63 else q
def native_encode(neg,a,b,s):
    m=(((a*b)&MASK)<<(s%64))&MASK
    return (-m)&MASK if neg else m
def guarded(a,b,s): return a<1<<24 and b<1<<24 and (a==0 or b==0 or s<=14)
def exact(neg,a,b,s):
    m=0 if a==0 or b==0 else (a*b)<<s
    return -m if neg else m
def split(neg,a,b,sa,sb):
    aa=(a<<(sa%64))&MASK
    bb=(b<<(sb%64))&MASK
    return (((-aa)&MASK if neg else aa)*bb)&MASK
valid=[(False,MAX,MAX,14),(True,MAX,MAX,14),(False,1,1,0),(True,1,1,14),
       (False,0,MAX,MASK),(True,MAX,0,64),(True,0,0,MASK),
       (False,1<<23,MAX,14),(True,MAX,1<<23,0)]
rows=[]
for neg,a,b,s in valid:
    assert guarded(a,b,s)
    got=signed(native_encode(neg,a,b,s)); want=exact(neg,a,b,s)
    assert got==want and abs(got)<1<<62
    rows.append(dict(negative=neg,left=a,right=b,shift=s,actual=got,expected=want))
split_rows=[]
for neg,a,b,sa,sb in [(False,MAX,MAX,7,7),(True,MAX,MAX,14,0),(True,MAX,MAX,0,14),
                    (False,0,MAX,MASK,1),(True,MAX,0,64,MASK)]:
    assert a==0 or b==0 or (sa<=14 and sb<=14 and ((sa+sb)&MASK)<=14)
    lhs=split(neg,a,b,sa,sb);rhs=native_encode(neg,a,b,(sa+sb)&MASK)
    assert lhs==rhs
    split_rows.append(dict(negative=neg,left=a,right=b,sa=sa,sb=sb,split_word=lhs,fused_word=rhs))
bad_shift=dict(left=1,right=1,shift=64,guard=False,actual_without_guard=signed(native_encode(False,1,1,64)),expected=1<<64)
bad_bound=dict(left=MAX,right=MAX,shift=15,guard=False,actual_abs=signed(native_encode(False,MAX,MAX,15)),claimed_limit=1<<62)
bad_product=dict(left=1<<32,right=1<<32,shift=0,guard=False,actual_without_guard=0,expected=1<<64)
bad_split=dict(sa=MASK,sb=1,word_sum=0,only_word_sum_guard_would_accept=True,
    proper_splitGuard=False,split_word=split(False,1,1,MASK,1),fused_word=native_encode(False,1,1,0))
assert bad_shift['actual_without_guard']!=bad_shift['expected']
assert bad_bound['actual_abs']>=bad_bound['claimed_limit']
assert bad_split['split_word']!=bad_split['fused_word']
sources=[dict(path=n,bytes=len((HERE/n).read_bytes()),sha256=hashlib.sha256((HERE/n).read_bytes()).hexdigest())
    for n in ['TwoChain128Encoder.lean.inc','TwoChain128SplitShift.lean.inc']]
result=dict(observed_at_utc=datetime.now(timezone.utc).isoformat(),phase_first_utc='2026-10-29T00:18:49Z',
    status='FIXED_WORD_MODEL_ONLY_LEAN_NOT_RUN_NOT_QUEUED',sources=sources,
    encoded_cases=rows,split_cases=split_rows,falsifiers=[bad_shift,bad_bound,bad_product,bad_split],
    full_kernel='NOT_IMPLEMENTED',timing='NOT_RUN',CI='NO_NEW_QUEUE')
(HERE/'chain2-encoder-word-results.json').write_text(json.dumps(result,indent=2)+'\n',encoding='utf-8')
print(json.dumps(dict(sources=sources,valid_encoder_cases=len(rows),valid_split_cases=len(split_rows),
    falsifier_count=4,all_fixed_checks_passed=True)))
