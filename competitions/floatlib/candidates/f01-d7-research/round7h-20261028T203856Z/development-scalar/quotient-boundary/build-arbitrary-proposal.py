"""Pure-word proposal plus exact normalized certificate, original ContractTensor only."""
from pathlib import Path
import ast,hashlib,json,re
HERE=Path(__file__).resolve().parent
ROOT=next(p for p in HERE.parents if (p/'AGENTS.md').is_file())
PUB=ROOT/'competitions/floatlib/candidates'
PARENT=PUB/'f01-r24-dev-scalar-interval-word1281'
TARGET=PUB/'f01-r24-dev-scalar-arbitrary-proposal1'
sha=lambda b:hashlib.sha256(b).hexdigest()

def main():
    prior=(PARENT/'Kernel.lean').read_bytes();assert sha(prior)=='b0bb8f5854632ee885fa5cdff06bbad5184243c86008ff4c85c45e8e0260a979'
    fragment=HERE/'ArbitraryProposal.lean.inc';body=fragment.read_bytes();raw=prior+b'\n\n'+body
    assert len(raw)<256000 and not re.search(rb'\b(?:sorry|admit|native_decide|axiom|unsafe)\b',body)
    assert b'Float.toFloat32' not in body and b'Float32.toFloat' not in body
    m=json.loads((PARENT/'manifest.json').read_bytes())
    for c in m['components']:
        b=(ROOT/c['path']).read_bytes();assert sha(b)==c['sha256'] and len(b)==c['bytes']
    gate=(PUB/'f01-d7-research/official-policy/gate-4b7e838.raw').read_bytes()
    tree=ast.parse(gate);n=next(n for n in tree.body if isinstance(n,ast.Assign) and any(isinstance(t,ast.Name) and t.id=='BANNED' for t in n.targets))
    assert re.compile(ast.literal_eval(n.value.args[0])).search(raw.decode()) is None
    roots=m['explicit_helper_audit']+['Submission.R24ArbitraryProposal.check_sound']
    m.update(candidate=TARGET.name,candidate_sha256=sha(raw),candidate_bytes=len(raw),
        helper_audit_source_sha256=sha(raw),explicit_helper_audit=roots,helper_audit_required_endpoints=roots,
        helper_audit_expected_count=len(roots),proof_status='NOT_RUN_ARBITRARY_PURE_WORD_PROPOSAL_WITH_CERTIFIED_ACCEPTANCE',
        parents=[{'candidate':PARENT.name,'sha256':sha(prior),'status':'UNCOMPILED_SOURCE_DEPENDENCY_NO_INHERITED_ACCEPTANCE'}],
        scope='Original ContractTensor mathematics with exact shipped four callbacks. Arbitrary pure-word proposal from any UInt64 data; no floating accuracy or narrowing premise. Exact normalized interval and exact sign premises, checked by fixed-word certificates, imply actual roundRatScaled result. Failed certificates must use caller fallback. No raw norm coverage, new-track runtime, cost or adoption claim.')
    m['components'].append({'path':fragment.relative_to(ROOT).as_posix(),'bytes':len(body),'sha256':sha(body)})
    TARGET.mkdir(parents=True,exist_ok=True);(TARGET/'Kernel.lean').write_bytes(raw)
    (TARGET/'manifest.json').write_bytes((json.dumps(m,indent=2)+'\n').encode())
    report=json.loads((HERE/'proposal-model.json').read_bytes());assert report['source_sha256']==sha(body)
    ready={'status':'READY_ARBITRARY_PROPOSAL_PENDING_DEPENDENCY_TYPING','candidate':TARGET.relative_to(ROOT).as_posix(),
        'source_sha256':sha(raw),'bytes':len(raw),'roots':len(roots),'components':m['components'],
        'model_cases':report['cases'],'model_file':'proposal-model.json','Lean':'NOT_RUN','replay':'NOT_RUN','AX':'NOT_RUN','native':'NOT_RUN','cost':'NOT_RUN',
        'normalization_boundary':m['normalization_boundary'],'proposal_accuracy':'NO_PREMISE; directed tie counterexamples intentionally retained.'}
    (HERE/'READY-arbitrary-proposal.json').write_bytes((json.dumps(ready,indent=2)+'\n').encode())
    print(json.dumps({'candidate':TARGET.name,'source':sha(raw),'bytes':len(raw),'roots':len(roots),'finite_cases':report['cases']}))
if __name__=='__main__':main()
