"""Combine the two substantive runtime mechanisms without obsolete cross-row code."""
from pathlib import Path
from datetime import datetime, timezone
import hashlib
import json

OUT = Path(__file__).resolve().parent
ROOT = OUT.parents[4]
C = ROOT / 'competitions/floatlib/candidates'
parent = C / 'f01-r14-dev-integer-exponent1/Kernel.lean'
raw = parent.read_bytes()
assert hashlib.sha256(raw).hexdigest() == '6f8808d0a6ea0c05e0ba2416a583e5ce388fa75f2ce62b04c408d2699b048dc3'
text = raw.decode()
scalar_end = text.index('def referenceBmm ')
scalar_prefix = text[:scalar_end]
start = text.index('namespace Submission.R11CrossRows\n')
end = text.index('end Submission.R11CrossRows\n', start) + len('end Submission.R11CrossRows\n')
removed = text[start:end].encode()
component = (OUT / 'development-thin-bcache.lean').read_bytes()
thin_manifest = json.loads((C / 'f01-r14-dev-thin-bcache1/manifest.json').read_bytes())
assert thin_manifest['candidate_sha256'] == 'ef5dcd969ac532093103e719d50157631e4fb79dbd5966b54bbf4f8e2e3a8f80'
assert hashlib.sha256(component).hexdigest() == thin_manifest['fragment_sha256']
# This parent has no n1-prepared namespace. Keep its ordinary direct fallback,
# and apply the same B reuse mechanism while preserving that exact fact.
slim = component.decode().replace('R13N1Prepared.dispatch_spec', 'bmmBeforeR11Cross_spec').replace('R13N1Prepared.dispatch', 'bmmBeforeR11Cross')
assert 'R13N1Prepared' not in slim
slim_path = OUT / 'development-thin-bcache-slim.lean'
assert not slim_path.exists()
slim_path.write_bytes(slim.encode())
text = text[:start] + slim + text[end:]
guard = '  if n ≤ 4 ∧ 2 < p then DirectContinuous.core batch m n p A B'
assert text.count(guard) == 1
text = text.replace(guard, '  if (n ≤ 4 ∧ 2 < p) ∨ p ≤ 8 then DirectContinuous.core batch m n p A B')
begin = text.index('def bmmBeforeUnderflowZero ')
finish = text.index('\nend Submission', begin)
old_dispatch = text[begin:finish].encode()
dispatch = '''def bmmBeforeUnderflowZero (batch m n p : Nat) (A : Vector Binary32 (batch*m*n))
    (B : Vector Binary32 (batch*n*p)) : Vector Binary32 (batch*m*p) :=
  R14ThinBCache.dispatch batch m n p A B

theorem bmmBeforeUnderflowZero_spec : ∀ (batch m n p : Nat) (A : Vector Binary32 (batch*m*n))
    (B : Vector Binary32 (batch*n*p)),
    (bmmBeforeUnderflowZero batch m n p A B).get = bmmSpec batch m n p A.get B.get := by
  intro batch m n p A B
  exact R14ThinBCache.dispatch_spec batch m n p A B
'''
text = text[:begin] + dispatch + text[finish:]
assert 'R11CrossRows' not in text and 'R13N1Prepared' not in text
assert text[:text.index('def referenceBmm ')] == scalar_prefix
result = text.encode()
assert len(result) <= 256000
folder = C / 'f01-r14-dev-combined-slim1'
assert not folder.exists()
folder.mkdir()
(folder / 'Kernel.lean').write_bytes(result)
record = dict(candidate=folder.name, candidate_file='Kernel.lean', candidate_sha256=hashlib.sha256(result).hexdigest(),
              candidate_bytes=len(result), created_at_utc=datetime.now(timezone.utc).isoformat(), validation_mode='full-gate',
              proof_status='COMPLETE_SOURCE_PROOF_ATTEMPT_NOT_COMPILED', performance='NOT_RUN',
              parent='f01-r14-dev-integer-exponent1', parent_sha256=hashlib.sha256(raw).hexdigest(),
              fragment=slim_path.relative_to(ROOT).as_posix(), fragment_sha256=hashlib.sha256(slim.encode()).hexdigest(),
              removed_namespace=dict(name='Submission.R11CrossRows', bytes=len(removed), sha256=hashlib.sha256(removed).hexdigest()),
              old_dispatch_sha256=hashlib.sha256(old_dispatch).hexdigest(),
              mechanism='Pure UInt64 normal-domain mul plus one-time native B preparation for m>=4,n>1,p1/p2; p<=8 uses existing DirectContinuous instead of packed10. All p2 cross-row paths, including tiny row counts, now go through exact direct/cache paths. Obsolete cross-row code removed to create proof/source headroom. No R13 n1 A cache is added.',
              source_attribution='DeepSeek69901745 p<=8 direct-route evidence informs the shape-only route; no performance/admission inherited. The B-preparation and scalar integer source are developer R14 components; original FloatLib/MIT attribution retained.',
              integration='Entire scalar prefix through referenceBmm definition boundary is byte-identical to6f8808d0. New B loop/order/default/replay proof is the same as thin-bcache1 except its existing fallback is the parent bmmBeforeR11Cross, since this parent never had R13N1Prepared. Public final underflow-zero fast path remains unchanged.',
              limits='This combined source is a genuinely new runtime, including the tiny-p2 dispatch change. It needs its own clean full discovery and frozen independent confirmations, not a product of component gains or a fresh name for failed6990 discovery.',
              bytes_remaining=256000 - len(result))
(folder / 'manifest.json').write_bytes((json.dumps(record, ensure_ascii=False, indent=2) + '\n').encode())
(OUT / 'development-combined-slim-build.json').write_bytes((json.dumps(record, ensure_ascii=False, indent=2) + '\n').encode())
print(json.dumps({key: record[key] for key in ('candidate', 'candidate_sha256', 'candidate_bytes', 'bytes_remaining', 'proof_status', 'performance')}))
