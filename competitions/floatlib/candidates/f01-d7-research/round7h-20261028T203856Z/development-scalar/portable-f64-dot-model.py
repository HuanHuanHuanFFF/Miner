"""Finite FP64 proposal/certificate oracle and frozen exploratory dot fixtures.

This models the new primitive; it does not execute Lean/C or prove its body.
"""
from pathlib import Path
from fractions import Fraction
import hashlib,importlib.util,json,math,random,struct
HERE=Path(__file__).resolve().parent
MASK32=(1<<32)-1;MASK64=(1<<64)-1;M=1<<23
def tofloat(w):return struct.unpack('<d',struct.pack('<Q',w))[0]
def tobits(x):return struct.unpack('<Q',struct.pack('<d',x))[0]
def p2(k):return Fraction(1<<k) if k>=0 else Fraction(1,1<<(-k))
def decode32(w):
    E=(w>>23)&255;f=w&0x7fffff
    return bool(w>>31),(M+f if E else f),max(0,E-1),E!=255
def widen_bits(w):
    sign=(w&0x80000000)<<32;E=(w>>23)&255;f=w&0x7fffff
    if not E:
        if not f:return sign
        L=f.bit_length()-1
        return sign|((L+874)<<52)|((f-(1<<L))<<(52-L))
    return sign|((E+896)<<52)|(f<<29)
def prepare(raw):
    values=[];peak=0;valid=True
    for w in raw:
        E=(w>>23)&255
        if E==255:valid=False;values.append(0.0)
        else:peak=max(peak,max(0,E-1));values.append(tofloat(widen_bits(w)))
    return {'raw':raw,'values':values,'maxIndex':peak,'valid':valid}
def proposal(w):
    mag=((((((w&0x7fffffffffffffff)+0x10000000)>>29)&MASK32)-0xc0000000)&MASK32)&0x7fffffff
    return ((w>>32)&0x80000000)|mag
def key(w):return (w^MASK64) if w>>63 else w^(1<<63)
def midpoints(q,naive_min=False):
    a=q&0x7fffffff;E=(a>>23)&255;f=a&0x7fffff
    base=((E+896)<<52)|(f<<29)
    dl=1<<(29 if a==0x00800000 and not naive_min else 28)
    lo=base-dl;hi=base+(1<<28)
    return ((hi|(1<<63)),(lo|(1<<63))) if q>>31 else (lo,hi)
def finite64(w):return w&0x7ff0000000000000!=0x7ff0000000000000
def certify(s,B,sw,q,naive_min=False):
    E=(q>>23)&255
    if E in (0,255):return False,'proposal_non_normal',None
    a=tobits(s-B);b=tobits(s+B)
    if not all(map(finite64,(sw,a,b))):return False,'nonfinite',None
    lo,hi=midpoints(q,naive_min)
    lower=key(lo)<key(a);upper=key(b)<key(hi)
    reason='accepted' if lower and upper else 'both_bounds' if not lower and not upper else 'lower_bound' if not lower else 'upper_bound'
    return lower and upper,reason,{'q':hex(q),'lower':hex(lo),'upper':hex(hi),'rlo':hex(a),'rhi':hex(b)}
def attempt(x,y,naive_min=False):
    n=len(x['raw'])
    if n==0 or n!=len(y['raw']):return 0,{'reason':'empty_or_mismatch'}
    if n>1<<30 or not(x['valid'] and y['valid']):return 0,{'reason':'invalid_input'}
    s=0.0
    for a,b in zip(x['values'],y['values']):s=s+a*b
    L=(n-1).bit_length();H=x['maxIndex']+y['maxIndex']
    B=tofloat((H+2*L+720)<<52);sw=tobits(s);q=proposal(sw)
    ok,reason,details=certify(s,B,sw,q,naive_min)
    return (q if ok else 0),{'reason':reason,'sum_word':hex(sw),'radius_word':hex(tobits(B)),'H':H,'L':L,'details':details,'sum':s,'radius':B}
def exact_dot(x,y,ref):
    if len(x)!=len(y):return 0x7fc00000,None
    terms=[];negative_zero=bool(x)
    for a,b in zip(x,y):
        sa,ma,ia,fa=decode32(a);sb,mb,ib,fb=decode32(b)
        if not(fa and fb):return 0x7fc00000,None
        p=ma*mb;negative_zero=negative_zero and not p and(sa!=sb)
        if p:terms.append(((-p if sa!=sb else p),ia+ib))
    if not terms:return (0x80000000 if negative_zero else 0),Fraction(0)
    low=min(i for _,i in terms);N=sum(v<<(i-low) for v,i in terms)
    if not N:return 0,Fraction(0)
    return ref.actual_word(N<0,abs(N),1,low-298),Fraction(N)*p2(low-298)
def load_ref():
    p=HERE/'quotient-boundary/model-preflight.py';s=importlib.util.spec_from_file_location('round_reference',p);r=importlib.util.module_from_spec(s);s.loader.exec_module(r);return r
def run_case(case,ref,check_bound=True):
    x,y=case['x'],case['y'];px,py=prepare(x),prepare(y);q,obs=attempt(px,py)
    exact,value=exact_dot(x,y,ref)
    if q:assert q==exact,(case['name'],hex(q),hex(exact),obs)
    if value is not None and x and len(x)==len(y) and check_bound:
        assert abs(Fraction.from_float(obs['sum'])-value)<=Fraction.from_float(obs['radius']),case['name']
    obs={k:v for k,v in obs.items() if k not in ('sum','radius')}
    return {**case,'expected':exact,'fast_result':q,'observation':obs}
def random_word(rng,lo,hi):return (rng.getrandbits(1)<<31)|(rng.randint(lo,hi)<<23)|rng.getrandbits(23)
def main():
    ref=load_ref();decoder_count=0
    for E in range(255):
        for f in (0,1,2,3,(1<<22)-1,1<<22,(1<<23)-2,(1<<23)-1):
            for sign in (0,1):
                w=(sign<<31)|(E<<23)|f;s,m,i,_=decode32(w);value=Fraction(-m if s else m)*p2(i-149)
                assert Fraction.from_float(tofloat(widen_bits(w)))==value
                assert tobits(tofloat(widen_bits(w)))>>63==sign
                decoder_count+=1
    rng=random.Random(24282401)
    for _ in range(100000):
        w=random_word(rng,0,254);s,m,i,_=decode32(w)
        assert Fraction.from_float(tofloat(widen_bits(w)))==Fraction(-m if s else m)*p2(i-149);decoder_count+=1
    cases=[]
    for seed in (24282403,24282405):
        rng=random.Random(seed)
        for n in (1,2,4,8,16,32,64,128,256,512,1024):
            for kind,lo,hi in (('narrow',120,132),('moderate',105,145),('wide',1,254)):
                cases.append({'name':f's{seed}-{kind}-n{n}','group':str(seed),'kind':kind,'x':[random_word(rng,lo,hi) for _ in range(n)],'y':[random_word(rng,lo,hi) for _ in range(n)]})
    directed=[
        ('empty',[],[]),('mismatch',[0x3f800000],[]),
        ('plus-zero',[0,0],[0x3f800000,0x40000000]),
        ('all-negative-zero',[0x80000000,0x80000000],[0x3f800000,0x40000000]),
        ('cancel',[0x3f800000,0x3f800000],[0x3f800000,0xbf800000]),
        ('lost-small-cancel',[0x7f000000,0x3f800000,0x7f000000],[0x3f800000,0x3f800000,0xbf800000]),
        ('half-ulp-even-tie',[0x3f800000,0x33800000],[0x3f800000,0x3f800000]),
        ('half-ulp-other-tie',[0x3f800001,0x33800000],[0x3f800000,0x3f800000]),
        ('min-normal',[0x00800000],[0x3f800000]),
        ('min-normal-lower-fix',[0x00800000,0x00000001],[0x3f800000,0xbe800000]),
        ('power-lower-inside',[0x3f800000,0x32800000],[0x3f800000,0xbf800000]),
        ('smallest-subnormal',[1],[0x3f800000]),
        ('subnormal-times-large',[1],[0x7f7fffff]),
        ('subnormal-normal-sum',[0x007fffff,0x00800000],[0x7f7fffff,0x3f800000]),
        ('overflow-product',[0x7f7fffff],[0x7f7fffff]),
        ('huge-cancel',[0x7f7fffff,0x7f7fffff],[0x7f7fffff,0xff7fffff]),
        ('positive-inf',[0x7f800000],[0x3f800000]),('nan',[0x7fc00001],[0x3f800000]),
        ('zero-summary-inflation',[0,0x3f800000],[0x7f7fffff,0x3f800000]),
        ('negative-normal',[0xbf800000,0xbf000000],[0x3f800000,0x3f000000])]
    cases += [{'name':name,'group':'directed','kind':name,'x':x,'y':y} for name,x,y in directed]
    results=[run_case(c,ref) for c in cases]
    selected=next(c for c in results if c['name']=='min-normal-lower-fix')
    correct=selected['fast_result'];naive,_=attempt(prepare(selected['x']),prepare(selected['y']),True)
    assert correct==0x00800000 and naive==0
    # More independent finite-oracle cases, not additional timing inputs.
    rng=random.Random(24282407);extra=0;accepted_extra=0
    for i in range(12000):
        n=rng.choice((1,2,3,4,8,16,32,64));lo,hi=rng.choice(((0,254),(110,140),(1,10),(240,254)))
        c={'name':f'finite-model-{i}','x':[random_word(rng,lo,hi) for _ in range(n)],'y':[random_word(rng,lo,hi) for _ in range(n)]}
        out=run_case(c,ref);extra+=1;accepted_extra+=bool(out['fast_result'])
    groups={}
    for c in results:
        g=groups.setdefault(c['group'],{'cases':0,'accepted':0,'miss_reasons':{},'words':0})
        g['cases']+=1;g['accepted']+=bool(c['fast_result']);g['words']+=len(c['x'])+len(c['y']);reason=c['observation']['reason'];g['miss_reasons'][reason]=g['miss_reasons'].get(reason,0)+1
    body=HERE/'PortableF64Dot.lean.inc';raw=body.read_bytes();assert b'toFloat32' not in raw and b'UInt64.log2' not in raw
    fixtures={'schema':'r24-portable-dot-cost-v1','source_sha256':hashlib.sha256(raw).hexdigest(),'seeds':[24282403,24282405],
        'sample_role':'EXPLORATION_COMPONENT_COST','cases':results,
        'policy':'Portable old ContractTensor primitive only. Finite exact sum rounded once, all-negative-zero=>-0, cancellation=>+0; mismatch/nonfinite unsupported canonicalNaN research policy. No ContractExact kernels/official special-value payload claim.'}
    fixture_raw=(json.dumps(fixtures,separators=(',',':'))+'\n').encode();(HERE/'portable-f64-dot-fixtures.json').write_bytes(fixture_raw)
    report={'status':'FINITE_F64_DOT_MODEL_PASS_LEAN_NATIVE_COST_NOT_RUN','source_sha256':hashlib.sha256(raw).hexdigest(),'source_bytes':len(raw),
        'decoder_cases':decoder_count,'fixture_cases':len(results),'groups':groups,'extra_finite_oracle_cases':extra,'extra_accepted':accepted_extra,
        'fixture_bytes':len(fixture_raw),'fixture_sha256':hashlib.sha256(fixture_raw).hexdigest(),
        'minnormal_fix_counterexample':{'name':selected['name'],'correct_fast':hex(correct),'naive_fast':hex(naive),'expected':hex(selected['expected'])},
        'H_policy':'Separable max index(E-1,0) summaries include zero input entries; no paired nonzero oracle.',
        'Lean':'NOT_RUN','universal_fastpath_proof':'NOT_RUN','actual_C_ASM':'NOT_RUN','native_checksums':'NOT_RUN','cost':'NOT_RUN',
        'scope':'Finite Python IEEE64/word/exact-integer model; accepted-case counts are not workload probabilities or speed estimates. Original four public functions remain B2 in the future composed diagnostic source.'}
    (HERE/'portable-f64-dot-model.json').write_bytes((json.dumps(report,indent=2)+'\n').encode())
    print(json.dumps(report,indent=2))
if __name__=='__main__':main()
