"""Multi-track entrypoint; preserve legacy DEFLATE lookup without moving raw evidence."""
from pathlib import Path
import argparse,hashlib,json,re,subprocess,sys
from urllib.parse import unquote

ROOT=Path(__file__).resolve().parents[1]

def check():
    import yaml
    failures=[];links=0
    markdown=[ROOT/'README.md',ROOT/'AGENTS.md',ROOT/'competitions/floatlib/README.md',*(ROOT/'competitions/floatlib/docs').glob('*.md'),*(ROOT/'competitions/floatlib/coordination').glob('*.md'),ROOT/'competitions/torchlean/README.md',*(ROOT/'competitions/torchlean/docs').glob('*.md')]
    for path in markdown:
        for match in re.finditer(r'\]\(([^)\n]+)\)',path.read_text(encoding='utf-8')):
            value=unquote(match[1].strip('<>').split('#')[0]);links+=1
            if not value or re.match(r'[a-z][a-z0-9+.-]*:',value,re.I):continue
            if not (path.parent/value).exists():failures.append(f'{path.relative_to(ROOT)}: {value}')
    workflows=list((ROOT/'.github/workflows').glob('*.yml'))
    for path in workflows:
        doc=yaml.safe_load(path.read_text(encoding='utf-8'));events=doc.get('on',doc.get(True))
        if set(events or {})!={'workflow_dispatch'}:failures.append(path.name+': nonmanual trigger')
        if doc.get('concurrency',{}).get('cancel-in-progress') is not False:failures.append(path.name+': cancellation enabled')
        if events['workflow_dispatch']['inputs']['allow_private'].get('default') is not False:failures.append(path.name+': private runner default')
        base=(doc.get('defaults') or {}).get('run',{}).get('working-directory','.')
        for job in doc.get('jobs',{}).values():
            workdir=(job.get('defaults') or {}).get('run',{}).get('working-directory',base)
            for step in job.get('steps',[]):
                for script in re.findall(r'\b(?:competitions/[a-z0-9-]+/)?scripts/[A-Za-z0-9._/-]+',step.get('run','')):
                    if not (ROOT/workdir/script).is_file():failures.append(path.name+': missing '+script)
    candidates=0
    for manifest in (ROOT/'competitions/floatlib/candidates').glob('*/manifest.json'):
        data=json.loads(manifest.read_text(encoding='utf-8'));kernel=manifest.parent/'Kernel.lean'
        if not kernel.is_file() or hashlib.sha256(kernel.read_bytes()).hexdigest()!=data.get('candidate_sha256'):failures.append(str(manifest.parent.relative_to(ROOT))+': Kernel digest mismatch')
        candidates+=1
    torchlean_candidates=0
    torchlean_remote_recipes=0
    for plan in (ROOT/'competitions/torchlean/candidates').glob('*/ci-plan.json'):
        data=json.loads(plan.read_bytes())
        for entry in data['candidates']:
            path=ROOT/entry['path']
            if 'fetch' in entry:
                # These sources are intentionally not redistributed. This is metadata validation;
                # the runner must fetch, reconstruct and verify the exact output bytes before use.
                pin=entry['fetch']; recipe=ROOT/entry.get('patch_script','')
                valid=(re.fullmatch(r'https://conjectures\.io/v1/competitions/torchlean/submissions/[1-9][0-9]*/source',pin.get('url',''))
                       and re.fullmatch(r'[0-9a-f]{64}',pin.get('sha256',''))
                       and re.fullmatch(r'[0-9a-f]{64}',entry.get('sha256',''))
                       and type(entry.get('bytes')) is int and 0<entry['bytes']<=256000
                       and recipe.is_file() and recipe.resolve().is_relative_to(ROOT.resolve())
                       and hashlib.sha256(recipe.read_bytes()).hexdigest()==entry.get('patch_script_sha256'))
                if not valid:failures.append('TorchLean remote recipe metadata: '+entry['name'])
                torchlean_remote_recipes+=1
            elif not path.is_file() or hashlib.sha256(path.read_bytes()).hexdigest()!=entry['sha256']:failures.append('TorchLean candidate digest: '+entry['name'])
            torchlean_candidates+=1
    old=subprocess.run([sys.executable,str(ROOT/'competitions/deflate/scripts/project.py'),'check'],cwd=ROOT/'competitions/deflate')
    if old.returncode:failures.append('DEFLATE local check failed')
    result={'status':'PASS' if not failures else 'FAIL','tracks':['deflate','floatlib','torchlean'],'manual_workflows':len(workflows),'root_links':links,'floatlib_candidates':candidates,'torchlean_candidates':torchlean_candidates,'torchlean_remote_recipe_metadata_only':torchlean_remote_recipes,'failures':failures,'scope':'Local links, syntax, manifests and workflow configuration. Remote recipe metadata does not verify fetched or reconstructed output bytes. No CI or chain operation.'}
    print(json.dumps(result,indent=2,ensure_ascii=False));return 1 if failures else 0

def main():
    if sys.argv[1:]==['check']:return check()
    if sys.argv[1:]==['tracks']:
        print('deflate: competitions/deflate\nfloatlib: competitions/floatlib\ntorchlean: competitions/torchlean');return 0
    args=sys.argv[1:]
    if args and args[0]=='deflate':args=args[1:]
    return subprocess.call([sys.executable,str(ROOT/'competitions/deflate/scripts/project.py'),*args],cwd=ROOT/'competitions/deflate')

if __name__=='__main__':raise SystemExit(main())
