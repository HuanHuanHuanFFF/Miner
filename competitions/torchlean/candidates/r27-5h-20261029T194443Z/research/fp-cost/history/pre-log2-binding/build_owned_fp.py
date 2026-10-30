"""Create an entirely project-owned FP experiment without website sources.

All12 runtime entries exist. Original correctness is renamed and proves the
old control only. New correctness/performance is NOT established here.
"""
from pathlib import Path
import hashlib
import importlib.util
import json
import re
import sys
import datetime

sys.dont_write_bytecode = True
HERE = Path(__file__).resolve().parent
ROOT = next(p for p in HERE.parents if (p / "AGENTS.md").is_file())
BASE = ROOT / "competitions/torchlean/candidates/r25-90m-20261029T064916Z/development/contract-port/norm-cache-proof1/Kernel.lean"
HELPER = HERE / "LazyFPOnly.lean"


def main():
    raw, helper = BASE.read_bytes(), HELPER.read_bytes()
    assert hashlib.sha256(raw).hexdigest() == "bcb8172381346b26afc69e2582442510865f74415c657d7ee208045474ca1ea7"
    assert hashlib.sha256(helper).hexdigest() == "7cc98e2bea5096e486800075e3f192589b9b1c35f277fe5af344b7fbf7626b21"
    text = raw.decode()
    marker = "def kernels : Kernels where"
    assert text.count(marker) == 1
    prefix, tail = text.split(marker)
    tail = marker + tail
    tail = re.sub(r"\bkernels\b", "ownedControlKernels", tail)
    tail = re.sub(r"\bcorrect\b", "ownedControlCorrect", tail)
    wrapper = """

namespace Submission
open ExactRuntime
/- New runtime is unproved. ownedControlCorrect proves ownedControlKernels. -/
def kernels : Kernels :=
  { ownedControlKernels with dense := { ownedControlKernels.dense with
    linear := fun rows k outW relu X W b =>
      R27FPOnly.linear (fun row col => dotFn (k + 1)
        (fun t => if t < k then X[row * k + t]! else oneW)
        (fun t => if t < k then W[col * k + t]! else b[col]!))
        rows k outW relu X W b } }
end Submission
"""
    result = (prefix + tail + "\n" + helper.decode().split("\n", 1)[1] + wrapper).encode()
    assert len(result) <= 256000
    assert "theorem correct :" not in result.decode()
    target = HERE / "owned-only/Kernel.lean"
    target.parent.mkdir(parents=True, exist_ok=True)
    target.write_bytes(result)
    loader = ROOT / "competitions/torchlean/candidates/r27-5h-20261029T194443Z/development/native/patch_public.py"
    spec = importlib.util.spec_from_file_location("r27_owned_fp_policy", loader)
    mod = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(mod)
    report = {"at_utc": datetime.datetime.now(datetime.timezone.utc).isoformat(),
              "source": str(target.relative_to(ROOT)), "bytes": len(result),
              "sha256": hashlib.sha256(result).hexdigest(), "policy": mod.policy_check(result),
              "scope": "UNPROVED_NATIVE_ONLY; no Submission.correct for new kernels",
              "old_correct": "ownedControlCorrect proves ownedControlKernels only",
              "source_website_dependency": False,
              "all12_interface": "Actual record contains all12; only dense.linear replaced",
              "fallback": "Already-proved project-owned dotFn, exact unactivated bias-inclusive dot",
              "target": "MLP champion33 last snapshot; norm speed irrelevant to this board",
              "performance": "UNKNOWN; never score original/control as performance target",
              "source_policy": "Existing published project-owned bytes only; full experiment may be committed by D",
              "required": "Pinned compile first. If cached strong current-chain anchor unavailable, standalone profile/checksum only, current multiplierUNKNOWN; do not substitute a new shipped/control comparison."}
    (HERE / "owned-fp-receipt.json").write_text(json.dumps(report, ensure_ascii=False, indent=2) + "\n", encoding="utf-8", newline="\n")
    print(json.dumps(report, ensure_ascii=False))


if __name__ == "__main__":
    main()
