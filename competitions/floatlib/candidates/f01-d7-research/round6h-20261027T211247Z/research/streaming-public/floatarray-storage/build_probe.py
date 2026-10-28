"""Byte composition only: original B2 public roots stay unchanged."""
from pathlib import Path
from datetime import datetime,timezone
import json,hashlib
HERE=Path(__file__).resolve().parent
ROOT=next(p for p in HERE.parents if (p/'competitions/floatlib/pins.json').is_file())
RESEARCH=HERE.parents[1]
paths=[ROOT/'competitions/floatlib/candidates/f01-r15-dev-packed-b2-1/Kernel.lean',
 HERE.parent/'PairEmitSizeOnly.lean.inc',
 RESEARCH/'floatarray-bridge-review/NativeTarget.lean.inc',HERE/'Runtime.lean.inc']
blocks=[p.read_bytes() for p in paths]
sha=lambda b:hashlib.sha256(b).hexdigest()
assert sha(blocks[0])=='622d8394a7127e93dcaf992c62c6dfcff7208d212738409a5e34525dfafd1a58'
assert sha(blocks[2])=='fb7d71540db5b0fee7ae9a9b73440b10224713ebd646c4cd812d145c4dfbc1b1'
combined=b'\n'.join(blocks)
assert combined[:len(blocks[0])]==blocks[0] and len(combined)<256000
assert not any(x in blocks[-1] for x in [b'partial ',b'unsafe ',b'sorry',b'axiom '])
(HERE/'Kernel-probe.lean').write_bytes(combined)
proofs=['Submission.R21StreamingPair.emit_size']+[
 'Submission.R22FloatArrayBridgeReview.'+n for n in ['checked_import','checked_native','checked_convert']]+[
 'Submission.R22FloatArrayB2.'+n for n in ['push_size','group_size','row_size','output_size']]
manifest=dict(created_at_utc=datetime.now(timezone.utc).isoformat(),
 phase_start_utc='2026-10-28T01:10:02Z',phase_limit_utc='2026-10-28T01:30:02Z',
 shared_deadline_utc='2026-10-28T03:12:47Z',
 source=dict(path='Kernel-probe.lean',bytes=len(combined),sha256=sha(combined)),
 fragments=[dict(path=str(p.relative_to(ROOT)),bytes=len(b),sha256=sha(b)) for p,b in zip(paths,blocks)],
 public_roots_unchanged=['Submission.add_spec','Submission.mul_spec','Submission.sum_spec','Submission.bmm_spec'],
 new_helper_proofs=proofs,callback='Submission.R22FloatArrayB2.guarded',
 callback_correctness='NOT_PROVED; original public bmm_spec still describes B2 only',
 validation='NOT_RUN',native_cost='UNKNOWN',actual_codegen='UNKNOWN',CI=False,
 semantic_choices=['Exact existing underflow-zero branch; eligible p2..8,n>1,m>=4 only',
 'Single checked build, no Array Float intermediate, no .data runtime access',
 'Native-target bit check from fb7d; failure invokes original full B2 on raw A/B',
 'Old odd right read including next row/batch/default is preserved',
 'Safe Nat get with erased 2*k and2*k+1 bounds; no USize or unrolling',
 'RawA codec, two Float32 chains, old finish/NaN replay and writer ordering unchanged'],
 missing=['Pinned compiler typing including size proofs','Producer native Prefix/read agreement and loop/public refinement',
 'Actual selected C/ASM and exact full-call cost/checksum','Gate/replay/audit for any later public source'])
(HERE/'runtime-manifest.json').write_text(json.dumps(manifest,ensure_ascii=False,indent=2)+'\n',encoding='utf-8')
print(json.dumps(dict(source=manifest['source'],runtime=manifest['fragments'][-1],helper_proofs=len(proofs),validation='NOT_RUN'),ensure_ascii=False))
