from pathlib import Path
from datetime import datetime,timezone
import hashlib,json

HERE=Path(__file__).resolve().parent
ROOT=next(p for p in HERE.parents if (p/'AGENTS.md').exists())
EXPOSURE=HERE.parent/'local-nonnan-certificate-exposure.json'
sha=lambda p:hashlib.sha256(p.read_bytes()).hexdigest()
assert sha(HERE/'ColumnRowSummary.lean.inc')=='14e59b3f19fac62d45589ae37039571b746bd767caad972b9f31cf7c4fa85055'
j=json.loads(EXPOSURE.read_text())
files=['ColumnRowSummary.lean.inc','DotImageInterface.lean.inc','column-row-feasibility.md','column-row-counterexamples.json']
out={
 'created_utc':datetime.now(timezone.utc).isoformat(),
 'decision':'PARK_AS_MATH_INTERFACE_RESERVE_NO_NEW_CI_OR_FULL_IMPLEMENTATION',
 'subtask_start_utc':'2026-10-27T21:54:09Z','subtask_bound_utc':'2026-10-27T22:19:09Z',
 'shared_deadline_utc':'2026-10-28T03:12:47Z',
 'files':{f:{'sha256':sha(HERE/f),'bytes':(HERE/f).stat().st_size} for f in files},
 'controller_exposure':{
  'path':str(EXPOSURE.relative_to(ROOT)).replace('\\','/'),'sha256':sha(EXPOSURE),
  'sampled_outputs':sum(r['sampled_outputs'] for r in j['runs']),
  'word_reads':j['word_reads'],'MACs':j['MACs'],
  'runs':[{'seed':r['seed'],'positive_samples':r['certified_native_nan_outputs'],
           'whole_case_share_of_sample_positive_cases':r['whole_case_share_of_sample_positive_cases'],
           'whole_case_share_also_missed_by_global_B_certificate':r['whole_case_share_also_missed_by_global_B_certificate']} for r in j['runs']],
  'limits':'Bounded alreadyseen discovery sample; not full exposure bound, removabletime, private distribution or10percentgain evidence.'},
 'conditional_roots':[
  'Submission.R22ColumnRowSummary.getD_of_ready','Submission.R22ColumnRowSummary.column_read_not_nan',
  'Submission.R22ColumnRowSummary.row_read_not_nan','Submission.R22ColumnRowSummary.column_dot_read_not_nan',
  'Submission.R22DotImage.dotLoop_image_of_reads','Submission.R22DotImage.dot_import_eq_of_reads',
  'Submission.R22DotImage.direct_import_eq_finish'],
 'missing':['prepare_produces_Ready','Aloop_produces_RowMaskReady','exactsource Lean/replay/audit','flags/mask/COW/finish fullcaller cost','publicgate'],
 'old_global_B_sketch':'FusedPreparedB.lean.inc retained, not selected for expansion',
 'status':'NOT_RUN','full_candidate':False,'CI':False,'local_Lean':False,
 'reopen':'Only after underlyingquad/prepared substantialcostsignal and D lowmarginal completecaller experiment',
}
(HERE/'column-row-manifest.json').write_text(json.dumps(out,indent=2)+'\n',encoding='utf-8')
print(json.dumps({k:v for k,v in out.items() if k not in ('conditional_roots',)},indent=2))
