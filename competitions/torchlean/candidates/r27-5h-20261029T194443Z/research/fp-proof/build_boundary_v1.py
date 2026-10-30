from pathlib import Path
import json,hashlib
from datetime import datetime,timezone
H=Path(__file__).parent;ROOT=Path.cwd();R26=ROOT/'competitions/torchlean/candidates/r26-1h-20261029T085515Z';OLD=R26/'research/key'
K=R26/'development/native/fp-word-conv6-local/Kernel.lean';b=K.read_bytes();assert hashlib.sha256(b).hexdigest()=='ad9bde3e9e8490df15f3d8d15c08805f85d4451e0a5f2d20977632c0b4b22540'
s=b.decode('utf-8-sig').replace('\r\n','\n');start=s.index('@[inline] def finite64 (word : UInt64)');block=s[start:s.index('def sumRemaining',start)]
identity=(ROOT/'competitions/torchlean/candidates/r25-90m-20261029T064916Z/research/order-key/RuntimeIdentity.lean.inc').read_text(encoding='utf-8-sig')
text=(H/'sources-v1/ActualCheckerContractOnly.lean').read_text(encoding='utf-8')+'\nnamespace Submission.R24PortableF64\n'+block+'\nend Submission.R24PortableF64\n'+identity+'\n'+(OLD/'follow-on/RnePullback.lean.inc').read_text(encoding='utf-8-sig')
text+='''
namespace Submission.R27ActualBoundary
open Submission.R25OrderKey Submission.R25Checker
open FloatLib.Floats FloatLib.Floats.Formats.BinaryInterchange

theorem actual_acceptance_contains_exact (s r : Float) (sw : UInt64) (q : UInt32)
    (S R : Real)
    (herr : |nativeValue s - S| ≤ R)
    (hlo : nativeValue (s - r) = Model.roundAt F64 (nativeValue s - R))
    (hhi : nativeValue (s + r) = Model.roundAt F64 (nativeValue s + R))
    (hacc : Submission.R24PortableF64.certify s r sw q = true) :
    value (lowerWord q) < S ∧ S < value (upperWord q) := by
  apply Submission.R26RnePullback.accepted_contains_exact s r sw q S R herr hlo hhi
  simpa only [certify_eq_runtime] using hacc

end Submission.R27ActualBoundary
'''
(H/'boundary-v1').mkdir(exist_ok=True);p=H/'boundary-v1/ActualBoundaryContractOnly.lean';p.write_text(text,encoding='utf-8',newline='\n');out=p.read_bytes()
r=dict(at_utc=datetime.now(timezone.utc).isoformat(),state='PREPARED_AFTER_KEYCORE_PASSES',source_path=p.relative_to(ROOT).as_posix(),source_sha256=hashlib.sha256(out).hexdigest(),bytes=len(out),helper_roots=['Submission.R25OrderKey.raw_value','Submission.R25OrderKey.orderKey_lt_real','Submission.R25Checker.actual_acceptance_bounds','Submission.R27ActualBoundary.actual_acceptance_contains_exact'],runtime_source=K.relative_to(ROOT).as_posix(),runtime_sha256=hashlib.sha256(b).hexdigest(),checker_block_sha256_LF=hashlib.sha256(block.encode()).hexdigest(),boundary='Actual runtime certify -> strict exact target cell, CONDITIONAL on explicit producer error and nearest-endpoint identities. Those producer facts remain separate mandatory obligations; no all12 correct claim.',dependencies='Contains frozen sources-v1/ActualCheckerContractOnly and actualruntime block; RNE pullback reuses pinned roundAt_mono/fixedpoint',proof='NOT_RUN',axioms='NOT_RUN',formal_submission=False)
(H/'boundary-v1/receipt.json').write_text(json.dumps(r,ensure_ascii=False,indent=2)+'\n',encoding='utf-8')
with (H/'HANDOFF.md').open('a',encoding='utf-8') as f:f.write('\n已读D首批40945451009/2da31f12：按exacthash跑旧key-core与prepare-core（与本次源同字节）；其他尚未入队。下一单文件可用 `boundary-v1/ActualBoundaryContractOnly.lean`，把Real/checker/实际runtime恒等/RNE回推合到29KB级，源/根在receipt，不用拼完整producer；前提仍显式保留，NOT_RUN。\n')
print(json.dumps(r,ensure_ascii=False,indent=2))
