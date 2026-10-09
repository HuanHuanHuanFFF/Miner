"""Separate original one-candidate measurements from same-process diagnostics."""
from pathlib import Path
import dataclasses, hashlib, json, os, statistics, sys
from round4 import ROOT, validate

WRAPPER = r'''
import json,os,pathlib,sys
requested=sys.argv[1]
affinity_initial=sorted(os.sched_getaffinity(0))
if requested!='observe':
 os.sched_setaffinity(0,{int(requested)})
paths=['/proc/self/status','/proc/self/cgroup','/sys/fs/cgroup/cpuset.cpus.effective','/sys/fs/cgroup/cpu.max','/sys/fs/cgroup/memory.max']
values={}
for p in paths:
 try: values[p]=pathlib.Path(p).read_text()
 except OSError as e: values[p]={'unavailable':type(e).__name__}
print('R18_ENGINE_PROCESS_CONTEXT '+json.dumps({'pid_before_exec':os.getpid(),'affinity_initial':affinity_initial,'explicit_affinity_request':requested,'affinity_before_exec':sorted(os.sched_getaffinity(0)),'files':values,'scope':'This process immediately execs the unmodified engine; exec preserves affinity and cgroup membership. Explicit binding is diagnostic only.'}),file=sys.stderr,flush=True)
os.execv(sys.argv[2],sys.argv[2:])
'''

def save(p, value):
    p.write_text(json.dumps(value,indent=2)+'\n',encoding='utf-8')

def main():
    assert os.environ.get('GITHUB_ACTIONS') == 'true' and os.environ.get('RUNNER_OS') == 'Linux'
    spec = validate(os.environ['ROUND4_SPEC']); assert spec['r18_mode'] == 'diagnostic'
    upstream = Path(os.environ['DEFLATE_ROOT'])
    sys.path.insert(0,str(upstream/'validator'))
    from bench import driver, corpora
    from bench.results import INCUMBENT
    from sandbox import bwrap
    cpu = str(min(os.sched_getaffinity(0)))
    config = dataclasses.replace(driver.Config.from_env(upstream/'validator'),reps=11,warmup=1,cpus=cpu,keep=driver.Keep.NEVER,bars=False)
    driver.check(config)
    names = spec['diagnostic_methods']; by = {e['name']:e for e in spec['entries']}
    paths = {n:ROOT/by[n]['path']/'parse.rs' for n in names}
    corpus = corpora.load(upstream/'validator').by_name('corpus-stage1')
    out = Path(os.environ['RUNNER_TEMP'])/'round4-receipts/r18-noise';out.mkdir(parents=True,exist_ok=True)
    result = {'run_id':os.environ['GITHUB_RUN_ID'],'git_sha':os.environ['GITHUB_SHA'],'batch':os.environ['ROUND4_SPEC'],'spec':spec,'status':'STARTED','requested_cpu':cpu,'blocks':[],'environment':driver.provenance(config),
              'scope':'Original isolated official protocol and multimethod diagnostics remain separate. Public repeated measurements are not formal admission or success probabilities. No candidate changes in this experiment.'}
    save(out/'noise.json',result)
    identities = {}
    def record(measured, order, protocol, block):
        meta = measured.raw_records[0]
        meta['benchmark_provenance'] = driver.provenance(config)
        files = [r for r in measured.raw_records if r['kind'] == 'file']
        assert len(files)==28 and sum(f['raw_bytes'] for f in files)==15930000
        axes={n:[] for n in order};sizes={n:[] for n in order}
        for n in order:
            assert not measured.failures(n)
            if n != INCUMBENT:
                assert meta['methods'][n]['source_sha256']==by[n]['hashes']['parse.rs']
        for f in files:
            med={}
            for n in order:
                m=f['methods'][n];assert m['deterministic'] and not m['errors']
                reps=[v['total_s'] for v in m['reps'] if v['phase']=='measured'];assert len(reps)==11 and min(reps)>0
                med[n]=statistics.median(reps)
                key=(meta['methods'][n]['source_sha256'],f['file'])
                ident=(f['sha256'],m['tokens_sha256'],m['output_sha256'],m['output_bytes'])
                assert identities.setdefault(key,ident)==ident
            for n in order:
                axes[n].append(med[n]/med[INCUMBENT]);sizes[n].append(100*f['methods'][n]['output_bytes']/f['raw_bytes'])
        path=out/f'{protocol}-block{block}-{"-".join(order[1:])}.jsonl'
        path.write_bytes(('\n'.join(json.dumps(r) for r in measured.raw_records)+'\n').encode())
        row={'protocol':protocol,'block':block,'order':order,'axes':{n:statistics.mean(v) for n,v in axes.items()},'sizes':{n:statistics.mean(v) for n,v in sizes.items()},'raw_file':path.name,'raw_sha256':hashlib.sha256(path.read_bytes()).hexdigest(),'libraries':{n:meta['methods'][n]['lib_sha256'] for n in order}}
        result['blocks'].append(row);save(out/'noise.json',result)
        print('R18_MEASUREMENT',json.dumps(row),flush=True)
    for block in range(1,spec['isolated_blocks']+1):
        for n in (names if block%2 else names[::-1]):
            measured=driver.run(config,{n:paths[n]},corpus).only()
            record(measured,[INCUMBENT,n],'official_isolated',block)
    workspace=driver._make_workspace(config,paths);crates=driver._generate(config,workspace,paths);driver._build(config,workspace,crates);rustc=driver._rustc_version(config,workspace,crates[INCUMBENT])
    wrapper=workspace/'r18-context.py';wrapper.write_text(WRAPPER)
    def measure_shared(block, order, protocol, pin):
        cmd=[str(config.engine),str(corpus.path)]+[f'{n}={crates[n]}' for n in order]+['--corpus-name',corpus.name,'--reps','11','--warmup','1','--rustc-version',rustc,'--no-bars']
        r=bwrap.run(driver.measure_sandbox(config,workspace,corpus),['/usr/bin/python3',str(wrapper),cpu if pin else 'observe']+cmd,cwd=None,timeout=config.timeout)
        stem=f'{protocol}-block{block}-{"-".join(order[1:])}'
        # Persist the original stream before any post-run assertion can fail.
        (out/(stem+'.raw.jsonl')).write_text(r.stdout)
        (out/(stem+'.stderr.log')).write_text(r.stderr)
        assert r.returncode==0
        contexts=[json.loads(line.removeprefix('R18_ENGINE_PROCESS_CONTEXT ')) for line in r.stderr.splitlines() if line.startswith('R18_ENGINE_PROCESS_CONTEXT ')]
        assert len(contexts)==1
        save(out/(stem+'-actual-process.json'),contexts[0])
        if pin: assert contexts[0]['affinity_before_exec']==[int(cpu)]
        measured=driver.parse_results(r.stdout,corpus)
        meta=measured.raw_records[0]
        if len(order)>2:
            assert meta['methods'][names[0]]['lib_sha256']==meta['methods'][names[1]]['lib_sha256']
            assert meta['methods'][names[2]]['lib_sha256']==meta['methods'][names[3]]['lib_sha256']
        record(measured,order,protocol,block)
    for block in range(1,spec['multimethod_blocks']+1):
        order=[INCUMBENT]+(names if block%2 else names[::-1])
        modes=[False,True] if block%2 else [True,False]
        for pin in modes:
            measure_shared(block,order,'multimethod_pinned_diagnostic' if pin else 'multimethod_observed_diagnostic',pin)
    for block in range(1,spec['isolated_blocks']+1):
        for n in (names if block%2 else names[::-1]):
            measure_shared(block,[INCUMBENT,n],'isolated_pinned_diagnostic',True)
    result['status']='COMPLETE_PROTOCOL_SEPARATED_MEASUREMENT_DIAGNOSTIC';save(out/'noise.json',result)
    print(result['status'],flush=True)

if __name__ == '__main__':
    main()
