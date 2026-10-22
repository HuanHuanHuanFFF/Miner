from pathlib import Path
import difflib
import hashlib
import json

ROOT = Path(__file__).resolve().parent.parent
parent = (ROOT / "upstream/Kernel.parent.lean").read_bytes()
assert len(parent) == 64087
assert hashlib.sha256(parent).hexdigest() == "5be0735a90d58d9efb8ee2c6d666c11029bca66665dca03b6b5eff5baf6cbfc4"
text = parent.decode("utf-8")
start = text.index("namespace CheckedFloatArray\n")
dot_start = text.index("def dotLoop ", start)
bmm_start = text.index("def bmm ", dot_start)
prep = (ROOT / "work/prepare-block.lean.txt").read_text()
bmm = (ROOT / "work/bmm-block.lean.txt").read_text()
candidate = text[:start] + prep + text[dot_start:bmm_start] + bmm
target = ROOT / "Kernel.lean"
target.write_text(candidate, encoding="utf-8", newline="")
patch = "".join(difflib.unified_diff(text.splitlines(keepends=True), candidate.splitlines(keepends=True), fromfile="parent/Kernel.lean", tofile="candidate/Kernel.lean"))
(ROOT / "Kernel.diff").write_text(patch, encoding="utf-8", newline="")
assert candidate[:start] == text[:start]
assert candidate[candidate.index("def dotLoop ", start):candidate.index("def bmm ", start)] == text[dot_start:bmm_start]
for marker, end in [("@[inline] def encode", "\n\n"), ("@[inline] def read", "\n\n")]:
    old = text[text.index(marker, start):].split(end, 1)[0]
    new = candidate[candidate.index(marker, start):].split(end, 1)[0]
    assert old == new
record = {
    "parent_sha256": hashlib.sha256(parent).hexdigest(),
    "kernel_bytes": target.stat().st_size,
    "kernel_sha256": hashlib.sha256(target.read_bytes()).hexdigest(),
    "prefix_before_CheckedFloatArray_byte_identical": True,
    "CheckedFloatArray_dotLoop_through_dot_eq_byte_identical": True,
    "CheckedFloatArray_encode_byte_identical": True,
    "CheckedFloatArray_read_byte_identical": True,
    "only_changed_regions": ["CheckedFloatArray preparation/check/proofs", "bmm and bmm_spec"],
    "lean_elaboration": "NOT_RUN",
}
(ROOT / "evidence/scope-integrity.json").write_text(json.dumps(record, indent=2) + "\n")
print(json.dumps(record, indent=2))
