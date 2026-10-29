"""Finite UInt128/UInt64 guard model for power-binade certificates; not a kernel."""
from pathlib import Path
import hashlib,importlib.util,json,random
HERE=Path(__file__).resolve().parent
MASK=(1<<64)-1;M=1<<23
def load():
    s=importlib.util.spec_from_file_location('power_reference',HERE/'model-preflight.py');m=importlib.util.module_from_spec(s);s.loader.exec_module(m);return m
def native_guard(n,d,E,mutant=None):
    if not (0<d<=MASK and 1<=E<=254):return False
    p=M*d
    below=n<p;gap=p-n if below else n-p
    if mutant!='low_only' and gap>>64:return False
    g=gap&MASK
    if mutant!='missing_gap_lt_den' and not g<d:return False
    if mutant!='quarter_without_half' and not g<=((d-g)&MASK):return False
    if below and E>=2:
        t=(g+g)&MASK
        if not t<=((d-t)&MASK):return False
    return True
def main():
    r=load();count=accepted=0;trace=hashlib.sha256()
    def test(n,d,E):
        nonlocal count,accepted
        if not 0<=n<(1<<128):return
        a=native_guard(n,d,E);b=r.check(n,d,E-150)
        assert a==b,(n,d,E,a,b)
        if d>0:assert a==(r.actual_word(False,n,d,E-150)==E<<23)
        count+=1;accepted+=int(a);trace.update(f'{n},{d},{E},{int(a)}\n'.encode())
    for E in range(1,255):
        for d in (0,1,2,3,4,7,(1<<24)-1,(1<<32)-1,(1<<63)-1,1<<63,(1<<63)+1,MASK):
            offsets={0,-1,1,-d-1,-d,-d+1,d-1,d,d+1,
                -(1<<64)-1,-(1<<64),-(1<<64)+1,(1<<64)-1,1<<64,(1<<64)+1,
                -(1<<63)-1,-(1<<63),-(1<<63)+1,(1<<63)-1,1<<63,(1<<63)+1}
            for q in (d//4,d//2):offsets.update((q-1,q,q+1,-q-1,-q,-q+1))
            for k in sorted(offsets):test(M*d+k,d,E)
    rng=random.Random(24280338)
    for _ in range(70000):
        d=rng.randrange(1,1<<64);E=rng.randrange(1,255)
        test(M*d+rng.randrange(-d,d+1),d,E)
    for _ in range(20000):test(rng.getrandbits(128),rng.randrange(1,1<<64),rng.randrange(1,255))
    mutants=[]
    for label,n,d,E in (
        ('low_only',M*4+(1<<64),4,128),
        ('missing_gap_lt_den',M+(1<<63),1,128),
        ('quarter_without_half',M*MASK-(1<<63),MASK,128)):
        assert native_guard(n,d,E,label) and not native_guard(n,d,E)
        assert r.actual_word(False,n,d,E-150)!=E<<23
        p=M*d;g=abs(n-p)
        mutants.append({'mutant':label,'num':str(n),'den':str(d),'E':E,'gap':str(g),'twice_gap_mod2^64':str((2*g)&MASK),
            'actual_word':hex(r.actual_word(False,n,d,E-150)),'wrong_power_word':hex(E<<23)})
    odd=M+1;d=2;n=2*odd+1;E=128
    assert abs(n-odd*d)*2<=d and r.actual_word(False,n,d,E-150)!=(E<<23|1)
    mutants.append({'mutant':'closed_generic_half_without_even_or_power_guard','mantissa':odd,'num':n,'den':d,'E':E,
        'actual_word':hex(r.actual_word(False,n,d,E-150)),'wrong_odd_mantissa_word':hex(E<<23|1)})
    assert not native_guard(0,0,128)
    result={'status':'FINITE_WORD_GUARD_EQUIVALENCE_PASS_MUTANTS_REJECTED','script_sha256':hashlib.sha256(Path(__file__).read_bytes()).hexdigest(),
        'cases':count,'accepted':accepted,'trace_sha256':trace.hexdigest(),'mutants':mutants,
        'required_guard_order':'D>0; full128 absolute gap; gap.high=0; gap.low<D; gap<=D-gap. Only then twiceGap=gap+gap; lower side and E>=2 require twiceGap<=D-twiceGap. M fixed2^23/even.',
        'scope':'Finite arithmetic model only. No native runtime, Lean proof, timing, new-track kernel, or success probability. Native boundary implementation waits for power-cell2 and broad WordGap128 actual typing.'}
    (HERE/'gap-boundary-model.json').write_bytes((json.dumps(result,indent=2)+'\n').encode())
    print(json.dumps({'status':result['status'],'cases':count,'accepted':accepted,'mutants':len(mutants)}))
if __name__=='__main__':main()
