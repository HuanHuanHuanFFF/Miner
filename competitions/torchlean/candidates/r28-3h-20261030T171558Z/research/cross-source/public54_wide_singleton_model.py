"""Independent literal model of public54 QW wide-row path on old Mixer36 calls.

This is not the earlier singleton578f: that merely opens the existing <=15
prepared path. Here packed input mantissa/exponent and a positive per-product
offset cover input span47 and weight span7, with one cached offset-sum correction.
No candidate or CI queue is created by this finite discriminator.
"""
from pathlib import Path
from datetime import datetime,timezone
import collections
import hashlib
import importlib.util
import json
import sys
sys.dont_write_bytecode=True
HERE=Path(__file__).resolve().parent
spec=importlib.util.spec_from_file_location('mixer_qw54',HERE/'mixer_path_model.py')
model=importlib.util.module_from_spec(spec);spec.loader.exec_module(model)
m=model.m;MASK=(1<<64)-1


def prepare(x):
    xm,xh,expmax=model.metadata(x)
    if expmax==255 or xm>xh or xh-xm>47 or not(0<len(x)<16384):return None
    v=[];sb=0
    for word in x:
        sign,mant,index=m.fields(word)
        shift=1 if mant==0 else index-xm+1
        assert 1<=shift<=48
        payload=((1<<24)+sign*mant)|(shift<<25)
        assert 0<=payload<1<<32
        v.append(payload);sb=(sb+(1<<shift))&MASK
    assert sb<1<<62
    return v,sb,xm


def dot(x,w,bias,p):
    if p is None:return None,'input_guard'
    v,sb,xm=p;wm,wh,expmax=model.metadata(w);_,mb,ib=m.fields(bias);bexp=(bias>>23)&255
    if wm>wh or expmax==255 or wh-wm>7 or wm<1 or bexp==255:return None,'weight_guard'
    base=xm+wm-1
    if mb and not(base<=126+ib and 126+ib-base<80):return None,'bias_guard'
    low=high=0
    for encoded,word in zip(v,w):
        factor=(encoded&0x1ffffff)-(1<<24);shift=encoded>>25
        sw,mw,iw=m.fields(word)
        # Zero mantissa remains0 even under the original masked UInt64 shift.
        aligned=(mw<<((iw-wm)&63))&MASK
        q=(aligned*(factor if sw>0 else -factor)+(1<<55))&MASK
        assert 0<q<1<<56
        term=(q<<shift)&MASK;new_low=(low+term)&MASK
        high=(high+(q>>(64-shift))+(new_low<term))&MASK;low=new_low
    correction_low=(sb<<55)&MASK;correction_high=sb>>9
    fixed_low=(low-correction_low)&MASK
    fixed_high=(high-correction_high-(low<correction_low))&MASK
    signed=(fixed_high<<64)|fixed_low
    if fixed_high>>63:signed-=1<<128
    exact_body=sum(m.key(a)*m.key(b)for a,b in zip(x,w))>>base
    # All admitted aligned products have an integral representation at this base.
    assert sum(m.key(a)*m.key(b)for a,b in zip(x,w))==signed*(1<<base)
    assert signed==exact_body
    total=signed+(m.fields(bias)[0]*mb<<(149+ib-base) if mb else 0)
    return m.round_ratio(total,1,base-298),'wide_qw'


def main():
    counts=collections.Counter();records=[];cell_name=None;original=model.Census.linear
    def linear(self,x,rows,k,out,w,b,relu,stage):
        if rows==1:
            prepared=prepare(x);per=collections.Counter()
            if prepared is not None:counts['input_prepare_items']+=k
            for j in range(out):
                right=w[j*k:(j+1)*k];value,state=dot(x,right,b[j],prepared)
                per[state]+=1;counts[state+'_macs']+=k
                if value is not None:
                    total=sum(m.key(a)*m.key(z)for a,z in zip(x,right))+(m.key(b[j])<<149)
                    expected=m.round_ratio(total,1,-298)
                    assert value==expected
            records.append({'cell':cell_name,'stage':stage,'k':k,'outputs':out,'paths':per})
        return original(self,x,rows,k,out,w,b,relu,stage)
    model.Census.linear=linear
    req=json.loads((model.r.E/'fp-word-conv6-26102901-request.json').read_bytes());measured=json.loads((model.r.E/'fp-word-conv6-26102901-measurement.json').read_bytes())['result'];checked=0
    for w in req['workloads']:
        for kind in ['normal','wide','sparse']:
            cell_name=f"{w['id']}|mixer:b1:{kind}";c=model.Census();out=model.r.run_cell('mixer',w['seed'],w['profile'],kind,c)
            assert model.r.fnv(out)==measured['rounds'][0]['cells'][cell_name]['candidate_checksum'];checked+=1
    out={'at_utc':datetime.now(timezone.utc).isoformat(),'state':'NEW_PUBLIC54_MECHANISM_FINITE_DISCRIMINATOR_NOT_NATIVE',
         'source_sha256':hashlib.sha256(Path(__file__).read_bytes()).hexdigest(),'native_matching_oldcells':checked,'counts':counts,'records':records,
         'mechanism':'public54 QWs/QWe/QWP/QWz/QWL/QWc/QWf/QW1; copied semantics into independent model, no sourcebody redistribution. Perproduct positive offset2^55 and cachedsum2^shift, exact128 correction, originalbias finish.',
         'distinction':'Earlier578f only admitted rows1 to <=15source36 prepcache andhit14880/64500MACs with70950prepitems. This wideinput path has its own47/7/n16384/bias80 guards and cachesonly inputonce; no strongrows>=2 path needs replacement.',
         'cost':'Unknown; operation/prepare counts alone do not prove a wholemodel speedup. Newcandidate/full12/proofbytebudget absent; existingCI3 untouched.'}
    (HERE/'public54-wide-singleton-model.json').write_text(json.dumps(out,indent=2)+'\n',encoding='utf-8');print(json.dumps({'cells':checked,'counts':counts},indent=2))


if __name__=='__main__':main()
