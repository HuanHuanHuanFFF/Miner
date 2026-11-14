"""Hash-bound old-ContractTensor boundary helper package. No build/Git/CI."""
from pathlib import Path
import hashlib,json,re
HERE=Path(__file__).resolve().parent
ROOT=next(p for p in HERE.parents if (p/'AGENTS.md').is_file())
PUB=ROOT/'competitions/floatlib/candidates'
BASE=PUB/'f01-r15-dev-packed-b2-1/Kernel.lean'
BROAD=HERE.parent.parent/'development-broad/WordGap128.lean.inc'
HELPER=PUB/'f01-d7-research/round9h-20261026T194639Z/development-helper-audit-v8.py'
TARGET=PUB/'f01-r24-dev-scalar-power-gap1281'
sha=lambda x:hashlib.sha256(x).hexdigest()

def main():
    base=BASE.read_bytes();assert sha(base)=='622d8394a7127e93dcaf992c62c6dfcff7208d212738409a5e34525dfafd1a58'
    broad=BROAD.read_bytes();assert sha(broad)=='6a7e25abad9723dc21f46856b06a3480232b689ffeb3d139025493b4f0bbacfe'
    # Only these exact definitions/proofs are reused. No handwritten alteration.
    spans=[(b'@[inline] def gap ',b'/-- Strict midpoint check'),
           (b'theorem gap_toNat_cases ',b'theorem check_midpoint_bounds ')]
    bodies=[];extractions=[]
    for start,end in spans:
        a=broad.index(start);b=broad.index(end,a);body=broad[a:b]
        bodies.append(body);extractions.append({'start':a,'end_exclusive':b,'sha256':sha(body),'bytes':len(body)})
    dep=b'namespace Submission.R24WordGap128\nopen FloatLib.Numerics.FixedWord\n'+b'\n'.join(bodies)+b'end Submission.R24WordGap128\n'
    (HERE/'GapSubstrate-exact.lean.inc').write_bytes(dep)
    parts=[HERE/'EvenMidpoint-v2.lean.inc',HERE/'CellPower-v2.lean.inc',HERE/'GapSubstrate-exact.lean.inc',HERE/'PowerGap128.lean.inc']
    assert sha(parts[0].read_bytes())=='b4316af8d681580cada1eb05ba918cb58a9d902bce63dec6714523af01fb35c8'
    source=base+b'\n'+b'\n'.join(p.read_bytes() for p in parts)
    assert len(source)<256000 and source.count(b'import ')==1
    assert not re.search(rb'\b(?:sorry|admit|native_decide|axiom|unsafe)\b',b'\n'.join(p.read_bytes() for p in parts))
    TARGET.mkdir(parents=True,exist_ok=True);(TARGET/'Kernel.lean').write_bytes(source)
    roots=['Submission.'+n+'_spec' for n in ('add','mul','sum','bmm')]
    roots+=['Submission.R24CellPrimitive.quotient_even_closed_midpoint']
    roots+=['Submission.R24PowerCell.'+n for n in ('common_bounds','ratio_log22','ratio_log23','native32_power_above_min','native32_min_normal','powerCell_sound')]
    roots+=['Submission.R24WordGap128.gap_toNat_cases']
    roots+=['Submission.R24PowerGap128.'+n for n in ('halfCheck_bound','quarterCheck_bound','check_powerCell','check_sound')]
    helper=HELPER.read_bytes();assert sha(helper)=='5b58eece211bd9cdaa270fc82bef624a5974c7d056732e19f54547c0fe6ef975'
    components=[]
    for p in parts:
        b=p.read_bytes();components.append({'path':p.relative_to(ROOT).as_posix(),'bytes':len(b),'sha256':sha(b)})
    manifest={'candidate':TARGET.name,'candidate_file':'Kernel.lean','candidate_sha256':sha(source),'candidate_bytes':len(source),
        'validation_mode':'statement-only','diagnostic_only':True,'diagnostic_timeout_seconds':600,
        'proof_status':'NOT_RUN_FIXED_WORD_POWER_BINADES_MINNORMAL_CLOSED_CELLS','performance':'NO_PERFORMANCE_CLAIM',
        'formal_submission':'NOT_SUBMITTED','official_submission_inherited':False,
        'helper_audit_module':HELPER.name,'helper_audit_module_path':HELPER.relative_to(PUB).as_posix(),'helper_audit_module_sha256':sha(helper),
        'explicit_helper_audit':roots,'helper_audit_required_endpoints':roots,'helper_audit_expected_count':len(roots),
        'helper_audit_source_sha256':sha(source),'diagnostic_evaluations':[],'components':components,
        'runtime_prefix':{'path':BASE.relative_to(ROOT).as_posix(),'sha256':sha(base),'bytes':len(base),'byte_identical':True},
        'dependency_extractions':{'source_path':BROAD.relative_to(ROOT).as_posix(),'source_sha256':sha(broad),
            'spans':extractions,'scope':'Exact gap definition and gap_toNat_cases proof; broad frozen source remains unchanged.'},
        'scope':'Old ContractTensor mathematical primitive, exact B2 public callbacks. Full128 numerator/full64 denominator and raw UInt32 candidate exponent; ordered gap, closed half-unit and quarter-unit guards conclude actual NativeBinary32.roundRatScaled/mkBits at mantissa2^23 including minnormal. No accuracy premise, new-track kernel, native execution or timing claim.'}
    (TARGET/'manifest.json').write_bytes((json.dumps(manifest,indent=2)+'\n').encode())
    ready={'status':'PREPARED_PENDING_MODEL_PREFLIGHT','candidate':TARGET.relative_to(ROOT).as_posix(),
        'source_sha256':sha(source),'bytes':len(source),'roots':roots,'components':components,
        'Lean':'NOT_RUN','replay':'NOT_RUN','AX':'NOT_RUN','runtime':'NOT_RUN','CI':'PARENT_ONLY'}
    (HERE/'READY-power-gap128.json').write_bytes((json.dumps(ready,indent=2)+'\n').encode())
    print(json.dumps({'candidate':TARGET.name,'source':sha(source),'bytes':len(source),'roots':len(roots)}))
if __name__=='__main__':main()
