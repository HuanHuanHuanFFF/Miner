"""Small fixed word-carry falsifiers against independent integer sums; no timings."""
from pathlib import Path
from datetime import datetime, timezone
import hashlib,json
HERE=Path(__file__).resolve().parent
B=1<<64
M=1<<128
T=(1<<62)-1
def decode(lo,hi):
    u=lo+hi*B
    return u-M if hi >= 1<<63 else u
def run(values,omit_carry=False,omit_sign=False):
    al=ah=bl=bh=0
    for z in values:
        q=z%B
        lo=(al+q)%B
        hi=(ah+(B-1 if q >= 1<<63 and not omit_sign else 0)+(lo<al))%B
        al,ah,bl,bh=bl,bh,lo,hi
    lo=(al+bl)%B
    hi=(ah+bh+(False if omit_carry else lo<al))%B
    return decode(lo,hi)
cases=[[],[0],[1],[-1],[T],[-T],[-1,1],[1,-1],[T,T],[-T,-T],
       [T,-T,T],[-T,T,-T],[T]*17,[-T]*17,[T,-T]*8+[1],
       [-1,T,1,-T,0], [1,2,3,4,5,6,7], [0,0,0,0,0]]
rows=[dict(terms=x,expected=sum(x),actual=run(x),pass_=run(x)==sum(x)) for x in cases]
assert all(r['pass_'] for r in rows)
bad_sign=dict(terms=[-1],expected=-1,actual=run([-1],omit_sign=True))
bad_merge=dict(terms=[-1,1],expected=0,actual=run([-1,1],omit_carry=True))
assert bad_sign['actual']!=bad_sign['expected'] and bad_merge['actual']!=bad_merge['expected']
src=(HERE/'TwoChain128.lean.inc').read_bytes()
result=dict(observed_at_utc=datetime.now(timezone.utc).isoformat(),source_sha256=hashlib.sha256(src).hexdigest(),
    status='FIXED_PYTHON_WORD_MODEL_ONLY_LEAN_NOT_RUN',cases=rows,
    falsifiers=dict(omitted_sign_extension=bad_sign,omitted_final_low_carry=bad_merge,
       one_complement_is_not_input_encoding=dict(magnitude=1,ones_complement_word=B-2,
           interpreted_signed64=-2,intended_negative_term=-1)),
    limitations='No Lean execution, generated ASM, timing, new benchmark, random sweep, or original-caller integration.')
(HERE/'chain2-word-results.json').write_text(json.dumps(result,indent=2)+'\n',encoding='utf-8')
print(json.dumps(dict(fixed_cases=len(rows),passed=len(rows),source_sha256=result['source_sha256'],falsifiers=result['falsifiers'])))
