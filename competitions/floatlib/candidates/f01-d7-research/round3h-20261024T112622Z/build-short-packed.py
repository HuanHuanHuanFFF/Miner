"""One route experiment: reuse the proved packed core for short dot products."""
from pathlib import Path
from datetime import datetime,timezone
import hashlib,json
HERE=Path(__file__).resolve().parent
ROOT=HERE.parents[4]
def sha(raw):return hashlib.sha256(raw).hexdigest()
def main():
    parent=ROOT/'competitions/floatlib/candidates/f01-d12-scalar-combined/Kernel.lean'
    raw=parent.read_bytes();assert sha(raw)=='df5c61a0ca24a8ef18c0c42d83bdd23466872d3fe8f39dd912e9c347b27fb172'
    start=raw.index(b'def bmmBeforeR11Cross (');end=raw.index(b'end Submission',start)
    section=raw[start:end]
    old=b'DirectContinuous.core';new=b'RowStream.core'
    assert section.count(old)==2 and section.count(b'DirectContinuous.core_eq_reference')==1
    changed=section.replace(old,new)
    result=raw[:start]+changed+raw[end:]
    assert len(result)<=256000 and result[:start]+section+result[start+len(changed):]==raw
    folder=ROOT/'competitions/floatlib/candidates/f01-d13-short-packed';folder.mkdir(exist_ok=False)
    (folder/'Kernel.lean').write_bytes(result)
    manifest={'candidate':folder.name,'candidate_file':'Kernel.lean','candidate_sha256':sha(result),'candidate_bytes':len(result),
        'parent':'f01-d12-scalar-combined','parent_sha256':sha(raw),'at_utc':datetime.now(timezone.utc).isoformat(),
        'mechanism':'Only n<=4 and p>2 fallback changes DirectContinuous.core to existing RowStream.core. Existing UnderflowZero and p2 Cross dispatch stay first. Packed10 preparation and vector arithmetic are reused unchanged; no new decoder or width.',
        'proof':'Reuse unconditional RowStream.core_eq_reference in the same branch; no type or contract change. New integration NOT_RUN.',
        'prior_evidence':'Current exactDF uninstrumented exposed seed1224016 diagnostic: DirectContinuous whole sum14.246874ms/8cases, RowStream6.231684ms/15cases. Different cases; not a speedup prediction. Existing short direct route was retained in prior package, so this is a falsifiable route re-evaluation, not a historical win claim.',
        'first_falsifier':'Complete original25-round candidate/DF normalized whole must improve >=3% with p05>0. Packed allocation/padding/preparation may erase conversion and SIMD savings. Do not infer gain from operation counts.',
        'edits':[{'scope':'bmmBeforeR11Cross runtime and its proof only','old':'DirectContinuous.core','new':'RowStream.core','occurrences':2}],
        'inverse_reconstruction_sha256':sha(raw),'benchmark':'NOT_RUN','formal_submission':'NOT_SUBMITTED'}
    (folder/'manifest.json').write_bytes((json.dumps(manifest,ensure_ascii=False,indent=2)+'\n').encode())
    print(json.dumps({'candidate':folder.name,'sha256':sha(result),'bytes':len(result),'inverse_equals_parent':True}))
if __name__=='__main__':main()
