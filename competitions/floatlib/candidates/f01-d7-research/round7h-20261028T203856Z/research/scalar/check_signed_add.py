"""Bounded exact-integer semantics check. No host float or target timing claims."""
from pathlib import Path
import importlib.util, hashlib, json, random, time
from datetime import datetime, timezone
D=Path(__file__).resolve().parent
R=next(p for p in D.parents if (p/'AGENTS.md').exists())
OLD=R/'competitions/floatlib/candidates/f01-d7-research/round6h-20261027T211247Z/research/independent-frontier'
spec=importlib.util.spec_from_file_location('oracle',OLD/'same_exponent_add.py')
M=importlib.util.module_from_spec(spec);spec.loader.exec_module(M)
MASK=(1<<64)-1

def guard(u,v):
    a,b=(u>>23)&255,(v>>23)&255
    return 24<=a<=252 and 24<=b<=252 and abs(a-b)<=38

def sint(u):
    m=(u&0x7fffff)|0x800000
    return -m if u>>31 else m

def integer_float_bits(n):
    return M.encode(n<<149)

def core(u,v):
    assert guard(u,v)
    eu,ev=(u>>23)&255,(v>>23)&255
    if eu<ev: u,v,eu,ev=v,u,ev,eu
    masku=MASK if u>>31 else 0; maskv=MASK if v>>31 else 0
    a=((((u&0x7fffff)|0x800000)^masku)-masku)&MASK
    b=((((v&0x7fffff)|0x800000)^maskv)-maskv)&MASK
    word=((a<<(eu-ev))+b)&MASK
    n=word if word<1<<63 else word-(1<<64)
    assert n==(sint(u)<<(eu-ev))+sint(v)
    assert -(1<<63)<n<(1<<63)
    if not n:return 0
    raw=integer_float_bits(n)
    e=(raw>>23)&255
    assert 1<=e+ev-150<=253
    return (raw+(((ev-150)&0xffffffff)<<23))&0xffffffff

def main():
    start=time.monotonic();n=0;trace=hashlib.sha256();cancellations=0;low=0
    fs=[0,1,2,3,0x3fffff,0x400000,0x7ffffe,0x7fffff]
    for elo in [24,25,63,64,126,127,128,190,191,214,251,252]:
        for gap in [0,1,7,8,23,24,25,26,37,38]:
            if elo+gap>252:continue
            for sa in [0,1]:
                for sb in [0,1]:
                    for fa in fs:
                        for fb in fs:
                            u=(sa<<31)|((elo+gap)<<23)|fa;v=(sb<<31)|(elo<<23)|fb
                            actual=core(u,v);expected=M.oracle(u,v)
                            assert actual==expected,(hex(u),hex(v),hex(actual),hex(expected))
                            trace.update(actual.to_bytes(4,'little'));n+=1
                            cancellations+=actual==0
                            low+=abs((sint(u)<<gap)+sint(v))<(1<<23)
    rng=random.Random(240110)
    for _ in range(20000):
        elo=rng.randrange(24,253);gap=rng.randrange(min(38,252-elo)+1)
        u=(rng.getrandbits(1)<<31)|((elo+gap)<<23)|rng.getrandbits(23)
        v=(rng.getrandbits(1)<<31)|(elo<<23)|rng.getrandbits(23)
        actual=core(u,v);expected=M.oracle(u,v)
        assert actual==expected,(hex(u),hex(v),hex(actual),hex(expected))
        trace.update(actual.to_bytes(4,'little'));n+=1
    # Keep counterexamples for rejected wider guards, instead of erasing them.
    rejected=[{'u':hex(u),'v':hex(v),'guard':guard(u,v),'oracle':hex(M.oracle(u,v))}
              for u,v in [(0x0b800001,0x8b800000),(0x7f7fffff,0x7f7fffff),
                          (0x1f7fffff,0x0c7fffff),(0x00000001,0x80000001),
                          (0x00000000,0x80000000),(0x80000000,0x80000000)]]
    out={'at_utc':datetime.now(timezone.utc).isoformat(),'cases':n,'mismatches':0,
         'fixed_cancellations':cancellations,'fixed_small_integer_magnitudes':low,
         'trace_sha256':trace.hexdigest(),'script_sha256':hashlib.sha256(Path(__file__).read_bytes()).hexdigest(),
         'oracle_sha256':hashlib.sha256((OLD/'same_exponent_add.py').read_bytes()).hexdigest(),
         'runtime_sha256':hashlib.sha256((D/'Runtime-signed-add.lean.inc').read_bytes()).hexdigest(),
         'guard':'both raw E in24..252 and abs(Eu-Ev)<=38',
         'scope':'Finite integer emulation only. Actual Int64 native conversion, Lean obligations and timing NOT_RUN.',
         'rejected_boundary_examples':rejected,'elapsed_seconds':time.monotonic()-start}
    (D/'signed-add-model.json').write_text(json.dumps(out,indent=2)+'\n',encoding='utf8')
    print(json.dumps(out))
if __name__=='__main__':main()
