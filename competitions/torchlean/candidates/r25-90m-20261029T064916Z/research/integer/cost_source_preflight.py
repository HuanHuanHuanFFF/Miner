"""Finite word-level preflight of the frozen C cost fixture and recurrences.

This parses the generated header and independently compares each algorithm's
word recurrence and integer rounder to saved exact-rational expected words.
It does NOT compile, execute or time C, and does not validate compiler behavior.
"""
from pathlib import Path
import datetime
import hashlib
import json
import re

HERE=Path(__file__).resolve().parent
FROZEN_C='cc1c1bfb03470581d3bf6293ee97335114d38e6ad27d4cef15e0464b1af49369'
M64=1<<64;MASK64=M64-1;M128=1<<128;MASK128=M128-1


def signed(q,bits):return q if q<1<<(bits-1) else q-(1<<bits)


def fields(w):
    e=(w>>23)&255
    assert e!=255
    return bool(w>>31),(w&0x7fffff)+(0x800000 if e else 0),max(e-1,0)


def align(words):
    fs=[fields(w) for w in words]
    es=[e for _,v,e in fs if v]
    low=min(es) if es else 0;span=max(es)-low if es else 0
    assert span<=15
    return [((-(v<<(e-low)) if neg else v<<(e-low)) if v else 0)&MASK64
            for neg,v,e in fs],low,span


def carry2(a,b):
    al=ah=bl=bh=0
    for u,v in zip(a,b):
        q=(u*v)&MASK64;lo=(al+q)&MASK64
        hi=(ah-(q>>63)+(lo<al))&MASK64
        al,ah,bl,bh=bl,bh,lo,hi
    lo=(al+bl)&MASK64;hi=(ah+bh+(lo<al))&MASK64
    return signed((hi<<64)|lo,128)


def block16(a,b):
    total=0
    for start in range(0,len(a),16):
        s0=s1=0;end=min(len(a),start+16);i=start
        while i+1<end:
            s0=(s0+a[i]*b[i])&MASK64;s1=(s1+a[i+1]*b[i+1])&MASK64;i+=2
        if i<end:s0=(s0+a[i]*b[i])&MASK64
        total=(total+signed((s0+s1)&MASK64,64))&MASK128
    return signed(total,128)


def buckets(a,b):
    pos=neg=0
    for u,v in zip(a,b):
        q=(u*v)&MASK64
        if q>>63:
            nxt=(neg+((-q)&MASK64))&MASK64
            if nxt<neg:return carry2(a,b),True
            neg=nxt
        else:
            nxt=(pos+q)&MASK64
            if nxt<pos:return carry2(a,b),True
            pos=nxt
    return pos-neg,False


def round_c(value,e):
    if not value:return 0
    assert abs(value)<1<<127
    sign=0x80000000 if value<0 else 0;m=abs(value)
    log=m.bit_length()-1;shift=max(log-23,-149-e);unit=e+shift
    if shift>=128:q=0
    elif shift>0:
        q=m>>shift;rem=m&((1<<shift)-1);half=1<<(shift-1)
        if rem>half or (rem==half and q&1):q+=1
    else:q=m<<(-shift)
    if not q:return sign
    if q==1<<24:q>>=1;unit+=1
    if unit==-149 and q<1<<23:return sign|q
    field=unit+150
    if field>=255:return sign|0x7f800000
    assert 1<=field<=254 and 1<<23<=q<1<<24
    return sign|(field<<23)|(q-0x800000)


def run():
    c=HERE/'integer_cost_probe_relu.c';h=HERE/'integer_cost_fixture.h'
    assert hashlib.sha256(c.read_bytes()).hexdigest()==FROZEN_C
    arrays={name:[int(x,16) for x in re.findall(r'0x([0-9a-f]{8})u',body)]
            for name,n,body in re.findall(r'static uint32_t (\w+)\[(\d+)\] = \{(.*?)\};',h.read_text(),re.S)}
    assert len(arrays)==8
    checks=[]
    for case in range(2):
        x,lx,sx=align(arrays[f'input_{case}']);n=len(x)
        w=arrays[f'weight_{case}'];bias=arrays[f'bias_{case}'];expected=arrays[f'expected_{case}']
        assert n==608 and len(bias)==len(expected)==80 and len(w)==608*80
        for j in range(80):
            y,ly,sy=align(w[j*n:(j+1)*n]);assert 48+sx+sy<=59
            neg,v,idx=fields(bias[j]);shift=idx+149-lx-ly
            assert 0<=shift<=102 and v<<shift<1<<126
            b=-(v<<shift) if neg else v<<shift
            outputs=[]
            q0=carry2(x,y);q1=block16(x,y);q2,fallback=buckets(x,y)
            assert q0==q1==q2 and not fallback
            for total in (q0,q1,q2):
                word=round_c(total+b,lx+ly-298)
                assert word==expected[j]
                outputs.append(0 if word>>31 else word)
            assert len(set(outputs))==1
        checks.append({'case':case,'outputs':80,'algorithms':3,'word_comparisons':240,
                       'mismatches':0,'bucket_fallbacks':0,'relu_equal':True})
    # The actual checked-bucket recurrence must reach fallback on this sequence.
    aa=[0xffffff]*65;bb=[0xffffff<<11]*33+[(-(0xffffff<<11))&MASK64]*32
    value,fallback=buckets(aa,bb)
    assert fallback and value==carry2(aa,bb)==block16(aa,bb)
    out={'at_utc':datetime.datetime.now(datetime.timezone.utc).isoformat(),
         'status':'PYTHON_WORD_PREFLIGHT_NOT_C_EXECUTION',
         'c_source_sha256':FROZEN_C,'header_sha256':hashlib.sha256(h.read_bytes()).hexdigest(),
         'preflight_sha256':hashlib.sha256(Path(__file__).read_bytes()).hexdigest(),
         'checks':checks,'overflow_fallback_counterexample':True,
         'limits':['No C compilation/codegen/undefined-behavior/runtime/timing conclusion.',
                   'Exact-rational oracle and header producer are pinned by cost-fixture-receipt.json.',
                   'Only published finite first-layer fixtures and one fixed overflow case.']}
    (HERE/'cost-source-preflight.json').write_text(json.dumps(out,indent=2)+'\n',encoding='utf-8',newline='\n')
    print(json.dumps({'status':out['status'],'checks':checks,'overflow_fallback_counterexample':True}))


if __name__=='__main__':run()
