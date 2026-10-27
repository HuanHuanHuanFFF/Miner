"""Restore exact retained fallback, removing only its unused R19 outer shells."""
from pathlib import Path
from datetime import datetime, timezone
import difflib
import hashlib
import json

HERE=Path(__file__).resolve().parent; ROOT=HERE.parents[4]
worker=HERE/'development-workers/astra-row-fusion/broad-draft'
original_path=worker/'Kernel-column4-broad.draft.lean'
original=original_path.read_bytes()
base_path=ROOT/'competitions/floatlib/candidates/f01-r15-dev-packed-b2-1/Kernel.lean'
base=base_path.read_bytes()
sha=lambda data:hashlib.sha256(data).hexdigest()
assert sha(original)=='a87f560a5944a778ca93dfb9a9d2dcd59895edc56b0ae7e498dbcf873fce8f19'
assert sha(base)=='622d8394a7127e93dcaf992c62c6dfcff7208d212738409a5e34525dfafd1a58'

def namespace_span(raw,name):
    start_marker=('namespace '+name+'\n').encode()
    end_marker=('end '+name).encode()
    assert raw.count(start_marker)==1
    start=raw.index(start_marker); end=raw.index(end_marker,start)+len(end_marker)
    return start,end

start,end=namespace_span(base,'Submission.R15PackedB2')
retained=base[start:end]
start,end=namespace_span(original,'Submission.R15PackedB2')
stub=original[start:end]
revised=original[:start]+retained+original[end:]
removed=[]
for name in ('Submission.R19Temporal','Submission.R19DualTemporal'):
    start,end=namespace_span(revised,name)
    marker=b'@[inline] def group ('
    cut=revised.index(marker,start,end)
    ending=revised.index(('end '+name).encode(),cut,end)
    raw=revised[cut:ending]
    removed.append(dict(namespace=name,bytes=len(raw),sha256=sha(raw)))
    revised=revised[:cut]+revised[ending:]
for old,new in ((b'else R19DualTemporal.dispatch b m n p A B',b'else R15PackedB2.dispatch b m n p A B'),
    (b'exact R19DualTemporal.dispatch_spec b m n p A B',b'exact R15PackedB2.dispatch_spec b m n p A B')):
    assert revised.count(old)==1
    revised=revised.replace(old,new)
assert len(revised)<=256000 and b'R19DualTemporal.dispatch' not in revised
assert revised.count(b'import ContractTensor')==1
target=HERE/'development-column4-broad-retained.lean'
assert not target.exists()
target.write_bytes(revised)
for direction,left,right in (('forward',original,revised),('inverse',revised,original)):
    patch=''.join(difflib.unified_diff(left.decode().splitlines(True),right.decode().splitlines(True),
        fromfile='a87f-broad-c36-fallback' if direction=='forward' else 'retained-broad',
        tofile='retained-broad' if direction=='forward' else 'a87f-broad-c36-fallback'))
    (HERE/f'development-column4-retained-{direction}.patch').write_bytes(patch.encode())
receipt=dict(at_utc=datetime.now(timezone.utc).isoformat(),state='NOT_RUN_RESTORED_FALLBACK_SOURCE',
    source=target.relative_to(ROOT).as_posix(),sha256=sha(revised),bytes=len(revised),remaining_bytes=256000-len(revised),
    parent_source=original_path.relative_to(ROOT).as_posix(),parent_sha256=sha(original),
    restored_namespace=dict(name='Submission.R15PackedB2',old_stub_bytes=len(stub),retained_bytes=len(retained),
        retained_sha256=sha(retained),retained_source_sha256=sha(base)),removed_outer_shells=removed,
    fallback='Retained exact PackedB2 namespace; public UnderflowZero and other three entries unchanged from producer source',
    change_scope='Restore retained B2; remove unused Temporal/Dual outer group/writer/dispatch shells, keep all core dependencies; switch exactly two new fallback references.',
    core_loop='Unchanged from producer repair118d; source needs fresh whole statement/replay/19roots',
    public_correctness='NOT_RUN',performance='NOT_RUN')
(HERE/'development-column4-retained-build.json').write_bytes((json.dumps(receipt,indent=2)+'\n').encode())
print(json.dumps(dict(source=receipt['source'],sha256=receipt['sha256'],bytes=len(revised),remaining_bytes=receipt['remaining_bytes'],removed=removed)))
