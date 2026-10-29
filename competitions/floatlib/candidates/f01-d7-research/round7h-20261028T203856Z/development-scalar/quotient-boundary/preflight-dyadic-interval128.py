"""Exact integer model of scaled endpoint controller; no machine execution."""
from pathlib import Path
import ast,hashlib,importlib.util,json,random,re
HERE=Path(__file__).resolve().parent
ROOT=next(p for p in HERE.parents if (p/'AGENTS.md').is_file())
PUB=ROOT/'competitions/floatlib/candidates';CAND=PUB/'f01-r24-dev-scalar-dyadic-interval1281'
M=1<<23
def load():
    s=importlib.util.spec_from_file_location('actual_reference',HERE/'model-preflight.py');r=importlib.util.module_from_spec(s);s.loader.exec_module(r);return r
def compare(a,e,b,f):
    if e>=f:a<<=e-f
    else:b<<=f-e
    return (a>b)-(a<b)
def fast(a,e,b,f):
    if a>>64:return True
    if e<=f:return f-e<64 and (b==0 or b.bit_length()-1+f-e<64)
    return e-f<64 and (a==0 or a.bit_length()-1+e-f<64)
def check(lo,hi,k,m,E,skip_fast=False):
    if not (1<=E<=254 and M<m<2*M):return False
    l=2*m-1;u=2*m+1;t=E-150
    if not skip_fast and not (fast(lo,k+1,l,t) and fast(hi,k+1,u,t)):return False
    return lo<=hi and compare(lo,k+1,l,t)>0 and compare(hi,k+1,u,t)<0
def main():
    r=load();manifest=json.loads((CAND/'manifest.json').read_bytes());raw=(CAND/'Kernel.lean').read_bytes()
    sha=lambda b:hashlib.sha256(b).hexdigest()
    assert sha(raw)==manifest['candidate_sha256'] and len(raw)==manifest['candidate_bytes']<256000
    for c in manifest['components']:
        b=(ROOT/c['path']).read_bytes();assert sha(b)==c['sha256'] and len(b)==c['bytes']
    prefix=(ROOT/manifest['runtime_prefix']['path']).read_bytes();assert raw.startswith(prefix) and sha(prefix)==manifest['runtime_prefix']['sha256']
    gate=(PUB/'f01-d7-research/official-policy/gate-4b7e838.raw').read_bytes();tree=ast.parse(gate)
    n=next(n for n in tree.body if isinstance(n,ast.Assign) and any(isinstance(t,ast.Name) and t.id=='BANNED' for t in n.targets))
    assert re.compile(ast.literal_eval(n.value.args[0])).search(raw.decode()) is None
    for p in (Path(__file__),HERE/'build-dyadic-interval128.py'):ast.parse(p.read_bytes())
    count=accepted=raw_wide=pointchecks=blocked_misses=0;trace=hashlib.sha256();rng=random.Random(24282350)
    def test(lo,hi,k,m,E,D,F,sign):
        nonlocal count,accepted,raw_wide,pointchecks,blocked_misses
        if not 0<=lo<1<<128 or not 0<=hi<1<<128:return
        a=check(lo,hi,k,m,E)
        assert not a or check(lo,hi,k,m,E,True)
        if check(lo,hi,k,m,E,True):assert a
        if not a and not (fast(lo,k+1,2*m-1,E-150) and fast(hi,k+1,2*m+1,E-150)):blocked_misses+=1
        if a:
            source=k-F;target=(int(sign)<<31)|(E<<23)|(m-M)
            L=lo*D*(1<<F);H=hi*D*(1<<F)
            assert L<=H
            N=rng.randrange(L,H+1)
            for actual in {L,H,N}:
                assert r.actual_word(sign,actual,D,source)==target,(lo,hi,k,m,E,actual,D,source)
                pointchecks+=1
            if (D<<max(0,(E-150)-source)).bit_length()>64:raw_wide+=1
        count+=1;accepted+=int(a);trace.update(f'{lo},{hi},{k},{m},{E},{D},{F},{int(sign)},{int(a)}\n'.encode())
    for E in range(256):
        for m in (M,M+1,M+2,2*M-2,2*M-1):
            for K in (0,1,2,29,40,63,80,103):
                p=m<<K
                for width in {0,1,max(0,(1<<K)//2-1),(1<<K)//2,(1<<K)//2+1}:
                    for sign in (False,True):test(p-width,p+width,E-150-K,m,E,(1<<90)+17,67,sign)
    for _ in range(60000):
        E=rng.randrange(256);m=rng.randrange(M+1,2*M);K=rng.randrange(104);p=m<<K
        width=rng.randrange(0,(1<<K)+1);lo=p-width;hi=p+width
        test(lo,hi,E-150-K,m,E,rng.getrandbits(96)+1,rng.randrange(101),bool(rng.getrandbits(1)))
    mutants=[]
    E=128;m=M+2;k=E-150-2;p=m<<2
    for name,lo,hi,n in (('only_low_endpoint',p,p+3,p+3),('only_high_endpoint',p-3,p,p-3),('center_only',p-3,p+3,p+3)):
        assert not check(lo,hi,k,m,E) and check(p,p,k,m,E)
        assert r.actual_word(False,n,1,k)!=(E<<23)|(m-M)
        mutants.append(name)
    assert not check(0,1,E-150,m,E)
    assert not check(p+1,p-1,k,m,E)
    # This miss would enter the public comparator's generic Nat branch without fastAllowed.
    assert not fast(1,-700,2*m-1,-22) and not check(1,1,-701,m,E)
    report={'status':'FINITE_SCALED_DYADIC_INTERVAL_CONTROLLER_PASS_LEAN_NOT_RUN','source_sha256':sha(raw),
        'bytes':len(raw),'roots':manifest['helper_audit_expected_count'],'interval_cases':count,'accepted':accepted,
        'accepted_raw_ratios_requiring_normalized_D_over64bits':raw_wide,'actual_rounder_point_checks':pointchecks,
        'fast_guard_blocked_misses':blocked_misses,'trace_sha256':trace.hexdigest(),'bad_guards_rejected':mutants,
        'Lean':'NOT_RUN','replay':'NOT_RUN','AX':'NOT_RUN','native':'NOT_RUN','cost':'NOT_RUN',
        'scope':'Finite exact dyadic/native-branch model; raw exact N/D up to hundreds of bits appears only in theorem premises. No native enclosure proof, Float64 loop integration, closed power cell, new-track runtime or measured cost.'}
    (HERE/'preflight-dyadic-interval128.json').write_bytes((json.dumps(report,indent=2)+'\n').encode())
    ready=json.loads((HERE/'READY-dyadic-interval128.json').read_bytes());ready['status']='READY_SCALED_DYADIC_INTERVAL_PENDING_DEPENDENCY_TYPING';ready['preflight']='preflight-dyadic-interval128.json'
    (HERE/'READY-dyadic-interval128.json').write_bytes((json.dumps(ready,indent=2)+'\n').encode())
    print(json.dumps({k:report[k] for k in ('status','source_sha256','bytes','roots','interval_cases','accepted','accepted_raw_ratios_requiring_normalized_D_over64bits','actual_rounder_point_checks','fast_guard_blocked_misses')}))
if __name__=='__main__':main()
