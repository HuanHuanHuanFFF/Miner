"""Portable exact product representation model, no new-track/old runtime kernel."""
from pathlib import Path
import hashlib
import json
import math
import random
import struct
from fractions import Fraction

HERE=Path(__file__).resolve().parent

def fields(w):
    exp=(w>>23)&255
    if exp==255:return None
    return (((w&0x7fffff)|(0x800000 if exp else 0)),max(exp-1,0),(w>>31)&1)

def product(a,b):
    af,bf=fields(a),fields(b)
    if af is None or bf is None:return None
    ma,ia,sa=af;mb,ib,sb=bf
    m=ma*mb;i=ia+ib
    assert m<1<<48 and i<=506
    scale_bits=(i+725)<<52
    scale=struct.unpack('<d',struct.pack('<Q',scale_bits))[0]
    value=float(m)*scale
    if sa^sb:value=-value
    exact=Fraction(m)*(Fraction(1<< (i-298)) if i>=298 else Fraction(1,1<<(298-i)))
    if sa^sb:exact=-exact
    assert Fraction(value)==exact
    bits=struct.unpack('<Q',struct.pack('<d',value))[0]
    if not m:assert bits>>63==sa^sb
    assert math.isfinite(value) and (value==0 or abs(value)>=2.0**-298)
    return {'bits':f'{bits:016x}','mantissa_bits':m.bit_length(),'scale_index':i}

def main():
    rng=random.Random(24293217);count=0;directed=[]
    for _ in range(20000):
        a=(rng.getrandbits(1)<<31)|(rng.randrange(255)<<23)|rng.getrandbits(23)
        b=(rng.getrandbits(1)<<31)|(rng.randrange(255)<<23)|rng.getrandbits(23)
        product(a,b);count+=1
    for a,b in [(1,1),(0x7f7fffff,0x7f7fffff),(0x80000000,0x3f800000),(0,0xbf800000),(0x00800000,1),(0x3f800001,0x3f7ffffe)]:
        directed.append({'a':f'{a:08x}','b':f'{b:08x}','result':product(a,b)})
    for a in (0x7f800000,0xff800000,0x7fc00001):assert product(a,0x3f800000) is None
    header=HERE.parents[1]/'round1h-20261023T110107Z/runtime-boundary/lean.h.raw'
    # Locate the existing old runtime evidence without writing it.
    root=next(p for p in HERE.parents if (p/'competitions/floatlib/pins.json').is_file())
    header=root/'competitions/floatlib/candidates/f01-d7-research/round1h-20261023T110107Z/runtime-boundary/lean.h.raw'
    assert hashlib.sha256(header.read_bytes()).hexdigest()=='982c731a1fbacc7688006f44f9f7af9d9e3e0247d310a728827f49e7f1466c13'
    report={'scope':'Finite exact representation model only. No Lean proof, runtime implementation, target cost, kernel or CI.',
        'source_sha256':hashlib.sha256(Path(__file__).read_bytes()).hexdigest(),'finite_random_pairs':count,'directed':directed,
        'special_inputs_return_fallback':True,'header_sha256':hashlib.sha256(header.read_bytes()).hexdigest(),
        'header_facts':{'UInt64_to_Float':'static inline C cast, line3189','Float_add_mul_negate':'static inline, lines3178/3180/3182','Float_to_bits':'exported ordinary call, line3177'}}
    (HERE/'product64-results.json').write_text(json.dumps(report,indent=2)+'\n',encoding='utf-8')
    print(json.dumps(report,indent=2))

if __name__=='__main__':main()
