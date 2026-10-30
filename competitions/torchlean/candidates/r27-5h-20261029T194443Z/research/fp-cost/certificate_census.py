"""Replay the exact R26 FP checker on old public exploratory fixtures only.

Not Lean/native execution, performance evidence, deployment probability or a
current-champion comparison. This checks the cost premise before more proof.
"""
from pathlib import Path
import datetime
import hashlib
import json
import math
import struct

HERE = Path(__file__).resolve().parent
ROOT = next(p for p in HERE.parents if (p / "AGENTS.md").is_file())
OLD = ROOT / "competitions/torchlean/candidates/r26-1h-20261029T085515Z"
M64 = (1 << 64) - 1


def hash_bytes(b):
    return hashlib.sha256(b).hexdigest()


def bits(x):
    return struct.unpack(">Q", struct.pack(">d", x))[0]


def from_bits(w):
    return struct.unpack(">d", struct.pack(">Q", w))[0]


def value(w):
    return struct.unpack(">f", struct.pack(">I", w))[0]


def widen(w):
    sign = (w & 0x80000000) << 32
    e, f = (w >> 23) & 255, w & 0x7fffff
    if e == 0:
        if f == 0:
            return sign
        lead = f.bit_length() - 1
        return sign | ((lead + 874) << 52) | ((f - (1 << lead)) << (52 - lead))
    return sign | ((e + 896) << 52) | (f << 29)


def key(w):
    return w ^ (0x8000000000000000 if w & 0x8000000000000000 == 0 else M64)


def finite(w):
    return w & 0x7ff0000000000000 != 0x7ff0000000000000


def relu(w):
    nan = ((w >> 23) & 255) == 255 and w & 0x7fffff != 0
    return 0 if w & 0x80000000 != 0 and not nan else w


def proposal(w):
    shifted = (((w & 0x7fffffffffffffff) + 0x10000000) & M64) >> 29
    magnitude = ((shifted & 0xffffffff) - 0xc0000000) & 0x7fffffff
    return ((w >> 32) & 0x80000000) | magnitude


def certify(s, r, q):
    magnitude = q & 0x7fffffff
    e = (magnitude >> 23) & 255
    if e in (0, 255):
        return False, "proposal_zero_or_subnormal" if e == 0 else "proposal_nonfinite"
    sw, low, high = bits(s), bits(s - r), bits(s + r)
    if not (finite(sw) and finite(low) and finite(high)):
        return False, "nonfinite_sum_or_endpoint"
    base = ((e + 896) << 52) | ((magnitude & 0x7fffff) << 29)
    below = base - (0x20000000 if magnitude == 0x00800000 else 0x10000000)
    above = base + 0x10000000
    negative = q & 0x80000000 != 0
    lower = (above | (1 << 63)) if negative else below
    upper = (below | (1 << 63)) if negative else above
    good = key(lower) < key(low) and key(high) < key(upper)
    return good, "accepted" if good else "strict_cell_failed"


def run():
    source = OLD / "development/native/fp-word-conv6-local/Kernel.lean"
    assert hash_bytes(source.read_bytes()) == "ad9bde3e9e8490df15f3d8d15c08805f85d4451e0a5f2d20977632c0b4b22540"
    groups = []
    for kind in ("normal", "sparse"):
        p = OLD / f"research/fallback/word-fixture-{kind}.txt"
        raw = p.read_bytes()
        lines = raw.decode().splitlines()
        n, out = int(lines[0]), int(lines[1])
        x, w, bias, expected = [[int(v) for v in line.split(",")] for line in lines[2:6]]
        assert len(x) == n and len(w) == n * out and len(bias) == len(expected) == out
        all_words = x + w + bias + [0x3f800000]
        assert all((z >> 23) & 255 != 255 for z in all_words)
        assert all(widen(z) == bits(value(z)) for z in all_words)
        xx = x + [0x3f800000]
        records, counts = [], {}
        for j in range(out):
            yy = w[j * n:(j + 1) * n] + [bias[j]]
            peak = lambda row: max(max(0, ((z >> 23) & 255) - 1) for z in row)
            H, L = peak(xx) + peak(yy), (len(xx) - 1).bit_length()
            radius = from_bits((H + 2 * L + 720) << 52)
            total = 0.0
            for a, b in zip(xx, yy):
                total = total + value(a) * value(b)
            assert math.isfinite(total)
            q = proposal(bits(total))
            accepted, reason = certify(total, radius, q)
            if accepted:
                assert relu(q) == expected[j], (kind, j, q, relu(q), expected[j])
            counts[reason] = counts.get(reason, 0) + 1
            records.append({"output": j, "H": H, "L": L, "sum_bits": bits(total),
                            "radius_bits": bits(radius), "proposal": q, "expected": expected[j],
                            "proposal_after_fixture_relu": relu(q),
                            "accepted": accepted, "reason": reason})
        groups.append({"kind": kind, "fixture": str(p.relative_to(ROOT)), "fixture_sha256": hash_bytes(raw),
                       "dot_terms_including_bias": n + 1, "outputs": out, "counts": counts, "records": records})
    result = {"at_utc": datetime.datetime.now(datetime.timezone.utc).isoformat(),
              "status": "FINITE_OLD_EXPLORATORY_FIXTURES_ONLY_NOT_LEAN_NATIVE_OR_PERFORMANCE",
              "script_sha256": hash_bytes(Path(__file__).read_bytes()), "runtime_source_sha256": hash_bytes(source.read_bytes()),
              "float_semantics": "Python binary64 sequential multiply/add with explicit matching widen/proposal/checker bit formulas; not executing compiled Lean",
              "reference_boundary": "Old WordBlockCostMain.output applies act true; compare accepted proposal after the exact original reluW. First harness mismatch retained in certificate-census-failure1.json.",
              "groups": groups, "current_champion_comparison": "UNKNOWN_NOT_MEASURED",
              "limits": ["160 first-layer outputs only; not later layers, wide, scale/boundary workloads or deployment acceptance probability.",
                         "A high acceptance count does not establish that prepare/check/drop/fallback costs beat the current champion."]}
    (HERE / "certificate-census-result.json").write_text(json.dumps(result, ensure_ascii=False, indent=2) + "\n", encoding="utf-8", newline="\n")
    print(json.dumps({"status": result["status"], "groups": [{"kind": g["kind"], "outputs": g["outputs"], "counts": g["counts"]} for g in groups]}))


if __name__ == "__main__":
    run()
