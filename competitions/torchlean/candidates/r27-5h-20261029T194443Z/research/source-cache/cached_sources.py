"""Bounded transport for two already-lawfully-captured public research inputs.

No HTTP, Git, credential operation or CI dispatch. Private chunks may be fed
by D to masked repository Actions data secrets; never commit/publish chunks.
Only the exact approved source hashes can be decoded. This is not a generic
archive unpacker and never accepts a path from payload content.
"""
from pathlib import Path
import argparse
import base64
import datetime
import hashlib
import json
import lzma
import os

PINS = {
    12: ("e2c1f1f1ba52e32563fb193ceea7e2a271b989fd3ba2eb16cff747987879b521", 218232),
    27: ("f92ee2c9a29de78dc434ad158b7141c0e4b5a67a5a198a353d59a4703481aa67", 255647),
}
PART_NAMES = ["R27_RESEARCH_SOURCE_1", "R27_RESEARCH_SOURCE_2", "R27_RESEARCH_SOURCE_3"]
MAX_PART_CHARS = 35000
MAX_DECODED_BYTES = 600000


def sha(b):
    return hashlib.sha256(b).hexdigest()


def validate(bundle):
    assert bundle["version"] == 1
    files = bundle["files"]
    assert isinstance(files, list) and 1 <= len(files) <= len(PINS)
    result = {}
    for item in files:
        ident = item["submission"]
        assert ident in PINS and ident not in result
        data = item["source"].encode("utf-8")
        digest, size = PINS[ident]
        assert len(data) == item["bytes"] == size
        assert sha(data) == item["sha256"] == digest
        result[ident] = data
    return result


def encode(source_dir):
    files = []
    for ident in PINS:
        data = (source_dir / f"submission{ident}-Kernel.lean").read_bytes()
        files.append({"submission": ident, "source": data.decode("utf-8"),
                      "bytes": len(data), "sha256": sha(data)})
    bundle = {"version": 1, "files": files}
    validate(bundle)
    raw = json.dumps(bundle, ensure_ascii=False, separators=(",", ":")).encode()
    assert len(raw) <= MAX_DECODED_BYTES
    packed = lzma.compress(raw, preset=6)
    text = base64.b64encode(packed).decode("ascii")
    assert len(text) <= MAX_PART_CHARS * len(PART_NAMES)
    parts = [text[i:i + MAX_PART_CHARS] for i in range(0, len(text), MAX_PART_CHARS)]
    assert len(parts) == len(PART_NAMES)
    return parts, {"raw_bytes": len(raw), "packed_bytes": len(packed),
                   "encoded_chars": len(text), "packed_sha256": sha(packed)}


def decode(parts):
    assert len(parts) == len(PART_NAMES)
    assert all(isinstance(p, str) and 0 < len(p) <= MAX_PART_CHARS for p in parts)
    packed = base64.b64decode("".join(parts), validate=True)
    d = lzma.LZMADecompressor(memlimit=128 * 1024 * 1024)
    raw = d.decompress(packed, max_length=MAX_DECODED_BYTES + 1)
    assert len(raw) <= MAX_DECODED_BYTES and d.eof and not d.unused_data
    return validate(json.loads(raw)), sha(packed)


def write_receipt(path, value):
    value["at_utc"] = datetime.datetime.now(datetime.timezone.utc).isoformat()
    value["scope"] = "Previously captured research source bytes only; no credential, wallet or new network access"
    value["publication"] = "Own codec/hash receipt only; encoded parts and decoded full sources remain private"
    path.write_text(json.dumps(value, ensure_ascii=False, indent=2) + "\n", encoding="utf-8", newline="\n")
    print(json.dumps({k: value[k] for k in ["mode", "source_hashes", "packed_sha256", "at_utc"] if k in value}))


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("mode", choices=["pack", "unpack"])
    ap.add_argument("--source-dir", type=Path)
    ap.add_argument("--private-parts-dir", type=Path)
    ap.add_argument("--cache-dir", type=Path)
    ap.add_argument("--receipt", type=Path, required=True)
    args = ap.parse_args()
    if args.mode == "pack":
        assert args.source_dir and args.private_parts_dir
        parts, info = encode(args.source_dir)
        decoded, digest = decode(parts)
        assert all(decoded[i] == (args.source_dir / f"submission{i}-Kernel.lean").read_bytes() for i in PINS)
        args.private_parts_dir.mkdir(parents=True, exist_ok=True)
        for name, part in zip(PART_NAMES, parts):
            target = args.private_parts_dir / (name + ".txt")
            assert not target.is_symlink()
            if target.exists():
                assert target.read_text(encoding="ascii") == part
            else:
                target.write_text(part, encoding="ascii", newline="")
        write_receipt(args.receipt, {"mode": "PACKED_LOCAL_ONLY_ROUNDTRIP_PASS", **info,
            "parts": [{"name": n, "chars": len(p), "sha256": sha(p.encode())} for n, p in zip(PART_NAMES, parts)],
            "source_hashes": {str(i): sha(b) for i, b in decoded.items()},
            "external_upload": "NOT_PERFORMED_BY_R", "secret_values_are_credentials": False})
    else:
        assert args.cache_dir
        if args.private_parts_dir:
            parts = [(args.private_parts_dir / (n + ".txt")).read_text(encoding="ascii") for n in PART_NAMES]
        else:
            parts = [os.environ.get(n, "") for n in PART_NAMES]
        decoded, digest = decode(parts)
        folder = args.cache_dir.resolve()
        folder.mkdir(parents=True, exist_ok=True)
        for ident, data in decoded.items():
            target = folder / f"submission{ident}-Kernel.lean"
            assert not target.is_symlink() and target.resolve().parent == folder
            if target.exists():
                assert target.read_bytes() == data
            else:
                target.write_bytes(data)
        write_receipt(args.receipt, {"mode": "UNPACKED_EXACT_HASH_CACHE", "packed_sha256": digest,
            "source_hashes": {str(i): sha(b) for i, b in decoded.items()},
            "files": len(decoded), "network_calls": 0})


if __name__ == "__main__":
    main()
