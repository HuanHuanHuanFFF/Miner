"""Small finite arithmetic model of public nMLP profiles, not a new kernel.

Purpose: inspect internal norm ranges and dot-certificate ambiguity after the
actual documented layer topology. No Lean/native code, machine timings or CI.
"""
from fractions import Fraction
from pathlib import Path
import hashlib
import importlib.util
import json
import math

HERE=Path(__file__).resolve().parent
spec=importlib.util.spec_from_file_location('r24_cert_model',HERE/'certificates.py');c=importlib.util.module_from_spec(spec);spec.loader.exec_module(c)
spec2=importlib.util.spec_from_file_location('r24_moment_model',HERE/'moment_width_model.py');mw=importlib.util.module_from_spec(spec2);spec2.loader.exec_module(mw)

def lcg(n,seed):
    out=[]
    for _ in range(n):seed=(seed*1664525+1013904223)&0xffffffff;out.append(seed)
    return out

def gen(kind,n,seed):
    result=[]
    for w in lcg(n,seed):
        exponent=87+(w>>23)%40 if kind=='wide' else 121+(w>>23)%6
        result.append(0 if kind=='sparse' and (w>>9)&1==0 else (w&0x807fffff)|(exponent<<23))
    return result

def weights(kind,seed,key,fan,total):
    scale=c.rn_rational(Fraction(4,max(1,math.isqrt(fan))))
    ms,es=c.parts(scale)
    result=[]
    for w in gen('sparse' if kind=='sparse' else 'normal',total,(seed+101*key)&0xffffffff):
        m,e=c.parts(w);result.append(c.rn_dyadic(m*ms,e+es))
    return result

def biases(seed,key,n):
    return [c.rn_dyadic(m,e-8) for w in gen('normal',n,(seed+101*key)&0xffffffff) for m,e in [c.parts(w)]]

def gains(seed,n):return [(w&0x7fffff)|0x3f800000 for w in gen('normal',n,seed&0xffffffff)]

def dimensions(seed,profile):
    r=lcg(8,seed^0x5bd1e995)
    boundary=profile=='boundary';scale=profile=='scale'
    edge=lambda base,i:base+(-1 if r[i]&0x1000==0 else 1)
    i=edge((16+r[0]%49)*8,2) if boundary else (4+r[0]%45)*16 if scale else (16+r[0]%49)*8
    h=edge((8+r[1]%25)*8,3) if boundary else (2+r[1]%7)*16 if scale else (8+r[1]%25)*8
    h2=edge((4+r[2]%13)*8,4) if boundary else (1+r[2]%4)*16 if scale else (4+r[2]%13)*8
    return i,h,h2,10

def linear(x,W,bias,outputs,relu):
    n=len(x);out=[];accepted=0;rejected=[]
    for j in range(outputs):
        report=c.dot_model(x+[0x3f800000],W[j*n:(j+1)*n]+[bias[j]])
        w=report['truth'];accepted+=report['accepted']
        if not report['accepted']:
            rejected.append({'output':j,'report':report,'input_words':x+[0x3f800000],'weight_words':W[j*n:(j+1)*n]+[bias[j]]})
        out.append(0 if relu and w>>31 else w)
    return out,{'outputs':outputs,'dot_filter_accepted':accepted,'bias_inside_exact_dot':True,'rejected':rejected}

def root(q):
    g=c.float_word(math.sqrt(float(q)))
    for w in (g,g-1,g+1):
        if c.sqrt_certificate(q,w):return w
    raise AssertionError('No certified normal root found; model result unavailable')

def norm(words,g,b,layer):
    xs=[c.value(w) for w in words];n=len(xs);S=sum(xs);Q=sum(x*x for x in xs)
    mean=S/n if layer else Fraction();var=(n*Q-S*S)/(n*n) if layer else Q/n
    den=root(var+c.value(0x3727c5ac));dv=c.value(den)
    out=[];certified=0
    # Approximate output guess uses the actual exact integer moment as source.
    # It remains a guess and is checked independently, never accepted by trust.
    native_mean=float(mean)
    for x,gw,bw in zip(xs,g,b):
        gain=c.value(gw);bias=c.value(bw) if layer else Fraction()
        q=(x-mean)*gain/dv+bias
        guess=c.float_word((float(x)-native_mean)*float(gain)/float(dv)+float(bias))
        certified+=c.rational_certificate(q,guess)
        out.append(c.rn_rational(q))
    return out,dict(mw.inspect(words),norm='layer' if layer else 'rms',outputs_certified=certified,den_word=f'{den:08x}')

def main():
    seed=24292317;results=[]
    for profile in ('typical','scale','boundary'):
        i,h,h2,o=dimensions(seed,profile)
        for kind in ('normal','wide','sparse'):
            x=gen(kind,i,(seed+999)&0xffffffff)
            x,l1=linear(x,weights(kind,seed,1,i,i*h),biases(seed,2,h),h,True)
            x,rms=norm(x,gains(seed+3,h),[0]*h,False)
            x,l2=linear(x,weights(kind,seed,4,h,h*h2),biases(seed,5,h2),h2,True)
            x,ln=norm(x,gains(seed+6,h2),biases(seed,7,h2),True)
            x,l3=linear(x,weights(kind,seed,8,h2,h2*o),biases(seed,9,o),o,False)
            checksum=2166136261
            for w in x:checksum=((checksum^w)*16777619)&0xffffffff
            results.append({'profile':profile,'kind':kind,'seed':seed,'rows':1,'dimensions':[i,h,h2,o],
                'linear':[l1,l2,l3],'norms':[rms,ln],'python_model_checksum':f'{checksum:08x}'})
    result={'scope':'Own-seed finite arithmetic reproduction of public profile shape/value formulas and nMLP topology. No Lean checksum comparison, gate, timing, success probability or current-champion result.',
        'official_source_commit':'accb82b6e2adeda1b41a57a260d68fb3879c427e','profile_source':'lean/bench/ExactSuite.lean profileModel/nmlpLayers',
        'source_sha256':hashlib.sha256(Path(__file__).read_bytes()).hexdigest(),'certificate_helper_sha256':hashlib.sha256((HERE/'certificates.py').read_bytes()).hexdigest(),
        'results':results}
    (HERE/'nmlp-coverage-results.json').write_text(json.dumps(result,indent=2)+'\n',encoding='utf-8')
    print(json.dumps(result,indent=2))

if __name__=='__main__':main()
