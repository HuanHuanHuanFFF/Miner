"""Combine exact peer p2 route with already proved continuous n1 row caching."""
from pathlib import Path
from datetime import datetime,timezone
import subprocess,hashlib,json,difflib
OUT=Path(__file__).resolve().parent;ROOT=OUT.parents[4];C=ROOT/'competitions/floatlib/candidates'
sha=lambda b:hashlib.sha256(b).hexdigest()
df=(C/'f01-d12-scalar-combined/Kernel.lean').read_bytes();assert sha(df)=='df5c61a0ca24a8ef18c0c42d83bdd23466872d3fe8f39dd912e9c347b27fb172'
peer_commit=subprocess.check_output(['git','rev-parse','efba4fdc'],cwd=ROOT).decode().strip()
peer_path='competitions/floatlib/candidates/f01-deepseek-p2cont/Kernel.lean'
peer=subprocess.check_output(['git','show',peer_commit+':'+peer_path],cwd=ROOT);assert sha(peer)=='e878b0f2a3558a6c43d01c0af504709c39ba02aaefba6cf772f2633ace8e4732'
old=df.splitlines(keepends=True);new=peer.splitlines(keepends=True)
changes=[]
for tag,i,j,k,l in difflib.SequenceMatcher(a=old,b=new,autojunk=False).get_opcodes():
    if tag=='equal':continue
    assert tag=='replace' and j-i==l-k==1
    assert old[i].lstrip().startswith(b'if ') and new[k].lstrip().startswith(b'if ')
    changes.append((old[i],new[k]))
assert len(changes)==2
base=(C/'f01-r13-n1-prepared-row-output/Kernel.lean').read_bytes();assert sha(base)=='8661a3a5a1988b2d6b3d827aa37a7abeb81c50fffabcc38f8c8476961b425e0c'
result=base
for before,after in changes:
    assert result.count(before)==1;result=result.replace(before,after,1)
needle=b'  if h : n = 1 \xe2\x88\xa7 2 < p then core batch m n p A B h.1'
replacement=b'  if h : n = 1 \xe2\x88\xa7 0 < p then core batch m n p A B h.1'
assert result.count(needle)==1;result=result.replace(needle,replacement,1)
assert len(result)<=256000
target=C/'f01-r14-dev-p2-n1-cache';assert not target.exists();target.mkdir()
(target/'Kernel.lean').write_bytes(result)
meta={'candidate':target.name,'candidate_file':'Kernel.lean','candidate_sha256':sha(result),'candidate_bytes':len(result),'created_at_utc':datetime.now(timezone.utc).isoformat(),
      'parent':'f01-r13-n1-prepared-row-output','parent_sha256':sha(base),'validation_mode':'full-gate','proof_status':'EXISTING_UNCONDITIONAL_BRANCH_PROOFS_NEW_COMBINATION_NOT_RUN',
      'source_attribution':{'peer_role':'DeepSeek free agent','peer_commit':peer_commit,'peer_file':peer_path,'peer_kernel_sha256':sha(peer),'prior_cache_kernel_sha256':sha(base)},
      'mechanism':'Reuse exact two p2cont branch-predicate changes from DeepSeek. Broaden existing R13 n=1 prepared-A continuous-row dispatch from p>2 to p>0, exposing it to newly direct p1/p2 outputs. All actual dot, writer and existing all-shape branch proof bodies unchanged; no p3..8 widening.',
      'historical_difference':'R13 cache was tested only after unchanged Cross and with n1,p>2 (about1.2-1.8% whole exposed coverage). New p2 routing changes which n1 p1/p2 cases reach this established cache path; this is a changed integrated runtime, not a renamed source or inherited performance.',
      'performance':'UNKNOWN; complete costs and actual path exposure require original full gate and fresh paired inputs. No additive component gain claim.',
      'three_literal_changes':[{'old':x.decode().rstrip(),'new':y.decode().rstrip()} for x,y in changes]+[{'old':needle.decode(),'new':replacement.decode()}]}
(target/'manifest.json').write_bytes((json.dumps(meta,ensure_ascii=False,indent=2)+'\n').encode())
(OUT/'development-p2-n1-cache-build.json').write_bytes((json.dumps(meta,ensure_ascii=False,indent=2)+'\n').encode());print(json.dumps(meta,ensure_ascii=False))
