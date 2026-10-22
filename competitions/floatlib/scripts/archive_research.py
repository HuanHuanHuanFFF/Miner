"""Extract the frozen R2-R5 deliveries and verify ordinary files; never delete inputs."""
from __future__ import annotations

import argparse
import hashlib
import json
from pathlib import Path, PurePosixPath
import re
import stat
import subprocess
from datetime import datetime, timezone
import zipfile

ROOT = Path(__file__).resolve().parents[3]
TRACK = ROOT / "competitions/floatlib"
DEST = TRACK / "research/materials/20261022"
INDEX = TRACK / "research/astra-collab-20261022-r5/download-index-final.json"
MANIFEST = DEST / "manifest.json"


def digest(data: bytes) -> str:
    return hashlib.sha256(data).hexdigest()


def relative(path: Path) -> str:
    return path.relative_to(ROOT).as_posix()


def safe_path(base: Path, name: str) -> Path:
    p = PurePosixPath(name)
    if (p.is_absolute() or "\\" in name or ":" in name or not p.parts
            or any(x in (".", "..") or x.endswith((".", " ")) for x in p.parts)):
        raise ValueError(f"Unsafe member: {name}")
    target = base.joinpath(*p.parts).resolve()
    if not target.is_relative_to(base.resolve()):
        raise ValueError(f"Outside destination: {name}")
    return target


def write_exact(path: Path, data: bytes) -> None:
    if path.exists():
        if path.read_bytes() != data:
            raise ValueError(f"Refuse to replace different existing bytes: {path}")
    else:
        path.parent.mkdir(parents=True, exist_ok=True)
        path.write_bytes(data)


def intake() -> None:
    if MANIFEST.exists():
        raise ValueError("Intake already exists; use verify")
    index = json.loads(INDEX.read_text(encoding="utf-8"))
    sources = index["files"]
    archives = [s for s in sources if s["path"].endswith(".zip")]
    if len(archives) != 12:
        raise ValueError("Expected exactly the frozen 12 research archives")
    for s in sources:
        p = Path(s["path"])
        if p.parent.resolve() != Path("E:/Download").resolve() or p.is_symlink():
            raise ValueError(f"Unexpected source location: {p}")
        data = p.read_bytes()
        if len(data) != s["bytes"] or digest(data) != s["sha256"]:
            raise ValueError(f"Source changed: {p.name}")

    rows, content_paths = [], {}
    for s in archives:
        source = Path(s["path"])
        package_id = re.search(r"R\d-W\d+[a-z]?", source.name).group()
        base = DEST / package_id
        members, by_name, seen = [], {}, set()
        with zipfile.ZipFile(source) as z:
            if sum(i.file_size for i in z.infolist()) > 50_000_000:
                raise ValueError("Unexpected expansion size")
            if z.testzip() is not None:
                raise ValueError(f"CRC failure: {source.name}")
            for info in z.infolist():
                target = safe_path(base, info.filename)
                key = info.filename.casefold()
                if key in seen or stat.S_ISLNK(info.external_attr >> 16):
                    raise ValueError(f"Duplicate or symlink: {info.filename}")
                seen.add(key)
                if info.is_dir():
                    continue
                data = z.read(info)
                write_exact(target, data)
                member = {"name": info.filename, "path": relative(target),
                          "bytes": len(data), "sha256": digest(data), "crc32": info.CRC}
                members.append(member)
                by_name[info.filename] = member
                content_paths.setdefault(digest(data), []).append(relative(target))
            checks = 0
            for name in by_name:
                if not PurePosixPath(name).name.startswith("SHA256SUMS"):
                    continue
                parent = PurePosixPath(name).parent
                for line in z.read(name).decode("utf-8-sig").splitlines():
                    if not line.strip():
                        continue
                    match = re.fullmatch(r"([0-9a-fA-F]{64})\s+\*?(.+)", line)
                    if not match:
                        raise ValueError(f"Unrecognized checksum line in {name}")
                    member_name = str(parent / match[2].removeprefix("./"))
                    if member_name not in by_name or by_name[member_name]["sha256"] != match[1].lower():
                        raise ValueError(f"Package checksum mismatch: {member_name}")
                    checks += 1
        rows.append({"id": package_id, "source_path": str(source),
                     "archive_bytes": s["bytes"], "archive_sha256": s["sha256"],
                     "crc": "PASS", "internal_checksums_verified": checks, "members": members})
    companions = []
    extra = Path("E:/Download/R2-W03-SHA256SUMS.txt")
    for s in [s for s in sources if not s["path"].endswith(".zip")] + ([{"path": str(extra)}] if extra.exists() else []):
        p = Path(s["path"])
        data = p.read_bytes()
        sha = digest(data)
        targets = content_paths.get(sha)
        if not targets:
            target = DEST / "companions" / p.name
            write_exact(target, data)
            targets = [relative(target)]
        companions.append({"source_path": str(p), "bytes": len(data),
                           "sha256": sha, "path": targets[0]})
    payload = {"schema": 1, "created_at_utc": datetime.now(timezone.utc).isoformat(),
               "source_index": relative(INDEX), "source_index_sha256": digest(INDEX.read_bytes()),
               "scope": "FloatLib R2-R5 only; source files preserved byte-for-byte; no downloaded code executed",
               "archives": rows, "companions": companions,
               "archive_count": len(rows), "member_count": sum(len(r["members"]) for r in rows),
               "archive_bytes": sum(r["archive_bytes"] for r in rows),
               "member_bytes": sum(m["bytes"] for r in rows for m in r["members"])}
    MANIFEST.write_text(json.dumps(payload, ensure_ascii=False, indent=2) + "\n", encoding="utf-8")
    print(json.dumps({k: payload[k] for k in ("archive_count", "member_count", "archive_bytes", "member_bytes")}))


def verify(check_git: bool, check_archives: bool) -> None:
    manifest = json.loads(MANIFEST.read_text(encoding="utf-8"))
    checked = {}
    for entry in [m for a in manifest["archives"] for m in a["members"]] + manifest["companions"]:
        path = safe_path(ROOT, entry["path"])
        data = path.read_bytes()
        if len(data) != entry["bytes"] or digest(data) != entry["sha256"]:
            raise ValueError(f"Changed extracted file: {entry['path']}")
        checked[entry["path"]] = entry["sha256"]
    if check_git:
        for name, sha in checked.items():
            data = subprocess.run(["git", "show", f"HEAD:{name}"], cwd=ROOT,
                                  check=True, capture_output=True).stdout
            if digest(data) != sha:
                raise ValueError(f"Committed bytes differ: {name}")
    if check_archives:
        for a in manifest["archives"]:
            data = Path(a["source_path"]).read_bytes()
            if len(data) != a["archive_bytes"] or digest(data) != a["archive_sha256"]:
                raise ValueError(f"Changed input: {a['source_path']}")
    print(json.dumps({"status": "PASS", "archives": manifest["archive_count"],
                      "members": manifest["member_count"], "unique_paths": len(checked),
                      "committed_bytes_checked": check_git, "source_archives_checked": check_archives}))


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("action", choices=("intake", "verify"))
    parser.add_argument("--git", action="store_true")
    parser.add_argument("--archives", action="store_true")
    args = parser.parse_args()
    if args.action == "intake":
        intake()
    else:
        verify(args.git, args.archives)
