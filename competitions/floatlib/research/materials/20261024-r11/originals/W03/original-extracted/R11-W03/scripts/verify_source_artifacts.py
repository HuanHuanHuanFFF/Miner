#!/usr/bin/env python3
"""Check SHA-bound patch application and unchanged boundaries, not Lean validity."""
from pathlib import Path
import hashlib
import json
import shutil
import subprocess
import tempfile

ROOT = Path(__file__).resolve().parents[1]
BASE_SHA = "4bdd1e7db35cd85e17d06511721d5dbf7f654ec12e58633264b08a086ec54fa0"
VARIANTS = [
    ("short-shared", "5645b861ce6eeaa00cbb80a791dcb225dca75463f1816ca051d52fe6b62ba910"),
    ("short-scalar-call", "4d778479f3c97c9793678b5f9e1d5742fe6190344d406ef3c9fef7b0ac86595e"),
]


def sha(b):
    return hashlib.sha256(b).hexdigest()


def main():
    base = (ROOT / "source/Kernel.lean").read_bytes()
    assert sha(base) == BASE_SHA and len(base) == 252609
    prefix = base.split(b"def dot8 (n p a0 a1 a2 a3 b0 b1 b2 b3", 1)[0]
    suffix_marker = b"def laneIndex (r : Fin 4) (j : Fin 2)"
    suffix = base[base.index(suffix_marker):]
    records = []
    for label, expected in VARIANTS:
        f = ROOT / f"agent-candidates/Kernel.{label}.lean"
        b = f.read_bytes()
        assert sha(b) == expected and len(b) <= 256000
        assert b.startswith(prefix) and b[b.index(suffix_marker):] == suffix
        patch = ROOT / f"agent-candidates/{label}.patch"
        with tempfile.TemporaryDirectory(prefix="r11-w03-patch-") as td:
            (Path(td) / "Kernel.lean").write_bytes(base)
            proc = subprocess.run(["patch", "--batch", "--fuzz=0", "-p1", "-i", str(patch)],
                                  cwd=td, text=True, capture_output=True)
            assert proc.returncode == 0, proc.stdout + proc.stderr
            assert (Path(td) / "Kernel.lean").read_bytes() == b
        added_lines = [l[1:] for l in patch.read_text().splitlines() if l.startswith("+") and not l.startswith("+++")]
        # This is only a lexical check over added lines, never an axiom audit.
        import re
        forbidden = re.compile(r"\b(sorry|admit|unsafe|axiom|extern|implemented_by|native_decide|set_option)\b")
        hits = [l for l in added_lines if forbidden.search(l)]
        assert not hits, hits
        records.append({"variant": label, "sha256": sha(b), "bytes": len(b),
                        "headroom_bytes": 256000-len(b), "patch_exact": True,
                        "prefix_and_finish8_through_bmm_spec_unchanged": True,
                        "added_line_forbidden_token_hits": hits,
                        "Lean": "NOT_RUN", "axiom_audit": "NOT_RUN",
                        "codegen": "NOT_RUN", "full_timing": "NOT_RUN"})
    print(json.dumps({"status": "STATIC_ARTIFACT_CHECKS_PASS", "base_sha256": BASE_SHA,
                      "patch_tool": shutil.which("patch"), "variants": records}, indent=2))


if __name__ == "__main__":
    main()
