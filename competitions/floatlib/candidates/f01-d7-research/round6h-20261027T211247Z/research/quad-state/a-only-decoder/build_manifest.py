from pathlib import Path
from datetime import datetime,timezone
import hashlib,json

HERE=Path(__file__).resolve().parent
sha=lambda p:hashlib.sha256(p.read_bytes()).hexdigest()
files=['DecoderNormalization.lean.inc','history-binding.json','investigation.md']
out={
 'created_utc':datetime.now(timezone.utc).isoformat(),
 'state':'HISTORY_CORRECTED_F84_MEASURED_NORMALIZATION_INTERFACE_NOT_RUN',
 'start_utc':'2026-10-27T22:18:35Z','bound_utc':'2026-10-27T22:33:35Z',
 'shared_deadline_utc':'2026-10-28T03:12:47Z',
 'files':{f:{'sha256':sha(HERE/f),'bytes':(HERE/f).stat().st_size} for f in files},
 'explicit_interface_roots':[
  'Submission.R22ADecoderNormalization.carrier_decode',
  'Submission.R22ADecoderNormalization.array_getD_decode',
  'Submission.R22ADecoderNormalization.replace_four_A',
  'Submission.R22ADecoderNormalization.normalize_A4B2_step'],
 'history_conclusion':'f65component unmeasuredalone, d5e dualdirect negative, laterf84 A-only indexedB2 fullymeasured with noeligiblecall/spill but belowadoption; noAonlynovelty claim.',
 'new_condition':'ExactF8 live-state/callplacement and sameF8 completecost must establish whether changed geometry matters; currentnewF8 source is not bound here.',
 'new_Lean':'NOT_RUN','new_runtime_created':False,'CI':False,'local_Lean':False,
 'actualnewF8mechanism':'UNKNOWN_PENDING_D_SOURCE_AND_SELECTED_CALLER',
 'preserved_quad_proof':'257d0a6863a854b461a8b6f0facdf57919b63555a381788fefdef9684c78331b',
}
(HERE/'manifest.json').write_text(json.dumps(out,indent=2)+'\n',encoding='utf-8')
print(json.dumps(out,indent=2))
