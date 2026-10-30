"""Bit/integer model of the guarded norm quotient path and final pack.

Uses exact formulas and explicit word bounds; not compiled Lean/native timing.
"""
from __future__ import annotations
from collections import Counter
from datetime import datetime,timezone
import hashlib,json
from pathlib import Path
import norm_frontier as nf


def finish_normal(sign,N,D,U,V):
    assert 0<N<1<<64 and 0<D<1<<64 and N>=D
    ratio=nf.floor_log_ratio(N,D)
    if ratio<=23:
        a,b=N<<(23-ratio),D
    else:
        a,b=N,D<<(ratio-23)
    assert a<1<<64 and b<1<<64 and 2*(a%b)<1<<64
    m=nf.quotient_even(a,b)
    carry=int(m==1<<24)
    exponent=ratio+U+carry-V
    if not(V<ratio+U and exponent<=254):return None
    fraction=((1<<23)if carry else m)-(1<<23)
    assert 0<=fraction<1<<23 and 1<=exponent<=254
    return (int(sign)<<31)|(exponent<<23)|fraction


def fast_word(n,w,gw,bw,b0,S1,dw,cap):
    state,ks=nf.guard_state(n,w,gw,bw,b0,S1,dw,cap)
    if state!="inner_fast":return None,state
    sw,mw,iw=nf.fields(w);sg,mg,ig=nf.fields(gw);sb,mb,ib=nf.fields(bw)
    _,md,idd=nf.fields(dw)
    centered=n*sw*(mw<<max(0,iw-b0))-S1
    cv=abs(centered);cs=centered<0
    D=n*md;c2=min(b0+ig,ib+idd);bs=ib+idd-c2
    q0=cv//D;r0=(cv%D)*mg;qq=q0*mg+r0//D
    ra=(r0%D)<<ks;qa=(qq<<ks)+ra//D;rr=ra%D;B=mb<<bs
    assert max(cv,D,q0,r0,qq,ra,qa,rr,B)<1<<64
    s1=cs!=(sg<0);s2=sb<0
    if s1==s2:qs,qi,qr=s1,qa+B,rr
    elif B<=qa:qs,qi,qr=s1,qa-B,rr
    elif rr==0:qs,qi,qr=s2,B-qa,0
    else:qs,qi,qr=s2,B-qa-1,D-rr
    assert qi<1<<63 and qr<D
    if qi>=1<<24:
        N=2*qi+int(qr!=0)
        result=finish_normal(qs,N,1,c2,idd+23)
    else:
        N=qi*D+qr
        if N==0:return 0,"fast_zero"
        if N<D:return None,"small_ratio"
        result=finish_normal(qs,N,D,c2+1,idd+23)
    return result,"fast_output"if result is not None else"final_pack_guard"


def check_row(x,n,g,b,row,counters):
    words=x[row*n:(row+1)*n];K=list(map(nf.key,words));S=sum(K);Q=sum(t*t for t in K)
    den=nf.sqrt_ratio(n*Q-S*S+n*n*nf.key(nf.EPS)*(1<<149),n*n<<298)
    b0=min((nf.fields(w)[2]for w in words if nf.fields(w)[1]),default=255)
    S1=sum(s*(m<<max(0,i-b0))for s,m,i in map(nf.fields,words))
    dk=nf.key(den)
    for j,w in enumerate(words):
        exact=nf.round_ratio((n*K[j]-S)*nf.key(g[j])+n*dk*nf.key(b[j]),n*dk,-149)
        for cap in[8,26]:
            result,state=fast_word(n,w,g[j],b[j],b0,S1,den,cap)
            counters[f"cap{cap}"][state]+=1
            if result is not None:assert result==exact,(n,w,g[j],b[j],b0,S1,den,cap,result,exact)


def main():
    started=datetime.now(timezone.utc).isoformat();cells=[]
    for seed in[27051001,27151004,27251007]:
        for profile in["typical","scale","boundary"]:
            i,h,h2=nf.dimensions(seed,profile)
            for kind in["normal","wide","sparse"]:
                for rows in[1,8]:
                    x=nf.gen(kind,rows*i,seed+999)
                    x=nf.linear(x,rows,i,h,nf.weights(kind,seed,1,i,h*i),nf.bias(seed,2,h),True)
                    x=nf.norm(x,rows,h,nf.scale(seed+3,h))
                    x=nf.linear(x,rows,h,h2,nf.weights(kind,seed,4,h,h2*h),nf.bias(seed,5,h2),True)
                    c={"cap8":Counter(),"cap26":Counter()}
                    g=nf.scale(seed+6,h2);b=nf.bias(seed,7,h2)
                    for r in range(rows):check_row(x,h2,g,b,r,c)
                    cells.append({"seed":seed,"profile":profile,"kind":kind,"rows":rows,"shape":[i,h,h2,10],"counts":c})
    total={f"cap{cap}":sum((c["counts"][f"cap{cap}"]for c in cells),Counter())for cap in[8,26]}
    out={"status":"FINITE_WORD_PATH_FORMULA_CHECK_NOT_LEAN","start_utc":started,"end_utc":datetime.now(timezone.utc).isoformat(),
        "source_sha256":hashlib.sha256(Path(__file__).read_bytes()).hexdigest(),"cells":cells,"total":total,
        "limits":["No Lean/native execution","No full12 proof","No time or current-champion gain claim"]}
    p=Path(__file__).with_name("norm-native-path-result.json");p.write_text(json.dumps(out,indent=2),encoding="utf-8")
    print(json.dumps({"cells":len(cells),"totals":total}))


if __name__=="__main__":main()
