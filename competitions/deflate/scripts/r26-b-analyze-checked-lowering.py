"""Verify exact B25 reduction loops and assembly-only symbol differences."""
from pathlib import Path
from datetime import datetime, timezone
import hashlib
import json
import re

ROOT = Path(__file__).resolve().parents[1]
FOLDER = ROOT/'evidence/round26/38218734487/lowering-b25-native/diagnostics/r26-b-a-checked-lowering'


def sha(raw):
    return hashlib.sha256(raw).hexdigest()


def normalize_alloc(text):
    mapping = {}
    def rename(m):
        name = m.group()
        if name not in mapping:
            mapping[name] = '.Lalloc_NORMALIZED_'+str(len(mapping))
        return mapping[name]
    return re.sub(r'\.Lalloc_[0-9a-f]{32}', rename, text), mapping


def main():
    receipt = json.loads((FOLDER/'receipt.json').read_bytes())
    assert receipt['status'] == 'VERIFIED_OFFICIAL_CANDIDATE_FLAGS_SHIM_COMPILE_DIAGNOSTIC_ONLY'
    body = {}
    for name, row in receipt['variants'].items():
        asm = (FOLDER/(name+'-a-dp-pass.s')).read_bytes()
        ir = (FOLDER/(name+'-a-dp-pass.ll')).read_bytes()
        assert sha(asm) == row['body_ASM_sha256'] and sha(ir) == row['body_IR_sha256']
        lines = ir.decode().splitlines()
        reductions = [{'line': i+1, 'text': line.strip()} for i, line in enumerate(lines) if '@llvm.vector.reduce.umin' in line]
        assert len(reductions) == 2
        assert row['IR_unsigned_add_overflow_calls'] == 0
        # Both original variable ranges retain independent vector bodies,
        # each with 8-term induction and two 4-lane minimum accumulators.
        vector_starts = [i for i, line in enumerate(lines) if re.match(r'^vector\.body', line)]
        assert len(vector_starts) == 2
        for at in vector_starts:
            part = '\n'.join(lines[at:at+40])
            assert len(re.findall(r'phi <4 x i32> \[ splat \(i32 -1\)', part)) == 2
            assert re.search(r'add nuw i64 %index[^,]*, 8', part)
        normalized, names = normalize_alloc(asm.decode())
        body[name] = {'normalized': normalized, 'symbols': names, 'reductions': reductions,
                      'vector_body_starts': [i+1 for i in vector_starts], 'raw_IR_sha256': sha(ir), 'raw_ASM_sha256': sha(asm)}
    a, b = body['original_checked'], body['safe_wrapping_increment']
    assert a['normalized'] == b['normalized']
    assert len(a['symbols']) == len(b['symbols']) == 5
    assert sorted(a['symbols'].values()) == sorted(b['symbols'].values())
    result = {'status': 'VERIFIED_TWO_ORIGINAL_CHECKED_A_REDUCTIONS_ALREADY_VECTORIZE',
              'computed_utc': datetime.now(timezone.utc).isoformat(), 'run_id': receipt['run_id'],
              'source_hashes': receipt['source_hashes'], 'release_settings': receipt['preflight']['release_settings'],
              'source_variants': receipt['preflight']['source_variants_sha256'],
              'exact_reductions': {name: {'IR_reduction_calls': r['reductions'], 'vector_body_starts': r['vector_body_starts']} for name, r in body.items()},
              'assembly_comparison': {'all_instruction_and_label_text_equal_after_bijective_alloc_symbol_rename': True,
                                      'differing_symbols': 5, 'normalization': 'Only .Lalloc_<32hex> symbols, first-use bijection; no registers/opcodes/labels/operands otherwise normalized.',
                                      'symbol_correspondence': list(zip(a['symbols'], b['symbols']))},
              'decision': 'STOP_CHECKED_INCREMENT_VECTOR_UNLOCK: original official-settings cdylib already has both 8-term/two4lane unsigned reductions, and safe wrapping emits same instruction text except five panic-location constant symbols. Do not create a production variant or hand-unroll using this invalidated premise.',
              'limits': ['Assembly text equality excluding five named panic-location constants is not literal ELF byte equality or a benchmark-library identity.',
                         'Actual official shim/release settings matched, but source paths/metadata differ between generated crates.',
                         'No changed parser executed, original encoder/paired total-time/fullgate not run for the two-increment diagnostic.',
                         'This rejects a specific vectorization barrier; other proven mechanisms may revisit current A DP without claiming this barrier persists.'],
              'input_hashes': {(FOLDER/'receipt.json').relative_to(ROOT).as_posix(): sha((FOLDER/'receipt.json').read_bytes())}}
    out = ROOT/'evidence/round26/route-b/b26-checked-lowering-feedback.json'
    assert not out.exists()
    out.write_text(json.dumps(result, indent=2)+'\n')
    print(json.dumps({'status': result['status'], 'asm_instruction_text_equal': True, 'symbols': 5, 'decision': result['decision']}))


if __name__ == '__main__':
    main()
