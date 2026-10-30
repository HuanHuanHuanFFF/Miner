from pathlib import Path
import hashlib,json
from datetime import datetime,timezone
H=Path(__file__).parent;ROOT=Path.cwd()
p=H/'boundary-v1/GuardedBoundaryContractOnly.lean';s=(H/'boundary-v1/ActualBoundaryContractOnly.lean').read_text(encoding='utf-8')+'\n'+(H/'boundary-v1/GuardedEndpoints.lean.inc').read_text(encoding='utf-8-sig');p.write_text(s,encoding='utf-8',newline='\n');b=p.read_bytes()
r=dict(at_utc=datetime.now(timezone.utc).isoformat(),state='SOURCE_READY_AFTER_KEYCORE',path=p.relative_to(ROOT).as_posix(),sha256=hashlib.sha256(b).hexdigest(),bytes=len(b),helper_roots=['Submission.R27GuardedEndpoints.accepted_endpoint_equations','Submission.R27GuardedEndpoints.actual_acceptance_contains_exact_of_error'],new_reduction='No endpoint real identities supplied by producer; derived from actual certify finite guards and pinned native add/sub semantics. Producer only supplies finite actual radius and abs(nativeValue(sum)-exactRawSum)<=nativeValue(radius).',proof='NOT_RUN',performance='UNKNOWN',formal_submission=False)
(H/'boundary-v1/guarded-receipt.json').write_text(json.dumps(r,ensure_ascii=False,indent=2)+'\n',encoding='utf-8')
with (H/'HANDOFF.md').open('a',encoding='utf-8') as f:f.write('\n20:08新实质归约：`boundary-v1/GuardedBoundaryContractOnly.lean`从实际certify的finite(sum/两端)guard推导native ±的RNE等式，最终只要求实际radius finite和forward-error；可删除旧producer endpoint magnitude路线。根/sha见guarded-receipt，仍NOT_RUN，不替换缺失producer证明。\n')
print(json.dumps(r,ensure_ascii=False,indent=2))
