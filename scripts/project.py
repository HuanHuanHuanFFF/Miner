"""Multi-track entrypoint; preserve legacy DEFLATE lookup without moving raw evidence."""
from pathlib import Path
import argparse,json,re,subprocess,sys
from urllib.parse import unquote

ROOT=Path(__file__).resolve().parents[1]

def check():
    import yaml
    failures=[];links=0
    for path in [ROOT/'README.md',ROOT/'AGENTS.md',ROOT/'competitions/floatlib/README.md',ROOT/'competitions/floatlib/docs/track-rules.md',ROOT/'competitions/floatlib/coordination/HANDOFF.md']:
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
        workdir=(doc.get('defaults') or {}).get('run',{}).get('working-directory','.')
        for script in re.findall(r'\b(?:competitions/[a-z0-9-]+/)?scripts/[A-Za-z0-9._/-]+',path.read_text()):
            if not (ROOT/workdir/script).is_file():failures.append(path.name+': missing '+script)
    old=subprocess.run([sys.executable,str(ROOT/'competitions/deflate/scripts/project.py'),'check'],cwd=ROOT/'competitions/deflate')
    if old.returncode:failures.append('DEFLATE local check failed')
    result={'status':'PASS' if not failures else 'FAIL','tracks':['deflate','floatlib'],'manual_workflows':len(workflows),'root_links':links,'failures':failures,'scope':'Local links, syntax, manifests and workflow configuration. No CI or chain operation.'}
    print(json.dumps(result,indent=2,ensure_ascii=False));return 1 if failures else 0

def main():
    if sys.argv[1:]==['check']:return check()
    if sys.argv[1:]==['tracks']:
        print('deflate: competitions/deflate\nfloatlib: competitions/floatlib');return 0
    args=sys.argv[1:]
    if args and args[0]=='deflate':args=args[1:]
    return subprocess.call([sys.executable,str(ROOT/'competitions/deflate/scripts/project.py'),*args],cwd=ROOT/'competitions/deflate')

if __name__=='__main__':raise SystemExit(main())
