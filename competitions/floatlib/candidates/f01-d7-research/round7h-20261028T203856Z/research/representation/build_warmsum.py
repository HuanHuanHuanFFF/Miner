"""Build an exact public SUM replacement; no compiler, CI, or benchmark runs here."""
from pathlib import Path
import datetime, hashlib, json

HERE = Path(__file__).resolve().parent
ROOT = next(p for p in HERE.parents if (p / "AGENTS.md").is_file())
CANDIDATES = ROOT / "competitions/floatlib/candidates"
BASE = CANDIDATES / "f01-r15-dev-packed-b2-1/Kernel.lean"
sha = lambda b: hashlib.sha256(b).hexdigest()
raw = BASE.read_bytes()
assert sha(raw) == "622d8394a7127e93dcaf992c62c6dfcff7208d212738409a5e34525dfafd1a58"
base = raw.decode()
old = "def sum {n : Nat} (x : Vector Binary32 n) : Binary32 := R7SinglePassSum.run x"
assert base.count(old) == 1
base = base.replace(old, "def sumBeforeR24Representation {n : Nat} (x : Vector Binary32 n) : Binary32 := R7SinglePassSum.run x")
start = base.index("def sumBeforeR24Representation")
end = base.index("end Submission", start)
block = base[start:end]
assert "theorem sum_spec" in block
block = block.replace("theorem sum_spec", "theorem sumBeforeR24Representation_spec")
block = block.replace("sum x", "sumBeforeR24Representation x")
base = base[:start] + block + base[end:]
fragment = (HERE / "WarmSum.lean.inc").read_bytes()
entry = """
namespace Submission
open FloatLib.Floats Competition
def sum {n : Nat} (x : Vector Binary32 n) : Binary32 := R24RepresentationWarmSum.run x
theorem sum_spec : ∀ (n : Nat) (x : Vector Binary32 n), sum x = sumSpec x.get := by
  exact R24RepresentationWarmSum.run_spec
end Submission
""".encode("utf-8")
blob = base.encode() + b"\n" + fragment + entry
assert len(blob) <= 256000
out = CANDIDATES / "f01-r24-research-representation-warmsum1"
out.mkdir(exist_ok=True)
(out / "Kernel.lean").write_bytes(blob)
helper = "f01-d7-research/round9h-20261026T194639Z/development-helper-audit-v8.py"
roots = ["Submission.R24RepresentationWarmSum." + n for n in ("loop_eq", "run_eq", "run_spec")]
manifest = dict(candidate=out.name, candidate_file="Kernel.lean", candidate_sha256=sha(blob),
    candidate_bytes=len(blob), created_at_utc=datetime.datetime.now(datetime.timezone.utc).isoformat(),
    validation_mode="statement-only", diagnostic_only=True, diagnostic_timeout_seconds=240,
    proof_status="NOT_RUN", performance="NOT_RUN", formal_submission="NOT_SUBMITTED",
    official_submission_inherited=False, helper_audit_module="development-helper-audit-v8.py",
    helper_audit_module_path=helper, helper_audit_module_sha256=sha((CANDIDATES / helper).read_bytes()),
    explicit_helper_audit=roots, helper_audit_required_endpoints=roots, helper_audit_expected_count=len(roots),
    helper_audit_source_sha256=sha(blob), diagnostic_evaluations=[],
    runtime_base_sha256=sha(raw), fragment_sha256=sha(fragment),
    public_endpoints={"add":"unchanged B2", "mul":"unchanged B2", "sum":"warm-prefix replacement", "bmm":"unchanged B2"},
    scope="Actual public SUM replacement with all-input loop transport draft. One hot-to-original transfer; no return record or resumption. No new compiler attribute/FFI/unsafe. First falsifier: actual warm backedge still spills acc or calls decoder/allocation each warm element.")
(out / "manifest.json").write_text(json.dumps(manifest, indent=2) + "\n", encoding="utf-8")
print(json.dumps({"candidate": out.name, "bytes":len(blob), "sha256":sha(blob), "roots":roots}))
