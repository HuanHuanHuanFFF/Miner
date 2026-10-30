"""Independent owned-recipe reconstruction; no upstream source is written."""
from pathlib import Path
import datetime
import hashlib
import importlib.util
import json
import sys

sys.dont_write_bytecode = True
HERE = Path(__file__).resolve().parent
C = HERE.parent / 'board-frontier'
ROUND = HERE.parents[1]


def load(name):
    spec = importlib.util.spec_from_file_location('r27_review_' + name, C / (name + '.py'))
    mod = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(mod)
    return mod


def sha(data):
    return hashlib.sha256(data).hexdigest()


base = (ROUND / 'competition-state/source-private/submission23-Kernel.lean').read_bytes()
formal = load('build_rms_native_finish').transform(base)
cost = load('build_rms_native_cost').transform(base, variant='rms-native-cost')
request = json.loads((C / 'CI-REQUEST-RMS-NATIVE-FINISH.json').read_text(encoding='utf8'))
assert sha(formal) == request['candidate_sha256']
assert sha(cost) == request['native_cost']['candidate_sha256']
helper = (C / 'RmsNativeFinish.lean.inc').read_text(encoding='utf8')
runtime = helper.split('lemma R27RmsFinish_eq', 1)[0]
assert runtime in formal.decode().replace('\r\n', '\n')
assert runtime in cost.decode().replace('\r\n', '\n')
assert b'theorem correct:Obligation kernels:=' in formal
assert b'theorem correct:' not in cost
assert b'theorem retainedCorrect:Obligation retainedKernels:=' in cost
assert 'norm := ⟨R27RmsNorm,MYbc⟩'.encode() in cost

result = {
    'at_utc': datetime.datetime.now(datetime.timezone.utc).isoformat(),
    'state': 'INDEPENDENT_SOURCE_RECONSTRUCTION_AND_MATH_INTERFACE_REVIEW_ONLY',
    'base_sha256': sha(base),
    'formal_sha256': sha(formal), 'formal_bytes': len(formal),
    'cost_sha256': sha(cost), 'cost_bytes': len(cost),
    'shared_terminal_runtime_text_identical_after_line_ending_normalization': True,
    'formal_actual_call': 'Ybb2 output uses R27RmsFinish; T4b rewrites unconditional R27RmsFinish_eq.',
    'formal_acceptance': 'UNKNOWN: no Lean or original all12 result in this review.',
    'cost_proof_boundary': 'retainedCorrect proves old retainedKernels only; new kernels has no correct.',
    'math_review': [
        'Nonpositive denominator returns the exact old Ya7 call.',
        'Yf multiplication fits UInt64 because each mantissa is below 2^24; K4 is the existing exact product bridge.',
        'Zero product returns positive zero, matching old Ya7 sign masking by Pn != 0; no dot-of-signed-zero rule is imported here.',
        'Native branch checks D <= N. Positive sv dw supplies positive mantissa D; mantissa bound supplies D < 2^40.',
        'U=idx(w)+idx(g) is at most 508; V=idx(dw)+22 is at most 276. Both satisfy existing rrsGe limits below 2^20 without UInt64 wrap.',
        'E=idx(w)+idx(g)-idx(dw)-149 gives E+127=U-V, including the required +22 offset.',
        'rrsGe retains its normal-range fallback; neither underflow nor overflow is silently clamped by this patch.',
        'No mathematical counterexample was identified in this source review. This does not establish tactic execution or native gain.'
    ],
    'difference_from_word_dot_endpoint': 'RMS is one rational product divided by a positive rounded denominator; it does not reuse the body-only YL bias offset that had the 23-bit mismatch.',
    'next_decision': 'Use actual complete-model cost; repair exact compiler goals only if this source is selected. No duplicate full proof review absent changes.',
    'source_handling': 'Whole upstream input and reconstructed candidates remained in memory only; only owned recipe hashes and review were written.',
    'input_hashes': {name: sha((C / name).read_bytes()) for name in (
        'build_rms_native_finish.py', 'build_rms_native_cost.py', 'RmsNativeFinish.lean.inc')}
}
(HERE / 'rms-interface-review.json').write_text(json.dumps(result, indent=2), encoding='utf8')
print(json.dumps({k: result[k] for k in ('state', 'formal_sha256', 'formal_bytes', 'cost_sha256', 'cost_bytes')}))

