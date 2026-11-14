"""Read-only source identity audit; outputs only a local receipt, never compiles."""
from pathlib import Path
from datetime import datetime, timezone
import hashlib
import json
import re

HERE = Path(__file__).resolve().parent
ROOT = next(p for p in HERE.parents if (p / "AGENTS.md").is_file())
sha = lambda b: hashlib.sha256(b).hexdigest()
rows = []
for receipt in (HERE / "prepare-v1/receipt.json", HERE / "producer-draft/receipt.json"):
    data = json.loads(receipt.read_bytes())
    entries = data.get("outputs", [data])
    for e in entries:
        p = ROOT / e["path"]
        raw = p.read_bytes()
        rows.append({"path": e["path"], "sha256": sha(raw), "bytes": len(raw),
                     "identity_matches_receipt": sha(raw) == e["sha256"] and len(raw) == e["bytes"],
                     "imports": [s.decode() for s in re.findall(rb"(?m)^import [^\r\n]*", raw)]})
fields = HERE / "sources/FloatLib-Fields-Proof.lean.raw"
raw = fields.read_bytes()
blob_sha = hashlib.sha1(b"blob " + str(len(raw)).encode() + b"\0" + raw).hexdigest()
source = {"path": str(fields.relative_to(ROOT)).replace("\\", "/"), "bytes": len(raw),
          "sha256": sha(raw), "git_blob_sha1": blob_sha,
          "expected_git_blob_sha1": "d77233aaebfe75066394f8c61900adcd48169db9",
          "pinned_ref": "0d91825727839f597fd06b22fdd038ea21480f0c",
          "url": "https://github.com/lean-dojo/FloatLib/blob/0d91825727839f597fd06b22fdd038ea21480f0c/FloatLib/Floats/Formats/BinaryInterchange/Model/Fields/Proof.lean"}
source["identity_matches_connector_blob"] = blob_sha == source["expected_git_blob_sha1"]
result = {"at_utc": datetime.now(timezone.utc).isoformat(), "files": rows,
          "pinned_primary_source": source, "Lean": "NOT_RUN", "native": "NOT_RUN",
          "new_proof_claim": False, "all_source_receipt_identities_match": all(r["identity_matches_receipt"] for r in rows)}
(HERE / "source-audit.json").write_text(json.dumps(result, indent=2) + "\n", encoding="utf-8")
print(json.dumps(result, indent=2))
