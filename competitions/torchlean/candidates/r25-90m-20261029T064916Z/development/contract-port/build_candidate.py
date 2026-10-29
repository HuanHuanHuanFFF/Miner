"""Build complete TorchLean candidates from the pinned shipped baseline.

This is source assembly only: it never invokes Lean, a native build, Git, or CI.
"""
from pathlib import Path
import argparse
import hashlib
import json

HERE = Path(__file__).resolve().parent
ROOT = HERE.parents[5]
SOURCE = ROOT / "competitions/floatlib/candidates/f01-d7-research/round7h-20261028T203856Z/source-snapshot/torchlean/kernels/exact/incumbent/Kernel.lean"
OFFICIAL_COMMIT = "accb82b6e2adeda1b41a57a260d68fb3879c427e"


def sha(data: bytes) -> str:
    return hashlib.sha256(data).hexdigest()


def main() -> None:
    parser = argparse.ArgumentParser()
    parser.add_argument("--addition", default="DecodeCache.lean.inc")
    parser.add_argument("--variant", default="decode-cache")
    parser.add_argument("--preserve-dense", action="store_true")
    parser.add_argument("--preserve-conv", action="store_true")
    parser.add_argument("--preserve-norm", action="store_true")
    args = parser.parse_args()
    assert args.variant.replace("-", "").isalnum()
    raw = SOURCE.read_bytes()
    baseline = HERE / "baseline"
    baseline.mkdir(parents=True, exist_ok=True)
    (baseline / "Kernel.lean").write_bytes(raw)
    out = {"official_commit": OFFICIAL_COMMIT, "source": str(SOURCE.relative_to(ROOT)),
           "source_sha256": sha(raw), "source_bytes": len(raw),
           "baseline_exact_byte_copy": True, "lean": "NOT_RUN", "native": "NOT_RUN"}
    addition = HERE / args.addition
    if addition.exists():
        body = raw.decode("utf-8")
        marker = "/-! ## The entry -/"
        assert body.count(marker) == 1
        extra = addition.read_text(encoding="utf-8")
        body = body.replace(marker, extra + "\n" + marker)
        rewrites = []
        if "def linearCached" in extra:
            if not args.preserve_dense:
                body = body.replace("dense := ⟨linearWith dotFn, gemmWith dotFn⟩", "dense := ⟨linearCached, gemmCached⟩")
            if not args.preserve_conv:
                body = body.replace("conv := ⟨conv2dWith dotFn, depthwiseWith dotFn⟩", "conv := ⟨conv2dCached, depthwiseCached⟩")
            rewrites += ["linearCached_eq", "gemmCached_eq", "conv2dCached_eq", "depthwiseCached_eq"]
        if "def rmsnormCached" in extra:
            if not args.preserve_norm:
                body = body.replace("norm := ⟨rmsnormWith dotFn, layernormWith dotFn⟩", "norm := ⟨rmsnormCached, layernormCached⟩")
            rewrites += ["rmsnormCached_eq", "layernormCached_eq"]
        if rewrites:
            body = body.replace("maxpoolW_eq, dotFn_eq_dotOf,", ", ".join(rewrites) + ",\n    maxpoolW_eq, dotFn_eq_dotOf,")
        candidate = HERE / args.variant
        candidate.mkdir(parents=True, exist_ok=True)
        encoded = body.encode("utf-8")
        (candidate / "Kernel.lean").write_bytes(encoded)
        out["candidate"] = {"path": str((candidate / "Kernel.lean").relative_to(ROOT)),
                            "sha256": sha(encoded), "bytes": len(encoded),
                            "preserved_families": [family for family in ["dense", "conv", "norm"] if getattr(args, "preserve_" + family)],
                            "full_submission_correct": "PRESENT_NOT_RUN", "policy": "NOT_RUN"}
    (HERE / f"{args.variant}-source-receipt.json").write_text(json.dumps(out, indent=2) + "\n", encoding="utf-8")
    print(json.dumps(out, indent=2))


if __name__ == "__main__":
    main()
