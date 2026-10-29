"""Finite UInt128 scaled-compare oracle/mutant check; not a target kernel."""
from pathlib import Path
import hashlib
import json
import random

HERE=Path(__file__).resolve().parent
MASK=(1<<128)-1

def compare_scaled(a,ea,b,eb):
    assert 0<=a<=MASK and 0<=b<=MASK
    if not a or not b:return (a>0)-(b>0)
    la,lb=a.bit_length(),b.bit_length()
    ha,hb=la+ea,lb+eb
    if ha!=hb:return (ha>hb)-(ha<hb)
    if ea>=eb:
        shift=ea-eb;assert shift<128 and a<<shift<=MASK
        return ((a<<shift)>b)-((a<<shift)<b)
    shift=eb-ea;assert shift<128 and b<<shift<=MASK
    return (a>(b<<shift))-(a<(b<<shift))

def oracle(a,ea,b,eb):
    e=min(ea,eb);aa=a<<(ea-e);bb=b<<(eb-e)
    return (aa>bb)-(aa<bb)

def main():
    rng=random.Random(24292801);count=0
    directed=[(1,200,1,0),((1<<128)-1,-200,1,0),(1,127,1<<127,0),(0,300,1,-300)]
    for i in range(20000):
        a=rng.getrandbits(rng.randrange(1,129));b=rng.getrandbits(rng.randrange(1,129))
        ea=rng.randrange(-402,307);eb=rng.randrange(-402,307)
        # Half the set forces equal leading exponents, exercising safe alignment.
        if i%2==0 and a and b:eb=a.bit_length()+ea-b.bit_length()
        assert compare_scaled(a,ea,b,eb)==oracle(a,ea,b,eb);count+=1
    for x in directed:assert compare_scaled(*x)==oracle(*x)
    bad=(1,200,1,0)
    naive=((bad[0]<<(bad[1]-bad[3]))&MASK)>bad[2]
    assert not naive and compare_scaled(*bad)>0
    report={'scope':'Exact integer model only; no C/ASM or speed claim.','random_cases':count,'directed_cases':len(directed),
        'all_comparisons_match':True,'large_shift_truncation_mutant_caught':True,'max_coefficient_bits':128,
        'source_sha256':hashlib.sha256(Path(__file__).read_bytes()).hexdigest()}
    (HERE/'scaled-compare-results.json').write_text(json.dumps(report,indent=2)+'\n',encoding='utf-8')
    print(json.dumps(report,indent=2))

if __name__=='__main__':main()
