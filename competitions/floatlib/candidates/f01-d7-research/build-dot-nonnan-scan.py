"""Append only the actual Nat scanner and its minimal raw-classification bridge.

This statement probe changes no exported operation and proves no canonical output.
"""
from datetime import datetime, timezone
import hashlib
import json
from pathlib import Path


HERE = Path(__file__).resolve().parent


def sha(data):
    return hashlib.sha256(data).hexdigest()


parent = HERE.parent / "f01-d7-direct-nonfinite"
parent_bytes = (parent / "Kernel.lean").read_bytes()
assert sha(parent_bytes) == "97f77e2ce3f53dc3625349d5d2a7bc761570f9428c0b547070e37254c4960d26"
classification = (HERE / "nan-choice-block.lean").read_bytes()
assert sha(classification) == "584ace5443838454b3687f7a93cfca07be4f9cce2c889c7196b171b7cfd4c93c"
scanner = (HERE / "dot-nonnan-scan-block.lean").read_bytes()
assert sha(scanner) == "5e46e932fb8483792c42a79d59e887e32af15e236100cbb8253ca82d3212ea8f"

# Retain these two declaration excerpts byte-for-byte. The unrelated NaN
# priority/quieting bridge is deliberately not needed by this scanner probe.
raw_definition = classification[
    classification.index(b"@[inline] def rawNaN "):
    classification.index(b"@[inline] def rawSNaN ")
]
raw_bridge = classification[
    classification.index(b"theorem rawNaN_eq "):
    classification.index(b"theorem rawSNaN_eq ")
]
minimal = (
    b"namespace DWordNaN\n\n"
    b"open FloatLib.Floats.Formats.BinaryInterchange\n\n"
    + raw_definition + raw_bridge + b"end DWordNaN\n"
)
assert b"DWordNaN" not in parent_bytes
data = parent_bytes + b"\n\n" + minimal + b"\n" + scanner
assert len(data) < 256000
assert data.startswith(parent_bytes)
out = HERE.parent / "f01-d7-dot-nonnan-scan-probe"
out.mkdir(exist_ok=True)
(out / "Kernel.lean").write_bytes(data)
manifest = {
    "candidate": out.name,
    "candidate_file": "Kernel.lean",
    "candidate_sha256": sha(data),
    "candidate_bytes": len(data),
    "created_at_utc": datetime.now(timezone.utc).isoformat(),
    "parent": parent.name,
    "parent_sha256": sha(parent_bytes),
    "classification_source_sha256": sha(classification),
    "raw_definition_excerpt_sha256": sha(raw_definition),
    "raw_bridge_excerpt_sha256": sha(raw_bridge),
    "minimal_classification_block_sha256": sha(minimal),
    "scanner_block_sha256": sha(scanner),
    "validation_mode": "statement-only",
    "proof_status": "NOT_RUN_NEW_CLASSIFIER_AND_NAT_SCAN_INTEGRATION",
    "mechanism": "Append actual early-exit Nat input scanner, exact Fin-domain coverage equivalence, and raw/model nonNaN consequences. A(baseA+k), B(baseB+k*p), getD positive-zero defaults; no machine-word address truncation.",
    "runtime_change": "NONE: the exact parent is an unchanged byte prefix; no exported operation or existing declaration is replaced.",
    "boundary": "Scanner acceptance establishes only that every actual input is nonNaN. It does not establish that a dot result is NaN, canonical, equal to a native endpoint, or safe to return. Canonical-image closure and the actual native/spec dot correspondence remain separate obligations before any cold-branch integration.",
    "gain": "UNKNOWN; proof-only probe has no new timing claim.",
    "formal_submission": "NOT_SUBMITTED",
}
(out / "manifest.json").write_text(json.dumps(manifest, ensure_ascii=False, indent=2) + "\n", encoding="utf-8")
print(json.dumps({"candidate": out.name, "sha256": sha(data), "bytes": len(data)}))
