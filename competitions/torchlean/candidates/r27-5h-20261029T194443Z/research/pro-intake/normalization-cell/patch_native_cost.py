"""Own integration of Pro's strict rational-cell module; native cost only.

Complete public23 stays private. Old correctness is retained for old kernels
only. The exact new runtime is not proved or admissible.
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
PIN = "1010c0744f0506974c64601e8ce7335bea56d0cb21b655543d390794df0665fe"
NATIVE = "57b62a985875ea54a9ea6d227f32b492abcd1ce1ec7ff713cac7e04dc9e69866"
COMPACT = "4c3dd79284f6701d3b128687f9f973f47d9236f8d9db502d398e2eb4d131e129"


def sha(data):
    return hashlib.sha256(data).hexdigest()


def load(path, name):
    spec = importlib.util.spec_from_file_location(name, path)
    module = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(module)
    return module


def transform(data, submission=23, variant="normalization-rational-cell-cost"):
    assert submission == 23 and variant == "normalization-rational-cell-cost"
    assert sha(data) == PIN
    path = HERE / "frozen_compact_public23.py"
    assert sha(path.read_bytes()) == COMPACT
    compact = load(path, "r27_norm_cell_compact").recipe(data)
    assert sha(compact) == "fc7b1e9e1b258f5254c75e046972fdc3bdc630b5b20fb35c9821839883c62019"
    native = (HERE / "R28NativeCell.lean").read_bytes()
    assert sha(native) == NATIVE and native.startswith(b"import ContractExact\n")
    text = compact.decode()
    marker = "def kernels:Kernels where"
    assert text.count(marker) == 1
    prefix, tail = text.split(marker)
    tail = marker + tail
    tail = re.sub(r"\bkernels\b", "retainedKernels", tail)
    tail = re.sub(r"\bcorrect\b", "retainedCorrect", tail)
    begin = text.index("def MYbc (")
    end = text.index("\nlemma ", begin)
    layer = text[begin:end]
    assert layer.count("def MYbc (") == 1
    layer = layer.replace("def MYbc (", "def r27CertifiedLayer (", 1)
    call = "Ya7G n x[r*n+j]! g[j]! b[j]! s.1 s.2.1 s.2.2 (λ _=>rowMean n x r) nU u.2.2 u.1 u.2.1"
    assert layer.count(call) == 1
    proposal = "let q:=R28NativeCell.attempt nU u.2.2 (!u.1) u.2.1 s.2.2 x[r*n+j]! g[j]! b[j]!;if q == 0 then " + call + " else q"
    layer = layer.replace(call, proposal)
    wrapper = "\nnamespace Submission\nopen ExactRuntime\n" + layer + "\n\ndef kernels : Kernels :=\n { retainedKernels with norm := ⟨Ybb2, r27CertifiedLayer⟩ }\nend Submission\n"
    result = (prefix + tail + "\n" + native.decode().split("\n", 1)[1] + wrapper).encode()
    assert len(result) <= 256000
    assert result.count(b"import ContractExact") == 1
    assert b"theorem retainedCorrect:" in result and b"theorem correct:" not in result
    return result


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("--source", type=Path, required=True)
    parser.add_argument("--output", type=Path, required=True)
    parser.add_argument("--receipt", type=Path, required=True)
    args = parser.parse_args()
    result = transform(args.source.read_bytes())
    policy = load(ROOT / "competitions/torchlean/candidates/r27-5h-20261029T194443Z/development/native/patch_public.py", "r27_norm_cell_policy").policy_check(result)
    args.output.parent.mkdir(parents=True, exist_ok=True)
    args.output.write_bytes(result)
    receipt = {"at_utc": datetime.datetime.now(datetime.timezone.utc).isoformat(),
               "candidate_sha256": sha(result), "candidate_bytes": len(result),
               "free_bytes": 256000 - len(result), "base_sha256": PIN,
               "native_helper_sha256": NATIVE, "compactor_sha256": COMPACT,
               "recipe_sha256": sha(Path(__file__).read_bytes()), "policy": policy,
               "runtime_change": "Only actual layernorm implementation; original stable/legacy split, Y8f/aux/YT and fallbackYa7G retained. Exact sign bridge uses!u.1. Other11 unchanged.",
               "proof_binding": "retainedCorrect provesretainedKernels only. Newkernel correctABSENT. OldMYbcandalloriginalproofsunchanged.",
               "state": "READY_FOR_PROFILE_JUDGMENT_THEN_NATIVE_COST_ONLY_NOT_ADMISSIBLE",
               "minimum": "Use full-call profile opportunity first. If worth a slot, pinnedcompile+completeNMLP differentialandtiming withallattempt/fallbackcost. Current43 via compatible reportchainINFERRED; never newshippedcomparison.",
               "native_compile": "NOT_RUN", "performance": "UNKNOWN",
               "publication": "Only ownintegration/module/receipts public, fullconstructedsourceprivate"}
    args.receipt.write_text(json.dumps(receipt, ensure_ascii=False, indent=2) + "\n", encoding="utf-8", newline="\n")
    print(json.dumps(receipt, ensure_ascii=False))


if __name__ == "__main__":
    main()
