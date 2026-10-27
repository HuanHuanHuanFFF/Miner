"""Pure Python synthetic runner checks. NEVER Lean or real benchmark evidence."""
from pathlib import Path
from types import SimpleNamespace
import ast
import hashlib
import importlib.util
import json
import inspect
import time

HERE=Path(__file__).resolve().parent
ROOT=next(p for p in HERE.parents if (p/'competitions/floatlib/scripts/estimate_champion_time.py').is_file())
def load(path,name):
    spec=importlib.util.spec_from_file_location(name,path);m=importlib.util.module_from_spec(spec);spec.loader.exec_module(m);return m
d=load(HERE/'driver.py','cost_driver_local')
def write(p,raw):p.parent.mkdir(parents=True,exist_ok=True);p.write_bytes(raw)
def trace(argv):return d.encode({'synthetic':False,'log':[{'message':'.> '+' '.join('"'+x+'"' for x in argv)}]})


class Runner:
    """Artifact content is a synthetic fixture, never a native compiler output."""
    def __init__(self,name,mode='ok'):
        self.HERE=HERE/'synthetic-fixtures'/name
        assert not self.HERE.exists(),'Use a fresh test invocation suffix'
        self.LIB=self.HERE/'lean';self.BUILD=self.LIB/'.lake/build';self.LAYER=self.HERE/'layer'
        self.WORK=self.LIB/'work/Submission.lean';self.LAKE='lake';self._SANDBOX=True
        self._BUILD_TIMEOUT=1800;self._BUILD_MEMORY_MB=4096;self._BENCH_MEMORY_MB=512;self._BENCH_CPU=''
        self.STAGES=[('intake',None),('policy',None),('statement',None)];self._budget=SimpleNamespace(left=600)
        self.OWN_STEMS={'Submission','MainFull'};self.mode=mode;self.calls=[]
        gate=ROOT/'competitions/floatlib/candidates/f01-d7-research/official-policy/gate-4b7e838.raw'
        write(self.HERE/'gate.py',gate.read_bytes());write(self.HERE/'benchmark_suite.py',b'# synthetic\n')
        write(self.HERE/'suites/public-v2.json',b'{}\n')
        write(self.WORK,(ROOT/'competitions/floatlib/candidates/f01-r19-dev-runtime-cost1/Kernel.lean').read_bytes())
        write(self.LIB/'lakefile.lean',b'import Lake\nopen Lake DSL\npackage competition where\nlean_exe benchFull where\n  srcDir := "bench"\n  root := `MainFull\n')
        write(self.LIB/'lake-manifest.json',b'{}\n');write(self.LIB/'lean-toolchain',b'leanprover/lean4:v4.34.0\n')
        write(self.LIB/'contract/Contract.lean',b'-- synthetic original\n');write(self.LIB/'bench/MainFull.lean',b'-- synthetic original\n')
        for n in ('MainFull.c','Submission.c'):write(self.BUILD/'ir'/n,b'/*synthetic original*/\n')
        for n in ('MainFull.c.o.export','Submission.c.o.export'):write(self.BUILD/'ir'/n,b'\x7fELF_SYNTHETIC')
        write(self.BUILD/'bin/benchFull',b'\x7fELF_SYNTHETIC_CONTROL')
        self.emit_trace('MainFull','benchFull',False)
        (self.LAYER/'upper').mkdir(parents=True)

    def emit_trace(self,root,target,upper):
        base=self.LAYER/'upper' if upper else self.BUILD
        c=(self.BUILD/'ir'/(root+'.c')).as_posix();obj=c+'.o.export'
        write(base/'ir'/(root+'.c.o.export.trace'),trace(['clang','-c','-o',obj,c,'-O3','-ffp-contract=off','-DLEAN_EXPORTING']))
        binary=(self.BUILD/'bin'/target).as_posix()
        write(base/'bin'/(target+'.trace'),trace(['clang','-o',binary,'@'+binary+'.rsp']))
        args=[obj,(self.BUILD/'ir/Submission.c.o.export').as_posix(),'-O3','-lm']
        if self.mode=='flags' and upper:args.append('-ffast-math')
        write(base/'bin'/(target+'.rsp'),('\n'.join('"'+a+'"' for a in args)+'\n').encode())

    def foreign(self,upper):
        return sorted(str(p.relative_to(upper)) for p in upper.rglob('*') if p.is_file() and p.name.split('.')[0] not in self.OWN_STEMS)

    def own(self,argv,cap,**kw):
        self.calls.append({'argv':argv,'cap':cap,'kwargs':kw});self._budget.left-=0.01
        if argv[0]=='lake':
            if self.mode=='buildfail':return 1,'SYNTHETIC_BUILD_FAILURE\n'
            write(self.LAYER/'upper/ir/R19RuntimeCostMain.c',b'/*SYNTHETIC BENCH_VARIANT; no actual code generated*/\n'+(b'R19DirectBias_diagnosticEntry\n' if self.mode=='noinline' else b''))
            write(self.LAYER/'upper/ir/R19RuntimeCostMain.c.o.export',b'\x7fELF_SYNTHETIC_NEW')
            write(self.LAYER/'upper/bin/r19RuntimeCost',b'\x7fELF_SYNTHETIC_BINARY')
            self.emit_trace('R19RuntimeCostMain','r19RuntimeCost',True)
            if self.mode=='drift':write(self.LAYER/'upper/ir/Submission.c',b'DRIFT')
            if self.mode=='foreign':write(self.LAYER/'upper/ir/Unrelated.c',b'FOREIGN')
            return 0,'Built R19RuntimeCostMain\nBuilt r19RuntimeCost\n'+('Built BenchSuite\n' if self.mode=='dependency' else '')
        env=kw['env_extra'];plan=json.loads(env['BENCH_PLAN']);rows=[]
        for i,c in enumerate(plan['cases']):
            ns=(100+i)*(2 if env['BENCH_VARIANT']=='control' else 1) if c['timed'] else 0
            checksum=i+1+(1 if self.mode=='checksum' and env['BENCH_VARIANT']=='guarded' else 0)
            rows.append(f"{c['name']} {str(c['timed']).lower()} {ns} {checksum}")
        if self.mode=='rows':rows.pop()
        return 0,'\n'.join(rows)+'\n'


def main():
    results=[];tag=str(time.time_ns())
    for p in (HERE/'driver.py',HERE.parent/'development-runtime-cost-audit.py',Path(__file__)):
        ast.parse(p.read_bytes());results.append({'check':'AST '+p.name,'pass':True})
    t=[100.0];b=d.Budget(200,lambda:t[0]);assert b.cap('build',180,52)==48
    t[0]=148;assert b.cap('measure',120,20,170)==22
    t[0]=181
    try:b.cap('expired',120,20);raise AssertionError('Budget accepted exhausted phase')
    except RuntimeError:pass
    results.append({'check':'one absolute budget phase/reserve/exhaustion','pass':True})
    real_load=d.load_module
    class Capture:
        @staticmethod
        def _bounded_tool(argv,artifact,seconds,limit):
            artifact.write_bytes(b'SYNTHETIC TOOL OUTPUT; NOT ASM\n');return {'ok':True,'argv':argv,'timeout_seconds':seconds,'artifact':artifact.name,'synthetic':True}
    d.load_module=lambda path,name: Capture if path==d.CAPTURE else real_load(path,name)
    for mode in ('ok','buildfail','flags','drift','checksum','rows','foreign','dependency','noinline'):
        g=Runner(tag+'-'+mode,mode);out=g.HERE/'out';prepared=d.prepare(g,g.WORK,out)
        assert (g.WORK.parent/'R19RuntimeCostLake.lean').read_bytes().startswith((g.LIB/'lakefile.lean').read_bytes())
        failed=False
        try:d.build_and_measure(g,prepared,out,time.monotonic()+580)
        except (RuntimeError,AssertionError):failed=True
        record=json.loads((out/'result.json').read_bytes())
        assert failed==(mode!='ok'),(mode,record)
        assert all(c['cap']<=180 and c['kwargs']['build'] in ('write','read') for c in g.calls)
        if mode=='ok':
            assert record['complete'] is True and len(record['runs'])==8 and len(record['pairs'])==2
            for seed in record['pairs']:
                for block in ('block_0','block_1'):
                    assert seed[block]['whole']['cases']==152
                    assert all(x['guarded_over_control']==0.5 for x in seed[block].values())
            assert len(list(out.glob('*-rows.json')))==8
        if mode in ('buildfail','flags','drift','foreign','dependency','noinline'):assert len(g.calls)==1,'Timing ran after stop condition'
        if mode=='buildfail':assert (out/'build.log').read_text()=='SYNTHETIC_BUILD_FAILURE\n'
        d.cleanup_owned(prepared)
        assert not (g.WORK.parent/'R19RuntimeCostMain.lean').exists()
        results.append({'check':'synthetic full driver '+mode,'pass':True,'calls':len(g.calls),'fixture':str(g.HERE.relative_to(HERE))})
    audit=load(HERE.parent/'development-runtime-cost-audit.py','cost_audit_local')
    manifest=json.loads((ROOT/'competitions/floatlib/candidates/f01-r19-dev-runtime-cost1/manifest.json').read_bytes())
    for mode in ('ok','buildfail'):
        g=Runner(tag+'-audit-'+mode,mode);out=g.HERE/'integration'
        stages=audit.stages(g,g.WORK,out,manifest)
        assert [n for n,_ in stages]==['runtime-cost-diagnostic']
        callback=stages[0][1];module=inspect.getclosurevars(callback).nonlocals['module'];original_load=module.load_module
        module.load_module=lambda path,name: Capture if path==module.CAPTURE else original_load(path,name)
        before=set(g.OWN_STEMS);reason=callback(g.WORK,SimpleNamespace())
        receipt=json.loads((out/'runtime-cost/stage-receipt.json').read_bytes())
        assert (reason is None)==(mode=='ok') and set(g.OWN_STEMS)==before
        assert receipt['original7root_replay']=='HISTORICAL40420540388_BOUND_NOT_RERUN'
        assert receipt['owned_work_sources_cleanup']=='EXACT_HASH_REMOVED'
        assert all(not any('leanchecker' in str(x) for x in c['argv']) for c in g.calls)
        results.append({'check':'audit registration/callback/cleanup '+mode,'pass':True,'calls':len(g.calls)})
    for bad in ('score','timeout','source'):
        g=Runner(tag+'-reject-'+bad);request=dict(manifest)
        if bad=='score':g.STAGES.append(('score',None))
        if bad=='timeout':request['diagnostic_timeout_seconds']=120
        if bad=='source':g.WORK.write_bytes(b'WRONG_SOURCE')
        try:audit.stages(g,g.WORK,g.HERE/'integration',request);raise RuntimeError('Unsafe registration accepted')
        except AssertionError:pass
        assert not g.calls
        results.append({'check':'registration refuses '+bad,'pass':True})
    parser=real_load(d.R13,'reused_parser_local');plan=json.loads((HERE/'plan-1927003.json').read_bytes())
    assert len(plan['cases'])==156 and sum(c['timed'] for c in plan['cases'])==152
    report={'status':'LOCAL_PYTHON_CHECKS_PASS_REMOTE_NOT_RUN','actual_Lean_build':'NOT_RUN','actual_benchmark':'NOT_RUN','synthetic_fixture_only':True,'checks':results}
    (HERE/'local-verification.json').write_bytes(d.encode(report));print(json.dumps({'checks':len(results),'all_pass':True,'remote':'NOT_RUN'}))
if __name__=='__main__':main()
