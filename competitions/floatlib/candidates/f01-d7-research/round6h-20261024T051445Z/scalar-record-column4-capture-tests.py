"""New Column4 selector receipt; retain all535/c124 receipts unchanged."""
from pathlib import Path
from datetime import datetime,timezone
import hashlib,json,subprocess,sys,time

HERE=Path(__file__).resolve().parent
sha=lambda raw:hashlib.sha256(raw).hexdigest()


def main():
    scripts=('scalar-test-observer.py','scalar-test-bmm-focus.py','scalar-test-bmm-core-focus.py','scalar-test-column4-focus.py')
    sources=('capture-mainfull.py','scalar-capture-legacy-fd17.py',*scripts,
        'astra-column4-assets.lean','astra-column4-writer.lean','astra-column4-capture-needs.json')
    before={n:sha((HERE/n).read_bytes())for n in sources}
    assert before['capture-mainfull.py']=='76ef3176ca1c91026d3c0d9109e40944b541d11aa9e6caa5873cf3ff82ee98cf'
    record={'recorded_at_utc':datetime.now(timezone.utc).isoformat(),'source_sha256':before,'tests':[],
        'Column4_actual_emission':'UNKNOWN_NOT_YET_OBSERVED','Column4_fixture':'SYNTHETIC_NOT_MACHINE_EVIDENCE',
        'actual_Lean_ELF_gate':'NOT_RUN','scope':'Keep scalar/default and real saved old-family symbol coverage; synthetic newColumn4 owner boundaries and same-object control-slot reservation only.'}
    count=0
    for script in scripts:
        start=time.monotonic();p=subprocess.run([sys.executable,str(HERE/script)],cwd=HERE,capture_output=True,timeout=30)
        prefix=script.removesuffix('.py')+'-76ef31';out,err=prefix+'.stdout.txt',prefix+'.stderr.txt'
        (HERE/out).write_bytes(p.stdout);(HERE/err).write_bytes(p.stderr)
        parsed=json.loads(p.stdout);count+=len(parsed['tests'])
        record['tests'].append({'script':script,'exit_code':p.returncode,'seconds':round(time.monotonic()-start,6),'argv':p.args,
            'stdout':{'path':out,'sha256':sha(p.stdout),'bytes':len(p.stdout)},'stderr':{'path':err,'sha256':sha(p.stderr),'bytes':len(p.stderr)},'result':parsed})
    after={n:sha((HERE/n).read_bytes())for n in sources};assert before==after
    record.update(source_sha256_after=after,all_sources_unchanged=True,total_cases=count,
        state='PASS'if count==11 and all(t['exit_code']==0 and t['result']['state']=='PASS'for t in record['tests'])else'FAIL')
    (HERE/'scalar-column4-capture-tests.json').write_text(json.dumps(record,ensure_ascii=False,indent=2)+'\n',encoding='utf-8',newline='\n')
    print(json.dumps({'state':record['state'],'total_cases':count,'exit_codes':[t['exit_code']for t in record['tests']],
        'helper_sha256':before['capture-mainfull.py'],'sources_unchanged':True,'Column4_machine_evidence':'NOT_RUN'},indent=2))
    return 0 if record['state']=='PASS'else 1


if __name__=='__main__':raise SystemExit(main())
