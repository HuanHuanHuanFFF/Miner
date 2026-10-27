"""Bind historical C and verdicts, then sample the previously exposed R15 domain."""
from pathlib import Path
import hashlib,json,re,importlib.util,datetime,time
from collections import Counter,defaultdict
HERE=Path(__file__).resolve().parent
ROOT=next(p for p in HERE.parents if (p/'DEVELOPMENT.md').exists())
sha=lambda p:hashlib.sha256(p.read_bytes()).hexdigest()
def imp(name,path):
    s=importlib.util.spec_from_file_location(name,path);m=importlib.util.module_from_spec(s);s.loader.exec_module(m);return m
m=imp('ccompare',HERE.parent/'compare_classifier_codegen.py')
old=ROOT/'competitions/floatlib/candidates/f01-mul-log2-proof1/ci-runs/40030324309/download-25f67cdeabfc42e59f4bb2b0cde14377/diagnostics/f01-d7-public-suite/public-suite/diagnostics/f01-d11-scalar-normal-band'
olds,oldids=m.load(old,'e279b35413de1a753dc38edafcca3f476745390ede518ddeab93f0ccc1b8ef1d')
bases,baseids=m.load(m.BASE,'622d8394a7127e93dcaf992c62c6dfcff7208d212738409a5e34525dfafd1a58')
o=m.select(olds)['mul'];b=m.select(bases)['mul'];text=o['body']
first=text.index('\nif (');brace=text.index('{',first)
def endbrace(s,at):
    depth=1;i=at+1
    while depth:
        if s[i]=='{':depth+=1
        elif s[i]=='}':depth-=1
        i+=1
    return i
stop=endbrace(text,brace);assert text[stop:].lstrip().startswith('else')
accepted_start=text.index('{',stop);accepted_end=endbrace(text,accepted_start)
accepted=text[:first]+'\n/* The joint range guard is true on this recorded old C path. */\n'+text[accepted_start:accepted_end]
assert 'lean_float32_beq' not in accepted
assert accepted.count('lean_float32_mul(')==3
assert accepted.count('lean_uint32_to_float32(')==2
assert accepted.count('lean_array_fget_borrowed(')==2
(HERE/'old-e279-accepted-path.txt').write_text(accepted+'\n',encoding='utf-8')
(HERE/'baseline-selected-mul.c').write_text(b['body']+'\n',encoding='utf-8')
d=json.loads((ROOT/'competitions/floatlib/candidates/f01-d7-research/public-suite-results.json').read_text())
hist=[x for x in d['records'] if x.get('candidate') in ['f01-d11-scalar-normal-band','f01-d12-none-native-result','f01-r16-dev-native-add-high3']]
verified=[]
for x in hist:
    p=ROOT/x['verdict'];assert sha(p)==x['verdict_sha256'];v=json.loads(p.read_text())
    verified.append({'candidate':x['candidate'],'run':x['run'],'source_sha256':x['kernel_sha256'],'path':str(p),'sha256':sha(p),'passed':v['passed'],'stage':v['stage'],'mode':v['mode']})
comparisons=[x for x in d['comparisons'] if x.get('candidate')=='f01-d11-scalar-normal-band']
sources=[]
for rel in ['competitions/floatlib/candidates/f01-r6-fused-add-proof1/Kernel.lean','competitions/floatlib/candidates/f01-r6-normal-add-proof1/Kernel.lean','competitions/floatlib/candidates/f01-d6-finite-decode-proof1/Kernel.lean','competitions/floatlib/candidates/f01-d7-direct-nonnan/Kernel.lean','competitions/floatlib/candidates/f01-d10-bmm-direct-rows/Kernel.lean','competitions/floatlib/candidates/f01-d11-scalar-normal-band/Kernel.lean','competitions/floatlib/candidates/f01-d12-scalar-combined/Kernel.lean','competitions/floatlib/candidates/f01-r15-dev-packed-b2-1/Kernel.lean','competitions/floatlib/candidates/f01-r16-dev-native-add-high3/Kernel.lean']:
    p=ROOT/rel;sources.append({'path':str(p),'sha256':sha(p),'bytes':p.stat().st_size})
g=imp('publicmodel',ROOT/'competitions/floatlib/candidates/f01-d7-research/round8h-20261024T190259Z/astra-public-input-domain.py')
plan=ROOT/'competitions/floatlib/candidates/f01-mul-log2-proof1/ci-runs/40168687803/download-13caf4644cf1467e8717d9474d417b8a/diagnostics/f01-d7-public-suite/public-suite/public-drawn-plan.json'
groups=defaultdict(lambda:{'sampled':0,'hit':0,'miss':0});rows=[];start=time.perf_counter()
for c in json.loads(plan.read_text())['cases']:
    if c['kernel']!='mul' or not c['timed']:continue
    n=min(256,c['work']);hit=0
    for j in range(n):
        assert time.perf_counter()-start<3
        lo,hi=j*c['work']//n,(j+1)*c['work']//n
        i=lo+g.word(c['seed'],j,63)%(hi-lo);u=g.element(c,i,0,31);v=g.partner(c,i,u)
        guard=((((u&0x7fffffff)-0x20000000)&0xffffffff)|(((v&0x7fffffff)-0x20000000)&0xffffffff))<0x40000000
        expected=0x20000000<=(u&0x7fffffff)<0x60000000 and 0x20000000<=(v&0x7fffffff)<0x60000000
        assert guard==expected
        if guard:assert ((u>>23)&255)+((v>>23)&255)>=128
        hit+=guard
    name=':'.join(c['name'].split(':')[:2]);groups[name]['sampled']+=n;groups[name]['hit']+=hit;groups[name]['miss']+=n-hit
    rows.append({'case':c['name'],'sampled':n,'hit':hit,'work':c['work']})
cost=json.loads((HERE.parents[2]/'astra-cost-allocation.json').read_text())
r={'utc':datetime.datetime.now(datetime.timezone.utc).isoformat(),'state':'VERIFIED_HISTORICAL_C_AND_VERDICTS_NEW_SOURCE_NOT_RUN',
 'source_identities':sources,'old_C':oldids,'baseline_C':baseids,
 'selected_callbacks':{'old':{k:v for k,v in o.items() if k!='body'},'baseline':{k:v for k,v in b.items() if k!='body'}},
 'old_accepted_C_sites':dict(Counter(re.findall(r'\b(lean_\w+)\(',accepted))),
 'historical_verdicts':verified,'historical_comparisons':comparisons,
 'exposure':{'old_completed_run':40168687803,'plan_sha256':sha(plan),'generator_translation_sha256':sha(Path(g.__file__)),'groups':dict(groups),'cases':rows,'elapsed_seconds':time.perf_counter()-start,'scope':'Unweighted source-model samples, not timing, machine paths or new confirmation'},
 'frozen_model_share':cost['median_fraction'],'required_MUL_reduction_for_ten_percent_whole':0.1/cost['median_fraction']['mul'],
 'new_condition':'B2 already pays two guarded numeric table decoders; e279 old parent paid direct ofBits. MUL-only reuse removes existing common work; ADD retains known old negative and stays unchanged.',
 'not_claimed':['New algorithm','Measured 10 percent gain','Old gate implies new gate','Source operation counts imply machine speed','Historical UNKNOWN reset']}
(HERE/'frontier-evidence.json').write_text(json.dumps(r,indent=2)+'\n',encoding='utf-8')
print(json.dumps({'groups':dict(groups),'required_MUL_reduction':r['required_MUL_reduction_for_ten_percent_whole'],'old_accepted_C_sites':r['old_accepted_C_sites']}))
