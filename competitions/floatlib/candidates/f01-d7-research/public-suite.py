"""Run the unchanged new official gate on its public suite in a separate checkout."""
from pathlib import Path
import datetime, hashlib, importlib.util, json, os, subprocess, sys, time

HEAD='4b7e83841cc0c32c6529f533923c73d33b5ecf97'

def run(g,kernel,out):
    repo=Path(os.environ['GITHUB_WORKSPACE']); stage=out/'public-suite';stage.mkdir(exist_ok=True)
    upstream=Path(os.environ['RUNNER_TEMP'])/'floatlib-r7-public-suite-upstream'
    env=os.environ.copy();env['PATH']=str(Path.home()/'.elan/bin')+os.pathsep+env['PATH']
    started=time.monotonic()
    def command(args,name,cwd,timeout):
        with (stage/name).open('wb') as log:
            p=subprocess.run(args,cwd=cwd,env=env,stdout=log,stderr=subprocess.STDOUT,timeout=timeout)
        if p.returncode:raise RuntimeError(f'{name}: exit{p.returncode}; exact log retained')
    old=Path(os.environ['FLOATLIB_ROOT'])
    command(['git','fetch','--depth','1','origin',HEAD],'fetch.log',old,90)
    command(['git','worktree','add','--detach',str(upstream),HEAD],'checkout.log',old,30)
    # Reuse only the exact same pinned Lean/FloatLib dependency cache; official source is clean.
    command(['cp','-al',str(old/'lean/.lake'),str(upstream/'lean/.lake')],'copy-dependencies.log',old,180)
    assert subprocess.check_output(['git','rev-parse','HEAD'],cwd=upstream,text=True).strip()==HEAD
    assert (old/'lean/lean-toolchain').read_bytes()==(upstream/'lean/lean-toolchain').read_bytes()
    assert (old/'lean/lake-manifest.json').read_bytes()==(upstream/'lean/lake-manifest.json').read_bytes()
    old_contracts={p.relative_to(old/'lean/contract').as_posix():hashlib.sha256(p.read_bytes()).hexdigest() for p in (old/'lean/contract').rglob('*.lean')}
    new_contracts={p.relative_to(upstream/'lean/contract').as_posix():hashlib.sha256(p.read_bytes()).hexdigest() for p in (upstream/'lean/contract').rglob('*.lean')}
    assert old_contracts==new_contracts,'Contract changed; stop before claiming compatibility'
    command(['bash','./setup.sh'],'setup.log',upstream,360)
    command(['bash','./setup.sh','--check'],'setup-check.log',upstream,60)
    requested=(repo/'competitions/floatlib/candidates/f01-d7-public-suite/suite-plan.json').read_bytes()
    (stage/'requested-plan.json').write_bytes(requested)
    plan=json.loads(requested)
    assert plan['official_commit']==HEAD and plan['suite']=='suites/public-v2.json'
    assert int(os.environ['FLOATLIB_SEED'])==plan['seed']
    env.update(GATE_FULL_SUITE=str(upstream/'suites/public-v2.json'),BENCH_SEED=str(plan['seed']),BENCH_ROUNDS='25',BENCH_PAIRS='500000',GATE_BUDGET_SECONDS='900',VERIFY_TOTAL_TIMEOUT='2700')
    suite=(upstream/'suites/public-v2.json').read_bytes()
    module_spec=importlib.util.spec_from_file_location('official_public_suite_plan',upstream/'benchmark_suite.py')
    module=importlib.util.module_from_spec(module_spec);module_spec.loader.exec_module(module)
    spec=module.load(upstream/'suites/public-v2.json')
    public_plan=module.make_plan(spec,plan['seed'],500000)
    (stage/'public-drawn-plan.json').write_text(json.dumps(public_plan,indent=2)+'\n')
    cell_work={cell:sum(c['work'] for c in public_plan['cases'] if c['timed'] and c['name'].rsplit(':',1)[0]==cell) for cell in module.cells(spec)}
    assert all(w>0 for w in cell_work.values())
    (stage/'public-cell-work.json').write_text(json.dumps(cell_work,indent=2)+'\n')
    provenance={'diagnostic_current_official_public_suite':True,'official_commit':HEAD,'source_commit':os.environ['GITHUB_SHA'],'old_pinned_commit':subprocess.check_output(['git','rev-parse','HEAD'],cwd=old,text=True).strip(),'suite_sha256':hashlib.sha256(suite).hexdigest(),'requested_plan_sha256':hashlib.sha256(requested).hexdigest(),'adapter_sha256':hashlib.sha256(Path(__file__).read_bytes()).hexdigest(),'official_generator_sha256':hashlib.sha256((upstream/'benchmark_suite.py').read_bytes()).hexdigest(),'seed':plan['seed'],'rounds':25,'pairs':500000,'same_contracts_sha256':new_contracts,'scope':'New official unchanged public suite full gate. Separate from legacy12 and unavailable private paid suite. No formal competition submission.'}
    (stage/'provenance.json').write_text(json.dumps(provenance,indent=2)+'\n')
    (stage/'public-v2.json').write_bytes(suite)
    rows=[]
    for entry in plan['candidates']:
        name=entry['candidate'];src=upstream/'kernels/full/incumbent/Kernel.lean' if name=='baseline' else repo/'competitions/floatlib/candidates'/name/'Kernel.lean'
        raw=src.read_bytes();digest=hashlib.sha256(raw).hexdigest();assert digest==entry['sha256']
        dst=stage/'inputs'/name;dst.mkdir(parents=True,exist_ok=True);(dst/'Kernel.lean').write_bytes(raw)
        verdict=stage/(name+'-verdict.json'); logname=name+'-gate.log'
        with (stage/logname).open('wb') as log:
            p=subprocess.run([str(upstream/'.venv/bin/python'),'gate.py','--slot','full',str(dst),'--verdict',str(verdict)],cwd=upstream,env=env,stdout=log,stderr=subprocess.STDOUT,timeout=960)
        v=json.loads(verdict.read_bytes()) if verdict.exists() else {}
        full=bool(p.returncode==0 and v.get('passed') and v.get('mode')=='gate' and v.get('stage')=='score')
        row={'candidate':name,'kernel_sha256':digest,'full_gate':full,'exit_code':p.returncode,'stage':v.get('stage','UNKNOWN'),'reason':v.get('reason',''),'verdict':verdict.name,'verdict_sha256':hashlib.sha256(verdict.read_bytes()).hexdigest() if verdict.exists() else None}
        if full:
            assert v['suite']['sha256']==provenance['suite_sha256'] and len(v['rounds'])==25
            assert v['verifier_fingerprint']==v['verifier_fingerprint_end']
            assert set(v['classes'])==set(cell_work)
            total_s=sum(c['submission_ns']*cell_work[n] for n,c in v['classes'].items())
            total_i=sum(c['incumbent_ns']*cell_work[n] for n,c in v['classes'].items())
            ratio=total_s/total_i;assert abs(ratio-v['ratio'])<1e-10
            row.update(ratio=ratio,classes=v['classes'],rounds=v['rounds'],suite=v['suite'],cell_work=cell_work,scored_submission_total_ns=total_s,scored_reference_total_ns=total_i)
        rows.append(row)
        (stage/'summary.json').write_text(json.dumps({**provenance,'results':rows,'complete':len(rows)==len(plan['candidates']),'elapsed_seconds':time.monotonic()-started},indent=2)+'\n')
        if name=='baseline' and not full:break
    command(['git','diff','--exit-code'],'official-source-clean.log',upstream,20)
    if not rows or len(rows)!=len(plan['candidates']) or not all(r['full_gate'] for r in rows):raise RuntimeError('Public suite acceptance incomplete or failed; original receipts retained')
