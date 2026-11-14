"""Scaled dyadic interval integration, old ContractTensor public endpoints only."""
from pathlib import Path
import hashlib,json,re
HERE=Path(__file__).resolve().parent
ROOT=next(p for p in HERE.parents if (p/'AGENTS.md').is_file())
PUB=ROOT/'competitions/floatlib/candidates'
PARENT=PUB/'f01-r24-dev-broad-scaled-cell1'
BASE=ROOT/'competitions/floatlib/references/official-incumbent/Kernel.lean'
TARGET=PUB/'f01-r24-dev-scalar-dyadic-interval1281'
sha=lambda b:hashlib.sha256(b).hexdigest()
def main():
    m=json.loads((PARENT/'manifest.json').read_bytes());parent=(PARENT/'Kernel.lean').read_bytes()
    assert sha(parent)==m['candidate_sha256']=='e80d9a7f68564cb9a2ab07e7bee071b9b32db6ed2a47d6662214d1de5e6496a4'
    base=BASE.read_bytes();assert sha(base)=='5d0cef3ff21093ca05cde92e516edfe45afca8e11996ad4858e7fb2407d65868'
    pieces=[]
    for c in m['components']:
        b=(ROOT/c['path']).read_bytes();assert sha(b)==c['sha256'] and len(b)==c['bytes'];pieces.append(b)
    fragment=HERE/'DyadicInterval128.lean.inc';body=fragment.read_bytes();pieces.append(body)
    assert not re.search(rb'\b(?:sorry|admit|native_decide|axiom|unsafe)\b',body)
    raw=base+b'\n\n'+b'\n\n'.join(pieces);assert len(raw)<256000
    roots=m['explicit_helper_audit']+['Submission.R24DyadicInterval128.check_bounds','Submission.R24DyadicInterval128.check_sound']
    m.update(candidate=TARGET.name,candidate_sha256=sha(raw),candidate_bytes=len(raw),
        helper_audit_source_sha256=sha(raw),explicit_helper_audit=roots,helper_audit_required_endpoints=roots,
        helper_audit_expected_count=len(roots),proof_status='NOT_RUN_DYADIC_INTERVAL_CONTROLLER_WITH_ARBITRARY_ACTUAL_RATIO',
        parents=[{'candidate':PARENT.name,'sha256':sha(parent),'status':'FROZEN_UNCOMPILED_SOURCE_NO_INHERITED_ACCEPTANCE'}],
        runtime_prefix={'path':BASE.relative_to(ROOT).as_posix(),'bytes':len(base),'sha256':sha(base),'byte_identical':True},
        scope='Original ContractTensor mathematics with exact shipped four callbacks. Full128 dyadic endpoint interval and logical exponent checked against word midpoint coefficients; raw exact N/D may be arbitrarily wide and exists only in theorem premises. Real enclosure implies actual Native32.roundRatScaled at independent original exponent. No normalized denominator constructed, opaque cast, actual native enclosure derivation, new-track kernel, cost or adoption claim.')
    m['components'].append({'path':fragment.relative_to(ROOT).as_posix(),'bytes':len(body),'sha256':sha(body)})
    TARGET.mkdir(parents=True,exist_ok=True);(TARGET/'Kernel.lean').write_bytes(raw)
    (TARGET/'manifest.json').write_bytes((json.dumps(m,indent=2)+'\n').encode())
    ready={'status':'PREPARED_PENDING_SCALED_INTERVAL_MODEL','candidate':TARGET.relative_to(ROOT).as_posix(),
        'source_sha256':sha(raw),'bytes':len(raw),'roots':len(roots),'components':m['components'],
        'Lean':'NOT_RUN','replay':'NOT_RUN','AX':'NOT_RUN','native':'NOT_RUN','cost':'NOT_RUN'}
    (HERE/'READY-dyadic-interval128.json').write_bytes((json.dumps(ready,indent=2)+'\n').encode())
    print(json.dumps({'candidate':TARGET.name,'source':sha(raw),'bytes':len(raw),'roots':len(roots)}))
if __name__=='__main__':main()
