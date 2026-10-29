"""Verify received Git blobs and emit an import-only public dependency receipt."""
from pathlib import Path
import hashlib
import json
import re

here = Path(__file__).resolve().parent
evidence = json.loads((here / "upstream-source-evidence.json").read_text(encoding="utf-8"))
rows = []
for row in evidence["records"]:
    blob = row["content"].encode("utf-8")
    git_sha = hashlib.sha1(b"blob " + str(len(blob)).encode() + b"\0" + blob).hexdigest()
    assert git_sha == row["sha"], (row["display_url"], git_sha, row["sha"])
    rows.append({"url": row["display_url"], "git_blob_sha1": row["sha"], "content_sha256": hashlib.sha256(blob).hexdigest(), "bytes": len(blob), "imports": re.findall(r"(?m)^(?:public )?(?:meta )?import (.+)$", row["content"])})
result = {
    "status": "FIXED_SOURCE_IMPORT_PATH_VERIFIED_LEAN_NOT_RUN",
    "required_candidate_import": "ContractExact",
    "paths": [
        ["ContractExact", "ExactToolkit.Values", "ExactToolkit.Decode", "ExactToolkit.Congr", "ExactToolkit.Round", "FloatLib", "FloatLib.Floats", "FloatLib.Floats.Formats", "FloatLib.Floats.Formats.BinaryInterchange", "FloatLib.Floats.Formats.BinaryInterchange.Configured"],
        ["ContractExact", "ExactToolkit.Values", "ExactToolkit.Limbs", "Mathlib"],
    ],
    "needed_barrel_modules": ["Model.Carrier", "Model.Lean", "Model.ExactValue", "Semantics", "Configured", "Configured.Conversion.Proof"],
    "claim_limit": "The fixed source import path reaches the modules and tactics used by the carrier. Only a real Lean build confirms elaboration and availability of every declaration.",
    "upstream_sources": rows,
    "private_evidence_sha256": hashlib.sha256((here / "upstream-source-evidence.json").read_bytes()).hexdigest(),
    "public_full_source_evidence": False,
}
(here / "import-closure.json").write_text(json.dumps(result, indent=2) + "\n", encoding="utf-8")
print(json.dumps({"status": result["status"], "verified_git_blobs": len(rows)}))
