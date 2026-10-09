"""R13 lightweight native diagnostic within the renewed seven-hour window."""
from pathlib import Path
import hashlib,importlib.util,json,os,subprocess,sys
from round4 import ROOT,validate

def main():
    assert os.environ.get('GITHUB_ACTIONS')=='true'and os.environ.get('RUNNER_OS')=='Linux'
    spec=validate(os.environ['ROUND4_SPEC']);out=Path(os.environ['RUNNER_TEMP'])/'round4-receipts';out.mkdir(exist_ok=True)
    if spec.get('r18_range_counts'):
        subprocess.run([sys.executable,str(ROOT/'scripts/research-round18-ranges.py')],check=True);return
    if spec.get('r16_transfer_candidates'):
        subprocess.run([sys.executable,str(ROOT/'scripts/research-round16-transfer.py')],check=True);return
    if spec.get('pc_rescue_counts'):
        loader=importlib.util.spec_from_file_location('r13_rescue',ROOT/'scripts/research-round13-rescue.py')
        module=importlib.util.module_from_spec(loader);loader.loader.exec_module(module);module.main();return
    if spec.get('pc_expired_counts'):
        loader=importlib.util.spec_from_file_location('r13_expired',ROOT/'scripts/research-round13-expired.py')
        module=importlib.util.module_from_spec(loader);loader.loader.exec_module(module);module.main();return
    if spec.get('native_encoder'):
        loader=importlib.util.spec_from_file_location('r13_native_encoder',ROOT/'scripts/research-round13-encoder-native.py')
        module=importlib.util.module_from_spec(loader);loader.loader.exec_module(module);module.main();return
    record={'run_id':os.environ['GITHUB_RUN_ID'],'git_sha':os.environ['GITHUB_SHA'],'batch':os.environ['ROUND4_SPEC'],
        'status':'STARTED_NATIVE_ONLY','candidate_hashes':{e['name']:e['hashes']for e in spec['entries']if not e['control']},
        'scope':'R13 native token/decode diagnostic only. Official extraction, paired two axes, full gate and ranking NOT_RUN.'}
    dest=out/'native-only.json';dest.write_text(json.dumps(record,indent=2)+'\n')
    result=subprocess.run([sys.executable,str(ROOT/'scripts/research-round4.py')],check=False)
    eq=json.loads((out/'equivalence-research.json').read_bytes())if(out/'equivalence-research.json').exists()else{}
    record.update(status='VERIFIED_FINITE_NATIVE_ONLY'if result.returncode==0 and eq.get('returncode')==0 and eq.get('cases') and all(r['cases']==444 and r['different_or_failed']==0 for r in eq['cases'])else'FAILED_OR_INCOMPLETE_NATIVE_ONLY',equivalence=eq)
    dest.write_text(json.dumps(record,indent=2)+'\n');print(json.dumps(record))
    if spec.get('ef32_key4_counts'):
        loader=importlib.util.spec_from_file_location('r13_key4_probe',ROOT/'scripts/research-round13-key4.py')
        module=importlib.util.module_from_spec(loader);loader.loader.exec_module(module);module.main()
    assert record['status']=='VERIFIED_FINITE_NATIVE_ONLY'

if __name__=='__main__':main()
