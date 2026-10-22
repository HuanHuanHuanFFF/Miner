"""Compose two independently verified components; new exact source still needs full gates."""
from pathlib import Path
import hashlib,json,re

root=Path(__file__).resolve().parents[1]
native=root/'f01-r7-nonnan-runtime/Kernel.lean'
direct=root/'f01-d7-direct-small/Kernel.lean'
a=native.read_bytes();b=direct.read_bytes()
assert hashlib.sha256(a).hexdigest()=='c76056882d69a1122da44b4bc0bb3ab5274251826f0677af2aec5771926d7435'
assert hashlib.sha256(b).hexdigest()=='d9a808479dd6a7c7da345ce680773105b638cc6c9e8145e34d10f59751411fb3'
s=a.decode('utf-8');pos=s.rindex('def bmm (')
s=s[:pos]+re.sub(r'\bbmm\b','bmmPackedBase',s[pos:]).replace('bmm_spec','bmmPackedBase_spec')
addition=b.decode('utf-8');addition=addition[addition.index('\n\nnamespace Submission.DirectSmall\n'):]
s+=addition;raw=s.encode('utf-8')
out=root/'f01-d7-direct-nonnan';out.mkdir(exist_ok=True);(out/'Kernel.lean').write_bytes(raw)
m={'candidate':out.name,'candidate_file':'Kernel.lean','candidate_sha256':hashlib.sha256(raw).hexdigest(),'candidate_bytes':len(raw),'validation_mode':'full-gate','proof_status':'NOT_RUN','parents':{'nonNaN_runtime':{'candidate':'f01-r7-nonnan-runtime','sha256':hashlib.sha256(a).hexdigest(),'full_gate_run':39836787411},'direct_small':{'candidate':'f01-d7-direct-small','sha256':hashlib.sha256(b).hexdigest(),'full_gate_runs':[39833363659,39835885059]}},'mechanism':'Keep the exact complete non-NaN sum/dot/packed-finish implementation, compose the same verified shape-only direct-small dispatcher and proof. NativeFinal.dot on the direct branch now also accepts infinity. No scalar semantics or loop order changes.','expected_gain':'UNKNOWN for composition; measure actual combined source against both components and8eb, never add standalone gains','formal_submission':'NOT_SUBMITTED'}
(out/'manifest.json').write_text(json.dumps(m,indent=2)+'\n','utf-8')
assert raw[:pos]==a[:pos] and len(raw)<256000
print(json.dumps({'candidate':out.name,'sha256':m['candidate_sha256'],'bytes':len(raw),'prefix_unchanged_bytes':pos}))
