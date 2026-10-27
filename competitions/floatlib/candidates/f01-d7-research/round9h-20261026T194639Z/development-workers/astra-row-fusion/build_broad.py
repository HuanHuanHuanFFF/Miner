from pathlib import Path
import re
import json
import hashlib
import difflib
from datetime import datetime, timezone

HERE=Path(__file__).resolve().parent
ROOT=HERE.parents[6]
OUT=HERE/'broad-draft'
OUT.mkdir(exist_ok=True)
parent=(ROOT/'competitions/floatlib/candidates/f01-r19-dev-dual-temporal-a4-5/Kernel.lean').read_bytes()
assert hashlib.sha256(parent).hexdigest()=='c36bc2502904bf946d442de1a4646e09689f016643f09ab0b6788f9bdd375250'
core=(HERE/'repair1/Column4Temporal-repair1.lean.inc').read_bytes()
assert hashlib.sha256(core).hexdigest()=='3d39789d2203d76d94219a00db19d86aec6fc06e49c4088ebb6a6cc9e51fd5f3'
entry=(HERE/'Column4Entry.draft.lean.inc').read_bytes()
assert hashlib.sha256(entry).hexdigest()=='2132424c1580d4a4e106f073292c34439556662401a43a09c5a735700b7760c9'
before='if 3≤p ∧ p≤8 ∧ 1<n ∧ 4≤m ∧ 4*((p+3)/4)=2*((p+1)/2) then core A B'.encode()
after='if 0<m ∧ 1<n ∧ 3≤p ∧ 4*((p+3)/4)=2*((p+1)/2) then core A B'.encode()
assert entry.count(before)==1
broad_entry=entry.replace(before,after)
comment_end=core.index(b'-/')+2
broad_core=b'/- R19 broad draft: repair1 core plus generic entry. NOT_RUN. -/'+core[comment_end:]
assert broad_core[broad_core.index(b'-/')+2:]==core[comment_end:]
matches=list(re.finditer(rb'\r?\nnamespace Submission\r?\nopen FloatLib.Floats Competition\r?\n\r?\ndef bmm ',parent))
assert len(matches)==1, len(matches)
pos=matches[0].start()
prefix=parent[:pos]
old_public=parent[pos:]
old_call=b'R19DualTemporal.dispatch batch m n p A B'
new_call=b'R19Column4Temporal.dispatch (b := batch) (m := m) (n := n) (p := p) A B'
old_proof=b'R19DualTemporal.dispatch_spec batch m n p A B'
new_proof=b'R19Column4Temporal.dispatch_spec (b := batch) (m := m) (n := n) (p := p) A B'
assert old_public.count(old_call)==1 and old_public.count(old_proof)==1
new_public=old_public.replace(old_call,new_call).replace(old_proof,new_proof)
assert new_public.replace(new_call,old_call).replace(new_proof,old_proof)==old_public
source=prefix+b'\n'+broad_core+b'\n'+broad_entry+b'\n'+new_public
assert len(source)<=256000,len(source)
assert prefix+old_public==parent
underflow_body=old_public[old_public.index(b'  if A.toArray.all UnderflowZero.small'):old_public.index(b'  else R19DualTemporal.dispatch')]
assert underflow_body in new_public
assert source.index(b'namespace Submission.R19Column4Temporal')<source.index(b'def bmm (batch m n p')
assert source.rindex(b'end Submission.R19Column4Temporal')<source.index(b'def bmm (batch m n p')
for banned in ['sorry','axiom','unsafe','extern','implemented_by','set_option','import']:
    s=re.sub(rb'/\-.*?\-/',b'',broad_core+broad_entry,flags=re.S)
    assert not re.search(rb'\b'+banned.encode()+rb'\b',s),banned
(OUT/'Kernel-column4-broad.draft.lean').write_bytes(source)
(OUT/'Column4Entry-broad.draft.lean.inc').write_bytes(broad_entry)
for name,a,b,fa,fb in [
    ('from-parent.patch',parent,source,'Kernel-parent-c36bc250.lean','Kernel-column4-broad.draft.lean'),
    ('inverse.patch',source,parent,'Kernel-column4-broad.draft.lean','Kernel-parent-c36bc250.lean')]:
    (OUT/name).write_text(''.join(difflib.unified_diff(a.decode().splitlines(True),b.decode().splitlines(True),fromfile=fa,tofile=fb)),encoding='utf-8',newline='\n')
core_roots=json.loads((HERE/'manifest.json').read_text(encoding='utf-8'))['roots']
entry_roots=['packB_get','finish_select','group_prefix','row_prefix','output_prefix','core_eq_reference','dispatch_spec']
roots=core_roots+['Submission.R19Column4Temporal.'+x for x in entry_roots]+['Submission.'+x+'_spec' for x in ['add','mul','sum','bmm']]
(OUT/'HelperAudit.lean.inc').write_text('\n'.join('#print axioms '+x for x in roots)+'\n',encoding='utf-8')
receipt={
 'at_utc':datetime.now(timezone.utc).isoformat(),'status':'NOT_RUN_BROAD_TYPED_DRAFT_ONLY',
 'source_sha256':hashlib.sha256(source).hexdigest(),'source_bytes':len(source),'remaining_bytes':256000-len(source),
 'parent_sha256':hashlib.sha256(parent).hexdigest(),'parent_bytes':len(parent),
 'core_repair1_sha256':'118d8efc9e8c3d92189913c0aae3d66bca1394a677ec09957174c9d9e97eb1fc',
 'core_runtime_and_proofs_equal_repair1':True,'old_parent_prefix_exact':True,
 'public_change':'Only dispatch call/spec call, both after new namespace declarations; explicit dimensions supplied.',
 'underflow_runtime_guard_and_zero_branch_exact':True,'public_other_bytes_exact':True,
 'new_guard':'m>0 and n>1 and p>=3 and 4*ceil(p/4)=2*ceil(p/2)',
 'fallback':'Original R19DualTemporal.dispatch (c36)',
 'result_tile_cache':False,
 'A4_lifecycle':'Same A4 design as c36 Dual. It is unchanged work only on the old Dual domain; broader prior DirectContinuous/other paths may acquire new A4 preparation, residency and destruction.',
 'B16_packing':'One flat outer cache, one packet vector per batch/group, built once before row fold. Replaces B8 only on former Dual paths; broader fallback comparisons require their actual old B representation and cost.',
 'entry_source_bytes':len(broad_entry),'entry_source_sha256':hashlib.sha256(broad_entry).hexdigest(),
 'roots':roots,'compile':'NOT_RUN','full_gate':'NOT_RUN','generated_C':'NOT_RUN','performance':'UNKNOWN',
 'coordinator_scope_snapshot':{'whole_share':[0.072887,0.059742],
     'required_target_total_reduction_for_whole_3pct':[0.03/0.072887,0.03/0.059742],
     'worker_read_raw_scope_inputs':False,'source':'Parent-provided independent old CI12 scope analysis; not D17.'},
 'D17_or_performance_confirmation_read':False,
}
(OUT/'receipt.json').write_text(json.dumps(receipt,ensure_ascii=False,indent=2)+'\n',encoding='utf-8')
print(json.dumps(receipt,ensure_ascii=False,indent=2))
