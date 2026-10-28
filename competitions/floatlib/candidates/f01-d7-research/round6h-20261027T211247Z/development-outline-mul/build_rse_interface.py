"""Read-only accepted9038 intake; materialize small runtime/boundary/proof fragments only."""
from pathlib import Path
import hashlib
import json
import re

HERE = Path(__file__).resolve().parent
ROOT = next(p for p in HERE.parents if (p / 'AGENTS.md').is_file())
OLD = ROOT / 'competitions/floatlib/candidates/f01-r14-dev-mul-cache-rse2/Kernel.lean'
B2 = ROOT / 'competitions/floatlib/candidates/f01-r15-dev-packed-b2-1/Kernel.lean'
sha = lambda b: hashlib.sha256(b).hexdigest()


def definition(text, name):
    m = re.search(r'(?m)^@\[inline\] def ' + re.escape(name) + r'\b', text)
    assert m, name
    nxt = re.search(r'(?m)^(?:@\[inline\] def |(?:private )?(?:theorem|def|abbrev) |namespace |end )', text[m.end():])
    end = m.end() + nxt.start() if nxt else len(text)
    return text[m.start():end].rstrip() + '\n'


def main():
    raw, b2 = OLD.read_bytes(), B2.read_bytes()
    assert sha(raw) == '9038f8d653f030a8812c3187733488f70995253a1a7b284759c4f58b96378c19'
    assert sha(b2) == '622d8394a7127e93dcaf992c62c6dfcff7208d212738409a5e34525dfafd1a58'
    text, retained = raw.decode(), b2.decode()
    start = text.index('namespace Submission.R14NativeProduct')
    end = text.index('namespace Submission\nopen FloatLib.Floats Competition\n\n@[inline] def mul (x y', start)
    support = text[start:end]
    word_start = support.index('namespace Submission.R14DIntegerNormal')
    word_end = support.index('end Submission.R14DIntegerNormal', word_start)
    word = support[word_start:word_end]
    first_exp = support[support.index('namespace Submission.R14ExponentShift'):word_start]
    last_exp = support[support.index('namespace Submission.R14ExponentShift', word_end):]
    imports = 'open FloatLib.Floats Competition\nopen FloatLib.Floats.Formats.BinaryInterchange\n'
    exp0 = '\n'.join(definition(first_exp, x) for x in ('ex', 'sign'))
    words = '\n'.join(definition(word, x) for x in ('productWord', 'highWord', 'shiftWord', 'roundedWord', 'carryWord', 'exponentWord', 'fractionWord', 'core'))
    exp1 = '\n'.join(definition(last_exp, x) for x in ('core', 'eligible', 'guardedMul'))
    boundary = '''namespace Submission.R22RseCold
open Competition
@[noinline] def retainedB2 (x y : Binary32) : Binary32 := Submission.mul x y
@[inline] def inlineOld (x y : Binary32) : Binary32 :=
  R14ExponentShift.guardedMul Submission.mul x y
@[inline] def outlined (x y : Binary32) : Binary32 :=
  R14ExponentShift.guardedMul retainedB2 x y
end Submission.R22RseCold
'''
    runtime = ('namespace Submission.R14ExponentShift\n' + imports + exp0 + 'end Submission.R14ExponentShift\n\n'
               'namespace Submission.R14DIntegerNormal\n' + imports + words + 'end Submission.R14DIntegerNormal\n\n'
               'namespace Submission.R14ExponentShift\n' + imports + exp1 + 'end Submission.R14ExponentShift\n\n' + boundary)
    assert not re.search(r'\b(log2|fastLog2|roundP|toFloat32|ofFloat32|toBits|scaleTable)\b', runtime)
    assert 'abbrev productNat' not in runtime and 'R14ExponentShift.product ' not in runtime
    assert runtime.count('@[inline] def ') == 15 and runtime.count('@[noinline] def ') == 1
    shared = {}
    for name in ('rse', 'rseAny', 'mkW', 'mantissa'):
        old_def, new_def = definition(text[:start], name), definition(retained, name)
        shared[name] = {'old_text_sha256': sha(old_def.encode()), 'B2_text_sha256': sha(new_def.encode()),
                        'text_equal': old_def == new_def}
    assert all(v['text_equal'] for v in shared.values()), shared
    out = HERE / 'rse-interface'
    out.mkdir(exist_ok=True)
    for name, content in (('Runtime.lean.inc', runtime), ('ColdBoundary.lean.inc', boundary), ('AcceptedMathSupport.lean.inc', support)):
        (out / name).write_bytes(content.encode())
    assert (out / 'ProofTransport.lean.inc').is_file()
    manifest = {
        'state': 'LOW_MARGINAL_COST_RESERVE_ONLY_NOT_QUEUED', 'source': {'path': str(OLD), 'sha256': sha(raw), 'bytes': len(raw), 'historical_full_gate_run': 40155753018},
        'current_B2_sha256': sha(b2), 'files': [{'file': name, 'bytes': (out / name).stat().st_size, 'sha256': sha((out / name).read_bytes())}
                                             for name in ('Runtime.lean.inc', 'ColdBoundary.lean.inc', 'AcceptedMathSupport.lean.inc', 'ProofTransport.lean.inc')],
        'copied_runtime_definitions': ['R14ExponentShift.ex', 'R14ExponentShift.sign', 'R14DIntegerNormal.productWord/highWord/shiftWord/roundedWord/carryWord/exponentWord/fractionWord/core',
                                       'R14ExponentShift.core/eligible/guardedMul'],
        'runtime_source_fidelity': 'Each originalruntime definition body copiedexactly; onlynamespace/open wrappers andnewcoldboundary added. No retained-product rewrite, guard/domainchange, IEEEproofornewNatBias.',
        'shared_B2_primitives': shared,
        'source_hot_path': 'UInt64product; high=P>>47; shift23+high; rseAny; carry=rounded>>24; exponent/fraction packing. No reachablelog2/FPcast/table. rseAny stillhasgenericshift checks andrse remainder/half/2comparisons/tieparity.',
        'historical_negative': {'baseline': 'df5c f01-d12-scalar-combined, notB2', 'whole': 1.0471437276654516, 'mul': 1.2908011496963538, 'gain_p05': -0.04566368078493384,
                                'old_source': '9038; originalfull25PASS but performancePARK. No scoretransfer.'},
        'old_selected_caller_ASM': 'UNKNOWN: 9038 run codegen_present=false. OtherR22ASM sectionheadings namingR14 symbols containno selectedbody andarenot evidence.',
        'new_cost_premise': 'Onlystatic noinlineB2fallback boundary maydelete sharedcallee-save/frame; old proofmodeldoesnot establish codegen orspeed. MusttraceactualselectedMain callback, samebinary staticIO control/inlineOld/outlined, fullguard/miss/Suitecost.',
        'proof_interface': {'minimal_transport_fragment': 'ProofTransport.lean.inc;requiresfullMathSupport;NOT_COMPILED',
                            'normal_domain': 'Both exponents1..254, sum128..380 exactly; originaleligible unchanged.',
                            'word_rounding': 'R14DIntegerNormal.roundedWord_nat composesFastMul.rseAny_eq +FixedWord.roundShiftRightEven_toNat; noBranchlessRNESeed dependency.',
                            'public_transport': 'R14ExponentShift.guardedMul_spec fallback hf; newnoinlineB2 fallback isdefinitionallyB2mul, so existingIEEE/model proofreused afterfreshintegration/replay.',
                            'key_roots': ['Submission.R14DIntegerNormal.roundedWord_nat', 'Submission.R14DIntegerNormal.core_word', 'Submission.R14ExponentShift.core_model',
                                          'Submission.R14ExponentShift.core_spec', 'Submission.R14ExponentShift.eligible_conditions', 'Submission.R14ExponentShift.guardedMul_spec']},
        'composition': {'diagnostic': 'B2+Runtime fragment only; public4endpoints unchanged. Requires freshcompile. Do notalsoappendMathSupport becauseit duplicatesruntime names.',
                        'proof_later': 'B2+AcceptedMathSupport+ColdBoundary, or equal-lengthrename Submission->R22RseBase thennewpublicaliases. RetainoldmaxRecDepth8192 sourceoption, nothighercap. Freshfullgate/roots mandatory.',
                        'B2_plus_support_bytes_before_wrapper': len(b2) + len(support.encode()), 'headroom_before_wrapper': 256000 - len(b2) - len(support.encode()),
                        'recursion_guard': 'On9038 existingpublicmul alreadyisRSEguard; fallbackmustbeoldmulBeforeExponent, notthatpublicmul. OnB2carrier newretainedB2maycallSubmission.mul. Neverwrapnewpublicmul asitsownfallback.'},
        'decision': 'No standaloneCI orlargeproofinvestment thiswindow. Notlog2-blocked, but old29%MUL negative plus heavierRSE mechanics lowerpriority; onlyone lowmarginal actualcaller/cost screen ifDselects andcurrentacceptanceunaffected.',
        'new_typecheck': 'NOT_RUN', 'new_caller_ASM': 'NOT_RUN', 'new_performance': 'NOT_RUN', 'new_public_Kernel_materialized': False
    }
    (out / 'manifest.json').write_text(json.dumps(manifest, ensure_ascii=False, indent=2) + '\n', encoding='utf-8')
    print(json.dumps({'runtime_bytes': len(runtime.encode()), 'runtime_sha256': sha(runtime.encode()),
                      'support_bytes': len(support.encode()), 'B2_plus_support_bytes': len(b2) + len(support.encode()),
                      'shared_primitives_equal': True, 'reachable_hot_log2': False, 'status': 'RESERVE_NOT_RUN_NOT_QUEUED'}))


if __name__ == '__main__':
    main()
