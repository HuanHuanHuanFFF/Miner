"""Owned native-only patch; upstream full source must remain private/ephemeral.

Original correct is renamed retainedCorrect and binds retainedKernels only.
There is deliberately no new Submission.correct or original-gate claim.
"""
from pathlib import Path
import argparse
import datetime
import hashlib
import importlib.util
import json
import re
import sys

sys.dont_write_bytecode = True
HERE = Path(__file__).resolve().parent
ROOT = next(p for p in HERE.parents if (p / "AGENTS.md").is_file())
BASE = "e2c1f1f1ba52e32563fb193ceea7e2a271b989fd3ba2eb16cff747987879b521"
HELPER = ROOT / "competitions/torchlean/candidates/r27-5h-20261029T194443Z/research/fp-cost/LazyFPOnly.lean"
HELPER_SHA = "1762a473178d3a45b431c94b995a2616fd4b939dd5b98d65f40ada71dfc2c892"


def sha(data):
    return hashlib.sha256(data).hexdigest()


def transform(data, submission=12, variant="fp-only-lazy"):
    assert submission == 12 and variant == "fp-only-lazy"
    assert sha(data) == BASE
    helper = HELPER.read_bytes()
    assert sha(helper) == HELPER_SHA
    assert helper.startswith(b"import ContractExact\n")
    original = data.decode("utf-8")
    marker = "def kernels:Kernels where"
    assert original.count(marker) == 1
    prefix, tail = original.split(marker)
    tail = marker + tail
    assert tail.count("theorem correct:") == 1
    tail = re.sub(r"\bkernels\b", "retainedKernels", tail)
    tail = re.sub(r"\bcorrect\b", "retainedCorrect", tail)
    wrapper = """

namespace Submission
open ExactRuntime

/- Native exploration only. retainedCorrect still proves retainedKernels,
   not this new record; the original gate must reject it as a submission. -/
def kernels : Kernels :=
  { retainedKernels with
    dense := { retainedKernels.dense with
      linear := fun rows k outW relu X W b =>
        R27FPOnly.linear (fun row col =>
          YaU X W b k row col (Yc X k row) (Yc W k col))
          rows k outW relu X W b } }

end Submission
"""
    result = (prefix + tail + "\n" + helper.decode().split("\n", 1)[1] + wrapper).encode()
    assert len(result) <= 256000
    assert result.decode().count("import ContractExact") == 1
    assert "theorem retainedCorrect:" in result.decode()
    assert "theorem correct:" not in result.decode()
    return result


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--source", type=Path, required=True)
    ap.add_argument("--output", type=Path, required=True)
    ap.add_argument("--receipt", type=Path, required=True)
    args = ap.parse_args()
    data = args.source.read_bytes()
    new = transform(data)
    loader = ROOT / "competitions/torchlean/candidates/r27-5h-20261029T194443Z/development/native/patch_public.py"
    spec = importlib.util.spec_from_file_location("r27_fp_only_policy", loader)
    mod = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(mod)
    policy = mod.policy_check(new)
    args.output.parent.mkdir(parents=True, exist_ok=True)
    args.output.write_bytes(new)
    receipt = {"at_utc": datetime.datetime.now(datetime.timezone.utc).isoformat(),
               "base_submission": 12, "base_sha256": sha(data),
               "patch_sha256": sha(Path(__file__).read_bytes()), "helper_sha256": HELPER_SHA,
               "candidate_sha256": sha(new), "candidate_bytes": len(new), "policy": policy,
               "runtime_entry": "Submission.kernels; all12 fields present, linear replaced",
               "proof_entry": "Submission.retainedCorrect proves retainedKernels ONLY",
               "new_correct": "ABSENT_UNPROVED_NATIVE_ONLY_NOT_ADMISSIBLE",
               "fallback": "Original predecessor12 YaU scalar exact-word single-dot callback; original Yc metadata scans execute only on a certification miss; YaU retains its original Yai fallback",
               "comparison": "Current normalized_mlp43 snapshot only via labeled compatible report calibration or UNKNOWN",
               "full_source_publication": "LOCAL_PRIVATE_OR_RUNNER_EPHEMERAL_ONLY",
               "native_compile": "NOT_RUN", "speed": "UNKNOWN"}
    args.receipt.write_text(json.dumps(receipt, ensure_ascii=False, indent=2) + "\n", encoding="utf-8", newline="\n")
    print(json.dumps(receipt, ensure_ascii=False))


if __name__ == "__main__":
    main()
