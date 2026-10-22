"""Build and verify the reproducible R2-W04 deliverable archive."""
from pathlib import Path
import hashlib
import json
import shutil
import zipfile

ROOT = Path(__file__).resolve().parent.parent
DEST = ROOT.parent / "deliverables"
DEST.mkdir(exist_ok=True)

def sha(data):
    return hashlib.sha256(data).hexdigest()

kernel = ROOT / "Kernel.lean"
assert kernel.stat().st_size == 68415
assert sha(kernel.read_bytes()) == "98cef0f25c29fe22cf7fa32cc3fb0f2bc38bf1faf65f91aae4fd2d995fe13d84"
source_records = json.loads((ROOT / "SOURCES.json").read_text())["sources"]
for source in source_records:
    b = (ROOT / source["local_path"]).read_bytes()
    assert len(b) == source["bytes"] and sha(b) == source["sha256"], source["local_path"]
paths = [s["local_path"] for s in source_records]
paths += [
    "Kernel.lean", "Kernel.diff", "R2-W04.md", "SOURCES.json",
    "evidence/parent-verification.json", "evidence/environment.json",
    "evidence/scope-integrity.json", "evidence/static-checks.json",
    "evidence/compile-attempt.json",
    "work/prepare-block.lean.txt", "work/bmm-block.lean.txt",
    "work/api-review.md", "work/cost-edge-review.md",
    "work/assemble.py", "work/static_checks.py", "work/attempt_compile.py",
    "work/compile_existing.py", "work/package.py",
    "work/symbolic_prepare_model.py", "work/symbolic_prepare_results.json",
    "diagnostics/Print.commands.txt",
    "upstream/lean-core-review/SOURCES.json", "upstream/floatlib/SOURCES.json",
]
paths = sorted(set(paths))
manifest = "".join(f"{sha((ROOT/p).read_bytes())}  {p}\n" for p in paths)
(ROOT / "SHA256SUMS.txt").write_text(manifest)
all_paths = sorted(paths + ["SHA256SUMS.txt"])
zip_path = DEST / "R2-W04.zip"
with zipfile.ZipFile(zip_path, "w", compression=zipfile.ZIP_DEFLATED, compresslevel=9) as archive:
    for relative in all_paths:
        entry = zipfile.ZipInfo("R2-W04/" + relative, date_time=(2026, 10, 22, 0, 0, 0))
        entry.compress_type = zipfile.ZIP_DEFLATED
        entry.external_attr = 0o100644 << 16
        archive.writestr(entry, (ROOT / relative).read_bytes())
with zipfile.ZipFile(zip_path) as archive:
    bad = archive.testzip()
    assert bad is None, bad
    for line in archive.read("R2-W04/SHA256SUMS.txt").decode().splitlines():
        expected, relative = line.split("  ", 1)
        assert sha(archive.read("R2-W04/" + relative)) == expected, relative
    assert archive.read("R2-W04/Kernel.lean") == kernel.read_bytes()
    assert len(archive.namelist()) == len(all_paths)
report = DEST / "R2-W04.md"
shutil.copyfile(ROOT / "R2-W04.md", report)
external = DEST / "R2-W04-SHA256.txt"
external.write_text("".join(f"{sha(p.read_bytes())}  {p.name}\n" for p in [report, zip_path]))
receipt = {
    "status": "PASS", "zip_crc": "PASS",
    "zip_entries": len(all_paths), "internal_sha256_entries": len(paths),
    "exact_kernel_bytes_preserved": True,
    "sources_verified_against_provenance": len(source_records),
    "deliverables": [{"name": p.name, "path": str(p), "bytes": p.stat().st_size,
                      "sha256": sha(p.read_bytes())} for p in [report, zip_path, external]],
    "kernel_sha256": sha(kernel.read_bytes()),
    "lean_compile": "NOT_RUN", "axiom_audit": "NOT_RUN", "performance": "NOT_RUN",
}
(DEST / "package-verification.json").write_text(json.dumps(receipt, indent=2) + "\n")
print(json.dumps(receipt, indent=2))
