from pathlib import Path
import datetime, hashlib, json

out=Path(__file__).resolve().parent
parent=out.parent/'f01-d10-bmm-inline-address/Kernel.lean'
raw=parent.read_bytes()
assert hashlib.sha256(raw).hexdigest()=='be325a846eca196fbce0a24c13e70d4780dd8f2334bfc6f9df5373ef6009547c'
assert not (out/'Kernel.lean').exists(), 'Do not overwrite frozen source'
s=raw.decode()
start=s.index('namespace Submission.DirectSmall')
end=s.index('end Submission.DirectSmall',start)
old=s[start:end]
needle='  dsimp only\n  rw [NativeFinal.dot_eq]'
assert old.count(needle)==1
new=old.replace(needle,'  rw [NativeFinal.dot_eq]')
result=(s[:start]+new+s[end:]).encode()
assert len(result)<=256000
(out/'Kernel.lean').write_bytes(result)
m={'candidate':out.name,'candidate_file':'Kernel.lean','candidate_sha256':hashlib.sha256(result).hexdigest(),'candidate_bytes':len(result),
   'parent':parent.parent.name,'parent_sha256':hashlib.sha256(raw).hexdigest(),'created_at_utc':datetime.datetime.now(datetime.timezone.utc).isoformat(),
   'repair':'Remove only DirectSmall.core_eq_reference dsimp made-no-progress instruction after prior simp already normalized lets. Runtime byte-identical to be325; original failed source/log preserved.',
   'failure_run':39996233409,'failure_seed':849,'failure_line':6085,
   'validation_mode':'full-gate','proof_status':'NOT_RUN_EXACT_REPAIR','performance':'UNKNOWN','formal_submission':'NOT_SUBMITTED'}
(out/'manifest.json').write_bytes((json.dumps(m,indent=2)+'\n').encode())
print(json.dumps(m))
