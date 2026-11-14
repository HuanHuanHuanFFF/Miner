from pathlib import Path
import ast,datetime,hashlib,json

HERE=Path(__file__).resolve().parent
ROOT=next(p for p in HERE.parents if (p/'AGENTS.md').is_file())
probes=json.loads((HERE/'probe-plan.json').read_text(encoding='utf-8'))['probes']
checks=[]
for p in probes:
    file=ROOT/p['path']
    digest=hashlib.sha256(file.read_bytes()).hexdigest()
    assert digest==p['sha256'],file
    assert file.stat().st_size==p['bytes'],file
    checks.append({'kind':'probe_identity','file':file.name,'sha256':digest,'ok':True})
for receipt in ('carrier-receipt.json','extended-receipt.json','complete-receipt.json'):
    obj=json.loads((HERE/receipt).read_text(encoding='utf-8'))
    file=HERE/obj.get('file',obj.get('output'))
    digest=hashlib.sha256(file.read_bytes()).hexdigest()
    assert digest==obj['sha256'],receipt
    for name,expected in obj['parts'].items():
        assert hashlib.sha256((HERE/name).read_bytes()).hexdigest()==expected,(receipt,name)
    checks.append({'kind':'assembled_parts','receipt':receipt,'file':file.name,'ok':True})
cost=json.loads((HERE/'cost-probe-receipt.json').read_text(encoding='utf-8'))
assert hashlib.sha256((HERE/cost['main']).read_bytes()).hexdigest()==cost['sha256']
for item in cost['fixtures']:
    assert hashlib.sha256((HERE/item['file']).read_bytes()).hexdigest()==item['sha256']
checks.append({'kind':'cost_sources_and_fixtures','ok':True})
for filename in HERE.glob('*.py'):
    ast.parse(filename.read_text(encoding='utf-8'),filename=str(filename))
checks.append({'kind':'python_parse','count':len(list(HERE.glob('*.py'))),'ok':True})
primary=ROOT/'competitions/floatlib/candidates/f01-d7-research/round7h-20261023T193125Z/astra-Lean-UInt-Lemmas.lean'
assert hashlib.sha256(primary.read_bytes()).hexdigest()=='faf52161e05982b8572e93928f7ec24b86d44d0d40c20fbf8d64cd2fd6c536b7'
checks.append({'kind':'primary_UInt_API_source','pin':'293d5d0c0c3f3dded4688b3ccd6a33939ac5102b','ok':True})
manifest=[]
for file in sorted(HERE.iterdir()):
    if file.is_file() and file.name not in ('delivery-audit.json','delivery-receipt.json','status.json','HANDOFF.md'):
        manifest.append({'file':file.name,'bytes':file.stat().st_size,'sha256':hashlib.sha256(file.read_bytes()).hexdigest()})
record={'at_utc':datetime.datetime.now(datetime.timezone.utc).isoformat(),
        'status':'SOURCE_IDENTITY_AND_LIGHTWEIGHT_CHECKS_PASS_NOT_LEAN_ACCEPTANCE',
        'checks':checks,'manifest':manifest,
        'missing':['All Lean compiler outputs','Kernel/axiom replay','Generated C','Native timings','All12 integration gate','Official submission'],
        'resource':'No local Lean/native compile, no own CI, no Git/index mutation, no direct messages'}
(HERE/'delivery-audit.json').write_text(json.dumps(record,indent=2)+'\n',encoding='utf-8')
print(json.dumps({'checks':len(checks),'files':len(manifest),'bytes':sum(x['bytes'] for x in manifest),'status':record['status']},indent=2))
