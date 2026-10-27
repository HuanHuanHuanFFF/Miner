"""Create an R16 proof candidate from exact read-only B2/R14 sources. No Lean or CI."""
from pathlib import Path
from datetime import datetime, timezone
import hashlib, json

HERE = Path(__file__).resolve().parent
ROOT = next(p for p in HERE.parents if (p / 'AGENTS.md').exists())
BASE = ROOT / 'competitions/floatlib/candidates/f01-r15-dev-packed-b2-1/Kernel.lean'
OLD = ROOT / 'competitions/floatlib/candidates/f01-r14-dev-mul-cache-rse2/Kernel.lean'
EXPECTED_BASE = '622d8394a7127e93dcaf992c62c6dfcff7208d212738409a5e34525dfafd1a58'
assert hashlib.sha256(BASE.read_bytes()).hexdigest() == EXPECTED_BASE
base = BASE.read_text(encoding='utf-8')
old = OLD.read_text(encoding='utf-8')

def namespace_once(name):
    start = old.index('namespace ' + name + '\n')
    end = old.index('end ' + name, start) + len('end ' + name)
    return old[start:end] + '\n'

def between(text, start, end):
    a = text.index(start)
    return text[a:text.index(end, a)].rstrip() + '\n'

np = namespace_once('Submission.R14NativeProduct')
nn = namespace_once('Submission.R14NatNormal')
eb = namespace_once('Submission.R14ExponentShift')
mf = between(old, 'theorem model_mul_normal_fields ', 'theorem core_model ')
tail = between(old, 'theorem core_model ', 'end Submission.R14ExponentShift\n\nnamespace Submission\nopen FloatLib.Floats Competition\n\n@[inline] def mul (')
new = (HERE / 'native-repack-new.lean').read_text(encoding='utf-8')
fragment = '\n\n'.join(['section R16NativeRepackProof\nset_option maxRecDepth 8192\n', np, nn, eb,
    'namespace Submission.R14ExponentShift\nopen FloatLib.Floats Competition\nopen FloatLib.Floats.Formats.BinaryInterchange\n',
    mf, new, tail, 'end Submission.R14ExponentShift\nend R16NativeRepackProof\n'])

start = base.index('@[inline] def mul (x y : Binary32) : Binary32 :=\n  let ex :=')
end = base.index('theorem add_eq :', start)
fallback = base[start:end].replace('def mul (', 'def mulBeforeR16NativeRepack (', 1)
fallback = fallback.replace('theorem mul_spec (', 'theorem mulBeforeR16NativeRepack_spec (', 1)
fallback = fallback.replace(' : mul x y =', ' : mulBeforeR16NativeRepack x y =', 1)
fallback = fallback.replace('  unfold mul\n', '  unfold mulBeforeR16NativeRepack\n', 1)
public = '''namespace Submission
open FloatLib.Floats Competition

@[inline] def mul (x y : Binary32) : Binary32 :=
  R14ExponentShift.guardedMul mulBeforeR16NativeRepack x y

theorem mul_spec (x y : Binary32) : mul x y = ExecFloat.Spec.mul x y := by
  exact R14ExponentShift.guardedMul_spec mulBeforeR16NativeRepack
    mulBeforeR16NativeRepack_spec x y

'''
candidate = base[:start] + fallback + '\nend Submission\n\n' + fragment + '\n' + public + base[end:]
out = HERE / 'Kernel-native-repack.lean'
out.write_bytes(candidate.encode('utf-8'))
(HERE / 'native-repack-complete-fragment.lean').write_bytes(fragment.encode('utf-8'))
assert out.stat().st_size <= 256000, out.stat().st_size
for forbidden in ('sorry', 'admit', 'unsafe', 'native_decide', 'axiom ', '@[extern', 'implemented_by'):
    assert forbidden not in fragment, forbidden

def item(path):
    data = path.read_bytes()
    return {'path': str(path.relative_to(ROOT)), 'bytes': len(data), 'sha256': hashlib.sha256(data).hexdigest()}

manifest = {'created_utc': datetime.now(timezone.utc).isoformat(),
    'state': 'DRAFT_NOT_COMPILED',
    'source': item(out), 'baseline': item(BASE), 'reused_full_gate_math_source': item(OLD),
    'full_gate_math_source_run': 40155753018,
    'new_fragment': item(HERE / 'native-repack-new.lean'),
    'complete_fragment': item(HERE / 'native-repack-complete-fragment.lean'),
    'builder': item(Path(__file__)),
    'reused_exact_namespace_hashes': {n: hashlib.sha256(t.encode()).hexdigest() for n, t in
      [('R14NativeProduct',np), ('R14NatNormal',nn), ('R14ExponentShift-base',eb), ('model_mul_normal_fields',mf), ('core_model_through_guarded_spec',tail)]},
    'runtime_change': 'normal original raw exponents1..254 and sum128..380: two exact UInt32 casts, one native Float32 multiply, toBits, explicit field repack; original B2 mul fallback',
    'proof_recursion_option': '8192 scoped to inserted section, matching reused full-gated R14 proof source; original gate/toolchain untouched',
    'not_claimed': ['Lean statement', 'helper axiom audit', 'kernel replay', 'full gate', 'generated caller cost', 'performance'],
    'input_tokens':'UNKNOWN', 'cached_input_tokens':'UNKNOWN','output_tokens':'UNKNOWN','reasoning_tokens':'UNKNOWN','ci_occupancy_seconds':0}
(HERE / 'source-manifest.json').write_text(json.dumps(manifest, ensure_ascii=False, indent=2)+'\n', encoding='utf-8')
print(json.dumps({'state':manifest['state'], 'source':manifest['source'], 'fragment_bytes':len(fragment.encode())}, indent=2))
