"""Local actual-data parser and interface tests; Linux runtime remains NOT_RUN."""
from pathlib import Path
import ast,copy,hashlib,importlib.util,json,time
HERE=Path(__file__).resolve().parent
REPO=next(p for p in HERE.parents if (p/'competitions/floatlib').is_dir())
sp=importlib.util.spec_from_file_location('r13_multi_test_target',HERE/'profile-whole-multi-current.py')
m=importlib.util.module_from_spec(sp);sp.loader.exec_module(m)


def run():
    started=time.monotonic();root=REPO/'competitions/floatlib/candidates/f01-mul-log2-proof1/ci-runs/40094358287'
    ix=json.loads((root/'original-artifact-hashes.json').read_bytes());rawroot=root/ix['directory']
    planpath=next(rawroot.rglob('profile-r13-coarse-full-public-plan.json'));plan=json.loads(planpath.read_bytes())
    logpath=planpath.with_name('profile-r13-coarse-original-whole-full-plan.log');log=logpath.read_text(encoding='utf-8')
    rows=m.bench_rows(log,plan);assert len(rows)==156
    actual=json.loads(planpath.with_name('profile-r13-coarse-original-whole-full-plan.json').read_bytes())
    assert rows==actual;m.verify_same_seed(rows,copy.deepcopy(rows))
    assert m.SEEDS==(1224011,1224091,1224092)and m.INITIAL_SEED==1224016 and m.PROCESSES==2 and m.INNER==3 and m.MAX_SECONDS==300
    rejected=[]
    def reject(name,fn):
        try:fn()
        except RuntimeError:rejected.append(name)
        else:raise AssertionError(name+' accepted')
    reject('missing case',lambda:m.bench_rows('\n'.join(log.splitlines()[:-1]),plan))
    reject('duplicate row',lambda:m.bench_rows(log+'\n'+log.splitlines()[0],plan))
    reject('missing plan case',lambda:m.bench_rows(log,{**plan,'cases':plan['cases'][:-1]}))
    reject('instrumented fine marker',lambda:m.bench_rows(log+'\nFL13 cat=0',plan))
    reject('instrumented coarse marker',lambda:m.bench_rows(log+'\nFC13 cat=0',plan))
    changed=copy.deepcopy(rows);changed[next(iter(rows))]['checksum']+=1
    reject('same-seed checksum mismatch',lambda:m.verify_same_seed(rows,changed))
    changed=copy.deepcopy(rows);changed.pop(next(iter(rows)))
    reject('same-seed coverage mismatch',lambda:m.verify_same_seed(rows,changed))
    first=log.splitlines()[0];parts=first.split();wrong=parts.copy();wrong[1]='false'if parts[1]=='true'else'true'
    reject('wrong timed flag',lambda:m.bench_rows(log.replace(first,' '.join(wrong),1),plan))
    wrong=parts.copy();wrong[2]='0'
    reject('zero timed whole',lambda:m.bench_rows(log.replace(first,' '.join(wrong),1),plan))
    module_source=(HERE/'profile-whole-multi-current.py').read_text(encoding='utf-8')
    entry=(HERE/'profile-whole-multi-entry.py').read_text(encoding='utf-8')
    ast.parse(module_source);ast.parse(entry)
    assert "'BENCH_PLAN':compact,'BENCH_SEED':str(actual_seed)"in module_source
    assert "for actual_seed in SEEDS:"in module_source and "for process in range(PROCESSES):"in module_source
    assert "verify_same_seed(processes[0]['rows'],processes[1]['rows'])"in module_source
    assert 'source_c.write'not in module_source and 'compile_argv'not in module_source and 'link_argv'not in module_source
    assert "profile-whole-multi-current.py"in entry and "('upstream','kernel','out','plan')"in entry
    assert "g.STAGES=[('intake',g.intake),('policy',g.policy),('statement',statement)]"in entry
    result={'state':'PASS','exit_code':0,'elapsed_seconds':time.monotonic()-started,'actual_oldDF_rows':156,
        'fixture_plan_sha256':hashlib.sha256(planpath.read_bytes()).hexdigest(),
        'fixture_original_log_sha256':hashlib.sha256(logpath.read_bytes()).hexdigest(),'rejected':rejected,
        'verified_interface':'four CLI args, exact three exposed seeds,6whole processes, per-process explicit plan+seed environment, same-seed-only comparisons, original statement-only gate',
        'source_sha256':{n:hashlib.sha256((HERE/n).read_bytes()).hexdigest()for n in ['profile-whole-multi-current.py','profile-whole-multi-entry.py','profile-whole-multi-test.py']},
        'Linux_runtime':'NOT_RUN'}
    (HERE/'profile-whole-multi-tests.json').write_text(json.dumps(result,indent=2)+'\n',encoding='utf-8',newline='\n')
    print(json.dumps(result))


if __name__=='__main__':run()
