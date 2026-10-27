import json,hashlib
from pathlib import Path
D=Path(__file__).resolve().parent
root=D.parents[4]
# Exact proved R18 U32-interface prefix; the new public entry remains unchanged in this probe.
base=root/'candidates/f01-r17-dev-u32-roundtrip-repair2/Kernel.lean'
frag=D/'Jam17.lean.inc'
b=base.read_bytes();f=frag.read_bytes()
assert hashlib.sha256(b).hexdigest().startswith('0873268d') and len(b)==238140
probe=b+b'\n'+f
(D/'Probe-jam17-v1.lean').write_bytes(probe)
roots=['or_one','jamNat_eq','rne_jam','jam_bounds','leading_cases','jamWord_nat','jam_roundtrip']
(D/'HelperAudit-jam17.lean.inc').write_text('\n'.join('#print axioms Submission.R19Jam17.'+r for r in roots)+'\n',encoding='utf8')
manifest={'state':'WRITTEN_NOT_RUN','base':{'path':str(base),'bytes':len(b),'sha256':hashlib.sha256(b).hexdigest()},'fragment':{'path':str(frag),'bytes':len(f),'sha256':hashlib.sha256(f).hexdigest()},'probe':{'path':str(D/'Probe-jam17-v1.lean'),'bytes':len(probe),'sha256':hashlib.sha256(probe).hexdigest(),'within256000':len(probe)<=256000},'helper_roots':['Submission.R19Jam17.'+r for r in roots],'diagnostic_caller':'Submission.R19Jam17.diagnosticEntry','public_operations':'unchanged B2 baseline; diagnostic guarded normal MUL is separately named','acceptance_status':{'statement':'NOT_RUN','kernel_replay':'NOT_RUN','helper_axioms':'NOT_RUN','full_gate':'NOT_RUN','public_performance':'NOT_RUN'},'scope':'Minimum arithmetic and numerical-interface check, plus full guarded cost caller; not formal candidate or ranking evidence'}
(D/'probe-manifest.json').write_text(json.dumps(manifest,indent=2)+'\n',encoding='utf8')
print(json.dumps(manifest,indent=2))

