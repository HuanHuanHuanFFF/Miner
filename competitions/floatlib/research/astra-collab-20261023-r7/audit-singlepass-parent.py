from pathlib import Path
from datetime import datetime,timezone
import hashlib,json,re
H=Path(__file__).resolve().parent;C=H.parents[3]/'competitions/floatlib/candidates'
p=C/'f01-r7-sum-singlepass-fused-proof1/Kernel.lean';b=p.read_bytes();parent=(C/'f01-r7-nonfinite-combined-proof2/Kernel.lean').read_bytes()
assert hashlib.sha256(b).hexdigest()=='3d9b1ea94ec105073334b793adcb5a9fecc4eda37dd2a5809e715b5584a54576'
s=b.decode();append='\n\nnamespace Submission\n\nnamespace R7SinglePassSum';assert s.count(append)==1;s=s[:s.index(append)]
a=s.index('end R7NaNProof')+len('end R7NaNProof');z=s.index('end R7SumProof',a)+len('end R7SumProof\n');assert s[a:z].startswith('\n\nsection R7SumProof\n');s=s[:a]+s[z:]
a=s.index('end R7Native')+len('end R7Native');z=s.index('namespace R7NaNReplay',a);s=s[:a]+'\n\n'+s[z:]
s=s.replace('theorem sumBeforeR7SinglePass_spec','theorem sum_spec');s=re.sub(r'\bsumBeforeR7SinglePass\b','sum',s)
assert s.encode()==parent
out={'checked_at_utc':datetime.now(timezone.utc).isoformat(),'candidate':p.parent.name,'candidate_sha256':hashlib.sha256(b).hexdigest(),'parent_sha256':hashlib.sha256(parent).hexdigest(),'remove_new_blocks_undo_legacy_sum_rename_recovers_parent_exact_bytes':'PASS','scope':'All parentdefinitions/proofs/constants preservedbyteforbyte under inverse transformation. Newsumreplacesexported sum; originalscalaradd/mul/BMMdefinitions untouched. This is notgeneratedC/machinecodeidentity orLean/fullgate/performance acceptance.'}
(H/'singlepass-parent-identity.json').write_text(json.dumps(out,indent=2)+'\n');print(json.dumps(out,indent=2))
