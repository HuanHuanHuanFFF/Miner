"""Normalized interval-certificate probe under original ContractTensor. No build/CI."""
from pathlib import Path
import hashlib,json,re
HERE=Path(__file__).resolve().parent
ROOT=next(p for p in HERE.parents if (p/'AGENTS.md').is_file())
PUB=ROOT/'competitions/floatlib/candidates'
BASE=ROOT/'competitions/floatlib/references/official-incumbent/Kernel.lean'
BROAD=HERE.parent.parent/'development-broad'
HELPER=PUB/'f01-d7-research/round9h-20261026T194639Z/development-helper-audit-v8.py'
TARGET=PUB/'f01-r24-dev-scalar-interval-word1281'
sha=lambda b:hashlib.sha256(b).hexdigest()

def main():
    base=BASE.read_bytes();assert sha(base)=='5d0cef3ff21093ca05cde92e516edfe45afca8e11996ad4858e7fb2407d65868'
    parts=[BROAD/'CellPrimitive-v2.lean.inc',HERE/'CellPower-v2.lean.inc',BROAD/'WordGap128.lean.inc',
           HERE/'PowerGap128.lean.inc',HERE/'IntervalWord128.lean.inc']
    expected=['78bef6ff5b493648c3be18faf0b194380fbf7c7585591b15b7c587caec7d1819',
        '8bea0d97835458a3ffaca3dd3944f2f624bf89d3b1fea04fb43b6f76e89c7313',
        '6a7e25abad9723dc21f46856b06a3480232b689ffeb3d139025493b4f0bbacfe']
    for p,h in zip(parts,expected):assert sha(p.read_bytes())==h
    source=base+b'\n\n'+b'\n\n'.join(p.read_bytes() for p in parts)
    assert len(source)<256000 and source.count(b'import ')==1
    assert not re.search(rb'\b(?:sorry|admit|native_decide|axiom|unsafe)\b',b'\n'.join(p.read_bytes() for p in parts))
    TARGET.mkdir(parents=True,exist_ok=True);(TARGET/'Kernel.lean').write_bytes(source)
    roots=['Submission.'+n+'_spec' for n in ('add','mul','sum','bmm')]
    roots+=['Submission.R24CellPrimitive.'+n for n in ('quotient_strict_midpoint','quotient_even_closed_midpoint','strictCell_sound',
        'normal_ratio_nat_bounds','normal_ratio_log23','native32_strict_cell','normalStrictCell_sound')]
    roots+=['Submission.R24PowerCell.'+n for n in ('common_bounds','ratio_log22','ratio_log23','native32_power_above_min','native32_min_normal','powerCell_sound')]
    roots+=['Submission.R24WordGap128.'+n for n in ('gap_toNat_cases','check_midpoint_bounds','check_sound','normalCheck_sound')]
    roots+=['Submission.R24PowerGap128.'+n for n in ('halfCheck_bound','quarterCheck_bound','check_powerCell','check_sound')]
    roots+=['Submission.R24IntervalWord128.'+n for n in ('strictCheck_sound','powerCheck_cell','powerCheck_sound')]
    helper=HELPER.read_bytes();assert sha(helper)=='5b58eece211bd9cdaa270fc82bef624a5974c7d056732e19f54547c0fe6ef975'
    components=[{'path':p.relative_to(ROOT).as_posix(),'bytes':len(p.read_bytes()),'sha256':sha(p.read_bytes())} for p in parts]
    manifest={'candidate':TARGET.name,'candidate_file':'Kernel.lean','candidate_sha256':sha(source),'candidate_bytes':len(source),
        'validation_mode':'statement-only','diagnostic_only':True,'diagnostic_timeout_seconds':600,
        'proof_status':'NOT_RUN_NORMALIZED_INTERVAL_ENDPOINTS_TO_ACTUAL_WORD','performance':'NOT_A_PERFORMANCE_CANDIDATE',
        'formal_submission':'NOT_SUBMITTED','official_submission_inherited':False,
        'helper_audit_module':HELPER.name,'helper_audit_module_path':HELPER.relative_to(PUB).as_posix(),'helper_audit_module_sha256':sha(helper),
        'explicit_helper_audit':roots,'helper_audit_required_endpoints':roots,'helper_audit_expected_count':len(roots),
        'helper_audit_source_sha256':sha(source),'diagnostic_evaluations':[],'components':components,
        'runtime_prefix':{'path':BASE.relative_to(ROOT).as_posix(),'sha256':sha(base),'bytes':len(base),'byte_identical':True},
        'scope':'Original ContractTensor mathematics only, shipped four callbacks exact. Runtime checks full128 normalized numerator endpoints/full64 D and arbitrary UInt64 mantissa/UInt32 field; independently established actual N enclosure is a theorem premise. Strict interior or closed power/minnormal endpoint guards imply actual roundRatScaled/mkBits. No raw norm coverage, external scale alignment, native enclosure derivation, new-track implementation, cost or adoption claim.',
        'normalization_boundary':'N/D must already be near the24-bit mantissa at exponent field-150. Width guard is not removed. Raw norm ratios may need a wider scaled denominator and are not covered by this interface alone.'}
    (TARGET/'manifest.json').write_bytes((json.dumps(manifest,indent=2)+'\n').encode())
    ready={'status':'PREPARED_PENDING_PREFLIGHT','candidate':TARGET.relative_to(ROOT).as_posix(),'source_sha256':sha(source),
        'bytes':len(source),'roots':roots,'components':components,'Lean':'NOT_RUN','replay':'NOT_RUN','AX':'NOT_RUN','native':'NOT_RUN','cost':'NOT_RUN'}
    (HERE/'READY-interval-word128.json').write_bytes((json.dumps(ready,indent=2)+'\n').encode())
    print(json.dumps({'candidate':TARGET.name,'source':sha(source),'bytes':len(source),'roots':len(roots)}))
if __name__=='__main__':main()
