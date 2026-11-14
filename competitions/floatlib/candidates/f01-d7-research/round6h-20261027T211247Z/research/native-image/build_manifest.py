from pathlib import Path
from datetime import datetime,timezone
import hashlib,json

HERE=Path(__file__).resolve().parent
ROOT=next(p for p in HERE.parents if (p/'AGENTS.md').exists())
sha=lambda p:hashlib.sha256(p.read_bytes()).hexdigest()
sources=[
 'competitions/floatlib/candidates/f01-r21-dev-streaming-pair-probe2/Kernel.lean',
 'competitions/floatlib/candidates/f01-d7-canonical-dot-scan/Kernel.lean',
 'competitions/floatlib/candidates/f01-r14-dev-row-nan-lazy/Kernel.lean',
 'competitions/floatlib/candidates/f01-r9-bmm-native-event-replay-proof2/Kernel.lean',
 'competitions/floatlib/candidates/f01-d7-research/bmm-scan-sharing-screen.md',
 'competitions/floatlib/candidates/f01-d7-research/round6h-20261027T211247Z/development-cost2/PreparedQuad.lean.inc',
]
files=['FusedPreparedB.lean.inc','DotImageInterface.lean.inc','feasibility.md','witnesses.json']
out={
 'created_utc':datetime.now(timezone.utc).isoformat(),
 'state':'DISTINCT_FUSED_SUMMARY_COST_PREMISE_DEFINED_NOT_RUN',
 'subtask_start_utc':'2026-10-27T21:54:09Z','subtask_bound_utc':'2026-10-27T22:19:09Z',
 'shared_deadline_utc':'2026-10-28T03:12:47Z',
 'files':{f:{'sha256':sha(HERE/f),'bytes':(HERE/f).stat().st_size} for f in files},
 'inspected_sources':{f:{'sha256':sha(ROOT/f),'bytes':(ROOT/f).stat().st_size} for f in sources},
 'old_math':'T19/W12 exact native-image closure already in currentB2; not re-proved.',
 'new_cost_question':'Fuse a globalB nonNaN Bool with already-required preparation, and oneA Bool per4row group at shared loads; select direct finish at group boundary.',
 'explicit_interface_roots':[
  'Submission.R22FusedPreparedB.getD_of_ready','Submission.R22FusedPreparedB.safe_getD_of_ready',
  'Submission.R22FusedPreparedB.native_getD_not_nan','Submission.R22FusedPreparedB.stored_value_import_eq_raw',
  'Submission.R22DotImage.dotLoop_image_of_reads','Submission.R22DotImage.dot_import_eq_of_reads',
  'Submission.R22DotImage.direct_import_eq_finish'],
 'missing':['prepare_spec for actualprototype','actualA-group flag producer and getD hypothesis','newexactsource Lean/replay/audit','actualcompletecaller cost','publicgate/confirmation'],
 'new_Lean':'NOT_RUN','new_performance':'UNKNOWN','candidate_assembled':False,'CI':False,
 'frozen_quad_unchanged':True,
}
(HERE/'manifest.json').write_text(json.dumps(out,indent=2)+'\n',encoding='utf-8')
print(json.dumps({k:v for k,v in out.items() if k not in ('inspected_sources','explicit_interface_roots')},indent=2))
