"""Low-frequency inclusive phases on exact628/shared/hint, no hot-pair timers."""
from pathlib import Path
import hashlib
import importlib
import json
import os
import subprocess

ROOT=Path(__file__).resolve().parents[1]
CONFIG={
 'public628':('784e02703c98a32f85753cae4f3b62aea3f505d91088869f327e0ad646629c14',
              ['parse','seed_parse','SFbase','SFshape','SFprev','SFsmallmatches','SFmorematches','SFsolve','SFseed','SFprefix','SFheavy','refine','Z469']),
 'r26-b-628-shared-cache-fix1':('582c3ea7236dfaa93a801a265713e3c96175d6978d895e62a9bea024fbdd39ac',
              ['parse','r26_b_seed_shared','seed_parse','r26_b_SFbase','SFbase','r26_b_SFshape','SFshape','SFprev','r26_b_small_cached','r26_b_more_cached','SFsmallmatches','SFmorematches','SFsolve','SFseed','SFprefix','r26_b_SFheavy','SFheavy','refine','Z469']),
 'r26-b-628-cache-hint':('1d55b3acf2db9c737b4af84a234b96d33748089dc0bb80300314192fde0581cd',
              ['parse','r26_b_seed_shared','seed_parse','r26_b_SFbase','SFbase','r26_b_SFshape','SFshape','SFprev','r26_b_SFsmallmatches_hint','r26_b_SFmorematches_hint','SFsmallmatches','SFmorematches','SFsolve','SFseed','SFprefix','r26_b_SFheavy','SFheavy','refine','Z469']),
}


def sha(raw):return hashlib.sha256(raw).hexdigest()


def preflight(spec):
    assert spec.get('r26_b_cache_phases')is True and spec.get('native_encoder')is False
    by={e['name']:e for e in spec['entries']};instrument=importlib.import_module('research-round18-functions').instrument
    checks={}
    for name,(digest,functions)in CONFIG.items():
        e=by[name];raw=(ROOT/e['path']/'parse.rs').read_bytes();assert sha(raw)==digest==e['hashes']['parse.rs']
        observed=instrument(raw,functions)
        checks[name]={'source_sha256':digest,'observer_sha256':sha(observed),'functions':functions}
    return {'status':'VERIFIED_THREE_FROZEN_SOURCES_AND_COARSE_WRAPPER_STRUCTURE_ONLY','entries':checks,
            'scope':'No localRustexecution; no SFmatchlen/cache-known/per-pair clocks.'}


def main():
    assert os.environ.get('GITHUB_ACTIONS')=='true'and os.environ.get('RUNNER_OS')=='Linux'
    spec=importlib.import_module('round4').validate(os.environ['ROUND4_SPEC']);preflight(spec)
    by={e['name']:e for e in spec['entries']};instrument=importlib.import_module('research-round18-functions').instrument
    build=Path(os.environ['RUNNER_TEMP'])/'r26-b-cache-phases';build.mkdir()
    out=Path(os.environ['RUNNER_TEMP'])/'round4-receipts/r26-b-cache-phases';out.mkdir(parents=True)
    corpus=Path(os.environ['DEFLATE_ROOT'])/'data/benchmark/corpus-stage1'
    records={}
    for index,(name,(digest,functions))in enumerate(CONFIG.items()):
        frozen=ROOT/by[name]['path']/'parse.rs';observed=build/f'observed-{index}.rs';observed.write_bytes(instrument(frozen.read_bytes(),functions))
        harness=importlib.import_module('research-round13-counts').HARNESS.replace('FROZEN',str(frozen)).replace('OBSERVED',str(observed)).replace('observed::r13_take()','observed::r15_take()').replace('R13_COUNT','R26_CACHE_PHASE')
        driver=build/f'driver-{index}.rs';driver.write_text(harness);binary=build/f'check-{index}'
        c=subprocess.run(['rustc','+nightly-2026-08-18','--edition=2021','-O','-C','overflow-checks=yes',str(driver),'-o',str(binary)],capture_output=True,text=True,timeout=240)
        (out/f'{name}.compile.log').write_text(c.stdout+c.stderr);assert c.returncode==0
        r=subprocess.run([str(binary),str(corpus)],capture_output=True,text=True,timeout=480)
        (out/f'{name}.run.log').write_text(r.stdout+r.stderr);assert r.returncode==0
        rows=[]
        for line in r.stdout.splitlines():
            if not line.startswith('R26_CACHE_PHASE '):continue
            _,file,size,*values=line.split();assert len(values)==2*len(functions)
            data=(corpus/file).read_bytes();assert len(data)==int(size);v=list(map(int,values))
            rows.append({'file':file,'raw_bytes':len(data),'input_sha256':sha(data),
                         'functions':{fn:{'calls':v[2*i],'inclusive_ns':v[2*i+1]}for i,fn in enumerate(functions)}})
        assert len(rows)==28 and sum(r['raw_bytes']for r in rows)==15930000
        records[name]={'source_hashes':by[name]['hashes'],'observer_sha256':sha(observed.read_bytes()),
                       'driver_sha256':sha(driver.read_bytes()),'functions':functions,'rows':rows,
                       'totals':{fn:{k:sum(row['functions'][fn][k]for row in rows)for k in ('calls','inclusive_ns')}for fn in functions}}
    reference={r['file']:(r['raw_bytes'],r['input_sha256'])for r in records['public628']['rows']}
    assert all({r['file']:(r['raw_bytes'],r['input_sha256'])for r in item['rows']}==reference for item in records.values())
    result={'status':'VERIFIED_THREE_COARSE_PHASE_OBSERVERS_FROZEN_TOKEN_DECODE_EQUAL',
            'run_id':os.environ['GITHUB_RUN_ID'],'git_sha':os.environ['GITHUB_SHA'],'batch':os.environ['ROUND4_SPEC'],
            'entries':records,
            'scope':'Eachvariant separately compares exact frozenparse tokens to its observedparse on all28files and independentlydecodes. Coarsebase/SFprev/collector/solve/heavy/classifier phases only; no timer on hotSFmatchlen/cache-known pair loop. No original pairedtime replacement.',
            'limits':['Inclusive nestedtimes overlap; do notsum base/seed/parse or collector/heavy/shape savings.',
                      'Observerwrappers affect code layout/inlining. Crossvariant times are diagnostic and are not source-level causation or recoverable gain bounds.',
                      'The B3 standardraw decomposition remains actualtotaltime evidence; thisdiagnostic onlyresolves where work/overhead lives.',
                      'No exactproof/gate/privateadmission/reward evidence.']}
    (out/'receipt.json').write_bytes((json.dumps(result,indent=2)+'\n').encode())
    print(json.dumps({'status':result['status'],'totals':{name:r['totals']for name,r in records.items()}},indent=2))


if __name__=='__main__':main()
