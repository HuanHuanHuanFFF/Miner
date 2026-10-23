"""Read-only byte/source checks for the frozen short-shared candidate."""
from pathlib import Path
import hashlib,json,importlib.util
HERE=Path(__file__).resolve().parent
CS=HERE.parent
sha=lambda b:hashlib.sha256(b).hexdigest()
m=json.loads((HERE/'manifest.json').read_text())
r=json.loads((HERE/'source-review.json').read_text())
parent=(CS/'f01-r11-crossrow-p2-pack12-proof2/Kernel.lean').read_bytes()
assert sha(parent)==m['parent_sha256']
text=parent.decode();a=r['changed_original_region']['start'];e=r['changed_original_region']['end']
assert text[a:e]==r['original_region']
expected=(text[:a]+r['new_region']+text[e:]).encode()
actual=(HERE/'Kernel.lean').read_bytes()
assert expected==actual and sha(actual)==m['candidate_sha256'] and len(actual)==m['candidate_bytes']
assert m['candidate_sha256']=='7cad7df494da6004b9e4b202f4d09b838ef8d4b79ba6fe934eea7287784fea28'
assert sha((HERE/'build.py').read_bytes())==m['build_script_sha256']
sp=importlib.util.spec_from_file_location('r11_policy',CS/'f01-r11-crossrow-p2-pack12-proof2/build.py')
checks=importlib.util.module_from_spec(sp);sp.loader.exec_module(checks);checks.static_check(actual.decode())
prefix=text[:a];suffix=text[e:]
assert actual.startswith(prefix.encode()) and actual.endswith(suffix.encode())
print(json.dumps({'source':m['candidate_sha256'],'bytes':len(actual),'parent':sha(parent),'exact_rebuild':'PASS',
                  'runtime_outside_dot8_region':'BYTE_IDENTICAL','static_policy':'PASS','Lean':'NOT_RUN_NEW_VARIANT'}))
