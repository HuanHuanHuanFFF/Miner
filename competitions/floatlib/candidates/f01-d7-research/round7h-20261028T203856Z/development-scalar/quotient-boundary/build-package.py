"""Old ContractTensor-only power-cell mathematical probe; no build or CI."""
from pathlib import Path
import hashlib,json,re
HERE=Path(__file__).resolve().parent
ROOT=next(p for p in HERE.parents if (p/'AGENTS.md').is_file())
PUB=ROOT/'competitions/floatlib/candidates'
BASE=PUB/'f01-r15-dev-packed-b2-1/Kernel.lean'
BROAD=HERE.parent.parent/'development-broad/CellPrimitive.lean.inc'
HELPER=PUB/'f01-d7-research/round9h-20261026T194639Z/development-helper-audit-v8.py'
TARGET=PUB/'f01-r24-dev-scalar-power-cell1'
sha=lambda raw:hashlib.sha256(raw).hexdigest()
def main():
    base=BASE.read_bytes();assert sha(base)=='622d8394a7127e93dcaf992c62c6dfcff7208d212738409a5e34525dfafd1a58'
    original=BROAD.read_bytes();assert sha(original)=='a34107b6c440235806e5a4436b15ef9a46ba5cc58455a99cbafcff63dad1d937'
    text=original.decode();start=text.index('theorem quotient_even_closed_midpoint')
    end=text.index('\n@[inline] def strictCell',start)
    body=text[start:end].rstrip()+'\n'
    dependency=('namespace Submission.R24CellPrimitive\nopen FloatLib.Floats FloatLib.Floats.Formats.BinaryInterchange\n'+body+'end Submission.R24CellPrimitive\n').encode()
    (HERE/'EvenMidpoint.lean.inc').write_bytes(dependency)
    own=(HERE/'CellPower.lean.inc').read_bytes();source=base+b'\n'+dependency+b'\n'+own
    assert len(source)<256000
    assert source.count(b'import ')==1
    assert not re.search(rb'\b(?:sorry|admit|native_decide|axiom|unsafe)\b',dependency+own)
    TARGET.mkdir(parents=True,exist_ok=True);(TARGET/'Kernel.lean').write_bytes(source)
    names=['Submission.'+n+'_spec' for n in ('add','mul','sum','bmm')]
    names+=['Submission.R24CellPrimitive.quotient_even_closed_midpoint']
    names+=['Submission.R24PowerCell.'+n for n in ('common_bounds','ratio_log22','ratio_log23','native32_power_above_min','native32_min_normal','powerCell_sound')]
    helper=HELPER.read_bytes();assert sha(helper)=='5b58eece211bd9cdaa270fc82bef624a5974c7d056732e19f54547c0fe6ef975'
    components=[]
    for p in (HERE/'EvenMidpoint.lean.inc',HERE/'CellPower.lean.inc'):
        raw=p.read_bytes();components.append({'path':p.relative_to(ROOT).as_posix(),'bytes':len(raw),'sha256':sha(raw)})
    manifest={'candidate':TARGET.name,'candidate_file':'Kernel.lean','candidate_sha256':sha(source),'candidate_bytes':len(source),
        'validation_mode':'statement-only','diagnostic_only':True,'diagnostic_timeout_seconds':600,
        'proof_status':'NOT_RUN_ACTUAL_ROUNDRATSCALED_POWER_BINADES_AND_MINNORMAL','performance':'NO_PERFORMANCE_CLAIM',
        'formal_submission':'NOT_SUBMITTED','official_submission_inherited':False,
        'helper_audit_module':HELPER.name,'helper_audit_module_path':HELPER.relative_to(PUB).as_posix(),'helper_audit_module_sha256':sha(helper),
        'explicit_helper_audit':names,'helper_audit_required_endpoints':names,'helper_audit_expected_count':len(names),
        'helper_audit_source_sha256':sha(source),'diagnostic_evaluations':[],'components':components,
        'runtime_prefix':{'path':BASE.relative_to(ROOT).as_posix(),'sha256':sha(base),'bytes':len(base),'byte_identical':True},
        'reused_dependency':{'source_path':BROAD.relative_to(ROOT).as_posix(),'source_sha256':sha(original),
            'theorem':'Submission.R24CellPrimitive.quotient_even_closed_midpoint','exact_extracted_body_sha256':sha(body.encode()),
            'scope':'Exact broad proof body, dependency reuse only; not a new lemma claim or a change to broad frozen source.'},
        'scope':'Old ContractTensor mathematical primitive with four exact B2 public endpoints. Certified mantissa2^23: lower quarter-unit boundary for normal exponent>=2, lower half-unit at minnormal exponent1; closed even ties, actual NativeBinary32.roundRatScaled to mkBits. No abstract hcell assumption, native-proposal accuracy premise, new-track kernel or benchmark.'}
    (TARGET/'manifest.json').write_bytes((json.dumps(manifest,ensure_ascii=False,indent=2)+'\n').encode())
    ready={'status':'PREPARED_PENDING_MODEL_PREFLIGHT','candidate':TARGET.relative_to(ROOT).as_posix(),'source_sha256':sha(source),
        'bytes':len(source),'roots':names,'components':components,'Lean':'NOT_RUN','runtime':'NOT_RUN'}
    (HERE/'READY.json').write_bytes((json.dumps(ready,indent=2)+'\n').encode())
    print(json.dumps({'candidate':TARGET.name,'sha256':sha(source),'bytes':len(source),'roots':len(names)}))
if __name__=='__main__':main()
