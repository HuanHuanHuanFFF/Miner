"""444 finite native decode checks for search-changing R12 sources, not equality."""
from pathlib import Path
import hashlib,importlib.util,json,os,subprocess
from round4 import ROOT,validate

def harness(spec):
    by={e['name']:e for e in spec['entries']}
    pairs=[(e,by[e['native_decode_reference']])for e in spec['entries']if e.get('native_decode_reference')]
    assert pairs and len(pairs)<=4
    for c,r in pairs:assert (ROOT/c['path']/'parse.rs').resolve()!=(ROOT/r['path']/'parse.rs').resolve()
    module=importlib.util.spec_from_file_location('r12_finite_parent',ROOT/'scripts/research-round4.py');m=importlib.util.module_from_spec(module);module.loader.exec_module(m)
    text=m.build_harness(pairs)
    before='r_decode&&c_decode&&rt==ct';assert text.count(before)==1
    text=text.replace(before,'r_decode&&c_decode',1)
    before='if !equal{bad[i]+=1;';assert text.count(before)==1
    after='if let (Ok(rt),Ok(ct))=(&r,&c){if rt!=ct{println!("TOKEN_CHANGE {} {} {}",candidate,reference,label);}}'+before
    text=text.replace(before,after,1)
    return text,pairs

def main():
    assert os.environ.get('GITHUB_ACTIONS')=='true'and os.environ.get('RUNNER_OS')=='Linux'
    spec=validate(os.environ['ROUND4_SPEC']);text,pairs=harness(spec)
    build=Path(os.environ['RUNNER_TEMP'])/'r12-decode-build';build.mkdir(exist_ok=True)
    output=Path(os.environ['RUNNER_TEMP'])/'round4-receipts'/'r12-decode';output.mkdir(parents=True,exist_ok=True)
    source=build/'decode.rs';source.write_text(text);binary=build/'decode'
    compiled=subprocess.run(['rustc','+nightly-2026-08-18','--edition=2021','-O','-C','overflow-checks=yes',str(source),'-o',str(binary)],capture_output=True,text=True,timeout=180)
    (output/'build.log').write_text(compiled.stdout+compiled.stderr);assert compiled.returncode==0
    run=subprocess.run([str(binary),str(Path(os.environ['DEFLATE_ROOT'])/'data/benchmark/corpus-stage1')],capture_output=True,text=True,timeout=240)
    (output/'run.log').write_text(run.stdout+run.stderr);assert run.returncode==0
    rows=[];changes={c['name']:[]for c,r in pairs}
    for line in run.stdout.splitlines():
        if line.startswith('TOKEN_CHANGE '):
            _,candidate,reference,label=line.split();changes[candidate].append(label)
        elif line.startswith('EQUIVALENCE_RESULT '):
            _,candidate,reference,count,failed=line.split();assert int(count)==444 and int(failed)==0,(candidate,count,failed)
            rows.append({'candidate':candidate,'reference':reference,'cases':int(count),'decode_or_panic_failures':int(failed),'token_changes':changes[candidate]})
    assert len(rows)==len(pairs)
    result={'run_id':os.environ['GITHUB_RUN_ID'],'git_sha':os.environ['GITHUB_SHA'],'batch':os.environ['ROUND4_SPEC'],
        'status':'VERIFIED_FINITE_NATIVE_DECODE_ONLY','harness_sha256':hashlib.sha256(source.read_bytes()).hexdigest(),
        'source_hashes':{c['name']:c['hashes']for c,r in pairs},'cases':rows,
        'scope':'444 finite reference/candidate decode checks with token changes permitted. Not all-input token equality, full Lean gate, timing, formal admission or reward.'}
    (output/'decode.json').write_text(json.dumps(result,indent=2)+'\n')
    print(json.dumps({'status':result['status'],'cases':[{**r,'token_changes':len(r['token_changes'])}for r in rows]}))

if __name__=='__main__':main()
