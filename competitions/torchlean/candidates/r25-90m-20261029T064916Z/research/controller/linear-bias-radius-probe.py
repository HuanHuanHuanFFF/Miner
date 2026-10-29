"""Screen Cartesian exponent inflation in the actual append-bias dot interface.

Uses C's exact public-generator mirror as a shared dependency, not independent
Lean equivalence. Python IEEE double is a finite diagnostic, never a proof.
"""
from pathlib import Path
import datetime
import hashlib
import importlib.util
import json
import math
import struct

HERE=Path(__file__).resolve().parent
RESEARCH=HERE.parent
MIRROR=RESEARCH/'integer/model_span_probe.py'
RECORDS=RESEARCH/'integer/model-span-probe.json'
MASK64=2**64-1


def f32(w):return struct.unpack('<f',struct.pack('<I',w))[0]
def bits(x):return struct.unpack('<Q',struct.pack('<d',x))[0]
def key(w):return w^((1<<63) if w>>63==0 else MASK64)
def finite(w):return w&0x7ff0000000000000 != 0x7ff0000000000000
def idx(w):
    e=(w>>23)&255
    return e-1 if e else 0
def peak(words):return max(map(idx,words),default=0)


def certify(s,q,H,L):
    mag=q&0x7fffffff;e=(mag>>23)&255
    if not 1<=e<=254:return False
    radius=math.ldexp(1.0,H+2*L-303)
    sw,lo,hi=bits(s),bits(s-radius),bits(s+radius)
    if not all(map(finite,(sw,lo,hi))):return False
    base=((e+896)<<52)|((mag&0x7fffff)<<29)
    lower=base-((1<<29) if mag==0x00800000 else (1<<28))
    upper=base+(1<<28)
    if q>>31:lower,upper=upper|(1<<63),lower|(1<<63)
    return key(lower)<key(lo) and key(hi)<key(upper)


def main():
    spec=importlib.util.spec_from_file_location('r25_shared_exact_mirror',MIRROR)
    m=importlib.util.module_from_spec(spec);spec.loader.exec_module(m)
    frozen=json.loads(RECORDS.read_bytes())
    assert frozen['seed']==42 and frozen['widths']==[537,243,87,10]
    rows={(r['kind'],r['layer'],r['output']):r for r in frozen['records']}
    checks={(r['kind'],r['layer']):r['input_sha256'] for r in frozen['independent_fraction_checks']}
    results=[]
    for kind in ('normal','wide','sparse'):
        x=m.gen(kind,537,1041)
        for layer,(ni,no) in enumerate(zip(frozen['widths'],frozen['widths'][1:])):
            weights=m.weights(kind,42,2*layer,ni,ni*no)
            bias=m.biases(42,2*layer+1,no)
            nxt=[]
            for j in range(no):
                w=weights[j*ni:(j+1)*ni];xx=x+[0x3f800000];yy=w+[bias[j]]
                if j==0:
                    raw=b''.join(struct.pack('<I',z) for z in xx+yy)
                    assert hashlib.sha256(raw).hexdigest()==checks[(kind,layer)]
                s=0.0
                for a,b in zip(xx,yy):s=s+f32(a)*f32(b)
                sw=bits(s)
                magnitude=((((sw&0x7fffffffffffffff)+0x10000000)&MASK64)>>29)&0xffffffff
                q=(((sw>>32)&0x80000000)|((magnitude-0xc0000000)&0x7fffffff))
                L=(len(xx)-1).bit_length()
                H=peak(xx)+peak(yy)
                bias_nonzero=(bias[j]&0x7fffffff)!=0
                refined=max(peak(x)+peak(w),idx(bias[j])+125 if bias_nonzero else 0)
                assert refined<=H
                old_ok=certify(s,q,H,L);new_ok=certify(s,q,refined,L)
                exact=rows[(kind,layer,j)]['output_word']
                assert not(old_ok or new_ok) or q==exact
                results.append({'kind':kind,'layer':layer,'output':j,'terms':len(xx),
                                'H_cartesian':H,'H_pair_and_bias':refined,'L':L,
                                'old_accept':old_ok,'refined_accept':new_ok,
                                'proposal_word':q,'exact_output_word':exact})
                nxt.append(0 if layer<2 and exact>>31 else exact)
            x=nxt
    summary=[]
    for kind in ('normal','wide','sparse'):
        for layer in range(3):
            rs=[x for x in results if x['kind']==kind and x['layer']==layer]
            summary.append({'kind':kind,'layer':layer,'dots':len(rs),
                            'cartesian_accepts':sum(x['old_accept'] for x in rs),
                            'refined_accepts':sum(x['refined_accept'] for x in rs),
                            'extra_accepts':sum(x['refined_accept'] and not x['old_accept'] for x in rs),
                            'H_reduction_range':[min(x['H_cartesian']-x['H_pair_and_bias'] for x in rs),
                                                 max(x['H_cartesian']-x['H_pair_and_bias'] for x in rs)]})
    report={'at_utc':datetime.datetime.now(datetime.timezone.utc).isoformat(),
            'status':'FINITE_DOMAIN_SCREEN_NOT_LEAN_OR_NATIVE_BENCHMARK','seed':42,
            'profile':'legacy dev only; not official typical/scale/boundary sampling',
            'mirror_source_sha256':hashlib.sha256(MIRROR.read_bytes()).hexdigest(),
            'mirror_record_sha256':hashlib.sha256(RECORDS.read_bytes()).hexdigest(),
            'summary':summary,'cases':len(results),'false_accepts_observed':0,'records':results,
            'mathematical_premise':'body product bound2^(peakX+peakW-250); exact bias term bound2^(idxBias-125); use max of those actual term bounds rather than Cartesian appended-operand peaks',
            'limits':['Depends on the shared Python exact-generator mirror; equivalence to Lean is not compiled.',
                      'Python double follows the intended separate double mul/add; no actual Lean runtime or C/ASM is exercised.',
                      'No new runtime source, producer proof, timing or champion-score conclusion.',
                      'No new seed or unseen confirmation set; this is opportunity screening only.']}
    (HERE/'linear-bias-radius-probe.json').write_text(json.dumps(report,indent=2)+'\n',encoding='utf-8',newline='\n')
    print(json.dumps({'cases':len(results),'summary':summary},indent=2))


if __name__=='__main__':main()
