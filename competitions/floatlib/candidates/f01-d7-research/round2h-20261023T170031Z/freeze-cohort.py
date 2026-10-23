"""Freeze final three input roles without generating or inspecting holdout inputs."""
from pathlib import Path
import argparse, datetime, hashlib, importlib.util, json

ap=argparse.ArgumentParser()
ap.add_argument('--candidate',required=True)
ap.add_argument('--discovery',type=int,required=True)
ap.add_argument('--diagnostic-only',action='store_true')
a=ap.parse_args()
out=Path(__file__).resolve().parent
root=out.parents[4]
d7=out.parent
spec=importlib.util.spec_from_file_location('guard',d7/'adoption-guard.py')
g=importlib.util.module_from_spec(spec);spec.loader.exec_module(g)
baseline='f01-r8-combined-result-guard'
p=g.load_run(root,d7,a.discovery,(a.candidate,baseline))
g.require(p['run_conclusion']=='success' and p['job_conclusion']=='success','Complete successful discovery required')
g.require(p['kernel_hashes'][baseline]=='41bce4856c4c921dd67b6115928df16e5e8ed08a55b71f1296d28b77cf9ce9a7','Wrong retained source')
g.require(p['plan']['selection_policy']==g.SELECTION_POLICY,'Discovery policy changed')
for n in (a.candidate,baseline):
    v=p['verdicts'][n]
    g.require(v.get('passed') is True and v.get('stage')=='score' and len(v.get('rounds',[]))==25,'Original full discovery required')
    g.require(v['seed']==p['seed']==p['plan']['seed'],'Discovery seed mismatch')
g.require(not p['codegen_present'] and not p['plan'].get('profile_parent') and not p['plan'].get('profile_current'),'Discovery observers present')
screen=json.loads((out/f'result-{p["seed"]}-{a.candidate}.json').read_bytes())
g.require(screen['run']==a.discovery and screen['sha256']==p['kernel_hashes'][a.candidate] and screen['evidence']==p['evidence'],'Discovery screen identity changed')
if not a.diagnostic_only:
    g.require(screen['local_discovery_screen_passed'] is True,'No qualifying discovery; use explicitly diagnostic-only extra input testing')
used=[]
for path in (root/'competitions/floatlib/candidates/f01-mul-log2-proof1/ci-runs').glob('dispatch-*/dispatch.json'):
    receipt=json.loads(path.read_bytes())
    if receipt.get('state') in ('RUN_IDENTIFIED','DISPATCH_SENT_NO_AUTOMATIC_RETRY'):
        used.append(int(receipt['inputs']['seed']))
g.require(not {842,843}.intersection(used),'Final extra input seed already dispatched')
files=[out/'round-plan.json',out/'prepare-plan.py',out/'verify-three-groups.py',d7/'adoption-guard.py',d7/'public-suite.py',Path(__file__).resolve()]
v=p['verdicts'][baseline]
freeze={'schema_version':1,'candidate':{'name':a.candidate,'sha256':p['kernel_hashes'][a.candidate]},
    'baseline':{'name':baseline,'sha256':p['kernel_hashes'][baseline]},
    'groups':{'D':{'seed':p['seed'],'run':a.discovery,'job':p['job_id']},'A':{'seed':842},'B':{'seed':843}},
    'required_groups':3,'selection_policy':g.SELECTION_POLICY,'suite_sha256':g.SUITE_SHA,'generator_sha256':g.GENERATOR_SHA,
    'reference':{k:v[k] for k in ('incumbent_sha256','champion_sha256')},
    'frozen_at_utc':datetime.datetime.now(datetime.timezone.utc).isoformat(),
    'holdouts_unseen_before_freeze':True,'diagnostic_only':a.diagnostic_only,
    'purpose':'Three distinct original full input groups, all source-bound; every slow/failing group retained. Diagnostic-only mode never authorizes adoption.',
    'discovery_evidence':p['evidence'],'discovery_screen':screen,
    'files':{path.relative_to(root).as_posix():{'sha256':hashlib.sha256(path.read_bytes()).hexdigest()} for path in files}}
path=out/'cohort-freeze.json'
with path.open('x',encoding='utf-8',newline='\n') as stream:stream.write(json.dumps(freeze,ensure_ascii=False,indent=2)+'\n')
sha=hashlib.sha256(path.read_bytes()).hexdigest()
with (out/'cohort-freeze.sha256').open('x',encoding='ascii') as stream:stream.write(sha+'\n')
print(json.dumps({'freeze':path.relative_to(root).as_posix(),'sha256':sha,'diagnostic_only':a.diagnostic_only,'groups':freeze['groups']}))
