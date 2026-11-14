"""Own-role byte inventory only. D remains the sole Git/publication coordinator."""
from pathlib import Path
import datetime,hashlib,json,re
H=Path(__file__).resolve().parent
ROOT=next(p for p in H.parents if (p/'AGENTS.md').is_file())
OUTPUTS={'PUBLIC-OWNED-MANIFEST.json','PUBLIC-OWNED-ALLOWLIST.txt'}
PRIVATE=re.compile(r'chatgpt\.com/(?:c/|library)|rollout-[^\s\"<>]*\.jsonl|\.codex[/\\]memories',re.I)
rows=[];local=[]
for p in sorted(H.rglob('*')):
 if not p.is_file()or p.name in OUTPUTS or p.suffix=='.tmp':continue
 data=p.read_bytes();rel=p.relative_to(ROOT).as_posix()
 if any(x in {'__pycache__','source-private','private','local-private'}for x in p.relative_to(H).parts):
  local.append({'path':rel,'sha256':hashlib.sha256(data).hexdigest(),'reason':'Private/cache directory'});continue
 try:s=data.decode('utf-8')
 except UnicodeDecodeError:
  local.append({'path':rel,'sha256':hashlib.sha256(data).hexdigest(),'reason':'Non-text output requires ownerreview'});continue
 if PRIVATE.search(s):
  local.append({'path':rel,'sha256':hashlib.sha256(data).hexdigest(),'reason':'Private conversation source reference; retain locally, not default export'});continue
 rows.append({'path':rel,'bytes':len(data),'sha256':hashlib.sha256(data).hexdigest()})
r={'at_utc':datetime.datetime.now(datetime.timezone.utc).isoformat(),'scope':'Thisrole ownsource/proof drafts/exactfinite models/evidence; byteinventory only, not Git commit/push orproof acceptance','public_files':rows,'public_bytes':sum(x['bytes']for x in rows),'local_only':local,'D_owner_action':'Merge with Rrootpublicallowlist; rebuild mutablefiles beforecommit; preserve locally excluded timeaudit originals; no full unknownlicense Kernel/rawprivatechat exported.','accepted_proof_index':'PROOF-COVERAGE.json','original_errors_retained':True}
(H/'PUBLIC-OWNED-MANIFEST.json').write_text(json.dumps(r,ensure_ascii=False,indent=2)+'\n',encoding='utf-8')
(H/'PUBLIC-OWNED-ALLOWLIST.txt').write_text('\n'.join(x['path']for x in rows)+'\n',encoding='utf-8')
print(json.dumps({'public_files':len(rows),'bytes':r['public_bytes'],'local_only':local},ensure_ascii=False,indent=2))
