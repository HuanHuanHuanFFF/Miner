"""Proof-only follow-up: immutable DNA Rust, original verifier, no new paired experiment."""
from pathlib import Path
import hashlib,json,os,re,shutil,subprocess,sys
ROOT=Path(__file__).resolve().parents[1]
RUST='805c03a521b44b665aef3113cb4d6f823924032fec164524163aa0c756002542'
def sha(p):return hashlib.sha256(p.read_bytes()).hexdigest()
def main():
    label=os.environ['ROUND17_SPEC'];assert re.fullmatch(r'gate-proof[1-9][0-9]?',label)
    spec=json.loads((ROOT/'evidence/round17'/(label+'.json')).read_bytes());source=(ROOT/spec['path']).resolve();assert source.is_relative_to((ROOT/'candidates').resolve())
    assert spec['files']['parse.rs']==RUST and set(spec['files'])=={'parse.rs','Parse.lean'}
    assert all(0<(source/f).stat().st_size<=524288 and sha(source/f)==h for f,h in spec['files'].items())
    if '--preflight' in sys.argv:print('EXACT_PAIR_PREFLIGHT',spec['candidate'],spec['files']);return
    assert os.environ.get('GITHUB_ACTIONS')=='true' and os.environ.get('RUNNER_OS')=='Linux'
    root=Path(os.environ['DEFLATE_ROOT']);out=Path(os.environ['RUNNER_TEMP'])/'round17-exact';out.mkdir();inp=out/'input';inp.mkdir()
    for f in spec['files']:shutil.copyfile(source/f,inp/f)
    receipt={'run_id':os.environ['GITHUB_RUN_ID'],'git_sha':os.environ['GITHUB_SHA'],'spec':spec,'paired_performance_blocks':0,'status':'GATE_RUNNING'}
    def save():(out/'gate-receipt.json').write_text(json.dumps(receipt,indent=2)+'\n')
    save()
    p=subprocess.run([str(root/'.venv/bin/python'),'validator/verifier/verify.py',str(inp),'--results',str(out/'gate.json'),'--keep','always'],cwd=root,capture_output=True,text=True,timeout=2100)
    log=p.stdout+p.stderr;(out/'gate.log').write_text(log);print(log,flush=True)
    verdict=json.loads((out/'gate.json').read_bytes()) if (out/'gate.json').exists() else {'accepted':False,'origin':'No official JSON produced'}
    match=re.search(r'^workspace: (.+)$',log,re.M)
    if match:
        workspace=Path(match[1].strip()).resolve();assert workspace.parent==(root/'data/verification-workspace').resolve();dest=out/'extracted';dest.mkdir()
        for f in ('Types.lean','Constants.lean','Funs.lean'):
            path=workspace/'lean/Slot'/f
            if path.is_file():assert path.stat().st_size<10000000;shutil.copyfile(path,dest/f)
        logs=out/'logs';logs.mkdir()
        for path in sorted((workspace/'logs').glob('*.log')):
            assert path.stat().st_size<10000000
            shutil.copyfile(path,logs/path.name)
    receipt.update(status='EXACT_ORIGINAL_PUBLIC_GATE_ACCEPTED' if verdict.get('accepted') else 'EXACT_ORIGINAL_PUBLIC_GATE_REJECTED',exit_code=p.returncode,verdict=verdict);save()
    assert all(sha(inp/f)==h for f,h in spec['files'].items())
    if verdict.get('accepted'):
        assert verdict['corpora']==['corpus-stage1'] and 'LZ77.Obligation slot.parse' in log and 'verification accepted' in log
        assert verdict['methods']['submission']['output_bytes']==spec['expected_public_output_bytes']
    subprocess.run(['git','diff','--exit-code'],cwd=root,check=True)
    if p.returncode or not verdict.get('accepted'):raise SystemExit(p.returncode or 1)
if __name__=='__main__':main()
