"""DRAFT Linux diagnostic build entry. No official gate source file is changed."""
from pathlib import Path
from dataclasses import asdict
import argparse,fcntl,hashlib,importlib.util,json,os,sys

def main():
    ap=argparse.ArgumentParser(description=__doc__)
    for name in ('upstream','kernel','out'):ap.add_argument('--'+name,type=Path,required=True)
    a=ap.parse_args();here=Path(__file__).resolve().parent
    request=json.loads((here/'request.json').read_text())
    assert hashlib.sha256(a.kernel.read_bytes()).hexdigest()==request['kernel_sha256']
    os.environ.update(BENCH_SEED='1927003',BENCH_PAIRS='500000',GATE_FULL_SUITE=str(a.upstream/'suites/public-v2.json'))
    sys.path.insert(0,str(a.upstream))
    spec=importlib.util.spec_from_file_location('r19_original_build_interface',a.upstream/'gate.py')
    g=importlib.util.module_from_spec(spec);sys.modules[spec.name]=g;spec.loader.exec_module(g)
    ps=importlib.util.spec_from_file_location('r19_route_driver',here/'route-profile-driver.py')
    driver=importlib.util.module_from_spec(ps);ps.loader.exec_module(driver)
    plan=json.loads((here/request['plans'][0]['path']).read_text());original_statement=g.statement
    def statement_then_collect(src,verdict):
        reason=original_statement(src,verdict)
        if reason:return reason
        driver.run(g,a.kernel,a.out/'measurement',plan,1927003)
        return None
    # A separate build-only diagnostic process; production gate/STAGES/files stay untouched.
    # No result from this three-stage table is reported as a full gate or an official score.
    g.STAGES=[('intake',g.intake),('policy',g.policy),('statement',statement_then_collect)]
    a.out.mkdir(parents=True,exist_ok=False)
    with(g.HERE/'gate.lock').open('w')as lock:
        fcntl.flock(lock,fcntl.LOCK_EX);g.check_limits();digest=g.pin(g.SLOTS['full'])
        v=g.gate(a.kernel.parent,digest,'gate','full')
    result=dict(original_build_diagnostic=asdict(v),diagnostic_only=True,full_gate=False,performance_acceptance=False,
                request_sha256=hashlib.sha256((here/'request.json').read_bytes()).hexdigest(),
                driver_sha256=hashlib.sha256((here/'route-profile-driver.py').read_bytes()).hexdigest())
    (a.out/'diagnostic-build-result.json').write_text(json.dumps(result,indent=2)+'\n')
    return 0 if v.passed else 1

if __name__=='__main__':raise SystemExit(main())
