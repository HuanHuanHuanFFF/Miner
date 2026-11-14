"""Compare the actual R26 frozen runtime definitions to the proof-chain inputs."""
from pathlib import Path
from datetime import datetime, timezone
import hashlib
import json

HERE = Path(__file__).resolve().parent
ROOT = next(p for p in HERE.parents if (p / "AGENTS.md").is_file())
R26 = HERE.parents[1]
R25 = ROOT / "competitions/torchlean/candidates/r25-90m-20261029T064916Z"
R24 = ROOT / "competitions/floatlib/candidates/f01-d7-research/round7h-20261028T203856Z"
sha = lambda b: hashlib.sha256(b).hexdigest()
load = lambda p: p.read_bytes().decode("utf-8").replace("\r\n", "\n")
candidate = R26 / "development/native/fp-word-conv6-local/Kernel.lean"
expected = "ad9bde3e9e8490df15f3d8d15c08805f85d4451e0a5f2d20977632c0b4b22540"
assert sha(candidate.read_bytes()) == expected
candidate_text = load(candidate)
prior = load(R24 / "development-dot-cost/PortableF64Dot-tail-v2.lean.inc")
fastlog = load(R25 / "research/widen/actual-bridge/ActualRuntime.lean.inc")

def fragment(source, first, last):
    assert source.count(first) == 1, first
    i = source.index(first)
    return source[i:source.index(last, i)].rstrip() + "\n"

candidate_f64 = fragment(candidate_text, "namespace Submission.R24PortableF64", "end Submission.R24PortableF64")

boundaries = [
    ("Prepared", "structure Prepared where", "@[inline] def index32"),
    ("index32", "@[inline] def index32", "/-- Exact finite-word widening recipe"),
    ("widenBits", "@[inline] def widenBits (word", "def prepare ("),
    ("prepare", "def prepare (raw : Array UInt32)", "@[inline] def ceilLog2"),
    ("ceilLog2", "@[inline] def ceilLog2", "@[inline] def finite64"),
    ("sumRemaining", "def sumRemaining (", "/-- Zero is a miss sentinel."),
    ("attemptPrepared", "def attemptPrepared (", "/-- Preparation and dropping"),
]
rows = []
for name, first, last in boundaries:
    a, b = fragment(prior, first, last), fragment(candidate_f64, first, last)
    rows.append({"name": name, "bytes_LF": len(a.encode()), "prior_sha256_LF": sha(a.encode()),
                 "candidate_sha256_LF": sha(b.encode()), "byte_identical_after_LF": a == b})
fast_first = "@[inline] def sx (k x : UInt64)"
fast_last = "end Submission.FastMul"
a, b = fragment(fastlog, fast_first, fast_last), fragment(candidate_text, fast_first, fast_last)
rows.append({"name": "sx_sr_fastLog2", "bytes_LF": len(a.encode()), "prior_sha256_LF": sha(a.encode()),
             "candidate_sha256_LF": sha(b.encode()), "byte_identical_after_LF": a == b})
result = {"at_utc": datetime.now(timezone.utc).isoformat(), "candidate": candidate.relative_to(ROOT).as_posix(),
          "candidate_sha256": expected, "runtime_fragments": rows,
          "all_identical_after_LF": all(r["byte_identical_after_LF"] for r in rows),
          "scope": "Source text identity only, no Lean proof or native timing result. Full actual producer-to-consumer chain remains unaccepted."}
(HERE / "runtime-identity.json").write_text(json.dumps(result, indent=2) + "\n")
print(json.dumps(result, indent=2))
