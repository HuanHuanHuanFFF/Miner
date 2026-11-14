"""Finite arbitrary word-hint and exact-certificate model, no native execution."""
from pathlib import Path
import hashlib,importlib.util,json,random
HERE=Path(__file__).resolve().parent
M=1<<23;MASK32=(1<<32)-1
def load(name,path):
    s=importlib.util.spec_from_file_location(name,path);m=importlib.util.module_from_spec(s);s.loader.exec_module(m);return m
def guess(bits):return (((((bits&0x7fffffffffffffff)+0x10000000)>>29)&MASK32)-0xc0000000)&MASK32
def fields(bits):
    w=guess(bits);return (w>>23)&255,M+(w&0x7fffff)

def main():
    interval=load('interval_model',HERE/'preflight-interval-word128.py')
    guards=load('guards_model',HERE/'gap-boundary-model.py');r=guards.load()
    count=accepted=0;trace=hashlib.sha256()
    def test_hint(bits,lo,hi,d,actual_sign):
        nonlocal count,accepted
        E,m=fields(bits)
        a=interval.power(lo,hi,d,E,guards) if m==M else interval.strict(lo,hi,d,m,E)
        if a:
            target=(int(actual_sign)<<31)|(E<<23)|(m-M)
            for n in {lo,hi,(lo+hi)//2}:
                assert r.actual_word(actual_sign,n,d,E-150)==target
        count+=1;accepted+=int(a);trace.update(f'{bits},{lo},{hi},{d},{int(actual_sign)},{int(a)}\n'.encode())
        return a
    rng=random.Random(24282342)
    for E32 in range(1,255):
        E64=E32+896
        for frac32 in (0,1,2,3,M-3,M-2,M-1):
            for residual in (0,1,(1<<28)-1,1<<28,(1<<28)+1,(1<<29)-1):
                frac=(frac32<<29)+residual
                for sign in (False,True):
                    bits=(int(sign)<<63)|(E64<<52)|frac;E,m=fields(bits)
                    # Exact normalization transport is computed here only for the finite model.
                    n=(1<<52)+frac;shift=(E-150)-(E64-1075)
                    assert shift in (29,30);d=1<<shift
                    test_hint(bits,n,n,d,sign)
    for _ in range(100000):
        E32=rng.randrange(1,255);E64=E32+896;frac=rng.getrandbits(52);sign=bool(rng.getrandbits(1))
        bits=(int(sign)<<63)|(E64<<52)|frac;E,m=fields(bits);n=(1<<52)+frac
        shift=(E-150)-(E64-1075);assert shift in (29,30)
        test_hint(bits,n,n,1<<shift,sign)
    # Hint values can be unrelated to the exact enclosure, including NaN/Inf bit patterns.
    # The generic certificate is still sound; it does not assert a hint-value relation.
    malformed_hints=(0,1,(1<<64)-1,0x7ff0000000000000,0x7ff8000000000001,0x8000000000000000)
    for bits in malformed_hints:
        E,m=fields(bits)
        for d in (1,4,(1<<32)-1,(1<<63)-1):
            for delta in (-d,-d//4,0,d//4,d):
                n=m*d+delta
                for sign in (False,True):test_hint(bits,n,n,d,sign)
    examples=[]
    for bits in (0x3ff0000010000000,0x3ff0000030000000,0x3ffffffff0000000):
        E64=(bits>>52)&2047;frac=bits&((1<<52)-1);E,m=fields(bits)
        n=(1<<52)+frac;d=1<<((E-150)-(E64-1075))
        a=test_hint(bits,n,n,d,False);exact=r.actual_word(False,n,d,E-150)
        examples.append({'binary64_word':hex(bits),'proposal':hex(guess(bits)),'exact_rn32':hex(exact),'accepted':a,
            'num':n,'den':d,'E':E})
    assert examples[0]['proposal']=='0x3f800001' and examples[0]['exact_rn32']=='0x3f800000' and not examples[0]['accepted']
    assert not examples[1]['accepted'] and examples[1]['proposal']==examples[1]['exact_rn32']
    assert examples[2]['accepted'] and examples[2]['proposal']==examples[2]['exact_rn32']=='0x40000000'
    report={'status':'FINITE_ARBITRARY_HINT_CERTIFICATE_MODEL_PASS','source_sha256':hashlib.sha256((HERE/'ArbitraryProposal.lean.inc').read_bytes()).hexdigest(),
        'cases':count,'accepted':accepted,'trace_sha256':trace.hexdigest(),'examples':examples,
        'Lean':'NOT_RUN','native':'NOT_RUN','cost':'NOT_RUN',
        'scope':'The proposal intentionally fails ties-to-even and need not match an F64 value. Certificate soundness uses only exact normalized enclosure premises and exact result sign. No Float.toFloat32 call, cast accuracy assumption, native enclosure derivation or runtime cost result.'}
    (HERE/'proposal-model.json').write_bytes((json.dumps(report,indent=2)+'\n').encode())
    print(json.dumps({k:report[k] for k in ('status','cases','accepted','examples')}))
if __name__=='__main__':main()
