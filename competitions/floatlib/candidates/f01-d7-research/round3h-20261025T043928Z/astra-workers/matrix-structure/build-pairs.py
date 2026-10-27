"""Assemble the one selected broad paired-column candidate; no compilation."""
from pathlib import Path
from datetime import datetime, timezone
import hashlib, json, time
OUT = Path(__file__).resolve().parent
ROOT = next(p for p in OUT.parents if (p / "competitions/floatlib/pins.json").is_file())
sha = lambda b: hashlib.sha256(b).hexdigest()
start = time.monotonic()
seed = (OUT / "ThinDual.lean").read_text(encoding="utf-8")
prefix = seed.split("@[inline] def row", 1)[0]
prefix = prefix.replace("R15ThinDual", "R15ThinPairs")
prefix = prefix.replace("fuse two independent columns while reusing one prepared B.",
                        "pair independent columns while reusing one prepared B; all odd tails preserved.")
fragment = (prefix + (OUT / "ThinPairs-writer.lean").read_text(encoding="utf-8")).encode()
(OUT / "ThinPairs.lean").write_bytes(fragment)
parent_path = "competitions/floatlib/candidates/f01-r15-dev-matrix-only1/Kernel.lean"
expected = "ec82ac20cf5b2a9621dce7e409a68a4af9700b1845d23385497c896439e372a1"
parent = (ROOT / parent_path).read_bytes()
assert sha(parent) == expected
eol = b"\r\n" if b"\r\n" in parent else b"\n"
fragment = fragment.replace(b"\n", eol)
marker = b"end Submission.UnderflowZero" + eol
assert parent.count(marker) == 1
at = parent.index(marker) + len(marker)
before, tail = parent[:at], parent[at:]
for old, new in [(b"else bmmBeforeUnderflowZero batch m n p A B", b"else R15ThinPairs.dispatch batch m n p A B"),
                 (b"exact bmmBeforeUnderflowZero_spec batch m n p A B", b"exact R15ThinPairs.dispatch_spec batch m n p A B")]:
    assert tail.count(old) == 1
    tail = tail.replace(old, new)
result = before + eol + fragment + eol + tail
assert len(result) <= 256000
assert result.count(b"import ContractTensor") == 1
assert b"sorry" not in fragment and b"admit" not in fragment and b"axiom " not in fragment
(OUT / "Kernel-pairs.lean").write_bytes(result)
receipt = {"created_at_utc": datetime.now(timezone.utc).isoformat(), "parent": parent_path,
           "parent_sha256": expected, "fragment": "ThinPairs.lean",
           "fragment_sha256": sha((OUT / "ThinPairs.lean").read_bytes()),
           "candidate_file": "Kernel-pairs.lean", "sha256": sha(result), "bytes": len(result),
           "scope": "2<=p<=8,n>1,m>=4; underflow-zero remains outermost; all other paths inherited from parent",
           "difference_from_parent": "per-pair fused two-accumulator loop shares raw A; B cached once also for p3..8; exact odd tail",
           "policy_status": "Static size/import/no-new-axiom check only; actual gate NOT_RUN",
           "proof_status": "COMPLETE_ATTEMPT_NOT_COMPILED", "performance": "UNKNOWN",
           "exclusions": "No Git/index/branch/push/CI, local Lean, native compilation, benchmark, extern or unsafe",
           "elapsed_seconds": time.monotonic() - start}
assert receipt["elapsed_seconds"] < 5
(OUT / "pairs-build-receipt.json").write_text(json.dumps(receipt, ensure_ascii=False, indent=2) + "\n", encoding="utf-8")
print(json.dumps(receipt, ensure_ascii=False))
