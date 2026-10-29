"""Tiny exact arithmetic discriminator; no new-track candidate or benchmark."""
from fractions import Fraction
from pathlib import Path
import json
import struct

HERE=Path(__file__).resolve().parent

def f32(x):
    return struct.unpack('<f',struct.pack('<f',float(x)))[0]

def word(x):
    return f'{struct.unpack("<I",struct.pack("<f",float(x)))[0]:08x}'

def one(name,a,b):
    exact=sum((Fraction(x)*Fraction(y) for x,y in zip(a,b)),Fraction())
    acc=f32(0)
    trace=[]
    for x,y in zip(a,b):
        product=f32(x*y)
        acc=f32(acc+product)
        trace.append({'a':word(x),'b':word(y),'rounded_product':word(product),'rounded_prefix':word(acc)})
    assert Fraction(f32(exact))==exact, 'Chosen result should be exactly representable'
    assert word(acc)!=word(exact), 'Counterexample did not distinguish boundaries'
    return {'name':name,'a_words':[word(x) for x in a],'b_words':[word(x) for x in b],
        'exact_rational':str(exact),'round_once_word':word(exact),'per_product_and_prefix_word':word(acc),'trace':trace}

def main():
    result={'scope':'Two small representable rational counterexamples to reusing old per-MAC F32 semantics for an exact round-once dot. Python finite arithmetic, not Lean proof or new-target runtime.',
        'examples':[
            one('prefix_rounding_loses_half_ulp',[1,2**-24,-1],[1,1,1]),
            one('product_rounding_loses_low_product',[1+2**-23,-1],[1-2**-23,1])
        ]}
    (HERE/'rounding-boundary-falsifier.json').write_text(json.dumps(result,indent=2)+'\n',encoding='utf-8')
    print(json.dumps(result,indent=2))

if __name__=='__main__':main()
