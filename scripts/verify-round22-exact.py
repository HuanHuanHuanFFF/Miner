"""Frozen R22 source/proof pair through the unmodified original public verifier."""
from pathlib import Path
import hashlib,json,os,re,shutil,subprocess,sys

ROOT=Path(__file__).resolve().parents[1]
def sha(p):return hashlib.sha256(p.read_bytes()).hexdigest()

def validate(label):
    assert re.fullmatch(r'gate-[a-z0-9-]{1,42}',label)
    spec=json.loads((ROOT/'evidence/round22'/(label+'.json')).read_bytes())
    assert spec['r22_mode']=='gate'
    source=(ROOT/spec['path']).resolve();assert source.is_relative_to((ROOT/'candidates').resolve())
    assert source.name==spec['candidate'] and set(spec['files'])=={'parse.rs','Parse.lean'}
    assert all(0<(source/f).stat().st_size<=524288 and sha(source/f)==h for f,h in spec['files'].items())
    assert isinstance(spec['expected_public_output_bytes'],int) and spec['expected_public_output_bytes']>0
    return spec

def main():
    spec=validate(os.environ['ROUND4_SPEC']);source=ROOT/spec['path']
    if '--preflight'in sys.argv:
        print('R22_EXACT_PAIR_PREFLIGHT',spec['candidate'],spec['files']);return
    assert os.environ.get('GITHUB_ACTIONS')=='true' and os.environ.get('RUNNER_OS')=='Linux'
    root=Path(os.environ['DEFLATE_ROOT']);out=Path(os.environ['RUNNER_TEMP'])/'round4-receipts/exact-gate';out.mkdir(parents=True);inp=out/'input';inp.mkdir()
    for f in spec['files']:shutil.copyfile(source/f,inp/f)
    receipt={'run_id':os.environ['GITHUB_RUN_ID'],'git_sha':os.environ['GITHUB_SHA'],'spec':spec,'paired_performance_blocks':0,'status':'GATE_RUNNING'}
    def save():(out/'gate-receipt.json').write_text(json.dumps(receipt,indent=2)+'\n')
    save();timed_out=False
    cmd=[str(root/'.venv/bin/python'),'validator/verifier/verify.py',str(inp),'--results',str(out/'gate.json'),'--keep','always']
    try:
        p=subprocess.run(cmd,cwd=root,capture_output=True,text=True,timeout=2100);log=p.stdout+p.stderr;code=p.returncode
    except subprocess.TimeoutExpired as e:
        def text(v):return v.decode(errors='replace')if isinstance(v,bytes)else(v or'')
        log=text(e.stdout)+text(e.stderr);code=124;timed_out=True
    (out/'gate.log').write_text(log);print(log,flush=True)
    verdict=json.loads((out/'gate.json').read_bytes())if(out/'gate.json').exists()else{'accepted':False,'origin':'No official JSON produced'}
    match=re.search(r'^workspace: (.+)$',log,re.M)
    if match:
        ws=Path(match[1].strip()).resolve();assert ws.parent==(root/'data/verification-workspace').resolve()
        for dirname,paths in [('extracted',[ws/'lean/Slot'/f for f in ('Types.lean','Constants.lean','Funs.lean')]),('logs',sorted((ws/'logs').glob('*.log')))]:
            dest=out/dirname;dest.mkdir()
            for p in paths:
                if p.is_file():assert p.stat().st_size<10000000;shutil.copyfile(p,dest/p.name)
    checks={'exit_zero':code==0,'original_verdict_accepted':verdict.get('accepted')is True,'files_match':all(sha(inp/f)==h for f,h in spec['files'].items()),'public_corpus_only':verdict.get('corpora')==['corpus-stage1'],'original_obligation_logged':'LZ77.Obligation slot.parse'in log,'acceptance_logged':'verification accepted'in log,'expected_output_bytes':((verdict.get('methods')or{}).get('submission')or{}).get('output_bytes')==spec['expected_public_output_bytes']}
    pins=subprocess.run(['git','diff','--exit-code'],cwd=root,capture_output=True,text=True);(out/'upstream-clean.log').write_text(pins.stdout+pins.stderr);checks['official_tree_unchanged']=pins.returncode==0
    accepted=all(checks.values());receipt.update(status='EXACT_ORIGINAL_PUBLIC_GATE_ACCEPTED'if accepted else'EXACT_ORIGINAL_PUBLIC_GATE_TIMEOUT'if timed_out else'EXACT_ORIGINAL_PUBLIC_GATE_REJECTED_OR_INCOMPLETE',exit_code=code,checks=checks,verdict=verdict);save()
    if not accepted:raise SystemExit(code or 1)

if __name__=='__main__':main()
