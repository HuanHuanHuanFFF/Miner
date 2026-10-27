from pathlib import Path
import json,hashlib,sys,subprocess,time,random
ROOT=Path(__file__).resolve().parent
def run_model():
    t=time.perf_counter(); M=(1<<64)-1; U=(1<<32)-1; rng=random.Random(1526004)
    def shr(x,s):return x>>(s%64)
    def shl(x,s):return (x<<(s%64))&M
    def old(value,shift):
        q=shr(value,shift);r=value&(shl(1,shift)-1)&M;h=shl(1,(shift-1)&M)
        return q if r<h else ((q+1)&M if r>h else q if q&1==0 else (q+1)&M)
    def new(value,shift):
        q=shr(value,shift);r=value&(shl(1,shift)-1)&M;h=shl(1,(shift-1)&M)
        nl=0 if r<h else 1;g=1 if r>h else 0;o=0 if q&1==0 else 1
        assert all(x in (0,1) for x in (nl,g,o))
        return (q+(nl&(g|o)))&M
    truths=[]
    for less in (False,True):
        for greater in (False,True):
            for odd in (False,True):
                oldinc=0 if less else 1 if greater else 1 if odd else 0
                newinc=(0 if less else 1)&((1 if greater else 0)|(1 if odd else 0))
                assert oldinc==newinc
                truths.append([less,greater,odd,oldinc])
    vals={0,1,2,3,M,M-1,1<<63,(1<<63)-1}
    for s in (1,23,24,63):
        for q in (0,1,2,3,(1<<23)-1,1<<23,(1<<24)-1):
            for rr in (0,1,(1<<(s-1))-1,1<<(s-1),(1<<(s-1))+1,(1<<s)-1):
                x=(q<<s)+rr
                if x<=M: vals.add(x)
    shifts=[0,1,2,22,23,24,25,62,63,64,65,127,M]
    round_checks=0
    for v in sorted(vals):
        for s in shifts:
            assert old(v,s)==new(v,s),(v,s)
            round_checks+=1
    for _ in range(12000):
        v=rng.getrandbits(64);s=rng.getrandbits(64)
        assert old(v,s)==new(v,s),(v,s)
        round_checks+=1
    def eligible(eu,ev):
        return ((eu-1)&U)<=253 and ((ev-1)&U)<=253 and ((eu+ev-128)&U)<=252
    guard_checks=0
    for eu in range(256):
        for ev in range(256):
            assert eligible(eu,ev)==(1<=eu<=254 and 1<=ev<=254 and 128<=eu+ev<=380)
            guard_checks+=1
    coverage={"high0":0,"high1":0,"carry1":0,"tie_even":0,"tie_odd":0}
    def check_product(a,b,eu,ev,sgn):
        p=a*b;hi=p>>47;s=23+hi;rd=new(p,s);oldrd=old(p,s)
        assert p<1<<48 and hi in (0,1) and s in (23,24)
        assert rd==oldrd and (1<<23)<=rd<=(1<<24)
        carry=rd>>24;assert carry in (0,1) and not (hi==1 and carry==1)
        coverage['high'+str(hi)]+=1
        coverage['carry1']+=int(carry==1)
        e=eu+ev-127+hi+carry; assert 1<=e<=254
        nw=(sgn<<31)|((e&255)<<23)|(rd&0x7fffff)
        # Independent integer quotient/remainder rounding and carry normalization.
        shift=p.bit_length()-24
        q,r=divmod(p,1<<shift)
        if 2*r==(1<<shift):coverage['tie_odd' if q%2 else 'tie_even']+=1
        q+=int(2*r>(1<<shift) or (2*r==(1<<shift) and q%2==1))
        oe=eu+ev-127+(p.bit_length()-47)
        if q==1<<24:q>>=1;oe+=1
        oracle=(sgn<<31)|(oe<<23)|(q&0x7fffff)
        assert nw==oracle,(a,b,eu,ev,sgn,nw,oracle)
    ms=[1<<23,(1<<23)+1,(1<<23)+2,(1<<23)+(1<<22)-1,(1<<23)+(1<<22),(1<<24)-3,(1<<24)-2,(1<<24)-1]
    ep=[(1,127),(1,254),(64,64),(126,254),(190,190),(254,126)]
    product_checks=0
    for a in ms:
        for b in ms:
            for eu,ev in ep:
                for sg in (0,1):check_product(a,b,eu,ev,sg);product_checks+=1
    for _ in range(6000):
        a=rng.randrange(1<<23,1<<24);b=rng.randrange(1<<23,1<<24)
        eu=rng.randrange(1,255); ev=rng.randrange(max(1,128-eu),min(254,380-eu)+1)
        check_product(a,b,eu,ev,rng.randrange(2));product_checks+=1
    return dict(state="FINITE_MODEL_NO_COUNTEREXAMPLE",seed=1526004,truth_table=truths,
        arbitrary_word_shift_samples=round_checks,all_exponent_guard_pairs=guard_checks,
        eligible_normal_product_samples=product_checks,normal_product_coverage=coverage,seconds=time.perf_counter()-t,
        limitations="Finite Python model, not Lean proof, not native execution/benchmark; fallback output not modeled. Universal equality reasoning is separately reviewed.",
        new_candidate_created=False)
if __name__=="__main__":
    if "--child" in sys.argv:
        print(json.dumps(run_model(),indent=2));raise SystemExit
    start=time.perf_counter()
    try:
        p=subprocess.run([sys.executable,str(Path(__file__).resolve()),"--child"],capture_output=True,text=True,timeout=5)
    except subprocess.TimeoutExpired as e:
        rec=dict(state="TIMEOUT",timeout_seconds=5,seconds=time.perf_counter()-start)
        (ROOT/"branchless-finite-model.json").write_text(json.dumps(rec,indent=2)+"\n")
        raise SystemExit(1)
    (ROOT/"branchless-finite-model.stdout.txt").write_text(p.stdout,encoding="utf-8")
    (ROOT/"branchless-finite-model.stderr.txt").write_text(p.stderr,encoding="utf-8")
    if p.returncode:raise SystemExit(p.returncode)
    rec=json.loads(p.stdout);rec["external_timeout_seconds"]=5;rec["wrapper_seconds"]=time.perf_counter()-start
    (ROOT/"branchless-finite-model.json").write_text(json.dumps(rec,indent=2)+"\n",encoding="utf-8")
    print(json.dumps({k:v for k,v in rec.items() if k!="truth_table"},indent=2))

