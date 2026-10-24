"""Separate current-source cost diagnostic; never an official scored result."""
from pathlib import Path
import hashlib,json,os,subprocess,time,importlib.util
HEAD='4b7e83841cc0c32c6529f533923c73d33b5ecf97'
SOURCE='df5c61a0ca24a8ef18c0c42d83bdd23466872d3fe8f39dd912e9c347b27fb172'
def run(g,kernel,out):
    deadline=time.monotonic()+1500
    repo=Path(os.environ['GITHUB_WORKSPACE']); folder=out/'cost-profile';folder.mkdir(exist_ok=False)
    request_path=repo/'competitions/floatlib/candidates/f01-d13-cost-profile/profile-request.json'
    request=json.loads(request_path.read_bytes());assert int(os.environ['FLOATLIB_SEED'])==request['dispatch_seed']
    assert request['source_sha256']==SOURCE and request['official_commit']==HEAD
    old=Path(os.environ['FLOATLIB_ROOT']);up=Path(os.environ['RUNNER_TEMP'])/'floatlib-r13-cost-profile-upstream'
    env=os.environ.copy();env['PATH']=str(Path.home()/'.elan/bin')+os.pathsep+env['PATH']
    def command(args,name,cwd,timeout):
        remaining=deadline-time.monotonic()
        if remaining<=0:raise TimeoutError('R13 diagnostic adapter total1500s budget exhausted')
        with (folder/name).open('wb')as stream:p=subprocess.run(args,cwd=cwd,env=env,stdout=stream,stderr=subprocess.STDOUT,timeout=min(timeout,remaining))
        if p.returncode:raise RuntimeError(name+': exit'+str(p.returncode))
    command(['git','fetch','--depth','1','origin',HEAD],'fetch.log',old,90)
    command(['git','worktree','add','--detach',str(up),HEAD],'checkout.log',old,30)
    command(['cp','-al',str(old/'lean/.lake'),str(up/'lean/.lake')],'copy-dependencies.log',old,180)
    assert subprocess.check_output(['git','rev-parse','HEAD'],cwd=up,text=True).strip()==HEAD
    for name in ['lean-toolchain','lake-manifest.json']:assert (old/'lean'/name).read_bytes()==(up/'lean'/name).read_bytes()
    hashes=lambda d:{p.relative_to(d).as_posix():hashlib.sha256(p.read_bytes()).hexdigest()for p in d.rglob('*.lean')}
    assert hashes(old/'lean/contract')==hashes(up/'lean/contract')
    command(['bash','./setup.sh'],'setup.log',up,360);command(['bash','./setup.sh','--check'],'setup-check.log',up,60)
    src=repo/'competitions/floatlib/candidates/f01-d12-scalar-combined/Kernel.lean';raw=src.read_bytes();assert hashlib.sha256(raw).hexdigest()==SOURCE
    dst=folder/'inputs/f01-d12-scalar-combined';dst.mkdir(parents=True);(dst/'Kernel.lean').write_bytes(raw)
    spec=importlib.util.spec_from_file_location('original_r13_plan_generator',up/'benchmark_suite.py');mod=importlib.util.module_from_spec(spec);spec.loader.exec_module(mod)
    drawn=mod.make_plan(mod.load(up/'suites/public-v2.json'),request['profile_seed'],500000)
    plan=folder/'public-drawn-plan.json';plan.write_bytes((json.dumps(drawn,indent=2)+'\n').encode())
    (folder/'requested-plan.json').write_bytes(request_path.read_bytes())
    (folder/'public-v2.json').write_bytes((up/'suites/public-v2.json').read_bytes())
    env.update(BENCH_SEED=str(request['profile_seed']),BENCH_ROUNDS='25',BENCH_PAIRS='500000',GATE_BUDGET_SECONDS='900',VERIFY_TOTAL_TIMEOUT='1800',GATE_FULL_SUITE=str(up/'suites/public-v2.json'))
    entry=Path(__file__).with_name('profile-entry.py')
    started=time.monotonic()
    command([str(up/'.venv/bin/python'),str(entry),'--upstream',str(up),'--kernel',str(dst/'Kernel.lean'),'--out',str(folder/'measurement'),'--plan',str(plan)],'profile.log',up,1000)
    command(['git','diff','--exit-code'],'official-source-clean.log',up,30)
    result={'source_commit':os.environ['GITHUB_SHA'],'official_commit':HEAD,'diagnostic_only':True,'full_gate':False,'source_sha256':SOURCE,'profile_seed':request['profile_seed'],'dispatch_seed':request['dispatch_seed'],'elapsed_seconds':time.monotonic()-started,'adapter_sha256':hashlib.sha256(Path(__file__).read_bytes()).hexdigest(),'entry_sha256':hashlib.sha256(entry.read_bytes()).hexdigest(),'requested_plan_sha256':hashlib.sha256(request_path.read_bytes()).hexdigest(),'drawn_plan_sha256':hashlib.sha256(plan.read_bytes()).hexdigest(),'timeout_seconds':{'adapter_total':1500,'entry':1000,'outer_replay':1800,'job':2700},'scope':'Separate diagnostic execution; observer/instrumented stages and uninstrumented full-call measurements stay separate. No admission or kernel performance adoption.'}
    (folder/'summary.json').write_bytes((json.dumps(result,indent=2)+'\n').encode())
