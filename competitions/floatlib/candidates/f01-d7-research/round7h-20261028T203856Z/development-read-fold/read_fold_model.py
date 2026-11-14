"""Finite traversal/error falsifier, never a proof or native Lean benchmark."""
from pathlib import Path
from fractions import Fraction
import hashlib, json, math, random, struct

HERE = Path(__file__).resolve().parent
rng = random.Random(2240401)
p2 = lambda e: Fraction(1 << e) if e >= 0 else Fraction(1, 1 << -e)

def fused(reader, count, offset):
    acc = 0.0
    for i in range(offset, offset + count): acc += reader(i)
    return acc

tests = []
for c in range(160):
    count = rng.choice([0,1,2,3,7,16,31,64,129,257])
    offset = rng.randrange(8)
    k = rng.choice([-250,-126,-1,0,1,64,128,255,256])
    terms = [math.ldexp(rng.randrange(-2**20 + 1, 2**20), k-20) for _ in range(count)]
    trace = []
    def reader(i):
        trace.append(i)
        return terms[i-offset]
    got = fused(reader,count,offset)
    reference = 0.0
    for t in terms: reference += t
    assert struct.pack('d',got) == struct.pack('d',reference)
    assert trace == list(range(offset,offset+count))
    exact = sum(map(Fraction,terms),Fraction())
    L = max(0,(count-1).bit_length())
    assert all(abs(Fraction(x)) < p2(k) for x in terms)
    assert math.isfinite(got) and abs(Fraction(got)-exact) <= p2(k+2*L-53)
    tests.append({'count':count,'offset':offset,'k':k,'L':L})

pair_checks = 0
for _ in range(120):
    a = [struct.unpack('!f',struct.pack('!I',(rng.randrange(2)<<31)|(rng.randrange(1,255)<<23)|rng.randrange(1<<23)))[0] for _ in range(rng.randrange(1,40))]
    b = [struct.unpack('!f',struct.pack('!I',(rng.randrange(2)<<31)|(rng.randrange(1,255)<<23)|rng.randrange(1<<23)))[0] for _ in range(rng.randrange(1,40))]
    count = rng.randrange(60)
    def product(i): return (a[i] if i<len(a) else 0.0)*(b[i] if i<len(b) else 0.0)
    products = [product(i) for i in range(count)]
    for i,t in enumerate(products):
        exact = Fraction(a[i] if i<len(a) else 0.0)*Fraction(b[i] if i<len(b) else 0.0)
        assert Fraction(t)==exact
        pair_checks += 1
    got = fused(product,count,0)
    assert math.isfinite(got)
    L=max(0,(count-1).bit_length())
    assert abs(Fraction(got)-sum(map(Fraction,products),Fraction()))<=p2(256+2*L-53)

cancellation = [1.0,2.0**-55,-1.0]
rounded=fused(cancellation.__getitem__,3,0)
exact=sum(map(Fraction,cancellation),Fraction())
assert rounded==0 and exact==Fraction(1,2**55)
reordered=fused([1.0,-1.0,2.0**-55].__getitem__,3,0)
assert reordered!=rounded
result={'fragment_sha256':hashlib.sha256((HERE/'ReadFold.lean.inc').read_bytes()).hexdigest(),
    'scope':'Finite Python binary64/Fraction model and index trace only; not Lean/native codegen, FloatArray, raw32 full theorem or performance.',
    'read_cases':len(tests),'exact_product_checks':pair_checks,'array_cases':120,'index_visits':'Exactly offset..offset+count-1, one each',
    'negative_exactness':{'terms_hex':[x.hex() for x in cancellation],'actual_hex':rounded.hex(),'exact_fraction':str(exact),'reordered_hex':reordered.hex()},
    'tests':tests,'status':'FINITE_MODEL_PASS','Lean_typing':'NOT_RUN','native_cost':'NOT_RUN'}
(HERE/'model-results.json').write_text(json.dumps(result,indent=2)+'\n',encoding='utf-8')
print(json.dumps({k:result[k] for k in ['fragment_sha256','read_cases','exact_product_checks','array_cases','status']}))
