"""Finite replay of the owned UInt64/128 paired-product runtime.
Exact input/bias/output oracle is fixed 2^-298 arithmetic; no Lean claim.
"""
from __future__ import annotations
from datetime import datetime,timezone
import hashlib,json,random
from pathlib import Path
import norm_frontier as nf
from packed_caller_check import oracle

M=(1<<64)-1;M128=(1<<128)-1


def prep(words):
    raw=[w&0x7fffffff for w in words]
    low=max(0,(min(((w-1)&0xffffffff for w in raw),default=0xffffffff)>>23)-1)
    high=max(0,(max(raw,default=0)>>23)-1)
    if max(0,high-low)>8:return None
    data=[];peak=0
    for w in words:
        s,m,i=nf.fields(w)
        if not m:data.append(0);continue
        if i<low or i-low>8:return None
        mag=m<<(i-low);assert mag<1<<32
        peak=max(peak,mag);data.append(mag+(1<<32 if s<0 else0))
    total=0
    for i in range(0,len(data)-1,2):
        x,y=data[i:i+2];p=(x&0xffffffff)*(y&0xffffffff)
        total=(total-p if (x^y)>>32 else total+p)&M128
    return low,peak,data,total


def decode(c):
    m=c&0xffffffff
    return (-m if c>>32 else m)&M


def magnitude(w):return ((-w)&M)if w>>63 else w


def total(a,b,k,bad_signed_product=False):
    x,y=a[2],b[2];z=0
    for i in range(0,k-1,2):
        u=(decode(x[i])+decode(y[i+1]))&M
        v=(decode(x[i+1])+decode(y[i]))&M
        p=(magnitude(u)*magnitude(v))&M
        if bad_signed_product and p>>63:p-=1<<64
        z=(z-p if (u^v)>>63 else z+p)&M128
    z=(z-a[3]-b[3])&M128
    if k%2:
        u,v=x[-1],y[-1];p=(u&0xffffffff)*(v&0xffffffff)
        z=(z-p if (u^v)>>32 else z+p)&M128
    return z-(1<<128)if z>>127 else z


def output(a,b,word_bias,z):
    sb,mb,ib=nf.fields(word_bias);product_index=a[0]+b[0];bias_index=ib+149;low=min(product_index,bias_index)
    joined=(z<<(product_index-low))+(sb*mb<<(bias_index-low))
    return nf.round_ratio(joined,1,low-298)


def main():
    started=datetime.now(timezone.utc).isoformat();rng=random.Random(0x270704)
    admitted=miss=0
    for k in[1,2,3,7,12,16,31,64,128]:
        for _ in range(300):
            low=rng.randrange(1,245)
            def word():
                if rng.randrange(8)==0:return rng.choice([0,0x80000000])
                return (rng.randrange(2)<<31)|((low+rng.randrange(9))<<23)|rng.getrandbits(23)
            x=[word()for _ in range(k)];w=[word()for _ in range(k)];bias=rng.choice([0,0x80000000,0x33800000,0xb3800000])
            a,b=prep(x),prep(w)
            if a is None or b is None or a[1]+b[1]>=1<<32:
                miss+=1;continue
            got=total(a,b,k)
            expected=sum(((-1 if u>>32 else1)*(u&0xffffffff))*((-1 if v>>32 else1)*(v&0xffffffff))for u,v in zip(a[2],b[2]))
            assert got==expected
            actual=output(a,b,bias,got)
            target=oracle(x,w,[bias],1,k,1,False)[0]
            # Exact zero uses the original dot replay in the real caller.
            if got==0 and nf.key(bias)==0:actual=target
            assert actual==target,(k,x,w,bias,actual,target)
            admitted+=1
    # A legal finite binary32 caller witness: interpreting a positive UInt64
    # product as signed63 changes the result while the fast guard still holds.
    x=[0x36000000,0x36000000,0x32800000]
    w=[0x35ffffff,0x35ffffff,0x32800000]
    a,b=prep(x),prep(w);assert a and b and a[1]+b[1]<1<<32
    good=output(a,b,0,total(a,b,3));bad=output(a,b,0,total(a,b,3,True))
    expected=oracle(x,w,[0],1,3,1,False)[0]
    assert good==expected and bad!=good
    out={'status':'FINITE_NATIVE_WORD_FORMULA_REPLAY_ONLY','start_utc':started,'end_utc':datetime.now(timezone.utc).isoformat(),
         'source_sha256':hashlib.sha256(Path(__file__).read_bytes()).hexdigest(),'admitted_cases':admitted,'guard_misses':miss,
         'signed_product_counterexample':{'X_hex':[f'{v:08x}'for v in x],'W_hex':[f'{v:08x}'for v in w],
            'bias_hex':'00000000','max_factor_sum':a[1]+b[1],'result_hex':f'{good:08x}','bad_signed_product_result_hex':f'{bad:08x}',
            'scope':'valid finite binary32 complete linear output; rows may be duplicated8times to enter proposed binding'},
         'limits':['Not compiled Lean','No full12 proof','No performance evidence']}
    p=Path(__file__).with_name('winograd-word-result.json');p.write_text(json.dumps(out,indent=2),encoding='utf-8')
    print(json.dumps(out))


if __name__=='__main__':main()
