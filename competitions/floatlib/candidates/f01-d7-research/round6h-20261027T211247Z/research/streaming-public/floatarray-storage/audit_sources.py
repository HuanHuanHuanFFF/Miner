"""Read and bind existing sources/verdicts; no compiler or new runtime."""
from pathlib import Path
import hashlib,json
from datetime import datetime,timezone
HERE=Path(__file__).resolve().parent
ROOT=next(p for p in HERE.parents if (p/'competitions/floatlib/pins.json').is_file())
BASE=ROOT/'competitions/floatlib'
def receipt(p):
    raw=p.read_bytes()
    return dict(path=str(p.relative_to(ROOT)),bytes=len(raw),sha256=hashlib.sha256(raw).hexdigest())
files=[
BASE/'candidates/f01-r15-dev-packed-b2-1/Kernel.lean',
BASE/'candidates/f01-d2-checked-floatarray/Kernel.lean',
BASE/'candidates/f01-d3-fused-floatarray/Kernel.lean',
BASE/'candidates/f01-d7-research/round45m-20261027T074758Z/research/source-intake/lean-runtime-293d5d0c/lean.h',
BASE/'candidates/f01-d7-research/round3h-20261024T112622Z/profile-scalar-wide-lean-Float32.lean',
BASE/'research/materials/20261022/R2-W04/R2-W04/upstream/lean-core-review/src_Init_Data_FloatArray_Basic.lean',
BASE/'research/materials/20261022/R2-W04/R2-W04/upstream/lean-core-review/src_runtime_object.cpp',
BASE/'research/astra-collab-20261022/codegen-audit-39661096034.json',
HERE/'REVIEW.md',HERE/'HANDOFF.md']
verdict_dirs=[BASE/'candidates/f01-mul-log2-proof1/ci-runs/39663131701/download-4d8a1a17e93c49598c38c54607e80d7e',
BASE/'candidates/f01-mul-log2-proof1/ci-runs/39724650290/download-38b3701f9f6f4ab8a56e4bae619336d9']
verdicts=[]
for directory,names in [(verdict_dirs[0],['f01-d2-checked-floatarray','f01-d2-preconverted-bmm']),
                        (verdict_dirs[1],['f01-d3-fused-floatarray'])]:
    for name in names:
        p=directory/(name+'-verdict.json');v=json.loads(p.read_bytes()); files.append(p)
        assert v['passed'] and v['stage']=='score' and len(v['rounds'])==25
        verdicts.append(dict(candidate=name,seed=v['seed'],passed=v['passed'],rounds=25,
            ratio_vs_own_shipped_reference=v['ratio'],
            classes={k:z for k,z in v['classes'].items() if k.startswith('bmm:')}))
old,control=verdicts[:2]
comparison={k:dict(raw_ns_ratio=v['submission_ns']/control['classes'][k]['submission_ns'],
    own_reference_normalized_ratio=v['ratio']/control['classes'][k]['ratio']) for k,v in old['classes'].items()}
audit=json.loads(files[7].read_bytes())
c=next(x for x in audit['records'] if x['candidate']=='f01-d2-checked-floatarray')
current_c=ROOT/c['generated_c']
c_receipt=dict(referenced_path=c['generated_c'],expected_sha256=c['generated_c_sha256'],
    original_present_now=current_c.exists(),fresh_byte_verification=False,
    evidence_scope='Historical hash-bound C audit only; no fresh C/ASM claim.')
if current_c.exists():
    assert receipt(current_c)['sha256']==c['generated_c_sha256']
    c_receipt['fresh_byte_verification']=True
sources=[receipt(p) for p in files]
expected=['622d8394a7127e93dcaf992c62c6dfcff7208d212738409a5e34525dfafd1a58',
'5be0735a90d58d9efb8ee2c6d666c11029bca66665dca03b6b5eff5baf6cbfc4',
'98cef0f25c29fe22cf7fa32cc3fb0f2bc38bf1faf65f91aae4fd2d995fe13d84',
'982c731a1fbacc7688006f44f9f7af9d9e3e0247d310a728827f49e7f1466c13']
assert [x['sha256'] for x in sources[:4]]==expected
report=dict(recorded_at_utc=datetime.now(timezone.utc).isoformat(),sources=sources,
    old_verdicts=verdicts,old_5be_vs_array_float32_same_job=comparison,
    old_c_evidence=c_receipt,new_runtime_created=False,new_kernel_created=False,
    new_formal='NOT_RUN',new_native_cost='UNKNOWN',new_actual_codegen='UNKNOWN',
    hypothesis='B-only group-major two-column FloatArray replacing Array F2; checked once per prepared native B element; unchanged ordered F32 pair MAC and raw replay.')
(HERE/'source-receipt.json').write_text(json.dumps(report,ensure_ascii=False,indent=2)+'\n',encoding='utf-8')
print(json.dumps(dict(recorded_at_utc=report['recorded_at_utc'],review=sources[8],old_c=c_receipt,new_native_cost='UNKNOWN'),ensure_ascii=False))
