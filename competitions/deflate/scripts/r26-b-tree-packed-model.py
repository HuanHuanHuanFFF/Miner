"""Fixed low26 timestamp/high6 prefix representation, finite tree/string model."""
from datetime import datetime, timezone
from pathlib import Path
import argparse
import hashlib
import json

ROOT = Path(__file__).resolve().parents[1]


def run():
    src = ROOT/'scripts/r26-b-tree-edge-model.py'
    code = src.read_text()
    pair = '            return low, l != p and low < cap'
    join = '            return min(l, t), (l < t and l < cap) or (t < l and exact)'
    assert code.count(pair) == code.count(join) == 1
    code = code.replace(pair, '            return min(low,31), l != p and low < cap and low <= 31')
    code = code.replace(join, '            low=min(l,t);return min(low,31), ((l<t and l<cap) or (t<l and exact)) and low<=31')
    namespace = {'__name__': 'finite_packed_model', '__file__': str(src)}
    exec(compile(code, str(src), 'exec'), namespace)
    counts = namespace['run']()
    stamp_checks = 0
    mask = (1 << 26) - 1
    for stamp in [0, 1, 32767, 32768, 65536, (1 << 24)-1, (1 << 25)-1, mask-1, mask]:
        for prefix in range(259):
            for exact in [False, True]:
                bound = min(prefix, 31)
                flag = exact and prefix <= 31
                tag = bound | (32 if flag else 0)
                word = stamp | (tag << 26)
                assert word <= (1 << 32)-1 and (word & mask) == stamp
                assert (word >> 26) & 31 == bound
                assert bool((word >> 26) & 32) == flag
                stamp_checks += 1
    return {'tree_model': counts, 'timestamp_prefix_bit_checks': stamp_checks,
            'generated_model_sha256': hashlib.sha256(code.encode()).hexdigest(),
            'base_model_sha256': hashlib.sha256(src.read_bytes()).hexdigest()}


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument('--output', type=Path, required=True)
    a = ap.parse_args()
    assert not a.output.exists()
    result = {'status': 'VERIFIED_FINITE_FIXED26_TIMESTAMP_31_PREFIX_TREE_MODEL_ONLY',
              'computed_utc': datetime.now(timezone.utc).isoformat(), 'details': run(),
              'limits': ['Fixed representation constraint, no tag width sweep. Only parsed A calls under n<2^26 justify complete timestamps.',
                         'Finite small-window tree/suffix metadata invariants and bit boundaries, not production Rust/encoder or full gate.']}
    a.output.write_text(json.dumps(result, indent=2)+'\n')
    print(json.dumps(result))


if __name__ == '__main__':
    main()
