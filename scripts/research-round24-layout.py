"""Process-local address-layout contrast; original engine and sandbox retained."""
from pathlib import Path
import dataclasses,hashlib,importlib,json,os,statistics as st,subprocess,sys
from round4 import ROOT,validate
def sha(p):return hashlib.sha256(p.read_bytes()).hexdigest()
def main():
    assert os.environ.get('GITHUB_ACTIONS')=='true' and os.environ.get('RUNNER_OS')=='Linux'
    spec=validate(os.environ['ROUND4_SPEC']);assert spec['r24_layout_diagnostic'];up=Path(os.environ['DEFLATE_ROOT']);sys.path.insert(0,str(up/'validator'))
    from bench import driver,corpora
    from bench.results import INCUMBENT
    from sandbox import bwrap
    names=spec['diagnostic_methods'];by={e['name']:e for e in spec['entries']};paths={n:ROOT/by[n]['path']/'parse.rs'for n in names};cpu=str(min(os.sched_getaffinity(0)))
    cfg=dataclasses.replace(driver.Config.from_env(up/'validator'),reps=11,warmup=1,cpus=cpu,keep=driver.Keep.NEVER,bars=False);assert cfg.timeout==300.0;driver.check(cfg);corpus=corpora.load(up/'validator').by_name('corpus-stage1');ws=driver._make_workspace(cfg,paths)
    code=importlib.import_module('research-round18-multimethod').WRAPPER.replace("paths=['/proc/self/status'","paths=['/proc/self/personality','/proc/sys/kernel/randomize_va_space','/proc/self/status'")
    wrapper=ws/'layout-context.py';wrapper.write_text(code);out=Path(os.environ['RUNNER_TEMP'])/'round4-receipts/r24-layout';out.mkdir(parents=True)
    prefix=['/usr/bin/setarch','x86_64','-R'];result={'status':'STARTED','run_id':os.environ['GITHUB_RUN_ID'],'git_sha':os.environ['GITHUB_SHA'],'batch':os.environ['ROUND4_SPEC'],'original_engine_sha256':sha(cfg.engine),'driver_sha256':sha(up/'validator/bench/driver.py'),'incumbent_source_sha256':sha(up/'validator/incumbent/parse.rs'),'source_files':{n:by[n]['hashes']for n in names},'blocks':[],'scope':'Diagnostic-only originalpaired11 engine. Soleintervention is child-process ADDR_NO_RANDOMIZE throughsetarch; no global sysctl, sandbox or perfpermissions changes. Originalcgrouprequest and sourcebytes retained inbotharms.'}
    def save():(out/'layout.json').write_bytes((json.dumps(result,indent=2)+'\n').encode())
    def contexts(p):return [json.loads(x.split(' ',1)[1])for x in p.stderr.splitlines()if x.startswith('R18_ENGINE_PROCESS_CONTEXT ')]
    def flag(c):
        value=c['files']['/proc/self/personality'];return int(value.strip(),16) if isinstance(value,str) else None
    probes={}
    for fixed in [False,True]:
        label='process_no_randomize'if fixed else'original_randomization';p=bwrap.run(driver.measure_sandbox(cfg,ws,corpus),(prefix if fixed else[])+['/usr/bin/python3',str(wrapper),'observe','/usr/bin/true'],cwd=None,timeout=30);(out/(label+'-probe.stdout.log')).write_text(p.stdout);(out/(label+'-probe.stderr.log')).write_text(p.stderr);cc=contexts(p);probes[label]={'returncode':p.returncode,'contexts':cc}
        if not fixed:assert p.returncode==0 and len(cc)==1
    result['probes']=probes;save();fixed=probes['process_no_randomize'];original=probes['original_randomization']
    if fixed['returncode']!=0 or len(fixed['contexts'])!=1 or flag(fixed['contexts'][0]) is None or not(flag(fixed['contexts'][0])&0x40000):
        result['status']='COMPLETE_INTERVENTION_UNAVAILABLE_NO_TIMING';result['decision']='Retain probe failure and stop. Do not alterkernel settings or seek privileged workaround.';save();print(result['status']);return
    if flag(original['contexts'][0]) is not None and flag(original['contexts'][0])&0x40000:
        result['status']='COMPLETE_ORIGINAL_ALREADY_NO_RANDOMIZE_NO_CONTRAST';save();print(result['status']);return
    crates=driver._generate(cfg,ws,paths);driver._build(cfg,ws,crates);rustc=driver._rustc_version(cfg,ws,crates[INCUMBENT]);identities={};libs={}
    for block in [1,2]:
        for n in (names if block==1 else names[::-1]):
            for fixed in ([False,True]if block==1 else[True,False]):
                mode='process_no_randomize'if fixed else'original_randomization';stem=f'{mode}-block{block}-{n}';cmd=[str(cfg.engine),str(corpus.path),f'{INCUMBENT}={crates[INCUMBENT]}',f'{n}={crates[n]}','--corpus-name',corpus.name,'--reps','11','--warmup','1','--rustc-version',rustc,'--no-bars']
                p=bwrap.run(driver.measure_sandbox(cfg,ws,corpus),(prefix if fixed else[])+['/usr/bin/python3',str(wrapper),'observe']+cmd,cwd=None,timeout=cfg.timeout);path=out/(stem+'.jsonl');path.write_text(p.stdout);(out/(stem+'.stderr.log')).write_text(p.stderr);assert p.returncode==0;cc=contexts(p);assert len(cc)==1
                if fixed:assert flag(cc[0])&0x40000
                m=driver.parse_results(p.stdout,corpus);meta=m.raw_records[0];fs=[x for x in m.raw_records if x['kind']=='file'];assert len(fs)==28 and meta['measured_rounds']==11 and meta['warmup_rounds']==1;assert meta['methods'][n]['source_sha256']==by[n]['hashes']['parse.rs'];ratios=[]
                for method in [INCUMBENT,n]:
                    h=meta['methods'][method]['source_sha256'];v=meta['methods'][method]['lib_sha256'];assert libs.setdefault(h,v)==v
                for f in fs:
                    med={}
                    for method in [INCUMBENT,n]:
                        d=f['methods'][method];assert d['deterministic'] and not d['errors'];reps=[x for x in d['reps']if x['phase']=='measured'];assert len(reps)==11;med[method]=st.median(x['total_s']for x in reps);key=(meta['methods'][method]['source_sha256'],f['file']);ident=(f['sha256'],d['tokens_sha256'],d['output_sha256']);assert identities.setdefault(key,ident)==ident
                    ratios.append(med[n]/med[INCUMBENT])
                result['blocks'].append({'mode':mode,'block':block,'method':n,'diagnostic_time_axis':st.mean(ratios),'raw_file':path.name,'raw_sha256':sha(path),'actual_context':cc[0],'metadata':meta});save();print('LAYOUT_DIAGNOSTIC',mode,block,n,st.mean(ratios),flush=True)
    subprocess.run(['git','diff','--exit-code'],cwd=up,check=True);result['status']='COMPLETE_CONTROLLED_PAIRED_LAYOUT_DIAGNOSTIC';save()
if __name__=='__main__':main()
