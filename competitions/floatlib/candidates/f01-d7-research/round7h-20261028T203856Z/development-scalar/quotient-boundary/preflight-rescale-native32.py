"""Finite full-branch rescaling model. Exact scaling is not floating rounding."""
from pathlib import Path
import ast,hashlib,importlib.util,json,random,re
HERE=Path(__file__).resolve().parent
ROOT=next(p for p in HERE.parents if (p/'AGENTS.md').is_file())
PUB=ROOT/'competitions/floatlib/candidates';CAND=PUB/'f01-r24-dev-scalar-rescale-native321'
def main():
    s=importlib.util.spec_from_file_location('rounder_reference',HERE/'model-preflight.py');r=importlib.util.module_from_spec(s);s.loader.exec_module(r)
    manifest=json.loads((CAND/'manifest.json').read_bytes());raw=(CAND/'Kernel.lean').read_bytes();sha=lambda b:hashlib.sha256(b).hexdigest()
    assert sha(raw)==manifest['candidate_sha256'] and len(raw)==manifest['candidate_bytes']<256000
    for c in manifest['components']:
        b=(ROOT/c['path']).read_bytes();assert sha(b)==c['sha256'] and len(b)==c['bytes']
    assert raw.startswith((ROOT/manifest['runtime_prefix']['path']).read_bytes())
    gate=(PUB/'f01-d7-research/official-policy/gate-4b7e838.raw').read_bytes();tree=ast.parse(gate)
    banned=next(n for n in tree.body if isinstance(n,ast.Assign) and any(isinstance(t,ast.Name) and t.id=='BANNED' for t in n.targets))
    assert re.compile(ast.literal_eval(banned.value.args[0])).search(raw.decode()) is None
    for p in (Path(__file__),HERE/'build-rescale-native32.py'):ast.parse(p.read_bytes())
    trace=hashlib.sha256();count=0;categories={'zero':0,'subnormal':0,'normal':0,'infinity':0,'nan':0}
    def test(n,d,source,target,sign):
        nonlocal count
        ns,ds=r.scaled(n,d,source-target)
        a=r.actual_word(sign,n,d,source);b=r.actual_word(sign,ns,ds,target)
        assert a==b,(n,d,source,target,sign,hex(a),hex(b))
        E=(a>>23)&255;F=a&0x7fffff
        category='zero' if E==0 and F==0 else 'subnormal' if E==0 else 'normal' if E<255 else 'infinity' if F==0 else 'nan'
        categories[category]+=1;count+=1;trace.update(f'{n},{d},{source},{target},{int(sign)},{a}\n'.encode())
    values=(0,1,2,3,(1<<23)-1,1<<23,(1<<24)-1,1<<24,(1<<53)-1,(1<<64)-1,(1<<127)+1)
    sources=(-2000,-300,-151,-150,-149,-148,-127,-126,-1,0,1,126,127,128,300,2000)
    targets=(-2200,-150,-149,-126,0,127,2200)
    for n in values:
        for d in (0,1,2,3,(1<<24)-1,(1<<64)-1):
            for source in sources:
                for target in targets:
                    for sign in (False,True):test(n,d,source,target,sign)
    rng=random.Random(24282400)
    for _ in range(80000):
        n=rng.getrandbits(rng.randrange(1,257));d=rng.getrandbits(rng.randrange(1,193))
        source=rng.randrange(-1000,1001);target=rng.randrange(-1500,1501)
        test(n,d,source,target,bool(rng.getrandbits(1)))
    n=d=1;source=0;target=1
    badn,badd=r.scaled(n,d,target-source)
    original=r.actual_word(False,n,d,source);wrong=r.actual_word(False,badn,badd,target)
    assert original==0x3f800000 and wrong==0x40800000
    report={'status':'FINITE_ALL_BRANCH_NATIVE32_RESCALE_MODEL_PASS_LEAN_NOT_RUN','source_sha256':sha(raw),
        'bytes':len(raw),'roots':manifest['helper_audit_expected_count'],'cases':count,'result_categories':categories,'trace_sha256':trace.hexdigest(),
        'mutant_wrong_scale_sign':{'source':source,'target':target,'num':1,'den':1,'original':hex(original),'wrong':hex(wrong)},
        'Lean':'NOT_RUN','replay':'NOT_RUN','AX':'NOT_RUN','native':'NOT_RUN','cost':'NOT_RUN',
        'scope':'Exact integer logical rescaling only, including both signs, zero denominator and zero numerator, very wide exponents and all finite/overflow/underflow result classes. No binary64 approximation, double-rounding theorem, runtime allocation or speed claim.'}
    (HERE/'preflight-rescale-native32.json').write_bytes((json.dumps(report,indent=2)+'\n').encode())
    ready=json.loads((HERE/'READY-rescale-native32.json').read_bytes());ready['status']='READY_ALL_BRANCH_ACTUAL_ROUNDER_RESCALE_PENDING_TYPING';ready['preflight']='preflight-rescale-native32.json'
    (HERE/'READY-rescale-native32.json').write_bytes((json.dumps(ready,indent=2)+'\n').encode())
    print(json.dumps({k:report[k] for k in ('status','source_sha256','bytes','roots','cases','result_categories')}))
if __name__=='__main__':main()
