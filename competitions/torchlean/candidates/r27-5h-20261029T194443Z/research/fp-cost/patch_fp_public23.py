"""One native-cost probe over the strong public23 normalization base.

The full third-party result stays private. Retained correctness only proves
retainedKernels. The new all12 record deliberately has no correct theorem.
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
BASE = "1010c0744f0506974c64601e8ce7335bea56d0cb21b655543d390794df0665fe"
FULL_HELPER = "1762a473178d3a45b431c94b995a2616fd4b939dd5b98d65f40ada71dfc2c892"
COMPACTOR = "4c3dd79284f6701d3b128687f9f973f47d9236f8d9db502d398e2eb4d131e129"


def sha(raw):
    return hashlib.sha256(raw).hexdigest()


def load_module(path, name):
    spec = importlib.util.spec_from_file_location(name, path)
    module = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(module)
    return module


def minimal_helper():
    """Remove only own unreachable old wrappers, preserving each used body."""
    original = (HERE / "LazyFPOnly.lean").read_bytes()
    assert sha(original) == FULL_HELPER
    text = original.decode()
    ranges = [
        ("structure Prepared where\n", "@[inline] def index32"),
        ("@[inline] def index32", "/-- Exact finite-word widening recipe"),
        ("def prepare (raw : Array UInt32)", "@[inline] def ceilLog2"),
        ("/-- Zero is a miss sentinel.", "end Submission.R24PortableF64"),
    ]
    removed = []
    for begin, end in ranges:
        a = text.index(begin)
        b = text.index(end, a)
        removed.append({"begin": begin, "bytes": len(text[a:b].encode()),
                        "sha256": sha(text[a:b].encode())})
        text = text[:a] + text[b:]
    raw = text.encode()
    # Every retained token/body comes from the parent-owned helper. The
    # receipt covers the removed sections; no algebraic optimization occurs.
    assert "structure Prepared where" not in text
    assert "def attemptPrepared" not in text
    assert "def prepareFn" in text and "def sumRemaining" in text
    return raw, removed


def transform(data, submission=23, variant="fp-only23-b8"):
    assert submission == 23 and variant == "fp-only23-b8"
    assert sha(data) == BASE
    path = HERE / "frozen_compact_public23.py"
    assert sha(path.read_bytes()) == COMPACTOR
    compact = load_module(path, "r27_fp23_compact").recipe(data)
    assert sha(compact) == "fc7b1e9e1b258f5254c75e046972fdc3bdc630b5b20fb35c9821839883c62019"
    helper, _ = minimal_helper()
    original = compact.decode()
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
/- Cost probe only; retainedCorrect proves the old record exclusively. -/
def kernels : Kernels :=
  { retainedKernels with dense := { retainedKernels.dense with
    linear := fun rows k outW relu X W b =>
      if rows < 2 then retainedKernels.dense.linear rows k outW relu X W b
      else R27FPOnly.linear (fun row col =>
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
    parser = argparse.ArgumentParser()
    parser.add_argument("--source", type=Path, required=True)
    parser.add_argument("--output", type=Path, required=True)
    parser.add_argument("--receipt", type=Path, required=True)
    args = parser.parse_args()
    result = transform(args.source.read_bytes())
    helper, removed = minimal_helper()
    (HERE / "FPOnlyMinimal.lean").write_bytes(helper)
    policy_module = load_module(ROOT / "competitions/torchlean/candidates/r27-5h-20261029T194443Z/development/native/patch_public.py", "r27_fp23_policy")
    policy = policy_module.policy_check(result)
    args.output.parent.mkdir(parents=True, exist_ok=True)
    args.output.write_bytes(result)
    receipt = {"at_utc": datetime.datetime.now(datetime.timezone.utc).isoformat(),
               "base_submission": 23, "base_sha256": BASE,
               "compacted_base_bytes": 248185, "compactor_sha256": COMPACTOR,
               "patch_sha256": sha(Path(__file__).read_bytes()),
               "full_owned_helper_sha256": FULL_HELPER,
               "minimal_helper_bytes": len(helper), "minimal_helper_sha256": sha(helper),
               "removed_own_sections": removed,
               "candidate_bytes": len(result), "candidate_sha256": sha(result),
               "free_bytes": 256000 - len(result), "policy": policy,
               "runtime": "All12; public23 layernorm/RMS/other11 retained. rows<2 uses exact original public23 linear; rows>=2 uses FP-only preparation/checker with lazy exact YaU/Yc scalar fallback.",
               "new_correct": "ABSENT_UNPROVED_NATIVE_ONLY_NOT_ADMISSIBLE",
               "old_correct": "retainedCorrect proves retainedKernels only",
               "why_new": "Newly available public23 and own proof-alias space recipe permit FP atop a much stronger normalization base; protects known expensive batch1 preparation rather than repeating old full-cache probe.",
               "measurement": "Pinned compile then one whole normalized_mlp cost discriminator. Current43 calibration only via compatible hash-bound report chain INFERRED; no new shipped/control performance comparison.",
               "native_compile": "NOT_RUN", "performance": "UNKNOWN",
               "publication": "Only own recipe/helper/receipt public; full constructed source private"}
    args.receipt.write_text(json.dumps(receipt, ensure_ascii=False, indent=2) + "\n", encoding="utf-8", newline="\n")
    print(json.dumps(receipt, ensure_ascii=False))


if __name__ == "__main__":
    main()
