"""Small Python-only preflight of changed packaging, paths and domain parser."""
from pathlib import Path
from types import SimpleNamespace
import ast
import hashlib
import importlib.util
import json
import tempfile

HERE=Path(__file__).resolve().parent
ROOT=next(p for p in HERE.parents if (p/'AGENTS.md').is_file())
PUB=ROOT/'competitions/floatlib/candidates'
CANDIDATE=PUB/'f01-r24-dev-scalar-routes-cost1'
sha=lambda p:hashlib.sha256(Path(p).read_bytes()).hexdigest()
def load(path,name):
    spec=importlib.util.spec_from_file_location(name,path)
    m=importlib.util.module_from_spec(spec);spec.loader.exec_module(m);return m
def write(p,raw):
    p.parent.mkdir(parents=True,exist_ok=True);p.write_bytes(raw)

def main():
    checks=[]
    for p in HERE.glob('*.py'):ast.parse(p.read_bytes())
    d=load(HERE/'driver.py','r24_scalar_preflight_driver')
    audit=load(HERE/'scalar-cost-audit.py','r24_scalar_preflight_stage')
    manifest=json.loads((CANDIDATE/'manifest.json').read_bytes())
    assert sha(CANDIDATE/'Kernel.lean')==manifest['candidate_sha256']==d.SOURCE==audit.SOURCE
    assert (CANDIDATE/'Kernel.lean').stat().st_size<=256000
    old=PUB/'f01-r23-dev-outline-public1/Kernel.lean'
    assert (CANDIDATE/'Kernel.lean').read_bytes().startswith(old.read_bytes())
    for item in manifest['components']:
        p=ROOT/item['path'];assert sha(p)==item['sha256'] and p.stat().st_size==item['bytes']
    assert manifest['helper_audit_module_path'].endswith('development-scalar/scalar-cost-audit.py')
    for p,expected in d.PINS.items():assert sha(p)==expected
    checks.append('AST, exact f90 prefix, byte cap, all component/helper hashes and legacy helper pins')
    assert len(d.ORDER)==16 and len(d.SEEDS)==2 and len(d.VARIANTS)==4
    assert d.normalize(['/x/MainFull.c','/x/benchFull','-O3'])==d.normalize(['/x/R24ScalarCostMain.c','/x/r24ScalarCost','-O3'])
    assert d.normalize(['/x/MainFull.c','-O3'])!=d.normalize(['/x/R24ScalarCostMain.c','-O3','-ffast-math'])
    checks.append('32 measured processes, ABBA pairs and only target/root normalization')
    plan={'cases':[{'name':'example','kernel':'mul','work':4}]}
    log='DOMAIN example 4 1 1 1 1 12\nEXAMPLE example 1065353216 1065353216 8388608 1065353216 1593835520 1602224128 0 2139095040\n'
    parsed=d.parse_domains(log,plan)
    assert parsed['example']['neither']==1 and len(parsed['example']['first_examples_if_count_positive'])==4
    for bad in (log.replace(' 4 1 1 1 1 ', ' 5 1 1 1 1 '),log.splitlines()[0],log+log):
        try:d.parse_domains(bad,plan)
        except RuntimeError:pass
        else:raise AssertionError('Malformed domain census accepted')
    checks.append('Domain parser accepts complete partition and refuses total/missing/duplicate records')
    with tempfile.TemporaryDirectory(dir=HERE,prefix='preflight-') as tmp:
        p=Path(tmp).resolve();assert p.is_relative_to(HERE.resolve())
        g=SimpleNamespace(HERE=p,LIB=p/'lean',BUILD=p/'lean/.lake/build',LAYER=p/'layer',
            WORK=p/'lean/work/Submission.lean',LAKE='lake',_SANDBOX=True,_BUILD_TIMEOUT=1800,
            _BUILD_MEMORY_MB=4096,_BENCH_MEMORY_MB=512,STAGES=[('intake',None),('policy',None),('statement',None)],
            OWN_STEMS={'Submission','MainFull'})
        g.foreign=lambda upper:[]
        gate=PUB/'f01-d7-research/official-policy/gate-4b7e838.raw'
        write(g.HERE/'gate.py',gate.read_bytes());assert sha(g.HERE/'gate.py')==d.GATE
        write(g.HERE/'benchmark_suite.py',b'# Python-only fixture\n')
        write(g.HERE/'suites/public-v2.json',b'{}\n')
        write(g.WORK,(CANDIDATE/'Kernel.lean').read_bytes())
        cfg=b'import Lake\nopen Lake DSL\npackage competition where\nlean_exe benchFull where\n  srcDir := "bench"\n  root := `MainFull\n'
        write(g.LIB/'lakefile.lean',cfg);write(g.LIB/'lake-manifest.json',b'{}\n');write(g.LIB/'lean-toolchain',b'leanprover/lean4:v4.34.0\n')
        for rel in ('bin/benchFull','ir/MainFull.c','ir/Submission.c','ir/MainFull.c.o.export','ir/Submission.c.o.export','bin/benchFull.trace','ir/MainFull.c.o.export.trace'):
            write(g.BUILD/rel,b'SYNTHETIC FIXTURE: NOT A BUILD\n')
        write(g.BUILD/'bin/benchFull.rsp',b'"-O3"\n')
        (g.LAYER/'upper').mkdir(parents=True)
        before=d.official_sources(g);original=d.original_build(g)
        prepared=d.prepare(g,g.WORK,p/'out')
        assert len(prepared['owned_files'])==3
        assert prepared['build_argv'][-2:]==['r24ScalarCost','r24ScalarDomain']
        assert d.official_sources(g)==before and d.original_build(g)==original
        assert (g.WORK.parent/'R24ScalarCostLake.lean').read_bytes().startswith(cfg)
        assert (g.WORK.parent/'R24ScalarDomainMain.lean').is_file()
        d.cleanup_owned(prepared)
        assert all(not Path(x).exists() for x in prepared['owned_files'])
        stages=audit.stages(g,g.WORK,p/'audit',manifest)
        assert len(stages)==1 and stages[0][0]=='runtime-cost-diagnostic'
        for bad in ('score','source','timeout'):
            request=dict(manifest)
            if bad=='score':g.STAGES.append(('score',None))
            elif bad=='source':write(g.WORK,b'WRONG')
            else:request['diagnostic_timeout_seconds']=180
            try:audit.stages(g,g.WORK,p/'reject',request)
            except AssertionError:pass
            else:raise AssertionError('Bad stage registration accepted')
            g.STAGES=[('intake',None),('policy',None),('statement',None)]
            write(g.WORK,(CANDIDATE/'Kernel.lean').read_bytes())
    checks.append('Python-only preparation creates/cleans all 3 owned work files; original metadata unchanged')
    checks.append('Stage registration validates exact manifest and refuses score/source/timeout drift')
    result={'status':'LOCAL_PYTHON_PREFLIGHT_PASS_REMOTE_NOT_RUN','checks':checks,'Lean_build':'NOT_RUN','native_benchmark':'NOT_RUN','full_gate':'NOT_RUN','performance':'UNKNOWN','fixture_only':True}
    (HERE/'local-preflight.json').write_text(json.dumps(result,indent=2)+'\n',encoding='utf-8')
    ready=json.loads((HERE/'READY.json').read_bytes());ready['status']='READY_FOR_PARENT_REVIEW_AND_STATEMENT_DIAGNOSTIC'
    ready['local_preflight']='local-preflight.json';ready['remote_Lean_and_performance']='NOT_RUN'
    (HERE/'READY.json').write_text(json.dumps(ready,indent=2)+'\n',encoding='utf-8')
    print(json.dumps({'checks':len(checks),'pass':True,'Lean':'NOT_RUN','performance':'UNKNOWN'}))
if __name__=='__main__':main()
