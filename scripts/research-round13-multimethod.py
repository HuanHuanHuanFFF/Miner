"""Unmodified trusted engine co-measurement of already verified boundary source."""
from pathlib import Path
import dataclasses,hashlib,json,os,statistics
from round4 import ROOT,validate

def main():
    assert os.environ.get('GITHUB_ACTIONS')=='true'and os.environ.get('RUNNER_OS')=='Linux'
    spec=validate(os.environ['ROUND4_SPEC']);assert spec.get('multimethod_diagnostic')
    from bench import driver,corpora
    from bench.results import INCUMBENT,parse_results
    from sandbox import bwrap
    upstream=Path(os.environ['DEFLATE_ROOT']);cpu=str(min(os.sched_getaffinity(0)))
    config=dataclasses.replace(driver.Config.from_env(upstream/'validator'),reps=11,warmup=1,cpus=cpu,keep=driver.Keep.NEVER,bars=False)
    names=['public514','r13-514-abs15','public514-shadow'];by={e['name']:e for e in spec['entries']}
    paths={n:ROOT/by[n]['path']/'parse.rs'for n in names}
    workspace=driver._make_workspace(config,paths);crates=driver._generate(config,workspace,paths);driver._build(config,workspace,crates);rustc=driver._rustc_version(config,workspace,crates[INCUMBENT])
    corpus=corpora.load(upstream/'validator').by_name('corpus-stage1');out=Path(os.environ['RUNNER_TEMP'])/'round4-receipts/r13-multimethod';out.mkdir(parents=True,exist_ok=True)
    blocks=[]
    for block in range(1,5):
        order=[INCUMBENT]+(names if block%2 else names[::-1])
        cmd=[str(config.engine),str(corpus.path)]+[f'{n}={crates[n]}'for n in order]+['--corpus-name',corpus.name,'--reps','11','--warmup','1','--rustc-version',rustc,'--no-bars']
        r=bwrap.run(driver.measure_sandbox(config,workspace,corpus),cmd,cwd=None,timeout=config.timeout)
        (out/f'block{block}.stderr.log').write_text(r.stderr);assert r.returncode==0
        measured=parse_results(r.stdout,corpus);measured.raw_records[0]['benchmark_provenance']=driver.provenance(config)
        assert not any(measured.failures(n)for n in order)
        meta=measured.raw_records[0];assert all(meta['methods'][n]['source_sha256']==by[n]['hashes']['parse.rs']for n in names)
        assert meta['methods']['public514']['lib_sha256']==meta['methods']['public514-shadow']['lib_sha256']
        files=[x for x in measured.raw_records if x['kind']=='file'];assert len(files)==28 and sum(x['raw_bytes']for x in files)==15930000
        axes={n:[]for n in order};direct={n:[]for n in names if n!='public514'}
        for row in files:
            med={n:statistics.median(x['total_s']for x in row['methods'][n]['reps']if x['phase']=='measured')for n in order}
            for n in order:axes[n].append(med[n]/med[INCUMBENT])
            for n in direct:direct[n].append(med[n]/med['public514'])
            for n in names:
                assert row['methods'][n]['deterministic']and not row['methods'][n]['errors']
                assert row['methods'][n]['output_sha256']==row['methods']['public514']['output_sha256']
        (out/f'block{block}.jsonl').write_bytes(('\n'.join(json.dumps(x)for x in measured.raw_records)+'\n').encode())
        blocks.append({'block':block,'method_order':order,'official_form_axes':{n:statistics.mean(v)for n,v in axes.items()},
            'candidate_change_pct_vs_parent':100*(statistics.mean(axes['r13-514-abs15'])/statistics.mean(axes['public514'])-1),
            'shadow_change_pct_vs_parent':100*(statistics.mean(axes['public514-shadow'])/statistics.mean(axes['public514'])-1),
            'mean_file_direct_ratio_change_pct':{n:100*(statistics.mean(v)-1)for n,v in direct.items()}})
    record={'run_id':os.environ['GITHUB_RUN_ID'],'git_sha':os.environ['GITHUB_SHA'],'batch':os.environ['ROUND4_SPEC'],'status':'VERIFIED_FINITE_TRUSTED_MULTIMETHOD_DIAGNOSTIC','source_hashes':{n:by[n]['hashes']for n in names},'blocks':blocks,
        'scope':'Original trusted engine/encoder/crate boundary unchanged,4 methods including incumbent in one process,11 reps/1warmup,4 mirrored blocks. Engine rotates method order per rep. Co-measurement protocol differs from official one-candidate isolation; diagnostic only, not independent private/admission/reward evidence.'}
    (out/'multi.json').write_text(json.dumps(record,indent=2)+'\n');print(json.dumps({'status':record['status'],'blocks':blocks}))

if __name__=='__main__':main()
