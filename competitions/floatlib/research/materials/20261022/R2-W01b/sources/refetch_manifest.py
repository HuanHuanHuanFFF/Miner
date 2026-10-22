#!/usr/bin/env python3
"""Fetch only pinned public text listed in source_manifest.json; verify both hashes."""
import concurrent.futures
import hashlib
import json
from pathlib import Path
import urllib.request

ROOT = Path(__file__).resolve().parent
MANIFEST = json.loads((ROOT / "source_manifest.json").read_text())

def fetch(row):
    # URLs and relative paths are fixed public-source records from the delivered manifest.
    url = row["url"]
    assert url.startswith("https://raw.githubusercontent.com/")
    request = urllib.request.Request(url, headers={"User-Agent": "R2-W01b-fixed-public-source-check"})
    with urllib.request.urlopen(request, timeout=45) as response:
        data = response.read()
    assert len(data) == row["bytes"]
    assert hashlib.sha256(data).hexdigest() == row["sha256"]
    assert hashlib.sha1(f"blob {len(data)}\0".encode() + data).hexdigest() == row["git_blob_sha1"]
    relative = Path(row["repository"]) / row["resolved_commit"] / row["path"]
    assert not relative.is_absolute() and ".." not in relative.parts
    path = ROOT / "recovered_text" / relative
    path.parent.mkdir(parents=True, exist_ok=True)
    path.write_bytes(data)
    return {"path": str(relative), "verified": True}

if __name__ == "__main__":
    with concurrent.futures.ThreadPoolExecutor(max_workers=4) as pool:
        rows = list(pool.map(fetch, MANIFEST))
    print(json.dumps({"files_verified": len(rows), "destination": str(ROOT / "recovered_text")}))
