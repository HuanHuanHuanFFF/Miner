"""Assemble owned research sources; never builds Lean or native code locally."""
from pathlib import Path
from datetime import datetime, timezone
import hashlib
import importlib.util
import json
import sys

sys.dont_write_bytecode = True
HERE = Path(__file__).resolve().parent
ROOT = next(p for p in HERE.parents if (p / "AGENTS.md").is_file())
R26 = ROOT / "competitions/torchlean/candidates/r26-1h-20261029T085515Z/development/native"

def digest(data):
    return hashlib.sha256(data).hexdigest()

def publish(name, source, changes):
    data = source.encode("utf-8")
    dst = HERE / name
    dst.mkdir(exist_ok=True)
    kernel = dst / "Kernel.lean"
    if kernel.exists() and kernel.read_bytes() != data:
        raise RuntimeError(f"Refusing to change frozen candidate {name}")
    kernel.write_bytes(data)
    row = {
        "id": name, "path": kernel.relative_to(ROOT).as_posix(),
        "sha256": digest(data), "bytes": len(data), "entry": "Submission.kernels",
        "status": "UNPROVED_NATIVE_RESEARCH_NOT_COMPILED",
        "proof_entry": "Submission.retainedCorrect",
        "proof_covers": "Submission.retainedKernels only, not Submission.kernels",
        "changes": changes,
        "bias": "Included as final term of same exact dot before one finishWord call",
        "official_contract": "Unmodified ContractExact and original12 obligations",
    }
    (dst / "source-receipt.json").write_text(json.dumps(row, indent=2) + "\n", encoding="utf-8")
    return row

def main():
    base_file = R26 / "word-official8-draft/Kernel.lean"
    base = base_file.read_bytes()
    original = base.decode("utf-8")
    direct = (HERE / "DirectWord.lean.inc").read_text(encoding="utf-8")
    marker = "namespace Submission.R26WordModel"
    assert original.count(marker) == 1
    source = original.replace(marker, direct + "\n\n" + marker, 1)
    start = source.index("@[noinline] def dot (n : Nat)", source.index(marker))
    end = source.index("@[noinline] def linear", start)
    source = source[:start] + "@[noinline] def dot (n : Nat) (fa fb : Nat → Word) : Word :=\n  R27DirectWord.dot n fa fb\n\n" + source[end:]
    old = "  if rows * outW == 0 then #[]\n  else\n"
    assert source.count(old) == 1
    source = source.replace(old, "  if rows * outW == 0 then #[]\n  else if rows == 1 then R27DirectWord.linear rows inW outW relu X W b\n  else\n", 1)
    old = "  if batch * (m * n) == 0 then #[]\n  else\n"
    assert source.count(old) == 1
    source = source.replace(old, "  if batch * (m * n) == 0 then #[]\n  else if m == 1 then R27DirectWord.gemm batch m k n A B\n  else\n", 1)
    rows = [publish("raw-direct1", source, [
        "Raw UInt32 normal/subnormal word decode, no FloatArray or encoded word arrays",
        "Official finishWord once at terminal64/128 instead of manual RNE",
        "Actual product exponent range scan instead of Cartesian operand min/max bound for direct path",
        "Direct getters for rows=1 linear and m=1 gemm, no one-use row/filter copies",
        "Shared prepared raw convolution windows and filters retained",
        "All twelve runtime entries remain populated; retained proof does not certify changed entries",
    ])]
    loader = ROOT / "competitions/torchlean/candidates/r25-90m-20261029T064916Z/verification/exact-policy-preflight.py"
    spec = importlib.util.spec_from_file_location("r27_policy", loader)
    mod = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(mod)
    ns, sources = mod.load_official_policy()
    for row in rows:
        file = ROOT / row["path"]
        row["intake"] = ns["intake"](mod.Utf8Path(file), None)
        row["policy"] = ns["policy"](mod.Utf8Path(file), None)
        row["intake_policy_passed"] = row["intake"] is None and row["policy"] is None
    report = {
        "at_utc": datetime.now(timezone.utc).isoformat(),
        "scope": "PINNED_SOURCE_INTAKE_POLICY_ONLY_NO_LEAN_BUILD",
        "base": {"path": base_file.relative_to(ROOT).as_posix(), "sha256": digest(base)},
        "policy_sources": sources, "candidates": rows,
    }
    initial = HERE / "READY-initial-raw-direct1.json"
    if not initial.exists():
        initial.write_text(json.dumps(report, indent=2) + "\n", encoding="utf-8")
    # READY.json is the live role index and must not be reset by replaying this
    # historical source builder. Existing first-read receipts stay immutable.
    print(json.dumps(rows, indent=2))

if __name__ == "__main__":
    main()
