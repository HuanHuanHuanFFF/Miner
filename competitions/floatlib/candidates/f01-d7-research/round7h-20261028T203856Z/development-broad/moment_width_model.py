"""Exact integer moment width discriminator, no candidate/native benchmark."""
from pathlib import Path
import hashlib
import importlib.util
import json
import math
import random

HERE=Path(__file__).resolve().parent
spec=importlib.util.spec_from_file_location('r24_certificates',HERE/'certificates.py')
c=importlib.util.module_from_spec(spec);spec.loader.exec_module(c)

def inspect(words):
    fields=[c.parts(w) for w in words];n=len(words);L=(n-1).bit_length()
    nonzero=[e for m,e in fields if m];b=min(nonzero,default=-149);R=max(nonzero,default=b)-b
    xs=[m<<(e-b) if m else 0 for m,e in fields]
    S=sum(xs);Q=sum(x*x for x in xs);T=n*Q-S*S
    assert T>=0
    qbound=48+2*R+L;tbound=48+2*R+2*L;sbound=24+R+L
    assert Q<(1<<qbound) and T<(1<<tbound) and abs(S)<(1<<sbound)
    return {'n':n,'R':R,'L':L,'S_bits':abs(S).bit_length(),'Q_bits':Q.bit_length(),'T_bits':T.bit_length(),
        'bound_Q_bits':qbound,'bound_T_bits':tbound,'rms128':qbound<=128,'layer128':tbound<=128,
        'rms192':qbound<=192,'layer192':tbound<=192}

def main():
    rng=random.Random(24291941);rows=[]
    for kind in ('normal','wide','sparse'):
        for n in (16,64,256,1024):
            samples=[inspect(c.draw(rng,n,kind)) for _ in range(16)]
            rows.append({'kind':kind,'n':n,'rows':len(samples),'max_R':max(r['R'] for r in samples),
                'max_S_bits':max(r['S_bits'] for r in samples),'max_Q_bits':max(r['Q_bits'] for r in samples),'max_T_bits':max(r['T_bits'] for r in samples),
                **{k:sum(r[k] for r in samples) for k in ('rms128','layer128','rms192','layer192')}})
    directed=[]
    for name,words in [('full_exponent_span',[1,0x7f7fffff]),('large_constant',[0x7f7fffff]*256),('near_constant',[0x3f800000]*255+[0x3f800001])]:
        directed.append(dict(name=name,**inspect(words)))
    # A naive E[x²]-E[x]² double guess can lose a legitimate tiny variance.
    xs=[c.value(w) for w in [0x3f800000]*255+[0x3f800001]];n=len(xs)
    S=sum(xs);Q=sum(x*x for x in xs);exact_variance=(n*Q-S*S)/(n*n)
    sf=qf=0.0
    for x in xs:sf=sf+float(x);qf=qf+float(x)*float(x)
    guessed_variance=qf/n-(sf/n)*(sf/n)
    eps=c.value(1);exact_q=exact_variance+eps
    naive=c.float_word(math.sqrt(max(0.0,guessed_variance)+float(eps)))
    exact_input_guess=c.sqrt_model(exact_q)
    adverse={'exact_variance':str(exact_variance),'naive_variance':guessed_variance,'naive_den_guess':f'{naive:08x}',
        'naive_den_certificate':c.sqrt_certificate(exact_q,naive),'exact_numerator_guess':exact_input_guess}
    assert guessed_variance==0.0 and not adverse['naive_den_certificate'] and exact_input_guess['accepted']
    report={'scope':'Finite exact integer width/certificate models only; no actual model profile, native timing, Lean or new candidate.',
        'source_sha256':hashlib.sha256(Path(__file__).read_bytes()).hexdigest(),'certificate_helper_sha256':hashlib.sha256((HERE/'certificates.py').read_bytes()).hexdigest(),
        'groups':rows,'directed':directed,'variance_cancellation':adverse}
    (HERE/'moment-width-results.json').write_text(json.dumps(report,indent=2)+'\n',encoding='utf-8')
    print(json.dumps(report,indent=2))

if __name__=='__main__':main()
