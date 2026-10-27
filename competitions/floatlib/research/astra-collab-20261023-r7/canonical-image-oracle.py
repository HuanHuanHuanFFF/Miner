from pathlib import Path
from datetime import datetime,timezone
import importlib.util,hashlib,json,random
HERE=Path(__file__).resolve().parent
sp=importlib.util.spec_from_file_location('word_oracle',HERE/'nonfinite-oracle.py');O=importlib.util.module_from_spec(sp);sp.loader.exec_module(O)
is_image=lambda w: not O.nan(w) or w==0x7fc00000
raw_nn=lambda w:(w & 0x7fffffff)<=0x7f800000
r=random.Random(2026102306);edge=[0,0x80000000,1,0x80000001,0x7fffff,0x800000,0x3f800000,0xbf800000,0x7f7fffff,0xff7fffff,0x7f800000,0xff800000,0x7fc00000]
words=edge+[r.getrandbits(32) for _ in range(100000)]
for w in words:assert raw_nn(w)==(not O.nan(w))
canonwords=[O.canon(w) for w in words];h=hashlib.sha256();opcases=0
for _ in range(50000):
    a=r.choice(canonwords);b=r.choice(canonwords)
    for op in [O.add,O.mul]:
        q=op(a,b);assert is_image(q) and q==O.native_model(op,a,b);opcases+=1;h.update(q.to_bytes(4,'little'))
nnwords=[w for w in words if not O.nan(w)];nnedge=edge[:-1];counts={'sum':0,'dot':0,'nan_results':0}
for n in [0,1,2,3,8,32,64]:
    for _ in range(500):
        a=[r.choice(nnedge) if r.randrange(3)==0 else r.choice(nnwords) for _ in range(n)]
        b=[r.choice(nnedge) if r.randrange(3)==0 else r.choice(nnwords) for _ in range(n)]
        rawsum=O.summation(a);nativesum=O.summation(a,lambda x,y:O.native_model(O.add,x,y))
        rawdot=O.dot(a,b);nativedot=O.dot(a,b,lambda x,y:O.native_model(O.add,x,y),lambda x,y:O.native_model(O.mul,x,y))
        assert rawsum==nativesum and rawdot==nativedot
        for name,q in [('sum',rawsum),('dot',rawdot)]:assert is_image(q);counts[name]+=1;counts['nan_results']+=int(O.nan(q));h.update(q.to_bytes(4,'little'))
q=0xffc12345;one=0x3f800000
cases=[('sum_opposite_inf',O.summation([0x7f800000,0xff800000,one])),('dot_invalid_then_inf',O.dot([0,0x7f800000],[0x7f800000,one])),('dot_overflow_opposite',O.dot([0x7f7fffff,0xff7fffff],[0x7f7fffff,0x7f7fffff]))]
out={'checked_at_utc':datetime.now(timezone.utc).isoformat(),'status':'PASS_FINITE_CANONICAL_IMAGE_MODEL','seed':2026102306,'raw_classifier_words':len(words),'canonical_image_operation_cases':opcases,'fold_cases':counts,'invalid_witnesses':{name:f'{v:08x}' for name,v in cases},'projection_not_raw_equality_counterexample':{'input_qnan':f'{q:08x}','raw_dot':f'{O.dot([q],[one]):08x}','native_canonical_dot':f'{O.dot([q],[one],lambda x,y:O.native_model(O.add,x,y),lambda x,y:O.native_model(O.mul,x,y)):08x}','product_non_signaling':not O.snan(O.mul(q,one)),'raw_result_in_image':is_image(O.dot([q],[one]))},'trace_sha256':h.hexdigest(),'oracle_sha256':hashlib.sha256((HERE/'nonfinite-oracle.py').read_bytes()).hexdigest(),'scope':'Finite exact integer/source model only. Native operations modeled by canonical projection, not hardware; raw equality/image assertions checked separately. Cannot replace W12 concrete operation image closure or real kernel acceptance/performance.'}
(HERE/'canonical-image-oracle.json').write_text(json.dumps(out,indent=2)+'\n');print(json.dumps(out,indent=2))
