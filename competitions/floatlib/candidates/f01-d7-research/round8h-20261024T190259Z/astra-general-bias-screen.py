"""Selected Euclidean-division boundary tests for the generic bias derivation."""
from pathlib import Path
from time import monotonic
from hashlib import sha256, sha1
from datetime import datetime, timezone
import json

start, budget_seconds, max_cases = monotonic(), 2.0, 14000

def rne(p, d):
    q,r = divmod(p,d)
    return q+int(2*r>d or (2*r==d and q%2==1))

count, trace = 0, sha256()
for half in list(range(1,257)) + [2**23,2**24,2**48,2**127]:
    for q in [0,1,2,3,15,16,2**24-1,2**48]:
        for r in sorted(set([0,half-1,half,min(half+1,2*half-1),2*half-1])):
            count += 1
            assert count <= max_cases and monotonic()-start <= budget_seconds
            p = q*2*half+r
            got=(p+half-1+(p//(2*half))%2)//(2*half)
            expected=rne(p,2*half)
            assert got==expected
            trace.update(f'{p},{half},{got}\n'.encode())

base = Path(__file__).resolve().parent
sources = [
    ('astra-upstream-lean/src/Init/Data/Nat/Div/Basic.lean',
     'de984fa8bcba0e0324b6d236a54b1637f471705d'),
    ('astra-upstream/FloatLib/Floats/Formats/BinaryInterchange/Arithmetic/Proof.lean',
     '469ca2d5a6749c2dfa5093d8eeb8353e6e701bf6')]
source_info=[]
for name, expected in sources:
    b=(base/name).read_bytes()
    blob=sha1(b'blob '+str(len(b)).encode()+b'\0'+b).hexdigest()
    assert blob==expected
    source_info.append(dict(path=name, bytes=len(b), git_blob_sha1=blob,
                            sha256=sha256(b).hexdigest()))
record=dict(timestamp_utc=datetime.now(timezone.utc).isoformat(),
            state='PAPER_DERIVATION_AND_SELECTED_BOUNDARY_SCREEN_NOT_LEAN',
            script_sha256=sha256(Path(__file__).read_bytes()).hexdigest(),
            cases=count, elapsed_seconds=monotonic()-start,
            budget_seconds=budget_seconds, max_cases=max_cases,
            trace_sha256=trace.hexdigest(), pinned_source_verification=source_info,
            result='NO_SELECTED_COUNTEREXAMPLE',
            negative=[dict(removed='half>0', p=1, half=0,
                           lean_quotient_rounding=1, lean_bias_div_zero=0),
                      dict(removed='shift>=1', p=1, shift=0,
                           original=1, proposed_bias=2)],
            scope='Nat Euclidean identity only, not UInt64 no-wrap, Lean compile, runtime or performance')
Path(__file__).with_suffix('.json').write_text(json.dumps(record,indent=2)+'\n',encoding='utf-8')
print(json.dumps(record,indent=2))
