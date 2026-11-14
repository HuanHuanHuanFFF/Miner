"""Research-only deletion of the third accumulator limb in old narrow fallback.

Distinct from centered caches: no new preparation; preserve every original
prepared MD/MD2 path. For at most65536 terms with original span<=63, the body
fits signed128. Normalize the deferred negative count before sign-extension,
then add bias with the unchanged192-bit terminal.
"""
from pathlib import Path
from datetime import datetime,timezone
import collections
import hashlib
import importlib.util
import json
import random
import sys
sys.dont_write_bytecode=True
HERE=Path(__file__).resolve().parent
spec=importlib.util.spec_from_file_location('mixer_narrow128',HERE/'mixer_path_model.py')
model=importlib.util.module_from_spec(spec);spec.loader.exec_module(model)
m=model.m;MASK=(1<<64)-1;MASK128=(1<<128)-1;MASK192=(1<<192)-1


def step192(state,a,b,lo):
    w2,w1,w0,c=state
    _,ma,ia=m.fields(a);_,mb,ib=m.fields(b)
    product=ma*mb;shift=(ia+ib-lo)&MASK;r=shift&63
    y0=(product<<r)&MASK;y1=(product>>1)>>(63-r)
    neg=(a^b)>>31;mask=(-neg)&MASK
    low=(w0+(y0^mask))&MASK;k0=low<w0
    upper=(w1+(y1^mask))&MASK;ka=upper<w1
    high=(upper+k0)&MASK;kb=high<upper
    top=(w2+mask+(ka or kb))&MASK
    return top,high,low,(c+neg)&MASK


def step128(state,a,b,lo):
    h,l,c=state
    _,ma,ia=m.fields(a);_,mb,ib=m.fields(b)
    product=ma*mb;shift=(ia+ib-lo)&MASK;r=shift&63
    low_product=(product<<r)&MASK;high_product=(product>>1)>>(63-r)
    neg=(a^b)>>31;mask=(-neg)&MASK
    low=(l+(low_product^mask))&MASK
    return (h+(high_product^mask)+(low<l))&MASK,low,(c+neg)&MASK


def normalize128(state):
    h,l,c=state;low=(l+c)&MASK;high=(h+(low<l))&MASK
    return (-int(high>>63))&MASK,high,low,0


def normalize192(state):
    h2,h1,l,c=state;low=(l+c)&MASK;high=(h1+(low<l))&MASK;top=(h2+(high<h1))&MASK
    return top,high,low,0


def exact_body(a,b,lo):
    return sum(m.fields(x)[0]*m.fields(x)[1]*m.fields(y)[0]*m.fields(y)[1]*(1<<(m.fields(x)[2]+m.fields(y)[2]-lo))
               for x,y in zip(a,b)if m.fields(x)[1]*m.fields(y)[1])


def compare(a,b,lo):
    assert len(a)==len(b)<=65536
    old=(0,0,0,0);new=(0,0,0)
    for x,y in zip(a,b):
        old=step192(old,x,y,lo);new=step128(new,x,y,lo)
        assert old[1:]==new
    actual=exact_body(a,b,lo)
    assert -(1<<127)<actual<1<<127
    result=normalize128(new)
    assert result==normalize192(old)
    assert ((result[0]<<128)|(result[1]<<64)|result[2])==actual&MASK192
    return result


def negative_controls():
    # Actual source36-accepted raw words expose the missing-count-guard failure.
    low=0x3c800001;high=0x5c7fffff;weight=0x3cffffff;k=65538;lo=240
    body=(m.fields(low)[1]*m.fields(weight)[1])+(k-1)*((1<<24)-1)**2*(1<<63)
    assert body>1<<127
    wrapped=(body&MASK128)-(1<<128)
    expected=m.round_ratio(body,1,lo-298);wrong=m.round_ratio(wrapped,1,lo-298)
    assert expected!=wrong
    # Omitting c changes even a single negative unit product.
    a=b=0x3f800000
    old=step192((0,0,0,0),a|0x80000000,b,252)
    new=step128((0,0,0),a|0x80000000,b,252)
    assert new[2]==1
    uncorrected=((new[0]<<64)|new[1])&MASK128
    corrected=((normalize128(new)[1]<<64)|normalize128(new)[2])&MASK128
    assert uncorrected!=corrected
    return {'without_count_guard':{'n':k,'x':'one3c800001 then65537copies5c7fffff','w':'65538copies3cffffff','bias':'00000000','lo':lo,'span':63,'source36_nlt1048576':True,'expected_word':f'{expected:08x}','wrong_signed128_word':f'{wrong:08x}'},
            'drop_negative_count_counterexample':{'a':'bf800000','b':'3f800000','bias':'3f800000','lo':252,'negative_count':new[2],
              'expected_word':'00000000','wrong_word_without_count':f'{m.round_ratio(-1,1,-46):08x}'}}


def main():
    fixtures=0;rng=random.Random(280128)
    for _ in range(2000):
        n=rng.choice([0,1,2,7,16,63,128]);span=rng.randrange(64);base=rng.randrange(1,150)
        a=[];b=[]
        for j in range(n):
            ex=base+rng.randrange(span+1);ey=60
            a.append((rng.randrange(2)<<31)|(ex<<23)|rng.randrange(1<<23))
            b.append((rng.randrange(2)<<31)|(ey<<23)|rng.randrange(1<<23))
        compare(a,b,base+60-2);fixtures+=1
    counts=collections.Counter();original=model.Census.linear
    def linear(self,x,rows,k,out,w,b,relu,stage):
        left=[x[i*k:(i+1)*k]for i in range(rows)];right=[w[j*k:(j+1)*k]for j in range(out)]
        lm=list(map(model.metadata,left));rm=list(map(model.metadata,right))
        for i,(a,ma) in enumerate(zip(left,lm)):
            for j,(v,mv) in enumerate(zip(right,rm)):
                _,bm,bi=m.fields(b[j]);lo=min(ma[0]+mv[0],126+bi)if bm else ma[0]+mv[0];hi=max(ma[1]+mv[1],126+bi)if bm else ma[1]+mv[1]
                # Only actual YaU callers: every singleton, or rejected prepared dot.
                if rows==1 or hi-lo>15 or hi<lo:
                    counts['old_yau_macs']+=k
                    if hi>=lo and hi-lo<=63 and k<=65536:
                        compare(a,v,lo);counts['new_fallback128_macs']+=k;counts['new_fallback128_dots']+=1
                        if stage=='classifier':counts['classifier_macs']+=k
        return original(self,x,rows,k,out,w,b,relu,stage)
    model.Census.linear=linear
    req=json.loads((model.r.E/'fp-word-conv6-26102901-request.json').read_bytes());measured=json.loads((model.r.E/'fp-word-conv6-26102901-measurement.json').read_bytes())['result'];checked=0
    for w in req['workloads']:
        for kind in ['normal','wide','sparse']:
            c=model.Census();out=model.r.run_cell('mixer',w['seed'],w['profile'],kind,c);cell=f"{w['id']}|mixer:b1:{kind}"
            assert model.r.fnv(out)==measured['rounds'][0]['cells'][cell]['candidate_checksum'];checked+=1
    result={'at_utc':datetime.now(timezone.utc).isoformat(),'state':'ISOLATED_NEXT_ROUTE_LITERAL_WORD_MODEL_NOT_CANDIDATE',
            'source_sha256':hashlib.sha256(Path(__file__).read_bytes()).hexdigest(),'fixture_sequences':fixtures,'native_matching_oldcells':checked,'counts':counts,'negative_controls':negative_controls(),
            'proof':'Perterm absproduct<2^(48+63)=2^111; n<=2^16 gives bodyabs<2^127. Normalize c into low/high, signextend body into192, then originalbias/finish. Finaltotalneed not fit128 becausebiasisadded in192.',
            'scope':'Source36 contiguous-linear YS6 fallback only; existing MD/MD2 and GEMM untouched. No extra preparation/cache.',
            'cost_hypothesis':'Use original inlineYL6 with highword0 and continuation discardingtop output; compiler mayremove two highcarry comparisons/or/topaddition. ActualgeneratedC/ASM/nativecost UNKNOWN.',
            'limits':['No new CIrequest or fullsource','No newcorrect/root acceptance','Counts not time share','Counterexample n65538 proves a countbound is needed, not that65536 is the optimal maximal guard']}
    (HERE/'narrow128-fallback-model.json').write_text(json.dumps(result,indent=2)+'\n',encoding='utf-8');print(json.dumps({k:result[k]for k in ['fixture_sequences','native_matching_oldcells','counts','negative_controls']},indent=2))


if __name__=='__main__':main()
