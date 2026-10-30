from pathlib import Path
import hashlib,json
from datetime import datetime,timezone
H=Path(__file__).parent;ROOT=Path.cwd();R24=ROOT/'competitions/floatlib/candidates/f01-d7-research/round7h-20261028T203856Z';R26=ROOT/'competitions/torchlean/candidates/r26-1h-20261029T085515Z/research'
(H/'numerics-v1').mkdir(exist_ok=True)
finite=(H/'producer-v1/FiniteWidenContractOnly.lean').read_text(encoding='utf-8')
canonical=finite[finite.index('namespace R2W01c'):finite.index('theorem fields32_toDyadic')]+ '\nend R2W01c\n'
entries={
'Sum3ContractOnly':('import ContractExact\n\n'+(R24/'research/representation/NativeSumEnclosure3.lean.inc').read_text(encoding='utf-8'),['Submission.R24RepresentationSum.round_grid','Submission.R24RepresentationSum.loop_invariant','Submission.R24RepresentationSum.sum_enclosure']),
'RadiusContractOnly':('import ContractExact\n\n'+canonical+'\n'+(R24/'research/rounding-review/RadiusEndpoints-v1.lean.inc').read_text(encoding='utf-8'),['Submission.R24RadiusEndpoints.radius_finite_value','Submission.R24RadiusEndpoints.native_endpoints_finite_real']),
'NativeMulContractOnly':('import ContractExact\n\n'+(R26/'finite-producer/producer-draft/NativeMulSupport.lean.inc').read_text(encoding='utf-8')+'\n'+(R24/'research/rounding-review/NativeMul-v4.lean.inc').read_text(encoding='utf-8'),['Submission.R24NativeMul.native_mul_toModel','Submission.R24NativeMul.native_mul_finite_roundAt','Submission.R24NativeMul.native_mul_exact_from_raw32_values']),
'ExactRawTotalContractOnly':((R26/'key/follow-on/ExactRawTotalContractOnly.lean').read_text(encoding='utf-8'),['Submission.R26ExactRawTotal.finiteSlice_real','Submission.R26ExactRawTotal.slice_eq_scaled_dsum']),
'FiniteDotFinishContractOnly':((R26/'key/follow-on/FiniteDotFinishContractOnly.lean').read_text(encoding='utf-8'),['Submission.R26FiniteDotFinish.dotSpec_eq_finishWord_nonzero']),
'ContractWordCore':((R26/'key/follow-on/ContractWordCore.lean').read_text(encoding='utf-8'),['Submission.R25ContractWordBridge.native_dyadic_word','Submission.R25ContractWordBridge.finishWord_of_native_result'])}
rows=[]
for n,(s,roots) in entries.items():
 p=H/'numerics-v1'/(n+'.lean');p.write_text(s,encoding='utf-8',newline='\n');b=p.read_bytes();rows.append(dict(name=n,path=p.relative_to(ROOT).as_posix(),bytes=len(b),sha256=hashlib.sha256(b).hexdigest(),helper_roots=roots,depends_on=[],purpose='standalone actual producer numerical primitive' if n in ['Sum3ContractOnly','RadiusContractOnly','NativeMulContractOnly'] else 'official total/finisher interface'))
r=dict(request_id='R27-FP-003',updated_at_utc=datetime.now(timezone.utc).isoformat(),state='PREPARED_NOT_QUEUED_AWAIT_FP001_FEEDBACK',candidates=rows,purpose='Factor numerical producer and official total interfaces out of105KB old closure. No runtime rewrite or new gamma analysis; SUM3 reused unchanged. Exact independent small imports can compile without failed widening or checker prefix.',allowed_axioms=['propext','Classical.choice','Quot.sound'],allow_private=False,measurement=False,local_Lean=False,resources={'compile_seconds_per_source':180,'memory_mib':4096},verification='NOT_RUN',decision='D may select after initial compile feedback; not a request to expand concurrentCI or skip core fixes')
(H/'CI-REQUEST-003.json').write_text(json.dumps(r,ensure_ascii=False,indent=2)+'\n',encoding='utf-8')
with (H/'HANDOFF.md').open('a',encoding='utf-8') as f:f.write('\n数值库已从旧105KB分成6个独立小源：SUM3（原round_grid/loop不变）、Radius、NativeMul及官方raw sum/finisher接口，`CI-REQUEST-003.json`仅PREPARED_NOT_QUEUED，先等首组反馈；可供后续同runner诊断，避免failed-prefix遮住后部错误。\n')
print(json.dumps(rows,ensure_ascii=False,indent=2))
