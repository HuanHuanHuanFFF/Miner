"""Replace native middle multiplication by direct UInt64 RNE/field packing."""
from pathlib import Path
from datetime import datetime, timezone
import hashlib
import json

OUT = Path(__file__).resolve().parent
ROOT = OUT.parents[4]
C = ROOT / 'competitions/floatlib/candidates'
parent = C / 'f01-r14-dev-native-exponent1/Kernel.lean'
raw = parent.read_bytes()
assert hashlib.sha256(raw).hexdigest() == '913d715b19be45a82bf45ce9af528b9001bbd62d49e3520bf2504f566145ca03'
model = (OUT / 'astra-exponent-shift-model-draft.lean').read_bytes()
algebra = (OUT / 'astra-exponent-shift-algebra-draft.lean').read_bytes()
bias = (OUT / 'astra-biased-rne1.lean').read_bytes()
integer = (OUT / 'development-integer-normal-draft.lean').read_bytes()
assert hashlib.sha256(model).hexdigest() == 'b2bb153c1e20e2e7ab0046f0e25583c4645cc5fc69ce9f94a2bbd482909a86f8'
assert hashlib.sha256(algebra).hexdigest() == '28f518f721fc1f076324dbab8c0525f6f0e9a5e70c2fcbf078bac7829c437b3f'
assert hashlib.sha256(bias).hexdigest() == '3515b1819897ad3d230f53d12375b85987fcf8678779e7428f4a78e693b65b0c'
text, middle = raw.decode(), model.decode()
assert text.count(middle) == 1 and text.count(algebra.decode()) == 1
first = middle.index('/-- The only floating arithmetic')
fields = middle.index('@[inline] def ex ', first)
core = middle.index('@[inline] def core ', fields)
tail = middle.index('theorem core_model ', core)
prefix = middle[:first] + middle[fields:core] + '\nend Submission.R14ExponentShift\n'
new_core = '''
namespace Submission.R14ExponentShift
open FloatLib.Floats Competition
open FloatLib.Floats.Formats.BinaryInterchange

@[inline] def core (u v : UInt32) : UInt32 := R14DIntegerNormal.core u v

theorem core_word (u v : UInt32)
    (hs : 128 ≤ R2W01c.wordExp u + R2W01c.wordExp v)
    (hs' : R2W01c.wordExp u + R2W01c.wordExp v ≤ 380) :
    core u v = Model.NativeBinary32.mkBits
      (Bool.xor (R2W01c.wordSign u) (R2W01c.wordSign v))
      (middleExponent (product (R2W01b.mantissa u) (R2W01b.mantissa v)) +
        R2W01c.wordExp u + R2W01c.wordExp v - 300)
      (storedFraction (product (R2W01b.mantissa u) (R2W01b.mantissa v))) := by
  exact R14DIntegerNormal.core_word u v hs

'''
new_middle = prefix + '\n' + bias.decode() + '\n' + integer.decode() + '\n' + new_core + middle[tail:]
text = text.replace(middle, new_middle).replace(algebra.decode(), '')
assert 'R14ExponentAlgebra.' not in text and 'first_product_bits' not in text
assert text.count('theorem core_word ') == 2  # own direct-fields proof and its adapter
result = text.encode()
budget = dict(at_utc=datetime.now(timezone.utc).isoformat(), candidate_bytes=len(result), limit=256000,
              removed_native_middle_bytes=tail - first - (core - fields), removed_unused_algebra_bytes=len(algebra),
              integer_component_bytes=len(integer), bias_component_bytes=len(bias), complete_proof_attempt=True, compiled=False)
(OUT / 'development-integer-exponent-budget.json').write_bytes((json.dumps(budget, indent=2) + '\n').encode())
assert len(result) <= 256000, budget
folder = C / 'f01-r14-dev-integer-exponent1'
assert not folder.exists()
folder.mkdir()
(folder / 'Kernel.lean').write_bytes(result)
record = dict(candidate=folder.name, candidate_file='Kernel.lean', candidate_sha256=hashlib.sha256(result).hexdigest(),
              candidate_bytes=len(result), created_at_utc=datetime.now(timezone.utc).isoformat(), validation_mode='full-gate',
              proof_status='COMPLETE_SOURCE_PROOF_ATTEMPT_NOT_COMPILED', performance='NOT_RUN',
              parent='f01-r14-dev-native-exponent1', parent_sha256=hashlib.sha256(raw).hexdigest(),
              mechanism='Exact normal domain: UInt64 24x24 product, highest bit selects shift23/24, biased ties-to-even rounding, direct carry/exponent/fraction/sign packing. No Float32 cast/mul/toBits in this fast core. Same original acyclic scalar fallback and full-input spec composition.',
              source_budget=budget,
              components=[dict(path=(OUT / n).relative_to(ROOT).as_posix(), sha256=hashlib.sha256(data).hexdigest(), bytes=len(data)) for n, data in [('development-integer-normal-draft.lean', integer), ('astra-biased-rne1.lean', bias)]],
              proof_changes='Native first-product theorem and raw exponent translation proof replaced by direct word field identities; unused entire exponent-algebra namespace removed only from this new source. Original913d/5677 remain unchanged. Remaining model/spec/guard/fallback chain retained.',
              limits='All arithmetic and all source-level proof attempts remain NOT_COMPILED. Independent39720 selected host cases support runtime math only. Actual source must pass original complete gate, caller inspection and fresh paired confirmations.')
(folder / 'manifest.json').write_bytes((json.dumps(record, ensure_ascii=False, indent=2) + '\n').encode())
(OUT / 'development-integer-exponent-build.json').write_bytes((json.dumps(record, ensure_ascii=False, indent=2) + '\n').encode())
print(json.dumps({key: record[key] for key in ('candidate', 'candidate_sha256', 'candidate_bytes', 'proof_status', 'performance')}))
