"""Freeze a generic all-pairs caller cost probe, not an official matrix candidate."""
from pathlib import Path
import hashlib,json
HERE=Path(__file__).resolve().parent
ROOT=next(p for p in HERE.parents if (p/'AGENTS.md').is_file())
R24=HERE.parent
sha=lambda p:hashlib.sha256(Path(p).read_bytes()).hexdigest()
parent=ROOT/'competitions/floatlib/candidates/f01-r24-dev-dot-tail-cost1'
assert sha(parent/'Kernel.lean')=='e50bf8769d0bef3cc7883d9c1285fd26439282d7c1fd8c141cb84073f90a7f78'
part=R24/'development-scalar/dot-bank/GenericDotBank.lean.inc'
assert sha(part)=='c76f6b1d7a87ce4c7402f4eae9aa074b2802c8bbefcf174a85fb3d72e7bb7774'
name='f01-r24-dev-dot-bank-cost1';out=ROOT/'competitions/floatlib/candidates'/name;out.mkdir(exist_ok=True)
raw=(parent/'Kernel.lean').read_bytes()+b'\n\n'+part.read_bytes()
p=out/'Kernel.lean'
if p.exists():assert p.read_bytes()==raw
else:p.write_bytes(raw)
source=sha(p)
audit=(R24/'development-dot-cost/audit-stage-tail.py').read_text(encoding='utf-8').replace('e50bf8769d0bef3cc7883d9c1285fd26439282d7c1fd8c141cb84073f90a7f78',source)
audit=audit.replace('Own word64/128 versus certified-proposal research pilot; not a champion comparison','Whole all-pairs bank caller versus own word64/128 control, not official matrix/oldBMM/newtarget/champion')
(HERE/'audit-stage.py').write_text(audit,encoding='utf-8',newline='\n')
m=json.loads((parent/'manifest.json').read_bytes())
components={x['path']:x for x in m['components']}
for p in [part]+[HERE/n for n in ['driver.py','audit-stage.py','parse-results.py','audit-callers.py','R24DotCostMain.lean','R24DotBarrier.lean','fixtures.json']]:
 components[p.relative_to(ROOT).as_posix()]={'path':p.relative_to(ROOT).as_posix(),'bytes':p.stat().st_size,'sha256':sha(p)}
m.update(candidate=name,candidate_sha256=source,candidate_bytes=len(raw),components=list(components.values()),helper_audit_module='audit-stage.py',helper_audit_module_path=(HERE/'audit-stage.py').relative_to(ROOT/'competitions/floatlib/candidates').as_posix(),helper_audit_module_sha256=sha(HERE/'audit-stage.py'),performance='NOT_RUN',scope='Generic exact-round-once all-pairs dot banks; old shipped4 unchanged. Not old per-MAC BMM or adopted new target. Each whole call prepares O(rows+cols) caches, computes all outputs, observes/drops full output inside timing.')
m['runtime_cost'].update(seeds=[24282601,24282603],boundaries=['full'],processes=16,all_148_numeric_dots=False,all_1049_word_round_cases=False,all_464_bank_words=True)
m['parent_runtime_source']={'path':(parent/'Kernel.lean').relative_to(ROOT).as_posix(),'sha256':sha(parent/'Kernel.lean')}
manifest_raw=(json.dumps(m,ensure_ascii=False,indent=2)+'\n').encode()
mp=out/'manifest.json'
if mp.exists():assert mp.read_bytes()==manifest_raw,'Frozen manifest differs; create a new diagnostic version'
else:mp.write_bytes(manifest_raw)
print(json.dumps({'candidate':name,'sha256':source,'bytes':len(raw),'components':len(components),'status':'PREPARED_NOT_RUN'}))
