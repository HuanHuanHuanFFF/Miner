"""Assemble one B2-layout variant on frozen D b116; no compiler/Git/CI."""
from pathlib import Path
from datetime import datetime,timezone
import hashlib,json,time
OUT=Path(__file__).resolve().parent
ROOT=next(p for p in OUT.parents if (p/'competitions/floatlib/pins.json').is_file())
start=time.monotonic();sha=lambda b:hashlib.sha256(b).hexdigest()
basepath='competitions/floatlib/candidates/f01-r15-dev-column-pairs2/Kernel.lean'
base=(ROOT/basepath).read_bytes()
expected='b116067185626ccb758fbadd608ce7514cb1ddef70ddd0a07e1596f8c776952b'
assert sha(base)==expected
fragment=(OUT/'PackedB2.lean').read_bytes()
eol=b'\r\n' if b'\r\n' in base else b'\n'
insert=fragment.replace(b'\r\n',b'\n').replace(b'\n',eol)
marker=b'end Submission.R15ThinPairs'+eol
assert base.count(marker)==1
i=base.index(marker)+len(marker)
before,tail=base[:i],base[i:]
for old,new in [(b'else R15ThinPairs.dispatch batch m n p A B',b'else R15PackedB2.dispatch batch m n p A B'),
                (b'exact R15ThinPairs.dispatch_spec batch m n p A B',b'exact R15PackedB2.dispatch_spec batch m n p A B')]:
    assert tail.count(old)==1
    tail=tail.replace(old,new)
result=before+eol+insert+eol+tail
assert len(result)<=256000 and result.count(b'import ContractTensor')==1
assert not any(x in fragment for x in [b'sorry',b'admit',b'axiom ',b'unsafe ',b'@[extern',b'implemented_by'])
(OUT/'Kernel-b2.lean').write_bytes(result)
assert sha((ROOT/basepath).read_bytes())==expected
assert sha((OUT/'Kernel-pairs.lean').read_bytes())=='b9629b37f47ed8b5c169de213ccec2a67a2b3b2737803c5814e996c1a1cc16b3'
receipt={'at_utc':datetime.now(timezone.utc).isoformat(),'parent':basepath,'parent_sha256':expected,
 'fragment':'PackedB2.lean','fragment_sha256':sha(fragment),'fragment_bytes':len(fragment),
 'candidate':'Kernel-b2.lean','candidate_sha256':sha(result),'candidate_bytes':len(result),
 'state':'SINGLE_LAYOUT_VARIANT_SOURCE_READY_NOT_COMPILED','proof_status':'COMPLETE_ATTEMPT_UNCOMPILED',
 'runtime_scope':'Same2<=p<=8,n>1,m>=4 and outer underflow guard as parent. Only preparedB layout and loop B accesses change; A decoding, two chains, F2 terminal result, emit, finish and raw replay remain semantically the parent via output_eq.',
 'layout':'Vector(Vector B2 n)(batch*ceil(p/2)); one outer tile vector and one inner k-vector per batch/pair. B2 aliases the existing two-native-Float32 F2. Tile base/div/mod computed before k preparation callback.',
 'odd_tail':'Preserves even the parent unobserved second lane exactly through total raw getD, including cross-row/batch reads and final+0 default. Therefore oddp prepares2*ceil(p/2) native fields per B row rather thanp.',
 'proof_route':'packB_get -> generic loop_s0/loop_s1 -> loop_eq_original -> group_eq/row_eq/output_eq -> existing Prefix/reference -> dispatch_spec',
 'new_generated_C':'UNKNOWN','new_full_gate':'NOT_RUN','performance':'UNKNOWN',
 'elapsed_seconds':time.monotonic()-start}
assert receipt['elapsed_seconds']<5
(OUT/'b2-build-receipt.json').write_text(json.dumps(receipt,ensure_ascii=False,indent=2)+'\n',encoding='utf-8')
print(json.dumps(receipt,ensure_ascii=False))
