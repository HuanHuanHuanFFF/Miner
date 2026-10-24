"""New-version receipt; preserve the original535 test logs/receipt untouched."""
from pathlib import Path
from datetime import datetime,timezone
import hashlib,json,subprocess,sys,time

HERE=Path(__file__).resolve().parent
sha=lambda raw:hashlib.sha256(raw).hexdigest()


def main():
    scripts=('scalar-test-observer.py','scalar-test-bmm-focus.py','scalar-test-bmm-core-focus.py')
    sources=('capture-mainfull.py','scalar-capture-legacy-fd17.py',*scripts)
    before={n:sha((HERE/n).read_bytes()) for n in sources}
    assert before['capture-mainfull.py']=='c1246c442c1f0f6ef24cfc48d9d68f0e8a1acf52000a7827d99de3fdc4c52f5e'
    record={'recorded_at_utc':datetime.now(timezone.utc).isoformat(),'source_sha256':before,'tests':[],
        'actual_Lean_ELF_gate':'NOT_RUN','scope':'Original5 fake-child checks, prior3 focus checks and actual1224003 C/nm core/producer selection fixture. Fake tools only; not a linked or measured run.'}
    count=0
    for script in scripts:
        start=time.monotonic();p=subprocess.run([sys.executable,str(HERE/script)],cwd=HERE,capture_output=True,timeout=30)
        prefix=script.removesuffix('.py')+'-c1246c'
        stdout,stderr=prefix+'.stdout.txt',prefix+'.stderr.txt'
        (HERE/stdout).write_bytes(p.stdout);(HERE/stderr).write_bytes(p.stderr)
        parsed=json.loads(p.stdout);count+=len(parsed['tests'])
        record['tests'].append({'script':script,'exit_code':p.returncode,'seconds':round(time.monotonic()-start,6),
            'argv':p.args,'stdout':{'path':stdout,'sha256':sha(p.stdout),'bytes':len(p.stdout)},
            'stderr':{'path':stderr,'sha256':sha(p.stderr),'bytes':len(p.stderr)},'result':parsed})
    after={n:sha((HERE/n).read_bytes()) for n in sources};assert before==after
    record.update(source_sha256_after=after,all_sources_unchanged=True,total_cases=count,
        state='PASS' if count==9 and all(t['exit_code']==0 and t['result']['state']=='PASS' for t in record['tests']) else 'FAIL')
    (HERE/'scalar-bmm-core-capture-tests.json').write_text(json.dumps(record,ensure_ascii=False,indent=2)+'\n',encoding='utf-8',newline='\n')
    print(json.dumps({'state':record['state'],'total_cases':count,'exit_codes':[t['exit_code'] for t in record['tests']],
        'helper_sha256':before['capture-mainfull.py'],'sources_unchanged':True},indent=2))
    return 0 if record['state']=='PASS' else 1


if __name__=='__main__':
    raise SystemExit(main())
