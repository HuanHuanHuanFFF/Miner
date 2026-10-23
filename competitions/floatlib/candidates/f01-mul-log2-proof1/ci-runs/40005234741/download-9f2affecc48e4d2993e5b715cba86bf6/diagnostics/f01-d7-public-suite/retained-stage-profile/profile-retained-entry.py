"""Separate Linux statement replay after an exact retained41 full gate; diagnostic only."""
from dataclasses import asdict
import argparse
import hashlib
import importlib.util
import json
import os
from pathlib import Path
import subprocess
import sys
import traceback

PARENT = "41bce4856c4c921dd67b6115928df16e5e8ed08a55b71f1296d28b77cf9ce9a7"
HEAD = "4b7e83841cc0c32c6529f533923c73d33b5ecf97"
SUITE = "a16494e97c6a073bfd8accf72480c34534c87808092c56074fdcfa42cd34868a"


def require(ok, message):
    if not ok:
        raise RuntimeError(message)


def sha(raw):
    return hashlib.sha256(raw).hexdigest()


def verify_original(kernel, verdict_raw, summary_raw, seed):
    """Pure validation of the original gate/summary identity, never rewrite either."""
    verdict, summary = json.loads(verdict_raw), json.loads(summary_raw)
    rows = [r for r in summary["results"] if r["candidate"] == kernel.parent.name]
    require(len(rows) == 1, "Original summary candidate absent/ambiguous")
    row = rows[0]
    require(row["kernel_sha256"] == PARENT and row["verdict_sha256"] == sha(verdict_raw), "Original gate/source binding differs")
    require(row["full_gate"] is True and row["exit_code"] == 0 and row["validation_mode"] == "full-gate",
            "Original gate has not completed successfully")
    require(verdict["passed"] is True and verdict["mode"] == "gate" and verdict["slot"] == "full" and
            verdict["stage"] == "score" and verdict["submission"] == kernel.parent.name, "Original is not an exact full scored gate")
    require(verdict["seed"] == summary["seed"] == seed and len(verdict["rounds"]) == 25,
            "Original full gate seed/round count mismatch")
    require(summary.get("complete") is True and summary.get("rounds") == 25 and summary.get("pairs") == 500000,
            "Original requested gate batch/protocol incomplete")
    require(verdict["suite"]["sha256"] == summary["suite_sha256"] == SUITE and summary["official_commit"] == HEAD,
            "Original public suite/version mismatch")
    require(verdict["reference_complete"] is True and verdict["incumbent_failed"] is False and
            verdict["exhausted"] is False and verdict["verifier_fingerprint"] == verdict["verifier_fingerprint_end"],
            "Original reference/verifier not complete")
    require(bool(verdict["verifier_fingerprint"]) and len(verdict["classes"]) == 26,
            "Original verifier/classes missing")
    return {"original_verdict_sha256": sha(verdict_raw), "original_summary_sha256": sha(summary_raw),
            "seed": seed, "kernel_sha256": PARENT, "original_gate_passed": True}


def main(argv=None):
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--upstream", type=Path, required=True)
    parser.add_argument("--kernel", type=Path, required=True)
    parser.add_argument("--out", type=Path, required=True)
    parser.add_argument("--plan", type=Path, required=True)
    parser.add_argument("--original-verdict", type=Path, required=True)
    parser.add_argument("--original-summary", type=Path, required=True)
    args = parser.parse_args(argv)
    require(sys.platform.startswith("linux"), "Runtime requires the official disposable Linux runner")
    import fcntl
    require(sha(args.kernel.read_bytes()) == PARENT, "Only exact retained41 is supported")
    original_verdict = args.original_verdict.read_bytes()
    original_summary = args.original_summary.read_bytes()
    identity = verify_original(args.kernel, original_verdict, original_summary, int(os.environ["BENCH_SEED"]))
    require(subprocess.check_output(["git", "rev-parse", "HEAD"], cwd=args.upstream, text=True).strip() == HEAD,
            "Original official checkout changed")
    args.out.mkdir(parents=True, exist_ok=True)
    def save(name, raw):
        with (args.out / name).open("xb") as stream:
            stream.write(raw)
    save("profile-retained-original-verdict.json", original_verdict)
    save("profile-retained-original-summary.json", original_summary)
    profile_path = Path(__file__).with_name("profile-retained.py")
    save("profile-retained-module.py", profile_path.read_bytes())
    save("profile-retained-entry.py", Path(__file__).read_bytes())
    sys.path.insert(0, str(args.upstream))
    spec = importlib.util.spec_from_file_location("retained_profile_official_gate", args.upstream / "gate.py")
    gate = importlib.util.module_from_spec(spec)
    sys.modules[spec.name] = gate
    spec.loader.exec_module(gate)
    spec = importlib.util.spec_from_file_location("retained_profile", profile_path)
    profile = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(profile)
    drawn = json.loads(args.plan.read_bytes())
    original_statement = gate.statement
    def statement(src, verdict):
        reason = original_statement(src, verdict)
        if reason:
            return reason
        try:
            profile.run(gate, args.kernel, args.out, drawn, int(os.environ["BENCH_SEED"]))
        except Exception:
            save("profile-retained-error.txt", traceback.format_exc().encode())
            raise
        return None
    gate.STAGES = [("intake", gate.intake), ("policy", gate.policy), ("statement", statement)]
    with (gate.HERE / "gate.lock").open("w") as lock:
        fcntl.flock(lock, fcntl.LOCK_EX)
        gate.check_limits()
        digest = gate.pin(gate.SLOTS["full"])
        verdict = gate.gate(args.kernel.parent, digest, "gate", "full")
    unchanged = args.original_verdict.read_bytes() == original_verdict and args.original_summary.read_bytes() == original_summary
    result = {**asdict(verdict), **identity, "mode": "diagnostic-statement-profile", "diagnostic_only": True,
              "full_gate": False, "original_receipts_unchanged": unchanged,
              "profile_module_sha256": sha(profile_path.read_bytes()), "entry_sha256": sha(Path(__file__).read_bytes()),
              "drawn_plan_file_sha256": sha(args.plan.read_bytes()),
              "scope": "Separate disposable statement replay; never replace original full-gate verdict or score"}
    save("diagnostic-only-verdict.json", (json.dumps(result, indent=2) + "\n").encode())
    require(unchanged, "Original receipts changed during diagnostic replay")
    return 0 if verdict.passed else 1


if __name__ == "__main__":
    sys.exit(main())
