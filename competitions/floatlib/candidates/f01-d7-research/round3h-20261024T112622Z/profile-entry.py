"""R13 independent diagnostic statement replay, exactDF only; never a full gate."""
from pathlib import Path
from dataclasses import asdict
import argparse,fcntl,hashlib,importlib.util,json,os,subprocess,sys,traceback


def main():
    ap=argparse.ArgumentParser(description=__doc__)
    for name in ('upstream','kernel','out','plan'):ap.add_argument('--'+name,required=True,type=Path)
    a=ap.parse_args();a.out.mkdir(parents=True,exist_ok=True)
    assert hashlib.sha256(a.kernel.read_bytes()).hexdigest()=='df5c61a0ca24a8ef18c0c42d83bdd23466872d3fe8f39dd912e9c347b27fb172'
    assert subprocess.check_output(['git','rev-parse','HEAD'],cwd=a.upstream,text=True).strip()=='4b7e83841cc0c32c6529f533923c73d33b5ecf97'
    sys.path.insert(0,str(a.upstream))
    spec=importlib.util.spec_from_file_location('r13_profile_original_gate',a.upstream/'gate.py')
    g=importlib.util.module_from_spec(spec);sys.modules[spec.name]=g;spec.loader.exec_module(g)
    pp=Path(__file__).with_name('profile-current.py');ps=importlib.util.spec_from_file_location('r13_exact_df_profile',pp)
    profile=importlib.util.module_from_spec(ps);sys.modules[ps.name]=profile;ps.loader.exec_module(profile)
    plan=json.loads(a.plan.read_bytes());original=g.statement
    def statement(src,verdict):
        reason=original(src,verdict)
        if reason:return reason
        profile.run(g,a.kernel,a.out,plan,int(os.environ['BENCH_SEED']))
        return None
    g.STAGES=[('intake',g.intake),('policy',g.policy),('statement',statement)]
    with(g.HERE/'gate.lock').open('w')as lock:
        fcntl.flock(lock,fcntl.LOCK_EX);g.check_limits();digest=g.pin(g.SLOTS['full'])
        verdict=g.gate(a.kernel.parent,digest,'gate','full')
    result={**asdict(verdict),'mode':'diagnostic-statement-profile','diagnostic_only':True,'full_gate':False,
        'profile_module_sha256':hashlib.sha256(pp.read_bytes()).hexdigest(),'drawn_plan_file_sha256':hashlib.sha256(a.plan.read_bytes()).hexdigest()}
    (a.out/'diagnostic-only-verdict.json').write_text(json.dumps(result,indent=2)+'\n',encoding='utf-8',newline='\n')
    return 0 if verdict.passed else 1


if __name__=='__main__':raise SystemExit(main())
