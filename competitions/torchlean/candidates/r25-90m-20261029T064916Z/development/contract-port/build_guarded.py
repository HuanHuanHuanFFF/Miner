"""Prepare guard-only source changes; frozen policy1 Kernel files are read only."""
from pathlib import Path

HERE = Path(__file__).resolve().parent
NAMES = ["linearCached", "gemmCached", "conv2dCached", "depthwiseCached", "rmsnormCached", "layernormCached"]
RENAMED = ["linearPreGuard", "gemmPreGuard", "conv2dPreGuard", "depthwisePreGuard", "rmsnormPreGuard", "layernormPreGuard"]


def main() -> None:
    base = (HERE / "PatchNormCache.lean.inc").read_text(encoding="utf-8")
    for old, new in zip(NAMES, RENAMED):
        base = base.replace(old, new)
    guarded = base + "\n" + (HERE / "EmptyOutputGuards.lean.inc").read_text(encoding="utf-8")
    (HERE / "GuardedPatchNorm.lean.inc").write_text(guarded, encoding="utf-8")


if __name__ == "__main__":
    main()
