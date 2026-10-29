"""Disprove a stronger interface implication, not the actual runtime producer."""
from pathlib import Path
from fractions import Fraction
from datetime import datetime, timezone
import json
import struct

HERE = Path(__file__).resolve().parent
word = lambda f: f"0x{struct.unpack('>Q', struct.pack('>d', f))[0]:016x}"
s = 1.0 - 3.0 * 2.0 ** -53
r = 2.0 ** -51
S = Fraction(1) + Fraction(1, 2 ** 53)
sq, rq = Fraction(s), Fraction(r)
upper = s + r
lower = s - r
exact_upper = sq + rq
assert abs(sq - S) == rq
assert exact_upper == S
assert Fraction(upper) == 1
assert Fraction(upper) < S
assert Fraction(lower) <= S
assert 250 + 2 * 1 - 303 == -51
record = {
    "at_utc": datetime.now(timezone.utc).isoformat(),
    "scope": "COUNTEREXAMPLE_TO_ERROR_BOUND_PLUS_RNE_ENDPOINTS_IMPLIES_NATIVE_ENCLOSURE",
    "not_a_runtime_counterexample": True,
    "not_a_Lean_acceptance_result": True,
    "parameters": {"H": 250, "L": 1, "n": 2, "H_le_506": True, "L_le_30": True},
    "s": {"word": word(s), "rational": str(sq)},
    "radius": {"word": word(r), "rational": str(rq)},
    "target_exact_rational": str(S), "error_exact_rational": str(abs(sq - S)),
    "native_lower": {"word": word(lower), "rational": str(Fraction(lower))},
    "native_upper": {"word": word(upper), "rational": str(Fraction(upper))},
    "unrounded_upper": str(exact_upper),
    "observed": "S equals s+radius but RN64(s+radius)=1<S; native upper enclosure does not follow from these premises.",
    "limit": "The chosen s,S pair has not been produced by an actual prepared dot. This does not refute runtime soundness. Strict midpoint monotone pullback avoids the stronger premise.",
}
(HERE / "endpoint-implication-counterexample.json").write_text(json.dumps(record, indent=2) + "\n")
print(json.dumps(record, indent=2))
