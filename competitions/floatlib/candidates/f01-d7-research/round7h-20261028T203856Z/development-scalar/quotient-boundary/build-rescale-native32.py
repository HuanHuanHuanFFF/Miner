"""Small actual-rounder rescaling proof probe; no build/Git/CI."""
from pathlib import Path
import hashlib,json,re
HERE=Path(__file__).resolve().parent
ROOT=next(p for p in HERE.parents if (p/'AGENTS.md').is_file())
PUB=ROOT/'competitions/floatlib/candidates';BASE=ROOT/'competitions/floatlib/references/official-incumbent/Kernel.lean'
HELPER=PUB/'f01-d7-research/round9h-20261026T194639Z/development-helper-audit-v8.py'
TARGET=PUB/'f01-r24-dev-scalar-rescale-native321'
sha=lambda b:hashlib.sha256(b).hexdigest()
def main():
    base=BASE.read_bytes();assert sha(base)=='5d0cef3ff21093ca05cde92e516edfe45afca8e11996ad4858e7fb2407d65868'
    p=HERE/'RescaleNative32.lean.inc';fragment=p.read_bytes();raw=base+b'\n\n'+fragment
    assert len(raw)<256000 and not re.search(rb'\b(?:sorry|admit|native_decide|axiom|unsafe)\b',fragment)
    roots=['Submission.'+n+'_spec' for n in ('add','mul','sum','bmm')]+['Submission.R24RescaleNative32.roundRatScaled_rescale']
    helper=HELPER.read_bytes();assert sha(helper)=='5b58eece211bd9cdaa270fc82bef624a5974c7d056732e19f54547c0fe6ef975'
    component={'path':p.relative_to(ROOT).as_posix(),'bytes':len(fragment),'sha256':sha(fragment)}
    manifest={'candidate':TARGET.name,'candidate_file':'Kernel.lean','candidate_sha256':sha(raw),'candidate_bytes':len(raw),
        'validation_mode':'statement-only','diagnostic_only':True,'diagnostic_timeout_seconds':600,
        'proof_status':'NOT_RUN_ACTUAL_NATIVE32_ROUNDRATSCALED_ALL_BRANCHES_RESCALE','performance':'NOT_A_PERFORMANCE_CANDIDATE',
        'formal_submission':'NOT_SUBMITTED','official_submission_inherited':False,
        'helper_audit_module':HELPER.name,'helper_audit_module_path':HELPER.relative_to(PUB).as_posix(),'helper_audit_module_sha256':sha(helper),
        'explicit_helper_audit':roots,'helper_audit_required_endpoints':roots,'helper_audit_expected_count':len(roots),
        'helper_audit_source_sha256':sha(raw),'diagnostic_evaluations':[],'components':[component],
        'runtime_prefix':{'path':BASE.relative_to(ROOT).as_posix(),'bytes':len(base),'sha256':sha(base),'byte_identical':True},
        'public_fixed_dependencies':{'FloatLib_commit':'0d91825727839f597fd06b22fdd038ea21480f0c',
            'Model.floorLog2_scaleByPowerOfTwo':'Rational/Logarithm.lean:327, blob88c6df468dcb07bcc68e78c998e74a6a9eb7fe01',
            'Model.roundQuotientEven_scaleByPowerOfTwo_add':'Rational/NearestEven.lean:201, blob796a22ce1c8601df415e600d3677b730b80c0a4e'},
        'scope':'Old ContractTensor mathematical primitive, original shipped four endpoints. For all sign,num,den,source,target, exact logical scale source-target preserves the actual NativeBinary32.roundRatScaled word. Includes zero numerator, zero denominator canonical NaN, subnormal/normal, carry, underflow and overflow. No floating intermediate, new runtime scale allocation, target kernel, cost or adoption claim.'}
    TARGET.mkdir(parents=True,exist_ok=True);(TARGET/'Kernel.lean').write_bytes(raw)
    (TARGET/'manifest.json').write_bytes((json.dumps(manifest,indent=2)+'\n').encode())
    ready={'status':'PREPARED_PENDING_RESCALE_MODEL','candidate':TARGET.relative_to(ROOT).as_posix(),'source_sha256':sha(raw),'bytes':len(raw),
        'roots':len(roots),'components':[component],'Lean':'NOT_RUN','replay':'NOT_RUN','AX':'NOT_RUN','native':'NOT_RUN','cost':'NOT_RUN'}
    (HERE/'READY-rescale-native32.json').write_bytes((json.dumps(ready,indent=2)+'\n').encode())
    print(json.dumps({'candidate':TARGET.name,'source':sha(raw),'bytes':len(raw),'roots':len(roots)}))
if __name__=='__main__':main()
