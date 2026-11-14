"""Finite synthetic discriminator; not Lean, not a candidate, not native timing."""
from pathlib import Path
from datetime import datetime, timezone
import hashlib
import json
import random
import struct

HERE = Path(__file__).resolve().parent
MASK64 = (1 << 64) - 1
CENTER = 1 << 39
OLD_CENTER = 1 << 62
MASK40 = (1 << 40) - 1
COUNT_RANDOM = 100000


def pack(index, magnitude, negative):
    low = CENTER - magnitude if negative else CENTER + magnitude
    return (index << 40) | low


def selected(payload, weight_negative):
    z = ((payload & MASK40) - CENTER) & MASK64
    return (-z if weight_negative else z) & MASK64


def old_selected(magnitude, negative, weight_negative):
    value = OLD_CENTER - magnitude if negative != weight_negative else OLD_CENTER + magnitude
    assert 0 <= value < 1 << 63
    return (value - OLD_CENTER) & MASK64


def check_case(index, magnitude, negative, weight_negative):
    assert 0 <= index < 1 << 20
    assert 0 <= magnitude < 1 << 39
    payload = pack(index, magnitude, negative)
    assert 0 <= payload < 1 << 60
    exponent = (payload >> 52) & 2047
    assert exponent <= 255 and exponent != 2047
    value = struct.unpack("<d", struct.pack("<Q", payload))[0]
    transported = struct.unpack("<Q", struct.pack("<d", value))[0]
    assert transported == payload
    assert payload >> 40 == index
    assert selected(transported, weight_negative) == old_selected(magnitude, negative, weight_negative)


def main():
    start = datetime.now(timezone.utc).isoformat()
    edge_count = 0
    for delta in range(16):
        for mantissa in [0, 1, (1 << 23) - 1, 1 << 23, (1 << 24) - 1]:
            for index in [0, 1, (1 << 20) - 1]:
                for negative in [False, True]:
                    for weight_negative in [False, True]:
                        check_case(index, mantissa << delta, negative, weight_negative)
                        edge_count += 1
    rng = random.Random(0xA60F1029)
    for _ in range(COUNT_RANDOM):
        delta = rng.randrange(16)
        magnitude = rng.randrange(1 << 24) << delta
        check_case(rng.randrange(1 << 20), magnitude, bool(rng.getrandbits(1)), bool(rng.getrandbits(1)))
    bad32_magnitude = ((1 << 24) - 1) << 8
    fixed_payload = pack((1 << 20) - 1, bad32_magnitude, False)
    assert selected(fixed_payload, False) == bad32_magnitude
    generic_width_edges = 0
    for index in [0, 1, (1 << 20) - 1]:
        for magnitude in [0, 1, (1 << 31) - 1, 1 << 31, CENTER - 1]:
            for negative in [False, True]:
                for weight_negative in [False, True]:
                    check_case(index, magnitude, negative, weight_negative)
                    generic_width_edges += 1
    result = {
        "state": "FINITE_SYNTHETIC_CODEC_CHECK_PASS_NOT_LEAN_NOT_NATIVE_TIMING",
        "actual_start_utc": start,
        "actual_end_utc": datetime.now(timezone.utc).isoformat(),
        "random_seed": "0xA60F1029",
        "counts": {"all16delta_edges": edge_count, "random_aligned_cases": COUNT_RANDOM, "generic39bit_edges": generic_width_edges},
        "domain": {"mantissa_lt": 1 << 24, "delta_max": 15, "magnitude_lt": 1 << 39, "index_lt": 1 << 20, "payload_lt": 1 << 60, "exponent_max": 255},
        "mathematical_max_payload": (1 << 60) - 1,
        "smallNat_limit_64bit": (1 << 63) - 1,
        "old_span8_signed32_counterexample_now_exact": {"magnitude": bad32_magnitude, "decoded": selected(fixed_payload, False), "payload": fixed_payload},
        "index_bridge_negative_control": {"dot_n": 1, "packed_index": (1 << 20) - 1, "finite_payload": pack((1 << 20) - 1, 1, False), "index_below_n": False},
        "remaining": ["ActualQPIindex<n andexactgetterlink", "LeanelaborationandAXaudit", "ActualsamepayloadFloatArrayversusArrayNatprepare/access/destructioncost", "All12bindingandfullgate"],
        "no_batch9_inputs_or_results_read": True,
        "no_new_CI": True,
        "script_sha256": hashlib.sha256(Path(__file__).read_bytes()).hexdigest(),
        "runtime_draft_sha256": hashlib.sha256((HERE / "Aligned60Carrier.lean.inc").read_bytes()).hexdigest()
    }
    (HERE / "aligned60-model.json").write_text(json.dumps(result, indent=2) + "\n", encoding="utf-8")
    print(json.dumps({k:result[k] for k in ["state", "counts", "old_span8_signed32_counterexample_now_exact", "actual_start_utc", "actual_end_utc"]}))


if __name__ == "__main__":
    main()

