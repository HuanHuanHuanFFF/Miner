"""Inventory R26 research bytes for D; never stage, commit, push or delete."""
from pathlib import Path
import datetime
import hashlib
import json
import re
import subprocess

HERE=Path(__file__).resolve().parent
ROOT=next(p for p in HERE.parents if (p/'AGENTS.md').is_file())
OUTPUTS={'public-research-manifest.json','public-research-allowlist.txt'}
PRIVATE=re.compile(r'chatgpt\.com/(?:c/|library)|rollout-[^\s\"<>]*\.jsonl|\.codex[/\\]memories',re.I)


def main():
    found=subprocess.run(['rg','--files',str(HERE)],cwd=ROOT,capture_output=True,text=True)
    assert found.returncode in (0,1),found.stderr
    paths=[Path(line).resolve() for line in found.stdout.splitlines()]
    paths.extend(p.resolve() for p in HERE.rglob('.gitignore') if p.is_file())
    # Ignoring a private original must not erase its local retention record.
    paths.extend(p.resolve() for p in (HERE/'pro-results').rglob('*') if p.is_file())
    for directory in HERE.rglob('source-private'):
        if directory.is_dir():
            paths.extend(p.resolve() for p in directory.rglob('*') if p.is_file())
    full_upstream=HERE/'widen/upstream-source-evidence.json'
    if full_upstream.is_file():paths.append(full_upstream.resolve())
    public=[];local=[]
    for path in sorted(set(paths)):
        rel=path.relative_to(ROOT).as_posix()
        if path.name in OUTPUTS:continue
        if '/pro-results/' in rel or '/source-private/' in rel or path==full_upstream.resolve():
            local.append({'path':rel,'reason':'Private original or full upstream payload retained locally; technical findings/hashes published separately'})
            continue
        data=path.read_bytes()
        try:value=data.decode('utf-8')
        except UnicodeDecodeError:
            local.append({'path':rel,'reason':'Non-text output needs separate review'});continue
        if PRIVATE.search(value):
            local.append({'path':rel,'reason':'Private conversation/source reference excluded'});continue
        public.append({'path':rel,'bytes':len(data),'sha256':hashlib.sha256(data).hexdigest()})
    manifest={'at_utc':datetime.datetime.now(datetime.timezone.utc).isoformat(),
              'owner':'R; D sole Git coordinator','state':'BYTE_INVENTORY_NOT_PUSH_OR_ACCEPTANCE',
              'public_scope':'R26 own research/curated pinned source excerpts/proof drafts/finite models/failures and independent receipts',
              'files':public,'public_bytes':sum(x['bytes'] for x in public),'local_only':local,
              'limits':'Mutable status/indexes require rebuild immediately before D commit. Git blob bytes and remote ref must be independently checked. No Lean or speed acceptance implied.'}
    (HERE/'public-research-manifest.json').write_text(json.dumps(manifest,ensure_ascii=False,indent=2)+'\n',encoding='utf-8',newline='\n')
    listing=[f['path'] for f in public]+[(HERE/n).relative_to(ROOT).as_posix() for n in sorted(OUTPUTS)]
    (HERE/'public-research-allowlist.txt').write_text('\n'.join(listing)+'\n',encoding='utf-8',newline='\n')
    print(json.dumps({'public_paths':len(listing),'public_bytes':manifest['public_bytes'],'local_only':len(local)}))


if __name__=='__main__':main()
