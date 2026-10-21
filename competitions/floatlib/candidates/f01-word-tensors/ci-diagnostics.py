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
import importlib.util,sys,json,hashlib,fcntl
from dataclasses import asdict
from pathlib import Path
upstream,kernel,out=map(Path,sys.argv[1:]);sys.path.insert(0,str(upstream))
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
    return reason
g.STAGES=[('intake',g.intake),('policy',g.policy),('statement',statement)]
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
                p=subprocess.Popen([str(a.upstream/'.venv/bin/python'),'-c',code,str(a.upstream),str(a.kernel),str(out)],cwd=a.upstream,env=os.environ.copy(),stdout=stream,stderr=subprocess.STDOUT,start_new_session=True)
                report['replay_exit_code']=p.wait(timeout=120)
            except subprocess.TimeoutExpired:
                os.killpg(p.pid,signal.SIGKILL);p.wait();report['replay']='diagnostic-only replay process group timed out at 120s'
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
