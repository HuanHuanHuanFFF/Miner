from pathlib import Path
from datetime import datetime,timezone
import json,hashlib
HERE=Path(__file__).resolve().parent
now=datetime.now(timezone.utc).isoformat();r=json.loads((HERE/'gemm27-public23-receipt.json').read_text())
recipe_sha=hashlib.sha256((HERE/'graft_gemm27_public23.py').read_bytes()).hexdigest()
r['recipe_sha256']=recipe_sha
request={'at_utc':now,'reply_to':'PUBLIC23-GEMM27-MIXER-GRAFT.json and MIXER-GRAFT-FALLBACK-CORRECTION.json',
 'priority':'High ROI actual full12-reusable Mixer graft, first exact source delivered23:11:45 before23:12 target',
 'recipe':'development/native/graft_gemm27_public23.py','recipe_sha256':recipe_sha,
 'interface':'build(raw23:bytes,donor27:bytes)->(result:bytes,metadata:dict). transform defaults to ownscope source-private/official-27.lean; runner can supply already-fetched exact donor tobuild directly',
 'source23_sha256':r['base_sha256'],'donor27_sha256':r['donor_sha256'],
 'candidate_sha256':r['candidate_sha256'],'candidate_bytes':r['candidate_bytes'],'free_bytes':r['free_bytes'],
 'dependency':{'path':'development/native/frozen_compact_public23.py','sha256':'4c3dd79284f6701d3b128687f9f973f47d9236f8d9db502d398e2eb4d131e129'},
 'intake_policy':'PASS','proof_state':'ACTUAL_ALL12_DECLARED_NOT_COMPILED',
 'closure':'DonorYos/Yqs/Yoc/Gsn/Gcg/Ya3Q/Xg/Fw/Zg2/Zc0Q,4585B, strong23ZcC reused. CQ resolved from explicit donor rename to Nat.pos_of_mul_pos_right; Cw already same alias in23prelude',
 'fallback':'Original kernels0.dense.2 for k<20/nonfinite, exactly per parent correction; no gemmSpec runtimefallback',
 'actual_binding':'dense second field changed toYa3Q, finalcorrectsimp includesZc0Q; all12 remain actual declarations, new gate stillrequired',
 'request':'Fresh original all12 gate, then complete Mixer paired cost against exact public27 with current36 reportchain; no new arithmetic proofmodule',
 'scope':'Do not alter frozen8. Droot onlyGit/CI, publicrunner allow_private=false. Full source/private donors never publicartifacts',
 'budget':'00:44:43 deadline unchanged, no newlong after00:00'}
(HERE/'CI-REQUEST-16-MIXER-GEMM-GRAFT.json').write_text(json.dumps(request,indent=2)+'\n',encoding='utf-8')
for name in ['READY.json','status.json']:
 d=json.loads((HERE/name).read_text(encoding='utf-8'));d['updated_at_utc']=now
 d['preferred']='CI-REQUEST-16-MIXER-GEMM-GRAFT.json';d['gemm_graft']=request
 d['processed_parent']='PUBLIC23-GEMM27-MIXER-GRAFT/23:00 and fallbackcorrection/23:03; exactsource ready23:11:45'
 (HERE/name).write_text(json.dumps(d,indent=2)+'\n',encoding='utf-8')
t=(HERE/'HANDOFF.md').read_text(encoding='utf-8')
t=t.replace('# R27 native current handoff\n','# R27 native current handoff\n\n**Priority new Mixer graft ready:** request16, `graft_gemm27_public23.py`; **252764B/bbd75849…31835**, policyPASS, actual all12 declared/NOT_COMPILED. Exact source first ready23:11:45. Reuses donor27 Ya3Q proof closure around strong23 YaV/ZcC, resolves donorCQ alias explicitly, keeps kernels0.dense.2 small-k/nonfinite fallback. Complete original gate and Mixer36 comparison required. Build accepts both exact cached source bytes, no extra network. Frozen8 unchanged.\n',1)
(HERE/'HANDOFF.md').write_text(t,encoding='utf-8');print(json.dumps(request,indent=2))
