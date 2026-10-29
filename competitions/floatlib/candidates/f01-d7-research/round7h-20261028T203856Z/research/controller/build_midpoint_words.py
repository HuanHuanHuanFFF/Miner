"""Build a portable component diagnostic; do not invoke Lean/CI/Git."""
from pathlib import Path
import datetime
import hashlib
import json

ROOT = Path(__file__).resolve().parents[7]
# Resolve the repository deterministically from this script, without depending
# on the caller's current directory or walking outside the declared workspace.
assert (ROOT / "AGENTS.md").is_file(), ROOT
CANDIDATES = ROOT / "competitions/floatlib/candidates"
BASE = CANDIDATES / "f01-r15-dev-packed-b2-1/Kernel.lean"
FRAGMENT = Path(__file__).with_name("MidpointWords.lean.inc")
OUT = CANDIDATES / "f01-r24-research-midpoint-words1"
HELPER = CANDIDATES / "f01-d7-research/round9h-20261026T194639Z/development-helper-audit-v8.py"


def sha(data: bytes) -> str:
    return hashlib.sha256(data).hexdigest()


def main() -> None:
    base, fragment = BASE.read_bytes(), FRAGMENT.read_bytes()
    assert len(base) == 226829
    assert sha(base) == "622d8394a7127e93dcaf992c62c6dfcff7208d212738409a5e34525dfafd1a58"
    data = base + b"\n" + fragment
    assert len(data) <= 256000
    OUT.mkdir(exist_ok=True)
    kernel = OUT / "Kernel.lean"
    if kernel.exists():
        assert kernel.read_bytes() == data, "A frozen candidate must not be overwritten"
    else:
        kernel.write_bytes(data)
    roots = ["Submission.R24MidpointWords." + x for x in
             ["upper_decode", "lower_inner_decode", "lower_power_decode", "lower_minNormal_decode"]]
    manifest = {
        "candidate": OUT.name,
        "candidate_file": "Kernel.lean",
        "candidate_sha256": sha(data),
        "candidate_bytes": len(data),
        "created_at_utc": datetime.datetime.now(datetime.timezone.utc).isoformat(),
        "validation_mode": "statement-only",
        "diagnostic_only": True,
        "diagnostic_timeout_seconds": 180,
        "proof_status": "NOT_RUN",
        "performance": "NOT_RUN",
        "formal_submission": "NOT_SUBMITTED",
        "official_submission_inherited": False,
        "helper_audit_module": HELPER.name,
        "helper_audit_module_path": HELPER.relative_to(CANDIDATES).as_posix(),
        "helper_audit_module_sha256": sha(HELPER.read_bytes()),
        "explicit_helper_audit": roots,
        "helper_audit_required_endpoints": roots,
        "helper_audit_expected_count": len(roots),
        "helper_audit_source_sha256": sha(data),
        "diagnostic_evaluations": [],
        "components": [{"path": FRAGMENT.relative_to(ROOT).as_posix(),
                        "sha256": sha(fragment), "bytes": len(fragment)}],
        "runtime_prefix": {"path": BASE.relative_to(ROOT).as_posix(),
                           "sha256": sha(base), "bytes": len(base), "byte_identical": True},
        "scope": "Actual UInt64 positive normal binary32 midpoint-word decodes, including power-of-two and minimum-normal boundary. Old B2 four endpoints unchanged.",
        "missing": ["Lean/replay/allowed-axiom checks", "Negative-sign wrapper and raw32 proposal extraction", "Real RNE32 cell theorem", "Native endpoint evaluation and error composition", "Runtime/whole-model timing"],
        "local_Lean": False,
        "CI_owner": "D",
        "window_start_utc": "2026-10-28T20:38:56Z",
        "shared_deadline_utc": "2026-10-29T03:38:56Z",
    }
    (OUT / "manifest.json").write_text(json.dumps(manifest, indent=2) + "\n", encoding="utf-8")
    receipt = {"candidate": OUT.name, "sha256": sha(data), "bytes": len(data),
               "fragment_sha256": sha(fragment), "bytes_prefix_equal": data[:len(base)] == base,
               "helper_sha256": sha(HELPER.read_bytes()), "proof": "NOT_RUN",
               "finite_math_model": "midpoint-word-model-results.json"}
    FRAGMENT.with_name("midpoint-words1-source-receipt.json").write_text(
        json.dumps(receipt, indent=2) + "\n", encoding="utf-8")
    print(json.dumps(receipt))


if __name__ == "__main__":
    main()
