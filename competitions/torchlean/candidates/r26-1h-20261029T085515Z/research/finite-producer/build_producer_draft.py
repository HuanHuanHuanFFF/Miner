"""Assemble the real producer chain for inspection, without compiling or queuing it."""
from pathlib import Path
from datetime import datetime, timezone
import hashlib
import json
import re
import types

HERE = Path(__file__).resolve().parent
ROOT = next(p for p in HERE.parents if (p / "AGENTS.md").is_file())
R25 = ROOT / "competitions/torchlean/candidates/r25-90m-20261029T064916Z"
R24 = ROOT / "competitions/floatlib/candidates/f01-d7-research/round7h-20261028T203856Z"
OLD = R25 / "research/widen"
sha = lambda b: hashlib.sha256(b).hexdigest()
inputs = []

def read(path):
    blob = path.read_bytes()
    inputs.append({"path": path.relative_to(ROOT).as_posix(), "sha256": sha(blob), "bytes": len(blob)})
    return blob.decode("utf-8").replace("\r\n", "\n")

def between(source, first, last):
    i = source.index(first)
    return source[i:source.index(last, i)].rstrip() + "\n"

base_path = ROOT / "competitions/floatlib/candidates/f01-r15-dev-packed-b2-1/Kernel.lean"
assert sha(base_path.read_bytes()) == "622d8394a7127e93dcaf992c62c6dfcff7208d212738409a5e34525dfafd1a58"
base = read(base_path)
base_c = base[base.index("namespace R2W01c"):]
mul_support = between(base_c, "namespace NativeBridge", "theorem toModelNativeMul")
assert len(re.findall(r"(?m)^theorem ", mul_support)) == 4
mul_support = "namespace R2W01c\n" + mul_support + "\nend NativeBridge\nend R2W01c\n"
finite = read(OLD / "finite-bridge/FiniteWidenCarrier.lean")
runtime = read(R24 / "development-dot-cost/PortableF64Dot-tail-v2.lean.inc")
prepare_runtime = read(OLD / "prepare-bridge/PrepareRuntime.lean.inc")
ceil_tail_runtime = "namespace Submission.R24PortableF64\n" + between(runtime, "@[inline] def ceilLog2", "@[inline] def finite64")
ceil_tail_runtime += between(runtime, "def sumRemaining (", "/-- Zero is a miss sentinel.") + "\nend Submission.R24PortableF64\n"
pieces = [finite, prepare_runtime, read(OLD / "prepare-bridge/PrepareAgreement.lean.inc"),
          read(HERE / "PreparePeak.lean.inc"), ceil_tail_runtime,
          read(HERE / "PreparedParameters.lean.inc"), mul_support,
          read(R24 / "research/rounding-review/NativeMul-v4.lean.inc"),
          read(R24 / "research/representation/NativeSumEnclosure3.lean.inc"),
          read(R24 / "research/rounding-review/RadiusEndpoints-v1.lean.inc"),
          read(HERE / "TailAgreement.lean.inc"), read(HERE / "ProducerNumerics.lean.inc"),
          read(HERE / "ProducerEnclosure.lean.inc")]
source = "\n\n".join(pieces)
assert re.findall(r"(?m)^import .*", source) == ["import ContractExact"]
out = HERE / "producer-draft/ProducerContractOnly.lean"
out.parent.mkdir(exist_ok=True)
out.write_bytes(source.encode("utf-8"))
(out.parent / "NativeMulSupport.lean.inc").write_bytes(mul_support.encode("utf-8"))
policy_path = R25 / "verification/exact-policy-preflight.py"
policy_module = types.ModuleType("pinned_policy")
policy_module.__file__ = str(policy_path)
exec(compile(policy_path.read_bytes(), str(policy_path), "exec"), policy_module.__dict__)
ns, policy_sources = policy_module.load_official_policy()
wrapped = policy_module.Utf8Path(out)
intake = ns["intake"](wrapped, None)
policy = ns["policy"](wrapped, None) if intake is None else None
result = {
    "created_at_utc": datetime.now(timezone.utc).isoformat(),
    "status": "INSPECTION_DRAFT_DO_NOT_QUEUE_BEFORE_FINITE_AND_PREPARE_REPAIRS",
    "path": out.relative_to(ROOT).as_posix(), "sha256": sha(out.read_bytes()), "bytes": out.stat().st_size,
    "intake": intake, "policy": policy, "policy_sources": policy_sources,
    "proof_status": "NOTRUN_KNOWN_FAILING_R25_FINITE_PREFIX_INCLUDED_UNCHANGED",
    "CI_request": False,
    "support_extraction": "13 retained W7 support declarations + 5 FastLog2 theorem declarations + 4 format-polymorphic NativeBridge helpers, no complete B2 runtime",
    "inputs": inputs,
    "roots": ["Submission.R26ProducerEnclosure." + n for n in
        ("prepared_product_bounded", "actualTerms_spec", "actualTerms_exactSum",
         "actual_tail_enclosure", "actual_tail_magnitude", "actual_radius_finite_value", "actual_endpoints_finite_real")],
    "boundary": "Actual original prepare, get!, native Float multiplication, Tail recursion, H/L/radius expression. No assumed B or enclosure premise; the source proof chain itself is not accepted.",
    "remaining_consumer": "Actual key/checker boundary transport and original exactdot rounder/fallback are separate.",
}
(out.parent / "receipt.json").write_text(json.dumps(result, indent=2) + "\n", encoding="utf-8")
print(json.dumps({k: result[k] for k in ("status", "path", "sha256", "bytes", "intake", "policy", "proof_status")}))
