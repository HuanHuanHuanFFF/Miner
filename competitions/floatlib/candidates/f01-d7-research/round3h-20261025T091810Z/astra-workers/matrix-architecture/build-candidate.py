from pathlib import Path
import hashlib,json,re
from datetime import datetime,timezone
here=Path(__file__).resolve().parent
root=next(p for p in here.parents if (p/'competitions/floatlib/pins.json').is_file())
base=root/'competitions/floatlib/candidates/f01-r15-dev-packed-b2-1/Kernel.lean'
data=base.read_bytes();assert hashlib.sha256(data).hexdigest()=='622d8394a7127e93dcaf992c62c6dfcff7208d212738409a5e34525dfafd1a58'
at=data.rfind(b'namespace Submission\r\n')
if at<0:at=data.rfind(b'namespace Submission\n')
assert at>200000
prefix,tail=data[:at],data[at:]
assert tail.count(b'else R15PackedB2.dispatch batch m n p A B')==1
assert tail.count(b'exact R15PackedB2.dispatch_spec batch m n p A B')==1
newtail=tail.replace(b'else R15PackedB2.dispatch batch m n p A B',b'else R16A4B2.dispatch batch m n p A B').replace(b'exact R15PackedB2.dispatch_spec batch m n p A B',b'exact R16A4B2.dispatch_spec batch m n p A B')
fragments=[(here/p).read_bytes() for p in ('A4B2-core.lean','A4B2-entry.lean')]
out=prefix+b'\n'.join(fragments)+b'\n'+newtail
assert len(out)<=256000
assert not re.search(rb'\b(sorry|axiom|unsafe|implemented_by|extern)\b',b'\n'.join(fragments))
(here/'Kernel-a4b2.lean').write_bytes(out)
manifest=dict(at_utc=datetime.now(timezone.utc).isoformat(),status='COMPLETE_ALL_INPUT_PROOF_ATTEMPT_NOT_COMPILED',
 parent_sha256=hashlib.sha256(data).hexdigest(),kernel_sha256=hashlib.sha256(out).hexdigest(),kernel_bytes=len(out),size_margin=256000-len(out),
 fragments={p:dict(sha256=hashlib.sha256((here/p).read_bytes()).hexdigest(),bytes=(here/p).stat().st_size) for p in ('A4B2-core.lean','A4B2-entry.lean')},
 unchanged_baseline_prefix_bytes=at,unchanged_prefix_sha256=hashlib.sha256(prefix).hexdigest(),
 baseline_tail_changes=['BMM non-underflow dispatcher name','BMM non-underflow proof dispatcher name'],
 active_guard='underflow miss and p>=2,n>1,m>=4,n<USize.size',
 fallback='Exact accepted B2 dispatcher',lean='NOT_RUN',full_gate='NOT_RUN',performance='NOT_RUN',
 constraints='Only ContractTensor, original4obligations, standard3axioms, original gate/bench/pins; no upstream modifications')
(here/'candidate-manifest.json').write_text(json.dumps(manifest,indent=2)+'\n')
print(json.dumps(manifest))
