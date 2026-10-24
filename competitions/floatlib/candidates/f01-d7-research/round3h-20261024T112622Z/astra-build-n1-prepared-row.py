"""One bounded n1 prepared-row candidate on exactDF; no combination or pruning."""
from pathlib import Path
from datetime import datetime,timezone
import hashlib,json
HERE=Path(__file__).resolve().parent;CS=HERE.parent.parent
PARENT=CS/'f01-d12-scalar-combined/Kernel.lean';DEST=CS/'f01-r13-n1-prepared-row-output'
sha=lambda b:hashlib.sha256(b).hexdigest()
raw=PARENT.read_bytes();expected='df5c61a0ca24a8ef18c0c42d83bdd23466872d3fe8f39dd912e9c347b27fb172'
assert sha(raw)==expected and b'\r' not in raw
increment=(HERE/'astra-n1-prepared-row.lean').read_bytes();assert b'\r' not in increment
s=raw.decode();marker='namespace Submission\nopen FloatLib.Floats Competition\n\ndef bmmBeforeUnderflowZero'
# Apply two old hooks before inserting a namespace that intentionally names the old fallback.
edits=[('replace_Cross_miss_dispatch','  else bmmBeforeR11Cross batch m n p A B',
        '  else R13N1Prepared.dispatch batch m n p A B'),
       ('replace_Cross_miss_proof','  · exact bmmBeforeR11Cross_spec batch m n p A B',
        '  · exact R13N1Prepared.dispatch_spec batch m n p A B'),
       ('insert_prepared_row_and_complete_proof',marker,increment.decode()+'\n'+marker)]
for name,old,new in edits:
    assert s.count(old)==1,(name,s.count(old));s=s.replace(old,new,1)
out=s.encode();assert len(out)<=256000
inverse=s
for name,old,new in reversed(edits):
    assert inverse.count(new)==1,(name,inverse.count(new));inverse=inverse.replace(new,old,1)
assert inverse.encode()==raw
DEST.mkdir(exist_ok=True);file=DEST/'Kernel.lean'
if file.exists():assert file.read_bytes()==out,'Frozen source differs; repair in new candidate.'
else:file.write_bytes(out)
history_path=HERE.parent/'round2h-20261023T170031Z/result-853-f01-d10-bmm-singleton-row-cache.json'
hist=json.loads(history_path.read_bytes())
manifest=dict(candidate=DEST.name,candidate_file='Kernel.lean',candidate_sha256=sha(out),candidate_bytes=len(out),
    parent='f01-d12-scalar-combined',parent_sha256=expected,parent_bytes=len(raw),created_at_utc=datetime.now(timezone.utc).isoformat(),
    official_commit='4b7e83841cc0c32c6529f533923c73d33b5ecf97',lean_toolchain='leanprover/lean4:v4.34.0',floatlib_commit='0d91825727839f597fd06b22fdd038ea21480f0c',
    mechanism='After unchanged outerUnderflow/Cross, only n=1,p>2: prepare one native A scalar per row, pass it to the known column fold, compute exactly+0+fa*fb, keep nonNaN guard and original raw replayEarly1. B reads and final Array writer remain currentDirectContinuous. No Amap,Bpack,F10 or rowVector.',
    mathematical_change='No new floating arithmetic claim: onePreparedDot_eq unfolds original dot/dotLoop at1 after substituting the prepared A value. row_eq/output_eq reuse original DirectContinuous prefix and reference bridge.',
    historical_revisit={'source':'f44802093e149959a4b64c519464f9d445de040b6bc2f760512a70596e2640b8','run':hist['run'],'whole_normalized':hist['relative_normalized_ratio'],'BMM_normalized':hist['per_operation_normalized']['bmm'],'gain_p05':hist['gain_p05'],'receipt_sha256':sha(history_path.read_bytes()),
      'difference':'Oldf448 shared A but materialized per-row Vectors/flatMap and used nativeProduct plus raw seed normalization. Current candidate uses current continuous Array output and original+0-add/resultguard/raw replay; same caching idea in a changed full-call context, not novelty or inherited speed.'},
    current_source_basis='ExactDF DirectContinuous column callback calls NativeFinal.dot/dynamic dotLoop per output; A getD/unbox/of_bits remains inside that dot. Sol actualDF C review independently confirmed source-level absence of rowfa hoist; finalLLVM cycle costs UNKNOWN.',
    preservation='Three reversible edits; all original bytes/comments/attribution otherwise preserved.3c5e/708/252b not included or modified. No n2-4 or width grid, no proof prune.',
    first_falsifier='Originalstatement/full gate and actual reachable new column specialization. fa must be a reusable unboxed Float32 parameter, not per-column closure/Float32 allocation/lean_apply. Check foreign B/output calls and any live-fa spills; complete uninstrumented25-round cost decides, not C counts.',
    proof_status='NOT_RUN_FIRST_COMPLETE_INTEGRATION',full_gate='NOT_RUN',codegen='NOT_RUN',performance='UNKNOWN',formal_submission='NOT_SUBMITTED',
    increment_bytes=len(increment),increment_sha256=sha(increment),inverse_reconstruction_sha256=sha(inverse.encode()),source_budget_remaining=256000-len(out),
    edit_ledger=[dict(name=n,old=o,new=v) for n,o,v in edits],authorization='D explicit bounded n1 GO during human-authorized R13;13:20 hard delivery checkpoint. R has no Git/CI/reset/adoption authority.')
(DEST/'manifest.json').write_text(json.dumps(manifest,ensure_ascii=False,indent=2)+'\n',encoding='utf-8',newline='\n')
print(json.dumps({k:manifest[k] for k in ['candidate','candidate_sha256','candidate_bytes','source_budget_remaining','proof_status']},indent=2))
