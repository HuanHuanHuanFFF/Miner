"""Diagnostic-only balanced ordering in a scratch engine; official tree untouched."""
from pathlib import Path
import dataclasses, hashlib, importlib.util, json, os, shutil, statistics, subprocess, sys
from round4 import ROOT, validate

ORDER_LOOP='''for lane in 0..methods.len() {
            let pattern = [0usize, 1, 4, 2, 3];
            let cycle = round.saturating_sub(warmup) % 10;
            let pos = if round < warmup { lane } else {
                let step = if cycle < 5 { lane } else { 4 - lane };
                (pattern[step] + cycle % 5) % 5
            };
            let m = &methods[pos];'''

def preflight():
    from collections import Counter
    base=[0,1,4,2,3]
    rows=[[(base[i if k<5 else 4-i]+k%5)%5 for i in range(5)]for k in range(10)]
    assert all(sorted(r)==list(range(5)) for r in rows)
    edges=Counter((a,b)for r in rows for a,b in zip(r,r[1:]));assert len(edges)==20 and set(edges.values())=={2}
    return rows

def main():
    orders=preflight();assert os.environ.get('GITHUB_ACTIONS')=='true' and os.environ.get('RUNNER_OS')=='Linux'
    spec=validate(os.environ['ROUND4_SPEC']);assert spec['r18_order_diagnostic']
    up=Path(os.environ['DEFLATE_ROOT']);sys.path.insert(0,str(up/'validator'))
    from bench import driver,corpora
    from bench.results import INCUMBENT
    from sandbox import bwrap
    names=spec['diagnostic_methods'];by={e['name']:e for e in spec['entries']};paths={n:ROOT/by[n]['path']/'parse.rs'for n in names}
    config=dataclasses.replace(driver.Config.from_env(up/'validator'),reps=11,warmup=1,cpus=str(min(os.sched_getaffinity(0))),keep=driver.Keep.NEVER,bars=False)
    driver.check(config);corpus=corpora.load(up/'validator').by_name('corpus-stage1')
    ws=driver._make_workspace(config,paths);crates=driver._generate(config,ws,paths);driver._build(config,ws,crates);rustc=driver._rustc_version(config,ws,crates[INCUMBENT])
    out=Path(os.environ['RUNNER_TEMP'])/'round4-receipts/r18-order';out.mkdir(parents=True,exist_ok=True)
    scratch=Path(os.environ['RUNNER_TEMP'])/'r18-balanced-engine';scratch.mkdir()
    original=up/'validator/measure';shutil.copytree(original/'src',scratch/'src')
    for f in ('Cargo.toml','Cargo.lock'):shutil.copyfile(original/f,scratch/f)
    mainfile=scratch/'src/main.rs';text=mainfile.read_text();assert text.count('for m in methods {')==1;mainfile.write_text(text.replace('for m in methods {',ORDER_LOOP))
    source_hashes={str(p.relative_to(scratch)):hashlib.sha256(p.read_bytes()).hexdigest() for p in scratch.rglob('*')if p.is_file()}
    for p in (scratch/'src').glob('*.rs'):
        if p.name!='main.rs':assert p.read_bytes()==(original/'src'/p.name).read_bytes()
    c=subprocess.run(['cargo','+nightly-2026-08-18','build','--release','--locked'],cwd=scratch,capture_output=True,text=True,timeout=360)
    (out/'compile.log').write_text(c.stdout+c.stderr);assert c.returncode==0
    binary=scratch/'target/release/measure';assert binary.is_file()
    sp=importlib.util.spec_from_file_location('noise_wrapper',ROOT/'scripts/research-round18-multimethod.py');m=importlib.util.module_from_spec(sp);sp.loader.exec_module(m)
    wrapper=ws/'context.py';wrapper.write_text(m.WRAPPER)
    report={'run_id':os.environ['GITHUB_RUN_ID'],'git_sha':os.environ['GITHUB_SHA'],'batch':os.environ['ROUND4_SPEC'],'status':'STARTED','source_hashes':source_hashes,'original_engine_sha256':hashlib.sha256(config.engine.read_bytes()).hexdigest(),'balanced_engine_sha256':hashlib.sha256(binary.read_bytes()).hexdigest(),'orders':orders,'blocks':[],
            'scope':'Diagnostic only: original fixed11, original fixed20, scratch balanced20 schedules at explicitCPU0. Sharedoriginalencoder/token/loader unchanged. Not original protocol performance, Lean gate or payout.'}
    def save(): (out/'order.json').write_text(json.dumps(report,indent=2)+'\n')
    save();identities={}
    for block in range(1,5):
        method_order=[INCUMBENT]+(names if block%2 else names[::-1])
        modes=[('original_fixed11',config.engine,11),('original_fixed20',config.engine,20),('balanced20',binary,20)]
        if block%2==0:modes.reverse()
        for label,engine,reps in modes:
            cmd=[str(engine),str(corpus.path)]+[f'{n}={crates[n]}'for n in method_order]+['--corpus-name',corpus.name,'--reps',str(reps),'--warmup','1','--rustc-version',rustc,'--no-bars']
            proc=bwrap.run(driver.measure_sandbox(config,ws,corpus),['/usr/bin/python3',str(wrapper),config.cpus]+cmd,cwd=None,timeout=config.timeout)
            stem=f'{label}-block{block}';(out/(stem+'.jsonl')).write_text(proc.stdout);(out/(stem+'.stderr.log')).write_text(proc.stderr);assert proc.returncode==0
            contexts=[json.loads(s.split(' ',1)[1])for s in proc.stderr.splitlines()if s.startswith('R18_ENGINE_PROCESS_CONTEXT ')];assert len(contexts)==1 and contexts[0]['affinity_before_exec']==[int(config.cpus)]
            (out/(stem+'-process.json')).write_text(json.dumps(contexts[0],indent=2)+'\n')
            raw=[json.loads(s)for s in proc.stdout.splitlines()];meta=raw[0];fs=[r for r in raw if r['kind']=='file'];assert len(fs)==28
            assert meta['measured_rounds']==reps and meta['warmup_rounds']==1
            assert all(meta['methods'][n]['source_sha256']==by[n]['hashes']['parse.rs']for n in names)
            axes={n:[]for n in method_order};observed_orders=None
            for f in fs:
                med={}
                for n in method_order:
                    mm=f['methods'][n];assert not mm['errors'] and mm['deterministic'];vv=[v for v in mm['reps']if v['phase']=='measured'];assert len(vv)==reps
                    med[n]=statistics.median(v['total_s']for v in vv);key=(meta['methods'][n]['source_sha256'],f['file']);ident=(f['sha256'],mm['tokens_sha256'],mm['output_sha256']);assert identities.setdefault(key,ident)==ident
                for n in method_order:axes[n].append(med[n]/med[INCUMBENT])
                if observed_orders is None:
                    observed_orders=[]
                    for j in range(reps):
                        observed_orders.append(sorted(method_order,key=lambda n:[v for v in f['methods'][n]['reps']if v['phase']=='measured'][j]['order_index']))
            expected=[[method_order[i]for i in orders[j%10]]for j in range(reps)] if label=='balanced20' else [method_order]*reps
            assert observed_orders==expected
            for a,b in ((names[0],names[1]),(names[2],names[3])):assert meta['methods'][a]['lib_sha256']==meta['methods'][b]['lib_sha256']
            row={'protocol':label,'block':block,'method_load_order':method_order,'observed_orders_first_file':observed_orders,'reps':reps,'axes':{n:statistics.mean(v)for n,v in axes.items()},'raw_file':stem+'.jsonl','raw_sha256':hashlib.sha256((out/(stem+'.jsonl')).read_bytes()).hexdigest()}
            report['blocks'].append(row);save();print('R18_ORDER',json.dumps(row),flush=True)
    subprocess.run(['git','diff','--exit-code'],cwd=up,check=True)
    report['status']='COMPLETE_DIAGNOSTIC_ORDER_COMPARISON';save()

if __name__=='__main__':main()
