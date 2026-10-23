from pathlib import Path
import datetime, hashlib, json

out=Path(__file__).resolve().parent
parent=out.parent/'f01-r8-combined-result-guard/Kernel.lean'
data=parent.read_bytes()
assert hashlib.sha256(data).hexdigest()=='41bce4856c4c921dd67b6115928df16e5e8ed08a55b71f1296d28b77cf9ce9a7'
assert not (out/'Kernel.lean').exists(), 'Do not overwrite frozen candidate'
s=data.decode()
start=s.index('namespace Submission.DirectSmall')
end=s.index('end Submission.DirectSmall',start)
old=s[start:end]
new=old.replace('let (b, i, j) := bmmDecodeC m p q.val','let (b, i, j) := Packed10.inlineDecodeC m p q.val')
new=new.replace('  unfold core referenceBmm\n','  unfold core referenceBmm\n  simp only [Packed10.inlineDecodeC_eq]\n')
assert new!=old and new.count('Packed10.inlineDecodeC')==2
result=(s[:start]+new+s[end:]).encode()
assert len(result)<=256000
(out/'Kernel.lean').write_bytes(result)
m={'candidate':out.name,'candidate_file':'Kernel.lean','candidate_sha256':hashlib.sha256(result).hexdigest(),'candidate_bytes':len(result),
   'parent':parent.parent.name,'parent_sha256':hashlib.sha256(data).hexdigest(),'created_at_utc':datetime.datetime.now(datetime.timezone.utc).isoformat(),
   'mechanism':'DirectSmall uses existing inline Packed10.inlineDecodeC instead of original non-inline bmmDecodeC. The accepted exact equality transports proof. No float, loop, output, dispatch, packed or scalar changes.',
   'hypothesis':'Inlining may avoid per-output tuple allocation and expose shared address arithmetic. Must verify complete end-to-end runtime; no assumed gain.',
   'validation_mode':'full-gate','proof_status':'NOT_RUN','performance':'UNKNOWN','formal_submission':'NOT_SUBMITTED'}
(out/'manifest.json').write_bytes((json.dumps(m,indent=2)+'\n').encode())
print(json.dumps(m))
