"""One controlled n=1 runtime composition; no inference of proof or speed.

Keep the existing dispatcher for all n != 1. Compute the exact scalar product
once, then change only a raw negative-zero result to positive zero.
"""
from datetime import datetime, timezone
import hashlib
import json
from pathlib import Path
import re


HERE = Path(__file__).resolve().parent
CANDIDATES = HERE.parent


def sha(data):
    return hashlib.sha256(data).hexdigest()


parent = CANDIDATES / "f01-d7-direct-nonfinite"
old_singleton = CANDIDATES / "f01-d7-singleton-proof1"
probe = CANDIDATES / "f01-d7-seed-normalize-probe"
raw = (parent / "Kernel.lean").read_bytes()
old = (old_singleton / "Kernel.lean").read_bytes()
probe_raw = (probe / "Kernel.lean").read_bytes()
proof_block = (HERE / "seed-normalize-block.lean").read_bytes()
assert sha(raw) == "97f77e2ce3f53dc3625349d5d2a7bc761570f9428c0b547070e37254c4960d26"
assert sha(old) == "dab15a44f753c1e8d4654d15ffc54eaa770702eeb42cf0cc601c91809418b21a"
assert sha(probe_raw) == "a1325da56ec17cbc73f83acc3fe8b4e9ea0b2edd379617b7b927514513249f4c"
assert sha(proof_block) == "c44c4afbbe117e97b857ac3541638f3cbee370ba86f837fc76be16c41d08ed26"
assert probe_raw == raw + b"\n\n" + proof_block

text = raw.decode()
start = text.rindex("\ndef bmm (batch m n p : Nat)")
tail = text[start:]
assert tail.count("theorem bmm_spec") == 1
renamed = re.sub(r"\bbmm\b", "bmmBeforeSingleton", tail)
renamed = renamed.replace("bmm_spec", "bmmBeforeSingleton_spec")
assert renamed.count("bmmBeforeSingleton") == 4
assert renamed.replace("bmmBeforeSingleton_spec", "bmm_spec").replace("bmmBeforeSingleton", "bmm") == tail

old_text = old.decode()
core_start = old_text.index("\ndef singletonCore ")
block_start = old_text.rfind("namespace Submission\n", 0, core_start)
singleton = old_text[block_start:]
before = "Submission.add posZero\n      (Submission.mul "
after = "D7SeedNormalize.normalizeProductSeedRaw\n      (Submission.mul "
assert singleton.count(before) == 1
singleton = singleton.replace(before, after, 1)
old_proof = "  dsimp only\n  simp only [Fin.foldl_succ, Fin.foldl_zero, Fin.val_zero]"
new_proof = "  dsimp only\n  rw [D7SeedNormalize.normalize_submission_mul_eq_add]\n  simp only [Fin.foldl_succ, Fin.foldl_zero, Fin.val_zero]"
assert singleton.count(old_proof) == 1
singleton = singleton.replace(old_proof, new_proof, 1)

data = (text[:start] + renamed).encode() + b"\n\n" + proof_block + b"\n\n" + singleton.encode()
assert len(data) < 256000
assert data.count(b"def bmm (") == 1
assert data.count(b"theorem bmm_spec :") == 1
assert data.count(b"def singletonCore ") == 1
out = CANDIDATES / "f01-d7-singleton-normalize"
out.mkdir(exist_ok=True)
(out / "Kernel.lean").write_bytes(data)
manifest = {
    "candidate": out.name,
    "candidate_file": "Kernel.lean",
    "candidate_sha256": sha(data),
    "candidate_bytes": len(data),
    "created_at_utc": datetime.now(timezone.utc).isoformat(),
    "parent": parent.name,
    "parent_sha256": sha(raw),
    "proof_probe": probe.name,
    "proof_probe_sha256": sha(probe_raw),
    "proof_block_sha256": sha(proof_block),
    "singleton_proof_source": old_singleton.name,
    "singleton_proof_source_sha256": sha(old),
    "singleton_original_suffix_sha256": sha(old_text[block_start:].encode()),
    "singleton_adapted_suffix_sha256": sha(singleton.encode()),
    "validation_mode": "statement-only",
    "proof_status": "NOT_RUN_MINIMAL_PROOF_PORT_AND_NEW_RUNTIME_COMPOSITION",
    "mechanism": "For general n=1, retain original output/address construction, compute Submission.mul once, then select UInt32 zero only when the exact product word is0x80000000. For every n!=1 use the exact original parent dispatcher. Existing add/mul/sum implementations are unchanged.",
    "proof_change": "Copy the frozen minimal seed proof block. The original singleton proof is changed only by rewriting normalize_submission_mul_eq_add before its existing Fin.foldl/zero/val_zero simplification. The final original bmm specification is retained with its renamed parent bridge.",
    "cost_boundary": "This uses the exact scalar multiply, including its guards and low-exponent fallback. The old direct native n=1 route can be cheaper on ordinary finite inputs; removing one add is not evidence of a whole-cost gain. Compare complete paired cost against direct-nonfinite, separately from the old singleton add control.",
    "source_identity": "All parent bytes before its final dispatcher are identical; the final dispatcher/spec are renamed only, not altered. No proof or performance inheritance from append-only probe, W10/W10b, old singleton or parent composition.",
    "gain": "UNKNOWN",
    "formal_submission": "NOT_SUBMITTED",
}
(out / "manifest.json").write_text(json.dumps(manifest, ensure_ascii=False, indent=2) + "\n", encoding="utf-8")
print(json.dumps({"candidate": out.name, "sha256": sha(data), "bytes": len(data), "status": "NOT_RUN"}))
