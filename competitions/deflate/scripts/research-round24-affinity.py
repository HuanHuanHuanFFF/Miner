"""Probe actual sandbox affinity, then isolate explicit binding if it differs."""
from pathlib import Path
import dataclasses,hashlib,importlib,json,os,statistics as st,subprocess,sys
from round4 import ROOT,validate
def sha(p):return hashlib.sha256(p.read_bytes()).hexdigest()
def main():
    assert os.environ.get('GITHUB_ACTIONS')=='true' and os.environ.get('RUNNER_OS')=='Linux' and os.environ.get('ROUND4_SPEC_DIR')=='evidence/round24'
    spec=validate(os.environ['ROUND4_SPEC']);assert spec['r24_affinity_diagnostic'] and spec['isolated_blocks']==2 and spec['multimethod_blocks']==0
    up=Path(os.environ['DEFLATE_ROOT']);sys.path.insert(0,str(up/'validator'))
    from bench import driver,corpora
    from bench.results import INCUMBENT
    from sandbox import bwrap
    names=spec['diagnostic_methods'];by={e['name']:e for e in spec['entries']};assert len(names)==4
    paths={n:ROOT/by[n]['path']/'parse.rs'for n in names};cpu=str(min(os.sched_getaffinity(0)))
    cfg=dataclasses.replace(driver.Config.from_env(up/'validator'),reps=11,warmup=1,cpus=cpu,keep=driver.Keep.NEVER,bars=False);assert cfg.timeout==300.0;driver.check(cfg)
    corpus=corpora.load(up/'validator').by_name('corpus-stage1');ws=driver._make_workspace(cfg,paths);wrapper=ws/'affinity-context.py';wrapper.write_text(importlib.import_module('research-round18-multimethod').WRAPPER)
    out=Path(os.environ['RUNNER_TEMP'])/'round4-receipts/r24-affinity';out.mkdir(parents=True)
    result={'run_id':os.environ['GITHUB_RUN_ID'],'git_sha':os.environ['GITHUB_SHA'],'batch':os.environ['ROUND4_SPEC'],'status':'STARTED','requested_cpu':cpu,'driver_sha256':sha(up/'validator/bench/driver.py'),'original_engine_sha256':sha(cfg.engine),'driver_provenance':driver.provenance(cfg),'source_files':{n:by[n]['hashes']for n in names},'blocks':[],'scope':'Diagnostic only: original engine/encoder/loader and paired incumbent+onecandidate,1warmup11reps. Actual sandbox context first. If mask is broad, sole intervention is explicit process affinity; no score promotion or official protocol correction.'}
    def save():(out/'affinity.json').write_bytes((json.dumps(result,indent=2)+'\n').encode())
    save()
    probe=bwrap.run(driver.measure_sandbox(cfg,ws,corpus),['/usr/bin/python3',str(wrapper),'observe','/usr/bin/true'],cwd=None,timeout=30)
    (out/'context-probe.stdout.log').write_text(probe.stdout);(out/'context-probe.stderr.log').write_text(probe.stderr);assert probe.returncode==0
    contexts=[json.loads(x.split(' ',1)[1])for x in probe.stderr.splitlines()if x.startswith('R18_ENGINE_PROCESS_CONTEXT ')];assert len(contexts)==1
    result['context_probe']=contexts[0];save()
    if contexts[0]['affinity_before_exec']==[int(cpu)]:
        result['status']='COMPLETE_CONTEXT_ALREADY_SINGLETON_NO_TIMING_CONTRAST';result['decision']='Do not spend16pairedruns on an idempotent intervention. This context probe does not explain earlier denominator variation.';save();subprocess.run(['git','diff','--exit-code'],cwd=up,check=True);print(result['status']);return
    crates=driver._generate(cfg,ws,paths);driver._build(cfg,ws,crates);rustc=driver._rustc_version(cfg,ws,crates[INCUMBENT]);identities={};libraries={}
    for block in [1,2]:
        for n in (names if block==1 else names[::-1]):
            for pinned in ([False,True]if block==1 else[True,False]):
                mode='explicit_single_cpu'if pinned else'original_cgroup_request';stem=f'{mode}-block{block}-{n}'
                cmd=[str(cfg.engine),str(corpus.path),f'{INCUMBENT}={crates[INCUMBENT]}',f'{n}={crates[n]}','--corpus-name',corpus.name,'--reps','11','--warmup','1','--rustc-version',rustc,'--no-bars']
                p=bwrap.run(driver.measure_sandbox(cfg,ws,corpus),['/usr/bin/python3',str(wrapper),cpu if pinned else'observe']+cmd,cwd=None,timeout=cfg.timeout)
                path=out/(stem+'.jsonl');path.write_text(p.stdout);(out/(stem+'.stderr.log')).write_text(p.stderr);assert p.returncode==0
                cc=[json.loads(x.split(' ',1)[1])for x in p.stderr.splitlines()if x.startswith('R18_ENGINE_PROCESS_CONTEXT ')];assert len(cc)==1
                if pinned:assert cc[0]['affinity_before_exec']==[int(cpu)]
                measured=driver.parse_results(p.stdout,corpus);meta=measured.raw_records[0];fs=[x for x in measured.raw_records if x['kind']=='file'];assert len(fs)==28 and meta['measured_rounds']==11 and meta['warmup_rounds']==1
                assert meta['methods'][n]['source_sha256']==by[n]['hashes']['parse.rs'];ratios=[]
                for method in [INCUMBENT,n]:
                    key=meta['methods'][method]['source_sha256'];lib=meta['methods'][method]['lib_sha256'];assert libraries.setdefault(key,lib)==lib
                for f in fs:
                    med={}
                    for method in [INCUMBENT,n]:
                        m=f['methods'][method];assert m['deterministic'] and not m['errors'];rep=[x for x in m['reps']if x['phase']=='measured'];assert len(rep)==11;med[method]=st.median(x['total_s']for x in rep)
                        key=(meta['methods'][method]['source_sha256'],f['file']);ident=(f['sha256'],m['tokens_sha256'],m['output_sha256']);assert identities.setdefault(key,ident)==ident
                    ratios.append(med[n]/med[INCUMBENT])
                row={'mode':mode,'block':block,'method':n,'diagnostic_time_axis':st.mean(ratios),'raw_file':path.name,'raw_sha256':sha(path),'actual_context':cc[0],'metadata':meta};result['blocks'].append(row);save();print('AFFINITY_DIAGNOSTIC',mode,block,n,row['diagnostic_time_axis'],flush=True)
    subprocess.run(['git','diff','--exit-code'],cwd=up,check=True)
    result['status']='COMPLETE_CONTROLLED_PAIRED_AFFINITY_DIAGNOSTIC';save()
if __name__=='__main__':main()
