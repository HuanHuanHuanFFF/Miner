"""Python-only checks of actual preparation/parser, using explicitly synthetic metadata."""
from pathlib import Path
from types import SimpleNamespace
import ast, hashlib, importlib.util, json, tempfile

HERE=Path(__file__).resolve().parent
ROOT=next(p for p in HERE.parents if (p/'AGENTS.md').is_file())
def load(name,path):
    s=importlib.util.spec_from_file_location(name,path);m=importlib.util.module_from_spec(s);s.loader.exec_module(m);return m
driver=load('dot_preflight_driver',HERE/'driver.py');parser=load('dot_preflight_parser',HERE/'parse-results.py')
caller=load('dot_preflight_callers',HERE/'audit-callers.py')
for p in HERE.glob('*.py'):ast.parse(p.read_bytes())
fixture=json.loads((HERE/'fixtures.json').read_bytes())
verify=[];accept=0;unknown=0
for c in fixture['cases']:
    q=c['fast_result'] if c['fast_result'] is not None else 0
    accept+=q!=0;unknown+=c['fast_result'] is None
    verify.append('\t'.join(map(str,['DOT_VERIFY',c['name'],c['expected'],q,q]+[c['expected']]*8+['true'])))
for c in fixture['round_cases']:verify.append('\t'.join(map(str,['DOT_ROUND',c['id'],c['expected'],c['expected'],'true'])))
verify.append('\t'.join(map(str,['DOT_VERIFY_DONE',len(fixture['cases']),len(fixture['round_cases']),accept,unknown])))
text='\n'.join(verify)+'\n';v=parser.verify(text,fixture)
for bad in ['\n'.join(verify[1:])+'\n',text+verify[0]+'\n',text.replace('\ttrue','\tfalse',1)]:
    try:parser.verify(bad,fixture)
    except ValueError:pass
    else:raise AssertionError('Incomplete/duplicate/rejected numerical output accepted')
group='24282403';timing=[]
for c in fixture['cases']:
    if not c['timed'] or c['group'] not in (group,'directed'):continue
    n=len(c['x']);iters=max(1,(131072+n-1)//n)
    for trial in range(3):
        sink=(1664525*trial+2654435769+iters*c['expected'])&((1<<32)-1)
        timing.append('\t'.join(map(str,['DOT_SAMPLE',c['name'],c['group'],'exact','full',trial,n,iters,n*iters,1000+trial,sink,sink,c['expected']])))
    timing.append('\t'.join(map(str,['DOT_SETUP',c['name'],c['group'],'exact','full',0,5000,3,c['expected']])))
timing.append('DOT_MEASURE_DONE\t24282403\texact\tfull\t49\t3')
t='\n'.join(timing)+'\n';rows=parser.rows(t,fixture,group);assert len(rows)==49
for bad in ['\n'.join(timing[1:])+'\n',t+timing[0]+'\n','\n'.join(timing[:-1])+'\n',t+timing[-1]+'\n',t.replace('\texact\tfull\t0\t','\texact\tfull\t9\t',1)]:
    try:parser.rows(bad,fixture,group)
    except ValueError:pass
    else:raise AssertionError('Incomplete/duplicate/badtrial timing accepted')
sample='''10: R_X86_64_PLT32 lp_R24DotBarrier_touchRaw-0x4
20: R_X86_64_PLT32 lp_Submission_R24DotProbe_exactFull-0x4
30: jne 0
'''
assert caller.loop_witness(sample,'exactFull')
assert not caller.loop_witness(sample.replace('20:','40:'),'exactFull')

with tempfile.TemporaryDirectory(dir=HERE,prefix='python-only-preflight-') as tmp:
    p=Path(tmp).resolve();assert p.is_relative_to(HERE.resolve())
    g=SimpleNamespace(HERE=p/'upstream',LIB=p/'upstream/lean',LAYER=p/'layer',_SANDBOX=True,LAKE='lake',STAGES=[('intake',None),('policy',None),('statement',None)])
    g.BUILD=g.LIB/'.lake/build';g.WORK=g.LIB/'work/Submission.lean';g.foreign=lambda _:[]
    g.own=lambda *a,**k: (_ for _ in ()).throw(AssertionError('No process allowed in local preflight'))
    def write(path,b):path.parent.mkdir(parents=True,exist_ok=True);path.write_bytes(b)
    write(g.HERE/'gate.py',(ROOT/'competitions/floatlib/candidates/f01-d7-research/official-policy/gate-4b7e838.raw').read_bytes())
    for rel in ['benchmark_suite.py','suites/public-v2.json']:write(g.HERE/rel,b'SYNTHETIC PYTHON-ONLY METADATA\n')
    config=b'import Lake\nopen Lake DSL\npackage competition where\nlean_exe benchFull where\n  srcDir := "bench"\n  root := `MainFull\n'
    write(g.LIB/'lakefile.lean',config)
    for rel in ['lake-manifest.json','lean-toolchain']:write(g.LIB/rel,b'SYNTHETIC PYTHON-ONLY METADATA\n')
    for rel in ['bin/benchFull','ir/MainFull.c','ir/Submission.c','ir/MainFull.c.o.export','ir/Submission.c.o.export','bin/benchFull.trace','ir/MainFull.c.o.export.trace']:
        write(g.BUILD/rel,b'SYNTHETIC NOT A BUILD\n')
    write(g.BUILD/'bin/benchFull.rsp',b'"-O3"\n');(g.LAYER/'upper').mkdir(parents=True)
    candidate=ROOT/'competitions/floatlib/candidates/f01-r24-dev-dot-cost1'
    write(g.WORK,(candidate/'Kernel.lean').read_bytes());m=json.loads((candidate/'manifest.json').read_bytes())
    old=driver.support();before=old.official_sources(g);objects=old.original_build(g)
    prepared=driver.prepare(g,g.WORK,p/'out',m)
    assert len(prepared['owned_files'])==4 and old.official_sources(g)==before and old.original_build(g)==objects
    assert (g.WORK.parent/'R24DotCostLake.lean').read_bytes().startswith(config)
    assert b'lean_lib R24DotBarrier where' in (g.WORK.parent/'R24DotCostLake.lean').read_bytes()
    driver.cleanup(prepared);assert all(not Path(x).exists() for x in prepared['owned_files'])

result={'status':'PYTHON_ONLY_PREFLIGHT_PASS','scope':'Synthetic parser/metadata and actual preparation checks only; no process, Lean, native build or performance.',
    'checks':['All Python AST','Actual strict parser accepts complete148/1049 records','Missing/duplicate/rejected numerical rows refused',
        'Actual strict timing parser accepts49cases x3samples','Missing/duplicate/badtrial rows refused',
        'ASM parser distinguishes calls inside versus outside the backward loop','Actual prepare/cleanup writes only4ownedfiles, leaves original config/build metadata unchanged'],
    'native_typing':'NOT_RUN','native_oracle':'NOT_RUN','cost':'NOT_RUN','fixture_sha256':hashlib.sha256((HERE/'fixtures.json').read_bytes()).hexdigest()}
(HERE/'preflight-results.json').write_text(json.dumps(result,ensure_ascii=False,indent=2)+'\n',encoding='utf-8')
print(json.dumps({'pass':True,'checks':len(result['checks']),'native':'NOT_RUN'}))
