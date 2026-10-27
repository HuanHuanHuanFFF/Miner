"""Pinned baseline ADD C/ABI facts, not new-source or timing verification."""
from pathlib import Path
from hashlib import sha256, sha1
from datetime import datetime, timezone
import json

base=Path(__file__).resolve().parent;root=base.parents[4]
prior=json.loads((base/'astra-retained-scalar-codegen-review.json').read_bytes())
c_path=root/prior['generated_c'];c_bytes=c_path.read_bytes()
assert sha256(c_bytes).hexdigest()==prior['generated_c_sha256']
lines=c_bytes.decode('utf-8').splitlines()
header_path=root/'competitions/floatlib/research/astra-collab-20261023-r7/upstream/lean-lean.h'
header=header_path.read_bytes()
assert sha256(header).hexdigest()=='982c731a1fbacc7688006f44f9f7af9d9e3e0247d310a728827f49e7f1466c13'
assert sha1(b'blob '+str(len(header)).encode()+b'\0'+header).hexdigest()=='910ecae72a7d1c149d4ccc8111ee438c8b4551dd'
assert 'uint32_t lp_competition_Submission_add(uint32_t' in lines[21260]
points=dict(
    unboxed_uint32_entry=21261,boxed_wrapper=21596,
    mantissa_to_float32=[21526,21581],
    scale_table_borrowed_reads=[21531,21586],
    scale_float32_mul=[21534,21589],
    native_float32_add=21469,result_self_beq=21470,final_to_bits=21505,
    table_index_uint32_to_nat=[21530,21585])
checks={'mantissa_to_float32':'lean_uint32_to_float32',
        'scale_table_borrowed_reads':'lean_array_fget_borrowed',
        'scale_float32_mul':'lean_float32_mul',
        'native_float32_add':'lean_float32_add','result_self_beq':'lean_float32_beq',
        'final_to_bits':'lean_float32_to_bits','table_index_uint32_to_nat':'lean_uint32_to_nat'}
for key,needle in checks.items():
    for n in points[key] if isinstance(points[key],list) else [points[key]]:
        assert needle in lines[n-1]
record=dict(timestamp_utc=datetime.now(timezone.utc).isoformat(),
    state='PINNED_OLD_ADD_DIAGNOSTIC_C_AND_RUNTIME_HEADER_FACTS',
    run=40135440097,candidate_sha256=prior['candidate_sha256'],
    retained_parent_sha256=prior['retained_runtime_parent_sha256'],
    generated_c=str(c_path.relative_to(root)),generated_c_sha256=prior['generated_c_sha256'],
    lines=points,lean_ref='293d5d0c0c3f3dded4688b3ccd6a33939ac5102b',
    header=dict(path=str(header_path.relative_to(root)),sha256=sha256(header).hexdigest(),git_blob_sha1='910ecae72a7d1c149d4ccc8111ee438c8b4551dd'),
    abi_facts=[
      'lean_float32_add/mul/beq and lean_uint32_to_float32 are static inline in lean.h; generated C function-like syntax is not evidence of out-of-line calls.',
      'The normal table path uses two integer-to-float conversions, two scale multiplies, two borrowed scale reads, one add, a self-NaN guard and final to_bits. Low normal exponents outside converter fastOK can instead use of_bits.',
      'The exported public add is uint32_t -> uint32_t with a separate boxed wrapper. Actual timed caller may still use that wrapper; inspect the actual BenchSuite code.',
      'On64-bit, lean_box_uint32 uses immediate lean_box. lean_box_float32 always allocates a scalar constructor. An Array Float32 cache therefore has a real representation cost unless generated code eliminates it; actual new-cache allocation count is not established.',
      'Normal table indices fit511 and are immediate Nat on64-bit. No guaranteed heap allocation should be charged to those two index conversions.'
    ],header_line_ranges=dict(float32_box=[3007,3011],uint32_box=[2955,2965],float32_ops=[3255,3267]),
    new_source='a2342948257d2e2e2011f0fe941bd2b692e70604b915734f4538b5efd1e69372',
    new_source_status='NOT_COMPILED_NO_GENERATED_C_OR_ASM',
    required_followup='Actual new timed caller, CSE of eligible/body repeated sort/extract work, higher-order fallback lowering, native-word boxing and full operation timing.',
    limits='Old diagnostic C is not the cleaned timed public-v2 object. No cycles, speedup, new-source allocation count or adoption inferred. No new candidate/CI.')
Path(__file__).with_suffix('.json').write_text(json.dumps(record,ensure_ascii=False,indent=2)+'\n',encoding='utf-8')
print(json.dumps({k:v for k,v in record.items() if k not in ['abi_facts','header']},ensure_ascii=False,indent=2))
