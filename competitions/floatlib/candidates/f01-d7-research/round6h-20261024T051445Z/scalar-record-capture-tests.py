"""Persist exact lightweight capture-test stdout, exit codes and source binding."""
from pathlib import Path
from datetime import datetime, timezone
import hashlib
import json
import subprocess
import sys
import time

HERE=Path(__file__).resolve().parent


def sha(raw):
    return hashlib.sha256(raw).hexdigest()


def main():
    sources=('capture-mainfull.py','scalar-capture-legacy-fd17.py','scalar-test-observer.py','scalar-test-bmm-focus.py')
    before={name:sha((HERE/name).read_bytes()) for name in sources}
    assert before['capture-mainfull.py']=='53525f8e5ac09300d01b57e37ff652eecdaa4ec3b6dc3d09c11f01dc4c924695'
    record={'recorded_at_utc':datetime.now(timezone.utc).isoformat(),'mode':'LIGHTWEIGHT_FAKE_CHILD_AND_SAVED_SYMBOL_FIXTURES',
        'source_sha256':before,'python_executable':sys.executable,'python_version':sys.version,'tests':[],
        'actual_Lean_ELF_gate':'NOT_RUN','scope':'Fresh bounded replay only to persist exact per-process exit codes and raw stdout/stderr; no Lean, benchmark, CI or compiler run.'}
    total=0
    for name in ('scalar-test-observer.py','scalar-test-bmm-focus.py'):
        start=time.monotonic()
        completed=subprocess.run([sys.executable,str(HERE/name)],cwd=HERE,capture_output=True,timeout=30)
        prefix=name.removesuffix('.py')
        stdout_name=prefix+'-53525f.stdout.txt';stderr_name=prefix+'-53525f.stderr.txt'
        (HERE/stdout_name).write_bytes(completed.stdout);(HERE/stderr_name).write_bytes(completed.stderr)
        parsed=json.loads(completed.stdout)
        cases=parsed['tests'];total+=len(cases)
        record['tests'].append({'script':name,'script_sha256':before[name],'argv':completed.args,'exit_code':completed.returncode,
            'seconds':round(time.monotonic()-start,6),'stdout':{'path':stdout_name,'sha256':sha(completed.stdout),'bytes':len(completed.stdout)},
            'stderr':{'path':stderr_name,'sha256':sha(completed.stderr),'bytes':len(completed.stderr)},'result':parsed})
    after={name:sha((HERE/name).read_bytes()) for name in sources}
    assert before==after
    record.update(source_sha256_after=after,all_sources_unchanged=True,total_cases=total,
        state='PASS' if total==8 and all(t['exit_code']==0 and t['result']['state']=='PASS' for t in record['tests']) else 'FAIL')
    (HERE/'scalar-bmm-capture-tests.json').write_text(json.dumps(record,ensure_ascii=False,indent=2)+'\n',encoding='utf-8',newline='\n')
    print(json.dumps({'state':record['state'],'total_cases':total,'helper_sha256':before['capture-mainfull.py'],
        'exit_codes':[t['exit_code'] for t in record['tests']],'all_sources_unchanged':True},indent=2))
    return 0 if record['state']=='PASS' else 1


if __name__=='__main__':
    raise SystemExit(main())
