"""R14 uses the existing whole-parser checks and exercises new DNA helpers directly."""
from pathlib import Path
import hashlib,importlib.util,json,os,subprocess,sys
from round4 import ROOT,validate

def main():
    assert os.environ.get('GITHUB_ACTIONS')=='true' and os.environ.get('RUNNER_OS')=='Linux'
    subprocess.run([sys.executable,str(ROOT/'scripts/research-round13.py')],check=True)
    spec=validate(os.environ['ROUND4_SPEC']);names=spec.get('dna_direct_checks',[])
    if not names:return
    by={e['name']:e for e in spec['entries']};assert len(names)==1 and set(names)<=set(by)
    entry=by[names[0]];reference=by[entry['comparison_baseline']]
    loader=importlib.util.spec_from_file_location('r14_finite',ROOT/'scripts/research-round4.py')
    module=importlib.util.module_from_spec(loader);loader.loader.exec_module(module)
    text=module.build_harness([(entry,reference)])
    assert text.count('candidate0::parse')==1 and text.count('reference0::parse')==1
    text=text.replace('candidate0::parse','candidate0::p125_row4').replace('reference0::parse','reference0::p125_row4')
    assert text.count('r_decode&&c_decode&&rt==ct')==1
    text=text.replace('r_decode&&c_decode&&rt==ct','r_decode&&c_decode')
    build=Path(os.environ['RUNNER_TEMP'])/'r14-dna-direct-build';build.mkdir(exist_ok=True)
    out=Path(os.environ['RUNNER_TEMP'])/'round4-receipts/r14-dna-direct';out.mkdir(parents=True,exist_ok=True)
    source=build/'direct.rs';source.write_text(text);binary=build/'direct'
    compile=subprocess.run(['rustc','+nightly-2026-08-18','--edition=2021','-O','-C','overflow-checks=yes',str(source),'-o',str(binary)],capture_output=True,text=True,timeout=180)
    (out/'compile.log').write_text(compile.stdout+compile.stderr);assert compile.returncode==0
    run=subprocess.run([str(binary),str(Path(os.environ['DEFLATE_ROOT'])/'data/benchmark/corpus-stage1')],capture_output=True,text=True,timeout=240)
    (out/'run.log').write_text(run.stdout+run.stderr);assert run.returncode==0
    lines=[s for s in run.stdout.splitlines()if s.startswith('EQUIVALENCE_RESULT ')]
    assert len(lines)==1;_,candidate,parent,cases,failures=lines[0].split()
    assert candidate==entry['name'] and parent==reference['name'] and int(cases)==444 and int(failures)==0
    result={'run_id':os.environ['GITHUB_RUN_ID'],'git_sha':os.environ['GITHUB_SHA'],'batch':os.environ['ROUND4_SPEC'],
        'status':'VERIFIED_FINITE_DIRECT_DNA_DECODE','function':'p125_row4','cases':444,'candidate':candidate,'reference':parent,
        'source_hashes':{e['name']:e['hashes']for e in(entry,reference)},'harness_sha256':hashlib.sha256(source.read_bytes()).hexdigest(),
        'scope':'Direct changed helper called on all28 public inputs plus26 boundary sizes times8 modes times2 seeds; bypasses classifier for this diagnostic. Token changes permitted; no proof or performance claim.'}
    (out/'direct.json').write_text(json.dumps(result,indent=2)+'\n');print(json.dumps(result))

if __name__=='__main__':main()
