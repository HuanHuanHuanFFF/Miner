"""Small finite falsifier for a separate exact-integer cache proposal.

No Lean/runtime candidate, timing, or universal proof. Uses only frozen fixtures
and independently decoded rational binary32 values. No third-party kernel code.
"""
from pathlib import Path
from fractions import Fraction
from collections import Counter
import hashlib
import json
import datetime

HERE = Path(__file__).resolve().parent
FIXTURES = HERE.parent/'development-dot-cost/fixtures.json'
MASK = 2**64-1


def decode(w):
    e, f = (w >> 23) & 255, w & (2**23-1)
    if e == 255:
        return None
    m = f if e == 0 else 2**23+f
    k = 0 if e == 0 else e-1
    value = Fraction(m)*Fraction(2)**(k-149)
    return -value if w >> 31 else value


def prepare(words):
    if any(((w>>23)&255)==255 or (((w>>23)&255)==0 and w&(2**23-1)) for w in words):
        return None
    active=[(((w>>23)&255)-1) for w in words if ((w>>23)&255)!=0]
    low, high = (min(active),max(active)) if active else (0,0)
    data=[]
    for w in words:
        e, f=(w>>23)&255,w&(2**23-1)
        m=0 if e==0 else 2**23+f
        aligned=0 if m==0 else m << (e-1-low)
        data.append((-aligned if w>>31 else aligned)&MASK)
    return low,high,data,bool(active)


def main():
    fixture=json.loads(FIXTURES.read_bytes())
    records=[]
    for c in fixture['cases']:
        x,y=c['x'],c['y']
        a,b=prepare(x),prepare(y)
        n=len(x)
        L=(n-1).bit_length() if n else 0
        reason='eligible'
        if not n or len(y)!=n or n>2**20:
            reason='shape'
        elif a is None or b is None:
            reason='not_normal_or_zero'
        elif not(a[3] and b[3]):
            reason='all_zero_operand_fallback'
        elif 48+(a[1]-a[0])+(b[1]-b[0])+L>62:
            reason='span_guard'
        r={'name':c['name'],'kind':c['kind'],'n':n,'timed':c.get('timed',False),'state':reason}
        if reason=='eligible':
            one=0; even=0; odd=0
            for i,(u,v) in enumerate(zip(a[2],b[2])):
                term=(u*v)&MASK
                one=(one+term)&MASK
                if i%2: odd=(odd+term)&MASK
                else: even=(even+term)&MASK
            two=(even+odd)&MASK
            assert two==one
            signed=one if one<2**63 else one-2**64
            exact=sum((decode(u)*decode(v) for u,v in zip(x,y)),Fraction())
            represented=Fraction(signed)*Fraction(2)**(a[0]+b[0]-298)
            assert represented==exact
            assert abs(signed)<2**62
            r.update(single_word=one,two_chain_word=two,zero_sum_needs_fallback=one==0,
                     input_spans=[a[1]-a[0],b[1]-b[0]],L=L,exact_rational_match=True)
        records.append(r)
    receipt={'at_utc':datetime.datetime.now(datetime.timezone.utc).isoformat(),
             'status':'FINITE_MODEL_NO_COUNTEREXAMPLE_NOT_A_PROOF_OR_BENCHMARK',
             'fixture_sha256':hashlib.sha256(FIXTURES.read_bytes()).hexdigest(),
             'cases':len(records),'states':dict(Counter(x['state'] for x in records)),
             'eligible_by_kind':dict(Counter(x['kind'] for x in records if x['state']=='eligible')),
             'eligible_zero_sums':sum(x.get('zero_sum_needs_fallback',False) for x in records),
             'records':records,
             'limits':['Uses observed exploratory fixtures, never an unseen confirmation set.',
                       'No packed-storage API, generated C/ASM, native cost or full-model coverage established.',
                       'Prealigned operands add preparation/storage cost; zero-sum fallback preserves a required policy branch only in the proposed design.',
                       'No Lean source or accepted runtime theorem is produced by this Python model.']}
    (HERE/'aligned-integer-discriminator.json').write_text(json.dumps(receipt,indent=2)+'\n',encoding='utf-8',newline='\n')
    print(json.dumps({k:receipt[k] for k in ('status','cases','states','eligible_by_kind','eligible_zero_sums')}))


if __name__=='__main__':
    main()
