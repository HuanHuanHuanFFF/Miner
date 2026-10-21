from pathlib import Path
import ast,datetime,hashlib,json
HERE=Path(__file__).resolve().parent
ROOT=HERE.parents[3]

def sha(p):return hashlib.sha256(p.read_bytes()).hexdigest()

checks=[]
for p in sorted(HERE.glob('*.py')):
 ast.parse(p.read_text(encoding='utf8'),filename=str(p))
 checks.append({'kind':'python_parse','file':p.name,'sha256':sha(p)})
for p in sorted((ROOT/'competitions/floatlib/candidates').glob('f01-r1-*/manifest.json')):
 m=json.loads(p.read_text(encoding='utf8'))
 k=p.parent/'Kernel.lean'
 assert sha(k)==m['candidate_sha256'],p
 assert 0<k.stat().st_size<=256000,p
 assert [l for l in k.read_text(encoding='utf8').splitlines() if l.startswith('import ')]==['import ContractTensor'],p
 checks.append({'kind':'frozen_candidate_bytes','candidate':p.parent.name,'sha256':sha(k),'bytes':k.stat().st_size})
state=json.loads((HERE/'research-status.json').read_text(encoding='utf-8-sig'))
for h in state['handoffs']:
 p=ROOT/h['path']
 assert p.exists() and sha(p)==h['sha256'],h['id']
 checks.append({'kind':'handoff_identity','id':h['id'],'sha256':sha(p)})
for name in ['source-receipts.json','native-source-receipts.json','mul-source-receipts.json']:
 r=json.loads((HERE/name).read_text(encoding='utf8'))
 for item in r['sources']:
  p=ROOT/item['file']
  assert sha(p)==item['sha256'] and p.stat().st_size==item['bytes'],p
  checks.append({'kind':'source_payload','file':item['file'],'sha256':sha(p)})
r=json.loads((HERE/'newer-mul-source-receipt.json').read_text(encoding='utf8'))
p=HERE/'sources/Newer-Arithmetic-LeanModel-MulDiv.lean'
assert sha(p)==r['sha256'] and p.stat().st_size==r['bytes']
checks.append({'kind':'source_payload','file':p.name,'sha256':sha(p)})
out={'checked_at_utc':datetime.datetime.now(datetime.timezone.utc).isoformat(),'passed':True,
 'scope':'Local syntax and artifact-identity checks, not Lean or performance acceptance','checks':checks}
(HERE/'bundle-audit.json').write_text(json.dumps(out,indent=2)+'\n',encoding='utf8')
print(json.dumps({'passed':True,'checks':len(checks),'candidates':[c for c in checks if c['kind']=='frozen_candidate_bytes']},indent=2))
