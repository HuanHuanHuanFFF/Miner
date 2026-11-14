"""Finite carry/sign/enclosure falsifiers; not Lean/native acceptance."""
from pathlib import Path
from fractions import Fraction
import ast,hashlib,importlib.util,json,random,re
HERE=Path(__file__).resolve().parent
ROOT=next(p for p in HERE.parents if (p/'AGENTS.md').is_file())
PUB=ROOT/'competitions/floatlib/candidates';CAND=PUB/'f01-r24-dev-scalar-center-radius1281'
MASK=(1<<128)-1;M=1<<23
def load(name,path):
    s=importlib.util.spec_from_file_location(name,path);m=importlib.util.module_from_spec(s);s.loader.exec_module(m);return m
def make(c,r):return ((c-r)&MASK,(c+r)&MASK,r<c and c+r<=MASK)
def main():
    interval=load('scaled_intervals',HERE/'preflight-dyadic-interval128.py');ref=interval.load()
    manifest=json.loads((CAND/'manifest.json').read_bytes());raw=(CAND/'Kernel.lean').read_bytes();sha=lambda b:hashlib.sha256(b).hexdigest()
    assert sha(raw)==manifest['candidate_sha256'] and len(raw)==manifest['candidate_bytes']<256000
    for c in manifest['components']:
        b=(ROOT/c['path']).read_bytes();assert sha(b)==c['sha256'] and len(b)==c['bytes']
    gate=(PUB/'f01-d7-research/official-policy/gate-4b7e838.raw').read_bytes();tree=ast.parse(gate)
    n=next(n for n in tree.body if isinstance(n,ast.Assign) and any(isinstance(t,ast.Name) and t.id=='BANNED' for t in n.targets))
    assert re.compile(ast.literal_eval(n.value.args[0])).search(raw.decode()) is None
    for p in (Path(__file__),HERE/'build-center-radius128.py'):ast.parse(p.read_bytes())
    rng=random.Random(24282355);count=valid=sign_checks=word_checks=accepted=0;trace=hashlib.sha256()
    def test(c,r,D,negative,delta=None,E=None,m=None,k=None):
        nonlocal count,valid,sign_checks,word_checks,accepted
        lo,hi,a=make(c,r)
        if a:
            assert lo+r==c and hi==c+r and lo>0
            valid+=1
            if delta is None:delta=rng.randrange(-r*D,r*D+1)
            assert abs(delta)<=r*D
            N=(-c if negative else c)*D+delta;value=Fraction(N,D)
            assert (value<0)==negative
            assert Fraction(lo)<=abs(value)<=Fraction(hi);sign_checks+=1
            if E is not None and interval.check(lo,hi,k,m,E):
                word=ref.actual_word(N<0,abs(N),D,k);target=(int(negative)<<31)|(E<<23)|(m-M)
                assert word==target;word_checks+=1;accepted+=1
        count+=1;trace.update(f'{c},{r},{D},{int(negative)},{int(a)}\n'.encode())
    for c in (0,1,2,3,(1<<64)-1,1<<64,(1<<127)-1,1<<127,MASK-1,MASK):
        for r in (0,1,2,3,c,max(0,c-1),min(MASK,c+1),MASK):
            for negative in (False,True):test(c,r,7,negative)
    for _ in range(50000):test(rng.getrandbits(128),rng.getrandbits(128),rng.randrange(1,1<<64),bool(rng.getrandbits(1)))
    for _ in range(50000):
        E=rng.randrange(1,255);m=rng.randrange(M+1,2*M);K=rng.randrange(104);c=m<<K;r=rng.randrange((1<<K)+1)
        test(c,r,rng.getrandbits(96)+1,bool(rng.getrandbits(1)),E=E,m=m,k=E-150-K)
    # Dropping each constructor precondition violates its advertised arithmetic/sign contract.
    lo,hi,a=make(MASK,1);assert not a and hi==0 and hi!=MASK+1
    overflow={'mutant':'ignore_upper_carry','center':str(MASK),'radius':1,'wrong_wrapped_hi':hi,'true_hi':str(MASK+1)}
    lo,hi,a=make(3,3);value=0;assert not a and (value<0)!=True
    zero={'mutant':'allow_radius_equal_center_then_trust_negative_center_sign','center':3,'radius':3,'value':0,'guessed_negative':True,'actual_negative':False}
    lo,hi,a=make(3,5);value=2;assert not a and abs(-3-value)<=5 and (value<0)!=True
    crossing={'mutant':'trust_center_sign_across_zero','center':3,'radius':5,'value':2,'guessed_negative':True,'actual_negative':False}
    report={'status':'FINITE_CENTER_RADIUS_SIGN_AND_WORD_COMPOSITION_PASS_LEAN_NOT_RUN','source_sha256':sha(raw),
        'bytes':len(raw),'roots':manifest['helper_audit_expected_count'],'cases':count,'valid_intervals':valid,
        'exact_sign_and_abs_enclosure_checks':sign_checks,'accepted_actual_word_checks':word_checks,
        'trace_sha256':trace.hexdigest(),'mutants':[overflow,zero,crossing],
        'Lean':'NOT_RUN','replay':'NOT_RUN','AX':'NOT_RUN','native':'NOT_RUN','cost':'NOT_RUN',
        'scope':'Exact finite integer/rational model. Radius and center must share a proved logical scale; no native Float64 decoder or actual loop error bound is implemented here. Sign crossing/carry/strict-cell misses retain caller fallback.'}
    (HERE/'preflight-center-radius128.json').write_bytes((json.dumps(report,indent=2)+'\n').encode())
    ready=json.loads((HERE/'READY-center-radius128.json').read_bytes());ready['status']='READY_CENTER_RADIUS_SIGN_AND_WORD_COMPOSITION_PENDING_TYPING';ready['preflight']='preflight-center-radius128.json'
    (HERE/'READY-center-radius128.json').write_bytes((json.dumps(ready,indent=2)+'\n').encode())
    print(json.dumps({k:report[k] for k in ('status','source_sha256','bytes','roots','cases','valid_intervals','exact_sign_and_abs_enclosure_checks','accepted_actual_word_checks')}))
if __name__=='__main__':main()
