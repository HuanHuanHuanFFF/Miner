"""Collect diagnostic compilation output separately from the original full gate.

Replay stops at statement compilation and is never an acceptance result.
The original upstream files and original verdict remain unchanged.
"""
from pathlib import Path
import argparse,json,os,signal,subprocess,sys,time

def main():
    ap=argparse.ArgumentParser();ap.add_argument('--upstream',type=Path,required=True);ap.add_argument('--kernel',type=Path,required=True);ap.add_argument('--reports',type=Path,required=True);ap.add_argument('--name',required=True);ap.add_argument('--verdict',type=Path,required=True);ap.add_argument('--compile-only',action='store_true');a=ap.parse_args()
    out=a.reports/'diagnostics'/a.name;out.mkdir(parents=True,exist_ok=True)
    original=json.loads(a.verdict.read_bytes()) if a.verdict.exists() else {}
    report={'diagnostic_only':True,'original_stage':original.get('stage'),'original_verdict_unchanged':True,'generated_c':[]}
    if a.compile_only or original.get('stage') in {'statement','score'}:
        code=r'''
import importlib.util,sys,json,hashlib,fcntl,re,subprocess
from dataclasses import asdict
from pathlib import Path
upstream,kernel,out,profiler=map(Path,sys.argv[1:]);sys.path.insert(0,str(upstream))
spec=importlib.util.spec_from_file_location('floatlib_gate_diagnostic',upstream/'gate.py');g=importlib.util.module_from_spec(spec);sys.modules[spec.name]=g;spec.loader.exec_module(g)
old_errors=g.errors
def full_errors(text,*args,**kwargs):
    with (out/'full-build-output.txt').open('a',encoding='utf-8') as stream: stream.write(text+'\n')
    print('DIAGNOSTIC COMPLETE BUILD OUTPUT\n'+text,flush=True)
    return old_errors(text,*args,**kwargs)
g.errors=full_errors
original_statement=g.statement
def statement(src,verdict):
    reason=original_statement(src,verdict)
    if not reason:
        rows=[]
        paths = [path for path in (g.LAYER/'upper').rglob('*.c')
                 if path.name == 'Submission.c' or path.name.startswith(('Main', 'Bench'))]
        paths.sort(key=lambda path: (path.name != 'Submission.c', str(path)))
        for path in paths:
            if path.is_file() and path.stat().st_size<8_000_000:
                name='candidate-generated-'+str(len(rows))+'.c';data=path.read_bytes();(out/name).write_bytes(data)
                rows.append({'source':str(path),'module':path.stem,'file':name,'sha256':hashlib.sha256(data).hexdigest(),'kernel_sha256':hashlib.sha256(kernel.read_bytes()).hexdigest(),'scope':'Successful statement and bench-build layer captured before gate cleanup'})
        (out/'candidate-c-index.json').write_text(json.dumps(rows,indent=2)+'\n',encoding='utf-8')
        # Inspect the object the unchanged official build actually produced.
        # No recompilation, flags, gate inputs or measured binary are changed.
        objects=[]
        def optional_object_tool(argv, object_data, **kwargs):
            try:
                result=subprocess.run(argv,**kwargs)
            except (subprocess.TimeoutExpired,OSError) as error:
                details={'error_type':type(error).__name__,'error':str(error)}
            else:
                if result.returncode == 0:
                    return result
                stderr=result.stderr or ''
                if isinstance(stderr,bytes):
                    stderr=stderr.decode('utf-8',errors='replace')
                details={'exit_code':result.returncode,'error':stderr}
            objects.append({'kind':'optional-built-object-capture','state':'UNKNOWN',
                            'tool':argv[0],'source':argv[-1],
                            'object_sha256':hashlib.sha256(object_data).hexdigest(),
                            'symbol':next((arg.split('=',1)[1] for arg in argv if arg.startswith('--disassemble=')),None),
                            **details})
            return None
        for path in (g.LAYER/'upper').rglob('*'):
            if not path.is_file() or not ('Submission' in path.name or 'MainFull' in path.name):
                continue
            if path.suffix == '.trace' and path.stat().st_size < 1_000_000:
                data=path.read_bytes();name='build-trace-'+str(len(objects))+'.txt'
                (out/name).write_bytes(data)
                objects.append({'kind':'trace','source':str(path),'file':name,'sha256':hashlib.sha256(data).hexdigest()})
            if '.o' not in path.name or path.stat().st_size > 8_000_000:
                continue
            data=path.read_bytes()
            if not data.startswith(b'\x7fELF'):
                continue
            symbols=optional_object_tool(['nm','--defined-only',str(path)],data,capture_output=True,text=True,timeout=15)
            if symbols is None:
                continue
            names=[line.split()[-1] for line in symbols.stdout.splitlines() if line.split()]
            names=[name for name in names if 'boxed' not in name and ((name.startswith('lp_competition_Submission_') and (('loop' in name.lower() and ('Packed' in name or 'NativeDecodeSum' in name or 'Tile' in name or 'R19Temporal' in name or 'R19DualTemporal' in name or 'R19DCRawPair' in name)) or name in ('lp_competition_Submission_R17NumericMulInteger_normalCore','lp_competition_Submission_R17NumericMulInteger_diagnosticEntry','lp_competition_Submission_R19Jam17_normalCore','lp_competition_Submission_R19Jam17_diagnosticEntry','lp_competition_Submission_R19DirectBias_normalCore','lp_competition_Submission_R19DirectBias_diagnosticEntry','lp_competition_Submission_R19GRS32Add_alignNonzero','lp_competition_Submission_R19GRS32Add_guardedAdd','lp_competition_Submission_R19GRS32Add_diagnosticEntry','lp_competition_Submission_add','lp_competition_Submission_mul','lp_competition_Submission_nativeMul'))) or name in ('lp_competition_R2W01b_fastOK','lp_competition_R2W01b_convert','lp_competition_main___lam__0','lp_competition_main___lam__1','lp_competition_main___lam__3'))]
            # The retained DC loop is the comparator for R19's actual pair loop.
            # Capture it from the same statement object and keep call relocations.
            if path.name.startswith('Submission'):
                all_names=[line.split()[-1] for line in symbols.stdout.splitlines() if line.split()]
                comparators = ('lp_competition_Submission_NativeFinal_dotLoop',
                    'lp_competition_Fin_foldl_loop___at___00Submission_R19DCRawPair_output_spec__2')
                names += [name for name in all_names if name in comparators and name not in names]
                new_core_functions = [line.split()[-1] for line in symbols.stdout.splitlines()
                    if len(line.split()) >= 3 and line.split()[-2] in ('T','t')]
                names += [name for name in new_core_functions if name not in names and 'boxed' not in name
                    and (name.startswith('lp_competition_Submission_R19Column4Temporal_')
                         or (name.startswith('lp_competition_Fin_foldl_loop_') and 'R19Column4Temporal' in name))
                    and any(part in name for part in ('loop','runDot','pack'))]
                names += [name for name in new_core_functions if name not in names and 'boxed' not in name
                    and name.startswith(('lp_competition_Submission_R20TerminalPair_',
                                         'lp_competition_Submission_R20RowBroadcast_'))
                    and any(part in name for part in ('loop', 'runDot', 'control', 'terminal', 'row8'))]
                names += [name for name in new_core_functions if name not in names and 'boxed' not in name
                    and name.startswith('lp_competition_Submission_R21StreamingPair_')
                    and any(part in name for part in ('loop', 'advance', 'updateCell', 'streamed', 'control'))]
                names += [name for name in new_core_functions if name not in names and 'boxed' not in name
                    and name.startswith('lp_competition_Submission_R21ScaledU32_')
                    and any(part in name for part in ('normalCore', 'guardedMul', 'diagnosticEntry'))]
                names += [name for name in new_core_functions if name not in names and 'boxed' not in name
                    and any(part in name for part in ('R22StreamingQuad', 'R22PreparedQuad', 'R22Pair8', 'R22Resident8', 'R22Resident16', 'R22IndexedResident8', 'R22OutlineMul', 'R22WordCarry', 'R22NativeProductScale', 'R22NativeCold', 'R22ExtremeNativeCold', 'R22FarOnlyAdd', 'R22Log2SourceProbe', 'R22BroadWordAdd', 'R22FloatProduct', 'R22SameExponent'))
                    and any(part in name for part in ('loop', 'advance', 'update', 'rows4', 'guarded', 'normalCore', 'core', 'diagnosticEntry', 'retainedMul', 'packRow', 'packB', 'packA', 'tile', 'wordLoop', 'runDot', 'word32', 'word64', 'hotMul', 'inlineMul', 'coldMul', 'coldAdd', 'endpointMiss'))]
                names += [name for name in new_core_functions if name not in names and 'boxed' not in name
                    and 'R22FlatScale' in name
                    and any(part in name for part in ('pick', 'lookup', 'convert', 'add', 'mul', 'nativeMul'))]
            for symbol in names:
                result=optional_object_tool(['objdump','-dr','--no-show-raw-insn','-Mintel','--disassemble='+symbol,str(path)],data,capture_output=True,timeout=15)
                if result is None:
                    continue
                name='native-loop-'+str(len(objects))+'.asm.txt';(out/name).write_bytes(result.stdout)
                objects.append({'kind':'actual-built-object-disassembly','source':str(path),'object_sha256':hashlib.sha256(data).hexdigest(),'symbol':symbol,'file':name,'sha256':hashlib.sha256(result.stdout).hexdigest(),'exit_code':result.returncode,'kernel_sha256':hashlib.sha256(kernel.read_bytes()).hexdigest(),'scope':'Diagnostic statement replay using the unchanged pinned build; this is not the cleaned-up timed gate object.'})
        (out/'native-assembly-index.json').write_text(json.dumps(objects,indent=2)+'\n',encoding='utf-8')
        if kernel.parent.name in ('f01-d5-costsplit', 'f01-d6-costsplit'):
            try:
                profile_path = profiler if kernel.parent.name == 'f01-d5-costsplit' else profiler.parent.parent/'f01-d6-research/profile-scored.py'
                ps=importlib.util.spec_from_file_location('candidate_cost_profile',profile_path)
                pm=importlib.util.module_from_spec(ps);ps.loader.exec_module(pm)
                pm.run(g,kernel,out)
            except Exception as error:
                import traceback
                (out/'profile-error.txt').write_text(traceback.format_exc(),encoding='utf-8')
        if kernel.parent.name == 'f01-d13-cost-profile':
            adapter=profiler.parent.parent/'f01-d7-research/round3h-20261024T112622Z/profile-suite.py'
            ps=importlib.util.spec_from_file_location('r13_separate_cost_diagnostic',adapter)
            pm=importlib.util.module_from_spec(ps);ps.loader.exec_module(pm)
            pm.run(g,kernel,out)
        if kernel.parent.name in ('f01-d6-public-suite','f01-d7-public-suite'):
            research_dir='f01-d6-research' if kernel.parent.name=='f01-d6-public-suite' else 'f01-d7-research'
            adapter=profiler.parent.parent/research_dir/'public-suite.py'
            if kernel.parent.name=='f01-d7-public-suite':
                request=json.loads((profiler.parent.parent/'f01-d7-public-suite/suite-plan.json').read_bytes())
                if request.get('r22_cost_diagnostic'):
                    assert not request.get('profile_current') and not request.get('confirmation_candidates')
                    adapter=profiler.parent.parent/research_dir/'round6h-20261027T211247Z/development-cost-suite.py'
                elif request.get('profile_current'):
                    adapter=profiler.parent.parent/research_dir/'round2h-20261023T170031Z/profile-wrapper.py'
            ps=importlib.util.spec_from_file_location('current_public_suite',adapter)
            pm=importlib.util.module_from_spec(ps);ps.loader.exec_module(pm)
            pm.run(g,kernel,out)
    return reason
g.STAGES=[('intake',g.intake),('policy',g.policy),('statement',statement)]
if kernel.parent.name.startswith('f01-r23-'):
    manifest_path=profiler.parent.parent/kernel.parent.name/'manifest.json'
    helper_manifest=json.loads(manifest_path.read_bytes())
    if helper_manifest.get('helper_audit_module_sha256'):
        helper_relative=Path(helper_manifest['helper_audit_module_path'])
        assert not helper_relative.is_absolute() and '..' not in helper_relative.parts
        helper_path=(profiler.parent.parent/helper_relative).resolve()
        allowed_root=(profiler.parent.parent/'f01-d7-research/round40m-20261028T142626Z').resolve()
        legacy=(profiler.parent.parent/'f01-d7-research/round9h-20261026T194639Z/development-helper-audit-v8.py').resolve()
        assert helper_path.is_relative_to(allowed_root) or helper_path==legacy
        assert hashlib.sha256(helper_path.read_bytes()).hexdigest()==helper_manifest['helper_audit_module_sha256']
        hs=importlib.util.spec_from_file_location('r23_explicit_diagnostic_audit',helper_path)
        hm=importlib.util.module_from_spec(hs);hs.loader.exec_module(hm)
        g.STAGES += hm.stages(g,kernel,out,helper_manifest)
elif kernel.parent.name.startswith('f01-r22-'):
    manifest_path=profiler.parent.parent/kernel.parent.name/'manifest.json'
    helper_manifest=json.loads(manifest_path.read_bytes())
    if helper_manifest.get('helper_audit_module_sha256'):
        helper_name=helper_manifest['helper_audit_module']
        if kernel.parent.name in ('f01-r22-dev-runtime-cost1', 'f01-r22-dev-runtime-cost2', 'f01-r22-dev-runtime-cost3', 'f01-r22-dev-flat-scale-cost1', 'f01-r22-dev-flat-scale-cost2', 'f01-r22-dev-pair8-cost1', 'f01-r22-dev-resident8-cost1', 'f01-r22-dev-broadword-cost1', 'f01-r22-dev-multistatic-cost1', 'f01-r22-dev-farstatic-cost1', 'f01-r22-dev-nativecold-cost1', 'f01-r22-dev-indexed8-cost1', 'f01-r22-dev-outline-isolation1', 'f01-r22-dev-wordcarry-cost1', 'f01-r22-dev-nat-prefix1', 'f01-r22-dev-nat-bias-repair1', 'f01-r22-dev-endpoint-cost1', 'f01-r22-dev-nat-light-repair1'):
            assert helper_name == {'f01-r22-dev-runtime-cost1':'development-cost-audit.py',
                                   'f01-r22-dev-runtime-cost2':'development-cost2-audit.py',
                                   'f01-r22-dev-runtime-cost3':'development-cost3-audit.py',
                                   'f01-r22-dev-flat-scale-cost1':'development-flat-cost-audit.py',
                                   'f01-r22-dev-flat-scale-cost2':'development-flat-cost2-audit.py',
                                   'f01-r22-dev-pair8-cost1':'development-pair8-cost-audit.py',
                                   'f01-r22-dev-resident8-cost1':'development-resident8-cost-audit.py',
                                   'f01-r22-dev-broadword-cost1':'development-broadword-cost-audit.py',
                                   'f01-r22-dev-multistatic-cost1':'development-multistatic-cost-audit.py',
                                   'f01-r22-dev-farstatic-cost1':'development-farstatic-cost-audit.py',
                                   'f01-r22-dev-nativecold-cost1':'development-nativecold-cost-audit.py',
                                   'f01-r22-dev-indexed8-cost1':'development-indexed8-cost-audit.py',
                                   'f01-r22-dev-outline-isolation1':'development-outline-isolation-audit.py',
                                   'f01-r22-dev-wordcarry-cost1':'development-wordcarry-cost-audit.py',
                                   'f01-r22-dev-nat-prefix1':'development-nat-prefix-audit.py',
                                   'f01-r22-dev-nat-bias-repair1':'development-nat-bias-repair-audit.py',
                                   'f01-r22-dev-endpoint-cost1':'development-endpoint-cost-audit.py',
                                   'f01-r22-dev-nat-light-repair1':'development-nat-light-repair-audit.py'}[kernel.parent.name]
            helper_path=profiler.parent.parent/'f01-d7-research/round6h-20261027T211247Z'/helper_name
        else:
            assert helper_name == 'development-helper-audit-v8.py'
            helper_path=profiler.parent.parent/'f01-d7-research/round9h-20261026T194639Z'/helper_name
        assert hashlib.sha256(helper_path.read_bytes()).hexdigest()==helper_manifest['helper_audit_module_sha256']
        hs=importlib.util.spec_from_file_location('r22_explicit_diagnostic_audit',helper_path)
        hm=importlib.util.module_from_spec(hs);hs.loader.exec_module(hm)
        g.STAGES += hm.stages(g,kernel,out,helper_manifest)
elif kernel.parent.name.startswith(('f01-r20-', 'f01-r21-')):
    manifest_path=profiler.parent.parent/kernel.parent.name/'manifest.json'
    helper_manifest=json.loads(manifest_path.read_bytes())
    if helper_manifest.get('helper_audit_module_sha256'):
        helper_name='development-helper-audit-v8.py'
        assert helper_manifest['helper_audit_module']==helper_name
        helper_path=profiler.parent.parent/'f01-d7-research/round9h-20261026T194639Z'/helper_name
        assert hashlib.sha256(helper_path.read_bytes()).hexdigest()==helper_manifest['helper_audit_module_sha256']
        hs=importlib.util.spec_from_file_location('r20_explicit_math_helper_audit',helper_path)
        hm=importlib.util.module_from_spec(hs);hs.loader.exec_module(hm)
        g.STAGES += hm.stages(g,kernel,out,helper_manifest)
elif kernel.parent.name == 'f01-r16-dev-u32-roundtrip-probe1':
    manifest_path=profiler.parent.parent/kernel.parent.name/'manifest.json'
    helper_manifest=json.loads(manifest_path.read_bytes())
    helper_path=profiler.parent.parent/'f01-d7-research/round3h-20261025T091810Z/development-helper-audit.py'
    assert hashlib.sha256(helper_path.read_bytes()).hexdigest()==helper_manifest['helper_audit_module_sha256']
    hs=importlib.util.spec_from_file_location('r16_explicit_math_helper_audit',helper_path)
    hm=importlib.util.module_from_spec(hs);hs.loader.exec_module(hm)
    g.STAGES += hm.stages(g,kernel,out,helper_manifest)
elif kernel.parent.name.startswith('f01-r17-dev-'):
    manifest_path=profiler.parent.parent/kernel.parent.name/'manifest.json'
    helper_manifest=json.loads(manifest_path.read_bytes())
    if helper_manifest.get('helper_audit_module_sha256'):
        helper_name=helper_manifest.get('helper_audit_module','development-helper-audit.py')
        assert helper_name in ('development-helper-audit.py','development-helper-audit-v2.py','development-helper-audit-v3.py')
        helper_path=profiler.parent.parent/'f01-d7-research/round11h-20261025T173831Z'/helper_name
        assert hashlib.sha256(helper_path.read_bytes()).hexdigest()==helper_manifest['helper_audit_module_sha256']
        hs=importlib.util.spec_from_file_location('r18_explicit_math_helper_audit',helper_path)
        hm=importlib.util.module_from_spec(hs);hs.loader.exec_module(hm)
        g.STAGES += hm.stages(g,kernel,out,helper_manifest)
elif kernel.parent.name.startswith('f01-r19-dev-'):
    manifest_path=profiler.parent.parent/kernel.parent.name/'manifest.json'
    helper_manifest=json.loads(manifest_path.read_bytes())
    if helper_manifest.get('helper_audit_module_sha256'):
        helper_name=helper_manifest.get('helper_audit_module','development-helper-audit.py')
        assert helper_name in ('development-helper-audit.py', 'development-helper-audit-v4.py', 'development-helper-audit-v5.py', 'development-helper-audit-v7.py', 'development-helper-audit-v8.py', 'development-resource-audit.py', 'development-resource-audit-v2.py', 'development-route-audit.py', 'development-route-audit-v2.py', 'development-math-outlet-audit.py', 'development-runtime-cost-audit.py', 'development-add-cost-audit.py')
        helper_path=profiler.parent.parent/'f01-d7-research/round9h-20261026T194639Z'/helper_name
        assert hashlib.sha256(helper_path.read_bytes()).hexdigest()==helper_manifest['helper_audit_module_sha256']
        hs=importlib.util.spec_from_file_location('r19_explicit_math_helper_audit',helper_path)
        hm=importlib.util.module_from_spec(hs);hs.loader.exec_module(hm)
        g.STAGES += hm.stages(g,kernel,out,helper_manifest)
with (g.HERE/'gate.lock').open('w') as lock:
    fcntl.flock(lock,fcntl.LOCK_EX)
    g.check_limits()
    digest=g.pin(g.SLOTS['full'])
    verdict=g.gate(kernel.parent,digest,'gate','full')
result=asdict(verdict);result['mode']='diagnostic-statement-only';result['diagnostic_only']=True
(out/'diagnostic-only-verdict.json').write_text(json.dumps(result,indent=2)+'\n',encoding='utf-8')
sys.exit(0 if verdict.passed else 1)
'''
        start=time.monotonic()
        with (out/'replay.log').open('wb') as stream:
            try:
                profiler=Path(__file__).resolve().parent.parent/'f01-d5-costsplit/profile-native.py'
                p=subprocess.Popen([str(a.upstream/'.venv/bin/python'),'-c',code,str(a.upstream),str(a.kernel),str(out),str(profiler)],cwd=a.upstream,env=os.environ.copy(),stdout=stream,stderr=subprocess.STDOUT,start_new_session=True)
                replay_timeout=1800 if a.name=='f01-d13-cost-profile' else 2400 if a.name in ('f01-d6-public-suite','f01-d7-public-suite') else 580 if a.name in ('f01-r19-dev-runtime-cost1', 'f01-r19-dev-add-cost1', 'f01-r22-dev-runtime-cost1', 'f01-r22-dev-runtime-cost2', 'f01-r22-dev-runtime-cost3', 'f01-r22-dev-flat-scale-cost1', 'f01-r22-dev-flat-scale-cost2', 'f01-r22-dev-pair8-cost1', 'f01-r22-dev-resident8-cost1', 'f01-r22-dev-broadword-cost1', 'f01-r22-dev-multistatic-cost1', 'f01-r22-dev-farstatic-cost1', 'f01-r22-dev-nativecold-cost1', 'f01-r22-dev-indexed8-cost1', 'f01-r22-dev-outline-isolation1', 'f01-r22-dev-wordcarry-cost1', 'f01-r22-dev-nat-prefix1', 'f01-r22-dev-nat-bias-repair1', 'f01-r22-dev-endpoint-cost1', 'f01-r22-dev-nat-light-repair1') else 240 if a.name.startswith('f01-r22-') else 170 if a.name=='f01-r19-dev-math-outlet-isolation1' else 120
                report['replay_exit_code']=p.wait(timeout=replay_timeout)
            except subprocess.TimeoutExpired:
                os.killpg(p.pid,signal.SIGKILL);p.wait();report['replay']=f'diagnostic-only replay process group timed out at {replay_timeout}s'
        report['replay_seconds']=round(time.monotonic()-start,3)
    candidate_c=out/'candidate-c-index.json'
    report['generated_c']=json.loads(candidate_c.read_bytes()) if candidate_c.exists() else []
    report['generated_c_scope']='Only successful candidate statement-layer C; never the cached shipped baseline outside that layer.'
    (out/'index.json').write_text(json.dumps(report,indent=2)+'\n',encoding='utf-8')
    if a.compile_only:
        p=out/'diagnostic-only-verdict.json'
        result=json.loads(p.read_bytes()) if p.exists() else {'passed':False,'stage':'diagnostic-timeout'}
        result['mode']='diagnostic-statement-only';result['diagnostic_only']=True
        a.verdict.write_text(json.dumps(result,indent=2)+'\n',encoding='utf-8')
        return 0 if result.get('passed') else 1
    return 0

if __name__=='__main__':raise SystemExit(main())
