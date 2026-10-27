"""Read-only syntax/component/import checks. Does not execute the collection stage."""
from pathlib import Path
from datetime import datetime,timezone
import ast,base64,hashlib,importlib.util,json

H=Path(__file__).resolve().parent
R=next(p for p in H.parents if(p/'competitions/floatlib/pins.json').is_file())
sha=lambda p:hashlib.sha256(p.read_bytes()).hexdigest()
hook=H.parent/'development-route-audit.py'
candidate=R/'competitions/floatlib/candidates/f01-r19-dev-route-profile1'
manifest=json.loads((candidate/'manifest.json').read_text())
assert sha(candidate/'Kernel.lean')==manifest['candidate_sha256']=='622d8394a7127e93dcaf992c62c6dfcff7208d212738409a5e34525dfafd1a58'
assert sha(hook)==manifest['helper_audit_module_sha256']
assert manifest['validation_mode']=='statement-only'and manifest['diagnostic_only']is True
components={}
for row in manifest['components']:
    p=(R/row['path']).resolve();assert p.is_relative_to(H.resolve())
    assert p.stat().st_size==row['bytes']and sha(p)==row['sha256'];components[p.name]=row
    assert b'\r\n'not in p.read_bytes(),'runtime components must use canonical LF'
for p in (hook,H/'driver.py',H/'legacy-whole-parser.py',H/'package-builder.py'):
    ast.parse(p.read_text())
tree=ast.parse((H/'driver.py').read_text())
save=next(n for n in ast.walk(tree)if isinstance(n,ast.FunctionDef)and n.name=='save')
constants=[n.value for n in ast.walk(save)if isinstance(n,ast.Constant)]
assert '\n'in constants and '\\n'not in constants,'JSON receipt newline must be real newline'
spec=importlib.util.spec_from_file_location('r19_route_hook_validation_only',hook)
m=importlib.util.module_from_spec(spec);spec.loader.exec_module(m)
class FakeGate:pass
stages=m.stages(FakeGate(),candidate/'Kernel.lean',H/'not-executed-output',manifest)
assert [name for name,_ in stages]==['route-collection']
rejected=0
for mode in ('hash','missing','request','mode'):
    bad=json.loads(json.dumps(manifest))
    if mode=='hash':bad['components'][0]['sha256']='0'*64
    elif mode=='missing':bad['components']=bad['components'][:-1]
    elif mode=='request':bad['route_profile_request_sha256']='0'*64
    else:bad['validation_mode']='full-gate'
    try:m.stages(FakeGate(),candidate/'Kernel.lean',H/'not-executed-output',bad)
    except AssertionError:rejected+=1
assert rejected==4
assert not any(isinstance(n,ast.Call)and isinstance(n.func,ast.Attribute)and n.func.attr in ('kernel','axioms','score')for n in ast.walk(ast.parse(hook.read_text())))
request=json.loads((H/'request.json').read_text());original=json.loads((H/'request-original-240.json').read_text())
assert request['maximum_module_seconds']==60 and original['maximum_module_seconds']==240
assert sha(H/'request-original-240.json')==request['original_request_sha256']
for p in request['plans']:assert sha(H/p['path'])==p['sha256']
provenance=json.loads((H/'parser-provenance.json').read_text())
assert provenance['git_blob']=='abc3d912dac66d1b2970ba1a7e5288a3d51446a4'
assert sha(H/'legacy-whole-parser.py')==provenance['sha256']==request['parser']['sha256']
cap_expr=next(n.value for n in ast.walk(ast.parse(hook.read_text()))if isinstance(n,ast.Assign)and any(isinstance(t,ast.Name)and t.id=='cap'for t in n.targets))
cap_code=compile(ast.Expression(cap_expr),'<cap-check>','eval')
caps={age:eval(cap_code,{'min':min,'age':age})for age in (0,40,70,100,112,119)}
assert caps=={0:60.0,40:60.0,70:42.0,100:12.0,112:0.0,119:-7.0}
receipt=json.loads((H/'package-receipt.json').read_text())
old=H.parent/'development-workers/structural-cost/route-profile'
assert all(sha(old/name)==value for name,value in receipt['source_worker_files_unchanged'].items())
assert base64.b64decode(receipt['original_request_bytes_base64'])==(old/'request.json').read_bytes()
result=dict(at_utc=datetime.now(timezone.utc).isoformat(),state='PACKAGE_SYNTAX_COMPONENTS_AND_STAGE_INTERFACE_PASS',
            kernel_sha256=sha(candidate/'Kernel.lean'),manifest_sha256=sha(candidate/'manifest.json'),hook_sha256=sha(hook),
            components=len(components),stages=[name for name,_ in stages],cap_cases=caps,negative_manifest_checks=rejected,
            parser_git_blob=provenance['git_blob'],source_worker_unchanged=True,
            runtime='NOT_RUN: no stage callback, Lean, benchmark, Git mutation, CI or original execution-file edit')
(H/'validation-receipt.json').write_text(json.dumps(result,indent=2)+'\n',newline='\n')
print(json.dumps(result,indent=2))
