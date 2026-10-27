from pathlib import Path
from datetime import datetime,timezone
import hashlib,json,re
H=Path(__file__).resolve().parent;R=H.parents[3];W=H/'web/R7-W12c/original-extracted/R7-W12c'
inc=(W/'R7W12cIncrement.lean').read_bytes();merged=(W/'Kernel.lean').read_bytes();old=(R/'competitions/floatlib/candidates/f01-d7-direct-nonnan/Kernel.lean').read_bytes()
assert hashlib.sha256(old).hexdigest()=='60f74aa4af01a9b35ece66a7c310e6b05b5b84b9b7121a4cccd12a0a9c987e15'
assert hashlib.sha256(inc).hexdigest()=='e2e2ce789b087824239d2b6ae52ac6f8e4620c7d36bb1ea1fc00c0c09b40f218'
assert hashlib.sha256(merged).hexdigest()=='173a091ecfa2d6ae7c3c048459e570cbffed4098d2a5ce70af3d2da6afa5c911'
assert merged[:115608]+merged[115608+12194:]==old
assert inc in merged[115608:115608+12194]
def strip_comments(text):
 result=[];i=0;depth=0
 while i<len(text):
  if text.startswith('/-',i):depth+=1;i+=2
  elif depth and text.startswith('-/',i):depth-=1;i+=2
  elif depth:i+=1
  elif text.startswith('--',i):
   j=text.find('\n',i);i=len(text) if j<0 else j
  else:result.append(text[i]);i+=1
 assert depth==0
 s=''.join(result);assert '"' not in s
 return re.sub(r'\s+','',s)
local=(H/'canonical-image-minimal-block.lean').read_bytes()
same=strip_comments(local.decode())==strip_comments(inc.decode());assert same
cp=H/'canonical-image-minimal-block-compiled.lean'
if cp.exists():assert cp.read_bytes()==inc
else:cp.write_bytes(inc)
audit=json.loads((W/'evidence/final-axiom-audit.json').read_text()) if (W/'evidence/final-axiom-audit.json').exists() else json.loads((W/'logs/final-axiom-audit.json').read_text())
assert audit['status']=='PASS'
out={'checked_at_utc':datetime.now(timezone.utc).isoformat(),'local_minimal_sha256':hashlib.sha256(local).hexdigest(),'compiled_increment_sha256':hashlib.sha256(inc).hexdigest(),'compiled_increment_bytes':len(inc),'compiled_public_merge_sha256':hashlib.sha256(merged).hexdigest(),'compiled_public_merge_bytes':len(merged),'single_insert_restores_exact60f':'PASS','local_vs_web_after_nested_comment_and_whitespace_removal':'IDENTICAL','exact_proof_compile':'WebactualfixedLean complete173a + originalfourfullspecs + 41declaration3axiom auditPASS','downstream_limit':'No exact703BMM or3d9sum compile/fullgate/performance inherited. Same theoremproof tokens remove minimalblock dependency uncertainty only.','file':cp.name}
(H/'canonical-image-compiled-equivalence.json').write_text(json.dumps(out,indent=2)+'\n');print(json.dumps(out,indent=2))
