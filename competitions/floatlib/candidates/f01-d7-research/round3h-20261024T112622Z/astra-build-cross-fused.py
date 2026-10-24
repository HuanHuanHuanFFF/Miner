"""Exact df5c integration; no proof pruning, decoder change, or old-source edit."""
from pathlib import Path
from datetime import datetime,timezone
import hashlib,json
HERE=Path(__file__).resolve().parent
CS=HERE.parent.parent
PARENT=CS/'f01-d12-scalar-combined/Kernel.lean'
DEST=CS/'f01-r13-cross-fused-output'
sha=lambda b:hashlib.sha256(b).hexdigest()
raw=PARENT.read_bytes();expected='df5c61a0ca24a8ef18c0c42d83bdd23466872d3fe8f39dd912e9c347b27fb172'
assert sha(raw)==expected and b'\r' not in raw
increment=(HERE/'astra-cross-fused.lean').read_bytes();assert b'\r' not in increment
s=raw.decode();marker='namespace Submission\nopen FloatLib.Floats Competition\n\ndef bmmBeforeUnderflowZero'
edits=[
 ('new_fused_writer_and_prefix_proofs',marker,increment.decode()+'\n'+marker),
 ('replace_only_existing_Cross_dispatch_arm','    R11CrossRows.core batch m n p A B h.2.2.2.1 (Nat.le_of_eq h.1)',
  '    R13CrossFused.core batch m n p A B h.2.2.2.1 h.1'),
 ('bridge_same_original_bmm_obligation','    · rw [R11CrossRows.core_eq_rows, DirectRows.core_eq, DirectSmall.core_eq_reference]',
  '    · rw [R13CrossFused.core_eq_reference]')]
# The actual split branch is indented two spaces in this exact parent.
edits[-1]=(edits[-1][0],edits[-1][1][2:],edits[-1][2][2:])
for name,old,new in edits:
    assert s.count(old)==1,(name,s.count(old))
    s=s.replace(old,new,1)
result=s.encode();assert len(result)<=256000
inverse=s
for name,old,new in reversed(edits):
    assert inverse.count(new)==1,(name,inverse.count(new));inverse=inverse.replace(new,old,1)
assert inverse.encode()==raw
DEST.mkdir(exist_ok=True)
file=DEST/'Kernel.lean'
if file.exists():assert file.read_bytes()==result,'Use a new candidate for any repair.'
else:file.write_bytes(result)
manifest=dict(candidate=DEST.name,candidate_file='Kernel.lean',candidate_sha256=sha(result),candidate_bytes=len(result),
    parent='f01-d12-scalar-combined',parent_sha256=expected,parent_bytes=len(raw),
    created_at_utc=datetime.now(timezone.utc).isoformat(),official_commit='4b7e83841cc0c32c6529f533923c73d33b5ecf97',
    lean_toolchain='leanprover/lean4:v4.34.0',floatlib_commit='0d91825727839f597fd06b22fdd038ea21480f0c',
    mechanism='Only existing p=2 Cross dispatch: compute original blockRows once per group and emit W8 fields directly into final preallocated Array; no all-groups Vector W8 or output index reconstruction. Keep original P12 pack, ordered F8 loop, finish8 and NaN replay.',
    unchanged='Every original byte, comment and attribution is preserved except two dispatcher/spec hooks.708 not included. No width, decoder, guard, threshold, proof-prune or official-file change.',
    proof_chain='Original blockRows_word -> original RowStream.point_row -> two-push prefix -> each valid local row -> unrolled four-row block -> group fold invariant min(4*g,rows)*p -> prefix_vector_eq_ofFn -> original points_eq_reference -> same bmm_spec.',
    tail='Explicit per-row bounds before each pair. Retain original padded block computation but emit only valid rows, in row-major0..7 order. Output size proved for p=2; original dispatcher proof supplies it.',
    representation='W8 itself remains; existing finish8 may reuse F8 storage. Only the array retaining all W8 groups and its second traversal are intended to disappear, not a claimed extra W8 allocation.',
    first_falsifier='Original statement/full gate on exact source; actual new BMM caller must reach the fused step, not R11CrossRows.words/old core. Verify final Array is incrementally reused and not copied per append, no read callback or Word8 vector reintroduced. Whole clean comparison versusdf5c determines value.',
    proof_status='NOT_RUN_FIRST_COMPLETE_INTEGRATION',full_gate='NOT_RUN',codegen='NOT_RUN',performance='UNKNOWN',formal_submission='NOT_SUBMITTED',
    increment_sha256=sha(increment),increment_bytes=len(increment),inverse_reconstruction_sha256=sha(inverse.encode()),
    edit_ledger=[dict(name=n,old=o,new=v) for n,o,v in edits],
    authorization='D selected Cross output fusion at R13 natural checkpoint; human3h continuation in round-plan.json. D owns Git/CI/adoption; R only candidate and astra files.',
    source_budget_remaining=256000-len(result))
(DEST/'manifest.json').write_text(json.dumps(manifest,ensure_ascii=False,indent=2)+'\n',encoding='utf-8',newline='\n')
print(json.dumps({k:manifest[k] for k in ['candidate','candidate_sha256','candidate_bytes','source_budget_remaining','proof_status']},indent=2))
