from pathlib import Path
import hashlib, json

HERE = Path(__file__).resolve().parent
ROOT = next(p for p in HERE.parents if (p / 'AGENTS.md').exists())
BASE = ROOT / 'competitions/floatlib/candidates/f01-r21-dev-scaled-u32-bridge-probe1/Kernel.lean'
OLD = ROOT / 'competitions/floatlib/candidates/f01-d7-research/round11h-20261025T173831Z/development-u64-roundtrip-repair1-fragment.lean'
base_bytes = BASE.read_bytes()
assert hashlib.sha256(base_bytes).hexdigest() == '56cdb076b82fb8212dfa7fcd535928cc96f5fa384c62c6647975ac9587fc1e35'
old = OLD.read_text(encoding='utf-8')
chunks = [old[old.index('namespace Submission.R14NatNormal'):old.index('namespace Submission.R17UInt64Integer')]]
def declaration(name, following):
    return old[old.index(name):old.index(following, old.index(name))]
chunks += [
    'namespace Submission.R17UInt64Integer\nopen FloatLib.Floats\nopen FloatLib.Floats.Formats.BinaryInterchange\nopen FloatLib.Numerics\n\n',
    declaration('def roundedShift', 'def roundedInteger'),
    declaration('theorem rounded_shift_cases', 'theorem rounded_integer_bounds'),
    declaration('theorem uint64_model_eq_roundDyadic', 'theorem uint64_roundtrip'),
    declaration('theorem product_word_nat', 'theorem numeric_integer_product'),
    'end Submission.R17UInt64Integer\n',
]
support = '\n'.join(chunks).encode('utf-8')
(HERE / 'Support-r17-minimal.lean.inc').write_bytes(support)
new = (HERE / 'Bridge-product-scaled.lean.inc').read_bytes()
kernel = base_bytes + b'\nsection R22ScaledProductProbe\nset_option maxRecDepth 8192\n' + support + b'\n' + new + b'\nend R22ScaledProductProbe\n'
(HERE / 'Kernel-probe1.lean').write_bytes(kernel)
roots = [
    'Submission.R17UInt64Integer.uint64_model_eq_roundDyadic',
    'Submission.R17UInt64Integer.native_uint64_decode',
    'Submission.R17UInt64Integer.product_word_nat',
    'Submission.R21ScaledU32.native_integer_product_decode',
    'Submission.R21ScaledU32.integer_product_scaled_fields',
]
(HERE / 'HelperAudit-probe1.lean.inc').write_text('\n'.join('#print axioms '+r for r in roots)+'\n', encoding='utf-8')
files = ['Kernel-probe1.lean','Support-r17-minimal.lean.inc','Bridge-product-scaled.lean.inc','HelperAudit-probe1.lean.inc']
manifest = {
    'status':'NOT_RUN', 'base_sha256':hashlib.sha256(base_bytes).hexdigest(),
    'old_support_source':str(OLD.relative_to(ROOT)).replace('\\','/'),
    'old_support_source_sha256':hashlib.sha256(OLD.read_bytes()).hexdigest(),
    'public_operations':'UNCHANGED_B2',
    'scope':'Actual UInt64 product to native Float32 decode and R21 scaled fields; no full public MUL proof.',
    'new_roots':roots[-2:], 'explicit_helper_audit':roots,
    'files': {f: {'bytes':(HERE/f).stat().st_size,'sha256':hashlib.sha256((HERE/f).read_bytes()).hexdigest()} for f in files},
    'missing':['normalCore repack equals normal model fields','original guard implies normal safe exponent band','guardedMul spec preserving fallback','full official gate and performance'],
}
(HERE/'probe1-manifest.json').write_text(json.dumps(manifest,indent=2)+'\n',encoding='utf-8')
print(json.dumps(manifest,indent=2))
