"""Finite Python semantic check for E1; not native Rust or Lean acceptance."""
from pathlib import Path
import hashlib
import json
import random

ROOT = Path(__file__).resolve().parents[1]
OUT = ROOT / "evidence/round26/extension90m/route-e"


def be8(data, pos):
    return int.from_bytes(data[pos:pos+8], "big") if pos+8 <= len(data) else 0


def old(data, a, b, length):
    k, ok = 0, 1
    while ok == 1 and k+8 <= length:
        if be8(data, a+k) == be8(data, b+k):
            k += 8
        else:
            ok = 0
    if ok == 1 and k < length:
        if a+k+8 <= len(data) and b+k+8 <= len(data):
            if (be8(data, a+k) ^ be8(data, b+k)) >> (64-8*(length-k)):
                ok = 0
        else:
            while ok == 1 and k < length:
                if data[a+k] == data[b+k]:
                    k += 1
                else:
                    ok = 0
    return ok


def new(data, a, b, length):
    n = len(data)
    if 1 <= length <= 8 and n >= 8 and a <= n-8 and b <= n-8:
        return int(((be8(data, a) ^ be8(data, b)) >> (64-8*length)) == 0)
    return old(data, a, b, length)


def main():
    count = 0
    by_length = {}
    for n in range(25):
        rng = random.Random(2665800+n)
        patterns = [bytes(n), bytes(range(n)), bytes((i % 3) for i in range(n)),
                    bytes(rng.randrange(256) for _ in range(n))]
        for data in patterns:
            for length in range(min(n, 10)+1):
                for a in range(n-length+1):
                    for b in range(n-length+1):
                        observed_old = old(data, a, b, length)
                        observed_new = new(data, a, b, length)
                        assert observed_old == observed_new == int(data[a:a+length] == data[b:b+length])
                        count += 1
                        by_length[str(length)] = by_length.get(str(length), 0)+1
    p = ROOT / "candidates/r26-e-658-short-same/parse.rs"
    receipt = {"status": "FINITE_PYTHON_MODEL_EQUALITY_ONLY", "checks": count,
        "input_lengths": "0..24", "same_lengths": "0..min(input_length,10)",
        "patterns": "zero, increasing, period3, fixed-seed random",
        "all_valid_positions": True, "by_length": by_length,
        "rust_sha256": hashlib.sha256(p.read_bytes()).hexdigest(),
        "limitations": "Model mirrors source, does not execute Rust/extraction/Lean or claim performance. Native checks and original public gate are NOT_RUN."}
    (OUT / "e1-finite-model.json").write_bytes((json.dumps(receipt, indent=2)+"\n").encode())
    print(json.dumps(receipt, indent=2))


if __name__ == "__main__":
    main()
