from datetime import datetime, timezone
from hashlib import sha256
from pathlib import Path
import json

HERE = Path(__file__).resolve().parent
PARENT = HERE.parent / 'f01-d10-bmm-direct-rows' / 'Kernel.lean'
PARENT_SHA = 'a06608bdc419d4647af301bfdd617d52e4796c404661a28672a022eef4a10b78'
source = PARENT.read_bytes()
assert sha256(source).hexdigest() == PARENT_SHA
begin = source.index(b'/-- Classify the native result; raw NaN inputs/results retain exact fallback. -/')
end = source.index(b'/-- `add` and `mul` are FloatLib\'s executable operations, whatever they compute internally. -/', begin)
old = source[begin:end]
renamed = old
replacements = [
    (b'@[inline] def add (x y : Binary32)', b'@[inline] def addBeforeNormalBand (x y : Binary32)'),
    (b'theorem add_spec : \xe2\x88\x80 x y : Binary32, add x y =', b'theorem addBeforeNormalBand_spec : \xe2\x88\x80 x y : Binary32, addBeforeNormalBand x y ='),
    (b'  unfold add\n', b'  unfold addBeforeNormalBand\n'),
    (b'@[inline] def mul (x y : Binary32)', b'@[inline] def mulBeforeNormalBand (x y : Binary32)'),
    (b'theorem mul_spec (x y : Binary32) : mul x y =', b'theorem mulBeforeNormalBand_spec (x y : Binary32) : mulBeforeNormalBand x y ='),
    (b'  unfold mul\n', b'  unfold mulBeforeNormalBand\n'),
]
for a, b in replacements:
    assert renamed.count(a) == 1, a
    renamed = renamed.replace(a, b, 1)
block = (HERE / 'normal-band-block.lean').read_bytes().strip() + b'\n\n'
candidate = source[:begin] + renamed + block + source[end:]
assert len(candidate) <= 256000
assert candidate.startswith(b'import ContractTensor\n')
assert candidate.count(b'\nimport ') == 0
for forbidden in (b'sorry', b'axiom ', b'unsafe ', b'extern ', b'implemented_by', b'set_option'):
    assert forbidden not in candidate
restored = candidate[:begin] + old + candidate[begin + len(renamed) + len(block):]
assert restored == source
(HERE / 'Kernel.lean').write_bytes(candidate)
manifest = {
    'candidate': HERE.name,
    'candidate_file': 'Kernel.lean',
    'candidate_sha256': sha256(candidate).hexdigest(),
    'candidate_bytes': len(candidate),
    'created_at_utc': datetime.now(timezone.utc).isoformat(),
    'parent': PARENT.parent.name,
    'parent_sha256': PARENT_SHA,
    'mechanism': 'One narrow two-input joint UInt32 bit-OR interval guard for E64..191. Hit directly tableProduct-converts both words, performs one native add/mul and ofFloat32, skipping old per-convert guards and result self-BEq. Miss uses exact renamed a066 scalar. All old declarations/spec remain under local renamed entries; new add/mul inserted before original add_eq/mul_eq so later tensor/replay references resolve to new proven scalars.',
    'proof': 'UInt32.toNat_or and actual Nat.left_le_or/right_le_or make each wrapped offset<2^30; UInt32 subtraction and omega give old NormalBand eligibility. Existing normal_eq/normal_finite, finite native add/mul bridge and exact raw finite roundtrip prove new scalar specs. All downstream original equalities/specs retained. NOT_RUN exact new source.',
    'eligibility': 'Both magnitudes in[0x20000000,0x60000000); exponent64..191; zeros/subnormal/specials miss. Both exponents>=64 so hit never replaces the existing exsum<128 LowScale route.',
    'history_classification': 'Restricted revisit, not a wholly new numeric-conversion mechanism. R4 all-band numeric-mul passed but mul whole regressed3.75percent, while near-one separately improved~8.4percent normalized; this narrower guard excludes old tiny exponent50..65 pair domain and excludes low/high portions of spread. R6 two-compare E24..254 direct numeric add showed only~0.3percent whole public improvement in one discovery; this uses one joint compare and narrower eligibility on current result-guard parent. No performance inference from these changes.',
    'new_conditions_justifying_one_probe': ['Current a066 classifies actual result by self-BEq instead of the older two-input finite guard', 'One combined OR interval comparison instead of two independent intervals', 'Restricted E64..191 avoids R4 low-input tiny route and narrows spread exposure, preserving current LowScale on miss'],
    'costs': 'Two masks, two word subtractions, one OR and one comparison precede every scalar miss. Numeric conversion adds uint-to-float/table/mul work on mul hit. No cost or compiler elimination assumed. Regular native BMM/SinglePass loops unchanged; only replay/reference scalar callers can inherit these wrappers.',
    'validation_mode': 'statement-only first; full original gate if accepted',
    'proof_status': 'NOT_RUN',
    'kernel_replay': 'NOT_RUN',
    'axiom_audit': 'NOT_RUN',
    'checksum': 'NOT_RUN',
    'performance': 'UNKNOWN',
    'formal_submission': 'NOT_SUBMITTED',
    'attribution': 'All parent author/provenance preserved. Reuses existing in-file proofs; new joint guard/proof and wrappers session-authored.',
}
(HERE / 'manifest.json').write_text(json.dumps(manifest, indent=2, ensure_ascii=False) + '\n', encoding='utf-8')
evidence = {
    'state': 'PASS_STATIC_PARENT_SIZE_INVERSE_ONLY',
    'parent_sha256': PARENT_SHA,
    'candidate_sha256': manifest['candidate_sha256'],
    'candidate_bytes': len(candidate),
    'new_block_bytes': len(block),
    'delta_bytes': len(candidate) - len(source),
    'headroom_bytes': 256000 - len(candidate),
    'renamed_entries': [a.decode('utf-8').strip() for a, _ in replacements],
    'inverse_transform_recovers_parent_bytes': True,
    'all_existing_bmm_sum_runtime_bytes_preserved': True,
    'declaration_order': 'Both new scalar functions/spec inserted immediately before original add_eq/mul_eq; no reference to later R7Word.',
    'compiler_environment_or_proof_resource_changed': False,
    'Lean_full_gate_C_timing': 'NOT_RUN',
}
(HERE / 'static-precheck.json').write_text(json.dumps(evidence, indent=2, ensure_ascii=False) + '\n', encoding='utf-8')
print(json.dumps({k: manifest[k] for k in ('candidate', 'candidate_sha256', 'candidate_bytes', 'proof_status')}))
