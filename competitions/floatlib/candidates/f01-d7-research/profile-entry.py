"""A separate diagnostic statement replay; never changes an original gate verdict."""
from pathlib import Path
from dataclasses import asdict
import argparse,fcntl,hashlib,importlib.util,json,os,subprocess,sys,traceback

ap=argparse.ArgumentParser()
ap.add_argument('--upstream',type=Path,required=True)
ap.add_argument('--kernel',type=Path,required=True)
ap.add_argument('--out',type=Path,required=True)
ap.add_argument('--plan',type=Path,required=True)
a=ap.parse_args();a.out.mkdir(parents=True,exist_ok=True)
assert hashlib.sha256(a.kernel.read_bytes()).hexdigest()=='8eb63a2fea39f8c483eb16857cb1dcc35ac4a30168ab91046a48aa1cb561e045'
assert subprocess.check_output(['git','rev-parse','HEAD'],cwd=a.upstream,text=True).strip()=='4b7e83841cc0c32c6529f533923c73d33b5ecf97'
sys.path.insert(0,str(a.upstream))
spec=importlib.util.spec_from_file_location('r7_profile_original_gate',a.upstream/'gate.py')
g=importlib.util.module_from_spec(spec);sys.modules[spec.name]=g;spec.loader.exec_module(g)
profile_path=Path(__file__).resolve().with_name('profile-current.py')
ps=importlib.util.spec_from_file_location('r7_current_profile',profile_path)
profile=importlib.util.module_from_spec(ps);sys.modules[ps.name]=profile;ps.loader.exec_module(profile)
drawn=json.loads(a.plan.read_bytes())
original_statement=g.statement
def statement(src,verdict):
    reason=original_statement(src,verdict)
    if reason:return reason
    try:
        profile.run(g,a.kernel,a.out,drawn,int(os.environ['BENCH_SEED']))
    except Exception:
        (a.out/'profile-error.txt').write_text(traceback.format_exc())
        raise
    return None
g.STAGES=[('intake',g.intake),('policy',g.policy),('statement',statement)]
with (g.HERE/'gate.lock').open('w') as lock:
    fcntl.flock(lock,fcntl.LOCK_EX)
    g.check_limits()
    digest=g.pin(g.SLOTS['full'])
    verdict=g.gate(a.kernel.parent,digest,'gate','full')
result={**asdict(verdict),'mode':'diagnostic-statement-profile','diagnostic_only':True,'full_gate':False,'profile_module_sha256':hashlib.sha256(profile_path.read_bytes()).hexdigest(),'drawn_plan_file_sha256':hashlib.sha256(a.plan.read_bytes()).hexdigest()}
(a.out/'diagnostic-only-verdict.json').write_text(json.dumps(result,indent=2)+'\n')
sys.exit(0 if verdict.passed else 1)
