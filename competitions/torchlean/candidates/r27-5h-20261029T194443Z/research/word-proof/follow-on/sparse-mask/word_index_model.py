"""Self-derived UInt32 one-hot lookup and finite mask enumeration model."""
from pathlib import Path
from datetime import datetime, timezone
import hashlib
import json
import random

HERE = Path(__file__).resolve().parent
MASK = (1 << 32)-1
MULTIPLIER = 0x077CB531
TABLE = [-1]*32
for index in range(32):
    slot = (((1 << index)*MULTIPLIER)&MASK) >> 27
    assert TABLE[slot] == -1
    TABLE[slot] = index
assert sorted(TABLE) == list(range(32))


def enumerate_word(mask):
    out = []
    while mask:
        isolated = mask & ((0-mask)&MASK)
        slot = ((isolated*MULTIPLIER)&MASK) >> 27
        out.append(TABLE[slot])
        mask &= (mask-1)&MASK
    return out


def main():
    counts = {'one_hot32':0, 'all_low16_masks':0, 'directed32':0, 'random32':0}
    for i in range(32):
        assert enumerate_word(1 << i) == [i]
        counts['one_hot32'] += 1
    for mask in range(1 << 16):
        got = enumerate_word(mask)
        assert sum(1 << i for i in got) == mask and got == sorted(set(got))
        counts['all_low16_masks'] += 1
    for mask in [0, MASK, 0x80000000, 0x80000001, 0x55555555, 0xaaaaaaaa, 0x7fffffff, 0xffff0000]:
        assert enumerate_word(mask) == [i for i in range(32) if mask >> i & 1]
        counts['directed32'] += 1
    rng = random.Random(0x32DE)
    for _ in range(5000):
        mask = rng.getrandbits(32)
        assert enumerate_word(mask) == [i for i in range(32) if mask >> i & 1]
        counts['random32'] += 1
    result = {'at_utc':datetime.now(timezone.utc).isoformat(),
              'state':'FINITE_UINT32_MASK_MODEL_NO_LEAN_NATIVE',
              'multiplier':MULTIPLIER,'table':TABLE,'cases':counts,
              'exhaustive_scope':'All32 one-hot words and every16-bit mask; random/directed32-bit enumeration only.',
              'general_argument_still_to_formalize':'For nonzero UInt32 m, m & -m isolates its least set bit; the32 one-hot map is a permutation; m & (m-1) removes that bit. The loop must be tied to actual prepared mask/getter bounds.',
              'cost':'Word negation/AND/multiply/shift/table load and clear-lowest-bit per emitted index, plus a predictable nonzero-word loop. This is source operation shape, not a native cycle count.',
              'difference_from_Nat_log2':'No Nat.log2 primitive is used or assumed to become a hardware bit-scan.',
              'implementation_state':'No Lean candidate or CI request generated. Need complete native cost including fused/separate metadata-mask preparation before proof investment.',
              'source_sha256':hashlib.sha256(Path(__file__).read_bytes()).hexdigest()}
    (HERE/'word-index-model.json').write_text(json.dumps(result,indent=2),encoding='utf8')
    print(json.dumps({'cases':counts,'table':TABLE}))


if __name__ == '__main__':
    main()
