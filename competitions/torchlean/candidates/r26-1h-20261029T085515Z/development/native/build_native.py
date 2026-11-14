"""Assemble owned runtime-only probes; no local Lean/native compilation."""
from pathlib import Path
import hashlib
import json
import re
from datetime import datetime, timezone

HERE = Path(__file__).resolve().parent
ROOT = next(p for p in HERE.parents if (p / 'AGENTS.md').is_file())
R25 = ROOT / 'competitions/torchlean/candidates/r25-90m-20261029T064916Z'
BASE = R25 / 'development/contract-port/norm-cache-proof1/Kernel.lean'
FP = R25 / 'development/fp-model-probe/Kernel.lean'
R24 = ROOT / 'competitions/floatlib/candidates/f01-d7-research/round7h-20261028T203856Z'

def sha(data):
    return hashlib.sha256(data).hexdigest()

def retained_prefix():
    raw = BASE.read_bytes()
    assert sha(raw) == 'bcb8172381346b26afc69e2582442510865f74415c657d7ee208045474ca1ea7'
    s = raw.decode('utf-8')
    assert s.count('def kernels : Kernels where') == 1
    s = s.replace('def kernels : Kernels where', 'def retainedKernels : Kernels where')
    s = s.replace('theorem correct : Obligation kernels := by',
                  'theorem retainedCorrect : Obligation retainedKernels := by')
    s = s.replace('simp only [Obligation, kernels, specKernels,',
                  'simp only [Obligation, retainedKernels, specKernels,')
    return s

def fp_probe():
    old = FP.read_text(encoding='utf-8')
    suffix = old[old.index('namespace Submission.FastMul'):]
    suffix = suffix.replace('namespace Submission.R25FpModel', 'namespace Submission.R26FpModel')
    suffix = suffix.replace('end Submission.R25FpModel', 'end Submission.R26FpModel')
    suffix = suffix.replace('R25FpModel.kernels', 'R26FpModel.kernels')
    suffix = suffix.replace('  if inW < 31 then linearWith dotFn',
        '  if rows * outW == 0 then #[]\n  else if inW < 31 then linearWith dotFn')
    suffix = suffix.replace('  if k < 32 then gemmWith dotFn',
        '  if batch * (m * n) == 0 then #[]\n  else if k < 32 then gemmWith dotFn')
    return retained_prefix() + '\n\n' + suffix

def word_probe():
    fp = FP.read_text(encoding='utf-8')
    fastlog = fp[fp.index('namespace Submission.FastMul'):fp.index('/- Portable primitive COST')]
    portable = (R24 / 'development-dot-cost/PortableF64Dot-tail-v2.lean.inc').read_text(encoding='utf-8')
    cost = (R24 / 'development-broad/ExactDotCost.lean.inc').read_text(encoding='utf-8')
    cost = cost[:cost.index('def referencePrepared')] + '\nend Submission.R24ExactDotCost\n'
    tier = (R24 / 'development-broad/ExactDotTiered.lean.inc').read_text(encoding='utf-8')
    tier = tier[:tier.index('@[inline] def exactPreparedV2')] + '\nend Submission.R24ExactDotTiered\n'
    return '\n\n'.join([retained_prefix(), fastlog, cost, tier, portable,
                          (HERE / 'WordFallback.lean.inc').read_text(encoding='utf-8'),
                          (HERE / 'Caller-word.lean.inc').read_text(encoding='utf-8')])

def shared_conv_probe():
    source = word_probe()
    entry = 'namespace Submission.R26WordModel'
    source = source.replace(entry,
        (HERE / 'Conv-shared.lean.inc').read_text(encoding='utf-8') + '\n\n' + entry, 1)
    source = source.replace('conv := ⟨conv2dWith dot, depthwiseWith dot⟩',
                            'conv := ⟨R26SharedConv.conv2d, R26SharedConv.depthwise⟩')
    return source

def raw_word_probe(explicit_bool=False):
    source = word_probe()
    source = source[:source.index('/- Runtime research only. A strict eligible64')]
    conv = (HERE / 'Conv-shared.lean.inc').read_text(encoding='utf-8')
    caller = (HERE / 'Caller-word.lean.inc').read_text(encoding='utf-8')
    conv = conv.replace('open R26WordFallback', 'open R26RawWord')
    caller = caller.replace('open R26WordFallback', 'open R26RawWord')
    caller = caller.replace('conv := ⟨conv2dWith dot, depthwiseWith dot⟩',
                            'conv := ⟨R26SharedConv.conv2d, R26SharedConv.depthwise⟩')
    raw = (HERE / 'RawWord.lean.inc').read_text(encoding='utf-8')
    if explicit_bool:
        raw = raw.replace('|| n > 1048576 then', '|| decide (n > 1048576) then')
        raw = raw.replace('|| n > 1073741824 ||', '|| decide (n > 1073741824) ||')
    return '\n\n'.join([source, raw, conv, caller])

def localize_instances(source, namespace):
    original = source
    match = re.search(r'^instance : Inhabited Prepared :=\n(.*?)(?=\ndef prepare)', source, re.M | re.S)
    assert match and source.count('\ninstance : Inhabited Prepared :=') == 1
    local = 'local instance : Inhabited ' + namespace + '.Prepared :=\n' + match[1]
    source = source[:match.start()] + 'local ' + source[match.start():]
    source = source.replace('open ' + namespace + '\n', 'open ' + namespace + '\n\n' + local + '\n')
    assert source.count(local) == 2, source.count(local)
    restored = source.replace('open ' + namespace + '\n\n' + local + '\n', 'open ' + namespace + '\n')
    restored = restored.replace('local instance : Inhabited Prepared :=', 'instance : Inhabited Prepared :=', 1)
    assert restored == original, 'Instance localization must be exactly reversible'
    return source

def official_finish_probe():
    source = raw_word_probe(explicit_bool=True)
    start = source.index('def prepare (raw : Array UInt32) : Prepared := Id.run do',
                         source.index('namespace Submission.R26RawWord'))
    end = source.index('@[inline] def baseIndex', start)
    source = source[:start] + (HERE / 'PrepareWordOnly.lean.inc').read_text(encoding='utf-8') + '\n' + source[end:]
    source = source.replace('def native64 (a b : Array UInt32)',
        (HERE / 'FinishOfficial.lean.inc').read_text(encoding='utf-8') + '\ndef native64 (a b : Array UInt32)', 1)
    source = source.replace('| 0 => R24ExactDotTiered.finish64 base negZero acc',
                            '| 0 => finishOfficial64 base negZero acc', 1)
    source = source.replace('| 0 => finish base negZero pLo pHi nLo nHi',
                            '| 0 => finishOfficial128 base negZero pLo pHi nLo nHi', 1)
    # Restrict the replacement to the fresh raw namespace. The earlier R24 cost
    # helper has a nativeLoop base case with the same text and must stay intact.
    assert '| 0 => finishOfficial128 base negZero pLo pHi nLo nHi' in source
    raw_start = source.index('namespace Submission.R26RawWord')
    old_native = source[:raw_start]
    raw_tail = source[raw_start:]
    if 'finishOfficial128' in old_native:
        old_native = old_native.replace('| 0 => finishOfficial128 base negZero pLo pHi nLo nHi',
                                        '| 0 => finish base negZero pLo pHi nLo nHi')
        raw_tail = raw_tail.replace('| 0 => finish base negZero pLo pHi nLo nHi',
                                    '| 0 => finishOfficial128 base negZero pLo pHi nLo nHi', 1)
    source = old_native + raw_tail
    start = source.index('@[inline] def attempt (left right : Prepared)', raw_start)
    end = source.index('@[inline] def dotPrepared', start)
    source = source[:start] + '@[inline] def attempt (_left _right : Prepared) : UInt32 := 0\n\n' + source[end:]
    return localize_instances(source, 'R26RawWord')

def publish(name, source, metadata):
    dst = HERE / name / 'Kernel.lean'
    dst.parent.mkdir(parents=True, exist_ok=True)
    data = source.encode('utf-8')
    if dst.exists() and dst.read_bytes() != data:
        raise RuntimeError(f'Frozen source would change: {dst}')
    dst.write_bytes(data)
    record = {'id': name, 'path': dst.relative_to(ROOT).as_posix(),
              'bytes': len(data), 'sha256': sha(data),
              'status': 'RUNTIME_PROBE_UNPROVED_NOT_COMPILED', **metadata}
    (HERE / name / 'source-receipt.json').write_text(
        json.dumps(record, indent=2) + '\n', encoding='utf-8')
    return record

def main():
    first = publish('fp1', fp_probe(), {
        'retained_prefix': BASE.relative_to(ROOT).as_posix(),
        'retained_original_sha256': sha(BASE.read_bytes()),
        'fp_original_sha256': sha(FP.read_bytes()),
        'entry': 'Submission.kernels',
        'proof_entry': 'Submission.retainedCorrect',
        'proof_covers': 'Submission.retainedKernels only',
        'changes': ['retained norm-cache runtime and original twelve proof retained',
                    'FP64 prepared row/column caches for linear and gemm',
                    'bias included as final term of the same inW+1 dot',
                    'cold FP64 dot for conv/depthwise, original dotFn on miss',
                    'empty dense output extents return before cache preparation'],
        'next_gate': 'owned native-only target; finite checksum versus golden retained/source; no adoption claim'})
    second = publish('fp-word2', word_probe(), {
        'retained_original_sha256': sha(BASE.read_bytes()),
        'entry': 'Submission.kernels', 'proof_entry': 'Submission.retainedCorrect',
        'proof_covers': 'Submission.retainedKernels only',
        'changes': ['FP64 attempt then exact signed62 or structural four-word128 fallback',
                    'row/column FP and word caches shared across dense dots',
                    'word loops use multiple UInt64 recursive arguments; no Id/tuple MAC state',
                    'nonfinite, subnormal nonzero, mismatched, or too-wide cases use original dotFn',
                    'old canonical-NaN research replay omitted entirely'],
        'next_gate': 'native full official-model finite checksums/timing; UNPROVED'})
    third = publish('fp-word-conv3', shared_conv_probe(), {
        'retained_original_sha256': sha(BASE.read_bytes()),
        'entry': 'Submission.kernels', 'proof_entry': 'Submission.retainedCorrect',
        'proof_covers': 'Submission.retainedKernels only',
        'parent_runtime': second['sha256'],
        'changes': ['same arithmetic as fp-word2',
                    'conv2d prepared input windows reused across output filters',
                    'conv2d/depthwise prepared filters reused across positions',
                    'unchanged ContractExact windowAt, term order, bias as last exact term',
                    'zero output extent returns before preparation'],
        'next_gate': 'full official-model finite checksum/timing; UNPROVED'})
    fourth = publish('fp-raw4', raw_word_probe(), {
        'retained_original_sha256': sha(BASE.read_bytes()),
        'entry': 'Submission.kernels', 'proof_entry': 'Submission.retainedCorrect',
        'proof_covers': 'Submission.retainedKernels only',
        'parent_runtime': third['sha256'],
        'changes': ['fused FloatArray and min/max preparation',
                    'no encoded UInt32 data array materialized',
                    'raw mantissa/index loops support all finite subnormal inputs inside width bound',
                    'same structural word64/128 and FP64 certificate; original dotFn outside bound',
                    'same shared dense/conv caller layouts'],
        'queue': 'SUPERSEDED_BY_FP_RAW5_EXPLICIT_BOOL',
        'next_gate': 'fresh raw-word Python model then official-model finite checksum/timing; UNPROVED'})
    fifth = publish('fp-raw5', raw_word_probe(explicit_bool=True), {
        'retained_original_sha256': sha(BASE.read_bytes()),
        'entry': 'Submission.kernels', 'proof_entry': 'Submission.retainedCorrect',
        'proof_covers': 'Submission.retainedKernels only',
        'parent_runtime': fourth['sha256'],
        'changes': ['same raw4 runtime, explicit decide in two Bool-or guards',
                    'preventive source elaboration fix; raw4 original preserved'],
        'queue': 'NEXT_DISCRIMINATOR_ONLY_IF_CI_THROUGHPUT_PERMITS',
        'next_gate': 'official-model finite checksum/timing; UNPROVED'})
    sixth = publish('fp-word-conv6-local', localize_instances(shared_conv_probe(), 'R26WordFallback'), {
        'retained_original_sha256': sha(BASE.read_bytes()),
        'entry': 'Submission.kernels', 'proof_entry': 'Submission.retainedCorrect',
        'proof_covers': 'Submission.retainedKernels only',
        'parent_runtime': third['sha256'],
        'changes': ['global Inhabited instance replaced by local instances in exact use scopes',
                    'same arithmetic/layout as fp-word-conv3'],
        'queue': 'REPLACE_FP_WORD_CONV3_POLICY_REJECTION',
        'next_gate': 'pinned original intake/policy, then native build/full-model checksums/timing'})
    seventh = publish('fp-raw7-local', localize_instances(raw_word_probe(explicit_bool=True), 'R26RawWord'), {
        'retained_original_sha256': sha(BASE.read_bytes()),
        'entry': 'Submission.kernels', 'proof_entry': 'Submission.retainedCorrect',
        'proof_covers': 'Submission.retainedKernels only',
        'parent_runtime': fifth['sha256'],
        'changes': ['global Inhabited instance replaced by local instances in exact use scopes',
                    'same fused raw5 runtime'],
        'queue': 'NEXT_DISCRIMINATOR_ONLY_IF_CI_THROUGHPUT_PERMITS',
        'next_gate': 'pinned original intake/policy, then native build/full-model checksums/timing'})
    eighth = publish('word-official8-draft', official_finish_probe(), {
        'retained_original_sha256': sha(BASE.read_bytes()),
        'entry': 'Submission.kernels', 'proof_entry': 'Submission.retainedCorrect',
        'proof_covers': 'Submission.retainedKernels only',
        'changes': ['word64/128 raw accumulation only; no FP cache preparation/attempt',
                    'one terminal official finishWord call per dot',
                    'same prepared dense/conv raw arrays and original dotFn outside eligibility'],
        'queue': 'DRAFT_NEXT_ROUND_PROOF_COST_ALTERNATIVE_NO_EXTRA_CI_REQUEST',
        'next_gate': 'native cost versus fp-raw7 and full all-input word recurrence refinement; UNPROVED'})
    ready = {'updated_utc': datetime.now(timezone.utc).isoformat(),
             'deadline_utc': '2026-10-29T09:55:15Z',
             'first_source': first, 'second_source': second, 'third_source': third,
             'fourth_source': fourth,
             'next_raw_source': fifth,
             'replacement_for_first_queue': sixth,
             'next_raw_source_policy_fixed': seventh,
             'current_policy_valid_sources': [first, sixth, seventh],
             'known_policy_rejected_sources': ['fp-word2', 'fp-word-conv3', 'fp-raw4', 'fp-raw5'],
             'word_only_official_finish_draft': eighth,
             'compile': 'NOT_RUN_LOCAL_BY_INSTRUCTION',
             'communication': 'FILE_ONLY', 'active_next': 'word128 structural fallback integration'}
    (HERE / 'READY.json').write_text(json.dumps(ready, indent=2) + '\n', encoding='utf-8')
    print(json.dumps(first, indent=2))
    print(json.dumps(second, indent=2))
    print(json.dumps(third, indent=2))
    print(json.dumps(fourth, indent=2))
    print(json.dumps(fifth, indent=2))
    print(json.dumps(sixth, indent=2))
    print(json.dumps(seventh, indent=2))
    print(json.dumps(eighth, indent=2))

if __name__ == '__main__':
    main()
