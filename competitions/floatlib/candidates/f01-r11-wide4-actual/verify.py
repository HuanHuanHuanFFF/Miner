from pathlib import Path
import hashlib, importlib.util, json
here=Path(__file__).resolve().parent
cs=here.parent
manifest=json.loads((here/'manifest.json').read_text(encoding='utf-8'))
data=(here/'Kernel.lean').read_bytes()
sha=lambda b:hashlib.sha256(b).hexdigest()
assert sha(data)==manifest['candidate_sha256']
assert len(data)==manifest['candidate_bytes'] and len(data)<=256000
base=(cs/'f01-d11-bmm-wide-backbone/Kernel.lean').read_bytes()
assert sha(base)==manifest['parent_sha256']
suffix=base[base.index(b'/-- Both short-circuiting scans'):]
assert data.endswith(suffix) and sha(suffix)==manifest['outer_underflow_suffix_sha256']
spec=importlib.util.spec_from_file_location('p',cs/'f01-r11-crossrow-p2-pack12-proof2/build.py')
p=importlib.util.module_from_spec(spec);spec.loader.exec_module(p);p.static_check(data.decode())
print(json.dumps({'static':'PASS','bytes':len(data),'sha256':sha(data),'outer_guard_identity':True,'Lean':'NOT_RUN'}))
