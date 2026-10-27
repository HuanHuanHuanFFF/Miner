from pathlib import Path
from datetime import datetime,timezone
import hashlib,json,re
ROOT=Path(__file__).resolve().parents[4];HERE=Path(__file__).resolve().parent
parent='f01-r7-nonnan-runtime';p=ROOT/'competitions/floatlib/candidates'/parent/'Kernel.lean';b=p.read_bytes();assert hashlib.sha256(b).hexdigest()=='c76056882d69a1122da44b4bc0bb3ab5274251826f0677af2aec5771926d7435'
nan=(ROOT/'competitions/floatlib/candidates/f01-r7-nan-replay-fullpath/Kernel.lean').read_bytes();assert hashlib.sha256(nan).hexdigest()=='9a2a05cd8e033d3cc079744ade77dd42464926d04ef5c9a8e7c050a1605ec854'
ns=nan.decode();a=ns.index('section R7NaNProof');z=ns.index('end R7NaNProof',a)+len('end R7NaNProof');baseproof=ns[a:z]
w3=HERE/'web/R7-W03/original-extracted/R7-W03/R7W03Append.lean';w3b=w3.read_bytes();assert hashlib.sha256(w3b).hexdigest()=='e911256f40e00d44a1fa9b9facde2fd0d9e4ea56c8ee3a086f56ec551d57bfc9'
addproof=w3b.decode().split('/-- The same all-input property stated directly on the complete runtime word.')[0]+'\nend R7W03\n'
assert addproof.count('R7W02.exec_toModel_add')==1
addproof=addproof.replace('R7W02.exec_toModel_add','Submission.R7Native.toModelExecAdd')
w5=HERE/'web/R7-W05/original-extracted/R7-W05/R7W05Append.lean';w5b=w5.read_bytes();assert hashlib.sha256(w5b).hexdigest()=='1834ecafc62a464f54805befdc9b60e2a3e54b1f8102fb0bf47f854c94f6ad6e';w5s=w5b.decode();a=w5s.index('namespace R7W05\n');z=w5s.index('/-- The precise first-event boundary:',a);core=w5s[a:z]+'\nend R7W05\n'
mapping={'R7W05Public.Submission.':'Submission.','R7W05Cached.R7W01.':'R7W01.','R7W05Cached.R7W03.':'Submission.R7W03.'}
for old,new in mapping.items():core=core.replace(old,new)
assert 'R7W05Cached.' not in core and 'R7W05Public.' not in core
addproof=re.sub(r'\bimport\b','dependency',addproof);core=re.sub(r'\bimport\b','dependency',core)
(HERE/'add-nonsignaling-block.lean').write_text(addproof);(HERE/'canonical-native-block.lean').write_text(core)
s=b.decode();s=s.replace('import ContractTensor\n','import ContractTensor\n\n'+baseproof+'\n',1);assert s.count('end R7Native')==1;s=s.replace('end R7Native','end R7Native\n\n'+addproof+'\n'+core)
out=s.encode();d=ROOT/'competitions/floatlib/candidates/f01-r7-canonical-bridge-probe';d.mkdir(exist_ok=False);(d/'Kernel.lean').write_bytes(out)
m={'candidate':d.name,'candidate_file':'Kernel.lean','candidate_sha256':hashlib.sha256(out).hexdigest(),'candidate_bytes':len(out),'parent':parent,'parent_sha256':hashlib.sha256(b).hexdigest(),'created_at_utc':datetime.now(timezone.utc).isoformat(),'proof_status':'NOT_RUN_NAMESPACE_INTEGRATION','validation_mode':'statement-only','mechanism':'Add concrete all-input canonical native add/mul, exact NaNclassification and repaired-event quietness bridges to already fullPASS c760. Runtime kernels unchanged, no dependency on failed b169 or new prefix source.','proof_derivation':{'base_quiet_proofs':'Exact already fullPASS9a2 global proofsection','W03_append_sha256':hashlib.sha256(w3b).hexdigest(),'W05_append_sha256':hashlib.sha256(w5b).hexdigest(),'new_declaration_mapping':mapping,'W03_codec_bridge':'Use actual already accepted Submission.R7Native.toModelExecAdd instead of identical webcachedR7W02 codec lemma','retained_scope':'Through repairSumStep_isQNaN and repairDotStep_isQNaN; no unused listfold/contract adapters or duplicatecached proofs'},'expected_gain':'NONE_CLAIMED: statement mathematical bridge probe only. Later runtime changes need their own fullgate and complete timing.','formal_submission':'NOT_SUBMITTED'}
(d/'manifest.json').write_text(json.dumps(m,indent=2)+'\n');print(json.dumps(m,indent=2))
