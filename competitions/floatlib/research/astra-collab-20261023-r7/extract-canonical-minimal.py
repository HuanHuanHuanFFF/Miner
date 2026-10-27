from pathlib import Path
import hashlib,json,re
from datetime import datetime,timezone
H=Path(__file__).resolve().parent
w=H/'web/R7-W12/original-extracted/R7-W12'
full=(w/'R7W12.lean').read_bytes();assert hashlib.sha256(full).hexdigest()=='6baa0a8007e85c24633d540a9f6687ddd5da1381da8aa93b1a29d166345fc288'
text=full.decode().replace('\r\n','\n')
a=text.index('namespace R7W05\n');base=text[a:]
prefix=base[:base.index('/-- Every actual carrier whose raw model is NaN') ] if '/-- Every actual carrier whose raw model is NaN' in base else base[:base.index('theorem toFloat32_eq_nan_of_model_nan')]
# End the first slice at its next documentation comment, leaving only three declarations.
last=prefix.rfind('/--')
if prefix[last:].count('theorem ')==0:prefix=prefix[:last]
def theorem_group(first,stop):
 s=base[base.index(first):base.index(stop)]
 j=s.rfind('/--')
 if j>=0 and s[j:].count('theorem ')==0:s=s[:j]
 return s.rstrip()+'\n'
nativeadd=theorem_group('theorem native_add_nan_left','theorem add_toFloat32')
nativemul=theorem_group('private theorem mul_unpack_of_isNaN','theorem mul_toFloat32_of_not_nan')
w5=prefix.rstrip()+'\n\n'+nativeadd+'\n'+nativemul+'\nend R7W05\n'
inc=(w/'R7W12Increment.lean').read_text()
w12=inc[:inc.index('end R7W12')+len('end R7W12')]
out=w5+'\n\n'+w12+'\n'
out=out.replace('R7W05Public.Submission.','Submission.')
out=re.sub(r'\bimport\b','native constructor',out)
assert 'R7W05Cached' not in out and 'R7W05Public' not in out
assert out.count('namespace R7W05')==1 and out.count('end R7W05')==1
assert out.count('namespace R7W12')==1 and out.count('end R7W12')==1
target=H/'canonical-image-minimal-block.lean';target.write_text(out,encoding='utf-8',newline='\n')
meta={'created_at_utc':datetime.now(timezone.utc).isoformat(),'file':target.name,'bytes':len(target.read_bytes()),'sha256':hashlib.sha256(target.read_bytes()).hexdigest(),'source':'R7W12.lean','source_sha256':hashlib.sha256(full).hexdigest(),'increment_sha256':hashlib.sha256((w/'R7W12Increment.lean').read_bytes()).hexdigest(),'source_web_compile':'PASS exactfull6baa +269declaration3axiom audit','mapped_block_compile':'NOT_RUN','placement':'Inside namespace Submission, after accepted R7Native and NativeBridge declarations. If appending at file end wrap with namespace Submission / end Submission. Do not combine with another R7W05 or R7W12 namespace declaring the same names.','dependencies':['ContractTensor','Submission.R7Native.toModelExecAdd','Submission.NativeBridge.toModelExecMul','Submission.R7Native.ofFloat32Add','Submission.R7Native.ofFloat32Mul'],'retained':'Only necessary W05 actualclassifier/nativeNaN addmul bridges + first W12 namespace through unrestricted add_ofFloat32/mul_ofFloat32. No W01/W02/W03 dependency, no folds orruntimecandidate. Exactnative imported-input closure includes NaNs; arbitraryrawfold still requiresimage condition.','changes':'Select actualsuccessful theorem groups; R7W05Public.Submission to Submission; standalone import word incomments replaced forintake policy. ActualBitVec fieldwidths retained.','D_action':'Use for BMM ownadapter; do not infer complete integratedgate. R owns single-passsum integration.'}
(H/'canonical-image-minimal-block.json').write_text(json.dumps(meta,indent=2)+'\n')
print(json.dumps(meta,indent=2))
