"""Inventory small proof fragments and exact size-cut interface, no large candidate."""
from pathlib import Path
from datetime import datetime, timezone
import hashlib
import json
import re

OUT=Path(__file__).resolve().parent
ROOT=OUT.parents[6]
ROUND=OUT.parents[1]
def sha(x):return hashlib.sha256(x).hexdigest()

def main():
    base_path=ROOT/'competitions/floatlib/candidates/f01-r21-dev-streaming-pair-probe2/Kernel.lean'
    base=base_path.read_bytes()
    assert sha(base)=='4e36c931825b4c152933208987f066c95a5a0aada79cdea67202a045a7953ba4'
    namespace=b'namespace Submission.R21StreamingPair'
    ns=base.index(namespace)
    start=base.index(b'theorem emit_size ',ns)
    stop=base.index(b'theorem controlRows_size ',start)
    emit=(b'namespace Submission.R21StreamingPair\nopen FloatLib.Floats Competition\n\n'+
          base[start:stop]+b'\nend Submission.R21StreamingPair\n')
    (OUT/'PairEmitSizeOnly.lean.inc').write_bytes(emit)
    assert b'R21StreamingPair' not in base[:ns]
    paths=[ROUND/'development-cost/StreamingQuad.lean.inc',
           OUT.parent/'quad-state/QuadStateProof.lean.inc',
           OUT/'FourWriterDirect.lean.inc',OUT/'FlatRowWriter.lean.inc',OUT/'QuadPublicTransport.lean.inc']
    items=[]
    roots=[]
    for p in paths:
        data=p.read_bytes()
        items.append({'path':str(p.relative_to(ROOT)),'sha256':sha(data),'bytes':len(data)})
        if p.parent==OUT:
            names=re.findall(rb'^theorem ([A-Za-z0-9_]+)',data,re.M)
            nsname='Submission.R22StreamingQuad' if p.name=='QuadPublicTransport.lean.inc' else 'Submission.R22BlockWriter'
            roots.extend(nsname+'.'+n.decode() for n in names)
    B_roots=json.loads((OUT.parent/'quad-state/manifest.json').read_text())['explicit_helper_audit']
    base_roots=['Submission.'+x+'_spec' for x in ['add','mul','sum','bmm']]
    support_roots=['Submission.R20WideRowRefinement.storageLoop_lane',
                   'Submission.R20WideRowRefinement.finish_lane','Submission.R21StreamingPair.emit_size']
    size_roots=['Submission.R22StreamingQuad.'+x for x in ['rows4_size','groups_size','rows_size','output_size']]
    diagnostic_roots=base_roots+support_roots+size_roots+B_roots+roots
    assert len(diagnostic_roots)==len(set(diagnostic_roots))
    result={
        'at_utc':datetime.now(timezone.utc).isoformat(),'state':'NOT_RUN','large_candidate_built':False,
        'base_sha256':sha(base),'base_bytes':len(base),'pieces_in_order':items,
        'A_additional_roots':roots,'A_root_count':len(roots),
        'diagnostic_assembly_audit_roots':diagnostic_roots,
        'diagnostic_assembly_audit_count':len(diagnostic_roots),
        'public_binding_boundary':'In this diagnostic assembly, Submission.bmm_spec is still the original B2 endpoint; the actual four-row theorem is R22StreamingQuad.guarded_spec. A promoted public binding requires its own new exact source and audit.',
        'pair_namespace_start_offset':ns,
        'pair_emit_size_only_sha256':sha(emit),'pair_emit_size_only_bytes':len(emit),
        'base_through_R20_plus_emit_size_bytes':ns+len(emit),
        'untrimmed_assembly_bytes_before_public_alias':len(base)+sum(i['bytes'] for i in items)+2*len(items),
        'minimal_assembly_bytes_before_public_alias':ns+len(emit)+sum(i['bytes'] for i in items)+2*len(items),
        'minimal_assembly_headroom_before_public_alias':256000-(ns+len(emit)+sum(i['bytes'] for i in items)+2*len(items)),
        'cut_boundary':'Keep all original B2 and R20; replace R21StreamingPair namespace with exact emit_size theorem only. D Quad references R21 only for emit_size; B and A quad proofs do not use pair runtime.',
        'concrete_state_dependency':'B rows4_eq_control exact four emit RHS. No new runtime declaration from A.',
        'gaps':['Pinned Lean compilation/replay/axiom audit for combined exact source','New public binding if adopted','Complete costs and independent confirmation'],
    }
    (OUT/'quad-bridge-manifest.json').write_text(json.dumps(result,indent=2)+'\n')
    print(json.dumps(result))

if __name__=='__main__':main()
