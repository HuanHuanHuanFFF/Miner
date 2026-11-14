"""Read-only arithmetic analysis: binary64 mul+add does not implement binary32 FMA."""
from pathlib import Path
import hashlib,json,struct
HERE=Path(__file__).resolve().parent
def to_float(u):return struct.unpack('<f',struct.pack('<I',u))[0]
def as_word(x):
    try:return struct.unpack('<I',struct.pack('<f',x))[0]
    except OverflowError:return 0xff800000 if x<0 else 0x7f800000
def units(u):
    e=u>>23&255;f=u&0x7fffff
    assert e!=255
    n=f if e==0 else (0x800000+f)<<(e-1)
    return -n if u>>31 else n
def rne(n,shift):
    if shift<=0:return n<<(-shift)
    q,r=divmod(n,1<<shift)
    return q+int(r>(1<<(shift-1)) or r==(1<<(shift-1)) and q&1)
def exact_word(total):
    if total==0:return 0
    sign=0x80000000 if total<0 else 0;n=abs(total)
    leading=n.bit_length()-1-298
    if leading < -126:return sign|rne(n,149)
    q=rne(n,n.bit_length()-24)
    if q==1<<24:q>>=1;leading+=1
    if leading>127:return sign|0x7f800000
    return sign|((leading+127)<<23)|(q-0x800000)
def main():
    a,b=0x3f800001,0x3fc00000
    cases=[]
    for k in (54,60,80,120,149):
        z=as_word(-(2.0**(-k)))
        total=units(a)*units(b)+(units(z)<<149)
        exact=exact_word(total)
        double=as_word(to_float(a)*to_float(b)+to_float(z))
        cases.append({'x':hex(a),'scale':hex(b),'shift':hex(z),'negative_shift_power':k,
            'exact_single_RN32':hex(exact),'binary64_mul_add_then_RN32':hex(double),
            'difference':exact!=double,'total_at_2^-298_units':str(total)})
    assert all(c['difference'] for c in cases)
    result={'status':'COUNTEREXAMPLES','script_sha256':hashlib.sha256(Path(__file__).read_bytes()).hexdigest(),
        'cases':cases,'mechanism':'Exact product is a binary32 halfway value with even upper neighbor. A negative tiny binary32 addend moves below that midpoint but is lost in binary64 addition; the final rounding chooses the wrong neighbor.',
        'scope':'Exact integer finite analysis; not a Lean proof, new kernel, benchmark, or cross-width theorem.'}
    (HERE/'fma-double-counterexample.json').write_text(json.dumps(result,indent=2)+'\n',encoding='utf-8')
    print(json.dumps({'cases':len(cases),'all_differ':True,'first':cases[0]}))
if __name__=='__main__':main()
