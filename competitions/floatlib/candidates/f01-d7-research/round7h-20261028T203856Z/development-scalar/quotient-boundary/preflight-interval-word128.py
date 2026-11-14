"""Finite normalized enclosure model. No native/Lean/compiler/performance claims."""
from pathlib import Path
import ast,hashlib,importlib.util,json,random,re
HERE=Path(__file__).resolve().parent
ROOT=next(p for p in HERE.parents if (p/'AGENTS.md').is_file())
PUB=ROOT/'competitions/floatlib/candidates'
CAND=PUB/'f01-r24-dev-scalar-interval-word1281'
M=1<<23;MASK=(1<<64)-1
sha=lambda b:hashlib.sha256(b).hexdigest()
def load(name,path):
    s=importlib.util.spec_from_file_location(name,path);m=importlib.util.module_from_spec(s);s.loader.exec_module(m);return m
def word_strict(n,d,m):
    g=abs(n-m*d)
    return d>0 and m>0 and g>>64==0 and g<d and g<d-g
def strict(lo,hi,d,m,E):
    return lo<=hi and 1<=E<=254 and M<m<2*M and word_strict(lo,d,m) and word_strict(hi,d,m)
def power(lo,hi,d,E,g):return lo<=hi and g.native_guard(lo,d,E) and g.native_guard(hi,d,E)

def main():
    g=load('power_guards',HERE/'gap-boundary-model.py');r=g.load()
    manifest=json.loads((CAND/'manifest.json').read_bytes());raw=(CAND/'Kernel.lean').read_bytes()
    assert sha(raw)==manifest['candidate_sha256'] and len(raw)==manifest['candidate_bytes']<256000
    assert raw.startswith((ROOT/manifest['runtime_prefix']['path']).read_bytes())
    for c in manifest['components']:
        b=(ROOT/c['path']).read_bytes();assert sha(b)==c['sha256'] and len(b)==c['bytes']
    gate=(PUB/'f01-d7-research/official-policy/gate-4b7e838.raw').read_bytes();assert sha(gate)=='1eb74ef7479b0023c721e776cc5e4073af21c6662b4afffcf16a48a124d27194'
    tree=ast.parse(gate);banned=next(n for n in tree.body if isinstance(n,ast.Assign) and any(isinstance(t,ast.Name) and t.id=='BANNED' for t in n.targets))
    assert re.compile(ast.literal_eval(banned.value.args[0])).search(raw.decode()) is None
    for p in (Path(__file__),HERE/'build-interval-word128.py'):ast.parse(p.read_bytes())
    count=accepted=pointchecks=0;trace=hashlib.sha256()
    def test(lo,hi,d,m,E,sign,mode):
        nonlocal count,accepted,pointchecks
        if not 0<=lo<1<<128 or not 0<=hi<1<<128:return
        a=strict(lo,hi,d,m,E) if mode=='strict' else power(lo,hi,d,E,g)
        if a:
            for n in {lo,hi,(lo+hi)//2,lo+(hi-lo)//3,hi-(hi-lo)//3}:
                w=r.actual_word(sign,n,d,E-150);target=(int(sign)<<31)|(E<<23)|(m-M)
                assert w==target,(mode,lo,hi,n,d,m,E,sign,hex(w),hex(target));pointchecks+=1
        count+=1;accepted+=int(a);trace.update(f'{mode},{lo},{hi},{d},{m},{E},{int(sign)},{int(a)}\n'.encode())
    for E in range(256):
        for d in (0,1,2,3,4,7,(1<<32)-1,(1<<63)-1,1<<63,MASK):
            for m in (M,M+1,M+2,2*M-2,2*M-1):
                mode='power' if m==M else 'strict';p=m*d
                for width in {0,1,d//4,max(0,d//2-1),d//2,d//2+1,d}:
                    for sign in (False,True):
                        test(p-width,p+width,d,m,E,sign,mode)
                        test(p+width,p-width,d,m,E,sign,mode)
    rng=random.Random(24282336)
    for _ in range(100000):
        E=rng.randrange(256);d=rng.randrange(1,1<<64);m=M if rng.randrange(4)==0 else rng.randrange(M+1,2*M)
        p=m*d;lo=p+rng.randrange(-d,d+1);hi=p+rng.randrange(-d,d+1)
        test(lo,hi,d,m,E,bool(rng.getrandbits(1)),'power' if m==M else 'strict')
    mutants=[]
    # A center or one endpoint alone does not establish that the entire enclosure is safe.
    d=4;E=128;m=M+2;p=m*d
    for label,lo,hi,n in (('only_low_endpoint',p,p+3,p+3),('only_high_endpoint',p-3,p,p-3),('center_only',p-3,p+3,p+3)):
        assert not strict(lo,hi,d,m,E)
        assert word_strict(p,d,m)
        assert r.actual_word(False,n,d,E-150)!=(E<<23)|(m-M)
        mutants.append({'mutant':label,'lo':lo,'hi':hi,'actual_n':n,'actual_word':hex(r.actual_word(False,n,d,E-150))})
    n=M*4-2;assert not power(n,n,4,2,g) and r.actual_word(False,n,4,2-150)==0xffffff
    mutants.append({'mutant':'uniform_half_lower_power_above_min','lo':n,'hi':n,'E':2,'actual_word':'0xffffff'})
    assert not strict(p+1,p-1,4,m,128)
    P=(1<<94)+1;D=(1<<29)+1;shift=42
    assert P.bit_length()==95 and D.bit_length()==30 and (D<<shift).bit_length()==72
    assert (D<<shift)>MASK and P%(1<<shift)!=0
    report={'status':'FINITE_NORMALIZED_INTERVAL_AND_SOURCE_PACKAGE_PASS_LEAN_NOT_RUN','source_sha256':sha(raw),
        'bytes':len(raw),'roots':len(manifest['explicit_helper_audit']),'interval_cases':count,'accepted_intervals':accepted,
        'accepted_point_checks':pointchecks,'trace_sha256':trace.hexdigest(),'bad_guards_rejected':mutants,
        'normalization_counterexample':{'P':str(P),'D':D,'P_bits':95,'D_bits':30,'required_D_left_shift':42,'normalized_D_bits':72,
            'reason':'Current full64 normalized denominator interface cannot consume this raw ratio at the proposed exponent; P has nonzero discarded bits so truncating the numerator is not exact.'},
        'Lean':'NOT_RUN','replay':'NOT_RUN','AX':'NOT_RUN','native':'NOT_RUN','cost':'NOT_RUN',
        'scope':'All256 exponent fields and both signs, strict interior or closed power/minnormal normalized enclosures. Exact N is sampled within each accepted interval; this is finite evidence only. Raw norm coverage, external scaling and a native enclosure theorem remain separate obligations.'}
    (HERE/'preflight-interval-word128.json').write_bytes((json.dumps(report,indent=2)+'\n').encode())
    ready=json.loads((HERE/'READY-interval-word128.json').read_bytes());ready['status']='READY_NORMALIZED_INTERVAL_INTERFACE_PENDING_DEPENDENCY_TYPING'
    ready['preflight']='preflight-interval-word128.json';ready['normalization_warning']=report['normalization_counterexample']
    (HERE/'READY-interval-word128.json').write_bytes((json.dumps(ready,indent=2)+'\n').encode())
    print(json.dumps({k:report[k] for k in ('status','source_sha256','bytes','roots','interval_cases','accepted_intervals','accepted_point_checks')}))
if __name__=='__main__':main()
