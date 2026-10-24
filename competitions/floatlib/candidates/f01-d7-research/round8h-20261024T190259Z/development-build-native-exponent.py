"""Wire the frozen math handoff into the real public mul, with acyclic fallback."""
from pathlib import Path
from datetime import datetime, timezone
import hashlib
import json

OUT = Path(__file__).resolve().parent
ROOT = OUT.parents[4]
CANDIDATES = ROOT / 'competitions/floatlib/candidates'
parent = CANDIDATES / 'f01-r14-dev-compact-base/Kernel.lean'
raw = parent.read_bytes()
assert hashlib.sha256(raw).hexdigest() == '3c6af73f9d679e9831ac8c4abb9f0e6d41b61718301dd045bedd2402e980632a'
proof = CANDIDATES / 'f01-r14-math-exponent-shift-proof1'
proof_raw = (proof / 'Kernel.lean').read_bytes()
assert hashlib.sha256(proof_raw).hexdigest() == '56773d4dcc464c87a269ed33ff363800257cba38eacb78c3c27051d8aa77433d'
manifest = json.loads((proof / 'manifest.json').read_bytes())
fragments = []
for record in manifest['fragments']:
    path = ROOT / record['path']
    assert path.resolve().is_relative_to(OUT)
    data = path.read_bytes()
    assert len(data) == record['bytes'] and hashlib.sha256(data).hexdigest() == record['sha256']
    fragments.append(data.decode())
text = raw.decode()
start = text.index('@[inline] def mul (x y : Binary32) : Binary32 :=\n  let ex :=')
end = text.index('theorem add_eq : add = ExecFloat.add :=', start)
# Include the blanked original prose lines before add_eq only as whitespace.
old = text[start:end]
assert old.count('@[inline] def mul ') == 1 and old.count('theorem mul_spec ') == 1
fallback = old.replace('def mul (', 'def mulBeforeExponent (').replace('theorem mul_spec (', 'theorem mulBeforeExponent_spec (')
fallback = fallback.replace(': mul x y = ExecFloat.Spec.mul x y', ': mulBeforeExponent x y = ExecFloat.Spec.mul x y')
fallback = fallback.replace('  unfold mul\n', '  unfold mulBeforeExponent\n')
assert 'theorem mulBeforeExponent_spec (x y : Binary32) : mulBeforeExponent x y =' in fallback
assert 'theorem mul_spec' not in fallback and '  unfold mul\n' not in fallback
math = '\nset_option maxRecDepth 8192\n\n' + '\n'.join(fragments)
wrapper = '''
namespace Submission
open FloatLib.Floats Competition

@[inline] def mul (x y : Binary32) : Binary32 :=
  R14ExponentShift.guardedMul mulBeforeExponent x y

theorem mul_spec (x y : Binary32) : mul x y = ExecFloat.Spec.mul x y := by
  exact R14ExponentShift.guardedMul_spec mulBeforeExponent mulBeforeExponent_spec x y

'''
result = (text[:start] + fallback + '\nend Submission\n' + math + wrapper + text[end:]).encode()
assert len(result) <= 256000
assert result.count(b'import ContractTensor') == 1
assert result.index(b'def guardedMul ') < result.index(b'def mul (x y : Binary32) : Binary32 :=\n  R14ExponentShift.')
assert result.index(b'def mul (x y : Binary32) : Binary32 :=\n  R14ExponentShift.') < result.index(b'def referenceBmm ')
folder = CANDIDATES / 'f01-r14-dev-native-exponent1'
assert not folder.exists()
folder.mkdir()
(folder / 'Kernel.lean').write_bytes(result)
record = dict(candidate=folder.name, candidate_file='Kernel.lean', candidate_sha256=hashlib.sha256(result).hexdigest(),
              candidate_bytes=len(result), created_at_utc=datetime.now(timezone.utc).isoformat(),
              parent='f01-r14-dev-compact-base', parent_sha256=hashlib.sha256(raw).hexdigest(),
              validation_mode='full-gate', proof_status='NOT_COMPILED_FROZEN_CHAIN_INTEGRATED', performance='NOT_RUN',
              mathematical_handoff=dict(candidate=proof.name, sha256=hashlib.sha256(proof_raw).hexdigest(), fragments=manifest['fragments']),
              mechanism='Actual public mul uses two UInt32 mantissa casts, one Float32 multiply, raw exponent translation/sign in the exact normal domain; original public mul renamed as acyclic fallback. Public referenceBmm and later raw replay see the new mul; native packed dot loops retain their own native multiply.',
              integration='Close Submission before absolute math namespaces; reopen before new public mul/spec and original add_eq/mul_eq/referenceBmm. The theorem type, definition and unfold are all renamed consistently. Existing global imports and tensor tail remain original.',
              options='maxRecDepth8192 after the old mul fallback; bounded by track rules. No new extern, unsafe, implemented_by, axiom or source-level floating reassociation.',
              limits='Complete proof-only chain has not yet compiled; integrated candidate is static preparation only, not accepted or benchmarked. Requires exact public full gate and independent frozen confirmations.')
(folder / 'manifest.json').write_bytes((json.dumps(record, ensure_ascii=False, indent=2) + '\n').encode())
(OUT / 'development-native-exponent-build.json').write_bytes((json.dumps(record, ensure_ascii=False, indent=2) + '\n').encode())
print(json.dumps({key: record[key] for key in ('candidate', 'candidate_sha256', 'candidate_bytes', 'proof_status', 'performance')}))
