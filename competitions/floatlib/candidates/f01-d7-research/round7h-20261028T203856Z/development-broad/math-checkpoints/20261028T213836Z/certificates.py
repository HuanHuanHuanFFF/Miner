"""Read-only mathematical discriminators, not a TorchLean kernel or benchmark.

Arbitrary native guesses are accepted only by exact rational certificates.
The dot enclosure additionally assumes IEEE binary64 nearest-even operations.
"""
from fractions import Fraction
from pathlib import Path
import collections
import hashlib
import json
import math
import random
import struct
import time

HERE=Path(__file__).resolve().parent

def pow2(e):
    return Fraction(1 << e) if e>=0 else Fraction(1,1 << -e)

def f32_word(w):
    return struct.unpack('<f',struct.pack('<I',w))[0]

def float_word(f):
    try:return struct.unpack('<I',struct.pack('<f',f))[0]
    except OverflowError:return 0xff800000 if f<0 else 0x7f800000

def parts(w):
    e=(w>>23)&255;f=w&0x7fffff
    assert e!=255
    return (-1 if w>>31 else 1)*((1<<23)+f if e else f), (e-1 if e else 0)-149

def value(w):
    m,e=parts(w);return m*pow2(e)

def shift_even(n,shift):
    if shift<=0:return n<<-shift
    q,r=divmod(n,1<<shift);half=1<<(shift-1)
    return q+(r>half or (r==half and bool(q&1)))

def rn_dyadic(integer,e):
    if integer==0:return 0
    sign=0x80000000 if integer<0 else 0;integer=abs(integer)
    top=integer.bit_length()-1+e
    if top < -126:
        return sign|shift_even(integer,-149-e)
    q=shift_even(integer,top-23-e)
    if q==(1<<24):q>>=1;top+=1
    if top>127:return sign|0x7f800000
    return sign|((top+127)<<23)|(q-(1<<23))

def rn_fraction(q):
    # Used here only for dyadic dot enclosures, not generic rational rounding.
    d=q.denominator;assert d&(d-1)==0
    return rn_dyadic(q.numerator,-(d.bit_length()-1))

def rn_rational(q):
    if q==0:return 0
    sign=0x80000000 if q<0 else 0;q=abs(q)
    n,d=q.numerator,q.denominator
    top=n.bit_length()-d.bit_length()
    if (n < d<<top) if top>=0 else (n<<-top < d):top-=1
    target=max(top-23,-149)
    if target>=0:den=d<<target;num=n
    else:num=n<<-target;den=d
    m,r=divmod(num,den);m+=2*r>den or (2*r==den and bool(m&1))
    return sign|rn_dyadic(m,target)

def cell(w):
    """Finite nonzero normal candidate; strict interior avoids all tie rules."""
    a=w&0x7fffffff
    if a<0x00800000 or a>0x7f7fffff:return None
    if w>>31:
        prev,nxt=(-pow2(128) if a==0x7f7fffff else value(w+1)),value(w-1)
    else:prev,nxt=value(w-1),(pow2(128) if a==0x7f7fffff else value(w+1))
    v=value(w)
    return (prev+v)/2,(v+nxt)/2

def dot_model(a,b):
    exact=0;s=0.0;emax=None
    for wa,wb in zip(a,b):
        ma,ea=parts(wa);mb,eb=parts(wb)
        p=ma*mb
        exact+=p<<(ea+eb+298)
        product=f32_word(wa)*f32_word(wb)  # Exact: <=48 significant bits.
        s=s+product                     # Separate operation, no FMA.
        if p:
            e=p.__abs__().bit_length()-1+ea+eb
            emax=e if emax is None else max(emax,e)
    n=len(a);truth=rn_dyadic(exact,-298);guess=float_word(s)
    if not n or emax is None:
        return {'n':n,'accepted':False,'reason':'zero/sign domain kept for fallback','truth':truth,'guess':guess}
    ceiln=(n-1).bit_length()
    bound=pow2(emax+2*ceiln-52)
    s_exact=Fraction(s)
    error=abs(s_exact-exact*pow2(-298))
    assert error<=bound,'Binary64 enclosure falsified'
    c=cell(guess)
    ok=c is not None and c[0]<s_exact-bound and s_exact+bound<c[1]
    if ok:assert guess==truth,'Unsound exact cell acceptance'
    return {'n':n,'accepted':ok,'truth':truth,'guess':guess,'blind_guess_correct':guess==truth,
        'bound_exponent':emax+2*ceiln-52,'error_bound_valid':True,
        'error_bound_over_ulp32':float(bound/pow2(((guess>>23)&255)-127-23)) if c else None,
        'enclosure_exact':str(error),'reason':'accepted' if ok else 'ambiguous/outside guarded output cell'}

def f32_filter_model(a,b):
    # Conservative four*n^2*u32*M bound, only normal-or-zero intermediate domain.
    exact=0;s=0.0;emax=None;domain=True
    for wa,wb in zip(a,b):
        ma,ea=parts(wa);mb,eb=parts(wb);p=ma*mb
        exact+=p<<(ea+eb+298)
        try:
            product=f32_word(float_word(f32_word(wa)*f32_word(wb)))
            s=f32_word(float_word(s+product))
        except (OverflowError,ValueError):domain=False;break
        for v in (product,s):
            vw=float_word(v);domain &= (vw&0x7fffffff)==0 or 1<=((vw>>23)&255)<=254
        if p:
            e=abs(p).bit_length()-1+ea+eb;emax=e if emax is None else max(emax,e)
    if not domain or emax is None:return {'accepted':False,'domain':False}
    n=len(a);bound=pow2(emax+2*(n-1).bit_length()-21);truth=rn_dyadic(exact,-298)
    assert abs(Fraction(s)-exact*pow2(-298))<=bound
    guess=float_word(s);c=cell(guess)
    ok=c is not None and c[0]<Fraction(s)-bound and Fraction(s)+bound<c[1]
    assert not ok or guess==truth
    return {'accepted':ok,'domain':True}

def draw(rng,n,kind):
    out=[]
    for _ in range(n):
        exponent=rng.randrange(87,127) if kind=='wide' else rng.randrange(121,127)
        w=(rng.getrandbits(1)<<31)|(exponent<<23)|rng.getrandbits(23)
        if kind=='sparse' and rng.getrandbits(1)==0:w=0
        out.append(w)
    return out

def sqrt_certificate(q,guess):
    """Arbitrary guessed positive finite normal word, exact squared midpoints."""
    if q<=0 or guess>>31:return False
    c=cell(guess)
    if c is None:return False
    lo,hi=c
    even=(guess&1)==0
    return (lo*lo<q or (even and lo*lo==q)) and (q<hi*hi or (even and q==hi*hi))

def sqrt_model(q,guess=None):
    if guess is None:
        try:guess=float_word(math.sqrt(float(q)))
        except (OverflowError,ValueError):return {'accepted':False,'reason':'native guess unavailable'}
    ok=sqrt_certificate(q,guess)
    # Exhaustively exclude both adjacent candidates if current certificate passed.
    if ok:
        assert not sqrt_certificate(q,guess-1)
        assert not sqrt_certificate(q,guess+1)
    return {'accepted':ok,'guess':f'{guess:08x}','q_num_bits':abs(q.numerator).bit_length(),'q_den_bits':q.denominator.bit_length()}

def rational_certificate(q,guess):
    # Norm's exact zero is always +0. All other zero/tie/extreme cases fallback.
    if q==0:return guess==0
    c=cell(guess)
    return c is not None and c[0]<q<c[1]

def norm_final_model(xs,gs,bs,eps,layer):
    n=len(xs);S=sum(xs,Fraction());Q=sum((x*x for x in xs),Fraction())
    mean=S/n if layer else Fraction()
    variance=(n*Q-S*S)/(n*n) if layer else Q/n
    den_report=sqrt_model(variance+eps)
    if not den_report['accepted']:return {'den_accepted':False,'samples':n,'accepted':0,'blind_wrong':0}
    den_word=int(den_report['guess'],16);den=value(den_word)
    native_sum=0.0
    for x in xs:native_sum=native_sum+float(x)
    native_mean=native_sum/n if layer else 0.0
    word_parts=[parts(float_word(float(x))) for x in xs]
    base=min((e for m,e in word_parts if m),default=-149)
    integers=[m<<(e-base) if m else 0 for m,e in word_parts]
    isum=sum(integers)
    md,ed=parts(den_word)
    accepted=wrong=max_pbits=max_dbits=max_residual_bits=0
    for x,g,b in zip(xs,gs,bs):
        q=(x-mean)*g/den+(b if layer else 0)
        guess=float_word((float(x)-native_mean)*float(g)/float(den)+(float(b) if layer else 0.0))
        truth=rn_rational(q);ok=rational_certificate(q,guess)
        assert not ok or guess==truth
        accepted+=ok;wrong+=guess!=truth
        mx,ex=parts(float_word(float(x)));mg,eg=parts(float_word(float(g)));mb,eb=parts(float_word(float(b)))
        xi=mx<<(ex-base) if mx else 0
        if layer:
            common=min(base+eg,eb+ed)
            P=((n*xi-isum)*mg << (base+eg-common))+(n*mb*md << (eb+ed-common))
            E=common-ed;D=n*md
        else:P=xi*mg;E=base+eg-ed;D=md
        assert P*pow2(E)/D==q,'Fraction-free final expression differs'
        max_pbits=max(max_pbits,abs(P).bit_length());max_dbits=max(max_dbits,D.bit_length())
        if cell(guess):
            mc,ec=parts(guess);re=min(E,ec)
            residual=(P<<(E-re))-(D*mc<<(ec-re))
            max_residual_bits=max(max_residual_bits,abs(residual).bit_length())
    return {'den_accepted':True,'samples':n,'accepted':accepted,'blind_wrong':wrong,'max_unreduced_P_bits':max_pbits,'max_D_bits':max_dbits,'max_exact_residual_bits':max_residual_bits}

def main():
    started=time.monotonic();rng=random.Random(24285517)
    r={'scope':'Finite read-only Python mathematical model. No Lean/native candidate build, workload time, admission or confidence inference. Own synthetic discovery values; no production holdouts.',
       'dot_hypotheses':['finite binary32 words','binary64 nearest-even multiplication and addition','n <= 2^51','no fused operation or compiler reassociation'],
       'dot_model_groups':[],'f32_filter_groups':[],'dot_directed':[],'sqrt_model_groups':[],'sqrt_directed':[],
       'norm_output_groups':[],'norm_output_directed':[],'norm_den_universal_extremes':[]}
    for kind in ('normal','wide','sparse'):
        for n in (16,64,256,1024):
            inputs=[(draw(rng,n,kind),draw(rng,n,'normal')) for _ in range(32)]
            models=[dot_model(a,b) for a,b in inputs]
            small=[f32_filter_model(a,b) for a,b in inputs]
            r['dot_model_groups'].append({'kind':kind,'n':n,'samples':len(models),'accepted':sum(m['accepted'] for m in models),'blind_guess_wrong':sum(m['guess']!=m['truth'] for m in models),'bound_violations':0,
                'max_bound_over_ulp32':max(m['error_bound_over_ulp32'] or 0 for m in models)})
            r['f32_filter_groups'].append({'kind':kind,'n':n,'samples':len(small),'accepted':sum(m['accepted'] for m in small),'normal_or_zero_domain':sum(m['domain'] for m in small)})
    directed=[('binary64_cancellation',[0x3f800000,float_word(2**-26),0xbf800000],[0x3f800000,float_word(2**-27),0x3f800000]),
              ('exact_binary32_midpoint',[0x3f800000,float_word(2**-12)],[0x3f800000,float_word(2**-12)]),
              ('299_bit_exact_span_but_unique_rounding',[0x3f800000,1],[0x3f800000,1]),
              ('all_zero',[0,0],[0x3f800000,0x3f800000]),
              ('large_products_cancel',[0x7f7fffff,0xff7fffff],[0x7f7fffff,0x7f7fffff])]
    for name,a,b in directed:r['dot_directed'].append(dict(name=name,**dot_model(a,b)))
    eps=value(0x3727c5ac)
    for kind in ('normal','wide','sparse'):
        for n in (16,64,256):
            stats=[]
            for _ in range(16):
                xs=[value(w) for w in draw(rng,n,kind)]
                s=sum(xs,Fraction());q=sum((x*x for x in xs),Fraction())
                rms=q/n+eps;layer=(n*q-s*s)/(n*n)+eps
                assert layer>=eps
                stats.extend([sqrt_model(rms),sqrt_model(layer)])
            r['sqrt_model_groups'].append({'kind':kind,'n':n,'samples':len(stats),'accepted':sum(s['accepted'] for s in stats),'max_num_bits':max(s.get('q_num_bits',0) for s in stats),'max_den_bits':max(s.get('q_den_bits',0) for s in stats)})
    for w in (0x3f800000,0x3f800001,0x40000000):
        lo,hi=cell(w)
        for label,q in [('lower_tie',lo*lo),('upper_tie',hi*hi)]:
            r['sqrt_directed'].append({'word':f'{w:08x}','case':label,'candidate_even':not bool(w&1),**sqrt_model(q,w)})
    for kind in ('normal','wide','sparse'):
        for n in (16,64,256):
            for layer in (False,True):
                models=[]
                for _ in range(8):
                    xs=[value(w) for w in draw(rng,n,kind)]
                    gs=[value(w&0x7fffff|0x3f800000) for w in draw(rng,n,'normal')]
                    bs=[value(w)/256 for w in draw(rng,n,'normal')]
                    models.append(norm_final_model(xs,gs,bs,eps,layer))
                r['norm_output_groups'].append({'kind':kind,'n':n,'norm':'layer' if layer else 'rms','rows':len(models),
                    'den_accepted':sum(m['den_accepted'] for m in models),'samples':sum(m['samples'] for m in models),
                    'accepted':sum(m['accepted'] for m in models),'blind_wrong':sum(m['blind_wrong'] for m in models),
                    'max_unreduced_P_bits':max(m.get('max_unreduced_P_bits',0) for m in models),'max_D_bits':max(m.get('max_D_bits',0) for m in models),'max_exact_residual_bits':max(m.get('max_exact_residual_bits',0) for m in models)})
    for name,xs in [('constant_row',[Fraction(1)]*64),('one_ulp_spread',[value(0x4b000000+i%2) for i in range(64)]),('signed_cancellation',[Fraction((-1)**i)*pow2(100) for i in range(64)]),('mean_double_loses_middle',[pow2(100),Fraction(1),-pow2(100)])]:
        r['norm_output_directed'].append(dict(name=name,**norm_final_model(xs,[Fraction(1)]*len(xs),[Fraction()]*len(xs),eps,True)))
    near=(value(0x3f800000)+value(0x3f800001))/2
    for direction in (-1,1):
        q=near*near+direction*pow2(-200)
        r['sqrt_directed'].append(dict(case='native_double_round_near_midpoint',offset_sign=direction,**sqrt_model(q)))
    fmax=value(0x7f7fffff);minimum=value(1);threshold=pow2(128)-pow2(103)
    assert fmax*fmax+fmax<threshold*threshold
    for name,q in [('minimum_variance_minimum_epsilon',minimum),('maximum_second_moment_maximum_epsilon',fmax*fmax+fmax)]:
        model=sqrt_model(q);assert model['accepted']
        word=int(model['guess'],16);assert 52<=((word>>23)&255)<=254 and not word>>31
        r['norm_den_universal_extremes'].append(dict(name=name,**model))
    r['elapsed_python_seconds']=time.monotonic()-started
    r['source_sha256']=hashlib.sha256(Path(__file__).read_bytes()).hexdigest()
    (HERE/'certificate-model-results.json').write_text(json.dumps(r,indent=2)+'\n',encoding='utf-8')
    print(json.dumps(r,indent=2))

if __name__=='__main__':main()
