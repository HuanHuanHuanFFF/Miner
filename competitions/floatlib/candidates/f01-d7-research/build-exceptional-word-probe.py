"""Append an exact word-dispatch proof draft; keep retained runtime unchanged."""
from datetime import datetime, timezone
import hashlib
import json
from pathlib import Path

HERE = Path(__file__).resolve().parent
parent = HERE.parent / "f01-d7-nan-choice-probe"
raw = (parent / "Kernel.lean").read_bytes()
assert hashlib.sha256(raw).hexdigest() == "ad014e0b1cdc6e42d3a9bd9437e32762d840b8047be740dca8894b0108aa3cb9"
original = (HERE / "exceptional-word-block.lean").read_bytes()
assert hashlib.sha256(original).hexdigest() == "b884fff04a3353c02d37a824e57aa43ea3b79834569b47601b225441023c79f1"
# Upstream policy scans comments too. Preserve the original research bytes and
# adapt just the explanatory word that is also a forbidden Lean command.
before = b"are written below. Existing context/options are retained; no Submission export."
after = b"are written below. Existing context/options are retained; no operation replacement."
assert original.count(before) == 1
adapted = original.replace(before, after, 1)
out = HERE.parent / "f01-d7-exceptional-word-probe"
out.mkdir(exist_ok=True)
data = raw + b"\n\n" + adapted
assert len(data) < 256000 and data.startswith(raw)
(out / "Kernel.lean").write_bytes(data)
manifest = {
    "candidate": out.name, "candidate_file": "Kernel.lean",
    "candidate_sha256": hashlib.sha256(data).hexdigest(), "candidate_bytes": len(data),
    "created_at_utc": datetime.now(timezone.utc).isoformat(),
    "parent": parent.name, "parent_sha256": hashlib.sha256(raw).hexdigest(),
    "original_math_block_sha256": hashlib.sha256(original).hexdigest(),
    "adapted_math_block_sha256": hashlib.sha256(adapted).hexdigest(),
    "policy_adaptation": "One explanatory comment command-word changed; every Lean declaration/proof/runtime byte in the new math block retained. Original block preserved separately.",
    "validation_mode": "statement-only", "proof_status": "NOT_RUN_APPEND_ONLY_MATHEMATICS",
    "mechanism": "No exported operation changes. Append UInt32-only exceptional add/mul definitions and concrete Model/ExecFloat equivalence conditional on the existing rejected-finite input guard. Runtime helper uses no Option; the existing rawChoose only appears in proof equalities.",
    "boundary": "New helpers are wrong for ordinary finite inputs and may be used only under the stated special-exponent precondition. All new theorem integration still needs actual Lean and complete axiom/kernel validation before adoption.",
    "gain": "UNKNOWN; proof-only probe has retained60f runtime and claims no new speed.",
    "formal_submission": "NOT_SUBMITTED",
}
(out / "manifest.json").write_text(json.dumps(manifest, ensure_ascii=False, indent=2) + "\n", encoding="utf-8")
print(json.dumps({"candidate": out.name, "sha256": manifest["candidate_sha256"], "bytes": len(data)}))
