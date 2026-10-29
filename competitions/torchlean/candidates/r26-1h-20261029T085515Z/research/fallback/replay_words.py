from pathlib import Path
from fractions import Fraction
import datetime, hashlib, importlib.util, json, random, sys

HERE = Path(__file__).resolve().parent
OLD = HERE.parents[2] / 'r25-90m-20261029T064916Z' / 'research' / 'integer'
sys.path.insert(0, str(OLD))
import model_span_probe as m
import band_pair_probe as band

B = 1 << 64
MASK = B - 1
MASK128 = (1 << 128) - 1

def sx(word, bits):
    return word if word < 1 << (bits-1) else word - (1 << bits)

def extend32(word):
    return ((word ^ (1 << 31)) - (1 << 31)) & MASK

def merge(lo, hi, q):
    nxt = (lo + q) & MASK
    high = (hi + (MASK if q >= B//2 else 0) + int(nxt < lo)) & MASK
    return nxt, high

def block(a, b, length, index, acc=0):
    for j in range(index, index+length):
        acc = (acc + extend32(a[j]) * extend32(b[j])) & MASK
    return acc

def each(a, b):
    lo = hi = 0
    for x, y in zip(a, b):
        lo, hi = merge(lo, hi, (extend32(x) * extend32(y)) & MASK)
    return lo, hi

def blocked(a, b, size=16):
    lo = hi = 0
    count = len(a) // size
    for j in range(count):
        lo, hi = merge(lo, hi, block(a, b, size, j*size))
    lo, hi = merge(lo, hi, block(a, b, len(a)%size, count*size))
    return lo, hi

def signed128(pair):
    lo, hi = pair
    return lo + sx(hi, 64)*B

def magn32(word):
    return abs(sx(word, 32))

def canblock(a, b):
    ma = max(map(magn32, a), default=0)
    mb = max(map(magn32, b), default=0)
    return len(a) <= 1048576 and ma*mb < 1 << 59

def align(raw):
    ds = [m.decode(w) for w in raw]
    active = [e for _,v,e in ds if v]
    base = min(active) if active else 0
    factors = [s*(v << (e-base)) if v else 0 for s,v,e in ds]
    assert all(-(1<<31) <= f < 1<<31 for f in factors)
    return base, [f & 0xffffffff for f in factors]

def main():
    seed = 42
    rr = m.lcg(8, seed ^ 0x5bd1e995)
    n = (32+rr[0]%67)*8
    outputs = (8+rr[1]%25)*8
    records=[]
    for kind in ('normal', 'sparse'):
        x = m.gen(kind,n,seed+999)
        w = m.weights(kind,seed,0,n,n*outputs)
        bias=m.biases(seed,1,outputs)
        baseA,a = align(x)
        for j in range(outputs):
            y=w[j*n:(j+1)*n]
            baseB,b=align(y)
            assert canblock(a,b)
            got = blocked(a,b)
            eachgot = each(a,b)
            total=sum(sx(x,32)*sx(y,32) for x,y in zip(a,b))
            assert signed128(got)==signed128(eachgot)==total
            sg,mb,eb=m.decode(bias[j]); shift=eb+149-baseA-baseB
            assert shift>=0
            full = total+sg*(mb<<shift)
            result = m.round_rat(Fraction(full)*Fraction(2)**(baseA+baseB-298))
            reference=m.round_rat(sum(m.rational(x)*m.rational(y) for x,y in zip(x,y))+m.rational(bias[j]))
            assert result==reference
            records.append({'kind':kind,'output':j,'word':result,'reference':reference,
                            'merges_in_source':n//16+1,'nonempty_blocks':(n+15)//16,
                            'guard':True,'signed_total_bits':abs(total).bit_length()})

    rng=random.Random(2026102909)
    synthetic=[]
    for length in (0,1,15,16,17,31,32,33,608):
        a=[rng.randrange(-(1<<29)+1,1<<29)&0xffffffff for _ in range(length)]
        b=[rng.randrange(-(1<<29)+1,1<<29)&0xffffffff for _ in range(length)]
        assert canblock(a,b)
        want=sum(sx(x,32)*sx(y,32) for x,y in zip(a,b))
        assert signed128(blocked(a,b))==want
        assert signed128(each(a,b))==want
        synthetic.append({'length':length,'word128':list(blocked(a,b)),'total':str(want)})
    for x in (0,1,0x7fffffff,0x80000000,0xffffffff):
        for y in (0,1,0x7fffffff,0x80000000,0xffffffff):
            assert sx((extend32(x)*extend32(y))&MASK,64)==sx(x,32)*sx(y,32)
    merges=[]
    for lo in (0,1,B//2-1,B//2,MASK):
        for hi in (0,1,B//2-1,B//2,MASK):
            for q in (0,1,B//2-1,B//2,MASK):
                merged=merge(lo,hi,q)
                want=(lo+B*hi+sx(q,64))&MASK128
                assert merged[0]+B*merged[1]==want
                merges.append((lo,hi,q))
    rejects=[]
    for magnitude in (1<<29,(1<<30)-1,1<<30,1<<31):
        a=[magnitude&0xffffffff]*16;b=a.copy()
        guard=canblock(a,b)
        true=sum(sx(x,32)*sx(y,32) for x,y in zip(a,b))
        actual=signed128(blocked(a,b))
        if guard: assert actual==true
        assert signed128(each(a,b))==true
        rejects.append({'factor_magnitude':magnitude,'block_guard':guard,
                        'unsafe_block_total':str(actual),'true_total':str(true),
                        'each_fallback_exact':True})
    result={'at_utc':datetime.datetime.now(datetime.timezone.utc).isoformat(),
            'status':'FINITE_WORD_REPLAY_NOT_LEAN_COMPILATION_OR_TIMING',
            'profile':'public typical seed42 first layer only',
            'shape':[n,outputs],'actual_loop_records':records,'synthetic':synthetic,
            'signed32_boundary_products':25,'merge128_boundary_cases':len(merges),
            'rejects':rejects,
            'source_hashes':{p.name:hashlib.sha256(p.read_bytes()).hexdigest()
                             for p in (Path(__file__),HERE/'WordBlockRuntime.lean',
                                       OLD/'model_span_probe.py',m.CONTRACT,m.SUITE)},
            'missing':['Lean compile','compiler boxing evidence','complete 12 obligation',
                       'fullmodel paired timing','fresh confirmation']} 
    (HERE/'word-replay.json').write_text(json.dumps(result,indent=2)+'\n',encoding='utf-8')
    print(json.dumps({'shape':result['shape'],'matching_dots':len(records),
                      'synthetic_lengths':len(synthetic),'merge_cases':len(merges),
                      'rejects':rejects},indent=2))

if __name__=='__main__': main()
