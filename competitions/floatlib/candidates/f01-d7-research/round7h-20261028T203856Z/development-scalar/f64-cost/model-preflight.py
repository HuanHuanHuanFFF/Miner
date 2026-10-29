"""Python-only arithmetic and packaging preflight; no Lean/native build."""
from pathlib import Path
from types import SimpleNamespace
import ast,hashlib,importlib.util,json,random,re,struct,tempfile,time
HERE=Path(__file__).resolve().parent
ROOT=next(p for p in HERE.parents if (p/'AGENTS.md').is_file())
PUB=ROOT/'competitions/floatlib/candidates'
TARGET=PUB/'f01-r24-dev-scalar-f64array-cost1'
sha=lambda p:hashlib.sha256(Path(p).read_bytes()).hexdigest()
def load(p,name):
    spec=importlib.util.spec_from_file_location(name,p);m=importlib.util.module_from_spec(spec);spec.loader.exec_module(m);return m
def write(p,raw):p.parent.mkdir(parents=True,exist_ok=True);p.write_bytes(raw if isinstance(raw,bytes) else raw.encode())
def f32(u):return struct.unpack('<f',struct.pack('<I',u))[0]
def f64(w):return struct.unpack('<d',struct.pack('<Q',w))[0]
def bits64(f):return struct.unpack('<Q',struct.pack('<d',f))[0]
def bits32(f):
    try:return struct.unpack('<I',struct.pack('<f',f))[0]
    except OverflowError:return 0xff800000 if f<0 else 0x7f800000
def scale(j):
    e=j&255;return ((j&256)<<55)|((874 if e==0 else e+873)<<52)
SCALES=tuple(f64(scale(j)) for j in range(512))
def decode(u):
    m=(u&0x7fffff)|(0 if u&0x7f800000==0 else 0x800000)
    return float(m)*SCALES[u>>23]
def narrow(w):
    sign=w>>32&0x80000000;e=w>>52&2047
    if e<873:return sign
    if e>1150:return sign|0x7f800000
    m=(w&0xfffffffffffff)|0x10000000000000
    if e<897:
        d=926-e;q=(m+((1<<(d-1))-1)+((m>>d)&1))>>d
        return sign|q
    q=(m+0xfffffff+((m>>29)&1))>>29
    return sign|(((e-897)<<23)+q)
def units(u):
    e=u>>23&255;f=u&0x7fffff
    n=f if e==0 else (0x800000+f)<<(e-1)
    return -n if u>>31 else n
def rne(n,d):
    if d<=0:return n<<(-d)
    q,r=divmod(n,1<<d);return q+int(r>(1<<(d-1)) or r==(1<<(d-1)) and q&1)
def exact_add(u,v):
    z=units(u)+units(v)
    if z==0:return 0x80000000 if u==v==0x80000000 else 0
    sign=0x80000000 if z<0 else 0;n=abs(z);leading=n.bit_length()-1-149
    if leading < -126:return sign|n
    q=rne(n,n.bit_length()-24)
    if q==1<<24:q>>=1;leading+=1
    if leading>127:return sign|0x7f800000
    return sign|((leading+127)<<23)|(q-0x800000)
def main():
    started=time.monotonic();checks=[];counts={'decode':0,'narrow':0,'ADD':0};trace=hashlib.sha256();bad=[]
    for p in HERE.glob('*.py'):ast.parse(p.read_bytes())
    manifest=json.loads((TARGET/'manifest.json').read_bytes());source=TARGET/'Kernel.lean'
    d=load(HERE/'driver.py','r24_f64_preflight_driver');a=load(HERE/'f64-cost-audit.py','r24_f64_preflight_stage')
    assert sha(source)==manifest['candidate_sha256']==d.SOURCE==a.SOURCE
    assert source.read_bytes().startswith((PUB/'f01-r15-dev-packed-b2-1/Kernel.lean').read_bytes()) and source.stat().st_size<=256000
    for item in manifest['components']:
        p=ROOT/item['path'];assert sha(p)==item['sha256'] and p.stat().st_size==item['bytes']
    for p,h in d.PINS.items():assert sha(p)==h
    assert len(d.SEEDS)==2 and len(d.ORDER)==12 and len(d.VARIANTS)==3
    # Use the exact pinned intake regex on the new kernel, including comments.
    gate=(PUB/'f01-d7-research/official-policy/gate-4b7e838.raw').read_text()
    tree=ast.parse(gate);node=next(n for n in tree.body if isinstance(n,ast.Assign) and any(isinstance(t,ast.Name) and t.id=='BANNED' for t in n.targets))
    banned=re.compile(ast.literal_eval(node.value.args[0]));assert banned.search(source.read_text()) is None
    checks.append('AST, byte cap, exact B2 prefix, all component hashes, legacy pins, exact policy regex,24 process ABBA')
    rng=random.Random(240010125)
    def decode_check(u):
        x,y=bits64(decode(u)),bits64(f32(u));counts['decode']+=1;trace.update(struct.pack('<IQQ',u,x,y))
        if x!=y:bad.append({'kind':'decode','u':hex(u),'new':hex(x),'expected':hex(y)})
    for e in range(255):
        for s in range(2):
            for f in (0,1,2,0x3fffff,0x400000,0x7ffffe,0x7fffff):decode_check(s<<31|e<<23|f)
    for _ in range(100000):decode_check(rng.getrandbits(1)<<31|rng.randrange(255)<<23|rng.getrandbits(23))
    def narrow_check(w):
        x,y=narrow(w),bits32(f64(w));counts['narrow']+=1;trace.update(struct.pack('<QII',w,x,y))
        if x!=y:bad.append({'kind':'narrow','w':hex(w),'new':hex(x),'expected':hex(y)})
    for e in range(2047):
        for s in range(2):
            for f in (0,1,(1<<28)-1,1<<28,(1<<51),(1<<52)-2,(1<<52)-1):narrow_check(s<<63|e<<52|f)
    for _ in range(100000):narrow_check(rng.getrandbits(1)<<63|rng.randrange(2047)<<52|rng.getrandbits(52))
    def add_check(u,v):
        z=decode(u)+decode(v);x,y,c=narrow(bits64(z)),exact_add(u,v),bits32(z);counts['ADD']+=1
        trace.update(struct.pack('<IIIII',u,v,x,y,c))
        if x!=y or y!=c:bad.append({'kind':'ADD','u':hex(u),'v':hex(v),'word':hex(x),'exact':hex(y),'cast':hex(c)})
    for eu in range(255):
        for ev in range(255):
            for k,(fu,fv) in enumerate(((0,0),(0x7fffff,0x7fffff),(1,0x7ffffe),(0x7fffff,0))):
                add_check((k&1)<<31|eu<<23|fu,(k>>1)<<31|ev<<23|fv)
    for _ in range(100000):
        add_check(rng.getrandbits(1)<<31|rng.randrange(255)<<23|rng.getrandbits(23),rng.getrandbits(1)<<31|rng.randrange(255)<<23|rng.getrandbits(23))
    for u,v in ((0,0),(0x80000000,0x80000000),(0,0x80000000),(1,1),(0x80000001,1),
            (0x7f7fffff,0x7f7fffff),(0xff7fffff,0xff7fffff),(0x7f7fffff,0xff7fffff),
            (0x00800000,0x807fffff),(0x007fffff,1),(0x3f800000,1),(0x3f800000,0x33800000)):
        add_check(u,v)
    assert not bad,bad[:4]
    checks.append('Finite numeric decoder, finite F64-to-F32 UInt64 RNE core and complete F32 binary ADD finite models')
    with tempfile.TemporaryDirectory(dir=HERE,prefix='preflight-') as tmp:
        p=Path(tmp).resolve();assert p.is_relative_to(HERE.resolve())
        g=SimpleNamespace(HERE=p,LIB=p/'lean',BUILD=p/'lean/.lake/build',LAYER=p/'layer',WORK=p/'lean/work/Submission.lean',
            LAKE='lake',_SANDBOX=True,_BUILD_TIMEOUT=1800,_BUILD_MEMORY_MB=4096,_BENCH_MEMORY_MB=512,
            STAGES=[('intake',None),('policy',None),('statement',None)],OWN_STEMS={'Submission','MainFull'})
        g.foreign=lambda upper:[]
        write(p/'gate.py',(PUB/'f01-d7-research/official-policy/gate-4b7e838.raw').read_bytes())
        write(p/'benchmark_suite.py',b'# PYTHON FIXTURE ONLY\n');write(p/'suites/public-v2.json',b'{}\n');write(g.WORK,source.read_bytes())
        cfg=b'import Lake\nopen Lake DSL\npackage competition where\nlean_exe benchFull where\n  srcDir := "bench"\n  root := `MainFull\n'
        write(g.LIB/'lakefile.lean',cfg);write(g.LIB/'lake-manifest.json',b'{}\n');write(g.LIB/'lean-toolchain',b'leanprover/lean4:v4.34.0\n')
        for rel in ('bin/benchFull','ir/MainFull.c','ir/Submission.c','ir/MainFull.c.o.export','ir/Submission.c.o.export','bin/benchFull.trace','ir/MainFull.c.o.export.trace'):write(g.BUILD/rel,b'FIXTURE NOT NATIVE BUILD\n')
        write(g.BUILD/'bin/benchFull.rsp',b'"-O3"\n');(g.LAYER/'upper').mkdir(parents=True)
        original=d.original_build(g);before=d.official_sources(g);prepared=d.prepare(g,g.WORK,p/'out')
        assert len(prepared['owned_files'])==2 and prepared['build_argv'][-1]=='r24ScalarF64Cost'
        assert d.original_build(g)==original and d.official_sources(g)==before
        assert (g.WORK.parent/'R24ScalarF64CostLake.lean').read_bytes().startswith(cfg)
        d.cleanup_owned(prepared);assert all(not Path(x).exists() for x in prepared['owned_files'])
        stages=a.stages(g,g.WORK,p/'stage',manifest);assert [x[0] for x in stages]==['runtime-cost-diagnostic']
        request=dict(manifest);request['diagnostic_timeout_seconds']=180
        try:a.stages(g,g.WORK,p/'reject',request)
        except AssertionError:pass
        else:raise AssertionError('Wrong timeout accepted')
    checks.append('Preparation/cleanup2 owned files, original metadata unchanged, exact stage registration and wrong-timeout rejection')
    report={'status':'LOCAL_PYTHON_PREFLIGHT_PASS_REMOTE_NOT_RUN','checks':checks,'finite_model_counts':counts,
       'finite_model_trace_sha256':trace.hexdigest(),'counterexamples':bad,'seconds':time.monotonic()-started,
       'source_sha256':sha(source),'proof':'NOT_RUN','Lean_typing':'NOT_RUN','native_execution':'NOT_RUN','performance':'UNKNOWN',
       'scope':'Finite diagnostics only; no universal double-round or GRS theorem. Legal-path cost must include UInt64 RNE, never infer it from opaque cast control.'}
    write(HERE/'local-preflight.json',json.dumps(report,indent=2)+'\n')
    ready=json.loads((HERE/'READY.json').read_bytes());ready.update(status='READY_FOR_PARENT_REVIEW_AND_COST_DIAGNOSTIC',local_preflight='local-preflight.json',Lean_and_performance='NOT_RUN')
    write(HERE/'READY.json',json.dumps(ready,indent=2)+'\n')
    print(json.dumps({'status':report['status'],'counts':counts,'seconds':report['seconds'],'source':report['source_sha256']}))
if __name__=='__main__':main()
