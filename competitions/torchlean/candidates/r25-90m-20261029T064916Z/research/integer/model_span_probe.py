"""Finite discriminator on the pinned public ExactSuite MLP, not a benchmark.

Independent Python integer implementation of the published distribution and exact
binary32 arithmetic. No third-party incumbent implementation is copied here.
Only seed 42, batch 1, legacy MLP and its actual three layers are inspected.
"""
from pathlib import Path
from fractions import Fraction
from collections import Counter
import datetime
import hashlib
import json
import math
import struct

HERE = Path(__file__).resolve().parent
ROOT = HERE.parents[5]
OLD = ROOT / 'competitions/floatlib/candidates/f01-d7-research/round7h-20261028T203856Z'
SUITE = OLD / 'development-broad/torchlean-source/lean/bench/ExactSuite.lean'
CONTRACT = OLD / 'source-snapshot/torchlean/lean/contract/ContractExact.lean'
MASK = 2**32 - 1
ONE = 0x3f800000


def lcg(n, seed):
    out=[]
    for _ in range(n):
        seed = (seed * 1664525 + 1013904223) & MASK
        out.append(seed)
    return out


def gen(kind, n, seed):
    out=[]
    for w in lcg(n, seed):
        e = 87 + (w >> 23) % 40 if kind == 'wide' else 121 + (w >> 23) % 6
        out.append(0 if kind == 'sparse' and ((w >> 9) & 1) == 0
                   else (w & 0x807fffff) | (e << 23))
    return out


def decode(w):
    e,f=(w >> 23) & 255,w & 0x7fffff
    assert e != 255
    return (-1 if w >> 31 else 1), ((1 << 23) + f if e else f), max(e-1,0)


def rational(w):
    s,m,k=decode(w)
    return s * Fraction(m) * Fraction(2)**(k-149)


def round_rat(value, negzero=False):
    if value == 0:
        return 0x80000000 if negzero else 0
    sign=0x80000000 if value < 0 else 0
    n,d=abs(value.numerator),value.denominator
    e=n.bit_length()-d.bit_length()
    if e >= 0:
        if n < d << e: e-=1
    elif n << (-e) < d:
        e-=1
    unit=max(-149,e-23)
    a,b=(n,d << unit) if unit >= 0 else (n << (-unit),d)
    q,r=divmod(a,b)
    if 2*r > b or (2*r == b and q % 2): q+=1
    if q == 0: return sign
    if q == 1 << 24:
        q >>= 1
        unit += 1
    if unit == -149 and q < 1 << 23: return sign | q
    ef=unit+150
    if ef >= 255: return sign | 0x7f800000
    assert 1 <= ef <= 254 and 1 << 23 <= q < 1 << 24
    return sign | (ef << 23) | (q-(1 << 23))


def weights(kind, seed, k, fanin, n):
    scale=round_rat(Fraction(4,max(1,math.isqrt(fanin))))
    return [round_rat(rational(w)*rational(scale))
            for w in gen('sparse' if kind == 'sparse' else 'normal',n,(seed+101*k)&MASK)]


def biases(seed,k,n):
    return [round_rat(rational(w)/256) for w in gen('normal',n,(seed+101*k)&MASK)]


def span_probe(x,y):
    ds=[(decode(a),decode(b)) for a,b in zip(x,y)]
    active=[(sa*sb,ma*mb,ia+ib) for (sa,ma,ia),(sb,mb,ib) in ds if ma and mb]
    if not active:
        return {'active':0},0
    lo=min(k for _,_,k in active)
    terms=[s*(m << (k-lo)) for s,m,k in active]
    total=sum(terms)
    bound=sum(abs(t) for t in terms)
    span=max(k for _,_,k in active)-lo
    xs=[d for d,_ in ds if d[1]]; ys=[d for _,d in ds if d[1]]
    lx=min(k for _,_,k in xs); ly=min(k for _,_,k in ys)
    ax=[m << (k-lx) for _,m,k in xs]; ay=[m << (k-ly) for _,m,k in ys]
    # Cached per-vector certificate, expressed at the pair's dyadic base.
    cached_bound=min(sum(ax)*max(ay),sum(ay)*max(ax))
    delta=lo-lx-ly
    cached_bound=(cached_bound+(1 << delta)-1) >> delta
    oldbits=48+(max(k for _,_,k in xs)-lx)+(max(k for _,_,k in ys)-ly)+(len(x)-1).bit_length()
    pairbits=48+span+(len(active)-1).bit_length()
    modular=sum(t & ((1<<64)-1) for t in terms)&((1<<64)-1)
    signed=modular if modular < 1<<63 else modular-(1<<64)
    # Primitive signed64 summation can overflow internally; modulo arithmetic is
    # still exact if a separate guard proves the final total is in signed range.
    l1fits=bound < 1<<63
    if l1fits: assert signed == total
    prefix=0; maxprefix=0
    for t in terms:
        prefix+=t; maxprefix=max(maxprefix,abs(prefix))
    out=round_rat(Fraction(total)*Fraction(2)**(lo-298))
    stats={'n':len(x),'active':len(active),'pair_base':lo,'pair_span':span,
           'old_guard_bits':oldbits,'pair_guard_bits':pairbits,
           'l1_bits':bound.bit_length(),'sum_abs':str(bound),'exact_total':str(total),
           'sum_bits':abs(total).bit_length(),'max_prefix_bits':maxprefix.bit_length(),
           'cached_l1_linf_bits':cached_bound.bit_length(),
           'old62':oldbits <= 62,'old63':oldbits <= 63,'pair63':pairbits <= 63,
           'l1_63':l1fits,'cached_63':cached_bound < 1<<63,
           'pair128':pairbits <= 127,'output_word':out}
    return stats,out


def run():
    seed=42
    r=lcg(8,seed ^ 0x5bd1e995)
    widths=[256+r[0]%529,64+r[1]%193,32+r[2]%97,10]
    records=[]; checks=[]
    for kind in ('normal','wide','sparse'):
        x=gen(kind,widths[0],seed+999)
        for layer,(ni,no) in enumerate(zip(widths,widths[1:])):
            w=weights(kind,seed,2*layer,ni,ni*no)
            b=biases(seed,2*layer+1,no)
            result=[]
            for j in range(no):
                xx=x+[ONE]; yy=w[j*ni:(j+1)*ni]+[b[j]]
                stats,out=span_probe(xx,yy)
                body,_=span_probe(x,w[j*ni:(j+1)*ni])
                stats.update(kind=kind,layer=layer,output=j,body=body)
                records.append(stats)
                if j == 0:
                    direct=sum((rational(a)*rational(c) for a,c in zip(xx,yy)),Fraction())
                    assert round_rat(direct) == out
                    checks.append({'kind':kind,'layer':layer,'direct_fraction_equal':True,
                                   'input_sha256':hashlib.sha256(b''.join(struct.pack('<I',z) for z in xx+yy)).hexdigest()})
                result.append(0 if layer < 2 and out >> 31 else out)
            x=result
    summaries=[]
    for kind in ('normal','wide','sparse'):
        for layer in range(3):
            rs=[r for r in records if r['kind']==kind and r['layer']==layer]
            keys=('old62','old63','pair63','l1_63','cached_63','pair128')
            summaries.append({'kind':kind,'layer':layer,'dots':len(rs),'terms':rs[0]['n'],
                              'accepted':{k:sum(z.get(k,False) for z in rs) for k in keys},
                              'body_accepted':{k:sum(z['body'].get(k,False) for z in rs) for k in keys},
                              'l1_bit_range':[min(z['l1_bits'] for z in rs),max(z['l1_bits'] for z in rs)],
                              'pair_span_range':[min(z['pair_span'] for z in rs),max(z['pair_span'] for z in rs)]})
    receipt={'at_utc':datetime.datetime.now(datetime.timezone.utc).isoformat(),
             'status':'FINITE_PUBLIC_MODEL_MIRROR_NOT_LEAN_OR_TIMING',
             'official_commit':'accb82b6e2adeda1b41a57a260d68fb3879c427e',
             'suite_sha256':hashlib.sha256(SUITE.read_bytes()).hexdigest(),
             'contract_sha256':hashlib.sha256(CONTRACT.read_bytes()).hexdigest(),
             'probe_sha256':hashlib.sha256(Path(__file__).read_bytes()).hexdigest(),
             'seed':seed,'profile':'legacy','batch':1,'widths':widths,
             'arithmetic':'Exact rational generator scaling and exact dot with one binary32 nearest-even rounding; zero handling limited to these finite nonempty fixtures.',
             'independent_fraction_checks':checks,'summaries':summaries,'records':records,
             'limits':['Exploratory public distribution; no unseen confirmation set.',
                       'Only MLP, seed42, batch1. No claim about hidden board weighting or current champion.',
                       'No Lean execution, native compiler, timing or gate; mirror equivalence to Lean generator is statically reviewed only.',
                       'Exact L1 acceptance is an oracle opportunity bound; it costs a pair-dependent product scan and is not a free runtime guard.']}
    (HERE/'model-span-probe.json').write_text(json.dumps(receipt,indent=2)+'\n',encoding='utf-8',newline='\n')
    print(json.dumps({'widths':widths,'summaries':summaries},indent=2))


if __name__ == '__main__':
    run()
