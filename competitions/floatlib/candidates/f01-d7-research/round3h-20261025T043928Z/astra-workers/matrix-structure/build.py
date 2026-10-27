"""Bounded source assembly only. No Git, compiler, network, CI, or external writes."""
from pathlib import Path
from datetime import datetime, timezone
import hashlib, json, time

OUT = Path(__file__).resolve().parent
ROOT = next(p for p in OUT.parents if (p / "competitions/floatlib/pins.json").is_file())
sha = lambda b: hashlib.sha256(b).hexdigest()
started = time.monotonic()
fragment = (OUT / "ThinDual.lean").read_bytes()
parents = [
    ("D-matrix-base", "competitions/floatlib/candidates/f01-r15-dev-matrix-only1/Kernel.lean",
     "ec82ac20cf5b2a9621dce7e409a68a4af9700b1845d23385497c896439e372a1", "Kernel.lean"),
    ("DF-isolated", "competitions/floatlib/candidates/f01-d12-scalar-combined/Kernel.lean",
     "df5c61a0ca24a8ef18c0c42d83bdd23466872d3fe8f39dd912e9c347b27fb172", "Kernel-df5c.lean"),
]
records = []
for label, path, expected, target in parents:
    source = (ROOT / path).read_bytes()
    assert sha(source) == expected, (label, sha(source), expected)
    # Normalize only the newly appended fragment; preserve original source bytes.
    eol = b"\r\n" if b"\r\n" in source else b"\n"
    frag = fragment.replace(b"\r\n", b"\n").replace(b"\n", eol)
    marker = b"end Submission.UnderflowZero" + eol
    assert source.count(marker) == 1
    at = source.index(marker) + len(marker)
    prefix, tail = source[:at], source[at:]
    old_call = b"else bmmBeforeUnderflowZero batch m n p A B"
    old_spec = b"exact bmmBeforeUnderflowZero_spec batch m n p A B"
    assert tail.count(old_call) == tail.count(old_spec) == 1
    tail = tail.replace(old_call, b"else R15ThinDual.dispatch batch m n p A B")
    tail = tail.replace(old_spec, b"exact R15ThinDual.dispatch_spec batch m n p A B")
    candidate = prefix + eol + frag + eol + tail
    assert len(candidate) <= 256000
    assert candidate.count(b"import ContractTensor") == 1
    assert b"sorry" not in frag and b"admit" not in frag and b"axiom " not in frag
    (OUT / target).write_bytes(candidate)
    records.append({"label": label, "parent": path, "parent_sha256": expected,
                    "candidate_file": target, "sha256": sha(candidate), "bytes": len(candidate),
                    "status": "SOURCE_ASSEMBLED_NOT_COMPILED"})
assert time.monotonic() - started < 5
receipt = {"created_at_utc": datetime.now(timezone.utc).isoformat(),
           "fragment": "ThinDual.lean", "fragment_sha256": sha(fragment),
           "fragment_bytes": len(fragment), "candidates": records,
           "runtime_change": "p=2,n>1,m>=4: two independent column folds share one raw A decode per k; B mapped once; old raw finish retained",
           "test_selection": "Two assembly targets are integration alternatives, not repeated discovery trials. Coordinator selects one exact source before its first D.",
           "validation": "No local Lean or compilation. New exact source needs full official gate and paired timing.",
           "elapsed_seconds": time.monotonic() - started}
(OUT / "build-receipt.json").write_text(json.dumps(receipt, ensure_ascii=False, indent=2) + "\n", encoding="utf-8")
print(json.dumps(receipt, ensure_ascii=False))
