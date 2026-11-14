"""Exact same-sign interval construction, no build/Git/CI operations."""
from pathlib import Path
import ast,hashlib,json,re
HERE=Path(__file__).resolve().parent
ROOT=next(p for p in HERE.parents if (p/'AGENTS.md').is_file())
PUB=ROOT/'competitions/floatlib/candidates'
PARENT=PUB/'f01-r24-dev-scalar-dyadic-interval1281'
TARGET=PUB/'f01-r24-dev-scalar-center-radius1281'
sha=lambda b:hashlib.sha256(b).hexdigest()
def main():
    prior=(PARENT/'Kernel.lean').read_bytes();assert sha(prior)=='87c75b37616a18a2fb420e6d6947d97ee982e55cf45f513f65e4434a8c238bc7'
    m=json.loads((PARENT/'manifest.json').read_bytes());fragment=HERE/'CenterRadius128.lean.inc';body=fragment.read_bytes()
    raw=prior+b'\n\n'+body;assert len(raw)<256000
    assert not re.search(rb'\b(?:sorry|admit|native_decide|axiom|unsafe)\b',body)
    for c in m['components']:
        b=(ROOT/c['path']).read_bytes();assert sha(b)==c['sha256'] and len(b)==c['bytes']
    gate=(PUB/'f01-d7-research/official-policy/gate-4b7e838.raw').read_bytes();tree=ast.parse(gate)
    n=next(n for n in tree.body if isinstance(n,ast.Assign) and any(isinstance(t,ast.Name) and t.id=='BANNED' for t in n.targets))
    assert re.compile(ast.literal_eval(n.value.args[0])).search(raw.decode()) is None
    roots=m['explicit_helper_audit']+['Submission.R24CenterRadius128.'+n for n in ('make_bounds','make_encloses','make_word_sound')]
    m.update(candidate=TARGET.name,candidate_sha256=sha(raw),candidate_bytes=len(raw),helper_audit_source_sha256=sha(raw),
        explicit_helper_audit=roots,helper_audit_required_endpoints=roots,helper_audit_expected_count=len(roots),
        proof_status='NOT_RUN_CARRY_CHECKED_SAME_SIGN_INTERVAL_TO_ACTUAL_WORD',
        parents=[{'candidate':PARENT.name,'sha256':sha(prior),'status':'FROZEN_UNCOMPILED_SOURCE_NO_INHERITED_ACCEPTANCE'}],
        scope='Original ContractTensor mathematical primitive with exact shipped four endpoints. Checked128 center-radius subtraction/addition constructs an exact same-sign interval. Independent real error bound proves actual sign and absolute-value enclosure; scaled dyadic controller yields actual Native32 roundRatScaled of arbitrary original N/D/source. No native Float64 decoding/enclosure theorem, raw workload coverage, new-track kernel, cost or adoption claim.')
    m['components'].append({'path':fragment.relative_to(ROOT).as_posix(),'sha256':sha(body),'bytes':len(body)})
    TARGET.mkdir(parents=True,exist_ok=True);(TARGET/'Kernel.lean').write_bytes(raw)
    (TARGET/'manifest.json').write_bytes((json.dumps(m,indent=2)+'\n').encode())
    ready={'status':'PREPARED_PENDING_CENTER_RADIUS_MODEL','candidate':TARGET.relative_to(ROOT).as_posix(),'source_sha256':sha(raw),
        'bytes':len(raw),'roots':len(roots),'components':m['components'],'Lean':'NOT_RUN','replay':'NOT_RUN','AX':'NOT_RUN','native':'NOT_RUN','cost':'NOT_RUN'}
    (HERE/'READY-center-radius128.json').write_bytes((json.dumps(ready,indent=2)+'\n').encode())
    print(json.dumps({'candidate':TARGET.name,'source':sha(raw),'bytes':len(raw),'roots':len(roots)}))
if __name__=='__main__':main()
