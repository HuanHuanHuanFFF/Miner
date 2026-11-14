"""Read-only source lineage/minimal-prefix inventory; no carrier or Lean run."""
from pathlib import Path
from datetime import datetime, timezone
import hashlib
import json

HERE = Path(__file__).resolve().parent
ROOT = next(p for p in HERE.parents if (p / "AGENTS.md").is_file())
R24 = ROOT / "competitions/floatlib/candidates/f01-d7-research/round7h-20261028T203856Z"
runtime_path = R24 / "development-dot-cost/PortableF64Dot-tail-v2.lean.inc"
measured_path = R24 / "ci-runs/40811305126/download-daa0fb1a3e304ebd8555ece28d2d6dab/diagnostics/f01-d7-public-suite/public-suite/inputs/f01-r24-dev-dot-bank-cost2/Kernel.lean"
sha = lambda b: hashlib.sha256(b).hexdigest()
raw = runtime_path.read_bytes()
measured = measured_path.read_bytes()
namespace = b"namespace Submission.R24PortableF64"
end_namespace = b"end Submission.R24PortableF64"

def region(blob, begin, end):
    start = blob.index(begin)
    return blob[start:blob.index(end, start) + len(end)]

runtime_region = region(raw, namespace, end_namespace)
measured_region = region(measured, namespace, end_namespace)
assert runtime_region.replace(b"\r\n", b"\n") == measured_region.replace(b"\r\n", b"\n")
text = raw.decode().replace("\r\n", "\n")
pairs = [
    ("Prepared", "structure Prepared where", "@[inline] def index32"),
    ("index32", "@[inline] def index32", "/-- Exact finite-word widening recipe"),
    ("widenBits", "@[inline] def widenBits", "def prepare ("),
    ("prepare", "def prepare (", "@[inline] def ceilLog2"),
    ("ceilLog2", "@[inline] def ceilLog2", "@[inline] def finite64"),
    ("sumRemaining", "def sumRemaining (", "/-- Zero is a miss sentinel"),
]
declarations = []
for name, begin, end in pairs:
    start = text.index(begin)
    fragment = text[start:text.index(end, start)].rstrip() + "\n"
    declarations.append({"name": "Submission.R24PortableF64." + name, "bytes_lf": len(fragment.encode()), "sha256_lf": sha(fragment.encode()), "line_start": text[:start].count("\n") + 1})
report = {
    "at_utc": datetime.now(timezone.utc).isoformat(),
    "status": "EXACT_SOURCE_LINEAGE_VERIFIED_NOT_A_PROOF_OR_TIMING_RECHECK",
    "runtime_path": runtime_path.relative_to(ROOT).as_posix(),
    "runtime_sha256": sha(raw),
    "measured_cost_kernel_path": measured_path.relative_to(ROOT).as_posix(),
    "measured_cost_kernel_sha256": sha(measured),
    "runtime_namespace_raw_byte_equal": runtime_region == measured_region,
    "runtime_namespace_lf_equal": True,
    "runtime_namespace_sha256": sha(runtime_region),
    "runtime_namespace_bytes": len(runtime_region),
    "minimum_producer_and_tail_declarations": declarations,
    "selected_declaration_bytes_lf": sum(x["bytes_lf"] for x in declarations),
    "additional_runtime_dependency": "Existing exact sx/sr/fastLog2 declarations already in actual-bridge/ActualRuntime.lean.inc; no other B2 runtime needed.",
    "scope": "The analyzed actual prepare and widening are byte-bound to the R24 measured dot-bank-cost2 candidate. R24 cost ratios remain synthetic, not TorchLean full-model evidence. No producer equality theorem is claimed.",
}
(HERE / "producer-prefix-receipt.json").write_text(json.dumps(report, indent=2) + "\n")
print(json.dumps({"status": report["status"], "raw_byte_equal": report["runtime_namespace_raw_byte_equal"], "selected_bytes": report["selected_declaration_bytes_lf"]}))
