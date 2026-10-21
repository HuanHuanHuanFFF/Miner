"""Run the exact pinned official full gate and retain original paired evidence."""
from pathlib import Path
import datetime, hashlib, importlib.util, json, os, re, shutil, subprocess, sys, time

ROOT=Path(os.environ['GITHUB_WORKSPACE']).resolve()
UPSTREAM=Path(os.environ['FLOATLIB_ROOT']).resolve()
REPORTS=Path(os.environ['FLOATLIB_REPORTS']).resolve()
TRACK=ROOT/'competitions/floatlib'

def save(path,value):
    path.write_text(json.dumps(value,indent=2,ensure_ascii=False,allow_nan=False)+'\n',encoding='utf-8')

def sha(path):
    return hashlib.sha256(path.read_bytes()).hexdigest()

def main():
    pins=json.loads((TRACK/'pins.json').read_text())
    assert subprocess.check_output(['git','rev-parse','HEAD'],cwd=UPSTREAM,text=True).strip()==pins['official_commit']
    supplied=os.environ.get('FLOATLIB_CANDIDATES','baseline')
    assert re.fullmatch(r'(?:baseline|f01-[a-z0-9-]+)(?:,(?:baseline|f01-[a-z0-9-]+))*',supplied),supplied
    names=list(dict.fromkeys(['baseline',*supplied.split(',')]))
    assert 1<=len(names)<=5
    seed=os.environ.get('FLOATLIB_SEED','42');assert seed.isdecimal() and 0<=int(seed)<2**32
    env=os.environ.copy();env['BENCH_SEED']=seed
    official_kernel=UPSTREAM/'kernels/full/incumbent/Kernel.lean'
    save(REPORTS/'plan.json',{'candidates':names,'seed':int(seed),'mode':'full official gate','rounds':25,'reference_sha256':sha(official_kernel),'scope':'Public shipped-reference comparison; no current-champion, official admission or reward claim.'})
    spec=importlib.util.spec_from_file_location('floatlib_official_admission',UPSTREAM/'validator/admission.py')
    admission=importlib.util.module_from_spec(spec);sys.modules[spec.name]=admission;spec.loader.exec_module(admission)
    rows=[]
    for name in names:
        source=official_kernel if name=='baseline' else TRACK/'candidates'/name/'Kernel.lean'
        assert source.is_file() and 0<source.stat().st_size<=pins['max_kernel_bytes']
        if name!='baseline':
            manifest=source.parent/'manifest.json'
            if manifest.exists(): shutil.copyfile(manifest,REPORTS/(name+'-manifest.json'))
        candidate=REPORTS/'inputs'/name;candidate.mkdir(parents=True,exist_ok=False)
        shutil.copyfile(source,candidate/'Kernel.lean')
        digest=sha(source);verdict=REPORTS/(name+'-verdict.json');log=REPORTS/(name+'-gate.log')
        command=[str(UPSTREAM/'.venv/bin/python'),'gate.py','--slot','full',str(candidate),'--verdict',str(verdict)]
        started=time.monotonic()
        with log.open('wb') as stream:
            process=subprocess.Popen(command,cwd=UPSTREAM,env=env,stdout=subprocess.PIPE,stderr=subprocess.STDOUT)
            for line in process.stdout:
                stream.write(line);stream.flush();sys.stdout.buffer.write(line);sys.stdout.flush()
            code=process.wait()
        # Preserve the authoritative gate; debugging artifacts have their own label.
        diagnostic=TRACK/'candidates/f01-word-tensors/ci-diagnostics.py'
        if name!='baseline' and diagnostic.is_file():
            try:
                subprocess.run([sys.executable,str(diagnostic),'--upstream',str(UPSTREAM),'--kernel',str(candidate/'Kernel.lean'),'--reports',str(REPORTS),'--name',name,'--verdict',str(verdict)],check=False,timeout=150)
            except subprocess.TimeoutExpired:
                save(REPORTS/(name+'-diagnostic-timeout.json'),{'diagnostic_only':True,'timeout_seconds':150,'original_verdict_unchanged':True})
        original=json.loads(verdict.read_bytes()) if verdict.exists() else None
        row={'candidate':name,'kernel_sha256':digest,'reference_sha256':sha(official_kernel),'exit_code':code,'wall_seconds':round(time.monotonic()-started,3),'full_gate':bool(code==0 and original and original.get('passed') and original.get('mode')=='gate' and original.get('stage')=='score'),'verdict':verdict.name,'seed':int(seed),'formal_online_result':'UNKNOWN'}
        if row['full_gate']:
            assert original['verifier_fingerprint']==original['verifier_fingerprint_end']
            assert len(original['classes'])==12 and len(original['rounds'])==25
            ratio=sum(c['submission_ns'] for c in original['classes'].values())/sum(c['incumbent_ns'] for c in original['classes'].values())
            assert abs(ratio-original['ratio'])<1e-10
            evidence=admission.Evidence(1,'public-runner',ratio,datetime.datetime(2026,10,21,tzinfo=datetime.timezone.utc),tuple(tuple(r) for r in original['rounds']))
            decision=admission.assess(evidence,.97)
            row.update(ratio=ratio,paired_gain_p05=decision.gain_p05,public_statistical_check=decision.outcome,classes=original['classes'],paired_rounds=original['rounds'])
        assert sha(source)==digest,'Candidate changed while validating'
        rows.append(row);save(REPORTS/'summary.json',{'run_id':os.environ['GITHUB_RUN_ID'],'source_commit':os.environ['GITHUB_SHA'],'official_commit':pins['official_commit'],'results':rows,'complete':len(rows)==len(names),'scope':'Full public official gate and paired performance; runner-specific, not formal online admission.'})
    for folder,pattern in [('logs','*.log'),('results','*.json')]:
        out=REPORTS/'official'/folder;out.mkdir(parents=True,exist_ok=True)
        for p in (UPSTREAM/folder).glob(pattern):shutil.copyfile(p,out/p.name)
    subprocess.run(['git','diff','--exit-code'],cwd=UPSTREAM,check=True)
    with Path(os.environ['GITHUB_STEP_SUMMARY']).open('a') as out:
        out.write('| Candidate | Full gate | Ratio vs shipped | Paired p05 gain | Public statistical check |\n|---|---|---:|---:|---|\n')
        for row in rows:out.write(f"| {row['candidate']} | {row['full_gate']} | {row.get('ratio','UNKNOWN')} | {row.get('paired_gain_p05','UNKNOWN')} | {row.get('public_statistical_check','UNKNOWN')} |\n")
        out.write('\nExact original verdicts and logs are in the artifact. No official competition submission was made.\n')
    return 0 if all(r['full_gate'] for r in rows) else 1

if __name__=='__main__':raise SystemExit(main())
