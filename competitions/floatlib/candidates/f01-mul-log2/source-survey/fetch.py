"""Read-only official source availability snapshot; no credentials or submission."""

import hashlib
import json
import urllib.error
import urllib.request
from datetime import datetime, timezone
from pathlib import Path

root = Path(__file__).resolve().parent
rows = []
for key, endpoint in [
    ("champions", "champions"),
    ("source174", "submissions/174/source"),
    ("source165", "submissions/165/source"),
    ("source147", "submissions/147/source"),
]:
    url = "https://conjectures.io/v1/competitions/floatlib/" + endpoint
    now = datetime.now(timezone.utc).isoformat()
    try:
        request = urllib.request.Request(
            url, headers={"User-Agent": "Mozilla/5.0", "Accept": "application/json"}
        )
        with urllib.request.urlopen(request, timeout=10) as response:
            body = response.read()
            code = response.status
    except urllib.error.HTTPError as error:
        body, code = error.read(), error.code
    except Exception as error:
        rows.append({"key": key, "url": url, "queried_at_utc": now,
                     "status": "ERROR", "error": str(error)})
        continue
    (root / (key + ".raw")).write_bytes(body)
    rows.append({"key": key, "url": url, "queried_at_utc": now,
                 "http_status": code, "sha256": hashlib.sha256(body).hexdigest(),
                 "bytes": len(body), "file": key + ".raw"})
(root / "network-receipts.json").write_text(json.dumps(rows, indent=2) + "\n", encoding="utf-8")
print(json.dumps(rows))
