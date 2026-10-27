"""Independent host binary32 corroboration of two explicit finite witnesses."""
from pathlib import Path
import datetime, json, math, struct
HERE=Path(__file__).resolve().parent
def val(u): return struct.unpack('<f',struct.pack('<I',u))[0]
def bits(x):
    try: return struct.unpack('<I',struct.pack('<f',x))[0]
    except OverflowError: return 0xff800000 if x<0 else 0x7f800000
def mul(a,b): return bits(val(a)*val(b))
def add(a,b): return bits(val(a)+val(b))
def dot(a,b):
    acc=0
    for x,y in zip(a,b): acc=add(acc,mul(x,y))
    return acc
a=0x3f800001; b0=0x3f800000; b1=0xbf7ffffe
left=dot([a,a],[b0,b1]); right=mul(a,add(b0,b1))
assert (left,right)==(0x34000000,0x34000001)
A=[0x00800000]*2; B=[0x33800000,0x3f800001]
old=dot(A,B); scaledA=[mul(x,0x40000000) for x in A]
scaledOld=mul(old,0x40000000); new=dot(scaledA,B)
assert (old,scaledOld,new)==(0x00800001,0x01000001,0x01000002)
assert all(1<=(x>>23)&255<=254 for x in A+B+scaledA+[old,scaledOld,new])
out={'at_utc':datetime.datetime.now(datetime.timezone.utc).isoformat(),'scope':'Independent host binary32 corroboration of exact finite witnesses only. No Lean, all-input theorem or performance.',
 'distributivity':{'lhs':hex(left),'rhs':hex(right),'different':True},
 'power_two_endpoint_normal_is_insufficient':{'original_dot':hex(old),'scale_after_dot':hex(scaledOld),'dot_after_scaling_inputs':hex(new),'all_inputs_and_endpoints_normal':True,'first_product_original':hex(mul(A[0],B[0])),'first_product_scaled':hex(mul(scaledA[0],B[0]))},
 'decision':'Factorization and scaled-row reuse need every intermediate rounding obligation; normal inputs/endpoints alone do not suffice.'}
(HERE/'semantic-counterexamples-independent-review.json').write_text(json.dumps(out,indent=2)+'\n',encoding='utf-8')
print(json.dumps(out))
